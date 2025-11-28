// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

use std::process::exit;

use tellusim::*;

extern crate tellusim;

/*
 */
fn main() {
	
	// create app
	let mut app = App::new();
	if !app.create() { exit(1) }
	
	let mut window = Window::new_with_platform_index(app.platform(), app.device());
	if !window.is_valid_ptr() { exit(1) }
	
	window.set_size(app.width(), app.height());
	
	window.set_close_clicked_callback({
		let mut window = window.copy_ptr();
		move || { window.stop() }
	});
	
	window.set_keyboard_pressed_callback({
		let mut window = window.copy_ptr();
		move |key: u32, _code: u32| {
			if key == WindowKey::Esc as u32 { window.stop() }
		}
	});
	
	let title = window.platform_name() + &" Tellusim::Meshlet Rust";
	if !window.create_with_title(&title) || !window.set_hidden(false) { exit(1) }
	
	// scene size
	let grid_size: i32 = 4;
	let num_instances: u32 = grid_size as u32 * 2 + 1;
	let num_instances2: u32 = num_instances * num_instances;
	
	// mesh parameters
	let group_size: u32 = 32;
	let max_vertices: u32 = 64;
	let max_primitives: u32 = 126;
	let mesh_flags = MeshModelFlags::Meshlet64x126;
	
	// create device
	let device = Device::new_with_window(&mut window);
	if !device.is_valid_ptr() { exit(1) }
	
	// create common pipeline
	let mut common_pipeline = device.create_pipeline();
	common_pipeline.set_color_format(0, window.color_format());
	common_pipeline.set_depth_format(window.depth_format());
	common_pipeline.set_depth_func(PipelineDepthFunc::Greater);
	common_pipeline.set_cull_mode(if window.platform() == Platform::VK { PipelineCullMode::Front } else { PipelineCullMode::Back });
	
	// vertex pipeline
	let mut vertex_pipeline = device.create_pipeline_with_pipeline(&common_pipeline);
	vertex_pipeline.set_uniform_mask(0, ShaderMask::Vertex);
	vertex_pipeline.set_uniform_mask(1, ShaderMask::Vertex);
	vertex_pipeline.add_attribute(PipelineAttribute::Position, Format::RGBf32, 0, 0, 32);
	vertex_pipeline.add_attribute(PipelineAttribute::Normal, Format::RGBf32, 0, 16, 32);
	if !vertex_pipeline.load_shader_glsl(ShaderType::Vertex, "main.shader", &format!("VERTEX_PIPELINE=1; VERTEX_SHADER=1; NUM_INSTANCES={0}u", num_instances2)) { exit(1) }
	if !vertex_pipeline.load_shader_glsl(ShaderType::Fragment, "main.shader", "VERTEX_PIPELINE=1; FRAGMENT_SHADER=1") { exit(1) }
	if !vertex_pipeline.create() { exit(1) }
	
	// mesh pipeline
	let mut mesh_pipeline = device.create_pipeline();
	if device.has_shader(ShaderType::Task) {
		mesh_pipeline = device.create_pipeline_with_pipeline(&common_pipeline);
		mesh_pipeline.set_uniform_mask(0, ShaderMask::Mesh);
		mesh_pipeline.set_uniform_mask(1, ShaderMask::Task | ShaderMask::Mesh);
		mesh_pipeline.set_storage_masks(0, 3, ShaderMask::Mesh);
		if !mesh_pipeline.load_shader_glsl(ShaderType::Task, "main.shader", "MESH_PIPELINE=1; TASK_SHADER=1") { exit(1) }
		if !mesh_pipeline.load_shader_glsl(ShaderType::Mesh, "main.shader", &format!("MESH_PIPELINE=1; MESH_SHADER=1; GROUP_SIZE={0}u; NUM_VERTICES={1}u; NUM_PRIMITIVES={2}u; NUM_INSTANCES={3}u", group_size, max_vertices, max_primitives, num_instances2)) { exit(1) }
		if !mesh_pipeline.load_shader_glsl(ShaderType::Fragment, "main.shader", "MESH_PIPELINE=1; FRAGMENT_SHADER=1") { exit(1) }
		if !mesh_pipeline.create() { exit(1) }
	}
	
	// compute pipeline
	let mut draw_kernel = device.create_kernel();
	let mut clear_kernel = device.create_kernel();
	let mut compute_pipeline = device.create_pipeline();
	if device.has_shader(ShaderType::Compute) {
		
		// create compute pipeline
		compute_pipeline = device.create_pipeline();
		compute_pipeline.set_texture_mask(0, ShaderMask::Fragment);
		compute_pipeline.set_color_format(0, window.color_format());
		compute_pipeline.set_depth_format(window.depth_format());
		if !compute_pipeline.load_shader_glsl(ShaderType::Vertex, "main.shader", "COMPUTE_PIPELINE=1; VERTEX_SHADER=1") { exit(1) }
		if !compute_pipeline.load_shader_glsl(ShaderType::Fragment, "main.shader", "COMPUTE_PIPELINE=1; FRAGMENT_SHADER=1") { exit(1) }
		if !compute_pipeline.create() { exit(1) }
		
		// create draw kernel
		draw_kernel = device.create_kernel().set_surfaces(2).set_uniforms(2).set_storages(3);
		if !draw_kernel.load_shader_glsl("main.shader", &format!("COMPUTE_PIPELINE=1; COMPUTE_DRAW_SHADER=1; COLOR_SHADING=1; GROUP_SIZE={0}u; NUM_VERTICES={1}u; NUM_PRIMITIVES={2}u; NUM_INSTANCES={3}u", npotu32(max_primitives), max_vertices, max_primitives, num_instances2)) { exit(1) }
		if !draw_kernel.create() { exit(1) }
		
		// create clear kernel
		clear_kernel = device.create_kernel().set_uniforms(1).set_surfaces(1);
		if !clear_kernel.load_shader_glsl("main.shader", "COMPUTE_PIPELINE=1; COMPUTE_CLEAR_SHADER=1") { exit(1) }
		if !clear_kernel.create() { exit(1) }
	}
	
	// load mesh
	let mut mesh = Mesh::new();
	let mut src_mesh = Mesh::new();
	if !src_mesh.load_with_name("model.glb", None) { exit(1) }
	if !mesh_refine::subdiv(&mut mesh, &src_mesh, 5) { exit(1) }
	mesh.create_normals_with_force(false);
	mesh.create_islands(max_vertices, max_primitives);
	
	// create vertex model
	let mut vertex_model = MeshModel::new();
	if !vertex_model.create_with_mesh_flags(&device, &vertex_pipeline, &mesh, MeshModelFlags::Default) { exit(1) }
	
	// create mesh model
	let mut mesh_model = MeshModel::new();
	if !mesh_model.create_with_mesh_flags(&device, &vertex_pipeline, &mesh, MeshModelFlags::Default | mesh_flags) { exit(1) }
	let mut mesh_vertex_buffer = mesh_model.vertex_buffer();
	let mut mesh_meshlet_buffer = mesh_model.meshlet_buffer();
	
	// mesh info
	let num_meshlets = mesh_model.num_meshlets();
	let num_vertices = num_instances2 * vertex_model.num_vertices();
	let num_primitives = num_instances2 * vertex_model.num_indices() / 3;
	ts_logf!(Message, "  Vertices: {0}\n", String::from_number(num_vertices as u64));
	ts_logf!(Message, "Primitives: {0}\n", String::from_number(num_primitives as u64));
	ts_logf!(Message, "  Meshlets: {0} ({1})\n", num_meshlets * num_instances2, num_meshlets);
	ts_logf!(Message, " Instances: {0}\n", num_instances2);
	ts_logf!(Message, " GroupSize: {0}\n", group_size);
	
	// compute surfaces
	let mut depth_surface = device.create_texture();
	let mut color_surface = device.create_texture();
	
	// create target
	let mut target = device.create_target_with_window(&mut window);
	target.set_clear_color_with_rgba(0.2, 0.2, 0.2, 1.0);
	target.set_clear_depth(0.0);
	
	// current mode
	#[derive(PartialEq)]
	enum Mode {
		Vertex = 0,
		Mesh,
		Compute,
	}
	let mut mode = Mode::Vertex;
	if mesh_pipeline.is_created() { mode = Mode::Mesh }
	if compute_pipeline.is_created() { mode = Mode::Compute }
	
	// instance transforms
	let mut transforms: Vec<Matrix4x3f> = Vec::new();
	
	// main loop
	window.run({
		let mut window = window.copy_ptr();
		move || -> bool {
		
		// update window
		Window::update();
		
		// render window
		if !window.render() { return false }
		
		// switch mode
		if window.keyboard_key('1' as u32) { mode = Mode::Vertex }
		else if window.keyboard_key('2' as u32) && mesh_pipeline.is_created() { mode = Mode::Mesh }
		else if window.keyboard_key('3' as u32) && compute_pipeline.is_created() { mode = Mode::Compute }
		
		// current time
		let time = time::seconds() as f32;
		
		// common parameters
		#[repr(C)]
		#[derive(Default)]
		struct CommonParameters {
			projection: Matrix4x4f,
			modelview: Matrix4x4f,
			camera: Vector4f,
		}
		let mut common_parameters = CommonParameters::default();
		common_parameters.camera = Vector4f::new(4.0 + grid_size as f32 * 3.0, 0.0, 1.0, 0.0);
		common_parameters.projection = Matrix4x4f::perspective_infinity_reverse(60.0, window.width() as f32 / window.height() as f32, 0.1);
		common_parameters.modelview = Matrix4x4f::look_at(&Vector3f::new_v4(&common_parameters.camera), &(&Vector3f::new_v4(&common_parameters.camera) + &Vector3f::new(-16.0, 0.0, -4.0)), &Vector3f::new(0.0, 0.0, 1.0));
		if target.is_flipped() { common_parameters.projection = &Matrix4x4f::scale(1.0, -1.0, 1.0) * &common_parameters.projection }
		
		// transform parameters
		transforms.clear();
		for y in -grid_size .. grid_size + 1 {
			for x in -grid_size .. grid_size + 1 {
				let translate = Matrix4x3f::translate(x as f32 * 3.2, y as f32 * 3.2, 0.0);
				let rotate = &Matrix4x3f::rotate_z(time * 32.0 + y as f32 * 2715.53) * &Matrix4x3f::rotate_x(time * 16.0 + (x as f32) * 9774.37);
				let scale = Matrix4x3f::scale_s(f32::sin(time + (x ^ y) as f32 * 13.73) * 0.2 + 0.8);
				transforms.push(&translate * &rotate * &scale);
			}
		}
		
		// compute rasterization
		if mode == Mode::Compute {
			
			// create surfaces
			if !depth_surface.is_created() || depth_surface.width() != window.width() || depth_surface.height() != window.height() {
				window.finish();
				depth_surface = device.create_texture2d_with_width_flags(Format::Ru32, window.width(), window.height(), TextureFlags::Surface | TextureFlags::Buffer);
				color_surface = device.create_texture2d_with_width_flags(Format::Ru32, window.width(), window.height(), TextureFlags::Surface | TextureFlags::Buffer);
			}
			
			// create command list
			let mut compute = device.create_compute();
			
			// clear depth surface
			compute.set_kernel(&mut clear_kernel);
			compute.set_uniform(0, &Vector4f::new_s(0.0));
			compute.set_surface_texture(0, &mut depth_surface);
			compute.dispatch(&mut depth_surface);
			compute.barrier(&mut depth_surface);
			
			// clear color texture
			compute.set_kernel(&mut clear_kernel);
			compute.set_uniform(0, &Vector4u::new_s(target.clear_color().rgbau8()));
			compute.set_surface_texture(0, &mut color_surface);
			compute.dispatch(&mut color_surface);
			compute.barrier(&mut color_surface);
			
			// compute parameters
			#[repr(C)]
			#[derive(Default)]
			struct ComputeParameters {
				num_meshlets: u32,
				group_offset: u32,
				surface_size: Vector2f,
				surface_stride: f32,
			}
			let mut compute_parameters = ComputeParameters {
				num_meshlets: num_meshlets,
				group_offset: 0,
				surface_size: Vector2f::new(window.width() as f32, window.height() as f32),
				surface_stride: alignu32(window.width(), 64) as f32,
			};
			
			// dispatch compute kernel
			compute.set_kernel(&mut draw_kernel);
			compute.set_uniform(0, &common_parameters);
			compute.set_surface_texture(0, &mut depth_surface);
			compute.set_surface_texture(1, &mut color_surface);
			compute.set_storage_array(0, &transforms);
			compute.set_storage_buffer(1, &mut mesh_vertex_buffer);
			compute.set_storage_buffer(2, &mut mesh_meshlet_buffer);
			let max_groups = device.features().max_group_count_x;
			for i in (0 .. num_meshlets * num_instances2).step_by(max_groups as usize) {
				let size = u32::min(num_meshlets * num_instances2 - i, max_groups);
				compute_parameters.group_offset = i;
				compute.set_uniform(1, &compute_parameters);
				compute.dispatch_with_width(npotu32(max_primitives) * size);
			}
			
			// flush surface
			device.flush_texture(&mut depth_surface);
			device.flush_texture(&mut color_surface);
		};
		
		// window target
		target.begin();
		{
			// create command list
			let mut command = device.create_command_with_target(&mut target);
			
			match mode {
				
				// vertex pipeline
				Mode::Vertex => {
					command.set_pipeline(&mut vertex_pipeline);
					command.set_uniform(0, &common_parameters);
					command.set_uniform_array(1, &transforms);
					vertex_model.set_buffers(&mut command);
					vertex_model.draw_instanced(&mut command, 0, num_instances2);
				},
				
				// mesh pipeline
				Mode::Mesh => {
					command.set_pipeline(&mut mesh_pipeline);
					command.set_uniform(0, &common_parameters);
					command.set_storage_array(0, &transforms);
					command.set_storage_buffer(1, &mut mesh_vertex_buffer);
					command.set_storage_buffer(2, &mut mesh_meshlet_buffer);
					let max_meshlets = device.features().max_task_meshes;
					for i in (0 .. num_meshlets).step_by(max_meshlets as usize) {
						let size = u32::min(num_meshlets - i, max_meshlets);
						command.set_uniform(1, &Vector2u::new(size, i));
						command.draw_mesh(num_instances2);
					}
				},
				
				// compute pipeline
				Mode::Compute => {
					command.set_pipeline(&mut compute_pipeline);
					command.set_texture(0, &mut color_surface);
					command.draw_arrays(3);
				}
			}
		}
		target.end();
		
		// present window
		if !window.present() { return false }
		
		// check device
		if !device.check() { return false }
		
		true
	}});
	
	// finish context
	window.finish();
	
	// done
	log::print("Done\n");
}

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
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
			if key == WindowKey::Esc { window.stop() }
		}
	});
	
	let title = window.platform_name() + &" Tellusim::Tracing Rust";
	if !window.create_with_title(&title) || !window.set_hidden(false) { exit(1) }
	
	// scene size
	let grid_size: i32 = 3;
	let num_instances: u32 = grid_size as u32 * 2 + 1;
	let num_instances2: u32 = num_instances * num_instances;
	
	// create device
	let device = Device::new_with_window(&mut window);
	if !device.is_valid_ptr() { exit(1) }
	
	// check compute tracing support
	if device.features().compute_tracing == 0 {
		ts_logf!(Error, "compute tracing is not supported\n");
		exit(1)
	}
	
	// create pipeline
	let mut pipeline = device.create_pipeline();
	pipeline.set_texture_mask(0, ShaderMask::Fragment);
	pipeline.set_color_format(0, window.color_format());
	pipeline.set_depth_format(window.depth_format());
	if !pipeline.load_shader_glsl(ShaderType::Vertex, "main.shader", "VERTEX_SHADER=1") { exit(1) }
	if !pipeline.load_shader_glsl(ShaderType::Fragment, "main.shader", "FRAGMENT_SHADER=1") { exit(1) }
	if !pipeline.create() { exit(1) }
	
	// create vertex pipeline
	let mut vertex_pipeline = device.create_pipeline();
	vertex_pipeline.add_attribute(PipelineAttribute::Position, Format::RGBf32, 0, 0, 32);
	vertex_pipeline.add_attribute(PipelineAttribute::Normal, Format::RGBf32, 0, 16, 32);
	
	// create kernel
	let mut kernel = device.create_kernel().set_uniforms(1).set_storages(2).set_surfaces(1).set_tracings(1);
	if !kernel.load_shader_glsl("main.shader", "COMPUTE_SHADER=1; GROUP_SIZE=8u") { exit(1) }
	if !kernel.create() { exit(1) }
	
	// load mesh
	let mut mesh = Mesh::new();
	let mut src_mesh = Mesh::new();
	if !src_mesh.load_with_name("model.glb", None) { exit(1) }
	if !mesh_refine::subdiv(&mut mesh, &src_mesh, 5) { exit(1) }
	mesh.create_normals_with_force(false);
	mesh.optimize_indices_with_cache(32);
	
	// create model geometry
	let mut model_geometry = MeshModel::new();
	if !model_geometry.create_with_mesh_flags(&device, &vertex_pipeline, &mesh, MeshModelFlags::Default | MeshModelFlags::Indices32 | MeshModelFlags::BufferStorage | MeshModelFlags::BufferTracing | MeshModelFlags::BufferAddress) { exit(1) }
	let mut vertex_buffer = model_geometry.vertex_buffer();
	let mut index_buffer = model_geometry.index_buffer();
	
	// create model tracing
	let mut model_tracing = device.create_tracing();
	model_tracing.add_vertex_buffer_with_buffer(model_geometry.num_geometry_vertices(0), vertex_pipeline.attribute_format(0), model_geometry.vertex_buffer_stride(0) as usize, &mut vertex_buffer);
	model_tracing.add_index_buffer_with_buffer(model_geometry.num_indices(), model_geometry.index_format(), &mut index_buffer);
	if !model_tracing.create_with_flags(TracingType::Triangle, TracingFlags::Compact | TracingFlags::FastTrace) { exit(1) }
	
	// create scratch buffer
	let mut scratch_buffer = device.create_buffer_with_flags(BufferFlags::Storage | BufferFlags::Scratch, model_tracing.build_size() + 1024 * 8 as usize);
	if !scratch_buffer.is_valid_ptr() { exit(1) }
	
	// build model tracing
	if !device.build_tracing_with_flags(&mut model_tracing, &mut scratch_buffer, TracingFlags::Compact) { exit(1) }
	device.flush_tracing(&mut model_tracing);
	
	// create instances
	let mut instances: Vec<TracingInstance> = Vec::new();
	for _ in 0 .. num_instances2 {
		instances.push(TracingInstance {
			transform: Matrix4x3f::identity(),
			data: 0, mask: 0xff, flags: 0, offset: 0,
			tracing: model_tracing.this_ptr(),
		});
	}
	
	// create instances buffer
	let mut instances_buffer = device.create_buffer_with_flags(BufferFlags::Storage | BufferFlags::Tracing, 64 * num_instances2 as usize);
	if !instances_buffer.is_valid_ptr() { exit(1) }
	
	// create instance tracing
	let mut instance_tracing = device.create_tracing_with_instances_instancebuffer(num_instances2, &mut instances_buffer);
	if !instance_tracing.is_valid_ptr() { exit(1) }
	
	// tracing surface
	let mut surface = device.create_texture();
	
	// create target
	let mut target = device.create_target_with_window(&mut window);
	if !target.is_valid_ptr() { exit(1) }
	
	// main loop
	window.run({
		let mut window = window.copy_ptr();
		move || -> bool {
		
		// update window
		Window::update();
		
		// render window
		if !window.render() { return false }
		
		// current time
		let time = time::seconds() as f32;
		
		// common parameters
		#[repr(C)]
		#[derive(Default)]
		struct CommonParameters {
			projection: Matrix4x4f,
			imodelview: Matrix4x4f,
			camera: Vector4f,
			light: Vector4f,
		}
		let mut common_parameters = CommonParameters::default();
		common_parameters.camera = &Matrix4x4f::rotate_z(f32::sin(time) * 4.0) * &Vector4f::new(16.0, 0.0, 8.0, 0.0);
		common_parameters.projection = Matrix4x4f::perspective_infinity_reverse(70.0, window.width() as f32 / window.height() as f32, 0.1);
		common_parameters.imodelview = Matrix4x4f::place_to(&Vector3f::new_v4(&common_parameters.camera), &Vector3f::new(0.0, 0.0, -3.0), &Vector3f::new(0.0, 0.0, 1.0));
		common_parameters.light = Vector4f::new(12.0, 0.0, 6.0, 0.0);
		
		// instance parameters
		let mut i: usize = 0;
		for y in -grid_size .. grid_size + 1 {
			for x in -grid_size .. grid_size + 1 {
				let translate = Matrix4x3f::translate(x as f32 * 4.0, y as f32 * 4.0, 4.0);
				let scale = Matrix4x3f::scale_s(f32::sin(time + i as f32) * 0.2 + 0.8);
				let rotate = &Matrix4x3f::rotate_z(time * 32.0) * &Matrix4x3f::rotate_x(90.0);
				instances[i].transform = &translate * &rotate * &scale;
				i += 1;
			}
		}
		
		// build instance tracing
		if !device.set_tracing(&mut instance_tracing, &instances) { return false }
		if !device.build_tracing(&mut instance_tracing, &mut scratch_buffer) { return false }
		device.flush_tracing(&mut instance_tracing);
		
		// create surface
		if !surface.is_created() || surface.width() != window.width() || surface.height() != window.height() {
			window.finish();
			surface = device.create_texture2d_with_width_flags(Format::RGBAu8n, window.width(), window.height(), TextureFlags::Surface);
		}
		
		// trace scene
		{
			let mut compute = device.create_compute();
			
			// dispatch kernel
			compute.set_kernel(&mut kernel);
			compute.set_uniform(0, &common_parameters);
			compute.set_surface_texture(0, &mut surface);
			compute.set_storage_buffer(0, &mut vertex_buffer);
			compute.set_storage_buffer(1, &mut index_buffer);
			compute.set_tracing(0, &mut instance_tracing);
			compute.dispatch(&mut surface);
			compute.barrier(&mut surface);
		}
		
		// flush surface
		device.flush_texture(&mut surface);
		
		// window target
		target.begin();
		{
			let mut command = device.create_command_with_target(&mut target);
			
			// draw surface
			command.set_pipeline(&mut pipeline);
			command.set_texture(0, &mut surface);
			command.draw_arrays(3);
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

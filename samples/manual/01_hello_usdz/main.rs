// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

use std::process::exit;

use tellusim::*;

extern crate tellusim;

/*
 */
fn create_texture(device: &Device, material: &MeshMaterial, name: &str) -> Texture {
	
	// find material parameter
	let index = material.find_parameter(name);
	if index == MAXU32 { return Texture::null() }
	
	// load image
	let mut image = Image::new();
	let blob = material.parameter_blob(index);
	if !image.load_with_stream(&mut blob.to_stream(), None) { return Texture::null() }
	
	// create texture
	device.create_texture_with_image_flags(&image, TextureFlags::Mipmaps)
}

/*
 */
fn main() {
	
	// create app
	let mut app = App::new();
	if !app.create() { exit(1) }
	
	// create window
	let mut window = Window::new_with_platform_index(app.platform(), app.device());
	if !window.is_valid_ptr() || !window.set_size(app.width(), app.height()) { exit(1) }
	if !window.create_with_title(&"01 Hello USDZ Rust") || !window.set_hidden(false) { exit(1) }
	
	window.set_keyboard_pressed_callback({
		let mut window = window.copy_ptr();
		move |key: u32, _code: u32| {
			if key == WindowKey::Esc as u32 { window.stop() }
		}
	});
	
	// create device
	let device = Device::new_with_window(&mut window);
	if !device.is_valid_ptr() { exit(1) }
	
	// create pipeline
	let mut pipeline = device.create_pipeline();
	pipeline.set_sampler_mask(0, ShaderMask::Fragment);
	pipeline.set_texture_masks(0, 3, ShaderMask::Fragment);
	pipeline.set_uniform_masks(0, 2, ShaderMask::Vertex);
	pipeline.add_attribute(PipelineAttribute::Position, Format::RGBf32, 0, 0, 80);
	pipeline.add_attribute(PipelineAttribute::Normal, Format::RGBf32, 0, 12, 80);
	pipeline.add_attribute(PipelineAttribute::Tangent, Format::RGBAf32, 0, 24, 80);
	pipeline.add_attribute(PipelineAttribute::TexCoord, Format::RGf32, 0, 40, 80);
	pipeline.add_attribute(PipelineAttribute::Weights, Format::RGBAf32, 0, 48, 80);
	pipeline.add_attribute(PipelineAttribute::Joints, Format::RGBAu32, 0, 64, 80);
	pipeline.set_color_format(0, window.color_format());
	pipeline.set_depth_format(window.depth_format());
	pipeline.set_depth_func(PipelineDepthFunc::Less);
	if !pipeline.load_shader_glsl(ShaderType::Vertex, "main.shader", "VERTEX_SHADER=1") { exit(1) }
	if !pipeline.load_shader_glsl(ShaderType::Fragment, "main.shader", "FRAGMENT_SHADER=1") { exit(1) }
	if !pipeline.create() { exit(1) }
	
	// load mesh
	let mut mesh = Mesh::new();
	if !mesh.load_with_name("model.usdz", None) { exit(1) }
	if mesh.num_geometries() == 0 { exit(1) }
	if mesh.num_animations() == 0 { exit(1) }
	mesh.set_basis(MeshBasis::ZUpRight);
	mesh.create_tangents();
	
	// create model
	let mut model = MeshModel::new();
	if !model.create_with_mesh(&device, &pipeline, &mesh) { exit(1) }
	
	// create textures
	let mut normal_textures: Vec<Texture> = Vec::new();
	let mut diffuse_textures: Vec<Texture> = Vec::new();
	let mut roughness_textures: Vec<Texture> = Vec::new();
	for i in 0 .. mesh.num_geometries() {
		let geometry = mesh.geometry(i);
		for j in 0 .. geometry.num_materials() {
			let material = geometry.material(j);
			normal_textures.push(create_texture(&device, &material, "normal"));
			diffuse_textures.push(create_texture(&device, &material, "diffuse"));
			roughness_textures.push(create_texture(&device, &material, "roughness"));
		}
	}
	
	// create sampler
	let mut sampler = device.create_sampler_with_filter_mode(SamplerFilter::Trilinear, SamplerWrapMode::Repeat);
	if !sampler.is_valid_ptr() { exit(1) }
	
	// create target
	let mut target = device.create_target_with_window(&mut window);
	target.set_clear_color_with_color(&Color::gray());
	
	// main loop
	window.run({
		let mut window = window.copy_ptr();
		move || -> bool {
		
		Window::update();
		
		if !window.render() { return false }
		
		// window target
		target.begin();
		{
			// create command list
			let mut command = device.create_command_with_target(&mut target);
			
			// set pipeline
			command.set_pipeline(&mut pipeline);
			
			// set sampler
			command.set_sampler(0, &mut sampler);
			
			// set model buffers
			model.set_buffers(&mut command);
			
			// set common parameters
			#[repr(C)]
			#[derive(Default)]
			struct CommonParameters {
				projection: Matrix4x4f,
				modelview: Matrix4x4f,
				camera: Vector4f,
			}
			let mut common_parameters = CommonParameters::default();
			common_parameters.camera = Vector4f::new(0.0, -180.0, 180.0, 0.0);
			common_parameters.projection = Matrix4x4f::perspective(60.0, window.width() as f32 / window.height() as f32, 0.1, 1000.0);
			common_parameters.modelview = Matrix4x4f::look_at(&Vector3f::new_v4(&common_parameters.camera), &Vector3f::new(0.0, 0.0, 80.0), &Vector3f::new(0.0, 0.0, 1.0));
			if target.is_flipped() { common_parameters.projection = &Matrix4x4f::scale(1.0, -1.0, 1.0) * &common_parameters.projection }
			command.set_uniform(0, &common_parameters);
			
			// mesh animation
			let time = time::seconds();
			let mut animation = mesh.animation(0);
			animation.set_time_with_transform(time, &Matrix4x3d::rotate_z(f64::sin(time) * 30.0));
			
			// draw geometries
			let mut texture_index: usize = 0;
			for i in 0 .. mesh.num_geometries() {
				let geometry = mesh.geometry(i);
				
				// joint transforms
				let mut joint_parameters: Vec<Vector4f> = Vec::new();
				for j in 0 .. geometry.num_joints() {
					let joint = geometry.joint(j);
					let transform = Matrix4x3f::new_m4x3d(&animation.global_transform_with_joint(&joint)) * joint.itransform() * geometry.transform();
					joint_parameters.push(transform.row_0);
					joint_parameters.push(transform.row_1);
					joint_parameters.push(transform.row_2);
				}
				command.set_uniform_vec(1, &joint_parameters);
				
				// draw materials
				for j in 0 .. geometry.num_materials() {
					command.set_texture(0, &mut normal_textures[texture_index]);
					command.set_texture(1, &mut diffuse_textures[texture_index]);
					command.set_texture(2, &mut roughness_textures[texture_index]);
					model.draw_with_geometry_material(&mut command, i, j);
					texture_index += 1;
				}
			}
		}
		target.end();
		
		if !window.present() { return false }
		
		if !device.check() { return false }
		
		true
	}});
	
	// finish context
	window.finish();
	
	// done
	log::print("Done\n");
}

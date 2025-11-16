// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

use tellusim::*;
use std::process::exit;

extern crate tellusim;

/*
 */
fn create_mesh(steps: &Vector2u, radius: &Vector2f, texcoord: f32) -> Mesh {
	
	// create mesh
	let mut mesh = Mesh::new();
	
	// create vertices
	let num_vertices = (steps.x + 1) * (steps.y + 1);
	let mut positions = MeshAttribute::new_with_type_size(MeshAttributeType::Position, Format::RGBf32, num_vertices, 0);
	let mut normals = MeshAttribute::new_with_type_size(MeshAttributeType::Normal, Format::RGBf32, num_vertices, 0);
	let mut tangents = MeshAttribute::new_with_type_size(MeshAttributeType::Tangent, Format::RGBAf32, num_vertices, 0);
	let mut texcoords = MeshAttribute::new_with_type_size(MeshAttributeType::TexCoord, Format::RGf32, num_vertices, 0);
	
	let mut vertex: u32 = 0;
	let isteps = Vector2f::new_s(1.0) / Vector2f::new_v2u(steps);
	let aspect = radius.x / radius.y;
	for j in 0 .. steps.y + 1 {
		let ty = j as f32 * isteps.y;
		let z = -f32::cos(ty * PI2 - PI05);
		let r = f32::sin(ty * PI2 - PI05);
		for i in 0 .. steps.x + 1 {
			let tx = i as f32 * isteps.x;
			let x = -f32::sin(tx * PI2);
			let y = f32::cos(tx * PI2);
			positions.set(vertex, Vector3f::new(x * (r * radius.y + radius.x), y * (r * radius.y + radius.x), z * radius.y));
			normals.set(vertex, Vector3f::new(x * r, y * r, z));
			tangents.set(vertex, Vector4f::new(-y, x, 0.0, 1.0));
			texcoords.set(vertex, Vector2f::new(tx * aspect, ty) * texcoord);
			vertex += 1;
		}
	}
	
	let mut basis = MeshAttribute::new_with_type_size(MeshAttributeType::Basis, Format::RGBAu32, num_vertices, 0);
	basis.pack_attributes(&normals, &tangents, Format::RGBAf16);
	
	// create indices
	let num_indices = steps.x * steps.y * 4;
	let indices_format = if num_vertices < MAXU16 { Format::Ru16 } else { Format::Ru32 };
	let mut indices = MeshIndices::new_with_type_size(MeshIndicesType::Quadrilateral, indices_format, num_indices);
	
	let mut index = 0;
	for j in 0 .. steps.y {
		for i in 0 .. steps.x {
			vertex = (steps.x + 1) * j + i;
			indices.set4(index, vertex, vertex + 1, vertex + steps.x + 2, vertex + steps.x + 1);
			index += 4;
		}
	}
	
	// create geometry
	let mut geometry = MeshGeometry::new_with_mesh(&mut mesh);
	geometry.add_attribute_with_indices(&mut positions, &mut indices);
	geometry.add_attribute_with_indices(&mut basis, &mut indices);
	geometry.add_attribute_with_indices(&mut normals, &mut indices);
	geometry.add_attribute_with_indices(&mut texcoords, &mut indices);
	
	// geometry bounds
	let hsize = Vector3f::new_v2(&Vector2f::new_s(radius.x + radius.y), radius.y);
	geometry.set_bound_box(&BoundBoxf::new(&-hsize, &hsize));
	
	// create bounds
	mesh.create_bounds();
	
	mesh
}

/*
 */
fn create_image(size: u32, frame: u32) -> Image {
	
	// create image
	let mut image = Image::new();
	image.create2d_with_size(Format::RGBAu8n, size);
	
	// create sampler
	let mut sampler = ImageSampler::new_with_image_mut(&mut image);
	
	// fill image
	let mut color = ImageColor::new_s(255);
	for y in 0 .. size {
		for x in 0 .. size {
			let v = (((x as i32 - (frame ^ y) as i32) as u32 ^ (y + (frame ^ x))) & 255) as f32 / 63.0;
			color.r = (f32::cos(PI * 1.0 + v) * 127.5 + 127.5) as u32;
			color.g = (f32::cos(PI * 0.5 + v) * 127.5 + 127.5) as u32;
			color.b = (f32::cos(PI * 0.0 + v) * 127.5 + 127.5) as u32;
			sampler.set2d(x, y, &color);
		}
	}
	
	image
}

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
			if key == WindowKey::F12 as u32 {
				let mut image = Image::new();
				if window.grab(&mut image) && image.save("screenshot.png") {
					ts_log!(Message, "Screenshot\n");
				}
			}
		}
	});
	
	let title = window.platform_name() + &" Tellusim::Rust";
	if !window.create_with_title_flags(&title, WindowFlags::Default | WindowFlags::VerticalSync) || !window.set_hidden(false) { exit(1) }
	
	// create device
	let device = Device::new_with_window(&mut window);
	if !device.is_valid_ptr() { exit(1) }
	
	// device features
	ts_logf!(Message, "Features:\n{0}\n", device.features());
	ts_logf!(Message, "Device: {0}\n", device.name());
	
	// build info
	ts_logf!(Message, "Build: {0}\n", App::build_info());
	
	// create target
	let mut target = device.create_target_with_window(&mut window);
	if !target.is_valid_ptr() { exit(1) }
	
	////////////////////////////////
	// core test
	////////////////////////////////
	
	let mut blob = Blob::new();
	blob.write_string_with_str(&title);
	
	blob.seek(0);
	ts_logf!(Message, "Stream: {0}\n", blob.read_string());
	
	////////////////////////////////
	// bounds test
	////////////////////////////////
	
	// 32-bit floating point
	let mut bound_boxf = BoundBoxf::new(&-Vector3f::one(), &Vector3f::one());
	let mut bound_spheref = BoundSpheref::new_bb(&bound_boxf);
	let bound_frustumf = BoundFrustumf::new_pm(&Matrix4x4f::perspective(60.0, 1.0, 0.1, 1000.0), &Matrix4x4f::look_at(&Vector3f::one(), &Vector3f::zero(), &Vector3f::new(0.0, 0.0, 1.0)));
	ts_logf!(Message, "{0} {1} {2} {3}\n", bound_boxf, bound_frustumf.inside_bb(&bound_boxf), bound_spheref, bound_frustumf.inside_bs(&bound_spheref));
	bound_boxf = Matrix4x3f::translate(10.0, 0.0, 0.0) * bound_boxf;
	bound_spheref = Matrix4x4f::translate(10.0, 0.0, 0.0) * bound_spheref;
	ts_logf!(Message, "{0} {1} {2} {3}\n", bound_boxf, bound_frustumf.inside_bb(&bound_boxf), bound_spheref, bound_frustumf.inside_bs(&bound_spheref));
	
	// 64-bit floating point
	let mut bound_boxd = BoundBoxd::new(&-Vector3d::one(), &Vector3d::one());
	let mut bound_sphered = BoundSphered::new_bb(&bound_boxd);
	let bound_frustumd = BoundFrustumd::new_pm(&Matrix4x4d::perspective(60.0, 1.0, 0.1, 1000.0), &Matrix4x4d::look_at(&Vector3d::one(), &Vector3d::zero(), &Vector3d::new(0.0, 0.0, 1.0)));
	ts_logf!(Message, "{0} {1} {2} {3}\n", bound_boxd, bound_frustumd.inside_bb(&bound_boxd), bound_sphered, bound_frustumd.inside_bs(&bound_sphered));
	bound_boxd = Matrix4x3d::translate(10.0, 0.0, 0.0) * bound_boxd;
	bound_sphered = Matrix4x4d::translate(10.0, 0.0, 0.0) * bound_sphered;
	ts_logf!(Message, "{0} {1} {2} {3}\n", bound_boxd, bound_frustumd.inside_bb(&bound_boxd), bound_sphered, bound_frustumd.inside_bs(&bound_sphered));
	
	////////////////////////////////
	// platform test
	////////////////////////////////
	
	// create pipeline
	let mut pipeline = device.create_pipeline();
	pipeline.set_uniform_mask(0, ShaderMask::Fragment);
	pipeline.set_color_format(0, window.color_format());
	pipeline.set_depth_format(window.depth_format());
	pipeline.set_depth_mask(PipelineDepthMask::None);
	pipeline.add_attribute(PipelineAttribute::Position, Format::RGf32, 0, 0, 8);
	if !pipeline.load_shader_glsl(ShaderType::Vertex, "main.shader", "VERTEX_SHADER=1") { exit(1) }
	if !pipeline.load_shader_glsl(ShaderType::Fragment, "main.shader", "FRAGMENT_SHADER=1") { exit(1) }
	if !pipeline.create() { exit(1) }
	
	// geometry vertices
	let vertices: [Vector2f; 3] = [ Vector2f::new(3.0, -1.0), Vector2f::new(-1.0, -1.0), Vector2f::new(-1.0, 3.0) ];
	
	// geometry indices
	let indices: [u16; 3] = [ 0, 1, 2 ];
	
	////////////////////////////////
	// interface test
	////////////////////////////////
	
	// create canvas
	let mut canvas = Canvas::new();
	
	// create root controls
	let mut root = ControlRoot::new_with_canvas_blob(&mut canvas, true);
	root.set_font_size(24);
	
	// create dialog
	let mut dialog = ControlDialog::new_with_parent_columns_x(Some(&root.to_control()), 1, 8.0, 8.0);
	dialog.set_updated_callback(|dialog: ControlDialog| {
		let x = dialog.position_x();
		let y = dialog.position_y();
		let width = dialog.width();
		let height = dialog.height();
		ts_logf!(Message, "Dialog Updated {0} {1} {2}x{3}\n", x, y, width, height);
	});
	dialog.set_align(ControlAlign::Center);
	dialog.set_size_with_width(240.0, 180.0);
	
	// create text
	let mut text = ControlText::new_with_parent_text(Some(&dialog.to_control()), &title);
	text.set_align(ControlAlign::CenterX);
	
	// create button
	let mut button = ControlButton::new_with_parent_text(Some(&dialog.to_control()), "Button");
	button.set_clicked_callback(move |button: ControlButton| {
		ts_logf!(Message, "{0} Clicked\n", button.text());
	});
	button.set_align(ControlAlign::Expand);
	button.set_margin_with_left(0.0, 0.0, 0.0, 16.0);
	
	// common parameters
	#[repr(C)]
	#[derive(Default)]
	struct CommonParameters {
		transform: Matrix4x4f,
		color: Color,
		time: f32,
	}
	let mut parameters = CommonParameters::default();
	parameters.color = Color::new_s(1.0);
	
	// create sliders
	let mut slider_r = ControlSlider::new_with_parent_text_digits_value_min(Some(&dialog.to_control()), "R", 2, parameters.color.r as f64, 0.0, 1.0);
	let mut slider_g = ControlSlider::new_with_parent_text_digits_value_min(Some(&dialog.to_control()), "G", 2, parameters.color.g as f64, 0.0, 1.0);
	let mut slider_b = ControlSlider::new_with_parent_text_digits_value_min(Some(&dialog.to_control()), "B", 2, parameters.color.b as f64, 0.0, 1.0);
	slider_r.set_changed_callback(|slider: ControlSlider| { parameters.color.r = slider.valuef32() });
	slider_g.set_changed_callback(|slider: ControlSlider| { parameters.color.g = slider.valuef32() });
	slider_b.set_changed_callback(|slider: ControlSlider| { parameters.color.b = slider.valuef32() });
	slider_r.set_format_callback(|slider: ControlSlider| { format!("Value: {0}", String::fromf32_with_digits(slider.valuef32(), 2)) });
	slider_g.set_format_callback(|slider: ControlSlider| { format!("Value: {0}", String::fromf32_with_digits(slider.valuef32(), 2)) });
	slider_b.set_format_callback(|slider: ControlSlider| { format!("Value: {0}", String::fromf32_with_digits(slider.valuef32(), 2)) });
	slider_r.set_align(ControlAlign::ExpandX);
	slider_g.set_align(ControlAlign::ExpandX);
	slider_b.set_align(ControlAlign::ExpandX);
	
	////////////////////////////////
	// render test
	////////////////////////////////
	
	// vertex shader
	let vertex_shader = r#"
		layout(location = 0) in vec4 in_position;
		layout(location = 1) in vec3 in_normal;
		layout(location = 2) in vec2 in_texcoord;
		layout(row_major, binding = 0) uniform CommonParameters {
			mat4 projection;
			mat4 modelview;
			mat4 transform;
			vec4 camera;
		};
		layout(location = 0) out vec3 s_direction;
		layout(location = 1) out vec3 s_normal;
		layout(location = 2) out vec2 s_texcoord;
		void main() {
			vec4 position = transform * in_position;
			gl_Position = projection * (modelview * position);
			s_direction = camera.xyz - position.xyz;
			s_normal = (transform * vec4(in_normal, 0.0f)).xyz;
			s_texcoord = in_texcoord;
		}
	"#;
	
	// fragment shader
	let fragment_shader = r#"
		layout(binding = 0, set = 1) uniform texture2D in_texture;
		layout(binding = 0, set = 2) uniform sampler in_sampler;
		layout(location = 0) in vec3 s_direction;
		layout(location = 1) in vec3 s_normal;
		layout(location = 2) in vec2 s_texcoord;
		layout(location = 0) out vec4 out_color;
		void main() {
			vec3 direction = normalize(s_direction);
			vec3 normal = normalize(s_normal);
			float diffuse = clamp(dot(direction, normal), 0.0f, 1.0f);
			float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0f, 1.0f), 16.0f);
			out_color = texture(sampler2D(in_texture, in_sampler), s_texcoord) * diffuse + specular;
		}
	"#;
	
	// create render pipeline
	let mut render_pipeline = device.create_pipeline();
	render_pipeline.set_uniform_mask(0, ShaderMask::Vertex);
	render_pipeline.set_texture_mask(0, ShaderMask::Fragment);
	render_pipeline.set_sampler_mask(0, ShaderMask::Fragment);
	render_pipeline.set_color_format(0, window.color_format());
	render_pipeline.set_depth_format(window.depth_format());
	render_pipeline.set_depth_func(PipelineDepthFunc::LessEqual);
	render_pipeline.add_attribute(PipelineAttribute::Position, Format::RGBf32, 0, 0, 32);
	render_pipeline.add_attribute(PipelineAttribute::Normal, Format::RGBf32, 0, 12, 32);
	render_pipeline.add_attribute(PipelineAttribute::TexCoord, Format::RGf32, 0, 24, 32);
	if !render_pipeline.create_shader_glsl(ShaderType::Vertex, vertex_shader, "") { exit(1) }
	if !render_pipeline.create_shader_glsl(ShaderType::Fragment, fragment_shader, "") { exit(1) }
	if !render_pipeline.create() { exit(1) }
	
	// create mesh
	let mesh = create_mesh(&Vector2u::new(64, 32), &Vector2f::new(8.0, 2.0), 2.0);
	
	// create model
	let mut model = MeshModel::new();
	if !model.create_with_mesh(&device, &render_pipeline, &mesh) { exit(1) }
	
	// create sampler
	let mut sampler = device.create_sampler_with_filter_mode(SamplerFilter::Linear, SamplerWrapMode::Repeat);
	if !sampler.is_valid_ptr() { exit(1) }
	
	// create texture
	let texture_image = create_image(256, 0);
	let mut texture = device.create_texture_with_image(&texture_image);
	if !texture.is_valid_ptr() { exit(1) }
	
	////////////////////////////////
	// main loop
	////////////////////////////////
	
	let mut texture_frame = 0;
	let texture_ifps = 1.0 / 30.0;
	let mut texture_time = time::seconds();
	
	// main loop
	window.run({
		let device = device.copy_ptr();
		let mut window = window.copy_ptr();
		let parameters = &mut parameters;
		move || -> bool {
		
		// update window
		Window::update();
		
		// render window
		if !window.render() { return false }
		
		// update texture
		if time::seconds() - texture_time > texture_ifps {
			texture_time += texture_ifps;
			let image = create_image(256, texture_frame);
			device.set_texture_with_image(&mut texture, &image);
			texture_frame += 1;
		}
		
		// update interface
		{
			// window size
			let height = app.height() as f32;
			let width = (height * window.width() as f32 / window.height() as f32).floor();
			let mouse_x = width * window.mouse_x() as f32 / window.width() as f32;
			let mouse_y = height * window.mouse_y() as f32 / window.height() as f32;
			
			// mouse button
			let mut buttons = ControlButtons::None;
			if window.mouse_buttons().has_flag(WindowButton::Left | WindowButton::Left2) { buttons |= ControlButtons::Left }
			
			// update controls
			root.set_viewportf32(width, height);
			root.set_mousef32(mouse_x, mouse_y, buttons);
			while root.update_with_scale(canvas.scale(&target)) { }
			
			// create canvas
			canvas.create(&device, &target);
		}
		
		// window target
		target.begin();
		{
			let mut command = device.create_command_with_target(&mut target);
			
			// current time
			let time = time::seconds() as f32;
			
			// common parameters
			parameters.transform = Matrix4x4f::rotate_z(time * 16.0);
			parameters.time = time;
			
			// draw background
			command.set_pipeline(&mut pipeline);
			command.set_uniform(0, parameters);
			command.set_vertices(0, &vertices);
			command.set_indices(&indices);
			command.draw_elements(3);
			
			// render parameters
			#[repr(C)]
			#[derive(Default)]
			struct RenderParameters {
				projection: Matrix4x4f,
				modelview: Matrix4x4f,
				transform: Matrix4x4f,
				camera: Vector3f,
			}
			let mut render_parameters = RenderParameters::default();
			render_parameters.camera = Vector3f::new(12.0, 12.0, 6.0);
			render_parameters.projection = Matrix4x4f::perspective(60.0, window.width() as f32 / window.height() as f32, 0.1, 1000.0);
			render_parameters.modelview = Matrix4x4f::look_at(&render_parameters.camera, &Vector3f::zero(), &Vector3f::new(0.0, 0.0, 1.0));
			render_parameters.transform = Matrix4x4f::rotate_z(time * 24.0) * Matrix4x4f::rotate_x(time * 16.0);
			
			// draw mesh
			command.set_pipeline(&mut render_pipeline);
			command.set_uniform(0, &render_parameters);
			command.set_sampler(0, &mut sampler);
			command.set_texture(0, &mut texture);
			model.set_buffers(&mut command);
			model.draw(&mut command);
			
			// draw canvas
			canvas.draw_with_target(&mut command, &mut target);
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
	ts_log!(Message, "Done\n");
}

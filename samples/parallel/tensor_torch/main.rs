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
	
	// create window
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
	
	let title = window.platform_name() + &" Tellusim::TensorTorch Rust";
	if !window.create_with_title(&title) || !window.set_hidden(false) { exit(1) }
	
	// create device
	let device = Device::new_with_window(&mut window);
	if !device.is_valid_ptr() { exit(1) }
	
	// check compute tracing support
	if !device.has_shader(ShaderType::Compute) {
		ts_logf!(Error, "compute shader is not supported\n");
		exit(1)
	}
	
	// shader cache
	Shader::set_cache("main.cache");
	
	// create pipeline
	let mut pipeline = device.create_pipeline();
	pipeline.set_sampler_mask(0, ShaderMask::Fragment);
	pipeline.set_texture_mask(0, ShaderMask::Fragment);
	pipeline.set_color_format(0, window.color_format());
	pipeline.set_depth_format(window.depth_format());
	if !pipeline.load_shader_glsl(ShaderType::Vertex, "main.shader", "VERTEX_SHADER=1") { exit(1) }
	if !pipeline.load_shader_glsl(ShaderType::Fragment, "main.shader", "FRAGMENT_SHADER=1") { exit(1) }
	if !pipeline.create() { exit(1) }
	
	// create kernel
	let mut kernel = device.create_kernel().set_uniforms(1).set_storages(1);
	if !kernel.load_shader_glsl("main.shader", "COMPUTE_SHADER=1") { exit(1) }
	if !kernel.create() { exit(1) }
	
	// create sampler
	let mut sampler = device.create_sampler_with_filter_mode(SamplerFilter::Linear, SamplerWrapMode::Clamp);
	if !sampler.is_valid_ptr() { exit(1) }
	
	// create texture
	let mut texture = device.load_texture("texture.jpg");
	if !texture.is_valid_ptr() { exit(1) }
	
	// create surface
	let mut surface = device.create_texture2d_with_width_flags(Format::RGBAu8n, texture.width(), texture.height(), TextureFlags::Surface);
	if !surface.is_valid_ptr() { exit(1) }
	
	// create tensor graph
	let mut tensor_graph = TensorGraph::new();
	if !tensor_graph.create_with_flags(&device, TensorGraphFlags::All & !TensorGraphFlags::FormatRf16) { exit(1) }
	
	// model tensors
	let mut tensors: Vec<Tensor> = Vec::new();
	
	// load model
	let mut source = Source::new();
	if !source.open("model.bin") { exit(1) }
	while source.is_available() {
		let size = source.readu8();
		if size == 0xff { break }
		let mut tensor = Tensor::new();
		if size > 3 { tensor.layers = source.readu16() as u32 }
		if size > 2 { tensor.depth = source.readu16() as u32 }
		if size > 1 { tensor.height = source.readu16() as u32 }
		if size > 0 { tensor.width = source.readu16() as u32 }
		tensor.offset = (source.readu32() * 4) as usize;
		let name = source.read_string_with_term(0);
		ts_logf!(Message, "{}: {} [{}x{}x{}x{}]\n", tensors.len(), name, tensor.width, tensor.height, tensor.depth, tensor.layers);
		tensors.push(tensor);
	}
	
	// load weights
	let size = source.readu32();
	let mut weights: Vec<f32> = Vec::new();
	for _i in 0..size { weights.push(source.readf32()) }
	let weights_buffer = device.create_buffer_with_flags_vec(BufferFlags::Storage, &weights);
	if !weights_buffer.is_valid_ptr() { exit(1) }
	
	// tensor buffer
	for tensor in &mut tensors {
		tensor.buffer = weights_buffer.this_ptr();
		tensor.format = Format::Rf32;
	}
	
	// create texture tensor
	let size: u32 = 64;
	let width = udivu32(texture.width(), size);
	let height = udivu32(texture.height(), size);
	let layers = width * height;
	let mut texture_buffer = device.create_buffer_with_flags(BufferFlags::Storage, (size * size * 3 * layers * 4) as usize);
	let mut texture_tensor = Tensor::new_with_size(&texture_buffer, Format::Rf32, size, size, 3, layers);
	if !texture_buffer.is_valid_ptr() { exit(1) }
	
	// create temporary buffers
	let mut tensor_0_buffer = device.create_buffer_with_flags(BufferFlags::Storage, texture_buffer.size());
	let tensor_1_buffer = device.create_buffer_with_flags(BufferFlags::Storage, texture_buffer.size());
	if !tensor_0_buffer.is_valid_ptr() || !tensor_1_buffer.is_valid_ptr() { exit(1) }
	
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
		
		{
			// create command list
			let mut compute = device.create_compute();
			
			// copy texture to tensor
			tensor_graph.dispatch_with_destct(&mut compute, &texture_tensor, &mut texture);
			
			// first convolution
			let mut tensor_0 = Tensor::new_with_buffer(&tensor_0_buffer);
			tensor_graph.dispatch_with_op_dest_mut_src1_flags(&mut compute, TensorGraphOperation::Conv, &mut tensor_0, &texture_tensor.set_stride(3).set_padding(2), &tensors[0], TensorGraphFlags::SiLU);
			
			// first batch normalization
			let mut tensor_1 = Tensor::new_with_buffer(&tensor_1_buffer);
			tensor_graph.dispatch_with_op_dest_mut_src1_src2(&mut compute, TensorGraphOperation::BatchMad, &mut tensor_1, &tensor_0, &tensors[1], &tensors[2]);
			
			// second convolution
			let mut tensor_2 = Tensor::new_with_buffer(&tensor_0_buffer);
			tensor_graph.dispatch_with_op_dest_mut_src1_flags(&mut compute, TensorGraphOperation::Conv, &mut tensor_2, &tensor_1.set_stride(2).set_padding(2), &tensors[5], TensorGraphFlags::SiLU);
			
			// second batch normalization
			let mut tensor_3 = Tensor::new_with_buffer(&tensor_1_buffer);
			tensor_graph.dispatch_with_op_dest_mut_src1_src2(&mut compute, TensorGraphOperation::BatchMad, &mut tensor_3, &tensor_2, &tensors[6], &tensors[7]);
			
			// third convolution
			let mut tensor_4 = Tensor::new_with_buffer(&tensor_0_buffer);
			tensor_graph.dispatch_with_op_dest_mut_src1_flags(&mut compute, TensorGraphOperation::Conv, &mut tensor_4, &tensor_3.set_stride(2).set_padding(1), &tensors[10], TensorGraphFlags::SiLU);
			
			// third batch normalization
			let mut tensor_5 = Tensor::new_with_buffer(&tensor_1_buffer);
			tensor_graph.dispatch_with_op_dest_mut_src1_src2(&mut compute, TensorGraphOperation::BatchMad, &mut tensor_5, &tensor_4, &tensors[11], &tensors[12]);
			
			// fourth convolution
			let mut tensor_6 = Tensor::new_with_buffer(&tensor_0_buffer);
			tensor_graph.dispatch_with_op_dest_mut_src1_flags(&mut compute, TensorGraphOperation::Conv, &mut tensor_6, &tensor_5.set_padding(1), &tensors[15], TensorGraphFlags::SiLU);
			
			// quantize tensor
			compute.set_kernel(&mut kernel);
			compute.set_uniform(0, &Vector4u::new(tensor_6.width, tensor_6.height, tensor_6.depth, tensor_6.layers));
			compute.set_storage_buffer(0, &mut tensor_0_buffer);
			compute.dispatch_with_width_height_depth(tensor_6.width, tensor_6.height, tensor_6.depth * layers);
			compute.barrier_with_buffer(&mut tensor_0_buffer);
			
			// first deconvolution
			let mut tensor_7 = Tensor::new_with_buffer(&tensor_1_buffer);
			tensor_graph.dispatch_with_op_dest_mut_src1_flags(&mut compute, TensorGraphOperation::DeConv, &mut tensor_7, &tensor_6.set_padding(1), &tensors[16], TensorGraphFlags::SiLU);
			
			// second deconvolution
			let mut tensor_8 = Tensor::new_with_buffer(&tensor_0_buffer);
			tensor_graph.dispatch_with_op_dest_mut_src1_flags(&mut compute, TensorGraphOperation::DeConv, &mut tensor_8, &tensor_7.set_stride(2).set_padding(1), &tensors[17], TensorGraphFlags::SiLU);
			
			// third deconvolution
			let mut tensor_9 = Tensor::new_with_buffer(&tensor_1_buffer);
			tensor_graph.dispatch_with_op_dest_mut_src1_flags(&mut compute, TensorGraphOperation::DeConv, &mut tensor_9, &tensor_8.set_stride(2).set_padding(1), &tensors[18], TensorGraphFlags::SiLU);
			
			// fourth deconvolution
			texture_tensor.padding = 1;
			tensor_graph.dispatch_with_op_dest_mut_src1_flags(&mut compute, TensorGraphOperation::DeConv, &mut texture_tensor, &tensor_9.set_stride(3).set_padding(1), &tensors[19], TensorGraphFlags::Sigm);
			
			// copy tensor to texture
			tensor_graph.dispatch_with_destt(&mut compute, &mut surface, &texture_tensor);
		}
		
		// flush surface
		device.flush_texture(&mut surface);
		
		// window target
		target.begin();
		{
			let mut command = device.create_command_with_target(&mut target);
			
			// draw surface
			command.set_pipeline(&mut pipeline);
			command.set_sampler(0, &mut sampler);
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

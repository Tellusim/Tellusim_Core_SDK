// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <core/TellusimAsync.h>
#include <core/TellusimSource.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimCommand.h>
#include <platform/TellusimCompute.h>
#include <parallel/TellusimTensorGraph.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::TensorTorch", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check compute shader support
	if(!device.hasShader(Shader::TypeCompute)) {
		TS_LOG(Error, "compute shader is not supported\n");
		return 0;
	}
	
	// shader cache
	Shader::setCache("main.cache");
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setSamplerMask(0, Shader::MaskFragment);
	pipeline.setTextureMask(0, Shader::MaskFragment);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create kernel
	Kernel kernel = device.createKernel().setUniforms(1).setStorages(1);
	if(!kernel.loadShaderGLSL("main.shader", "COMPUTE_SHADER=1")) return 1;
	if(!kernel.create()) return 1;
	
	// create sampler
	Sampler sampler = device.createSampler(Sampler::FilterLinear, Sampler::WrapModeClamp);
	if(!sampler) return 1;
	
	// create texture
	Texture texture = device.loadTexture("texture.jpg");
	if(!texture) return 1;
	
	// create surface
	Texture surface = device.createTexture2D(FormatRGBAu8n, texture.getWidth(), texture.getHeight(), Texture::FlagSurface);
	if(!surface) return 1;
	
	// create async
	Async async;
	if(device.getFeatures().threadAccess && !async.init()) return 1;
	
	// create tensor graph
	TensorGraph tensor_graph;
	if(!tensor_graph.create(device, TensorGraph::FlagsAll & ~TensorGraph::FlagFormatRf16, TensorGraph::MasksAll, &async)) return 1;
	
	// model tensors
	Array<Tensor> tensors;
	
	// load model
	Source source;
	if(!source.open("model.bin")) return 1;
	while(source.isAvailable()) {
		uint32_t size = source.readu8();
		if(size == 0xff) break;
		Tensor &tensor = tensors.append();
		if(size > 3) tensor.layers = source.readu16();
		if(size > 2) tensor.depth = source.readu16();
		if(size > 1) tensor.height = source.readu16();
		if(size > 0) tensor.width = source.readu16();
		tensor.offset = sizeof(float32_t) * source.readu32();
		String name = source.readString('\0');
		TS_LOGF(Message, "%u: %s [%ux%ux%ux%u]\n", tensors.size() - 1, name.get(), tensor.width, tensor.height, tensor.depth, tensor.layers);
	}
	
	// model weights
	Array<float32_t> weights(source.readu32());
	if(source.read(weights.get(), weights.bytes()) != weights.bytes()) return 1;
	Buffer weights_buffer = device.createBuffer(Buffer::FlagStorage, weights.get(), weights.bytes());
	if(!weights_buffer) return 1;
	
	// tensor buffer
	for(Tensor &tensor : tensors) {
		tensor.buffer = &weights_buffer;
		tensor.format = FormatRf32;
	}
	
	// create texture tensor
	constexpr uint32_t size = 64;
	uint32_t width = udiv(texture.getWidth(), size);
	uint32_t height = udiv(texture.getHeight(), size);
	uint32_t layers = width * height;
	Buffer texture_buffer = device.createBuffer(Buffer::FlagStorage, sizeof(float32_t) * size * size * 3 * layers);
	Tensor texture_tensor = Tensor(&texture_buffer, FormatRf32, size, size, 3, layers);
	if(!texture_buffer) return 1;
	
	// create temporary buffers
	Buffer tensor_0_buffer = device.createBuffer(Buffer::FlagStorage, texture_buffer.getSize());
	Buffer tensor_1_buffer = device.createBuffer(Buffer::FlagStorage, texture_buffer.getSize());
	if(!tensor_0_buffer || !tensor_1_buffer) return 1;
	
	// create target
	Target target = device.createTarget(window);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// FPS counter
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		{
			// create command list
			Compute compute = device.createCompute();
			
			// copy texture to tensor
			tensor_graph.dispatch(compute, texture_tensor, texture);
			
			// first convolution
			Tensor tensor_0(&tensor_0_buffer);
			tensor_graph.dispatch(compute, TensorGraph::Conv, tensor_0, texture_tensor.setStride(3).setPadding(2), tensors[0], TensorGraph::FlagSiLU);
			
			// first batch normalization
			Tensor tensor_1(&tensor_1_buffer);
			tensor_graph.dispatch(compute, TensorGraph::BatchMad, tensor_1, tensor_0, tensors[1], tensors[2]);
			
			// second convolution
			Tensor tensor_2(&tensor_0_buffer);
			tensor_graph.dispatch(compute, TensorGraph::Conv, tensor_2, tensor_1.setStride(2).setPadding(2), tensors[5], TensorGraph::FlagSiLU);
			
			// second batch normalization
			Tensor tensor_3(&tensor_1_buffer);
			tensor_graph.dispatch(compute, TensorGraph::BatchMad, tensor_3, tensor_2, tensors[6], tensors[7]);
			
			// third convolution
			Tensor tensor_4(&tensor_0_buffer);
			tensor_graph.dispatch(compute, TensorGraph::Conv, tensor_4, tensor_3.setStride(2).setPadding(1), tensors[10], TensorGraph::FlagSiLU);
			
			// third batch normalization
			Tensor tensor_5(&tensor_1_buffer);
			tensor_graph.dispatch(compute, TensorGraph::BatchMad, tensor_5, tensor_4, tensors[11], tensors[12]);
			
			// fourth convolution
			Tensor tensor_6(&tensor_0_buffer);
			tensor_graph.dispatch(compute, TensorGraph::Conv, tensor_6, tensor_5.setStride(1).setPadding(1), tensors[15], TensorGraph::FlagSiLU);
			
			// quantize tensor
			compute.setKernel(kernel);
			compute.setUniform(0, tensor_6.size);
			compute.setStorageBuffer(0, *tensor_6.buffer);
			compute.dispatch(tensor_6.width, tensor_6.height, tensor_6.depth * layers);
			compute.barrier(tensor_0_buffer);
			
			// first deconvolution
			Tensor tensor_7(&tensor_1_buffer);
			tensor_graph.dispatch(compute, TensorGraph::DeConv, tensor_7, tensor_6.setStride(1).setPadding(1), tensors[16], TensorGraph::FlagSiLU);
			
			// second deconvolution
			Tensor tensor_8(&tensor_0_buffer);
			tensor_graph.dispatch(compute, TensorGraph::DeConv, tensor_8, tensor_7.setStride(2).setPadding(1), tensors[17], TensorGraph::FlagSiLU);
			
			// third deconvolution
			Tensor tensor_9(&tensor_1_buffer);
			tensor_graph.dispatch(compute, TensorGraph::DeConv, tensor_9, tensor_8.setStride(2).setPadding(1), tensors[18], TensorGraph::FlagSiLU);
			
			// fourth deconvolution
			texture_tensor.padding = 1;
			tensor_graph.dispatch(compute, TensorGraph::DeConv, texture_tensor, tensor_9.setStride(3).setPadding(1), tensors[19], TensorGraph::FlagSigm);
			
			// copy tensor to texture
			tensor_graph.dispatch(compute, surface, texture_tensor);
		}
		
		// flush texture
		device.flushTexture(surface);
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// draw surface
			command.setPipeline(pipeline);
			command.setSampler(0, sampler);
			command.setTexture(0, surface);
			command.drawArrays(3);
		}
		target.end();
		
		if(!window.present()) return false;
		
		// check errors
		device.check();
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}

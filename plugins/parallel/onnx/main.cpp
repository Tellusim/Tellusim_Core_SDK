// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <format/TellusimXml.h>
#include <core/TellusimAsync.h>
#include <core/TellusimSource.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>
#include <platform/TellusimCompute.h>

#include "include/TellusimONNX.h"

/*
 */
#define DATA_PATH	"data/"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::TensorONNX", window.getPlatformName());
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
	pipeline.setTextureMasks(0, 2, Shader::MaskFragment);
	pipeline.setStorageMask(0, Shader::MaskFragment);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, DATA_PATH "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, DATA_PATH "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create sampler
	Sampler sampler = device.createSampler(Sampler::FilterLinear, Sampler::WrapModeClamp);
	if(!sampler) return 1;
	
	// create textures
	Texture texture = device.loadTexture("data/texture.png");
	Texture numbers = device.loadTexture("data/numbers.png");
	if(!texture || !numbers) return 1;
	
	// create async
	Async async;
	if(device.getFeatures().threadAccess && !async.init()) return 1;
	
	// create tensor graph
	TensorGraph tensor_graph;
	if(!tensor_graph.create(device, TensorGraph::FlagsAll & ~TensorGraph::FlagFormatRf16, TensorGraph::MasksAll, &async)) return 1;
	
	// load model
	TensorONNX tensor_onnx;
	if(!tensor_onnx.load(device, DATA_PATH "model.onnx", TensorONNX::FlagQuery)) return 1;
	
	if(0) {
		
		// save model
		Xml root = Xml("onnx");
		tensor_onnx.save(root);
		root.save("model.xml");
	}
	
	// create input tensor
	constexpr uint32_t size = 28;
	uint32_t width = udiv(texture.getWidth(), size);
	uint32_t height = udiv(texture.getHeight(), size);
	uint32_t layers = width * height;
	Buffer input_buffer = device.createBuffer(Buffer::FlagStorage, sizeof(float32_t) * size * size * layers);
	Tensor input_tensor = Tensor(&input_buffer, FormatRf32, size, size, 1, layers);
	if(!input_buffer) return 1;
	
	// create output buffer
	Buffer output_buffer = device.createBuffer(Buffer::FlagStorage, sizeof(float32_t) * 10 * layers);
	if(!output_buffer) return 1;
	
	// create temporary buffer
	Buffer tensor_buffer = device.createBuffer(Buffer::FlagStorage, 1024 * 1024 * 16);
	if(!tensor_buffer) return 1;
	
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
		
		// print statistics
		if(window.getKeyboardKey('q', true)) {
			Log::printf("\n%s\n", tensor_onnx.getStatistics().get());
		}
		
		{
			// create command list
			Compute compute = device.createCompute();
			
			// copy texture to tensor
			tensor_graph.dispatch(compute, input_tensor, texture);
			
			// dispatch model
			Tensor output_tensor(&output_buffer);
			if(!tensor_onnx.dispatch(tensor_graph, compute, output_tensor, input_tensor, tensor_buffer, TensorONNX::FlagQuery)) return false;
		}
		
		// flush buffer
		device.flushBuffer(output_buffer);
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// draw surface
			command.setPipeline(pipeline);
			command.setSampler(0, sampler);
			command.setTextures(0, { texture, numbers });
			command.setStorageBuffer(0, output_buffer);
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

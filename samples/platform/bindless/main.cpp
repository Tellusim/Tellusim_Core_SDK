// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimMath.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCompute.h>
#include <platform/TellusimCommand.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	using Tellusim::sin;
	using Tellusim::cos;
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Bindless", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// number of objects
	constexpr uint32_t width = 64;
	constexpr uint32_t height = 64;
	constexpr uint32_t num_instances = width * height;
	
	// structures
	struct ComputeParameters {
		uint32_t num_vertices;
		uint32_t width;
		uint32_t height;
		float32_t time;
	};
	
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Vector4f camera;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check table support
	if(!device.getFeatures().textureTable) {
		TS_LOG(Error, "texture table is not supported\n");
		return 0;
	}
	if(!device.getFeatures().bufferTable) {
		TS_LOG(Error, "buffer table is not supported\n");
		return 0;
	}
	
	// create kernel
	Kernel kernel = device.createKernel().setUniforms(1).setStorages(1).setTableType(0, TableTypeStorage, num_instances);
	if(!kernel.loadShaderGLSL("main.shader", "COMPUTE_SHADER=1")) return 1;
	if(!kernel.create()) return 1;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setSamplerMask(0, Shader::MaskFragment);
	pipeline.setTextureMask(0, Shader::MaskFragment);
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.setStorageMask(0, Shader::MaskVertex);
	pipeline.setTableType(0, TableTypeTexture, num_instances, Shader::MaskFragment);
	pipeline.setTableType(1, TableTypeStorage, num_instances, Shader::MaskVertex, BindFlagRead);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create sampler
	Sampler sampler = device.createSampler(Sampler::FilterLinear, Sampler::WrapModeClamp);
	if(!sampler) return 1;
	
	// create texture
	Image image;
	image.create2D(FormatRGBAu8n, 16);
	ImageSampler image_sampler(image);
	image_sampler.clear(ImageColor(255u));
	Texture texture = device.createTexture(image);
	if(!texture) return 1;
	
	// object geometry
	#include "main_icosa.h"
	
	// create resources
	Array<Texture> textures;
	Array<Buffer> buffers;
	float32_t center_x = width * 0.5f - 0.5f;
	float32_t center_y = height * 0.5f - 0.5f;
	for(uint32_t y = 0, i = 0; y < height; y++) {
		for(uint32_t x = 0; x < width; x++, i++) {
			
			// create image
			ImageSampler image_sampler(image);
			float32_t k = length(Vector2f(x - center_x, y - center_y)) * 0.03f;
			uint32_t r = (uint32_t)(127.0f + 127.0f * sin(7.0f * k));
			uint32_t g = (uint32_t)(127.0f + 127.0f * cos(11.0f * k));
			uint32_t b = (uint32_t)(127.0f + 127.0f * sin(17.0f * k));
			image_sampler.clear(ImageColor(r, g, b, 255u));
			
			// create texture
			textures.append(device.createTexture(image));
			if(!textures.back()) return 1;
			
			// create buffer
			buffers.append(device.createBuffer(Buffer::FlagStorage, sizeof(icosa_vertices)));
			if(!buffers.back()) return 1;
		}
	}
	
	// create texture table
	TextureTable texture_table = device.createTextureTable(textures);
	if(!texture_table) return 1;
	
	// create buffer table
	BufferTable buffer_table = device.createBufferTable(buffers);
	if(!buffer_table) return 1;
	
	// create vertices buffer
	Buffer vertex_buffer = device.createBuffer(Buffer::FlagStorage, icosa_vertices, sizeof(icosa_vertices));
	if(!vertex_buffer) return 1;
	
	// create indices buffer
	uint32_t num_indices = num_icosa_indices;
	Buffer index_buffer = device.createBuffer(Buffer::FlagIndex, icosa_indices, sizeof(icosa_indices));
	if(!index_buffer) return 1;
	
	// create target
	Target target = device.createTarget(window);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// FPS counter
		if(fps > 0.0f) window.setTitle(String::format("%s FPS: %.1f", title.get(), fps).get());
		
		// transform vertices
		{
			// create command list
			Compute compute = device.createCompute();
			
			// set kernel
			compute.setKernel(kernel);
			compute.setStorageBuffer(0, vertex_buffer);
			compute.setStorageTable(0, buffer_table);
			
			// set common parameters
			ComputeParameters compute_parameters;
			compute_parameters.num_vertices = num_icosa_vertices / 8;
			compute_parameters.width = width;
			compute_parameters.height = height;
			compute_parameters.time = time;
			compute.setUniform(0, compute_parameters);
			
			// dispatch kernel
			compute.dispatch(compute_parameters.num_vertices, num_instances);
		}
		
		// window target
		target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// set pipeline
			command.setPipeline(pipeline);
			command.setSampler(0, sampler);
			command.setTexture(0, texture);
			command.setTextureTable(0, texture_table);
			command.setStorageBuffer(0, vertex_buffer);
			command.setStorageTable(1, buffer_table);
			command.setIndexBuffer(FormatRu32, index_buffer);
			
			// set common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Vector4f(cos(time / 8.0f) * 16.0f, sin(time / 8.0f) * 16.0f, 16.0f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			command.setUniform(0, common_parameters);
			
			// draw instances
			command.drawElementsInstanced(num_indices, 0, num_instances);
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

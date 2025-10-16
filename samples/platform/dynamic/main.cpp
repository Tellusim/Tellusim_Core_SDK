// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimMath.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Dynamic", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// number of objects
	#if _ANDROID || _IOS || _EMSCRIPTEN
		constexpr int32_t width = 64;
		constexpr int32_t height = 32;
	#else
		constexpr int32_t width = 128;
		constexpr int32_t height = 64;
	#endif
	constexpr float32_t scale = 0.9f;
	constexpr float32_t radius = 0.5f;
	constexpr uint32_t num_vertices = 32 + 1;
	constexpr uint32_t num_indices = (num_vertices - 1) * 3;
	constexpr uint32_t num_instances = (width * 2 + 1) * (height * 2 + 1);
	constexpr uint32_t num_triangles = num_instances * (num_vertices - 1);
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Matrix4x4f transform;
	};
	
	struct Vertex {
		float32_t position[3];
		float32_t color[3];
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, offsetof(Vertex, position), sizeof(Vertex));
	pipeline.addAttribute(Pipeline::AttributeColor, FormatRGBf32, 0, offsetof(Vertex, color), sizeof(Vertex));
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create buffers
	Array<Vertex> vertex_data(num_vertices);
	Array<uint32_t> index_data(num_indices);
	
	// create target
	Target target = device.createTarget(window);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		using Tellusim::sin;
		using Tellusim::cos;
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS %.1fM", title.get(), fps, num_triangles * fps / 1e6f));
		
		// window target
		target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// set pipeline
			command.setPipeline(pipeline);
			
			// common parameters
			CommonParameters common_parameters;
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(0.0f, -24.0f, 32.0f), Vector3f(0.0f, -8.0f, 0.0f), Vector3f::oneZ);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			
			command.setUniform(0, common_parameters);
			
			// draw objects
			for(int32_t y = -height; y <= height; y++) {
				float32_t Y = cos(time * 2.0f + y * 16.0f);
				
				for(int32_t x = -width; x <= width; x++) {
					float32_t X = time * 3.0f + x * 8.0f;
					
					// set common parameters
					common_parameters.transform = Matrix4x4f::translate(x * scale, y * scale, 0.0f);
					command.setUniform(0, common_parameters);
					
					// update object
					if(((x + width) & 0x07) == 0 && ((y + height) & 0x03) == 0) {
						Vertex *vertex = vertex_data.get();
						uint32_t *index = index_data.get();
						vertex->position[0] = 0.0f;
						vertex->position[1] = 0.0f;
						vertex->position[2] = 0.0f;
						vertex->color[0] = 0.0f;
						vertex->color[1] = 0.0f;
						vertex->color[2] = 0.0f;
						vertex++;
						for(uint32_t i = 1; i < num_vertices; i++) {
							float32_t k = Pi2 * (i - 1) / (num_vertices - 2);
							float32_t r = radius * (2.0f + sin(k * 7.0f + X) * Y) * 0.3f;
							vertex->position[0] = k;
							vertex->position[1] = r;
							vertex->position[2] = r;
							vertex->color[0] = k + time;
							vertex->color[1] = 2.0f;
							vertex->color[2] = 1.0f;
							vertex++;
							*index++ = 0;
							*index++ = i - 1;
							*index++ = i;
						}
					}
					
					// draw object
					command.setVertexData(0, vertex_data.get(), vertex_data.bytes());
					command.setIndexData(FormatRu32, index_data.get(), index_data.bytes());
					command.drawElements(num_indices);
				}
			}
		}
		target.end();
		
		if(!window.present()) return false;
		
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}

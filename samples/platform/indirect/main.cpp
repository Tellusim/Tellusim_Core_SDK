// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimMath.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>

/*
 */
#define BATCH_INDEX		1

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Indirect", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// number of instances
	constexpr uint32_t num_draws = 256;
	constexpr uint32_t num_instances = 4;
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Vector4f camera;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// device features
	bool has_base_index = device.getFeatures().baseInstanceIndex;
	bool has_draw_index = device.getFeatures().drawIndirectIndex;
	bool has_draw_count = device.getFeatures().drawIndirectCount;
	
	// shader macros
	Shader::setMacro("NUM_DRAWS", num_draws);
	Shader::setMacro("NUM_INSTANCES", num_instances);
	Shader::setMacro("HAS_BASE_INDEX", (int32_t)has_base_index);
	Shader::setMacro("HAS_DRAW_INDEX", (int32_t)has_draw_index);
	Shader::setMacro("BATCH_INDEX", TS_STRING(BATCH_INDEX));
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 8);
	pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, sizeof(float32_t) * 3, sizeof(float32_t) * 8);
	pipeline.addAttribute(Pipeline::AttributeTexCoord, FormatRu32, 1, 0, sizeof(uint32_t), 1);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create geometry
	Array<float32_t> vertices;
	Array<uint32_t> indices;
	Array<uint32_t> counter;
	Command::DrawElementsIndirect indirect = {};
	Array<Command::DrawElementsIndirect> indirects;
	
	#include "main_icosa.h"
	#include "main_dodeca.h"
	indirect.num_instances = num_instances;
	for(uint32_t i = 0; i < num_draws * num_draws; i++) {
		
		#if BATCH_INDEX
			indirect.base_instance = counter.size();
			for(uint32_t j = 0; j < num_instances; j++) counter.append(counter.size());
		#else
			if(!has_draw_index) {
				indirect.base_instance = counter.size();
				for(uint32_t j = 0; j < num_instances; j++) counter.append(indirects.size());
			}
		#endif
		
		indirect.base_index = indices.size();
		indirect.base_vertex = vertices.size() / 8;
		if(i & 0x01) {
			vertices.append(icosa_vertices, num_icosa_vertices);
			indices.append(icosa_indices, num_icosa_indices);
			indirect.num_indices = num_icosa_indices;
		} else {
			vertices.append(dodeca_vertices, num_dodeca_vertices);
			indices.append(dodeca_indices, num_dodeca_indices);
			indirect.num_indices = num_dodeca_indices;
		}
		indirects.append(indirect);
	}
	
	uint32_t count[4] = { indirects.size() };
	Buffer vertex_buffer = device.createBuffer(Buffer::FlagVertex, vertices.get(), vertices.bytes());
	Buffer index_buffer = device.createBuffer(Buffer::FlagIndex, indices.get(), indices.bytes());
	Buffer count_buffer = device.createBuffer(Buffer::FlagIndirect, count, sizeof(count));
	if(!vertex_buffer || !index_buffer || !count_buffer) return 1;
	
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
		
		// FPS counter
		if(fps > 0.0f) {
			#if BATCH_INDEX
				const char *batch = "Batch";
			#else
				const char *batch = "";
			#endif
			const char *base = (has_base_index) ? "Base" : "";
			const char *draw = (has_draw_index) ? "Draw" : "";
			const char *count = (has_draw_count) ? "Count" : "";
			String size = String::fromBytes(indirects.bytes());
			window.setTitle(String::format("%s%s%s%s%s FPS: %.1f %s", title.get(), batch, base, draw, count, fps, size.get()).get());
		}
		
		// window target
		target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// set pipeline
			command.setPipeline(pipeline);
			
			// set buffers
			command.setVertexBuffer(0, vertex_buffer);
			command.setIndexBuffer(FormatRu32, index_buffer);
			command.setVertexData(1, counter.get(), counter.bytes());
			command.setIndirectData(indirects.get(), indirects.bytes());
			
			// set common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Vector4f(cos(time / 8.0f) * 16.0f, sin(time / 8.0f) * 16.0f, 16.0f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			command.setUniform(0, common_parameters);
			
			// draw indirects
			if(has_draw_count) command.drawElementsIndirect(count_buffer, 0, indirects.size());
			else command.drawElementsIndirect(indirects.size());
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

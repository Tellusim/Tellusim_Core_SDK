// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimMath.h>
#include <math/TellusimSimd.h>
#include <format/TellusimMesh.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>
#include <graphics/TellusimMeshModel.h>

/*
 */
//#define TEXEL	1

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Morph", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// structures
	struct Vertex {
		float32_t position[3];
		float32_t normal[3];
		uint32_t index;
	};
	
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Matrix4x4f transform;
		Vector4f camera;
		float32_t time;
	};
	
	struct TargetParameters {
		uint32_t base_target;
		uint32_t num_targets;
		uint32_t num_vertices;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// shader macro
	Shader::setMacro("TEXEL", TS_STRING(TEXEL));
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.setUniformMask(1, Shader::MaskVertex);
	#if TEXEL
		pipeline.setTexelMask(0, Shader::MaskVertex);
	#else
		pipeline.setStorageMask(0, Shader::MaskVertex);
	#endif
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, offsetof(Vertex, position), sizeof(Vertex));
	pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, offsetof(Vertex, normal), sizeof(Vertex));
	pipeline.addAttribute(Pipeline::AttributeIndex, FormatRu32, 0, offsetof(Vertex, index), sizeof(Vertex));
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// load mesh
	Mesh mesh;
	if(!mesh.load("model.mesh")) return 1;
	
	// create model
	MeshModel model;
	if(!model.create(device, pipeline, mesh)) return 1;
	
	// create targets data
	using Tellusim::float16x4_t;
	Array<float16x4_t> targets_data;
	Array<TargetParameters> target_parameters;
	for(MeshGeometry geometry : mesh.getGeometries()) {
		TargetParameters &parameters = target_parameters.append();
		parameters.base_target = targets_data.size();
		parameters.num_targets = 0;
		parameters.num_vertices = geometry.getAttribute(MeshAttribute::TypePosition).getSize();
		for(uint32_t i = 0; i < geometry.getNumAttributes(); i++) {
			
			// find position attrubute
			uint32_t position = geometry.findAttribute(MeshAttribute::TypePosition, i + 1);
			if(position == Maxu32) continue;
			MeshAttribute position_attribute = geometry.getAttribute(position);
			if(position_attribute.getSize() != parameters.num_vertices) continue;
			if(position_attribute.getFormat() != FormatRGBf32) continue;
			
			// create normal attrubute
			uint32_t normal = geometry.createNormals(false, position);
			if(normal == Maxu32) continue;
			MeshAttribute normal_attribute = geometry.getAttribute(normal);
			if(normal_attribute.getSize() != parameters.num_vertices) continue;
			if(normal_attribute.getFormat() != FormatRGBf32) continue;
			
			// convert format
			position_attribute = position_attribute.toFormat(FormatRGBAf16);
			normal_attribute = normal_attribute.toFormat(FormatRGBAf16);
			
			// create targets data
			targets_data.reserve(targets_data.size() + parameters.num_vertices * 2);
			targets_data.append((const float16x4_t*)position_attribute.getData(), parameters.num_vertices);
			targets_data.append((const float16x4_t*)normal_attribute.getData(), parameters.num_vertices);
			parameters.num_targets++;
		}
	}
	
	// create targets buffer
	#if TEXEL
		Buffer targets_buffer = device.createBuffer(Buffer::FlagTexel, targets_data.get(), targets_data.bytes(), FormatRGBAf16);
	#else
		Buffer targets_buffer = device.createBuffer(Buffer::FlagStorage, targets_data.get(), targets_data.bytes());
	#endif
	if(!targets_buffer) return 1;
	
	// create target
	Target target = device.createTarget(window);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// window target
		target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// set pipeline
			command.setPipeline(pipeline);
			
			// set model buffers
			model.setBuffers(command);
			
			// set common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Vector4f(5.0f, 0.0f, 1.0f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
			common_parameters.transform = Matrix4x4f::rotateZ(Tellusim::sin(time * 0.5f) * 30.0f);
			common_parameters.time = time;
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			command.setUniform(0, common_parameters);
			
			// set targets buffer
			#if TEXEL
				command.setTexelBuffer(0, targets_buffer);
			#else
				command.setStorageBuffer(0, targets_buffer);
			#endif
			
			// draw geometries
			for(uint32_t i = 0; i < mesh.getNumGeometries(); i++) {
				command.setUniform(1, target_parameters[i]);
				model.draw(command, i);
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

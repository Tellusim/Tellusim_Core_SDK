// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <format/TellusimMesh.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>
#include <graphics/TellusimMeshModel.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Tangent", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// structures
	struct Vertex {
		float32_t position[3];
		float32_t normal[3];
		float32_t tangent[4];
		float32_t texcoord[2];
	};
	
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Matrix4x4f transform;
		Vector4f camera;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.setSamplerMask(0, Shader::MaskFragment);
	pipeline.setTextureMask(0, Shader::MaskFragment);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, offsetof(Vertex, position), sizeof(Vertex));
	pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, offsetof(Vertex, normal), sizeof(Vertex));
	pipeline.addAttribute(Pipeline::AttributeTangent, FormatRGBAf32, 0, offsetof(Vertex, tangent), sizeof(Vertex));
	pipeline.addAttribute(Pipeline::AttributeTexCoord, FormatRGf32, 0, offsetof(Vertex, texcoord), sizeof(Vertex));
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create sampler
	Sampler sampler = device.createSampler(Sampler::FilterTrilinear, Sampler::WrapModeRepeat);
	if(!sampler) return 1;
	
	// create texture
	Texture texture = device.loadTexture("tangent.exr", Texture::FlagMipmaps);
	if(!texture) return 1;
	
	// load mesh
	Mesh mesh;
	if(!mesh.load("tangent.glb")) return 1;
	if(!mesh.createNormals(180.0f, true)) return 1;
	if(!mesh.createTangents(true)) return 1;
	mesh.setBasis(Mesh::BasisZUpRight);
	
	// create model
	MeshModel model;
	if(!model.create(device, pipeline, mesh)) return 1;
	
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
			
			// set sampler
			command.setSampler(0, sampler);
			
			// set texture
			command.setTexture(0, texture);
			
			// set model buffers
			model.setBuffers(command);
			
			// set common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Vector4f(1.5f, 1.5f, 1.0f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
			common_parameters.transform = Matrix4x4f::rotateZ(time * 32.0f) * Matrix4x4f::rotateY(60.0f + time * 8.0f);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			command.setUniform(0, common_parameters);
			
			// draw model
			model.draw(command);
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

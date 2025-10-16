// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimMath.h>
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
	String title = String::format("%s Tellusim::Skinned", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// structures
	struct Vertex {
		float32_t position[3];
		float32_t normal[3];
		float32_t texcoord[2];
	};
	
	struct Control {
		float32_t weights[4];
		uint32_t joints[4];
	};
	
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Vector4f camera;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setSamplerMask(0, Shader::MaskFragment);
	pipeline.setTextureMask(0, Shader::MaskFragment);
	pipeline.setUniformMasks(0, 2, Shader::MaskVertex);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, offsetof(Vertex, position), sizeof(Vertex));
	pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, offsetof(Vertex, normal), sizeof(Vertex));
	pipeline.addAttribute(Pipeline::AttributeTexCoord, FormatRGf32, 0, offsetof(Vertex, texcoord), sizeof(Vertex));
	pipeline.addAttribute(Pipeline::AttributeWeights, FormatRGBAf32, 1, offsetof(Control, weights), sizeof(Control));
	pipeline.addAttribute(Pipeline::AttributeJoints, FormatRGBAu32, 1, offsetof(Control, joints), sizeof(Control));
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create sampler
	Sampler sampler = device.createSampler(Sampler::FilterTrilinear, Sampler::WrapModeRepeat);
	if(!sampler) return 1;
	
	// create textures
	Texture textures[2];
	textures[0] = device.loadTexture("skinned_head.jpg");
	textures[1] = device.loadTexture("skinned_body.jpg");
	if(!textures[0] || !textures[1]) return 1;
	
	// load mesh
	Mesh mesh;
	if(!mesh.load("skinned.glb")) return 1;
	if(!mesh.getNumAnimations()) return 1;
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
		
		using Tellusim::sin;
		
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
			
			// set model buffers
			model.setBuffers(command);
			
			// set common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Vector4f(-80.0f, 0.0f, 70.0f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f(0.0f, 0.0f, 40.0f), Vector3f::oneZ);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			command.setUniform(0, common_parameters);
			
			// mesh animation
			MeshAnimation animation = mesh.getAnimation(0);
			animation.setTime(time * 0.7, Matrix4x3d::rotateZ(180.0 + sin(time * 0.5) * 40.0));
			
			// draw geometries
			Vector4f joint_parameters[192];
			for(const MeshGeometry &geometry : mesh.getGeometries()) {
				
				// joint transforms
				for(uint32_t i = 0, j = 0; i < geometry.getNumJoints(); i++, j += 3) {
					const MeshJoint &joint = geometry.getJoint(i);
					Matrix4x3f transform = Matrix4x3f(animation.getGlobalTransform(joint)) * joint.getITransform() * geometry.getTransform();
					joint_parameters[j + 0] = transform.row_0;
					joint_parameters[j + 1] = transform.row_1;
					joint_parameters[j + 2] = transform.row_2;
				}
				command.setUniform(1, joint_parameters);
				
				// draw materials
				for(uint32_t j = 0; j < geometry.getNumMaterials() && j < TS_COUNTOF(textures); j++) {
					command.setTexture(0, textures[j]);
					model.draw(command, geometry.getIndex(), j);
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

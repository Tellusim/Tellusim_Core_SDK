// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <TellusimApp.h>
#include <core/TellusimLog.h>
#include <core/TellusimBlob.h>
#include <core/TellusimTime.h>
#include <format/TellusimMesh.h>
#include <graphics/TellusimMeshModel.h>
#include <platform/TellusimWindow.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>

/*
 */
using namespace Tellusim;

/*
 */
static Texture create_texture(const Device &device, const MeshMaterial &material, const char *type) {
	
	// find material parameter
	uint32_t index = material.findParameter(type);
	if(index == Maxu32 || !material.hasParameterFlag(index, MeshMaterial::FlagBlob)) return Texture::null;
	
	// load image
	Image image;
	Blob blob = material.getParameterBlob(index);
	if(!image.load(blob)) return Texture::null;
	
	// create texture
	return device.createTexture(image, Texture::FlagMipmaps);
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create app
	App app(argc, argv);
	if(!app.create()) return 1;
	
	// create window
	Window window(app.getPlatform(), app.getDevice());
	if(!window || !window.setSize(app.getWidth(), app.getHeight())) return 1;
	if(!window.create("01 Hello USDZ") || !window.setHidden(false)) return 1;
	window.setKeyboardPressedCallback([&](uint32_t key, uint32_t code) {
		if(key == Window::KeyEsc) window.stop();
	});
	window.setCloseClickedCallback([&]() { window.stop(); });
	
	// vertex layout
	struct Vertex {
		Vector3f position;
		Vector3f normal;
		Vector4f tangent;
		Vector2f texcoord;
		Vector4f weights;
		Vector4u joints;
	};
	
	// common parameters
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
	pipeline.setTextureMasks(0, 3, Shader::MaskFragment);
	pipeline.setUniformMasks(0, 2, Shader::MaskVertex);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, offsetof(Vertex, position), sizeof(Vertex));
	pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, offsetof(Vertex, normal), sizeof(Vertex));
	pipeline.addAttribute(Pipeline::AttributeTangent, FormatRGBAf32, 0, offsetof(Vertex, tangent), sizeof(Vertex));
	pipeline.addAttribute(Pipeline::AttributeTexCoord, FormatRGf32, 0, offsetof(Vertex, texcoord), sizeof(Vertex));
	pipeline.addAttribute(Pipeline::AttributeWeights, FormatRGBAf32, 0, offsetof(Vertex, weights), sizeof(Vertex));
	pipeline.addAttribute(Pipeline::AttributeJoints, FormatRGBAu32, 0, offsetof(Vertex, joints), sizeof(Vertex));
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLess);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// load mesh
	Mesh mesh;
	if(!mesh.load("model.usdz")) return 1;
	if(!mesh.getNumGeometries()) return 1;
	if(!mesh.getNumAnimations()) return 1;
	mesh.setBasis(Mesh::BasisZUpRight);
	mesh.createTangents();
	
	// create model
	MeshModel model;
	if(!model.create(device, pipeline, mesh)) return 1;
	
	// create textures
	Array<Texture> normal_textures;
	Array<Texture> diffuse_textures;
	Array<Texture> roughness_textures;
	for(const MeshGeometry &geometry : mesh.getGeometries()) {
		for(const MeshMaterial &material : geometry.getMaterials()) {
			normal_textures.append(create_texture(device, material, MeshMaterial::TypeNormal));
			diffuse_textures.append(create_texture(device, material, MeshMaterial::TypeDiffuse));
			roughness_textures.append(create_texture(device, material, MeshMaterial::TypeRoughness));
		}
	}
	
	// create sampler
	Sampler sampler = device.createSampler(Sampler::FilterTrilinear, Sampler::WrapModeRepeat);
	if(!sampler) return 1;
	
	// create target
	Target target = device.createTarget(window);
	target.setClearColor(Color::gray);
	
	// main loop
	window.run([&]() {
		
		Window::update();
		
		// render window
		if(!window.render()) return false;
		
		// window target
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
			common_parameters.camera = Vector4f(0.0f, -180.0f, 180.0f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(common_parameters.camera.xyz, Vector3f(0.0f, 0.0f, 80.0f), Vector3f::oneZ);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			command.setUniform(0, common_parameters);
			
			// mesh animation
			float64_t time = Time::seconds();
			MeshAnimation animation = mesh.getAnimation(0);
			animation.setTime(time, Matrix4x3d::rotateZ(Tellusim::sin(time) * 30.0));
			
			// draw geometries
			uint32_t texture_index = 0;
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
				for(const MeshMaterial &material : geometry.getMaterials()) {
					command.setTexture(0, normal_textures[texture_index]);
					command.setTexture(1, diffuse_textures[texture_index]);
					command.setTexture(2, roughness_textures[texture_index]);
					model.draw(command, geometry.getIndex(), material.getIndex());
					texture_index++;
				}
			}
		}
		target.end();
		
		// present window
		if(!window.present()) return false;
		
		// check errors
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}

/*
 */
#if _ANDROID
	#include <system/TellusimAndroid.h>
	TS_DECLARE_ANDROID_NATIVE_ACTIVITY
#endif

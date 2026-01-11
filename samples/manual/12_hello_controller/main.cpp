// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <TellusimApp.h>
#include <core/TellusimLog.h>
#include <core/TellusimBlob.h>
#include <core/TellusimTime.h>
#include <format/TellusimMesh.h>
#include <geometry/TellusimSpatial.h>
#include <geometry/TellusimTriangle.h>
#include <graphics/TellusimMeshModel.h>
#include <platform/TellusimWindow.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>
#include <system/TellusimController.h>

#include "panel.h"

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
	
	// create texture with mipmaps
	return device.createTexture(image.getMipmapped(Image::FilterBox), Texture::FlagMipmaps);
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
	if(!window.create("12 Hello Controller") || !window.setHidden(false)) return 1;
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
	};
	
	// common parameters
	struct CommonParameters {
		Matrix4x4f projection;		// projection matrix
		Matrix4x4f modelview;		// modelview matrix
		Matrix4x4f transform;		// transform matrix
		Vector4f camera;			// camera position
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// device info
	TS_LOGF(Message, "Device: %s\n", device.getName().get());
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setSamplerMask(0, Shader::MaskFragment);
	pipeline.setTextureMasks(0, 3, Shader::MaskFragment);
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, offsetof(Vertex, position), sizeof(Vertex));
	pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, offsetof(Vertex, normal), sizeof(Vertex));
	pipeline.addAttribute(Pipeline::AttributeTangent, FormatRGBAf32, 0, offsetof(Vertex, tangent), sizeof(Vertex));
	pipeline.addAttribute(Pipeline::AttributeTexCoord, FormatRGf32, 0, offsetof(Vertex, texcoord), sizeof(Vertex));
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLess);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// load mesh
	Mesh mesh;
	if(!mesh.load("model.glb") || !mesh.getNumGeometries()) return 1;
	mesh.setBasis(Mesh::BasisZUpRight);
	mesh.setTransform(Vector3d(0.01));
	mesh.createTangents();
	
	// create geometry spatial trees
	struct SpatialTree {
		Array<Spatial::Node3f> nodes;
		Array<Vector3f> vertices;
	};
	Array<SpatialTree> spatial_trees(mesh.getNumGeometries());
	for(const MeshGeometry &geometry : mesh.getGeometries()) {
		SpatialTree &spatial = spatial_trees[geometry.getIndex()];
		
		// geometry positions
		const MeshAttribute &positions = geometry.getAttribute(MeshAttribute::TypePosition);
		if(!positions || positions.getFormat() != FormatRGBf32) continue;
		
		// position indices
		const MeshIndices &indices = positions.getIndices();
		if(!indices || indices.getType() != MeshIndices::TypeTriangle) continue;
		
		// create spatial tree
		uint32_t num_nodes = indices.getSize() / 3;
		spatial.nodes.resize(num_nodes * 2);
		spatial.vertices.resize(num_nodes * 3);
		for(uint32_t i = 0, j = 0; i < num_nodes; i++, j += 3) {
			const Vector3f &v0 = positions.get<Vector3f>(indices.get(j + 0));
			const Vector3f &v1 = positions.get<Vector3f>(indices.get(j + 1));
			const Vector3f &v2 = positions.get<Vector3f>(indices.get(j + 2));
			spatial.nodes[num_nodes + i].bound.min = min(v0, v1, v2);
			spatial.nodes[num_nodes + i].bound.max = max(v0, v1, v2);
			spatial.vertices[j + 0] = v0;
			spatial.vertices[j + 1] = v1;
			spatial.vertices[j + 2] = v2;
		}
		Spatial::create<float32_t>(spatial.nodes.get(), num_nodes);
	}
	Array<uint32_t> spatial_indices(1024);
	
	// create model
	MeshModel model;
	if(!model.create(device, pipeline, mesh, MeshModel::FlagMaterials)) return 1;
	
	// create textures
	Array<Texture> normal_textures;
	Array<Texture> diffuse_textures;
	Array<Texture> metallic_textures;
	for(const MeshGeometry &geometry : mesh.getGeometries()) {
		for(const MeshMaterial &material : geometry.getMaterials()) {
			normal_textures.append(create_texture(device, material, MeshMaterial::TypeNormal));
			diffuse_textures.append(create_texture(device, material, MeshMaterial::TypeDiffuse));
			metallic_textures.append(create_texture(device, material, MeshMaterial::TypeMetallic));
		}
	}
	
	// create sampler
	Sampler sampler = device.createSampler(Sampler::FilterTrilinear, Sampler::WrapModeRepeat);
	if(!sampler) return 1;
	
	// create target
	Target target = device.createTarget(window);
	target.setClearColor(Color::gray);
	
	// create panel
	Panel panel(device);
	
	// camera parameters
	constexpr float32_t camera_radius = 0.3f;
	constexpr float32_t camera_linear_damping = 4.0f;
	constexpr float32_t camera_angular_damping = 4.0f;
	Vector3f camera_linear_velocity = Vector3f::zero;
	Vector2f camera_angular_velocity = Vector2f::zero;
	
	// current camera position and direction
	Vector3f camera_position = Vector3f(0.0f, -2.0f, 1.0f);
	Vector3f camera_direction = Vector3f(0.0f, 1.0f, 0.0f);
	
	// mouse/keyboard parameters
	constexpr float32_t panning_sensitivity = 0.02f;
	constexpr float32_t dollying_sensitivity = 0.02f;
	constexpr float32_t rotation_sensitivity = 0.4f;
	constexpr float32_t keyboard_acceleration = 16.0f;
	
	// game controller parameters
	constexpr float32_t controller_sensitivity = 720.0f;
	constexpr float32_t controller_acceleration = 16.0f;
	
	// create controller
	Controller controller;
	
	// controller callbacks
	controller.setConnectedCallback([&](Controller controller) {
		panel.setInfo(controller.getName() + "\n" + controller.getModel());
	});
	controller.setDisconnectedCallback([&](Controller controller) {
		panel.setInfo(String("Disconnected"));
	});
	
	// old system time
	float64_t old_time = Time::seconds();
	
	// main loop
	window.run([&]() {
		
		using Tellusim::exp;
		using Tellusim::acos;
		using Tellusim::atan2;
		
		Window::update();
		
		Controller::update();
		
		// connect controller if it isn't yet connected
		if(!controller.wasConnected()) controller.connect();
		
		// render window
		if(!window.render()) return false;
		
		// update panel
		panel.update(window, device, target);
		
		// calculate inverse FPS value
		float64_t time = Time::seconds();
		float32_t ifps = (float32_t)(time - old_time);
		old_time = time;
		
		// reduce camera velocity over the time
		camera_linear_velocity *= exp(-ifps * camera_linear_damping);
		camera_angular_velocity *= exp(-ifps * camera_angular_damping);
		
		// keyboard controls
		float32_t acceleration = ifps * keyboard_acceleration;
		if(window.getKeyboardKey('w') || window.getKeyboardKey(Window::KeyUp)) camera_linear_velocity.x -= acceleration;
		if(window.getKeyboardKey('s') || window.getKeyboardKey(Window::KeyDown)) camera_linear_velocity.x += acceleration;
		if(window.getKeyboardKey('a') || window.getKeyboardKey(Window::KeyLeft)) camera_linear_velocity.y += acceleration;
		if(window.getKeyboardKey('d') || window.getKeyboardKey(Window::KeyRight)) camera_linear_velocity.y -= acceleration;
		if(window.getKeyboardKey('q')) camera_linear_velocity.z += acceleration;
		if(window.getKeyboardKey('e')) camera_linear_velocity.z -= acceleration;
		
		// mouse controls
		{
			float32_t mouse_dx = (float32_t)window.getMouseDX();
			float32_t mouse_dy = (float32_t)window.getMouseDY();
			
			// camera rotation
			if(window.getMouseButton(Window::ButtonLeft)) {
				camera_angular_velocity.x += mouse_dx * rotation_sensitivity;
				camera_angular_velocity.y += mouse_dy * rotation_sensitivity;
			}
			// camera panning
			else if(window.getMouseButton(Window::ButtonMiddle)) {
				camera_linear_velocity.y += mouse_dx * panning_sensitivity;
				camera_linear_velocity.z += mouse_dy * panning_sensitivity;
			}
			// camera dollying
			else if(window.getMouseButton(Window::ButtonRight)) {
				camera_linear_velocity.x += mouse_dy * dollying_sensitivity;
			}
		}
		
		// controller controlls
		{
			// camera rotation with right stick
			float32_t sensitivity = controller_sensitivity * ifps;
			camera_angular_velocity.x += controller.getStickX(Controller::StickRight) * sensitivity;
			camera_angular_velocity.y += controller.getStickY(Controller::StickRight) * sensitivity;
			
			// camera panning with left stick
			float32_t acceleration = controller_acceleration * ifps;
			camera_linear_velocity.y -= controller.getStickX(Controller::StickLeft) * acceleration;
			camera_linear_velocity.x -= controller.getStickY(Controller::StickLeft) * acceleration;
			
			// camera dollying with triggers
			camera_linear_velocity.z += controller.getButtonValue(Controller::ButtonTriggerLeft) * acceleration;
			camera_linear_velocity.z -= controller.getButtonValue(Controller::ButtonTriggerRight) * acceleration;
		}
		
		// rotate camera based on camera angular velocity
		float32_t phi = atan2(camera_direction.x, camera_direction.y) * Rad2Deg + camera_angular_velocity.x * ifps;
		float32_t theta = clamp(acos(clamp(camera_direction.z, -1.0f, 1.0f)) * Rad2Deg - 90.0f + camera_angular_velocity.y * ifps, -89.9f, 89.9f);
		camera_direction = (Quaternionf::rotateZ(-phi) * Quaternionf::rotateX(-theta)) * Vector3f(0.0f, 1.0f, 0.0f);
		
		// calculate local camera basis
		Vector3f front_direction = normalize(camera_direction);
		Vector3f right_direction = normalize(cross(camera_direction, Vector3f(0.0f, 0.0f, 1.0f)));
		Vector3f top_direction = normalize(cross(front_direction, right_direction));
		
		// update camera position based on camera linear velocity and current orientation
		camera_position += front_direction * (camera_linear_velocity.x * ifps);
		camera_position += right_direction * (camera_linear_velocity.y * ifps);
		camera_position += top_direction * (camera_linear_velocity.z * ifps);
		
		// calculate camera up vector based on angular velocity
		Vector3f camera_up = Quaternionf(camera_direction, clamp(-camera_angular_velocity.x * 0.05f, -15.0f, 15.0f)) * Vector3f(0.0f, 0.0f, 1.0f);
		
		// scene collision detection
		for(uint32_t i = 0; i < 8; i++) {
			
			// perform collision detection with the scene
			float32_t contact_depth = 0.0f;
			Vector3f contact_position = Vector3f::zero;
			BoundBoxf camera_bound = BoundBoxf(camera_position - camera_radius, camera_position + camera_radius);
			for(const SpatialTree &spatial : spatial_trees) {
				if(!spatial.nodes) continue;
				Spatial::intersection(camera_bound, spatial.nodes.get(), spatial_indices);
				for(uint32_t index : spatial_indices) {
					const Vector3f &v0 = spatial.vertices[index * 3 + 0];
					const Vector3f &v1 = spatial.vertices[index * 3 + 1];
					const Vector3f &v2 = spatial.vertices[index * 3 + 2];
					Vector3f texcoord = Triangle::closest(v0, v1, v2, camera_position);
					float32_t depth = camera_radius - texcoord.z;
					if(depth < contact_depth) continue;
					contact_position = Triangle::lerp(v0, v1, v2, texcoord.xy);
					contact_depth = depth;
				}
			}
			
			// check contact depth
			if(contact_depth < 1e-6f) break;
			
			// simple collision resolve using deepest contact
			Vector3f contact_normal = normalize(camera_position - contact_position);
			camera_position += contact_normal * (contact_depth - 1e-6f);
		}
		
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
			common_parameters.camera = Vector4f(camera_position, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f);
			common_parameters.modelview = Matrix4x4f::lookAt(camera_position, camera_position - camera_direction, camera_up);
			common_parameters.transform = Matrix4x4f::identity;
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			command.setUniform(0, common_parameters);
			
			// draw geometries
			uint32_t texture_index = 0;
			for(const MeshGeometry &geometry : mesh.getGeometries()) {
				
				// draw materials
				for(const MeshMaterial &material : geometry.getMaterials()) {
					command.setTexture(0, normal_textures[texture_index]);
					command.setTexture(1, diffuse_textures[texture_index]);
					command.setTexture(2, metallic_textures[texture_index]);
					model.draw(command, geometry.getIndex(), material.getIndex());
					texture_index++;
				}
			}
			
			// draw panel
			panel.draw(command, target);
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

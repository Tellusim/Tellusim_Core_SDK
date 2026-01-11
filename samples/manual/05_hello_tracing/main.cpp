// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <TellusimApp.h>
#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <core/TellusimFile.h>
#include <math/TellusimMath.h>
#include <format/TellusimMesh.h>
#include <geometry/TellusimMeshRefine.h>
#include <graphics/TellusimMeshModel.h>
#include <platform/TellusimWindow.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>

#include "panel.h"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create app
	App app(argc, argv);
	if(!app.create()) return 1;
	
	// create window
	Window window(app.getPlatform(), app.getDevice());
	if(!window || !window.setSize(app.getWidth(), app.getHeight())) return 1;
	if(!window.create("05 Hello Tracing") || !window.setHidden(false)) return 1;
	window.setKeyboardPressedCallback([&](uint32_t key, uint32_t code) {
		if(key == Window::KeyEsc) window.stop();
	});
	window.setCloseClickedCallback([&]() { window.stop(); });
	
	// scene size
	constexpr uint32_t grid_size = 48;
	constexpr uint32_t grid_height = 2;
	
	// structures
	struct Vertex {
		Vector4f position;
		Vector4f normal;
	};
	
	struct CommonParameters {
		Matrix4x4f projection;			// projection matrix
		Matrix4x4f imodelview;			// imodelview matrix
		Vector4f camera;				// camera position
		float32_t window_width;			// window width
		float32_t window_height;		// window height
		float32_t time;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// device info
	TS_LOGF(Message, "Device: %s\n", device.getName().get());
	
	// check fragment tracing support
	if(!device.getFeatures().fragmentTracing) {
		TS_LOG(Error, "fragment tracing is not supported\n");
		return 0;
	}
	
	// create model pipeline
	Pipeline model_pipeline = device.createPipeline();
	model_pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, offsetof(Vertex, position), sizeof(Vertex));
	model_pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, offsetof(Vertex, normal), sizeof(Vertex));
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskFragment);
	pipeline.setStorageMasks(0, 2, Shader::MaskFragment);
	pipeline.setTracingMask(0, Shader::MaskFragment);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create mesh
	if(!File::isFile("model.mesh")) {
		
		// load mesh
		Mesh src_mesh;
		TS_LOG(Message, "Loading Mesh\n");
		if(!src_mesh.load("model.fbx")) return 1;
		
		// remove texture coordinates
		for(MeshGeometry &geometry : src_mesh.getGeometries()) {
			MeshAttribute texcoord_attribute = geometry.getAttribute(MeshAttribute::TypeTexCoord);
			if(texcoord_attribute) geometry.removeAttribute(texcoord_attribute);
		}
		
		// refine mesh
		Mesh subdiv_mesh;
		uint32_t subdiv_steps = 4;
		TS_LOG(Message, "Refining Mesh\n");
		if(!MeshRefine::subdiv(subdiv_mesh, src_mesh, subdiv_steps)) return 1;
		subdiv_mesh.createNormals(true);
		subdiv_mesh.optimizeAttributes();
		subdiv_mesh.optimizeIndices();
		
		// save mesh
		TS_LOG(Message, "Saving Mesh\n");
		subdiv_mesh.save("model.mesh");
	}
	
	// load mesh
	Mesh mesh;
	if(!mesh.load("model.mesh")) return 1;
	
	// create model
	MeshModel model;
	if(!model.create(device, model_pipeline, mesh, MeshModel::FlagIndices32 | MeshModel::FlagBufferStorage | MeshModel::FlagBufferTracing | MeshModel::FlagBufferAddress)) return 1;
	Buffer vertex_buffer = model.getVertexBuffer();
	Buffer index_buffer = model.getIndexBuffer();
	
	// create tracing
	Tracing tracing = device.createTracing();
	tracing.addVertexBuffer(model.getNumGeometryVertices(0), model_pipeline.getAttributeFormat(0), model.getVertexBufferStride(0), vertex_buffer);
	tracing.addIndexBuffer(model.getNumIndices(), model.getIndexFormat(), index_buffer);
	if(!tracing.create(Tracing::TypeTriangle, Tracing::FlagCompact | Tracing::FlagFastTrace)) return 1;
	
	// create instances
	Tracing::Instance instance;
	instance.mask = 0xff;
	instance.tracing = &tracing;
	Array<Tracing::Instance> instances(grid_size * grid_size * grid_height, instance);
	
	// create instances buffer
	Buffer instances_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagTracing, Tracing::InstanceSize * instances.size());
	if(!instances_buffer) return 1;
	
	// create instances tracing
	Tracing instances_tracing = device.createTracing(instances.size(), instances_buffer);
	if(!instances_tracing) return 1;
	
	// create build buffer
	size_t build_size = max(tracing.getBuildSize(), instances_tracing.getBuildSize());
	Buffer build_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagScratch, build_size);
	if(!build_buffer) return 1;
	
	// build tracing
	if(!device.buildTracing(tracing, build_buffer, Tracing::FlagCompact)) return 1;
	device.flushTracing(tracing);
	
	// create target
	Target target = device.createTarget(window);
	target.setClearColor(Color::gray * 0.25f);
	
	// create query
	Query time_query;
	if(device.hasQuery(Query::TypeTime)) time_query = device.createQuery(Query::TypeTime);
	
	// create panel
	Panel panel(device);
	
	// print info
	TS_LOGF(Message, "Instances: %s\n", String::fromBytes(instances_tracing.getMemory()).get());
	TS_LOGF(Message, "Tracing: %s\n", String::fromBytes(tracing.getMemory()).get());
	TS_LOGF(Message, "Vertex: %s\n", String::fromBytes(vertex_buffer.getSize()).get());
	TS_LOGF(Message, "Index: %s\n", String::fromBytes(index_buffer.getSize()).get());
	TS_LOGF(Message, "Build: %s\n", String::fromBytes(tracing.getBuildSize()).get());
	
	// main loop
	window.run([&]() {
		
		Window::update();
		
		// render window
		if(!window.render()) return false;
		
		// get query
		if(time_query && time_query.isAvailable()) panel.setInfo("\nDraw: " + String::fromTime(time_query.getTime()));
		
		// update panel
		panel.update(window, device, target);
		
		// current time
		float32_t time = (float32_t)Time::seconds();
		
		// time control
		if(window.getKeyboardKey('3')) time = Pi;
		if(window.getKeyboardKey('4')) time = Pi / 0.2f;
		
		// transform instances
		float32_t offset = (grid_size - 1.0f) * 0.5f;
		for(uint32_t z = 0, i = 0; z < grid_height; z++) {
			Matrix4x3f rotate = Matrix4x3f::rotateZ(time * (z * 16.0f - 8.0f)) * Matrix4x3f::rotateY(90.0f);
			for(uint32_t y = 0; y < grid_size; y++) {
				for(uint32_t x = 0; x < grid_size; x++, i++) {
					Matrix4x3f translate = Matrix4x3f::translate((x - offset) * 4.0f, (y - offset) * 4.0f, z * 2.0f);
					(translate * rotate).get(instances[i].transform);
				}
			}
		}
		
		// build instances tracing
		if(!device.setTracing(instances_tracing, instances.get(), instances.size())) return false;
		if(!device.buildTracing(instances_tracing, build_buffer)) return false;
		
		// flush instances tracing
		device.flushTracing(instances_tracing);
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// set pipeline
			command.setPipeline(pipeline);
			
			// common parameters
			CommonParameters common_parameters;
			float32_t offset = 1.0f - Tellusim::cos(time * 0.2f);
			common_parameters.camera = Matrix4x4f::rotateZ(time * 2.0f) * Vector4f(Vector3f(32.0f + offset * 24.0f, 0.0f, 8.0f + offset * 8.0f), 1.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, true);
			common_parameters.imodelview = inverse(Matrix4x4f::lookAt(common_parameters.camera.xyz, Vector3f(0.0f, 0.0f, -16.0f), Vector3f::oneZ));
			common_parameters.window_width = (float32_t)window.getWidth();
			common_parameters.window_height = (float32_t)window.getHeight();
			common_parameters.time = time;
			
			// set common parameters
			command.setUniform(0, common_parameters);
			
			// set storage buffers
			command.setStorageBuffers(0, {
				vertex_buffer,
				index_buffer,
			});
			
			// set tracing
			command.setTracing(0, instances_tracing);
			
			// begin query
			if(time_query) command.beginQuery(time_query);
				
				// draw triangle
				command.drawArrays(3);
				
			// end query
			if(time_query) command.endQuery(time_query);
			
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

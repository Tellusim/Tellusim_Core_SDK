// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <TellusimApp.h>
#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <core/TellusimFile.h>
#include <format/TellusimMesh.h>
#include <geometry/TellusimMeshRefine.h>
#include <graphics/TellusimMeshModel.h>
#include <platform/TellusimWindow.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimTraversal.h>
#include <platform/TellusimCommand.h>
#include <platform/TellusimCompute.h>

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
	if(!window.create("06 Hello Traversal") || !window.setHidden(false)) return 1;
	window.setKeyboardPressedCallback([&](uint32_t key, uint32_t code) {
		if(key == Window::KeyEsc) window.stop();
	});
	window.setCloseClickedCallback([&]() { window.stop(); });
	
	// declarations
	#include "main.h"
	
	// scene size
	constexpr uint32_t grid_size = 9;
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;			// projection matrix
		Matrix4x4f imodelview;			// imodelview matrix
		Vector4f camera;				// camera position
		Vector4f light;					// light position
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// device info
	TS_LOGF(Message, "Device: %s\n", device.getName().get());
	
	// check traversal tracing support
	if(!device.getFeatures().traversalTracing) {
		TS_LOG(Error, "traversal tracing is not supported\n");
		return 0;
	}
	if(device.getFeatures().maxTraversalDepth == 1) {
		TS_LOG(Error, "traversal recursion is not supported\n");
	}
	
	// shader macros
	Shader::setMacro("MAX_TRAVERSAL_DEPTH", device.getFeatures().maxTraversalDepth);
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setTextureMask(0, Shader::MaskFragment);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create model pipeline
	Pipeline model_pipeline = device.createPipeline();
	model_pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, offsetof(Vertex, position), sizeof(Vertex));
	model_pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, offsetof(Vertex, normal), sizeof(Vertex));
	
	// create traversal
	Traversal traversal = device.createTraversal();
	traversal.setUniformMask(0, Shader::MaskAll);
	traversal.setStorageMasks(0, 3, Shader::MaskAll);
	traversal.setSurfaceMask(0, Shader::MaskRayGen);
	traversal.setTracingMask(0, Shader::MaskRayGen | Shader::MaskClosest);
	traversal.setRecursionDepth(min(device.getFeatures().maxTraversalDepth, 2u));
	
	// entry shader
	if(!traversal.loadShaderGLSL(Shader::TypeRayGen, "main.shader", "RAYGEN_SHADER=1")) return 1;
	
	// primary shaders
	if(!traversal.loadShaderGLSL(Shader::TypeRayMiss, "main.shader", "RAYMISS_SHADER=1; PRIMARY_SHADER=1")) return 1;
	if(!traversal.loadShaderGLSL(Shader::TypeClosest, "main.shader", "CLOSEST_SHADER=1; PRIMARY_SHADER=1; PLANE_SHADER=1")) return 1;
	if(!traversal.loadShaderGLSL(Shader::TypeClosest, "main.shader", "CLOSEST_SHADER=1; PRIMARY_SHADER=1; MODEL_SHADER=1")) return 1;
	if(!traversal.loadShaderGLSL(Shader::TypeClosest, "main.shader", "CLOSEST_SHADER=1; PRIMARY_SHADER=1; DODECA_SHADER=1")) return 1;
	
	// reflection shaders
	if(!traversal.loadShaderGLSL(Shader::TypeRayMiss, "main.shader", "RAYMISS_SHADER=1; REFLECTION_SHADER=1")) return 1;
	if(!traversal.loadShaderGLSL(Shader::TypeClosest, "main.shader", "CLOSEST_SHADER=1; REFLECTION_SHADER=1; PLANE_SHADER=1")) return 1;
	if(!traversal.loadShaderGLSL(Shader::TypeClosest, "main.shader", "CLOSEST_SHADER=1; REFLECTION_SHADER=1; MODEL_SHADER=1")) return 1;
	if(!traversal.loadShaderGLSL(Shader::TypeClosest, "main.shader", "CLOSEST_SHADER=1; REFLECTION_SHADER=1; DODECA_SHADER=1")) return 1;
	
	// shadow shaders
	if(!traversal.loadShaderGLSL(Shader::TypeRayMiss, "main.shader", "RAYMISS_SHADER=1; SHADOW_SHADER=1")) return 1;
	
	// create traversal
	if(!traversal.create()) return 1;
	
	// create mesh
	if(!File::isFile("model.mesh")) {
		
		// load mesh
		Mesh src_mesh;
		TS_LOG(Message, "Loading Mesh\n");
		if(!src_mesh.load("model.fbx")) return 1;
		
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
	
	// create geometries
	Array<Geometry> geometries;
	Array<Vertex> vertices;
	Array<uint32_t> indices;
	const char *names[] = { "plane.glb", "model.mesh", "dodeca.glb", nullptr };
	for(uint32_t i = 0; names[i]; i++) {
		
		// load mesh
		Mesh mesh;
		if(!mesh.load(names[i])) return 1;
		
		MeshModel model;
		
		// vertex buffer callback
		model.setVertexBufferCallback([&](const void *src, size_t size, bool owner) {
			
			// create geometry
			Geometry &geometry = geometries.append();
			geometry.base_vertex = vertices.size();
			geometry.base_index = indices.size();
			
			// copy vertices
			geometry.num_vertices = (uint32_t)(size / sizeof(Vertex));
			vertices.append((const Vertex*)src, geometry.num_vertices);
			
			// release memory
			if(owner) Allocator::free(src, size);
			
			return true;
		});
		
		// index buffer callback
		model.setIndexBufferCallback([&](const void *src, size_t size, bool owner) {
			
			// copy indices
			Geometry &geometry = geometries.back();
			geometry.num_indices = (uint32_t)(size / sizeof(uint32_t));
			indices.append((const uint32_t*)src, geometry.num_indices);
			
			// release memory
			if(owner) Allocator::free(src, size);
			
			return true;
		});
		
		// create model
		if(!model.create(device, model_pipeline, mesh, MeshModel::FlagIndices32)) return 1;
	}
	
	TS_LOGF(Message, "Geometries: %u\n", geometries.size());
	TS_LOGF(Message, "Vertices: %u\n", vertices.size());
	TS_LOGF(Message, "Triangles: %u\n", indices.size() / 3);
	
	// create geometry buffer
	Buffer geometry_buffer = device.createBuffer(Buffer::FlagStorage, geometries.get(), geometries.bytes());
	if(!geometry_buffer) return 1;
	
	// create vertex buffer
	Buffer vertex_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagTracing | Buffer::FlagAddress, vertices.get(), vertices.bytes());
	if(!vertex_buffer) return 1;
	
	// create index buffer
	Buffer index_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagTracing | Buffer::FlagAddress, indices.get(), indices.bytes());
	if(!index_buffer) return 1;
	
	// create tracings
	size_t build_size = 0;
	Array<Tracing> tracings;
	for(Geometry &geometry : geometries) {
		Tracing tracing = device.createTracing();
		tracing.addVertexBuffer(geometry.num_vertices, FormatRGBf32, sizeof(Vertex), vertex_buffer, sizeof(Vertex) * geometry.base_vertex);
		tracing.addIndexBuffer(geometry.num_indices, FormatRu32, index_buffer, sizeof(uint32_t) * geometry.base_index);
		if(!tracing.create(Tracing::TypeTriangle, Tracing::FlagCompact | Tracing::FlagFastTrace)) return 1;
		build_size += tracing.getBuildSize();
		tracings.append(tracing);
	}
	
	// create build buffer
	Buffer build_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagScratch, build_size);
	if(!build_buffer) return 1;
	
	// build tracings
	if(!device.buildTracings(tracings, build_buffer, Tracing::FlagCompact)) return 1;
	device.flushTracings(tracings);
	
	// plane instance
	Tracing::Instance plane_instance;
	plane_instance.mask = 0xff;
	plane_instance.data = 0;
	plane_instance.offset = 0;
	plane_instance.tracing = &tracings[0];
	Matrix4x3f::identity.get(plane_instance.transform);
	
	// model instance
	Tracing::Instance model_instance;
	model_instance.mask = 0xff;
	model_instance.data = 1;
	model_instance.offset = 1;
	model_instance.tracing = &tracings[1];
	
	// dodeca instance
	Tracing::Instance dodeca_instance;
	dodeca_instance.mask = 0xff;
	dodeca_instance.data = 2;
	dodeca_instance.offset = 2;
	dodeca_instance.tracing = &tracings[2];
	
	// create instances
	Array<Tracing::Instance> instances;
	instances.reserve(grid_size * grid_size * 2 + 1);
	for(uint32_t i = 0; i < grid_size * grid_size; i++) {
		instances.append(model_instance);
		instances.append(dodeca_instance);
	}
	instances.append(plane_instance);
	
	// create instances buffer
	Buffer instances_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagTracing, Tracing::InstanceSize * instances.size());
	if(!instances_buffer) return 1;
	
	// create instances tracing
	Tracing instances_tracing = device.createTracing(instances.size(), instances_buffer);
	if(!instances_tracing) return 1;
	
	// create query
	Query time_query = device.createQuery(Query::TypeTime);
	
	// create target
	Target target = device.createTarget(window);
	
	// tracing surface
	Texture surface;
	
	// create panel
	Panel panel(device);
	
	// main loop
	window.run([&]() {
		
		using Tellusim::sin;
		using Tellusim::cos;
		
		Window::update();
		
		// render window
		if(!window.render()) return false;
		
		// get query
		if(time_query.isAvailable()) panel.setInfo("\nDraw: " + String::fromTime(time_query.getTime()));
		
		// update panel
		panel.update(window, device, target);
		
		// current time
		float32_t time = (float32_t)Time::seconds();
		
		// time control
		if(window.getKeyboardKey('1')) time = 0.0f;
		
		// common parameters
		CommonParameters common_parameters;
		common_parameters.camera = Matrix4x4f::rotateZ(sin(time) * 4.0f) * Vector4f(16.0f, 0.0f, 8.0f + cos(time * 2.0f) * 0.5f, 0.0f) * (1.0f + sin(time * 0.5f) * 0.2f);
		common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, true);
		common_parameters.imodelview = Matrix4x4f::placeTo(Vector3f(common_parameters.camera), Vector3f(0.0f, 0.0f, -3.0f), Vector3f::oneZ);
		common_parameters.light = Vector4f(12.0f + sin(time * 0.5f) * 2.0f, cos(time * 0.5f) * 2.0f, 8.0f, 0.0f);
		
		// transform instances
		float32_t offset = (grid_size - 1.0f) * 0.5f;
		for(uint32_t y = 0, i = 0; y < grid_size; y++) {
			for(uint32_t x = 0; x < grid_size; x++) {
				Matrix4x3f translate = Matrix4x3f::translate((x - offset) * 5.0f, (y - offset) * 5.0f, 4.0f);
				Matrix4x3f rotate_0 = Matrix4x3f::rotateZ(time * 32.0f + i * 13.0f) * Matrix4x3f::rotateY(90.0f);
				Matrix4x3f rotate_1 = Matrix4x3f::translate(0.0f, 0.0f, 1.0f) * Matrix4x3f::rotateX(time * 32.0f + i * 13.0f) * Matrix4x3f::rotateZ(-time * 32.0f + i * 13.0f);
				(translate * rotate_0).get(instances[i++].transform);
				(translate * rotate_1).get(instances[i++].transform);
			}
		}
		
		// build instance tracing
		if(!device.setTracing(instances_tracing, instances.get(), instances.size())) return false;
		if(!device.buildTracing(instances_tracing, build_buffer)) return false;
		device.flushTracing(instances_tracing);
		
		// create surface
		uint32_t width = window.getWidth();
		uint32_t height = window.getHeight();
		if(window.getKeyboardKey('2')) { width = 1600; height = 900; }
		if(window.getKeyboardKey('3')) { width = 3840; height = 2160; }
		if(!surface || surface.getWidth() != width || surface.getHeight() != height) {
			device.releaseTexture(surface);
			surface = device.createTexture2D(FormatRGBAu8n, width, height, Texture::FlagSurface);
		}
		
		// trace scene
		{
			// create command list
			Compute compute = device.createCompute();
			
			// begin query
			compute.beginQuery(time_query);
				
				// set traversal
				compute.setTraversal(traversal);
				
				// set uniform parameters
				compute.setUniform(0, common_parameters);
				
				// set storage buffers
				compute.setStorageBuffers(0, {
					geometry_buffer,
					vertex_buffer,
					index_buffer
				});
				
				// set instances tracing
				compute.setTracing(0, instances_tracing);
				
				// set surface texture
				compute.setSurfaceTexture(0, surface);
				
				// dispatch traversal
				compute.dispatch(surface);
				
				// surface barrier
				compute.barrier(surface);
				
			// end query
			compute.endQuery(time_query);
		}
		
		// flush surface
		device.flushTexture(surface);
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// draw surface
			command.setPipeline(pipeline);
			command.setTexture(0, surface);
			command.drawArrays(3);
			
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

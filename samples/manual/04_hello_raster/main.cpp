// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <TellusimApp.h>
#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <core/TellusimFile.h>
#include <core/TellusimAsync.h>
#include <math/TellusimMath.h>
#include <format/TellusimMesh.h>
#include <geometry/TellusimMeshGraph.h>
#include <geometry/TellusimMeshRefine.h>
#include <graphics/TellusimMeshModel.h>
#include <platform/TellusimWindow.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCompute.h>
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
	if(!window.create("04 Hello Raster") || !window.setHidden(false)) return 1;
	window.setKeyboardPressedCallback([&](uint32_t key, uint32_t code) {
		if(key == Window::KeyEsc) window.stop();
	});
	window.setCloseClickedCallback([&]() { window.stop(); });
	
	// declarations
	#include "main.h"
	
	// scene size
	constexpr uint32_t grid_size = 48;
	constexpr uint32_t grid_height = 2;
	
	// mesh parameters
	constexpr uint32_t draw_group_size = 32;
	constexpr uint32_t raster_group_size = 128;
	constexpr uint32_t max_geometries = 2048;
	constexpr uint32_t max_attributes = 128;
	constexpr uint32_t max_primitives = 128;
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;			// projection matrix
		Matrix4x4f modelview;			// modelview matrix
		Vector4f planes[4];				// clipping planes
		Vector4f signs[4];				// clipping signs
		Vector4f camera;				// camera position
		float32_t projection_scale;		// projection scale
		float32_t surface_width;		// surface width
		float32_t surface_height;		// surface height
		float32_t time;
	};
	
	struct ClearParameters {
		uint32_t depth_value;			// depth value
		uint32_t color_value;			// color value
		uint32_t surface_width;			// surface width
		uint32_t surface_height;		// surface height
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// device info
	TS_LOGF(Message, "Device: %s\n", device.getName().get());
	
	// check compute shader support
	if(!device.hasShader(Shader::TypeCompute)) {
		TS_LOG(Error, "compute shader is not supported\n");
		return 0;
	}
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBAf32, 0, offsetof(Vertex, position), sizeof(Vertex));
	pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBAf32, 0, offsetof(Vertex, normal), sizeof(Vertex));
	
	// create draw pipeline
	Pipeline draw_pipeline = device.createPipeline();
	draw_pipeline.setTextureMask(0, Shader::MaskFragment);
	draw_pipeline.setColorFormat(window.getColorFormat());
	draw_pipeline.setDepthFormat(window.getDepthFormat());
	if(!draw_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!draw_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!draw_pipeline.create()) return 1;
	
	// create clear kernel
	Kernel clear_kernel = device.createKernel().setUniforms(1).setStorages(1, BindFlagFixed).setSurfaces(1);
	if(!clear_kernel.loadShaderGLSL("main.shader", "CLEAR_SHADER=1")) return 1;
	if(!clear_kernel.create()) return 1;
	
	// create draw kernel
	Kernel draw_kernel = device.createKernel().setUniforms(1).setStorages(5, BindFlagFixed);
	if(!draw_kernel.loadShaderGLSL("main.shader", "DRAW_SHADER=1; GROUP_SIZE=%uu", draw_group_size)) return 1;
	if(!draw_kernel.create()) return 1;
	
	// create raster kernel
	Kernel raster_kernel = device.createKernel().setUniforms(1).setStorages(6, BindFlagFixed).setSurfaces(1);
	if(!raster_kernel.loadShaderGLSL("main.shader", "RASTER_SHADER=1; GROUP_SIZE=%uu; MAX_VERTICES=%uu", raster_group_size, max_attributes)) return 1;
	if(!raster_kernel.create()) return 1;
	
	// create mesh
	if(!File::isFile("model.mesh")) {
		
		Async async;
		if(!async.init()) return 1;
		
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
		
		// create graph
		Mesh graph_mesh;
		TS_LOG(Message, "Creating Graph\n");
		MeshGraph::create(graph_mesh, subdiv_mesh, max_attributes, max_primitives, nullptr, &async);
		
		// save mesh
		TS_LOG(Message, "Saving Mesh\n");
		graph_mesh.save("model.mesh");
	}
	
	// load mesh
	Mesh mesh;
	if(!mesh.load("model.mesh") || mesh.getNumGeometries() > max_geometries) return 1;
	
	// create model
	MeshModel mesh_model;
	if(!mesh_model.create(device, pipeline, mesh, MeshModel::FlagIndices10 | MeshModel::FlagBufferStorage)) return 1;
	Buffer vertex_buffer = mesh_model.getVertexBuffer();
	Buffer index_buffer = mesh_model.getIndexBuffer();
	
	// create instances
	Array<Matrix4x3f> instance_parameters;
	instance_parameters.resize(grid_size * grid_size * grid_height);
	
	// create geometries
	Array<uint32_t> children_indices;
	Array<GeometryParameters> geometry_parameters(mesh.getNumGeometries());
	for(const MeshGeometry &geometry : mesh.getGeometries()) {
		
		uint32_t index = geometry.getIndex();
		GeometryParameters &parameters = geometry_parameters[index];
		
		// bounding box
		const BoundBoxf &bound_box = geometry.getBoundBox();
		parameters.bound_min.set(bound_box.min, 1.0f);
		parameters.bound_max.set(bound_box.max, 1.0f);
		
		// visibility error
		parameters.error = geometry.getVisibilityError();
		
		// parent indices
		parameters.parent_0 = (geometry.getParent0()) ? geometry.getParent0().getIndex() : Maxu32;
		parameters.parent_1 = (geometry.getParent1()) ? geometry.getParent1().getIndex() : Maxu32;
		
		// children indices
		parameters.num_children = geometry.getNumChildren();
		parameters.base_child = children_indices.size();
		for(const MeshGeometry &child : geometry.getChildren()) {
			children_indices.append(child.getIndex());
		}
		
		// vertices
		parameters.num_vertices = mesh_model.getNumGeometryVertices(index);
		parameters.base_vertex = mesh_model.getGeometryBaseVertex(index);
		
		// indices
		parameters.num_primitives = mesh_model.getNumGeometryIndices(index) / 3;
		parameters.base_primitive = mesh_model.getGeometryBaseIndex(index) / 3;
		
		// check geometry
		if(parameters.num_vertices > max_attributes || parameters.num_primitives > max_primitives) {
			TS_LOGF(Error, "%u %u\n", parameters.num_vertices, parameters.num_primitives);
			return 1;
		}
	}
	
	// create instances buffer
	Buffer instances_buffer = device.createBuffer(Buffer::FlagStorage, instance_parameters.bytes());
	if(!instances_buffer) return 1;
	
	// create geometries buffer
	Buffer geometries_buffer = device.createBuffer(Buffer::FlagStorage, geometry_parameters.get(), geometry_parameters.bytes());
	if(!geometries_buffer) return 1;
	
	// create children buffer
	Buffer children_buffer = device.createBuffer(Buffer::FlagStorage, children_indices.get(), children_indices.bytes());
	if(!children_buffer) return 1;
	
	// create batch buffer
	Buffer batch_buffer = device.createBuffer(Buffer::FlagStorage, sizeof(uint32_t) * instance_parameters.size() * max_geometries);
	if(!batch_buffer) return 1;
	
	// create indirect buffer
	Buffer indirect_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagIndirect, sizeof(Compute::DispatchIndirect));
	if(!indirect_buffer) return 1;
	
	// create target
	Target target = device.createTarget(window);
	
	// create query
	Query time_query;
	if(device.hasQuery(Query::TypeTime)) time_query = device.createQuery(Query::TypeTime);
	
	// create panel
	Panel panel(device);
	
	// compute surfaces
	Buffer depth_buffer;
	Texture color_surface;
	
	// print info
	TS_LOGF(Message, "Vertex: %s\n", String::fromBytes(vertex_buffer.getSize()).get());
	TS_LOGF(Message, "Index: %s\n", String::fromBytes(index_buffer.getSize()).get());
	
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
		instance_parameters.clear();
		float32_t offset = (grid_size - 1.0f) * 0.5f;
		for(uint32_t z = 0; z < grid_height; z++) {
			Matrix4x3f rotate = Matrix4x3f::rotateZ(time * (z * 16.0f - 8.0f)) * Matrix4x3f::rotateY(90.0f);
			for(uint32_t y = 0; y < grid_size; y++) {
				for(uint32_t x = 0; x < grid_size; x++) {
					Matrix4x3f translate = Matrix4x3f::translate((x - offset) * 4.0f, (y - offset) * 4.0f, z * 2.0f);
					instance_parameters.append(translate * rotate);
				}
			}
		}
		
		// update instances buffer
		if(!device.setBuffer(instances_buffer, instance_parameters.get(), instance_parameters.bytes())) return false;
		
		// clear indirect buffer
		Compute::DispatchIndirect indirect_data = { 0, 1, 1, 0 };
		if(!device.setBuffer(indirect_buffer, &indirect_data, sizeof(indirect_data))) return false;
		
		// flush buffers
		device.flushBuffers({ instances_buffer, indirect_buffer });
		
		// create surfaces
		uint32_t width = window.getWidth();
		uint32_t height = window.getHeight();
		if(window.getKeyboardKey('5')) { width = 1600; height = 900; }
		if(window.getKeyboardKey('6')) { width = 1920; height = 1080; }
		if(window.getKeyboardKey('7')) { width = 2560; height = 1440; }
		if(window.getKeyboardKey('8')) { width = 3840; height = 2160; }
		if(!color_surface || color_surface.getWidth() != width || color_surface.getHeight() != height) {
			device.releaseBuffer(depth_buffer);
			device.releaseTexture(color_surface);
			depth_buffer = device.createBuffer(Buffer::FlagStorage, sizeof(uint32_t) * width * height);
			color_surface = device.createTexture2D(FormatRu32, width, height, Texture::FlagSurface);
			if(!depth_buffer || !color_surface) return false;
		}
		
		{
			Compute compute = device.createCompute();
			
			// clear parameters
			ClearParameters clear_parameters;
			clear_parameters.depth_value = f32u32(0.0f).u;
			clear_parameters.color_value = (Color::gray * 0.25f).getRGBAu8();
			clear_parameters.surface_width = color_surface.getWidth();
			clear_parameters.surface_height = color_surface.getHeight();
			
			// dispatch clear kernel
			compute.setKernel(clear_kernel);
			compute.setUniform(0, clear_parameters);
			compute.setStorageBuffer(0, depth_buffer);
			compute.setSurfaceTexture(0, color_surface);
			compute.dispatch(color_surface);
			
			compute.barrier(depth_buffer);
			compute.barrier(color_surface);
			
			// common parameters
			CommonParameters common_parameters;
			float32_t offset = 1.0f - Tellusim::cos(time * 0.2f);
			common_parameters.camera = Matrix4x4f::rotateZ(time * 2.0f) * Vector4f(Vector3f(32.0f + offset * 24.0f, 0.0f, 8.0f + offset * 8.0f), 1.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)color_surface.getWidth() / color_surface.getHeight(), 0.1f, true);
			common_parameters.modelview = Matrix4x4f::lookAt(common_parameters.camera.xyz, Vector3f(0.0f, 0.0f, -16.0f), Vector3f::oneZ);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			common_parameters.projection_scale = Tellusim::abs(common_parameters.projection.m11) * color_surface.getHeight() * (1.0f / 6.0f);
			common_parameters.surface_width = (float32_t)color_surface.getWidth();
			common_parameters.surface_height = (float32_t)color_surface.getHeight();
			common_parameters.time = time;
			
			// clip planes
			BoundFrustumf bound_frustum(common_parameters.projection, common_parameters.modelview);
			for(uint32_t i = 0; i < 4; i++) {
				common_parameters.planes[i] = bound_frustum.planes[i];
				common_parameters.signs[i].x = (float32_t)bound_frustum.signs[i][0];
				common_parameters.signs[i].y = (float32_t)bound_frustum.signs[i][1];
				common_parameters.signs[i].z = (float32_t)bound_frustum.signs[i][2];
			}
			
			// lod control
			if(window.getKeyboardKey('1')) common_parameters.projection_scale = 0.0f;
			if(window.getKeyboardKey('2')) common_parameters.projection_scale = 1e6f;
			
			// begin query
			if(time_query) compute.beginQuery(time_query);
				
				// dispatch draw kernel
				compute.setKernel(draw_kernel);
				compute.setUniform(0, common_parameters);
				compute.setStorageBuffers(0, {
					instances_buffer,
					geometries_buffer,
					children_buffer,
					indirect_buffer,
					batch_buffer,
				});
				compute.dispatch(instance_parameters.size() * draw_group_size);
				
				compute.barrier({ indirect_buffer, batch_buffer });
				
				// dispatch raster kernel
				compute.setKernel(raster_kernel);
				compute.setUniform(0, common_parameters);
				compute.setStorageBuffers(0, {
					instances_buffer,
					geometries_buffer,
					batch_buffer,
					vertex_buffer,
					index_buffer,
					depth_buffer,
				});
				compute.setSurfaceTexture(0, color_surface);
				compute.setIndirectBuffer(indirect_buffer);
				compute.dispatchIndirect();
				
				compute.barrier(depth_buffer);
				compute.barrier(color_surface);
				
			// end query
			if(time_query) compute.endQuery(time_query);
		}
		
		// flush surface
		device.flushTexture(color_surface);
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// set pipeline
			command.setPipeline(draw_pipeline);
			command.setTexture(0, color_surface);
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

/*
 */
#if _ANDROID
	#include <system/TellusimAndroid.h>
	TS_DECLARE_ANDROID_NATIVE_ACTIVITY
#endif

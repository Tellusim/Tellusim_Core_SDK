// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <format/TellusimMesh.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCompute.h>
#include <platform/TellusimCommand.h>
#include <parallel/TellusimPrefixScan.h>
#include <parallel/TellusimRadixSort.h>
#include <parallel/TellusimSpatialTree.h>
#include <graphics/TellusimMeshModel.h>
#include <geometry/TellusimMeshRefine.h>
#include <geometry/TellusimSpatial.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::MeshTree", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// number of objects
	constexpr int32_t grid_size = 4;
	constexpr uint32_t num_instances = grid_size * 2 + 1;
	constexpr uint32_t num_instances2 = num_instances * num_instances;
	
	constexpr uint32_t group_size = 256;
	
	// structures
	struct Vertex {
		float32_t position[4];
		float32_t normal[4];
	};
	
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f imodelview;
		Vector4f camera;
		Vector4f light;
		uint32_t num_triangles;
		uint32_t trace_reflection;
		uint32_t cast_shadow;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check compute shader support
	if(!device.hasShader(Shader::TypeCompute)) {
		TS_LOG(Error, "compute shader is not supported\n");
		return 0;
	}
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setTextureMask(0, Shader::MaskFragment);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create vertex pipeline
	Pipeline vertex_pipeline = device.createPipeline();
	vertex_pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, offsetof(Vertex, position), sizeof(Vertex));
	vertex_pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, offsetof(Vertex, normal), sizeof(Vertex));
	
	// create bounds kernel
	Kernel bounds_kernel = device.createKernel().setUniforms(1).setStorages(3);
	if(!bounds_kernel.loadShaderGLSL("main.shader", "COMPUTE_BOUNDS_SHADER=1; GROUP_SIZE=%uu", group_size)) return 1;
	if(!bounds_kernel.create()) return 1;
	
	// create nodes kernel
	Kernel nodes_kernel = device.createKernel().setUniforms(1).setStorages(3);
	if(!nodes_kernel.loadShaderGLSL("main.shader", "COMPUTE_NODES_SHADER=1; GROUP_SIZE=%uu", group_size)) return 1;
	if(!nodes_kernel.create()) return 1;
	
	// create trace kernel
	Kernel trace_kernel = device.createKernel().setUniforms(2).setStorages(4).setSurfaces(1);
	if(!trace_kernel.loadShaderGLSL("main.shader", "COMPUTE_TRACE_SHADER=1; NUM_INSTANCES=%uu", num_instances2)) return 1;
	if(!trace_kernel.create()) return 1;
	
	// load mesh
	Mesh mesh, src_mesh;
	if(!src_mesh.load("model.glb")) return 1;
	if(!MeshRefine::subdiv(mesh, src_mesh, 5)) return 1;
	mesh.createBounds();
	mesh.createNormals();
	mesh.optimizeIndices();
	
	// create mesh model
	MeshModel vertex_model;
	if(!vertex_model.create(device, vertex_pipeline, mesh, MeshModel::DefaultFlags | MeshModel::FlagIndices32 | MeshModel::FlagBufferStorage)) return 1;
	Buffer vertex_buffer = vertex_model.getVertexBuffer();
	Buffer index_buffer = vertex_model.getIndexBuffer();
	
	// mesh info
	uint32_t num_vertices = vertex_model.getNumVertices();
	uint32_t num_triangles = vertex_model.getNumIndices() / 3;
	TS_LOGF(Message, "  Vertices: %s %s\n", String::fromNumber(num_vertices * num_instances2).get(), String::fromBytes(vertex_model.getVertexBuffer().getSize()).get());
	TS_LOGF(Message, "Primitives: %s %s\n", String::fromNumber(num_triangles * num_instances2).get(), String::fromBytes(vertex_model.getIndexBuffer().getSize()).get());
	TS_LOGF(Message, " Triangles: %u\n", num_triangles);
	TS_LOGF(Message, " Instances: %u\n", num_instances2);
	
	// create tree
	RadixSort radix_sort;
	PrefixScan prefix_scan;
	SpatialTree spatial_tree;
	if(!radix_sort.create(device, RadixSort::FlagsAll, prefix_scan, num_triangles, group_size)) return 1;
	if(!spatial_tree.create(device, SpatialTree::FlagsAllOptimize, radix_sort, num_triangles, group_size)) return 1;
	
	// create spatial buffer
	Buffer bottom_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagSource, sizeof(SpatialTree::Node) * num_triangles * 2);
	Buffer top_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagSource, sizeof(SpatialTree::Node) * num_instances2 * 2);
	if(!bottom_buffer || !top_buffer) return 1;
	
	// print buffer info
	TS_LOGF(Message, "  Blas: %s\n", String::fromBytes(bottom_buffer.getSize()).get());
	TS_LOGF(Message, "  Tlas: %s\n", String::fromBytes(top_buffer.getSize()).get());
	
	// create spatial tree
	{
		Compute compute = device.createCompute();
		
		// create triangle bounds
		compute.setKernel(bounds_kernel);
		compute.setUniform(0, num_triangles);
		compute.setStorageBuffers(0, { bottom_buffer, vertex_buffer, index_buffer });
		compute.dispatch(num_triangles);
		compute.barrier(bottom_buffer);
		
		// create bottom tree
		if(1) {
			
			// GPU builder
			spatial_tree.dispatch(compute, SpatialTree::HashXYZ10, bottom_buffer, 0, num_triangles, SpatialTree::FlagOptimize);
		}
		else {
			
			compute.clearPtr();
			
			// get nodes
			Array<Spatial::Node4f> bottom_nodes(num_triangles * 2);
			device.getBuffer(bottom_buffer, bottom_nodes.get(), bottom_nodes.bytes());
			
			// CPU builder
			Spatial::create<float32_t>(bottom_nodes.get(), num_triangles);
			Spatial::optimize<float32_t>(bottom_nodes.get(), num_triangles);
			device.setBuffer(bottom_buffer, bottom_nodes.get(), bottom_nodes.bytes());
			
			compute = device.createCompute();
		}
		
		// create nodes
		compute.setKernel(nodes_kernel);
		compute.setUniform(0, num_triangles);
		compute.setStorageBuffers(0, { bottom_buffer, vertex_buffer, index_buffer });
		compute.dispatch(num_triangles);
		compute.barrier(bottom_buffer);
	}
	
	// create query
	Query trace_query;
	if(device.hasQuery(Query::TypeTime)) {
		trace_query = device.createQuery(Query::TypeTime);
		if(!trace_query) return 1;
	}
	
	// compute surface
	Texture compute_surface;
	
	// create target
	Target target = device.createTarget(window);
	
	// create canvas
	Canvas canvas;
	
	// create controls
	ControlRoot root(canvas, true);
	
	ControlPanel left_panel(&root, 1, 0.0f, 8.0f);
	left_panel.setAlign(Control::AlignLeftTop);
	left_panel.setPosition(8.0f, -8.0f);
	
	ControlText info_text(&left_panel);
	info_text.setAlign(Control::AlignLeft);
	
	ControlPanel right_panel(&root, 1, 0.0f, 8.0f);
	right_panel.setAlign(Control::AlignRightTop);
	right_panel.setPosition(-8.0f, -8.0f);
	
	ControlCheck trace_reflection_check(&right_panel, "Trace Reflection", true);
	trace_reflection_check.setAlign(Control::AlignLeft);
	
	ControlCheck cast_shadow_check(&right_panel, "Cast Shadow", true);
	cast_shadow_check.setAlign(Control::AlignLeft);
	
	ControlCheck animation_check(&right_panel, "Animation", true);
	animation_check.setAlign(Control::AlignLeft);
	
	float32_t animation_time = 0.0f;
	float32_t old_animation_time = 0.0f;
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// FPS counter
		if(fps > 0.0f || frame_counter == 0) {
			String trace_time = String::fromTime(((bool)trace_query && trace_query.isAvailable()) ? trace_query.getTime() : 0);
			info_text.setText(String::format("FPS: %.1f\nTrace: %s", fps, trace_time.get()));
		}
		
		// update keyboard
		if(window.getKeyboardKey('r', true)) trace_reflection_check.switchChecked();
		if(window.getKeyboardKey('s', true)) cast_shadow_check.switchChecked();
		if(window.getKeyboardKey(' ', true)) animation_check.switchChecked();
		
		// update controls
		update_controls(window, root);
		canvas.create(device, target);
		
		// animation time
		if(animation_check.isChecked()) animation_time += time - old_animation_time;
		old_animation_time = time;
		
		// common parameters
		CommonParameters common_parameters;
		common_parameters.camera = Vector4f(16.0f, 0.0f, 1.0f, 0.0f);
		common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, true);
		common_parameters.imodelview = inverse(Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f(0.0f, 0.0f, -4.0f), Vector3f::oneZ));
		common_parameters.light = Vector4f(32.0f, 0.0f, 16.0f, 0.0f);
		common_parameters.num_triangles = num_triangles;
		common_parameters.trace_reflection = trace_reflection_check.isChecked();
		common_parameters.cast_shadow = cast_shadow_check.isChecked();
		
		// transform parameters
		Array<Matrix4x3f> itransforms;
		Array<Spatial::Node4f> top_nodes;
		itransforms.reserve(num_instances2);
		top_nodes.reserve(num_instances2 * 2);
		top_nodes.resize(num_instances2);
		BoundBoxf bound_box = BoundBoxf(mesh.getBoundBox());
		for(int32_t i = 0, y = -grid_size; y <= grid_size; y++) {
			for(int32_t x = -grid_size; x <= grid_size; x++, i++) {
				Matrix4x3f offset = Matrix4x3f::translate(x * 3.2f, y * 3.2f, 0.0f);
				Matrix4x3f transform = offset * Matrix4x3f::rotateZ(animation_time * 32.0f + y * 2715.53f) * Matrix4x3f::rotateX(animation_time * 16.0f + x * 9774.37f);
				itransforms.append(inverse(transform));
				BoundBoxf bb = transform * bound_box;
				Spatial::Node4f &node = top_nodes.append();
				node.bound.min = Vector4f(bb.min, 1.0f);
				node.bound.max = Vector4f(bb.max, 1.0f);
			}
		}
		
		// create top tree
		Spatial::create<float32_t>(top_nodes.get(), num_instances2);
		Spatial::optimize<float32_t>(top_nodes.get(), num_instances2);
		device.setBuffer(top_buffer, top_nodes.get(), top_nodes.bytes());
		
		// resize compute surface
		if(!compute_surface || compute_surface.getWidth() != window.getWidth() || compute_surface.getHeight() != window.getHeight()) {
			window.finish();
			compute_surface = device.createTexture2D(FormatRGBAu8n, window.getWidth(), window.getHeight(), Texture::FlagSurface);
			TS_LOGF(Message, "Resize: %ux%u\n", window.getWidth(), window.getHeight());
		}
		
		{
			// create command list
			Compute compute = device.createCompute();
			
			if(trace_query) compute.beginQuery(trace_query);
			
			// dispatch trace kernel
			compute.setKernel(trace_kernel);
			compute.setUniform(0, common_parameters);
			compute.setUniformData(1, itransforms.get(), itransforms.bytes());
			compute.setSurfaceTexture(0, compute_surface);
			compute.setStorageBuffers(0, { top_buffer, bottom_buffer, vertex_buffer, index_buffer });
			compute.dispatch(compute_surface);
			compute.barrier(compute_surface);
			
			if(trace_query) compute.endQuery(trace_query);
		}
		
		// flush surface
		device.flushTexture(compute_surface);
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// draw surface
			command.setPipeline(pipeline);
			command.setTexture(0, compute_surface);
			command.drawArrays(3);
			
			// draw canvas
			canvas.draw(command, target);
		}
		target.end();
		
		if(!window.present()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}

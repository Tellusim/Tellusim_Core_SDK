// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <core/TellusimLog.h>
#include <format/TellusimMesh.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimTraversal.h>
#include <platform/TellusimCompute.h>
#include <platform/TellusimCommand.h>
#include <graphics/TellusimMeshModel.h>
#include <geometry/TellusimMeshRefine.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::MeshTracing", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// number of objects
	constexpr int32_t grid_size = 4;
	constexpr uint32_t num_instances = grid_size * 2 + 1;
	constexpr uint32_t num_instances2 = num_instances * num_instances;
	
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
		uint32_t trace_reflection;
		uint32_t cast_shadow;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check ray tracing support
	const Device::Features &features = device.getFeatures();
	if(!features.computeTracing && !features.rayTracing) {
		TS_LOG(Error, "ray tracing is not supported\n");
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
	
	// create trace kernel
	Kernel trace_kernel;
	if(features.computeTracing) {
		trace_kernel = device.createKernel().setUniforms(1).setStorages(2).setSurfaces(1).setTracings(1);
		if(!trace_kernel.loadShaderGLSL("main.shader", "COMPUTE_SHADER=1; NUM_INSTANCES=%uu", num_instances2)) return 1;
		if(!trace_kernel.create()) return 1;
	}
	
	// create trace traversal
	Traversal trace_traversal;
	if(features.rayTracing && features.recursionDepth > 1) {
		trace_traversal = device.createTraversal();
		trace_traversal.setUniformMask(0, Shader::MaskAll);
		trace_traversal.setStorageMasks(0, 2, Shader::MaskAll);
		trace_traversal.setSurfaceMask(0, Shader::MaskRayGen);
		trace_traversal.setTracingMask(0, Shader::MaskRayGen | Shader::MaskClosest);
		trace_traversal.setRecursionDepth(min(device.getFeatures().recursionDepth, 2u));
		if(!trace_traversal.loadShaderGLSL(Shader::TypeRayGen, "main.shader", "RAYGEN_SHADER=1")) return 1;
		if(!trace_traversal.loadShaderGLSL(Shader::TypeRayMiss, "main.shader", "RAYMISS_SHADER=1")) return 1;
		if(!trace_traversal.loadShaderGLSL(Shader::TypeClosest, "main.shader", "CLOSEST_SHADER=1")) return 1;
		if(!trace_traversal.loadShaderGLSL(Shader::TypeRayMiss, "main.shader", "RAYMISS_REFLECTION_SHADER=1")) return 1;
		if(!trace_traversal.loadShaderGLSL(Shader::TypeClosest, "main.shader", "CLOSEST_REFLECTION_SHADER=1")) return 1;
		if(!trace_traversal.loadShaderGLSL(Shader::TypeRayMiss, "main.shader", "RAYMISS_SHADOW_SHADER=1")) return 1;
		if(!trace_traversal.create()) return 1;
	}
	
	// load mesh
	Mesh mesh, src_mesh;
	if(!src_mesh.load("model.glb")) return 1;
	if(!MeshRefine::subdiv(mesh, src_mesh, 5)) return 1;
	mesh.createNormals();
	mesh.optimizeIndices();
	
	// create vertex model
	MeshModel vertex_model;
	if(!vertex_model.create(device, vertex_pipeline, mesh, MeshModel::DefaultFlags | MeshModel::FlagIndices32 | MeshModel::FlagBufferStorage | MeshModel::FlagBufferTracing)) return 1;
	Buffer vertex_buffer = vertex_model.getVertexBuffer();
	Buffer index_buffer = vertex_model.getIndexBuffer();
	
	// mesh info
	uint32_t num_vertices = vertex_model.getNumVertices();
	uint32_t num_triangles = vertex_model.getNumIndices() / 3;
	TS_LOGF(Message, "  Vertices: %s %s\n", String::fromNumber(num_vertices * num_instances2).get(), String::fromBytes(vertex_model.getVertexBuffer().getSize()).get());
	TS_LOGF(Message, "Primitives: %s %s\n", String::fromNumber(num_triangles * num_instances2).get(), String::fromBytes(vertex_model.getIndexBuffer().getSize()).get());
	TS_LOGF(Message, " Instances: %u\n", num_instances2);
	
	// bottom tracing
	Tracing bottom_tracing = device.createTracing();
	bottom_tracing.addVertexBuffer(vertex_model.getNumGeometryVertices(0), vertex_pipeline.getAttributeFormat(0), vertex_model.getVertexBufferStride(0), vertex_buffer);
	bottom_tracing.addIndexBuffer(vertex_model.getNumIndices(), vertex_model.getIndexFormat(), index_buffer);
	if(!bottom_tracing.create(Tracing::TypeTriangle, Tracing::FlagCompact | Tracing::FlagFastTrace)) return 1;
	
	// create scratch buffer
	Buffer scratch_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagScratch, bottom_tracing.getBuildSize() + 1024 * 1024);
	if(!scratch_buffer) return 1;
	
	// build bottom tracing
	if(!device.buildTracing(bottom_tracing, scratch_buffer, Tracing::FlagCompact)) return 1;
	device.flushTracing(bottom_tracing);
	
	// create instances buffer
	Tracing::Instance instance = {};
	instance.mask = 0xff;
	instance.tracing = &bottom_tracing;
	Array<Tracing::Instance> instances(num_instances2, instance);
	Buffer instances_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagTracing, instances.get(), instances.bytes());
	if(!instances_buffer) return 1;
	
	// create top tracing
	Tracing top_tracing = device.createTracing(num_instances2, instances_buffer);
	if(!top_tracing) return 1;
	
	// print tracing info
	TS_LOGF(Message, "  Blas: %s/%s\n", String::fromBytes(bottom_tracing.getMemory()).get(), String::fromBytes(bottom_tracing.getBuildSize()).get());
	TS_LOGF(Message, "  Tlas: %s/%s\n", String::fromBytes(top_tracing.getMemory()).get(), String::fromBytes(top_tracing.getBuildSize()).get());
	
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
	
	ControlCheck trace_traversal_check(&right_panel, "Trace Traversal", !trace_kernel);
	trace_traversal_check.setDisabled(!trace_kernel || !trace_traversal);
	trace_traversal_check.setAlign(Control::AlignLeft);
	
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
		if(window.getKeyboardKey('t', true) && trace_traversal) trace_traversal_check.switchChecked();
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
		common_parameters.trace_reflection = trace_reflection_check.isChecked();
		common_parameters.cast_shadow = cast_shadow_check.isChecked();
		
		// instance parameters
		for(int32_t i = 0, y = -grid_size; y <= grid_size; y++) {
			for(int32_t x = -grid_size; x <= grid_size; x++, i++) {
				Matrix4x3f offset = Matrix4x3f::translate(x * 3.2f, y * 3.2f, 0.0f);
				Matrix4x3f transform = offset * Matrix4x3f::rotateZ(animation_time * 32.0f + y * 2715.53f) * Matrix4x3f::rotateX(animation_time * 16.0f + x * 9774.37f);
				transform.get(instances[i].transform);
			}
		}
		
		// build top acceleration structure
		if(!device.setTracing(top_tracing, instances.get(), instances.size())) return false;
		if(!device.buildTracing(top_tracing, scratch_buffer)) return false;
		device.flushTracing(top_tracing);
		
		// resize compute surface
		if(!compute_surface || compute_surface.getWidth() != window.getWidth() || compute_surface.getHeight() != window.getHeight()) {
			window.finish();
			compute_surface = device.createTexture2D(FormatRGBAu8n, window.getWidth(), window.getHeight(), Texture::FlagSurface);
			TS_LOGF(Message, "Resize: %ux%u\n", window.getWidth(), window.getHeight());
		}
		
		// raytracer
		{
			// create command list
			Compute compute = device.createCompute();
			
			if(trace_query) compute.beginQuery(trace_query);
			
			// trace traversal
			if(trace_traversal && trace_traversal_check.isChecked()) compute.setTraversal(trace_traversal);
			else compute.setKernel(trace_kernel);
			compute.setUniform(0, common_parameters);
			compute.setSurfaceTexture(0, compute_surface);
			compute.setStorageBuffer(0, vertex_buffer);
			compute.setStorageBuffer(1, index_buffer);
			compute.setTracing(0, top_tracing);
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

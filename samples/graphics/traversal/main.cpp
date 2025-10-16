// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <format/TellusimMesh.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimTraversal.h>
#include <platform/TellusimCompute.h>
#include <platform/TellusimCommand.h>
#include <geometry/TellusimMeshRefine.h>
#include <graphics/TellusimMeshModel.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Traversal", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// scene size
	constexpr int32_t grid_size = 3;
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
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check ray tracing support
	if(!device.getFeatures().rayTracing) {
		TS_LOG(Error, "ray tracing is not supported\n");
		return 0;
	}
	if(device.getFeatures().recursionDepth == 1) {
		TS_LOG(Error, "ray tracing recursion is not supported\n");
	}
	
	// shader macros
	Shader::setMacro("RECURSION_DEPTH", device.getFeatures().recursionDepth);
	
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
	
	// create tracing traversal
	Traversal tracing_traversal = device.createTraversal();
	tracing_traversal.setUniformMask(0, Shader::MaskAll);
	tracing_traversal.setStorageMasks(0, 4, Shader::MaskAll);
	tracing_traversal.setSurfaceMask(0, Shader::MaskRayGen);
	tracing_traversal.setTracingMask(0, Shader::MaskRayGen | Shader::MaskClosest);
	tracing_traversal.setRecursionDepth(min(device.getFeatures().recursionDepth, 2u));
	if(!tracing_traversal.loadShaderGLSL(Shader::TypeRayGen, "main.shader", "RAYGEN_SHADER=1")) return 1;
	if(!tracing_traversal.loadShaderGLSL(Shader::TypeRayMiss, "main.shader", "RAYMISS_SHADER=1")) return 1;
	if(!tracing_traversal.loadShaderGLSL(Shader::TypeClosest, "main.shader", "CLOSEST_MODEL_SHADER=1")) return 1;
	if(!tracing_traversal.loadShaderGLSL(Shader::TypeClosest, "main.shader", "CLOSEST_PLANE_SHADER=1")) return 1;
	if(!tracing_traversal.loadShaderGLSL(Shader::TypeRayMiss, "main.shader", "RAYMISS_REFLECTION_SHADER=1")) return 1;
	if(!tracing_traversal.loadShaderGLSL(Shader::TypeClosest, "main.shader", "CLOSEST_MODEL_REFLECTION_SHADER=1")) return 1;
	if(!tracing_traversal.loadShaderGLSL(Shader::TypeClosest, "main.shader", "CLOSEST_PLANE_REFLECTION_SHADER=1")) return 1;
	if(!tracing_traversal.loadShaderGLSL(Shader::TypeRayMiss, "main.shader", "RAYMISS_SHADOW_SHADER=1")) return 1;
	if(!tracing_traversal.create()) return 1;
	
	// load model mesh
	Mesh mesh, src_mesh;
	if(!src_mesh.load("model.glb")) return 1;
	if(!MeshRefine::subdiv(mesh, src_mesh, 5)) return 1;
	mesh.createNormals();
	mesh.optimizeIndices(32);
	
	// create model geometry
	MeshModel model_geometry;
	if(!model_geometry.create(device, vertex_pipeline, mesh, MeshModel::DefaultFlags | MeshModel::FlagIndices32 | MeshModel::FlagBufferStorage | MeshModel::FlagBufferTracing)) return 1;
	Buffer model_vertex_buffer = model_geometry.getVertexBuffer();
	Buffer model_index_buffer = model_geometry.getIndexBuffer();
	
	// create model tracing
	Tracing model_tracing = device.createTracing();
	model_tracing.addVertexBuffer(model_geometry.getNumGeometryVertices(0), vertex_pipeline.getAttributeFormat(0), model_geometry.getVertexBufferStride(0), model_vertex_buffer);
	model_tracing.addIndexBuffer(model_geometry.getNumIndices(), model_geometry.getIndexFormat(), model_index_buffer);
	if(!model_tracing.create(Tracing::TypeTriangle, Tracing::FlagCompact | Tracing::FlagFastTrace)) return 1;
	
	// create scratch buffer
	Buffer scratch_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagScratch, model_tracing.getBuildSize() * 2 + 1024 * 8);
	if(!scratch_buffer) return 1;
	
	// build model tracing
	if(!device.buildTracing(model_tracing, scratch_buffer, Tracing::FlagCompact)) return 1;
	device.flushTracing(model_tracing);
	
	// load plane mesh
	if(!mesh.load("plane.glb")) return 1;
	
	// create plane geometry
	MeshModel plane_geometry;
	if(!plane_geometry.create(device, vertex_pipeline, mesh, MeshModel::DefaultFlags | MeshModel::FlagIndices32 | MeshModel::FlagBufferStorage | MeshModel::FlagBufferTracing)) return 1;
	Buffer plane_vertex_buffer = plane_geometry.getVertexBuffer();
	Buffer plane_index_buffer = plane_geometry.getIndexBuffer();
	
	// create plane tracing
	Tracing plane_tracing = device.createTracing();
	plane_tracing.addVertexBuffer(plane_geometry.getNumGeometryVertices(0), vertex_pipeline.getAttributeFormat(0), plane_geometry.getVertexBufferStride(0), plane_vertex_buffer);
	plane_tracing.addIndexBuffer(plane_geometry.getNumIndices(), plane_geometry.getIndexFormat(), plane_index_buffer);
	if(!plane_tracing.create(Tracing::TypeTriangle, Tracing::FlagCompact | Tracing::FlagFastTrace)) return 1;
	
	// build plane tracing
	if(!device.buildTracing(plane_tracing, scratch_buffer, model_tracing.getBuildSize(), Tracing::FlagCompact)) return 1;
	device.flushTracing(plane_tracing);
	
	// create instances
	Tracing::Instance instance = {};
	Matrix4x3f::identity.get(instance.transform);
	instance.mask = 0xff;
	
	// model instances
	instance.tracing = &model_tracing;
	Array<Tracing::Instance> instances(num_instances2, instance);
	
	// plane instance
	instance.offset = 1;
	instance.tracing = &plane_tracing;
	instances.append(instance);
	
	// create instances buffer
	Buffer instances_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagTracing, Tracing::InstanceSize * (num_instances2 + 1));
	if(!instances_buffer) return 1;
	
	// create instance tracing
	Tracing instance_tracing = device.createTracing(num_instances2, instances_buffer);
	if(!instance_tracing) return 1;
	
	// create query
	Query trace_query;
	if(device.hasQuery(Query::TypeTime)) {
		trace_query = device.createQuery(Query::TypeTime);
		if(!trace_query) return 1;
	}
	
	// tracing surface
	Texture surface;
	
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
		if(fps > 0.0f) {
			String trace_time = String::fromTime((trace_query && trace_query.isAvailable()) ? trace_query.getTime() : 0);
			window.setTitle(String::format("%s %.1f FPS %s", title.get(), fps, trace_time.get()));
		}
		
		// common parameters
		CommonParameters common_parameters;
		common_parameters.camera = Matrix4x4f::rotateZ(sin(time) * 4.0f) * Vector4f(16.0f, 0.0f, 8.0f, 0.0f);
		common_parameters.projection = Matrix4x4f::perspective(70.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, true);
		common_parameters.imodelview = Matrix4x4f::placeTo(Vector3f(common_parameters.camera), Vector3f(0.0f, 0.0f, -3.0f), Vector3f::oneZ);
		common_parameters.light = Vector4f(12.0f, 0.0f, 6.0f, 0.0f);
		
		// instance parameters
		for(int32_t i = 0, y = -grid_size; y <= grid_size; y++) {
			for(int32_t x = -grid_size; x <= grid_size; x++, i++) {
				Matrix4x3f translate = Matrix4x3f::translate(x * 4.0f, y * 4.0f, 4.0f);
				Matrix4x3f rotate = Matrix4x3f::rotateZ(time * 32.0f) * Matrix4x3f::rotateX(90.0f);
				Matrix4x3f scale = Matrix4x3f::scale(sin(time + i) * 0.2f + 0.8f);
				(translate * rotate * scale).get(instances[i].transform);
			}
		}
		
		// build instance tracing
		if(!device.setTracing(instance_tracing, instances.get(), instances.size())) return false;
		if(!device.buildTracing(instance_tracing, scratch_buffer)) return false;
		device.flushTracing(instance_tracing);
		
		// create surface
		uint32_t width = window.getWidth();
		uint32_t height = window.getHeight();
		if(!surface || surface.getWidth() != width || surface.getHeight() != height) {
			window.finish();
			surface = device.createTexture2D(FormatRGBAu8n, width, height, Texture::FlagSurface);
		}
		
		// trace scene
		{
			// create command list
			Compute compute = device.createCompute();
			
			if(trace_query) compute.beginQuery(trace_query);
			
			// dispatch tracing traversal
			compute.setTraversal(tracing_traversal);
			compute.setUniform(0, common_parameters);
			compute.setSurfaceTexture(0, surface);
			compute.setStorageBuffers(0, { model_vertex_buffer, plane_vertex_buffer, model_index_buffer, plane_index_buffer });
			compute.setTracing(0, instance_tracing);
			compute.dispatch(surface);
			compute.barrier(surface);
			
			if(trace_query) compute.endQuery(trace_query);
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
		}
		target.end();
		
		if(!window.present()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}

// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <format/TellusimMesh.h>
#include <math/TellusimRandom.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCompute.h>
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
	String title = String::format("%s Tellusim::SkinnedTracing", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// number of objects
	constexpr uint32_t num_instances = 9;
	constexpr uint32_t num_instances2 = num_instances * num_instances;
	
	constexpr uint32_t group_size = 256;
	
	// structures
	struct SkinnedVertex {
		float32_t position[3];
		float32_t normal[3];
		float32_t texcoord[2];
		float32_t tangent[4];
		float32_t weights[4];
		uint32_t joints[4];
	};
	
	struct Vertex {
		float32_t position[3];
		float32_t normal[3];
		float32_t texcoord[2];
		float32_t tangent[4];
	};
	
	struct VerticesParameters {
		uint32_t num_joints;
		uint32_t num_vertices;
		uint32_t num_instances;
	};
	
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f imodelview;
		Vector4f camera;
		Vector4f light;
		uint32_t num_vertices;
		uint32_t body_triangles;
		uint32_t cast_shadow;
		float32_t time;
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
	
	// create vertices kernel
	Kernel vertices_kernel = device.createKernel().setUniforms(1).setStorages(3);
	if(!vertices_kernel.loadShaderGLSL("main.shader", "COMPUTE_VERTICES_SHADER=1; GROUP_SIZE=%uu", group_size)) return 1;
	if(!vertices_kernel.create()) return 1;
	
	// create trace kernel
	Kernel trace_kernel = device.createKernel().setSamplers(1).setTextures(2).setSurfaces(1).setUniforms(1).setStorages(2).setTracings(1);
	if(!trace_kernel.loadShaderGLSL("main.shader", "COMPUTE_TRACE_SHADER=1; NUM_INSTANCES=%uu", num_instances2)) return 1;
	if(!trace_kernel.create()) return 1;
	
	// create vertex pipeline
	Pipeline vertex_pipeline = device.createPipeline();
	vertex_pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, offsetof(SkinnedVertex, position), sizeof(SkinnedVertex));
	vertex_pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, offsetof(SkinnedVertex, normal), sizeof(SkinnedVertex));
	vertex_pipeline.addAttribute(Pipeline::AttributeTexCoord, FormatRGf32, 0, offsetof(SkinnedVertex, texcoord), sizeof(SkinnedVertex));
	vertex_pipeline.addAttribute(Pipeline::AttributeTangent, FormatRGBAf32, 0, offsetof(SkinnedVertex, tangent), sizeof(SkinnedVertex));
	vertex_pipeline.addAttribute(Pipeline::AttributeWeights, FormatRGBAf32, 0, offsetof(SkinnedVertex, weights), sizeof(SkinnedVertex));
	vertex_pipeline.addAttribute(Pipeline::AttributeJoints, FormatRGBAu32, 0, offsetof(SkinnedVertex, joints), sizeof(SkinnedVertex));
	
	// load mesh
	Mesh mesh;
	if(!mesh.load("model.glb")) return 1;
	if(!mesh.getNumGeometries()) return 1;
	if(!mesh.getNumAnimations()) return 1;
	mesh.setBasis(Mesh::BasisZUpRight);
	mesh.createTangents();
	mesh.optimizeAttributes();
	mesh.optimizeIndices();
	
	// create mesh model
	MeshModel vertex_model;
	MeshGeometry geometry = mesh.getGeometry(0);
	if(!vertex_model.create(device, vertex_pipeline, geometry, MeshModel::DefaultFlags | MeshModel::FlagIndices32 | MeshModel::FlagBufferStorage | MeshModel::FlagBufferTracing)) return 1;
	Buffer model_vertex_buffer = vertex_model.getVertexBuffer();
	Buffer index_buffer = vertex_model.getIndexBuffer();
	
	// mesh info
	uint32_t num_joints = geometry.getNumJoints();
	uint32_t num_vertices = vertex_model.getNumVertices();
	uint32_t num_triangles = vertex_model.getNumIndices() / 3;
	TS_LOGF(Message, "  Vertices: %s %s\n", String::fromNumber(num_vertices * num_instances2).get(), String::fromBytes(vertex_model.getVertexBuffer().getSize()).get());
	TS_LOGF(Message, "Primitives: %s %s\n", String::fromNumber(num_triangles * num_instances2).get(), String::fromBytes(vertex_model.getIndexBuffer().getSize()).get());
	TS_LOGF(Message, " Triangles: %u\n", num_triangles);
	TS_LOGF(Message, " Instances: %u\n", num_instances2);
	
	// create spatial buffers
	Buffer joints_buffer = device.createBuffer(Buffer::FlagStorage, sizeof(Matrix4x3f) * num_joints * num_instances2);
	Buffer vertex_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagTracing, sizeof(Vertex) * num_vertices * num_instances2);
	
	// print buffer info
	TS_LOGF(Message, "  Joints: %s\n", String::fromBytes(joints_buffer.getSize()).get());
	TS_LOGF(Message, "Vertices: %s\n", String::fromBytes(vertex_buffer.getSize()).get());
	
	// bottom tracings
	size_t bottom_build_size = 0;
	size_t bottom_tracing_size = 0;
	Array<Tracing> bottom_tracings;
	for(uint32_t i = 0; i < num_instances2; i++) {
		uint32_t base_vertex = vertex_model.getNumGeometryVertices(0) * i;
		Tracing bottom_tracing = device.createTracing();
		bottom_tracing.addVertexBuffer(vertex_model.getNumGeometryVertices(0), FormatRGBf32, sizeof(Vertex), vertex_buffer, sizeof(Vertex) * base_vertex);
		bottom_tracing.addIndexBuffer(vertex_model.getNumIndices(), vertex_model.getIndexFormat(), index_buffer);
		if(!bottom_tracing.create(Tracing::TypeTriangle, Tracing::FlagUpdate | Tracing::FlagFastBuild)) return 1;
		bottom_tracings.append(bottom_tracing);
		bottom_build_size += bottom_tracing.getBuildSize();
		bottom_tracing_size += bottom_tracing.getMemory();
	}
	
	// create scratch buffer
	Buffer scratch_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagScratch, bottom_build_size + 1024 * 1024);
	if(!scratch_buffer) return 1;
	
	// create instances buffer
	Array<Tracing::Instance> instances;
	float32_t step = 18.0f / num_instances;
	for(uint32_t i = 0, y = 0; y < num_instances; y++) {
		for(uint32_t x = 0; x < num_instances; x++, i++) {
			Tracing::Instance &instance = instances.append();
			instance.mask = 0xff;
			instance.tracing = &bottom_tracings[i];
			Matrix4x3f offset = Matrix4x3f::translate(x * step, y * step, 0.0f);
			Matrix4x3f transform = offset * Matrix4x3f::rotateZ(225.0f);
			transform.get((float32_t*)instance.transform);
		}
	}
	Buffer instances_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagTracing, instances.get(), instances.bytes());
	if(!instances_buffer) return 1;
	
	// create top tracing
	Tracing top_tracing = device.createTracing(num_instances2, instances_buffer);
	if(!top_tracing) return 1;
	
	// print tracing info
	TS_LOGF(Message, "  Blas: %s/%s\n", String::fromBytes(bottom_tracing_size).get(), String::fromBytes(bottom_build_size).get());
	TS_LOGF(Message, "  Tlas: %s/%s\n", String::fromBytes(top_tracing.getMemory()).get(), String::fromBytes(top_tracing.getBuildSize()).get());
	
	// create sampler
	Sampler sampler = device.createSampler(Sampler::FilterLinear, Sampler::WrapModeRepeat);
	if(!sampler) return 1;
	
	// create textures
	Texture noise_texture = device.loadTexture("noise.jpg");
	Texture model_texture = device.loadTexture("model.jpg");
	if(!noise_texture || !model_texture) return 1;
	
	// create query
	Query vertex_query;
	Query build_query;
	Query trace_query;
	if(device.hasQuery(Query::TypeTime)) {
		vertex_query = device.createQuery(Query::TypeTime);
		build_query = device.createQuery(Query::TypeTime);
		trace_query = device.createQuery(Query::TypeTime);
		if(!vertex_query || !build_query || !trace_query) return 1;
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
	
	ControlCheck update_check(&right_panel, "Update Only");
	update_check.setAlign(Control::AlignLeft);
	
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
		
		using Tellusim::pow;
		
		Window::update();
		
		if(!window.render()) return false;
		
		// FPS counter
		if(fps > 0.0f || frame_counter == 0) {
			String vertex_time = String::fromTime(((bool)vertex_query && vertex_query.isAvailable()) ? vertex_query.getTime() : 0);
			String build_time = String::fromTime(((bool)build_query && build_query.isAvailable()) ? build_query.getTime() : 0);
			String trace_time = String::fromTime(((bool)trace_query && trace_query.isAvailable()) ? trace_query.getTime() : 0);
			info_text.setText(String::format("FPS: %.1f\nVertex: %s\nBuild: %s\nTrace: %s", fps, vertex_time.get(), build_time.get(), trace_time.get()));
		}
		
		// update keyboard
		if(window.getKeyboardKey('u', true)) update_check.switchChecked();
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
		common_parameters.camera = Vector4f(-2.2f, -2.2f, 3.0f, 0.0f);
		common_parameters.projection = Matrix4x4f::perspective(50.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, true);
		common_parameters.imodelview = inverse(Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f(0.0f, 0.0f, 1.5f), Vector3f::oneZ));
		common_parameters.light = Vector4f(-8.0f, 4.0f, 8.0f, 0.0f);
		common_parameters.num_vertices = num_vertices;
		common_parameters.body_triangles = vertex_model.getNumMaterialIndices(0, 0) / 3;
		common_parameters.cast_shadow = cast_shadow_check.isChecked();
		common_parameters.time = time;
		
		// joint parameters
		if(animation_check.isChecked() || frame_counter == 0) {
			Random<int32_t> random(7);
			float32_t scale = pow(9.0f / num_instances, 0.9f);
			Array<Matrix4x3f> joints_data(num_joints * num_instances2);
			float64_t offset = (pause && window.getKeyboardKey('u')) ? 1.3 : 0.0;
			for(uint32_t i = 0, y = 0; y < num_instances; y++) {
				for(uint32_t x = 0; x < num_instances; x++, i++) {
					if(i < 128) {
						MeshAnimation animation = mesh.getAnimation((i + 12) % mesh.getNumAnimations());
						animation.setTime(animation_time * 0.7 + offset + random.getf32(3.0f, 9.0f), Matrix4x3d::scale(Vector3d(scale)));
						for(uint32_t j = 0; j < num_joints; j++) {
							const MeshJoint joint = geometry.getJoint(j);
							joints_data[num_joints * i + j] = Matrix4x3f(animation.getGlobalTransform(joint)) * joint.getITransform();
						}
					} else {
						const Matrix4x3f *src = joints_data.get() + num_joints * random.geti32(0, 127);
						Matrix4x3f *dest = joints_data.get() + num_joints * i;
						memcpy(dest, src, sizeof(Matrix4x3f) * num_joints);
					}
				}
			}
			device.setBuffer(joints_buffer, joints_data.get(), joints_data.bytes());
			device.flushBuffer(joints_buffer);
		}
		
		// create compute surface
		if(!compute_surface || compute_surface.getWidth() != window.getWidth() || compute_surface.getHeight() != window.getHeight()) {
			window.finish();
			compute_surface = device.createTexture2D(FormatRGBAu8n, window.getWidth(), window.getHeight(), Texture::FlagSurface);
			TS_LOGF(Message, "Resize: %ux%u\n", window.getWidth(), window.getHeight());
		}
		
		{
			// create command list
			Compute compute = device.createCompute();
			
			VerticesParameters vertices_parameters;
			vertices_parameters.num_joints = num_joints;
			vertices_parameters.num_vertices = num_vertices;
			vertices_parameters.num_instances = num_instances2;
			
			// transform vertices
			if(vertex_query) compute.beginQuery(vertex_query);
			
			compute.setKernel(vertices_kernel);
			compute.setUniform(0, vertices_parameters);
			compute.setStorageBuffer(0, vertex_buffer);
			compute.setStorageBuffer(1, model_vertex_buffer);
			compute.setStorageBuffer(2, joints_buffer);
			compute.dispatch(num_vertices * num_instances2);
			compute.barrier(vertex_buffer);
			
			if(vertex_query) compute.endQuery(vertex_query);
		}
		
		{
			if(build_query) device.beginQuery(build_query);
			
			// build bottom tracings
			Tracing::Flags bottom_flags = Tracing::FlagFastBuild;
			if(update_check.isChecked()) bottom_flags |= Tracing::FlagUpdate;
			if(!device.buildTracings(bottom_tracings, scratch_buffer, bottom_flags)) return false;
			device.flushTracings(bottom_tracings);
			
			if(build_query) device.endQuery(build_query);
		}
		
		{
			// build top acceleration structure
			if(!device.setTracing(top_tracing, instances.get(), instances.size())) return false;
			if(!device.buildTracing(top_tracing, scratch_buffer)) return false;
			device.flushTracing(top_tracing);
		}
		
		// raytracer
		{
			// create command list
			Compute compute = device.createCompute();
			
			if(trace_query) compute.beginQuery(trace_query);
			
			// dispatch trace kernel
			compute.setKernel(trace_kernel);
			compute.setSampler(0, sampler);
			compute.setTexture(0, noise_texture);
			compute.setTexture(1, model_texture);
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

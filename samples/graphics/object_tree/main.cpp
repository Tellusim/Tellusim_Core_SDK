// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <math/TellusimMath.h>
#include <math/TellusimRandom.h>
#include <geometry/TellusimSpatial.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCompute.h>
#include <platform/TellusimCommand.h>
#include <parallel/TellusimPrefixScan.h>
#include <parallel/TellusimRadixSort.h>
#include <parallel/TellusimSpatialTree.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::ObjectTree", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// number of objects
	constexpr uint32_t batch = 128;
	constexpr uint32_t width = 1024;
	constexpr uint32_t height = 1024;
	constexpr uint32_t num_nodes = width * height;
	constexpr float32_t step = 2.0f;
	
	// structures
	struct IntersectionParameters {
		Vector4f planes[6];
		Vector4f signs[6];
		Vector4f camera;
		float32_t lod0_distance2;
		float32_t lod1_distance2;
	};
	
	struct IndirectParameters {
		uint32_t num_indices;
	};
	
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Vector4f camera;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// optimal group size
	uint32_t group_size = min(device.getFeatures().maxGroupSizeX, 256u);
	
	// check compute shader support
	if(!device.hasShader(Shader::TypeCompute)) {
		TS_LOG(Error, "compute shader is not supported\n");
		return 0;
	}
	if(!device.getFeatures().vertexStorage) {
		TS_LOG(Error, "vertex storage buffer is not supported\n");
		return 0;
	}
	
	// shader cache
	Shader::setCache("main.cache");
	
	// create clear kernel
	Kernel clear_kernel = device.createKernel().setStorages(4, BindFlagFixed);
	if(!clear_kernel.loadShaderGLSL("main.shader", "COMPUTE_CLEAR_SHADER=1; GROUP_SIZE=%uu", group_size)) return 1;
	if(!clear_kernel.create()) return 1;
	
	// create intersection kernel
	Kernel intersection_kernel = device.createKernel().setUniforms(1).setStorages(6, BindFlagFixed);
	if(!intersection_kernel.loadShaderGLSL("main.shader", "COMPUTE_INTERSECTION_SHADER=1; GROUP_SIZE=%uu", group_size)) return 1;
	if(!intersection_kernel.create()) return 1;
	
	// create indirect kernel
	Kernel indirect_kernel = device.createKernel().setUniforms(1).setStorages(4, BindFlagFixed);
	if(!indirect_kernel.loadShaderGLSL("main.shader", "COMPUTE_INDIRECT_SHADER=1")) return 1;
	if(!indirect_kernel.create()) return 1;
	
	// create lod0 pipeline
	Pipeline lod0_pipeline = device.createPipeline();
	lod0_pipeline.setUniformMask(0, Shader::MaskVertex);
	lod0_pipeline.setStorageMasks(0, 2, Shader::MaskVertex, BindFlagFixed);
	lod0_pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 8);
	lod0_pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, sizeof(float32_t) * 3, sizeof(float32_t) * 8);
	lod0_pipeline.setMultisample(window.getMultisample());
	lod0_pipeline.setColorFormat(window.getColorFormat());
	lod0_pipeline.setDepthFormat(window.getDepthFormat());
	lod0_pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!lod0_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_LOD0_SHADER=1")) return 1;
	if(!lod0_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_LOD0_SHADER=1")) return 1;
	if(!lod0_pipeline.create()) return 1;
	
	// create lod1 pipeline
	Pipeline lod1_pipeline = device.createPipeline();
	lod1_pipeline.setUniformMask(0, Shader::MaskVertex);
	lod1_pipeline.setStorageMasks(0, 2, Shader::MaskVertex, BindFlagFixed);
	lod1_pipeline.setPrimitive(Pipeline::PrimitivePoint);
	lod1_pipeline.setMultisample(window.getMultisample());
	lod1_pipeline.setColorFormat(window.getColorFormat());
	lod1_pipeline.setDepthFormat(window.getDepthFormat());
	lod1_pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!lod1_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_LOD1_SHADER=1")) return 1;
	if(!lod1_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_LOD1_SHADER=1")) return 1;
	if(!lod1_pipeline.create()) return 1;
	
	// create nodes pipeline
	Pipeline nodes_pipeline = device.createPipeline();
	nodes_pipeline.setUniformMask(0, Shader::MaskVertex);
	nodes_pipeline.setStorageMask(0, Shader::MaskVertex, BindFlagFixed);
	nodes_pipeline.setMultisample(window.getMultisample());
	nodes_pipeline.setColorFormat(window.getColorFormat());
	nodes_pipeline.setDepthFormat(window.getDepthFormat());
	nodes_pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	nodes_pipeline.setPrimitive(Pipeline::PrimitiveLine);
	if(!nodes_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_NODES_SHADER=1")) return 1;
	if(!nodes_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_NODES_SHADER=1")) return 1;
	if(!nodes_pipeline.create()) return 1;
	
	// create tree
	RadixSort radix_sort;
	PrefixScan prefix_scan;
	SpatialTree spatial_tree;
	if(!radix_sort.create(device, RadixSort::ModeSingle, prefix_scan, num_nodes)) return 1;
	if(!spatial_tree.create(device, SpatialTree::ModeSingle, radix_sort, num_nodes)) return 1;
	
	// create objects
	uint64_t begin = Time::current();
	Array<Vector3f> radiuses(width);
	Array<Quaternionf> rotations(width);
	Array<Matrix4x3f> transforms(num_nodes);
	Array<Spatial::Node4f> nodes(num_nodes * 2);
	Random<Vector3i, Vector3f> random(Vector3i(1, 3, 7));
	for(uint32_t i = 0; i < width; i++) {
		radiuses[i] = Vector3f(random.getf32(Vector3f(0.3f), Vector3f(1.0f)).x * step);
		rotations[i] = Quaternionf::rotateXYZ(random.getf32(Vector3f(0.0f), Vector3f(360.0f)));
	}
	for(uint32_t y = 0, i = 0; y < height; y += batch) {
		for(uint32_t x = 0; x < width; x += batch) {
			Vector3f scale = Vector3f((float32_t)batch, (float32_t)batch, 4.0f) * step;
			Vector3f offset = Vector3f(x - width * 0.5f, y - height * 0.5f, 0.0f) * step;
			for(uint32_t j = 0; j < batch * batch; j++, i++) {
				Vector3i index = random.geti32();
				uint32_t index_0 = index.x % width;
				uint32_t index_1 = index.y % width;
				Vector3f translate = random.getf32(Vector3f(0.0f), Vector3f(1.0f)) * scale + offset;
				nodes[num_nodes + i].bound.min = Vector4f(translate - radiuses[index_1], f32u32(1u << 31u).f);
				nodes[num_nodes + i].bound.max = Vector4f(translate + radiuses[index_1], 0.0f);
				transforms[i].setComponents(translate, rotations[index_0], radiuses[index_1]);
			}
		}
	}
	TS_LOGF(Message, "Create Nodes: %s %s\n", String::fromBytes(transforms.bytes()).get(), String::fromTime(Time::current() - begin).get());
	
	// create spatial tree
	if(0) {
		uint64_t begin = Time::current();
		Spatial::create<float32_t>((Spatial::Node4f*)nodes.get(), num_nodes);
		Spatial::optimize<float32_t>((Spatial::Node4f*)nodes.get(), num_nodes);
		TS_LOGF(Message, "Create Tree: %s %s\n", String::fromBytes(nodes.bytes()).get(), String::fromTime(Time::current() - begin).get());
	}
	
	// create scene buffers
	begin = Time::current();
	Buffer transforms_buffer = device.createBuffer(Buffer::FlagStorage, transforms.get(), transforms.bytes());
	Buffer nodes_buffer = device.createBuffer(Buffer::FlagSource | Buffer::FlagStorage, nodes.get(), nodes.bytes());
	TS_LOGF(Message, "Upload Nodes: %s %s %s/s\n", String::fromBytes(transforms.bytes() + nodes.bytes()).get(), String::fromTime(Time::current() - begin).get(),
		String::fromBytes((size_t)((float64_t)(transforms.bytes() + nodes.bytes()) * (float64_t)Time::Seconds / (Time::current() - begin))).get());
	
	// create spatial tree
	if(1) {
		device.finish();
		uint64_t begin = Time::current();
		{
			Compute compute = device.createCompute();
			spatial_tree.dispatch(compute, SpatialTree::HashXY15, nodes_buffer, 0, num_nodes);
		}
		device.finish();
		TS_LOGF(Message, "Create Tree: %s %s\n", String::fromBytes(nodes.bytes()).get(), String::fromTime(Time::current() - begin).get());
		begin = Time::current();
		device.getBuffer(nodes_buffer, nodes.get());
		TS_LOGF(Message, "Download Tree: %s %s %s/s\n", String::fromBytes(nodes.bytes()).get(), String::fromTime(Time::current() - begin).get(),
			String::fromBytes((size_t)((float64_t)nodes.bytes() * (float64_t)Time::Seconds / (Time::current() - begin))).get());
	}
	
	// create intersection buffers
	Buffer indices_buffers[2];
	Buffer indirect_buffers[2];
	indices_buffers[0] = device.createBuffer(Buffer::FlagStorage, sizeof(uint32_t) * num_nodes + sizeof(uint32_t));
	indices_buffers[1] = device.createBuffer(Buffer::FlagStorage, sizeof(uint32_t) * num_nodes + sizeof(uint32_t));
	indirect_buffers[0] = device.createBuffer(Buffer::FlagStorage | Buffer::FlagIndirect, sizeof(Compute::DispatchIndirect));
	indirect_buffers[1] = device.createBuffer(Buffer::FlagStorage | Buffer::FlagIndirect, sizeof(Compute::DispatchIndirect));
	
	// create draw buffers
	Array<uint32_t> lod0_indices(num_nodes + 1);
	Array<uint32_t> lod1_indices(num_nodes + 1);
	Buffer lod0_indices_buffer = device.createBuffer(Buffer::FlagStorage, lod0_indices.bytes() + sizeof(uint32_t));
	Buffer lod1_indices_buffer = device.createBuffer(Buffer::FlagStorage, lod1_indices.bytes() + sizeof(uint32_t));
	Buffer lod0_indirect_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagIndirect, sizeof(Command::DrawElementsIndirect));
	Buffer lod1_indirect_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagIndirect, sizeof(Command::DrawArraysIndirect));
	
	// create octa geometry
	#include "main_octa.h"
	constexpr uint32_t num_vertices = num_octa_vertices;
	constexpr uint32_t num_indices = num_octa_indices;
	Buffer vertex_buffer = device.createBuffer(Buffer::FlagVertex, octa_vertices, sizeof(float32_t) * num_vertices);
	Buffer index_buffer = device.createBuffer(Buffer::FlagIndex, octa_indices, sizeof(uint32_t) * num_indices);
	if(!vertex_buffer || !index_buffer) return 1;
	
	// create queries
	Query tree_query, render_query;
	if(device.hasQuery(Query::TypeTime)) {
		tree_query = device.createQuery(Query::TypeTime);
		render_query = device.createQuery(Query::TypeTime);
		if(!tree_query || !render_query) return 1;
	}
	
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
	
	ControlCheck cpu_mode_check(&right_panel, "CPU mode");
	cpu_mode_check.setAlign(Control::AlignLeft);
	
	ControlCheck show_nodes_check(&right_panel, "Show nodes");
	show_nodes_check.setAlign(Control::AlignLeft);
	
	ControlCheck animation_check(&right_panel, "Animation", true);
	animation_check.setAlign(Control::AlignLeft);
	
	float32_t animation_time = 0.0f;
	float32_t old_animation_time = 0.0f;
	
	uint64_t cpu_time = 0;
	bool old_cpu_mode = false;
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		using Tellusim::sin;
		using Tellusim::cos;
		
		Window::update();
		
		if(!window.render()) return false;
		
		// FPS counter
		bool cpu_mode = cpu_mode_check.isChecked();
		if(fps > 0.0f || cpu_mode != old_cpu_mode || frame_counter == 0) {
			String tree_time = String::fromTime(cpu_time);
			if(!cpu_mode && tree_query && tree_query.isAvailable()) tree_time = String::fromTime(tree_query.getTime());
			String render_time = String::fromTime((render_query && render_query.isAvailable()) ? render_query.getTime() : 0);
			String statistics_info = (cpu_mode) ? String::format("\nLod 0: %u\nLod 1: %u", lod0_indices.size(), lod1_indices.size()) : String::null;
			info_text.setText(String::format("FPS: %.1f\nTree: %s\nRender: %s%s", fps, tree_time.get(), render_time.get(), statistics_info.get()));
			old_cpu_mode = cpu_mode;
		}
		
		// update keyboard
		if(window.getKeyboardKey('c', true)) cpu_mode_check.switchChecked();
		if(window.getKeyboardKey('n', true)) show_nodes_check.switchChecked();
		if(window.getKeyboardKey(' ', true)) animation_check.switchChecked();
		
		// update controls
		update_controls(window, root);
		canvas.create(device, target);
		
		// animation time
		if(animation_check.isChecked()) animation_time += time - old_animation_time;
		old_animation_time = time;
		
		// camera parameters
		float32_t lod0_distance = 200.0f;
		float32_t lod1_distance = 800.0f;
		float32_t lod0_distance2 = lod0_distance * lod0_distance;
		float32_t lod1_distance2 = lod1_distance * lod1_distance;
		Vector4f camera = Vector4f(sin(animation_time * 0.1f) * 200.0f, cos(animation_time * 0.1f) * 200.0f, 40.0f + sin(animation_time) * 30.0f, 0.0f);
		Matrix4x4f projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, lod1_distance);
		Matrix4x4f modelview = Matrix4x4f::lookAt(Vector3f(camera), Vector3f(0.0f, 0.0f, -40.0f), Vector3f(0.0f, 0.0f, 1.0f));
		BoundFrustumf bound_frustum(projection, modelview);
		
		// common parameters
		CommonParameters common_parameters;
		common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 10000.0f);
		if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
		common_parameters.modelview = modelview;
		common_parameters.camera = camera;
		
		// objects intersection
		if(cpu_mode) {
			uint32_t index = 0;
			Array<uint32_t> stack;
			const auto *nodes_ptr = nodes.get();
			lod0_indices.clear(); lod0_indices.append(0);
			lod1_indices.clear(); lod1_indices.append(0);
			uint64_t begin = Time::current();
			while(true) {
				const auto &node = nodes_ptr[index];
				if(bound_frustum.insideAll(node.bound)) {
					uint32_t depth = stack.size();
					while(true) {
						bool left = true, right = true;
						const auto &node = nodes_ptr[index];
						if(node.left >= node.spatial) {
							float32_t distance = length32(nodes_ptr[node.left].bound.getCenter() - camera);
							if(distance < lod0_distance2) lod0_indices.append(node.left - node.spatial);
							else if(distance < lod1_distance2) lod1_indices.append(node.left - node.spatial);
							left = false;
						}
						if(node.right >= node.spatial) {
							float32_t distance = length32(nodes_ptr[node.right].bound.getCenter() - camera);
							if(distance < lod0_distance2) lod0_indices.append(node.right - node.spatial);
							else if(distance < lod1_distance2) lod1_indices.append(node.right - node.spatial);
							right = false;
						}
						if(right) {
							if(left) stack.append(node.left);
							index = node.right; continue;
						}
						if(left) {
							index = node.left; continue;
						}
						if(stack.size() == depth) break;
						index = stack.back(); stack.removeBack();
					}
					if(stack.size() == 0) break;
					index = stack.back(); stack.removeBack();
					continue;
				}
				bool left = bound_frustum.inside(nodes_ptr[node.left].bound);
				bool right = bound_frustum.inside(nodes_ptr[node.right].bound);
				if(left && node.left >= node.spatial) {
					float32_t distance = length32(nodes_ptr[node.left].bound.getCenter() - camera);
					if(distance < lod0_distance2) lod0_indices.append(node.left - node.spatial);
					else if(distance < lod1_distance2) lod1_indices.append(node.left - node.spatial);
					left = false;
				}
				if(right && node.right >= node.spatial) {
					float32_t distance = length32(nodes_ptr[node.right].bound.getCenter() - camera);
					if(distance < lod0_distance2) lod0_indices.append(node.right - node.spatial);
					else if(distance < lod1_distance2) lod1_indices.append(node.right - node.spatial);
					right = false;
				}
				if(right) {
					if(left) stack.append(node.left);
					index = node.right; continue;
				}
				if(left) {
					index = node.left; continue;
				}
				if(stack.size() == 0) break;
				index = stack.back(); stack.removeBack();
			}
			cpu_time = Time::current() - begin;
			lod0_indices[0] = lod0_indices.size() - 1;
			lod1_indices[0] = lod1_indices.size() - 1;
			device.setBuffer(lod0_indices_buffer, lod0_indices.get(), lod0_indices.bytes());
			device.setBuffer(lod1_indices_buffer, lod1_indices.get(), lod1_indices.bytes());
		}
		else {
			
			// create command list
			Compute compute = device.createCompute();
			
			// intersection parameters
			IntersectionParameters intersection_parameters;
			for(uint32_t i = 0; i < 4; i++) {
				intersection_parameters.camera[i] = camera[i];
				for(uint32_t j = 0; j < 6; j++) {
					intersection_parameters.planes[j][i] = bound_frustum.planes[j][i];
					intersection_parameters.signs[j][i] = (float32_t)bound_frustum.signs[j][i];
				}
			}
			intersection_parameters.lod0_distance2 = lod0_distance2;
			intersection_parameters.lod1_distance2 = lod1_distance2;
			
			if(tree_query) compute.beginQuery(tree_query);
			
			// dispatch clear kernel
			compute.setKernel(clear_kernel);
			compute.setStorageBuffers(0, { indices_buffers[0], indices_buffers[1] });
			compute.setStorageBuffers(2, { lod0_indices_buffer, lod1_indices_buffer });
			compute.dispatch(1);
			
			compute.barrier({ indices_buffers[0], indices_buffers[1], lod0_indices_buffer, lod1_indices_buffer });
			
			// dispatch main intersection kernel
			compute.setKernel(intersection_kernel);
			compute.setUniform(0, intersection_parameters);
			compute.setStorageBuffers(0, { nodes_buffer, indices_buffers[0], indices_buffers[1] });
			compute.setStorageBuffers(3, { lod0_indices_buffer, lod1_indices_buffer });
			compute.setStorageBuffer(5, indirect_buffers[0]);
			compute.dispatch(1);
			
			// dispatch multipass intersection kernels
			for(uint32_t i = 0; i < 6; i++) {
				
				// swap buffers
				swap(indices_buffers[0], indices_buffers[1]);
				swap(indirect_buffers[0], indirect_buffers[1]);
				
				// buffers barrier
				compute.barrier({ indices_buffers[0], indices_buffers[1] });
				compute.barrier({ indirect_buffers[0], indirect_buffers[1] });
				
				// dispatch additional intersection kernel
				compute.setKernel(intersection_kernel);
				compute.setUniform(0, intersection_parameters);
				compute.setStorageBuffers(0, { nodes_buffer, indices_buffers[0], indices_buffers[1] });
				compute.setStorageBuffers(3, { lod0_indices_buffer, lod1_indices_buffer });
				compute.setStorageBuffer(5, indirect_buffers[0]);
				compute.setIndirectBuffer(indirect_buffers[1]);
				compute.dispatchIndirect();
			}
			
			compute.barrier({ lod0_indices_buffer, lod1_indices_buffer });
			
			if(tree_query) compute.endQuery(tree_query);
		}
		
		{
			// create command list
			Compute compute = device.createCompute();
			
			// indirect parameters
			IndirectParameters indirect_parameters;
			indirect_parameters.num_indices = num_indices;
			
			// dispatch indirect kernel
			compute.setKernel(indirect_kernel);
			compute.setUniform(0, indirect_parameters);
			compute.setStorageBuffers(0, { lod0_indices_buffer, lod1_indices_buffer, lod0_indirect_buffer, lod1_indirect_buffer });
			compute.dispatch(1);
			
			// indirect barrier
			compute.barrier({ lod0_indirect_buffer, lod1_indirect_buffer });
		}
		
		// set buffer layout
		device.flushBuffers({
			lod0_indices_buffer, lod1_indices_buffer,
			lod0_indirect_buffer, lod1_indirect_buffer,
		});
		
		// window target
		target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		target.begin();
		{
			// create command list
			auto command = device.createCommand(target);
			
			if(render_query) command.beginQuery(render_query);
				
				// draw lod0 objects
				command.setPipeline(lod0_pipeline);
				command.setUniform(0, common_parameters);
				command.setStorageBuffers(0, { lod0_indices_buffer, transforms_buffer });
				command.setVertexBuffer(0, vertex_buffer);
				command.setIndexBuffer(FormatRu32, index_buffer);
				command.setIndirectBuffer(lod0_indirect_buffer);
				command.drawElementsIndirect(1);
				
				// draw lod1 objects
				command.setPipeline(lod1_pipeline);
				command.setUniform(0, common_parameters);
				command.setStorageBuffers(0, { lod1_indices_buffer, transforms_buffer });
				command.setIndirectBuffer(lod1_indirect_buffer);
				command.drawArraysIndirect(1);
				
			if(render_query) command.endQuery(render_query);
			
			// draw spatial nodes
			if(show_nodes_check.isChecked()) {
				command.setPipeline(nodes_pipeline);
				command.setUniform(0, common_parameters);
				command.setStorageBuffer(0, nodes_buffer);
				command.setIndices({ 0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 0, 4, 1, 5, 2, 6, 3, 7 });
				command.drawElementsInstanced(24, 0, num_nodes - 1);
			}
			
			// draw canvas
			canvas.draw(command, target);
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

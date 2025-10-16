// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimMath.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimCommand.h>
#include <platform/TellusimCompute.h>
#include <parallel/TellusimPrefixScan.h>
#include <parallel/TellusimRadixSort.h>
#include <parallel/TellusimSpatialTree.h>

/*
 */
//#define LEAF_NODEF16	1

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::SpatialTree", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// structures
	struct ComputeParameters {
		uint32_t size;
		float32_t ifps;
		float32_t radius;
		uint32_t grid_size;
		float32_t grid_scale;
	};
	
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		float32_t radius;
	};
	
	// spatial parameters
	const uint32_t grid_size = 64;
	const uint32_t group_size = 128;
	constexpr float32_t radius = 0.1f;
	constexpr float32_t ifps = 1.0f / 400.0f;
	#if _ANDROID || _IOS
		constexpr uint32_t size = 24;
	#else
		constexpr uint32_t size = 32;
	#endif
	constexpr uint32_t num_particles = size * size * size;
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check compute shader support
	if(!device.hasShader(Shader::TypeCompute)) {
		TS_LOG(Error, "compute shader is not supported\n");
		return 0;
	}
	
	// shader cache
	Shader::setCache("main.cache");
	
	// shader macro
	Shader::setMacro("LEAF_NODEF16", TS_STRING(LEAF_NODEF16));
	
	// create kernel
	Kernel kernel = device.createKernel().setUniforms(1).setStorages(5, BindFlagFixed);
	if(!kernel.loadShaderGLSL("main.shader", "COMPUTE_SHADER=1; GROUP_SIZE=%uu", group_size)) return 1;
	if(!kernel.create()) return 1;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLess);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBAf32, 0, 0, sizeof(Vector4f), 1);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create nodes pipeline
	Pipeline nodes_pipeline;
	if(device.getFeatures().vertexStorage) {
		nodes_pipeline = device.createPipeline();
		nodes_pipeline.setUniformMask(0, Shader::MaskVertex);
		nodes_pipeline.setStorageMask(0, Shader::MaskVertex);
		nodes_pipeline.setColorFormat(window.getColorFormat());
		nodes_pipeline.setDepthFormat(window.getDepthFormat());
		nodes_pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
		nodes_pipeline.setPrimitive(Pipeline::PrimitiveLine);
		if(!nodes_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_NODES_SHADER=1")) return 1;
		if(!nodes_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_NODES_SHADER=1")) return 1;
		if(!nodes_pipeline.create()) return 1;
	}
	
	// create particles
	Array<Vector4f> positions(num_particles);
	Array<Vector4f> velocities(num_particles);
	Matrix4x4f transform = Matrix4x4f::translate(0.0f, 0.0f, size * radius * 2.0f) * Matrix4x4f::rotateY(35.3f) * Matrix4x4f::rotateX(45.0f);
	for(uint32_t z = 0, index = 0; z < size; z++) {
		float32_t Z = (z - size * 0.5f) * radius * 2.0f;
		uint32_t color = Color::hsv(60.0f + z * 240.0f / size, 1.0f, 1.0f).getRGBAu8();
		for(uint32_t y = 0; y < size; y++) {
			float32_t Y = (y - size * 0.5f) * radius * 2.0f;
			for(uint32_t x = 0; x < size; x++, index++) {
				float32_t X = (x - size * 0.5f) * radius * 2.0f;
				if(index < num_particles) {
					positions[index] = Vector4f(transform * Vector3f(X, Y, Z), f32u32(color).f);
					velocities[index] = Vector4f(0.0f);
				}
			}
		}
	}
	
	// create buffers
	Buffer position_buffers[2];
	Buffer velocity_buffers[2];
	position_buffers[0] = device.createBuffer(Buffer::FlagVertex | Buffer::FlagStorage, positions.get(), positions.bytes());
	position_buffers[1] = device.createBuffer(Buffer::FlagVertex | Buffer::FlagStorage, positions.bytes());
	velocity_buffers[0] = device.createBuffer(Buffer::FlagStorage, velocities.get(), velocities.bytes());
	velocity_buffers[1] = device.createBuffer(Buffer::FlagStorage, velocities.bytes());
	if(!position_buffers[0] || !position_buffers[1]) return 1;
	if(!velocity_buffers[0] || !velocity_buffers[1]) return 1;
	
	// create spatial tree
	RadixSort radix_sort;
	PrefixScan prefix_scan;
	SpatialTree spatial_tree;
	SpatialTree::Flags spatial_tree_flags = SpatialTree::FlagSingle;
	#if LEAF_NODEF16
		spatial_tree_flags |= SpatialTree::FlagLeafNodef16;
	#endif
	if(!radix_sort.create(device, RadixSort::FlagSingle | RadixSort::FlagIndirect, prefix_scan, num_particles, group_size)) return 1;
	if(!spatial_tree.create(device, spatial_tree_flags, radix_sort, num_particles, group_size)) return 1;
	
	// create dispatch buffer
	SpatialTree::DispatchParameters dispatch_parameters[4] = {};
	dispatch_parameters[3].offset = 0;
	dispatch_parameters[3].size = num_particles;
	Buffer dispatch_buffer = device.createBuffer(Buffer::FlagStorage, dispatch_parameters, sizeof(dispatch_parameters));
	if(!dispatch_buffer) return 1;
	
	// create spatial buffers
	Buffer nodes_buffer = device.createBuffer(Buffer::FlagStorage, sizeof(SpatialTree::Node) * num_particles * 2);
	if(!nodes_buffer || !device.clearBuffer(nodes_buffer)) return 1;
	
	// create target
	Target target = device.createTarget(window);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// reset simulation
		if(window.getKeyboardKey(' ')) {
			device.setBuffer(position_buffers[0], positions.get());
			device.setBuffer(velocity_buffers[0], velocities.get());
			frame_counter = 0;
		}
		if(window.getKeyboardKey('s')) {
			frame_counter = 0;
		}
		
		#if _EMSCRIPTEN
			for(float32_t i = 0.0f; i < 1.0f / (ifps * 60.0f); i += 1.0f)
		#endif
		{
			// create command list
			Compute compute = device.createCompute();
			
			// swap buffers
			if(simulate && frame_counter < 2800) {
				swap(position_buffers[0], position_buffers[1]);
				swap(velocity_buffers[0], velocity_buffers[1]);
			}
			
			// compute parameters
			ComputeParameters compute_parameters;
			compute_parameters.size = num_particles;
			compute_parameters.ifps = ifps;
			compute_parameters.radius = radius;
			compute_parameters.grid_size = grid_size;
			compute_parameters.grid_scale = 0.5f / radius;
			
			// set simulation kernel
			compute.setKernel(kernel);
			compute.setUniform(0, compute_parameters);
			compute.setStorageBuffers(0, { nodes_buffer,
				position_buffers[0], velocity_buffers[0],
				position_buffers[1], velocity_buffers[1],
			});
			compute.dispatch(num_particles);
			compute.barrier(nodes_buffer);
			
			// dispatch spatial tree
			bool indirect = window.getKeyboardKey('i');
			SpatialTree::Flags flags = window.getKeyboardKey('u') ? SpatialTree::FlagUpdate : SpatialTree::FlagNone;
			if(indirect) spatial_tree.dispatchIndirect(compute, SpatialTree::HashXYZ10, nodes_buffer, dispatch_buffer, 3, num_particles, flags);
			else spatial_tree.dispatch(compute, SpatialTree::HashXYZ10, nodes_buffer, 0, num_particles, flags);
			compute.barrier(position_buffers[0]);
		}
		
		// window target
		target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// common parameters
			CommonParameters common_parameters;
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(16.0f, 0.0f, 8.0f), Vector3f::zero, Vector3f::oneZ);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			common_parameters.radius = radius;
			
			// draw partices
			command.setPipeline(pipeline);
			command.setUniform(0, common_parameters);
			command.setIndices({ 0, 1, 2, 2, 3, 0 });
			command.setVertexBuffer(0, position_buffers[0]);
			command.drawElementsInstanced(6, 0, num_particles);
			
			// draw spatial nodes
			if(window.getKeyboardKey('n') && nodes_pipeline) {
				command.setPipeline(nodes_pipeline);
				command.setUniform(0, common_parameters);
				command.setStorageBuffer(0, nodes_buffer);
				command.setIndices({ 0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 0, 4, 1, 5, 2, 6, 3, 7 });
				command.drawElementsInstanced(24, 0, max(num_particles - 1, 1u));
			}
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

// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <core/TellusimSort.h>
#include <math/TellusimMath.h>
#include <math/TellusimRandom.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCompute.h>
#include <platform/TellusimCommand.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Fence", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// structures
	struct ComputeParameters {
		float32_t ifps;
		uint32_t size;
		uint32_t offset;
	};
	
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		float32_t radius;
	};
	
	// number of particles
	#if _ANDROID || _IOS
		uint32_t num_particles = 1024 * 4;
	#else
		uint32_t num_particles = 1024 * 16;
	#endif
	constexpr uint32_t group_size = 128;
	
	// create primary device
	Device device(window);
	if(!device) return 1;
	
	// check compute shader support
	if(!device.hasShader(Shader::TypeCompute)) {
		TS_LOG(Error, "compute shader is not supported\n");
		return 0;
	}
	
	// device info
	TS_LOGF(Message, "%s (%s) %u\n", device.getName().get(), device.getPlatformName(), device.getIndex());
	
	// create kernel
	Kernel kernel = device.createKernel().setUniforms(1).setStorages(4);
	if(!kernel.loadShaderGLSL("main.shader", "COMPUTE_SHADER=1; GROUP_SIZE=%uu", group_size)) return 1;
	if(!kernel.create()) return 1;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncNone);
	pipeline.setBlend(Pipeline::BlendOpAdd, Pipeline::BlendFuncOne, Pipeline::BlendFuncOne);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBAf32, 0, 0, sizeof(Vector4f), 1);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create particles
	using Tellusim::sin;
	using Tellusim::cos;
	using Tellusim::sqrt;
	Array<Vector4f> positions(num_particles);
	Array<Vector4f> velocities(num_particles);
	Random<Vector3i, Vector3f> random(Vector3i(1, 3, 7));
	for(uint32_t i = 0; i < num_particles; i++) {
		Vector3f p = random.getf32(Vector3f(0.0f, -1.0f, 12.0f), Vector3f(Pi2, 1.0f, 13.0f));
		float32_t x = sin(p.x) * sqrt(1.0f - p.y * p.y);
		float32_t y = cos(p.x) * sqrt(1.0f - p.y * p.y);
		positions[i] = Vector4f(Vector3f(x, y, p.y) * p.z, 0.0f);
		velocities[i] = Vector4f(0.0f);
	}
	
	// create buffers
	Buffer position_buffers[2];
	Buffer velocity_buffers[2];
	position_buffers[0] = device.createBuffer(Buffer::FlagStorage | Buffer::FlagVertex | Buffer::FlagSource, positions.get(), positions.bytes());
	position_buffers[1] = device.createBuffer(Buffer::FlagStorage | Buffer::FlagVertex | Buffer::FlagSource, positions.bytes());
	velocity_buffers[0] = device.createBuffer(Buffer::FlagStorage, velocities.get(), velocities.bytes());
	velocity_buffers[1] = device.createBuffer(Buffer::FlagStorage, velocities.bytes());
	if(!position_buffers[0] || !position_buffers[1]) return 1;
	if(!velocity_buffers[0] || !velocity_buffers[1]) return 1;
	
	// create secondary device
	Device secondary_device;
	if((device.getPlatform() == PlatformVK || device.getPlatform() == PlatformD3D12) && !app.isArgument("single")) {
		secondary_device = device.createDevice(1);
		if(secondary_device && !secondary_device.hasShader(Shader::TypeCompute)) secondary_device.clearPtr();
		if(secondary_device) TS_LOGF(Message, "%s (%s) %u\n", secondary_device.getName().get(), secondary_device.getPlatformName(), secondary_device.getIndex());
	}
	
	// create secondary device resources
	Fence primary_fence_0;
	Fence primary_fence_1;
	Fence secondary_fence_0;
	Fence secondary_fence_1;
	Kernel secondary_kernel;
	Buffer secondary_position_buffers[2];
	Buffer secondary_velocity_buffers[2];
	Buffer primary_shared_position_buffer;
	Buffer secondary_shared_position_buffer;
	size_t primary_size = 0;
	size_t secondary_size = 0;
	uint32_t primary_particles = num_particles;
	uint32_t secondary_particles = 0;
	if(secondary_device) {
		
		// create primary to secondary shared fence
		primary_fence_0 = device.createFence(Fence::FlagSignaled | Fence::FlagShared);
		secondary_fence_0 = secondary_device.createFence(primary_fence_0);
		if(!primary_fence_0 || !secondary_fence_0) return 1;
		
		// create secondary to primary shared fence
		secondary_fence_1 = secondary_device.createFence(Fence::FlagShared);
		primary_fence_1 = device.createFence(secondary_fence_1);
		if(!primary_fence_1 || !secondary_fence_1) return 1;
		
		// create secondary kernel
		secondary_kernel = secondary_device.createKernel().setUniforms(1).setStorages(4);
		if(!secondary_kernel.loadShaderGLSL("main.shader", "COMPUTE_SHADER=1; GROUP_SIZE=%uu", group_size)) return 1;
		if(!secondary_kernel.create()) return 1;
		
		// create secondary buffers
		secondary_position_buffers[0] = secondary_device.createBuffer(Buffer::FlagStorage | Buffer::FlagSource, positions.get(), positions.bytes());
		secondary_position_buffers[1] = secondary_device.createBuffer(Buffer::FlagStorage | Buffer::FlagSource, positions.bytes());
		secondary_velocity_buffers[0] = secondary_device.createBuffer(Buffer::FlagStorage, velocities.get(), velocities.bytes());
		secondary_velocity_buffers[1] = secondary_device.createBuffer(Buffer::FlagStorage, velocities.bytes());
		if(!secondary_position_buffers[0] || !secondary_position_buffers[1]) return 1;
		if(!secondary_velocity_buffers[0] || !secondary_velocity_buffers[1]) return 1;
		
		// create shared position buffer
		primary_shared_position_buffer = device.createBuffer(Buffer::FlagSource | Buffer::FlagShared, positions.get(), positions.bytes());
		secondary_shared_position_buffer = secondary_device.createBuffer(primary_shared_position_buffer);
		if(!primary_shared_position_buffer || !secondary_shared_position_buffer) return 1;
		
		// primary particles
		primary_particles = num_particles / 2;
		primary_size = sizeof(Vector4f) * primary_particles;
		
		// secondary particles
		secondary_particles = num_particles - primary_particles;
		secondary_size = sizeof(Vector4f) * secondary_particles;
	}
	
	// create target
	Target target = device.createTarget(window);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS %u", title.get(), fps, num_particles));
		
		// swap buffers
		swap(position_buffers[0], position_buffers[1]);
		swap(velocity_buffers[0], velocity_buffers[1]);
		if(secondary_device) {
			swap(secondary_position_buffers[0], secondary_position_buffers[1]);
			swap(secondary_velocity_buffers[0], secondary_velocity_buffers[1]);
		}
		
		// compute parameters
		ComputeParameters compute_parameters;
		#if _EMSCRIPTEN
			compute_parameters.ifps = 1.0f / 60.0f;
		#else
			compute_parameters.ifps = 1.0f / 1000.0f;
		#endif
		compute_parameters.size = num_particles;
		compute_parameters.offset = 0;
		
		// update positions
		{
			// create command list
			Compute compute = device.createCompute();
			
			// dispatch primary kernel
			compute.setKernel(kernel);
			compute.setUniform(0, compute_parameters);
			compute.setStorageBuffers(0, { position_buffers[0], velocity_buffers[0] });
			compute.setStorageBuffers(2, { position_buffers[1], velocity_buffers[1] });
			compute.dispatch(primary_particles);
			
			// multi device mode
			if(secondary_device) {
				
				Compute secondary_compute = secondary_device.createCompute();
				
				compute_parameters.offset = primary_particles;
				
				// dispatch secondary kernel
				secondary_compute.setKernel(secondary_kernel);
				secondary_compute.setUniform(0, compute_parameters);
				secondary_compute.setStorageBuffers(0, { secondary_position_buffers[0], secondary_velocity_buffers[0] });
				secondary_compute.setStorageBuffers(2, { secondary_position_buffers[1], secondary_velocity_buffers[1] });
				secondary_compute.dispatch(secondary_particles);
			}
		}
		
		// copy buffers
		if(secondary_device) {
			
			// synchronization flag
			bool sync = !window.getKeyboardKey('s');
			
			if(sync) secondary_device.waitFence(secondary_fence_0);
			device.copyBuffer(primary_shared_position_buffer, 0, position_buffers[1], 0, primary_size);
			secondary_device.copyBuffer(secondary_shared_position_buffer, primary_size, secondary_position_buffers[1], primary_size, secondary_size);
			if(sync) secondary_device.flip(secondary_fence_1);
			else secondary_device.flip();
			
			if(sync) device.waitFence(primary_fence_1);
			device.copyBuffer(position_buffers[1], primary_size, primary_shared_position_buffer, primary_size, secondary_size);
			secondary_device.copyBuffer(secondary_position_buffers[1], 0, secondary_shared_position_buffer, 0, primary_size);
			if(sync) device.signalFence(primary_fence_0);
		}
		
		// flush buffer
		device.flushBuffer(position_buffers[1]);
			
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// set pipeline
			command.setPipeline(pipeline);
			
			// set common parameters
			CommonParameters common_parameters;
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(16.0f, 16.0f, 16.0f), Vector3f::zero, Vector3f::oneZ);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			common_parameters.radius = 1.0f / 16.0f;
			command.setUniform(0, common_parameters);
			
			// draw particles
			command.setIndices({ 0, 1, 2, 2, 3, 0 });
			command.setVertexBuffer(0, position_buffers[1]);
			command.drawElementsInstanced(6, 0, num_particles);
		}
		target.end();
		
		// flush buffer
		device.flushBuffer(position_buffers[0], Buffer::FlagStorage);
		
		if(!window.present()) return false;
		
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish secondary context
	if(secondary_device) secondary_device.finish();
	
	// finish context
	window.finish();
	
	return 0;
}

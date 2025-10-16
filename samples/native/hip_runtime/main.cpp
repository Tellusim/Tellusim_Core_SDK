// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <hip/hip_runtime.h>

#include <common/common.h>
#include <common/sample_controls.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimContext.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>

/*
 */
__global__ void kernel(uint32_t size, float scale, float time, float4 *positions) {
	
	uint32_t global_x = blockDim.x * blockIdx.x + threadIdx.x;
	uint32_t global_y = blockDim.y * blockIdx.y + threadIdx.y;
	
	uint32_t id = global_y * size + global_x;
	
	float x = (float)global_x / size * 2.0f - 1.0f;
	float y = (float)global_y / size * 2.0f - 1.0f;
	
	float r = sin(x * scale) * 0.5f + 0.5f;
	float g = cos(y * scale) * 0.5f + 0.5f;
	float b = max(1.0f - r - g, 0.0f);
	
	uint32_t color = 0xff000000u;
	color |= (uint32_t)(r * 255.0f) << 0u;
	color |= (uint32_t)(g * 255.0f) << 8u;
	color |= (uint32_t)(b * 255.0f) << 16u;
	
	positions[id] = make_float4(x * scale, y * scale, r + g + sin(sqrt(x * x + y * y) * 4.0f + time * 2.0f) * 4.0f, __uint_as_float(color));
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	using namespace Tellusim;
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::HipRuntime", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// geometry parameters
	constexpr uint32_t grid_size = 1024;
	constexpr uint32_t group_size = 8;
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create Hip context for our device
	HIPContext hip_context = HIPContext(Context(PlatformHIP));//, device.getFeatures().pciBusID));
	if(!hip_context || !hip_context.create()) {
		TS_LOG(Error, "main(): can't create Hip context\n");
		return 1;
	}
	
	// create Hip device
	Device hip_device(hip_context);
	if(!hip_device) return 1;
	
	// set Hip device
	if(hipSetDevice(hip_context.getDevice()) != hipSuccess) return 1;
	
	// Hip info
	int32_t driver_version = 0;
	int32_t runtime_version = 0;
	if(hipDriverGetVersion(&driver_version) != hipSuccess) return 1;
	if(hipRuntimeGetVersion(&runtime_version) != hipSuccess) return 1;
	TS_LOGF(Message, "Driver: %u\n", driver_version);
	TS_LOGF(Message, "Runtime: %u\n", runtime_version);
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBAf32, 0, 0, sizeof(float32_t) * 4);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setPrimitive(Pipeline::PrimitivePoint);
	pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create position buffer
	Buffer position_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagVertex | Buffer::FlagInterop, sizeof(float32_t) * 4 * grid_size * grid_size);
	if(!position_buffer) return 1;
	
	// create Hip position buffer
	HIPBuffer hip_position_buffer = HIPBuffer(hip_device.createBuffer(position_buffer));
	if(!hip_position_buffer) return 1;
	
	// create target
	Target target = device.createTarget(window);
	target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	// create canvas
	Canvas canvas;
	
	// create panel
	ControlRoot root(canvas, true);
	ControlPanel panel(&root, 1, 8.0f, 8.0f);
	panel.setAlign(Control::AlignRightTop);
	panel.setPosition(-8.0f, -8.0f);
	
	// create sliders
	ControlSlider scale_slider(&panel, "Scale", 3, 32.0f, 16.0f, 48.0f);
	scale_slider.setSize(192.0f, 0.0f);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		// suppress warnings
		simulate = simulate;
		pause = pause;
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// update controls
		update_controls(window, root);
		canvas.create(device, target);
		
		// dispatch Hip kernel
		{
			// dispatch Hip kernel
			uint32_t num_groups = udiv(grid_size, group_size);
			hipStream_t stream = (hipStream_t)hip_context.getStream();
			float4 *data = (float4*)hip_position_buffer.getBufferPtr();
			hipLaunchKernelGGL(kernel, dim3(num_groups, num_groups), dim3(group_size, group_size), 0, stream, grid_size, scale_slider.getValuef32(), time, data);
			
			// check Hip error
			hipError_t error = hipGetLastError();
			if(error != hipSuccess) TS_LOGF(Error, "main(): %s\n", hipGetErrorString(error));
			
			// synchronize stream
			hipStreamSynchronize(stream);
		}
		
		// flush buffer
		device.flushBuffer(position_buffer);
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// set pipeline
			command.setPipeline(pipeline);
			
			// set position buffers
			command.setVertexBuffer(0, position_buffer);
			
			// set common parameters
			CommonParameters common_parameters;
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(20.0f, 20.0f, 20.0f), Vector3f::zero, Vector3f::oneZ);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			command.setUniform(0, common_parameters);
			
			// draw geometry
			command.drawArrays(grid_size * grid_size);
			
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

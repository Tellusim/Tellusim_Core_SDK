// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

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
	String title = String::format("%s Tellusim::Cuda Runtime", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title);
	
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
	
	// create Cuda context for our device
	CUContext cu_context = CUContext(Context(PlatformCU, device.getFeatures().pciBusID));
	if(!cu_context || !cu_context.create()) {
		TS_LOG(Error, "main(): can't create Cuda context\n");
		return 1;
	}
	
	// create Cuda device
	Device cu_device(cu_context);
	if(!cu_device) return 1;
	
	// set Cuda device
	if(cudaSetDevice(cu_context.getDevice()) != cudaSuccess) return 1;
	
	// Cuda info
	int32_t driver_version = 0;
	int32_t runtime_version = 0;
	if(cudaDriverGetVersion(&driver_version) != cudaSuccess) return 1;
	if(cudaRuntimeGetVersion(&runtime_version) != cudaSuccess) return 1;
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
	
	// create Cuda position buffer
	CUBuffer cu_position_buffer = CUBuffer(cu_device.createBuffer(position_buffer));
	if(!cu_position_buffer) return 1;
	
	// create target
	Target target = device.createTarget(window);
	
	// create canvas
	Canvas canvas;
	
	// create panel
	ControlRoot root(canvas, true);
	ControlPanel panel(&root, 1, 8.0f, 8.0f);
	panel.setAlign(Control::AlignRight | Control::AlignTop);
	panel.setPosition(-8.0f, -8.0f);
	
	// create sliders
	ControlSlider scale_slider(&panel, "Scale", 3, 32.0f, 16.0f, 48.0f);
	scale_slider.setSize(192.0f, 0.0f);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() -> bool {
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
		
		// dispatch Cuda kernel
		{
			// dispatch Cuda kernel
			uint32_t num_groups = udiv(grid_size, group_size);
			cudaStream_t stream = (cudaStream_t)cu_context.getStream();
			float4 *data = (float4*)cu_position_buffer.getBufferPtr();
			kernel<<<dim3(num_groups, num_groups), dim3(group_size, group_size), 0, stream>>>(grid_size, scale_slider.getValuef32(), time, data);
			
			// check Cuda error
			cudaError_t error = cudaGetLastError();
			if(error != cudaSuccess) TS_LOGF(Error, "main(): %s\n", cudaGetErrorString(error));
			
			// synchronize stream
			cudaStreamSynchronize(stream);
		}
		
		// flush buffer
		device.flushBuffer(position_buffer);
		
		// window target
		target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
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
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(20.0f, 20.0f, 20.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 1.0f));
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

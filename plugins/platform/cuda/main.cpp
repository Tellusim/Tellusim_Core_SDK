// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <math/TellusimMath.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimContext.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>

#include "include/TellusimCU.h"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Cuda", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// geometry parameters
	constexpr uint32_t grid_size = 1024;
	constexpr uint32_t group_size = 8;
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
	};
	
	struct ComputeParameters {
		uint32_t size;
		float32_t scale;
		float32_t time;
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
	
	// initialize Cuda
	if(!CU::init()) {
		TS_LOG(Error, "main(): can't init Cuda\n");
		return 1;
	}
	
	// create Cuda device
	Device cu_device(cu_context);
	if(!cu_device) return 1;
	
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
	
	// create Cuda shader
	CUShader cu_shader = CUShader(cu_device.loadShaderGLSL(Shader::TypeCompute, "main.shader", "COMPUTE_SHADER=1"));
	if(!cu_shader) return 1;
	
	// create position buffer
	Buffer position_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagVertex | Buffer::FlagInterop, sizeof(float32_t) * 4 * grid_size * grid_size);
	if(!position_buffer) return 1;
	
	// create Cuda position buffer
	CUBuffer cu_position_buffer = CUBuffer(cu_device.createBuffer(position_buffer));
	if(!cu_position_buffer) return 1;
	
	// create Cuda uniform buffer
	CUBuffer cu_uniform_buffer = CUBuffer(cu_device.createBuffer(Buffer::FlagStorage, sizeof(ComputeParameters)));
	if(!cu_uniform_buffer) return 1;
	
	// create target
	Target target = device.createTarget(window);
	
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
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// update controls
		update_controls(window, root);
		canvas.create(device, target);
		
		// dispatch Cuda kernel
		{
			// set current context
			if(CUContext::error(Tellusim::cuCtxSetCurrent(cu_context.getCUContext()))) {
				TS_LOG(Error, "main(): can't set current context\n");
				return false;
			}
			
			// compute parameters
			ComputeParameters compute_parameters;
			compute_parameters.size = grid_size;
			compute_parameters.scale = scale_slider.getValuef32();
			compute_parameters.time = time;
			if(CUContext::error(Tellusim::cuMemcpyHtoD(cu_uniform_buffer.getBufferPtr(), &compute_parameters, sizeof(compute_parameters)))) {
				TS_LOG(Error, "main(): can't copy uniform parameters\n");
				return false;
			}
			
			// kernel parameters
			CUdeviceptr parameters[] = {
				cu_uniform_buffer.getBufferPtr(),
				cu_position_buffer.getBufferPtr(),
			};
			size_t parameters_size = sizeof(CUdeviceptr) * TS_COUNTOF(parameters);
			
			// launch options
			void *options[] = {
				CU_LAUNCH_PARAM_BUFFER_POINTER, parameters,
				CU_LAUNCH_PARAM_BUFFER_SIZE, &parameters_size,
				CU_LAUNCH_PARAM_END,
			};
			
			// launch kernel
			uint32_t num_groups = udiv(grid_size, group_size);
			if(CUContext::error(Tellusim::cuLaunchKernel(cu_shader.getFunction(), num_groups, num_groups, 1, group_size, group_size, 1, 0, cu_context.getStream(), nullptr, options))) {
				TS_LOG(Error, "main(): can't launch kernel\n");
				return false;
			}
			
			// synchronize stream
			if(CUContext::error(Tellusim::cuStreamSynchronize(cu_context.getStream()))) {
				TS_LOG(Error, "main(): can't synchronize stream\n");
				return false;
			}
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

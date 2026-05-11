// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <core/TellusimSource.h>
#include <math/TellusimMath.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimContext.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>

#include "include/TellusimCL.h"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::OpenCL", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// geometry parameters
	constexpr uint32_t grid_size = 1024;
	
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
	
	// initialize OpenCL
	if(!CL::open()) {
		TS_LOG(Error, "main(): can't open OpenCL\n");
		return 1;
	}
	
	// OpenCL platform info
	TS_LOGF(Message, "Platform Name: %s\n", CL::getName().get());
	TS_LOGF(Message, "Platform Vendor: %s\n", CL::getVendor().get());
	TS_LOGF(Message, "Platform Version: %s\n", CL::getVersion().get());
	TS_LOGF(Message, "Platform Extensions: %s\n", CL::getExtensions().get());
	
	// OpenCL device info
	for(uint32_t i = 0; i < CL::getNumDevices(); i++) {
		CLDevice *cl_device = CL::getDevice(i);
		TS_LOGF(Message, "Device %u Name: %s\n", i, cl_device->getName().get());
		TS_LOGF(Message, "Device %u Vendor: %s\n", i, cl_device->getVendor().get());
		TS_LOGF(Message, "Device %u Version: %s\n", i, cl_device->getVersion().get());
		TS_LOGF(Message, "Device %u Extensions: %s\n", i, cl_device->getExtensions().get());
	}
	
	// default OpenCL device
	CLDevice *cl_device = CL::getDevice(0);
	
	// check required OpenCL extension
	if(!cl_device->checkExtension("khr_external_memory")) {
		TS_LOG(Error, "main(): khr_external_memory extension is not supported\n");
		return 1;
	}
	
	// create OpenCL context
	cl_int ocl_error = CL_SUCCESS;
	cl_context_properties ocl_context_properties[] = {
		CL_CONTEXT_PLATFORM, (cl_context_properties)(cl_device->getPlatform()),
		0,
	};
	cl_device_id ocl_device_id = cl_device->getDevice();
	cl_context ocl_context = Tellusim::clCreateContext(ocl_context_properties, 1, &ocl_device_id, nullptr, nullptr, &ocl_error);
	if(CL::error(ocl_error)) return 1;
	
	// create OpenCL command queue
	cl_command_queue ocl_command_queue = Tellusim::clCreateCommandQueueWithProperties(ocl_context, ocl_device_id, nullptr, &ocl_error);
	if(CL::error(ocl_error)) return 1;
	
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
	
	// program source
	Source program_source;
	if(!program_source.open("kernel.cl")) return 1;
	const char *program_src = (const char*)program_source.getData();
	size_t program_size = program_source.getSize();
	
	// create OpenCL program
	cl_program ocl_program = Tellusim::clCreateProgramWithSource(ocl_context, 1, &program_src, &program_size, &ocl_error);
	if(CL::error(ocl_error)) return 1;
	
	// build OpenCL program
	if(CL::error(Tellusim::clBuildProgram(ocl_program, 1, &ocl_device_id, nullptr, nullptr, nullptr))) {
		char buffer[4096];
		Tellusim::clGetProgramBuildInfo(ocl_program, ocl_device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, nullptr);
		TS_LOGF(Error, "main(): %s\n", buffer);
		return 1;
	}
	
	// create kernel
	cl_kernel ocl_kernel = Tellusim::clCreateKernel(ocl_program, "main_", &ocl_error);
	if(CL::error(ocl_error)) return 1;
	
	// create position buffer
	Buffer position_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagVertex | Buffer::FlagInterop, sizeof(float32_t) * 4 * grid_size * grid_size);
	if(!position_buffer) return 1;
	
	// position buffer handle
	void *position_buffer_handle = nullptr;
	if(position_buffer.getPlatform() == PlatformVK) {
		VKBuffer vk_position_buffer = VKBuffer(position_buffer);
		if(!vk_position_buffer) return 1;
		position_buffer_handle = vk_position_buffer.getInteropHandle();
	} else if(position_buffer.getPlatform() == PlatformD3D12) {
		D3D12Buffer d3d12_position_buffer = D3D12Buffer(position_buffer);
		if(!d3d12_position_buffer) return 1;
		position_buffer_handle = d3d12_position_buffer.getInteropHandle();
	} else {
		return 1;
	}
	
	// create OpenCL position buffer
	cl_mem_properties ocl_position_buffer_properties[] = {
		#if _WIN32
			CL_EXTERNAL_MEMORY_HANDLE_OPAQUE_WIN32_KHR, (cl_mem_properties)position_buffer_handle,
		#else
			CL_EXTERNAL_MEMORY_HANDLE_OPAQUE_FD_KHR, (cl_mem_properties)position_buffer_handle,
		#endif
		0,
	};
	cl_mem ocl_position_buffer = Tellusim::clCreateBufferWithProperties(ocl_context, ocl_position_buffer_properties, CL_MEM_READ_WRITE, position_buffer.getSize(), nullptr, &ocl_error);
	if(CL::error(ocl_error)) return 1;
	
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
		
		// dispatch OpenCL kernel
		{
			float32_t scale = scale_slider.getValuef32();
			
			// aquire buffer
			if(CL::error(Tellusim::clEnqueueAcquireExternalMemObjectsKHR(ocl_command_queue, 1, &ocl_position_buffer, 0, nullptr, nullptr))) return false;
			
			// dispatch kernel
			size_t global_work_size[2] = { grid_size, grid_size };
			Tellusim::clSetKernelArg(ocl_kernel, 0, sizeof(cl_uint), &grid_size);
			Tellusim::clSetKernelArg(ocl_kernel, 1, sizeof(cl_float), &scale);
			Tellusim::clSetKernelArg(ocl_kernel, 2, sizeof(cl_float), &time);
			Tellusim::clSetKernelArg(ocl_kernel, 3, sizeof(cl_mem), &ocl_position_buffer);
			if(CL::error(Tellusim::clEnqueueNDRangeKernel(ocl_command_queue, ocl_kernel, 2, nullptr, global_work_size, nullptr, 0, nullptr, nullptr))) return false;
			
			// release buffer
			if(CL::error(Tellusim::clEnqueueReleaseExternalMemObjectsKHR(ocl_command_queue, 1, &ocl_position_buffer, 0, nullptr, nullptr))) return false;
			
			// finish queue
			if(CL::error(Tellusim::clFinish(ocl_command_queue))) return false;
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

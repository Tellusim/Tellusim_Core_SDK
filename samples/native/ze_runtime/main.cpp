// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <level_zero/ze_api.h>

#include <common/common.h>
#include <common/sample_controls.h>
#include <core/TellusimSource.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimContext.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	using namespace Tellusim;
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::ZeRuntime", window.getPlatformName());
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
	
	// create ZE context
	ze_init_driver_type_desc_t ze_driver_desc = {};
	ze_driver_desc.stype = ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC;
	ze_driver_desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_GPU;
	
	// get number of ZE drivers
	uint32_t num_ze_drivers = 0;
	if(zeInitDrivers(&num_ze_drivers, nullptr, &ze_driver_desc) != ZE_RESULT_SUCCESS || num_ze_drivers == 0) return 1;
	
	// get ZE drivers
	ArrayStack<ze_driver_handle_t, 16> ze_drivers(num_ze_drivers);
	if(zeInitDrivers(&num_ze_drivers, ze_drivers.get(), &ze_driver_desc) != ZE_RESULT_SUCCESS) return 1;
	ze_driver_handle_t ze_driver = ze_drivers[0];
	
	// get number of ZE devices
	uint32_t num_ze_devices = 0;
	if(zeDeviceGet(ze_driver, &num_ze_devices, nullptr) != ZE_RESULT_SUCCESS || num_ze_devices == 0) return 1;
	
	// get ZE devices
	ArrayStack<ze_device_handle_t, 16> ze_devices(num_ze_devices);
	if(zeDeviceGet(ze_driver, &num_ze_devices, ze_devices.get()) != ZE_RESULT_SUCCESS) return 1;
	ze_device_handle_t ze_device = ze_devices[0];
	
	// get ZE driver properties
	ze_driver_properties_t ze_driver_properties = {};
	ze_driver_properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
	if(zeDriverGetProperties(ze_driver, &ze_driver_properties) != ZE_RESULT_SUCCESS) return 1;
	
	// get ZE device properties
	ze_device_properties_t ze_device_properties = {};
	ze_device_properties.stype = ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES;
	if(zeDeviceGetProperties(ze_device, &ze_device_properties) != ZE_RESULT_SUCCESS) return 1;
	
	// ZE info
	TS_LOGF(Message, "Device: %s (0x%x)\n", ze_device_properties.name, ze_device_properties.deviceId);
	TS_LOGF(Message, "Version: %u\n", ze_driver_properties.driverVersion);
	
	// create ZE context
	ze_context_desc_t ze_context_desc = {};
	ze_context_desc.stype = ZE_STRUCTURE_TYPE_CONTEXT_DESC;
	
	ze_context_handle_t ze_context = nullptr;
	if(zeContextCreate(ze_driver, &ze_context_desc, &ze_context) != ZE_RESULT_SUCCESS) return 1;
	
	// create ZE command queue
	ze_command_queue_desc_t ze_command_queue_desc = {};
	ze_command_queue_desc.stype = ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC;
	ze_command_queue_desc.mode = ZE_COMMAND_QUEUE_MODE_ASYNCHRONOUS;
	
	ze_command_queue_handle_t ze_command_queue = nullptr;
	if(zeCommandQueueCreate(ze_context, ze_device, &ze_command_queue_desc, &ze_command_queue) != ZE_RESULT_SUCCESS) return 1;
	
	// create ZE command list
	ze_command_list_desc_t ze_command_list_desc = {};
	ze_command_list_desc.stype = ZE_STRUCTURE_TYPE_COMMAND_LIST_DESC;
	
	ze_command_list_handle_t ze_command_list = nullptr;
	if(zeCommandListCreate(ze_context, ze_device, &ze_command_list_desc, &ze_command_list) != ZE_RESULT_SUCCESS) return 1;
	
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
	
	// load module blob
	Source module_source;
	if(!module_source.open("kernel.spv") || module_source.getData() == nullptr) return 1;
	
	// create ZE module
	ze_module_desc_t ze_module_desc = {};
	ze_module_desc.stype = ZE_STRUCTURE_TYPE_MODULE_DESC;
	ze_module_desc.format = ZE_MODULE_FORMAT_IL_SPIRV;
	ze_module_desc.inputSize = module_source.getSize();
	ze_module_desc.pInputModule = (const uint8_t*)module_source.getData();
	
	ze_module_handle_t ze_module = nullptr;
	if(zeModuleCreate(ze_context, ze_device, &ze_module_desc, &ze_module, nullptr) != ZE_RESULT_SUCCESS) return 1;
	
	// create ZE kernel from module
	ze_kernel_desc_t ze_kernel_desc = {};
	ze_kernel_desc.stype = ZE_STRUCTURE_TYPE_KERNEL_DESC;
	ze_kernel_desc.pKernelName = "main_";
	
	ze_kernel_handle_t ze_kernel = nullptr;
	if(zeKernelCreate(ze_module, &ze_kernel_desc, &ze_kernel) != ZE_RESULT_SUCCESS) return 1;
	
	// set ZE kernel parameters
	if(zeKernelSetGroupSize(ze_kernel, group_size, group_size, 1) != ZE_RESULT_SUCCESS) return 1;
	
	// ZE external memory import desc
	ze_external_memory_import_win32_handle_t ze_memory_import_desc = {};
	ze_memory_import_desc.stype = ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMPORT_WIN32;
	ze_memory_import_desc.flags = ZE_EXTERNAL_MEMORY_TYPE_FLAG_OPAQUE_WIN32;
	
	// get interop handle
	if(position_buffer.getPlatform() == PlatformVK) {
		VKBuffer vk_position_buffer = VKBuffer(position_buffer);
		if(!vk_position_buffer) return 1;
		ze_memory_import_desc.handle = vk_position_buffer.getInteropHandle();
	} else if(position_buffer.getPlatform() == PlatformD3D12) {
		D3D12Buffer d3d12_position_buffer = D3D12Buffer(position_buffer);
		if(!d3d12_position_buffer) return 1;
		ze_memory_import_desc.handle = d3d12_position_buffer.getInteropHandle();
	} else {
		return 1;
	}
	
	// ZE memory allocation decs
	ze_device_mem_alloc_desc_t ze_alloc_desc = {};
	ze_alloc_desc.stype = ZE_STRUCTURE_TYPE_DEVICE_MEM_ALLOC_DESC;
	ze_alloc_desc.pNext = &ze_memory_import_desc;
	
	// import ZE memory
	void* ze_position_buffer = nullptr;
	if(zeMemAllocDevice(ze_context, &ze_alloc_desc, position_buffer.getSize(), 0, ze_device, &ze_position_buffer) != ZE_RESULT_SUCCESS) return 1;
	
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
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// update controls
		update_controls(window, root);
		canvas.create(device, target);
		
		// dispatch ZE kernel
		{
			float32_t scale = scale_slider.getValuef32();
			
			// reset command list
			if(zeCommandListReset(ze_command_list) != ZE_RESULT_SUCCESS) return false;
			
			// set kernel arguments
			zeKernelSetArgumentValue(ze_kernel, 0, sizeof(uint32_t), &grid_size);
			zeKernelSetArgumentValue(ze_kernel, 1, sizeof(float32_t), &scale);
			zeKernelSetArgumentValue(ze_kernel, 2, sizeof(float32_t), &time);
			zeKernelSetArgumentValue(ze_kernel, 3, sizeof(void*), &ze_position_buffer);
			
			// dispatch kernel
			ze_group_count_t ze_group_count = {};
			ze_group_count.groupCountX = grid_size / group_size;
			ze_group_count.groupCountY = grid_size / group_size;
			ze_group_count.groupCountZ = 1;
			
			if(zeCommandListAppendLaunchKernel(ze_command_list, ze_kernel, &ze_group_count, nullptr, 0, nullptr) != ZE_RESULT_SUCCESS) return false;
			
			// close command list
			if(zeCommandListClose(ze_command_list) != ZE_RESULT_SUCCESS) return false;
			
			// execute command list
			if(zeCommandQueueExecuteCommandLists(ze_command_queue, 1, &ze_command_list, nullptr) != ZE_RESULT_SUCCESS) return false;
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

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <level_zero/ze_api.h>

#include <common/common.h>
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
	String title = String::format("%s Tellusim::ZeTexture", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title);
	
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
	pipeline.setSamplerMask(0, Shader::MaskFragment);
	pipeline.setTextureMask(0, Shader::MaskFragment);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create sampler
	Sampler sampler = device.createSampler(Sampler::FilterLinear, Sampler::WrapModeClamp);
	if(!sampler) return 1;
	
	// create texture
	constexpr uint32_t texture_size = 1024;
	Texture texture = device.createTexture2D(FormatRGBAu8n, texture_size, Texture::FlagSurface | Texture::FlagInterop);
	if(!texture) return 1;
	
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
	constexpr uint32_t group_size = 8;
	if(zeKernelSetGroupSize(ze_kernel, group_size, group_size, 1) != ZE_RESULT_SUCCESS) return 1;
	
	// ZE external memory import desc
	ze_external_memory_import_win32_handle_t ze_memory_import_desc = {};
	ze_memory_import_desc.stype = ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMPORT_WIN32;
	ze_memory_import_desc.flags = ZE_EXTERNAL_MEMORY_TYPE_FLAG_OPAQUE_WIN32;
	
	// get interop handle
	if(texture.getPlatform() == PlatformVK) {
		VKTexture vk_texture = VKTexture(texture);
		if(!vk_texture) return 1;
		ze_memory_import_desc.handle = vk_texture.getInteropHandle();
	} else if(texture.getPlatform() == PlatformD3D12) {
		D3D12Texture d3d12_texture = D3D12Texture(texture);
		if(!d3d12_texture) return 1;
		ze_memory_import_desc.handle = d3d12_texture.getInteropHandle();
	} else {
		return 1;
	}
	
	// ZE image desc
	ze_image_desc_t ze_image_desc = {};
	ze_image_desc.stype = ZE_STRUCTURE_TYPE_IMAGE_DESC;
	ze_image_desc.pNext = &ze_memory_import_desc;
	ze_image_desc.flags = ZE_IMAGE_FLAG_KERNEL_WRITE;
	ze_image_desc.type = ZE_IMAGE_TYPE_2D;
	ze_image_desc.format.layout = ZE_IMAGE_FORMAT_LAYOUT_8_8_8_8;
	ze_image_desc.format.type = ZE_IMAGE_FORMAT_TYPE_UNORM;
	ze_image_desc.format.x = ZE_IMAGE_FORMAT_SWIZZLE_R;
	ze_image_desc.format.y = ZE_IMAGE_FORMAT_SWIZZLE_G;
	ze_image_desc.format.z = ZE_IMAGE_FORMAT_SWIZZLE_B;
	ze_image_desc.format.w = ZE_IMAGE_FORMAT_SWIZZLE_A;
	ze_image_desc.width = texture.getWidth();
	ze_image_desc.height = texture.getHeight();
	ze_image_desc.depth = 1;
	
	// create ZE image
	ze_image_handle_t ze_image = nullptr;
	if(zeImageCreate(ze_context, ze_device, &ze_image_desc, &ze_image) != ZE_RESULT_SUCCESS) return 1;
	
	// create target
	Target target = device.createTarget(window);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() -> bool {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// dispatch ZE kernel
		{
			// reset command list
			if(zeCommandListReset(ze_command_list) != ZE_RESULT_SUCCESS) return false;
			
			// set kernel arguments
			zeKernelSetArgumentValue(ze_kernel, 0, sizeof(uint32_t), &texture_size);
			zeKernelSetArgumentValue(ze_kernel, 1, sizeof(float32_t), &time);
			zeKernelSetArgumentValue(ze_kernel, 2, sizeof(ze_image_handle_t), &ze_image);
			
			// dispatch kernel
			ze_group_count_t ze_group_count = {};
			ze_group_count.groupCountX = texture_size / group_size;
			ze_group_count.groupCountY = texture_size / group_size;
			ze_group_count.groupCountZ = 1;
			
			if(zeCommandListAppendLaunchKernel(ze_command_list, ze_kernel, &ze_group_count, nullptr, 0, nullptr) != ZE_RESULT_SUCCESS) return false;
			
			// close command list
			if(zeCommandListClose(ze_command_list) != ZE_RESULT_SUCCESS) return false;
			
			// execute command list
			if(zeCommandQueueExecuteCommandLists(ze_command_queue, 1, &ze_command_list, nullptr) != ZE_RESULT_SUCCESS) return false;
		}
		
		// flush texture
		device.flushTexture(texture);
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// draw texture
			command.setPipeline(pipeline);
			command.setSampler(0, sampler);
			command.setTexture(0, texture);
			command.drawArrays(3);
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

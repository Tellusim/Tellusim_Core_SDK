// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <sycl/sycl.hpp>
#include <sycl/ext/oneapi/backend/level_zero.hpp>
#include <level_zero/ze_api.h>

#include <common/common.h>
#include <common/sample_controls.h>
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
	String title = String::format("%s Tellusim::SyclRuntime", window.getPlatformName());
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
	
	// create SYCL context
	sycl::queue sycl_queue(sycl::gpu_selector_v);
	sycl::device sycl_device = sycl_queue.get_device();
	sycl::context sycl_context = sycl_queue.get_context();
	
	// get ZE context
	ze_context_handle_t ze_context = sycl::get_native<sycl::backend::ext_oneapi_level_zero>(sycl_context);
	ze_device_handle_t ze_device  = sycl::get_native<sycl::backend::ext_oneapi_level_zero>(sycl_device);
	
	// SYCL info
	TS_LOGF(Message, "Platform: %s\n", sycl_device.get_platform().get_info<sycl::info::platform::name>().c_str());
	TS_LOGF(Message, "Device: %s\n", sycl_device.get_info<sycl::info::device::name>().c_str());
	TS_LOGF(Message, "Vendor: %s\n", sycl_device.get_info<sycl::info::device::vendor>().c_str());
	TS_LOGF(Message, "Version: %s\n", sycl_device.get_info<sycl::info::device::driver_version>().c_str());
	
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
	
	// SYCL backend input
	sycl::backend_input_t<sycl::backend::ext_oneapi_level_zero, sycl::buffer<sycl::float4, 1>> sycl_backend_input;
	sycl_backend_input.NativeHandle = ze_position_buffer;
	sycl_backend_input.Ownership = sycl::ext::oneapi::level_zero::ownership::keep;
	
	// create SYCL position buffer
	sycl::buffer<sycl::float4, 1> sycl_position_buffer = sycl::make_buffer<sycl::backend::ext_oneapi_level_zero, sycl::float4, 1>(sycl_backend_input, sycl_context);
	
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
		
		// dispatch SYCL kernel
		sycl_queue.submit([&](sycl::handler &handler) {
			
			float32_t scale = scale_slider.getValuef32();
			
			auto positions = sycl_position_buffer.get_access<sycl::access::mode::read_write>(handler);
			
			handler.parallel_for(sycl::range<2>(grid_size, grid_size), [=](sycl::id<2> global_id) {
				
				uint32_t id = global_id[1] * grid_size + global_id[0];
				
				float32_t x = (float32_t)global_id[0] / grid_size * 2.0f - 1.0f;
				float32_t y = (float32_t)global_id[1] / grid_size * 2.0f - 1.0f;
				
				float32_t r = sycl::sin(x * scale) * 0.5f + 0.5f;
				float32_t g = sycl::cos(y * scale) * 0.5f + 0.5f;
				float32_t b = sycl::max(1.0f - r - g, 0.0f);
				
				uint32_t color = 0xff000000u;
				color |= (uint32_t)(r * 255.0f) << 0u;
				color |= (uint32_t)(g * 255.0f) << 8u;
				color |= (uint32_t)(b * 255.0f) << 16u;
				
				float32_t z = r + g + sycl::sin(sycl::sqrt(x * x + y * y) * 4.0f + time * 2.0f) * 4.0f;
				
				positions[id] = sycl::float4(x * scale, y * scale, z, sycl::bit_cast<float32_t>(color));
			});
		});
		
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

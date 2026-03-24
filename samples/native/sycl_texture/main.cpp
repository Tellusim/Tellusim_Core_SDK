// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <sycl/sycl.hpp>
#include <sycl/ext/oneapi/backend/level_zero.hpp>
#include <level_zero/ze_api.h>

#include <common/common.h>
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
	String title = String::format("%s Tellusim::SyclTexture", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title);
	
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
	
	// SYCL backend input
	sycl::backend_input_t<sycl::backend::ext_oneapi_level_zero, sycl::image<2>> sycl_backend_input;
	sycl_backend_input.ZeImageHandle = ze_image;
	sycl_backend_input.ChanOrder = sycl::image_channel_order::rgba;
	sycl_backend_input.ChanType = sycl::image_channel_type::unorm_int8;
	sycl_backend_input.Range = sycl::range<2>(texture.getWidth(), texture.getHeight());
	sycl_backend_input.Ownership = sycl::ext::oneapi::level_zero::ownership::keep;
	
	// create SYCL image
	sycl::image<2> sycl_image = sycl::make_image<sycl::backend::ext_oneapi_level_zero, 2>(sycl_backend_input, sycl_context);
	
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
		
		// dispatch SYCL kernel
		sycl_queue.submit([&](sycl::handler &handler) {
			
			auto surface = sycl_image.get_access<sycl::float4, sycl::access_mode::write>(handler);
			
			handler.parallel_for(sycl::range<2>(texture_size, texture_size), [=](sycl::id<2> global_id) {
				
				float32_t k = time * 2.0f;
				float32_t s = sycl::sin(time * 0.5f);
				float32_t c = sycl::cos(time * 0.5f);
				
				sycl::float2 t = sycl::float2((float32_t)global_id[0] / texture_size - 0.5f, (float32_t)global_id[1] / texture_size - 0.5f);
				
				t = sycl::float2((s * t.x() + c * t.y()) * 32.0f - 16.0f, (c * t.x() - s * t.y()) * 32.0f - 16.0f);
				
				float32_t v = sycl::sin(t.x() + k) + sycl::sin(t.y() + k) + sycl::sin(t.x() + t.y() + k) + sycl::sin(sycl::sqrt(t.x() * t.x() + t.y() * t.y()) + k * 3.0f) + k * 2.0f;
				
				float32_t r = sycl::cos(v + 0.00f) * 0.5f + 0.5f;
				float32_t g = sycl::cos(v + 1.57f) * 0.5f + 0.5f;
				float32_t b = sycl::cos(v + 3.14f) * 0.5f + 0.5f;
				
				surface.write(sycl::int2(global_id[0], global_id[1]), sycl::float4(r, g, b, 1.0f));
			});
		});
		
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

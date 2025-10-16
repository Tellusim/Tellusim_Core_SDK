// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <core/TellusimString.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimTarget.h>
#include <platform/TellusimSurface.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	if(!window) return 1;
	
	// create window
	String title = String::format("%s Tellusim::Surface", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create target
	Device device = Device(window);
	Target target = device.createTarget(window);
	
	// window surface
	Surface surface = window.getSurface();
	TS_LOGF(Message, "%s\n", surface.getPlatformName());
	TS_LOGF(Message, "Size: %ux%u\n", surface.getWidth(), surface.getHeight());
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		using Tellusim::sin;
		using Tellusim::cos;
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window surface
		if(frame_counter < 4) {
			
			// frame number
			TS_LOGF(Message, "Frame: %u\n", frame_counter);
			
			// Direct3D12 surface
			if(surface.getPlatform() == PlatformD3D12) {
				D3D12Surface d3d12_surface = D3D12Surface(surface);
				TS_LOGF(Message, "RenderTargetView: %" TS_FORMAT_64 "u\n", (uint64_t)d3d12_surface.getRenderTargetView());
				TS_LOGF(Message, "DepthStencilView: %" TS_FORMAT_64 "u\n", (uint64_t)d3d12_surface.getDepthStencilView());
			}
			
			// Direct3D11 surface
			if(surface.getPlatform() == PlatformD3D11) {
				D3D11Surface d3d11_surface = D3D11Surface(surface);
				TS_LOGF(Message, "RenderTargetView: %p\n", d3d11_surface.getRenderTargetView());
				TS_LOGF(Message, "DepthStencilView: %p\n", d3d11_surface.getDepthStencilView());
			}
			
			// Metal surface
			if(surface.getPlatform() == PlatformMTL) {
				MTLSurface mtl_surface = MTLSurface(surface);
				TS_LOGF(Message, "Descriptor: %p\n", mtl_surface.getDescriptor());
			}
			
			// Vulkan surface
			if(surface.getPlatform() == PlatformVK) {
				VKSurface vk_surface = VKSurface(surface);
				TS_LOGF(Message, "RenderPass: %p\n", vk_surface.getRenderPass());
				TS_LOGF(Message, "Framebuffer: %p\n", vk_surface.getFramebuffer());
			}
			
			// OpenGL surface
			if(surface.getPlatform() == PlatformGL) {
				GLSurface gl_surface = GLSurface(surface);
				TS_LOGF(Message, "FramebufferID: %u\n", gl_surface.getFramebufferID());
			}
		}
		
		// window target
		target.setClearColor(Color(sin(time), cos(time), sin(time) * cos(time)) * 0.5f + 0.5f);
		target.begin();
		target.end();
		
		if(!window.present()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}

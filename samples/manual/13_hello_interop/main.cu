// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <TellusimApp.h>
#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <platform/TellusimWindow.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimContext.h>
#include <interface/TellusimCanvas.h>

/*
 */
__global__ void kernel(uint32_t size, float time, cudaSurfaceObject_t surface) {
	
	uint32_t global_x = blockDim.x * blockIdx.x + threadIdx.x;
	uint32_t global_y = blockDim.y * blockIdx.y + threadIdx.y;
	
	float x = (float)global_x * 2.0f / (float)(size - 1) - 1.0f;
	float y = (float)global_y * 2.0f / (float)(size - 1) - 1.0f;
	
	float angle = atan2(y, x);
	float radius = sqrt(x * x + y * y) + 0.1f;
	
	x = 3.0f / radius + time * 3.0f;
	y = angle * 2.0f + time * 0.5f;
	
	float k = sin(x - y * 0.5f) * 4.0f + sin(y) * sin(4.0f / radius) * 3.0f;
	k = sin(tanh(k * 0.8f) * 3.0f - k * 0.2f) * 0.5f + 0.5f;
	
	uint32_t r = (uint32_t)(255.0f * pow(k, 0.9f));
	uint32_t g = (uint32_t)(255.0f * pow(k, 0.2f));
	uint32_t b = (uint32_t)(255.0f * pow(k, 1.0f));
	
	surf2Dwrite(make_uchar4(r, g, b, 255), surface, global_x * sizeof(uchar4), global_y);
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	using namespace Tellusim;
	
	// create app
	App app(argc, argv);
	if(!app.create()) return 1;
	
	// create window
	Window window(app.getPlatform(), app.getDevice());
	if(!window || !window.setSize(app.getWidth(), app.getHeight())) return 1;
	if(!window.create("13 Hello Interop") || !window.setHidden(false)) return 1;
	window.setKeyboardPressedCallback([&](uint32_t key, uint32_t code) {
		if(key == Window::KeyEsc) window.stop();
	});
	window.setCloseClickedCallback([&]() { window.stop(); });
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// device info
	const Device::Features &features = device.getFeatures();
	TS_LOGF(Message, "%s 0x%x\n", device.getName().get(), features.pciBusID);
	
	// create Cuda context for device
	CUContext cu_context = CUContext(Context(PlatformCU, features.pciBusID));
	if(!cu_context || !cu_context.create()) {
		TS_LOG(Error, "Can't create Cuda context\n");
		return 1;
	}
	
	// set Cuda device
	if(cudaSetDevice(cu_context.getDevice()) != cudaSuccess) return 1;
	
	// create Cuda device
	Device cu_device(cu_context);
	if(!cu_device) return 1;
	
	// create texture
	uint32_t texture_size = 2048;
	Texture texture = device.createTexture2D(FormatRGBAu8n, texture_size, Texture::FlagSurface | Texture::FlagInterop);
	if(!texture) return 1;
	
	// create Cuda texture
	CUTexture cu_texture = CUTexture(cu_device.createTexture(texture));
	if(!cu_texture) return 1;
	
	// create Cuda surface desc
	cudaResourceDesc surface_desc = {};
	surface_desc.resType = cudaResourceTypeArray;
	surface_desc.res.array.array = (cudaArray_t)cu_texture.getTextureLevel(0);
	
	// create Cuda surface
	cudaSurfaceObject_t cu_surface = 0;
	cudaError_t error = cudaCreateSurfaceObject(&cu_surface, &surface_desc);
	if(error != cudaSuccess) return 1;
	
	// create canvas
	Canvas canvas;
	
	// set viewport size
	float32_t width = 1600.0f;
	float32_t height = 900.0f;
	canvas.setViewport(width, height);
	
	// create background rectangle
	CanvasRect texture_rect(canvas);
	texture_rect.setMode(CanvasElement::ModeTexture);
	texture_rect.setPosition(width * 0.5f, height * 0.5f);
	texture_rect.setSize(width, height);
	texture_rect.setTexture(texture);
	
	// create target
	Target target = device.createTarget(window);
	if(!target) return 1;
	
	// main loop
	window.run([&]() {
		
		Window::update();
		
		// render window
		if(!window.render()) return false;
		
		// current time
		float32_t time = (float32_t)Time::seconds();
		
		// create canvas
		if(!canvas.create(device, target)) return false;
		
		// dispatch Cuda kernel
		{
			// dispatch Cuda kernel
			uint32_t group_size = 8;
			uint32_t num_groups = udiv(texture_size, group_size);
			cudaStream_t stream = (cudaStream_t)cu_context.getStream();
			kernel<<<dim3(num_groups, num_groups), dim3(group_size, group_size), 0, stream>>>(texture_size, time, cu_surface);
			
			// check Cuda error
			cudaError_t error = cudaGetLastError();
			if(error != cudaSuccess) TS_LOGF(Error, "%s\n", cudaGetErrorString(error));
			
			// synchronize stream
			cudaStreamSynchronize(stream);
		}
		
		// flush texture
		device.flushTexture(texture);
		
		// window target
		target.begin();
		{
			Command command = device.createCommand(target);
			canvas.draw(command);
		}
		target.end();
		
		// present window
		if(!window.present()) return false;
		
		// check errors
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}

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
__global__ void kernel(uint32_t size, float time, cudaSurfaceObject_t surface) {
	
	uint32_t global_x = blockDim.x * blockIdx.x + threadIdx.x;
	uint32_t global_y = blockDim.y * blockIdx.y + threadIdx.y;
	
	float k = time * 2.0f;
	
	float s = sin(time * 0.5f);
	float c = cos(time * 0.5f);
	
	float2 t = make_float2((float)global_x / (float)size - 0.5f, (float)global_y / (float)size - 0.5f);
	
	t = make_float2((s * t.x + c * t.y) * 32.0f - 16.0f, (c * t.x - s * t.y) * 32.0f - 16.0f);
	
	float v = sin(t.x + k) + sin(t.y + k) + sin(t.x + t.y + k) + sin(sqrt(t.x * t.x + t.y * t.y) + k * 3.0f) + k * 2.0f;
	
	float r = (cos(v + 0.00f) * 0.5f + 0.5f) * 255.0f;
	float g = (cos(v + 1.57f) * 0.5f + 0.5f) * 255.0f;
	float b = (cos(v + 3.14f) * 0.5f + 0.5f) * 255.0f;
	uchar4 color = make_uchar4((uint8_t)r, (uint8_t)g, (uint8_t)b, 255);
	
	surf2Dwrite(color, surface, global_x * sizeof(uchar4), global_y);
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	using namespace Tellusim;
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::CudaTexture", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title);
	
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
	
	// create target
	Target target = device.createTarget(window);
	
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
		
		// dispatch Cuda kernel
		{
			// dispatch Cuda kernel
			uint32_t group_size = 8;
			uint32_t num_groups = udiv(texture_size, group_size);
			cudaStream_t stream = (cudaStream_t)cu_context.getStream();
			kernel<<<dim3(num_groups, num_groups), dim3(group_size, group_size), 0, stream>>>(texture_size, time, cu_surface);
			
			// check Cuda error
			cudaError_t error = cudaGetLastError();
			if(error != cudaSuccess) TS_LOGF(Error, "main(): %s\n", cudaGetErrorString(error));
			
			// synchronize stream
			cudaStreamSynchronize(stream);
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

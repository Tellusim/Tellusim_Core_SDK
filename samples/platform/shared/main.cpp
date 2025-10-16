// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCompute.h>
#include <platform/TellusimCommand.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Shared", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// structures
	struct ComputeParameters {
		float32_t positions_x[4];
		float32_t positions_y[4];
		uint32_t offset_x;
		uint32_t offset_y;
	};
	
	// create primary device
	Device device(window);
	if(!device) return 1;
	
	// check compute shader support
	if(!device.hasShader(Shader::TypeCompute)) {
		TS_LOG(Error, "compute shader is not supported\n");
		return 0;
	}
	
	// create secondary device
	Device secondary_device;
	if((device.getPlatform() == PlatformVK || device.getPlatform() == PlatformD3D12) && !app.isArgument("single")) {
		secondary_device = device.createDevice(1);
		if(!secondary_device) secondary_device.clearPtr();
	}
	if(secondary_device && !secondary_device.hasShader(Shader::TypeCompute)) secondary_device.clearPtr();
	if(!secondary_device) secondary_device = device.createDevice(device.getIndex());
	if(!secondary_device) {
		TS_LOG(Error, "can't create secondary device\n");
		return 0;
	}
	
	// device info
	TS_LOGF(Message, "%s (%s) %u\n", device.getName().get(), device.getPlatformName(), device.getIndex());
	TS_LOGF(Message, "%s (%s) %u\n", secondary_device.getName().get(), secondary_device.getPlatformName(), secondary_device.getIndex());
	
	// create kernels
	Kernel primary_kernel = device.createKernel().setSurfaces(1).setUniforms(1);
	Kernel secondary_kernel = secondary_device.createKernel().setSurfaces(1).setUniforms(1);
	if(!primary_kernel.loadShaderGLSL("main.shader", "COMPUTE_SHADER=1")) return 1;
	if(!secondary_kernel.loadShaderGLSL("main.shader", "COMPUTE_SHADER=1")) return 1;
	if(!primary_kernel.create() || !secondary_kernel.create()) return 1;
	
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
	Sampler sampler = device.createSampler(Sampler::FilterLinear, Sampler::WrapModeRepeat);
	if(!sampler) return 1;
	
	// create surfaces
	constexpr uint32_t width = 3840;
	constexpr uint32_t height = 2160;
	Texture primary_surface = device.createTexture2D(FormatRGBAu8n, width, height, Texture::FlagSurface);
	Texture secondary_surface = secondary_device.createTexture2D(FormatRGBAu8n, width, height, Texture::FlagSurface | Texture::FlagSource);
	if(!primary_surface || !secondary_surface) return 1;
	
	// create shared textures
	Texture shared_primary_texture = device.createTexture2D(FormatRGBAu8n, width, height, Texture::FlagSource | Texture::FlagShared);
	Texture shared_secondary_texture = secondary_device.createTexture(shared_primary_texture);
	if(!shared_primary_texture || !shared_secondary_texture) return 1;
	
	// print texture info
	TS_LOGF(Message, "%s\n", shared_secondary_texture.getDescription().get());
	
	// create primary to secondary shared fence
	Fence primary_fence_0 = device.createFence(Fence::FlagSignaled | Fence::FlagShared);
	Fence secondary_fence_0 = secondary_device.createFence(primary_fence_0);
	if(!primary_fence_0 || !secondary_fence_0) return 1;
	
	// create secondary to primary shared fence
	Fence secondary_fence_1 = secondary_device.createFence(Fence::FlagShared);
	Fence primary_fence_1 = device.createFence(secondary_fence_1);
	if(!primary_fence_1 || !secondary_fence_1) return 1;
	
	// create target
	Target target = device.createTarget(window);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		using Tellusim::sin;
		using Tellusim::cos;
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) {
			String bandwidth = String::fromBytes((size_t)(4 * width * height / 2 * fps)) + "/s";
			window.setTitle(String::format("%s %.1f FPS %s", title.get(), fps, bandwidth.get()));
		}
		
		{
			// create command lists
			Compute primary_compute = device.createCompute();
			Compute secondary_compute = secondary_device.createCompute();
			
			// compute parameters
			float32_t time_x = time * 0.5f;
			float32_t time_y = time * 3.0f;
			ComputeParameters compute_parameters;
			compute_parameters.positions_x[0] = width * (sin(time_x - 0.2f) * 0.4f + 0.5f);
			compute_parameters.positions_x[1] = width * (sin(time_x - 0.1f) * 0.4f + 0.5f);
			compute_parameters.positions_x[2] = width * (sin(time_x + 0.1f) * 0.4f + 0.5f);
			compute_parameters.positions_x[3] = width * (sin(time_x + 0.2f) * 0.4f + 0.5f);
			compute_parameters.positions_y[0] = height * (cos(time_y - 0.2f) * 0.4f + 0.5f);
			compute_parameters.positions_y[1] = height * (cos(time_y - 0.1f) * 0.4f + 0.5f);
			compute_parameters.positions_y[2] = height * (cos(time_y + 0.1f) * 0.4f + 0.5f);
			compute_parameters.positions_y[3] = height * (cos(time_y + 0.2f) * 0.4f + 0.5f);
			
			// dispatch primary kernel
			compute_parameters.offset_x = 0;
			compute_parameters.offset_y = 0;
			primary_compute.setKernel(primary_kernel);
			primary_compute.setSurfaceTexture(0, primary_surface);
			primary_compute.setUniform(0, compute_parameters);
			primary_compute.dispatch(width / 2, height);
			primary_compute.barrier(primary_surface);
			
			// dispatch secondary kernel
			compute_parameters.offset_x = width / 2;
			compute_parameters.offset_y = 0;
			secondary_compute.setKernel(secondary_kernel);
			secondary_compute.setSurfaceTexture(0, secondary_surface);
			secondary_compute.setUniform(0, compute_parameters);
			secondary_compute.dispatch(width / 2, height);
			secondary_compute.barrier(secondary_surface);
		}
		
		device.flushTexture(primary_surface);
		secondary_device.flushTexture(secondary_surface);
		
		{
			Origin origin = Origin(width / 2, 0);
			Region region = Region(width / 2, 0, width / 2, height);
			
			// synchronization flag
			bool sync = !window.getKeyboardKey('s');
			
			// copy secondary texture to shared texture and flip secondary device
			if(sync) secondary_device.waitFence(secondary_fence_0);
			secondary_device.copyTexture(shared_secondary_texture, origin, secondary_surface, region);
			if(sync) secondary_device.flip(secondary_fence_1);
			else secondary_device.flip();
			
			// copy shared texture to primary texture
			if(sync) device.waitFence(primary_fence_1);
			device.copyTexture(primary_surface, origin, shared_primary_texture, region);
			if(sync) device.signalFence(primary_fence_0);
		}
		
		// flush texture
		device.flushTexture(primary_surface);
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// draw surface
			command.setPipeline(pipeline);
			command.setSampler(0, sampler);
			command.setTexture(0, primary_surface);
			command.drawArrays(3);
		}
		target.end();
		
		if(!window.present()) return false;
		
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish secondary context
	secondary_device.finish();
	
	// finish context
	window.finish();
	
	return 0;
}

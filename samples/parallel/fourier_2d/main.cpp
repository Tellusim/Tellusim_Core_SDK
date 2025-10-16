// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <core/TellusimAsync.h>
#include <math/TellusimMath.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimCommand.h>
#include <platform/TellusimCompute.h>
#include <parallel/TellusimFourierTransform.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Fourier2D", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// structures
	struct CommonParameters {
		Vector4f size;
		float32_t scale;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check compute shader support
	if(!device.hasShader(Shader::TypeCompute)) {
		TS_LOG(Error, "compute shader is not supported\n");
		return 0;
	}
	
	// shader cache
	Shader::setCache("main.cache");
	
	// create sampler
	Sampler sampler = device.createSampler(Sampler::FilterLinear, Sampler::WrapModeBorder);
	if(!sampler) return 1;
	
	// create source texture
	Image image;
	if(!image.load("image.hdr")) return 1;
	image = image.getResized(Size(2048, 2048));
	image = image.getRegion(Region(3 * 5 * 7 * 16, 3 * 6 * 64));
	Texture src_texture = device.createTexture(image);
	const uint32_t width = src_texture.getWidth();
	const uint32_t height = src_texture.getHeight();
	if(!src_texture) return 1;
	
	// create kernel texture
	Image kernel;
	float32_t kernel_average = 0.0f;
	if(!kernel.load("kernel.png")) return 1;
	if(width < kernel.getWidth() || height < kernel.getHeight()) return 1;
	image.create2D(kernel.getFormat(), image.getWidth(), image.getHeight());
	ImageSampler src(kernel), dest(image);
	for(uint32_t y = 0; y < src.getHeight(); y++) {
		for(uint32_t x = 0; x < src.getWidth(); x++) {
			uint32_t X = x + ((x > src.getWidth() / 2) ? dest.getWidth() - src.getWidth() : 0);
			uint32_t Y = y + ((y > src.getHeight() / 2) ? dest.getHeight() - src.getHeight() : 0);
			ImageColor color = src.get2D(x + src.getWidth() / 2, y + src.getHeight() / 2, true);
			kernel_average += color.u.r * (1.0f / 255.0f);
			dest.set2D(X, Y, color);
		}
	}
	Texture kernel_texture = device.createTexture(image);
	if(!kernel_texture) return 1;
	
	// print textures info
	TS_LOGF(Message, "%s\n", src_texture.getDescription().get());
	TS_LOGF(Message, "%s\n", kernel_texture.getDescription().get());
	
	// mode
	struct Mode {
		FourierTransform::Mode mode;
		Format forward_format;
		Format backward_format;
		uint32_t forward_layers;
		const char *macros;
		const char *name;
		char key;
	};
	
	Mode modes[] = {
		{ FourierTransform::ModeRGBf21c, FormatRGBAf32, FormatRGBAf16, 1, "MODE_RGBF21C=1; SURFACE_FORMAT=rgba32f", "RGBf21c", '1' },
		{ FourierTransform::ModeRGBf16c, FormatRGBAf32, FormatRGBAf16, 1, "MODE_RGBF16C=1; SURFACE_FORMAT=rgba32f", "RGBf16c", '2' },
		{ FourierTransform::ModeRGBf16p, FormatRGBAf16, FormatRGBAf16, 2, "MODE_RGBF16P=1; SURFACE_FORMAT=rgba16f", "RGBf16p", '3' },
		{ FourierTransform::ModeRGBf32p, FormatRGBAf32, FormatRGBAf32, 2, "MODE_RGBF32P=1; SURFACE_FORMAT=rgba32f", "RGBf32p", '4' },
	};
	
	// create async
	Async async;
	if(device.getFeatures().threadAccess && !async.init()) return 1;
	
	// create transform
	uint32_t flags = 0;
	FourierTransform transform;
	uint64_t begin = Time::current();
	for(uint32_t i = 0; i < TS_COUNTOF(modes); i++) flags |= 1 << modes[i].mode;
	if(!transform.create(device, (FourierTransform::Flags)flags | FourierTransform::FlagNpot, npot(width) / 2, npot(height), &async)) return 1;
	TS_LOGF(Message, "create transform: %s\n", String::fromTime(Time::current() - begin).get());
	
	// create pipelines
	Pipeline pipelines[TS_COUNTOF(modes)];
	for(uint32_t i = 0; i < TS_COUNTOF(modes); i++) {
		pipelines[i] = device.createPipeline();
		pipelines[i].setSamplerMask(0, Shader::MaskFragment);
		pipelines[i].setTextureMasks(0, 3, Shader::MaskFragment);
		pipelines[i].setUniformMask(0, Shader::MaskVertexFragment);
		pipelines[i].setColorFormat(window.getColorFormat());
		pipelines[i].setDepthFormat(window.getDepthFormat());
		if(!pipelines[i].loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
		if(!pipelines[i].loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1; %s", modes[i].macros)) return 1;
		if(!pipelines[i].create()) return 1;
	}
	
	// create kernels
	Kernel kernels[TS_COUNTOF(modes)];
	for(uint32_t i = 0; i < TS_COUNTOF(modes); i++) {
		kernels[i] = device.createKernel().setTextures(2).setSurfaces(1).setUniforms(1);
		if(!kernels[i].loadShaderGLSL("main.shader", "COMPUTE_SHADER=1; %s", modes[i].macros)) return 1;
		if(!kernels[i].create()) return 1;
	}
	
	// create textures
	Texture forward_textures[TS_COUNTOF(modes)][3];
	Texture backward_textures[TS_COUNTOF(modes)];
	for(uint32_t i = 0; i < TS_COUNTOF(modes); i++) {
		if(!device.hasSurface(modes[i].forward_format) || !device.hasSurface(modes[i].backward_format)) continue;
		forward_textures[i][0] = device.createTexture2D(modes[i].forward_format, width / 2 + 1, height, modes[i].forward_layers, Texture::FlagSurface);
		forward_textures[i][1] = device.createTexture2D(modes[i].forward_format, width / 2 + 1, height, modes[i].forward_layers, Texture::FlagSurface);
		forward_textures[i][2] = device.createTexture2D(modes[i].forward_format, width / 2 + 1, height, modes[i].forward_layers, Texture::FlagSurface);
		backward_textures[i] = device.createTexture2D(modes[i].backward_format, width, height, Texture::FlagSurface);
		if(!forward_textures[i][0] || !forward_textures[i][1] || !forward_textures[i][2] || !backward_textures[i]) return 1;
	}
	
	// dispatch convolution transform
	{
		Compute compute = device.createCompute();
		for(uint32_t i = 0; i < TS_COUNTOF(modes); i++) {
			transform.dispatch(compute, modes[i].mode, FourierTransform::ForwardRtoC, forward_textures[i][2], kernel_texture);
		}
	}
	
	// create queries
	Query forward_query;
	Query backward_query;
	if(device.hasQuery(Query::TypeTime)) {
		forward_query = device.createQuery(Query::TypeTime);
		backward_query = device.createQuery(Query::TypeTime);
		if(!forward_query || !backward_query) return 1;
	}
	
	// create target
	Target target = device.createTarget(window);
	
	uint32_t mode = 0;
	uint32_t old_mode = 0;
	
	bool difference = false;
	bool convolution = true;
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f || mode != old_mode) {
			String forward_time = String::fromTime((forward_query && forward_query.isAvailable()) ? forward_query.getTime() : 0);
			String backward_time = String::fromTime((backward_query && backward_query.isAvailable()) ? backward_query.getTime() : 0);
			window.setTitle(String::format("%s FPS: %.1f %s %s %s", title.get(), fps, modes[mode].name, forward_time.get(), backward_time.get()));
			old_mode = mode;
		}
		
		// select mode
		for(uint32_t i = 0; i < TS_COUNTOF(modes); i++) {
			if(window.getKeyboardKey(modes[i].key) && forward_textures[i][0]) mode = i;
		}
		if(window.getKeyboardKey('d', true)) {
			difference = !difference;
			convolution = false;
		}
		if(window.getKeyboardKey(' ', true)) {
			convolution = !convolution;
			difference = false;
		}
		
		{
			// create command list
			Compute compute = device.createCompute();
			
			// dispatch convolution transform
			Texture forward_texture = forward_textures[mode][0];
			Texture convolution_texture = forward_textures[mode][2];
			if(convolution) forward_texture = forward_textures[mode][1];
			
			// dispatch forward transform
			if(forward_query) compute.beginQuery(forward_query);
			transform.dispatch(compute, modes[mode].mode, FourierTransform::ForwardRtoC, forward_texture, src_texture);
			if(forward_query) compute.endQuery(forward_query);
			
			// dispatch convolution kernel
			if(convolution) {
				compute.setKernel(kernels[mode]);
				compute.setUniform(0, src_texture.getWidth() / kernel_average);
				compute.setTextures(0, { forward_texture, convolution_texture });
				compute.setSurfaceTexture(0, forward_textures[mode][0]);
				compute.dispatch(forward_texture.getSize());
			}
			
			// dispatch backward transform
			if(backward_query) compute.beginQuery(backward_query);
			transform.dispatch(compute, modes[mode].mode, FourierTransform::BackwardCtoR, backward_textures[mode], forward_textures[mode][0]);
			if(backward_query) compute.endQuery(backward_query);
		}
		
		// flush textures
		device.flushTextures({ src_texture, forward_textures[mode][0], backward_textures[mode] });
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// common parameters
			CommonParameters common_parameters;
			common_parameters.size = Vector4f((float32_t)window.getWidth(), (float32_t)window.getHeight(), (float32_t)width, (float32_t)height);
			common_parameters.scale = (difference) ? 32.0f : 0.0f;
			
			// draw surface
			command.setPipeline(pipelines[mode]);
			command.setTextures(0, { src_texture, backward_textures[mode], forward_textures[mode][0] });
			command.setUniform(0, common_parameters);
			command.setSampler(0, sampler);
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

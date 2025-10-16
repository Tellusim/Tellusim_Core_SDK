// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <math/TellusimMath.h>
#include <format/TellusimMesh.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>
#include <platform/TellusimCompute.h>
#include <graphics/TellusimSeparableFilter.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::SeparableFilter", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// check compute shader support
	if(!device.hasShader(Shader::TypeCompute)) {
		TS_LOG(Error, "compute shader is not supported\n");
		return 0;
	}
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setSamplerMask(0, Shader::MaskFragment);
	pipeline.setTextureMask(0, Shader::MaskFragment);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create texture
	Texture texture = device.loadTexture("texture.exr");
	if(!texture) return 1;
	
	// create separable filter
	SeparableFilter filter;
	SeparableFilter::Flags flags = SeparableFilter::DefaultFlags;
	
	// create surfaces
	Texture surface_0 = device.createTexture2D(texture.getFormat(), texture.getWidth(), texture.getHeight(), Texture::FlagSurface);
	Texture surface_1 = device.createTexture2D(texture.getFormat(), texture.getWidth(), texture.getHeight(), Texture::FlagSurface);
	if(!surface_0 || !surface_1) return 1;
	
	// create sampler
	Sampler sampler = device.createSampler(Sampler::FilterLinear, Sampler::WrapModeClamp);
	if(!sampler) return 1;
	
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
	ControlSlider size_slider(&panel, "Size", 32, 0, 128);
	size_slider.setFormatCallback([&](ControlSlider slider) {
		return String::format("%u (%u)", slider.getValueu32() * 2 + 1, slider.getValueu32());
	});
	size_slider.setSize(192.0f, 0.0f);
	
	ControlSlider sigma_slider(&panel, "Sigma", 2, 8.0f, 0.0f, 32.0f);
	sigma_slider.setSize(192.0f, 0.0f);
	
	ControlCombo weights_combo(&panel, { "Gaussian", "SobelX", "SobelY", "Box" });
	weights_combo.setAlign(Control::AlignExpandX);
	
	ControlCombo border_combo(&panel, { "Clamp", "Repeat", "Zero" });
	border_combo.setChangedCallback([&](ControlCombo combo) {
		flags = SeparableFilter::DefaultFlags;
		const String &mode = combo.getCurrentText();
		if(mode == "Repeat") flags |= SeparableFilter::FlagRepeat;
		if(mode == "Zero") flags |= SeparableFilter::FlagZero;
		window.finish();
		filter.clear();
	});
	border_combo.setAlign(Control::AlignExpandX);
	
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
		
		// filter weights
		uint32_t size = size_slider.getValueu32();
		const String &mode = weights_combo.getCurrentText();
		if(mode == "Gaussian") filter.setGaussianWeights(size, sigma_slider.getValuef32());
		else if(mode == "SobelX") filter.setSobelXWeights(size);
		else if(mode == "SobelY") filter.setSobelYWeights(size);
		else if(mode == "Box") filter.setBoxWeights(size);
		
		// create separable filter
		if(!filter.isCreated(texture.getFormat(), size)) {
			filter.setOutputSource(SeparableFilter::ModeVertical, "pow(max(value, TYPE(0.0f)), TYPE(1.0f / 2.2f))");
			if(!filter.create(device, texture.getFormat(), size, flags)) return false;
		}
		
		// dispatch filter
		{
			Compute compute = device.createCompute();
			
			// horizontal pass
			if(!filter.dispatch(compute, SeparableFilter::ModeHorizontal, size, surface_0, texture)) return false;
			
			// vertical pass
			if(!filter.dispatch(compute, SeparableFilter::ModeVertical, size, surface_1, surface_0)) return false;
		}
		
		// flush surface
		device.flushTexture(surface_1);
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// draw surface
			command.setPipeline(pipeline);
			command.setSampler(0, sampler);
			command.setTexture(0, surface_1);
			command.drawArrays(3);
			
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

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <core/TellusimDirectory.h>
#include <platform/TellusimDevice.h>

#include "include/TellusimRmlUi.h"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::RmlUi", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create target
	Target target = device.createTarget(window);
	target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	// create rmlui
	RmlUi rmlui;
	if(!rmlui.init(window, device)) return 1;
	
	// load font
	Rml::LoadFontFace("data/sansb.ttf");
	
	// fonts needed for RmlUi demos
	if(Directory::isFile("data/LatoLatin-Regular.ttf")) {
		Rml::LoadFontFace("data/LatoLatin-Regular.ttf");
		Rml::LoadFontFace("data/LatoLatin-Italic.ttf");
		Rml::LoadFontFace("data/LatoLatin-Bold.ttf");
		Rml::LoadFontFace("data/LatoLatin-BoldItalic.ttf");
		Rml::LoadFontFace("data/NotoEmoji-Regular.ttf", true);
	}
	
	// load document
	String name = String("data/index.rml");
	if(app.isArgument("name")) name = app.getArgument("name");
	if(app.isArgument("path")) {
		String path = name.dirname();
		name = name.basename();
		uint32_t num = app.getArgument("path").tou32();
		for(uint32_t i = 0; i < num && path; i++) {
			if(path.back() == '/') path.removeBack();
			name = path.basename() + "/" + name;
			path = path.dirname();
		}
		if(path) Directory::changeDirectory(path);
	}
	Rml::ElementDocument *document = rmlui.getContext()->LoadDocument(name.get());
	if(document) document->Show();
	else return 1;
	
	// texture render
	Texture color_texture;
	Texture depth_texture;
	bool texture_render = (!app.isArgument("texture") || app.getArgument("texture").tou32() != 0);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// update RmlUi
		if(!rmlui.update()) return false;
		
		// render RmlUi
		if(texture_render) {
			if(!color_texture || color_texture.getWidth() != window.getWidth() || color_texture.getHeight() != window.getHeight()) {
				device.releaseTexture(color_texture);
				device.releaseTexture(depth_texture);
				color_texture = device.createTexture2D(FormatRGBAu8n, window.getWidth(), window.getHeight(), Texture::FlagTarget | Texture::FlagSource);
				depth_texture = device.createTexture2D(window.getDepthFormat(), window.getWidth(), window.getHeight(), Texture::FlagTarget);
			}
			if(!rmlui.render(color_texture, depth_texture)) return false;
		}
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// render RmlUi
			if(color_texture) rmlui.draw(target, command, color_texture);
			else rmlui.render(target, command);
		}
		target.end();
		
		if(!window.present()) return false;
		
		if(!device.check()) return false;
		
		return true;
	});
	
	// close document
	if(document) document->Close();
	
	// finish context
	window.finish();
	
	return 0;
}

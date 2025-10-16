// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <format/TellusimXml.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimCommand.h>
#include <interface/TellusimCanvas.h>

/*
 */
using namespace Tellusim;

/*
 */
TS_INLINE Matrix4x4f get_transform(const String &src) {
	float32_t m[16];
	if(src.scanf("matrix(%f,%f,%f,%f,%f,%f)", &m[0], &m[1], &m[2], &m[3], &m[4], &m[5]) == 6) {
		return Matrix4x4f(m, 6, false);
	}
	return Matrix4x4f::identity;
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	if(!window) return 1;
	
	// create window
	String title = String::format("%s Tellusim::SVG", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create canvas
	Canvas canvas;
	canvas.setViewport(window.getWidth(), window.getHeight());
	
	// SVG shapes
	Xml xml;
	uint32_t order = 0;
	Canvas svg_canvas(&canvas);
	if(!xml.load("tellusim.svg")) return 1;
	for(const Xml &child: xml.getChildren()) {
		if(child.getName() != "g") continue;
		if(!child.isChild("path")) continue;
		if(!child.isAttribute("style")) continue;
		
		// group path
		const Xml path = child.getChild("path");
		if(!path.isAttribute("d")) continue;
		
		// group style
		String style = child.getAttribute("style");
		if(style.contains("display:inline")) style = path.getAttribute("style");
		uint32_t pos = style.find("fill:");
		if(pos == Maxu32) continue;
		
		// create shape
		CanvasShape shape(svg_canvas);
		if(!shape.createSVG(path.getAttribute("d").get())) return 1;
		
		// shape transform
		shape.setTransform(get_transform(child.getAttribute("transform")));
		
		// shape color
		shape.setColor(Color(style.substring(pos + 5).get()));
		
		// shape order
		shape.setOrder(order++);
	}
	
	// create target
	Target target = device.createTarget(window);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// perspective transformation
		Matrix4x4f transform = Matrix4x4f::identity;
		transform *= Matrix4x4f::translate(canvas.getWidth() * 0.5f, canvas.getHeight() * 0.5f, 0.0f);
		transform *= Matrix4x4f::scale(Vector3f(1.0f, -1.0f, 1.0f) * canvas.getHeight() * 0.6f);
		transform *= Matrix4x4f::perspective(40.0f, 1.0f, 1.0f, 10000.0f);
		transform *= Matrix4x4f::lookAt(Vector3f(0.0f, 0.0f, 1000.0f), Vector3f::zero, Vector3f(0.0f, 1.0f, 0.0f));
		transform *= Matrix4x4f::rotateY(Tellusim::sin(time) * 16.0f);
		transform *= Matrix4x4f::rotateZ(Tellusim::cos(time) * 16.0f);
		transform *= Matrix4x4f::translate(-256.0f, -256.0f, 0.0f);
		svg_canvas.setTransform(transform);
		
		// create canvas
		if(!canvas.create(device, target)) return false;
		
		// window target
		target.setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
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

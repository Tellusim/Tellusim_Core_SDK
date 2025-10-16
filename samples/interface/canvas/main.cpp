// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <format/TellusimXml.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimCommand.h>
#include <interface/TellusimCanvas.h>

/*
 */
#define DATA_PATH	"data/"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	using Tellusim::sin;
	using Tellusim::cos;
	
	DECLARE_WINDOW
	if(!window) return 1;
	
	// create window
	String title = String::format("%s Tellusim::Canvas", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create canvas
	Canvas canvas;
	canvas.setViewport(window.getWidth(), window.getHeight());
	
	// create texture
	Texture texture = device.loadTexture(DATA_PATH "texture.png", Texture::FlagMipmaps);
	if(!texture) return 1;
	
	// canvas meshes
	uint32_t grid_width = 128;
	uint32_t grid_height = 64;
	float32_t dx = (float32_t)window.getWidth() / grid_width;
	float32_t dy = (float32_t)window.getHeight() / grid_height;
	for(uint32_t y = 0; y < grid_height; y++) {
		float32_t y0 = dy * y + dy * 0.25f;
		float32_t y1 = y0 + dy * 0.5f;
		for(uint32_t x = 0; x < grid_width; x++) {
			float32_t x0 = dx * x + dx * 0.25f;
			float32_t x1 = x0 + dx * 0.5f;
			CanvasMesh mesh(canvas);
			uint32_t i0 = mesh.addVertex(x0, y0, 0xff888888);
			uint32_t i1 = mesh.addVertex(x1, y0, 0xff888888);
			uint32_t i2 = mesh.addVertex(x1, y1, 0xff888888);
			uint32_t i3 = mesh.addVertex(x0, y1, 0xff888888);
			mesh.addIndices(i0, i1, i2);
			mesh.addIndices(i2, i3, i0);
		}
	}
	
	// canvas rectangles
	float32_t radiuses[] = {
		16.0f, 32.0f, 64.0f,
		16.0f, 32.0f, 48.0f,
	};
	CanvasElement::Mode modes[] = {
		CanvasElement::ModeTextureCubic,
		CanvasElement::ModeTextureCubic3x3,
		CanvasElement::ModeTextureCubic5x5,
	};
	Array<CanvasRect> rects;
	float32_t step = (float32_t)window.getWidth() / 4.0f;
	for(uint32_t i = 0; i < TS_COUNTOF(radiuses); i++) {
		float32_t x = step * (i % 3) + step;
		float32_t y = window.getHeight() - step * 0.5f;
		Vector2f size = Vector2f(step * 0.75f / (i / 3 + 1));
		CanvasRect rect(canvas, radiuses[i], size);
		rect.setStrokeColor(Color(0.75f, 0.75f, 0.75f, 1.0f));
		rect.setPosition(x, y);
		if(i < 3) {
			rect.setOrder(1);
			rect.setMipmap(1);
			rect.setMode(modes[i]);
			rect.setTexture(texture);
			rect.setColor(0.8f, 0.8f, 0.8f, 1.0f);
		} else {
			rect.setOrder(2);
			rect.setColor(Color::zero);
		}
		rects.append(rect);
	}
	
	// canvas meshes
	for(uint32_t i = 0; i < TS_COUNTOF(modes); i++) {
		float32_t x0 = step * i + step * 0.625f;
		float32_t y0 = step * 0.125f;
		float32_t x1 = x0 + step * 0.75f;
		float32_t y1 = y0 + step * 0.75f;
		CanvasMesh mesh(canvas);
		mesh.setOrder(1);
		mesh.setMipmap(1);
		mesh.setMode(modes[i]);
		mesh.setTexture(texture);
		mesh.addVertex(x0, y0, 0.0f, 0.0f, 1.0f);
		mesh.addVertex(x1, y0, 0.0f, 1.0f, 1.0f);
		mesh.addVertex(x1, y1, 0.0f, 1.0f, 0.0f);
		mesh.addVertex(x0, y1, 0.0f, 0.0f, 0.0f);
		mesh.addIndices(0, 1, 2);
		mesh.addIndices(2, 3, 0);
	}
	
	// canvas strip primitive
	CanvasStrip strip(canvas);
	strip.setColor(1.0f, 1.0f, 1.0f, 0.5f);
	strip.setStrokeStyle(StrokeStyle(4.0f, Color(0.0f, 0.0f, 0.0f, 0.5f)));
	strip.setWidth(24.0f);
	strip.setOrder(2);
	for(uint32_t j = 0; j <= 512; j++) {
		float32_t angle = j / 128.0f * Pi2;
		float32_t radius = j * 0.25f + 256.0f;
		strip.addPosition(sin(angle) * radius, cos(angle) * radius);
	}
	
	// canvas line primitive
	CanvasMesh mesh(canvas);
	mesh.setPrimitive(Pipeline::PrimitiveLine);
	mesh.setOrder(3);
	for(uint32_t j = 0; j < 32; j++) {
		float32_t offset = j / 64.0f;
		float32_t radius = j / 128.0f + 0.75f;
		for(uint32_t i = 0; i <= 7; i++) {
			float32_t angle = 2.0f * Pi2 * i / 7.0f + offset;
			uint32_t index = mesh.addVertex(sin(angle) * radius, cos(angle) * radius, 0xff000000u | (j << 2) | (j << 10) | (j << 18));
			if(i) mesh.addIndices(index - 1, index);
		}
	}
	
	// tiger shapes
	Xml tiger_xml;
	Canvas tiger_canvas;
	tiger_canvas.setParent(canvas);
	if(!tiger_xml.load(DATA_PATH "tiger.svg")) return 1;
	const Xml tiger_group_xml = tiger_xml.getChild("g");
	if(!tiger_group_xml) return 1;
	for(uint32_t i = 0; i < tiger_group_xml.getNumChildren(); i++) {
		const Xml xml = tiger_group_xml.getChild(i);
		if(xml.getName() == "g" && xml.isChild("path") && xml.isAttribute("fill")) {
			CanvasShape shape(tiger_canvas);
			if(!shape.createSVG(xml.getChild("path").getAttribute("d").get())) return 1;
			shape.setColor(Color(xml.getAttribute("fill").get()));
			if(xml.isAttribute("stroke")) {
				float32_t width = xml.getAttribute("stroke-width", 1.0f);
				float32_t offset = xml.getAttribute("stroke-width", 1.0f) * 0.5f;
				shape.setStrokeStyle(StrokeStyle(width, offset, Color(xml.getAttribute("stroke").get())));
			}
			shape.setOrder(i);
		}
	}
	tiger_canvas.setTransform(Matrix4x4f::translate(1000.0f, 600.0f, 0.0f) * Matrix4x4f::scale(0.8f, -0.8f, 1.0f));
	tiger_canvas.setOrder(1);
	
	// canvas ellipses
	Canvas ellipse_canvas;
	Array<CanvasEllipse> ellipses;
	ellipse_canvas.setParent(canvas);
	for(uint32_t i = 0; i < 16; i++) {
		CanvasEllipse ellipse(ellipse_canvas, 160.0f);
		ellipse.setStrokeStyle(StrokeStyle(4.0f, Color(0.75f, 0.75f, 0.75f, 1.0f)));
		ellipse.setColor(Color::zero);
		ellipses.append(ellipse);
		ellipse.setOrder(3);
	}
	ellipse_canvas.setOrder(2);
	
	// canvas triangle
	Canvas triangle_canvas;
	Array<CanvasTriangle> triangles;
	triangle_canvas.setParent(canvas);
	for(uint32_t i = 0; i < 8; i++) {
		CanvasTriangle triangle(triangle_canvas);
		triangle.setStrokeStyle(StrokeStyle(8.0f, Color(0.75f, 0.75f, 0.75f, 1.0f)));
		triangle.setColor(Color::zero);
		triangles.append(triangle);
	}
	triangle_canvas.setOrder(3);
	
	// canvas gradients
	CanvasEllipse gradient_0(canvas, 80.0f);
	CanvasEllipse gradient_1(canvas, 80.0f);
	CanvasRect gradient_2(canvas, 16.0f, Vector2f(128.0f));
	CanvasRect gradient_3(canvas, 16.0f, Vector2f(128.0f));
	gradient_0.setMode(CanvasElement::ModeGradient);
	gradient_1.setMode(CanvasElement::ModeGradient);
	gradient_2.setMode(CanvasElement::ModeGradient);
	gradient_3.setMode(CanvasElement::ModeGradient);
	gradient_0.setPosition(96.0f, 128.0f);
	gradient_1.setPosition(canvas.getWidth() - 96.0f, 128.0f);
	gradient_2.setPosition(96.0f, canvas.getHeight() - 128.0f);
	gradient_3.setPosition(canvas.getWidth() - 96.0f, canvas.getHeight() - 128.0f);
	gradient_0.setGradientStyle(GradientStyle(0.75f, Vector2f(0.5f)));
	gradient_1.setGradientStyle(GradientStyle(1.0f, Vector2f(0.0f), Vector2f(1.0f, 0.0f)));
	gradient_2.setGradientStyle(GradientStyle(0.75f, Vector2f(0.5f)));
	gradient_3.setGradientStyle(GradientStyle(1.0f, Vector2f(0.0f), Vector2f(1.0f, 0.0f)));
	
	// canvas text
	Canvas text_canvas;
	CanvasText text(text_canvas);
	text_canvas.setParent(canvas);
	text.setAlign(CanvasElement::AlignCenter);
	text.setFontName(DATA_PATH "sansb.ttf");
	text.setFontStyle(FontStyle(64, Color(0.9f, 0.1f, 0.1f, 1.0f)));
	text.getFontStyle().offset = Vector3f(4.0f, -4.0f, 0.0f);
	text.setText("Hello Canvas!!!");
	text_canvas.setOrder(4);
	
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
		
		// create canvas
		if(!canvas.create(device, target)) return false;
		
		// update elements
		Matrix4x4f center = Matrix4x4f::translate(canvas.getWidth() * 0.5f, canvas.getHeight() * 0.5f, 0.0f);
		mesh.setTransform(center * Matrix4x4f::rotateZ(time * 16.0f) * Matrix4x4f::scale(384.0f, 384.0f, 1.0f));
		strip.setTransform(center * Matrix4x4f::rotateZ(time * 32.0f) * Matrix4x4f::scale(1.0f, 1.0f, 1.0f));
		tiger_canvas.setTransform(center * Matrix4x4f::rotateZ(sin(time) * 16.0f) * Matrix4x4f::scale(0.8f, -0.8f, 1.0f) * Matrix4x4f::translate(-100.0f, -100.0f, 0.0f));
		ellipse_canvas.setTransform(center);
		text_canvas.setTransform(center);
		strip.setWidth(24.0f + sin(time) * 8.0f);
		for(uint32_t i = 0; i < ellipses.size(); i++) {
			CanvasEllipse &ellipse = ellipses[i];
			float32_t radius = 64.0f + sin(time * 2.0f + i) * 64.0f;
			ellipse.setPosition0(sin(time * 0.7f + i * 3.0f) * radius, cos(time * 1.3f) * radius, 0.0f);
			ellipse.setPosition1(cos(time * 0.7f + i * 4.0f) * radius, sin(time * 1.3f) * radius, 0.0f);
		}
		for(uint32_t i = 0; i < rects.size(); i++) {
			CanvasRect &rect = rects[i];
			rect.getStrokeStyle().width = 24.0f + sin(time + i * 3.0f) * 16.0f;
			rect.getStrokeStyle().offset = cos(time + i * 2.0f) * 8.0f;
		}
		for(uint32_t i = 0; i < triangles.size(); i++) {
			CanvasTriangle &triangle = triangles[i];
			float32_t width = (i < 4) ? 64.0f : -64.0f;
			float32_t x = (i < 4) ? 64.0f : canvas.getWidth() - 64.0f;
			triangle.setPosition0(x, canvas.getHeight() * 0.5f);
			triangle.setPosition1(x + width, canvas.getHeight() * 0.5f - 64.0f);
			triangle.setPosition2(x + width, canvas.getHeight() * 0.5f + 64.0f);
			triangle.setRadius((i & 3) * 12.0f + sin(time) * 16.0f);
		}
		gradient_0.getGradientStyle().center = Vector2f(0.5f + sin(time) * 0.25f, 0.5f + cos(time) * 0.25f);
		gradient_2.getGradientStyle().center = Vector2f(0.5f + sin(time) * 0.25f, 0.5f + cos(time) * 0.25f);
		gradient_1.getGradientStyle().center = Vector2f(0.5f - sin(time) * 0.5f, 0.5f - cos(time) * 0.5f);
		gradient_3.getGradientStyle().center = Vector2f(0.5f - sin(time) * 0.5f, 0.5f - cos(time) * 0.5f);
		gradient_1.getGradientStyle().axis = Vector2f(sin(time), cos(time));
		gradient_3.getGradientStyle().axis = Vector2f(sin(time), cos(time));
		
		// window target
		target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
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

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <TellusimApp.h>
#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <platform/TellusimWindow.h>
#include <platform/TellusimDevice.h>
#include <interface/TellusimCanvas.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	using Tellusim::sin;
	using Tellusim::cos;
	
	// create app
	App app(argc, argv);
	if(!app.create()) return 1;
	
	// create window
	Window window(app.getPlatform(), app.getDevice());
	if(!window || !window.setSize(app.getWidth(), app.getHeight())) return 1;
	if(!window.create("08 Hello Canvas") || !window.setHidden(false)) return 1;
	window.setKeyboardPressedCallback([&](uint32_t key, uint32_t code) {
		if(key == Window::KeyEsc) window.stop();
	});
	window.setCloseClickedCallback([&]() { window.stop(); });
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create canvas
	Canvas canvas;
	
	// set viewport size
	float32_t width = 1600.0f;
	float32_t height = 900.0f;
	canvas.setViewport(width, height);
	
	// elements order
	uint32_t order = 0;
	
	// create background rectangle
	CanvasRect background_rect(canvas);
	background_rect.setMode(CanvasElement::ModeGradient);
	background_rect.setSize(width, height);
	background_rect.setPosition(width * 0.5f, height * 0.5f);
	background_rect.setGradientStyle(GradientStyle(1.5f, Vector2f(0.5f, 1.0f), Color::gray, Color::black));
	background_rect.setOrder(order++);
	
	// grid offset
	float32_t offset = 32.0f;
	
	// create grid
	{
		float32_t step = 128.0f;
		for(float32_t x = offset + step; x + offset < width; x += step) {
			CanvasStrip x_strip(canvas);
			x_strip.addPosition(x, offset);
			x_strip.addPosition(x, height - offset);
			x_strip.setOrder(order++);
		}
		for(float32_t y = offset + step; y + offset < height; y += step) {
			CanvasStrip y_strip(canvas);
			y_strip.addPosition(offset, y);
			y_strip.addPosition(width - offset, y);
			y_strip.setOrder(order++);
		}
	}
	
	// create main axes
	{
		// create basis axes
		CanvasStrip x_strip(canvas);
		x_strip.addPosition(offset, offset);
		x_strip.addPosition(width - offset * 1.5f, offset);
		x_strip.setColor(Color::red);
		x_strip.setWidth(3.0f);
		x_strip.setOrder(order++);
		
		CanvasStrip y_strip(canvas);
		y_strip.addPosition(offset, offset);
		y_strip.addPosition(offset, height - offset * 1.5f);
		y_strip.setColor(Color::green);
		y_strip.setWidth(3.0f);
		y_strip.setOrder(order++);
		
		// create basis arrows
		CanvasTriangle x_triangle(canvas);
		x_triangle.setPosition0(width - offset, offset);
		x_triangle.setPosition1(x_triangle.getPosition0() - Vector3f(offset,  offset * 0.25f, 0.0f));
		x_triangle.setPosition2(x_triangle.getPosition0() - Vector3f(offset, -offset * 0.25f, 0.0f));
		x_triangle.setColor(Color::red);
		x_triangle.setOrder(order++);
		
		CanvasTriangle y_triangle(canvas);
		y_triangle.setPosition0(offset, height - offset);
		y_triangle.setPosition1(y_triangle.getPosition0() - Vector3f( offset * 0.25f, offset, 0.0f));
		y_triangle.setPosition2(y_triangle.getPosition0() - Vector3f(-offset * 0.25f, offset, 0.0f));
		y_triangle.setColor(Color::green);
		y_triangle.setOrder(order++);
	}
	
	// create transform rect
	CanvasRect transform_rect(canvas);
	transform_rect.setTransform(Matrix4x4f::translate(offset, offset, 0.0f), CanvasElement::StackSet);
	transform_rect.setOrder(order++);
	
	// create rectangle
	// gradient is texture based
	CanvasRect element_rect(canvas, 32.0f);
	element_rect.setMode(CanvasElement::ModeGradient);
	element_rect.setStrokeStyle(StrokeStyle(8.0f, -8.0f, Color::black));
	element_rect.setGradientStyle(GradientStyle(1.5f, Vector2f(0.0f, 1.0f), Color::blue, Color::magenta));
	element_rect.setOrder(order++);
	
	// create triangle
	// gradient is position based
	CanvasTriangle element_triangle(canvas, 32.0f);
	element_triangle.setMode(CanvasElement::ModeGradient);
	element_triangle.setStrokeStyle(StrokeStyle(8.0f, -8.0f, Color::black));
	element_triangle.setGradientStyle(GradientStyle(128.0f, Vector2f(0.0f, 0.0f), Color::green, Color::yellow));
	element_triangle.setOrder(order++);
	
	// create ellipse
	// gradient is texture based
	CanvasEllipse element_ellipse(canvas);
	element_ellipse.setMode(CanvasElement::ModeGradient);
	element_ellipse.setStrokeStyle(StrokeStyle(8.0f, Color::black));
	element_ellipse.setGradientStyle(GradientStyle(1.0f, Vector2f(0.0f, 0.0f), Color::red, Color::yellow));
	element_ellipse.setRadius(128.0f);
	element_ellipse.setOrder(order++);
	
	// create quadratic shape
	// gradient is texture based
	CanvasShape quadratic_shape(canvas);
	quadratic_shape.setMode(CanvasElement::ModeGradient);
	quadratic_shape.setStrokeStyle(StrokeStyle(8.0f, 8.0f, Color::black));
	quadratic_shape.setGradientStyle(GradientStyle(1.0f, Vector2f(0.0f, 0.0f), Color::blue, Color::cyan));
	quadratic_shape.setTexCoord(-128.0f, 128.0f, -128.0f, 128.0f);
	{
		Vector3f old_position;
		float32_t radius = 96.0f;
		for(uint32_t i = 0; i < 7; i++) {
			float32_t angle = Pi2 * i / 6.0f;
			Vector3f position = Vector3f(sin(angle) * radius, cos(angle) * radius, 0.0f);
			if(i) {
				quadratic_shape.addPosition(old_position);
				quadratic_shape.addPosition(old_position + position);
				quadratic_shape.addPosition(position);
			}
			old_position = position;
		}
	}
	quadratic_shape.setOrder(order++);
	
	// create cubic shape
	// gradient is texture based
	CanvasShape cubic_shape(canvas, true);
	cubic_shape.setMode(CanvasElement::ModeGradient);
	cubic_shape.setStrokeStyle(StrokeStyle(8.0f, Color::black));
	cubic_shape.setGradientStyle(GradientStyle(1.0f, Vector2f(0.0f, 0.0f), Color::red, Color::magenta));
	{
		// outer shape
		float32_t radius = 128.0f;
		cubic_shape.addPosition(   0.0f, -radius);
		cubic_shape.addPosition( radius, -radius);
		cubic_shape.addPosition( radius,  radius);
		cubic_shape.addPosition(   0.0f,  radius);
		cubic_shape.addPosition(   0.0f,  radius);
		cubic_shape.addPosition(-radius,  radius);
		cubic_shape.addPosition(-radius, -radius);
		cubic_shape.addPosition(   0.0f, -radius);
		
		// shape connection
		cubic_shape.addPosition(0.0f, -radius);
		cubic_shape.addPosition(0.0f, -radius);
		cubic_shape.addPosition(0.0f, -radius);
		cubic_shape.addPosition(0.0f, -radius);
		
		// inner shape
		radius *= 0.5f;
		cubic_shape.addPosition(   0.0f,  radius);
		cubic_shape.addPosition( radius,  radius);
		cubic_shape.addPosition( radius, -radius);
		cubic_shape.addPosition(   0.0f, -radius);
		cubic_shape.addPosition(   0.0f, -radius);
		cubic_shape.addPosition(-radius, -radius);
		cubic_shape.addPosition(-radius,  radius);
		cubic_shape.addPosition(   0.0f,  radius);
	}
	cubic_shape.setTexCoord(-128.0f, 128.0f, -128.0f, 128.0f);
	cubic_shape.setOrder(order++);
	
	// create strip shape
	CanvasStrip element_strip(canvas);
	element_strip.setStrokeStyle(StrokeStyle(4.0f, Color::black));
	element_strip.setWidth(24.0f);
	element_strip.setOrder(2);
	for(uint32_t j = 0; j <= 256; j++) {
		float32_t angle = j / 64.0f * Pi2;
		float32_t radius = j * 0.5f + 12.0f;
		element_strip.addPosition(sin(angle) * radius, cos(angle) * radius);
	}
	element_strip.setOrder(order++);
	
	// create text
	CanvasText element_text(canvas);
	element_text.setFontName("font.ttf");
	element_text.getFontStyle().offset = Vector3f(6.0f, -6.0f, 0.0f);
	element_text.setFontSize(48);
	element_text.setOrder(order++);
	
	// create font batches
	const FontBatch font_batches[] = {
		FontBatch(Vector3f(256.0f, 64.0f, 0.0f), "Rect"),
		FontBatch(Vector3f(768.0f, 64.0f, 0.0f), "Triangle"),
		FontBatch(Vector3f(1280.0f, 64.0f, 0.0f), "Ellipse"),
		FontBatch(Vector3f(256.0f, 448.0f, 0.0f), "Quadratic"),
		FontBatch(Vector3f(768.0f, 448.0f, 0.0f), "Cubic"),
		FontBatch(Vector3f(1280.0f, 448.0f, 0.0f), "Strip"),
	};
	element_text.setBatches(font_batches, TS_COUNTOF(font_batches));
	
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
		
		// animate rectangle
		element_rect.setTransform(Matrix4x4f::translate(256.0f, 256.0f, 0.0f) * Matrix4x4f::rotateZ(time * 64.0f));
		element_rect.setSize(192.0f + sin(time) * 64.0f, 192.0f + cos(time) * 64.0f);
		
		// animate triangle
		element_triangle.setTransform(Matrix4x4f::translate(768.0f, 256.0f, 0.0f));
		element_triangle.setPosition0(sin(time) * 32.0f, -cos(time) * 32.0f);
		element_triangle.setPosition1(sin(time * 2.0f) * 128.0f, cos(time * 2.0f) * 128.0f);
		element_triangle.setPosition2(sin(-time * 3.0f) * 128.0f, cos(-time * 3.0f) * 128.0f);
		
		// animate ellipse
		element_ellipse.setTransform(Matrix4x4f::translate(1280.0f, 256.0f, 0.0f));
		element_ellipse.setPosition0(sin(-time) * sin(time * 2.0f) * 96.0f, cos(time) * sin(-time * 2.0f) * 96.0f);
		element_ellipse.setPosition1(sin(time) * sin(time * 2.0f) * 128.0f, cos(time) * sin(time * 2.0f) * 128.0f);
		
		// animate quadratic shape
		quadratic_shape.setTransform(Matrix4x4f::translate(256.0f, 640.0f, 0.0f) * Matrix4x4f::rotateZ(-time * 64.0f));
		
		// animate cubic shape
		cubic_shape.setTransform(Matrix4x4f::translate(768.0f, 640.0f, 0.0f) * Matrix4x4f::rotateZ(time * 64.0f));
		
		// animate strip
		element_strip.setTransform(Matrix4x4f::translate(1280.0f, 640.0f, 0.0f) * Matrix4x4f::rotateZ(-time * 64.0f));
		
		// create canvas resource for target
		if(!canvas.create(device, target, 100)) return false;
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// draw canvas
			canvas.draw(command, target);
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

/*
 */
#if _ANDROID
	#include <system/TellusimAndroid.h>
	TS_DECLARE_ANDROID_NATIVE_ACTIVITY
#endif

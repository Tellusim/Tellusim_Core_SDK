// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <core/TellusimPointer.h>
#include <interface/TellusimControls.h>
#include <platform/TellusimDevice.h>

/*
 */
using namespace Tellusim;

/*
 */
class CustomControl : public ControlBase {
		
	public:
		
		explicit CustomControl(Control *parent) : ControlBase(parent) {
			create();
		}
		
		void setAngle(float32_t a) {
			angle = a;
		}
		void setRadius(float32_t r) {
			radius = r;
		}
		
	private:
		
		// create control
		void create() {
			Canvas canvas = getCanvas();
			canvas_rect = CanvasRect(canvas);
			canvas_rect.setColor(Color::black);
			ControlBase::create();
		}
		
		// update control
		virtual void update_enabled(bool enabled) {
			enabled &= isEnabled();
			canvas_rect.setEnabled(enabled);
			ControlBase::update_enabled(enabled);
		}
		virtual void update_rectangle(ControlRoot &root, int32_t &order, uint32_t scale) {
			canvas_rect.setOrder(order++);
			Rect rect(0.0f);
			rect.right = getWidth() + radius * 2.0f;
			rect.top = getHeight() + radius * 2.0f;
			rect += getMargin();
			set_rect(rect);
		}
		virtual bool update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale) {
			update_expand(root, region);
			Rect rect = getRect() - getMargin();
			Vector3f position = get_position(region, scale);
			canvas_rect.setRadius(radius);
			canvas_rect.setSize(rect.getWidth(), rect.getHeight());
			canvas_rect.setStrokeStyle(StrokeStyle(radius * 0.5f, Color::white));
			canvas_rect.setTransform(Matrix4x4f::translate(rect.getCenterX() + position.x, rect.getCenterY() + position.y, position.z) * Matrix4x4f::rotateZ(angle));
			return false;
		}
		
		float32_t angle = 0.0f;
		float32_t radius = 64.0f;
		
		CanvasRect canvas_rect;
};

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	if(!window) return 1;
	
	// create window
	String title = String::format("%s Tellusim::CustomControl", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create canvas
	Canvas canvas;
	
	// create root control
	ControlRoot root(canvas, true);
	root.setFontSize(18);
	
	// create custom control
	CustomControl custom_control(&root);
	custom_control.setSize(128.0f, 128.0f);
	custom_control.setAlign(Control::AlignCenter);
	
	// create window
	ControlDialog dialog(&root, 1, 0.0f, 8.0f);
	dialog.setAlign(Control::AlignRightTop);
	dialog.setSize(192.0f, 0.0f);
	dialog.setMargin(16.0f);
	
	// create sliders
	ControlSlider size_x_slider(&dialog, "SizeX", 2, 0.25f);
	ControlSlider size_y_slider(&dialog, "SizeY", 2, 0.25f);
	ControlSlider radius_slider(&dialog, "Radius", 2, 0.25f);
	ControlSlider angle_slider(&dialog, "Angle", 2, 0.0f);
	size_x_slider.setAlign(Control::AlignExpandX);
	size_y_slider.setAlign(Control::AlignExpandX);
	radius_slider.setAlign(Control::AlignExpandX);
	angle_slider.setAlign(Control::AlignExpandX);
	
	ControlCheck enabled_slider(&dialog, "Enabled", true);
	enabled_slider.setClickedCallback([&](ControlCheck check) { custom_control.setEnabled(check.isChecked()); });
	
	// create target
	Target target = device.createTarget(window);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// update element
		custom_control.setSize(size_x_slider.getValuef32() * 512.0f, size_y_slider.getValuef32() * 512.0f);
		custom_control.setRadius(radius_slider.getValuef32() * 256.0f + 16.0f);
		custom_control.setAngle(angle_slider.getValuef32() * 360.0f);
		
		// update controls
		update_controls(window, root);
		
		// create canvas
		canvas.create(device, target);
		
		// window target
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

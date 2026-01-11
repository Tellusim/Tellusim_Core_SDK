// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <math.h>
#include <stdio.h>

#include "include/TellusimCAPI.h"

/*
 */
typedef struct Self {
	TSWindow window;
	TSDevice device;
	TSCanvas canvas;
	TSTarget target;
	TSControlRoot root;
	TSControlRect rect;
	TSTexture texture;
	TSColor color;
} Self;

/*
 */
static void close_clicked_func(void *ptr) {
	tsWindow_stop((TSWindow)ptr);
}

static void keyboard_pressed_func(uint32_t key, uint32_t code, void *ptr) {
	TSWindow window = (TSWindow)ptr;
	if(key == TS_WindowKeyEsc) tsWindow_stop(window);
	if(key == TS_WindowKeyF12) {
		TSImage image = tsImage_new();
		if(tsWindow_grab(window, image) && tsImage_save_csIFu(image, "screenshot.png", TS_ImageFlagNone, 85)) {
			TS_CLOG(Message, "Screenshot\n");
		}
		tsImage_delete(image);
	}
	(void)code;
}

static void dialog_updated_func(TSControlDialog dialog, void *data) {
	TSControl control = tsControlDialog_baseControlPtr(dialog);
	float32_t x = tsControl_getPositionX(control);
	float32_t y = tsControl_getPositionY(control);
	float32_t width = tsControl_getWidth(control);
	float32_t height = tsControl_getHeight(control);
	TS_CLOGF(Message, "Dialog updated %.0f %.0f %.0fx%.0f\n", x, y, width, height);
	tsControl_delete(control);
	(void)data;
}

static void button_clicked_func(TSControlButton button, void *data) {
	TSString text = tsControlText_getText((TSControlText)button);
	TS_CLOGF(Message, "%s clicked\n", tsString_get(text));
	tsString_delete(text);
	(void)data;
}

static void slider_changed_func(TSControlSlider slider, void *data) {
	*((float32_t*)data) = tsControlSlider_getValuef32(slider, false);
}

/*
 */
static TSImage create_image(uint32_t size, uint32_t frame) {
	
	// create image
	TSImage image = tsImage_new();
	tsImage_create2D_FuIF(image, TS_FormatRGBAu8n, size, TS_ImageFlagNone);
	
	// create sampler
	TSImageSampler sampler = tsImageSampler_new_IcS(image, 0);
	
	// fill image
	for(uint32_t y = 0; y < size; y++) {
		for(uint32_t x = 0; x < size; x++) {
			TSImageColor color = tsImageColor_new_u2((x - (frame ^ y)) ^ (y + (frame ^ x)), 255);
			tsImageSampler_set2D(sampler, x, y, &color);
		}
	}
	
	// release sampler
	tsImageSampler_delete(sampler);
	
	return image;
}

/*
 */
static bool_t main_func(void *ptr) {
	
	// update window
	tsWindow_update(false);
	
	// self resources
	Self *self = (Self*)ptr;
	TSWindow window = self->window;
	TSDevice device = self->device;
	TSCanvas canvas = self->canvas;
	TSTarget target = self->target;
	TSControlRoot root = self->root;
	TSControlRect rect = self->rect;
	TSTexture texture = self->texture;
	
	// render window
	if(!tsWindow_render(window)) return false;
	
	// window size
	float32_t height = 900.0f;
	float32_t width = floorf(height * (float32_t)tsWindow_getWidth(window) / (float32_t)tsWindow_getHeight(window));
	float32_t mouse_x = width * (float32_t)tsWindow_getMouseX(window) / (float32_t)tsWindow_getWidth(window);
	float32_t mouse_y = height * (float32_t)tsWindow_getMouseY(window) / (float32_t)tsWindow_getHeight(window);
	
	// mouse button
	TS_ControlButton buttons = TS_ControlButtonNone;
	if(tsWindow_getMouseButtons(window) & TS_WindowButtonLeft) buttons |= TS_ControlButtonLeft;
	if(tsWindow_getMouseButtons(window) & TS_WindowButtonLeft2) buttons |= TS_ControlButtonLeft;
	
	// update texture
	static uint32_t texture_frame = 0;
	static float64_t texture_time = 0.0;
	if(tsTime_seconds() - texture_time > 1.0 / 30.0) {
		TSImage image = create_image(tsTexture_getWidth_c(texture), texture_frame);
		tsDevice_setTexture_cTcI(device, texture, image);
		tsDevice_flushTexture_cTTF(device, texture, TS_TextureDefaultFlags);
		tsImage_delete(image);
		texture_time = tsTime_seconds();
		texture_frame++;
	}
	
	// update rect
	float32_t time = (float32_t)tsTime_seconds();
	tsControlRect_setColor_cC(rect, &self->color);
	float32_t aspect = width / height;
	float32_t dx = sinf(time * 0.4f) * 0.2f;
	float32_t dy = cosf(time * 0.5f) * 0.2f / aspect;
	tsControlRect_setTexCoord_ffff(rect, -aspect - dx, aspect + dx, -1.0f - dy, 1.0f + dy);
	
	// update controls
	tsControlRoot_setViewport_ff(root, width, height);
	tsControlRoot_setMouse_ffCB(root, mouse_x, mouse_y, buttons);
	while(tsControlRoot_update(root, tsCanvas_getScale(canvas, target, 100), 0)) { }
	
	// create canvas
	tsCanvas_create_cDcTu(canvas, device, target, 100);
	
	// window target
	tsTarget_begin(target);
	{
		// create command list
		TSCommand command = tsDevice_createCommand_cT(device, target);
		
		// draw canvas
		tsCanvas_draw_CcT(canvas, command, target);
		
		// release command list
		tsCommand_delete(command);
	}
	tsTarget_end(target);
	
	// present window
	if(!tsWindow_present(window)) return false;
	
	// check device
	if(!tsDevice_check(device)) return false;
	
	return true;
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create app
	TSApp app = tsApp_new(argc, argv);
	if(!tsApp_create(app, TS_PlatformUnknown, TS_AppVersion)) return 1;
	
	// create window
	TSWindow window = tsWindow_new_Pu(tsApp_getPlatform(app), tsApp_getDevice(app));
	if(!window) return 1;
	
	tsWindow_setSize(window, tsApp_getWidth(app), tsApp_getHeight(app), 0);
	tsWindow_setCloseClickedCallback(window, close_clicked_func, window);
	tsWindow_setKeyboardPressedCallback(window, keyboard_pressed_func, window);
	
	TSString title = tsString_format("%s Tellusim::CAPI", tsWindow_getPlatformName(window));
	if(!tsWindow_create_cSWF(window, title, TS_WindowDefaultFlags | TS_WindowFlagVerticalSync) || !tsWindow_setHidden(window, 0)) return 1;
	
	// build info
	TS_CLOGF(Message, "Build: %s\n", tsString_get_c(tsApp_getBuildInfo()));
	
	// create device
	TSDevice device = tsDevice_new_W(window);
	if(!device) return 1;
	
	// create target
	TSTarget target = tsDevice_createTarget_cW(device, window);
	if(!target) return 1;
	
	// create canvas
	TSCanvas canvas = tsCanvas_new();
	
	// create root control
	TSControlRoot root = tsControlRoot_new_Cb(canvas, true);
	tsControlRoot_setFontSize(root, 24, false);
	
	// create texture
	TSImage image = create_image(256, 0);
	TSTexture texture = tsDevice_createTexture_ccITFA(device, image, TS_TextureDefaultFlags, 0);
	tsImage_delete(image);
	if(!texture) return 1;
	
	// create rect
	TSControlRect rect = tsControlRect_new_CCEM((TSControl*)&root, TS_CanvasElementModeTexture);
	tsControl_setAlign((TSControl)rect, TS_ControlAlignExpand);
	tsControlRect_setWrapMode(rect, TS_SamplerWrapModeRepeat);
	tsControlRect_setTexture(rect, texture, false);
	tsControlRect_setFullscreen(rect, true);
	
	// create dialog
	TSControlDialog dialog = tsControlDialog_new_Cuff((TSControl*)&root, 1, 0.0f, 8.0f);
	tsControlDialog_setUpdatedCallback(dialog, dialog_updated_func, 0);
	tsControl_setAlign((TSControl)dialog, TS_ControlAlignCenter);
	tsControl_setSize_ff((TSControl)dialog, 240.0f, 180.0f);
	
	// create text
	TSControlText text = tsControlText_new_CcS((TSControl*)&dialog, title);
	tsControl_setAlign((TSControl)text, TS_ControlAlignCenterX);
	
	// create button
	TSControlButton button = tsControlButton_new_Cs((TSControl*)&dialog, "Button");
	tsControlButton_setClickedCallback(button, button_clicked_func, 0);
	tsControl_setAlign((TSControl)button, TS_ControlAlignExpand);
	tsControl_setMargin_ffff((TSControl)button, 0.0f, 0.0f, 0.0f, 16.0f);
	
	// self resources
	Self self;
	self.window = window;
	self.device = device;
	self.canvas = canvas;
	self.target = target;
	self.root = root;
	self.rect = rect;
	self.texture = texture;
	self.color = tsColor_new2(0.75f, 1.0f);
	
	// create sliders
	TSControlSlider slider_r = tsControlSlider_new_Csuf64f64f64((TSControl*)&dialog, "R", 2, self.color.r, 0.0, 1.0);
	TSControlSlider slider_g = tsControlSlider_new_Csuf64f64f64((TSControl*)&dialog, "G", 2, self.color.g, 0.0, 1.0);
	TSControlSlider slider_b = tsControlSlider_new_Csuf64f64f64((TSControl*)&dialog, "B", 2, self.color.b, 0.0, 1.0);
	tsControlSlider_setChangedCallback(slider_r, slider_changed_func, &self.color.r);
	tsControlSlider_setChangedCallback(slider_g, slider_changed_func, &self.color.g);
	tsControlSlider_setChangedCallback(slider_b, slider_changed_func, &self.color.b);
	tsControl_setAlign((TSControl)slider_r, TS_ControlAlignExpandX);
	tsControl_setAlign((TSControl)slider_g, TS_ControlAlignExpandX);
	tsControl_setAlign((TSControl)slider_b, TS_ControlAlignExpandX);
	
	// main loop
	tsWindow_run(window, main_func, &self);
	
	// finish context
	tsWindow_finish(window);
	
	// release resources
	tsControlSlider_delete(slider_r);
	tsControlSlider_delete(slider_g);
	tsControlSlider_delete(slider_b);
	tsControlButton_delete(button);
	tsControlText_delete(text);
	tsControlDialog_delete(dialog);
	tsControlRect_delete(rect);
	tsControlRoot_delete(root);
	tsTexture_delete(texture);
	tsCanvas_delete(canvas);
	tsTarget_delete(target);
	tsDevice_delete(device);
	tsWindow_delete(window);
	tsApp_delete(app);
	
	// done
	TS_CLOG(Message, "Done\n");
	
	return 0;
}

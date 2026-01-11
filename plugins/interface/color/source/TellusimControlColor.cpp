// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimBlob.h>
#include <platform/TellusimDevice.h>

#include <system/config/include/TellusimConfig.h>

#include "../include/TellusimControlColor.h"

/*
 */
#define COLOR_CONFIG	"color/"

/*
 */
namespace Tellusim {
	
	/*
	 */
	ControlColor::ControlColor(Control *parent, const Device &device, Config &config, const Color &color) : ControlBase(parent), device(device), config(config) {
	
		// control align
		setAlign(AlignOverlap);
		
		// create control
		create();
		
		// set color
		setColor(color);
	}
	
	ControlColor::~ControlColor() {
		
	}
	
	/*
	 */
	void ControlColor::create() {
		
		// parent control
		Control parent = getParent();
		
		// main grid
		ControlGrid main_grid(&parent, 1, 4.0f, 4.0f);
		main_grid.setAlign(AlignExpand);
		
		// color rect
		color_rect = ControlRect(&main_grid, CanvasElement::ModeSolid);
		color_rect.setAlign(AlignBottom | AlignCenterX | AlignExpand | AlignAspect);
		color_rect.setSize(256.0f, 256.0f);
		color_rect.setInsideCallback([](ControlRect rect, float32_t x, float32_t y) {
			Vector2f center = rect.getRect().getCenter();
			center = Vector2f(center.x, min(center.x, center.y));
			return (length(Vector2f(x, y) - center) <= center.y);
		});
		color_rect.setPressedCallback([this](ControlRect rect, float32_t x, float32_t y) {
			Vector2f center = rect.getRect().getCenter();
			center = Vector2f(center.x, min(center.x, center.y));
			Vector2f color = (Vector2f(x, y) - center) / center.y;
			set_color(Vector4f(fract(atan2(color.y, -color.x) / Pi2), length(color), hsv_color.z, hsv_color.w));
		});
		
		// value rect
		value_rect = ControlRect(&main_grid, CanvasElement::ModeSolid);
		value_rect.setSize(256.0f, 20.0f);
		value_rect.setAlign(AlignExpandX);
		value_rect.setPressedCallback([this](ControlRect rect, float32_t x, float32_t y) {
			Vector2f size = rect.getRect().getSize();
			set_color(Vector4f(hsv_color.x, hsv_color.y, x / size.x, hsv_color.w));
		});
		
		// mode grid
		ControlGrid mode_grid(&main_grid, 2, 4.0f, 0.0f);
		mode_grid.setAlign(AlignExpandX);
		
		// control edit
		color_edit = ControlEdit(&mode_grid);
		color_edit.setAlign(AlignExpand);
		color_edit.setReturnedCallback([this](ControlEdit edit) {
			String color = edit.getText();
			if(!color.begins("#")) color = "#" + color;
			setColor(Color::html(color.get()));
		});
		
		// mode combo
		mode_combo = ControlCombo(&mode_grid, { "RGBu8", "RGB", "HSV" });
		mode_combo.setAlign(AlignCenterY);
		mode_combo.setChangedCallback([this](ControlCombo combo) {
			config.set(COLOR_CONFIG "mode", combo.getCurrentText());
			mode_changed();
		});
		mode_combo.setCurrentText(config.gets(COLOR_CONFIG "mode"));
		
		// sliders
		#define TS_DECLARE_SLIDER(NAME) { \
			NAME ## _slider = ControlSlider(&main_grid, "", 2); \
			NAME ## _slider.setAlign(AlignExpandX); \
			NAME ## _slider.setFormatCallback([](ControlSlider slider) { \
				return String::fromf32(slider.getValuef32(), slider.getDigits()); \
			}); \
			ControlEdit edit = ControlEdit(&main_grid); \
			edit.setAlign(AlignExpandX); \
			edit.setEnabled(false); \
			edit.setFrame(false); \
			NAME ## _slider.setChangedCallback(makeFunction([this](ControlSlider slider) { \
				slider_changed(slider); \
			})); \
			NAME ## _slider.setClickedRightCallback(makeFunction([](ControlSlider slider, ControlEdit edit) { \
				edit.setEnabled(true); \
				slider.setEnabled(false); \
				edit.setSize(0.0f, slider.getRect().getHeight()); \
				edit.setText(String::fromf32(slider.getValuef32(), slider.getDigits(), true)); \
				edit.setSelection(true, true); \
			}, ControlSlider::null, edit)); \
			edit.setReturnedCallback(makeFunction([](ControlEdit edit, ControlSlider slider) { \
				edit.setEnabled(false); \
				slider.setEnabled(true); \
				if(edit.getText()) slider.setValue(edit.getText().tof32(), true); \
			}, ControlEdit::null, NAME ## _slider)); \
		}
		TS_DECLARE_SLIDER(r_h)
		TS_DECLARE_SLIDER(g_s)
		TS_DECLARE_SLIDER(b_v)
		TS_DECLARE_SLIDER(alpha)
		#undef TS_DECLARE_SLIDER
		alpha_slider.setText("Alpha");
		
		// palette grid
		ControlGrid palette_grid(&main_grid, 2, 4.0f, 4.0f);
		palette_grid.setMargin(0.0f, 0.0f, 0.0f, 4.0f);
		palette_grid.setAlign(AlignLeft);
		
		// palette color
		palette_rect = ControlRect(&palette_grid);
		palette_rect.setSize(36.0f, 36.0f);
		palette_rect.setAlign(AlignCenter);
		palette_rect.setReleasedCallback([this](ControlRect rect, float32_t x, float32_t y) {
			dropped_position = rect.getOffset().xy + Vector2f(x, y);
			dragged_rect = rect;
		});
		
		// palette colors
		ControlGrid grid(&palette_grid, NumColors / 2, 4.0f, 4.0f);
		grid.setAlign(AlignCenter);
		for(uint32_t i = 0; i < NumColors; i++) {
			palette_rects[i] = ControlRect(&grid);
			palette_rects[i].setSize(16.0f, 16.0f);
			palette_rects[i].setReleasedCallback([this](ControlRect rect, float32_t x, float32_t y) {
				dropped_position = rect.getOffset().xy + Vector2f(x, y);
				dragged_rect = rect;
			});
			palette_rects[i].setClickedCallback([this](ControlRect rect) {
				if(rect.getColor() == Color::zero) return;
				setColor(rect.getColor());
			});
			palette_rects[i].setClicked2Callback([this](ControlRect rect) {
				if(rect.getColor() == Color::zero) return;
				rect.setColor(Color::zero);
				save_palette();
			});
			palette_rects[i].setColor(config.getColor(String::format("%scolor_%u", COLOR_CONFIG, i).get(), Color::zero));
		}
		
		// update controls
		mode_changed();
		
		ControlBase::create();
	}
	
	/*
	 */
	bool ControlColor::create_pipelines() {
		
		// control canvas
		Canvas canvas = getCanvas();
		if(canvas.getColorFormat() == FormatUnknown) return false;
		
		// color shader source
		#include "TellusimControlColor.blob"
		String src = Blob(TellusimControlColor_blob_src).gets();
		
		// create pipeline
		Pipeline pipeline = device.createPipeline();
		pipeline.setUniformMasks(0, 2, Shader::MaskVertex);
		pipeline.setScissorTest(true);
		pipeline.setDepthMask(Pipeline::DepthMaskNone);
		pipeline.setDepthFunc(Pipeline::DepthFuncAlways);
		pipeline.setColorFormat(canvas.getColorFormat());
		pipeline.setDepthFormat(canvas.getDepthFormat());
		pipeline.setMultisample(canvas.getMultisample());
		pipeline.setBlend(Pipeline::BlendOpAdd, Pipeline::BlendFuncSrcAlpha, Pipeline::BlendFuncInvSrcAlpha);
		pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, offsetof(CanvasVertex, position), sizeof(CanvasVertex));
		pipeline.addAttribute(Pipeline::AttributeTexCoord, FormatRGf32, 0, offsetof(CanvasVertex, texcoord), sizeof(CanvasVertex));
		pipeline.addAttribute(Pipeline::AttributeColor, FormatRGBAu8n, 0, offsetof(CanvasVertex, color), sizeof(CanvasVertex));
		
		// create color pipeline
		color_pipeline = device.createPipeline(pipeline);
		color_pipeline.setUniformMask(2, Shader::MaskFragment);
		if(!color_pipeline.createShaderGLSL(Shader::TypeVertex, src.get(), "VERTEX_SHADER=1")) return false;
		if(!color_pipeline.createShaderGLSL(Shader::TypeFragment, src.get(), "COLOR_SHADER=1")) return false;
		if(!color_pipeline.create()) {
			TS_LOG(Error, "ControlColor::create_pipelines(): can't create color pipeline\n");
			return false;
		}
		
		// create value pipeline
		value_pipeline = device.createPipeline(pipeline);
		value_pipeline.setUniformMask(2, Shader::MaskFragment);
		if(!value_pipeline.createShaderGLSL(Shader::TypeVertex, src.get(), "VERTEX_SHADER=1")) return false;
		if(!value_pipeline.createShaderGLSL(Shader::TypeFragment, src.get(), "VALUE_SHADER=1")) return false;
		if(!value_pipeline.create()) {
			TS_LOG(Error, "ControlColor::create_pipelines(): can't create value pipeline\n");
			return false;
		}
		
		// create palette pipeline
		palette_pipeline = device.createPipeline(pipeline);
		if(!palette_pipeline.createShaderGLSL(Shader::TypeVertex, src.get(), "VERTEX_SHADER=1")) return false;
		if(!palette_pipeline.createShaderGLSL(Shader::TypeFragment, src.get(), "PALETTE_SHADER=1")) return false;
		if(!palette_pipeline.create()) {
			TS_LOG(Error, "ControlColor::create_pipelines(): can't create palette pipeline\n");
			return false;
		}
		
		return true;
	}
	
	/*
	 */
	void ControlColor::mode_changed() {
		uint32_t mode = mode_combo.getCurrentIndex();
		if(mode == ModeRGBu8) {
			r_h_slider.setText("Red");
			g_s_slider.setText("Green");
			b_v_slider.setText("Blue");
			r_h_slider.setRange(0.0f, 255.0f);
			g_s_slider.setRange(0.0f, 255.0f);
			b_v_slider.setRange(0.0f, 255.0f);
			alpha_slider.setRange(0.0f, 255.0f);
			r_h_slider.setDigits(0);
			g_s_slider.setDigits(0);
			b_v_slider.setDigits(0);
			alpha_slider.setDigits(0);
		} else if(mode == ModeRGB) {
			r_h_slider.setText("Red");
			g_s_slider.setText("Green");
			b_v_slider.setText("Blue");
			r_h_slider.setRange(0.0f, 1.0f);
			g_s_slider.setRange(0.0f, 1.0f);
			b_v_slider.setRange(0.0f, 1.0f);
			alpha_slider.setRange(0.0f, 1.0f);
			r_h_slider.setDigits(3);
			g_s_slider.setDigits(3);
			b_v_slider.setDigits(3);
			alpha_slider.setDigits(3);
		} else if(mode == ModeHSV) {
			r_h_slider.setText("Hue");
			g_s_slider.setText("Saturation");
			b_v_slider.setText("Value");
			r_h_slider.setRange(0.0f, 360.0f);
			g_s_slider.setRange(0.0f, 1.0f);
			b_v_slider.setRange(0.0f, 1.0f);
			alpha_slider.setRange(0.0f, 1.0f);
			r_h_slider.setDigits(2);
			g_s_slider.setDigits(3);
			b_v_slider.setDigits(3);
			alpha_slider.setDigits(3);
		} else {
			TS_ASSERT(0 && "ControlColor::mode_changed(): unknown mode");
		}
		update_color(rgb_color);
	}
	
	void ControlColor::slider_changed(const ControlSlider &slider) {
		uint32_t mode = mode_combo.getCurrentIndex();
		float32_t value = (float32_t)(slider.getValue() / slider.getMaxRange());
		if(mode == ModeRGBu8 || mode == ModeRGB) {
			if(slider == r_h_slider) setColor(Color(value, rgb_color.g, rgb_color.b, rgb_color.a));
			if(slider == g_s_slider) setColor(Color(rgb_color.r, value, rgb_color.b, rgb_color.a));
			if(slider == b_v_slider) setColor(Color(rgb_color.r, rgb_color.g, value, rgb_color.a));
		} else if(mode == ModeHSV) {
			if(slider == r_h_slider) set_color(Vector4f(value, hsv_color.y, hsv_color.z, hsv_color.w));
			if(slider == g_s_slider) set_color(Vector4f(hsv_color.x, value, hsv_color.z, hsv_color.w));
			if(slider == b_v_slider) set_color(Vector4f(hsv_color.x, hsv_color.y, value, hsv_color.w));
		} else {
			TS_ASSERT(0 && "ControlColor::slider_changed(): unknown mode");
		}
		if(slider == alpha_slider) {
			Color old_color = rgb_color;
			hsv_color.w = value;
			rgb_color.a = value;
			update_color(old_color);
		}
	}
	
	bool ControlColor::rect_callback(Command &command) {
		struct ColorParameters {
			Vector4f hsv_color;
			Color rgb_color;
		};
		ColorParameters parameters;
		parameters.hsv_color = hsv_color;
		parameters.rgb_color = rgb_color;
		command.setUniform(2, parameters);
		return true;
	}
	
	/*
	 */
	void ControlColor::set_color(const Vector4f &color) {
		Color old_rgb_color = rgb_color;
		hsv_color = saturate(color);
		rgb_color = Color(Color::hsv(hsv_color.x * 360.0f, hsv_color.y, hsv_color.z), hsv_color.w);
		update_color(old_rgb_color);
	}
	
	void ControlColor::setColor(const Color &color) {
		Vector4f old_hsv_color = hsv_color;
		Color old_rgb_color = rgb_color;
		rgb_color = saturate(color);
		if(!rgb_color.getHSV(hsv_color.x, hsv_color.y, hsv_color.z)) {
			hsv_color.x = old_hsv_color.x;
			hsv_color.y = old_hsv_color.y;
		} else {
			hsv_color.x /= 360.0f;
		}
		hsv_color.w = rgb_color.a;
		update_color(old_rgb_color);
	}
	
	/*
	 */
	void ControlColor::save_palette() {
		for(uint32_t i = 0; i < NumColors; i++) {
			const Color &color = palette_rects[i].getColor();
			String name = String::format("%scolor_%u", COLOR_CONFIG, i);
			if(color != Color::zero) config.set(name.get(), color);
			else config.remove(name.get());
		}
	}
	
	/*
	 */
	void ControlColor::update_color(const Color &old_color) {
		
		// update sliders
		uint32_t mode = mode_combo.getCurrentIndex();
		if(mode == ModeRGBu8) {
			r_h_slider.setValue(rgb_color.r * 255.0f);
			g_s_slider.setValue(rgb_color.g * 255.0f);
			b_v_slider.setValue(rgb_color.b * 255.0f);
			alpha_slider.setValue(rgb_color.a * 255.0f);
		} else if(mode == ModeRGB) {
			r_h_slider.setValue(rgb_color.r);
			g_s_slider.setValue(rgb_color.g);
			b_v_slider.setValue(rgb_color.b);
			alpha_slider.setValue(rgb_color.a);
		} else if(mode == ModeHSV) {
			r_h_slider.setValue(hsv_color.x * 360.0f);
			g_s_slider.setValue(hsv_color.y);
			b_v_slider.setValue(hsv_color.z);
			alpha_slider.setValue(rgb_color.a);
		} else {
			TS_ASSERT(0 && "ControlColor::update_color(): unknown mode");
		}
		
		// update html color
		uint32_t alpha = rgb_color.getAu8();
		if(alpha == 255) color_edit.setText(String::format("#%02X%02X%02X", rgb_color.getRu8(), rgb_color.getGu8(), rgb_color.getBu8()));
		else color_edit.setText(String::format("#%02X%02X%02X%02X", rgb_color.getRu8(), rgb_color.getGu8(), rgb_color.getBu8(), alpha));
		
		// update palette color
		palette_rect.setColor(Color(rgb_color, max(rgb_color.a, 0.01f)));
		
		// changed callback
		if(old_color != rgb_color && changed_func) {
			changed_func(rgb_color, is_changed);
			is_changed = true;
		}
	}
	
	/*
	 */
	bool ControlColor::update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale) {
		
		// check control
		if(!isEnabled()) return false;
		
		// create resources
		if(!color_pipeline && create_pipelines()) {
			color_rect.setPipeline(color_pipeline, [this](Command command, CanvasElement element) {
				return rect_callback(command);
			});
			value_rect.setPipeline(value_pipeline, [this](Command command, CanvasElement element) {
				return rect_callback(command);
			});
			palette_rect.setPipeline(palette_pipeline);
			for(uint32_t i = 0; i < NumColors; i++) {
				palette_rects[i].setPipeline(palette_pipeline);
			}
		}
		
		// drag and drop
		if(dragged_rect) {
			uint32_t src_index = Maxu32;
			uint32_t dest_index = Maxu32;
			if(palette_rect == dragged_rect) src_index = NumColors;
			if((palette_rect.getRect() + palette_rect.getOffset().xy).inside(dropped_position)) dest_index = NumColors;
			for(uint32_t i = 0; i < NumColors; i++) {
				if(palette_rects[i] == dragged_rect) src_index = i;
				if((palette_rects[i].getRect() + palette_rects[i].getOffset().xy).inside(dropped_position)) dest_index = i;
				if(src_index != Maxu32 && dest_index != Maxu32) break;
			}
			if(src_index < NumColors && dest_index < NumColors) {
				Color src_color = palette_rects[src_index].getColor();
				palette_rects[src_index].setColor(palette_rects[dest_index].getColor());
				palette_rects[dest_index].setColor(src_color);
			} else if(src_index == NumColors && dest_index < NumColors) {
				palette_rects[dest_index].setColor(rgb_color);
			} else if(src_index < NumColors && dest_index == NumColors) {
				setColor(palette_rects[src_index].getColor());
			}
			if(dest_index < NumColors) {
				save_palette();
			}
			dragged_rect.clearPtr();
		}
		
		return false;
	}
}

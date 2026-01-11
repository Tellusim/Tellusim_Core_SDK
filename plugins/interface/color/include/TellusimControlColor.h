// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_INTERFACE_CONTROL_COLOR_H__
#define __TELLUSIM_PLUGINS_INTERFACE_CONTROL_COLOR_H__

#include <interface/TellusimControls.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Config;
	
	/* ControlColor
	 */
	class ControlColor : public ControlBase {
			
		public:
			
			/// color constructor
			ControlColor(Control *parent, const Device &device, Config &config, const Color &color = Color::white);
			virtual ~ControlColor();
			
			/// disable copying
			ControlColor(const ControlColor&) = delete;
			ControlColor &operator=(const ControlColor&) = delete;
			
			/// changed callback
			using ChangedCallback = Function<void(Color color, bool is_changed)>;
			void setChangedCallback(const ChangedCallback &func) { changed_func = func; }
			TS_INLINE ChangedCallback getChangedCallback() const { return changed_func; }
			
			/// current color
			void setColor(const Color &color);
			TS_INLINE const Color &getColor() const { return rgb_color; }
			
		private:
			
			/// create control
			void create();
			bool create_pipelines();
			
			/// control callbacks
			void mode_changed();
			void slider_changed(const ControlSlider &slider);
			bool rect_callback(Command &command);
			
			/// set color
			void set_color(const Vector4f &color);
			
			/// save palette
			void save_palette();
			
			/// update control
			void update_color(const Color &old_color);
			virtual bool update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale);
			
			enum {
				ModeRGBu8 = 0,
				ModeRGB,
				ModeHSV,
			};
			
			enum {
				NumColors = 22,
			};
			
			const Device &device;					// device
			
			Config &config;							// config
			
			Pipeline color_pipeline;				// color pipeline
			Pipeline value_pipeline;				// value pipeline
			Pipeline palette_pipeline;				// palette pipeline
			
			ControlRect color_rect;					// color rect
			ControlRect value_rect;					// value rect
			ControlEdit color_edit;					// color edit
			ControlCombo mode_combo;				// mode combo
			ControlSlider r_h_slider;				// r h slider
			ControlSlider g_s_slider;				// g s slider
			ControlSlider b_v_slider;				// b v slider
			ControlSlider alpha_slider;				// alpha slider
			
			ControlRect palette_rect;				// palette rect
			ControlRect palette_rects[NumColors];	// palette rects
			
			ControlRect dragged_rect;				// dragged rect
			Vector2f dropped_position;				// dropped position
			
			ChangedCallback changed_func;			// changed callback
			bool is_changed = false;				// changed flag
			
			Vector4f hsv_color = Vector4f::zero;	// hsv color
			Color rgb_color = Color::white;			// rgb color
	};
}

#endif /* __TELLUSIM_PLUGINS_INTERFACE_CONTROL_COLOR_H__ */

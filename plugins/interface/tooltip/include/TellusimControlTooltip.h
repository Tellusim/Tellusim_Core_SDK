// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_INTERFACE_CONTROL_TOOLTIP_H__
#define __TELLUSIM_PLUGINS_INTERFACE_CONTROL_TOOLTIP_H__

#include <core/TellusimMap.h>
#include <interface/TellusimControls.h>

/*
 */
namespace Tellusim {
	
	/* ControlTooltip
	 */
	class ControlTooltip : public ControlBase {
			
		public:
			
			/// tooltip constructor
			explicit ControlTooltip(Control *parent);
			virtual ~ControlTooltip();
			
			/// disable copying
			ControlTooltip(const ControlTooltip&) = delete;
			ControlTooltip &operator=(const ControlTooltip&) = delete;
			
			/// tooltip offset
			void setOffset(float32_t offset);
			TS_INLINE float32_t getOffset() const { return offset; }
			
			/// tooltip radius
			void setRadius(float32_t radius);
			TS_INLINE float32_t getRadius() const { return canvas_rect.getRadius(); }
			
			/// tooltip color
			void setColor(const Color &color);
			TS_INLINE const Color &getColor() const { return canvas_rect.getColor(); }
			
			/// tooltip callbacks
			using TextCallback = Function<String(Control control, Vector2f *position, float32_t *height)>;
			using DrawCallback = Function<String(Control control, CanvasMesh mesh, Vector2f *position, float32_t *height)>;
			
			/// tooltips
			void clearTooltips();
			void removeTooltip(const Control &control, bool hierarchy = true);
			void addTooltip(const Control &control, const char *text);
			void addTooltip(const Control &control, const String &text);
			void addTooltip(const Control &control, const TextCallback &func);
			void addTooltip(const Control &control, const DrawCallback &func);
			
			/// tooltip flag
			TS_INLINE bool isTooltip() const { return is_tooltip; }
			
		private:
			
			/// create control
			void create();
			
			/// update control
			virtual void update_enabled(bool enabled);
			virtual void update_style(const FontStyle &style);
			virtual bool update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale);
			
			float32_t offset = 32.0f;					// tooltip offset
			
			Map<Control, String> tooltips;				// text tooltips
			Map<Control, TextCallback> text_callbacks;	// text callbacks
			Map<Control, DrawCallback> draw_callbacks;	// draw callbacks
			
			Control tooltip_control;					// tooltip control
			Vector2f tooltip_position;					// tooltip position
			uint64_t tooltip_time = 0;					// tooltip time
			bool is_tooltip = false;					// tooltip flag
			
			CanvasRect canvas_rect;						// canvas rect
			CanvasText canvas_text;						// canvas text
			CanvasMesh canvas_mesh;						// canvas mesh
	};
}

#endif /* __TELLUSIM_PLUGINS_INTERFACE_CONTROL_TOOLTIP_H__ */

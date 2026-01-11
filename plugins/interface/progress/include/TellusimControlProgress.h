// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_INTERFACE_CONTROL_PROGRESS_H__
#define __TELLUSIM_PLUGINS_INTERFACE_CONTROL_PROGRESS_H__

#include <core/TellusimAtomic.h>
#include <interface/TellusimControls.h>

/*
 */
namespace Tellusim {
	
	/* ControlProgress
	 */
	class ControlProgress : public ControlBase {
			
		public:
			
			/// progress constructor
			explicit ControlProgress(Control *parent);
			virtual ~ControlProgress();
			
			/// disable copying
			ControlProgress(const ControlProgress&) = delete;
			ControlProgress &operator=(const ControlProgress&) = delete;
			
			/// progress size
			void setSize(float32_t width, float32_t height);
			TS_INLINE float32_t getWidth() const { return progress_panel.getWidth(); }
			TS_INLINE float32_t getHeight() const { return progress_panel.getHeight(); }
			
			/// progress radius
			void setRadius(float32_t radius);
			TS_INLINE float32_t getRadius() const { return progress_panel.getRadius(); }
			
			/// progress color
			void setColor(const Color &color);
			TS_INLINE const Color &getColor() const { return progress_panel.getColor(); }
			
			/// progress font style
			bool setFontSize(uint32_t size);
			uint32_t getFontSize() const { return progress_text.getFontSize(); }
			
			bool setFontStyle(const FontStyle &style);
			const FontStyle &getFontStyleConst() const { return progress_text.getFontStyleConst(); }
			const FontStyle &getFontStyle() const { return progress_text.getFontStyle(); }
			FontStyle &getFontStyle() { return progress_text.getFontStyle(); }
			
			/// progress rect color
			void setRectColor(const Color &color);
			TS_INLINE const Color &getRectColor() const { return progress_rect.getColor(); }
			
			/// button radius
			void setButtonRadius(float32_t radius);
			TS_INLINE float32_t getButtonRadius() const { return cancel_button.getButtonRadius(); }
			
			/// progress title
			void setTitle(const char *text);
			void setTitle(const String &text);
			
			/// progress text
			bool setText(const char *text);
			bool setText(const String &text);
			TS_INLINE const String &getText() const { return current_text; }
			
			/// progress value
			bool setProgress(uint32_t progress);
			TS_INLINE uint32_t getProgress() { return (uint32_t)current_progress.get(); }
			
			/// progress status
			void setCanceled(bool canceled);
			bool isCanceled();
			
			/// progress controls
			TS_INLINE ControlPanel &getProgressPanel() { return progress_panel; }
			TS_INLINE ControlText &getProgressText() { return progress_text; }
			TS_INLINE ControlRect &getProgressRect() { return progress_rect; }
			TS_INLINE ControlButton &getCancelButton() { return cancel_button; }
			TS_INLINE ControlText &getTitleText() { return title_text; }
			
		private:
			
			/// create control
			void create();
			
			/// update control
			virtual void update_enabled(bool enabled);
			virtual bool update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale);
			
			SpinLock lock;						// atomic lock
			
			Atomici32 is_canceled = 0;			// canceled flag
			
			String current_text;				// progress text
			Atomici32 current_progress;			// progress value
			
			ControlPanel progress_panel;		// progress panel
			ControlText progress_text;			// progress text
			ControlRect progress_rect;			// progress rect
			ControlButton cancel_button;		// cancel button
			ControlText title_text;				// title text
	};
}

#endif /* __TELLUSIM_PLUGINS_INTERFACE_CONTROL_PROGRESS_H__ */

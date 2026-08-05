// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_INTERFACE_CONTROL_POPUP_H__
#define __TELLUSIM_PLUGINS_INTERFACE_CONTROL_POPUP_H__

#include <core/TellusimMap.h>
#include <interface/TellusimControls.h>

/*
 */
namespace Tellusim {
	
	/* ControlPopup
	 */
	class ControlPopup : public ControlBase {
			
		public:
			
			/// popup constructor
			explicit ControlPopup(Control *parent);
			virtual ~ControlPopup();
			
			/// disable copying
			ControlPopup(const ControlPopup&) = delete;
			ControlPopup &operator=(const ControlPopup&) = delete;
			
			/// popup radius
			void setRadius(float32_t radius);
			TS_INLINE float32_t getRadius() const { return radius; }
			
			/// popup color
			void setColor(const Color &color);
			TS_INLINE const Color &getColor() const { return color; }
			
			/// popup item color
			void setItemColor(const Color &color);
			TS_INLINE const Color &getItemColor() const { return item_color; }
			
			/// popup stroke style
			void setStrokeStyle(const StrokeStyle &style);
			TS_INLINE const StrokeStyle &getStrokeStyle() const { return stroke_style; }
			
			/// popup gradient style
			void setGradientStyle(const GradientStyle &style);
			TS_INLINE const GradientStyle &getGradientStyle() const { return gradient_style; }
			
			/// popup spacing
			void setSpacing(const Vector2f &spacing);
			void setSpacing(float32_t x, float32_t y);
			TS_INLINE const Vector2f &getSpacing() const { return spacing; }
			
			/// popup callback
			using PopupCallback = Function<Align(ControlPanel panel)>;
			
			/// popups
			void closePopups();
			void clearPopups();
			void removePopup(const Control &control, bool hierarchy = true);
			void addPopup(const Control &control, const PopupCallback &func);
			void addPopup(const Vector2f &position, const PopupCallback &func);
			void addPopup(Control *parent, const Vector2f &position, const PopupCallback &func);
			
			/// button item
			using ClickedCallback = Function<void()>;
			void createItem(ControlPanel &panel, const char *text, const ClickedCallback &func, const String &key = String::null);
			void createItem(ControlPanel &panel, const String &text, const ClickedCallback &func, const String &key = String::null);
			
			/// image button item
			void createItem(ControlPanel &panel, const char *text, const char *texture, const Rect &texcoord, const ClickedCallback &func, const String &key = String::null);
			void createItem(ControlPanel &panel, const String &text, const char *texture, const Rect &texcoord, const ClickedCallback &func, const String &key = String::null);
			
			/// check item
			using ChangedCallback = Function<void(bool)>;
			void createItem(ControlPanel &panel, const char *text, bool checked, const ChangedCallback &func, const String &key = String::null);
			void createItem(ControlPanel &panel, const String &text, bool checked, const ChangedCallback &func, const String &key = String::null);
			
			/// popup item
			void createItemPopup(ControlPanel &panel, const char *text, const PopupCallback &func);
			void createItemPopup(ControlPanel &panel, const String &text, const PopupCallback &func);
			
			/// separator item
			void createItemSeparator(ControlPanel &panel) const;
			
			/// number of popups
			TS_INLINE uint32_t getNumPopups() const { return popups.size(); }
			
		private:
			
			/// create control
			void create();
			
			/// create panel
			ControlPanel create_panel(Control *parent, const Control &control, const Vector2f &position, float32_t scale, const PopupCallback &func) const;
			
			/// create item
			ControlPanel create_item(Control *parent) const;
			
			/// clear popups
			bool clear_popups(ControlRoot &root, const Control &control);
			
			/// update control
			virtual void update_style(const FontStyle &style);
			virtual bool update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale);
			
			float32_t radius = 0.0f;					// popup radius
			Color color = Color::zero;					// popup color
			StrokeStyle stroke_style;					// popup stroke style
			GradientStyle gradient_style;				// popup gradient style
			Vector2f spacing = Vector2f::zero;			// popup spacing
			
			Color item_color = Color::zero;				// popup item color
			
			Map<Control, PopupCallback> callbacks;		// popup callbacks
			
			struct Popup {
				Control control;						// popup control
				ControlPanel panel;						// popup panel
				uint64_t time = 0;						// popup time
			};
			Array<Popup> popups;						// control popups
			
			Control popup_control;						// popup control
			uint64_t popup_time = 0;					// popup time
			
			bool close_popups = false;					// close popups flag
	};
}

#endif /* __TELLUSIM_PLUGINS_INTERFACE_CONTROL_POPUP_H__ */

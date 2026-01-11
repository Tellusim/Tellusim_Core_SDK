// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_INTERFACE_CONTROL_ELEMENT_H__
#define __TELLUSIM_PLUGINS_INTERFACE_CONTROL_ELEMENT_H__

#include <interface/TellusimControls.h>

/*
 */
namespace Tellusim {
	
	/* ControlElement
	 */
	class ControlElement : public ControlBase {
			
		public:
			
			/// element constructor
			explicit ControlElement(Control *parent);
			ControlElement(Control *parent, const CanvasElement &element);
			virtual ~ControlElement();
			
			/// disable copying
			ControlElement(const ControlElement&) = delete;
			ControlElement &operator=(const ControlElement&) = delete;
			
			/// input margin
			void setInputMargin(float32_t value) { input_margin = Rect(value); }
			void setInputMargin(float32_t horizontal, float32_t vertical) { input_margin = Rect(horizontal, vertical); }
			void setInputMargin(float32_t left, float32_t right, float32_t bottom, float32_t top) { input_margin = Rect(left, right, bottom, top); }
			void setInputMargin(const Rect &margin) { input_margin = margin; }
			TS_INLINE const Rect &getInputMargin() const { return input_margin; }
			
			/// canvas element
			void setElement(const CanvasElement &element);
			TS_INLINE CanvasElement &getElement() { return element; }
			TS_INLINE const CanvasElement &getElement() const { return element; }
			
			/// element color
			void setColor(const Color &c) { color = c; }
			TS_INLINE const Color &getColor() const { return color; }
			
			/// state offset
			void setStateOffset(State state, const Vector2f &offset) { offsets[state] = offset; }
			TS_INLINE const Vector2f &getStateOffset(State state) const { return offsets[state]; }
			
			/// state color
			void setStateColor(State state, const Color &color) { colors[state] = color; }
			TS_INLINE const Color &getStateColor(State state) const { return colors[state]; }
			
			/// state callback
			using StateCallback = Function<void(ControlElement*, State state)>;
			void setStateCallback(const StateCallback &func) { state_func = func; }
			TS_INLINE StateCallback getStateCallback() const { return state_func; }
			void updateState() { if(state_func) state_func(this, getState()); }
			
			/// pressed callback
			using PressedCallback = Function<void(ControlElement*, float32_t x, float32_t y)>;
			void setPressedCallback(const PressedCallback &func) { pressed_func = func; }
			TS_INLINE PressedCallback getPressedCallback() const { return pressed_func; }
			TS_INLINE bool isPressed() { bool ret = is_pressed; is_clicked = false; return ret; }
			
			/// released callback
			using ReleasedCallback = Function<void(ControlElement*, float32_t x, float32_t y)>;
			void setReleasedCallback(const ReleasedCallback &func) { released_func = func; }
			TS_INLINE ReleasedCallback getReleasedCallback() const { return released_func; }
			TS_INLINE bool isReleased() { bool ret = is_released; is_clicked = false; return ret; }
			
			/// clicked callback
			using ClickedCallback = Function<void(ControlElement*)>;
			void setClickedCallback(const ClickedCallback &func) { clicked_func = func; }
			void setClicked2Callback(const ClickedCallback &func) { clicked2_func = func; }
			void setClickedRightCallback(const ClickedCallback &func) { clickedr_func = func; }
			TS_INLINE ClickedCallback getClickedCallback() const { return clicked_func; }
			TS_INLINE ClickedCallback getClicked2Callback() const { return clicked2_func; }
			TS_INLINE ClickedCallback getClickedRightCallback() const { return clickedr_func; }
			TS_INLINE bool isClicked() { bool ret = is_clicked; is_clicked = false; return ret; }
			
			/// element rectangle
			void setElementRect(const Rect &rect) { element_rect = rect; }
			TS_INLINE const Rect &getElementRect() const { return element_rect; }
			
		private:
			
			/// update control
			virtual void update_enabled(bool enabled);
			virtual void update_rectangle(ControlRoot &root, int32_t &order, uint32_t scale);
			virtual bool update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale);
			
			uint32_t click_mode = 0;			// click mode
			
			bool is_pressed = false;			// pressed flag
			bool is_released = false;			// released flag
			bool is_clicked = false;			// clicked flag
			
			StateCallback state_func;			// state callback
			PressedCallback pressed_func;		// pressed callback
			ReleasedCallback released_func;		// released callback
			ClickedCallback clicked_func;		// clicked callback
			ClickedCallback clicked2_func;		// clicked2 callback
			ClickedCallback clickedr_func;		// clickedr callback
			
			Rect input_margin = Rect(0.0f);		// input margin
			
			CanvasElement element;				// canvas element
			Color color = Color::white;			// element color
			Vector2f offsets[NumStates];		// state offsets
			Color colors[NumStates];			// state colors
			
			Rect element_rect;					// element rect
	};
}

#endif /* __TELLUSIM_PLUGINS_INTERFACE_CONTROL_ELEMENT_H__ */

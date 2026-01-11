// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_INTERFACE_CONTROL_BUTTON_H__
#define __TELLUSIM_PLUGINS_INTERFACE_CONTROL_BUTTON_H__

#include <interface/TellusimControls.h>

/*
 */
namespace Tellusim {
	
	/* ControlButtonBase
	 */
	class ControlButtonBase : public ControlBase {
			
		public:
			
			/// button constructor
			explicit ControlButtonBase(Control *parent);
			virtual ~ControlButtonBase();
			
			/// disable copying
			ControlButtonBase(const ControlButtonBase&) = delete;
			ControlButtonBase &operator=(const ControlButtonBase&) = delete;
			
			/// button elements
			void addElement(State state, const CanvasElement &element);
			void setElement(State state, const CanvasElement &element);
			void setElements(State state, const Array<CanvasElement> &elements);
			void setElements(State state, const InitializerList<CanvasElement> &elements);
			
			TS_INLINE uint32_t getNumElements(State state) const { return elements[state].size(); }
			TS_INLINE CanvasElement getElement(State state, uint32_t index) { return elements[state][index]; }
			
			/// state offset
			void setStateOffset(State state, const Vector2f &offset) { offsets[state] = offset; }
			TS_INLINE const Vector2f &getStateOffset(State state) const { return offsets[state]; }
			
			/// state color
			void setStateColor(State state, const Color &color) { colors[state] = color; }
			TS_INLINE const Color &getStateColor(State state) const { return colors[state]; }
			
			/// state callback
			using StateCallback = Function<void(ControlButtonBase*, State state)>;
			void setStateCallback(const StateCallback &func) { state_func = func; }
			TS_INLINE StateCallback getStateCallback() const { return state_func; }
			void updateState() { if(state_func) state_func(this, getState()); }
			
			/// pressed callback
			using PressedCallback = Function<void(ControlButtonBase*)>;
			void setPressedCallback(const PressedCallback &func) { pressed_func = func; }
			TS_INLINE PressedCallback getPressedCallback() const { return pressed_func; }
			TS_INLINE bool isPressed() { bool ret = is_pressed; is_clicked = false; return ret; }
			
			/// released callback
			using ReleasedCallback = Function<void(ControlButtonBase*)>;
			void setReleasedCallback(const ReleasedCallback &func) { released_func = func; }
			TS_INLINE ReleasedCallback getReleasedCallback() const { return released_func; }
			TS_INLINE bool isReleased() { bool ret = is_released; is_clicked = false; return ret; }
			
			/// clicked callback
			using ClickedCallback = Function<void(ControlButtonBase*)>;
			void setClickedCallback(const ClickedCallback &func) { clicked_func = func; }
			TS_INLINE ClickedCallback getClickedCallback() const { return clicked_func; }
			TS_INLINE bool isClicked() { bool ret = is_clicked; is_clicked = false; return ret; }
			
			/// button rectangle
			void setButtonRect(const Rect &rect) { button_rect = rect; }
			TS_INLINE const Rect &getButtonRect() const { return button_rect; }
			
		private:
			
			/// update control
			virtual void update_enabled(bool enabled);
			virtual void update_rectangle(ControlRoot &root, int32_t &order, uint32_t scale);
			virtual bool update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale);
			
			bool is_pressed = false;					// pressed flag
			bool is_released = false;					// released flag
			bool is_clicked = false;					// clicked flag
			
			StateCallback state_func;					// state callback
			PressedCallback pressed_func;				// pressed callback
			ReleasedCallback released_func;				// released callback
			ClickedCallback clicked_func;				// clicked callback
			
			Array<CanvasElement> elements[NumStates];	// button elements
			Vector2f offsets[NumStates];				// state offsets
			Color colors[NumStates];					// state colors
			
			Rect button_rect;							// button rect
	};
}

#endif /* __TELLUSIM_PLUGINS_INTERFACE_CONTROL_BUTTON_H__ */

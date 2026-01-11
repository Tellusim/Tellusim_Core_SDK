// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_INTERFACE_CONTROL_SLIDER_H__
#define __TELLUSIM_PLUGINS_INTERFACE_CONTROL_SLIDER_H__

#include <interface/TellusimControls.h>

/*
 */
namespace Tellusim {
	
	/* ControlSliderBase
	 */
	class ControlSliderBase : public ControlBase {
			
		public:
			
			/// slider constructor
			explicit ControlSliderBase(Control *parent);
			ControlSliderBase(Control *parent, float64_t value, float64_t min, float64_t max);
			virtual ~ControlSliderBase();
			
			/// disable copying
			ControlSliderBase(const ControlSliderBase&) = delete;
			ControlSliderBase &operator=(const ControlSliderBase&) = delete;
			
			/// slider step
			void setStep(float64_t s) { step = s; }
			TS_INLINE float64_t getStep() const { return step; }
			
			/// slider value
			void setValue(float64_t value, bool callback = false);
			TS_INLINE float64_t getValue() const { return value; }
			TS_INLINE float32_t getValuef32() const { return (float32_t)value; }
			TS_INLINE uint32_t getValueu32() const { return (uint32_t)value; }
			TS_INLINE int32_t getValuei32() const { return (int32_t)value; }
			
			/// slider range
			void setRange(float64_t min, float64_t max);
			TS_INLINE float64_t getMinRange() const { return min_range; }
			TS_INLINE float64_t getMaxRange() const { return max_range; }
			
			/// slider elements
			void addElement(State state, const CanvasElement &element);
			void setElement(State state, const CanvasElement &element);
			void setElements(State state, const Array<CanvasElement> &elements);
			void setElements(State state, const InitializerList<CanvasElement> &elements);
			
			TS_INLINE uint32_t getNumElements(State state) const { return elements[state].size(); }
			TS_INLINE CanvasElement getElement(State state, uint32_t index) { return elements[state][index]; }
			
			/// slider handles
			void addHandle(State state, const CanvasElement &element);
			void setHandle(State state, const CanvasElement &element);
			void setHandles(State state, const Array<CanvasElement> &elements);
			void setHandles(State state, const InitializerList<CanvasElement> &elements);
			
			TS_INLINE uint32_t getNumHandles(State state) const { return handles[state].size(); }
			TS_INLINE CanvasElement getHandle(State state, uint32_t index) { return handles[state][index]; }
			
			/// state offset
			void setStateOffset(State state, const Vector2f &offset) { offsets[state] = offset; }
			TS_INLINE const Vector2f &getStateOffset(State state) const { return offsets[state]; }
			
			/// state color
			void setStateColor(State state, const Color &color) { colors[state] = color; }
			TS_INLINE const Color &getStateColor(State state) const { return colors[state]; }
			
			/// state callback
			using StateCallback = Function<void(ControlSliderBase*, State state)>;
			void setStateCallback(const StateCallback &func) { state_func = func; }
			TS_INLINE StateCallback getStateCallback() const { return state_func; }
			void updateState() { if(state_func) state_func(this, getState()); }
			
			/// released callback
			using ReleasedCallback = Function<void(ControlSliderBase*)>;
			void setReleasedCallback(const ReleasedCallback &func) { released_func = func; }
			TS_INLINE ReleasedCallback getReleasedCallback() const { return released_func; }
			TS_INLINE bool isReleased() { bool ret = is_released; is_clicked = false; return ret; }
			
			/// clicked callback
			using ClickedCallback = Function<void(ControlSliderBase*)>;
			void setClickedCallback(const ClickedCallback &func) { clicked_func = func; }
			TS_INLINE ClickedCallback getClickedCallback() const { return clicked_func; }
			TS_INLINE bool isClicked() { bool ret = is_clicked; is_clicked = false; return ret; }
			
			/// changed callback
			using ChangedCallback = Function<void(ControlSliderBase*)>;
			void setChangedCallback(const ChangedCallback &func) { changed_func = func; }
			TS_INLINE ChangedCallback getChangedCallback() const { return changed_func; }
			TS_INLINE bool isChanged(bool clear = true) { bool ret = is_changed; if(clear) is_changed = false; return ret; }
			
			/// slider rectangle
			void setSliderRect(const Rect &rect) { slider_rect = rect; }
			TS_INLINE const Rect &getSliderRect() const { return slider_rect; }
			
			/// handle rectangle
			void setHandleRect(const Rect &rect) { handle_rect = rect; }
			TS_INLINE const Rect &getHandleRect() const { return handle_rect; }
			
		private:
			
			/// update control
			virtual void update_enabled(bool enabled);
			virtual void update_rectangle(ControlRoot &root, int32_t &order, uint32_t scale);
			virtual bool update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale);
			
			float64_t step = 0.0;						// slider step
			float64_t value = 0.0;						// current value
			float64_t min_range = 0.0;					// minimum range
			float64_t max_range = 1.0;					// maximum range
			
			float64_t handle_offset = 0.0;				// handle offset
			
			bool is_released = false;					// released flag
			bool is_clicked = false;					// clicked flag
			bool is_changed = false;					// changed flag
			
			StateCallback state_func;					// state callback
			ReleasedCallback released_func;				// released callback
			ClickedCallback clicked_func;				// clicked callback
			ChangedCallback changed_func;				// changed callback
			
			Array<CanvasElement> elements[NumStates];	// slider elements
			Array<CanvasElement> handles[NumStates];	// slider handles
			Vector2f offsets[NumStates];				// state offsets
			Color colors[NumStates];					// state colors
			
			Rect slider_rect;							// slider rect
			Rect handle_rect;							// handle rect
	};
}

#endif /* __TELLUSIM_PLUGINS_INTERFACE_CONTROL_SLIDER_H__ */

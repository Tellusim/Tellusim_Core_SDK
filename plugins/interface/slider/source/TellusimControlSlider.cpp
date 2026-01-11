// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include "../include/TellusimControlSlider.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	ControlSliderBase::ControlSliderBase(Control *parent) : ControlBase(parent) {
		for(uint32_t i = 0; i < NumStates; i++) {
			offsets[i] = Vector2f::zero;
			colors[i] = Color::zero;
		}
		ControlBase::create();
	}
	
	ControlSliderBase::ControlSliderBase(Control *parent, float64_t value, float64_t min, float64_t max) : ControlSliderBase(parent) {
		setValue(value);
		setRange(min, max);
	}
	
	ControlSliderBase::~ControlSliderBase() {
		
	}
	
	/*
	 */
	void ControlSliderBase::setValue(float64_t v, bool callback) {
		float64_t old_value = value;
		value = v;
		if(callback && changed_func && old_value != value) changed_func(this);
	}
	
	void ControlSliderBase::setRange(float64_t min, float64_t max) {
		min_range = min;
		max_range = max;
	}
	
	/*
	 */
	void ControlSliderBase::addElement(State state, const CanvasElement &e) {
		elements[state].append(e);
	}
	
	void ControlSliderBase::setElement(State state, const CanvasElement &e) {
		elements[state].clear();
		elements[state].append(e);
	}
	
	void ControlSliderBase::setElements(State state, const Array<CanvasElement> &e) {
		elements[state] = e;
	}
	
	void ControlSliderBase::setElements(State state, const InitializerList<CanvasElement> &e) {
		elements[state] = e;
	}
	
	/*
	 */
	void ControlSliderBase::addHandle(State state, const CanvasElement &h) {
		handles[state].append(h);
	}
	
	void ControlSliderBase::setHandle(State state, const CanvasElement &h) {
		handles[state].clear();
		handles[state].append(h);
	}
	
	void ControlSliderBase::setHandles(State state, const Array<CanvasElement> &h) {
		handles[state] = h;
	}
	
	void ControlSliderBase::setHandles(State state, const InitializerList<CanvasElement> &h) {
		handles[state] = h;
	}
	
	/*
	 */
	void ControlSliderBase::update_enabled(bool enabled) {
		enabled &= isEnabled();
		State slider_state = getState();
		if(!elements[slider_state]) slider_state = StateNormal;
		for(uint32_t i = 0; i < NumStates; i++) {
			if(i == StateUnknown || i == (uint32_t)slider_state) continue;
			for(CanvasElement &element : elements[i]) {
				element.setEnabled(false);
			}
		}
		for(CanvasElement &element : elements[StateUnknown]) {
			element.setEnabled(enabled);
		}
		for(CanvasElement &element : elements[slider_state]) {
			element.setEnabled(enabled);
		}
		State handle_state = getState();
		if(!handles[handle_state]) handle_state = StateNormal;
		for(uint32_t i = 0; i < NumStates; i++) {
			if(i == StateUnknown || i == (uint32_t)handle_state) continue;
			for(CanvasElement &handle : handles[i]) {
				handle.setEnabled(false);
			}
		}
		for(CanvasElement &handle : handles[StateUnknown]) {
			handle.setEnabled(enabled);
		}
		for(CanvasElement &handle : handles[handle_state]) {
			handle.setEnabled(enabled);
		}
		ControlBase::update_enabled(enabled);
	}
	
	void ControlSliderBase::update_rectangle(ControlRoot &root, int32_t &order, uint32_t scale) {
		State slider_state = getState();
		if(!elements[slider_state]) slider_state = StateNormal;
		for(CanvasElement &element : elements[slider_state]) {
			element.setOrder(order++);
		}
		for(CanvasElement &element : elements[StateUnknown]) {
			element.setOrder(order++);
		}
		if(!slider_rect) {
			for(uint32_t i = 0; i < NumStates; i++) {
				for(CanvasElement &element : elements[i]) {
					slider_rect.expand(element.getRect());
				}
			}
		}
		State handle_state = getState();
		if(!handles[handle_state]) handle_state = StateNormal;
		for(CanvasElement &handle : handles[handle_state]) {
			handle.setOrder(order++);
		}
		for(CanvasElement &handle : handles[StateUnknown]) {
			handle.setOrder(order++);
		}
		if(!handle_rect) {
			for(uint32_t i = 0; i < NumStates; i++) {
				for(CanvasElement &handle : handles[i]) {
					handle_rect.expand(handle.getRect());
				}
				slider_rect.expand(handle_rect);
			}
		}
		Rect rect = getSliderRect();
		rect.right += max(getWidth() - rect.getWidth(), 0.0f);
		rect.top += max(getHeight() - rect.getHeight(), 0.0f);
		rect += getMargin();
		set_rect(rect);
	}
	
	bool ControlSliderBase::update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale) {
		
		bool ret = false;
		
		// update expand
		update_expand(root, region);
		
		// control position
		Vector3f position = get_position(region, scale);
		Rect rect = getRect() - getMargin() + Vector2f(position);
		float32_t scale_x = rect.getWidth() / getSliderRect().getWidth();
		float32_t scale_y = rect.getHeight() / getSliderRect().getHeight();
		if(hasAlign(AlignAspect)) {
			float32_t scale = min(scale_x, scale_y);
			if(scale_x > scale) {
				if(hasAlign(AlignRight)) {
					float32_t offset = (scale_x - scale) * getSliderRect().getWidth();
					position.x += offset;
					rect.left += offset;
				} else if(hasAlign(AlignCenterX)) {
					float32_t offset = floor((scale_x - scale) * getSliderRect().getWidth() * 0.5f + 0.5f);
					position.x += offset;
					rect.left += offset;
					rect.right -= offset;
				} else {
					rect.right -= (scale_x - scale) * getSliderRect().getWidth();
				}
			}
			if(scale_y > scale) {
				if(hasAlign(AlignTop)) {
					float32_t offset = (scale_y - scale) * getSliderRect().getHeight();
					position.y += offset;
					rect.bottom += offset;
				} else if(hasAlign(AlignCenterY)) {
					float32_t offset = floor((scale_y - scale) * getSliderRect().getHeight() * 0.5f + 0.5f);
					position.y += offset;
					rect.bottom += offset;
					rect.top -= offset;
				} else {
					rect.top -= (scale_y - scale) * getSliderRect().getHeight();
				}
			}
			scale_x = scale;
			scale_y = scale;
		}
		setOffset(position);
		
		// slider parameters
		float64_t range = max_range - min_range;
		float64_t slider_width = rect.getWidth() - getHandleRect().getWidth() * scale_y;
		
		// handle rectangle
		Rect handle_rect = rect;
		handle_rect.left += (float32_t)(slider_width * saturate((value - min_range) / range));
		handle_rect.right = handle_rect.left + getHandleRect().getWidth() * scale_y;
		
		// control state
		State old_state = getState();
		if(!get_disabled(root) && range != 0.0) {
			if(!root.getCurrentControl() || root.getCurrentControl() == *this) {
				if((handle_rect.inside(root.getMouse()) && view.inside(root.getMouse())) || getState() == StatePressed) {
					if(root.getMouseButtons() & (ButtonLeft | ButtonLeft2)) {
						if(getState() != StatePressed) {
							handle_offset = root.getMouseX() - handle_rect.left;
						} else {
							float64_t offset = root.getMouseX() - rect.left - handle_offset;
							float64_t value = clamp(offset * range / slider_width + min_range, min_range, max_range);
							if(step > 0.0) value = floor(value / step + 0.5) * step;
							setValue(value, true);
							handle_offset += (value - clamp(getValue(), min_range, max_range)) * slider_width / range;
							is_changed = true;
						}
						set_state(root, StatePressed);
					} else {
						if(set_state(root, StateFocused) == StatePressed) {
							if(handle_rect.inside(root.getMouse())) {
								if(clicked_func) clicked_func(this);
								is_clicked = true;
							}
							if(released_func) released_func(this);
							is_released = true;
						}
					}
				} else if(rect.inside(root.getMouse()) && view.inside(root.getMouse())) {
					if(root.getMouseButtons() & (ButtonLeft | ButtonLeft2)) {
						root.setCurrentControl(*this);
						float64_t offset = root.getMouseX() - rect.left - getHandleRect().getWidth() * scale_y * 0.5;
						float64_t value = clamp(offset * range / slider_width + min_range, min_range, max_range);
						if(step > 0.0) value = floor(value / step + 0.5) * step;
						setValue(value, true);
						is_changed = true;
					}
					set_state(root, StateFocused);
				} else if(!root.getCurrentControl()) {
					if(set_state(root, StateNormal) == StatePressed) {
						if(released_func) released_func(this);
						is_released = true;
					}
				}
			} else {
				set_state(root, StateNormal);
			}
		} else {
			set_state(root, StateDisabled);
		}
		if(old_state != getState()) {
			if(state_func) state_func(this, getState());
			update_enabled(isEnabled());
			ret = true;
		}
		
		// transformation matrix
		Vector2f offset = getSliderRect().getCenter() + (rect.getSize() - getSliderRect().getSize()) * 0.5f;
		Matrix4x4f transform = Matrix4x4f::translate(Vector3f(position + Vector3f(offset, 0.0f)));
		transform *= Matrix4x4f::scale(scale_x, scale_y, 1.0f);
		transform *= Matrix4x4f::translate(Vector3f(-getSliderRect().getCenter(), 0.0f));
		
		// update elements
		State slider_state = getState();
		if(!elements[slider_state]) slider_state = StateNormal;
		for(CanvasElement &element : elements[StateUnknown]) {
			if(colors[getState()]) element.setColor(colors[getState()]);
			element.setTransform(transform);
		}
		for(CanvasElement &element : elements[slider_state]) {
			if(colors[getState()]) element.setColor(colors[getState()]);
			element.setTransform(transform);
		}
		
		// handle transform
		transform *= Matrix4x4f::translate(Vector3f(offsets[StateUnknown] + offsets[getState()], 0.0f) + Vector3f((handle_rect.left - rect.left) / scale_x, 0.0f, 0.0f));
		
		// update handles
		State handle_state = getState();
		if(!handles[handle_state]) handle_state = StateNormal;
		for(CanvasElement &handle : handles[StateUnknown]) {
			if(colors[getState()]) handle.setColor(colors[getState()]);
			handle.setTransform(transform);
		}
		for(CanvasElement &handle : handles[handle_state]) {
			if(colors[getState()]) handle.setColor(colors[getState()]);
			handle.setTransform(transform);
		}
		
		return ret;
	}
}

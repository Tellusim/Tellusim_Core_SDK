// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include "../include/TellusimControlButton.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	ControlButtonBase::ControlButtonBase(Control *parent) : ControlBase(parent) {
		for(uint32_t i = 0; i < NumStates; i++) {
			offsets[i] = Vector2f::zero;
			colors[i] = Color::zero;
		}
		ControlBase::create();
	}
	
	ControlButtonBase::~ControlButtonBase() {
		
	}
	
	/*
	 */
	void ControlButtonBase::addElement(State state, const CanvasElement &e) {
		elements[state].append(e);
	}
	
	void ControlButtonBase::setElement(State state, const CanvasElement &e) {
		elements[state].clear();
		elements[state].append(e);
	}
	
	void ControlButtonBase::setElements(State state, const Array<CanvasElement> &e) {
		elements[state] = e;
	}
	
	void ControlButtonBase::setElements(State state, const InitializerList<CanvasElement> &e) {
		elements[state] = e;
	}
	
	/*
	 */
	void ControlButtonBase::update_enabled(bool enabled) {
		enabled &= isEnabled();
		State state = getState();
		if(!elements[state]) state = StateNormal;
		for(uint32_t i = 0; i < NumStates; i++) {
			if(i == StateUnknown || i == (uint32_t)state) continue;
			for(CanvasElement &element : elements[i]) {
				element.setEnabled(false);
			}
		}
		for(CanvasElement &element : elements[StateUnknown]) {
			element.setEnabled(enabled);
		}
		for(CanvasElement &element : elements[state]) {
			element.setEnabled(enabled);
		}
		ControlBase::update_enabled(enabled);
	}
	
	void ControlButtonBase::update_rectangle(ControlRoot &root, int32_t &order, uint32_t scale) {
		State state = getState();
		if(!elements[state]) state = StateNormal;
		for(CanvasElement &element : elements[state]) {
			element.setOrder(order++);
		}
		for(CanvasElement &element : elements[StateUnknown]) {
			element.setOrder(order++);
		}
		if(!button_rect) {
			for(uint32_t i = 0; i < NumStates; i++) {
				for(CanvasElement &element : elements[i]) {
					button_rect.expand(element.getRect());
				}
			}
		}
		Rect rect = getButtonRect();
		rect.right += max(getWidth() - rect.getWidth(), 0.0f);
		rect.top += max(getHeight() - rect.getHeight(), 0.0f);
		rect += getMargin();
		set_rect(rect);
	}
	
	bool ControlButtonBase::update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale) {
		
		bool ret = false;
		
		// update expand
		update_expand(root, region);
		
		// control position
		Vector3f position = get_position(region, scale);
		Rect rect = getRect() - getMargin() + Vector2f(position);
		float32_t scale_x = rect.getWidth() / getButtonRect().getWidth();
		float32_t scale_y = rect.getHeight() / getButtonRect().getHeight();
		if(hasAlign(AlignAspect)) {
			float32_t scale = min(scale_x, scale_y);
			if(scale_x > scale) {
				if(hasAlign(AlignRight)) {
					float32_t offset = (scale_x - scale) * getButtonRect().getWidth();
					position.x += offset;
					rect.left += offset;
				} else if(hasAlign(AlignCenterX)) {
					float32_t offset = floor((scale_x - scale) * getButtonRect().getWidth() * 0.5f + 0.5f);
					position.x += offset;
					rect.left += offset;
					rect.right -= offset;
				} else {
					rect.right -= (scale_x - scale) * getButtonRect().getWidth();
				}
			}
			if(scale_y > scale) {
				if(hasAlign(AlignTop)) {
					float32_t offset = (scale_y - scale) * getButtonRect().getHeight();
					position.y += offset;
					rect.bottom += offset;
				} else if(hasAlign(AlignCenterY)) {
					float32_t offset = floor((scale_y - scale) * getButtonRect().getHeight() * 0.5f + 0.5f);
					position.y += offset;
					rect.bottom += offset;
					rect.top -= offset;
				} else {
					rect.top -= (scale_y - scale) * getButtonRect().getHeight();
				}
			}
			scale_x = scale;
			scale_y = scale;
		}
		setOffset(position);
		
		// control state
		State old_state = getState();
		if(!get_disabled(root)) {
			if(!root.getCurrentControl() || root.getCurrentControl() == *this) {
				if(rect.inside(root.getMouse()) && view.inside(root.getMouse())) {
					if(root.getMouseButtons() & (ButtonLeft | ButtonLeft2)) {
						set_state(root, StatePressed);
						if(pressed_func) pressed_func(this);
						is_pressed = true;
					} else {
						if(set_state(root, StateFocused) == StatePressed) {
							if(clicked_func) clicked_func(this);
							if(released_func) released_func(this);
							is_clicked = true;
							is_released = true;
						}
					}
				} else if(root.getCurrentControl() == *this) {
					if(root.getMouseButtons() & (ButtonLeft | ButtonLeft2)) {
						if(pressed_func) pressed_func(this);
						is_pressed = true;
					}
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
		Vector2f offset = offsets[StateUnknown] + offsets[getState()] + getButtonRect().getCenter() + (rect.getSize() - getButtonRect().getSize()) * 0.5f;
		Matrix4x4f transform = Matrix4x4f::translate(Vector3f(position + Vector3f(offset, 0.0f)));
		transform *= Matrix4x4f::scale(scale_x, scale_y, 1.0f);
		transform *= Matrix4x4f::translate(Vector3f(-getButtonRect().getCenter(), 0.0f));
		
		// update elements
		State state = getState();
		if(!elements[state]) state = StateNormal;
		for(CanvasElement &element : elements[StateUnknown]) {
			if(colors[getState()]) element.setColor(colors[getState()]);
			element.setTransform(transform);
		}
		for(CanvasElement &element : elements[state]) {
			if(colors[getState()]) element.setColor(colors[getState()]);
			element.setTransform(transform);
		}
		
		return ret;
	}
}

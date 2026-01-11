// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include "../include/TellusimControlElement.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	ControlElement::ControlElement(Control *parent) : ControlBase(parent) {
		for(uint32_t i = 0; i < NumStates; i++) {
			offsets[i] = Vector2f::zero;
			colors[i] = Color::zero;
		}
		ControlBase::create();
	}
	
	ControlElement::ControlElement(Control *parent, const CanvasElement &element) : ControlElement(parent) {
		if(element) setColor(element.getColor());
		setElement(element);
	}
	
	ControlElement::~ControlElement() {
		
	}
	
	/*
	 */
	void ControlElement::setElement(const CanvasElement &e) {
		element = e;
	}
	
	/*
	 */
	void ControlElement::update_enabled(bool enabled) {
		enabled &= isEnabled();
		if(element) element.setEnabled(enabled);
		ControlBase::update_enabled(enabled);
	}
	
	void ControlElement::update_rectangle(ControlRoot &root, int32_t &order, uint32_t scale) {
		if(element) {
			element.setOrder(order++);
			element_rect = element.getRect();
		}
		Rect rect = getElementRect();
		rect.right += max(getWidth() - rect.getWidth(), 0.0f);
		rect.top += max(getHeight() - rect.getHeight(), 0.0f);
		rect += getMargin();
		set_rect(rect);
	}
	
	bool ControlElement::update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale) {
		
		bool ret = false;
		
		// update expand
		update_expand(root, region);
		
		// control position
		Vector3f position = getPosition();
		
		// control rect
		Rect rect = getRect() - getMargin();
		
		// control scale
		bool has_scale = false;
		float32_t scale_x = 1.0f;
		float32_t scale_y = 1.0f;
		
		// control position
		if(!hasAlign(AlignOverlap)) {
			position = get_position(region, scale);
			rect += Vector2f(position);
			scale_x = rect.getWidth() / getElementRect().getWidth();
			scale_y = rect.getHeight() / getElementRect().getHeight();
			has_scale = !compare(scale_x, 1.0f, 1e-6f) || !compare(scale_y, 1.0f, 1e-6f);
			if(hasAlign(AlignAspect)) {
				float32_t scale = min(scale_x, scale_y);
				if(scale_x > scale) {
					if(hasAlign(AlignRight)) {
						float32_t offset = (scale_x - scale) * getElementRect().getWidth();
						position.x += offset;
						rect.left += offset;
					} else if(hasAlign(AlignCenterX)) {
						float32_t offset = floor((scale_x - scale) * getElementRect().getWidth() * 0.5f + 0.5f);
						position.x += offset;
						rect.left += offset;
						rect.right -= offset;
					} else {
						rect.right -= (scale_x - scale) * getElementRect().getWidth();
					}
				}
				if(scale_y > scale) {
					if(hasAlign(AlignTop)) {
						float32_t offset = (scale_y - scale) * getElementRect().getHeight();
						position.y += offset;
						rect.bottom += offset;
					} else if(hasAlign(AlignCenterY)) {
						float32_t offset = floor((scale_y - scale) * getElementRect().getHeight() * 0.5f + 0.5f);
						position.y += offset;
						rect.bottom += offset;
						rect.top -= offset;
					} else {
						rect.top -= (scale_y - scale) * getElementRect().getHeight();
					}
				}
				scale_x = scale;
				scale_y = scale;
			}
			setOffset(position);
		}
		
		// control state
		State old_state = getState();
		if(!get_disabled(root)) {
			Rect state_rect = rect + getInputMargin();
			if(!root.getCurrentControl() || root.getCurrentControl() == *this) {
				if(state_rect.inside(root.getMouse()) && view.inside(root.getMouse())) {
					if((pressed_func || clicked_func) && (root.getMouseButtons() & (ButtonLeft | ButtonLeft2))) {
						click_mode = 1;
						set_state(root, StatePressed);
						if(clicked2_func && (root.getMouseButtons() & ButtonLeft2)) click_mode = 2;
						if(pressed_func) pressed_func(this, root.getMouseX() - position.x, root.getMouseY() - position.y);
						is_pressed = true;
					} else if(root.getMouseButtons() & ButtonRight) {
						root.setCurrentControl(*this);
						click_mode = 3;
					} else {
						if(set_state(root, StateFocused) == StatePressed) {
							if(click_mode == 1 && clicked_func) clicked_func(this);
							if(click_mode == 2 && clicked2_func) clicked2_func(this);
							if(released_func) released_func(this, root.getMouseX() - position.x, root.getMouseY() - position.y);
							is_clicked = true;
							is_released = true;
						} else if(click_mode == 3) {
							if(clickedr_func) clickedr_func(this);
						}
						click_mode = 0;
					}
				} else if(root.getCurrentControl() == *this) {
					if(root.getMouseButtons() & (ButtonLeft | ButtonLeft2)) {
						if(pressed_func) pressed_func(this, root.getMouseX() - position.x, root.getMouseY() - position.y);
						is_pressed = true;
					}
				} else if(!root.getCurrentControl()) {
					if(set_state(root, StateNormal) == StatePressed) {
						if(released_func) released_func(this, root.getMouseX() - position.x, root.getMouseY() - position.y);
						is_released = true;
					}
					click_mode = 0;
				}
			} else {
				set_state(root, StateNormal);
				click_mode = 0;
			}
		} else {
			set_state(root, StateDisabled);
			click_mode = 0;
		}
		if(old_state != getState()) {
			if(state_func) state_func(this, getState());
			update_enabled(isEnabled());
			ret = true;
		}
		
		// update element
		if(element) {
			Matrix4x4f transform;
			if(!hasAlign(AlignOverlap)) {
				if(has_scale) {
					Vector2f offset = getElementRect().getCenter() + (rect.getSize() - getElementRect().getSize()) * 0.5f;
					transform = Matrix4x4f::translate(position + Vector3f(Vector3f(offset, 0.0f)));
					transform *= Matrix4x4f::scale(scale_x, scale_y, 1.0f);
					transform *= Matrix4x4f::translate(Vector3f(-getElementRect().getCenter() + offsets[StateUnknown] + offsets[getState()], 0.0f));
				} else {
					Vector2f offset = Vector2f(getMargin().left, getMargin().bottom) + offsets[StateUnknown] + offsets[getState()];
					transform = Matrix4x4f::translate(position + Vector3f(Vector3f(offset, 0.0f)));
				}
			} else {
				Vector2f offset = offsets[StateUnknown] + offsets[getState()];
				transform = Matrix4x4f::translate(position + Vector3f(Vector3f(offset, 0.0f)));
			}
			if(colors[getState()]) element.setColor(colors[getState()] * getColor());
			else element.setColor(root.getTextColor(getType(), getState()) * getColor());
			element.setTransform(transform);
		}
		
		return ret;
	}
}

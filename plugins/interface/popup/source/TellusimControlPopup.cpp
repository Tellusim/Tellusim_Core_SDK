// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimTime.h>

#include "../include/TellusimControlPopup.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	ControlPopup::ControlPopup(Control *parent) : ControlBase(parent) {
		
		// root control
		ControlRoot root = getRoot();
		uint32_t font_size = root.getFontSize() + 4;
		
		// popup parameters
		radius = (float32_t)font_size * 0.5f;
		color = Color(0.12f, 1.0f);
		
		getParent().lowerChild(*this);
	}
	
	ControlPopup::~ControlPopup() {
		
	}
	
	/*
	 */
	void ControlPopup::setRadius(float32_t r) {
		radius = r;
	}
	
	void ControlPopup::setColor(const Color &c) {
		color = c;
	}
	
	void ControlPopup::setSpacing(const Vector2f &s) {
		spacing = s;
	}
	
	void ControlPopup::setStrokeStyle(const StrokeStyle &style) {
		stroke_style = style;
	}
	
	void ControlPopup::setGradientStyle(const GradientStyle &style) {
		gradient_style = style;
	}
	
	void ControlPopup::setSpacing(float32_t x, float32_t y) {
		spacing.set(x, y);
	}
	
	/*
	 */
	void ControlPopup::closePopups() {
		close_popups = true;
	}
	
	void ControlPopup::clearPopups() {
		callbacks.clear();
	}
	
	void ControlPopup::removePopup(const Control &control, bool hierarchy) {
		callbacks.remove(control);
		if(hierarchy) {
			for(const Control &child : control.getChildren()) {
				removePopup(child, hierarchy);
			}
		}
	}
	
	void ControlPopup::addPopup(const Control &control, const PopupCallback &func) {
		callbacks.append(control, func);
	}
	
	void ControlPopup::addPopup(const Vector2f &position, const PopupCallback &func) {
		Popup &popup = popups.append();
		popup.panel = create_panel(Control::null, position, 1.0f, func);
		popup.control = popup.panel;
		popup.time = Time::current();
		close_popups = false;
	}
	
	/*
	 */
	ControlPanel ControlPopup::create_panel(const Control &control, const Vector2f &position, float32_t scale, const PopupCallback &func) {
		
		// create popup panel at local root
		Control parent = (control) ? control.getRoot(true) : getRoot(true);
		ControlPanel popup_panel = ControlPanel(&parent);
		popup_panel.setCallback(true);
		
		// popup size
		popup_panel.setRadius(getRadius());
		popup_panel.setMargin(getRadius());
		popup_panel.setSpacing(getSpacing());
		
		// popup style
		popup_panel.setColor(getColor());
		popup_panel.setStrokeStyle(getStrokeStyle());
		popup_panel.setGradientStyle(getGradientStyle());
		
		// popup callback
		Align align = func(control, popup_panel);
		
		// popup layout
		Vector3f popup_position = Vector3f(position, 0.0f);
		Align popup_align = Control::AlignOverlap | Control::AlignLocal;
		Rect rect = (control) ? control.getRect() : Rect(0.0f);
		if(align & AlignTop) {
			popup_position.y += rect.top;
			popup_align |= AlignBottom;
		} else if(align & AlignBottom) {
			popup_position.y += rect.bottom;
			popup_align |= AlignTop;
		} else if(align & AlignCenterY) {
			popup_position.y += rect.getCenterY();
			popup_align |= AlignCenterY;
		}
		if(align & AlignLeft) {
			popup_position.x += rect.left;
			popup_align |= AlignRight;
		} else if(align & AlignRight) {
			popup_position.x += rect.right;
			popup_align |= AlignLeft;
		} else if(align & AlignCenterX) {
			popup_position.x += rect.getCenterX();
			popup_align |= AlignCenterX;
		}
		popup_position = popup_panel.getPosition() + popup_position * scale;
		popup_panel.setPosition(popup_position);
		popup_panel.setAlign(popup_align);
		
		return popup_panel;
	}
	
	/*
	 */
	bool ControlPopup::clear_popups(const Control &control) {
		
		bool ret = false;
		
		// check popups
		if(popups) {
			
			// current time
			uint64_t time = Time::current();
			uint64_t delay = Time::Seconds / 8;
			
			// remove inactive popups
			for(uint32_t i = popups.size(); i > 0; i--) {
				Popup &popup = popups[i - 1];
				if(!close_popups && (popup.control == control || popup.panel == control || popup.panel.isChild(control, true))) {
					popup.time = time;
				} else if(close_popups || time - popup.time > delay) {
					if(i < popups.size() && popup.panel.isChild(popups[i].control, true)) continue;
					Control parent = popup.panel.getParent();
					parent.removeChild(popup.panel);
					popup.panel.setEnabled(false);
					removePopup(popup.panel);
					popup.control.clearPtr();
					popup.panel.clearPtr();
					popups.remove(i - 1);
					ret = true;
				}
			}
			
			// raise popups
			for(Popup &popup : popups) {
				Control parent = popup.panel.getParent();
				parent.raiseChild(popup.panel);
			}
		}
		
		// clear flags
		close_popups = false;
		
		return ret;
	}
	
	/*
	 */
	bool ControlPopup::update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale) {
		
		bool ret = false;
		
		// check focused control
		Control focused_control = root.getFocusedControl();
		if(!focused_control) {
			focused_control = root.getCurrentControl();
			if(!focused_control) {
				if(root.getMouseButtons()) {
					ret |= clear_popups(focused_control);
				}
				return ret;
			}
		}
		
		// focused control offset
		float32_t area_iscale = 1.0f;
		Control parent = focused_control.getParent();
		Vector2f focused_offset = focused_control.getOffset().xy;
		while(parent) {
			if(parent.isArea()) {
				ControlArea area = ControlArea(parent);
				if(area.isAbsolute()) focused_offset += area.getControlsOffset();
				area_iscale = 1.0f / area.getScale();
			}
			parent = parent.getParent();
		}
		
		// update popup
		Vector2f mouse_position = root.getMouse();
		Control current_control = root.getCurrentControl();
		if(focused_control.getRect().inside(mouse_position * area_iscale - focused_offset) && (!current_control || current_control == focused_control)) {
			uint64_t time = Time::current();
			auto it = callbacks.find(focused_control);
			if(it && !root.getMouseButtons() && popup_control == focused_control) {
				bool is_popup = false;
				for(const Popup &popup : popups) {
					if(popup.control == focused_control) {
						is_popup = true;
						break;
					}
				}
				if(!is_popup && time - popup_time > Time::Seconds / 16) {
					for(Popup &popup : popups) {
						popup.time = 0;
					}
					Popup &popup = popups.append();
					popup.control = focused_control;
					popup.panel = create_panel(focused_control, focused_offset, 1.0f / area_iscale, it->data);
					popup.time = Time::current();
					ret = true;
				}
				clear_popups(focused_control);
			} else {
				ret |= clear_popups(focused_control);
				popup_control = focused_control;
				popup_time = time;
			}
		}
		else {
			ret |= clear_popups(focused_control);
			popup_control = Control::null;
			popup_time = 0;
		}
		
		return ret;
	}
}

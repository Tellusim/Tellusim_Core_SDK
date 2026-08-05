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
		create();
	}
	
	ControlPopup::~ControlPopup() {
		
	}
	
	/*
	 */
	void ControlPopup::create() {
		
		ControlRoot root = getRoot();
		
		// default parameters
		update_style(root.getFontStyle());
		setColor(Color(0.12f, 0.12f, 0.12f, 1.0f));
		setItemColor(Color(0.2f, 0.3f, 0.4f, 0.9f));
		setSpacing(1.0f, 1.0f);
		
		// lower control
		getParent().lowerChild(*this);
		
		ControlBase::create();
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
	void ControlPopup::setItemColor(const Color &c) {
		item_color = c;
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
		Control parent = getRoot(true);
		addPopup(&parent, position, func);
	}
	
	void ControlPopup::addPopup(Control *parent, const Vector2f &position, const PopupCallback &func) {
		Popup &popup = popups.append();
		popup.panel = create_panel(parent, Control::null, position, 1.0f, func);
		popup.control = popup.panel;
		popup.time = Time::current();
		close_popups = false;
	}
	
	/*
	 */
	void ControlPopup::createItem(ControlPanel &popup_panel, const char *text, const ClickedCallback &func, const String &key) {
		
		// popup item
		ControlPanel panel = create_item(&popup_panel);
		panel.setColumns(2);
		
		// item text
		ControlText item_text(&panel, text);
		item_text.setAlign(Control::AlignLeft | Control::AlignExpandX);
		
		// item hotkey
		if(key) {
			ControlText key_text(&panel, key);
			key_text.setFontColor(Color::gray);
			key_text.setAlign(Control::AlignRight);
			key_text.setMargin(getRadius() * 2.0f, 0.0f, 0.0f, 0.0f);
		}
		
		// item callback
		panel.setClickedCallback(makeFunction([this](ControlRect rect, ClickedCallback func) {
			closePopups();
			func.run();
		}, ControlRect::null, func));
	}
	
	void ControlPopup::createItem(ControlPanel &popup_panel, const String &text, const ClickedCallback &func, const String &key) {
		createItem(popup_panel, text.get(), func, key);
	}
	
	/*
	 */
	void ControlPopup::createItem(ControlPanel &popup_panel, const char *text, const char *texture, const Rect &texcoord, const ClickedCallback &func, const String &key) {
		
		// popup item
		ControlPanel panel = create_item(&popup_panel);
		panel.setColumns(3);
		
		// item image
		ControlRect item_rect(&panel, texture);
		float32_t margin = floor(getRadius() * 0.5f);
		item_rect.setMargin(-margin, margin, -margin, -margin);
		item_rect.setSize(getRadius() * 2.0f, getRadius() * 2.0f);
		item_rect.setBlend(Pipeline::BlendOpAdd, Pipeline::BlendFuncSrcAlpha, Pipeline::BlendFuncInvSrcAlpha);
		item_rect.setTextureScale(0.0f, 0.0f);
		item_rect.setTexCoord(texcoord);
		
		// item text
		ControlText item_text(&panel, text);
		item_text.setAlign(Control::AlignLeft | Control::AlignExpandX | Control::AlignCenterY);
		
		// item hotkey
		if(key) {
			ControlText key_text(&panel, key);
			key_text.setFontColor(Color::gray);
			key_text.setAlign(Control::AlignRight);
			key_text.setMargin(getRadius() * 2.0f, 0.0f, 0.0f, 0.0f);
		}
		
		// item callback
		panel.setClickedCallback(makeFunction([this](ControlRect rect, ClickedCallback func) {
			closePopups();
			func.run();
		}, ControlRect::null, func));
	}
	
	void ControlPopup::createItem(ControlPanel &popup_panel, const String &text, const char *texture, const Rect &texcoord, const ClickedCallback &func, const String &key) {
		createItem(popup_panel, text.get(), texture, texcoord, func, key);
	}
	
	/*
	 */
	void ControlPopup::createItem(ControlPanel &popup_panel, const char *text, bool checked, const ChangedCallback &func, const String &key) {
		
		// popup item
		ControlPanel panel = create_item(&popup_panel);
		panel.setColumns(3);
		
		// check text
		ControlText check_text(&panel, (checked) ? "&#10004;" : "");
		check_text.setAlign(Control::AlignLeft);
		check_text.setSize(getRadius() * 2.0f, 0.0f);
		
		// item text
		ControlText item_text(&panel, text);
		item_text.setAlign(Control::AlignLeft | Control::AlignExpandX);
		
		// item hotkey
		if(key) {
			ControlText key_text(&panel, key);
			key_text.setFontColor(Color::gray);
			key_text.setAlign(Control::AlignRight);
			key_text.setMargin(getRadius() * 2.0f, 0.0f, 0.0f, 0.0f);
		}
		
		// item callback
		panel.setClickedCallback(makeFunction([this](ControlRect rect, ChangedCallback func, bool checked) {
			closePopups();
			func.run(!checked);
		}, ControlRect::null, func, checked));
	}
	
	void ControlPopup::createItem(ControlPanel &popup_panel, const String &text, bool checked, const ChangedCallback &func, const String &key) {
		createItem(popup_panel, text.get(), checked, func, key);
	}
	
	/*
	 */
	void ControlPopup::createItemPopup(ControlPanel &popup_panel, const char *text, const PopupCallback &func) {
		
		// popup item
		ControlPanel panel = create_item(&popup_panel);
		panel.setColumns(2);
		
		// item text
		ControlText item_text(&panel, text);
		item_text.setAlign(Control::AlignLeft | Control::AlignExpandX);
		
		// arrow text
		ControlText arrow_text(&panel, "&#9654;");
		arrow_text.setAlign(Control::AlignRight);
		arrow_text.setMargin(getRadius() * 2.0f, 0.0f, 0.0f, 0.0f);
		
		// create popup
		addPopup(panel, makeFunction([this](ControlPanel panel, PopupCallback func) {
			panel.setPosition(0.0f, floor(getRadius() * 3.75f));
			return func(panel);
		}, ControlPanel::null, func));
	}
	
	void ControlPopup::createItemPopup(ControlPanel &popup_panel, const String &text, const PopupCallback &func) {
		createItemPopup(popup_panel, text.get(), func);
	}
	
	/*
	 */
	void ControlPopup::createItemSeparator(ControlPanel &popup_panel) const {
		
		// check the last child
		uint32_t num_children = popup_panel.getNumChildren();
		if(num_children && popup_panel.getChild(num_children - 1).isRect()) return;
		
		// root parameters
		const ControlRoot root = getRoot();
		Color color = root.getFontStyle().color;
		
		// create line
		ControlRect rect(&popup_panel);
		rect.setSize(1.0f, 1.0f);
		rect.setAlign(Control::AlignExpandX);
		rect.setMargin(0.0f, floor(getRadius() * 0.5f));
		rect.setColor(color);
	}
	
	/*
	 */
	ControlPanel ControlPopup::create_panel(Control *parent, const Control &control, const Vector2f &position, float32_t scale, const PopupCallback &func) const {
		
		// create popup panel at local root
		ControlPanel popup_panel = ControlPanel(parent);
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
		Align align = func(popup_panel);
		
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
	
	ControlPanel ControlPopup::create_item(Control *parent) const {
		
		// create item panel
		ControlPanel item_panel = ControlPanel(parent);
		item_panel.setCallback(true);
		
		// item size
		item_panel.setAlign(Control::AlignExpandX);
		item_panel.setRadius(floor(getRadius() * 0.5f));
		item_panel.setMargin(getRadius(), floor(getRadius() * 0.75f));
		
		// item color
		item_panel.setColor(Color(0.2f, 0.3f, 0.4f, 0.9f));
		item_panel.setStateColor(Control::StateNormal, Color(1.0f, 0.0f));
		item_panel.setStateColor(Control::StateFocused, Color(1.0f, 1.0f));
		item_panel.setStateColor(Control::StatePressed, Color(1.0f, 1.0f));
		
		return item_panel;
	}
	
	/*
	 */
	bool ControlPopup::clear_popups(ControlRoot &root, const Control &control) {
		
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
				} else if(close_popups || ((popups.size() > 1 || root.getMouseButtons()) && time - popup.time > delay)) {
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
	void ControlPopup::update_style(const FontStyle &style) {
		uint32_t font_size = style.size + 4;
		setRadius(floor(font_size * 0.5f));
	}
	
	bool ControlPopup::update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale) {
		
		bool ret = false;
		
		// check focused control
		Control focused_control = root.getFocusedControl();
		if(!focused_control) {
			focused_control = root.getCurrentControl();
			if(!focused_control) {
				if(close_popups || root.getMouseButtons()) {
					ret |= clear_popups(root, focused_control);
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
					ControlRoot focused_root = focused_control.getRoot(true);
					popup.panel = create_panel(&focused_root, focused_control, focused_offset, 1.0f / area_iscale, it->data);
					popup.time = Time::current();
					ret = true;
				}
				clear_popups(root, focused_control);
			} else {
				ret |= clear_popups(root, focused_control);
				popup_control = focused_control;
				popup_time = time;
			}
		}
		else {
			ret |= clear_popups(root, focused_control);
			popup_control = Control::null;
			popup_time = 0;
		}
		
		// clear mouse align
		if(popups) root.setMouseAlign(Control::AlignNone);
		
		return ret;
	}
}

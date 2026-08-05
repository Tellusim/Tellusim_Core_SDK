// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimTime.h>

#include "../include/TellusimControlTooltip.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	ControlTooltip::ControlTooltip(Control *parent) : ControlBase(parent) {
		tooltip_position = Vector2f::zero;
		create();
	}
	
	ControlTooltip::~ControlTooltip() {
		
	}
	
	/*
	 */
	void ControlTooltip::create() {
		
		ControlRoot root = getRoot();
		
		// create canvas mesh
		Canvas canvas = getCanvas();
		canvas_rect = CanvasRect(canvas);
		canvas_text = create_text();
		canvas_mesh = CanvasMesh(canvas);
		canvas_mesh.addVertex(0.0f, 0.0f);
		canvas_mesh.addVertex(0.0f, 0.0f);
		canvas_mesh.addVertex(0.0f, 0.0f);
		canvas_mesh.addVertex(0.0f, 0.0f);
		canvas_mesh.setVertexTexCoord(0, 0.0f, 1.0f);
		canvas_mesh.setVertexTexCoord(1, 1.0f, 1.0f);
		canvas_mesh.setVertexTexCoord(2, 1.0f, 0.0f);
		canvas_mesh.setVertexTexCoord(3, 0.0f, 0.0f);
		canvas_mesh.addIndices(0, 1, 2);
		canvas_mesh.addIndices(2, 3, 0);
		
		// default parameters
		update_style(root.getFontStyle());
		setColor(Color(0.2f, 0.3f, 0.4f, 0.9f));
		
		// lower control
		getParent().lowerChild(*this);
		
		ControlBase::create();
	}
	
	/*
	 */
	void ControlTooltip::setOffset(float32_t o) {
		offset = o;
	}
	
	void ControlTooltip::setRadius(float32_t radius) {
		canvas_rect.setRadius(radius);
	}
	
	void ControlTooltip::setColor(const Color &color) {
		canvas_rect.setColor(color);
	}
	
	/*
	 */
	void ControlTooltip::clearTooltips() {
		tooltips.clear();
		text_callbacks.clear();
		draw_callbacks.clear();
	}
	
	void ControlTooltip::removeTooltip(const Control &control, bool hierarchy) {
		tooltips.remove(control);
		text_callbacks.remove(control);
		draw_callbacks.remove(control);
		if(hierarchy) {
			for(const Control &child : control.getChildren()) {
				removeTooltip(child, hierarchy);
			}
		}
	}
	
	void ControlTooltip::addTooltip(const Control &control, const char *text) {
		tooltips.append(control, String(text));
	}
	
	void ControlTooltip::addTooltip(const Control &control, const String &text) {
		tooltips.append(control, text);
	}
	
	void ControlTooltip::addTooltip(const Control &control, const TextCallback &func) {
		text_callbacks.append(control, func);
	}
	
	void ControlTooltip::addTooltip(const Control &control, const DrawCallback &func) {
		draw_callbacks.append(control, func);
	}
	
	/*
	 */
	void ControlTooltip::update_enabled(bool enabled) {
		enabled &= isEnabled();
		canvas_rect.setEnabled(enabled);
		canvas_text.setEnabled(enabled);
		canvas_mesh.setEnabled(enabled);
		ControlBase::update_enabled(enabled);
	}
	
	void ControlTooltip::update_style(const FontStyle &style) {
		uint32_t font_size = style.size + 4;
		setRadius(floor(font_size * 0.5f));
	}
	
	bool ControlTooltip::update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale) {
		
		// disable canvas
		Control focused_control = root.getFocusedControl();
		if(canvas_rect.isEnabled()) {
			if((Time::current() - tooltip_time > Time::Seconds / 2 || root.getMouseButtons()) || (focused_control && focused_control.isTree())) {
				canvas_rect.setEnabled(false);
				canvas_text.setEnabled(false);
				canvas_mesh.setEnabled(false);
			}
		}
		
		// update font scale
		canvas_text.setFontScale(scale);
		
		// check focused control
		Vector2f mouse_position = root.getMouse();
		if(!focused_control) {
			if(tooltip_control) {
				canvas_rect.setEnabled(false);
				canvas_text.setEnabled(false);
				canvas_mesh.setEnabled(false);
			}
			tooltip_control = Control::null;
			tooltip_position = mouse_position;
			return false;
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
		
		// update tooltip
		Control current_control = root.getCurrentControl();
		if(focused_control.getRect().inside(mouse_position * area_iscale - focused_offset) && (!current_control || current_control == focused_control)) {
			
			uint64_t time = Time::current();
			float32_t control_height = 0.0f;
			auto text_it = text_callbacks.find(focused_control);
			auto draw_it = draw_callbacks.find(focused_control);
			float32_t tooltip_distance = (text_it || draw_it) ? Maxf32 : 1.0f;
			if((text_it || draw_it || tooltip_control == focused_control) && length(tooltip_position - mouse_position) < tooltip_distance && !root.getMouseButtons()) {
				
				auto tooltip_it = tooltips.find(focused_control);
				uint64_t tooltip_delay = (text_it || draw_it) ? 0 : Time::Seconds / 4;
				if((text_it || draw_it || tooltip_it) && time - tooltip_time >= tooltip_delay) {
					
					String text;
					if(tooltip_it) text = tooltip_it->data;
					if(text_it) text = text_it->data(focused_control, &mouse_position, &control_height);
					if(draw_it) text = draw_it->data(focused_control, canvas_mesh, &mouse_position, &control_height);
					if(text || draw_it) {
						
						Rect rect;
						
						// tooltip rectangle
						if(text) {
							canvas_text.setText(text);
							Rect text_rect = canvas_text.getRect() - canvas_text.getPosition().xy;
							if(text_rect) {
								if(rect) {
									rect.right += max(text_rect.getWidth() - rect.getWidth(), 0.0f);
									rect.top += text_rect.getHeight() + floor(root.getFontSize() * 0.5f);
								} else {
									rect = text_rect;
								}
							} else {
								text.clear();
							}
						}
						if(draw_it) {
							Rect mesh_rect = canvas_mesh.getRect() - mouse_position;
							if(mesh_rect) {
								if(rect) {
									rect.right += max(mesh_rect.getWidth() - rect.getWidth(), 0.0f);
									rect.top += mesh_rect.getHeight() + 4.0f;
								} else {
									rect = mesh_rect;
								}
							} else {
								draw_it.clear();
							}
						}
						
						// tooltip position
						Vector2f position = mouse_position + Vector2f(0.0f, -getOffset());
						Rect tooltip_rect = rect + Vector2f(position - Vector2f(rect.getCenterX(), rect.top)) + Rect(getRadius());
						if(tooltip_rect.left < view.left) {
							tooltip_rect.right += view.left - tooltip_rect.left;
							position.x += view.left - tooltip_rect.left;
						}
						if(tooltip_rect.right > view.right) position.x -= tooltip_rect.right - view.right;
						if(tooltip_rect.bottom < view.bottom) position.y += tooltip_rect.getHeight() + getOffset() + getRadius() + control_height;
						
						// update rect, tooltip must be over than overlay
						int32_t order = root.getOverlayOrder() * 4;
						canvas_rect.setEnabled(true);
						canvas_rect.setOrder(order++);
						canvas_rect.setPosition(floor(position.x + 0.5f), floor(position.y - rect.getHeight() * 0.5f + 0.5f));
						canvas_rect.setSize(rect.getWidth() + getRadius() * 2.0f, rect.getHeight() + getRadius() * 2.0f);
						
						// tooltip elements
						if(text) {
							canvas_text.setEnabled(true);
							canvas_text.setOrder(order++);
							Rect text_rect = canvas_text.getRect();
							canvas_text.setFontSize(root.getFontSize());
							canvas_text.setPosition(floor(position.x - text_rect.getWidth() * 0.5f + 0.5f), floor(position.y - rect.bottom - text_rect.getHeight() + 0.5f));
						} else {
							canvas_text.setEnabled(false);
						}
						if(draw_it) {
							canvas_mesh.setEnabled(true);
							canvas_mesh.setOrder(order++);
							Rect mesh_rect = canvas_mesh.getRect();
							mesh_rect += Vector2f(floor(position.x - mesh_rect.getWidth() * 0.5f + 0.5f), floor(position.y - rect.getHeight() + 0.5f));
							canvas_mesh.setVertexPosition(0, mesh_rect.left, mesh_rect.bottom);
							canvas_mesh.setVertexPosition(1, mesh_rect.right, mesh_rect.bottom);
							canvas_mesh.setVertexPosition(2, mesh_rect.right, mesh_rect.top);
							canvas_mesh.setVertexPosition(3, mesh_rect.left, mesh_rect.top);
						} else {
							canvas_mesh.setEnabled(false);
						}
					}
					tooltip_time = time - tooltip_delay;
					is_tooltip = false;
				}
				else {
					is_tooltip = (text_it || draw_it || tooltip_it);
				}
			}
			else {
				if(tooltip_control != focused_control) {
					canvas_rect.setEnabled(false);
					canvas_text.setEnabled(false);
					canvas_mesh.setEnabled(false);
				}
				tooltip_control = focused_control;
				tooltip_position = mouse_position;
				tooltip_time = time;
				is_tooltip = false;
			}
		}
		else {
			if(tooltip_control) {
				canvas_rect.setEnabled(false);
				canvas_text.setEnabled(false);
				canvas_mesh.setEnabled(false);
			}
			tooltip_control = Control::null;
			tooltip_position = mouse_position;
			tooltip_time = 0;
			is_tooltip = false;
		}
		
		return false;
	}
}

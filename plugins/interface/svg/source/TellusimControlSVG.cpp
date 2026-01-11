// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimStream.h>
#include <format/TellusimXml.h>

#include "../include/TellusimControlSVG.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	ControlSVG::ControlSVG(Control *parent) : ControlBase(parent) {
		ControlBase::create();
	}
	
	ControlSVG::ControlSVG(Control *parent, float32_t threshold) : ControlSVG(parent) {
		setThreshold(threshold);
	}
	
	ControlSVG::~ControlSVG() {
		
	}
	
	/*
	 */
	void ControlSVG::clear_shapes() {
		Canvas canvas = getCanvas();
		for(CanvasShape &shape : shapes) {
			canvas.removeElement(shape);
		}
		gradients.clear();
		names.clear();
		shapes.release();
		svg_rect = Rect(0.0f);
	}
	
	/*
	 */
	bool ControlSVG::loadSVG(Stream &stream) {
		Xml xml;
		if(!xml.load(stream) || !createSVG(xml)) {
			TS_LOGF(Error, "ControlSVG::loadSVG(): can't load \"%s\" file\n", stream.getName().get());
			return false;
		}
		return true;
	}
	
	bool ControlSVG::loadSVG(const char *name) {
		Xml xml;
		if(!xml.load(name) || !createSVG(xml)) {
			TS_LOGF(Error, "ControlSVG::loadSVG(): can't load \"%s\" file\n", name);
			return false;
		}
		return true;
	}
	
	bool ControlSVG::loadSVG(const String &name) {
		Xml xml;
		if(!xml.load(name) || !createSVG(xml)) {
			TS_LOGF(Error, "ControlSVG::loadSVG(): can't load \"%s\" file\n", name.get());
			return false;
		}
		return true;
	}
	
	/*
	 */
	bool ControlSVG::createSVG(const Xml &root) {
		
		// clear shapes
		clear_shapes();
		
		// check xml type
		if(root.getName() != "svg") {
			TS_LOGF(Error, "ControlSVG::createSVG(): invalid root node %s\n", root.getName().get());
			return false;
		}
		
		// view box
		float32_t box[4] = {};
		if(root.getAttribute("viewBox", box, 4)) {
			svg_rect = Rect(box[0], box[0] + box[2], box[1], box[1] + box[3]);
		}
		
		// default group
		Group group;
		group.transform = Matrix4x3f::identity;
		group.color = Color::black;
		
		// create transform shape
		Canvas canvas = getCanvas();
		shapes.append(CanvasShape(canvas));
		
		// load SVG groups
		for(const Xml &xml : root.getChildren()) {
			const String &name = xml.getName();
			if(name == "metadata") continue;
			if(name == "defs") create_defs(xml);
			else if(name == "g") create_group(xml, group);
			else if(name == "path") create_path(xml, group);
			else TS_LOGF(Warning, "ControlSVG::createSVG(): unknown element %s\n", name.get());
		}
		
		// create restore shape
		shapes.append(CanvasShape(canvas));
		
		// transform shapes and styles
		for(CanvasShape &shape : shapes) {
			
			// transform shapes
			uint32_t num_positions = shape.getNumPositions();
			Vector3f *positions = shape.getPositions();
			Matrix4x4f transform = shape.getTransform();
			for(uint32_t i = 0; i < num_positions; i++) {
				positions[i] = transform * positions[i];
			}
			shape.clearTransform();
			
			// transform stroke style
			float32_t scale = length(transform.getScale().xy);
			StrokeStyle &style = shape.getStrokeStyle();
			style.width *= scale;
			style.offset *= scale;
			
			// transform gradient style
			GradientStyle &gradient = shape.getGradientStyle();
			gradient.center = transform * gradient.center;
			gradient.axis = transform * gradient.axis;
		}
		
		// SVG rect
		if(!svg_rect) {
			for(CanvasShape &shape : shapes) {
				svg_rect.expand(shape.getRect());
			}
		}
		
		// normalize rect
		float32_t scale = 1.0f;
		if(getHeight() > 0.0f && svg_rect.getHeight() > 0.0f) scale = getHeight() / svg_rect.getHeight();
		Matrix4x4f transform = Matrix4x4f::scale(scale, scale, 1.0f) * Matrix4x4f::translate(-svg_rect.left, -svg_rect.bottom, 0.0f);
		svg_rect = transform * svg_rect;
		
		// transform shapes and styles
		float32_t height = svg_rect.getHeight();
		for(CanvasShape &shape : shapes) {
			
			// transform shapes
			Vector3f *positions = shape.getPositions();
			uint32_t num_positions = shape.getNumPositions();
			for(uint32_t i = 0; i < num_positions; i++) {
				positions[i] = transform * positions[i];
				positions[i].y = height - positions[i].y;
			}
			
			// transform stroke style
			StrokeStyle &style = shape.getStrokeStyle();
			style.width *= scale;
			style.offset *= scale;
			
			// transform gradient style
			GradientStyle &gradient = shape.getGradientStyle();
			gradient.center = transform * gradient.center;
			gradient.center.y = height - gradient.center.y;
			gradient.axis = transform * gradient.axis;
			gradient.axis.y = height - gradient.axis.y;
			
			// create gradient parameters
			if(shape.getMode() == CanvasElement::ModeGradient) {
				if(gradient.length > 0.0f) {
					gradient.length = length2(gradient.axis - gradient.center);
					gradient.axis = gradient.axis - gradient.center;
				}
				if(gradient.radius > 0.0f) {
					gradient.radius = length(gradient.axis - gradient.center);
				}
				shape.setTexCoord(Rect(0.0f, 1.0f, 0.0f, 1.0f));
			}
		}
		
		return true;
	}
	
	/*
	 */
	Matrix4x3f ControlSVG::get_transform(const String &src) {
		float32_t m[6];
		Matrix4x3f transform;
		if(src.scanf("matrix(%f %f %f %f %f %f)", &m[0], &m[1], &m[2], &m[3], &m[4], &m[5]) == 6 ||
			src.scanf("matrix(%f,%f,%f,%f,%f,%f)", &m[0], &m[1], &m[2], &m[3], &m[4], &m[5]) == 6) {
			transform = Matrix4x3f(m, 6, false);
		}
		else if(src.scanf("translate(%f %f)", &m[0], &m[1]) == 2 ||
			src.scanf("translate(%f,%f)", &m[0], &m[1]) == 2) {
			transform = Matrix4x3f::translate(m[0], m[1], 0.0f);
		}
		else if(src.scanf("translate(%f)", &m[0]) == 1) {
			transform = Matrix4x3f::translate(m[0], 0.0f, 0.0f);
		}
		else if(src.scanf("rotate(%f)", &m[0]) == 1) {
			transform = Matrix4x3f::rotateZ(m[0]);
		}
		else if(src.scanf("scale(%f %f)", &m[0], &m[1]) == 2 ||
			src.scanf("scale(%f,%f)", &m[0], &m[1]) == 2) {
			transform = Matrix4x3f::scale(m[0], m[1], 1.0f);
		}
		else {
			TS_LOGF(Warning, "ControlSVG::get_transform(): unknown transform \"%s\"\n", src.get());
			transform = Matrix4x3f::identity;
		}
		uint32_t pos = src.find(')');
		if(pos != Maxu32 && src.find('(', pos) != Maxu32) {
			return transform * get_transform(src.substring(pos + 1));
		}
		return transform;
	}
	
	/*
	 */
	bool ControlSVG::create_defs(const Xml &xml) {
		
		for(const Xml &child : xml.getChildren()) {
			const String &name = child.getName();
			if(name == "linearGradient" || name == "radialGradient") {
				GradientStyle gradient;
				gradient.color_0 = Color::zero;
				gradient.color_1 = Color::zero;
				if(child.isAttribute("xlink:href")) {
					auto it = gradients.find(child.getAttribute("xlink:href"));
					if(it) {
						if(it->data.color_0) gradient.color_0 = it->data.color_0;
						if(it->data.color_1) gradient.color_1 = it->data.color_1;
					}
				}
				if(name == "linearGradient") {
					gradient.center.x = child.getAttribute("x1", 0.0f);
					gradient.center.y = child.getAttribute("y1", 0.0f);
					gradient.axis.x = child.getAttribute("x2", 1.0f);
					gradient.axis.y = child.getAttribute("y2", 1.0f);
					gradient.length = length(gradient.axis - gradient.center);
				} else if(name == "radialGradient") {
					gradient.center.x = child.getAttribute("cx", 0.5f);
					gradient.center.y = child.getAttribute("cy", 0.5f);
					gradient.radius = child.getAttribute("r", 0.5f);
					gradient.axis = gradient.center + Vector2f(0.0f, gradient.radius);
				} else {
					TS_ASSERT(0 && "ControlSVG::create_defs(): unknown gradient");
				}
				uint32_t index = 0;
				for(const Xml &stop : child.getChildren()) {
					const String &name = stop.getName();
					if(name != "stop") continue;
					if(index == 0) {
						String color = stop.getAttribute("stop-color");
						if(color) gradient.color_0 = Color(color.get());
						gradient.color_0.a = stop.getAttribute("stop-opacity", 1.0f);
					} else if(index == 1) {
						String color = stop.getAttribute("stop-color");
						if(color) gradient.color_1 = Color(color.get());
						gradient.color_1.a = stop.getAttribute("stop-opacity", 1.0f);
					} else {
						TS_LOG(Warning, "ControlSVG::create_defs(): only two gradient colors are supported\n");
						break;
					}
					index++;
				}
				if(child.isAttribute("gradientTransform")) {
					Matrix4x3f transform = get_transform(child.getAttribute("gradientTransform"));
					gradient.center = transform * gradient.center;
					gradient.axis = transform * gradient.axis;
				}
				if(!gradient.color_0) gradient.color_0 = Color::black;
				if(!gradient.color_1) gradient.color_1 = Color::black;
				String id = child.getAttribute("id");
				if(id) {
					gradients.append(String::format("#%s", id.get()), gradient);
					gradients.append(String::format("url(#%s)", id.get()), gradient);
				}
			}
			else {
				TS_LOGF(Warning, "ControlSVG::create_defs(): unknown element %s\n", name.get());
			}
		}
		
		return true;
	}
	
	/*
	 */
	bool ControlSVG::create_style(const Xml &xml, Group &group) {
		
		// get style
		String style = xml.getAttribute("style");
		
		// inline color
		uint32_t color = style.find("fill:");
		if(color != Maxu32) group.color = Color(style.substring(color + 5).get());
		
		return true;
	}
	
	/*
	 */
	bool ControlSVG::create_group(const Xml &xml, Group group) {
		
		// group transform
		if(xml.isAttribute("transform")) {
			group.transform *= get_transform(xml.getAttribute("transform"));
		}
		
		// group stroke style
		if(xml.isAttribute("stroke")) {
			float32_t width = xml.getAttribute("stroke-width", 1.0f);
			float32_t offset = xml.getAttribute("stroke-width", 1.0f) * 0.5f;
			Color color = Color(xml.getAttribute("stroke").get());
			group.stroke = StrokeStyle(width, offset, color);
		} else {
			group.stroke = StrokeStyle();
		}
		
		// group color
		if(xml.isAttribute("fill")) {
			String fill = xml.getAttribute("fill");
			auto it = gradients.find(fill);
			if(it) {
				group.gradient = it->data;
				group.color = Color::white;
			} else {
				Color color = Color(fill.get());
				group.color = color;
			}
		} else if(group.stroke.width > 0.0f) {
			group.color = Color::zero;
		}
		
		// group style
		if(xml.isAttribute("style")) {
			create_style(xml, group);
		}
		
		// group elements
		for(const Xml &child : xml.getChildren()) {
			const String &name = child.getName();
			if(name == "g") create_group(child, group);
			else if(name == "path") create_path(child, group);
			else TS_LOGF(Warning, "ControlSVG::create_group(): unknown element %s\n", name.get());
		}
		
		return true;
	}
	
	/*
	 */
	bool ControlSVG::create_path(const Xml &xml, Group group) {
		
		// check path
		if(!xml.isAttribute("d")) {
			TS_LOG(Error, "ControlSVG::create_path(): can't find data\n");
			return false;
		}
		
		// path transform
		if(xml.isAttribute("transform")) {
			group.transform *= get_transform(xml.getAttribute("transform"));
		}
		
		// path stroke style
		if(xml.isAttribute("stroke")) {
			float32_t width = xml.getAttribute("stroke-width", 1.0f);
			float32_t offset = xml.getAttribute("stroke-width", 1.0f) * 0.5f;
			Color color = Color(xml.getAttribute("stroke").get());
			group.stroke = StrokeStyle(width, offset, color);
		}
		
		// path color
		if(xml.isAttribute("fill")) {
			String fill = xml.getAttribute("fill");
			auto it = gradients.find(fill);
			if(it) {
				group.gradient = it->data;
				group.color = Color::white;
			} else {
				Color color = Color(fill.get());
				group.color = color;
			}
		}
		
		// path style
		if(xml.isAttribute("style")) {
			create_style(xml, group);
		}
		
		// transparent path
		if(group.color.a == 0.0f) return true;
		
		// create shape
		Canvas canvas = getCanvas();
		CanvasShape shape = CanvasShape(canvas);
		if(!shape.createSVG(xml.getAttribute("d").get())) {
			TS_LOG(Error, "ControlSVG::create_path(): can't create shape\n");
			return false;
		}
		shape.setThreshold(getThreshold());
		shape.setTransform(Matrix4x4f(group.transform));
		shape.setColor(group.color);
		shapes.append(shape);
		
		// stroke style
		if(group.stroke.width > 0.0f) {
			shape.setStrokeStyle(group.stroke);
		}
		
		// gradient style
		if(group.gradient.radius > 0.0f || group.gradient.length > 0.0f) {
			shape.setMode(CanvasElement::ModeGradient);
			shape.setGradientStyle(group.gradient);
		}
		
		// shape name
		if(xml.isAttribute("id")) {
			names.append(xml.getAttribute("id"), shapes.size() - 1);
		}
		
		return true;
	}
	
	/*
	 */
	void ControlSVG::setThreshold(float32_t t) {
		for(CanvasShape &shape : shapes) {
			shape.setThreshold(t);
		}
		threshold = t;
	}
	
	/*
	 */
	uint32_t ControlSVG::findShape(const char *name) const {
		auto it = names.find(name);
		if(it) return it->data;
		return Maxu32;
	}
	
	uint32_t ControlSVG::findShape(const String &name) const {
		auto it = names.find(name);
		if(it) return it->data;
		return Maxu32;
	}
	
	CanvasShape ControlSVG::getShape(const char *name) {
		auto it = names.find(name);
		if(it) return shapes[it->data];
		return CanvasShape::null;
	}
	
	CanvasShape ControlSVG::getShape(const String &name) {
		auto it = names.find(name);
		if(it) return shapes[it->data];
		return CanvasShape::null;
	}
	
	/*
	 */
	void ControlSVG::update_enabled(bool enabled) {
		enabled &= isEnabled();
		for(CanvasShape &shape : shapes) {
			shape.setEnabled(enabled);
		}
		ControlBase::update_enabled(enabled);
	}
	
	void ControlSVG::update_rectangle(ControlRoot &root, int32_t &order, uint32_t scale) {
		for(CanvasShape &shape : shapes) {
			shape.setOrder(order++);
		}
		Rect rect = getSVGRect();
		rect.right += max(getWidth() - rect.getWidth(), 0.0f);
		rect.top += max(getHeight() - rect.getHeight(), 0.0f);
		rect += getMargin();
		set_rect(rect);
	}
	
	bool ControlSVG::update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale) {
		
		// expand control
		update_expand(root, region);
		Rect rect = getRect() - getMargin();
		
		// control position
		Vector3f position = get_position(region, scale);
		float32_t scale_x = rect.getWidth() / getSVGRect().getWidth();
		float32_t scale_y = rect.getHeight() / getSVGRect().getHeight();
		if(hasAlign(AlignAspect)) {
			float32_t scale = min(scale_x, scale_y);
			if(scale_x > scale) {
				if(hasAlign(AlignRight)) position.x += (scale_x - scale) * getSVGRect().getWidth();
				else if(hasAlign(AlignCenterX)) position.x += floor((scale_x - scale) * getSVGRect().getWidth() * 0.5f + 0.5f);
			}
			if(scale_y > scale) {
				if(hasAlign(AlignTop)) position.y += (scale_y - scale) * getSVGRect().getHeight();
				else if(hasAlign(AlignCenterY)) position.y += floor((scale_y - scale) * getSVGRect().getHeight() * 0.5f + 0.5f);
			}
			scale_x = scale;
			scale_y = scale;
		}
		setOffset(position);
		
		// transform shapes
		if(shapes) {
			Matrix4x4f transform = Matrix4x4f::translate(position) * Matrix4x4f::scale(scale_x, scale_y, 1.0f);
			shapes[0].setTransform(transform, CanvasElement::StackPush | CanvasElement::StackMul);
			shapes.back().setTransform(CanvasElement::StackPop);
		}
		
		return false;
	}
}

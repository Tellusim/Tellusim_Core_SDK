// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimBlob.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimCommand.h>

#include "../include/TellusimControlPlotter.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	ControlPlotter::ControlPlotter(Control *parent, const Device &device, uint32_t num) : ControlBase(parent), device(device) {
		setMaxValues(num);
		create();
	}
	
	ControlPlotter::~ControlPlotter() {
		
	}
	
	/*
	 */
	void ControlPlotter::clear() {
		Canvas canvas = getCanvas();
		canvas_rect = CanvasRect(canvas);
		canvas.removeElement(canvas_rect);
		canvas_rect.clearPtr();
		ControlBase::clear();
	}
	
	/*
	 */
	void ControlPlotter::create() {
		Canvas canvas = getCanvas();
		canvas_rect = CanvasRect(canvas);
		ControlBase::create();
	}
	
	/*
	 */
	bool ControlPlotter::create_pipeline() {
		
		// control canvas
		Canvas canvas = getCanvas();
		if(canvas.getColorFormat() == FormatUnknown) return false;
		
		// plotter shader source
		#include "TellusimControlPlotter.blob"
		String src = Blob(TellusimControlPlotter_blob_src).gets();
		
		// create plotter pipeline
		pipeline = device.createPipeline();
		pipeline.setUniformMasks(0, 2, Shader::MaskVertex);
		pipeline.setUniformMasks(2, 3, Shader::MaskFragment);
		pipeline.setScissorTest(true);
		pipeline.setDepthMask(Pipeline::DepthMaskNone);
		pipeline.setDepthFunc(Pipeline::DepthFuncAlways);
		pipeline.setColorFormat(canvas.getColorFormat());
		pipeline.setDepthFormat(canvas.getDepthFormat());
		pipeline.setMultisample(canvas.getMultisample());
		pipeline.setBlend(Pipeline::BlendOpAdd, Pipeline::BlendFuncSrcAlpha, Pipeline::BlendFuncInvSrcAlpha);
		pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBAf32, 0, offsetof(CanvasShapeVertex, position), sizeof(CanvasShapeVertex));
		pipeline.addAttribute(Pipeline::AttributeTexCoord, FormatRGBAf32, 0, offsetof(CanvasShapeVertex, parameters), sizeof(CanvasShapeVertex));
		pipeline.addAttribute(Pipeline::AttributeTexCoord, FormatRGf32, 0, offsetof(CanvasShapeVertex, texcoord), sizeof(CanvasShapeVertex));
		if(!pipeline.createShaderGLSL(Shader::TypeVertex, src.get(), "VERTEX_SHADER=1")) return false;
		if(!pipeline.createShaderGLSL(Shader::TypeFragment, src.get(), "FRAGMENT_SHADER=1")) return false;
		if(!pipeline.create()) {
			TS_LOG(Error, "ControlPlotter::create_pipeline(): can't create plotter pipeline\n");
			return false;
		}
		
		return true;
	}
	
	/*
	 */
	void ControlPlotter::setRange(float32_t min, float32_t max, float32_t step) {
		range_min = Vector2f(min);
		range_max = Vector2f(max);
		range_step = Vector2f(step);
	}
	
	void ControlPlotter::setRangeX(float32_t min, float32_t max, float32_t step) {
		range_min.x = min;
		range_max.x = max;
		range_step.x = step;
	}
	
	void ControlPlotter::setRangeY(float32_t min, float32_t max, float32_t step) {
		range_min.y = min;
		range_max.y = max;
		range_step.y = step;
	}
	
	/*
	 */
	void ControlPlotter::setMaxValues(uint32_t num) {
		values.resize(num, 0.0f);
		num_values = 0;
	}
	
	/*
	 */
	void ControlPlotter::clearValues() {
		num_values = 0;
	}
	
	/*
	 */
	void ControlPlotter::addValue(float32_t value, bool expand) {
		values[(num_values++) % getMaxValues()] = value;
		if(expand) {
			range_min.y = min(range_min.y, value - (range_max.y - range_min.y) * 0.1f);
			range_max.y = max(range_max.y, value + (range_max.y - range_min.y) * 0.1f);
		}
	}
	
	void ControlPlotter::addValues(const float32_t *v, uint32_t num, bool expand) {
		for(uint32_t i = 0; i < num; i++) {
			float32_t value = *v++;
			values[(num_values++) % getMaxValues()] = value;
			if(expand) {
				range_min.y = min(range_min.y, value - (range_max.y - range_min.y) * 0.1f);
				range_max.y = max(range_max.y, value + (range_max.y - range_min.y) * 0.1f);
			}
		}
	}
	
	/*
	 */
	void ControlPlotter::update_enabled(bool enabled) {
		enabled &= isEnabled();
		canvas_rect.setEnabled(enabled);
		ControlBase::update_enabled(enabled);
	}
	
	void ControlPlotter::update_rectangle(ControlRoot &root, int32_t &order, uint32_t scale) {
		Rect rect = Rect(0.0f, getWidth(), 0.0f, getHeight());
		canvas_rect.setOrder(order++);
		rect += getMargin();
		set_rect(rect);
	}
	
	bool ControlPlotter::update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale) {
		
		// plotter parameters
		struct PlotterParameters {
			Color plotter_color;
			Color line_color;
			Color axis_color;
			Vector4f range_x;
			Vector4f range_y;
			float32_t line_width;
			float32_t axis_width;
			uint32_t max_values;
			uint32_t num_values;
		};
		
		// create pipeline
		if(!pipeline && create_pipeline()) {
			canvas_rect.setPipeline(pipeline);
			canvas_rect.setDrawCallback([this](Command command, CanvasElement element) {
				PlotterParameters parameters = {};
				parameters.plotter_color = getPlotterColor();
				parameters.line_color = getLineColor();
				parameters.axis_color = getAxisColor();
				if(range_step.x > 0.0f) {
					parameters.range_x = Vector4f(range_min.x, range_max.x - range_min.x, 1.0f / range_step.x, 0.0f);
					if(getNumValues() > getMaxValues()) {
						float32_t step = 1.0f / (float32_t)(getMaxValues() - 3);
						float32_t scale = parameters.range_x.y * parameters.range_x.z;
						parameters.range_x.w = (float32_t)(getNumValues() - getMaxValues()) * scale * step;
					}
				}
				if(range_step.y > 0.0f) {
					parameters.range_y = Vector4f(range_min.y, range_max.y - range_min.y, 1.0f / range_step.y, 0.0f);
				}
				parameters.line_width = getLineWidth();
				parameters.axis_width = getAxisWidth();
				parameters.max_values = getMaxValues();
				parameters.num_values = getNumValues();
				command.setUniform(3, parameters);
				command.setUniformData(4, values.get(), values.bytes());
				return true;
			});
		}
		
		// expand control
		update_expand(root, region);
		Rect rect = getRect() - getMargin();
		
		// control position
		Vector3f position = get_position(region, scale);
		if(hasAlign(AlignAspect)) {
			float32_t aspect = getWidth() / getHeight();
			float32_t rect_aspect = rect.getWidth() / rect.getHeight();
			if(aspect < rect_aspect) {
				float32_t width = rect.getHeight() * aspect;
				if(hasAlign(AlignRight)) position.x += rect.getWidth() - width;
				else if(hasAlign(AlignCenterX)) position.x += floor((rect.getWidth() - width) * 0.5f + 0.5f);
				rect.right = width;
			} else if(aspect > rect_aspect) {
				float32_t height = rect.getWidth() / aspect;
				if(hasAlign(AlignTop)) position.y += rect.getHeight() - height;
				else if(hasAlign(AlignCenterY)) position.y += floor((rect.getHeight() - height) * 0.5f + 0.5f);
				rect.top = height;
			}
		}
		setOffset(position);
		
		// update element
		canvas_rect.setSize(rect.getWidth(), rect.getHeight());
		canvas_rect.setPosition(position + Vector3f(rect.getCenterX(), rect.getCenterY(), 0.0f));
		
		return false;
	}

}

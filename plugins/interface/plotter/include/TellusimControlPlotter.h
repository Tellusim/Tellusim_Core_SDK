// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_INTERFACE_CONTROL_PLOT_H__
#define __TELLUSIM_PLUGINS_INTERFACE_CONTROL_PLOT_H__

#include <interface/TellusimControls.h>

/*
 */
namespace Tellusim {
	
	/* ControlPlotter
	 */
	class ControlPlotter : public ControlBase {
			
		public:
			
			/// plotter constructor
			explicit ControlPlotter(Control *parent, const Device &device, uint32_t num = 256);
			virtual ~ControlPlotter();
			
			/// disable copying
			ControlPlotter(const ControlPlotter&) = delete;
			ControlPlotter &operator=(const ControlPlotter&) = delete;
			
			/// plotter colors
			void setPlotterColor(const Color &color) { plotter_color = color; }
			void setLineColor(const Color &color) { line_color = color; }
			void setAxisColor(const Color &color) { axis_color = color; }
			TS_INLINE const Color &getPlotterColor() const { return plotter_color; }
			TS_INLINE const Color &getLineColor() const { return line_color; }
			TS_INLINE const Color &getAxisColor() const { return axis_color; }
			
			/// plotter width
			void setLineWidth(float32_t width) { line_width = width; }
			void setAxisWidth(float32_t width) { axis_width = width; }
			TS_INLINE float32_t getLineWidth() const { return line_width; }
			TS_INLINE float32_t getAxisWidth() const { return axis_width; }
			
			/// plotter range
			void setRange(float32_t min, float32_t max, float32_t step = 0.0f);
			void setRangeX(float32_t min, float32_t max, float32_t step = 0.0f);
			void setRangeY(float32_t min, float32_t max, float32_t step = 0.0f);
			TS_INLINE const Vector2f &getRangeMin() const { return range_min; }
			TS_INLINE const Vector2f &getRangeMax() const { return range_min; }
			TS_INLINE const Vector2f &getRangeStep() const { return range_step; }
			
			/// plotter values
			void setMaxValues(uint32_t num);
			TS_INLINE uint32_t getMaxValues() const { return values.size(); }
			TS_INLINE uint32_t getNumValues() const { return num_values; }
			
			void clearValues();
			void addValue(float32_t value, bool expand = true);
			void addValues(const float32_t *values, uint32_t num, bool expand = true);
			
			/// canvas elements
			TS_INLINE CanvasRect &getCanvasRect() { return canvas_rect; }
			
		private:
			
			/// create control
			void create();
			bool create_pipeline();
			
			/// update control
			virtual void update_enabled(bool enabled);
			virtual void update_rectangle(ControlRoot &root, int32_t &order, uint32_t scale);
			virtual bool update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale);
			
			const Device &device;					// device
			
			Color plotter_color = Color::black;		// plotter color
			Color line_color = Color::white;		// line color
			Color axis_color = Color::gray;			// axis color
			
			float32_t line_width = 3.0f;			// line width
			float32_t axis_width = 3.0f;			// axis width
			
			Vector2f range_min = Vector2f(0.0f);	// minimum values
			Vector2f range_max = Vector2f(1.0f);	// maximum values
			Vector2f range_step = Vector2f(0.0f);	// grid step
			
			uint32_t num_values = 0;				// number of values
			
			Array<float32_t> values;				// plotter values
			
			Pipeline pipeline;						// plotter pipeline
			
			CanvasRect canvas_rect;					// canvas rect
	};
}

#endif /* __TELLUSIM_PLUGINS_INTERFACE_CONTROL_PLOT_H__ */

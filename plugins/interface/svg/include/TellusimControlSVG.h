// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_INTERFACE_CONTROL_SVG_H__
#define __TELLUSIM_PLUGINS_INTERFACE_CONTROL_SVG_H__

#include <core/TellusimMap.h>
#include <interface/TellusimControls.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Xml;
	class Stream;
	
	/* ControlSVG
	 */
	class ControlSVG : public ControlBase {
			
		public:
			
			/// SVG constructor
			explicit ControlSVG(Control *parent);
			ControlSVG(Control *parent, float32_t threshold);
			virtual ~ControlSVG();
			
			/// disable copying
			ControlSVG(const ControlSVG&) = delete;
			ControlSVG &operator=(const ControlSVG&) = delete;
			
			/// load SVG file
			bool loadSVG(Stream &stream);
			bool loadSVG(const char *name);
			bool loadSVG(const String &name);
			
			/// create SVG control
			bool createSVG(const Xml &root);
			
			/// cubic to quadratic threshold
			void setThreshold(float32_t threshold);
			TS_INLINE float32_t getThreshold() const { return threshold; }
			
			/// named elements
			uint32_t findShape(const char *name) const;
			uint32_t findShape(const String &name) const;
			CanvasShape getShape(const char *name);
			CanvasShape getShape(const String &name);
			
			/// canvas elements
			TS_INLINE uint32_t getNumShapes() const { return shapes.size(); }
			TS_INLINE CanvasShape &getShape(uint32_t index) { return shapes[index]; }
			TS_INLINE const Array<CanvasShape> &getShapes() const { return shapes; }
			TS_INLINE Array<CanvasShape> &getShapes() { return shapes; }
			
			/// SVG rectangle
			void setSVGRect(const Rect &rect) { svg_rect = rect; }
			TS_INLINE const Rect &getSVGRect() const { return svg_rect; }
			
		private:
			
			struct Group;
			
			/// clear SVG
			void clear_shapes();
			
			/// read SVG
			static Matrix4x3f get_transform(const String &src);
			
			/// create SVG
			bool create_defs(const Xml &xml);
			bool create_style(const Xml &xml, Group &group);
			bool create_group(const Xml &xml, Group group);
			bool create_path(const Xml &xml, Group group);
			
			/// control batch
			virtual bool is_batch() const { return false; }
			
			/// update control
			virtual void update_enabled(bool enabled);
			virtual void update_rectangle(ControlRoot &root, int32_t &order, uint32_t scale);
			virtual bool update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale);
			
			struct Group {
				Matrix4x3f transform;				// group transform
				GradientStyle gradient;				// gradient style
				StrokeStyle stroke;					// stroke style
				Color color;						// group color
			};
			
			float32_t threshold = 1.0f;				// threshold
			
			Map<String, GradientStyle> gradients;	// gradients
			Map<String, uint32_t> names;			// names
			Array<CanvasShape> shapes;				// shapes
			
			Rect svg_rect = Rect(0.0f);				// SVG rect
	};
}

#endif /* __TELLUSIM_PLUGINS_INTERFACE_CONTROL_SVG_H__ */

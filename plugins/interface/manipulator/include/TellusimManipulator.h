// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_INTERFACE_MANIPULATOR_H__
#define __TELLUSIM_PLUGINS_INTERFACE_MANIPULATOR_H__

#include <interface/TellusimControls.h>

/*
 */
namespace Tellusim {
	
	/* Manipulator
	 */
	class Manipulator : public ControlBase {
			
		public:
			
			/// manipulator constructor
			explicit Manipulator(Control *parent);
			virtual ~Manipulator();
			
			/// disable copying
			Manipulator(const Manipulator&) = delete;
			Manipulator &operator=(const Manipulator&) = delete;
			
			enum Mode {
				ModeUnknown = 0,
				ModeTranslator,
				ModeRotator,
				ModeScaler,
				NumModes,
			};
			
			enum Axis {
				AxisX = 0,
				AxisY,
				AxisZ,
				NumAxes1,
				AxisYZ = NumAxes1,
				AxisXZ,
				AxisXY,
				NumAxes2,
				AxisXYZ = NumAxes2,
				AxisUnknown,
				NumAxes,
			};
			
			/// current mode
			void setMode(Mode mode);
			TS_INLINE Mode getMode() const { return current_mode; }
			
			TS_INLINE bool isModeUnknown() const { return (getMode() == ModeUnknown); }
			TS_INLINE bool isTranslator() const { return (getMode() == ModeTranslator); }
			TS_INLINE bool isRotator() const { return (getMode() == ModeRotator); }
			TS_INLINE bool isScaler() const { return (getMode() == ModeScaler); }
			
			/// current axis
			TS_INLINE Axis getAxis() const { return current_axis; }
			
			TS_INLINE bool isAxisUnknown() const { return (getAxis() == AxisUnknown); }
			TS_INLINE bool isAxisX() const { return (getAxis() == AxisX); }
			TS_INLINE bool isAxisY() const { return (getAxis() == AxisY); }
			TS_INLINE bool isAxisZ() const { return (getAxis() == AxisZ); }
			TS_INLINE bool isAxisYZ() const { return (getAxis() == AxisYZ); }
			TS_INLINE bool isAxisXZ() const { return (getAxis() == AxisXZ); }
			TS_INLINE bool isAxisXY() const { return (getAxis() == AxisXY); }
			TS_INLINE bool isAxisXYZ() const { return (getAxis() == AxisXYZ); }
			
			/// axis length
			void setAxisLength(float32_t length);
			TS_INLINE float32_t getAxisLength() const { return axis_length; }
			
			/// axis radius
			void setAxisRadius(float32_t radius);
			TS_INLINE float32_t getAxisRadius() const { return axis_radius; }
			
			/// arrow length
			void setArrowLength(float32_t length);
			TS_INLINE float32_t getArrowLength() const { return arrow_length; }
			
			/// arrow radius
			void setArrowRadius(float32_t radius);
			TS_INLINE float32_t getArrowRadius() const { return arrow_radius; }
			
			/// handle offset
			void setHandleOffset(float32_t offset);
			TS_INLINE float32_t getHandleOffset() const { return handle_offset; }
			
			/// handle size
			void setHandleSize(float32_t size);
			TS_INLINE float32_t getHandleSize() const { return handle_size; }
			
			/// rotator sensivity
			void setRotatorSensivity(float32_t sensivity);
			TS_INLINE float32_t getRotatorSensivity() const { return rotator_sensivity; }
			
			/// scaler uniform
			void setScalerUniform(bool uniform);
			TS_INLINE bool isScalerUniform() const { return scaler_uniform; }
			
			/// manipulator step
			void setModeStep(Mode mode, float64_t step);
			TS_INLINE float64_t getModeStep(Mode mode) const { return mode_steps[mode]; }
			
			/// manipulator colors
			void setEnabledColor(const Color &color);
			void setDisabledColor(const Color &color);
			void setAxisColor(Axis axis, const Color &color);
			TS_INLINE const Color &getEnabledColor() const { return enabled_color; }
			TS_INLINE const Color &getDisabledColor() const { return disabled_color; }
			TS_INLINE const Color &getAxisColor(Axis axis) const { return axis_colors[axis]; }
			
			/// projection matrix
			void setProjection(const Matrix4x4f &projection);
			TS_INLINE const Matrix4x4f &getProjection() const { return camera_projection; }
			
			/// imodelview matrix
			void setIModelview(const Matrix4x3d &modelview);
			TS_INLINE const Matrix4x3d &getIModelview() const { return camera_imodelview; }
			
			/// global transform
			void setGlobalTransform(const Matrix4x3d &transform);
			TS_INLINE const Matrix4x3d &getGlobalTransform() const { return global_transform; }
			
			/// basis transform
			void setBasisTransform(const Matrix4x3d &transform);
			TS_INLINE const Matrix4x3d &getBasisTransform() const { return basis_transform; }
			
			/// local transform
			void setLocalTransform(const Matrix4x3d &transform);
			TS_INLINE const Matrix4x3d &getLocalTransform() const { return local_transform; }
			
			/// relative transform
			TS_INLINE const Matrix4x3d &getRelativeTransform() const { return relative_transform; }
			
			/// clicked callback
			using ClickedCallback = Function<void(Manipulator*)>;
			void setClickedCallback(const ClickedCallback &func);
			TS_INLINE const ClickedCallback &getClickedCallback() const { return clicked_func; }
			
			/// changed callback
			using ChangedCallback = Function<void(Manipulator*)>;
			void setChangedCallback(const ChangedCallback &func);
			TS_INLINE const ChangedCallback &getChangedCallback() const { return changed_func; }
			
			/// changed flag
			TS_INLINE bool isChanged() const { return mouse_changed; }
			
		private:
			
			/// clear control
			virtual void clear();
			
			/// create control
			void create();
			
			/// create canvas
			void create_canvas();
			
			/// manipulator selection
			float32_t get_distance(const Vector2f &point, const Vector2f &v0, const Vector2f &v1) const;
			bool get_intersection(const Vector2f &point, const Vector2f &v0, const Vector2f &v1, const Vector2f &v2, const Vector2f &v3) const;
			
			/// manipulator intersection
			Vector2f get_position(const Vector2f &point) const;
			Vector3d get_direction(const Vector2f &point) const;
			Vector3d get_intersection(const Vector2f &point, const Vector4d &plane) const;
			
			/// manipulator values
			float64_t round_value(const float64_t value, float64_t step) const;
			Vector3d round_value(const Vector3d &value, float64_t step) const;
			
			/// update control
			virtual void update_enabled(bool enabled);
			virtual void update_rectangle(ControlRoot &root, int32_t &order, uint32_t scale);
			virtual bool update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale);
			
			enum {
				ArrowSteps		= 16,					// arrow steps
				RotatorSteps	= 64,					// rotator steps
			};
			
			Mode current_mode = ModeUnknown;			// current mode
			Axis current_axis = AxisUnknown;			// current axis
			
			float32_t axis_length = 96.0f;				// axis length
			float32_t axis_radius = 2.0f;				// axis radius
			
			float32_t arrow_length = 24.0f;				// arrow length
			float32_t arrow_radius = 6.0f;				// arrow radius
			
			float32_t handle_offset = 48.0f;			// handle offset
			float32_t handle_size = 18.0f;				// handle size
			
			float32_t rotator_sensivity = 0.5f;			// rotator sensivity
			
			bool scaler_uniform = false;				// scaler uniform
			
			float64_t mode_steps[NumModes] = {};		// mode steps
			
			Color enabled_color = Color::white;			// enabled color
			Color disabled_color = Color(0.7f);			// diabled color
			Color axis_colors[NumAxes];					// axis colors
			
			Matrix4x4f camera_projection;				// camera projection
			Matrix4x3d camera_imodelview;				// camera imodelview
			Matrix4x3d camera_itransform;				// camera itransform
			
			Matrix4x3d global_transform;				// global transform
			Matrix4x3d basis_transform;					// basis transform
			Matrix4x3d local_transform;					// local transform
			
			Matrix4x3d relative_transform;				// relative transform
			
			Matrix4x4f mouse_projection;				// mouse projection
			Vector4d mouse_plane = Vector4d::zero;		// mouse plane
			Vector3d mouse_value = Vector3d::zero;		// mouse value
			Vector3d mouse_position = Vector3d::zero;	// mouse position
			bool mouse_changed = false;					// mouse changed flag
			
			ClickedCallback clicked_func;				// clicked callback
			ChangedCallback changed_func;				// changed callback
			
			CanvasMesh translator_meshes[NumAxes2];		// translator meshes
			CanvasStrip translator_strips[NumAxes1];	// translator strips
			CanvasStrip rotator_strips[NumAxes1];		// rotator strips
			CanvasEllipse rotator_ellipse;				// rotator ellipse
			CanvasMesh scaler_meshes[NumAxes];			// scaler meshes
			CanvasStrip scaler_strips[NumAxes1];		// scaler strips
			CanvasStrip relative_strip;					// relative strip
			
			CanvasMesh scissor_mesh;					// scissor mesh
			CanvasMesh restore_mesh;					// restore mesh
	};
}

#endif /* __TELLUSIM_PLUGINS_INTERFACE_MANIPULATOR_H__ */

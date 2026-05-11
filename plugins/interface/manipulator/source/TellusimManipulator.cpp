// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimSort.h>
#include <geometry/TellusimBasis.h>

#include "../include/TellusimManipulator.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	Manipulator::Manipulator(Control *parent) : ControlBase(parent) {
		
		axis_colors[AxisX] = Color::red;
		axis_colors[AxisY] = Color::green;
		axis_colors[AxisZ] = Color::blue;
		axis_colors[AxisYZ] = Color::red;
		axis_colors[AxisXZ] = Color::green;
		axis_colors[AxisXY] = Color::blue;
		axis_colors[AxisXYZ] = Color::gray * Color(1.0f, 0.5f);
		
		camera_projection = Matrix4x4f::zero;
		camera_imodelview = Matrix4x3d::identity;
		camera_itransform = Matrix4x3d::identity;
		
		global_transform = Matrix4x3d::identity;
		local_transform = Matrix4x3d::identity;
		basis_transform = Matrix4x3d::identity;
		
		relative_transform = Matrix4x3d::identity;
		
		mouse_projection = Matrix4x4f::zero;
		
		create();
	}
	
	Manipulator::~Manipulator() {
		clear();
	}
	
	/*
	 */
	void Manipulator::clear() {
		Canvas canvas = getCanvas();
		for(uint32_t i = 0; i < TS_COUNTOF(translator_meshes); i++) {
			canvas.removeElement(translator_meshes[i]);
			translator_meshes[i].clearPtr();
		}
		for(uint32_t i = 0; i < TS_COUNTOF(translator_strips); i++) {
			canvas.removeElement(translator_strips[i]);
			translator_strips[i].clearPtr();
		}
		for(uint32_t i = 0; i < TS_COUNTOF(rotator_strips); i++) {
			canvas.removeElement(rotator_strips[i]);
			rotator_strips[i].clearPtr();
		}
		canvas.removeElement(rotator_ellipse);
		rotator_ellipse.clearPtr();
		for(uint32_t i = 0; i < TS_COUNTOF(scaler_meshes); i++) {
			canvas.removeElement(scaler_meshes[i]);
			scaler_meshes[i].clearPtr();
		}
		for(uint32_t i = 0; i < TS_COUNTOF(scaler_strips); i++) {
			canvas.removeElement(scaler_strips[i]);
			scaler_strips[i].clearPtr();
		}
		canvas.removeElement(relative_strip);
		canvas.removeElement(scissor_mesh);
		canvas.removeElement(restore_mesh);
		relative_strip.clearPtr();
		scissor_mesh.clearPtr();
		restore_mesh.clearPtr();
		ControlBase::clear();
	}
	
	/*
	 */
	void Manipulator::create() {
		Canvas canvas = getCanvas();
		for(uint32_t i = 0; i < TS_COUNTOF(translator_meshes); i++) {
			translator_meshes[i] = CanvasMesh(canvas);
		}
		for(uint32_t i = 0; i < TS_COUNTOF(translator_strips); i++) {
			translator_strips[i] = CanvasStrip(canvas);
		}
		for(uint32_t i = 0; i < TS_COUNTOF(rotator_strips); i++) {
			rotator_strips[i] = CanvasStrip(canvas);
		}
		rotator_ellipse = CanvasEllipse(canvas);
		for(uint32_t i = 0; i < TS_COUNTOF(scaler_meshes); i++) {
			scaler_meshes[i] = CanvasMesh(canvas);
		}
		for(uint32_t i = 0; i < TS_COUNTOF(scaler_strips); i++) {
			scaler_strips[i] = CanvasStrip(canvas);
		}
		relative_strip = CanvasStrip(canvas);
		scissor_mesh = CanvasMesh(canvas);
		restore_mesh = CanvasMesh(canvas);
		ControlBase::create();
		create_canvas();
	}
	
	/*
	 */
	void Manipulator::setMode(Mode m) {
		current_mode = m;
	}
	
	/*
	 */
	void Manipulator::setAxisLength(float32_t size) {
		axis_length = size;
		create_canvas();
	}
	
	void Manipulator::setAxisRadius(float32_t radius) {
		axis_radius = radius;
		create_canvas();
	}
	
	void Manipulator::setArrowLength(float32_t size) {
		arrow_length = size;
		create_canvas();
	}
	
	void Manipulator::setArrowRadius(float32_t radius) {
		arrow_radius = radius;
		create_canvas();
	}
	
	void Manipulator::setHandleOffset(float32_t offset) {
		handle_offset = offset;
		create_canvas();
	}
	
	void Manipulator::setHandleSize(float32_t size) {
		handle_size = size;
		create_canvas();
	}
	
	void Manipulator::setEnabledColor(const Color &color) {
		enabled_color = color;
	}
	
	void Manipulator::setDisabledColor(const Color &color) {
		disabled_color = color;
	}
	
	void Manipulator::setRotatorSensivity(float32_t sensivity) {
		rotator_sensivity = sensivity;
	}
	
	void Manipulator::setScalerUniform(bool uniform) {
		scaler_uniform = uniform;
	}
	
	void Manipulator::setModeStep(Mode mode, float64_t step) {
		mode_steps[mode] = step;
	}
	
	void Manipulator::setAxisColor(Axis axis, const Color &color) {
		axis_colors[axis] = color;
	}
	
	/*
	 */
	void Manipulator::setProjection(const Matrix4x4f &projection) {
		camera_projection = projection;
	}
	
	void Manipulator::setIModelview(const Matrix4x3d &imodelview) {
		camera_imodelview = imodelview;
	}
	
	void Manipulator::setGlobalTransform(const Matrix4x3d &transform) {
		global_transform = transform;
	}
	
	void Manipulator::setBasisTransform(const Matrix4x3d &transform) {
		basis_transform = transform;
	}
	
	void Manipulator::setLocalTransform(const Matrix4x3d &transform) {
		local_transform = transform;
	}
	
	/*
	 */
	void Manipulator::setClickedCallback(const ClickedCallback &func) {
		clicked_func = func;
	}
	
	void Manipulator::setChangedCallback(const ChangedCallback &func) {
		changed_func = func;
	}
	
	/*
	 */
	void Manipulator::create_canvas() {
		
		// create translator
		{
			// clear translator meshes
			for(uint32_t i = 0; i < TS_COUNTOF(translator_meshes); i++) {
				translator_meshes[i].clearVertices();
				translator_meshes[i].clearIndices();
			}
			
			// create translator mesh arrows
			float32_t length = getAxisLength() - getArrowLength();
			CanvasMesh &mesh_x = translator_meshes[AxisX];
			CanvasMesh &mesh_y = translator_meshes[AxisY];
			CanvasMesh &mesh_z = translator_meshes[AxisZ];
			mesh_x.addVertex(axis_length, 0.0f, 0.0f);
			mesh_y.addVertex(0.0f, axis_length, 0.0f);
			mesh_z.addVertex(0.0f, 0.0f, axis_length);
			for(uint32_t i = 0; i < ArrowSteps; i++) {
				float32_t x, y, angle = Pi2 * i / (ArrowSteps - 1);
				sincos(angle, x, y); x *= arrow_radius; y *= arrow_radius;
				mesh_x.addVertex(length, x, y);
				mesh_y.addVertex(x, length, y);
				mesh_z.addVertex(x, y, length);
			}
			for(uint32_t i = 0; i + 1 < ArrowSteps; i++) {
				mesh_x.addIndices(0, i + 1, i + 2);
			}
			
			// create translator mesh handles
			CanvasMesh &mesh_yz = translator_meshes[AxisYZ];
			CanvasMesh &mesh_xz = translator_meshes[AxisXZ];
			CanvasMesh &mesh_xy = translator_meshes[AxisXY];
			for(uint32_t i = 0; i < 4; i++) {
				float32_t x = ((i & 1) ? -getHandleSize() : getHandleSize()) + getHandleOffset();
				float32_t y = ((i < 2) ? -getHandleSize() : getHandleSize()) + getHandleOffset();
				mesh_yz.addVertex(0.0f, x, y);
				mesh_xz.addVertex(x, 0.0f, y);
				mesh_xy.addVertex(x, y, 0.0f);
			}
			mesh_yz.addIndices(0, 1, 2);
			mesh_yz.addIndices(2, 3, 1);
			
			// duplicate translator mesh indices
			mesh_y.setIndices(mesh_x.getIndices(), mesh_x.getNumIndices());
			mesh_z.setIndices(mesh_x.getIndices(), mesh_x.getNumIndices());
			mesh_xz.setIndices(mesh_yz.getIndices(), mesh_yz.getNumIndices());
			mesh_xy.setIndices(mesh_yz.getIndices(), mesh_yz.getNumIndices());
		}
		
		// create scaler
		{
			// clear scaler meshes
			for(uint32_t i = 0; i < TS_COUNTOF(scaler_meshes); i++) {
				scaler_meshes[i].clearVertices();
				scaler_meshes[i].clearIndices();
			}
			
			// create scaler mesh arrows
			float32_t size = getArrowRadius();
			float32_t length = getAxisLength() - getArrowRadius() * 2.0f;
			CanvasMesh &mesh_x = scaler_meshes[AxisX];
			CanvasMesh &mesh_y = scaler_meshes[AxisY];
			CanvasMesh &mesh_z = scaler_meshes[AxisZ];
			for(uint32_t i = 0; i < 4; i++) {
				float32_t x = (i & 1) ? -size : size;
				float32_t y = (i < 2) ? -size : size;
				mesh_x.addVertex(getAxisLength(), x, y);
				mesh_y.addVertex(x, getAxisLength(), y);
				mesh_z.addVertex(x, y, getAxisLength());
				mesh_x.addVertex(length, x, y);
				mesh_y.addVertex(x, length, y);
				mesh_z.addVertex(x, y, length);
			}
			mesh_x.addIndices(0, 2, 4); mesh_x.addIndices(4, 6, 2);
			mesh_x.addIndices(1, 3, 5); mesh_x.addIndices(5, 7, 3);
			mesh_x.addIndices(0, 1, 5); mesh_x.addIndices(5, 4, 0);
			mesh_x.addIndices(4, 5, 7); mesh_x.addIndices(7, 6, 4);
			mesh_x.addIndices(6, 7, 3); mesh_x.addIndices(3, 2, 6);
			mesh_x.addIndices(2, 3, 1); mesh_x.addIndices(1, 0, 2);
			
			// create scaler mesh handles
			CanvasMesh &mesh_yz = scaler_meshes[AxisYZ];
			CanvasMesh &mesh_xz = scaler_meshes[AxisXZ];
			CanvasMesh &mesh_xy = scaler_meshes[AxisXY];
			for(uint32_t i = 0; i < 4; i++) {
				float32_t x = ((i & 1) ? -getHandleSize() : getHandleSize()) + getHandleOffset();
				float32_t y = ((i < 2) ? -getHandleSize() : getHandleSize()) + getHandleOffset();
				mesh_yz.addVertex(0.0f, x, y);
				mesh_xz.addVertex(x, 0.0f, y);
				mesh_xy.addVertex(x, y, 0.0f);
			}
			mesh_yz.addIndices(0, 1, 2);
			mesh_yz.addIndices(2, 3, 1);
			
			// create scaler mesh handle
			size = getAxisLength();
			CanvasMesh &mesh_xyz = scaler_meshes[AxisXYZ];
			for(uint32_t i = 0; i < 4; i++) {
				float32_t x = (i & 1) ? 0.0f : size;
				float32_t y = (i < 2) ? 0.0f : size;
				mesh_xyz.addVertex(size, x, y);
				mesh_xyz.addVertex(0.0f, x, y);
			}
			
			// duplicate scaler mesh indices
			mesh_y.setIndices(mesh_x.getIndices(), mesh_x.getNumIndices());
			mesh_z.setIndices(mesh_x.getIndices(), mesh_x.getNumIndices());
			mesh_xyz.setIndices(mesh_x.getIndices(), mesh_x.getNumIndices());
			mesh_xz.setIndices(mesh_yz.getIndices(), mesh_yz.getNumIndices());
			mesh_xy.setIndices(mesh_yz.getIndices(), mesh_yz.getNumIndices());
		}
		
		// update strips
		for(uint32_t i = 0; i < TS_COUNTOF(translator_strips); i++) {
			translator_strips[i].setWidth(getAxisRadius() * 2.0f);
		}
		for(uint32_t i = 0; i < TS_COUNTOF(rotator_strips); i++) {
			rotator_strips[i].setWidth(getAxisRadius() * 2.0f);
		}
		for(uint32_t i = 0; i < TS_COUNTOF(scaler_strips); i++) {
			scaler_strips[i].setWidth(getAxisRadius() * 2.0f);
		}
	}
	
	/*
	 */
	float32_t Manipulator::get_distance(const Vector2f &point, const Vector2f &v0, const Vector2f &v1) const {
		Vector2f v10 = v1 - v0;
		Vector2f p0 = point - v0;
		float32_t k = saturate(dot(p0, v10) / dot(v10, v10));
		return length(v0 + v10 * k - point);
	}
	
	/*
	 */
	Vector2f Manipulator::get_position(const Vector2f &point) const {
		float32_t x = (point.x * 2.0f - 1.0f + camera_projection.m02) / camera_projection.m00;
		float32_t y = (point.y * 2.0f - 1.0f + camera_projection.m12) / camera_projection.m11;
		return Vector2f(x, y);
	}
	
	Vector3d Manipulator::get_direction(const Vector2f &point) const {
		if(camera_projection.m32 == 0.0f) return -camera_itransform.getColumn(2);
		return camera_itransform * Vector3d(get_position(point), -1.0f) - camera_itransform.getTranslate();
	}
	
	Vector3d Manipulator::get_intersection(const Vector2f &point, const Vector4d &plane) const {
		Vector3d position, direction;
		if(camera_projection.m32 == 0.0f) {
			position = camera_itransform * Vector3d(get_position(point), 0.0f);
			direction = -camera_itransform.getColumn(2);
		} else {
			position = camera_itransform.getTranslate();
			direction = camera_itransform * Vector3d(get_position(point), -1.0f) - position;
		}
		return position - direction * (dot(plane, position) / dot3(plane, direction));
	}
	
	/*
	 */
	float64_t Manipulator::round_value(float64_t value, float64_t step) const {
		if(value < 0.0) value = ceil(value / step - 0.5) * step;
		else value = floor(value / step + 0.5) * step;
		return value;
	}
	
	Vector3d Manipulator::round_value(const Vector3d &value, float64_t step) const {
		float64_t x = round_value(value.x, step);
		float64_t y = round_value(value.y, step);
		float64_t z = round_value(value.z, step);
		return Vector3d(x, y, z);
	}
	
	/*
	 */
	void Manipulator::update_enabled(bool enabled) {
		enabled &= isEnabled();
		for(uint32_t i = 0; i < TS_COUNTOF(translator_meshes); i++) {
			translator_meshes[i].setEnabled(enabled);
		}
		for(uint32_t i = 0; i < TS_COUNTOF(translator_strips); i++) {
			translator_strips[i].setEnabled(enabled);
		}
		for(uint32_t i = 0; i < TS_COUNTOF(rotator_strips); i++) {
			rotator_strips[i].setEnabled(enabled);
		}
		rotator_ellipse.setEnabled(enabled);
		for(uint32_t i = 0; i < TS_COUNTOF(scaler_meshes); i++) {
			scaler_meshes[i].setEnabled(enabled);
		}
		for(uint32_t i = 0; i < TS_COUNTOF(scaler_strips); i++) {
			scaler_strips[i].setEnabled(enabled);
		}
		relative_strip.setEnabled(enabled);
		ControlBase::update_enabled(enabled);
	}
	
	void Manipulator::update_rectangle(ControlRoot &root, int32_t &order, uint32_t scale) {
		float32_t size = getAxisLength() * 1.5f;
		Rect rect = Rect(0.0f);
		rect.left = -size;
		rect.right = size;
		rect.bottom = -size;
		rect.top = size;
		set_rect(rect);
	}
	
	bool Manipulator::update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale) {
		
		bool ret = false;
		
		// disable all elements
		update_enabled(false);
		
		// unknown mode
		if(isModeUnknown()) return false;
		
		// camera modelview
		Matrix4x3d camera_modelview = inverse(getIModelview());
		
		// camera transform
		// combination of modelview matrix and global transform
		Quaterniond camera_rotate;
		Vector3d camera_translate, camera_scale;
		Matrix4x3d camera_transform = camera_modelview * getGlobalTransform() * getBasisTransform();
		camera_transform.getComponents(camera_translate, camera_rotate, camera_scale);
		camera_itransform = inverse(camera_transform);
		
		// manipulator transform
		// combination of all transforms including relative
		Quaternionf manipulator_rotate;
		Vector3f manipulator_translate, manipulator_scale;
		Matrix4x3d local_transform = inverse(getBasisTransform()) * getLocalTransform();
		Matrix4x4f manipulator_transform = Matrix4x4f(camera_transform * local_transform * getRelativeTransform());
		manipulator_transform.getComponents(manipulator_translate, manipulator_rotate, manipulator_scale);
		
		// projection perspective scale
		// to keep fixed manipulator size in the viewport
		float32_t viewport_width = region.getWidth();
		float32_t viewport_height = region.getHeight();
		Vector3f p0 = (getProjection() * Vector4f(manipulator_translate, 1.0f)).cartesian();
		Vector3f p1 = (getProjection() * Vector4f(manipulator_translate + Vector3f(0.0f, getAxisLength(), 0.0f), 1.0f)).cartesian();
		float32_t projection_scale = 2.0f * getAxisLength() / max(viewport_height * length(Vector2f(p1 - p0)), 1e-16f);
		
		// projection transform
		// combination of final translation, camera rotate and fixed projection scale
		Matrix4x4f projection = getProjection() * Matrix4x4f::compose(manipulator_translate, Quaternionf(camera_rotate), Vector3f(projection_scale));
		projection = Matrix4x4f::scale(viewport_width * 0.5f, viewport_height * 0.5f, 1.0f) * Matrix4x4f::translate(1.0f, 1.0f, 0.0f) * projection;
		
		// manipulator position
		Vector3f control_position = (projection * Vector4f(0.0f, 0.0f, 0.0f, 1.0f)).cartesian();
		Vector3f control_offset = Vector3f(region.left, region.bottom, 0.0f);
		Rect rect = getRect() + control_position.xy + control_offset.xy;
		
		// control state
		if(!isDisabled()) {
			if(!root.getCurrentControl() || root.getCurrentControl() == *this) {
				if((rect.inside(root.getMouse()) && view.inside(root.getMouse()) && projection_scale < 1e8f) || getState() == StatePressed) {
					
					// mouse position
					Vector2f mouse = root.getMouse() - control_offset.xy;
					
					// reset axis
					if(getState() != StatePressed) current_axis = AxisUnknown;
					
					// select current axis
					if(isAxisUnknown() && !root.isMouseControl()) {
						
						// translator axis
						if(isTranslator()) {
							
							// axis intersection
							float32_t max_distance = -Maxf32;
							for(uint32_t i = 0; i < NumAxes1; i++) {
								Vector3f position = Vector3f::zero;
								position[i] = getAxisLength();
								position = (projection * Vector4f(position, 1.0f)).cartesian();
								float32_t d = get_distance(mouse, control_position.xy, position.xy);
								if(max_distance < position.z && d < getAxisRadius() * 4.0f) {
									max_distance = position.z;
									current_axis = (Axis)i;
								}
							}
							
							// handle intersection
							for(uint32_t i = NumAxes1; i < NumAxes2; i++) {
								Rect rect;
								float32_t max_position = -Maxf32;
								const CanvasMesh &mesh = translator_meshes[i];
								for(uint32_t j = 0; j < mesh.getNumVertices(); j++) {
									Vector3f position = (projection * Vector4f(mesh.getVertexPosition(j), 1.0f)).cartesian();
									max_position = max(max_position, position.z);
									rect.expand(position.x, position.y);
								}
								if(max_distance < max_position && rect.inside(mouse)) {
									max_distance = max_position;
									current_axis = (Axis)i;
								}
							}
						}
						// rotator axis
						else if(isRotator()) {
							
							// segment intersection
							Vector3f positions[NumAxes1];
							Vector3f old_positions[NumAxes1];
							float32_t min_distance = Maxf32;
							for(uint32_t i = 0; i < RotatorSteps; i++) {
								float32_t x, y, angle = Pi2 * i / (RotatorSteps - 1);
								sincosFast(angle, x, y); x *= getAxisLength(); y *= getAxisLength();
								positions[AxisX] = (projection * Vector4f(0.0f, x, y, 1.0f)).cartesian();
								positions[AxisY] = (projection * Vector4f(x, 0.0f, y, 1.0f)).cartesian();
								positions[AxisZ] = (projection * Vector4f(x, y, 0.0f, 1.0f)).cartesian();
								positions[AxisX].z -= control_position.z;
								positions[AxisY].z -= control_position.z;
								positions[AxisZ].z -= control_position.z;
								for(uint32_t j = 0; j < NumAxes1; j++) {
									if(i > 0 && old_positions[j].z > 0.0f && positions[j].z > 0.0f) {
										float32_t d = get_distance(mouse, old_positions[j].xy, positions[j].xy);
										if(d < getAxisRadius() * 4.0f && min_distance > d) {
											current_axis = (Axis)j;
											min_distance = d;
										}
									}
									old_positions[j] = positions[j];
								}
							}
							
							// circle intersection
							if(isAxisUnknown() && length(mouse - control_position.xy) < getAxisLength()) {
								current_axis = AxisXYZ;
							}
						}
						// scaler axis
						else if(isScaler()) {
							
							// axis intersection
							float32_t max_distance = -Maxf32;
							for(uint32_t i = 0; i < NumAxes1; i++) {
								Vector3f position = Vector3f::zero;
								position[i] = getAxisLength();
								position = (projection * Vector4f(position, 1.0f)).cartesian();
								float32_t d = get_distance(mouse, control_position.xy, position.xy);
								if(max_distance < position.z && d < getAxisRadius() * 4.0f) {
									max_distance = position.z;
									current_axis = (Axis)i;
								}
							}
							
							// handle intersection
							for(uint32_t i = NumAxes1; i < NumAxes2; i++) {
								Rect rect;
								float32_t max_position = -Maxf32;
								const CanvasMesh &mesh = scaler_meshes[i];
								for(uint32_t j = 0; j < mesh.getNumVertices(); j++) {
									Vector3f position = (projection * Vector4f(mesh.getVertexPosition(j), 1.0f)).cartesian();
									max_position = max(max_position, position.z);
									rect.expand(position.x, position.y);
								}
								if(max_distance < max_position && rect.inside(mouse)) {
									max_distance = max_position;
									current_axis = (Axis)i;
								}
							}
							
							// handle intersection
							if(isAxisUnknown() || isScalerUniform()) {
								Rect rect;
								const CanvasMesh &mesh = scaler_meshes[AxisXYZ];
								for(uint32_t j = 0; j < mesh.getNumVertices(); j++) {
									Vector3f position = (projection * Vector4f(mesh.getVertexPosition(j), 1.0f)).cartesian();
									rect.expand(position.x, position.y);
								}
								if(rect.inside(mouse)) {
									current_axis = AxisXYZ;
								}
							}
						}
					}
					
					// axis is focused and mouse is pressed
					if(!isAxisUnknown() && (root.getMouseButtons() & ButtonLeft)) {
						
						// normalize mouse coordinates
						mouse /= Vector2f(viewport_width, viewport_height);
						
						// initialize mouse values
						if(getState() != StatePressed) {
							mouse_projection = Matrix4x4f::translate(control_offset) * projection;
							Vector3d normal = Vector3d::zero;
							if(isTranslator()) {
								if(getAxis() < NumAxes1) {
									normal[getAxis()] = 1.0;
									Vector3d direction = get_direction(mouse);
									normal = normalize(cross(normal, cross(normal, direction)));
								} else if(getAxis() < NumAxes2) {
									normal[getAxis() - AxisYZ] = 1.0;
								}
							} else if(isRotator()) {
								if(getAxis() < NumAxes1) {
									normal[getAxis()] = 1.0;
								} else if(isAxisXYZ()) {
									normal = normalize(get_direction(mouse));
								}
							} else if(isScaler()) {
								if(getAxis() < NumAxes1) {
									normal[getAxis()] = 1.0;
									Vector3d direction = get_direction(mouse);
									normal = normalize(cross(normal, cross(normal, direction)));
								} else if(getAxis() < NumAxes2) {
									normal[getAxis() - AxisYZ] = 1.0;
								} else if(isAxisXYZ()) {
									normal = normalize(get_direction(mouse));
								}
							}
							mouse_position = local_transform.getTranslate();
							mouse_plane = Vector4d(normal, -dot(normal, mouse_position));
							mouse_value = get_intersection(mouse, mouse_plane);
							relative_transform = Matrix4x3d::identity;
							mouse_changed = false;
						}
						
						// set pressed state
						set_state(root, StatePressed);
						
						// save transform
						Matrix4x3d old_transform = getRelativeTransform();
						
						// current value
						Vector3d current_value = get_intersection(mouse, mouse_plane);
						
						// translator
						if(isTranslator()) {
							Vector3d value = Vector3d::zero;
							float64_t mode_step = getModeStep(ModeTranslator);
							Vector3d translate = current_value - mouse_value;
							if(mode_step > 0.0) translate = round_value(translate, mode_step);
							if(getAxis() < NumAxes1) { value[getAxis()] = 1.0; translate *= value; }
							else if(getAxis() < NumAxes2) translate[getAxis() - AxisYZ] = 0.0;
							relative_transform = inverse(local_transform) * Matrix4x3d::translate(translate) * local_transform;
						}
						// rotator
						else if(isRotator()) {
							Vector3d normal = Vector3d(mouse_plane);
							Matrix4x3d local_rotate = local_transform.getRotate();
							float64_t mode_step = getModeStep(ModeRotator);
							if(getAxis() < NumAxes1) {
								Vector3d p0 = mouse_value - mouse_position;
								Vector3d p1 = current_value - mouse_position;
								float64_t angle = atan2(dot(cross(p0, p1), normal), dot(p0, p1)) * Rad2Deg;
								if(angle < 0.0) angle += 360.0;
								if(mode_step > 0.0) angle = round_value(angle, mode_step);
								Matrix4x3d transform = Matrix4x3d::rotate(normal, angle);
								relative_transform = inverse(local_rotate) * transform * local_rotate;
								projection *= Matrix4x4f(transform);
							} else if(isAxisXYZ()) {
								Vector3d tangent, binormal;
								Basis::ortho(normal, tangent, binormal);
								Vector3d translate = current_value - mouse_value;
								float64_t scale = getRotatorSensivity() * length(camera_scale) / projection_scale;
								float64_t angle_x = dot(tangent, translate) * scale;
								float64_t angle_y = dot(binormal, translate) * scale;
								if(mode_step > 0.0) angle_x = round_value(angle_x, mode_step);
								if(mode_step > 0.0) angle_y = round_value(angle_y, mode_step);
								Matrix4x3d transform = Matrix4x3d::rotate(binormal, -angle_x) * Matrix4x3d::rotate(tangent, angle_y);
								relative_transform = inverse(local_rotate) * transform * local_rotate;
								projection *= Matrix4x4f(transform);
							}
						}
						// scaler
						else if(isScaler()) {
							float64_t mode_step = getModeStep(ModeScaler);
							Matrix4x3d local_rotate = normalize(local_transform.getRotate());
							Vector3d scale = (current_value - mouse_value) / abs(mouse_value);
							if(getAxis() < NumAxes2) {
								Vector3d value = Vector3d::zero;
								if(getAxis() < NumAxes1) { value[getAxis()] = 1.0; scale *= value; }
								else if(getAxis() < NumAxes2) scale[getAxis() - AxisYZ] = 0.0;
							} else if(isAxisXYZ()) {
								scale = Vector3d(dot(scale, normalize(mouse_value - mouse_position)));
							}
							scale = scale / max(Vector3d(1.0) - scale, Vector3d(1.0));
							if(mode_step > 0.0) {
								Quaterniond current_rotate;
								Vector3d current_translate, current_scale;
								Matrix4x3d current_transform = local_transform * inverse(local_rotate) * Matrix4x3d::scale(scale + 1.0) * local_rotate;
								current_transform.getComponents(current_translate, current_rotate, current_scale);
								current_scale = max(round_value(current_scale, mode_step), Vector3d(mode_step));
								current_transform = Matrix4x3d::compose(current_translate, current_rotate, current_scale);
								relative_transform = inverse(local_transform) * current_transform;
							} else {
								relative_transform = inverse(local_rotate) * Matrix4x3d::scale(scale + 1.0) * local_rotate;
							}
						}
						
						// changed callback
						if(old_transform != relative_transform) {
							if(changed_func) changed_func(this);
							mouse_changed = true;
						}
					}
					else {
						
						// clicked callback
						if(getState() == StatePressed) {
							if(clicked_func) clicked_func(this);
							ret = true;
						}
						
						// reset transform
						relative_transform = Matrix4x3d::identity;
						set_state(root, StateFocused);
						mouse_changed = false;
					}
				} else {
					set_state(root, StateNormal);
					current_axis = AxisUnknown;
				}
			} else {
				set_state(root, StateNormal);
				current_axis = AxisUnknown;
			}
		} else {
			set_state(root, StateDisabled);
			current_axis = AxisUnknown;
		}
		
		// update manipulator region
		projection = Matrix4x4f::translate(control_offset) * projection;
		control_position.xy += control_offset.xy;
		
		// set scissor
		int32_t order = Mini16;
		scissor_mesh.setOrder(order++);
		scissor_mesh.setEnabled(isEnabled());
		scissor_mesh.setScissor(region, CanvasElement::StackPush | CanvasElement::StackMul);
		
		// translator elements
		if(isTranslator() && control_position.z > 0.0f) {
			
			// create translator positions
			Vector3f positions[NumAxes1];
			float32_t length = getAxisLength() - getArrowRadius();
			positions[AxisX] = (projection * Vector4f(length, 0.0f, 0.0f, 1.0f)).cartesian();
			positions[AxisY] = (projection * Vector4f(0.0f, length, 0.0f, 1.0f)).cartesian();
			positions[AxisZ] = (projection * Vector4f(0.0f, 0.0f, length, 1.0f)).cartesian();
			
			// translator distances
			float32_t distances[NumAxes2];
			distances[AxisX] = positions[AxisX].z;
			distances[AxisY] = positions[AxisY].z;
			distances[AxisZ] = positions[AxisZ].z;
			distances[AxisYZ] = (projection * Vector4f(0.0f, getHandleOffset(), getHandleOffset(), 1.0f)).cartesian().z;
			distances[AxisXZ] = (projection * Vector4f(getHandleOffset(), 0.0f, getHandleOffset(), 1.0f)).cartesian().z;
			distances[AxisXY] = (projection * Vector4f(getHandleOffset(), getHandleOffset(), 0.0f, 1.0f)).cartesian().z;
			
			// sort meshes by distance
			uint32_t axis_order[NumAxes2];
			for(uint32_t i = 0; i < NumAxes2; i++) axis_order[i] = i;
			quickSort(distances, axis_order, NumAxes2);
			
			// update elements
			relative_strip.setOrder(order++);
			for(uint32_t i = 0; i < NumAxes2; i++) {
				bool enabled = isEnabled();
				if(enabled && mouse_changed) {
					if(getAxis() < NumAxes1) {
						enabled = (i == (uint32_t)getAxis());
					} else if(getAxis() < NumAxes2) {
						if(i < NumAxes1) {
							enabled = (NumAxes1 + i != (uint32_t)getAxis());
						} else {
							enabled = (i == (uint32_t)getAxis());
						}
					}
				}
				translator_meshes[axis_order[i]].setOrder(order++);
				translator_meshes[i].setColor(getAxisColor((Axis)i) * ((i == (uint32_t)getAxis()) ? getEnabledColor() : getDisabledColor()));
				translator_meshes[i].setTransform(projection);
				translator_meshes[i].setEnabled(enabled);
			}
			for(uint32_t i = 0; i < NumAxes1; i++) {
				translator_strips[i].clearPositions();
				translator_strips[i].addPosition(positions[i]);
				translator_strips[i].addPosition(control_position);
				translator_strips[i].setEnabled(translator_meshes[i].isEnabled());
				translator_strips[i].setOrder(translator_meshes[i].getOrder());
				translator_strips[i].setColor(translator_meshes[i].getColor());
			}
			
			// relative strip
			if(mouse_changed && getState() == StatePressed) {
				relative_strip.clearPositions();
				relative_strip.addPosition((mouse_projection * Vector4f(0.0f, 0.0f, 0.0f, 1.0f)).cartesian());
				relative_strip.addPosition((projection * Vector4f(0.0f, 0.0f, 0.0f, 1.0f)).cartesian());
				relative_strip.setColor(getAxisColor(getAxis()));
				relative_strip.setWidth(getAxisRadius());
				relative_strip.setEnabled(isEnabled());
			}
		}
		// rotator elements
		else if(isRotator() && control_position.z > 0.0f) {
			
			// create rotator positions
			Vector3f positions[NumAxes1][RotatorSteps];
			for(uint32_t i = 0; i < RotatorSteps; i++) {
				float32_t x, y, angle = Pi2 * i / (RotatorSteps - 1);
				sincosFast(angle, x, y); x *= getAxisLength(); y *= getAxisLength();
				positions[AxisX][i] = (projection * Vector4f(0.0f, x, y, 1.0f)).cartesian();
				positions[AxisY][i] = (projection * Vector4f(x, 0.0f, y, 1.0f)).cartesian();
				positions[AxisZ][i] = (projection * Vector4f(x, y, 0.0f, 1.0f)).cartesian();
				positions[AxisX][i].z -= control_position.z;
				positions[AxisY][i].z -= control_position.z;
				positions[AxisZ][i].z -= control_position.z;
			}
			
			// update elements
			rotator_ellipse.setOrder(order++);
			for(uint32_t i = 0; i < NumAxes1; i++) {
				rotator_strips[i].clearPositions();
				rotator_strips[i].setOrder(order++);
				rotator_strips[i].setColor(getAxisColor((Axis)i) * ((i == (uint32_t)getAxis()) ? getEnabledColor() : getDisabledColor()));
				rotator_strips[i].setEnabled(isEnabled());
			}
			if(isAxisXYZ()) {
				rotator_ellipse.setRadius(getAxisLength());
				rotator_ellipse.setPosition(control_position);
				rotator_ellipse.setColor(getAxisColor(AxisXYZ));
				rotator_ellipse.setEnabled(isEnabled());
			}
			
			// wrap strip positions
			for(uint32_t i = 0; i < NumAxes1; i++) {
				const Vector3f *p = positions[i];
				if(mouse_changed && i == (uint32_t)getAxis()) {
					for(uint32_t j = 0; j < RotatorSteps; j++) {
						rotator_strips[i].addPosition(p[j]);
					}
					continue;
				}
				Vector3f p0 = positions[i][0];
				for(uint32_t j = 1; j < RotatorSteps * 2; j++) {
					Vector3f p1 = p[j % RotatorSteps];
					if(p0.z <= 0.0f && p1.z > 0.0f) {
						rotator_strips[i].addPosition(lerp(p0, p1, p0.z / (p0.z - p1.z)));
						for(j++; j < RotatorSteps * 2; j++) {
							p1 = p[j % RotatorSteps];
							if(p1.z < 0.0f) {
								rotator_strips[i].addPosition(lerp(p0, p1, p0.z / (p0.z - p1.z)));
								break;
							}
							rotator_strips[i].addPosition(p1);
							p0 = p1;
						}
						break;
					}
					p0 = p1;
				}
			}
			
			// relative strip
			if(mouse_changed && getState() == StatePressed && !isAxisXYZ()) {
				relative_strip.clearPositions();
				Matrix4x3f local_rotate = Matrix4x3f(local_transform).getRotate();
				Vector3f p0 = normalize(Vector3f(mouse_value - mouse_position)) * getAxisLength();
				Vector3f p1 = inverse(local_rotate * Matrix4x3f(getRelativeTransform()) * inverse(local_rotate)) * p0;
				relative_strip.addPosition((projection * Vector4f(p0, 1.0f)).cartesian());
				relative_strip.addPosition(control_position);
				relative_strip.addPosition((projection * Vector4f(p1, 1.0f)).cartesian());
				relative_strip.setColor(getAxisColor(getAxis()));
				relative_strip.setWidth(getAxisRadius() * 2.0f);
				relative_strip.setEnabled(isEnabled());
			}
		}
		// scaler elements
		else if(isScaler() && control_position.z > 0.0f) {
			
			// create scaler positions
			Vector3f positions[NumAxes1];
			float32_t length = getAxisLength() - getArrowRadius();
			positions[AxisX] = (projection * Vector4f(length, 0.0f, 0.0f, 1.0f)).cartesian();
			positions[AxisY] = (projection * Vector4f(0.0f, length, 0.0f, 1.0f)).cartesian();
			positions[AxisZ] = (projection * Vector4f(0.0f, 0.0f, length, 1.0f)).cartesian();
			
			// scaler distances
			float32_t distances[NumAxes2];
			distances[AxisX] = positions[AxisX].z;
			distances[AxisY] = positions[AxisY].z;
			distances[AxisZ] = positions[AxisZ].z;
			distances[AxisYZ] = (projection * Vector4f(0.0f, getHandleOffset(), getHandleOffset(), 1.0f)).cartesian().z;
			distances[AxisXZ] = (projection * Vector4f(getHandleOffset(), 0.0f, getHandleOffset(), 1.0f)).cartesian().z;
			distances[AxisXY] = (projection * Vector4f(getHandleOffset(), getHandleOffset(), 0.0f, 1.0f)).cartesian().z;
			
			// sort meshes by distance
			uint32_t axis_order[NumAxes2];
			for(uint32_t i = 0; i < NumAxes2; i++) axis_order[i] = i;
			quickSort(distances, axis_order, NumAxes2);
			
			// update elements
			scaler_meshes[AxisXYZ].setOrder(order++);
			for(uint32_t i = 0; i < NumAxes2; i++) {
				bool enabled = isEnabled();
				if(enabled && mouse_changed) {
					if(getAxis() < NumAxes1) {
						enabled = (i == (uint32_t)getAxis());
					} else if(getAxis() < NumAxes2) {
						if(i < NumAxes1) {
							enabled = (NumAxes1 + i != (uint32_t)getAxis());
						} else {
							enabled = (i == (uint32_t)getAxis());
						}
					}
				}
				scaler_meshes[axis_order[i]].setOrder(order++);
				scaler_meshes[i].setColor(getAxisColor((Axis)i) * ((i == (uint32_t)getAxis()) ? getEnabledColor() : getDisabledColor()));
				scaler_meshes[i].setTransform(projection);
				scaler_meshes[i].setEnabled(enabled);
			}
			if(isAxisXYZ()) {
				scaler_meshes[AxisXYZ].setColor(getAxisColor(AxisXYZ));
				scaler_meshes[AxisXYZ].setTransform(projection);
				scaler_meshes[AxisXYZ].setEnabled(isEnabled());
			}
			for(uint32_t i = 0; i < NumAxes1; i++) {
				scaler_strips[i].clearPositions();
				scaler_strips[i].addPosition(positions[i]);
				scaler_strips[i].addPosition(control_position);
				scaler_strips[i].setEnabled(scaler_meshes[i].isEnabled());
				scaler_strips[i].setOrder(scaler_meshes[i].getOrder());
				scaler_strips[i].setColor(scaler_meshes[i].getColor());
			}
			
			// relative strip
			if(mouse_changed && getState() == StatePressed) {
				relative_strip.clearPositions();
				relative_strip.addPosition((mouse_projection * Vector4f(0.0f, 0.0f, 0.0f, 1.0f)).cartesian());
				relative_strip.addPosition((projection * Vector4f(0.0f, 0.0f, 0.0f, 1.0f)).cartesian());
				relative_strip.setColor(getAxisColor(getAxis()));
				relative_strip.setWidth(getAxisRadius());
				relative_strip.setEnabled(isEnabled());
			}
		}
		
		// restore scissor
		restore_mesh.setOrder(order++);
		restore_mesh.setEnabled(isEnabled());
		restore_mesh.setScissor(CanvasElement::StackPop);
		
		return ret;
	}
}

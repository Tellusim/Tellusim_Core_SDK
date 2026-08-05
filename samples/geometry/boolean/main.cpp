// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <math/TellusimMath.h>
#include <format/TellusimMesh.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>
#include <graphics/TellusimMeshModel.h>
#include <geometry/TellusimMeshBoolean.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Boolean", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// structures
	struct Vertex {
		float32_t position[3];
		float32_t normal[3];
	};
	
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Matrix4x4f transform;
		Vector4f camera;
		Color color;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create target
	Target target = device.createTarget(window);
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, offsetof(Vertex, position), sizeof(Vertex));
	pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, offsetof(Vertex, normal), sizeof(Vertex));
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	pipeline.setCullMode(target.isFlipped() ? Pipeline::CullModeFront : Pipeline::CullModeBack);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create wireframe pipeline
	Pipeline wireframe_pipeline = device.createPipeline(pipeline);
	wireframe_pipeline.setPrimitive(Pipeline::PrimitiveLine);
	if(!wireframe_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1; WIREFRAME_SHADER=1")) return 1;
	if(!wireframe_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1; WIREFRAME_SHADER=1")) return 1;
	if(!wireframe_pipeline.create()) return 1;
	
	// load mesh
	Mesh src_mesh;
	if(!src_mesh.load("model.mesh") || src_mesh.getNumGeometries() != 4) return 1;
	
	// create models
	MeshModel src_models[32];
	for(uint32_t i = 0; i < src_mesh.getNumGeometries(); i++) {
		if(!src_models[i].create(device, pipeline, src_mesh.getGeometry(i))) return 1;
	}
	
	// intersection models
	MeshModel dest_model_0;
	MeshModel dest_model_1;
	MeshModel dest_line_model_0;
	MeshModel dest_line_model_1;
	
	// create canvas
	Canvas canvas;
	
	// create panel
	ControlRoot root(canvas, true);
	ControlPanel panel(&root, 1, 8.0f, 8.0f);
	panel.setAlign(Control::AlignRightTop);
	panel.setPosition(-8.0f, -8.0f);
	
	// create controls
	ControlSlider angle_x_slider(&panel, "Angle X", 2, 0.0, -180.0, 180.0);
	angle_x_slider.setSize(192.0f, 0.0f);
	
	ControlSlider angle_y_slider(&panel, "Angle Y", 2, 90.0, -180.0, 180.0);
	angle_y_slider.setSize(192.0f, 0.0f);
	
	ControlSlider angle_z_slider(&panel, "Angle Z", 2, 0.0, -180.0, 180.0);
	angle_z_slider.setSize(192.0f, 0.0f);
	
	ControlSlider offset_slider(&panel, "Offset", 2, 0.0, -0.5, 0.5);
	offset_slider.setSize(192.0f, 0.0f);
	
	ControlSlider scale_slider(&panel, "Scale", 2, 1.0, 0.5, 2.0);
	scale_slider.setSize(192.0f, 0.0f);
	
	ControlCombo src_0_combo(&panel, { "Box", "Dodeca", "Sphere", "Knot" }, 1);
	src_0_combo.setAlign(Control::AlignExpandX);
	
	ControlCombo src_1_combo(&panel, { "Box", "Dodeca", "Sphere", "Knot" }, 1);
	src_1_combo.setAlign(Control::AlignExpandX);
	
	ControlCombo op_combo(&panel, { "Union", "Difference", "Intersection" }, 0);
	op_combo.setAlign(Control::AlignExpandX);
	
	ControlCheck wireframe_check(&panel, "Wireframe");
	
	ControlCheck animation_check(&panel, "Animation", true);
	
	ControlText info_text(&panel);
	
	// changed callback
	auto changed_func = [&]() {
		
		// object indices
		uint32_t src_0_index = src_0_combo.getCurrentIndex();
		uint32_t src_1_index = src_1_combo.getCurrentIndex();
		
		// transform geometry
		MeshGeometry src_geometry_1 = src_mesh.getGeometry(src_1_index).clonePtr();
		Matrix4x3d transform = Matrix4x3d::translate(offset_slider.getValue(), 0.0, 0.0) * Matrix4x3d::scale(scale_slider.getValue());
		transform *= Matrix4x3d::rotateZ(angle_z_slider.getValue()) * Matrix4x3d::rotateY(angle_y_slider.getValue()) * Matrix4x3d::rotateX(angle_x_slider.getValue());
		src_geometry_1.setTransform(Matrix4x3f(transform), true);
		
		// geometry intersection
		MeshGeometry dest_geometry_0;
		MeshGeometry dest_geometry_1;
		uint64_t dest_begin = Time::current();
		MeshBoolean::Operation op = MeshBoolean::OpUnion;
		if(op_combo.getCurrentText() == "Difference") op = MeshBoolean::OpDifference;
		else if(op_combo.getCurrentText() == "Intersection") op = MeshBoolean::OpIntersection;
		MeshBoolean::intersect(dest_geometry_0, dest_geometry_1, src_mesh.getGeometry(src_0_index), src_geometry_1, op);
		uint64_t dest_end = Time::current();
		
		// intersection models
		Mesh dest_mesh_0;
		Mesh dest_mesh_1;
		dest_mesh_0.addGeometry(dest_geometry_0);
		dest_mesh_1.addGeometry(dest_geometry_1);
		if(dest_model_0.create(device, pipeline, dest_mesh_0) && dest_model_1.create(device, pipeline, dest_mesh_1)) {
			String info;
			info += String::format("Boolean: %s\n", String::fromTime(dest_end - dest_begin).get());
			info += String::format("Vertices: %u -> %u\n", src_models[src_0_index].getNumVertices() + src_models[src_1_index].getNumVertices(), dest_model_0.getNumVertices() + dest_model_0.getNumVertices());
			info += String::format("Indices: %u -> %u", src_models[src_0_index].getNumIndices() + src_models[src_1_index].getNumIndices(), dest_model_0.getNumIndices() + dest_model_1.getNumIndices());
			info_text.setText(info);
		}
		dest_line_model_0.create(device, wireframe_pipeline, dest_mesh_0);
		dest_line_model_1.create(device, wireframe_pipeline, dest_mesh_1);
		
		// save mesh
		//dest_mesh.save("model_boolean.glb");
	};
	angle_x_slider.setChangedCallback([&](ControlSlider slider) { changed_func(); });
	angle_y_slider.setChangedCallback([&](ControlSlider slider) { changed_func(); });
	angle_z_slider.setChangedCallback([&](ControlSlider slider) { changed_func(); });
	offset_slider.setChangedCallback([&](ControlSlider slider) { changed_func(); });
	scale_slider.setChangedCallback([&](ControlSlider slider) { changed_func(); });
	src_0_combo.setChangedCallback([&](ControlCombo combo) { changed_func(); });
	src_1_combo.setChangedCallback([&](ControlCombo combo) { changed_func(); });
	op_combo.setChangedCallback([&](ControlCombo combo) { changed_func(); });
	
	// update model
	changed_func();
	
	float32_t animation_time = 0.0f;
	float32_t old_animation_time = 0.0f;
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// update keyboard
		if(window.getKeyboardKey('w', true)) wireframe_check.switchChecked();
		if(window.getKeyboardKey(' ', true)) animation_check.switchChecked();
		
		// update controls
		update_controls(window, root);
		canvas.create(device, target);
		
		// animation time
		if(animation_check.isChecked()) animation_time += time - old_animation_time;
		old_animation_time = time;
		
		// window target
		target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// set pipeline
			command.setPipeline(pipeline);
			
			// set common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Vector4f(1.5f, 0.0f, 0.5f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
			common_parameters.transform = Matrix4x4f::rotateX(animation_time * 8.0f) * Matrix4x4f::rotateZ(animation_time * 16.0f);
			common_parameters.color = Color::white;
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			command.setUniform(0, common_parameters);
			
			// draw model
			if(window.getKeyboardKey('1')) {
				src_models[0].setBuffers(command);
				src_models[0].draw(command);
			} else if(window.getKeyboardKey('2')) {
				src_models[1].setBuffers(command);
				src_models[1].draw(command);
			} else if(window.getKeyboardKey('3')) {
				src_models[2].setBuffers(command);
				src_models[2].draw(command);
			} else if(window.getKeyboardKey('4')) {
				src_models[3].setBuffers(command);
				src_models[3].draw(command);
			}
			else {
				
				// first model
				if(dest_model_0.isCreated()) {
					dest_model_0.setBuffers(command);
					dest_model_0.draw(command);
				}
				
				// second model
				if(dest_model_1.isCreated()) {
					common_parameters.color = Color(1.0f, 0.25f, 0.25f, 1.0f);
					command.setUniform(0, common_parameters);
					dest_model_1.setBuffers(command);
					dest_model_1.draw(command);
				}
				
				// wireframe mode
				if(wireframe_check.isChecked()) {
					command.setPipeline(wireframe_pipeline);
					command.setUniform(0, common_parameters);
					if(dest_line_model_0.isCreated()) {
						dest_line_model_0.setBuffers(command);
						dest_line_model_0.draw(command);
					}
					if(dest_line_model_1.isCreated()) {
						dest_line_model_1.setBuffers(command);
						dest_line_model_1.draw(command);
					}
				}
			}
			
			// draw canvas
			canvas.draw(command, target);
		}
		target.end();
		
		if(!window.present()) return false;
		
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}

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
#include <geometry/TellusimMeshSplit.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Split", window.getPlatformName());
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
	if(!src_mesh.load("model.mesh")) return 1;
	
	// create normals
	src_mesh.createNormals(45.0f);
	
	// create model
	MeshModel src_model;
	if(!src_model.create(device, pipeline, src_mesh)) return 1;
	
	// split models
	MeshModel front_model;
	MeshModel cross_model;
	MeshModel front_line_model;
	MeshModel cross_line_model;
	
	// create canvas
	Canvas canvas;
	
	// create panel
	ControlRoot root(canvas, true);
	ControlPanel panel(&root, 1, 8.0f, 8.0f);
	panel.setAlign(Control::AlignRightTop);
	panel.setPosition(-8.0f, -8.0f);
	
	// create controls
	ControlSlider angle_x_slider(&panel, "Angle X", 2, 0.0f, -180.0f, 180.0f);
	angle_x_slider.setSize(192.0f, 0.0f);
	
	ControlSlider angle_y_slider(&panel, "Angle Y", 2, 0.0f, -180.0f, 180.0f);
	angle_y_slider.setSize(192.0f, 0.0f);
	
	ControlSlider offset_slider(&panel, "Offset", 2, 0.0f, -4.0f, 4.0f);
	offset_slider.setSize(192.0f, 0.0f);
	
	ControlCheck wireframe_check(&panel, "Wireframe");
	
	ControlCheck animation_check(&panel, "Animation", true);
	
	ControlText info_text(&panel);
	
	// changed callback
	ControlSlider::ChangedCallback changed_func = ControlSlider::ChangedCallback([&](ControlSlider slider) {
		
		// split mesh
		Mesh front_mesh;
		Mesh cross_mesh;
		Mesh back_mesh = Mesh::null;
		uint64_t split_begin = Time::current();
		Matrix4x3f basis = Matrix4x3f::translate(0.0f, 0.0f, offset_slider.getValuef32());
		basis *= Matrix4x3f::rotateY(angle_y_slider.getValuef32()) * Matrix4x3f::rotateX(angle_x_slider.getValuef32());
		MeshSplit::split(front_mesh, cross_mesh, back_mesh, src_mesh, basis);
		uint64_t split_end = Time::current();
		
		// split models
		if(front_model.create(device, pipeline, front_mesh) && cross_model.create(device, pipeline, cross_mesh)) {
			String info;
			info += String::format("Split: %s\n", String::fromTime(split_end - split_begin).get());
			info += String::format("Vertices: %u -> %u\n", src_model.getNumVertices(), front_model.getNumVertices() + cross_model.getNumVertices());
			info += String::format("Indices: %u -> %u", src_model.getNumIndices(), front_model.getNumIndices() + cross_model.getNumIndices());
			info_text.setText(info);
		}
		front_line_model.create(device, wireframe_pipeline, front_mesh);
		cross_line_model.create(device, wireframe_pipeline, cross_mesh);
		
		// save mesh
		//front_mesh.save("model_front.glb");
		//cross_mesh.save("model_cross.glb");
	});
	angle_x_slider.setChangedCallback(changed_func);
	angle_y_slider.setChangedCallback(changed_func);
	offset_slider.setChangedCallback(changed_func);
	
	// split model
	changed_func.run();
	
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
			common_parameters.camera = Vector4f(5.0f, 0.0f, -15.0f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
			common_parameters.transform = Matrix4x4f::rotateX(animation_time * 8.0f) * Matrix4x4f::rotateZ(animation_time * 16.0f);
			common_parameters.color = Color::white;
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			command.setUniform(0, common_parameters);
			
			// draw model
			if(window.getKeyboardKey('1')) {
				src_model.setBuffers(command);
				src_model.draw(command);
			}
			else {
				
				// front model
				command.setUniform(0, common_parameters);
				if(front_model.isCreated()) {
					front_model.setBuffers(command);
					front_model.draw(command);
				}
				
				// cross model
				if(cross_model.isCreated()) {
					common_parameters.color = Color(1.0f, 0.25f, 0.25f, 1.0f);
					command.setUniform(0, common_parameters);
					cross_model.setBuffers(command);
					cross_model.draw(command);
				}
				
				// wireframe mode
				if(wireframe_check.isChecked()) {
					command.setPipeline(wireframe_pipeline);
					command.setUniform(0, common_parameters);
					if(front_line_model.isCreated()) {
						front_line_model.setBuffers(command);
						front_line_model.draw(command);
					}
					if(cross_line_model.isCreated()) {
						cross_line_model.setBuffers(command);
						cross_line_model.draw(command);
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

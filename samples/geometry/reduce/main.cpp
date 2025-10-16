// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <math/TellusimMath.h>
#include <format/TellusimMesh.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>
#include <graphics/TellusimMeshModel.h>
#include <geometry/TellusimMeshReduce.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Reduce", window.getPlatformName());
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
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, offsetof(Vertex, position), sizeof(Vertex));
	pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, offsetof(Vertex, normal), sizeof(Vertex));
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create wireframe pipeline
	Pipeline wireframe_pipeline = device.createPipeline(pipeline);
	wireframe_pipeline.setFillMode(Pipeline::FillModeLine);
	if(!wireframe_pipeline.create()) return 1;
	
	// load mesh
	Mesh src_mesh;
	if(!src_mesh.load("model.glb")) return 1;
	
	// create normals
	src_mesh.createNormals();
	
	// create model
	MeshModel src_model;
	if(!src_model.create(device, pipeline, src_mesh)) return 1;
	
	// collapse model
	MeshModel collapse_model;
	
	// create target
	Target target = device.createTarget(window);
	
	// create canvas
	Canvas canvas;
	
	// create panel
	ControlRoot root(canvas, true);
	ControlPanel panel(&root, 1, 8.0f, 8.0f);
	panel.setAlign(Control::AlignRightTop);
	panel.setPosition(-8.0f, -8.0f);
	
	// create controls
	ControlSlider ratio_slider(&panel, "Ratio", 3, 0.1f, 0.0f, 1.0f);
	ratio_slider.setSize(192.0f, 0.0f);
	
	ControlSlider threshold_slider(&panel, "Threshold", 3, 1.0f, 0.0f, 2.0f);
	threshold_slider.setSize(192.0f, 0.0f);
	
	ControlCheck wireframe_check(&panel, "Wireframe");
	
	ControlText info_text(&panel);
	
	// changed callback
	ControlSlider::ChangedCallback changed_func = ControlSlider::ChangedCallback([&](ControlSlider slider) {
		
		// collapse mesh
		Mesh collapse_mesh;
		uint64_t collapse_begin = Time::current();
		MeshReduce::collapse(collapse_mesh, src_mesh, ratio_slider.getValuef32(), threshold_slider.getValuef32() * 0.001f);
		uint64_t collapse_end = Time::current();
		
		// collapse model
		if(collapse_model.create(device, pipeline, collapse_mesh)) {
			String info;
			info += String::format("Collapse: %s\n", String::fromTime(collapse_end - collapse_begin).get());
			info += String::format("Vertices: %u -> %u\n", src_model.getNumVertices(), collapse_model.getNumVertices());
			info += String::format("Indices: %u -> %u", src_model.getNumIndices(), collapse_model.getNumIndices());
			info_text.setText(info);
		}
		
		// save mesh
		//collapse_mesh.save("model_collapse.glb");
	});
	ratio_slider.setChangedCallback(changed_func);
	threshold_slider.setChangedCallback(changed_func);
	
	// collapse model
	changed_func.run();
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// update controls
		update_controls(window, root);
		canvas.create(device, target);
		
		// window target
		target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// set pipeline
			command.setPipeline((wireframe_check.isChecked()) ? wireframe_pipeline : pipeline);
			
			// set common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Vector4f(2.0f, 2.0f, 1.0f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
			common_parameters.transform = Matrix4x4f::rotateX(time * 8.0f) * Matrix4x4f::rotateZ(time * 16.0f);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			command.setUniform(0, common_parameters);
			
			// draw model
			if(window.getKeyboardKey('1')) {
				src_model.setBuffers(command);
				src_model.draw(command);
			} else {
				collapse_model.setBuffers(command);
				collapse_model.draw(command);
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

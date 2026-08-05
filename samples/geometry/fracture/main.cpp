// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <core/TellusimAsync.h>
#include <math/TellusimMath.h>
#include <math/TellusimRandom.h>
#include <format/TellusimMesh.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>
#include <graphics/TellusimMeshModel.h>
#include <geometry/TellusimMeshFracture.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Fracture", window.getPlatformName());
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
	MeshModel src_line_models[32];
	for(uint32_t i = 0; i < src_mesh.getNumGeometries(); i++) {
		if(!src_models[i].create(device, pipeline, src_mesh.getGeometry(i))) return 1;
		if(!src_line_models[i].create(device, wireframe_pipeline, src_mesh.getGeometry(i))) return 1;
	}
	
	// fracture model
	Mesh dest_mesh;
	MeshModel dest_model;
	MeshModel dest_line_model;
	
	// create canvas
	Canvas canvas;
	
	// create panel
	ControlRoot root(canvas, true);
	ControlPanel panel(&root, 1, 8.0f, 8.0f);
	panel.setAlign(Control::AlignRightTop);
	panel.setPosition(-8.0f, -8.0f);
	
	// create controls
	ControlSlider shards_slider(&panel, "Shards", 32, 2, 64);
	shards_slider.setSize(192.0f, 0.0f);
	
	ControlSlider angle_slider(&panel, "Angle", 2, 0.0, -180.0, 180.0);
	angle_slider.setSize(192.0f, 0.0f);
	
	ControlSlider power_slider(&panel, "Power", 2, 1.0, 0.2, 2.0);
	power_slider.setSize(192.0f, 0.0f);
	
	ControlSlider offset_slider(&panel, "Offset", 2, 0.5, 0.0, 1.0);
	offset_slider.setSize(192.0f, 0.0f);
	
	ControlCombo src_combo(&panel, { "Solid Dodeca", "Hollow Dodeca", "Solid Sphere", "Hollow Sphere" }, 0);
	src_combo.setAlign(Control::AlignExpandX);
	
	ControlCheck wireframe_check(&panel, "Wireframe");
	
	ControlCheck animation_check(&panel, "Animation", true);
	
	ControlText info_text(&panel);
	
	// create async
	#if !_EMSCRIPTEN
		Async async;
		if(!async.init()) return 1;
	#endif
	
	// changed callback
	auto changed_func = [&]() {
		
		using Tellusim::abs;
		using Tellusim::pow;
		
		// object index
		uint32_t src_index = src_combo.getCurrentIndex();
		
		// fracture transform
		Matrix4x3f transform = Matrix4x3f::rotateX(angle_slider.getValuef32());
		
		// fracture points
		ArrayStack<Vector3f, 1024> points;
		Random<Vector3i, Vector3f> random(Vector3i(3, 5, 7));
		for(uint32_t i = 0; i < shards_slider.getValueu32(); i++) {
			Vector3f point = transform * (random.getf32() * 1.0f - 0.5f);
			point.x = sign(point.x) * pow(abs(point.x), power_slider.getValuef32());
			point.y = sign(point.y) * pow(abs(point.y), power_slider.getValuef32());
			point.z = sign(point.z) * pow(abs(point.z), power_slider.getValuef32());
			points.append(point);
		}
		
		// fracture mesh
		uint64_t dest_begin = Time::current();
		ArrayStack<MeshGeometry, 1024> dest_geometries;
		#if !_EMSCRIPTEN
			MeshFracture::split(dest_geometries, src_mesh.getGeometry(src_index), points.get(), points.size(), Vector2f::one, 1e-3f, 1e-3f, 1e-3f, &async);
		#else
			MeshFracture::split(dest_geometries, src_mesh.getGeometry(src_index), points.get(), points.size());
		#endif
		uint64_t dest_end = Time::current();
		
		// fracture model (empty materials are required to create model with materials)
		dest_mesh = Mesh();
		for(MeshGeometry &geometry : dest_geometries) {
			MeshMaterial material_0(geometry);
			MeshMaterial material_1(geometry);
			dest_mesh.addGeometry(geometry);
		}
		if(dest_model.create(device, pipeline, dest_mesh)) {
			String info;
			info += String::format("Fracture: %s\n", String::fromTime(dest_end - dest_begin).get());
			info += String::format("Vertices: %u -> %u\n", src_models[src_index].getNumVertices(), dest_model.getNumVertices());
			info += String::format("Indices: %u -> %u", src_models[src_index].getNumIndices(), dest_model.getNumIndices());
			info_text.setText(info);
		}
		dest_line_model.create(device, wireframe_pipeline, dest_mesh);
		
		// save mesh
		//dest_mesh.save("model_fracture.glb");
	};
	shards_slider.setChangedCallback([&](ControlSlider slider) { changed_func(); });
	angle_slider.setChangedCallback([&](ControlSlider slider) { changed_func(); });
	power_slider.setChangedCallback([&](ControlSlider slider) { changed_func(); });
	src_combo.setChangedCallback([&](ControlCombo combo) { changed_func(); });
	
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
			if(offset_slider.getValuef32() == 0.0f) {
				uint32_t index = src_combo.getCurrentIndex();
				src_models[index].setBuffers(command);
				src_models[index].draw(command);
				if(wireframe_check.isChecked()) {
					command.setPipeline(wireframe_pipeline);
					command.setUniform(0, common_parameters);
					src_line_models[index].setBuffers(command);
					src_line_models[index].draw(command);
				}
			}
			else {
				
				// fracture model
				dest_model.setBuffers(command);
				float32_t offset = offset_slider.getValuef32() * (Tellusim::sin(animation_time * 2.0f) * 0.5f + 0.5f);
				Matrix4x4f transform = common_parameters.transform;
				for(uint32_t i = 0; i < dest_mesh.getNumGeometries(); i++) {
					BoundBoxf bound_box = dest_mesh.getGeometry(i).getBoundBox();
					common_parameters.transform = transform * Matrix4x4f::translate(bound_box.getCenter() * offset);
					common_parameters.color = Color::white;
					command.setUniform(0, common_parameters);
					dest_model.draw(command, i, 0);
					if(dest_model.getNumMaterials(0) == 2) {
						common_parameters.color = Color(1.0f, 0.25f, 0.25f, 1.0f);
						command.setUniform(0, common_parameters);
						dest_model.draw(command, i, 1);
					}
				}
				
				// wireframe mode
				if(wireframe_check.isChecked()) {
					command.setPipeline(wireframe_pipeline);
					command.setUniform(0, common_parameters);
					dest_line_model.setBuffers(command);
					for(uint32_t i = 0; i < dest_mesh.getNumGeometries(); i++) {
						BoundBoxf bound_box = dest_mesh.getGeometry(i).getBoundBox();
						common_parameters.transform = transform * Matrix4x4f::translate(bound_box.getCenter() * offset);
						command.setUniform(0, common_parameters);
						dest_line_model.draw(command, i);
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

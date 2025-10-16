// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimMath.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Geometry", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	const uint32_t grid_size = 64;
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Matrix4x4f transform;
		Vector4f camera;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create vertex pipeline
	Pipeline vertex_pipeline;
	vertex_pipeline = device.createPipeline();
	vertex_pipeline.setUniformMask(0, Shader::MaskVertex);
	vertex_pipeline.setColorFormat(window.getColorFormat());
	vertex_pipeline.setDepthFormat(window.getDepthFormat());
	vertex_pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!vertex_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1; VERTEX_MODE=1; GRID_SIZE=%uu", grid_size)) return 1;
	if(!vertex_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!vertex_pipeline.create()) return 1;
	
	// create geometry pipeline
	Pipeline geometry_pipeline;
	if(device.hasShader(Shader::TypeGeometry)) {
		geometry_pipeline = device.createPipeline();
		geometry_pipeline.setUniformMask(0, Shader::MaskGeometry);
		geometry_pipeline.setColorFormat(window.getColorFormat());
		geometry_pipeline.setDepthFormat(window.getDepthFormat());
		geometry_pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
		geometry_pipeline.setPrimitive(Pipeline::PrimitivePoint);
		if(!geometry_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1; GEOMETRY_MODE=1; GRID_SIZE=%uu", grid_size)) return 1;
		if(!geometry_pipeline.loadShaderGLSL(Shader::TypeGeometry, "main.shader", "GEOMETRY_SHADER=1")) return 1;
		if(!geometry_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
		if(!geometry_pipeline.create()) return 1;
	}
	
	// create mesh pipeline
	Pipeline mesh_pipeline;
	if(device.hasShader(Shader::TypeTask)) {
		mesh_pipeline = device.createPipeline();
		mesh_pipeline.setUniformMask(0, Shader::MaskMesh);
		mesh_pipeline.setColorFormat(window.getColorFormat());
		mesh_pipeline.setDepthFormat(window.getDepthFormat());
		mesh_pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
		if(!mesh_pipeline.loadShaderGLSL(Shader::TypeTask, "main.shader", "TASK_SHADER=1; GRID_SIZE=%uu", grid_size)) return 1;
		if(!mesh_pipeline.loadShaderGLSL(Shader::TypeMesh, "main.shader", "MESH_SHADER=1; GRID_SIZE=%uu", grid_size)) return 1;
		if(!mesh_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
		if(!mesh_pipeline.create()) return 1;
	}
	
	// create target
	Target target = device.createTarget(window);
	
	// current mode
	const char *mode = "";
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s%s %.1f FPS", title.get(), mode, fps));
		
		// window target
		target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Matrix4x4f::rotateZ(time * 4.0f) * Vector4f(192.0f * 0.7f, 0.0f, 128.0f * 0.7f, 1.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 1000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
			common_parameters.transform = Matrix4x4f::rotateZ(time * 32.0f);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			
			// vertex mode
			if(window.getKeyboardKey('1') || (!mesh_pipeline && !geometry_pipeline)) {
				command.setPipeline(vertex_pipeline);
				command.setUniform(0, common_parameters);
				command.setIndices({ 0, 1, 3, 3, 2, 0, 4, 6, 7, 7, 5, 4, 8, 10, 11, 11, 9, 8 });
				command.drawElementsInstanced(3 * 2 * 3, 0, grid_size * grid_size * grid_size);
				mode = " Vertex";
			}
			// mesh mode
			else if(mesh_pipeline && (window.getKeyboardKey('2') || !geometry_pipeline)) {
				command.setPipeline(mesh_pipeline);
				command.setUniform(0, common_parameters);
				command.drawMesh(grid_size * grid_size);
				mode = " Mesh";
			}
			// geometry mode
			else if(geometry_pipeline) {
				command.setPipeline(geometry_pipeline);
				command.setUniform(0, common_parameters);
				command.drawArrays(grid_size * grid_size * grid_size);
				mode = "";
			}
		}
		target.end();
		
		if(!window.present()) return false;
		
		// check errors
		device.check();
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}

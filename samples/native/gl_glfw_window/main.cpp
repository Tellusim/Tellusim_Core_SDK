// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <GLFW/glfw3.h>

#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <math/TellusimMath.h>
#include <platform/TellusimContext.h>
#include <platform/TellusimSurface.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>
#include <platform/TellusimDevice.h>

/*
 */
namespace Tellusim {
	
	/*
	 */
	class GLGLFWWindow {
			
		public:
			
			GLGLFWWindow();
			~GLGLFWWindow();
			
			// create window
			bool create();
			
			// main loop
			bool run();
			
		private:
			
			// rendering loop
			bool create_gl();
			bool render_gl();
			
			bool done = false;
			
			GLFWwindow *window = nullptr;
			
			GLContext context;
			GLSurface surface;
			
			Device device;
			
			Pipeline pipeline;
			Buffer vertex_buffer;
			Buffer index_buffer;
	};
	
	/*
	 */
	GLGLFWWindow::GLGLFWWindow() {
		
	}
	
	GLGLFWWindow::~GLGLFWWindow() {
		
		// terminate GLFW
		if(window) glfwDestroyWindow(window);
		glfwTerminate();
	}
	
	/*
	 */
	bool GLGLFWWindow::create() {
		
		TS_ASSERT(window == nullptr);
		
		// initialize GLFW
		if(!glfwInit()) {
			TS_LOG(Error, "GLGLFWWindow::create(): can't init GLFW\n");
			return false;
		}
		
		// create window
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		window = glfwCreateWindow(1600, 900, "OpenGL Tellusim::GLGLFWWindow", nullptr, nullptr);
		if(!window) {
			TS_LOG(Error, "GLGLFWWindow::create(): can't create window\n");
			return false;
		}
		
		// set current context
		glfwMakeContextCurrent(window);
		
		// create external context
		if(!context.create(nullptr)) {
			TS_LOG(Error, "GLGLFWWindow::create(): can't create context\n");
			return false;
		}
		
		// create external surface
		surface = GLSurface(context);
		if(!surface) {
			TS_LOG(Error, "GLGLFWWindow::create(): can't create context\n");
			return false;
		}
		
		// create device
		device = Device(surface);
		if(!device) {
			TS_LOG(Error, "GLGLFWWindow::create(): can't create device\n");
			return false;
		}
		
		// initialize OpenGL
		if(!create_gl()) {
			TS_LOG(Error, "GLGLFWWindow::create(): can't create OpenGL\n");
			return false;
		}
		
		return true;
	}
	
	/*
	 */
	bool GLGLFWWindow::create_gl() {
		
		// create surface
		surface.setColorFormat(FormatRGBAu8n);
		surface.setDepthFormat(FormatDu24Su8);
		
		// create pipeline
		pipeline = device.createPipeline();
		pipeline.setUniformMask(0, Shader::MaskVertex);
		pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 6);
		pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, sizeof(float32_t) * 3, sizeof(float32_t) * 6);
		pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
		pipeline.setColorFormat(surface.getColorFormat());
		pipeline.setDepthFormat(surface.getDepthFormat());
		pipeline.setMultisample(surface.getMultisample());
		if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return false;
		if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return false;
		if(!pipeline.create()) return false;
		
		// create mesh geometry
		#include "main_mesh.h"
		vertex_buffer = device.createBuffer(Buffer::FlagVertex, mesh_vertices, sizeof(float32_t) * num_mesh_vertices);
		index_buffer = device.createBuffer(Buffer::FlagIndex, mesh_indices, sizeof(uint32_t) * num_mesh_indices);
		if(!vertex_buffer || !index_buffer) return false;
		
		return true;
	}
	
	/*
	 */
	bool GLGLFWWindow::render_gl() {
		
		// structures
		struct CommonParameters {
			Matrix4x4f projection;
			Matrix4x4f modelview;
			Matrix4x4f transform;
			Vector4f camera;
		};
		
		// widget target
		Target target = device.createTarget(surface);
		target.setClearColor(Color("#5586a4"));
		target.begin();
		{
			// current time
			float32_t time = (float32_t)Time::seconds();
			
			// common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Vector4f(2.0f, 2.0f, 1.0f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)surface.getWidth() / surface.getHeight(), 0.1f, 1000.0f);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
			common_parameters.transform = Matrix4x4f::rotateZ(time * 32.0f) * Matrix4x4f::rotateY(60.0f + time * 8.0f);
			
			// create command list
			Command command = device.createCommand(target);
			
			// draw mesh
			command.setPipeline(pipeline);
			command.setUniform(0, common_parameters);
			command.setVertexBuffer(0, vertex_buffer);
			command.setIndexBuffer(FormatRu32, index_buffer);
			command.drawElements((uint32_t)index_buffer.getSize() / 4);
		}
		target.end();
		
		// swap buffers
		glfwSwapBuffers(window);
		
		return true;
	}
	
	/*
	 */
	bool GLGLFWWindow::run() {
		
		// main loop
		while(!done) {
			
			// pool events
			glfwPollEvents();
			done |= (glfwWindowShouldClose(window) != 0);
			done |= (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS);
			
			// surface size
			int32_t width, height;
			glfwGetFramebufferSize(window, &width, &height);
			surface.setSize(width, height);
			
			// render application
			if(!render_gl()) {
				return false;
			}
		}
		
		return true;
	}
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create window
	Tellusim::GLGLFWWindow window;
	if(!window.create()) return 1;
	
	// run application
	window.run();
	
	return 0;
}

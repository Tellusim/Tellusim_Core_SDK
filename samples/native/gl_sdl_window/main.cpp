// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

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
	class GLSDLWindow {
			
		public:
			
			GLSDLWindow();
			~GLSDLWindow();
			
			// create window
			bool create();
			
			// main loop
			bool run();
			
		private:
			
			// rendering loop
			bool create_gl();
			bool render_gl();
			
			bool done = false;
			
			SDL_Window *window = nullptr;
			SDL_GLContext sdl_context = nullptr;
			
			GLContext context;
			GLSurface surface;
			
			Device device;
			
			Pipeline pipeline;
			Buffer vertex_buffer;
			Buffer index_buffer;
	};
	
	/*
	 */
	GLSDLWindow::GLSDLWindow() {
		
	}
	
	GLSDLWindow::~GLSDLWindow() {
		
		// terminate SDL
		if(sdl_context) SDL_GL_DeleteContext(sdl_context);
		if(window) SDL_DestroyWindow(window);
		SDL_Quit();
	}
	
	/*
	 */
	bool GLSDLWindow::create() {
		
		TS_ASSERT(window == nullptr);
		
		// initialize SDL
		if(SDL_Init(SDL_INIT_VIDEO) < 0) {
			TS_LOGF(Error, "GLSDLWindow::create(): can't init SDL %s\n", SDL_GetError());
			return false;
		}
		
		// create window
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
		window = SDL_CreateWindow("OpenGL Tellusim::GLSDLWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_OPENGL);
		if(!window) {
			TS_LOGF(Error, "GLSDLWindow::create(): can't create window %s\n", SDL_GetError());
			return false;
		}
		
		// set current context
		sdl_context = SDL_GL_CreateContext(window);
		if(!sdl_context) {
			TS_LOGF(Error, "GLSDLWindow::create(): can't create context %s\n", SDL_GetError());
			return false;
		}
		
		// create external context
		if(!context.create(nullptr)) {
			TS_LOG(Error, "GLSDLWindow::create(): can't create context\n");
			return false;
		}
		
		// create external surface
		surface = GLSurface(context);
		if(!surface) {
			TS_LOG(Error, "GLSDLWindow::create(): can't create context\n");
			return false;
		}
		
		// create device
		device = Device(surface);
		if(!device) {
			TS_LOG(Error, "GLSDLWindow::create(): can't create device\n");
			return false;
		}
		
		// create OpenGL
		if(!create_gl()) {
			TS_LOG(Error, "GLSDLWindow::create(): can't create OpenGL\n");
			return false;
		}
		
		return true;
	}
	
	/*
	 */
	bool GLSDLWindow::create_gl() {
		
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
	bool GLSDLWindow::render_gl() {
		
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
		SDL_GL_SwapWindow(window);
		
		return true;
	}
	
	/*
	 */
	bool GLSDLWindow::run() {
		
		// main loop
		while(!done) {
			
			// pool events
			SDL_Event event = {};
			while(SDL_PollEvent(&event)) {
				done |= (event.type == SDL_QUIT);
				done |= (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE);
			}
			
			// surface size
			int32_t width, height;
			SDL_GetWindowSize(window, &width, &height);
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
	Tellusim::GLSDLWindow window;
	if(!window.create()) return 1;
	
	// run application
	window.run();
	
	return 0;
}

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#define GDK_DISABLE_DEPRECATION_WARNINGS

#include <gtk/gtk.h>

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
	class GLGTK3Window {
			
		public:
			
			GLGTK3Window();
			~GLGTK3Window();
			
			// create window
			bool create();
			
		private:
			
			// window signals
			static gboolean key_press_signal(GtkWidget *widget, GdkEventKey *event, gpointer data);
			
			// gl area signals
			static void realize_signal(GtkGLArea *area, gpointer data);
			static gboolean render_signal(GtkGLArea *area, GdkGLContext *context, gpointer data);
			
			// create context
			bool create_context();
			
			// rendering loop
			bool create_gl();
			bool render_gl();
			
			GtkWidget *window = nullptr;
			GtkWidget *gl_area = nullptr;
			
			uint32_t window_scale = 1;
			
			GLContext context;
			GLSurface surface;
			
			Device device;
			
			Pipeline pipeline;
			Buffer vertex_buffer;
			Buffer index_buffer;
	};
	
	/*
	 */
	GLGTK3Window::GLGTK3Window() {
		
	}
	
	GLGTK3Window::~GLGTK3Window() {
		
	}
	
	/*
	 */
	bool GLGTK3Window::create() {
		
		TS_ASSERT(window == nullptr);
		
		// create window
		window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title(GTK_WINDOW(window), "OpenGL Tellusim::GLGTK3Window");
		gtk_widget_set_double_buffered(window, false);
		gtk_widget_set_app_paintable(window, true);
		
		// create gl area
		gl_area = gtk_gl_area_new();
		gtk_gl_area_set_required_version(GTK_GL_AREA(gl_area), 4, 5);
		gtk_gl_area_set_has_depth_buffer(GTK_GL_AREA(gl_area), true);
		gtk_gl_area_set_has_stencil_buffer(GTK_GL_AREA(gl_area), true);
		gtk_container_add(GTK_CONTAINER(window), gl_area);
		
		// window size
		gtk_widget_realize(window);
		window_scale = max(gtk_widget_get_scale_factor(window), 1);
		gtk_window_set_default_size(GTK_WINDOW(window), 1600 / window_scale, 900 / window_scale);
		
		// window signals
		g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);
		g_signal_connect(window, "key-press-event", G_CALLBACK(key_press_signal), this);
		
		// gl area signals
		g_signal_connect(gl_area, "realize", G_CALLBACK(realize_signal), this);
		g_signal_connect(gl_area, "render", G_CALLBACK(render_signal), this);
		
		// show window
		gtk_widget_show_all(window);
		
		return true;
	}
	
	/*
	 */
	gboolean GLGTK3Window::key_press_signal(GtkWidget *widget, GdkEventKey *event, gpointer data) {
		if(event->keyval == GDK_KEY_Escape) gtk_main_quit();
		return false;
	}
	
	/*
	 */
	void GLGTK3Window::realize_signal(GtkGLArea *area, gpointer data) {
		gtk_gl_area_make_current(area);
		((GLGTK3Window*)data)->create_context();
		((GLGTK3Window*)data)->create_gl();
	}
	
	gboolean GLGTK3Window::render_signal(GtkGLArea *area, GdkGLContext *context, gpointer data) {
		gtk_gl_area_make_current(area);
		((GLGTK3Window*)data)->render_gl();
		gtk_gl_area_queue_render(area);
		return true;
	}
	
	/*
	 */
	bool GLGTK3Window::create_context() {
		
		// create context
		if(!context.create(nullptr)) {
			TS_LOG(Error, "GLGTK3Window::create_context(): can't create context\n");
			return false;
		}
		
		// create surface
		surface = GLSurface(context);
		if(!surface) {
			TS_LOG(Error, "GLGTK3Window::create_context(): can't create context\n");
			return false;
		}
		
		// create device
		device = Device(surface);
		if(!device) {
			TS_LOG(Error, "GLGTK3Window::create_context(): can't create device\n");
			return false;
		}
		
		// create surface
		surface.setFramebufferID(Maxu32);
		surface.setColorFormat(FormatRGBAu8n);
		surface.setDepthFormat(FormatDu24Su8);
		
		return true;
	}
	
	/*
	 */
	bool GLGTK3Window::create_gl() {
		
		// check device
		if(!device) return false;
		
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
	bool GLGTK3Window::render_gl() {
		
		// surface size
		int32_t width = gtk_widget_get_allocated_width(gl_area) * window_scale;
		int32_t height = gtk_widget_get_allocated_height(gl_area) * window_scale;
		surface.setSize(width, height);
		
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
		
		return true;
	}
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// initialize gtk
	gtk_init(&argc, &argv);
	
	// create window
	Tellusim::GLGTK3Window window;
	if(!window.create()) return 1;
	
	// run application
	gtk_main();
	
	return 0;
}

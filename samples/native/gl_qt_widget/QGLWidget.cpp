// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include "QGLWidget.h"
#include <QtGui/QOpenGLContext>
#if _WIN32
	#include <QtPlatformHeaders/QWGLNativeContext>
#else
	#include <QtPlatformHeaders/QGLXNativeContext>
#endif

#include <core/TellusimTime.h>
#include <math/TellusimMath.h>
#include <platform/TellusimCommand.h>

/*
 */
namespace Tellusim {
	
	/*
	 */
	QGLWidget::QGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
		
	}
	
	QGLWidget::~QGLWidget() {
		
	}
	
	/*
	 */
	QSize QGLWidget::sizeHint() const {
		return QSize(1600, 900);
	}
	
	/*
	 */
	void QGLWidget::initializeGL() {
		
		// context handle
		#if _WIN32
			QWGLNativeContext handle = qvariant_cast<QWGLNativeContext>(context()->nativeHandle());
		#else
			QGLXNativeContext handle = qvariant_cast<QGLXNativeContext>(context()->nativeHandle());
		#endif
		
		// create context
		if(!gl_context.create(handle.context())) return;
		
		// create surface
		surface = GLSurface(gl_context);
		if(!surface) return;
		
		// create device
		device = Device(surface);
		if(!device) return;
		
		// create pipeline
		pipeline = device.createPipeline();
		pipeline.setUniformMask(0, Shader::MaskVertex);
		pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 6);
		pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, sizeof(float32_t) * 3, sizeof(float32_t) * 6);
		pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
		pipeline.setColorFormat(surface.getColorFormat());
		pipeline.setDepthFormat(surface.getDepthFormat());
		pipeline.setMultisample(surface.getMultisample());
		if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return;
		if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return;
		if(!pipeline.create()) return;
		
		// create mesh geometry
		#include "main_mesh.h"
		vertex_buffer = device.createBuffer(Buffer::FlagVertex, mesh_vertices, sizeof(float32_t) * num_mesh_vertices);
		index_buffer = device.createBuffer(Buffer::FlagIndex, mesh_indices, sizeof(uint32_t) * num_mesh_indices);
		if(!vertex_buffer || !index_buffer) return;
		
		// start update timer
		timer.setSingleShot(false);
		connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
		timer.start(1000 / 60);
		
		// initialization flag
		initialized = true;
	}
	
	/*
	 */
	void QGLWidget::resizeGL(int32_t width, int32_t height) {
		
		// check status
		if(!initialized) return;
		
		// surface size
		surface.setSize((uint32_t)width, (uint32_t)height);
	}
	
	/*
	 */
	void QGLWidget::paintGL() {
		
		// check status
		if(!initialized) return;
		
		// structures
		struct CommonParameters {
			Matrix4x4f projection;
			Matrix4x4f modelview;
			Matrix4x4f transform;
			Vector4f camera;
		};
		
		// surface framebuffer
		surface.setFramebufferID(defaultFramebufferObject());
		
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
		
		device.check();
	}
}

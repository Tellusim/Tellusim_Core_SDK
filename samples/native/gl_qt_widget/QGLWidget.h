// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_QT_GL_WIDGET_H__
#define __TELLUSIM_QT_GL_WIDGET_H__

#include <QtCore/QTimer>
#include <QtWidgets/QOpenGLWidget>

#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimContext.h>
#include <platform/TellusimSurface.h>

/*
 */
namespace Tellusim {
	
	/*
	 */
	class QGLWidget : public QOpenGLWidget {
			
			Q_OBJECT
			
		public:
			
			QGLWidget(QWidget *parent = nullptr);
			~QGLWidget();
			
			virtual QSize sizeHint() const;
			
		protected:
			
			/// rendering loop
			virtual void initializeGL();
			virtual void resizeGL(int32_t width, int32_t height);
			virtual void paintGL();
			
		private:
			
			bool initialized = false;
			
			GLContext gl_context;
			
			GLSurface surface;
			
			Device device;
			Pipeline pipeline;
			Buffer vertex_buffer;
			Buffer index_buffer;
			
			QTimer timer;
	};
}

#endif /* __TELLUSIM_QT_GL_WIDGET_H__ */

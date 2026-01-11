// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <QtWidgets/QApplication>

#include "QGLWidget.h"

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// application
	QApplication app(argc, argv);
	
	// surface format
	QSurfaceFormat format;
	format.setVersion(4, 5);
	format.setDepthBufferSize(24);
	format.setStencilBufferSize(8);
	format.setProfile(QSurfaceFormat::CoreProfile);
	
	// create window
	Tellusim::QGLWidget window;
	window.setFormat(format);
	window.setWindowTitle("OpenGL Tellusim::GLQtWidget");
	window.show();
	
	// run application
	return app.exec();
}

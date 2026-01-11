// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <QtWidgets/QApplication>

#include "QVKWidget.h"

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// application
	QApplication app(argc, argv);
	
	// create window
	Tellusim::QVKWidget window;
	window.setWindowTitle("Vulkan Tellusim::VKQtWidget");
	window.show();
	
	// run application
	return app.exec();
}

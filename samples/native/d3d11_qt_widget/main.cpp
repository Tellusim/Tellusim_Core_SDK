// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <QtWidgets/QApplication>

#include "QD3D11Widget.h"

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// application
	QApplication app(argc, argv);
	
	// create window
	Tellusim::QD3D11Widget window;
	window.setWindowTitle("Direct3D11 Tellusim::D3D11QtWidget");
	window.show();
	
	// run application
	return app.exec();
}

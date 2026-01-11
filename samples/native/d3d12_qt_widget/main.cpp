// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <QtWidgets/QApplication>

#include "QD3D12Widget.h"

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// application
	QApplication app(argc, argv);
	
	// create window
	Tellusim::QD3D12Widget window;
	window.setWindowTitle("Direct3D12 Tellusim::D3D12QtWidget");
	window.show();
	
	// run application
	return app.exec();
}

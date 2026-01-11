// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <format/TellusimImage.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	Image image;
	
	// load webp
	if(!image.load("test.webp")) return 1;
	
	// save image
	if(!image.save("test_save.png")) return 1;
	
	// save webp
	if(!image.save("test_save.webp")) return 1;
	
	return 0;
}

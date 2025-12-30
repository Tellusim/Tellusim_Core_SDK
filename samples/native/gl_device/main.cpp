// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <platform/TellusimContext.h>
#include <platform/TellusimDevice.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create context
	GLContext context;
	if(!context.create()) return 1;
	
	// create device
	Device device(context);
	if(!device) return 1;
	
	// device name
	TS_LOGF(Message, "%s (%s)\n", device.getName().get(), device.getPlatformName());
	if(device.getVendor()) TS_LOGF(Message, "Vendor: %s\n", device.getVendor().get());
	if(device.getVersion()) TS_LOGF(Message, "Version: %s\n", device.getVersion().get());
	
	// context extensions
	TS_LOGF(Message, "Extensions: %s\n", GLContext::getExtensions().get());
	
	// finish context
	context.finish();
	
	return 0;
}

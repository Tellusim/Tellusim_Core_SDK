// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <TellusimApp.h>
#include <core/TellusimLog.h>
#include <platform/TellusimContext.h>
#include <platform/TellusimDevice.h>

#include "include/TellusimLogger.h"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create logger
	Logger::Flags flags = Logger::FlagNone;
	flags |= Logger::FlagDate;
	flags |= Logger::FlagTime;
	flags |= Logger::FlagPrint;
	flags |= Logger::FlagLocal;
	Logger logger(flags);
	
	// create app
	App app(argc, argv);
	if(!app.create()) return 1;
	
	// create context
	Context context(app.getPlatform(), app.getDevice());
	if(!context.create()) return 1;
	
	// create device
	Device device(context);
	if(!device) return 1;
	
	// print device info
	const auto &features = device.getFeatures();
	TS_LOGF(Message, "GPU name: %s\n", device.getName().get());
	TS_LOGF(Message, "GPU vendor: %s\n", device.getVendor().get());
	TS_LOGF(Message, "GPU version: %s\n", device.getVersion().get());
	TS_LOGF(Message, "GPU memory: %s\n", String::fromBytes(features.videoMemory).get());
	
	// fatal error
	//TS_LOG(Fatal, "Fatal Error\n");
	
	// finish context
	context.finish();
	
	return 0;
}

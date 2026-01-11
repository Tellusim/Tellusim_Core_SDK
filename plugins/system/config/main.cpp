// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>

#include "include/TellusimConfig.h"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create config
	Config::Flags flags = Config::FlagNone;
	flags |= Config::FlagLocal;
	Config config(flags);
	
	// config version
	TS_LOGF(Message, "Version: %s\n", config.getVersion().get());
	
	// run counter
	uint32_t counter = config.getu32("counter", 0);
	TS_LOGF(Message, "Counter: %u\n", counter);
	config.set("counter", counter + 1);
	
	return 0;
}

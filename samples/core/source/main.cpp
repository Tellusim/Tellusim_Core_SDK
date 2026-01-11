// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimBlob.h>
#include <core/TellusimSource.h>

/*
 */
using namespace Tellusim;

/*
 */
Stream source_callback(const char *name, void *data) {
	if(String(name) == "source.txt") {
		Blob blob(name);
		blob.puts("Hello Source!!!");
		blob.seek(0);
		return move(blob);
	}
	return Stream::null;
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// source callback
	if(1) {
		
		Source::setCallback(source_callback);
		
		Source source;
		if(!source.open("source.txt")) return 1;
		TS_LOGF(Message, "%s\n", source.gets().get());
		TS_LOGF(Message, "%s\n", source.getName().get());
	}
	
	return 0;
}

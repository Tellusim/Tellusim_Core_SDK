// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>

#include "include/TellusimStreamer.h"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create streamer
	Streamer::Flags flags = Streamer::FlagNone;
	flags |= Streamer::FlagCase;
	flags |= Streamer::FlagRecursive;
	Streamer streamer(flags);
	
	// streamer prefix
	streamer.addPrefix("./");
	
	// recursive loading
	if(!streamer.loadDirectory("data")) return 1;
	
	// streamer archive
	//if(!streamer.loadArchive("data/archive.zip")) return 1;
	
	// streamer directory
	//if(!streamer.loadDirectory("data/directory")) return 1;
	
	// print streamer files
	for(uint32_t i = 0; i < streamer.getNumFiles(); i++) {
		TS_LOGF(Message, "%s: %s\n", streamer.getFileName(i).get(), String::fromBytes(streamer.getFileSize(i)).get());
	}
	
	Source source;
	
	// archive stream
	if(source.open("./directory/archive.txt")) {
		TS_LOGF(Message, "%s\n", source.gets().get());
		source.close();
	}
	
	// directory stream
	if(source.open("file.txt")) {
		TS_LOGF(Message, "%s\n", source.gets().get());
		source.close();
	}
	
	return 0;
}

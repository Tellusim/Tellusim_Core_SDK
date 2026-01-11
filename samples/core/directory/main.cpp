// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimDirectory.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	{
		Directory directory;
		if(!directory.open("../", true)) return 1;
		for(uint32_t i = 0; i < directory.getNumFiles(); i++) {
			TS_LOGF(Message, "file: %s %x %s\n", directory.getFileName(i).get(), directory.getFileAttributes(i), String::fromBytes(directory.getFileSize(i)).get());
		}
		for(uint32_t i = 0; i < directory.getNumDirectories(); i++) {
			TS_LOGF(Message, "directory: %s %x %u\n", directory.getDirectoryName(i).get(), directory.getDirectoryAttributes(i), directory.getDirectorySize(i));
		}
	}
	
	{
		if(!Directory::createDirectory("one/two/three", true)) return 1;
		if(!Directory::removeDirectory("one", true)) return 1;
	}
	
	{
		TS_LOGF(Message, "current:   %s\n", Directory::getCurrentDirectory().get());
		TS_LOGF(Message, "binary:    %s\n", Directory::getBinaryDirectory().get());
		TS_LOGF(Message, "home:      %s\n", Directory::getHomeDirectory().get());
		TS_LOGF(Message, "temp:      %s\n", Directory::getTempDirectory().get());
		TS_LOGF(Message, "config:    %s\n", Directory::getConfigDirectory().get());
		TS_LOGF(Message, "documents: %s\n", Directory::getDocumentsDirectory().get());
	}
	
	{
		Directory::Attributes attributes = Directory::getFileAttributes("main.cpp");
		TS_LOGF(Message, "rd: %u\n", !!(attributes & Directory::AttributeRead));
		TS_LOGF(Message, "wr: %u\n", !!(attributes & Directory::AttributeWrite));
		TS_LOGF(Message, "hd: %u\n", !!(attributes & Directory::AttributeHidden));
		TS_LOGF(Message, "ex: %u\n", !!(attributes & Directory::AttributeExecute));
		TS_LOGF(Message, "tm: %u\n", !!(attributes & Directory::AttributeTemporary));
	}
	
	{
		for(const String &drive : Directory::getDriveNames()) {
			TS_LOGF(Message, "drive: %s\n", drive.get());
		}
	}
	
	return 0;
}

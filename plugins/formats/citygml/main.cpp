// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimDirectory.h>
#include <format/TellusimMesh.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	Mesh mesh;
	
	// process files
	Directory directory;
	String prefix = String("data/");
	if(Directory::isDirectory(prefix) && directory.open(prefix)) {
		for(const String &name : directory.getFiles()) {
			if(name.extension() != "gml") continue;
			
			// load CityGML
			TS_LOGF(Message, "%s\n", name.get());
			if(!mesh.load(prefix + name)) return 1;
			
			// save mesh
			mesh.save(prefix + name.extension("mesh"));
		}
	}
	else {
		
		// load CityGML
		if(!mesh.load("test.gml")) return 1;
		
		// save mesh
		if(!mesh.save("test_save.mesh")) return 1;
	}
	
	return 0;
}

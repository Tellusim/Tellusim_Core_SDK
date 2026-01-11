// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <format/TellusimMesh.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	Mesh mesh;
	
	// load draco
	//if(!mesh.load("test.drc")) return 1;
	if(!mesh.load("test.glb")) return 1;
	
	// save mesh
	if(!mesh.save("test_save.mesh")) return 1;
	
	return 0;
}

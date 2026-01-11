// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <platform/TellusimShader.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create compliler
	ShaderCompiler compiler;
	
	// load shader
	if(!compiler.loadGLSL(Shader::TypeCompute, "main.shader", "COMPUTE_SHADER=1")) return 1;
	
	// unknown source
	Log::print(compiler.getSource().get());
	
	// platform source
	for(uint32_t i = PlatformFusion + 1; i < PlatformAny; i++) {
		Platform platform = (Platform)i;
		if(!isPlatformAvailable(platform)) continue;
		Log::printf("\n%s:\n", getPlatformName(platform));
		Log::print(compiler.getSource(platform).get());
	}
	
	return 0;
}

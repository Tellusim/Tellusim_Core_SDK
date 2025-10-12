#!/usr/bin/env python3

# Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/

from tellusimd import *

# create compiler
compiler = ShaderCompiler()

# load shader
if not compiler.loadGLSL(Shader.TypeCompute, 'main.shader', 'COMPUTE_SHADER=1'): exit(1)

# unknown source
Log.print(compiler.getSource())

# platform source
for platform in range(PlatformFusion + 1, PlatformAny):
	if not isPlatformAvailable(platform): continue
	Log.printf('\n%s:\n', getPlatformName(platform))
	Log.print(compiler.getSource(platform))

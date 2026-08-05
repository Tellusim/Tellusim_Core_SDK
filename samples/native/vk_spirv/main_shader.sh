#!/bin/bash

#ts_shader -v -DVERTEX_SHADER=1 main.shader -o main_shader_v.spv
#ts_shader -f -DFRAGMENT_SHADER=1 main.shader -o main_shader_f.spv

glslangValidator -V main.shader -S vert -DVERTEX_SHADER=1 -o main_shader_v.spv
glslangValidator -V main.shader -S frag -DFRAGMENT_SHADER=1 -o main_shader_f.spv

#cp main.shader main.glsl
#glslc -O -fshader-stage=vert main.glsl -DVERTEX_SHADER=1 -o main_shader_v.spv
#glslc -O -fshader-stage=frag main.glsl -DFRAGMENT_SHADER=1 -o main_shader_f.spv
#rm main.glsl

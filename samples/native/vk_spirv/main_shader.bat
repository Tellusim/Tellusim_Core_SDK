@echo off

rem ts_shader -v -DVERTEX_SHADER=1 main.shader -o main_shader_v.spv
rem ts_shader -f -DFRAGMENT_SHADER=1 main.shader -o main_shader_f.spv

glslangValidator -V main.shader -S vert -DVERTEX_SHADER=1 -o main_shader_v.spv
glslangValidator -V main.shader -S frag -DFRAGMENT_SHADER=1 -o main_shader_f.spv

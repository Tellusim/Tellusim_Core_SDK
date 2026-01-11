// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <stdio.h>

#if _WIN32
	#include <io.h>
	#include <fcntl.h>
	#define fileno _fileno
#endif

#include <core/TellusimLog.h>
#include <core/TellusimFile.h>
#include <platform/TellusimShader.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// print help
	if(argc < 2 || String(argv[1]) == "-h") {
		Log::printf("Tellusim Shader Compiler (build " __DATE__ " https://tellusim.com/)\nUsage: %s -v shader.glsl\n", argv[0]);
		Log::print("  -D<macro>[=<val>]  Define a macro and value\n");
		Log::print("  -U<macro>          Undefine a macro\n");
		Log::print("  -no-warn, -nw      No warnings output\n");
		Log::print("  -vertex, -v        Vertex shader\n");
		Log::print("  -control, -tc      Control shader\n");
		Log::print("  -evaluate, -te     Evaluate shader\n");
		Log::print("  -geometry, -g      Geometry shader\n");
		Log::print("  -fragment, -f      Fragment shader\n");
		Log::print("  -compute, -c       Compute shader\n");
		Log::print("  -task, -t          Task shader\n");
		Log::print("  -mesh, -m          Mesh shader\n");
		Log::print("  -raygen, -rg       RayGen shader\n");
		Log::print("  -raymiss, -rm      RayMiss shader\n");
		Log::print("  -closest, -rc      Closest shader\n");
		Log::print("  -firsthit, -rf     FirstHit shader\n");
		Log::print("  -intersection, -ri Intersection shader\n");
		Log::print("  -callable, -rcall  Callable shader\n");
		Log::print("  -sampler <offset>  Sampler offset\n");
		Log::print("  -texture <offset>  Texture offset\n");
		Log::print("  -surface <offset>  Surface offset\n");
		Log::print("  -uniform <offset>  Uniform offset\n");
		Log::print("  -storage <offset>  Storage offset\n");
		Log::print("  -tracing <offset>  Tracing offset\n");
		Log::print("  -texel <offset>    Texel offset\n");
		Log::print("  -table <offset>    Table offset\n");
		Log::print("  -flags <flags>     Shader flags (mslindirect)\n");
		Log::print("  -d <filename>      Decompile shader\n");
		Log::print("  -o <filename>      Output Vulkan SPIR-V binary\n");
		Log::print("  -gl <filename>     Create OpenGL SPIR-V binary\n");
		Log::print("  -glsl <filename>   Create GLSL OpenGL shader source\n");
		Log::print("  -glsles <filename> Create GLSL OpenGLES shader source\n");
		Log::print("  -hlsl <filename>   Create HLSL DXIL shader source\n");
		Log::print("  -hlslbc <filename> Create HLSL DXBC shader source\n");
		Log::print("  -wgsl <filename>   Create WGSL shader source\n");
		Log::print("  -msl <filename>    Create MSL shader source\n");
		Log::print("  -cu <filename>     Create CU shader source\n");
		Log::print("  -hip <filename>    Create HIP shader source\n");
		return 0;
	}
	
	File file;
	
	// shader compiler
	ShaderCompiler shader;
	Shader::Type type = Shader::TypeUnknown;
	ShaderCompiler::Flags flags = ShaderCompiler::FlagNone;
	
	// default offsets
	int32_t sampler_offset = 0;
	int32_t texture_offset = 0;
	int32_t surface_offset = 0;
	int32_t uniform_offset = 0;
	int32_t storage_offset = 0;
	int32_t tracing_offset = 0;
	int32_t texel_offset = 0;
	int32_t table_offset = 0;
	
	// command line arguments
	for(int32_t i = 1; i < argc; i++) {
		const char *s = argv[i];
		
		// commands
		if(s[0] == '-') {
			while(*s == '-') s++;
			String command = String(s);
			
			// macros
			if(command.begins("D")) Shader::setMacros(command.get() + 1);
			else if(command.begins("U")) Shader::removeMacro(command.get() + 1);
			
			// warnings output
			else if(command == "no-warn" || command == "nw") Log::setLevel(Log::Error);
			
			// shader type
			else if(command == "vertex" || command == "v") type = Shader::TypeVertex;
			else if(command == "control" || command == "tc") type = Shader::TypeControl;
			else if(command == "evaluate" || command == "te") type = Shader::TypeEvaluate;
			else if(command == "geometry" || command == "g") type = Shader::TypeGeometry;
			else if(command == "fragment" || command == "f") type = Shader::TypeFragment;
			else if(command == "compute" || command == "c") type = Shader::TypeCompute;
			else if(command == "task" || command == "t") type = Shader::TypeTask;
			else if(command == "mesh" || command == "m") type = Shader::TypeMesh;
			else if(command == "raygen" || command == "rg") type = Shader::TypeRayGen;
			else if(command == "raymiss" || command == "rm") type = Shader::TypeRayMiss;
			else if(command == "closest" || command == "rc") type = Shader::TypeClosest;
			else if(command == "firsthit" || command == "rf") type = Shader::TypeFirstHit;
			else if(command == "intersection" || command == "ri") type = Shader::TypeIntersection;
			else if(command == "callable" || command == "rcall") type = Shader::TypeCallable;
			
			// shader offsets
			else if(command == "sampler" && i + 1 < argc) sampler_offset = String::toi32(argv[++i]);
			else if(command == "texture" && i + 1 < argc) texture_offset = String::toi32(argv[++i]);
			else if(command == "surface" && i + 1 < argc) surface_offset = String::toi32(argv[++i]);
			else if(command == "uniform" && i + 1 < argc) uniform_offset = String::toi32(argv[++i]);
			else if(command == "storage" && i + 1 < argc) storage_offset = String::toi32(argv[++i]);
			else if(command == "tracing" && i + 1 < argc) tracing_offset = String::toi32(argv[++i]);
			else if(command == "texel" && i + 1 < argc) texel_offset = String::toi32(argv[++i]);
			else if(command == "table" && i + 1 < argc) table_offset = String::toi32(argv[++i]);
			
			// shader flags
			else if(command == "flags" && i + 1 < argc) {
				for(; i + 1 < argc; i++) {
					String flag = String(argv[i + 1]);
					if(flag == "none") flags = ShaderCompiler::FlagNone;
					else if(flag == "mslindirect") flags |= ShaderCompiler::FlagMSLIndirect;
					else break;
				}
			}
			
			// save shader
			else {
				
				// check shader
				if(!shader.isCreated()) {
					TS_LOGF(Error, "%s: shader is not created\n", argv[0]);
					return 1;
				}
				
				// shader offsets
				shader.setSamplerOffset(sampler_offset);
				shader.setTextureOffset(texture_offset);
				shader.setSurfaceOffset(surface_offset);
				shader.setUniformOffset(uniform_offset);
				shader.setStorageOffset(storage_offset);
				shader.setTracingOffset(tracing_offset);
				shader.setTexelOffset(texel_offset);
				shader.setTableOffset(table_offset);
				
				// shader flags
				shader.setFlags(flags);
				
				// output file
				if((command == "d" || command == "o" || command == "gl" || command == "glsl" || command == "glsles" || command == "hlsl" || command == "wgsl" || command == "msl" || command == "cu" || command == "hip") && i + 1 < argc && argv[i + 1][0] != '-') {
					if(!file.open(argv[++i], "wb")) {
						TS_LOGEF(Error, "%s: can't create \"%s\" file\n", argv[0], argv[i]);
						return 1;
					}
					if(command == "d") file.puts(shader.getSource());
					if(command == "o") shader.getBinary(file);
					if(command == "gl") shader.getBinary(file, PlatformGL);
					if(command == "glsl") file.puts(shader.getSource(PlatformGL));
					if(command == "glsles") file.puts(shader.getSource(PlatformGLES));
					if(command == "hlsl") file.puts(shader.getSource(PlatformD3D12));
					if(command == "hlslbc") file.puts(shader.getSource(PlatformD3D11));
					if(command == "wgsl") file.puts(shader.getSource(PlatformWG));
					if(command == "msl") file.puts(shader.getSource(PlatformMTL));
					if(command == "cu") file.puts(shader.getSource(PlatformCU));
					if(command == "hip") file.puts(shader.getSource(PlatformHIP));
					file.close();
				}
				
				// output to the stream
				else if(command == "d") Log::print(shader.getSource().get());
				else if(command == "glsl") Log::print(shader.getSource(PlatformGL).get());
				else if(command == "glsles") Log::print(shader.getSource(PlatformGLES).get());
				else if(command == "hlsl") Log::print(shader.getSource(PlatformD3D12).get());
				else if(command == "hlslbc") Log::print(shader.getSource(PlatformD3D11).get());
				else if(command == "wgsl") Log::print(shader.getSource(PlatformWG).get());
				else if(command == "msl") Log::print(shader.getSource(PlatformMTL).get());
				else if(command == "cu") Log::print(shader.getSource(PlatformCU).get());
				else if(command == "hip") Log::print(shader.getSource(PlatformHIP).get());
				else if((command == "o" || command == "gl") && i + 1 < argc && String(argv[i + 1]) == "-") {
					#if _WIN32
						_setmode(fileno(stdout), O_BINARY);
					#endif
					if(!file.open(fileno(stdout), "stdout", "wb")) {
						TS_LOGEF(Error, "%s: can't open stdout\n", argv[i]);
						return 1;
					}
					if(command == "o") shader.getBinary(file);
					if(command == "gl") shader.getBinary(file, PlatformGL);
					file.close();
					i++;
				}
				
				// unknown command
				else {
					TS_LOGF(Error, "%s: invalid command line option \"%s\"\n", argv[0], argv[i]);
					return 1;
				}
			}
		}
		else {
			
			// check shader type
			if(type == Shader::TypeUnknown) {
				TS_LOGF(Error, "%s: shader type is not specified\n", argv[0]);
				return 1;
			}
			
			// input file type
			if(!file.open(argv[i], "rb")) {
				TS_LOGEF(Error, "%s: can't open \"%s\" file\n", argv[0], argv[i]);
				return 1;
			}
			uint32_t magic = file.readu32();
			file.close();
			
			// load shader
			bool ret = false;
			uint32_t SpvMagicNumber = 0x07230203;
			if(magic == SpvMagicNumber) ret = shader.loadSPIRV(type, argv[i]);
			else ret = shader.loadGLSL(type, argv[i]);
			if(ret == false) return 1;
		}
	}
	
	return 0;
}

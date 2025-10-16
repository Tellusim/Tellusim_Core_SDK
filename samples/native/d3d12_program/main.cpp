// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <d3d12.h>

#include <common/common.h>
#include <core/TellusimSystem.h>
#include <core/TellusimPointer.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimContext.h>
#include <platform/TellusimCommand.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimSurface.h>

/*
 */
//#define MESH_SHADER	1

/*
 */
#define D3D12_SDK_PATH	"../d3d12_common"

/*
 */
using namespace Tellusim;

/*
 */
extern "C" {
	__declspec(dllexport) extern const char *D3D12SDKPath = D3D12_SDK_PATH;
	__declspec(dllexport) extern const uint32_t D3D12SDKVersion = D3D12_PREVIEW_SDK_VERSION;
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	App::setPlatform(PlatformD3D12);
	
	// create window
	DECLARE_WINDOW
	
	// load DXCompiler libraries
	System::loadLibrary(D3D12_SDK_PATH "/dxil.dll");
	System::loadLibrary(D3D12_SDK_PATH "/dxcompiler.dll");
	
	// create window
	String title = String::format("%s Tellusim::D3D12Program", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// geometry parameters
	constexpr uint32_t num_vertices = 16 * 8;
	
	// structures
	struct CommonParameters {
		uint32_t offset;
		float32_t time;
	};
	
	// create device
	D3D12Device device(window);
	if(!device) return 1;
	
	// get device interface
	AutoComPtr<ID3D12Device5> d3d12_device;
	if(D3D12Context::error(device.getD3D12Device()->QueryInterface(IID_PPV_ARGS(d3d12_device.create())))) {
		TS_LOG(Error, "can't get device interface\n");
		return 1;
	}
	
	// check shader model support
	D3D12_FEATURE_DATA_SHADER_MODEL shader_model = {};
	shader_model.HighestShaderModel = D3D_SHADER_MODEL_6_8;
	if(D3D12Context::error(d3d12_device->CheckFeatureSupport(D3D12_FEATURE_SHADER_MODEL, &shader_model, sizeof(shader_model)))) {
		TS_LOG(Error, "can't get shader model\n");
		return 1;
	}
	if(shader_model.HighestShaderModel < D3D_SHADER_MODEL_6_8) {
		TS_LOG(Error, "shader model 6.8 is not supported\n");
		return 1;
	}
	
	// create root signature pipeline
	D3D12Pipeline pipeline = D3D12Pipeline(device.createPipeline());
	pipeline.setUniformMask(0, Shader::MaskAll);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	#if MESH_SHADER
		if(!pipeline.loadShaderGLSL(Shader::TypeMesh, "main.shader", "MESH_SHADER=1")) return 1;
	#else
		if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	#endif
	if(!pipeline.create()) return 1;
	
	#if MESH_SHADER
		
		// load mesh shader
		D3D12Shader mesh_shader = D3D12Shader(device.loadShaderGLSL(Shader::TypeMesh, "main.shader", "MESH_SHADER=1"));
		if(!mesh_shader) return 1;
		
	#else
		
		// load vertex shader
		D3D12Shader vertex_shader = D3D12Shader(device.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1"));
		if(!vertex_shader) return 1;
		
	#endif
	
	// load fragment shader
	D3D12Shader fragment_0_shader = D3D12Shader(device.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_0_SHADER=1"));
	D3D12Shader fragment_1_shader = D3D12Shader(device.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_1_SHADER=1"));
	if(!fragment_0_shader || !fragment_1_shader) return 1;
	
	// create graphis program
	AutoComPtr<ID3D12StateObject> program_state;
	D3D12_PROGRAM_IDENTIFIER program_0 = {};
	D3D12_PROGRAM_IDENTIFIER program_1 = {};
	{
		// program objects
		Array<D3D12_STATE_SUBOBJECT> objects_desc;
		Array<D3D12_STATE_SUBOBJECT*> program_objects_desc;
		
		// reserve objects (to have stable program pointers)
		objects_desc.reserve(128);
		
		// window surface
		D3D12Surface surface = D3D12Surface(window.getSurface());
		
		#if MESH_SHADER
			
			// mesh shader
			D3D12_DXIL_LIBRARY_DESC mesh_shader_desc = {};
			D3D12_EXPORT_DESC mesh_shader_export_desc = {};
			mesh_shader_desc.DXILLibrary.pShaderBytecode = mesh_shader.getShaderBlob()->GetBufferPointer();
			mesh_shader_desc.DXILLibrary.BytecodeLength = mesh_shader.getShaderBlob()->GetBufferSize();
			mesh_shader_desc.NumExports = 1;
			mesh_shader_desc.pExports = &mesh_shader_export_desc;
			mesh_shader_export_desc.Name = L"mesh";
			mesh_shader_export_desc.ExportToRename = L"*";
			{
				D3D12_STATE_SUBOBJECT &object_desc = objects_desc.append();
				object_desc.Type = D3D12_STATE_SUBOBJECT_TYPE_DXIL_LIBRARY;
				object_desc.pDesc = &mesh_shader_desc;
			}
			
		#else
			
			// vertex shader
			D3D12_DXIL_LIBRARY_DESC vertex_shader_desc = {};
			D3D12_EXPORT_DESC vertex_shader_export_desc = {};
			vertex_shader_desc.DXILLibrary.pShaderBytecode = vertex_shader.getShaderBlob()->GetBufferPointer();
			vertex_shader_desc.DXILLibrary.BytecodeLength = vertex_shader.getShaderBlob()->GetBufferSize();
			vertex_shader_desc.NumExports = 1;
			vertex_shader_desc.pExports = &vertex_shader_export_desc;
			vertex_shader_export_desc.Name = L"vertex";
			vertex_shader_export_desc.ExportToRename = L"*";
			{
				D3D12_STATE_SUBOBJECT &object_desc = objects_desc.append();
				object_desc.Type = D3D12_STATE_SUBOBJECT_TYPE_DXIL_LIBRARY;
				object_desc.pDesc = &vertex_shader_desc;
			}
			
		#endif
		
		// fragment 0 shader
		D3D12_DXIL_LIBRARY_DESC fragment_0_shader_desc = {};
		D3D12_EXPORT_DESC fragment_0_shader_export_desc = {};
		fragment_0_shader_desc.DXILLibrary.pShaderBytecode = fragment_0_shader.getShaderBlob()->GetBufferPointer();
		fragment_0_shader_desc.DXILLibrary.BytecodeLength = fragment_0_shader.getShaderBlob()->GetBufferSize();
		fragment_0_shader_desc.NumExports = 1;
		fragment_0_shader_desc.pExports = &fragment_0_shader_export_desc;
		fragment_0_shader_export_desc.Name = L"fragment_0";
		fragment_0_shader_export_desc.ExportToRename = L"*";
		{
			D3D12_STATE_SUBOBJECT &object_desc = objects_desc.append();
			object_desc.Type = D3D12_STATE_SUBOBJECT_TYPE_DXIL_LIBRARY;
			object_desc.pDesc = &fragment_0_shader_desc;
		}
		
		// fragment 1 shader
		D3D12_DXIL_LIBRARY_DESC fragment_1_shader_desc = {};
		D3D12_EXPORT_DESC fragment_1_shader_export_desc = {};
		fragment_1_shader_desc.DXILLibrary.pShaderBytecode = fragment_1_shader.getShaderBlob()->GetBufferPointer();
		fragment_1_shader_desc.DXILLibrary.BytecodeLength = fragment_1_shader.getShaderBlob()->GetBufferSize();
		fragment_1_shader_desc.NumExports = 1;
		fragment_1_shader_desc.pExports = &fragment_1_shader_export_desc;
		fragment_1_shader_export_desc.Name = L"fragment_1";
		fragment_1_shader_export_desc.ExportToRename = L"*";
		{
			D3D12_STATE_SUBOBJECT &object_desc = objects_desc.append();
			object_desc.Type = D3D12_STATE_SUBOBJECT_TYPE_DXIL_LIBRARY;
			object_desc.pDesc = &fragment_1_shader_desc;
		}
		
		// root signature
		ID3D12RootSignature *root_signature = pipeline.getRootSignature();
		{
			D3D12_STATE_SUBOBJECT &object_desc = objects_desc.append();
			object_desc.Type = D3D12_STATE_SUBOBJECT_TYPE_GLOBAL_ROOT_SIGNATURE;
			object_desc.pDesc = &root_signature;
		}
		
		// rasterizer desc
		D3D12_RASTERIZER_DESC2 rasterizer_desc = {};
		rasterizer_desc.FillMode = D3D12_FILL_MODE_SOLID;
		rasterizer_desc.CullMode = D3D12_CULL_MODE_BACK;
		rasterizer_desc.FrontCounterClockwise = TRUE;
		rasterizer_desc.DepthClipEnable = TRUE;
		{
			D3D12_STATE_SUBOBJECT &object_desc = objects_desc.append();
			object_desc.Type = D3D12_STATE_SUBOBJECT_TYPE_RASTERIZER;
			object_desc.pDesc = &rasterizer_desc;
			program_objects_desc.append(&object_desc);
		}
		
		// depth stencil desc
		D3D12_DEPTH_STENCIL_DESC depth_stencil_desc = {};
		depth_stencil_desc.DepthEnable = FALSE;
		depth_stencil_desc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
		depth_stencil_desc.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS;
		{
			D3D12_STATE_SUBOBJECT &object_desc = objects_desc.append();
			object_desc.Type = D3D12_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL;
			object_desc.pDesc = &depth_stencil_desc;
			program_objects_desc.append(&object_desc);
		}
		
		// primitive topology
		D3D12_PRIMITIVE_TOPOLOGY_DESC primitive_desc = {};
		primitive_desc.PrimitiveTopology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		{
			D3D12_STATE_SUBOBJECT &object_desc = objects_desc.append();
			object_desc.Type = D3D12_STATE_SUBOBJECT_TYPE_PRIMITIVE_TOPOLOGY;
			object_desc.pDesc = &primitive_desc;
			program_objects_desc.append(&object_desc);
		}
		
		// render target format
		D3D12_RT_FORMAT_ARRAY render_target_desc = {};
		render_target_desc.NumRenderTargets = 1;
		render_target_desc.RTFormats[0] = (DXGI_FORMAT)surface.getColorDXGIFormat();
		{
			D3D12_STATE_SUBOBJECT &object_desc = objects_desc.append();
			object_desc.Type = D3D12_STATE_SUBOBJECT_TYPE_RENDER_TARGET_FORMATS;
			object_desc.pDesc = &render_target_desc;
			program_objects_desc.append(&object_desc);
		}
		
		// depth stencil format
		DXGI_FORMAT depth_stencil_format = (DXGI_FORMAT)surface.getDepthDXGIFormat();
		{
			D3D12_STATE_SUBOBJECT &object_desc = objects_desc.append();
			object_desc.Type = D3D12_STATE_SUBOBJECT_TYPE_DEPTH_STENCIL_FORMAT;
			object_desc.pDesc = &depth_stencil_format;
			program_objects_desc.append(&object_desc);
		}
		
		// create program 0
		D3D12_GENERIC_PROGRAM_DESC program_0_desc = {};
		#if MESH_SHADER
			LPCWSTR program_0_exports[] = { L"mesh", L"fragment_0" };
		#else
			LPCWSTR program_0_exports[] = { L"vertex", L"fragment_0" };
		#endif
		program_0_desc.ProgramName = L"program_0";
		program_0_desc.NumExports = TS_COUNTOF(program_0_exports);
		program_0_desc.pExports = program_0_exports;
		program_0_desc.NumSubobjects = program_objects_desc.size();
		program_0_desc.ppSubobjects = program_objects_desc.get();
		{
			D3D12_STATE_SUBOBJECT &object_desc = objects_desc.append();
			object_desc.Type = D3D12_STATE_SUBOBJECT_TYPE_GENERIC_PROGRAM;
			object_desc.pDesc = &program_0_desc;
		}
		
		// create program 1
		D3D12_GENERIC_PROGRAM_DESC program_1_desc = {};
		#if MESH_SHADER
			LPCWSTR program_1_exports[] = { L"mesh", L"fragment_1" };
		#else
			LPCWSTR program_1_exports[] = { L"vertex", L"fragment_1" };
		#endif
		program_1_desc.ProgramName = L"program_1";
		program_1_desc.NumExports = TS_COUNTOF(program_1_exports);
		program_1_desc.pExports = program_1_exports;
		program_1_desc.NumSubobjects = program_objects_desc.size();
		program_1_desc.ppSubobjects = program_objects_desc.get();
		{
			D3D12_STATE_SUBOBJECT &object_desc = objects_desc.append();
			object_desc.Type = D3D12_STATE_SUBOBJECT_TYPE_GENERIC_PROGRAM;
			object_desc.pDesc = &program_1_desc;
		}
		
		// create program state
		D3D12_STATE_OBJECT_DESC state_desc = {};
		state_desc.Type = D3D12_STATE_OBJECT_TYPE_EXECUTABLE;
		state_desc.NumSubobjects = objects_desc.size();
		state_desc.pSubobjects = objects_desc.get();
		if(D3D12Context::error(d3d12_device->CreateStateObject(&state_desc, IID_PPV_ARGS(program_state.create())))) {
			TS_LOG(Error, "can't create state object\n");
			return 1;
		}
		
		// get state object program
		AutoComPtr<ID3D12StateObjectProperties1> state_properties;
		if(D3D12Context::error(program_state->QueryInterface(IID_PPV_ARGS(state_properties.create())))) {
			TS_LOG(Error, "can't get state properties\n");
			return 1;
		}
		program_0 = state_properties->GetProgramIdentifier(program_0_desc.ProgramName);
		program_1 = state_properties->GetProgramIdentifier(program_1_desc.ProgramName);
	}
	
	// create target
	Target target = device.createTarget(window);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// window target
		target.begin();
		{
			// create command list
			D3D12Command command = D3D12Command(device.createCommand(target));
			
			// get command list interface
			AutoComPtr<ID3D12GraphicsCommandList10> command_list;
			if(D3D12Context::error(command.getD3D12Command()->QueryInterface(IID_PPV_ARGS(command_list.create())))) {
				TS_LOG(Error, "can't get command list interface\n");
				return false;
			}
			
			// common parameters
			CommonParameters parameters = {};
			parameters.time = time;
			
			// set resources
			command.setPipeline(pipeline);
			
			// program desc
			D3D12_SET_PROGRAM_DESC program_desc = {};
			program_desc.Type = D3D12_PROGRAM_TYPE_GENERIC_PIPELINE;
			
			// draw program 0
			parameters.offset = 0;
			command.setUniform(0, parameters);
			command.update();
			
			program_desc.GenericPipeline.ProgramIdentifier = program_0;
			command_list->SetProgram(&program_desc);
			
			#if MESH_SHADER
				command.drawMesh(num_vertices, num_vertices / 2);
			#else
				command.drawArrays(num_vertices * num_vertices * 3);
			#endif
			
			// draw program 1
			parameters.offset = num_vertices / 2;
			command.setUniform(0, parameters);
			command.update();
			
			program_desc.GenericPipeline.ProgramIdentifier = program_1;
			command_list->SetProgram(&program_desc);
			
			#if MESH_SHADER
				command.drawMesh(num_vertices, num_vertices / 2);
			#else
				command.drawArrays(num_vertices * num_vertices * 3);
			#endif
		}
		target.end();
		
		if(!window.present()) return false;
		
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}

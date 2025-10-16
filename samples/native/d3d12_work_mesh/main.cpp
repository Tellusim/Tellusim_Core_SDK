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
	
	// enable experimental features
	{
		// load Direct3D12
		void *handle = System::loadLibrary("d3d12.dll");
		if(!handle) return 1;
		
		// get proc address
		typedef HRESULT (WINAPI *PFN_D3D12EnableExperimentalFeatures)(UINT, const IID*, void*, UINT*);
		PFN_D3D12EnableExperimentalFeatures D3D12EnableExperimentalFeatures = (PFN_D3D12EnableExperimentalFeatures)System::getFunction(handle, "D3D12EnableExperimentalFeatures");
		if(!D3D12EnableExperimentalFeatures) return 1;
		
		// enable required features
		UUID features[] = { D3D12ExperimentalShaderModels, D3D12StateObjectsExperiment };
		if(D3D12Context::error(D3D12EnableExperimentalFeatures(TS_COUNTOF(features), features, nullptr, nullptr))) {
			TS_LOG(Error, "can't enable experimental features\n");
			return 1;
		}
	}
	
	// create window
	String title = String::format("%s Tellusim::D3D12WorkGraphMesh", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	D3D12Device device(window);
	if(!device) return 1;
	
	// get device interface
	AutoComPtr<ID3D12Device5> d3d12_device;
	if(D3D12Context::error(device.getD3D12Device()->QueryInterface(IID_PPV_ARGS(d3d12_device.create())))) {
		TS_LOG(Error, "can't get device interface\n");
		return 1;
	}
	
	// check work graph support
	D3D12_FEATURE_DATA_D3D12_OPTIONS21 options = {};
	if(D3D12Context::error(d3d12_device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS21, &options, sizeof(options)))) {
		TS_LOG(Error, "can't get device options\n");
		return 1;
	}
	if(options.WorkGraphsTier < D3D12_WORK_GRAPHS_TIER_1_1) {
		TS_LOG(Error, "work graph 1.1 tier is not supported\n");
		return 1;
	}
	
	// create root signature pipeline
	D3D12Pipeline pipeline = D3D12Pipeline(device.createPipeline());
	pipeline.setUniformMask(0, Shader::MaskAll);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	if(!pipeline.loadShaderGLSL(Shader::TypeMesh, "main.shader", "MESH_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// load work graph shader library
	// parameters are specified in the #pragma section
	D3D12Shader shader = D3D12Shader(device.loadShader(Shader::TypeCompute, "main.hlsl"));
	if(!shader) return 1;
	
	// load fragment shader
	D3D12Shader fragment_shader = D3D12Shader(device.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1"));
	if(!fragment_shader) return 1;
	
	// create work graph
	size_t work_graph_memory = 0;
	AutoComPtr<ID3D12StateObject> work_graph_state;
	D3D12_PROGRAM_IDENTIFIER work_graph_program = {};
	{
		// work graph objects
		Array<D3D12_STATE_SUBOBJECT> objects_desc;
		Array<D3D12_STATE_SUBOBJECT*> program_objects_desc;
		
		// reserve objects (to have stable program pointers)
		objects_desc.reserve(128);
		
		// window surface
		D3D12Surface surface = D3D12Surface(window.getSurface());
		
		// state flags
		D3D12_STATE_OBJECT_CONFIG object_config = {};
		object_config.Flags = D3D12_STATE_OBJECT_FLAG_WORK_GRAPHS_USE_GRAPHICS_STATE_FOR_GLOBAL_ROOT_SIGNATURE;
		{
			D3D12_STATE_SUBOBJECT &object_desc = objects_desc.append();
			object_desc.Type = D3D12_STATE_SUBOBJECT_TYPE_STATE_OBJECT_CONFIG;
			object_desc.pDesc = &object_config;
		}
		
		// shader library desc
		D3D12_DXIL_LIBRARY_DESC library_desc = {};
		library_desc.DXILLibrary.pShaderBytecode = shader.getShaderBlob()->GetBufferPointer();
		library_desc.DXILLibrary.BytecodeLength = shader.getShaderBlob()->GetBufferSize();
		{
			D3D12_STATE_SUBOBJECT &object_desc = objects_desc.append();
			object_desc.Type = D3D12_STATE_SUBOBJECT_TYPE_DXIL_LIBRARY;
			object_desc.pDesc = &library_desc;
		}
		
		// fragment shader
		D3D12_DXIL_LIBRARY_DESC fragment_shader_desc = {};
		D3D12_EXPORT_DESC fragment_shader_export_desc = {};
		fragment_shader_desc.DXILLibrary.pShaderBytecode = fragment_shader.getShaderBlob()->GetBufferPointer();
		fragment_shader_desc.DXILLibrary.BytecodeLength = fragment_shader.getShaderBlob()->GetBufferSize();
		fragment_shader_desc.NumExports = 1;
		fragment_shader_desc.pExports = &fragment_shader_export_desc;
		fragment_shader_export_desc.Name = L"fragment";
		fragment_shader_export_desc.ExportToRename = L"*";
		{
			D3D12_STATE_SUBOBJECT &object_desc = objects_desc.append();
			object_desc.Type = D3D12_STATE_SUBOBJECT_TYPE_DXIL_LIBRARY;
			object_desc.pDesc = &fragment_shader_desc;
		}
		
		// work graph desc
		D3D12_WORK_GRAPH_DESC work_graph_desc = {};
		work_graph_desc.Flags = D3D12_WORK_GRAPH_FLAG_INCLUDE_ALL_AVAILABLE_NODES;
		work_graph_desc.ProgramName = L"WorkGraph";
		{
			D3D12_STATE_SUBOBJECT &object_desc = objects_desc.append();
			object_desc.Type = D3D12_STATE_SUBOBJECT_TYPE_WORK_GRAPH;
			object_desc.pDesc = &work_graph_desc;
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
		
		// create generic program
		D3D12_GENERIC_PROGRAM_DESC generic_program_desc = {};
		LPCWSTR generic_program_exports[] = { L"mesh", L"fragment" };
		generic_program_desc.ProgramName = L"WorkGraphMesh";
		generic_program_desc.NumExports = TS_COUNTOF(generic_program_exports);
		generic_program_desc.pExports = generic_program_exports;
		generic_program_desc.NumSubobjects = program_objects_desc.size();
		generic_program_desc.ppSubobjects = program_objects_desc.get();
		{
			D3D12_STATE_SUBOBJECT &object_desc = objects_desc.append();
			object_desc.Type = D3D12_STATE_SUBOBJECT_TYPE_GENERIC_PROGRAM;
			object_desc.pDesc = &generic_program_desc;
		}
		
		// create work graph state
		D3D12_STATE_OBJECT_DESC state_desc = {};
		state_desc.Type = D3D12_STATE_OBJECT_TYPE_EXECUTABLE;
		state_desc.NumSubobjects = objects_desc.size();
		state_desc.pSubobjects = objects_desc.get();
		if(D3D12Context::error(d3d12_device->CreateStateObject(&state_desc, IID_PPV_ARGS(work_graph_state.create())))) {
			TS_LOG(Error, "can't create state object\n");
			return 1;
		}
		
		// get state object program
		AutoComPtr<ID3D12StateObjectProperties1> state_properties;
		if(D3D12Context::error(work_graph_state->QueryInterface(IID_PPV_ARGS(state_properties.create())))) {
			TS_LOG(Error, "can't get state properties\n");
			return 1;
		}
		work_graph_program = state_properties->GetProgramIdentifier(work_graph_desc.ProgramName);
		
		// get work graph properties
		AutoComPtr<ID3D12WorkGraphProperties1> work_graph_properties;
		if(D3D12Context::error(work_graph_state->QueryInterface(IID_PPV_ARGS(work_graph_properties.create())))) {
			TS_LOG(Error, "can't get work graph properties\n");
			return 1;
		}
		uint32_t index = work_graph_properties->GetWorkGraphIndex(work_graph_desc.ProgramName);
		
		// set mesh properties
		work_graph_properties->SetMaximumInputRecords(index, 1, 1);
		
		// print work graph properties
		TS_LOGF(Message, " Graphs: %u\n", work_graph_properties->GetNumWorkGraphs());
		TS_LOGF(Message, "  Nodes: %u\n", work_graph_properties->GetNumNodes(index));
		TS_LOGF(Message, "Entries: %u\n", work_graph_properties->GetNumEntrypoints(index));
		for(uint32_t i = 0; i < work_graph_properties->GetNumEntrypoints(index); i++) {
			TS_LOGF(Message, "  Input: %s\n", String::fromBytes(work_graph_properties->GetEntrypointRecordSizeInBytes(index, i)).get());
		}
		
		// get memory requirements
		D3D12_WORK_GRAPH_MEMORY_REQUIREMENTS memory_requirements = {};
		work_graph_properties->GetWorkGraphMemoryRequirements(index, &memory_requirements);
		work_graph_memory = memory_requirements.MaxSizeInBytes;
		
		// print memory requirements
		TS_LOGF(Message, "    MinSize: %s\n", String::fromBytes(memory_requirements.MinSizeInBytes).get());
		TS_LOGF(Message, "    MaxSize: %s\n", String::fromBytes(memory_requirements.MaxSizeInBytes).get());
		TS_LOGF(Message, "Granularity: %s\n", String::fromBytes(memory_requirements.SizeGranularityInBytes).get());
	}
	
	// create backing buffer
	D3D12Buffer buffer = D3D12Buffer(device.createBuffer(Buffer::FlagStorage, work_graph_memory));
	if(!buffer) return 1;
	
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
			
			// set resources
			command.setPipeline(pipeline);
			command.setUniform(0, time);
			
			if(!window.getKeyboardKey('m')) {
				
				// flush resources
				command.update();
				
				// set work graph
				D3D12_SET_PROGRAM_DESC program_desc = {};
				program_desc.Type = D3D12_PROGRAM_TYPE_WORK_GRAPH;
				program_desc.WorkGraph.ProgramIdentifier = work_graph_program;
				if(frame_counter == 0) program_desc.WorkGraph.Flags = D3D12_SET_WORK_GRAPH_FLAG_INITIALIZE;
				program_desc.WorkGraph.BackingMemory.StartAddress = buffer.getBufferAddress();
				program_desc.WorkGraph.BackingMemory.SizeInBytes = buffer.getSize();
				command_list->SetProgram(&program_desc);
				
				// dispatch work graph
				D3D12_DISPATCH_GRAPH_DESC dispatch_desc = {};
				dispatch_desc.Mode = D3D12_DISPATCH_MODE_NODE_CPU_INPUT;
				dispatch_desc.NodeCPUInput.EntrypointIndex = 0;
				dispatch_desc.NodeCPUInput.NumRecords = 1;
				dispatch_desc.NodeCPUInput.pRecords = nullptr;
				dispatch_desc.NodeCPUInput.RecordStrideInBytes = 0;
				command_list->DispatchGraph(&dispatch_desc);
			}
			else {
				
				// draw mesh shader
				command.drawMesh(16 * 8, 16 * 8);
			}
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

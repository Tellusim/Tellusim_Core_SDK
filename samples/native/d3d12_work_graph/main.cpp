// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <d3d12.h>

#include <common/common.h>
#include <core/TellusimSystem.h>
#include <core/TellusimPointer.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimContext.h>
#include <platform/TellusimCompute.h>
#include <platform/TellusimCommand.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimPipeline.h>

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
	
	DECLARE_WINDOW
	
	// load DXCompiler libraries
	System::loadLibrary(D3D12_SDK_PATH "/dxil.dll");
	System::loadLibrary(D3D12_SDK_PATH "/dxcompiler.dll");
	
	// create window
	String title = String::format("%s Tellusim::D3D12WorkGraph", window.getPlatformName());
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
	if(options.WorkGraphsTier == D3D12_WORK_GRAPHS_TIER_NOT_SUPPORTED) {
		TS_LOG(Error, "work graph 1.0 tier is not supported\n");
		return 1;
	}
	
	// create root signature kernel (pointer must be moved)
	D3D12Kernel kernel = D3D12Kernel(move(device.createKernel().setSurfaces(1).setUniforms(1)));
	if(!kernel.loadShaderGLSL("main.shader", "COMPUTE_SHADER=1")) return 1;
	if(!kernel.create()) return 1;
	
	// load work graph shader library
	// parameters are specified in the #pragma section
	D3D12Shader shader = D3D12Shader(device.loadShader(Shader::TypeCompute, "main.hlsl"));
	if(!shader) return 1;
	
	// create work graph
	size_t work_graph_memory = 0;
	AutoComPtr<ID3D12StateObject> work_graph_state;
	D3D12_PROGRAM_IDENTIFIER work_graph_program = {};
	{
		// work graph objects
		Array<D3D12_STATE_SUBOBJECT> objects_desc;
		
		// shader library desc
		D3D12_DXIL_LIBRARY_DESC library_desc = {};
		library_desc.DXILLibrary.pShaderBytecode = shader.getShaderBlob()->GetBufferPointer();
		library_desc.DXILLibrary.BytecodeLength = shader.getShaderBlob()->GetBufferSize();
		{
			D3D12_STATE_SUBOBJECT &object_desc = objects_desc.append();
			object_desc.Type = D3D12_STATE_SUBOBJECT_TYPE_DXIL_LIBRARY;
			object_desc.pDesc = &library_desc;
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
		ID3D12RootSignature *root_signature = kernel.getRootSignature();
		{
			D3D12_STATE_SUBOBJECT &object_desc = objects_desc.append();
			object_desc.Type = D3D12_STATE_SUBOBJECT_TYPE_GLOBAL_ROOT_SIGNATURE;
			object_desc.pDesc = &root_signature;
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
		AutoComPtr<ID3D12WorkGraphProperties> work_graph_properties;
		if(D3D12Context::error(work_graph_state->QueryInterface(IID_PPV_ARGS(work_graph_properties.create())))) {
			TS_LOG(Error, "can't get work graph properties\n");
			return 1;
		}
		uint32_t index = work_graph_properties->GetWorkGraphIndex(work_graph_desc.ProgramName);
		
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
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setSamplerMask(0, Shader::MaskFragment);
	pipeline.setTextureMask(0, Shader::MaskFragment);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
	// create sampler
	Sampler sampler = device.createSampler(Sampler::FilterLinear, Sampler::WrapModeClamp);
	if(!sampler) return 1;
	
	// create surface
	constexpr uint32_t size = 1024;
	D3D12Texture surface = D3D12Texture(device.createTexture2D(FormatRGBAu8n, size, Texture::FlagSurface));
	if(!surface) return 1;
	
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
		
		{
			// create command list
			D3D12Compute compute = D3D12Compute(device.createCompute());
			
			// get command list interface
			AutoComPtr<ID3D12GraphicsCommandList10> command_list;
			if(D3D12Context::error(compute.getCommand()->QueryInterface(IID_PPV_ARGS(command_list.create())))) {
				TS_LOG(Error, "can't get command list interface\n");
				return false;
			}
			
			// set resources
			compute.setKernel(kernel);
			compute.setUniform(0, time);
			compute.setSurfaceTexture(0, surface);
			compute.update();
			
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
			
			// surface barrier
			compute.barrier(surface);
		}
		
		// flush texture
		device.flushTexture(surface);
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// draw texture
			command.setPipeline(pipeline);
			command.setSampler(0, sampler);
			command.setTexture(0, surface);
			command.drawArrays(3);
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

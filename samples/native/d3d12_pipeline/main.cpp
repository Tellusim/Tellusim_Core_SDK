// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <d3d12.h>

#include <common/common.h>
#include <core/TellusimPointer.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimSurface.h>
#include <platform/TellusimContext.h>
#include <platform/TellusimCommand.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	App::setPlatform(PlatformD3D12);
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::D3D12Pipeline", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	D3D12Device device(window);
	if(!device) return 1;
	
	// load vertex shader
	D3D12Shader vertex_shader = D3D12Shader(device.loadShader(Shader::TypeVertex, "main.hlsl", "VERTEX_SHADER=1"));
	if(!vertex_shader) return 1;
	
	// load fragment shader
	D3D12Shader fragment_shader = D3D12Shader(device.loadShader(Shader::TypeFragment, "main.hlsl", "FRAGMENT_SHADER=1"));
	if(!fragment_shader) return 1;
	
	// create root signature
	AutoComPtr<ID3D12RootSignature> root_signature;
	{
		D3D12_ROOT_PARAMETER parameters[1] = {};
		parameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
		parameters[0].Constants.ShaderRegister = 0;
		parameters[0].Constants.RegisterSpace = 0;
		parameters[0].Constants.Num32BitValues = 2;
		parameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
		
		D3D12_ROOT_SIGNATURE_DESC signature_desc = {};
		signature_desc.NumParameters = 1;
		signature_desc.pParameters = parameters;
		signature_desc.NumStaticSamplers = 0;
		signature_desc.pStaticSamplers = nullptr;
		
		typedef HRESULT (WINAPI *PFN_D3D12SerializeRootSignature)(const D3D12_ROOT_SIGNATURE_DESC*, D3D_ROOT_SIGNATURE_VERSION, ID3DBlob**, ID3DBlob**);
		PFN_D3D12SerializeRootSignature D3D12SerializeRootSignature = (PFN_D3D12SerializeRootSignature)D3D12Context::getProcAddress("D3D12SerializeRootSignature");
		if(!D3D12SerializeRootSignature) return 1;
		
		ID3DBlob *signature_blob, *error_blob;
		ID3D12Device *d3d12_device = device.getD3D12Device();
		if(D3D12Context::error(D3D12SerializeRootSignature(&signature_desc, D3D_ROOT_SIGNATURE_VERSION_1, &signature_blob, &error_blob))) return 1;
		if(D3D12Context::error(d3d12_device->CreateRootSignature(0, signature_blob->GetBufferPointer(), signature_blob->GetBufferSize(), IID_PPV_ARGS(root_signature.create())))) return 1;
	}
	
	// create pipeline state
	AutoComPtr<ID3D12PipelineState> pipeline_state;
	{
		D3D12Surface surface = D3D12Surface(window.getSurface());
		
		D3D12_GRAPHICS_PIPELINE_STATE_DESC state_desc = {};
		
		state_desc.pRootSignature = root_signature.get();
		
		state_desc.VS.pShaderBytecode = vertex_shader.getShaderBlob()->GetBufferPointer();
		state_desc.VS.BytecodeLength = vertex_shader.getShaderBlob()->GetBufferSize();
		
		state_desc.PS.pShaderBytecode = fragment_shader.getShaderBlob()->GetBufferPointer();
		state_desc.PS.BytecodeLength = fragment_shader.getShaderBlob()->GetBufferSize();
		
		state_desc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
		state_desc.SampleMask = UINT_MAX;
		
		state_desc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
		state_desc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
		state_desc.RasterizerState.FrontCounterClockwise = TRUE;
		state_desc.RasterizerState.DepthClipEnable = TRUE;
		
		state_desc.DepthStencilState.DepthEnable = FALSE;
		state_desc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
		state_desc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS;
		
		state_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		
		state_desc.NumRenderTargets = 1;
		state_desc.RTVFormats[0] = (DXGI_FORMAT)surface.getColorDXGIFormat();
		state_desc.DSVFormat = (DXGI_FORMAT)surface.getDepthDXGIFormat();
		state_desc.SampleDesc.Count = 1;
		
		ID3D12Device *d3d12_device = device.getD3D12Device();
		if(D3D12Context::error(d3d12_device->CreateGraphicsPipelineState(&state_desc, IID_PPV_ARGS(pipeline_state.create())))) return 1;
	}
	
	// create target
	Target target = device.createTarget(window);
	target.setClearColor(Color("#7fba00"));
	
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
			ID3D12GraphicsCommandList *command_list = command.getD3D12Command();
			
			// set viewport
			D3D12_VIEWPORT viewport = {};
			viewport.Width = (float32_t)target.getWidth();
			viewport.Height = (float32_t)target.getHeight();
			command_list->RSSetViewports(1, &viewport);
			
			// set scissor
			D3D12_RECT scissor = {};
			scissor.right = target.getWidth();
			scissor.bottom = target.getHeight();
			command_list->RSSetScissorRects(1, &scissor);
			
			// aspect ratio
			float32_t aspect = (float32_t)target.getWidth() / target.getHeight();
			
			// set pipeline state
			command_list->SetGraphicsRootSignature(root_signature.get());
			command_list->SetGraphicsRoot32BitConstant(0, f32u32(aspect).u, 0);
			command_list->SetGraphicsRoot32BitConstant(0, f32u32(time).u, 1);
			command_list->SetPipelineState(pipeline_state.get());
			
			// primitive topology
			command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			
			// draw triangle
			command_list->DrawInstanced(3, 1, 0, 0);
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

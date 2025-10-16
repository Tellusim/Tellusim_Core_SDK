// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <d3d11.h>

#include <common/common.h>
#include <core/TellusimPointer.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimContext.h>
#include <platform/TellusimCommand.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	App::setPlatform(PlatformD3D11);
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::D3D11Pipeline", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	D3D11Device device = D3D11Device(Device(window));
	if(!device) return 1;
	
	// device pointer
	ID3D11Device *d3d11_device = device.getD3D11Device();
	
	// load vertex shader
	D3D11Shader vertex_shader = D3D11Shader(device.loadShader(Shader::TypeVertex, "main.hlsl", "VERTEX_SHADER=1"));
	if(!vertex_shader) return 1;
	
	// load fragment shader
	D3D11Shader fragment_shader = D3D11Shader(device.loadShader(Shader::TypeFragment, "main.hlsl", "FRAGMENT_SHADER=1"));
	if(!fragment_shader) return 1;
	
	// create blend state
	AutoComPtr<ID3D11BlendState> blend_state;
	{
		D3D11_BLEND_DESC blend_desc = {};
		blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		
		if(D3D11Context::error(d3d11_device->CreateBlendState(&blend_desc, blend_state.create()))) return 1;
	}
	
	// create rasterizer state
	AutoComPtr<ID3D11RasterizerState> rasterizer_state;
	{
		D3D11_RASTERIZER_DESC rasterizer_desc = {};
		rasterizer_desc.FillMode = D3D11_FILL_SOLID;
		rasterizer_desc.CullMode = D3D11_CULL_BACK;
		rasterizer_desc.FrontCounterClockwise = TRUE;
		rasterizer_desc.DepthClipEnable = TRUE;
		
		if(D3D11Context::error(d3d11_device->CreateRasterizerState(&rasterizer_desc, rasterizer_state.create()))) return 1;
	}
	
	// create depth stencil state
	AutoComPtr<ID3D11DepthStencilState> depth_stencil_state;
	{
		D3D11_DEPTH_STENCIL_DESC depth_stencil_desc = {};
		depth_stencil_desc.DepthEnable = TRUE;
		depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		
		if(D3D11Context::error(d3d11_device->CreateDepthStencilState(&depth_stencil_desc, depth_stencil_state.create()))) return 1;
	}
	
	// create parameters buffer
	AutoComPtr<ID3D11Buffer> parameters_buffer;
	{
		D3D11_BUFFER_DESC buffer_desc = {};
		buffer_desc.Usage = D3D11_USAGE_DEFAULT;
		buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		
		buffer_desc.ByteWidth = sizeof(float32_t) * 4;
		if(D3D11Context::error(d3d11_device->CreateBuffer(&buffer_desc, nullptr, parameters_buffer.create()))) return 1;
	}
	
	// create target
	D3D11Target target = D3D11Target(device.createTarget(window));
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
			// get device context interface
			ID3D11DeviceContext *command = device.getCommand();
			
			// set viewport
			D3D11_VIEWPORT viewport = {};
			viewport.Width = (float32_t)target.getWidth();
			viewport.Height = (float32_t)target.getHeight();
			command->RSSetViewports(1, &viewport);
			
			// set scissor
			D3D11_RECT scissor = {};
			scissor.right = target.getWidth();
			scissor.bottom = target.getHeight();
			command->RSSetScissorRects(1, &scissor);
			
			// set render targets
			command->OMSetRenderTargets(1, target.getRenderTargetViews(), target.getDepthStencilView());
			
			// set input assembler
			command->IASetInputLayout(nullptr);
			
			// set states
			command->RSSetState(rasterizer_state.get());
			command->OMSetBlendState(blend_state.get(), nullptr, UINT_MAX);
			command->OMSetDepthStencilState(depth_stencil_state.get(), 0x00);
			
			// set shaders
			command->VSSetShader((ID3D11VertexShader*)vertex_shader.getD3D11Shader(), nullptr, 0);
			command->PSSetShader((ID3D11PixelShader*)fragment_shader.getD3D11Shader(), nullptr, 0);
			
			// create parameters
			float32_t parameters[4];
			parameters[0] = (float32_t)target.getWidth() / target.getHeight();
			parameters[1] = time;
			
			// set parameters
			ID3D11Buffer *buffer = parameters_buffer.get();
			command->UpdateSubresource(parameters_buffer.get(), 0, nullptr, parameters, 0, 0);
			command->VSSetConstantBuffers(0, 1, &buffer);
			
			// primitive topology
			command->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			
			// draw triangle
			command->DrawInstanced(3, 1, 0, 0);
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

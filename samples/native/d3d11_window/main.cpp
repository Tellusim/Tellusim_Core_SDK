// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <dxgi.h>
#include <d3d11.h>
#include <windows.h>
#include <shellscalingapi.h>

#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <math/TellusimMath.h>
#include <platform/TellusimContext.h>
#include <platform/TellusimSurface.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>
#include <platform/TellusimDevice.h>

/*
 */
#define EXTERNAL_DEVICE		1

/*
 */
namespace Tellusim {
	
	/*
	 */
	class D3D11Window {
			
		public:
			
			D3D11Window();
			~D3D11Window();
			
			// create window
			bool create();
			
			// main loop
			bool run();
			
		private:
			
			// window procedure
			static LRESULT CALLBACK window_proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
			
			// create context
			bool create_context();
			void release_context();
			
			// create swap chain
			bool create_swap_chain();
			void release_swap_chain();
			
			// create buffers
			bool create_buffers();
			void release_buffers();
			
			// rendering loop
			bool create_d3d11();
			bool render_d3d11();
			
			enum {
				Samples = 4,
			};
			
			static bool done;
			
			uint32_t width = 0;
			uint32_t height = 0;
			
			HWND window = nullptr;
			
			IDXGIFactory *dxgi_factory = nullptr;
			ID3D11Device *d3d11_device = nullptr;
			IDXGISwapChain *dxgi_swap_chain = nullptr;
			
			ID3D11Texture2D *render_target = nullptr;
			ID3D11RenderTargetView *render_target_view = nullptr;
			
			D3D11Context context;
			D3D11Surface surface;
			
			Device device;
			
			Pipeline pipeline;
			Buffer vertex_buffer;
			Buffer index_buffer;
			
			D3D11Texture depth_stencil_texture;
	};
	
	/*
	 */
	bool D3D11Window::done = false;
	
	/*
	 */
	D3D11Window::D3D11Window() {
		
	}
	
	D3D11Window::~D3D11Window() {
		
		// release context
		release_context();
	}
	
	/*
	 */
	bool D3D11Window::create() {
		
		TS_ASSERT(window == nullptr);
		
		// dpi awareness
		SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
		
		// module handle
		HINSTANCE instance = GetModuleHandleW(nullptr);
		
		// window parameters
		const wchar_t *class_name = L"Tellusim::D3D11Window";
		const wchar_t *window_title = L"Direct3D11 Tellusim::D3D11Window";
		
		// register class
		WNDCLASSEXW window_class = {};
		window_class.cbSize = sizeof(window_class);
		window_class.style = CS_HREDRAW | CS_VREDRAW;
		window_class.lpfnWndProc = window_proc;
		window_class.hInstance = instance;
		window_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
		window_class.hbrBackground = nullptr;
		window_class.lpszMenuName = nullptr;
		window_class.lpszClassName = class_name;
		if(!RegisterClassExW(&window_class)) {
			TS_LOGE(Error, "D3D11Window::create(): RegisterClassEx(): failed\n");
			return false;
		}
		
		// window size
		width = 1600;
		height = 900;
		RECT rect = {};
		rect.right = width;
		rect.bottom = height;
		uint32_t style = WS_OVERLAPPEDWINDOW;
		AdjustWindowRectEx(&rect, style, 0, 0);
		
		// create window
		LONG window_width = rect.right - rect.left;
		LONG window_height = rect.bottom - rect.top;
		window = CreateWindowExW(0, class_name, window_title, style, CW_USEDEFAULT, CW_USEDEFAULT, window_width, window_height, nullptr, nullptr, instance, nullptr);
		if(window == nullptr) {
			TS_LOGE(Error, "D3D11Window::create(): CreateWindowExW(): failed\n");
			return false;
		}
		
		// show window
		ShowWindow(window, true);
		
		// create context
		if(!create_context()) {
			TS_LOG(Error, "D3D11Window::create(): can't create context\n");
			return false;
		}
		
		// create swap chain
		if(!create_swap_chain()) {
			TS_LOG(Error, "D3D11Window::create(): can't create swap chain\n");
			return false;
		}
		
		// create buffers
		if(!create_buffers()) {
			TS_LOG(Error, "D3D11Window::create(): can't create buffers\n");
			return false;
		}
		
		// create Direct3D11
		if(!create_d3d11()) {
			TS_LOG(Error, "D3D11Window::create(): can't create Direct3D11\n");
			return false;
		}
		
		return true;
	}
	
	/*
	 */
	bool D3D11Window::create_context() {
		
		TS_ASSERT(d3d11_device == nullptr);
		
		#if EXTERNAL_DEVICE
			
			// create factory
			if(D3D11Context::error(CreateDXGIFactory(IID_PPV_ARGS(&dxgi_factory)))) {
				TS_LOG(Error, "D3D11Window::create_context(): can't create factory\n");
				release_context();
				return false;
			}
			
			// enumerate adapters
			IDXGIAdapter *adapter = nullptr;
			if(D3D11Context::error(dxgi_factory->EnumAdapters(0, &adapter)) || adapter == nullptr) {
				TS_LOG(Error, "D3D11Window::create_context(): can't enum adapters\n");
				release_context();
				return false;
			}
			
			// create device
			ID3D11DeviceContext *d3d11_context = nullptr;
			D3D_DRIVER_TYPE type = D3D_DRIVER_TYPE_UNKNOWN;
			D3D_FEATURE_LEVEL feature_level = D3D_FEATURE_LEVEL_11_1;
			if(D3D11Context::error(D3D11CreateDevice(adapter, type, nullptr, 0, &feature_level, 1, D3D11_SDK_VERSION, &d3d11_device, nullptr, &d3d11_context))) {
				TS_LOG(Error, "D3D11Window::create_context(): can't create device\n");
				adapter->Release();
				release_context();
				return false;
			}
			d3d11_context->Release();
			adapter->Release();
			
			// create external context
			if(!context.create(d3d11_device)) {
				TS_LOG(Error, "D3D11Window::create_context(): can't create context\n");
				return false;
			}
			
			// create external surface
			surface = D3D11Surface(context);
			if(!surface) {
				TS_LOG(Error, "D3D11Window::create_context(): can't create context\n");
				return false;
			}
			
		#else
			
			// create internal context
			if(!context.create()) {
				TS_LOG(Error, "D3D11Window::create_context(): can't create context\n");
				return false;
			}
			
			// create internal surface
			surface = D3D11Surface(context);
			if(!surface) {
				TS_LOG(Error, "D3D11Window::create_context(): can't create context\n");
				return false;
			}
			
			// internal interfaces
			dxgi_factory = surface.getFactory();
			d3d11_device = surface.getDevice();
			
		#endif
		
		// configure window
		if(D3D11Context::error(dxgi_factory->MakeWindowAssociation(window, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER))) {
			TS_LOG(Error, "D3D11Window::create_context(): can't set window association\n");
			return false;
		}
		
		// create device
		device = Device(surface);
		if(!device) {
			TS_LOG(Error, "D3D11Window::create_context(): can't create device\n");
			return false;
		}
		
		return true;
	}
	
	void D3D11Window::release_context() {
		
		// release resources
		release_buffers();
		release_swap_chain();
		
		// release resources
		pipeline.clearPtr();
		index_buffer.clearPtr();
		vertex_buffer.clearPtr();
		device.clearPtr();
		
		// release context
		surface.clearPtr();
		context.clearPtr();
	}
	
	/*
	 */
	bool D3D11Window::create_swap_chain() {
		
		TS_ASSERT(dxgi_swap_chain == nullptr);
		
		// create swap chain
		DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
		swap_chain_desc.BufferDesc.Width = width;
		swap_chain_desc.BufferDesc.Height = height;
		swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swap_chain_desc.SampleDesc.Count = Samples;
		swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_desc.BufferCount = 1;
		swap_chain_desc.OutputWindow = window;
		swap_chain_desc.Windowed = TRUE;
		swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swap_chain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		if(D3D11Context::error(dxgi_factory->CreateSwapChain(d3d11_device, &swap_chain_desc, &dxgi_swap_chain))) {
			TS_LOG(Error, "D3D11Window::create_swap_chain(): can't create swap chain\n");
			return false;
		}
		
		// surface size
		surface.setSize(width, height);
		surface.setMultisample(Samples);
		
		return true;
	}
	
	void D3D11Window::release_swap_chain() {
		
		// release swap chain
		if(dxgi_swap_chain) dxgi_swap_chain->Release();
		dxgi_swap_chain = nullptr;
	}
	
	/*
	 */
	bool D3D11Window::create_buffers() {
		
		TS_ASSERT(!depth_stencil_texture);
		
		// get render target
		if(D3D11Context::error(dxgi_swap_chain->GetBuffer(0, IID_PPV_ARGS(&render_target)))) {
			TS_LOG(Error, "D3D11Window::create_buffers(): can't get render target\n");
			release_buffers();
			return false;
		}
		
		if(D3D11Context::error(d3d11_device->CreateRenderTargetView(render_target, nullptr, &render_target_view))) {
			TS_LOG(Error, "D3D11Window::create_buffers(): can't create render target view\n");
			release_buffers();
			return false;
		}
		
		// create depth stencil
		depth_stencil_texture = device.createTexture2D(FormatDu24Su8, width, height, Texture::FlagTarget | Texture::FlagMultisample4);
		if(!depth_stencil_texture) {
			TS_LOG(Error, "D3D11Window::create_buffers(): can't create depth stencil\n");
			return false;
		}
		
		// surface size
		surface.setSize(width, height);
		
		return true;
	}
	
	void D3D11Window::release_buffers() {
		
		// release buffers
		if(render_target_view) render_target_view->Release();
		if(render_target) render_target->Release();
		render_target = nullptr;
		render_target_view = nullptr;
		
		// release depth stencil
		depth_stencil_texture.clearPtr();
	}
	
	/*
	 */
	bool D3D11Window::create_d3d11() {
		
		// create surface
		surface.setColorFormat(FormatRGBAu8n);
		surface.setDepthFormat(depth_stencil_texture.getFormat());
		
		// create pipeline
		pipeline = device.createPipeline();
		pipeline.setUniformMask(0, Shader::MaskVertex);
		pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, sizeof(float32_t) * 0, sizeof(float32_t) * 6);
		pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, sizeof(float32_t) * 3, sizeof(float32_t) * 6);
		pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
		pipeline.setColorFormat(surface.getColorFormat());
		pipeline.setDepthFormat(surface.getDepthFormat());
		pipeline.setMultisample(surface.getMultisample());
		if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return false;
		if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return false;
		if(!pipeline.create()) return false;
		
		// create mesh geometry
		#include "main_mesh.h"
		vertex_buffer = device.createBuffer(Buffer::FlagVertex, mesh_vertices, sizeof(float32_t) * num_mesh_vertices);
		index_buffer = device.createBuffer(Buffer::FlagIndex, mesh_indices, sizeof(uint32_t) * num_mesh_indices);
		if(!vertex_buffer || !index_buffer) return false;
		
		return true;
	}
	
	/*
	 */
	bool D3D11Window::render_d3d11() {
		
		// structures
		struct CommonParameters {
			Matrix4x4f projection;
			Matrix4x4f modelview;
			Matrix4x4f transform;
			Vector4f camera;
		};
		
		// surface render target
		surface.setRenderTargetView(render_target_view);
		surface.setDepthStencilView(depth_stencil_texture.getDepthStencilView());
		
		// widget target
		Target target = device.createTarget(surface);
		target.setClearColor(Color("#7fba00"));
		target.begin();
		{
			// current time
			float32_t time = (float32_t)Time::seconds();
			
			// common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Vector4f(2.0f, 2.0f, 1.0f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)surface.getWidth() / surface.getHeight(), 0.1f, 1000.0f);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f::zero, Vector3f::oneZ);
			common_parameters.transform = Matrix4x4f::rotateZ(time * 32.0f) * Matrix4x4f::rotateY(60.0f + time * 8.0f);
			
			// create command list
			Command command = device.createCommand(target);
			
			// draw mesh
			command.setPipeline(pipeline);
			command.setUniform(0, common_parameters);
			command.setVertexBuffer(0, vertex_buffer);
			command.setIndexBuffer(FormatRu32, index_buffer);
			command.drawElements((uint32_t)index_buffer.getSize() / 4);
		}
		target.end();
		
		// present swap chain
		HRESULT result = dxgi_swap_chain->Present(1, 0);
		if(result != DXGI_STATUS_OCCLUDED && D3D11Context::error(result)) {
			TS_LOGF(Error, "D3D11Window::render_d3d11(): can't present swap chain 0x%08x\n", result);
			return false;
		}
		
		return true;
	}
	
	/*
	 */
	LRESULT CALLBACK D3D11Window::window_proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
		
		// destroy message
		if(message == WM_DESTROY) done = true;
		
		// escape key
		if(message == WM_KEYDOWN && wparam == VK_ESCAPE) done = true;
		
		// default window procedure
		return DefWindowProcW(window, message, wparam, lparam);
	}
	
	/*
	 */
	bool D3D11Window::run() {
		
		// main loop
		while(!done) {
			
			// window size
			RECT rect = {};
			uint32_t old_width = width;
			uint32_t old_height = height;
			GetClientRect(window, &rect);
			width = rect.right - rect.left;
			height = rect.bottom - rect.top;
			if(!width) width = old_width;
			if(!height) height = old_height;
			
			// resize buffers
			if(old_width != width || old_height != height) {
				release_buffers();
				if(D3D11Context::error(dxgi_swap_chain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH))) {
					TS_LOG(Error, "D3D11Window::run(): can't resize swap chain\n");
					return false;
				}
				if(!create_buffers()) {
					TS_LOG(Error, "D3D11Window::run(): can't create buffers\n");
					return false;
				}
			}
			
			// process messages
			MSG message = {};
			while(PeekMessageW(&message, nullptr, 0, 0, PM_NOREMOVE)) {
				if(GetMessageW(&message, nullptr, 0, 0) == 0) break;
				DispatchMessageW(&message);
			}
			
			// render application
			if(!render_d3d11()) {
				return false;
			}
		}
		
		return true;
	}
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create window
	Tellusim::D3D11Window window;
	if(!window.create()) return 1;
	
	// run application
	window.run();
	
	return 0;
}

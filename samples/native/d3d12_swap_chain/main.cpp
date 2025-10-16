// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <d3d12.h>
#include <dxgi1_5.h>

#include <common/common.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimContext.h>
#include <platform/TellusimSurface.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>

/*
 */
using namespace Tellusim;

/*
 */
namespace Tellusim {
	
	/*
	 */
	class D3D12Window : public Window {
			
		public:
			
			// constructor
			explicit D3D12Window(Platform platform, uint32_t index = Maxu32);
			virtual ~D3D12Window();
			
			// create window
			virtual bool create(const char *title, Flags flags = DefaultFlags);
			virtual bool create(const String &title, Flags flags = DefaultFlags);
			virtual bool create(Flags flags = DefaultFlags);
			virtual void release();
			
			// render window
			virtual bool render();
			virtual bool present();
			virtual bool finish();
			
		private:
			
			// create swap chain
			bool create_swap_chain();
			void release_swap_chain();
			
			// create buffers
			bool create_buffers();
			void release_buffers();
			
			enum {
				NumFrames = 3,
			};
			
			Context context;
			D3D12Surface surface;
			D3D12Device device;
			
			uint32_t swap_chain_flags = 0;
			IDXGISwapChain3 *swap_chain = nullptr;
			
			ID3D12Resource *render_targets[NumFrames] = {};
			ID3D12DescriptorHeap *render_target_heap = nullptr;
			D3D12_CPU_DESCRIPTOR_HANDLE render_target_views[NumFrames] = {};
			
			D3D12Texture depth_stencil_texture;
	};
	
	/*
	 */
	D3D12Window::D3D12Window(Platform platform, uint32_t index) : Window(PlatformUnknown), context(platform, index) {
		
		// create context
		D3D12Context d3d12_context = D3D12Context(context);
		if(!d3d12_context || !d3d12_context.create()) return;
		
		// create surface
		surface = D3D12Surface(d3d12_context);
		if(!surface) return;
		
		// set surface
		setSurface(surface);
	}
	
	/*
	 */
	D3D12Window::~D3D12Window() {
		release();
	}
	
	/*
	 */
	bool D3D12Window::create(const char *title, Flags flags) {
		setTitle(title);
		return create(flags);
	}
	
	bool D3D12Window::create(const String &title, Flags flags) {
		setTitle(title);
		return create(flags);
	}
	
	bool D3D12Window::create(Flags flags) {
		
		// check surface
		if(!surface) return false;
		
		// create window
		if(!Window::create(flags)) return false;
		
		// surface format
		surface.setColorFormat(FormatRGBAu8n);
		surface.setDepthFormat(FormatDu24Su8);
		
		// create device
		device = Device(surface);
		if(!device) return false;
		
		return true;
	}
	
	void D3D12Window::release() {
		
		// release buffers
		release_buffers();
		
		// release swap chain
		release_swap_chain();
	}
	
	/*
	 */
	bool D3D12Window::create_swap_chain() {
		
		TS_ASSERT(!swap_chain && "D3D12Window::create_swap_chain(): is already created");
		
		IDXGIFactory4 *factory = surface.getFactory();
		ID3D12CommandQueue *d3d12_queue = surface.getQueue();
		
		// swap chain flags
		IDXGIFactory5 *factory5 = nullptr;
		swap_chain_flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		if(factory->QueryInterface(IID_PPV_ARGS(&factory5)) == S_OK) {
			BOOL allow_tearing = false;
			if(factory5->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &allow_tearing, sizeof(allow_tearing)) == S_OK && allow_tearing) {
				swap_chain_flags |= DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
			}
			factory5->Release();
		}
		
		// create swap chain
		DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
		swap_chain_desc.BufferDesc.Width = getWidth();
		swap_chain_desc.BufferDesc.Height = getHeight();
		swap_chain_desc.BufferDesc.Format = (DXGI_FORMAT)surface.getColorDXGIFormat();
		swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swap_chain_desc.SampleDesc.Count = 1;
		swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_desc.BufferCount = NumFrames;
		swap_chain_desc.OutputWindow = (HWND)getHandle();
		swap_chain_desc.Windowed = TRUE;
		swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swap_chain_desc.Flags = swap_chain_flags;
		
		IDXGISwapChain *swap_chain1 = nullptr;
		HRESULT result = factory->CreateSwapChain(d3d12_queue, &swap_chain_desc, &swap_chain1);
		if(result != DXGI_STATUS_OCCLUDED && D3D12Context::error(result)) {
			TS_LOG(Error, "D3D12Window::create_swap_chain(): can't create swap chain\n");
			return false;
		}
		
		// query swap chain interface
		if(D3D12Context::error(swap_chain1->QueryInterface(IID_PPV_ARGS(&swap_chain)))) {
			TS_LOG(Error, "D3D12Window::create_swap_chain(): can't get swap chain\n");
			swap_chain->Release();
			return false;
		}
		swap_chain1->Release();
		
		// configure window
		if(D3D12Context::error(factory->MakeWindowAssociation((HWND)getHandle(), DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER))) {
			TS_LOG(Error, "D3D12Window::create_swap_chain(): can't set window association\n");
			return false;
		}
		
		return true;
	}
	
	void D3D12Window::release_swap_chain() {
		
		// release swap chain
		if(swap_chain) {
			swap_chain->SetFullscreenState(FALSE, nullptr);
			swap_chain->Release();
		}
		swap_chain = nullptr;
	}
	
	/*
	 */
	bool D3D12Window::create_buffers() {
		
		TS_ASSERT(!depth_stencil_texture && "D3D12Window::create_buffers(): is already created");
		
		ID3D12Device *d3d12_device = surface.getDevice();
		
		// get render targets
		for(uint32_t i = 0; i < NumFrames; i++) {
			if(D3D12Context::error(swap_chain->GetBuffer(i, IID_PPV_ARGS(&render_targets[i])))) {
				TS_LOG(Error, "D3D12Window::create_buffers(): can't get render target\n");
				return false;
			}
		}
		
		// create render target heap
		D3D12_DESCRIPTOR_HEAP_DESC render_target_heap_desc = {};
		render_target_heap_desc.NumDescriptors = NumFrames;
		render_target_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		render_target_heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		if(D3D12Context::error(d3d12_device->CreateDescriptorHeap(&render_target_heap_desc, IID_PPV_ARGS(&render_target_heap)))) {
			TS_LOG(Error, "D3D12Window::create_buffers(): can't create descriptor heap\n");
			return false;
		}
		
		// create render target views
		D3D12_RENDER_TARGET_VIEW_DESC render_target_view_desc = {};
		render_target_view_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		render_target_view_desc.Format = (DXGI_FORMAT)surface.getColorDXGIFormat();
		
		size_t render_target_heap_ptr = render_target_heap->GetCPUDescriptorHandleForHeapStart().ptr;
		uint32_t render_target_heap_stride = d3d12_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		for(uint32_t i = 0; i < NumFrames; i++) {
			render_target_views[i].ptr = render_target_heap_ptr + render_target_heap_stride * i;
			d3d12_device->CreateRenderTargetView(render_targets[i], &render_target_view_desc, render_target_views[i]);
		}
		
		// create depth stencil
		depth_stencil_texture = device.createTexture2D(surface.getDepthFormat(), getWidth(), getHeight(), Texture::FlagTarget);
		if(!depth_stencil_texture) {
			TS_LOG(Error, "D3D12Window::create_buffers(): can't create depth stencil\n");
			return false;
		}
		
		// set depth stencil state
		device.setTextureState(depth_stencil_texture, D3D12_RESOURCE_STATE_DEPTH_WRITE);
		
		// surface size
		surface.setSize(getWidth(), getHeight());
		
		return true;
	}
	
	void D3D12Window::release_buffers() {
		
		// finish device
		if(device) device.finish();
		
		// release heap
		if(render_target_heap) render_target_heap->Release();
		render_target_heap = nullptr;
		
		// release buffers
		for(uint32_t i = 0; i < NumFrames; i++) {
			if(render_targets[i]) render_targets[i]->Release();
			render_target_views[i].ptr = 0;
			render_targets[i] = nullptr;
		}
		
		// release depth stencil
		depth_stencil_texture.clearPtr();
	}
	
	/*
	 */
	bool D3D12Window::render() {
		
		// check device
		if(!device) return false;
		
		// resize buffers
		if(surface.getWidth() != getWidth() || surface.getHeight() != getHeight()) {
			if(swap_chain) {
				release_buffers();
				if(D3D12Context::error(swap_chain->ResizeBuffers(NumFrames, getWidth(), getHeight(), (DXGI_FORMAT)surface.getColorDXGIFormat(), swap_chain_flags))) {
					TS_LOG(Error, "D3D12Window::render(): can't resize swap chain\n");
					return false;
				}
			} else {
				if(!create_swap_chain()) {
					TS_LOG(Error, "D3D12Window::render(): can't create swap chain\n");
					return false;
				}
			}
			if(!create_buffers()) {
				TS_LOG(Error, "D3D12Window::render(): can't create buffers\n");
				return false;
			}
		}
		
		ID3D12GraphicsCommandList *command = surface.getCommand();
		
		uint32_t frame = swap_chain->GetCurrentBackBufferIndex();
		
		// render target barrier
		D3D12_RESOURCE_BARRIER barrier = {};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = render_targets[frame];
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
		command->ResourceBarrier(1, &barrier);
		
		// surface render target
		surface.setRenderTargetView(render_target_views[frame].ptr);
		surface.setDepthStencilView(depth_stencil_texture.getDepthStencilView());
		
		return true;
	}
	
	/*
	 */
	bool D3D12Window::present() {
		
		// check device
		if(!device) return false;
		
		ID3D12GraphicsCommandList *command = surface.getCommand();
		
		uint32_t frame = swap_chain->GetCurrentBackBufferIndex();
		
		// present barrier
		D3D12_RESOURCE_BARRIER barrier = {};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = render_targets[frame];
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
		command->ResourceBarrier(1, &barrier);
		
		// flush device
		device.flush();
		
		// present parameters
		uint32_t present_flags = 0;
		uint32_t present_interval = (hasFlag(FlagVerticalSync)) ? 1 : 0;
		if(present_interval == 0 && (swap_chain_flags & DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING)) {
			present_flags |= DXGI_PRESENT_ALLOW_TEARING;
		}
		
		// present swap chain
		HRESULT result = swap_chain->Present(present_interval, present_flags);
		if(result != DXGI_STATUS_OCCLUDED && D3D12Context::error(result)) {
			TS_LOGF(Error, "D3D12Window::present(): can't present swap chain 0x%08x\n", result);
			return false;
		}
		
		// flip device
		device.flip();
		
		return true;
	}
	
	/*
	 */
	bool D3D12Window::finish() {
		
		// check device
		if(!device) return false;
		
		// finish device
		return device.finish();
	}
};

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	App::setPlatform(PlatformD3D12);
	
	// create app
	App app(argc, argv);
	if(!app.create()) return 1;
	
	// create window
	D3D12Window window(app.getPlatform(), app.getDevice());
	window.setSize(app.getWidth(), app.getHeight());
	DECLARE_WINDOW_CALLBACKS
	
	String title = String::format("%s Tellusim::D3D12SwapChain", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskFragment);
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	if(!pipeline.create()) return 1;
	
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
			Command command = device.createCommand(target);
			
			// draw texture
			command.setPipeline(pipeline);
			command.setUniform(0, time);
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

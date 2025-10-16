// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <dxgi.h>
#include <d3d11.h>

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
	class D3D11Window : public Window {
			
		public:
			
			// constructor
			explicit D3D11Window(Platform platform, uint32_t index = Maxu32);
			virtual ~D3D11Window();
			
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
			
			Context context;
			D3D11Surface surface;
			Device device;
			
			IDXGISwapChain *swap_chain = nullptr;
			
			ID3D11Texture2D *render_target = nullptr;
			ID3D11RenderTargetView *render_target_view = nullptr;
			
			D3D11Texture depth_stencil_texture;
	};
	
	/*
	 */
	D3D11Window::D3D11Window(Platform platform, uint32_t index) : Window(PlatformUnknown), context(platform, index) {
		
		// create context
		D3D11Context d3d12_context = D3D11Context(context);
		if(!d3d12_context || !d3d12_context.create()) return;
		
		// create surface
		surface = D3D11Surface(d3d12_context);
		if(!surface) return;
		
		// set surface
		setSurface(surface);
	}
	
	/*
	 */
	D3D11Window::~D3D11Window() {
		release();
	}
	
	/*
	 */
	bool D3D11Window::create(const char *title, Flags flags) {
		setTitle(title);
		return create(flags);
	}
	
	bool D3D11Window::create(const String &title, Flags flags) {
		setTitle(title);
		return create(flags);
	}
	
	bool D3D11Window::create(Flags flags) {
		
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
	
	void D3D11Window::release() {
		
		// release buffers
		release_buffers();
		
		// release swap chain
		release_swap_chain();
	}
	
	/*
	 */
	bool D3D11Window::create_swap_chain() {
		
		TS_ASSERT(!swap_chain && "D3D11Window::create_swap_chain(): is already created");
		
		IDXGIFactory *factory = surface.getFactory();
		
		// create swap chain
		DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
		swap_chain_desc.BufferDesc.Width = getWidth();
		swap_chain_desc.BufferDesc.Height = getHeight();
		swap_chain_desc.BufferDesc.Format = (DXGI_FORMAT)surface.getColorDXGIFormat();
		swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swap_chain_desc.SampleDesc.Count = getMultisample();
		swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_desc.BufferCount = 1;
		swap_chain_desc.OutputWindow = (HWND)getHandle();
		swap_chain_desc.Windowed = TRUE;
		swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swap_chain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		if(D3D11Context::error(factory->CreateSwapChain(surface.getDevice(), &swap_chain_desc, &swap_chain))) {
			TS_LOG(Error, "D3D11Window::create_swap_chain(): can't create swap chain\n");
			return false;
		}
		
		// configure window
		if(D3D11Context::error(factory->MakeWindowAssociation((HWND)getHandle(), DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER))) {
			TS_LOG(Error, "D3D11Window::create_swap_chain(): can't set window association\n");
			return false;
		}
		
		return true;
	}
	
	void D3D11Window::release_swap_chain() {
		
		// release swap chain
		if(swap_chain) {
			swap_chain->SetFullscreenState(FALSE, nullptr);
			swap_chain->Release();
		}
		swap_chain = nullptr;
	}
	
	/*
	 */
	bool D3D11Window::create_buffers() {
		
		TS_ASSERT(!depth_stencil_texture && "D3D11Window::create_buffers(): is already created");
		
		// get render target
		if(D3D11Context::error(swap_chain->GetBuffer(0, IID_PPV_ARGS(&render_target)))) {
			TS_LOG(Error, "D3D11Window::create_buffers(): can't get render target\n");
			release_buffers();
			return false;
		}
		
		if(D3D11Context::error(surface.getDevice()->CreateRenderTargetView(render_target, nullptr, &render_target_view))) {
			TS_LOG(Error, "D3D11Window::create_buffers(): can't create render target view\n");
			release_buffers();
			return false;
		}
		
		// create depth stencil
		Texture::Flags texture_flags = Texture::FlagTarget;
		if(getMultisample() == 2) texture_flags |= Texture::FlagMultisample2;
		if(getMultisample() == 4) texture_flags |= Texture::FlagMultisample4;
		if(getMultisample() == 8) texture_flags |= Texture::FlagMultisample8;
		depth_stencil_texture = device.createTexture2D(surface.getDepthFormat(), getWidth(), getHeight(), texture_flags);
		if(!depth_stencil_texture) {
			TS_LOG(Error, "D3D11Window::create_buffers(): can't create depth stencil\n");
			return false;
		}
		
		// surface size
		surface.setSize(getWidth(), getHeight());
		surface.setMultisample(getMultisample());
		
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
	bool D3D11Window::render() {
		
		// check device
		if(!device) return false;
		
		// resize buffers
		if(surface.getWidth() != getWidth() || surface.getHeight() != getHeight()) {
			if(swap_chain) {
				release_buffers();
				if(D3D11Context::error(swap_chain->ResizeBuffers(1, getWidth(), getHeight(), (DXGI_FORMAT)surface.getColorDXGIFormat(), DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH))) {
					TS_LOG(Error, "D3D11Window::run(): can't resize swap chain\n");
					return false;
				}
			} else {
				if(!create_swap_chain()) {
					TS_LOG(Error, "D3D11Window::render(): can't create swap chain\n");
					return false;
				}
			}
			if(!create_buffers()) {
				TS_LOG(Error, "D3D11Window::run(): can't create buffers\n");
				return false;
			}
		}
		
		// surface render target
		surface.setRenderTargetView(render_target_view);
		surface.setDepthStencilView(depth_stencil_texture.getDepthStencilView());
		
		return true;
	}
	
	/*
	 */
	bool D3D11Window::present() {
		
		// check device
		if(!device) return false;
		
		// present swap chain
		HRESULT result = swap_chain->Present(hasFlag(FlagVerticalSync) ? 1 : 0, 0);
		if(result != DXGI_STATUS_OCCLUDED && D3D11Context::error(result)) {
			TS_LOGF(Error, "D3D11Window::present(): can't present swap chain 0x%08x\n", result);
			return false;
		}
		
		return true;
	}
	
	/*
	 */
	bool D3D11Window::finish() {
		
		// check device
		if(!device) return false;
		
		// finish device
		return device.finish();
	}
};

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	App::setPlatform(PlatformD3D11);
	
	// create app
	App app(argc, argv);
	if(!app.create()) return 1;
	
	// create window
	D3D11Window window(app.getPlatform(), app.getDevice());
	window.setSize(app.getWidth(), app.getHeight());
	DECLARE_WINDOW_CALLBACKS
	
	String title = String::format("%s Tellusim::D3D11SwapChain", window.getPlatformName());
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

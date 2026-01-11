// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include "QD3D11Widget.h"

#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <math/TellusimMath.h>
#include <platform/TellusimCommand.h>

/*
 */
#define EXTERNAL_DEVICE		1

/*
 */
namespace Tellusim {
	
	/*
	 */
	QD3D11Widget::QD3D11Widget(QWidget *parent) : ::QWidget(parent) {
		
		// configure widget
		setAttribute(Qt::WA_PaintOnScreen);
		setAttribute(Qt::WA_NoSystemBackground);
	}
	
	QD3D11Widget::~QD3D11Widget() {
		
		// release resources
		release_buffers();
		release_swap_chain();
		release_context();
	}
	
	/*
	 */
	QSize QD3D11Widget::sizeHint() const {
		return QSize(1600, 900);
	}
	
	/*
	 */
	bool QD3D11Widget::create_context() {
		
		TS_ASSERT(d3d11_device == nullptr);
		
		#if EXTERNAL_DEVICE
			
			// create factory
			if(CreateDXGIFactory(IID_PPV_ARGS(&dxgi_factory)) != S_OK) {
				TS_LOG(Error, "QD3D11Widget::create_context(): can't create factory\n");
				release_context();
				return false;
			}
			
			// enumerate adapters
			IDXGIAdapter *adapter = nullptr;
			if(dxgi_factory->EnumAdapters(0, &adapter) != S_OK || adapter == nullptr) {
				TS_LOG(Error, "QD3D11Widget::create_context(): can't enum adapters\n");
				release_context();
				return false;
			}
			
			// create device
			ID3D11DeviceContext *d3d11_context = nullptr;
			D3D_DRIVER_TYPE type = D3D_DRIVER_TYPE_UNKNOWN;
			D3D_FEATURE_LEVEL feature_level = D3D_FEATURE_LEVEL_11_1;
			if(D3D11CreateDevice(adapter, type, nullptr, 0, &feature_level, 1, D3D11_SDK_VERSION, &d3d11_device, nullptr, &d3d11_context) != S_OK) {
				TS_LOG(Error, "QD3D11Widget::create_context(): can't create device\n");
				adapter->Release();
				release_context();
				return false;
			}
			d3d11_context->Release();
			adapter->Release();
			
			// create external context
			if(!context.create(d3d11_device)) {
				TS_LOG(Error, "QD3D11Widget::create_context(): can't create context\n");
				return false;
			}
			
			// create external surface
			surface = D3D11Surface(context);
			if(!surface) {
				TS_LOG(Error, "QD3D11Widget::create_context(): can't create context\n");
				return false;
			}
		
		#else
			
			// create internal context
			if(!context.create()) {
				TS_LOG(Error, "QD3D11Widget::create_context(): can't create context\n");
				return false;
			}
			
			// create internal context
			surface = D3D11Surface(context);
			if(!surface) {
				TS_LOG(Error, "QD3D11Widget::create_context(): can't create context\n");
				return false;
			}
			
			// internal interfaces
			dxgi_factory = surface.getFactory();
			d3d11_device = surface.getDevice();
			
		#endif
		
		// configure window
		if(dxgi_factory->MakeWindowAssociation((HWND)winId(), DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER) != S_OK) {
			TS_LOG(Error, "QD3D11Widget::create_context(): can't set window association\n");
			release_context();
			return false;
		}
		
		return true;
	}
	
	void QD3D11Widget::release_context() {
		
		release_buffers();
		release_swap_chain();
	}
	
	/*
	 */
	bool QD3D11Widget::create_swap_chain() {
		
		TS_ASSERT(dxgi_swap_chain == nullptr);
		
		// create swap chain
		DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
		swap_chain_desc.BufferDesc.Width = widget_width;
		swap_chain_desc.BufferDesc.Height = widget_height;
		swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swap_chain_desc.SampleDesc.Count = Samples;
		swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_desc.BufferCount = 1;
		swap_chain_desc.OutputWindow = (HWND)winId();
		swap_chain_desc.Windowed = TRUE;
		swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swap_chain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		if(dxgi_factory->CreateSwapChain(d3d11_device, &swap_chain_desc, &dxgi_swap_chain) != S_OK) {
			TS_LOG(Error, "QD3D11Widget::create_swap_chain(): can't create swap chain\n");
			return false;
		}
		
		// surface size
		surface.setMultisample(Samples);
		surface.setSize(widget_width, widget_height);
		
		return true;
	}
	
	void QD3D11Widget::release_swap_chain() {
		
		// release swap chain
		if(dxgi_swap_chain) dxgi_swap_chain->Release();
		dxgi_swap_chain = nullptr;
	}
	
	/*
	 */
	bool QD3D11Widget::create_buffers() {
		
		TS_ASSERT(render_target == nullptr);
		
		// get render target
		if(dxgi_swap_chain->GetBuffer(0, IID_PPV_ARGS(&render_target)) != S_OK) {
			TS_LOG(Error, "QD3D11Widget::create_buffers(): can't get render target\n");
			release_buffers();
			return false;
		}
		
		if(d3d11_device->CreateRenderTargetView(render_target, nullptr, &render_target_view) != S_OK) {
			TS_LOG(Error, "QD3D11Widget::create_buffers(): can't create render target view\n");
			release_buffers();
			return false;
		}
		
		// create depth stencil
		D3D11_TEXTURE2D_DESC depth_stencil_desc = {};
		depth_stencil_desc.Width = widget_width;
		depth_stencil_desc.Height = widget_height;
		depth_stencil_desc.MipLevels = 1;
		depth_stencil_desc.ArraySize = 1;
		depth_stencil_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_stencil_desc.SampleDesc.Count = Samples;
		depth_stencil_desc.Usage = D3D11_USAGE_DEFAULT;
		depth_stencil_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		
		if(d3d11_device->CreateTexture2D(&depth_stencil_desc, nullptr, &depth_stencil) != S_OK) {
			TS_LOG(Error, "QD3D11Widget::create_buffers(): can't create depth stencil\n");
			release_buffers();
			return false;
		}
		
		if(d3d11_device->CreateDepthStencilView(depth_stencil, nullptr, &depth_stencil_view) != S_OK) {
			TS_LOG(Error, "QD3D11Widget::create_buffers(): can't create depth stencil view\n");
			release_buffers();
			return false;
		}
		
		// surface size
		surface.setSize(widget_width, widget_height);
		
		return true;
	}
	
	void QD3D11Widget::release_buffers() {
		
		// release buffers
		if(render_target_view) render_target_view->Release();
		if(depth_stencil_view) depth_stencil_view->Release();
		if(render_target) render_target->Release();
		if(depth_stencil) depth_stencil->Release();
		render_target = nullptr;
		depth_stencil = nullptr;
		render_target_view = nullptr;
		depth_stencil_view = nullptr;
	}
	
	/*
	 */
	void QD3D11Widget::paintEvent(QPaintEvent *event) {
		
		Q_UNUSED(event);
		
		// widget size
		uint32_t old_width = widget_width;
		uint32_t old_height = widget_height;
		widget_width = (uint32_t)width();
		widget_height = (uint32_t)height();
		
		// create device
		if(!failed && dxgi_swap_chain == nullptr) {
			if(!failed && !create_context()) failed = true;
			if(!failed && !create_swap_chain()) failed = true;
			if(!failed && !create_buffers()) failed = true;
			old_width = widget_width;
			old_height = widget_height;
		}
		
		// resize buffers
		if(!failed && (old_width != widget_width || old_height != widget_height)) {
			release_buffers();
			if(dxgi_swap_chain->ResizeBuffers(1, widget_width, widget_height, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH) != S_OK) {
				TS_LOG(Error, "QD3D11Widget::paintEvent(): can't resize swap chain\n");
				release_context();
				failed = true;
			}
			if(!failed && !create_buffers()) failed = true;
		}
		
		// initialize application
		if(!failed && !initialized) {
			initialized = create_d3d11();
			if(!initialized) {
				release_context();
				failed = true;
			}
		}
		
		// render application
		if(!failed && initialized) {
			render_d3d11();
		}
	}
	
	/*
	 */
	bool QD3D11Widget::create_d3d11() {
		
		// create device
		device = Device(surface);
		if(!device) return false;
		
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
		
		// start update timer
		timer.setSingleShot(false);
		connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
		timer.start(1000 / 60);
		
		return true;
	}
	
	/*
	 */
	void QD3D11Widget::render_d3d11() {
		
		// structures
		struct CommonParameters {
			Matrix4x4f projection;
			Matrix4x4f modelview;
			Matrix4x4f transform;
			Vector4f camera;
		};
		
		// surface render target
		surface.setRenderTargetView(render_target_view);
		surface.setDepthStencilView(depth_stencil_view);
		
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
		if(result != DXGI_STATUS_OCCLUDED && result != S_OK) {
			TS_LOGF(Error, "QD3D11Widget::render_d3d11(): can't present swap chain 0x%08x\n", result);
			failed = true;
		}
	}
}

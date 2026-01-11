// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include "QD3D12Widget.h"

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
	QD3D12Widget::QD3D12Widget(QWidget *parent) : ::QWidget(parent) {
		
		// configure widget
		setAttribute(Qt::WA_PaintOnScreen);
		setAttribute(Qt::WA_NoSystemBackground);
	}
	
	QD3D12Widget::~QD3D12Widget() {
		
		// release resources
		release_buffers();
		release_swap_chain();
		release_context();
	}
	
	/*
	 */
	QSize QD3D12Widget::sizeHint() const {
		return QSize(1600, 900);
	}
	
	/*
	 */
	bool QD3D12Widget::create_context() {
		
		TS_ASSERT(d3d12_device == nullptr);
		
		#if EXTERNAL_DEVICE
			
			// enable debug layer
			ID3D12Debug *debug = nullptr;
			if(D3D12GetDebugInterface(IID_PPV_ARGS(&debug)) == S_OK) {
				debug->EnableDebugLayer();
				debug->Release();
			}
			
			// create factory
			if(CreateDXGIFactory2(0, IID_PPV_ARGS(&dxgi_factory)) != S_OK) {
				TS_LOG(Error, "QD3D12Widget::create_context(): can't create factory\n");
				release_context();
				return false;
			}
			
			// enumerate adapters
			IDXGIAdapter3 *adapter = nullptr;
			IDXGIAdapter1 *adapter1 = nullptr;
			if(dxgi_factory->EnumAdapters1(0, &adapter1) != S_OK || adapter1 == nullptr) {
				TS_LOG(Error, "QD3D12Widget::create_context(): can't enum adapters\n");
				release_context();
				return false;
			}
			if(adapter1->QueryInterface(IID_PPV_ARGS(&adapter)) != S_OK) {
				TS_LOG(Error, "QD3D12Widget::create_context(): can't get adapter\n");
				adapter1->Release();
				release_context();
				return false;
			}
			adapter1->Release();
			
			// create device
			D3D_FEATURE_LEVEL feature_level = D3D_FEATURE_LEVEL_12_0;
			if(D3D12CreateDevice(adapter, feature_level, IID_PPV_ARGS(&d3d12_device)) != S_OK) {
				TS_LOG(Error, "QD3D12Widget::create_context(): can't create device\n");
				adapter->Release();
				release_context();
				return false;
			}
			adapter->Release();
			
			// create command queue
			D3D12_COMMAND_QUEUE_DESC queue_desc = {};
			queue_desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
			if(d3d12_device->CreateCommandQueue(&queue_desc, IID_PPV_ARGS(&d3d12_queue)) != S_OK) {
				TS_LOG(Error, "QD3D12Widget::create_context(): can't create command queue\n");
				release_context();
				return false;
			}
			
			// create external context
			if(!context.create(d3d12_device, d3d12_queue)) {
				TS_LOG(Error, "QD3D12Widget::create_context(): can't create context\n");
				return false;
			}
			
			// create external surface
			surface = D3D12Surface(context);
			if(!surface) {
				TS_LOG(Error, "QD3D12Widget::create_context(): can't create context\n");
				return false;
			}
			
		#else
			
			// create internal context
			if(!context.create()) {
				TS_LOG(Error, "QD3D12Widget::create_context(): can't create context\n");
				return false;
			}
			
			// create internal context
			surface = D3D12Surface(context);
			if(!surface) {
				TS_LOG(Error, "QD3D12Widget::create_context(): can't create context\n");
				return false;
			}
			
			// internal interfaces
			dxgi_factory = surface.getFactory();
			d3d12_device = surface.getDevice();
			d3d12_queue = surface.getQueue();
			
		#endif
		
		// configure window
		if(dxgi_factory->MakeWindowAssociation((HWND)winId(), DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER) != S_OK) {
			TS_LOG(Error, "QD3D12Widget::create_context(): can't set window association\n");
			release_context();
			return false;
		}
		
		return true;
	}
	
	void QD3D12Widget::release_context() {
		
		release_buffers();
		release_swap_chain();
	}
	
	/*
	 */
	bool QD3D12Widget::create_swap_chain() {
		
		TS_ASSERT(dxgi_swap_chain == nullptr);
		
		// create swap chain
		IDXGISwapChain *swap_chain = nullptr;
		DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
		swap_chain_desc.BufferDesc.Width = widget_width;
		swap_chain_desc.BufferDesc.Height = widget_height;
		swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swap_chain_desc.SampleDesc.Count = 1;
		swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_desc.BufferCount = NumFrames;
		swap_chain_desc.OutputWindow = (HWND)winId();
		swap_chain_desc.Windowed = TRUE;
		swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swap_chain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		if(dxgi_factory->CreateSwapChain(d3d12_queue, &swap_chain_desc, &swap_chain) != S_OK) {
			TS_LOG(Error, "QD3D12Widget::create_swap_chain(): can't create swap chain\n");
			return false;
		}
		
		// query swap chain interface
		if(swap_chain->QueryInterface(IID_PPV_ARGS(&dxgi_swap_chain)) != S_OK) {
			TS_LOG(Error, "QD3D12Widget::create_swap_chain(): can't get swap chain\n");
			swap_chain->Release();
			return false;
		}
		swap_chain->Release();
		
		return true;
	}
	
	void QD3D12Widget::release_swap_chain() {
		
		// release swap chain
		if(dxgi_swap_chain) dxgi_swap_chain->Release();
		dxgi_swap_chain = nullptr;
	}
	
	/*
	 */
	bool QD3D12Widget::create_buffers() {
		
		TS_ASSERT(render_target_views[0].ptr == 0);
		
		// get render targets
		for(uint32_t i = 0; i < NumFrames; i++) {
			if(dxgi_swap_chain->GetBuffer(i, IID_PPV_ARGS(&render_targets[i])) != S_OK) {
				TS_LOG(Error, "QD3D12Widget::create_buffers(): can't get render target\n");
				release_buffers();
				return false;
			}
		}
		
		// create render target heap
		D3D12_DESCRIPTOR_HEAP_DESC render_target_heap_desc = {};
		render_target_heap_desc.NumDescriptors = NumFrames;
		render_target_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		render_target_heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		if(d3d12_device->CreateDescriptorHeap(&render_target_heap_desc, IID_PPV_ARGS(&render_target_heap)) != S_OK) {
			TS_LOG(Error, "QD3D12Widget::create_buffers(): can't create descriptor heap\n");
			release_buffers();
			return false;
		}
		
		// create render target views
		D3D12_RENDER_TARGET_VIEW_DESC render_target_view_desc = {};
		render_target_view_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		render_target_view_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		
		size_t render_target_heap_ptr = render_target_heap->GetCPUDescriptorHandleForHeapStart().ptr;
		uint32_t render_target_heap_stride = d3d12_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		for(uint32_t i = 0; i < NumFrames; i++) {
			render_target_views[i].ptr = render_target_heap_ptr + render_target_heap_stride * i;
			d3d12_device->CreateRenderTargetView(render_targets[i], &render_target_view_desc, render_target_views[i]);
		}
		
		// create depth stencil
		D3D12_HEAP_PROPERTIES depth_stencil_prop = {};
		depth_stencil_prop.Type = D3D12_HEAP_TYPE_DEFAULT;
		depth_stencil_prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		depth_stencil_prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		
		D3D12_RESOURCE_DESC depth_stencil_desc = {};
		depth_stencil_desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		depth_stencil_desc.Width = widget_width;
		depth_stencil_desc.Height = widget_height;
		depth_stencil_desc.DepthOrArraySize = 1;
		depth_stencil_desc.MipLevels = 1;
		depth_stencil_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_stencil_desc.SampleDesc.Count = 1;
		depth_stencil_desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		depth_stencil_desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
		
		D3D12_CLEAR_VALUE depth_stencil_clear = {};
		depth_stencil_clear.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_stencil_clear.DepthStencil.Depth = 1.0f;
		depth_stencil_clear.DepthStencil.Stencil = 0;
		
		if(d3d12_device->CreateCommittedResource(&depth_stencil_prop, D3D12_HEAP_FLAG_NONE, &depth_stencil_desc, D3D12_RESOURCE_STATE_DEPTH_WRITE, &depth_stencil_clear, IID_PPV_ARGS(&depth_stencil))) {
			TS_LOG(Error, "QD3D12Widget::create_buffers(): can't create committed resource\n");
			release_buffers();
			return false;
		}
		
		// create depth stencil heap
		D3D12_DESCRIPTOR_HEAP_DESC depth_stencil_heap_desc = {};
		depth_stencil_heap_desc.NumDescriptors = 1;
		depth_stencil_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		depth_stencil_heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		if(d3d12_device->CreateDescriptorHeap(&depth_stencil_heap_desc, IID_PPV_ARGS(&depth_stencil_heap)) != S_OK) {
			TS_LOG(Error, "QD3D12Widget::create_buffers(): can't create descriptor heap\n");
			release_buffers();
			return false;
		}
		
		// create depth stencil view
		depth_stencil_view.ptr = depth_stencil_heap->GetCPUDescriptorHandleForHeapStart().ptr;
		d3d12_device->CreateDepthStencilView(depth_stencil, nullptr, depth_stencil_view);
		
		// surface size
		surface.setSize(widget_width, widget_height);
		
		return true;
	}
	
	void QD3D12Widget::release_buffers() {
		
		// finish device
		if(device) device.finish();
		
		// release heaps
		if(render_target_heap) render_target_heap->Release();
		if(depth_stencil_heap) depth_stencil_heap->Release();
		render_target_heap = nullptr;
		depth_stencil_heap = nullptr;
		
		// release buffers
		for(uint32_t i = 0; i < NumFrames; i++) {
			if(render_targets[i]) render_targets[i]->Release();
			render_target_views[i].ptr = 0;
			render_targets[i] = nullptr;
		}
		if(depth_stencil) depth_stencil->Release();
		depth_stencil_view.ptr = 0;
		depth_stencil = nullptr;
	}
	
	/*
	 */
	void QD3D12Widget::paintEvent(QPaintEvent *event) {
		
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
			if(dxgi_swap_chain->ResizeBuffers(NumFrames, widget_width, widget_height, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH) != S_OK) {
				TS_LOG(Error, "QD3D12Widget::paintEvent(): can't resize swap chain\n");
				release_context();
				failed = true;
			}
			if(!failed && !create_buffers()) failed = true;
		}
		
		// initialize application
		if(!failed && !initialized) {
			initialized = create_d3d12();
			if(!initialized) {
				release_context();
				failed = true;
			}
		}
		
		// render application
		if(!failed && initialized) {
			render_d3d12();
		}
	}
	
	/*
	 */
	bool QD3D12Widget::create_d3d12() {
		
		// create surface
		surface.setColorFormat(FormatRGBAu8n);
		surface.setDepthFormat(FormatDu24Su8);
		
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
	void QD3D12Widget::render_d3d12() {
		
		// structures
		struct CommonParameters {
			Matrix4x4f projection;
			Matrix4x4f modelview;
			Matrix4x4f transform;
			Vector4f camera;
		};
		
		// current back buffer
		uint32_t frame = dxgi_swap_chain->GetCurrentBackBufferIndex();
		
		// current command list
		ID3D12GraphicsCommandList *command = surface.getCommand();
		
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
		surface.setDepthStencilView(depth_stencil_view.ptr);
		
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
		
		// present barrier
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
		command->ResourceBarrier(1, &barrier);
		
		// flush device
		device.flush();
		
		// present swap chain
		HRESULT result = dxgi_swap_chain->Present(1, 0);
		if(result != DXGI_STATUS_OCCLUDED && result != S_OK) {
			TS_LOGF(Error, "QD3D12Widget::render_d3d12(): can't present swap chain 0x%08x\n", result);
			failed = true;
			return;
		}
		
		// flip device
		device.flip();
	}
}

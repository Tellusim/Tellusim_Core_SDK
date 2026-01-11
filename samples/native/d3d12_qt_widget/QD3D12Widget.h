// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_QT_D3D12_WIDGET_H__
#define __TELLUSIM_QT_D3D12_WIDGET_H__

#include <d3d12.h>
#include <dxgi1_4.h>

#include <QtCore/QTimer>
#include <QtWidgets/QWidget>

#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimContext.h>
#include <platform/TellusimSurface.h>

/*
 */
namespace Tellusim {
	
	/*
	 */
	class QD3D12Widget : public QWidget {
			
			Q_OBJECT
			
		public:
			
			QD3D12Widget(QWidget *parent = nullptr);
			~QD3D12Widget();
			
			virtual QSize sizeHint() const;
			
		protected:
			
			virtual QPaintEngine *paintEngine() const { return nullptr; }
			
			virtual void paintEvent(QPaintEvent *event);
			
		private:
			
			/// create context
			bool create_context();
			void release_context();
			
			/// create swap chain
			bool create_swap_chain();
			void release_swap_chain();
			
			/// create buffers
			bool create_buffers();
			void release_buffers();
			
			/// rendering loop
			bool create_d3d12();
			void render_d3d12();
			
			enum {
				NumFrames = 3,
			};
			
			bool failed = false;
			bool initialized = false;
			
			uint32_t widget_width = 0;
			uint32_t widget_height = 0;
			
			IDXGIFactory4 *dxgi_factory = nullptr;
			ID3D12Device *d3d12_device = nullptr;
			ID3D12CommandQueue *d3d12_queue = nullptr;
			IDXGISwapChain3 *dxgi_swap_chain = nullptr;
			
			ID3D12Resource *render_targets[NumFrames] = {};
			ID3D12DescriptorHeap *render_target_heap = nullptr;
			D3D12_CPU_DESCRIPTOR_HANDLE render_target_views[NumFrames] = {};
			
			ID3D12Resource *depth_stencil = nullptr;
			ID3D12DescriptorHeap *depth_stencil_heap = nullptr;
			D3D12_CPU_DESCRIPTOR_HANDLE depth_stencil_view = {};
			
			D3D12Context context;
			D3D12Surface surface;
			
			Device device;
			Pipeline pipeline;
			Buffer vertex_buffer;
			Buffer index_buffer;
			
			QTimer timer;
	};
}

#endif /* __TELLUSIM_QT_D3D12_WIDGET_H__ */

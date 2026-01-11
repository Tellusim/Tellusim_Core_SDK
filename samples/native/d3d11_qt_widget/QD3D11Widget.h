// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_QT_D3D11_WIDGET_H__
#define __TELLUSIM_QT_D3D11_WIDGET_H__

#include <d3d11.h>

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
	class QD3D11Widget : public QWidget {
			
			Q_OBJECT
			
		public:
			
			QD3D11Widget(QWidget *parent = nullptr);
			~QD3D11Widget();
			
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
			bool create_d3d11();
			void render_d3d11();
			
			enum {
				Samples = 4,
			};
			
			bool failed = false;
			bool initialized = false;
			
			uint32_t widget_width = 0;
			uint32_t widget_height = 0;
			
			IDXGIFactory *dxgi_factory = nullptr;
			ID3D11Device *d3d11_device = nullptr;
			IDXGISwapChain *dxgi_swap_chain = nullptr;
			
			ID3D11Texture2D *render_target = nullptr;
			ID3D11Texture2D *depth_stencil = nullptr;
			ID3D11RenderTargetView *render_target_view = nullptr;
			ID3D11DepthStencilView *depth_stencil_view = nullptr;
			
			D3D11Context context;
			D3D11Surface surface;
			
			Device device;
			Pipeline pipeline;
			Buffer vertex_buffer;
			Buffer index_buffer;
			
			QTimer timer;
	};
}

#endif /* __TELLUSIM_QT_D3D11_WIDGET_H__ */

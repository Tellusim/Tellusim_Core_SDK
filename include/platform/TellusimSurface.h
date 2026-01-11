// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_SURFACE_H__
#define __TELLUSIM_PLATFORM_SURFACE_H__

#include <TellusimFormat.h>
#include <platform/TellusimPlatform.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Context;
	class D3D12Context;
	class D3D11Context;
	class MTLContext;
	class VKContext;
	class GLContext;
	class GLESContext;
	
	/**
	 * The Surface class represents a rendering surface, encapsulating the properties and configurations related to a graphical context and its associated platform.
	 * It provides methods for querying and manipulating surface characteristics, such as the platform, size, multisampling options, layers, and formats.
	 * The class supports configuring the surface color and depth layers, as well as its associated formats, allowing for fine control over how rendering operations are performed on that surface.
	 * It also supports features like multisampling and layer management for advanced rendering scenarios.
	 */
	class TS_API Surface {
			
		protected:
			
			TS_DECLARE_PTR_0(Surface, 2)
			
		public:
			
			Surface();
			explicit Surface(Context &context);
			explicit Surface(Platform platform);
			
			/// context platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// surface device index
			uint32_t getIndex() const;
			
			/// surface size
			void setSize(uint32_t width, uint32_t height);
			uint32_t getWidth() const;
			uint32_t getHeight() const;
			
			/// surface multisample
			void setMultisample(uint32_t multisample);
			uint32_t getMultisample() const;
			bool hasMultisample() const;
			
			/// surface layers
			void setColorLayer(uint32_t layer, uint32_t layers);
			void setDepthLayer(uint32_t layer, uint32_t layers);
			uint32_t getColorLayer() const;
			uint32_t getDepthLayer() const;
			uint32_t getColorLayers() const;
			uint32_t getDepthLayers() const;
			bool hasColorLayers() const;
			bool hasDepthLayers() const;
			
			/// surface formats
			void setColorFormat(Format format);
			void setDepthFormat(Format format);
			Format getColorFormat() const;
			Format getDepthFormat() const;
	};
	
	/**
	 * The D3D12Surface class extends the Surface class to provide Direct3D12-specific functionality for managing a rendering surface.
	 * It includes methods for interacting with Direct3D12 devices, command queues, and command lists, enabling rendering operations in the context of Direct3D12.
	 * The class supports managing swap chains, render targets, and depth-stencil buffers, which are essential for rendering operations.
	 */
	class TS_API D3D12Surface : public Surface {
			
			TS_DECLARE_PTR_1(D3D12Surface, Surface, 0)
			
		public:
			
			D3D12Surface();
			explicit D3D12Surface(D3D12Context &context);
			
			/// current device
			IDXGIFactory4 *getFactory() const;
			ID3D12Device *getDevice() const;
			ID3D12CommandQueue *getQueue() const;
			ID3D12GraphicsCommandList *getCommand() const;
			
			/// swap chain
			void setSwapChain(IDXGISwapChain *swap_chain);
			IDXGISwapChain *getSwapChain() const;
			
			/// render targets
			void setRenderTarget(ID3D12Resource *render_target);
			void setDepthStencil(ID3D12Resource *depth_stencil);
			ID3D12Resource *getRenderTarget() const;
			ID3D12Resource *getDepthStencil() const;
			
			/// render target views
			void setRenderTargetView(size_t render_target_view);
			void setDepthStencilView(size_t depth_stencil_view);
			size_t getRenderTargetView() const;
			size_t getDepthStencilView() const;
			
			/// surface formats
			uint32_t getColorDXGIFormat() const;
			uint32_t getDepthDXGIFormat() const;
	};
	
	/**
	 * The D3D11Surface class extends the Surface class to provide Direct3D11-specific functionality for managing a rendering surface.
	 * It includes methods for interacting with Direct3D11 devices, device contexts, and swap chains, enabling rendering operations in the context of Direct3D11.
	 * The class supports managing render targets, depth-stencil buffers, and render target views, which are essential for rendering operations.
	 */
	class TS_API D3D11Surface : public Surface {
			
			TS_DECLARE_PTR_1(D3D11Surface, Surface, 0)
			
		public:
			
			D3D11Surface();
			explicit D3D11Surface(D3D11Context &context);
			
			/// current device
			IDXGIFactory *getFactory() const;
			ID3D11Device *getDevice() const;
			ID3D11DeviceContext *getContext() const;
			
			/// swap chain
			void setSwapChain(IDXGISwapChain *swap_chain);
			IDXGISwapChain *getSwapChain() const;
			
			/// render targets
			void setRenderTarget(ID3D11Texture2D *render_target);
			void setDepthStencil(ID3D11Texture2D *depth_stencil);
			ID3D11Texture2D *getRenderTarget() const;
			ID3D11Texture2D *getDepthStencil() const;
			
			/// render target views
			void setRenderTargetView(ID3D11RenderTargetView *render_target_view);
			void setDepthStencilView(ID3D11DepthStencilView *depth_stencil_view);
			ID3D11RenderTargetView *getRenderTargetView() const;
			ID3D11DepthStencilView *getDepthStencilView() const;
			
			/// surface formats
			uint32_t getColorDXGIFormat() const;
			uint32_t getDepthDXGIFormat() const;
	};
	
	/**
	 * The MTLSurface class extends the Surface class to provide Metal-specific functionality for managing a rendering surface.
	 * It includes methods for interacting with Metal devices, queues, and command buffers, enabling rendering operations in the context of Metal.
	 * The class supports managing render pass descriptors and surface formats, which are essential for rendering operations.
	 */
	class TS_API MTLSurface : public Surface {
			
			TS_DECLARE_PTR_1(MTLSurface, Surface, 0)
			
		public:
			
			MTLSurface();
			explicit MTLSurface(MTLContext &context);
			
			/// current device
			void *getDevice() const;
			void *getQueue() const;
			void *getCommand() const;
			
			/// render pass descriptor
			void setDescriptor(void *descriptor);
			void *getDescriptor() const;
			
			/// surface formats
			uint32_t getColorPixelFormat() const;
			uint32_t getDepthPixelFormat() const;
	};
	
	/**
	 * The VKSurface class extends the Surface class to provide Vulkan-specific functionality for managing a rendering surface.
	 * It includes methods for interacting with Vulkan instances, physical devices, logical devices, command buffers, and queues, enabling rendering operations in the context of Vulkan.
	 * The class supports managing swap chains, images, image views, render passes, and framebuffers, which are essential for rendering operations.
	 */
	class TS_API VKSurface : public Surface {
			
			TS_DECLARE_PTR_1(VKSurface, Surface, 0)
			
		public:
			
			VKSurface();
			explicit VKSurface(VKContext &context);
			
			/// current device
			VkInstance getInstance() const;
			VkPhysicalDevice getAdapter() const;
			VkDevice getDevice() const;
			VkQueue getQueue() const;
			VkCommandBuffer getCommand() const;
			uint32_t getFamily() const;
			
			/// swap chain
			void setSwapChain(VkSwapchainKHR swap_chain);
			VkSwapchainKHR getSwapChain() const;
			
			/// image handles
			void setColorImage(VkImage image);
			void setDepthImage(VkImage image);
			VkImage getColorImage() const;
			VkImage getDepthImage() const;
			
			/// image view handles
			void setColorImageView(VkImageView image_view);
			void setDepthImageView(VkImageView image_view);
			VkImageView getColorImageView() const;
			VkImageView getDepthImageView() const;
			
			/// framebuffer handle
			void setRenderPass(VkRenderPass render_pass);
			void setFramebuffer(VkFramebuffer framebuffer);
			VkRenderPass getRenderPass() const;
			VkFramebuffer getFramebuffer() const;
			
			/// surface formats
			uint32_t getColorPixelFormat() const;
			uint32_t getDepthPixelFormat() const;
	};
	
	/**
	 * The GLSurface class extends the Surface class to provide OpenGL-specific functionality for managing a rendering surface.
	 * It includes methods for interacting with OpenGL contexts and managing texture identifiers and framebuffers, enabling rendering operations in the context of OpenGL.
	 * The class supports managing color and depth textures, along with their respective internal formats, and facilitates handling of framebuffer objects essential for rendering.
	 */
	class TS_API GLSurface : public Surface {
			
			TS_DECLARE_PTR_1(GLSurface, Surface, 0)
			
		public:
			
			GLSurface();
			explicit GLSurface(GLContext &context);
			
			/// current context
			void *getContext() const;
			
			/// texture identifiers
			void setColorTextureID(uint32_t texture_id);
			void setDepthTextureID(uint32_t texture_id);
			uint32_t getColorTextureID() const;
			uint32_t getDepthTextureID() const;
			
			/// framebuffer identifier
			void setFramebufferID(uint32_t framebuffer_id);
			uint32_t getFramebufferID() const;
			
			/// surface formats
			uint32_t getColorInternalFormat() const;
			uint32_t getDepthInternalFormat() const;
	};
	
	/**
	 * The GLESSurface class extends the Surface class to provide OpenGLES-specific functionality for managing a rendering surface.
	 * It includes methods for interacting with OpenGLES contexts and managing texture identifiers and framebuffers, enabling rendering operations in the context of OpenGLES.
	 * The class supports managing color and depth textures, along with their respective internal formats, and facilitates handling of framebuffer objects essential for rendering.
	 */
	class TS_API GLESSurface : public Surface {
			
			TS_DECLARE_PTR_1(GLESSurface, Surface, 0)
			
		public:
			
			GLESSurface();
			explicit GLESSurface(GLESContext &context);
			
			/// current context
			void *getContext() const;
			
			/// texture identifiers
			void setColorTextureID(uint32_t texture_id);
			void setDepthTextureID(uint32_t texture_id);
			uint32_t getColorTextureID() const;
			uint32_t getDepthTextureID() const;
			
			/// framebuffer identifier
			void setFramebufferID(uint32_t framebuffer_id);
			uint32_t getFramebufferID() const;
			
			/// surface formats
			uint32_t getColorInternalFormat() const;
			uint32_t getDepthInternalFormat() const;
	};
}

#endif /* __TELLUSIM_PLATFORM_SURFACE_H__ */

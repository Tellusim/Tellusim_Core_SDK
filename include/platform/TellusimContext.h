// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_CONTEXT_H__
#define __TELLUSIM_PLATFORM_CONTEXT_H__

#include <platform/TellusimPlatform.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class String;
	
	/**
	 * The Context class initializes the target platform API in headless mode.
	 * It provides a simple way to create compute or off-screen rendering tasks.
	 * It can be constructed with a specific platform and an optional device index.
	 * For visualization, the separate Window class should be used.
	 */
	class TS_API Context {
			
			TS_DECLARE_PTR_0(Context, 2)
			
		public:
			
			/// context constructor
			Context();
			explicit Context(Platform platform, uint32_t index = Maxu32);
			
			/// context platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// context device index
			uint32_t getIndex() const;
			
			/// check context
			bool isCreated() const;
			
			/// create context
			bool create();
			
			/// flush context
			bool flush();
			bool finish();
	};
	
	/**
	 * The D3D12Context class is a Direct3D12-specific implementation of the Context class.
	 * It allows initialization of the rendering context using an externally provided ID3D12Device and command queue.
	 * The class also provides access to the underlying DXGI factory, device, command queue, and command list.
	 */
	class TS_API D3D12Context : public Context {
			
			TS_DECLARE_PTR_1(D3D12Context, Context, 0)
			
		public:
			
			D3D12Context();
			
			/// create context
			bool create(ID3D12Device *device, ID3D12CommandQueue *queue);
			
			/// current device
			IDXGIFactory4 *getFactory() const;
			ID3D12Device *getDevice() const;
			ID3D12CommandQueue *getQueue() const;
			ID3D12GraphicsCommandList *getCommand() const;
			
			/// Direct3D12 functions
			static void *getProcAddress(const char *name);
			
			/// check Direct3D12 errors
			static bool error(uint32_t result);
			
			using Context::create;
	};
	
	/**
	 * The D3D11Context class is a Direct3D11-specific implementation of the Context class.
	 * It allows initializing the rendering context using an externally provided ID3D11Device.
	 * The class also provides access to the DXGI factory, device, and device context.
	 */
	class TS_API D3D11Context : public Context {
			
			TS_DECLARE_PTR_1(D3D11Context, Context, 0)
			
		public:
			
			D3D11Context();
			
			/// create context
			bool create(ID3D11Device *device);
			
			/// current device
			IDXGIFactory *getFactory() const;
			ID3D11Device *getDevice() const;
			ID3D11DeviceContext *getD3D11Context() const;
			
			/// Direct3D11 functions
			static void *getProcAddress(const char *name);
			
			/// check Direct3D11 errors
			static bool error(uint32_t result);
			
			using Context::create;
	};
	
	/**
	 * The MTLContext class is a Metal-specific implementation of the Context class.
	 * It allows initializing the rendering context using externally provided Metal device and command queue pointers.
	 * The class provides access to the underlying device, command queue, command buffer, and Metal command encoders.
	 */
	class TS_API MTLContext : public Context {
			
			TS_DECLARE_PTR_1(MTLContext, Context, 0)
			
		public:
			
			MTLContext();
			
			/// create context
			bool create(void *device, void *queue);
			
			/// current device
			void *getDevice() const;
			void *getQueue() const;
			void *getCommand() const;
			
			/// command encoder
			void *getEncoder() const;
			void *getRenderEncoder(void *descriptor) const;
			void *getComputeEncoder() const;
			void *getTracingEncoder() const;
			void *getBlitEncoder() const;
			void endEncoder() const;
			
			using Context::create;
	};
	
	/**
	 * The VKContext class is a Vulkan-specific implementation of the Context class.
	 * It initializes the rendering context using externally provided Vulkan instance, device, and queue parameters.
	 * The class provides access to the Vulkan instance, physical device, logical device, command queue, and command buffer.
	 */
	class TS_API VKContext : public Context {
			
			TS_DECLARE_PTR_1(VKContext, Context, 0)
			
		public:
			
			VKContext();
			
			/// create context
			bool create(VkInstance instance, PFN_vkGetInstanceProcAddr func, VkPhysicalDevice adapter, VkDevice device, uint32_t family, uint32_t index);
			
			/// current device
			VkInstance getInstance() const;
			VkPhysicalDevice getAdapter() const;
			VkDevice getDevice() const;
			
			/// current context
			VkQueue getQueue() const;
			VkCommandBuffer getCommand() const;
			uint32_t getFamily() const;
			
			/// device queues
			uint32_t getNumQueues();
			uint32_t getQueueFlags(uint32_t index);
			uint32_t getQueueFamily(uint32_t index);
			
			/// additional extensions
			static void addContextExtension(const char *name);
			static void addAdapterExtension(const char *name);
			static void addAdapterFeatures(void *features);
			
			/// context info
			static String getLayers();
			static String getExtensions();
			
			/// check context info
			static bool checkLayer(const char *name);
			static bool checkExtension(const char *name);
			
			/// get proc address functions
			static PFN_vkGetInstanceProcAddr getInstanceProcAddress();
			static PFN_vkGetDeviceProcAddr getDeviceProcAddress();
			
			/// Vulkan functions
			static void *getProcAddress(const char *name);
			
			/// check Vulkan errors
			static bool error(uint32_t result);
			
			using Context::create;
	};
	
	/**
	 * The GLContext class is an OpenGL-specific implementation of the Context class.
	 * It initializes the rendering context using an externally provided OpenGL context.
	 * The class provides access to OpenGL context-related resources, including the display, visual, configuration, surface, and the context.
	 */
	class TS_API GLContext : public Context {
			
			TS_DECLARE_PTR_1(GLContext, Context, 0)
			
		public:
			
			GLContext();
			
			/// create context
			bool create(void *context);
			
			/// current context
			void *getGLDisplay() const;
			void *getGLVisual() const;
			void *getGLConfig() const;
			void *getGLSurface() const;
			void *getGLContext() const;
			
			/// context info
			static String getExtensions();
			
			/// check context info
			static bool checkExtension(const char *name);
			
			/// OpenGL functions
			static void *getProcAddress(const char *name);
			
			/// check OpenGL errors
			static bool error(uint32_t result);
			static bool check();
			
			using Context::create;
	};
	
	/**
	 * The GLESContext class is an OpenGLES-specific implementation of the Context class.
	 * It initializes the rendering context using an externally provided OpenGLES context.
	 * The class provides access to OpenGLES context-related resources, including the display, configuration, and the context.
	 */
	class TS_API GLESContext : public Context {
			
			TS_DECLARE_PTR_1(GLESContext, Context, 0)
			
		public:
			
			GLESContext();
			
			/// create context
			bool create(void *context);
			
			/// current context
			void *getGLESDisplay() const;
			void *getGLESConfig() const;
			void *getGLESContext() const;
			
			/// context info
			static String getExtensions();
			
			/// check context info
			static bool checkExtension(const char *name);
			
			/// OpenGLES functions
			static void *getProcAddress(const char *name);
			
			/// check OpenGLES errors
			static bool error(uint32_t result);
			static bool check();
			
			using Context::create;
	};
	
	/**
	 * The WGContext class is a WebGPU-specific implementation of the Context class.
	 * It facilitates the creation of a rendering context using an externally provided WebGPU instance, adapter, and device.
	 * The class provides access to the underlying WebGPU instance, adapter, and device.
	 */
	class TS_API WGContext : public Context {
			
			TS_DECLARE_PTR_1(WGContext, Context, 0)
			
		public:
			
			WGContext();
			
			/// open context
			static bool open(WGPUInstance instance, WGPUAdapter adapter, WGPUDevice device);
			
			/// create context
			bool create(WGPUInstance instance, WGPUAdapter adapter, WGPUDevice device);
			
			/// current context
			WGPUInstance getInstance() const;
			WGPUAdapter getAdapter() const;
			WGPUDevice getDevice() const;
			
			using Context::create;
	};
	
	/**
	 * The CUContext class is a CUDA-specific implementation of the Context class.
	 * It provides functionality to manage and interact with a CUDA context, stream, and device.
	 * The class allows retrieving the current CUDA device, context, and stream.
	 */
	class TS_API CUContext : public Context {
			
			TS_DECLARE_PTR_1(CUContext, Context, 0)
			
		public:
			
			CUContext();
			
			/// current device
			int32_t getDevice() const;
			CUcontext getCUContext() const;
			CUstream getStream() const;
			
			/// Cuda functions
			static void *getProcAddress(const char *name);
			
			/// check Cuda errors
			static bool error(uint32_t result);
	};
	
	/**
	 * The HIPContext class is a HIP-specific implementation of the Context class.
	 * It provides functionality to manage and interact with a HIP context, stream, and device.
	 * The class allows retrieving the current CUDA device, context, and stream.
	 */
	class TS_API HIPContext : public Context {
			
			TS_DECLARE_PTR_1(HIPContext, Context, 0)
			
		public:
			
			HIPContext();
			
			/// current device
			int32_t getDevice() const;
			void *getHIPContext() const;
			void *getStream() const;
			
			/// Hip functions
			static void *getProcAddress(const char *name);
			
			/// check Hip errors
			static bool error(uint32_t result);
	};
}

#endif /* __TELLUSIM_PLATFORM_CONTEXT_H__ */

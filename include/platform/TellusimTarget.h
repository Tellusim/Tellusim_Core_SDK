// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_TARGET_H__
#define __TELLUSIM_PLATFORM_TARGET_H__

#include <TellusimTypes.h>
#include <TellusimFormat.h>
#include <core/TellusimArray.h>
#include <platform/TellusimPlatform.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	struct Color;
	class Fence;
	class Surface;
	class Texture;
	
	/**
	 * The Target class provides functionality for managing rendering targets, including color and depth buffers, in a graphics pipeline.
	 * It supports operations such as loading, clearing, discarding, storing, and resolving targets, allowing for flexible rendering workflows.
	 * The class enables managing target properties such as format, dimension, multisampling, as well as configuring clear colors, textures, and slices for color and depth targets, making it suitable for complex rendering tasks.
	 */
	class TS_API Target {
			
			TS_DECLARE_PTR_0(Target, 0)
			
		public:
			
			/// Target operations
			enum Operation {
				
				BeginLoad		= (1 << 0),		// load targets
				BeginClear		= (1 << 1),		// clear targets
				BeginDiscard	= (1 << 2),		// discard targets
				BeginMask		= (BeginLoad | BeginClear | BeginDiscard),
				
				EndStore		= (1 << 3),		// store targets
				EndResolve		= (1 << 4),		// resolve targets
				EndDiscard		= (1 << 5),		// discard targets
				EndMask			= (EndStore | EndResolve | EndDiscard),
				
				OpNone			= 0,
				OpLoad			= BeginLoad,
				OpLoadStore		= (BeginLoad | EndStore),
				OpClearStore	= (BeginClear | EndStore),
				OpClearDiscard	= (BeginClear | EndDiscard),
				OpDefault		= OpClearStore,
			};
			
			Target();
			
			/// target platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// target device index
			uint32_t getIndex() const;
			
			/// begin target
			bool begin(Fence &fence);
			bool begin();
			
			/// end target
			void end(Fence &fence);
			void end();
			
			/// swap target
			void swap(Surface &surface);
			
			/// check target
			bool isEnabled() const;
			
			/// target format
			Format getColorFormat(uint32_t index = 0) const;
			Format getDepthFormat() const;
			uint32_t getMultisample() const;
			bool hasMultisample() const;
			bool isFlipped() const;
			bool isAtomic() const;
			
			/// target dimension
			uint32_t getWidth() const;
			uint32_t getHeight() const;
			uint32_t getDepth() const;
			uint32_t getFaces() const;
			uint32_t getLayers() const;
			uint32_t getMipmaps() const;
			
			/// color target
			void setClearColor(const Color &color);
			void setClearColor(uint32_t index, const Color &color);
			void setClearColor(float32_t r, float32_t g, float32_t b, float32_t a);
			void setClearColor(uint32_t index, float32_t r, float32_t g, float32_t b, float32_t a);
			void setColorTexture(Texture &texture, Operation op = OpDefault, const Slice &slice = Slice());
			void setColorTexture(uint32_t index, Texture &texture, Operation op = OpDefault, const Slice &slice = Slice());
			void setColorResolve(Texture &texture, const Slice &slice = Slice());
			void setColorResolve(uint32_t index, Texture &texture, const Slice &slice = Slice());
			
			uint32_t getNumTargets() const;
			const Color &getClearColor(uint32_t index = 0) const;
			Operation getColorOp(uint32_t index = 0) const;
			Texture getColorTexture(uint32_t index) const;
			Texture getColorResolve(uint32_t index) const;
			const Slice &getColorTextureSlice(uint32_t index) const;
			const Slice &getColorResolveSlice(uint32_t index) const;
			
			/// depth target
			void setClearDepth(float32_t depth, uint32_t stencil = 0);
			void setDepthTexture(Texture &texture, Operation op = OpDefault, const Slice &slice = Slice());
			void setDepthResolve(Texture &texture, const Slice &slice = Slice());
			
			float32_t getClearDepth() const;
			uint32_t getClearStencil() const;
			Operation getDepthOp() const;
			Texture getDepthTexture() const;
			Texture getDepthResolve() const;
			const Slice &getDepthTextureSlice() const;
			const Slice &getDepthResolveSlice() const;
	};
	
	/**
	 * The D3D12Target class is a Direct3D12-specific implementation of the Target class, providing methods for interacting with render and depth-stencil targets in a Direct3D12 context.
	 * It allows access to an array of render target views and a single depth-stencil view, which are essential for rendering operations in Direct3D12.
	 */
	class TS_API D3D12Target : public Target {
			
			TS_DECLARE_PTR_1(D3D12Target, Target, 0)
			
		public:
			
			D3D12Target();
			
			size_t *getRenderTargetViews() const;
			size_t getDepthStencilView() const;
	};
	
	/**
	 * The D3D11Target class is a Direct3D11-specific implementation of the Target class, providing methods for interacting with render and depth-stencil targets in a Direct3D11 context.
	 * It allows access to an array of render target views and a single depth-stencil view, which are essential for rendering operations in Direct3D11.
	 */
	class TS_API D3D11Target : public Target {
			
			TS_DECLARE_PTR_1(D3D11Target, Target, 0)
			
		public:
			
			D3D11Target();
			
			ID3D11RenderTargetView **getRenderTargetViews() const;
			ID3D11DepthStencilView *getDepthStencilView() const;
	};
	
	/**
	 * The MTLTarget class is a Metal-specific implementation of the Target class, providing functionality for interacting with Metal render and depth-stencil targets.
	 * It offers access to a descriptor object, which encapsulates the configuration of a Metal rendering target.
	 */
	class TS_API MTLTarget : public Target {
			
			TS_DECLARE_PTR_1(MTLTarget, Target, 0)
			
		public:
			
			MTLTarget();
			
			void *getDescriptor() const;
	};
	
	/**
	 * The VKTarget class is a Vulkan-specific implementation of the Target class, offering functionality for managing Vulkan render passes and framebuffers.
	 * It provides methods to retrieve the associated Vulkan render pass and framebuffer objects, which are essential for the rendering process in Vulkan.
	 */
	class TS_API VKTarget : public Target {
			
			TS_DECLARE_PTR_1(VKTarget, Target, 0)
			
		public:
			
			VKTarget();
			
			VkRenderPass getRenderPass() const;
			VkFramebuffer getFramebuffer() const;
	};
	
	/**
	 * The GLTarget class is an OpenGL-specific implementation of the Target class, designed to manage OpenGL framebuffers.
	 * It provides access to the framebuffer ID, allowing for efficient handling of rendering operations within OpenGL.
	 */
	class TS_API GLTarget : public Target {
			
			TS_DECLARE_PTR_1(GLTarget, Target, 0)
			
		public:
			
			GLTarget();
			
			uint32_t getFramebufferID() const;
	};
	
	/**
	 * The GLESTarget class is an OpenGLES-specific implementation of the Target class, designed to manage OpenGLES framebuffers.
	 * It provides access to the framebuffer ID, allowing for efficient handling of rendering operations within OpenGLES.
	 */
	class TS_API GLESTarget : public Target {
			
			TS_DECLARE_PTR_1(GLESTarget, Target, 0)
			
		public:
			
			GLESTarget();
			
			uint32_t getFramebufferID() const;
	};
	
	/**
	 * The FUTarget class extends the Target class to support managing multiple targets across various devices.
	 * It provides functionality for handling a fusion of targets from different devices, which is useful for multi-device workflows.
	 */
	class TS_API FUTarget : public Target {
			
			TS_DECLARE_PTR_1(FUTarget, Target, 0)
			
		public:
			
			FUTarget();
			explicit FUTarget(const Array<Target> &targets, bool owner = false);
			
			/// device mask
			void setMask(uint32_t mask);
			uint32_t getMask() const;
			
			/// Fusion targets
			uint32_t getNumTargets() const;
			const Target getTarget(uint32_t index) const;
			Target getTarget(uint32_t index);
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(Target::Operation)
}

#endif /* __TELLUSIM_PLATFORM_TARGET_H__ */

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_TEXTURE_H__
#define __TELLUSIM_PLATFORM_TEXTURE_H__

#include <TellusimTypes.h>
#include <TellusimFormat.h>
#include <core/TellusimArray.h>
#include <platform/TellusimPlatform.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class String;
	
	/**
	 * The Texture class represents a GPU texture resource supporting 2D, 3D, and Cube types with configurable format, dimensions, layers, mipmaps, and multisampling.
	 * It includes flags for usage patterns such as read/write access, target rendering, sharing, and interop with external or sparse resources.
	 * The class provides functions to query texture properties, format characteristics, and memory usage for efficient texture management across rendering platforms.
	 */
	class TS_API Texture {
			
			TS_DECLARE_PTR_0(Texture, 0)
			
		public:
			
			/// Texture types
			enum Type {
				TypeUnknown = 0,
				Type2D,
				Type3D,
				TypeCube,
				NumTypes,
			};
			
			/// Texture flags
			enum Flags {
				FlagNone = 0,
				FlagRead				= (1 << 0),		// read texture
				FlagWrite				= (1 << 1),		// write texture
				FlagTarget				= (1 << 2),		// target texture
				FlagBuffer				= (1 << 3),		// buffer texture
				FlagSource				= (1 << 4),		// source texture
				FlagSparse				= (1 << 5),		// sparse texture
				FlagShared				= (1 << 6),		// shared texture
				FlagExtern				= (1 << 7),		// extern texture
				FlagInterop				= (1 << 8),		// interop texture
				FlagSurface				= (1 << 9),		// surface texture
				FlagMutable				= (1 << 10),	// mutable texture
				FlagMipmaps				= (1 << 11),	// mipmaps texture
				FlagGenerate			= (1 << 12),	// generate mipmaps
				FlagFormatNorm			= (1 << 13),	// convert to norm format
				FlagFormatSRGB			= (1 << 14),	// convert to sRGB format
				FlagFormatSigned		= (1 << 15),	// convert to signed format
				FlagMultisample2		= (1 << 16),	// 2x multisample texture
				FlagMultisample4		= (1 << 17),	// 4x multisample texture
				FlagMultisample8		= (1 << 18),	// 8x multisample texture
				FlagClearOne			= (1 << 19),	// clear value is one
				FlagClearZero			= (1 << 20),	// clear value is zero
				FlagClearNormal			= (1 << 21),	// clear value is normal
				FlagMultisample			= (FlagMultisample2 | FlagMultisample4 | FlagMultisample8),
				DefaultFlags			= FlagNone,
				NumFlags = 22,
			};
			
			Texture();
			
			/// texture platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// texture device index
			uint32_t getIndex() const;
			
			/// clear texture
			void clear();
			
			/// check texture
			bool isCreated() const;
			
			/// texture name
			void setName(const char *name);
			String getName() const;
			
			/// create texture
			bool create(Type type, Format format, const Size &size, uint32_t layers, Flags flags = DefaultFlags);
			
			bool create2D(Format format, uint32_t size, Flags flags = DefaultFlags);
			bool create3D(Format format, uint32_t size, Flags flags = DefaultFlags);
			bool createCube(Format format, uint32_t size, Flags flags = DefaultFlags);
			
			bool create2D(Format format, uint32_t width, uint32_t height, Flags flags = DefaultFlags);
			bool create3D(Format format, uint32_t width, uint32_t height, uint32_t depth, Flags flags = DefaultFlags);
			
			bool create2D(Format format, uint32_t width, uint32_t height, uint32_t layers, Flags flags = DefaultFlags);
			bool createCube(Format format, uint32_t size, uint32_t layers, Flags flags = DefaultFlags);
			
			/// texture type
			Type getType() const;
			
			static const char *getTypeName(Type type);
			const char *getTypeName() const;
			
			TS_INLINE bool is2DType() const { return (getType() == Type2D); }
			TS_INLINE bool is3DType() const { return (getType() == Type3D); }
			TS_INLINE bool isCubeType() const { return (getType() == TypeCube); }
			
			/// texture format
			Format getFormat() const;
			
			TS_INLINE const char *getFormatName() const { return Tellusim::getFormatName(getFormat()); }
			
			TS_INLINE bool isColorFormat() const { return Tellusim::isColorFormat(getFormat()); }
			TS_INLINE bool isDepthFormat() const { return Tellusim::isDepthFormat(getFormat()); }
			TS_INLINE bool isPixelFormat() const { return Tellusim::isPixelFormat(getFormat()); }
			TS_INLINE bool isPlainFormat() const { return Tellusim::isPlainFormat(getFormat()); }
			TS_INLINE bool isMixedFormat() const { return Tellusim::isMixedFormat(getFormat()); }
			TS_INLINE bool isBlockFormat() const { return Tellusim::isBlockFormat(getFormat()); }
			TS_INLINE bool isStencilFormat() const { return Tellusim::isStencilFormat(getFormat()); }
			
			TS_INLINE bool isNormFormat() const { return Tellusim::isNormFormat(getFormat()); }
			TS_INLINE bool isSRGBFormat() const { return Tellusim::isSRGBFormat(getFormat()); }
			TS_INLINE bool isFloatFormat() const { return Tellusim::isFloatFormat(getFormat()); }
			TS_INLINE bool isSignedFormat() const { return Tellusim::isSignedFormat(getFormat()); }
			TS_INLINE bool isUnsignedFormat() const { return Tellusim::isUnsignedFormat(getFormat()); }
			TS_INLINE bool isIntegerFormat() const { return Tellusim::isIntegerFormat(getFormat()); }
			
			TS_INLINE bool isi8Format() const { return Tellusim::isi8Format(getFormat()); }
			TS_INLINE bool isu8Format() const { return Tellusim::isu8Format(getFormat()); }
			TS_INLINE bool is8BitFormat() const { return Tellusim::is8BitFormat(getFormat()); }
			
			TS_INLINE bool isi16Format() const { return Tellusim::isi16Format(getFormat()); }
			TS_INLINE bool isu16Format() const { return Tellusim::isu16Format(getFormat()); }
			TS_INLINE bool isf16Format() const { return Tellusim::isf16Format(getFormat()); }
			TS_INLINE bool is16BitFormat() const { return Tellusim::is16BitFormat(getFormat()); }
			
			TS_INLINE bool isi32Format() const { return Tellusim::isi32Format(getFormat()); }
			TS_INLINE bool isu32Format() const { return Tellusim::isu32Format(getFormat()); }
			TS_INLINE bool isf32Format() const { return Tellusim::isf32Format(getFormat()); }
			TS_INLINE bool is32BitFormat() const { return Tellusim::is32BitFormat(getFormat()); }
			
			TS_INLINE bool isi64Format() const { return Tellusim::isi64Format(getFormat()); }
			TS_INLINE bool isu64Format() const { return Tellusim::isu64Format(getFormat()); }
			TS_INLINE bool isf64Format() const { return Tellusim::isf64Format(getFormat()); }
			TS_INLINE bool is64BitFormat() const { return Tellusim::is64BitFormat(getFormat()); }
			
			TS_INLINE bool isBC15Format() const { return Tellusim::isBC15Format(getFormat()); }
			TS_INLINE bool isBC67Format() const { return Tellusim::isBC67Format(getFormat()); }
			TS_INLINE bool isETC2Format() const { return Tellusim::isETC2Format(getFormat()); }
			TS_INLINE bool isASTCFormat() const { return Tellusim::isASTCFormat(getFormat()); }
			
			TS_INLINE uint32_t getComponents() const { return getFormatComponents(getFormat()); }
			TS_INLINE uint32_t getPixelSize() const { return getFormatPixelSize(getFormat()); }
			TS_INLINE uint32_t getBlockSize() const { return getFormatBlockSize(getFormat()); }
			TS_INLINE uint32_t getBlockWidth() const { return getFormatBlockWidth(getFormat()); }
			TS_INLINE uint32_t getBlockHeight() const { return getFormatBlockHeight(getFormat()); }
			
			/// texture flags
			Flags getFlags() const;
			
			TS_INLINE bool hasFlag(Flags flags) const { return ((getFlags() & flags) != FlagNone); }
			TS_INLINE bool hasFlags(Flags flags) const { return ((getFlags() & flags) == flags); }
			
			String getFlagsName() const;
			
			/// texture multisample
			uint32_t getMultisample() const;
			bool hasMultisample() const;
			
			/// texture dimension
			uint32_t getWidth() const;
			uint32_t getHeight() const;
			uint32_t getDepth() const;
			uint32_t getFaces() const;
			uint32_t getLayers() const;
			uint32_t getMipmaps() const;
			uint32_t findMipmap(const Size &size) const;
			uint32_t getWidth(uint32_t mipmap) const;
			uint32_t getHeight(uint32_t mipmap) const;
			uint32_t getDepth(uint32_t mipmap) const;
			
			TS_INLINE bool hasFaces() const { return (getFaces() > 1); }
			TS_INLINE bool hasLayers() const { return (getLayers() > 1); }
			TS_INLINE bool hasMipmaps() const { return (getMipmaps() > 1); }
			
			Size getSize() const;
			Region getRegion() const;
			Slice getSlice() const;
			Size getSize(uint32_t mipmap) const;
			Region getRegion(uint32_t mipmap) const;
			Slice getSlice(uint32_t mipmap) const;
			
			/// sparse texture dimension
			uint32_t getTileWidth() const;
			uint32_t getTileHeight() const;
			uint32_t getTileDepth() const;
			uint32_t getTileMipmaps() const;
			
			Size getTileSize() const;
			
			/// texture description
			String getDescription() const;
			
			/// memory usage
			size_t getMemory() const;
	};
	
	/**
	 * The TextureTable class provides a container for managing multiple texture objects with support for bindless resource access.
	 * It enables efficient rendering workflows by organizing textures of a specific type, reducing the overhead of traditional binding operations.
	 * This class supports querying platform details, memory usage, and ownership of individual texture entries.
	 */
	class TS_API TextureTable {
			
			TS_DECLARE_PTR_0(TextureTable, 0)
			
		public:
			
			TextureTable();
			
			/// table platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// table device index
			uint32_t getIndex() const;
			
			/// clear table
			void clear();
			
			/// check table
			bool isCreated() const;
			
			/// table name
			void setName(const char *name);
			String getName() const;
			
			/// create table
			bool create(Texture::Type type, uint32_t size);
			
			/// table type
			Texture::Type getType() const;
			
			const char *getTypeName() const;
			
			/// table textures
			uint32_t getSize() const;
			Texture get(uint32_t index) const;
			bool isOwner(uint32_t index) const;
			
			/// memory usage
			size_t getMemory() const;
	};
	
	/**
	 * The D3D12Texture class is a Direct3D12-specific implementation of the Texture class, providing access to internal resources and views.
	 * It supports creation from external ID3D12Resource objects and exposes methods to retrieve shader, render target, depth stencil, and unordered access views.
	 * This class also manages resource state transitions and provides access to shared and interop handles for advanced usage scenarios.
	 */
	class TS_API D3D12Texture : public Texture {
			
			TS_DECLARE_PTR_1(D3D12Texture, Texture, 0)
			
		public:
			
			D3D12Texture();
			
			/// create external texture
			bool create(Type type, ID3D12Resource *texture, uint32_t state, Flags flags = DefaultFlags, Format format = FormatUnknown);
			
			/// native texture
			uint32_t getDXGIFormat() const;
			ID3D12Resource *getD3D12Texture() const;
			size_t getShaderResourceView() const;
			size_t getRenderTargetView() const;
			size_t getDepthStencilView() const;
			size_t getUnorderedAccessView() const;
			
			void setTextureState(uint32_t state);
			uint32_t getTextureState() const;
			
			void *getSharedHandle() const;
			void *getInteropHandle() const;
			
			using Texture::create;
	};
	
	/**
	 * The D3D11Texture class is a Direct3D11-specific implementation of the Texture class, providing access to internal resources and views.
	 * It supports the creation of external textures from ID3D11Texture2D objects and provides methods for accessing various views, such as shader resource, render target, depth stencil, and unordered access views.
	 * Additionally, the class includes interop handle support for integrating with other APIs or systems.
	 */
	class TS_API D3D11Texture : public Texture {
			
			TS_DECLARE_PTR_1(D3D11Texture, Texture, 0)
			
		public:
			
			D3D11Texture();
			
			/// create external texture
			bool create(Type type, ID3D11Texture2D *texture, Flags flags = DefaultFlags, Format format = FormatUnknown);
			
			/// native texture
			uint32_t getDXGIFormat() const;
			ID3D11Texture2D *getD3D11Texture() const;
			ID3D11ShaderResourceView *getShaderResourceView() const;
			ID3D11RenderTargetView *getRenderTargetView() const;
			ID3D11DepthStencilView *getDepthStencilView() const;
			ID3D11UnorderedAccessView *getUnorderedAccessView() const;
			
			void *getInteropHandle() const;
			
			using Texture::create;
	};
	
	/**
	 * The MTLTexture class is a Metal-specific implementation of the Texture class, offering access to Metal resources and enabling texture management in Metal applications.
	 * It supports external texture creation through raw pointer data and provides methods to retrieve the Metal texture, buffer, and shared pointer for interoperability.
	 * The class inherits the create method from the Texture class, facilitating flexible texture creation and management.
	 */
	class TS_API MTLTexture : public Texture {
			
			TS_DECLARE_PTR_1(MTLTexture, Texture, 0)
			
		public:
			
			MTLTexture();
			
			/// create external texture
			bool create(void *texture, Flags flags = DefaultFlags, Format format = FormatUnknown);
			
			/// native texture
			uint32_t getPixelFormat() const;
			uint32_t getTextureType() const;
			void *getMTLTexture() const;
			
			void *getMTLBuffer() const;
			
			void *getSharedPtr() const;
			
			using Texture::create;
	};
	
	/**
	 * The VKTexture class is a Vulkan-specific implementation of the Texture class, providing access to Vulkan texture resources and views.
	 * It enables the creation of external textures, specifying Vulkan image handles, formats, and layouts, while supporting various texture formats and flags.
	 * This class allows for managing texture layouts, retrieving texture views, and interacting with Vulkan-specific texture ranges, along with shared pointer functionality for interoperability.
	 * The class also inherits the create method from the Texture class, facilitating the initialization of textures in Vulkan-based applications.
	 */
	class TS_API VKTexture : public Texture {
			
			TS_DECLARE_PTR_1(VKTexture, Texture, 0)
			
		public:
			
			VKTexture();
			
			/// create external texture
			bool create(Type type, uint32_t format, VkImage texture, uint32_t layout, Flags flags = DefaultFlags, Format texture_format = FormatUnknown);
			
			/// native texture
			uint32_t getPixelFormat() const;
			VkImage getVKTexture() const;
			VkImageView getTextureView() const;
			
			void setTextureLayout(uint32_t layout);
			uint32_t getTextureLayout() const;
			
			void getTextureRange(void *range, const Slice &slice) const;
			
			void *getSharedPtr() const;
			void *getInteropHandle() const;
			
			using Texture::create;
	};
	
	/**
	 * The GLTexture class is an OpenGL-specific implementation of the Texture class, providing access to OpenGL texture resources.
	 * It enables the creation of external textures by specifying the texture target, ID, and additional flags, allowing for efficient interaction with OpenGL texture management system.
	 * This class provides functions to retrieve the texture target, internal format, and ID while inheriting the create method from the Texture class for initializing textures in OpenGL-based applications.
	 */
	class TS_API GLTexture : public Texture {
			
			TS_DECLARE_PTR_1(GLTexture, Texture, 0)
			
		public:
			
			GLTexture();
			
			/// create external texture
			bool create(uint32_t target, uint32_t texture_id, Flags flags = DefaultFlags, Format format = FormatUnknown);
			
			/// native texture
			uint32_t getTarget() const;
			uint32_t getInternalFormat() const;
			uint32_t getTextureID() const;
			
			using Texture::create;
	};
	
	/**
	 * The GLESTexture class is an OpenGLES-specific implementation of the Texture class, providing access to OpenGLES texture resources.
	 * It enables the creation of external textures by specifying the texture target, ID, and additional flags, allowing for efficient interaction with OpenGLES texture management system.
	 * This class provides functions to retrieve the texture target, internal format, and ID while inheriting the create method from the Texture class for initializing textures in OpenGLES-based applications.
	 */
	class TS_API GLESTexture : public Texture {
			
			TS_DECLARE_PTR_1(GLESTexture, Texture, 0)
			
		public:
			
			GLESTexture();
			
			/// create external texture
			bool create(uint32_t target, uint32_t texture_id, Flags flags = DefaultFlags, Format format = FormatUnknown);
			
			/// native texture
			uint32_t getTarget() const;
			uint32_t getInternalFormat() const;
			uint32_t getTextureID() const;
			
			using Texture::create;
	};
	
	/**
	 * The CUTexture class is a CUDA-specific implementation of the Texture class, providing access to CUDA texture resources and memory management.
	 * It allows retrieval of the texture array and texture levels, along with details about its array format and channels.
	 * Additionally, the class provides access to shared memory for efficient interoperation with CUDA, enabling advanced texture handling in GPU-based applications.
	 */
	class TS_API CUTexture : public Texture {
			
			TS_DECLARE_PTR_1(CUTexture, Texture, 0)
			
		public:
			
			CUTexture();
			
			/// native texture
			CUmipmappedArray getTextureArray() const;
			CUarray getTextureLevel(uint32_t index) const;
			uint32_t getArrayFormat() const;
			uint32_t getArrayChannels() const;
			CUexternalMemory getSharedMemory() const;
	};
	
	/**
	 * The HIPTexture class is a HIP-specific implementation of the Texture class, providing access to HIP texture resources and management.
	 * It allows retrieval of texture arrays, specific texture levels, and channel format details.
	 * This class is designed to facilitate efficient texture handling and interaction with HIP-based applications, supporting advanced texture operations and resource management.
	 */
	class TS_API HIPTexture : public Texture {
			
			TS_DECLARE_PTR_1(HIPTexture, Texture, 0)
			
		public:
			
			HIPTexture();
			
			/// native texture
			void *getTextureArray() const;
			void *getTextureLevel(uint32_t index) const;
			uint32_t getArrayFormat() const;
			uint32_t getArrayChannels() const;
			void *getSharedMemory() const;
	};
	
	/**
	 * The FUTexture class extends the Texture class to manage a fusion of multiple textures from different devices.
	 * It provides methods for setting and retrieving a device mask, tracking the number of fusion textures, and accessing individual textures within the fusion.
	 * This functionality is essential for managing textures across multiple devices, especially in high-performance or multi-device workflows where efficient resource handling is required.
	 */
	class TS_API FUTexture : public Texture {
			
			TS_DECLARE_PTR_1(FUTexture, Texture, 0)
			
		public:
			
			FUTexture();
			explicit FUTexture(const Array<Texture> &textures, bool owner = false);
			
			/// device mask
			void setMask(uint32_t mask);
			uint32_t getMask() const;
			
			/// Fusion textures
			uint32_t getNumTextures() const;
			const Texture getTexture(uint32_t index) const;
			Texture getTexture(uint32_t index);
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(Texture::Flags)
}

#endif /* __TELLUSIM_PLATFORM_TEXTURE_H__ */

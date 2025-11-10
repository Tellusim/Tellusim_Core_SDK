// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_BUFFER_H__
#define __TELLUSIM_PLATFORM_BUFFER_H__

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
	 * The Buffer class represents a GPU buffer resource that can be used for a wide range of data storage and access patterns.
	 * It supports creation with various flags that define its usage, such as read/write access, dynamic allocation, sharing, mapping, uniform or storage usage, vertex or index roles, and more.
	 * The class provides methods to create, clear, and query the buffer state, including platform type, format, size, and associated flags.
	 * The Buffer class is a versatile and foundational component for managing memory on the GPU.
	 */
	class TS_API Buffer {
			
			TS_DECLARE_PTR_0(Buffer, 0)
			
		public:
			
			/// Buffer flags
			enum Flags {
				FlagNone = 0,
				FlagRead			= (1 << 0),		// read buffer
				FlagWrite			= (1 << 1),		// write buffer
				FlagSource			= (1 << 2),		// source buffer
				FlagSparse			= (1 << 3),		// sparse buffer
				FlagShared			= (1 << 4),		// shared buffer
				FlagMapped			= (1 << 5),		// mapped buffer
				FlagExtern			= (1 << 6),		// extern buffer
				FlagInterop			= (1 << 7),		// interop buffer
				FlagDynamic			= (1 << 8),		// dynamic buffer
				FlagUniform			= (1 << 9),		// uniform buffer
				FlagStorage			= (1 << 10),	// storage buffer
				FlagAddress			= (1 << 11),	// address buffer
				FlagTracing			= (1 << 12),	// tracing buffer
				FlagScratch			= (1 << 13),	// scratch buffer
				FlagBinding			= (1 << 14),	// binding buffer
				FlagIndirect		= (1 << 15),	// indirect buffer
				FlagConditional		= (1 << 16),	// conditional buffer
				FlagVertex			= (1 << 17),	// vertex buffer
				FlagIndex			= (1 << 18),	// index buffer
				FlagTexel			= (1 << 19),	// texel buffer
				FlagAccel			= (1 << 20),	// accel buffer
				DefaultFlags		= FlagNone,
				NumFlags = 21,
			};
			
			Buffer();
			
			/// buffer platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// buffer device index
			uint32_t getIndex() const;
			
			/// clear buffer
			void clear();
			
			/// check buffer
			bool isCreated() const;
			
			/// buffer name
			void setName(const char *name);
			String getName() const;
			
			/// create buffer
			bool create(Flags flags, size_t size, Format format = FormatUnknown);
			
			bool isMapped() const;
			
			/// buffer flags
			Flags getFlags() const;
			
			TS_INLINE bool hasFlag(Flags flags) const { return ((getFlags() & flags) != FlagNone); }
			TS_INLINE bool hasFlags(Flags flags) const { return ((getFlags() & flags) == flags); }
			
			String getFlagsName() const;
			
			/// buffer format
			Format getFormat() const;
			
			TS_INLINE const char *getFormatName() const { return Tellusim::getFormatName(getFormat()); }
			
			TS_INLINE uint32_t getComponents() const { return getFormatComponents(getFormat()); }
			TS_INLINE uint32_t getPixelSize() const { return getFormatPixelSize(getFormat()); }
			
			/// buffer size
			size_t getSize();
			
			/// sparse buffer page size
			size_t getPageSize();
			
			/// buffer description
			String getDescription() const;
	};
	
	/**
	 * The BufferTable class provides a container for managing multiple buffers with support for bindless resource access.
	 * It enables more efficient rendering and compute operations by reducing the overhead associated with traditional binding.
	 */
	class TS_API BufferTable {
			
			TS_DECLARE_PTR_0(BufferTable, 0)
			
		public:
			
			BufferTable();
			
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
			bool create(uint32_t size);
			
			/// table buffers
			uint32_t getSize() const;
			Buffer get(uint32_t index) const;
			bool isOwner(uint32_t index) const;
			
			/// memory usage
			size_t getMemory() const;
	};
	
	/**
	 * The D3D12Buffer class is a Direct3D12-specific implementation of the Buffer class, providing access to internal resources and views.
	 * It allows the creation of external buffers from ID3D12Resource objects and provides methods to retrieve unordered access and shader resource views, along with the buffer memory address.
	 * This class also facilitates managing buffer state transitions and offers shared and interop handles for advanced resource handling.
	 */
	class TS_API D3D12Buffer : public Buffer {
			
			TS_DECLARE_PTR_1(D3D12Buffer, Buffer, 0)
			
		public:
			
			D3D12Buffer();
			
			/// create external buffer
			bool create(Flags flags, ID3D12Resource *buffer, uint32_t state);
			
			/// native buffer
			ID3D12Resource *getD3D12Buffer() const;
			size_t getUnorderedAccessView() const;
			size_t getShaderResourceView() const;
			uint64_t getBufferAddress() const;
			
			void setBufferState(uint32_t state);
			uint32_t getBufferState() const;
			
			void *getSharedHandle() const;
			void *getInteropHandle() const;
			
			using Buffer::create;
	};
	
	/**
	 * The D3D11Buffer class is a Direct3D11-specific implementation of the Buffer class, providing access to internal resources and views.
	 * It enables the creation of external buffers from ID3D11Buffer objects and provides methods to retrieve unordered access and shader resource views.
	 * This class also includes support for interop handles to facilitate advanced resource management in Direct3D11-based applications.
	 */
	class TS_API D3D11Buffer : public Buffer {
			
			TS_DECLARE_PTR_1(D3D11Buffer, Buffer, 0)
			
		public:
			
			D3D11Buffer();
			
			/// create external buffer
			bool create(Flags flags, ID3D11Buffer *buffer);
			
			/// native buffer
			ID3D11Buffer *getD3D11Buffer() const;
			ID3D11UnorderedAccessView *getUnorderedAccessView() const;
			ID3D11ShaderResourceView *getShaderResourceView() const;
			
			void *getInteropHandle() const;
			
			using Buffer::create;
	};
	
	/**
	 * The MTLBuffer class is a Metal-specific implementation of the Buffer class, providing access to internal resources in Metal-based applications.
	 * It supports the creation of external buffers from raw pointer data and offers methods to retrieve the Metal buffer and shared pointer for interop with other systems.
	 * The class also inherits the create method from the Buffer class to allow for flexible buffer creation and management.
	 */
	class TS_API MTLBuffer : public Buffer {
			
			TS_DECLARE_PTR_1(MTLBuffer, Buffer, 0)
			
		public:
			
			MTLBuffer();
			
			/// create external buffer
			bool create(Flags flags, void *buffer);
			
			/// native buffer
			void *getMTLBuffer() const;
			
			void *getSharedPtr() const;
			
			using Buffer::create;
	};
	
	/**
	 * The VKBuffer class is a Vulkan-specific implementation of the Buffer class, providing access to Vulkan buffer resources and views.
	 * It allows for the creation of external buffers, specifying Vulkan buffer handles and access modes, and includes methods for managing buffer access, retrieving the buffer address, and obtaining shared pointers for interoperability.
	 * The class also inherits the create method from the Buffer class, facilitating the initialization of buffers in Vulkan-based applications.
	 */
	class TS_API VKBuffer : public Buffer {
			
			TS_DECLARE_PTR_1(VKBuffer, Buffer, 0)
			
		public:
			
			VKBuffer();
			
			/// create external buffer
			bool create(Flags flags, size_t size, VkBuffer buffer, uint32_t access);
			
			/// native buffer
			VkBuffer getVKBuffer() const;
			VkBufferView getBufferView() const;
			uint64_t getBufferAddress() const;
			
			void setBufferAccess(uint32_t access);
			uint32_t getBufferAccess() const;
			
			void *getSharedPtr() const;
			void *getInteropHandle() const;
			
			using Buffer::create;
	};
	
	/**
	 * The GLBuffer class is an OpenGL-specific implementation of the Buffer class, providing access to OpenGL buffer resources.
	 * It enables the creation of external buffers by specifying the buffer target and ID, allowing for efficient interaction with OpenGL buffer management system.
	 * This class provides functions to retrieve the buffer target and ID while inheriting the create method from the Buffer class for initializing buffers in OpenGL-based applications.
	 */
	class TS_API GLBuffer : public Buffer {
			
			TS_DECLARE_PTR_1(GLBuffer, Buffer, 0)
			
		public:
			
			GLBuffer();
			
			/// create external buffer
			bool create(Flags flags, uint32_t target, uint32_t buffer_id);
			
			/// native buffer
			uint32_t getTarget() const;
			uint32_t getBufferID() const;
			
			using Buffer::create;
	};
	
	/**
	 * The GLESBuffer class is an OpenGLES-specific implementation of the Buffer class, providing access to OpenGLES buffer resources.
	 * It enables the creation of external buffers by specifying the buffer target and ID, allowing for efficient interaction with OpenGLES buffer management system.
	 * This class provides functions to retrieve the buffer target and ID while inheriting the create method from the Buffer class for initializing buffers in OpenGLES-based applications.
	 */
	class TS_API GLESBuffer : public Buffer {
			
			TS_DECLARE_PTR_1(GLESBuffer, Buffer, 0)
			
		public:
			
			GLESBuffer();
			
			/// create external buffer
			bool create(Flags flags, uint32_t target, uint32_t buffer_id);
			
			/// native buffer
			uint32_t getTarget() const;
			uint32_t getBufferID() const;
			
			using Buffer::create;
	};
	
	/**
	 * The CUBuffer class is a CUDA-specific implementation of the Buffer class, providing access to CUDA buffer resources and memory management.
	 * It offers functionality to retrieve the buffer pointer, data, and event, as well as information about its array format and channels.
	 * This class also includes a method to access the shared memory for CUDA interoperation, enabling seamless integration with CUDA-based applications.
	 */
	class TS_API CUBuffer : public Buffer {
			
			TS_DECLARE_PTR_1(CUBuffer, Buffer, 0)
			
		public:
			
			CUBuffer();
			
			/// native buffer
			size_t getBufferPtr() const;
			uint8_t *getBufferData() const;
			CUevent getBufferEvent() const;
			uint32_t getArrayFormat() const;
			uint32_t getArrayChannels() const;
			CUexternalMemory getSharedMemory() const;
	};
	
	/**
	 * The HIPBuffer class is a HIP-specific implementation of the Buffer class, providing access to HIP buffer resources and memory management.
	 * It allows retrieval of buffer pointers, data, events, and details about array format and channels.
	 * Additionally, the class supports interaction with shared memory, enabling efficient resource management and interoperation in HIP-based applications.
	 */
	class TS_API HIPBuffer : public Buffer {
			
			TS_DECLARE_PTR_1(HIPBuffer, Buffer, 0)
			
		public:
			
			HIPBuffer();
			
			/// native buffer
			void *getBufferPtr() const;
			uint8_t *getBufferData() const;
			void *getBufferEvent() const;
			uint32_t getArrayFormat() const;
			uint32_t getArrayChannels() const;
			void *getSharedMemory() const;
	};
	
	/**
	 * The FUBuffer class extends the Buffer class to manage a fusion of multiple buffers from different devices.
	 * It provides methods to set and retrieve a device mask, track the number of fusion buffers, and access individual buffers within the fusion.
	 * This functionality is particularly useful for high-performance computing scenarios that require managing and interacting with buffers from multiple devices in parallel workflows.
	 */
	class TS_API FUBuffer : public Buffer {
			
			TS_DECLARE_PTR_1(FUBuffer, Buffer, 0)
			
		public:
			
			FUBuffer();
			explicit FUBuffer(const Array<Buffer> &buffers, bool owner = false);
			
			/// device mask
			void setMask(uint32_t mask);
			uint32_t getMask() const;
			
			/// Fusion buffers
			uint32_t getNumBuffers() const;
			const Buffer getBuffer(uint32_t index) const;
			Buffer getBuffer(uint32_t index);
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(Buffer::Flags)
}

#endif /* __TELLUSIM_PLATFORM_BUFFER_H__ */

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_TRACING_H__
#define __TELLUSIM_PLATFORM_TRACING_H__

#include <TellusimTypes.h>
#include <TellusimFormat.h>
#include <core/TellusimArray.h>
#include <platform/TellusimBuffer.h>

/*
 */
namespace Tellusim {
	
	/**
	 * The Tracing class provides an abstraction for managing acceleration structures used in ray tracing tasks.
	 * It allows the creation, management, and manipulation of different types of acceleration structures, such as instances, triangles, and bounds.
	 * It provides methods to set up and manage vertex buffers, index buffers, and instance buffers, enabling the setup of geometries and the specification of tracing parameters.
	 */
	class TS_API Tracing {
			
			TS_DECLARE_PTR_0(Tracing, 0)
			
		public:
			
			/// Tracing types
			enum Type {
				TypeUnknown = 0,
				TypeInstance,
				TypeTriangle,
				TypeBound,
				NumTypes,
			};
			
			/// Tracing flags
			enum Flags {
				FlagNone = 0,
				FlagInfo			= (1 << 0),		// get build info
				FlagUpdate			= (1 << 1),		// update tracing
				FlagCompact			= (1 << 2),		// compact tracing
				FlagTransparent		= (1 << 3),		// transparent tracing
				FlagFastBuild		= (1 << 4),		// fast build tracing
				FlagFastTrace		= (1 << 5),		// fast trace tracing
				DefaultFlags		= FlagNone,
				NumFlags = 6,
			};
			
			Tracing();
			
			/// tracing platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// tracing device index
			uint32_t getIndex() const;
			
			/// clear tracing
			void clear();
			
			/// check tracing
			bool isCreated() const;
			bool isBuilt() const;
			
			/// tracing name
			void setName(const char *name);
			String getName() const;
			
			/// create tracing
			bool create(Type type, Flags flags = DefaultFlags);
			
			/// tracing type
			Type getType() const;
			
			static const char *getTypeName(Type type);
			const char *getTypeName() const;
			
			TS_INLINE bool isInstanceType() const { return (getType() == TypeInstance); }
			TS_INLINE bool isTriangleType() const { return (getType() == TypeTriangle); }
			TS_INLINE bool isBoundType() const { return (getType() == TypeBound); }
			
			TS_INLINE bool isGeometryType() const { return (getType() >= TypeTriangle && getType() <= TypeBound); }
			
			/// tracing parameters
			void setParameters(const Tracing &tracing);
			
			/// tracing geometries
			uint32_t getNumGeometries() const;
			
			/// instance buffer
			void setInstanceBuffer(uint32_t num_instances, Buffer &buffer, size_t offset = 0);
			void setInstanceBuffer(Buffer &buffer, size_t offset = 0);
			void setNumInstances(uint32_t num_instances);
			
			uint32_t getNumInstances() const;
			Buffer getInstanceBuffer() const;
			size_t getInstanceOffset() const;
			
			/// vertex buffers
			uint32_t addVertexBuffer(uint32_t num_vertices, Format format, size_t stride, Buffer buffer = Buffer::null, size_t offset = 0);
			void setVertexBuffer(uint32_t index, uint32_t num_vertices, Buffer &buffer, size_t offset = 0);
			void setVertexBuffer(uint32_t index, Buffer &buffer, size_t offset = 0);
			void setNumVertices(uint32_t index, uint32_t num_vertices);
			
			uint32_t getNumVertices(uint32_t index) const;
			Format getVertexFormat(uint32_t index) const;
			uint32_t getVertexStride(uint32_t index) const;
			Buffer getVertexBuffer(uint32_t index) const;
			size_t getVertexOffset(uint32_t index) const;
			
			/// index buffers
			uint32_t addIndexBuffer(uint32_t num_indices, Format format, Buffer buffer = Buffer::null, size_t offset = 0);
			void setIndexBuffer(uint32_t index, uint32_t num_indices, Buffer &buffer, size_t offset = 0);
			void setIndexBuffer(uint32_t index, Buffer &buffer, size_t offset = 0);
			void setNumIndices(uint32_t index, uint32_t num_indices);
			
			uint32_t getNumIndices(uint32_t index) const;
			Format getIndexFormat(uint32_t index) const;
			Buffer getIndexBuffer(uint32_t index) const;
			size_t getIndexOffset(uint32_t index) const;
			
			/// bound buffers
			uint32_t addBoundBuffer(uint32_t num_bounds, size_t stride, Buffer buffer = Buffer::null, size_t offset = 0);
			void setBoundBuffer(uint32_t index, uint32_t num_bounds, Buffer &buffer, size_t offset = 0);
			void setBoundBuffer(uint32_t index, Buffer &buffer, size_t offset = 0);
			void setNumBounds(uint32_t index, uint32_t num_bounds);
			
			uint32_t getNumBounds(uint32_t index) const;
			uint32_t getBoundStride(uint32_t index) const;
			Buffer getBoundBuffer(uint32_t index) const;
			size_t getBoundOffset(uint32_t index) const;
			
			/// indirect buffer
			void setIndirectBuffer(Buffer &buffer, size_t offset = 0);
			
			Buffer getIndirectBuffer() const;
			size_t getIndirectOffset() const;
			
			/// tracing description
			String getDescription() const;
			
			/// tracing address
			uint64_t getTracingAddress() const;
			
			/// scratch buffer size
			size_t getBuildSize() const;
			size_t getUpdateSize() const;
			
			/// memory usage
			size_t getMemory() const;
			
			/// tracing instance
			struct TS_ALIGNAS16 Instance {
				float32_t transform[12];	// row-major transform
				uint32_t data;				// intersection data
				uint32_t mask;				// intersection mask
				uint32_t flags;				// intersection flags
				uint32_t offset;			// intersection offset
				Tracing *tracing;			// geometry tracing
			};
			
			/// build indirect parameters
			struct BuildIndirect {
				uint32_t num_primitives;
				uint32_t base_primitive;
				uint32_t base_vertex;
				uint32_t base_transform;
			};
			
			/// instance size
			enum {
				InstanceSize = 64,
			};
	};
	
	/**
	 * The D3D12Tracing class is a Direct3D12-specific implementation of the Tracing class.
	 * It provides methods and structures for managing ray tracing acceleration structures within the Direct3D12 API.
	 */
	class TS_API D3D12Tracing : public Tracing {
			
			TS_DECLARE_PTR_1(D3D12Tracing, Tracing, 0)
			
		public:
			
			D3D12Tracing();
			
			void *getGeometryDesc(uint32_t index) const;
			void *getBuildInputs() const;
			void *getPrebuildInfo() const;
			void *getBuildDesc() const;
			
			Buffer getTracingBuffer() const;
			size_t getShaderResourceView() const;
			
			/// tracing instance
			struct D3D12Instance {
				float32_t transform[12];	// row-major transform
				uint32_t data : 24;			// intersection data
				uint32_t mask : 8;			// intersection mask
				uint32_t offset : 24;		// intersection offset
				uint32_t flags : 8;			// intersection flags
				uint64_t address;			// tracing address
			};
	};
	
	/**
	 * The MTLTracing class is a Metal-specific implementation of the Tracing class.
	 * It provides methods and structures for managing ray tracing acceleration structures within the Metal API.
	 */
	class TS_API MTLTracing : public Tracing {
			
			TS_DECLARE_PTR_1(MTLTracing, Tracing, 0)
			
		public:
			
			MTLTracing();
			
			void *getGeometryDesc(uint32_t index) const;
			void *getPrimitiveDesc() const;
			void *getInstanceDesc() const;
			
			void *getAccelerationStructure() const;
			
			/// tracing instance
			struct MTLInstance {
				float32_t transform[12];	// column-major transform
				uint32_t options;			// intersection options
				uint32_t mask;				// intersection mask
				uint32_t offset;			// intersection function offset
				uint32_t index;				// acceleration structure index
			};
	};
	
	/**
	 * The VKTracing class is a Vulkan-specific implementation of the Tracing class.
	 * It provides methods and structures for managing ray tracing acceleration structures within the Vulkan API.
	 */
	class TS_API VKTracing : public Tracing {
			
			TS_DECLARE_PTR_1(VKTracing, Tracing, 0)
			
		public:
			
			VKTracing();
			
			void *getBuildGeometryInfo() const;
			void *getBuildSizeInfo() const;
			
			Buffer getTracingBuffer() const;
			VkAccelerationStructureKHR getAccelerationStructure() const;
			
			/// tracing instance
			struct VKInstance {
				float32_t transform[12];	// row-major transform
				uint32_t data : 24;			// intersection data
				uint32_t mask : 8;			// intersection mask
				uint32_t offset : 24;		// intersection offset
				uint32_t flags : 8;			// intersection flags
				uint64_t address;			// tracing address
			};
	};
	
	/**
	 * The FUTracing class extends the Tracing class to manage a fusion of multiple tracing instances from different devices.
	 * It provides methods to set and retrieve a device mask, track the number of fusion tracings, and access individual tracings within the fusion.
	 * This functionality is particularly useful for high-performance computing scenarios that require managing and interacting with buffers from multiple devices in parallel workflows.
	 */
	class TS_API FUTracing : public Tracing {
			
			TS_DECLARE_PTR_1(FUTracing, Tracing, 0)
			
		public:
			
			FUTracing();
			explicit FUTracing(const Array<Tracing> &tracings, bool owner = false);
			
			/// device mask
			void setMask(uint32_t mask);
			uint32_t getMask() const;
			
			/// Fusion tracings
			uint32_t getNumTracings() const;
			const Tracing getTracing(uint32_t index) const;
			Tracing getTracing(uint32_t index);
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(Tracing::Flags)
}

#endif /* __TELLUSIM_PLATFORM_TRACING_H__ */

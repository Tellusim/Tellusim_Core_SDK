// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GRAPHICS_MESH_MODEL_H__
#define __TELLUSIM_GRAPHICS_MESH_MODEL_H__

#include <core/TellusimArray.h>
#include <core/TellusimFunction.h>
#include <TellusimFormat.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Async;
	class Stream;
	class Buffer;
	class Command;
	class Pipeline;
	class Device;
	class MeshGeometry;
	class Mesh;
	
	/**
	 * The MeshModel class represents a 3D model used in graphics rendering, offering various methods for creating, loading, and managing model data.
	 * It provides support for different model flags, such as optimizing indices, creating materials, and specifying buffer types.
	 * The class facilitates the setup of vertex and index buffers, meshlet buffers, and materials, with flexible configurations for geometry and material handling.
	 * It also supports the ability to draw the model in various ways, including instancing for efficient rendering.
	 * Additionally, the class offers tools for managing the memory usage of the model and interacting with the underlying device and pipeline for custom rendering operations.
	 */
	class TS_API MeshModel {
			
			TS_DECLARE_NONCOPY(MeshModel, 70)
			
		public:
			
			/// Model flags
			enum Flags {
				FlagNone = 0,
				FlagDirect			= (1 << 0),		// direct creation
				FlagVerbose			= (1 << 1),		// verbose creation
				FlagOptimize		= (1 << 2),		// optimize indices
				FlagMaterials		= (1 << 3),		// create materials
				FlagIndices10		= (1 << 4),		// create 10-bit indices
				FlagIndices16		= (1 << 5),		// create 16-bit indices
				FlagIndices32		= (1 << 6),		// create 32-bit indices
				FlagMeshlet64x84	= (1 << 7),		// create meshlets with 64 vertices and 84 triangles
				FlagMeshlet64x126	= (1 << 8),		// create meshlets with 64 vertices and 126 triangles
				FlagMeshlet96x169	= (1 << 9),		// create meshlets with 96 vertices and 169 triangles
				FlagMeshlet128x212	= (1 << 10),	// create meshlets with 128 vertices and 212 triangles
				FlagBufferWrite		= (1 << 11),	// create write buffers
				FlagBufferSource	= (1 << 12),	// create source buffers
				FlagBufferStorage	= (1 << 13),	// create storage buffers
				FlagBufferTracing	= (1 << 14),	// create tracing buffers
				FlagBufferAddress	= (1 << 15),	// create address buffers
				FlagBufferTexel		= (1 << 16),	// create texel buffers
				FlagMeshlets		= (FlagMeshlet64x84 | FlagMeshlet64x126 | FlagMeshlet96x169 | FlagMeshlet128x212),
				DefaultFlags		= (FlagVerbose | FlagMaterials),
				NumFlags = 17,
			};
			
			MeshModel();
			
			/// clear model
			void clear();
			
			/// check model
			bool isCreated() const;
			
			/// model flags
			Flags getFlags() const;
			
			TS_INLINE bool hasFlag(Flags flags) const { return ((getFlags() & flags) != FlagNone); }
			TS_INLINE bool hasFlags(Flags flags) const { return ((getFlags() & flags) == flags); }
			
			/// load model
			bool load(const Device &device, const Pipeline &pipeline, const char *name, Flags flags = DefaultFlags, Async *async = nullptr);
			bool load(const Device &device, const Pipeline &pipeline, Stream &stream, Flags flags = DefaultFlags, Async *async = nullptr);
			
			/// create model
			bool create(const Device &device, const Pipeline &pipeline, const char *name, Flags flags = DefaultFlags);
			bool create(const Device &device, const Pipeline &pipeline, const Mesh &mesh, Flags flags = DefaultFlags);
			bool create(const Device &device, const Pipeline &pipeline, const MeshGeometry &geometry, Flags flags = DefaultFlags);
			bool create(const Device &device, const Pipeline &pipeline, const Array<MeshGeometry> &geometries, Flags flags = DefaultFlags);
			
			/// create buffer callbacks
			using CreateCallback = Function<bool(const void *src, size_t size, bool owner)>;
			void setVertexBufferCallback(const CreateCallback &func);
			void setIndexBufferCallback(const CreateCallback &func);
			void setMeshBufferCallback(const CreateCallback &func);
			
			/// set model buffers
			void setBuffers(Command &command, uint32_t index = 0, const Pipeline *pipeline = nullptr) const;
			
			/// draw model
			void draw(Command &command) const;
			void draw(Command &command, uint32_t geometry) const;
			void draw(Command &command, uint32_t geometry, uint32_t material) const;
			
			/// draw instanced model
			void drawInstanced(Command &command, uint32_t geometry, uint32_t num_instances, uint32_t base_instance = 0) const;
			void drawInstanced(Command &command, uint32_t geometry, uint32_t material, uint32_t num_instances, uint32_t base_instance) const;
			
			/// vertices buffer
			uint32_t getNumVertices() const;
			uint32_t getNumVertexBuffers() const;
			uint32_t getVertexBufferStride(uint32_t index) const;
			size_t getVertexBufferOffset(uint32_t index) const;
			Buffer getVertexBuffer() const;
			
			/// indices buffer
			uint32_t getNumIndices() const;
			Format getIndexFormat() const;
			Buffer getIndexBuffer() const;
			
			/// meshlets buffer
			uint32_t getNumMeshlets() const;
			Buffer getMeshletBuffer() const;
			
			/// geometries
			uint32_t getNumGeometries() const;
			uint32_t getNumGeometryIndices(uint32_t geometry) const;
			uint32_t getNumGeometryVertices(uint32_t geometry) const;
			uint32_t getNumGeometryMeshlets(uint32_t geometry) const;
			uint32_t getGeometryBaseIndex(uint32_t geometry) const;
			uint32_t getGeometryBaseVertex(uint32_t geometry) const;
			uint32_t getGeometryBaseMeshlet(uint32_t geometry) const;
			
			/// geometry materials
			uint32_t getNumMaterials(uint32_t geometry) const;
			uint32_t getNumMaterialIndices(uint32_t geometry, uint32_t material) const;
			uint32_t getNumMaterialVertices(uint32_t geometry, uint32_t material) const;
			uint32_t getNumMaterialMeshlets(uint32_t geometry, uint32_t material) const;
			uint32_t getMaterialBaseIndex(uint32_t geometry, uint32_t material) const;
			uint32_t getMaterialBaseVertex(uint32_t geometry, uint32_t material) const;
			uint32_t getMaterialBaseMeshlet(uint32_t geometry, uint32_t material) const;
			
			/// memory usage
			size_t getMemory() const;
			
			struct Meshlet {
				uint32_t num_primitives;	// number of primitives
				uint32_t num_vertices;		// number of vertices
				uint32_t base_index;		// base meshlet index
				uint32_t base_vertex;		// base meshlet vertex
				float32_t bound_sphere[4];	// meshlet bound sphere
				float32_t normal_angle[4];	// meshlet normal angle
			};
			
		protected:
			
			/// create vertex buffer
			/// \param src Vertex data.
			/// \param size Vertex data size.
			/// \param owner If true, the vertex data must be freed with the Allocator class.
			virtual bool create_vertex_buffer(const Device &device, const void *src, size_t size, bool owner);
			
			/// create index buffer
			/// \param src Index data.
			/// \param size Index data size.
			/// \param owner If true, the index data must be freed with the Allocator class.
			virtual bool create_index_buffer(const Device &device, const void *src, size_t size, bool owner);
			
			/// create meshlet buffer
			/// \param src Meshlet data.
			/// \param size Meshlet data size.
			/// \param owner If true, the meshlet data must be freed with the Allocator class.
			virtual bool create_meshlet_buffer(const Device &device, const void *src, size_t size, bool owner);
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(MeshModel::Flags)
}

#endif /* __TELLUSIM_GRAPHICS_MESH_MODEL_H__ */

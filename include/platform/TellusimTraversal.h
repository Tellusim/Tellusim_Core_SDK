// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_TRAVERSAL_H__
#define __TELLUSIM_PLATFORM_TRAVERSAL_H__

#include <TellusimFormat.h>
#include <core/TellusimArray.h>
#include <platform/TellusimShader.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Stream;
	
	/**
	 * The Traversal class manages the configuration of a ray tracing pipeline, providing control over shaders, resource bindings, and pipeline states.
	 * It allows users to configure and retrieve various ray tracing pipeline parameters, including samplers, textures, and buffer bindings.
	 * The class supports shader creation, loading, and compilation in multiple formats, such as native, GLSL, and SPIRV, offering fine-grained control over ray tracing pipeline states.
	 */
	class TS_API Traversal {
			
			TS_DECLARE_PTR_0(Traversal, 0)
			
		public:
			
			Traversal();
			
			/// traversal platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// traversal device index
			uint32_t getIndex() const;
			
			/// clear traversal
			void clear();
			
			/// check traversal
			bool isCreated() const;
			
			/// traversal name
			void setName(const char *name);
			String getName() const;
			
			/// create traversal
			bool create();
			
			/// traversal parameters
			void setParameters(const Traversal &traversal);
			bool saveState(Stream &stream) const;
			
			/// shader pointers
			void addShader(Shader &shader, bool owner = false);
			
			Shader getRayGenShader() const;
			
			/// load shaders
			bool loadShader(Shader::Type type, const char *name, const char *format, ...) TS_PRINTF(4, 5);
			bool loadShaderGLSL(Shader::Type type, const char *name, const char *format, ...) TS_PRINTF(4, 5);
			bool loadShader(Shader::Type type, const char *name, const String &macros = String::null, const char **includes = nullptr, uint32_t size = 0);
			bool loadShaderGLSL(Shader::Type type, const char *name, const String &macros = String::null, const char **includes = nullptr, uint32_t size = 0);
			bool loadShaderSPIRV(Shader::Type type, const char *name);
			
			/// create shaders
			bool createShader(Shader::Type type, const char *src, const char *format, ...) TS_PRINTF(4, 5);
			bool createShaderGLSL(Shader::Type type, const char *src, const char *format, ...) TS_PRINTF(4, 5);
			bool createShader(Shader::Type type, const char *src, const String &macros = String::null, const char **includes = nullptr, uint32_t size = 0);
			bool createShaderGLSL(Shader::Type type, const char *src, const String &macros = String::null, const char **includes = nullptr, uint32_t size = 0);
			bool createShaderSPIRV(Shader::Type type, const Array<uint32_t> &data);
			
			/// sampler parameters
			uint32_t addSampler(Shader::Mask mask);
			uint32_t getNumSamplers() const;
			
			Traversal &setSamplerOffset(uint32_t offset);
			uint32_t getSamplerOffset() const;
			
			Traversal &setSamplerMask(uint32_t index, Shader::Mask mask);
			Shader::Mask getSamplerMask(uint32_t index) const;
			
			Traversal &setSamplerMasks(uint32_t index, uint32_t num, Shader::Mask mask, bool array = false);
			Shader::Mask getSamplerMasks(uint32_t index, uint32_t num) const;
			
			Traversal &setSamplerArray(uint32_t index, uint32_t num, bool array);
			uint32_t getSamplerArray(uint32_t index) const;
			
			/// texture parameters
			uint32_t addTexture(Shader::Mask mask);
			uint32_t getNumTextures() const;
			
			Traversal &setTextureOffset(uint32_t offset);
			uint32_t getTextureOffset() const;
			
			Traversal &setTextureMask(uint32_t index, Shader::Mask mask);
			Shader::Mask getTextureMask(uint32_t index) const;
			
			Traversal &setTextureMasks(uint32_t index, uint32_t num, Shader::Mask mask, bool array = false);
			Shader::Mask getTextureMasks(uint32_t index, uint32_t num) const;
			
			Traversal &setTextureArray(uint32_t index, uint32_t num, bool array);
			uint32_t getTextureArray(uint32_t index) const;
			
			/// surface parameters
			uint32_t addSurface(Shader::Mask mask);
			uint32_t getNumSurfaces() const;
			
			Traversal &setSurfaceOffset(uint32_t offset);
			uint32_t getSurfaceOffset() const;
			
			Traversal &setSurfaceMask(uint32_t index, Shader::Mask mask);
			Shader::Mask getSurfaceMask(uint32_t index) const;
			
			Traversal &setSurfaceMasks(uint32_t index, uint32_t num, Shader::Mask mask, bool array = false);
			Shader::Mask getSurfaceMasks(uint32_t index, uint32_t num) const;
			
			Traversal &setSurfaceArray(uint32_t index, uint32_t num, bool array);
			uint32_t getSurfaceArray(uint32_t index) const;
			
			/// uniform parameters
			uint32_t addUniform(Shader::Mask mask, BindFlags flags = BindFlagNone);
			uint32_t getNumUniforms() const;
			
			Traversal &setUniformOffset(uint32_t offset);
			uint32_t getUniformOffset() const;
			
			Traversal &setUniformMask(uint32_t index, Shader::Mask mask, BindFlags flags = BindFlagNone);
			Shader::Mask getUniformMask(uint32_t index) const;
			
			Traversal &setUniformMasks(uint32_t index, uint32_t num, Shader::Mask mask, BindFlags flags = BindFlagNone);
			Shader::Mask getUniformMasks(uint32_t index, uint32_t num) const;
			
			Traversal &setUniformFlags(uint32_t index, BindFlags flags);
			BindFlags getUniformFlags(uint32_t index) const;
			
			/// storage parameters
			uint32_t addStorage(Shader::Mask mask, BindFlags flags = BindFlagNone);
			uint32_t getNumStorages() const;
			
			Traversal &setStorageOffset(uint32_t offset);
			uint32_t getStorageOffset() const;
			
			Traversal &setStorageMask(uint32_t index, Shader::Mask mask, BindFlags flags = BindFlagNone);
			Shader::Mask getStorageMask(uint32_t index) const;
			
			Traversal &setStorageMasks(uint32_t index, uint32_t num, Shader::Mask mask, BindFlags flags = BindFlagNone);
			Shader::Mask getStorageMasks(uint32_t index, uint32_t num) const;
			
			Traversal &setStorageFlags(uint32_t index, BindFlags flags);
			BindFlags getStorageFlags(uint32_t index) const;
			
			/// tracing parameters
			uint32_t addTracing(Shader::Mask mask);
			uint32_t getNumTracings() const;
			
			Traversal &setTracingOffset(uint32_t offset);
			uint32_t getTracingOffset() const;
			
			Traversal &setTracingMask(uint32_t index, Shader::Mask mask);
			Shader::Mask getTracingMask(uint32_t index) const;
			
			Traversal &setTracingMasks(uint32_t index, uint32_t num, Shader::Mask mask);
			Shader::Mask getTracingMasks(uint32_t index, uint32_t num) const;
			
			/// texel parameters
			uint32_t addTexel(Shader::Mask mask);
			uint32_t getNumTexels() const;
			
			Traversal &setTexelOffset(uint32_t offset);
			uint32_t getTexelOffset() const;
			
			Traversal &setTexelMask(uint32_t index, Shader::Mask mask);
			Shader::Mask getTexelMask(uint32_t index) const;
			
			Traversal &setTexelMasks(uint32_t index, uint32_t num, Shader::Mask mask);
			Shader::Mask getTexelMasks(uint32_t index, uint32_t num) const;
			
			/// table parameters
			uint32_t addTable(TableType type, uint32_t size, Shader::Mask mask, BindFlags flags = BindFlagNone);
			uint32_t getNumTables() const;
			
			Traversal &setTableOffset(uint32_t offset);
			uint32_t getTableOffset() const;
			
			Traversal &setTableType(uint32_t index, TableType type, uint32_t size, Shader::Mask mask, BindFlags flags = BindFlagNone);
			TableType getTableType(uint32_t index) const;
			uint32_t getTableSize(uint32_t index) const;
			
			Traversal &setTableMask(uint32_t index, Shader::Mask mask, BindFlags flags = BindFlagNone);
			Shader::Mask getTableMask(uint32_t index) const;
			
			Traversal &setTableFlags(uint32_t index, BindFlags flags);
			BindFlags getTableFlags(uint32_t index) const;
			
			/// recursion depth
			void setRecursionDepth(uint32_t depth);
			uint32_t getRecursionDepth() const;
	};
	
	/**
	 * The D3D12Traversal class is a specialized ray tracing pipeline for Direct3D12, derived from the Traversal class.
	 * It provides access to the native Direct3D12 root signature, enabling precise control over resource bindings and pipeline state in Direct3D12 ray tracing workflows.
	 */
	class TS_API D3D12Traversal : public Traversal {
			
			TS_DECLARE_PTR_1(D3D12Traversal, Traversal, 0)
			
		public:
			
			D3D12Traversal();
			
			ID3D12RootSignature *getRootSignature() const;
	};
	
	/**
	 * The FUTraversal class extends the Traversal class to manage a fusion of multiple ray tracing pipelines across different devices.
	 * It provides methods to set and retrieve a device mask, track the number of fused traversals, and access individual traversals within the fusion.
	 * This design is particularly beneficial for high-performance computing scenarios that require synchronized execution of ray tracing operations across multiple devices.
	 */
	class TS_API FUTraversal : public Traversal {
			
			TS_DECLARE_PTR_1(FUTraversal, Traversal, 0)
			
		public:
			
			FUTraversal();
			explicit FUTraversal(const Array<Traversal> &traversals, bool owner = false);
			
			/// device mask
			void setMask(uint32_t mask);
			uint32_t getMask() const;
			
			/// Fusion traversals
			uint32_t getNumTraversals() const;
			const Traversal getTraversal(uint32_t index) const;
			Traversal getTraversal(uint32_t index);
	};
}

#endif /* __TELLUSIM_PLATFORM_TRAVERSAL_H__ */

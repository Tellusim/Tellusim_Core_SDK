// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_KERNEL_H__
#define __TELLUSIM_PLATFORM_KERNEL_H__

#include <core/TellusimArray.h>
#include <core/TellusimString.h>
#include <platform/TellusimPlatform.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class String;
	class Stream;
	class Shader;
	
	/**
	 * The Kernel class represents a compute kernel responsible for managing shaders, textures, buffers, samplers, surfaces, uniforms, and storage within a computational pipeline.
	 * It allows users to set and retrieve various parameters, including device index, platform, and kernel state, while supporting shader compilation, loading, and creation in formats like native, GLSL, and SPIRV.
	 * The class also provides functionality for configuring kernel parameters such as texture, surface, and storage settings, along with memory alignment and sampler configurations, offering comprehensive control over the pipeline compute operations.
	 */
	class TS_API Kernel {
			
			TS_DECLARE_PTR_0(Kernel, 0)
			
		public:
			
			Kernel();
			
			/// kernel platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// kernel device index
			uint32_t getIndex() const;
			
			/// clear kernel
			void clear();
			
			/// check kernel
			bool isCreated() const;
			
			/// kernel name
			void setName(const char *name);
			String getName() const;
			
			/// create kernel
			bool create();
			
			/// kernel parameters
			void setParameters(const Kernel &kernel);
			bool saveState(Stream &stream) const;
			
			/// shader pointer
			void setShader(Shader &shader, bool owner = false);
			
			Shader getComputeShader() const;
			
			/// load shaders
			bool loadShader(const char *name, const char *format, ...) TS_PRINTF(3, 4);
			bool loadShaderGLSL(const char *name, const char *format, ...) TS_PRINTF(3, 4);
			bool loadShader(const char *name, const String &macros = String::null, const char **includes = nullptr, uint32_t size = 0);
			bool loadShaderGLSL(const char *name, const String &macros = String::null, const char **includes = nullptr, uint32_t size = 0);
			bool loadShaderSPIRV(const char *name);
			
			/// create shaders
			bool createShader(const char *src, const char *format, ...) TS_PRINTF(3, 4);
			bool createShaderGLSL(const char *src, const char *format, ...) TS_PRINTF(3, 4);
			bool createShader(const char *src, const String &macros = String::null, const char **includes = nullptr, uint32_t size = 0);
			bool createShaderGLSL(const char *src, const String &macros = String::null, const char **includes = nullptr, uint32_t size = 0);
			bool createShaderSPIRV(const Array<uint32_t> &data);
			
			/// sampler parameters
			uint32_t addSampler();
			Kernel &setSamplers(uint32_t num);
			uint32_t getNumSamplers() const;
			
			Kernel &setSamplerOffset(uint32_t offset);
			uint32_t getSamplerOffset() const;
			
			Kernel &setSamplerArray(uint32_t index, uint32_t num, bool array);
			uint32_t getSamplerArray(uint32_t index) const;
			
			/// texture parameters
			uint32_t addTexture();
			Kernel &setTextures(uint32_t num);
			uint32_t getNumTextures() const;
			
			Kernel &setTextureOffset(uint32_t offset);
			uint32_t getTextureOffset() const;
			
			Kernel &setTextureArray(uint32_t index, uint32_t num, bool array);
			uint32_t getTextureArray(uint32_t index) const;
			
			/// surface parameters
			uint32_t addSurface();
			Kernel &setSurfaces(uint32_t num);
			uint32_t getNumSurfaces() const;
			
			Kernel &setSurfaceOffset(uint32_t offset);
			uint32_t getSurfaceOffset() const;
			
			Kernel &setSurfaceArray(uint32_t index, uint32_t num, bool array);
			uint32_t getSurfaceArray(uint32_t index) const;
			
			/// uniform parameters
			uint32_t addUniform(BindFlags flags = BindFlagNone);
			Kernel &setUniforms(uint32_t num, BindFlags flags = BindFlagNone);
			uint32_t getNumUniforms() const;
			
			Kernel &setUniformOffset(uint32_t offset);
			uint32_t getUniformOffset() const;
			
			Kernel &setUniformFlags(uint32_t index, BindFlags flags);
			BindFlags getUniformFlags(uint32_t index) const;
			
			/// storage parameters
			uint32_t addStorage(BindFlags flags = BindFlagNone);
			Kernel &setStorages(uint32_t num, BindFlags flags = BindFlagNone);
			uint32_t getNumStorages() const;
			
			Kernel &setStorageOffset(uint32_t offset);
			uint32_t getStorageOffset() const;
			
			Kernel &setStorageFlags(uint32_t index, BindFlags flags);
			BindFlags getStorageFlags(uint32_t index) const;
			
			/// tracing parameters
			uint32_t addTracing();
			Kernel &setTracings(uint32_t num);
			uint32_t getNumTracings() const;
			
			Kernel &setTracingOffset(uint32_t offset);
			uint32_t getTracingOffset() const;
			
			/// texel parameters
			uint32_t addTexel();
			Kernel &setTexels(uint32_t num);
			uint32_t getNumTexels() const;
			
			Kernel &setTexelOffset(uint32_t offset);
			uint32_t getTexelOffset() const;
			
			/// table parameters
			uint32_t addTable(TableType type, uint32_t size);
			uint32_t getNumTables() const;
			
			Kernel &setTableOffset(uint32_t offset);
			uint32_t getTableOffset() const;
			
			Kernel &setTableType(uint32_t index, TableType type, uint32_t size, BindFlags flags = BindFlagNone);
			TableType getTableType(uint32_t index) const;
			uint32_t getTableSize(uint32_t index) const;
			
			Kernel &setTableFlags(uint32_t index, BindFlags flags);
			BindFlags getTableFlags(uint32_t index) const;
			
			/// thread group size
			void setGroupSize(uint32_t width, uint32_t height = 1, uint32_t depth = 1);
			
			uint32_t getGroupSizeX() const;
			uint32_t getGroupSizeY() const;
			uint32_t getGroupSizeZ() const;
	};
	
	/**
	 * The D3D12Kernel class is a specialized compute kernel for Direct3D12, inheriting from the Kernel class.
	 * It provides a method to retrieve the root signature, which is a critical component for binding resources and defining pipeline states in Direct3D12.
	 */
	class TS_API D3D12Kernel : public Kernel {
			
			TS_DECLARE_PTR_1(D3D12Kernel, Kernel, 0)
			
		public:
			
			D3D12Kernel();
			
			ID3D12RootSignature *getRootSignature() const;
	};
	
	/**
	 * The MTLKernel class is a compute kernel designed for Metal, inheriting from the Kernel class.
	 * It allows enabling or disabling indirect command buffers and provides access to the compute function.
	 */
	class TS_API MTLKernel : public Kernel {
			
			TS_DECLARE_PTR_1(MTLKernel, Kernel, 0)
			
		public:
			
			MTLKernel();
			
			/// indirect command buffer
			void setIndirect(bool enabled);
			bool isIndirect() const;
			
			void *getComputeFunction() const;
	};
	
	/**
	 * The FUKernel class extends the Kernel class to manage a fusion of multiple compute kernels across different devices.
	 * It provides methods to set and retrieve a device mask, track the number of fused kernels, and access individual kernels within the fusion.
	 * This design is useful for high-performance computing workflows that require coordinated execution of compute operations across multiple devices.
	 */
	class TS_API FUKernel : public Kernel {
			
			TS_DECLARE_PTR_1(FUKernel, Kernel, 0)
			
		public:
			
			FUKernel();
			explicit FUKernel(const Array<Kernel> &kernels, bool owner = false);
			
			/// device mask
			void setMask(uint32_t mask);
			uint32_t getMask() const;
			
			/// Fusion kernels
			uint32_t getNumKernels() const;
			const Kernel getKernel(uint32_t index) const;
			Kernel getKernel(uint32_t index);
	};
}

#endif /* __TELLUSIM_PLATFORM_KERNEL_H__ */

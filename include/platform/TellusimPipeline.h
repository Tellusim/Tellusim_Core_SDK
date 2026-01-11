// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_PIPELINE_H__
#define __TELLUSIM_PLATFORM_PIPELINE_H__

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
	 * The Pipeline class manages the configuration of a graphics pipeline, offering control over shader stages, primitive types, blending, depth and stencil testing, and rasterization.
	 * It allows users to configure and retrieve various pipeline parameters, including vertex attributes, texture and surface bindings, sampling configurations, and memory offsets.
	 * The class supports shader creation, loading, and compilation in multiple formats such as native, GLSL, and SPIRV, providing fine-grained control over pipeline states.
	 */
	class TS_API Pipeline {
			
			TS_DECLARE_PTR_0(Pipeline, 0)
			
		public:
			
			/// Primitive types
			enum Primitive {
				PrimitivePoint = 0,				// point primitive
				PrimitivePointPatch,			// point patch primitive
				PrimitiveLine,					// line primitive
				PrimitiveLineAdj,				// line with adjacency primitive
				PrimitiveLineStrip,				// line strip primitive
				PrimitiveLinePatch,				// line patch primitive
				PrimitiveTriangle,				// triangle primitive
				PrimitiveTriangleAdj,			// triangle with adjacency primitive
				PrimitiveTriangleStrip,			// triangle strip primitive
				PrimitiveTrianglePatch,			// triangle patch primitive
				PrimitiveQuadrilateralPatch,	// quadrilateral patch primitive
				NumPrimitiveTypes,
			};
			
			/// Attribute types
			enum Attribute {
				AttributePosition = 0,			// position attribute
				AttributeBasis,					// basis attribute
				AttributeNormal,				// normal attribute
				AttributeTangent,				// tangent attribute
				AttributeBinormal,				// binormal attribute
				AttributeTexCoord,				// texcoord attribute
				AttributeWeights,				// joint weights attribute
				AttributeJoints,				// joint indices attribute
				AttributeColor,					// vertex color attribute
				AttributeIndex,					// vertex index attribute
				NumAttributeTypes,
			};
			
			/// Filling modes
			enum FillMode {
				FillModeLine = 0,
				FillModeSolid,
				NumFillModes,
			};
			
			/// Culling modes
			enum CullMode {
				CullModeNone = 0,
				CullModeBack,
				CullModeFront,
				NumCullModes,
			};
			
			/// Front modes
			enum FrontMode {
				FrontModeCCW = 0,
				FrontModeCW,
				NumFrontModes,
			};
			
			/// Blending operations
			enum BlendOp {
				BlendOpAdd = 0,
				BlendOpSub,
				BlendOpMin,
				BlendOpMax,
				NumBlendOperations,
			};
			
			/// Blending functions
			enum BlendFunc {
				BlendFuncNone = 0,
				BlendFuncZero,
				BlendFuncOne,
				BlendFuncSrcColor,
				BlendFuncSrcAlpha,
				BlendFuncSrc1Color,
				BlendFuncSrc1Alpha,
				BlendFuncDestColor,
				BlendFuncDestAlpha,
				BlendFuncFactorColor,
				BlendFuncFactorAlpha,
				BlendFuncInvSrcColor,
				BlendFuncInvSrcAlpha,
				BlendFuncInvSrc1Color,
				BlendFuncInvSrc1Alpha,
				BlendFuncInvDestColor,
				BlendFuncInvDestAlpha,
				BlendFuncInvFactorColor,
				BlendFuncInvFactorAlpha,
				NumBlendFunctions,
			};
			
			/// Color masks
			enum ColorMask {
				ColorMaskNone = 0,
				ColorMaskR			= (1 << 0),
				ColorMaskG			= (1 << 1),
				ColorMaskB			= (1 << 2),
				ColorMaskA			= (1 << 3),
				ColorMaskUnknown	= (1 << 4),
				ColorMaskRGB		= (ColorMaskR | ColorMaskG | ColorMaskB),
				ColorMaskAll		= (ColorMaskRGB | ColorMaskA),
			};
			
			/// Depth masks
			enum DepthMask {
				DepthMaskNone = 0,
				DepthMaskRead,
				DepthMaskWrite,
				NumDepthMasks,
			};
			
			/// Depth functions
			enum DepthFunc {
				DepthFuncNone = 0,
				DepthFuncNever,
				DepthFuncAlways,
				DepthFuncEqual,
				DepthFuncLess,
				DepthFuncGreater,
				DepthFuncNotEqual,
				DepthFuncLessEqual,
				DepthFuncGreaterEqual,
				NumDepthFunctions,
			};
			
			/// Stencil operations
			enum StencilOp {
				StencilOpKeep = 0,
				StencilOpInvert,
				StencilOpReplace,
				StencilOpIncrWrap,
				StencilOpDecrWrap,
				StencilOpIncrSat,
				StencilOpDecrSat,
				NumStencilOperations,
			};
			
			/// Stencil functions
			enum StencilFunc {
				StencilFuncNone = 0,
				StencilFuncNever,
				StencilFuncAlways,
				StencilFuncEqual,
				StencilFuncLess,
				StencilFuncGreater,
				StencilFuncNotEqual,
				StencilFuncLessEqual,
				StencilFuncGreaterEqual,
				NumStencilFunctions,
			};
			
			Pipeline();
			
			/// pipeline platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// pipeline device index
			uint32_t getIndex() const;
			
			/// clear pipeline
			void clear();
			
			/// check pipeline
			bool isCreated() const;
			
			/// pipeline name
			void setName(const char *name);
			String getName() const;
			
			/// create pipeline
			bool create();
			
			/// pipeline parameters
			void setParameters(const Pipeline &pipeline);
			bool saveState(Stream &stream) const;
			
			/// shader pointers
			void addShader(Shader &shader, bool owner = false);
			
			Shader getVertexShader() const;
			Shader getControlShader() const;
			Shader getEvaluateShader() const;
			Shader getGeometryShader() const;
			Shader getFragmentShader() const;
			Shader getTaskShader() const;
			Shader getMeshShader() const;
			
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
			
			Pipeline &setSamplerOffset(uint32_t offset);
			uint32_t getSamplerOffset() const;
			
			Pipeline &setSamplerMask(uint32_t index, Shader::Mask mask);
			Shader::Mask getSamplerMask(uint32_t index) const;
			
			Pipeline &setSamplerMasks(uint32_t index, uint32_t num, Shader::Mask mask, bool array = false);
			Shader::Mask getSamplerMasks(uint32_t index, uint32_t num) const;
			
			Pipeline &setSamplerArray(uint32_t index, uint32_t num, bool array);
			uint32_t getSamplerArray(uint32_t index) const;
			
			/// texture parameters
			uint32_t addTexture(Shader::Mask mask);
			uint32_t getNumTextures() const;
			
			Pipeline &setTextureOffset(uint32_t offset);
			uint32_t getTextureOffset() const;
			
			Pipeline &setTextureMask(uint32_t index, Shader::Mask mask);
			Shader::Mask getTextureMask(uint32_t index) const;
			
			Pipeline &setTextureMasks(uint32_t index, uint32_t num, Shader::Mask mask, bool array = false);
			Shader::Mask getTextureMasks(uint32_t index, uint32_t num) const;
			
			Pipeline &setTextureArray(uint32_t index, uint32_t num, bool array);
			uint32_t getTextureArray(uint32_t index) const;
			
			/// surface parameters
			uint32_t addSurface(Shader::Mask mask);
			uint32_t getNumSurfaces() const;
			
			Pipeline &setSurfaceOffset(uint32_t offset);
			uint32_t getSurfaceOffset() const;
			
			Pipeline &setSurfaceMask(uint32_t index, Shader::Mask mask);
			Shader::Mask getSurfaceMask(uint32_t index) const;
			
			Pipeline &setSurfaceMasks(uint32_t index, uint32_t num, Shader::Mask mask, bool array = false);
			Shader::Mask getSurfaceMasks(uint32_t index, uint32_t num) const;
			
			Pipeline &setSurfaceArray(uint32_t index, uint32_t num, bool array);
			uint32_t getSurfaceArray(uint32_t index) const;
			
			/// uniform parameters
			uint32_t addUniform(Shader::Mask mask, BindFlags flags = BindFlagNone);
			uint32_t getNumUniforms() const;
			
			Pipeline &setUniformOffset(uint32_t offset);
			uint32_t getUniformOffset() const;
			
			Pipeline &setUniformMask(uint32_t index, Shader::Mask mask, BindFlags flags = BindFlagNone);
			Shader::Mask getUniformMask(uint32_t index) const;
			
			Pipeline &setUniformMasks(uint32_t index, uint32_t num, Shader::Mask mask, BindFlags flags = BindFlagNone);
			Shader::Mask getUniformMasks(uint32_t index, uint32_t num) const;
			
			Pipeline &setUniformFlags(uint32_t index, BindFlags flags);
			BindFlags getUniformFlags(uint32_t index) const;
			
			/// storage parameters
			uint32_t addStorage(Shader::Mask mask, BindFlags flags = BindFlagNone);
			uint32_t getNumStorages() const;
			
			Pipeline &setStorageOffset(uint32_t offset);
			uint32_t getStorageOffset() const;
			
			Pipeline &setStorageMask(uint32_t index, Shader::Mask mask, BindFlags flags = BindFlagNone);
			Shader::Mask getStorageMask(uint32_t index) const;
			
			Pipeline &setStorageMasks(uint32_t index, uint32_t num, Shader::Mask mask, BindFlags flags = BindFlagNone);
			Shader::Mask getStorageMasks(uint32_t index, uint32_t num) const;
			
			Pipeline &setStorageFlags(uint32_t index, BindFlags flags);
			BindFlags getStorageFlags(uint32_t index) const;
			
			/// tracing parameters
			uint32_t addTracing(Shader::Mask mask);
			uint32_t getNumTracings() const;
			
			Pipeline &setTracingOffset(uint32_t offset);
			uint32_t getTracingOffset() const;
			
			Pipeline &setTracingMask(uint32_t index, Shader::Mask mask);
			Shader::Mask getTracingMask(uint32_t index) const;
			
			Pipeline &setTracingMasks(uint32_t index, uint32_t num, Shader::Mask mask);
			Shader::Mask getTracingMasks(uint32_t index, uint32_t num) const;
			
			/// texel parameters
			uint32_t addTexel(Shader::Mask mask);
			uint32_t getNumTexels() const;
			
			Pipeline &setTexelOffset(uint32_t offset);
			uint32_t getTexelOffset() const;
			
			Pipeline &setTexelMask(uint32_t index, Shader::Mask mask);
			Shader::Mask getTexelMask(uint32_t index) const;
			
			Pipeline &setTexelMasks(uint32_t index, uint32_t num, Shader::Mask mask);
			Shader::Mask getTexelMasks(uint32_t index, uint32_t num) const;
			
			/// table parameters
			uint32_t addTable(TableType type, uint32_t size, Shader::Mask mask, BindFlags flags = BindFlagNone);
			uint32_t getNumTables() const;
			
			Pipeline &setTableOffset(uint32_t offset);
			uint32_t getTableOffset() const;
			
			Pipeline &setTableType(uint32_t index, TableType type, uint32_t size, Shader::Mask mask, BindFlags flags = BindFlagNone);
			TableType getTableType(uint32_t index) const;
			uint32_t getTableSize(uint32_t index) const;
			
			Pipeline &setTableMask(uint32_t index, Shader::Mask mask, BindFlags flags = BindFlagNone);
			Shader::Mask getTableMask(uint32_t index) const;
			
			Pipeline &setTableFlags(uint32_t index, BindFlags flags);
			BindFlags getTableFlags(uint32_t index) const;
			
			/// vertex parameters
			uint32_t getNumVertices() const;
			uint32_t getVertexStride(uint32_t index) const;
			uint32_t getVertexRate(uint32_t index) const;
			
			/// vertex attributes
			uint32_t addAttribute(Attribute attribute, Format format, uint32_t vertex, size_t offset, size_t stride, uint32_t rate = 0);
			Pipeline &setAttribute(uint32_t index, Attribute attribute, Format format, uint32_t vertex, size_t offset, size_t stride, uint32_t rate = 0);
			Pipeline &setAttributeType(uint32_t index, Attribute attribute);
			Pipeline &setAttributeFormat(uint32_t index, Format format);
			Pipeline &setAttributeVertex(uint32_t index, uint32_t vertex);
			Pipeline &setAttributeOffset(uint32_t index, size_t offset);
			Pipeline &setAttributeStride(uint32_t index, size_t stride);
			Pipeline &setAttributeRate(uint32_t index, uint32_t rate);
			
			uint32_t getNumAttributes() const;
			Attribute getAttributeType(uint32_t index) const;
			Format getAttributeFormat(uint32_t index) const;
			uint32_t getAttributeVertex(uint32_t index) const;
			uint32_t getAttributeOffset(uint32_t index) const;
			uint32_t getAttributeStride(uint32_t index) const;
			uint32_t getAttributeRate(uint32_t index) const;
			
			/// rasterization parameters
			void setPrimitive(Primitive primitive);
			Primitive getPrimitive() const;
			
			void setFillMode(FillMode mode);
			FillMode getFillMode() const;
			
			void setCullMode(CullMode mode);
			CullMode getCullMode() const;
			
			void setFrontMode(FrontMode mode);
			FrontMode getFrontMode() const;
			
			void setDepthBias(float32_t bias, float32_t slope, float32_t clamp = 0.0f);
			float32_t getDepthBias() const;
			float32_t getDepthSlope() const;
			float32_t getDepthClamp() const;
			
			void setMultisample(uint32_t multisample);
			uint32_t getMultisample() const;
			
			void setSampleMask(uint32_t sample_mask);
			uint32_t getSampleMask() const;
			
			void setDepthClip(bool enabled);
			bool getDepthClip() const;
			
			void setDepthReplace(bool enabled);
			bool getDepthReplace() const;
			
			void setScissorTest(bool enabled);
			bool getScissorTest() const;
			
			void setRasterDiscard(bool enabled);
			bool getRasterDiscard() const;
			
			void setSampleShading(bool enabled);
			bool getSampleShading() const;
			
			void setAlphaToCoverage(bool enabled);
			bool getAlphaToCoverage() const;
			
			void setMultisampleRaster(bool enabled);
			bool getMultisampleRaster() const;
			
			void setConservativeRaster(bool enabled);
			bool getConservativeRaster() const;
			
			void setNumViewports(uint32_t num_viewports);
			uint32_t getNumTargets() const;
			uint32_t getNumViewports() const;
			
			void setNumClipDistances(uint32_t num_distances);
			uint32_t getNumClipDistances() const;
			
			/// blending parameters
			void setBlend(BlendOp op, BlendFunc src, BlendFunc dest);
			void setBlendColor(BlendOp op, BlendFunc src, BlendFunc dest);
			void setBlendAlpha(BlendOp op, BlendFunc src, BlendFunc dest);
			void setBlend(uint32_t index, BlendOp op, BlendFunc src, BlendFunc dest);
			void setBlendColor(uint32_t index, BlendOp op, BlendFunc src, BlendFunc dest);
			void setBlendAlpha(uint32_t index, BlendOp op, BlendFunc src, BlendFunc dest);
			
			BlendOp getBlendColorOp(uint32_t index) const;
			BlendOp getBlendAlphaOp(uint32_t index) const;
			BlendFunc getBlendSrcColorFunc(uint32_t index) const;
			BlendFunc getBlendSrcAlphaFunc(uint32_t index) const;
			BlendFunc getBlendDestColorFunc(uint32_t index) const;
			BlendFunc getBlendDestAlphaFunc(uint32_t index) const;
			
			/// color parameters
			void setColorMask(ColorMask mask);
			void setColorMask(uint32_t index, ColorMask mask);
			void setColorFormat(uint32_t index, Format format);
			void setColorFormat(Format format, uint32_t num = 1);
			
			ColorMask getColorMask(uint32_t index) const;
			Format getColorFormat(uint32_t index) const;
			
			/// depth parameters
			void setDepthMask(DepthMask mask);
			void setDepthFunc(DepthFunc func);
			void setDepthFormat(Format format);
			
			DepthMask getDepthMask() const;
			DepthFunc getDepthFunc() const;
			Format getDepthFormat() const;
			
			/// stencil parameters
			void setStencilMask(uint32_t mask);
			void setStencilBackMask(uint32_t mask);
			void setStencilFrontMask(uint32_t mask);
			void setStencilFunc(StencilFunc func, StencilOp dpass_op);
			void setStencilBackFunc(StencilFunc func, StencilOp dpass_op);
			void setStencilFrontFunc(StencilFunc func, StencilOp dpass_op);
			void setStencilFunc(StencilFunc func, StencilOp fail_op, StencilOp dfail_op, StencilOp dpass_op);
			void setStencilBackFunc(StencilFunc func, StencilOp fail_op, StencilOp dfail_op, StencilOp dpass_op);
			void setStencilFrontFunc(StencilFunc func, StencilOp fail_op, StencilOp dfail_op, StencilOp dpass_op);
			
			uint32_t getStencilBackMask() const;
			StencilFunc getStencilBackFunc() const;
			StencilOp getStencilBackFailOp() const;
			StencilOp getStencilBackDepthFailOp() const;
			StencilOp getStencilBackDepthPassOp() const;
			
			uint32_t getStencilFrontMask() const;
			StencilFunc getStencilFrontFunc() const;
			StencilOp getStencilFrontFailOp() const;
			StencilOp getStencilFrontDepthFailOp() const;
			StencilOp getStencilFrontDepthPassOp() const;
	};
	
	/**
	 * The D3D12Pipeline class is a specialized graphics pipeline for Direct3D12, derived from the Pipeline class.
	 * It provides access to the native Direct3D12 root signature, enabling precise control over resource bindings and pipeline state in Direct3D12 rendering workflows.
	 */
	class TS_API D3D12Pipeline : public Pipeline {
			
			TS_DECLARE_PTR_1(D3D12Pipeline, Pipeline, 0)
			
		public:
			
			D3D12Pipeline();
			
			ID3D12RootSignature *getRootSignature() const;
	};
	
	/**
	 * The MTLPipeline class is a graphics pipeline implementation for Metal, inheriting from the Pipeline class.
	 * It supports indirect command buffer execution and provides access to the underlying Metal vertex and fragment functions.
	 */
	class TS_API MTLPipeline : public Pipeline {
			
			TS_DECLARE_PTR_1(MTLPipeline, Pipeline, 0)
			
		public:
			
			MTLPipeline();
			
			/// indirect command buffer
			void setIndirect(bool enabled);
			bool isIndirect() const;
			
			void *getVertexFunction() const;
			void *getFragmentFunction() const;
	};
	
	/**
	 * The FUPipeline class extends the Pipeline class to manage a fusion of multiple compute pipelines across different devices.
	 * It provides methods to set and retrieve a device mask, track the number of fused pipelines, and access individual pipelines within the fusion.
	 * This design is useful for high-performance computing workflows that require coordinated execution of rendering operations across multiple devices.
	 */
	class TS_API FUPipeline : public Pipeline {
			
			TS_DECLARE_PTR_1(FUPipeline, Pipeline, 0)
			
		public:
			
			FUPipeline();
			explicit FUPipeline(const Array<Pipeline> &pipelines, bool owner = false);
			
			/// device mask
			void setMask(uint32_t mask);
			uint32_t getMask() const;
			
			/// Fusion pipelines
			uint32_t getNumPipelines() const;
			const Pipeline getPipeline(uint32_t index) const;
			Pipeline getPipeline(uint32_t index);
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(Pipeline::ColorMask)
}

#endif /* __TELLUSIM_PLATFORM_PIPELINE_H__ */

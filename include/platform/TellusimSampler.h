// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLATFORM_SAMPLER_H__
#define __TELLUSIM_PLATFORM_SAMPLER_H__

#include <core/TellusimArray.h>
#include <math/TellusimColor.h>
#include <platform/TellusimPlatform.h>

/*
 */
namespace Tellusim {
	
	/**
	 * The Sampler class manages texture sampling parameters such as filter types, anisotropy, wrapping modes, level of detail (LOD), and border colors for texture mapping.
	 * It provides methods for setting and retrieving various sampling properties, including different filtering and wrapping strategies, anisotropic filtering, comparison functions, and reduction modes.
	 * The class also offers functionality to clear or create a sampler and check its creation status, which is essential for controlling the behavior of textures in rendering pipelines across different platforms and devices.
	 */
	class TS_API Sampler {
			
			TS_DECLARE_PTR_0(Sampler, 0)
			
		public:
			
			/// Filter types
			enum Filter {
				FilterPoint = 0,
				FilterLinear,
				FilterBipoint,
				FilterBilinear,
				FilterTrilinear,
				NumFilters,
			};
			
			/// Anisotropy range
			enum {
				MinAnisotropy = 1,
				MaxAnisotropy = 16,
			};
			
			/// Wrap modes
			enum WrapMode {
				WrapModeClamp = 0,
				WrapModeRepeat,
				WrapModeMirror,
				WrapModeBorder,
				NumWrapModes,
			};
			
			/// Compare functions
			enum CompareFunc {
				CompareFuncNone = 0,
				CompareFuncEqual,
				CompareFuncLess,
				CompareFuncGreater,
				CompareFuncNotEqual,
				CompareFuncLessEqual,
				CompareFuncGreaterEqual,
				NumCompareFunctions,
			};
			
			/// Reduction modes
			enum ReductionMode {
				ReductionModeAverage = 0,
				ReductionModeMin,
				ReductionModeMax,
				NumReductionModes,
			};
			
			Sampler();
			
			/// sampler platform
			Platform getPlatform() const;
			
			TS_INLINE const char *getPlatformName() const { return Tellusim::getPlatformName(getPlatform()); }
			
			/// sampler device index
			uint32_t getIndex() const;
			
			/// clear sampler
			void clear();
			
			/// check sampler
			bool isCreated() const;
			
			/// create sampler
			bool create();
			
			/// sampler parameters
			void setParameters(const Sampler &sampler);
			
			/// filter type
			void setFilter(Filter filter);
			Filter getFilter() const;
			bool isPointFilter() const;
			
			/// anisotropy level
			void setAnisotropy(uint32_t anisotropy);
			uint32_t getAnisotropy() const;
			bool hasAnisotropy() const;
			
			/// wrapping mode
			void setWrapMode(WrapMode mode);
			void setWrapMode(WrapMode mode_s, WrapMode mode_t, WrapMode mode_r);
			
			void setWrapModeS(WrapMode mode);
			WrapMode getWrapModeS() const;
			
			void setWrapModeT(WrapMode mode);
			WrapMode getWrapModeT() const;
			
			void setWrapModeR(WrapMode mode);
			WrapMode getWrapModeR() const;
			
			/// level of detail
			void setLod(float32_t min, float32_t max, float32_t bias);
			
			void setLodMin(float32_t min);
			float32_t getLodMin() const;
			
			void setLodMax(float32_t max);
			float32_t getLodMax() const;
			
			void setLodBias(float32_t bias);
			float32_t getLodBias() const;
			
			/// border color
			void setBorderColor(const Color &color);
			void setBorderColor(float32_t r, float32_t g, float32_t b, float32_t a);
			const Color &getBorderColor() const;
			
			/// compare func
			void setCompareFunc(CompareFunc func);
			CompareFunc getCompareFunc() const;
			
			/// reduction mode
			void setReductionMode(ReductionMode mode);
			ReductionMode getReductionMode() const;
	};
	
	/**
	 * The MTLSampler class extends the Sampler class and provides additional functionality specific to Metal, including support for indirect command buffers.
	 * It allows enabling or disabling the indirect command feature, which is useful for optimizing rendering commands and reducing CPU overhead.
	 */
	class TS_API MTLSampler : public Sampler {
			
			TS_DECLARE_PTR_1(MTLSampler, Sampler, 0)
			
		public:
			
			MTLSampler();
			
			/// indirect command buffer
			void setIndirect(bool enabled);
			bool isIndirect() const;
	};
	
	/**
	 * The FUSampler class extends the Sampler class to handle fusion samplers across multiple devices.
	 * It provides functionality for managing a device mask and accessing a collection of fusion samplers, making it useful in high-performance computing and multi-device workflows.
	 * The class allows querying the number of fusion samplers and provides methods to retrieve individual samplers from the fusion, enabling flexible sampling across different devices.
	 */
	class TS_API FUSampler : public Sampler {
			
			TS_DECLARE_PTR_1(FUSampler, Sampler, 0)
			
		public:
			
			FUSampler();
			explicit FUSampler(const Array<Sampler> &samplers, bool owner = false);
			
			/// device mask
			void setMask(uint32_t mask);
			uint32_t getMask() const;
			
			/// Fusion samplers
			uint32_t getNumSamplers() const;
			const Sampler getSampler(uint32_t index) const;
			Sampler getSampler(uint32_t index);
	};
}

#endif /* __TELLUSIM_PLATFORM_SAMPLER_H__ */

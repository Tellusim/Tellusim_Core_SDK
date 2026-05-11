// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GRAPHICS_CUBE_FILTER_H__
#define __TELLUSIM_GRAPHICS_CUBE_FILTER_H__

#include <TellusimTypes.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Buffer;
	class Texture;
	class Compute;
	class Device;
	
	/**
	 * The CubeFilter class provides GPU-based filtering operations for cube and panorama textures, enabling the generation and reconstruction of spherical harmonics.
	 * Filters can be created with specific parameters and dispatched using compute shaders, either to generate coefficient buffers from cube textures or to reconstruct filtered textures from coefficients.
	 */
	class TS_API CubeFilter {
			
			TS_DECLARE_PTR(CubeFilter, 0)
			
		public:
			
			/// Filter modes
			enum Mode {
				ModeCube = 0,
				ModePanorama,
				NumModes,
			};
			
			/// Filter flags
			enum Flags {
				FlagCube		= (1 << ModeCube),
				FlagPanorama	= (1 << ModePanorama),
				FlagsAll		= (FlagCube | FlagPanorama),
			};
			
			CubeFilter();
			
			/// clear filter
			void clear();
			
			/// check filter
			bool isCreated(Mode mode) const;
			
			/// filter parameters
			uint32_t getGroupSize() const;
			uint32_t getMaxOrder() const;
			uint32_t getMaxSize() const;
			uint32_t getHarmonics() const;
			
			/// create filter
			/// \param order Maximum filter order (2, 3, 5).
			/// \param size Maximum filter size.
			/// \param groups Reduction group size.
			bool create(const Device &device, Mode mode, uint32_t order = 3, uint32_t size = 1024, uint32_t groups = 256);
			bool create(const Device &device, Flags flags, uint32_t order = 3, uint32_t size = 1024, uint32_t groups = 256);
			
			/// dispatch cube filter
			/// \param buffer Destination coefficients buffer.
			/// \param offset Destination buffer offset.
			/// \param texture Source cube texture.
			/// \param slice Source texture slice.
			bool dispatch(Compute &compute, Buffer &buffer, uint32_t offset, Texture &texture, const Slice &slice) const;
			bool dispatch(Compute &compute, Buffer &buffer, uint32_t offset, Texture &texture) const;
			
			/// dispatch cube render
			/// \param texture Destination cube texture (RGBAf16).
			/// \param slice Destination texture slice.
			/// \param buffer Source coefficients buffer.
			/// \param offset Source buffer offset.
			bool dispatch(Compute &compute, Texture &texture, const Slice &slice, Buffer &buffer, uint32_t offset) const;
			bool dispatch(Compute &compute, Texture &texture, Buffer &buffer, uint32_t offset) const;
			
			/// dispatch cube mipmaps generation
			/// \param dest Destination cube texture (RGBAf16).
			/// \param src Source environment texture.
			/// \param dest_slice Destination texture slice.
			/// \param src_slice Source environment texture slice.
			bool dispatch(Compute &compute, Texture &dest, Texture &src, const Slice &dest_slice, const Slice &src_slice) const;
			bool dispatch(Compute &compute, Texture &dest, Texture &src, const Slice &src_slice) const;
			bool dispatch(Compute &compute, Texture &dest, Texture &src) const;
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(CubeFilter::Flags)
}

#endif /* __TELLUSIM_GRAPHICS_CUBE_FILTER_H__ */

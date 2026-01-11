// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GRAPHICS_ENCODER_ASTC_H__
#define __TELLUSIM_GRAPHICS_ENCODER_ASTC_H__

#include <TellusimTypes.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Texture;
	class Compute;
	class Device;
	
	/**
	 * The EncoderASTC class provides a compute-based interface for compressing textures into ASTC formats with support for 4x4, 5x4, and 5x5 block sizes in RGBAu8n format.
	 */
	class TS_API EncoderASTC {
			
			TS_DECLARE_PTR(EncoderASTC, 0)
			
		public:
			
			/// Encoder modes
			enum Mode {
				ModeASTC44RGBAu8n = 0,
				ModeASTC54RGBAu8n,
				ModeASTC55RGBAu8n,
				NumModes,
			};
			
			/// Encoder flags
			enum Flags {
				FlagNone = 0,
				FlagASTC44RGBAu8n	= (1 << ModeASTC44RGBAu8n),
				FlagASTC54RGBAu8n	= (1 << ModeASTC54RGBAu8n),
				FlagASTC55RGBAu8n	= (1 << ModeASTC55RGBAu8n),
				FlagCube			= (1 << (NumModes + 1)),
				FlagsAll			= (FlagASTC44RGBAu8n | FlagASTC54RGBAu8n | FlagASTC55RGBAu8n),
			};
			
			EncoderASTC();
			
			/// clear encoder
			void clear();
			
			/// check encoder
			bool isCreated(Mode mode) const;
			
			/// create encoder
			bool create(const Device &device, Mode mode);
			bool create(const Device &device, Flags flags);
			
			/// dispatch texture encoder
			/// \param mode Compression mode.
			/// \param dest Destination proxy texture.
			/// \param src Source texture to compress.
			/// \param dest_slice Destination texture slice.
			/// \param src_slice Source texture slice.
			/// \param components Number of components.
			bool dispatch(Compute &compute, Mode mode, Texture &dest, Texture &src, const Slice &dest_slice, const Slice &src_slice, uint32_t components = 4) const;
			bool dispatch(Compute &compute, Mode mode, Texture &dest, Texture &src, const Slice &src_slice, uint32_t components = 4) const;
			bool dispatch(Compute &compute, Mode mode, Texture &dest, Texture &src, uint32_t components = 4) const;
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(EncoderASTC::Flags)
}

#endif /* __TELLUSIM_GRAPHICS_ENCODER_ASTC_H__ */

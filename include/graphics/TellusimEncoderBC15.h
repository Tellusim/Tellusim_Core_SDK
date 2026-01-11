// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GRAPHICS_ENCODER_BC15_H__
#define __TELLUSIM_GRAPHICS_ENCODER_BC15_H__

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
	 * The EncoderBC15 class implements GPU-based texture compression using BC1-BC5 (S3TC) formats, supporting both color (RGB/RGBA) and single or dual-channel compression modes.
	 */
	class TS_API EncoderBC15 {
			
			TS_DECLARE_PTR(EncoderBC15, 0)
			
		public:
			
			/// Encoder modes
			enum Mode {
				ModeBC1RGBu8n = 0,
				ModeBC2RGBAu8n,
				ModeBC3RGBAu8n,
				ModeBC4Ru8n,
				ModeBC5RGu8n,
				NumModes,
			};
			
			/// Encoder flags
			enum Flags {
				FlagNone = 0,
				FlagBC1RGBu8n	= (1 << ModeBC1RGBu8n),
				FlagBC2RGBAu8n	= (1 << ModeBC2RGBAu8n),
				FlagBC3RGBAu8n	= (1 << ModeBC3RGBAu8n),
				FlagBC4Ru8n		= (1 << ModeBC4Ru8n),
				FlagBC5RGu8n	= (1 << ModeBC5RGu8n),
				FlagCube		= (1 << (NumModes + 1)),
				FlagsBC13		= (FlagBC1RGBu8n | FlagBC2RGBAu8n | FlagBC3RGBAu8n),
				FlagsBC45		= (FlagBC4Ru8n | FlagBC5RGu8n),
				FlagsAll		= (FlagsBC13 | FlagsBC45),
			};
			
			EncoderBC15();
			
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
			bool dispatch(Compute &compute, Mode mode, Texture &dest, Texture &src, const Slice &dest_slice, const Slice &src_slice) const;
			bool dispatch(Compute &compute, Mode mode, Texture &dest, Texture &src, const Slice &src_slice) const;
			bool dispatch(Compute &compute, Mode mode, Texture &dest, Texture &src) const;
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(EncoderBC15::Flags)
}

#endif /* __TELLUSIM_GRAPHICS_ENCODER_BC15_H__ */

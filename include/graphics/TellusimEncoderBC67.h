// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GRAPHICS_ENCODER_BC67_H__
#define __TELLUSIM_GRAPHICS_ENCODER_BC67_H__

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
	 * The EncoderBC67 class provides GPU-based texture compression using BC6H and BC7 formats, supporting high dynamic range (HDR) and standard color data encoding in both signed and unsigned formats.
	 */
	class TS_API EncoderBC67 {
			
			TS_DECLARE_PTR(EncoderBC67, 0)
			
		public:
			
			/// Encoder modes
			enum Mode {
				ModeBC6RGBf16s = 0,
				ModeBC6RGBf16u,
				ModeBC7RGBAu8n,
				NumModes,
			};
			
			/// Encoder flags
			enum Flags {
				FlagNone = 0,
				FlagBC6RGBf16s	= (1 << ModeBC6RGBf16s),
				FlagBC6RGBf16u	= (1 << ModeBC6RGBf16u),
				FlagBC7RGBAu8n	= (1 << ModeBC7RGBAu8n),
				FlagCube		= (1 << (NumModes + 1)),
				FlagsAll		= (FlagBC6RGBf16s | FlagBC6RGBf16u | FlagBC7RGBAu8n),
			};
			
			EncoderBC67();
			
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
	TS_DECLARE_ENUM_OP(EncoderBC67::Flags)
}

#endif /* __TELLUSIM_GRAPHICS_ENCODER_BC67_H__ */

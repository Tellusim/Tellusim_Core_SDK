// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GRAPHICS_DECODER_JPEG_H__
#define __TELLUSIM_GRAPHICS_DECODER_JPEG_H__

#include <platform/TellusimTexture.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Image;
	class Stream;
	class Compute;
	class Device;
	
	/**
	 * The DecoderJPEG class provides a GPU-accelerated JPEG decoding interface capable of converting JPEG images into textures.
	 */
	class TS_API DecoderJPEG {
			
			TS_DECLARE_PTR(DecoderJPEG, 0)
			
		public:
			
			/// Decoder modes
			enum Mode {
				ModeR = 0,
				ModeRG,
				ModeRGBA,
				ModeYUV444,
				ModeYUV422H,
				ModeYUV422V,
				ModeYUV420,
				NumModes,
			};
			
			/// Decoder flags
			enum Flags {
				FlagNone = 0,
				FlagR			= (1 << ModeR),
				FlagRG			= (1 << ModeRG),
				FlagRGBA		= (1 << ModeRGBA),
				FlagYUV444		= (1 << ModeYUV444),
				FlagYUV422H		= (1 << ModeYUV422H),
				FlagYUV422V		= (1 << ModeYUV422V),
				FlagYUV420		= (1 << ModeYUV420),
				FlagsAll		= (FlagR | FlagRG | FlagRGBA | FlagYUV444 | FlagYUV422H | FlagYUV422V | FlagYUV420),
			};
			
			DecoderJPEG();
			
			/// clear decoder
			void clear();
			
			/// check decoder
			bool isCreated(Mode mode) const;
			
			/// YUV444 mode performs inplace YUVtoRGB conversion
			TS_INLINE static bool isYUV(Mode mode) { return (mode > ModeYUV444 && mode <= ModeYUV420); }
			
			/// create decoder
			bool create(const Device &device, Mode mode);
			bool create(const Device &device, Flags flags);
			
			/// load decoder image
			/// \param name Image name
			/// \param image Decoder image.
			/// \param mode Decoding mode.
			/// \param size Decoding size.
			static bool load(const char *name, Image &image, Mode &mode, Size &size);
			static bool load(Stream &stream, Image &image, Mode &mode, Size &size);
			
			/// load texture from image
			/// \param device Device pointer.
			/// \param name Image name.
			/// \param flags Texture flags.
			Texture loadTexture(const Device &device, const char *name, Texture::Flags flags = Texture::DefaultFlags) const;
			Texture loadTexture(const Device &device, Stream &stream, Texture::Flags flags = Texture::DefaultFlags) const;
			
			/// dispatch decoder
			/// \param mode Decoder mode.
			/// \param dest Destination surface.
			/// \param src Source FFT surface.
			/// \param dest_slice Destination texture slice.
			/// \param src_slice Source texture slice.
			bool dispatch(Compute &compute, Mode mode, Texture &dest, Texture &src, const Slice &dest_slice, const Slice &src_slice) const;
			bool dispatch(Compute &compute, Mode mode, Texture &dest, Texture &src, const Slice &src_slice) const;
			bool dispatch(Compute &compute, Mode mode, Texture &dest, Texture &src) const;
			
			/// dispatch YUV converter
			/// \param mode Decoder mode.
			/// \param dest Destination surface.
			/// \param src Source YUV surface.
			/// \param dest_slice Destination texture slice.
			/// \param src_slice Source texture slice.
			bool dispatchYUV(Compute &compute, Mode mode, Texture &dest, Texture &src, const Slice &dest_slice, const Slice &src_slice) const;
			bool dispatchYUV(Compute &compute, Mode mode, Texture &dest, Texture &src, const Slice &src_slice) const;
			bool dispatchYUV(Compute &compute, Mode mode, Texture &dest, Texture &src) const;
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(DecoderJPEG::Flags)
}

#endif /* __TELLUSIM_GRAPHICS_DECODER_JPEG_H__ */

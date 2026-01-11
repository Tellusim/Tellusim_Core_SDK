// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PARALLEL_FOURIER_TRANSFORM_H__
#define __TELLUSIM_PARALLEL_FOURIER_TRANSFORM_H__

#include <TellusimTypes.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Async;
	class Texture;
	class Compute;
	class Device;
	
	/**
	 * The FourierTransform class provides a highly flexible and efficient implementation of the Fourier Transform, supporting a variety of input/output data formats and operations.
	 * It is designed for tasks such as signal processing, image processing, and simulations requiring complex transformations.
	 * The class supports different modes, such as interleaved, complex, and planar formats, along with various transform operations (forward and backward, real-to-complex and complex-to-real).
	 * It allows for the creation and dispatch of transformations on textures, enabling GPU-accelerated processing for large datasets.
	 * Additionally, the class offers flexibility in handling different data types and sizes, ensuring scalability across a range of applications.
	 */
	class TS_API FourierTransform {
			
			TS_DECLARE_PTR(FourierTransform, 0)
			
		public:
			
			/// Transform modes
			enum Mode {
				ModeRf16i = 0,	// one interleaved 16-bit per pixel component, texture format is FormatRGf16
				ModeRf32i,		// one interleaved 32-bit per pixel component, texture format is FormatRGf32
				ModeRGf16i,		// two interleaved 16-bit per pixel components, texture format is FormatRGBAf16
				ModeRGf32i,		// two interleaved 32-bit per pixel components, texture format is FormatRGBAf32
				ModeRGBf16c,	// three complex 16-bit per pixel components, texture format is FormatRGBAf32
				ModeRGBf21c,	// three complex 21-bit per pixel components, texture format is FormatRGBAf32
				ModeRGBf16p,	// three planar 16-bit per pixel components, texture format is FormatRGBAf16x2
				ModeRGBf32p,	// three planar 32-bit per pixel components, texture format is FormatRGBAf32x2
				NumModes,
			};
			
			/// Transform flags
			enum Flags {
				FlagNone = 0,
				FlagRf16i			= (1 << ModeRf16i),
				FlagRf32i			= (1 << ModeRf32i),
				FlagRGf16i			= (1 << ModeRGf16i),
				FlagRGf32i			= (1 << ModeRGf32i),
				FlagRGBf16c			= (1 << ModeRGBf16c),
				FlagRGBf21c			= (1 << ModeRGBf21c),
				FlagRGBf16p			= (1 << ModeRGBf16p),
				FlagRGBf32p			= (1 << ModeRGBf32p),
				FlagNpot			= (1 << NumModes),
				FlagsInterleaved	= (FlagRf16i | FlagRf32i | FlagRGf16i | FlagRGf32i),
				FlagsComplex		= (FlagRGBf16c | FlagRGBf21c),
				FlagsPlanar			= (FlagRGBf16p | FlagRGBf32p),
				FlagsAll			= (FlagsInterleaved | FlagsComplex | FlagsPlanar | FlagNpot),
			};
			
			/// Transform operations
			enum Operation {
				ForwardCtoC = 0,	// complex to complex forward transform
				BackwardCtoC,		// complex to complex backward transform
				ForwardRtoC,		// real to complex forward transform
				BackwardCtoR,		// complex to real backward transform
				NumOperations,
			};
			
			FourierTransform();
			
			/// clear transform
			void clear();
			
			/// check transform
			bool isCreated(Mode mode) const;
			bool isCreated(Flags flags) const;
			
			/// transform parameters
			uint32_t getMaxWidth() const;
			uint32_t getMaxHeight() const;
			uint32_t getAlignedSize(uint32_t size) const;
			
			/// create transform
			bool create(const Device &device, Mode mode, uint32_t width, uint32_t height, Async *async = nullptr);
			bool create(const Device &device, Flags flags, uint32_t width, uint32_t height, Async *async = nullptr);
			
			/// dispatch transform
			/// \param mode Transform mode.
			/// \param op Transform operation.
			/// \param dest Destination texture.
			/// \param src Source texture.
			bool dispatch(Compute &compute, Mode mode, Operation op, Texture &dest, Texture &src, const Slice &dest_slice, const Slice &src_slice) const;
			bool dispatch(Compute &compute, Mode mode, Operation op, Texture &dest, Texture &src, const Slice &src_slice) const;
			bool dispatch(Compute &compute, Mode mode, Operation op, Texture &dest, Texture &src) const;
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(FourierTransform::Flags)
}

#endif /* __TELLUSIM_PARALLEL_FOURIER_TRANSFORM_H__ */

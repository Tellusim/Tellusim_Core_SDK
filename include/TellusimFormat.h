// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_FORMAT_H__
#define __TELLUSIM_FORMAT_H__

#include <TellusimBase.h>

/*
 */
namespace Tellusim {
	
	/**
	 * The Format enum defines formats used for storing pixel data in different bit depths and layouts.\
	 * i - Signed integer\
	 * u - Unsigned integer\
	 * f - Floating point\
	 * n - Normalized (fixed-point mapped to [0, 1] or [-1, 1])\
	 * s - sRGB color space
	 */
	enum Format {
		
		FormatUnknown = 0,
		
		/// 8-bit per pixel formats
		FormatRi8, FormatRu8, FormatRi8n, FormatRu8n,
		FormatRGi8, FormatRGu8, FormatRGi8n, FormatRGu8n,
		FormatRGBi8, FormatRGBu8, FormatRGBi8n, FormatRGBu8n, FormatRGBu8ns,
		FormatRGBAi8, FormatRGBAu8, FormatRGBAi8n, FormatRGBAu8n, FormatRGBAu8ns,
		FormatBGRAu8n, FormatBGRAu8ns,
		
		/// 16-bit per pixel formats
		FormatRi16, FormatRu16, FormatRi16n, FormatRu16n, FormatRf16,
		FormatRGi16, FormatRGu16, FormatRGi16n, FormatRGu16n, FormatRGf16,
		FormatRGBi16, FormatRGBu16, FormatRGBi16n, FormatRGBu16n, FormatRGBf16,
		FormatRGBAi16, FormatRGBAu16, FormatRGBAi16n, FormatRGBAu16n, FormatRGBAf16,
		
		/// 32-bit per pixel formats
		FormatRi32, FormatRu32, FormatRf32,
		FormatRGi32, FormatRGu32, FormatRGf32,
		FormatRGBi32, FormatRGBu32, FormatRGBf32,
		FormatRGBAi32, FormatRGBAu32, FormatRGBAf32,
		
		/// 64-bit per pixel formats
		FormatRi64, FormatRu64, FormatRf64,
		FormatRGi64, FormatRGu64, FormatRGf64,
		FormatRGBi64, FormatRGBu64, FormatRGBf64,
		FormatRGBAi64, FormatRGBAu64, FormatRGBAf64,
		
		/// mixed formats
		FormatRGBAu4n, FormatRGBu5Au1n, FormatRu5Gu6Bu5n,
		FormatRGBu10Au2, FormatRGBu10Au2n,
		FormatRGf11Bf10, FormatRGBf9Eu5, FormatRGBf21,
		
		/// block formats
		FormatBC1RGBu8n, FormatBC1RGBu8ns,
		FormatBC1RGBAu8n, FormatBC1RGBAu8ns,
		FormatBC2RGBAu8n, FormatBC2RGBAu8ns,
		FormatBC3RGBAu8n, FormatBC3RGBAu8ns,
		
		FormatBC4Ri8n, FormatBC4Ru8n,
		FormatBC5RGi8n, FormatBC5RGu8n,
		FormatBC6RGBf16s, FormatBC6RGBf16u,
		FormatBC7RGBAu8n, FormatBC7RGBAu8ns,
		
		/// etc2 block formats
		FormatEACRi8n, FormatEACRu8n,
		FormatEACRGi8n, FormatEACRGu8n,
		FormatETC2RGBu8n, FormatETC2RGBu8ns,
		FormatETC2RGBAu8n, FormatETC2RGBAu8ns,
		FormatETC2RGBu8Au1n, FormatETC2RGBu8Au1ns,
		
		/// astc block formats
		FormatASTC44RGBAu8n, FormatASTC44RGBAu8ns, FormatASTC44RGBAf16,
		FormatASTC54RGBAu8n, FormatASTC54RGBAu8ns, FormatASTC54RGBAf16,
		FormatASTC55RGBAu8n, FormatASTC55RGBAu8ns, FormatASTC55RGBAf16,
		FormatASTC65RGBAu8n, FormatASTC65RGBAu8ns, FormatASTC65RGBAf16,
		FormatASTC66RGBAu8n, FormatASTC66RGBAu8ns, FormatASTC66RGBAf16,
		FormatASTC85RGBAu8n, FormatASTC85RGBAu8ns, FormatASTC85RGBAf16,
		FormatASTC86RGBAu8n, FormatASTC86RGBAu8ns, FormatASTC86RGBAf16,
		FormatASTC88RGBAu8n, FormatASTC88RGBAu8ns, FormatASTC88RGBAf16,
		
		/// depth formats
		FormatDu16, FormatDu16Su8,
		FormatDu24, FormatDu24Su8,
		FormatDf32, FormatDf32Su8,
		
		NumFormats,
	};
	
	/// format literal name
	TS_API const char *getFormatName(Format format);
	TS_API Format findFormatName(const char *name);
	
	/// GLSL format literal name
	TS_API const char *getGLSLFormatName(Format format);
	TS_API Format findGLSLFormatName(const char *name);
	
	/// format type
	TS_API bool isColorFormat(Format format);
	TS_API bool isDepthFormat(Format format);
	TS_API bool isPixelFormat(Format format);
	TS_API bool isPlainFormat(Format format);
	TS_API bool isMixedFormat(Format format);
	TS_API bool isBlockFormat(Format format);
	TS_API bool isStencilFormat(Format format);
	TS_API Format toPixelFormat(Format format);
	
	TS_API bool isNormFormat(Format format);
	TS_API bool isSRGBFormat(Format format);
	TS_API bool isSignedFormat(Format format);
	TS_API bool isUnsignedFormat(Format format);
	TS_API bool isIntegerFormat(Format format);
	TS_API bool isFloatFormat(Format format);
	TS_API Format toNormFormat(Format format);
	TS_API Format toSRGBFormat(Format format);
	TS_API Format toSignedFormat(Format format);
	TS_API Format toUnsignedFormat(Format format);
	TS_API Format toFloatFormat(Format format);
	
	TS_API bool isi8Format(Format format);
	TS_API bool isu8Format(Format format);
	TS_API bool is8BitFormat(Format format);
	TS_API Format to8BitFormat(Format format);
	
	TS_API bool isi16Format(Format format);
	TS_API bool isu16Format(Format format);
	TS_API bool isf16Format(Format format);
	TS_API bool is16BitFormat(Format format);
	TS_API Format to16BitFormat(Format format);
	
	TS_API bool isi32Format(Format format);
	TS_API bool isu32Format(Format format);
	TS_API bool isf32Format(Format format);
	TS_API bool is32BitFormat(Format format);
	TS_API Format to32BitFormat(Format format);
	
	TS_API bool isi64Format(Format format);
	TS_API bool isu64Format(Format format);
	TS_API bool isf64Format(Format format);
	TS_API bool is64BitFormat(Format format);
	
	TS_API bool isBC15Format(Format format);
	TS_API bool isBC67Format(Format format);
	TS_API bool isETC2Format(Format format);
	TS_API bool isASTCFormat(Format format);
	
	/// format components
	TS_API uint32_t getFormatComponents(Format format);
	TS_API Format toFormatComponents(Format format, uint32_t components);
	
	/// format size
	TS_API uint32_t getFormatPixelSize(Format format);
	TS_API uint32_t getFormatBlockSize(Format format);
	TS_API uint32_t getFormatBlockWidth(Format format);
	TS_API uint32_t getFormatBlockHeight(Format format);
	
	/// pixel sampler
	TS_API uint32_t getPixelFormatValue(Format format, float32_t value[4], const void *src, uint32_t stride = 0);
	TS_API uint32_t setPixelFormatValue(Format format, void *dest, const float32_t value[4], uint32_t stride = 0);
}

#endif /* __TELLUSIM_FORMAT_H__ */

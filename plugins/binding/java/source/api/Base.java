// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;

/*
 */
public class Base extends BaseGlobal {
	
	public static String getPlatformName(Platform platform) { return get_platform_name(platform.value); }
	public static String getPlatformName(Platform.Enum platform) { return get_platform_name(platform.value); }
	public static Platform findPlatformName(String name) { return new Platform(find_platform_name(name)); }
	public static boolean isPlatformAvailable(Platform platform) { return is_platform_available(platform.value); }
	public static boolean isPlatformAvailable(Platform.Enum platform) { return is_platform_available(platform.value); }
	public static String getFormatName(Format format) { return get_format_name(format.value); }
	public static String getFormatName(Format.Enum format) { return get_format_name(format.value); }
	public static Format findFormatName(String name) { return new Format(find_format_name(name)); }
	public static String getGLSLFormatName(Format format) { return get_glsl_format_name(format.value); }
	public static String getGLSLFormatName(Format.Enum format) { return get_glsl_format_name(format.value); }
	public static Format findGLSLFormatName(String name) { return new Format(find_glsl_format_name(name)); }
	public static boolean isColorFormat(Format format) { return is_color_format(format.value); }
	public static boolean isColorFormat(Format.Enum format) { return is_color_format(format.value); }
	public static boolean isDepthFormat(Format format) { return is_depth_format(format.value); }
	public static boolean isDepthFormat(Format.Enum format) { return is_depth_format(format.value); }
	public static boolean isPixelFormat(Format format) { return is_pixel_format(format.value); }
	public static boolean isPixelFormat(Format.Enum format) { return is_pixel_format(format.value); }
	public static boolean isPlainFormat(Format format) { return is_plain_format(format.value); }
	public static boolean isPlainFormat(Format.Enum format) { return is_plain_format(format.value); }
	public static boolean isMixedFormat(Format format) { return is_mixed_format(format.value); }
	public static boolean isMixedFormat(Format.Enum format) { return is_mixed_format(format.value); }
	public static boolean isBlockFormat(Format format) { return is_block_format(format.value); }
	public static boolean isBlockFormat(Format.Enum format) { return is_block_format(format.value); }
	public static boolean isStencilFormat(Format format) { return is_stencil_format(format.value); }
	public static boolean isStencilFormat(Format.Enum format) { return is_stencil_format(format.value); }
	public static Format toPixelFormat(Format format) { return new Format(to_pixel_format(format.value)); }
	public static Format toPixelFormat(Format.Enum format) { return new Format(to_pixel_format(format.value)); }
	public static boolean isNormFormat(Format format) { return is_norm_format(format.value); }
	public static boolean isNormFormat(Format.Enum format) { return is_norm_format(format.value); }
	public static boolean isSRGBFormat(Format format) { return is_srgb_format(format.value); }
	public static boolean isSRGBFormat(Format.Enum format) { return is_srgb_format(format.value); }
	public static boolean isSignedFormat(Format format) { return is_signed_format(format.value); }
	public static boolean isSignedFormat(Format.Enum format) { return is_signed_format(format.value); }
	public static boolean isUnsignedFormat(Format format) { return is_unsigned_format(format.value); }
	public static boolean isUnsignedFormat(Format.Enum format) { return is_unsigned_format(format.value); }
	public static boolean isIntegerFormat(Format format) { return is_integer_format(format.value); }
	public static boolean isIntegerFormat(Format.Enum format) { return is_integer_format(format.value); }
	public static boolean isFloatFormat(Format format) { return is_float_format(format.value); }
	public static boolean isFloatFormat(Format.Enum format) { return is_float_format(format.value); }
	public static Format toNormFormat(Format format) { return new Format(to_norm_format(format.value)); }
	public static Format toNormFormat(Format.Enum format) { return new Format(to_norm_format(format.value)); }
	public static Format toSRGBFormat(Format format) { return new Format(to_srgb_format(format.value)); }
	public static Format toSRGBFormat(Format.Enum format) { return new Format(to_srgb_format(format.value)); }
	public static Format toSignedFormat(Format format) { return new Format(to_signed_format(format.value)); }
	public static Format toSignedFormat(Format.Enum format) { return new Format(to_signed_format(format.value)); }
	public static Format toUnsignedFormat(Format format) { return new Format(to_unsigned_format(format.value)); }
	public static Format toUnsignedFormat(Format.Enum format) { return new Format(to_unsigned_format(format.value)); }
	public static Format toFloatFormat(Format format) { return new Format(to_float_format(format.value)); }
	public static Format toFloatFormat(Format.Enum format) { return new Format(to_float_format(format.value)); }
	public static boolean isi8Format(Format format) { return isi8_format(format.value); }
	public static boolean isi8Format(Format.Enum format) { return isi8_format(format.value); }
	public static boolean isu8Format(Format format) { return isu8_format(format.value); }
	public static boolean isu8Format(Format.Enum format) { return isu8_format(format.value); }
	public static boolean is8BitFormat(Format format) { return is8_bit_format(format.value); }
	public static boolean is8BitFormat(Format.Enum format) { return is8_bit_format(format.value); }
	public static Format to8BitFormat(Format format) { return new Format(to8_bit_format(format.value)); }
	public static Format to8BitFormat(Format.Enum format) { return new Format(to8_bit_format(format.value)); }
	public static boolean isi16Format(Format format) { return isi16_format(format.value); }
	public static boolean isi16Format(Format.Enum format) { return isi16_format(format.value); }
	public static boolean isu16Format(Format format) { return isu16_format(format.value); }
	public static boolean isu16Format(Format.Enum format) { return isu16_format(format.value); }
	public static boolean isf16Format(Format format) { return isf16_format(format.value); }
	public static boolean isf16Format(Format.Enum format) { return isf16_format(format.value); }
	public static boolean is16BitFormat(Format format) { return is16_bit_format(format.value); }
	public static boolean is16BitFormat(Format.Enum format) { return is16_bit_format(format.value); }
	public static Format to16BitFormat(Format format) { return new Format(to16_bit_format(format.value)); }
	public static Format to16BitFormat(Format.Enum format) { return new Format(to16_bit_format(format.value)); }
	public static boolean isi32Format(Format format) { return isi32_format(format.value); }
	public static boolean isi32Format(Format.Enum format) { return isi32_format(format.value); }
	public static boolean isu32Format(Format format) { return isu32_format(format.value); }
	public static boolean isu32Format(Format.Enum format) { return isu32_format(format.value); }
	public static boolean isf32Format(Format format) { return isf32_format(format.value); }
	public static boolean isf32Format(Format.Enum format) { return isf32_format(format.value); }
	public static boolean is32BitFormat(Format format) { return is32_bit_format(format.value); }
	public static boolean is32BitFormat(Format.Enum format) { return is32_bit_format(format.value); }
	public static Format to32BitFormat(Format format) { return new Format(to32_bit_format(format.value)); }
	public static Format to32BitFormat(Format.Enum format) { return new Format(to32_bit_format(format.value)); }
	public static boolean isi64Format(Format format) { return isi64_format(format.value); }
	public static boolean isi64Format(Format.Enum format) { return isi64_format(format.value); }
	public static boolean isu64Format(Format format) { return isu64_format(format.value); }
	public static boolean isu64Format(Format.Enum format) { return isu64_format(format.value); }
	public static boolean isf64Format(Format format) { return isf64_format(format.value); }
	public static boolean isf64Format(Format.Enum format) { return isf64_format(format.value); }
	public static boolean is64BitFormat(Format format) { return is64_bit_format(format.value); }
	public static boolean is64BitFormat(Format.Enum format) { return is64_bit_format(format.value); }
	public static boolean isBC15Format(Format format) { return is_bc15_format(format.value); }
	public static boolean isBC15Format(Format.Enum format) { return is_bc15_format(format.value); }
	public static boolean isBC67Format(Format format) { return is_bc67_format(format.value); }
	public static boolean isBC67Format(Format.Enum format) { return is_bc67_format(format.value); }
	public static boolean isETC2Format(Format format) { return is_etc2_format(format.value); }
	public static boolean isETC2Format(Format.Enum format) { return is_etc2_format(format.value); }
	public static boolean isASTCFormat(Format format) { return is_astc_format(format.value); }
	public static boolean isASTCFormat(Format.Enum format) { return is_astc_format(format.value); }
	public static int getFormatComponents(Format format) { return get_format_components(format.value); }
	public static int getFormatComponents(Format.Enum format) { return get_format_components(format.value); }
	public static Format toFormatComponents(Format format, int components) { return new Format(to_format_components(format.value, components)); }
	public static Format toFormatComponents(Format.Enum format, int components) { return new Format(to_format_components(format.value, components)); }
	public static int getFormatPixelSize(Format format) { return get_format_pixel_size(format.value); }
	public static int getFormatPixelSize(Format.Enum format) { return get_format_pixel_size(format.value); }
	public static int getFormatBlockSize(Format format) { return get_format_block_size(format.value); }
	public static int getFormatBlockSize(Format.Enum format) { return get_format_block_size(format.value); }
	public static int getFormatBlockWidth(Format format) { return get_format_block_width(format.value); }
	public static int getFormatBlockWidth(Format.Enum format) { return get_format_block_width(format.value); }
	public static int getFormatBlockHeight(Format format) { return get_format_block_height(format.value); }
	public static int getFormatBlockHeight(Format.Enum format) { return get_format_block_height(format.value); }
	public static int getPixelFormatValue(Format format, long value, long src) { return get_pixel_format_value(format.value, value, src, 0); }
	public static int getPixelFormatValue(Format.Enum format, long value, long src) { return get_pixel_format_value(format.value, value, src, 0); }
	public static int getPixelFormatValue(Format format, long value, long src, int stride) { return get_pixel_format_value(format.value, value, src, stride); }
	public static int getPixelFormatValue(Format.Enum format, long value, long src, int stride) { return get_pixel_format_value(format.value, value, src, stride); }
	public static int setPixelFormatValue(Format format, long dest, long value) { return set_pixel_format_value(format.value, dest, value, 0); }
	public static int setPixelFormatValue(Format.Enum format, long dest, long value) { return set_pixel_format_value(format.value, dest, value, 0); }
	public static int setPixelFormatValue(Format format, long dest, long value, int stride) { return set_pixel_format_value(format.value, dest, value, stride); }
	public static int setPixelFormatValue(Format.Enum format, long dest, long value, int stride) { return set_pixel_format_value(format.value, dest, value, stride); }
	
	private static native String get_platform_name(int platform);
	private static native int find_platform_name(String name);
	private static native boolean is_platform_available(int platform);
	private static native String get_format_name(int format);
	private static native int find_format_name(String name);
	private static native String get_glsl_format_name(int format);
	private static native int find_glsl_format_name(String name);
	private static native boolean is_color_format(int format);
	private static native boolean is_depth_format(int format);
	private static native boolean is_pixel_format(int format);
	private static native boolean is_plain_format(int format);
	private static native boolean is_mixed_format(int format);
	private static native boolean is_block_format(int format);
	private static native boolean is_stencil_format(int format);
	private static native int to_pixel_format(int format);
	private static native boolean is_norm_format(int format);
	private static native boolean is_srgb_format(int format);
	private static native boolean is_signed_format(int format);
	private static native boolean is_unsigned_format(int format);
	private static native boolean is_integer_format(int format);
	private static native boolean is_float_format(int format);
	private static native int to_norm_format(int format);
	private static native int to_srgb_format(int format);
	private static native int to_signed_format(int format);
	private static native int to_unsigned_format(int format);
	private static native int to_float_format(int format);
	private static native boolean isi8_format(int format);
	private static native boolean isu8_format(int format);
	private static native boolean is8_bit_format(int format);
	private static native int to8_bit_format(int format);
	private static native boolean isi16_format(int format);
	private static native boolean isu16_format(int format);
	private static native boolean isf16_format(int format);
	private static native boolean is16_bit_format(int format);
	private static native int to16_bit_format(int format);
	private static native boolean isi32_format(int format);
	private static native boolean isu32_format(int format);
	private static native boolean isf32_format(int format);
	private static native boolean is32_bit_format(int format);
	private static native int to32_bit_format(int format);
	private static native boolean isi64_format(int format);
	private static native boolean isu64_format(int format);
	private static native boolean isf64_format(int format);
	private static native boolean is64_bit_format(int format);
	private static native boolean is_bc15_format(int format);
	private static native boolean is_bc67_format(int format);
	private static native boolean is_etc2_format(int format);
	private static native boolean is_astc_format(int format);
	private static native int get_format_components(int format);
	private static native int to_format_components(int format, int components);
	private static native int get_format_pixel_size(int format);
	private static native int get_format_block_size(int format);
	private static native int get_format_block_width(int format);
	private static native int get_format_block_height(int format);
	private static native int get_pixel_format_value(int format, long value, long src, int stride);
	private static native int set_pixel_format_value(int format, long dest, long value, int stride);
}

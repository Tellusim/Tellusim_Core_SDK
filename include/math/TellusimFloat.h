// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_MATH_FLOAT_H__
#define __TELLUSIM_MATH_FLOAT_H__

#include <math/TellusimScalar.h>

/*
 */
namespace Tellusim {
	
	/**
	 * 32-bit floating-point as integer
	 */
	union f32u32 {
		
		explicit f32u32(float32_t f) : f(f) { }
		explicit f32u32(uint32_t u) : u(u) { }
		explicit f32u32(int32_t i) : i(i) { }
		
		/// access to number
		TS_INLINE uint32_t exponent() const { return (u & 0x7f800000u) >> 23u; }
		TS_INLINE uint32_t mantissa() const { return (u & 0x007fffffu); }
		
		float32_t f;
		uint32_t u;
		int32_t i;
	};
	
	/**
	 * 64-bit floating-point as integer
	 */
	union f64u64 {
		
		explicit f64u64(float64_t f) : f(f) { }
		explicit f64u64(uint64_t u) : u(u) { }
		explicit f64u64(int64_t i) : i(i) { }
		
		/// access to number
		TS_INLINE uint64_t exponent() const { return (u & 0x7ff0000000000000ull) >> 52ull; }
		TS_INLINE uint64_t mantissa() const { return (u & 0x000fffffffffffffull); }
		
		float64_t f;
		uint64_t u;
		int64_t i;
	};
	
	/**
	 * 16-bit floating-point number class
	 * mantissa bits 10, exponent bits 5
	 * strict conversion is performed by default
	 */
	struct float16_t final {
		
		float16_t() { }
		explicit float16_t(uint16_t u) : bits(u) { }
		explicit float16_t(float32_t f) { set(f); }
		explicit float16_t(float64_t f) { set((float32_t)f); }
		
		/// handle normal, denormal, infinity and NaN cases
		TS_API void set(float32_t f);
		TS_API float32_t get() const;
		
		/// handle normal cases only
		TS_API void setFast(float32_t f);
		TS_API float32_t getFast() const;
		
		/// conversion to numbers
		TS_INLINE operator uint16_t() const { return bits; }
		TS_INLINE operator float32_t() const { return get(); }
		TS_INLINE operator float64_t() const { return get(); }
		
		/// conversion from numbers
		TS_INLINE float16_t &operator=(uint16_t u) { bits = u; return *this; }
		TS_INLINE float16_t &operator=(float32_t f) { set(f); return *this; }
		TS_INLINE float16_t &operator=(float16_t f) { bits = f.bits; return *this; }
		
		/// access to number
		TS_INLINE uint16_t exponent() const { return (bits & 0x7c00u) >> 10; }
		TS_INLINE uint16_t mantissa() const { return (bits & 0x03ffu); }
		
		uint16_t bits;
		
		/// constant values
		TS_API static const float16_t zero;
		TS_API static const float16_t half;
		TS_API static const float16_t one;
		TS_API static const float16_t two;
	};
	
	/**
	 * 21-bit floating-point number class
	 * mantissa bits 14, exponent bits 6
	 * strict conversion is performed by default
	 */
	struct float21_t final {
		
		float21_t() { }
		explicit float21_t(uint32_t u) : bits(u) { }
		explicit float21_t(float32_t f) { set(f); }
		explicit float21_t(float64_t f) { set((float32_t)f); }
		
		/// handle normal, denormal, infinity and NaN cases
		TS_API void set(float32_t f);
		TS_API float32_t get() const;
		
		/// handle normal cases only
		TS_API void setFast(float32_t f);
		TS_API float32_t getFast() const;
		
		/// conversion to numbers
		TS_INLINE operator uint32_t() const { return bits; }
		TS_INLINE operator float32_t() const { return get(); }
		TS_INLINE operator float64_t() const { return get(); }
		
		/// conversion from numbers
		TS_INLINE float21_t &operator=(uint32_t u) { bits = u; return *this; }
		TS_INLINE float21_t &operator=(float32_t f) { set(f); return *this; }
		TS_INLINE float21_t &operator=(float21_t f) { bits = f.bits; return *this; }
		
		/// access to number
		TS_INLINE uint32_t exponent() const { return (bits & 0xfc000u) >> 14; }
		TS_INLINE uint32_t mantissa() const { return (bits & 0x03fffu); }
		
		uint32_t bits;
		
		/// constant values
		TS_API static const float21_t zero;
		TS_API static const float21_t half;
		TS_API static const float21_t one;
		TS_API static const float21_t two;
	};
	
	/**
	 * 24-bit floating-point number class
	 * mantissa bits 17, exponent bits 6
	 * strict conversion is performed by default
	 */
	struct float24_t final {
		
		float24_t() { }
		explicit float24_t(uint32_t u) : bits(u) { }
		explicit float24_t(float32_t f) { set(f); }
		explicit float24_t(float64_t f) { set((float32_t)f); }
		
		/// handle normal, denormal, infinity and NaN cases
		TS_API void set(float32_t f);
		TS_API float32_t get() const;
		
		/// handle normal cases only
		TS_API void setFast(float32_t f);
		TS_API float32_t getFast() const;
		
		/// conversion to numbers
		TS_INLINE operator uint32_t() const { return bits; }
		TS_INLINE operator float32_t() const { return get(); }
		TS_INLINE operator float64_t() const { return get(); }
		
		/// conversion from numbers
		TS_INLINE float24_t &operator=(uint32_t u) { bits = u; return *this; }
		TS_INLINE float24_t &operator=(float32_t f) { set(f); return *this; }
		TS_INLINE float24_t &operator=(float24_t f) { bits = f.bits; return *this; }
		
		/// access to number
		TS_INLINE uint32_t exponent() const { return (bits & 0x7e0000u) >> 17; }
		TS_INLINE uint32_t mantissa() const { return (bits & 0x01ffffu); }
		
		uint32_t bits;
		
		/// constant values
		TS_API static const float24_t zero;
		TS_API static const float24_t half;
		TS_API static const float24_t one;
		TS_API static const float24_t two;
	};
	
	/**
	 * 16-bit floating-point numbers
	 */
	TS_INLINE bool isFinite(float16_t f) { return (f.exponent() < 31); }
	TS_INLINE bool isNormal(float16_t f) { uint16_t e = f.exponent(); return (e > 0 && e < 31); }
	TS_INLINE bool isInf(float16_t f) { return (f.exponent() == 31 && f.mantissa() == 0); }
	TS_INLINE bool isNan(float16_t f) { return (f.exponent() == 31 && f.mantissa() != 0); }
	
	/**
	 * 21-bit floating-point numbers
	 */
	TS_INLINE bool isFinite(float21_t f) { return (f.exponent() < 63); }
	TS_INLINE bool isNormal(float21_t f) { uint32_t e = f.exponent(); return (e > 0 && e < 63); }
	TS_INLINE bool isInf(float21_t f) { return (f.exponent() == 63 && f.mantissa() == 0); }
	TS_INLINE bool isNan(float21_t f) { return (f.exponent() == 63 && f.mantissa() != 0); }
	
	/**
	 * 24-bit floating-point numbers
	 */
	TS_INLINE bool isFinite(float24_t f) { return (f.exponent() < 63); }
	TS_INLINE bool isNormal(float24_t f) { uint32_t e = f.exponent(); return (e > 0 && e < 63); }
	TS_INLINE bool isInf(float24_t f) { return (f.exponent() == 63 && f.mantissa() == 0); }
	TS_INLINE bool isNan(float24_t f) { return (f.exponent() == 63 && f.mantissa() != 0); }
	
	/**
	 * 32-bit floating-point numbers
	 */
	TS_INLINE bool isFinite(float32_t f) { return (f32u32(f).exponent() < 255); }
	TS_INLINE bool isNormal(float32_t f) { uint32_t e = f32u32(f).exponent(); return (e > 0 && e < 255); }
	TS_INLINE bool isInf(float32_t f) { return (f32u32(f).exponent() == 255 && f32u32(f).mantissa() == 0); }
	TS_INLINE bool isNan(float32_t f) { return (f32u32(f).exponent() == 255 && f32u32(f).mantissa() != 0); }
	
	/**
	 * 64-bit floating-point numbers
	 */
	TS_INLINE bool isFinite(float64_t f) { return (f64u64(f).exponent() < 2047); }
	TS_INLINE bool isNormal(float64_t f) { uint64_t e = f64u64(f).exponent(); return (e > 0 && e < 2047); }
	TS_INLINE bool isInf(float64_t f) { return (f64u64(f).exponent() == 2047 && f64u64(f).mantissa() == 0); }
	TS_INLINE bool isNan(float64_t f) { return (f64u64(f).exponent() == 2047 && f64u64(f).mantissa() != 0); }
	
	/**
	 * 32-bit floating-point numbers with error is less than 1.2e-2
	 */
	TS_API float32_t rsqrtFast(float32_t x);
	TS_API float32_t rcbrtFast(float32_t x);
	TS_API float32_t powFast(float32_t x, float32_t p);
	
	/**
	 * fast sin/cos approximation with error is less than 1.4e-6
	 */
	TS_API float32_t sinFast(float32_t x);
	TS_API float32_t cosFast(float32_t x);
	TS_API void sincosFast(float32_t x, float32_t &s, float32_t &c);
	
	/* fast asin/acos approximation with error is less than 4.3e-6
	 */
	TS_API float32_t asinFast(float32_t x);
	TS_API float32_t acosFast(float32_t x);
	
	/* fast atan approximation with error is less than 1.1e-5
	 */
	TS_API float32_t atanFast(float32_t x);
	TS_API float32_t atan2Fast(float32_t y, float32_t x);
}

#endif /* __TELLUSIM_MATH_FLOAT_H__ */

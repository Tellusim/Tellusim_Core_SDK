// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_ENDIAN_H__
#define __TELLUSIM_CORE_ENDIAN_H__

#include <TellusimBase.h>

/*
 */
namespace Tellusim {
	
	/**
	 * 16-bit integer swaps
	 */
	TS_INLINE int16_t swapEndian(int16_t value) {
		return ((value << 8) & 0xff00) | ((value >> 8) & 0x00ff);
	}
	
	TS_INLINE uint16_t swapEndian(uint16_t value) {
		return ((value << 8) & 0xff00u) | ((value >> 8) & 0x00ffu);
	}
	
	/**
	 * 32-bit integer swaps
	 */
	TS_INLINE int32_t swapEndian(int32_t value) {
		value = ((value << 8) & 0xff00ff00) | ((value >>  8) & 0x00ff00ff);
		return ((value << 16) & 0xffff0000) | ((value >> 16) & 0x0000ffff);
	}
	
	TS_INLINE uint32_t swapEndian(uint32_t value) {
		value = ((value << 8) & 0xff00ff00u) | ((value >>  8) & 0x00ff00ffu);
		return ((value << 16) & 0xffff0000u) | ((value >> 16) & 0x0000ffffu);
	}
	
	/**
	 * 64-bit integer swaps
	 */
	TS_INLINE int64_t swapEndian(int64_t value) {
		value = ((value <<  8) & 0xff00ff00ff00ff00ll) | ((value >>  8) & 0x00ff00ff00ff00ffll);
		value = ((value << 16) & 0xffff0000ffff0000ll) | ((value >> 16) & 0x0000ffff0000ffffll);
		return  ((value << 32) & 0xffffffff00000000ll) | ((value >> 32) & 0x00000000ffffffffll);
	}
	
	TS_INLINE uint64_t swapEndian(uint64_t value) {
		value = ((value <<  8) & 0xff00ff00ff00ff00ull) | ((value >>  8) & 0x00ff00ff00ff00ffull);
		value = ((value << 16) & 0xffff0000ffff0000ull) | ((value >> 16) & 0x0000ffff0000ffffull);
		return  ((value << 32) & 0xffffffff00000000ull) | ((value >> 32) & 0x00000000ffffffffull);
	}
	
	/**
	 * floating-point swaps
	 */
	TS_INLINE float32_t swapEndian(float32_t value) {
		union f32u32 {
			f32u32(float32_t f) : f(f) { }
			f32u32(uint32_t u) : u(u) { }
			float32_t f;
			uint32_t u;
		};
		return f32u32(swapEndian(f32u32(value).u)).f;
	}
	
	TS_INLINE float64_t swapEndian(float64_t value) {
		union f64u64 {
			f64u64(float64_t f) : f(f) { }
			f64u64(uint64_t u) : u(u) { }
			float64_t f;
			uint64_t u;
		};
		return f64u64(swapEndian(f64u64(value).u)).f;
	}
	
	/**
	 * convert endianness
	 */
	#if TS_BIG_ENDIAN
		
		template <class Type> TS_INLINE Type bigEndian(Type value) { return value; }
		template <class Type> TS_INLINE Type littleEndian(Type value) { return swapEndian(value); }
		
		template <class Type> TS_INLINE void bigEndian(Type *data, size_t size) { }
		template <class Type> TS_INLINE void littleEndian(Type *data, size_t size) {
			for(size_t i = 0; i < size; i++) {
				data[i] = swapEndian(data[i]);
			}
		}
		
	#else
		
		template <class Type> TS_INLINE Type littleEndian(Type value) { return value; }
		template <class Type> TS_INLINE Type bigEndian(Type value) { return swapEndian(value); }
		
		template <class Type> TS_INLINE void littleEndian(Type *data, size_t size) { }
		template <class Type> TS_INLINE void bigEndian(Type *data, size_t size) {
			for(size_t i = 0; i < size; i++) {
				data[i] = swapEndian(data[i]);
			}
		}
		
	#endif
}

#endif /* __TELLUSIM_CORE_ENDIAN_H__ */

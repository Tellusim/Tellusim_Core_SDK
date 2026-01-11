// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_MATH_RANDOM_H__
#define __TELLUSIM_MATH_RANDOM_H__

#include <math/TellusimFloat.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Linear congruential random generator
	 */
	template <class Integer = int32_t, class Float = float32_t> struct Random final {
		
		enum {
			MaxValue = 0x0fffffff,
		};
		
		/// constructor
		Random() {
			init(Integer(0x6b8b4567));
		}
		explicit Random(const Integer &s) {
			init(s);
		}
		
		/// initialize random
		void init(const Integer &s) {
			seed_0 = s;
			seed_1 = s;
			geti32();
		}
		
		/// returns an integer number
		Integer geti32(int32_t mask = MaxValue) {
			seed_0 = ((seed_0 * 16807 + 11) >> 2) & (int32_t)MaxValue;
			seed_1 = ((seed_1 * 48271 + 23) >> 2) & (int32_t)MaxValue;
			return (seed_0 - seed_1) & mask;
		}
		
		/// returns an integer in [min-max] range
		TS_INLINE Integer geti32(const Integer &min, const Integer &max) {
			return geti32() % (max - min + 1) + min;
		}
		
		/// returns a floating-point number in [0-1] range
		Float getf32() {
			union f32i32 {
				f32i32(const Integer &i) : i(i) { }
				Integer i;
				Float f;
			};
			return f32i32(geti32(0x7fffff) + 0x3f000000).f * 2.0f - 1.0f;
		}
		
		/// returns a floating-point number in [min-max] range
		TS_INLINE Float getf32(const Float &min, const Float &max) {
			return getf32() * (max - min) + min;
		}
		
		Integer seed_0;
		Integer seed_1;
	};
}

#endif /* __TELLUSIM_MATH_RANDOM_H__ */

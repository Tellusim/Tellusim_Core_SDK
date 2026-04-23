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
	
	/**
	 * Stratified samplers
	 */
	namespace Stratified {
		
		/// Halton sampler
		TS_INLINE float32_t halton2(uint32_t sample) {
			uint32_t bits = (sample << 16u) | (sample >> 16u);
			bits = ((bits & 0x00ff00ffu) << 8u) | ((bits & 0xff00ff00u) >> 8u);
			bits = ((bits & 0x0f0f0f0fu) << 4u) | ((bits & 0xf0f0f0f0u) >> 4u);
			bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xccccccccu) >> 2u);
			bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xaaaaaaaau) >> 1u);
			return bits * 0x1p-32f;
		}
		
		template <class Type, uint32_t Base> Type haltonN(uint32_t sample) {
			Type f = 1.0f, r = 0.0f;
			Type ibase = 1.0f / Base;
			while(sample > 0) {
				f *= ibase;
				r += f * (sample % Base);
				sample /= Base;
			}
			return r;
		}
		
		template <class Vector2> Vector2 halton23(uint32_t sample) {
			using Type = typename Vector2::Type;
			return Vector2(haltonN<Type, 2>(sample), haltonN<Type, 3>(sample));
		}
		
		template <class Vector2> Vector2 halton34(uint32_t sample) {
			using Type = typename Vector2::Type;
			return Vector2(haltonN<Type, 3>(sample), haltonN<Type, 4>(sample));
		}
		
		/// Hammersley sampler
		template <class Vector2> Vector2 hammersley(uint32_t sample, uint32_t samples) {
			using Type = typename Vector2::Type;
			return Vector2((Type)((sample % samples) + 0.5f) / (Type)samples, haltonN<Type, 2>(sample));
		}
		
		/// Vogel disk sampler
		template <class Vector2> Vector2 vogel(uint32_t sample, uint32_t samples, float32_t offset = 0.0f) {
			float32_t angle = sample * 2.39996322973f + offset;
			float32_t radius = sqrt(sample + 1.0f) / sqrt((float32_t)samples);
			return Vector2(sin(angle) * radius, cos(angle) * radius);
		}
		
		template <class Vector2> Vector2 vogelFast(uint32_t sample, uint32_t samples, float32_t offset = 0.0f) {
			float32_t radius = sample + 1.0f;
			float32_t angle = sample * 2.39996322973f + offset;
			radius = radius * rsqrtFast(radius) * rsqrtFast((float32_t)samples);
			return Vector2(sinFast(angle) * radius, cosFast(angle) * radius);
		}
	}
}

#endif /* __TELLUSIM_MATH_RANDOM_H__ */

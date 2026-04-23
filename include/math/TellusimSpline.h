// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_MATH_SPLINE_H__
#define __TELLUSIM_MATH_SPLINE_H__

#include <math/TellusimScalar.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Spline utils
	 */
	namespace Spline {
		
		/// Bezier spline
		template <class Type> TS_INLINE Type bezier(Type v0, Type v1, Type v2, Type v3, Type k1) {
			Type k0 = Type(1.0f) - k1, k02 = k0 * k0, k12 = k1 * k1;
			return v0 * k0 * k02 + Type(3.0f) * v1 * k02 * k1 + Type(3.0f) * v2 * k0 * k12 + v3 * k1 * k12;
		}
		
		/// Derivative of Bezier spline
		template <class Type> TS_INLINE Type dbezier(Type v0, Type v1, Type v2, Type v3, Type k1) {
			Type k0 = Type(1.0f) - k1;
			return Type(3.0f) * (v1 - v0) * k0 * k0 + Type(6.0f) * (v2 - v1) * k0 * k1 + Type(3.0f) * (v3 - v2) * k1 * k1;
		}
		
		/// Solves spline interection in [0-1] range
		template <class Type, class Func, uint32_t Iterations = 32> Type solve(Type v0, Type v1, Type v2, Type v3, Type value, Func func, Type threshold = Type(1e-4f)) {
			Type k0 = Type(0.0f);
			Type k1 = Type(1.0f);
			Type s0 = func(v0, v1, v2, v3, k0) - value;
			Type s1 = func(v0, v1, v2, v3, k1) - value;
			if(s0 * s1 > Type(0.0f)) return Type(-1.0f);
			if(abs(s0) < threshold) return k0;
			if(abs(s1) < threshold) return k1;
			for(uint32_t i = 0; i < Iterations && (k1 - k0) > threshold; i++) {
				Type k = (k0 + k1) * Type(0.5f);
				Type s = func(v0, v1, v2, v3, k) - value;
				if(abs(s) < threshold) return k;
				if(s0 * s < Type(0.0f)) k1 = k;
				else { k0 = k; s0 = s; }
			}
			return (k0 + k1) * Type(0.5f);
		}
	}
}

#endif /* __TELLUSIM_MATH_SPLINE_H__ */

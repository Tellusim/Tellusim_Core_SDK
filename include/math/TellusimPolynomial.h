// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_MATH_POLYNOMIAL_H__
#define __TELLUSIM_MATH_POLYNOMIAL_H__

#include <math/TellusimScalar.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Polynomial utils
	 */
	namespace Polynomial {
		
		/// Solves linear equation
		template <class Type> uint32_t linear(Type a, Type b, Type ret[1], Type epsilon = 1e-6f) {
			if(abs(a) > min(abs(b) * epsilon, epsilon)) {
				ret[0] = -b / a;
				return 1;
			}
			return 0;
		}
		
		/// Solves quadratic equation
		template <class Type> uint32_t quadratic(Type a, Type b, Type c, Type ret[2], Type epsilon = 1e-6f) {
			if(abs(a) > min(max(abs(b), abs(c)) * epsilon, epsilon)) {
				Type d = b * b - 4.0f * a * c;
				if(d == 0.0f) {
					ret[0] = -b * 0.5f / a;
					return 1;
				}
				if(d > 0.0f) {
					Type q = -(b + sign(b) * sqrt(d)) * 0.5f;
					Type x0 = q / a;
					Type x1 = c / q;
					if(x0 > x1) swap(x0, x1);
					ret[0] = x0;
					ret[1] = x1;
					return 2;
				}
				return 0;
			}
			return linear(b, c, ret, epsilon);
		}
		
		/// Solves cubic equation
		template <class Type> uint32_t cubicFast(Type a, Type b, Type c, Type d, Type ret[3], Type epsilon = 1e-6f) {
			if(abs(a) > min(max(abs(b), abs(c), abs(d)) * epsilon, epsilon)) {
				b /= 3.0f;
				c /= 3.0f;
				Type d0 = a * c - b * b;
				Type d1 = a * d - b * c;
				Type d2 = b * d - c * c;
				Type h = d1 * d1 - 4.0f * d0 * d2;
				if(h >= 0.0f) {
					h = sqrt(h);
					Type r = 2.0f * b * d0 - a * d1;
					Type p = cbrt((abs(r) + abs(a) * h) * 0.5f) * sign(r);
					Type x = (p - d0 / p - b) / a;
					Type dy = x * (x * 3.0f * a + 6.0f * b) + 3.0f * c;
					if(abs(dy) > epsilon) x -= (x * (x * (x * a + 3.0f * b) + 3.0f * c) + d) / dy;
					ret[0] = x;
					return 1;
				}
				if(h < 0.0f) {
					h = sqrt(-h);
					Type s0, c0, k0 = sqrt(-d0);
					Type t0 = atan2(a * h, 2.0f * b * d0 - a * d1);
					sincos(abs(t0) / 3.0f, s0, c0);
					s0 *= Sqrt3 * k0; c0 *= k0;
					ret[0] = (2.0f * c0 - b) / a;
					ret[1] = (-c0 - s0 - b) / a;
					ret[2] = (-c0 + s0 - b) / a;
					for(uint32_t i = 0; i < 3; i++) {
						Type x = ret[i];
						Type dy = x * (x * 3.0f * a + 6.0f * b) + 3.0f * c;
						if(abs(dy) > epsilon) ret[i] -= (x * (x * (x * a + 3.0f * b) + 3.0f * c) + d) / dy;
					}
					return 3;
				}
				return 0;
			}
			return quadratic(b, c, d, ret, epsilon);
		}
		
		/// Solves cubic equation
		template <class Type> uint32_t cubic(Type a, Type b, Type c, Type d, Type ret[3], Type epsilon = 1e-6f) {
			if(abs(a) > min(max(abs(b), abs(c), abs(d)) * epsilon, epsilon)) {
				b /= 3.0f;
				c /= 3.0f;
				Type d0 = a * c - b * b;
				Type d1 = a * d - b * c;
				Type d2 = b * d - c * c;
				Type h = d1 * d1 - 4.0f * d0 * d2;
				if(h >= 0.0f) {
					h = sqrt(h);
					Type x = 0.0f;
					if(b * b * b * d >= c * c * c * a) {
						Type r = 2.0f * b * d0 - a * d1;
						Type p = cbrt((abs(r) + abs(a) * h) * 0.5f) * sign(r);
						Type q = (abs(r) > 0.0f) ? d0 / p : p;
						x = (d0 > 0.0f) ? r / (p * p + q * q + d0) : p - q;
						x = (x - b) / a;
					} else {
						Type r = d * d1 - 2.0f * c * d2;
						Type p = cbrt((abs(r) + abs(d) * h) * 0.5f) * sign(r);
						Type q = (abs(r) > 0.0f) ? d2 / p : p;
						x = (d2 > 0.0f) ? r / (p * p + q * q + d2) : p - q;
						x = -d / (x + c);
					}
					Type dy = x * (x * 3.0f * a + 6.0f * b) + 3.0f * c;
					if(abs(dy) > epsilon) x -= (x * (x * (x * a + 3.0f * b) + 3.0f * c) + d) / dy;
					ret[0] = x;
					return 1;
				}
				if(h < 0.0f) {
					h = sqrt(-h);
					Type s0, c0, s1, c1;
					Type k0 = 2.0f * sqrt(-d0);
					Type k1 = 2.0f * sqrt(-d2);
					Type t0 = atan2(a * h, 2.0f * b * d0 - a * d1);
					Type t1 = atan2(d * h, d * d1 - 2.0f * c * d2);
					sincos(abs(t0) / 3.0f, s0, c0);
					sincos(abs(t1) / 3.0f, s1, c1);
					Type x00 = k0 * c0;
					Type x10 = k1 * c1;
					Type x01 = -(x00 + k0 * Sqrt3 * s0) * 0.5f;
					Type x11 = -(x10 + k1 * Sqrt3 * s1) * 0.5f;
					Type x0 = (x00 + x01 > 2.0f * b) ? x00 : x01;
					Type x1 = (x10 + x11 < 2.0f * c) ? x10 : x11;
					Type x0n = x0 - b;
					Type x1d = x1 + c;
					Type x2 = x0n * x1d - a * d;
					ret[0] = x0n / a;
					ret[1] = -d / x1d;
					ret[2] = -(x2 * c - x0n * b * d) / (x2 * b + x1d * a * c);
					for(uint32_t i = 0; i < 3; i++) {
						Type x = ret[i];
						Type dy = x * (x * 3.0f * a + 6.0f * b) + 3.0f * c;
						if(abs(dy) > epsilon) ret[i] -= (x * (x * (x * a + 3.0f * b) + 3.0f * c) + d) / dy;
					}
					if(ret[0] > ret[1]) swap(ret[0], ret[1]);
					if(ret[0] > ret[2]) swap(ret[0], ret[2]);
					if(ret[1] > ret[2]) swap(ret[1], ret[2]);
					return 3;
				}
				return 0;
			}
			return quadratic(b, c, d, ret, epsilon);
		}
		
		/// Solves quartic equation
		template <class Type> uint32_t quartic(Type a, Type b, Type c, Type d, Type e, Type ret[4], Type threshold = 1e-6f, Type epsilon = 1e-6f) {
			if(abs(a) > min(max(abs(b), abs(c), abs(d), abs(e)) * epsilon, epsilon)) {
				if(a != (Type)1.0f) {
					b = b / a;
					c = c / a;
					d = d / a;
					e = e / a;
				}
				Type p = b * d - 4.0f * e;
				Type q = 4.0f * c * e - b * b * e - d * d;
				uint32_t num = cubic((Type)1.0f, -c, p, q, ret, epsilon);
				if(num != 0) {
					b *= 0.5f;
					Type t = ret[num - 1];
					Type p = b * b - c + t;
					if(p > threshold) {
						Type q = sqrt(p);
						Type r = (b * t - d) * 0.5f;
						Type s = b * q;
						t *= q * 0.5f;
						num = quadratic(q, s - p, t - r, ret, epsilon);
						num += quadratic(q, s + p, t + r, ret + num, epsilon);
						for(uint32_t i = 0; i < num; i++) {
							Type x = ret[i];
							Type dy = x * (x * (x * 4.0f + 6.0f * b) + 2.0f * c) + d;
							if(abs(dy) > epsilon) ret[i] -= (x * (x * (x * (x + 2.0f * b) + c) + d) + e) / dy;
						}
						if(num == 4) {
							if(ret[0] > ret[2]) swap(ret[0], ret[2]);
							if(ret[1] > ret[3]) swap(ret[1], ret[3]);
							if(ret[1] > ret[2]) swap(ret[1], ret[2]);
						} else if(num == 3) {
							if(ret[0] > ret[1]) swap(ret[0], ret[1]);
							if(ret[0] > ret[2]) swap(ret[0], ret[2]);
							if(ret[1] > ret[2]) swap(ret[1], ret[2]);
						} else if(num == 2) {
							if(ret[0] > ret[1]) swap(ret[0], ret[1]);
						}
						return num;
					}
				}
				return 0;
			}
			return cubic(b, c, d, e, ret, epsilon);
		}
		template <class Type> uint32_t quarticRev(Type a, Type b, Type c, Type d, Type e, Type ret[4], Type threshold = 1e-6f, Type epsilon = 1e-6f) {
			uint32_t num = quartic(e, d, c, b, a, ret, threshold, epsilon);
			for(uint32_t i = 0; i < num; i++) ret[i] = 1.0f / ret[i];
			return num;
		}
		
		/// Solves quintic equation
		template <class Type, uint32_t Num = 64> uint32_t quintic(Type a, Type b, Type c, Type d, Type e, Type f, Type ret[5], Type x, Type threshold = 1e-6f, Type epsilon = 1e-6f) {
			if(abs(a) > min(max(max(abs(b), abs(c), abs(d), abs(e)), abs(f)) * epsilon, epsilon)) {
				Type old_dx = Maxf32;
				for(uint32_t i = 0; i < Num; i++) {
					Type y = x * (x * (x * (x * (x * a + b) + c) + d) + e) + f;
					Type dy = x * (x * (x * (x * 5.0f * a + 4.0f * b) + 3.0f * c) + 2.0f * d) + e;
					Type ddy = x * (x * (x * 20.0f * a + 12.0f * b) + 6.0f * c) + 2.0f * d;
					Type denominator = sqrt(max(16.0f * dy * dy - 20.0f * y * ddy, (Type)0.0f));
					if(abs(dy - denominator) > abs(dy + denominator)) denominator = -denominator;
					Type dx = 5.0f * y / (dy + denominator);
					if(abs(dx * 1.1f) > abs(old_dx)) break;
					old_dx = dx;
					x -= dx;
					if(abs(dx) < threshold) {
						b += a * x;
						c += b * x;
						d += c * x;
						e += d * x;
						uint32_t num = quartic(a, b, c, d, e, ret, threshold, epsilon);
						if(num == 0) num = quarticRev(a, b, c, d, e, ret, threshold, epsilon);
						ret[num++] = x;
						return num;
					}
				}
				return 0;
			}
			return quartic(b, c, d, e, f, ret, threshold, epsilon);
		}
		template <class Type, uint32_t Num = 64> uint32_t quinticRev(Type a, Type b, Type c, Type d, Type e, Type f, Type ret[5], Type x, Type threshold = 1e-6f, Type epsilon = 1e-6f) {
			uint32_t num = quintic<Type, Num>(f, e, d, c, b, a, ret, 1.0f / x, threshold, epsilon);
			for(uint32_t i = 0; i < num; i++) ret[i] = 1.0f / ret[i];
			return num;
		}
		template <class Type, uint32_t Num = 64> uint32_t quinticNr(Type a, Type b, Type c, Type d, Type e, Type f, Type ret[5], Type x, Type threshold = 1e-6f, Type epsilon = 1e-6f) {
			uint32_t num = quintic<Type, Num>(a, b, c, d, e, f, ret, x, threshold, epsilon);
			if(num == 0) num = quinticRev<Type, Num>(a, b, c, d, e, f, ret, x, threshold, epsilon);
			for(uint32_t i = 0; i < num; i++) {
				Type x = ret[i];
				Type dy = x * (x * (x * (x * 5.0f * a + 4.0f * b) + 3.0f * c) + 2.0f * d) + e;
				if(abs(dy) > epsilon) ret[i] -= (x * (x * (x * (x * (x * a + b) + c) + d) + e) + f) / dy;
			}
			return num;
		}
		
		/// Solves sextic equation
		template <class Type, uint32_t Num = 64> uint32_t sextic(Type a, Type b, Type c, Type d, Type e, Type f, Type g, Type ret[6], Type x, Type threshold = 1e-6f, Type epsilon = 1e-6f) {
			if(abs(a) > min(max(max(abs(b), abs(c), abs(d), abs(e)), abs(f), abs(g)) * epsilon, epsilon)) {
				Type old_dx = Maxf32;
				for(uint32_t i = 0; i < Num; i++) {
					Type y = x * (x * (x * (x * (x * (x * a + b) + c) + d) + e) + f) + g;
					Type dy = x * (x * (x * (x * (x * 6.0f * a + 5.0f * b) + 4.0f * c) + 3.0f * d) + 2.0f * e) + f;
					Type ddy = x * (x * (x * (x * 30.0f * a + 20.0f * b) + 12.0f * c) + 6.0f * d) + 2.0f * e;
					Type denominator = sqrt(max(25.0f * dy * dy - 30.0f * y * ddy, (Type)0.0f));
					if(abs(dy - denominator) > abs(dy + denominator)) denominator = -denominator;
					Type dx = 6.0f * y / (dy + denominator);
					if(abs(dx * 1.1f) > abs(old_dx)) break;
					old_dx = dx;
					x -= dx;
					if(abs(dx) < threshold) {
						b += a * x;
						c += b * x;
						d += c * x;
						e += d * x;
						f += e * x;
						uint32_t num = quintic(a, b, c, d, e, f, ret, x, threshold, epsilon);
						if(num == 0) num = quinticRev(a, b, c, d, e, f, ret, x, threshold, epsilon);
						ret[num++] = x;
						return num;
					}
				}
				return 0;
			}
			return quintic(b, c, d, e, f, g, ret, x, threshold, epsilon);
		}
		template <class Type, uint32_t Num = 64> uint32_t sexticRev(Type a, Type b, Type c, Type d, Type e, Type f, Type g, Type ret[6], Type x, Type threshold = 1e-6f, Type epsilon = 1e-6f) {
			uint32_t num = sextic<Type, Num>(g, f, e, d, c, b, a, ret, 1.0f / x, threshold, epsilon);
			for(uint32_t i = 0; i < num; i++) ret[i] = 1.0f / ret[i];
			return num;
		}
		template <class Type, uint32_t Num = 64> uint32_t sexticNr(Type a, Type b, Type c, Type d, Type e, Type f, Type g, Type ret[6], Type x, Type threshold = 1e-6f, Type epsilon = 1e-6f) {
			uint32_t num = sextic<Type, Num>(a, b, c, d, e, f, g, ret, x, threshold, epsilon);
			if(num == 0) num = sexticRev<Type, Num>(a, b, c, d, e, f, g, ret, x, threshold, epsilon);
			for(uint32_t i = 0; i < num; i++) {
				Type x = ret[i];
				Type dy = x * (x * (x * (x * (x * 6.0f * a + 5.0f * b) + 4.0f * c) + 3.0f * d) + 2.0f * e) + f;
				if(abs(dy) > epsilon) ret[i] -= (x * (x * (x * (x * (x * (x * a + b) + c) + d) + e) + f) + g) / dy;
			}
			return num;
		}
		
		/// Solves septic equation
		template <class Type, uint32_t Num = 64> uint32_t septic(Type a, Type b, Type c, Type d, Type e, Type f, Type g, Type h, Type ret[7], Type x, Type threshold = 1e-6f, Type epsilon = 1e-6f) {
			if(abs(a) > min(max(max(abs(b), abs(c), abs(d), abs(e)), abs(f), abs(g), abs(h)) * epsilon, epsilon)) {
				Type old_dx = Maxf32;
				for(uint32_t i = 0; i < Num; i++) {
					Type y = x * (x * (x * (x * (x * (x * (x * a + b) + c) + d) + e) + f) + g) + h;
					Type dy = x * (x * (x * (x * (x * (x * 7.0f * a + 6.0f * b) + 5.0f * c) + 4.0f * d) + 3.0f * e) + 2.0f * f) + g;
					Type ddy = x * (x * (x * (x * (x * 42.0f * a + 30.0f * b) + 20.0f * c) + 12.0f * d) + 6.0f * e) + 2.0f * f;
					Type denominator = sqrt(max(36.0f * dy * dy - 42.0f * y * ddy, (Type)0.0f));
					if(abs(dy - denominator) > abs(dy + denominator)) denominator = -denominator;
					Type dx = 7.0f * y / (dy + denominator);
					if(abs(dx * 1.1f) > abs(old_dx)) break;
					old_dx = dx;
					x -= dx;
					if(abs(dx) < threshold) {
						b += a * x;
						c += b * x;
						d += c * x;
						e += d * x;
						f += e * x;
						g += f * x;
						uint32_t num = sextic(a, b, c, d, e, f, g, ret, x, threshold, epsilon);
						if(num == 0) num = sexticRev(a, b, c, d, e, f, g, ret, x, threshold, epsilon);
						ret[num++] = x;
						return num;
					}
				}
				return 0;
			}
			return sextic(b, c, d, e, f, g, h, ret, x, threshold, epsilon);
		}
		template <class Type, uint32_t Num = 64> uint32_t septicRev(Type a, Type b, Type c, Type d, Type e, Type f, Type g, Type h, Type ret[7], Type x, Type threshold = 1e-6f, Type epsilon = 1e-6f) {
			uint32_t num = septic<Type, Num>(h, g, f, e, d, c, b, a, ret, 1.0f / x, threshold, epsilon);
			for(uint32_t i = 0; i < num; i++) ret[i] = 1.0f / ret[i];
			return num;
		}
		template <class Type, uint32_t Num = 64> uint32_t septicNr(Type a, Type b, Type c, Type d, Type e, Type f, Type g, Type h, Type ret[7], Type x, Type threshold = 1e-6f, Type epsilon = 1e-6f) {
			uint32_t num = septic<Type, Num>(a, b, c, d, e, f, g, h, ret, x, threshold, epsilon);
			if(num == 0) num = septicRev<Type, Num>(a, b, c, d, e, f, g, h, ret, x, threshold, epsilon);
			for(uint32_t i = 0; i < num; i++) {
				Type x = ret[i];
				Type dy = x * (x * (x * (x * (x * (x * 7.0f * a + 6.0f * b) + 5.0f * c) + 4.0f * d) + 3.0f * e) + 2.0f * f) + h;
				if(abs(dy) > epsilon) ret[i] -= (x * (x * (x * (x * (x * (x * (x * a + b) + c) + d) + e) + f) + g) + h) / dy;
			}
			return num;
		}
	}
}

#endif /* __TELLUSIM_MATH_POLYNOMIAL_H__ */

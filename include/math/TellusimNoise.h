// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_MATH_NOISE_H__
#define __TELLUSIM_MATH_NOISE_H__

#include <math/TellusimFloat.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Noise
	 */
	namespace Noise {
		
		/// utils
		template <class Type> TS_INLINE void mod289(Type &x) {
			x -= floor(x * (1.0f / 289.0f)) * 289.0f;
		}
		
		template <class Type> TS_INLINE void perm(Type &x) {
			x *= x * 34.0f + 1.0f;
			mod289(x);
		}
		
		template <class Type> TS_INLINE Type fract(const Type &x) {
			return x - floor(x);
		}
		
		template <class Type> TS_INLINE Type rsqrt_fast(const Type &x) {
			return x * (-0.85373472095314f) + 1.79284291400159f;
		}
		
		/// 2D Perlin noise
		template <class Type> Type perlin(const Type &x, const Type &y, bool cubic = false) {
			Type fx = fract(x);
			Type fy = fract(y);
			Type ix = floor(x);
			Type iy = floor(y);
			Type fz = fx - 1.0f;
			Type fw = fy - 1.0f;
			Type iz = ix + 1.0f;
			Type iw = iy + 1.0f;
			mod289(ix);
			mod289(iy);
			mod289(iz);
			mod289(iw);
			perm(ix);
			perm(iz);
			Type px = ix + iy;
			Type py = iz + iy;
			Type pz = ix + iw;
			Type pw = iz + iw;
			perm(px);
			perm(py);
			perm(pz);
			perm(pw);
			Type xx = fract(px * (1.0f / 41.0f)) * 2.0f - 1.0f;
			Type xy = fract(py * (1.0f / 41.0f)) * 2.0f - 1.0f;
			Type xz = fract(pz * (1.0f / 41.0f)) * 2.0f - 1.0f;
			Type xw = fract(pw * (1.0f / 41.0f)) * 2.0f - 1.0f;
			Type yx = abs(xx) - 0.5f;
			Type yy = abs(xy) - 0.5f;
			Type yz = abs(xz) - 0.5f;
			Type yw = abs(xw) - 0.5f;
			xx -= floor(xx + 0.5f);
			xy -= floor(xy + 0.5f);
			xz -= floor(xz + 0.5f);
			xw -= floor(xw + 0.5f);
			Type kx, ky;
			if(cubic) {
				kx = fx * fx * (fx * (-2.0f) + 3.0f);
				ky = fy * fy * (fy * (-2.0f) + 3.0f);
			} else {
				kx = fx * fx * fx * (fx * (fx * 6.0f - 15.0f) + 10.0f);
				ky = fy * fy * fy * (fy * (fy * 6.0f - 15.0f) + 10.0f);
			}
			Type vx = (xx * fx + yx * fy) * rsqrt_fast(xx * xx + yx * yx);
			Type vy = (xy * fz + yy * fy) * rsqrt_fast(xy * xy + yy * yy);
			Type vz = (xz * fx + yz * fw) * rsqrt_fast(xz * xz + yz * yz);
			Type vw = (xw * fz + yw * fw) * rsqrt_fast(xw * xw + yw * yw);
			return (vx + (vy - vx) * kx + (vz - vx) * ky + (vx - vy - vz + vw) * (kx * ky)) * (2.3f * 0.5f) + 0.5f;
		}
		
		/// 3D Perlin noise
		template <class Type> Type perlin(const Type &x, const Type &y, const Type &z, bool cubic = false) {
			Type f0x = fract(x);
			Type f0y = fract(y);
			Type f0z = fract(z);
			Type i0x = floor(x);
			Type i0y = floor(y);
			Type i0z = floor(z);
			Type f1x = f0x - 1.0f;
			Type f1y = f0y - 1.0f;
			Type f1z = f0z - 1.0f;
			Type i1x = i0x + 1.0f;
			Type i1y = i0y + 1.0f;
			Type i1z = i0z + 1.0f;
			mod289(i0x);
			mod289(i0y);
			mod289(i0z);
			mod289(i1x);
			mod289(i1y);
			mod289(i1z);
			perm(i0x);
			perm(i1x);
			Type px = i0x + i0y;
			Type py = i1x + i0y;
			Type pz = i0x + i1y;
			Type pw = i1x + i1y;
			perm(px);
			perm(py);
			perm(pz);
			perm(pw);
			Type p0x = px + i0z;
			Type p0y = py + i0z;
			Type p0z = pz + i0z;
			Type p0w = pw + i0z;
			Type p1x = px + i1z;
			Type p1y = py + i1z;
			Type p1z = pz + i1z;
			Type p1w = pw + i1z;
			perm(p0x);
			perm(p0y);
			perm(p0z);
			perm(p0w);
			perm(p1x);
			perm(p1y);
			perm(p1z);
			perm(p1w);
			Type gx0x = p0x * (1.0f / 7.0f);
			Type gx0y = p0y * (1.0f / 7.0f);
			Type gx0z = p0z * (1.0f / 7.0f);
			Type gx0w = p0w * (1.0f / 7.0f);
			Type gx1x = p1x * (1.0f / 7.0f);
			Type gx1y = p1y * (1.0f / 7.0f);
			Type gx1z = p1z * (1.0f / 7.0f);
			Type gx1w = p1w * (1.0f / 7.0f);
			Type gy0x = fract(floor(gx0x) * (1.0f / 7.0f)) - 0.5f;
			Type gy0y = fract(floor(gx0y) * (1.0f / 7.0f)) - 0.5f;
			Type gy0z = fract(floor(gx0z) * (1.0f / 7.0f)) - 0.5f;
			Type gy0w = fract(floor(gx0w) * (1.0f / 7.0f)) - 0.5f;
			Type gy1x = fract(floor(gx1x) * (1.0f / 7.0f)) - 0.5f;
			Type gy1y = fract(floor(gx1y) * (1.0f / 7.0f)) - 0.5f;
			Type gy1z = fract(floor(gx1z) * (1.0f / 7.0f)) - 0.5f;
			Type gy1w = fract(floor(gx1w) * (1.0f / 7.0f)) - 0.5f;
			gx0x = fract(gx0x);
			gx0y = fract(gx0y);
			gx0z = fract(gx0z);
			gx0w = fract(gx0w);
			gx1x = fract(gx1x);
			gx1y = fract(gx1y);
			gx1z = fract(gx1z);
			gx1w = fract(gx1w);
			Type gz0x = Type(0.5f) - abs(gx0x) - abs(gy0x);
			Type gz0y = Type(0.5f) - abs(gx0y) - abs(gy0y);
			Type gz0z = Type(0.5f) - abs(gx0z) - abs(gy0z);
			Type gz0w = Type(0.5f) - abs(gx0w) - abs(gy0w);
			Type gz1x = Type(0.5f) - abs(gx1x) - abs(gy1x);
			Type gz1y = Type(0.5f) - abs(gx1y) - abs(gy1y);
			Type gz1z = Type(0.5f) - abs(gx1z) - abs(gy1z);
			Type gz1w = Type(0.5f) - abs(gx1w) - abs(gy1w);
			Type sz0x = select(Type(0.0f), Type(1.0f), gz0x);
			Type sz0y = select(Type(0.0f), Type(1.0f), gz0y);
			Type sz0z = select(Type(0.0f), Type(1.0f), gz0z);
			Type sz0w = select(Type(0.0f), Type(1.0f), gz0w);
			Type sz1x = select(Type(0.0f), Type(1.0f), gz1x);
			Type sz1y = select(Type(0.0f), Type(1.0f), gz1y);
			Type sz1z = select(Type(0.0f), Type(1.0f), gz1z);
			Type sz1w = select(Type(0.0f), Type(1.0f), gz1w);
			gx0x -= sz0x * select(Type(0.5f), Type(-0.5f), gx0x);
			gx0y -= sz0y * select(Type(0.5f), Type(-0.5f), gx0y);
			gx0z -= sz0z * select(Type(0.5f), Type(-0.5f), gx0z);
			gx0w -= sz0w * select(Type(0.5f), Type(-0.5f), gx0w);
			gx1x -= sz1x * select(Type(0.5f), Type(-0.5f), gx1x);
			gx1y -= sz1y * select(Type(0.5f), Type(-0.5f), gx1y);
			gx1z -= sz1z * select(Type(0.5f), Type(-0.5f), gx1z);
			gx1w -= sz1w * select(Type(0.5f), Type(-0.5f), gx1w);
			gy0x -= sz0x * select(Type(0.5f), Type(-0.5f), gy0x);
			gy0y -= sz0y * select(Type(0.5f), Type(-0.5f), gy0y);
			gy0z -= sz0z * select(Type(0.5f), Type(-0.5f), gy0z);
			gy0w -= sz0w * select(Type(0.5f), Type(-0.5f), gy0w);
			gy1x -= sz1x * select(Type(0.5f), Type(-0.5f), gy1x);
			gy1y -= sz1y * select(Type(0.5f), Type(-0.5f), gy1y);
			gy1z -= sz1z * select(Type(0.5f), Type(-0.5f), gy1z);
			gy1w -= sz1w * select(Type(0.5f), Type(-0.5f), gy1w);
			Type v0 = (gx0x * f0x + gy0x * f0y + gz0x * f0z) * rsqrt_fast(gx0x * gx0x + gy0x * gy0x + gz0x * gz0x);
			Type v1 = (gx0y * f1x + gy0y * f0y + gz0y * f0z) * rsqrt_fast(gx0y * gx0y + gy0y * gy0y + gz0y * gz0y);
			Type v2 = (gx0z * f0x + gy0z * f1y + gz0z * f0z) * rsqrt_fast(gx0z * gx0z + gy0z * gy0z + gz0z * gz0z);
			Type v3 = (gx0w * f1x + gy0w * f1y + gz0w * f0z) * rsqrt_fast(gx0w * gx0w + gy0w * gy0w + gz0w * gz0w);
			Type v4 = (gx1x * f0x + gy1x * f0y + gz1x * f1z) * rsqrt_fast(gx1x * gx1x + gy1x * gy1x + gz1x * gz1x);
			Type v6 = (gx1y * f1x + gy1y * f0y + gz1y * f1z) * rsqrt_fast(gx1y * gx1y + gy1y * gy1y + gz1y * gz1y);
			Type v5 = (gx1z * f0x + gy1z * f1y + gz1z * f1z) * rsqrt_fast(gx1z * gx1z + gy1z * gy1z + gz1z * gz1z);
			Type v7 = (gx1w * f1x + gy1w * f1y + gz1w * f1z) * rsqrt_fast(gx1w * gx1w + gy1w * gy1w + gz1w * gz1w);
			Type kx, ky, kz;
			if(cubic) {
				kx = f0x * f0x * (f0x * (-2.0f) + 3.0f);
				ky = f0y * f0y * (f0y * (-2.0f) + 3.0f);
				kz = f0z * f0z * (f0z * (-2.0f) + 3.0f);
			} else {
				kx = f0x * f0x * f0x * (f0x * (f0x * 6.0f - 15.0f) + 10.0f);
				ky = f0y * f0y * f0y * (f0y * (f0y * 6.0f - 15.0f) + 10.0f);
				kz = f0z * f0z * f0z * (f0z * (f0z * 6.0f - 15.0f) + 10.0f);
			}
			return (v0 + (v1 - v0) * kx + (v2 - v0) * ky + (v4 - v0) * kz +
				(v0 - v1 - v2 + v3) * (kx * ky) + (v0 - v2 - v4 + v5) * (ky * kz) +
				(v0 - v1 - v4 + v6) * (kz * kx) + (-v0 + v1 + v2 - v3 + v4 - v6 - v5 + v7) * (kx * ky * kz)) * (2.3f * 0.5f) + 0.5f;
		}
		
		/// 2D Fractal noise
		template <class Type> Type fractal(Type x, Type y, uint32_t steps = 5, float32_t scale = 0.5f) {
			Type ret = Type(0.0f);
			float32_t value = 1.0f;
			for(uint32_t i = 0; i < steps; i++) {
				ret += (perlin(x, y) - 0.5f) * value;
				Type sx = x * (-1.47f) + y * (-1.35f);
				Type sy = x * ( 1.35f) + y * (-1.47f);
				value *= scale;
				x = sx;
				y = sy;
			}
			return ret + 0.5f;
		}
		
		/// 3D Fractal noise
		template <class Type> Type fractal(Type x, Type y, Type z, uint32_t steps = 5, float32_t scale = 0.5f) {
			Type ret = Type(0.0f);
			float32_t value = 1.0f;
			for(uint32_t i = 0; i < steps; i++) {
				ret += (perlin(x, y, z) - 0.5f) * value;
				Type sx = x * ( 1.119847f) + y * (-1.635496f) + z * 0.266637f;
				Type sy = x * ( 0.580474f) + y * ( 0.688591f) + z * 1.785747f;
				Type sz = x * (-1.552093f) + y * (-0.922494f) + z * 0.860240f;
				value *= scale;
				x = sx;
				y = sy;
				z = sz;
			}
			return ret + 0.5f;
		}
	}
}

#endif /* __TELLUSIM_MATH_NOISE_H__ */

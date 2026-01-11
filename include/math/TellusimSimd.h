// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_MATH_SIMD_H__
#define __TELLUSIM_MATH_SIMD_H__

#if (TS_AVX || TS_SSE) && (_LINUX || _MACOS)
	#include <x86intrin.h>
#endif

#if TS_AVX >= 1
	#define TS_SSE	4
	#include <immintrin.h>
#elif TS_SSE >= 4
	#include <nmmintrin.h>
#elif TS_SSE >= 2
	#include <emmintrin.h>
#endif

#if TS_NEON
	#include <arm_neon.h>
	#include <TellusimBase.h>
	TS_INLINE int16x8_t _vld1q_s16(const int16_t *v) { return vld1q_s16(v); }
	TS_INLINE int32x4_t _vld1q_s32(const int32_t *v) { return vld1q_s32(v); }
	TS_INLINE uint16x4_t _vld1_u16(const uint16_t *v) { return vld1_u16(v); }
	TS_INLINE uint16x8_t _vld1q_u16(const uint16_t *v) { return vld1q_u16(v); }
	TS_INLINE uint32x4_t _vld1q_u32(const uint32_t *v) { return vld1q_u32(v); }
	TS_INLINE float32x4_t _vld1q_f32(const float32_t *v) { return vld1q_f32(v); }
	TS_INLINE void _vst1q_s16(int16_t *v, int16x8_t vec) { return vst1q_s16(v, vec); }
	TS_INLINE void _vst1q_s32(int32_t *v, int32x4_t vec) { return vst1q_s32(v, vec); }
	TS_INLINE void _vst1_u16(uint16_t *v, uint16x4_t vec) { return vst1_u16(v, vec); }
	TS_INLINE void _vst1q_u16(uint16_t *v, uint16x8_t vec) { return vst1q_u16(v, vec); }
	TS_INLINE void _vst1q_u32(uint32_t *v, uint32x4_t vec) { return vst1q_u32(v, vec); }
	TS_INLINE void _vst1q_f32(float32_t *v, float32x4_t vec) { return vst1q_f32(v, vec); }
	template <uint32_t Index> TS_INLINE int16x8_t _vsetq_lane_s16(int16_t v, int16x8_t vec) { return vsetq_lane_s16(v, vec, Index); }
	template <uint32_t Index> TS_INLINE int32x4_t _vsetq_lane_s32(int32_t v, int32x4_t vec) { return vsetq_lane_s32(v, vec, Index); }
	template <uint32_t Index> TS_INLINE uint16x4_t _vset_lane_u16(uint16_t v, uint16x4_t vec) { return vset_lane_u16(v, vec, Index); }
	template <uint32_t Index> TS_INLINE uint16x8_t _vsetq_lane_u16(uint16_t v, uint16x8_t vec) { return vsetq_lane_u16(v, vec, Index); }
	template <uint32_t Index> TS_INLINE uint32x4_t _vsetq_lane_u32(uint32_t v, uint32x4_t vec) { return vsetq_lane_u32(v, vec, Index); }
	template <uint32_t Index> TS_INLINE float32x4_t _vsetq_lane_f32(float32_t v, float32x4_t vec) { return vsetq_lane_f32(v, vec, Index); }
	template <uint32_t Index> TS_INLINE int16_t _vget_lane_s16(int16x4_t vec) { return vget_lane_s16(vec, Index); }
	template <uint32_t Index> TS_INLINE int32_t _vget_lane_s32(int32x2_t vec) { return vget_lane_s32(vec, Index); }
	template <uint32_t Index> TS_INLINE int16_t _vgetq_lane_s16(int16x8_t vec) { return vgetq_lane_s16(vec, Index); }
	template <uint32_t Index> TS_INLINE int32_t _vgetq_lane_s32(int32x4_t vec) { return vgetq_lane_s32(vec, Index); }
	template <uint32_t Index> TS_INLINE uint16_t _vget_lane_u16(uint16x4_t vec) { return vget_lane_u16(vec, Index); }
	template <uint32_t Index> TS_INLINE uint32_t _vget_lane_u32(uint32x2_t vec) { return vget_lane_u32(vec, Index); }
	template <uint32_t Index> TS_INLINE uint16_t _vgetq_lane_u16(uint16x8_t vec) { return vgetq_lane_u16(vec, Index); }
	template <uint32_t Index> TS_INLINE uint32_t _vgetq_lane_u32(uint32x4_t vec) { return vgetq_lane_u32(vec, Index); }
	template <uint32_t Index> TS_INLINE float32_t _vget_lane_f32(float32x2_t vec) { return vget_lane_f32(vec, Index); }
	template <uint32_t Index> TS_INLINE float32_t _vgetq_lane_f32(float32x4_t vec) { return vgetq_lane_f32(vec, Index); }
	template <uint32_t Index> TS_INLINE float32x4_t _vdupq_lane_f32(float32x2_t vec) { return vdupq_lane_f32(vec, Index); }
	template <uint32_t Index> TS_INLINE float32x4_t _vmulq_lane_f32(float32x4_t v0, float32x2_t v1) { return vmulq_lane_f32(v0, v1, Index); }
	template <uint32_t Index> TS_INLINE float32x4_t _vmlaq_lane_f32(float32x4_t v0, float32x4_t v1, float32x2_t v2) { return vmlaq_lane_f32(v0, v1, v2, Index); }
	template <uint32_t Index> TS_INLINE float32x4_t _vmlsq_lane_f32(float32x4_t v0, float32x4_t v1, float32x2_t v2) { return vmlsq_lane_f32(v0, v1, v2, Index); }
	template <uint32_t Index> TS_INLINE float32x4_t _vextq_f32(float32x4_t v0, float32x4_t v1) { return vextq_f32(v0, v1, Index); }
	#if _WIN32
		TS_INLINE int16x4_t vset_s16(int16_t v0, int16_t v1, int16_t v2, int16_t v3) { const int16_t v[4] = { v0, v1, v2, v3 }; return vld1_s16(v); }
		TS_INLINE uint16x4_t vset_u16(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3) { const uint16_t v[4] = { v0, v1, v2, v3 }; return vld1_u16(v); }
		TS_INLINE int16x8_t vsetq_s16(int16_t v0, int16_t v1, int16_t v2, int16_t v3, int16_t v4, int16_t v5, int16_t v6, int16_t v7) { const int16_t v[8] = { v0, v1, v2, v3, v4, v5, v6, v7 }; return vld1q_s16(v); }
		TS_INLINE uint16x8_t vsetq_u16(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3, uint16_t v4, uint16_t v5, uint16_t v6, uint16_t v7) { const uint16_t v[8] = { v0, v1, v2, v3, v4, v5, v6, v7 }; return vld1q_u16(v); }
		TS_INLINE int32x4_t vsetq_s32(int32_t v0, int32_t v1, int32_t v2, int32_t v3) { const int32_t v[4] = { v0, v1, v2, v3 }; return vld1q_s32(v); }
		TS_INLINE uint32x4_t vsetq_u32(uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3) { const uint32_t v[4] = { v0, v1, v2, v3 }; return vld1q_u32(v); }
		TS_INLINE float32x4_t vsetq_f32(float32_t v0, float32_t v1, float32_t v2, float32_t v3) { const float32_t v[4] = { v0, v1, v2, v3 }; return vld1q_f32(v); }
	#else
		TS_INLINE int16x4_t vset_s16(int16_t v0, int16_t v1, int16_t v2, int16_t v3) { return (int16x4_t){ v0, v1, v2, v3 }; }
		TS_INLINE uint16x4_t vset_u16(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3) { return (uint16x4_t){ v0, v1, v2, v3 }; }
		TS_INLINE int16x8_t vsetq_s16(int16_t v0, int16_t v1, int16_t v2, int16_t v3, int16_t v4, int16_t v5, int16_t v6, int16_t v7) { return (int16x8_t){ v0, v1, v2, v3, v4, v5, v6, v7 }; }
		TS_INLINE uint16x8_t vsetq_u16(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3, uint16_t v4, uint16_t v5, uint16_t v6, uint16_t v7) { return (uint16x8_t){ v0, v1, v2, v3, v4, v5, v6, v7 }; }
		TS_INLINE int32x4_t vsetq_s32(int32_t v0, int32_t v1, int32_t v2, int32_t v3) { return (int32x4_t){ v0, v1, v2, v3 }; }
		TS_INLINE uint32x4_t vsetq_u32(uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3) { return (uint32x4_t){ v0, v1, v2, v3 }; }
		TS_INLINE float32x4_t vsetq_f32(float32_t v0, float32_t v1, float32_t v2, float32_t v3) { return (float32x4_t){ v0, v1, v2, v3 }; }
	#endif
#endif

/*
 */
#include <math/TellusimFloat.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	struct int16x8_t;
	struct int32x4_t;
	struct int32x8_t;
	struct uint16x8_t;
	struct uint32x4_t;
	struct uint32x8_t;
	struct float16x4_t;
	struct float16x8_t;
	struct float32x4_t;
	struct float32x8_t;
	struct float64x2_t;
	struct float64x4_t;
	struct float64x8_t;
	
	/// simd types
	template <> struct IsPod<int16x8_t> { enum { Result = 1 }; };
	template <> struct IsPod<int32x4_t> { enum { Result = 1 }; };
	template <> struct IsPod<int32x8_t> { enum { Result = 1 }; };
	template <> struct IsPod<uint16x8_t> { enum { Result = 1 }; };
	template <> struct IsPod<uint32x4_t> { enum { Result = 1 }; };
	template <> struct IsPod<uint32x8_t> { enum { Result = 1 }; };
	template <> struct IsPod<float16x4_t> { enum { Result = 1 }; };
	template <> struct IsPod<float16x8_t> { enum { Result = 1 }; };
	template <> struct IsPod<float32x4_t> { enum { Result = 1 }; };
	template <> struct IsPod<float32x8_t> { enum { Result = 1 }; };
	template <> struct IsPod<float64x2_t> { enum { Result = 1 }; };
	template <> struct IsPod<float64x4_t> { enum { Result = 1 }; };
	template <> struct IsPod<float64x8_t> { enum { Result = 1 }; };
	
	/**
	 * SSE Utils
	 */
	#if TS_SSE >= 1
		
		/// swizzle components
		#define _MM_SWIZZLE_X	0
		#define _MM_SWIZZLE_Y	1
		#define _MM_SWIZZLE_Z	2
		#define _MM_SWIZZLE_W	3
		#define _mm_swizzle_ps(V0, V1, X, Y, Z, W) _mm_shuffle_ps(V0, V1, (_MM_SWIZZLE_ ## W << 6) | (_MM_SWIZZLE_ ## Z << 4) | (_MM_SWIZZLE_ ## Y << 2) | (_MM_SWIZZLE_ ## X))
		
		/// vector functions
		TS_INLINE __m128 _mm_dot4_ps(__m128 v0, __m128 v1) {
			__m128 v = _mm_mul_ps(v0, v1);
			#if TS_SSE >= 3
				v = _mm_hadd_ps(v, v);
				return _mm_hadd_ps(v, v);
			#else
				v = _mm_add_ps(v, _mm_swizzle_ps(v, v, Z, W, X, Y));
				return _mm_add_ps(v, _mm_swizzle_ps(v, v, Y, X, W, Z));
			#endif
		}
		
		/// math functions
		TS_INLINE __m128 _mm_rcp_ss_nr(__m128 v) {
			__m128 iv = _mm_rcp_ss(v);
			return _mm_sub_ss(_mm_add_ss(iv, iv), _mm_mul_ss(_mm_mul_ss(iv, iv), v));
		}
		
		TS_INLINE __m128 _mm_rcp_ps_nr(__m128 v) {
			__m128 iv = _mm_rcp_ps(v);
			return _mm_sub_ps(_mm_add_ps(iv, iv), _mm_mul_ps(_mm_mul_ps(iv, iv), v));
		}
		
		TS_INLINE __m128 _mm_rsqrt_ss_nr(__m128 v) {
			__m128 iv = _mm_rsqrt_ss(v);
			__m128 nr = _mm_mul_ss(_mm_mul_ss(iv, iv), v);
			return _mm_mul_ss(_mm_sub_ss(_mm_set_ss(3.0f), nr), _mm_mul_ss(_mm_set_ss(0.5f), iv));
		}
		
		TS_INLINE __m128 _mm_rsqrt_ps_nr(__m128 v) {
			__m128 iv = _mm_rsqrt_ps(v);
			__m128 nr = _mm_mul_ps(_mm_mul_ps(iv, iv), v);
			return _mm_mul_ps(_mm_sub_ps(_mm_set1_ps(3.0f), nr), _mm_mul_ps(_mm_set1_ps(0.5f), iv));
		}
		
	#endif
	
	#if TS_SSE >= 2
		
		/// swizzle components
		#define _mm_swizzle_epi32(V, X, Y, Z, W) _mm_shuffle_epi32(V, (_MM_SWIZZLE_ ## W << 6) | (_MM_SWIZZLE_ ## Z << 4) | (_MM_SWIZZLE_ ## Y << 2) | (_MM_SWIZZLE_ ## X))
		#define _mm_swizzle_pd(V0, V1, X, Y) _mm_shuffle_pd(V0, V1, (_MM_SWIZZLE_ ## Y << 1) | (_MM_SWIZZLE_ ## X))
		
		/// math functions
		TS_INLINE __m128d _mm_rcp_pd(__m128d v) {
			return _mm_div_pd(_mm_set1_pd(1.0), v);
		}
		
		TS_INLINE __m128d _mm_rsqrt_pd(__m128d v) {
			return _mm_div_pd(_mm_set1_pd(1.0), _mm_sqrt_pd(v));
		}
		
	#endif
	
	/**
	 * AVX utils
	 */
	#if TS_AVX >= 1
		
		/// swizzle components
		#if TS_AVX >= 2
			#define _mm256_swizzle_x_pd(V) _mm256_permute4x64_pd(V, 0x00)
			#define _mm256_swizzle_y_pd(V) _mm256_permute4x64_pd(V, 0x55)
			#define _mm256_swizzle_z_pd(V) _mm256_permute4x64_pd(V, 0xaa)
			#define _mm256_swizzle_w_pd(V) _mm256_permute4x64_pd(V, 0xff)
		#else
			#define _mm256_swizzle_x_pd(V) _mm256_permute_pd(_mm256_permute2f128_pd(V, V, 0x00), 0x00)
			#define _mm256_swizzle_y_pd(V) _mm256_permute_pd(_mm256_permute2f128_pd(V, V, 0x00), 0x0f)
			#define _mm256_swizzle_z_pd(V) _mm256_permute_pd(_mm256_permute2f128_pd(V, V, 0x11), 0x00)
			#define _mm256_swizzle_w_pd(V) _mm256_permute_pd(_mm256_permute2f128_pd(V, V, 0x11), 0x0f)
		#endif
		
		/// vector functions
		TS_INLINE __m256d _mm256_dot4_pd(__m256d v0, __m256d v1) {
			__m256d v = _mm256_mul_pd(v0, v1);
			v = _mm256_add_pd(_mm256_permute2f128_pd(v, v, 0x01), v);
			return _mm256_hadd_pd(v, v);
		}
		
		/// math functions
		TS_INLINE __m256 _mm256_rcp_ps_nr(__m256 v) {
			__m256 iv = _mm256_rcp_ps(v);
			return _mm256_sub_ps(_mm256_add_ps(iv, iv), _mm256_mul_ps(_mm256_mul_ps(iv, iv), v));
		}
		
		TS_INLINE __m256 _mm256_rsqrt_ps_nr(__m256 v) {
			__m256 iv = _mm256_rsqrt_ps(v);
			__m256 nr = _mm256_mul_ps(_mm256_mul_ps(iv, iv), v);
			return _mm256_mul_ps(_mm256_sub_ps(_mm256_set1_ps(3.0f), nr), _mm256_mul_ps(_mm256_set1_ps(0.5f), iv));
		}
		
		TS_INLINE __m256d _mm256_rcp_pd(__m256d v) {
			return _mm256_div_pd(_mm256_set1_pd(1.0), v);
		}
		
		TS_INLINE __m256d _mm256_rsqrt_pd(__m256d v) {
			return _mm256_div_pd(_mm256_set1_pd(1.0), _mm256_sqrt_pd(v));
		}
		
	#endif
	
	#if TS_AVX >= 2
		
		/// swizzle components
		#define _mm256_swizzle_pd(V, X, Y, Z, W) _mm256_permute4x64_pd(V, (_MM_SWIZZLE_ ## W << 6) | (_MM_SWIZZLE_ ## Z << 4) | (_MM_SWIZZLE_ ## Y << 2) | (_MM_SWIZZLE_ ## X))
		
	#endif
	
	/**
	 * NEON utils
	 */
	#if TS_NEON
		
		/// vector functions
		TS_INLINE ::float32x4_t vdot4q_f32(::float32x4_t v0, ::float32x4_t v1) {
			::float32x4_t v = vmulq_f32(v0, v1);
			v = vaddq_f32(v, vcombine_f32(vget_high_f32(v), vget_low_f32(v)));
			return vaddq_f32(v, vrev64q_f32(v));
		}
		
		/// math functions
		TS_INLINE ::float32x4_t vrcpq_f32(::float32x4_t v) {
			::float32x4_t iv = vrecpeq_f32(v);
			::float32x4_t nr = vmulq_f32(vrecpsq_f32(v, iv), iv);
			return vmulq_f32(vrecpsq_f32(v, nr), nr);
		}
		
		#ifndef vdivq_f32
			TS_INLINE ::float32x4_t vdivq_f32(::float32x4_t v0, ::float32x4_t v1) {
				return vmulq_f32(v0, vrcpq_f32(v1));
			}
		#endif
		
		TS_INLINE ::float32x4_t vrsqrtq_f32(::float32x4_t v) {
			::float32x4_t iv = vrsqrteq_f32(v);
			::float32x4_t nr = vmulq_f32(vrsqrtsq_f32(vmulq_f32(v, iv), iv), iv);
			return vmulq_f32(vrsqrtsq_f32(vmulq_f32(v, nr), nr), nr);
		}
		
		#ifndef vsqrtq_f32
			TS_INLINE ::float32x4_t vsqrtq_f32(::float32x4_t v) {
				return vmulq_f32(v, vrsqrtq_f32(vmaxq_f32(v, vdupq_n_f32(1e-16f))));
			}
		#endif
		
		/// comparison functions
		TS_INLINE uint32_t vmaskq_u32(::uint32x4_t v) {
			v = vandq_u32(v, vsetq_u32(0x01, 0x02, 0x04, 0x08));
			::uint32x2_t m = vorr_u32(vget_high_u32(v), vget_low_u32(v));
			return vget_lane_u32(vpadd_u32(m, m), 0);
		}
		
	#endif
	
	/*****************************************************************************\
	 *
	 * int16x8_t
	 *
	\*****************************************************************************/
	
	/**
	 * Vector of eight int16_t components
	 */
	struct TS_ALIGNAS16 int16x8_t {
		
		int16x8_t() { }
		explicit int16x8_t(const int32x8_t &v);
		explicit int16x8_t(const int16_t *v) { set(v); }
		int16x8_t(const int32x4_t &v0, const int32x4_t &v1);
		#if TS_SSE >= 2
			int16x8_t(const int16x8_t &v) : vec(v.vec) { }
			explicit int16x8_t(__m128i v) : vec(v) { }
			explicit int16x8_t(int16_t v) : vec(_mm_set1_epi16(v)) { }
			int16x8_t(int16_t x0, int16_t y0, int16_t z0, int16_t w0, int16_t x1, int16_t y1, int16_t z1, int16_t w1) : vec(_mm_setr_epi16(x0, y0, z0, w0, x1, y1, z1, w1)) { }
		#elif TS_NEON
			int16x8_t(const int16x8_t &v) : vec(v.vec) { }
			explicit int16x8_t(::int16x8_t v) : vec(v) { }
			explicit int16x8_t(int16_t v) : vec(vdupq_n_s16(v)) { }
			int16x8_t(int16_t x0, int16_t y0, int16_t z0, int16_t w0, int16_t x1, int16_t y1, int16_t z1, int16_t w1) : vec(vsetq_s16(x0, y0, z0, w0, x1, y1, z1, w1)) { }
		#else
			explicit int16x8_t(int16_t v) : x0(v), y0(v), z0(v), w0(v), x1(v), y1(v), z1(v), w1(v) { }
			int16x8_t(int16_t x0, int16_t y0, int16_t z0, int16_t w0, int16_t x1, int16_t y1, int16_t z1, int16_t w1) : x0(x0), y0(y0), z0(z0), w0(w0), x1(x1), y1(y1), z1(z1), w1(w1) { }
		#endif
		
		/// cast vector data
		TS_INLINE int32x4_t asi32x4() const;
		TS_INLINE uint16x8_t asu16x8() const;
		TS_INLINE uint32x4_t asu32x4() const;
		TS_INLINE float16x8_t asf16x8() const;
		TS_INLINE float32x4_t asf32x4() const;
		
		/// update vector data
		TS_INLINE void set(const int16x8_t &v) {
			#if TS_SSE >= 2
				vec = v.vec;
			#elif TS_NEON
				vec = v.vec;
			#else
				x0 = v.x0; y0 = v.y0; z0 = v.z0; w0 = v.w0;
				x1 = v.x1; y1 = v.y1; z1 = v.z1; w1 = v.w1;
			#endif
		}
		TS_INLINE void set(int16_t X0, int16_t Y0, int16_t Z0, int16_t W0, int16_t X1, int16_t Y1, int16_t Z1, int16_t W1) {
			#if TS_SSE >= 2
				vec = _mm_setr_epi16(X0, Y0, Z0, W0, X1, Y1, Z1, W1);
			#elif TS_NEON
				vec = vsetq_s16(X0, Y0, Z0, W0, X1, Y1, Z1, W1);
			#else
				x0 = X0; y0 = Y0; z0 = Z0; w0 = W0;
				x1 = X1; y1 = Y1; z1 = Z1; w1 = W1;
			#endif
		}
		TS_INLINE void set(const int16_t *TS_RESTRICT v) {
			#if TS_SSE >= 2
				vec = _mm_castps_si128(_mm_load_ps((const float32_t*)v));
			#elif TS_NEON
				vec = _vld1q_s16(v);
			#else
				x0 = v[0]; y0 = v[1]; z0 = v[2]; w0 = v[3];
				x1 = v[4]; y1 = v[5]; z1 = v[6]; w1 = v[7];
			#endif
		}
		TS_INLINE void get(int16_t *TS_RESTRICT v) const {
			#if TS_SSE >= 2
				_mm_stream_ps((float32_t*)v, _mm_castsi128_ps(vec));
			#elif TS_NEON
				_vst1q_s16(v, vec);
			#else
				v[0] = x0; v[1] = y0; v[2] = z0; v[3] = w0;
				v[4] = x1; v[5] = y1; v[6] = z1; v[7] = w1;
			#endif
		}
		template <uint32_t Index> TS_INLINE void set(int16_t V) {
			#if TS_SSE >= 2
				vec = _mm_insert_epi16(vec, V, Index);
			#elif TS_NEON
				vec = _vsetq_lane_s16<Index>(V, vec);
			#else
				v[Index] = V;
			#endif
		}
		template <uint32_t Index> TS_INLINE int16_t get() const {
			#if TS_SSE >= 2
				return (int16_t)_mm_extract_epi16(vec, Index);
			#elif TS_NEON
				return _vgetq_lane_s16<Index>(vec);
			#else
				return v[Index];
			#endif
		}
		
		/// vector to scalar operators
		TS_INLINE int16x8_t &operator*=(int16_t v) {
			#if TS_SSE >= 2
				vec = _mm_mullo_epi16(vec, _mm_set1_epi16(v));
			#elif TS_NEON
				vec = vmulq_n_s16(vec, v);
			#else
				x0 *= v; y0 *= v; z0 *= v; w0 *= v; x1 *= v; y1 *= v; z1 *= v; w1 *= v;
			#endif
			return *this;
		}
		TS_INLINE int16x8_t &operator+=(int16_t v) {
			#if TS_SSE >= 2
				vec = _mm_add_epi16(vec, _mm_set1_epi16(v));
			#elif TS_NEON
				vec = vaddq_s16(vec, vdupq_n_s16(v));
			#else
				x0 += v; y0 += v; z0 += v; w0 += v; x1 += v; y1 += v; z1 += v; w1 += v;
			#endif
			return *this;
		}
		TS_INLINE int16x8_t &operator-=(int16_t v) {
			#if TS_SSE >= 2
				vec = _mm_sub_epi16(vec, _mm_set1_epi16(v));
			#elif TS_NEON
				vec = vsubq_s16(vec, vdupq_n_s16(v));
			#else
				x0 -= v; y0 -= v; z0 -= v; w0 -= v; x1 -= v; y1 -= v; z1 -= v; w1 -= v;
			#endif
			return *this;
		}
		TS_INLINE int16x8_t &operator&=(int16_t v) {
			#if TS_SSE >= 2
				vec = _mm_and_si128(vec, _mm_set1_epi16(v));
			#elif TS_NEON
				vec = vandq_s16(vec, vdupq_n_s16(v));
			#else
				x0 &= v; y0 &= v; z0 &= v; w0 &= v; x1 &= v; y1 &= v; z1 &= v; w1 &= v;
			#endif
			return *this;
		}
		TS_INLINE int16x8_t &operator|=(int16_t v) {
			#if TS_SSE >= 2
				vec = _mm_or_si128(vec, _mm_set1_epi16(v));
			#elif TS_NEON
				vec = vorrq_s16(vec, vdupq_n_s16(v));
			#else
				x0 |= v; y0 |= v; z0 |= v; w0 |= v; x1 |= v; y1 |= v; z1 |= v; w1 |= v;
			#endif
			return *this;
		}
		TS_INLINE int16x8_t &operator^=(int16_t v) {
			#if TS_SSE >= 2
				vec = _mm_xor_si128(vec, _mm_set1_epi16(v));
			#elif TS_NEON
				vec = veorq_s16(vec, vdupq_n_s16(v));
			#else
				x0 ^= v; y0 ^= v; z0 ^= v; w0 ^= v; x1 ^= v; y1 ^= v; z1 ^= v; w1 ^= v;
			#endif
			return *this;
		}
		TS_INLINE int16x8_t &operator<<=(int16_t v) {
			#if TS_SSE >= 2
				vec = _mm_slli_epi16(vec, v);
			#elif TS_NEON
				vec = vshlq_s16(vec, vdupq_n_s16(v));
			#else
				x0 <<= v; y0 <<= v; z0 <<= v; w0 <<= v; x1 <<= v; y1 <<= v; z1 <<= v; w1 <<= v;
			#endif
			return *this;
		}
		TS_INLINE int16x8_t &operator>>=(int16_t v) {
			#if TS_SSE >= 2
				vec = _mm_srai_epi16(vec, v);
			#elif TS_NEON
				vec = vshlq_s16(vec, vdupq_n_s16(-v));
			#else
				x0 >>= v; y0 >>= v; z0 >>= v; w0 >>= v; x1 >>= v; y1 >>= v; z1 >>= v; w1 >>= v;
			#endif
			return *this;
		}
		
		/// vector to vector operators
		TS_INLINE int16x8_t &operator*=(const int16x8_t &v) {
			#if TS_SSE >= 2
				vec = _mm_mullo_epi16(vec, v.vec);
			#elif TS_NEON
				vec = vmulq_s16(vec, v.vec);
			#else
				x0 *= v.x0; y0 *= v.y0; z0 *= v.z0; w0 *= v.w0; x1 *= v.x1; y1 *= v.y1; z1 *= v.z1; w1 *= v.w1;
			#endif
			return *this;
		}
		TS_INLINE int16x8_t &operator+=(const int16x8_t &v) {
			#if TS_SSE >= 2
				vec = _mm_add_epi16(vec, v.vec);
			#elif TS_NEON
				vec = vaddq_s16(vec, v.vec);
			#else
				x0 += v.x0; y0 += v.y0; z0 += v.z0; w0 += v.w0; x1 += v.x1; y1 += v.y1; z1 += v.z1; w1 += v.w1;
			#endif
			return *this;
		}
		TS_INLINE int16x8_t &operator-=(const int16x8_t &v) {
			#if TS_SSE >= 2
				vec = _mm_sub_epi16(vec, v.vec);
			#elif TS_NEON
				vec = vsubq_s16(vec, v.vec);
			#else
				x0 -= v.x0; y0 -= v.y0; z0 -= v.z0; w0 -= v.w0; x1 -= v.x1; y1 -= v.y1; z1 -= v.z1; w1 -= v.w1;
			#endif
			return *this;
		}
		TS_INLINE int16x8_t &operator&=(const int16x8_t &v) {
			#if TS_SSE >= 2
				vec = _mm_and_si128(vec, v.vec);
			#elif TS_NEON
				vec = vandq_s16(vec, v.vec);
			#else
				x0 &= v.x0; y0 &= v.y0; z0 &= v.z0; w0 &= v.w0; x1 &= v.x1; y1 &= v.y1; z1 &= v.z1; w1 &= v.w1;
			#endif
			return *this;
		}
		TS_INLINE int16x8_t &operator|=(const int16x8_t &v) {
			#if TS_SSE >= 2
				vec = _mm_or_si128(vec, v.vec);
			#elif TS_NEON
				vec = vorrq_s16(vec, v.vec);
			#else
				x0 |= v.x0; y0 |= v.y0; z0 |= v.z0; w0 |= v.w0; x1 |= v.x1; y1 |= v.y1; z1 |= v.z1; w1 |= v.w1;
			#endif
			return *this;
		}
		TS_INLINE int16x8_t &operator^=(const int16x8_t &v) {
			#if TS_SSE >= 2
				vec = _mm_xor_si128(vec, v.vec);
			#elif TS_NEON
				vec = veorq_s16(vec, v.vec);
			#else
				x0 ^= v.x0; y0 ^= v.y0; z0 ^= v.z0; w0 ^= v.w0; x1 ^= v.x1; y1 ^= v.y1; z1 ^= v.z1; w1 ^= v.w1;
			#endif
			return *this;
		}
		
		/// swizzle vector
		TS_INLINE int16x8_t xyzw10() const {
			#if TS_SSE >= 2
				return int16x8_t(_mm_swizzle_epi32(vec, Z, W, X, Y));
			#elif TS_NEON
				return int16x8_t(vcombine_s16(vget_high_s16(vec), vget_low_s16(vec)));
			#else
				return int16x8_t(x1, y1, z1, w1, x0, y0, z0, w0);
			#endif
		}
		TS_INLINE int16x8_t zwxy01() const {
			#if TS_SSE >= 2
				return int16x8_t(_mm_shufflehi_epi16(_mm_shufflelo_epi16(vec, 0x4e), 0x4e));
			#elif TS_NEON
				return int16x8_t(vreinterpretq_s16_s32(vrev64q_s32(vreinterpretq_s32_s16(vec))));
			#else
				return int16x8_t(z0, w0, x0, y0, z1, w1, x1, y1);
			#endif
		}
		TS_INLINE int16x8_t yxwz01() const {
			#if TS_SSE >= 2
				return int16x8_t(_mm_shufflehi_epi16(_mm_shufflelo_epi16(vec, 0xb1), 0xb1));
			#elif TS_NEON
				return int16x8_t(vrev32q_s16(vec));
			#else
				return int16x8_t(y0, x0, w0, z0, y1, x1, w1, z1);
			#endif
		}
		int32x4_t xyzw0() const;
		int32x4_t xyzw1() const;
		
		/// sum vector components
		TS_INLINE int16_t sum() const {
			#if TS_SSE >= 4
				__m128i temp = _mm_hadd_epi16(vec, vec);
				temp = _mm_hadd_epi16(temp, temp);
				temp = _mm_hadd_epi16(temp, temp);
				return (int16_t)_mm_extract_epi16(temp, 0);
			#elif TS_SSE >= 2
				__m128i temp = _mm_add_epi16(vec, _mm_swizzle_epi32(vec, Z, W, X, Y));
				temp = _mm_add_epi16(temp, _mm_shufflelo_epi16(temp, 0x4e));
				temp = _mm_add_epi16(temp, _mm_shufflelo_epi16(temp, 0xb1));
				return (int16_t)_mm_extract_epi16(temp, 0);
			#elif TS_NEON
				::int16x4_t temp = vadd_s16(vget_high_s16(vec), vget_low_s16(vec));
				temp = vadd_s16(temp, vrev64_s16(temp));
				temp = vadd_s16(temp, vrev32_s16(temp));
				return _vget_lane_s16<0>(temp);
			#else
				return x0 + y0 + z0 + w0 + x1 + y1 + z1 + w1;
			#endif
		}
		
		enum {
			Size = 8,
		};
		
		union {
			struct {
				int16_t x0, y0, z0, w0;
				int16_t x1, y1, z1, w1;
			};
			int16_t v[Size];
			#if TS_SSE >= 2
				__m128i vec;
			#elif TS_NEON
				::int16x8_t vec;
			#endif
		};
	};
	
	/// unary operators
	TS_INLINE int16x8_t operator-(const int16x8_t &v) {
		#if TS_SSE >= 4
			return int16x8_t(_mm_sign_epi16(v.vec, _mm_set1_epi16(-1)));
		#elif TS_SSE >= 2
			return int16x8_t(_mm_sub_epi16(_mm_set1_epi16(0), v.vec));
		#elif TS_NEON
			return int16x8_t(vnegq_s16(v.vec));
		#else
			return int16x8_t(-v.x0, -v.y0, -v.z0, -v.w0, -v.x1, -v.y1, -v.z1, -v.w1);
		#endif
	}
	
	/// vector to scalar operators
	TS_INLINE int16x8_t operator*(const int16x8_t &v0, int16_t v1) {
		#if TS_SSE >= 2
			return int16x8_t(_mm_mullo_epi16(v0.vec, _mm_set1_epi16(v1)));
		#elif TS_NEON
			return int16x8_t(vmulq_n_s16(v0.vec, v1));
		#else
			return int16x8_t(v0.x0 * v1, v0.y0 * v1, v0.z0 * v1, v0.w0 * v1, v0.x1 * v1, v0.y1 * v1, v0.z1 * v1, v0.w1 * v1);
		#endif
	}
	TS_INLINE int16x8_t operator+(const int16x8_t &v0, int16_t v1) {
		#if TS_SSE >= 2
			return int16x8_t(_mm_add_epi16(v0.vec, _mm_set1_epi16(v1)));
		#elif TS_NEON
			return int16x8_t(vaddq_s16(v0.vec, vdupq_n_s16(v1)));
		#else
			return int16x8_t(v0.x0 + v1, v0.y0 + v1, v0.z0 + v1, v0.w0 + v1, v0.x1 + v1, v0.y1 + v1, v0.z1 + v1, v0.w1 + v1);
		#endif
	}
	TS_INLINE int16x8_t operator-(const int16x8_t &v0, int16_t v1) {
		#if TS_SSE >= 2
			return int16x8_t(_mm_sub_epi16(v0.vec, _mm_set1_epi16(v1)));
		#elif TS_NEON
			return int16x8_t(vsubq_s16(v0.vec, vdupq_n_s16(v1)));
		#else
			return int16x8_t(v0.x0 - v1, v0.y0 - v1, v0.z0 - v1, v0.w0 - v1, v0.x1 - v1, v0.y1 - v1, v0.z1 - v1, v0.w1 - v1);
		#endif
	}
	TS_INLINE int16x8_t operator&(const int16x8_t &v0, int16_t v1) {
		#if TS_SSE >= 2
			return int16x8_t(_mm_and_si128(v0.vec, _mm_set1_epi16(v1)));
		#elif TS_NEON
			return int16x8_t(vandq_s16(v0.vec, vdupq_n_s16(v1)));
		#else
			return int16x8_t(v0.x0 & v1, v0.y0 & v1, v0.z0 & v1, v0.w0 & v1, v0.x1 & v1, v0.y1 & v1, v0.z1 & v1, v0.w1 & v1);
		#endif
	}
	TS_INLINE int16x8_t operator|(const int16x8_t &v0, int16_t v1) {
		#if TS_SSE >= 2
			return int16x8_t(_mm_or_si128(v0.vec, _mm_set1_epi16(v1)));
		#elif TS_NEON
			return int16x8_t(vorrq_s16(v0.vec, vdupq_n_s16(v1)));
		#else
			return int16x8_t(v0.x0 | v1, v0.y0 | v1, v0.z0 | v1, v0.w0 | v1, v0.x1 | v1, v0.y1 | v1, v0.z1 | v1, v0.w1 | v1);
		#endif
	}
	TS_INLINE int16x8_t operator^(const int16x8_t &v0, int16_t v1) {
		#if TS_SSE >= 2
			return int16x8_t(_mm_xor_si128(v0.vec, _mm_set1_epi16(v1)));
		#elif TS_NEON
			return int16x8_t(veorq_s16(v0.vec, vdupq_n_s16(v1)));
		#else
			return int16x8_t(v0.x0 ^ v1, v0.y0 ^ v1, v0.z0 ^ v1, v0.w0 ^ v1, v0.x1 ^ v1, v0.y1 ^ v1, v0.z1 ^ v1, v0.w1 ^ v1);
		#endif
	}
	TS_INLINE int16x8_t operator<<(const int16x8_t &v0, int16_t v1) {
		#if TS_SSE >= 2
			return int16x8_t(_mm_slli_epi16(v0.vec, v1));
		#elif TS_NEON
			return int16x8_t(vshlq_s16(v0.vec, vdupq_n_s16(v1)));
		#else
			return int16x8_t(v0.x0 << v1, v0.y0 << v1, v0.z0 << v1, v0.w0 << v1, v0.x1 << v1, v0.y1 << v1, v0.z1 << v1, v0.w1 << v1);
		#endif
	}
	TS_INLINE int16x8_t operator>>(const int16x8_t &v0, int16_t v1) {
		#if TS_SSE >= 2
			return int16x8_t(_mm_srai_epi16(v0.vec, v1));
		#elif TS_NEON
			return int16x8_t(vshlq_s16(v0.vec, vdupq_n_s16(-v1)));
		#else
			return int16x8_t(v0.x0 >> v1, v0.y0 >> v1, v0.z0 >> v1, v0.w0 >> v1, v0.x1 >> v1, v0.y1 >> v1, v0.z1 >> v1, v0.w1 >> v1);
		#endif
	}
	
	/// vector to vector operators
	TS_INLINE int16x8_t operator*(const int16x8_t &v0, const int16x8_t &v1) {
		#if TS_SSE >= 2
			return int16x8_t(_mm_mullo_epi16(v0.vec, v1.vec));
		#elif TS_NEON
			return int16x8_t(vmulq_s16(v0.vec, v1.vec));
		#else
			return int16x8_t(v0.x0 * v1.x0, v0.y0 * v1.y0, v0.z0 * v1.z0, v0.w0 * v1.w0, v0.x1 * v1.x1, v0.y1 * v1.y1, v0.z1 * v1.z1, v0.w1 * v1.w1);
		#endif
	}
	TS_INLINE int16x8_t operator+(const int16x8_t &v0, const int16x8_t &v1) {
		#if TS_SSE >= 2
			return int16x8_t(_mm_add_epi16(v0.vec, v1.vec));
		#elif TS_NEON
			return int16x8_t(vaddq_s16(v0.vec, v1.vec));
		#else
			return int16x8_t(v0.x0 + v1.x0, v0.y0 + v1.y0, v0.z0 + v1.z0, v0.w0 + v1.w0, v0.x1 + v1.x1, v0.y1 + v1.y1, v0.z1 + v1.z1, v0.w1 + v1.w1);
		#endif
	}
	TS_INLINE int16x8_t operator-(const int16x8_t &v0, const int16x8_t &v1) {
		#if TS_SSE >= 2
			return int16x8_t(_mm_sub_epi16(v0.vec, v1.vec));
		#elif TS_NEON
			return int16x8_t(vsubq_s16(v0.vec, v1.vec));
		#else
			return int16x8_t(v0.x0 - v1.x0, v0.y0 - v1.y0, v0.z0 - v1.z0, v0.w0 - v1.w0, v0.x1 - v1.x1, v0.y1 - v1.y1, v0.z1 - v1.z1, v0.w1 - v1.w1);
		#endif
	}
	TS_INLINE int16x8_t operator&(const int16x8_t &v0, const int16x8_t &v1) {
		#if TS_SSE >= 2
			return int16x8_t(_mm_and_si128(v0.vec, v1.vec));
		#elif TS_NEON
			return int16x8_t(vandq_s16(v0.vec, v1.vec));
		#else
			return int16x8_t(v0.x0 & v1.x0, v0.y0 & v1.y0, v0.z0 & v1.z0, v0.w0 & v1.w0, v0.x1 & v1.x1, v0.y1 & v1.y1, v0.z1 & v1.z1, v0.w1 & v1.w1);
		#endif
	}
	TS_INLINE int16x8_t operator|(const int16x8_t &v0, const int16x8_t &v1) {
		#if TS_SSE >= 2
			return int16x8_t(_mm_or_si128(v0.vec, v1.vec));
		#elif TS_NEON
			return int16x8_t(vorrq_s16(v0.vec, v1.vec));
		#else
			return int16x8_t(v0.x0 | v1.x0, v0.y0 | v1.y0, v0.z0 | v1.z0, v0.w0 | v1.w0, v0.x1 | v1.x1, v0.y1 | v1.y1, v0.z1 | v1.z1, v0.w1 | v1.w1);
		#endif
	}
	TS_INLINE int16x8_t operator^(const int16x8_t &v0, const int16x8_t &v1) {
		#if TS_SSE >= 2
			return int16x8_t(_mm_xor_si128(v0.vec, v1.vec));
		#elif TS_NEON
			return int16x8_t(veorq_s16(v0.vec, v1.vec));
		#else
			return int16x8_t(v0.x0 ^ v1.x0, v0.y0 ^ v1.y0, v0.z0 ^ v1.z0, v0.w0 ^ v1.w0, v0.x1 ^ v1.x1, v0.y1 ^ v1.y1, v0.z1 ^ v1.z1, v0.w1 ^ v1.w1);
		#endif
	}
	
	/// min/max functions
	TS_INLINE int16x8_t min(const int16x8_t &v0, const int16x8_t &v1) {
		#if TS_SSE >= 2
			return int16x8_t(_mm_min_epi16(v0.vec, v1.vec));
		#elif TS_NEON
			return int16x8_t(vminq_s16(v0.vec, v1.vec));
		#else
			return int16x8_t(min(v0.x0, v1.x0), min(v0.y0, v1.y0), min(v0.z0, v1.z0), min(v0.w0, v1.w0), min(v0.x1, v1.x1), min(v0.y1, v1.y1), min(v0.z1, v1.z1), min(v0.w1, v1.w1));
		#endif
	}
	TS_INLINE int16x8_t max(const int16x8_t &v0, const int16x8_t &v1) {
		#if TS_SSE >= 2
			return int16x8_t(_mm_max_epi16(v0.vec, v1.vec));
		#elif TS_NEON
			return int16x8_t(vmaxq_s16(v0.vec, v1.vec));
		#else
			return int16x8_t(max(v0.x0, v1.x0), max(v0.y0, v1.y0), max(v0.z0, v1.z0), max(v0.w0, v1.w0), max(v0.x1, v1.x1), max(v0.y1, v1.y1), max(v0.z1, v1.z1), max(v0.w1, v1.w1));
		#endif
	}
	
	/// range functions
	TS_INLINE int16x8_t clamp(const int16x8_t &v, int16_t v0, int16_t v1) {
		return min(max(v, int16x8_t(v0)), int16x8_t(v1));
	}
	TS_INLINE int16x8_t clamp(const int16x8_t &v, const int16x8_t &v0, const int16x8_t &v1) {
		return min(max(v, v0), v1);
	}
	
	/// select functions
	TS_INLINE int16x8_t select(const int16x8_t &v0, const int16x8_t &v1, const int16x8_t &s) {
		#if TS_SSE >= 2
			return int16x8_t(_mm_xor_si128(v0.vec, _mm_and_si128(_mm_xor_si128(v0.vec, v1.vec), _mm_srai_epi16(s.vec, 15))));
		#elif TS_NEON
			return int16x8_t(vbslq_s16(vcgeq_s16(s.vec, vdupq_n_s16(0)), v0.vec, v1.vec));
		#else
			return int16x8_t(select(v0.x0, v1.x0, s.x0), select(v0.y0, v1.y0, s.y0), select(v0.z0, v1.z0, s.z0), select(v0.w0, v1.w0, s.w0), select(v0.x1, v1.x1, s.x1), select(v0.y1, v1.y1, s.y1), select(v0.z1, v1.z1, s.z1), select(v0.w1, v1.w1, s.w1));
		#endif
	}
	TS_INLINE int16x8_t select(const int16x8_t &v0, const int16x8_t &v1, int16_t s) {
		return select(v0, v1, int16x8_t(s));
	}
	
	/*****************************************************************************\
	 *
	 * int32x4_t
	 *
	\*****************************************************************************/
	
	/**
	 * Vector of four int32_t components
	 */
	struct TS_ALIGNAS16 int32x4_t {
		
		int32x4_t() { }
		explicit int32x4_t(const uint32x4_t &v);
		explicit int32x4_t(const float32x4_t &v);
		explicit int32x4_t(const float64x4_t &v);
		explicit int32x4_t(const int32_t *v) { set(v); }
		int32x4_t(const int32_t *v, int32_t w) { set(v, w); }
		#if TS_SSE >= 2
			int32x4_t(const int32x4_t &v) : vec(v.vec) { }
			explicit int32x4_t(__m128i v) : vec(v) { }
			explicit int32x4_t(int32_t v) : vec(_mm_set1_epi32(v)) { }
			int32x4_t(int32_t x, int32_t y, int32_t z, int32_t w = 0) : vec(_mm_setr_epi32(x, y, z, w)) { }
		#elif TS_NEON
			int32x4_t(const int32x4_t &v) : vec(v.vec) { }
			explicit int32x4_t(::int32x4_t v) : vec(v) { }
			explicit int32x4_t(int32_t v) : vec(vdupq_n_s32(v)) { }
			int32x4_t(int32_t x, int32_t y, int32_t z, int32_t w = 0) : vec(vsetq_s32(x, y, z, w)) { }
		#else
			explicit int32x4_t(int32_t v) : x(v), y(v), z(v), w(v) { }
			int32x4_t(int32_t x, int32_t y, int32_t z, int32_t w = 0) : x(x), y(y), z(z), w(w) { }
		#endif
		
		/// cast vector data
		TS_INLINE int16x8_t asi16x8() const {
			#if TS_SSE >= 2
				return int16x8_t(vec);
			#elif TS_NEON
				return int16x8_t(vreinterpretq_s16_s32(vec));
			#else
				return int16x8_t((int16_t*)v);
			#endif
		}
		TS_INLINE uint16x8_t asu16x8() const;
		TS_INLINE uint32x4_t asu32x4() const;
		TS_INLINE float16x8_t asf16x8() const;
		TS_INLINE float32x4_t asf32x4() const;
		
		/// update vector data
		TS_INLINE void set(const int32x4_t &v) {
			#if TS_SSE >= 2
				vec = v.vec;
			#elif TS_NEON
				vec = v.vec;
			#else
				x = v.x; y = v.y; z = v.z; w = v.w;
			#endif
		}
		TS_INLINE void set(int32_t X, int32_t Y, int32_t Z, int32_t W) {
			#if TS_SSE >= 2
				vec = _mm_setr_epi32(X, Y, Z, W);
			#elif TS_NEON
				vec = vsetq_s32(X, Y, Z, W);
			#else
				x = X; y = Y; z = Z; w = W;
			#endif
		}
		TS_INLINE void set(const int32_t *TS_RESTRICT v, int32_t W) {
			#if TS_SSE >= 2
				vec = _mm_setr_epi32(v[0], v[1], v[2], W);
			#elif TS_NEON
				vec = vsetq_s32(v[0], v[1], v[2], W);
			#else
				x = v[0]; y = v[1]; z = v[2]; w = W;
			#endif
		}
		TS_INLINE void set(const int32_t *TS_RESTRICT v) {
			#if TS_SSE >= 2
				vec = _mm_castps_si128(_mm_load_ps((const float32_t*)v));
			#elif TS_NEON
				vec = _vld1q_s32(v);
			#else
				x = v[0]; y = v[1]; z = v[2]; w = v[3];
			#endif
		}
		TS_INLINE void get(int32_t *TS_RESTRICT v) const {
			#if TS_SSE >= 2
				_mm_stream_ps((float32_t*)v, _mm_castsi128_ps(vec));
			#elif TS_NEON
				_vst1q_s32(v, vec);
			#else
				v[0] = x; v[1] = y; v[2] = z; v[3] = w;
			#endif
		}
		template <uint32_t Index> TS_INLINE void set(int32_t V) {
			#if TS_SSE >= 4
				vec = _mm_insert_epi32(vec, V, Index);
			#elif TS_NEON
				vec = _vsetq_lane_s32<Index>(V, vec);
			#else
				v[Index] = V;
			#endif
		}
		template <uint32_t Index> TS_INLINE int32_t get() const {
			#if TS_SSE >= 4
				return _mm_extract_epi32(vec, Index);
			#elif TS_NEON
				return _vgetq_lane_s32<Index>(vec);
			#else
				return v[Index];
			#endif
		}
		template <uint32_t Index> TS_INLINE int32x4_t get4() const {
			#if TS_SSE >= 2
				return int32x4_t(_mm_shuffle_epi32(vec, (Index << 6) | (Index << 4) | (Index << 2) | Index));
			#elif TS_NEON
				return int32x4_t(vdupq_n_s32(_vgetq_lane_s32<Index>(vec)));
			#else
				return int32x4_t(v[Index]);
			#endif
		}
		
		/// vector to scalar operators
		TS_INLINE int32x4_t &operator*=(int32_t v) {
			#if TS_SSE >= 4
				vec = _mm_mullo_epi32(vec, _mm_set1_epi32(v));
			#elif TS_NEON
				vec = vmulq_n_s32(vec, v);
			#else
				x *= v; y *= v; z *= v; w *= v;
			#endif
			return *this;
		}
		TS_INLINE int32x4_t &operator+=(int32_t v) {
			#if TS_SSE >= 2
				vec = _mm_add_epi32(vec, _mm_set1_epi32(v));
			#elif TS_NEON
				vec = vaddq_s32(vec, vdupq_n_s32(v));
			#else
				x += v; y += v; z += v; w += v;
			#endif
			return *this;
		}
		TS_INLINE int32x4_t &operator-=(int32_t v) {
			#if TS_SSE >= 2
				vec = _mm_sub_epi32(vec, _mm_set1_epi32(v));
			#elif TS_NEON
				vec = vsubq_s32(vec, vdupq_n_s32(v));
			#else
				x -= v; y -= v; z -= v; w -= v;
			#endif
			return *this;
		}
		TS_INLINE int32x4_t &operator&=(int32_t v) {
			#if TS_SSE >= 2
				vec = _mm_and_si128(vec, _mm_set1_epi32(v));
			#elif TS_NEON
				vec = vandq_s32(vec, vdupq_n_s32(v));
			#else
				x &= v; y &= v; z &= v; w &= v;
			#endif
			return *this;
		}
		TS_INLINE int32x4_t &operator|=(int32_t v) {
			#if TS_SSE >= 2
				vec = _mm_or_si128(vec, _mm_set1_epi32(v));
			#elif TS_NEON
				vec = vorrq_s32(vec, vdupq_n_s32(v));
			#else
				x |= v; y |= v; z |= v; w |= v;
			#endif
			return *this;
		}
		TS_INLINE int32x4_t &operator^=(int32_t v) {
			#if TS_SSE >= 2
				vec = _mm_xor_si128(vec, _mm_set1_epi32(v));
			#elif TS_NEON
				vec = veorq_s32(vec, vdupq_n_s32(v));
			#else
				x ^= v; y ^= v; z ^= v; w ^= v;
			#endif
			return *this;
		}
		TS_INLINE int32x4_t &operator<<=(int32_t v) {
			#if TS_SSE >= 2
				vec = _mm_slli_epi32(vec, v);
			#elif TS_NEON
				vec = vshlq_s32(vec, vdupq_n_s32(v));
			#else
				x <<= v; y <<= v; z <<= v; w <<= v;
			#endif
			return *this;
		}
		TS_INLINE int32x4_t &operator>>=(int32_t v) {
			#if TS_SSE >= 2
				vec = _mm_srai_epi32(vec, v);
			#elif TS_NEON
				vec = vshlq_s32(vec, vdupq_n_s32(-v));
			#else
				x >>= v; y >>= v; z >>= v; w >>= v;
			#endif
			return *this;
		}
		
		/// vector to vector operators
		TS_INLINE int32x4_t &operator*=(const int32x4_t &v) {
			#if TS_SSE >= 4
				vec = _mm_mullo_epi32(vec, v.vec);
			#elif TS_NEON
				vec = vmulq_s32(vec, v.vec);
			#else
				x *= v.x; y *= v.y; z *= v.z; w *= v.w;
			#endif
			return *this;
		}
		TS_INLINE int32x4_t &operator+=(const int32x4_t &v) {
			#if TS_SSE >= 2
				vec = _mm_add_epi32(vec, v.vec);
			#elif TS_NEON
				vec = vaddq_s32(vec, v.vec);
			#else
				x += v.x; y += v.y; z += v.z; w += v.w;
			#endif
			return *this;
		}
		TS_INLINE int32x4_t &operator-=(const int32x4_t &v) {
			#if TS_SSE >= 2
				vec = _mm_sub_epi32(vec, v.vec);
			#elif TS_NEON
				vec = vsubq_s32(vec, v.vec);
			#else
				x -= v.x; y -= v.y; z -= v.z; w -= v.w;
			#endif
			return *this;
		}
		TS_INLINE int32x4_t &operator&=(const int32x4_t &v) {
			#if TS_SSE >= 2
				vec = _mm_and_si128(vec, v.vec);
			#elif TS_NEON
				vec = vandq_s32(vec, v.vec);
			#else
				x &= v.x; y &= v.y; z &= v.z; w &= v.w;
			#endif
			return *this;
		}
		TS_INLINE int32x4_t &operator|=(const int32x4_t &v) {
			#if TS_SSE >= 2
				vec = _mm_or_si128(vec, v.vec);
			#elif TS_NEON
				vec = vorrq_s32(vec, v.vec);
			#else
				x |= v.x; y |= v.y; z |= v.z; w |= v.w;
			#endif
			return *this;
		}
		TS_INLINE int32x4_t &operator^=(const int32x4_t &v) {
			#if TS_SSE >= 2
				vec = _mm_xor_si128(vec, v.vec);
			#elif TS_NEON
				vec = veorq_s32(vec, v.vec);
			#else
				x ^= v.x; y ^= v.y; z ^= v.z; w ^= v.w;
			#endif
			return *this;
		}
		
		/// swizzle vector
		TS_INLINE int32x4_t zwxy() const {
			#if TS_SSE >= 2
				return int32x4_t(_mm_swizzle_epi32(vec, Z, W, X, Y));
			#elif TS_NEON
				return int32x4_t(vcombine_s32(vget_high_s32(vec), vget_low_s32(vec)));
			#else
				return int32x4_t(z, w, x, y);
			#endif
		}
		TS_INLINE int32x4_t yxwz() const {
			#if TS_SSE >= 2
				return int32x4_t(_mm_swizzle_epi32(vec, Y, X, W, Z));
			#elif TS_NEON
				return int32x4_t(vrev64q_s32(vec));
			#else
				return int32x4_t(y, x, w, z);
			#endif
		}
		
		/// sum vector components
		TS_INLINE int32_t sum() const {
			#if TS_SSE >= 4
				__m128i temp = _mm_hadd_epi32(vec, vec);
				temp = _mm_hadd_epi32(temp, temp);
				return _mm_extract_epi32(temp, 0);
			#elif TS_SSE >= 2
				__m128i temp = _mm_add_epi32(vec, _mm_swizzle_epi32(vec, Z, W, X, Y));
				temp = _mm_add_epi32(temp, _mm_swizzle_epi32(temp, Y, X, W, Z));
				return (int32_t)f32u32(_mm_cvtss_f32(_mm_castsi128_ps(temp))).u;
			#elif TS_NEON
				::int32x2_t temp = vadd_s32(vget_high_s32(vec), vget_low_s32(vec));
				temp = vadd_s32(temp, vrev64_s32(temp));
				return _vget_lane_s32<0>(temp);
			#else
				return x + y + z + w;
			#endif
		}
		
		enum {
			Size = 4,
		};
		
		union {
			struct {
				int32_t x, y, z, w;
			};
			int32_t v[Size];
			#if TS_SSE >= 2
				__m128i vec;
			#elif TS_NEON
				::int32x4_t vec;
			#endif
		};
	};
	
	/// unary operators
	TS_INLINE int32x4_t operator-(const int32x4_t &v) {
		#if TS_SSE >= 4
			return int32x4_t(_mm_sign_epi32(v.vec, _mm_set1_epi32(-1)));
		#elif TS_SSE >= 2
			return int32x4_t(_mm_sub_epi32(_mm_set1_epi32(0), v.vec));
		#elif TS_NEON
			return int32x4_t(vnegq_s32(v.vec));
		#else
			return int32x4_t(-v.x, -v.y, -v.z, -v.w);
		#endif
	}
	
	/// vector to scalar operators
	TS_INLINE int32x4_t operator*(const int32x4_t &v0, int32_t v1) {
		#if TS_SSE >= 4
			return int32x4_t(_mm_mullo_epi32(v0.vec, _mm_set1_epi32(v1)));
		#elif TS_NEON
			return int32x4_t(vmulq_n_s32(v0.vec, v1));
		#else
			return int32x4_t(v0.x * v1, v0.y * v1, v0.z * v1, v0.w * v1);
		#endif
	}
	TS_INLINE int32x4_t operator+(const int32x4_t &v0, int32_t v1) {
		#if TS_SSE >= 2
			return int32x4_t(_mm_add_epi32(v0.vec, _mm_set1_epi32(v1)));
		#elif TS_NEON
			return int32x4_t(vaddq_s32(v0.vec, vdupq_n_s32(v1)));
		#else
			return int32x4_t(v0.x + v1, v0.y + v1, v0.z + v1, v0.w + v1);
		#endif
	}
	TS_INLINE int32x4_t operator-(const int32x4_t &v0, int32_t v1) {
		#if TS_SSE >= 2
			return int32x4_t(_mm_sub_epi32(v0.vec, _mm_set1_epi32(v1)));
		#elif TS_NEON
			return int32x4_t(vsubq_s32(v0.vec, vdupq_n_s32(v1)));
		#else
			return int32x4_t(v0.x - v1, v0.y - v1, v0.z - v1, v0.w - v1);
		#endif
	}
	TS_INLINE int32x4_t operator&(const int32x4_t &v0, int32_t v1) {
		#if TS_SSE >= 2
			return int32x4_t(_mm_and_si128(v0.vec, _mm_set1_epi32(v1)));
		#elif TS_NEON
			return int32x4_t(vandq_s32(v0.vec, vdupq_n_s32(v1)));
		#else
			return int32x4_t(v0.x & v1, v0.y & v1, v0.z & v1, v0.w & v1);
		#endif
	}
	TS_INLINE int32x4_t operator|(const int32x4_t &v0, int32_t v1) {
		#if TS_SSE >= 2
			return int32x4_t(_mm_or_si128(v0.vec, _mm_set1_epi32(v1)));
		#elif TS_NEON
			return int32x4_t(vorrq_s32(v0.vec, vdupq_n_s32(v1)));
		#else
			return int32x4_t(v0.x | v1, v0.y | v1, v0.z | v1, v0.w | v1);
		#endif
	}
	TS_INLINE int32x4_t operator^(const int32x4_t &v0, int32_t v1) {
		#if TS_SSE >= 2
			return int32x4_t(_mm_xor_si128(v0.vec, _mm_set1_epi32(v1)));
		#elif TS_NEON
			return int32x4_t(veorq_s32(v0.vec, vdupq_n_s32(v1)));
		#else
			return int32x4_t(v0.x ^ v1, v0.y ^ v1, v0.z ^ v1, v0.w ^ v1);
		#endif
	}
	TS_INLINE int32x4_t operator<<(const int32x4_t &v0, int32_t v1) {
		#if TS_SSE >= 2
			return int32x4_t(_mm_slli_epi32(v0.vec, v1));
		#elif TS_NEON
			return int32x4_t(vshlq_s32(v0.vec, vdupq_n_s32(v1)));
		#else
			return int32x4_t(v0.x << v1, v0.y << v1, v0.z << v1, v0.w << v1);
		#endif
	}
	TS_INLINE int32x4_t operator>>(const int32x4_t &v0, int32_t v1) {
		#if TS_SSE >= 2
			return int32x4_t(_mm_srai_epi32(v0.vec, v1));
		#elif TS_NEON
			return int32x4_t(vshlq_s32(v0.vec, vdupq_n_s32(-v1)));
		#else
			return int32x4_t(v0.x >> v1, v0.y >> v1, v0.z >> v1, v0.w >> v1);
		#endif
	}
	
	/// vector to vector operators
	TS_INLINE int32x4_t operator*(const int32x4_t &v0, const int32x4_t &v1) {
		#if TS_SSE >= 4
			return int32x4_t(_mm_mullo_epi32(v0.vec, v1.vec));
		#elif TS_NEON
			return int32x4_t(vmulq_s32(v0.vec, v1.vec));
		#else
			return int32x4_t(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z, v0.w * v1.w);
		#endif
	}
	TS_INLINE int32x4_t operator+(const int32x4_t &v0, const int32x4_t &v1) {
		#if TS_SSE >= 2
			return int32x4_t(_mm_add_epi32(v0.vec, v1.vec));
		#elif TS_NEON
			return int32x4_t(vaddq_s32(v0.vec, v1.vec));
		#else
			return int32x4_t(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w);
		#endif
	}
	TS_INLINE int32x4_t operator-(const int32x4_t &v0, const int32x4_t &v1) {
		#if TS_SSE >= 2
			return int32x4_t(_mm_sub_epi32(v0.vec, v1.vec));
		#elif TS_NEON
			return int32x4_t(vsubq_s32(v0.vec, v1.vec));
		#else
			return int32x4_t(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w);
		#endif
	}
	TS_INLINE int32x4_t operator&(const int32x4_t &v0, const int32x4_t &v1) {
		#if TS_SSE >= 2
			return int32x4_t(_mm_and_si128(v0.vec, v1.vec));
		#elif TS_NEON
			return int32x4_t(vandq_s32(v0.vec, v1.vec));
		#else
			return int32x4_t(v0.x & v1.x, v0.y & v1.y, v0.z & v1.z, v0.w & v1.w);
		#endif
	}
	TS_INLINE int32x4_t operator|(const int32x4_t &v0, const int32x4_t &v1) {
		#if TS_SSE >= 2
			return int32x4_t(_mm_or_si128(v0.vec, v1.vec));
		#elif TS_NEON
			return int32x4_t(vorrq_s32(v0.vec, v1.vec));
		#else
			return int32x4_t(v0.x | v1.x, v0.y | v1.y, v0.z | v1.z, v0.w | v1.w);
		#endif
	}
	TS_INLINE int32x4_t operator^(const int32x4_t &v0, const int32x4_t &v1) {
		#if TS_SSE >= 2
			return int32x4_t(_mm_xor_si128(v0.vec, v1.vec));
		#elif TS_NEON
			return int32x4_t(veorq_s32(v0.vec, v1.vec));
		#else
			return int32x4_t(v0.x ^ v1.x, v0.y ^ v1.y, v0.z ^ v1.z, v0.w ^ v1.w);
		#endif
	}
	
	/// min/max functions
	TS_INLINE int32x4_t min(const int32x4_t &v0, const int32x4_t &v1) {
		#if TS_SSE >= 4
			return int32x4_t(_mm_min_epi32(v0.vec, v1.vec));
		#elif TS_NEON
			return int32x4_t(vminq_s32(v0.vec, v1.vec));
		#else
			return int32x4_t(min(v0.x, v1.x), min(v0.y, v1.y), min(v0.z, v1.z), min(v0.w, v1.w));
		#endif
	}
	TS_INLINE int32x4_t max(const int32x4_t &v0, const int32x4_t &v1) {
		#if TS_SSE >= 4
			return int32x4_t(_mm_max_epi32(v0.vec, v1.vec));
		#elif TS_NEON
			return int32x4_t(vmaxq_s32(v0.vec, v1.vec));
		#else
			return int32x4_t(max(v0.x, v1.x), max(v0.y, v1.y), max(v0.z, v1.z), max(v0.w, v1.w));
		#endif
	}
	
	/// range functions
	TS_INLINE int32x4_t clamp(const int32x4_t &v, int32_t v0, int32_t v1) {
		return min(max(v, int32x4_t(v0)), int32x4_t(v1));
	}
	TS_INLINE int32x4_t clamp(const int32x4_t &v, const int32x4_t &v0, const int32x4_t &v1) {
		return min(max(v, v0), v1);
	}
	
	/// select functions
	TS_INLINE int32x4_t select(const int32x4_t &v0, const int32x4_t &v1, const int32x4_t &s) {
		#if TS_AVX >= 1
			return int32x4_t(_mm_castps_si128(_mm_blendv_ps(_mm_castsi128_ps(v0.vec), _mm_castsi128_ps(v1.vec), _mm_castsi128_ps(s.vec))));
		#elif TS_SSE >= 2
			return int32x4_t(_mm_xor_si128(v0.vec, _mm_and_si128(_mm_xor_si128(v0.vec, v1.vec), _mm_srai_epi32(s.vec, 31))));
		#elif TS_NEON
			return int32x4_t(vbslq_s32(vcgeq_s32(s.vec, vdupq_n_s32(0)), v0.vec, v1.vec));
		#else
			return int32x4_t(select(v0.x, v1.x, s.x), select(v0.y, v1.y, s.y), select(v0.z, v1.z, s.z), select(v0.w, v1.w, s.w));
		#endif
	}
	TS_INLINE int32x4_t select(const int32x4_t &v0, const int32x4_t &v1, int32_t s) {
		return select(v0, v1, int32x4_t(s));
	}
	
	/*****************************************************************************\
	 *
	 * int32x8_t
	 *
	\*****************************************************************************/
	
	/**
	 * Vector of eight int32_t components
	 */
	struct TS_ALIGNAS32 int32x8_t {
		
		int32x8_t() { }
		explicit int32x8_t(const uint32x8_t &v);
		explicit int32x8_t(const float32x8_t &v);
		explicit int32x8_t(const float64x8_t &v);
		explicit int32x8_t(const int32_t *v) { set(v); }
		#if TS_AVX >= 1
			int32x8_t(const int32x8_t &v) : vec(v.vec) { }
			explicit int32x8_t(__m256i v) : vec(v) { }
			explicit int32x8_t(int32_t v) : vec(_mm256_set1_epi32(v)) { }
			int32x8_t(__m128i v0, __m128i v1) : vec(_mm256_setr_m128i(v0, v1)) { }
			#if TS_AVX >= 2
				explicit int32x8_t(const int16x8_t &v) : vec(_mm256_cvtepi16_epi32(v.vec)) { }
			#else
				explicit int32x8_t(const int16x8_t &v) : vec(_mm256_setr_m128i(_mm_cvtepi16_epi32(v.vec), _mm_cvtepi16_epi32(_mm_swizzle_epi32(v.vec, Z, W, Z, W)))) { }
			#endif
			int32x8_t(const int32x4_t &v0, const int32x4_t &v1) : vec(_mm256_setr_m128i(v0.vec, v1.vec)) { }
			int32x8_t(int32_t x0, int32_t y0, int32_t z0, int32_t w0, int32_t x1, int32_t y1, int32_t z1, int32_t w1) : vec(_mm256_setr_epi32(x0, y0, z0, w0, x1, y1, z1, w1)) { }
		#elif TS_SSE >= 1
			int32x8_t(const int32x8_t &v) : vec0(v.vec0), vec1(v.vec1) { }
			int32x8_t(__m128i v0, __m128i v1) : vec0(v0), vec1(v1) { }
			explicit int32x8_t(int32_t v) : vec0(_mm_set1_epi32(v)), vec1(_mm_set1_epi32(v)) { }
			#if TS_SSE >= 4
				explicit int32x8_t(const int16x8_t &v) : vec0(_mm_cvtepi16_epi32(v.vec)), vec1(_mm_cvtepi16_epi32(_mm_swizzle_epi32(v.vec, Z, W, Z, W))) { }
			#else
				explicit int32x8_t(const int16x8_t &v) : x0(v.x0), y0(v.y0), z0(v.z0), w0(v.w0), x1(v.x1), y1(v.y1), z1(v.z1), w1(v.w1) { }
			#endif
			#if TS_SSE >= 2
				int32x8_t(const int32x4_t &v0, const int32x4_t &v1) : vec0(v0.vec), vec1(v1.vec) { }
			#else
				int32x8_t(const int32x4_t &v0, const int32x4_t &v1) : x0(v0.x), y0(v0.y), z0(v0.z), w0(v0.w), x1(v1.x), y1(v1.y), z1(v1.z), w1(v1.w) { }
			#endif
			int32x8_t(int32_t x0, int32_t y0, int32_t z0, int32_t w0, int32_t x1, int32_t y1, int32_t z1, int32_t w1) : vec0(_mm_setr_epi32(x0, y0, z0, w0)), vec1(_mm_setr_epi32(x1, y1, z1, w1)) { }
		#elif TS_NEON
			int32x8_t(const int32x8_t &v) : vec0(v.vec0), vec1(v.vec1) { }
			int32x8_t(::int32x4_t v0, ::int32x4_t v1) : vec0(v0), vec1(v1) { }
			explicit int32x8_t(int32_t v) : vec0(vdupq_n_s32(v)), vec1(vdupq_n_s32(v)) { }
			explicit int32x8_t(const int16x8_t &v) : vec0(vmovl_s16(vget_low_s16(v.vec))), vec1(vmovl_s16(vget_high_s16(v.vec))) { }
			int32x8_t(const int32x4_t &v0, const int32x4_t &v1) : vec0(v0.vec), vec1(v1.vec) { }
			int32x8_t(int32_t x0, int32_t y0, int32_t z0, int32_t w0, int32_t x1, int32_t y1, int32_t z1, int32_t w1) : vec0(vsetq_s32(x0, y0, z0, w0)), vec1(vsetq_s32(x1, y1, z1, w1)) { }
		#else
			explicit int32x8_t(int32_t v) : x0(v), y0(v), z0(v), w0(v), x1(v), y1(v), z1(v), w1(v) { }
			explicit int32x8_t(const int16x8_t &v) : x0(v.x0), y0(v.y0), z0(v.z0), w0(v.w0), x1(v.x1), y1(v.y1), z1(v.z1), w1(v.w1) { }
			int32x8_t(const int32x4_t &v0, const int32x4_t &v1) : x0(v0.x), y0(v0.y), z0(v0.z), w0(v0.w), x1(v1.x), y1(v1.y), z1(v1.z), w1(v1.w) { }
			int32x8_t(int32_t x0, int32_t y0, int32_t z0, int32_t w0, int32_t x1, int32_t y1, int32_t z1, int32_t w1) : x0(x0), y0(y0), z0(z0), w0(w0), x1(x1), y1(y1), z1(z1), w1(w1) { }
		#endif
		
		/// cast vector data
		TS_INLINE uint32x8_t asu32x8() const;
		TS_INLINE float32x8_t asf32x8() const;
		
		/// update vector data
		TS_INLINE void set(const int32x8_t &v) {
			#if TS_AVX >= 1
				vec = v.vec;
			#elif TS_SSE >= 1
				vec0 = v.vec0;
				vec1 = v.vec1;
			#elif TS_NEON
				vec0 = v.vec0;
				vec1 = v.vec1;
			#else
				x0 = v.x0; y0 = v.y0; z0 = v.z0; w0 = v.w0;
				x1 = v.x1; y1 = v.y1; z1 = v.z1; w1 = v.w1;
			#endif
		}
		TS_INLINE void set(int32_t X0, int32_t Y0, int32_t Z0, int32_t W0, int32_t X1, int32_t Y1, int32_t Z1, int32_t W1) {
			#if TS_AVX >= 1
				vec = _mm256_setr_epi32(X0, Y0, Z0, W0, X1, Y1, Z1, W1);
			#elif TS_SSE >= 1
				vec0 = _mm_setr_epi32(X0, Y0, Z0, W0);
				vec1 = _mm_setr_epi32(X1, Y1, Z1, W1);
			#elif TS_NEON
				vec0 = vsetq_s32(X0, Y0, Z0, W0);
				vec1 = vsetq_s32(X1, Y1, Z1, W1);
			#else
				x0 = X0; y0 = Y0; z0 = Z0; w0 = W0;
				x1 = X1; y1 = Y1; z1 = Z1; w1 = W1;
			#endif
		}
		TS_INLINE void set(const int32_t *TS_RESTRICT v) {
			#if TS_AVX >= 1
				vec = _mm256_castps_si256(_mm256_load_ps((const float32_t*)v));
			#elif TS_SSE >= 1
				vec0 = _mm_castps_si128(_mm_load_ps((const float32_t*)v + 0));
				vec1 = _mm_castps_si128(_mm_load_ps((const float32_t*)v + 4));
			#elif TS_NEON
				vec0 = _vld1q_s32(v + 0);
				vec1 = _vld1q_s32(v + 4);
			#else
				x0 = v[0]; y0 = v[1]; z0 = v[2]; w0 = v[3];
				x1 = v[4]; y1 = v[5]; z1 = v[6]; w1 = v[7];
			#endif
		}
		TS_INLINE void get(int32_t *TS_RESTRICT v) const {
			#if TS_AVX >= 1
				_mm256_stream_ps((float32_t*)v, _mm256_castsi256_ps(vec));
			#elif TS_SSE >= 1
				_mm_stream_ps((float32_t*)v + 0, _mm_castsi128_ps(vec0));
				_mm_stream_ps((float32_t*)v + 4, _mm_castsi128_ps(vec1));
			#elif TS_NEON
				_vst1q_s32(v + 0, vec0);
				_vst1q_s32(v + 4, vec1);
			#else
				v[0] = x0; v[1] = y0; v[2] = z0; v[3] = w0;
				v[4] = x1; v[5] = y1; v[6] = z1; v[7] = w1;
			#endif
		}
		template <uint32_t Index> TS_INLINE void set(int32_t V) {
			#if TS_AVX >= 1
				__m128i temp = _mm_insert_epi32(_mm256_extractf128_si256(vec, Index >> 2), V, Index & 0x03);
				vec = _mm256_insertf128_si256(vec, temp, Index >> 2);
			#elif TS_SSE >= 4
				vec[Index >> 2] = _mm_insert_epi32(vec[Index >> 2], V, Index & 0x03);
			#elif TS_NEON
				vec[Index >> 2] = _vsetq_lane_s32<Index & 0x03>(V, vec[Index >> 2]);
			#else
				v[Index] = V;
			#endif
		}
		template <uint32_t Index> TS_INLINE int32_t get() const {
			#if TS_AVX >= 1
				return _mm_extract_epi32(_mm256_extractf128_si256(vec, Index >> 2), Index & 0x03);
			#elif TS_SSE >= 4
				return _mm_extract_epi32(vec[Index >> 2], Index & 0x03);
			#elif TS_NEON
				return _vgetq_lane_s32<Index & 0x03>(vec[Index >> 2]);
			#else
				return v[Index];
			#endif
		}
		template <uint32_t Index> TS_INLINE int32x8_t get8() const {
			#if TS_AVX >= 1
				__m128i temp = _mm256_extractf128_si256(vec, Index >> 2);
				temp = _mm_shuffle_epi32(temp, ((Index & 0x03) << 6) | ((Index & 0x03) << 4) | ((Index & 0x03) << 2) | (Index & 0x03));
				return int32x8_t(temp, temp);
			#elif TS_SSE >= 4
				__m128i temp = _mm_shuffle_epi32(vec[Index >> 2], ((Index & 0x03) << 6) | ((Index & 0x03) << 4) | ((Index & 0x03) << 2) | (Index & 0x03));
				return int32x8_t(temp, temp);
			#elif TS_NEON
				::int32x4_t temp = vdupq_n_s32(_vgetq_lane_s32<Index & 0x03>(vec[Index >> 2]));
				return int32x8_t(temp, temp);
			#else
				return int32x8_t(v[Index]);
			#endif
		}
		
		/// vector to scalar operators
		TS_INLINE int32x8_t &operator*=(int32_t v) {
			#if TS_AVX >= 2
				vec = _mm256_mullo_epi32(vec, _mm256_set1_epi32(v));
			#elif TS_SSE >= 4
				__m128i temp = _mm_set1_epi32(v);
				vec0 = _mm_mullo_epi32(vec0, temp);
				vec1 = _mm_mullo_epi32(vec1, temp);
			#elif TS_NEON
				::int32x4_t temp = vdupq_n_s32(v);
				vec0 = vmulq_s32(vec0, temp);
				vec1 = vmulq_s32(vec1, temp);
			#else
				x0 *= v; y0 *= v; z0 *= v; w0 *= v; x1 *= v; y1 *= v; z1 *= v; w1 *= v;
			#endif
			return *this;
		}
		TS_INLINE int32x8_t &operator+=(int32_t v) {
			#if TS_AVX >= 2
				vec = _mm256_add_epi32(vec, _mm256_set1_epi32(v));
			#elif TS_SSE >= 1
				__m128i temp = _mm_set1_epi32(v);
				vec0 = _mm_add_epi32(vec0, temp);
				vec1 = _mm_add_epi32(vec1, temp);
			#elif TS_NEON
				::int32x4_t temp = vdupq_n_s32(v);
				vec0 = vaddq_s32(vec0, temp);
				vec1 = vaddq_s32(vec1, temp);
			#else
				x0 += v; y0 += v; z0 += v; w0 += v; x1 += v; y1 += v; z1 += v; w1 += v;
			#endif
			return *this;
		}
		TS_INLINE int32x8_t &operator-=(int32_t v) {
			#if TS_AVX >= 2
				vec = _mm256_sub_epi32(vec, _mm256_set1_epi32(v));
			#elif TS_SSE >= 1
				__m128i temp = _mm_set1_epi32(v);
				vec0 = _mm_sub_epi32(vec0, temp);
				vec1 = _mm_sub_epi32(vec1, temp);
			#elif TS_NEON
				::int32x4_t temp = vdupq_n_s32(v);
				vec0 = vsubq_s32(vec0, temp);
				vec1 = vsubq_s32(vec1, temp);
			#else
				x0 -= v; y0 -= v; z0 -= v; w0 -= v; x1 -= v; y1 -= v; z1 -= v; w1 -= v;
			#endif
			return *this;
		}
		TS_INLINE int32x8_t &operator&=(int32_t v) {
			#if TS_AVX >= 2
				vec = _mm256_and_si256(vec, _mm256_set1_epi32(v));
			#elif TS_SSE >= 1
				__m128i temp = _mm_set1_epi32(v);
				vec0 = _mm_and_si128(vec0, temp);
				vec1 = _mm_and_si128(vec1, temp);
			#elif TS_NEON
				::int32x4_t temp = vdupq_n_s32(v);
				vec0 = vandq_s32(vec0, temp);
				vec1 = vandq_s32(vec1, temp);
			#else
				x0 &= v; y0 &= v; z0 &= v; w0 &= v; x1 &= v; y1 &= v; z1 &= v; w1 &= v;
			#endif
			return *this;
		}
		TS_INLINE int32x8_t &operator|=(int32_t v) {
			#if TS_AVX >= 2
				vec = _mm256_or_si256(vec, _mm256_set1_epi32(v));
			#elif TS_SSE >= 1
				__m128i temp = _mm_set1_epi32(v);
				vec0 = _mm_or_si128(vec0, temp);
				vec1 = _mm_or_si128(vec1, temp);
			#elif TS_NEON
				::int32x4_t temp = vdupq_n_s32(v);
				vec0 = vorrq_s32(vec0, temp);
				vec1 = vorrq_s32(vec1, temp);
			#else
				x0 |= v; y0 |= v; z0 |= v; w0 |= v; x1 |= v; y1 |= v; z1 |= v; w1 |= v;
			#endif
			return *this;
		}
		TS_INLINE int32x8_t &operator^=(int32_t v) {
			#if TS_AVX >= 2
				vec = _mm256_xor_si256(vec, _mm256_set1_epi32(v));
			#elif TS_SSE >= 1
				__m128i temp = _mm_set1_epi32(v);
				vec0 = _mm_xor_si128(vec0, temp);
				vec1 = _mm_xor_si128(vec1, temp);
			#elif TS_NEON
				::int32x4_t temp = vdupq_n_s32(v);
				vec0 = veorq_s32(vec0, temp);
				vec1 = veorq_s32(vec1, temp);
			#else
				x0 ^= v; y0 ^= v; z0 ^= v; w0 ^= v; x1 ^= v; y1 ^= v; z1 ^= v; w1 ^= v;
			#endif
			return *this;
		}
		TS_INLINE int32x8_t &operator<<=(int32_t v) {
			#if TS_AVX >= 2
				vec = _mm256_slli_epi32(vec, v);
			#elif TS_SSE >= 1
				vec0 = _mm_slli_epi32(vec0, v);
				vec1 = _mm_slli_epi32(vec1, v);
			#elif TS_NEON
				::int32x4_t temp = vdupq_n_s32(v);
				vec0 = vshlq_s32(vec0, temp);
				vec1 = vshlq_s32(vec1, temp);
			#else
				x0 <<= v; y0 <<= v; z0 <<= v; w0 <<= v; x1 <<= v; y1 <<= v; z1 <<= v; w1 <<= v;
			#endif
			return *this;
		}
		TS_INLINE int32x8_t &operator>>=(int32_t v) {
			#if TS_AVX >= 2
				vec = _mm256_srai_epi32(vec, v);
			#elif TS_SSE >= 1
				vec0 = _mm_srai_epi32(vec0, v);
				vec1 = _mm_srai_epi32(vec1, v);
			#elif TS_NEON
				::int32x4_t temp = vdupq_n_s32(-v);
				vec0 = vshlq_s32(vec0, temp);
				vec1 = vshlq_s32(vec1, temp);
			#else
				x0 >>= v; y0 >>= v; z0 >>= v; w0 >>= v; x1 >>= v; y1 >>= v; z1 >>= v; w1 >>= v;
			#endif
			return *this;
		}
		
		/// vector to vector operators
		TS_INLINE int32x8_t &operator*=(const int32x8_t &v) {
			#if TS_AVX >= 2
				vec = _mm256_mullo_epi32(vec, v.vec);
			#elif TS_SSE >= 4
				vec0 = _mm_mullo_epi32(vec0, v.vec0);
				vec1 = _mm_mullo_epi32(vec1, v.vec1);
			#elif TS_NEON
				vec0 = vmulq_s32(vec0, v.vec0);
				vec1 = vmulq_s32(vec1, v.vec1);
			#else
				x0 *= v.x0; y0 *= v.y0; z0 *= v.z0; w0 *= v.w0; x1 *= v.x1; y1 *= v.y1; z1 *= v.z1; w1 *= v.w1;
			#endif
			return *this;
		}
		TS_INLINE int32x8_t &operator+=(const int32x8_t &v) {
			#if TS_AVX >= 2
				vec = _mm256_add_epi32(vec, v.vec);
			#elif TS_SSE >= 1
				vec0 = _mm_add_epi32(vec0, v.vec0);
				vec1 = _mm_add_epi32(vec1, v.vec1);
			#elif TS_NEON
				vec0 = vaddq_s32(vec0, v.vec0);
				vec1 = vaddq_s32(vec1, v.vec1);
			#else
				x0 += v.x0; y0 += v.y0; z0 += v.z0; w0 += v.w0; x1 += v.x1; y1 += v.y1; z1 += v.z1; w1 += v.w1;
			#endif
			return *this;
		}
		TS_INLINE int32x8_t &operator-=(const int32x8_t &v) {
			#if TS_AVX >= 2
				vec = _mm256_sub_epi32(vec, v.vec);
			#elif TS_SSE >= 1
				vec0 = _mm_sub_epi32(vec0, v.vec0);
				vec1 = _mm_sub_epi32(vec1, v.vec1);
			#elif TS_NEON
				vec0 = vsubq_s32(vec0, v.vec0);
				vec1 = vsubq_s32(vec1, v.vec1);
			#else
				x0 -= v.x0; y0 -= v.y0; z0 -= v.z0; w0 -= v.w0; x1 -= v.x1; y1 -= v.y1; z1 -= v.z1; w1 -= v.w1;
			#endif
			return *this;
		}
		TS_INLINE int32x8_t &operator&=(const int32x8_t &v) {
			#if TS_AVX >= 2
				vec = _mm256_and_si256(vec, v.vec);
			#elif TS_SSE >= 1
				vec0 = _mm_and_si128(vec0, v.vec0);
				vec1 = _mm_and_si128(vec1, v.vec1);
			#elif TS_NEON
				vec0 = vandq_s32(vec0, v.vec0);
				vec1 = vandq_s32(vec1, v.vec1);
			#else
				x0 &= v.x0; y0 &= v.y0; z0 &= v.z0; w0 &= v.w0; x1 &= v.x1; y1 &= v.y1; z1 &= v.z1; w1 &= v.w1;
			#endif
			return *this;
		}
		TS_INLINE int32x8_t &operator|=(const int32x8_t &v) {
			#if TS_AVX >= 2
				vec = _mm256_or_si256(vec, v.vec);
			#elif TS_SSE >= 1
				vec0 = _mm_or_si128(vec0, v.vec0);
				vec1 = _mm_or_si128(vec1, v.vec1);
			#elif TS_NEON
				vec0 = vorrq_s32(vec0, v.vec0);
				vec1 = vorrq_s32(vec1, v.vec1);
			#else
				x0 |= v.x0; y0 |= v.y0; z0 |= v.z0; w0 |= v.w0; x1 |= v.x1; y1 |= v.y1; z1 |= v.z1; w1 |= v.w1;
			#endif
			return *this;
		}
		TS_INLINE int32x8_t &operator^=(const int32x8_t &v) {
			#if TS_AVX >= 2
				vec = _mm256_xor_si256(vec, v.vec);
			#elif TS_SSE >= 1
				vec0 = _mm_xor_si128(vec0, v.vec0);
				vec1 = _mm_xor_si128(vec1, v.vec1);
			#elif TS_NEON
				vec0 = veorq_s32(vec0, v.vec0);
				vec1 = veorq_s32(vec1, v.vec1);
			#else
				x0 ^= v.x0; y0 ^= v.y0; z0 ^= v.z0; w0 ^= v.w0; x1 ^= v.x1; y1 ^= v.y1; z1 ^= v.z1; w1 ^= v.w1;
			#endif
			return *this;
		}
		
		/// swizzle vector
		TS_INLINE int32x8_t xyzw10() const {
			#if TS_AVX >= 1
				return int32x8_t(_mm256_permute2f128_si256(vec, vec, 0x03));
			#elif TS_SSE >= 2
				return int32x8_t(vec1, vec0);
			#elif TS_NEON
				return int32x8_t(vec1, vec0);
			#else
				return int32x8_t(x1, y1, z1, w1, x0, y0, z0, w0);
			#endif
		}
		TS_INLINE int32x8_t zwxy01() const {
			#if TS_AVX >= 1
				return int32x8_t(_mm256_castps_si256(_mm256_permute_ps(_mm256_castsi256_ps(vec), 0x4e)));
			#elif TS_SSE >= 2
				return int32x8_t(_mm_swizzle_epi32(vec0, Z, W, X, Y), _mm_swizzle_epi32(vec1, Z, W, X, Y));
			#elif TS_NEON
				return int32x8_t(vcombine_s32(vget_high_s32(vec0), vget_low_s32(vec0)), vcombine_s32(vget_high_s32(vec1), vget_low_s32(vec1)));
			#else
				return int32x8_t(z0, w0, x0, y0, z1, w1, x1, y1);
			#endif
		}
		TS_INLINE int32x8_t yxwz01() const {
			#if TS_AVX >= 1
				return int32x8_t(_mm256_castps_si256(_mm256_permute_ps(_mm256_castsi256_ps(vec), 0xb1)));
			#elif TS_SSE >= 2
				return int32x8_t(_mm_swizzle_epi32(vec0, Y, X, W, Z), _mm_swizzle_epi32(vec1, Y, X, W, Z));
			#elif TS_NEON
				return int32x8_t(vrev64q_s32(vec0), vrev64q_s32(vec1));
			#else
				return int32x8_t(y0, x0, w0, z0, y1, x1, w1, z1);
			#endif
		}
		TS_INLINE int32x4_t xyzw0() const {
			#if TS_AVX >= 1
				return int32x4_t(_mm256_extractf128_si256(vec, 0));
			#elif TS_SSE >= 2
				return int32x4_t(vec0);
			#elif TS_NEON
				return int32x4_t(vec0);
			#else
				return int32x4_t(x0, y0, z0, w0);
			#endif
		}
		TS_INLINE int32x4_t xyzw1() const {
			#if TS_AVX >= 1
				return int32x4_t(_mm256_extractf128_si256(vec, 1));
			#elif TS_SSE >= 2
				return int32x4_t(vec1);
			#elif TS_NEON
				return int32x4_t(vec1);
			#else
				return int32x4_t(x1, y1, z1, w1);
			#endif
		}
		
		/// sum vector components
		TS_INLINE int32_t sum() const {
			#if TS_AVX >= 1
				__m128i temp = _mm_add_epi32(_mm256_extractf128_si256(vec, 0), _mm256_extractf128_si256(vec, 1));
				temp = _mm_hadd_epi32(temp, temp);
				temp = _mm_hadd_epi32(temp, temp);
				return _mm_extract_epi32(temp, 0);
			#elif TS_SSE >= 4
				__m128i temp = _mm_add_epi32(vec0, vec1);
				temp = _mm_hadd_epi32(temp, temp);
				temp = _mm_hadd_epi32(temp, temp);
				return _mm_extract_epi32(temp, 0);
			#elif TS_SSE >= 2
				__m128i temp = _mm_add_epi32(vec0, vec1);
				temp = _mm_add_epi32(temp, _mm_swizzle_epi32(temp, Z, W, X, Y));
				temp = _mm_add_epi32(temp, _mm_swizzle_epi32(temp, Y, X, W, Z));
				return (int32_t)f32u32(_mm_cvtss_f32(_mm_castsi128_ps(temp))).u;
			#elif TS_NEON
				::int32x2_t temp = vadd_s32(vget_high_s32(vec0), vget_low_s32(vec0));
				temp = vadd_s32(temp, vadd_s32(vget_high_s32(vec1), vget_low_s32(vec1)));
				temp = vadd_s32(temp, vrev64_s32(temp));
				return _vget_lane_s32<0>(temp);
			#else
				return x0 + y0 + z0 + w0 + x1 + y1 + z1 + w1;
			#endif
		}
		
		enum {
			Size = 8,
		};
		
		union {
			struct {
				int32_t x0, y0, z0, w0;
				int32_t x1, y1, z1, w1;
			};
			int32_t v[Size];
			#if TS_AVX >= 1
				struct {
					__m128i vec0;
					__m128i vec1;
				};
				__m256i vec;
			#elif TS_SSE >= 1
				struct {
					__m128i vec0;
					__m128i vec1;
				};
				__m128i vec[2];
			#elif TS_NEON
				struct {
					::int32x4_t vec0;
					::int32x4_t vec1;
				};
				::int32x4_t vec[2];
			#endif
		};
	};
	
	/// unary operators
	TS_INLINE int32x8_t operator-(const int32x8_t &v) {
		#if TS_AVX >= 2
			return int32x8_t(_mm256_sign_epi32(v.vec, _mm256_set1_epi32(-1)));
		#elif TS_SSE >= 4
			__m128i temp = _mm_set1_epi32(-1);
			return int32x8_t(_mm_sign_epi32(v.vec0, temp), _mm_sign_epi32(v.vec1, temp));
		#elif TS_SSE >= 2
			__m128i temp = _mm_set1_epi32(0);
			return int32x8_t(_mm_sub_epi32(temp, v.vec0), _mm_sub_epi32(temp, v.vec1));
		#elif TS_NEON
			return int32x8_t(vnegq_s32(v.vec0), vnegq_s32(v.vec1));
		#else
			return int32x8_t(-v.x0, -v.y0, -v.z0, -v.w0, -v.x1, -v.y1, -v.z1, -v.w1);
		#endif
	}
	
	/// vector to scalar operators
	TS_INLINE int32x8_t operator*(const int32x8_t &v0, int32_t v1) {
		#if TS_AVX >= 2
			return int32x8_t(_mm256_mullo_epi32(v0.vec, _mm256_set1_epi32(v1)));
		#elif TS_SSE >= 4
			__m128i temp = _mm_set1_epi32(v1);
			return int32x8_t(_mm_mullo_epi32(v0.vec0, temp), _mm_mullo_epi32(v0.vec1, temp));
		#elif TS_NEON
			::int32x4_t temp = vdupq_n_s32(v1);
			return int32x8_t(vmulq_s32(v0.vec0, temp), vmulq_s32(v0.vec1, temp));
		#else
			return int32x8_t(v0.x0 * v1, v0.y0 * v1, v0.z0 * v1, v0.w0 * v1, v0.x1 * v1, v0.y1 * v1, v0.z1 * v1, v0.w1 * v1);
		#endif
	}
	TS_INLINE int32x8_t operator+(const int32x8_t &v0, int32_t v1) {
		#if TS_AVX >= 2
			return int32x8_t(_mm256_add_epi32(v0.vec, _mm256_set1_epi32(v1)));
		#elif TS_SSE >= 1
			__m128i temp = _mm_set1_epi32(v1);
			return int32x8_t(_mm_add_epi32(v0.vec0, temp), _mm_add_epi32(v0.vec1, temp));
		#elif TS_NEON
			::int32x4_t temp = vdupq_n_s32(v1);
			return int32x8_t(vaddq_s32(v0.vec0, temp), vaddq_s32(v0.vec1, temp));
		#else
			return int32x8_t(v0.x0 + v1, v0.y0 + v1, v0.z0 + v1, v0.w0 + v1, v0.x1 + v1, v0.y1 + v1, v0.z1 + v1, v0.w1 + v1);
		#endif
	}
	TS_INLINE int32x8_t operator-(const int32x8_t &v0, int32_t v1) {
		#if TS_AVX >= 2
			return int32x8_t(_mm256_sub_epi32(v0.vec, _mm256_set1_epi32(v1)));
		#elif TS_SSE >= 1
			__m128i temp = _mm_set1_epi32(v1);
			return int32x8_t(_mm_sub_epi32(v0.vec0, temp), _mm_sub_epi32(v0.vec1, temp));
		#elif TS_NEON
			::int32x4_t temp = vdupq_n_s32(v1);
			return int32x8_t(vsubq_s32(v0.vec0, temp), vsubq_s32(v0.vec1, temp));
		#else
			return int32x8_t(v0.x0 - v1, v0.y0 - v1, v0.z0 - v1, v0.w0 - v1, v0.x1 - v1, v0.y1 - v1, v0.z1 - v1, v0.w1 - v1);
		#endif
	}
	TS_INLINE int32x8_t operator&(const int32x8_t &v0, int32_t v1) {
		#if TS_AVX >= 2
			return int32x8_t(_mm256_and_si256(v0.vec, _mm256_set1_epi32(v1)));
		#elif TS_SSE >= 1
			__m128i temp = _mm_set1_epi32(v1);
			return int32x8_t(_mm_and_si128(v0.vec0, temp), _mm_and_si128(v0.vec1, temp));
		#elif TS_NEON
			::int32x4_t temp = vdupq_n_s32(v1);
			return int32x8_t(vandq_s32(v0.vec0, temp), vandq_s32(v0.vec1, temp));
		#else
			return int32x8_t(v0.x0 & v1, v0.y0 & v1, v0.z0 & v1, v0.w0 & v1, v0.x1 & v1, v0.y1 & v1, v0.z1 & v1, v0.w1 & v1);
		#endif
	}
	TS_INLINE int32x8_t operator|(const int32x8_t &v0, int32_t v1) {
		#if TS_AVX >= 2
			return int32x8_t(_mm256_or_si256(v0.vec, _mm256_set1_epi32(v1)));
		#elif TS_SSE >= 1
			__m128i temp = _mm_set1_epi32(v1);
			return int32x8_t(_mm_or_si128(v0.vec0, temp), _mm_or_si128(v0.vec1, temp));
		#elif TS_NEON
			::int32x4_t temp = vdupq_n_s32(v1);
			return int32x8_t(vorrq_s32(v0.vec0, temp), vorrq_s32(v0.vec1, temp));
		#else
			return int32x8_t(v0.x0 | v1, v0.y0 | v1, v0.z0 | v1, v0.w0 | v1, v0.x1 | v1, v0.y1 | v1, v0.z1 | v1, v0.w1 | v1);
		#endif
	}
	TS_INLINE int32x8_t operator^(const int32x8_t &v0, int32_t v1) {
		#if TS_AVX >= 2
			return int32x8_t(_mm256_xor_si256(v0.vec, _mm256_set1_epi32(v1)));
		#elif TS_SSE >= 1
			__m128i temp = _mm_set1_epi32(v1);
			return int32x8_t(_mm_xor_si128(v0.vec0, temp), _mm_xor_si128(v0.vec1, temp));
		#elif TS_NEON
			::int32x4_t temp = vdupq_n_s32(v1);
			return int32x8_t(veorq_s32(v0.vec0, temp), veorq_s32(v0.vec1, temp));
		#else
			return int32x8_t(v0.x0 ^ v1, v0.y0 ^ v1, v0.z0 ^ v1, v0.w0 ^ v1, v0.x1 ^ v1, v0.y1 ^ v1, v0.z1 ^ v1, v0.w1 ^ v1);
		#endif
	}
	TS_INLINE int32x8_t operator<<(const int32x8_t &v0, int32_t v1) {
		#if TS_AVX >= 2
			return int32x8_t(_mm256_slli_epi32(v0.vec, v1));
		#elif TS_SSE >= 1
			return int32x8_t(_mm_slli_epi32(v0.vec0, v1), _mm_slli_epi32(v0.vec1, v1));
		#elif TS_NEON
			::int32x4_t temp = vdupq_n_s32(v1);
			return int32x8_t(vshlq_s32(v0.vec0, temp), vshlq_s32(v0.vec1, temp));
		#else
			return int32x8_t(v0.x0 << v1, v0.y0 << v1, v0.z0 << v1, v0.w0 << v1, v0.x1 << v1, v0.y1 << v1, v0.z1 << v1, v0.w1 << v1);
		#endif
	}
	TS_INLINE int32x8_t operator>>(const int32x8_t &v0, int32_t v1) {
		#if TS_AVX >= 2
			return int32x8_t(_mm256_srai_epi32(v0.vec, v1));
		#elif TS_SSE >= 1
			return int32x8_t(_mm_srai_epi32(v0.vec0, v1), _mm_srai_epi32(v0.vec1, v1));
		#elif TS_NEON
			::int32x4_t temp = vdupq_n_s32(-v1);
			return int32x8_t(vshlq_s32(v0.vec0, temp), vshlq_s32(v0.vec1, temp));
		#else
			return int32x8_t(v0.x0 >> v1, v0.y0 >> v1, v0.z0 >> v1, v0.w0 >> v1, v0.x1 >> v1, v0.y1 >> v1, v0.z1 >> v1, v0.w1 >> v1);
		#endif
	}
	
	/// vector to vector operators
	TS_INLINE int32x8_t operator*(const int32x8_t &v0, const int32x8_t &v1) {
		#if TS_AVX >= 2
			return int32x8_t(_mm256_mullo_epi32(v0.vec, v1.vec));
		#elif TS_SSE >= 4
			return int32x8_t(_mm_mullo_epi32(v0.vec0, v1.vec0), _mm_mullo_epi32(v0.vec1, v1.vec1));
		#elif TS_NEON
			return int32x8_t(vmulq_s32(v0.vec0, v1.vec0), vmulq_s32(v0.vec1, v1.vec1));
		#else
			return int32x8_t(v0.x0 * v1.x0, v0.y0 * v1.y0, v0.z0 * v1.z0, v0.w0 * v1.w0, v0.x1 * v1.x1, v0.y1 * v1.y1, v0.z1 * v1.z1, v0.w1 * v1.w1);
		#endif
	}
	TS_INLINE int32x8_t operator+(const int32x8_t &v0, const int32x8_t &v1) {
		#if TS_AVX >= 2
			return int32x8_t(_mm256_add_epi32(v0.vec, v1.vec));
		#elif TS_SSE >= 1
			return int32x8_t(_mm_add_epi32(v0.vec0, v1.vec0), _mm_add_epi32(v0.vec1, v1.vec1));
		#elif TS_NEON
			return int32x8_t(vaddq_s32(v0.vec0, v1.vec0), vaddq_s32(v0.vec1, v1.vec1));
		#else
			return int32x8_t(v0.x0 + v1.x0, v0.y0 + v1.y0, v0.z0 + v1.z0, v0.w0 + v1.w0, v0.x1 + v1.x1, v0.y1 + v1.y1, v0.z1 + v1.z1, v0.w1 + v1.w1);
		#endif
	}
	TS_INLINE int32x8_t operator-(const int32x8_t &v0, const int32x8_t &v1) {
		#if TS_AVX >= 2
			return int32x8_t(_mm256_sub_epi32(v0.vec, v1.vec));
		#elif TS_SSE >= 1
			return int32x8_t(_mm_sub_epi32(v0.vec0, v1.vec0), _mm_sub_epi32(v0.vec1, v1.vec1));
		#elif TS_NEON
			return int32x8_t(vsubq_s32(v0.vec0, v1.vec0), vsubq_s32(v0.vec1, v1.vec1));
		#else
			return int32x8_t(v0.x0 - v1.x0, v0.y0 - v1.y0, v0.z0 - v1.z0, v0.w0 - v1.w0, v0.x1 - v1.x1, v0.y1 - v1.y1, v0.z1 - v1.z1, v0.w1 - v1.w1);
		#endif
	}
	TS_INLINE int32x8_t operator&(const int32x8_t &v0, const int32x8_t &v1) {
		#if TS_AVX >= 2
			return int32x8_t(_mm256_and_si256(v0.vec, v1.vec));
		#elif TS_SSE >= 1
			return int32x8_t(_mm_and_si128(v0.vec0, v1.vec0), _mm_and_si128(v0.vec1, v1.vec1));
		#elif TS_NEON
			return int32x8_t(vandq_s32(v0.vec0, v1.vec0), vandq_s32(v0.vec1, v1.vec1));
		#else
			return int32x8_t(v0.x0 & v1.x0, v0.y0 & v1.y0, v0.z0 & v1.z0, v0.w0 & v1.w0, v0.x1 & v1.x1, v0.y1 & v1.y1, v0.z1 & v1.z1, v0.w1 & v1.w1);
		#endif
	}
	TS_INLINE int32x8_t operator|(const int32x8_t &v0, const int32x8_t &v1) {
		#if TS_AVX >= 2
			return int32x8_t(_mm256_or_si256(v0.vec, v1.vec));
		#elif TS_SSE >= 1
			return int32x8_t(_mm_or_si128(v0.vec0, v1.vec0), _mm_or_si128(v0.vec1, v1.vec1));
		#elif TS_NEON
			return int32x8_t(vorrq_s32(v0.vec0, v1.vec0), vorrq_s32(v0.vec1, v1.vec1));
		#else
			return int32x8_t(v0.x0 | v1.x0, v0.y0 | v1.y0, v0.z0 | v1.z0, v0.w0 | v1.w0, v0.x1 | v1.x1, v0.y1 | v1.y1, v0.z1 | v1.z1, v0.w1 | v1.w1);
		#endif
	}
	TS_INLINE int32x8_t operator^(const int32x8_t &v0, const int32x8_t &v1) {
		#if TS_AVX >= 2
			return int32x8_t(_mm256_xor_si256(v0.vec, v1.vec));
		#elif TS_SSE >= 1
			return int32x8_t(_mm_xor_si128(v0.vec0, v1.vec0), _mm_xor_si128(v0.vec1, v1.vec1));
		#elif TS_NEON
			return int32x8_t(veorq_s32(v0.vec0, v1.vec0), veorq_s32(v0.vec1, v1.vec1));
		#else
			return int32x8_t(v0.x0 ^ v1.x0, v0.y0 ^ v1.y0, v0.z0 ^ v1.z0, v0.w0 ^ v1.w0, v0.x1 ^ v1.x1, v0.y1 ^ v1.y1, v0.z1 ^ v1.z1, v0.w1 ^ v1.w1);
		#endif
	}
	
	/// min/max functions
	TS_INLINE int32x8_t min(const int32x8_t &v0, const int32x8_t &v1) {
		#if TS_AVX >= 2
			return int32x8_t(_mm256_min_epi32(v0.vec, v1.vec));
		#elif TS_SSE >= 4
			return int32x8_t(_mm_min_epi32(v0.vec0, v1.vec0), _mm_min_epi32(v0.vec1, v1.vec1));
		#elif TS_NEON
			return int32x8_t(vminq_s32(v0.vec0, v1.vec0), vminq_s32(v0.vec1, v1.vec1));
		#else
			return int32x8_t(min(v0.x0, v1.x0), min(v0.y0, v1.y0), min(v0.z0, v1.z0), min(v0.w0, v1.w0), min(v0.x1, v1.x1), min(v0.y1, v1.y1), min(v0.z1, v1.z1), min(v0.w1, v1.w1));
		#endif
	}
	TS_INLINE int32x8_t max(const int32x8_t &v0, const int32x8_t &v1) {
		#if TS_AVX >= 2
			return int32x8_t(_mm256_max_epi32(v0.vec, v1.vec));
		#elif TS_SSE >= 4
			return int32x8_t(_mm_max_epi32(v0.vec0, v1.vec0), _mm_max_epi32(v0.vec1, v1.vec1));
		#elif TS_NEON
			return int32x8_t(vmaxq_s32(v0.vec0, v1.vec0), vmaxq_s32(v0.vec1, v1.vec1));
		#else
			return int32x8_t(max(v0.x0, v1.x0), max(v0.y0, v1.y0), max(v0.z0, v1.z0), max(v0.w0, v1.w0), max(v0.x1, v1.x1), max(v0.y1, v1.y1), max(v0.z1, v1.z1), max(v0.w1, v1.w1));
		#endif
	}
	
	/// range functions
	TS_INLINE int32x8_t clamp(const int32x8_t &v, int32_t v0, int32_t v1) {
		return min(max(v, int32x8_t(v0)), int32x8_t(v1));
	}
	TS_INLINE int32x8_t clamp(const int32x8_t &v, const int32x8_t &v0, const int32x8_t &v1) {
		return min(max(v, v0), v1);
	}
	
	/// select functions
	TS_INLINE int32x8_t select(const int32x8_t &v0, const int32x8_t &v1, const int32x8_t &s) {
		#if TS_AVX >= 1
			return int32x8_t(_mm256_castps_si256(_mm256_blendv_ps(_mm256_castsi256_ps(v0.vec), _mm256_castsi256_ps(v1.vec), _mm256_castsi256_ps(s.vec))));
		#elif TS_SSE >= 2
			return int32x8_t(_mm_xor_si128(v0.vec0, _mm_and_si128(_mm_xor_si128(v0.vec0, v1.vec0), _mm_srai_epi32(s.vec0, 31))), _mm_xor_si128(v0.vec1, _mm_and_si128(_mm_xor_si128(v0.vec1, v1.vec1), _mm_srai_epi32(s.vec1, 31))));
		#elif TS_NEON
			return int32x8_t(vbslq_s32(vcgeq_s32(s.vec0, vdupq_n_s32(0)), v0.vec0, v1.vec0), vbslq_s32(vcgeq_s32(s.vec1, vdupq_n_s32(0)), v0.vec1, v1.vec1));
		#else
			return int32x8_t(select(v0.x0, v1.x0, s.x0), select(v0.y0, v1.y0, s.y0), select(v0.z0, v1.z0, s.z0), select(v0.w0, v1.w0, s.w0), select(v0.x1, v1.x1, s.x1), select(v0.y1, v1.y1, s.y1), select(v0.z1, v1.z1, s.z1), select(v0.w1, v1.w1, s.w1));
		#endif
	}
	TS_INLINE int32x8_t select(const int32x8_t &v0, const int32x8_t &v1, int32_t s) {
		return select(v0, v1, int32x8_t(s));
	}
	
	/*****************************************************************************\
	 *
	 * uint16x8_t
	 *
	\*****************************************************************************/
	
	/**
	 * Vector of eight uint16_t components
	 */
	struct TS_ALIGNAS16 uint16x8_t {
		
		uint16x8_t() { }
		explicit uint16x8_t(const uint32x8_t &v);
		explicit uint16x8_t(const uint16_t *v) { set(v); }
		uint16x8_t(const uint32x4_t &v0, const uint32x4_t &v1);
		#if TS_SSE >= 2
			uint16x8_t(const uint16x8_t &v) : vec(v.vec) { }
			explicit uint16x8_t(__m128i v) : vec(v) { }
			explicit uint16x8_t(uint16_t v) : vec(_mm_set1_epi16((int16_t)v)) { }
			uint16x8_t(uint16_t x0, uint16_t y0, uint16_t z0, uint16_t w0, uint16_t x1, uint16_t y1, uint16_t z1, uint16_t w1) : vec(_mm_setr_epi16((int16_t)x0, (int16_t)y0, (int16_t)z0, (int16_t)w0, (int16_t)x1, (int16_t)y1, (int16_t)z1, (int16_t)w1)) { }
		#elif TS_NEON
			uint16x8_t(const uint16x8_t &v) : vec(v.vec) { }
			explicit uint16x8_t(::uint16x8_t v) : vec(v) { }
			explicit uint16x8_t(uint16_t v) : vec(vdupq_n_u16(v)) { }
			uint16x8_t(uint16_t x0, uint16_t y0, uint16_t z0, uint16_t w0, uint16_t x1, uint16_t y1, uint16_t z1, uint16_t w1) : vec(vsetq_u16(x0, y0, z0, w0, x1, y1, z1, w1)) { }
		#else
			explicit uint16x8_t(uint16_t v) : x0(v), y0(v), z0(v), w0(v), x1(v), y1(v), z1(v), w1(v) { }
			uint16x8_t(uint16_t x0, uint16_t y0, uint16_t z0, uint16_t w0, uint16_t x1, uint16_t y1, uint16_t z1, uint16_t w1) : x0(x0), y0(y0), z0(z0), w0(w0), x1(x1), y1(y1), z1(z1), w1(w1) { }
		#endif
		
		/// cast vector data
		TS_INLINE int16x8_t asi16x8() const {
			#if TS_SSE >= 2
				return int16x8_t(vec);
			#elif TS_NEON
				return int16x8_t(vreinterpretq_s16_u16(vec));
			#else
				return int16x8_t((int16_t*)v);
			#endif
		}
		TS_INLINE int32x4_t asi32x4() const {
			#if TS_SSE >= 2
				return int32x4_t(vec);
			#elif TS_NEON
				return int32x4_t(vreinterpretq_s32_u16(vec));
			#else
				return int32x4_t((int32_t*)v);
			#endif
		}
		TS_INLINE uint32x4_t asu32x4() const;
		TS_INLINE float16x8_t asf16x8() const;
		TS_INLINE float32x4_t asf32x4() const;
		
		/// update vector data
		TS_INLINE void set(const uint16x8_t &v) {
			#if TS_SSE >= 2
				vec = v.vec;
			#elif TS_NEON
				vec = v.vec;
			#else
				x0 = v.x0; y0 = v.y0; z0 = v.z0; w0 = v.w0;
				x1 = v.x1; y1 = v.y1; z1 = v.z1; w1 = v.w1;
			#endif
		}
		TS_INLINE void set(uint16_t X0, uint16_t Y0, uint16_t Z0, uint16_t W0, uint16_t X1, uint16_t Y1, uint16_t Z1, uint16_t W1) {
			#if TS_SSE >= 2
				vec = _mm_setr_epi16((int16_t)X0, (int16_t)Y0, (int16_t)Z0, (int16_t)W0, (int16_t)X1, (int16_t)Y1, (int16_t)Z1, (int16_t)W1);
			#elif TS_NEON
				vec = vsetq_u16(X0, Y0, Z0, W0, X1, Y1, Z1, W1);
			#else
				x0 = X0; y0 = Y0; z0 = Z0; w0 = W0;
				x1 = X1; y1 = Y1; z1 = Z1; w1 = W1;
			#endif
		}
		TS_INLINE void set(const uint16_t *TS_RESTRICT v) {
			#if TS_SSE >= 2
				vec = _mm_castps_si128(_mm_load_ps((const float32_t*)v));
			#elif TS_NEON
				vec = _vld1q_u16(v);
			#else
				x0 = v[0]; y0 = v[1]; z0 = v[2]; w0 = v[3];
				x1 = v[4]; y1 = v[5]; z1 = v[6]; w1 = v[7];
			#endif
		}
		TS_INLINE void get(uint16_t *TS_RESTRICT v) const {
			#if TS_SSE >= 2
				_mm_stream_ps((float32_t*)v, _mm_castsi128_ps(vec));
			#elif TS_NEON
				_vst1q_u16(v, vec);
			#else
				v[0] = x0; v[1] = y0; v[2] = z0; v[3] = w0;
				v[4] = x1; v[5] = y1; v[6] = z1; v[7] = w1;
			#endif
		}
		template <uint32_t Index> TS_INLINE void set(uint16_t V) {
			#if TS_SSE >= 2
				vec = _mm_insert_epi16(vec, (int16_t)V, Index);
			#elif TS_NEON
				vec = _vsetq_lane_u16<Index>(V, vec);
			#else
				v[Index] = V;
			#endif
		}
		template <uint32_t Index> TS_INLINE uint16_t get() const {
			#if TS_SSE >= 2
				return (uint16_t)_mm_extract_epi16(vec, Index);
			#elif TS_NEON
				return _vgetq_lane_u16<Index>(vec);
			#else
				return v[Index];
			#endif
		}
		
		/// vector to scalar operators
		TS_INLINE uint16x8_t &operator*=(uint16_t v) {
			#if TS_SSE >= 2
				vec = _mm_mullo_epi16(vec, _mm_set1_epi16(v));
			#elif TS_NEON
				vec = vmulq_n_u16(vec, v);
			#else
				x0 *= v; y0 *= v; z0 *= v; w0 *= v; x1 *= v; y1 *= v; z1 *= v; w1 *= v;
			#endif
			return *this;
		}
		TS_INLINE uint16x8_t &operator+=(uint16_t v) {
			#if TS_SSE >= 2
				vec = _mm_add_epi16(vec, _mm_set1_epi16(v));
			#elif TS_NEON
				vec = vaddq_u16(vec, vdupq_n_u16(v));
			#else
				x0 += v; y0 += v; z0 += v; w0 += v; x1 += v; y1 += v; z1 += v; w1 += v;
			#endif
			return *this;
		}
		TS_INLINE uint16x8_t &operator-=(uint16_t v) {
			#if TS_SSE >= 2
				vec = _mm_sub_epi16(vec, _mm_set1_epi16(v));
			#elif TS_NEON
				vec = vsubq_u16(vec, vdupq_n_u16(v));
			#else
				x0 -= v; y0 -= v; z0 -= v; w0 -= v; x1 -= v; y1 -= v; z1 -= v; w1 -= v;
			#endif
			return *this;
		}
		TS_INLINE uint16x8_t &operator&=(uint16_t v) {
			#if TS_SSE >= 2
				vec = _mm_and_si128(vec, _mm_set1_epi16(v));
			#elif TS_NEON
				vec = vandq_u16(vec, vdupq_n_u16(v));
			#else
				x0 &= v; y0 &= v; z0 &= v; w0 &= v; x1 &= v; y1 &= v; z1 &= v; w1 &= v;
			#endif
			return *this;
		}
		TS_INLINE uint16x8_t &operator|=(uint16_t v) {
			#if TS_SSE >= 2
				vec = _mm_or_si128(vec, _mm_set1_epi16(v));
			#elif TS_NEON
				vec = vorrq_u16(vec, vdupq_n_u16(v));
			#else
				x0 |= v; y0 |= v; z0 |= v; w0 |= v; x1 |= v; y1 |= v; z1 |= v; w1 |= v;
			#endif
			return *this;
		}
		TS_INLINE uint16x8_t &operator^=(uint16_t v) {
			#if TS_SSE >= 2
				vec = _mm_xor_si128(vec, _mm_set1_epi16(v));
			#elif TS_NEON
				vec = veorq_u16(vec, vdupq_n_u16(v));
			#else
				x0 ^= v; y0 ^= v; z0 ^= v; w0 ^= v; x1 ^= v; y1 ^= v; z1 ^= v; w1 ^= v;
			#endif
			return *this;
		}
		TS_INLINE uint16x8_t &operator<<=(uint16_t v) {
			#if TS_SSE >= 2
				vec = _mm_slli_epi16(vec, v);
			#elif TS_NEON
				vec = vshlq_u16(vec, vdupq_n_s16(v));
			#else
				x0 <<= v; y0 <<= v; z0 <<= v; w0 <<= v; x1 <<= v; y1 <<= v; z1 <<= v; w1 <<= v;
			#endif
			return *this;
		}
		TS_INLINE uint16x8_t &operator>>=(uint16_t v) {
			#if TS_SSE >= 2
				vec = _mm_srli_epi16(vec, v);
			#elif TS_NEON
				vec = vshlq_u16(vec, vdupq_n_s16(-v));
			#else
				x0 >>= v; y0 >>= v; z0 >>= v; w0 >>= v; x1 >>= v; y1 >>= v; z1 >>= v; w1 >>= v;
			#endif
			return *this;
		}
		
		/// vector to vector operators
		TS_INLINE uint16x8_t &operator*=(const uint16x8_t &v) {
			#if TS_SSE >= 2
				vec = _mm_mullo_epi16(vec, v.vec);
			#elif TS_NEON
				vec = vmulq_u16(vec, v.vec);
			#else
				x0 *= v.x0; y0 *= v.y0; z0 *= v.z0; w0 *= v.w0; x1 *= v.x1; y1 *= v.y1; z1 *= v.z1; w1 *= v.w1;
			#endif
			return *this;
		}
		TS_INLINE uint16x8_t &operator+=(const uint16x8_t &v) {
			#if TS_SSE >= 2
				vec = _mm_add_epi16(vec, v.vec);
			#elif TS_NEON
				vec = vaddq_u16(vec, v.vec);
			#else
				x0 += v.x0; y0 += v.y0; z0 += v.z0; w0 += v.w0; x1 += v.x1; y1 += v.y1; z1 += v.z1; w1 += v.w1;
			#endif
			return *this;
		}
		TS_INLINE uint16x8_t &operator-=(const uint16x8_t &v) {
			#if TS_SSE >= 2
				vec = _mm_sub_epi16(vec, v.vec);
			#elif TS_NEON
				vec = vsubq_u16(vec, v.vec);
			#else
				x0 -= v.x0; y0 -= v.y0; z0 -= v.z0; w0 -= v.w0; x1 -= v.x1; y1 -= v.y1; z1 -= v.z1; w1 -= v.w1;
			#endif
			return *this;
		}
		TS_INLINE uint16x8_t &operator&=(const uint16x8_t &v) {
			#if TS_SSE >= 2
				vec = _mm_and_si128(vec, v.vec);
			#elif TS_NEON
				vec = vandq_u16(vec, v.vec);
			#else
				x0 &= v.x0; y0 &= v.y0; z0 &= v.z0; w0 &= v.w0; x1 &= v.x1; y1 &= v.y1; z1 &= v.z1; w1 &= v.w1;
			#endif
			return *this;
		}
		TS_INLINE uint16x8_t &operator|=(const uint16x8_t &v) {
			#if TS_SSE >= 2
				vec = _mm_or_si128(vec, v.vec);
			#elif TS_NEON
				vec = vorrq_u16(vec, v.vec);
			#else
				x0 |= v.x0; y0 |= v.y0; z0 |= v.z0; w0 |= v.w0; x1 |= v.x1; y1 |= v.y1; z1 |= v.z1; w1 |= v.w1;
			#endif
			return *this;
		}
		TS_INLINE uint16x8_t &operator^=(const uint16x8_t &v) {
			#if TS_SSE >= 2
				vec = _mm_xor_si128(vec, v.vec);
			#elif TS_NEON
				vec = veorq_u16(vec, v.vec);
			#else
				x0 ^= v.x0; y0 ^= v.y0; z0 ^= v.z0; w0 ^= v.w0; x1 ^= v.x1; y1 ^= v.y1; z1 ^= v.z1; w1 ^= v.w1;
			#endif
			return *this;
		}
		
		/// swizzle vector
		TS_INLINE uint16x8_t xyzw10() const {
			#if TS_SSE >= 2
				return uint16x8_t(_mm_swizzle_epi32(vec, Z, W, X, Y));
			#elif TS_NEON
				return uint16x8_t(vcombine_u16(vget_high_u16(vec), vget_low_u16(vec)));
			#else
				return uint16x8_t(x1, y1, z1, w1, x0, y0, z0, w0);
			#endif
		}
		TS_INLINE uint16x8_t zwxy01() const {
			#if TS_SSE >= 2
				return uint16x8_t(_mm_shufflehi_epi16(_mm_shufflelo_epi16(vec, 0x4e), 0x4e));
			#elif TS_NEON
				return uint16x8_t(vreinterpretq_u16_u32(vrev64q_u32(vreinterpretq_u32_u16(vec))));
			#else
				return uint16x8_t(z0, w0, x0, y0, z1, w1, x1, y1);
			#endif
		}
		TS_INLINE uint16x8_t yxwz01() const {
			#if TS_SSE >= 2
				return uint16x8_t(_mm_shufflehi_epi16(_mm_shufflelo_epi16(vec, 0xb1), 0xb1));
			#elif TS_NEON
				return uint16x8_t(vrev32q_u16(vec));
			#else
				return uint16x8_t(y0, x0, w0, z0, y1, x1, w1, z1);
			#endif
		}
		uint32x4_t xyzw0() const;
		uint32x4_t xyzw1() const;
		
		/// sum vector components
		TS_INLINE uint16_t sum() const {
			#if TS_SSE >= 4
				__m128i temp = _mm_hadd_epi16(vec, vec);
				temp = _mm_hadd_epi16(temp, temp);
				temp = _mm_hadd_epi16(temp, temp);
				return (uint16_t)_mm_extract_epi16(temp, 0);
			#elif TS_SSE >= 2
				__m128i temp = _mm_add_epi16(vec, _mm_swizzle_epi32(vec, Z, W, X, Y));
				temp = _mm_add_epi16(temp, _mm_shufflelo_epi16(temp, 0x4e));
				temp = _mm_add_epi16(temp, _mm_shufflelo_epi16(temp, 0xb1));
				return (uint16_t)_mm_extract_epi16(temp, 0);
			#elif TS_NEON
				::uint16x4_t temp = vadd_u16(vget_high_u16(vec), vget_low_u16(vec));
				temp = vadd_u16(temp, vrev64_u16(temp));
				temp = vadd_u16(temp, vrev32_u16(temp));
				return _vget_lane_u16<0>(temp);
			#else
				return x0 + y0 + z0 + w0 + x1 + y1 + z1 + w1;
			#endif
		}
		
		enum {
			Size = 8,
		};
		
		union {
			struct {
				uint16_t x0, y0, z0, w0;
				uint16_t x1, y1, z1, w1;
			};
			uint16_t v[Size];
			#if TS_SSE >= 2
				__m128i vec;
			#elif TS_NEON
				::uint16x8_t vec;
			#endif
		};
	};
	
	/// vector to vector operators
	TS_INLINE uint16x8_t operator*(const uint16x8_t &v0, uint16_t v1) {
		#if TS_SSE >= 2
			return uint16x8_t(_mm_mullo_epi16(v0.vec, _mm_set1_epi16(v1)));
		#elif TS_NEON
			return uint16x8_t(vmulq_n_u16(v0.vec, v1));
		#else
			return uint16x8_t(v0.x0 * v1, v0.y0 * v1, v0.z0 * v1, v0.w0 * v1, v0.x1 * v1, v0.y1 * v1, v0.z1 * v1, v0.w1 * v1);
		#endif
	}
	TS_INLINE uint16x8_t operator+(const uint16x8_t &v0, uint16_t v1) {
		#if TS_SSE >= 2
			return uint16x8_t(_mm_add_epi16(v0.vec, _mm_set1_epi16(v1)));
		#elif TS_NEON
			return uint16x8_t(vaddq_u16(v0.vec, vdupq_n_u16(v1)));
		#else
			return uint16x8_t(v0.x0 + v1, v0.y0 + v1, v0.z0 + v1, v0.w0 + v1, v0.x1 + v1, v0.y1 + v1, v0.z1 + v1, v0.w1 + v1);
		#endif
	}
	TS_INLINE uint16x8_t operator-(const uint16x8_t &v0, uint16_t v1) {
		#if TS_SSE >= 2
			return uint16x8_t(_mm_sub_epi16(v0.vec, _mm_set1_epi16(v1)));
		#elif TS_NEON
			return uint16x8_t(vsubq_u16(v0.vec, vdupq_n_u16(v1)));
		#else
			return uint16x8_t(v0.x0 - v1, v0.y0 - v1, v0.z0 - v1, v0.w0 - v1, v0.x1 - v1, v0.y1 - v1, v0.z1 - v1, v0.w1 - v1);
		#endif
	}
	TS_INLINE uint16x8_t operator&(const uint16x8_t &v0, uint16_t v1) {
		#if TS_SSE >= 2
			return uint16x8_t(_mm_and_si128(v0.vec, _mm_set1_epi16(v1)));
		#elif TS_NEON
			return uint16x8_t(vandq_u16(v0.vec, vdupq_n_u16(v1)));
		#else
			return uint16x8_t(v0.x0 & v1, v0.y0 & v1, v0.z0 & v1, v0.w0 & v1, v0.x1 & v1, v0.y1 & v1, v0.z1 & v1, v0.w1 & v1);
		#endif
	}
	TS_INLINE uint16x8_t operator|(const uint16x8_t &v0, uint16_t v1) {
		#if TS_SSE >= 2
			return uint16x8_t(_mm_or_si128(v0.vec, _mm_set1_epi16(v1)));
		#elif TS_NEON
			return uint16x8_t(vorrq_u16(v0.vec, vdupq_n_u16(v1)));
		#else
			return uint16x8_t(v0.x0 | v1, v0.y0 | v1, v0.z0 | v1, v0.w0 | v1, v0.x1 | v1, v0.y1 | v1, v0.z1 | v1, v0.w1 | v1);
		#endif
	}
	TS_INLINE uint16x8_t operator^(const uint16x8_t &v0, uint16_t v1) {
		#if TS_SSE >= 2
			return uint16x8_t(_mm_xor_si128(v0.vec, _mm_set1_epi16(v1)));
		#elif TS_NEON
			return uint16x8_t(veorq_u16(v0.vec, vdupq_n_u16(v1)));
		#else
			return uint16x8_t(v0.x0 ^ v1, v0.y0 ^ v1, v0.z0 ^ v1, v0.w0 ^ v1, v0.x1 ^ v1, v0.y1 ^ v1, v0.z1 ^ v1, v0.w1 ^ v1);
		#endif
	}
	TS_INLINE uint16x8_t operator<<(const uint16x8_t &v0, uint16_t v1) {
		#if TS_SSE >= 2
			return uint16x8_t(_mm_slli_epi16(v0.vec, v1));
		#elif TS_NEON
			return uint16x8_t(vshlq_u16(v0.vec, vdupq_n_s16(v1)));
		#else
			return uint16x8_t(v0.x0 << v1, v0.y0 << v1, v0.z0 << v1, v0.w0 << v1, v0.x1 << v1, v0.y1 << v1, v0.z1 << v1, v0.w1 << v1);
		#endif
	}
	TS_INLINE uint16x8_t operator>>(const uint16x8_t &v0, uint16_t v1) {
		#if TS_SSE >= 2
			return uint16x8_t(_mm_srli_epi16(v0.vec, v1));
		#elif TS_NEON
			return uint16x8_t(vshlq_u16(v0.vec, vdupq_n_s16(-v1)));
		#else
			return uint16x8_t(v0.x0 >> v1, v0.y0 >> v1, v0.z0 >> v1, v0.w0 >> v1, v0.x1 >> v1, v0.y1 >> v1, v0.z1 >> v1, v0.w1 >> v1);
		#endif
	}
	
	/// vector to vector operators
	TS_INLINE uint16x8_t operator*(const uint16x8_t &v0, const uint16x8_t &v1) {
		#if TS_SSE >= 2
			return uint16x8_t(_mm_mullo_epi16(v0.vec, v1.vec));
		#elif TS_NEON
			return uint16x8_t(vmulq_u16(v0.vec, v1.vec));
		#else
			return uint16x8_t(v0.x0 * v1.x0, v0.y0 * v1.y0, v0.z0 * v1.z0, v0.w0 * v1.w0, v0.x1 * v1.x1, v0.y1 * v1.y1, v0.z1 * v1.z1, v0.w1 * v1.w1);
		#endif
	}
	TS_INLINE uint16x8_t operator+(const uint16x8_t &v0, const uint16x8_t &v1) {
		#if TS_SSE >= 2
			return uint16x8_t(_mm_add_epi16(v0.vec, v1.vec));
		#elif TS_NEON
			return uint16x8_t(vaddq_u16(v0.vec, v1.vec));
		#else
			return uint16x8_t(v0.x0 + v1.x0, v0.y0 + v1.y0, v0.z0 + v1.z0, v0.w0 + v1.w0, v0.x1 + v1.x1, v0.y1 + v1.y1, v0.z1 + v1.z1, v0.w1 + v1.w1);
		#endif
	}
	TS_INLINE uint16x8_t operator-(const uint16x8_t &v0, const uint16x8_t &v1) {
		#if TS_SSE >= 2
			return uint16x8_t(_mm_sub_epi16(v0.vec, v1.vec));
		#elif TS_NEON
			return uint16x8_t(vsubq_u16(v0.vec, v1.vec));
		#else
			return uint16x8_t(v0.x0 - v1.x0, v0.y0 - v1.y0, v0.z0 - v1.z0, v0.w0 - v1.w0, v0.x1 - v1.x1, v0.y1 - v1.y1, v0.z1 - v1.z1, v0.w1 - v1.w1);
		#endif
	}
	TS_INLINE uint16x8_t operator&(const uint16x8_t &v0, const uint16x8_t &v1) {
		#if TS_SSE >= 2
			return uint16x8_t(_mm_and_si128(v0.vec, v1.vec));
		#elif TS_NEON
			return uint16x8_t(vandq_u16(v0.vec, v1.vec));
		#else
			return uint16x8_t(v0.x0 & v1.x0, v0.y0 & v1.y0, v0.z0 & v1.z0, v0.w0 & v1.w0, v0.x1 & v1.x1, v0.y1 & v1.y1, v0.z1 & v1.z1, v0.w1 & v1.w1);
		#endif
	}
	TS_INLINE uint16x8_t operator|(const uint16x8_t &v0, const uint16x8_t &v1) {
		#if TS_SSE >= 2
			return uint16x8_t(_mm_or_si128(v0.vec, v1.vec));
		#elif TS_NEON
			return uint16x8_t(vorrq_u16(v0.vec, v1.vec));
		#else
			return uint16x8_t(v0.x0 | v1.x0, v0.y0 | v1.y0, v0.z0 | v1.z0, v0.w0 | v1.w0, v0.x1 | v1.x1, v0.y1 | v1.y1, v0.z1 | v1.z1, v0.w1 | v1.w1);
		#endif
	}
	TS_INLINE uint16x8_t operator^(const uint16x8_t &v0, const uint16x8_t &v1) {
		#if TS_SSE >= 2
			return uint16x8_t(_mm_xor_si128(v0.vec, v1.vec));
		#elif TS_NEON
			return uint16x8_t(veorq_u16(v0.vec, v1.vec));
		#else
			return uint16x8_t(v0.x0 ^ v1.x0, v0.y0 ^ v1.y0, v0.z0 ^ v1.z0, v0.w0 ^ v1.w0, v0.x1 ^ v1.x1, v0.y1 ^ v1.y1, v0.z1 ^ v1.z1, v0.w1 ^ v1.w1);
		#endif
	}
	
	/// min/max functions
	TS_INLINE uint16x8_t min(const uint16x8_t &v0, const uint16x8_t &v1) {
		#if TS_SSE >= 4
			return uint16x8_t(_mm_min_epu16(v0.vec, v1.vec));
		#elif TS_NEON
			return uint16x8_t(vminq_u16(v0.vec, v1.vec));
		#else
			return uint16x8_t(min(v0.x0, v1.x0), min(v0.y0, v1.y0), min(v0.z0, v1.z0), min(v0.w0, v1.w0), min(v0.x1, v1.x1), min(v0.y1, v1.y1), min(v0.z1, v1.z1), min(v0.w1, v1.w1));
		#endif
	}
	TS_INLINE uint16x8_t max(const uint16x8_t &v0, const uint16x8_t &v1) {
		#if TS_SSE >= 4
			return uint16x8_t(_mm_max_epu16(v0.vec, v1.vec));
		#elif TS_NEON
			return uint16x8_t(vmaxq_u16(v0.vec, v1.vec));
		#else
			return uint16x8_t(max(v0.x0, v1.x0), max(v0.y0, v1.y0), max(v0.z0, v1.z0), max(v0.w0, v1.w0), max(v0.x1, v1.x1), max(v0.y1, v1.y1), max(v0.z1, v1.z1), max(v0.w1, v1.w1));
		#endif
	}
	
	/// range functions
	TS_INLINE uint16x8_t clamp(const uint16x8_t &v, uint16_t v0, const uint16_t v1) {
		return min(max(v, uint16x8_t(v0)), uint16x8_t(v1));
	}
	TS_INLINE uint16x8_t clamp(const uint16x8_t &v, const uint16x8_t &v0, const uint16x8_t &v1) {
		return min(max(v, v0), v1);
	}
	
	/// select functions
	TS_INLINE uint16x8_t select(const uint16x8_t &v0, const uint16x8_t &v1, const int16x8_t &s) {
		#if TS_SSE >= 2
			return uint16x8_t(_mm_xor_si128(v0.vec, _mm_and_si128(_mm_xor_si128(v0.vec, v1.vec), _mm_srai_epi16(s.vec, 15))));
		#elif TS_NEON
			return uint16x8_t(vbslq_u16(vcgeq_s16(s.vec, vdupq_n_s16(0)), v0.vec, v1.vec));
		#else
			return uint16x8_t(select(v0.x0, v1.x0, s.x0), select(v0.y0, v1.y0, s.y0), select(v0.z0, v1.z0, s.z0), select(v0.w0, v1.w0, s.w0), select(v0.x1, v1.x1, s.x1), select(v0.y1, v1.y1, s.y1), select(v0.z1, v1.z1, s.z1), select(v0.w1, v1.w1, s.w1));
		#endif
	}
	TS_INLINE uint16x8_t select(const uint16x8_t &v0, const uint16x8_t &v1, int16_t s) {
		return select(v0, v1, int16x8_t(s));
	}
	
	/*****************************************************************************\
	 *
	 * uint32x4_t
	 *
	\*****************************************************************************/
	
	/**
	 * Vector of four uint32_t components
	 */
	struct TS_ALIGNAS16 uint32x4_t {
		
		uint32x4_t() { }
		explicit uint32x4_t(const int32x4_t &v);
		explicit uint32x4_t(const float32x4_t &v);
		explicit uint32x4_t(const float64x4_t &v);
		explicit uint32x4_t(const uint32_t *v) { set(v); }
		uint32x4_t(const uint32_t *v, uint32_t w) { set(v, w); }
		#if TS_SSE >= 2
			uint32x4_t(const uint32x4_t &v) : vec(v.vec) { }
			explicit uint32x4_t(__m128i v) : vec(v) { }
			explicit uint32x4_t(uint32_t v) : vec(_mm_set1_epi32((int32_t)v)) { }
			uint32x4_t(uint32_t x, uint32_t y, uint32_t z, uint32_t w = 0) : vec(_mm_setr_epi32((int32_t)x, (int32_t)y, (int32_t)z, (int32_t)w)) { }
		#elif TS_NEON
			uint32x4_t(const uint32x4_t &v) : vec(v.vec) { }
			explicit uint32x4_t(::uint32x4_t v) : vec(v) { }
			explicit uint32x4_t(uint32_t v) : vec(vdupq_n_u32(v)) { }
			uint32x4_t(uint32_t x, uint32_t y, uint32_t z, uint32_t w = 0) : vec(vsetq_u32(x, y, z, w)) { }
		#else
			explicit uint32x4_t(uint32_t v) : x(v), y(v), z(v), w(v) { }
			uint32x4_t(uint32_t x, uint32_t y, uint32_t z, uint32_t w = 0) : x(x), y(y), z(z), w(w) { }
		#endif
		
		/// cast vector data
		TS_INLINE int16x8_t asi16x8() const {
			#if TS_SSE >= 2
				return int16x8_t(vec);
			#elif TS_NEON
				return int16x8_t(vreinterpretq_s16_u32(vec));
			#else
				return int16x8_t((int16_t*)v);
			#endif
		}
		TS_INLINE int32x4_t asi32x4() const {
			#if TS_SSE >= 2
				return int32x4_t(vec);
			#elif TS_NEON
				return int32x4_t(vreinterpretq_s32_u32(vec));
			#else
				return int32x4_t((int32_t*)v);
			#endif
		}
		TS_INLINE uint16x8_t asu16x8() const {
			#if TS_SSE >= 2
				return uint16x8_t(vec);
			#elif TS_NEON
				return uint16x8_t(vreinterpretq_u16_u32(vec));
			#else
				return uint16x8_t((uint16_t*)v);
			#endif
		}
		TS_INLINE float16x8_t asf16x8() const;
		TS_INLINE float32x4_t asf32x4() const;
		
		/// update vector data
		TS_INLINE void set(const uint32x4_t &v) {
			#if TS_SSE >= 2
				vec = v.vec;
			#elif TS_NEON
				vec = v.vec;
			#else
				x = v.x; y = v.y; z = v.z; w = v.w;
			#endif
		}
		TS_INLINE void set(uint32_t X, uint32_t Y, uint32_t Z, uint32_t W) {
			#if TS_SSE >= 2
				vec = _mm_setr_epi32((int32_t)X, (int32_t)Y, (int32_t)Z, (int32_t)W);
			#elif TS_NEON
				vec = vsetq_u32(X, Y, Z, W);
			#else
				x = X; y = Y; z = Z; w = W;
			#endif
		}
		TS_INLINE void set(const uint32_t *TS_RESTRICT v, uint32_t W) {
			#if TS_SSE >= 2
				vec = _mm_setr_epi32((int32_t)v[0], (int32_t)v[1], (int32_t)v[2], (int32_t)W);
			#elif TS_NEON
				vec = vsetq_u32(v[0], v[1], v[2], W);
			#else
				x = v[0]; y = v[1]; z = v[2]; w = W;
			#endif
		}
		TS_INLINE void set(const uint32_t *TS_RESTRICT v) {
			#if TS_SSE >= 2
				vec = _mm_castps_si128(_mm_load_ps((const float32_t*)v));
			#elif TS_NEON
				vec = _vld1q_u32(v);
			#else
				x = v[0]; y = v[1]; z = v[2]; w = v[3];
			#endif
		}
		TS_INLINE void get(uint32_t *TS_RESTRICT v) const {
			#if TS_SSE >= 2
				_mm_stream_ps((float32_t*)v, _mm_castsi128_ps(vec));
			#elif TS_NEON
				_vst1q_u32(v, vec);
			#else
				v[0] = x; v[1] = y; v[2] = z; v[3] = w;
			#endif
		}
		template <uint32_t Index> TS_INLINE void set(uint32_t V) {
			#if TS_SSE >= 4
				vec = _mm_insert_epi32(vec, (int32_t)V, Index);
			#elif TS_NEON
				vec = _vsetq_lane_u32<Index>(V, vec);
			#else
				v[Index] = V;
			#endif
		}
		template <uint32_t Index> TS_INLINE uint32_t get() const {
			#if TS_SSE >= 4
				return (uint32_t)_mm_extract_epi32(vec, Index);
			#elif TS_NEON
				return _vgetq_lane_u32<Index>(vec);
			#else
				return v[Index];
			#endif
		}
		template <uint32_t Index> TS_INLINE uint32x4_t get4() const {
			#if TS_SSE >= 2
				return uint32x4_t(_mm_shuffle_epi32(vec, (Index << 6) | (Index << 4) | (Index << 2) | Index));
			#elif TS_NEON
				return uint32x4_t(vdupq_n_u32(_vgetq_lane_u32<Index>(vec)));
			#else
				return uint32x4_t(v[Index]);
			#endif
		}
		
		/// vector to scalar operators
		TS_INLINE uint32x4_t &operator*=(uint32_t v) {
			#if TS_SSE >= 4
				vec = _mm_mullo_epi32(vec, _mm_set1_epi32(v));
			#elif TS_NEON
				vec = vmulq_n_u32(vec, v);
			#else
				x *= v; y *= v; z *= v; w *= v;
			#endif
			return *this;
		}
		TS_INLINE uint32x4_t &operator+=(uint32_t v) {
			#if TS_SSE >= 2
				vec = _mm_add_epi32(vec, _mm_set1_epi32(v));
			#elif TS_NEON
				vec = vaddq_u32(vec, vdupq_n_u32(v));
			#else
				x += v; y += v; z += v; w += v;
			#endif
			return *this;
		}
		TS_INLINE uint32x4_t &operator-=(uint32_t v) {
			#if TS_SSE >= 2
				vec = _mm_sub_epi32(vec, _mm_set1_epi32(v));
			#elif TS_NEON
				vec = vsubq_u32(vec, vdupq_n_u32(v));
			#else
				x -= v; y -= v; z -= v; w -= v;
			#endif
			return *this;
		}
		TS_INLINE uint32x4_t &operator&=(uint32_t v) {
			#if TS_SSE >= 2
				vec = _mm_and_si128(vec, _mm_set1_epi32(v));
			#elif TS_NEON
				vec = vandq_u32(vec, vdupq_n_u32(v));
			#else
				x &= v; y &= v; z &= v; w &= v;
			#endif
			return *this;
		}
		TS_INLINE uint32x4_t &operator|=(uint32_t v) {
			#if TS_SSE >= 2
				vec = _mm_or_si128(vec, _mm_set1_epi32(v));
			#elif TS_NEON
				vec = vorrq_u32(vec, vdupq_n_u32(v));
			#else
				x |= v; y |= v; z |= v; w |= v;
			#endif
			return *this;
		}
		TS_INLINE uint32x4_t &operator^=(uint32_t v) {
			#if TS_SSE >= 2
				vec = _mm_xor_si128(vec, _mm_set1_epi32(v));
			#elif TS_NEON
				vec = veorq_u32(vec, vdupq_n_u32(v));
			#else
				x ^= v; y ^= v; z ^= v; w ^= v;
			#endif
			return *this;
		}
		TS_INLINE uint32x4_t &operator<<=(uint32_t v) {
			#if TS_SSE >= 2
				vec = _mm_slli_epi32(vec, v);
			#elif TS_NEON
				vec = vshlq_u32(vec, vdupq_n_s32(v));
			#else
				x <<= v; y <<= v; z <<= v; w <<= v;
			#endif
			return *this;
		}
		TS_INLINE uint32x4_t &operator>>=(uint32_t v) {
			#if TS_SSE >= 2
				vec = _mm_srli_epi32(vec, v);
			#elif TS_NEON
				vec = vshlq_u32(vec, vdupq_n_s32(-(int32_t)v));
			#else
				x >>= v; y >>= v; z >>= v; w >>= v;
			#endif
			return *this;
		}
		
		/// vector to vector operators
		TS_INLINE uint32x4_t &operator*=(const uint32x4_t &v) {
			#if TS_SSE >= 4
				vec = _mm_mullo_epi32(vec, v.vec);
			#elif TS_NEON
				vec = vmulq_u32(vec, v.vec);
			#else
				x *= v.x; y *= v.y; z *= v.z; w *= v.w;
			#endif
			return *this;
		}
		TS_INLINE uint32x4_t &operator+=(const uint32x4_t &v) {
			#if TS_SSE >= 2
				vec = _mm_add_epi32(vec, v.vec);
			#elif TS_NEON
				vec = vaddq_u32(vec, v.vec);
			#else
				x += v.x; y += v.y; z += v.z; w += v.w;
			#endif
			return *this;
		}
		TS_INLINE uint32x4_t &operator-=(const uint32x4_t &v) {
			#if TS_SSE >= 2
				vec = _mm_sub_epi32(vec, v.vec);
			#elif TS_NEON
				vec = vsubq_u32(vec, v.vec);
			#else
				x -= v.x; y -= v.y; z -= v.z; w -= v.w;
			#endif
			return *this;
		}
		TS_INLINE uint32x4_t &operator&=(const uint32x4_t &v) {
			#if TS_SSE >= 2
				vec = _mm_and_si128(vec, v.vec);
			#elif TS_NEON
				vec = vandq_u32(vec, v.vec);
			#else
				x &= v.x; y &= v.y; z &= v.z; w &= v.w;
			#endif
			return *this;
		}
		TS_INLINE uint32x4_t &operator|=(const uint32x4_t &v) {
			#if TS_SSE >= 2
				vec = _mm_or_si128(vec, v.vec);
			#elif TS_NEON
				vec = vorrq_u32(vec, v.vec);
			#else
				x |= v.x; y |= v.y; z |= v.z; w |= v.w;
			#endif
			return *this;
		}
		TS_INLINE uint32x4_t &operator^=(const uint32x4_t &v) {
			#if TS_SSE >= 2
				vec = _mm_xor_si128(vec, v.vec);
			#elif TS_NEON
				vec = veorq_u32(vec, v.vec);
			#else
				x ^= v.x; y ^= v.y; z ^= v.z; w ^= v.w;
			#endif
			return *this;
		}
		
		/// swizzle vector
		TS_INLINE uint32x4_t zwxy() const {
			#if TS_SSE >= 2
				return uint32x4_t(_mm_swizzle_epi32(vec, Z, W, X, Y));
			#elif TS_NEON
				return uint32x4_t(vcombine_u32(vget_high_u32(vec), vget_low_u32(vec)));
			#else
				return uint32x4_t(z, w, x, y);
			#endif
		}
		TS_INLINE uint32x4_t yxwz() const {
			#if TS_SSE >= 2
				return uint32x4_t(_mm_swizzle_epi32(vec, Y, X, W, Z));
			#elif TS_NEON
				return uint32x4_t(vrev64q_u32(vec));
			#else
				return uint32x4_t(y, x, w, z);
			#endif
		}
		
		/// sum vector components
		TS_INLINE uint32_t sum() const {
			#if TS_SSE >= 4
				__m128i temp = _mm_hadd_epi32(vec, vec);
				temp = _mm_hadd_epi32(temp, temp);
				return (uint32_t)_mm_extract_epi32(temp, 0);
			#elif TS_SSE >= 2
				__m128i temp = _mm_add_epi32(vec, _mm_swizzle_epi32(vec, Z, W, X, Y));
				temp = _mm_add_epi32(temp, _mm_swizzle_epi32(temp, Y, X, W, Z));
				return f32u32(_mm_cvtss_f32(_mm_castsi128_ps(temp))).u;
			#elif TS_NEON
				::uint32x2_t temp = vadd_u32(vget_high_u32(vec), vget_low_u32(vec));
				temp = vadd_u32(temp, vrev64_u32(temp));
				return _vget_lane_u32<0>(temp);
			#else
				return x + y + z + w;
			#endif
		}
		
		enum {
			Size = 4,
		};
		
		union {
			struct {
				uint32_t x, y, z, w;
			};
			uint32_t v[Size];
			#if TS_SSE >= 2
				__m128i vec;
			#elif TS_NEON
				::uint32x4_t vec;
			#endif
		};
	};
	
	/// vector to scalar operators
	TS_INLINE uint32x4_t operator*(const uint32x4_t &v0, uint32_t v1) {
		#if TS_SSE >= 4
			return uint32x4_t(_mm_mullo_epi32(v0.vec, _mm_set1_epi32(v1)));
		#elif TS_NEON
			return uint32x4_t(vmulq_n_u32(v0.vec, v1));
		#else
			return uint32x4_t(v0.x * v1, v0.y * v1, v0.z * v1, v0.w * v1);
		#endif
	}
	TS_INLINE uint32x4_t operator+(const uint32x4_t &v0, uint32_t v1) {
		#if TS_SSE >= 2
			return uint32x4_t(_mm_add_epi32(v0.vec, _mm_set1_epi32(v1)));
		#elif TS_NEON
			return uint32x4_t(vaddq_u32(v0.vec, vdupq_n_u32(v1)));
		#else
			return uint32x4_t(v0.x + v1, v0.y + v1, v0.z + v1, v0.w + v1);
		#endif
	}
	TS_INLINE uint32x4_t operator-(const uint32x4_t &v0, uint32_t v1) {
		#if TS_SSE >= 2
			return uint32x4_t(_mm_sub_epi32(v0.vec, _mm_set1_epi32(v1)));
		#elif TS_NEON
			return uint32x4_t(vsubq_u32(v0.vec, vdupq_n_u32(v1)));
		#else
			return uint32x4_t(v0.x - v1, v0.y - v1, v0.z - v1, v0.w - v1);
		#endif
	}
	TS_INLINE uint32x4_t operator&(const uint32x4_t &v0, uint32_t v1) {
		#if TS_SSE >= 2
			return uint32x4_t(_mm_and_si128(v0.vec, _mm_set1_epi32(v1)));
		#elif TS_NEON
			return uint32x4_t(vandq_u32(v0.vec, vdupq_n_u32(v1)));
		#else
			return uint32x4_t(v0.x & v1, v0.y & v1, v0.z & v1, v0.w & v1);
		#endif
	}
	TS_INLINE uint32x4_t operator|(const uint32x4_t &v0, uint32_t v1) {
		#if TS_SSE >= 2
			return uint32x4_t(_mm_or_si128(v0.vec, _mm_set1_epi32(v1)));
		#elif TS_NEON
			return uint32x4_t(vorrq_u32(v0.vec, vdupq_n_u32(v1)));
		#else
			return uint32x4_t(v0.x | v1, v0.y | v1, v0.z | v1, v0.w | v1);
		#endif
	}
	TS_INLINE uint32x4_t operator^(const uint32x4_t &v0, uint32_t v1) {
		#if TS_SSE >= 2
			return uint32x4_t(_mm_xor_si128(v0.vec, _mm_set1_epi32(v1)));
		#elif TS_NEON
			return uint32x4_t(veorq_u32(v0.vec, vdupq_n_u32(v1)));
		#else
			return uint32x4_t(v0.x ^ v1, v0.y ^ v1, v0.z ^ v1, v0.w ^ v1);
		#endif
	}
	TS_INLINE uint32x4_t operator<<(const uint32x4_t &v0, uint32_t v1) {
		#if TS_SSE >= 2
			return uint32x4_t(_mm_slli_epi32(v0.vec, v1));
		#elif TS_NEON
			return uint32x4_t(vshlq_u32(v0.vec, vdupq_n_s32(v1)));
		#else
			return uint32x4_t(v0.x << v1, v0.y << v1, v0.z << v1, v0.w << v1);
		#endif
	}
	TS_INLINE uint32x4_t operator>>(const uint32x4_t &v0, uint32_t v1) {
		#if TS_SSE >= 2
			return uint32x4_t(_mm_srli_epi32(v0.vec, v1));
		#elif TS_NEON
			return uint32x4_t(vshlq_u32(v0.vec, vdupq_n_s32(-(int32_t)v1)));
		#else
			return uint32x4_t(v0.x >> v1, v0.y >> v1, v0.z >> v1, v0.w >> v1);
		#endif
	}
	
	/// vector to vector operators
	TS_INLINE uint32x4_t operator*(const uint32x4_t &v0, const uint32x4_t &v1) {
		#if TS_SSE >= 4
			return uint32x4_t(_mm_mullo_epi32(v0.vec, v1.vec));
		#elif TS_NEON
			return uint32x4_t(vmulq_u32(v0.vec, v1.vec));
		#else
			return uint32x4_t(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z, v0.w * v1.w);
		#endif
	}
	TS_INLINE uint32x4_t operator+(const uint32x4_t &v0, const uint32x4_t &v1) {
		#if TS_SSE >= 2
			return uint32x4_t(_mm_add_epi32(v0.vec, v1.vec));
		#elif TS_NEON
			return uint32x4_t(vaddq_u32(v0.vec, v1.vec));
		#else
			return uint32x4_t(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w);
		#endif
	}
	TS_INLINE uint32x4_t operator-(const uint32x4_t &v0, const uint32x4_t &v1) {
		#if TS_SSE >= 2
			return uint32x4_t(_mm_sub_epi32(v0.vec, v1.vec));
		#elif TS_NEON
			return uint32x4_t(vsubq_u32(v0.vec, v1.vec));
		#else
			return uint32x4_t(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w);
		#endif
	}
	TS_INLINE uint32x4_t operator&(const uint32x4_t &v0, const uint32x4_t &v1) {
		#if TS_SSE >= 2
			return uint32x4_t(_mm_and_si128(v0.vec, v1.vec));
		#elif TS_NEON
			return uint32x4_t(vandq_u32(v0.vec, v1.vec));
		#else
			return uint32x4_t(v0.x & v1.x, v0.y & v1.y, v0.z & v1.z, v0.w & v1.w);
		#endif
	}
	TS_INLINE uint32x4_t operator|(const uint32x4_t &v0, const uint32x4_t &v1) {
		#if TS_SSE >= 2
			return uint32x4_t(_mm_or_si128(v0.vec, v1.vec));
		#elif TS_NEON
			return uint32x4_t(vorrq_u32(v0.vec, v1.vec));
		#else
			return uint32x4_t(v0.x | v1.x, v0.y | v1.y, v0.z | v1.z, v0.w | v1.w);
		#endif
	}
	TS_INLINE uint32x4_t operator^(const uint32x4_t &v0, const uint32x4_t &v1) {
		#if TS_SSE >= 2
			return uint32x4_t(_mm_xor_si128(v0.vec, v1.vec));
		#elif TS_NEON
			return uint32x4_t(veorq_u32(v0.vec, v1.vec));
		#else
			return uint32x4_t(v0.x ^ v1.x, v0.y ^ v1.y, v0.z ^ v1.z, v0.w ^ v1.w);
		#endif
	}
	
	/// min/max functions
	TS_INLINE uint32x4_t min(const uint32x4_t &v0, const uint32x4_t &v1) {
		#if TS_SSE >= 4
			return uint32x4_t(_mm_min_epu32(v0.vec, v1.vec));
		#elif TS_NEON
			return uint32x4_t(vminq_u32(v0.vec, v1.vec));
		#else
			return uint32x4_t(min(v0.x, v1.x), min(v0.y, v1.y), min(v0.z, v1.z), min(v0.w, v1.w));
		#endif
	}
	TS_INLINE uint32x4_t max(const uint32x4_t &v0, const uint32x4_t &v1) {
		#if TS_SSE >= 4
			return uint32x4_t(_mm_max_epu32(v0.vec, v1.vec));
		#elif TS_NEON
			return uint32x4_t(vmaxq_u32(v0.vec, v1.vec));
		#else
			return uint32x4_t(max(v0.x, v1.x), max(v0.y, v1.y), max(v0.z, v1.z), max(v0.w, v1.w));
		#endif
	}
	
	/// range functions
	TS_INLINE uint32x4_t clamp(const uint32x4_t &v, uint32_t v0, uint32_t v1) {
		return min(max(v, uint32x4_t(v0)), uint32x4_t(v1));
	}
	TS_INLINE uint32x4_t clamp(const uint32x4_t &v, const uint32x4_t &v0, const uint32x4_t &v1) {
		return min(max(v, v0), v1);
	}
	
	/// select functions
	TS_INLINE uint32x4_t select(const uint32x4_t &v0, const uint32x4_t &v1, const int32x4_t &s) {
		#if TS_AVX >= 1
			return uint32x4_t(_mm_castps_si128(_mm_blendv_ps(_mm_castsi128_ps(v0.vec), _mm_castsi128_ps(v1.vec), _mm_castsi128_ps(s.vec))));
		#elif TS_SSE >= 2
			return uint32x4_t(_mm_xor_si128(v0.vec, _mm_and_si128(_mm_xor_si128(v0.vec, v1.vec), _mm_srai_epi32(s.vec, 31))));
		#elif TS_NEON
			return uint32x4_t(vbslq_u32(vcgeq_s32(s.vec, vdupq_n_s32(0)), v0.vec, v1.vec));
		#else
			return uint32x4_t(select(v0.x, v1.x, s.x), select(v0.y, v1.y, s.y), select(v0.z, v1.z, s.z), select(v0.w, v1.w, s.w));
		#endif
	}
	TS_INLINE uint32x4_t select(const uint32x4_t &v0, const uint32x4_t &v1, int32_t s) {
		return select(v0, v1, int32x4_t(s));
	}
	
	/*****************************************************************************\
	 *
	 * uint32x8_t
	 *
	\*****************************************************************************/
	
	/**
	 * Vector of eight uint32_t components
	 */
	struct TS_ALIGNAS32 uint32x8_t {
		
		uint32x8_t() { }
		explicit uint32x8_t(const int32x8_t &v);
		explicit uint32x8_t(const float32x8_t &v);
		explicit uint32x8_t(const float64x8_t &v);
		explicit uint32x8_t(const uint32_t *v) { set(v); }
		#if TS_AVX >= 1
			uint32x8_t(const uint32x8_t &v) : vec(v.vec) { }
			explicit uint32x8_t(__m256i v) : vec(v) { }
			explicit uint32x8_t(uint32_t v) : vec(_mm256_set1_epi32(v)) { }
			uint32x8_t(__m128i v0, __m128i v1) : vec(_mm256_setr_m128i(v0, v1)) { }
			#if TS_AVX >= 2
				explicit uint32x8_t(const uint16x8_t &v) : vec(_mm256_cvtepu16_epi32(v.vec)) { }
			#else
				explicit uint32x8_t(const uint16x8_t &v) : vec(_mm256_setr_m128i(_mm_cvtepu16_epi32(v.vec), _mm_cvtepu16_epi32(_mm_swizzle_epi32(v.vec, Z, W, Z, W)))) { }
			#endif
			uint32x8_t(const uint32x4_t &v0, const uint32x4_t &v1) : vec(_mm256_setr_m128i(v0.vec, v1.vec)) { }
			uint32x8_t(uint32_t x0, uint32_t y0, uint32_t z0, uint32_t w0, uint32_t x1, uint32_t y1, uint32_t z1, uint32_t w1) : vec(_mm256_setr_epi32((int32_t)x0, (int32_t)y0, (int32_t)z0, (int32_t)w0, (int32_t)x1, (int32_t)y1, (int32_t)z1, (int32_t)w1)) { }
		#elif TS_SSE >= 1
			uint32x8_t(const uint32x8_t &v) : vec0(v.vec0), vec1(v.vec1) { }
			uint32x8_t(__m128i v0, __m128i v1) : vec0(v0), vec1(v1) { }
			explicit uint32x8_t(uint32_t v) : vec0(_mm_set1_epi32(v)), vec1(_mm_set1_epi32(v)) { }
			#if TS_SSE >= 4
				explicit uint32x8_t(const uint16x8_t &v) : vec0(_mm_cvtepu16_epi32(v.vec)), vec1(_mm_cvtepu16_epi32(_mm_swizzle_epi32(v.vec, Z, W, Z, W))) { }
			#else
				explicit uint32x8_t(const uint16x8_t &v) : x0(v.x0), y0(v.y0), z0(v.z0), w0(v.w0), x1(v.x1), y1(v.y1), z1(v.z1), w1(v.w1) { }
			#endif
			#if TS_SSE >= 2
				uint32x8_t(const uint32x4_t &v0, const uint32x4_t &v1) : vec0(v0.vec), vec1(v1.vec) { }
			#else
				uint32x8_t(const uint32x4_t &v0, const uint32x4_t &v1) : x0(v0.x), y0(v0.y), z0(v0.z), w0(v0.w), x1(v1.x), y1(v1.y), z1(v1.z), w1(v1.w) { }
			#endif
			uint32x8_t(uint32_t x0, uint32_t y0, uint32_t z0, uint32_t w0, uint32_t x1, uint32_t y1, uint32_t z1, uint32_t w1) : vec0(_mm_setr_epi32((int32_t)x0, (int32_t)y0, (int32_t)z0, (int32_t)w0)), vec1(_mm_setr_epi32((int32_t)x1, (int32_t)y1, (int32_t)z1, (int32_t)w1)) { }
		#elif TS_NEON
			uint32x8_t(const uint32x8_t &v) : vec0(v.vec0), vec1(v.vec1) { }
			uint32x8_t(::uint32x4_t v0, ::uint32x4_t v1) : vec0(v0), vec1(v1) { }
			explicit uint32x8_t(uint32_t v) : vec0(vdupq_n_u32(v)), vec1(vdupq_n_u32(v)) { }
			explicit uint32x8_t(const uint16x8_t &v) : vec0(vmovl_u16(vget_low_u16(v.vec))), vec1(vmovl_u16(vget_high_u16(v.vec))) { }
			uint32x8_t(const uint32x4_t &v0, const uint32x4_t &v1) : vec0(v0.vec), vec1(v1.vec) { }
			uint32x8_t(uint32_t x0, uint32_t y0, uint32_t z0, uint32_t w0, uint32_t x1, uint32_t y1, uint32_t z1, uint32_t w1) : vec0(vsetq_u32(x0, y0, z0, w0)), vec1(vsetq_u32(x1, y1, z1, w1)) { }
		#else
			explicit uint32x8_t(uint32_t v) : x0(v), y0(v), z0(v), w0(v), x1(v), y1(v), z1(v), w1(v) { }
			explicit uint32x8_t(const uint16x8_t &v) : x0(v.x0), y0(v.y0), z0(v.z0), w0(v.w0), x1(v.x1), y1(v.y1), z1(v.z1), w1(v.w1) { }
			uint32x8_t(const uint32x4_t &v0, const uint32x4_t &v1) : x0(v0.x), y0(v0.y), z0(v0.z), w0(v0.w), x1(v1.x), y1(v1.y), z1(v1.z), w1(v1.w) { }
			uint32x8_t(uint32_t x0, uint32_t y0, uint32_t z0, uint32_t w0, uint32_t x1, uint32_t y1, uint32_t z1, uint32_t w1) : x0(x0), y0(y0), z0(z0), w0(w0), x1(x1), y1(y1), z1(z1), w1(w1) { }
		#endif
		
		/// cast vector data
		TS_INLINE int32x8_t asi32x8() const;
		TS_INLINE float32x8_t asf32x8() const;
		
		/// update vector data
		TS_INLINE void set(const uint32x8_t &v) {
			#if TS_AVX >= 1
				vec = v.vec;
			#elif TS_SSE >= 1
				vec0 = v.vec0;
				vec1 = v.vec1;
			#elif TS_NEON
				vec0 = v.vec0;
				vec1 = v.vec1;
			#else
				x0 = v.x0; y0 = v.y0; z0 = v.z0; w0 = v.w0;
				x1 = v.x1; y1 = v.y1; z1 = v.z1; w1 = v.w1;
			#endif
		}
		TS_INLINE void set(uint32_t X0, uint32_t Y0, uint32_t Z0, uint32_t W0, uint32_t X1, uint32_t Y1, uint32_t Z1, uint32_t W1) {
			#if TS_AVX >= 1
				vec = _mm256_setr_epi32((int32_t)X0, (int32_t)Y0, (int32_t)Z0, (int32_t)W0, (int32_t)X1, (int32_t)Y1, (int32_t)Z1, (int32_t)W1);
			#elif TS_SSE >= 1
				vec0 = _mm_setr_epi32((int32_t)X0, (int32_t)Y0, (int32_t)Z0, (int32_t)W0);
				vec1 = _mm_setr_epi32((int32_t)X1, (int32_t)Y1, (int32_t)Z1, (int32_t)W1);
			#elif TS_NEON
				vec0 = vsetq_u32(X0, Y0, Z0, W0);
				vec1 = vsetq_u32(X1, Y1, Z1, W1);
			#else
				x0 = X0; y0 = Y0; z0 = Z0; w0 = W0;
				x1 = X1; y1 = Y1; z1 = Z1; w1 = W1;
			#endif
		}
		TS_INLINE void set(const uint32_t *TS_RESTRICT v) {
			#if TS_AVX >= 1
				vec = _mm256_castps_si256(_mm256_load_ps((const float32_t*)v));
			#elif TS_SSE >= 1
				vec0 = _mm_castps_si128(_mm_load_ps((const float32_t*)v + 0));
				vec1 = _mm_castps_si128(_mm_load_ps((const float32_t*)v + 4));
			#elif TS_NEON
				vec0 = _vld1q_u32(v + 0);
				vec1 = _vld1q_u32(v + 4);
			#else
				x0 = v[0]; y0 = v[1]; z0 = v[2]; w0 = v[3];
				x1 = v[4]; y1 = v[5]; z1 = v[6]; w1 = v[7];
			#endif
		}
		TS_INLINE void get(uint32_t *TS_RESTRICT v) const {
			#if TS_AVX >= 1
				_mm256_stream_ps((float32_t*)v, _mm256_castsi256_ps(vec));
			#elif TS_SSE >= 1
				_mm_stream_ps((float32_t*)v + 0, _mm_castsi128_ps(vec0));
				_mm_stream_ps((float32_t*)v + 4, _mm_castsi128_ps(vec1));
			#elif TS_NEON
				_vst1q_u32(v + 0, vec0);
				_vst1q_u32(v + 4, vec1);
			#else
				v[0] = x0; v[1] = y0; v[2] = z0; v[3] = w0;
				v[4] = x1; v[5] = y1; v[6] = z1; v[7] = w1;
			#endif
		}
		template <uint32_t Index> TS_INLINE void set(uint32_t V) {
			#if TS_AVX >= 1
				__m128i temp = _mm_insert_epi32(_mm256_extractf128_si256(vec, Index >> 2), V, Index & 0x03);
				vec = _mm256_insertf128_si256(vec, temp, Index >> 2);
			#elif TS_SSE >= 4
				vec[Index >> 2] = _mm_insert_epi32(vec[Index >> 2], V, Index & 0x03);
			#elif TS_NEON
				vec[Index >> 2] = _vsetq_lane_u32<Index & 0x03>(V, vec[Index >> 2]);
			#else
				v[Index] = V;
			#endif
		}
		template <uint32_t Index> TS_INLINE uint32_t get() const {
			#if TS_AVX >= 1
				return _mm_extract_epi32(_mm256_extractf128_si256(vec, Index >> 2), Index & 0x03);
			#elif TS_SSE >= 4
				return _mm_extract_epi32(vec[Index >> 2], Index & 0x03);
			#elif TS_NEON
				return _vgetq_lane_u32<Index & 0x03>(vec[Index >> 2]);
			#else
				return v[Index];
			#endif
		}
		template <uint32_t Index> TS_INLINE uint32x8_t get8() const {
			#if TS_AVX >= 1
				__m128i temp = _mm256_extractf128_si256(vec, Index >> 2);
				temp = _mm_shuffle_epi32(temp, ((Index & 0x03) << 6) | ((Index & 0x03) << 4) | ((Index & 0x03) << 2) | (Index & 0x03));
				return uint32x8_t(temp, temp);
			#elif TS_SSE >= 4
				__m128i temp = _mm_shuffle_epi32(vec[Index >> 2], ((Index & 0x03) << 6) | ((Index & 0x03) << 4) | ((Index & 0x03) << 2) | (Index & 0x03));
				return uint32x8_t(temp, temp);
			#elif TS_NEON
				::uint32x4_t temp = vdupq_n_u32(_vgetq_lane_u32<Index & 0x03>(vec[Index >> 2]));
				return uint32x8_t(temp, temp);
			#else
				return uint32x8_t(v[Index]);
			#endif
		}
		
		/// vector to scalar operators
		TS_INLINE uint32x8_t &operator*=(uint32_t v) {
			#if TS_AVX >= 2
				vec = _mm256_mullo_epi32(vec, _mm256_set1_epi32(v));
			#elif TS_SSE >= 4
				__m128i temp = _mm_set1_epi32(v);
				vec0 = _mm_mullo_epi32(vec0, temp);
				vec1 = _mm_mullo_epi32(vec1, temp);
			#elif TS_NEON
				::uint32x4_t temp = vdupq_n_u32(v);
				vec0 = vmulq_u32(vec0, temp);
				vec1 = vmulq_u32(vec1, temp);
			#else
				x0 *= v; y0 *= v; z0 *= v; w0 *= v; x1 *= v; y1 *= v; z1 *= v; w1 *= v;
			#endif
			return *this;
		}
		TS_INLINE uint32x8_t &operator+=(uint32_t v) {
			#if TS_AVX >= 2
				vec = _mm256_add_epi32(vec, _mm256_set1_epi32(v));
			#elif TS_SSE >= 1
				__m128i temp = _mm_set1_epi32(v);
				vec0 = _mm_add_epi32(vec0, temp);
				vec1 = _mm_add_epi32(vec1, temp);
			#elif TS_NEON
				::uint32x4_t temp = vdupq_n_u32(v);
				vec0 = vaddq_u32(vec0, temp);
				vec1 = vaddq_u32(vec1, temp);
			#else
				x0 += v; y0 += v; z0 += v; w0 += v; x1 += v; y1 += v; z1 += v; w1 += v;
			#endif
			return *this;
		}
		TS_INLINE uint32x8_t &operator-=(uint32_t v) {
			#if TS_AVX >= 2
				vec = _mm256_sub_epi32(vec, _mm256_set1_epi32(v));
			#elif TS_SSE >= 1
				__m128i temp = _mm_set1_epi32(v);
				vec0 = _mm_sub_epi32(vec0, temp);
				vec1 = _mm_sub_epi32(vec1, temp);
			#elif TS_NEON
				::uint32x4_t temp = vdupq_n_u32(v);
				vec0 = vsubq_u32(vec0, temp);
				vec1 = vsubq_u32(vec1, temp);
			#else
				x0 -= v; y0 -= v; z0 -= v; w0 -= v; x1 -= v; y1 -= v; z1 -= v; w1 -= v;
			#endif
			return *this;
		}
		TS_INLINE uint32x8_t &operator&=(uint32_t v) {
			#if TS_AVX >= 2
				vec = _mm256_and_si256(vec, _mm256_set1_epi32(v));
			#elif TS_SSE >= 1
				__m128i temp = _mm_set1_epi32(v);
				vec0 = _mm_and_si128(vec0, temp);
				vec1 = _mm_and_si128(vec1, temp);
			#elif TS_NEON
				::uint32x4_t temp = vdupq_n_u32(v);
				vec0 = vandq_u32(vec0, temp);
				vec1 = vandq_u32(vec1, temp);
			#else
				x0 &= v; y0 &= v; z0 &= v; w0 &= v; x1 &= v; y1 &= v; z1 &= v; w1 &= v;
			#endif
			return *this;
		}
		TS_INLINE uint32x8_t &operator|=(uint32_t v) {
			#if TS_AVX >= 2
				vec = _mm256_or_si256(vec, _mm256_set1_epi32(v));
			#elif TS_SSE >= 1
				__m128i temp = _mm_set1_epi32(v);
				vec0 = _mm_or_si128(vec0, temp);
				vec1 = _mm_or_si128(vec1, temp);
			#elif TS_NEON
				::uint32x4_t temp = vdupq_n_u32(v);
				vec0 = vorrq_u32(vec0, temp);
				vec1 = vorrq_u32(vec1, temp);
			#else
				x0 |= v; y0 |= v; z0 |= v; w0 |= v; x1 |= v; y1 |= v; z1 |= v; w1 |= v;
			#endif
			return *this;
		}
		TS_INLINE uint32x8_t &operator^=(uint32_t v) {
			#if TS_AVX >= 2
				vec = _mm256_xor_si256(vec, _mm256_set1_epi32(v));
			#elif TS_SSE >= 1
				__m128i temp = _mm_set1_epi32(v);
				vec0 = _mm_xor_si128(vec0, temp);
				vec1 = _mm_xor_si128(vec1, temp);
			#elif TS_NEON
				::uint32x4_t temp = vdupq_n_u32(v);
				vec0 = veorq_u32(vec0, temp);
				vec1 = veorq_u32(vec1, temp);
			#else
				x0 ^= v; y0 ^= v; z0 ^= v; w0 ^= v; x1 ^= v; y1 ^= v; z1 ^= v; w1 ^= v;
			#endif
			return *this;
		}
		TS_INLINE uint32x8_t &operator<<=(uint32_t v) {
			#if TS_AVX >= 2
				vec = _mm256_slli_epi32(vec, v);
			#elif TS_SSE >= 1
				vec0 = _mm_slli_epi32(vec0, v);
				vec1 = _mm_slli_epi32(vec1, v);
			#elif TS_NEON
				::int32x4_t temp = vdupq_n_s32(v);
				vec0 = vshlq_u32(vec0, temp);
				vec1 = vshlq_u32(vec1, temp);
			#else
				x0 <<= v; y0 <<= v; z0 <<= v; w0 <<= v; x1 <<= v; y1 <<= v; z1 <<= v; w1 <<= v;
			#endif
			return *this;
		}
		TS_INLINE uint32x8_t &operator>>=(uint32_t v) {
			#if TS_AVX >= 2
				vec = _mm256_srli_epi32(vec, v);
			#elif TS_SSE >= 1
				vec0 = _mm_srli_epi32(vec0, v);
				vec1 = _mm_srli_epi32(vec1, v);
			#elif TS_NEON
				::int32x4_t temp = vdupq_n_s32(-(int32_t)v);
				vec0 = vshlq_u32(vec0, temp);
				vec1 = vshlq_u32(vec1, temp);
			#else
				x0 >>= v; y0 >>= v; z0 >>= v; w0 >>= v; x1 >>= v; y1 >>= v; z1 >>= v; w1 >>= v;
			#endif
			return *this;
		}
		
		/// vector to vector operators
		TS_INLINE uint32x8_t &operator*=(const uint32x8_t &v) {
			#if TS_AVX >= 2
				vec = _mm256_mullo_epi32(vec, v.vec);
			#elif TS_SSE >= 4
				vec0 = _mm_mullo_epi32(vec0, v.vec0);
				vec1 = _mm_mullo_epi32(vec1, v.vec1);
			#elif TS_NEON
				vec0 = vmulq_u32(vec0, v.vec0);
				vec1 = vmulq_u32(vec1, v.vec1);
			#else
				x0 *= v.x0; y0 *= v.y0; z0 *= v.z0; w0 *= v.w0; x1 *= v.x1; y1 *= v.y1; z1 *= v.z1; w1 *= v.w1;
			#endif
			return *this;
		}
		TS_INLINE uint32x8_t &operator+=(const uint32x8_t &v) {
			#if TS_AVX >= 2
				vec = _mm256_add_epi32(vec, v.vec);
			#elif TS_SSE >= 1
				vec0 = _mm_add_epi32(vec0, v.vec0);
				vec1 = _mm_add_epi32(vec1, v.vec1);
			#elif TS_NEON
				vec0 = vaddq_u32(vec0, v.vec0);
				vec1 = vaddq_u32(vec1, v.vec1);
			#else
				x0 += v.x0; y0 += v.y0; z0 += v.z0; w0 += v.w0; x1 += v.x1; y1 += v.y1; z1 += v.z1; w1 += v.w1;
			#endif
			return *this;
		}
		TS_INLINE uint32x8_t &operator-=(const uint32x8_t &v) {
			#if TS_AVX >= 2
				vec = _mm256_sub_epi32(vec, v.vec);
			#elif TS_SSE >= 1
				vec0 = _mm_sub_epi32(vec0, v.vec0);
				vec1 = _mm_sub_epi32(vec1, v.vec1);
			#elif TS_NEON
				vec0 = vsubq_u32(vec0, v.vec0);
				vec1 = vsubq_u32(vec1, v.vec1);
			#else
				x0 -= v.x0; y0 -= v.y0; z0 -= v.z0; w0 -= v.w0; x1 -= v.x1; y1 -= v.y1; z1 -= v.z1; w1 -= v.w1;
			#endif
			return *this;
		}
		TS_INLINE uint32x8_t &operator&=(const uint32x8_t &v) {
			#if TS_AVX >= 2
				vec = _mm256_and_si256(vec, v.vec);
			#elif TS_SSE >= 1
				vec0 = _mm_and_si128(vec0, v.vec0);
				vec1 = _mm_and_si128(vec1, v.vec1);
			#elif TS_NEON
				vec0 = vandq_u32(vec0, v.vec0);
				vec1 = vandq_u32(vec1, v.vec1);
			#else
				x0 &= v.x0; y0 &= v.y0; z0 &= v.z0; w0 &= v.w0; x1 &= v.x1; y1 &= v.y1; z1 &= v.z1; w1 &= v.w1;
			#endif
			return *this;
		}
		TS_INLINE uint32x8_t &operator|=(const uint32x8_t &v) {
			#if TS_AVX >= 2
				vec = _mm256_or_si256(vec, v.vec);
			#elif TS_SSE >= 1
				vec0 = _mm_or_si128(vec0, v.vec0);
				vec1 = _mm_or_si128(vec1, v.vec1);
			#elif TS_NEON
				vec0 = vorrq_u32(vec0, v.vec0);
				vec1 = vorrq_u32(vec1, v.vec1);
			#else
				x0 |= v.x0; y0 |= v.y0; z0 |= v.z0; w0 |= v.w0; x1 |= v.x1; y1 |= v.y1; z1 |= v.z1; w1 |= v.w1;
			#endif
			return *this;
		}
		TS_INLINE uint32x8_t &operator^=(const uint32x8_t &v) {
			#if TS_AVX >= 2
				vec = _mm256_xor_si256(vec, v.vec);
			#elif TS_SSE >= 1
				vec0 = _mm_xor_si128(vec0, v.vec0);
				vec1 = _mm_xor_si128(vec1, v.vec1);
			#elif TS_NEON
				vec0 = veorq_u32(vec0, v.vec0);
				vec1 = veorq_u32(vec1, v.vec1);
			#else
				x0 ^= v.x0; y0 ^= v.y0; z0 ^= v.z0; w0 ^= v.w0; x1 ^= v.x1; y1 ^= v.y1; z1 ^= v.z1; w1 ^= v.w1;
			#endif
			return *this;
		}
		
		/// swizzle vector
		TS_INLINE uint32x8_t xyzw10() const {
			#if TS_AVX >= 1
				return uint32x8_t(_mm256_permute2f128_si256(vec, vec, 0x03));
			#elif TS_SSE >= 2
				return uint32x8_t(vec1, vec0);
			#elif TS_NEON
				return uint32x8_t(vec1, vec0);
			#else
				return uint32x8_t(x1, y1, z1, w1, x0, y0, z0, w0);
			#endif
		}
		TS_INLINE uint32x8_t zwxy01() const {
			#if TS_AVX >= 1
				return uint32x8_t(_mm256_castps_si256(_mm256_permute_ps(_mm256_castsi256_ps(vec), 0x4e)));
			#elif TS_SSE >= 2
				return uint32x8_t(_mm_swizzle_epi32(vec0, Z, W, X, Y), _mm_swizzle_epi32(vec1, Z, W, X, Y));
			#elif TS_NEON
				return uint32x8_t(vcombine_u32(vget_high_u32(vec0), vget_low_u32(vec0)), vcombine_u32(vget_high_u32(vec1), vget_low_u32(vec1)));
			#else
				return uint32x8_t(z0, w0, x0, y0, z1, w1, x1, y1);
			#endif
		}
		TS_INLINE uint32x8_t yxwz01() const {
			#if TS_AVX >= 1
				return uint32x8_t(_mm256_castps_si256(_mm256_permute_ps(_mm256_castsi256_ps(vec), 0xb1)));
			#elif TS_SSE >= 2
				return uint32x8_t(_mm_swizzle_epi32(vec0, Y, X, W, Z), _mm_swizzle_epi32(vec1, Y, X, W, Z));
			#elif TS_NEON
				return uint32x8_t(vrev64q_u32(vec0), vrev64q_u32(vec1));
			#else
				return uint32x8_t(y0, x0, w0, z0, y1, x1, w1, z1);
			#endif
		}
		TS_INLINE uint32x4_t xyzw0() const {
			#if TS_AVX >= 1
				return uint32x4_t(_mm256_extractf128_si256(vec, 0));
			#elif TS_SSE >= 2
				return uint32x4_t(vec0);
			#elif TS_NEON
				return uint32x4_t(vec0);
			#else
				return uint32x4_t(x0, y0, z0, w0);
			#endif
		}
		TS_INLINE uint32x4_t xyzw1() const {
			#if TS_AVX >= 1
				return uint32x4_t(_mm256_extractf128_si256(vec, 1));
			#elif TS_SSE >= 2
				return uint32x4_t(vec1);
			#elif TS_NEON
				return uint32x4_t(vec1);
			#else
				return uint32x4_t(x1, y1, z1, w1);
			#endif
		}
		
		/// sum vector components
		TS_INLINE uint32_t sum() const {
			#if TS_AVX >= 1
				__m128i temp = _mm_add_epi32(_mm256_extractf128_si256(vec, 0), _mm256_extractf128_si256(vec, 1));
				temp = _mm_hadd_epi32(temp, temp);
				temp = _mm_hadd_epi32(temp, temp);
				return (uint32_t)_mm_extract_epi32(temp, 0);
			#elif TS_SSE >= 4
				__m128i temp = _mm_add_epi32(vec0, vec1);
				temp = _mm_hadd_epi32(temp, temp);
				temp = _mm_hadd_epi32(temp, temp);
				return (uint32_t)_mm_extract_epi32(temp, 0);
			#elif TS_SSE >= 2
				__m128i temp = _mm_add_epi32(vec0, vec1);
				temp = _mm_add_epi32(temp, _mm_swizzle_epi32(temp, Z, W, X, Y));
				temp = _mm_add_epi32(temp, _mm_swizzle_epi32(temp, Y, X, W, Z));
				return f32u32(_mm_cvtss_f32(_mm_castsi128_ps(temp))).u;
			#elif TS_NEON
				::uint32x2_t temp = vadd_u32(vget_high_u32(vec0), vget_low_u32(vec0));
				temp = vadd_u32(temp, vadd_u32(vget_high_u32(vec1), vget_low_u32(vec1)));
				temp = vadd_u32(temp, vrev64_u32(temp));
				return _vget_lane_u32<0>(temp);
			#else
				return x0 + y0 + z0 + w0 + x1 + y1 + z1 + w1;
			#endif
		}
		
		enum {
			Size = 8,
		};
		
		union {
			struct {
				uint32_t x0, y0, z0, w0;
				uint32_t x1, y1, z1, w1;
			};
			uint32_t v[Size];
			#if TS_AVX >= 1
				struct {
					__m128i vec0;
					__m128i vec1;
				};
				__m256i vec;
			#elif TS_SSE >= 1
				struct {
					__m128i vec0;
					__m128i vec1;
				};
				__m128i vec[2];
			#elif TS_NEON
				struct {
					::uint32x4_t vec0;
					::uint32x4_t vec1;
				};
				::uint32x4_t vec[2];
			#endif
		};
	};
	
	/// vector to scalar operators
	TS_INLINE uint32x8_t operator*(const uint32x8_t &v0, uint32_t v1) {
		#if TS_AVX >= 2
			return uint32x8_t(_mm256_mullo_epi32(v0.vec, _mm256_set1_epi32(v1)));
		#elif TS_SSE >= 4
			__m128i temp = _mm_set1_epi32(v1);
			return uint32x8_t(_mm_mullo_epi32(v0.vec0, temp), _mm_mullo_epi32(v0.vec1, temp));
		#elif TS_NEON
			::uint32x4_t temp = vdupq_n_u32(v1);
			return uint32x8_t(vmulq_u32(v0.vec0, temp), vmulq_u32(v0.vec1, temp));
		#else
			return uint32x8_t(v0.x0 * v1, v0.y0 * v1, v0.z0 * v1, v0.w0 * v1, v0.x1 * v1, v0.y1 * v1, v0.z1 * v1, v0.w1 * v1);
		#endif
	}
	TS_INLINE uint32x8_t operator+(const uint32x8_t &v0, uint32_t v1) {
		#if TS_AVX >= 2
			return uint32x8_t(_mm256_add_epi32(v0.vec, _mm256_set1_epi32(v1)));
		#elif TS_SSE >= 1
			__m128i temp = _mm_set1_epi32(v1);
			return uint32x8_t(_mm_add_epi32(v0.vec0, temp), _mm_add_epi32(v0.vec1, temp));
		#elif TS_NEON
			::uint32x4_t temp = vdupq_n_u32(v1);
			return uint32x8_t(vaddq_u32(v0.vec0, temp), vaddq_u32(v0.vec1, temp));
		#else
			return uint32x8_t(v0.x0 + v1, v0.y0 + v1, v0.z0 + v1, v0.w0 + v1, v0.x1 + v1, v0.y1 + v1, v0.z1 + v1, v0.w1 + v1);
		#endif
	}
	TS_INLINE uint32x8_t operator-(const uint32x8_t &v0, uint32_t v1) {
		#if TS_AVX >= 2
			return uint32x8_t(_mm256_sub_epi32(v0.vec, _mm256_set1_epi32(v1)));
		#elif TS_SSE >= 1
			__m128i temp = _mm_set1_epi32(v1);
			return uint32x8_t(_mm_sub_epi32(v0.vec0, temp), _mm_sub_epi32(v0.vec1, temp));
		#elif TS_NEON
			::uint32x4_t temp = vdupq_n_u32(v1);
			return uint32x8_t(vsubq_u32(v0.vec0, temp), vsubq_u32(v0.vec1, temp));
		#else
			return uint32x8_t(v0.x0 - v1, v0.y0 - v1, v0.z0 - v1, v0.w0 - v1, v0.x1 - v1, v0.y1 - v1, v0.z1 - v1, v0.w1 - v1);
		#endif
	}
	TS_INLINE uint32x8_t operator&(const uint32x8_t &v0, uint32_t v1) {
		#if TS_AVX >= 2
			return uint32x8_t(_mm256_and_si256(v0.vec, _mm256_set1_epi32(v1)));
		#elif TS_SSE >= 1
			__m128i temp = _mm_set1_epi32(v1);
			return uint32x8_t(_mm_and_si128(v0.vec0, temp), _mm_and_si128(v0.vec1, temp));
		#elif TS_NEON
			::uint32x4_t temp = vdupq_n_u32(v1);
			return uint32x8_t(vandq_u32(v0.vec0, temp), vandq_u32(v0.vec1, temp));
		#else
			return uint32x8_t(v0.x0 & v1, v0.y0 & v1, v0.z0 & v1, v0.w0 & v1, v0.x1 & v1, v0.y1 & v1, v0.z1 & v1, v0.w1 & v1);
		#endif
	}
	TS_INLINE uint32x8_t operator|(const uint32x8_t &v0, uint32_t v1) {
		#if TS_AVX >= 2
			return uint32x8_t(_mm256_or_si256(v0.vec, _mm256_set1_epi32(v1)));
		#elif TS_SSE >= 1
			__m128i temp = _mm_set1_epi32(v1);
			return uint32x8_t(_mm_or_si128(v0.vec0, temp), _mm_or_si128(v0.vec1, temp));
		#elif TS_NEON
			::uint32x4_t temp = vdupq_n_u32(v1);
			return uint32x8_t(vorrq_u32(v0.vec0, temp), vorrq_u32(v0.vec1, temp));
		#else
			return uint32x8_t(v0.x0 | v1, v0.y0 | v1, v0.z0 | v1, v0.w0 | v1, v0.x1 | v1, v0.y1 | v1, v0.z1 | v1, v0.w1 | v1);
		#endif
	}
	TS_INLINE uint32x8_t operator^(const uint32x8_t &v0, uint32_t v1) {
		#if TS_AVX >= 2
			return uint32x8_t(_mm256_xor_si256(v0.vec, _mm256_set1_epi32(v1)));
		#elif TS_SSE >= 1
			__m128i temp = _mm_set1_epi32(v1);
			return uint32x8_t(_mm_xor_si128(v0.vec0, temp), _mm_xor_si128(v0.vec1, temp));
		#elif TS_NEON
			::uint32x4_t temp = vdupq_n_u32(v1);
			return uint32x8_t(veorq_u32(v0.vec0, temp), veorq_u32(v0.vec1, temp));
		#else
			return uint32x8_t(v0.x0 ^ v1, v0.y0 ^ v1, v0.z0 ^ v1, v0.w0 ^ v1, v0.x1 ^ v1, v0.y1 ^ v1, v0.z1 ^ v1, v0.w1 ^ v1);
		#endif
	}
	TS_INLINE uint32x8_t operator<<(const uint32x8_t &v0, uint32_t v1) {
		#if TS_AVX >= 2
			return uint32x8_t(_mm256_slli_epi32(v0.vec, v1));
		#elif TS_SSE >= 1
			return uint32x8_t(_mm_slli_epi32(v0.vec0, v1), _mm_slli_epi32(v0.vec1, v1));
		#elif TS_NEON
			::int32x4_t temp = vdupq_n_s32(v1);
			return uint32x8_t(vshlq_u32(v0.vec0, temp), vshlq_u32(v0.vec1, temp));
		#else
			return uint32x8_t(v0.x0 << v1, v0.y0 << v1, v0.z0 << v1, v0.w0 << v1, v0.x1 << v1, v0.y1 << v1, v0.z1 << v1, v0.w1 << v1);
		#endif
	}
	TS_INLINE uint32x8_t operator>>(const uint32x8_t &v0, uint32_t v1) {
		#if TS_AVX >= 2
			return uint32x8_t(_mm256_srli_epi32(v0.vec, v1));
		#elif TS_SSE >= 1
			return uint32x8_t(_mm_srli_epi32(v0.vec0, v1), _mm_srli_epi32(v0.vec1, v1));
		#elif TS_NEON
			::int32x4_t temp = vdupq_n_s32(-(int32_t)v1);
			return uint32x8_t(vshlq_u32(v0.vec0, temp), vshlq_u32(v0.vec1, temp));
		#else
			return uint32x8_t(v0.x0 >> v1, v0.y0 >> v1, v0.z0 >> v1, v0.w0 >> v1, v0.x1 >> v1, v0.y1 >> v1, v0.z1 >> v1, v0.w1 >> v1);
		#endif
	}
	
	/// vector to vector operators
	TS_INLINE uint32x8_t operator*(const uint32x8_t &v0, const uint32x8_t &v1) {
		#if TS_AVX >= 2
			return uint32x8_t(_mm256_mullo_epi32(v0.vec, v1.vec));
		#elif TS_SSE >= 4
			return uint32x8_t(_mm_mullo_epi32(v0.vec0, v1.vec0), _mm_mullo_epi32(v0.vec1, v1.vec1));
		#elif TS_NEON
			return uint32x8_t(vmulq_u32(v0.vec0, v1.vec0), vmulq_u32(v0.vec1, v1.vec1));
		#else
			return uint32x8_t(v0.x0 * v1.x0, v0.y0 * v1.y0, v0.z0 * v1.z0, v0.w0 * v1.w0, v0.x1 * v1.x1, v0.y1 * v1.y1, v0.z1 * v1.z1, v0.w1 * v1.w1);
		#endif
	}
	TS_INLINE uint32x8_t operator+(const uint32x8_t &v0, const uint32x8_t &v1) {
		#if TS_AVX >= 2
			return uint32x8_t(_mm256_add_epi32(v0.vec, v1.vec));
		#elif TS_SSE >= 1
			return uint32x8_t(_mm_add_epi32(v0.vec0, v1.vec0), _mm_add_epi32(v0.vec1, v1.vec1));
		#elif TS_NEON
			return uint32x8_t(vaddq_u32(v0.vec0, v1.vec0), vaddq_u32(v0.vec1, v1.vec1));
		#else
			return uint32x8_t(v0.x0 + v1.x0, v0.y0 + v1.y0, v0.z0 + v1.z0, v0.w0 + v1.w0, v0.x1 + v1.x1, v0.y1 + v1.y1, v0.z1 + v1.z1, v0.w1 + v1.w1);
		#endif
	}
	TS_INLINE uint32x8_t operator-(const uint32x8_t &v0, const uint32x8_t &v1) {
		#if TS_AVX >= 2
			return uint32x8_t(_mm256_sub_epi32(v0.vec, v1.vec));
		#elif TS_SSE >= 1
			return uint32x8_t(_mm_sub_epi32(v0.vec0, v1.vec0), _mm_sub_epi32(v0.vec1, v1.vec1));
		#elif TS_NEON
			return uint32x8_t(vsubq_u32(v0.vec0, v1.vec0), vsubq_u32(v0.vec1, v1.vec1));
		#else
			return uint32x8_t(v0.x0 - v1.x0, v0.y0 - v1.y0, v0.z0 - v1.z0, v0.w0 - v1.w0, v0.x1 - v1.x1, v0.y1 - v1.y1, v0.z1 - v1.z1, v0.w1 - v1.w1);
		#endif
	}
	TS_INLINE uint32x8_t operator&(const uint32x8_t &v0, const uint32x8_t &v1) {
		#if TS_AVX >= 2
			return uint32x8_t(_mm256_and_si256(v0.vec, v1.vec));
		#elif TS_SSE >= 1
			return uint32x8_t(_mm_and_si128(v0.vec0, v1.vec0), _mm_and_si128(v0.vec1, v1.vec1));
		#elif TS_NEON
			return uint32x8_t(vandq_u32(v0.vec0, v1.vec0), vandq_u32(v0.vec1, v1.vec1));
		#else
			return uint32x8_t(v0.x0 & v1.x0, v0.y0 & v1.y0, v0.z0 & v1.z0, v0.w0 & v1.w0, v0.x1 & v1.x1, v0.y1 & v1.y1, v0.z1 & v1.z1, v0.w1 & v1.w1);
		#endif
	}
	TS_INLINE uint32x8_t operator|(const uint32x8_t &v0, const uint32x8_t &v1) {
		#if TS_AVX >= 2
			return uint32x8_t(_mm256_or_si256(v0.vec, v1.vec));
		#elif TS_SSE >= 1
			return uint32x8_t(_mm_or_si128(v0.vec0, v1.vec0), _mm_or_si128(v0.vec1, v1.vec1));
		#elif TS_NEON
			return uint32x8_t(vorrq_u32(v0.vec0, v1.vec0), vorrq_u32(v0.vec1, v1.vec1));
		#else
			return uint32x8_t(v0.x0 | v1.x0, v0.y0 | v1.y0, v0.z0 | v1.z0, v0.w0 | v1.w0, v0.x1 | v1.x1, v0.y1 | v1.y1, v0.z1 | v1.z1, v0.w1 | v1.w1);
		#endif
	}
	TS_INLINE uint32x8_t operator^(const uint32x8_t &v0, const uint32x8_t &v1) {
		#if TS_AVX >= 2
			return uint32x8_t(_mm256_xor_si256(v0.vec, v1.vec));
		#elif TS_SSE >= 1
			return uint32x8_t(_mm_xor_si128(v0.vec0, v1.vec0), _mm_xor_si128(v0.vec1, v1.vec1));
		#elif TS_NEON
			return uint32x8_t(veorq_u32(v0.vec0, v1.vec0), veorq_u32(v0.vec1, v1.vec1));
		#else
			return uint32x8_t(v0.x0 ^ v1.x0, v0.y0 ^ v1.y0, v0.z0 ^ v1.z0, v0.w0 ^ v1.w0, v0.x1 ^ v1.x1, v0.y1 ^ v1.y1, v0.z1 ^ v1.z1, v0.w1 ^ v1.w1);
		#endif
	}
	
	/// min/max functions
	TS_INLINE uint32x8_t min(const uint32x8_t &v0, const uint32x8_t &v1) {
		#if TS_AVX >= 2
			return uint32x8_t(_mm256_min_epi32(v0.vec, v1.vec));
		#elif TS_SSE >= 4
			return uint32x8_t(_mm_min_epi32(v0.vec0, v1.vec0), _mm_min_epi32(v0.vec1, v1.vec1));
		#elif TS_NEON
			return uint32x8_t(vminq_u32(v0.vec0, v1.vec0), vminq_u32(v0.vec1, v1.vec1));
		#else
			return uint32x8_t(min(v0.x0, v1.x0), min(v0.y0, v1.y0), min(v0.z0, v1.z0), min(v0.w0, v1.w0), min(v0.x1, v1.x1), min(v0.y1, v1.y1), min(v0.z1, v1.z1), min(v0.w1, v1.w1));
		#endif
	}
	TS_INLINE uint32x8_t max(const uint32x8_t &v0, const uint32x8_t &v1) {
		#if TS_AVX >= 2
			return uint32x8_t(_mm256_max_epi32(v0.vec, v1.vec));
		#elif TS_SSE >= 4
			return uint32x8_t(_mm_max_epi32(v0.vec0, v1.vec0), _mm_max_epi32(v0.vec1, v1.vec1));
		#elif TS_NEON
			return uint32x8_t(vmaxq_u32(v0.vec0, v1.vec0), vmaxq_u32(v0.vec1, v1.vec1));
		#else
			return uint32x8_t(max(v0.x0, v1.x0), max(v0.y0, v1.y0), max(v0.z0, v1.z0), max(v0.w0, v1.w0), max(v0.x1, v1.x1), max(v0.y1, v1.y1), max(v0.z1, v1.z1), max(v0.w1, v1.w1));
		#endif
	}
	
	/// range functions
	TS_INLINE uint32x8_t clamp(const uint32x8_t &v, uint32_t v0, uint32_t v1) {
		return min(max(v, uint32x8_t(v0)), uint32x8_t(v1));
	}
	TS_INLINE uint32x8_t clamp(const uint32x8_t &v, const uint32x8_t &v0, const uint32x8_t &v1) {
		return min(max(v, v0), v1);
	}
	
	/// select functions
	TS_INLINE uint32x8_t select(const uint32x8_t &v0, const uint32x8_t &v1, const int32x8_t &s) {
		#if TS_AVX >= 1
			return uint32x8_t(_mm256_castps_si256(_mm256_blendv_ps(_mm256_castsi256_ps(v0.vec), _mm256_castsi256_ps(v1.vec), _mm256_castsi256_ps(s.vec))));
		#elif TS_SSE >= 2
			return uint32x8_t(_mm_xor_si128(v0.vec0, _mm_and_si128(_mm_xor_si128(v0.vec0, v1.vec0), _mm_srai_epi32(s.vec0, 31))), _mm_xor_si128(v0.vec1, _mm_and_si128(_mm_xor_si128(v0.vec1, v1.vec1), _mm_srai_epi32(s.vec1, 31))));
		#elif TS_NEON
			return uint32x8_t(vbslq_u32(vcgeq_s32(s.vec0, vdupq_n_s32(0)), v0.vec0, v1.vec0), vbslq_u32(vcgeq_s32(s.vec1, vdupq_n_s32(0)), v0.vec1, v1.vec1));
		#else
			return uint32x8_t(select(v0.x0, v1.x0, s.x0), select(v0.y0, v1.y0, s.y0), select(v0.z0, v1.z0, s.z0), select(v0.w0, v1.w0, s.w0), select(v0.x1, v1.x1, s.x1), select(v0.y1, v1.y1, s.y1), select(v0.z1, v1.z1, s.z1), select(v0.w1, v1.w1, s.w1));
		#endif
	}
	TS_INLINE uint32x8_t select(const uint32x8_t &v0, const uint32x8_t &v1, int32_t s) {
		return select(v0, v1, int32x8_t(s));
	}
	
	/*****************************************************************************\
	 *
	 * float16x4_t
	 *
	\*****************************************************************************/
	
	/**
	 * Vector of four float16_t components
	 */
	struct TS_ALIGNAS8 float16x4_t {
		
		float16x4_t() { }
		explicit float16x4_t(const float32x4_t &v);
		explicit float16x4_t(const float16_t *v) { set(v); }
		float16x4_t(const float16_t *v, float16_t w) { set(v, w); }
		explicit float16x4_t(float16_t v) : f16 { v, v, v, v } { }
		float16x4_t(float16_t x, float16_t y, float16_t z, float16_t w) : f16 { x, y, z, w } { }
		#if TS_NEON
			explicit float16x4_t(uint64_t v) : vec(vcreate_u16(v)) { }
			float16x4_t(const float16x4_t &v) : vec(v.vec) { }
			explicit float16x4_t(::uint16x4_t v) : vec(v) { }
		#else
			explicit float16x4_t(uint64_t v) : vec(v) { }
			float16x4_t(const float16x4_t &v) : vec(v.vec) { }
		#endif
		
		/// update vector data
		TS_INLINE void set(float16x4_t &v) {
			#if TS_NEON
				vec = v.vec;
			#else
				vec = v.vec;
			#endif
		}
		TS_INLINE void set(float16_t X, float16_t Y, float16_t Z, float16_t W) {
			#if TS_NEON
				vec = vset_u16(X.bits, Y.bits, Z.bits, W.bits);
			#else
				f16.x = X; f16.y = Y; f16.z = Z; f16.w = W;
			#endif
		}
		TS_INLINE void set(const float16_t *TS_RESTRICT v, float16_t W) {
			#if TS_NEON
				vec = vset_u16(v[0].bits, v[1].bits, v[2].bits, W.bits);
			#else
				f16.x = v[0]; f16.y = v[1]; f16.z = v[2]; f16.w = W;
			#endif
		}
		TS_INLINE void set(const float16_t *TS_RESTRICT v) {
			#if TS_NEON
				vec = vld1_u16((const uint16_t*)v);
			#else
				f16.x = v[0]; f16.y = v[1]; f16.z = v[2]; f16.w = v[3];
			#endif
		}
		TS_INLINE void get(float16_t *TS_RESTRICT v) const {
			#if TS_NEON
				_vst1_u16((uint16_t*)v, vec);
			#else
				v[0] = f16.x; v[1] = f16.y; v[2] = f16.z; v[3] = f16.w;
			#endif
		}
		template <uint32_t Index> TS_INLINE void set(float16_t V) {
			#if TS_NEON
				vec = _vset_lane_u16<Index>(V.bits, vec);
			#else
				v[Index] = V;
			#endif
		}
		template <uint32_t Index> TS_INLINE float16_t get() const {
			#if TS_NEON
				return float16_t(_vget_lane_u16<Index>(vec));
			#else
				return v[Index];
			#endif
		}
		
		/// assignment operator
		TS_INLINE float16x4_t &operator=(const float16x4_t &v) {
			vec = v.vec;
			return *this;
		}
		
		enum {
			Size = 4,
		};
		
		union {
			struct {
				float16_t x, y, z, w;
			} f16;
			float16_t v[Size];
			#if TS_NEON
				::uint16x4_t vec;
			#else
				uint64_t vec;
			#endif
		};
	};
	
	/*****************************************************************************\
	 *
	 * float16x8_t
	 *
	\*****************************************************************************/
	
	/**
	 * Vector of eight float16_t components
	 */
	struct TS_ALIGNAS16 float16x8_t {
		
		float16x8_t() { }
		explicit float16x8_t(const float32x8_t &v);
		explicit float16x8_t(const float16_t *v) { set(v); }
		explicit float16x8_t(const uint64_t *v) : vec0(v[0]), vec1(v[1]) { }
		float16x8_t(uint64_t v0, uint64_t v1) : vec0(v0), vec1(v1) { }
		#if TS_SSE >= 2
			float16x8_t(const float16x8_t &v) : vec(v.vec) { }
			explicit float16x8_t(__m128i v) : vec(v) { }
			explicit float16x8_t(float16_t v) : vec(_mm_set1_epi16((int32_t)v.bits)) { }
			float16x8_t(const float16x4_t &v0, const float16x4_t &v1) : vec(_mm_set_epi64x(v1.vec, v0.vec)) { }
			float16x8_t(float16_t x0, float16_t y0, float16_t z0, float16_t w0, float16_t x1, float16_t y1, float16_t z1, float16_t w1) : vec(_mm_setr_epi16((int16_t)x0.bits, (int16_t)y0.bits, (int16_t)z0.bits, (int16_t)w0.bits, (int16_t)x1.bits, (int16_t)y1.bits, (int16_t)z1.bits, (int16_t)w1.bits)) { }
		#elif TS_NEON
			float16x8_t(const float16x8_t &v) : vec(v.vec) { }
			explicit float16x8_t(::uint16x8_t v) : vec(v) { }
			explicit float16x8_t(float16_t v) : vec(vdupq_n_u16(v.bits)) { }
			float16x8_t(const float16x4_t &v0, const float16x4_t &v1) : vec(vcombine_u16(v0.vec, v1.vec)) { }
			float16x8_t(float16_t x0, float16_t y0, float16_t z0, float16_t w0, float16_t x1, float16_t y1, float16_t z1, float16_t w1) : vec(vsetq_u16(x0.bits, y0.bits, z0.bits, w0.bits, x1.bits, y1.bits, z1.bits, w1.bits)) { }
		#else
			explicit float16x8_t(float16_t v) : f16 { v, v, v, v, v, v, v, v } { }
			float16x8_t(const float16x4_t &v0, const float16x4_t &v1) : f16 { v0.f16.x, v0.f16.y, v0.f16.z, v0.f16.w, v1.f16.x, v1.f16.y, v1.f16.z, v1.f16.w } { }
			float16x8_t(float16_t x0, float16_t y0, float16_t z0, float16_t w0, float16_t x1, float16_t y1, float16_t z1, float16_t w1) : f16 { x0, y0, z0, w0, x1, y1, z1, w1 } { }
		#endif
		
		/// cast vector data
		TS_INLINE int16x8_t asi16x8() const {
			#if TS_SSE >= 2
				return int16x8_t(vec);
			#elif TS_NEON
				return int16x8_t(vreinterpretq_s16_u16(vec));
			#else
				return int16x8_t((int16_t*)v);
			#endif
		}
		TS_INLINE uint16x8_t asu16x8() const {
			#if TS_SSE >= 2
				return uint16x8_t(vec);
			#elif TS_NEON
				return uint16x8_t(vec);
			#else
				return uint16x8_t((uint16_t*)v);
			#endif
		}
		TS_INLINE int32x4_t asi32x4() const {
			#if TS_SSE >= 2
				return int32x4_t(vec);
			#elif TS_NEON
				return int32x4_t(vreinterpretq_s32_u16(vec));
			#else
				return int32x4_t((int32_t*)v);
			#endif
		}
		TS_INLINE uint32x4_t asu32x4() const {
			#if TS_SSE >= 2
				return uint32x4_t(vec);
			#elif TS_NEON
				return uint32x4_t(vreinterpretq_u32_u16(vec));
			#else
				return uint32x4_t((uint32_t*)v);
			#endif
		}
		TS_INLINE float32x4_t asf32x4() const;
		
		/// update vector data
		TS_INLINE void set(const float16x8_t &v) {
			#if TS_SSE >= 2
				vec = v.vec;
			#elif TS_NEON
				vec = v.vec;
			#else
				vec0 = v.vec0;
				vec1 = v.vec1;
			#endif
		}
		TS_INLINE void set(float16_t X0, float16_t Y0, float16_t Z0, float16_t W0, float16_t X1, float16_t Y1, float16_t Z1, float16_t W1) {
			#if TS_SSE >= 2
				vec = _mm_setr_epi16((int16_t)X0.bits, (int16_t)Y0.bits, (int16_t)Z0.bits, (int16_t)W0.bits, (int16_t)X1.bits, (int16_t)Y1.bits, (int16_t)Z1.bits, (int16_t)W1.bits);
			#elif TS_NEON
				vec = vsetq_u16(X0.bits, Y0.bits, Z0.bits, W0.bits, X1.bits, Y1.bits, Z1.bits, W1.bits);
			#else
				f16.x0 = X0; f16.y0 = Y0; f16.z0 = Z0; f16.w0 = W0;
				f16.x1 = X1; f16.y1 = Y1; f16.z1 = Z1; f16.w1 = W1;
			#endif
		}
		TS_INLINE void set(const float16_t *TS_RESTRICT v) {
			#if TS_SSE >= 2
				vec = _mm_castps_si128(_mm_load_ps((const float32_t*)v));
			#elif TS_NEON
				vec = _vld1q_u16((const uint16_t*)v);
			#else
				f16.x0 = v[0]; f16.y0 = v[1]; f16.z0 = v[2]; f16.w0 = v[3];
				f16.x1 = v[4]; f16.y1 = v[5]; f16.z1 = v[6]; f16.w1 = v[7];
			#endif
		}
		TS_INLINE void get(float16_t *TS_RESTRICT v) const {
			#if TS_SSE >= 2
				_mm_stream_ps((float32_t*)v, _mm_castsi128_ps(vec));
			#elif TS_NEON
				_vst1q_u16((uint16_t*)v, vec);
			#else
				v[0] = f16.x0; v[1] = f16.y0; v[2] = f16.z0; v[3] = f16.w0;
				v[4] = f16.x1; v[5] = f16.y1; v[6] = f16.z1; v[7] = f16.w1;
			#endif
		}
		TS_INLINE void set(const uint64_t *TS_RESTRICT v) {
			vec0 = v[0]; vec1 = v[1];
		}
		TS_INLINE void get(uint64_t *TS_RESTRICT v) const {
			v[0] = vec0; v[1] = vec1;
		}
		template <uint32_t Index> TS_INLINE void set(float16_t V) {
			#if TS_SSE >= 2
				vec = _mm_insert_epi16(vec, (int16_t)V.bits, Index);
			#elif TS_NEON
				vec = _vsetq_lane_u16<Index>(V.bits, vec);
			#else
				v[Index] = V;
			#endif
		}
		template <uint32_t Index> TS_INLINE float16_t get() const {
			#if TS_SSE >= 2
				return float16_t((uint16_t)_mm_extract_epi16(vec, Index));
			#elif TS_NEON
				return float16_t(_vgetq_lane_u16<Index>(vec));
			#else
				return v[Index];
			#endif
		}
		
		/// assignment operator
		TS_INLINE float16x8_t &operator=(const float16x8_t &v) {
			#if TS_SSE >= 2
				vec = v.vec;
			#elif TS_NEON
				vec = v.vec;
			#else
				vec0 = v.vec0;
				vec1 = v.vec1;
			#endif
			return *this;
		}
		
		enum {
			Size = 8,
		};
		
		union {
			struct {
				float16_t x0, y0, z0, w0;
				float16_t x1, y1, z1, w1;
			} f16;
			struct {
				uint64_t vec0;
				uint64_t vec1;
			};
			float16_t v[Size];
			#if TS_SSE >= 2
				__m128i vec;
			#elif TS_NEON
				::uint16x8_t vec;
			#else
				uint64_t vec[2];
			#endif
		};
	};
	
	/*****************************************************************************\
	 *
	 * float32x4_t
	 *
	\*****************************************************************************/
	
	/**
	 * Vector of four float32_t components
	 */
	struct TS_ALIGNAS16 float32x4_t {
		
		float32x4_t() { }
		explicit float32x4_t(const float64x4_t &v);
		explicit float32x4_t(const float32_t *v) { set(v); }
		float32x4_t(const float32_t *v, float32_t w) { set(v, w); }
		#if TS_SSE >= 1
			float32x4_t(const float32x4_t &v) : vec(v.vec) { }
			explicit float32x4_t(__m128 v) : vec(v) { }
			explicit float32x4_t(float32_t v) : vec(_mm_set1_ps(v)) { }
			#if TS_SSE >= 2
				explicit float32x4_t(const int32x4_t &v) : vec(_mm_cvtepi32_ps(v.vec)) { }
				explicit float32x4_t(const uint32x4_t &v) : vec(_mm_cvtepi32_ps(v.vec)) { }
			#else
				explicit float32x4_t(const int32x4_t &v) : x((float32_t)v.x), y((float32_t)v.y), z((float32_t)v.z), w((float32_t)v.w) { }
				explicit float32x4_t(const uint32x4_t &v) : x((float32_t)v.x), y((float32_t)v.y), z((float32_t)v.z), w((float32_t)v.w) { }
			#endif
			#if TS_AVX >= 1
				explicit float32x4_t(const float16x4_t &v) : vec(_mm_cvtph_ps(_mm_set1_epi64x(v.vec))) { }
			#else
				explicit float32x4_t(const float16x4_t &v) : x(v.f16.x.get()), y(v.f16.y.get()), z(v.f16.z.get()), w(v.f16.w.get()) { }
			#endif
			float32x4_t(float32_t x, float32_t y, float32_t z, float32_t w = 0.0f) : vec(_mm_setr_ps(x, y, z, w)) { }
		#elif TS_NEON
			float32x4_t(const float32x4_t &v) : vec(v.vec) { }
			explicit float32x4_t(::float32x4_t v) : vec(v) { }
			explicit float32x4_t(float32_t v) : vec(vdupq_n_f32(v)) { }
			explicit float32x4_t(const int32x4_t &v) : vec(vcvtq_f32_s32(v.vec)) { }
			explicit float32x4_t(const uint32x4_t &v) : vec(vcvtq_f32_u32(v.vec)) { }
			#if TS_ARM64
				explicit float32x4_t(const float16x4_t &v) : vec(vcvt_f32_f16((::float16x4_t)v.vec)) { }
			#else
				explicit float32x4_t(const float16x4_t &v) : x(v.f16.x.get()), y(v.f16.y.get()), z(v.f16.z.get()), w(v.f16.w.get()) { }
			#endif
			float32x4_t(float32_t x, float32_t y, float32_t z, float32_t w = 0.0f) : vec(vsetq_f32(x, y, z, w)) { }
		#else
			explicit float32x4_t(float32_t v) : x(v), y(v), z(v), w(v) { }
			explicit float32x4_t(const int32x4_t &v) : x((float32_t)v.x), y((float32_t)v.y), z((float32_t)v.z), w((float32_t)v.w) { }
			explicit float32x4_t(const uint32x4_t &v) : x((float32_t)v.x), y((float32_t)v.y), z((float32_t)v.z), w((float32_t)v.w) { }
			explicit float32x4_t(const float16x4_t &v) : x(v.f16.x.get()), y(v.f16.y.get()), z(v.f16.z.get()), w(v.f16.w.get()) { }
			float32x4_t(float32_t x, float32_t y, float32_t z, float32_t w = 0.0f) : x(x), y(y), z(z), w(w) { }
		#endif
		
		/// cast vector data
		TS_INLINE int32x4_t asi32x4() const {
			#if TS_SSE >= 2
				return int32x4_t(_mm_castps_si128(vec));
			#elif TS_NEON
				return int32x4_t(vreinterpretq_s32_f32(vec));
			#else
				return int32x4_t((int32_t*)v);
			#endif
		}
		TS_INLINE uint32x4_t asu32x4() const {
			#if TS_SSE >= 2
				return uint32x4_t(_mm_castps_si128(vec));
			#elif TS_NEON
				return uint32x4_t(vreinterpretq_u32_f32(vec));
			#else
				return uint32x4_t((uint32_t*)v);
			#endif
		}
		TS_INLINE int16x8_t asi16x8() const {
			#if TS_SSE >= 2
				return int16x8_t(_mm_castps_si128(vec));
			#elif TS_NEON
				return int16x8_t(vreinterpretq_s16_f32(vec));
			#else
				return int16x8_t((int16_t*)v);
			#endif
		}
		TS_INLINE uint16x8_t asu16x8() const {
			#if TS_SSE >= 2
				return uint16x8_t(_mm_castps_si128(vec));
			#elif TS_NEON
				return uint16x8_t(vreinterpretq_u16_f32(vec));
			#else
				return uint16x8_t((uint16_t*)v);
			#endif
		}
		TS_INLINE float16x8_t asf16x8() const {
			#if TS_SSE >= 2
				return float16x8_t(_mm_castps_si128(vec));
			#elif TS_NEON
				return float16x8_t(vreinterpretq_u16_f32(vec));
			#else
				return float16x8_t((float16_t*)v);
			#endif
		}
		
		/// update vector data
		TS_INLINE void set(const float32x4_t &v) {
			#if TS_SSE >= 2
				vec = v.vec;
			#elif TS_NEON
				vec = v.vec;
			#else
				x = v.x; y = v.y; z = v.z; w = v.w;
			#endif
		}
		TS_INLINE void set(float32_t X, float32_t Y, float32_t Z, float32_t W) {
			#if TS_SSE >= 1
				vec = _mm_setr_ps(X, Y, Z, W);
			#elif TS_NEON
				vec = vsetq_f32(X, Y, Z, W);
			#else
				x = X; y = Y; z = Z; w = W;
			#endif
		}
		TS_INLINE void set(const float32_t *TS_RESTRICT v, float32_t W) {
			#if TS_SSE >= 1
				vec = _mm_setr_ps(v[0], v[1], v[2], W);
			#elif TS_NEON
				vec = vsetq_f32(v[0], v[1], v[2], W);
			#else
				x = v[0]; y = v[1]; z = v[2]; w = W;
			#endif
		}
		TS_INLINE void set(const float32_t *TS_RESTRICT v) {
			#if TS_SSE >= 1
				vec = _mm_load_ps(v);
			#elif TS_NEON
				vec = _vld1q_f32(v);
			#else
				x = v[0]; y = v[1]; z = v[2]; w = v[3];
			#endif
		}
		TS_INLINE void get(float32_t *TS_RESTRICT v) const {
			#if TS_SSE >= 1
				_mm_stream_ps(v, vec);
			#elif TS_NEON
				_vst1q_f32(v, vec);
			#else
				v[0] = x; v[1] = y; v[2] = z; v[3] = w;
			#endif
		}
		template <uint32_t Index> TS_INLINE void set(float32_t V) {
			#if TS_SSE >= 4
				vec = _mm_castsi128_ps(_mm_insert_epi32(_mm_castps_si128(vec), (int32_t)f32u32(V).u, Index));
			#elif TS_NEON
				vec = _vsetq_lane_f32<Index>(V, vec);
			#else
				v[Index] = V;
			#endif
		}
		template <uint32_t Index> TS_INLINE float32_t get() const {
			#if TS_SSE >= 4
				return f32u32((uint32_t)_mm_extract_epi32(_mm_castps_si128(vec), Index)).f;
			#elif TS_NEON
				return _vgetq_lane_f32<Index>(vec);
			#else
				return v[Index];
			#endif
		}
		template <uint32_t Index> TS_INLINE float32x4_t get4() const {
			#if TS_SSE >= 1
				return float32x4_t(_mm_shuffle_ps(vec, vec, (Index << 6) | (Index << 4) | (Index << 2) | Index));
			#elif TS_NEON
				return float32x4_t(vdupq_n_f32(_vgetq_lane_f32<Index>(vec)));
			#else
				return float32x4_t(v[Index]);
			#endif
		}
		
		/// vector to scalar operators
		TS_INLINE float32x4_t &operator*=(float32_t v) {
			#if TS_SSE >= 1
				vec = _mm_mul_ps(vec, _mm_set1_ps(v));
			#elif TS_NEON
				vec = vmulq_f32(vec, vdupq_n_f32(v));
			#else
				x *= v; y *= v; z *= v; w *= v;
			#endif
			return *this;
		}
		TS_INLINE float32x4_t &operator/=(float32_t v) {
			#if TS_SSE >= 1
				vec = _mm_div_ps(vec, _mm_set1_ps(v));
			#elif TS_NEON
				vec = vdivq_f32(vec, vdupq_n_f32(v));
			#else
				x /= v; y /= v; z /= v; w /= v;
			#endif
			return *this;
		}
		TS_INLINE float32x4_t &operator+=(float32_t v) {
			#if TS_SSE >= 1
				vec = _mm_add_ps(vec, _mm_set1_ps(v));
			#elif TS_NEON
				vec = vaddq_f32(vec, vdupq_n_f32(v));
			#else
				x += v; y += v; z += v; w += v;
			#endif
			return *this;
		}
		TS_INLINE float32x4_t &operator-=(float32_t v) {
			#if TS_SSE >= 1
				vec = _mm_sub_ps(vec, _mm_set1_ps(v));
			#elif TS_NEON
				vec = vsubq_f32(vec, vdupq_n_f32(v));
			#else
				x -= v; y -= v; z -= v; w -= v;
			#endif
			return *this;
		}
		
		/// vector to vector operators
		TS_INLINE float32x4_t &operator*=(const float32x4_t &v) {
			#if TS_SSE >= 1
				vec = _mm_mul_ps(vec, v.vec);
			#elif TS_NEON
				vec = vmulq_f32(vec, v.vec);
			#else
				x *= v.x; y *= v.y; z *= v.z; w *= v.w;
			#endif
			return *this;
		}
		TS_INLINE float32x4_t &operator/=(const float32x4_t &v) {
			#if TS_SSE >= 1
				vec = _mm_div_ps(vec, v.vec);
			#elif TS_NEON
				vec = vdivq_f32(vec, v.vec);
			#else
				x /= v.x; y /= v.y; z /= v.z; w /= v.w;
			#endif
			return *this;
		}
		TS_INLINE float32x4_t &operator+=(const float32x4_t &v) {
			#if TS_SSE >= 1
				vec = _mm_add_ps(vec, v.vec);
			#elif TS_NEON
				vec = vaddq_f32(vec, v.vec);
			#else
				x += v.x; y += v.y; z += v.z; w += v.w;
			#endif
			return *this;
		}
		TS_INLINE float32x4_t &operator-=(const float32x4_t &v) {
			#if TS_SSE >= 1
				vec = _mm_sub_ps(vec, v.vec);
			#elif TS_NEON
				vec = vsubq_f32(vec, v.vec);
			#else
				x -= v.x; y -= v.y; z -= v.z; w -= v.w;
			#endif
			return *this;
		}
		
		/// swizzle vector
		TS_INLINE float32x4_t zxyw() const {
			#if TS_SSE >= 1
				return float32x4_t(_mm_swizzle_ps(vec, vec, Z, X, Y, W));
			#elif TS_NEON
				::float32x4_t temp = _vsetq_lane_f32<0>(_vgetq_lane_f32<2>(vec), vec);
				temp = _vsetq_lane_f32<1>(_vgetq_lane_f32<0>(vec), temp);
				temp = _vsetq_lane_f32<2>(_vgetq_lane_f32<1>(vec), temp);
				return float32x4_t(temp);
			#else
				return float32x4_t(z, x, y, w);
			#endif
		}
		TS_INLINE float32x4_t zwxy() const {
			#if TS_SSE >= 1
				return float32x4_t(_mm_swizzle_ps(vec, vec, Z, W, X, Y));
			#elif TS_NEON
				return float32x4_t(vcombine_f32(vget_high_f32(vec), vget_low_f32(vec)));
			#else
				return float32x4_t(z, w, x, y);
			#endif
		}
		TS_INLINE float32x4_t yxwz() const {
			#if TS_SSE >= 1
				return float32x4_t(_mm_swizzle_ps(vec, vec, Y, X, W, Z));
			#elif TS_NEON
				return float32x4_t(vrev64q_f32(vec));
			#else
				return float32x4_t(y, x, w, z);
			#endif
		}
		
		/// sum vector components
		TS_INLINE float32_t sum() const {
			#if TS_SSE >= 4
				__m128 temp = _mm_hadd_ps(vec, vec);
				temp = _mm_hadd_ps(temp, temp);
				return _mm_cvtss_f32(temp);
			#elif TS_SSE >= 2
				__m128 temp = _mm_add_ps(vec, _mm_swizzle_ps(vec, vec, Z, W, X, Y));
				temp = _mm_add_ps(temp, _mm_swizzle_ps(temp, temp, Y, X, W, Z));
				return _mm_cvtss_f32(temp);
			#elif TS_NEON
				::float32x2_t temp = vadd_f32(vget_high_f32(vec), vget_low_f32(vec));
				temp = vadd_f32(temp, vrev64_f32(temp));
				return _vget_lane_f32<0>(temp);
			#else
				return x + y + z + w;
			#endif
		}
		
		enum {
			Size = 4,
		};
		
		union {
			struct {
				float32_t x, y, z, w;
			};
			float32_t v[Size];
			#if TS_SSE >= 1
				__m128 vec;
			#elif TS_NEON
				::float32x4_t vec;
			#endif
		};
	};
	
	/// unary operators
	TS_INLINE float32x4_t operator-(const float32x4_t &v) {
		#if TS_SSE >= 1
			return float32x4_t(_mm_xor_ps(v.vec, _mm_set1_ps(f32u32(Signf32).f)));
		#elif TS_NEON
			return float32x4_t(vnegq_f32(v.vec));
		#else
			return float32x4_t(-v.x, -v.y, -v.z, -v.w);
		#endif
	}
	
	/// vector to scalar operators
	TS_INLINE float32x4_t operator*(const float32x4_t &v0, float32_t v1) {
		#if TS_SSE >= 1
			return float32x4_t(_mm_mul_ps(v0.vec, _mm_set1_ps(v1)));
		#elif TS_NEON
			return float32x4_t(vmulq_f32(v0.vec, vdupq_n_f32(v1)));
		#else
			return float32x4_t(v0.x * v1, v0.y * v1, v0.z * v1, v0.w * v1);
		#endif
	}
	TS_INLINE float32x4_t operator/(const float32x4_t &v0, float32_t v1) {
		#if TS_SSE >= 1
			return float32x4_t(_mm_div_ps(v0.vec, _mm_set1_ps(v1)));
		#elif TS_NEON
			return float32x4_t(vdivq_f32(v0.vec, vdupq_n_f32(v1)));
		#else
			return float32x4_t(v0.x / v1, v0.y / v1, v0.z / v1, v0.w / v1);
		#endif
	}
	TS_INLINE float32x4_t operator+(const float32x4_t &v0, float32_t v1) {
		#if TS_SSE >= 1
			return float32x4_t(_mm_add_ps(v0.vec, _mm_set1_ps(v1)));
		#elif TS_NEON
			return float32x4_t(vaddq_f32(v0.vec, vdupq_n_f32(v1)));
		#else
			return float32x4_t(v0.x + v1, v0.y + v1, v0.z + v1, v0.w + v1);
		#endif
	}
	TS_INLINE float32x4_t operator-(const float32x4_t &v0, float32_t v1) {
		#if TS_SSE >= 1
			return float32x4_t(_mm_sub_ps(v0.vec, _mm_set1_ps(v1)));
		#elif TS_NEON
			return float32x4_t(vsubq_f32(v0.vec, vdupq_n_f32(v1)));
		#else
			return float32x4_t(v0.x - v1, v0.y - v1, v0.z - v1, v0.w - v1);
		#endif
	}
	
	/// vector to vector operators
	TS_INLINE float32x4_t operator*(const float32x4_t &v0, const float32x4_t &v1) {
		#if TS_SSE >= 1
			return float32x4_t(_mm_mul_ps(v0.vec, v1.vec));
		#elif TS_NEON
			return float32x4_t(vmulq_f32(v0.vec, v1.vec));
		#else
			return float32x4_t(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z, v0.w * v1.w);
		#endif
	}
	TS_INLINE float32x4_t operator/(const float32x4_t &v0, const float32x4_t &v1) {
		#if TS_SSE >= 1
			return float32x4_t(_mm_div_ps(v0.vec, v1.vec));
		#elif TS_NEON
			return float32x4_t(vdivq_f32(v0.vec, v1.vec));
		#else
			return float32x4_t(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z, v0.w / v1.w);
		#endif
	}
	TS_INLINE float32x4_t operator+(const float32x4_t &v0, const float32x4_t &v1) {
		#if TS_SSE >= 1
			return float32x4_t(_mm_add_ps(v0.vec, v1.vec));
		#elif TS_NEON
			return float32x4_t(vaddq_f32(v0.vec, v1.vec));
		#else
			return float32x4_t(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w);
		#endif
	}
	TS_INLINE float32x4_t operator-(const float32x4_t &v0, const float32x4_t &v1) {
		#if TS_SSE >= 1
			return float32x4_t(_mm_sub_ps(v0.vec, v1.vec));
		#elif TS_NEON
			return float32x4_t(vsubq_f32(v0.vec, v1.vec));
		#else
			return float32x4_t(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w);
		#endif
	}
	
	/// comparison operators
	TS_INLINE uint32_t operator<(const float32x4_t &v0, const float32x4_t &v1) {
		#if TS_SSE >= 1
			return _mm_movemask_ps(_mm_cmplt_ps(v0.vec, v1.vec));
		#elif TS_NEON
			return vmaskq_u32(vcltq_f32(v0.vec, v1.vec));
		#else
			return ((uint32_t)(v0.x < v1.x) << 0) | ((uint32_t)(v0.y < v1.y) << 1) | ((uint32_t)(v0.z < v1.z) << 2) | ((uint32_t)(v0.w < v1.w) << 3);
		#endif
	}
	TS_INLINE uint32_t operator>(const float32x4_t &v0, const float32x4_t &v1) {
		#if TS_SSE >= 1
			return _mm_movemask_ps(_mm_cmpgt_ps(v0.vec, v1.vec));
		#elif TS_NEON
			return vmaskq_u32(vcgtq_f32(v0.vec, v1.vec));
		#else
			return ((uint32_t)(v0.x > v1.x) << 0) | ((uint32_t)(v0.y > v1.y) << 1) | ((uint32_t)(v0.z > v1.z) << 2) | ((uint32_t)(v0.w > v1.w) << 3);
		#endif
	}
	TS_INLINE uint32_t operator<=(const float32x4_t &v0, const float32x4_t &v1) {
		#if TS_SSE >= 1
			return _mm_movemask_ps(_mm_cmple_ps(v0.vec, v1.vec));
		#elif TS_NEON
			return vmaskq_u32(vcleq_f32(v0.vec, v1.vec));
		#else
			return ((uint32_t)(v0.x <= v1.x) << 0) | ((uint32_t)(v0.y <= v1.y) << 1) | ((uint32_t)(v0.z <= v1.z) << 2) | ((uint32_t)(v0.w <= v1.w) << 3);
		#endif
	}
	TS_INLINE uint32_t operator>=(const float32x4_t &v0, const float32x4_t &v1) {
		#if TS_SSE >= 1
			return _mm_movemask_ps(_mm_cmpge_ps(v0.vec, v1.vec));
		#elif TS_NEON
			return vmaskq_u32(vcgeq_f32(v0.vec, v1.vec));
		#else
			return ((uint32_t)(v0.x >= v1.x) << 0) | ((uint32_t)(v0.y >= v1.y) << 1) | ((uint32_t)(v0.z >= v1.z) << 2) | ((uint32_t)(v0.w >= v1.w) << 3);
		#endif
	}
	TS_INLINE uint32_t operator==(const float32x4_t &v0, const float32x4_t &v1) {
		#if TS_SSE >= 1
			return _mm_movemask_ps(_mm_cmpeq_ps(v0.vec, v1.vec));
		#elif TS_NEON
			return vmaskq_u32(vceqq_f32(v0.vec, v1.vec));
		#else
			return ((uint32_t)(v0.x == v1.x) << 0) | ((uint32_t)(v0.y == v1.y) << 1) | ((uint32_t)(v0.z == v1.z) << 2) | ((uint32_t)(v0.w == v1.w) << 3);
		#endif
	}
	TS_INLINE uint32_t operator!=(const float32x4_t &v0, const float32x4_t &v1) {
		#if TS_SSE >= 1
			return _mm_movemask_ps(_mm_cmpneq_ps(v0.vec, v1.vec));
		#elif TS_NEON
			return (~vmaskq_u32(vceqq_f32(v0.vec, v1.vec))) & 0x0f;
		#else
			return ((uint32_t)(v0.x != v1.x) << 0) | ((uint32_t)(v0.y != v1.y) << 1) | ((uint32_t)(v0.z != v1.z) << 2) | ((uint32_t)(v0.w != v1.w) << 3);
		#endif
	}
	
	/// min/max functions
	TS_INLINE float32x4_t min(const float32x4_t &v0, const float32x4_t &v1) {
		#if TS_SSE >= 1
			return float32x4_t(_mm_min_ps(v0.vec, v1.vec));
		#elif TS_NEON
			return float32x4_t(vminq_f32(v0.vec, v1.vec));
		#else
			return float32x4_t(min(v0.x, v1.x), min(v0.y, v1.y), min(v0.z, v1.z), min(v0.w, v1.w));
		#endif
	}
	TS_INLINE float32x4_t max(const float32x4_t &v0, const float32x4_t &v1) {
		#if TS_SSE >= 1
			return float32x4_t(_mm_max_ps(v0.vec, v1.vec));
		#elif TS_NEON
			return float32x4_t(vmaxq_f32(v0.vec, v1.vec));
		#else
			return float32x4_t(max(v0.x, v1.x), max(v0.y, v1.y), max(v0.z, v1.z), max(v0.w, v1.w));
		#endif
	}
	
	/// range functions
	TS_INLINE float32x4_t saturate(const float32x4_t &v) {
		return min(max(v, float32x4_t(0.0f)), float32x4_t(1.0f));
	}
	TS_INLINE float32x4_t clamp(const float32x4_t &v, float32_t v0, float32_t v1) {
		return min(max(v, float32x4_t(v0)), float32x4_t(v1));
	}
	TS_INLINE float32x4_t clamp(const float32x4_t &v, const float32x4_t &v0, const float32x4_t &v1) {
		return min(max(v, v0), v1);
	}
	
	/// select functions
	TS_INLINE float32x4_t select(const float32x4_t &v0, const float32x4_t &v1, const float32x4_t &s) {
		#if TS_AVX >= 1
			return float32x4_t(_mm_blendv_ps(v0.vec, v1.vec, s.vec));
		#elif TS_SSE >= 2
			return float32x4_t(_mm_xor_ps(v0.vec, _mm_and_ps(_mm_xor_ps(v0.vec, v1.vec), _mm_cmplt_ps(s.vec, _mm_setzero_ps()))));
		#elif TS_NEON
			return float32x4_t(vbslq_f32(vcgeq_f32(s.vec, vdupq_n_f32(0.0f)), v0.vec, v1.vec));
		#else
			return float32x4_t(select(v0.x, v1.x, s.x), select(v0.y, v1.y, s.y), select(v0.z, v1.z, s.z), select(v0.w, v1.w, s.w));
		#endif
	}
	TS_INLINE float32x4_t select(const float32x4_t &v0, const float32x4_t &v1, float32_t s) {
		return select(v0, v1, float32x4_t(s));
	}
	
	/// math functions
	TS_INLINE float32x4_t rcp(const float32x4_t &v) {
		#if TS_SSE >= 1
			return float32x4_t(_mm_rcp_ps_nr(v.vec));
		#elif TS_NEON
			return float32x4_t(vrcpq_f32(v.vec));
		#else
			return float32x4_t(rcp(v.x), rcp(v.y), rcp(v.z), rcp(v.w));
		#endif
	}
	TS_INLINE float32x4_t sqrt(const float32x4_t &v) {
		#if TS_SSE >= 1
			return float32x4_t(_mm_sqrt_ps(v.vec));
		#elif TS_NEON
			return float32x4_t(vsqrtq_f32(v.vec));
		#else
			return float32x4_t(sqrt(v.x), sqrt(v.y), sqrt(v.z), sqrt(v.w));
		#endif
	}
	TS_INLINE float32x4_t rsqrt(const float32x4_t &v) {
		#if TS_SSE >= 1
			return float32x4_t(_mm_rsqrt_ps_nr(v.vec));
		#elif TS_NEON
			return float32x4_t(vrsqrtq_f32(v.vec));
		#else
			return float32x4_t(rsqrt(v.x), rsqrt(v.y), rsqrt(v.z), rsqrt(v.w));
		#endif
	}
	TS_INLINE float32x4_t abs(const float32x4_t &v) {
		#if TS_SSE >= 1
			return float32x4_t(_mm_and_ps(v.vec, _mm_set1_ps(f32u32(~Signf32).f)));
		#elif TS_NEON
			return float32x4_t(vabsq_f32(v.vec));
		#else
			return float32x4_t(abs(v.x), abs(v.y), abs(v.z), abs(v.w));
		#endif
	}
	TS_INLINE float32x4_t ceil(const float32x4_t &v) {
		#if TS_SSE >= 2
			float32x4_t f = float32x4_t(_mm_cvtepi32_ps(_mm_cvtps_epi32(v.vec)));
			return f + float32x4_t(_mm_and_ps(_mm_set1_ps(1.0f), _mm_cmpgt_ps(v.vec, f.vec)));
		#elif TS_NEON
			float32x4_t f = float32x4_t(vcvtq_f32_s32(vcvtq_s32_f32(v.vec)));
			return f + float32x4_t(vbslq_f32(vcgtq_f32(v.vec, f.vec), vdupq_n_f32(1.0f), vdupq_n_f32(0.0f)));
		#else
			return float32x4_t(ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w));
		#endif
	}
	TS_INLINE float32x4_t floor(const float32x4_t &v) {
		#if TS_SSE >= 2
			float32x4_t f = float32x4_t(_mm_cvtepi32_ps(_mm_cvtps_epi32(v.vec)));
			return f - float32x4_t(_mm_and_ps(_mm_set1_ps(1.0f), _mm_cmplt_ps(v.vec, f.vec)));
		#elif TS_NEON
			float32x4_t f = float32x4_t(vcvtq_f32_s32(vcvtq_s32_f32(v.vec)));
			return f - float32x4_t(vbslq_f32(vcltq_f32(v.vec, f.vec), vdupq_n_f32(1.0f), vdupq_n_f32(0.0f)));
		#else
			return float32x4_t(floor(v.x), floor(v.y), floor(v.z), floor(v.w));
		#endif
	}
	
	/// fast math functions
	TS_INLINE float32x4_t rsqrtFast(const float32x4_t &v) {
		float32x4_t r = (uint32x4_t(0x5f3759dfu) - (v.asu32x4() >> 1)).asf32x4();
		return (float32x4_t(1.5f) - r * r * v * 0.5f) * r;
	}
	TS_INLINE float32x4_t powFast(const float32x4_t &v, const float32x4_t &p) {
		int32x4_t i = max(v, float32x4_t(1e-16f)).asi32x4() - 0x3f79e59d;
		i = int32x4_t(float32x4_t(i) * p) + 0x3f79e59d;
		return int32x4_t(i).asf32x4();
	}
	TS_INLINE float32x4_t powFast(const float32x4_t &v, float32_t p) {
		return powFast(v, float32x4_t(p));
	}
	
	/// vector functions
	TS_INLINE float32x4_t lerp(const float32x4_t &v0, const float32x4_t &v1, float32_t k) {
		#if TS_SSE >= 1
			return float32x4_t(_mm_add_ps(v0.vec, _mm_mul_ps(_mm_sub_ps(v1.vec, v0.vec), _mm_set1_ps(k))));
		#elif TS_NEON
			return float32x4_t(vaddq_f32(v0.vec, vmulq_f32(vsubq_f32(v1.vec, v0.vec), vdupq_n_f32(k))));
		#else
			return float32x4_t(lerp(v0.x, v1.x, k), lerp(v0.y, v1.y, k), lerp(v0.z, v1.z, k), lerp(v0.w, v1.w, k));
		#endif
	}
	
	/*****************************************************************************\
	 *
	 * float32x8_t
	 *
	\*****************************************************************************/
	
	/**
	 * Vector of eight float32_t components
	 */
	struct TS_ALIGNAS32 float32x8_t {
		
		float32x8_t() { }
		explicit float32x8_t(const float64x8_t &v);
		explicit float32x8_t(const float32_t *v) { set(v); }
		#if TS_AVX >= 1
			float32x8_t(const float32x8_t &v) : vec(v.vec) { }
			explicit float32x8_t(__m256 v) : vec(v) { }
			explicit float32x8_t(float32_t v) : vec(_mm256_set1_ps(v)) { }
			float32x8_t(__m128 v0, __m128 v1) : vec(_mm256_setr_m128(v0, v1)) { }
			explicit float32x8_t(const int32x8_t &v) : vec(_mm256_cvtepi32_ps(v.vec)) { }
			explicit float32x8_t(const uint32x8_t &v) : vec(_mm256_cvtepi32_ps(v.vec)) { }
			explicit float32x8_t(const float16x8_t &v) : vec(_mm256_cvtph_ps(v.vec)) { }
			float32x8_t(const float32x4_t &v0, const float32x4_t &v1) : vec(_mm256_setr_m128(v0.vec, v1.vec)) { }
			float32x8_t(float32_t x0, float32_t y0, float32_t z0, float32_t w0, float32_t x1, float32_t y1, float32_t z1, float32_t w1) : vec(_mm256_setr_ps(x0, y0, z0, w0, x1, y1, z1, w1)) { }
		#elif TS_SSE >= 1
			float32x8_t(const float32x8_t &v) : vec0(v.vec0), vec1(v.vec1) { }
			float32x8_t(__m128 v0, __m128 v1) : vec0(v0), vec1(v1) { }
			explicit float32x8_t(float32_t v) : vec0(_mm_set1_ps(v)), vec1(_mm_set1_ps(v)) { }
			explicit float32x8_t(const int32x8_t &v) : vec0(_mm_cvtepi32_ps(v.vec0)), vec1(_mm_cvtepi32_ps(v.vec1)) { }
			explicit float32x8_t(const uint32x8_t &v) : vec0(_mm_cvtepi32_ps(v.vec0)), vec1(_mm_cvtepi32_ps(v.vec1)) { }
			float32x8_t(const float32x4_t &v0, const float32x4_t &v1) : vec0(v0.vec), vec1(v1.vec) { }
			explicit float32x8_t(const float16x8_t &v) : x0(v.f16.x0.get()), y0(v.f16.y0.get()), z0(v.f16.z0.get()), w0(v.f16.w0.get()), x1(v.f16.x1.get()), y1(v.f16.y1.get()), z1(v.f16.z1.get()), w1(v.f16.w1.get()) { }
			float32x8_t(float32_t x0, float32_t y0, float32_t z0, float32_t w0, float32_t x1, float32_t y1, float32_t z1, float32_t w1) : vec0(_mm_setr_ps(x0, y0, z0, w0)), vec1(_mm_setr_ps(x1, y1, z1, w1)) { }
		#elif TS_NEON
			float32x8_t(const float32x8_t &v) : vec0(v.vec0), vec1(v.vec1) { }
			float32x8_t(::float32x4_t v0, ::float32x4_t v1) : vec0(v0), vec1(v1) { }
			explicit float32x8_t(float32_t v) : vec0(vdupq_n_f32(v)), vec1(vdupq_n_f32(v)) { }
			explicit float32x8_t(const int32x8_t &v) : vec0(vcvtq_f32_s32(v.vec0)), vec1(vcvtq_f32_s32(v.vec1)) { }
			explicit float32x8_t(const uint32x8_t &v) : vec0(vcvtq_f32_u32(v.vec0)), vec1(vcvtq_f32_u32(v.vec1)) { }
			float32x8_t(const float32x4_t &v0, const float32x4_t &v1) : vec0(v0.vec), vec1(v1.vec) { }
			#if TS_ARM64
				explicit float32x8_t(const float16x8_t &v) : vec0(vcvt_f32_f16((::float16x4_t)vget_low_u16(v.vec))), vec1(vcvt_f32_f16((::float16x4_t)vget_high_u16(v.vec))) { }
			#else
				explicit float32x8_t(const float16x8_t &v) : x0(v.f16.x0.get()), y0(v.f16.y0.get()), z0(v.f16.z0.get()), w0(v.f16.w0.get()), x1(v.f16.x1.get()), y1(v.f16.y1.get()), z1(v.f16.z1.get()), w1(v.f16.w1.get()) { }
			#endif
			float32x8_t(float32_t x0, float32_t y0, float32_t z0, float32_t w0, float32_t x1, float32_t y1, float32_t z1, float32_t w1) : vec0(vsetq_f32(x0, y0, z0, w0)), vec1(vsetq_f32(x1, y1, z1, w1)) { }
		#else
			explicit float32x8_t(float32_t v) : x0(v), y0(v), z0(v), w0(v), x1(v), y1(v), z1(v), w1(v) { }
			explicit float32x8_t(const int32x8_t &v) : x0((float32_t)v.x0), y0((float32_t)v.y0), z0((float32_t)v.z0), w0((float32_t)v.w0), x1((float32_t)v.x1), y1((float32_t)v.y1), z1((float32_t)v.z1), w1((float32_t)v.w1) { }
			explicit float32x8_t(const uint32x8_t &v) : x0((float32_t)v.x0), y0((float32_t)v.y0), z0((float32_t)v.z0), w0((float32_t)v.w0), x1((float32_t)v.x1), y1((float32_t)v.y1), z1((float32_t)v.z1), w1((float32_t)v.w1) { }
			float32x8_t(const float32x4_t &v0, const float32x4_t &v1) : x0(v0.x), y0(v0.y), z0(v0.z), w0(v0.w), x1(v1.x), y1(v1.y), z1(v1.z), w1(v1.w) { }
			explicit float32x8_t(const float16x8_t &v) : x0(v.f16.x0.get()), y0(v.f16.y0.get()), z0(v.f16.z0.get()), w0(v.f16.w0.get()), x1(v.f16.x1.get()), y1(v.f16.y1.get()), z1(v.f16.z1.get()), w1(v.f16.w1.get()) { }
			float32x8_t(float32_t x0, float32_t y0, float32_t z0, float32_t w0, float32_t x1, float32_t y1, float32_t z1, float32_t w1) : x0(x0), y0(y0), z0(z0), w0(w0), x1(x1), y1(y1), z1(z1), w1(w1) { }
		#endif
		
		/// cast vector data
		TS_INLINE int32x8_t asi32x8() const {
			#if TS_AVX >= 1
				return int32x8_t(_mm256_castps_si256(vec));
			#elif TS_SSE >= 1
				return int32x8_t(_mm_castps_si128(vec0), _mm_castps_si128(vec1));
			#elif TS_NEON
				return int32x8_t(vreinterpretq_s32_f32(vec0), vreinterpretq_s32_f32(vec1));
			#else
				return int32x8_t((int32_t*)v);
			#endif
		}
		TS_INLINE uint32x8_t asu32x8() const {
			#if TS_AVX >= 1
				return uint32x8_t(_mm256_castps_si256(vec));
			#elif TS_SSE >= 1
				return uint32x8_t(_mm_castps_si128(vec0), _mm_castps_si128(vec1));
			#elif TS_NEON
				return uint32x8_t(vreinterpretq_u32_f32(vec0), vreinterpretq_u32_f32(vec1));
			#else
				return uint32x8_t((uint32_t*)v);
			#endif
		}
		
		/// update vector data
		TS_INLINE void set(const float32x8_t &v) {
			#if TS_AVX >= 1
				vec = v.vec;
			#elif TS_SSE >= 1
				vec0 = v.vec0;
				vec1 = v.vec1;
			#elif TS_NEON
				vec0 = v.vec0;
				vec1 = v.vec1;
			#else
				x0 = v.x0; y0 = v.y0; z0 = v.z0; w0 = v.w0;
				x1 = v.x1; y1 = v.y1; z1 = v.z1; w1 = v.w1;
			#endif
		}
		TS_INLINE void set(float32_t X0, float32_t Y0, float32_t Z0, float32_t W0, float32_t X1, float32_t Y1, float32_t Z1, float32_t W1) {
			#if TS_AVX >= 1
				vec = _mm256_setr_ps(X0, Y0, Z0, W0, X1, Y1, Z1, W1);
			#elif TS_SSE >= 1
				vec0 = _mm_setr_ps(X0, Y0, Z0, W0);
				vec1 = _mm_setr_ps(X1, Y1, Z1, W1);
			#elif TS_NEON
				vec0 = vsetq_f32(X0, Y0, Z0, W0);
				vec1 = vsetq_f32(X1, Y1, Z1, W1);
			#else
				x0 = X0; y0 = Y0; z0 = Z0; w0 = W0;
				x1 = X1; y1 = Y1; z1 = Z1; w1 = W1;
			#endif
		}
		TS_INLINE void set(const float32_t *TS_RESTRICT v) {
			#if TS_AVX >= 1
				vec = _mm256_load_ps(v);
			#elif TS_SSE >= 1
				vec0 = _mm_load_ps(v + 0);
				vec1 = _mm_load_ps(v + 4);
			#elif TS_NEON
				vec0 = _vld1q_f32(v + 0);
				vec1 = _vld1q_f32(v + 4);
			#else
				x0 = v[0]; y0 = v[1]; z0 = v[2]; w0 = v[3];
				x1 = v[4]; y1 = v[5]; z1 = v[6]; w1 = v[7];
			#endif
		}
		TS_INLINE void get(float32_t *TS_RESTRICT v) const {
			#if TS_AVX >= 1
				_mm256_stream_ps(v, vec);
			#elif TS_SSE >= 1
				_mm_stream_ps(v + 0, vec0);
				_mm_stream_ps(v + 4, vec1);
			#elif TS_NEON
				_vst1q_f32(v + 0, vec0);
				_vst1q_f32(v + 4, vec1);
			#else
				v[0] = x0; v[1] = y0; v[2] = z0; v[3] = w0;
				v[4] = x1; v[5] = y1; v[6] = z1; v[7] = w1;
			#endif
		}
		template <uint32_t Index> TS_INLINE void set(float32_t V) {
			#if TS_AVX >= 1
				__m128i temp = _mm_insert_epi32(_mm256_extractf128_si256(_mm256_castps_si256(vec), Index >> 2), (int32_t)f32u32(V).u, Index & 0x03);
				vec = _mm256_castsi256_ps(_mm256_insertf128_si256(_mm256_castps_si256(vec), temp, Index >> 2));
			#elif TS_SSE >= 4
				vec[Index >> 2] = _mm_castsi128_ps(_mm_insert_epi32(_mm_castps_si128(vec[Index >> 2]), (int32_t)f32u32(V).u, Index & 0x03));
			#elif TS_NEON
				vec[Index >> 2] = _vsetq_lane_f32<Index & 0x03>(V, vec[Index >> 2]);
			#else
				v[Index] = V;
			#endif
		}
		template <uint32_t Index> TS_INLINE float32_t get() const {
			#if TS_AVX >= 1
				return f32u32((uint32_t)_mm_extract_epi32(_mm_castps_si128(_mm256_extractf128_ps(vec, Index >> 2)), Index & 0x03)).f;
			#elif TS_SSE >= 4
				return f32u32((uint32_t)_mm_extract_epi32(_mm_castps_si128(vec[Index >> 2]), Index & 0x03)).f;
			#elif TS_NEON
				return _vgetq_lane_f32<Index & 0x03>(vec[Index >> 2]);
			#else
				return v[Index];
			#endif
		}
		template <uint32_t Index> TS_INLINE float32x8_t get8() const {
			#if TS_AVX >= 1
				__m128 temp = _mm256_extractf128_ps(vec, Index >> 2);
				temp = _mm_shuffle_ps(temp, temp, ((Index & 0x03) << 6) | ((Index & 0x03) << 4) | ((Index & 0x03) << 2) | (Index & 0x03));
				return float32x8_t(temp, temp);
			#elif TS_SSE >= 4
				__m128 temp = _mm_shuffle_ps(vec[Index >> 2], vec[Index >> 2], ((Index & 0x03) << 6) | ((Index & 0x03) << 4) | ((Index & 0x03) << 2) | (Index & 0x03));
				return float32x8_t(temp, temp);
			#elif TS_NEON
				::float32x4_t temp = vdupq_n_f32(_vgetq_lane_f32<Index & 0x03>(vec[Index >> 2]));
				return float32x8_t(temp, temp);
			#else
				return float32x8_t(v[Index]);
			#endif
		}
		
		/// vector to scalar operators
		TS_INLINE float32x8_t &operator*=(float32_t v) {
			#if TS_AVX >= 1
				vec = _mm256_mul_ps(vec, _mm256_set1_ps(v));
			#elif TS_SSE >= 1
				__m128 temp = _mm_set1_ps(v);
				vec0 = _mm_mul_ps(vec0, temp);
				vec1 = _mm_mul_ps(vec1, temp);
			#elif TS_NEON
				::float32x4_t temp = vdupq_n_f32(v);
				vec0 = vmulq_f32(vec0, temp);
				vec1 = vmulq_f32(vec1, temp);
			#else
				x0 *= v; y0 *= v; z0 *= v; w0 *= v; x1 *= v; y1 *= v; z1 *= v; w1 *= v;
			#endif
			return *this;
		}
		TS_INLINE float32x8_t &operator/=(float32_t v) {
			#if TS_AVX >= 1
				vec = _mm256_div_ps(vec, _mm256_set1_ps(v));
			#elif TS_SSE >= 1
				__m128 temp = _mm_set1_ps(v);
				vec0 = _mm_div_ps(vec0, temp);
				vec1 = _mm_div_ps(vec1, temp);
			#elif TS_NEON
				::float32x4_t temp = vdupq_n_f32(v);
				vec0 = vdivq_f32(vec0, temp);
				vec1 = vdivq_f32(vec1, temp);
			#else
				x0 /= v; y0 /= v; z0 /= v; w0 /= v; x1 /= v; y1 /= v; z1 /= v; w1 /= v;
			#endif
			return *this;
		}
		TS_INLINE float32x8_t &operator+=(float32_t v) {
			#if TS_AVX >= 1
				vec = _mm256_add_ps(vec, _mm256_set1_ps(v));
			#elif TS_SSE >= 1
				__m128 temp = _mm_set1_ps(v);
				vec0 = _mm_add_ps(vec0, temp);
				vec1 = _mm_add_ps(vec1, temp);
			#elif TS_NEON
				::float32x4_t temp = vdupq_n_f32(v);
				vec0 = vaddq_f32(vec0, temp);
				vec1 = vaddq_f32(vec1, temp);
			#else
				x0 += v; y0 += v; z0 += v; w0 += v; x1 += v; y1 += v; z1 += v; w1 += v;
			#endif
			return *this;
		}
		TS_INLINE float32x8_t &operator-=(float32_t v) {
			#if TS_AVX >= 1
				vec = _mm256_sub_ps(vec, _mm256_set1_ps(v));
			#elif TS_SSE >= 1
				__m128 temp = _mm_set1_ps(v);
				vec0 = _mm_sub_ps(vec0, temp);
				vec1 = _mm_sub_ps(vec1, temp);
			#elif TS_NEON
				::float32x4_t temp = vdupq_n_f32(v);
				vec0 = vsubq_f32(vec0, temp);
				vec1 = vsubq_f32(vec1, temp);
			#else
				x0 -= v; y0 -= v; z0 -= v; w0 -= v; x1 -= v; y1 -= v; z1 -= v; w1 -= v;
			#endif
			return *this;
		}
		
		/// vector to vector operators
		TS_INLINE float32x8_t &operator*=(const float32x8_t &v) {
			#if TS_AVX >= 1
				vec = _mm256_mul_ps(vec, v.vec);
			#elif TS_SSE >= 1
				vec0 = _mm_mul_ps(vec0, v.vec0);
				vec1 = _mm_mul_ps(vec1, v.vec1);
			#elif TS_NEON
				vec0 = vmulq_f32(vec0, v.vec0);
				vec1 = vmulq_f32(vec1, v.vec1);
			#else
				x0 *= v.x0; y0 *= v.y0; z0 *= v.z0; w0 *= v.w0; x1 *= v.x1; y1 *= v.y1; z1 *= v.z1; w1 *= v.w1;
			#endif
			return *this;
		}
		TS_INLINE float32x8_t &operator/=(const float32x8_t &v) {
			#if TS_AVX >= 1
				vec = _mm256_div_ps(vec, v.vec);
			#elif TS_SSE >= 1
				vec0 = _mm_div_ps(vec0, v.vec0);
				vec1 = _mm_div_ps(vec1, v.vec1);
			#elif TS_NEON
				vec0 = vdivq_f32(vec0, v.vec0);
				vec1 = vdivq_f32(vec1, v.vec1);
			#else
				x0 /= v.x0; y0 /= v.y0; z0 /= v.z0; w0 /= v.w0; x1 /= v.x1; y1 /= v.y1; z1 /= v.z1; w1 /= v.w1;
			#endif
			return *this;
		}
		TS_INLINE float32x8_t &operator+=(const float32x8_t &v) {
			#if TS_AVX >= 1
				vec = _mm256_add_ps(vec, v.vec);
			#elif TS_SSE >= 1
				vec0 = _mm_add_ps(vec0, v.vec0);
				vec1 = _mm_add_ps(vec1, v.vec1);
			#elif TS_NEON
				vec0 = vaddq_f32(vec0, v.vec0);
				vec1 = vaddq_f32(vec1, v.vec1);
			#else
				x0 += v.x0; y0 += v.y0; z0 += v.z0; w0 += v.w0; x1 += v.x1; y1 += v.y1; z1 += v.z1; w1 += v.w1;
			#endif
			return *this;
		}
		TS_INLINE float32x8_t &operator-=(const float32x8_t &v) {
			#if TS_AVX >= 1
				vec = _mm256_sub_ps(vec, v.vec);
			#elif TS_SSE >= 1
				vec0 = _mm_sub_ps(vec0, v.vec0);
				vec1 = _mm_sub_ps(vec1, v.vec1);
			#elif TS_NEON
				vec0 = vsubq_f32(vec0, v.vec0);
				vec1 = vsubq_f32(vec1, v.vec1);
			#else
				x0 -= v.x0; y0 -= v.y0; z0 -= v.z0; w0 -= v.w0; x1 -= v.x1; y1 -= v.y1; z1 -= v.z1; w1 -= v.w1;
			#endif
			return *this;
		}
		
		/// swizzle vector
		TS_INLINE float32x8_t xyzw10() const {
			#if TS_AVX >= 1
				return float32x8_t(_mm256_permute2f128_ps(vec, vec, 0x03));
			#elif TS_SSE >= 2
				return float32x8_t(vec1, vec0);
			#elif TS_NEON
				return float32x8_t(vec1, vec0);
			#else
				return float32x8_t(x1, y1, z1, w1, x0, y0, z0, w0);
			#endif
		}
		TS_INLINE float32x8_t zwxy01() const {
			#if TS_AVX >= 1
				return float32x8_t(_mm256_permute_ps(vec, 0x4e));
			#elif TS_SSE >= 2
				return float32x8_t(_mm_swizzle_ps(vec0, vec0, Z, W, X, Y), _mm_swizzle_ps(vec1, vec1, Z, W, X, Y));
			#elif TS_NEON
				return float32x8_t(vcombine_f32(vget_high_f32(vec0), vget_low_f32(vec0)), vcombine_f32(vget_high_f32(vec1), vget_low_f32(vec1)));
			#else
				return float32x8_t(z0, w0, x0, y0, z1, w1, x1, y1);
			#endif
		}
		TS_INLINE float32x8_t yxwz01() const {
			#if TS_AVX >= 1
				return float32x8_t(_mm256_permute_ps(vec, 0xb1));
			#elif TS_SSE >= 2
				return float32x8_t(_mm_swizzle_ps(vec0, vec0, Y, X, W, Z), _mm_swizzle_ps(vec1, vec1, Y, X, W, Z));
			#elif TS_NEON
				return float32x8_t(vrev64q_f32(vec0), vrev64q_f32(vec1));
			#else
				return float32x8_t(y0, x0, w0, z0, y1, x1, w1, z1);
			#endif
		}
		TS_INLINE float32x4_t xyzw0() const {
			#if TS_AVX >= 1
				return float32x4_t(_mm256_extractf128_ps(vec, 0));
			#elif TS_SSE >= 2
				return float32x4_t(vec0);
			#elif TS_NEON
				return float32x4_t(vec0);
			#else
				return float32x4_t(x0, y0, z0, w0);
			#endif
		}
		TS_INLINE float32x4_t xyzw1() const {
			#if TS_AVX >= 1
				return float32x4_t(_mm256_extractf128_ps(vec, 1));
			#elif TS_SSE >= 2
				return float32x4_t(vec1);
			#elif TS_NEON
				return float32x4_t(vec1);
			#else
				return float32x4_t(x1, y1, z1, w1);
			#endif
		}
		
		/// sum vector components
		TS_INLINE float32_t sum() const {
			#if TS_AVX >= 1
				__m128 temp = _mm_add_ps(_mm256_extractf128_ps(vec, 0), _mm256_extractf128_ps(vec, 1));
				temp = _mm_hadd_ps(temp, temp);
				temp = _mm_hadd_ps(temp, temp);
				return _mm_cvtss_f32(temp);
			#elif TS_SSE >= 4
				__m128 temp = _mm_add_ps(vec0, vec1);
				temp = _mm_hadd_ps(temp, temp);
				temp = _mm_hadd_ps(temp, temp);
				return _mm_cvtss_f32(temp);
			#elif TS_SSE >= 2
				__m128 temp = _mm_add_ps(vec0, vec1);
				temp = _mm_add_ps(temp, _mm_swizzle_ps(temp, temp, Z, W, X, Y));
				temp = _mm_add_ps(temp, _mm_swizzle_ps(temp, temp, Y, X, W, Z));
				return _mm_cvtss_f32(temp);
			#elif TS_NEON
				::float32x2_t temp = vadd_f32(vget_high_f32(vec0), vget_low_f32(vec0));
				temp = vadd_f32(temp, vadd_f32(vget_high_f32(vec1), vget_low_f32(vec1)));
				temp = vadd_f32(temp, vrev64_f32(temp));
				return _vget_lane_f32<0>(temp);
			#else
				return x0 + y0 + z0 + w0 + x1 + y1 + z1 + w1;
			#endif
		}
		
		enum {
			Size = 8,
		};
		
		union {
			struct {
				float32_t x0, y0, z0, w0;
				float32_t x1, y1, z1, w1;
			};
			float32_t v[Size];
			#if TS_AVX >= 1
				struct {
					__m128 vec0;
					__m128 vec1;
				};
				__m256 vec;
			#elif TS_SSE >= 1
				struct {
					__m128 vec0;
					__m128 vec1;
				};
				__m128 vec[2];
			#elif TS_NEON
				struct {
					::float32x4_t vec0;
					::float32x4_t vec1;
				};
				::float32x4_t vec[2];
			#endif
		};
	};
	
	/// unary operators
	TS_INLINE float32x8_t operator-(const float32x8_t &v) {
		#if TS_AVX >= 1
			return float32x8_t(_mm256_xor_ps(v.vec, _mm256_set1_ps(f32u32(Signf32).f)));
		#elif TS_SSE >= 1
			__m128 temp = _mm_set1_ps(f32u32(Signf32).f);
			return float32x8_t(_mm_xor_ps(v.vec0, temp), _mm_xor_ps(v.vec1, temp));
		#elif TS_NEON
			return float32x8_t(vnegq_f32(v.vec0), vnegq_f32(v.vec1));
		#else
			return float32x8_t(-v.x0, -v.y0, -v.z0, -v.w0, -v.x1, -v.y1, -v.z1, -v.w1);
		#endif
	}
	
	/// vector to scalar operators
	TS_INLINE float32x8_t operator*(const float32x8_t &v0, float32_t v1) {
		#if TS_AVX >= 1
			return float32x8_t(_mm256_mul_ps(v0.vec, _mm256_set1_ps(v1)));
		#elif TS_SSE >= 1
			__m128 temp = _mm_set1_ps(v1);
			return float32x8_t(_mm_mul_ps(v0.vec0, temp), _mm_mul_ps(v0.vec1, temp));
		#elif TS_NEON
			::float32x4_t temp = vdupq_n_f32(v1);
			return float32x8_t(vmulq_f32(v0.vec0, temp), vmulq_f32(v0.vec1, temp));
		#else
			return float32x8_t(v0.x0 * v1, v0.y0 * v1, v0.z0 * v1, v0.w0 * v1, v0.x1 * v1, v0.y1 * v1, v0.z1 * v1, v0.w1 * v1);
		#endif
	}
	TS_INLINE float32x8_t operator/(const float32x8_t &v0, float32_t v1) {
		#if TS_AVX >= 1
			return float32x8_t(_mm256_div_ps(v0.vec, _mm256_set1_ps(v1)));
		#elif TS_SSE >= 1
			__m128 temp = _mm_set1_ps(v1);
			return float32x8_t(_mm_div_ps(v0.vec0, temp), _mm_div_ps(v0.vec1, temp));
		#elif TS_NEON
			::float32x4_t temp = vdupq_n_f32(v1);
			return float32x8_t(vdivq_f32(v0.vec0, temp), vdivq_f32(v0.vec1, temp));
		#else
			return float32x8_t(v0.x0 / v1, v0.y0 / v1, v0.z0 / v1, v0.w0 / v1, v0.x1 / v1, v0.y1 / v1, v0.z1 / v1, v0.w1 / v1);
		#endif
	}
	TS_INLINE float32x8_t operator+(const float32x8_t &v0, float32_t v1) {
		#if TS_AVX >= 1
			return float32x8_t(_mm256_add_ps(v0.vec, _mm256_set1_ps(v1)));
		#elif TS_SSE >= 1
			__m128 temp = _mm_set1_ps(v1);
			return float32x8_t(_mm_add_ps(v0.vec0, temp), _mm_add_ps(v0.vec1, temp));
		#elif TS_NEON
			::float32x4_t temp = vdupq_n_f32(v1);
			return float32x8_t(vaddq_f32(v0.vec0, temp), vaddq_f32(v0.vec1, temp));
		#else
			return float32x8_t(v0.x0 + v1, v0.y0 + v1, v0.z0 + v1, v0.w0 + v1, v0.x1 + v1, v0.y1 + v1, v0.z1 + v1, v0.w1 + v1);
		#endif
	}
	TS_INLINE float32x8_t operator-(const float32x8_t &v0, float32_t v1) {
		#if TS_AVX >= 1
			return float32x8_t(_mm256_sub_ps(v0.vec, _mm256_set1_ps(v1)));
		#elif TS_SSE >= 1
			__m128 temp = _mm_set1_ps(v1);
			return float32x8_t(_mm_sub_ps(v0.vec0, temp), _mm_sub_ps(v0.vec1, temp));
		#elif TS_NEON
			::float32x4_t temp = vdupq_n_f32(v1);
			return float32x8_t(vsubq_f32(v0.vec0, temp), vsubq_f32(v0.vec1, temp));
		#else
			return float32x8_t(v0.x0 - v1, v0.y0 - v1, v0.z0 - v1, v0.w0 - v1, v0.x1 - v1, v0.y1 - v1, v0.z1 - v1, v0.w1 - v1);
		#endif
	}
	
	/// vector to vector operators
	TS_INLINE float32x8_t operator*(const float32x8_t &v0, const float32x8_t &v1) {
		#if TS_AVX >= 1
			return float32x8_t(_mm256_mul_ps(v0.vec, v1.vec));
		#elif TS_SSE >= 1
			return float32x8_t(_mm_mul_ps(v0.vec0, v1.vec0), _mm_mul_ps(v0.vec1, v1.vec1));
		#elif TS_NEON
			return float32x8_t(vmulq_f32(v0.vec0, v1.vec0), vmulq_f32(v0.vec1, v1.vec1));
		#else
			return float32x8_t(v0.x0 * v1.x0, v0.y0 * v1.y0, v0.z0 * v1.z0, v0.w0 * v1.w0, v0.x1 * v1.x1, v0.y1 * v1.y1, v0.z1 * v1.z1, v0.w1 * v1.w1);
		#endif
	}
	TS_INLINE float32x8_t operator/(const float32x8_t &v0, const float32x8_t &v1) {
		#if TS_AVX >= 1
			return float32x8_t(_mm256_div_ps(v0.vec, v1.vec));
		#elif TS_SSE >= 1
			return float32x8_t(_mm_div_ps(v0.vec0, v1.vec0), _mm_div_ps(v0.vec1, v1.vec1));
		#elif TS_NEON
			return float32x8_t(vdivq_f32(v0.vec0, v1.vec0), vdivq_f32(v0.vec1, v1.vec1));
		#else
			return float32x8_t(v0.x0 / v1.x0, v0.y0 / v1.y0, v0.z0 / v1.z0, v0.w0 / v1.w0, v0.x1 / v1.x1, v0.y1 / v1.y1, v0.z1 / v1.z1, v0.w1 / v1.w1);
		#endif
	}
	TS_INLINE float32x8_t operator+(const float32x8_t &v0, const float32x8_t &v1) {
		#if TS_AVX >= 1
			return float32x8_t(_mm256_add_ps(v0.vec, v1.vec));
		#elif TS_SSE >= 1
			return float32x8_t(_mm_add_ps(v0.vec0, v1.vec0), _mm_add_ps(v0.vec1, v1.vec1));
		#elif TS_NEON
			return float32x8_t(vaddq_f32(v0.vec0, v1.vec0), vaddq_f32(v0.vec1, v1.vec1));
		#else
			return float32x8_t(v0.x0 + v1.x0, v0.y0 + v1.y0, v0.z0 + v1.z0, v0.w0 + v1.w0, v0.x1 + v1.x1, v0.y1 + v1.y1, v0.z1 + v1.z1, v0.w1 + v1.w1);
		#endif
	}
	TS_INLINE float32x8_t operator-(const float32x8_t &v0, const float32x8_t &v1) {
		#if TS_AVX >= 1
			return float32x8_t(_mm256_sub_ps(v0.vec, v1.vec));
		#elif TS_SSE >= 1
			return float32x8_t(_mm_sub_ps(v0.vec0, v1.vec0), _mm_sub_ps(v0.vec1, v1.vec1));
		#elif TS_NEON
			return float32x8_t(vsubq_f32(v0.vec0, v1.vec0), vsubq_f32(v0.vec1, v1.vec1));
		#else
			return float32x8_t(v0.x0 - v1.x0, v0.y0 - v1.y0, v0.z0 - v1.z0, v0.w0 - v1.w0, v0.x1 - v1.x1, v0.y1 - v1.y1, v0.z1 - v1.z1, v0.w1 - v1.w1);
		#endif
	}
	
	/// comparison operators
	TS_INLINE uint32_t operator<(const float32x8_t &v0, const float32x8_t &v1) {
		#if TS_AVX >= 1
			return _mm256_movemask_ps(_mm256_cmp_ps(v0.vec, v1.vec, _CMP_LT_OQ));
		#elif TS_SSE >= 1
			return _mm_movemask_ps(_mm_cmplt_ps(v0.vec0, v1.vec0)) | (_mm_movemask_ps(_mm_cmplt_ps(v0.vec1, v1.vec1)) << 4);
		#elif TS_NEON
			return vmaskq_u32(vcltq_f32(v0.vec0, v1.vec0)) | (vmaskq_u32(vcltq_f32(v0.vec1, v1.vec1)) << 4);
		#else
			return ((uint32_t)(v0.x0 < v1.x0) << 0) | ((uint32_t)(v0.y0 < v1.y0) << 1) | ((uint32_t)(v0.z0 < v1.z0) << 2) | ((uint32_t)(v0.w0 < v1.w0) << 3) | ((uint32_t)(v0.x1 < v1.x1) << 4) | ((uint32_t)(v0.y1 < v1.y1) << 5) | ((uint32_t)(v0.z1 < v1.z1) << 6) | ((uint32_t)(v0.w1 < v1.w1) << 7);
		#endif
	}
	TS_INLINE uint32_t operator>(const float32x8_t &v0, const float32x8_t &v1) {
		#if TS_AVX >= 1
			return _mm256_movemask_ps(_mm256_cmp_ps(v0.vec, v1.vec, _CMP_GT_OQ));
		#elif TS_SSE >= 1
			return _mm_movemask_ps(_mm_cmpgt_ps(v0.vec0, v1.vec0)) | (_mm_movemask_ps(_mm_cmpgt_ps(v0.vec1, v1.vec1)) << 4);
		#elif TS_NEON
			return vmaskq_u32(vcgtq_f32(v0.vec0, v1.vec0)) | (vmaskq_u32(vcgtq_f32(v0.vec1, v1.vec1)) << 4);
		#else
			return ((uint32_t)(v0.x0 > v1.x0) << 0) | ((uint32_t)(v0.y0 > v1.y0) << 1) | ((uint32_t)(v0.z0 > v1.z0) << 2) | ((uint32_t)(v0.w0 > v1.w0) << 3) | ((uint32_t)(v0.x1 > v1.x1) << 4) | ((uint32_t)(v0.y1 > v1.y1) << 5) | ((uint32_t)(v0.z1 > v1.z1) << 6) | ((uint32_t)(v0.w1 > v1.w1) << 7);
		#endif
	}
	TS_INLINE uint32_t operator<=(const float32x8_t &v0, const float32x8_t &v1) {
		#if TS_AVX >= 1
			return _mm256_movemask_ps(_mm256_cmp_ps(v0.vec, v1.vec, _CMP_LE_OQ));
		#elif TS_SSE >= 1
			return _mm_movemask_ps(_mm_cmple_ps(v0.vec0, v1.vec0)) | (_mm_movemask_ps(_mm_cmple_ps(v0.vec1, v1.vec1)) << 4);
		#elif TS_NEON
			return vmaskq_u32(vcleq_f32(v0.vec0, v1.vec0)) | (vmaskq_u32(vcleq_f32(v0.vec1, v1.vec1)) << 4);
		#else
			return ((uint32_t)(v0.x0 <= v1.x0) << 0) | ((uint32_t)(v0.y0 <= v1.y0) << 1) | ((uint32_t)(v0.z0 <= v1.z0) << 2) | ((uint32_t)(v0.w0 <= v1.w0) << 3) | ((uint32_t)(v0.x1 <= v1.x1) << 4) | ((uint32_t)(v0.y1 <= v1.y1) << 5) | ((uint32_t)(v0.z1 <= v1.z1) << 6) | ((uint32_t)(v0.w1 <= v1.w1) << 7);
		#endif
	}
	TS_INLINE uint32_t operator>=(const float32x8_t &v0, const float32x8_t &v1) {
		#if TS_AVX >= 1
			return _mm256_movemask_ps(_mm256_cmp_ps(v0.vec, v1.vec, _CMP_GE_OQ));
		#elif TS_SSE >= 1
			return _mm_movemask_ps(_mm_cmpge_ps(v0.vec0, v1.vec0)) | (_mm_movemask_ps(_mm_cmpge_ps(v0.vec1, v1.vec1)) << 4);
		#elif TS_NEON
			return vmaskq_u32(vcgeq_f32(v0.vec0, v1.vec0)) | (vmaskq_u32(vcgeq_f32(v0.vec1, v1.vec1)) << 4);
		#else
			return ((uint32_t)(v0.x0 >= v1.x0) << 0) | ((uint32_t)(v0.y0 >= v1.y0) << 1) | ((uint32_t)(v0.z0 >= v1.z0) << 2) | ((uint32_t)(v0.w0 >= v1.w0) << 3) | ((uint32_t)(v0.x1 >= v1.x1) << 4) | ((uint32_t)(v0.y1 >= v1.y1) << 5) | ((uint32_t)(v0.z1 >= v1.z1) << 6) | ((uint32_t)(v0.w1 >= v1.w1) << 7);
		#endif
	}
	TS_INLINE uint32_t operator==(const float32x8_t &v0, const float32x8_t &v1) {
		#if TS_AVX >= 1
			return _mm256_movemask_ps(_mm256_cmp_ps(v0.vec, v1.vec, _CMP_EQ_OQ));
		#elif TS_SSE >= 1
			return _mm_movemask_ps(_mm_cmpeq_ps(v0.vec0, v1.vec0)) | (_mm_movemask_ps(_mm_cmpeq_ps(v0.vec1, v1.vec1)) << 4);
		#elif TS_NEON
			return vmaskq_u32(vceqq_f32(v0.vec0, v1.vec0)) | (vmaskq_u32(vceqq_f32(v0.vec1, v1.vec1)) << 4);
		#else
			return ((uint32_t)(v0.x0 == v1.x0) << 0) | ((uint32_t)(v0.y0 == v1.y0) << 1) | ((uint32_t)(v0.z0 == v1.z0) << 2) | ((uint32_t)(v0.w0 == v1.w0) << 3) | ((uint32_t)(v0.x1 == v1.x1) << 4) | ((uint32_t)(v0.y1 == v1.y1) << 5) | ((uint32_t)(v0.z1 == v1.z1) << 6) | ((uint32_t)(v0.w1 == v1.w1) << 7);
		#endif
	}
	TS_INLINE uint32_t operator!=(const float32x8_t &v0, const float32x8_t &v1) {
		#if TS_AVX >= 1
			return _mm256_movemask_ps(_mm256_cmp_ps(v0.vec, v1.vec, _CMP_NEQ_OQ));
		#elif TS_SSE >= 1
			return _mm_movemask_ps(_mm_cmpneq_ps(v0.vec0, v1.vec0)) | (_mm_movemask_ps(_mm_cmpneq_ps(v0.vec1, v1.vec1)) << 4);
		#elif TS_NEON
			return ~(vmaskq_u32(vceqq_f32(v0.vec0, v1.vec0)) | (vmaskq_u32(vceqq_f32(v0.vec1, v1.vec1)) << 4)) & 0xff;
		#else
			return ((uint32_t)(v0.x0 != v1.x0) << 0) | ((uint32_t)(v0.y0 != v1.y0) << 1) | ((uint32_t)(v0.z0 != v1.z0) << 2) | ((uint32_t)(v0.w0 != v1.w0) << 3) | ((uint32_t)(v0.x1 != v1.x1) << 4) | ((uint32_t)(v0.y1 != v1.y1) << 5) | ((uint32_t)(v0.z1 != v1.z1) << 6) | ((uint32_t)(v0.w1 != v1.w1) << 7);
		#endif
	}
	
	/// min/max functions
	TS_INLINE float32x8_t min(const float32x8_t &v0, const float32x8_t &v1) {
		#if TS_AVX >= 1
			return float32x8_t(_mm256_min_ps(v0.vec, v1.vec));
		#elif TS_SSE >= 1
			return float32x8_t(_mm_min_ps(v0.vec0, v1.vec0), _mm_min_ps(v0.vec1, v1.vec1));
		#elif TS_NEON
			return float32x8_t(vminq_f32(v0.vec0, v1.vec0), vminq_f32(v0.vec1, v1.vec1));
		#else
			return float32x8_t(min(v0.x0, v1.x0), min(v0.y0, v1.y0), min(v0.z0, v1.z0), min(v0.w0, v1.w0), min(v0.x1, v1.x1), min(v0.y1, v1.y1), min(v0.z1, v1.z1), min(v0.w1, v1.w1));
		#endif
	}
	TS_INLINE float32x8_t max(const float32x8_t &v0, const float32x8_t &v1) {
		#if TS_AVX >= 1
			return float32x8_t(_mm256_max_ps(v0.vec, v1.vec));
		#elif TS_SSE >= 1
			return float32x8_t(_mm_max_ps(v0.vec0, v1.vec0), _mm_max_ps(v0.vec1, v1.vec1));
		#elif TS_NEON
			return float32x8_t(vmaxq_f32(v0.vec0, v1.vec0), vmaxq_f32(v0.vec1, v1.vec1));
		#else
			return float32x8_t(max(v0.x0, v1.x0), max(v0.y0, v1.y0), max(v0.z0, v1.z0), max(v0.w0, v1.w0), max(v0.x1, v1.x1), max(v0.y1, v1.y1), max(v0.z1, v1.z1), max(v0.w1, v1.w1));
		#endif
	}
	
	/// range functions
	TS_INLINE float32x8_t saturate(const float32x8_t &v) {
		return min(max(v, float32x8_t(0.0f)), float32x8_t(1.0f));
	}
	TS_INLINE float32x8_t clamp(const float32x8_t &v, float32_t v0, const float32_t v1) {
		return min(max(v, float32x8_t(v0)), float32x8_t(v1));
	}
	TS_INLINE float32x8_t clamp(const float32x8_t &v, const float32x8_t &v0, const float32x8_t &v1) {
		return min(max(v, v0), v1);
	}
	
	/// select functions
	TS_INLINE float32x8_t select(const float32x8_t &v0, const float32x8_t &v1, const float32x8_t &s) {
		#if TS_AVX >= 1
			return float32x8_t(_mm256_blendv_ps(v0.vec, v1.vec, s.vec));
		#elif TS_SSE >= 2
			return float32x8_t(_mm_xor_ps(v0.vec0, _mm_and_ps(_mm_xor_ps(v0.vec0, v1.vec0), _mm_cmplt_ps(s.vec0, _mm_setzero_ps()))), _mm_xor_ps(v0.vec1, _mm_and_ps(_mm_xor_ps(v0.vec1, v1.vec1), _mm_cmplt_ps(s.vec1, _mm_setzero_ps()))));
		#elif TS_NEON
			return float32x8_t(vbslq_f32(vcgeq_f32(s.vec0, vdupq_n_f32(0.0f)), v0.vec0, v1.vec0), vbslq_f32(vcgeq_f32(s.vec1, vdupq_n_f32(0.0f)), v0.vec1, v1.vec1));
		#else
			return float32x8_t(select(v0.x0, v1.x0, s.x0), select(v0.y0, v1.y0, s.y0), select(v0.z0, v1.z0, s.z0), select(v0.w0, v1.w0, s.w0), select(v0.x1, v1.x1, s.x1), select(v0.y1, v1.y1, s.y1), select(v0.z1, v1.z1, s.z1), select(v0.w1, v1.w1, s.w1));
		#endif
	}
	TS_INLINE float32x8_t select(const float32x8_t &v0, const float32x8_t &v1, float32_t s) {
		return select(v0, v1, float32x8_t(s));
	}
	
	/// math functions
	TS_INLINE float32x8_t rcp(const float32x8_t &v) {
		#if TS_AVX >= 1
			return float32x8_t(_mm256_rcp_ps_nr(v.vec));
		#elif TS_SSE >= 1
			return float32x8_t(_mm_rcp_ps_nr(v.vec0), _mm_rcp_ps_nr(v.vec1));
		#elif TS_NEON
			return float32x8_t(vrcpq_f32(v.vec0), vrcpq_f32(v.vec1));
		#else
			return float32x8_t(rcp(v.x0), rcp(v.y0), rcp(v.z0), rcp(v.w0), rcp(v.x1), rcp(v.y1), rcp(v.z1), rcp(v.w1));
		#endif
	}
	TS_INLINE float32x8_t sqrt(const float32x8_t &v) {
		#if TS_AVX >= 1
			return float32x8_t(_mm256_sqrt_ps(v.vec));
		#elif TS_SSE >= 1
			return float32x8_t(_mm_sqrt_ps(v.vec0), _mm_sqrt_ps(v.vec1));
		#elif TS_NEON
			return float32x8_t(vsqrtq_f32(v.vec0), vsqrtq_f32(v.vec1));
		#else
			return float32x8_t(sqrt(v.x0), sqrt(v.y0), sqrt(v.z0), sqrt(v.w0), sqrt(v.x1), sqrt(v.y1), sqrt(v.z1), sqrt(v.w1));
		#endif
	}
	TS_INLINE float32x8_t rsqrt(const float32x8_t &v) {
		#if TS_AVX >= 1
			return float32x8_t(_mm256_rsqrt_ps_nr(v.vec));
		#elif TS_SSE >= 1
			return float32x8_t(_mm_rsqrt_ps_nr(v.vec0), _mm_rsqrt_ps_nr(v.vec1));
		#elif TS_NEON
			return float32x8_t(vrsqrtq_f32(v.vec0), vrsqrtq_f32(v.vec1));
		#else
			return float32x8_t(rsqrt(v.x0), rsqrt(v.y0), rsqrt(v.z0), rsqrt(v.w0), rsqrt(v.x1), rsqrt(v.y1), rsqrt(v.z1), rsqrt(v.w1));
		#endif
	}
	TS_INLINE float32x8_t abs(const float32x8_t &v) {
		#if TS_AVX >= 1
			return float32x8_t(_mm256_and_ps(v.vec, _mm256_set1_ps(f32u32(~Signf32).f)));
		#elif TS_SSE >= 1
			__m128 temp = _mm_set1_ps(f32u32(~Signf32).f);
			return float32x8_t(_mm_and_ps(v.vec0, temp), _mm_and_ps(v.vec1, temp));
		#elif TS_NEON
			return float32x8_t(vabsq_f32(v.vec0), vabsq_f32(v.vec1));
		#else
			return float32x8_t(abs(v.x0), abs(v.y0), abs(v.z0), abs(v.w0), abs(v.x1), abs(v.y1), abs(v.z1), abs(v.w1));
		#endif
	}
	TS_INLINE float32x8_t ceil(const float32x8_t &v) {
		#if TS_AVX >= 1
			float32x8_t f = float32x8_t(_mm256_cvtepi32_ps(_mm256_cvtps_epi32(v.vec)));
			return f + float32x8_t(_mm256_and_ps(_mm256_set1_ps(1.0f), _mm256_cmp_ps(v.vec, f.vec, _CMP_GT_OQ)));
		#elif TS_SSE >= 2
			__m128 temp = _mm_set1_ps(1.0f);
			float32x8_t f = float32x8_t(_mm_cvtepi32_ps(_mm_cvtps_epi32(v.vec0)), _mm_cvtepi32_ps(_mm_cvtps_epi32(v.vec1)));
			return f + float32x8_t(_mm_and_ps(temp, _mm_cmpgt_ps(v.vec0, f.vec0)), _mm_and_ps(temp, _mm_cmpgt_ps(v.vec1, f.vec1)));
		#elif TS_NEON
			float32x8_t f = float32x8_t(vcvtq_f32_s32(vcvtq_s32_f32(v.vec0)), vcvtq_f32_s32(vcvtq_s32_f32(v.vec1)));
			return f + float32x8_t(vbslq_f32(vcgtq_f32(v.vec0, f.vec0), vdupq_n_f32(1.0f), vdupq_n_f32(0.0f)), vbslq_f32(vcgtq_f32(v.vec1, f.vec1), vdupq_n_f32(1.0f), vdupq_n_f32(0.0f)));
		#else
			return float32x8_t(ceil(v.x0), ceil(v.y0), ceil(v.z0), ceil(v.w0), ceil(v.x1), ceil(v.y1), ceil(v.z1), ceil(v.w1));
		#endif
	}
	TS_INLINE float32x8_t floor(const float32x8_t &v) {
		#if TS_AVX >= 1
			float32x8_t f = float32x8_t(_mm256_cvtepi32_ps(_mm256_cvtps_epi32(v.vec)));
			return f - float32x8_t(_mm256_and_ps(_mm256_set1_ps(1.0f), _mm256_cmp_ps(v.vec, f.vec, _CMP_LT_OQ)));
		#elif TS_SSE >= 2
			__m128 temp = _mm_set1_ps(1.0f);
			float32x8_t f = float32x8_t(_mm_cvtepi32_ps(_mm_cvtps_epi32(v.vec0)), _mm_cvtepi32_ps(_mm_cvtps_epi32(v.vec1)));
			return f - float32x8_t(_mm_and_ps(temp, _mm_cmplt_ps(v.vec0, f.vec0)), _mm_and_ps(temp, _mm_cmplt_ps(v.vec1, f.vec1)));
		#elif TS_NEON
			float32x8_t f = float32x8_t(vcvtq_f32_s32(vcvtq_s32_f32(v.vec0)), vcvtq_f32_s32(vcvtq_s32_f32(v.vec1)));
			return f - float32x8_t(vbslq_f32(vcltq_f32(v.vec0, f.vec0), vdupq_n_f32(1.0f), vdupq_n_f32(0.0f)), vbslq_f32(vcltq_f32(v.vec1, f.vec1), vdupq_n_f32(1.0f), vdupq_n_f32(0.0f)));
		#else
			return float32x8_t(floor(v.x0), floor(v.y0), floor(v.z0), floor(v.w0), floor(v.x1), floor(v.y1), floor(v.z1), floor(v.w1));
		#endif
	}
	
	/// fast math functions
	TS_INLINE float32x8_t rsqrtFast(const float32x8_t &v) {
		float32x8_t r = (uint32x8_t(0x5f3759dfu) - (v.asu32x8() >> 1)).asf32x8();
		return (float32x8_t(1.5f) - r * r * v * 0.5f) * r;
	}
	TS_INLINE float32x8_t powFast(const float32x8_t &v, const float32x8_t &p) {
		int32x8_t i = max(v, float32x8_t(1e-16f)).asi32x8() - 0x3f79e59d;
		i = int32x8_t(float32x8_t(i) * p) + 0x3f79e59d;
		return int32x8_t(i).asf32x8();
	}
	TS_INLINE float32x8_t powFast(const float32x8_t &v, float32_t p) {
		return powFast(v, float32x8_t(p));
	}
	
	/// vector functions
	TS_INLINE float32x8_t lerp(const float32x8_t &v0, const float32x8_t &v1, float32_t k) {
		#if TS_AVX >= 1
			return float32x8_t(_mm256_add_ps(v0.vec, _mm256_mul_ps(_mm256_sub_ps(v1.vec, v0.vec), _mm256_set1_ps(k))));
		#elif TS_SSE >= 1
			__m128 temp = _mm_set1_ps(k);
			return float32x8_t(_mm_add_ps(v0.vec0, _mm_mul_ps(_mm_sub_ps(v1.vec0, v0.vec0), temp)), _mm_add_ps(v0.vec1, _mm_mul_ps(_mm_sub_ps(v1.vec1, v0.vec1), temp)));
		#elif TS_NEON
			::float32x4_t temp = vdupq_n_f32(k);
			return float32x8_t(vaddq_f32(v0.vec0, vmulq_f32(vsubq_f32(v1.vec0, v0.vec0), temp)), vaddq_f32(v0.vec1, vmulq_f32(vsubq_f32(v1.vec1, v0.vec1), temp)));
		#else
			return float32x8_t(lerp(v0.x0, v1.x0, k), lerp(v0.y0, v1.y0, k), lerp(v0.z0, v1.z0, k), lerp(v0.w0, v1.w0, k), lerp(v0.x1, v1.x1, k), lerp(v0.y1, v1.y1, k), lerp(v0.z1, v1.z1, k), lerp(v0.w1, v1.w1, k));
		#endif
	}
	
	/*****************************************************************************\
	 *
	 * float64x2_t
	 *
	\*****************************************************************************/
	
	/**
	 * Vector of two float64_t components
	 */
	struct TS_ALIGNAS16 float64x2_t {
		
		float64x2_t() { }
		explicit float64x2_t(const float64_t *v) { set(v); }
		#if TS_SSE >= 2
			float64x2_t(const float64x2_t &v) : vec(v.vec) { }
			explicit float64x2_t(__m128d v) : vec(v) { }
			explicit float64x2_t(float64_t v) : vec(_mm_set1_pd(v)) { }
			float64x2_t(float64_t x, float64_t y) : vec(_mm_setr_pd(x, y)) { }
		#else
			explicit float64x2_t(float64_t v) : x(v), y(v) { }
			float64x2_t(float64_t x, float64_t y) : x(x), y(y) { }
		#endif
		
		/// update vector data
		TS_INLINE void set(const float64x2_t &v) {
			#if TS_SSE >= 2
				vec = v.vec;
			#else
				x = v.x; y = v.y;
			#endif
		}
		TS_INLINE void set(float64_t X, float64_t Y) {
			#if TS_SSE >= 2
				vec = _mm_setr_pd(X, Y);
			#else
				x = X; y = Y;
			#endif
		}
		TS_INLINE void set(const float64_t *TS_RESTRICT v) {
			#if TS_SSE >= 2
				vec = _mm_load_pd(v);
			#else
				x = v[0]; y = v[1];
			#endif
		}
		TS_INLINE void get(float64_t *TS_RESTRICT v) const {
			#if TS_SSE >= 2
				_mm_stream_pd(v, vec);
			#else
				v[0] = x; v[1] = y;
			#endif
		}
		template <uint32_t Index> TS_INLINE void set(float64_t V) {
			#if TS_SSE >= 4 && TS_X64
				vec = _mm_castsi128_pd(_mm_insert_epi64(_mm_castpd_si128(vec), (int64_t)f64u64(V).u, Index));
			#else
				v[Index] = V;
			#endif
		}
		template <uint32_t Index> TS_INLINE float64_t get() const {
			#if TS_SSE >= 4 && TS_X64
				return f64u64((uint64_t)_mm_extract_epi64(_mm_castpd_si128(vec), Index)).f;
			#else
				return v[Index];
			#endif
		}
		template <uint64_t Index> TS_INLINE float64x2_t get2() const {
			#if TS_SSE >= 2
				return float64x2_t(_mm_shuffle_pd(vec, vec, (Index << 1) | Index));
			#else
				return float64x2_t(v[Index]);
			#endif
		}
		
		/// vector to scalar operators
		TS_INLINE float64x2_t &operator*=(float64_t v) {
			#if TS_SSE >= 2
				vec = _mm_mul_pd(vec, _mm_set1_pd(v));
			#else
				x *= v; y *= v;
			#endif
			return *this;
		}
		TS_INLINE float64x2_t &operator/=(float64_t v) {
			#if TS_SSE >= 2
				vec = _mm_div_pd(vec, _mm_set1_pd(v));
			#else
				x /= v; y /= v;
			#endif
			return *this;
		}
		TS_INLINE float64x2_t &operator+=(float64_t v) {
			#if TS_SSE >= 2
				vec = _mm_add_pd(vec, _mm_set1_pd(v));
			#else
				x += v; y += v;
			#endif
			return *this;
		}
		TS_INLINE float64x2_t &operator-=(float64_t v) {
			#if TS_SSE >= 2
				vec = _mm_sub_pd(vec, _mm_set1_pd(v));
			#else
				x -= v; y -= v;
			#endif
			return *this;
		}
		
		/// vector to vector operators
		TS_INLINE float64x2_t &operator*=(const float64x2_t &v) {
			#if TS_SSE >= 2
				vec = _mm_mul_pd(vec, v.vec);
			#else
				x *= v.x; y *= v.y;
			#endif
			return *this;
		}
		TS_INLINE float64x2_t &operator/=(const float64x2_t &v) {
			#if TS_SSE >= 2
				vec = _mm_div_pd(vec, v.vec);
			#else
				x /= v.x; y /= v.y;
			#endif
			return *this;
		}
		TS_INLINE float64x2_t &operator+=(const float64x2_t &v) {
			#if TS_SSE >= 2
				vec = _mm_add_pd(vec, v.vec);
			#else
				x += v.x; y += v.y;
			#endif
			return *this;
		}
		TS_INLINE float64x2_t &operator-=(const float64x2_t &v) {
			#if TS_SSE >= 2
				vec = _mm_sub_pd(vec, v.vec);
			#else
				x -= v.x; y -= v.y;
			#endif
			return *this;
		}
		
		/// swizzle vector
		TS_INLINE float64x2_t yx() const {
			#if TS_SSE >= 2
				return float64x2_t(_mm_swizzle_pd(vec, vec, Y, X));
			#else
				return float64x2_t(y, x);
			#endif
		}
		
		/// sum vector components
		TS_INLINE float64_t sum() const {
			#if TS_SSE >= 4
				return _mm_cvtsd_f64(_mm_hadd_pd(vec, vec));
			#elif TS_SSE >= 2
				return _mm_cvtsd_f64(_mm_add_pd(vec, _mm_swizzle_pd(vec, vec, Y, Z)));
			#else
				return x + y;
			#endif
		}
		
		enum {
			Size = 2,
		};
		
		union {
			struct {
				float64_t x, y;
			};
			float64_t v[Size];
			#if TS_SSE >= 2
				__m128d vec;
			#endif
		};
	};
	
	/// unary operators
	TS_INLINE float64x2_t operator-(const float64x2_t &v) {
		#if TS_SSE >= 2
			return float64x2_t(_mm_xor_pd(v.vec, _mm_set1_pd(f64u64(Signf64).f)));
		#else
			return float64x2_t(-v.x, -v.y);
		#endif
	}
	
	/// vector to scalar operators
	TS_INLINE float64x2_t operator*(const float64x2_t &v0, float64_t v1) {
		#if TS_SSE >= 2
			return float64x2_t(_mm_mul_pd(v0.vec, _mm_set1_pd(v1)));
		#else
			return float64x2_t(v0.x * v1, v0.y * v1);
		#endif
	}
	TS_INLINE float64x2_t operator/(const float64x2_t &v0, float64_t v1) {
		#if TS_SSE >= 2
			return float64x2_t(_mm_div_pd(v0.vec, _mm_set1_pd(v1)));
		#else
			return float64x2_t(v0.x / v1, v0.y / v1);
		#endif
	}
	TS_INLINE float64x2_t operator+(const float64x2_t &v0, float64_t v1) {
		#if TS_SSE >= 2
			return float64x2_t(_mm_add_pd(v0.vec, _mm_set1_pd(v1)));
		#else
			return float64x2_t(v0.x + v1, v0.y + v1);
		#endif
	}
	TS_INLINE float64x2_t operator-(const float64x2_t &v0, float64_t v1) {
		#if TS_SSE >= 2
			return float64x2_t(_mm_sub_pd(v0.vec, _mm_set1_pd(v1)));
		#else
			return float64x2_t(v0.x - v1, v0.y - v1);
		#endif
	}
	
	/// vector to vector operators
	TS_INLINE float64x2_t operator*(const float64x2_t &v0, const float64x2_t &v1) {
		#if TS_SSE >= 2
			return float64x2_t(_mm_mul_pd(v0.vec, v1.vec));
		#else
			return float64x2_t(v0.x * v1.x, v0.y * v1.y);
		#endif
	}
	TS_INLINE float64x2_t operator/(const float64x2_t &v0, const float64x2_t &v1) {
		#if TS_SSE >= 2
			return float64x2_t(_mm_div_pd(v0.vec, v1.vec));
		#else
			return float64x2_t(v0.x / v1.x, v0.y / v1.y);
		#endif
	}
	TS_INLINE float64x2_t operator+(const float64x2_t &v0, const float64x2_t &v1) {
		#if TS_SSE >= 2
			return float64x2_t(_mm_add_pd(v0.vec, v1.vec));
		#else
			return float64x2_t(v0.x + v1.x, v0.y + v1.y);
		#endif
	}
	TS_INLINE float64x2_t operator-(const float64x2_t &v0, const float64x2_t &v1) {
		#if TS_SSE >= 2
			return float64x2_t(_mm_sub_pd(v0.vec, v1.vec));
		#else
			return float64x2_t(v0.x - v1.x, v0.y - v1.y);
		#endif
	}
	
	/// comparison operators
	TS_INLINE uint32_t operator<(const float64x2_t &v0, const float64x2_t &v1) {
		#if TS_SSE >= 2
			return _mm_movemask_pd(_mm_cmplt_pd(v0.vec, v1.vec));
		#else
			return ((uint32_t)(v0.x < v1.x) << 0) | ((uint32_t)(v0.y < v1.y) << 1);
		#endif
	}
	TS_INLINE uint32_t operator>(const float64x2_t &v0, const float64x2_t &v1) {
		#if TS_SSE >= 2
			return _mm_movemask_pd(_mm_cmpgt_pd(v0.vec, v1.vec));
		#else
			return ((uint32_t)(v0.x > v1.x) << 0) | ((uint32_t)(v0.y > v1.y) << 1);
		#endif
	}
	TS_INLINE uint32_t operator<=(const float64x2_t &v0, const float64x2_t &v1) {
		#if TS_SSE >= 2
			return _mm_movemask_pd(_mm_cmple_pd(v0.vec, v1.vec));
		#else
			return ((uint32_t)(v0.x <= v1.x) << 0) | ((uint32_t)(v0.y <= v1.y) << 1);
		#endif
	}
	TS_INLINE uint32_t operator>=(const float64x2_t &v0, const float64x2_t &v1) {
		#if TS_SSE >= 2
			return _mm_movemask_pd(_mm_cmpge_pd(v0.vec, v1.vec));
		#else
			return ((uint32_t)(v0.x >= v1.x) << 0) | ((uint32_t)(v0.y >= v1.y) << 1);
		#endif
	}
	TS_INLINE uint32_t operator==(const float64x2_t &v0, const float64x2_t &v1) {
		#if TS_SSE >= 2
			return _mm_movemask_pd(_mm_cmpeq_pd(v0.vec, v1.vec));
		#else
			return ((uint32_t)(v0.x == v1.x) << 0) | ((uint32_t)(v0.y == v1.y) << 1);
		#endif
	}
	TS_INLINE uint32_t operator!=(const float64x2_t &v0, const float64x2_t &v1) {
		#if TS_SSE >= 2
			return _mm_movemask_pd(_mm_cmpneq_pd(v0.vec, v1.vec));
		#else
			return ((uint32_t)(v0.x != v1.x) << 0) | ((uint32_t)(v0.y != v1.y) << 1);
		#endif
	}
	
	/// min/max functions
	TS_INLINE float64x2_t min(const float64x2_t &v0, const float64x2_t &v1) {
		#if TS_SSE >= 2
			return float64x2_t(_mm_min_pd(v0.vec, v1.vec));
		#else
			return float64x2_t(min(v0.x, v1.x), min(v0.y, v1.y));
		#endif
	}
	TS_INLINE float64x2_t max(const float64x2_t &v0, const float64x2_t &v1) {
		#if TS_SSE >= 2
			return float64x2_t(_mm_max_pd(v0.vec, v1.vec));
		#else
			return float64x2_t(max(v0.x, v1.x), max(v0.y, v1.y));
		#endif
	}
	
	/// range functions
	TS_INLINE float64x2_t saturate(const float64x2_t &v) {
		return min(max(v, float64x2_t(0.0)), float64x2_t(1.0));
	}
	TS_INLINE float64x2_t clamp(const float64x2_t &v, float64_t v0, float64_t v1) {
		return min(max(v, float64x2_t(v0)), float64x2_t(v1));
	}
	TS_INLINE float64x2_t clamp(const float64x2_t &v, const float64x2_t &v0, const float64x2_t &v1) {
		return min(max(v, v0), v1);
	}
	
	/// select functions
	TS_INLINE float64x2_t select(const float64x2_t &v0, const float64x2_t &v1, const float64x2_t &s) {
		#if TS_AVX >= 1
			return float64x2_t(_mm_blendv_pd(v0.vec, v1.vec, s.vec));
		#elif TS_SSE >= 2
			return float64x2_t(_mm_xor_pd(v0.vec, _mm_and_pd(_mm_xor_pd(v0.vec, v1.vec), _mm_cmplt_pd(s.vec, _mm_setzero_pd()))));
		#else
			return float64x2_t(select(v0.x, v1.x, s.x), select(v0.y, v1.y, s.y));
		#endif
	}
	TS_INLINE float64x2_t select(const float64x2_t &v0, const float64x2_t &v1, float64_t s) {
		return select(v0, v1, float64x2_t(s));
	}
	
	/// math functions
	TS_INLINE float64x2_t sqrt(const float64x2_t &v) {
		#if TS_SSE >= 2
			return float64x2_t(_mm_sqrt_pd(v.vec));
		#else
			return float64x2_t(sqrt(v.x), sqrt(v.y));
		#endif
	}
	
	/// vector functions
	TS_INLINE float64x2_t lerp(const float64x2_t &v0, const float64x2_t &v1, float64_t k) {
		#if TS_SSE >= 2
			return float64x2_t(_mm_add_pd(v0.vec, _mm_mul_pd(_mm_sub_pd(v1.vec, v0.vec), _mm_set1_pd(k))));
		#else
			return float64x2_t(lerp(v0.x, v1.x, k), lerp(v0.y, v1.y, k));
		#endif
	}
	
	/*****************************************************************************\
	 *
	 * float64x4_t
	 *
	\*****************************************************************************/
	
	/**
	 * Vector of four float64_t components
	 */
	struct TS_ALIGNAS32 float64x4_t {
		
		float64x4_t() { }
		explicit float64x4_t(const float64_t *v) { set(v); }
		float64x4_t(const float64_t *v, float64_t w) { set(v, w); }
		#if TS_AVX >= 1
			float64x4_t(const float64x4_t &v) : vec(v.vec) { }
			explicit float64x4_t(__m256d v) : vec(v) { }
			explicit float64x4_t(float64_t v) : vec(_mm256_set1_pd(v)) { }
			float64x4_t(__m128d v0, __m128d v1) : vec(_mm256_setr_m128d(v0, v1)) { }
			explicit float64x4_t(const int32x4_t &v) : vec(_mm256_cvtepi32_pd(v.vec)) { }
			explicit float64x4_t(const uint32x4_t &v) : vec(_mm256_cvtepi32_pd(v.vec)) { }
			explicit float64x4_t(const float32x4_t &v) : vec(_mm256_cvtps_pd(v.vec)) { }
			float64x4_t(const float64x2_t &v0, const float64x2_t &v1) : vec(_mm256_setr_m128d(v0.vec, v1.vec)) { }
			float64x4_t(float64_t x, float64_t y, float64_t z, float64_t w = 0.0) : vec(_mm256_setr_pd(x, y, z, w)) { }
		#elif TS_SSE >= 2
			float64x4_t(const float64x4_t &v) : vec0(v.vec0), vec1(v.vec1) { }
			float64x4_t(__m128d v0, __m128d v1) : vec0(v0), vec1(v1) { }
			explicit float64x4_t(float64_t v) : vec0(_mm_set1_pd(v)), vec1(_mm_set1_pd(v)) { }
			explicit float64x4_t(const int32x4_t &v) : vec0(_mm_cvtepi32_pd(v.vec)), vec1(_mm_cvtepi32_pd(_mm_swizzle_epi32(v.vec, Z, W, Z, W))) { }
			explicit float64x4_t(const uint32x4_t &v) : vec0(_mm_cvtepi32_pd(v.vec)), vec1(_mm_cvtepi32_pd(_mm_swizzle_epi32(v.vec, Z, W, Z, W))) { }
			explicit float64x4_t(const float32x4_t &v) : vec0(_mm_cvtps_pd(v.vec)), vec1(_mm_cvtps_pd(_mm_swizzle_ps(v.vec, v.vec, Z, W, Z, W))) { }
			float64x4_t(const float64x2_t &v0, const float64x2_t &v1) : vec0(v0.vec), vec1(v1.vec) { }
			float64x4_t(float64_t x, float64_t y, float64_t z, float64_t w = 0.0) : vec0(_mm_setr_pd(x, y)), vec1(_mm_setr_pd(z, w)) { }
		#else
			explicit float64x4_t(float64_t v) : x(v), y(v), z(v), w(v) { }
			explicit float64x4_t(const int32x4_t &v) : x((float64_t)v.x), y((float64_t)v.y), z((float64_t)v.z), w((float64_t)v.w) { }
			explicit float64x4_t(const uint32x4_t &v) : x((float64_t)v.x), y((float64_t)v.y), z((float64_t)v.z), w((float64_t)v.w) { }
			explicit float64x4_t(const float32x4_t &v) : x(v.x), y(v.y), z(v.z), w(v.w) { }
			float64x4_t(const float64x2_t &v0, const float64x2_t &v1) : x(v0.x), y(v0.y), z(v1.x), w(v1.y) { }
			float64x4_t(float64_t x, float64_t y, float64_t z, float64_t w = 0.0) : x(x), y(y), z(z), w(w) { }
		#endif
		
		/// update vector data
		TS_INLINE void set(const float64x4_t &v) {
			#if TS_AVX >= 1
				vec = v.vec;
			#elif TS_SSE >= 2
				vec0 = v.vec0;
				vec1 = v.vec1;
			#else
				x = v.x; y = v.y; z = v.z; w = v.w;
			#endif
		}
		TS_INLINE void set(float64_t X, float64_t Y, float64_t Z, float64_t W) {
			#if TS_AVX >= 1
				vec = _mm256_setr_pd(X, Y, Z, W);
			#elif TS_SSE >= 2
				vec0 = _mm_setr_pd(X, Y);
				vec1 = _mm_setr_pd(Z, W);
			#else
				x = X; y = Y; z = Z; w = W;
			#endif
		}
		TS_INLINE void set(const float64_t *TS_RESTRICT v, float64_t W) {
			#if TS_AVX >= 1
				vec = _mm256_setr_pd(v[0], v[1], v[2], W);
			#elif TS_SSE >= 2
				vec0 = _mm_setr_pd(v[0], v[1]);
				vec1 = _mm_setr_pd(v[2], W);
			#else
				x = v[0]; y = v[1]; z = v[2]; w = W;
			#endif
		}
		TS_INLINE void set(const float64_t *TS_RESTRICT v) {
			#if TS_AVX >= 1
				vec = _mm256_load_pd(v);
			#elif TS_SSE >= 2
				vec0 = _mm_load_pd(v + 0);
				vec1 = _mm_load_pd(v + 2);
			#else
				x = v[0]; y = v[1]; z = v[2]; w = v[3];
			#endif
		}
		TS_INLINE void get(float64_t *TS_RESTRICT v) const {
			#if TS_AVX >= 1
				_mm256_stream_pd(v, vec);
			#elif TS_SSE >= 2
				_mm_stream_pd(v + 0, vec0);
				_mm_stream_pd(v + 2, vec1);
			#else
				v[0] = x; v[1] = y; v[2] = z; v[3] = w;
			#endif
		}
		template <uint32_t Index> TS_INLINE void set(float64_t V) {
			#if TS_AVX >= 1 && TS_X64
				__m128i temp = _mm_insert_epi64(_mm256_extractf128_si256(_mm256_castpd_si256(vec), Index >> 1), (int64_t)f64u64(V).u, Index & 0x01);
				vec = _mm256_castsi256_pd(_mm256_insertf128_si256(_mm256_castpd_si256(vec), temp, Index >> 1));
			#elif TS_SSE >= 4 && TS_X64
				vec[Index >> 1] = _mm_castsi128_pd(_mm_insert_epi64(_mm_castpd_si128(vec[Index >> 1]), (int64_t)f64u64(V).u, Index & 0x01));
			#else
				v[Index] = V;
			#endif
		}
		template <uint32_t Index> TS_INLINE float64_t get() const {
			#if TS_AVX >= 1 && TS_X64
				return f64u64((uint64_t)_mm_extract_epi64(_mm256_extractf128_si256(_mm256_castpd_si256(vec), Index >> 1), Index & 0x01)).f;
			#elif TS_SSE >= 4 && TS_X64
				return f64u64((uint64_t)_mm_extract_epi64(_mm_castpd_si128(vec[Index >> 1]), Index & 0x01)).f;
			#else
				return v[Index];
			#endif
		}
		template <uint64_t Index> TS_INLINE float64x4_t get4() const {
			#if TS_AVX >= 2
				return float64x4_t(_mm256_permute4x64_pd(vec, (Index << 6) | (Index << 4) | (Index << 2) | Index));
			#elif TS_AVX >= 1
				return float64x4_t(_mm256_permute_pd(_mm256_permute2f128_pd(vec, vec, (Index & 0x02) ? 0x11 : 0x00), (Index & 0x01) ? 0x0f : 0x00));
			#elif TS_SSE >= 2
				__m128d temp = _mm_shuffle_pd(vec[Index >> 1], vec[Index >> 1], (Index & 0x01) ? 0x03 : 0x00);
				return float64x4_t(temp, temp);
			#else
				return float64x4_t(v[Index]);
			#endif
		}
		
		/// vector to scalar operators
		TS_INLINE float64x4_t &operator*=(float64_t v) {
			#if TS_AVX >= 1
				vec = _mm256_mul_pd(vec, _mm256_set1_pd(v));
			#elif TS_SSE >= 2
				__m128d temp = _mm_set1_pd(v);
				vec0 = _mm_mul_pd(vec0, temp);
				vec1 = _mm_mul_pd(vec1, temp);
			#else
				x *= v; y *= v; z *= v; w *= v;
			#endif
			return *this;
		}
		TS_INLINE float64x4_t &operator/=(float64_t v) {
			#if TS_AVX >= 1
				vec = _mm256_div_pd(vec, _mm256_set1_pd(v));
			#elif TS_SSE >= 2
				__m128d temp = _mm_set1_pd(v);
				vec0 = _mm_div_pd(vec0, temp);
				vec1 = _mm_div_pd(vec1, temp);
			#else
				x /= v; y /= v; z /= v; w /= v;
			#endif
			return *this;
		}
		TS_INLINE float64x4_t &operator+=(float64_t v) {
			#if TS_AVX >= 1
				vec = _mm256_add_pd(vec, _mm256_set1_pd(v));
			#elif TS_SSE >= 2
				__m128d temp = _mm_set1_pd(v);
				vec0 = _mm_add_pd(vec0, temp);
				vec1 = _mm_add_pd(vec1, temp);
			#else
				x += v; y += v; z += v; w += v;
			#endif
			return *this;
		}
		TS_INLINE float64x4_t &operator-=(float64_t v) {
			#if TS_AVX >= 1
				vec = _mm256_sub_pd(vec, _mm256_set1_pd(v));
			#elif TS_SSE >= 2
				__m128d temp = _mm_set1_pd(v);
				vec0 = _mm_sub_pd(vec0, temp);
				vec1 = _mm_sub_pd(vec1, temp);
			#else
				x -= v; y -= v; z -= v; w -= v;
			#endif
			return *this;
		}
		
		/// vector to vector operators
		TS_INLINE float64x4_t &operator*=(const float64x4_t &v) {
			#if TS_AVX >= 1
				vec = _mm256_mul_pd(vec, v.vec);
			#elif TS_SSE >= 2
				vec0 = _mm_mul_pd(vec0, v.vec0);
				vec1 = _mm_mul_pd(vec1, v.vec1);
			#else
				x *= v.x; y *= v.y; z *= v.z; w *= v.w;
			#endif
			return *this;
		}
		TS_INLINE float64x4_t &operator/=(const float64x4_t &v) {
			#if TS_AVX >= 1
				vec = _mm256_div_pd(vec, v.vec);
			#elif TS_SSE >= 2
				vec0 = _mm_div_pd(vec0, v.vec0);
				vec1 = _mm_div_pd(vec1, v.vec1);
			#else
				x /= v.x; y /= v.y; z /= v.z; w /= v.w;
			#endif
			return *this;
		}
		TS_INLINE float64x4_t &operator+=(const float64x4_t &v) {
			#if TS_AVX >= 1
				vec = _mm256_add_pd(vec, v.vec);
			#elif TS_SSE >= 2
				vec0 = _mm_add_pd(vec0, v.vec0);
				vec1 = _mm_add_pd(vec1, v.vec1);
			#else
				x += v.x; y += v.y; z += v.z; w += v.w;
			#endif
			return *this;
		}
		TS_INLINE float64x4_t &operator-=(const float64x4_t &v) {
			#if TS_AVX >= 1
				vec = _mm256_sub_pd(vec, v.vec);
			#elif TS_SSE >= 2
				vec0 = _mm_sub_pd(vec0, v.vec0);
				vec1 = _mm_sub_pd(vec1, v.vec1);
			#else
				x -= v.x; y -= v.y; z -= v.z; w -= v.w;
			#endif
			return *this;
		}
		
		/// swizzle vector
		TS_INLINE float64x4_t zxyw() const {
			#if TS_AVX >= 2
				return float64x4_t(_mm256_swizzle_pd(vec, Z, X, Y, W));
			#elif TS_AVX >= 1
				return float64x4_t(_mm256_shuffle_pd(_mm256_permute2f128_pd(vec, vec, 0x01), vec, 0x0c));
			#elif TS_SSE >= 2
				return float64x4_t(_mm_swizzle_pd(vec1, vec0, X, X), _mm_swizzle_pd(vec0, vec1, Y, Y));
			#else
				return float64x4_t(z, x, y, w);
			#endif
		}
		TS_INLINE float64x4_t zwxy() const {
			#if TS_AVX >= 1
				return float64x4_t(_mm256_permute2f128_pd(vec, vec, 0x01));
			#elif TS_SSE >= 2
				return float64x4_t(_mm_swizzle_pd(vec1, vec1, X, Y), _mm_swizzle_pd(vec0, vec0, X, Y));
			#else
				return float64x4_t(z, w, x, y);
			#endif
		}
		TS_INLINE float64x4_t yxwz() const {
			#if TS_AVX >= 1
				return float64x4_t(_mm256_permute_pd(vec, 0x05));
			#elif TS_SSE >= 2
				return float64x4_t(_mm_swizzle_pd(vec0, vec0, Y, X), _mm_swizzle_pd(vec1, vec1, Y, X));
			#else
				return float64x4_t(y, x, w, z);
			#endif
		}
		TS_INLINE float64x2_t xy() const {
			#if TS_AVX >= 1
				return float64x2_t(_mm256_extractf128_pd(vec, 0));
			#elif TS_SSE >= 2
				return float64x2_t(vec0);
			#else
				return float64x2_t(x, y);
			#endif
		}
		TS_INLINE float64x2_t zw() const {
			#if TS_AVX >= 1
				return float64x2_t(_mm256_extractf128_pd(vec, 1));
			#elif TS_SSE >= 2
				return float64x2_t(vec1);
			#else
				return float64x2_t(z, w);
			#endif
		}
		
		/// sum vector components
		TS_INLINE float64_t sum() const {
			#if	TS_AVX >= 1
				__m128d temp = _mm_add_pd(_mm256_extractf128_pd(vec, 0), _mm256_extractf128_pd(vec, 1));
				temp = _mm_hadd_pd(temp, temp);
				return _mm_cvtsd_f64(temp);
			#elif TS_SSE >= 4
				__m128d temp = _mm_add_pd(vec0, vec1);
				temp = _mm_hadd_pd(temp, temp);
				return _mm_cvtsd_f64(temp);
			#elif TS_SSE >= 2
				__m128d temp = _mm_add_pd(vec0, vec1);
				temp = _mm_add_pd(temp, _mm_swizzle_pd(temp, temp, Y, X));
				return _mm_cvtsd_f64(temp);
			#else
				return x + y + z + w;
			#endif
		}
		
		enum {
			Size = 4,
		};
		
		union {
			struct {
				float64_t x, y, z, w;
			};
			float64_t v[Size];
			#if TS_AVX >= 1
				struct {
					__m128d vec0;
					__m128d vec1;
				};
				__m256d vec;
			#elif TS_SSE >= 2
				struct {
					__m128d vec0;
					__m128d vec1;
				};
				__m128d vec[2];
			#endif
		};
	};
	
	/// unary operators
	TS_INLINE float64x4_t operator-(const float64x4_t &v) {
		#if TS_AVX >= 1
			return float64x4_t(_mm256_xor_pd(v.vec, _mm256_set1_pd(f64u64(Signf64).f)));
		#elif TS_SSE >= 2
			__m128d temp = _mm_set1_pd(f64u64(Signf64).f);
			return float64x4_t(_mm_xor_pd(v.vec0, temp), _mm_xor_pd(v.vec1, temp));
		#else
			return float64x4_t(-v.x, -v.y, -v.z, -v.w);
		#endif
	}
	
	/// vector to scalar operators
	TS_INLINE float64x4_t operator*(const float64x4_t &v0, float64_t v1) {
		#if TS_AVX >= 1
			return float64x4_t(_mm256_mul_pd(v0.vec, _mm256_set1_pd(v1)));
		#elif TS_SSE >= 2
			__m128d temp = _mm_set1_pd(v1);
			return float64x4_t(_mm_mul_pd(v0.vec0, temp), _mm_mul_pd(v0.vec1, temp));
		#else
			return float64x4_t(v0.x * v1, v0.y * v1, v0.z * v1, v0.w * v1);
		#endif
	}
	TS_INLINE float64x4_t operator/(const float64x4_t &v0, float64_t v1) {
		#if TS_AVX >= 1
			return float64x4_t(_mm256_div_pd(v0.vec, _mm256_set1_pd(v1)));
		#elif TS_SSE >= 2
			__m128d temp = _mm_set1_pd(v1);
			return float64x4_t(_mm_div_pd(v0.vec0, temp), _mm_div_pd(v0.vec1, temp));
		#else
			return float64x4_t(v0.x / v1, v0.y / v1, v0.z / v1, v0.w / v1);
		#endif
	}
	TS_INLINE float64x4_t operator+(const float64x4_t &v0, float64_t v1) {
		#if TS_AVX >= 1
			return float64x4_t(_mm256_add_pd(v0.vec, _mm256_set1_pd(v1)));
		#elif TS_SSE >= 2
			__m128d temp = _mm_set1_pd(v1);
			return float64x4_t(_mm_add_pd(v0.vec0, temp), _mm_add_pd(v0.vec1, temp));
		#else
			return float64x4_t(v0.x + v1, v0.y + v1, v0.z + v1, v0.w + v1);
		#endif
	}
	TS_INLINE float64x4_t operator-(const float64x4_t &v0, float64_t v1) {
		#if TS_AVX >= 1
			return float64x4_t(_mm256_sub_pd(v0.vec, _mm256_set1_pd(v1)));
		#elif TS_SSE >= 2
			__m128d temp = _mm_set1_pd(v1);
			return float64x4_t(_mm_sub_pd(v0.vec0, temp), _mm_sub_pd(v0.vec1, temp));
		#else
			return float64x4_t(v0.x - v1, v0.y - v1, v0.z - v1, v0.w - v1);
		#endif
	}
	
	/// vector to vector operators
	TS_INLINE float64x4_t operator*(const float64x4_t &v0, const float64x4_t &v1) {
		#if TS_AVX >= 1
			return float64x4_t(_mm256_mul_pd(v0.vec, v1.vec));
		#elif TS_SSE >= 2
			return float64x4_t(_mm_mul_pd(v0.vec0, v1.vec0), _mm_mul_pd(v0.vec1, v1.vec1));
		#else
			return float64x4_t(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z, v0.w * v1.w);
		#endif
	}
	TS_INLINE float64x4_t operator/(const float64x4_t &v0, const float64x4_t &v1) {
		#if TS_AVX >= 1
			return float64x4_t(_mm256_div_pd(v0.vec, v1.vec));
		#elif TS_SSE >= 2
			return float64x4_t(_mm_div_pd(v0.vec0, v1.vec0), _mm_div_pd(v0.vec1, v1.vec1));
		#else
			return float64x4_t(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z, v0.w / v1.w);
		#endif
	}
	TS_INLINE float64x4_t operator+(const float64x4_t &v0, const float64x4_t &v1) {
		#if TS_AVX >= 1
			return float64x4_t(_mm256_add_pd(v0.vec, v1.vec));
		#elif TS_SSE >= 2
			return float64x4_t(_mm_add_pd(v0.vec0, v1.vec0), _mm_add_pd(v0.vec1, v1.vec1));
		#else
			return float64x4_t(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w);
		#endif
	}
	TS_INLINE float64x4_t operator-(const float64x4_t &v0, const float64x4_t &v1) {
		#if TS_AVX >= 1
			return float64x4_t(_mm256_sub_pd(v0.vec, v1.vec));
		#elif TS_SSE >= 2
			return float64x4_t(_mm_sub_pd(v0.vec0, v1.vec0), _mm_sub_pd(v0.vec1, v1.vec1));
		#else
			return float64x4_t(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w);
		#endif
	}
	
	/// comparison operators
	TS_INLINE uint32_t operator<(const float64x4_t &v0, const float64x4_t &v1) {
		#if TS_AVX >= 1
			return _mm256_movemask_pd(_mm256_cmp_pd(v0.vec, v1.vec, _CMP_LT_OQ));
		#elif TS_SSE >= 2
			return _mm_movemask_pd(_mm_cmplt_pd(v0.vec0, v1.vec0)) | (_mm_movemask_pd(_mm_cmplt_pd(v0.vec1, v1.vec1)) << 2);
		#else
			return ((uint32_t)(v0.x < v1.x) << 0) | ((uint32_t)(v0.y < v1.y) << 1) | ((uint32_t)(v0.z < v1.z) << 2) | ((uint32_t)(v0.w < v1.w) << 3);
		#endif
	}
	TS_INLINE uint32_t operator>(const float64x4_t &v0, const float64x4_t &v1) {
		#if TS_AVX >= 1
			return _mm256_movemask_pd(_mm256_cmp_pd(v0.vec, v1.vec, _CMP_GT_OQ));
		#elif TS_SSE >= 2
			return _mm_movemask_pd(_mm_cmpgt_pd(v0.vec0, v1.vec0)) | (_mm_movemask_pd(_mm_cmpgt_pd(v0.vec1, v1.vec1)) << 2);
		#else
			return ((uint32_t)(v0.x > v1.x) << 0) | ((uint32_t)(v0.y > v1.y) << 1) | ((uint32_t)(v0.z > v1.z) << 2) | ((uint32_t)(v0.w > v1.w) << 3);
		#endif
	}
	TS_INLINE uint32_t operator<=(const float64x4_t &v0, const float64x4_t &v1) {
		#if TS_AVX >= 1
			return _mm256_movemask_pd(_mm256_cmp_pd(v0.vec, v1.vec, _CMP_LE_OQ));
		#elif TS_SSE >= 2
			return _mm_movemask_pd(_mm_cmple_pd(v0.vec0, v1.vec0)) | (_mm_movemask_pd(_mm_cmple_pd(v0.vec1, v1.vec1)) << 2);
		#else
			return ((uint32_t)(v0.x <= v1.x) << 0) | ((uint32_t)(v0.y <= v1.y) << 1) | ((uint32_t)(v0.z <= v1.z) << 2) | ((uint32_t)(v0.w <= v1.w) << 3);
		#endif
	}
	TS_INLINE uint32_t operator>=(const float64x4_t &v0, const float64x4_t &v1) {
		#if TS_AVX >= 1
			return _mm256_movemask_pd(_mm256_cmp_pd(v0.vec, v1.vec, _CMP_GE_OQ));
		#elif TS_SSE >= 2
			return _mm_movemask_pd(_mm_cmpge_pd(v0.vec0, v1.vec0)) | (_mm_movemask_pd(_mm_cmpge_pd(v0.vec1, v1.vec1)) << 2);
		#else
			return ((uint32_t)(v0.x >= v1.x) << 0) | ((uint32_t)(v0.y >= v1.y) << 1) | ((uint32_t)(v0.z >= v1.z) << 2) | ((uint32_t)(v0.w >= v1.w) << 3);
		#endif
	}
	TS_INLINE uint32_t operator==(const float64x4_t &v0, const float64x4_t &v1) {
		#if TS_AVX >= 1
			return _mm256_movemask_pd(_mm256_cmp_pd(v0.vec, v1.vec, _CMP_EQ_OQ));
		#elif TS_SSE >= 2
			return _mm_movemask_pd(_mm_cmpeq_pd(v0.vec0, v1.vec0)) | (_mm_movemask_pd(_mm_cmpeq_pd(v0.vec1, v1.vec1)) << 2);
		#else
			return ((uint32_t)(v0.x == v1.x) << 0) | ((uint32_t)(v0.y == v1.y) << 1) | ((uint32_t)(v0.z == v1.z) << 2) | ((uint32_t)(v0.w == v1.w) << 3);
		#endif
	}
	TS_INLINE uint32_t operator!=(const float64x4_t &v0, const float64x4_t &v1) {
		#if TS_AVX >= 1
			return _mm256_movemask_pd(_mm256_cmp_pd(v0.vec, v1.vec, _CMP_NEQ_OQ));
		#elif TS_SSE >= 2
			return _mm_movemask_pd(_mm_cmpneq_pd(v0.vec0, v1.vec0)) | (_mm_movemask_pd(_mm_cmpneq_pd(v0.vec1, v1.vec1)) << 2);
		#else
			return ((uint32_t)(v0.x != v1.x) << 0) | ((uint32_t)(v0.y != v1.y) << 1) | ((uint32_t)(v0.z != v1.z) << 2) | ((uint32_t)(v0.w != v1.w) << 3);
		#endif
	}
	
	/// min/max functions
	TS_INLINE float64x4_t min(const float64x4_t &v0, const float64x4_t &v1) {
		#if TS_AVX >= 1
			return float64x4_t(_mm256_min_pd(v0.vec, v1.vec));
		#elif TS_SSE >= 2
			return float64x4_t(_mm_min_pd(v0.vec0, v1.vec0), _mm_min_pd(v0.vec1, v1.vec1));
		#else
			return float64x4_t(min(v0.x, v1.x), min(v0.y, v1.y), min(v0.z, v1.z), min(v0.w, v1.w));
		#endif
	}
	TS_INLINE float64x4_t max(const float64x4_t &v0, const float64x4_t &v1) {
		#if TS_AVX >= 1
			return float64x4_t(_mm256_max_pd(v0.vec, v1.vec));
		#elif TS_SSE >= 2
			return float64x4_t(_mm_max_pd(v0.vec0, v1.vec0), _mm_max_pd(v0.vec1, v1.vec1));
		#else
			return float64x4_t(max(v0.x, v1.x), max(v0.y, v1.y), max(v0.z, v1.z), max(v0.w, v1.w));
		#endif
	}
	
	/// range functions
	TS_INLINE float64x4_t saturate(const float64x4_t &v) {
		return min(max(v, float64x4_t(0.0)), float64x4_t(1.0));
	}
	TS_INLINE float64x4_t clamp(const float64x4_t &v, float64_t v0, float64_t v1) {
		return min(max(v, float64x4_t(v0)), float64x4_t(v1));
	}
	TS_INLINE float64x4_t clamp(const float64x4_t &v, const float64x4_t &v0, const float64x4_t &v1) {
		return min(max(v, v0), v1);
	}
	
	/// select functions
	TS_INLINE float64x4_t select(const float64x4_t &v0, const float64x4_t &v1, const float64x4_t &s) {
		#if TS_AVX >= 1
			return float64x4_t(_mm256_blendv_pd(v0.vec, v1.vec, s.vec));
		#elif TS_SSE >= 2
			return float64x4_t(_mm_xor_pd(v0.vec0, _mm_and_pd(_mm_xor_pd(v0.vec0, v1.vec0), _mm_cmplt_pd(s.vec0, _mm_setzero_pd()))), _mm_xor_pd(v0.vec1, _mm_and_pd(_mm_xor_pd(v0.vec1, v1.vec1), _mm_cmplt_pd(s.vec1, _mm_setzero_pd()))));
		#else
			return float64x4_t(select(v0.x, v1.x, s.x), select(v0.y, v1.y, s.y), select(v0.z, v1.z, s.z), select(v0.w, v1.w, s.w));
		#endif
	}
	TS_INLINE float64x4_t select(const float64x4_t &v0, const float64x4_t &v1, float64_t s) {
		return select(v0, v1, float64x4_t(s));
	}
	
	/// math functions
	TS_INLINE float64x4_t sqrt(const float64x4_t &v) {
		#if TS_AVX >= 1
			return float64x4_t(_mm256_sqrt_pd(v.vec));
		#elif TS_SSE >= 2
			return float64x4_t(_mm_sqrt_pd(v.vec0), _mm_sqrt_pd(v.vec1));
		#else
			return float64x4_t(sqrt(v.x), sqrt(v.y), sqrt(v.z), sqrt(v.w));
		#endif
	}
	
	/// vector functions
	TS_INLINE float64x4_t lerp(const float64x4_t &v0, const float64x4_t &v1, float64_t k) {
		#if TS_AVX >= 1
			return float64x4_t(_mm256_add_pd(v0.vec, _mm256_mul_pd(_mm256_sub_pd(v1.vec, v0.vec), _mm256_set1_pd(k))));
		#elif TS_SSE >= 2
			__m128d temp = _mm_set1_pd(k);
			return float64x4_t(_mm_add_pd(v0.vec0, _mm_mul_pd(_mm_sub_pd(v1.vec0, v0.vec0), temp)), _mm_add_pd(v0.vec1, _mm_mul_pd(_mm_sub_pd(v1.vec1, v0.vec1), temp)));
		#else
			return float64x4_t(lerp(v0.x, v1.x, k), lerp(v0.y, v1.y, k), lerp(v0.z, v1.z, k), lerp(v0.w, v1.w, k));
		#endif
	}
	
	/*****************************************************************************\
	 *
	 * float64x8_t
	 *
	\*****************************************************************************/
	
	/**
	 * Vector of eight float64_t components
	 */
	struct TS_ALIGNAS32 float64x8_t {
		
		float64x8_t() { }
		explicit float64x8_t(const float64_t *v) { set(v); }
		#if TS_AVX >= 1
			float64x8_t(const float64x8_t &v) : vec0(v.vec0), vec1(v.vec1) { }
			float64x8_t(__m256d v0, __m256d v1) : vec0(v0), vec1(v1) { }
			explicit float64x8_t(float64_t v) : vec0(_mm256_set1_pd(v)), vec1(_mm256_set1_pd(v)) { }
			explicit float64x8_t(const int32x8_t &v) : vec0(_mm256_cvtepi32_pd(v.vec0)), vec1(_mm256_cvtepi32_pd(v.vec1)) { }
			explicit float64x8_t(const uint32x8_t &v) : vec0(_mm256_cvtepi32_pd(v.vec0)), vec1(_mm256_cvtepi32_pd(v.vec1)) { }
			explicit float64x8_t(const float32x8_t &v) : vec0(_mm256_cvtps_pd(v.vec0)), vec1(_mm256_cvtps_pd(v.vec1)) { }
			float64x8_t(const float64x4_t &v0, const float64x4_t &v1) : vec0(v0.vec), vec1(v1.vec) { }
			float64x8_t(float64_t x0, float64_t y0, float64_t z0, float64_t w0, float64_t x1, float64_t y1, float64_t z1, float64_t w1) : vec0(_mm256_setr_pd(x0, y0, z0, w0)), vec1(_mm256_setr_pd(x1, y1, z1, w1)) { }
		#elif TS_SSE >= 2
			float64x8_t(const float64x8_t &v) : vec0(v.vec0), vec1(v.vec1), vec2(v.vec2), vec3(v.vec3) { }
			float64x8_t(__m128d v0, __m128d v1, __m128d v2, __m128d v3) : vec0(v0), vec1(v1), vec2(v2), vec3(v3) { }
			explicit float64x8_t(float64_t v) : vec0(_mm_set1_pd(v)), vec1(_mm_set1_pd(v)), vec2(_mm_set1_pd(v)), vec3(_mm_set1_pd(v)) { }
			explicit float64x8_t(const int32x8_t &v) : vec0(_mm_cvtepi32_pd(v.vec0)), vec1(_mm_cvtepi32_pd(_mm_swizzle_epi32(v.vec0, Z, W, Z, W))), vec2(_mm_cvtepi32_pd(v.vec1)), vec3(_mm_cvtepi32_pd(_mm_swizzle_epi32(v.vec1, Z, W, Z, W))) { }
			explicit float64x8_t(const uint32x8_t &v) : vec0(_mm_cvtepi32_pd(v.vec0)), vec1(_mm_cvtepi32_pd(_mm_swizzle_epi32(v.vec0, Z, W, Z, W))), vec2(_mm_cvtepi32_pd(v.vec1)), vec3(_mm_cvtepi32_pd(_mm_swizzle_epi32(v.vec1, Z, W, Z, W))) { }
			explicit float64x8_t(const float32x8_t &v) : vec0(_mm_cvtps_pd(v.vec0)), vec1(_mm_cvtps_pd(_mm_swizzle_ps(v.vec0, v.vec0, Z, W, Z, W))), vec2(_mm_cvtps_pd(v.vec1)), vec3(_mm_cvtps_pd(_mm_swizzle_ps(v.vec1, v.vec1, Z, W, Z, W))) { }
			float64x8_t(const float64x4_t &v0, const float64x4_t &v1) : vec0(v0.vec0), vec1(v0.vec1), vec2(v1.vec0), vec3(v1.vec1) { }
			float64x8_t(float64_t x0, float64_t y0, float64_t z0, float64_t w0, float64_t x1, float64_t y1, float64_t z1, float64_t w1) : vec0(_mm_setr_pd(x0, y0)), vec1(_mm_setr_pd(z0, w0)), vec2(_mm_setr_pd(x1, y1)), vec3(_mm_setr_pd(z1, w1)) { }
		#else
			explicit float64x8_t(float64_t v) : x0(v), y0(v), z0(v), w0(v), x1(v), y1(v), z1(v), w1(v) { }
			explicit float64x8_t(const int32x8_t &v) : x0((float64_t)v.x0), y0((float64_t)v.y0), z0((float64_t)v.z0), w0((float64_t)v.w0), x1((float64_t)v.x1), y1((float64_t)v.y1), z1((float64_t)v.z1), w1((float64_t)v.w1) { }
			explicit float64x8_t(const uint32x8_t &v) : x0((float64_t)v.x0), y0((float64_t)v.y0), z0((float64_t)v.z0), w0((float64_t)v.w0), x1((float64_t)v.x1), y1((float64_t)v.y1), z1((float64_t)v.z1), w1((float64_t)v.w1) { }
			explicit float64x8_t(const float32x8_t &v) : x0(v.x0), y0(v.y0), z0(v.z0), w0(v.w0), x1(v.x1), y1(v.y1), z1(v.z1), w1(v.w1) { }
			float64x8_t(const float64x4_t &v0, const float64x4_t &v1) : x0(v0.x), y0(v0.y), z0(v0.z), w0(v0.w), x1(v1.x), y1(v1.y), z1(v1.z), w1(v1.w) { }
			float64x8_t(float64_t x0, float64_t y0, float64_t z0, float64_t w0, float64_t x1, float64_t y1, float64_t z1, float64_t w1) : x0(x0), y0(y0), z0(z0), w0(w0), x1(x1), y1(y1), z1(z1), w1(w1) { }
		#endif
		
		/// update vector data
		TS_INLINE void set(const float64x8_t &v) {
			#if TS_AVX >= 1
				vec0 = v.vec0;
				vec1 = v.vec1;
			#elif TS_SSE >= 2
				vec0 = v.vec0;
				vec1 = v.vec1;
				vec2 = v.vec2;
				vec3 = v.vec3;
			#else
				x0 = v.x0; y0 = v.y0; z0 = v.z0; w0 = v.w0;
				x1 = v.x1; y1 = v.y1; z1 = v.z1; w1 = v.w1;
			#endif
		}
		TS_INLINE void set(float64_t X0, float64_t Y0, float64_t Z0, float64_t W0, float64_t X1, float64_t Y1, float64_t Z1, float64_t W1) {
			#if TS_AVX >= 1
				vec0 = _mm256_setr_pd(X0, Y0, Z0, W0);
				vec1 = _mm256_setr_pd(X1, Y1, Z1, W1);
			#elif TS_SSE >= 2
				vec0 = _mm_setr_pd(X0, Y0);
				vec1 = _mm_setr_pd(Z0, W0);
				vec2 = _mm_setr_pd(X1, Y1);
				vec3 = _mm_setr_pd(Z1, W1);
			#else
				x0 = X0; y0 = Y0; z0 = Z0; w0 = W0;
				x1 = X1; y1 = Y1; z1 = Z1; w1 = W1;
			#endif
		}
		TS_INLINE void set(const float64_t *TS_RESTRICT v) {
			#if TS_AVX >= 1
				vec0 = _mm256_load_pd(v + 0);
				vec1 = _mm256_load_pd(v + 4);
			#elif TS_SSE >= 2
				vec0 = _mm_load_pd(v + 0);
				vec1 = _mm_load_pd(v + 2);
				vec2 = _mm_load_pd(v + 4);
				vec3 = _mm_load_pd(v + 6);
			#else
				x0 = v[0]; y0 = v[1]; z0 = v[2]; w0 = v[3];
				x1 = v[4]; y1 = v[5]; z1 = v[6]; w1 = v[7];
			#endif
		}
		TS_INLINE void get(float64_t *TS_RESTRICT v) const {
			#if TS_AVX >= 1
				_mm256_stream_pd(v + 0, vec0);
				_mm256_stream_pd(v + 4, vec1);
			#elif TS_SSE >= 2
				_mm_stream_pd(v + 0, vec0);
				_mm_stream_pd(v + 2, vec1);
				_mm_stream_pd(v + 4, vec2);
				_mm_stream_pd(v + 6, vec3);
			#else
				v[0] = x0; v[1] = y0; v[2] = z0; v[3] = w0;
				v[4] = x1; v[5] = y1; v[6] = z1; v[7] = w1;
			#endif
		}
		template <uint32_t Index> TS_INLINE void set(float64_t V) {
			#if TS_AVX >= 1 && TS_X64
				__m128i temp = _mm_insert_epi64(_mm256_extractf128_si256(_mm256_castpd_si256(vec[Index >> 2]), (Index & 0x03) >> 1), (int64_t)f64u64(V).u, Index & 0x01);
				vec[Index >> 2] = _mm256_castsi256_pd(_mm256_insertf128_si256(_mm256_castpd_si256(vec[Index >> 2]), temp, (Index & 0x03) >> 1));
			#elif TS_SSE >= 4 && TS_X64
				vec[Index >> 1] = _mm_castsi128_pd(_mm_insert_epi64(_mm_castpd_si128(vec[Index >> 1]), (int64_t)f64u64(V).u, Index & 0x01));
			#else
				v[Index] = V;
			#endif
		}
		template <uint32_t Index> TS_INLINE float64_t get() const {
			#if TS_AVX >= 1 && TS_X64
				return f64u64((uint64_t)_mm_extract_epi64(_mm256_extractf128_si256(_mm256_castpd_si256(vec[Index >> 2]), (Index & 0x03) >> 1), Index & 0x01)).f;
			#elif TS_SSE >= 4 && TS_X64
				return f64u64((uint64_t)_mm_extract_epi64(_mm_castpd_si128(vec[Index >> 1]), Index & 0x01)).f;
			#else
				return v[Index];
			#endif
		}
		template <uint64_t Index> TS_INLINE float64x8_t get8() const {
			#if TS_AVX >= 2
				__m256d temp = _mm256_permute4x64_pd(vec[Index >> 2], ((Index & 0x03) << 6) | ((Index & 0x03) << 4) | ((Index & 0x03) << 2) | (Index & 0x03));
				return float64x8_t(temp, temp);
			#elif TS_AVX >= 1
				__m256d temp = _mm256_permute_pd(_mm256_permute2f128_pd(vec[Index >> 2], vec[Index >> 2], (Index & 0x02) ? 0x11 : 0x00), (Index & 0x01) ? 0x0f : 0x00);
				return float64x8_t(temp, temp);
			#elif TS_SSE >= 2
				__m128d temp = _mm_shuffle_pd(vec[Index >> 1], vec[Index >> 1], (Index & 0x01) ? 0x03 : 0x00);
				return float64x8_t(temp, temp, temp, temp);
			#else
				return float64x8_t(v[Index]);
			#endif
		}
		
		/// vector to scalar operators
		TS_INLINE float64x8_t &operator*=(float64_t v) {
			#if TS_AVX >= 1
				__m256d temp = _mm256_set1_pd(v);
				vec0 = _mm256_mul_pd(vec0, temp);
				vec1 = _mm256_mul_pd(vec1, temp);
			#elif TS_SSE >= 2
				__m128d temp = _mm_set1_pd(v);
				vec0 = _mm_mul_pd(vec0, temp);
				vec1 = _mm_mul_pd(vec1, temp);
				vec2 = _mm_mul_pd(vec2, temp);
				vec3 = _mm_mul_pd(vec3, temp);
			#else
				x0 *= v; y0 *= v; z0 *= v; w0 *= v; x1 *= v; y1 *= v; z1 *= v; w1 *= v;
			#endif
			return *this;
		}
		TS_INLINE float64x8_t &operator/=(float64_t v) {
			#if TS_AVX >= 1
				__m256d temp = _mm256_set1_pd(v);
				vec0 = _mm256_div_pd(vec0, temp);
				vec1 = _mm256_div_pd(vec1, temp);
			#elif TS_SSE >= 2
				__m128d temp = _mm_set1_pd(v);
				vec0 = _mm_div_pd(vec0, temp);
				vec1 = _mm_div_pd(vec1, temp);
				vec2 = _mm_div_pd(vec2, temp);
				vec3 = _mm_div_pd(vec3, temp);
			#else
				x0 /= v; y0 /= v; z0 /= v; w0 /= v; x1 /= v; y1 /= v; z1 /= v; w1 /= v;
			#endif
			return *this;
		}
		TS_INLINE float64x8_t &operator+=(float64_t v) {
			#if TS_AVX >= 1
				__m256d temp = _mm256_set1_pd(v);
				vec0 = _mm256_add_pd(vec0, temp);
				vec1 = _mm256_add_pd(vec1, temp);
			#elif TS_SSE >= 2
				__m128d temp = _mm_set1_pd(v);
				vec0 = _mm_add_pd(vec0, temp);
				vec1 = _mm_add_pd(vec1, temp);
				vec2 = _mm_add_pd(vec2, temp);
				vec3 = _mm_add_pd(vec3, temp);
			#else
				x0 += v; y0 += v; z0 += v; w0 += v; x1 += v; y1 += v; z1 += v; w1 += v;
			#endif
			return *this;
		}
		TS_INLINE float64x8_t &operator-=(float64_t v) {
			#if TS_AVX >= 1
				__m256d temp = _mm256_set1_pd(v);
				vec0 = _mm256_sub_pd(vec0, temp);
				vec1 = _mm256_sub_pd(vec1, temp);
			#elif TS_SSE >= 2
				__m128d temp = _mm_set1_pd(v);
				vec0 = _mm_sub_pd(vec0, temp);
				vec1 = _mm_sub_pd(vec1, temp);
				vec2 = _mm_sub_pd(vec2, temp);
				vec3 = _mm_sub_pd(vec3, temp);
			#else
				x0 -= v; y0 -= v; z0 -= v; w0 -= v; x1 -= v; y1 -= v; z1 -= v; w1 -= v;
			#endif
			return *this;
		}
		
		/// vector to vector operators
		TS_INLINE float64x8_t &operator*=(const float64x8_t &v) {
			#if TS_AVX >= 1
				vec0 = _mm256_mul_pd(vec0, v.vec0);
				vec1 = _mm256_mul_pd(vec1, v.vec1);
			#elif TS_SSE >= 2
				vec0 = _mm_mul_pd(vec0, v.vec0);
				vec1 = _mm_mul_pd(vec1, v.vec1);
				vec2 = _mm_mul_pd(vec2, v.vec2);
				vec3 = _mm_mul_pd(vec3, v.vec3);
			#else
				x0 *= v.x0; y0 *= v.y0; z0 *= v.z0; w0 *= v.w0; x1 *= v.x1; y1 *= v.y1; z1 *= v.z1; w1 *= v.w1;
			#endif
			return *this;
		}
		TS_INLINE float64x8_t &operator/=(const float64x8_t &v) {
			#if TS_AVX >= 1
				vec0 = _mm256_div_pd(vec0, v.vec0);
				vec1 = _mm256_div_pd(vec1, v.vec1);
			#elif TS_SSE >= 2
				vec0 = _mm_div_pd(vec0, v.vec0);
				vec1 = _mm_div_pd(vec1, v.vec1);
				vec2 = _mm_div_pd(vec2, v.vec2);
				vec3 = _mm_div_pd(vec3, v.vec3);
			#else
				x0 /= v.x0; y0 /= v.y0; z0 /= v.z0; w0 /= v.w0; x1 /= v.x1; y1 /= v.y1; z1 /= v.z1; w1 /= v.w1;
			#endif
			return *this;
		}
		TS_INLINE float64x8_t &operator+=(const float64x8_t &v) {
			#if TS_AVX >= 1
				vec0 = _mm256_add_pd(vec0, v.vec0);
				vec1 = _mm256_add_pd(vec1, v.vec1);
			#elif TS_SSE >= 2
				vec0 = _mm_add_pd(vec0, v.vec0);
				vec1 = _mm_add_pd(vec1, v.vec1);
				vec2 = _mm_add_pd(vec2, v.vec2);
				vec3 = _mm_add_pd(vec3, v.vec3);
			#else
				x0 += v.x0; y0 += v.y0; z0 += v.z0; w0 += v.w0; x1 += v.x1; y1 += v.y1; z1 += v.z1; w1 += v.w1;
			#endif
			return *this;
		}
		TS_INLINE float64x8_t &operator-=(const float64x8_t &v) {
			#if TS_AVX >= 1
				vec0 = _mm256_sub_pd(vec0, v.vec0);
				vec1 = _mm256_sub_pd(vec1, v.vec1);
			#elif TS_SSE >= 2
				vec0 = _mm_sub_pd(vec0, v.vec0);
				vec1 = _mm_sub_pd(vec1, v.vec1);
				vec2 = _mm_sub_pd(vec2, v.vec2);
				vec3 = _mm_sub_pd(vec3, v.vec3);
			#else
				x0 -= v.x0; y0 -= v.y0; z0 -= v.z0; w0 -= v.w0; x1 -= v.x1; y1 -= v.y1; z1 -= v.z1; w1 -= v.w1;
			#endif
			return *this;
		}
		
		/// swizzle vector
		TS_INLINE float64x8_t xyzw10() const {
			#if TS_AVX >= 1
				return float64x8_t(vec1, vec0);
			#elif TS_SSE >= 2
				return float64x8_t(vec2, vec3, vec0, vec1);
			#else
				return float64x8_t(x1, y1, z1, w1, x0, y0, z0, w0);
			#endif
		}
		TS_INLINE float64x8_t zwxy01() const {
			#if TS_AVX >= 1
				return float64x8_t(_mm256_permute2f128_pd(vec0, vec0, 0x01), _mm256_permute2f128_pd(vec1, vec1, 0x01));
			#elif TS_SSE >= 2
				return float64x8_t(_mm_swizzle_pd(vec1, vec1, X, Y), _mm_swizzle_pd(vec0, vec0, X, Y), _mm_swizzle_pd(vec3, vec3, X, Y), _mm_swizzle_pd(vec2, vec2, X, Y));
			#else
				return float64x8_t(z0, w0, x0, y0, z1, w1, x1, y1);
			#endif
		}
		TS_INLINE float64x8_t yxwz01() const {
			#if TS_AVX >= 1
				return float64x8_t(_mm256_permute_pd(vec0, 0x05), _mm256_permute_pd(vec1, 0x05));
			#elif TS_SSE >= 2
				return float64x8_t(_mm_swizzle_pd(vec0, vec0, Y, X), _mm_swizzle_pd(vec1, vec1, Y, X), _mm_swizzle_pd(vec2, vec2, Y, X), _mm_swizzle_pd(vec3, vec3, Y, X));
			#else
				return float64x8_t(y0, x0, w0, z0, y1, x1, w1, z1);
			#endif
		}
		TS_INLINE float64x4_t xyzw0() const {
			#if TS_AVX >= 1
				return float64x4_t(vec0);
			#elif TS_SSE >= 2
				return float64x4_t(vec0, vec1);
			#else
				return float64x4_t(x0, y0, z0, w0);
			#endif
		}
		TS_INLINE float64x4_t xyzw1() const {
			#if TS_AVX >= 1
				return float64x4_t(vec1);
			#elif TS_SSE >= 2
				return float64x4_t(vec2, vec3);
			#else
				return float64x4_t(x1, y1, z1, w1);
			#endif
		}
		
		/// sum vector components
		TS_INLINE float64_t sum() const {
			#if	TS_AVX >= 1
				__m256d temp01 = _mm256_add_pd(vec0, vec1);
				__m128d temp = _mm_add_pd(_mm256_extractf128_pd(temp01, 0), _mm256_extractf128_pd(temp01, 1));
				temp = _mm_hadd_pd(temp, temp);
				return _mm_cvtsd_f64(temp);
			#elif TS_SSE >= 4
				__m128d temp = _mm_add_pd(_mm_add_pd(vec0, vec1), _mm_add_pd(vec2, vec3));
				temp = _mm_hadd_pd(temp, temp);
				return _mm_cvtsd_f64(temp);
			#elif TS_SSE >= 2
				__m128d temp = _mm_add_pd(_mm_add_pd(vec0, vec1), _mm_add_pd(vec2, vec3));
				temp = _mm_add_pd(temp, _mm_swizzle_pd(temp, temp, Y, X));
				return _mm_cvtsd_f64(temp);
			#else
				return x0 + y0 + z0 + w0 + x1 + y1 + z1 + w1;
			#endif
		}
		
		enum {
			Size = 8,
		};
		
		union {
			struct {
				float64_t x0, y0, z0, w0;
				float64_t x1, y1, z1, w1;
			};
			float64_t v[Size];
			#if TS_AVX >= 1
				struct {
					__m256d vec0;
					__m256d vec1;
				};
				__m256d vec[2];
			#elif TS_SSE >= 2
				struct {
					__m128d vec0;
					__m128d vec1;
					__m128d vec2;
					__m128d vec3;
				};
				__m128d vec[4];
			#endif
		};
	};
	
	/// unary operators
	TS_INLINE float64x8_t operator-(const float64x8_t &v) {
		#if TS_AVX >= 1
			__m256d temp = _mm256_set1_pd(f64u64(Signf64).f);
			return float64x8_t(_mm256_xor_pd(v.vec0, temp), _mm256_xor_pd(v.vec1, temp));
		#elif TS_SSE >= 2
			__m128d temp = _mm_set1_pd(f64u64(Signf64).f);
			return float64x8_t(_mm_xor_pd(v.vec0, temp), _mm_xor_pd(v.vec1, temp), _mm_xor_pd(v.vec2, temp), _mm_xor_pd(v.vec3, temp));
		#else
			return float64x8_t(-v.x0, -v.y0, -v.z0, -v.w0, -v.x1, -v.y1, -v.z1, -v.w1);
		#endif
	}
	
	/// vector to scalar operators
	TS_INLINE float64x8_t operator*(const float64x8_t &v0, float64_t v1) {
		#if TS_AVX >= 1
			__m256d temp = _mm256_set1_pd(v1);
			return float64x8_t(_mm256_mul_pd(v0.vec0, temp), _mm256_mul_pd(v0.vec1, temp));
		#elif TS_SSE >= 2
			__m128d temp = _mm_set1_pd(v1);
			return float64x8_t(_mm_mul_pd(v0.vec0, temp), _mm_mul_pd(v0.vec1, temp), _mm_mul_pd(v0.vec2, temp), _mm_mul_pd(v0.vec3, temp));
		#else
			return float64x8_t(v0.x0 * v1, v0.y0 * v1, v0.z0 * v1, v0.w0 * v1, v0.x1 * v1, v0.y1 * v1, v0.z1 * v1, v0.w1 * v1);
		#endif
	}
	TS_INLINE float64x8_t operator/(const float64x8_t &v0, float64_t v1) {
		#if TS_AVX >= 1
			__m256d temp = _mm256_set1_pd(v1);
			return float64x8_t(_mm256_div_pd(v0.vec0, temp), _mm256_div_pd(v0.vec1, temp));
		#elif TS_SSE >= 2
			__m128d temp = _mm_set1_pd(v1);
			return float64x8_t(_mm_div_pd(v0.vec0, temp), _mm_div_pd(v0.vec1, temp), _mm_div_pd(v0.vec2, temp), _mm_div_pd(v0.vec3, temp));
		#else
			return float64x8_t(v0.x0 / v1, v0.y0 / v1, v0.z0 / v1, v0.w0 / v1, v0.x1 / v1, v0.y1 / v1, v0.z1 / v1, v0.w1 / v1);
		#endif
	}
	TS_INLINE float64x8_t operator+(const float64x8_t &v0, float64_t v1) {
		#if TS_AVX >= 1
			__m256d temp = _mm256_set1_pd(v1);
			return float64x8_t(_mm256_add_pd(v0.vec0, temp), _mm256_add_pd(v0.vec1, temp));
		#elif TS_SSE >= 2
			__m128d temp = _mm_set1_pd(v1);
			return float64x8_t(_mm_add_pd(v0.vec0, temp), _mm_add_pd(v0.vec1, temp), _mm_add_pd(v0.vec2, temp), _mm_add_pd(v0.vec3, temp));
		#else
			return float64x8_t(v0.x0 + v1, v0.y0 + v1, v0.z0 + v1, v0.w0 + v1, v0.x1 + v1, v0.y1 + v1, v0.z1 + v1, v0.w1 + v1);
		#endif
	}
	TS_INLINE float64x8_t operator-(const float64x8_t &v0, float64_t v1) {
		#if TS_AVX >= 1
			__m256d temp = _mm256_set1_pd(v1);
			return float64x8_t(_mm256_sub_pd(v0.vec0, temp), _mm256_sub_pd(v0.vec1, temp));
		#elif TS_SSE >= 2
			__m128d temp = _mm_set1_pd(v1);
			return float64x8_t(_mm_sub_pd(v0.vec0, temp), _mm_sub_pd(v0.vec1, temp), _mm_sub_pd(v0.vec2, temp), _mm_sub_pd(v0.vec3, temp));
		#else
			return float64x8_t(v0.x0 - v1, v0.y0 - v1, v0.z0 - v1, v0.w0 - v1, v0.x1 - v1, v0.y1 - v1, v0.z1 - v1, v0.w1 - v1);
		#endif
	}
	
	/// vector to vector operators
	TS_INLINE float64x8_t operator*(const float64x8_t &v0, const float64x8_t &v1) {
		#if TS_AVX >= 1
			return float64x8_t(_mm256_mul_pd(v0.vec0, v1.vec0), _mm256_mul_pd(v0.vec1, v1.vec1));
		#elif TS_SSE >= 2
			return float64x8_t(_mm_mul_pd(v0.vec0, v1.vec0), _mm_mul_pd(v0.vec1, v1.vec1), _mm_mul_pd(v0.vec2, v1.vec2), _mm_mul_pd(v0.vec3, v1.vec3));
		#else
			return float64x8_t(v0.x0 * v1.x0, v0.y0 * v1.y0, v0.z0 * v1.z0, v0.w0 * v1.w0, v0.x1 * v1.x1, v0.y1 * v1.y1, v0.z1 * v1.z1, v0.w1 * v1.w1);
		#endif
	}
	TS_INLINE float64x8_t operator/(const float64x8_t &v0, const float64x8_t &v1) {
		#if TS_AVX >= 1
			return float64x8_t(_mm256_div_pd(v0.vec0, v1.vec0), _mm256_div_pd(v0.vec1, v1.vec1));
		#elif TS_SSE >= 2
			return float64x8_t(_mm_div_pd(v0.vec0, v1.vec0), _mm_div_pd(v0.vec1, v1.vec1), _mm_div_pd(v0.vec2, v1.vec2), _mm_div_pd(v0.vec3, v1.vec3));
		#else
			return float64x8_t(v0.x0 / v1.x0, v0.y0 / v1.y0, v0.z0 / v1.z0, v0.w0 / v1.w0, v0.x1 / v1.x1, v0.y1 / v1.y1, v0.z1 / v1.z1, v0.w1 / v1.w1);
		#endif
	}
	TS_INLINE float64x8_t operator+(const float64x8_t &v0, const float64x8_t &v1) {
		#if TS_AVX >= 1
			return float64x8_t(_mm256_add_pd(v0.vec0, v1.vec0), _mm256_add_pd(v0.vec1, v1.vec1));
		#elif TS_SSE >= 2
			return float64x8_t(_mm_add_pd(v0.vec0, v1.vec0), _mm_add_pd(v0.vec1, v1.vec1), _mm_add_pd(v0.vec2, v1.vec2), _mm_add_pd(v0.vec3, v1.vec3));
		#else
			return float64x8_t(v0.x0 + v1.x0, v0.y0 + v1.y0, v0.z0 + v1.z0, v0.w0 + v1.w0, v0.x1 + v1.x1, v0.y1 + v1.y1, v0.z1 + v1.z1, v0.w1 + v1.w1);
		#endif
	}
	TS_INLINE float64x8_t operator-(const float64x8_t &v0, const float64x8_t &v1) {
		#if TS_AVX >= 1
			return float64x8_t(_mm256_sub_pd(v0.vec0, v1.vec0), _mm256_sub_pd(v0.vec1, v1.vec1));
		#elif TS_SSE >= 2
			return float64x8_t(_mm_sub_pd(v0.vec0, v1.vec0), _mm_sub_pd(v0.vec1, v1.vec1), _mm_sub_pd(v0.vec2, v1.vec2), _mm_sub_pd(v0.vec3, v1.vec3));
		#else
			return float64x8_t(v0.x0 - v1.x0, v0.y0 - v1.y0, v0.z0 - v1.z0, v0.w0 - v1.w0, v0.x1 - v1.x1, v0.y1 - v1.y1, v0.z1 - v1.z1, v0.w1 - v1.w1);
		#endif
	}
	
	/// comparison operators
	TS_INLINE uint32_t operator<(const float64x8_t &v0, const float64x8_t &v1) {
		#if TS_AVX >= 1
			return _mm256_movemask_pd(_mm256_cmp_pd(v0.vec0, v1.vec0, _CMP_LT_OQ)) | (_mm256_movemask_pd(_mm256_cmp_pd(v0.vec1, v1.vec1, _CMP_LT_OQ)) << 4);
		#elif TS_SSE >= 2
			return _mm_movemask_pd(_mm_cmplt_pd(v0.vec0, v1.vec0)) | (_mm_movemask_pd(_mm_cmplt_pd(v0.vec1, v1.vec1)) << 2) | (_mm_movemask_pd(_mm_cmplt_pd(v0.vec2, v1.vec2)) << 4) | (_mm_movemask_pd(_mm_cmplt_pd(v0.vec3, v1.vec3)) << 6);
		#else
			return ((uint32_t)(v0.x0 < v1.x0) << 0) | ((uint32_t)(v0.y0 < v1.y0) << 1) | ((uint32_t)(v0.z0 < v1.z0) << 2) | ((uint32_t)(v0.w0 < v1.w0) << 3) | ((uint32_t)(v0.x1 < v1.x1) << 4) | ((uint32_t)(v0.y1 < v1.y1) << 5) | ((uint32_t)(v0.z1 < v1.z1) << 6) | ((uint32_t)(v0.w1 < v1.w1) << 7);
		#endif
	}
	TS_INLINE uint32_t operator>(const float64x8_t &v0, const float64x8_t &v1) {
		#if TS_AVX >= 1
			return _mm256_movemask_pd(_mm256_cmp_pd(v0.vec0, v1.vec0, _CMP_GT_OQ)) | (_mm256_movemask_pd(_mm256_cmp_pd(v0.vec1, v1.vec1, _CMP_GT_OQ)) << 4);
		#elif TS_SSE >= 2
			return _mm_movemask_pd(_mm_cmpgt_pd(v0.vec0, v1.vec0)) | (_mm_movemask_pd(_mm_cmpgt_pd(v0.vec1, v1.vec1)) << 2) | (_mm_movemask_pd(_mm_cmpgt_pd(v0.vec2, v1.vec2)) << 4) | (_mm_movemask_pd(_mm_cmpgt_pd(v0.vec3, v1.vec3)) << 6);
		#else
			return ((uint32_t)(v0.x0 > v1.x0) << 0) | ((uint32_t)(v0.y0 > v1.y0) << 1) | ((uint32_t)(v0.z0 > v1.z0) << 2) | ((uint32_t)(v0.w0 > v1.w0) << 3) | ((uint32_t)(v0.x1 > v1.x1) << 4) | ((uint32_t)(v0.y1 > v1.y1) << 5) | ((uint32_t)(v0.z1 > v1.z1) << 6) | ((uint32_t)(v0.w1 > v1.w1) << 7);
		#endif
	}
	TS_INLINE uint32_t operator<=(const float64x8_t &v0, const float64x8_t &v1) {
		#if TS_AVX >= 1
			return _mm256_movemask_pd(_mm256_cmp_pd(v0.vec0, v1.vec0, _CMP_LE_OQ)) | (_mm256_movemask_pd(_mm256_cmp_pd(v0.vec1, v1.vec1, _CMP_LE_OQ)) << 4);
		#elif TS_SSE >= 2
			return _mm_movemask_pd(_mm_cmple_pd(v0.vec0, v1.vec0)) | (_mm_movemask_pd(_mm_cmple_pd(v0.vec1, v1.vec1)) << 2) | (_mm_movemask_pd(_mm_cmple_pd(v0.vec2, v1.vec2)) << 4) | (_mm_movemask_pd(_mm_cmple_pd(v0.vec3, v1.vec3)) << 6);
		#else
			return ((uint32_t)(v0.x0 <= v1.x0) << 0) | ((uint32_t)(v0.y0 <= v1.y0) << 1) | ((uint32_t)(v0.z0 <= v1.z0) << 2) | ((uint32_t)(v0.w0 <= v1.w0) << 3) | ((uint32_t)(v0.x1 <= v1.x1) << 4) | ((uint32_t)(v0.y1 <= v1.y1) << 5) | ((uint32_t)(v0.z1 <= v1.z1) << 6) | ((uint32_t)(v0.w1 <= v1.w1) << 7);
		#endif
	}
	TS_INLINE uint32_t operator>=(const float64x8_t &v0, const float64x8_t &v1) {
		#if TS_AVX >= 1
			return _mm256_movemask_pd(_mm256_cmp_pd(v0.vec0, v1.vec0, _CMP_GE_OQ)) | (_mm256_movemask_pd(_mm256_cmp_pd(v0.vec1, v1.vec1, _CMP_GE_OQ)) << 4);
		#elif TS_SSE >= 2
			return _mm_movemask_pd(_mm_cmpge_pd(v0.vec0, v1.vec0)) | (_mm_movemask_pd(_mm_cmpge_pd(v0.vec1, v1.vec1)) << 2) | (_mm_movemask_pd(_mm_cmpge_pd(v0.vec2, v1.vec2)) << 4) | (_mm_movemask_pd(_mm_cmpge_pd(v0.vec3, v1.vec3)) << 6);
		#else
			return ((uint32_t)(v0.x0 >= v1.x0) << 0) | ((uint32_t)(v0.y0 >= v1.y0) << 1) | ((uint32_t)(v0.z0 >= v1.z0) << 2) | ((uint32_t)(v0.w0 >= v1.w0) << 3) | ((uint32_t)(v0.x1 >= v1.x1) << 4) | ((uint32_t)(v0.y1 >= v1.y1) << 5) | ((uint32_t)(v0.z1 >= v1.z1) << 6) | ((uint32_t)(v0.w1 >= v1.w1) << 7);
		#endif
	}
	TS_INLINE uint32_t operator==(const float64x8_t &v0, const float64x8_t &v1) {
		#if TS_AVX >= 1
			return _mm256_movemask_pd(_mm256_cmp_pd(v0.vec0, v1.vec0, _CMP_EQ_OQ)) | (_mm256_movemask_pd(_mm256_cmp_pd(v0.vec1, v1.vec1, _CMP_EQ_OQ)) << 4);
		#elif TS_SSE >= 2
			return _mm_movemask_pd(_mm_cmpeq_pd(v0.vec0, v1.vec0)) | (_mm_movemask_pd(_mm_cmpeq_pd(v0.vec1, v1.vec1)) << 2) | (_mm_movemask_pd(_mm_cmpeq_pd(v0.vec2, v1.vec2)) << 4) | (_mm_movemask_pd(_mm_cmpeq_pd(v0.vec3, v1.vec3)) << 6);
		#else
			return ((uint32_t)(v0.x0 == v1.x0) << 0) | ((uint32_t)(v0.y0 == v1.y0) << 1) | ((uint32_t)(v0.z0 == v1.z0) << 2) | ((uint32_t)(v0.w0 == v1.w0) << 3) | ((uint32_t)(v0.x1 == v1.x1) << 4) | ((uint32_t)(v0.y1 == v1.y1) << 5) | ((uint32_t)(v0.z1 == v1.z1) << 6) | ((uint32_t)(v0.w1 == v1.w1) << 7);
		#endif
	}
	TS_INLINE uint32_t operator!=(const float64x8_t &v0, const float64x8_t &v1) {
		#if TS_AVX >= 1
			return _mm256_movemask_pd(_mm256_cmp_pd(v0.vec0, v1.vec0, _CMP_NEQ_OQ)) | (_mm256_movemask_pd(_mm256_cmp_pd(v0.vec1, v1.vec1, _CMP_NEQ_OQ)) << 4);
		#elif TS_SSE >= 2
			return _mm_movemask_pd(_mm_cmpneq_pd(v0.vec0, v1.vec0)) | (_mm_movemask_pd(_mm_cmpneq_pd(v0.vec1, v1.vec1)) << 2) | (_mm_movemask_pd(_mm_cmpneq_pd(v0.vec2, v1.vec2)) << 4) | (_mm_movemask_pd(_mm_cmpneq_pd(v0.vec3, v1.vec3)) << 6);
		#else
			return ((uint32_t)(v0.x0 != v1.x0) << 0) | ((uint32_t)(v0.y0 != v1.y0) << 1) | ((uint32_t)(v0.z0 != v1.z0) << 2) | ((uint32_t)(v0.w0 != v1.w0) << 3) | ((uint32_t)(v0.x1 != v1.x1) << 4) | ((uint32_t)(v0.y1 != v1.y1) << 5) | ((uint32_t)(v0.z1 != v1.z1) << 6) | ((uint32_t)(v0.w1 != v1.w1) << 7);
		#endif
	}
	
	/// min/max functions
	TS_INLINE float64x8_t min(const float64x8_t &v0, const float64x8_t &v1) {
		#if TS_AVX >= 1
			return float64x8_t(_mm256_min_pd(v0.vec0, v1.vec0), _mm256_min_pd(v0.vec1, v1.vec1));
		#elif TS_SSE >= 2
			return float64x8_t(_mm_min_pd(v0.vec0, v1.vec0), _mm_min_pd(v0.vec1, v1.vec1), _mm_min_pd(v0.vec2, v1.vec2), _mm_min_pd(v0.vec3, v1.vec3));
		#else
			return float64x8_t(min(v0.x0, v1.x0), min(v0.y0, v1.y0), min(v0.z0, v1.z0), min(v0.w0, v1.w0), min(v0.x1, v1.x1), min(v0.y1, v1.y1), min(v0.z1, v1.z1), min(v0.w1, v1.w1));
		#endif
	}
	TS_INLINE float64x8_t max(const float64x8_t &v0, const float64x8_t &v1) {
		#if TS_AVX >= 1
			return float64x8_t(_mm256_max_pd(v0.vec0, v1.vec0), _mm256_max_pd(v0.vec1, v1.vec1));
		#elif TS_SSE >= 2
			return float64x8_t(_mm_max_pd(v0.vec0, v1.vec0), _mm_max_pd(v0.vec1, v1.vec1), _mm_max_pd(v0.vec2, v1.vec2), _mm_max_pd(v0.vec3, v1.vec3));
		#else
			return float64x8_t(max(v0.x0, v1.x0), max(v0.y0, v1.y0), max(v0.z0, v1.z0), max(v0.w0, v1.w0), max(v0.x1, v1.x1), max(v0.y1, v1.y1), max(v0.z1, v1.z1), max(v0.w1, v1.w1));
		#endif
	}
	
	/// range functions
	TS_INLINE float64x8_t saturate(const float64x8_t &v) {
		return min(max(v, float64x8_t(0.0)), float64x8_t(1.0));
	}
	TS_INLINE float64x8_t clamp(const float64x8_t &v, float64_t v0, float64_t v1) {
		return min(max(v, float64x8_t(v0)), float64x8_t(v1));
	}
	TS_INLINE float64x8_t clamp(const float64x8_t &v, const float64x8_t &v0, const float64x8_t &v1) {
		return min(max(v, v0), v1);
	}
	
	/// select functions
	TS_INLINE float64x8_t select(const float64x8_t &v0, const float64x8_t &v1, const float64x8_t &s) {
		#if TS_AVX >= 1
			return float64x8_t(_mm256_blendv_pd(v0.vec0, v1.vec0, s.vec0),_mm256_blendv_pd(v0.vec1, v1.vec1, s.vec1) );
		#elif TS_SSE >= 2
			return float64x8_t(_mm_xor_pd(v0.vec0, _mm_and_pd(_mm_xor_pd(v0.vec0, v1.vec0), _mm_cmplt_pd(s.vec0, _mm_setzero_pd()))), _mm_xor_pd(v0.vec1, _mm_and_pd(_mm_xor_pd(v0.vec1, v1.vec1), _mm_cmplt_pd(s.vec1, _mm_setzero_pd()))), _mm_xor_pd(v0.vec2, _mm_and_pd(_mm_xor_pd(v0.vec2, v1.vec2), _mm_cmplt_pd(s.vec2, _mm_setzero_pd()))), _mm_xor_pd(v0.vec3, _mm_and_pd(_mm_xor_pd(v0.vec3, v1.vec3), _mm_cmplt_pd(s.vec3, _mm_setzero_pd()))));
		#else
			return float64x8_t(select(v0.x0, v1.x0, s.x0), select(v0.y0, v1.y0, s.y0), select(v0.z0, v1.z0, s.z0), select(v0.w0, v1.w0, s.w0), select(v0.x1, v1.x1, s.x1), select(v0.y1, v1.y1, s.y1), select(v0.z1, v1.z1, s.z1), select(v0.w1, v1.w1, s.w1));
		#endif
	}
	TS_INLINE float64x8_t select(const float64x8_t &v0, const float64x8_t &v1, float64_t s) {
		return select(v0, v1, float64x8_t(s));
	}
	
	/// math functions
	TS_INLINE float64x8_t sqrt(const float64x8_t &v) {
		#if TS_AVX >= 1
			return float64x8_t(_mm256_sqrt_pd(v.vec0), _mm256_sqrt_pd(v.vec1));
		#elif TS_SSE >= 2
			return float64x8_t(_mm_sqrt_pd(v.vec0), _mm_sqrt_pd(v.vec1), _mm_sqrt_pd(v.vec2), _mm_sqrt_pd(v.vec3));
		#else
			return float64x8_t(sqrt(v.x0), sqrt(v.y0), sqrt(v.z0), sqrt(v.w0), sqrt(v.x1), sqrt(v.y1), sqrt(v.z1), sqrt(v.w1));
		#endif
	}
	
	/// vector functions
	TS_INLINE float64x8_t lerp(const float64x8_t &v0, const float64x8_t &v1, float64_t k) {
		#if TS_AVX >= 1
			__m256d temp = _mm256_set1_pd(k);
			return float64x8_t(_mm256_add_pd(v0.vec0, _mm256_mul_pd(_mm256_sub_pd(v1.vec0, v0.vec0), temp)), _mm256_add_pd(v0.vec1, _mm256_mul_pd(_mm256_sub_pd(v1.vec1, v0.vec1), temp)));
		#elif TS_SSE >= 2
			__m128d temp = _mm_set1_pd(k);
			return float64x8_t(_mm_add_pd(v0.vec0, _mm_mul_pd(_mm_sub_pd(v1.vec0, v0.vec0), temp)), _mm_add_pd(v0.vec1, _mm_mul_pd(_mm_sub_pd(v1.vec1, v0.vec1), temp)), _mm_add_pd(v0.vec2, _mm_mul_pd(_mm_sub_pd(v1.vec2, v0.vec2), temp)), _mm_add_pd(v0.vec3, _mm_mul_pd(_mm_sub_pd(v1.vec3, v0.vec3), temp)));
		#else
			return float64x8_t(lerp(v0.x0, v1.x0, k), lerp(v0.y0, v1.y0, k), lerp(v0.z0, v1.z0, k), lerp(v0.w0, v1.w0, k), lerp(v0.x1, v1.x1, k), lerp(v0.y1, v1.y1, k), lerp(v0.z1, v1.z1, k), lerp(v0.w1, v1.w1, k));
		#endif
	}
	
	/*****************************************************************************\
	 *
	 * int16x8_t
	 *
	\*****************************************************************************/
	
	/**
	 * Vector of eight int16_t components
	 */
	#if TS_AVX >= 1
		TS_INLINE int16x8_t::int16x8_t(const int32x8_t &v) : vec(_mm_packs_epi32(_mm256_extractf128_si256(v.vec, 0), _mm256_extractf128_si256(v.vec, 1))) { }
		TS_INLINE int16x8_t::int16x8_t(const int32x4_t &v0, const int32x4_t &v1) : vec(_mm_packs_epi32(v0.vec, v1.vec)) { }
	#elif TS_SSE >= 2
		TS_INLINE int16x8_t::int16x8_t(const int32x8_t &v) : vec(_mm_packs_epi32(v.vec0, v.vec1)) { }
		TS_INLINE int16x8_t::int16x8_t(const int32x4_t &v0, const int32x4_t &v1) : vec(_mm_packs_epi32(v0.vec, v1.vec)) { }
	#elif TS_NEON
		TS_INLINE int16x8_t::int16x8_t(const int32x8_t &v) : vec(vcombine_s16(vqmovn_s32(v.vec0), vqmovn_s32(v.vec1))) { }
		TS_INLINE int16x8_t::int16x8_t(const int32x4_t &v0, const int32x4_t &v1) : vec(vcombine_s16(vqmovn_s32(v0.vec), vqmovn_s32(v1.vec))) { }
	#else
		TS_INLINE int16x8_t::int16x8_t(const int32x8_t &v) : x0((int16_t)v.x0), y0((int16_t)v.y0), z0((int16_t)v.z0), w0((int16_t)v.w0), x1((int16_t)v.x1), y1((int16_t)v.y1), z1((int16_t)v.z1), w1((int16_t)v.w1) { }
		TS_INLINE int16x8_t::int16x8_t(const int32x4_t &v0, const int32x4_t &v1) : x0((int16_t)v0.x), y0((int16_t)v0.y), z0((int16_t)v0.z), w0((int16_t)v0.w), x1((int16_t)v1.x), y1((int16_t)v1.y), z1((int16_t)v1.z), w1((int16_t)v1.w) { }
	#endif
	
	/// cast vector data
	TS_INLINE int32x4_t int16x8_t::asi32x4() const {
		#if TS_SSE >= 2
			return int32x4_t(vec);
		#elif TS_NEON
			return int32x4_t(vreinterpretq_s32_s16(vec));
		#else
			return int32x4_t((int32_t*)v);
		#endif
	}
	TS_INLINE uint16x8_t int16x8_t::asu16x8() const {
		#if TS_SSE >= 2
			return uint16x8_t(vec);
		#elif TS_NEON
			return uint16x8_t(vreinterpretq_u16_s16(vec));
		#else
			return uint16x8_t((uint16_t*)v);
		#endif
	}
	TS_INLINE uint32x4_t int16x8_t::asu32x4() const {
		#if TS_SSE >= 2
			return uint32x4_t(vec);
		#elif TS_NEON
			return uint32x4_t(vreinterpretq_u32_s16(vec));
		#else
			return uint32x4_t((uint32_t*)v);
		#endif
	}
	TS_INLINE float16x8_t int16x8_t::asf16x8() const {
		#if TS_SSE >= 2
			return float16x8_t(vec);
		#elif TS_NEON
			return float16x8_t(vreinterpretq_u16_s16(vec));
		#else
			return float16x8_t((float16_t*)v);
		#endif
	}
	TS_INLINE float32x4_t int16x8_t::asf32x4() const {
		#if TS_SSE >= 2
			return float32x4_t(_mm_castsi128_ps(vec));
		#elif TS_NEON
			return float32x4_t(vreinterpretq_f32_s16(vec));
		#else
			return float32x4_t((float32_t*)v);
		#endif
	}
	
	/// swizzle vector
	TS_INLINE int32x4_t int16x8_t::xyzw0() const {
		#if TS_SSE >= 4
			return int32x4_t(_mm_cvtepi16_epi32(vec));
		#elif TS_NEON
			return int32x4_t(vmovl_s16(vget_low_s16(vec)));
		#else
			return int32x4_t(x0, y0, z0, w0);
		#endif
	}
	TS_INLINE int32x4_t int16x8_t::xyzw1() const {
		#if TS_SSE >= 4
			return int32x4_t(_mm_cvtepi16_epi32(_mm_swizzle_epi32(vec, Z, W, Z, W)));
		#elif TS_NEON
			return int32x4_t(vmovl_s16(vget_high_s16(vec)));
		#else
			return int32x4_t(x1, y1, z1, w1);
		#endif
	}
	
	/*****************************************************************************\
	 *
	 * int32x4_t
	 *
	\*****************************************************************************/
	
	/**
	 * Vector of four int32_t components
	 */
	#if TS_AVX >= 1
		TS_INLINE int32x4_t::int32x4_t(const uint32x4_t &v) : vec(v.vec) { }
		TS_INLINE int32x4_t::int32x4_t(const float32x4_t &v) : vec(_mm_cvtps_epi32(v.vec)) { }
		TS_INLINE int32x4_t::int32x4_t(const float64x4_t &v) : vec(_mm256_cvtpd_epi32(v.vec)) { }
	#elif TS_SSE >= 2
		TS_INLINE int32x4_t::int32x4_t(const uint32x4_t &v) : vec(v.vec) { }
		TS_INLINE int32x4_t::int32x4_t(const float32x4_t &v) : vec(_mm_cvtps_epi32(v.vec)) { }
		TS_INLINE int32x4_t::int32x4_t(const float64x4_t &v) : vec(_mm_castps_si128(_mm_swizzle_ps(_mm_castsi128_ps(_mm_cvtpd_epi32(v.vec0)), _mm_castsi128_ps(_mm_cvtpd_epi32(v.vec1)), X, Y, X, Y))) { }
	#elif TS_NEON
		TS_INLINE int32x4_t::int32x4_t(const uint32x4_t &v) : vec(vreinterpretq_s32_u32(v.vec)) { }
		TS_INLINE int32x4_t::int32x4_t(const float32x4_t &v) : vec(vcvtq_s32_f32(v.vec)) { }
		TS_INLINE int32x4_t::int32x4_t(const float64x4_t &v) : x((int32_t)v.x), y((int32_t)v.y), z((int32_t)v.z), w((int32_t)v.w) { }
	#else
		TS_INLINE int32x4_t::int32x4_t(const uint32x4_t &v) : x((int32_t)v.x), y((int32_t)v.y), z((int32_t)v.z), w((int32_t)v.w) { }
		TS_INLINE int32x4_t::int32x4_t(const float32x4_t &v) : x((int32_t)v.x), y((int32_t)v.y), z((int32_t)v.z), w((int32_t)v.w) { }
		TS_INLINE int32x4_t::int32x4_t(const float64x4_t &v) : x((int32_t)v.x), y((int32_t)v.y), z((int32_t)v.z), w((int32_t)v.w) { }
	#endif
	
	/// cast vector data
	TS_INLINE uint16x8_t int32x4_t::asu16x8() const {
		#if TS_SSE >= 2
			return uint16x8_t(vec);
		#elif TS_NEON
			return uint16x8_t(vreinterpretq_u16_s32(vec));
		#else
			return uint16x8_t((uint16_t*)v);
		#endif
	}
	TS_INLINE uint32x4_t int32x4_t::asu32x4() const {
		#if TS_SSE >= 2
			return uint32x4_t(vec);
		#elif TS_NEON
			return uint32x4_t(vreinterpretq_u32_s32(vec));
		#else
			return uint32x4_t((uint32_t*)v);
		#endif
	}
	TS_INLINE float16x8_t int32x4_t::asf16x8() const {
		#if TS_SSE >= 2
			return float16x8_t(vec);
		#elif TS_NEON
			return float16x8_t(vreinterpretq_u16_s32(vec));
		#else
			return float16x8_t((float16_t*)v);
		#endif
	}
	TS_INLINE float32x4_t int32x4_t::asf32x4() const {
		#if TS_SSE >= 2
			return float32x4_t(_mm_castsi128_ps(vec));
		#elif TS_NEON
			return float32x4_t(vreinterpretq_f32_s32(vec));
		#else
			return float32x4_t((float32_t*)v);
		#endif
	}
	
	/*****************************************************************************\
	 *
	 * int32x8_t
	 *
	\*****************************************************************************/
	
	/**
	 * Vector of eight int32_t components
	 */
	#if TS_AVX >= 1
		TS_INLINE int32x8_t::int32x8_t(const uint32x8_t &v) : vec(v.vec) { }
		TS_INLINE int32x8_t::int32x8_t(const float32x8_t &v) : vec(_mm256_cvtps_epi32(v.vec)) { }
		TS_INLINE int32x8_t::int32x8_t(const float64x8_t &v) : vec(_mm256_setr_m128i(_mm256_cvtpd_epi32(v.vec0), _mm256_cvtpd_epi32(v.vec1))) { }
	#elif TS_SSE >= 2
		TS_INLINE int32x8_t::int32x8_t(const uint32x8_t &v) : vec0(v.vec0), vec1(v.vec1) { }
		TS_INLINE int32x8_t::int32x8_t(const float32x8_t &v) : vec0(_mm_cvtps_epi32(v.vec0)), vec1(_mm_cvtps_epi32(v.vec1)) { }
		TS_INLINE int32x8_t::int32x8_t(const float64x8_t &v) : vec0(_mm_castps_si128(_mm_swizzle_ps(_mm_castsi128_ps(_mm_cvtpd_epi32(v.vec0)), _mm_castsi128_ps(_mm_cvtpd_epi32(v.vec1)), X, Y, X, Y))), vec1(_mm_castps_si128(_mm_swizzle_ps(_mm_castsi128_ps(_mm_cvtpd_epi32(v.vec2)), _mm_castsi128_ps(_mm_cvtpd_epi32(v.vec3)), X, Y, X, Y))) { }
	#elif TS_NEON
		TS_INLINE int32x8_t::int32x8_t(const uint32x8_t &v) : vec0(vreinterpretq_s32_u32(v.vec0)), vec1(vreinterpretq_s32_u32(v.vec1)) { }
		TS_INLINE int32x8_t::int32x8_t(const float32x8_t &v) : vec0(vcvtq_s32_f32(v.vec0)), vec1(vcvtq_s32_f32(v.vec1)) { }
		TS_INLINE int32x8_t::int32x8_t(const float64x8_t &v) : x0((int32_t)v.x0), y0((int32_t)v.y0), z0((int32_t)v.z0), w0((int32_t)v.w0), x1((int32_t)v.x1), y1((int32_t)v.y1), z1((int32_t)v.z1), w1((int32_t)v.w1) { }
	#else
		TS_INLINE int32x8_t::int32x8_t(const uint32x8_t &v) : x0((int32_t)v.x0), y0((int32_t)v.y0), z0((int32_t)v.z0), w0((int32_t)v.w0), x1((int32_t)v.x1), y1((int32_t)v.y1), z1((int32_t)v.z1), w1((int32_t)v.w1) { }
		TS_INLINE int32x8_t::int32x8_t(const float32x8_t &v) : x0((int32_t)v.x0), y0((int32_t)v.y0), z0((int32_t)v.z0), w0((int32_t)v.w0), x1((int32_t)v.x1), y1((int32_t)v.y1), z1((int32_t)v.z1), w1((int32_t)v.w1) { }
		TS_INLINE int32x8_t::int32x8_t(const float64x8_t &v) : x0((int32_t)v.x0), y0((int32_t)v.y0), z0((int32_t)v.z0), w0((int32_t)v.w0), x1((int32_t)v.x1), y1((int32_t)v.y1), z1((int32_t)v.z1), w1((int32_t)v.w1) { }
	#endif
	
	/// cast vector data
	TS_INLINE uint32x8_t int32x8_t::asu32x8() const {
		#if TS_AVX >= 1
			return uint32x8_t(vec);
		#elif TS_SSE >= 1
			return uint32x8_t(vec0, vec1);
		#elif TS_NEON
			return uint32x8_t(vreinterpretq_u32_s32(vec0), vreinterpretq_u32_s32(vec1));
		#else
			return uint32x8_t((uint32_t*)v);
		#endif
	}
	TS_INLINE float32x8_t int32x8_t::asf32x8() const {
		#if TS_AVX >= 1
			return float32x8_t(_mm256_castsi256_ps(vec));
		#elif TS_SSE >= 1
			return float32x8_t(_mm_castsi128_ps(vec0), _mm_castsi128_ps(vec1));
		#elif TS_NEON
			return float32x8_t(vreinterpretq_f32_s32(vec0), vreinterpretq_f32_s32(vec1));
		#else
			return float32x8_t((float32_t*)v);
		#endif
	}
	
	/*****************************************************************************\
	 *
	 * uint16x8_t
	 *
	\*****************************************************************************/
	
	/**
	 * Vector of eight uint16_t components
	 */
	#if TS_AVX >= 1
		TS_INLINE uint16x8_t::uint16x8_t(const uint32x8_t &v) : vec(_mm_packus_epi32(_mm256_extractf128_si256(v.vec, 0), _mm256_extractf128_si256(v.vec, 1))) { }
		TS_INLINE uint16x8_t::uint16x8_t(const uint32x4_t &v0, const uint32x4_t &v1) : vec(_mm_packus_epi32(v0.vec, v1.vec)) { }
	#elif TS_SSE >= 4
		TS_INLINE uint16x8_t::uint16x8_t(const uint32x8_t &v) : vec(_mm_packus_epi32(v.vec0, v.vec1)) { }
		TS_INLINE uint16x8_t::uint16x8_t(const uint32x4_t &v0, const uint32x4_t &v1) : vec(_mm_packus_epi32(v0.vec, v1.vec)) { }
	#elif TS_NEON
		TS_INLINE uint16x8_t::uint16x8_t(const uint32x8_t &v) : vec(vcombine_u16(vqmovn_u32(v.vec0), vqmovn_u32(v.vec1))) { }
		TS_INLINE uint16x8_t::uint16x8_t(const uint32x4_t &v0, const uint32x4_t &v1) : vec(vcombine_u16(vqmovn_u32(v0.vec), vqmovn_u32(v1.vec))) { }
	#else
		TS_INLINE uint16x8_t::uint16x8_t(const uint32x8_t &v) : x0((uint16_t)v.x0), y0((uint16_t)v.y0), z0((uint16_t)v.z0), w0((uint16_t)v.w0), x1((uint16_t)v.x1), y1((uint16_t)v.y1), z1((uint16_t)v.z1), w1((uint16_t)v.w1) { }
		TS_INLINE uint16x8_t::uint16x8_t(const uint32x4_t &v0, const uint32x4_t &v1) : x0((uint16_t)v0.x), y0((uint16_t)v0.y), z0((uint16_t)v0.z), w0((uint16_t)v0.w), x1((uint16_t)v1.x), y1((uint16_t)v1.y), z1((uint16_t)v1.z), w1((uint16_t)v1.w) { }
	#endif
	
	/// cast vector data
	TS_INLINE uint32x4_t uint16x8_t::asu32x4() const {
		#if TS_SSE >= 2
			return uint32x4_t(vec);
		#elif TS_NEON
			return uint32x4_t(vreinterpretq_u32_u16(vec));
		#else
			return uint32x4_t((uint32_t*)v);
		#endif
	}
	TS_INLINE float16x8_t uint16x8_t::asf16x8() const {
		#if TS_SSE >= 2
			return float16x8_t(vec);
		#elif TS_NEON
			return float16x8_t(vec);
		#else
			return float16x8_t((float16_t*)v);
		#endif
	}
	TS_INLINE float32x4_t uint16x8_t::asf32x4() const {
		#if TS_SSE >= 2
			return float32x4_t(_mm_castsi128_ps(vec));
		#elif TS_NEON
			return float32x4_t(vreinterpretq_f32_u16(vec));
		#else
			return float32x4_t((float32_t*)v);
		#endif
	}
	
	/// swizzle vector
	TS_INLINE uint32x4_t uint16x8_t::xyzw0() const {
		#if TS_SSE >= 4
			return uint32x4_t(_mm_cvtepu16_epi32(vec));
		#elif TS_NEON
			return uint32x4_t(vmovl_u16(vget_low_u16(vec)));
		#else
			return uint32x4_t(x0, y0, z0, w0);
		#endif
	}
	TS_INLINE uint32x4_t uint16x8_t::xyzw1() const {
		#if TS_SSE >= 4
			return uint32x4_t(_mm_cvtepu16_epi32(_mm_swizzle_epi32(vec, Z, W, Z, W)));
		#elif TS_NEON
			return uint32x4_t(vmovl_u16(vget_high_u16(vec)));
		#else
			return uint32x4_t(x1, y1, z1, w1);
		#endif
	}
	
	/*****************************************************************************\
	 *
	 * uint32x4_t
	 *
	\*****************************************************************************/
	
	/**
	 * Vector of four uint32_t components
	 */
	#if TS_AVX >= 1
		TS_INLINE uint32x4_t::uint32x4_t(const int32x4_t &v) : vec(v.vec) { }
		TS_INLINE uint32x4_t::uint32x4_t(const float32x4_t &v) : vec(_mm_cvtps_epi32(v.vec)) { }
		TS_INLINE uint32x4_t::uint32x4_t(const float64x4_t &v) : vec(_mm256_cvtpd_epi32(v.vec)) { }
	#elif TS_SSE >= 2
		TS_INLINE uint32x4_t::uint32x4_t(const int32x4_t &v) : vec(v.vec) { }
		TS_INLINE uint32x4_t::uint32x4_t(const float32x4_t &v) : vec(_mm_cvtps_epi32(v.vec)) { }
		TS_INLINE uint32x4_t::uint32x4_t(const float64x4_t &v) : vec(_mm_castps_si128(_mm_swizzle_ps(_mm_castsi128_ps(_mm_cvtpd_epi32(v.vec0)), _mm_castsi128_ps(_mm_cvtpd_epi32(v.vec1)), X, Y, X, Y))) { }
	#elif TS_NEON
		TS_INLINE uint32x4_t::uint32x4_t(const int32x4_t &v) : vec(vreinterpretq_u32_s32(v.vec)) { }
		TS_INLINE uint32x4_t::uint32x4_t(const float32x4_t &v) : vec(vcvtq_u32_f32(v.vec)) { }
		TS_INLINE uint32x4_t::uint32x4_t(const float64x4_t &v) : x((uint32_t)v.x), y((uint32_t)v.y), z((uint32_t)v.z), w((uint32_t)v.w) { }
	#else
		TS_INLINE uint32x4_t::uint32x4_t(const int32x4_t &v) : x((uint32_t)v.x), y((uint32_t)v.y), z((uint32_t)v.z), w((uint32_t)v.w) { }
		TS_INLINE uint32x4_t::uint32x4_t(const float32x4_t &v) : x((uint32_t)v.x), y((uint32_t)v.y), z((uint32_t)v.z), w((uint32_t)v.w) { }
		TS_INLINE uint32x4_t::uint32x4_t(const float64x4_t &v) : x((uint32_t)v.x), y((uint32_t)v.y), z((uint32_t)v.z), w((uint32_t)v.w) { }
	#endif
	
	/// cast vector data
	TS_INLINE float16x8_t uint32x4_t::asf16x8() const {
		#if TS_SSE >= 2
			return float16x8_t(vec);
		#elif TS_NEON
			return float16x8_t(vreinterpretq_u16_u32(vec));
		#else
			return float16x8_t((float16_t*)v);
		#endif
	}
	TS_INLINE float32x4_t uint32x4_t::asf32x4() const {
		#if TS_SSE >= 2
			return float32x4_t(_mm_castsi128_ps(vec));
		#elif TS_NEON
			return float32x4_t(vreinterpretq_f32_u32(vec));
		#else
			return float32x4_t((float32_t*)v);
		#endif
	}
	
	/*****************************************************************************\
	 *
	 * uint32x8_t
	 *
	\*****************************************************************************/
	
	/**
	 * Vector of eight uint32_t components
	 */
	#if TS_AVX >= 1
		TS_INLINE uint32x8_t::uint32x8_t(const int32x8_t &v) : vec(v.vec) { }
		TS_INLINE uint32x8_t::uint32x8_t(const float32x8_t &v) : vec(_mm256_cvtps_epi32(v.vec)) { }
		TS_INLINE uint32x8_t::uint32x8_t(const float64x8_t &v) : vec(_mm256_setr_m128i(_mm256_cvtpd_epi32(v.vec0), _mm256_cvtpd_epi32(v.vec1))) { }
	#elif TS_SSE >= 2
		TS_INLINE uint32x8_t::uint32x8_t(const int32x8_t &v) : vec0(v.vec0), vec1(v.vec1) { }
		TS_INLINE uint32x8_t::uint32x8_t(const float32x8_t &v) : vec0(_mm_cvtps_epi32(v.vec0)), vec1(_mm_cvtps_epi32(v.vec1)) { }
		TS_INLINE uint32x8_t::uint32x8_t(const float64x8_t &v) : vec0(_mm_castps_si128(_mm_swizzle_ps(_mm_castsi128_ps(_mm_cvtpd_epi32(v.vec0)), _mm_castsi128_ps(_mm_cvtpd_epi32(v.vec1)), X, Y, X, Y))), vec1(_mm_castps_si128(_mm_swizzle_ps(_mm_castsi128_ps(_mm_cvtpd_epi32(v.vec2)), _mm_castsi128_ps(_mm_cvtpd_epi32(v.vec3)), X, Y, X, Y))) { }
	#elif TS_NEON
		TS_INLINE uint32x8_t::uint32x8_t(const int32x8_t &v) : vec0(vreinterpretq_u32_s32(v.vec0)), vec1(vreinterpretq_u32_s32(v.vec1)) { }
		TS_INLINE uint32x8_t::uint32x8_t(const float32x8_t &v) : vec0(vcvtq_u32_f32(v.vec0)), vec1(vcvtq_u32_f32(v.vec1)) { }
		TS_INLINE uint32x8_t::uint32x8_t(const float64x8_t &v) : x0((uint32_t)v.x0), y0((uint32_t)v.y0), z0((uint32_t)v.z0), w0((uint32_t)v.w0), x1((uint32_t)v.x1), y1((uint32_t)v.y1), z1((uint32_t)v.z1), w1((uint32_t)v.w1) { }
	#else
		TS_INLINE uint32x8_t::uint32x8_t(const int32x8_t &v) : x0((uint32_t)v.x0), y0((uint32_t)v.y0), z0((uint32_t)v.z0), w0((uint32_t)v.w0), x1((uint32_t)v.x1), y1((uint32_t)v.y1), z1((uint32_t)v.z1), w1((uint32_t)v.w1) { }
		TS_INLINE uint32x8_t::uint32x8_t(const float32x8_t &v) : x0((uint32_t)v.x0), y0((uint32_t)v.y0), z0((uint32_t)v.z0), w0((uint32_t)v.w0), x1((uint32_t)v.x1), y1((uint32_t)v.y1), z1((uint32_t)v.z1), w1((uint32_t)v.w1) { }
		TS_INLINE uint32x8_t::uint32x8_t(const float64x8_t &v) : x0((uint32_t)v.x0), y0((uint32_t)v.y0), z0((uint32_t)v.z0), w0((uint32_t)v.w0), x1((uint32_t)v.x1), y1((uint32_t)v.y1), z1((uint32_t)v.z1), w1((uint32_t)v.w1) { }
	#endif
	
	/// cast vector data
	TS_INLINE int32x8_t uint32x8_t::asi32x8() const {
		#if TS_AVX >= 1
			return int32x8_t(vec);
		#elif TS_SSE >= 1
			return int32x8_t(vec0, vec1);
		#elif TS_NEON
			return int32x8_t(vreinterpretq_s32_u32(vec0), vreinterpretq_s32_u32(vec1));
		#else
			return int32x8_t((int32_t*)v);
		#endif
	}
	TS_INLINE float32x8_t uint32x8_t::asf32x8() const {
		#if TS_AVX >= 1
			return float32x8_t(_mm256_castsi256_ps(vec));
		#elif TS_SSE >= 1
			return float32x8_t(_mm_castsi128_ps(vec0), _mm_castsi128_ps(vec1));
		#elif TS_NEON
			return float32x8_t(vreinterpretq_f32_u32(vec0), vreinterpretq_f32_u32(vec1));
		#else
			return float32x8_t((float32_t*)v);
		#endif
	}
	
	/*****************************************************************************\
	 *
	 * float16x4_t
	 *
	\*****************************************************************************/
	
	/**
	 * Vector of four float16_t components
	 */
	#if TS_AVX >= 1 && TS_X64
		TS_INLINE float16x4_t::float16x4_t(const float32x4_t &v) : vec((uint64_t)_mm_extract_epi64(_mm_cvtps_ph(v.vec, 0), 0)) { }
	#elif TS_NEON && TS_ARM64
		TS_INLINE float16x4_t::float16x4_t(const float32x4_t &v) : vec((::uint16x4_t)vcvt_f16_f32(v.vec)) { }
	#else
		TS_INLINE float16x4_t::float16x4_t(const float32x4_t &v) : f16 { float16_t(v.x), float16_t(v.y), float16_t(v.z), float16_t(v.w) } { }
	#endif
	
	/*****************************************************************************\
	 *
	 * float16x8_t
	 *
	\*****************************************************************************/
	
	/**
	 * Vector of eight float16_t components
	 */
	#if TS_AVX >= 1
		TS_INLINE float16x8_t::float16x8_t(const float32x8_t &v) : vec(_mm256_cvtps_ph(v.vec, 0)) { }
	#elif TS_NEON && TS_ARM64
		TS_INLINE float16x8_t::float16x8_t(const float32x8_t &v) : vec(vcombine_u16((::uint16x4_t)vcvt_f16_f32(v.vec0), (::uint16x4_t)vcvt_f16_f32(v.vec1))) { }
	#else
		TS_INLINE float16x8_t::float16x8_t(const float32x8_t &v) : f16 { float16_t(v.x0), float16_t(v.y0), float16_t(v.z0), float16_t(v.w0), float16_t(v.x1), float16_t(v.y1), float16_t(v.z1), float16_t(v.w1) } { }
	#endif
	
	/// cast vector data
	TS_INLINE float32x4_t float16x8_t::asf32x4() const {
		#if TS_SSE >= 2
			return float32x4_t(_mm_castsi128_ps(vec));
		#elif TS_NEON
			return float32x4_t(vreinterpretq_f32_u16(vec));
		#else
			return float32x4_t((float32_t*)v);
		#endif
	}
	
	/*****************************************************************************\
	 *
	 * float32x4_t
	 *
	\*****************************************************************************/
	
	/**
	 * Vector of four float32_t components
	 */
	#if TS_AVX >= 1
		TS_INLINE float32x4_t::float32x4_t(const float64x4_t &v) : vec(_mm256_cvtpd_ps(v.vec)) { }
	#elif TS_SSE >= 2
		TS_INLINE float32x4_t::float32x4_t(const float64x4_t &v) : vec(_mm_swizzle_ps(_mm_cvtpd_ps(v.vec0), _mm_cvtpd_ps(v.vec1), X, Y, X, Y)) { }
	#else
		TS_INLINE float32x4_t::float32x4_t(const float64x4_t &v) : x((float32_t)v.x), y((float32_t)v.y), z((float32_t)v.z), w((float32_t)v.w) { }
	#endif
	
	/*****************************************************************************\
	 *
	 * float32x8_t
	 *
	\*****************************************************************************/
	
	/**
	 * Vector of eight float32_t components
	 */
	#if TS_AVX >= 1
		TS_INLINE float32x8_t::float32x8_t(const float64x8_t &v) : vec(_mm256_setr_m128(_mm256_cvtpd_ps(v.vec0), _mm256_cvtpd_ps(v.vec1))) { }
	#elif TS_SSE >= 2
		TS_INLINE float32x8_t::float32x8_t(const float64x8_t &v) : vec0(_mm_swizzle_ps(_mm_cvtpd_ps(v.vec0), _mm_cvtpd_ps(v.vec1), X, Y, X, Y)), vec1(_mm_swizzle_ps(_mm_cvtpd_ps(v.vec2), _mm_cvtpd_ps(v.vec3), X, Y, X, Y)) { }
	#else
		TS_INLINE float32x8_t::float32x8_t(const float64x8_t &v) : x0((float32_t)v.x0), y0((float32_t)v.y0), z0((float32_t)v.z0), w0((float32_t)v.w0), x1((float32_t)v.x1), y1((float32_t)v.y1), z1((float32_t)v.z1), w1((float32_t)v.w1) { }
	#endif
}

#endif /* __TELLUSIM_MATH_SIMD_H__ */

// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

/*
 */
#if HASH_1_1_SHADER
	float p = fract((IN) * 0.1031f);
	p *= p + 33.33f;
	OUT = fract((p + p) * p);
#endif

#if HASH_1_2_SHADER
	vec3 p3 = fract((IN).xyx * 0.1031f);
	p3 += dot(p3, p3.yzx + 33.33f);
	OUT = fract((p3.x + p3.y) * p3.z);
#endif

#if HASH_1_3_SHADER
	vec3 p3 = fract((IN) * 0.1031f);
	p3 += dot(p3, p3.zyx + 33.33f);
	OUT = fract((p3.x + p3.y) * p3.z);
#endif

#if HASH_1_4_SHADER
	vec4 p4 = fract((IN) * vec4(0.1031f, 0.1030f, 0.0973f, 0.1099f));
	p4 += dot(p4, p4.wzxy + 33.33f);
	OUT = fract((p4.x + p4.y) * (p4.z + p4.w));
#endif

/*
 */
#if HASH_2_1_SHADER
	vec3 p3 = fract((IN) * vec3(0.1031f, 0.1030f, 0.0973f));
	p3 += dot(p3, p3.yzx + 33.33f);
	OUT = fract((p3.xx + p3.yz) * p3.zy);
#endif

#if HASH_2_2_SHADER
	vec3 p3 = fract((IN).xyx * vec3(0.1031f, 0.1030f, 0.0973f));
	p3 += dot(p3, p3.yzx + 33.33f);
	OUT = fract((p3.xx+p3.yz) * p3.zy);
#endif

#if HASH_2_3_SHADER
	vec3 p3 = fract((IN) * vec3(0.1031f, 0.1030f, 0.0973f));
	p3 += dot(p3, p3.yzx + 33.33f);
	OUT = fract((p3.xx + p3.yz) * p3.zy);
#endif

/*
 */
#if HASH_3_1_SHADER
	vec3 p3 = fract((IN) * vec3(0.1031f, 0.1030f, 0.0973f));
	p3 += dot(p3, p3.yzx + 33.33f);
	OUT = fract((p3.xxy + p3.yzz) * p3.zyx); 
#endif

#if HASH_3_2_SHADER
	vec3 p3 = fract((IN).xyx * vec3(0.1031f, 0.1030f, 0.0973f));
	p3 += dot(p3, p3.yxz + 33.33f);
	OUT = fract((p3.xxy + p3.yzz) * p3.zyx);
#endif

#if HASH_3_3_SHADER
	vec3 p3 = fract((IN) * vec3(0.1031f, 0.1030f, 0.0973f));
	p3 += dot(p3, p3.yxz + 33.33f);
	OUT = fract((p3.xxy + p3.yxx)*p3.zyx);
#endif

/*
 */
#if HASH_4_1_SHADER
	vec4 p4 = fract((IN) * vec4(0.1031f, 0.1030f, 0.0973f, 0.1099f));
	p4 += dot(p4, p4.wzxy + 33.33f);
	OUT = fract((p4.xxyz + p4.yzzw) * p4.zywx);
#endif

#if HASH_4_2_SHADER
	vec4 p4 = fract((IN).xyxy * vec4(0.1031f, 0.1030f, 0.0973f, 0.1099f);
	p4 += dot(p4, p4.wzxy + 33.33f);
	OUT = fract((p4.xxyz + p4.yzzw) * p4.zywx);
#endif

#if HASH_4_3_SHADER
	vec4 p4 = fract((IN).xyzx * vec4(0.1031f, 0.1030f, 0.0973f, 0.1099f));
	p4 += dot(p4, p4.wzxy + 33.33f);
	OUT = fract((p4.xxyz + p4.yzzw) * p4.zywx);
#endif

#if HASH_4_4_SHADER
	vec4 p4 = fract((IN) * vec4(0.1031f, 0.1030f, 0.0973f, 0.1099f));
	p4 += dot(p4, p4.wzxy + 33.33f);
	OUT = fract((p4.xxyz + p4.yzzw) * p4.zywx);
#endif

/*
 */
#if PERLIN_2_SHADER || PERLIN_3_SHADER
	#define MOD289(NAME) NAME -= floor(NAME * (1.0f / 289.0f)) * 289.0f;
	#define PERM(NAME) NAME *= NAME * 34.0f + 1.0f; MOD289(NAME)
	#define INVERSESQRT(VALUE) (1.79284291400159f - VALUE * 0.85373472095314f)
#endif

/*
 */
#if PERLIN_2_SHADER
	
	vec4 f = fract(IN).xyxy - vec4(0.0f, 0.0f, 1.0f, 1.0f);
	vec4 i = floor(IN).xyxy + vec4(0.0f, 0.0f, 1.0f, 1.0f);
	MOD289(i)
	vec2 p2 = i.xz;
	PERM(p2)
	vec4 p4 = p2.xyxy + i.yyww;
	PERM(p4)
	vec4 x = fract(p4 * (1.0f / 41.0f)) * 2.0f - 1.0f;
	vec4 y = abs(x) - 0.5f;
	x -= floor(x + 0.5f);
	#if CUBIC_SHADER
		vec2 k = f.xy * f.xy * (3.0f - f.xy * 2.0f);
	#else
		vec2 k = f.xy * f.xy * f.xy * (f.xy * (f.xy * 6.0f - 15.0f) + 10.0f);
	#endif
	#if DERIVATIVE_SHADER
		vec2 g0 = vec2(x.x, y.x);
		vec2 g1 = vec2(x.y, y.y);
		vec2 g2 = vec2(x.z, y.z);
		vec2 g3 = vec2(x.w, y.w);
		vec4 ig = INVERSESQRT(vec4(dot(g0, g0), dot(g1, g1), dot(g2, g2), dot(g3, g3)));
		g0 *= ig.x;
		g1 *= ig.y;
		g2 *= ig.z;
		g3 *= ig.w;
		float v0 = dot(g0, vec2(f.x, f.y));
		float v1 = dot(g1, vec2(f.z, f.y));
		float v2 = dot(g2, vec2(f.x, f.w));
		float v3 = dot(g3, vec2(f.z, f.w));
		float v0123 = v0 - v1 - v2 + v3;
		#if CUBIC_SHADER
			vec2 dk = f.xy * (1.0f - f.xy) * 6.0f;
		#else
			vec2 dk = f.xy * f.xy * (f.xy * (f.xy - 2.0f) + 1.0f) * 30.0f;
		#endif
		vec3 OUT = vec3(v0 + (v1 - v0) * k.x + (v2 - v0) * k.y + v0123 * (k.x * k.y),
			g0 + (g1 - g0) * k.x + (g2 - g0) * k.y + (g0 - g1 - g2 + g3) * (k.x * k.y) +
			(v0123 * k.yx + vec2(v1, v2) - v0) * dk);
	#else
		vec4 v4 = (x * f.xzxz + y * f.yyww) * INVERSESQRT(x * x + y * y);
		float OUT = v4.x + (v4.y - v4.x) * k.x + (v4.z - v4.x) * k.y + (v4.x - v4.y - v4.z + v4.w) * (k.x * k.y);
	#endif
	
#elif PERLIN_3_SHADER
	
	vec3 f0 = fract(IN);
	vec3 i0 = floor(IN);
	vec3 f1 = f0 - 1.0f;
	vec3 i1 = i0 + 1.0f;
	MOD289(i0)
	MOD289(i1)
	vec2 p2 = vec2(i0.x, i1.x);
	PERM(p2)
	vec4 p4 = p2.xyxy + vec4(i0.yy, i1.yy);
	PERM(p4)
	vec4 p40 = p4 + i0.z;
	PERM(p40)
	vec4 p41 = p4 + i1.z;
	PERM(p41)
	vec4 gx0 = p40 * (1.0f / 7.0f);
	vec4 gx1 = p41 * (1.0f / 7.0f);
	vec4 gy0 = fract(floor(gx0) * (1.0f / 7.0f)) - 0.5f;
	vec4 gy1 = fract(floor(gx1) * (1.0f / 7.0f)) - 0.5f;
	gx0 = fract(gx0);
	gx1 = fract(gx1);
	vec4 gz0 = 0.5f - abs(gx0) - abs(gy0);
	vec4 gz1 = 0.5f - abs(gx1) - abs(gy1);
	vec4 sz0 = step(gz0, vec4(0.0f));
	vec4 sz1 = step(gz1, vec4(0.0f));
	gx0 -= sz0 * (step(0.0f, gx0) - 0.5f);
	gx1 -= sz1 * (step(0.0f, gx1) - 0.5f);
	gy0 -= sz0 * (step(0.0f, gy0) - 0.5f);
	gy1 -= sz1 * (step(0.0f, gy1) - 0.5f);
	vec3 g0 = vec3(gx0.x, gy0.x, gz0.x);
	vec3 g1 = vec3(gx0.y, gy0.y, gz0.y);
	vec3 g2 = vec3(gx0.z, gy0.z, gz0.z);
	vec3 g3 = vec3(gx0.w, gy0.w, gz0.w);
	vec3 g4 = vec3(gx1.x, gy1.x, gz1.x);
	vec3 g5 = vec3(gx1.y, gy1.y, gz1.y);
	vec3 g6 = vec3(gx1.z, gy1.z, gz1.z);
	vec3 g7 = vec3(gx1.w, gy1.w, gz1.w);
	vec4 ig0 = INVERSESQRT(vec4(dot(g0, g0), dot(g2, g2), dot(g1, g1), dot(g3, g3)));
	vec4 ig1 = INVERSESQRT(vec4(dot(g4, g4), dot(g6, g6), dot(g5, g5), dot(g7, g7)));
	#if DERIVATIVE_SHADER
		g0 *= ig0.x;
		g2 *= ig0.y;
		g1 *= ig0.z;
		g3 *= ig0.w;
		g4 *= ig1.x;
		g6 *= ig1.y;
		g5 *= ig1.z;
		g7 *= ig1.w;
		float v0 = dot(g0, vec3(f0.x, f0.y, f0.z));
		float v1 = dot(g1, vec3(f1.x, f0.y, f0.z));
		float v2 = dot(g2, vec3(f0.x, f1.y, f0.z));
		float v3 = dot(g3, vec3(f1.x, f1.y, f0.z));
		float v4 = dot(g4, vec3(f0.x, f0.y, f1.z));
		float v5 = dot(g6, vec3(f0.x, f1.y, f1.z));
		float v6 = dot(g5, vec3(f1.x, f0.y, f1.z));
		float v7 = dot(g7, vec3(f1.x, f1.y, f1.z));
	#else
		float v0 = dot(g0, vec3(f0.x, f0.y, f0.z)) * ig0.x;
		float v1 = dot(g1, vec3(f1.x, f0.y, f0.z)) * ig0.z;
		float v2 = dot(g2, vec3(f0.x, f1.y, f0.z)) * ig0.y;
		float v3 = dot(g3, vec3(f1.x, f1.y, f0.z)) * ig0.w;
		float v4 = dot(g4, vec3(f0.x, f0.y, f1.z)) * ig1.x;
		float v5 = dot(g6, vec3(f0.x, f1.y, f1.z)) * ig1.y;
		float v6 = dot(g5, vec3(f1.x, f0.y, f1.z)) * ig1.z;
		float v7 = dot(g7, vec3(f1.x, f1.y, f1.z)) * ig1.w;
	#endif
	#if CUBIC_SHADER
		vec3 k = f0 * f0 * (3.0f - f0 * 2.0f);
	#else
		vec3 k = f0 * f0 * f0 * (f0 * (f0 * 6.0f - 15.0f) + 10.0f);
	#endif
	float noise = v0 + (v1 - v0) * k.x + (v2 - v0) * k.y + (v4 - v0) * k.z +
		(v0 - v1 - v2 + v3) * (k.x * k.y) + (v0 - v2 - v4 + v5) * (k.y * k.z) +
		(v0 - v1 - v4 + v6) * (k.z * k.x) + (-v0 + v1 + v2 - v3 + v4 - v6 - v5 + v7) * (k.x * k.y * k.z);
	#if DERIVATIVE_SHADER
		#if CUBIC_SHADER
			vec3 dk = f0 * (1.0f - f0) * 6.0f;
		#else
			vec3 dk = f0 * f0 * (f0 * (f0 - 2.0f) + 1.0f) * 30.0f;
		#endif
		vec4 OUT = vec4(noise,
			g0 + (g1 - g0) * k.x + (g2 - g0) * k.y + (g4 - g0) * k.z +
			(g0 - g1 - g2 + g3) * (k.x * k.y) + (g0 - g2 - g4 + g6) * (k.y * k.z) +
			(g0 - g1 - g4 + g5) * (k.z * k.x) + (-g0 + g1 + g2 - g3 + g4 - g5 - g6 + g7) * (k.x * k.y * k.z) +
			((-v0 + v1 + v2 - v3 + v4 - v6 - v5 + v7) * k.yzx * k.zxy + vec3(v0 - v1 - v2 + v3, v0 - v2 - v4 + v5, v0 - v1 - v4 + v6) * k.yzx +
			vec3(v0 - v1 - v4 + v6, v0 - v1 - v2 + v3, v0 - v2 - v4 + v5) * k.zxy + vec3(v1, v2, v4) - v0) * dk);
	#else
		float OUT = noise;
	#endif
	
#endif

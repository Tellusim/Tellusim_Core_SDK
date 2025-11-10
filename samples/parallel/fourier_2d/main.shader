// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if COMPUTE_SHADER
	
	layout(local_size_x = 8, local_size_y = 8) in;
	
	layout(std140, binding = 0) uniform compute_parameters {
		float scale;
	};
	
	#if MODE_RGBF16P || MODE_RGBF32P
		layout(binding = 0, set = 1) uniform texture2DArray in_texture_0;
		layout(binding = 1, set = 1) uniform texture2DArray in_texture_1;
		layout(binding = 2, set = 1, SURFACE_FORMAT) uniform writeonly image2DArray out_surface;
	#else
		layout(binding = 0, set = 1) uniform texture2D in_texture_0;
		layout(binding = 1, set = 1) uniform texture2D in_texture_1;
		layout(binding = 2, set = 1, SURFACE_FORMAT) uniform writeonly image2D out_surface;
	#endif
	
	#if MODE_RGBF21C
		uvec2 packFloat3x21(vec3 f) {
			uvec3 u = floatBitsToUint(f);
			uvec3 h = (u & 0x80000000u) >> 11u;
			uvec3 em = (u & 0x7fffffffu) - 0x30000000u;
			h |= mix(uvec3(0u), em >> 9u, lessThan(em, uvec3(0x1f800000u)));
			return uvec2(h.x | ((h.z & 0x7ffu) << 21u), h.y | ((h.z & 0x1ff800u) << 10u));
		}
		vec3 unpackFloat3x21(uvec2 u) {
			uvec3 h = uvec3(u.x & 0x1fffffu, u.y & 0x1fffffu, ((u.x >> 21u) & 0x7ffu) | ((u.y >> 10u) & 0x1ff800u));
			return uintBitsToFloat(((h & 0x100000u) << 11u) | (((h & 0xfffffu) << 9u) + 0x30000000u));
		}
	#endif
	
	/*
	 */
	void main() {
		
		ivec2 texcoord = ivec2(gl_GlobalInvocationID.xy);
		
		#if MODE_RGBF16P || MODE_RGBF32P
			vec4 r0 = texelFetch(in_texture_0, ivec3(texcoord, 0), 0);
			vec4 i0 = texelFetch(in_texture_0, ivec3(texcoord, 1), 0);
			vec4 r1 = texelFetch(in_texture_1, ivec3(texcoord, 0), 0);
			vec4 i1 = texelFetch(in_texture_1, ivec3(texcoord, 1), 0);
		#else
			vec4 data_0 = texelFetch(in_texture_0, texcoord, 0);
			vec4 data_1 = texelFetch(in_texture_1, texcoord, 0);
			#if MODE_RGBF16C
				vec2 x0 = unpackHalf2x16(floatBitsToUint(data_0.x));
				vec2 y0 = unpackHalf2x16(floatBitsToUint(data_0.y));
				vec2 z0 = unpackHalf2x16(floatBitsToUint(data_0.z));
				vec2 x1 = unpackHalf2x16(floatBitsToUint(data_1.x));
				vec2 y1 = unpackHalf2x16(floatBitsToUint(data_1.y));
				vec2 z1 = unpackHalf2x16(floatBitsToUint(data_1.z));
				vec4 r0 = vec4(x0.x, y0.x, z0.x, 0.0f);
				vec4 i0 = vec4(x0.y, y0.y, z0.y, 0.0f);
				vec4 r1 = vec4(x1.x, y1.x, z1.x, 0.0f);
				vec4 i1 = vec4(x1.y, y1.y, z1.y, 0.0f);
			#elif MODE_RGBF21C
				vec4 r0 = vec4(unpackFloat3x21(floatBitsToUint(data_0.xy)), 0.0f);
				vec4 i0 = vec4(unpackFloat3x21(floatBitsToUint(data_0.zw)), 0.0f);
				vec4 r1 = vec4(unpackFloat3x21(floatBitsToUint(data_1.xy)), 0.0f);
				vec4 i1 = vec4(unpackFloat3x21(floatBitsToUint(data_1.zw)), 0.0f);
			#endif
		#endif
		
		vec4 r = (r0 * r1 - i0 * i1) * scale;
		vec4 i = (i0 * r1 + r0 * i1) * scale;
		
		#if MODE_RGBF16P || MODE_RGBF32P
			imageStore(out_surface, ivec3(texcoord, 0), r);
			imageStore(out_surface, ivec3(texcoord, 1), i);
		#else
			#if MODE_RGBF16C
				uint x = packHalf2x16(vec2(r.x, i.x));
				uint y = packHalf2x16(vec2(r.y, i.y));
				uint z = packHalf2x16(vec2(r.z, i.z));
				vec4 data = vec4(uintBitsToFloat(x), uintBitsToFloat(y), uintBitsToFloat(z), 0.0f);
			#elif MODE_RGBF21C
				uvec2 xy = packFloat3x21(r.xyz);
				uvec2 zw = packFloat3x21(i.xyz);
				vec4 data = vec4(uintBitsToFloat(xy), uintBitsToFloat(zw));
			#endif
			imageStore(out_surface, texcoord, data);
		#endif
	}
	
#elif VERTEX_SHADER
	
	layout(std140, binding = 0) uniform CommonParameters {
		vec4 size;
		float scale;
	};
	
	layout(location = 0) out vec2 s_texcoord;
	
	/*
	 */
	void main() {
		
		vec2 texcoord = vec2(0.0f);
		if(gl_VertexIndex == 0) texcoord.x = 2.0f;
		if(gl_VertexIndex == 2) texcoord.y = 2.0f;
		
		float aspect_0 = size.x / size.y;
		float aspect_1 = size.z / size.w;
		vec2 position = texcoord * 2.0f - 1.0f;
		position.y = (position.y + 1.0f) * aspect_0 / aspect_1 - 1.0f;
		
		#if !CLAY_VK
			position.y = -position.y;
		#endif
		
		gl_Position = vec4(position, 0.0f, 1.0f);
		
		s_texcoord = texcoord * 2.0f;
	}
	
#elif FRAGMENT_SHADER
	
	layout(std140, binding = 0) uniform CommonParameters {
		vec4 size;
		float scale;
	};
	
	layout(binding = 0, set = 1) uniform texture2D in_texture_0;
	layout(binding = 1, set = 1) uniform texture2D in_texture_1;
	#if MODE_RGBF16P || MODE_RGBF32P
		layout(binding = 2, set = 1) uniform texture2DArray in_texture_2;
	#else
		layout(binding = 2, set = 1) uniform texture2D in_texture_2;
	#endif
	layout(binding = 0, set = 2) uniform sampler in_sampler;
	
	layout(location = 0) in vec2 s_texcoord;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	#if MODE_RGBF21C
		vec3 unpackFloat3x21(uvec2 u) {
			uvec3 h = uvec3(u.x & 0x1fffffu, u.y & 0x1fffffu, ((u.x >> 21u) & 0x7ffu) | ((u.y >> 10u) & 0x1ff800u));
			return uintBitsToFloat(((h & 0x100000u) << 11u) | (((h & 0xfffffu) << 9u) + 0x30000000u));
		}
	#endif
	
	/*
	 */
	void main() {
		
		vec2 texcoord_0 = s_texcoord - vec2(0.0f, 0.0f);
		vec2 texcoord_1 = s_texcoord - vec2(1.0f, 0.0f);
		vec4 color_0 = pow(texture(sampler2D(in_texture_0, in_sampler), texcoord_0), vec4(1.0f / 2.2f));
		vec4 color_1 = pow(texture(sampler2D(in_texture_1, in_sampler), texcoord_1), vec4(1.0f / 2.2f));
		
		if(scale > 0.0f) {
			vec4 color_0 = pow(texture(sampler2D(in_texture_0, in_sampler), texcoord_1), vec4(1.0f / 2.2f));
			color_1 = abs(color_1 - color_0) * scale;
			color_1.w = 0.0f;
		}
		
		if(any(greaterThan(abs(texcoord_0 - 0.5f), 0.5f))) color_0 = vec4(0.0f);
		if(any(greaterThan(abs(texcoord_1 - 0.5f), 0.5f))) color_1 = vec4(0.0f);
		
		vec2 texture_size = vec2(textureSize(in_texture_0, 0));
		float offset = 1.0f - texture_size.x / texture_size.y;
		
		vec2 size = vec2(textureSize(in_texture_2, 0));
		vec2 texcoord_2 = (s_texcoord.yx - vec2(offset, 1.5f)) * vec2(size.y / size.x, 1.0f);
		vec2 texcoord_3 = (s_texcoord.yx - vec2(offset, 1.5f)) * vec2(size.y / size.x, 1.0f);
		while(texcoord_2.x < 0.0f) texcoord_2.x += 1.0f; while(texcoord_2.x > 1.0f) texcoord_2.x -= 1.0f;
		while(texcoord_2.y < 0.0f) texcoord_2.y += 1.0f; while(texcoord_2.y > 1.0f) texcoord_2.y -= 1.0f;
		#if MODE_RGBF16P || MODE_RGBF32P
			vec4 color_2 = texelFetch(in_texture_2, ivec3(texcoord_2 * size, 0), 0);
			vec4 color_3 = texelFetch(in_texture_2, ivec3(texcoord_2 * size, 1), 0);
		#else
			vec4 data = texelFetch(in_texture_2, ivec2(texcoord_2 * size), 0);
			#if MODE_RGBF16C
				vec2 x = unpackHalf2x16(floatBitsToUint(data.x));
				vec2 y = unpackHalf2x16(floatBitsToUint(data.y));
				vec2 z = unpackHalf2x16(floatBitsToUint(data.z));
				vec4 color_2 = vec4(x.x, y.x, z.x, 0.0f);
				vec4 color_3 = vec4(x.y, y.y, z.y, 0.0f);
			#elif MODE_RGBF21C
				vec4 color_2 = vec4(unpackFloat3x21(floatBitsToUint(data.xy)), 0.0f);
				vec4 color_3 = vec4(unpackFloat3x21(floatBitsToUint(data.zw)), 0.0f);
			#endif
		#endif
		if(any(greaterThan(abs(texcoord_3 - vec2(2.5f, -1.0f)), vec2(0.5f, 0.5f)))) color_2 = vec4(0.0f);
		if(any(greaterThan(abs(texcoord_3 - vec2(2.5f,  0.0f)), vec2(0.5f, 0.5f)))) color_3 = vec4(0.0f);
		color_2 = pow(abs(color_2), vec4(1.0f / 2.2f));
		color_3 = pow(abs(color_3), vec4(1.0f / 2.2f));
		
		out_color = color_0 + color_1 + color_2 + color_3;
	}
	
#endif

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if VERTEX_SHADER && FILTER_SHADER
	
	layout(location = 0) out vec2 s_texcoord;
	
	/*
	 */
	void main() {
		
		vec2 texcoord = vec2(0.0f);
		if(gl_VertexIndex == 0) texcoord.x = 2.0f;
		if(gl_VertexIndex == 2) texcoord.y = 2.0f;
		
		gl_Position = vec4(texcoord * 2.0f - 1.0f, 0.0f, 1.0f);
		
		#if FLAG_FLIPPED
			gl_Position.y = -gl_Position.y;
		#endif
		
		s_texcoord = texcoord;
	}

#elif VERTEX_SHADER
	
	layout(std140, row_major, binding = 0) uniform ProjectionParameters {
		mat4 projection;
	};
	
	layout(std140, binding = 1) uniform TransformParameters {
		vec4 transform;
		vec2 translate;
	};
	
	layout(location = 0) in vec2 in_position;
	layout(location = 1) in vec2 in_texcoord;
	layout(location = 2) in vec4 in_color;
	
	#if TEXTURE_SHADER || GRADIENT_SHADER
		layout(location = 0) out vec2 s_texcoord;
	#endif
	#if SOLID_SHADER || TEXTURE_SHADER || GRADIENT_SHADER
		layout(location = 1) out vec4 s_color;
	#endif
	
	/*
	 */
	void main() {
		
		gl_Position = projection * vec4(in_position + translate, 0.0f, 1.0f);
		
		gl_Position.z = gl_Position.z * 0.5f + 0.5f;
		
		#if FLAG_FLIPPED
			gl_Position.y = -gl_Position.y;
		#endif
		
		#if TEXTURE_SHADER || GRADIENT_SHADER
			s_texcoord = in_texcoord * transform.xy + transform.zw;
		#endif
		
		#if SOLID_SHADER || TEXTURE_SHADER || GRADIENT_SHADER
			s_color = in_color;
		#endif
	}
	
#elif FRAGMENT_SHADER && FILTER_SHADER
	
	#if FILTER_COPY_SHADER
		layout(std140, binding = 0) uniform FilterParameters {
			float value;
		};
	#elif FILTER_MASK_SHADER
		layout(std140, binding = 0) uniform FilterParameters {
			vec4 transform;
		};
	#elif FILTER_BLUR_SHADER
		layout(std140, binding = 0) uniform FilterParameters {
			vec4 weights[NUM_SHADER_SAMPLES / 4u];
			vec4 texcoords;
			vec2 direction;
		};
	#elif FILTER_COLOR_SHADER
		layout(std140, row_major, binding = 0) uniform FilterParameters {
			mat4 transform;
		};
	#elif FILTER_SHADOW_SHADER
		layout(std140, binding = 0) uniform FilterParameters {
			vec4 shadow_color;
			vec4 texcoords;
			vec2 offset;
		};
	#endif
	
	layout(binding = 0, set = 1) uniform texture2D in_texture;
	#if FILTER_MASK_SHADER
		layout(binding = 1, set = 1) uniform texture2D in_mask_texture;
	#endif
	layout(binding = 0, set = 2) uniform sampler in_sampler;
	
	layout(location = 0) in vec2 s_texcoord;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		#if FILTER_COPY_SHADER
			vec4 color = texture(sampler2D(in_texture, in_sampler), s_texcoord) * value;
		#elif FILTER_MASK_SHADER
			vec2 texcoord = clamp(s_texcoord * transform.xy + transform.zw, 0.0f, 1.0f);
			float alpha = texture(sampler2D(in_mask_texture, in_sampler), texcoord).w;
			vec4 color = texture(sampler2D(in_texture, in_sampler), s_texcoord) * alpha;
		#elif FILTER_BLUR_SHADER
			vec4 weight = weights[0u];
			vec4 color = texture(sampler2D(in_texture, in_sampler), s_texcoord) * weight.x;
			#define BLUR_SAMPLE(WEIGHT, INDEX) { \
				vec2 offset = direction * (float(INDEX) * 2.0f - 0.5f); \
				vec2 texcoord_0 = clamp(s_texcoord - offset, texcoords.xy, texcoords.zw); \
				vec2 texcoord_1 = clamp(s_texcoord + offset, texcoords.xy, texcoords.zw); \
				color += texture(sampler2D(in_texture, in_sampler), texcoord_0) * WEIGHT; \
				color += texture(sampler2D(in_texture, in_sampler), texcoord_1) * WEIGHT; \
			}
			BLUR_SAMPLE(weight.y, 1)
			BLUR_SAMPLE(weight.z, 2)
			BLUR_SAMPLE(weight.w, 3)
			[[loop]] for(uint i = 4u; i < NUM_SHADER_SAMPLES && weight.w > 0.0f; i += 4u) {
				weight = weights[i / 4u];
				BLUR_SAMPLE(weight.x, i + 0u)
				BLUR_SAMPLE(weight.y, i + 1u)
				BLUR_SAMPLE(weight.z, i + 2u)
				BLUR_SAMPLE(weight.w, i + 3u)
			}
			#undef BLUR_SAMPLE
		#elif FILTER_COLOR_SHADER
			vec4 color = texture(sampler2D(in_texture, in_sampler), s_texcoord);
			color = vec4((transform * color).xyz, color.w);
		#elif FILTER_SHADOW_SHADER
			vec2 texcoord = clamp(s_texcoord - offset, texcoords.xy, texcoords.zw);
			float alpha = texture(sampler2D(in_texture, in_sampler), texcoord).w;
			vec4 color = shadow_color * alpha;
		#endif
		out_color = color;
	}
	
#elif FRAGMENT_SHADER && GRADIENT_SHADER
	
	layout(std140, binding = 2) uniform ShaderParameters {
		uint shader_type;
		uint sheder_flags;
		uint num_colors;
		vec4 parameters;
		vec4 colors[NUM_SHADER_COLORS];
		vec4 values[NUM_SHADER_COLORS / 4u];
	};
	
	layout(location = 0) in vec2 s_texcoord;
	layout(location = 1) in vec4 s_color;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	float get_value(uint index) {
		vec4 value_4 = values[index >> 2];
		index &= 0x03u;
		if(index == 0u) return value_4.x;
		if(index == 1u) return value_4.y;
		if(index == 2u) return value_4.z;
		return value_4.w;
	}
	
	/*
	 */
	void main() {
		
		vec2 texcoord = s_texcoord - parameters.xy;
		
		#if GRADIENT_LINEAR_SHADER
			vec2 direction = parameters.zw - parameters.xy;
			float k = dot(texcoord, direction) / dot(direction, direction);
		#elif GRADIENT_RADIAL_SHADER
			float k = length(texcoord * parameters.zw);
		#elif GRADIENT_CONIC_SHADER
			float x = dot(texcoord, vec2(parameters.z, -parameters.w));
			float y = dot(texcoord, vec2(parameters.w, parameters.z));
			float k = atan(-x, y) / (6.283185f) + 0.5f;
		#endif
		
		#if FLAG_REPEAT
			float k0 = get_value(0u);
			float k1 = get_value(num_colors - 1u);
			k = k0 + mod(k - k0, k1 - k0);
		#endif
		
		float v0 = get_value(0);
		vec4 color = colors[0u];
		[[loop]] for(uint i = 1u; i < num_colors; i++) {
			float v1 = get_value(i);
			color = mix(color, colors[i], smoothstep(v0, v1, k));
			v0 = v1;
		}
		
		out_color = color * s_color;
	}

#else
	
	#if TEXTURE_SHADER
		layout(binding = 0, set = 1) uniform texture2D in_texture;
		layout(binding = 0, set = 2) uniform sampler in_sampler;
	#endif
	
	#if TEXTURE_SHADER
		layout(location = 0) in vec2 s_texcoord;
	#endif
	#if SOLID_SHADER || TEXTURE_SHADER
		layout(location = 1) in vec4 s_color;
	#endif
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		#if SOLID_SHADER
			vec4 color = s_color;
		#elif TEXTURE_SHADER
			vec4 color = texture(sampler2D(in_texture, in_sampler), s_texcoord) * s_color;
		#elif STENCIL_SHADER
			vec4 color = vec4(1.0f);
		#endif
		out_color = color;
	}
	
#endif

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if RENDER_TARGET || FRAGMENT_SHADER
	
	/*
	 */
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		mat4 transform;
		vec4 camera;
		vec4 color;
		uint stride;
		uint size;
	};
	
#endif

/*
 */
#if RENDER_TARGET
	
	#if VERTEX_SHADER
		
		layout(location = 0) in vec4 in_position;
		layout(location = 1) in vec3 in_normal;
		
		layout(location = 0) out vec3 s_normal;
		layout(location = 1) out vec3 s_direction;
		
		/*
		 */
		void main() {
			
			vec4 position = transform * in_position;
			gl_Position = projection * (modelview * position);
			
			s_normal = (transform * vec4(in_normal, 0.0f)).xyz;
			s_direction = camera.xyz - position.xyz;
		}
		
	#elif FRAGMENT_SHADER
		
		layout(location = 0) in vec3 s_normal;
		layout(location = 1) in vec3 s_direction;
		
		layout(std430, binding = 1) buffer IndexBuffer { uint index_buffer[]; };
		layout(std430, binding = 2) buffer ColorBuffer { vec4 color_buffer[]; };
		
		/*
		 */
		void main() {
			
			vec3 normal = normalize(s_normal);
			vec3 direction = normalize(s_direction);
			
			ivec2 frag_coord = ivec2(gl_FragCoord.xy);
			float depth = gl_FragCoord.z * gl_FragCoord.w;
			
			uint index = atomicIncrement(index_buffer[0]) + 1u;
			[[branch]] if(index < size) {
				
				float diffuse = dot(direction, normal);
				float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0f, 1.0f), 16.0f);
				if(diffuse < 0.0f) diffuse *= -0.5f;
				
				uint prev = atomicExchange(index_buffer[stride * frag_coord.y + frag_coord.x + stride], index);
				
				uint data = packUnorm4x8(vec4(pow(color.xyz, vec3(2.2f * 2.0f)) * (diffuse + specular), color.w));
				
				color_buffer[index] = vec4(uintBitsToFloat(data), depth, 0.0f, uintBitsToFloat(prev));
			}
		}
		
	#endif
	
/*
 */
#elif VERTEX_SHADER
	
	/*
	 */
	void main() {
		
		vec2 texcoord = vec2(0.0f);
		if(gl_VertexIndex == 0) texcoord.x = 2.0f;
		if(gl_VertexIndex == 2) texcoord.y = 2.0f;
		
		gl_Position = vec4(texcoord * 2.0f - 1.0f, 0.0f, 1.0f);
	}
	
#elif FRAGMENT_SHADER
	
	layout(std430, binding = 1) buffer IndexBuffer { uint index_buffer[]; };
	layout(std430, binding = 2) buffer ColorBuffer { vec4 color_buffer[]; };
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		ivec2 frag_coord = ivec2(gl_FragCoord.xy);
		
		vec3 color = vec3(0.02f);
		
		vec2 samples[8];
		uint num_samples = 0u;
		uint index = index_buffer[stride * frag_coord.y + frag_coord.x + stride];
		[[unroll]] for(int i = 0; i < 8; i++) {
			[[branch]] if(index != 0u) {
				vec4 value = color_buffer[index];
				index = floatBitsToUint(value.w);
				samples[i] = value.xy;
				num_samples++;
			} else {
				samples[i] = vec2(0.0f, 1.0f);
			}
		}
		
		#define COMPARE(S0, S1) if(S0.y > S1.y) { vec2 S = S0; S0 = S1; S1 = S; }
		
		[[branch]] if(num_samples > 4) {
			
			COMPARE(samples[0], samples[1])
			COMPARE(samples[2], samples[3])
			COMPARE(samples[4], samples[5])
			COMPARE(samples[6], samples[7])
			
			COMPARE(samples[0], samples[2])
			COMPARE(samples[1], samples[3])
			COMPARE(samples[4], samples[6])
			COMPARE(samples[5], samples[7])
			
			COMPARE(samples[1], samples[2])
			COMPARE(samples[5], samples[6])
			
			COMPARE(samples[0], samples[4])
			COMPARE(samples[1], samples[5])
			COMPARE(samples[2], samples[6])
			COMPARE(samples[3], samples[7])
			
			COMPARE(samples[2], samples[4])
			COMPARE(samples[3], samples[5])
			
			COMPARE(samples[1], samples[2])
			COMPARE(samples[3], samples[4])
			COMPARE(samples[5], samples[6])
		}
		else if(num_samples > 2) {
			
			COMPARE(samples[0], samples[1])
			COMPARE(samples[2], samples[3])
			
			COMPARE(samples[0], samples[2])
			COMPARE(samples[1], samples[3])
			
			COMPARE(samples[1], samples[2])
		}
		else if(num_samples > 1) {
			
			COMPARE(samples[0], samples[1])
		}
		
		#undef COMPARE
		
		[[loop]] for(int i = 0; i < num_samples; i++) {
			vec4 value = unpackUnorm4x8(floatBitsToUint(samples[i].x));
			color = mix(color, value.xyz, value.w);
		}
		
		out_color = vec4(pow(color, vec3(1.0f / 2.2f)), 1.0f);
	}
	
#endif

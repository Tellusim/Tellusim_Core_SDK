// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if !SHADOW_TARGET && (VERTEX_SHADER || FRAGMENT_SHADER)
	
	/*
	 */
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		mat4 transform;
		mat4 texcoord;
		vec4 camera;
		vec4 light;
		float znear;
		float radius;
		float penumbra;
		float samples;
	};
	
#endif

/*
 */
#if SHADOW_TARGET
	
	#if VERTEX_SHADER
		
		layout(location = 0) in vec4 in_position;
		
		layout(row_major, binding = 0) uniform CommonParameters {
			mat4 projection;
			mat4 modelview;
			mat4 transform;
		};
		
		/*
		 */
		void main() {
			
			gl_Position = projection * (modelview * (transform * in_position));
		}
		
	#elif FRAGMENT_SHADER
		
		/*
		 */
		void main() {
			
		}
		
	#endif
	
/*
 */
#elif VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec3 in_normal;
	
	layout(location = 0) out vec3 s_normal;
	layout(location = 1) out vec4 s_texcoord;
	layout(location = 2) out vec3 s_position;
	
	/*
	 */
	void main() {
		
		vec4 position = transform * in_position;
		gl_Position = projection * (modelview * position);
		
		s_normal = (transform * vec4(in_normal, 0.0f)).xyz;
		s_texcoord = texcoord * position;
		
		s_position = position.xyz;
	}
	
#elif FRAGMENT_SHADER
	
	layout(binding = 0, set = 1) uniform texture2D in_noise_texture;
	layout(binding = 1, set = 1) uniform texture2D in_shadow_texture;
	layout(binding = 0, set = 2) uniform sampler in_noise_sampler;
	layout(binding = 1, set = 2) uniform sampler in_point_sampler;
	layout(binding = 2, set = 2) uniform sampler in_shadow_sampler;
	
	layout(location = 0) in vec3 s_normal;
	layout(location = 1) in vec4 s_texcoord;
	layout(location = 2) in vec3 s_position;
	
	layout(location = 0) out vec4 out_color;
	
	#if CLAY_WG
		#pragma texture(1, point)
		#pragma sampler(1, point)
		#pragma sampler(2, comparison)
	#endif
	
	/*
	 */
	float shadow_pcf(vec3 texcoord, float samples, float radius, float penumbra, float noise) {
		
		// distance to the blocker
		float weight = 0.0f;
		float distance = 0.0f;
		float isamples = radius * inversesqrt(samples);
		for(float i = 0.0f; i < samples; i += 2.0f) {
			float angle = i * 2.4f + noise;
			vec2 offset = vec2(sin(angle), cos(angle)) * (sqrt(i + 1.0f) * isamples);
			float depth = textureLod(sampler2D(in_shadow_texture, in_point_sampler), texcoord.xy + offset, 0.0f).x;
			if(depth > texcoord.z) {
				distance += znear / depth;
				weight += 1.0f;
			}
		}
		distance /= weight;
		
		// adjust radius
		radius = min(radius, penumbra * clamp((znear / texcoord.z - distance) / distance, 0.0f, 1.0f));
		radius = max(radius, 1.0f / 512.0f);
		
		// sample shadow
		float shadow = 0.0f;
		if(weight < 4.0f) samples = 4.0f;
		isamples = radius * inversesqrt(samples);
		for(float i = 0.0f; i < samples; i += 1.0f) {
			float angle = i * 2.4f + noise;
			vec2 offset = vec2(sin(angle), cos(angle)) * (sqrt(i + 1.0f) * isamples);
			#if CLAY_GL || CLAY_GLES || CLAY_MTL || CLAY_WG
				if(textureLod(sampler2D(in_shadow_texture, in_point_sampler), texcoord.xy + offset, 0.0f).x < texcoord.z) shadow += 1.0f;
			#else
				shadow += textureLod(sampler2DShadow(in_shadow_texture, in_shadow_sampler), vec3(texcoord.xy + offset, texcoord.z), 0.0f);
			#endif
		}
		
		return shadow / samples;
	}
	
	/*
	 */
	void main() {
		
		vec3 normal = normalize(s_normal);
		vec3 view_vector = normalize(camera.xyz - s_position);
		vec3 light_vector = normalize(light.xyz - s_position);
		
		float diffuse = clamp(dot(light_vector, normal), 0.0f, 1.0f) * 0.75f;
		float specular = pow(clamp(dot(reflect(-light_vector, normal), view_vector), 0.0f, 1.0f), 16.0f) * 0.75f;
		
		vec2 noise_texcoord = gl_FragCoord.xy / 128.0f;
		float noise = textureLod(sampler2D(in_noise_texture, in_noise_sampler), noise_texcoord, 0.0f).x;
		
		float shadow = 1.0f;
		vec3 texcoord = s_texcoord.xyz / s_texcoord.w;
		[[branch]] if(all(lessThan(abs(texcoord.xy - 0.5f), 0.5f))) {
			shadow = shadow_pcf(texcoord, samples, radius, penumbra, noise * 6.28f);
		}
		
		float color = (diffuse + specular) * max(shadow, 0.05f);
		
		out_color = vec4(vec3(pow(color, 1.0f / 2.2f)), 1.0f);
	}
	
#endif

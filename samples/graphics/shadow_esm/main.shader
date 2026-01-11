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
		float znear_alpha;
		float shadow_power;
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
	
	layout(binding = 0, set = 1) uniform texture2D in_texture;
	layout(binding = 0, set = 2) uniform sampler in_point_sampler;
	layout(binding = 1, set = 2) uniform sampler in_linear_sampler;
	
	layout(location = 0) in vec3 s_normal;
	layout(location = 1) in vec4 s_texcoord;
	layout(location = 2) in vec3 s_position;
	
	layout(location = 0) out vec4 out_color;
	
	#if CLAY_WG
		#pragma texture(0, point)
		#pragma sampler(0, point)
	#endif
	
	/*
	 */
	void main() {
		
		vec3 normal = normalize(s_normal);
		vec3 view_vector = normalize(camera.xyz - s_position);
		vec3 light_vector = normalize(light.xyz - s_position);
		
		float diffuse = clamp(dot(light_vector, normal), 0.0f, 1.0f) * 0.75f;
		float specular = pow(clamp(dot(reflect(-light_vector, normal), view_vector), 0.0f, 1.0f), 16.0f) * 0.75f;
		
		vec3 texcoord = s_texcoord.xyz / s_texcoord.w;
		#if CLAY_WG
			vec2 w = texcoord.xy * textureSize(in_texture).xy - 0.5f; w -= floor(w);
			vec4 shadow4 = textureGather(sampler2D(in_texture, in_point_sampler), texcoord.xy);
			vec2 shadow2 = mix(shadow4.wz, shadow4.xy, w.y);
			float shadow = mix(shadow2.x, shadow2.y, w.x);
		#else
			float shadow = textureLod(sampler2D(in_texture, in_linear_sampler), texcoord.xy, 0.0f).x;
		#endif
		shadow = pow(shadow * exp(-znear_alpha / texcoord.z), shadow_power);
		if(any(greaterThan(abs(texcoord.xy - 0.5f), 0.5f))) shadow = 1.0f;
		
		float color = (diffuse + specular) * clamp(shadow, 0.05f, 1.0f);
		
		out_color = vec4(vec3(pow(color, 1.0f / 2.2f)), 1.0f);
	}
	
#endif

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		mat4 transform;
		vec4 camera;
	};
	
	layout(location = 0) out vec3 s_camera;
	layout(location = 1) out vec3 s_direction;
	
	/*
	 */
	void main() {
		
		vec4 position = transform * in_position;
		gl_Position = projection * (modelview * position);
		
		s_camera = (camera * transform).xyz;
		s_direction = in_position.xyz - s_camera;
	}
	
#elif FRAGMENT_SHADER
	
	layout(binding = 0, set = 1) uniform texture3D in_texture;
	layout(binding = 0, set = 2) uniform sampler in_sampler;
	
	layout(location = 0) in vec3 s_camera;
	layout(location = 1) in vec3 s_direction;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec3 idirection = 1.0f / s_direction;
		vec3 k0 = -(s_camera - 0.5f) * idirection;
		vec3 k1 = -(s_camera + 0.5f) * idirection;
		vec3 k2 = min(k0, k1);
		vec3 k3 = max(k0, k1);
		
		vec4 color = vec4(0.0f);
		float back = min(k3.x, min(k3.y, k3.z));
		float front = max(k2.x, max(k2.y, k2.z));
		for(float k = back; k > front; k -= 0.02f) {
			vec4 value = textureLod(sampler3D(in_texture, in_sampler), s_camera + s_direction * k + 0.5f, 0.0f);
			color += (1.0f - color) * value * 0.2f;
		}
		
		out_color = color;
	}
	
#endif

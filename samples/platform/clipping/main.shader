// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec3 in_normal;
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		vec4 camera;
		float distance;
	};
	
	layout(row_major, binding = 1) uniform InstanceParameters {
		mat4 transform;
		vec4 color;
	};
	
	layout(location = 0) out vec3 s_direction;
	layout(location = 1) out vec3 s_normal;
	layout(location = 2) out vec4 s_color;
	
	out gl_PerVertex {
		vec4 gl_Position;
		float gl_ClipDistance[4];
	};
	
	/*
	 */
	void main() {
		
		vec4 position = transform * (in_position * vec4(0.5f, 0.5f, 0.5f, 1.0f));
		gl_Position = projection * (modelview * position);
		
		s_direction = camera.xyz - position.xyz;
		s_normal = (transform * vec4(in_normal, 0.0f)).xyz;
		
		s_color = color;
		
		float size = gl_Position.w * distance;
		gl_ClipDistance[0] = size - gl_Position.x;
		gl_ClipDistance[1] = size + gl_Position.x;
		gl_ClipDistance[2] = size - gl_Position.y;
		gl_ClipDistance[3] = size + gl_Position.y;
	}
	
#elif FRAGMENT_SHADER
	
	layout(location = 0) in vec3 s_direction;
	layout(location = 1) in vec3 s_normal;
	layout(location = 2) in vec4 s_color;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec3 direction = normalize(s_direction);
		vec3 normal = normalize(s_normal);
		
		float diffuse = clamp(dot(direction, normal), 0.0f, 1.0f);
		float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0f, 1.0f), 16.0f);
		
		out_color = s_color * (diffuse + specular);
	}
	
#endif

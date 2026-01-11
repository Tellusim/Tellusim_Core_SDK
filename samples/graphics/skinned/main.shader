// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec3 in_normal;
	layout(location = 2) in vec2 in_texcoord;
	layout(location = 3) in vec4 in_weights;
	layout(location = 4) in uvec4 in_joints;
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		vec4 camera;
	};
	
	layout(binding = 1) uniform JointParameters {
		vec4 joints[192];
	};
	
	layout(location = 0) out vec3 s_direction;
	layout(location = 1) out vec3 s_normal;
	layout(location = 2) out vec2 s_texcoord;
	
	/*
	 */
	void main() {
		
		vec4 row_0, row_1, row_2;
		#define JOINT(OP, SWIZZLE) \
		row_0 OP joints[in_joints.SWIZZLE * 3 + 0] * in_weights.SWIZZLE; \
		row_1 OP joints[in_joints.SWIZZLE * 3 + 1] * in_weights.SWIZZLE; \
		row_2 OP joints[in_joints.SWIZZLE * 3 + 2] * in_weights.SWIZZLE;
		JOINT( =, x)
		JOINT(+=, y)
		JOINT(+=, z)
		JOINT(+=, w)
		
		mat4 skinning = mat4(row_0, row_1, row_2, vec4(0.0f, 0.0f, 0.0f, 1.0f));
		
		vec4 position = in_position * skinning;
		gl_Position = projection * (modelview * position);
		
		s_direction = camera.xyz - position.xyz;
		s_normal = ((vec4(in_normal, 0.0f) * skinning)).xyz;
		
		s_texcoord = vec2(in_texcoord.x, 1.0f - in_texcoord.y);
	}
	
#elif FRAGMENT_SHADER
	
	layout(binding = 0, set = 1) uniform texture2D in_texture;
	layout(binding = 0, set = 2) uniform sampler in_sampler;
	
	layout(location = 0) in vec3 s_direction;
	layout(location = 1) in vec3 s_normal;
	layout(location = 2) in vec2 s_texcoord;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec3 direction = normalize(s_direction);
		vec3 normal = normalize(s_normal);
		
		float diffuse = clamp(dot(direction, normal), 0.0f, 1.0f);
		float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0f, 1.0f), 16.0f);
		
		out_color = texture(sampler2D(in_texture, in_sampler), s_texcoord) * (diffuse + specular);
	}
	
#endif

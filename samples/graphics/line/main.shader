// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

/*
 */
#if VERTEX_SHADER
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		mat4 transform;
		vec4 color;
	};
	
	layout(location = 0) out vec4 s_color;
	layout(location = 1) out vec2 s_position;
	layout(location = 2) out vec2 s_position_0;
	layout(location = 3) out vec2 s_position_1;
	
	/*
	 */
	void main() {
		
		vec4 position_0 = transform * vec4(-color.xyz, 1.0f);
		vec4 position_1 = transform * vec4( color.xyz, 1.0f);
		
		position_0 = projection * (modelview * position_0);
		position_1 = projection * (modelview * position_1);
		
		position_0 /= position_0.w;
		position_1 /= position_1.w;
		
		vec4 tangent = vec4(position_1.xy - position_0.xy, 0.0f, 0.0f);
		tangent *= inversesqrt(max(dot(tangent.xy, tangent.xy), 1e-12f)) / 32.0f;
		vec4 binormal = vec4(tangent.y, -tangent.x, 0.0f, 0.0f);
		
		vec4 position = position_0 - tangent;
		if(gl_VertexIndex >= 2 && gl_VertexIndex <= 4) position = position_1 + tangent;
		
		if(gl_VertexIndex >= 1 && gl_VertexIndex <= 3) position += binormal;
		else position -= binormal;
		
		gl_Position = position;
		
		float aspect_y = projection[1].y / projection[0].x;
		vec2 aspect = vec2(min(aspect_y, 1.0f), min(1.0f / aspect_y, 1.0f));
		
		s_color = color;
		s_position = position.xy * aspect;
		s_position_0 = position_0.xy * aspect;
		s_position_1 = position_1.xy * aspect;
	}
	
#elif FRAGMENT_SHADER
	
	layout(location = 0) in vec4 s_color;
	layout(location = 1) in vec2 s_position;
	layout(location = 2) in vec2 s_position_0;
	layout(location = 3) in vec2 s_position_1;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec2 direction = s_position_1 - s_position_0;
		float k = clamp(dot(s_position - s_position_0, direction) / dot(direction, direction), 0.0f, 1.0f);
		vec2 position = s_position_0 + direction * k;
		
		float scale = 1.0f / length(fwidth(s_position));
		float distance = length(s_position - position) * scale;
		float alpha = min(4.0f - distance, 1.0f);
		if(alpha < 0.0f) discard;
		
		out_color = vec4(s_color.xyz, alpha);
	}
	
#endif

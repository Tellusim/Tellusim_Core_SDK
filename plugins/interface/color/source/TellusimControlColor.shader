// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

/*
 */
#if VERTEX_SHADER
	
	layout(std140, row_major, binding = 0) uniform CanvasParameters {
		mat4 canvas_transform;
		vec4 canvas_color;
		vec2 canvas_size;
	};
	
	layout(std140, row_major, binding = 1) uniform ElementParameters {
		mat4 element_transform;
		vec4 element_color;
		float element_mipmap;
	};
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec2 in_texcoord;
	layout(location = 2) in vec4 in_color;
	
	layout(location = 0) centroid out vec2 s_texcoord;
	layout(location = 1) centroid out vec4 s_color;
	
	/*
	 */
	void main() {
		
		gl_Position = canvas_transform * (element_transform * in_position);
		
		s_texcoord = in_texcoord;
		
		s_color = in_color * canvas_color * element_color;
	}
	
#elif COLOR_SHADER
	
	layout(location = 0) centroid in vec2 s_texcoord;
	layout(location = 1) centroid in vec4 s_color;
	
	layout(std140, binding = 2) uniform ColorParameters {
		vec4 hsv_color;
		vec4 rgb_color;
	};
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec2 texcoord = s_texcoord - 0.5f;
		
		float dx = dFdx(s_texcoord.x);
		float radius = length(texcoord);
		float alpha = max(0.5f - radius, 0.0f) / dx;
		
		float h = fract(atan(texcoord.y, -texcoord.x) / 6.283185f);
		if(abs(texcoord.x) < 1e-6f) h = (texcoord.y > 0.0f) ? 0.25f : 0.75f;
		float s = radius * 2.0f;
		
		vec3 color = abs(h * 6.0f - vec3(3.0f, 2.0f, 4.0f));
		color = clamp(vec3(color.x - 1.0f, 2.0f - color.y, 2.0f - color.z), 0.0f, 1.0f);
		color = color * color * (3.0f - color * 2.0f);
		color = (color * s + max(1.0f - s, 0.0f)) * hsv_color.z;
		
		float angle = hsv_color.x * 6.283185f;
		float x = 0.5f - cos(angle) * hsv_color.y * 0.5f;
		float y = 0.5f + sin(angle) * hsv_color.y * 0.5f;
		
		vec3 icolor = (max(rgb_color.x, max(rgb_color.y, rgb_color.z)) > 0.5f) ? vec3(0.0f) : vec3(1.0f);
		float distance = max(abs(length(s_texcoord - vec2(x, y)) - dx * 10.0f) - dx * 2.0f, 0.0f);
		color = mix(icolor, color, clamp(distance / dx, 0.0f, 1.0f));
		
		out_color = s_color * vec4(color, alpha);
	}
	
#elif VALUE_SHADER
	
	layout(location = 0) centroid in vec2 s_texcoord;
	layout(location = 1) centroid in vec4 s_color;
	
	layout(std140, binding = 2) uniform ColorParameters {
		vec4 hsv_color;
		vec4 rgb_color;
	};
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		float dx = dFdx(s_texcoord.x);
		
		vec3 color = abs(fract(hsv_color.x) * 6.0f - vec3(3.0f, 2.0f, 4.0f));
		color = clamp(vec3(color.x - 1.0f, 2.0f - color.y, 2.0f - color.z), 0.0f, 1.0f);
		color = (color * hsv_color.y + max(1.0f - hsv_color.y, 0.0f)) * s_texcoord.x;
		
		vec3 icolor = (max(rgb_color.x, max(rgb_color.y, rgb_color.z)) > 0.5f) ? vec3(0.0f) : vec3(1.0f);
		float distance = max(abs(s_texcoord.x - hsv_color.z) - dx * 2.0f, 0.0f);
		color = mix(icolor, color, clamp(distance / dx, 0.0f, 1.0f));
		
		out_color = s_color * vec4(color, 1.0f);
	}
	
#elif PALETTE_SHADER
	
	layout(location = 0) centroid in vec2 s_texcoord;
	layout(location = 1) centroid in vec4 s_color;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec4 color = s_color;
		
		float dx = dFdx(s_texcoord.x);
		
		float distance = s_texcoord.y - s_texcoord.x;
		if(any(notEqual(color, vec4(0.0f))) && color.w < 254.0f / 255.0f) color = mix(vec4(color.w), vec4(color.xyz, 1.0f), clamp(distance / dx, 0.0f, 1.0f));
		
		distance = min(s_texcoord.x, 1.0f - s_texcoord.x);
		distance = min(distance, min(s_texcoord.y, 1.0f - s_texcoord.y));
		distance = max(distance - dx * 2.0f, 0.0f);
		color = mix(vec4(vec3(0.4f), 1.0f), color, clamp(distance / dx, 0.0f, 1.0f));
		
		out_color = color;
	}
	
#endif

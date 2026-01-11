// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if COMPUTE_SHADER
	
	layout(local_size_x = 8, local_size_y = 8) in;
	
	layout(std140, binding = 0) uniform ComputeParameters {
		uint width;
		uint height;
		float aspect;
		float time;
	};
	
	layout(binding = 0, set = 2) uniform sampler in_sampler;
	layout(binding = 0, set = 1) uniform texture2D in_texture;
	
	layout(binding = 1, set = 1, rgba8) uniform writeonly image2D out_surface;
	
	/*
	 */
	void main() {
		
		vec2 scale = vec2(aspect, 1.0f) / 384.0f;
		vec2 texcoord = (gl_GlobalInvocationID.xy - vec2(width, height) * 0.5f) * scale + 0.5f;
		texcoord.x -= sin(gl_GlobalInvocationID.x * 0.01f + time * 3.0f) * aspect * 0.05f;
		texcoord.y += cos(gl_GlobalInvocationID.y * 0.01f + time * 5.0f) * 0.05f;
		
		vec4 color = textureLod(sampler2D(in_texture, in_sampler), texcoord, 0.0f) * vec4(0.5f, 0.7f, 1.0f, 1.0f);
		color += textureLod(sampler2D(in_texture, in_sampler), texcoord * 0.1f, 0.0f) + textureLod(sampler2D(in_texture, in_sampler), texcoord * 0.3f, 0.0f);
		color *= pow(clamp(2.0f + color.x - length(texcoord - 0.5f) + sin(time * 2.0f) * 0.5f, 0.0f, 1.0f), 4.0f) * 0.5f;
		
		imageStore(out_surface, ivec2(gl_GlobalInvocationID.xy), color);
	}
	
#elif VERTEX_SHADER
	
	layout(location = 0) out vec2 s_texcoord;
	
	/*
	 */
	void main() {
		
		vec2 texcoord = vec2(0.0f);
		if(gl_VertexIndex == 0) texcoord.x = 2.0f;
		if(gl_VertexIndex == 2) texcoord.y = 2.0f;
		
		gl_Position = vec4(texcoord * 2.0f - 1.0f, 0.0f, 1.0f);
		
		#if CLAY_VK
			texcoord.y = 1.0f - texcoord.y;
		#endif
		
		s_texcoord = texcoord;
	}
	
#elif FRAGMENT_SHADER
	
	layout(binding = 0, set = 1) uniform sampler in_sampler;
	layout(binding = 0, set = 0) uniform texture2D in_texture;
	
	layout(location = 0) in vec2 s_texcoord;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		out_color = texture(sampler2D(in_texture, in_sampler), s_texcoord);
	}
	
#endif

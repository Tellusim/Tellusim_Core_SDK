// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) out vec2 s_texcoord;
	
	/*
	 */
	void main() {
		
		vec2 texcoord = vec2(0.0f);
		if(gl_VertexIndex == 0) texcoord.x = 2.0f;
		if(gl_VertexIndex == 2) texcoord.y = 2.0f;
		
		gl_Position = vec4(texcoord * 2.0f - 1.0f, 0.0f, 1.0f);
		
		#if !CLAY_VK
			texcoord.y = 1.0f - texcoord.y;
		#endif
		
		s_texcoord = texcoord;
	}
	
#elif FRAGMENT_SHADER
	
	layout(std430, binding = 0) buffer tensor_buffer { float tensor_data[]; };
	
	layout(binding = 0, set = 1) uniform texture2D in_texture;
	layout(binding = 1, set = 1) uniform texture2D in_numbers;
	layout(binding = 0, set = 2) uniform sampler in_sampler;
	
	layout(location = 0) in vec2 s_texcoord;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec2 texcoord = s_texcoord * 24.0f;
		
		ivec2 id = ivec2(texcoord);
		
		texcoord = (texcoord - vec2(id)) * vec2(2.0f, 1.0f);
		
		vec4 color = vec4(texture(sampler2D(in_texture, in_sampler), (texcoord + ivec2(id)) / 24.0f).xxx, 1.0f);
		
		[[branch]] if(texcoord.x > 1.0f) {
			int value = 15;
			float weight = 0.0f;
			int index = (id.y * 24 + id.x) * 10;
			for(int i = 0; i < 10; i++) {
				float w = tensor_data[index + i];
				if(weight < w) {
					weight = w;
					value = i;
				}
			}
			texcoord = clamp(texcoord * 1.2f - vec2(1.2f, 0.1f), 0.0f, 1.0f);
			texcoord.x = (texcoord.x + float(value)) / 16.0f;
			color = vec4(textureLod(sampler2D(in_numbers, in_sampler), texcoord, 0.0f).x, 0.0f, 0.0f, 1.0f);
		}
		
		out_color = color;
	}
	
#endif

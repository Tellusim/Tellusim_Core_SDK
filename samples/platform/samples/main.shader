// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

/*
 */
#if RENDER_TARGET
	
	#if VERTEX_SHADER
		
		layout(location = 0) in vec4 in_position;
		layout(location = 1) in vec2 in_texcoord;
		
		/*
		 */
		void main() {
			
			gl_Position = in_position;
		}
		
	#elif FRAGMENT_SHADER
		
		layout(binding = 0) uniform CommonParameters {
			float time;
		};
		
		layout(location = 0) out vec4 out_color;
		
		/*
		 */
		void main() {
			
			vec3 color = cos(vec3(0.0f, 0.5f, 1.0f) * 3.14f + float(gl_SampleID) + time);
			
			out_color = vec4(color * 0.5f + 0.5f, 1.0f);
		}
		
	#endif
	
/*
 */
#elif VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec2 in_texcoord;
	
	layout(location = 0) out vec2 s_texcoord;
	
	/*
	 */
	void main() {
		
		gl_Position = in_position;
		
		s_texcoord = in_texcoord;
	}
	
#elif FRAGMENT_SHADER
	
	layout(binding = 0, set = 0) uniform texture2DMS in_texture;
	
	layout(location = 0) in vec2 s_texcoord;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		int index = 0;
		#if SAMPLES == 2
			if(s_texcoord.x > 0.5f) index += 1;
		#elif SAMPLES == 4
			if(s_texcoord.x > 0.5f) index += 2;
			if(s_texcoord.y > 0.5f) index += 1;
		#elif SAMPLES == 8
			if(s_texcoord.x > 0.25f) index += 2;
			if(s_texcoord.x > 0.50f) index += 2;
			if(s_texcoord.x > 0.75f) index += 2;
			if(s_texcoord.y > 0.50f) index += 1;
		#endif
		
		ivec2 size = textureSize(in_texture);
		
		out_color = texelFetch(in_texture, ivec2(s_texcoord * size), index);
	}
	
#endif

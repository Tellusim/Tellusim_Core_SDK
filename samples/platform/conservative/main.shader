// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

/*
 */
#if RENDER_TARGET
	
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
			
			vec4 position = transform * in_position;
			gl_Position = projection * (modelview * position);
		}
		
	#elif FRAGMENT_SHADER
		
		layout(location = 0) out vec4 out_color;
		
		/*
		 */
		void main() {
			
			out_color = vec4(0.5f, 0.5f, 0.5f, 1.0f);
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
	
	layout(binding = 0, set = 0) uniform texture2D in_texture;
	layout(binding = 0, set = 1) uniform sampler in_sampler;
	
	layout(location = 0) in vec2 s_texcoord;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		out_color = texture(sampler2D(in_texture, in_sampler), s_texcoord);
	}
	
#endif

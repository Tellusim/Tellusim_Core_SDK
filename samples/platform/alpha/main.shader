// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

/*
 */
#if RENDER_TARGET
	
	#if VERTEX_SHADER
		
		layout(location = 0) in vec4 in_position;
		layout(location = 1) in vec2 in_texcoord;
		
		layout(row_major, binding = 0) uniform CommonParameters {
			mat4 projection;
			mat4 modelview;
			mat4 transform;
		};
		
		layout(location = 0) out vec2 s_texcoord;
		
		/*
		 */
		void main() {
			
			gl_Position = projection * (modelview * (transform * in_position));
			
			s_texcoord = in_texcoord;
		}
		
	#elif FRAGMENT_SHADER
		
		layout(binding = 0, set = 1) uniform texture2D in_texture;
		layout(binding = 0, set = 2) uniform sampler in_sampler;
		
		layout(location = 0) in vec2 s_texcoord;
		
		layout(location = 0) out vec4 out_color;
		
		/*
		 */
		void main() {
			
			#if ALPHA_TO_COVERAGE
				
				float color = texture(sampler2D(in_texture, in_sampler), s_texcoord).x;
				
				out_color = vec4(vec3(color), (color - 0.5f) / fwidth(color) + 0.5f);
				
			#else
				
				int mask = 0;
				float color = 0.0f;
				vec2 dx = dFdx(s_texcoord);
				vec2 dy = dFdy(s_texcoord);
				
				#define SAMPLE(X, Y, MASK) { \
					color = texture(sampler2D(in_texture, in_sampler), s_texcoord + dx * X + dy * Y).x; \
					if(color >= 0.5f) mask |= MASK; \
				}
				
				#if MULTISAMPLE == 2
					SAMPLE( -0.25f, -0.25f, 0x01)
					SAMPLE(  0.25f,  0.25f, 0x02)
				#elif MULTISAMPLE == 4
					SAMPLE( -0.125f, -0.375f, 0x01)
					SAMPLE(  0.375f, -0.125f, 0x02)
					SAMPLE( -0.375f,  0.125f, 0x04)
					SAMPLE(  0.125f,  0.375f, 0x08)
				#elif MULTISAMPLE == 8
					SAMPLE(  0.4875f, -0.4375f, 0x01)
					SAMPLE( -0.1875f, -0.3125f, 0x02)
					SAMPLE(  0.0625f, -0.1875f, 0x04)
					SAMPLE( -0.4375f, -0.0125f, 0x08)
					SAMPLE(  0.3125f, -0.0125f, 0x10)
					SAMPLE( -0.0625f, -0.1875f, 0x20)
					SAMPLE( -0.3125f,  0.3125f, 0x40)
					SAMPLE(  0.1875f,  0.4375f, 0x80)
				#elif MULTISAMPLE == 16
					SAMPLE(  0.4875f, -0.4375f, 0x0003)
					SAMPLE( -0.1875f, -0.3125f, 0x000c)
					SAMPLE(  0.0625f, -0.1875f, 0x0030)
					SAMPLE( -0.4375f, -0.0125f, 0x00c0)
					SAMPLE(  0.3125f, -0.0125f, 0x0300)
					SAMPLE( -0.0625f, -0.1875f, 0x0c00)
					SAMPLE( -0.3125f,  0.3125f, 0x3000)
					SAMPLE(  0.1875f,  0.4375f, 0xc000)
				#endif
				
				out_color = texture(sampler2D(in_texture, in_sampler), s_texcoord).xxxw;
				
				gl_SampleMask[0] = mask;
				
			#endif
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
		
		vec4 color = vec4(0.0f);
		
		ivec2 size = textureSize(in_texture);
		
		for(int i = 0; i < MULTISAMPLE; i++) {
			color += texelFetch(in_texture, ivec2(s_texcoord * size), i);
		}
		
		out_color = color / MULTISAMPLE;
	}
	
#endif

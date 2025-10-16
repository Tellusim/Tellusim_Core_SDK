// Clay header

#version 430 core

/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec2 in_texcoord;
	
	layout(location = 0) out vec2 s_texcoord;
	
	layout(std140, binding = 0) uniform CommonParameters {
		float aspect;
	};
	
	/*
	 */
	void main() {
		
		gl_Position = in_position;
		
		if(aspect > 1.0f) {
			s_texcoord = vec2((in_texcoord.x - 0.5f) * aspect + 0.5f, in_texcoord.y);
		} else {
			s_texcoord = vec2(in_texcoord.x, (in_texcoord.y - 0.5f) / aspect + 0.5f);
		}
	}
	
#elif FRAGMENT_SHADER
	
	layout(std430, binding = 1) readonly buffer mapped_buffer { uint mapped_data[]; };
	
	layout(location = 0) in vec2 s_texcoord;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		uint color = 0;
		
		ivec2 texcoord = ivec2(s_texcoord * 512.0f);
		
		[[branch]] if(texcoord.x >= 0 && texcoord.y >= 0 && texcoord.x < 512 && texcoord.y < 512) {
			color = mapped_data[512 * texcoord.y + texcoord.x];
		}
		
		out_color = unpackUnorm4x8(color);
	}
	
#endif

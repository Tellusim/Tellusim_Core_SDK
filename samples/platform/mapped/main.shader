// Clay header

#version 430 core

/*
 */
#if COMPUTE_SHADER
	
	layout(local_size_x = 8, local_size_y = 8) in;
	
	layout(std140, binding = 0) uniform ComputeParameters {
		float time;
	};
	
	layout(std430, binding = 1) buffer MappedBuffer { uint mapped_buffer[]; };
	
	/*
	 */
	void main() {
		
		ivec2 global_id = gl_GlobalInvocationID.xy;
		
		[[branch]] if((global_id.x < 32 || global_id.x > WIDTH - 32) || (global_id.y < 32 || global_id.y > HEIGHT - 32)) {
			
			uint index = WIDTH * global_id.y + global_id.x;
			
			vec4 color = unpackUnorm4x8(mapped_buffer[index]);
			
			color.x = sin(time) * 0.5f + 0.5f;
			
			mapped_buffer[index] = packUnorm4x8(color);
		}
		
		[[branch]] if(global_id.x == 0 && global_id.y == 0) {
			mapped_buffer[0] = ~0u;
		}
	}
	
#elif VERTEX_SHADER
	
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
	
	layout(std430, binding = 1) readonly buffer MappedBuffer { uint mapped_buffer[]; };
	
	layout(location = 0) in vec2 s_texcoord;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		uint color = 0;
		
		ivec2 texcoord = ivec2(s_texcoord * WIDTH.0f);
		
		[[branch]] if(texcoord.x >= 0 && texcoord.y >= 0 && texcoord.x < WIDTH && texcoord.y < HEIGHT) {
			color = mapped_buffer[WIDTH * texcoord.y + texcoord.x];
		}
		
		out_color = unpackUnorm4x8(color);
	}
	
#endif

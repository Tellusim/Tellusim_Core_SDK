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
		uint depth;
		uint layers;
	};
	
	layout(std430, binding = 1) buffer TensorBuffer { float tensor_buffer[]; };
	
	/*
	 */
	void main() {
		
		uvec3 global_id = gl_GlobalInvocationID.xyz;
		if(global_id.x >= width || global_id.y >= height) return;
		
		uint index = width * (height * global_id.z + global_id.y) + global_id.x;
		
		float value = tensor_buffer[index];
		value = floor(value * 255.0f) / 255.0f;
		tensor_buffer[index] = value;
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
		
		#if !CLAY_VK
			texcoord.y = 1.0f - texcoord.y;
		#endif
		
		s_texcoord = texcoord;
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

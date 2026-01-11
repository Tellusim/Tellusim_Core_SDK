// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if COMPUTE_SHADER
	
	layout(local_size_x = 8, local_size_y = 8) in;
	
	layout(std140, binding = 0) uniform compute_parameters {
		vec4 positions_x;
		vec4 positions_y;
		uvec2 offset;
	};
	
	layout(binding = 0, set = 1, rgba8) uniform writeonly image2D out_surface;
	
	/*
	 */
	void main() {
		
		uvec2 global_id = gl_GlobalInvocationID.xy;
		
		vec4 distances_x = clamp(1.0f - pow(abs(vec4(offset.x + global_id.x) - positions_x), 2.0f) / 32.0f, 0.02f, 1.0f);
		vec4 distances_y = clamp(1.0f - pow(abs(vec4(offset.y + global_id.y) - positions_y), 2.0f) / 32.0f, 0.02f, 1.0f);
		
		float distance = dot(distances_x + distances_y, vec4(1.0f));
		
		imageStore(out_surface, ivec2(global_id + offset), vec4(distance));
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

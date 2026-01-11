// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

layout(std140, binding = 0) uniform CommonParameters {
	uint offset;
	float time;
};

/*
 */
#if VERTEX_SHADER || MESH_SHADER
	
	/*
	 */
	vec4 get_position(vec2 p, float time) {
		p.x *= cos(p.y * 3.0f + time * 3.0f) * 0.25f + 0.75f;
		p.y *= sin(p.x * 4.0f + time * 2.0f) * 0.25f + 0.75f;
		return vec4(p, 0.0f, 1.0f);
	}
	
	vec4 get_color(vec2 p, float time) {
		float k = time * 2.0f;
		float s = sin(time * 0.5f);
		float c = cos(time * 0.5f);
		p = vec2(s * p.x + c * p.y, c * p.x - s * p.y) * 32.0f - 16.0f;
		float v = sin(p.x + k) + sin(p.y + k) + sin(p.x + p.y + k) + sin(length(p) + k * 3.0f) + k * 2.0f;
		return vec4((cos(vec3(0.0f, 1.57f, 3.14f) + v) * 0.5f) + 0.5f, 1.0f);
	}
	
#endif
	
/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) out vec4 s_color;
	
	/*
	 */
	void main() {
		
		uint index = gl_VertexIndex / 6;
		
		uvec2 group_id = uvec2(index % (16 * 8), index / (16 * 8) + offset);
		
		index = gl_VertexIndex % 6;
		
		if(index == 1u || index == 2u || index == 3u) group_id.x += 1;
		if(index == 2u || index == 3u || index == 4u) group_id.y += 1;
		
		float iscale = 1.0f / (16.0f * 8.0f + 1.0f);
		vec2 position = vec2(group_id) * iscale * 2.0f - 1.0f;
		
		gl_Position = get_position(position, time);
		
		s_color = get_color(position, time);
	}
	
#elif MESH_SHADER
	
	layout(local_size_x = 1) in;
	
	layout(triangles, max_vertices = 4, max_primitives = 2) out;
	
	layout(location = 0) out VertexOut {
		vec4 color;
	} OUT[4];
	
	/*
	 */
	void main() {
		
		uvec2 group_id = uvec2(gl_WorkGroupID.x, gl_WorkGroupID.y + offset);
		
		SetMeshOutputsEXT(4, 2);
		
		float iscale = 1.0f / (16.0f * 8.0f + 1.0f);
		vec2 position = vec2(group_id + 1) * iscale * 2.0f - 1.0f;
		vec2 position_0 = position + vec2(-1.0f,  1.0f) * iscale;
		vec2 position_1 = position + vec2(-1.0f, -1.0f) * iscale;
		vec2 position_2 = position + vec2( 1.0f, -1.0f) * iscale;
		vec2 position_3 = position + vec2( 1.0f,  1.0f) * iscale;
		
		gl_MeshVerticesEXT[0].gl_Position = get_position(position_0, time);
		gl_MeshVerticesEXT[1].gl_Position = get_position(position_1, time);
		gl_MeshVerticesEXT[2].gl_Position = get_position(position_2, time);
		gl_MeshVerticesEXT[3].gl_Position = get_position(position_3, time);
		
		OUT[0].color = get_color(position_0, time);
		OUT[1].color = get_color(position_1, time);
		OUT[2].color = get_color(position_2, time);
		OUT[3].color = get_color(position_3, time);
		
		gl_PrimitiveTriangleIndicesEXT[0] = uvec3(0, 1, 2);
		gl_PrimitiveTriangleIndicesEXT[1] = uvec3(2, 3, 0);
	}
	
#elif FRAGMENT_0_SHADER || FRAGMENT_1_SHADER
	
	layout(location = 0) in vec4 s_color;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		#if FRAGMENT_0_SHADER
			out_color = s_color;
		#elif FRAGMENT_1_SHADER
			out_color = 1.0f - s_color;
		#endif
	}
	
#endif

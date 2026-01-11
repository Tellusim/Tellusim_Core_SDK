// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if COMPUTE_SHADER || VERTEX_SHADER
	
	#define REFERENCE	1
	//#define ARRAY		1
	//#define VECTOR	1
	
	struct Vertex {
		#if REFERENCE
			#if ARRAY
				float position_x;
				float position_y;
				float position_z;
				float normal[3];
				float texcoord[2];
			#elif VECTOR
				vec4 data[2];
			#else
				vec4 position_normal;
				vec4 normal_texcoord;
			#endif
		#else
			vec4 position_normal;
			vec4 normal_texcoord;
		#endif
	};
	
#endif
	
/*
 */
#if COMPUTE_SHADER
	
	layout(local_size_x = 32) in;
	
	layout(row_major, binding = 0) uniform ComputeParameters {
		int num_vertices;
		int width;
		int height;
		float time;
	};
	
	#if REFERENCE
		#if ARRAY || VECTOR
			layout(std430, binding = 1) readonly buffer VertexBuffer { uint vertex_buffer[]; };
			layout(std430, binding = 0, set = 1) buffer VertexBuffers { uint vertex_buffer[]; } vertex_buffers[];
		#else
			layout(std430, binding = 1) readonly buffer VertexBuffer { uvec4 vertex_buffer[]; };
			layout(std430, binding = 0, set = 1) buffer VertexBuffers { uvec4 vertex_buffer[]; } vertex_buffers[];
		#endif
	#else
		layout(std430, binding = 1) readonly buffer VertexBuffer { Vertex vertex_buffer[]; };
		layout(std430, binding = 0, set = 1) buffer VertexBuffers { Vertex vertex_buffer[]; } vertex_buffers[];
	#endif
	
	/*
	 */
	void main() {
		
		ivec2 global_id = gl_GlobalInvocationID.xy;
		
		[[branch]] if(global_id.x < num_vertices && global_id.y < width * height) {
			
			// load vertex
			#if REFERENCE
				#if ARRAY
					Vertex &static_vertex = Vertex(vertex_buffer, global_id.x * 8);
					vec4 position_normal = vec4(static_vertex.position_x, static_vertex.position_y, static_vertex.position_z, static_vertex.normal[0]);
					vec4 normal_texcoord = vec4(static_vertex.normal[1], static_vertex.normal[2], static_vertex.texcoord[0], static_vertex.texcoord[1]);
				#elif VECTOR
					Vertex &static_vertex = Vertex(vertex_buffer, global_id.x * 8);
					vec4 position_normal = vec4(static_vertex.data[0].x, static_vertex.data[0].y, static_vertex.data[0].z, static_vertex.data[0].w);
					vec4 normal_texcoord = vec4(static_vertex.data[1][0], static_vertex.data[1][1], static_vertex.data[1][2], static_vertex.data[1][3]);
				#else
					Vertex &static_vertex = Vertex(vertex_buffer, global_id.x * 2);
					vec4 position_normal = static_vertex.position_normal;
					vec4 normal_texcoord = static_vertex.normal_texcoord;
				#endif
			#else
				vec4 position_normal = vertex_buffer[global_id.x].position_normal;
				vec4 normal_texcoord = vertex_buffer[global_id.x].normal_texcoord;
			#endif
			
			// transform vertex
			position_normal.x += float(global_id.y % width) - width * 0.5f + 0.5f;
			position_normal.y += float(global_id.y / width) - height * 0.5f + 0.5f;
			position_normal.z += cos(length(position_normal.xy) * 0.3f + time * 2.0f);
			
			// save vertex
			#if REFERENCE
				#if ARRAY
					Vertex &dynamic_vertex = Vertex(vertex_buffers[global_id.y].vertex_buffer, global_id.x * 8);
					dynamic_vertex.position_x = position_normal.x;
					dynamic_vertex.position_y = position_normal.y;
					dynamic_vertex.position_z = position_normal.z;
					dynamic_vertex.normal[0] = position_normal.w;
					dynamic_vertex.normal[1] = normal_texcoord.x;
					dynamic_vertex.normal[2] = normal_texcoord.y;
					dynamic_vertex.texcoord[0] = normal_texcoord.z;
					dynamic_vertex.texcoord[1] = normal_texcoord.w;
				#elif VECTOR
					Vertex &dynamic_vertex = Vertex(vertex_buffers[global_id.y].vertex_buffer, global_id.x * 8);
					dynamic_vertex.data[0].x = position_normal.x;
					dynamic_vertex.data[0].y = position_normal.y;
					dynamic_vertex.data[0].z = position_normal.z;
					dynamic_vertex.data[0].w = position_normal.w;
					dynamic_vertex.data[1][0] = normal_texcoord.x;
					dynamic_vertex.data[1][1] = normal_texcoord.y;
					dynamic_vertex.data[1][2] = normal_texcoord.z;
					dynamic_vertex.data[1][3] = normal_texcoord.w;
				#else
					Vertex &dynamic_vertex = Vertex(vertex_buffers[global_id.y].vertex_buffer, global_id.x * 2);
					dynamic_vertex.position_normal = position_normal;
					dynamic_vertex.normal_texcoord = normal_texcoord;
				#endif
			#else
				vertex_buffers[global_id.y].vertex_buffer[global_id.x].position_normal = position_normal;
				vertex_buffers[global_id.y].vertex_buffer[global_id.x].normal_texcoord = normal_texcoord;
			#endif
		}
		
		memoryBarrier();
	}
	
#elif VERTEX_SHADER
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		vec4 camera;
		int base_instance;
	};
	
	#if REFERENCE
		#if ARRAY || VECTOR
			layout(std430, binding = 1) readonly buffer VertexBuffer { uint vertex_buffer[]; };
			layout(std430, binding = 0, set = 4) readonly buffer VertexBuffers { uint vertex_buffer[]; } vertex_buffers[];
		#else
			layout(std430, binding = 1) readonly buffer VertexBuffer { vec4 vertex_buffer[]; };
			layout(std430, binding = 0, set = 4) readonly buffer VertexBuffers { vec4 vertex_buffer[]; } vertex_buffers[];
		#endif
	#else
		layout(std430, binding = 1) readonly buffer VertexBuffer { Vertex vertex_buffer[]; };
		layout(std430, binding = 0, set = 4) readonly buffer VertexBuffers { Vertex vertex_buffer[]; } vertex_buffers[];
	#endif
	
	layout(location = 0) flat out int s_instance;
	layout(location = 1) out vec3 s_direction;
	layout(location = 2) out vec3 s_normal;
	layout(location = 3) out vec2 s_texcoord;
	
	/*
	 */
	void main() {
		
		int instance_index = gl_InstanceIndex + base_instance;
		
		#if REFERENCE
			#if ARRAY
				Vertex &static_vertex = Vertex(vertex_buffer, gl_VertexIndex * 8);
				Vertex &dynamic_vertex = Vertex(vertex_buffers[nonuniformEXT(instance_index)].vertex_buffer, gl_VertexIndex * 8);
				vec4 position_normal = vec4(static_vertex.position_x, static_vertex.position_y, static_vertex.position_z, static_vertex.normal[0]);
				vec4 normal_texcoord = vec4(static_vertex.normal[1], static_vertex.normal[2], static_vertex.texcoord[0], static_vertex.texcoord[1]);
				vec4 dynamic_position = vec4(dynamic_vertex.position_x, dynamic_vertex.position_y, dynamic_vertex.position_z, dynamic_vertex.normal[0]);
			#elif VECTOR
				Vertex &static_vertex = Vertex(vertex_buffer, gl_VertexIndex * 8);
				Vertex &dynamic_vertex = Vertex(vertex_buffers[nonuniformEXT(instance_index)].vertex_buffer, gl_VertexIndex * 8);
				vec4 position_normal = vec4(static_vertex.data[0].x, static_vertex.data[0].y, static_vertex.data[0].z, static_vertex.data[0].w);
				vec4 normal_texcoord = vec4(static_vertex.data[1][0], static_vertex.data[1][1], static_vertex.data[1][2], static_vertex.data[1][3]);
				vec4 dynamic_position = vec4(dynamic_vertex.data[0][0], dynamic_vertex.data[0][1], dynamic_vertex.data[0][2], dynamic_vertex.data[0][3]);
			#else
				Vertex &static_vertex = Vertex(vertex_buffer, gl_VertexIndex * 2);
				Vertex &dynamic_vertex = Vertex(vertex_buffers[nonuniformEXT(instance_index)].vertex_buffer, gl_VertexIndex * 2);
				vec4 position_normal = static_vertex.position_normal;
				vec4 normal_texcoord = static_vertex.normal_texcoord;
				vec4 dynamic_position = dynamic_vertex.position_normal;
			#endif
		#else
			vec4 position_normal = vertex_buffer[gl_VertexIndex].position_normal;
			vec4 normal_texcoord = vertex_buffer[gl_VertexIndex].normal_texcoord;
			vec4 dynamic_position = vertex_buffers[nonuniformEXT(instance_index)].vertex_buffer[gl_VertexIndex].position_normal;
		#endif
		
		vec4 position = vec4(dynamic_position.xyz, 1.0f);
		gl_Position = projection * (modelview * position);
		
		s_instance = instance_index;
		s_direction = camera.xyz - position.xyz;
		s_normal = vec3(position_normal.w, normal_texcoord.xy);
		s_texcoord = normal_texcoord.zw;
	}
	
#elif FRAGMENT_SHADER
	
	layout(binding = 0, set = 2) uniform sampler in_sampler;
	layout(binding = 0, set = 1) uniform texture2D in_texture;
	layout(binding = 0, set = 3) uniform texture2D in_textures[];
	
	layout(location = 0) flat in int s_instance;
	layout(location = 1) in vec3 s_direction;
	layout(location = 2) in vec3 s_normal;
	layout(location = 3) in vec2 s_texcoord;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec3 direction = normalize(s_direction);
		vec3 normal = normalize(s_normal);
		
		float diffuse = clamp(dot(direction, normal), 0.0f, 1.0f) * 0.75f;
		float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0f, 1.0f), 16.0f);
		
		vec4 color = texture(sampler2D(in_texture, in_sampler), s_texcoord);
		#if CLAY_D3D12
			color *= texture(sampler2D(in_textures[nonuniformEXT(s_instance)], in_sampler), s_texcoord);
		#else
			color *= texture(nonuniformEXT(sampler2D(in_textures[s_instance], in_sampler)), s_texcoord);
		#endif
		
		out_color = color * (diffuse + specular);
	}
	
#endif

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

/*
 */
#if RENDER_TARGET
	
	#if VERTEX_SHADER
		
		layout(location = 0) in vec4 in_position;
		layout(location = 1) in vec3 in_normal;
		
		layout(row_major, binding = 0) uniform CommonParameters {
			mat4 projection;
			mat4 modelview;
			vec4 camera;
		};
		
		#if VERTEX_LAYER
			layout(location = 0) out vec3 s_direction;
			layout(location = 1) out vec3 s_normal;
			layout(location = 2) out vec4 s_color;
		#else
			layout(location = 0) out vec3 s_directions;
			layout(location = 1) out vec3 s_normals;
			layout(location = 2) out vec4 s_colors;
			layout(location = 3) out float s_layers;
		#endif
		
		/*
		 */
		void main() {
			
			vec4 position = in_position;
			position.x += float((gl_InstanceIndex / NUM_LAYERS) / 4) - 1.5f;
			position.y += float((gl_InstanceIndex / NUM_LAYERS) % 4) - 1.5f;
			
			gl_Position = projection * (modelview * position);
			
			uint layer = gl_InstanceIndex % NUM_LAYERS;
			
			vec3 color = cos(vec3(0.0f, 0.5f, 1.0f) * 3.14f + float(layer)) * 0.5f + 0.5f;
			
			#if VERTEX_LAYER
				s_normal = in_normal;
				s_direction = camera.xyz - position.xyz;
				s_color = vec4(color, 1.0f);
				gl_Layer = layer;
			#else
				s_normals = in_normal;
				s_directions = camera.xyz - position.xyz;
				s_colors = vec4(color, 1.0f);
				s_layers = float(layer);
			#endif
		}
		
	#elif GEOMETRY_SHADER
		
		#if GEOMETRY_PASSTHROUGH
			
			#extension GL_NV_geometry_shader_passthrough : enable
			
			layout(triangles) in;
			
			layout(passthrough) in gl_PerVertex { vec4 gl_Position; } gl_in[];
			layout(passthrough, location = 0) in vec3 s_directions[3];
			layout(passthrough, location = 1) in vec3 s_normals[3];
			layout(passthrough, location = 2) in vec4 s_colors[3];
			layout(location = 3) in float s_layers[3];
			
			/*
			 */
			void main() {
				
				gl_Layer = int(s_layers[0]);
			}
			
		#else
			
			layout(triangles) in;
			
			layout(triangle_strip, max_vertices = 3) out;
			
			layout(location = 0) in vec3 s_directions[3];
			layout(location = 1) in vec3 s_normals[3];
			layout(location = 2) in vec4 s_colors[3];
			layout(location = 3) in float s_layers[3];
			
			layout(location = 0) out vec3 s_direction;
			layout(location = 1) out vec3 s_normal;
			layout(location = 2) out vec4 s_color;
			
			/*
			 */
			void main() {
				
				gl_Layer = int(s_layers[0]);
				
				for(int i = 0; i < 3; i++) {
					gl_Position = gl_in[i].gl_Position;
					s_direction = s_directions[i];
					s_normal = s_normals[i];
					s_color = s_colors[i];
					EmitVertex();
				}
				EndPrimitive();
			}
			
		#endif
		
	#elif FRAGMENT_SHADER
		
		layout(location = 0) in vec3 s_direction;
		layout(location = 1) in vec3 s_normal;
		layout(location = 2) in vec4 s_color;
		
		layout(location = 0) out vec4 out_color;
		
		/*
		 */
		void main() {
			
			vec3 direction = normalize(s_direction);
			vec3 normal = normalize(s_normal);
			
			float diffuse = clamp(dot(direction, normal), 0.0f, 1.0f) * 0.75f;
			float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0f, 1.0f), 8.0f);
			
			out_color = s_color * (diffuse + specular);
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
		
		s_texcoord = in_texcoord * 16.0f;
	}
	
#elif FRAGMENT_SHADER
	
	layout(binding = 0, set = 0) uniform texture2DArray in_texture;
	layout(binding = 0, set = 1) uniform sampler in_sampler;
	
	layout(location = 0) in vec2 s_texcoord;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		float layer = 0.0f;
		for(float x = 1.0f; x < 16.0f; x += 1.0f) {
			if(s_texcoord.x > x) layer += 1.0f;
			if(s_texcoord.y > x) layer += 16.0f;
		}
		
		out_color = texture(sampler2DArray(in_texture, in_sampler), vec3(s_texcoord, layer));
	}
	
#endif

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
		
		layout(binding = 1) uniform ColorParameters {
			vec4 colors[NUM_COLORS];
		};
		
		#if VERTEX_INDEX
			layout(location = 0) out vec3 s_direction;
			layout(location = 1) out vec3 s_normal;
			layout(location = 2) out vec4 s_color;
		#else
			layout(location = 0) out vec3 s_directions;
			layout(location = 1) out vec3 s_normals;
			layout(location = 2) out vec4 s_colors;
			layout(location = 3) out float s_viewports;
		#endif
		
		/*
		 */
		void main() {
			
			vec4 position = in_position;
			position.x += float((gl_InstanceIndex / NUM_VIEWPORTS) / 16) - 7.5f;
			position.y += float((gl_InstanceIndex / NUM_VIEWPORTS) % 16) - 7.5f;
			
			gl_Position = projection * (modelview * position);
			
			int viewport = gl_InstanceIndex % NUM_VIEWPORTS;
			
			#if VERTEX_INDEX
				s_normal = in_normal;
				s_direction = camera.xyz - position.xyz;
				s_color = colors[viewport % NUM_COLORS];
				gl_ViewportIndex = viewport;
			#else
				s_normals = in_normal;
				s_directions = camera.xyz - position.xyz;
				s_colors = colors[viewport % NUM_COLORS];
				s_viewports = float(viewport);
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
			layout(location = 3) in float s_viewports[3];
			
			/*
			 */
			void main() {
				
				gl_ViewportIndex = int(s_viewports[0]);
			}
			
		#else
			
			layout(triangles) in;
			
			layout(triangle_strip, max_vertices = 3) out;
			
			layout(location = 0) in vec3 s_directions[3];
			layout(location = 1) in vec3 s_normals[3];
			layout(location = 2) in vec4 s_colors[3];
			layout(location = 3) in float s_viewports[3];
			
			layout(location = 0) out vec3 s_direction;
			layout(location = 1) out vec3 s_normal;
			layout(location = 2) out vec4 s_color;
			
			/*
			 */
			void main() {
				
				gl_ViewportIndex = int(s_viewports[0]);
				
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

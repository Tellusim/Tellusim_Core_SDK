// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec3 in_normal;
	layout(location = 2) in vec4 in_tangent;
	layout(location = 3) in vec2 in_texcoord;
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		mat4 transform;
		vec4 camera;
		vec4 light;
	};
	
	layout(location = 0) out vec3 s_normal;
	layout(location = 1) out vec4 s_tangent;
	layout(location = 2) out vec2 s_texcoord;
	layout(location = 3) out vec3 s_view_vector;
	layout(location = 4) out vec3 s_light_vector;
	
	/*
	 */
	void main() {
		
		vec4 position = transform * in_position;
		gl_Position = projection * (modelview * position);
		
		s_normal = (transform * vec4(in_normal, 0.0f)).xyz;
		s_tangent = vec4((transform * vec4(in_tangent.xyz, 0.0f)).xyz, in_tangent.w);
		
		s_texcoord.x = in_texcoord.x;
		s_texcoord.y = 1.0f - in_texcoord.y;
		
		s_view_vector = camera.xyz - position.xyz;
		s_light_vector = light.xyz - position.xyz;
	}
	
#elif FRAGMENT_SHADER
	
	layout(binding = 0, set = 2) uniform sampler in_sampler;
	layout(binding = 0, set = 1) uniform texture2D in_normal_texture;
	layout(binding = 1, set = 1) uniform texture2D in_height_texture;
	
	layout(location = 0) in vec3 s_normal;
	layout(location = 1) in vec4 s_tangent;
	layout(location = 2) in vec2 s_texcoord;
	layout(location = 3) in vec3 s_view_vector;
	layout(location = 4) in vec3 s_light_vector;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec3 view_vector = normalize(s_view_vector);
		vec3 light_vector = normalize(s_light_vector);
		
		vec3 basis_normal = normalize(s_normal);
		vec3 basis_binormal = cross(basis_normal, s_tangent.xyz);
		vec3 basis_tangent = normalize(cross(basis_binormal, basis_normal));
		basis_binormal = normalize(basis_binormal * sign(s_tangent.w));
		
		float height_scale = 0.12f;
		float iscale = 1.0f / dot(basis_normal, view_vector);
		float steps = clamp(16.0f * iscale, 16.0f, 64.0f);
		float isteps = 1.0f / steps;
		
		vec2 texcoord = s_texcoord;
		vec2 step = vec2(-dot(basis_tangent, view_vector), dot(basis_binormal, view_vector)) * (iscale * isteps * height_scale);
		
		#if FAST
			
			float old_height = 0.0f;
			[[loop]] for(float threshold = 1.0f; threshold > 0.0f; threshold -= isteps) {
				float height = textureLod(sampler2D(in_height_texture, in_sampler), texcoord, 0.0f).x - threshold;
				[[branch]] if(height > 0.0f) {
					texcoord -= step * (height / (height - old_height));
					threshold = 0.0f;
				}
				old_height = height;
				texcoord += step;
			}
			
		#else
			
			float threshold = 1.0f;
			float old_height = -1.0f;
			[[loop]] for(float i = 0.0f; i < steps; i += 1.0f) {
				float height = textureLod(sampler2D(in_height_texture, in_sampler), texcoord, 0.0f).x - threshold;
				[[branch]] if((height > 0.0f) != (old_height > 0.0f)) {
					if(dot(step, step) < 1e-6f) i = steps;
					isteps = -isteps * 0.5f;
					step = -step * 0.5f;
				}
				old_height = height;
				threshold -= isteps;
				texcoord += step;
			}
			
			float height = textureLod(sampler2D(in_height_texture, in_sampler), texcoord, 0.0f).x - threshold;
			texcoord += step * (height / (old_height - height));
			
		#endif
		
		vec3 normal = texture(sampler2D(in_normal_texture, in_sampler), texcoord).xyz * 2.0f - 1.0f;
		normal.z = sqrt(clamp(1.0f - dot(normal.xy, normal.xy), 0.0f, 1.0f));
		normal = basis_tangent * normal.x + basis_binormal * normal.y + basis_normal * normal.z;
		
		float shadow = 1.0f;
		float diffuse = clamp(dot(light_vector, normal), 0.0f, 1.0f) * 0.5f;
		float specular = pow(clamp(dot(reflect(-light_vector, normal), view_vector), 0.0f, 1.0f), 32.0f);
		
		[[branch]] if(diffuse > 0.0f) {
			
			iscale = 1.0f / dot(basis_normal, light_vector);
			steps = clamp(32.0f * iscale, 16.0f, 64.0f);
			isteps = 1.0f / steps;
			
			height = textureLod(sampler2D(in_height_texture, in_sampler), texcoord, 0.0f).x;
			step = vec2(dot(basis_tangent, light_vector), dot(-basis_binormal, light_vector)) * (iscale * isteps * height_scale);
			texcoord += step;
			
			[[loop]] for(float threshold = 1.0f; threshold > 0.0f && shadow > 0.0f; threshold -= isteps) {
				float h = textureLod(sampler2D(in_height_texture, in_sampler), texcoord, 0.0f).x - height;
				shadow = max(shadow - max(h * 0.1f, 0.0f), 0.0f);
				texcoord += step;
			}
		}
		
		out_color = vec4(pow((diffuse + specular) * clamp(shadow + 0.05f, 0.0f, 1.0f), 1.0f / 2.2f));
	}
	
#endif

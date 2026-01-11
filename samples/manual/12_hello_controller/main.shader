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
	};
	
	layout(location = 0) out vec3 s_camera;
	layout(location = 1) out vec3 s_normal;
	layout(location = 2) out vec4 s_tangent;
	layout(location = 3) out vec2 s_texcoord;
	
	/*
	 */
	void main() {
		
		vec4 position = in_position * transform;
		gl_Position = projection * (modelview * position);
		
		s_camera = camera.xyz - position.xyz;
		s_normal = ((vec4(in_normal, 0.0f) * transform)).xyz;
		s_tangent = vec4(((vec4(in_tangent.xyz, 0.0f) * transform)).xyz, in_tangent.w);
		s_texcoord = vec2(in_texcoord.x, 1.0f - in_texcoord.y);
	}
	
#elif FRAGMENT_SHADER
	
	layout(binding = 0, set = 1) uniform texture2D in_normal_texture;
	layout(binding = 1, set = 1) uniform texture2D in_diffuse_texture;
	layout(binding = 2, set = 1) uniform texture2D in_metallic_texture;
	layout(binding = 0, set = 2) uniform sampler in_sampler;
	
	layout(location = 0) in vec3 s_camera;
	layout(location = 1) in vec3 s_normal;
	layout(location = 2) in vec4 s_tangent;
	layout(location = 3) in vec2 s_texcoord;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec3 direction = normalize(s_camera);
		vec3 basis_normal = normalize(s_normal);
		vec3 basis_tangent = normalize(s_tangent.xyz - basis_normal * dot(basis_normal, s_tangent.xyz));
		vec3 basis_binormal = normalize(cross(basis_normal, basis_tangent) * s_tangent.w);
		
		vec3 normal = vec3(texture(sampler2D(in_normal_texture, in_sampler), s_texcoord).xy * 2.0f - 254.0f / 255.0f, 0.0f);
		normal = basis_tangent * normal.x + basis_binormal * normal.y + basis_normal * sqrt(max(1.0f - dot(normal.xy, normal.xy), 0.0f));
		
		vec3 diffuse_color = texture(sampler2D(in_diffuse_texture, in_sampler), s_texcoord).xyz;
		diffuse_color = pow(diffuse_color, vec3(2.2f));
		
		vec3 metallic_color = texture(sampler2D(in_metallic_texture, in_sampler), s_texcoord).xyz;
		metallic_color = pow(metallic_color, vec3(2.2f));
		
		float reflectance = 0.1f;
		float metallic = metallic_color.z;
		vec3 specular_color = mix(vec3(reflectance), diffuse_color, metallic);
		//diffuse_color *= (1.0f - reflectance) * (1.0f - metallic);
		
		float roughness = metallic_color.y;
		float power = 2.0f / max(roughness, 1e-6f);
		
		vec3 diffuse = diffuse_color * clamp(dot(direction, normal), 0.0f, 1.0f);
		vec3 specular = specular_color * pow(clamp(dot(reflect(-direction, normal), direction), 0.0f, 1.0f), power);
		
		out_color = vec4(pow(diffuse + specular, vec3(1.0f / 2.2f)), 1.0f);
	}
	
#endif

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 420 core

/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec3 in_normal;
	layout(location = 2) in uint in_index;
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		mat4 transform;
		vec4 camera;
		float time;
	};
	
	layout(binding = 1) uniform TargetParameters {
		uint base_target;
		uint num_targets;
		uint num_vertices;
	};
	
	#if TEXEL
		layout(binding = 0, set = 1) uniform samplerBuffer in_targets;
	#else
		layout(std430, binding = 2) readonly buffer TargetsBuffer { uint targets_buffer[]; };
	#endif
	
	layout(location = 0) out vec3 s_direction;
	layout(location = 1) out vec3 s_normal;
	
	/*
	 */
	void main() {
		
		vec4 position = in_position;
		vec4 normal = vec4(in_normal, 0.0f);
		
		// gl_VertexIndex is wrong for meshes with multiple indices/materials
		#if TEXEL
			uint index = base_target + in_index;
		#else
			uint index = base_target + in_index * 2u;
		#endif
		
		float morph_weight = 1.0f;
		vec3 morph_position = vec3(0.0f);
		vec3 morph_normal = vec3(0.0f);
		
		for(uint i = 0u; i < num_targets; i++) {
			
			float weight = 1.0f - abs(smoothstep(float(i), float(i + 3u), mod(time * 5.0f, float(num_targets + 2u))) * 2.0f - 1.0f);
			
			morph_weight -= weight;
			
			// morph position
			#if TEXEL
				morph_position += texelFetch(in_targets, index).xyz * weight;
				index += num_vertices;
			#else
				morph_position.xy += unpackHalf2x16(targets_buffer[index + 0u]) * weight;
				morph_position.z += unpackHalf2x16(targets_buffer[index + 1u]).x * weight;
				index += num_vertices * 2u;
			#endif
			
			// morph normal
			#if TEXEL
				morph_normal += texelFetch(in_targets, index).xyz * weight;
				index += num_vertices;
			#else
				morph_normal += mix(normal.xyz, vec3(unpackHalf2x16(targets_buffer[index + 0u]), unpackHalf2x16(targets_buffer[index + 1u]).x), weight) * abs(weight);
				index += num_vertices * 2u;
			#endif
		}
		
		position.xyz = position.xyz * morph_weight + morph_position;
		
		float normal_length2 = dot(morph_normal, morph_normal);
		if(normal_length2 > 0.0f) normal.xyz = morph_normal * inversesqrt(normal_length2);
		
		position = transform * position;
		gl_Position = projection * (modelview * position);
		
		s_direction = camera.xyz - position.xyz;
		s_normal = (transform * normal).xyz;
	}
	
#elif FRAGMENT_SHADER
	
	layout(location = 0) in vec3 s_direction;
	layout(location = 1) in vec3 s_normal;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec3 direction = normalize(s_direction);
		vec3 normal = normalize(s_normal);
		
		float diffuse = clamp(dot(direction, normal), 0.0f, 1.0f);
		float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0f, 1.0f), 16.0f);
		
		out_color = vec4(diffuse + specular);
	}
	
#endif

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 460 core

/*
 */
#if VERTEX_SHADER || FRAGMENT_SHADER
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		mat4 transform;
		vec4 camera;
		vec4 light;
	};
	
#endif

/*
 */
#if VERTEX_SHADER
	
	layout(location = 0) in vec4 in_position;
	layout(location = 1) in vec3 in_normal;
	
	layout(location = 0) out vec3 s_position;
	layout(location = 1) out vec3 s_normal;
	
	/*
	 */
	void main() {
		
		vec4 position = transform * in_position;
		gl_Position = projection * (modelview * position);
		
		s_position = position.xyz;
		
		s_normal = (transform * vec4(in_normal, 0.0f)).xyz;
	}
	
#elif FRAGMENT_SHADER
	
	layout(binding = 0, set = 1) uniform accelerationStructureEXT tracing;
	
	layout(location = 0) in vec3 s_position;
	layout(location = 1) in vec3 s_normal;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	float get_random(vec2 p, float seed) {
		return fract(sin(dot(p, vec2(19.937f, 86.243f)) + seed) * 1346.6917f);
	}
	
	/*
	 */
	void main() {
		
		vec3 normal = normalize(s_normal);
		
		vec3 view_vector = normalize(camera.xyz - s_position);
		vec3 light_vector = normalize(light.xyz - s_position);
		
		float diffuse = clamp(dot(light_vector, normal), 0.0f, 1.0f) * 0.75f;
		float specular = pow(clamp(dot(reflect(-light_vector, normal), view_vector), 0.0f, 1.0f), 16.0f) * 0.75f;
		
		vec2 seed = gl_FragCoord.xy / 1024.0f;
		float theta = get_random(seed, 1307.1307f) * 3.14f * 2.0f;
		float cos_phi = get_random(seed, 3071.3071f) * 2.0f - 1.0f;
		float sin_phi = sqrt(max(1.0f - cos_phi * cos_phi, 0.0f));
		vec3 offset = vec3(cos(theta) * sin_phi, sin(theta) * sin_phi, cos_phi) * 0.01f;
		
		rayQueryEXT shadow_query;
		rayQueryInitializeEXT(shadow_query, tracing, gl_RayFlagsTerminateOnFirstHitEXT, 0xff, s_position, 0.001f, light.xyz + offset - s_position, 1.0f);
		rayQueryProceedEXT(shadow_query);
		
		float shadow = 0.0f;
		if(rayQueryGetIntersectionTypeEXT(shadow_query, true) != gl_RayQueryCommittedIntersectionNoneEXT) shadow = 1.0f;
		
		out_color = vec4((diffuse + specular) * (1.0f - shadow));
	}
	
#endif

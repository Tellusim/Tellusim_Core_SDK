// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 460 core

/*
 */
#if VERTEX_SHADER
	
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
	
	layout(location = 0) in vec2 s_texcoord;
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 imodelview;
		vec4 camera;
		float window_width;
		float window_height;
		float time;
	};
	
	layout(std430, binding = 1) readonly buffer VertexBuffer { vec4 vertex_buffer[]; };
	layout(std430, binding = 2) readonly buffer IndexBuffer { uint index_buffer[]; };
	
	layout(binding = 0, set = 1) uniform accelerationStructureEXT tracing;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		// ray parameters
		float x = (s_texcoord.x * 2.0f - 1.0f + projection[2].x) / projection[0].x;
		float y = (s_texcoord.y * 2.0f - 1.0f + projection[2].y) / projection[1].y;
		vec3 ray_position = (imodelview * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
		vec3 ray_direction = normalize((imodelview * vec4(x, y, -1.0f, 1.0f)).xyz - ray_position);
		
		// closest intersection
		rayQueryEXT ray_query;
		rayQueryInitializeEXT(ray_query, tracing, gl_RayFlagsOpaqueEXT, 0xff, ray_position, 0.0f, ray_direction, 1000.0f);
		while(rayQueryProceedEXT(ray_query)) {
			if(rayQueryGetIntersectionTypeEXT(ray_query, false) == gl_RayQueryCandidateIntersectionTriangleEXT) {
				rayQueryConfirmIntersectionEXT(ray_query);
			}
		}
		
		// check intersection
		[[branch]] if(rayQueryGetIntersectionTypeEXT(ray_query, true) == gl_RayQueryCommittedIntersectionNoneEXT) {
			discard;
		}
		
		// camera direction
		vec3 direction = -ray_direction;
		
		// intersection parameters
		uint instance = rayQueryGetIntersectionInstanceIdEXT(ray_query, true);
		uint index = rayQueryGetIntersectionPrimitiveIndexEXT(ray_query, true) * 3u;
		vec2 texcoord = rayQueryGetIntersectionBarycentricsEXT(ray_query, true);
		mat4x3 transform = rayQueryGetIntersectionObjectToWorldEXT(ray_query, true);
		
		// interpolate normal
		vec3 normal_0 = vertex_buffer[index_buffer[index + 0u] * 2u + 1u].xyz;
		vec3 normal_1 = vertex_buffer[index_buffer[index + 1u] * 2u + 1u].xyz;
		vec3 normal_2 = vertex_buffer[index_buffer[index + 2u] * 2u + 1u].xyz;
		vec3 normal = normal_0 * (1.0f - texcoord.x - texcoord.y) + normal_1 * texcoord.x + normal_2 * texcoord.y;
		normal = normalize(transform[0].xyz * normal.x + transform[1].xyz * normal.y + transform[2].xyz * normal.z);
		
		// light color
		float diffuse = clamp(dot(direction, normal), 0.0f, 1.0f);
		float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0f, 1.0f), 16.0f);
		
		// instance color
		vec3 color = cos(vec3(0.0f, 0.5f, 1.0f) * 3.14f + float(instance)) * 0.5f + 0.5f;
		float position = window_width * (cos(time) * 0.25f + 0.75f);
		if(gl_FragCoord.x < position) color = vec3(0.75f);
		
		// output color
		if(abs(gl_FragCoord.x - position) < 1.0f) out_color = vec4(0.0f);
		else out_color = vec4(color, 1.0f) * diffuse + specular;
	}
	
#endif

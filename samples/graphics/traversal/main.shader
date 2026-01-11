// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 460 core

/*
 */
#if RAYGEN_SHADER || RAYMISS_SHADER || CLOSEST_MODEL_SHADER || CLOSEST_PLANE_SHADER || RAYMISS_REFLECTION_SHADER || CLOSEST_MODEL_REFLECTION_SHADER || CLOSEST_PLANE_REFLECTION_SHADER || RAYMISS_SHADOW_SHADER
	
	#extension GL_EXT_ray_tracing : require
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 imodelview;
		vec4 camera;
		vec4 light;
	};
	
	layout(std430, binding = 1) readonly buffer ModelVertexBuffer { vec4 model_vertex_buffer[]; };
	layout(std430, binding = 2) readonly buffer PlaneVertexBuffer { vec4 plane_vertex_buffer[]; };
	layout(std430, binding = 3) readonly buffer ModelIndexBuffer { uint model_index_buffer[]; };
	layout(std430, binding = 4) readonly buffer PlaneIndexBuffer { uint plane_index_buffer[]; };
	
#endif

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
	
	layout(binding = 0, set = 0) uniform texture2D in_texture;
	
	layout(location = 0) in vec2 s_texcoord;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		ivec2 size = textureSize(in_texture, 0);
		
		ivec2 texcoord = ivec2(s_texcoord * size);
		
		out_color = texelFetch(in_texture, texcoord, 0);
	}
	
#elif RAYGEN_SHADER
	
	layout(binding = 0, set = 1, rgba8) uniform writeonly image2D out_surface;
	
	layout(binding = 0, set = 2) uniform accelerationStructureEXT tracing;
	
	layout(location = 0) rayPayloadEXT vec3 color_value;
	
	/*
	 */
	void main() {
		
		color_value = vec3(0.0f);
		
		ivec2 global_id = ivec2(gl_LaunchIDEXT.xy);
		
		ivec2 surface_size = imageSize(out_surface);
		
		// ray parameters
		vec3 position = (imodelview * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
		float x = ((global_id.x + 0.5f) / float(surface_size.x) * 2.0f - 1.0f + projection[2].x) / projection[0].x;
		float y = ((global_id.y + 0.5f) / float(surface_size.y) * 2.0f - 1.0f + projection[2].y) / projection[1].y;
		vec3 direction = normalize((imodelview * vec4(x, y, -1.0f, 1.0f)).xyz - position);
		
		traceRayEXT(tracing, gl_RayFlagsOpaqueEXT, 0xffu, 0u, 2u, 0u, position, 0.0f, direction, 1000.0f, 0);
		
		imageStore(out_surface, global_id, vec4(color_value, 1.0f));
	}
	
#elif RAYMISS_SHADER
	
	layout(location = 0) rayPayloadInEXT vec3 color_value;
	
	/*
	 */
	void main() {
		
		color_value = vec3(0.2f);
	}
	
#elif RAYMISS_REFLECTION_SHADER
	
	layout(location = 1) rayPayloadInEXT vec3 reflection_color;
	
	/*
	 */
	void main() {
		
		reflection_color = vec3(0.0f);
	}
	
#elif RAYMISS_SHADOW_SHADER
	
	layout(location = 2) rayPayloadInEXT float shadow_value;
	
	/*
	 */
	void main() {
		
		shadow_value = 1.0f;
	}
	
#elif CLOSEST_MODEL_SHADER || CLOSEST_PLANE_SHADER
	
	layout(binding = 0, set = 2) uniform accelerationStructureEXT tracing;
	
	layout(location = 0) rayPayloadInEXT vec3 color_value;
	
	layout(location = 1) rayPayloadEXT vec3 reflection_color;
	layout(location = 2) rayPayloadEXT float shadow_value;
	
	hitAttributeEXT vec2 hit_attribute;
	
	/*
	 */
	void main() {
		
		#if MAX_TRAVERSAL_DEPTH > 1
			shadow_value = 0.0f;
		#else
			shadow_value = 1.0f;
		#endif
		
		reflection_color = vec3(0.0f);
		
		vec3 position = gl_WorldRayOriginEXT + gl_WorldRayDirectionEXT * gl_HitTEXT;
		
		vec3 direction = normalize(camera.xyz - position);
		
		vec3 light_direction = normalize(light.xyz - position);
		
		uint index = gl_PrimitiveID * 3u;
		#if CLOSEST_MODEL_SHADER
			vec3 normal_0 = model_vertex_buffer[model_index_buffer[index + 0u] * 2u + 1u].xyz;
			vec3 normal_1 = model_vertex_buffer[model_index_buffer[index + 1u] * 2u + 1u].xyz;
			vec3 normal_2 = model_vertex_buffer[model_index_buffer[index + 2u] * 2u + 1u].xyz;
		#elif CLOSEST_PLANE_SHADER
			vec3 normal_0 = plane_vertex_buffer[plane_index_buffer[index + 0u] * 2u + 1u].xyz;
			vec3 normal_1 = plane_vertex_buffer[plane_index_buffer[index + 1u] * 2u + 1u].xyz;
			vec3 normal_2 = plane_vertex_buffer[plane_index_buffer[index + 2u] * 2u + 1u].xyz;
		#endif
		vec3 normal = normal_0 * (1.0f - hit_attribute.x - hit_attribute.y) + normal_1 * hit_attribute.x + normal_2 * hit_attribute.y;
		normal = normalize(gl_ObjectToWorldEXT[0].xyz * normal.x + gl_ObjectToWorldEXT[1].xyz * normal.y + gl_ObjectToWorldEXT[2].xyz * normal.z);
		
		float diffuse = clamp(dot(light_direction, normal), 0.0f, 1.0f);
		float specular = pow(clamp(dot(reflect(-light_direction, normal), direction), 0.0f, 1.0f), 16.0f);
		
		#if CLOSEST_MODEL_SHADER
			float seed = gl_InstanceID * 13.7351f;
			vec3 instance_color = cos(vec3(vec3(1.0f, 0.5f, 0.0f) * 3.14f + seed)) * 0.4f + 0.6f;
		#elif CLOSEST_PLANE_SHADER
			ivec2 color_index = ivec2(position.xy / 2.0f - 64.0f) & 0x01;
			vec3 instance_color = vec3(((color_index.x ^ color_index.y) == 0) ? 0.8f : 0.4f);
		#endif
		
		#if MAX_TRAVERSAL_DEPTH > 1
			traceRayEXT(tracing, gl_RayFlagsOpaqueEXT | gl_RayFlagsTerminateOnFirstHitEXT | gl_RayFlagsSkipClosestHitShaderEXT, 0xffu, 0u, 2u, 2u, position, 1e-3f, light_direction, 1000.0f, 2);
			traceRayEXT(tracing, gl_RayFlagsOpaqueEXT, 0xffu, 2u, 2u, 1u, position, 1e-3f, reflect(-direction, normal), 1000.0f, 1);
		#endif
		
		color_value = (instance_color * diffuse + specular) * shadow_value + reflection_color * 0.5f;
	}
	
#elif CLOSEST_MODEL_REFLECTION_SHADER || CLOSEST_PLANE_REFLECTION_SHADER
	
	layout(location = 1) rayPayloadInEXT vec3 reflection_color;
	
	hitAttributeEXT vec2 hit_attribute;
	
	/*
	 */
	void main() {
		
		vec3 position = gl_WorldRayOriginEXT + gl_WorldRayDirectionEXT * gl_HitTEXT;
		
		vec3 direction = normalize(camera.xyz - position);
		
		vec3 light_direction = normalize(light.xyz - position);
		
		uint index = gl_PrimitiveID * 3u;
		#if CLOSEST_MODEL_REFLECTION_SHADER
			vec3 normal_0 = model_vertex_buffer[model_index_buffer[index + 0u] * 2u + 1u].xyz;
			vec3 normal_1 = model_vertex_buffer[model_index_buffer[index + 1u] * 2u + 1u].xyz;
			vec3 normal_2 = model_vertex_buffer[model_index_buffer[index + 2u] * 2u + 1u].xyz;
		#elif CLOSEST_PLANE_REFLECTION_SHADER
			vec3 normal_0 = plane_vertex_buffer[plane_index_buffer[index + 0u] * 2u + 1u].xyz;
			vec3 normal_1 = plane_vertex_buffer[plane_index_buffer[index + 1u] * 2u + 1u].xyz;
			vec3 normal_2 = plane_vertex_buffer[plane_index_buffer[index + 2u] * 2u + 1u].xyz;
		#endif
		vec3 normal = normal_0 * (1.0f - hit_attribute.x - hit_attribute.y) + normal_1 * hit_attribute.x + normal_2 * hit_attribute.y;
		normal = normalize(gl_ObjectToWorldEXT[0].xyz * normal.x + gl_ObjectToWorldEXT[1].xyz * normal.y + gl_ObjectToWorldEXT[2].xyz * normal.z);
		
		float diffuse = clamp(dot(light_direction, normal), 0.0f, 1.0f);
		float specular = pow(clamp(dot(reflect(-light_direction, normal), direction), 0.0f, 1.0f), 16.0f);
		
		#if CLOSEST_MODEL_REFLECTION_SHADER
			float seed = gl_InstanceID * 13.7351f;
			vec3 instance_color = cos(vec3(vec3(1.0f, 0.5f, 0.0f) * 3.14f + seed)) * 0.4f + 0.6f;
		#elif CLOSEST_PLANE_REFLECTION_SHADER
			ivec2 color_index = ivec2(position.xy / 2.0f - 64.0f) & 0x01;
			vec3 instance_color = vec3(((color_index.x ^ color_index.y) == 0) ? 0.8f : 0.4f);
		#endif
		
		reflection_color = instance_color * diffuse + specular;
	}
	
#endif

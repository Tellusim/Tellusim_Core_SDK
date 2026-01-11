// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

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
		
		s_texcoord.x = texcoord.x;
		#if CLAY_VK
			s_texcoord.y = 1.0f - texcoord.y;
		#else
			s_texcoord.y = texcoord.y;
		#endif
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
	
#elif COMPUTE_VERTICES_SHADER
	
	layout(local_size_x = GROUP_SIZE) in;
	
	layout(std140, binding = 0) uniform ComputeParameters {
		uint num_joints;
		uint num_vertices;
		uint num_instances;
	};
	
	layout(std430, binding = 1) writeonly buffer VertexBuffer { vec4 vertex_buffer[]; };
	layout(std430, binding = 2) readonly buffer SrcVertexBuffer { vec4 src_vertex_buffer[]; };
	layout(std430, binding = 3) readonly buffer JointsBuffer { vec4 joints_buffer[]; };
	
	/*
	 */
	void main() {
		
		uint global_id = gl_GlobalInvocationID.x;
		uint instance = global_id / num_vertices;
		if(instance >= num_instances) return;
		
		uint joint_index = num_joints * instance;
		uint vertex_index = global_id - num_vertices * instance;
		
		vec4 vertex_weights = src_vertex_buffer[vertex_index * 5u + 3u];
		uvec4 vertex_joints = floatBitsToUint(src_vertex_buffer[vertex_index * 5u + 4u]);
		
		vec4 row_0, row_1, row_2;
		#define JOINT(OP, SWIZZLE) \
		row_0 OP joints_buffer[(joint_index + vertex_joints.SWIZZLE) * 3u + 0u] * vertex_weights.SWIZZLE; \
		row_1 OP joints_buffer[(joint_index + vertex_joints.SWIZZLE) * 3u + 1u] * vertex_weights.SWIZZLE; \
		row_2 OP joints_buffer[(joint_index + vertex_joints.SWIZZLE) * 3u + 2u] * vertex_weights.SWIZZLE;
		JOINT( =, x)
		JOINT(+=, y)
		JOINT(+=, z)
		JOINT(+=, w)
		
		vec4 vertex_position_normal = src_vertex_buffer[vertex_index * 5u + 0u];
		vec4 vertex_normal_texcoord = src_vertex_buffer[vertex_index * 5u + 1u];
		vec4 vertex_tangent = src_vertex_buffer[vertex_index * 5u + 2u];
		
		vec4 position = vec4(vertex_position_normal.xyz, 1.0f);
		vec3 normal = vec3(vertex_position_normal.w, vertex_normal_texcoord.xy);
		vec3 tangent = vertex_tangent.xyz;
		
		position = vec4(dot(row_0, position), dot(row_1, position), dot(row_2, position), 1.0f);
		normal = vec3(dot(row_0.xyz, normal), dot(row_1.xyz, normal), dot(row_2.xyz, normal));
		tangent = vec3(dot(row_0.xyz, tangent), dot(row_1.xyz, tangent), dot(row_2.xyz, tangent));
		
		vertex_buffer[global_id * 3u + 0u] = vec4(position.xyz, normal.x);
		vertex_buffer[global_id * 3u + 1u] = vec4(normal.yz, vertex_normal_texcoord.zw);
		vertex_buffer[global_id * 3u + 2u] = vec4(tangent.xyz, vertex_tangent.w);
	}
	
#elif COMPUTE_TRACE_SHADER
	
	#define GROUP_SIZE	8u
	
	#extension GL_EXT_ray_query : require
	#extension GL_EXT_ray_tracing : require
	
	layout(local_size_x = GROUP_SIZE, local_size_y = GROUP_SIZE) in;
	
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 imodelview;
		vec4 camera;
		vec4 light;
		uint num_vertices;
		uint body_triangles;
		uint cast_shadow;
		float time;
	};
	
	layout(std430, binding = 1) readonly buffer VertexBuffer { vec4 vertex_buffer[]; };
	layout(std430, binding = 2) readonly buffer IndexBuffer { uint index_buffer[]; };
	
	layout(binding = 0, set = 1) uniform texture2D in_texture_0;
	layout(binding = 1, set = 1) uniform texture2D in_texture_1;
	layout(binding = 0, set = 2) uniform sampler in_sampler;
	
	layout(binding = 2, set = 1, rgba8) uniform writeonly image2D out_surface;
	
	layout(binding = 0, set = 3) uniform accelerationStructureEXT tracing;
	
	/*
	 */
	vec3 mat4x3_mul3(mat4x3 m, vec3 v) {
		return m[0].xyz * v.x + m[1].xyz * v.y + m[2].xyz * v.z;
	}
	
	/*
	 */
	void main() {
		
		ivec2 global_id = ivec2(gl_GlobalInvocationID.xy);
		
		ivec2 surface_size = imageSize(out_surface);
		
		// noise texture
		vec4 noise = textureLod(sampler2D(in_texture_0, in_sampler), vec2(global_id) / 256.0f, 0.0f);
		
		// ray parameters
		vec3 position = (imodelview * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
		float x = ((global_id.x + 0.5f) / float(surface_size.x) * 2.0f - 1.0f + projection[2].x) / projection[0].x;
		float y = ((global_id.y + 0.5f) / float(surface_size.y) * 2.0f - 1.0f + projection[2].y) / projection[1].y;
		vec3 direction = normalize((imodelview * vec4(x, y, -1.0f, 1.0f)).xyz - position);
		
		// depth of field
		#if DEPTH_OF_FIELD
			float k = sin(time * 0.5f) * 0.2f;
			vec3 position_offset = (imodelview * vec4(noise.zw * k * 2.0f - k, 0.0f, 0.0f)).xyz;
			direction = normalize((position + direction * 4.5f) - position - position_offset);
			position += position_offset;
		#endif
		
		// closest intersection
		rayQueryEXT ray_query;
		rayQueryInitializeEXT(ray_query, tracing, gl_RayFlagsOpaqueEXT, 0xff, position, 0.0f, direction, 1000.0f);
		while(rayQueryProceedEXT(ray_query)) {
			if(rayQueryGetIntersectionTypeEXT(ray_query, false) == gl_RayQueryCandidateIntersectionTriangleEXT) {
				rayQueryConfirmIntersectionEXT(ray_query);
			}
		}
		
		// background color
		vec3 color = vec3(0.1f);
		
		// plane position
		vec3 plane_position = position - direction * (position.z / direction.z);
		
		// light position
		float theta = noise.z * 3.14f * 2.0f;
		float cos_phi = noise.w;
		float sin_phi = sqrt(max(1.0f - cos_phi * cos_phi, 0.0f));
		vec3 light_position = light.xyz + vec3(cos(theta) * sin_phi, sin(theta) * sin_phi, cos_phi) * 0.4f;
		
		// intersection data
		[[branch]] if(rayQueryGetIntersectionTypeEXT(ray_query, true) != gl_RayQueryCommittedIntersectionNoneEXT) {
			
			position += direction * rayQueryGetIntersectionTEXT(ray_query, true);
			
			direction = -direction;
			
			vec3 light_direction = normalize(light_position - position);
			
			// shadow intersection
			float shadow_value = 1.0f;
			[[branch]] if(cast_shadow != 0u) {
				rayQueryEXT shadow_ray_query;
				rayQueryInitializeEXT(shadow_ray_query, tracing, gl_RayFlagsTerminateOnFirstHitEXT, 0xff, position, 0.001f, light_direction, 1000.0f);
				while(rayQueryProceedEXT(shadow_ray_query)) {
					if(rayQueryGetIntersectionTypeEXT(shadow_ray_query, false) == gl_RayQueryCandidateIntersectionTriangleEXT) {
						rayQueryConfirmIntersectionEXT(shadow_ray_query);
					}
				}
				if(rayQueryGetIntersectionTypeEXT(shadow_ray_query, true) != gl_RayQueryCommittedIntersectionNoneEXT) shadow_value = 0.05f;
			}
			
			// ray parameters
			mat4x3 ray_transform = rayQueryGetIntersectionObjectToWorldEXT(ray_query, true);
			vec2 ray_texcoord = rayQueryGetIntersectionBarycentricsEXT(ray_query, true);
			uint ray_primitive = rayQueryGetIntersectionPrimitiveIndexEXT(ray_query, true);
			uint ray_instance = rayQueryGetIntersectionInstanceIdEXT(ray_query, true);
			
			// fetch indices
			uint index = ray_primitive * 3u;
			uint index_0 = index_buffer[index + 0u];
			uint index_1 = index_buffer[index + 1u];
			uint index_2 = index_buffer[index + 2u];
			
			// fetch vertex
			uvec3 indices = num_vertices * ray_instance + uvec3(index_0, index_1, index_2);
			vec4 position_normal_0 = vertex_buffer[indices.x * 3u + 0u];
			vec4 position_normal_1 = vertex_buffer[indices.y * 3u + 0u];
			vec4 position_normal_2 = vertex_buffer[indices.z * 3u + 0u];
			vec4 normal_texcoord_0 = vertex_buffer[indices.x * 3u + 1u];
			vec4 normal_texcoord_1 = vertex_buffer[indices.y * 3u + 1u];
			vec4 normal_texcoord_2 = vertex_buffer[indices.z * 3u + 1u];
			vec4 tangent_0 = vertex_buffer[indices.x * 3u + 1u];
			vec4 tangent_1 = vertex_buffer[indices.y * 3u + 1u];
			vec4 tangent_2 = vertex_buffer[indices.z * 3u + 1u];
			
			// intersection normal
			vec3 normal_0 = vec3(position_normal_0.w, normal_texcoord_0.xy);
			vec3 normal_1 = vec3(position_normal_1.w, normal_texcoord_1.xy);
			vec3 normal_2 = vec3(position_normal_2.w, normal_texcoord_2.xy);
			vec3 normal = normal_0 * (1.0f - ray_texcoord.x - ray_texcoord.y) + normal_1 * ray_texcoord.x + normal_2 * ray_texcoord.y;
			normal = normalize(mat4x3_mul3(ray_transform, normal));
			
			// intersection basis
			vec4 tangent = tangent_0 * (1.0f - ray_texcoord.x - ray_texcoord.y) + tangent_1 * ray_texcoord.x + tangent_2 * ray_texcoord.y;
			vec3 binormal = normalize(cross(normal, mat4x3_mul3(ray_transform, tangent.xyz))) * tangent_0.w;
			tangent.xyz = normalize(cross(binormal, normal)) * tangent_0.w;
			
			// intersection texcoord
			vec2 texcoord = normal_texcoord_0.zw * (1.0f - ray_texcoord.x - ray_texcoord.y) + normal_texcoord_1.zw * ray_texcoord.x + normal_texcoord_2.zw * ray_texcoord.y;
			texcoord = vec2(texcoord.x / 3.0f, 0.5f - texcoord.y * 0.5f);
			if(ray_primitive < body_triangles) texcoord.y += 0.5f;
			
			// fetch textures
			vec3 texture_color = textureLod(sampler2D(in_texture_1, in_sampler), texcoord, 0.0f).xyz;
			texture_color *= texture_color;
			
			vec3 texture_normal = textureLod(sampler2D(in_texture_1, in_sampler), texcoord + vec2(1.0f / 3.0f, 0.0f), 0.0f).xyz * 2.0f - 254.0f / 255.0f;
			normal = tangent.xyz * texture_normal.x + binormal * texture_normal.y + normal * texture_normal.z;
			
			vec3 texture_emission = textureLod(sampler2D(in_texture_1, in_sampler), texcoord + vec2(2.0f / 3.0f, 0.0f), 0.0f).xyz;
			texture_emission *= texture_emission;
			
			float diffuse = clamp(dot(light_direction, normal), 0.0f, 1.0f);
			float specular = pow(clamp(dot(reflect(-light_direction, normal), direction), 0.0f, 1.0f), 8.0f);
			
			color = (texture_color * diffuse + specular) * shadow_value + texture_emission * 2.0f;
		}
		// plane intersection
		else if(direction.z < 0.0f && plane_position.x > -2.0f && plane_position.y > -2.0f && plane_position.x < 24.0f && plane_position.y < 24.0f) {
			
			position = plane_position;
			
			direction = -direction;
			
			vec3 light_direction = normalize(light_position - position);
			
			// shadow intersection
			float shadow_value = 1.0f;
			[[branch]] if(cast_shadow != 0u) {
				rayQueryEXT shadow_ray_query;
				rayQueryInitializeEXT(shadow_ray_query, tracing, gl_RayFlagsTerminateOnFirstHitEXT, 0xff, position, 0.0f, light_direction, 1000.0f);
				while(rayQueryProceedEXT(shadow_ray_query)) {
					if(rayQueryGetIntersectionTypeEXT(shadow_ray_query, false) == gl_RayQueryCandidateIntersectionTriangleEXT) {
						rayQueryConfirmIntersectionEXT(shadow_ray_query);
					}
				}
				if(rayQueryGetIntersectionTypeEXT(shadow_ray_query, true) != gl_RayQueryCommittedIntersectionNoneEXT) shadow_value = 0.05f;
			}
			
			vec3 normal = vec3(0.0f, 0.0f, 1.0f);
			
			float diffuse = clamp(dot(light_direction, normal), 0.0f, 1.0f);
			float specular = pow(clamp(dot(reflect(-light_direction, normal), direction), 0.0f, 1.0f), 16.0f);
			
			ivec2 index = ivec2(position.xy / 1.0f - 64.0f) & 0x01;
			vec3 plane_color = vec3(((index.x ^ index.y) == 0) ? 0.8f : 0.4f);
			
			color = (plane_color * diffuse + specular) * shadow_value;
		}
		
		imageStore(out_surface, global_id, vec4(pow(color, vec3(1.0f / 2.2f)), 1.0f));
	}
	
#endif

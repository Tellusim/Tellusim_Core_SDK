// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#if !COMMAND_SHADER
	#version 420 core
#endif

/*
 */
#if ((VERTEX_PIPELINE || PRIMITIVE_PIPELINE || INDEXING_PIPELINE || INDIRECT_PIPELINE) && VERTEX_SHADER) || MESH_SHADER || COMPUTE_DRAW_SHADER
	vec3 get_color(uint index) {
		float seed = mod(index * 93.7351f, 1024.0f);
		return cos(vec3(0.0f, 0.5f, 1.0f) * 3.14f + seed) * 0.5f + 0.5f;
	}
#endif

/*
 */
#if (VERTEX_PIPELINE || PRIMITIVE_PIPELINE || INDEXING_PIPELINE || INDIRECT_PIPELINE || MESH_PIPELINE) && FRAGMENT_SHADER
	
	layout(location = 0) in VertexOut {
		vec3 direction;
		vec3 normal;
		vec3 color;
	} IN;
	
	layout(location = 0) out vec4 out_color;
	
	/*
	 */
	void main() {
		
		vec3 direction = normalize(IN.direction);
		vec3 normal = normalize(IN.normal);
		vec3 color = IN.color;
		
		float diffuse = clamp(dot(direction, normal), 0.0f, 1.0f);
		float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0f, 1.0f), 16.0f);
		
		out_color = vec4(color, 1.0f) * diffuse + specular;
	}
	
#endif

/*
 */
#if VERTEX_PIPELINE || PRIMITIVE_PIPELINE || INDEXING_PIPELINE || INDIRECT_PIPELINE
	
	#if VERTEX_SHADER
		
		layout(row_major, binding = 0) uniform CommonParameters {
			mat4 projection;
			mat4 modelview;
			vec4 camera;
		};
		
		#if PRIMITIVE_PIPELINE || INDEXING_PIPELINE
			
			layout(std140, binding = 1) uniform MeshletParameter {
				uint num_meshlets;
			};
			
			layout(std430, binding = 2) readonly buffer TransformsBuffer { vec4 transforms[]; };
			layout(std430, binding = 3) readonly buffer VerticesBuffer { vec4 vertices_buffer[]; };
			layout(std430, binding = 4) readonly buffer MeshletsBuffer { uint meshlets_buffer[]; };
			
		#else
			
			layout(location = 0) in vec4 in_position;
			layout(location = 1) in vec3 in_normal;
			#if INDIRECT_PIPELINE
				layout(location = 2) in uint in_instance;
			#endif
			
			layout(std140, binding = 1) uniform TransformParameters { vec4 transforms[NUM_INSTANCES * 3u]; };
			
		#endif
		
		layout(location = 0) out VertexOut {
			vec3 direction;
			vec3 normal;
			vec3 color;
		} OUT;
		
		/*
		 */
		void main() {
			
			#if PRIMITIVE_PIPELINE
				uint primitive = gl_VertexIndex / 3u;
				uint group = primitive / NUM_PRIMITIVES;
				uint instance = group / num_meshlets;
				uint meshlet = group % num_meshlets;
				uint meshlet_index = meshlet * 12u;
				uint num_primitives = meshlets_buffer[meshlet_index + 0u];
				uint base_index = meshlets_buffer[meshlet_index + 2u];
				uint base_vertex = meshlets_buffer[meshlet_index + 3u];
				uint primitive_index = min(uint(gl_VertexIndex) - group * NUM_PRIMITIVES * 3u, num_primitives * 3u - 1u);
				uint primitive_vertex = (meshlets_buffer[base_index + (primitive_index >> 2u)] >> ((primitive_index & 0x03u) * 8u)) & 0xffu;
				uint address = (base_vertex + primitive_vertex) * 2u;
				vec4 in_position = vec4(vertices_buffer[address + 0u].xyz, 1.0f);
				vec3 in_normal = vertices_buffer[address + 1u].xyz;
			#elif INDEXING_PIPELINE
				uint group = gl_VertexIndex >> 8u;
				uint primitive_vertex = gl_VertexIndex & 0xffu;
				uint instance = group / num_meshlets;
				uint meshlet = group % num_meshlets;
				uint meshlet_index = meshlet * 12u;
				uint base_vertex = meshlets_buffer[meshlet_index + 3u];
				uint address = (base_vertex + primitive_vertex) * 2u;
				vec4 in_position = vec4(vertices_buffer[address + 0u].xyz, 1.0f);
				vec3 in_normal = vertices_buffer[address + 1u].xyz;
			#elif INDIRECT_PIPELINE
				uint meshlet = in_instance & 0xffffu;
				uint instance = in_instance >> 16u;
			#else
				uint meshlet = gl_InstanceIndex;
				uint instance = gl_InstanceIndex;
			#endif
			
			uint index = instance * 3u;
			vec4 row_0 = transforms[index + 0u];
			vec4 row_1 = transforms[index + 1u];
			vec4 row_2 = transforms[index + 2u];
			
			vec4 position = vec4(dot(row_0, in_position), dot(row_1, in_position), dot(row_2, in_position), 1.0f);
			gl_Position = projection * (modelview * position);
			
			OUT.direction = camera.xyz - position.xyz;
			OUT.normal = vec3(dot(row_0.xyz, in_normal), dot(row_1.xyz, in_normal), dot(row_2.xyz, in_normal));
			
			OUT.color = get_color(meshlet);
		}
		
	#endif
	
#elif MESH_PIPELINE
	
	#if TASK_SHADER
		
		layout(local_size_x = 1) in;
		
		layout(std140, binding = 1) uniform MeshletParameter {
			uint num_meshlets;
			uint base_meshlet;
		};
		
		struct TaskOut {
			uint instance_id;
		};
		
		taskPayloadSharedEXT TaskOut OUT;
		
		/*
		 */
		void main() {
			
			uint group_id = gl_WorkGroupID.x;
			
			OUT.instance_id = group_id;
			
			EmitMeshTasksEXT(num_meshlets, 1, 1);
		}
		
	#elif MESH_SHADER
		
		layout(local_size_x = GROUP_SIZE) in;
		
		layout(triangles, max_vertices = NUM_VERTICES, max_primitives = NUM_PRIMITIVES) out;
		
		layout(row_major, binding = 0) uniform CommonParameters {
			mat4 projection;
			mat4 modelview;
			vec4 camera;
		};
		
		layout(std140, binding = 1) uniform MeshletParameter {
			uint num_meshlets;
			uint base_meshlet;
		};
		
		struct TaskOut {
			uint instance_id;
		};
		
		taskPayloadSharedEXT TaskOut IN;
		
		layout(std430, binding = 2) readonly buffer TransformsBuffer { vec4 transforms[]; };
		layout(std430, binding = 3) readonly buffer VerticesBuffer { vec4 vertices_buffer[]; };
		layout(std430, binding = 4) readonly buffer MeshletsBuffer { uint meshlets_buffer[]; };
		
		layout(location = 0) out VertexOut {
			vec3 direction;
			vec3 normal;
			vec3 color;
		} OUT[NUM_VERTICES];
		
		shared uint num_primitives;
		shared uint num_vertices;
		shared uint base_index;
		shared uint base_vertex;
		shared vec4 row_0;
		shared vec4 row_1;
		shared vec4 row_2;
		shared vec3 color;
		
		/*
		 */
		void main() {
			
			uint local_id = gl_LocalInvocationIndex;
			uint group_id = gl_WorkGroupID.x;
			
			// meshlet parameters
			[[branch]] if(local_id == 0u) {
				
				uint transform_index = IN.instance_id * 3u;
				row_0 = transforms[transform_index + 0u];
				row_1 = transforms[transform_index + 1u];
				row_2 = transforms[transform_index + 2u];
				
				uint meshlet_index = (base_meshlet + group_id) * 12u;
				num_primitives = meshlets_buffer[meshlet_index + 0u];
				num_vertices = meshlets_buffer[meshlet_index + 1u];
				base_index = meshlets_buffer[meshlet_index + 2u];
				base_vertex = meshlets_buffer[meshlet_index + 3u];
				
				// meshlet culling
				vec4 position = vec4(uintBitsToFloat(uvec3(meshlets_buffer[meshlet_index + 4u], meshlets_buffer[meshlet_index + 5u], meshlets_buffer[meshlet_index + 6u])), 1.0f);
				vec3 normal = uintBitsToFloat(uvec3(meshlets_buffer[meshlet_index + 8u], meshlets_buffer[meshlet_index + 9u], meshlets_buffer[meshlet_index + 10u]));
				vec3 direction = normalize(vec3(dot(row_0, position), dot(row_1, position), dot(row_2, position)) - camera.xyz);
				normal = normalize(vec3(dot(row_0.xyz, normal), dot(row_1.xyz, normal), dot(row_2.xyz, normal)));
				if(dot(direction, normal) < uintBitsToFloat(meshlets_buffer[meshlet_index + 11u])) {
					num_primitives = 0u;
					num_vertices = 0u;
				}
				
				color = get_color(base_meshlet + group_id);
			}
			memoryBarrierShared(); barrier();
			
			// number of primitives
			SetMeshOutputsEXT(num_vertices, num_primitives);
			
			// vertices
			[[unroll]] for(uint i = 0; i < NUM_VERTICES; i += GROUP_SIZE) {
				
				uint index = local_id + i;
				
				[[branch]] if(index < num_vertices) {
					
					uint address = (base_vertex + index) * 2u;
					
					vec4 position = vec4(vertices_buffer[address + 0u].xyz, 1.0f);
					position = vec4(dot(row_0, position), dot(row_1, position), dot(row_2, position), 1.0f);
					gl_MeshVerticesEXT[index].gl_Position = projection * (modelview * position);
					
					vec3 normal = vertices_buffer[address + 1u].xyz;
					OUT[index].direction = camera.xyz - position.xyz;
					OUT[index].normal = vec3(dot(row_0.xyz, normal), dot(row_1.xyz, normal), dot(row_2.xyz, normal));
					OUT[index].color = color;
				}
			}
			
			// indices
			[[loop]] for(uint i = local_id; (i << 2u) < num_primitives; i += GROUP_SIZE) {
				
				uint index = i * 4u;
				
				uint address = base_index + i * 3u;
				uint indices_0 = meshlets_buffer[address + 0u];
				uint indices_1 = meshlets_buffer[address + 1u];
				uint indices_2 = meshlets_buffer[address + 2u];
				
				gl_PrimitiveTriangleIndicesEXT[index + 0u] = uvec3(indices_0 >>  0u, indices_0 >>  8u, indices_0 >> 16u) & 0xffu;
				gl_PrimitiveTriangleIndicesEXT[index + 1u] = uvec3(indices_0 >> 24u, indices_1 >>  0u, indices_1 >>  8u) & 0xffu;
				gl_PrimitiveTriangleIndicesEXT[index + 2u] = uvec3(indices_1 >> 16u, indices_1 >> 24u, indices_2 >>  0u) & 0xffu;
				gl_PrimitiveTriangleIndicesEXT[index + 3u] = uvec3(indices_2 >>  8u, indices_2 >> 16u, indices_2 >> 24u) & 0xffu;
			}
		}
		
	#endif
	
#elif COMPUTE_PIPELINE
	
	#if VERTEX_SHADER
		
		layout(location = 0) out vec2 s_texcoord;
		
		/*
		 */
		void main() {
			
			vec2 texcoord = vec2(0.0f);
			if(gl_VertexIndex == 0) texcoord.x = 2.0f;
			if(gl_VertexIndex == 2) texcoord.y = 2.0f;
			
			gl_Position = vec4(texcoord * 2.0f - 1.0f, 0.0f, 1.0f);
			
			s_texcoord = texcoord;
		}
		
	#elif FRAGMENT_SHADER
		
		layout(binding = 0, set = 0) uniform utexture2D in_texture;
		
		layout(location = 0) in vec2 s_texcoord;
		
		layout(location = 0) out vec4 out_color;
		
		/*
		 */
		void main() {
			
			ivec2 size = textureSize(in_texture, 0);
			
			ivec2 texcoord = ivec2(s_texcoord * size);
			
			uint value = texelFetch(in_texture, texcoord, 0).x;
			
			out_color = unpackUnorm4x8(value);
		}
		
	#elif COMPUTE_DRAW_SHADER
		
		layout(local_size_x = GROUP_SIZE) in;
		
		layout(row_major, binding = 0) uniform CommonParameters {
			mat4 projection;
			mat4 modelview;
			vec4 camera;
		};
		
		layout(std140, binding = 1) uniform ComputeParameters {
			uint num_meshlets;
			uint group_offset;
			vec2 surface_size;
			float surface_stride;
		};
		
		layout(std430, binding = 2) readonly buffer TransformsBuffer { vec4 transforms[]; };
		layout(std430, binding = 3) readonly buffer VerticesBuffer { vec4 vertices_buffer[]; };
		layout(std430, binding = 4) readonly buffer MeshletsBuffer { uint meshlets_buffer[]; };
		
		#if CLAY_MTL
			#pragma surface(0, 5)
			#pragma surface(1, 6)
			layout(std430, binding = 5) buffer DepthBuffer { uint depth_surface[]; };
			layout(std430, binding = 6) buffer ColorBuffer { uint color_surface[]; };
		#else
			layout(binding = 0, set = 1, r32ui) uniform uimage2D depth_surface;
			layout(binding = 1, set = 1, r32ui) uniform uimage2D color_surface;
		#endif
		
		shared uint num_primitives;
		shared uint num_vertices;
		shared uint base_index;
		shared uint base_vertex;
		
		shared vec4 row_0;
		shared vec4 row_1;
		shared vec4 row_2;
		
		shared vec3 positions[NUM_VERTICES];
		shared uint indices[NUM_PRIMITIVES * 3u];
		
		shared vec3 color;
		#if COLOR_SHADING
			shared vec3 vertices[NUM_VERTICES];
			shared vec3 normals[NUM_VERTICES];
		#elif COLOR_SOLID
			shared uint color_index;
		#endif
		
		/*
		 */
		void raster(uint i0, uint i1, uint i2) {
			
			// clip triangle
			vec3 p0 = positions[i0];
			vec3 p1 = positions[i1];
			vec3 p2 = positions[i2];
			[[branch]] if(p0.z < 0.0f || p1.z < 0.0f || p2.z < 0.0f) return;
			
			// backface culling
			vec3 p10 = p1 - p0;
			vec3 p20 = p2 - p0;
			float det = p20.x * p10.y - p20.y * p10.x;
			#if CLAY_VK
				[[branch]] if(det <= 0.0f) return;
			#else
				[[branch]] if(det >= 0.0f) return;
			#endif
			
			// triangle rect
			float x0 = min(min(p0.x, p1.x), p2.x);
			float y0 = min(min(p0.y, p1.y), p2.y);
			float x1 = ceil(max(max(p0.x, p1.x), p2.x));
			float y1 = ceil(max(max(p0.y, p1.y), p2.y));
			[[branch]] if(x1 - floor(x0) < 2.0f || y1 - floor(y0) < 2.0f) return;
			x0 = floor(x0 + 0.5f);
			y0 = floor(y0 + 0.5f);
			
			// viewport cull
			[[branch]] if(x1 < 0.0f || y1 < 0.0f || x0 >= surface_size.x || y0 >= surface_size.y) return;
			x0 = max(x0, 0.0f); x1 = min(x1, surface_size.x);
			y0 = max(y0, 0.0f); y1 = min(y1, surface_size.y);
			
			// triangle area
			float area = (x1 - x0) * (y1 - y0);
			[[branch]] if(area == 0.0f) return;
			
			// triangle parameters
			float idet = 1.0f / det;
			vec2 dx = vec2(-p20.y, p10.y) * idet;
			vec2 dy = vec2(p20.x, -p10.x) * idet;
			vec2 texcoord_x = dx * (x0 - p0.x);
			vec2 texcoord_y = dy * (y0 - p0.y);
			
			#if COLOR_SHADING
				vec3 v0 = vertices[i0];
				vec3 v10 = vertices[i1] - v0;
				vec3 v20 = vertices[i2] - v0;
			#endif
			
			#if COLOR_SHADING
				vec3 n0 = normals[i0];
				vec3 n10 = normals[i1] - n0;
				vec3 n20 = normals[i2] - n0;
			#endif
			
			for(float y = y0; y < y1; y += 1.0f) {
				vec2 texcoord = texcoord_x + texcoord_y;
				for(float x = x0; x < x1; x += 1.0f) {
					[[branch]] if(texcoord.x > -1e-5f && texcoord.y > -1e-5f && texcoord.x + texcoord.y < 1.0f + 1e-5f) {
						
						uint z = floatBitsToUint(p10.z * texcoord.x + p20.z * texcoord.y + p0.z);
						
						#if CLAY_MTL
							uint index = uint(surface_stride * y + x);
							uint old_z = atomicMax(depth_surface[index], z);
							[[branch]] if(old_z < z) {
						#elif CLAY_GLES
							uint old_z = imageLoad(depth_surface, ivec2(vec2(x, y))).x;
							[[branch]] if(old_z < z) {
								imageStore(depth_surface, ivec2(vec2(x, y)), uvec4(z));
						#elif CLAY_WG
							imageStore(depth_surface, ivec2(vec2(x, y)), uvec4(z));
							{
						#else
							uint old_z = imageAtomicMax(depth_surface, ivec2(vec2(x, y)), z);
							[[branch]] if(old_z < z) {
						#endif
							#if COLOR_SHADING
								vec3 direction = normalize(camera.xyz - (v10 * texcoord.x + v20 * texcoord.y + v0));
								vec3 normal = normalize(n10 * texcoord.x + n20 * texcoord.y + n0);
								float diffuse = clamp(dot(direction, normal), 0.0f, 1.0f);
								float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0f, 1.0f), 16.0f);
								uint c = packUnorm4x8(vec4(color * diffuse + specular, 1.0f));
							#elif COLOR_SOLID
								uint c = color_index;
							#endif
							#if CLAY_MTL
								atomicStore(color_surface[index], c);
							#elif CLAY_GLES || CLAY_WG
								imageStore(color_surface, ivec2(vec2(x, y)), uvec4(c));
							#else
								imageAtomicExchange(color_surface, ivec2(vec2(x, y)), c);
							#endif
						}
					}
					
					texcoord += dx;
				}
				
				texcoord_y += dy;
			}
		}
		
		/*
		 */
		void main() {
			
			uint group_id = gl_WorkGroupID.x + group_offset;
			uint local_id = gl_LocalInvocationIndex;
			
			// meshlet parameters
			[[branch]] if(local_id == 0u) {
				
				uint transform_index = (group_id / num_meshlets) * 3u;
				row_0 = transforms[transform_index + 0u];
				row_1 = transforms[transform_index + 1u];
				row_2 = transforms[transform_index + 2u];
				
				uint meshlet = group_id % num_meshlets;
				uint meshlet_index = meshlet * 12u;
				num_primitives = meshlets_buffer[meshlet_index + 0u];
				num_vertices = meshlets_buffer[meshlet_index + 1u];
				base_index = meshlets_buffer[meshlet_index + 2u];
				base_vertex = meshlets_buffer[meshlet_index + 3u];
				
				// meshlet culling
				vec4 position = vec4(uintBitsToFloat(uvec3(meshlets_buffer[meshlet_index + 4u], meshlets_buffer[meshlet_index + 5u], meshlets_buffer[meshlet_index + 6u])), 1.0f);
				vec3 normal = uintBitsToFloat(uvec3(meshlets_buffer[meshlet_index + 8u], meshlets_buffer[meshlet_index + 9u], meshlets_buffer[meshlet_index + 10u]));
				vec3 direction = normalize(vec3(dot(row_0, position), dot(row_1, position), dot(row_2, position)) - camera.xyz);
				normal = normalize(vec3(dot(row_0.xyz, normal), dot(row_1.xyz, normal), dot(row_2.xyz, normal)));
				if(dot(direction, normal) < uintBitsToFloat(meshlets_buffer[meshlet_index + 11u])) {
					num_primitives = 0u;
					num_vertices = 0u;
				}
				
				color = get_color(meshlet);
				#if COLOR_SOLID
					color_index = packUnorm4x8(vec4(color, 1.0f));
				#endif
			}
			memoryBarrierShared(); barrier();
			
			// load vertices
			[[loop]] for(uint i = 0; i < NUM_VERTICES; i += GROUP_SIZE) {
				
				uint index = local_id + i;
				
				[[branch]] if(index < num_vertices) {
					
					uint address = (base_vertex + index) * 2u;
					
					vec4 position = vec4(vertices_buffer[address].xyz, 1.0f);
					position = vec4(dot(row_0, position), dot(row_1, position), dot(row_2, position), 1.0f);
					
					#if COLOR_SHADING
						vertices[index] = position.xyz;
					#endif
					
					#if COLOR_SHADING
						vec3 normal = vertices_buffer[address + 1u].xyz;
						normal = vec3(dot(row_0.xyz, normal), dot(row_1.xyz, normal), dot(row_2.xyz, normal));
						normals[index] = normal;
					#endif
					
					position = projection * (modelview * position);
					
					positions[index] = vec3((position.xy / position.w * 0.5f + 0.5f) * surface_size - 0.5f, position.z / position.w);
				}
			}
			
			// load indices
			[[loop]] for(uint i = local_id; (i << 2u) < num_primitives; i += GROUP_SIZE) {
				
				uint index = i * 12u;
				
				uint address = base_index + i * 3u;
				uint indices_0 = meshlets_buffer[address + 0u];
				uint indices_1 = meshlets_buffer[address + 1u];
				uint indices_2 = meshlets_buffer[address + 2u];
				
				indices[index +  0u] = (indices_0 >>  0u) & 0xffu;
				indices[index +  1u] = (indices_0 >>  8u) & 0xffu;
				indices[index +  2u] = (indices_0 >> 16u) & 0xffu;
				
				indices[index +  3u] = (indices_0 >> 24u) & 0xffu;
				indices[index +  4u] = (indices_1 >>  0u) & 0xffu;
				indices[index +  5u] = (indices_1 >>  8u) & 0xffu;
				
				indices[index +  6u] = (indices_1 >> 16u) & 0xffu;
				indices[index +  7u] = (indices_1 >> 24u) & 0xffu;
				indices[index +  8u] = (indices_2 >>  0u) & 0xffu;
				
				indices[index +  9u] = (indices_2 >>  8u) & 0xffu;
				indices[index + 10u] = (indices_2 >> 16u) & 0xffu;
				indices[index + 11u] = (indices_2 >> 24u) & 0xffu;
			}
			memoryBarrierShared(); barrier();
			
			// rasterize triangles
			if(local_id < num_primitives) {
				
				uint index = local_id * 3u;
				
				uint index_0 = indices[index + 0u];
				uint index_1 = indices[index + 1u];
				uint index_2 = indices[index + 2u];
				
				raster(index_0, index_1, index_2);
			}
		}
		
	#elif COMPUTE_CLEAR_SHADER
		
		layout(local_size_x = 8, local_size_y = 8) in;
		
		layout(binding = 0) uniform ClearParameters {
			uint clear_value;
		};
		
		layout(binding = 0, set = 1, r32ui) uniform uimage2D out_surface;
		
		/*
		 */
		void main() {
			
			ivec2 size = imageSize(out_surface);
			
			ivec2 global_id = ivec2(gl_GlobalInvocationID.xy);
			
			[[branch]] if(global_id.x < size.x && global_id.y < size.y) {
				imageStore(out_surface, global_id, uvec4(clear_value));
			}
		}
		
	#endif
	
#elif INDIRECT_SHADER
	
	layout(local_size_x = 64) in;
	
	layout(std140, binding = 0) uniform IndirectParameter {
		uint num_instances;
		uint num_meshlets;
		uint num_indices;
	};
	
	layout(std430, binding = 1) readonly buffer MeshletsBuffer { uint meshlets_buffer[]; };
	layout(std430, binding = 2) writeonly buffer IndirectBuffer { uint indirects_buffer[]; };
	layout(std430, binding = 3) writeonly buffer IndicesBuffer { uint indices_buffer[]; };
	
	/*
	 */
	void main() {
		
		uint global_id = gl_GlobalInvocationID.x;
		
		// meshlet parameters
		[[branch]] if(global_id < num_meshlets * num_instances) {
			
			uint meshlet_index = (global_id % num_meshlets) * 12u;
			uint num_primitives = meshlets_buffer[meshlet_index + 0u];
			uint base_index = meshlets_buffer[meshlet_index + 2u];
			uint base_vertex = meshlets_buffer[meshlet_index + 3u];
			
			uint indirect_index = global_id * 5u;
			indirects_buffer[indirect_index + 0u] = num_primitives * 3u;
			indirects_buffer[indirect_index + 1u] = 1;
			indirects_buffer[indirect_index + 2u] = base_index * 4u - num_meshlets * 16u;
			indirects_buffer[indirect_index + 3u] = base_vertex;
			indirects_buffer[indirect_index + 4u] = global_id;
		}
		
		// indices parameters
		[[branch]] if(global_id * 4u < num_indices) {
			
			uint index = num_meshlets * 4u + global_id;
			uint indices = meshlets_buffer[index];
			
			uint index_0 = (indices >>  0u) & 0xffu;
			uint index_1 = (indices >>  8u) & 0xffu;
			uint index_2 = (indices >> 16u) & 0xffu;
			uint index_3 = (indices >> 24u) & 0xffu;
			
			index = global_id * 2u;
			indices_buffer[index + 0u] = (index_1 << 16u) | index_0;
			indices_buffer[index + 1u] = (index_3 << 16u) | index_2;
		}
	}
	
#elif COMMAND_SHADER
	
	##include <metal_stdlib>
	
	using namespace metal;
	
	#pragma group_size(64)
	
	struct alignas(256) IndirectParameters {
		uint num_instances;
		uint num_meshlets;
		uint num_indices;
	};
	
	struct Meshlet {
		uint num_primitives;
		uint num_vertices;
		uint base_index;
		uint base_vertex;
		float4 bound_sphere;
		float4 normal_angle;
	};
	
	struct CommandBuffer {
		command_buffer buffer [[id(0)]];
	};
	
	/*
	 */
	kernel void compute_main(
		constant IndirectParameters &parameters [[buffer(0)]],
		constant Meshlet *meshlets_buffer [[buffer(1)]],
		device ushort *indices_buffer [[buffer(2)]],
		device CommandBuffer *command_buffer [[buffer(3)]],
		uint global_id [[thread_position_in_grid]]) {
		
		if(global_id < parameters.num_meshlets * parameters.num_instances) {
			
			uint meshlet_index = global_id % parameters.num_meshlets;
			Meshlet meshlet = meshlets_buffer[meshlet_index];
			
			render_command command(command_buffer->buffer, global_id);
			command.draw_indexed_primitives(primitive_type::triangle,
				meshlet.num_primitives * 3u,
				indices_buffer + meshlet.base_index * 4u - parameters.num_meshlets * 16u,
				1u, meshlet.base_vertex, global_id);
		}
	}
	
#elif INDEXING_SHADER
	
	layout(local_size_x = GROUP_SIZE) in;
	
	layout(std140, binding = 0) uniform IndexingParameter {
		uint num_meshlets;
		uint base_group;
	};
	
	layout(std430, binding = 1) readonly buffer MeshletsBuffer { uint meshlets_buffer[]; };
	layout(std430, binding = 2) writeonly buffer IndexingBuffer { uvec4 indexing_buffer[]; };
	
	shared uint num_primitives;
	shared uint base_index;
	
	/*
	 */
	void main() {
		
		uint group_id = base_group + gl_WorkGroupID.x;
		uint local_id = gl_LocalInvocationIndex;
		
		// meshlet parameters
		[[branch]] if(local_id == 0u) {
			uint meshlet_index = (group_id % num_meshlets) * 12u;
			num_primitives = meshlets_buffer[meshlet_index + 0u];
			base_index = meshlets_buffer[meshlet_index + 2u];
		}
		memoryBarrierShared(); barrier();
		
		// indices
		uint indices_0 = 0u;
		uint indices_1 = 0u;
		uint indices_2 = 0u;
		[[branch]] if(local_id * 4u < num_primitives) {
			uint address = base_index + local_id * 3u;
			indices_0 = meshlets_buffer[address + 0u];
			indices_1 = meshlets_buffer[address + 1u];
			indices_2 = meshlets_buffer[address + 2u];
		}
		
		uint group_index = group_id << 8u;
		uint index = (GROUP_SIZE * group_id + local_id) * 3u;
		indexing_buffer[index + 0u] = (uvec4(indices_0, indices_0 >> 8u, indices_0 >> 16u, indices_0 >> 24u) & 0xffu) | group_index;
		indexing_buffer[index + 1u] = (uvec4(indices_1, indices_1 >> 8u, indices_1 >> 16u, indices_1 >> 24u) & 0xffu) | group_index;
		indexing_buffer[index + 2u] = (uvec4(indices_2, indices_2 >> 8u, indices_2 >> 16u, indices_2 >> 24u) & 0xffu) | group_index;
	}
	
#endif

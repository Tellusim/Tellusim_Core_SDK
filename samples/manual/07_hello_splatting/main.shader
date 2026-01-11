// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if GAUSSIAN_SHADER || SCATTER_SHADER || SPLATTING_SHADER
	
	/*
	 */
	#define Vector2i	ivec2
	#define Vector4f	vec4
	#define Quaternionf	vec4
	#define float16x8_t	vec4
	
	#include "main.h"
	
#endif

/*
 */
#if GAUSSIAN_SHADER || DISPATCH_SHADER || SCATTER_SHADER || SPLATTING_SHADER
	
	/*
	 */
	layout(row_major, binding = 0) uniform CommonParameters {
		mat4 projection;
		mat4 modelview;
		vec4 camera;
		int tiles_width;
		int tiles_height;
		int surface_width;
		int surface_height;
		uint max_gaussians;
		uint num_gaussians;
		uint num_tiles;
	};
	
#endif

/*
 */
#if GAUSSIAN_SHADER || SPLATTING_SHADER
	
	/*
	 */
	vec4 unpack_half4(vec2 v) {
		uvec2 u = floatBitsToUint(v);
		return vec4(unpackHalf2x16(u.x), unpackHalf2x16(u.y));
	}
	
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
	
#elif CLEAR_SHADER
	
	layout(local_size_x = GROUP_SIZE) in;
	
	layout(binding = 0) uniform ClearParameters {
		uint num_tiles;
	};
	
	layout(std430, binding = 1) writeonly buffer CountBuffer { uint count_buffer[]; };
	
	/*
	 */
	void main() {
		
		uint global_id = gl_GlobalInvocationID.x;
		
		// clear tile counter
		[[branch]] if(global_id < num_tiles) count_buffer[global_id + num_tiles] = 0u;
		
		// clear Gaussian counter
		[[branch]] if(global_id == 0u) count_buffer[num_tiles * 2u] = 0u;
	}
	
#elif GAUSSIAN_SHADER
	
	layout(local_size_x = GROUP_SIZE) in;
	
	layout(std430, binding = 1) buffer GaussiansBuffer { Gaussian gaussians_buffer[]; };
	layout(std430, binding = 2) buffer CountBuffer { uint count_buffer[]; };
	
	/*
	 */
	const float k0  =  0.282094791773878f;
	const float k10 = -0.488602511902919f;
	const float k11 =  0.488602511902919f;
	const float k12 = -0.488602511902919f;
	const float k20 =  1.092548430592079f;
	const float k21 = -1.092548430592079f;
	const float k22 =  0.315391565252520f;
	const float k23 = -1.092548430592079f;
	const float k24 =  0.546274215296039f;
	const float k30 = -0.590043589926643f;
	const float k31 =  2.890611442640554f;
	const float k32 = -0.457045799464465f;
	const float k33 =  0.373176332590115f;
	const float k34 = -0.457045799464465f;
	const float k35 =  1.445305721320277f;
	const float k36 = -0.590043589926643f;
	
	/*
	 */
	vec2 pack_half4(vec4 v) {
		uvec2 u = uvec2(packHalf2x16(v.xy), packHalf2x16(v.zw));
		return uintBitsToFloat(u);
	}
	
	vec3 get_color(uint index, float x, float y, float z) {
		float xx = x * x;
		float yy = y * y;
		float zz = z * z;
		float xy = x * y;
		float xz = x * z;
		float yz = y * z;
		#define DECLARE_HARMONICS(INDEX_0, INDEX_1, INDEX) \
			vec4 harmonics_ ## INDEX_0 = gaussians_buffer[index].harmonics[INDEX]; \
			vec4 harmonics_ ## INDEX_1 = unpack_half4(harmonics_ ## INDEX_0.zw); \
			harmonics_ ## INDEX_0 = unpack_half4(harmonics_ ## INDEX_0.xy);
		DECLARE_HARMONICS(0, 1, 0)
		DECLARE_HARMONICS(2, 3, 1)
		DECLARE_HARMONICS(4, 5, 2)
		DECLARE_HARMONICS(6, 7, 3)
		DECLARE_HARMONICS(8, 9, 4)
		DECLARE_HARMONICS(10, 11, 5)
		DECLARE_HARMONICS(12, 13, 6)
		vec3 color = harmonics_0.xyz * k0 +
			harmonics_1.xyz * (k10 * y) +
			harmonics_2.xyz * (k11 * z) +
			harmonics_3.xyz * (k12 * x) +
			harmonics_4.xyz * (k20 * xy) +
			harmonics_5.xyz * (k21 * yz) +
			harmonics_6.xyz * (k22 * (2.0f * zz - xx - yy)) +
			harmonics_7.xyz * (k23 * xz) +
			harmonics_8.xyz * (k24 * (xx - yy)) +
			harmonics_9.xyz * (k30 * (3.0f * xx - yy) * y) +
			harmonics_10.xyz * (k31 * xy * z) +
			harmonics_11.xyz * (k32 * (4.0f * zz - xx - yy) * y) +
			harmonics_12.xyz * (k33 * (2.0f * zz - 3.0f * xx - 3.0f * yy) * z) +
			harmonics_13.xyz * (k34 * (4.0f * zz - xx - yy) * x) +
			vec3(harmonics_0.w, harmonics_1.w, harmonics_2.w) * (k35 * (xx - yy) * z) +
			vec3(harmonics_3.w, harmonics_4.w, harmonics_5.w) * (k36 * (xx - 3.0f * yy) * x);
		return max(color + 0.5f, vec3(0.0f));
	}
	
	/*
	 */
	void main() {
		
		uint global_id = gl_GlobalInvocationID.x;
		
		[[branch]] if(global_id < num_gaussians) {
			
			// Gaussian position
			vec4 position = modelview * gaussians_buffer[global_id].position;
			[[branch]] if(position.z > -0.1f) return;
			float distance = length(position.xyz);
			
			// Gaussian rotation, scale, and opacity
			vec4 rotation_scale = gaussians_buffer[global_id].rotation_scale;
			vec4 scale_opacity = unpack_half4(rotation_scale.zw);
			
			// rotation matrix
			vec4 q = unpack_half4(rotation_scale.xy);
			vec4 x2 = q * (q.x * 2.0f);
			vec4 y2 = q * (q.y * 2.0f);
			vec4 z2 = q * (q.z * 2.0f);
			mat3 rotation = mat3(
				vec3(1.0f - y2.y - z2.z, y2.x - z2.w, x2.z + y2.w),
				vec3(y2.x + z2.w, 1.0f - x2.x - z2.z, z2.y - x2.w),
				vec3(x2.z - y2.w, z2.y + x2.w, 1.0f - x2.x - y2.y)
			);
			
			// scale matrix
			vec3 s = scale_opacity.xyz;
			mat3 scale = mat3(
				vec3(s.x, 0.0f, 0.0f),
				vec3(0.0f, s.y, 0.0f),
				vec3(0.0f, 0.0f, s.z)
			);
			
			// Jacobian matrix
			float iposition_z = 1.0f / abs(position.z);
			float size_x = abs(position.z / projection[0].x);
			float size_y = abs(position.z / projection[1].y);
			size_x = clamp(position.x, -size_x, size_x) * iposition_z;
			size_y = clamp(position.y, -size_y, size_y) * iposition_z;
			float pixel_x = float(surface_width) * projection[0].x * 0.5f * iposition_z;
			float pixel_y = float(surface_height) * projection[1].y * 0.5f * iposition_z;
			mat3 jacobian = mat3(
				vec3(pixel_x, 0.0f, pixel_x * size_x),
				vec3(0.0f, pixel_y, pixel_y * size_y),
				vec3(0.0f, 0.0f, 0.0f)
			);
			
			// covariance matrix
			mat3 transform = scale * rotation;
			#if CLAY_HLSL || CLAY_MTL || CLAY_WG
				mat3 basis = mat3(modelview) * jacobian;
			#else
				mat3 basis = transpose(mat3(modelview)) * jacobian;
			#endif
			mat3 m = transpose(basis) * transpose(transpose(transform) * transform) * basis;
			vec3 covariance = vec3(m[0].x + 0.3f, m[1].y + 0.3f, m[0].y);
			
			// perspective projection
			position = projection * position;
			position.xy = (position.xy * (0.5f / position.w) + 0.5f) * vec2(surface_width, surface_height);
			
			// Gaussian region
			vec2 region_size = sqrt(covariance.xy) * 3.0f;
			ivec2 group_size = ivec2(GROUP_WIDTH, GROUP_HEIGHT);
			ivec2 min_tile = ivec2(position.xy - region_size) / group_size;
			ivec2 max_tile = (ivec2(position.xy + region_size) + group_size - 1) / group_size;
			min_tile = clamp(min_tile, ivec2(0), ivec2(tiles_width, tiles_height));
			max_tile = clamp(max_tile, ivec2(0), ivec2(tiles_width, tiles_height));
			[[branch]] if(any(equal(min_tile, max_tile))) return;
			
			// number of Gaussians per tile
			for(int y = min_tile.y; y < max_tile.y; y++) {
				for(int x = min_tile.x; x < max_tile.x; x++) {
					int tile_index = tiles_width * y + x;
					atomicIncrement(count_buffer[tile_index + num_tiles]);
				}
			}
			
			// Gaussian color
			vec3 direction = normalize(gaussians_buffer[global_id].position.xyz - camera.xyz);
			vec4 color_opacity = vec4(get_color(global_id, direction.x, direction.y, direction.z), scale_opacity.w);
			
			// update Gaussian parameters
			uint index = atomicIncrement(count_buffer[num_tiles * 2u]);
			float idet = 1.0f / (covariance.x * covariance.y - covariance.z * covariance.z);
			gaussians_buffer[index].covariance_depth = vec4(covariance * vec3(-0.5f, -0.5f, 1.0f) * idet, distance);
			gaussians_buffer[index].position_color = vec4(position.xy, pack_half4(color_opacity));
			gaussians_buffer[index].min_tile = min_tile;
			gaussians_buffer[index].max_tile = max_tile;
		}
	}
	
#elif ALIGN_SHADER
	
	layout(local_size_x = GROUP_SIZE) in;
	
	layout(binding = 0) uniform AlignParameters {
		uint num_tiles;
	};
	
	layout(std430, binding = 1) buffer CountBuffer { uint count_buffer[]; };
	
	/*
	 */
	void main() {
		
		uint global_id = gl_GlobalInvocationID.x;
		
		// align tile counter
		[[branch]] if(global_id < num_tiles) {
			uint num_gaussians = count_buffer[global_id + num_tiles];
			count_buffer[global_id] = (num_gaussians + 3u) & ~3u;
		}
	}
	
#elif DISPATCH_SHADER
	
	layout(local_size_x = GROUP_SIZE) in;
	
	layout(std430, binding = 1) buffer CountBuffer { uint count_buffer[]; };
	layout(std430, binding = 2) writeonly buffer DispatchBuffer { uint dispatch_buffer[]; };
	
	/*
	 */
	void main() {
		
		uint global_id = gl_GlobalInvocationID.x;
		
		// radix sort dispatch
		[[branch]] if(global_id < num_tiles) {
			
			// order offset
			uint keys_offset = count_buffer[global_id];
			uint data_offset = keys_offset + max_gaussians;
			
			// radix sort dispatch
			uint index = global_id * 4u;
			dispatch_buffer[index + 0u] = keys_offset;
			dispatch_buffer[index + 1u] = data_offset;
			dispatch_buffer[index + 2u] = count_buffer[global_id + num_tiles];
			
			// clear tiles counter
			count_buffer[global_id + num_tiles] = 0u;
		}
		
		// index kernel dispatch
		[[branch]] if(global_id == 0u) {
			
			// scatter dispatch
			uint index = num_tiles * 4u;
			dispatch_buffer[index + 0u] = (count_buffer[num_tiles * 2u] + GROUP_SIZE - 1u) / GROUP_SIZE;
			dispatch_buffer[index + 1u] = 1u;
			dispatch_buffer[index + 2u] = 1u;
		}
	}
	
#elif SCATTER_SHADER
	
	layout(local_size_x = GROUP_SIZE) in;
	
	layout(std430, binding = 1) readonly buffer GaussiansBuffer { Gaussian gaussians_buffer[]; };
	layout(std430, binding = 2) buffer CountBuffer { uint count_buffer[]; };
	layout(std430, binding = 3) writeonly buffer OrderBuffer { uint order_buffer[]; };
	
	/*
	 */
	void main() {
		
		uint global_id = gl_GlobalInvocationID.x;
		
		uint num_gaussians = count_buffer[num_tiles * 2u];
		
		[[branch]] if(global_id < num_gaussians) {
			
			// Gaussian depth
			float position_z = gaussians_buffer[global_id].covariance_depth.w;
			uint depth = (floatBitsToUint(position_z) ^ 0x80000000u) >> 8u;
			
			// Gaussian region
			ivec2 min_tile = gaussians_buffer[global_id].min_tile;
			ivec2 max_tile = gaussians_buffer[global_id].max_tile;
			
			// scatter Gaussian
			[[loop]] for(int y = min_tile.y; y < max_tile.y; y++) {
				[[loop]] for(int x = min_tile.x; x < max_tile.x; x++) {
					
					// file index
					int tile_index = tiles_width * y + x;
					
					// order indices
					uint keys_index = count_buffer[tile_index] + atomicIncrement(count_buffer[tile_index + num_tiles]);
					uint data_index = keys_index + max_gaussians;
					
					order_buffer[keys_index] = depth;
					order_buffer[data_index] = global_id;
				}
			}
		}
	}
	
#elif SPLATTING_SHADER
	
	#if CLAY_MTL
		#define half		float16_t
		#define hvec3		f16vec3
		#define hvec4		f16vec4
	#else
		#define half		float
		#define hvec3		vec3
		#define hvec4		vec4
	#endif
	
	layout(local_size_x = GROUP_WIDTH / 4, local_size_y = GROUP_HEIGHT / 2) in;
	
	layout(std430, binding = 1) readonly buffer GaussiansBuffer { Gaussian gaussians_buffer[]; };
	layout(std430, binding = 2) readonly buffer CountBuffer { uint count_buffer[]; };
	layout(std430, binding = 3) readonly buffer OrderBuffer { uint order_buffer[]; };
	
	layout(binding = 0, set = 1, rgba8) uniform writeonly image2D out_surface;
	
	shared uint tile_gaussians;
	shared uint data_offset;
	
	/*
	 */
	void main() {
		
		ivec2 group_id = ivec2(gl_WorkGroupID.xy);
		ivec2 global_id = ivec2(gl_GlobalInvocationID.xy) * ivec2(4, 2);
		uint local_id = gl_LocalInvocationIndex;
		
		// global parameters
		[[branch]] if(local_id == 0u) {
			int tile_index = tiles_width * group_id.y + group_id.x;
			tile_gaussians = count_buffer[tile_index + num_tiles];
			data_offset = count_buffer[tile_index] + max_gaussians;
		}
		memoryBarrierShared(); barrier();
		
		vec2 position = vec2(global_id);
		
		half transparency_00 = 1.0f;
		half transparency_10 = 1.0f;
		half transparency_20 = 1.0f;
		half transparency_30 = 1.0f;
		half transparency_31 = 1.0f;
		half transparency_01 = 1.0f;
		half transparency_11 = 1.0f;
		half transparency_21 = 1.0f;
		
		hvec3 color_00 = hvec3(0.0f);
		hvec3 color_10 = hvec3(0.0f);
		hvec3 color_20 = hvec3(0.0f);
		hvec3 color_30 = hvec3(0.0f);
		hvec3 color_01 = hvec3(0.0f);
		hvec3 color_11 = hvec3(0.0f);
		hvec3 color_21 = hvec3(0.0f);
		hvec3 color_31 = hvec3(0.0f);
		
		[[loop]] for(uint i = 0u; i < tile_gaussians; i++) {
			
			uint index = order_buffer[data_offset + i];
			vec4 position_color = gaussians_buffer[index].position_color;
			vec3 covariance = gaussians_buffer[index].covariance_depth.xyz;
			hvec4 color_opacity = hvec4(unpack_half4(position_color.zw));
			
			vec2 direction_00 = vec2(position_color.xy - position);
			vec2 direction_10 = direction_00 - vec2(1.0f, 0.0f);
			vec2 direction_20 = direction_00 - vec2(2.0f, 0.0f);
			vec2 direction_30 = direction_00 - vec2(3.0f, 0.0f);
			vec2 direction_01 = direction_00 - vec2(0.0f, 1.0f);
			vec2 direction_11 = direction_00 - vec2(1.0f, 1.0f);
			vec2 direction_21 = direction_00 - vec2(2.0f, 1.0f);
			vec2 direction_31 = direction_00 - vec2(3.0f, 1.0f);
			
			half power_00 = half(dot(covariance, direction_00.yxx * direction_00.yxy));
			half power_10 = half(dot(covariance, direction_10.yxx * direction_10.yxy));
			half power_20 = half(dot(covariance, direction_20.yxx * direction_20.yxy));
			half power_30 = half(dot(covariance, direction_30.yxx * direction_30.yxy));
			half power_01 = half(dot(covariance, direction_01.yxx * direction_01.yxy));
			half power_11 = half(dot(covariance, direction_11.yxx * direction_11.yxy));
			half power_21 = half(dot(covariance, direction_21.yxx * direction_21.yxy));
			half power_31 = half(dot(covariance, direction_31.yxx * direction_31.yxy));
			
			half alpha_00 = min(color_opacity.w * exp(power_00), half(1.0f));
			half alpha_10 = min(color_opacity.w * exp(power_10), half(1.0f));
			half alpha_20 = min(color_opacity.w * exp(power_20), half(1.0f));
			half alpha_30 = min(color_opacity.w * exp(power_30), half(1.0f));
			half alpha_01 = min(color_opacity.w * exp(power_01), half(1.0f));
			half alpha_11 = min(color_opacity.w * exp(power_11), half(1.0f));
			half alpha_21 = min(color_opacity.w * exp(power_21), half(1.0f));
			half alpha_31 = min(color_opacity.w * exp(power_31), half(1.0f));
			
			color_00 += color_opacity.xyz * (alpha_00 * transparency_00);
			color_10 += color_opacity.xyz * (alpha_10 * transparency_10);
			color_20 += color_opacity.xyz * (alpha_20 * transparency_20);
			color_30 += color_opacity.xyz * (alpha_30 * transparency_30);
			color_01 += color_opacity.xyz * (alpha_01 * transparency_01);
			color_11 += color_opacity.xyz * (alpha_11 * transparency_11);
			color_21 += color_opacity.xyz * (alpha_21 * transparency_21);
			color_31 += color_opacity.xyz * (alpha_31 * transparency_31);
			
			transparency_00 *= half(1.0f) - alpha_00;
			transparency_10 *= half(1.0f) - alpha_10;
			transparency_20 *= half(1.0f) - alpha_20;
			transparency_30 *= half(1.0f) - alpha_30;
			transparency_01 *= half(1.0f) - alpha_01;
			transparency_11 *= half(1.0f) - alpha_11;
			transparency_21 *= half(1.0f) - alpha_21;
			transparency_31 *= half(1.0f) - alpha_31;
			
			half transparency_0 = max(max(transparency_00, transparency_10), max(transparency_20, transparency_30));
			half transparency_1 = max(max(transparency_01, transparency_11), max(transparency_21, transparency_31));
			[[branch]] if(max(transparency_0, transparency_1) < half(1.0f / 255.0f)) break;
		}
		
		// save result
		[[branch]] if(all(lessThan(global_id, ivec2(surface_width, surface_height)))) {
			imageStore(out_surface, global_id + ivec2(0, 0), vec4(color_00, transparency_00));
			imageStore(out_surface, global_id + ivec2(1, 0), vec4(color_10, transparency_10));
			imageStore(out_surface, global_id + ivec2(2, 0), vec4(color_20, transparency_20));
			imageStore(out_surface, global_id + ivec2(3, 0), vec4(color_30, transparency_30));
			imageStore(out_surface, global_id + ivec2(0, 1), vec4(color_01, transparency_01));
			imageStore(out_surface, global_id + ivec2(1, 1), vec4(color_11, transparency_11));
			imageStore(out_surface, global_id + ivec2(2, 1), vec4(color_21, transparency_21));
			imageStore(out_surface, global_id + ivec2(3, 1), vec4(color_31, transparency_31));
		}
	}
	
#endif

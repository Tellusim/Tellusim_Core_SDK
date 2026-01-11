// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

#if INVERSE_SHADER
	
	layout(local_size_x = GROUP_SIZE, local_size_y = GROUP_SIZE) in;
	
	layout(binding = 0, set = 0) uniform texture2D in_texture;
	layout(binding = 1, set = 0, r32f) uniform writeonly image2D out_surface;
	
	/*
	 */
	void main() {
		
		ivec2 texture_size = textureSize(in_texture, 0);
		ivec2 global_id = ivec2(gl_GlobalInvocationID.xy);
		
		if(all(lessThan(global_id, texture_size))) {
			
			float value = 1.0f - texelFetch(in_texture, global_id, 0).x;
			
			imageStore(out_surface, global_id, vec4(value, 0.0f, 0.0f, 0.0f));
		}
	}
	
#elif FILTER_SHADER
	
	layout(local_size_x = GROUP_SIZE, local_size_y = GROUP_SIZE) in;
	
	layout(binding = 0, set = 0) uniform texture2D in_texture_0;
	layout(binding = 1, set = 0) uniform texture2D in_texture_1;
	layout(binding = 2, set = 0, rg32f) uniform writeonly image2D out_surface;
	
	/*
	 */
	void main() {
		
		ivec2 texture_size = textureSize(in_texture_0, 0);
		ivec2 global_id = ivec2(gl_GlobalInvocationID.xy);
		
		[[branch]] if(global_id.x < texture_size.x) {
			
			// noise texture
			vec2 ri_0 = texelFetch(in_texture_0, global_id, 0).xy;
			float r0 = ri_0.x;
			float i0 = ri_0.y;
			
			// convolution texture
			vec2 ri_1 = texelFetch(in_texture_1, global_id, 0).xy;
			float r1 = ri_1.x;
			float i1 = ri_1.y;
			
			// complex multiplication
			float r = r0 * r1 - i0 * i1;
			float i = i0 * r1 + r0 * i1;
			
			imageStore(out_surface, global_id, vec4(r, i, 0.0f, 0.0f));
		}
	}
	
#elif MIN_SAMPLE_SHADER || MAX_SAMPLE_SHADER
	
	layout(local_size_x = GROUP_SIZE, local_size_y = GROUP_SIZE) in;
	
	layout(std140, binding = 0) uniform SampleParameters {
		uint num_groups;
	};
	
	layout(std430, binding = 1) buffer PositionBuffer { ivec4 position_buffer[]; };
	
	layout(binding = 0, set = 1) uniform texture2D in_texture_0;
	layout(binding = 1, set = 1) uniform texture2D in_texture_1;
	
	shared float weights[GROUP_SIZE * GROUP_SIZE];
	shared ivec2 positions[GROUP_SIZE * GROUP_SIZE];
	
	/*
	 */
	void main() {
		
		uint local_id = gl_LocalInvocationIndex;
		uint local_id_2 = local_id << 1u;
		
		uvec2 group_id = uvec2(gl_WorkGroupID.xy);
		ivec2 global_id = ivec2(gl_GlobalInvocationID.xy);
		
		// sample weight
		float value = texelFetch(in_texture_0, global_id, 0).x;
		float weight = texelFetch(in_texture_1, global_id, 0).x;
		#if MIN_SAMPLE_SHADER
			if(value > 0.5f) weight = -1e9f;
			else weight = -weight;
		#elif MAX_SAMPLE_SHADER
			if(value < 0.5f) weight = -1e9f;
		#else
			#error unknown shader
		#endif
		weights[local_id] = weight;
		positions[local_id] = global_id;
		memoryBarrierShared(); barrier();
		
		// find position with maximum weight
		for(uint offset = 1u; offset < GROUP_SIZE * GROUP_SIZE; offset <<= 1u) {
			uint index = offset * local_id_2;
			[[branch]] if(index + offset < GROUP_SIZE * GROUP_SIZE) {
				float weight = weights[index + offset];
				if(weights[index] < weight) {
					weights[index] = weight;
					positions[index] = positions[index + offset];
				}
			}
			memoryBarrierShared(); barrier();
		}
		
		// save maximum weight position
		[[branch]] if(local_id == 0u) {
			uint index = num_groups * group_id.y + group_id.x;
			position_buffer[index] = ivec4(positions[0], floatBitsToInt(weights[0]), 0.0f);
		}
	}
	
#elif POSITION_SHADER
	
	layout(local_size_x = GROUP_SIZE) in;
	
	layout(std140, binding = 0) uniform PositionParameters {
		uint num_positions;
	};
	
	layout(std430, binding = 1) buffer PositionBuffer { ivec4 position_buffer[]; };
	
	shared float weights[GROUP_SIZE];
	shared ivec2 positions[GROUP_SIZE];
	
	#define UDIV(A, B)	(((A) + (B) - 1u) / (B))
	
	/*
	 */
	void main() {
		
		uint local_id = gl_LocalInvocationIndex;
		uint local_id_2 = local_id << 1;
		
		// sample positions
		weights[local_id] = -1e9f;
		positions[local_id] = ivec2(0);
		uint steps = UDIV(num_positions, GROUP_SIZE);
		[[loop]] for(uint i = 0; i < steps ; i++) {
			uint index = GROUP_SIZE * i + local_id;
			[[branch]] if(index < num_positions) {
				ivec4 position = position_buffer[index];
				float weight = intBitsToFloat(position.z);
				if(weights[local_id] < weight) {
					weights[local_id] = weight;
					positions[local_id] = position.xy;
				}
			}
		}
		memoryBarrierShared(); barrier();
		
		// find position with maximum weight
		for(uint offset = 1u; offset < GROUP_SIZE; offset <<= 1u) {
			uint index = offset * local_id_2;
			[[branch]] if(index + offset < GROUP_SIZE) {
				float weight = weights[index + offset];
				if(weights[index] < weight) {
					weights[index] = weight;
					positions[index] = positions[index + offset];
				}
			}
			memoryBarrierShared(); barrier();
		}
		
		// save maximum weight position
		[[branch]] if(local_id == 0u) {
			position_buffer[0] = ivec4(positions[0], floatBitsToInt(weights[0]), 0.0f);
		}
	}
	
#elif UPDATE_SHADER
	
	layout(local_size_x = GROUP_SIZE) in;
	
	layout(std140, binding = 0) uniform UpdateParameters {
		ivec2 texture_size;
		float value;
		uint index;
	};
	
	layout(std430, binding = 1) buffer SequenceBuffer { ivec4 sequence_buffer[]; };
	layout(std430, binding = 2) buffer PositionBuffer { ivec4 position_buffer[]; };
	
	layout(binding = 0, set = 1, r32f) uniform image2D out_surface;
	
	/*
	 */
	void main() {
		
		ivec2 surface_size = imageSize(out_surface);
		uint local_id = gl_LocalInvocationIndex;
		
		[[branch]] if(local_id == 0u) {
			
			ivec4 position = position_buffer[0];
			
			// downscale position
			ivec2 offset = (texture_size - surface_size) / 2;
			if(position.x < offset.x) position.x += surface_size.x;
			if(position.y < offset.y) position.y += surface_size.y;
			position.xy = (position.xy - offset) % surface_size;
			
			// update noise
			imageStore(out_surface, position.xy, vec4(value, 0.0f, 0.0f, 0.0f));
			
			// update sequence
			if(index != ~0u) sequence_buffer[index] = position;
		}
	}
	
#elif RENDER_SHADER
	
	layout(local_size_x = GROUP_SIZE, local_size_y = GROUP_SIZE) in;
	
	layout(std140, binding = 0) uniform RenderParameters {
		int width;
		int height;
	};
	
	layout(std430, binding = 1) buffer SequenceBuffer { ivec4 sequence_buffer[]; };
	
	layout(binding = 0, set = 1, r32f) uniform writeonly image2D out_surface;
	
	/*
	 */
	void main() {
		
		ivec2 surface_size = imageSize(out_surface);
		ivec2 global_id = ivec2(gl_GlobalInvocationID.xy);
		
		if(all(lessThan(global_id, surface_size))) {
			
			int index = width * global_id.y + global_id.x;
			ivec2 position = sequence_buffer[index].xy;
			
			float value = float(index) / float(width * height - 1);
			
			imageStore(out_surface, position, vec4(value, 0.0f, 0.0f, 0.0f));
		}
	}
	
#elif LAYER_SHADER
	
	layout(local_size_x = GROUP_SIZE, local_size_y = GROUP_SIZE) in;
	
	layout(std140, binding = 0) uniform LayerParameters {
		float threshold;
	};
	
	layout(binding = 0, set = 1) uniform texture2D in_texture;
	layout(binding = 1, set = 1, r32f) uniform writeonly image2D out_surface;
	
	/*
	 */
	void main() {
		
		ivec2 size = textureSize(in_texture, 0);
		ivec2 global_id = ivec2(gl_GlobalInvocationID.xy);
		
		if(all(lessThan(global_id, size))) {
			
			float value = 1.0f - texelFetch(in_texture, size - global_id - 1, 0).x;
			
			value = (value < threshold) ? 1.0f : 0.0f;
			
			imageStore(out_surface, global_id, vec4(value, 0.0f, 0.0f, 0.0f));
		}
	}
	
#elif UPSCALE_SHADER
	
	layout(local_size_x = GROUP_SIZE, local_size_y = GROUP_SIZE) in;
	
	layout(binding = 0, set = 0) uniform texture2D in_texture;
	layout(binding = 1, set = 0, r32f) uniform writeonly image2D out_surface;
	
	/*
	 */
	void main() {
		
		ivec2 surface_size = imageSize(out_surface);
		ivec2 texture_size = textureSize(in_texture, 0);
		ivec2 global_id = ivec2(gl_GlobalInvocationID.xy);
		
		ivec2 position = global_id;
		ivec2 offset = (surface_size - texture_size) / 2;
		if(position.x < offset.x) position.x += texture_size.x;
		if(position.y < offset.y) position.y += texture_size.y;
		position = (position - offset) % texture_size;
		
		float value = texelFetch(in_texture, position, 0).x;
		
		imageStore(out_surface, global_id, vec4(value, 0.0f, 0.0f, 0.0f));
	}
	
#endif

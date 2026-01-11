// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if COMPUTE_SHADER
	
	layout(local_size_x = 8, local_size_y = 4) in;
	
	layout(std430, binding = 0) buffer ScalarBuffer { uint scalar_buffer[]; };
	
	shared uint value;
	
	/*
	 */
	inline uint printv(uint value) { return value; }
	inline uint printv(float value) { return floatBitsToUint(value); }
	#define PRINTV(VALUE, INDEX) scalar_buffer[i + (INDEX + 1u)] = printv(VALUE);
	#define PRINTF(ARGC, ...) { \
		uint i = atomicAdd(scalar_buffer[0u], __VA_ARGC__ + 1u) + 1u; \
		scalar_buffer[i] = __VA_ARGC__ | ((ARGC) << 16u); \
		__VA_ARGM__(PRINTV) \
	}
	#define printf(FORMAT, ...) PRINTF(__VA_ARGC__, @FORMAT, __VA_ARGS__)
	
	/*
	 */
	void main() {
		
		uint local_id = gl_LocalInvocationIndex;
		uvec2 global_id = gl_GlobalInvocationID.xy;
		
		[[branch]] if(local_id == 0u) value = 0u;
		memoryBarrierShared(); barrier();
		
		printf("global: %ux%u local: %2u shared: %2.0f\n", global_id.x, global_id.y, local_id, float(atomicIncrement(value)));
	}
	
#endif

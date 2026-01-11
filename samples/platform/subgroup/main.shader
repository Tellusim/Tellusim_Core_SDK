// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#version 430 core

/*
 */
#if COMPUTE_SHADER
	
	#if _INTEL
		#pragma subgroup_size(32)
	#endif
	
	layout(local_size_x = GROUP_SIZE) in;
	
	layout(std430, binding = 0) writeonly buffer DataBuffer { uvec4 data[]; };
	
	/*
	 */
	void main() {
		
		uint id = gl_GlobalInvocationID.x;
		
		uint x0 = subgroupAdd(id);
		uint y0 = subgroupInclusiveAdd(id);
		uint z0 = subgroupExclusiveAdd(id);
		uint w0 = gl_SubgroupInvocationID;
		
		uint x1 = subgroupMul((id & 3u) + 1u);
		uint y1 = subgroupInclusiveMul((id & 3u) + 1u);
		uint z1 = subgroupExclusiveMul((id & 3u) + 1u);
		uint w1 = gl_SubgroupSize;
		
		uint x2 = subgroupMin(SIZE - 1u - id);
		uint y2 = subgroupInclusiveMin(SIZE - 1u - id);
		uint z2 = subgroupExclusiveMin(SIZE - 1u - id);
		
		uint x3 = subgroupMax(id);
		uint y3 = subgroupInclusiveMax(id);
		uint z3 = subgroupExclusiveMax(id);
		
		data[id * 4u + 0u] = uvec4(x0, y0, z0, w0);
		data[id * 4u + 1u] = uvec4(x1, y1, z1, w1);
		data[id * 4u + 2u] = uvec4(x2, y2, z2, 0u);
		data[id * 4u + 3u] = uvec4(x3, y3, z3, 0u);
	}
	
#endif

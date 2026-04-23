// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

/*
 */
__kernel void main_(const uint size, const float scale, const float time, __global float4 *positions) {
	
	uint global_x = get_global_id(0);
	uint global_y = get_global_id(1);
	
	uint id = global_y * size + global_x;
	
	float x = (float)global_x / size * 2.0f - 1.0f;
	float y = (float)global_y / size * 2.0f - 1.0f;
	
	float r = sin(x * scale) * 0.5f + 0.5f;
	float g = cos(y * scale) * 0.5f + 0.5f;
	float b = fmax(1.0f - r - g, 0.0f);
	
	uint color = 0xff000000u;
	color |= (uint)(r * 255.0f) << 0u;
	color |= (uint)(g * 255.0f) << 8u;
	color |= (uint)(b * 255.0f) << 16u;
	
	float z = r + g + sin(sqrt(x * x + y * y) * 4.0f + time * 2.0f) * 4.0f;
	
	positions[id] = (float4)(x * scale, y * scale, z, as_float(color));
}

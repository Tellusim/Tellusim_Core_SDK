// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

/*
 */
__kernel void main_(const uint size, const float time, __write_only image2d_t surface) {
	
	uint global_x = get_global_id(0);
	uint global_y = get_global_id(1);
	
	float k = time * 2.0f;
	float s = sin(time * 0.5f);
	float c = cos(time * 0.5f);
	
	float2 t = (float2)((float)global_x / (float)size - 0.5f, (float)global_y / (float)size - 0.5f);
	
	t = (float2)((s * t.x + c * t.y) * 32.0f - 16.0f, (c * t.x - s * t.y) * 32.0f - 16.0f);
	
	float v = sin(t.x + k) + sin(t.y + k) + sin(t.x + t.y + k) + sin(sqrt(t.x * t.x + t.y * t.y) + k * 3.0f) + k * 2.0f;
	
	float r = cos(v + 0.00f) * 0.5f + 0.5f;
	float g = cos(v + 1.57f) * 0.5f + 0.5f;
	float b = cos(v + 3.14f) * 0.5f + 0.5f;
	
	write_imagef(surface, (int2)(global_x, global_y), (float4)(r, g, b, 1.0f));
}

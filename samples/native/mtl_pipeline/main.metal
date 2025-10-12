// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

##include <metal_stdlib>

using namespace metal;

/*
 */
struct VertexOut {
	float4 position [[position]];
	float2 texcoord;
};

/*
 */
#if VERTEX_SHADER
	
	/*
	 */
	struct alignas(256) Parameters {
		float aspect;
		float time;
	};
	
	/*
	 */
	vertex VertexOut vertex_main(uint vertex_id [[vertex_id]],
		constant Parameters &parameters [[buffer(0)]]) {
		
		VertexOut OUT;
		
		float height = 2.0f * sqrt(5.0f);
		float2 position = float2(0.0f, height);
		if(vertex_id == 0) position = float2(-sqrt(15.0f), -sqrt(5.0f));
		if(vertex_id == 1) position = float2( sqrt(15.0f), -sqrt(5.0f));
		position /= height;
		
		OUT.texcoord = position + 0.5f;
		
		OUT.position.x = (sin(parameters.time) * position.x - cos(parameters.time) * position.y) / parameters.aspect;
		OUT.position.y = (cos(parameters.time) * position.x + sin(parameters.time) * position.y);
		OUT.position.z = 0.0f;
		OUT.position.w = 1.0f;
		
		return OUT;
	}
	
#elif FRAGMENT_SHADER
	
	/*
	 */
	fragment float4 fragment_main(VertexOut IN [[stage_in]]) {
		return float4(IN.texcoord, 1.0f - IN.texcoord.x - IN.texcoord.y, 1.0f);
	}
	
#endif

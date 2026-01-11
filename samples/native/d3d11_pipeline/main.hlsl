// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

/*
 */
struct VertexOut {
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD0;
};

/*
 */
#if VERTEX_SHADER
	
	/*
	 */
	cbuffer Parameters : register(b0) {
		float aspect;
		float time;
	};
	
	/*
	 */
	VertexOut main(uint vertex_id : SV_VertexID) {
		
		VertexOut OUT;
		
		float height = 2.0f * sqrt(5.0f);
		float2 position = float2(0.0f, height);
		if(vertex_id == 0) position = float2(-sqrt(15.0f), -sqrt(5.0f));
		if(vertex_id == 1) position = float2( sqrt(15.0f), -sqrt(5.0f));
		position /= height;
		
		OUT.texcoord = position + 0.5f;
		
		OUT.position.x = (sin(time) * position.x - cos(time) * position.y) / aspect;
		OUT.position.y = (cos(time) * position.x + sin(time) * position.y);
		OUT.position.z = 0.0f;
		OUT.position.w = 1.0f;
		
		return OUT;
	}
	
#elif FRAGMENT_SHADER
	
	/*
	 */
	float4 main(VertexOut IN) : SV_Target0 {
		return float4(IN.texcoord, 1.0f - IN.texcoord.x - IN.texcoord.y, 1.0f);
	}
	
#endif

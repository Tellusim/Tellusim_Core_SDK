// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

/*
 */
#if VERTEX_SHADER
	
	cbuffer CommonParameters : register(b0) {
		row_major float4x4 projection;
		row_major float4x4 modelview;
		row_major float4x4 transform;
		float4 camera;
	};
	
	struct ShaderIn {
		float4 position : Position;
		float3 normal : TexCoord0;
	};
	
	struct ShaderOut {
		float3 direction : TexCoord0;
		float3 normal : TexCoord1;
		float4 position : SV_Position;
	};
	
	/*
	 */
	ShaderOut main(ShaderIn IN) {
		
		ShaderOut OUT;
		
		float4 position = mul(transform, IN.position);
		
		OUT.position = mul(projection, mul(modelview, position));
		OUT.direction = camera.xyz - position.xyz;
		OUT.normal = mul(transform, float4(IN.normal, 0.0)).xyz;
		
		return OUT;
	}
	
#elif FRAGMENT_SHADER
	
	struct ShaderIn {
		float3 direction : TexCoord0;
		float3 normal : TexCoord1;
	};
	
	/*
	 */
	float4 main(ShaderIn IN) : SV_Target0 {
		
		float3 direction = normalize(IN.direction);
		float3 normal = normalize(IN.normal);
		
		float diffuse = clamp(dot(direction, normal), 0.0, 1.0);
		float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0, 1.0), 32.0);
		float color = diffuse + specular;
		
		return float4(color, color, color, 1.0);
	}
	
#endif

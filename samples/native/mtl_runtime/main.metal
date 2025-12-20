// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

##include <metal_stdlib>

using namespace metal;

/*
 */
#if VERTEX_SHADER
	
	struct alignas(256) CommonParameters {
		float4x4 projection;
		float4x4 modelview;
		float4x4 transform;
		float4 camera;
	};
	
	struct ShaderIn {
		float4 position [[attribute(0)]];
		float3 normal [[attribute(1)]];
	};
	
	struct ShaderOut {
		float3 direction;
		float3 normal;
		float4 position [[position]];
	};
	
	/*
	 */
	[[vertex]] ShaderOut vertex_main(ShaderIn IN [[stage_in]],
		constant CommonParameters &U0 [[buffer(1)]]) {
		
		ShaderOut OUT;
		
		float4 position = IN.position * U0.transform;
		
		OUT.position = (position * U0.modelview) * U0.projection;
		OUT.direction = U0.camera.xyz - position.xyz;
		OUT.normal = (float4(IN.normal, 0.0) * U0.transform).xyz;
		
		return OUT;
	}
	
#elif FRAGMENT_SHADER
	
	struct ShaderIn {
		float3 direction;
		float3 normal;
	};
	
	/*
	 */
	[[fragment]] float4 fragment_main(ShaderIn IN [[stage_in]]) {
		
		float3 direction = normalize(IN.direction);
		float3 normal = normalize(IN.normal);
		
		float diffuse = clamp(dot(direction, normal), 0.0, 1.0);
		float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0, 1.0), 32.0);
		
		return float4(float3(diffuse + specular), 1.0);
	}
	
#endif

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#pragma entry(null)
#pragma target(lib_6_8)

struct Index {
	uint2 index;
};

cbuffer CommonParameters : register(b0) {
	row_major float4x4 projection;
	row_major float4x4 imodelview;
	float4 camera;
	float4 light;
	float time;
};

RWByteAddressBuffer vertex_buffer : register(u1);
RWByteAddressBuffer index_buffer : register(u2);

RWTexture2D<unorm float4> out_surface : register(u0);

RaytracingAccelerationStructure tracing : register(t0);

/*
 */
float4 trace(float2 texcoord, float4 color) {
	
	float x = (texcoord.x * 2.0f - 1.0f + projection[2].x) / projection[0].x;
	float y = (texcoord.y * 2.0f - 1.0f + projection[2].y) / projection[1].y;
	
	float3 position = mul(imodelview, float4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
	float3 direction = normalize(mul(imodelview, float4(x, y, -1.0f, 1.0f)).xyz - position);
	
	// ray description
	RayDesc ray_desc;
	ray_desc.Origin = position;
	ray_desc.TMin = 0.0f;
	ray_desc.Direction = direction;
	ray_desc.TMax = 1000.0f;
	
	// ray query
	RayQuery<RAY_FLAG_NONE> ray_query;
	ray_query.TraceRayInline(tracing, 1u, 255, ray_desc);
	while(ray_query.Proceed()) {
		if(ray_query.CandidateType() == CANDIDATE_NON_OPAQUE_TRIANGLE) {
			ray_query.CommitNonOpaqueTriangleHit();
		}
	}
	
	// triangle intersection
	[branch] if(ray_query.CommittedStatus() == COMMITTED_TRIANGLE_HIT) {
		
		position += (direction * ray_query.CommittedRayT());
		direction = -direction;
		
		// intersection normal
		uint index = ray_query.CommittedPrimitiveIndex() * 12;
		float2 texcoord = ray_query.CommittedTriangleBarycentrics();
		float3 normal_0 = asfloat(vertex_buffer.Load4(index_buffer.Load(index + 0) * 32 + 16).xyz);
		float3 normal_1 = asfloat(vertex_buffer.Load4(index_buffer.Load(index + 4) * 32 + 16).xyz);
		float3 normal_2 = asfloat(vertex_buffer.Load4(index_buffer.Load(index + 8) * 32 + 16).xyz);
		float3 normal = ((normal_0 * ((1.0f - texcoord.x) - texcoord.y)) + (normal_1 * texcoord.x)) + (normal_2 * texcoord.y);
		
		// transform normal
		float4x3 transform = ray_query.CommittedObjectToWorld4x3();
		normal = normalize(((transform[0] * normal.x) + (transform[1] * normal.y)) + (transform[2] * normal.z));
		
		// phong lighting
		float3 light_direction = normalize(light.xyz - position);
		float diffuse = saturate(dot(light_direction, normal));
		float specular = pow(saturate(dot(reflect(-light_direction, normal), direction)), 16.0f);
		
		// ambient lighting
		float3 camera_direction = normalize(camera.xyz - position);
		diffuse += saturate(dot(camera_direction, normal)) * 0.2f;
		
		// model material
		color = float4(float3(0.2f, 0.8f, 0.8f) * diffuse + specular, 1.0f);
	}
	
	return color;
}

/*
 */
[Shader("node")]
[NodeIsProgramEntry]
[NodeLaunch("broadcasting")]
[NodeDispatchGrid(128, 128, 1)]
[NumThreads(8, 8, 1)]
void main(uint3 global_id : SV_DispatchThreadID,
	[MaxRecords(64)] [NodeArraySize(3)] NodeOutputArray<Index> nodes) {
	
	// thread output
	uint index = 0u;
	switch(uint(time) % 6u) {
		case 0: index = 0u; break;
		case 1: index = 1u; break;
		case 2: index = 2u; break;
		case 3: index = global_id.x; break;
		case 4: index = global_id.y; break;
		case 5: index = global_id.x ^ global_id.y; break;
	}
	ThreadNodeOutputRecords<Index> OUT = nodes[index % 3].GetThreadNodeOutputRecords(1);
	OUT[0].index = global_id.xy;
	OUT.OutputComplete();
}

/*
 */
[Shader("node")]
[NodeID("nodes", 0)]
[NodeLaunch("thread")]
void node_0(ThreadNodeInputRecord<Index> IN) {
	float2 texcoord = (float2(IN.Get().index) + 0.5f) / 1024.0f;
	out_surface[IN.Get().index] = trace(texcoord, float4(0.1f, 0.3f, 0.3f, 0.0f));
}

[Shader("node")]
[NodeID("nodes", 1)]
[NodeLaunch("thread")]
void node_1(ThreadNodeInputRecord<Index> IN) {
	float2 texcoord = (float2(IN.Get().index) + 0.5f) / 1024.0f;
	out_surface[IN.Get().index] = trace(texcoord, float4(0.3f, 0.1f, 0.3f, 0.0f));
}

[Shader("node")]
[NodeID("nodes", 2)]
[NodeLaunch("thread")]
void node_2(ThreadNodeInputRecord<Index> IN) {
	float2 texcoord = (float2(IN.Get().index) + 0.5f) / 1024.0f;
	out_surface[IN.Get().index] = trace(texcoord, float4(0.3f, 0.3f, 0.1f, 0.0f));
}

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#pragma entry(null)
#pragma target(lib_6_8)

struct Index {
	uint2 index;
};

cbuffer CommonParameters : register(b0) {
	float time;
};

RWTexture2D<unorm float4> out_surface : register(u0);

/*
 */
[Shader("node")]
[NodeIsProgramEntry]
[NodeLaunch("broadcasting")]
[NodeDispatchGrid(128, 128, 1)]
[NumThreads(8, 8, 1)]
void main(uint3 global_id : SV_DispatchThreadID,
	[MaxRecords(64)] [NodeArraySize(2)] NodeOutputArray<Index> nodes) {
	
	float distance = length(float2(global_id.xy) - 512.0f);
	float2 texcoord = float2(global_id.xy) / 1024.0f - 0.5f;
	float radius = sin(atan2(texcoord.x, texcoord.y) * 9.0f);
	
	// thread output
	uint index = (distance < ((0.2f + radius * 0.1f) * sin(time) + 0.6f) * 512.0f) ? 0 : 1;
	ThreadNodeOutputRecords<Index> OUT = nodes[index].GetThreadNodeOutputRecords(1);
	OUT[0].index = global_id.xy;
	OUT.OutputComplete();
}

/*
 */
[Shader("node")]
[NodeID("nodes", 0)]
[NodeLaunch("thread")]
void plasma_node(ThreadNodeInputRecord<Index> IN) {
	
	float k = time * 2.0f;
	float s = sin(time * 0.5f);
	float c = cos(time * 0.5f);
	
	float2 t = float2(IN.Get().index) / 1024.0f - 0.5f;
	t = float2(s * t.x + c * t.y, c * t.x - s * t.y) * 32.0f - 16.0f;
	float v = sin(t.x + k) + sin(t.y + k) + sin(t.x + t.y + k) + sin(length(t) + k * 3.0f) + k * 2.0f;
	
	float4 color = float4((cos(float3(0.0f, 1.57f, 3.14f) + v) * 0.5f) + 0.5f, 1.0f);
	
	out_surface[IN.Get().index] = color;
}

/*
 */
[Shader("node")]
[NodeID("nodes", 1)]
[NodeLaunch("thread")]
void clear_node(ThreadNodeInputRecord<Index> IN) {
	
	out_surface[IN.Get().index] = 0.0f;
}

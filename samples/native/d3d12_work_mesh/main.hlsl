// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#pragma entry(null)
#pragma target(lib_6_9)
#pragma flags(internal)

struct Index {
	uint2 index;
};

struct Vertex {
	float4 color : TexCoord0;
	float4 position : SV_Position;
};

cbuffer CommonParameters : register(b0) {
	float time;
};

/*
 */
float4 get_color(float2 p, float time) {
	float k = time * 2.0f;
	float s = sin(time * 0.5f);
	float c = cos(time * 0.5f);
	p = float2(s * p.x + c * p.y, c * p.x - s * p.y) * 32.0f - 16.0f;
	float v = sin(p.x + k) + sin(p.y + k) + sin(p.x + p.y + k) + sin(length(p) + k * 3.0f) + k * 2.0f;
	return float4((cos(float3(0.0f, 1.57f, 3.14f) + v) * 0.5f) + 0.5f, 1.0f);
}

float4 get_position(float2 p, float time) {
	p.x *= cos(p.y * 3.0f + time * 3.0f) * 0.25f + 0.75f;
	p.y *= sin(p.x * 4.0f + time * 2.0f) * 0.25f + 0.75f;
	return float4(p, 0.0f, 1.0f);
}

/*
 */
[Shader("node")]
[NodeIsProgramEntry]
[NodeLaunch("broadcasting")]
[NodeDispatchGrid(16, 16, 1)]
[NumThreads(8, 8, 1)]
void main(uint3 global_id : SV_DispatchThreadID,
	[MaxRecords(64)] NodeOutput<Index> mesh) {
	
	// thread output
	ThreadNodeOutputRecords<Index> OUT = mesh.GetThreadNodeOutputRecords(1);
	OUT[0].index = global_id.xy;
	OUT.OutputComplete();
}

/*
 */
[Shader("node")]
[NodeLaunch("mesh")]
[NumThreads(1, 1, 1)]
[NodeDispatchGrid(1, 1, 1)]
[OutputTopology("triangle")]
void mesh(DispatchNodeInputRecord<Index> IN,
	out vertices Vertex vertices[4],
	out indices uint3 indices[2]) {
	
	SetMeshOutputCounts(4, 2);
	
	float iscale = 1.0f / (16.0f * 8.0f + 1.0f);
	float2 position = float2(IN.Get().index + 1) * iscale * 2.0f - 1.0f;
	float2 position_0 = position + float2(-1.0f,  1.0f) * iscale;
	float2 position_1 = position + float2(-1.0f, -1.0f) * iscale;
	float2 position_2 = position + float2( 1.0f, -1.0f) * iscale;
	float2 position_3 = position + float2( 1.0f,  1.0f) * iscale;
	
	vertices[0].position = get_position(position_0, time);
	vertices[1].position = get_position(position_1, time);
	vertices[2].position = get_position(position_2, time);
	vertices[3].position = get_position(position_3, time);
	
	vertices[0].color = get_color(position_0, time);
	vertices[1].color = get_color(position_1, time);
	vertices[2].color = get_color(position_2, time);
	vertices[3].color = get_color(position_3, time);
	
	indices[0] = uint3(0, 1, 2);
	indices[1] = uint3(2, 3, 0);
}

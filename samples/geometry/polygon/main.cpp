// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <math/TellusimMath.h>
#include <geometry/TellusimPolygon.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	if(1) {
		
		Vector2f vertices[] = {
			{  0.0f,  0.0f },
			{  1.0f, -1.0f },
			{  2.0f, -1.0f },
			{  1.0f,  0.0f },
			{  2.0f,  0.0f },
			{  1.0f,  1.0f },
			{  2.0f,  1.0f },
			{  1.0f,  2.0f },
			{  0.0f,  1.0f },
			{ -1.0f,  2.0f },
			{ -2.0f,  1.0f },
			{ -1.0f,  1.0f },
			{ -2.0f,  0.0f },
			{ -1.0f,  0.0f },
			{ -2.0f, -1.0f },
			{ -1.0f, -1.0f },
		};
		
		uint32_t indices[128];
		uint32_t num_indices = Polygon<>::triangulate(vertices, TS_COUNTOF(vertices), indices);
		for(uint32_t i = 0; i < num_indices; i += 3) {
			TS_LOGF(Message, "(%u %u %u)\n", indices[i + 0], indices[i + 1], indices[i + 2]);
		}
	}
	
	return 0;
}

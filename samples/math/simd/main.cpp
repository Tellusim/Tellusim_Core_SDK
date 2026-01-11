// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <math/TellusimVector.h>
#include <math/TellusimSimd.h>

/*
 */
using namespace Tellusim;

/*
 */
void print(const char *str, const Tellusim::float64x2_t &v) {
	TS_LOGF(Message, "%s%f %f\n", str, v.get<0>(), v.get<1>());
}

/*
 */
void print(const char *str, const Tellusim::int32x4_t &v) {
	TS_LOGF(Message, "%s%d %d %d %d\n", str, v.get<0>(), v.get<1>(), v.get<2>(), v.get<3>());
}

void print(const char *str, const Tellusim::uint32x4_t &v) {
	TS_LOGF(Message, "%s%u %u %u %u\n", str, v.get<0>(), v.get<1>(), v.get<2>(), v.get<3>());
}

void print(const char *str, const Tellusim::float32x4_t &v) {
	TS_LOGF(Message, "%s%f %f %f %f\n", str, v.get<0>(), v.get<1>(), v.get<2>(), v.get<3>());
}

void print(const char *str, const Tellusim::float64x4_t &v) {
	TS_LOGF(Message, "%s%f %f %f %f\n", str, v.get<0>(), v.get<1>(), v.get<2>(), v.get<3>());
}

/*
 */
void print(const char *str, const Tellusim::int32x8_t &v) {
	TS_LOGF(Message, "%s%d %d %d %d %d %d %d %d\n", str, v.get<0>(), v.get<1>(), v.get<2>(), v.get<3>(), v.get<4>(), v.get<5>(), v.get<6>(), v.get<7>());
}

void print(const char *str, const Tellusim::uint32x8_t &v) {
	TS_LOGF(Message, "%s%u %u %u %u %u %u %u %u\n", str, v.get<0>(), v.get<1>(), v.get<2>(), v.get<3>(), v.get<4>(), v.get<5>(), v.get<6>(), v.get<7>());
}

void print(const char *str, const Tellusim::float32x8_t &v) {
	TS_LOGF(Message, "%s%f %f %f %f %f %f %f %f\n", str, v.get<0>(), v.get<1>(), v.get<2>(), v.get<3>(), v.get<4>(), v.get<5>(), v.get<6>(), v.get<7>());
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	using Tellusim::float32_t;
	using Tellusim::float64_t;
	using Tellusim::int32x4_t;
	using Tellusim::int32x8_t;
	using Tellusim::uint32x4_t;
	using Tellusim::uint32x8_t;
	using Tellusim::float32x4_t;
	using Tellusim::float64x2_t;
	using Tellusim::float64x4_t;
	
	TS_ALIGNAS16 int16_t int16_array[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	TS_ALIGNAS16 int32_t int32_array[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	TS_UNUSED(int16_array);
	TS_UNUSED(int32_array);
	
	TS_ALIGNAS16 uint16_t uint16_array[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	TS_ALIGNAS16 uint32_t uint32_array[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	TS_UNUSED(uint16_array);
	TS_UNUSED(uint32_array);
	
	TS_ALIGNAS32 float32_t float32_array[] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f };
	TS_ALIGNAS32 float64_t float64_array[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };
	TS_UNUSED(float32_array);
	TS_UNUSED(float64_array);
	
	// four elements type conversion
	if(1) {
		
		TS_LOG(Message, "\n");
		
		print("int32x4 from u32x4: ", int32x4_t(uint32x4_t(uint32_array)));
		print("int32x4 from f32x4: ", int32x4_t(float32x4_t(float32_array)));
		print("int32x4 from f64x4: ", int32x4_t(float64x4_t(float64_array)));
		print("int32x4 from i32x4: ", int32x4_t(-int32x4_t(int32_array)));
		print("int32x4 from f32x4: ", int32x4_t(-float32x4_t(float32_array)));
		print("int32x4 from f64x4: ", int32x4_t(-float64x4_t(float64_array)));
		
		TS_LOG(Message, "\n");
		
		print("uint32x4 from i32x4: ", uint32x4_t(int32x4_t(int32_array)));
		print("uint32x4 from f32x4: ", uint32x4_t(float32x4_t(float32_array)));
		print("uint32x4 from f64x4: ", uint32x4_t(float64x4_t(float64_array)));
		
		TS_LOG(Message, "\n");
		
		print("float32x4 from i32x4: ", float32x4_t(int32x4_t(int32_array)));
		print("float32x4 from u32x4: ", float32x4_t(uint32x4_t(uint32_array)));
		print("float32x4 from f64x4: ", float32x4_t(float64x4_t(float64_array)));
		print("float32x4 from i32x4: ", float32x4_t(-int32x4_t(int32_array)));
		print("float32x4 from f32x4: ", float32x4_t(-float32x4_t(float32_array)));
		print("float32x4 from f64x4: ", float32x4_t(-float64x4_t(float64_array)));
		
		TS_LOG(Message, "\n");
		
		print("float64x4 from i32x4: ", float64x4_t(int32x4_t(int32_array)));
		print("float64x4 from u32x4: ", float64x4_t(uint32x4_t(uint32_array)));
		print("float64x4 from f32x4: ", float64x4_t(float32x4_t(float32_array)));
		print("float64x4 from i32x4: ", float64x4_t(-int32x4_t(int32_array)));
		print("float64x4 from f32x4: ", float64x4_t(-float32x4_t(float32_array)));
		print("float64x4 from f64x4: ", float64x4_t(-float64x4_t(float64_array)));
	}
	
	// eight elements type conversion
	if(1) {
		
		TS_LOG(Message, "\n");
		
		print("int32x8 from u32x8: ", int32x8_t(uint32x8_t(uint32_array)));
		print("int32x8 from f32x8: ", int32x8_t(float32x8_t(float32_array)));
		print("int32x8 from i32x8: ", int32x8_t(-int32x8_t(int32_array)));
		print("int32x8 from f32x8: ", int32x8_t(-float32x8_t(float32_array)));
		
		TS_LOG(Message, "\n");
		
		print("uint32x8 from i32x8: ", uint32x8_t(int32x8_t(int32_array)));
		print("uint32x8 from f32x8: ", uint32x8_t(float32x8_t(float32_array)));
		
		TS_LOG(Message, "\n");
		
		print("float32x8 from i32x8: ", float32x8_t(int32x8_t(int32_array)));
		print("float32x8 from u32x8: ", float32x8_t(uint32x8_t(uint32_array)));
		print("float32x8 from i32x8: ", float32x8_t(-int32x8_t(int32_array)));
		print("float32x8 from f32x8: ", float32x8_t(-float32x8_t(float32_array)));
	}
	
	// reinterpret cast
	if(1) {
		
		TS_LOG(Message, "\n");
		
		print(" int32x4 as u32x4: ", int32x4_t(int32_array).asu32x4().asi32x4());
		print(" int32x4 as f32x8: ", int32x4_t(int32_array).asf32x4().asi32x4());
		
		print("uint32x4 as i32x4: ", uint32x4_t(uint32_array).asi32x4().asu32x4());
		print("uint32x4 as u32x4: ", uint32x4_t(uint32_array).asf32x4().asu32x4());
		
		TS_LOG(Message, "\n");
		
		print(" int32x8 as u32x8: ", int32x8_t(int32_array).asu32x8().asi32x8());
		print(" int32x8 as f32x8: ", int32x8_t(int32_array).asf32x8().asi32x8());
		
		print("uint32x8 as i32x8: ", uint32x8_t(uint32_array).asi32x8().asu32x8());
		print("uint32x8 as f32x8: ", uint32x8_t(uint32_array).asf32x8().asu32x8());
		
		TS_LOG(Message, "\n");
		
		print(" int32x4 as f32x4: ", int32x4_t((int32_t)Onef32).asf32x4());
		print("uint32x4 as f32x4: ", uint32x4_t(Onef32).asf32x4());
		
		TS_LOG(Message, "\n");
		
		print(" int32x8 as f32x8: ", int32x8_t((int32_t)Onef32).asf32x8());
		print("uint32x8 as f32x8: ", uint32x8_t(Onef32).asf32x8());
	}
	
	// set elements
	if(1) {
		
		TS_LOG(Message, "\n");
		
		int32x4_t int32x4;
		int32x4.set<0>(1); int32x4.set<1>(2); int32x4.set<2>(3); int32x4.set<3>(4);
		print(" int32x4: ", int32x4);
		
		uint32x4_t uint32x4;
		uint32x4.set<0>(1); uint32x4.set<1>(2); uint32x4.set<2>(3); uint32x4.set<3>(4);
		print("uint32x4: ", uint32x4);
		
		int32x8_t int32x8;
		int32x8.set<0>(1); int32x8.set<1>(2); int32x8.set<2>(3); int32x8.set<3>(4);
		int32x8.set<4>(5); int32x8.set<5>(6); int32x8.set<6>(7); int32x8.set<7>(8);
		print(" int32x8: ", int32x8);
		
		uint32x8_t uint32x8;
		uint32x8.set<0>(1); uint32x8.set<1>(2); uint32x8.set<2>(3); uint32x8.set<3>(4);
		uint32x8.set<4>(5); uint32x8.set<5>(6); uint32x8.set<6>(7); uint32x8.set<7>(8);
		print("uint32x8: ", uint32x8);
		
		TS_LOG(Message, "\n");
		
		float64x2_t float64x2;
		float64x2.set<0>(1.0); float64x2.set<1>(2.0);
		print("float64x2: ", float64x2);
		
		float32x4_t float32x4;
		float32x4.set<0>(1.0f); float32x4.set<1>(2.0f); float32x4.set<2>(3.0f); float32x4.set<3>(4.0f);
		print("float32x4: ", float32x4);
		
		float64x4_t float64x4;
		float64x4.set<0>(1.0); float64x4.set<1>(2.0); float64x4.set<2>(3.0); float64x4.set<3>(4.0);
		print("float64x4: ", float64x4);
		
		float32x8_t float32x8;
		float32x8.set<0>(1.0f); float32x8.set<1>(2.0f); float32x8.set<2>(3.0f); float32x8.set<3>(4.0f);
		float32x8.set<4>(5.0f); float32x8.set<5>(6.0f); float32x8.set<6>(7.0f); float32x8.set<7>(8.0f);
		print("float32x8: ", float32x8);
		
		TS_LOG(Message, "\n");
	}
	
	// get elements
	if(1) {
		
		TS_LOG(Message, "\n");
		
		print(" int32x4: ", int32x4_t(int32_array).get4<0>());
		print(" int32x4: ", int32x4_t(int32_array).get4<1>());
		print(" int32x4: ", int32x4_t(int32_array).get4<2>());
		print(" int32x4: ", int32x4_t(int32_array).get4<3>());
		
		print("uint32x4: ", uint32x4_t(uint32_array).get4<0>());
		print("uint32x4: ", uint32x4_t(uint32_array).get4<1>());
		print("uint32x4: ", uint32x4_t(uint32_array).get4<2>());
		print("uint32x4: ", uint32x4_t(uint32_array).get4<3>());
		
		TS_LOG(Message, "\n");
		
		print(" int32x8: ", int32x8_t(int32_array).get8<0>());
		print(" int32x8: ", int32x8_t(int32_array).get8<1>());
		print(" int32x8: ", int32x8_t(int32_array).get8<2>());
		print(" int32x8: ", int32x8_t(int32_array).get8<3>());
		print(" int32x8: ", int32x8_t(int32_array).get8<4>());
		print(" int32x8: ", int32x8_t(int32_array).get8<5>());
		print(" int32x8: ", int32x8_t(int32_array).get8<6>());
		print(" int32x8: ", int32x8_t(int32_array).get8<7>());
		
		print("uint32x8: ", uint32x8_t(uint32_array).get8<0>());
		print("uint32x8: ", uint32x8_t(uint32_array).get8<1>());
		print("uint32x8: ", uint32x8_t(uint32_array).get8<2>());
		print("uint32x8: ", uint32x8_t(uint32_array).get8<3>());
		print("uint32x8: ", uint32x8_t(uint32_array).get8<4>());
		print("uint32x8: ", uint32x8_t(uint32_array).get8<5>());
		print("uint32x8: ", uint32x8_t(uint32_array).get8<6>());
		print("uint32x8: ", uint32x8_t(uint32_array).get8<7>());
		
		TS_LOG(Message, "\n");
		
		print("float64x2: ", float64x2_t(float64_array).get2<0>());
		print("float64x2: ", float64x2_t(float64_array).get2<1>());
		
		TS_LOG(Message, "\n");
		
		print("float32x4: ", float32x4_t(float32_array).get4<0>());
		print("float32x4: ", float32x4_t(float32_array).get4<1>());
		print("float32x4: ", float32x4_t(float32_array).get4<2>());
		print("float32x4: ", float32x4_t(float32_array).get4<3>());
		
		print("float64x4: ", float64x4_t(float64_array).get4<0>());
		print("float64x4: ", float64x4_t(float64_array).get4<1>());
		print("float64x4: ", float64x4_t(float64_array).get4<2>());
		print("float64x4: ", float64x4_t(float64_array).get4<3>());
		
		TS_LOG(Message, "\n");
		
		print("float32x8: ", float32x8_t(float32_array).get8<0>());
		print("float32x8: ", float32x8_t(float32_array).get8<1>());
		print("float32x8: ", float32x8_t(float32_array).get8<2>());
		print("float32x8: ", float32x8_t(float32_array).get8<3>());
		print("float32x8: ", float32x8_t(float32_array).get8<4>());
		print("float32x8: ", float32x8_t(float32_array).get8<5>());
		print("float32x8: ", float32x8_t(float32_array).get8<6>());
		print("float32x8: ", float32x8_t(float32_array).get8<7>());
	}
	
	// math operators
	if(1) {
		
		TS_LOG(Message, "\n");
		
		print("int32x4 mul: ", int32x4_t(int32_array) * 16);
		print("int32x4 mul: ", int32x4_t(int32_array) * int32x4_t(16));
		print("int32x4 add: ", int32x4_t(int32_array) + 16);
		print("int32x4 add: ", int32x4_t(int32_array) + int32x4_t(16));
		print("int32x4 sub: ", int32x4_t(int32_array) - 16);
		print("int32x4 sub: ", int32x4_t(int32_array) - int32x4_t(16));
		print("int32x4 and: ", int32x4_t(int32_array) & 1);
		print("int32x4 and: ", int32x4_t(int32_array) & int32x4_t(1));
		print("int32x4  or: ", int32x4_t(int32_array) | 2);
		print("int32x4  or: ", int32x4_t(int32_array) | int32x4_t(2));
		print("int32x4 xor: ", int32x4_t(int32_array) ^ 1);
		print("int32x4 xor: ", int32x4_t(int32_array) ^ int32x4_t(1));
		print("int32x4 shl: ", int32x4_t(int32_array) << 4);
		print("int32x4 shr: ", int32x4_t(int32_array) >> 1);
		
		TS_LOG(Message, "\n");
		
		print("uint32x4 mul: ", uint32x4_t(uint32_array) * 16u);
		print("uint32x4 mul: ", uint32x4_t(uint32_array) * uint32x4_t(16u));
		print("uint32x4 add: ", uint32x4_t(uint32_array) + 16u);
		print("uint32x4 add: ", uint32x4_t(uint32_array) + uint32x4_t(16u));
		print("uint32x4 sub: ", uint32x4_t(uint32_array) - 1u);
		print("uint32x4 sub: ", uint32x4_t(uint32_array) - uint32x4_t(1u));
		print("uint32x4 and: ", uint32x4_t(uint32_array) & 1u);
		print("uint32x4 and: ", uint32x4_t(uint32_array) & uint32x4_t(1u));
		print("uint32x4  or: ", uint32x4_t(uint32_array) | 2u);
		print("uint32x4  or: ", uint32x4_t(uint32_array) | uint32x4_t(2u));
		print("uint32x4 xor: ", uint32x4_t(uint32_array) ^ 1u);
		print("uint32x4 xor: ", uint32x4_t(uint32_array) ^ uint32x4_t(1u));
		print("uint32x4 shl: ", uint32x4_t(uint32_array) << 4u);
		print("uint32x4 shr: ", uint32x4_t(uint32_array) >> 1u);
		
		TS_LOG(Message, "\n");
		
		print("float32x4 mul: ", float32x4_t(float32_array) * 16.0f);
		print("float32x4 mul: ", float32x4_t(float32_array) * float32x4_t(16.0f));
		print("float32x4 div: ", float32x4_t(float32_array) / 16.0f);
		print("float32x4 div: ", float32x4_t(float32_array) / float32x4_t(16.0f));
		print("float32x4 add: ", float32x4_t(float32_array) + 16.0f);
		print("float32x4 add: ", float32x4_t(float32_array) + float32x4_t(16.0f));
		print("float32x4 sub: ", float32x4_t(float32_array) - 16.0f);
		print("float32x4 sub: ", float32x4_t(float32_array) - float32x4_t(16.0f));
		
		TS_LOG(Message, "\n");
		
		print("float64x4 mul: ", float64x4_t(float64_array) * 16.0f);
		print("float64x4 mul: ", float64x4_t(float64_array) * float64x4_t(16.0f));
		print("float64x4 div: ", float64x4_t(float64_array) / 16.0f);
		print("float64x4 div: ", float64x4_t(float64_array) / float64x4_t(16.0f));
		print("float64x4 add: ", float64x4_t(float64_array) + 16.0f);
		print("float64x4 add: ", float64x4_t(float64_array) + float64x4_t(16.0f));
		print("float64x4 sub: ", float64x4_t(float64_array) - 16.0f);
		print("float64x4 sub: ", float64x4_t(float64_array) - float64x4_t(16.0f));
	}
	
	// math operators
	if(1) {
		
		TS_LOG(Message, "\n");
		
		print("int32x8 mul: ", int32x8_t(int32_array) * 16);
		print("int32x8 mul: ", int32x8_t(int32_array) * int32x8_t(16));
		print("int32x8 add: ", int32x8_t(int32_array) + 16);
		print("int32x8 add: ", int32x8_t(int32_array) + int32x8_t(16));
		print("int32x8 sub: ", int32x8_t(int32_array) - 16);
		print("int32x8 sub: ", int32x8_t(int32_array) - int32x8_t(16));
		print("int32x8 and: ", int32x8_t(int32_array) & 1);
		print("int32x8 and: ", int32x8_t(int32_array) & int32x8_t(1));
		print("int32x8  or: ", int32x8_t(int32_array) | 2);
		print("int32x8  or: ", int32x8_t(int32_array) | int32x8_t(2));
		print("int32x8 xor: ", int32x8_t(int32_array) ^ 1);
		print("int32x8 xor: ", int32x8_t(int32_array) ^ int32x8_t(1));
		print("int32x8 shl: ", int32x8_t(int32_array) << 4);
		print("int32x8 shr: ", int32x8_t(int32_array) >> 1);
		
		TS_LOG(Message, "\n");
		
		print("uint32x8 mul: ", uint32x8_t(uint32_array) * 16u);
		print("uint32x8 mul: ", uint32x8_t(uint32_array) * uint32x8_t(16u));
		print("uint32x8 add: ", uint32x8_t(uint32_array) + 16u);
		print("uint32x8 add: ", uint32x8_t(uint32_array) + uint32x8_t(16u));
		print("uint32x8 sub: ", uint32x8_t(uint32_array) - 1u);
		print("uint32x8 sub: ", uint32x8_t(uint32_array) - uint32x8_t(1u));
		print("uint32x8 and: ", uint32x8_t(uint32_array) & 1u);
		print("uint32x8 and: ", uint32x8_t(uint32_array) & uint32x8_t(1u));
		print("uint32x8  or: ", uint32x8_t(uint32_array) | 2u);
		print("uint32x8  or: ", uint32x8_t(uint32_array) | uint32x8_t(2u));
		print("uint32x8 xor: ", uint32x8_t(uint32_array) ^ 1u);
		print("uint32x8 xor: ", uint32x8_t(uint32_array) ^ uint32x8_t(1u));
		print("uint32x8 shl: ", uint32x8_t(uint32_array) << 4u);
		print("uint32x8 shr: ", uint32x8_t(uint32_array) >> 1u);
		
		TS_LOG(Message, "\n");
		
		print("float32x8 mul: ", float32x8_t(float32_array) * 16.0f);
		print("float32x8 mul: ", float32x8_t(float32_array) * float32x8_t(16.0f));
		print("float32x8 div: ", float32x8_t(float32_array) / 16.0f);
		print("float32x8 div: ", float32x8_t(float32_array) / float32x8_t(16.0f));
		print("float32x8 add: ", float32x8_t(float32_array) + 16.0f);
		print("float32x8 add: ", float32x8_t(float32_array) + float32x8_t(16.0f));
		print("float32x8 sub: ", float32x8_t(float32_array) - 16.0f);
		print("float32x8 sub: ", float32x8_t(float32_array) - float32x8_t(16.0f));
	}
	
	// math functions
	if(1) {
		
		TS_LOG(Message, "\n");
		
		print("float32x4 sqrt: ", sqrt(float32x4_t(float32_array) * float32x4_t(10.0f)));
		print("float64x4 sqrt: ", sqrt(float64x4_t(float64_array) * float64x4_t(10.0)));
		
		TS_LOG(Message, "\n");
		
		print("float32x8 sqrt: ", sqrt(float32x8_t(float32_array) * float32x8_t(10.0f)));
		
		TS_LOG(Message, "\n");
		
		print("float32x4 rcp: ", rcp(float32x4_t(2.0f, 3.0f, 4.0f, 5.0f)));
		print("float32x4 rcp: ", rcp(float32x4_t(10.0f, 11.0f, 12.0f, 13.0f)));
		print("float32x4 sqrt: ", sqrt(float32x4_t(2.0f, 3.0f, 4.0f, 5.0f)));
		print("float32x4 sqrt: ", sqrt(float32x4_t(10.0f, 11.0f, 12.0f, 13.0f)));
		print("float32x4 rsqrt: ", rsqrt(float32x4_t(2.0f, 3.0f, 4.0f, 5.0f)));
		print("float32x4 rsqrt: ", rsqrt(float32x4_t(10.0f, 11.0f, 12.0f, 13.0f)));
		print("float32x4 abs: ", abs(float32x4_t(-1.0f, -0.0f, 0.0f, 1.0f)));
		print("float32x4 ceil: ", ceil(float32x4_t(-1.0f, 0.3f, 1.0f, 1.4f)));
		print("float32x4 floor: ", floor(float32x4_t(-1.0f, 0.3f, 1.0f, 1.4f)));
		print("float32x4 rsqrtFast: ", rsqrtFast(float32x4_t(2.0f, 3.0f, 4.0f, 5.0f)));
		print("float32x4 rsqrtFast: ", rsqrtFast(float32x4_t(10.0f, 11.0f, 12.0f, 13.0f)));
		print("float32x4 powFast: ", powFast(float32x4_t(0.5f, 1.0f, 2.0f, 4.0f), 2.0f));
		
		TS_LOG(Message, "\n");
		
		print("float32x8 rcp: ", rcp(float32x8_t(2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f)));
		print("float32x8 rcp: ", rcp(float32x8_t(10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f)));
		print("float32x8 sqrt: ", sqrt(float32x8_t(2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f)));
		print("float32x8 sqrt: ", sqrt(float32x8_t(10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f)));
		print("float32x8 rsqrt: ", rsqrt(float32x8_t(2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f)));
		print("float32x8 rsqrt: ", rsqrt(float32x8_t(10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f)));
		print("float32x8 abs: ", abs(float32x8_t(-3.0f, -2.0f, -1.0f, -0.0f, 0.0f, 1.0f, 2.0f, 3.0f)));
		print("float32x8 ceil: ", ceil(float32x8_t(-2.0f, -1.3f, -1.0f, 0.3f, 1.0f, 1.4f, 2.0f, 2.3f)));
		print("float32x8 floor: ", floor(float32x8_t(-2.0f, -1.3f, -1.0f, 0.3f, 1.0f, 1.4f, 2.0f, 2.3f)));
		print("float32x8 rsqrtFast: ", rsqrtFast(float32x8_t(2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f)));
		print("float32x8 rsqrtFast: ", rsqrtFast(float32x8_t(10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f)));
		print("float32x8 powFast: ", powFast(float32x8_t(0.5f, 1.0f, 2.0f, 4.0f, 8.0f, 16.0f, 32.0f, 64.0f), 2.0f));
	}
	
	// swizzles
	if(1) {
		
		TS_LOG(Message, "\n");
		
		print(" int32x4 zwxy: ", int32x4_t(int32_array).zwxy());
		print("uint32x4 zwxy: ", uint32x4_t(uint32_array).zwxy());
		
		print(" int32x4 yxwz: ", int32x4_t(int32_array).yxwz());
		print("uint32x4 yxwz: ", uint32x4_t(uint32_array).yxwz());
		
		TS_LOG(Message, "\n");
		
		print(" int32x8 xyzw10: ", int32x8_t(int32_array).xyzw10());
		print("uint32x8 xyzw10: ", uint32x8_t(uint32_array).xyzw10());
		
		print(" int32x8 zwxy01: ", int32x8_t(int32_array).zwxy01());
		print("uint32x8 zwxy01: ", uint32x8_t(uint32_array).zwxy01());
		
		print(" int32x8 yxwz01: ", int32x8_t(int32_array).yxwz01());
		print("uint32x8 yxwz01: ", uint32x8_t(uint32_array).yxwz01());
		
		TS_LOG(Message, "\n");
		
		print("float32x4 zxyw: ", float32x4_t(float32_array).zxyw());
		print("float64x4 zxyw: ", float64x4_t(float64_array).zxyw());
		
		print("float32x4 zwxy: ", float32x4_t(float32_array).zwxy());
		print("float64x4 zwxy: ", float64x4_t(float64_array).zwxy());
		
		print("float32x4 yxwz: ", float32x4_t(float32_array).yxwz());
		print("float64x4 yxwz: ", float64x4_t(float64_array).yxwz());
		
		TS_LOG(Message, "\n");
		
		print("float32x8 xyzw10: ", float32x8_t(float32_array).xyzw10());
		
		print("float32x8 zwxy01: ", float32x8_t(float32_array).zwxy01());
		
		print("float32x8 yxwz01: ", float32x8_t(float32_array).yxwz01());
		
		TS_LOG(Message, "\n");
		
		print(" int32x8 xyzw0: ", int32x8_t(int32_array).xyzw0());
		
		print("uint32x8 xyzw0: ", uint32x8_t(uint32_array).xyzw0());
		
		print(" int32x8 xyzw1: ", int32x8_t(int32_array).xyzw1());
		
		print("uint32x8 xyzw1: ", uint32x8_t(uint32_array).xyzw1());
		
		TS_LOG(Message, "\n");
		
		print("float32x8 xyzw0: ", float32x8_t(float32_array).xyzw0());
		
		print("float32x8 xyzw1: ", float32x8_t(float32_array).xyzw1());
		
		TS_LOG(Message, "\n");
		
		print("float64x4 xy: ", float64x4_t(float64_array).xy());
		print("float64x4 zw: ", float64x4_t(float64_array).zw());
		
		print("float64x2 yx: ", float64x2_t(float64_array).yx());
	}
	
	// sum components
	if(1) {
		
		TS_LOG(Message, "\n");
		
		TS_LOGF(Message, " int32x4: %d\n", int32x4_t(int32_array).sum());
		TS_LOGF(Message, "uint32x4: %d\n", uint32x4_t(uint32_array).sum());
		
		TS_LOG(Message, "\n");
		
		TS_LOGF(Message, " int32x8: %d\n", int32x8_t(int32_array).sum());
		TS_LOGF(Message, "uint32x8: %d\n", uint32x8_t(uint32_array).sum());
		
		TS_LOG(Message, "\n");
		
		TS_LOGF(Message, "float64x2: %f\n", float64x2_t(float64_array).sum());
		
		TS_LOGF(Message, "float32x4: %f\n", float32x4_t(float32_array).sum());
		TS_LOGF(Message, "float64x4: %f\n", float64x4_t(float64_array).sum());
		
		TS_LOGF(Message, "float32x8: %f\n", float32x8_t(float32_array).sum());
	}
	
	// comparison operators
	if(1) {
		
		TS_LOG(Message, "\n");
		
		TS_LOGF(Message, "float64x2 op<:  0x%02x\n", float64x2_t(float64_array) <  float64x2_t(2.0f));
		TS_LOGF(Message, "float64x2 op>:  0x%02x\n", float64x2_t(float64_array) >  float64x2_t(2.0f));
		TS_LOGF(Message, "float64x2 op<=: 0x%02x\n", float64x2_t(float64_array) <= float64x2_t(2.0f));
		TS_LOGF(Message, "float64x2 op>=: 0x%02x\n", float64x2_t(float64_array) <= float64x2_t(2.0f));
		TS_LOGF(Message, "float64x2 op==: 0x%02x\n", float64x2_t(float64_array) == float64x2_t(2.0f));
		TS_LOGF(Message, "float64x2 op!=: 0x%02x\n", float64x2_t(float64_array) != float64x2_t(2.0f));
		
		TS_LOG(Message, "\n");
		
		TS_LOGF(Message, "float32x4 op<:  0x%02x\n", float32x4_t(float32_array) <  float32x4_t(2.0f));
		TS_LOGF(Message, "float64x4 op<:  0x%02x\n", float64x4_t(float64_array) <  float64x4_t(2.0f));
		TS_LOGF(Message, "float32x4 op>:  0x%02x\n", float32x4_t(float32_array) >  float32x4_t(2.0f));
		TS_LOGF(Message, "float64x4 op>:  0x%02x\n", float64x4_t(float64_array) >  float64x4_t(2.0f));
		TS_LOGF(Message, "float32x4 op<=: 0x%02x\n", float32x4_t(float32_array) <= float32x4_t(2.0f));
		TS_LOGF(Message, "float64x4 op<=: 0x%02x\n", float64x4_t(float64_array) <= float64x4_t(2.0f));
		TS_LOGF(Message, "float32x4 op>=: 0x%02x\n", float32x4_t(float32_array) >= float32x4_t(2.0f));
		TS_LOGF(Message, "float64x4 op>=: 0x%02x\n", float64x4_t(float64_array) >= float64x4_t(2.0f));
		TS_LOGF(Message, "float32x4 op==: 0x%02x\n", float32x4_t(float32_array) == float32x4_t(2.0f));
		TS_LOGF(Message, "float64x4 op==: 0x%02x\n", float64x4_t(float64_array) == float64x4_t(2.0f));
		TS_LOGF(Message, "float32x4 op!=: 0x%02x\n", float32x4_t(float32_array) != float32x4_t(2.0f));
		TS_LOGF(Message, "float64x4 op!=: 0x%02x\n", float64x4_t(float64_array) != float64x4_t(2.0f));
		
		TS_LOG(Message, "\n");
		
		TS_LOGF(Message, "float32x8 op<:  0x%02x\n", float32x8_t(float32_array) <  float32x8_t(2.0f));
		TS_LOGF(Message, "float32x8 op>:  0x%02x\n", float32x8_t(float32_array) >  float32x8_t(2.0f));
		TS_LOGF(Message, "float32x8 op<=: 0x%02x\n", float32x8_t(float32_array) <= float32x8_t(2.0f));
		TS_LOGF(Message, "float32x8 op>=: 0x%02x\n", float32x8_t(float32_array) >= float32x8_t(2.0f));
		TS_LOGF(Message, "float32x8 op==: 0x%02x\n", float32x8_t(float32_array) == float32x8_t(2.0f));
		TS_LOGF(Message, "float32x8 op!=: 0x%02x\n", float32x8_t(float32_array) != float32x8_t(2.0f));
	}
	
	// select functions
	if(1) {
		
		TS_LOG(Message, "\n");
		
		print(" int32x8 select: ", select(int32x8_t(int32_array), -int32x8_t(int32_array), int32x8_t((int32_t)0)));
		print(" int32x8 select: ", select(int32x8_t(int32_array), -int32x8_t(int32_array), int32x8_t(1)));
		print(" int32x8 select: ", select(int32x8_t(int32_array), -int32x8_t(int32_array), int32x8_t(1, -1, 1, -1, 1, -1, 1, -1)));
		print(" int32x8 select: ", select(int32x8_t(int32_array), -int32x8_t(int32_array), int32x8_t(-1)));
		
		TS_LOG(Message, "\n");
		
		print(" int32x4 select: ", select(int32x4_t(int32_array), -int32x4_t(int32_array), int32x4_t((int32_t)0)));
		print(" int32x4 select: ", select(int32x4_t(int32_array), -int32x4_t(int32_array), int32x4_t(1)));
		print(" int32x4 select: ", select(int32x4_t(int32_array), -int32x4_t(int32_array), int32x4_t(1, -1, 1, -1)));
		print(" int32x4 select: ", select(int32x4_t(int32_array), -int32x4_t(int32_array), int32x4_t(-1)));
		
		TS_LOG(Message, "\n");
		
		print("float64x2 select: ", select(float64x2_t(float64_array), -float64x2_t(float64_array), float64x2_t(0.0f)));
		print("float64x2 select: ", select(float64x2_t(float64_array), -float64x2_t(float64_array), float64x2_t(1.0f)));
		print("float64x2 select: ", select(float64x2_t(float64_array), -float64x2_t(float64_array), float64x2_t(1.0f, -1.0f)));
		print("float64x2 select: ", select(float64x2_t(float64_array), -float64x2_t(float64_array), float64x2_t(-1.0f)));
		
		TS_LOG(Message, "\n");
		
		print("float32x4 select: ", select(float32x4_t(float32_array), -float32x4_t(float32_array), float32x4_t(0.0f)));
		print("float64x4 select: ", select(float64x4_t(float64_array), -float64x4_t(float64_array), float64x4_t(0.0f)));
		print("float32x4 select: ", select(float32x4_t(float32_array), -float32x4_t(float32_array), float32x4_t(1.0f)));
		print("float64x4 select: ", select(float64x4_t(float64_array), -float64x4_t(float64_array), float64x4_t(1.0f)));
		print("float32x4 select: ", select(float32x4_t(float32_array), -float32x4_t(float32_array), float32x4_t(1.0f, -1.0f, 1.0f, -1.0f)));
		print("float64x4 select: ", select(float64x4_t(float64_array), -float64x4_t(float64_array), float64x4_t(1.0f, -1.0f, 1.0f, -1.0f)));
		print("float32x4 select: ", select(float32x4_t(float32_array), -float32x4_t(float32_array), float32x4_t(-1.0f)));
		print("float64x4 select: ", select(float64x4_t(float64_array), -float64x4_t(float64_array), float64x4_t(-1.0f)));
		
		TS_LOG(Message, "\n");
		
		print("float32x8 select: ", select(float32x8_t(float32_array), -float32x8_t(float32_array), float32x8_t(0.0f)));
		print("float32x8 select: ", select(float32x8_t(float32_array), -float32x8_t(float32_array), float32x8_t(1.0f)));
		print("float32x8 select: ", select(float32x8_t(float32_array), -float32x8_t(float32_array), float32x8_t(1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f)));
		print("float32x8 select: ", select(float32x8_t(float32_array), -float32x8_t(float32_array), float32x8_t(-1.0f)));
	}
	
	{
		TS_LOG(Message, "\n");
		
		using Vector4x4f = Vector4<float32x4_t>;
		
		Vector4x4f a = Vector4x4f(float32x4_t(1.0f, 2.0f, 3.0f, 4.0f));
		Vector4x4f b = Vector4x4f(float32x4_t(1.0f), float32x4_t(2.0f), float32x4_t(3.0f), float32x4_t(4.0f));
		Vector4x4f c = a + normalize(b * float32x4_t(2.0f, 3.0f, 4.0f, 5.0f));
		
		print("float32x4_t x: ", c.x);
		print("float32x4_t y: ", c.y);
		print("float32x4_t z: ", c.z);
		print("float32x4_t w: ", c.w);
	}
	
	return 0;
}

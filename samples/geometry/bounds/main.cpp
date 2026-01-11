// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <geometry/TellusimBounds.h>

/*
 */
using namespace Tellusim;

/*
 */
template <class Type> void print4(const char *str, const Type &v) {
	TS_LOGF(Message, "%s%f %f %f %f\n", str, v.x, v.y, v.z, v.w);
}

template <class Type> void print(const char *str, const BoundRect<Type> &br) {
	TS_LOGF(Message, "%s%f %f - %f %f\n", str, br.min.x, br.min.y, br.max.x, br.max.y);
}

template <class Type> void print(const char *str, const BoundCircle<Type> &bc) {
	TS_LOGF(Message, "%s%f %f - %f\n", str, bc.center.x, bc.center.y, bc.radius);
}

template <class Type> void print(const char *str, const BoundBox<Type> &bb) {
	TS_LOGF(Message, "%s%f %f %f - %f %f %f\n", str, bb.min.x, bb.min.y, bb.min.z, bb.max.x, bb.max.y, bb.max.z);
}

template <class Type> void print(const char *str, const BoundSphere<Type> &bs) {
	TS_LOGF(Message, "%s%f %f %f - %f\n", str, bs.center.x, bs.center.y, bs.center.z, bs.radius);
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// bound rect transformation
	if(1) {
		
		TS_LOG(Message, "\n");
		
		using Vector2 = Tellusim::Vector2<float32_t>;
		using Matrix4x4 = Tellusim::Matrix4x4<float32_t>;
		
		BoundRect<float32_t> br(Vector2(-1.0f), Vector2(1.0));
		
		print("br ", br);
		print("br ", (Matrix4x4::rotateZ(45.0f) * Matrix4x4::translate(1.0f, 0.0f, 0.0f)) * br);
	}
	
	// bound circle transformation
	if(1) {
		
		TS_LOG(Message, "\n");
		
		using Vector2 = Tellusim::Vector2<float32_t>;
		using Matrix4x4 = Tellusim::Matrix4x4<float32_t>;
		
		BoundCircle<float32_t> bc(Vector2(0.0f), 1.0);
		
		print("bc ", bc);
		print("bc ", (Matrix4x4::rotateZ(45.0f) * Matrix4x4::translate(1.0f, 0.0f, 0.0f)) * bc);
	}
	
	// bound box transformation
	if(1) {
		
		TS_LOG(Message, "\n");
		
		using Vector3 = Tellusim::Vector3<float32_t>;
		using Matrix4x4 = Tellusim::Matrix4x4<float32_t>;
		
		BoundBox<float32_t> bb(Vector3(-1.0f), Vector3(1.0));
		
		print("bb ", bb);
		print("bb ", (Matrix4x4::rotateZ(45.0f) * Matrix4x4::translate(1.0f, 0.0f, 0.0f)) * bb);
	}
	
	// bound sphere transformation
	if(1) {
		
		TS_LOG(Message, "\n");
		
		using Vector3 = Tellusim::Vector3<float32_t>;
		using Matrix4x4 = Tellusim::Matrix4x4<float32_t>;
		
		BoundSphere<float32_t> bs(Vector3(0.0f), 1.0);
		
		print("bs ", bs);
		print("bs ", (Matrix4x4::rotateZ(45.0f) * Matrix4x4::translate(1.0f, 0.0f, 0.0f)) * bs);
	}
	
	// bound box float32_t inside
	if(1) {
		
		TS_LOG(Message, "\n");
		
		using Vector3 = Tellusim::Vector3<float32_t>;
		
		BoundBox<float32_t> bb;
		bb.set(Vector3(0.0f), Vector3(0.1f));
		bb.expand(Vector3(1.0f));
		
		TS_LOGF(Message, "bb32 valid 0x%02x\n", bb.isValid());
		TS_LOGF(Message, "bb32 point 0x%02x 0x%02x\n", bb.inside(Vector3(0.5f)), bb.inside(Vector3(2.0f)));
		TS_LOGF(Message, "bb32 bb bs 0x%02x 0x%02x\n", bb.inside(Vector3(0.5f), Vector3(0.6f)), bb.inside(Vector3(0.5f), 0.5f));
	}
	
	// bound box float64_t inside
	if(1) {
		
		TS_LOG(Message, "\n");
		
		using Vector3 = Tellusim::Vector3<float64_t>;
		
		BoundBox<float64_t> bb;
		bb.set(Vector3(0.0f), Vector3(0.1f));
		bb.expand(Vector3(1.0f));
		
		TS_LOGF(Message, "bb64 valid 0x%02x\n", bb.isValid());
		TS_LOGF(Message, "bb64 point 0x%02x 0x%02x\n", bb.inside(Vector3(0.5f)), bb.inside(Vector3(2.0f)));
		TS_LOGF(Message, "bb64 bb bs 0x%02x 0x%02x\n", bb.inside(Vector3(0.5f), Vector3(0.6f)), bb.inside(Vector3(0.5f), 0.5f));
	}
	
	// bound sphere float32_t inside
	if(1) {
		
		TS_LOG(Message, "\n");
		
		using Vector3 = Tellusim::Vector3<float32_t>;
		
		BoundSphere<float32_t> bs;
		bs.set(Vector3(0.0f), 1.0f);
		
		bs.expand(Vector3(1.0f));
		bs.expand(Vector3(-1.0f));
		bs.expand(Vector3(0.0f), Vector3(0.0f));
		bs.expand(Vector3(0.0f), 0.1f);
		TS_LOGF(Message, "bs32 expand %f %f %f : %f\n", bs.center.x, bs.center.y, bs.center.z, bs.radius);
		
		TS_LOGF(Message, "bs32 valid 0x%02x\n", bs.isValid());
		TS_LOGF(Message, "bs32 point 0x%02x 0x%02x\n", bs.inside(Vector3(0.5f)), bs.inside(Vector3(2.0f)));
		TS_LOGF(Message, "bs32 bound 0x%02x 0x%02x\n", bs.inside(Vector3(0.5f), Vector3(0.6f)), bs.inside(Vector3(0.5f), 0.1f));
	}
	
	// bound sphere float64_t inside
	if(1) {
		
		TS_LOG(Message, "\n");
		
		using Vector3 = Tellusim::Vector3<float64_t>;
		
		BoundSphere<float64_t> bs;
		bs.set(Vector3(0.0f), 1.0f);
		
		bs.expand(Vector3(1.0f));
		bs.expand(Vector3(-1.0f));
		bs.expand(Vector3(0.0f), Vector3(0.0f));
		bs.expand(Vector3(0.0f), 0.1f);
		TS_LOGF(Message, "bs64 expand %f %f %f : %f\n", bs.center.x, bs.center.y, bs.center.z, bs.radius);
		
		TS_LOGF(Message, "bs64 valid 0x%02x\n", bs.isValid());
		TS_LOGF(Message, "bs64 point 0x%02x 0x%02x\n", bs.inside(Vector3(0.5f)), bs.inside(Vector3(2.0f)));
		TS_LOGF(Message, "bs64 bb bs 0x%02x 0x%02x\n", bs.inside(Vector3(0.5f), Vector3(0.6f)), bs.inside(Vector3(0.5f), 0.1f));
	}
	
	// bound frustum float32_t inside
	if(1) {
		
		TS_LOG(Message, "\n");
		
		using Vector3 = Tellusim::Vector3<float32_t>;
		using Matrix4x4 = Tellusim::Matrix4x4<float32_t>;
		
		BoundFrustum<float32_t> bf;
		bf.set(Matrix4x4::perspective(60.0f, 1.0f, 0.1f, 1000.0f), Matrix4x4::lookAt(Vector3(8.0f), Vector3(0.0f), Vector3(0.0f, 0.0f, 1.0f)));
		
		TS_LOGF(Message, "bf bb32: 0x%02x\n", bf.inside(BoundBox<float32_t>(Vector3(0.0f, 0.0f, -10.0f), Vector3(1.0f, 1.0f, -9.0f))));
		TS_LOGF(Message, "bf bb32: 0x%02x\n", bf.inside(BoundBox<float32_t>(Vector3(0.0f, 0.0f,  10.0f), Vector3(1.0f, 1.0f, 11.0f))));
		
		TS_LOGF(Message, "bf bs32: 0x%02x\n", bf.inside(BoundSphere<float32_t>(Vector3(0.0f, 0.0f, -10.0f), 1.0f)));
		TS_LOGF(Message, "bf bs32: 0x%02x\n", bf.inside(BoundSphere<float32_t>(Vector3(0.0f, 0.0f,  10.0f), 1.0f)));
	}
	
	return 0;
}

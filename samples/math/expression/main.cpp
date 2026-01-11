// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <math/TellusimString.h>
#include <math/TellusimExpression.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	try {
		const char *expression = "31 * 3 + 3";
		TS_LOGF(Message, "%s = %d\n", expression, (int32_t)Expression::getScalari64(expression));
	}
	catch(...) {
		TS_LOG(Error, "can't evaluate expression\n");
	}
	
	try {
		const char *expression = "Vector3f(31.0f) * Vector3f(1.0f, 2.0f, 3.0f) * 3.0f + 3.0f";
		TS_LOGF(Message, "%s = %s\n", expression, toString(Expression::getVector3f(expression)).get());
	}
	catch(...) {
		TS_LOG(Error, "can't evaluate expression\n");
	}
	
	try {
		const char *expression = "vec3(31.0f) * vec3(1.0f, 2.0f, 3.0f) * 3.0f + 3.0f";
		TS_LOGF(Message, "%s = %s\n", expression, toString(Expression::getVector3f(expression, "vec3")).get());
	}
	catch(...) {
		TS_LOG(Error, "can't evaluate expression\n");
	}
	
	try {
		const char *expression = "perspectiveR(60.0f, 1.0f, 0.01f) * rotateX(90.0f)";
		TS_LOGF(Message, "%s = %s\n", expression, toString(Expression::getMatrix4x4f(expression)).get());
	}
	catch(...) {
		TS_LOG(Error, "can't evaluate expression\n");
	}
	
	return 0;
}

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
		class Scope : public Expression::Scope<int64_t> {
			public:
				virtual bool isVariable(const String &name, uint32_t hash) const {
					if(hash == String::hashu32("var")) return true;
					if(hash == String::hashu32("one")) return true;
					return false;
				}
				virtual int64_t getVariable(const String &name, uint32_t hash) const {
					if(hash == String::hashu32("var")) return 31;
					if(hash == String::hashu32("one")) return 1;
					return 0;
				}
				virtual bool isFunction(const String &name, uint32_t hash) const {
					if(hash == String::hashu32("mul")) return true;
					if(hash == String::hashu32("add")) return true;
					return false;
				}
				virtual int64_t getFunction(const String &name, uint32_t hash, const int64_t *args, uint32_t num) const {
					if(hash == String::hashu32("mul") && num == 2) return args[0] * args[1];
					if(hash == String::hashu32("add") && num == 2) return args[0] + args[1];
					return 0;
				}
		};
		Scope scope;
		const char *expression = "mul(var, 3) + add(one, add(one, one))";
		TS_LOGF(Message, "%s = %d\n", expression, (int32_t)Expression::getScalari64(expression, &scope));
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

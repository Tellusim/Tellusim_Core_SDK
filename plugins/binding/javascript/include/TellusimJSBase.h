// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_JS_BASE_H__
#define __TELLUSIM_JS_BASE_H__

#include <emscripten.h>

#include <TellusimBase.h>

/*
 */
#define TS_JSAPI __attribute__ ((visibility("default"))) __attribute__ ((used))

/*
 */
namespace Tellusim {
	
	/*
	 */
	#define TS_JS_DECLARE_BASE(TYPE) \
		TS_JSAPI TYPE *ts ## TYPE ## _new() { return new TYPE(); } \
		TS_JSAPI TYPE *ts ## TYPE ## _copy(const TYPE &self) { return new TYPE(self); } \
		TS_JSAPI void ts ## TYPE ## _delete(TYPE *self) { delete self; }
	
	/*
	 */
	#define TS_JS_DECLARE_SETGET_POD(NAME, TYPE, MEMBER) \
		TS_JSAPI void ts ## NAME ## _set_ ## MEMBER(NAME &self, TYPE MEMBER) { self.MEMBER = MEMBER; } \
		TS_JSAPI TYPE ts ## NAME ## _get_ ## MEMBER(const NAME &self) { return self.MEMBER; }
	
	#define TS_JS_DECLARE_SETGET_POD_SWIZZLE(NAME, TYPE, MEMBER, SWIZZLE) \
		TS_JSAPI void ts ## NAME ## _set_ ## MEMBER(NAME &self, TYPE MEMBER) { self.SWIZZLE = MEMBER; } \
		TS_JSAPI TYPE ts ## NAME ## _get_ ## MEMBER(const NAME &self) { return self.SWIZZLE; }
	
	#define TS_JS_DECLARE_SETGET_CLASS(NAME, TYPE, MEMBER) \
		TS_JSAPI void ts ## NAME ## _set_ ## MEMBER(NAME &self, const TYPE &MEMBER) { self.MEMBER = MEMBER; } \
		TS_JSAPI TYPE *ts ## NAME ## _get_ ## MEMBER(const NAME &self) { return new TYPE(self.MEMBER); }
}

#endif /* __TELLUSIM_JS_BASE_H__ */

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_MATH_EXPRESSION_H__
#define __TELLUSIM_MATH_EXPRESSION_H__

#include <math/TellusimMath.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class String;
	
	/**
	 * Expression utils
	 */
	namespace Expression {
		
		/// expression scope
		template <class Type> class Scope {
				
			public:
				
				virtual ~Scope() { }
				
				/// scope variables
				virtual bool isVariable(const String &name, uint32_t hash) const { return false; }
				virtual Type getVariable(const String &name, uint32_t hash) const { return Type(); }
				
				/// scope functions
				virtual bool isFunction(const String &name, uint32_t hash) const { return false; }
				virtual Type getFunction(const String &name, uint32_t hash, const Type *args, uint32_t num) const { return Type(); }
		};
		
		/// scalar expressions
		TS_API int64_t getScalari64(const char *src);
		TS_API uint64_t getScalaru64(const char *src);
		TS_API float32_t getScalarf32(const char *src);
		TS_API float64_t getScalarf64(const char *src);
		
		/// scalar expressions with scope
		TS_API int64_t getScalari64(const char *src, const Scope<int64_t> *scope);
		TS_API uint64_t getScalaru64(const char *src, const Scope<uint64_t> *scope);
		TS_API float32_t getScalarf32(const char *src, const Scope<float32_t> *scope);
		TS_API float64_t getScalarf64(const char *src, const Scope<float64_t> *scope);
		
		/// vector expressions
		TS_API Vector2f getVector2f(const char *src, const char *type = "Vector2f");
		TS_API Vector3f getVector3f(const char *src, const char *type = "Vector3f");
		TS_API Vector4f getVector4f(const char *src, const char *type = "Vector4f");
		
		/// vector expressions with scope
		TS_API Vector2f getVector2f(const char *src, const Scope<float32_t> *scope, const char *type = "Vector2f");
		TS_API Vector3f getVector3f(const char *src, const Scope<float32_t> *scope, const char *type = "Vector3f");
		TS_API Vector4f getVector4f(const char *src, const Scope<float32_t> *scope, const char *type = "Vector4f");
		
		/// matrix expressions
		TS_API Matrix3x2f getMatrix3x2f(const char *src, const char *type = "Matrix3x2f");
		TS_API Matrix4x3f getMatrix4x3f(const char *src, const char *type = "Matrix4x3f");
		TS_API Matrix4x4f getMatrix4x4f(const char *src, const char *type = "Matrix4x4f");
		
		/// matrix expressions with scope
		TS_API Matrix3x2f getMatrix3x2f(const char *src, const Scope<float32_t> *scope, const char *type = "Matrix3x2f");
		TS_API Matrix4x3f getMatrix4x3f(const char *src, const Scope<float32_t> *scope, const char *type = "Matrix4x3f");
		TS_API Matrix4x4f getMatrix4x4f(const char *src, const Scope<float32_t> *scope, const char *type = "Matrix4x4f");
	}
}

#endif /* __TELLUSIM_MATH_EXPRESSION_H__ */

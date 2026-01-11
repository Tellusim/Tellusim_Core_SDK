// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_SYSTEM_REFLECTION_IMPL_H__
#define __TELLUSIM_PLUGINS_SYSTEM_REFLECTION_IMPL_H__

#include <core/TellusimFunction.h>

#include "TellusimReflection.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	template <class RefType> struct ReflectionType {
		using Type = RefType;
	};
	template <class RefType> struct ReflectionType<RefType&> {
		using Type = RefType;
	};
	template <class RefType> struct ReflectionType<RefType&&> {
		using Type = RefType;
	};
	template <class RefType> struct ReflectionType<const RefType&> {
		using Type = RefType;
	};
	template <class RefType> struct ReflectionType<const RefType> {
		using Type = RefType;
	};
	
	/**
	 * Reflection
	 */
	class ReflectionImpl : public Reflection {
			
		public:
			
			/// class constructors
			virtual AutoPtr<Constructor> getConstructor(uint32_t index) const { return AutoPtr<Constructor>((Constructor*)nullptr); }
			
			/// class destructor
			virtual AutoPtr<Destructor> getDestructor() const { return AutoPtr<Destructor>((Destructor*)nullptr); }
			
			/// class functions
			virtual AutoPtr<Function> getFunction(uint32_t index) const { return AutoPtr<Function>((Function*)nullptr); }
	};
	
	/*
	 */
	template <class Class, class Args> class ConstructorImpl : public Reflection::Constructor {
			
		public:
			
			using A0 = typename ReflectionType<typename TypeListAt<0, Args>::Type>::Type;
			using A1 = typename ReflectionType<typename TypeListAt<1, Args>::Type>::Type;
			using A2 = typename ReflectionType<typename TypeListAt<2, Args>::Type>::Type;
			using A3 = typename ReflectionType<typename TypeListAt<3, Args>::Type>::Type;
			using A4 = typename ReflectionType<typename TypeListAt<4, Args>::Type>::Type;
			using A5 = typename ReflectionType<typename TypeListAt<5, Args>::Type>::Type;
			using A6 = typename ReflectionType<typename TypeListAt<6, Args>::Type>::Type;
			using A7 = typename ReflectionType<typename TypeListAt<7, Args>::Type>::Type;
			using A8 = typename ReflectionType<typename TypeListAt<8, Args>::Type>::Type;
			enum { Length = TypeListLength<Args>::Result };
			
			ConstructorImpl() { }
			ConstructorImpl(const A0 &a0) : a0(a0) { }
			ConstructorImpl(const A0 &a0, const A1 &a1) : a0(a0), a1(a1) { }
			ConstructorImpl(const A0 &a0, const A1 &a1, const A2 &a2) : a0(a0), a1(a1), a2(a2) { }
			ConstructorImpl(const A0 &a0, const A1 &a1, const A2 &a2, const A3 &a3) : a0(a0), a1(a1), a2(a2), a3(a3) { }
			ConstructorImpl(const A0 &a0, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4) : a0(a0), a1(a1), a2(a2), a3(a3), a4(a4) { }
			ConstructorImpl(const A0 &a0, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5) : a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5) { }
			ConstructorImpl(const A0 &a0, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6) : a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5), a6(a6) { }
			ConstructorImpl(const A0 &a0, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7) : a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5), a6(a6), a7(a7) { }
			ConstructorImpl(const A0 &a0, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8) : a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5), a6(a6), a7(a7), a8(a8) { }
			
			virtual void *run() {
				return do_run(IntToType<Length>());
			}
			
			virtual uint32_t getNumArgs() const {
				return Length;
			}
			virtual void setArg(uint32_t index, const void *ptr) {
				switch(index) {
					case 0: a0 = *(A0*)ptr; return;
					case 1: a1 = *(A1*)ptr; return;
					case 2: a2 = *(A2*)ptr; return;
					case 3: a3 = *(A3*)ptr; return;
					case 4: a4 = *(A4*)ptr; return;
					case 5: a5 = *(A5*)ptr; return;
					case 6: a6 = *(A6*)ptr; return;
					case 7: a7 = *(A7*)ptr; return;
					case 8: a8 = *(A8*)ptr; return;
				}
			}
			virtual void *getArg(uint32_t index) {
				switch(index) {
					case 0: return &a0;
					case 1: return &a1;
					case 2: return &a2;
					case 3: return &a3;
					case 4: return &a4;
					case 5: return &a5;
					case 6: return &a6;
					case 7: return &a7;
					case 8: return &a8;
				}
				return nullptr;
			}
			
		private:
			
			TS_INLINE Class *do_run(IntToType<0>) { return new Class(); }
			TS_INLINE Class *do_run(IntToType<1>) { return new Class(a0); }
			TS_INLINE Class *do_run(IntToType<2>) { return new Class(a0, a1); }
			TS_INLINE Class *do_run(IntToType<3>) { return new Class(a0, a1, a2); }
			TS_INLINE Class *do_run(IntToType<4>) { return new Class(a0, a1, a2, a3); }
			TS_INLINE Class *do_run(IntToType<5>) { return new Class(a0, a1, a2, a3, a4); }
			TS_INLINE Class *do_run(IntToType<6>) { return new Class(a0, a1, a2, a3, a4, a5); }
			TS_INLINE Class *do_run(IntToType<7>) { return new Class(a0, a1, a2, a3, a4, a5, a6); }
			TS_INLINE Class *do_run(IntToType<8>) { return new Class(a0, a1, a2, a3, a4, a5, a6, a7); }
			TS_INLINE Class *do_run(IntToType<9>) { return new Class(a0, a1, a2, a3, a4, a5, a6, a7, a8); }
			
			A0 a0; A1 a1; A2 a2; A3 a3;
			A4 a4; A5 a5; A6 a6; A7 a7; A8 a8;
	};
	
	/*
	 */
	template <class Class> class DestructorImpl : public Reflection::Destructor {
			
		public:
			
			virtual void run(void *ptr) {
				delete (Class*)ptr;
			}
	};
	
	/*
	 */
	template <class Type> class FunctionImpl : public Reflection::Function {
			
		public:
			
			using Ret = typename ReflectionType<typename FunctionType<Type>::Ret>::Type;
			using Args = typename FunctionType<Type>::Args;
			using Func = typename FunctionType<Type>::Type;
			using Class = typename FunctionType<Type>::Class;
			enum { IsClass = FunctionType<Type>::IsClass };
			
			using A0 = typename ReflectionType<typename TypeListAt<0, Args>::Type>::Type;
			using A1 = typename ReflectionType<typename TypeListAt<1, Args>::Type>::Type;
			using A2 = typename ReflectionType<typename TypeListAt<2, Args>::Type>::Type;
			using A3 = typename ReflectionType<typename TypeListAt<3, Args>::Type>::Type;
			using A4 = typename ReflectionType<typename TypeListAt<4, Args>::Type>::Type;
			using A5 = typename ReflectionType<typename TypeListAt<5, Args>::Type>::Type;
			using A6 = typename ReflectionType<typename TypeListAt<6, Args>::Type>::Type;
			using A7 = typename ReflectionType<typename TypeListAt<7, Args>::Type>::Type;
			using A8 = typename ReflectionType<typename TypeListAt<8, Args>::Type>::Type;
			enum { Length = TypeListLength<Args>::Result };
			
			FunctionImpl(const Func &func) : func(func) { }
			FunctionImpl(const Func &func, const A0 &a0) : func(func), a0(a0) { }
			FunctionImpl(const Func &func, const A0 &a0, const A1 &a1) : func(func), a0(a0), a1(a1) { }
			FunctionImpl(const Func &func, const A0 &a0, const A1 &a1, const A2 &a2) : func(func), a0(a0), a1(a1), a2(a2) { }
			FunctionImpl(const Func &func, const A0 &a0, const A1 &a1, const A2 &a2, const A3 &a3) : func(func), a0(a0), a1(a1), a2(a2), a3(a3) { }
			FunctionImpl(const Func &func, const A0 &a0, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4) : func(func), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4) { }
			FunctionImpl(const Func &func, const A0 &a0, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5) : func(func), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5) { }
			FunctionImpl(const Func &func, const A0 &a0, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6) : func(func), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5), a6(a6) { }
			FunctionImpl(const Func &func, const A0 &a0, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7) : func(func), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5), a6(a6), a7(a7) { }
			FunctionImpl(const Func &func, const A0 &a0, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8) : func(func), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5), a6(a6), a7(a7), a8(a8) { }
			
			virtual void run(void *ptr) {
				do_run((Class*)ptr, IntToType<IsClass>(), IntToType<Length>());
			}
			
			virtual uint32_t getNumArgs() const {
				return Length;
			}
			virtual void setArg(uint32_t index, const void *ptr) {
				switch(index) {
					case 0: a0 = *(A0*)ptr; return;
					case 1: a1 = *(A1*)ptr; return;
					case 2: a2 = *(A2*)ptr; return;
					case 3: a3 = *(A3*)ptr; return;
					case 4: a4 = *(A4*)ptr; return;
					case 5: a5 = *(A5*)ptr; return;
					case 6: a6 = *(A6*)ptr; return;
					case 7: a7 = *(A7*)ptr; return;
					case 8: a8 = *(A8*)ptr; return;
				}
			}
			virtual void *getArg(uint32_t index) {
				switch(index) {
					case 0: return &a0;
					case 1: return &a1;
					case 2: return &a2;
					case 3: return &a3;
					case 4: return &a4;
					case 5: return &a5;
					case 6: return &a6;
					case 7: return &a7;
					case 8: return &a8;
				}
				return nullptr;
			}
			
			virtual void *getRet() {
				return &ret;
			}
			
		private:
			
			TS_INLINE void do_run(Class *ptr, IntToType<0>, IntToType<0>) { ret = func(); }
			TS_INLINE void do_run(Class *ptr, IntToType<0>, IntToType<1>) { ret = func(a0); }
			TS_INLINE void do_run(Class *ptr, IntToType<0>, IntToType<2>) { ret = func(a0, a1); }
			TS_INLINE void do_run(Class *ptr, IntToType<0>, IntToType<3>) { ret = func(a0, a1, a2); }
			TS_INLINE void do_run(Class *ptr, IntToType<0>, IntToType<4>) { ret = func(a0, a1, a2, a3); }
			TS_INLINE void do_run(Class *ptr, IntToType<0>, IntToType<5>) { ret = func(a0, a1, a2, a3, a4); }
			TS_INLINE void do_run(Class *ptr, IntToType<0>, IntToType<6>) { ret = func(a0, a1, a2, a3, a4, a5); }
			TS_INLINE void do_run(Class *ptr, IntToType<0>, IntToType<7>) { ret = func(a0, a1, a2, a3, a4, a5, a6); }
			TS_INLINE void do_run(Class *ptr, IntToType<0>, IntToType<8>) { ret = func(a0, a1, a2, a3, a4, a5, a6, a7); }
			TS_INLINE void do_run(Class *ptr, IntToType<0>, IntToType<9>) { ret = func(a0, a1, a2, a3, a4, a5, a6, a7, a8); }
			
			TS_INLINE void do_run(Class *ptr, IntToType<1>, IntToType<0>) { ret = (ptr->*func)(); }
			TS_INLINE void do_run(Class *ptr, IntToType<1>, IntToType<1>) { ret = (ptr->*func)(a0); }
			TS_INLINE void do_run(Class *ptr, IntToType<1>, IntToType<2>) { ret = (ptr->*func)(a0, a1); }
			TS_INLINE void do_run(Class *ptr, IntToType<1>, IntToType<3>) { ret = (ptr->*func)(a0, a1, a2); }
			TS_INLINE void do_run(Class *ptr, IntToType<1>, IntToType<4>) { ret = (ptr->*func)(a0, a1, a2, a3); }
			TS_INLINE void do_run(Class *ptr, IntToType<1>, IntToType<5>) { ret = (ptr->*func)(a0, a1, a2, a3, a4); }
			TS_INLINE void do_run(Class *ptr, IntToType<1>, IntToType<6>) { ret = (ptr->*func)(a0, a1, a2, a3, a4, a5); }
			TS_INLINE void do_run(Class *ptr, IntToType<1>, IntToType<7>) { ret = (ptr->*func)(a0, a1, a2, a3, a4, a5, a6); }
			TS_INLINE void do_run(Class *ptr, IntToType<1>, IntToType<8>) { ret = (ptr->*func)(a0, a1, a2, a3, a4, a5, a6, a7); }
			TS_INLINE void do_run(Class *ptr, IntToType<1>, IntToType<9>) { ret = (ptr->*func)(a0, a1, a2, a3, a4, a5, a6, a7, a8); }
			
			Func func;
			A0 a0; A1 a1; A2 a2; A3 a3;
			A4 a4; A5 a5; A6 a6; A7 a7; A8 a8;
			Ret ret;
	};
	
	/*
	 */
	template <class Type> class FunctionVoidImpl : public Reflection::Function {
			
		public:
			
			using Args = typename FunctionType<Type>::Args;
			using Func = typename FunctionType<Type>::Type;
			using Class = typename FunctionType<Type>::Class;
			enum { IsClass = FunctionType<Type>::IsClass };
			
			using A0 = typename ReflectionType<typename TypeListAt<0, Args>::Type>::Type;
			using A1 = typename ReflectionType<typename TypeListAt<1, Args>::Type>::Type;
			using A2 = typename ReflectionType<typename TypeListAt<2, Args>::Type>::Type;
			using A3 = typename ReflectionType<typename TypeListAt<3, Args>::Type>::Type;
			using A4 = typename ReflectionType<typename TypeListAt<4, Args>::Type>::Type;
			using A5 = typename ReflectionType<typename TypeListAt<5, Args>::Type>::Type;
			using A6 = typename ReflectionType<typename TypeListAt<6, Args>::Type>::Type;
			using A7 = typename ReflectionType<typename TypeListAt<7, Args>::Type>::Type;
			using A8 = typename ReflectionType<typename TypeListAt<8, Args>::Type>::Type;
			enum { Length = TypeListLength<Args>::Result };
			
			FunctionVoidImpl(const Func &func) : func(func) { }
			FunctionVoidImpl(const Func &func, const A0 &a0) : func(func), a0(a0) { }
			FunctionVoidImpl(const Func &func, const A0 &a0, const A1 &a1) : func(func), a0(a0), a1(a1) { }
			FunctionVoidImpl(const Func &func, const A0 &a0, const A1 &a1, const A2 &a2) : func(func), a0(a0), a1(a1), a2(a2) { }
			FunctionVoidImpl(const Func &func, const A0 &a0, const A1 &a1, const A2 &a2, const A3 &a3) : func(func), a0(a0), a1(a1), a2(a2), a3(a3) { }
			FunctionVoidImpl(const Func &func, const A0 &a0, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4) : func(func), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4) { }
			FunctionVoidImpl(const Func &func, const A0 &a0, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5) : func(func), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5) { }
			FunctionVoidImpl(const Func &func, const A0 &a0, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6) : func(func), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5), a6(a6) { }
			FunctionVoidImpl(const Func &func, const A0 &a0, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7) : func(func), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5), a6(a6), a7(a7) { }
			FunctionVoidImpl(const Func &func, const A0 &a0, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8) : func(func), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4), a5(a5), a6(a6), a7(a7), a8(a8) { }
			
			virtual void run(void *ptr) {
				do_run((Class*)ptr, IntToType<IsClass>(), IntToType<Length>());
			}
			
			virtual uint32_t getNumArgs() const {
				return Length;
			}
			virtual void setArg(uint32_t index, const void *ptr) {
				switch(index) {
					case 0: a0 = *(A0*)ptr; return;
					case 1: a1 = *(A1*)ptr; return;
					case 2: a2 = *(A2*)ptr; return;
					case 3: a3 = *(A3*)ptr; return;
					case 4: a4 = *(A4*)ptr; return;
					case 5: a5 = *(A5*)ptr; return;
					case 6: a6 = *(A6*)ptr; return;
					case 7: a7 = *(A7*)ptr; return;
					case 8: a8 = *(A8*)ptr; return;
				}
			}
			virtual void *getArg(uint32_t index) {
				switch(index) {
					case 0: return &a0;
					case 1: return &a1;
					case 2: return &a2;
					case 3: return &a3;
					case 4: return &a4;
					case 5: return &a5;
					case 6: return &a6;
					case 7: return &a7;
					case 8: return &a8;
				}
				return nullptr;
			}
			
			virtual void *getRet() {
				return nullptr;
			}
			
		private:
			
			TS_INLINE void do_run(Class *ptr, IntToType<0>, IntToType<0>) { func(); }
			TS_INLINE void do_run(Class *ptr, IntToType<0>, IntToType<1>) { func(a0); }
			TS_INLINE void do_run(Class *ptr, IntToType<0>, IntToType<2>) { func(a0, a1); }
			TS_INLINE void do_run(Class *ptr, IntToType<0>, IntToType<3>) { func(a0, a1, a2); }
			TS_INLINE void do_run(Class *ptr, IntToType<0>, IntToType<4>) { func(a0, a1, a2, a3); }
			TS_INLINE void do_run(Class *ptr, IntToType<0>, IntToType<5>) { func(a0, a1, a2, a3, a4); }
			TS_INLINE void do_run(Class *ptr, IntToType<0>, IntToType<6>) { func(a0, a1, a2, a3, a4, a5); }
			TS_INLINE void do_run(Class *ptr, IntToType<0>, IntToType<7>) { func(a0, a1, a2, a3, a4, a5, a6); }
			TS_INLINE void do_run(Class *ptr, IntToType<0>, IntToType<8>) { func(a0, a1, a2, a3, a4, a5, a6, a7); }
			TS_INLINE void do_run(Class *ptr, IntToType<0>, IntToType<9>) { func(a0, a1, a2, a3, a4, a5, a6, a7, a8); }
			
			TS_INLINE void do_run(Class *ptr, IntToType<1>, IntToType<0>) { (ptr->*func)(); }
			TS_INLINE void do_run(Class *ptr, IntToType<1>, IntToType<1>) { (ptr->*func)(a0); }
			TS_INLINE void do_run(Class *ptr, IntToType<1>, IntToType<2>) { (ptr->*func)(a0, a1); }
			TS_INLINE void do_run(Class *ptr, IntToType<1>, IntToType<3>) { (ptr->*func)(a0, a1, a2); }
			TS_INLINE void do_run(Class *ptr, IntToType<1>, IntToType<4>) { (ptr->*func)(a0, a1, a2, a3); }
			TS_INLINE void do_run(Class *ptr, IntToType<1>, IntToType<5>) { (ptr->*func)(a0, a1, a2, a3, a4); }
			TS_INLINE void do_run(Class *ptr, IntToType<1>, IntToType<6>) { (ptr->*func)(a0, a1, a2, a3, a4, a5); }
			TS_INLINE void do_run(Class *ptr, IntToType<1>, IntToType<7>) { (ptr->*func)(a0, a1, a2, a3, a4, a5, a6); }
			TS_INLINE void do_run(Class *ptr, IntToType<1>, IntToType<8>) { (ptr->*func)(a0, a1, a2, a3, a4, a5, a6, a7); }
			TS_INLINE void do_run(Class *ptr, IntToType<1>, IntToType<9>) { (ptr->*func)(a0, a1, a2, a3, a4, a5, a6, a7, a8); }
			
			Func func;
			A0 a0; A1 a1; A2 a2; A3 a3; A4 a4;
			A5 a5; A6 a6; A7 a7; A8 a8;
	};
}

#endif /* __TELLUSIM_PLUGINS_SYSTEM_REFLECTION_IMPL_H__ */

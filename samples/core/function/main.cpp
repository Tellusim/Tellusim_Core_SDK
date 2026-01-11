// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimFunction.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	if(1) {
		
		TS_LOG(Message, "\n");
		TS_LOG(Message, "Functions:\n");
		
		struct Foo {
			static void func_0() { TS_LOG(Message, "func_0(): called\n"); }
			static int32_t func_1(int32_t a) { TS_LOGF(Message, "func_1(%2d): called\n", a); return a; }
			static int32_t func_2(int32_t a, int32_t b) { TS_LOGF(Message, "func_2(%2d, %2d): called\n", a, b); return a + b; }
		};
		
		Function<void()> func_0(Foo::func_0);
		Function<int32_t(int32_t)> func_1(Foo::func_1, -1);
		Function<int32_t(int32_t, int32_t)> func_2(Foo::func_2, -2, -3);
		
		func_0();
		func_1();
		func_1(1);
		func_2();
		func_2(2);
		func_2(2, 3);
		
		auto f0 = func_0;
		auto f1 = func_1;
		auto f2 = func_2;
		TS_LOGF(Message, "%u %u %u\n", f0 == func_0, f1 == func_1, f2 == func_2);
	}
	
	if(1) {
		
		TS_LOG(Message, "\n");
		TS_LOG(Message, "Lambda functions:\n");
		
		Function<void()> func_0([]() { TS_LOG(Message, "func_0(): called\n"); });
		Function<int32_t(int32_t)> func_1([](int32_t a) -> int32_t { TS_LOGF(Message, "func_1(%2d): called\n", a); return a; }, -1);
		Function<int32_t(int32_t, int32_t)> func_2([](int32_t a, int32_t b) -> int32_t { TS_LOGF(Message, "func_2(%2d, %2d): called\n", a, b); return a + b; }, -2, -3);
		
		func_0();
		func_1();
		func_1(1);
		func_2();
		func_2(2);
		func_2(2, 3);
		
		auto f0 = func_0;
		auto f1 = func_1;
		auto f2 = func_2;
		TS_LOGF(Message, "%u %u %u\n", f0 == func_0, f1 == func_1, f2 == func_2);
	}
	
	if(1) {
		
		TS_LOG(Message, "\n");
		TS_LOG(Message, "Lambda functions with capture:\n");
		
		int32_t capture = 0;
		
		Function<void()> func_0([&]() { TS_LOGF(Message, "func_0(): called %d\n", capture++); });
		Function<int32_t(int32_t)> func_1([&](int32_t a) -> int32_t { TS_LOGF(Message, "func_1(%2d): called %d\n", a, capture++); return a; }, -1);
		Function<int32_t(int32_t, int32_t)> func_2([&](int32_t a, int32_t b) -> int32_t { TS_LOGF(Message, "func_2(%2d, %2d): called %d\n", a, b, capture++); return a + b; }, -2, -3);
		
		func_0();
		func_1();
		func_1(1);
		func_2();
		func_2(2);
		func_2(2, 3);
		
		auto f0 = func_0;
		auto f1 = func_1;
		auto f2 = func_2;
		TS_LOGF(Message, "%u %u %u\n", f0 == func_0, f1 == func_1, f2 == func_2);
	}
	
	if(1) {
		
		TS_LOG(Message, "\n");
		TS_LOG(Message, "Member functions:\n");
		
		struct Foo {
			Foo(int32_t id) : id(id) { }
			void func_0() const { TS_LOGF(Message, "Foo::func_0(): called %d\n", id); }
			int32_t func_1(int32_t a) { TS_LOGF(Message, "Foo::func_1(%2d): called %d\n", a, id); return a; }
			int32_t func_2(int32_t a, int32_t b) { TS_LOGF(Message, "Foo::func_2(%2d, %2d): called %d\n", a, b, id); return a + b; }
			int32_t id;
		};
		
		Foo foo0(0);
		Foo foo1(1);
		Foo foo2(2);
		
		Function<void (Foo::*)() const> func_0(&foo0, &Foo::func_0);
		Function<int32_t (Foo::*)(int32_t)> func_1(&foo1, &Foo::func_1, -1);
		Function<int32_t (Foo::*)(int32_t, int32_t)> func_2(&foo2, &Foo::func_2, -2, -3);
		
		func_0();
		func_1();
		func_1(1);
		func_2();
		func_2(2);
		func_2(2, 3);
		
		auto f0 = func_0;
		auto f1 = func_1;
		auto f2 = func_2;
		TS_LOGF(Message, "%d %d %d\n", f0 == func_0, f1 == func_1, f2 == func_2);
	}
	
	return 0;
}

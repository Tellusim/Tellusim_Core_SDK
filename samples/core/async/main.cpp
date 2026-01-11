// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <core/TellusimAsync.h>
#include <core/TellusimString.h>

/*
 */
#define NUM_THREADS	1024

/*
 */
using namespace Tellusim;

/*
 */
struct Foo {
	Foo() : id(0) { }
	Foo(int32_t id) : id(id) { }
	int32_t id;
};

/*
 */
static volatile uint32_t sum[NUM_THREADS] = {};
static volatile uint32_t counter[NUM_THREADS] = {};

void function(uint32_t value, uint32_t index) {
	volatile uint32_t s = sum[index];
	for(uint32_t i = 0; i < value; i++) s++;
	counter[index]++;
	sum[index] = s;
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	Async async;
	if(!async.init()) return 1;
	
	{
		Async::Task task = async.run([]() -> const char* {
			return "lambda string";
		});
		
		task.wait();
		
		TS_LOGF(Message, "string: %s\n", task.getPtr<const char*>());
	}
	
	{
		Async::Task task = async.run([](int32_t id) -> Foo {
			return Foo(id);
		}, 1);
		
		task.run([](int32_t id) -> Foo* {
			return new Foo(id);
		}, 2);
		
		task.run([](int32_t id) -> const Foo* {
			return new Foo(id);
		}, 3);
		
		task.wait();
		
		TS_LOGF(Message, "1: %u\n", task.get<Foo>(0).id);
		TS_LOGF(Message, "2: %u\n", task.get<Foo>(1).id);
		TS_LOGF(Message, "3: %u\n", task.get<Foo>(2).id);
	}
	
	{
		Async::Task task = async.run([](int32_t a, int32_t b) -> int32_t {
			return a + b;
		}, 1, 2);
		
		task.run([](int32_t a, int32_t b) -> int32_t {
			return a + b;
		}, 3, 4);
		
		task.run([](int32_t a, int32_t b) -> int32_t {
			return a + b;
		}, 5, 6);
		
		task.wait();
		
		TS_LOGF(Message, "1+2: %d\n", task.get<int32_t>(0));
		TS_LOGF(Message, "3+4: %d\n", task.get<int32_t>(1));
		TS_LOGF(Message, "5+6: %d\n", task.get<int32_t>(2));
	}
	
	{
		Async::Task task = async.run([](int32_t a) -> int32_t {
			TS_LOGF(Message, "1: %d\n", a);
			return a + 1;
		}, 1);
		
		task.run([](Async::Task *task) -> int32_t {
			TS_LOGF(Message, "2: %d\n", task->get<int32_t>(0));
			return task->get<int32_t>(0) + 1;
		}, &task);
		
		task.wait();
		
		TS_LOGF(Message, "3: %d\n", task.get<int32_t>(1));
	}
	
	for(uint32_t num = 1; num <= async.getNumThreads(); num++) {
		
		TS_LOG(Message, "\n");
		
		memset((void*)sum, 0, sizeof(sum));
		memset((void*)counter, 0, sizeof(counter));
		
		Async::Task tasks[NUM_THREADS];
		uint64_t init_begin = Time::current();
		for(uint32_t j = 0; j < num; j++) {
			tasks[j] = async.run((uint64_t)(1ull << j));
		}
		
		uint64_t run_begin = Time::current();
		for(uint32_t i = 0; i < 1024 * 16; i++) {
			for(uint32_t j = 0; j < num; j++) {
				tasks[j].run(function, i, j);
			}
		}
		
		uint64_t wait_begin = Time::current();
		for(uint32_t j = 0; j < num; j++) {
			tasks[j].wait();
		}
		
		uint64_t wait_end = Time::current();
		for(uint64_t i = 0; i < num; i++) {
			TS_LOGF(Message, "%u %u\n", sum[i], counter[i]);
		}
		
		TS_LOGF(Message, "init: %s\n", String::fromTime(run_begin - init_begin).get());
		TS_LOGF(Message, " run: %s\n", String::fromTime(wait_begin - run_begin).get());
		TS_LOGF(Message, "wait: %s\n", String::fromTime(wait_end - run_begin).get());
	}
	
	return 0;
}

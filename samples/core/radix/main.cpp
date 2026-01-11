// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimMap.h>
#include <core/TellusimTime.h>
#include <core/TellusimRadix.h>
#include <math/TellusimRandom.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	if(1) {
		
		TS_LOG(Message, "\n");
		
		RadixMap<uint32_t, uint32_t, 32> map;
		
		for(uint32_t i = 8; i < 32; i++) {
			map.append(1 << i, i);
		}
		for(uint32_t i = 0; i < 8; i++) {
			map.append(i, i);
		}
		
		map.remove(1);
		map.remove(3);
		map.remove(1 << 8);
		map.remove(1 << 10);
		
		TS_LOGF(Message, " forward (%u): ", map.size());
		for(auto it = map.begin(); it != map.end(); ++it) {
			Log::printf("%u ", it.get());
		}
		Log::print("\n");
		
		TS_LOGF(Message, "backward (%u): ", map.size());
		for(auto it = map.back(); it != map.end(); --it) {
			Log::printf("%u ", it.get());
		}
		Log::print("\n");
	}
	
	if(1) {
		
		TS_LOG(Message, "\n");
		
		RadixMap<uint64_t, uint64_t, 64> map;
		
		for(uint64_t i = 8; i < 64; i++) {
			map.append((uint64_t)1 << i, i);
		}
		for(uint64_t i = 0; i < 8; i++) {
			map.append(i, i);
		}
		
		map.remove(1);
		map.remove(3);
		map.remove(1 << 8);
		map.remove(1 << 10);
		
		TS_LOGF(Message, " forward (%u): ", map.size());
		for(auto it = map.begin(); it != map.end(); ++it) {
			Log::printf("%u ", (uint32_t)it.get());
		}
		Log::print("\n");
		
		TS_LOGF(Message, "backward (%u): ", map.size());
		for(auto it = map.back(); it != map.end(); --it) {
			Log::printf("%u ", (uint32_t)it.get());
		}
		Log::print("\n");
	}
	
	if(1) {
		
		TS_LOG(Message, "\n");
		TS_LOG(Message, "Map\n");
		
		Map<uint64_t, uint64_t> map;
		
		constexpr uint32_t num = 1024 * 1024;
		constexpr int32_t mask = 0x00ffffff;
		
		uint64_t begin = Time::current();
		for(uint32_t i = 0; i < num; i++) {
			map.append(i, i);
		}
		TS_LOGF(Message, "append inc %u %s %s\n", map.size(), String::fromTime(Time::current() - begin).get(), String::fromBytes(map.memory()).get());
		
		begin = Time::current();
		for(uint32_t i = 0; i < num; i++) {
			map.remove(i);
		}
		TS_LOGF(Message, "remove inc %u %s %s\n", map.size(), String::fromTime(Time::current() - begin).get(), String::fromBytes(map.memory()).get());
		
		begin = Time::current();
		for(uint32_t i = 0; i < num; i++) {
			map.append(num - i);
		}
		TS_LOGF(Message, "append dec %u %s %s\n", map.size(), String::fromTime(Time::current() - begin).get(), String::fromBytes(map.memory()).get());
		
		begin = Time::current();
		for(uint32_t i = 0; i < num; i++) {
			map.remove(num - i);
		}
		TS_LOGF(Message, "remove dec %u %s %s\n", map.size(), String::fromTime(Time::current() - begin).get(), String::fromBytes(map.memory()).get());
		
		Random<> random(0);
		begin = Time::current();
		for(uint32_t i = 0; i < num; i++) {
			map.append(random.geti32(mask));
		}
		TS_LOGF(Message, "append rnd %u %s %s\n", map.size(), String::fromTime(Time::current() - begin).get(), String::fromBytes(map.memory()).get());
		
		random.init(0);
		begin = Time::current();
		for(uint32_t i = 0; i < num; i++) {
			map.remove(random.geti32(mask));
		}
		TS_LOGF(Message, "remove rnd %u %s %s\n", map.size(), String::fromTime(Time::current() - begin).get(), String::fromBytes(map.memory()).get());
		
		random.init(0);
		begin = Time::current();
		for(uint32_t i = 0; i < num; i++) {
			map.append(random.geti32(mask));
			map.remove(random.geti32(mask));
			map.remove(random.geti32(mask));
		}
		TS_LOGF(Message, "update rnd %u %s %s\n", map.size(), String::fromTime(Time::current() - begin).get(), String::fromBytes(map.memory()).get());
	}
	
	if(1) {
		
		TS_LOG(Message, "\n");
		TS_LOG(Message, "RadixMap\n");
		
		RadixMap<uint64_t, uint64_t, 64> map;
		
		constexpr uint32_t num = 1024 * 1024;
		constexpr int32_t mask = 0x00ffffff;
		
		uint64_t begin = Time::current();
		for(uint32_t i = 0; i < num; i++) {
			map.append(i, i);
		}
		TS_LOGF(Message, "append inc %u %s %s\n", map.size(), String::fromTime(Time::current() - begin).get(), String::fromBytes(map.memory()).get());
		
		begin = Time::current();
		for(uint32_t i = 0; i < num; i++) {
			map.remove(i);
		}
		TS_LOGF(Message, "remove inc %u %s %s\n", map.size(), String::fromTime(Time::current() - begin).get(), String::fromBytes(map.memory()).get());
		
		begin = Time::current();
		for(uint32_t i = 0; i < num; i++) {
			map.append(num - i);
		}
		TS_LOGF(Message, "append dec %u %s %s\n", map.size(), String::fromTime(Time::current() - begin).get(), String::fromBytes(map.memory()).get());
		
		begin = Time::current();
		for(uint32_t i = 0; i < num; i++) {
			map.remove(num - i);
		}
		TS_LOGF(Message, "remove dec %u %s %s\n", map.size(), String::fromTime(Time::current() - begin).get(), String::fromBytes(map.memory()).get());
		
		Random<> random(0);
		begin = Time::current();
		for(uint32_t i = 0; i < num; i++) {
			map.append(random.geti32(mask));
		}
		TS_LOGF(Message, "append rnd %u %s %s\n", map.size(), String::fromTime(Time::current() - begin).get(), String::fromBytes(map.memory()).get());
		
		random.init(0);
		begin = Time::current();
		for(uint32_t i = 0; i < num; i++) {
			map.remove(random.geti32(mask));
		}
		TS_LOGF(Message, "remove rnd %u %s %s\n", map.size(), String::fromTime(Time::current() - begin).get(), String::fromBytes(map.memory()).get());
		
		random.init(0);
		begin = Time::current();
		for(uint32_t i = 0; i < num; i++) {
			map.append(random.geti32(mask));
			map.remove(random.geti32(mask));
			map.remove(random.geti32(mask));
		}
		TS_LOGF(Message, "update rnd %u %s %s\n", map.size(), String::fromTime(Time::current() - begin).get(), String::fromBytes(map.memory()).get());
	}
	
	return 0;
}

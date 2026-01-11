// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimSet.h>
#include <core/TellusimMap.h>
#include <core/TellusimString.h>

/*
 */
using namespace Tellusim;

/*
 */
Set<String> create_set() {
	Set<String> set;
	set.append(String("a"));
	set.append(String("b"));
	set.append(String("c"));
	return set;
}

Map<String, String> create_map() {
	Map<String, String> map;
	map.append(String("a"), String("A"));
	map.append(String("b"), String("B"));
	map.append(String("c"), String("C"));
	return map;
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	if(1) {
		
		Set<String> set;
		
		set = create_set();
		set.append(create_set());
		
		set.append(String("5"));
		set.append(String("6"));
		set.append(String("7"));
		set.append(String("8"));
		set.append(String("0"));
		set.append(String("1"));
		set.append(String("2"));
		set.append(String("3"));
		set.append(String("4"));
		
		set.remove(String("5"));
		set.remove(String("1"));
		set.remove(String("8"));
		set.remove(String("7"));
		
		set.append(String("A"));
		set.append(String("Z"));
		set.append(String("W"));
		
		auto copy = set;
		set = copy;
		
		TS_LOGF(Message, " forward (%u): ", set.size());
		for(auto it = set.begin(); it != set.end(); ++it) {
			Log::printf("%s ", it->get());
		}
		Log::printf("\n");
		
		TS_LOGF(Message, "backward (%u): ", set.size());
		for(auto it = set.back(); it != set.end(); --it) {
			Log::printf("%s ", it->get());
		}
		Log::printf("\n");
	}
	
	if(1) {
		
		TS_LOG(Message, "\n");
		
		Map<String, String> map;
		
		map = create_map();
		map.append(create_map());
		
		map.append(String("5"), String("5"));
		map.append(String("6"), String("6"));
		map.append(String("7"), String("7"));
		
		map.remove(String("a"));
		
		auto copy = map;
		map = copy;
		
		TS_LOGF(Message, " forward (%u): ", map.size());
		for(auto it = map.begin(); it != map.end(); ++it) {
			Log::printf("%s(%s) ", it->key.get(), it->data.get());
		}
		Log::printf("\n");
		
		TS_LOGF(Message, "backward (%u): ", map.size());
		for(auto it = map.back(); it != map.end(); --it) {
			Log::printf("%s(%s) ", it->key.get(), it->data.get());
		}
		Log::printf("\n");
	}
	
	return 0;
}

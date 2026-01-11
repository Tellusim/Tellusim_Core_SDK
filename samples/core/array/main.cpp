// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimArray.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// array operations
	if(1) {
		
		Array<int32_t> array({ 0, 1, 2, 3 });
		array.append(Array<int32_t>({ 4, 5, 6, 7 }));
		array.append({ 8, 9, 10, 11 });
		array.append(12);
		array.remove(2, 2);
		for(int32_t i : array) {
			Log::printf("%d ", i);
		}
		Log::printf("\n");
	}
	
	// fast array element removal
	if(1) {
		
		Array<int32_t> array({ 0, 1, 2, 3, 4, 5, 6, 7 });
		array.removeFast(1, 5);
		for(int32_t i : array) {
			Log::printf("%d ", i);
		}
		Log::printf("\n");
	}
	
	// array element insertion
	if(1) {
		
		Array<int32_t> array({ 0, 1, 2, 3, 4, 5, 6, 7 });
		array.insert(1, 8);
		array.insert(3, { 9, 10, 11 });
		array.insert(9, { 12, 13, 14 });
		for(int32_t i : array) {
			Log::printf("%d ", i);
		}
		Log::printf("\n");
	}
	
	// swap arrays
	if(1) {
		TS_LOG(Message, "\n");
		Array<uint32_t> array_0 = { 4, 5, 6, 7 };
		Array<uint32_t> array_1 = { 0, 1, 2, 3 };
		swap(array_0, array_1);
		for(uint32_t i = 0; i < array_0.size(); i++) {
			TS_LOGF(Message, "%u: %u\n", i, array_0[i]);
		}
		for(uint32_t i = 0; i < array_1.size(); i++) {
			TS_LOGF(Message, "%u: %u\n", i, array_1[i]);
		}
	}
		
	return 0;
}

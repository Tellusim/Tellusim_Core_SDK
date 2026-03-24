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
	
	// array element reverse
	if(1) {
		
		TS_LOG(Message, "\n");
		
		Array<int32_t> array({ 0, 1, 2, 3, 4, 5, 6, 7 });
		array.reverse(1, 6);
		for(int32_t i : array) {
			Log::printf("%d ", i);
		}
		Log::printf("\n");
	}
	
	// array range
	if(1) {
		
		TS_LOG(Message, "\n");
		
		Array<int32_t> array;
		for(int32_t i = 0; i < 16; i += 2) {
			array.append(i);
		}
		for(int32_t i = -2; i <= 16; i++) {
			uint32_t prev = array.prevIndex(i);
			uint32_t next = array.nextIndex(i);
			if(prev != Maxu32 && next != Maxu32) TS_LOGF(Message, "%2d: prev: %2d next: %2d\n", i, array[prev], array[next]);
			else if(next != Maxu32) TS_LOGF(Message, "%2d:          next: %2d\n", i, array[next]);
			else if(prev != Maxu32) TS_LOGF(Message, "%2d: prev: %2d\n", i, array[prev]);
		}
	}
	
	// swap arrays
	if(1) {
		
		TS_LOG(Message, "\n");
		
		Array<uint32_t> array_0 = { 4, 5, 6, 7 };
		Array<uint32_t> array_1 = { 0, 1, 2, 3 };
		
		Array<uint32_t>          array_2 = { 4, 5, 6, 7 };
		ArrayStack<uint32_t,  2> array_3 = { 0, 1, 2, 3 };
		
		ArrayStack<uint32_t,  2> array_4 = { 4, 5, 6, 7 };
		Array<uint32_t>          array_5 = { 0, 1, 2, 3 };
		
		Array<uint32_t>          array_6 = { 4, 5, 6, 7 };
		ArrayStack<uint32_t, 16> array_7 = { 0, 1, 2, 3 };
		
		ArrayStack<uint32_t, 16> array_8 = { 4, 5, 6, 7 };
		Array<uint32_t>          array_9 = { 0, 1, 2, 3 };
		
		ArrayStack<uint32_t,  2> array_10 = { 4, 5, 6, 7 };
		ArrayStack<uint32_t,  2> array_11 = { 0, 1, 2, 3 };
		
		ArrayStack<uint32_t,  2> array_12 = { 4, 5, 6, 7 };
		ArrayStack<uint32_t, 16> array_13 = { 0, 1, 2, 3 };
		
		ArrayStack<uint32_t, 16> array_14 = { 4, 5, 6, 7 };
		ArrayStack<uint32_t, 16> array_15 = { 0, 1, 2, 3 };
		
		swap(array_0, array_1);
		swap(array_2, array_3);
		swap(array_4, array_5);
		swap(array_6, array_7);
		swap(array_8, array_9);
		swap(array_10, array_11);
		swap(array_12, array_13);
		swap(array_14, array_15);
		
		for(uint32_t i = 0; i < array_0.size(); i++) {
			TS_LOGF(Message, "%u: %u %u %u %u %u %u %u %u\n", i, array_0[i], array_2[i], array_4[i], array_6[i], array_8[i], array_10[i], array_12[i], array_14[i]);
		}
		for(uint32_t i = 0; i < array_1.size(); i++) {
			TS_LOGF(Message, "%u: %u %u %u %u %u %u %u %u\n", i, array_1[i], array_3[i], array_5[i], array_7[i], array_9[i], array_11[i], array_13[i], array_15[i]);
		}
	}
	
	// move array
	if(1) {
		
		TS_LOG(Message, "\n");
		
		Array<uint32_t> array_0;
		Array<uint32_t> array_1;
		ArrayStack<uint32_t, 32> array_2;
		ArrayStack<uint32_t, 32> array_3;
		ArrayStack<uint32_t,  2> array_4;
		ArrayStack<uint32_t, 16> array_5;
		
		{
			ArrayStack<uint32_t,  2> stack_0 = { 0, 1, 2, 3 };
			ArrayStack<uint32_t, 16> stack_1 = { 0, 1, 2, 3 };
			ArrayStack<uint32_t,  2> stack_2 = { 0, 1, 2, 3 };
			ArrayStack<uint32_t, 16> stack_3 = { 0, 1, 2, 3 };
			Array<uint32_t> stack_4 = { 0, 1, 2, 3 };
			Array<uint32_t> stack_5 = { 0, 1, 2, 3 };
			
			array_0 = move(stack_0);
			array_1 = move(stack_1);
			array_2 = move(stack_2);
			array_3 = move(stack_3);
			array_4 = move(stack_4);
			array_5 = move(stack_5);
			
			stack_0 = { 10, 11, 12, 13 };
			stack_1 = { 10, 11, 12, 13 };
			stack_2 = { 10, 11, 12, 13 };
			stack_3 = { 10, 11, 12, 13 };
			stack_4 = { 10, 11, 12, 13 };
			stack_5 = { 10, 11, 12, 13 };
		}
		
		for(uint32_t i = 0; i < array_0.size(); i++) {
			TS_LOGF(Message, "%u: %u %u %u %u %u %u\n", i, array_0[i], array_1[i], array_2[i], array_3[i], array_4[i], array_5[i]);
		}
	}
		
	return 0;
}

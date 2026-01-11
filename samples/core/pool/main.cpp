// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimPool.h>
#include <core/TellusimArray.h>
#include <math/TellusimRandom.h>

/*
 */
using namespace Tellusim;

/*
 */
template <class Type, class Index> void print(const FixedPool<Type, Index> &pool) {
	TS_LOGF(Message, "%u %u\n", pool.getMemory(), pool.getAllocations());
}

template <uint32_t Alignment> void print(const HeapPool<Alignment> &pool) {
	TS_LOGF(Message, "%u %u %u\n", pool.getMemory(), pool.getAllocations(), pool.getBlocks());
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	constexpr uint32_t size = 1024;
	
	if(1) {
		
		TS_LOG(Message, "\n");
		
		FixedPool<uint32_t, uint8_t> pool(sizeof(uint32_t) * Maxu8);
		for(uint32_t i = 0; i <= Maxu8; i++) {
			if(i < Maxu8 - 1) pool.allocate();
			else TS_LOGF(Message, "%u %u\n", i, pool.allocate());
		}
	}
	
	if(1) {
		
		Random<> random;
		
		TS_LOG(Message, "\n");
		
		FixedPool<uint32_t> pool(size * size);
		
		for(uint32_t i = 0; i < 4; i++) {
			
			TS_LOGF(Message, "Iteration: %u\n", i);
			
			// allocate memory
			Array<uint32_t> allocations;
			for(uint32_t j = 1; j < size; j++) {
				uint32_t offset = pool.allocate();
				allocations.append(offset);
			}
			print(pool);
			
			// free memory
			for(uint32_t j = 0; j < size / 4; j++) {
				uint32_t index = random.geti32() % allocations.size();
				pool.free(allocations[index]);
				allocations[index] = Maxu32;
			}
			print(pool);
			
			// allocate memory
			for(uint32_t j = 1; j < size; j++) {
				uint32_t offset = pool.allocate();
				allocations.append(offset);
			}
			print(pool);
			
			// free memory
			for(uint32_t j = 0; j < allocations.size(); j++) {
				uint32_t i0 = random.geti32() % allocations.size();
				uint32_t i1 = random.geti32() % allocations.size();
				swap(allocations[i0], allocations[i1]);
			}
			for(uint32_t j = 0; j < allocations.size(); j++) {
				pool.free(allocations[j]);
			}
			print(pool);
			
			TS_LOG(Message, "\n");
		}
	}
	
	if(1) {
		
		TS_LOG(Message, "\n");
		
		HeapPool<0> pool(sizeof(uint32_t) * Maxu8);
		for(uint32_t i = 0; i <= Maxu8; i++) {
			if(i < Maxu8 - 1) pool.allocate(4, sizeof(uint32_t));
			else TS_LOGF(Message, "%u %u\n", i, pool.allocate(4, sizeof(uint32_t)));
		}
	}
	
	if(1) {
		
		Random<> random;
		
		TS_LOG(Message, "\n");
		
		HeapPool<> pool(size * size);
		
		for(uint32_t i = 0; i < 4; i++) {
			
			TS_LOGF(Message, "Iteration: %u\n", i);
			
			// allocate memory
			Array<uint32_t> allocations;
			for(uint32_t j = 1; j < size; j++) {
				uint32_t offset = pool.allocate(32, j);
				allocations.append(offset);
			}
			print(pool);
			
			// free memory
			for(uint32_t j = 0; j < size / 4; j++) {
				uint32_t index = random.geti32() % allocations.size();
				pool.free(allocations[index]);
				allocations[index] = Maxu32;
			}
			print(pool);
			
			// allocate memory
			for(uint32_t j = 1; j < size; j++) {
				uint32_t offset = pool.allocate(32, j);
				allocations.append(offset);
			}
			print(pool);
			
			// free memory
			for(uint32_t j = 0; j < allocations.size(); j++) {
				uint32_t i0 = random.geti32() % allocations.size();
				uint32_t i1 = random.geti32() % allocations.size();
				swap(allocations[i0], allocations[i1]);
			}
			for(uint32_t j = 0; j < allocations.size(); j++) {
				pool.free(allocations[j]);
			}
			print(pool);
			
			TS_LOG(Message, "\n");
		}
	}
	
	if(1) {
		
		TS_LOG(Message, "\n");
		
		HeapPool<0> pool(sizeof(uint32_t) * Maxu8);
		
		uint32_t offset_0 = pool.allocate(4, sizeof(uint32_t) * 32);
		uint32_t offset_1 = pool.allocate(4, sizeof(uint32_t) * 32);
		pool.free(offset_0);
		
		offset_0 = pool.allocate(4, sizeof(uint32_t), true);
		offset_1 = pool.allocate(4, sizeof(uint32_t), false);
		
		TS_LOGF(Message, "%u %u\n", offset_0, offset_1);
	}
	
	
	return 0;
}

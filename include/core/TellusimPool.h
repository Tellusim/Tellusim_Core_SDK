// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_POOL_H__
#define __TELLUSIM_CORE_POOL_H__

#include <core/TellusimSet.h>
#include <core/TellusimMap.h>
#include <core/TellusimArray.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Fixed pool memory allocator
	 */
	template <class Type, class Index = uint32_t> class FixedPool {
			
		public:
			
			FixedPool() { }
			explicit FixedPool(uint32_t size) { init(size); }
			~FixedPool() { }
			
			/// initialize pool
			void init(uint32_t size) {
				TS_ASSERT(size > sizeof(Type) && "FixedPool::init(): invalid size");
				TS_ASSERT(size / sizeof(Type) <= 1ull << (sizeof(Index) * 8u) && "FixedPool::init(): invalid size");
				num_indices = size / sizeof(Type);
				indices.resize(num_indices);
				for(uint32_t i = 0; i < num_indices; i++) {
					indices[i] = (Index)(num_indices - i - 1);
				}
			}
			
			/// shutdown pool
			void shutdown() {
				num_indices = 0;
				indices.clear();
			}
			
			/// pool status
			TS_INLINE bool isInitialized() {
				return (num_indices > 0);
			}
			
			/// allocate object memory
			uint32_t allocate() {
				TS_ASSERT(isInitialized() && "FixedPool::allocate(): is not initialized");
				if(indices.empty()) return Maxu32;
				uint32_t index = indices.back();
				indices.removeBack();
				return sizeof(Type) * index;
			}
			
			/// free object memory
			void free(uint32_t offset) {
				if(offset == Maxu32) return;
				TS_ASSERT(isInitialized() && "FixedPool::free(): is not initialized");
				uint32_t index = offset / sizeof(Type);
				TS_ASSERT(index < num_indices && "FixedPool::free(): invalid memory offset");
				indices.append((Index)index);
			}
			
			/// memory usage in bytes
			uint32_t getMemory() const {
				return sizeof(Type) * (num_indices - indices.size());
			}
			
			/// number of allocations
			uint32_t getAllocations() const {
				return num_indices - indices.size();
			}
			
		private:
			
			uint32_t num_indices = 0;			// number of indices
			Array<Index> indices;				// pool indices
	};
	
	/**
	 * Heap pool memory allocator
	 */
	template <uint32_t Threshold = 8> class HeapPool {
			
		public:
			
			/// constructor
			HeapPool() { }
			explicit HeapPool(uint32_t size) { init(size); }
			~HeapPool() { }
			
			/// initialize pool
			void init(uint32_t size) {
				TS_ASSERT(size > 0 && "HeapPool::init(): invalid size");
				blocks.clear();
				offsets.clear();
				allocations.clear();
				blocks.append((uint64_t)size << OffsetBits);
				offsets.append(0, size);
				capacity = size;
				memory_usage = 0;
			}
			
			/// shutdown pool
			void shutdown() {
				blocks.clear();
				offsets.clear();
				allocations.clear();
				memory_usage = 0;
			}
			
			/// pool status
			TS_INLINE bool isInitialized() {
				return (offsets || allocations);
			}
			
			/// append memory
			void append(uint32_t size) {
				TS_ASSERT(isInitialized() && "HeapPool::append(): is not initialized");
				TS_ASSERT(size > 0 && "HeapPool::append(): invalid size");
				auto it = offsets.back();
				uint32_t block_size = it->data;
				uint32_t block_offset = it->key;
				if(block_offset + block_size == capacity) {
					blocks.remove(((uint64_t)block_size << OffsetBits) | block_offset);
					blocks.append(((uint64_t)(block_size + size) << OffsetBits) | block_offset);
					it->data += size;
				} else {
					blocks.append(((uint64_t)size << OffsetBits) | capacity);
					offsets.append(capacity, size);
				}
				capacity += size;
			}
			
			/// allocate memory
			uint32_t allocate(uint32_t alignment, uint32_t size, bool optimal = true) {
				TS_ASSERT(isInitialized() && "HeapPool::allocate(): is not initialized");
				TS_ASSERT(alignment > 0 && "HeapPool::allocate(): invalid alignment");
				if(size == 0) return Maxu32;
				uint32_t mask = alignment - 1;
				auto it = (optimal) ? blocks.next(((uint64_t)size << OffsetBits) - 1u) : blocks.back();
				for(; it; ++it) {
					uint32_t align = 0;
					uint32_t block_size = (uint32_t)(it.get() >> OffsetBits);
					uint32_t block_offset = (uint32_t)(it.get() & OffsetMask);
					if((alignment & mask) == 0) align = ((block_offset + mask) & ~mask) - block_offset;
					else align = ((block_offset + mask) / alignment) * alignment - block_offset;
					if(size + align > block_size) continue;
					offsets.remove(block_offset);
					blocks.remove(it);
					if(align > 0) {
						blocks.append(((uint64_t)align << OffsetBits) | block_offset);
						offsets.append(block_offset, align);
						block_offset += align;
						block_size -= align;
					}
					if(block_size > size + Threshold || blocks.empty()) {
						blocks.append(((uint64_t)(block_size - size) << OffsetBits) | (block_offset + size));
						offsets.append(block_offset + size, block_size - size);
					} else {
						size = block_size;
					}
					allocations.append(block_offset, size);
					memory_usage += size;
					return block_offset;
				}
				return Maxu32;
			}
			
			/// free memory
			void free(uint32_t offset) {
				if(offset == Maxu32) return;
				TS_ASSERT(isInitialized() && "HeapPool::free(): is not initialized");
				auto it = allocations.find(offset);
				TS_ASSERT(it && "HeapPool::free(): invalid memory offset");
				TS_ASSERT(memory_usage >= it->data && "HeapPool::free(): invalid memory usage");
				uint32_t size = it->data;
				allocations.remove(it);
				memory_usage -= size;
				auto next_it = offsets.find(offset + size);
				if(next_it) {
					size += next_it->data;
					blocks.remove(((uint64_t)next_it->data << OffsetBits) | next_it->key);
					offsets.remove(next_it);
				}
				auto prev_it = offsets.prev(offset);
				if(prev_it && prev_it->key + prev_it->data == offset) {
					size += prev_it->data;
					offset -= prev_it->data;
					blocks.remove(((uint64_t)prev_it->data << OffsetBits) | prev_it->key);
					offsets.remove(prev_it);
				}
				blocks.append(((uint64_t)size << OffsetBits) | offset);
				offsets.append(offset, size);
			}
			
			/// pool size in bytes
			TS_INLINE uint32_t getSize() const {
				return capacity;
			}
			
			/// memory usage in bytes
			TS_INLINE uint32_t getMemory() const {
				return memory_usage;
			}
			
			/// number of allocations
			TS_INLINE uint32_t getAllocations() const {
				return allocations.size();
			}
			
			/// heap fragmentation
			TS_INLINE uint32_t getBlocks() const {
				return blocks.size();
			}
			
			/// heap state
			TS_INLINE const Map<uint32_t, uint32_t> &getState() const {
				return allocations;
			}
			
		private:
			
			enum {
				OffsetBits = 32u,
				OffsetMask = Maxu32,
			};
			
			Set<uint64_t> blocks;					// free blocks
			Map<uint32_t, uint32_t> offsets;		// free offsets
			Map<uint32_t, uint32_t> allocations;	// allocated offsets
			
			uint32_t capacity = 0;					// pool capacity
			uint32_t memory_usage = 0;				// pool memory usage
	};
}

#endif /* __TELLUSIM_CORE_POOL_H__ */

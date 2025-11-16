// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_ATOMIC_H__
#define __TELLUSIM_CORE_ATOMIC_H__

#if _WIN32
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
	#include <windows.h>
#endif

#include <TellusimBase.h>

/*
 */
namespace Tellusim {
	
	/**
	 * 32-bit integer Atomic
	 */
	struct Atomici32 final {
		
		Atomici32(int32_t value = 0) : value(value) { }
		
		TS_INLINE operator int32_t() { return get(); }
		TS_INLINE Atomici32 &operator=(int32_t value) { set(value); return *this; }
		
		#if _WIN32
			
			/// atomic operators
			TS_INLINE int32_t operator++() { return _InterlockedIncrement((volatile long*)&value); }
			TS_INLINE int32_t operator--() { return _InterlockedDecrement((volatile long*)&value); }
			TS_INLINE int32_t operator++(int32_t) { return _InterlockedIncrement((volatile long*)&value) - 1; }
			TS_INLINE int32_t operator--(int32_t) { return _InterlockedDecrement((volatile long*)&value) + 1; }
			TS_INLINE int32_t operator+=(int32_t v) { return _InterlockedExchangeAdd((volatile long*)&value,  v) + v; }
			TS_INLINE int32_t operator-=(int32_t v) { return _InterlockedExchangeAdd((volatile long*)&value, -v) - v; }
			TS_INLINE int32_t operator&=(int32_t v) { return _InterlockedAnd((volatile long*)&value, v) & v; }
			TS_INLINE int32_t operator|=(int32_t v) { return _InterlockedOr((volatile long*)&value, v) | v; }
			
			/// atomic functions
			TS_INLINE void set(int32_t v) { _InterlockedExchange((volatile long*)&value, v); }
			TS_INLINE int32_t get() { return _InterlockedExchangeAdd((volatile long*)&value, 0); }
			TS_INLINE bool cas(int32_t old_value, int32_t new_value) { return (_InterlockedCompareExchange((volatile long*)&value, new_value, old_value) == old_value); }
			
		#else
			
			/// atomic operators
			TS_INLINE int32_t operator++() { return __sync_add_and_fetch(&value, 1); }
			TS_INLINE int32_t operator--() { return __sync_sub_and_fetch(&value, 1); }
			TS_INLINE int32_t operator++(int32_t) { return __sync_fetch_and_add(&value, 1); }
			TS_INLINE int32_t operator--(int32_t) { return __sync_fetch_and_sub(&value, 1); }
			TS_INLINE int32_t operator+=(int32_t v) { return __sync_add_and_fetch(&value, v); }
			TS_INLINE int32_t operator-=(int32_t v) { return __sync_sub_and_fetch(&value, v); }
			TS_INLINE int32_t operator&=(int32_t v) { return __sync_and_and_fetch(&value, v); }
			TS_INLINE int32_t operator|=(int32_t v) { return __sync_or_and_fetch(&value, v); }
			
			/// atomic functions
			TS_INLINE void set(int32_t v) { (void)__sync_lock_test_and_set(&value, v); }
			TS_INLINE int32_t get() { return __sync_fetch_and_add(&value, 0); }
			TS_INLINE bool cas(int32_t old_value, int32_t new_value) { return __sync_bool_compare_and_swap(&value, old_value, new_value); }
			
		#endif
		
		volatile int32_t value;
	};
	
	/**
	 * 64-bit integer Atomic
	 */
	struct Atomici64 final {
		
		Atomici64(int64_t value = 0) : value(value) { }
		
		TS_INLINE operator int64_t() { return get(); }
		TS_INLINE Atomici64 &operator=(int64_t value) { set(value); return *this; }
		
		#if _WIN64
			
			/// atomic operators
			TS_INLINE int64_t operator++() { return _InterlockedIncrement64(&value); }
			TS_INLINE int64_t operator--() { return _InterlockedDecrement64(&value); }
			TS_INLINE int64_t operator++(int32_t) { return _InterlockedIncrement64(&value) - 1; }
			TS_INLINE int64_t operator--(int32_t) { return _InterlockedDecrement64(&value) + 1; }
			TS_INLINE int64_t operator+=(int64_t v) { return _InterlockedExchangeAdd64(&value,  v) + v; }
			TS_INLINE int64_t operator-=(int64_t v) { return _InterlockedExchangeAdd64(&value, -v) - v; }
			TS_INLINE int64_t operator&=(int64_t v) { return _InterlockedAnd64(&value, v) & v; }
			TS_INLINE int64_t operator|=(int64_t v) { return _InterlockedOr64(&value, v) | v; }
			
			/// atomic functions
			TS_INLINE void set(int64_t v) { _InterlockedExchange64(&value, v); }
			TS_INLINE int64_t get() { return _InterlockedExchangeAdd64(&value, 0); }
			TS_INLINE bool cas(int64_t old_value, int64_t new_value) { return (_InterlockedCompareExchange64(&value, new_value, old_value) == old_value); }
			
		#elif _WIN32
			
			/// atomic operators
			TS_INLINE int64_t operator++() { return ++value; }
			TS_INLINE int64_t operator--() { return --value; }
			TS_INLINE int64_t operator++(int32_t) { return value++; }
			TS_INLINE int64_t operator--(int32_t) { return value--; }
			TS_INLINE int64_t operator+=(int64_t v) { int64_t ret = value; value += v; return ret; }
			TS_INLINE int64_t operator-=(int64_t v) { int64_t ret = value; value -= v; return ret; }
			TS_INLINE int64_t operator&=(int64_t v) { int64_t ret = value; value &= v; return ret; }
			TS_INLINE int64_t operator|=(int64_t v) { int64_t ret = value; value |= v; return ret; }
			
			/// atomic functions
			TS_INLINE void set(int64_t v) { value = v; }
			TS_INLINE int64_t get() { return value; }
			TS_INLINE bool cas(int64_t old_value, int64_t new_value) { if(value == old_value) { value = new_value; return true; } return false; }
			
		#else
			
			/// atomic operators
			TS_INLINE int64_t operator++() { return __sync_add_and_fetch(&value, 1); }
			TS_INLINE int64_t operator--() { return __sync_sub_and_fetch(&value, 1); }
			TS_INLINE int64_t operator++(int32_t) { return __sync_fetch_and_add(&value, 1); }
			TS_INLINE int64_t operator--(int32_t) { return __sync_fetch_and_sub(&value, 1); }
			TS_INLINE int64_t operator+=(int64_t v) { return __sync_add_and_fetch(&value, v); }
			TS_INLINE int64_t operator-=(int64_t v) { return __sync_sub_and_fetch(&value, v); }
			TS_INLINE int64_t operator&=(int64_t v) { return __sync_and_and_fetch(&value, v); }
			TS_INLINE int64_t operator|=(int64_t v) { return __sync_or_and_fetch(&value, v); }
			
			/// atomic functions
			TS_INLINE void set(int64_t v) { (void)__sync_lock_test_and_set(&value, v); }
			TS_INLINE int64_t get() { return __sync_fetch_and_add(&value, 0); }
			TS_INLINE bool cas(int64_t old_value, int64_t new_value) { return __sync_bool_compare_and_swap(&value, old_value, new_value); }
			
		#endif
		
		volatile int64_t value;
	};
	
	/**
	 * Atomic pointer
	 */
	template <class Type> struct AtomicPtr {
		
		AtomicPtr(Type *ptr = nullptr) : ptr(ptr) { }
		
		TS_INLINE operator Type*() { return get(); }
		TS_INLINE AtomicPtr &operator=(Type *ptr) { set(ptr); return *this; }
		explicit TS_INLINE operator bool() { return (get() != nullptr); }
		
		TS_INLINE Type &operator[](int32_t index) { return get()[index]; }
		TS_INLINE Type &operator[](uint32_t index) { return get()[index]; }
		
		#if _WIN64
			
			/// atomic operators
			TS_INLINE Type *operator++() { return (Type*)_InterlockedExchangeAdd64((volatile int64_t*)&ptr, (int64_t)sizeof(Type)); }
			TS_INLINE Type *operator--() { return (Type*)_InterlockedExchangeAdd64((volatile int64_t*)&ptr, -(int64_t)sizeof(Type)); }
			TS_INLINE Type *operator++(int32_t) { return (Type*)(_InterlockedExchangeAdd64((volatile int64_t*)&ptr,  (int64_t)sizeof(Type)) + sizeof(Type)); }
			TS_INLINE Type *operator--(int32_t) { return (Type*)(_InterlockedExchangeAdd64((volatile int64_t*)&ptr, -(int64_t)sizeof(Type)) - sizeof(Type)); }
			TS_INLINE Type *operator+=(size_t v) { return (Type*)(_InterlockedExchangeAdd64((volatile int64_t*)&ptr,  (int64_t)sizeof(Type) * v) + sizeof(Type) * v); }
			TS_INLINE Type *operator-=(size_t v) { return (Type*)(_InterlockedExchangeAdd64((volatile int64_t*)&ptr, -(int64_t)sizeof(Type) * v) - sizeof(Type) * v); }
			
			/// atomic functions
			TS_INLINE void set(Type *p) { _InterlockedExchange64((volatile int64_t*)&ptr, (int64_t)p); }
			TS_INLINE Type *get() { return (Type*)_InterlockedExchangeAdd64((volatile int64_t*)&ptr, 0); }
			TS_INLINE bool cas(Type *old_ptr, Type *new_ptr) { return (_InterlockedCompareExchange64((volatile int64_t*)&ptr, (int64_t)new_ptr, (int64_t)old_ptr) == (int64_t)old_ptr); }
			
		#elif _WIN32
			
			/// atomic operators
			TS_INLINE Type *operator++() { return (Type*)_InterlockedExchangeAdd((volatile long*)&ptr, (long)sizeof(Type)); }
			TS_INLINE Type *operator--() { return (Type*)_InterlockedExchangeAdd((volatile long*)&ptr, -(long)sizeof(Type)); }
			TS_INLINE Type *operator++(int32_t) { return (Type*)(_InterlockedExchangeAdd((volatile long*)&ptr,  (long)sizeof(Type)) + sizeof(Type)); }
			TS_INLINE Type *operator--(int32_t) { return (Type*)(_InterlockedExchangeAdd((volatile long*)&ptr, -(long)sizeof(Type)) - sizeof(Type)); }
			TS_INLINE Type *operator+=(size_t v) { return (Type*)(_InterlockedExchangeAdd((volatile long*)&ptr,  (long)sizeof(Type) * v) + sizeof(Type) * v); }
			TS_INLINE Type *operator-=(size_t v) { return (Type*)(_InterlockedExchangeAdd((volatile long*)&ptr, -(long)sizeof(Type) * v) - sizeof(Type) * v); }
			
			/// atomic functions
			TS_INLINE void set(Type *p) { _InterlockedExchange((volatile long*)&ptr, (long)p); }
			TS_INLINE Type *get() { return (Type*)_InterlockedExchangeAdd((volatile long*)&ptr, 0); }
			TS_INLINE bool cas(Type *old_ptr, Type *new_ptr) { return (_InterlockedCompareExchange((volatile long*)&ptr, (long)new_ptr, (long)old_ptr) == (long)old_ptr); }
			
		#else
			
			/// atomic operators
			TS_INLINE Type *operator++() { return (Type*)__sync_add_and_fetch((volatile size_t*)&ptr, sizeof(Type)); }
			TS_INLINE Type *operator--() { return (Type*)__sync_sub_and_fetch((volatile size_t*)&ptr, sizeof(Type)); }
			TS_INLINE Type *operator++(int32_t) { return (Type*)__sync_fetch_and_add((volatile size_t*)&ptr, sizeof(Type)); }
			TS_INLINE Type *operator--(int32_t) { return (Type*)__sync_fetch_and_sub((volatile size_t*)&ptr, sizeof(Type)); }
			TS_INLINE Type *operator+=(size_t v) { return (Type*)__sync_add_and_fetch((volatile size_t*)&ptr, sizeof(Type) * v); }
			TS_INLINE Type *operator-=(size_t v) { return (Type*)__sync_sub_and_fetch((volatile size_t*)&ptr, sizeof(Type) * v); }
			
			/// atomic functions
			TS_INLINE void set(Type *p) { (void)__sync_lock_test_and_set(&ptr, p); }
			TS_INLINE Type *get() { return (Type*)__sync_fetch_and_add(&ptr, 0); }
			TS_INLINE bool cas(Type *old_ptr, Type *new_ptr) { return __sync_bool_compare_and_swap(&ptr, old_ptr, new_ptr); }
			
		#endif
		
		volatile Type *ptr;
	};
	
	/**
	 * Atomic Array
	 */
	template <class Type> class AtomicArray {
			
		public:
			
			AtomicArray() : capacity(0), length(0) { }
			explicit AtomicArray(uint32_t size) : capacity(0), length(0) { resize(size); }
			AtomicArray(uint32_t size, const Type *array) : capacity(0), length(0) { copy(array, size); }
			AtomicArray(uint32_t size, const Type &value) : capacity(0), length(0) { resize(size, value); }
			AtomicArray(AtomicArray &array) : capacity(0), length(0) { copy(array); }
			~AtomicArray() { release(); }
			
			/// resize array
			void reserve(uint32_t size) {
				if((uint32_t)capacity < size) {
					uint32_t new_capacity = (size * 3 + 2) / 2;
					Type *new_data = new Type[new_capacity];
					if(IsPod<Type>::Result) {
						memcpy((void*)new_data, (const void*)data, sizeof(Type) * length);
					} else {
						for(uint32_t i = 0; i < (uint32_t)length; i++) {
							new_data[i] = data[i];
						}
					}
					delete [] data.get();
					capacity = new_capacity;
					data = new_data;
				}
			}
			void resize(uint32_t size, bool reserve = false, bool discard = false) {
				if((uint32_t)capacity < size) {
					uint32_t new_capacity = (reserve) ? (size * 3 + 2) / 2 : size;
					Type *new_data = new Type[new_capacity];
					if(!discard) {
						if(IsPod<Type>::Result) {
							memcpy((void*)new_data, (const void*)data, sizeof(Type) * length);
						} else {
							for(uint32_t i = 0; i < (uint32_t)length; i++) {
								new_data[i] = data[i];
							}
						}
					}
					delete [] data.get();
					capacity = new_capacity;
					data = new_data;
				}
				length = size;
			}
			void resize(uint32_t size, const Type &value, bool reserve = false) {
				resize(size, reserve);
				for(uint32_t i = 0; i < size; i++) {
					data[i] = value;
				}
			}
			
			/// clear array
			void release() {
				if(data != nullptr) {
					delete [] data;
					capacity = 0;
					length = 0;
				}
			}
			void clear() {
				length = 0;
			}
			
			/// swap arrays
			void swap(AtomicArray &array) {
				Tellusim::swap(capacity, array.capacity);
				Tellusim::swap(length, array.length);
				Tellusim::swap(data, array.data);
			}
			
			/// copy value
			void copy(const Type *array, uint32_t size) {
				resize(size, false, true);
				for(uint32_t i = 0; i < size; i++) {
					data[i] = array[i];
				}
			}
			void copy(AtomicArray &array) {
				copy(array.get(), array.size());
			}
			
			/// assignment operator
			AtomicArray &operator=(AtomicArray &array) {
				if(&array == this) return *this;
				copy(array);
				return *this;
			}
			
			/// append value
			void append(const Type &value) {
				reserve(length + 1);
				data[length++] = value;
			}
			AtomicArray &append(const Type *array, uint32_t size) {
				reserve(length + size);
				for(uint32_t i = 0; i < size; i++) {
					data[length++] = array[i];
				}
				return *this;
			}
			TS_INLINE AtomicArray &append(AtomicArray &array) {
				return append(array.get(), array.size());
			}
			
			/// remove value
			void removeFast(uint32_t pos, uint32_t len = 1) {
				TS_ASSERT(pos < (uint32_t)length && "AtomicArray::removeFast(): invalid position");
				if(len == Maxu32) len = length - pos;
				TS_ASSERT(pos + len <= (uint32_t)length && "AtomicArray::removeFast(): invalid length");
				uint32_t size = length - pos - len;
				if(size > len) size = len;
				for(uint32_t i = 0; i < size; i++) {
					data[pos + i] = data[length - size + i];
				}
				length -= len;
			}
			void remove(uint32_t pos, uint32_t len = 1) {
				TS_ASSERT(pos < (uint32_t)length && "AtomicArray::remove(): invalid position");
				if(len == Maxu32) len = length - pos;
				TS_ASSERT(pos + len <= (uint32_t)length && "AtomicArray::remove(): invalid length");
				for(uint32_t i = pos + len; i < (uint32_t)length; i++) {
					data[i - len] = data[i];
				}
				length -= len;
			}
			
			/// array info
			TS_INLINE bool empty() { return (length == 0); }
			explicit TS_INLINE operator bool() { return (length != 0); }
			TS_INLINE uint32_t bytes() { return sizeof(Type) * length; }
			TS_INLINE uint32_t memory() { return capacity; }
			TS_INLINE uint32_t size() { return length; }
			
			/// array data
			TS_INLINE Type *get() { return data; }
			TS_INLINE Type &operator[](uint32_t index) {
				TS_ASSERT(index < (uint32_t)length && "AtomicArray::operator[](): invalid index");
				return data[index];
			}
			TS_INLINE Type &get(uint32_t index) {
				TS_ASSERT(index < (uint32_t)length && "AtomicArray::get(): invalid index");
				return data[index];
			}
			
			/// array data
			template <class T> uint32_t findIndex(const T &value) {
				for(uint32_t i = 0; i < (uint32_t)length; i++) {
					if(data[i] == value) return i;
				}
				return Maxu32;
			}
			
			/// array iterators
			TS_INLINE Type *begin() { return data; }
			TS_INLINE Type *end() { return data + length; }
			
		private:
			
			Atomici32 capacity;
			Atomici32 length;
			AtomicPtr<Type> data;
	};
	
	/**
	 * Swap arrays
	 */
	template <class Type> void swap(AtomicArray<Type> &a0, AtomicArray<Type> &a1) {
		a0.swap(a1);
	}
	
	/**
	 * SpinLock class
	 */
	struct SpinLock final {
		
		SpinLock() { }
		
		explicit TS_INLINE operator bool() { return (get() != 0); }
		
		TS_INLINE void clear() { atomic.set(0); }
		TS_INLINE void signal() { atomic.set(1); }
		TS_INLINE void lock() { while(!atomic.cas(0, 1)) { } }
		TS_INLINE void unlock() { while(!atomic.cas(1, 0)) { } }
		TS_INLINE bool check() { return atomic.cas(0, 1); }
		TS_INLINE int32_t get() { return atomic.get(); }
		
		Atomici32 atomic;
	};
	
	/**
	 * AtomicLock class
	 */
	struct AtomicLock final {
		
		TS_INLINE AtomicLock(SpinLock &lock) : lock(lock) {
			lock.lock();
		}
		TS_INLINE ~AtomicLock() {
			lock.unlock();
		}
		
		SpinLock &lock;
	};
}

#endif /* __TELLUSIM_CORE_ATOMIC_H__ */

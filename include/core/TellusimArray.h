// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_ARRAY_H__
#define __TELLUSIM_CORE_ARRAY_H__

#include <core/TellusimAllocator.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	template <class, uint32_t> class ArrayStack;
	
	/**
	 * Array container
	 */
	template <class Type> class Array {
			
		private:
			
			/// Array implementation
			struct ArrayImpl {
				
				ArrayImpl() : capacity(0), length(0), data(nullptr) { }
				~ArrayImpl() { release(); }
				
				/// swap arrays
				void swap(ArrayImpl &impl) {
					Tellusim::swap(capacity, impl.capacity);
					Tellusim::swap(length, impl.length);
					Tellusim::swap(data, impl.data);
				}
				
				/// copy array
				void copy(const ArrayImpl &impl) {
					resize(impl.length, false, true);
					if(IsPod<Type>::Result) {
						memcpy((void*)data, (const void*)impl.data, sizeof(Type) * length);
					} else {
						for(uint32_t i = 0; i < length; i++) {
							data[i] = impl.data[i];
						}
					}
				}
				
				/// move array
				void move(ArrayImpl &impl) {
					if(impl.capacity & (uint32_t)AllocatorBit) {
						release();
						capacity = impl.capacity;
						length = impl.length;
						data = impl.data;
						impl.capacity = 0;
						impl.length = 0;
						impl.data = nullptr;
					} else {
						copy(impl);
					}
				}
				
				/// initialize array data
				void init(Type *d, size_t size, uint32_t len) {
					if(data && (capacity & (uint32_t)AllocatorBit)) Allocator::freeArray<Type>(data, capacity & CapacityMask);
					if(d && size) {
						TS_ASSERT(len <= size && "Array::init(): invalid length");
						capacity = (uint32_t)size;
						length = len;
						data = d;
					} else {
						capacity = 0;
						length = 0;
						data = nullptr;
					}
				}
				
				/// reserve array
				void reserve(uint32_t size, bool discard = false) {
					if((capacity & CapacityMask) < size) {
						size_t new_capacity = ((size_t)size * 3 + 2) / 2;
						if(new_capacity >= (uint32_t)AllocatorBit) new_capacity = (size_t)AllocatorBit - 1;
						Type *new_data = Allocator::allocate<Type>((uint32_t)new_capacity);
						if(data && !discard) {
							if(IsPod<Type>::Result) {
								memcpy((void*)new_data, (const void*)data, sizeof(Type) * length);
							} else {
								for(uint32_t i = 0; i < length; i++) {
									new_data[i] = data[i];
								}
							}
						}
						if(data && (capacity & (uint32_t)AllocatorBit)) Allocator::freeArray<Type>(data, capacity & CapacityMask);
						capacity = (uint32_t)new_capacity | (uint32_t)AllocatorBit;
						data = new_data;
					}
				}
				
				/// resize array
				void resize(uint32_t size, bool reserve = false, bool discard = false) {
					if((capacity & CapacityMask) < size) {
						size_t new_capacity = size;
						if(reserve) new_capacity = ((size_t)size * 3 + 2) / 2;
						if(new_capacity >= (uint32_t)AllocatorBit) new_capacity = (uint32_t)AllocatorBit - 1;
						Type *new_data = Allocator::allocate<Type>((uint32_t)new_capacity);
						if(data && !discard) {
							if(IsPod<Type>::Result) {
								memcpy((void*)new_data, (const void*)data, sizeof(Type) * length);
							} else {
								for(uint32_t i = 0; i < length; i++) {
									new_data[i] = data[i];
								}
							}
						}
						if(data && (capacity & (uint32_t)AllocatorBit)) Allocator::freeArray<Type>(data, capacity & CapacityMask);
						capacity = (uint32_t)new_capacity | (uint32_t)AllocatorBit;
						data = new_data;
					}
					length = size;
				}
				
				/// discard array
				Type *discard() {
					Type *ret = data;
					if(capacity & (uint32_t)AllocatorBit) {
						data = nullptr;
						capacity = 0;
						length = 0;
					} else {
						length = 0;
					}
					return ret;
				}
				
				/// release array
				void release() {
					if(capacity & (uint32_t)AllocatorBit) {
						Allocator::freeArray<Type>(data, capacity & CapacityMask);
						data = nullptr;
						capacity = 0;
						length = 0;
					} else {
						length = 0;
					}
				}
				
				enum {
					AllocatorBit = (int32_t)(1u << (sizeof(uint32_t) * 8u - 1u)),
					CapacityMask = ~AllocatorBit,
				};
				
				uint32_t capacity;	// array capacity
				uint32_t length;	// array length
				Type *data;			// array data
			};
			
		public:
			
			/// Iterator
			class Iterator {
					
				private:
					
					friend class Array;
					
					Iterator(Type *begin, Type *end, Type *ptr) : begin(begin), end(end), ptr(ptr) { }
					
				public:
					
					Iterator() : begin(nullptr), end(nullptr), ptr(nullptr) { }
					Iterator(const Iterator &it) : begin(it.begin), end(it.end), ptr(it.ptr) { }
					
					void clear() { begin = nullptr; end = nullptr; ptr = nullptr; }
					
					Iterator &operator=(const Iterator &it) { begin = it.begin; end = it.end; ptr = it.ptr; return *this; }
					
					explicit TS_INLINE operator bool() const { return (ptr != end); }
					TS_INLINE bool operator==(const Iterator &it) const { return (begin == it.begin && end == it.end && ptr == it.ptr); }
					TS_INLINE bool operator!=(const Iterator &it) const { return (begin != it.begin || end != it.end || ptr != it.ptr); }
					
					TS_INLINE Iterator &operator++() { if(ptr < end) ptr++; return *this; }
					TS_INLINE Iterator &operator--() { if(ptr > begin) ptr--; return *this; }
					TS_INLINE Iterator operator++(int32_t) { Type *ret = ptr; if(ptr < end) ptr++; return Iterator(begin, end, ret); }
					TS_INLINE Iterator operator--(int32_t) { Type *ret = ptr; if(ptr > begin) ptr--; return Iterator(begin, end, ret); }
					
					int32_t operator-(const Iterator &it) const { if(begin == it.begin && end == it.end) return (int32_t)(ptr - it.ptr); return 0; }
					
					TS_INLINE Type &operator*() const { return *ptr; }
					TS_INLINE Type *operator->() const { return ptr; }
					TS_INLINE Type *get() const { return ptr; }
					
				private:
					
					Type *begin;	// begin of the array
					Type *end;		// end of the array
					Type *ptr;		// current element
			};
			
			/// Constant iterator
			class ConstIterator {
					
				private:
					
					friend class Array;
					
					ConstIterator(const Type *begin, const Type *end, const Type *ptr) : begin(begin), end(end), ptr(ptr) { }
					
				public:
					
					ConstIterator() : begin(nullptr), end(nullptr), ptr(nullptr) { }
					ConstIterator(const Iterator &it) : begin(it.begin), end(it.end), ptr(it.ptr) { }
					ConstIterator(const ConstIterator &it) : begin(it.begin), end(it.end), ptr(it.ptr) { }
					
					void clear() { begin = nullptr; end = nullptr; ptr = nullptr; }
					
					ConstIterator &operator=(const Iterator &it) { begin = it.begin; end = it.end; ptr = it.ptr; return *this; }
					ConstIterator &operator=(const ConstIterator &it) { begin = it.begin; end = it.end; ptr = it.ptr; return *this; }
					
					explicit TS_INLINE operator bool() const { return (ptr != end); }
					TS_INLINE bool operator==(const ConstIterator &it) const { return (begin == it.begin && end == it.end && ptr == it.ptr); }
					TS_INLINE bool operator!=(const ConstIterator &it) const { return (begin != it.begin || end != it.end || ptr != it.ptr); }
					
					TS_INLINE ConstIterator &operator++() { if(ptr < end) ptr++; return *this; }
					TS_INLINE ConstIterator &operator--() { if(ptr > begin) ptr--; return *this; }
					TS_INLINE ConstIterator operator++(int32_t) { const Type *ret = ptr; if(ptr < end) ptr++; return ConstIterator(begin, end, ret); }
					TS_INLINE ConstIterator operator--(int32_t) { const Type *ret = ptr; if(ptr > begin) ptr--; return ConstIterator(begin, end, ret); }
					
					int32_t operator-(const ConstIterator &it) const { if(begin == it.begin && end == it.end) return (int32_t)(ptr - it.ptr); return 0; }
					
					TS_INLINE const Type &operator*() const { return *ptr; }
					TS_INLINE const Type *operator->() const { return ptr; }
					TS_INLINE const Type *get() const { return ptr; }
					
				private:
					
					const Type *begin;	// begin of the array
					const Type *end;	// end of the array
					const Type *ptr;	// current element
			};
			
			/// constructors
			Array() { }
			explicit Array(uint32_t size) { resize(size); }
			Array(const InitializerList<Type> &list) { copy(list); }
			Array(uint32_t size, const Type *array) { copy(array, size); }
			Array(uint32_t size, const Type &value) { resize(size, value); }
			Array(const Array &array) { copy(array); }
			Array(Array &&array) { impl.move(array.impl); }
			template <uint32_t C> Array(const ArrayStack<Type, C> &array) { copy(array); }
			template <uint32_t C> Array(ArrayStack<Type, C> &&array) { move((ArrayStack<Type, C>&&)array); }
			~Array() { }
			
			/// initialize array data
			void init(Type *data, size_t size, uint32_t length = 0) {
				impl.init(data, size, length);
			}
			
			/// resize array
			TS_INLINE void reserve(uint32_t size, bool discard = false) {
				impl.reserve(size, discard);
			}
			TS_INLINE void resize(uint32_t size, bool reserve = false, bool discard = false) {
				impl.resize(size, reserve, discard);
			}
			void resize(uint32_t size, const Type &value, bool reserve = false) {
				impl.resize(size, reserve, true);
				for(uint32_t i = 0; i < size; i++) {
					impl.data[i] = value;
				}
			}
			
			/// clear array
			TS_INLINE Type *discard() {
				return impl.discard();
			}
			TS_INLINE void release() {
				impl.release();
			}
			TS_INLINE void clear() {
				impl.length = 0;
			}
			
			/// swap arrays
			TS_INLINE void swap(Array &array) {
				impl.swap(array.impl);
			}
			template <uint32_t C> void swap(ArrayStack<Type, C> &array);
			
			/// copy array
			void copy(const InitializerList<Type> &list) {
				impl.resize((uint32_t)list.size(), false, true);
				auto it = list.begin();
				for(uint32_t i = 0; i < impl.length; i++) {
					impl.data[i] = *it++;
				}
			}
			void copy(const Type *array, uint32_t size) {
				impl.resize(size, false, true);
				for(uint32_t i = 0; i < size; i++) {
					impl.data[i] = array[i];
				}
			}
			TS_INLINE void copy(const Array &array) {
				copy(array.get(), array.size());
			}
			TS_INLINE void move(Array &&array) {
				impl.move(array.impl);
			}
			template <uint32_t C> void move(ArrayStack<Type, C> &&array);
			
			/// assignment operators
			TS_INLINE Array &operator=(const InitializerList<Type> &list) {
				copy(list);
				return *this;
			}
			TS_INLINE Array &operator=(const Array &array) {
				if(&array != this) copy(array);
				return *this;
			}
			TS_INLINE Array &operator=(Array &&array) {
				move((Array&&)array);
				return *this;
			}
			template <uint32_t C> TS_INLINE Array &operator=(ArrayStack<Type, C> &&array) {
				move((ArrayStack<Type, C>&&)array);
				return *this;
			}
			
			/// append value
			TS_INLINE Type &append() {
				impl.reserve(impl.length + 1);
				return impl.data[impl.length++];
			}
			TS_INLINE Array &append(const Type &value) {
				impl.reserve(impl.length + 1);
				impl.data[impl.length++] = value;
				return *this;
			}
			Array &append(const Type *array, uint32_t size) {
				impl.reserve(impl.length + size);
				for(uint32_t i = 0; i < size; i++) {
					impl.data[impl.length++] = array[i];
				}
				return *this;
			}
			Array &append(const Array &array) {
				return append(array.get(), array.size());
			}
			Array &append(const InitializerList<Type> &list) {
				impl.reserve(impl.length + (uint32_t)list.size());
				auto it = list.begin();
				for(uint32_t i = 0; i < list.size(); i++) {
					impl.data[impl.length++] = *it++;
				}
				return *this;
			}
			
			/// insert value
			Array &insert(uint32_t pos, const Type &value) {
				TS_ASSERT(pos <= impl.length && "Array::insert(): invalid position");
				impl.resize(impl.length + 1, true);
				for(uint32_t i = impl.length - 1; i > pos; i--) {
					impl.data[i] = impl.data[i - 1];
				}
				impl.data[pos] = value;
				return *this;
			}
			Array &insert(uint32_t pos, const Type *array, uint32_t size) {
				TS_ASSERT(pos <= impl.length && "Array::insert(): invalid position");
				impl.resize(impl.length + size, true);
				for(uint32_t i = impl.length - 1, end = pos + size - 1; i > end; i--) {
					impl.data[i] = impl.data[i - size];
				}
				for(uint32_t i = 0; i < size; i++) {
					impl.data[pos++] = array[i];
				}
				return *this;
			}
			Array &insert(uint32_t pos, const Array &array) {
				return insert(pos, array.get(), array.size());
			}
			Array &insert(uint32_t pos, const InitializerList<Type> &list) {
				TS_ASSERT(pos <= impl.length && "Array::insert(): invalid position");
				impl.resize(impl.length + (uint32_t)list.size(), true);
				for(uint32_t i = impl.length - 1, end = pos + (uint32_t)list.size() - 1; i > end; i--) {
					impl.data[i] = impl.data[i - list.size()];
				}
				auto it = list.begin();
				for(uint32_t i = 0; i < list.size(); i++) {
					impl.data[pos++] = *it++;
				}
				return *this;
			}
			
			/// replace value
			Array &replace(uint32_t pos, const Type *array, uint32_t size) {
				TS_ASSERT(pos <= impl.length && "Array::replace(): invalid position");
				TS_ASSERT(pos + size <= impl.length && "Array::replace(): invalid size");
				for(uint32_t i = 0; i < size; i++) {
					impl.data[pos++] = array[i];
				}
				return *this;
			}
			Array &replace(uint32_t pos, const Array &array) {
				return replace(pos, array.get(), array.size());
			}
			Array &replace(uint32_t pos, const InitializerList<Type> &list) {
				TS_ASSERT(pos <= impl.length && "Array::replace(): invalid position");
				TS_ASSERT(pos + list.size() <= impl.length && "Array::replace(): invalid size");
				auto it = list.begin();
				for(uint32_t i = 0; i < list.size(); i++) {
					impl.data[pos++] = *it++;
				}
				return *this;
			}
			
			/// remove value
			TS_INLINE Array &removeBack(uint32_t len = 1) {
				TS_ASSERT(len <= impl.length && "Array::removeBack(): invalid length");
				impl.length -= len;
				return *this;
			}
			Array &removeFast(uint32_t pos, uint32_t len = 1) {
				TS_ASSERT(pos < impl.length && "Array::removeFast(): invalid position");
				if(len == Maxu32) len = impl.length - pos;
				TS_ASSERT(pos + len <= impl.length && "Array::removeFast(): invalid length");
				uint32_t size = impl.length - pos - len;
				if(size > len) size = len;
				for(uint32_t i = 0; i < size; i++) {
					impl.data[pos + i] = impl.data[impl.length - size + i];
				}
				impl.length -= len;
				return *this;
			}
			Array &remove(uint32_t pos, uint32_t len = 1) {
				TS_ASSERT(pos < impl.length && "Array::remove(): invalid position");
				if(len == Maxu32) len = impl.length - pos;
				TS_ASSERT(pos + len <= impl.length && "Array::remove(): invalid length");
				for(uint32_t i = pos + len; i < impl.length; i++) {
					impl.data[i - len] = impl.data[i];
				}
				impl.length -= len;
				return *this;
			}
			TS_INLINE Array &remove(const Iterator &it) {
				return remove(it - begin());
			}
			TS_INLINE Array &remove(const ConstIterator &it) {
				return remove(it - begin());
			}
			
			/// reverse values
			Array &reverse(uint32_t pos = 0, uint32_t len = Maxu32) {
				TS_ASSERT(pos <= impl.length && "Array::reverse(): invalid position");
				if(len == Maxu32) len = impl.length - pos;
				TS_ASSERT(pos + len <= impl.length && "Array::reverse(): invalid length");
				for(uint32_t i = len / 2; i < len; i++) {
					Tellusim::swap(impl.data[pos + i], impl.data[pos + len - i - 1]);
				}
				return *this;
			}
			
			/// array info
			TS_INLINE bool empty() const { return (impl.length == 0); }
			explicit TS_INLINE operator bool() const { return (impl.length != 0); }
			TS_INLINE size_t bytes() const { return sizeof(Type) * impl.length; }
			TS_INLINE size_t memory() const { return sizeof(Type) * (impl.capacity & ArrayImpl::CapacityMask); }
			TS_INLINE bool allocator() const { return ((impl.capacity & ArrayImpl::AllocatorBit) != 0); }
			TS_INLINE uint32_t capacity() const { return (impl.capacity & ArrayImpl::CapacityMask); }
			TS_INLINE uint32_t size() const { return impl.length; }
			
			/// array data
			TS_INLINE const Type *get() const { return impl.data; }
			TS_INLINE Type *get() { return impl.data; }
			TS_INLINE const Type &operator[](uint32_t index) const {
				TS_ASSERT(index < impl.length && "Array::operator[](): invalid index");
				return impl.data[index];
			}
			TS_INLINE Type &operator[](uint32_t index) {
				TS_ASSERT(index < impl.length && "Array::operator[](): invalid index");
				return impl.data[index];
			}
			TS_INLINE const Type &get(uint32_t index) const {
				TS_ASSERT(index < impl.length && "Array::get(): invalid index");
				return impl.data[index];
			}
			TS_INLINE Type &get(uint32_t index) {
				TS_ASSERT(index < impl.length && "Array::get(): invalid index");
				return impl.data[index];
			}
			
			/// array data
			template <class T> Iterator find(const T &value) {
				for(uint32_t i = 0; i < impl.length; i++) {
					if(impl.data[i] == value) return Iterator(impl.data, impl.data + impl.length, impl.data + i);
				}
				return Iterator(impl.data, impl.data + impl.length, impl.data + impl.length);
			}
			template <class T> ConstIterator find(const T &value) const {
				for(uint32_t i = 0; i < impl.length; i++) {
					if(impl.data[i] == value) return ConstIterator(impl.data, impl.data + impl.length, impl.data + i);
				}
				return ConstIterator(impl.data, impl.data + impl.length, impl.data + impl.length);
			}
			template <class T> uint32_t findIndex(const T &value) const {
				for(uint32_t i = 0; i < impl.length; i++) {
					if(impl.data[i] == value) return i;
				}
				return Maxu32;
			}
			
			/// sorted array
			template <class T> uint32_t binaryIndex(const T &value) const {
				if(impl.length == 0) return Maxu32;
				int32_t l = 0;
				int32_t r = impl.length - 1;
				while(l <= r) {
					int32_t m = (l + r) >> 1;
					if(impl.data[m] < value) l = m + 1;
					else if(value < impl.data[m]) r = m - 1;
					else return (uint32_t)m;
				}
				return Maxu32;
			}
			template <class T> uint32_t prevIndex(const T &value) const {
				if(impl.length == 0) return Maxu32;
				if(value < impl.data[0]) return Maxu32;
				int32_t l = 0;
				int32_t r = impl.length - 1;
				while(l <= r) {
					int32_t m = (l + r) >> 1;
					if(impl.data[m] < value) l = m + 1;
					else if(value < impl.data[m]) r = m - 1;
					else if(m == 0) return Maxu32;
					else return (uint32_t)m - 1;
				}
				return (uint32_t)l - 1;
			}
			template <class T> uint32_t nextIndex(const T &value) const {
				if(impl.length == 0) return Maxu32;
				if(impl.data[impl.length - 1] < value) return Maxu32;
				int32_t l = 0;
				int32_t r = impl.length - 1;
				while(l <= r) {
					int32_t m = (l + r) >> 1;
					if(impl.data[m] < value) l = m + 1;
					else if(value < impl.data[m]) r = m - 1;
					else if(m == (int32_t)impl.length - 1) return Maxu32;
					else return (uint32_t)m + 1;
				}
				return (uint32_t)r + 1;
			}
			
			/// array iterators
			TS_INLINE Iterator begin() { return Iterator(impl.data, impl.data + impl.length, impl.data); }
			TS_INLINE Iterator end() { return Iterator(impl.data, impl.data + impl.length, impl.data + impl.length); }
			TS_INLINE ConstIterator begin() const { return ConstIterator(impl.data, impl.data + impl.length, impl.data); }
			TS_INLINE ConstIterator end() const { return ConstIterator(impl.data, impl.data + impl.length, impl.data + impl.length); }
			TS_INLINE ConstIterator beginConst() const { return ConstIterator(impl.data, impl.data + impl.length, impl.data); }
			TS_INLINE ConstIterator endConst() const { return ConstIterator(impl.data, impl.data + impl.length, impl.data + impl.length); }
			
			/// array elements
			TS_INLINE const Type &front(uint32_t index = 0) const {
				TS_ASSERT(index < impl.length && "Array::front(): invalid index");
				return impl.data[index];
			}
			TS_INLINE const Type &back(uint32_t index = 0) const {
				TS_ASSERT(index < impl.length && "Array::back(): invalid index");
				return impl.data[impl.length - index - 1];
			}
			TS_INLINE Type &front(uint32_t index = 0) {
				TS_ASSERT(index < impl.length && "Array::front(): invalid index");
				return impl.data[index];
			}
			TS_INLINE Type &back(uint32_t index = 0) {
				TS_ASSERT(index < impl.length && "Array::back(): invalid index");
				return impl.data[impl.length - index - 1];
			}
			
		private:
			
			template <class, uint32_t> friend class ArrayStack;
			
			ArrayImpl impl;		// array implementation
	};
	
	/**
	 * ArrayStack container
	 */
	template <class Type, uint32_t Capacity> class ArrayStack : public Array<Type> {
			
		public:
			
			using ArrayBase = Tellusim::Array<Type>;
			
			ArrayStack() { ArrayBase::init(data, Capacity); }
			explicit ArrayStack(uint32_t size) { ArrayBase::init(data, Capacity); ArrayBase::resize(size); }
			ArrayStack(const InitializerList<Type> &list) { ArrayBase::init(data, Capacity); ArrayBase::copy(list); }
			ArrayStack(uint32_t size, const Type *array) { ArrayBase::init(data, Capacity); ArrayBase::copy(array, size); }
			ArrayStack(uint32_t size, const Type &value) { ArrayBase::init(data, Capacity); ArrayBase::resize(size, value); }
			ArrayStack(const ArrayBase &array) { ArrayBase::init(data, Capacity); ArrayBase::copy(array); }
			ArrayStack(const ArrayStack &array) { ArrayBase::init(data, Capacity); ArrayBase::copy(array); }
			ArrayStack(ArrayBase &&array) { ArrayBase::move((ArrayBase&&)array); }
			ArrayStack(ArrayStack &&array) { move((ArrayStack&&)array); }
			template <uint32_t C> ArrayStack(const ArrayStack<Type, C> &array) { ArrayBase::init(data, Capacity); ArrayBase::copy(array); }
			template <uint32_t C> ArrayStack(ArrayStack<Type, C> &&array) { move((ArrayStack<Type, C>&&)array); }
			
			/// swap arrays
			TS_INLINE void swap(ArrayBase &array) {
				array.swap(*this);
			}
			void swap(ArrayStack &array) {
				if(ArrayBase::get() != data && array.get() != array.data) {
					ArrayBase::swap(array);
				} else {
					ArrayStack temp = array;
					array.copy(ArrayBase::get(), ArrayBase::size());
					ArrayBase::copy(temp);
				}
			}
			template <uint32_t C> void swap(ArrayStack<Type, C> &array) {
				if(ArrayBase::get() != data && array.get() != array.data) {
					ArrayBase::swap(array);
				} else {
					ArrayStack temp = array;
					array.copy(ArrayBase::get(), ArrayBase::size());
					ArrayBase::copy(temp);
				}
			}
			
			/// copy array
			void move(ArrayStack &&array) {
				ArrayBase::init(data, Capacity);
				if(array.get() != array.data) ArrayBase::move((ArrayBase&&)array);
				else ArrayBase::copy(array);
			}
			template <uint32_t C> void move(ArrayStack<Type, C> &&array) {
				ArrayBase::init(data, Capacity);
				if(array.get() != array.data) ArrayBase::move((ArrayBase&&)array);
				else ArrayBase::copy(array);
			}
			
			/// assignment operators
			TS_INLINE ArrayStack &operator=(const InitializerList<Type> &list) {
				ArrayBase::copy(list);
				return *this;
			}
			TS_INLINE ArrayStack &operator=(const ArrayBase &array) {
				if(array.get() != ArrayBase::get()) ArrayBase::copy(array);
				return *this;
			}
			TS_INLINE ArrayStack &operator=(const ArrayStack &array) {
				if(array.get() != ArrayBase::get()) ArrayBase::copy(array);
				return *this;
			}
			template <uint32_t C> TS_INLINE ArrayStack &operator=(const ArrayStack<Type, C> &array) {
				if(array.get() != ArrayBase::get()) ArrayBase::copy(array);
				return *this;
			}
			TS_INLINE ArrayStack &operator=(ArrayBase &&array) {
				ArrayBase::move((ArrayBase&&)array);
				return *this;
			}
			TS_INLINE ArrayStack &operator=(ArrayStack &&array) {
				ArrayBase::move((ArrayStack&&)array);
				return *this;
			}
			template <uint32_t C> TS_INLINE ArrayStack &operator=(ArrayStack<Type, C> &&array) {
				ArrayBase::move((ArrayStack<Type, C>&&)array);
				return *this;
			}
			
		private:
			
			template <class> friend class Tellusim::Array;
			template <class, uint32_t> friend class ArrayStack;
			
			Type data[Capacity];	// stack data
	};
	
	/// swap arrays
	template <class Type> template <uint32_t C> void Array<Type>::swap(ArrayStack<Type, C> &array) {
		if(array.get() != array.data) {
			swap((Array&)array);
		} else {
			ArrayStack<Type, C> temp = array;
			array.copy(get(), size());
			copy(temp);
		}
	}
	
	/// copy array
	template <class Type> template <uint32_t C> void Array<Type>::move(ArrayStack<Type, C> &&array) {
		if(array.get() != array.data) move((Array&&)array);
		else copy(array);
	}
	
	/**
	 * Swap arrays
	 */
	template <class Type> void swap(Array<Type> &a0, Array<Type> &a1) { a0.swap(a1); }
	template <class Type, uint32_t C> void swap(Array<Type> &a0, ArrayStack<Type, C> &a1) { a0.swap(a1); }
	template <class Type, uint32_t C> void swap(ArrayStack<Type, C> &a0, Array<Type> &a1) { a0.swap(a1); }
	template <class Type, uint32_t C> void swap(ArrayStack<Type, C> &a0, ArrayStack<Type, C> &a1) { a0.swap(a1); }
	template <class Type, uint32_t C0, uint32_t C1> void swap(ArrayStack<Type, C0> &a0, ArrayStack<Type, C1> &a1) { a0.swap(a1); }
}

#endif /* __TELLUSIM_CORE_ARRAY_H__ */

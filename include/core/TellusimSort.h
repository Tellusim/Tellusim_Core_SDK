// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_SORT_H__
#define __TELLUSIM_CORE_SORT_H__

#include <TellusimBase.h>

/*
 */
namespace Tellusim {
	
	/*****************************************************************************\
	 *
	 * Elements sort
	 *
	\*****************************************************************************/
	
	/*
	 */
	template <class Type> void sort3(Type &v0, Type &v1, Type &v2) {
		if(v0 > v1) swap(v0, v1);
		if(v1 > v2) swap(v1, v2);
		if(v0 > v1) swap(v0, v1);
	}
	
	/*
	 */
	template <class Type> void sort4(Type &v0, Type &v1, Type &v2, Type &v3) {
		if(v0 > v1) swap(v0, v1);
		if(v2 > v3) swap(v2, v3);
		if(v0 > v2) swap(v0, v2);
		if(v1 > v3) swap(v1, v3);
		if(v1 > v2) swap(v1, v2);
	}
	
	/*****************************************************************************\
	 *
	 * quickSort
	 *
	\*****************************************************************************/
	
	/**
	 * quickSort default compare
	 */
	template <class Type> struct QuickCompare {
		TS_INLINE int32_t operator()(const Type &q0, const Type &q1) const {
			if(q0 < q1) return -1;
			if(q0 > q1) return 1;
			return 0;
		}
	};
	
	template <class Type> struct QuickInverseCompare {
		TS_INLINE int32_t operator()(const Type &q0, const Type &q1) const {
			if(q0 > q1) return -1;
			if(q0 < q1) return 1;
			return 0;
		}
	};
	
	/**
	 * quickSort function compare
	 */
	template <class Type, class Func> struct QuickFunctionCompare {
		QuickFunctionCompare(const Func &func) : func(func) { }
		TS_INLINE int32_t operator()(const Type &q0, const Type &q1) const {
			return func(q0, q1);
		}
		Func func;
	};
	
	/**
	 * Make quickSort compare function
	 */
	template <class Type, class Func> QuickFunctionCompare<Type, Func> makeQuickCompare(const Func &func) {
		return QuickFunctionCompare<Type, Func>(func);
	}
	
	/**
	 * quickSort
	 * \brief Sort typed array.
	 */
	template <class Type, class Compare = QuickCompare<Type>, class Index = int32_t, uint32_t StackSize = 512> void quickSort(Type *data, uint32_t size, Compare compare = QuickCompare<Type>()) {
		
		if(size < 2) return;
		
		int32_t depth = 0;
		Index stack[StackSize];
		stack[0] = 0;
		stack[1] = size - 1;
		
		while(depth >= 0) {
			Index left = stack[depth + 0];
			Index right = stack[depth + 1];
			Index l = left;
			Index r = right;
			Type value = data[(l + r) >> 1];
			do {
				while(r > left && compare(value, data[r]) < 0) r--;
				while(l < right && compare(value, data[l]) > 0) l++;
				if(l < r) swap(data[l++], data[r--]);
				else if(l == r) { l++; r--; }
			} while(l <= r);
			if(left < r) {
				if(l < right) {
					TS_ASSERT(depth + 4 < (int32_t)StackSize && "quickSort(): stack overflow");
					if(r - left > right - l) {
						stack[depth + 1] = r;
						stack[depth + 2] = l;
						stack[depth + 3] = right;
					} else {
						stack[depth + 0] = l;
						stack[depth + 2] = left;
						stack[depth + 3] = r;
					}
					depth += 2;
				} else {
					stack[depth + 1] = r;
				}
			} else if(l < right) {
				stack[depth + 0] = l;
			} else {
				depth -= 2;
			}
		}
	}
	
	/**
	 * quickSort
	 * \brief Sort typed array with parameters.
	 */
	template <class Type, class Parameter, class Compare = QuickCompare<Type>, class Index = int32_t, uint32_t StackSize = 512> void quickSort(Type *data, Parameter *parameters, uint32_t size, Compare compare = QuickCompare<Type>()) {
		
		if(size < 2) return;
		
		int32_t depth = 0;
		Index stack[StackSize];
		stack[0] = 0;
		stack[1] = size - 1;
		
		while(depth >= 0) {
			Index left = stack[depth + 0];
			Index right = stack[depth + 1];
			Index l = left;
			Index r = right;
			Type value = data[(l + r) >> 1];
			do {
				while(r > left && compare(value, data[r]) < 0) r--;
				while(l < right && compare(value, data[l]) > 0) l++;
				if(l < r) swap(data[l], data[r]), swap(parameters[l++], parameters[r--]);
				else if(l == r) { l++; r--; }
			} while(l <= r);
			if(left < r) {
				if(l < right) {
					TS_ASSERT(depth + 4 < (int32_t)StackSize && "quickSort(): stack overflow");
					if(r - left > right - l) {
						stack[depth + 1] = r;
						stack[depth + 2] = l;
						stack[depth + 3] = right;
					} else {
						stack[depth + 0] = l;
						stack[depth + 2] = left;
						stack[depth + 3] = r;
					}
					depth += 2;
				} else {
					stack[depth + 1] = r;
				}
			} else if(l < right) {
				stack[depth + 0] = l;
			} else {
				depth -= 2;
			}
		}
	}
	
	/*****************************************************************************\
	 *
	 * radixSort
	 *
	\*****************************************************************************/
	
	/**
	 * radixSort default compare
	 */
	template <class Type> struct RadixCompare;
	
	template <> struct RadixCompare<int32_t> {
		enum { Bits = 32 };
		using Radix = uint32_t;
		TS_INLINE uint32_t operator()(int32_t value) {
			return (uint32_t)value ^ 0x80000000u;
		}
	};
	
	template <> struct RadixCompare<uint32_t> {
		enum { Bits = 32 };
		using Radix = uint32_t;
		TS_INLINE uint32_t operator()(uint32_t value) {
			return value;
		}
	};
	
	template <> struct RadixCompare<float32_t> {
		enum { Bits = 32 };
		using Radix = uint32_t;
		TS_INLINE uint32_t operator()(float32_t value) {
			union { float32_t f; uint32_t u; } f32u32 = { value };
			if(f32u32.u & 0x80000000u) return ~f32u32.u;
			return f32u32.u ^ 0x80000000u;
		}
	};
	
	/**
	 * radixSort sort pass
	 */
	template <uint32_t Size, uint32_t Shift0, uint32_t Shift1, uint32_t Mask0, uint32_t Mask1, class Type> Type *radixPass2(Type *data, uint32_t size) {
		
		uint32_t histogram0[Size] = {};
		uint32_t histogram1[Size] = {};
		for(uint32_t i = 0; i < size; i++) {
			typename Type::Radix radix = data[i].radix;
			histogram0[(radix >> Shift0) & Mask0]++;
			histogram1[(radix >> Shift1) & Mask1]++;
		}
		for(uint32_t i = 0, c0 = size, c1 = 0; i < Size; i++) {
			uint32_t h0 = histogram0[i];
			uint32_t h1 = histogram1[i];
			histogram0[i] = c0;
			histogram1[i] = c1;
			c0 += h0;
			c1 += h1;
		}
		
		for(uint32_t i = 0; i < size; i++) {
			data[histogram0[(data[i].radix >> Shift0) & Mask0]++] = data[i];
		}
		for(uint32_t i = 0, j = size; i < size; i++, j++) {
			data[histogram1[(data[j].radix >> Shift1) & Mask1]++] = data[j];
		}
		
		return data;
	}
	
	template <uint32_t Size, uint32_t Shift0, uint32_t Shift1, uint32_t Shift2, uint32_t Mask0, uint32_t Mask1, uint32_t Mask2, class Type> Type *radixPass3(Type *data, uint32_t size) {
		
		uint32_t histogram0[Size] = {};
		uint32_t histogram1[Size] = {};
		uint32_t histogram2[Size] = {};
		for(uint32_t i = 0; i < size; i++) {
			typename Type::Radix radix = data[i].radix;
			histogram0[(radix >> Shift0) & Mask0]++;
			histogram1[(radix >> Shift1) & Mask1]++;
			histogram2[(radix >> Shift2) & Mask2]++;
		}
		for(uint32_t i = 0, c0 = size, c1 = 0, c2 = size; i < Size; i++) {
			uint32_t h0 = histogram0[i];
			uint32_t h1 = histogram1[i];
			uint32_t h2 = histogram2[i];
			histogram0[i] = c0;
			histogram1[i] = c1;
			histogram2[i] = c2;
			c0 += h0;
			c1 += h1;
			c2 += h2;
		}
		
		for(uint32_t i = 0; i < size; i++) {
			data[histogram0[(data[i].radix >> Shift0) & Mask0]++] = data[i];
		}
		for(uint32_t i = 0, j = size; i < size; i++, j++) {
			data[histogram1[(data[j].radix >> Shift1) & Mask1]++] = data[j];
		}
		for(uint32_t i = 0; i < size; i++) {
			data[histogram2[(data[i].radix >> Shift2) & Mask2]++] = data[i];
		}
		
		return data + size;
	}
	
	/**
	 * radixSort
	 */
	template <class Type, class Compare = RadixCompare<Type>, uint32_t Capacity = 1024> void radixSort(Type *dest, const Type *src, uint32_t size, Compare compare = RadixCompare<Type>()) {
		
		struct Index {
			using Radix = typename Compare::Radix;
			uint32_t index;
			Radix radix;
		};
		
		Index *indices = nullptr;
		Index indices_data[Capacity * 2];
		if(size <= Capacity) indices = indices_data;
		else indices = new Index[size * 2];
		for(uint32_t i = 0; i < size; i++) {
			indices[i].radix = compare(src[i]);
			indices[i].index = i;
		}
		
		Index *sort = nullptr;
		if(Compare::Bits == 16) sort = radixPass2<0x100, 0, 8, 0xff, 0xff>(indices, size);
		else if(Compare::Bits == 24) sort = radixPass3<0x100, 0, 8, 16, 0xff, 0xff, 0xff>(indices, size);
		else if(Compare::Bits == 32) sort = radixPass3<0x800, 0, 11, 22, 0x7ff, 0x7ff, 0x3ff>(indices, size);
		else TS_ASSERT(0 && "radixSort(): unsupported bit count");
		
		for(uint32_t i = 0; i < size; i++) {
			dest[i] = src[sort[i].index];
		}
		
		if(indices != indices_data) delete [] indices;
	}
	
	template <class Type, class Compare = RadixCompare<Type>, uint32_t Capacity = 1024> void radixSort(Type *data, uint32_t size, Compare compare = RadixCompare<Type>()) {
		
		Type *src = nullptr;
		Type src_data[Capacity];
		if(size <= Capacity) src = src_data;
		else src = new Type[size];
		for(uint32_t i = 0; i < size; i++) {
			src[i] = data[i];
		}
		
		radixSort<Type, Compare, Capacity>(data, src, size, compare);
		
		if(src != src_data) delete [] src;
	}
}

#endif /* __TELLUSIM_CORE_SORT_H__ */

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_TYPE_H__
#define __TELLUSIM_CORE_TYPE_H__

#include <TellusimBase.h>

/*
 */
namespace Tellusim {
	
	/**
	 * IntToType template
	 */
	template <int32_t IntTo> struct IntToType {
		enum { Int = IntTo };
	};
	
	/**
	 * TypeToType template
	 */
	template <class TypeTo> struct TypeToType {
		using Type = TypeTo;
	};
	
	/**
	 * TypeList template
	 */
	struct TypeListEnd {
		
	};
	
	template <class Type = TypeListEnd, class... List> struct TypeList : public TypeList<List...> {
		
	};
	
	/**
	 * TypeListLength template
	 */
	template <class Type> struct TypeListLength {
		
	};
	
	template <> struct TypeListLength<TypeList<TypeListEnd>> {
		enum { Result = 0 };
	};
	
	template <class Type> struct TypeListLength<TypeList<Type>> {
		enum { Result = 1 };
	};
	
	template <class Type, class... List> struct TypeListLength<TypeList<Type, List...>> {
		enum { Result = 1 + TypeListLength<TypeList<List...>>::Result };
	};
	
	/**
	 * TypeListAt template
	 */
	template <int32_t Num, class TypeAt> struct TypeListAt {
		using Type = TypeListEnd;
	};
	
	template <class TypeAt, class... List> struct TypeListAt<0, TypeList<TypeAt, List...>> {
		using Type = TypeAt;
	};
	
	template <int32_t Num, class TypeAt, class... List> struct TypeListAt<Num, TypeList<TypeAt, List...>> {
		using Type = typename TypeListAt<Num - 1, TypeList<List...>>::Type;
	};
}

#endif /* __TELLUSIM_CORE_TYPE_H__ */

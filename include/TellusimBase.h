// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

/*
 */
#ifdef min
	#undef min
	#undef max
#endif

#ifdef check
	#undef check
#endif

/*
 */
#ifndef __TELLUSIM_BASE_H__
#define __TELLUSIM_BASE_H__

#include <cassert>
#include <cstdint>
#include <cstdarg>
#include <cstddef>
#include <cstring>

#include <initializer_list>

/*
 */
#if defined(_M_X64) || defined(__x86_64__)
	#define TS_ARCH					"x64"
	#define TS_X64					1
#elif defined(_M_IX86) || defined(__i386__)
	#define TS_ARCH					"x86"
	#define TS_X86					1
#elif defined(_M_ARM64) || defined(__aarch64__)
	#define TS_ARCH					"arm64"
	#define TS_ARM64				1
#elif defined(_M_ARM) || defined(__arm__)
	#define TS_ARCH					"arm"
	#define TS_ARMV7				1
#else
	#define TS_ARCH					"Unknown"
#endif

/*
 */
#if _WIN32
	#define TS_PLATFORM				"Windows"
#elif _LINUX
	#define TS_PLATFORM				"Linux"
#elif _MACOS
	#define TS_PLATFORM				"macOS"
#elif _ANDROID
	#define TS_PLATFORM				"Android"
#elif _IOS
	#define TS_PLATFORM				"iOS"
#elif _TVOS
	#define TS_PLATFORM				"tvOS"
#elif _EMSCRIPTEN
	#define TS_PLATFORM				"Emscripten"
#else
	#define TS_PLATFORM				"Unknown"
#endif

/*
 */
#if TS_DEBUG
	#define TS_ASSERT(EXP)			assert(EXP)
#else
	#define TS_ASSERT(EXP)			(static_cast<void>(0))
#endif

#define TS_STATIC_ASSERT(EXP)		static_assert(EXP, #EXP)

/*
 */
#define TS_TO_STRING(NAME)			#NAME
#define TS_STRING(NAME)				TS_TO_STRING(NAME)

/*
 */
#define TS_UNUSED(NAME)				(void)NAME

/*
 */
#define TS_COUNTOF(ARRAY)			(sizeof(ARRAY) / sizeof(ARRAY[0]))

/*
 */
#if _WIN32
	#if TS_EXPORT
		#define TS_API				__declspec(dllexport)
	#else
		#define TS_API				__declspec(dllimport)
	#endif
	#define TS_INLINE				__forceinline
	#define TS_RESTRICT				__restrict
#else
	#define TS_API					__attribute__ ((visibility("default")))
	#define TS_INLINE				__inline__ __attribute__ ((always_inline))
	#define TS_RESTRICT				__restrict
#endif

/*
 */
#if __GNUC__
	#define TS_PRINTF(FORMAT, ARGS)	__attribute__((format(printf, FORMAT, ARGS)))
	#define TS_SCANF(FORMAT, ARGS)	__attribute__((format(scanf, FORMAT, ARGS)))
#else
	#define TS_PRINTF(FORMAT, ARGS)
	#define TS_SCANF(FORMAT, ARGS)
#endif

/*
 */
#if (TS_X64 || TS_ARM64) && (_LINUX || _ANDROID)
	#define TS_FORMAT_64			"l"
#else
	#define TS_FORMAT_64			"ll"
#endif

/*
 */
#define TS_ALIGNAS4					alignas(4)
#define TS_ALIGNAS8					alignas(8)
#define TS_ALIGNAS16				alignas(16)
#define TS_ALIGNAS32				alignas(32)
#define TS_ALIGNAS64				alignas(64)

#define TS_ALIGN4(VALUE)			(((VALUE) + 0x03) & ~0x03)
#define TS_ALIGN8(VALUE)			(((VALUE) + 0x07) & ~0x07)
#define TS_ALIGN16(VALUE)			(((VALUE) + 0x0f) & ~0x0f)
#define TS_ALIGN32(VALUE)			(((VALUE) + 0x1f) & ~0x1f)
#define TS_ALIGN64(VALUE)			(((VALUE) + 0x3f) & ~0x3f)

#define TS_ISALIGNED4(VALUE)		(((size_t)(VALUE) & 0x03) == 0)
#define TS_ISALIGNED8(VALUE)		(((size_t)(VALUE) & 0x07) == 0)
#define TS_ISALIGNED16(VALUE)		(((size_t)(VALUE) & 0x0f) == 0)
#define TS_ISALIGNED32(VALUE)		(((size_t)(VALUE) & 0x1f) == 0)
#define TS_ISALIGNED64(VALUE)		(((size_t)(VALUE) & 0x3f) == 0)

/*
 */
#define TS_DECLARE_PTR_BASE(TYPE, SIZE) \
	public: \
		TYPE(const TYPE&); \
		TYPE(TYPE&); \
		TYPE(TYPE&&); \
		TYPE &operator=(const TYPE&); \
		TYPE &operator=(TYPE&); \
		TYPE &operator=(TYPE&&); \
		bool operator==(const TYPE&) const; \
		bool operator!=(const TYPE&) const; \
		bool operator<=(const TYPE&) const; \
		bool operator>=(const TYPE&) const; \
		bool operator<(const TYPE&) const; \
		bool operator>(const TYPE&) const; \
		explicit operator bool() const; \
		TYPE clonePtr() const; \
		void clearPtr(); \
		void destroyPtr(); \
		TYPE &acquirePtr(); \
		TYPE &unacquirePtr(); \
		bool isValidPtr() const; \
		bool isOwnerPtr() const; \
		bool isConstPtr() const; \
		uint32_t getCountPtr() const; \
		const void *getInternalPtr() const; \
		static const TYPE null; \
	protected: \
		TYPE(const VoidImpl&); \
	private: \
		friend struct TYPE ## Impl; \
		struct TYPE ## Impl; \
		TS_INLINE const TYPE ## Impl *impl() const { return (const TYPE ## Impl*)reserved; } \
		TS_INLINE TYPE ## Impl *impl() { return (TYPE ## Impl*)reserved; } \
		void *reserved[3 + SIZE];

#define TS_DECLARE_PTR(TYPE, SIZE) \
	TS_DECLARE_PTR_BASE(TYPE, SIZE) \
	public: \
		~TYPE(); \
		const char *getClassName() const; \
		static const char *getClassNamePtr();

#define TS_DECLARE_PTR_0(TYPE, SIZE) \
	TS_DECLARE_PTR_BASE(TYPE, SIZE) \
	public: \
		virtual ~TYPE(); \
		virtual const char *getClassName() const; \
		static const char *getClassNamePtr();

#define TS_DECLARE_PTR_1(TYPE, BASE, SIZE) \
	TS_DECLARE_PTR_0(TYPE, SIZE) \
	public: \
		explicit TYPE(const BASE&); \
		explicit TYPE(BASE&); \
		explicit TYPE(BASE&&); \
		TYPE &operator=(const BASE&); \
		TYPE &operator=(BASE&); \
		TYPE &operator=(BASE&&); \
		bool operator==(const BASE&) const; \
		bool operator!=(const BASE&) const; \
		bool operator<=(const BASE&) const; \
		bool operator>=(const BASE&) const; \
		bool operator<(const BASE&) const; \
		bool operator>(const BASE&) const; \
		const BASE get ## BASE() const; \
		BASE get ## BASE();

#define TS_DECLARE_PTR_2(TYPE, BASE_1, BASE_0, SIZE) \
	TS_DECLARE_PTR_1(TYPE, BASE_0, SIZE) \
	public: \
		explicit TYPE(const BASE_1&); \
		explicit TYPE(BASE_1&); \
		explicit TYPE(BASE_1&&); \
		TYPE &operator=(const BASE_1&); \
		TYPE &operator=(BASE_1&); \
		TYPE &operator=(BASE_1&&); \
		bool operator==(const BASE_1&) const; \
		bool operator!=(const BASE_1&) const; \
		bool operator<=(const BASE_1&) const; \
		bool operator>=(const BASE_1&) const; \
		bool operator<(const BASE_1&) const; \
		bool operator>(const BASE_1&) const; \
		const BASE_1 get ## BASE_1() const; \
		BASE_1 get ## BASE_1();

#define TS_DECLARE_PTR_3(TYPE, BASE_2, BASE_1, BASE_0, SIZE) \
	TS_DECLARE_PTR_2(TYPE, BASE_1, BASE_0, SIZE) \
	public: \
		explicit TYPE(const BASE_2&); \
		explicit TYPE(BASE_2&); \
		explicit TYPE(BASE_2&&); \
		TYPE &operator=(const BASE_2&); \
		TYPE &operator=(BASE_2&); \
		TYPE &operator=(BASE_2&&); \
		bool operator==(const BASE_2&) const; \
		bool operator!=(const BASE_2&) const; \
		bool operator<=(const BASE_2&) const; \
		bool operator>=(const BASE_2&) const; \
		bool operator<(const BASE_2&) const; \
		bool operator>(const BASE_2&) const; \
		const BASE_2 get ## BASE_2() const; \
		BASE_2 get ## BASE_2();

#define TS_DECLARE_PTR_4(TYPE, BASE_3, BASE_2, BASE_1, BASE_0, SIZE) \
	TS_DECLARE_PTR_3(TYPE, BASE_2, BASE_1, BASE_0, SIZE) \
	public: \
		explicit TYPE(const BASE_3&); \
		explicit TYPE(BASE_3&); \
		explicit TYPE(BASE_3&&); \
		TYPE &operator=(const BASE_3&); \
		TYPE &operator=(BASE_3&); \
		TYPE &operator=(BASE_3&&); \
		bool operator==(const BASE_3&) const; \
		bool operator!=(const BASE_3&) const; \
		bool operator<=(const BASE_3&) const; \
		bool operator>=(const BASE_3&) const; \
		bool operator<(const BASE_3&) const; \
		bool operator>(const BASE_3&) const; \
		const BASE_3 get ## BASE_3() const; \
		BASE_3 get ## BASE_3();

/*
 */
#define TS_DECLARE_COPY(TYPE, SIZE) \
	public: \
		TYPE(const TYPE&); \
		TYPE(TYPE&&); \
		TYPE &operator=(const TYPE&); \
		TYPE &operator=(TYPE&&); \
		~TYPE(); \
		const char *getClassName() const; \
		static const char *getClassNamePtr(); \
	private: \
		friend struct TYPE ## Impl; \
		struct TYPE ## Impl; \
		TS_INLINE const TYPE ## Impl *impl() const { return (const TYPE ## Impl*)reserved; } \
		TS_INLINE TYPE ## Impl *impl() { return (TYPE ## Impl*)reserved; } \
		void *reserved[3 + SIZE];

/*
 */
#define TS_DECLARE_NONCOPY(TYPE, SIZE) \
	public: \
		TYPE(const TYPE&) = delete; \
		TYPE &operator=(const TYPE&) = delete; \
		virtual ~TYPE(); \
		virtual const char *getClassName() const; \
		static const char *getClassNamePtr(); \
	private: \
		friend struct TYPE ## Impl; \
		struct TYPE ## Impl; \
		TS_INLINE const TYPE ## Impl *impl() const { return (const TYPE ## Impl*)reserved; } \
		TS_INLINE TYPE ## Impl *impl() { return (TYPE ## Impl*)reserved; } \
		void *reserved[3 + SIZE];

/*
 */
#define TS_DECLARE_BASE(TYPE) \
	public: \
		TYPE(const TYPE&) = delete; \
		TYPE &operator=(const TYPE&) = delete; \
		virtual ~TYPE(); \
		virtual const char *getClassName() const; \
		static const char *getClassNamePtr(); \
	private: \
		friend struct TYPE ## Impl; \
		struct TYPE ## Impl; \
		TS_INLINE const TYPE ## Impl *impl() const { return pointer; } \
		TS_INLINE TYPE ## Impl *impl() { return pointer; } \
		TYPE ## Impl* pointer = nullptr;

/*
 */
#define TS_DECLARE_ENUM_OP(TYPE) \
	TS_INLINE TYPE operator~(TYPE e) { return (TYPE)(~(uint32_t)e); } \
	TS_INLINE TYPE operator|(TYPE e0, TYPE e1) { return (TYPE)((uint32_t)e0 | (uint32_t)e1); } \
	TS_INLINE TYPE operator&(TYPE e0, TYPE e1) { return (TYPE)((uint32_t)e0 & (uint32_t)e1); } \
	TS_INLINE TYPE operator^(TYPE e0, TYPE e1) { return (TYPE)((uint32_t)e0 ^ (uint32_t)e1); } \
	TS_INLINE TYPE operator|=(TYPE &e0, TYPE e1) { return (e0 = (TYPE)((uint32_t)e0 | (uint32_t)e1)); } \
	TS_INLINE TYPE operator&=(TYPE &e0, TYPE e1) { return (e0 = (TYPE)((uint32_t)e0 & (uint32_t)e1)); } \
	TS_INLINE TYPE operator^=(TYPE &e0, TYPE e1) { return (e0 = (TYPE)((uint32_t)e0 ^ (uint32_t)e1)); }

/*
 */
#define TS_DECLARE_ENUM_FRIEND(TYPE) \
	friend TYPE operator~(TYPE e); \
	friend TYPE operator|(TYPE e0, TYPE e1); \
	friend TYPE operator&(TYPE e0, TYPE e1); \
	friend TYPE operator^(TYPE e0, TYPE e1); \
	friend TYPE operator|=(TYPE &e0, TYPE e1); \
	friend TYPE operator&=(TYPE &e0, TYPE e1); \
	friend TYPE operator^=(TYPE &e0, TYPE e1);

/*
 */
#if _WIN32
	#pragma warning(disable: 4100)		// unreferenced formal parameter
	#pragma warning(disable: 4127)		// conditional expression is constant
	#pragma warning(disable: 4201)		// nonstandard extension used: nameless struct/union
	#pragma warning(disable: 4316)		// '...': object allocated on the heap may not be aligned 16
	#pragma warning(disable: 4324)		// '...': structure was padded due to alignment specifier
	#pragma warning(disable: 4447)		// 'main' signature found without threading model
	#pragma warning(disable: 4456)		// declaration of '...' hides previous local declaration
	#pragma warning(disable: 4457)		// declaration of '...' hides function parameter
	#pragma warning(disable: 4458)		// declaration of '...' hides class member
	#pragma warning(disable: 4521)		// multiple copy constructors specified
	#pragma warning(disable: 4522)		// multiple assignment operators specified
	#pragma warning(disable: 26495)		// Variable '...' is uninitialized. Always initialize a member variable.
	#pragma warning(disable: 26812)		// The enum type '...' is unscoped. Prefer 'enum class' over 'enum'.
#endif

/*
 */
namespace Tellusim {
	
	/**
	 * Integer types
	 */
	constexpr int8_t Mini8 = -127 - 1;
	constexpr int8_t Maxi8 =  127;
	constexpr uint8_t Maxu8 = 255u;
	
	constexpr int16_t Mini16 = -32767 - 1;
	constexpr int16_t Maxi16 =  32767;
	constexpr uint16_t Maxu16 = 65535u;
	
	constexpr int32_t Mini32 = -2147483647 - 1;
	constexpr int32_t Maxi32 =  2147483647;
	constexpr uint32_t Maxu32 = 4294967295u;
	
	constexpr int64_t Mini64 = -9223372036854775807ll - 1;
	constexpr int64_t Maxi64 =  9223372036854775807ll;
	constexpr uint64_t Maxu64 = 18446744073709551615ull;
	
	constexpr size_t MaxSize = ~(size_t)0u;
	
	/**
	 * Floating point types
	 */
	using float32_t = float;
	using float64_t = double;
	
	constexpr uint16_t Onef16 = 0x3c00u;
	constexpr uint32_t Onef21 = 0x7c000u;
	constexpr uint32_t Onef24 = 0x3e0000u;
	constexpr uint32_t Onef32 = 0x3f800000u;
	constexpr uint64_t Onef64 = 0x3ff0000000000000ull;
	
	constexpr uint16_t Signf16 = 0x8000u;
	constexpr uint32_t Signf21 = 0x100000u;
	constexpr uint32_t Signf24 = 0x800000u;
	constexpr uint32_t Signf32 = 0x80000000u;
	constexpr uint64_t Signf64 = 0x8000000000000000ull;
	
	constexpr float32_t Minf16 = 5.96046448e-08f;
	constexpr float32_t Maxf16 = 65504.0f;
	
	constexpr float32_t Minf32 = 1.17549435e-38f;
	constexpr float32_t Maxf32 = 3.40282346e+38f;
	
	constexpr float64_t Minf64 = 2.22507385850720138e-308;
	constexpr float64_t Maxf64 = 1.79769313486231571e+308;
	
	/**
	 * VoidImpl type
	 */
	struct VoidImpl {
		
	};
	
	/**
	 * Swap values
	 */
	template <class Type> void swap(Type &t0, Type &t1) {
		Type temp = t0; t0 = t1; t1 = temp;
	}
	
	/**
	 * Move semantic
	 */
	template <class RefType> struct UnrefType {
		using Type = RefType;
	};
	template <class RefType> struct UnrefType<RefType&> {
		using Type = RefType;
	};
	template <class RefType> struct UnrefType<RefType&&> {
		using Type = RefType;
	};
	template <class RefType> struct UnrefType<const RefType&> {
		using Type = RefType;
	};
	template <class Type> typename UnrefType<Type>::Type &&move(Type &&ptr) {
		return (typename UnrefType<Type>::Type &&)ptr;
	}
	
	/**
	 * Pointer type
	 */
	template <class Type> struct IsPtr {
		enum { Result = 0 };
	};
	template <class Type> struct IsPtr<Type*> {
		enum { Result = 1 };
	};
	
	/**
	 * Plain old data type
	 */
	template <class Type> struct IsPod {
		enum { Result = 0 };
	};
	template <class Type> struct IsPod<Type*> {
		enum { Result = 1 };
	};
	
	template <> struct IsPod<char> { enum { Result = 1 }; };
	template <> struct IsPod<wchar_t> { enum { Result = 1 }; };
	
	template <> struct IsPod<int8_t> { enum { Result = 1 }; };
	template <> struct IsPod<int16_t> { enum { Result = 1 }; };
	template <> struct IsPod<int32_t> { enum { Result = 1 }; };
	template <> struct IsPod<int64_t> { enum { Result = 1 }; };
	
	template <> struct IsPod<uint8_t> { enum { Result = 1 }; };
	template <> struct IsPod<uint16_t> { enum { Result = 1 }; };
	template <> struct IsPod<uint32_t> { enum { Result = 1 }; };
	template <> struct IsPod<uint64_t> { enum { Result = 1 }; };
	
	template <> struct IsPod<float32_t> { enum { Result = 1 }; };
	template <> struct IsPod<float64_t> { enum { Result = 1 }; };
	
	/**
	 * Initializer list
	 */
	template <class Type> using InitializerList = std::initializer_list<Type>;
}

#endif /* __TELLUSIM_BASE_H__ */

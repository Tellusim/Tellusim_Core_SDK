// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_STRING_H__
#define __TELLUSIM_CORE_STRING_H__

#include <core/TellusimLog.h>
#include <core/TellusimArray.h>

/*
 */
namespace Tellusim {
	
	/**
	 * The String class provides a comprehensive set of functionalities for managing and manipulating strings.
	 * It supports operations such as resizing, clearing, copying, appending, inserting, removing, and reversing strings.
	 * The class also provides utility functions for string comparison, search, format conversion, and encoding/decoding.
	 * Additionally, it includes functions for working with file paths, string case manipulation, and string formatting using variadic templates.
	 * The String class can handle different types of string data, including ASCII, UTF-16, and UTF-32 encoded data.
	 * It also provides static functions to convert between strings and various data types (e.g., integers, floating-point values, and sizes).
	 */
	class TS_API String {
			
			TS_DECLARE_COPY(String, 4)
			
		public:
			
			String();
			explicit String(uint32_t size, char c = 0);
			explicit String(const char *str, uint32_t length = Maxu32);
			explicit String(const wchar_t *str, uint32_t length = Maxu32);
			explicit String(const uint32_t *str, uint32_t length = Maxu32);
			
			/// resize string
			String &reserve(uint32_t size, bool discard = false);
			String &resize(uint32_t size, char c = 0, bool reserve = false);
			
			/// clear string
			void release();
			void clear();
			
			/// copy string
			void copy(const char *str, uint32_t length = Maxu32);
			void copy(const wchar_t *str, uint32_t length = Maxu32);
			void copy(const uint32_t *str, uint32_t length = Maxu32);
			void copy(const String &string, uint32_t length = Maxu32);
			
			String &operator=(const char *str);
			
			/// append string
			String &append(char c);
			String &append(const char *str, uint32_t length = Maxu32);
			String &append(const String &string, uint32_t length = Maxu32);
			
			String &operator+=(char c);
			String &operator+=(const char *str);
			String &operator+=(const String &string);
			
			/// insert string
			String &insert(uint32_t pos, const char *str, uint32_t length = Maxu32);
			String &insert(uint32_t pos, const String &string, uint32_t length = Maxu32);
			
			/// remove string
			String &removeBack(uint32_t length = 1);
			String &remove(uint32_t pos, uint32_t length = 1);
			
			/// reverse string
			String &reverse(uint32_t pos = 0, uint32_t length = Maxu32);
			
			/// string info
			uint32_t size() const;
			TS_INLINE bool empty() const { return (size() == 0); }
			explicit TS_INLINE operator bool() const { return (size() != 0); }
			
			/// string data
			char *get();
			const char *get() const;
			char &get(uint32_t index);
			char get(uint32_t index) const;
			TS_INLINE char &operator[](uint32_t index) { return get(index); }
			TS_INLINE char operator[](uint32_t index) const { return get(index); }
			
			/// find ascii character
			uint32_t find(char c, uint32_t pos = 0) const;
			uint32_t rfind(char c, uint32_t pos = Maxu32) const;
			uint32_t count(char c, uint32_t pos = 0) const;
			
			/// find part of the string
			uint32_t find(const char *str, uint32_t pos = 0) const;
			uint32_t rfind(const char *str, uint32_t pos = Maxu32) const;
			uint32_t count(const char *str, uint32_t pos = 0) const;
			
			/// compare begin of the string
			bool begins(const char *str, uint32_t length = Maxu32, uint32_t pos = 0) const;
			
			/// contains the string
			bool contains(const char *str, uint32_t length = Maxu32, uint32_t pos = 0) const;
			
			/// matches the pattern
			bool match(const char *str, uint32_t length = Maxu32, uint32_t pos = 0) const;
			
			/// compare strings
			int32_t compare(const char *str, uint32_t pos = 0) const;
			
			/// distance between strings
			uint32_t distance(const char *str, bool scan = false, uint32_t pos = 0) const;
			
			/// string iterators
			const char *begin() const;
			const char *end() const;
			
			/// string elements
			char front(uint32_t index = 0) const;
			char back(uint32_t index = 0) const;
			char &front(uint32_t index = 0);
			char &back(uint32_t index = 0);
			
			/// return part of the string
			String substring(uint32_t pos, uint32_t length = Maxu32) const;
			
			/// replace part of the string
			String replace(char before, char after, uint32_t pos = 0) const;
			String replace(const char *before, const char *after, uint32_t pos = 0) const;
			String replace(const String &before, const String &after, uint32_t pos = 0) const;
			
			/// split string
			const Array<String> split(const char *delimiters, uint32_t length = Maxu32) const;
			const Array<String> split(const String &delimiters, uint32_t length = Maxu32) const;
			
			/// file name utils
			String extension(const char *extension) const;
			String extension() const;
			String pathname() const;
			String basename() const;
			String dirname() const;
			
			/// relative file name
			static String relname(const char *path, const char *str);
			static String relname(const String &path, const String &str);
			
			/// convert string case
			String capitalize(const char *delimiters = nullptr, const char *spaces = nullptr) const;
			String lower() const;
			String upper() const;
			
			/// string to unicode
			static uint32_t toUtf32(const char *str, uint32_t &code);
			uint32_t toUtf16(wchar_t *d, uint32_t length) const;
			uint32_t toUtf32(uint32_t *d, uint32_t length) const;
			
			/// unicode to string
			static uint32_t fromUtf32(String &d, uint32_t code);
			static String fromUtf16(const wchar_t *str, uint32_t length = Maxu32);
			static String fromUtf32(const uint32_t *str, uint32_t length = Maxu32);
			
			/// url to string
			static String fromUrl(const char *str, uint32_t length = Maxu32);
			static String fromUrl(const String &string, uint32_t length = Maxu32);
			
			/// string scan function
			uint32_t vscanf(const char *format, va_list args) const;
			uint32_t scanf(const char *format, ...) const TS_SCANF(2, 3);
			
			/// string printf function
			String &vprintf(const char *format, va_list args);
			String &printf(const char *format, ...) TS_PRINTF(2, 3);
			
			template <class... List> String &tprintf(const char *f, List... Args) {
				Array<String> args;
				args.reserve(sizeof...(Args));
				tformat_args(args, Args...);
				while(*f) {
					if(*f == '{' && f[1] >= '0' && f[1] <= '9' && f[2] == '}') {
						uint32_t index = (uint32_t)(f[1] - '0');
						if(index < args.size()) append(args[index]);
						else append(f, 3);
						f += 3;
					} else {
						append(*f++);
					}
				}
				return *this;
			}
			
			/// string format function
			static String vformat(const char *format, va_list args);
			static String format(const char *format, ...) TS_PRINTF(1, 2);
			
			template <class... List> static String tformat(const char *format, List... Args) {
				String ret;
				return ret.tprintf(format, Args...);
			}
			
			/// value to string
			static String &fromi32(String &d, int32_t value, uint32_t radix = 10);
			static String &fromi64(String &d, int64_t value, uint32_t radix = 10);
			static String &fromu32(String &d, uint32_t value, uint32_t radix = 10);
			static String &fromu64(String &d, uint64_t value, uint32_t radix = 10);
			static String &fromf32(String &d, float32_t value, uint32_t digits = 6, bool compact = false, bool exponent = false);
			static String &fromf64(String &d, float64_t value, uint32_t digits = 12, bool compact = false, bool exponent = false);
			
			static String fromi32(int32_t value, uint32_t radix = 10);
			static String fromi64(int64_t value, uint32_t radix = 10);
			static String fromu32(uint32_t value, uint32_t radix = 10);
			static String fromu64(uint64_t value, uint32_t radix = 10);
			static String fromf32(float32_t value, uint32_t digits = 6, bool compact = false, bool exponent = false);
			static String fromf64(float64_t value, uint32_t digits = 12, bool compact = false, bool exponent = false);
			
			/// string to value
			static int32_t toi32(const char *str, uint32_t radix = 10, uint32_t *size = nullptr);
			static int64_t toi64(const char *str, uint32_t radix = 10, uint32_t *size = nullptr);
			static uint32_t tou32(const char *str, uint32_t radix = 10, uint32_t *size = nullptr);
			static uint64_t tou64(const char *str, uint32_t radix = 10, uint32_t *size = nullptr);
			TS_INLINE static int32_t toi32(const char *str, uint32_t *size) { return toi32(str, 10, size); }
			TS_INLINE static int64_t toi64(const char *str, uint32_t *size) { return toi64(str, 10, size); }
			TS_INLINE static uint32_t tou32(const char *str, uint32_t *size) { return tou32(str, 10, size); }
			TS_INLINE static uint64_t tou64(const char *str, uint32_t *size) { return tou64(str, 10, size); }
			static float32_t tof32(const char *str, uint32_t *size = nullptr);
			static float64_t tof64(const char *str, uint32_t *size = nullptr);
			
			int32_t toi32(uint32_t radix = 10, uint32_t pos = 0) const;
			int64_t toi64(uint32_t radix = 10, uint32_t pos = 0) const;
			uint32_t tou32(uint32_t radix = 10, uint32_t pos = 0) const;
			uint64_t tou64(uint32_t radix = 10, uint32_t pos = 0) const;
			float32_t tof32(uint32_t pos = 0) const;
			float64_t tof64(uint32_t pos = 0) const;
			
			/// string to hash value
			uint32_t toHashu32(uint32_t pos = 0) const;
			uint64_t toHashu64(uint32_t pos = 0) const;
			
			/// string to color value
			uint32_t toRGBAu8(uint32_t pos = 0) const;
			
			/// value convertors
			static String fromTime(uint64_t usec, uint32_t digits = 2);
			static String fromBytes(uint64_t bytes, uint32_t digits = 2);
			static String fromNumber(uint64_t value, uint32_t digits = 2);
			static String fromFrequency(uint64_t hz, uint32_t digits = 2);
			static String fromLength(float64_t distance, uint32_t digits = 2);
			static String fromAngle(float64_t angle, uint32_t digits = 2);
			
			static uint64_t toBytes(const char *str, uint32_t *size = nullptr);
			static uint64_t toNumber(const char *str, uint32_t *size = nullptr);
			static uint64_t toFrequency(const char *str, uint32_t *size = nullptr);
			static float64_t toLength(const char *str, uint32_t *size = nullptr);
			
			uint64_t toBytes(uint32_t pos = 0, uint32_t *size = nullptr) const;
			uint64_t toNumber(uint32_t pos = 0, uint32_t *size = nullptr) const;
			uint64_t toFrequency(uint32_t pos = 0, uint32_t *size = nullptr) const;
			float64_t toLength(uint32_t pos = 0, uint32_t *size = nullptr) const;
			
			/// empty string
			static const String null;
			
		private:
			
			/// variadic template arguments
			TS_INLINE static void tformat_args(Array<String> &args) { TS_UNUSED(args); }
			TS_INLINE static void tformat_args(Array<String> &args, const String &arg) { args.append(arg); }
			TS_INLINE static void tformat_args(Array<String> &args, char *arg) { args.append(String(arg)); }
			TS_INLINE static void tformat_args(Array<String> &args, wchar_t *arg) { args.append(String(arg)); }
			TS_INLINE static void tformat_args(Array<String> &args, const char *arg) { args.append(String(arg)); }
			TS_INLINE static void tformat_args(Array<String> &args, const wchar_t *arg) { args.append(String(arg)); }
			TS_INLINE static void tformat_args(Array<String> &args, bool arg) { args.append(String::fromu32(arg)); }
			TS_INLINE static void tformat_args(Array<String> &args, int8_t arg) { args.append(String::fromi32(arg)); }
			TS_INLINE static void tformat_args(Array<String> &args, int16_t arg) { args.append(String::fromi32(arg)); }
			TS_INLINE static void tformat_args(Array<String> &args, int32_t arg) { args.append(String::fromi32(arg)); }
			TS_INLINE static void tformat_args(Array<String> &args, int64_t arg) { args.append(String::fromi64(arg)); }
			TS_INLINE static void tformat_args(Array<String> &args, uint8_t arg) { args.append(String::fromu32(arg)); }
			TS_INLINE static void tformat_args(Array<String> &args, uint16_t arg) { args.append(String::fromu32(arg)); }
			TS_INLINE static void tformat_args(Array<String> &args, uint32_t arg) { args.append(String::fromu32(arg)); }
			TS_INLINE static void tformat_args(Array<String> &args, uint64_t arg) { args.append(String::fromu64(arg)); }
			TS_INLINE static void tformat_args(Array<String> &args, float32_t arg) { args.append(String::fromf32(arg, 6, true)); }
			TS_INLINE static void tformat_args(Array<String> &args, float64_t arg) { args.append(String::fromf64(arg, 12, true)); }
			TS_INLINE static void tformat_args(Array<String> &args, void *arg) { args.append(String::format("%p", arg)); }
			TS_INLINE static void tformat_args(Array<String> &args, const void *arg) { args.append(String::format("%p", arg)); }
			template <class Type> static void tformat_args(Array<String> &args, const Type &arg) { args.append(toString(arg)); }
			template <class... List> static void tformat_args(Array<String> &args, const String &arg, List... Args) { args.append(arg); tformat_args(args, Args...); }
			template <class... List> static void tformat_args(Array<String> &args, char *arg, List... Args) { args.append(String(arg)); tformat_args(args, Args...); }
			template <class... List> static void tformat_args(Array<String> &args, wchar_t *arg, List... Args) { args.append(String(arg)); tformat_args(args, Args...); }
			template <class... List> static void tformat_args(Array<String> &args, const char *arg, List... Args) { args.append(String(arg)); tformat_args(args, Args...); }
			template <class... List> static void tformat_args(Array<String> &args, const wchar_t *arg, List... Args) { args.append(String(arg)); tformat_args(args, Args...); }
			template <class... List> static void tformat_args(Array<String> &args, bool arg, List... Args) { args.append(String::fromu32(arg)); tformat_args(args, Args...); }
			template <class... List> static void tformat_args(Array<String> &args, int8_t arg, List... Args) { args.append(String::fromi32(arg)); tformat_args(args, Args...); }
			template <class... List> static void tformat_args(Array<String> &args, int16_t arg, List... Args) { args.append(String::fromi32(arg)); tformat_args(args, Args...); }
			template <class... List> static void tformat_args(Array<String> &args, int32_t arg, List... Args) { args.append(String::fromi32(arg)); tformat_args(args, Args...); }
			template <class... List> static void tformat_args(Array<String> &args, int64_t arg, List... Args) { args.append(String::fromi64(arg)); tformat_args(args, Args...); }
			template <class... List> static void tformat_args(Array<String> &args, uint8_t arg, List... Args) { args.append(String::fromu32(arg)); tformat_args(args, Args...); }
			template <class... List> static void tformat_args(Array<String> &args, uint16_t arg, List... Args) { args.append(String::fromu32(arg)); tformat_args(args, Args...); }
			template <class... List> static void tformat_args(Array<String> &args, uint32_t arg, List... Args) { args.append(String::fromu32(arg)); tformat_args(args, Args...); }
			template <class... List> static void tformat_args(Array<String> &args, uint64_t arg, List... Args) { args.append(String::fromu64(arg)); tformat_args(args, Args...); }
			template <class... List> static void tformat_args(Array<String> &args, float32_t arg, List... Args) { args.append(String::fromf32(arg, 6, true)); tformat_args(args, Args...); }
			template <class... List> static void tformat_args(Array<String> &args, float64_t arg, List... Args) { args.append(String::fromf64(arg, 12, true)); tformat_args(args, Args...); }
			template <class... List> static void tformat_args(Array<String> &args, void *arg, List... Args) { args.append(String::format("%p", arg)); tformat_args(args, Args...); }
			template <class... List> static void tformat_args(Array<String> &args, const void *arg, List... Args) { args.append(String::format("%p", arg)); tformat_args(args, Args...); }
			template <class Type, class... List> static void tformat_args(Array<String> &args, const Type &arg, List... Args) { args.append(toString(arg)); tformat_args(args, Args...); }
			#if _MACOS || _IOS || _TVOS || _EMSCRIPTEN
				TS_INLINE static void tformat_args(Array<String> &args, size_t arg) { args.append(String::fromu64(arg)); }
				template <class... List> static void tformat_args(Array<String> &args, size_t arg, List... Args) { args.append(String::fromu64(arg)); tformat_args(args, Args...); }
			#endif
	};
	
	/**
	 * String operators
	 */
	TS_API String operator+(const String &s0, const char *s1);
	TS_API String operator+(const char *s0, const String &s1);
	TS_API String operator+(const String &s0, const String &s1);
	
	TS_API bool operator==(const String &s0, const char *s1);
	TS_API bool operator==(const char *s0, const String &s1);
	TS_API bool operator==(const String &s0, const String &s1);
	
	TS_API bool operator!=(const String &s0, const char *s1);
	TS_API bool operator!=(const char *s0, const String &s1);
	TS_API bool operator!=(const String &s0, const String &s1);
	
	TS_API bool operator<(const String &s0, const char *s1);
	TS_API bool operator<(const char *s0, const String &s1);
	TS_API bool operator<(const String &s0, const String &s1);
	
	TS_API bool operator>(const String &s0, const char *s1);
	TS_API bool operator>(const char *s0, const String &s1);
	TS_API bool operator>(const String &s0, const String &s1);
}

#endif /* __TELLUSIM_CORE_STRING_H__ */

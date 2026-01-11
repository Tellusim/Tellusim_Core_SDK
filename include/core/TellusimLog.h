// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_LOG_H__
#define __TELLUSIM_CORE_LOG_H__

#include <TellusimBase.h>

/*
 */
namespace Tellusim {
	
	/**
	 * The Log namespace provides a system for managing and printing log messages at various levels of severity.
	 * It allows setting the current log level and printing messages with different severity levels, such as Fatal, Error, Warning, Message, and Verbose.
	 * The logging system supports both simple and formatted message output and includes the ability to use callbacks for custom logging behavior.
	 */
	namespace Log {
		
		/// Log level
		enum Level {
			Fatal = 0,
			Error,
			Warning,
			Message,
			Verbose,
			Unknown,
			NumLevels,
		};
		
		/// current Log level
		TS_API void setLevel(Level level);
		TS_API Level getLevel();
		
		/// print callback
		using Callback = bool(Level, uint64_t time, const char *str, void *data);
		TS_API void setCallback(Callback *callback, void *data = nullptr);
		TS_API Callback *getCallback();
		TS_API void *getCallbackData();
		TS_API void unlockCallback();
		TS_API void lockCallback();
		
		/// print message
		TS_API void print(const char *str);
		TS_API void vprintf(const char *str, va_list args);
		TS_API void printf(const char *format, ...) TS_PRINTF(1, 2);
		
		/// print message with Level
		TS_API void print(Level level, const char *str);
		TS_API void printe(Level level, const char *str);
		TS_API void vprintf(Level level, const char *str, va_list args);
		TS_API void vprintef(Level level, const char *str, va_list args);
		TS_API void printf(Level level, const char *format, ...) TS_PRINTF(2, 3);
		TS_API void printef(Level level, const char *format, ...) TS_PRINTF(2, 3);
	}
	
	/**
	 * Log system macros
	 */
	#define TS_LOG(LEVEL, STR) Tellusim::Log::print(Tellusim::Log::LEVEL, STR)
	#define TS_LOGE(LEVEL, STR) Tellusim::Log::printe(Tellusim::Log::LEVEL, STR)
	#define TS_LOGF(LEVEL, FORMAT, ...) Tellusim::Log::printf(Tellusim::Log::LEVEL, FORMAT, __VA_ARGS__)
	#define TS_LOGEF(LEVEL, FORMAT, ...) Tellusim::Log::printef(Tellusim::Log::LEVEL, FORMAT, __VA_ARGS__)
	#define TS_LOGT(LEVEL, FORMAT, ...) Tellusim::Log::print(Tellusim::Log::LEVEL, String::tformat(FORMAT, __VA_ARGS__).get())
	#define TS_LOGET(LEVEL, FORMAT, ...) Tellusim::Log::printe(Tellusim::Log::LEVEL, String::tformat(FORMAT, __VA_ARGS__).get())
	
	/**
	 * Log pointer macros
	 */
	#define TS_LOGPTR(LEVEL, STR, PTR) Tellusim::Log::printf(Tellusim::Log::LEVEL, "%sValid: %u; Owner: %u; Const: %u; Count: %u; Internal: %p\n", \
		STR, (PTR).isValidPtr(), (PTR).isOwnerPtr(), (PTR).isConstPtr(), (PTR).getCountPtr(), (PTR).getInternalPtr())
}

#endif /* __TELLUSIM_CORE_LOG_H__ */

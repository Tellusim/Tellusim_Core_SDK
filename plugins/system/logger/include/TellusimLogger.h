// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_SYSTEM_LOGGER_H__
#define __TELLUSIM_PLUGINS_SYSTEM_LOGGER_H__

#include <core/TellusimLog.h>
#include <core/TellusimFile.h>
#include <core/TellusimArray.h>
#include <core/TellusimAtomic.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Logger
	 */
	class Logger {
			
		public:
			
			/// Logger flags
			enum Flags {
				FlagNone = 0,
				FlagDump		= (1 << 0),		// create dump string
				FlagDate		= (1 << 1),		// print date string
				FlagTime		= (1 << 2),		// print time string
				FlagPrint		= (1 << 3),		// print log messages
				FlagLocal		= (1 << 4),		// create local log
				FlagClear		= (1 << 5),		// clear current log
				DefaultFlags	= (FlagDate | FlagTime | FlagPrint),
			};
			
			/// logger constructor
			explicit Logger(Flags flags = DefaultFlags, const char *name = nullptr);
			virtual ~Logger();
			
			/// disable copying
			Logger(const Logger&) = delete;
			Logger &operator=(const Logger&) = delete;
			
			/// logger flags
			void setFlags(Flags f) { flags = f; }
			TS_INLINE Flags getFlags() const { return flags; }
			
			TS_INLINE bool hasFlag(Flags flags) const { return ((getFlags() & flags) != FlagNone); }
			TS_INLINE bool hasFlags(Flags flags) const { return ((getFlags() & flags) == flags); }
			
			/// last log message
			void clearBuffer();
			String getBuffer() const;
			
			/// all log messages
			String getDump() const;
			
			/// log file path
			TS_INLINE const String &getPath() const { return path; }
			
			/// log file name
			TS_INLINE const String &getName() const { return name; }
			
		private:
			
			/// log callback
			static bool callback(Log::Level level, uint64_t time, const char *str, void *data);
			
			enum {
				BufferSize = 4,			// buffer size
			};
			
			Flags flags = FlagNone;		// logger flags
			
			mutable SpinLock lock;		// atomic lock
			
			uint64_t time = 0;			// init time
			
			File file;					// log file
			
			String path;				// log file path
			
			String name;				// log file name
			
			String dump;				// log message dump
			
			Array<String> buffer;		// log messages buffer
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(Logger::Flags)
}

#endif /* __TELLUSIM_PLUGINS_SYSTEM_LOGGER_H__ */

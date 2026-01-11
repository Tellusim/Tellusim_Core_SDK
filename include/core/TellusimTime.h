// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_TIME_H__
#define __TELLUSIM_CORE_TIME_H__

#include <core/TellusimString.h>

/*
 */
namespace Tellusim {
	
	/**
	 * The Time namespace provides functions and constants for handling time-related operations.
	 */
	namespace Time {
		
		enum {
			Seconds = 1000000u,
			MSeconds = 1000u,
			USeconds = 1u,
		};
		
		/// current system time in microseconds
		TS_API uint64_t current();
		
		/// current process time in seconds
		TS_API float64_t seconds();
		
		/// sleep process in microseconds
		TS_API void sleep(uint32_t usec);
	}
	
	/**
	 * The Date class provides a flexible way to handle date and time operations.
	 * It allows for the creation of date objects using a specific timestamp or a formatted string, with options for local or UTC time.
	 * The class offers methods to set and retrieve individual date and time components, such as year, month, day, hours, minutes, and seconds.
	 * Additionally, it supports converting time to and from a string representation, with customizable date formats.
	 * This class enables comprehensive date and time management with various formatting and conversion capabilities.
	 */
	class TS_API Date {
			
			TS_DECLARE_PTR(Date, 0)
			
		public:
			
			Date();
			explicit Date(int64_t time, bool local = true);
			explicit Date(const char *str, const char *format = nullptr);
			
			/// clear date
			void clear();
			
			/// time in seconds since 1970-01-01 00:00:00
			void setTime(int64_t time, bool local = true);
			int64_t getTime(bool local = true) const;
			
			/// string time value
			/// \param format Default time format is yyyy-MM-dd HH:mm:ss
			bool setString(const char *str, const char *format = nullptr);
			String getString(const char *format = nullptr) const;
			
			/// current date
			void setYear(uint32_t year);
			void setMonth(uint32_t month);
			void setDate(uint32_t date);
			void setDay(uint32_t day);
			void setHours(uint32_t hours);
			void setMinutes(uint32_t minutes);
			void setSeconds(uint32_t seconds);
			
			uint32_t getYear() const;
			uint32_t getMonth() const;
			uint32_t getDate() const;
			uint32_t getDay() const;
			uint32_t getHours() const;
			uint32_t getMinutes() const;
			uint32_t getSeconds() const;
			
			/// local timezone in seconds
			static int32_t getTimeZone();
	};
}

#endif /* __TELLUSIM_CORE_TIME_H__ */

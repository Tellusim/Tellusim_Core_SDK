// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimTime.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	if(1) {
		
		TS_LOG(Message, "\n");
		
		TS_LOGF(Message, "Time::current(): %" TS_FORMAT_64 "u\n", Time::current());
		
		TS_LOGF(Message, "Time::seconds(): %f\n", Time::seconds());
		Time::sleep(1000);
		TS_LOGF(Message, "Time::seconds(): %f\n", Time::seconds());
	}
	
	if(1) {
		
		TS_LOG(Message, "\n");
		
		const char *formats[] = {
			"yyyy-MM-dd HH:mm:ss",
			"yyyy-MM-dd dddd HH:mm:ss",
			"yyyy-MM-dd ddd hh:mm:ss tt",
			"yyyy-MM-dd ddd tt hh:mm:ss",
			"\\y\\y-\\M-\\d yy-M-d h:m:s t",
			"\\y\\y-\\M-\\d yy-M-d H:m:s",
		};
		
		for(uint32_t j = 0; j < 60 * 60; j++) {
			Date date = Date(Time::current() / Time::Seconds + j);
			for(uint32_t i = 0; i < TS_COUNTOF(formats); i++) {
				const char *format = formats[i];
				String s0 = date.getString(format);
				String s1 = Date(s0.get(), format).getString(format);
				if(s0 != s1) TS_LOGF(Message, "Error: %s (%s) (%s)\n", s1.get(), s0.get(), format);
				else if(j == 0) TS_LOGF(Message, "%s\n", s1.get());
			}
		}
	}
	
	if(1) {
		
		TS_LOG(Message, "\n");
		
		int64_t time = Time::current() / Time::Seconds;
		
		Date utc_date(time, false);
		Date local_date(time, true);
		
		TS_LOGF(Message, "UTC   %s\n", utc_date.getString().get());
		TS_LOGF(Message, "Local %s\n", local_date.getString().get());
		
		TS_LOGF(Message, "Zone: %d H (%d s)\n", utc_date.getTimeZone() / 60 / 60, utc_date.getTimeZone());
	}
	
	return 0;
}

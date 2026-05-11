// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimString.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	if(1) {
		String str = String("hello long world!!!");
		TS_LOGF(Message, "%s\n", str.replace("l", "LoL").replace("!!", "").get());
		TS_LOGF(Message, "%s\n", str.substring(3, 5).get());
		TS_LOGF(Message, "%s\n", str.reverse(6, 4).reverse(11, 5).get());
	}
	
	if(1) {
		TS_LOG(Message, "\n");
		int32_t value = 0xabcdefab;
		TS_LOGF(Message, "%x %x %s\n",  value, String::fromi32( value, 16).toi32(16), String::fromi32( value, 16).get());
		TS_LOGF(Message, "%x %x %s\n", -value, String::fromi32(-value, 16).toi32(16), String::fromi32(-value, 16).get());
	}
	
	if(1) {
		int32_t value = 123456789;
		TS_LOGF(Message, "%d %d %s\n",  value, String::fromi32( value, 10).toi32(10), String::fromi32( value, 10).get());
		TS_LOGF(Message, "%d %d %s\n", -value, String::fromi32(-value, 10).toi32(10), String::fromi32(-value, 10).get());
	}
	
	if(1) {
		float32_t value = 2.504e25f;
		TS_LOGF(Message, "%f %s %s\n",  value, String::fromf32(value, 6, true, true).get(), String::fromf64(value, 6, true, true).get());
	}
	
	if(1) {
		TS_LOG(Message, "\n");
		String file = String("/path.//./to/../directory/my_file.txt");
		TS_LOGF(Message, "%s\n", file.extension("STR").get());
		TS_LOGF(Message, "%s\n", file.extension().get());
		TS_LOGF(Message, "%s\n", file.pathname().get());
		TS_LOGF(Message, "%s\n", file.basename().get());
		TS_LOGF(Message, "%s\n", file.dirname().get());
	}
	
	if(1) {
		TS_LOG(Message, "\n");
		String path = String::relname("/my/home/one1/two/", "/my/home/one1/another/folder");
		TS_LOGF(Message, "%s\n", path.get());
	}
	
	if(1) {
		TS_LOG(Message, "\n");
		String file = String("path/to/my_file.txt");
		TS_LOGF(Message, "%s\n", file.extension("TXT").get());
		TS_LOGF(Message, "%s\n", file.extension().get());
		TS_LOGF(Message, "%s\n", file.basename().get());
		TS_LOGF(Message, "%s\n", file.dirname().get());
	}
	
	if(1) {
		TS_LOG(Message, "\n");
		TS_LOGF(Message, "%s\n", String::fromAngle(135.135135).get());
		TS_LOGF(Message, "%s\n", String::fromAngle(-135.135135).get());
	}
	
	if(1) {
		TS_LOG(Message, "\n");
		String string_0 = String("right");
		String string_1 = String("left");
		swap(string_0, string_1);
		TS_LOGF(Message, "%s %s\n", string_0.get(), string_1.get());
	}
	
	if(1) {
		TS_LOG(Message, "\n");
		String string;
		{
			String stack = String("String");
			string = move(stack);
			stack = "failed";
		}
		TS_LOGF(Message, "%s <%u>\n", string.get(), string.size());
	}
	
	if(1) {
		TS_LOG(Message, "\n");
		String string = String("ASCII STRING \u0417\u0434\u0440\u0430\u0432\u043e \u0421\u0432\u0435\u0442\u0435 ascii string");
		TS_LOGF(Message, "lower: %s\n", string.lower().get());
		TS_LOGF(Message, "upper: %s\n", string.upper().get());
	}
	
	if(1) {
		TS_LOG(Message, "\n");
		String string = String("this is a big string");
		TS_LOGF(Message, "d0: %u\n", string.distance("this is"));
		TS_LOGF(Message, "d1: %u\n", string.distance("is a big"));
		TS_LOGF(Message, "d2: %u\n", string.distance("big string"));
	}
	
	if(1) {
		TS_LOG(Message, "\n");
		String string = String("ascii string xyz value_x value_y");
		TS_LOGF(Message, "capitalize: %s\n", string.capitalize().get());
		TS_LOGF(Message, "capitalize: %s\n", string.capitalize(" ").get());
		TS_LOGF(Message, "capitalize: %s\n", string.capitalize(" _").get());
		TS_LOGF(Message, "capitalize: %s\n", string.capitalize(" ", "_").get());
	}
	
	if(1) {
		TS_LOG(Message, "\n");
		String string = String("this is a string");
		const char *patterns[] = {
			"this is a string",
			"this is ? string",
			"this is a *",
			"this is *in?",
			"this is a * ",
			"this is *in? ",
			"th?s is ? strin",
			"this is ? string ",
			"this is string| this is*|this is*",
		};
		for(uint32_t i = 0; i < TS_COUNTOF(patterns); i++) {
			TS_LOGF(Message, "match: %u: %s\n", string.match(patterns[i]), patterns[i]);
		}
	}
	
	if(1) {
		TS_LOG(Message, "\n");
		TS_LOGF(Message, "tformat: %s\n", String::tformat("Hello {1}::{0}", "tformat", "String").get());
		TS_LOGF(Message, "tformat: %s\n", String::tformat("{2} = {0} + {1}", 4, 8, 4 + 8).get());
		TS_LOGF(Message, "tformat: %s\n", String::tformat("{2} = {0} + {1}", 4.5f, 8.5f, 4.5f + 8.5f).get());
	}
	
	return 0;
}

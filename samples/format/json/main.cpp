// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <format/TellusimJson.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	if(1) {
		
		Json root("root");
		
		root.setData("null", nullptr);
		root.setData("bool_true", true);
		root.setData("bool_false", false);
		root.setData("number_int32", -113);
		root.setData("number_uint32", 113);
		root.setData("number_float32", 113.133f);
		root.setData("string", "this is a string");
		
		Json object(&root, "object");
		object.setData("first", "first string");
		object.setData("second", "second string");
		
		Json null_array(&root, "null_array");
		null_array.setData(nullptr, nullptr);
		null_array.setData(nullptr, nullptr);
		null_array.setData(nullptr, nullptr);
		
		Json bool_array(&root, "bool_array");
		bool_array.setData(nullptr, true);
		bool_array.setData(nullptr, false);
		bool_array.setData(nullptr, true);
		
		Json number_array(&root, "number_array");
		number_array.setData(nullptr, 0.0f);
		number_array.setData(nullptr, 1.0f);
		number_array.setData(nullptr, 2.0f);
		number_array.setData(nullptr, 3.0f);
		
		Json string_array(&root, "string_array");
		string_array.setData(nullptr, "first");
		string_array.setData(nullptr, "second");
		string_array.setData(nullptr, "third");
		
		Json object_array(&root, "object_array");
		
		Json(&object_array, nullptr).setData("first", "second");
		Json(&object_array, nullptr).setData("third", "fourth");
		
		Json mixed_array(&root, "mixed_array");
		mixed_array.setData(nullptr, nullptr);
		mixed_array.setData(nullptr, true);
		mixed_array.setData(nullptr, 1.0f);
		mixed_array.setData(nullptr, "first");
		Json(&mixed_array, nullptr, Json::TypeObject);
		Json(&mixed_array, nullptr, Json::TypeArray);
		
		Json copy = root.clonePtr();
		TS_LOGPTR(Message, "root: ", root);
		TS_LOGPTR(Message, "copy: ", copy);
		if(!copy.save("test_save_a.json")) return 1;
	}
	
	if(1) {
		
		Json json;
		if(!json.load("test_load.json")) return 1;
		
		Json copy = json.clonePtr();
		TS_LOGPTR(Message, "json: ", json);
		TS_LOGPTR(Message, "copy: ", copy);
		if(!copy.save("test_save_b.json")) return 1;
	}
	
	return 0;
}

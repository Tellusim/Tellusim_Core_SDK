// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <format/TellusimXml.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	if(1) {
		
		Xml root("root", "version=\"2\"");
		root.setAttribute("attribute", "root");
		Xml(&root, "!-- comment line--");
		
		Xml first(&root, "first", "one=\"<one>\" two=\"&quot;two&quot;\"");
		first.setData("<first data>");
		
		Xml second(&root, "second");
		second.setAttribute("one", "one");
		second.setAttribute("two", "two");
		Xml(&second, "![CDATA[second data]]");
		
		Xml third(&root, "third", "one=\"one\" two=\"two\"");
		third.setData("\"third data\"");
		
		Xml fourth(&root, "fourth", "one=\"one\" two=\"two\"");
		fourth.setData("fifth", "'fifth data'");
		fourth.setData("sixth", "@@");
		fourth.setData("seventh", "/path/to/file");
		
		Xml copy = root.clonePtr();
		TS_LOGPTR(Message, "root: ", root);
		TS_LOGPTR(Message, "copy: ", copy);
		if(!copy.save("test_save_a.xml")) return 1;
		
		for(const Xml &xml : root.getChildren()) {
			TS_LOGF(Message, "%s\n", xml.getName().get());
		}
	}
	
	if(1) {
		
		Xml xml;
		if(!xml.load("test_load.xml")) return 1;
		
		Xml copy = xml.clonePtr();
		TS_LOGPTR(Message, " xml: ", xml);
		TS_LOGPTR(Message, "copy: ", copy);
		if(!copy.save("test_save_b.xml")) return 1;
	}
	
	return 0;
}

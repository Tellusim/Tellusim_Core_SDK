// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimFile.h>
#include <core/TellusimBlob.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// zip compression
	if(1) {
		
		Blob blob;
		
		blob.writei32e(63);
		blob.writei32e(-63);
		blob.writei32e(8192);
		blob.writei32e(-8192);
		blob.writei32e(1048575);
		blob.writei32e(-1048575);
		blob.writei32e(134217727);
		blob.writei32e(-134217727);
		blob.writei32e(2147483647);
		blob.writei32e(-2147483647);
		blob.writeu32e(0x0000007fu);
		blob.writeu32e(0x00003fffu);
		blob.writeu32e(0x001fffffu);
		blob.writeu32e(0x0fffffffu);
		blob.writeu32e(0xffffffffu);
		
		blob.seek(0);
		Blob zip_blob;
		if(!blob.encodeZip(zip_blob)) return 2;
		
		blob.clear();
		zip_blob.seek(0);
		if(!blob.decodeZip(zip_blob)) return 3;
		TS_LOGF(Message, "%u->%u\n", (uint32_t)blob.getSize(), (uint32_t)zip_blob.getSize());
		
		blob.seek(0);
		for(uint32_t i = 0; i < 10; i++) {
			TS_LOGF(Message, "%d\n", blob.readi32e());
		}
		for(uint32_t i = 0; i < 5; i++) {
			TS_LOGF(Message, "%08x\n", blob.readu32e());
		}
	}
	
	// message digest algorithm
	if(1) {
		
		TS_LOG(Message, "\n");
		
		Blob blob;
		File file;
		if(!file.open("main.cpp", "rb")) return 1;
		blob.writeStream(file);
		file.close();
		
		blob.seek(0);
		TS_LOGF(Message, "MD5: %s\n", blob.getMD5().get());
	}
	
	// secure hash algorithm
	if(1) {
		
		TS_LOG(Message, "\n");
		
		Blob blob;
		File file;
		if(!file.open("main.cpp", "rb")) return 1;
		blob.writeStream(file);
		file.close();
		
		blob.seek(0);
		TS_LOGF(Message, "SHA1: %s\n", blob.getSHA1().get());
	}
	
	return 0;
}

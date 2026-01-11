// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <core/TellusimBlob.h>
#include <core/TellusimFile.h>
#include <core/TellusimSource.h>
#include <core/TellusimArray.h>
#include <math/TellusimScalar.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// print help
	if(argc < 2 || String(argv[1]) == "-h") {
		Log::printf("Tellusim Blob File Creator (build " __DATE__ " https://tellusim.com/)\nUsage: %s file.txt file.png\n", argv[0]);
		Log::print("  -force    Force blob creation\n");
		Log::print("  -src      Create source blob\n");
		Log::print("  -cpp      Create cpp blob\n");
		Log::print("  -o (name) Output file\n");
		return 0;
	}
	
	// blob files
	String output;
	Array<String> names;
	
	// command options
	bool force = false;
	bool is_src = false;
	bool is_cpp = false;
	
	// command line arguments
	for(int32_t i = 1; i < argc; i++) {
		const char *s = argv[i];
		if(s[0] == '-') {
			while(*s == '-') s++;
			String command = String(s);
			if(command == "force") force = true;
			else if(command == "f") force = true;
			else if(command == "src") is_src = true;
			else if(command == "cpp") is_cpp = true;
			else if(command == "o" && i + 1 < argc) output = String(argv[++i]).extension("blob");
			else TS_LOGF(Warning, "%s: invalid command line option \"%s\"\n", argv[0], argv[i]);
		} else {
			names.append(String(s));
		}
	}
	
	// blob file
	File blob_file;
	File cpp_file;
	
	// compress files
	for(const String &name : names) {
		
		// source modification time
		uint64_t mtime = File::getMTime(name.get());
		
		// open source file
		File src_file;
		if(!src_file.open(name, "rb")) {
			TS_LOGF(Error, "%s: can't open \"%s\" file\n", argv[0], name.get());
			continue;
		}
		
		// read source file
		Blob src_blob;
		src_file.readStream(src_blob);
		src_file.close();
		
		// check source file size
		if(src_blob.getSize() == 0) {
			TS_LOGF(Error, "%s: empty \"%s\" file\n", argv[0], name.get());
			continue;
		}
		
		// source checksum
		src_blob.seek(0);
		String sha1 = src_blob.getSHA1();
		
		// find old checksum
		if(!force && (!output || names.size() == 1)) {
			Source source;
			String target = output ? output : name.extension("blob");
			if(Source::isSource(target) && source.open(target)) {
				String line;
				while(source.readLine(line) && line.begins("//")) {
					if(line.begins("// SHA1: ")) {
						if(sha1 == line.get() + 9) {
							TS_LOGF(Message, "%s: skip %s file\n", argv[0], name.get());
							src_blob.clear();
						}
						break;
					}
				}
			}
			if(src_blob.getSize() == 0) continue;
		}
		
		// source blob
		if(is_src) {
			src_blob.seek(0);
			String src = src_blob.gets();
			char *d = src.get();
			for(const char *s = src.get(); *s;) {
				if(*s == '/' && s[1] == '/') {
					while(*s && *s != '\n') s++;
				} else if(*s == '/' && s[1] == '*') {
					while(*s && (*s != '*' || s[1] != '/')) s++;
					if(*s == '*' && s[1] == '/') s += 2;
				} else if(*s == '\t') {
					*d++ = ' ';
					s++;
				} else {
					*d++ = *s++;
				}
			}
			*d++ = '\0';
			d = src.get();
			const char *delimiters = "+-*/%&|^<>?!=,.;:{}()[]";
			for(const char *s = src.get(); *s;) {
				bool new_line = (d > src.get() && d[-1] == '\n');
				if(*s == '\n') {
					if(new_line || d == src.get()) s++;
					else *d++ = *s++;
				} else if(*s == ' ' && new_line) {
					while(*s == ' ') s++;
				} else if(*s == ' ' && s[1] == ' ') {
					s++;
				} else if(*s && strchr(delimiters, *s) && s[1] == ' ') {
					*d++ = *s++; s++;
					while(*s == ' ') s++;
				} else if(*s == ' ' && s[1] && strchr(delimiters, s[1])) {
					s++; *d++ = *s++;
					while(*s == ' ') s++;
				} else if(*s == '}' && new_line) {
					if(d > src.get() + 1 && d[-2] == '}') { d[-1] = *s++; *d++ = '\n'; }
					else *d++ = *s++;
				} else if(*s == '\\' && s[1] == '\n') {
					s += 2;
				} else if(*s == '"' && (s == src.get() || s[-1] != '\\')) {
					*d++ = *s++;
					while(*s && (*s != '"' || s[-1] == '\\')) *d++ = *s++;
					if(*s == '"') *d++ = *s++;
				} else {
					*d++ = *s++;
				}
			}
			*d++ = '\0';
			src_blob.clear();
			src_blob.puts(src.get());
		}
		
		// compress blob
		Blob zip_blob;
		bool status = true;
		src_blob.seek(0);
		src_blob.encodeZipBest(zip_blob, src_blob.getSize(), &status);
		if(status == false) {
			TS_LOGF(Error, "%s: can't compress \"%s\" file\n", argv[0], name.get());
			continue;
		}
		src_file.close();
		
		// open blob file
		if(!blob_file || !blob_file.isOpened()) {
			String target = output ? output : name.extension("blob");
			if(!blob_file.open(target, "wb")) {
				TS_LOGF(Error, "%s: can't create \"%s\" file\n", argv[0], target.get());
				continue;
			}
			if(is_cpp) {
				if(!cpp_file.open(target.extension("cpp"), "wb")) {
					TS_LOGF(Error, "%s: can't create \"%s\" file\n", argv[0], target.extension("cpp").get());
					return 1;
				}
				cpp_file.puts("#include <cstdint>\n\n");
				cpp_file.puts("namespace Tellusim {\n");
				cpp_file.printf("\t#include \"%s\"\n", target.basename().get());
			}
		}
		
		// variable name
		String variable = name.basename().extension("blob").replace(".", "_");
		
		// write blob
		String data;
		zip_blob.seek(0);
		blob_file.printf("// %s\n", name.get());
		blob_file.printf("// SHA1: %s\n", sha1.get());
		blob_file.printf("// File: %s\n", Date(mtime).getString("MMM d yyyy").get());
		blob_file.printf("// Date: %s\n", Date(Time::current() / Time::Seconds).getString("MMM d yyyy").get());
		blob_file.printf("// Size: %s -> %s\n", String::fromBytes(src_blob.getSize()).get(), String::fromBytes(zip_blob.getSize()).get());
		blob_file.printf("static const uint8_t %s_%s[][256] = {\n", variable.get(), (cpp_file) ? "data" : "src");
		for(size_t i = 0; i < zip_blob.getSize();) {
			uint32_t size = (uint32_t)min(zip_blob.getSize() - zip_blob.tell(), (size_t)254);
			if(size == 0) break;
			data = String::format("\t{ %u", 254 - size);
			for(uint32_t j = 0; j < size; j++) {
				String::fromu32(data.append(','), zip_blob.readu8());
			}
			blob_file.puts(data.append(" },\n"));
			i += size;
		}
		blob_file.puts("\t{ 255 }\n};\n");
		
		// cpp file
		if(cpp_file) {
			cpp_file.printf("\tconst uint8_t (*%s_src)[256] = %s_data;\n", variable.get(), variable.get());
		}
		
		TS_LOGF(Message, "%s (%s) -> %s (%s)\n", name.get(), String::fromBytes(src_blob.getSize()).get(), blob_file.getName().get(), String::fromBytes(zip_blob.getSize()).get());
		
		// close blob file if there is no output file
		if(!output) {
			blob_file.close();
			if(cpp_file && cpp_file.isOpened()) {
				cpp_file.puts("}\n");
				cpp_file.close();
			}
		}
	}
	
	// close cpp file if it is still opened
	if(cpp_file && cpp_file.isOpened()) {
		cpp_file.puts("}\n");
		cpp_file.close();
	}
	
	return 0;
}

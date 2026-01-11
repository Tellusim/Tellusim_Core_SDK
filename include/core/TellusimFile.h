// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_FILE_H__
#define __TELLUSIM_CORE_FILE_H__

#include <core/TellusimStream.h>

/*
 */
namespace Tellusim {
	
	/**
	 * The File class extends the Stream class and provides a specialized implementation for managing files in a system.
	 * It offers functionality for opening, reading, writing, and closing files, along with managing the file status, position, and size.
	 * The class supports file operations using both file descriptors and file names, and it includes utilities for retrieving file status and performing manipulations.
	 */
	class TS_API File : public Stream {
			
			TS_DECLARE_PTR_0(File, 0)
			
		public:
			
			File();
			
			/// open/close file
			bool open(const char *name, const char *mode);
			bool open(const String &name, const char *mode);
			bool open(int32_t fd, const char *name, const char *mode);
			bool popen(const char *command, const char *mode);
			bool popen(const String &command, const char *mode);
			void close();
			
			/// file utils
			static bool isFile(const char *name);
			static bool isFile(const String &name);
			static uint64_t getMTime(const char *name);
			static size_t getSize(const char *name);
			static bool remove(const char *name);
			
			using Stream::getSize;
	};
}

#endif /* __TELLUSIM_CORE_FILE_H__ */

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_SOURCE_H__
#define __TELLUSIM_CORE_SOURCE_H__

#include <core/TellusimStream.h>

/*
 */
namespace Tellusim {
	
	/**
	 * The Source class extends the Stream class and provides functionality for managing data from memory-mapped files or raw memory pointers.
	 * It supports operations for opening and closing sources, setting data, and querying the source name and size.
	 * The class also allows defining custom callbacks for opening and validating user-defined sources.
	 */
	class TS_API Source : public Stream {
			
			TS_DECLARE_PTR_0(Source, 0)
			
		public:
			
			Source();
			Source(const uint8_t *data, size_t size, const char *name = nullptr);
			
			/// open/close source
			bool open(const char *name, bool callback = true, bool write = false);
			bool open(const String &name, bool callback = true, bool write = false);
			void close();
			
			/// source name
			void setName(const char *name, size_t offset, size_t size);
			void setName(const String &name, size_t offset, size_t size);
			
			/// source data
			void setData(const uint8_t *data, size_t size, const char *name = nullptr);
			
			/// source utils
			static bool isSource(const char *name);
			static bool isSource(const String &name);
			static uint64_t getMTime(const char *name);
			static size_t getSize(const char *name);
			
			/// source callback
			using IsCallback = bool(const char *name, void *data);
			using OpenCallback = Stream(const char *name, void *data);
			static void setCallback(OpenCallback *open_func, void *data = nullptr);
			static void setCallback(OpenCallback *open_func, IsCallback *is_func, void *data = nullptr);
			static OpenCallback *getOpenCallback();
			static IsCallback *getIsCallback();
			static void *getCallbackData();
			
			using Stream::getSize;
	};
}

#endif /* __TELLUSIM_CORE_SOURCE_H__ */

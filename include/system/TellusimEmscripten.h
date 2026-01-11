// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_SYSTEM_EMSCRIPTEN_H__
#define __TELLUSIM_SYSTEM_EMSCRIPTEN_H__

#include <core/TellusimFunction.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Blob;
	class String;
	
	/**
	 * The Emscripten namespace provides functions for interacting with JavaScript and the browser in an Emscripten environment.
	 * It includes utilities for running scripts, displaying alert dialogs, saving and loading user files, and performing asynchronous fetch operations.
	 * These features enable seamless integration of native code with web-based functionalities.
	 */
	namespace Emscripten {
		
		/// run script
		TS_API void run(const char *src);
		TS_API int32_t runi32(const char *src);
		TS_API const char *runs(const char *src);
		
		/// alert dialog
		TS_API void alert(const char *message);
		TS_API void alert(const String &message);
		TS_API void alertf(const char *format, ...) TS_PRINTF(1, 2);
		
		/// save user file
		TS_API void save(const Blob &blob, const char *mime = nullptr);
		
		/// load user file
		using LoadedCallback = Function<void(Blob blob)>;
		TS_API void load(const LoadedCallback &func, const char *type = nullptr);
		
		/// asynchronous fetch
		using ProgressCallback = Function<void(uint32_t progress, uint32_t total)>;
		using FetchedCallback = Function<void(const uint8_t *data, size_t size, uint32_t status)>;
		TS_API void fetch(const char *name, const FetchedCallback &fetched_func, const ProgressCallback &progress_func, bool cache = false);
		TS_API void fetch(const String &name, const FetchedCallback &fetched_func, const ProgressCallback &progress_func, bool cache = false);
	}
}

#endif /* __TELLUSIM_SYSTEM_EMSCRIPTEN_H__ */

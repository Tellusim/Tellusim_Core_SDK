// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

/*
 */
#ifndef __TELLUSIM_SYSTEM_ANDROID_H__
#define __TELLUSIM_SYSTEM_ANDROID_H__

#include <core/TellusimString.h>

/*
 */
struct ANativeActivity;
struct ANativeWindow;

/*
 */
namespace Tellusim {
	
	/**
	 * The Android namespace provides access to essential Android platform features, including native activity management,
	 * lifecycle status checks, window and screen properties, application package and directory paths,
	 * and initialization of the native entry point via the onCreate function.
	 */
	namespace Android {
		
		/// Android activity
		TS_API ANativeActivity *getActivity();
		
		TS_API bool isCreated();
		TS_API bool isResumed();
		TS_API bool isFocused();
		
		/// Android window
		TS_API ANativeWindow *getWindow();
		
		TS_API int32_t getWidth();
		TS_API int32_t getHeight();
		TS_API int32_t getFormat();
		
		/// application package name
		TS_API String getPackageName();
		
		/// application directories
		TS_API String getHomeDirectory();
		TS_API String getFilesDirectory();
		TS_API String getCacheDirectory();
		TS_API String getCardDirectory();
		TS_API String getObbDirectory();
		
		/// Android native activity
		using Main = int32_t(int32_t argc, char **argv);
		TS_API void onCreate(ANativeActivity *activity, void *state, size_t size, Main *main);
	}
}

/*
 */
#define TS_DECLARE_ANDROID_NATIVE_ACTIVITY \
extern int32_t main(int32_t argc, char **argv); \
extern "C" __attribute__((visibility("default"))) void ANativeActivity_onCreate(ANativeActivity *activity, void *state, size_t size) { \
	Tellusim::Android::onCreate(activity, state, size, ::main); \
}

#endif /* __TELLUSIM_SYSTEM_ANDROID_H__ */

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

/*
 */
#ifndef __TELLUSIM_SYSTEM_WINDOWS_H__
#define __TELLUSIM_SYSTEM_WINDOWS_H__

#if _WIN32
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
	#include <windows.h>
#else
	#define __stdcall
#endif

#include <core/TellusimString.h>

/*
 */
namespace Tellusim {
	
	/**
	 * The Windows namespace provides functions for managing Windows application instances, console windows, and their properties.
	 * It includes operations to create and configure a console window, set its title and geometry, check its visibility, and access console handle and status.
	 * The namespace also defines a main entry point for Windows applications.
	 */
	namespace Windows {
		
		/// application instance
		TS_API void *getInstance();
		
		/// application show mode
		TS_API int32_t getShowMode();
		
		/// console window handle
		TS_API void *getConsoleHandle();
		
		/// check console status
		TS_API bool isConsoleCreated();
		
		/// create console window
		TS_API bool createConsole(const char *title, uint32_t width = 0, uint32_t height = 0, int32_t x = Maxi32, int32_t y = Maxi32);
		TS_API bool createConsole(const String &title, uint32_t width = 0, uint32_t height = 0, int32_t x = Maxi32, int32_t y = Maxi32);
		
		/// set console title
		TS_API void setConsoleTitle(const char *title);
		TS_API void setConsoleTitle(const String &title);
		TS_API String getConsoleTitle();
		
		/// console geometry
		TS_API void setConsoleGeometry(uint32_t width, uint32_t height, int32_t x = Maxi32, int32_t y = Maxi32);
		TS_API uint32_t getConsoleWidth();
		TS_API uint32_t getConsoleHeight();
		TS_API int32_t getConsolePositionX();
		TS_API int32_t getConsolePositionY();
		
		/// hide console window
		TS_API void setConsoleHidden(bool hidden);
		TS_API bool isConsoleHidden();
		
		/// Windows main
		using Main = int32_t(int32_t argc, char **argv);
		TS_API void main(void *instance, void *prev_instance, wchar_t *command, int32_t show_mode, Main *main);
	}
}

/*
 */
#define TS_DECLARE_WINDOWS_HIGH_PERFORMANCE \
extern "C" _declspec(dllexport) uint32_t NvOptimusEnablement = 1; \
extern "C" _declspec(dllexport) uint32_t AmdPowerXpressRequestHighPerformance = 1;

/*
 */
#ifdef DECLARE_HANDLE
	#define TS_HINSTANCE
#else
	#define TS_HINSTANCE struct HINSTANCE__ { int32_t unused; }; typedef HINSTANCE__ *HINSTANCE;
#endif
#define TS_DECLARE_WINDOWS_MAIN TS_HINSTANCE \
extern int32_t main(int32_t argc, char **argv); \
int32_t __stdcall wWinMain(HINSTANCE instance, HINSTANCE prev_instance, wchar_t *command, int32_t show_mode) { \
	Tellusim::Windows::main((void*)instance, (void*)prev_instance, command, show_mode, ::main); \
}

#endif /* __TELLUSIM_SYSTEM_WINDOWS_H__ */

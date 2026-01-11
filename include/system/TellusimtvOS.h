// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

/*
 */
#ifndef __TELLUSIM_SYSTEM_TVOS_H__
#define __TELLUSIM_SYSTEM_TVOS_H__

#include <core/TellusimString.h>

/*
 */
namespace Tellusim {
	
	/**
	 * The tvOS namespace provides access to key tvOS platform features, including screen size, device information, virtual keyboard management, and application directory paths.
	 * It also includes functions for managing the application lifecycle and opening URLs.
	 */
	namespace tvOS {
		
		/// tvOS application
		TS_API void *getApplication();
		
		TS_API bool isCreated();
		TS_API bool isFocused();
		
		/// screen size
		TS_API uint32_t getWidth();
		TS_API uint32_t getHeight();
		TS_API float32_t getScale();
		
		/// device info
		TS_API String getModel();
		
		/// virtual keyboard
		TS_API bool setKeyboardHidden(bool hidden);
		TS_API bool isKeyboardHidden();
		
		/// application home directory
		TS_API String getHomeDirectory();
		
		/// application caches directory
		TS_API String getCachesDirectory();
		
		/// application documents directory
		TS_API String getDocumentsDirectory();
		
		/// open url
		TS_API bool openUrl(const char *name);
		TS_API bool openUrl(const String &name);
	}
}

#endif /* __TELLUSIM_SYSTEM_TVOS_H__ */

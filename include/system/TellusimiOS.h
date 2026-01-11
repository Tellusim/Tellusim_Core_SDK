// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

/*
 */
#ifndef __TELLUSIM_SYSTEM_IOS_H__
#define __TELLUSIM_SYSTEM_IOS_H__

#include <core/TellusimString.h>

/*
 */
namespace Tellusim {
	
	/**
	 * The iOS namespace provides access to key iOS platform features, including device orientation, screen size,
	 * device information, virtual keyboard management, and application directory paths.
	 * It also includes functions for managing the application lifecycle and opening URLs.
	 */
	namespace iOS {
		
		/// Device orientation
		enum Orientation {
			OrientationUnknown = 0,
			OrientationPortrait,
			OrientationPortraitUpsideDown,
			OrientationLandscapeLeft,
			OrientationLandscapeRight,
			OrientationFaceUp,
			OrientationFaceDown,
		};
		
		/// iOS application
		TS_API void *getApplication();
		
		TS_API bool isCreated();
		TS_API bool isFocused();
		
		/// screen size
		TS_API uint32_t getWidth();
		TS_API uint32_t getHeight();
		TS_API float32_t getScale();
		
		/// device info
		TS_API String getModel();
		TS_API Orientation getOrientation();
		
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

#endif /* __TELLUSIM_SYSTEM_IOS_H__ */

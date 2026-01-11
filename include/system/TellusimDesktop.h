// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_SYSTEM_DESKTOP_H__
#define __TELLUSIM_SYSTEM_DESKTOP_H__

#include <core/TellusimString.h>

/*
 */
namespace Tellusim {
	
	/**
	 * The Desktop class provides methods to interact with the desktop environment and screen configurations on Windows, Linux, and macOS.
	 * It allows for adjusting screen resolution and position, querying screen details, and managing multiple screens and their settings.
	 * Additionally, it provides functionality for setting and retrieving the mouse position.
	 */
	class TS_API Desktop {
			
			TS_DECLARE_PTR(Desktop, 0)
			
		public:
			
			Desktop();
			
			/// update configuration
			bool update();
			
			/// desktop resolution
			uint32_t getWidth() const;
			uint32_t getHeight() const;
			int32_t getPositionX() const;
			int32_t getPositionY() const;
			float32_t getScale() const;
			
			/// screen configuration
			uint32_t getNumScreens() const;
			String getScreenName(uint32_t index) const;
			String getScreenDevice(uint32_t index) const;
			uint32_t getScreenWidth(uint32_t index) const;
			uint32_t getScreenHeight(uint32_t index) const;
			int32_t getScreenPositionX(uint32_t index) const;
			int32_t getScreenPositionY(uint32_t index) const;
			uint32_t getScreenFrequency(uint32_t index) const;
			
			/// screen video modes
			uint32_t getNumModes(uint32_t index) const;
			uint32_t getModeWidth(uint32_t index, uint32_t mode) const;
			uint32_t getModeHeight(uint32_t index, uint32_t mode) const;
			
			/// change screen resolution
			uint32_t getModeIndex(uint32_t index, uint32_t width, uint32_t height) const;
			bool setMode(uint32_t index, uint32_t width, uint32_t height);
			bool restoreMode(uint32_t index);
			
			/// current screen configuration
			uint32_t getWidth(uint32_t index) const;
			uint32_t getHeight(uint32_t index) const;
			int32_t getPositionX(uint32_t index) const;
			int32_t getPositionY(uint32_t index) const;
			
			/// get current screen index
			uint32_t getScreenIndex(int32_t x, int32_t y) const;
			
			/// mouse position
			bool setMouse(int32_t x, int32_t y) const;
			bool getMouse(int32_t &x, int32_t &y) const;
	};
}

#endif /* __TELLUSIM_SYSTEM_DESKTOP_H__ */

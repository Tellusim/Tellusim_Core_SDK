// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <system/TellusimDesktop.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	Desktop desktop;
	
	if(1) {
		
		TS_LOGF(Message, "desktop %ux%u\n", desktop.getWidth(), desktop.getHeight());
	}
	
	if(1) {
		
		for(uint32_t i = 0; i < desktop.getNumScreens(); i++) {
			TS_LOGF(Message, "screen %2d: %d, %d: %ux%u\n", i, desktop.getPositionX(i), desktop.getPositionY(i), desktop.getWidth(i), desktop.getHeight(i));
			TS_LOGF(Message, "\"%s\" / \"%s\"\n", desktop.getScreenName(i).get(), desktop.getScreenDevice(i).get());
			for(uint32_t j = 0; j < desktop.getNumModes(i); j++) {
				uint32_t width = desktop.getModeWidth(i, j);
				uint32_t height = desktop.getModeHeight(i, j);
				TS_LOGF(Message, "\tmode %2d: %4ux%u\n", j, width, height);
			}
		}
	}
	
	if(1) {
		
		uint32_t screen = 0;
		uint32_t width = 1280;
		uint32_t height = 720;
		uint32_t mode = desktop.getModeIndex(screen, width, height);
		if(mode != Maxu32 && desktop.setMode(screen, desktop.getModeWidth(screen, mode), desktop.getModeHeight(screen, mode))) {
			Time::sleep(Time::Seconds);
			TS_LOG(Message, "set mode ok\n");
			for(uint32_t i = 0; i < desktop.getNumScreens(); i++) {
				TS_LOGF(Message, "screen %2d: %d, %d: %ux%u\n", i, desktop.getPositionX(i), desktop.getPositionY(i), desktop.getWidth(i), desktop.getHeight(i));
			}
			if(desktop.restoreMode(screen)) {
				Time::sleep(Time::Seconds);
				TS_LOG(Message, "restore mode ok\n");
				for(uint32_t i = 0; i < desktop.getNumScreens(); i++) {
					TS_LOGF(Message, "screen %2d: %d, %d: %ux%u\n", i, desktop.getPositionX(i), desktop.getPositionY(i), desktop.getWidth(i), desktop.getHeight(i));
				}
			}
		}
	}
	
	if(1) {
		
		int32_t x, y;
		int32_t dx = 1;
		int32_t dy = 1;
		int32_t size = 128;
		desktop.getMouse(x, y);
		TS_LOGF(Message, "mouse: %dx%d\n", x, y);
		for(int32_t i = 0; i <= size * 4; i++) {
			Time::sleep(Time::MSeconds * 2);
			desktop.setMouse(x, y);
			if(i == size * 1) dx = -1;
			if(i == size * 2) dy = -1;
			if(i == size * 3) dx =  1;
			x += dx;
			y += dy;
		}
	}
	
	return 0;
}

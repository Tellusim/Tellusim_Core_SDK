// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <interface/TellusimDialogs.h>

/*
 */
#if _ANDROID || _IOS
	#define PLATFORM	PlatformAny
#else
	#define PLATFORM	PlatformUnknown
#endif

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create window
	Window window = Window(PlatformAny);
	if(!window || !window.create("Tellusim::Dialogs")) return 1;
	if(!window.setSize(512, 256) || !window.setHidden(false)) return 1;
	
	// window callbacks
	window.setCloseClickedCallback([&]() { window.stop(); });
	
	// update callback
	auto update_func = makeFunction([&]() {
		
		using Tellusim::abs;
		using Tellusim::sin;
		using Tellusim::cos;
		
		float32_t time = (float32_t)Time::seconds();
		
		window.clear(Color(abs(sin(time)), abs(cos(time * 0.7f)), abs(sin(time * 0.5f) * cos(time * 0.3f)), 1.0f));
		
		Time::sleep(1000);
		
		return true;
	});
	
	// menu parameters
	uint32_t index_0 = 0;
	uint32_t index_1 = 0;
	bool is_hidden = false;
	bool is_checked = true;
	
	// keyboard pressed callback
	window.setKeyboardPressedCallback([&](uint32_t key, uint32_t code) {
		
		// message dialog
		if(code == 'i') {
			DialogMessage dialog("DialogMessage", "Hello Message");
			dialog.setUpdateCallback(update_func);
			DialogMessage::Result res_0 = dialog.run(DialogMessage::FlagMessage | DialogMessage::FlagYesNo | DialogMessage::FlagMouse);
			DialogMessage::Result res_1 = dialog.run(DialogMessage::FlagWarning | DialogMessage::FlagOkCancel);
			TS_LOGF(Message, "DialogMessage: %u %u | %d %d\n", res_0, res_1, dialog.getPositionX(), dialog.getPositionY());
		}
		
		// file open dialog
		if(code == 'o') {
			DialogFileOpen dialog("DialogFileOpen");
			dialog.setFilter("All files\n*\nSource files\n.cpp.h\nImage files\n.png.jpg.dds");
			dialog.setUpdateCallback(update_func);
			DialogFileOpen::Result res_0 = dialog.run(DialogFileOpen::FlagHidden | DialogFileOpen::FlagMouse);
			DialogFileOpen::Result res_1 = dialog.run();
			TS_LOGF(Message, "DialogFileOpen: %u %u | %d %d %s\n", res_0, res_1, dialog.getPositionX(), dialog.getPositionY(), dialog.getFile().get());
		}
		
		// file save dialog
		if(code == 's') {
			DialogFileSave dialog("DialogFileSave");
			dialog.setFilter("All files\n*\n.cpp.h\n.png.jpg.dds");
			dialog.setUpdateCallback(update_func);
			DialogFileSave::Result res_0 = dialog.run(DialogFileSave::FlagHidden | DialogFileSave::FlagMouse);
			DialogFileSave::Result res_1 = dialog.run(DialogFileSave::FlagOverwrite);
			TS_LOGF(Message, "DialogFileSave: %u %u | %d %d %s\n", res_0, res_1, dialog.getPositionX(), dialog.getPositionY(), dialog.getFile().get());
		}
		
		// directory dialog
		if(code == 'd') {
			DialogDirectory dialog("DialogDirectory");
			dialog.setUpdateCallback(update_func);
			DialogDirectory::Result res_0 = dialog.run(DialogDirectory::FlagMouse);
			DialogDirectory::Result res_1 = dialog.run();
			TS_LOGF(Message, "DialogDirectory: %u %u | %d %d %s\n", res_0, res_1, dialog.getPositionX(), dialog.getPositionY(), dialog.getDirectory().get());
		}
		
		// progress dialog
		if(code == 'p') {
			uint32_t progress = 0;
			DialogProgress dialog("DialogProgress", "Hello Progress");
			for(; progress < 100; progress++) {
				float32_t color = progress / 100.0f;
				if(dialog.run(DialogProgress::FlagMouse) != DialogProgress::ResultOk) break;
				window.clear(Color(color, color, color, 1.0f));
				dialog.setMessage(String::format("Hello Progress %2u", progress));
				dialog.setProgress(progress);
				Time::sleep(10000);
			}
			dialog.close();
			for(; progress > 0; progress--) {
				float32_t color = progress / 100.0f;
				if(dialog.run(DialogProgress::FlagMouse) != DialogProgress::ResultOk) break;
				window.clear(Color(color, color, color, 1.0f));
				dialog.setMessage(String::format("Hello Progress %2u", progress));
				dialog.setProgress(progress);
				Time::sleep(10000);
			}
			TS_LOGF(Message, "DialogProgress: %d %d %2u\n", dialog.getPositionX(), dialog.getPositionY(), dialog.getProgress());
		}
		
		// color dialog
		if(code == 'c') {
			DialogColor dialog("DialogColor");
			dialog.setColor(Color(0xffaabb00u));
			dialog.setChangedCallback([&](Color color) { dialog.setColor(color); window.clear(color); TS_LOGF(Message, "%08x\n", color.getRGBAu8()); });
			dialog.setUpdateCallback([&]() { window.clear(dialog.getColor()); Time::sleep(1000); return true; });
			DialogColor::Result res_0 = dialog.run(DialogColor::FlagAlpha | DialogColor::FlagMouse);
			DialogColor::Result res_1 = dialog.run();
			TS_LOGF(Message, "DialogColor: %u %u | %d %d %08x\n", res_0, res_1, dialog.getPositionX(), dialog.getPositionY(), dialog.getColor().getRGBAu8());
		}
		
		// menu dialog
		if(code == 'm' || code == 't' || code == 'w') {
			DialogMenu dialog;
			dialog.addItem("Message", [&]() { window.getKeyboardPressedCallback()(0, 'i'); });
			dialog.addItem("Open", [&]() { window.getKeyboardPressedCallback()(0, 'o'); });
			dialog.addItem("Save", [&]() { window.getKeyboardPressedCallback()(0, 's'); });
			dialog.addItem("Directory", [&]() { window.getKeyboardPressedCallback()(0, 'd'); });
			dialog.addItem("Progress", [&]() { window.getKeyboardPressedCallback()(0, 'p'); });
			dialog.addItem("Color", [&]() { window.getKeyboardPressedCallback()(0, 'c'); });
			dialog.setItemHidden(dialog.addItem("\v"), is_hidden);
			dialog.setItemHidden(dialog.addItem("Dialogs\n"), is_hidden);
			dialog.addItem("Dialogs\nMessage", [&]() { window.getKeyboardPressedCallback()(0, 'i'); });
			dialog.addItem("Dialogs\nOpen", [&]() { window.getKeyboardPressedCallback()(0, 'o'); });
			dialog.addItem("Dialogs\nSave", [&]() { window.getKeyboardPressedCallback()(0, 's'); });
			dialog.addItem("Dialogs\nDirectory", [&]() { window.getKeyboardPressedCallback()(0, 'd'); });
			dialog.addItem("Dialogs\nProgress", [&]() { window.getKeyboardPressedCallback()(0, 'p'); });
			dialog.addItem("Dialogs\nColor", [&]() { window.getKeyboardPressedCallback()(0, 'c'); });
			dialog.addItem("Dialogs\n\v");
			dialog.addItem("Dialogs\nQuit", [&]() { TS_LOG(Message, "quit clicked\n"); window.stop(); });
			dialog.addItem("\v");
			dialog.addItem("Hidden", is_hidden, [&](bool c) { is_hidden = c; TS_LOGF(Message, "hidden changed %u\n", is_hidden); });
			dialog.addItem("Check", is_checked, [&](bool c) { is_checked = c; TS_LOGF(Message, "check changed %u\n", is_checked); });
			dialog.setItemEnabled(dialog.addItem("Disabled"), false);
			dialog.addItem("\v");
			uint32_t group_0 = dialog.addItem("Groups\nFirst", (index_0 == 0), [&](bool c) { index_0 = 0; TS_LOGF(Message, "group changed %u %u\n", index_0, c); });
			dialog.addItem("Groups\nSecond", (index_0 == 1), [&](bool c) { index_0 = 1; TS_LOGF(Message, "group changed %u %u\n", index_0, c); });
			dialog.addItem("Groups\nThird", (index_0 == 2), [&](bool c) { index_0 = 2; TS_LOGF(Message, "group changed %u %u\n", index_0, c); });
			uint32_t group_1 = dialog.addItem("Groups\nFirst", (index_1 == 0), [&](bool c) { index_1 = 0; TS_LOGF(Message, "group changed %u %u\n", index_1, c); });
			dialog.addItem("Groups\nSecond", (index_1 == 1), [&](bool c) { index_1 = 1; TS_LOGF(Message, "group changed %u %u\n", index_1, c); });
			dialog.addItem("Groups\nThird", (index_1 == 2), [&](bool c) { index_1 = 2; TS_LOGF(Message, "group changed %u %u\n", index_1, c); });
			dialog.addItem("Quit", [&]() { TS_LOG(Message, "quit clicked\n"); window.stop(); });
			if(code == 't') dialog.setPosition(window.getPositionX(true), window.getPositionY(true));
			if(code == 'w') dialog.setPosition(window.getPositionX(), window.getPositionY());
			dialog.setItemsGroup(group_0, 3);
			dialog.setItemsGroup(group_1, 3);
			dialog.setUpdateCallback(update_func);
			DialogMenu::Result res = dialog.run();
			TS_LOGF(Message, "DialogMenu: %u\n", res);
		}
		
		if(code == 'q') {
			window.stop();
		}
	});
	
	// show dialog
	#if _ANDROID || _IOS
		window.getKeyboardPressedCallback()(0, 'i');
	#endif
	
	// mouse released callback
	window.setMouseReleasedCallback([&](Window::Button button) {
		if(button == Window::ButtonRight) {
			window.getKeyboardPressedCallback()(0, 'm');
		}
	});
	
	// main loop
	window.run([&]() {
		Window::update();
		return update_func();
	});
	
	return 0;
}

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <interface/TellusimDialogs.h>

#include "include/TellusimControlApp.h"

/*
 */
using namespace Tellusim;

/*
 */
namespace Tellusim {
	
	/*
	 */
	class Application : public ControlApp {
			
		public:
			
			Application(int32_t argc, char **argv) : ControlApp(argc, argv) {
				
			}
			
			int32_t run() {
				
				dialog.setSize(320, 240);
				
				ControlText title_text(&dialog, window.getTitle());
				title_text.setAlign(Control::AlignCenterX);
				title_text.setColor(Color("#f71e46"));
				title_text.setFontSize(24);
				
				ControlButton close_button(&dialog, "&#215;");
				close_button.setAlign(Control::AlignOverlap | Control::AlignRightTop);
				close_button.setPosition(6.0f, 14.0f);
				close_button.setFontSize(24);
				close_button.setBackground(false);
				close_button.setClickedCallback([&](ControlButton button) {
					window.stop();
				});
				
				ControlText info_text(&dialog);
				info_text.setAlign(Control::AlignCenter | Control::AlignExpandY);
				
				ControlEdit edit(&dialog, "Edit");
				edit.setAlign(Control::AlignExpandX);
				
				ControlButton button(&dialog, "Button");
				button.setAlign(Control::AlignExpandX);
				button.setClickedCallback([this](ControlButton button) {
					DialogMessage message("DialogMessage", window.getTitle());
					message.run(DialogMessage::FlagMessage | DialogMessage::FlagMouse | DialogMessage::FlagOk);
				});
				
				return ControlApp::run([&]() {
					
					String info;
					Rect rect = dialog.getRect();
					info += String::format("Dialog %.1f %.1f %.1fx%.1f\n", dialog.getPositionX(), dialog.getPositionY(), rect.getWidth(), rect.getHeight());
					info += String::format("Window %d %d %ux%u\n", window.getPositionX(), window.getPositionY(), window.getWidth(), window.getHeight());
					info_text.setText(info);
					
					return true;
				});
			}
	};
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// instantiate app
	Application app(argc, argv);
	
	// create app
	if(!app.create("Application")) return 1;
	
	// run app
	return app.run();
}

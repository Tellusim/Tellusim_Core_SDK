// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_INTERFACE_CONTROL_APP_H__
#define __TELLUSIM_PLUGINS_INTERFACE_CONTROL_APP_H__

#include <TellusimApp.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimTarget.h>
#include <platform/TellusimWindow.h>
#include <interface/TellusimControls.h>

/*
 */
namespace Tellusim {
	
	/* ControlApp
	 */
	class ControlApp {
			
		public:
			
			/// app constructor
			ControlApp(int32_t argc, char **argv);
			virtual ~ControlApp();
			
			/// disable copying
			ControlApp(const ControlApp&) = delete;
			ControlApp &operator=(const ControlApp&) = delete;
			
			/// create application
			bool create(const char *title);
			
			/// run application
			using UpdateCallback = Function<bool()>;
			int32_t run(const UpdateCallback &func = UpdateCallback());
			
			/// application
			TS_INLINE const App &getApp() const { return app; }
			
			/// platforms
			TS_INLINE Window &getWindow() { return window; }
			TS_INLINE Device &getDevice() { return device; }
			TS_INLINE Target &getTarget() { return target; }
			
			/// controls
			TS_INLINE Canvas &getCanvas() { return canvas; }
			TS_INLINE ControlRoot &getRoot() { return root; }
			TS_INLINE ControlDialog &getDialog() { return dialog; }
			
			/// frame counter
			void setFrame(uint32_t frame) { frame_counter = frame; }
			uint32_t getFrame() const { return frame_counter; }
			
		protected:
			
			App app;						// Application
			
			Window window;					// Window interface
			Device device;					// Device interface
			Target target;					// Target interface
			
			Canvas canvas;					// Canvas interface
			ControlRoot root;				// ControlRoot interface
			ControlDialog dialog;			// ControlDialog interface
			
			uint32_t frame_counter = 2;		// frame counter
	};
}

#endif /* __TELLUSIM_PLUGINS_INTERFACE_CONTROL_APP_H__ */

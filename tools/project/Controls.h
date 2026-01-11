// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __PROJECT_CONTROLS_H__
#define __PROJECT_CONTROLS_H__

#include "Plugins.h"

/*
 */
namespace Tellusim {
	
	/**
	 * Controls
	 */
	class Controls : public ControlApp {
			
		public:
			
			Controls(int32_t argc, char **argv);
			
			/// create controls
			bool create();
			
			/// run controls
			int32_t run();
			
		private:
			
			Logger logger;						// logger
			Config config;						// config
			
			String console_log;					// console log
			
			Log::Callback *log_func = nullptr;	// log callback
			void *log_data = nullptr;			// log data
	};
}

#endif /* __PROJECT_CONTROLS_H__ */

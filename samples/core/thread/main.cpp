// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <core/TellusimSystem.h>
#include <core/TellusimThread.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	{
		class TaskThread : public Thread {
			protected:
				virtual void process() {
					uint32_t counter = 0;
					TS_LOGF(Message, "Thread started %u\n", System::getThreadID());
					while(isRunning()) {
						TS_LOGF(Message, "Thread %u: %u\n", System::getThreadID(), counter++);
						wait();
					}
					TS_LOGF(Message, "Thread stopped %u\n", System::getThreadID());
				}
		};
		
		TaskThread thread_0;
		TaskThread thread_1;
		
		thread_0.run();
		thread_1.run();
		
		for(uint32_t i = 0; i < 8; i++) {
			Time::sleep(Time::MSeconds * 100);
			thread_0.signal();
			thread_1.signal();
		}
		
		thread_0.stop();
		thread_1.stop();
		
		while(!thread_0.isStopped() || !thread_1.isStopped()) { }
	}
		
	return 0;
}

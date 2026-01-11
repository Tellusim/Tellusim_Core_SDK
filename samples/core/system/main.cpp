// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimString.h>
#include <core/TellusimSystem.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	Info info;
	
	TS_LOGF(Message, "Name: %s\n", info.getSystemName().get());
	TS_LOGF(Message, "System: %s\n", info.getSystemVersion().get());
	TS_LOGF(Message, "Kernel: %s\n", info.getKernelVersion().get());
	TS_LOGF(Message, "Memory: %s\n", String::fromBytes(info.getSystemMemory()).get());
	TS_LOGF(Message, "Uptime: %s\n", String::fromTime(info.getSystemUptime()).get());
	
	if(1) {
		
		for(uint32_t i = 0; i < info.getCPUCount(); i++) {
			TS_LOG(Message, "\n");
			TS_LOGF(Message, "Name: %s\n", info.getCPUName(i).get());
			TS_LOGF(Message, "Vendor: %s\n", info.getCPUVendor(i).get());
			TS_LOGF(Message, "Cores: %u\n", info.getCPUCores(i));
			TS_LOGF(Message, "Threads: %u\n", info.getCPUThreads(i));
			TS_LOGF(Message, "Frequency: %s\n", String::fromFrequency(info.getCPUFrequency(i)).get());
			TS_LOGF(Message, "Temperature: %u C\n", info.getCPUTemperature(i));
			TS_LOGF(Message, "Utilization: %u %%\n", info.getCPUUtilization(i));
			TS_LOGF(Message, "FanSpeed: %u\n", info.getCPUFanSpeed(i));
			TS_LOGF(Message, "Power: %u Watt\n", info.getCPUPower(i));
		}
	}
	
	if(1) {
		
		for(uint32_t i = 0; i < info.getGPUCount(); i++) {
			TS_LOG(Message, "\n");
			TS_LOGF(Message, "Name: %s\n", info.getGPUName(i).get());
			TS_LOGF(Message, "Vendor: %s\n", info.getGPUVendor(i).get());
			TS_LOGF(Message, "Device: %s\n", info.getGPUDevice(i).get());
			TS_LOGF(Message, "Serial: %s\n", info.getGPUSerial(i).get());
			TS_LOGF(Message, "Version: %s\n", info.getGPUVersion(i).get());
			TS_LOGF(Message, "Memory: %s\n", String::fromBytes(info.getGPUMemory(i)).get());
			TS_LOGF(Message, "Screens: %u\n", info.getGPUScreens(i));
			TS_LOGF(Message, "Frequency: %s\n", String::fromFrequency(info.getGPUFrequency(i)).get());
			TS_LOGF(Message, "Temperature: %u C\n", info.getGPUTemperature(i));
			TS_LOGF(Message, "Utilization: %u %%\n", info.getGPUUtilization(i));
			TS_LOGF(Message, "FanSpeed: %u\n", info.getGPUFanSpeed(i));
			TS_LOGF(Message, "Power: %.1f Watt\n", info.getGPUPower(i) / 1000.0f);
		}
	}
	
	return 0;
}

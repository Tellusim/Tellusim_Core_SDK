// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_SYSTEM_H__
#define __TELLUSIM_CORE_SYSTEM_H__

#include <core/TellusimString.h>

/*
 */
namespace Tellusim {
	
	/**
	 * The System namespace offers functions for system-level operations, including retrieving the current thread identifier, managing environment variables, and working with dynamic libraries.
	 * It also provides functionality for executing commands with exec, optionally waiting for completion, and opening resources or applications using the open function.
	 */
	namespace System {
		
		/**
		 * Thread identifier
		 */
		TS_API uint32_t getThreadID();
		
		/**
		 * Environment variables
		 */
		TS_API bool setEnvironment(const char *name, const char *value);
		TS_API bool setEnvironment(const String &name, const char *value);
		TS_API String getEnvironment(const char *name);
		TS_API String getEnvironment(const String &name);
		
		/**
		 * Dynamic libraries
		 */
		TS_API void *loadLibrary(const char *name);
		TS_API void *loadLibrary(const String &name);
		TS_API void *getFunction(void *handle, const char *name);
		TS_API void *getFunction(void *handle, const String &name);
		TS_API void closeLibrary(void *handle);
		
		/**
		 * Execute command
		 * \param wait Wait for the process completion.
		 * \param console Create process console window.
		 */
		TS_API int32_t exec(const char *command, bool wait = false, bool console = true);
		TS_API int32_t exec(const String &command, bool wait = false, bool console = true);
		
		/**
		 * Open resource
		 */
		TS_API bool open(const char *command);
		TS_API bool open(const String &command);
	}
	
	/**
	 * The Info class provides detailed system and hardware information, offering methods to retrieve data on system memory, uptime, and version, as well as kernel details.
	 * CPU-related queries include processor details like core count, temperature, and frequency.
	 * For GPU information, aspects such as memory size, frequency, utilization, and power are available, along with the ability to detect throttling states.
	 * The class offers a comprehensive suite of functions for gathering detailed system performance and hardware status.
	 */
	class TS_API Info {
			
			TS_DECLARE_PTR(Info, 0)
			
		public:
			
			Info();
			
			/// System info
			size_t getSystemMemory() const;
			uint64_t getSystemUptime() const;
			String getSystemName() const;
			String getSystemVersion() const;
			String getKernelVersion() const;
			
			/// CPU info
			uint32_t getCPUCount() const;
			String getCPUName(uint32_t index) const;
			String getCPUVendor(uint32_t index) const;
			uint32_t getCPUCores(uint32_t index) const;
			uint32_t getCPUThreads(uint32_t index) const;
			uint64_t getCPUFrequency(uint32_t index) const;
			uint32_t getCPUTemperature(uint32_t index) const;
			uint32_t getCPUUtilization(uint32_t index) const;
			uint32_t getCPUFanSpeed(uint32_t index) const;
			uint32_t getCPUPower(uint32_t index) const;
			
			/// GPU info
			uint32_t getGPUCount() const;
			String getGPUName(uint32_t index) const;
			String getGPUVendor(uint32_t index) const;
			String getGPUSerial(uint32_t index) const;
			String getGPUDevice(uint32_t index) const;
			String getGPUVersion(uint32_t index) const;
			size_t getGPUMemory(uint32_t index) const;
			uint32_t getGPUScreens(uint32_t index) const;
			uint64_t getGPUFrequency(uint32_t index) const;
			uint32_t getGPUTemperature(uint32_t index) const;
			uint32_t getGPUUtilization(uint32_t index) const;
			uint32_t getGPUFanSpeed(uint32_t index) const;
			uint32_t getGPUPower(uint32_t index) const;
			bool isGPUThrottling(uint32_t index) const;
	};
}

#endif /* __TELLUSIM_CORE_SYSTEM_H__ */

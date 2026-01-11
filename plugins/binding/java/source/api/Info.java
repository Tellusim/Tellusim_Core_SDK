// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Info {
	
	public Info() { init_(new_()); }
	public Info[] ref() { return new Info[] { this }; }
	public boolean equalPtr(Info ptr) { return equal_ptr(self, ptr.self); }
	public Info clonePtr() { return new Info(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public long getSystemMemory() { return get_system_memory(self); }
	public long getSystemUptime() { return get_system_uptime(self); }
	public String getSystemName() { return get_system_name(self); }
	public String getSystemVersion() { return get_system_version(self); }
	public String getKernelVersion() { return get_kernel_version(self); }
	public int getCPUCount() { return get_cpu_count(self); }
	public String getCPUName(int index) { return get_cpu_name(self, index); }
	public String getCPUVendor(int index) { return get_cpu_vendor(self, index); }
	public int getCPUCores(int index) { return get_cpu_cores(self, index); }
	public int getCPUThreads(int index) { return get_cpu_threads(self, index); }
	public long getCPUFrequency(int index) { return get_cpu_frequency(self, index); }
	public int getCPUTemperature(int index) { return get_cpu_temperature(self, index); }
	public int getCPUUtilization(int index) { return get_cpu_utilization(self, index); }
	public int getCPUFanSpeed(int index) { return get_cpu_fan_speed(self, index); }
	public int getCPUPower(int index) { return get_cpu_power(self, index); }
	public int getGPUCount() { return get_gpu_count(self); }
	public String getGPUName(int index) { return get_gpu_name(self, index); }
	public String getGPUVendor(int index) { return get_gpu_vendor(self, index); }
	public String getGPUSerial(int index) { return get_gpu_serial(self, index); }
	public String getGPUDevice(int index) { return get_gpu_device(self, index); }
	public String getGPUVersion(int index) { return get_gpu_version(self, index); }
	public long getGPUMemory(int index) { return get_gpu_memory(self, index); }
	public int getGPUScreens(int index) { return get_gpu_screens(self, index); }
	public long getGPUFrequency(int index) { return get_gpu_frequency(self, index); }
	public int getGPUTemperature(int index) { return get_gpu_temperature(self, index); }
	public int getGPUUtilization(int index) { return get_gpu_utilization(self, index); }
	public int getGPUFanSpeed(int index) { return get_gpu_fan_speed(self, index); }
	public int getGPUPower(int index) { return get_gpu_power(self, index); }
	public boolean isGPUThrottling(int index) { return is_gpu_throttling(self, index); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_ptr(long self, long ptr);
	private static native long clone_ptr(long self);
	private static native void clear_ptr(long self);
	private static native void destroy_ptr(long self);
	private static native void acquire_ptr(long self);
	private static native void unacquire_ptr(long self);
	private static native boolean is_valid_ptr(long self);
	private static native boolean is_owner_ptr(long self);
	private static native boolean is_const_ptr(long self);
	private static native int get_count_ptr(long self);
	private static native long get_internal_ptr(long self);
	private static native long get_system_memory(long self);
	private static native long get_system_uptime(long self);
	private static native String get_system_name(long self);
	private static native String get_system_version(long self);
	private static native String get_kernel_version(long self);
	private static native int get_cpu_count(long self);
	private static native String get_cpu_name(long self, int index);
	private static native String get_cpu_vendor(long self, int index);
	private static native int get_cpu_cores(long self, int index);
	private static native int get_cpu_threads(long self, int index);
	private static native long get_cpu_frequency(long self, int index);
	private static native int get_cpu_temperature(long self, int index);
	private static native int get_cpu_utilization(long self, int index);
	private static native int get_cpu_fan_speed(long self, int index);
	private static native int get_cpu_power(long self, int index);
	private static native int get_gpu_count(long self);
	private static native String get_gpu_name(long self, int index);
	private static native String get_gpu_vendor(long self, int index);
	private static native String get_gpu_serial(long self, int index);
	private static native String get_gpu_device(long self, int index);
	private static native String get_gpu_version(long self, int index);
	private static native long get_gpu_memory(long self, int index);
	private static native int get_gpu_screens(long self, int index);
	private static native long get_gpu_frequency(long self, int index);
	private static native int get_gpu_temperature(long self, int index);
	private static native int get_gpu_utilization(long self, int index);
	private static native int get_gpu_fan_speed(long self, int index);
	private static native int get_gpu_power(long self, int index);
	private static native boolean is_gpu_throttling(long self, int index);
	
	protected Info(long self) {
		init_(self);
	}
	public static Info Null() {
		return new Info((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Info[] ptr) {
		long[] self = new long[ptr.length];
		for(int i = 0; i < ptr.length; i++) self[i] = ptr[i].self;
		return self;
	}
	private static class Destructor implements Runnable {
		Destructor(long self) { this.self = self; }
		public void run() { delete_(self); }
		private long self;
	}
	
	private static Cleaner cleaner = Cleaner.create();
	
	protected long self;
}

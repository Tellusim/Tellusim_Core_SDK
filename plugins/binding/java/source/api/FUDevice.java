// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class FUDevice extends Device {
	
	public FUDevice() { init_(new_()); }
	public FUDevice(Device[] devices) { init_(new_1(Device.self_(devices), false)); }
	public FUDevice(Device[] devices, boolean owner) { init_(new_1(Device.self_(devices), owner)); }
	public FUDevice[] ref() { return new FUDevice[] { this }; }
	public FUDevice(Device base) { init_(cast_device_ptr(base.self)); }
	public Device toDevice() { return new Device(base_device_ptr(self)); }
	public void setMask(int mask) { set_mask(self, mask); }
	public int getMask() { return get_mask(self); }
	public int getNumDevices() { return get_num_devices(self); }
	public Device getDevice(int index) { return new Device(get_device(self, index)); }
	
	private static native long new_();
	private static native long new_1(long[] devices, boolean owner);
	private static native void delete_(long self);
	private static native boolean equal_device_ptr(long self, long base);
	private static native long cast_device_ptr(long self);
	private static native long base_device_ptr(long self);
	private static native void set_mask(long self, int mask);
	private static native int get_mask(long self);
	private static native int get_num_devices(long self);
	private static native long get_device(long self, int index);
	private static native long get_device_1(long self, int index);
	
	protected FUDevice(long self) {
		init_(self);
	}
	public static FUDevice Null() {
		return new FUDevice((long)0);
	}
}

// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class D3D11Device extends Device {
	
	public D3D11Device() { init_(new_()); }
	public D3D11Device(Context context) { init_(new_1(context.self)); }
	public D3D11Device(Surface surface) { init_(new_2(surface.self)); }
	public D3D11Device(Window window) { init_(new_3(window.self)); }
	public D3D11Device[] ref() { return new D3D11Device[] { this }; }
	public D3D11Device(Device base) { init_(cast_device_ptr(base.self)); }
	public Device toDevice() { return new Device(base_device_ptr(self)); }
	public long getD3D11Device() { return get_d3d11_device(self); }
	public long getCommand() { return get_command(self); }
	public long getD3D11Features(int index) { return get_d3d11_features(self, index); }
	
	private static native long new_();
	private static native long new_1(long context);
	private static native long new_2(long surface);
	private static native long new_3(long window);
	private static native void delete_(long self);
	private static native boolean equal_device_ptr(long self, long base);
	private static native long cast_device_ptr(long self);
	private static native long base_device_ptr(long self);
	private static native long get_d3d11_device(long self);
	private static native long get_command(long self);
	private static native long get_d3d11_features(long self, int index);
	
	protected D3D11Device(long self) {
		init_(self);
	}
	public static D3D11Device Null() {
		return new D3D11Device((long)0);
	}
}

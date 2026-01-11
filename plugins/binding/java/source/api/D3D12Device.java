// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class D3D12Device extends Device {
	
	public D3D12Device() { init_(new_()); }
	public D3D12Device(Context context) { init_(new_1(context.self)); }
	public D3D12Device(Surface surface) { init_(new_2(surface.self)); }
	public D3D12Device(Window window) { init_(new_3(window.self)); }
	public D3D12Device[] ref() { return new D3D12Device[] { this }; }
	public D3D12Device(Device base) { init_(cast_device_ptr(base.self)); }
	public Device toDevice() { return new Device(base_device_ptr(self)); }
	public void setBufferState(Buffer buffer, int state) { set_buffer_state(self, buffer.self, state); }
	public void setTextureState(Texture texture, int state) { set_texture_state(self, texture.self, state); }
	public long getD3D12Device() { return get_d3d12_device(self); }
	public long getQueue() { return get_queue(self); }
	public long getCommand() { return get_command(self); }
	public long getD3D12Features(int index) { return get_d3d12_features(self, index); }
	public int getShaderModel() { return get_shader_model(self); }
	
	private static native long new_();
	private static native long new_1(long context);
	private static native long new_2(long surface);
	private static native long new_3(long window);
	private static native void delete_(long self);
	private static native boolean equal_device_ptr(long self, long base);
	private static native long cast_device_ptr(long self);
	private static native long base_device_ptr(long self);
	private static native void set_buffer_state(long self, long buffer, int state);
	private static native void set_texture_state(long self, long texture, int state);
	private static native long get_d3d12_device(long self);
	private static native long get_queue(long self);
	private static native long get_command(long self);
	private static native long get_d3d12_features(long self, int index);
	private static native int get_shader_model(long self);
	
	protected D3D12Device(long self) {
		init_(self);
	}
	public static D3D12Device Null() {
		return new D3D12Device((long)0);
	}
}

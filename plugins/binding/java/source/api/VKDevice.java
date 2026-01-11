// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class VKDevice extends Device {
	
	public VKDevice() { init_(new_()); }
	public VKDevice(Context context) { init_(new_1(context.self)); }
	public VKDevice(Surface surface) { init_(new_2(surface.self)); }
	public VKDevice(Window window) { init_(new_3(window.self)); }
	public VKDevice[] ref() { return new VKDevice[] { this }; }
	public VKDevice(Device base) { init_(cast_device_ptr(base.self)); }
	public Device toDevice() { return new Device(base_device_ptr(self)); }
	public void setBufferAccess(Buffer buffer, int access) { set_buffer_access(self, buffer.self, access); }
	public void setTextureLayout(Texture texture, int layout) { set_texture_layout(self, texture.self, layout); }
	public boolean waitVKFence(long fence, long timeout, boolean reset) { return wait_vk_fence(self, fence, timeout, reset); }
	public boolean signalVKFence(long fence) { return signal_vk_fence(self, fence); }
	public void waitSemaphore(long semaphore, int mask) { wait_semaphore(self, semaphore, mask); }
	public void signalSemaphore(long semaphore) { signal_semaphore(self, semaphore); }
	public boolean hasMemoryType(int flags) { return has_memory_type(self, flags); }
	public int getMemoryIndex(int types, int flags) { return get_memory_index(self, types, flags); }
	public long getInstance() { return get_instance(self); }
	public long getAdapter() { return get_adapter(self); }
	public long getVKDevice() { return get_vk_device(self); }
	public long getQueue() { return get_queue(self); }
	public long getCommand() { return get_command(self); }
	public int getFamily() { return get_family(self); }
	public String getExtensions() { return get_extensions(self); }
	public boolean checkExtension(String name) { return check_extension(self, name); }
	public long getVKFeatures(int type) { return get_vk_features(self, type); }
	
	private static native long new_();
	private static native long new_1(long context);
	private static native long new_2(long surface);
	private static native long new_3(long window);
	private static native void delete_(long self);
	private static native boolean equal_device_ptr(long self, long base);
	private static native long cast_device_ptr(long self);
	private static native long base_device_ptr(long self);
	private static native void set_buffer_access(long self, long buffer, int access);
	private static native void set_texture_layout(long self, long texture, int layout);
	private static native boolean wait_vk_fence(long self, long fence, long timeout, boolean reset);
	private static native boolean signal_vk_fence(long self, long fence);
	private static native void wait_semaphore(long self, long semaphore, int mask);
	private static native void signal_semaphore(long self, long semaphore);
	private static native boolean has_memory_type(long self, int flags);
	private static native int get_memory_index(long self, int types, int flags);
	private static native long get_instance(long self);
	private static native long get_adapter(long self);
	private static native long get_vk_device(long self);
	private static native long get_queue(long self);
	private static native long get_command(long self);
	private static native int get_family(long self);
	private static native String get_extensions(long self);
	private static native boolean check_extension(long self, String name);
	private static native long get_vk_features(long self, int type);
	
	protected VKDevice(long self) {
		init_(self);
	}
	public static VKDevice Null() {
		return new VKDevice((long)0);
	}
}

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class VKContext extends Context {
	
	public VKContext() { init_(new_(Base.Maxu32)); }
	public VKContext(int index) { init_(new_(index)); }
	public VKContext[] ref() { return new VKContext[] { this }; }
	public VKContext(Context base) { init_(cast_context_ptr(base.self)); }
	public Context toContext() { return new Context(base_context_ptr(self)); }
	public boolean create(long instance, long func, long adapter, long device, int family, int index) { return create_(self, instance, func, adapter, device, family, index); }
	public long getInstance() { return get_instance(self); }
	public long getAdapter() { return get_adapter(self); }
	public long getDevice() { return get_device(self); }
	public long getQueue() { return get_queue(self); }
	public long getCommand() { return get_command(self); }
	public int getFamily() { return get_family(self); }
	public int getNumQueues() { return get_num_queues(self); }
	public int getQueueFlags(int index) { return get_queue_flags(self, index); }
	public int getQueueFamily(int index) { return get_queue_family(self, index); }
	public static void addContextExtension(String name) { add_context_extension(name); }
	public static void addAdapterExtension(String name) { add_adapter_extension(name); }
	public static void addAdapterFeatures(long features) { add_adapter_features(features); }
	public static String getLayers() { return get_layers(); }
	public static String getExtensions() { return get_extensions(); }
	public static boolean checkLayer(String name) { return check_layer(name); }
	public static boolean checkExtension(String name) { return check_extension(name); }
	public static long getInstanceProcAddress() { return get_instance_proc_address(); }
	public static long getDeviceProcAddress() { return get_device_proc_address(); }
	public static long getProcAddress(String name) { return get_proc_address(name); }
	public static boolean error(int result) { return error_(result); }
	
	private static native long new_(int index);
	private static native void delete_(long self);
	private static native boolean equal_context_ptr(long self, long base);
	private static native long cast_context_ptr(long self);
	private static native long base_context_ptr(long self);
	private static native boolean create_(long self, long instance, long func, long adapter, long device, int family, int index);
	private static native long get_instance(long self);
	private static native long get_adapter(long self);
	private static native long get_device(long self);
	private static native long get_queue(long self);
	private static native long get_command(long self);
	private static native int get_family(long self);
	private static native int get_num_queues(long self);
	private static native int get_queue_flags(long self, int index);
	private static native int get_queue_family(long self, int index);
	private static native void add_context_extension(String name);
	private static native void add_adapter_extension(String name);
	private static native void add_adapter_features(long features);
	private static native String get_layers();
	private static native String get_extensions();
	private static native boolean check_layer(String name);
	private static native boolean check_extension(String name);
	private static native long get_instance_proc_address();
	private static native long get_device_proc_address();
	private static native long get_proc_address(String name);
	private static native boolean error_(int result);
	
	protected VKContext(long self) {
		init_(self);
	}
	public static VKContext Null() {
		return new VKContext((long)0);
	}
}

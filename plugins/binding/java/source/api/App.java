// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class App {
	
	public static final int Version_19 = 20221010;
	public static final int Version_20 = 20221109;
	public static final int Version_21 = 20221122;
	public static final int Version_22 = 20221222;
	public static final int Version_23 = 20230117;
	public static final int Version_24 = 20230217;
	public static final int Version_25 = 20230402;
	public static final int Version_26 = 20230509;
	public static final int Version_27 = 20230612;
	public static final int Version_28 = 20230718;
	public static final int Version_29 = 20230824;
	public static final int Version_30 = 20231029;
	public static final int Version_31 = 20231113;
	public static final int Version_32 = 20231212;
	public static final int Version_33 = 20240116;
	public static final int Version_34 = 20240216;
	public static final int Version_35 = 20240320;
	public static final int Version_36 = 20240427;
	public static final int Version_37 = 20240515;
	public static final int Version_38 = 20250215;
	public static final int Version_39 = 20250322;
	public static final int Version_40 = 20250429;
	public static final int Version_41 = 20250816;
	public static final int Version_42 = 20251102;
	public static final int Version_43 = 20251220;
	public static final int Version_44 = 20260625;
	public static final int Version_45 = 20260702;
	public static final int Version = 20260702;
	
	public App(String[] args) { init_(new_(Base.getArgs(args))); }
	public App[] ref() { return new App[] { this }; }
	public void clear() { clear_(self); }
	public Platform getPlatform() { return new Platform(get_platform(self)); }
	public int getDevice() { return get_device(self); }
	public int getWidth() { return get_width(self); }
	public int getHeight() { return get_height(self); }
	public int getMultisample() { return get_multisample(self); }
	public int getNumArguments() { return get_num_arguments(self); }
	public String getArgument(int num) { return get_argument(self, num); }
	public boolean isArgument(String name) { return is_argument(self, name); }
	public String getArgument(String name) { return get_argument_1(self, name); }
	public boolean create() { return create_(self, Platform.Unknown.value, Version); }
	public boolean create(Platform platform) { return create_(self, platform.value, Version); }
	public boolean create(Platform.Enum platform) { return create_(self, platform.value, Version); }
	public boolean create(Platform platform, int version) { return create_(self, platform.value, version); }
	public boolean create(Platform.Enum platform, int version) { return create_(self, platform.value, version); }
	public static void setPlatform(Platform platform) { set_platform(platform.value, Base.Maxu32); }
	public static void setPlatform(Platform.Enum platform) { set_platform(platform.value, Base.Maxu32); }
	public static void setPlatform(Platform platform, int device) { set_platform(platform.value, device); }
	public static void setPlatform(Platform.Enum platform, int device) { set_platform(platform.value, device); }
	public static void setSize(int width, int height) { set_size(width, height, 0); }
	public static void setSize(int width, int height, int multisample) { set_size(width, height, multisample); }
	public static boolean isBuildCore() { return is_build_core(); }
	public static boolean isBuildDebug() { return is_build_debug(); }
	public static boolean isBuildFloat64() { return is_build_float64(); }
	public static String getBuildDate() { return get_build_date(); }
	public static String getBuildInfo() { return get_build_info(); }
	public static int getVersion() { return get_version(); }
	public static long getAPIHash() { return get_api_hash(); }
	
	private static native long new_(String[] argv);
	private static native void delete_(long self);
	private static native void clear_(long self);
	private static native int get_platform(long self);
	private static native int get_device(long self);
	private static native int get_width(long self);
	private static native int get_height(long self);
	private static native int get_multisample(long self);
	private static native int get_num_arguments(long self);
	private static native String get_argument(long self, int num);
	private static native boolean is_argument(long self, String name);
	private static native String get_argument_1(long self, String name);
	private static native boolean create_(long self, int platform, int version);
	private static native void set_platform(int platform, int device);
	private static native void set_size(int width, int height, int multisample);
	private static native boolean is_build_core();
	private static native boolean is_build_debug();
	private static native boolean is_build_float64();
	private static native String get_build_date();
	private static native String get_build_info();
	private static native int get_version();
	private static native long get_api_hash();
	
	protected App(long self) {
		init_(self);
	}
	public static App Null() {
		return new App((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(App[] ptr) {
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

// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;

/*
 */
public class Sys {
	
	public static int getThreadID() { return get_thread_id(); }
	public static boolean setEnvironment(String name, String value) { return set_environment(name, value); }
	public static boolean setEnvironment(TSString name, String value) { return set_environment_1(name.self, value); }
	public static String getEnvironment(String name) { return get_environment(name); }
	public static String getEnvironment(TSString name) { return get_environment_1(name.self); }
	public static long loadLibrary(String name) { return load_library(name); }
	public static long loadLibrary(TSString name) { return load_library_1(name.self); }
	public static long getFunction(long handle, String name) { return get_function(handle, name); }
	public static long getFunction(long handle, TSString name) { return get_function_1(handle, name.self); }
	public static void closeLibrary(long handle) { close_library(handle); }
	public static int exec(String command) { return exec_(command, false, true); }
	public static int exec(String command, boolean wait) { return exec_(command, wait, true); }
	public static int exec(String command, boolean wait, boolean console) { return exec_(command, wait, console); }
	public static int exec(TSString command) { return exec_1(command.self, false, true); }
	public static int exec(TSString command, boolean wait) { return exec_1(command.self, wait, true); }
	public static int exec(TSString command, boolean wait, boolean console) { return exec_1(command.self, wait, console); }
	public static boolean open(String command) { return open_(command); }
	public static boolean open(TSString command) { return open_1(command.self); }
	
	private static native int get_thread_id();
	private static native boolean set_environment(String name, String value);
	private static native boolean set_environment_1(long name, String value);
	private static native String get_environment(String name);
	private static native String get_environment_1(long name);
	private static native long load_library(String name);
	private static native long load_library_1(long name);
	private static native long get_function(long handle, String name);
	private static native long get_function_1(long handle, long name);
	private static native void close_library(long handle);
	private static native int exec_(String command, boolean wait, boolean console);
	private static native int exec_1(long command, boolean wait, boolean console);
	private static native boolean open_(String command);
	private static native boolean open_1(long command);
}

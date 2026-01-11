// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;

/*
 */
public class Time {
	
	public static final int Seconds = 1000000;
	public static final int MSeconds = 1000;
	public static final int USeconds = 1;
	
	public static long current() { return current_(); }
	public static double seconds() { return seconds_(); }
	public static void sleep(int usec) { sleep_(usec); }
	
	private static native long current_();
	private static native double seconds_();
	private static native void sleep_(int usec);
}

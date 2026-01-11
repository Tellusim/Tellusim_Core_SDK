// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;

/*
 */
public class Log {
	
	public static class Level {
		public enum Enum {
			Fatal(0),
			Error(1),
			Warning(2),
			Message(3),
			Verbose(4),
			Unknown(5),
			NumLevels(6);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Fatal = Enum.Fatal;
		public static final Enum Error = Enum.Error;
		public static final Enum Warning = Enum.Warning;
		public static final Enum Message = Enum.Message;
		public static final Enum Verbose = Enum.Verbose;
		public static final Enum Unknown = Enum.Unknown;
		public static final Enum NumLevels = Enum.NumLevels;
		public Level(int value) { this.value = value; }
		public Level(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static abstract class Callback {
		public abstract boolean run(Level a0, long time, String str, long data);
		public boolean run_(int a0, long time, String str, long data) { return run(new Level(a0), time, str, data); }
	}
	
	public static void setLevel(Level level) { set_level(level.value); }
	public static void setLevel(Level.Enum level) { set_level(level.value); }
	public static Level getLevel() { return new Level(get_level()); }
	public static void unlockCallback() { unlock_callback(); }
	public static void lockCallback() { lock_callback(); }
	public static void print(String str) { print_(str); }
	public static void print(Level level, String str) { print_1(level.value, str); }
	public static void print(Level.Enum level, String str) { print_1(level.value, str); }
	public static void printe(Level level, String str) { printe_(level.value, str); }
	public static void printe(Level.Enum level, String str) { printe_(level.value, str); }
	public static void printf(String format, java.lang.Object ... args) { print_(String.format(format, args)); }
	public static void printf(Level level, String str, java.lang.Object ... args) { print_1(level.value, String.format(str, args)); }
	public static void printf(Level.Enum level, String str, java.lang.Object ... args) { print_1(level.value, String.format(str, args)); }
	public static void printe(Level level, String str, java.lang.Object ... args) { printe_(level.value, String.format(str, args)); }
	public static void printe(Level.Enum level, String str, java.lang.Object ... args) { printe_(level.value, String.format(str, args)); }
	
	private static native void set_level(int level);
	private static native int get_level();
	private static native void unlock_callback();
	private static native void lock_callback();
	private static native void print_(String str);
	private static native void print_1(int level, String str);
	private static native void printe_(int level, String str);
}

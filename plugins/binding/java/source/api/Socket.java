// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Socket extends Stream {
	
	public static class Type {
		public enum Enum {
			Stream(0),
			Datagram(1),
			NumTypes(2);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Stream = Enum.Stream;
		public static final Enum Datagram = Enum.Datagram;
		public static final Enum NumTypes = Enum.NumTypes;
		public Type(int value) { this.value = value; }
		public Type(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public Socket() { init_(new_(Type.Stream.value)); }
	public Socket(Type type) { init_(new_(type.value)); }
	public Socket(Type.Enum type) { init_(new_(type.value)); }
	public Socket[] ref() { return new Socket[] { this }; }
	public boolean open(short port) { return open_(self, port, (short)32); }
	public boolean open(short port, short num) { return open_(self, port, num); }
	public boolean open(String name, short port) { return open_1(self, name, port); }
	public boolean open(TSString name, short port) { return open_2(self, name.self, port); }
	public void close() { close_(self); }
	public boolean connect(int sec) { return connect_(self, sec, 0); }
	public boolean connect(int sec, int usec) { return connect_(self, sec, usec); }
	public boolean accept(Socket socket) { return accept_(self, socket.self); }
	public boolean select(int sec) { return select_(self, sec, 0); }
	public boolean select(int sec, int usec) { return select_(self, sec, usec); }
	public boolean setTimeout(int sec) { return set_timeout(self, sec); }
	public int getTimeout() { return get_timeout(self); }
	public boolean setBlock(boolean block) { return set_block(self, block); }
	public boolean getBlock() { return get_block(self); }
	public boolean setDelay(boolean delay) { return set_delay(self, delay); }
	public boolean getDelay() { return get_delay(self); }
	public void setName(String name) { set_name(self, name); }
	public void setName(TSString name) { set_name_1(self, name.self); }
	public short getPort() { return get_port(self); }
	public int getFD() { return get_fd(self); }
	public Type getType() { return new Type(get_type(self)); }
	public static String getAddress() { return get_address(null); }
	public static String getAddress(String delimiter) { return get_address(delimiter); }
	
	private static native long new_(int type);
	private static native void delete_(long self);
	private static native boolean open_(long self, short port, short num);
	private static native boolean open_1(long self, String name, short port);
	private static native boolean open_2(long self, long name, short port);
	private static native void close_(long self);
	private static native boolean connect_(long self, int sec, int usec);
	private static native boolean accept_(long self, long socket);
	private static native boolean select_(long self, int sec, int usec);
	private static native boolean set_timeout(long self, int sec);
	private static native int get_timeout(long self);
	private static native boolean set_block(long self, boolean block);
	private static native boolean get_block(long self);
	private static native boolean set_delay(long self, boolean delay);
	private static native boolean get_delay(long self);
	private static native void set_name(long self, String name);
	private static native void set_name_1(long self, long name);
	private static native short get_port(long self);
	private static native int get_fd(long self);
	private static native int get_type(long self);
	private static native String get_address(String delimiter);
	
	protected Socket(long self) {
		init_(self);
	}
	public static Socket Null() {
		return new Socket((long)0);
	}
}

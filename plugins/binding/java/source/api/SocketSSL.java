// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class SocketSSL extends Socket {
	
	public SocketSSL() { init_(new_()); }
	public SocketSSL[] ref() { return new SocketSSL[] { this }; }
	public SocketSSL(Socket base) { init_(cast_socket_ptr(base.self)); }
	public Socket toSocket() { return new Socket(base_socket_ptr(self)); }
	public boolean handshake() { return handshake_(self, null); }
	public boolean handshake(String name) { return handshake_(self, name); }
	public boolean accept(SocketSSL socket) { return accept_(self, socket.self); }
	public boolean accept(Socket socket) { return accept_1(self, socket.self); }
	public boolean load(Stream stream) { return load_(self, stream.self); }
	public boolean load(String name) { return load_1(self, name); }
	public boolean load(TSString name) { return load_2(self, name.self); }
	public boolean isConnected() { return is_connected(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_socket_ptr(long self, long base);
	private static native long cast_socket_ptr(long self);
	private static native long base_socket_ptr(long self);
	private static native boolean handshake_(long self, String name);
	private static native boolean accept_(long self, long socket);
	private static native boolean accept_1(long self, long socket);
	private static native boolean load_(long self, long stream);
	private static native boolean load_1(long self, String name);
	private static native boolean load_2(long self, long name);
	private static native boolean is_connected(long self);
	
	protected SocketSSL(long self) {
		init_(self);
	}
	public static SocketSSL Null() {
		return new SocketSSL((long)0);
	}
}

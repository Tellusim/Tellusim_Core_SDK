// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class D3D12Command extends Command {
	
	public D3D12Command() { init_(new_()); }
	public D3D12Command[] ref() { return new D3D12Command[] { this }; }
	public D3D12Command(Command base) { init_(cast_command_ptr(base.self)); }
	public Command toCommand() { return new Command(base_command_ptr(self)); }
	public long getD3D12Command() { return get_d3d12_command(self); }
	public void update() { update_(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_command_ptr(long self, long base);
	private static native long cast_command_ptr(long self);
	private static native long base_command_ptr(long self);
	private static native long get_d3d12_command(long self);
	private static native void update_(long self);
	
	protected D3D12Command(long self) {
		init_(self);
	}
	public static D3D12Command Null() {
		return new D3D12Command((long)0);
	}
}

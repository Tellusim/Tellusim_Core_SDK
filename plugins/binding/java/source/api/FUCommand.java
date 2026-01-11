// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class FUCommand extends Command {
	
	public FUCommand() { init_(new_()); }
	public FUCommand(Command[] commands) { init_(new_1(Command.self_(commands), false)); }
	public FUCommand(Command[] commands, boolean owner) { init_(new_1(Command.self_(commands), owner)); }
	public FUCommand[] ref() { return new FUCommand[] { this }; }
	public FUCommand(Command base) { init_(cast_command_ptr(base.self)); }
	public Command toCommand() { return new Command(base_command_ptr(self)); }
	public void setMask(int mask) { set_mask(self, mask); }
	public int getMask() { return get_mask(self); }
	public int getNumCommands() { return get_num_commands(self); }
	public Command getCommand(int index) { return new Command(get_command(self, index)); }
	
	private static native long new_();
	private static native long new_1(long[] commands, boolean owner);
	private static native void delete_(long self);
	private static native boolean equal_command_ptr(long self, long base);
	private static native long cast_command_ptr(long self);
	private static native long base_command_ptr(long self);
	private static native void set_mask(long self, int mask);
	private static native int get_mask(long self);
	private static native int get_num_commands(long self);
	private static native long get_command(long self, int index);
	private static native long get_command_1(long self, int index);
	
	protected FUCommand(long self) {
		init_(self);
	}
	public static FUCommand Null() {
		return new FUCommand((long)0);
	}
}

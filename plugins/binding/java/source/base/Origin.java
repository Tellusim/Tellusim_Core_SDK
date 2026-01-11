// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Origin {
	
	public Origin() { this(new_()); }
	public Origin(Origin o) { this(copy_(o.self)); }
	public Origin(int x, int y) { this(new_()); set_x(self, x); set_y(self, y); }
	public Origin(int x, int y, int z) { this(new_()); set_x(self, x); set_y(self, y); set_z(self, z); }
	
	public void setX(int x) { set_x(self, x); }
	public void setY(int y) { set_y(self, y); }
	public void setZ(int z) { set_z(self, z); }
	
	public int getX() { return get_x(self); }
	public int getY() { return get_y(self); }
	public int getZ() { return get_z(self); }
	
	public int x() { return get_x(self); }
	public int y() { return get_y(self); }
	public int z() { return get_z(self); }
	
	private static native long new_();
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_x(long self, int x);
	private static native void set_y(long self, int y);
	private static native void set_z(long self, int z);
	private static native int get_x(long self);
	private static native int get_y(long self);
	private static native int get_z(long self);
	
	protected Origin(long self) {
		cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	private static class Destructor implements Runnable {
		Destructor(long self) { this.self = self; }
		public void run() { delete_(self); }
		private long self;
	}
	
	private static Cleaner cleaner = Cleaner.create();
	
	protected long self;
}

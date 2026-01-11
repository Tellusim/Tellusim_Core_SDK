// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class CanvasStripVertex {
	
	public CanvasStripVertex() { this(new_()); }
	public CanvasStripVertex(CanvasStripVertex v) { this(copy_(v.self)); }
	
	private static native long new_();
	private static native long copy_(long self);
	private static native void delete_(long self);
	private static native void set_position(long self, long v);
	private static native void set_parameters(long self, long v);
	private static native void set_adjacencies(long self, long v);
	private static native long get_position(long self);
	private static native long get_parameters(long self);
	private static native long get_adjacencies(long self);
	
	protected CanvasStripVertex(long self) {
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

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class FUTraversal extends Traversal {
	
	public FUTraversal() { init_(new_()); }
	public FUTraversal(Traversal[] traversals) { init_(new_1(Traversal.self_(traversals), false)); }
	public FUTraversal(Traversal[] traversals, boolean owner) { init_(new_1(Traversal.self_(traversals), owner)); }
	public FUTraversal[] ref() { return new FUTraversal[] { this }; }
	public FUTraversal(Traversal base) { init_(cast_traversal_ptr(base.self)); }
	public Traversal toTraversal() { return new Traversal(base_traversal_ptr(self)); }
	public void setMask(int mask) { set_mask(self, mask); }
	public int getMask() { return get_mask(self); }
	public int getNumTraversals() { return get_num_traversals(self); }
	public Traversal getTraversal(int index) { return new Traversal(get_traversal(self, index)); }
	
	private static native long new_();
	private static native long new_1(long[] traversals, boolean owner);
	private static native void delete_(long self);
	private static native boolean equal_traversal_ptr(long self, long base);
	private static native long cast_traversal_ptr(long self);
	private static native long base_traversal_ptr(long self);
	private static native void set_mask(long self, int mask);
	private static native int get_mask(long self);
	private static native int get_num_traversals(long self);
	private static native long get_traversal(long self, int index);
	private static native long get_traversal_1(long self, int index);
	
	protected FUTraversal(long self) {
		init_(self);
	}
	public static FUTraversal Null() {
		return new FUTraversal((long)0);
	}
}

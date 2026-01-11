// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class D3D12Traversal extends Traversal {
	
	public D3D12Traversal() { init_(new_()); }
	public D3D12Traversal[] ref() { return new D3D12Traversal[] { this }; }
	public D3D12Traversal(Traversal base) { init_(cast_traversal_ptr(base.self)); }
	public Traversal toTraversal() { return new Traversal(base_traversal_ptr(self)); }
	public long getRootSignature() { return get_root_signature(self); }
	
	private static native long new_();
	private static native void delete_(long self);
	private static native boolean equal_traversal_ptr(long self, long base);
	private static native long cast_traversal_ptr(long self);
	private static native long base_traversal_ptr(long self);
	private static native long get_root_signature(long self);
	
	protected D3D12Traversal(long self) {
		init_(self);
	}
	public static D3D12Traversal Null() {
		return new D3D12Traversal((long)0);
	}
}

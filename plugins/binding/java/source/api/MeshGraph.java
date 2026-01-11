// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;

/*
 */
public class MeshGraph {
	
	public static abstract class ProgressCallback {
		public abstract boolean run(int progress);
		public boolean run_(int progress) { return run(progress); }
	}
	
	public static boolean create(Mesh dest, Mesh src, int max_attributes, int max_primitives) { return create_(dest.self, src.self, max_attributes, max_primitives, null, 0); }
	public static boolean create(Mesh dest, Mesh src, int max_attributes, int max_primitives, ProgressCallback func) { return create_(dest.self, src.self, max_attributes, max_primitives, func, 0); }
	public static boolean create(Mesh dest, Mesh src, int max_attributes, int max_primitives, ProgressCallback func, Async async) { return create_(dest.self, src.self, max_attributes, max_primitives, func, async.self); }
	
	private static native boolean create_(long dest, long src, int max_attributes, int max_primitives, ProgressCallback func, long async);
}

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;

/*
 */
public class MeshSolid {
	
	public static abstract class ProgressCallback {
		public abstract boolean run(int progress);
		public boolean run_(int progress) { return run(progress); }
	}
	
	public static boolean create(Mesh dest, Mesh src) { return create_(dest.self, src.self, 1.0f, 0.9f, null); }
	public static boolean create(Mesh dest, Mesh src, float ratio) { return create_(dest.self, src.self, ratio, 0.9f, null); }
	public static boolean create(Mesh dest, Mesh src, float ratio, float threshold) { return create_(dest.self, src.self, ratio, threshold, null); }
	public static boolean create(Mesh dest, Mesh src, float ratio, float threshold, ProgressCallback func) { return create_(dest.self, src.self, ratio, threshold, func); }
	public static boolean create(MeshGeometry dest, MeshGeometry src) { return create_1(dest.self, src.self, 1.0f, 0.9f, null, Base.Maxu32); }
	public static boolean create(MeshGeometry dest, MeshGeometry src, float ratio) { return create_1(dest.self, src.self, ratio, 0.9f, null, Base.Maxu32); }
	public static boolean create(MeshGeometry dest, MeshGeometry src, float ratio, float threshold) { return create_1(dest.self, src.self, ratio, threshold, null, Base.Maxu32); }
	public static boolean create(MeshGeometry dest, MeshGeometry src, float ratio, float threshold, ProgressCallback func) { return create_1(dest.self, src.self, ratio, threshold, func, Base.Maxu32); }
	public static boolean create(MeshGeometry dest, MeshGeometry src, float ratio, float threshold, ProgressCallback func, int position) { return create_1(dest.self, src.self, ratio, threshold, func, position); }
	
	private static native boolean create_(long dest, long src, float ratio, float threshold, ProgressCallback func);
	private static native boolean create_1(long dest, long src, float ratio, float threshold, ProgressCallback func, int position);
}

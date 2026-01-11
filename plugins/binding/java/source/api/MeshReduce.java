// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;

/*
 */
public class MeshReduce {
	
	public static abstract class ProgressCallback {
		public abstract boolean run(int progress);
		public boolean run_(int progress) { return run(progress); }
	}
	
	public static boolean collapse(Mesh dest, Mesh src, float ratio) { return collapse_(dest.self, src.self, ratio, 0.0f, null); }
	public static boolean collapse(Mesh dest, Mesh src, float ratio, float threshold) { return collapse_(dest.self, src.self, ratio, threshold, null); }
	public static boolean collapse(Mesh dest, Mesh src, float ratio, float threshold, ProgressCallback func) { return collapse_(dest.self, src.self, ratio, threshold, func); }
	public static boolean collapse(MeshGeometry dest, MeshGeometry src, float ratio) { return collapse_1(dest.self, src.self, ratio, 0.0f, null, Base.Maxu32); }
	public static boolean collapse(MeshGeometry dest, MeshGeometry src, float ratio, float threshold) { return collapse_1(dest.self, src.self, ratio, threshold, null, Base.Maxu32); }
	public static boolean collapse(MeshGeometry dest, MeshGeometry src, float ratio, float threshold, ProgressCallback func) { return collapse_1(dest.self, src.self, ratio, threshold, func, Base.Maxu32); }
	public static boolean collapse(MeshGeometry dest, MeshGeometry src, float ratio, float threshold, ProgressCallback func, int position) { return collapse_1(dest.self, src.self, ratio, threshold, func, position); }
	
	private static native boolean collapse_(long dest, long src, float ratio, float threshold, ProgressCallback func);
	private static native boolean collapse_1(long dest, long src, float ratio, float threshold, ProgressCallback func, int position);
}

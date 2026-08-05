// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;

/*
 */
public class MeshSplit {
	
	public static boolean split(Mesh front, Mesh cross, Mesh back, Mesh src, Matrix4x3f basis) { return split_(front.self, cross.self, back.self, src.self, basis.self); }
	public static boolean split(MeshGeometry front, MeshGeometry cross, MeshGeometry back, MeshGeometry src, Matrix4x3f basis) { return split_1(front.self, cross.self, back.self, src.self, basis.self, Base.Maxu32); }
	public static boolean split(MeshGeometry front, MeshGeometry cross, MeshGeometry back, MeshGeometry src, Matrix4x3f basis, int position) { return split_1(front.self, cross.self, back.self, src.self, basis.self, position); }
	
	private static native boolean split_(long front, long cross, long back, long src, long basis);
	private static native boolean split_1(long front, long cross, long back, long src, long basis, int position);
}

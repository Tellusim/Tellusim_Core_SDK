// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;

/*
 */
public class MeshRefine {
	
	public static boolean subdiv(Mesh dest, Mesh src, int steps) { return subdiv_(dest.self, src.self, steps, 1.0f); }
	public static boolean subdiv(Mesh dest, Mesh src, int steps, float weight) { return subdiv_(dest.self, src.self, steps, weight); }
	public static boolean subdiv(MeshGeometry dest, MeshGeometry src, int steps) { return subdiv_1(dest.self, src.self, steps, 1.0f, Base.Maxu32); }
	public static boolean subdiv(MeshGeometry dest, MeshGeometry src, int steps, float weight) { return subdiv_1(dest.self, src.self, steps, weight, Base.Maxu32); }
	public static boolean subdiv(MeshGeometry dest, MeshGeometry src, int steps, float weight, int position) { return subdiv_1(dest.self, src.self, steps, weight, position); }
	
	private static native boolean subdiv_(long dest, long src, int steps, float weight);
	private static native boolean subdiv_1(long dest, long src, int steps, float weight, int position);
}

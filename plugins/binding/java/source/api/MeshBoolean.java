// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;

/*
 */
public class MeshBoolean {
	
	public static class Operation {
		public enum Enum {
			OpUnion(0),
			OpDifference(1),
			OpIntersection(2);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum OpUnion = Enum.OpUnion;
		public static final Enum OpDifference = Enum.OpDifference;
		public static final Enum OpIntersection = Enum.OpIntersection;
		public Operation(int value) { this.value = value; }
		public Operation(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static boolean intersect(MeshGeometry dest, MeshGeometry src_0, MeshGeometry src_1, Operation op) { return intersect_(dest.self, src_0.self, src_1.self, op.value); }
	public static boolean intersect(MeshGeometry dest, MeshGeometry src_0, MeshGeometry src_1, Operation.Enum op) { return intersect_(dest.self, src_0.self, src_1.self, op.value); }
	public static boolean intersect(MeshGeometry dest_0, MeshGeometry dest_1, MeshGeometry src_0, MeshGeometry src_1, Operation op) { return intersect_1(dest_0.self, dest_1.self, src_0.self, src_1.self, op.value); }
	public static boolean intersect(MeshGeometry dest_0, MeshGeometry dest_1, MeshGeometry src_0, MeshGeometry src_1, Operation.Enum op) { return intersect_1(dest_0.self, dest_1.self, src_0.self, src_1.self, op.value); }
	
	private static native boolean intersect_(long dest, long src_0, long src_1, int op);
	private static native boolean intersect_1(long dest_0, long dest_1, long src_0, long src_1, int op);
}

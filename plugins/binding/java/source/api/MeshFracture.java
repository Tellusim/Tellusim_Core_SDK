// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;

/*
 */
public class MeshFracture {
	
	public static boolean split(Mesh dest, Mesh src, Vector3f[] points, int num_points) { return split_(dest.self, src.self, Vector3f.self_(points), num_points, Vector2f.one().self, 1e-3f, 1e-3f, 1e-3f, 0); }
	public static boolean split(Mesh dest, Mesh src, Vector3f[] points, int num_points, Vector2f texcoord) { return split_(dest.self, src.self, Vector3f.self_(points), num_points, texcoord.self, 1e-3f, 1e-3f, 1e-3f, 0); }
	public static boolean split(Mesh dest, Mesh src, Vector3f[] points, int num_points, Vector2f texcoord, float threshold) { return split_(dest.self, src.self, Vector3f.self_(points), num_points, texcoord.self, threshold, 1e-3f, 1e-3f, 0); }
	public static boolean split(Mesh dest, Mesh src, Vector3f[] points, int num_points, Vector2f texcoord, float threshold, float collapse) { return split_(dest.self, src.self, Vector3f.self_(points), num_points, texcoord.self, threshold, collapse, 1e-3f, 0); }
	public static boolean split(Mesh dest, Mesh src, Vector3f[] points, int num_points, Vector2f texcoord, float threshold, float collapse, float volume) { return split_(dest.self, src.self, Vector3f.self_(points), num_points, texcoord.self, threshold, collapse, volume, 0); }
	public static boolean split(Mesh dest, Mesh src, Vector3f[] points, int num_points, Vector2f texcoord, float threshold, float collapse, float volume, Async async) { return split_(dest.self, src.self, Vector3f.self_(points), num_points, texcoord.self, threshold, collapse, volume, async.self); }
	
	private static native boolean split_(long dest, long src, long[] points, int num_points, long texcoord, float threshold, float collapse, float volume, long async);
}

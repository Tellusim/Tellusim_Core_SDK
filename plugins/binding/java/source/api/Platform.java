// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;

/*
 */
public class Platform {
	public enum Enum {
		Unknown(0),
		Fusion(1),
		D3D12(2),
		D3D11(3),
		MTL(4),
		VK(5),
		GL(6),
		GLES(7),
		WG(8),
		CU(9),
		HIP(10),
		Any(11),
		NumPlatforms(12);
		Enum(int value) { this.value = value; }
		public int value;
	}
	public static final Enum Unknown = Enum.Unknown;
	public static final Enum Fusion = Enum.Fusion;
	public static final Enum D3D12 = Enum.D3D12;
	public static final Enum D3D11 = Enum.D3D11;
	public static final Enum MTL = Enum.MTL;
	public static final Enum VK = Enum.VK;
	public static final Enum GL = Enum.GL;
	public static final Enum GLES = Enum.GLES;
	public static final Enum WG = Enum.WG;
	public static final Enum CU = Enum.CU;
	public static final Enum HIP = Enum.HIP;
	public static final Enum Any = Enum.Any;
	public static final Enum NumPlatforms = Enum.NumPlatforms;
	public Platform(int value) { this.value = value; }
	public Platform(Enum e) { this(e.value); }
	public boolean equals(int v) { return (value == v); }
	public boolean equals(Enum e) { return (value == e.value); }
	public int value;
}

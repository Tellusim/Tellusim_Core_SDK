// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;

/*
 */
public class Vendor {
	public enum Enum {
		ARM(0x13b5),
		AMD(0x1002),
		Apple(0x106b),
		Intel(0x8086),
		Nvidia(0x10de),
		Qualcomm(0x5143);
		Enum(int value) { this.value = value; }
		public int value;
	}
	public static final Enum ARM = Enum.ARM;
	public static final Enum AMD = Enum.AMD;
	public static final Enum Apple = Enum.Apple;
	public static final Enum Intel = Enum.Intel;
	public static final Enum Nvidia = Enum.Nvidia;
	public static final Enum Qualcomm = Enum.Qualcomm;
	public Vendor(int value) { this.value = value; }
	public Vendor(Enum e) { this(e.value); }
	public boolean equals(int v) { return (value == v); }
	public boolean equals(Enum e) { return (value == e.value); }
	public int value;
}

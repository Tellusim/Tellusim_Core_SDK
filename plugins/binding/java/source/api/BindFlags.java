// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;

/*
 */
public class BindFlags {
	public enum Enum {
		BindFlagNone(0),
		BindFlagFixed(1),
		BindFlagRead(2);
		Enum(int value) { this.value = value; }
		public int value;
	}
	public static final Enum BindFlagNone = Enum.BindFlagNone;
	public static final Enum BindFlagFixed = Enum.BindFlagFixed;
	public static final Enum BindFlagRead = Enum.BindFlagRead;
	public BindFlags(int value) { this.value = value; }
	public BindFlags(Enum e) { this(e.value); }
	public boolean equals(int v) { return (value == v); }
	public boolean equals(Enum e) { return (value == e.value); }
	public int value;
}

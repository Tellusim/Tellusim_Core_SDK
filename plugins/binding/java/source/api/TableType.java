// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;

/*
 */
public class TableType {
	public enum Enum {
		Texture(0),
		Storage(1),
		NumTableTypes(2);
		Enum(int value) { this.value = value; }
		public TableType and(TableType e) { return new TableType(value & e.value); }
		public TableType and(Enum e) { return new TableType(value & e.value); }
		public TableType or(TableType e) { return new TableType(value | e.value); }
		public TableType or(Enum e) { return new TableType(value | e.value); }
		public boolean has(TableType e) { return ((value & e.value) != 0); }
		public boolean has(Enum e) { return ((value & e.value) != 0); }
		public int value;
	}
	public static final Enum Texture = Enum.Texture;
	public static final Enum Storage = Enum.Storage;
	public static final Enum NumTableTypes = Enum.NumTableTypes;
	public TableType(int value) { this.value = value; }
	public TableType(Enum e) { this(e.value); }
	public boolean equals(int v) { return (value == v); }
	public boolean equals(Enum e) { return (value == e.value); }
	public TableType(Enum e0, Enum e1) { this(e0.value | e1.value); }
	public TableType(Enum e0, Enum e1, Enum e2) { this(e0.value | e1.value | e2.value); }
	public TableType(Enum e0, Enum e1, Enum e2, Enum e3) { this(e0.value | e1.value | e2.value | e3.value); }
	public TableType not() { return new TableType(~value); }
	public TableType and(TableType e) { return new TableType(value & e.value); }
	public TableType and(Enum e) { return new TableType(value & e.value); }
	public TableType or(TableType e) { return new TableType(value | e.value); }
	public TableType or(Enum e) { return new TableType(value | e.value); }
	public boolean has(TableType e) { return ((value & e.value) != 0); }
	public boolean has(Enum e) { return ((value & e.value) != 0); }
	public int value;
}

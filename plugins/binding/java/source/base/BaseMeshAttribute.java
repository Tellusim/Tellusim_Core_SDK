// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.nio.ByteBuffer;

/*
 */
public abstract class BaseMeshAttribute {
	
	public abstract void setValue(int index, byte[] src);
	public <Type extends Bytes> void set(int index, Type value) {
		setValue(index, value.getBytes());
	}
}

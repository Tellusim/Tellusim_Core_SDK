// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.nio.ByteOrder;
import java.nio.ByteBuffer;

/*
 */
public abstract class BaseCompute {
	
	/// uniform buffer
	public abstract void setUniformData(int index, byte[] src);
	public void setUniform(int index, ByteBuffer buffer) {
		setUniformData(index, buffer.array());
	}
	public <Type extends Bytes> void setUniform(int index, Type value) {
		setUniformData(index, value.getBytes());
	}
	public <Type extends Bytes> void setUniform(int index, Type[] values) {
		ByteBuffer buffer = ByteBuffer.allocate(values.length * values[0].getBytes().length).order(ByteOrder.LITTLE_ENDIAN);
		for(Type value : values) if(value != null) buffer.put(value.getBytes());
		setUniformData(index, buffer.array());
	}
	
	/// storage buffer
	public abstract void setStorageData(int index, byte[] src);
	public void setStorage(int index, ByteBuffer buffer) {
		setStorageData(index, buffer.array());
	}
	public <Type extends Bytes> void setStorage(int index, Type value) {
		setStorageData(index, value.getBytes());
	}
	public <Type extends Bytes> void setStorage(int index, Type[] values) {
		ByteBuffer buffer = ByteBuffer.allocate(values.length * values[0].getBytes().length).order(ByteOrder.LITTLE_ENDIAN);
		for(Type value : values) if(value != null) buffer.put(value.getBytes());
		setStorageData(index, buffer.array());
	}
	
	/// indirect buffer
	public abstract void setIndirectData(byte[] src);
	public void setIndirect(ByteBuffer buffer) {
		setIndirectData(buffer.array());
	}
	public <Type extends Bytes> void setIndirect(Type value) {
		setIndirectData(value.getBytes());
	}
	public <Type extends Bytes> void setIndirect(Type[] values) {
		ByteBuffer buffer = ByteBuffer.allocate(values.length * values[0].getBytes().length).order(ByteOrder.LITTLE_ENDIAN);
		for(Type value : values) if(value != null) buffer.put(value.getBytes());
		setIndirectData(buffer.array());
	}
}

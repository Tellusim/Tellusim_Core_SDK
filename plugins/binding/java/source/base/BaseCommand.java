// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.nio.ByteOrder;
import java.nio.ByteBuffer;

/*
 */
public abstract class BaseCommand {
	
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
	
	/// vertex buffer
	public abstract void setVertexData(int index, byte[] src);
	public void setVertices(int index, ByteBuffer buffer) {
		setVertexData(index, buffer.array());
	}
	public <Type extends Bytes> void setVertices(int index, Type[] vertices) {
		ByteBuffer buffer = ByteBuffer.allocate(vertices.length * vertices[0].getBytes().length).order(ByteOrder.LITTLE_ENDIAN);
		for(Type vertex : vertices) if(vertex != null) buffer.put(vertex.getBytes());
		setVertexData(index, buffer.array());
	}
	
	/// index buffer
	public abstract void setIndexData(Format.Enum format, byte[] src);
	public void setIndices(short[] indices) {
		ByteBuffer buffer = ByteBuffer.allocate(indices.length * 2).order(ByteOrder.LITTLE_ENDIAN);
		buffer.asShortBuffer().put(indices);
		setIndexData(Format.Ru16, buffer.array());
	}
	public void setIndices(int[] indices) {
		ByteBuffer buffer = ByteBuffer.allocateDirect(indices.length * 4).order(ByteOrder.LITTLE_ENDIAN);
		buffer.asIntBuffer().put(indices);
		setIndexData(Format.Ru32, buffer.array());
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

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;

/*
 */
public class Layer {
	
	public Layer() { index = 0; size = 1; }
	public Layer(int i) { index = i; size = 1; }
	public Layer(int i, int s) { index = i; size = s; }
	
	public String toString() { return String.format("%d : %d", index, size); }
	
	public int index;
	public int size;
}

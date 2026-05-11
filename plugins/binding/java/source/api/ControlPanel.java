// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class ControlPanel extends ControlRect {
	
	public ControlPanel() { init_(new_()); }
	public ControlPanel(Control[] parent) { init_(new_1(Control.self_(parent))); }
	public ControlPanel(Control[] parent, int columns) { init_(new_2(Control.self_(parent), columns)); }
	public ControlPanel(Control[] parent, int columns, float x, float y) { init_(new_3(Control.self_(parent), columns, x, y)); }
	public ControlPanel[] ref() { return new ControlPanel[] { this }; }
	public ControlPanel(ControlRect base) { init_(cast_control_rect_ptr(base.self)); }
	public ControlRect toControlRect() { return new ControlRect(base_control_rect_ptr(self)); }
	public void setColumns(int columns) { set_columns(self, columns); }
	public int getColumns() { return get_columns(self); }
	public void setSpacing(Vector2f spacing) { set_spacing(self, spacing.self); }
	public void setSpacing(float x, float y) { set_spacing_1(self, x, y); }
	public Vector2f getSpacing() { return new Vector2f(get_spacing(self)); }
	public void setColumnRatio(int index, float ratio) { set_column_ratio(self, index, ratio); }
	public float getColumnRatio(int index) { return get_column_ratio(self, index); }
	public void setColumnSpacing(int index, float spacing) { set_column_spacing(self, index, spacing); }
	public float getColumnSpacing(int index) { return get_column_spacing(self, index); }
	public void setRowSpacing(int index, float spacing) { set_row_spacing(self, index, spacing); }
	public float getRowSpacing(int index) { return get_row_spacing(self, index); }
	public Vector2f getControlsSize() { return new Vector2f(get_controls_size(self)); }
	
	private static native long new_();
	private static native long new_1(long[] parent);
	private static native long new_2(long[] parent, int columns);
	private static native long new_3(long[] parent, int columns, float x, float y);
	private static native void delete_(long self);
	private static native boolean equal_control_rect_ptr(long self, long base);
	private static native long cast_control_rect_ptr(long self);
	private static native long base_control_rect_ptr(long self);
	private static native void set_columns(long self, int columns);
	private static native int get_columns(long self);
	private static native void set_spacing(long self, long spacing);
	private static native void set_spacing_1(long self, float x, float y);
	private static native long get_spacing(long self);
	private static native void set_column_ratio(long self, int index, float ratio);
	private static native float get_column_ratio(long self, int index);
	private static native void set_column_spacing(long self, int index, float spacing);
	private static native float get_column_spacing(long self, int index);
	private static native void set_row_spacing(long self, int index, float spacing);
	private static native float get_row_spacing(long self, int index);
	private static native long get_controls_size(long self);
	
	protected ControlPanel(long self) {
		init_(self);
	}
	public static ControlPanel Null() {
		return new ControlPanel((long)0);
	}
}

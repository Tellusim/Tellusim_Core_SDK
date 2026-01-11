// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class ControlDialog extends ControlPanel {
	
	public static abstract class UpdatedCallback {
		public abstract void run(ControlDialog a0);
		public void run_(long a0) { run(new ControlDialog(a0)); }
	}
	
	public ControlDialog() { init_(new_()); }
	public ControlDialog(Control[] parent) { init_(new_1(Control.self_(parent))); }
	public ControlDialog(Control[] parent, int columns) { init_(new_2(Control.self_(parent), columns)); }
	public ControlDialog(Control[] parent, int columns, float x, float y) { init_(new_3(Control.self_(parent), columns, x, y)); }
	public ControlDialog[] ref() { return new ControlDialog[] { this }; }
	public ControlDialog(ControlPanel base) { init_(cast_control_panel_ptr(base.self)); }
	public ControlPanel toControlPanel() { return new ControlPanel(base_control_panel_ptr(self)); }
	public void setConstrained(boolean constrained) { set_constrained(self, constrained); }
	public boolean isConstrained() { return is_constrained(self); }
	public void setResizable(boolean resizable) { set_resizable(self, resizable); }
	public boolean isResizable() { return is_resizable(self); }
	public void setMoveable(boolean moveable) { set_moveable(self, moveable); }
	public boolean isMoveable() { return is_moveable(self); }
	public void setResizeArea(float area) { set_resize_area(self, area); }
	public float getResizeArea() { return get_resize_area(self); }
	public Align getResizeAlign() { return new Align(get_resize_align(self)); }
	public boolean hasResizeAlign(Align align) { return has_resize_align(self, align.value); }
	public boolean hasResizeAlign(Align.Enum align) { return has_resize_align(self, align.value); }
	public boolean hasResizeAligns(Align aligns) { return has_resize_aligns(self, aligns.value); }
	public boolean hasResizeAligns(Align.Enum aligns) { return has_resize_aligns(self, aligns.value); }
	public void setMousePosition(Vector2f position) { set_mouse_position(self, position.self); }
	public Vector2f getMousePosition() { return new Vector2f(get_mouse_position(self)); }
	public void setUpdatedCallback(UpdatedCallback func) { set_updated_callback(self, func); }
	public boolean isUpdated() { return is_updated(self); }
	
	private static native long new_();
	private static native long new_1(long[] parent);
	private static native long new_2(long[] parent, int columns);
	private static native long new_3(long[] parent, int columns, float x, float y);
	private static native void delete_(long self);
	private static native boolean equal_control_panel_ptr(long self, long base);
	private static native long cast_control_panel_ptr(long self);
	private static native long base_control_panel_ptr(long self);
	private static native void set_constrained(long self, boolean constrained);
	private static native boolean is_constrained(long self);
	private static native void set_resizable(long self, boolean resizable);
	private static native boolean is_resizable(long self);
	private static native void set_moveable(long self, boolean moveable);
	private static native boolean is_moveable(long self);
	private static native void set_resize_area(long self, float area);
	private static native float get_resize_area(long self);
	private static native int get_resize_align(long self);
	private static native boolean has_resize_align(long self, int align);
	private static native boolean has_resize_aligns(long self, int aligns);
	private static native void set_mouse_position(long self, long position);
	private static native long get_mouse_position(long self);
	private static native void set_updated_callback(long self, UpdatedCallback func);
	private static native boolean is_updated(long self);
	
	protected ControlDialog(long self) {
		init_(self);
	}
	public static ControlDialog Null() {
		return new ControlDialog((long)0);
	}
}

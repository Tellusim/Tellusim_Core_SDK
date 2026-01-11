// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class ControlEdit extends ControlText {
	
	public static class EditMode {
		public enum Enum {
			Text(0),
			Password(1),
			Number(2),
			Signed(3),
			Unsigned(4),
			Hexadecimal(5);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Text = Enum.Text;
		public static final Enum Password = Enum.Password;
		public static final Enum Number = Enum.Number;
		public static final Enum Signed = Enum.Signed;
		public static final Enum Unsigned = Enum.Unsigned;
		public static final Enum Hexadecimal = Enum.Hexadecimal;
		public EditMode(int value) { this.value = value; }
		public EditMode(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static abstract class ClickedCallback {
		public abstract void run(ControlEdit a0);
		public void run_(long a0) { run(new ControlEdit(a0)); }
	}
	
	public static abstract class ChangedCallback {
		public abstract void run(ControlEdit a0);
		public void run_(long a0) { run(new ControlEdit(a0)); }
	}
	
	public static abstract class ReturnedCallback {
		public abstract void run(ControlEdit a0);
		public void run_(long a0) { run(new ControlEdit(a0)); }
	}
	
	public ControlEdit() { init_(new_()); }
	public ControlEdit(Control[] parent) { init_(new_1(Control.self_(parent))); }
	public ControlEdit(Control[] parent, String text) { init_(new_2(Control.self_(parent), text)); }
	public ControlEdit(Control[] parent, TSString text) { init_(new_3(Control.self_(parent), text.self)); }
	public ControlEdit[] ref() { return new ControlEdit[] { this }; }
	public ControlEdit(ControlText base) { init_(cast_control_text_ptr(base.self)); }
	public ControlText toControlText() { return new ControlText(base_control_text_ptr(self)); }
	public void setFrame(boolean frame) { set_frame(self, frame); }
	public boolean getFrame() { return get_frame(self); }
	public void setBackground(boolean background) { set_background(self, background); }
	public boolean getBackground() { return get_background(self); }
	public void setEditColor(Color color) { set_edit_color(self, color.self); }
	public Color getEditColor() { return new Color(get_edit_color(self)); }
	public void setEditMode(EditMode mode) { set_edit_mode(self, mode.value); }
	public void setEditMode(EditMode.Enum mode) { set_edit_mode(self, mode.value); }
	public EditMode getEditMode() { return new EditMode(get_edit_mode(self)); }
	public void setPasswordCode(int code) { set_password_code(self, code); }
	public int getPasswordCode() { return get_password_code(self); }
	public int getNumCodes() { return get_num_codes(self); }
	public long getCodes() { return get_codes(self); }
	public void setCurrentIndex(int index) { set_current_index(self, index, Base.Maxu32); }
	public void setCurrentIndex(int index, int selection_index) { set_current_index(self, index, selection_index); }
	public int getCurrentIndex() { return get_current_index(self); }
	public int getSelectionIndex() { return get_selection_index(self); }
	public void setSelection() { set_selection(self, false, false); }
	public void setSelection(boolean current) { set_selection(self, current, false); }
	public void setSelection(boolean current, boolean changed) { set_selection(self, current, changed); }
	public void clearSelection() { clear_selection(self); }
	public String getSelectedText() { return get_selected_text(self); }
	public boolean updateKeyboard(ControlRoot root, int key, int code) { return update_keyboard(self, root.self, key, code); }
	public void setClickedCallback(ClickedCallback func) { set_clicked_callback(self, func); }
	public boolean isClicked() { return is_clicked(self); }
	public void setChangedCallback(ChangedCallback func) { set_changed_callback(self, func); }
	public boolean isChanged() { return is_changed(self); }
	public void setReturnedCallback(ReturnedCallback func) { set_returned_callback(self, func); }
	public boolean isReturned() { return is_returned(self); }
	public CanvasMesh getCanvasMesh() { return new CanvasMesh(get_canvas_mesh(self)); }
	
	private static native long new_();
	private static native long new_1(long[] parent);
	private static native long new_2(long[] parent, String text);
	private static native long new_3(long[] parent, long text);
	private static native void delete_(long self);
	private static native boolean equal_control_text_ptr(long self, long base);
	private static native long cast_control_text_ptr(long self);
	private static native long base_control_text_ptr(long self);
	private static native void set_frame(long self, boolean frame);
	private static native boolean get_frame(long self);
	private static native void set_background(long self, boolean background);
	private static native boolean get_background(long self);
	private static native void set_edit_color(long self, long color);
	private static native long get_edit_color(long self);
	private static native void set_edit_mode(long self, int mode);
	private static native int get_edit_mode(long self);
	private static native void set_password_code(long self, int code);
	private static native int get_password_code(long self);
	private static native int get_num_codes(long self);
	private static native long get_codes(long self);
	private static native void set_current_index(long self, int index, int selection_index);
	private static native int get_current_index(long self);
	private static native int get_selection_index(long self);
	private static native void set_selection(long self, boolean current, boolean changed);
	private static native void clear_selection(long self);
	private static native String get_selected_text(long self);
	private static native boolean update_keyboard(long self, long root, int key, int code);
	private static native void set_clicked_callback(long self, ClickedCallback func);
	private static native boolean is_clicked(long self);
	private static native void set_changed_callback(long self, ChangedCallback func);
	private static native boolean is_changed(long self);
	private static native void set_returned_callback(long self, ReturnedCallback func);
	private static native boolean is_returned(long self);
	private static native long get_canvas_mesh(long self);
	
	protected ControlEdit(long self) {
		init_(self);
	}
	public static ControlEdit Null() {
		return new ControlEdit((long)0);
	}
}

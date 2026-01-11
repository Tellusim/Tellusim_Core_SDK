// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class ControlCombo extends ControlText {
	
	public static abstract class ClickedCallback {
		public abstract void run(ControlCombo a0);
		public void run_(long a0) { run(new ControlCombo(a0)); }
	}
	
	public static abstract class ChangedCallback {
		public abstract void run(ControlCombo a0);
		public void run_(long a0) { run(new ControlCombo(a0)); }
	}
	
	public ControlCombo() { init_(new_()); }
	public ControlCombo(Control[] parent) { init_(new_1(Control.self_(parent))); }
	public ControlCombo[] ref() { return new ControlCombo[] { this }; }
	public ControlCombo(ControlText base) { init_(cast_control_text_ptr(base.self)); }
	public ControlText toControlText() { return new ControlText(base_control_text_ptr(self)); }
	public void setTextEnabled(boolean enabled) { set_text_enabled(self, enabled); }
	public boolean isTextEnabled() { return is_text_enabled(self); }
	public void setMultiSelection(boolean multi_selection) { set_multi_selection(self, multi_selection); }
	public boolean isMultiSelection() { return is_multi_selection(self); }
	public void setComboText(String text) { set_combo_text(self, text); }
	public void setComboText(TSString text) { set_combo_text_1(self, text.self); }
	public String getComboText() { return get_combo_text(self); }
	public void setComboColor(Color color) { set_combo_color(self, color.self); }
	public Color getComboColor() { return new Color(get_combo_color(self)); }
	public void setItemsSpacing(float spacing) { set_items_spacing(self, spacing); }
	public float getItemsSpacing() { return get_items_spacing(self); }
	public void clearItems() { clear_items(self); }
	public int addItem(String text) { return add_item(self, text); }
	public int addItem(TSString text) { return add_item_1(self, text.self); }
	public void addItem(int index, String text) { add_item_2(self, index, text); }
	public void addItem(int index, TSString text) { add_item_3(self, index, text.self); }
	public void removeItem(int index) { remove_item(self, index); }
	public int getNumItems() { return get_num_items(self); }
	public boolean switchItemSelected(int index) { return switch_item_selected(self, index); }
	public void setItemSelected(int index, boolean selected) { set_item_selected(self, index, selected); }
	public boolean isItemSelected(int index) { return is_item_selected(self, index); }
	public void setItemText(int index, String text) { set_item_text(self, index, text); }
	public void setItemText(int index, TSString text) { set_item_text_1(self, index, text.self); }
	public String getItemText(int index) { return get_item_text(self, index); }
	public int findItemText(String text) { return find_item_text(self, text); }
	public int findItemText(TSString text) { return find_item_text_1(self, text.self); }
	public void setItemColor(int index, Color color) { set_item_color(self, index, color.self); }
	public Color getItemColor(int index) { return new Color(get_item_color(self, index)); }
	public void setCurrentIndex(int index) { set_current_index(self, index, false); }
	public void setCurrentIndex(int index, boolean callback) { set_current_index(self, index, callback); }
	public boolean setCurrentText(String text) { return set_current_text(self, text, false); }
	public boolean setCurrentText(String text, boolean callback) { return set_current_text(self, text, callback); }
	public boolean setCurrentText(TSString text) { return set_current_text_1(self, text.self, false); }
	public boolean setCurrentText(TSString text, boolean callback) { return set_current_text_1(self, text.self, callback); }
	public int getCurrentIndex() { return get_current_index(self); }
	public String getCurrentText() { return get_current_text(self); }
	public void setClickedCallback(ClickedCallback func) { set_clicked_callback(self, func); }
	public boolean isClicked() { return is_clicked(self); }
	public void setChangedCallback(ChangedCallback func) { set_changed_callback(self, func); }
	public boolean isChanged() { return is_changed(self); }
	public CanvasMesh getCanvasMesh() { return new CanvasMesh(get_canvas_mesh(self)); }
	
	private static native long new_();
	private static native long new_1(long[] parent);
	private static native void delete_(long self);
	private static native boolean equal_control_text_ptr(long self, long base);
	private static native long cast_control_text_ptr(long self);
	private static native long base_control_text_ptr(long self);
	private static native void set_text_enabled(long self, boolean enabled);
	private static native boolean is_text_enabled(long self);
	private static native void set_multi_selection(long self, boolean multi_selection);
	private static native boolean is_multi_selection(long self);
	private static native void set_combo_text(long self, String text);
	private static native void set_combo_text_1(long self, long text);
	private static native String get_combo_text(long self);
	private static native void set_combo_color(long self, long color);
	private static native long get_combo_color(long self);
	private static native void set_items_spacing(long self, float spacing);
	private static native float get_items_spacing(long self);
	private static native void clear_items(long self);
	private static native int add_item(long self, String text);
	private static native int add_item_1(long self, long text);
	private static native void add_item_2(long self, int index, String text);
	private static native void add_item_3(long self, int index, long text);
	private static native void remove_item(long self, int index);
	private static native int get_num_items(long self);
	private static native boolean switch_item_selected(long self, int index);
	private static native void set_item_selected(long self, int index, boolean selected);
	private static native boolean is_item_selected(long self, int index);
	private static native void set_item_text(long self, int index, String text);
	private static native void set_item_text_1(long self, int index, long text);
	private static native String get_item_text(long self, int index);
	private static native int find_item_text(long self, String text);
	private static native int find_item_text_1(long self, long text);
	private static native void set_item_color(long self, int index, long color);
	private static native long get_item_color(long self, int index);
	private static native void set_current_index(long self, int index, boolean callback);
	private static native boolean set_current_text(long self, String text, boolean callback);
	private static native boolean set_current_text_1(long self, long text, boolean callback);
	private static native int get_current_index(long self);
	private static native String get_current_text(long self);
	private static native void set_clicked_callback(long self, ClickedCallback func);
	private static native boolean is_clicked(long self);
	private static native void set_changed_callback(long self, ChangedCallback func);
	private static native boolean is_changed(long self);
	private static native long get_canvas_mesh(long self);
	
	protected ControlCombo(long self) {
		init_(self);
	}
	public static ControlCombo Null() {
		return new ControlCombo((long)0);
	}
}

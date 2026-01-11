// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class ControlTree extends ControlText {
	
	public static abstract class ChangedCallback {
		public abstract void run(ControlTree a0, int item);
		public void run_(long a0, int item) { run(new ControlTree(a0), item); }
	}
	
	public static abstract class DraggedCallback {
		public abstract boolean run(ControlTree a0, int item);
		public boolean run_(long a0, int item) { return run(new ControlTree(a0), item); }
	}
	
	public static abstract class DroppedCallback {
		public abstract void run(ControlTree a0, int item);
		public void run_(long a0, int item) { run(new ControlTree(a0), item); }
	}
	
	public static abstract class ClickedCallback {
		public abstract void run(ControlTree a0, int item);
		public void run_(long a0, int item) { run(new ControlTree(a0), item); }
	}
	
	public static abstract class ExpandedCallback {
		public abstract void run(ControlTree a0, int item);
		public void run_(long a0, int item) { run(new ControlTree(a0), item); }
	}
	
	public static abstract class SelectedCallback {
		public abstract void run(ControlTree a0);
		public void run_(long a0) { run(new ControlTree(a0)); }
	}
	
	public ControlTree() { init_(new_()); }
	public ControlTree(Control[] parent) { init_(new_1(Control.self_(parent))); }
	public ControlTree[] ref() { return new ControlTree[] { this }; }
	public ControlTree(ControlText base) { init_(cast_control_text_ptr(base.self)); }
	public ControlText toControlText() { return new ControlText(base_control_text_ptr(self)); }
	public void setSelectable(boolean selectable) { set_selectable(self, selectable); }
	public boolean isSelectable() { return is_selectable(self); }
	public void setMultiSelection(boolean multi_selection) { set_multi_selection(self, multi_selection); }
	public boolean isMultiSelection() { return is_multi_selection(self); }
	public void setFoldedText(String text) { set_folded_text(self, text); }
	public void setFoldedText(TSString text) { set_folded_text_1(self, text.self); }
	public String getFoldedText() { return get_folded_text(self); }
	public void setExpandedText(String text) { set_expanded_text(self, text); }
	public void setExpandedText(TSString text) { set_expanded_text_1(self, text.self); }
	public String getExpandedText() { return get_expanded_text(self); }
	public void setTexture(Texture texture) { set_texture(self, texture.self, 1, 1); }
	public void setTexture(Texture texture, int rows) { set_texture(self, texture.self, rows, 1); }
	public void setTexture(Texture texture, int rows, int columns) { set_texture(self, texture.self, rows, columns); }
	public Texture getTexture() { return new Texture(get_texture(self)); }
	public void setTextureName(String name) { set_texture_name(self, name, 1, 1); }
	public void setTextureName(String name, int rows) { set_texture_name(self, name, rows, 1); }
	public void setTextureName(String name, int rows, int columns) { set_texture_name(self, name, rows, columns); }
	public void setTextureName(TSString name) { set_texture_name_1(self, name.self, 1, 1); }
	public void setTextureName(TSString name, int rows) { set_texture_name_1(self, name.self, rows, 1); }
	public void setTextureName(TSString name, int rows, int columns) { set_texture_name_1(self, name.self, rows, columns); }
	public String getTextureName() { return get_texture_name(self); }
	public void setTextureGrid(int rows, int columns) { set_texture_grid(self, rows, columns); }
	public int getTextureRows() { return get_texture_rows(self); }
	public int getTextureColumns() { return get_texture_columns(self); }
	public void clearItems() { clear_items(self); }
	public int addItem(String text) { return add_item(self, text, Base.Maxu32, true); }
	public int addItem(String text, int parent) { return add_item(self, text, parent, true); }
	public int addItem(String text, int parent, boolean expanded) { return add_item(self, text, parent, expanded); }
	public int addItem(TSString text) { return add_item_1(self, text.self, Base.Maxu32, true); }
	public int addItem(TSString text, int parent) { return add_item_1(self, text.self, parent, true); }
	public int addItem(TSString text, int parent, boolean expanded) { return add_item_1(self, text.self, parent, expanded); }
	public void removeItem(int item) { remove_item(self, item, false); }
	public void removeItem(int item, boolean children) { remove_item(self, item, children); }
	public void viewItem(int item) { view_item(self, item); }
	public int getNumItems() { return get_num_items(self); }
	public int getItem(int index) { return get_item(self, index); }
	public boolean switchItemHidden(int item) { return switch_item_hidden(self, item, false); }
	public boolean switchItemHidden(int item, boolean children) { return switch_item_hidden(self, item, children); }
	public void setItemHidden(int item, boolean hidden) { set_item_hidden(self, item, hidden, false); }
	public void setItemHidden(int item, boolean hidden, boolean children) { set_item_hidden(self, item, hidden, children); }
	public boolean isItemHidden(int item) { return is_item_hidden(self, item); }
	public boolean switchItemExpanded(int item) { return switch_item_expanded(self, item, false); }
	public boolean switchItemExpanded(int item, boolean children) { return switch_item_expanded(self, item, children); }
	public void setItemExpanded(int item, boolean expanded) { set_item_expanded(self, item, expanded, false); }
	public void setItemExpanded(int item, boolean expanded, boolean children) { set_item_expanded(self, item, expanded, children); }
	public boolean isItemExpanded(int item) { return is_item_expanded(self, item); }
	public boolean switchItemSelected(int item) { return switch_item_selected(self, item, false); }
	public boolean switchItemSelected(int item, boolean children) { return switch_item_selected(self, item, children); }
	public void setItemSelected(int item, boolean selected) { set_item_selected(self, item, selected, false); }
	public void setItemSelected(int item, boolean selected, boolean children) { set_item_selected(self, item, selected, children); }
	public boolean isItemSelected(int item) { return is_item_selected(self, item); }
	public void setItemParent(int item, int parent) { set_item_parent(self, item, parent); }
	public int getItemParent(int item) { return get_item_parent(self, item); }
	public boolean isItemParent(int item, int parent) { return is_item_parent(self, item, parent, false); }
	public boolean isItemParent(int item, int parent, boolean hierarchy) { return is_item_parent(self, item, parent, hierarchy); }
	public void addItemChild(int item, int child) { add_item_child(self, item, child); }
	public void removeItemChild(int item, int child) { remove_item_child(self, item, child); }
	public void addItemChildren(int item, int[] children) { add_item_children(self, item, children); }
	public void removeItemChildren(int item, int[] children) { remove_item_children(self, item, children); }
	public int findItemChild(int item, int child) { return find_item_child(self, item, child); }
	public boolean isItemChild(int item, int child) { return is_item_child(self, item, child); }
	public int getNumItemChildren(int item) { return get_num_item_children(self, item); }
	public int getItemChild(int item, int index) { return get_item_child(self, item, index); }
	public void setItemText(int item, String text) { set_item_text(self, item, text); }
	public void setItemText(int item, TSString text) { set_item_text_1(self, item, text.self); }
	public String getItemText(int item) { return get_item_text(self, item); }
	public int findItemText(String text) { return find_item_text(self, text); }
	public int findItemText(TSString text) { return find_item_text_1(self, text.self); }
	public void setItemColor(int item, Color color) { set_item_color(self, item, color.self); }
	public Color getItemColor(int item) { return new Color(get_item_color(self, item)); }
	public void setItemTexture(int item, int row) { set_item_texture(self, item, row, 0); }
	public void setItemTexture(int item, int row, int column) { set_item_texture(self, item, row, column); }
	public int getItemTextureRow(int item) { return get_item_texture_row(self, item); }
	public int getItemTextureColumn(int item) { return get_item_texture_column(self, item); }
	public void setItemData(int item, long data) { set_item_data(self, item, data); }
	public long getItemData(int item) { return get_item_data(self, item); }
	public int getFocusedItem() { return get_focused_item(self); }
	public void setCurrentItem(int item) { set_current_item(self, item, false, false, false); }
	public void setCurrentItem(int item, boolean select) { set_current_item(self, item, select, false, false); }
	public void setCurrentItem(int item, boolean select, boolean view) { set_current_item(self, item, select, view, false); }
	public void setCurrentItem(int item, boolean select, boolean view, boolean callback) { set_current_item(self, item, select, view, callback); }
	public int getCurrentItem() { return get_current_item(self); }
	public String getCurrentText() { return get_current_text(self); }
	public void setSelection() { set_selection(self); }
	public void clearSelection() { clear_selection(self); }
	public void inverseSelection() { inverse_selection(self); }
	public int getNumSelectedItems() { return get_num_selected_items(self); }
	public int getSelectedItem(int index) { return get_selected_item(self, index); }
	public void setChangedCallback(ChangedCallback func) { set_changed_callback(self, func); }
	public void setDraggedCallback(DraggedCallback func) { set_dragged_callback(self, func); }
	public void setDroppedCallback(DroppedCallback func) { set_dropped_callback(self, func); }
	public void setClickedCallback(ClickedCallback func) { set_clicked_callback(self, func); }
	public void setClicked2Callback(ClickedCallback func) { set_clicked2_callback(self, func); }
	public void setClickedRightCallback(ClickedCallback func) { set_clicked_right_callback(self, func); }
	public void setExpandedCallback(ExpandedCallback func) { set_expanded_callback(self, func); }
	public void setSelectedCallback(SelectedCallback func) { set_selected_callback(self, func); }
	
	private static native long new_();
	private static native long new_1(long[] parent);
	private static native void delete_(long self);
	private static native boolean equal_control_text_ptr(long self, long base);
	private static native long cast_control_text_ptr(long self);
	private static native long base_control_text_ptr(long self);
	private static native void set_selectable(long self, boolean selectable);
	private static native boolean is_selectable(long self);
	private static native void set_multi_selection(long self, boolean multi_selection);
	private static native boolean is_multi_selection(long self);
	private static native void set_folded_text(long self, String text);
	private static native void set_folded_text_1(long self, long text);
	private static native String get_folded_text(long self);
	private static native void set_expanded_text(long self, String text);
	private static native void set_expanded_text_1(long self, long text);
	private static native String get_expanded_text(long self);
	private static native void set_texture(long self, long texture, int rows, int columns);
	private static native long get_texture(long self);
	private static native void set_texture_name(long self, String name, int rows, int columns);
	private static native void set_texture_name_1(long self, long name, int rows, int columns);
	private static native String get_texture_name(long self);
	private static native void set_texture_grid(long self, int rows, int columns);
	private static native int get_texture_rows(long self);
	private static native int get_texture_columns(long self);
	private static native void clear_items(long self);
	private static native int add_item(long self, String text, int parent, boolean expanded);
	private static native int add_item_1(long self, long text, int parent, boolean expanded);
	private static native void remove_item(long self, int item, boolean children);
	private static native void view_item(long self, int item);
	private static native int get_num_items(long self);
	private static native int get_item(long self, int index);
	private static native boolean switch_item_hidden(long self, int item, boolean children);
	private static native void set_item_hidden(long self, int item, boolean hidden, boolean children);
	private static native boolean is_item_hidden(long self, int item);
	private static native boolean switch_item_expanded(long self, int item, boolean children);
	private static native void set_item_expanded(long self, int item, boolean expanded, boolean children);
	private static native boolean is_item_expanded(long self, int item);
	private static native boolean switch_item_selected(long self, int item, boolean children);
	private static native void set_item_selected(long self, int item, boolean selected, boolean children);
	private static native boolean is_item_selected(long self, int item);
	private static native void set_item_parent(long self, int item, int parent);
	private static native int get_item_parent(long self, int item);
	private static native boolean is_item_parent(long self, int item, int parent, boolean hierarchy);
	private static native void add_item_child(long self, int item, int child);
	private static native void remove_item_child(long self, int item, int child);
	private static native void add_item_children(long self, int item, int[] children);
	private static native void remove_item_children(long self, int item, int[] children);
	private static native int find_item_child(long self, int item, int child);
	private static native boolean is_item_child(long self, int item, int child);
	private static native int get_num_item_children(long self, int item);
	private static native int get_item_child(long self, int item, int index);
	private static native void set_item_text(long self, int item, String text);
	private static native void set_item_text_1(long self, int item, long text);
	private static native String get_item_text(long self, int item);
	private static native int find_item_text(long self, String text);
	private static native int find_item_text_1(long self, long text);
	private static native void set_item_color(long self, int item, long color);
	private static native long get_item_color(long self, int item);
	private static native void set_item_texture(long self, int item, int row, int column);
	private static native int get_item_texture_row(long self, int item);
	private static native int get_item_texture_column(long self, int item);
	private static native void set_item_data(long self, int item, long data);
	private static native long get_item_data(long self, int item);
	private static native int get_focused_item(long self);
	private static native void set_current_item(long self, int item, boolean select, boolean view, boolean callback);
	private static native int get_current_item(long self);
	private static native String get_current_text(long self);
	private static native void set_selection(long self);
	private static native void clear_selection(long self);
	private static native void inverse_selection(long self);
	private static native int get_num_selected_items(long self);
	private static native int get_selected_item(long self, int index);
	private static native void set_changed_callback(long self, ChangedCallback func);
	private static native void set_dragged_callback(long self, DraggedCallback func);
	private static native void set_dropped_callback(long self, DroppedCallback func);
	private static native void set_clicked_callback(long self, ClickedCallback func);
	private static native void set_clicked2_callback(long self, ClickedCallback func);
	private static native void set_clicked_right_callback(long self, ClickedCallback func);
	private static native void set_expanded_callback(long self, ExpandedCallback func);
	private static native void set_selected_callback(long self, SelectedCallback func);
	
	protected ControlTree(long self) {
		init_(self);
	}
	public static ControlTree Null() {
		return new ControlTree((long)0);
	}
}

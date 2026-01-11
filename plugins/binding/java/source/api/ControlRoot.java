// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class ControlRoot extends Control {
	
	public static abstract class CopyCallback {
		public abstract void run(ControlRoot a0, String text);
		public void run_(long a0, String text) { run(new ControlRoot(a0), text); }
	}
	
	public static abstract class PasteCallback {
		public abstract String run(ControlRoot a0);
		public String run_(long a0) { return run(new ControlRoot(a0)); }
	}
	
	public ControlRoot() { init_(new_()); }
	public ControlRoot(Canvas canvas) { init_(new_1(canvas.self, false)); }
	public ControlRoot(Canvas canvas, boolean blob) { init_(new_1(canvas.self, blob)); }
	public ControlRoot[] ref() { return new ControlRoot[] { this }; }
	public ControlRoot(Control base) { init_(cast_control_ptr(base.self)); }
	public Control toControl() { return new Control(base_control_ptr(self)); }
	public void setViewport(Viewport viewport) { set_viewport(self, viewport.self); }
	public void setViewport(int width, int height) { set_viewport_1(self, width, height); }
	public void setViewport(float width, float height) { set_viewport_2(self, width, height); }
	public Viewport getViewport() { return new Viewport(get_viewport(self)); }
	public String getFontName() { return get_font_name(self); }
	public void setFontName(String name) { set_font_name(self, name); }
	public void setFontName(TSString name) { set_font_name_1(self, name.self); }
	public boolean setFontSize(int size) { return set_font_size(self, size, false); }
	public boolean setFontSize(int size, boolean update) { return set_font_size(self, size, update); }
	public int getFontSize() { return get_font_size(self); }
	public boolean setFontScale(int scale) { return set_font_scale(self, scale, false); }
	public boolean setFontScale(int scale, boolean update) { return set_font_scale(self, scale, update); }
	public int getFontScale() { return get_font_scale(self); }
	public boolean setFontStyle(FontStyle style) { return set_font_style(self, style.self, false); }
	public boolean setFontStyle(FontStyle style, boolean update) { return set_font_style(self, style.self, update); }
	public FontStyle getFontStyle() { return new FontStyle(get_font_style(self)); }
	public String getTextureName() { return get_texture_name(self); }
	public boolean setTextureName(String name) { return set_texture_name(self, name, 0, 0, 0.0f); }
	public boolean setTextureName(String name, int width) { return set_texture_name(self, name, width, 0, 0.0f); }
	public boolean setTextureName(String name, int width, int height) { return set_texture_name(self, name, width, height, 0.0f); }
	public boolean setTextureName(String name, int width, int height, float border) { return set_texture_name(self, name, width, height, border); }
	public boolean setTextureName(TSString name) { return set_texture_name_1(self, name.self, 0, 0, 0.0f); }
	public boolean setTextureName(TSString name, int width) { return set_texture_name_1(self, name.self, width, 0, 0.0f); }
	public boolean setTextureName(TSString name, int width, int height) { return set_texture_name_1(self, name.self, width, height, 0.0f); }
	public boolean setTextureName(TSString name, int width, int height, float border) { return set_texture_name_1(self, name.self, width, height, border); }
	public float getTextureWidth() { return get_texture_width(self); }
	public float getTextureHeight() { return get_texture_height(self); }
	public void setTextColor(Type type, State state, Color color) { set_text_color(self, type.value, state.value, color.self); }
	public void setTextColor(Type.Enum type, State state, Color color) { set_text_color(self, type.value, state.value, color.self); }
	public void setTextColor(Type.Enum type, State.Enum state, Color color) { set_text_color(self, type.value, state.value, color.self); }
	public void setTextColor(Type type, State.Enum state, Color color) { set_text_color(self, type.value, state.value, color.self); }
	public void setTextOffset(Type type, State state, Vector3f offset) { set_text_offset(self, type.value, state.value, offset.self); }
	public void setTextOffset(Type.Enum type, State state, Vector3f offset) { set_text_offset(self, type.value, state.value, offset.self); }
	public void setTextOffset(Type.Enum type, State.Enum state, Vector3f offset) { set_text_offset(self, type.value, state.value, offset.self); }
	public void setTextOffset(Type type, State.Enum state, Vector3f offset) { set_text_offset(self, type.value, state.value, offset.self); }
	public Color getTextColor(Type type, State state) { return new Color(get_text_color(self, type.value, state.value)); }
	public Color getTextColor(Type.Enum type, State state) { return new Color(get_text_color(self, type.value, state.value)); }
	public Color getTextColor(Type.Enum type, State.Enum state) { return new Color(get_text_color(self, type.value, state.value)); }
	public Color getTextColor(Type type, State.Enum state) { return new Color(get_text_color(self, type.value, state.value)); }
	public Vector3f getTextOffset(Type type, State state) { return new Vector3f(get_text_offset(self, type.value, state.value)); }
	public Vector3f getTextOffset(Type.Enum type, State state) { return new Vector3f(get_text_offset(self, type.value, state.value)); }
	public Vector3f getTextOffset(Type.Enum type, State.Enum state) { return new Vector3f(get_text_offset(self, type.value, state.value)); }
	public Vector3f getTextOffset(Type type, State.Enum state) { return new Vector3f(get_text_offset(self, type.value, state.value)); }
	public void setMeshColor(Mesh mesh, State state, Color color) { set_mesh_color(self, mesh.value, state.value, color.self); }
	public void setMeshColor(Mesh.Enum mesh, State state, Color color) { set_mesh_color(self, mesh.value, state.value, color.self); }
	public void setMeshColor(Mesh.Enum mesh, State.Enum state, Color color) { set_mesh_color(self, mesh.value, state.value, color.self); }
	public void setMeshColor(Mesh mesh, State.Enum state, Color color) { set_mesh_color(self, mesh.value, state.value, color.self); }
	public void setMeshRegion(Mesh mesh, Rect grid, Rect region, Vector2f border) { set_mesh_region(self, mesh.value, grid.self, region.self, border.self); }
	public void setMeshRegion(Mesh.Enum mesh, Rect grid, Rect region, Vector2f border) { set_mesh_region(self, mesh.value, grid.self, region.self, border.self); }
	public void setMeshRegions(Mesh mesh, Rect grid, Rect regions, Vector2f border) { set_mesh_regions(self, mesh.value, grid.self, regions.self, border.self); }
	public void setMeshRegions(Mesh.Enum mesh, Rect grid, Rect regions, Vector2f border) { set_mesh_regions(self, mesh.value, grid.self, regions.self, border.self); }
	public int getMeshColor(Mesh mesh, State state) { return get_mesh_color(self, mesh.value, state.value); }
	public int getMeshColor(Mesh.Enum mesh, State state) { return get_mesh_color(self, mesh.value, state.value); }
	public int getMeshColor(Mesh.Enum mesh, State.Enum state) { return get_mesh_color(self, mesh.value, state.value); }
	public int getMeshColor(Mesh mesh, State.Enum state) { return get_mesh_color(self, mesh.value, state.value); }
	public Rect getMeshGrid(Mesh mesh) { return new Rect(get_mesh_grid(self, mesh.value)); }
	public Rect getMeshGrid(Mesh.Enum mesh) { return new Rect(get_mesh_grid(self, mesh.value)); }
	public Rect getMeshMargin(Mesh mesh) { return new Rect(get_mesh_margin(self, mesh.value)); }
	public Rect getMeshMargin(Mesh.Enum mesh) { return new Rect(get_mesh_margin(self, mesh.value)); }
	public Rect getMeshRegion(Mesh mesh, State state) { return new Rect(get_mesh_region(self, mesh.value, state.value)); }
	public Rect getMeshRegion(Mesh.Enum mesh, State state) { return new Rect(get_mesh_region(self, mesh.value, state.value)); }
	public Rect getMeshRegion(Mesh.Enum mesh, State.Enum state) { return new Rect(get_mesh_region(self, mesh.value, state.value)); }
	public Rect getMeshRegion(Mesh mesh, State.Enum state) { return new Rect(get_mesh_region(self, mesh.value, state.value)); }
	public void setGroupRadius(float radius) { set_group_radius(self, radius); }
	public void setGroupColor(Color color) { set_group_color(self, color.self); }
	public float getGroupRadius() { return get_group_radius(self); }
	public Color getGroupColor() { return new Color(get_group_color(self)); }
	public void setPanelRadius(float radius) { set_panel_radius(self, radius); }
	public void setPanelColor(Color color) { set_panel_color(self, color.self); }
	public float getPanelRadius() { return get_panel_radius(self); }
	public Color getPanelColor() { return new Color(get_panel_color(self)); }
	public void setCheckedColor(Color color) { set_checked_color(self, color.self); }
	public Color getCheckedColor() { return new Color(get_checked_color(self)); }
	public void setSplitSize(float size) { set_split_size(self, size); }
	public float getSplitSize() { return get_split_size(self); }
	public void setMousePosition(Vector2f position) { set_mouse_position(self, position.self); }
	public void setMouse(int x, int y, Button buttons) { set_mouse(self, x, y, buttons.value); }
	public void setMouse(int x, int y, Button.Enum buttons) { set_mouse(self, x, y, buttons.value); }
	public void setMouse(float x, float y, Button buttons) { set_mouse_1(self, x, y, buttons.value); }
	public void setMouse(float x, float y, Button.Enum buttons) { set_mouse_1(self, x, y, buttons.value); }
	public Vector2f getMouse() { return new Vector2f(get_mouse(self)); }
	public Button getMouseButtons() { return new Button(get_mouse_buttons(self)); }
	public float getMouseX() { return get_mouse_x(self); }
	public float getMouseY() { return get_mouse_y(self); }
	public void setMouseOffset(Vector2f offset) { set_mouse_offset(self, offset.self); }
	public Vector2f getMouseOffset() { return new Vector2f(get_mouse_offset(self)); }
	public void setMouseAxis(Axis axis, float delta) { set_mouse_axis(self, axis.value, delta); }
	public void setMouseAxis(Axis.Enum axis, float delta) { set_mouse_axis(self, axis.value, delta); }
	public void setMouseAlign(Align align) { set_mouse_align(self, align.value, true); }
	public void setMouseAlign(Align.Enum align) { set_mouse_align(self, align.value, true); }
	public void setMouseAlign(Align align, boolean clear) { set_mouse_align(self, align.value, clear); }
	public void setMouseAlign(Align.Enum align, boolean clear) { set_mouse_align(self, align.value, clear); }
	public Align getMouseAlign() { return new Align(get_mouse_align(self)); }
	public boolean hasMouseAlign(Align align) { return has_mouse_align(self, align.value); }
	public boolean hasMouseAlign(Align.Enum align) { return has_mouse_align(self, align.value); }
	public boolean hasMouseAligns(Align aligns) { return has_mouse_aligns(self, aligns.value); }
	public boolean hasMouseAligns(Align.Enum aligns) { return has_mouse_aligns(self, aligns.value); }
	public boolean setKeyboardKey(int key, int code, boolean value) { return set_keyboard_key(self, key, code, value); }
	public boolean getKeyboardKey(int key) { return get_keyboard_key(self, key, false); }
	public boolean getKeyboardKey(int key, boolean clear) { return get_keyboard_key(self, key, clear); }
	public void clearCurrentControl() { clear_current_control(self); }
	public void setCurrentControl(Control control) { set_current_control(self, control.self, false); }
	public void setCurrentControl(Control control, boolean grab) { set_current_control(self, control.self, grab); }
	public Control getCurrentControl() { return new Control(get_current_control(self)); }
	public boolean isCurrentControl() { return is_current_control(self); }
	public boolean getControlGrab() { return get_control_grab(self); }
	public void clearFocusedControl() { clear_focused_control(self); }
	public void setFocusedControl(Control control) { set_focused_control(self, control.self); }
	public Control getFocusedControl() { return new Control(get_focused_control(self)); }
	public boolean isFocusedControl() { return is_focused_control(self); }
	public void clearMouseControl() { clear_mouse_control(self); }
	public void setMouseControl(Control control) { set_mouse_control(self, control.self); }
	public Control getMouseControl() { return new Control(get_mouse_control(self)); }
	public boolean isMouseControl() { return is_mouse_control(self); }
	public void clearInputControl() { clear_input_control(self); }
	public void setInputControl(Control control) { set_input_control(self, control.self); }
	public Control getInputControl() { return new Control(get_input_control(self)); }
	public boolean isInputControl() { return is_input_control(self); }
	public void clearModalControl() { clear_modal_control(self); }
	public void setModalControl(Control control) { set_modal_control(self, control.self, true); }
	public void setModalControl(Control control, boolean disabled) { set_modal_control(self, control.self, disabled); }
	public Control getModalControl() { return new Control(get_modal_control(self)); }
	public boolean isModalDisabled() { return is_modal_disabled(self); }
	public boolean isModalControl() { return is_modal_control(self); }
	public void setOverlayOrder(int order) { set_overlay_order(self, order); }
	public int getOverlayOrder() { return get_overlay_order(self); }
	public boolean update() { return update_(self, 0, 0); }
	public boolean update(int scale) { return update_(self, scale, 0); }
	public boolean update(int scale, int order) { return update_(self, scale, order); }
	public void setCopyText(String text) { set_copy_text(self, text); }
	public void setCopyText(TSString text) { set_copy_text_1(self, text.self); }
	public String getPasteText() { return get_paste_text(self); }
	public void setCopyCallback(CopyCallback func) { set_copy_callback(self, func); }
	public void setPasteCallback(PasteCallback func) { set_paste_callback(self, func); }
	
	private static native long new_();
	private static native long new_1(long canvas, boolean blob);
	private static native void delete_(long self);
	private static native boolean equal_control_ptr(long self, long base);
	private static native long cast_control_ptr(long self);
	private static native long base_control_ptr(long self);
	private static native void set_viewport(long self, long viewport);
	private static native void set_viewport_1(long self, int width, int height);
	private static native void set_viewport_2(long self, float width, float height);
	private static native long get_viewport(long self);
	private static native String get_font_name(long self);
	private static native void set_font_name(long self, String name);
	private static native void set_font_name_1(long self, long name);
	private static native boolean set_font_size(long self, int size, boolean update);
	private static native int get_font_size(long self);
	private static native boolean set_font_scale(long self, int scale, boolean update);
	private static native int get_font_scale(long self);
	private static native boolean set_font_style(long self, long style, boolean update);
	private static native long get_font_style(long self);
	private static native long get_font_style_1(long self);
	private static native String get_texture_name(long self);
	private static native boolean set_texture_name(long self, String name, int width, int height, float border);
	private static native boolean set_texture_name_1(long self, long name, int width, int height, float border);
	private static native float get_texture_width(long self);
	private static native float get_texture_height(long self);
	private static native void set_text_color(long self, int type, int state, long color);
	private static native void set_text_offset(long self, int type, int state, long offset);
	private static native long get_text_color(long self, int type, int state);
	private static native long get_text_offset(long self, int type, int state);
	private static native void set_mesh_color(long self, int mesh, int state, long color);
	private static native void set_mesh_region(long self, int mesh, long grid, long region, long border);
	private static native void set_mesh_regions(long self, int mesh, long grid, long regions, long border);
	private static native int get_mesh_color(long self, int mesh, int state);
	private static native long get_mesh_grid(long self, int mesh);
	private static native long get_mesh_margin(long self, int mesh);
	private static native long get_mesh_region(long self, int mesh, int state);
	private static native void set_group_radius(long self, float radius);
	private static native void set_group_color(long self, long color);
	private static native float get_group_radius(long self);
	private static native long get_group_color(long self);
	private static native void set_panel_radius(long self, float radius);
	private static native void set_panel_color(long self, long color);
	private static native float get_panel_radius(long self);
	private static native long get_panel_color(long self);
	private static native void set_checked_color(long self, long color);
	private static native long get_checked_color(long self);
	private static native void set_split_size(long self, float size);
	private static native float get_split_size(long self);
	private static native void set_mouse_position(long self, long position);
	private static native void set_mouse(long self, int x, int y, int buttons);
	private static native void set_mouse_1(long self, float x, float y, int buttons);
	private static native long get_mouse(long self);
	private static native int get_mouse_buttons(long self);
	private static native float get_mouse_x(long self);
	private static native float get_mouse_y(long self);
	private static native void set_mouse_offset(long self, long offset);
	private static native long get_mouse_offset(long self);
	private static native void set_mouse_axis(long self, int axis, float delta);
	private static native void set_mouse_align(long self, int align, boolean clear);
	private static native int get_mouse_align(long self);
	private static native boolean has_mouse_align(long self, int align);
	private static native boolean has_mouse_aligns(long self, int aligns);
	private static native boolean set_keyboard_key(long self, int key, int code, boolean value);
	private static native boolean get_keyboard_key(long self, int key, boolean clear);
	private static native void clear_current_control(long self);
	private static native void set_current_control(long self, long control, boolean grab);
	private static native long get_current_control(long self);
	private static native boolean is_current_control(long self);
	private static native boolean get_control_grab(long self);
	private static native void clear_focused_control(long self);
	private static native void set_focused_control(long self, long control);
	private static native long get_focused_control(long self);
	private static native boolean is_focused_control(long self);
	private static native void clear_mouse_control(long self);
	private static native void set_mouse_control(long self, long control);
	private static native long get_mouse_control(long self);
	private static native boolean is_mouse_control(long self);
	private static native void clear_input_control(long self);
	private static native void set_input_control(long self, long control);
	private static native long get_input_control(long self);
	private static native boolean is_input_control(long self);
	private static native void clear_modal_control(long self);
	private static native void set_modal_control(long self, long control, boolean disabled);
	private static native long get_modal_control(long self);
	private static native boolean is_modal_disabled(long self);
	private static native boolean is_modal_control(long self);
	private static native void set_overlay_order(long self, int order);
	private static native int get_overlay_order(long self);
	private static native boolean update_(long self, int scale, int order);
	private static native void set_copy_text(long self, String text);
	private static native void set_copy_text_1(long self, long text);
	private static native String get_paste_text(long self);
	private static native void set_copy_callback(long self, CopyCallback func);
	private static native void set_paste_callback(long self, PasteCallback func);
	
	protected ControlRoot(long self) {
		init_(self);
	}
	public static ControlRoot Null() {
		return new ControlRoot((long)0);
	}
}

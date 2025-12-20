// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Control {
	
	public static class Type {
		public enum Enum {
			Unknown(0),
			Root(1),
			Text(2),
			Rect(3),
			Grid(4),
			Group(5),
			Panel(6),
			Dialog(7),
			Window(8),
			Check(9),
			Combo(10),
			Button(11),
			Slider(12),
			Scroll(13),
			Split(14),
			Area(15),
			Tree(16),
			Edit(17),
			NumTypes(18);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Unknown = Enum.Unknown;
		public static final Enum Root = Enum.Root;
		public static final Enum Text = Enum.Text;
		public static final Enum Rect = Enum.Rect;
		public static final Enum Grid = Enum.Grid;
		public static final Enum Group = Enum.Group;
		public static final Enum Panel = Enum.Panel;
		public static final Enum Dialog = Enum.Dialog;
		public static final Enum Window = Enum.Window;
		public static final Enum Check = Enum.Check;
		public static final Enum Combo = Enum.Combo;
		public static final Enum Button = Enum.Button;
		public static final Enum Slider = Enum.Slider;
		public static final Enum Scroll = Enum.Scroll;
		public static final Enum Split = Enum.Split;
		public static final Enum Area = Enum.Area;
		public static final Enum Tree = Enum.Tree;
		public static final Enum Edit = Enum.Edit;
		public static final Enum NumTypes = Enum.NumTypes;
		public Type(int value) { this.value = value; }
		public Type(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class State {
		public enum Enum {
			Unknown(0),
			Normal(1),
			Focused(2),
			Pressed(3),
			Disabled(4),
			NumStates(5);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Unknown = Enum.Unknown;
		public static final Enum Normal = Enum.Normal;
		public static final Enum Focused = Enum.Focused;
		public static final Enum Pressed = Enum.Pressed;
		public static final Enum Disabled = Enum.Disabled;
		public static final Enum NumStates = Enum.NumStates;
		public State(int value) { this.value = value; }
		public State(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class Mesh {
		public enum Enum {
			Check(0),
			Button(1),
			SliderLine(2),
			HScrollLine(3),
			VScrollLine(4),
			SliderHandle(5),
			HScrollHandle(6),
			VScrollHandle(7),
			Background(8),
			Selection(9),
			Border(10),
			Frame(11),
			NumMeshes(12);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Check = Enum.Check;
		public static final Enum Button = Enum.Button;
		public static final Enum SliderLine = Enum.SliderLine;
		public static final Enum HScrollLine = Enum.HScrollLine;
		public static final Enum VScrollLine = Enum.VScrollLine;
		public static final Enum SliderHandle = Enum.SliderHandle;
		public static final Enum HScrollHandle = Enum.HScrollHandle;
		public static final Enum VScrollHandle = Enum.VScrollHandle;
		public static final Enum Background = Enum.Background;
		public static final Enum Selection = Enum.Selection;
		public static final Enum Border = Enum.Border;
		public static final Enum Frame = Enum.Frame;
		public static final Enum NumMeshes = Enum.NumMeshes;
		public Mesh(int value) { this.value = value; }
		public Mesh(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class Align {
		public enum Enum {
			None(0),
			Left(1),
			Right(2),
			Bottom(4),
			Top(8),
			CenterX(16),
			CenterY(32),
			ExpandX(64),
			ExpandY(128),
			Overlap(256),
			Spacer(512),
			Aspect(1024),
			Local(2048),
			LeftBottom(5),
			LeftTop(9),
			RightBottom(6),
			RightTop(10),
			Center(48),
			Expand(192),
			NumAligns(12);
			Enum(int value) { this.value = value; }
			public Align and(Align e) { return new Align(value & e.value); }
			public Align and(Enum e) { return new Align(value & e.value); }
			public Align or(Align e) { return new Align(value | e.value); }
			public Align or(Enum e) { return new Align(value | e.value); }
			public boolean has(Align e) { return ((value & e.value) != 0); }
			public boolean has(Enum e) { return ((value & e.value) != 0); }
			public int value;
		}
		public static final Enum None = Enum.None;
		public static final Enum Left = Enum.Left;
		public static final Enum Right = Enum.Right;
		public static final Enum Bottom = Enum.Bottom;
		public static final Enum Top = Enum.Top;
		public static final Enum CenterX = Enum.CenterX;
		public static final Enum CenterY = Enum.CenterY;
		public static final Enum ExpandX = Enum.ExpandX;
		public static final Enum ExpandY = Enum.ExpandY;
		public static final Enum Overlap = Enum.Overlap;
		public static final Enum Spacer = Enum.Spacer;
		public static final Enum Aspect = Enum.Aspect;
		public static final Enum Local = Enum.Local;
		public static final Enum LeftBottom = Enum.LeftBottom;
		public static final Enum LeftTop = Enum.LeftTop;
		public static final Enum RightBottom = Enum.RightBottom;
		public static final Enum RightTop = Enum.RightTop;
		public static final Enum Center = Enum.Center;
		public static final Enum Expand = Enum.Expand;
		public static final Enum NumAligns = Enum.NumAligns;
		public Align(int value) { this.value = value; }
		public Align(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public Align(Enum e0, Enum e1) { this(e0.value | e1.value); }
		public Align(Enum e0, Enum e1, Enum e2) { this(e0.value | e1.value | e2.value); }
		public Align(Enum e0, Enum e1, Enum e2, Enum e3) { this(e0.value | e1.value | e2.value | e3.value); }
		public Align not() { return new Align(~value); }
		public Align and(Align e) { return new Align(value & e.value); }
		public Align and(Enum e) { return new Align(value & e.value); }
		public Align or(Align e) { return new Align(value | e.value); }
		public Align or(Enum e) { return new Align(value | e.value); }
		public boolean has(Align e) { return ((value & e.value) != 0); }
		public boolean has(Enum e) { return ((value & e.value) != 0); }
		public int value;
	}
	
	public static class Button {
		public enum Enum {
			None(0),
			Left(1),
			Left2(2),
			Right(4),
			Right2(8),
			Middle(16),
			Middle2(32),
			NumButtons(6);
			Enum(int value) { this.value = value; }
			public Button and(Button e) { return new Button(value & e.value); }
			public Button and(Enum e) { return new Button(value & e.value); }
			public Button or(Button e) { return new Button(value | e.value); }
			public Button or(Enum e) { return new Button(value | e.value); }
			public boolean has(Button e) { return ((value & e.value) != 0); }
			public boolean has(Enum e) { return ((value & e.value) != 0); }
			public int value;
		}
		public static final Enum None = Enum.None;
		public static final Enum Left = Enum.Left;
		public static final Enum Left2 = Enum.Left2;
		public static final Enum Right = Enum.Right;
		public static final Enum Right2 = Enum.Right2;
		public static final Enum Middle = Enum.Middle;
		public static final Enum Middle2 = Enum.Middle2;
		public static final Enum NumButtons = Enum.NumButtons;
		public Button(int value) { this.value = value; }
		public Button(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public Button(Enum e0, Enum e1) { this(e0.value | e1.value); }
		public Button(Enum e0, Enum e1, Enum e2) { this(e0.value | e1.value | e2.value); }
		public Button(Enum e0, Enum e1, Enum e2, Enum e3) { this(e0.value | e1.value | e2.value | e3.value); }
		public Button not() { return new Button(~value); }
		public Button and(Button e) { return new Button(value & e.value); }
		public Button and(Enum e) { return new Button(value & e.value); }
		public Button or(Button e) { return new Button(value | e.value); }
		public Button or(Enum e) { return new Button(value | e.value); }
		public boolean has(Button e) { return ((value & e.value) != 0); }
		public boolean has(Enum e) { return ((value & e.value) != 0); }
		public int value;
	}
	
	public static class Axis {
		public enum Enum {
			Unknown(0),
			X(1),
			Y(2),
			Z(3),
			W(4),
			NumAxes(5);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Unknown = Enum.Unknown;
		public static final Enum X = Enum.X;
		public static final Enum Y = Enum.Y;
		public static final Enum Z = Enum.Z;
		public static final Enum W = Enum.W;
		public static final Enum NumAxes = Enum.NumAxes;
		public Axis(int value) { this.value = value; }
		public Axis(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class Key {
		public enum Enum {
			None(128),
			Tab(129),
			Backspace(130),
			Delete(131),
			Insert(132),
			Return(133),
			Prior(134),
			Next(135),
			End(136),
			Home(137),
			Up(138),
			Down(139),
			Left(140),
			Right(141),
			Shift(142),
			Ctrl(143),
			Alt(144),
			Cmd(145),
			NumKeys(146);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum None = Enum.None;
		public static final Enum Tab = Enum.Tab;
		public static final Enum Backspace = Enum.Backspace;
		public static final Enum Delete = Enum.Delete;
		public static final Enum Insert = Enum.Insert;
		public static final Enum Return = Enum.Return;
		public static final Enum Prior = Enum.Prior;
		public static final Enum Next = Enum.Next;
		public static final Enum End = Enum.End;
		public static final Enum Home = Enum.Home;
		public static final Enum Up = Enum.Up;
		public static final Enum Down = Enum.Down;
		public static final Enum Left = Enum.Left;
		public static final Enum Right = Enum.Right;
		public static final Enum Shift = Enum.Shift;
		public static final Enum Ctrl = Enum.Ctrl;
		public static final Enum Alt = Enum.Alt;
		public static final Enum Cmd = Enum.Cmd;
		public static final Enum NumKeys = Enum.NumKeys;
		public Key(int value) { this.value = value; }
		public Key(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public Control() { init_(new_()); }
	public Control(Control[] parent) { init_(new_1(Control.self_(parent))); }
	public Control(Control[] parent, float width) { init_(new_2(Control.self_(parent), width, 0.0f)); }
	public Control(Control[] parent, float width, float height) { init_(new_2(Control.self_(parent), width, height)); }
	public Control[] ref() { return new Control[] { this }; }
	public boolean equalPtr(Control ptr) { return equal_ptr(self, ptr.self); }
	public Control clonePtr() { return new Control(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public static int getNumControls() { return get_num_controls(); }
	public static boolean isControl(Control control) { return is_control(control.self); }
	public Type getType() { return new Type(get_type(self)); }
	public static String getTypeName(Type type) { return get_type_name(type.value); }
	public static String getTypeName(Type.Enum type) { return get_type_name(type.value); }
	public String getTypeName() { return get_type_name_1(self); }
	public boolean isUnknown() { return is_unknown(self); }
	public boolean isRoot() { return is_root(self); }
	public boolean isText() { return is_text(self); }
	public boolean isRect() { return is_rect(self); }
	public boolean isGrid() { return is_grid(self); }
	public boolean isGroup() { return is_group(self); }
	public boolean isPanel() { return is_panel(self); }
	public boolean isDialog() { return is_dialog(self); }
	public boolean isWindow() { return is_window(self); }
	public boolean isCheck() { return is_check(self); }
	public boolean isCombo() { return is_combo(self); }
	public boolean isButton() { return is_button(self); }
	public boolean isSlider() { return is_slider(self); }
	public boolean isScroll() { return is_scroll(self); }
	public boolean isSplit() { return is_split(self); }
	public boolean isArea() { return is_area(self); }
	public boolean isTree() { return is_tree(self); }
	public boolean isEdit() { return is_edit(self); }
	public void setAlign(Align align) { set_align(self, align.value); }
	public void setAlign(Align.Enum align) { set_align(self, align.value); }
	public Align getAlign() { return new Align(get_align(self)); }
	public boolean hasAlign(Align align) { return has_align(self, align.value); }
	public boolean hasAlign(Align.Enum align) { return has_align(self, align.value); }
	public boolean hasAligns(Align aligns) { return has_aligns(self, aligns.value); }
	public boolean hasAligns(Align.Enum aligns) { return has_aligns(self, aligns.value); }
	public boolean isSpacer() { return is_spacer(self); }
	public void setCreated(boolean created) { set_created(self, created); }
	public boolean isCreated() { return is_created(self); }
	public void setEnabled(boolean enabled) { set_enabled(self, enabled); }
	public boolean isEnabled() { return is_enabled(self); }
	public boolean wasEnabled() { return was_enabled(self); }
	public boolean wasUpdated() { return was_updated(self); }
	public void setDisabled(boolean disabled) { set_disabled(self, disabled); }
	public boolean isDisabled() { return is_disabled(self); }
	public Canvas getCanvas() { return new Canvas(get_canvas(self)); }
	public ControlRoot getRoot() { return new ControlRoot(get_root(self, false)); }
	public ControlRoot getRoot(boolean local) { return new ControlRoot(get_root(self, local)); }
	public ControlPanel getPanel() { return new ControlPanel(get_panel(self)); }
	public int setParent(Control parent) { return set_parent(self, parent.self); }
	public Control getParent() { return new Control(get_parent(self)); }
	public boolean isParentEnabled() { return is_parent_enabled(self); }
	public boolean isParentDisabled() { return is_parent_disabled(self); }
	public int addChild(Control child) { return add_child(self, child.self); }
	public Control setChild(int index, Control child) { return new Control(set_child(self, index, child.self)); }
	public boolean raiseChild(Control child) { return raise_child(self, child.self, 0); }
	public boolean raiseChild(Control child, int index) { return raise_child(self, child.self, index); }
	public boolean lowerChild(Control child) { return lower_child(self, child.self, 0); }
	public boolean lowerChild(Control child, int index) { return lower_child(self, child.self, index); }
	public boolean removeChild(Control child) { return remove_child(self, child.self); }
	public void releaseChildren() { release_children(self); }
	public int findChild(Control child) { return find_child(self, child.self); }
	public boolean isChild(Control child) { return is_child(self, child.self, false); }
	public boolean isChild(Control child, boolean hierarchy) { return is_child(self, child.self, hierarchy); }
	public int getNumChildren() { return get_num_children(self); }
	public Control getChild(int index) { return new Control(get_child(self, index)); }
	public void setSize(Vector2f size) { set_size(self, size.self); }
	public void setSize(float width, float height) { set_size_1(self, width, height); }
	public Vector2f getSize() { return new Vector2f(get_size(self)); }
	public float getWidth() { return get_width(self); }
	public float getHeight() { return get_height(self); }
	public void setPosition(Vector3f position) { set_position(self, position.self); }
	public void setPosition(float x, float y) { set_position_1(self, x, y, 0.0f); }
	public void setPosition(float x, float y, float z) { set_position_1(self, x, y, z); }
	public Vector3f getPosition() { return new Vector3f(get_position(self)); }
	public float getPositionX() { return get_position_x(self); }
	public float getPositionY() { return get_position_y(self); }
	public void setOffset(Vector3f offset) { set_offset(self, offset.self); }
	public void setOffset(float x, float y) { set_offset_1(self, x, y, 0.0f); }
	public void setOffset(float x, float y, float z) { set_offset_1(self, x, y, z); }
	public Vector3f getOffset() { return new Vector3f(get_offset(self)); }
	public float getOffsetX() { return get_offset_x(self); }
	public float getOffsetY() { return get_offset_y(self); }
	public void setMargin(float value) { set_margin(self, value); }
	public void setMargin(float horizontal, float vertical) { set_margin_1(self, horizontal, vertical); }
	public void setMargin(float left, float right, float bottom, float top) { set_margin_2(self, left, right, bottom, top); }
	public void setMargin(Rect margin) { set_margin_3(self, margin.self); }
	public Rect getMargin() { return new Rect(get_margin(self)); }
	public Rect getRect() { return new Rect(get_rect(self)); }
	public State getState() { return new State(get_state(self)); }
	
	private static native long new_();
	private static native long new_1(long[] parent);
	private static native long new_2(long[] parent, float width, float height);
	private static native void delete_(long self);
	private static native boolean equal_ptr(long self, long ptr);
	private static native long clone_ptr(long self);
	private static native void clear_ptr(long self);
	private static native void destroy_ptr(long self);
	private static native void acquire_ptr(long self);
	private static native void unacquire_ptr(long self);
	private static native boolean is_valid_ptr(long self);
	private static native boolean is_owner_ptr(long self);
	private static native boolean is_const_ptr(long self);
	private static native int get_count_ptr(long self);
	private static native long get_internal_ptr(long self);
	private static native int get_num_controls();
	private static native boolean is_control(long control);
	private static native int get_type(long self);
	private static native String get_type_name(int type);
	private static native String get_type_name_1(long self);
	private static native boolean is_unknown(long self);
	private static native boolean is_root(long self);
	private static native boolean is_text(long self);
	private static native boolean is_rect(long self);
	private static native boolean is_grid(long self);
	private static native boolean is_group(long self);
	private static native boolean is_panel(long self);
	private static native boolean is_dialog(long self);
	private static native boolean is_window(long self);
	private static native boolean is_check(long self);
	private static native boolean is_combo(long self);
	private static native boolean is_button(long self);
	private static native boolean is_slider(long self);
	private static native boolean is_scroll(long self);
	private static native boolean is_split(long self);
	private static native boolean is_area(long self);
	private static native boolean is_tree(long self);
	private static native boolean is_edit(long self);
	private static native void set_align(long self, int align);
	private static native int get_align(long self);
	private static native boolean has_align(long self, int align);
	private static native boolean has_aligns(long self, int aligns);
	private static native boolean is_spacer(long self);
	private static native void set_created(long self, boolean created);
	private static native boolean is_created(long self);
	private static native void set_enabled(long self, boolean enabled);
	private static native boolean is_enabled(long self);
	private static native boolean was_enabled(long self);
	private static native boolean was_updated(long self);
	private static native void set_disabled(long self, boolean disabled);
	private static native boolean is_disabled(long self);
	private static native long get_canvas(long self);
	private static native long get_root(long self, boolean local);
	private static native long get_root_1(long self, boolean local);
	private static native long get_panel(long self);
	private static native long get_panel_1(long self);
	private static native int set_parent(long self, long parent);
	private static native long get_parent(long self);
	private static native long get_parent_1(long self);
	private static native boolean is_parent_enabled(long self);
	private static native boolean is_parent_disabled(long self);
	private static native int add_child(long self, long child);
	private static native long set_child(long self, int index, long child);
	private static native boolean raise_child(long self, long child, int index);
	private static native boolean lower_child(long self, long child, int index);
	private static native boolean remove_child(long self, long child);
	private static native void release_children(long self);
	private static native int find_child(long self, long child);
	private static native boolean is_child(long self, long child, boolean hierarchy);
	private static native int get_num_children(long self);
	private static native long get_child(long self, int index);
	private static native long get_child_1(long self, int index);
	private static native void set_size(long self, long size);
	private static native void set_size_1(long self, float width, float height);
	private static native long get_size(long self);
	private static native float get_width(long self);
	private static native float get_height(long self);
	private static native void set_position(long self, long position);
	private static native void set_position_1(long self, float x, float y, float z);
	private static native long get_position(long self);
	private static native float get_position_x(long self);
	private static native float get_position_y(long self);
	private static native void set_offset(long self, long offset);
	private static native void set_offset_1(long self, float x, float y, float z);
	private static native long get_offset(long self);
	private static native float get_offset_x(long self);
	private static native float get_offset_y(long self);
	private static native void set_margin(long self, float value);
	private static native void set_margin_1(long self, float horizontal, float vertical);
	private static native void set_margin_2(long self, float left, float right, float bottom, float top);
	private static native void set_margin_3(long self, long margin);
	private static native long get_margin(long self);
	private static native long get_rect(long self);
	private static native int get_state(long self);
	
	protected Control(long self) {
		init_(self);
	}
	public static Control Null() {
		return new Control((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Control[] ptr) {
		long[] self = new long[ptr.length];
		for(int i = 0; i < ptr.length; i++) self[i] = ptr[i].self;
		return self;
	}
	private static class Destructor implements Runnable {
		Destructor(long self) { this.self = self; }
		public void run() { delete_(self); }
		private long self;
	}
	
	private static Cleaner cleaner = Cleaner.create();
	
	protected long self;
}

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class DialogMenu {
	
	public static class Flags {
		public enum Enum {
			None(0),
			Mouse(1),
			Default(0),
			Num(1);
			Enum(int value) { this.value = value; }
			public Flags and(Flags e) { return new Flags(value & e.value); }
			public Flags and(Enum e) { return new Flags(value & e.value); }
			public Flags or(Flags e) { return new Flags(value | e.value); }
			public Flags or(Enum e) { return new Flags(value | e.value); }
			public boolean has(Flags e) { return ((value & e.value) != 0); }
			public boolean has(Enum e) { return ((value & e.value) != 0); }
			public int value;
		}
		public static final Enum None = Enum.None;
		public static final Enum Mouse = Enum.Mouse;
		public static final Enum Default = Enum.Default;
		public static final Enum Num = Enum.Num;
		public Flags(int value) { this.value = value; }
		public Flags(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public Flags(Enum e0, Enum e1) { this(e0.value | e1.value); }
		public Flags(Enum e0, Enum e1, Enum e2) { this(e0.value | e1.value | e2.value); }
		public Flags(Enum e0, Enum e1, Enum e2, Enum e3) { this(e0.value | e1.value | e2.value | e3.value); }
		public Flags not() { return new Flags(~value); }
		public Flags and(Flags e) { return new Flags(value & e.value); }
		public Flags and(Enum e) { return new Flags(value & e.value); }
		public Flags or(Flags e) { return new Flags(value | e.value); }
		public Flags or(Enum e) { return new Flags(value | e.value); }
		public boolean has(Flags e) { return ((value & e.value) != 0); }
		public boolean has(Enum e) { return ((value & e.value) != 0); }
		public int value;
	}
	
	public static class Result {
		public enum Enum {
			Cancel(0),
			Click(1),
			NumResults(2);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Cancel = Enum.Cancel;
		public static final Enum Click = Enum.Click;
		public static final Enum NumResults = Enum.NumResults;
		public Result(int value) { this.value = value; }
		public Result(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static abstract class ClickedCallback {
		public abstract void run();
		public void run_() { run(); }
	}
	
	public static abstract class ChangedCallback {
		public abstract void run(boolean a0);
		public void run_(boolean a0) { run(a0); }
	}
	
	public static abstract class UpdateCallback {
		public abstract boolean run();
		public boolean run_() { return run(); }
	}
	
	public DialogMenu() { init_(new_()); }
	public DialogMenu[] ref() { return new DialogMenu[] { this }; }
	public boolean equalPtr(DialogMenu ptr) { return equal_ptr(self, ptr.self); }
	public DialogMenu clonePtr() { return new DialogMenu(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public void setPosition(int x, int y) { set_position(self, x, y); }
	public int getPositionX() { return get_position_x(self); }
	public int getPositionY() { return get_position_y(self); }
	public int getNumItems() { return get_num_items(self); }
	public void setItemText(int index, String text) { set_item_text(self, index, text); }
	public void setItemText(int index, TSString text) { set_item_text_1(self, index, text.self); }
	public String getItemText(int index) { return get_item_text(self, index); }
	public void setItemKey(int index, String key) { set_item_key(self, index, key); }
	public String getItemKey(int index) { return get_item_key(self, index); }
	public void setItemImage(int index, Image image) { set_item_image(self, index, image.self); }
	public Image getItemImage(int index) { return new Image(get_item_image(self, index)); }
	public void setItemChecked(int index, boolean checked) { set_item_checked(self, index, checked, false); }
	public void setItemChecked(int index, boolean checked, boolean callback) { set_item_checked(self, index, checked, callback); }
	public boolean isItemChecked(int index) { return is_item_checked(self, index); }
	public void setItemEnabled(int index, boolean enabled) { set_item_enabled(self, index, enabled); }
	public boolean isItemEnabled(int index) { return is_item_enabled(self, index); }
	public void setItemHidden(int index, boolean hidden) { set_item_hidden(self, index, hidden); }
	public boolean isItemHidden(int index) { return is_item_hidden(self, index); }
	public void setItemsGroup(int index, int size) { set_items_group(self, index, size); }
	public int getItemGroupIndex(int index) { return get_item_group_index(self, index); }
	public int getItemGroupSize(int index) { return get_item_group_size(self, index); }
	public int addItem(String text) { return add_item(self, text, null); }
	public int addItem(String text, String key) { return add_item(self, text, key); }
	public int addItem(TSString text) { return add_item_1(self, text.self, null); }
	public int addItem(TSString text, String key) { return add_item_1(self, text.self, key); }
	public int addItem(String text, Image image) { return add_item_2(self, text, image.self, null); }
	public int addItem(String text, Image image, String key) { return add_item_2(self, text, image.self, key); }
	public int addItem(TSString text, Image image) { return add_item_3(self, text.self, image.self, null); }
	public int addItem(TSString text, Image image, String key) { return add_item_3(self, text.self, image.self, key); }
	public int addItem(String text, ClickedCallback func) { return add_item_4(self, text, func, null); }
	public int addItem(String text, ClickedCallback func, String key) { return add_item_4(self, text, func, key); }
	public int addItem(TSString text, ClickedCallback func) { return add_item_5(self, text.self, func, null); }
	public int addItem(TSString text, ClickedCallback func, String key) { return add_item_5(self, text.self, func, key); }
	public int addItem(String text, Image image, ClickedCallback func) { return add_item_6(self, text, image.self, func, null); }
	public int addItem(String text, Image image, ClickedCallback func, String key) { return add_item_6(self, text, image.self, func, key); }
	public int addItem(TSString text, Image image, ClickedCallback func) { return add_item_7(self, text.self, image.self, func, null); }
	public int addItem(TSString text, Image image, ClickedCallback func, String key) { return add_item_7(self, text.self, image.self, func, key); }
	public int addItem(String text, boolean checked, ChangedCallback func) { return add_item_8(self, text, checked, func, null); }
	public int addItem(String text, boolean checked, ChangedCallback func, String key) { return add_item_8(self, text, checked, func, key); }
	public int addItem(TSString text, boolean checked, ChangedCallback func) { return add_item_9(self, text.self, checked, func, null); }
	public int addItem(TSString text, boolean checked, ChangedCallback func, String key) { return add_item_9(self, text.self, checked, func, key); }
	public int addItem(String text, Image image, boolean checked, ChangedCallback func) { return add_item_10(self, text, image.self, checked, func, null); }
	public int addItem(String text, Image image, boolean checked, ChangedCallback func, String key) { return add_item_10(self, text, image.self, checked, func, key); }
	public int addItem(TSString text, Image image, boolean checked, ChangedCallback func) { return add_item_11(self, text.self, image.self, checked, func, null); }
	public int addItem(TSString text, Image image, boolean checked, ChangedCallback func, String key) { return add_item_11(self, text.self, image.self, checked, func, key); }
	public void setUpdateCallback(UpdateCallback func) { set_update_callback(self, func); }
	public Result run() { return new Result(run_(self, Flags.Default.value)); }
	public Result run(Flags flags) { return new Result(run_(self, flags.value)); }
	public Result run(Flags.Enum flags) { return new Result(run_(self, flags.value)); }
	
	private static native long new_();
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
	private static native void set_position(long self, int x, int y);
	private static native int get_position_x(long self);
	private static native int get_position_y(long self);
	private static native int get_num_items(long self);
	private static native void set_item_text(long self, int index, String text);
	private static native void set_item_text_1(long self, int index, long text);
	private static native String get_item_text(long self, int index);
	private static native void set_item_key(long self, int index, String key);
	private static native String get_item_key(long self, int index);
	private static native void set_item_image(long self, int index, long image);
	private static native long get_item_image(long self, int index);
	private static native void set_item_checked(long self, int index, boolean checked, boolean callback);
	private static native boolean is_item_checked(long self, int index);
	private static native void set_item_enabled(long self, int index, boolean enabled);
	private static native boolean is_item_enabled(long self, int index);
	private static native void set_item_hidden(long self, int index, boolean hidden);
	private static native boolean is_item_hidden(long self, int index);
	private static native void set_items_group(long self, int index, int size);
	private static native int get_item_group_index(long self, int index);
	private static native int get_item_group_size(long self, int index);
	private static native int add_item(long self, String text, String key);
	private static native int add_item_1(long self, long text, String key);
	private static native int add_item_2(long self, String text, long image, String key);
	private static native int add_item_3(long self, long text, long image, String key);
	private static native int add_item_4(long self, String text, ClickedCallback func, String key);
	private static native int add_item_5(long self, long text, ClickedCallback func, String key);
	private static native int add_item_6(long self, String text, long image, ClickedCallback func, String key);
	private static native int add_item_7(long self, long text, long image, ClickedCallback func, String key);
	private static native int add_item_8(long self, String text, boolean checked, ChangedCallback func, String key);
	private static native int add_item_9(long self, long text, boolean checked, ChangedCallback func, String key);
	private static native int add_item_10(long self, String text, long image, boolean checked, ChangedCallback func, String key);
	private static native int add_item_11(long self, long text, long image, boolean checked, ChangedCallback func, String key);
	private static native void set_update_callback(long self, UpdateCallback func);
	private static native int run_(long self, int flags);
	
	protected DialogMenu(long self) {
		init_(self);
	}
	public static DialogMenu Null() {
		return new DialogMenu((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(DialogMenu[] ptr) {
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

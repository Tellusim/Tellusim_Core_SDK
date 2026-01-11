// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Controller {
	
	public static class Type {
		public enum Enum {
			Unknown(0),
			Joystick(1),
			GamePad(2),
			Wheel(3),
			NumTypes(4);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Unknown = Enum.Unknown;
		public static final Enum Joystick = Enum.Joystick;
		public static final Enum GamePad = Enum.GamePad;
		public static final Enum Wheel = Enum.Wheel;
		public static final Enum NumTypes = Enum.NumTypes;
		public Type(int value) { this.value = value; }
		public Type(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class Stick {
		public enum Enum {
			Left(0),
			Right(1),
			NumSticks(2);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Left = Enum.Left;
		public static final Enum Right = Enum.Right;
		public static final Enum NumSticks = Enum.NumSticks;
		public Stick(int value) { this.value = value; }
		public Stick(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class Axis {
		public enum Enum {
			X(0),
			Y(1),
			Z(2),
			RX(3),
			RY(4),
			RZ(5),
			NumAxes(16);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum X = Enum.X;
		public static final Enum Y = Enum.Y;
		public static final Enum Z = Enum.Z;
		public static final Enum RX = Enum.RX;
		public static final Enum RY = Enum.RY;
		public static final Enum RZ = Enum.RZ;
		public static final Enum NumAxes = Enum.NumAxes;
		public Axis(int value) { this.value = value; }
		public Axis(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class Button {
		public enum Enum {
			Left(0),
			Right(1),
			Down(2),
			Up(3),
			Home(4),
			ShoulderLeft(5),
			ShoulderRight(6),
			TriggerLeft(7),
			TriggerRight(8),
			StickLeft(9),
			StickRight(10),
			A(11),
			B(12),
			X(13),
			Y(14),
			View(15),
			Menu(16),
			L1(5),
			R1(6),
			L2(7),
			R2(8),
			L3(9),
			R3(10),
			Cross(11),
			Circle(12),
			Square(13),
			Triangle(14),
			Share(15),
			Options(16),
			NumButtons(32);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Left = Enum.Left;
		public static final Enum Right = Enum.Right;
		public static final Enum Down = Enum.Down;
		public static final Enum Up = Enum.Up;
		public static final Enum Home = Enum.Home;
		public static final Enum ShoulderLeft = Enum.ShoulderLeft;
		public static final Enum ShoulderRight = Enum.ShoulderRight;
		public static final Enum TriggerLeft = Enum.TriggerLeft;
		public static final Enum TriggerRight = Enum.TriggerRight;
		public static final Enum StickLeft = Enum.StickLeft;
		public static final Enum StickRight = Enum.StickRight;
		public static final Enum A = Enum.A;
		public static final Enum B = Enum.B;
		public static final Enum X = Enum.X;
		public static final Enum Y = Enum.Y;
		public static final Enum View = Enum.View;
		public static final Enum Menu = Enum.Menu;
		public static final Enum L1 = Enum.L1;
		public static final Enum R1 = Enum.R1;
		public static final Enum L2 = Enum.L2;
		public static final Enum R2 = Enum.R2;
		public static final Enum L3 = Enum.L3;
		public static final Enum R3 = Enum.R3;
		public static final Enum Cross = Enum.Cross;
		public static final Enum Circle = Enum.Circle;
		public static final Enum Square = Enum.Square;
		public static final Enum Triangle = Enum.Triangle;
		public static final Enum Share = Enum.Share;
		public static final Enum Options = Enum.Options;
		public static final Enum NumButtons = Enum.NumButtons;
		public Button(int value) { this.value = value; }
		public Button(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static class Motor {
		public enum Enum {
			Low(0),
			High(1),
			NumMotors(2);
			Enum(int value) { this.value = value; }
			public int value;
		}
		public static final Enum Low = Enum.Low;
		public static final Enum High = Enum.High;
		public static final Enum NumMotors = Enum.NumMotors;
		public Motor(int value) { this.value = value; }
		public Motor(Enum e) { this(e.value); }
		public boolean equals(int v) { return (value == v); }
		public boolean equals(Enum e) { return (value == e.value); }
		public int value;
	}
	
	public static abstract class ButtonPressedCallback {
		public abstract void run(Controller controller, Button button);
		public void run_(long controller, int button) { run(new Controller(controller), new Button(button)); }
	}
	
	public static abstract class ButtonReleasedCallback {
		public abstract void run(Controller controller, Button button);
		public void run_(long controller, int button) { run(new Controller(controller), new Button(button)); }
	}
	
	public static abstract class ConnectedCallback {
		public abstract void run(Controller controller);
		public void run_(long controller) { run(new Controller(controller)); }
	}
	
	public static abstract class DisconnectedCallback {
		public abstract void run(Controller controller);
		public void run_(long controller) { run(new Controller(controller)); }
	}
	
	public Controller() { init_(new_()); }
	public Controller(int index) { init_(new_1(index)); }
	public Controller(Type type) { init_(new_2(type.value, Base.Maxu32)); }
	public Controller(Type.Enum type) { init_(new_2(type.value, Base.Maxu32)); }
	public Controller(Type type, int index) { init_(new_2(type.value, index)); }
	public Controller(Type.Enum type, int index) { init_(new_2(type.value, index)); }
	public Controller[] ref() { return new Controller[] { this }; }
	public boolean equalPtr(Controller ptr) { return equal_ptr(self, ptr.self); }
	public Controller clonePtr() { return new Controller(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public static int getNumControllers() { return get_num_controllers(); }
	public static int findController(String name) { return find_controller(name); }
	public static Controller getController(int index) { return new Controller(get_controller(index)); }
	public static void update() { update_(); }
	public void setType(Type type) { set_type(self, type.value); }
	public void setType(Type.Enum type) { set_type(self, type.value); }
	public Type getType() { return new Type(get_type(self)); }
	public static String getTypeName(Type type) { return get_type_name(type.value); }
	public static String getTypeName(Type.Enum type) { return get_type_name(type.value); }
	public String getTypeName() { return get_type_name_1(self); }
	public boolean isUnknown() { return is_unknown(self); }
	public boolean isJoystick() { return is_joystick(self); }
	public boolean isGamePad() { return is_game_pad(self); }
	public boolean isWheel() { return is_wheel(self); }
	public void setIndex(int index) { set_index(self, index); }
	public int getIndex() { return get_index(self); }
	public void setName(String name) { set_name(self, name); }
	public String getName() { return get_name(self); }
	public void setModel(String model) { set_model(self, model); }
	public String getModel() { return get_model(self); }
	public boolean isConnected() { return is_connected(self); }
	public boolean wasConnected() { return was_connected(self); }
	public boolean connect() { return connect_(self, null); }
	public boolean connect(String name) { return connect_(self, name); }
	public void release() { release_(self); }
	public void setStickName(Stick stick, String name) { set_stick_name(self, stick.value, name); }
	public void setStickName(Stick.Enum stick, String name) { set_stick_name(self, stick.value, name); }
	public String getStickName(Stick stick) { return get_stick_name(self, stick.value); }
	public String getStickName(Stick.Enum stick) { return get_stick_name(self, stick.value); }
	public Stick findStick(String name) { return new Stick(find_stick(self, name)); }
	public void setStick(Stick stick, float x, float y) { set_stick(self, stick.value, x, y); }
	public void setStick(Stick.Enum stick, float x, float y) { set_stick(self, stick.value, x, y); }
	public float getStickX(Stick stick) { return get_stick_x(self, stick.value); }
	public float getStickX(Stick.Enum stick) { return get_stick_x(self, stick.value); }
	public float getStickY(Stick stick) { return get_stick_y(self, stick.value); }
	public float getStickY(Stick.Enum stick) { return get_stick_y(self, stick.value); }
	public void setAxisName(Axis axis, String name) { set_axis_name(self, axis.value, name); }
	public void setAxisName(Axis.Enum axis, String name) { set_axis_name(self, axis.value, name); }
	public String getAxisName(Axis axis) { return get_axis_name(self, axis.value); }
	public String getAxisName(Axis.Enum axis) { return get_axis_name(self, axis.value); }
	public Axis findAxis(String name) { return new Axis(find_axis(self, name)); }
	public void setAxis(Axis axis, float value) { set_axis(self, axis.value, value); }
	public void setAxis(Axis.Enum axis, float value) { set_axis(self, axis.value, value); }
	public float getAxis(Axis axis) { return get_axis(self, axis.value); }
	public float getAxis(Axis.Enum axis) { return get_axis(self, axis.value); }
	public void setButtonName(Button button, String name) { set_button_name(self, button.value, name); }
	public void setButtonName(Button.Enum button, String name) { set_button_name(self, button.value, name); }
	public String getButtonName(Button button) { return get_button_name(self, button.value); }
	public String getButtonName(Button.Enum button) { return get_button_name(self, button.value); }
	public Button findButton(String name) { return new Button(find_button(self, name)); }
	public void setButton(Button button, boolean value) { set_button(self, button.value, value); }
	public void setButton(Button.Enum button, boolean value) { set_button(self, button.value, value); }
	public boolean getButton(Button button) { return get_button(self, button.value, false); }
	public boolean getButton(Button.Enum button) { return get_button(self, button.value, false); }
	public boolean getButton(Button button, boolean clear) { return get_button(self, button.value, clear); }
	public boolean getButton(Button.Enum button, boolean clear) { return get_button(self, button.value, clear); }
	public boolean wasButtonPressed(Button button) { return was_button_pressed(self, button.value); }
	public boolean wasButtonPressed(Button.Enum button) { return was_button_pressed(self, button.value); }
	public boolean wasButtonReleased(Button button) { return was_button_released(self, button.value); }
	public boolean wasButtonReleased(Button.Enum button) { return was_button_released(self, button.value); }
	public void setButtonValue(Button button, float value) { set_button_value(self, button.value, value); }
	public void setButtonValue(Button.Enum button, float value) { set_button_value(self, button.value, value); }
	public float getButtonValue(Button button) { return get_button_value(self, button.value); }
	public float getButtonValue(Button.Enum button) { return get_button_value(self, button.value); }
	public void setMotorName(Motor motor, String name) { set_motor_name(self, motor.value, name); }
	public void setMotorName(Motor.Enum motor, String name) { set_motor_name(self, motor.value, name); }
	public String getMotorName(Motor motor) { return get_motor_name(self, motor.value); }
	public String getMotorName(Motor.Enum motor) { return get_motor_name(self, motor.value); }
	public Motor findMotor(String name) { return new Motor(find_motor(self, name)); }
	public void setMotor(Motor motor, float value) { set_motor(self, motor.value, value); }
	public void setMotor(Motor.Enum motor, float value) { set_motor(self, motor.value, value); }
	public float getMotor(Motor motor) { return get_motor(self, motor.value); }
	public float getMotor(Motor.Enum motor) { return get_motor(self, motor.value); }
	public void setButtonPressedCallback(ButtonPressedCallback func) { set_button_pressed_callback(self, func); }
	public void setButtonReleasedCallback(ButtonReleasedCallback func) { set_button_released_callback(self, func); }
	public void setConnectedCallback(ConnectedCallback func) { set_connected_callback(self, func); }
	public void setDisconnectedCallback(DisconnectedCallback func) { set_disconnected_callback(self, func); }
	
	private static native long new_();
	private static native long new_1(int index);
	private static native long new_2(int type, int index);
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
	private static native int get_num_controllers();
	private static native int find_controller(String name);
	private static native long get_controller(int index);
	private static native void update_();
	private static native void set_type(long self, int type);
	private static native int get_type(long self);
	private static native String get_type_name(int type);
	private static native String get_type_name_1(long self);
	private static native boolean is_unknown(long self);
	private static native boolean is_joystick(long self);
	private static native boolean is_game_pad(long self);
	private static native boolean is_wheel(long self);
	private static native void set_index(long self, int index);
	private static native int get_index(long self);
	private static native void set_name(long self, String name);
	private static native String get_name(long self);
	private static native void set_model(long self, String model);
	private static native String get_model(long self);
	private static native boolean is_connected(long self);
	private static native boolean was_connected(long self);
	private static native boolean connect_(long self, String name);
	private static native void release_(long self);
	private static native void set_stick_name(long self, int stick, String name);
	private static native String get_stick_name(long self, int stick);
	private static native int find_stick(long self, String name);
	private static native void set_stick(long self, int stick, float x, float y);
	private static native float get_stick_x(long self, int stick);
	private static native float get_stick_y(long self, int stick);
	private static native void set_axis_name(long self, int axis, String name);
	private static native String get_axis_name(long self, int axis);
	private static native int find_axis(long self, String name);
	private static native void set_axis(long self, int axis, float value);
	private static native float get_axis(long self, int axis);
	private static native void set_button_name(long self, int button, String name);
	private static native String get_button_name(long self, int button);
	private static native int find_button(long self, String name);
	private static native void set_button(long self, int button, boolean value);
	private static native boolean get_button(long self, int button, boolean clear);
	private static native boolean was_button_pressed(long self, int button);
	private static native boolean was_button_released(long self, int button);
	private static native void set_button_value(long self, int button, float value);
	private static native float get_button_value(long self, int button);
	private static native void set_motor_name(long self, int motor, String name);
	private static native String get_motor_name(long self, int motor);
	private static native int find_motor(long self, String name);
	private static native void set_motor(long self, int motor, float value);
	private static native float get_motor(long self, int motor);
	private static native void set_button_pressed_callback(long self, ButtonPressedCallback func);
	private static native void set_button_released_callback(long self, ButtonReleasedCallback func);
	private static native void set_connected_callback(long self, ConnectedCallback func);
	private static native void set_disconnected_callback(long self, DisconnectedCallback func);
	
	protected Controller(long self) {
		init_(self);
	}
	public static Controller Null() {
		return new Controller((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Controller[] ptr) {
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

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_SYSTEM_CONTROLLER_H__
#define __TELLUSIM_SYSTEM_CONTROLLER_H__

#include <core/TellusimString.h>
#include <core/TellusimFunction.h>

/*
 */
namespace Tellusim {
	
	/**
	 * The Controller class provides cross-platform methods to interact with various types of controllers such as joysticks, gamepads, and steering wheels.
	 * It supports querying and setting controller properties such as type, name, model, buttons, sticks, axes, and motors.
	 * It also allows you to check the connection status of the controller and register callbacks for button presses, releases, and connection events.
	 * The class allows for managing multiple controllers, retrieving controller details by index, and interacting with buttons, axes, and motors by name or value.
	 * It also supports the use of custom callbacks for button events and connection changes.
	 * The class includes static methods for querying and managing all connected controllers.
	 */
	class TS_API Controller {
			
			TS_DECLARE_PTR_0(Controller, 0)
			
		public:
			
			/// Controller types
			enum Type {
				TypeUnknown = 0,
				TypeJoystick,
				TypeGamePad,
				TypeWheel,
				NumTypes,
			};
			
			/// Controller sticks
			enum Stick {
				StickLeft = 0,
				StickRight,
				NumSticks,
			};
			
			/// Controller axes
			enum Axis {
				AxisX = 0,
				AxisY,
				AxisZ,
				AxisRX,
				AxisRY,
				AxisRZ,
				NumAxes = 16,
			};
			
			/// Controller buttons
			enum Button {
				
				/// D-Pad
				ButtonLeft = 0,
				ButtonRight,
				ButtonDown,
				ButtonUp,
				
				/// Common buttons
				ButtonHome,
				
				/// Xbox buttons
				ButtonShoulderLeft,
				ButtonShoulderRight,
				ButtonTriggerLeft,
				ButtonTriggerRight,
				ButtonStickLeft,
				ButtonStickRight,
				ButtonA,
				ButtonB,
				ButtonX,
				ButtonY,
				ButtonView,
				ButtonMenu,
				
				/// PlayStation buttons
				ButtonL1 = ButtonShoulderLeft,
				ButtonR1,
				ButtonL2,
				ButtonR2,
				ButtonL3,
				ButtonR3,
				ButtonCross,
				ButtonCircle,
				ButtonSquare,
				ButtonTriangle,
				ButtonShare,
				ButtonOptions,
				
				NumButtons = 32,
			};
			
			/// Controller motors
			enum Motor {
				MotorLow = 0,
				MotorHigh,
				NumMotors,
			};
			
			Controller();
			explicit Controller(uint32_t index);
			explicit Controller(Type type, uint32_t index = Maxu32);
			
			/// all controllers
			static uint32_t getNumControllers();
			static uint32_t findController(const char *name);
			static Controller getController(uint32_t index);
			
			/// update controllers
			static void update();
			
			/// controller type
			void setType(Type type);
			Type getType() const;
			
			static const char *getTypeName(Type type);
			
			const char *getTypeName() const;
			
			TS_INLINE bool isUnknown() const { return (getType() == TypeUnknown); }
			TS_INLINE bool isJoystick() const { return (getType() == TypeJoystick); }
			TS_INLINE bool isGamePad() const { return (getType() == TypeGamePad); }
			TS_INLINE bool isWheel() const { return (getType() == TypeWheel); }
			
			/// controller index
			void setIndex(uint32_t index);
			uint32_t getIndex() const;
			
			/// controller name
			void setName(const char *name);
			String getName() const;
			
			/// controller model
			void setModel(const char *model);
			String getModel() const;
			
			/// check controller
			bool isConnected() const;
			bool wasConnected() const;
			
			/// connect controller
			bool connect(const char *name = nullptr);
			void release();
			
			/// stick name
			void setStickName(Stick stick, const char *name);
			String getStickName(Stick stick) const;
			Stick findStick(const char *name) const;
			
			/// stick value
			void setStick(Stick stick, float32_t x, float32_t y);
			float32_t getStickX(Stick stick) const;
			float32_t getStickY(Stick stick) const;
			
			/// axis name
			void setAxisName(Axis axis, const char *name);
			String getAxisName(Axis axis) const;
			Axis findAxis(const char *name) const;
			
			/// axis value
			void setAxis(Axis axis, float32_t value);
			float32_t getAxis(Axis axis) const;
			
			/// button name
			void setButtonName(Button button, const char *name);
			String getButtonName(Button button) const;
			Button findButton(const char *name) const;
			
			/// button state
			void setButton(Button button, bool value);
			bool getButton(Button button, bool clear = false) const;
			bool wasButtonPressed(Button button) const;
			bool wasButtonReleased(Button button) const;
			
			/// button value
			void setButtonValue(Button button, float32_t value);
			float32_t getButtonValue(Button button) const;
			
			/// motor name
			void setMotorName(Motor motor, const char *name);
			String getMotorName(Motor motor) const;
			Motor findMotor(const char *name) const;
			
			/// motor state
			void setMotor(Motor motor, float32_t value);
			float32_t getMotor(Motor motor) const;
			
			/// button pressed callback
			using ButtonPressedCallback = Function<void(Controller controller, Button button)>;
			void setButtonPressedCallback(const ButtonPressedCallback &func);
			ButtonPressedCallback getButtonPressedCallback() const;
			
			/// button released callback
			using ButtonReleasedCallback = Function<void(Controller controller, Button button)>;
			void setButtonReleasedCallback(const ButtonReleasedCallback &func);
			ButtonReleasedCallback getButtonReleasedCallback() const;
			
			/// connected callback
			using ConnectedCallback = Function<void(Controller controller)>;
			void setConnectedCallback(const ConnectedCallback &func);
			ConnectedCallback getConnectedCallback() const;
			
			/// disconnected callback
			using DisconnectedCallback = Function<void(Controller controller)>;
			void setDisconnectedCallback(const DisconnectedCallback &func);
			DisconnectedCallback getDisconnectedCallback() const;
			
			/// controller names
			static const char *NameXbox;
			static const char *NamePlayStation;
			static const char *NameNintendo;
	};
}

#endif /* __TELLUSIM_SYSTEM_CONTROLLER_H__ */

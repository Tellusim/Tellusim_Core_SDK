// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_INTERFACE_RMLUI_H__
#define __TELLUSIM_PLUGINS_INTERFACE_RMLUI_H__

/*
 */
#define RMLUI_VECTOR2_USER_EXTRA \
	constexpr Vector2(const Tellusim::Vector2<Type> &v) : x(v.x), y(v.y) { } \
	operator Tellusim::Vector2<Type>() const { return Tellusim::Vector2<Type>(x, y); }

#define RMLUI_VECTOR3_USER_EXTRA \
	constexpr Vector3(const Tellusim::Vector3<Type> &v) : x(v.x), y(v.y), z(v.z) { } \
	operator Tellusim::Vector3<Type>() const { return Tellusim::Vector3<Type>(x, y, z); }

#define RMLUI_VECTOR4_USER_EXTRA \
	constexpr Vector4(const Tellusim::Vector4<Type> &v) : x(v.x), y(v.y), z(v.z), w(v.w) { } \
	operator Tellusim::Vector4<Type>() const { return Tellusim::Vector4<Type>(x, y, z, w); }

/*
 */
#include <core/TellusimPointer.h>
#include <platform/TellusimWindow.h>
#include <platform/TellusimDevice.h>

#define RMLUI_STATIC_LIB
#define RMLUI_MATRIX_ROW_MAJOR
#define RMLUI_NO_THIRDPARTY_CONTAINERS

#include "../extern/RmlUi/Core.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	class FileInterface;
	class SystemInterface;
	class RenderInterface;
	
	/*
	 */
	class RmlUi {
			
		public:
			
			RmlUi();
			RmlUi(Window &window, Device &device);
			virtual ~RmlUi();
			
			/// clear RmlUi
			void clear();
			
			/// RmlUi status
			TS_INLINE bool isInitialized() const { return (context != nullptr); }
			
			/// initialize RmlUi
			bool init(Window &window, Device &device, const char *name = nullptr, float32_t scale = 0.0f);
			
			/// update RmlUi
			bool update();
			
			/// render RmlUi into target
			bool render(const Target &target, Command &command);
			
			/// render RmlUi into texture
			bool render(Texture &color_texture, Texture &depth_texture);
			
			/// draw fullscreen texture
			bool draw(const Target &target, Command &command, Texture &texture);
			
			/// RmlUi context
			TS_INLINE Rml::Context *getContext() { return context; }
			
			/// RmlUi callbacks
			void setEnabled(bool enable);
			TS_INLINE bool isEnabled() const { return is_enabled; }
			
		private:
			
			int32_t get_key_state() const;
			static int32_t translate_mouse(Window::Button button);
			static Rml::Input::KeyIdentifier translate_keyboard(uint32_t key);
			
			Window window;
			Device device;
			
			AutoPtr<FileInterface> file_interface;
			AutoPtr<SystemInterface> system_interface;
			AutoPtr<RenderInterface> render_interface;
			
			Rml::Context *context = nullptr;
			
			bool is_enabled = true;
			
			Window::MousePressedCallback mouse_pressed;
			Window::MouseReleasedCallback mouse_released;
			Window::MouseChangedCallback mouse_changed;
			Window::MouseRotatedCallback mouse_rotated;
			
			Window::KeyboardPressedCallback keyboard_pressed;
			Window::KeyboardReleasedCallback keyboard_released;
	};
}

#endif /* __TELLUSIM_PLUGINS_INTERFACE_RMLUI_H__ */

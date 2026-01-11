// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_INTERFACE_IMGUI_H__
#define __TELLUSIM_PLUGINS_INTERFACE_IMGUI_H__

/*
 */
#define IM_VEC2_CLASS_EXTRA \
	constexpr ImVec2(const Tellusim::Vector2f &v) : x(v.x), y(v.y) { } \
	operator Tellusim::Vector2f() const { return Tellusim::Vector2f(x, y); }

#define IM_VEC4_CLASS_EXTRA \
	constexpr ImVec4(const Tellusim::Vector4f &v) : x(v.x), y(v.y), z(v.z), w(v.w) { } \
	constexpr ImVec4(const Tellusim::Color &c) : x(c.r), y(c.g), z(c.b), w(c.a) { } \
	operator Tellusim::Vector4f() const { return Tellusim::Vector4f(x, y, z, w); } \
	operator Tellusim::Color() const { return Tellusim::Color(x, y, z, w); }

/*
 */
#include <math/TellusimMath.h>
#include <math/TellusimColor.h>
#include <platform/TellusimWindow.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimSampler.h>
#include <platform/TellusimTexture.h>
#include "../extern/imgui/imgui.h"

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Target;
	class Command;
	
	/*
	 */
	class TS_ImGui {
			
		public:
			
			explicit TS_ImGui(Window &window);
			~TS_ImGui();
			
			/// clear ImGui
			void clear();
			
			/// initialize ImGui
			bool init(Window &window);
			
			/// begin frame
			bool frame(const Device &device, const Target &target);
			
			/// render frame
			void render(Command &command);
			
		private:
			
			/// translate events
			static int32_t translate_mouse(Window::Button button);
			static ImGuiKey translate_keyboard(uint32_t key);
			
			/// create resources
			bool create(const Device &device, const Target &target);
			
			bool initialized = false;
			
			Window window;
			
			Pipeline pipeline;
			Sampler sampler;
			Texture texture;
			
			bool flipped = false;
			float64_t time = 0.0;
			float32_t scale = 1.0f;
			
			Window::MousePressedCallback mouse_pressed;
			Window::MouseReleasedCallback mouse_released;
			Window::MouseChangedCallback mouse_changed;
			Window::MouseRotatedCallback mouse_rotated;
			
			Window::KeyboardPressedCallback keyboard_pressed;
			Window::KeyboardReleasedCallback keyboard_released;
	};
}

#endif /* __TELLUSIM_PLUGINS_INTERFACE_IMGUI_H__ */

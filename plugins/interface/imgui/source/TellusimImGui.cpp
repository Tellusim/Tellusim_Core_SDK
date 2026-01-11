// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#define IMGUI_DEFINE_MATH_OPERATORS

#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <format/TellusimImage.h>
#include <platform/TellusimWindow.h>
#include <platform/TellusimTarget.h>
#include <platform/TellusimCommand.h>
#include <platform/TellusimDevice.h>

#include "../include/TellusimImGui.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	TS_ImGui::TS_ImGui(Window &window) {
		init(window);
	}
	
	TS_ImGui::~TS_ImGui() {
		clear();
	}
	
	/*
	 */
	bool TS_ImGui::init(Window &w) {
		
		window = w;
		
		// create ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		initialized = true;
		
		// input/output
		ImGuiIO &io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		
		// window scale
		scale = window.getScale();
		io.DisplayFramebufferScale = ImVec2(scale, scale);
		
		// save callbacks
		mouse_pressed = window.getMousePressedCallback();
		mouse_released = window.getMouseReleasedCallback();
		mouse_changed = window.getMouseChangedCallback();
		mouse_rotated = window.getMouseRotatedCallback();
		keyboard_pressed = window.getKeyboardPressedCallback();
		keyboard_released = window.getKeyboardReleasedCallback();
		
		// mouse callbacks
		window.setMousePressedCallback([this](Window::Button button) {
			if(initialized) ImGui::GetIO().AddMouseButtonEvent(translate_mouse(button), true);
			if(mouse_pressed) mouse_pressed(button);
		});
		window.setMouseReleasedCallback([this](Window::Button button) {
			if(initialized) ImGui::GetIO().AddMouseButtonEvent(translate_mouse(button), false);
			if(mouse_released) mouse_released(button);
		});
		window.setMouseChangedCallback([this](int32_t x, int32_t y) {
			if(initialized) ImGui::GetIO().AddMousePosEvent((float32_t)x, ImGui::GetIO().DisplaySize.y - (float32_t)y);
			if(mouse_changed) mouse_changed(x, y);
		});
		window.setMouseRotatedCallback([this](Window::Axis axis, float32_t delta) {
			if(initialized && axis == Window::AxisX) ImGui::GetIO().AddMouseWheelEvent(delta, 0.0f);
			if(initialized && axis == Window::AxisY) ImGui::GetIO().AddMouseWheelEvent(0.0f, delta);
			if(mouse_rotated) mouse_rotated(axis, delta);
		});
		
		// keyboard callbacks
		window.setKeyboardPressedCallback([this](uint32_t key, uint32_t code) {
			if(initialized) ImGui::GetIO().AddKeyEvent(translate_keyboard(key), true);
			if(initialized && code) ImGui::GetIO().AddInputCharacter(code);
			if(keyboard_pressed) keyboard_pressed(key, code);
		});
		window.setKeyboardReleasedCallback([this](uint32_t key) {
			if(initialized) ImGui::GetIO().AddKeyEvent(translate_keyboard(key), false);
			if(keyboard_released) keyboard_released(key);
		});
		
		return true;
	}
	
	/*
	 */
	void TS_ImGui::clear() {
		
		// destroy ImGui context
		if(initialized) {
			ImGui::DestroyContext();
			initialized = false;
		}
		
		// restore callbacks
		if(mouse_pressed) window.setMousePressedCallback(mouse_pressed);
		if(mouse_released) window.setMouseReleasedCallback(mouse_released);
		if(mouse_changed) window.setMouseChangedCallback(mouse_changed);
		if(mouse_rotated) window.setMouseRotatedCallback(mouse_rotated);
		if(keyboard_pressed) window.setKeyboardPressedCallback(keyboard_pressed);
		if(keyboard_released) window.setKeyboardReleasedCallback(keyboard_released);
		mouse_pressed.clear();
		mouse_released.clear();
		mouse_changed.clear();
		mouse_rotated.clear();
		keyboard_pressed.clear();
		keyboard_released.clear();
		
		// clear resources
		pipeline.clearPtr();
		sampler.clearPtr();
		texture.clearPtr();
		
		// clear window
		window.clearPtr();
	}
	
	/*
	 */
	bool TS_ImGui::create(const Device &device, const Target &target) {
		
		// check status
		if(!initialized) {
			TS_LOG(Error, "TS_ImGui::create(): is not initialized\n");
			return false;
		}
		
		ImGuiIO &io = ImGui::GetIO();
		
		// vertex shader
		const char *vertex_shader = R"(
			layout(std140, row_major, binding = 0) uniform Parameters {
				mat4 projection;
			};
			layout(location = 0) in vec4 in_position;
			layout(location = 1) in vec2 in_texcoord;
			layout(location = 2) in vec4 in_color;
			layout(location = 0) out vec2 s_texcoord;
			layout(location = 1) out vec4 s_color;
			void main() {
				gl_Position = projection * in_position;
				s_texcoord = in_texcoord;
				s_color = in_color;
			}
		)";
		
		// fragment shader
		const char *fragment_shader = R"(
			layout(binding = 0, set = 1) uniform texture2D in_texture;
			layout(binding = 0, set = 2) uniform sampler in_sampler;
			layout(location = 0) in vec2 s_texcoord;
			layout(location = 1) in vec4 s_color;
			layout(location = 0) out vec4 out_color;
			void main() {
				float)" R"( alpha = texture(sampler2D(in_texture, in_sampler), s_texcoord).x;
				out_color = s_color * vec4(1.0f, 1.0f, 1.0f, alpha);
			}
		)";
		
		// create pipeline
		pipeline = device.createPipeline();
		pipeline.setUniformMask(0, Shader::MaskVertex);
		pipeline.setSamplerMask(0, Shader::MaskFragment);
		pipeline.setTextureMask(0, Shader::MaskFragment);
		pipeline.addAttribute(Pipeline::AttributePosition, FormatRGf32, 0, offsetof(ImDrawVert, pos), sizeof(ImDrawVert));
		pipeline.addAttribute(Pipeline::AttributeTexCoord, FormatRGf32, 0, offsetof(ImDrawVert, uv), sizeof(ImDrawVert));
		pipeline.addAttribute(Pipeline::AttributeColor, FormatRGBAu8n, 0, offsetof(ImDrawVert, col), sizeof(ImDrawVert));
		pipeline.setBlendColor(Pipeline::BlendOpAdd, Pipeline::BlendFuncSrcAlpha, Pipeline::BlendFuncInvSrcAlpha);
		pipeline.setBlendAlpha(Pipeline::BlendOpAdd, Pipeline::BlendFuncOne, Pipeline::BlendFuncInvSrcAlpha);
		pipeline.setColorFormat(target.getColorFormat());
		pipeline.setDepthFormat(target.getDepthFormat());
		pipeline.setDepthFunc(Pipeline::DepthFuncAlways);
		pipeline.setScissorTest(true);
		if(!pipeline.createShaderGLSL(Shader::TypeVertex, vertex_shader)) return false;
		if(!pipeline.createShaderGLSL(Shader::TypeFragment, fragment_shader)) return false;
		if(!pipeline.create()) {
			TS_LOG(Error, "TS_ImGui::create(): can't create pipeline\n");
			return false;
		}
		
		// create sampler
		sampler = device.createSampler(Sampler::FilterPoint, Sampler::WrapModeClamp);
		if(!sampler) {
			TS_LOG(Error, "TS_ImGui::create(): can't create sampler\n");
			return false;
		}
		
		// get texture data
		int32_t width = 0;
		int32_t height = 0;
		uint8_t *data = nullptr;
		io.Fonts->GetTexDataAsAlpha8(&data, &width, &height);
		if(!data) {
			TS_LOG(Error, "TS_ImGui::create(): can't get texture data\n");
			return false;
		}
		
		// create texture
		Image image(Image::Type2D, FormatRu8n, Size(width, height));
		memcpy(image.getData(), data, width * height);
		texture = device.createTexture(image);
		if(!texture) {
			TS_LOG(Error, "TS_ImGui::create(): can't create texture\n");
			return false;
		}
		
		// texture pointer
		io.Fonts->SetTexID((ImTextureID)texture.getInternalPtr());
		
		return true;
	}
	
	/*
	 */
	bool TS_ImGui::frame(const Device &device, const Target &target) {
		
		// check status
		if(!initialized) {
			TS_LOG(Error, "TS_ImGui::frame(): is not initialized\n");
			return false;
		}
		
		ImGuiIO &io = ImGui::GetIO();
		
		// display size
		io.DisplaySize = ImVec2((float32_t)target.getWidth(), (float32_t)target.getHeight());
		
		// flipped flag
		flipped = target.isFlipped();
		
		// delta time
		float64_t current_time = Time::seconds();
		io.DeltaTime = (float32_t)(current_time - time);
		time = current_time;
		
		// create resources
		if(!pipeline && !create(device, target)) return false;
		
		// start frame
		ImGui::NewFrame();
		
		return true;
	}
	
	/*
	 */
	void TS_ImGui::render(Command &command) {
		
		// check status
		if(!initialized) return;
		
		// end frame
		ImGui::EndFrame();
		
		// render frame
		ImGui::Render();
		
		// get draw data
		ImDrawData *draw = ImGui::GetDrawData();
		
		// projection matrix
		float32_t l = draw->DisplayPos.x;
		float32_t r = draw->DisplayPos.x + draw->DisplaySize.x;
		float32_t t = draw->DisplayPos.y;
		float32_t b = draw->DisplayPos.y + draw->DisplaySize.y;
		if(flipped) swap(t, b);
		
		// set pipeline
		command.setPipeline(pipeline);
		command.setUniform(0, Matrix4x4f::ortho(l, r, b, t, -1.0f, 1.0f));
		command.setSampler(0, sampler);
		command.setTexture(0, texture);
		
		// clip parameters
		Vector2f offset = draw->DisplayPos;
		
		// draw data
		for(int32_t i = 0; i < draw->CmdListsCount; i++) {
			const ImDrawList *list = draw->CmdLists[i];
			
			// buffers data
			command.setVertexData(0, list->VtxBuffer.Data, list->VtxBuffer.Size * sizeof(ImDrawVert));
			command.setIndexData(FormatRu16, list->IdxBuffer.Data, list->IdxBuffer.Size * sizeof(ImDrawIdx));
			
			// draw commands
			for(int32_t j = 0; j < list->CmdBuffer.Size; j++) {
				const ImDrawCmd *cmd = &list->CmdBuffer[j];
				
				// visible rect
				Vector2f min = Vector2f(cmd->ClipRect.x, cmd->ClipRect.y) - offset;
				Vector2f max = Vector2f(cmd->ClipRect.z, cmd->ClipRect.w) - offset;
				if(max.x <= min.x || max.y <= min.y) continue;
				
				// set scissor
				int32_t x = (int32_t)min.x;
				int32_t y = (int32_t)(draw->DisplaySize.y - max.y);
				int32_t width = (int32_t)(max.x - min.x);
				int32_t height = (int32_t)(max.y - min.y);
				command.setScissor(0, Scissor(x, y, width, height));
				
				// draw elements
				command.drawElements(cmd->ElemCount, cmd->IdxOffset, cmd->VtxOffset);
			}
		}
	}
	
	/*
	 */
	int32_t TS_ImGui::translate_mouse(Window::Button button) {
		if(button == Window::ButtonLeft) return 0;
		if(button == Window::ButtonLeft2) return 0;
		if(button == Window::ButtonRight) return 1;
		if(button == Window::ButtonRight2) return 1;
		if(button == Window::ButtonMiddle) return 2;
		if(button == Window::ButtonMiddle2) return 2;
		if(button == Window::ButtonBack) return 3;
		if(button == Window::ButtonBack) return 3;
		if(button == Window::ButtonForward) return 4;
		if(button == Window::ButtonForward) return 4;
		return -1;
	}
	
	ImGuiKey TS_ImGui::translate_keyboard(uint32_t key) {
		switch(key) {
			case Window::KeyEsc: return ImGuiKey_Escape;
			case Window::KeyTab: return ImGuiKey_Tab;
			case Window::KeyBackspace: return ImGuiKey_Backspace;
			case Window::KeyDelete: return ImGuiKey_Delete;
			case Window::KeyInsert: return ImGuiKey_Insert;
			case Window::KeyReturn: return ImGuiKey_Enter;
			case Window::KeyPause: return ImGuiKey_Pause;
			case Window::KeyPrior: return ImGuiKey_PageUp;
			case Window::KeyNext: return ImGuiKey_PageDown;
			case Window::KeyEnd: return ImGuiKey_End;
			case Window::KeyHome: return ImGuiKey_Home;
			case Window::KeyUp: return ImGuiKey_UpArrow;
			case Window::KeyDown: return ImGuiKey_DownArrow;
			case Window::KeyLeft: return ImGuiKey_LeftArrow;
			case Window::KeyRight: return ImGuiKey_RightArrow;
			case Window::KeyNum: return ImGuiKey_NumLock;
			case Window::KeyCaps: return ImGuiKey_CapsLock;
			case Window::KeyScroll: return ImGuiKey_ScrollLock;
			case Window::KeyShift: return ImGuiKey_LeftShift;
			case Window::KeyCtrl: return ImGuiKey_LeftCtrl;
			case Window::KeyAlt: return ImGuiKey_LeftAlt;
			case Window::KeyF1: return ImGuiKey_F1;
			case Window::KeyF2: return ImGuiKey_F2;
			case Window::KeyF3: return ImGuiKey_F3;
			case Window::KeyF4: return ImGuiKey_F4;
			case Window::KeyF5: return ImGuiKey_F5;
			case Window::KeyF6: return ImGuiKey_F6;
			case Window::KeyF7: return ImGuiKey_F7;
			case Window::KeyF8: return ImGuiKey_F8;
			case Window::KeyF9: return ImGuiKey_F9;
			case Window::KeyF10: return ImGuiKey_F10;
			case Window::KeyF11: return ImGuiKey_F11;
			case Window::KeyF12: return ImGuiKey_F12;
			case ' ': return ImGuiKey_Space;
			case '1': return ImGuiKey_1;
			case '2': return ImGuiKey_2;
			case '3': return ImGuiKey_3;
			case '4': return ImGuiKey_4;
			case '5': return ImGuiKey_5;
			case '6': return ImGuiKey_6;
			case '7': return ImGuiKey_7;
			case '8': return ImGuiKey_8;
			case '9': return ImGuiKey_9;
			case '0': return ImGuiKey_0;
			case 'a': return ImGuiKey_A;
			case 'b': return ImGuiKey_B;
			case 'c': return ImGuiKey_C;
			case 'd': return ImGuiKey_D;
			case 'e': return ImGuiKey_E;
			case 'f': return ImGuiKey_F;
			case 'g': return ImGuiKey_G;
			case 'h': return ImGuiKey_H;
			case 'i': return ImGuiKey_I;
			case 'j': return ImGuiKey_K;
			case 'k': return ImGuiKey_K;
			case 'l': return ImGuiKey_L;
			case 'm': return ImGuiKey_M;
			case 'n': return ImGuiKey_N;
			case 'o': return ImGuiKey_O;
			case 'p': return ImGuiKey_P;
			case 'q': return ImGuiKey_Q;
			case 'r': return ImGuiKey_R;
			case 's': return ImGuiKey_S;
			case 't': return ImGuiKey_T;
			case 'u': return ImGuiKey_U;
			case 'v': return ImGuiKey_V;
			case 'w': return ImGuiKey_W;
			case 'x': return ImGuiKey_X;
			case 'y': return ImGuiKey_Y;
			case 'z': return ImGuiKey_Z;
			case '\'': return ImGuiKey_Apostrophe;
			case ',': return ImGuiKey_Comma;
			case '-': return ImGuiKey_Minus;
			case '.': return ImGuiKey_Period;
			case '/': return ImGuiKey_Slash;
			case ';': return ImGuiKey_Semicolon;
			case '=': return ImGuiKey_Equal;
			case '[': return ImGuiKey_LeftBracket;
			case '\\': return ImGuiKey_Backslash;
			case ']': return ImGuiKey_RightBracket;
			case '`': return ImGuiKey_GraveAccent;
		}
		return ImGuiKey_None;
	}
}

#include "../extern/imgui/imgui.cpp"
#include "../extern/imgui/imgui_draw.cpp"
#include "../extern/imgui/imgui_tables.cpp"
#include "../extern/imgui/imgui_widgets.cpp"

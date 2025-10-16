// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <core/TellusimSource.h>
#include <format/TellusimXml.h>
#include <platform/TellusimDevice.h>

#include "include/TellusimControlFlow.h"

/*
 */
using namespace Tellusim;

/*
 */
static bool get_level(const String &level) {
	if(level == "1") return true;
	if(level == "+") return true;
	return false;
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Flow", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create canvas
	Canvas canvas;
	
	// create root control
	ControlRoot root(canvas, true);
	root.setFontSize(18);
	
	// keyboard callbacks
	window.setKeyboardPressedCallback([&](uint32_t key, uint32_t code) {
		if(root) root.setKeyboardKey(translate_key(key, true), code, true);
		if(key == Window::KeyEsc) window.stop();
	});
	window.setKeyboardReleasedCallback([&](uint32_t key) {
		if(root) root.setKeyboardKey(translate_key(key, true), 0, false);
	});
	
	// create controls
	ControlPanel panel(&root, 1, 0.0f, 4.0f);
	ControlText text(&panel, "Panel (Mouse+Shift - clone nodes, Mouse+Ctrl - select nodes, DoubleClick - remove connection)");
	text.setAlign(Control::AlignTop);
	
	// create Flow
	ControlFlow flow(&panel, "logic", 1);
	if(!flow.create()) return 1;
	
	{
		// create types
		uint32_t gnd_type = flow.addType("gnd", Color::black, ControlFlow::ShapeSquare);
		flow.setTypeConnectionWidth(gnd_type, 4.0f);
		flow.setTypeText(gnd_type, "GND");
		flow.setTypeInfo(gnd_type, "Ground");
		
		uint32_t vcc_type = flow.addType("vcc", Color::red, ControlFlow::ShapePlus);
		flow.setTypeConnectionWidth(vcc_type, 3.0f);
		flow.setTypeText(vcc_type, "VCC");
		flow.setTypeInfo(vcc_type, "Voltage Input/Output");
		
		uint32_t level_type = flow.addType("level", Color::white, ControlFlow::ShapeCircle);
		flow.setTypeInputMask(level_type, ControlFlow::TypeMask(gnd_type) | ControlFlow::TypeMask(vcc_type));
		flow.setTypeUpdateCallback(level_type, [](ControlFlow *flow, ControlText text, String value, uint32_t type) {
			if(value && value.tou32()) text.setText("1");
			else if(value) text.setText(value);
			else text.setText("");
		});
		flow.setTypeConnectionWidth(level_type, 2.0f);
		flow.setTypeInfo(level_type, "Logical Level");
		flow.setTypeValue(level_type, "0");
		
		// create protos
		uint32_t battery_proto = flow.addProto("bat", {}, { vcc_type, gnd_type });
		flow.setProtoText(battery_proto, "Battery");
		flow.setProtoInfo(battery_proto, "Power Supply");
		flow.setProtoMultiOutput(battery_proto, 0, true);
		flow.setProtoMultiOutput(battery_proto, 1, true);
		flow.setProtoOutputValue(battery_proto, "vcc", "+");
		flow.setProtoOutputValue(battery_proto, "gnd", "-");
		
		// switch proto
		uint32_t switch_proto = flow.addProto("sw", { vcc_type, gnd_type }, { vcc_type, level_type, gnd_type });
		flow.setProtoCreateCallback(switch_proto, [](ControlFlow *flow, ControlGrid grid, uint32_t node) {
			ControlCheck check(&grid, "On");
			check.setFontName("sansb.ttf");
			check.setFontSize(20);
			check.setClickedCallback(makeFunction([](ControlCheck check, ControlFlow *flow, uint32_t node) {
				const String &vcc = flow->getInputValue(node, "vcc");
				const String &gnd = flow->getInputValue(node, "gnd");
				if(gnd == "-" && vcc == "+") flow->setOutputValue(node, "level", check.isChecked() ? "1" : "0");
				flow->traverseNodes(node);
			}, ControlCheck::null, flow, node));
		});
		flow.setProtoUpdateCallback(switch_proto, [](ControlFlow *flow, uint32_t node, bool inverse) {
			const String &vcc = flow->getInputValue(node, "vcc");
			const String &gnd = flow->getInputValue(node, "gnd");
			if(vcc != "+" || gnd != "-") flow->clearOutputValue(node, "level");
			flow->setOutputValue(node, "vcc", vcc.get());
			flow->setOutputValue(node, "gnd", gnd.get());
		});
		flow.setProtoText(switch_proto, "Switch");
		flow.setProtoInfo(switch_proto, "Switch");
		flow.setProtoMultiOutput(switch_proto, 0, true);
		flow.setProtoMultiOutput(switch_proto, 1, true);
		flow.setProtoMultiOutput(switch_proto, 2, true);
		
		// button proto
		uint32_t button_proto = flow.addProto("but", { vcc_type, gnd_type }, { vcc_type, level_type, gnd_type });
		flow.setProtoCreateCallback(button_proto, [](ControlFlow *flow, ControlGrid grid, uint32_t node) {
			ControlButton button(&grid, "Click");
			button.setFontName("sansb.ttf");
			button.setFontSize(20);
			button.setSize(64.0f, 24.0f);
			button.setClickedCallback(makeFunction([](ControlButton button, ControlFlow *flow, uint32_t node) {
				const String &vcc = flow->getInputValue(node, "vcc");
				const String &gnd = flow->getInputValue(node, "gnd");
				if(gnd == "-" && vcc == "+") {
					flow->setOutputValue(node, "level", "1");
					flow->traverseNodes(node);
					flow->setOutputValue(node, "level", "0");
					flow->traverseNodes(node);
				}
			}, ControlButton::null, flow, node));
		});
		flow.setProtoUpdateCallback(button_proto, [](ControlFlow *flow, uint32_t node, bool inverse) {
			const String &vcc = flow->getInputValue(node, "vcc");
			const String &gnd = flow->getInputValue(node, "gnd");
			if(vcc != "+" || gnd != "-") flow->clearOutputValue(node, "level");
			flow->setOutputValue(node, "vcc", vcc.get());
			flow->setOutputValue(node, "gnd", gnd.get());
		});
		flow.setProtoText(button_proto, "Button");
		flow.setProtoInfo(button_proto, "Button");
		flow.setProtoMultiOutput(button_proto, 0, true);
		flow.setProtoMultiOutput(button_proto, 1, true);
		flow.setProtoMultiOutput(button_proto, 2, true);
		
		// led proto
		uint32_t led_proto = flow.addProto("led", { level_type, gnd_type });
		flow.setProtoCreateCallback(led_proto, [](ControlFlow *flow, ControlGrid grid, uint32_t node) {
			ControlCombo combo(&grid, { "White", "Red", "Green", "Blue" });
			if(flow->getNodeValue(node)) combo.setCurrentText(flow->getNodeValue(node));
			combo.setChangedCallback(makeFunction([](ControlCombo combo, ControlFlow *flow, uint32_t node) {
				flow->setChanged(true);
			}, ControlCombo::null, flow, node));
			flow->setNodeUpdateCallback(node, makeFunction([](ControlFlow *flow, uint32_t node, bool inverse, ControlCombo combo) {
				const String &gnd = flow->getInputValue(node, "gnd");
				const String &level = flow->getInputValue(node, "level");
				Color colors[] = { Color::white, Color::red, Color::green, Color::blue };
				if(gnd == "-" && level == "1") flow->getNodeDialog(node).setColor(colors[combo.getCurrentIndex()] * 2.0f);
				else if(gnd == "-" && level == "+") flow->getNodeDialog(node).setColor(colors[combo.getCurrentIndex()] * 4.0f);
				else flow->getNodeDialog(node).setColor(Color::gray);
			}, nullptr, 0, false, combo));
			flow->setNodeLoadCallback(node, makeFunction([](ControlFlow *flow, const Xml *xml, uint32_t node, ControlCombo combo) {
				combo.setCurrentIndex(xml->getData("color", 0u));
			}, nullptr, nullptr, node, combo));
			flow->setNodeSaveCallback(node, makeFunction([](const ControlFlow *flow, Xml *xml, uint32_t node, ControlCombo combo) {
				xml->setData("color", combo.getCurrentIndex());
			}, nullptr, nullptr, node, combo));
		});
		for(uint32_t i = 0; i < flow.getNumProtoInputs(led_proto); i++) {
			flow.setProtoInputUpdateCallback(led_proto, i, [](ControlFlow *flow, uint32_t node, uint32_t input) {
				flow->updateNode(node);
			});
		}
		flow.setProtoText(led_proto, "LED");
		flow.setProtoInfo(led_proto, "Light-Emitting Diode");
		
		// logical not
		uint32_t not_proto = flow.addProto("not", { vcc_type, level_type, gnd_type }, { vcc_type, level_type, gnd_type });
		flow.setProtoUpdateCallback(not_proto, [](ControlFlow *flow, uint32_t node, bool inverse) {
			const String &vcc = flow->getInputValue(node, "vcc");
			const String &gnd = flow->getInputValue(node, "gnd");
			const String &a = flow->getInputValue(node, "level");
			if(vcc != "+" || gnd != "-") flow->clearOutputValue(node, "level");
			else if(!inverse) flow->setOutputValue(node, "level", String::fromu32(!get_level(a)));
			flow->setOutputValue(node, "vcc", vcc.get());
			flow->setOutputValue(node, "gnd", gnd.get());
		});
		flow.setProtoText(not_proto, "NOT");
		flow.setProtoInfo(not_proto, "Logical Not");
		flow.setProtoInputText(not_proto, 1, "A");
		flow.setProtoOutputText(not_proto, 1, "!A");
		flow.setProtoMultiOutput(not_proto, 0, true);
		flow.setProtoMultiOutput(not_proto, 1, true);
		flow.setProtoMultiOutput(not_proto, 2, true);
		
		// logical and
		uint32_t and_proto = flow.addProto("and", { vcc_type, level_type, level_type, gnd_type }, { vcc_type, level_type, gnd_type });
		flow.setProtoUpdateCallback(and_proto, [](ControlFlow *flow, uint32_t node, bool inverse) {
			const String &vcc = flow->getInputValue(node, "vcc");
			const String &gnd = flow->getInputValue(node, "gnd");
			const String &a = flow->getInputValue(node, "A");
			const String &b = flow->getInputValue(node, "B");
			if(vcc != "+" || gnd != "-") flow->clearOutputValue(node, "level");
			else if(!inverse) flow->setOutputValue(node, "level", String::fromu32(get_level(a) && get_level(b)));
			flow->setOutputValue(node, "vcc", vcc.get());
			flow->setOutputValue(node, "gnd", gnd.get());
		});
		flow.setProtoText(and_proto, "AND");
		flow.setProtoInfo(and_proto, "Logical And");
		flow.setProtoInputText(and_proto, 1, "A");
		flow.setProtoInputText(and_proto, 2, "B");
		flow.setProtoOutputText(and_proto, 1, "A&B");
		flow.setProtoMultiOutput(and_proto, 0, true);
		flow.setProtoMultiOutput(and_proto, 1, true);
		flow.setProtoMultiOutput(and_proto, 2, true);
		
		// logical not and
		uint32_t nand_proto = flow.addProto("nand", { vcc_type, level_type, level_type, gnd_type }, { vcc_type, level_type, gnd_type });
		flow.setProtoUpdateCallback(nand_proto, [](ControlFlow *flow, uint32_t node, bool inverse) {
			const String &vcc = flow->getInputValue(node, "vcc");
			const String &gnd = flow->getInputValue(node, "gnd");
			const String &a = flow->getInputValue(node, "A");
			const String &b = flow->getInputValue(node, "B");
			if(vcc != "+" || gnd != "-") flow->clearOutputValue(node, "level");
			else if(!inverse) flow->setOutputValue(node, "level", String::fromu32(!(get_level(a) && get_level(b))));
			flow->setOutputValue(node, "vcc", vcc.get());
			flow->setOutputValue(node, "gnd", gnd.get());
		});
		flow.setProtoText(nand_proto, "NAND");
		flow.setProtoInfo(nand_proto, "Logical Nand");
		flow.setProtoInputText(nand_proto, 1, "A");
		flow.setProtoInputText(nand_proto, 2, "B");
		flow.setProtoOutputText(nand_proto, 1, "!A&B");
		flow.setProtoMultiOutput(nand_proto, 0, true);
		flow.setProtoMultiOutput(nand_proto, 1, true);
		flow.setProtoMultiOutput(nand_proto, 2, true);
		
		// logical xor
		uint32_t xor_proto = flow.addProto("xor", { vcc_type, level_type, level_type, gnd_type }, { vcc_type, level_type, gnd_type });
		flow.setProtoUpdateCallback(xor_proto, [](ControlFlow *flow, uint32_t node, bool inverse) {
			const String &vcc = flow->getInputValue(node, "vcc");
			const String &gnd = flow->getInputValue(node, "gnd");
			const String &a = flow->getInputValue(node, "A");
			const String &b = flow->getInputValue(node, "B");
			if(vcc != "+" || gnd != "-") flow->clearOutputValue(node, "level");
			else if(!inverse) flow->setOutputValue(node, "level", String::fromu32((uint32_t)get_level(a) ^ (uint32_t)get_level(b)));
			flow->setOutputValue(node, "vcc", vcc.get());
			flow->setOutputValue(node, "gnd", gnd.get());
		});
		flow.setProtoText(xor_proto, "XOR");
		flow.setProtoInfo(xor_proto, "Logical Xor");
		flow.setProtoInputText(xor_proto, 1, "A");
		flow.setProtoInputText(xor_proto, 2, "B");
		flow.setProtoOutputText(xor_proto, 1, "A^B");
		flow.setProtoMultiOutput(xor_proto, 0, true);
		flow.setProtoMultiOutput(xor_proto, 1, true);
		flow.setProtoMultiOutput(xor_proto, 2, true);
		
		// logical or
		uint32_t or_proto = flow.addProto("or", { vcc_type, level_type, level_type, gnd_type }, { vcc_type, level_type, gnd_type });
		flow.setProtoUpdateCallback(or_proto, [](ControlFlow *flow, uint32_t node, bool inverse) {
			const String &vcc = flow->getInputValue(node, "vcc");
			const String &gnd = flow->getInputValue(node, "gnd");
			const String &a = flow->getInputValue(node, "A");
			const String &b = flow->getInputValue(node, "B");
			if(vcc != "+" || gnd != "-") flow->clearOutputValue(node, "level");
			else if(!inverse) flow->setOutputValue(node, "level", String::fromu32(get_level(a) || get_level(b)));
			flow->setOutputValue(node, "vcc", vcc.get());
			flow->setOutputValue(node, "gnd", gnd.get());
		});
		flow.setProtoText(or_proto, "OR");
		flow.setProtoInfo(or_proto, "Logical Or");
		flow.setProtoInputText(or_proto, 1, "A");
		flow.setProtoInputText(or_proto, 2, "B");
		flow.setProtoOutputText(or_proto, 1, "A|B");
		flow.setProtoMultiOutput(or_proto, 0, true);
		flow.setProtoMultiOutput(or_proto, 1, true);
		flow.setProtoMultiOutput(or_proto, 2, true);
		
		// load flow
		#if _EMSCRIPTEN
			{
		#else
			if(!Source::isSource("test_save.flow") || !flow.load("test_save.flow")) {
		#endif
			
			// clear nodes
			flow.clearNodes();
			
			// create nodes
			uint32_t battery_node = flow.addNode(battery_proto, Vector2f(-640.0f, 0.0f));
			uint32_t button_node = flow.addNode(button_proto, Vector2f(-384.0f, 0.0f));
			uint32_t nand_0_node = flow.addNode(nand_proto, Vector2f(0.0f, -128.0f));
			uint32_t nand_1_node = flow.addNode(nand_proto, Vector2f(0.0f, 128.0f));
			uint32_t nand_2_node = flow.addNode(nand_proto, Vector2f(256.0f, -128.0f));
			uint32_t nand_3_node = flow.addNode(nand_proto, Vector2f(256.0f, 128.0f));
			uint32_t led_0_node = flow.addNode(led_proto, Vector2f(512.0f, -128.0f), "Red");
			uint32_t led_1_node = flow.addNode(led_proto, Vector2f(512.0f, 128.0f), "Blue");
			
			// connect battery to the button
			flow.addOutputConnection(battery_node, "vcc", button_node, "vcc");
			flow.addOutputConnection(battery_node, "gnd", button_node, "gnd");
			
			// connect button to the nands
			flow.addOutputConnection(button_node, "vcc", nand_0_node, "vcc");
			flow.addOutputConnection(button_node, "gnd", nand_0_node, "gnd");
			flow.addOutputConnection(button_node, "vcc", nand_1_node, "vcc");
			flow.addOutputConnection(button_node, "gnd", nand_1_node, "gnd");
			flow.addOutputConnection(button_node, "level", nand_0_node, "B");
			flow.addOutputConnection(button_node, "level", nand_1_node, "A");
			
			// connect nands to the nands
			flow.addOutputConnection(nand_0_node, "vcc", nand_2_node, "vcc");
			flow.addOutputConnection(nand_0_node, "gnd", nand_2_node, "gnd");
			flow.addOutputConnection(nand_1_node, "vcc", nand_3_node, "vcc");
			flow.addOutputConnection(nand_1_node, "gnd", nand_3_node, "gnd");
			flow.addOutputConnection(nand_0_node, "level", nand_2_node, "B");
			flow.addOutputConnection(nand_1_node, "level", nand_3_node, "A");
			flow.addOutputConnection(nand_3_node, "level", nand_2_node, "A");
			flow.addOutputConnection(nand_2_node, "level", nand_3_node, "B");
			flow.addOutputConnection(nand_1_node, "level", nand_0_node, "A");
			flow.addOutputConnection(nand_2_node, "level", nand_1_node, "B");
			
			// connect nands to leds
			flow.addOutputConnection(nand_2_node, "level", led_0_node, "level");
			flow.addOutputConnection(nand_2_node, "gnd", led_0_node, "gnd");
			flow.addOutputConnection(nand_3_node, "level", led_1_node, "level");
			flow.addOutputConnection(nand_3_node, "gnd", led_1_node, "gnd");
			
			// save flow
			#if !_EMSCRIPTEN
				if(!flow.save("test_save.flow")) return 1;
			#endif
		}
	}
	
	// standalone
	#if !_EMSCRIPTEN
		{
			ControlFlow flow(nullptr);
			if(flow.load("test_save.flow")) {
				flow.traverseNodes(0, [](ControlFlow *flow, uint32_t node, uint32_t parent) {
					if(parent == Maxu32) TS_LOGF(Message, "traverse: %s %u\n", flow->getNodeName(node).get(), node);
					else TS_LOGF(Message, "traverse: %s %u %s %u\n", flow->getNodeName(node).get(), node, flow->getNodeName(parent).get(), parent);
				});
				flow.itraverseNodes(7, [](ControlFlow *flow, uint32_t node, uint32_t parent) {
					if(parent == Maxu32) TS_LOGF(Message, "itraverse: %s %u\n", flow->getNodeName(node).get(), node);
					else TS_LOGF(Message, "itraverse: %s %u %s %u\n", flow->getNodeName(node).get(), node, flow->getNodeName(parent).get(), parent);
				});
				flow.save("test_save-.flow");
			}
		}
	#endif
		
	// create target
	Target target = device.createTarget(window);
	target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	// controls time
	uint64_t update_time = 0;
	uint64_t create_time = 0;
	uint64_t draw_time = 0;
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) {
			String update = String::fromTime(update_time);
			String create = String::fromTime(create_time);
			String draw = String::fromTime(draw_time);
			window.setTitle(String::format("%s %.1f FPS %s %s %s", title.get(), fps, update.get(), create.get(), draw.get()));
		}
		
		// resize panel
		float32_t size = root.getPanelRadius() * 2.0f;
		panel.setSize(window.getWidth() - size, window.getHeight() - size);
		
		// load/save flow
		#if !_EMSCRIPTEN
			if(window.getKeyboardKey('l', true)) { flow.clearNodes(); flow.load("test_save.flow"); }
			if(window.getKeyboardKey('s', true)) { flow.save("test_save.flow"); }
		#endif
		
		// unredo action
		if(window.getKeyboardKey('z', true) && window.getKeyboardKey(Window::KeyOption)) {
			if(window.getKeyboardKey(Window::KeyShift)) flow.redo();
			else flow.undo();
		}
		if(window.getKeyboardKey('y', true) && window.getKeyboardKey(Window::KeyOption)) {
			flow.redo();
		}
		
		// inverse traversal
		if(flow.isChanged()) {
			for(uint32_t node : flow.findNodes("led")) {
				flow.itraverseNodes(node);
			}
		}
		
		// update controls
		uint64_t begin = Time::current();
		update_controls(window, root, 0);
		update_time = Time::current() - begin;
		
		// create canvas
		begin = Time::current();
		canvas.create(device, target);
		create_time = Time::current() - begin;
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// draw canvas
			begin = Time::current();
			canvas.draw(command, target);
			draw_time = Time::current() - begin;
		}
		target.end();
		
		if(!window.present()) return false;
		
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}

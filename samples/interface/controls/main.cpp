// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <common/sample_controls.h>
#include <format/TellusimXml.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimCommand.h>
#include <interface/TellusimCanvas.h>
#include <interface/TellusimControls.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	if(!window) return 1;
	
	// create window
	String title = String::format("%s Tellusim::Controls", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create canvas
	Canvas canvas;
	
	// create root control
	ControlRoot root(canvas, true);
	
	// mouse callbacks
	window.setMouseRotatedCallback([&](Window::Axis axis, float32_t value) {
		root.setMouseAxis(translate_axis(axis), value);
	});
	
	// keyboard callbacks
	window.setKeyboardPressedCallback([&](uint32_t key, uint32_t code) {
		if(root) root.setKeyboardKey(translate_key(key, true), code, true);
		if(key == Window::KeyEsc) window.stop();
	});
	window.setKeyboardReleasedCallback([&](uint32_t key) {
		if(root) root.setKeyboardKey(translate_key(key, false), 0, false);
	});
	
	// create tables
	ControlGrid table_left(&root, 4);
	table_left.setAlign(Control::AlignLeftTop);
	table_left.setMargin(96.0f, 0.0f, 0.0f, 64.0f);
	for(uint32_t i = 0, j = 0; i < 16; i++) {
		ControlGrid table(&table_left, 4);
		table.setAlign(Control::AlignCenter);
		table.setMargin(2.0f);
		for(uint32_t k = 0; k < 16; k++) {
			ControlText text(&table, String::format("%u", j++));
			text.setAlign(Control::AlignCenter);
			text.setFontSize(12);
			text.setMargin(2.0f);
		}
	}
	
	ControlGrid table_right(&root, 8, 4.0f, 4.0f);
	table_right.setAlign(Control::AlignRightTop);
	table_right.setMargin(0.0f, 96.0f, 0.0f, 64.0f);
	for(uint32_t i = 0; i < 64; i++) {
		ControlButton button(&table_right, String::format("%u", i));
		button.setAlign(Control::AlignCenter);
		button.setSize(24.0f, 0.0f);
	}
	
	// create left area
	ControlArea left_area(&root);
	left_area.setAbsolute(true);
	left_area.setScalable(true);
	left_area.setHorizontalEnabled(true, true);
	left_area.setVerticalEnabled(true, true);
	left_area.setAlign(Control::AlignLeftBottom);
	left_area.setMargin(96.0f, 0.0f, 64.0f, 0.0f);
	left_area.setSize(384.0f, 256.0f);
	
	// create left rect texture
	constexpr uint32_t rect_size = 1024;
	Image rect_image(Image::Type2D, FormatRGBAu8n, Tellusim::Size(rect_size, rect_size));
	ImageSampler rect_sampler(rect_image);
	for(uint32_t y = 0; y < rect_size; y++) {
		for(uint32_t x = 0; x < rect_size; x++) {
			uint32_t c = 0xaf - ((x & 0x7f) ^ (y & 0x7f));
			rect_sampler.set2D(x, y, ImageColor(c, c, c, 255u));
		}
	}
	Texture rect_texture = device.createTexture(rect_image);
	
	// create left rect
	ControlRect left_rect(&left_area);
	left_rect.setMode(CanvasElement::ModeTexture);
	left_area.setFrameAlign(Control::AlignCenter);
	left_rect.setTexture(rect_texture);
	
	// create right area
	ControlArea right_area(&root, false, true);
	right_area.setAlign(Control::AlignRightBottom);
	right_area.setMargin(0.0f, 96.0f, 64.0f, 0.0f);
	right_area.setSize(384.0f, 256.0f);
	right_area.setValue(0.0f, 1e8f);
	
	// create right tree texture
	constexpr uint32_t tree_size = 16;
	constexpr uint32_t tree_layout = 16;
	Image tree_image(Image::Type2D, FormatRGBAu8n, Tellusim::Size(tree_size, tree_size * tree_layout));
	ImageSampler tree_sampler(tree_image);
	for(uint32_t i = 0; i < tree_layout; i++) {
		uint32_t c = 255 - 255 * i / (tree_layout - 1);
		for(uint32_t y = 0; y < tree_size; y++) {
			for(uint32_t x = 0; x < tree_size; x++) {
				tree_sampler.set2D(x, tree_size * i + y, ImageColor(c, c, c, 255u));
			}
		}
	}
	Texture tree_texture = device.createTexture(tree_image);
	
	// create right tree
	ControlTree tree(&right_area);
	tree.setAlign(Control::AlignExpand);
	tree.setTexture(tree_texture, tree_layout);
	uint32_t root_item = tree.addItem("root");
	tree.addItems({ "first", "second", "third" }, root_item);
	tree.addItems({ "fifth" , "sixth" }, tree.addItem("fourth", root_item));
	tree.addItem("seveth", root_item);
	
	// create items
	constexpr uint32_t num_items = 256;
	for(uint32_t i = 0; i < num_items; i++) {
		float32_t k = (float32_t)i / (num_items - 1);
		uint32_t item = tree.addItem(String::format("item %u", i), root_item);
		tree.setItemColor(item, Color(0.5f + k * 0.5f, 1.0f - k * 0.5f, 1.0f, 1.0f));
		tree.setItemTexture(item, i % tree_layout);
		if((i & 0x0f) == 0) root_item = item;
	}
	
	tree.setChangedCallback([](ControlTree tree, uint32_t item) { TS_LOGF(Message, "Tree changed %u\n", item); });
	tree.setDraggedCallback([](ControlTree tree, uint32_t item) { TS_LOGF(Message, "Tree dragged %u\n", item); return tree.getItemText(item).begins("item"); });
	tree.setDroppedCallback([](ControlTree tree, uint32_t item) { TS_LOGF(Message, "Tree dropped %u\n", item); if(tree.getItemText(item).begins("item")) tree.addItemChildren(item, tree.getSelectedItems()); });
	tree.setClickedCallback([](ControlTree tree, uint32_t item) { TS_LOGF(Message, "Tree clicked %u\n", item); });
	tree.setClicked2Callback([](ControlTree tree, uint32_t item) { TS_LOGF(Message, "Tree clicked2 %u\n", item); tree.switchItemExpanded(item); });
	tree.setExpandedCallback([](ControlTree tree, uint32_t item) { TS_LOGF(Message, "Tree expanded %u\n", item); });
	
	// create controls
	ControlDialog dialog(&root, 1, 0.0f, 8.0f);
	dialog.setAlign(Control::AlignCenter);
	dialog.setSize(384.0f, 256.0f + 64.0f);
	
	ControlSplit split(&dialog, 1.0f);
	split.setAlign(Control::AlignExpand);
	
	ControlGrid split_left(&split, 1, 0.0f, 8.0f);
	split_left.setAlign(Control::AlignExpand);
	
	Control split_right(&split);
	
	ControlGroup group(&split_left, "Color", 1, 0.0f, 8.0f);
	group.setClickedCallback([](ControlGroup group) { TS_LOGF(Message, "Group clicked %u\n", group.isExpanded()); });
	group.setStrokeStyle(StrokeStyle(2.0f, Color(0.3f, 0.5f)));
	group.setAlign(Control::AlignExpandX);
	group.setFoldable(true);
	
	ControlSlider rgba[4] = {
		ControlSlider(&group, "Red",	2, 0.25f, 0.0f, 1.0f),
		ControlSlider(&group, "Green",	2, 0.25f, 0.0f, 1.0f),
		ControlSlider(&group, "Blue",	2, 0.25f, 0.0f, 1.0f),
		ControlSlider(&group, "Alpha",	2, 1.00f, 0.0f, 1.0f),
	};
	rgba[0].setFormat("%.2f");
	rgba[1].setFormat("%.2f");
	rgba[2].setFormat("%.2f");
	rgba[3].setFormat("%.2f");
	rgba[0].setFontColor(Color(1.0f, 0.2f, 0.2f, 1.0f));
	rgba[1].setFontColor(Color(0.2f, 1.0f, 0.2f, 1.0f));
	rgba[2].setFontColor(Color(0.2f, 0.2f, 1.0f, 1.0f));
	rgba[3].setFontColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
	rgba[0].setFontAlign(Control::AlignLeft);
	rgba[1].setFontAlign(Control::AlignCenter);
	rgba[2].setFontAlign(Control::AlignRight);
	rgba[3].setFontAlign(Control::AlignLeft);
	rgba[0].getFontStyle().size += 0;
	rgba[1].getFontStyle().size += 4;
	rgba[2].getFontStyle().size += 8;
	rgba[3].getFontStyle().size += 0;
	for(uint32_t i = 0; i < 4; i++) {
		rgba[i].setClickedCallback([](ControlSlider slider) { TS_LOGF(Message, "Slider clicked %f\n", slider.getValue()); });
		rgba[i].setChangedCallback([](ControlSlider slider) { TS_LOGF(Message, "Slider changed %f\n", slider.getValue()); });
		rgba[i].setAlign(Control::AlignExpandX);
	}
	
	ControlButton button(&split_left, "Reset");
	button.setClickedCallback([&](ControlButton button) { rgba[0].setValue(0.25f); rgba[1].setValue(0.25f); rgba[2].setValue(0.25f); rgba[3].setValue(1.0f); TS_LOG(Message, "Button clicked\n"); });
	button.setAlign(Control::AlignExpandX);
	
	ControlGrid edit_grid(&split_left, 3, 4.0f, 0.0f);
	edit_grid.setAlign(Control::AlignExpandX);
	
	ControlEdit edit(&edit_grid, "ControlEdit");
	edit.setChangedCallback([&](ControlEdit edit) { TS_LOGF(Message, "Edit changed \"%s\" %u %u\n", edit.getText().get(), edit.getCurrentIndex(), edit.getSelectionIndex()); });
	edit.setClickedCallback([&](ControlEdit edit) { TS_LOGF(Message, "Edit clicked \"%s\" %u %u\n", edit.getText().get(), edit.getCurrentIndex(), edit.getSelectionIndex()); });
	edit.setReturnedCallback([&](ControlEdit edit) { TS_LOGF(Message, "Edit returned \"%s\" %u %u\n", edit.getText().get(), edit.getCurrentIndex(), edit.getSelectionIndex()); });
	edit.setAlign(Control::AlignExpandX);
	
	ControlCombo edit_mode(&edit_grid, { "Text", "Pwd", "Float", "SInt", "UInt", "Hex" });
	edit_mode.setChangedCallback([&](ControlCombo combo) { edit.setEditMode((ControlEdit::EditMode)combo.getCurrentIndex()); });
	edit_mode.setAlign(Control::AlignRight | Control::AlignCenterY);
	
	ControlCombo edit_align(&edit_grid, { "Left", "Center", "Right" });
	edit_align.setChangedCallback([&](ControlCombo combo) { Control::Align aligngs[] = { Control::AlignLeft, Control::AlignCenterX, Control::AlignRight }; edit.setFontAlign(aligngs[combo.getCurrentIndex()]); });
	edit_align.setAlign(Control::AlignRight | Control::AlignCenterY);
	
	ControlScroll scroll(&split_left, (16.0f - 4.0f) / 2.0f, 4.0f, 16.0f);
	scroll.setClickedCallback([&](ControlScroll scroll) { TS_LOGF(Message, "Scroll clicked %f\n", scroll.getValue()); edit.setSelection(true); });
	scroll.setChangedCallback([&](ControlScroll scroll) { TS_LOGF(Message, "Scroll changed %f\n", scroll.getValue()); edit.setText(String::fromf64(scroll.getValue(), 2).get()); });
	scroll.setAlign(Control::AlignExpandX);
	scroll.getFontStyle().size += 2;
	scroll.setStep(0.1f);
	
	ControlGrid grid(&split_left, 3, 4.0f, 8.0f);
	grid.setAlign(Control::AlignBottom | Control::AlignExpand);
	
	ControlCheck check(&grid, "Check");
	check.setClickedCallback([](ControlCheck check) { TS_LOGF(Message, "Check clicked %u\n", check.isChecked()); });
	check.setAlign(Control::AlignBottom | Control::AlignCenterX | Control::AlignExpand);
	check.getFontStyle().size += 8;
	
	check = ControlCheck(&grid, "Check", true);
	check.setClickedCallback([](ControlCheck check) { TS_LOGF(Message, "Check clicked %u\n", check.isChecked()); });
	check.setAlign(Control::AlignCenterX | Control::AlignExpandX);
	check.getFontStyle().size += 8;
	
	check = ControlCheck(&grid, "Check");
	check.setClickedCallback([](ControlCheck check) { TS_LOGF(Message, "Check clicked %u\n", check.isChecked()); });
	check.setAlign(Control::AlignCenterX | Control::AlignExpandX);
	check.setFontAlign(Control::AlignLeft);
	
	ControlCombo combo(&grid, { "Combo", "First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth" });
	combo.setChangedCallback([](ControlCombo combo) { TS_LOGF(Message, "Combo changed %u\n", combo.getCurrentIndex()); });
	combo.setAlign(Control::AlignCenterX | Control::AlignExpandX);
	combo.getFontStyle().size += 2;
	
	combo = ControlCombo(&grid, { "Combo", "First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth" }, 3);
	combo.setChangedCallback([](ControlCombo combo) { TS_LOGF(Message, "Combo changed %u\n", combo.getCurrentIndex()); });
	combo.setAlign(Control::AlignCenterX | Control::AlignExpandX);
	combo.getFontStyle().size += 2;
	
	combo = ControlCombo(&grid, { "Combo", "First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth" });
	combo.setChangedCallback([](ControlCombo combo) { TS_LOGF(Message, "Combo changed %u\n", combo.getCurrentIndex()); });
	combo.setAlign(Control::AlignCenterX | Control::AlignExpandX);
	combo.setFontAlign(Control::AlignRight);
	
	button = ControlButton(&dialog, "Modal");
	button.setSize(96.0f, 24.0f);
	button.setButtonRadius(12.0f);
	button.setStrokeStyle(StrokeStyle(2.0f, Color(0.5f, 1.0f)));
	button.setAlign(Control::AlignCenterX);
	button.setClickedCallback([&](ControlButton button) {
		
		ControlDialog dialog(&root, 1, 16.0f, 16.0f);
		dialog.setPosition(root.getMouseX() - canvas.getWidth() * 0.5f, root.getMouseY() - canvas.getHeight() * 0.5f);
		dialog.setStrokeStyle(StrokeStyle(2.0f, Color(0.5f, 1.0f)));
		dialog.setAlign(Control::AlignCenter);
		dialog.setResizable(false);
		
		ControlText text(&dialog, "Modal Dialog");
		text.setAlign(Control::AlignCenterX);
		text.setFontSize(24);
		
		ControlButton close_button(&dialog, "Close");
		close_button.setAlign(Control::AlignCenterX);
		close_button.setStrokeStyle(StrokeStyle(2.0f, Color(0.5f, 1.0f)));
		close_button.setButtonRadius(12.0f);
		close_button.setSize(96.0f, 24.0f);
		close_button.setFontSize(24);
		
		root.setModalControl(dialog);
		
		// run main loop
		while(!close_button.isClicked()) {
			Window::MainLoopCallback main_loop = window.getMainLoopCallback();
			if(main_loop) main_loop();
			else break;
		}
		
		TS_LOG(Message, "Modal Done\n");
		
		root.removeChild(dialog);
	});
	button.setFontSize(24);
	
	// create buttons
	ControlButton buttons[] = {
		ControlButton(&root, "LB"),
		ControlButton(&root, "RB"),
		ControlButton(&root, "LT"),
		ControlButton(&root, "RT"),
		ControlButton(&root, "LC"),
		ControlButton(&root, "RC"),
		ControlButton(&root, "CB"),
		ControlButton(&root, "CT"),
		ControlButton(&root, "CC"),
	};
	buttons[0].setAlign(Control::AlignLeftBottom);
	buttons[1].setAlign(Control::AlignRightBottom);
	buttons[2].setAlign(Control::AlignLeftTop);
	buttons[3].setAlign(Control::AlignRightTop);
	buttons[4].setAlign(Control::AlignLeft | Control::AlignCenterY);
	buttons[5].setAlign(Control::AlignRight | Control::AlignCenterY);
	buttons[6].setAlign(Control::AlignCenterX | Control::AlignBottom);
	buttons[7].setAlign(Control::AlignCenterX | Control::AlignTop);
	buttons[8].setAlign(Control::AlignCenterX | Control::AlignCenterY);
	buttons[0].setMargin(32.0f,  0.0f, 32.0f,  0.0f);
	buttons[1].setMargin( 0.0f, 32.0f, 32.0f,  0.0f);
	buttons[2].setMargin(32.0f,  0.0f,  0.0f, 32.0f);
	buttons[3].setMargin( 0.0f, 32.0f,  0.0f, 32.0f);
	buttons[4].setMargin(16.0f,  0.0f,  0.0f,  0.0f);
	buttons[5].setMargin( 0.0f, 16.0f,  0.0f,  0.0f);
	buttons[6].setMargin( 0.0f,  0.0f, 16.0f,  0.0f);
	buttons[7].setMargin( 0.0f,  0.0f,  0.0f, 16.0f);
	buttons[8].setPosition(0.0f, 256.0f);
	for(uint32_t i = 0; i < TS_COUNTOF(buttons); i++) {
		buttons[i].setClickedCallback([&](ControlButton button) { dialog.setPosition(Vector3f(0.0f)); dialog.setAlign(button.getAlign()); TS_LOGF(Message, "%s clicked\n", button.getText().get()); });
		buttons[i].setFontAlign(buttons[i].getAlign());
		buttons[i].setFontSize(24);
		buttons[i].setSize(40.0f, 40.0f);
	}
	
	// create target
	Target target = device.createTarget(window);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// update controls
		update_controls(window, root);
		
		// render must be after controls update
		if(!window.render()) return false;
		
		// create canvas
		canvas.create(device, target);
		canvas.setColor(Color(1.0f, 1.0f, 1.0f, rgba[3].getValuef32()));
		
		// window target
		target.setClearColor(rgba[0].getValuef32(), rgba[1].getValuef32(), rgba[2].getValuef32(), 1.0f);
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// draw canvas
			canvas.draw(command, target);
		}
		target.end();
		
		if(!window.present()) return false;
		
		if(!device.check()) return false;
		
		return true;
	});
	
	TS_LOG(Message, "Done\n");
	
	// finish context
	window.finish();
	
	return 0;
}

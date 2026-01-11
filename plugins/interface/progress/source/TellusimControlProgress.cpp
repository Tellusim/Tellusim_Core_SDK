// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimTime.h>

#include "../include/TellusimControlProgress.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	ControlProgress::ControlProgress(Control *parent) : ControlBase(parent) {
		
		// control align
		setAlign(AlignOverlap);
		
		// create control
		create();
	}
	
	ControlProgress::~ControlProgress() {
		
		// release self
		Control parent = getParent();
		if(parent) parent.removeChild(*this);
		
		// release controls
		parent = progress_panel.getParent();
		if(parent) parent.removeChild(progress_panel);
	}
	
	/*
	 */
	void ControlProgress::create() {
		
		// parent control
		Control parent = getParent();
		if(parent) parent = parent.getPanel();
		
		// main panel
		progress_panel = ControlPanel(&parent, 1, 0.0f, 12.0f);
		progress_panel.setAlign(AlignCenter | AlignOverlap);
		progress_panel.setColor(Color(0.12f, 1.0f));
		progress_panel.setCallback(true);
		
		// title text
		title_text = ControlText(&progress_panel);
		title_text.setAlign(AlignCenterX);
		title_text.setEnabled(false);
		title_text.setFontSize(24);
		
		// progress text
		progress_text = ControlText(&progress_panel);
		progress_text.setAlign(AlignCenterX);
		progress_text.setFontSize(24);
		
		// progress rect
		progress_rect = ControlRect(&progress_panel);
		progress_rect.setAlign(AlignLeft);
		progress_rect.setSize(0, 24.0f);
		progress_rect.setRadius(12.0f);
		
		// cancel button
		cancel_button = ControlButton(&progress_panel, "Cancel");
		cancel_button.setAlign(AlignRight);
		cancel_button.setSize(96.0f, 18.0f);
		cancel_button.setButtonRadius(8.0f);
		
		// cancel callback
		cancel_button.setClickedCallback([this](ControlButton button) {
			is_canceled = 1;
		});
		
		// default parameters
		setSize(384.0f, 0.0f);
		setRadius(24.0f);
		
		ControlBase::create();
	}
	
	/*
	 */
	void ControlProgress::setSize(float32_t width, float32_t height) {
		progress_panel.setSize(width, height);
	}
	
	void ControlProgress::setRadius(float32_t radius) {
		progress_panel.setRadius(radius);
		progress_panel.setMargin(radius);
	}
	
	void ControlProgress::setColor(const Color &color) {
		progress_panel.setColor(color);
	}
	
	/*
	 */
	bool ControlProgress::setFontSize(uint32_t size) {
		return progress_text.setFontSize(size);
	}
	
	bool ControlProgress::setFontStyle(const FontStyle &style) {
		return progress_text.setFontStyle(style);
	}
	
	/*
	 */
	void ControlProgress::setRectColor(const Color &color) {
		return progress_rect.setColor(color);
	}
	
	/*
	 */
	void ControlProgress::setButtonRadius(float32_t radius) {
		cancel_button.setButtonRadius(radius);
	}
	
	/*
	 */
	void ControlProgress::setTitle(const char *text) {
		title_text.setText(text);
	}
	
	void ControlProgress::setTitle(const String &text) {
		title_text.setText(text);
	}
	
	/*
	 */
	bool ControlProgress::setText(const char *text) {
		AtomicLock atomic(lock);
		current_text = text;
		bool ret = (is_canceled == 0);
		is_canceled = 0;
		return ret;
	}
	
	bool ControlProgress::setText(const String &text) {
		AtomicLock atomic(lock);
		current_text = text.get();
		bool ret = (is_canceled == 0);
		is_canceled = 0;
		return ret;
	}
	
	/*
	 */
	bool ControlProgress::setProgress(uint32_t progress) {
		AtomicLock atomic(lock);
		current_progress = progress;
		bool ret = (is_canceled == 0);
		is_canceled = 0;
		return ret;
	}
	
	/*
	 */
	void ControlProgress::setCanceled(bool canceled) {
		is_canceled = (canceled) ? 1 : 0;
	}
	
	bool ControlProgress::isCanceled() {
		return (is_canceled != 0);
	}
	
	/*
	 */
	void ControlProgress::update_enabled(bool enabled) {
		enabled &= isEnabled();
		if(progress_panel.isEnabled() != enabled) {
			progress_panel.setEnabled(enabled);
			setProgress(0);
		}
		ControlBase::update_enabled(enabled);
	}
	
	bool ControlProgress::update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale) {
		
		bool ret = false;
		
		AtomicLock atomic(lock);
		
		// progress title
		if(title_text.isEnabled() != progress_panel.isEnabled() && title_text.getText()) {
			title_text.setEnabled(progress_panel.isEnabled() && title_text.getText());
			ret = true;
		}
		
		// progress text
		if(progress_text.getText() != current_text) {
			progress_text.setText(current_text);
			ret = true;
		}
		
		// progress value
		float32_t width = floor(getWidth() * current_progress / 100.0f);
		progress_rect.setSize(width, progress_rect.getHeight());
		
		return ret;
	}
}

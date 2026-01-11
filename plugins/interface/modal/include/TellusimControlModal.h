// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_INTERFACE_CONTROL_MODAL_H__
#define __TELLUSIM_PLUGINS_INTERFACE_CONTROL_MODAL_H__

#include <interface/TellusimControls.h>

/*
 */
namespace Tellusim {
	
	/*
	 */
	class Window;
	
	/* ControlModal
	 */
	class ControlModal : public ControlBase {
			
		public:
			
			/// modal result
			enum Result {
				ResultYes = 0,
				ResultNo,
				ResultOk,
				ResultCancel,
				ResultClose,
				NumResults,
			};
			
			/// modal flags
			enum Flags {
				FlagNone = 0,
				FlagYes			= (1 << ResultYes),
				FlagNo			= (1 << ResultNo),
				FlagOk			= (1 << ResultOk),
				FlagCancel		= (1 << ResultCancel),
				FlagClose		= (1 << ResultClose),
				FlagYesNo		= (FlagYes | FlagNo),
				FlagOkCancel	= (FlagOk | FlagCancel),
				FlagContainer	= (1 << (NumResults + 0)),
				FlagResizable	= (1 << (NumResults + 1)),
				FlagMoveable	= (1 << (NumResults + 2)),
				FlagMouse		= (1 << (NumResults + 3)),
				DefaultFlags	= (FlagOk),
			};
			
			/// modal constructor
			explicit ControlModal(Control *parent, Flags flags = DefaultFlags);
			explicit ControlModal(Control *parent, const char *title, Flags flags = DefaultFlags);
			explicit ControlModal(Control *parent, const String &title, Flags flags = DefaultFlags);
			explicit ControlModal(Control *parent, uint32_t columns, const char *title, Flags flags = DefaultFlags);
			explicit ControlModal(Control *parent, uint32_t columns, const String &title, Flags flags = DefaultFlags);
			explicit ControlModal(Control *parent, const char *title, const char *message, Flags flags = DefaultFlags);
			explicit ControlModal(Control *parent, const char *title, const String &message, Flags flags = DefaultFlags);
			explicit ControlModal(Control *parent, const String &title, const String &message, Flags flags = DefaultFlags);
			explicit ControlModal(Control *parent, uint32_t columns, const char *title, const char *message, Flags flags = DefaultFlags);
			explicit ControlModal(Control *parent, uint32_t columns, const String &title, const String &message, Flags flags = DefaultFlags);
			virtual ~ControlModal();
			
			/// disable copying
			ControlModal(const ControlModal&) = delete;
			ControlModal &operator=(const ControlModal&) = delete;
			
			/// modal size
			void setSize(float32_t width, float32_t height);
			TS_INLINE float32_t getWidth() const { return modal_dialog.getWidth(); }
			TS_INLINE float32_t getHeight() const { return modal_dialog.getHeight(); }
			
			/// modal radius
			void setRadius(float32_t radius);
			TS_INLINE float32_t getRadius() const { return modal_dialog.getRadius(); }
			
			/// modal color
			void setColor(const Color &color);
			TS_INLINE const Color &getColor() const { return modal_dialog.getColor(); }
			
			/// modal stroke style
			void setStrokeStyle(const StrokeStyle &style);
			TS_INLINE const StrokeStyle &getStrokeStyle() const { return modal_dialog.getStrokeStyle(); }
			
			/// modal gradient style
			void setGradientStyle(const GradientStyle &style);
			TS_INLINE const GradientStyle &getGradientStyle() const { return modal_dialog.getGradientStyle(); }
			
			/// button radius
			void setButtonRadius(float32_t radius);
			TS_INLINE float32_t getButtonRadius() const { return button_radius; }
			
			/// modal title
			void setTitle(const char *text);
			void setTitle(const String &text);
			
			/// modal message
			void setMessage(const char *text);
			void setMessage(const String &text);
			
			/// run modal
			Result run(Window &window, bool disabled = true);
			
			/// modal controls
			TS_INLINE ControlDialog &getModalDialog() { return modal_dialog; }
			TS_INLINE ControlGrid &getModalGrid() { return modal_grid; }
			TS_INLINE ControlText &getTitleText() { return title_text; }
			TS_INLINE ControlButton &getCloseButton() { return buttons[ResultClose]; }
			TS_INLINE ControlButton &getCancelButton() { return buttons[ResultCancel]; }
			TS_INLINE ControlButton &getOkButton() { return buttons[ResultOk]; }
			TS_INLINE ControlButton &getNoButton() { return buttons[ResultNo]; }
			TS_INLINE ControlButton &getYesButton() { return buttons[ResultYes]; }
			
		private:
			
			/// create control
			void create(uint32_t columns, const char *title, const char *message, Flags flags);
			
			/// update control
			virtual void update_enabled(bool enabled);
			
			float32_t button_radius = 8.0f;		// button radius
			
			ControlDialog modal_dialog;			// modal dialog
			ControlGrid modal_grid;				// modal grid
			ControlText title_text;				// title text
			ControlText message_text;			// message text
			ControlButton buttons[NumResults];	// buttons
			
			Result ret_result = NumResults;		// ret result
			Result esc_result = NumResults;		// esc result
			
			Result result = NumResults;			// modal result
	};
	
	TS_DECLARE_ENUM_OP(ControlModal::Flags)
}

#endif /* __TELLUSIM_PLUGINS_INTERFACE_CONTROL_MODAL_H__ */

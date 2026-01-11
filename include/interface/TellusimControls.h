// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_INTERFACE_CONTROLS_H__
#define __TELLUSIM_INTERFACE_CONTROLS_H__

#include <interface/TellusimCanvas.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Window;
	class ControlRoot;
	class ControlPanel;
	
	/**
	 * The Control class is a base class for UI controls such as buttons, sliders, and panels, providing methods to define their type, state, and alignment.
	 * It supports flexible parent-child relationships, allowing for the addition, removal, and organization of controls in a hierarchical layout.
	 * The class also manages control size, position, margins, and offsets, with the ability to enable or disable controls based on user interaction.
	 * It handles various control states, such as focused, pressed, or disabled, and allows for querying and modifying these states.
	 * Additionally, it provides functionality for managing interaction events, such as mouse clicks and key presses, making it essential for creating dynamic and interactive UI elements.
	 */
	class TS_API Control {
			
			TS_DECLARE_PTR_0(Control, 0)
			
		public:
			
			/// Control types
			enum Type {
				TypeUnknown = 0,
				TypeRoot,
				TypeText,
				TypeRect,
				TypeGrid,
				TypeGroup,
				TypePanel,
				TypeDialog,
				TypeWindow,
				TypeCheck,
				TypeCombo,
				TypeButton,
				TypeSlider,
				TypeScroll,
				TypeSplit,
				TypeArea,
				TypeTree,
				TypeEdit,
				NumTypes,
			};
			
			/// Control states
			enum State {
				StateUnknown = 0,
				StateNormal,
				StateFocused,
				StatePressed,
				StateDisabled,
				NumStates,
			};
			
			/// Control meshes
			enum Mesh {
				MeshCheck = 0,
				MeshButton,
				MeshSliderLine,
				MeshHScrollLine,
				MeshVScrollLine,
				MeshSliderHandle,
				MeshHScrollHandle,
				MeshVScrollHandle,
				MeshBackground,
				MeshSelection,
				MeshBorder,
				MeshFrame,
				NumMeshes,
			};
			
			/// Control alignments
			enum Align {
				AlignNone = 0,
				AlignLeft			= (1 << 0),
				AlignRight			= (1 << 1),
				AlignBottom			= (1 << 2),
				AlignTop			= (1 << 3),
				AlignCenterX		= (1 << 4),
				AlignCenterY		= (1 << 5),
				AlignExpandX		= (1 << 6),
				AlignExpandY		= (1 << 7),
				AlignOverlap		= (1 << 8),
				AlignSpacer			= (1 << 9),
				AlignAspect			= (1 << 10),
				AlignLocal			= (1 << 11),
				AlignLeftBottom		= (AlignLeft | AlignBottom),
				AlignLeftTop		= (AlignLeft | AlignTop),
				AlignRightBottom	= (AlignRight | AlignBottom),
				AlignRightTop		= (AlignRight | AlignTop),
				AlignCenter			= (AlignCenterX | AlignCenterY),
				AlignExpand			= (AlignExpandX | AlignExpandY),
				NumAligns = 12,
			};
			
			/// Control buttons
			enum Button {
				ButtonNone = 0,
				ButtonLeft		= (1 << 0),
				ButtonLeft2		= (1 << 1),
				ButtonRight		= (1 << 2),
				ButtonRight2	= (1 << 3),
				ButtonMiddle	= (1 << 4),
				ButtonMiddle2	= (1 << 5),
				NumButtons = 6,
			};
			
			/// Control axes
			enum Axis {
				AxisUnknown = 0,
				AxisX,
				AxisY,
				AxisZ,
				AxisW,
				NumAxes,
			};
			
			/// Control keys
			enum Key {
				KeyNone = 128,
				KeyTab,
				KeyBackspace,
				KeyDelete,
				KeyInsert,
				KeyReturn,
				KeyPrior,
				KeyNext,
				KeyEnd,
				KeyHome,
				KeyUp,
				KeyDown,
				KeyLeft,
				KeyRight,
				KeyShift,
				KeyCtrl,
				KeyAlt,
				KeyCmd,
				NumKeys,
				#if _MACOS
					KeyOption = KeyCmd,
				#else
					KeyOption = KeyCtrl,
				#endif
			};
			
			Control();
			explicit Control(Control *parent);
			Control(Control *parent, float32_t width, float32_t height = 0.0f);
			
			/// check controls
			static uint32_t getNumControls();
			static bool isControl(const Control &control);
			
			/// control type
			Type getType() const;
			
			static const char *getTypeName(Type type);
			const char *getTypeName() const;
			
			TS_INLINE bool isUnknown() const { return (getType() == TypeUnknown); }
			TS_INLINE bool isRoot() const { return (getType() == TypeRoot); }
			TS_INLINE bool isText() const { return (getType() == TypeText); }
			TS_INLINE bool isRect() const { return (getType() == TypeRect); }
			TS_INLINE bool isGrid() const { return (getType() == TypeGrid); }
			TS_INLINE bool isGroup() const { return (getType() == TypeGroup); }
			TS_INLINE bool isPanel() const { return (getType() == TypePanel); }
			TS_INLINE bool isDialog() const { return (getType() == TypeDialog); }
			TS_INLINE bool isWindow() const { return (getType() == TypeWindow); }
			TS_INLINE bool isCheck() const { return (getType() == TypeCheck); }
			TS_INLINE bool isCombo() const { return (getType() == TypeCombo); }
			TS_INLINE bool isButton() const { return (getType() == TypeButton); }
			TS_INLINE bool isSlider() const { return (getType() == TypeSlider); }
			TS_INLINE bool isScroll() const { return (getType() == TypeScroll); }
			TS_INLINE bool isSplit() const { return (getType() == TypeSplit); }
			TS_INLINE bool isArea() const { return (getType() == TypeArea); }
			TS_INLINE bool isTree() const { return (getType() == TypeTree); }
			TS_INLINE bool isEdit() const { return (getType() == TypeEdit); }
			
			/// control alignment
			void setAlign(Align align);
			Align getAlign() const;
			
			TS_INLINE bool hasAlign(Align align) const { return ((getAlign() & align) != AlignNone); }
			TS_INLINE bool hasAligns(Align aligns) const { return ((getAlign() & aligns) == aligns); }
			
			TS_INLINE bool isSpacer() const { return (isUnknown() && hasAlign(AlignSpacer)); }
			
			/// control created
			void setCreated(bool created);
			bool isCreated() const;
			
			/// control enabled flag
			void setEnabled(bool enabled);
			bool isEnabled() const;
			bool wasEnabled() const;
			bool wasUpdated() const;
			
			/// control disabled flag
			void setDisabled(bool disabled);
			bool isDisabled() const;
			
			/// control canvas
			Canvas getCanvas() const;
			
			/// control root
			const ControlRoot getRoot(bool local = false) const;
			ControlRoot getRoot(bool local = false);
			
			/// control panel
			const ControlPanel getPanel() const;
			ControlPanel getPanel();
			
			/// control parent
			uint32_t setParent(Control &parent);
			const Control getParent() const;
			Control getParent();
			
			bool isParentEnabled() const;
			bool isParentDisabled() const;
			
			/// control children
			uint32_t addChild(Control &child);
			Control setChild(uint32_t index, Control &child);
			bool raiseChild(Control &child, uint32_t index = 0);
			bool lowerChild(Control &child, uint32_t index = 0);
			bool removeChild(Control &child);
			void releaseChildren();
			
			uint32_t findChild(const Control &child) const;
			bool isChild(const Control &child, bool hierarchy = false) const;
			
			uint32_t getNumChildren() const;
			const Array<Control> getChildren() const;
			Array<Control> getChildren();
			const Control getChild(uint32_t index) const;
			Control getChild(uint32_t index);
			
			/// control size
			void setSize(const Vector2f &size);
			void setSize(float32_t width, float32_t height);
			const Vector2f &getSize() const;
			float32_t getWidth() const;
			float32_t getHeight() const;
			
			/// control position
			void setPosition(const Vector3f &position);
			void setPosition(float32_t x, float32_t y, float32_t z = 0.0f);
			const Vector3f &getPosition() const;
			float32_t getPositionX() const;
			float32_t getPositionY() const;
			
			/// control offset
			void setOffset(const Vector3f &offset);
			void setOffset(float32_t x, float32_t y, float32_t z = 0.0f);
			const Vector3f &getOffset() const;
			float32_t getOffsetX() const;
			float32_t getOffsetY() const;
			
			/// control margin
			void setMargin(float32_t value);
			void setMargin(float32_t horizontal, float32_t vertical);
			void setMargin(float32_t left, float32_t right, float32_t bottom, float32_t top);
			void setMargin(const Rect &margin);
			
			const Rect &getMargin() const;
			
			/// control rectangle
			const Rect &getRect() const;
			
			/// control state
			State getState() const;
	};
	
	/**
	 * The ControlRoot class extends the Control class and manages the root of a UI hierarchy, providing functions for setting viewport dimensions, font, texture, and mesh properties.
	 * It allows control over text color and offsets, as well as panel and group properties like radius and color.
	 * The class supports advanced input handling, including mouse position and button tracking, keyboard key events, and control focus management.
	 * It offers functionalities for managing the current, focused, modal, and mouse-controlled elements in the UI.
	 * Additionally, it includes copy and paste functionality, with user-defined callback functions for these operations.
	 */
	class TS_API ControlRoot : public Control {
			
			TS_DECLARE_PTR_1(ControlRoot, Control, 0)
			
		public:
			
			ControlRoot();
			explicit ControlRoot(Canvas &canvas, bool blob = false);
			
			/// root viewport
			void setViewport(const Viewport &viewport);
			void setViewport(uint32_t width, uint32_t height);
			void setViewport(float32_t width, float32_t height);
			const Viewport &getViewport() const;
			
			/// font name
			String getFontName() const;
			void setFontName(const char *name);
			void setFontName(const String &name);
			bool setFontBlob(const uint8_t (*blob)[256], const char *name = nullptr);
			
			/// font style
			bool setFontSize(uint32_t size, bool update = false);
			uint32_t getFontSize() const;
			
			bool setFontScale(uint32_t scale, bool update = false);
			uint32_t getFontScale() const;
			
			bool setFontStyle(const FontStyle &style, bool update = false);
			const FontStyle &getFontStyle() const;
			FontStyle &getFontStyle();
			
			/// texture parameters
			String getTextureName() const;
			bool setTextureName(const char *name, uint32_t width = 0, uint32_t height = 0, float32_t border = 0.0f);
			bool setTextureName(const String &name, uint32_t width = 0, uint32_t height = 0, float32_t border = 0.0f);
			bool setTextureBlob(const uint8_t (*blob)[256], const char *name = nullptr, uint32_t width = 0, uint32_t height = 0, float32_t border = 0.0f);
			float32_t getTextureWidth() const;
			float32_t getTextureHeight() const;
			
			/// text parameters
			void setTextColor(Type type, State state, const Color &color);
			void setTextOffset(Type type, State state, const Vector3f &offset);
			const Color &getTextColor(Type type, State state) const;
			const Vector3f &getTextOffset(Type type, State state) const;
			
			/// mesh parameters
			void setMeshColor(Mesh mesh, State state, const Color &color);
			void setMeshRegion(Mesh mesh, const Rect &grid, const Rect &region, const Vector2f &border);
			void setMeshRegions(Mesh mesh, const Rect &grid, const Rect &regions, const Vector2f &border);
			uint32_t getMeshColor(Mesh mesh, State state) const;
			const Rect &getMeshGrid(Mesh mesh) const;
			const Rect &getMeshMargin(Mesh mesh) const;
			const Rect &getMeshRegion(Mesh mesh, State state) const;
			
			/// panel parameters
			void setGroupRadius(float32_t radius);
			void setGroupColor(const Color &color);
			float32_t getGroupRadius() const;
			const Color &getGroupColor() const;
			
			/// panel parameters
			void setPanelRadius(float32_t radius);
			void setPanelColor(const Color &color);
			float32_t getPanelRadius() const;
			const Color &getPanelColor() const;
			
			/// check parameters
			void setCheckedColor(const Color &color);
			const Color &getCheckedColor() const;
			
			/// split parameters
			void setSplitSize(float32_t size);
			float32_t getSplitSize() const;
			
			/// mouse button
			void setMousePosition(const Vector2f &position);
			void setMouse(int32_t x, int32_t y, Button buttons);
			void setMouse(float32_t x, float32_t y, Button buttons);
			const Vector2f &getMouse() const;
			Button getMouseButtons() const;
			float32_t getMouseX() const;
			float32_t getMouseY() const;
			
			/// mouse offset
			void setMouseOffset(const Vector2f &offset);
			const Vector2f &getMouseOffset() const;
			
			/// mouse axes
			void setMouseAxis(Axis axis, float32_t delta);
			
			/// mouse alignment
			void setMouseAlign(Align align, bool clear = true);
			Align getMouseAlign() const;
			
			TS_INLINE bool hasMouseAlign(Align align) const { return ((getMouseAlign() & align) != AlignNone); }
			TS_INLINE bool hasMouseAligns(Align aligns) const { return ((getMouseAlign() & aligns) == aligns); }
			
			/// keyboard keys
			bool setKeyboardKey(uint32_t key, uint32_t code, bool value);
			bool getKeyboardKey(uint32_t key, bool clear = false);
			
			/// current control
			void clearCurrentControl();
			void setCurrentControl(Control control, bool grab = false);
			Control getCurrentControl() const;
			bool isCurrentControl() const;
			bool getControlGrab() const;
			
			/// focused control
			void clearFocusedControl();
			void setFocusedControl(Control control);
			Control getFocusedControl() const;
			bool isFocusedControl() const;
			
			/// mouse control
			void clearMouseControl();
			void setMouseControl(Control control);
			Control getMouseControl() const;
			bool isMouseControl() const;
			
			/// input control
			void clearInputControl();
			void setInputControl(Control control);
			Control getInputControl() const;
			bool isInputControl() const;
			
			/// modal control
			void clearModalControl();
			void setModalControl(Control control, bool disabled = true);
			Control getModalControl() const;
			bool isModalDisabled() const;
			bool isModalControl() const;
			
			/// overlay order
			void setOverlayOrder(int32_t order);
			int32_t getOverlayOrder() const;
			
			/// update controls
			bool update(uint32_t scale = 0, int32_t order = 0);
			
			/// copy/paste buffer
			void setCopyText(const char *text);
			void setCopyText(const String &text);
			String getPasteText();
			
			/// copy callback
			using CopyCallback = Function<void(ControlRoot, const char *text)>;
			void setCopyCallback(const CopyCallback &func);
			CopyCallback getCopyCallback() const;
			
			/// paste callback
			using PasteCallback = Function<String(ControlRoot)>;
			void setPasteCallback(const PasteCallback &func);
			PasteCallback getPasteCallback() const;
	};
	
	/**
	 * The ControlText class extends the Control class and is responsible for managing text-based UI elements.
	 * It provides methods for setting and retrieving text, font properties such as size, style, color, and alignment, as well as control color and blending settings.
	 * The class allows for configuring control mode, pipeline settings, and filtering, including anisotropy and blending operations.
	 * Through its integration with canvas elements, the ControlText class enables precise control over the rendering of text and related visual attributes in the UI.
	 */
	class TS_API ControlText : public Control {
			
			TS_DECLARE_PTR_1(ControlText, Control, 0)
			
		public:
			
			ControlText();
			explicit ControlText(Control *parent);
			ControlText(Control *parent, const char *text);
			ControlText(Control *parent, const String &text);
			
			/// callback flag
			void setCallback(bool callback);
			bool getCallback() const;
			
			/// control mode
			void setMode(CanvasElement::Mode mode);
			CanvasElement::Mode getMode() const;
			
			/// control pipeline
			void setPipeline(Pipeline &pipeline);
			void setPipeline(Pipeline &pipeline, const CanvasElement::DrawCallback &func);
			Pipeline getPipeline() const;
			
			/// control color
			void setColor(const Color &color);
			void setColor(float32_t r, float32_t g, float32_t b, float32_t a);
			const Color &getColor() const;
			
			/// filter mode
			void setFilter(Sampler::Filter filter);
			Sampler::Filter getFilter() const;
			
			void setAnisotropy(uint32_t anisotropy);
			uint32_t getAnisotropy() const;
			
			/// blending parameters
			void setBlend(Pipeline::BlendOp op, Pipeline::BlendFunc src, Pipeline::BlendFunc dest);
			Pipeline::BlendOp getBlendOp() const;
			Pipeline::BlendFunc getBlendSrcFunc() const;
			Pipeline::BlendFunc getBlendDestFunc() const;
			
			/// font name
			void setFontName(const char *name);
			void setFontName(const String &name);
			String getFontName() const;
			
			/// font color
			void setFontColor(const Color &color);
			const Color &getFontColor() const;
			
			/// font style
			bool setFontSize(uint32_t size);
			uint32_t getFontSize() const;
			
			bool setFontStyle(const FontStyle &style);
			const FontStyle &getFontStyleConst() const;
			const FontStyle &getFontStyle() const;
			FontStyle &getFontStyle();
			
			/// font alignment
			void setFontAlign(Align align);
			Align getFontAlign() const;
			
			TS_INLINE bool hasFontAlign(Align align) const { return ((getFontAlign() & align) != AlignNone); }
			TS_INLINE bool hasFontAligns(Align aligns) const { return ((getFontAlign() & aligns) == aligns); }
			
			/// control text
			void setText(const char *text);
			void setText(const String &text);
			String getText() const;
			
			/// canvas elements
			CanvasText getCanvasText();
	};
	
	/**
	 * The ControlRect class extends the Control class and is designed for managing rectangular UI elements with customizable properties such as color, texture, stroke style, and gradients.
	 * It provides methods for setting control modes, pipelines, filters, and wrapping modes, as well as controlling mipmaps and anisotropy for texture handling.
	 * The class supports texture properties like scale, flip, and projection, and allows for defining texture coordinates and names.
	 * Additionally, it includes various callbacks for interaction handling, such as inside, pressed, released, and clicked events, along with support for fullscreen mode, radius, and blending parameters.
	 * The ControlRect class also integrates with canvas elements, enabling the rendering of rectangular shapes and meshes with flexible visual configurations.
	 */
	class TS_API ControlRect : public Control {
			
			TS_DECLARE_PTR_1(ControlRect, Control, 0)
			
		public:
			
			ControlRect();
			explicit ControlRect(Control *parent);
			ControlRect(Control *parent, Texture &texture);
			ControlRect(Control *parent, const char *name);
			ControlRect(Control *parent, CanvasElement::Mode mode);
			
			/// callback flag
			void setCallback(bool callback);
			bool getCallback() const;
			
			/// fullscreen flag
			void setFullscreen(bool fullscreen);
			bool isFullscreen() const;
			
			/// control mode
			void setMode(CanvasElement::Mode mode);
			CanvasElement::Mode getMode() const;
			
			/// control pipeline
			void setPipeline(Pipeline &pipeline);
			void setPipeline(Pipeline &pipeline, const CanvasElement::DrawCallback &func);
			Pipeline getPipeline() const;
			
			/// control radius
			void setRadius(float32_t radius);
			float32_t getRadius() const;
			
			/// control color
			void setColor(const Color &color);
			void setColor(float32_t r, float32_t g, float32_t b, float32_t a);
			const Color &getColor() const;
			
			/// stroke style
			void setStrokeStyle(const StrokeStyle &style);
			const StrokeStyle &getStrokeStyleConst() const;
			const StrokeStyle &getStrokeStyle() const;
			StrokeStyle &getStrokeStyle();
			
			/// gradient style
			void setGradientStyle(const GradientStyle &style);
			const GradientStyle &getGradientStyleConst() const;
			const GradientStyle &getGradientStyle() const;
			GradientStyle &getGradientStyle();
			
			/// control mipmap
			void setMipmap(float32_t mipmap);
			float32_t getMipmap() const;
			
			/// filter mode
			void setFilter(Sampler::Filter filter);
			Sampler::Filter getFilter() const;
			
			void setAnisotropy(uint32_t anisotropy);
			uint32_t getAnisotropy() const;
			
			/// wrapping mode
			void setWrapMode(Sampler::WrapMode mode);
			Sampler::WrapMode getWrapMode() const;
			
			/// blending parameters
			void setBlend(Pipeline::BlendOp op, Pipeline::BlendFunc src, Pipeline::BlendFunc dest);
			Pipeline::BlendOp getBlendOp() const;
			Pipeline::BlendFunc getBlendSrcFunc() const;
			Pipeline::BlendFunc getBlendDestFunc() const;
			
			/// texture pointer
			void setTexture(Texture &texture, bool linear = false);
			Texture getTexture() const;
			bool getTextureLinear() const;
			
			/// texture name
			void setTextureName(const char *name);
			void setTextureName(const String &name);
			String getTextureName() const;
			
			/// texture scale
			void setTextureScale(float32_t scale_x, float32_t scale_y);
			float32_t getTextureScaleX() const;
			float32_t getTextureScaleY() const;
			
			/// texture orientation
			void setTextureFlip(bool flip_x, bool flip_y);
			bool getTextureFlipX() const;
			bool getTextureFlipY() const;
			
			/// texture projection
			void setTextureProj(bool projection);
			bool getTextureProj() const;
			
			/// texture coordinates
			void setTexCoord(const Rect &texcoord);
			void setTexCoord(float32_t left, float32_t right, float32_t bottom, float32_t top);
			const Rect &getTexCoord() const;
			
			/// inside callback
			using InsideCallback = Function<bool(ControlRect, float32_t x, float32_t y)>;
			void setInsideCallback(const InsideCallback &func);
			InsideCallback getInsideCallback() const;
			
			/// pressed callback
			using PressedCallback = Function<void(ControlRect, float32_t x, float32_t y)>;
			void setPressedCallback(const PressedCallback &func);
			PressedCallback getPressedCallback() const;
			
			/// released callback
			using ReleasedCallback = Function<void(ControlRect, float32_t x, float32_t y)>;
			void setReleasedCallback(const ReleasedCallback &func);
			ReleasedCallback getReleasedCallback() const;
			
			/// clicked callback
			using ClickedCallback = Function<void(ControlRect)>;
			void setClickedCallback(const ClickedCallback &func);
			void setClicked2Callback(const ClickedCallback &func);
			void setClickedRightCallback(const ClickedCallback &func);
			ClickedCallback getClickedCallback() const;
			ClickedCallback getClicked2Callback() const;
			ClickedCallback getClickedRightCallback() const;
			
			/// canvas elements
			CanvasRect getCanvasRect();
			CanvasMesh getCanvasMesh();
	};
	
	/**
	 * The ControlGrid class is a layout control derived from Control that arranges child controls in a grid structure with configurable columns and spacing.
	 * It allows dynamic adjustment of the number of columns, spacing between items, and individual column width ratios to create flexible UI layouts.
	 * The class provides methods to retrieve the size occupied by all child controls, making it useful for auto-layout and responsive interface design.
	 */
	class TS_API ControlGrid : public Control {
			
			TS_DECLARE_PTR_1(ControlGrid, Control, 0)
			
		public:
			
			ControlGrid();
			explicit ControlGrid(Control *parent);
			ControlGrid(Control *parent, uint32_t columns);
			ControlGrid(Control *parent, uint32_t columns, float32_t x, float32_t y = 0.0f);
			
			/// number of columns
			void setColumns(uint32_t columns);
			uint32_t getColumns() const;
			
			/// grid spacing
			void setSpacing(const Vector2f &spacing);
			void setSpacing(float32_t x, float32_t y);
			const Vector2f &getSpacing() const;
			
			/// grid column ratio
			void setColumnRatio(uint32_t index, float32_t ratio);
			float32_t getColumnRatio(uint32_t index) const;
			
			/// controls size
			const Vector2f &getControlsSize() const;
	};
	
	/**
	 * The ControlGroup class is a composite UI control derived from ControlText that groups multiple controls together with a labeled header, optional folding behavior, and customizable styling.
	 * It supports layout features similar to a grid, including configurable columns, spacing, and per-column ratios.
	 * A ControlGroup can be rendered either above or below its children, optionally with a background and rounded borders.
	 */
	class TS_API ControlGroup : public ControlText {
			
			TS_DECLARE_PTR_2(ControlGroup, ControlText, Control, 0)
			
		public:
			
			ControlGroup();
			explicit ControlGroup(Control *parent, bool above = false);
			ControlGroup(Control *parent, const char *text, bool above = false);
			ControlGroup(Control *parent, const String &text, bool above = false);
			ControlGroup(Control *parent, const char *text, uint32_t columns, bool above = false);
			ControlGroup(Control *parent, const char *text, uint32_t columns, float32_t x, float32_t y, bool above = false);
			
			/// above flag
			void setAbove(bool above, bool text = true);
			bool isAbove() const;
			bool isBelow() const;
			
			/// foldable flag
			void setFoldable(bool foldable);
			bool isFoldable() const;
			
			/// expanded flag
			void setExpanded(bool expanded);
			bool isExpanded() const;
			
			/// background flag
			void setBackground(bool background);
			bool getBackground() const;
			
			/// group radius
			void setGroupRadius(float32_t radius);
			float32_t getGroupRadius() const;
			
			/// group color
			void setGroupColor(const Color &color);
			const Color &getGroupColor() const;
			
			/// stroke style
			void setStrokeStyle(const StrokeStyle &style);
			const StrokeStyle &getStrokeStyleConst() const;
			const StrokeStyle &getStrokeStyle() const;
			StrokeStyle &getStrokeStyle();
			
			/// gradient style
			void setGradientStyle(const GradientStyle &style);
			const GradientStyle &getGradientStyleConst() const;
			const GradientStyle &getGradientStyle() const;
			GradientStyle &getGradientStyle();
			
			/// folded text
			void setFoldedText(const char *text);
			void setFoldedText(const String &text);
			String getFoldedText() const;
			
			/// expanded text
			void setExpandedText(const char *text);
			void setExpandedText(const String &text);
			String getExpandedText() const;
			
			/// number of columns
			void setColumns(uint32_t columns);
			uint32_t getColumns() const;
			
			/// grid spacing
			void setSpacing(const Vector2f &spacing);
			void setSpacing(float32_t x, float32_t y);
			const Vector2f &getSpacing() const;
			
			/// grid column ratio
			void setColumnRatio(uint32_t index, float32_t ratio);
			float32_t getColumnRatio(uint32_t index) const;
			
			/// controls size
			const Vector2f &getControlsSize() const;
			
			/// clicked callback
			using ClickedCallback = Function<void(ControlGroup)>;
			void setClickedCallback(const ClickedCallback &func);
			ClickedCallback getClickedCallback() const;
			bool isClicked();
			
			/// canvas elements
			CanvasRect getCanvasRect();
	};
	
	/**
	 * The ControlPanel class is a container UI control derived from ControlRect that arranges child controls in a structured, grid-based layout.
	 * It allows customization of the number of columns, spacing between elements, and the relative width of each column using column ratios.
	 * As a rectangular control, it inherits visual styling options such as background color, radius, and texture support, making it suitable for organizing and grouping controls within a visually distinct section of a user interface.
	 */
	class TS_API ControlPanel : public ControlRect {
			
			TS_DECLARE_PTR_2(ControlPanel, ControlRect, Control, 0)
			
		public:
			
			ControlPanel();
			explicit ControlPanel(Control *parent);
			ControlPanel(Control *parent, uint32_t columns);
			ControlPanel(Control *parent, uint32_t columns, float32_t x, float32_t y);
			
			/// number of columns
			void setColumns(uint32_t columns);
			uint32_t getColumns() const;
			
			/// grid spacing
			void setSpacing(const Vector2f &spacing);
			void setSpacing(float32_t x, float32_t y);
			const Vector2f &getSpacing() const;
			
			/// grid column ratio
			void setColumnRatio(uint32_t index, float32_t ratio);
			float32_t getColumnRatio(uint32_t index) const;
			
			/// controls size
			const Vector2f &getControlsSize() const;
	};
	
	/**
	 * The ControlDialog class is a specialized UI container derived from ControlPanel, designed to represent movable and resizable dialog windows.
	 * It supports features like constraint within parent bounds, resizability with customizable resize area, and movability through mouse interaction.
	 * These capabilities make it ideal for creating flexible, interactive dialogs in a GUI environment, such as tool windows or popup panels.
	 */
	class TS_API ControlDialog : public ControlPanel {
			
			TS_DECLARE_PTR_3(ControlDialog, ControlPanel, ControlRect, Control, 0)
			
		public:
			
			ControlDialog();
			explicit ControlDialog(Control *parent);
			ControlDialog(Control *parent, uint32_t columns);
			ControlDialog(Control *parent, uint32_t columns, float32_t x, float32_t y);
			
			/// constrained flag
			void setConstrained(bool constrained);
			bool isConstrained() const;
			
			/// resizable flag
			void setResizable(bool resizable);
			bool isResizable() const;
			
			/// moveable flag
			void setMoveable(bool moveable);
			bool isMoveable() const;
			
			/// resize area
			void setResizeArea(float32_t area);
			float32_t getResizeArea() const;
			
			/// resize alignment
			Align getResizeAlign() const;
			
			TS_INLINE bool hasResizeAlign(Align align) const { return ((getResizeAlign() & align) != AlignNone); }
			TS_INLINE bool hasResizeAligns(Align aligns) const { return ((getResizeAlign() & aligns) == aligns); }
			
			/// mouse position
			void setMousePosition(const Vector2f &position);
			const Vector2f &getMousePosition() const;
			
			/// updated callback
			using UpdatedCallback = Function<void(ControlDialog)>;
			void setUpdatedCallback(const UpdatedCallback &func);
			UpdatedCallback getUpdatedCallback() const;
			bool isUpdated();
	};
	
	/**
	 * The ControlWindow class extends ControlDialog to integrate with native windowing, allowing UI controls to be embedded within or associated with system-level windows.
	 * Designed for complex UI applications, it combines dialog interaction features like resizing and movement with platform window management through a ControlRoot.
	 */
	class TS_API ControlWindow : public ControlDialog {
			
			TS_DECLARE_PTR_4(ControlWindow, ControlDialog, ControlPanel, ControlRect, Control, 0)
			
		public:
			
			ControlWindow();
			ControlWindow(ControlRoot *root, Window &parent, Window &window);
			ControlWindow(ControlRoot *root, Window &parent, Window &window, uint32_t columns);
			ControlWindow(ControlRoot *root, Window &parent, Window &window, uint32_t columns, float32_t x, float32_t y);
			
			/// control windows
			Window getParentWindow() const;
			Window getDialogWindow() const;
	};
	
	/**
	 * The ControlCheck class provides a UI control for a checkable text element, typically rendered as a checkbox with an associated label.
	 * It allows customization of check and checked colors, handles checked state toggling, and supports a ClickedCallback to respond to user interaction.
	 * It inherits from ControlText, enabling full styling and text layout capabilities, and uses CanvasMesh for rendering the checkbox graphic.
	 */
	class TS_API ControlCheck : public ControlText {
			
			TS_DECLARE_PTR_2(ControlCheck, ControlText, Control, 0)
			
		public:
			
			ControlCheck();
			explicit ControlCheck(Control *parent);
			ControlCheck(Control *parent, const char *text);
			ControlCheck(Control *parent, const String &text);
			ControlCheck(Control *parent, const char *text, bool checked);
			ControlCheck(Control *parent, const String &text, bool checked);
			
			/// check text
			void setCheckText(const char *text);
			void setCheckText(const String &text);
			String getCheckText() const;
			
			/// check color
			void setCheckColor(const Color &color);
			const Color &getCheckColor() const;
			
			/// checked color
			void setCheckedColor(const Color &color);
			const Color &getCheckedColor() const;
			
			/// checked state
			bool switchChecked(bool callback = false);
			void setChecked(bool checked, bool callback = false);
			bool isChecked() const;
			
			/// clicked callback
			using ClickedCallback = Function<void(ControlCheck)>;
			void setClickedCallback(const ClickedCallback &func);
			ClickedCallback getClickedCallback() const;
			bool isClicked();
			
			/// canvas elements
			CanvasMesh getCanvasMesh();
	};
	
	/**
	 * The ControlCombo class represents a combo box control that allows users to select from a list of items.
	 * It provides functionality to enable or disable text input, as well as enable multi-selection mode.
	 * The combo box text and color can be set and retrieved, and item spacing can be customized.
	 */
	class TS_API ControlCombo : public ControlText {
			
			TS_DECLARE_PTR_2(ControlCombo, ControlText, Control, 0)
			
		public:
			
			ControlCombo();
			explicit ControlCombo(Control *parent);
			ControlCombo(Control *parent, const InitializerList<const char*> &items);
			ControlCombo(Control *parent, const InitializerList<const char*> &items, uint32_t index);
			
			/// text enabled flag
			void setTextEnabled(bool enabled);
			bool isTextEnabled() const;
			
			/// multi-selection flag
			void setMultiSelection(bool multi_selection);
			bool isMultiSelection() const;
			
			/// combo text
			void setComboText(const char *text);
			void setComboText(const String &text);
			String getComboText() const;
			
			/// combo color
			void setComboColor(const Color &color);
			const Color &getComboColor() const;
			
			/// items spacing
			void setItemsSpacing(float32_t spacing);
			float32_t getItemsSpacing() const;
			
			/// combo items
			void clearItems();
			uint32_t addItem(const char *text);
			uint32_t addItem(const String &text);
			void addItem(uint32_t index, const char *text);
			void addItem(uint32_t index, const String &text);
			void addItems(const InitializerList<const char*> &items);
			void removeItem(uint32_t index);
			
			uint32_t getNumItems() const;
			
			/// item selected flag
			bool switchItemSelected(uint32_t index);
			void setItemSelected(uint32_t index, bool selected);
			bool isItemSelected(uint32_t index) const;
			
			/// item text
			void setItemText(uint32_t index, const char *text);
			void setItemText(uint32_t index, const String &text);
			String getItemText(uint32_t index) const;
			
			uint32_t findItemText(const char *text) const;
			uint32_t findItemText(const String &text) const;
			
			/// item color
			void setItemColor(uint32_t index, const Color &color);
			const Color &getItemColor(uint32_t index) const;
			
			/// current item
			void setCurrentIndex(uint32_t index, bool callback = false);
			bool setCurrentText(const char *text, bool callback = false);
			bool setCurrentText(const String &text, bool callback = false);
			uint32_t getCurrentIndex() const;
			String getCurrentText() const;
			
			/// clicked callback
			using ClickedCallback = Function<void(ControlCombo)>;
			void setClickedCallback(const ClickedCallback &func);
			ClickedCallback getClickedCallback() const;
			bool isClicked();
			
			/// changed callback
			using ChangedCallback = Function<void(ControlCombo)>;
			void setChangedCallback(const ChangedCallback &func);
			ChangedCallback getChangedCallback() const;
			bool isChanged();
			
			/// canvas elements
			CanvasMesh getCanvasMesh();
	};
	
	/**
	 * The ControlButton class represents a button control that can be customized with various visual properties such as background, radius, color, stroke style, and gradient style.
	 * The class allows for defining callbacks for button interactions, including when the button is pressed, released, or clicked, enabling responsive behavior based on user input.
	 */
	class TS_API ControlButton : public ControlText {
			
			TS_DECLARE_PTR_2(ControlButton, ControlText, Control, 0)
			
		public:
			
			ControlButton();
			explicit ControlButton(Control *parent);
			ControlButton(Control *parent, const char *text);
			ControlButton(Control *parent, const String &text);
			
			/// background flag
			void setBackground(bool background);
			bool getBackground() const;
			
			/// control mode
			void setButtonMode(CanvasElement::Mode mode);
			CanvasElement::Mode getButtonMode() const;
			
			/// button radius
			void setButtonRadius(float32_t radius);
			float32_t getButtonRadius() const;
			
			/// button color
			void setButtonColor(const Color &color);
			const Color &getButtonColor() const;
			
			/// stroke style
			void setStrokeStyle(const StrokeStyle &style);
			const StrokeStyle &getStrokeStyleConst() const;
			const StrokeStyle &getStrokeStyle() const;
			StrokeStyle &getStrokeStyle();
			
			/// gradient style
			void setGradientStyle(const GradientStyle &style);
			const GradientStyle &getGradientStyleConst() const;
			const GradientStyle &getGradientStyle() const;
			GradientStyle &getGradientStyle();
			
			/// pressed callback
			using PressedCallback = Function<void(ControlButton, float32_t x, float32_t y)>;
			void setPressedCallback(const PressedCallback &func);
			PressedCallback getPressedCallback() const;
			bool isPressed();
			
			/// released callback
			using ReleasedCallback = Function<void(ControlButton, float32_t x, float32_t y)>;
			void setReleasedCallback(const ReleasedCallback &func);
			ReleasedCallback getReleasedCallback() const;
			bool isReleased();
			
			/// clicked callback
			using ClickedCallback = Function<void(ControlButton)>;
			void setClickedCallback(const ClickedCallback &func);
			ClickedCallback getClickedCallback() const;
			bool isClicked();
			
			/// canvas elements
			CanvasRect getCanvasRect();
			CanvasMesh getCanvasMesh();
	};
	
	/**
	 * The ControlSlider class represents a slider control that allows the user to select a value within a specified range.
	 * It offers customization options such as setting the slider color, digits, step size, and base for exponential conversion.
	 * The class supports constraints, text enablement, and custom formatting for value display.
	 */
	class TS_API ControlSlider : public ControlText {
			
			TS_DECLARE_PTR_2(ControlSlider, ControlText, Control, 0)
			
		public:
			
			ControlSlider();
			explicit ControlSlider(Control *parent);
			ControlSlider(Control *parent, const char *text);
			ControlSlider(Control *parent, const String &text);
			ControlSlider(Control *parent, const char *text, uint32_t digits);
			ControlSlider(Control *parent, const char *text, uint32_t digits, float64_t value);
			ControlSlider(Control *parent, const char *text, uint32_t digits, float64_t value, float64_t min, float64_t max);
			ControlSlider(Control *parent, const char *text, float64_t value, float64_t min, float64_t max);
			ControlSlider(Control *parent, const char *text, uint32_t value, uint32_t min, uint32_t max);
			ControlSlider(Control *parent, const char *text, int32_t value, int32_t min, int32_t max);
			
			/// constrained flag
			void setConstrained(bool constrained);
			bool isConstrained() const;
			
			/// text enabled flag
			void setTextEnabled(bool enabled);
			bool isTextEnabled() const;
			
			/// slider color
			void setSliderColor(const Color &color);
			const Color &getSliderColor() const;
			
			/// slider digits
			void setDigits(uint32_t digits);
			uint32_t getDigits() const;
			
			/// slider step
			void setStep(float64_t step);
			float64_t getStep() const;
			
			/// exponent base
			void setBase(float64_t base);
			float64_t getBase() const;
			
			/// slider format
			void setFormat(const char *format);
			void setFormat(const String &format);
			String getFormat() const;
			
			/// slider value
			/// \param callback Run changed callback on value change.
			/// \param exponent perform exponential conversion.
			void setValue(float64_t value, bool callback = false, bool exponent = false);
			float64_t getValue(bool exponent = false) const;
			float32_t getValuef32(bool exponent = false) const;
			uint32_t getValueu32(bool exponent = false) const;
			int32_t getValuei32(bool exponent = false) const;
			
			/// slider range
			/// \param exponent perform exponential conversion.
			void setRange(float64_t min, float64_t max, bool exponent = false);
			float64_t getMinRange(bool exponent = false) const;
			float64_t getMaxRange(bool exponent = false) const;
			
			/// handle size
			void setHandleSize(float32_t size);
			float32_t getHandleSize() const;
			
			/// format callback
			using FormatCallback = Function<String(ControlSlider)>;
			void setFormatCallback(const FormatCallback &func);
			FormatCallback getFormatCallback() const;
			
			/// pressed callback
			using PressedCallback = Function<void(ControlSlider)>;
			void setPressedCallback(const PressedCallback &func);
			PressedCallback getPressedCallback() const;
			bool isPressed();
			
			/// released callback
			using ReleasedCallback = Function<void(ControlSlider)>;
			void setReleasedCallback(const ReleasedCallback &func);
			ReleasedCallback getReleasedCallback() const;
			bool isReleased();
			
			/// clicked callback
			using ClickedCallback = Function<void(ControlSlider)>;
			void setClickedCallback(const ClickedCallback &func);
			void setClicked2Callback(const ClickedCallback &func);
			void setClickedRightCallback(const ClickedCallback &func);
			ClickedCallback getClickedCallback() const;
			ClickedCallback getClicked2Callback() const;
			ClickedCallback getClickedRightCallback() const;
			bool isClicked();
			
			/// changed callback
			using ChangedCallback = Function<void(ControlSlider)>;
			void setChangedCallback(const ChangedCallback &func);
			ChangedCallback getChangedCallback() const;
			bool isChanged(bool clear = true);
			
			/// canvas elements
			CanvasMesh getCanvasMesh();
	};
	
	/**
	 * The ControlScroll class represents a scroll control, typically used for scrolling content or adjusting values within a specified range.
	 * It can be configured to be either vertical or horizontal and supports customization of scroll step, color, range, and frame size.
	 */
	class TS_API ControlScroll : public ControlText {
			
			TS_DECLARE_PTR_2(ControlScroll, ControlText, Control, 0)
			
		public:
			
			ControlScroll();
			explicit ControlScroll(Control *parent, bool vertical = false);
			ControlScroll(Control *parent, float64_t value, bool vertical = false);
			ControlScroll(Control *parent, float64_t value, float64_t frame, float64_t range, bool vertical = false);
			ControlScroll(Control *parent, uint32_t value, uint32_t frame, uint32_t range, bool vertical = false);
			ControlScroll(Control *parent, int32_t value, int32_t frame, int32_t range, bool vertical = false);
			
			/// vertical flag
			void setVertical(bool vertical, bool text = true);
			bool isHorizontal() const;
			bool isVertical() const;
			
			/// scroll previous text
			void setPrevText(const char *text);
			void setPrevText(const String &text);
			String getPrevText() const;
			
			/// scroll next text
			void setNextText(const char *text);
			void setNextText(const String &text);
			String getNextText() const;
			
			/// scroll color
			void setScrollColor(const Color &color);
			const Color &getScrollColor() const;
			
			/// scroll step
			void setStep(float64_t step);
			float64_t getStep() const;
			
			/// scroll value
			void setValue(float64_t value, bool callback = false);
			float64_t getValue() const;
			
			/// scroll frame
			void setFrame(float64_t frame);
			float64_t getFrame() const;
			
			/// scroll range
			void setRange(float64_t range);
			float64_t getRange() const;
			
			/// frame alignment
			void setFrameAlign(Align align);
			Align getFrameAlign() const;
			
			TS_INLINE bool hasFrameAlign(Align align) const { return ((getFrameAlign() & align) != AlignNone); }
			TS_INLINE bool hasFrameAligns(Align aligns) const { return ((getFrameAlign() & aligns) == aligns); }
			
			/// clicked callback
			using ClickedCallback = Function<void(ControlScroll)>;
			void setClickedCallback(const ClickedCallback &func);
			ClickedCallback getClickedCallback() const;
			bool isClicked();
			
			/// changed callback
			using ChangedCallback = Function<void(ControlScroll)>;
			void setChangedCallback(const ChangedCallback &func);
			ChangedCallback getChangedCallback() const;
			bool isChanged(bool clear = true);
			
			/// canvas elements
			CanvasMesh getCanvasMesh();
	};
	
	/**
	 * The ControlSplit class represents a split control, often used for creating resizable panels or dividers within a user interface.
	 * It supports both vertical and horizontal orientations, with the ability to configure whether the split is absolute or relative.
	 * This control is useful for creating adjustable layouts in applications with multiple sections or panels.
	 */
	class TS_API ControlSplit : public Control {
			
			TS_DECLARE_PTR_1(ControlSplit, Control, 0)
			
		public:
			
			ControlSplit();
			explicit ControlSplit(Control *parent, bool vertical = false);
			ControlSplit(Control *parent, float32_t value, bool vertical = false);
			
			/// absolute flag
			void setAbsolute(bool absolute);
			bool isAbsolute() const;
			
			/// vertical flag
			void setVertical(bool vertical);
			bool isHorizontal() const;
			bool isVertical() const;
			
			/// split value
			void setValue(float32_t value);
			float32_t getValue() const;
			
			/// handle size
			void setHandleSize(float32_t size);
			float32_t getHandleSize() const;
			
			/// controls size
			const Vector2f &getControlsSize() const;
	};
	
	/**
	 * The ControlArea class represents a flexible area control within a user interface, capable of managing multiple controls in a grid-like layout.
	 * It allows for both horizontal and vertical scrolling, configurable scaling, and offers a range of alignment, size, and step options.
	 * The class supports dynamic scrolling, with adjustable values and steps for both horizontal and vertical axes.
	 * This control is ideal for creating organized, scrollable, and scalable grid-based layouts within a user interface.
	 */
	class TS_API ControlArea : public Control {
			
			TS_DECLARE_PTR_1(ControlArea, Control, 0)
			
		public:
			
			ControlArea();
			explicit ControlArea(Control *parent);
			ControlArea(Control *parent, uint32_t columns);
			ControlArea(Control *parent, bool horizontal, bool vertical);
			ControlArea(Control *parent, uint32_t columns, float32_t x, float32_t y);
			
			/// absolute flag
			void setAbsolute(bool absolute);
			bool isAbsolute() const;
			
			/// scalable flag
			void setScalable(bool scalable);
			bool isScalable() const;
			
			/// scrollable flag
			void setScrollable(bool scrollable);
			bool isScrollable() const;
			
			/// area scale
			void setScale(float32_t scale);
			float32_t getScale() const;
			
			/// scale range
			void setScaleRange(float32_t min, float32_t max);
			float32_t getMinScale() const;
			float32_t getMaxScale() const;
			
			/// area step
			void setHorizontalStep(float64_t step);
			void setVerticalStep(float64_t step);
			void setStep(float64_t horizontal, float64_t vertical);
			float64_t getHorizontalStep() const;
			float64_t getVerticalStep() const;
			
			/// area value
			void setHorizontalValue(float64_t value);
			void setVerticalValue(float64_t value);
			void setValue(float64_t horizontal, float64_t vertical);
			float64_t getHorizontalValue() const;
			float64_t getVerticalValue() const;
			
			/// frame alignment
			void setFrameAlign(Align align);
			Align getFrameAlign() const;
			
			/// area frame
			float64_t getHorizontalFrame() const;
			float64_t getVerticalFrame() const;
			
			/// area range
			float64_t getHorizontalRange() const;
			float64_t getVerticalRange() const;
			
			/// horizontal scroll
			void setHorizontalEnabled(bool enabled, bool dynamic = false);
			bool isHorizontalEnabled() const;
			bool isHorizontalDynamic() const;
			bool isHorizontalHidden() const;
			const ControlScroll getHorizontalScroll() const;
			ControlScroll getHorizontalScroll();
			
			/// vertical scroll
			void setVerticalEnabled(bool enabled, bool dynamic = false);
			bool isVerticalEnabled() const;
			bool isVerticalDynamic() const;
			bool isVerticalHidden() const;
			const ControlScroll getVerticalScroll() const;
			ControlScroll getVerticalScroll();
			
			/// font style
			bool setFontSize(uint32_t size);
			uint32_t getFontSize() const;
			
			bool setFontStyle(const FontStyle &style);
			const FontStyle &getFontStyleConst() const;
			const FontStyle &getFontStyle() const;
			FontStyle &getFontStyle();
			
			/// number of columns
			void setColumns(uint32_t columns);
			uint32_t getColumns() const;
			
			/// grid spacing
			void setSpacing(const Vector2f &spacing);
			void setSpacing(float32_t x, float32_t y);
			const Vector2f &getSpacing() const;
			
			/// grid column ratio
			void setColumnRatio(uint32_t index, float32_t ratio);
			float32_t getColumnRatio(uint32_t index) const;
			
			/// controls size
			const Vector2f &getControlsSize() const;
			
			/// controls offset
			const Vector2f &getControlsOffset() const;
			
			/// view rectangle
			const Rect &getViewRect() const;
	};
	
	/**
	 * The ControlTree class manages a hierarchical list or tree structure of items in a user interface, supporting various interaction features like selection, multi-selection, and item visibility.
	 * It allows items to be organized in a parent-child relationship, with functions to manipulate their text, color, icon, and custom data.
	 * The class also enables the folding and expansion of tree items, providing both a folded and expanded text representation.
	 * It offers texture management with configurable grid layouts and callbacks for user interactions, such as item selection, expansion, and dragging.
	 * This control is ideal for representing tree-like or linear structures, such as file explorers, menus, or categorized lists, with rich interaction capabilities.
	 */
	class TS_API ControlTree : public ControlText {
			
			TS_DECLARE_PTR_2(ControlTree, ControlText, Control, 0)
			
		public:
			
			ControlTree();
			explicit ControlTree(Control *parent);
			
			/// selectable flag
			void setSelectable(bool selectable);
			bool isSelectable() const;
			
			/// multi-selection flag
			void setMultiSelection(bool multi_selection);
			bool isMultiSelection() const;
			
			/// folded text
			void setFoldedText(const char *text);
			void setFoldedText(const String &text);
			String getFoldedText() const;
			
			/// expanded text
			void setExpandedText(const char *text);
			void setExpandedText(const String &text);
			String getExpandedText() const;
			
			/// texture pointer
			void setTexture(Texture &texture, uint32_t rows = 1, uint32_t columns = 1);
			Texture getTexture() const;
			
			/// texture name
			void setTextureName(const char *name, uint32_t rows = 1, uint32_t columns = 1);
			void setTextureName(const String &name, uint32_t rows = 1, uint32_t columns = 1);
			String getTextureName() const;
			
			/// texture layout
			void setTextureGrid(uint32_t rows, uint32_t columns);
			uint32_t getTextureRows() const;
			uint32_t getTextureColumns() const;
			
			/// tree items
			void clearItems();
			uint32_t addItem(const char *text, uint32_t parent = Maxu32, bool expanded = true);
			uint32_t addItem(const String &text, uint32_t parent = Maxu32, bool expanded = true);
			void addItems(const InitializerList<const char*> &items, uint32_t parent = Maxu32);
			void removeItem(uint32_t item, bool children = false);
			void viewItem(uint32_t item);
			
			uint32_t getNumItems() const;
			uint32_t getItem(uint32_t index) const;
			
			/// item hidden flag
			bool switchItemHidden(uint32_t item, bool children = false);
			void setItemHidden(uint32_t item, bool hidden, bool children = false);
			bool isItemHidden(uint32_t item) const;
			
			/// item expanded flag
			bool switchItemExpanded(uint32_t item, bool children = false);
			void setItemExpanded(uint32_t item, bool expanded, bool children = false);
			bool isItemExpanded(uint32_t item) const;
			
			/// item selected flag
			bool switchItemSelected(uint32_t item, bool children = false);
			void setItemSelected(uint32_t item, bool selected, bool children = false);
			bool isItemSelected(uint32_t item) const;
			
			/// item parent
			void setItemParent(uint32_t item, uint32_t parent);
			uint32_t getItemParent(uint32_t item) const;
			
			bool isItemParent(uint32_t item, uint32_t parent, bool hierarchy = false) const;
			
			/// item children
			void addItemChild(uint32_t item, uint32_t child);
			void removeItemChild(uint32_t item, uint32_t child);
			void addItemChildren(uint32_t item, const Array<uint32_t> &children);
			void removeItemChildren(uint32_t item, const Array<uint32_t> &children);
			
			uint32_t findItemChild(uint32_t item, uint32_t child) const;
			bool isItemChild(uint32_t item, uint32_t child) const;
			
			uint32_t getNumItemChildren(uint32_t item) const;
			uint32_t getItemChild(uint32_t item, uint32_t index) const;
			Array<uint32_t> getItemChildren(uint32_t item) const;
			
			/// item text
			void setItemText(uint32_t item, const char *text);
			void setItemText(uint32_t item, const String &text);
			String getItemText(uint32_t item) const;
			
			uint32_t findItemText(const char *text) const;
			uint32_t findItemText(const String &text) const;
			
			/// item color
			void setItemColor(uint32_t item, const Color &color);
			const Color &getItemColor(uint32_t item) const;
			
			/// item icon
			void setItemTexture(uint32_t item, uint32_t row, uint32_t column = 0);
			uint32_t getItemTextureRow(uint32_t item) const;
			uint32_t getItemTextureColumn(uint32_t item) const;
			
			/// item data
			void setItemData(uint32_t item, void *data);
			void *getItemData(uint32_t item) const;
			
			/// focused item
			uint32_t getFocusedItem() const;
			
			/// current item
			void setCurrentItem(uint32_t item, bool select = false, bool view = false, bool callback = false);
			uint32_t getCurrentItem() const;
			String getCurrentText() const;
			
			/// selected items
			void setSelection();
			void clearSelection();
			void inverseSelection();
			uint32_t getNumSelectedItems() const;
			uint32_t getSelectedItem(uint32_t index) const;
			Array<uint32_t> getSelectedItems() const;
			
			/// changed callback
			using ChangedCallback = Function<void(ControlTree, uint32_t item)>;
			void setChangedCallback(const ChangedCallback &func);
			ChangedCallback getChangedCallback() const;
			
			/// dragged callback
			using DraggedCallback = Function<bool(ControlTree, uint32_t item)>;
			void setDraggedCallback(const DraggedCallback &func);
			DraggedCallback getDraggedCallback() const;
			
			/// dropped callback
			using DroppedCallback = Function<void(ControlTree, uint32_t item)>;
			void setDroppedCallback(const DroppedCallback &func);
			DroppedCallback getDroppedCallback() const;
			
			/// clicked callback
			using ClickedCallback = Function<void(ControlTree, uint32_t item)>;
			void setClickedCallback(const ClickedCallback &func);
			void setClicked2Callback(const ClickedCallback &func);
			void setClickedRightCallback(const ClickedCallback &func);
			ClickedCallback getClickedCallback() const;
			ClickedCallback getClicked2Callback() const;
			ClickedCallback getClickedRightCallback() const;
			
			/// expanded callback
			using ExpandedCallback = Function<void(ControlTree, uint32_t item)>;
			void setExpandedCallback(const ExpandedCallback &func);
			ExpandedCallback getExpandedCallback() const;
			
			/// selected callback
			using SelectedCallback = Function<void(ControlTree)>;
			void setSelectedCallback(const SelectedCallback &func);
			SelectedCallback getSelectedCallback() const;
	};
	
	/**
	 * The ControlEdit class provides a user interface control for text input, supporting various modes like plain text, password, numeric, and hexadecimal input.
	 * It allows for customizable features like frame and background visibility, edit color, and password code.
	 * The class supports multiple text selection and manipulation functionalities, including setting and getting the current index, selection, and selected text.
	 * It also allows interaction through callbacks for events such as clicks, changes, and text returns.
	 * Additionally, the control can be updated based on keyboard input, enabling real-time interaction in user interfaces.
	 * Ideal for scenarios that require dynamic text input and modification, such as forms or password fields.
	 */
	class TS_API ControlEdit : public ControlText {
			
			TS_DECLARE_PTR_2(ControlEdit, ControlText, Control, 0)
			
		public:
			
			ControlEdit();
			explicit ControlEdit(Control *parent);
			ControlEdit(Control *parent, const char *text);
			ControlEdit(Control *parent, const String &text);
			
			/// frame flag
			void setFrame(bool frame);
			bool getFrame() const;
			
			/// background flag
			void setBackground(bool background);
			bool getBackground() const;
			
			/// edit color
			void setEditColor(const Color &color);
			const Color &getEditColor() const;
			
			/// edit mode
			enum EditMode {
				EditModeText,
				EditModePassword,
				EditModeNumber,
				EditModeSigned,
				EditModeUnsigned,
				EditModeHexadecimal,
			};
			
			void setEditMode(EditMode mode);
			EditMode getEditMode() const;
			
			/// password code
			void setPasswordCode(uint32_t code);
			uint32_t getPasswordCode() const;
			
			/// edit codes
			uint32_t getNumCodes() const;
			const uint32_t *getCodes() const;
			
			/// current index
			void setCurrentIndex(uint32_t index, uint32_t selection_index = Maxu32);
			uint32_t getCurrentIndex() const;
			uint32_t getSelectionIndex() const;
			
			/// selected text
			void setSelection(bool current = false, bool changed = false);
			void clearSelection();
			String getSelectedText() const;
			
			/// update control
			bool updateKeyboard(ControlRoot &root, uint32_t key, uint32_t code);
			
			/// clicked callback
			using ClickedCallback = Function<void(ControlEdit)>;
			void setClickedCallback(const ClickedCallback &func);
			ClickedCallback getClickedCallback() const;
			bool isClicked();
			
			/// changed callback
			using ChangedCallback = Function<void(ControlEdit)>;
			void setChangedCallback(const ChangedCallback &func);
			ChangedCallback getChangedCallback() const;
			bool isChanged();
			
			/// returned callback
			using ReturnedCallback = Function<void(ControlEdit)>;
			void setReturnedCallback(const ReturnedCallback &func);
			ReturnedCallback getReturnedCallback() const;
			bool isReturned();
			
			/// canvas elements
			CanvasMesh getCanvasMesh();
	};
	
	/**
	 * The ControlBase class serves as the foundation for creating various user interface controls.
	 * It provides essential functionalities for control creation, position management, and updates to control states, styles, and interactions.
	 * The class allows for control initialization and clearing, creation of canvas elements, and provides functionality to manage control visibility and state changes.
	 * It includes methods for updating control properties like position, style, mouse input, keyboard input, and control expansion.
	 * It also includes utilities for managing control states and rendering through canvases, making it suitable as a base class for more specific control implementations.
	 */
	class TS_API ControlBase : public Control {
			
			TS_DECLARE_BASE(ControlBase)
			
		protected:
			
			explicit ControlBase(Control *parent);
			
			/// clear control
			virtual void clear();
			
			/// create control
			void create();
			
			/// create canvas
			CanvasText create_text();
			CanvasMesh create_mesh();
			
			/// control batch
			virtual bool is_batch() const;
			
			/// disabled control
			bool get_disabled(ControlRoot &root) const;
			
			/// control position
			Vector3f get_position(const Rect &region, uint32_t scale) const;
			
			/// update control
			virtual void update_enabled(bool enabled);
			virtual void update_disabled(bool disabled);
			virtual void update_style(const FontStyle &style);
			virtual void update_expand(ControlRoot &root, const Rect &region);
			virtual void update_position(ControlRoot &root, const Vector2f &offset);
			virtual void update_mouse(ControlRoot &root, Axis axis, float32_t delta);
			virtual bool update_keyboard(ControlRoot &root, uint32_t key, uint32_t code);
			virtual void update_rectangle(ControlRoot &root, int32_t &order, uint32_t scale);
			virtual bool update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale);
			
			/// update canvas
			void update_text(ControlRoot &root, CanvasText &canvas_text, const Color &color, State state, const Vector3f &position) const;
			void update_mesh(ControlRoot &root, CanvasMesh &canvas_mesh, Mesh mesh, State state, const Rect &rect, uint32_t scale, bool clear = true) const;
			
			/// set control state
			State set_state(ControlRoot &root, State state);
			
			/// set control rect
			void set_rect(const Rect &rect);
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(Control::Align)
	TS_DECLARE_ENUM_OP(Control::Button)
}

#endif /* __TELLUSIM_INTERFACE_CONTROLS_H__ */

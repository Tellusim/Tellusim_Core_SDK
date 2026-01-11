// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_PLATFORM_XR_WINDOW_H__
#define __TELLUSIM_PLUGINS_PLATFORM_XR_WINDOW_H__

#include <core/TellusimSet.h>
#include <platform/TellusimContext.h>
#include <platform/TellusimSurface.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimWindow.h>

#include "TellusimXR.h"

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class XRInput;
	
	/**
	 * XRWindow
	 */
	class XRWindow : public Window {
			
		public:
			
			/// window constructor
			XRWindow();
			explicit XRWindow(Platform platform = PlatformAny, uint32_t index = Maxu32);
			virtual ~XRWindow();
			
			/// create window
			virtual bool create(const char *title, Window::Flags flags = DefaultFlags);
			virtual bool create(const String &title, Window::Flags flags = DefaultFlags);
			virtual bool create(Window::Flags flags = DefaultFlags);
			virtual void release();
			
			/// render window
			virtual bool render();
			virtual bool present();
			virtual bool finish();
			
			/// OpenXR system
			TS_INLINE XRSystem *getSystem() const { return system; }
			TS_INLINE XrSession getSession() const { return system->getSession(); }
			
			/// window context
			TS_INLINE Context getContext() const { return context; }
			TS_INLINE Device getDevice() const { return device; }
			
			/// window surfaces
			TS_INLINE uint32_t getNumSurfaces() const { return surfaces.size(); }
			TS_INLINE Surface getSurface(uint32_t index) const { return surfaces[index]; }
			
			/// frame state
			TS_INLINE uint64_t getFrameIndex() const { return frame_index; }
			TS_INLINE const XrFrameState &getFrameState() const { return frame_state; }
			TS_INLINE XrTime getFrameTime() const { return frame_state.predictedDisplayTime; }
			
			/// current views
			TS_INLINE const XrViewState &getViewState() const { return view_state; }
			TS_INLINE const XrView &getView(uint32_t index) const { return current_views[index]; }
			
			/// current location
			TS_INLINE const XrSpaceLocation &getLocation() const { return current_location; }
			TS_INLINE const XrSpaceVelocity &getVelocity() const { return current_velocity; }
			
			/// swap chains
			TS_INLINE uint32_t getNumSwapChains() const { return swap_chains.size(); }
			TS_INLINE XrSwapchain getColorSwapChain(uint32_t index) const { return swap_chains[index].color; }
			TS_INLINE XrSwapchain getDepthSwapChain(uint32_t index) const { return swap_chains[index].depth; }
			
			/// headset position
			Vector3f getPosition() const;
			Quaternionf getRotation() const;
			Matrix4x3f getTransform() const;
			
			/// headset velocity
			Vector3f getLinearVelocity() const;
			Vector3f getAngularVelocity() const;
			
			/// headset matrices
			Matrix4x4f getProjection(uint32_t index, float32_t znear) const;
			Matrix4x3f getModelview(uint32_t index) const;
			
			/// input interfaces
			void addInput(XRInput *input);
			void removeInput(const XRInput *input);
			
		private:
			
			/// update callback
			void update();
			
			/// close callback
			void close();
			
			bool open = false;							// open flag
			
			XRSystem *system = nullptr;					// OpenXR system
			
			Context context;							// window context
			Surface surface;							// window surface
			Device device;								// window device
			
			Array<Surface> surfaces;					// window surfaces
			
			uint64_t frame_index = 0;					// frame index
			XrFrameState frame_state = {};				// frame state
			
			XrViewState view_state = {};				// view state
			Array<XrView> current_views;				// current views
			
			XrSpaceLocation current_location = {};		// current location
			XrSpaceVelocity current_velocity = {};		// current velocity
			
			struct SwapChain {
				uint32_t width = 0;						// width
				uint32_t height = 0;					// height
				Array<uint32_t> surfaces;				// surfaces
				Array<size_t> color_images;				// color images
				Array<size_t> depth_images;				// depth images
				XrSwapchain color = XR_NULL_HANDLE;		// color swap chain
				XrSwapchain depth = XR_NULL_HANDLE;		// depth swap chain
			};
			
			Array<SwapChain> swap_chains;				// view swap chains
			
			Set<XRInput*> current_inputs;				// current inputs
			Array<XrActiveActionSet> active_actions;	// active actions
			
			Array<XrCompositionLayerProjectionView> projection_views;
	};
}

#endif /* __TELLUSIM_PLUGINS_PLATFORM_XR_WINDOW_H__ */

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <platform/TellusimCommand.h>

#include "../include/TellusimXRInput.h"
#include "../include/TellusimXRWindow.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	XRWindow::XRWindow() {
		
		// open OpenXR
		open = XR::retain();
	}
	
	XRWindow::XRWindow(Platform platform, uint32_t index) : Window(platform, index) {
		
		// open OpenXR
		open = XR::retain();
	}
	
	XRWindow::~XRWindow() {
		
		// release window
		release();
		
		// close OpenXR
		if(XR::release()) XR::close();
	}
	
	/*
	 */
	bool XRWindow::create(const char *title, Window::Flags flags) {
		return (setTitle(title) && create(flags));
	}
	
	bool XRWindow::create(const String &title, Window::Flags flags) {
		return (setTitle(title) && create(flags));
	}
	
	bool XRWindow::create(Window::Flags flags) {
		
		TS_ASSERT(!isCreated() && "XRWindow::create(): is already created");
		
		// open OpenXR
		if(open) {
			open = false;
			if(!XR::isOpened() && !XR::open()) {
				TS_LOG(Error, "XRWindow::create(): can't open OpenXR\n");
				return false;
			}
		}
		
		// check OpenXR
		if(!XR::isOpened()) {
			TS_LOG(Error, "XRWindow::create(): OpenXR is not opened\n");
			return false;
		}
		
		// create system
		system = XR::getSystem(0);
		context = Context(getPlatform(), getIndex());
		if(!system->isCreated() && !system->create(context)) {
			TS_LOG(Error, "XRWindow::create(): can't create system\n");
			return false;
		}
		
		// create window surface
		surface = Surface(context);
		if(!surface) {
			TS_LOG(Error, "XRWindow::create(): can't create surface\n");
			return false;
		}
		
		// window flags
		setFlags(flags);
		
		// update callback
		setUpdateCallback(makeFunction([](XRWindow *window) { window->update(); }, this));
		
		// surface multisample
		surface.setMultisample(getMultisample());
		
		// window surface color format
		if(hasFlag(FlagColorRGBu10Au2n) && system->hasFormat(FormatRGBu10Au2n)) surface.setColorFormat(FormatRGBu10Au2n);
		else if(hasFlag(FlagColorRGBAf16) && system->hasFormat(FormatRGBAf16)) surface.setColorFormat(FormatRGBAf16);
		else if(system->hasFormat(FormatRGBAu8ns)) surface.setColorFormat(FormatRGBAu8ns);
		else if(system->hasFormat(FormatRGBAu8n)) surface.setColorFormat(FormatRGBAu8n);
		else {
			TS_LOG(Error, "XRWindow::create(): can't find color format\n");
			release();
			return false;
		}
		
		// window surface depth format
		if(system->hasFormat(FormatDu24Su8)) surface.setDepthFormat(FormatDu24Su8);
		else if(system->hasFormat(FormatDf32Su8)) surface.setDepthFormat(FormatDf32Su8);
		else if(system->hasFormat(FormatDu16Su8)) surface.setDepthFormat(FormatDu16Su8);
		else if(system->hasFormat(FormatDu24)) surface.setDepthFormat(FormatDu24);
		else if(system->hasFormat(FormatDf32)) surface.setDepthFormat(FormatDf32);
		else if(system->hasFormat(FormatDu16)) surface.setDepthFormat(FormatDu16);
		else {
			TS_LOG(Error, "XRWindow::create(): can't find depth format\n");
			release();
			return false;
		}
		
		// set window surface
		setSurface(surface);
		
		// create surfaces
		XrView current_view = {};
		surfaces.resize(system->getNumViewModes(0));
		current_views.resize(getNumSurfaces(), current_view);
		for(uint32_t i = 0; i < getNumSurfaces(); i++) {
			const XrViewConfigurationView &mode = system->getViewMode(0, i);
			
			// view size
			uint32_t width = mode.recommendedImageRectWidth;
			uint32_t height = mode.recommendedImageRectHeight;
			
			// create surface
			surfaces[i] = Surface(context);
			surfaces[i].setMultisample(surface.getMultisample());
			surfaces[i].setColorFormat(surface.getColorFormat());
			surfaces[i].setDepthFormat(surface.getDepthFormat());
			surfaces[i].setSize(width, height);
			
			// create current view
			current_views[i].type = XR_TYPE_VIEW;
			
			// window size
			setSize(max(getWidth(), width), max(getHeight(), height));
			surface.setSize(getWidth(), getHeight());
			
			// find swap chain
			uint32_t index = Maxu32;
			for(uint32_t j = 0; j < swap_chains.size(); j++) {
				SwapChain &swap_chain = swap_chains[j];
				if(swap_chain.width != width) continue;
				if(swap_chain.height != height) continue;
				swap_chain.surfaces.append(i);
				index = j;
				break;
			}
			if(index != Maxu32) continue;
			
			// create swap chain
			SwapChain swap_chain;
			swap_chain.width = width;
			swap_chain.height = height;
			swap_chain.surfaces.append(i);
			swap_chains.append(swap_chain);
		}
		
		// create swap chains
		for(SwapChain &swap_chain : swap_chains) {
			
			// swap chain create info
			XrSwapchainCreateInfo swap_chain_info = {};
			swap_chain_info.type = XR_TYPE_SWAPCHAIN_CREATE_INFO;
			swap_chain_info.sampleCount = getMultisample();
			swap_chain_info.width = swap_chain.width;
			swap_chain_info.height = swap_chain.height;
			swap_chain_info.faceCount = 1;
			swap_chain_info.arraySize = swap_chain.surfaces.size();
			swap_chain_info.mipCount = 1;
			
			// create color swap chain
			swap_chain_info.format = system->getFormat(getColorFormat());
			swap_chain_info.usageFlags = XR_SWAPCHAIN_USAGE_COLOR_ATTACHMENT_BIT;
			if(XR::error(xrCreateSwapchain(system->getSession(), &swap_chain_info, &swap_chain.color))) {
				TS_LOG(Error, "XRWindow::create(): can't create color swap chain\n");
				release();
				return false;
			}
			if(!system->getImages(swap_chain.color, swap_chain.color_images)) {
				TS_LOG(Error, "XRWindow::create(): can't get color swap chain images\n");
				release();
				return false;
			}
			
			// create depth swap chain
			swap_chain_info.format = system->getFormat(getDepthFormat());
			swap_chain_info.usageFlags = XR_SWAPCHAIN_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
			if(XR::error(xrCreateSwapchain(system->getSession(), &swap_chain_info, &swap_chain.depth))) {
				TS_LOG(Error, "XRWindow::create(): can't create depth swap chain\n");
				release();
				return false;
			}
			if(!system->getImages(swap_chain.depth, swap_chain.depth_images)) {
				TS_LOG(Error, "XRWindow::create(): can't get depth swap chain images\n");
				release();
				return false;
			}
			
			// update surface layers
			for(uint32_t i = 0; i < swap_chain.surfaces.size(); i++) {
				Surface &surface = surfaces[swap_chain.surfaces[i]];
				surface.setColorLayer(i, swap_chain.surfaces.size());
				surface.setDepthLayer(i, swap_chain.surfaces.size());
			}
		}
		
		// create window device
		device = Device(surface);
		if(!device) {
			TS_LOG(Error, "XRWindow::create(): can't create device\n");
			release();
			return false;
		}
		
		return true;
	}
	
	void XRWindow::release() {
		
		// finish context
		if(context) context.finish();
		
		// clear surfaces
		surfaces.clear();
		
		// clear views
		current_views.clear();
		
		// release swap chains
		for(SwapChain &swap_chain : swap_chains) {
			if(swap_chain.color && XR::error(xrDestroySwapchain(swap_chain.color))) {
				TS_LOG(Error, "XRWindow::release(): can't release color swap chain\n");
			}
			if(swap_chain.depth && XR::error(xrDestroySwapchain(swap_chain.depth))) {
				TS_LOG(Error, "XRWindow::release(): can't release depth swap chain\n");
			}
			swap_chain.color = XR_NULL_HANDLE;
			swap_chain.depth = XR_NULL_HANDLE;
		}
		swap_chains.clear();
		
		// clear inputs
		for(XRInput *input : current_inputs) {
			input->window = nullptr;
			input->release();
		}
		current_inputs.clear();
	}
	
	/*
	 */
	void XRWindow::update() {
		
		// check system
		if(getSystem() == nullptr) return;
		
		// initialize window
		if(frame_index++ == 0) {
			
			// hide window
			setHidden(true);
			setMinimized(true);
			setFocused(false);
			
			// attach actions
			if(current_inputs) {
				
				// current actions
				active_actions.clear();
				Array<XrActionSet> actions;
				Map<String, Array<XrActionSuggestedBinding>> bindings;
				for(XRInput *input : current_inputs) {
					
					// current inputs
					actions.append(input->getActions());
					
					// action set
					XrActiveActionSet actions = {};
					actions.actionSet = input->getActions();
					active_actions.append(actions);
					
					// input bindings
					input->get_bindings(bindings);
				}
				
				// create bindings
				for(const auto &it : bindings) {
					
					// create profile
					XrPath profile;
					if(XR::error(xrStringToPath(XR::getInstance(), it.key.get(), &profile))) {
						TS_LOGF(Error, "XRWindow::update(): can't add \"%s\" path\n", it.key.get());
						continue;
					}
					
					// create binding
					XrInteractionProfileSuggestedBinding binding = {};
					binding.type = XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING;
					binding.interactionProfile = profile;
					binding.countSuggestedBindings = it.data.size();
					binding.suggestedBindings = it.data.get();
					if(XR::error(xrSuggestInteractionProfileBindings(XR::getInstance(), &binding))) {
						TS_LOGF(Error, "XRInput::addBinding(): can't add \"%s\" profile\n", it.key.get());
						continue;
					}
				}
				
				// attach info
				XrSessionActionSetsAttachInfo attach_info = {};
				attach_info.type = XR_TYPE_SESSION_ACTION_SETS_ATTACH_INFO;
				attach_info.countActionSets = actions.size();
				attach_info.actionSets = actions.get();
				
				// attach actions
				if(XR::error(xrAttachSessionActionSets(getSession(), &attach_info))) {
					TS_LOG(Error, "XRWindow::update(): can't attach actions\n");
					active_actions.clear();
				}
			}
		}
		
		// process events
		while(true) {
			
			// get next event
			XrEventDataBuffer event_data = {};
			event_data.type = XR_TYPE_EVENT_DATA_BUFFER;
			XrResult result = xrPollEvent(XR::getInstance(), &event_data);
			if(result == XR_EVENT_UNAVAILABLE) break;
			if(XR::error(result)) break;
			
			// session state changed
			XrStructureType type = event_data.type;
			if(type == XR_TYPE_EVENT_DATA_SESSION_STATE_CHANGED) {
				XrEventDataSessionStateChanged *event = (XrEventDataSessionStateChanged*)&event_data;
				XrSessionState state = event->state;
				
				// session is idle
				if(state == XR_SESSION_STATE_IDLE) {
					TS_LOG(Verbose, "XRWindow::update(): session is idle\n");
					setMinimized(true);
					setFocused(false);
				}
				// session is ready
				else if(state == XR_SESSION_STATE_READY) {
					TS_LOG(Verbose, "XRWindow::update(): session is ready\n");
					if(isHidden()) {
						XrSessionBeginInfo begin_info = {};
						begin_info.type = XR_TYPE_SESSION_BEGIN_INFO;
						begin_info.primaryViewConfigurationType = system->getViewType(0);
						if(XR::error(xrBeginSession(system->getSession(), &begin_info))) {
							TS_LOG(Error, "XRWindow::update(): can't begin session\n");
							close();
							break;
						}
						setHidden(false);
						setMinimized(false);
					}
				}
				// session is synchronized
				else if(state == XR_SESSION_STATE_SYNCHRONIZED) {
					TS_LOG(Verbose, "XRWindow::update(): session is synchronized\n");
					setMinimized(false);
				}
				// session is visible
				else if(state == XR_SESSION_STATE_VISIBLE) {
					TS_LOG(Verbose, "XRWindow::update(): session is visible\n");
				}
				// session is focused
				else if(state == XR_SESSION_STATE_FOCUSED) {
					TS_LOG(Verbose, "XRWindow::update(): session is focused\n");
					setFocused(true);
				}
				// session is stopping
				else if(state == XR_SESSION_STATE_STOPPING) {
					TS_LOG(Verbose, "XRWindow::update(): session is stopping\n");
					if(!isHidden()) {
						if(XR::error(xrEndSession(system->getSession()))) {
							TS_LOG(Error, "XRWindow::update(): can't end session\n");
							close();
							break;
						}
						setHidden(true);
					}
				}
				// session is exiting
				else if(state == XR_SESSION_STATE_LOSS_PENDING || state == XR_SESSION_STATE_EXITING) {
					TS_LOG(Verbose, "XRWindow::update(): session is exiting\n");
					close();
					break;
				}
				else {
					TS_LOGF(Verbose, "XRWindow::update(): session state %u\n", state);
				}
			}
			else if(type == XR_TYPE_EVENT_DATA_INSTANCE_LOSS_PENDING) {
				TS_LOG(Verbose, "XRWindow::update(): instance loss pending\n");
				close();
				break;
			}
			// reference space change pending
			else if(type == XR_TYPE_EVENT_DATA_REFERENCE_SPACE_CHANGE_PENDING) {
				TS_LOG(Verbose, "XRWindow::update(): reference space change pending\n");
			}
			// interaction profile changed
			else if(type == XR_TYPE_EVENT_DATA_INTERACTION_PROFILE_CHANGED) {
				TS_LOG(Verbose, "XRWindow::update(): interaction profile changed\n");
			}
			// display refresh rate chagned
			else if(type == XR_TYPE_EVENT_DATA_DISPLAY_REFRESH_RATE_CHANGED_FB) {
				TS_LOG(Verbose, "XRWindow::update(): display refresh rate changed\n");
			}
			// unknown event
			else {
				TS_LOGF(Warning, "XRWindow::update(): unknown event %u\n", type);
			}
		}
		
		// synchronize actions
		if(!isHidden() && !isMinimized() && isFocused() && active_actions) {
			
			// sync info
			XrActionsSyncInfo sync_info = {};
			sync_info.type = XR_TYPE_ACTIONS_SYNC_INFO;
			sync_info.countActiveActionSets = active_actions.size();
			sync_info.activeActionSets = active_actions.get();
			
			// sync actions
			if(XR::error(xrSyncActions(getSession(), &sync_info))) {
				TS_LOG(Error, "XRWindow::update(): can't synchronize actions\n");
			}
		}
	}
	
	/*
	 */
	void XRWindow::close() {
		const auto &close_func = getCloseClickedCallback();
		if(close_func) close_func();
	}
	
	/*
	 */
	bool XRWindow::render() {
		
		// check system
		if(getSystem() == nullptr) return true;
		
		// check status
		if(isHidden()) return true;
		
		// frame wait info
		XrFrameWaitInfo wait_info = {};
		wait_info.type = XR_TYPE_FRAME_WAIT_INFO;
		
		// wait frame
		frame_state.type = XR_TYPE_FRAME_STATE;
		if(XR::error(xrWaitFrame(system->getSession(), &wait_info, &frame_state))) {
			TS_LOG(Error, "XRWindow::render(): can't wait frame\n");
			return false;
		}
		
		// get spaces
		XrSpace view_space = system->getSpace(XR_REFERENCE_SPACE_TYPE_VIEW);
		XrSpace local_space = system->getSpace(XR_REFERENCE_SPACE_TYPE_LOCAL);
		
		// current location
		current_location.type = XR_TYPE_SPACE_LOCATION;
		current_velocity.type = XR_TYPE_SPACE_VELOCITY;
		current_location.next = &current_velocity;
		if(XR::error(xrLocateSpace(view_space, local_space, getFrameTime(), &current_location))) {
			TS_LOG(Error, "XRWindow::render(): can't locate space\n");
			return false;
		}
		
		// view locate info
		XrViewLocateInfo locate_info = {};
		locate_info.type = XR_TYPE_VIEW_LOCATE_INFO;
		locate_info.viewConfigurationType = system->getViewType(0);
		locate_info.displayTime = getFrameTime();
		locate_info.space = local_space;
		
		// current views
		view_state.type = XR_TYPE_VIEW_STATE;
		uint32_t num_views = getNumSurfaces();
		if(XR::error(xrLocateViews(system->getSession(), &locate_info, &view_state, num_views, &num_views, current_views.get()))) {
			TS_LOG(Error, "XRWindow::render(): can't locate views\n");
			return false;
		}
		
		// check status
		if(isMinimized()) return true;
		
		// begin frame
		XrFrameBeginInfo begin_info = {};
		begin_info.type = XR_TYPE_FRAME_BEGIN_INFO;
		if(XR::error(xrBeginFrame(system->getSession(), &begin_info))) {
			TS_LOG(Error, "XRWindow::render(): can't begin frame\n");
			return false;
		}
		
		// acquire swap chains
		for(const SwapChain &swap_chain : swap_chains) {
			
			// acquire info
			XrSwapchainImageAcquireInfo acquire_info = {};
			acquire_info.type = XR_TYPE_SWAPCHAIN_IMAGE_ACQUIRE_INFO;
			
			// acquire color image
			uint32_t color_index = 0;
			if(XR::error(xrAcquireSwapchainImage(swap_chain.color, &acquire_info, &color_index))) {
				TS_LOG(Error, "XRWindow::render(): can't acquire color image\n");
				return false;
			}
			
			// acquire depth image
			uint32_t depth_index = 0;
			if(XR::error(xrAcquireSwapchainImage(swap_chain.depth, &acquire_info, &depth_index))) {
				TS_LOG(Error, "XRWindow::render(): can't acquire depth image\n");
				return false;
			}
			
			// wait info
			XrSwapchainImageWaitInfo wait_info = {};
			wait_info.type = XR_TYPE_SWAPCHAIN_IMAGE_WAIT_INFO;
			wait_info.timeout = XR_INFINITE_DURATION;
			
			// wait color image
			if(XR::error(xrWaitSwapchainImage(swap_chain.color, &wait_info))) {
				TS_LOG(Error, "XRWindow::render(): can't wait color image\n");
				return false;
			}
			
			// wait depth image
			if(XR::error(xrWaitSwapchainImage(swap_chain.depth, &wait_info))) {
				TS_LOG(Error, "XRWindow::render(): can't wait depth image\n");
				return false;
			}
			
			// swap chain surfaces
			for(uint32_t i = 0; i < swap_chain.surfaces.size(); i++) {
				Surface &surface = surfaces[swap_chain.surfaces[i]];
				size_t color_image = swap_chain.color_images[color_index];
				size_t depth_image = swap_chain.depth_images[depth_index];
				system->setImages(surface, color_image, depth_image);
			}
		}
		
		return true;
	}
	
	/*
	 */
	bool XRWindow::present() {
		
		// check system
		if(getSystem() == nullptr) return true;
		
		// check status
		if(isHidden() || isMinimized()) return true;
		
		// flip context
		if(!device.flip()) {
			TS_LOG(Error, "XRWindow::present(): can't flip context\n");
			return false;
		}
		
		// release swap chains
		projection_views.clear();
		for(const SwapChain &swap_chain : swap_chains) {
			
			// release info
			XrSwapchainImageReleaseInfo release_info = {};
			release_info.type = XR_TYPE_SWAPCHAIN_IMAGE_RELEASE_INFO;
			
			// release color image
			if(XR::error(xrReleaseSwapchainImage(swap_chain.color, &release_info))) {
				TS_LOG(Error, "XRWindow::present(): can't release color image\n");
				return false;
			}
			
			// release depth image
			if(XR::error(xrReleaseSwapchainImage(swap_chain.depth, &release_info))) {
				TS_LOG(Error, "XRWindow::present(): can't release depth image\n");
				return false;
			}
			
			// swap chain surfaces
			for(uint32_t i = 0; i < swap_chain.surfaces.size(); i++) {
				
				// clear surface images
				Surface &surface = surfaces[swap_chain.surfaces[i]];
				system->setImages(surface, 0, 0);
				
				// projection view
				uint32_t index = projection_views.size();
				XrCompositionLayerProjectionView view = {};
				view.type = XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW;
				view.pose = current_views[index].pose;
				view.fov = current_views[index].fov;
				view.subImage.swapchain = swap_chain.color;
				view.subImage.imageRect.extent.width = swap_chain.width;
				view.subImage.imageRect.extent.height = swap_chain.height;
				view.subImage.imageArrayIndex = i;
				projection_views.append(view);
			}
		}
		
		// projection layer
		XrCompositionLayerProjection projection_layer = {};
		projection_layer.type = XR_TYPE_COMPOSITION_LAYER_PROJECTION;
		projection_layer.layerFlags = XR_COMPOSITION_LAYER_CORRECT_CHROMATIC_ABERRATION_BIT;
		projection_layer.space = system->getSpace(XR_REFERENCE_SPACE_TYPE_LOCAL);
		projection_layer.viewCount = projection_views.size();
		projection_layer.views = projection_views.get();
		
		// composition layers
		XrCompositionLayerBaseHeader *layers[XR_MIN_COMPOSITION_LAYERS_SUPPORTED] = {};
		layers[0] = (XrCompositionLayerBaseHeader*)&projection_layer;
		
		// frame end info
		XrFrameEndInfo end_info = {};
		end_info.type = XR_TYPE_FRAME_END_INFO;
		end_info.displayTime = getFrameTime();
		end_info.environmentBlendMode = XR_ENVIRONMENT_BLEND_MODE_OPAQUE;
		end_info.layerCount = 1;
		end_info.layers = layers;
		
		// end frame
		if(XR::error(xrEndFrame(system->getSession(), &end_info))) {
			TS_LOG(Error, "XRWindow::present(): can't end frame\n");
			return false;
		}
		
		return true;
	}
	
	/*
	 */
	bool XRWindow::finish() {
		if(context) return context.finish();
		return true;
	}
	
	/*
	 */
	Vector3f XRWindow::getPosition() const {
		const XrVector3f &position = current_location.pose.position;
		return Vector3f(position.x, -position.z, position.y);
	}
	
	Quaternionf XRWindow::getRotation() const {
		return Quaternionf::rotateX(90.0f) * XR::toQuaternionf(current_location.pose.orientation);
	}
	
	Matrix4x3f XRWindow::getTransform() const {
		return Matrix4x3f::rotateX(90.0f) * XR::toMatrix4x3f(current_location.pose);
	}
	
	/*
	 */
	Vector3f XRWindow::getLinearVelocity() const {
		const XrVector3f &velocity = current_velocity.linearVelocity;
		return Vector3f(velocity.x, -velocity.z, velocity.y);
	}
	
	Vector3f XRWindow::getAngularVelocity() const {
		const XrVector3f &velocity = current_velocity.angularVelocity;
		return Vector3f(velocity.x, -velocity.z, velocity.y);
	}
	
	/*
	 */
	Matrix4x4f XRWindow::getProjection(uint32_t index, float32_t znear) const {
		const XrFovf &fov = current_views[index].fov;
		float32_t l = tan(fov.angleLeft);
		float32_t r = tan(fov.angleRight);
		float32_t b = tan(fov.angleDown);
		float32_t t = tan(fov.angleUp);
		float32_t rl = r - l;
		float32_t tb = t - b;
		Matrix4x4f ret;
		ret.row_0.set(2.0f / rl, 0.0f, (l + r) / rl, 0.0f);
		ret.row_1.set(0.0f, 2.0f / tb, (t + b) / tb, 0.0f);
		ret.row_2.set(0.0f, 0.0f, 0.0f, znear);
		ret.row_3.set(0.0f, 0.0f, -1.0f, 0.0f);
		return ret;
	}
	
	Matrix4x3f XRWindow::getModelview(uint32_t index) const {
		const XrPosef &pose = current_views[index].pose;
		return inverse(XR::toMatrix4x3f(pose)) * Matrix4x3f::rotateX(-90.0f);
	}
	
	/*
	 */
	void XRWindow::addInput(XRInput *input) {
		current_inputs.append(input);
	}
	
	void XRWindow::removeInput(const XRInput *input) {
		current_inputs.remove(input);
	}
}

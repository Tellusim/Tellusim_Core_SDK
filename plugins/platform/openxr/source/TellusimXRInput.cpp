// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>

#include "../include/TellusimXRWindow.h"
#include "../include/TellusimXRInput.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	const char *XRInput::ProfileKHR = "/interaction_profiles/khr/simple_controller";
	const char *XRInput::ProfileHTC = "/interaction_profiles/htc/vive_controller";
	const char *XRInput::ProfileValve = "/interaction_profiles/valve/index_controller";
	const char *XRInput::ProfileOculus = "/interaction_profiles/oculus/touch_controller";
	
	const char *XRInput::HandLeft = "/user/hand/left";
	const char *XRInput::HandRight = "/user/hand/right";
	
	const char *XRInput::InputA = "/input/a/click";
	const char *XRInput::InputB = "/input/b/click";
	const char *XRInput::InputX = "/input/x/click";
	const char *XRInput::InputY = "/input/y/click";
	const char *XRInput::InputAim = "/input/aim/pose";
	const char *XRInput::InputGrip = "/input/grip/pose";
	const char *XRInput::InputThumb = "/input/thumbstick";
	const char *XRInput::InputTrigger = "/input/trigger";
	const char *XRInput::InputSqueeze = "/input/squeeze";
	
	/*
	 */
	XRInput::XRInput() {
		
	}
	
	XRInput::~XRInput() {
		
		release();
	}
	
	/*
	 */
	bool XRInput::create(XRWindow *w, const char *p) {
		
		TS_ASSERT(!isCreated() && "XRInput::create(): is already created");
		
		// check window
		if(w == nullptr || !w->isCreated() || !w->getSystem()) {
			TS_LOG(Error, "XRInput::create(): window is not created\n");
			return false;
		}
		
		window = w;
		system = window->getSystem();
		
		prefix = p;
		
		// action set info
		XrActionSetCreateInfo actions_info = {};
		actions_info.type = XR_TYPE_ACTION_SET_CREATE_INFO;
		strncpy(actions_info.actionSetName, prefix.replace("/", "_").get(), sizeof(actions_info.actionSetName));
		strncpy(actions_info.localizedActionSetName, actions_info.actionSetName, sizeof(actions_info.localizedActionSetName));
		actions_info.priority = 0;
		
		// create action set
		if(XR::error(xrCreateActionSet(XR::getInstance(), &actions_info, &actions))) {
			TS_LOGF(Error, "XRInput::create(): can't create action set for \"%s\"\n", prefix.get());
			release();
			return false;
		}
		
		// register input
		window->addInput(this);
		
		return true;
	}
	
	void XRInput::release() {
		
		// unregister input
		if(window) window->removeInput(this);
		
		// clear window
		window = nullptr;
		system = nullptr;
		prefix.clear();
		
		// clear parameters
		parameters.clear();
		names.clear();
		
		// release action set
		if(actions != XR_NULL_HANDLE) {
			if(XR::error(xrDestroyActionSet(actions))) {
				TS_LOG(Error, "XRInput::release(): can't release action set\n");
			}
			actions = XR_NULL_HANDLE;
		}
	}
	
	/*
	 */
	uint32_t XRInput::add_parameter(const char *name, XrActionType type, const char *profile, const char *path) {
		
		TS_ASSERT(isCreated() && "XRInput::add_parameter(): is not created");
		
		// find parameter
		auto it = names.find(name);
		if(it != names.end()) {
			if(profile) addBinding(it->data, profile, path);
			return it->data;
		}
		
		// create parameter
		Parameter parameter;
		parameter.name = name;
		
		// create parameter action
		XrActionCreateInfo action_info = {};
		action_info.type = XR_TYPE_ACTION_CREATE_INFO;
		action_info.actionType = type;
		strncpy(action_info.actionName, parameter.name.replace("/", "_").get(), sizeof(action_info.actionName));
		strncpy(action_info.localizedActionName, action_info.actionName, sizeof(action_info.localizedActionName));
		
		// create action
		if(XR::error(xrCreateAction(getActions(), &action_info, &parameter.action))) {
			TS_LOGF(Error, "XRInput::add_parameter(): can't create \"%s\" action\n", name);
			return Maxu32;
		}
		
		// create pose space
		if(type == XR_ACTION_TYPE_POSE_INPUT) {
			XrActionSpaceCreateInfo space_info = {};
			space_info.type = XR_TYPE_ACTION_SPACE_CREATE_INFO;
			space_info.action = parameter.action;
			space_info.poseInActionSpace.orientation.w = 1.0f;
			if(XR::error(xrCreateActionSpace(getSession(), &space_info, &parameter.space))) {
				TS_LOGF(Error, "XRInput::add_parameter(): can't create \"%s\" space\n", name);
				return Maxu32;
			}
		}
		
		// create parameter
		uint32_t id = parameters.size();
		parameters.append(id, parameter);
		names.append(String(name), id);
		addBinding(id, profile, path);
		return id;
	}
	
	/*
	 */
	bool XRInput::addBinding(const char *name, const char *profile, const char *path) {
		auto it = names.find(name);
		if(it) return addBinding(it->data, profile, path);
		return false;
	}
	
	bool XRInput::addBinding(uint32_t id, const char *profile, const char *path) {
		
		// find parameter
		auto it = parameters.find(id);
		if(it == parameters.end()) {
			TS_LOGF(Error, "XRInput::addBinding(): can't find %u parameter\n", id);
			return Maxu32;
		}
		Parameter &parameter = it->data;
		
		// create action binding
		XrPath binding = XR_NULL_PATH;
		String name = getPrefix() + path;
		if(!path) name += parameter.name;
		if(XR::error(xrStringToPath(XR::getInstance(), name.get(), &binding))) {
			TS_LOGF(Error, "XRInput::addBinding(): can't add \"%s\" path\n", name.get());
			return false;
		}
		
		// create binding
		parameter.bindings.append(String(profile), binding);
		
		return true;
	}
	
	/*
	 */
	void XRInput::get_bindings(Map<String, Array<XrActionSuggestedBinding>> &bindings) const {
		
		// create suggested bindings for all parameters
		for(const auto &parameter_it : parameters) {
			const Parameter &parameter = parameter_it.data;
			for(const auto &binding_it : parameter.bindings) {
				XrActionSuggestedBinding binding = {};
				binding.action = parameter.action;
				binding.binding = binding_it.data;
				auto it = bindings.find(binding_it.key);
				if(!it) it = bindings.append(binding_it.key);
				it->data.append(binding);
			}
		}
	}
	
	/*
	 */
	uint32_t XRInput::addBool(const char *name, const char *profile, const char *path) {
		return add_parameter(name, XR_ACTION_TYPE_BOOLEAN_INPUT, profile, path);
	}
	
	bool XRInput::getBool(const char *name, bool clear, bool value) const {
		auto it = names.find(name);
		if(it) return getBool(it->data, clear, value);
		return value;
	}
	
	bool XRInput::getBool(uint32_t id, bool clear, bool value) const {
		
		// check parameter
		if(id == Maxu32) return value;
		
		// find parameter
		auto it = parameters.find(id);
		if(it == parameters.end()) {
			TS_LOGF(Error, "XRInput::getBool(): can't find %u parameter\n", id);
			return value;
		}
		const Parameter &parameter = it->data;
		
		// get info
		XrActionStateGetInfo get_info = {};
		get_info.type = XR_TYPE_ACTION_STATE_GET_INFO;
		get_info.action = parameter.action;
		
		// parameters state
		XrActionStateBoolean state = {};
		state.type = XR_TYPE_ACTION_STATE_BOOLEAN;
		if(XR::error(xrGetActionStateBoolean(getSession(), &get_info, &state))) {
			TS_LOGF(Error, "XRInput::getBool(): can't get \"%s\" parameter\n", parameter.name.get());
			return value;
		}
		
		// check parameter
		if(!state.isActive) return value;
		
		// parameter value
		bool ret = (state.currentState != XR_FALSE);
		if(clear && ret) {
			if(parameter.clear) ret = false;
			else parameter.clear = true;
		} else {
			parameter.clear = false;
		}
		
		return ret;
	}
	
	/*
	 */
	uint32_t XRInput::addScalarf32(const char *name, const char *profile, const char *path) {
		return add_parameter(name, XR_ACTION_TYPE_FLOAT_INPUT, profile, path);
	}
	
	float32_t XRInput::getScalarf32(const char *name, float32_t value) const {
		auto it = names.find(name);
		if(it) return getScalarf32(it->data, value);
		return value;
	}
	
	float32_t XRInput::getScalarf32(uint32_t id, float32_t value) const {
		
		// check parameter
		if(id == Maxu32) return value;
		
		// find parameter
		auto it = parameters.find(id);
		if(it == parameters.end()) {
			TS_LOGF(Error, "XRInput::getScalarf32(): can't find %u parameter\n", id);
			return value;
		}
		const Parameter &parameter = it->data;
		
		// get info
		XrActionStateGetInfo get_info = {};
		get_info.type = XR_TYPE_ACTION_STATE_GET_INFO;
		get_info.action = parameter.action;
		
		// parameters state
		XrActionStateFloat state = {};
		state.type = XR_TYPE_ACTION_STATE_FLOAT;
		if(XR::error(xrGetActionStateFloat(getSession(), &get_info, &state))) {
			TS_LOGF(Error, "XRInput::getScalarf32(): can't get \"%s\" parameter\n", parameter.name.get());
			return value;
		}
		
		// check parameter
		if(!state.isActive) return value;
		
		return state.currentState;
	}
	
	/*
	 */
	uint32_t XRInput::addVector2f(const char *name, const char *profile, const char *path) {
		return add_parameter(name, XR_ACTION_TYPE_VECTOR2F_INPUT, profile, path);
	}
	
	Vector2f XRInput::getVector2f(const char *name, const Vector2f &value) const {
		auto it = names.find(name);
		if(it) return getVector2f(it->data, value);
		return value;
	}
	
	Vector2f XRInput::getVector2f(uint32_t id, const Vector2f &value) const {
		
		// check parameter
		if(id == Maxu32) return value;
		
		// find parameter
		auto it = parameters.find(id);
		if(it == parameters.end()) {
			TS_LOGF(Error, "XRInput::getVector2f(): can't find %u parameter\n", id);
			return value;
		}
		const Parameter &parameter = it->data;
		
		// get info
		XrActionStateGetInfo get_info = {};
		get_info.type = XR_TYPE_ACTION_STATE_GET_INFO;
		get_info.action = parameter.action;
		
		// parameters state
		XrActionStateVector2f state = {};
		state.type = XR_TYPE_ACTION_STATE_VECTOR2F;
		if(XR::error(xrGetActionStateVector2f(getSession(), &get_info, &state))) {
			TS_LOGF(Error, "XRInput::getVector2f(): can't get \"%s\" parameter\n", parameter.name.get());
			return value;
		}
		
		// check parameter
		if(!state.isActive) return value;
		
		return XR::toVector2f(state.currentState);
	}
	
	/*
	 */
	uint32_t XRInput::addMatrix4x3f(const char *name, const char *profile, const char *path) {
		return add_parameter(name, XR_ACTION_TYPE_POSE_INPUT, profile, path);
	}
	
	Matrix4x3f XRInput::getMatrix4x3f(const char *name, const Matrix4x3f &value) const {
		auto it = names.find(name);
		if(it) return getMatrix4x3f(it->data, value);
		return value;
	}
	
	Matrix4x3f XRInput::getMatrix4x3f(uint32_t id, const Matrix4x3f &value) const {
		
		// check parameter
		if(id == Maxu32) return value;
		
		// find parameter
		auto it = parameters.find(id);
		if(it == parameters.end()) {
			TS_LOGF(Error, "XRInput::getMatrix4x3f(): can't find %u parameter\n", id);
			return value;
		}
		const Parameter &parameter = it->data;
		
		// get info
		XrActionStateGetInfo get_info = {};
		get_info.type = XR_TYPE_ACTION_STATE_GET_INFO;
		get_info.action = parameter.action;
		
		// parameters state
		XrActionStatePose state = {};
		state.type = XR_TYPE_ACTION_STATE_POSE;
		if(XR::error(xrGetActionStatePose(getSession(), &get_info, &state))) {
			TS_LOGF(Error, "XRInput::getMatrix4x3f(): can't get \"%s\" parameter\n", parameter.name.get());
			return value;
		}
		
		// check parameter
		if(!state.isActive) return value;
		
		// locate parameter
		XrSpaceLocation location = {};
		location.type = XR_TYPE_SPACE_LOCATION;
		XrSpace local_space = system->getSpace(XR_REFERENCE_SPACE_TYPE_LOCAL);
		if(XR::error(xrLocateSpace(parameter.space, local_space, window->getFrameTime(), &location))) {
			TS_LOGF(Error, "XRInput::getMatrix4x3f(): can't locate \"%s\" parameter\n", parameter.name.get());
			return value;
		}
		
		// check location
		if(!(location.locationFlags & XR_SPACE_LOCATION_POSITION_VALID_BIT)) return value;
		if(!(location.locationFlags & XR_SPACE_LOCATION_ORIENTATION_VALID_BIT)) return value;
		
		// current transform
		return Matrix4x3f::rotateX(90.0f) * XR::toMatrix4x3f(location.pose);
	}
}

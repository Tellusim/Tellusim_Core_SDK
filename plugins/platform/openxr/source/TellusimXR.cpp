// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <TellusimBase.h>

#if _WIN32
	#define XR_USE_PLATFORM_WIN32			1
	#define XR_USE_GRAPHICS_API_D3D12		1
	#define XR_USE_GRAPHICS_API_D3D11		1
	#define XR_USE_GRAPHICS_API_VULKAN		1
	#define XR_USE_GRAPHICS_API_OPENGL		1
	#include <d3d12.h>
	#include <d3d11.h>
	#include <vulkan/vulkan.h>
	#include <GL/glcorearb.h>
#elif _LINUX
	#define XR_USE_PLATFORM_XLIB			1
	#define XR_USE_GRAPHICS_API_VULKAN		1
	#define XR_USE_GRAPHICS_API_OPENGL		1
	#include <vulkan/vulkan.h>
	#include <GL/glcorearb.h>
	#include <GL/glx.h>
#elif _ANDROID
	#define XR_USE_PLATFORM_ANDROID			1
	#define XR_USE_GRAPHICS_API_VULKAN		1
	#define XR_USE_GRAPHICS_API_OPENGL_ES	1
	#include <vulkan/vulkan.h>
	#include <GLES3/gl32.h>
	#include <EGL/egl.h>
	#include <android/native_activity.h>
	#include <system/TellusimAndroid.h>
#endif

#include <openxr/openxr_platform.h>

#include <core/TellusimLog.h>
#include <core/TellusimArray.h>
#include <core/TellusimSystem.h>
#include <core/TellusimAtomic.h>
#include <core/TellusimString.h>
#include <platform/TellusimContext.h>
#include <platform/TellusimSurface.h>

#include "../include/TellusimXR.h"

/*
 */
#ifndef TS_XR_ENGINE_NAME
	#define TS_XR_ENGINE_NAME		"TellusimEngine"
	#define TS_XR_ENGINE_VERSION	0x00010001
#endif

#ifndef TS_XR_APP_NAME
	#ifdef TS_APP_NAME
		#define TS_XR_APP_NAME		TS_APP_NAME
	#else
		#define TS_XR_APP_NAME		"TellusimApp"
	#endif
	#define TS_XR_APP_VERSION		0x00010001
#endif

#ifndef TS_XR_API_VERSION
	#define TS_XR_API_VERSION		XR_MAKE_VERSION(1, 0, 26);
#endif

/*
 */
namespace Tellusim {
	
	/*
	 */
	namespace XR {
		
		Atomici32 counter = 0;							// reference counter
		
		void *handle = nullptr;							// library handle
		
		XrInstance instance = XR_NULL_HANDLE;			// instance handle
		
		String instance_layers;							// instance layers
		String instance_extensions;						// instance extensions
		
		XrInstanceProperties instance_properties = {};	// instance properties
		
		Array<XRSystem*> systems;						// instance systems
		
		/*
		 */
		bool retain() {
			counter++;
			return !isOpened();
		}
		
		bool release() {
			TS_ASSERT(counter > 0 && "XR::release(): reference counter is zero");
			return (--counter == 0);
		}
		
		/*
		 */
		bool isOpened() {
			return (instance != XR_NULL_HANDLE);
		}
		
		/*
		 */
		bool open() {
			
			TS_ASSERT(!isOpened() && "XR::open(): is already opened");
			
			// load library
			const char *name = nullptr;
			#if _WIN32
				name = "openxr_loader.dll";
			#elif _LINUX || _ANDROID
				name = "libopenxr_loader.so";
			#else
				TS_LOG(Error, "XR::open(): unknown platform\n");
				close();
				return false;
			#endif
			handle = System::loadLibrary(name);
			if(handle == nullptr) {
				TS_LOGEF(Error, "XR::open(): can't load %s library\n", name);
				close();
				return false;
			}
			
			#define GET_ADDRESS(TYPE, NAME) { \
				void *address = System::getFunction(handle, #NAME); \
				if(address == nullptr) TS_LOGF(Error, "XR::open(): can't find \"%s\" function\n", #NAME); \
				if(address == nullptr) { close(); return false; } \
				NAME = (TYPE)address; \
			}
			
			// OpenXR 10 functions
			GET_ADDRESS(PFN_xrGetInstanceProcAddr, xrGetInstanceProcAddr)
			GET_ADDRESS(PFN_xrEnumerateApiLayerProperties, xrEnumerateApiLayerProperties)
			GET_ADDRESS(PFN_xrEnumerateInstanceExtensionProperties, xrEnumerateInstanceExtensionProperties)
			GET_ADDRESS(PFN_xrCreateInstance, xrCreateInstance)
			GET_ADDRESS(PFN_xrDestroyInstance, xrDestroyInstance)
			GET_ADDRESS(PFN_xrGetInstanceProperties, xrGetInstanceProperties)
			GET_ADDRESS(PFN_xrPollEvent, xrPollEvent)
			GET_ADDRESS(PFN_xrResultToString, xrResultToString)
			GET_ADDRESS(PFN_xrStructureTypeToString, xrStructureTypeToString)
			GET_ADDRESS(PFN_xrGetSystem, xrGetSystem)
			GET_ADDRESS(PFN_xrGetSystemProperties, xrGetSystemProperties)
			GET_ADDRESS(PFN_xrEnumerateEnvironmentBlendModes, xrEnumerateEnvironmentBlendModes)
			GET_ADDRESS(PFN_xrCreateSession, xrCreateSession)
			GET_ADDRESS(PFN_xrDestroySession, xrDestroySession)
			GET_ADDRESS(PFN_xrEnumerateReferenceSpaces, xrEnumerateReferenceSpaces)
			GET_ADDRESS(PFN_xrCreateReferenceSpace, xrCreateReferenceSpace)
			GET_ADDRESS(PFN_xrGetReferenceSpaceBoundsRect, xrGetReferenceSpaceBoundsRect)
			GET_ADDRESS(PFN_xrCreateActionSpace, xrCreateActionSpace)
			GET_ADDRESS(PFN_xrLocateSpace, xrLocateSpace)
			GET_ADDRESS(PFN_xrDestroySpace, xrDestroySpace)
			GET_ADDRESS(PFN_xrEnumerateViewConfigurations, xrEnumerateViewConfigurations)
			GET_ADDRESS(PFN_xrGetViewConfigurationProperties, xrGetViewConfigurationProperties)
			GET_ADDRESS(PFN_xrEnumerateViewConfigurationViews, xrEnumerateViewConfigurationViews)
			GET_ADDRESS(PFN_xrEnumerateSwapchainFormats, xrEnumerateSwapchainFormats)
			GET_ADDRESS(PFN_xrCreateSwapchain, xrCreateSwapchain)
			GET_ADDRESS(PFN_xrDestroySwapchain, xrDestroySwapchain)
			GET_ADDRESS(PFN_xrEnumerateSwapchainImages, xrEnumerateSwapchainImages)
			GET_ADDRESS(PFN_xrAcquireSwapchainImage, xrAcquireSwapchainImage)
			GET_ADDRESS(PFN_xrWaitSwapchainImage, xrWaitSwapchainImage)
			GET_ADDRESS(PFN_xrReleaseSwapchainImage, xrReleaseSwapchainImage)
			GET_ADDRESS(PFN_xrBeginSession, xrBeginSession)
			GET_ADDRESS(PFN_xrEndSession, xrEndSession)
			GET_ADDRESS(PFN_xrRequestExitSession, xrRequestExitSession)
			GET_ADDRESS(PFN_xrWaitFrame, xrWaitFrame)
			GET_ADDRESS(PFN_xrBeginFrame, xrBeginFrame)
			GET_ADDRESS(PFN_xrEndFrame, xrEndFrame)
			GET_ADDRESS(PFN_xrLocateViews, xrLocateViews)
			GET_ADDRESS(PFN_xrStringToPath, xrStringToPath)
			GET_ADDRESS(PFN_xrPathToString, xrPathToString)
			GET_ADDRESS(PFN_xrCreateActionSet, xrCreateActionSet)
			GET_ADDRESS(PFN_xrDestroyActionSet, xrDestroyActionSet)
			GET_ADDRESS(PFN_xrCreateAction, xrCreateAction)
			GET_ADDRESS(PFN_xrDestroyAction, xrDestroyAction)
			GET_ADDRESS(PFN_xrSuggestInteractionProfileBindings, xrSuggestInteractionProfileBindings)
			GET_ADDRESS(PFN_xrAttachSessionActionSets, xrAttachSessionActionSets)
			GET_ADDRESS(PFN_xrGetCurrentInteractionProfile, xrGetCurrentInteractionProfile)
			GET_ADDRESS(PFN_xrGetActionStateBoolean, xrGetActionStateBoolean)
			GET_ADDRESS(PFN_xrGetActionStateFloat, xrGetActionStateFloat)
			GET_ADDRESS(PFN_xrGetActionStateVector2f, xrGetActionStateVector2f)
			GET_ADDRESS(PFN_xrGetActionStatePose, xrGetActionStatePose)
			GET_ADDRESS(PFN_xrSyncActions, xrSyncActions)
			GET_ADDRESS(PFN_xrEnumerateBoundSourcesForAction, xrEnumerateBoundSourcesForAction)
			GET_ADDRESS(PFN_xrGetInputSourceLocalizedName, xrGetInputSourceLocalizedName)
			GET_ADDRESS(PFN_xrApplyHapticFeedback, xrApplyHapticFeedback)
			GET_ADDRESS(PFN_xrStopHapticFeedback, xrStopHapticFeedback)
			
			#undef GET_ADDRESS
			
			// KHR loader init
			#if _ANDROID
				if(error(xrGetInstanceProcAddr(instance, "xrInitializeLoaderKHR", (PFN_xrVoidFunction*)&xrInitializeLoaderKHR))) {
					TS_LOGF(Error, "XR::open(): can't find \"%s\" function\n", "xrInitializeLoaderKHR");
					close();
					return false;
				}
			#endif
			
			// initialize loader
			#if _ANDROID
				ANativeActivity *activity = Android::getActivity();
				XrLoaderInitInfoAndroidKHR loader_info = {};
				loader_info.type = XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR;
				loader_info.applicationVM = activity->vm;
				loader_info.applicationContext = activity->clazz;
				if(error(xrInitializeLoaderKHR((XrLoaderInitInfoBaseHeaderKHR*)&loader_info))) {
					TS_LOG(Error, "XR::open(): can't initialize OpenXR\n");
					close();
					return false;
				}
			#endif
			
			// enabled instance layers
			static const char *enabled_layers[] = {
				nullptr,
			};
			
			// enumerate instance layers
			uint32_t num_instance_layers = 0;
			if(error(xrEnumerateApiLayerProperties(0, &num_instance_layers, nullptr))) {
				TS_LOG(Error, "XR::open(): can't get instance layers count\n");
				close();
				return false;
			}
			Array<XrApiLayerProperties> instance_layer_properties(num_instance_layers);
			for(XrApiLayerProperties &properties : instance_layer_properties) {
				properties.type = XR_TYPE_API_LAYER_PROPERTIES;
				properties.next = nullptr;
			}
			if(error(xrEnumerateApiLayerProperties(num_instance_layers, &num_instance_layers, instance_layer_properties.get()))) {
				TS_LOG(Error, "XR::open(): can't get instance layers\n");
				close();
				return false;
			}
			for(uint32_t i = 0; i < instance_layer_properties.size(); i++) {
				if(instance_layers) instance_layers += ' ';
				const char *name = instance_layer_properties[i].layerName;
				if(!strncmp(name, "XR_LAYER_", 9)) instance_layers += name + 9;
				else instance_layers += name;
			}
			
			// enabled instance layers
			Array<const char*> enabled_instance_layers;
			for(uint32_t i = 0; enabled_layers[i]; i++) {
				if(!checkLayer(enabled_layers[i])) continue;
				enabled_instance_layers.append(enabled_layers[i]);
			}
			
			// enabled instance extensions
			static const char *enabled_extensions[] = {
				#if XR_KHR_D3D12_enable
					XR_KHR_D3D12_ENABLE_EXTENSION_NAME,
				#endif
				#if XR_KHR_D3D11_enable
					XR_KHR_D3D11_ENABLE_EXTENSION_NAME,
				#endif
				#if XR_KHR_vulkan_enable
					XR_KHR_VULKAN_ENABLE_EXTENSION_NAME,
				#endif
				#if XR_KHR_opengl_enable
					XR_KHR_OPENGL_ENABLE_EXTENSION_NAME,
				#endif
				#if XR_KHR_opengl_es_enable
					XR_KHR_OPENGL_ES_ENABLE_EXTENSION_NAME,
				#endif
				nullptr,
			};
			
			// enumerate instance extensions
			uint32_t num_instance_extensions = 0;
			if(error(xrEnumerateInstanceExtensionProperties(XR_NULL_HANDLE, 0, &num_instance_extensions, nullptr))) {
				TS_LOG(Error, "XR::open(): can't get instance extensions count\n");
				close();
				return false;
			}
			Array<XrExtensionProperties> instance_extension_properties(num_instance_extensions);
			for(XrExtensionProperties &properties : instance_extension_properties) {
				properties.type = XR_TYPE_EXTENSION_PROPERTIES;
				properties.next = nullptr;
			}
			if(error(xrEnumerateInstanceExtensionProperties(XR_NULL_HANDLE, num_instance_extensions, &num_instance_extensions, instance_extension_properties.get()))) {
				TS_LOG(Error, "XR::open(): can't get instance extensions\n");
				close();
				return false;
			}
			for(uint32_t i = 0; i < instance_extension_properties.size(); i++) {
				if(instance_extensions) instance_extensions += ' ';
				const char *name = instance_extension_properties[i].extensionName;
				if(!strncmp(name, "XR_", 3)) instance_extensions += name + 3;
				else instance_extensions += name;
			}
			
			// enabled instance extensions
			Array<const char*> enabled_instance_extensions;
			for(uint32_t i = 0; enabled_extensions[i]; i++) {
				if(!checkExtension(enabled_extensions[i])) continue;
				enabled_instance_extensions.append(enabled_extensions[i]);
			}
			
			// instance info
			XrInstanceCreateInfo instance_info = {};
			instance_info.type = XR_TYPE_INSTANCE_CREATE_INFO;
			instance_info.enabledApiLayerCount = enabled_instance_layers.size();
			instance_info.enabledApiLayerNames = enabled_instance_layers.get();
			instance_info.enabledExtensionCount = enabled_instance_extensions.size();
			instance_info.enabledExtensionNames = enabled_instance_extensions.get();
			
			// application info
			XrApplicationInfo &application_info = instance_info.applicationInfo;
			strncpy(application_info.applicationName, TS_XR_APP_NAME, sizeof(application_info.applicationName));
			application_info.applicationVersion = TS_XR_APP_VERSION;
			strncpy(application_info.engineName, TS_XR_ENGINE_NAME, sizeof(application_info.engineName));
			application_info.engineVersion = TS_XR_ENGINE_VERSION;
			application_info.apiVersion = TS_XR_API_VERSION;
			
			// create instance
			if(error(xrCreateInstance(&instance_info, &instance))) {
				TS_LOG(Error, "XR::open(): can't create OpenXR instance\n");
				close();
				return false;
			}
			
			// get instance properties
			instance_properties.type = XR_TYPE_INSTANCE_PROPERTIES;
			instance_properties.next = nullptr;
			if(error(xrGetInstanceProperties(instance, &instance_properties))) {
				TS_LOG(Error, "XR::open(): can't get instance properties\n");
				close();
				return false;
			}
			
			// head mounted system
			XrSystemId hmd_system = 0;
			XrSystemGetInfo hmd_system_info = {};
			hmd_system_info.type = XR_TYPE_SYSTEM_GET_INFO;
			hmd_system_info.formFactor = XR_FORM_FACTOR_HEAD_MOUNTED_DISPLAY;
			if(xrGetSystem(instance, &hmd_system_info, &hmd_system) == XR_SUCCESS) {
				XRSystem *system = new XRSystem(hmd_system, hmd_system_info.formFactor);
				TS_LOG(Verbose, "XR::open(): creating HMD system\n");
				addSystem(system);
			}
			
			// handheld system
			XrSystemId hhd_system = 0;
			XrSystemGetInfo hhd_system_info = {};
			hhd_system_info.type = XR_TYPE_SYSTEM_GET_INFO;
			hhd_system_info.formFactor = XR_FORM_FACTOR_HANDHELD_DISPLAY;
			if(xrGetSystem(instance, &hhd_system_info, &hhd_system) == XR_SUCCESS) {
				XRSystem *system = new XRSystem(hhd_system, hhd_system_info.formFactor);
				TS_LOG(Verbose, "XR::open(): creating HHD system\n");
				addSystem(system);
			}
			
			// check systems
			if(getNumSystems() == 0) {
				TS_LOG(Error, "XR::open(): no OpenXR systems are available\n");
				close();
				return false;
			}
			
			// extension functions
			#define GET_ADDRESS(NAME) xrGetInstanceProcAddr(instance, #NAME, (PFN_xrVoidFunction*)&NAME);
			
			#if XR_KHR_android_thread_settings
				GET_ADDRESS(xrSetAndroidApplicationThreadKHR)
			#endif
			#if XR_KHR_android_surface_swapchain
				GET_ADDRESS(xrCreateSwapchainAndroidSurfaceKHR)
			#endif
			#if XR_KHR_opengl_enable
				GET_ADDRESS(xrGetOpenGLGraphicsRequirementsKHR)
			#endif
			#if XR_KHR_opengl_es_enable
				GET_ADDRESS(xrGetOpenGLESGraphicsRequirementsKHR)
			#endif
			#if XR_KHR_vulkan_enable
				GET_ADDRESS(xrGetVulkanInstanceExtensionsKHR)
				GET_ADDRESS(xrGetVulkanDeviceExtensionsKHR)
				GET_ADDRESS(xrGetVulkanGraphicsDeviceKHR)
				GET_ADDRESS(xrGetVulkanGraphicsRequirementsKHR)
			#endif
			#if XR_KHR_D3D11_enable
				GET_ADDRESS(xrGetD3D11GraphicsRequirementsKHR)
			#endif
			#if XR_KHR_D3D12_enable
				GET_ADDRESS(xrGetD3D12GraphicsRequirementsKHR)
			#endif
			
			#undef GET_ADDRESS
			
			return true;
		}
		
		/*
		 */
		void close() {
			
			// release systems
			for(uint32_t i = 0; i < systems.size(); i++) {
				delete systems[i];
			}
			systems.clear();
			
			// release instance
			if(instance && error(xrDestroyInstance(instance))) {
				TS_LOG(Error, "XRSystem::release(): can't release instance\n");
			}
			instance = XR_NULL_HANDLE;
			
			// close library
			if(handle != nullptr) {
				System::closeLibrary(handle);
				handle = nullptr;
			}
			
			// clear instance info
			instance_layers.clear();
			instance_extensions.clear();
		}
		
		/*
		 */
		XrInstance getInstance() {
			return instance;
		}
		
		const String &getLayers() {
			return instance_layers;
		}
		
		const String &getExtensions() {
			return instance_extensions;
		}
		
		bool checkLayer(const char *name) {
			if(!strncmp(name, "XR_LAYER_", 9)) name += 9;
			return instance_layers.contains(name);
		}
		
		bool checkExtension(const char *name) {
			if(!strncmp(name, "XR_", 3)) name += 3;
			return instance_extensions.contains(name);
		}
		
		const XrInstanceProperties &getProperties() {
			return instance_properties;
		}
		
		/*
		 */
		uint32_t getNumSystems() {
			return systems.size();
		}
		
		void addSystem(XRSystem *system) {
			systems.append(system);
		}
		
		XRSystem *getSystem(uint32_t index) {
			if(index < systems.size()) return systems[index];
			TS_LOGF(Error, "XR::getSystem(): invalid system index %u\n", index);
			return nullptr;
		}
		
		/*
		 */
		Matrix4x3f toMatrix4x3f(const XrPosef &pose) {
			Matrix4x3f translate = Matrix4x3f::translate(pose.position.x, pose.position.y, pose.position.z);
			Quaternionf rotate = Quaternionf(pose.orientation.x, pose.orientation.y, pose.orientation.z, pose.orientation.w);
			return translate * Matrix4x3f(rotate);
		}
		
		/*
		 */
		bool error(XrResult result) {
			const char *str = nullptr;
			switch((int32_t)result) {
				case XR_SUCCESS: return false;
				case XR_TIMEOUT_EXPIRED: str = "timeout expired"; break;
				case XR_SESSION_LOSS_PENDING: str = "session loss pending"; break;
				case XR_EVENT_UNAVAILABLE: str = "event unavailable"; break;
				case XR_SPACE_BOUNDS_UNAVAILABLE: str = "space bounds unavailable"; break;
				case XR_SESSION_NOT_FOCUSED: str = "session not focused"; break;
				case XR_FRAME_DISCARDED: str = "frame discarded"; break;
				case XR_ERROR_VALIDATION_FAILURE: str = "validation failure"; break;
				case XR_ERROR_RUNTIME_FAILURE: str = "runtime failure"; break;
				case XR_ERROR_OUT_OF_MEMORY: str = "out of memory"; break;
				case XR_ERROR_API_VERSION_UNSUPPORTED: str = "api version unsupported"; break;
				case XR_ERROR_INITIALIZATION_FAILED: str = "initialization failed"; break;
				case XR_ERROR_FUNCTION_UNSUPPORTED: str = "function unsupported"; break;
				case XR_ERROR_FEATURE_UNSUPPORTED: str = "feature unsupported"; break;
				case XR_ERROR_EXTENSION_NOT_PRESENT: str = "extension not present"; break;
				case XR_ERROR_LIMIT_REACHED: str = "limit reached"; break;
				case XR_ERROR_SIZE_INSUFFICIENT: str = "size insufficient"; break;
				case XR_ERROR_HANDLE_INVALID: str = "handle invalid"; break;
				case XR_ERROR_INSTANCE_LOST: str = "instance lost"; break;
				case XR_ERROR_SESSION_RUNNING: str = "session running"; break;
				case XR_ERROR_SESSION_NOT_RUNNING: str = "session not running"; break;
				case XR_ERROR_SESSION_LOST: str = "session lost"; break;
				case XR_ERROR_SYSTEM_INVALID: str = "system invalid"; break;
				case XR_ERROR_PATH_INVALID: str = "path invalid"; break;
				case XR_ERROR_PATH_COUNT_EXCEEDED: str = "path count exceeded"; break;
				case XR_ERROR_PATH_FORMAT_INVALID: str = "path format invalid"; break;
				case XR_ERROR_PATH_UNSUPPORTED: str = "path unsupported"; break;
				case XR_ERROR_LAYER_INVALID: str = "layer invalid"; break;
				case XR_ERROR_LAYER_LIMIT_EXCEEDED: str = "layer limit exceeded"; break;
				case XR_ERROR_SWAPCHAIN_RECT_INVALID: str = "swapchain rect invalid"; break;
				case XR_ERROR_SWAPCHAIN_FORMAT_UNSUPPORTED: str = "swapchain format unsupported"; break;
				case XR_ERROR_ACTION_TYPE_MISMATCH: str = "action type mismatch"; break;
				case XR_ERROR_SESSION_NOT_READY: str = "session not ready"; break;
				case XR_ERROR_SESSION_NOT_STOPPING: str = "session not stopping"; break;
				case XR_ERROR_TIME_INVALID: str = "time invalid"; break;
				case XR_ERROR_REFERENCE_SPACE_UNSUPPORTED: str = "reference space unsupported"; break;
				case XR_ERROR_FILE_ACCESS_ERROR: str = "file access error"; break;
				case XR_ERROR_FILE_CONTENTS_INVALID: str = "file contents invalid"; break;
				case XR_ERROR_FORM_FACTOR_UNSUPPORTED: str = "form factor unsupported"; break;
				case XR_ERROR_FORM_FACTOR_UNAVAILABLE: str = "form factor unavailable"; break;
				case XR_ERROR_API_LAYER_NOT_PRESENT: str = "api layer not present"; break;
				case XR_ERROR_CALL_ORDER_INVALID: str = "call order invalid"; break;
				case XR_ERROR_GRAPHICS_DEVICE_INVALID: str = "graphics device invalid"; break;
				case XR_ERROR_POSE_INVALID: str = "pose invalid"; break;
				case XR_ERROR_INDEX_OUT_OF_RANGE: str = "index out of range"; break;
				case XR_ERROR_VIEW_CONFIGURATION_TYPE_UNSUPPORTED: str = "view configuration type unsupported"; break;
				case XR_ERROR_ENVIRONMENT_BLEND_MODE_UNSUPPORTED: str = "environment blend mode unsupported"; break;
				case XR_ERROR_NAME_DUPLICATED: str = "name duplicated"; break;
				case XR_ERROR_NAME_INVALID: str = "name invalid"; break;
				case XR_ERROR_ACTIONSET_NOT_ATTACHED: str = "actionset not attached"; break;
				case XR_ERROR_ACTIONSETS_ALREADY_ATTACHED: str = "actionsets already attached"; break;
				case XR_ERROR_LOCALIZED_NAME_DUPLICATED: str = "localized name duplicated"; break;
				case XR_ERROR_LOCALIZED_NAME_INVALID: str = "localized name invalid"; break;
				case XR_ERROR_GRAPHICS_REQUIREMENTS_CALL_MISSING: str = "graphics requirements call missing"; break;
				case XR_ERROR_RUNTIME_UNAVAILABLE: str = "runtime unavailable"; break;
			}
			if(str) TS_LOGF(Error, "XR::error(): %s\n", str);
			else TS_LOGF(Error, "XR::error(): 0x%08x\n", result);
			return true;
		}
	}
	
	/*****************************************************************************\
	 *
	 * OpenXR System
	 *
	\*****************************************************************************/
	
	/*
	 */
	XRSystem::XRSystem(XrSystemId system, XrFormFactor type) : system(system), system_type(type) {
		
		// system properties
		system_properties.type = XR_TYPE_SYSTEM_PROPERTIES;
		system_properties.next = nullptr;
		if(XR::error(xrGetSystemProperties(XR::getInstance(), getSystem(), &system_properties))) {
			TS_LOG(Error, "XRSystem::XRSystem(): can't get system properties\n");
			return;
		}
		
		// view types
		uint32_t num_view_types = 0;
		if(XR::error(xrEnumerateViewConfigurations(XR::getInstance(), getSystem(), 0, &num_view_types, nullptr)) || num_view_types == 0) {
			TS_LOG(Error, "XRSystem::XRSystem(): can't get view types\n");
			return;
		}
		view_types.resize(num_view_types);
		view_modes.resize(num_view_types);
		if(XR::error(xrEnumerateViewConfigurations(XR::getInstance(), getSystem(), num_view_types, &num_view_types, view_types.get()))) {
			TS_LOG(Error, "XRSystem::XRSystem(): can't get view types\n");
			return;
		}
		
		// view modes
		for(uint32_t i = 0; i < num_view_types; i++) {
			uint32_t num_view_modes = 0;
			if(XR::error(xrEnumerateViewConfigurationViews(XR::getInstance(), getSystem(), view_types[i], 0, &num_view_modes, nullptr)) || num_view_modes == 0) {
				TS_LOG(Error, "XRSystem::XRSystem(): can't get view modes\n");
				return;
			}
			view_modes[i].resize(num_view_modes);
			for(uint32_t j = 0; j < num_view_modes; j++) {
				view_modes[i][j].type = XR_TYPE_VIEW_CONFIGURATION_VIEW;
				view_modes[i][j].next = nullptr;
			}
			if(XR::error(xrEnumerateViewConfigurationViews(XR::getInstance(), getSystem(), view_types[i], num_view_modes, &num_view_modes, view_modes[i].get()))) {
				TS_LOG(Error, "XRSystem::XRSystem(): can't get view modes\n");
				return;
			}
		}
	}
	
	XRSystem::~XRSystem() {
		
		release();
	}
	
	/*
	 */
	bool XRSystem::isCreated() const {
		return (getSession() != XR_NULL_HANDLE);
	}
	
	/*
	 */
	bool XRSystem::create(Context &context) {
		
		TS_ASSERT(!isCreated() && "XRSystem::create(): is already created");
		
		// current platform
		platform = context.getPlatform();
		
		// initialize extensions
		#if XR_KHR_vulkan_enable
			
			// Vulkan context extensions
			if(platform == PlatformVK) {
				uint32_t size = 0;
				if(xrGetVulkanInstanceExtensionsKHR == nullptr) {
					TS_LOGF(Error, "XRSystem::create(): can't get %s function\n", "xrGetVulkanInstanceExtensionsKHR");
					return false;
				}
				if(XR::error(xrGetVulkanInstanceExtensionsKHR(XR::getInstance(), getSystem(), 0, &size, nullptr))) {
					TS_LOG(Error, "XRSystem::create(): can't get instance extensions\n");
					return false;
				}
				String extensions(size, '\0');
				if(XR::error(xrGetVulkanInstanceExtensionsKHR(XR::getInstance(), getSystem(), size, &size, extensions.get()))) {
					TS_LOG(Error, "XRSystem::create(): can't get instance extensions\n");
					return false;
				}
				for(uint32_t i = 0, j = 0; i < size; i++) {
					if(extensions[i] == ' ') extensions[i] = '\0';
					if(extensions[i] == '\0') {
						if(j < i) VKContext::addContextExtension(extensions.get() + j);
						j = i + 1;
					}
				}
			}
			
			// Vulkan adapter extensions
			if(platform == PlatformVK) {
				uint32_t size = 0;
				if(xrGetVulkanDeviceExtensionsKHR == nullptr) {
					TS_LOGF(Error, "XRSystem::create(): can't get %s function\n", "xrGetVulkanDeviceExtensionsKHR");
					return false;
				}
				if(XR::error(xrGetVulkanDeviceExtensionsKHR(XR::getInstance(), getSystem(), 0, &size, nullptr))) {
					TS_LOG(Error, "XRSystem::create(): can't get device extensions\n");
					return false;
				}
				String extensions(size, '\0');
				if(XR::error(xrGetVulkanDeviceExtensionsKHR(XR::getInstance(), getSystem(), size, &size, extensions.get()))) {
					TS_LOG(Error, "XRSystem::create(): can't get device extensions\n");
					return false;
				}
				for(uint32_t i = 0, j = 0; i < size; i++) {
					if(extensions[i] == ' ') extensions[i] = '\0';
					if(extensions[i] == '\0') {
						if(j < i) VKContext::addAdapterExtension(extensions.get() + j);
						j = i + 1;
					}
				}
			}
			
		#endif
		
		// create context
		if(!context.isCreated() && !context.create()) {
			TS_LOG(Error, "XRSystem::create(): can't create context\n");
			return false;
		}
		
		// graphics bindings
		void *binding_ptr = nullptr;
		#if _WIN32
			XrGraphicsBindingD3D12KHR d3d12_binding = {};
			XrGraphicsBindingD3D11KHR d3d11_binding = {};
			XrGraphicsRequirementsD3D12KHR d3d12_requirements = {};
			XrGraphicsRequirementsD3D11KHR d3d11_requirements = {};
			if(platform == PlatformD3D12) {
				d3d12_requirements.type = XR_TYPE_GRAPHICS_REQUIREMENTS_D3D12_KHR;
				if(xrGetD3D12GraphicsRequirementsKHR == nullptr) {
					TS_LOGF(Error, "XRSystem::create(): can't get %s function\n", "xrGetD3D12GraphicsRequirementsKHR");
					return false;
				}
				if(XR::error(xrGetD3D12GraphicsRequirementsKHR(XR::getInstance(), getSystem(), &d3d12_requirements))) {
					TS_LOGF(Error, "XRSystem::create(): can't get %s graphics requirements\n", getPlatformName(platform));
					release();
					return false;
				}
				D3D12Context d3d12_context = D3D12Context(context);
				d3d12_binding.type = XR_TYPE_GRAPHICS_BINDING_D3D12_KHR;
				d3d12_binding.device = d3d12_context.getDevice();
				d3d12_binding.queue = d3d12_context.getQueue();
				binding_ptr = &d3d12_binding;
			}
			else if(platform == PlatformD3D11) {
				d3d11_requirements.type = XR_TYPE_GRAPHICS_REQUIREMENTS_D3D11_KHR;
				if(xrGetD3D11GraphicsRequirementsKHR == nullptr) {
					TS_LOGF(Error, "XRSystem::create(): can't get %s function\n", "xrGetD3D11GraphicsRequirementsKHR");
					return false;
				}
				if(XR::error(xrGetD3D11GraphicsRequirementsKHR(XR::getInstance(), getSystem(), &d3d11_requirements))) {
					TS_LOGF(Error, "XRSystem::create(): can't get %s graphics requirements\n", getPlatformName(platform));
					release();
					return false;
				}
				D3D11Context d3d11_context = D3D11Context(context);
				d3d11_binding.type = XR_TYPE_GRAPHICS_BINDING_D3D11_KHR;
				d3d11_binding.device = d3d11_context.getDevice();
				binding_ptr = &d3d11_binding;
			}
		#endif
		#if _WIN32 || _LINUX || _ANDROID
			XrGraphicsBindingVulkanKHR vk_binding = {};
			XrGraphicsRequirementsVulkanKHR vk_requirements = {};
			if(platform == PlatformVK) {
				vk_requirements.type = XR_TYPE_GRAPHICS_REQUIREMENTS_VULKAN_KHR;
				if(xrGetVulkanGraphicsRequirementsKHR == nullptr) {
					TS_LOGF(Error, "XRSystem::create(): can't get %s function\n", "xrGetVulkanGraphicsRequirementsKHR");
					return false;
				}
				if(XR::error(xrGetVulkanGraphicsRequirementsKHR(XR::getInstance(), getSystem(), &vk_requirements))) {
					TS_LOGF(Error, "XRSystem::create(): can't get %s graphics requirements\n", getPlatformName(platform));
					release();
					return false;
				}
				VKContext vk_context = VKContext(context);
				VkPhysicalDevice vk_adapter = VK_NULL_HANDLE;
				if(xrGetVulkanGraphicsDeviceKHR == nullptr) {
					TS_LOGF(Error, "XRSystem::create(): can't get %s function\n", "xrGetVulkanGraphicsDeviceKHR");
					return false;
				}
				if(XR::error(xrGetVulkanGraphicsDeviceKHR(XR::getInstance(), getSystem(), vk_context.getInstance(), &vk_adapter))) {
					TS_LOGF(Error, "XRSystem::create(): can't get %s physical device\n", getPlatformName(platform));
					release();
					return false;
				}
				if(vk_adapter != vk_context.getAdapter()) {
					TS_LOGF(Error, "XRSystem::create(): invalid %s physical device\n", getPlatformName(platform));
					release();
					return false;
				}
				vk_binding.type = XR_TYPE_GRAPHICS_BINDING_VULKAN_KHR;
				vk_binding.instance = vk_context.getInstance();
				vk_binding.physicalDevice = vk_context.getAdapter();
				vk_binding.device = vk_context.getDevice();
				vk_binding.queueFamilyIndex = vk_context.getFamily();
				vk_binding.queueIndex = 0;
				binding_ptr = &vk_binding;
			}
		#endif
		#if _WIN32
			XrGraphicsBindingOpenGLWin32KHR gl_binding = {};
			XrGraphicsRequirementsOpenGLKHR gl_requirements = {};
			if(platform == PlatformGL) {
				gl_requirements.type = XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_KHR;
				if(xrGetOpenGLGraphicsRequirementsKHR == nullptr) {
					TS_LOGF(Error, "XRSystem::create(): can't get %s function\n", "xrGetOpenGLGraphicsRequirementsKHR");
					return false;
				}
				if(XR::error(xrGetOpenGLGraphicsRequirementsKHR(XR::getInstance(), getSystem(), &gl_requirements))) {
					TS_LOGF(Error, "XRSystem::create(): can't get %s graphics requirements\n", getPlatformName(platform));
					release();
					return false;
				}
				GLContext gl_context = GLContext(context);
				gl_binding.type = XR_TYPE_GRAPHICS_BINDING_OPENGL_WIN32_KHR;
				gl_binding.hDC = (HDC)gl_context.getGLSurface();
				gl_binding.hGLRC = (HGLRC)gl_context.getGLContext();
				binding_ptr = &gl_binding;
			}
		#endif
		#if _LINUX
			XrGraphicsBindingOpenGLXlibKHR gl_binding = {};
			XrGraphicsRequirementsOpenGLKHR gl_requirements = {};
			if(platform == PlatformGL) {
				gl_requirements.type = XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_KHR;
				if(xrGetOpenGLGraphicsRequirementsKHR == nullptr) {
					TS_LOGF(Error, "XRSystem::create(): can't get %s function\n", "xrGetOpenGLGraphicsRequirementsKHR");
					return false;
				}
				if(XR::error(xrGetOpenGLGraphicsRequirementsKHR(XR::getInstance(), getSystem(), &gl_requirements))) {
					TS_LOGF(Error, "XRSystem::create(): can't get %s graphics requirements\n", getPlatformName(platform));
					release();
					return false;
				}
				GLContext gl_context = GLContext(context);
				if(gl_context.getGLVisual() && gl_context.getGLSurface()) {
					gl_binding.type = XR_TYPE_GRAPHICS_BINDING_OPENGL_XLIB_KHR;
					gl_binding.xDisplay = (Display*)gl_context.getGLDisplay();
					gl_binding.visualid = ((XVisualInfo*)gl_context.getGLVisual())->visualid;
					gl_binding.glxFBConfig = (GLXFBConfig)gl_context.getGLConfig();
					gl_binding.glxDrawable = (GLXDrawable)*((::Window*)gl_context.getGLSurface());
					gl_binding.glxContext = (GLXContext)gl_context.getGLContext();
					binding_ptr = &gl_binding;
				}
			}
		#endif
		#if _ANDROID
			XrGraphicsBindingOpenGLESAndroidKHR gles_binding = {};
			XrGraphicsRequirementsOpenGLESKHR gles_requirements = {};
			if(platform == PlatformGLES) {
				gles_requirements.type = XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_ES_KHR;
				if(xrGetOpenGLESGraphicsRequirementsKHR == nullptr) {
					TS_LOGF(Error, "XRSystem::create(): can't get %s function\n", "xrGetOpenGLESGraphicsRequirementsKHR");
					return false;
				}
				if(XR::error(xrGetOpenGLESGraphicsRequirementsKHR(XR::getInstance(), getSystem(), &gles_requirements))) {
					TS_LOGF(Error, "XRSystem::create(): can't get %s graphics requirements\n", getPlatformName(platform));
					release();
					return false;
				}
				GLESContext gles_context = GLESContext(context);
				gles_binding.type = XR_TYPE_GRAPHICS_BINDING_OPENGL_ES_ANDROID_KHR;
				gles_binding.display = (EGLDisplay)gles_context.getGLESDisplay();
				gles_binding.config = (EGLConfig)gles_context.getGLESConfig();
				gles_binding.context = (EGLContext)gles_context.getGLESContext();
				binding_ptr = &gles_binding;
			}
		#endif
		if(binding_ptr == nullptr) {
			TS_LOGF(Error, "XRSystem::create(): unknown platform %s\n", getPlatformName(platform));
			release();
			return false;
		}
		
		// create session
		XrSessionCreateInfo session_info = {};
		session_info.type = XR_TYPE_SESSION_CREATE_INFO;
		session_info.next = binding_ptr;
		session_info.createFlags = 0;
		session_info.systemId = getSystem();
		if(XR::error(xrCreateSession(XR::getInstance(), &session_info, &session))) {
			TS_LOG(Error, "XRSystem::create(): can't create session\n");
			release();
			return false;
		}
		
		// enumarate space types
		uint32_t num_space_types = 0;
		if(XR::error(xrEnumerateReferenceSpaces(getSession(), 0, &num_space_types, nullptr)) || num_space_types == 0) {
			TS_LOG(Error, "XRSystem::create(): can't get space types\n");
			release();
			return false;
		}
		space_types.resize(num_space_types);
		if(XR::error(xrEnumerateReferenceSpaces(getSession(), num_space_types, &num_space_types, space_types.get()))) {
			TS_LOG(Error, "XRSystem::create(): can't get space types\n");
			release();
			return false;
		}
		
		// space info
		XrReferenceSpaceCreateInfo space_info = {};
		space_info.type = XR_TYPE_REFERENCE_SPACE_CREATE_INFO;
		space_info.poseInReferenceSpace.orientation.w = 1.0f;
		
		// create spaces
		spaces.resize(getNumSpaces(), XR_NULL_HANDLE);
		for(uint32_t i = 0; i < getNumSpaces(); i++) {
			space_info.referenceSpaceType = space_types[i];
			if(XR::error(xrCreateReferenceSpace(getSession(), &space_info, &spaces[i]))) {
				TS_LOG(Error, "XRSystem::create(): can't create space\n");
				release();
				return false;
			}
		}
		
		// enumerate swap chain formats
		uint32_t num_formats = 0;
		if(XR::error(xrEnumerateSwapchainFormats(getSession(), 0, &num_formats, nullptr)) || num_formats == 0) {
			TS_LOG(Error, "XRSystem::create(): can't get swap chain formats\n");
			release();
			return false;
		}
		formats.resize(num_formats, (int64_t)0);
		if(XR::error(xrEnumerateSwapchainFormats(getSession(), num_formats, &num_formats, formats.get()))) {
			TS_LOG(Error, "XRSystem::create(): can't get swap chain formats\n");
			release();
			return false;
		}
		
		return true;
	}
	
	void XRSystem::release() {
		
		// clear spaces
		for(XrSpace space : spaces) {
			if(XR::error(xrDestroySpace(space))) {
				TS_LOG(Error, "XRSystem::release(): can't release space\n");
			}
		}
		space_types.clear();
		spaces.clear();
		
		// clear formats
		formats.clear();
		
		// release session
		if(session && XR::error(xrDestroySession(session))) {
			TS_LOG(Error, "XRSystem::release(): can't release session\n");
		}
		session = XR_NULL_HANDLE;
		platform = PlatformUnknown;
	}
	
	/*
	 */
	const XrSystemProperties &XRSystem::getProperties() const {
		return system_properties;
	}
	
	/*
	 */
	uint32_t XRSystem::getNumViewTypes() const {
		return view_types.size();
	}
	
	uint32_t XRSystem::getNumViewModes(uint32_t index) const {
		TS_ASSERT(index < view_modes.size() && "XRSystem::getNumViewModes(): invalid index");
		return view_modes[index].size();
	}
	
	XrViewConfigurationType XRSystem::getViewType(uint32_t index) const {
		TS_ASSERT(index < view_types.size() && "XRSystem::getViewType(): invalid index");
		return view_types[index];
	}
	
	const Array<XrViewConfigurationType> &XRSystem::getViewTypes() const {
		return view_types;
	}
	
	const Array<XrViewConfigurationView> &XRSystem::getViewModes(uint32_t index) const {
		TS_ASSERT(index < view_modes.size() && "XRSystem::getViewModes(): invalid index");
		return view_modes[index];
	}
	
	const XrViewConfigurationView &XRSystem::getViewMode(uint32_t index, uint32_t num) const {
		TS_ASSERT(index < view_modes.size() && "XRSystem::getViewMode(): invalid index");
		TS_ASSERT(num < view_modes[index].size() && "XRSystem::getViewMode(): invalid index");
		return view_modes[index][num];
	}
	
	/*
	 */
	uint32_t XRSystem::getNumSpaces() const {
		return space_types.size();
	}
	
	const Array<XrReferenceSpaceType> &XRSystem::getSpaceTypes() const {
		return space_types;
	}
	
	XrSpace XRSystem::getSpace(XrReferenceSpaceType type) const {
		uint32_t index = space_types.findIndex(type);
		if(index != Maxu32) return spaces[index];
		return XR_NULL_HANDLE;
	}
	
	XrSpace XRSystem::getSpace(uint32_t index) const {
		TS_ASSERT(index < spaces.size() && "XRSystem::getSpace(): invalid index");
		return spaces[index];
	}
	
	/*
	 */
	const Array<int64_t> &XRSystem::getFormats() const {
		return formats;
	}
	
	int64_t XRSystem::getFormat(Format format) const {
		#if XR_KHR_D3D12_enable || XR_KHR_D3D11_enable
			if(platform == PlatformD3D12 || platform == PlatformD3D11) {
				if(format == FormatRGBAu8n) return DXGI_FORMAT_R8G8B8A8_UNORM;
				if(format == FormatRGBAu8ns) return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
				if(format == FormatRGBu10Au2n) return DXGI_FORMAT_R10G10B10A2_UNORM;
				if(format == FormatRGBAf16) return DXGI_FORMAT_R16G16B16A16_FLOAT;
				if(format == FormatDu16Su8) return DXGI_FORMAT_D24_UNORM_S8_UINT;
				if(format == FormatDu24Su8) return DXGI_FORMAT_D24_UNORM_S8_UINT;
				if(format == FormatDf32Su8) return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
				if(format == FormatDu16) return DXGI_FORMAT_D16_UNORM;
				if(format == FormatDu24) return DXGI_FORMAT_D24_UNORM_S8_UINT;
				if(format == FormatDf32) return DXGI_FORMAT_D32_FLOAT;
			}
		#endif
		#if XR_KHR_vulkan_enable
			if(platform == PlatformVK) {
				if(format == FormatRGBAu8n) return VK_FORMAT_R8G8B8A8_UNORM;
				if(format == FormatRGBAu8ns) return VK_FORMAT_R8G8B8A8_SRGB;
				if(format == FormatRGBu10Au2n) return VK_FORMAT_A2B10G10R10_UNORM_PACK32;
				if(format == FormatRGBAf16) return VK_FORMAT_R16G16B16A16_SFLOAT;
				if(format == FormatDu16Su8) return VK_FORMAT_D16_UNORM_S8_UINT;
				if(format == FormatDu24Su8) return VK_FORMAT_D24_UNORM_S8_UINT;
				if(format == FormatDf32Su8) return VK_FORMAT_D32_SFLOAT_S8_UINT;
				if(format == FormatDu16) return VK_FORMAT_D16_UNORM;
				if(format == FormatDu24) return VK_FORMAT_X8_D24_UNORM_PACK32;
				if(format == FormatDf32) return VK_FORMAT_D32_SFLOAT;
			}
		#endif
		#if XR_KHR_opengl_enable
			if(platform == PlatformGL) {
				if(format == FormatRGBAu8n) return GL_RGBA8;
				if(format == FormatRGBAu8ns) return GL_SRGB8_ALPHA8;
				if(format == FormatRGBu10Au2n) return GL_RGB10_A2;
				if(format == FormatRGBAf16) return GL_RGBA16F;
				if(format == FormatDu16Su8) return GL_DEPTH24_STENCIL8;
				if(format == FormatDu24Su8) return GL_DEPTH24_STENCIL8;
				if(format == FormatDf32Su8) return GL_DEPTH32F_STENCIL8;
				if(format == FormatDu16) return GL_DEPTH_COMPONENT16;
				if(format == FormatDu24) return GL_DEPTH_COMPONENT24;
				if(format == FormatDf32) return GL_DEPTH_COMPONENT32F;
			}
		#endif
		#if XR_KHR_opengl_es_enable
			if(platform == PlatformGLES) {
				if(format == FormatRGBAu8n) return GL_RGBA8;
				if(format == FormatRGBAu8ns) return GL_SRGB8_ALPHA8;
				if(format == FormatRGBu10Au2n) return GL_RGB10_A2;
				if(format == FormatRGBAf16) return GL_RGBA16F;
				if(format == FormatDu16Su8) return GL_DEPTH24_STENCIL8;
				if(format == FormatDu24Su8) return GL_DEPTH24_STENCIL8;
				if(format == FormatDf32Su8) return GL_DEPTH32F_STENCIL8;
				if(format == FormatDu16) return GL_DEPTH_COMPONENT16;
				if(format == FormatDu24) return GL_DEPTH_COMPONENT24;
				if(format == FormatDf32) return GL_DEPTH_COMPONENT32F;
			}
		#endif
		TS_LOGF(Error, "XRSystem::getFormat(): unknown %s %s format\n", getPlatformName(platform), getFormatName(format));
		return Maxi64;
	}
	
	bool XRSystem::hasFormat(Format format) const {
		return (bool)formats.find(getFormat(format));
	}
	
	/*
	 */
	bool XRSystem::getImages(XrSwapchain swap_chain, Array<size_t> &images) const {
		
		// number of images
		uint32_t num_images = 0;
		if(XR::error(xrEnumerateSwapchainImages(swap_chain, 0, &num_images, nullptr)) || num_images == 0) {
			TS_LOG(Error, "XRSystem::getImages(): can't get swap chain images\n");
			return false;
		}
		
		// create swap chain images
		XrSwapchainImageBaseHeader *images_ptr = nullptr;
		#if XR_KHR_D3D12_enable
			Array<XrSwapchainImageD3D12KHR> d3d12_images;
			if(platform == PlatformD3D12) {
				d3d12_images.resize(num_images);
				for(uint32_t i = 0; i < num_images; i++) {
					d3d12_images[i].type = XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR;
					d3d12_images[i].next = nullptr;
				}
				images_ptr = (XrSwapchainImageBaseHeader*)d3d12_images.get();
			}
		#endif
		#if XR_KHR_D3D11_enable
			Array<XrSwapchainImageD3D11KHR> d3d11_images;
			if(platform == PlatformD3D11) {
				d3d11_images.resize(num_images);
				for(uint32_t i = 0; i < num_images; i++) {
					d3d11_images[i].type = XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR;
					d3d11_images[i].next = nullptr;
				}
				images_ptr = (XrSwapchainImageBaseHeader*)d3d11_images.get();
			}
		#endif
		#if XR_KHR_vulkan_enable
			Array<XrSwapchainImageVulkanKHR> vk_images;
			if(platform == PlatformVK) {
				vk_images.resize(num_images);
				for(uint32_t i = 0; i < num_images; i++) {
					vk_images[i].type = XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR;
					vk_images[i].next = nullptr;
				}
				images_ptr = (XrSwapchainImageBaseHeader*)vk_images.get();
			}
		#endif
		#if XR_KHR_opengl_enable
			Array<XrSwapchainImageOpenGLKHR> gl_images;
			if(platform == PlatformGL) {
				gl_images.resize(num_images);
				for(uint32_t i = 0; i < num_images; i++) {
					gl_images[i].type = XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR;
					gl_images[i].next = nullptr;
				}
				images_ptr = (XrSwapchainImageBaseHeader*)gl_images.get();
			}
		#endif
		#if XR_KHR_opengl_es_enable
			Array<XrSwapchainImageOpenGLESKHR> gles_images;
			if(platform == PlatformGLES) {
				gles_images.resize(num_images);
				for(uint32_t i = 0; i < num_images; i++) {
					gles_images[i].type = XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR;
					gles_images[i].next = nullptr;
				}
				images_ptr = (XrSwapchainImageBaseHeader*)gles_images.get();
			}
		#endif
		if(images_ptr == nullptr) {
			TS_LOGF(Error, "XRSystem::getImages(): unknown platform %s\n", getPlatformName(platform));
			return false;
		}
		
		// get swap chain images
		if(XR::error(xrEnumerateSwapchainImages(swap_chain, num_images, &num_images, images_ptr))) {
			TS_LOG(Error, "XRSystem::getImages(): can't get swap chain images\n");
			return false;
		}
		
		// copy swap chain images
		images.resize(num_images, (size_t)0);
		for(uint32_t i = 0; i < num_images; i++) {
			#if XR_KHR_D3D12_enable
				if(d3d12_images) images[i] = (size_t)d3d12_images[i].texture;
			#endif
			#if XR_KHR_D3D11_enable
				if(d3d11_images) images[i] = (size_t)(void*)d3d11_images[i].texture;
			#endif
			#if XR_KHR_vulkan_enable
				if(vk_images) images[i] = (size_t)(void*)vk_images[i].image;
			#endif
			#if XR_KHR_opengl_enable
				if(gl_images) images[i] = gl_images[i].image;
			#endif
			#if XR_KHR_opengl_es_enable
				if(gles_images) images[i] = gles_images[i].image;
			#endif
		}
		
		return true;
	}
	
	bool XRSystem::setImages(Surface &surface, size_t color_image, size_t depth_image) const {
		
		#if XR_KHR_D3D12_enable
			if(platform == PlatformD3D12) {
				D3D12Surface d3d12_surface = D3D12Surface(surface);
				if(d3d12_surface) {
					d3d12_surface.setRenderTarget((ID3D12Resource*)color_image);
					d3d12_surface.setDepthStencil((ID3D12Resource*)depth_image);
					return true;
				}
			}
		#endif
		#if XR_KHR_D3D11_enable
			if(platform == PlatformD3D11) {
				D3D11Surface d3d11_surface = D3D11Surface(surface);
				if(d3d11_surface) {
					d3d11_surface.setRenderTarget((ID3D11Texture2D*)color_image);
					d3d11_surface.setDepthStencil((ID3D11Texture2D*)depth_image);
					return true;
				}
			}
		#endif
		#if XR_KHR_vulkan_enable
			if(platform == PlatformVK) {
				VKSurface vk_surface = VKSurface(surface);
				if(vk_surface) {
					vk_surface.setColorImage((VkImage)color_image);
					vk_surface.setDepthImage((VkImage)depth_image);
					return true;
				}
			}
		#endif
		#if XR_KHR_opengl_enable
			if(platform == PlatformGL) {
				GLSurface gl_surface = GLSurface(surface);
				if(gl_surface) {
					gl_surface.setColorTextureID((uint32_t)color_image);
					gl_surface.setDepthTextureID((uint32_t)depth_image);
					return true;
				}
			}
		#endif
		#if XR_KHR_opengl_es_enable
			if(platform == PlatformGLES) {
				GLESSurface gles_surface = GLESSurface(surface);
				if(gles_surface) {
					gles_surface.setColorTextureID((uint32_t)color_image);
					gles_surface.setDepthTextureID((uint32_t)depth_image);
					return true;
				}
			}
		#endif
		
		TS_LOGF(Error, "XRSystem::setImages(): unknown platform %s\n", getPlatformName(platform));
		return false;
	}
	
	/*****************************************************************************\
	 *
	 * OpenXR functions
	 *
	\*****************************************************************************/
	
	// OpenXR 10 functions
	PFN_xrGetInstanceProcAddr xrGetInstanceProcAddr = nullptr;
	PFN_xrEnumerateApiLayerProperties xrEnumerateApiLayerProperties = nullptr;
	PFN_xrEnumerateInstanceExtensionProperties xrEnumerateInstanceExtensionProperties = nullptr;
	PFN_xrCreateInstance xrCreateInstance = nullptr;
	PFN_xrDestroyInstance xrDestroyInstance = nullptr;
	PFN_xrGetInstanceProperties xrGetInstanceProperties = nullptr;
	PFN_xrPollEvent xrPollEvent = nullptr;
	PFN_xrResultToString xrResultToString = nullptr;
	PFN_xrStructureTypeToString xrStructureTypeToString = nullptr;
	PFN_xrGetSystem xrGetSystem = nullptr;
	PFN_xrGetSystemProperties xrGetSystemProperties = nullptr;
	PFN_xrEnumerateEnvironmentBlendModes xrEnumerateEnvironmentBlendModes = nullptr;
	PFN_xrCreateSession xrCreateSession = nullptr;
	PFN_xrDestroySession xrDestroySession = nullptr;
	PFN_xrEnumerateReferenceSpaces xrEnumerateReferenceSpaces = nullptr;
	PFN_xrCreateReferenceSpace xrCreateReferenceSpace = nullptr;
	PFN_xrGetReferenceSpaceBoundsRect xrGetReferenceSpaceBoundsRect = nullptr;
	PFN_xrCreateActionSpace xrCreateActionSpace = nullptr;
	PFN_xrLocateSpace xrLocateSpace = nullptr;
	PFN_xrDestroySpace xrDestroySpace = nullptr;
	PFN_xrEnumerateViewConfigurations xrEnumerateViewConfigurations = nullptr;
	PFN_xrGetViewConfigurationProperties xrGetViewConfigurationProperties = nullptr;
	PFN_xrEnumerateViewConfigurationViews xrEnumerateViewConfigurationViews = nullptr;
	PFN_xrEnumerateSwapchainFormats xrEnumerateSwapchainFormats = nullptr;
	PFN_xrCreateSwapchain xrCreateSwapchain = nullptr;
	PFN_xrDestroySwapchain xrDestroySwapchain = nullptr;
	PFN_xrEnumerateSwapchainImages xrEnumerateSwapchainImages = nullptr;
	PFN_xrAcquireSwapchainImage xrAcquireSwapchainImage = nullptr;
	PFN_xrWaitSwapchainImage xrWaitSwapchainImage = nullptr;
	PFN_xrReleaseSwapchainImage xrReleaseSwapchainImage = nullptr;
	PFN_xrBeginSession xrBeginSession = nullptr;
	PFN_xrEndSession xrEndSession = nullptr;
	PFN_xrRequestExitSession xrRequestExitSession = nullptr;
	PFN_xrWaitFrame xrWaitFrame = nullptr;
	PFN_xrBeginFrame xrBeginFrame = nullptr;
	PFN_xrEndFrame xrEndFrame = nullptr;
	PFN_xrLocateViews xrLocateViews = nullptr;
	PFN_xrStringToPath xrStringToPath = nullptr;
	PFN_xrPathToString xrPathToString = nullptr;
	PFN_xrCreateActionSet xrCreateActionSet = nullptr;
	PFN_xrDestroyActionSet xrDestroyActionSet = nullptr;
	PFN_xrCreateAction xrCreateAction = nullptr;
	PFN_xrDestroyAction xrDestroyAction = nullptr;
	PFN_xrSuggestInteractionProfileBindings xrSuggestInteractionProfileBindings = nullptr;
	PFN_xrAttachSessionActionSets xrAttachSessionActionSets = nullptr;
	PFN_xrGetCurrentInteractionProfile xrGetCurrentInteractionProfile = nullptr;
	PFN_xrGetActionStateBoolean xrGetActionStateBoolean = nullptr;
	PFN_xrGetActionStateFloat xrGetActionStateFloat = nullptr;
	PFN_xrGetActionStateVector2f xrGetActionStateVector2f = nullptr;
	PFN_xrGetActionStatePose xrGetActionStatePose = nullptr;
	PFN_xrSyncActions xrSyncActions = nullptr;
	PFN_xrEnumerateBoundSourcesForAction xrEnumerateBoundSourcesForAction = nullptr;
	PFN_xrGetInputSourceLocalizedName xrGetInputSourceLocalizedName = nullptr;
	PFN_xrApplyHapticFeedback xrApplyHapticFeedback = nullptr;
	PFN_xrStopHapticFeedback xrStopHapticFeedback = nullptr;
	
	// KHR loader init
	PFN_xrInitializeLoaderKHR xrInitializeLoaderKHR = nullptr;
	
	// KHR Android thread settings
	#if XR_KHR_android_thread_settings
		PFN_xrSetAndroidApplicationThreadKHR xrSetAndroidApplicationThreadKHR = nullptr;
	#endif
	
	// KHR Android surface swapchain
	#if XR_KHR_android_surface_swapchain
		PFN_xrCreateSwapchainAndroidSurfaceKHR xrCreateSwapchainAndroidSurfaceKHR = nullptr;
	#endif
	
	// KHR OpenGL enable
	#if XR_KHR_opengl_enable
		PFN_xrGetOpenGLGraphicsRequirementsKHR xrGetOpenGLGraphicsRequirementsKHR = nullptr;
	#endif
	
	// KHR OpenGLES enable
	#if XR_KHR_opengl_es_enable
		PFN_xrGetOpenGLESGraphicsRequirementsKHR xrGetOpenGLESGraphicsRequirementsKHR = nullptr;
	#endif
	
	// KHR Vulkan enable
	#if XR_KHR_vulkan_enable
		PFN_xrGetVulkanInstanceExtensionsKHR xrGetVulkanInstanceExtensionsKHR = nullptr;
		PFN_xrGetVulkanDeviceExtensionsKHR xrGetVulkanDeviceExtensionsKHR = nullptr;
		PFN_xrGetVulkanGraphicsDeviceKHR xrGetVulkanGraphicsDeviceKHR = nullptr;
		PFN_xrGetVulkanGraphicsRequirementsKHR xrGetVulkanGraphicsRequirementsKHR = nullptr;
	#endif
	
	// KHR D3D11 enable
	#if XR_KHR_D3D11_enable
		PFN_xrGetD3D11GraphicsRequirementsKHR xrGetD3D11GraphicsRequirementsKHR = nullptr;
	#endif
	
	// KHR D3D12 enable
	#if XR_KHR_D3D12_enable
		PFN_xrGetD3D12GraphicsRequirementsKHR xrGetD3D12GraphicsRequirementsKHR = nullptr;
	#endif
}

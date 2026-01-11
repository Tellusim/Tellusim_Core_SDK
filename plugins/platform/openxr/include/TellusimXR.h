// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_PLATFORM_XR_H__
#define __TELLUSIM_PLUGINS_PLATFORM_XR_H__

#ifndef XR_NO_PROTOTYPES
	#define XR_NO_PROTOTYPES		1
#endif

#include <openxr/openxr.h>

#include <TellusimFormat.h>
#include <math/TellusimMath.h>
#include <core/TellusimArray.h>
#include <core/TellusimString.h>
#include <platform/TellusimPlatform.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Context;
	class Surface;
	class XRSystem;
	
	/**
	 * OpenXR
	 */
	namespace XR {
		
		/// retain/release
		bool retain();
		bool release();
		
		/// check status
		bool isOpened();
		
		/// open/close
		bool open();
		void close();
		
		/// OpenXR instance
		XrInstance getInstance();
		
		/// OpenXR instance info
		const String &getLayers();
		const String &getExtensions();
		
		/// check OpenXR instance info
		bool checkLayer(const char *name);
		bool checkExtension(const char *name);
		
		/// OpenXR instance properties
		const XrInstanceProperties &getProperties();
		
		/// OpenXR systems
		uint32_t getNumSystems();
		void addSystem(XRSystem *system);
		XRSystem *getSystem(uint32_t index);
		
		/// OpenXR types
		TS_INLINE Vector2f toVector2f(const XrVector2f &v) { return Vector2f(v.x, v.y); }
		TS_INLINE Vector3f toVector3f(const XrVector3f &v) { return Vector3f(v.x, v.y, v.z); }
		TS_INLINE Vector4f toVector4f(const XrVector4f &v) { return Vector4f(v.x, v.y, v.z, v.w); }
		
		TS_INLINE Quaternionf toQuaternionf(const XrQuaternionf &q) { return Quaternionf(q.x, q.y, q.z, q.w); }
		
		Matrix4x3f toMatrix4x3f(const XrPosef &pose);
		
		/// check OpenXR errors
		bool error(XrResult result);
	}
	
	/**
	 * OpenXR System
	 */
	class XRSystem {
			
		public:
			
			XRSystem(XrSystemId system, XrFormFactor type);
			~XRSystem();
			
			/// check status
			bool isCreated() const;
			
			/// create session
			bool create(Context &context);
			void release();
			
			/// system info
			TS_INLINE XrSystemId getSystem() const { return system; }
			TS_INLINE XrFormFactor getType() const { return system_type; }
			
			/// system session
			TS_INLINE XrSession getSession() const { return session; }
			TS_INLINE Platform getPlatform() const { return platform; }
			
			/// system properties
			const XrSystemProperties &getProperties() const;
			
			/// system view configurations
			uint32_t getNumViewTypes() const;
			uint32_t getNumViewModes(uint32_t index) const;
			XrViewConfigurationType getViewType(uint32_t index) const;
			const Array<XrViewConfigurationType> &getViewTypes() const;
			const Array<XrViewConfigurationView> &getViewModes(uint32_t index) const;
			const XrViewConfigurationView &getViewMode(uint32_t index, uint32_t num) const;
			
			/// reference spaces
			uint32_t getNumSpaces() const;
			const Array<XrReferenceSpaceType> &getSpaceTypes() const;
			XrSpace getSpace(XrReferenceSpaceType type) const;
			XrSpace getSpace(uint32_t index) const;
			
			/// swap chain formats
			const Array<int64_t> &getFormats() const;
			int64_t getFormat(Format format) const;
			bool hasFormat(Format format) const;
			
			/// swap chain images
			bool getImages(XrSwapchain swap_chain, Array<size_t> &images) const;
			bool setImages(Surface &surface, size_t color_image, size_t depth_image) const;
			
		private:
			
			XrSystemId system = 0;								// system handle
			XrFormFactor system_type;							// system type
			
			XrSystemProperties system_properties;				// system properties
			
			Array<XrViewConfigurationType> view_types;			// view types
			Array<Array<XrViewConfigurationView>> view_modes;	// view modes
			
			XrSession session = XR_NULL_HANDLE;					// system session
			Platform platform = PlatformUnknown;				// system platform
			
			Array<XrReferenceSpaceType> space_types;			// reference space types
			Array<XrSpace> spaces;								// system spaces
			
			Array<int64_t> formats;								// swap chain formats
	};
	
	/// OpenXR 10 functions
	extern PFN_xrGetInstanceProcAddr xrGetInstanceProcAddr;
	extern PFN_xrEnumerateApiLayerProperties xrEnumerateApiLayerProperties;
	extern PFN_xrEnumerateInstanceExtensionProperties xrEnumerateInstanceExtensionProperties;
	extern PFN_xrCreateInstance xrCreateInstance;
	extern PFN_xrDestroyInstance xrDestroyInstance;
	extern PFN_xrGetInstanceProperties xrGetInstanceProperties;
	extern PFN_xrPollEvent xrPollEvent;
	extern PFN_xrResultToString xrResultToString;
	extern PFN_xrStructureTypeToString xrStructureTypeToString;
	extern PFN_xrGetSystem xrGetSystem;
	extern PFN_xrGetSystemProperties xrGetSystemProperties;
	extern PFN_xrEnumerateEnvironmentBlendModes xrEnumerateEnvironmentBlendModes;
	extern PFN_xrCreateSession xrCreateSession;
	extern PFN_xrDestroySession xrDestroySession;
	extern PFN_xrEnumerateReferenceSpaces xrEnumerateReferenceSpaces;
	extern PFN_xrCreateReferenceSpace xrCreateReferenceSpace;
	extern PFN_xrGetReferenceSpaceBoundsRect xrGetReferenceSpaceBoundsRect;
	extern PFN_xrCreateActionSpace xrCreateActionSpace;
	extern PFN_xrLocateSpace xrLocateSpace;
	extern PFN_xrDestroySpace xrDestroySpace;
	extern PFN_xrEnumerateViewConfigurations xrEnumerateViewConfigurations;
	extern PFN_xrGetViewConfigurationProperties xrGetViewConfigurationProperties;
	extern PFN_xrEnumerateViewConfigurationViews xrEnumerateViewConfigurationViews;
	extern PFN_xrEnumerateSwapchainFormats xrEnumerateSwapchainFormats;
	extern PFN_xrCreateSwapchain xrCreateSwapchain;
	extern PFN_xrDestroySwapchain xrDestroySwapchain;
	extern PFN_xrEnumerateSwapchainImages xrEnumerateSwapchainImages;
	extern PFN_xrAcquireSwapchainImage xrAcquireSwapchainImage;
	extern PFN_xrWaitSwapchainImage xrWaitSwapchainImage;
	extern PFN_xrReleaseSwapchainImage xrReleaseSwapchainImage;
	extern PFN_xrBeginSession xrBeginSession;
	extern PFN_xrEndSession xrEndSession;
	extern PFN_xrRequestExitSession xrRequestExitSession;
	extern PFN_xrWaitFrame xrWaitFrame;
	extern PFN_xrBeginFrame xrBeginFrame;
	extern PFN_xrEndFrame xrEndFrame;
	extern PFN_xrLocateViews xrLocateViews;
	extern PFN_xrStringToPath xrStringToPath;
	extern PFN_xrPathToString xrPathToString;
	extern PFN_xrCreateActionSet xrCreateActionSet;
	extern PFN_xrDestroyActionSet xrDestroyActionSet;
	extern PFN_xrCreateAction xrCreateAction;
	extern PFN_xrDestroyAction xrDestroyAction;
	extern PFN_xrSuggestInteractionProfileBindings xrSuggestInteractionProfileBindings;
	extern PFN_xrAttachSessionActionSets xrAttachSessionActionSets;
	extern PFN_xrGetCurrentInteractionProfile xrGetCurrentInteractionProfile;
	extern PFN_xrGetActionStateBoolean xrGetActionStateBoolean;
	extern PFN_xrGetActionStateFloat xrGetActionStateFloat;
	extern PFN_xrGetActionStateVector2f xrGetActionStateVector2f;
	extern PFN_xrGetActionStatePose xrGetActionStatePose;
	extern PFN_xrSyncActions xrSyncActions;
	extern PFN_xrEnumerateBoundSourcesForAction xrEnumerateBoundSourcesForAction;
	extern PFN_xrGetInputSourceLocalizedName xrGetInputSourceLocalizedName;
	extern PFN_xrApplyHapticFeedback xrApplyHapticFeedback;
	extern PFN_xrStopHapticFeedback xrStopHapticFeedback;
	
	/// KHR loader init
	extern PFN_xrInitializeLoaderKHR xrInitializeLoaderKHR;
	
	/// KHR Android thread settings
	#if XR_KHR_android_thread_settings
		extern PFN_xrSetAndroidApplicationThreadKHR xrSetAndroidApplicationThreadKHR;
	#endif
	
	/// KHR Android surface swapchain
	#if XR_KHR_android_surface_swapchain
		extern PFN_xrCreateSwapchainAndroidSurfaceKHR xrCreateSwapchainAndroidSurfaceKHR;
	#endif
	
	/// KHR OpenGL enable
	#if XR_KHR_opengl_enable
		extern PFN_xrGetOpenGLGraphicsRequirementsKHR xrGetOpenGLGraphicsRequirementsKHR;
	#endif
	
	/// KHR OpenGLES enable
	#if XR_KHR_opengl_es_enable
		extern PFN_xrGetOpenGLESGraphicsRequirementsKHR xrGetOpenGLESGraphicsRequirementsKHR;
	#endif
	
	/// KHR Vulkan enable
	#if XR_KHR_vulkan_enable
		extern PFN_xrGetVulkanInstanceExtensionsKHR xrGetVulkanInstanceExtensionsKHR;
		extern PFN_xrGetVulkanDeviceExtensionsKHR xrGetVulkanDeviceExtensionsKHR;
		extern PFN_xrGetVulkanGraphicsDeviceKHR xrGetVulkanGraphicsDeviceKHR;
		extern PFN_xrGetVulkanGraphicsRequirementsKHR xrGetVulkanGraphicsRequirementsKHR;
	#endif
	
	/// KHR D3D11 enable
	#if XR_KHR_D3D11_enable
		extern PFN_xrGetD3D11GraphicsRequirementsKHR xrGetD3D11GraphicsRequirementsKHR;
	#endif
	
	/// KHR D3D12 enable
	#if XR_KHR_D3D12_enable
		extern PFN_xrGetD3D12GraphicsRequirementsKHR xrGetD3D12GraphicsRequirementsKHR;
	#endif
}

#endif /* __TELLUSIM_PLUGINS_PLATFORM_XR_H__ */

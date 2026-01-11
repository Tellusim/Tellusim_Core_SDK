// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_PLATFORM_XR_INPUT_H__
#define __TELLUSIM_PLUGINS_PLATFORM_XR_INPUT_H__

#include <core/TellusimMap.h>

#include "TellusimXR.h"

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class XRWindow;
	
	/**
	 * XRInput
	 */
	class XRInput {
			
		public:
			
			/// input constructor
			XRInput();
			virtual ~XRInput();
			
			/// input status
			TS_INLINE bool isCreated() const { return actions != XR_NULL_HANDLE; }
			
			/// create input
			bool create(XRWindow *window, const char *prefix);
			void release();
			
			/// boolean parameter
			uint32_t addBool(const char *name, const char *profile = nullptr, const char *path = nullptr);
			bool getBool(const char *name, bool clear = false, bool value = false) const;
			bool getBool(uint32_t id, bool clear = false, bool value = false) const;
			
			/// scalar parameter
			uint32_t addScalarf32(const char *name, const char *profile = nullptr, const char *path = nullptr);
			float32_t getScalarf32(const char *name, float32_t value = 0.0f) const;
			float32_t getScalarf32(uint32_t id, float32_t value = 0.0f) const;
			
			/// vector parameter
			uint32_t addVector2f(const char *name, const char *profile = nullptr, const char *path = nullptr);
			Vector2f getVector2f(const char *name, const Vector2f &value = Vector2f::zero) const;
			Vector2f getVector2f(uint32_t id, const Vector2f &value = Vector2f::zero) const;
			
			/// matrix parameter
			uint32_t addMatrix4x3f(const char *name, const char *profile = nullptr, const char *path = nullptr);
			Matrix4x3f getMatrix4x3f(const char *name, const Matrix4x3f &value = Matrix4x3f::zero) const;
			Matrix4x3f getMatrix4x3f(uint32_t id, const Matrix4x3f &value = Matrix4x3f::zero) const;
			
			/// parameter bindings
			bool addBinding(const char *name, const char *profile, const char *path = nullptr);
			bool addBinding(uint32_t id, const char *profile, const char *path = nullptr);
			
			/// OpenXR window
			TS_INLINE XRWindow *getWindow() const { return window; }
			
			/// OpenXR system
			TS_INLINE XRSystem *getSystem() const { return system; }
			TS_INLINE XrSession getSession() const { return system->getSession(); }
			
			/// input prefix
			TS_INLINE const String &getPrefix() const { return prefix; }
			
			/// input actions set
			TS_INLINE XrActionSet getActions() const { return actions; }
			
			/// default profiles
			static const char *ProfileKHR;
			static const char *ProfileHTC;
			static const char *ProfileValve;
			static const char *ProfileOculus;
			
			/// default controllers
			static const char *HandLeft;
			static const char *HandRight;
			
			/// default inputs
			static const char *InputA;
			static const char *InputB;
			static const char *InputX;
			static const char *InputY;
			static const char *InputAim;
			static const char *InputGrip;
			static const char *InputThumb;
			static const char *InputTrigger;
			static const char *InputSqueeze;
			
		private:
			
			friend class XRWindow;
			
			/// add parameter
			uint32_t add_parameter(const char *name, XrActionType type, const char *profile, const char *path);
			
			/// get parameters bindings
			void get_bindings(Map<String, Array<XrActionSuggestedBinding>> &bindings) const;
			
			XRWindow *window = nullptr;				// OpenXR window
			XRSystem *system = nullptr;				// OpenXR system
			
			String prefix;							// input prefix
			
			XrActionSet actions = XR_NULL_HANDLE;	// input actions
			
			struct Parameter {
				String name;						// parameter name
				XrAction action = XR_NULL_HANDLE;	// parameter action
				XrSpace space = XR_NULL_HANDLE;		// parameter space
				Map<String, XrPath> bindings;		// parameter bindings
				mutable bool clear = false;			// parameter clear flag
			};
			
			Map<uint32_t, Parameter> parameters;	// parameters
			
			Map<String, uint32_t> names;			// parameter names
	};
}

#endif /* __TELLUSIM_PLUGINS_PLATFORM_XR_INPUT_H__ */

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_SYSTEM_CONFIG_H__
#define __TELLUSIM_PLUGINS_SYSTEM_CONFIG_H__

#include <core/TellusimAtomic.h>
#include <math/TellusimMath.h>
#include <format/TellusimXml.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Config
	 */
	class Config {
			
		public:
			
			/// Config flags
			enum Flags {
				FlagNone = 0,
				FlagLocal		= (1 << 0),		// create local config
				FlagReadOnly	= (1 << 1),		// readonly config access
				FlagComplete	= (1 << 2),		// write all values including defaults
				DefaultFlags	= FlagNone,
			};
			
			/// config constructor
			explicit Config(Flags flags = DefaultFlags, const char *name = nullptr);
			virtual ~Config();
			
			/// disable copying
			Config(const Config&) = delete;
			Config &operator=(const Config&) = delete;
			
			/// config flags
			void setFlags(Flags f) { flags = f; }
			TS_INLINE Flags getFlags() const { return flags; }
			
			TS_INLINE bool hasFlag(Flags flags) const { return ((getFlags() & flags) != FlagNone); }
			TS_INLINE bool hasFlags(Flags flags) const { return ((getFlags() & flags) == flags); }
			
			TS_INLINE bool isChanged() const { return changed; }
			
			/// load/save config
			bool load(const char *name = nullptr);
			bool save();
			
			/// config version
			String getVersion() const;
			
			/// remove config values
			void remove(const char *name);
			
			/// set config values
			Xml setXml(const char *name);
			void set(const char *name, bool value);
			void set(const char *name, int32_t value);
			void set(const char *name, uint32_t value);
			void set(const char *name, float32_t value);
			void set(const char *name, float64_t value);
			void set(const char *name, const char *value);
			void set(const char *name, const String &value);
			void set(const char *name, const Vector2f &value);
			void set(const char *name, const Vector2d &value);
			void set(const char *name, const Vector3f &value);
			void set(const char *name, const Vector3d &value);
			void set(const char *name, const Vector4f &value);
			void set(const char *name, const Vector4d &value);
			void set(const char *name, const Matrix4x3f &value);
			void set(const char *name, const Matrix4x3d &value);
			void set(const char *name, const Matrix4x4f &value);
			void set(const char *name, const Matrix4x4d &value);
			void set(const char *name, const Quaternionf &value);
			void set(const char *name, const Quaterniond &value);
			void set(const char *name, const Color &value);
			
			TS_INLINE void setb(const char *name, bool value) { set(name, value); }
			TS_INLINE void seti32(const char *name, int32_t value) { set(name, value); }
			TS_INLINE void setu32(const char *name, uint32_t value) { set(name, value); }
			TS_INLINE void setf32(const char *name, float32_t value) { set(name, value); }
			TS_INLINE void setf64(const char *name, float64_t value) { set(name, value); }
			
			template <class Type> TS_INLINE void set(const String &name, const Type &value) { set(name.get(), value); }
			
			/// get config values
			Xml getXml(const char *name) const;
			bool getb(const char *name, bool value = false) const;
			int32_t geti32(const char *name, int32_t value = 0) const;
			uint32_t getu32(const char *name, uint32_t value = 0) const;
			float32_t getf32(const char *name, float32_t value = 0.0f) const;
			float64_t getf64(const char *name, float64_t value = 0.0) const;
			String gets(const char *name, const char *value = nullptr) const;
			String gets(const char *name, const String &value) const;
			Vector2f getVector2f(const char *name, const Vector2f &value = Vector2f::zero) const;
			Vector2d getVector2d(const char *name, const Vector2d &value = Vector2d::zero) const;
			Vector3f getVector3f(const char *name, const Vector3f &value = Vector3f::zero) const;
			Vector3d getVector3d(const char *name, const Vector3d &value = Vector3d::zero) const;
			Vector4f getVector4f(const char *name, const Vector4f &value = Vector4f::zero) const;
			Vector4d getVector4d(const char *name, const Vector4d &value = Vector4d::zero) const;
			Matrix4x3f getMatrix4x3f(const char *name, const Matrix4x3f &value = Matrix4x3f::identity) const;
			Matrix4x3d getMatrix4x3d(const char *name, const Matrix4x3d &value = Matrix4x3d::identity) const;
			Matrix4x4f getMatrix4x4f(const char *name, const Matrix4x4f &value = Matrix4x4f::identity) const;
			Matrix4x4d getMatrix4x4d(const char *name, const Matrix4x4d &value = Matrix4x4d::identity) const;
			Quaternionf getQuaternionf(const char *name, const Quaternionf &value = Quaternionf::identity) const;
			Quaterniond getQuaterniond(const char *name, const Quaterniond &value = Quaterniond::identity) const;
			Color getColor(const char *name, const Color &value = Color::white) const;
			
			TS_INLINE bool getb(const String &name, bool value = false) const { return getb(name.get(), value); }
			TS_INLINE int32_t geti32(const String &name, int32_t value = 0) const { return geti32(name.get(), value); }
			TS_INLINE uint32_t getu32(const String &name, uint32_t value = 0) const { return getu32(name.get(), value); }
			TS_INLINE float32_t getf32(const String &name, float32_t value = 0.0f) const { return getf32(name.get(), value); }
			TS_INLINE float64_t getf64(const String &name, float64_t value = 0.0) const { return getf64(name.get(), value); }
			TS_INLINE String gets(const String &name, const char *value = nullptr) const { return gets(name.get(), value); }
			TS_INLINE String gets(const String &name, const String &value) const { return gets(name.get(), value); }
			
			template <class Type> void getb(const char *name, Type &flags, Type mask) const {
				if(getb(name, flags & mask)) flags |= mask;
				else flags &= ~mask;
			}
			
			/// config file path
			TS_INLINE const String &getPath() const { return path; }
			
			/// config file name
			TS_INLINE const String &getName() const { return name; }
			
		private:
			
			/// get config xml
			Xml set_xml(const char *name);
			Xml get_xml(const char *name) const;
			
			mutable SpinLock lock;		// config lock
			
			Flags flags = FlagNone;		// config flags
			
			bool changed = false;		// changed flag
			
			String path;				// config path
			String name;				// config name
			
			Xml root;					// config root
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(Config::Flags)
}

#endif /* __TELLUSIM_PLUGINS_SYSTEM_CONFIG_H__ */

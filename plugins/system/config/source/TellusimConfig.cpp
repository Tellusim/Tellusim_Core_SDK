// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimSource.h>
#include <core/TellusimDirectory.h>
#if _IOS
	#include <system/TellusimiOS.h>
#elif _ANDROID
	#include <system/TellusimAndroid.h>
#endif

#include "../include/TellusimConfig.h"

/*
 */
#ifndef TS_CONFIG_TYPE
	#define TS_CONFIG_TYPE ".cfg"
#endif

/*
 */
#ifndef TS_APP_NAME
	#error TS_APP_NAME is not defined
#endif
#ifndef TS_APP_VERSION
	#error TS_APP_VERSION is not defined
#endif
#if !defined(TS_APP_PATH) && !_IOS && !_ANDROID
	#error TS_APP_PATH is not defined
#endif

/*
 */
namespace Tellusim {
	
	/*
	 */
	Config::Config(Flags flags, const char *name) : flags(flags) {
		
		// config file path
		#if _IOS
			path = iOS::getDocumentsDirectory() + "/";
		#elif _ANDROID
			path = Android::getCacheDirectory() + "/";
		#else
			if(hasFlag(FlagLocal)) {
				path = Directory::getCurrentDirectory() + "/";
			} else {
				path = Directory::getHomeDirectory() + "/" TS_APP_PATH "/";
				Directory::createDirectory(path);
			}
		#endif
		
		// initialize config
		root.setName(TS_APP_NAME);
		root.setAttribute("version", TS_APP_VERSION);
		
		// load config
		load(name);
	}
	
	Config::~Config() {
		
		// save config
		if(changed && !hasFlag(FlagReadOnly)) save();
	}
	
	/*
	 */
	bool Config::load(const char *config_name) {
		AtomicLock atomic(lock);
		if(!config_name || !config_name[0]) config_name = TS_APP_NAME TS_CONFIG_TYPE;
		name = path + config_name;
		if(!Directory::isFile(name.get())) {
			Source source;
			if(Source::isSource(config_name) && source.open(config_name)) {
				setFlags(getFlags() | FlagReadOnly);
				name = config_name;
			} else {
				return false;
			}
		}
		if(!root.load(name)) {
			TS_LOGF(Error, "Config::load(): can't load \"%s\" config\n", name.get());
			return false;
		}
		if(root.getName() != TS_APP_NAME) {
			TS_LOGF(Error, "Config::load(): invalid root \"%s\" for \"%s\" app\n", root.getName().get(), TS_APP_NAME);
			return false;
		}
		return true;
	}
	
	bool Config::save() {
		AtomicLock atomic(lock);
		if(root && name && !hasFlag(FlagReadOnly)) {
			if(!hasFlag(FlagLocal) && !Directory::createDirectory(path)) {
				TS_LOGF(Error, "Config::save(): can't create \"%s\" directory\n", path.get());
				return false;
			}
			root.setName(TS_APP_NAME);
			root.setAttribute("version", TS_APP_VERSION);
			if(!root.save(name)) {
				TS_LOG(Error, "Config::save(): can't save config\n");
				return false;
			}
			changed = false;
			return true;
		}
		return false;
	}
	
	/*
	 */
	String Config::getVersion() const {
		AtomicLock atomic(lock);
		return root.getAttribute("version");
	}
	
	/*
	 */
	Xml Config::set_xml(const char *name) {
		String path;
		Xml xml, parent = root;
		for(const char *s = name; parent; s++) {
			if(*s == '/' || *s == '\0') {
				xml = parent.getChild(path.get());
				if(!xml) xml = parent.addChild(path.get());
				parent = xml;
				path.clear();
			}
			if(*s == '\0') break;
			if(*s != '/') path += *s;
		}
		return xml;
	}
	
	Xml Config::get_xml(const char *name) const {
		String path;
		Xml xml = root;
		for(const char *s = name; xml; s++) {
			if(*s == '/' || *s == '\0') {
				xml = xml.getChild(path.get());
				path.clear();
			}
			if(*s == '\0') break;
			if(*s != '/') path += *s;
		}
		return xml;
	}
	
	/*
	 */
	void Config::remove(const char *name) {
		AtomicLock atomic(lock);
		Xml xml = get_xml(name);
		if(xml && xml.getParent()) xml.getParent().removeChild(xml);
	}
	
	/*
	 */
	Xml Config::setXml(const char *name) {
		AtomicLock atomic(lock);
		changed = true;
		return set_xml(name);
	}
	
	/*
	 */
	void Config::set(const char *name, bool value) {
		AtomicLock atomic(lock);
		Xml xml = set_xml(name);
		if(xml.getDataBool() == value && !hasFlag(FlagForce)) return;
		xml.setData(value);
		changed = true;
	}
	
	void Config::set(const char *name, int32_t value) {
		AtomicLock atomic(lock);
		Xml xml = set_xml(name);
		if(xml.getDatai32() == value && !hasFlag(FlagForce)) return;
		xml.setData(value);
		changed = true;
	}
	
	void Config::set(const char *name, uint32_t value) {
		AtomicLock atomic(lock);
		Xml xml = set_xml(name);
		if(xml.getDatau32() == value && !hasFlag(FlagForce)) return;
		xml.setData(value);
		changed = true;
	}
	
	void Config::set(const char *name, float32_t value) {
		AtomicLock atomic(lock);
		Xml xml = set_xml(name);
		if(xml.getDataf32() == value && !hasFlag(FlagForce)) return;
		xml.setData(value);
		changed = true;
	}
	
	void Config::set(const char *name, float64_t value) {
		AtomicLock atomic(lock);
		Xml xml = set_xml(name);
		if(xml.getDataf64() == value && !hasFlag(FlagForce)) return;
		xml.setData(value);
		changed = true;
	}
	
	void Config::set(const char *name, const char *value) {
		AtomicLock atomic(lock);
		Xml xml = set_xml(name);
		if(xml.getData() == value && !hasFlag(FlagForce)) return;
		xml.setData(String(value));
		changed = true;
	}
	
	void Config::set(const char *name, const String &value) {
		AtomicLock atomic(lock);
		Xml xml = set_xml(name);
		if(xml.getData() == value && !hasFlag(FlagForce)) return;
		xml.setData(value);
		changed = true;
	}
	
	/*
	 */
	Xml Config::getXml(const char *name) const {
		AtomicLock atomic(lock);
		return get_xml(name);
	}
	
	/*
	 */
	bool Config::getb(const char *name, bool value) const {
		AtomicLock atomic(lock);
		Xml xml = get_xml(name);
		if(xml) return xml.getDataBool();
		return value;
	}
	
	int32_t Config::geti32(const char *name, int32_t value) const {
		AtomicLock atomic(lock);
		Xml xml = get_xml(name);
		if(xml) return xml.getDatai32();
		return value;
	}
	
	uint32_t Config::getu32(const char *name, uint32_t value) const {
		AtomicLock atomic(lock);
		Xml xml = get_xml(name);
		if(xml) return xml.getDatau32();
		return value;
	}
	
	float32_t Config::getf32(const char *name, float32_t value) const {
		AtomicLock atomic(lock);
		Xml xml = get_xml(name);
		if(xml) return xml.getDataf32();
		return value;
	}
	
	float64_t Config::getf64(const char *name, float64_t value) const {
		AtomicLock atomic(lock);
		Xml xml = get_xml(name);
		if(xml) return xml.getDataf64();
		return value;
	}
	
	String Config::gets(const char *name, const char *value) const {
		AtomicLock atomic(lock);
		Xml xml = get_xml(name);
		if(xml) return xml.getData();
		return String(value);
	}
	
	String Config::gets(const char *name, const String &value) const {
		AtomicLock atomic(lock);
		Xml xml = get_xml(name);
		if(xml) return xml.getData();
		return value;
	}
	
	/*
	 */
	#define TS_DECLARE_CONFIG(TYPE, DATA) \
	void Config::set(const char *name, const TYPE &value) { \
		TYPE data; \
		AtomicLock atomic(lock); \
		Xml xml = set_xml(name); \
		if(xml.getData(data . DATA, TYPE::Size) == TYPE::Size && data == value) return; \
		xml.setData(value. DATA, TYPE::Size); \
		changed = true; \
	} \
	TYPE Config::get ## TYPE(const char *name, const TYPE &value) const { \
		TYPE ret; \
		AtomicLock atomic(lock); \
		Xml xml = get_xml(name); \
		if(xml && xml.getData(ret. DATA, TYPE::Size) == TYPE::Size) return ret; \
		return value; \
	}
	TS_DECLARE_CONFIG(Vector2f, v)
	TS_DECLARE_CONFIG(Vector2d, v)
	TS_DECLARE_CONFIG(Vector3f, v)
	TS_DECLARE_CONFIG(Vector3d, v)
	TS_DECLARE_CONFIG(Vector4f, v)
	TS_DECLARE_CONFIG(Vector4d, v)
	TS_DECLARE_CONFIG(Matrix4x3f, m)
	TS_DECLARE_CONFIG(Matrix4x3d, m)
	TS_DECLARE_CONFIG(Matrix4x4f, m)
	TS_DECLARE_CONFIG(Matrix4x4d, m)
	TS_DECLARE_CONFIG(Quaternionf, q)
	TS_DECLARE_CONFIG(Quaterniond, q)
	TS_DECLARE_CONFIG(Color, c)
	#undef TS_DECLARE_CONFIG
}

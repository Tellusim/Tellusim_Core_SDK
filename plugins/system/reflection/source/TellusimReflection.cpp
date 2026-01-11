// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>

#include "../include/TellusimReflectionImpl.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	String Reflection::getConstructorSignature(uint32_t index, bool names) const {
		String ret;
		uint32_t num = getNumConstructorArgs(index);
		for(uint32_t i = 0; i < num; i++) {
			if(ret) ret += ", ";
			ret += getConstructorArgType(index, i);
			if(names) {
				ret += " ";
				ret += getConstructorArgName(index, i);
			}
		}
		return ret;
	}
	
	/*
	 */
	uint32_t Reflection::findConstructor(uint32_t args) const {
		for(uint32_t i = 0; i < getNumConstructors(); i++) {
			if(args != Maxu32 && getNumConstructorArgs(i) != args) continue;
			return i;
		}
		return Maxu32;
	}
	
	uint32_t Reflection::findConstructor(const char *signature) const {
		for(uint32_t i = 0; i < getNumConstructors(); i++) {
			if(getConstructorSignature(i) != signature) continue;
			return i;
		}
		uint32_t index = Maxu32;
		uint32_t distance = Maxu32;
		for(uint32_t i = 0; i < getNumConstructors(); i++) {
			uint32_t d = getConstructorSignature(i).distance(signature);
			if(distance < d) continue;
			distance = d;
			index = i;
		}
		if(index != Maxu32) {
			String s = getConstructorSignature(index);
			TS_LOGF(Error, "Reflection::findConstructor(): can't find %s(%s) using %s(%s)\n", getName(), signature, getName(), s.get());
		}
		return index;
	}
	
	uint32_t Reflection::findConstructor(const String &signature) const {
		return findConstructor(signature.get());
	}
	
	/*
	 */
	bool Reflection::isConstructor(uint32_t args) const {
		return (findConstructor(args) != Maxu32);
	}
	
	bool Reflection::isConstructor(const char *signature) const {
		return (findConstructor(signature) != Maxu32);
	}
	
	bool Reflection::isConstructor(const String &signature) const {
		return (findConstructor(signature) != Maxu32);
	}
	
	/*
	 */
	Reflection::ConstructorPtr Reflection::getConstructorArgs(uint32_t args) const {
		uint32_t index = findConstructor(args);
		if(index != Maxu32) return getConstructor(index);
		if(args == Maxu32) TS_LOGF(Error, "Reflection::getConstructorArgs(): can't find %s(...) constructor\n", getName());
		else TS_LOGF(Error, "Reflection::getConstructorArgs(): can't find %s() constructor with %u arguments\n", getName(), args);
		return ConstructorPtr((Constructor*)nullptr);
	}
	
	Reflection::ConstructorPtr Reflection::getConstructor(const char *signature) const {
		uint32_t index = findConstructor(signature);
		if(index != Maxu32) return getConstructor(index);
		TS_LOGF(Error, "Reflection::getConstructor(): can't find %s(%s) constructor\n", getName(), signature);
		return ConstructorPtr((Constructor*)nullptr);
	}
	
	Reflection::ConstructorPtr Reflection::getConstructor(const String &signature) const {
		return getConstructor(signature.get());
	}
	
	/*
	 */
	String Reflection::getFunctionSignature(uint32_t index, bool names) const {
		String ret;
		uint32_t num = getNumFunctionArgs(index);
		for(uint32_t i = 0; i < num; i++) {
			if(ret) ret += ", ";
			ret += getFunctionArgType(index, i);
			if(names) {
				ret += " ";
				ret += getFunctionArgName(index, i);
			}
		}
		return ret;
	}
	
	/*
	 */
	uint32_t Reflection::findFunction(const char *name, uint32_t args) const {
		for(uint32_t i = 0; i < getNumFunctions(); i++) {
			if(args != Maxu32 && getNumFunctionArgs(i) != args) continue;
			if(strcmp(getFunctionName(i), name)) continue;
			return i;
		}
		return Maxu32;
	}
	
	uint32_t Reflection::findFunction(const String &name, uint32_t args) const {
		return findFunction(name.get(), args);
	}
	
	uint32_t Reflection::findFunction(const char *name, const char *signature) const {
		for(uint32_t i = 0; i < getNumFunctions(); i++) {
			if(strcmp(getFunctionName(i), name)) continue;
			if(getFunctionSignature(i) != signature) continue;
			return i;
		}
		uint32_t index = Maxu32;
		uint32_t distance = Maxu32;
		for(uint32_t i = 0; i < getNumFunctions(); i++) {
			if(strcmp(getFunctionName(i), name)) continue;
			uint32_t d = getFunctionSignature(i).distance(signature);
			if(distance < d) continue;
			distance = d;
			index = i;
		}
		if(index != Maxu32) {
			String s = getFunctionSignature(index);
			TS_LOGF(Error, "Reflection::findFunction(): can't find %s::%s(%s) using %s::%s(%s)\n", getName(), name, signature, getName(), name, s.get());
		}
		return index;
	}
	
	uint32_t Reflection::findFunction(const String &name, const String &signature) const {
		return findFunction(name.get(), signature.get());
	}
	
	/*
	 */
	bool Reflection::isFunction(const char *name, uint32_t args) const {
		return (findFunction(name, args) != Maxu32);
	}
	
	bool Reflection::isFunction(const String &name, uint32_t args) const {
		return (findFunction(name, args) != Maxu32);
	}
	
	bool Reflection::isFunction(const char *name, const char *signature) const {
		return (findFunction(name, signature) != Maxu32);
	}
	
	bool Reflection::isFunction(const String &name, const String &signature) const {
		return (findFunction(name, signature) != Maxu32);
	}
	
	/*
	 */
	Reflection::FunctionPtr Reflection::getFunction(const char *name, uint32_t args) const {
		uint32_t index = findFunction(name, args);
		if(index != Maxu32) return getFunction(index);
		if(getBase()) return getBase()->getFunction(name, args);
		if(args == Maxu32) TS_LOGF(Error, "Reflection::getFunction(): can't find %s::%s(...) function\n", getName(), name);
		else TS_LOGF(Error, "Reflection::getFunction(): can't find %s::%s() function with %u arguments\n", getName(), name, args);
		return FunctionPtr((Function*)nullptr);
	}
	
	Reflection::FunctionPtr Reflection::getFunction(const String &name, uint32_t args) const {
		return getFunction(name.get(), args);
	}
	
	Reflection::FunctionPtr Reflection::getFunction(const char *name, const char *signature) const {
		uint32_t index = findFunction(name, signature);
		if(index != Maxu32) return getFunction(index);
		if(getBase()) return getBase()->getFunction(name, signature);
		TS_LOGF(Error, "Reflection::getFunction(): can't find %s::%s(%s) function\n", getName(), name, signature);
		return FunctionPtr((Function*)nullptr);
	}
	
	Reflection::FunctionPtr Reflection::getFunction(const String &name, const String &signature) const {
		return getFunction(name.get(), signature.get());
	}
	
	/*
	 */
	String Reflection::getCallbackSignature(uint32_t index, bool names) const {
		String ret;
		uint32_t num = getNumCallbackArgs(index);
		for(uint32_t i = 0; i < num; i++) {
			if(ret) ret += ", ";
			ret += getCallbackArgType(index, i);
			if(names) {
				ret += " ";
				ret += getCallbackArgName(index, i);
			}
		}
		return ret;
	}
	
	/*
	 */
	uint32_t Reflection::findCallback(const char *name) const {
		for(uint32_t i = 0; i < getNumCallbacks(); i++) {
			if(strcmp(getCallbackName(i), name)) continue;
			return i;
		}
		return Maxu32;
	}
	
	uint32_t Reflection::findCallback(const String &name) const {
		return findCallback(name.get());
	}
	
	/*
	 */
	bool Reflection::isCallback(const char *name) const {
		return (findCallback(name) != Maxu32);
	}
	
	bool Reflection::isCallback(const String &name) const {
		return (findCallback(name) != Maxu32);
	}
	
	/*
	 */
	uint32_t Reflection::findEnum(const char *name) const {
		for(uint32_t i = 0; i < getNumEnums(); i++) {
			if(!getEnumName(i) || strcmp(getEnumName(i), name)) continue;
			return i;
		}
		return Maxu32;
	}
	
	uint32_t Reflection::findEnum(const String &name) const {
		return findEnum(name.get());
	}
	
	/*
	 */
	bool Reflection::isEnum(const char *name) const {
		return (findEnum(name) != Maxu32);
	}
	
	bool Reflection::isEnum(const String &name) const {
		return (findEnum(name) != Maxu32);
	}
	
	/*
	 */
	const Reflection *Reflection::get(const String &name) {
		return get(name.get());
	}
}

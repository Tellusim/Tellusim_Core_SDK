// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_SYSTEM_REFLECTION_H__
#define __TELLUSIM_PLUGINS_SYSTEM_REFLECTION_H__

#include <core/TellusimMap.h>
#include <core/TellusimString.h>
#include <core/TellusimPointer.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Reflection
	 */
	class Reflection {
			
		public:
			
			class Constructor;
			class Destructor;
			class Function;
			
			using ConstructorPtr = AutoPtr<Constructor>;
			using DestructorPtr = AutoPtr<Destructor>;
			using FunctionPtr = AutoPtr<Function>;
			
			virtual ~Reflection() { }
			
			/// reflection name
			virtual const char *getName() const = 0;
			
			/// base reflection
			virtual const Reflection *getBase() const = 0;
			
			/// class constructors
			virtual uint32_t getNumConstructors() const = 0;
			virtual uint32_t getNumConstructorArgs(uint32_t index) const = 0;
			virtual const char *getConstructorArgType(uint32_t index, uint32_t arg) const = 0;
			virtual const char *getConstructorArgName(uint32_t index, uint32_t arg) const = 0;
			virtual const char *getConstructorArgValue(uint32_t index, uint32_t arg) const = 0;
			virtual ConstructorPtr getConstructor(uint32_t index) const = 0;
			
			String getConstructorSignature(uint32_t index, bool names = false) const;
			
			uint32_t findConstructor(uint32_t args) const;
			uint32_t findConstructor(const char *signature) const;
			uint32_t findConstructor(const String &signature) const;
			
			bool isConstructor(uint32_t args) const;
			bool isConstructor(const char *signature) const;
			bool isConstructor(const String &signature) const;
			
			ConstructorPtr getConstructorArgs(uint32_t args) const;
			ConstructorPtr getConstructor(const char *signature) const;
			ConstructorPtr getConstructor(const String &signature) const;
			
			/// class destructor
			virtual DestructorPtr getDestructor() const = 0;
			
			/// class functions
			virtual uint32_t getNumFunctions() const = 0;
			virtual bool isStaticFunction(uint32_t index) const = 0;
			virtual bool isConstFunction(uint32_t index) const = 0;
			virtual bool isVirtualFunction(uint32_t index) const = 0;
			virtual bool isAbstractFunction(uint32_t index) const = 0;
			virtual const char *getFunctionName(uint32_t index) const = 0;
			virtual const char *getFunctionType(uint32_t index) const = 0;
			virtual uint32_t getNumFunctionArgs(uint32_t index) const = 0;
			virtual const char *getFunctionArgType(uint32_t index, uint32_t arg) const = 0;
			virtual const char *getFunctionArgName(uint32_t index, uint32_t arg) const = 0;
			virtual const char *getFunctionArgValue(uint32_t index, uint32_t arg) const = 0;
			virtual FunctionPtr getFunction(uint32_t index) const = 0;
			
			String getFunctionSignature(uint32_t index, bool names = false) const;
			
			uint32_t findFunction(const char *name, uint32_t args = Maxu32) const;
			uint32_t findFunction(const String &name, uint32_t args = Maxu32) const;
			uint32_t findFunction(const char *name, const char *signature) const;
			uint32_t findFunction(const String &name, const String &signature) const;
			
			bool isFunction(const char *name, uint32_t args = Maxu32) const;
			bool isFunction(const String &name, uint32_t args = Maxu32) const;
			bool isFunction(const char *name, const char *signature) const;
			bool isFunction(const String &name, const String &signature) const;
			
			FunctionPtr getFunction(const char *name, uint32_t args = Maxu32) const;
			FunctionPtr getFunction(const String &name, uint32_t args = Maxu32) const;
			FunctionPtr getFunction(const char *name, const char *signature) const;
			FunctionPtr getFunction(const String &name, const String &signature) const;
			
			/// class callbacks
			virtual uint32_t getNumCallbacks() const = 0;
			virtual const char *getCallbackName(uint32_t index) const = 0;
			virtual const char *getCallbackType(uint32_t index) const = 0;
			virtual uint32_t getNumCallbackArgs(uint32_t index) const = 0;
			virtual const char *getCallbackArgType(uint32_t index, uint32_t arg) const = 0;
			virtual const char *getCallbackArgName(uint32_t index, uint32_t arg) const = 0;
			
			String getCallbackSignature(uint32_t index, bool names = false) const;
			
			uint32_t findCallback(const char *name) const;
			uint32_t findCallback(const String &name) const;
			
			bool isCallback(const char *name) const;
			bool isCallback(const String &name) const;
			
			/// class enumerations
			virtual uint32_t getNumEnums() const = 0;
			virtual const char *getEnumName(uint32_t index) const = 0;
			virtual uint32_t getNumEnumVars(uint32_t index) const = 0;
			virtual const char *getEnumVarName(uint32_t index, uint32_t var) const = 0;
			
			uint32_t findEnum(const char *name) const;
			uint32_t findEnum(const String &name) const;
			
			bool isEnum(const char *name) const;
			bool isEnum(const String &name) const;
			
			/// get reflection
			static const Reflection *get(const char *name);
			static const Reflection *get(const String &name);
			static const Map<const char*, Reflection*> &get();
			template <class Type> static const Reflection *get(const Type &type) { return get(type.getClassName()); }
			template <class Type> static const Reflection *get(const Type *type) { return get(type->getClassName()); }
			
			/// class constructor
			class Constructor {
				public:
					virtual ~Constructor() { }
					virtual void *run() = 0;
					virtual uint32_t getNumArgs() const = 0;
					virtual void setArg(uint32_t index, const void *ptr) = 0;
					virtual void *getArg(uint32_t index) = 0;
					void set(uint32_t index, void *ptr) { setArg(index, ptr); }
					void set(uint32_t index, const void *ptr) { setArg(index, ptr); }
					template <class Type> void set(uint32_t index, const Type &value) { setArg(index, &value); }
					template <class Type> Type get(uint32_t index) { return *(Type*)getArg(index); }
			};
			
			/// class destructor
			class Destructor {
				public:
					virtual ~Destructor() { }
					virtual void run(void *ptr) = 0;
			};
			
			/// class function
			class Function {
				public:
					virtual ~Function() { }
					virtual void run(void *ptr) = 0;
					virtual uint32_t getNumArgs() const = 0;
					virtual void setArg(uint32_t index, const void *ptr) = 0;
					virtual void *getArg(uint32_t index) = 0;
					virtual void *getRet() = 0;
					void set(uint32_t index, void *ptr) { setArg(index, ptr); }
					void set(uint32_t index, const void *ptr) { setArg(index, ptr); }
					template <class Type> void set(uint32_t index, const Type &value) { setArg(index, &value); }
					template <class Type> Type get(uint32_t index) { return *(Type*)getArg(index); }
					template <class Type> Type ret() { return *(Type*)getRet(); }
			};
			
			/// run constructor
			template <class Type> Type constructor(uint32_t args = Maxu32) const {
				ConstructorPtr constructor = getConstructorArgs(args);
				if(constructor) return run_constructor(TypeToType<Type>(), constructor);
				return Type();
			}
			template <class Type> Type constructor(const char *signature) const {
				ConstructorPtr constructor = getConstructor(signature);
				if(constructor) return run_constructor(TypeToType<Type>(), constructor);
				return Type();
			}
			template <class Type, class... List> Type constructor(uint32_t args, List... Args) const {
				ConstructorPtr constructor = getConstructorArgs(args);
				if(constructor) return run_constructor(TypeToType<Type>(), constructor, Args...);
				return Type();
			}
			template <class Type, class... List> Type constructor(const char *signature, List... Args) const {
				ConstructorPtr constructor = getConstructor(signature);
				if(constructor) return run_constructor(TypeToType<Type>(), constructor, Args...);
				return Type();
			}
			
			/// run destructor
			void destructor(void *ptr) const {
				DestructorPtr destructor = getDestructor();
				if(destructor) destructor->run(ptr);
			}
			
			/// run class function
			template <class Type> Type function(void *ptr, const char *name, uint32_t args = Maxu32) const {
				FunctionPtr function = getFunction(name, args);
				if(function) return run_function(TypeToType<Type>(), function, ptr);
				return Type();
			}
			template <class Type> Type function(void *ptr, const char *name, const char *signature) const {
				FunctionPtr function = getFunction(name, signature);
				if(function) return run_function(TypeToType<Type>(), function, ptr);
				return Type();
			}
			template <class Type, class... List> Type function(void *ptr, const char *name, uint32_t args, List... Args) const {
				FunctionPtr function = getFunction(name, args);
				if(function) return run_function(TypeToType<Type>(), function, ptr, Args...);
				return Type();
			}
			template <class Type, class... List> Type function(void *ptr, const char *name, const char *signature, List... Args) const {
				FunctionPtr function = getFunction(name, signature);
				if(function) return run_function(TypeToType<Type>(), function, ptr, Args...);
				return Type();
			}
			
			/// run static function
			template <class Type> Type function(const char *name, uint32_t args = Maxu32) const {
				FunctionPtr function = getFunction(name, args);
				if(function) return run_function(TypeToType<Type>(), function, nullptr);
				return Type();
			}
			template <class Type> Type function(const char *name, const char *signature) const {
				FunctionPtr function = getFunction(name, signature);
				if(function) return run_function(TypeToType<Type>(), function, nullptr);
				return Type();
			}
			template <class Type, class... List> Type function(const char *name, uint32_t args, List... Args) const {
				FunctionPtr function = getFunction(name, args);
				if(function) return run_function(TypeToType<Type>(), function, nullptr, Args...);
				return Type();
			}
			template <class Type, class... List> Type function(const char *name, const char *signature, List... Args) const {
				FunctionPtr function = getFunction(name, signature);
				if(function) return run_function(TypeToType<Type>(), function, nullptr, Args...);
				return Type();
			}
			
		private:
			
			/// set arguments
			template <class Ptr, class Type> static void set_args(Ptr &ptr, uint32_t index, const Type &value) {
				ptr->set(index, value);
			}
			template <class Ptr, class Type, class... List> static void set_args(Ptr &ptr, uint32_t index, const Type &value, List... Args) {
				ptr->set(index, value);
				set_args(ptr, index + 1, Args...);
			}
			
			/// run constructor
			void *run_constructor(TypeToType<void*>, ConstructorPtr &constructor) const {
				return constructor->run();
			}
			template <class Type> Type run_constructor(TypeToType<Type>, ConstructorPtr &constructor) const {
				Type *ret = (Type*)constructor->run();
				if(ret) return *ret;
				return Type();
			}
			template <class... List> void *run_constructor(TypeToType<void*>, ConstructorPtr &constructor, List... Args) const {
				set_args(constructor, 0, Args...);
				return constructor->run();
			}
			template <class Type, class... List> Type run_constructor(TypeToType<Type>, ConstructorPtr &constructor, List... Args) const {
				set_args(constructor, 0, Args...);
				Type *ret = (Type*)constructor->run();
				if(ret) return *ret;
				return Type();
			}
			
			/// run function
			void run_function(TypeToType<void>, FunctionPtr &function, void *ptr) const {
				function->run(ptr);
			}
			void *run_function(TypeToType<void*>, FunctionPtr &function, void *ptr) const {
				function->run(ptr);
				return function->getRet();
			}
			template <class Type> Type run_function(TypeToType<Type>, FunctionPtr &function, void *ptr) const {
				function->run(ptr);
				return function->ret<Type>();
			}
			template <class... List> void run_function(TypeToType<void>, FunctionPtr &function, void *ptr, List... Args) const {
				set_args(function, 0, Args...);
				function->run(ptr);
			}
			template <class... List> void *run_function(TypeToType<void*>, FunctionPtr &function, void *ptr, List... Args) const {
				set_args(function, 0, Args...);
				function->run(ptr);
				return function->getRet();
			}
			template <class Type, class... List> Type run_function(TypeToType<Type>, FunctionPtr &function, void *ptr, List... Args) const {
				set_args(function, 0, Args...);
				function->run(ptr);
				return function->ret<Type>();
			}
	};
}

#endif /* __TELLUSIM_PLUGINS_SYSTEM_REFLECTION_H__ */

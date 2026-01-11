// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_FORMAT_JSON_H__
#define __TELLUSIM_FORMAT_JSON_H__

#include <core/TellusimArray.h>
#include <core/TellusimString.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Stream;
	
	/**
	 * The Json class provides a flexible and efficient interface for working with Json data.
	 * It supports a wide range of functionalities for creating, manipulating, and querying Json data, including handling Json objects, arrays, strings, numbers, booleans, and more.
	 * This class is designed to work with nested structures and offers various methods for loading, saving, and editing Json content.
	 */
	class TS_API Json {
			
			TS_DECLARE_PTR(Json, 0)
			
		public:
			
			/// Json types
			enum Type {
				TypeUnknown = 0,
				TypeNull,
				TypeBool,
				TypeNumber,
				TypeString,
				TypeObject,
				TypeArray,
				NumTypes,
			};
			
			Json();
			explicit Json(Type type);
			explicit Json(const char *name, Type type = TypeUnknown);
			explicit Json(const String &name, Type type = TypeUnknown);
			Json(Json *parent, const char *name, Type type = TypeUnknown);
			Json(Json *parent, const String &name, Type type = TypeUnknown);
			
			/// clear json
			void clear();
			
			/// create json
			bool create(const char *str, size_t size = 0, bool owner = false);
			bool create(const String &str, size_t size = 0, bool owner = false);
			
			/// load json
			bool load(const char *name);
			bool load(const String &name);
			bool load(Stream &stream);
			
			/// save json
			bool save(const char *name, bool compact = false) const;
			bool save(const String &name, bool compact = false) const;
			bool save(Stream &stream, bool compact = false) const;
			
			/// json root
			const Json getRoot() const;
			Json getRoot();
			
			/// json parent
			uint32_t setParent(Json &parent, bool check = true);
			const Json getParent() const;
			Json getParent();
			
			/// json children
			Json addChild(const char *name, Type type = TypeUnknown, bool check = true);
			uint32_t addChild(Json &child, bool check = true);
			bool removeChild(Json &child);
			void releaseChildren();
			
			uint32_t findChild(const char *name) const;
			bool isChild(const char *name) const;
			
			const Json getChild(const char *name) const;
			Json getChild(const char *name);
			
			uint32_t getNumChildren() const;
			const Array<Json> getChildren() const;
			Array<Json> getChildren();
			const Json getChild(uint32_t index) const;
			Json getChild(uint32_t index);
			
			/// json path name
			String getPathName() const;
			
			/// json name
			void setName(const char *name);
			void setName(const String &name);
			String getName() const;
			
			/// json type
			void setType(Type type);
			Type getType() const;
			
			static const char *getTypeName(Type type);
			const char *getTypeName() const;
			
			TS_INLINE bool isUnknown() const { return (getType() == TypeUnknown); }
			TS_INLINE bool isNull() const { return (getType() == TypeNull); }
			TS_INLINE bool isBool() const { return (getType() == TypeBool); }
			TS_INLINE bool isNumber() const { return (getType() == TypeNumber); }
			TS_INLINE bool isString() const { return (getType() == TypeString); }
			TS_INLINE bool isObject() const { return (getType() == TypeObject); }
			TS_INLINE bool isArray() const { return (getType() == TypeArray); }
			
			/// json data
			/// \param radix The decimal number radix (use 16 for hexadecimal numbers).
			/// \param digits The number of digits in the floating-point representation.
			/// \param compact Remove redundant zeros at the end of the number.
			/// \param exponent Use exponent representation.
			void setData(bool value);
			void setData(int32_t value, uint32_t radix = 10);
			void setData(uint32_t value, uint32_t radix = 10);
			void setData(uint64_t value, uint32_t radix = 10);
			void setData(float32_t value, uint32_t digits = 6, bool compact = true, bool exponent = true);
			void setData(float64_t value, uint32_t digits = 12, bool compact = true, bool exponent = true);
			void setData(const char *value);
			void setData(const String &value);
			
			template <class Type> Json setData(const char *name, Type value, Json::Type type = TypeUnknown) {
				uint32_t index = (name) ? findChild(name) : Maxu32;
				Json child = (index == Maxu32) ? addChild(name, type, false) : getChild(index);
				child.setData(value);
				return child;
			}
			
			String getData() const;
			bool getDataBool() const;
			int32_t getDatai32(uint32_t radix = 10) const;
			uint32_t getDatau32(uint32_t radix = 10) const;
			uint64_t getDatau64(uint32_t radix = 10) const;
			float32_t getDataf32() const;
			float64_t getDataf64() const;
			String getNumber() const;
			String getString() const;
			
			bool getData(const char *name, bool value) const;
			int32_t getData(const char *name, int32_t value, uint32_t radix = 10) const;
			uint32_t getData(const char *name, uint32_t value, uint32_t radix = 10) const;
			uint64_t getData(const char *name, uint64_t value, uint32_t radix = 10) const;
			float32_t getData(const char *name, float32_t value) const;
			float64_t getData(const char *name, float64_t value) const;
			String getData(const char *name, const String &value = String::null) const;
			
			/// json array data
			/// \param radix The decimal number radix (use 16 for hexadecimal numbers).
			/// \param digits The number of digits in the floating-point representation.
			/// \param compact Remove redundant zeros at the end of the number.
			/// \param exponent Use exponent representation.
			void setData(const char **values, uint32_t size);
			void setData(const String *values, uint32_t size);
			void setData(const int32_t *values, uint32_t size, uint32_t radix = 10);
			void setData(const uint32_t *values, uint32_t size, uint32_t radix = 10);
			void setData(const float32_t *values, uint32_t size, uint32_t digits = 6, bool compact = true, bool exponent = true);
			void setData(const float64_t *values, uint32_t size, uint32_t digits = 12, bool compact = true, bool exponent = true);
			
			template <class Type> Json setData(const char *name, Type *values, uint32_t size, Json::Type type = TypeUnknown) {
				uint32_t index = (name) ? findChild(name) : Maxu32;
				Json child = (index == Maxu32) ? addChild(name, type, false) : getChild(index);
				child.setData(values, size);
				return child;
			}
			template <class Type> void setData(const Array<Type> &values) {
				setData(values.get(), values.size());
			}
			template <class Type> void setData(const char *name, const Array<Type> &values) {
				setData(name, values.get(), values.size());
			}
			
			uint32_t getData(String *values, uint32_t size) const;
			uint32_t getData(int32_t *values, uint32_t size, uint32_t radix = 10) const;
			uint32_t getData(uint32_t *values, uint32_t size, uint32_t radix = 10) const;
			uint32_t getData(float32_t *values, uint32_t size) const;
			uint32_t getData(float64_t *values, uint32_t size) const;
			
			template <class Type> uint32_t getData(const char *name, Type *values, uint32_t size) const {
				uint32_t index = findChild(name);
				if(index == Maxu32) return 0;
				return getChild(index).getData(values, size);
			}
			template <class Type> uint32_t getData(Array<Type> &values) const {
				return getData(values.get(), values.size());
			}
			template <class Type> uint32_t getData(const char *name, Array<Type> &values) const {
				return getData(name, values.get(), values.size());
			}
	};
}

#endif /* __TELLUSIM_FORMAT_JSON_H__ */

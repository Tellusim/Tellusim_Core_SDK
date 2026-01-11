// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_FORMAT_XML_H__
#define __TELLUSIM_FORMAT_XML_H__

#include <core/TellusimArray.h>
#include <core/TellusimString.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Stream;
	
	/**
	 * The Xml class is a comprehensive utility for managing Xml data in a flexible and efficient manner.
	 * It provides an object-oriented interface for working with Xml documents and supports a wide range of features for creating, manipulating, and querying Xml data.
	 */
	class TS_API Xml {
			
			TS_DECLARE_PTR(Xml, 0)
			
		public:
			
			Xml();
			explicit Xml(const char *name, const char *attributes = nullptr);
			explicit Xml(const String &name, const char *attributes = nullptr);
			Xml(Xml *parent, const char *name, const char *attributes = nullptr);
			Xml(Xml *parent, const String &name, const char *attributes = nullptr);
			
			/// clear xml
			void clear();
			
			/// create xml
			bool create(const char *str, size_t size = 0, bool owner = false);
			bool create(const String &str, size_t size = 0, bool owner = false);
			
			/// load xml
			bool load(const char *name);
			bool load(const String &name);
			bool load(Stream &stream);
			
			/// save xml
			bool save(const char *name, bool compact = false) const;
			bool save(const String &name, bool compact = false) const;
			bool save(Stream &stream, bool compact = false) const;
			
			/// xml root
			const Xml getRoot() const;
			Xml getRoot();
			
			/// xml parent
			uint32_t setParent(Xml &parent, bool check = true);
			const Xml getParent() const;
			Xml getParent();
			
			/// xml children
			Xml addChild(const char *name, bool check = true);
			uint32_t addChild(Xml &child, bool check = true);
			bool removeChild(Xml &child);
			void releaseChildren();
			
			uint32_t findChild(const char *name) const;
			bool isChild(const char *name) const;
			
			const Xml getChild(const char *name) const;
			Xml getChild(const char *name);
			
			uint32_t getNumChildren() const;
			const Array<Xml> getChildren() const;
			Array<Xml> getChildren();
			const Xml getChild(uint32_t index) const;
			Xml getChild(uint32_t index);
			
			/// xml path name
			String getPathName() const;
			
			/// xml name
			void setName(const char *name);
			void setName(const String &name);
			String getName() const;
			
			/// xml data
			/// \param radix The decimal number radix (use 16 for hexadecimal numbers).
			/// \param digits The number of digits in the floating-point representation.
			/// \param compact Remove redundant zeros at the end of the number.
			/// \param exponent Use exponent representation.
			void setData(bool value);
			void setData(const char *value);
			void setData(const String &value);
			void setData(int32_t value, uint32_t radix = 10);
			void setData(uint32_t value, uint32_t radix = 10);
			void setData(uint64_t value, uint32_t radix = 10);
			void setData(float32_t value, uint32_t digits = 6, bool compact = true, bool exponent = true);
			void setData(float64_t value, uint32_t digits = 12, bool compact = true, bool exponent = true);
			
			template <class Type> Xml setData(const char *name, Type value) {
				uint32_t index = findChild(name);
				Xml child = (index == Maxu32) ? addChild(name, false) : getChild(index);
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
			
			String getData(const char *name, const String &value = String::null) const;
			bool getData(const char *name, bool value) const;
			int32_t getData(const char *name, int32_t value, uint32_t radix = 10) const;
			uint32_t getData(const char *name, uint32_t value, uint32_t radix = 10) const;
			uint64_t getData(const char *name, uint64_t value, uint32_t radix = 10) const;
			float32_t getData(const char *name, float32_t value) const;
			float64_t getData(const char *name, float64_t value) const;
			
			/// xml array data
			/// \param wrap The data string wrap parameter to avoid extra-long lines.
			/// \param radix The decimal number radix (use 16 for hexadecimal numbers).
			/// \param digits The number of digits in the floating-point representation.
			/// \param compact Remove redundant zeros at the end of the number.
			/// \param exponent Use exponent representation.
			void setData(const char **values, uint32_t size, uint32_t wrap = Maxu32);
			void setData(const String *values, uint32_t size, uint32_t wrap = Maxu32);
			void setData(const int32_t *values, uint32_t size, uint32_t radix = 10, uint32_t wrap = Maxu32);
			void setData(const uint32_t *values, uint32_t size, uint32_t radix = 10, uint32_t wrap = Maxu32);
			void setData(const float32_t *values, uint32_t size, uint32_t digits = 6, bool compact = true, bool exponent = true, uint32_t wrap = Maxu32);
			void setData(const float64_t *values, uint32_t size, uint32_t digits = 12, bool compact = true, bool exponent = true, uint32_t wrap = Maxu32);
			
			template <class Type> Xml setData(const char *name, Type *values, uint32_t size) {
				uint32_t index = findChild(name);
				Xml child = (index == Maxu32) ? addChild(name, false) : getChild(index);
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
			
			/// xml attributes
			uint32_t addAttribute(const char *name);
			bool removeAttribute(const char *name);
			uint32_t findAttribute(const char *name) const;
			bool isAttribute(const char *name) const;
			void removeAttributes();
			
			uint32_t getNumAttributes() const;
			String getAttributeName(uint32_t index) const;
			
			bool setAttributes(const char *str);
			
			void setAttribute(uint32_t index, bool value);
			void setAttribute(uint32_t index, const char *value);
			void setAttribute(uint32_t index, const String &value);
			void setAttribute(uint32_t index, int32_t value, uint32_t radix = 10);
			void setAttribute(uint32_t index, uint32_t value, uint32_t radix = 10);
			void setAttribute(uint32_t index, uint64_t value, uint32_t radix = 10);
			void setAttribute(uint32_t index, float32_t value, uint32_t digits = 6, bool compact = true, bool exponent = true);
			void setAttribute(uint32_t index, float64_t value, uint32_t digits = 12, bool compact = true, bool exponent = true);
			
			template <class Type> uint32_t setAttribute(const char *name, Type value) {
				uint32_t index = findAttribute(name);
				if(index == Maxu32) index = addAttribute(name);
				setAttribute(index, value);
				return index;
			}
			
			String getAttribute(uint32_t index) const;
			int32_t getAttributei32(uint32_t index, uint32_t radix = 10) const;
			uint32_t getAttributeu32(uint32_t index, uint32_t radix = 10) const;
			uint64_t getAttributeu64(uint32_t index, uint32_t radix = 10) const;
			float32_t getAttributef32(uint32_t index) const;
			float64_t getAttributef64(uint32_t index) const;
			
			String getAttribute(const char *name, const String &value = String::null) const;
			bool getAttribute(const char *name, bool value) const;
			int32_t getAttribute(const char *name, int32_t value, uint32_t radix = 10) const;
			uint32_t getAttribute(const char *name, uint32_t value, uint32_t radix = 10) const;
			uint64_t getAttribute(const char *name, uint64_t value, uint32_t radix = 10) const;
			float32_t getAttribute(const char *name, float32_t value) const;
			float64_t getAttribute(const char *name, float64_t value) const;
			
			/// xml array attributes
			void setAttribute(uint32_t index, const char **values, uint32_t size, const char *delimiter = nullptr);
			void setAttribute(uint32_t index, const String *values, uint32_t size, const char *delimiter = nullptr);
			void setAttribute(uint32_t index, const int32_t *values, uint32_t size, uint32_t radix = 10);
			void setAttribute(uint32_t index, const uint32_t *values, uint32_t size, uint32_t radix = 10);
			void setAttribute(uint32_t index, const float32_t *values, uint32_t size, uint32_t digits = 6, bool compact = true, bool exponent = true);
			void setAttribute(uint32_t index, const float64_t *values, uint32_t size, uint32_t digits = 12, bool compact = true, bool exponent = true);
			
			template <class Type> uint32_t setAttribute(const char *name, Type *values, uint32_t size) {
				uint32_t index = findAttribute(name);
				if(index == Maxu32) index = addAttribute(name);
				setAttribute(index, values, size);
				return index;
			}
			template <class Type> void setAttribute(uint32_t index, const Array<Type> &values) {
				setAttribute(index, values.get(), values.size());
			}
			template <class Type> void setAttribute(const char *name, const Array<Type> &values) {
				setAttribute(name, values.get(), values.size());
			}
			
			uint32_t getAttribute(uint32_t index, String *values, uint32_t size, const char *delimiter = nullptr) const;
			uint32_t getAttribute(uint32_t index, int32_t *values, uint32_t size, uint32_t radix = 10) const;
			uint32_t getAttribute(uint32_t index, uint32_t *values, uint32_t size, uint32_t radix = 10) const;
			uint32_t getAttribute(uint32_t index, float32_t *values, uint32_t size) const;
			uint32_t getAttribute(uint32_t index, float64_t *values, uint32_t size) const;
			
			template <class Type> uint32_t getAttribute(const char *name, Type *values, uint32_t size) const {
				uint32_t index = findAttribute(name);
				if(index == Maxu32) return 0;
				return getAttribute(index, values, size);
			}
			template <class Type> uint32_t getAttribute(uint32_t index, Array<Type> &values) const {
				return getAttribute(index, values.get(), values.size());
			}
			template <class Type> uint32_t getAttribute(const char *name, Array<Type> &values) const {
				return getAttribute(name, values.get(), values.size());
			}
	};
}

#endif /* __TELLUSIM_FORMAT_XML_H__ */

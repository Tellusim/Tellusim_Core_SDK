// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_BLOB_H__
#define __TELLUSIM_CORE_BLOB_H__

#include <core/TellusimStream.h>

/*
 */
namespace Tellusim {
	
	/**
	 * The Blob class extends the Stream class and provides a flexible way to manage binary data located in the system memory.
	 * The class also includes functions for base64 encoding and decoding, as well as calculating message digests using MD5 and SHA1 hash algorithms.
	 */
	class TS_API Blob : public Stream {
			
			TS_DECLARE_PTR_0(Blob, 0)
			
		public:
			
			explicit Blob(const char *name = nullptr);
			explicit Blob(const String &name);
			explicit Blob(size_t size, const char *name = nullptr);
			Blob(const uint8_t *data, size_t size, const char *name = nullptr);
			Blob(const uint8_t (*blob)[256], const char *name = nullptr);
			Blob(const Blob &blob, bool move);
			
			/// clear blob
			void release();
			void clear();
			
			/// blob name
			void setName(const char *name);
			void setName(const String &name);
			
			/// blob data
			void setSize(size_t size);
			void setCapacity(size_t size);
			size_t getCapacity() const;
			bool setData(const uint8_t *data, size_t size);
			bool setData(const uint8_t (*blob)[256]);
			bool setData(const Blob &blob);
			const uint8_t *getData() const;
			uint8_t *getData();
			
			/// base64 encoding
			String encodeBase64(size_t size = 0);
			bool decodeBase64(const char *src);
			
			/// message digest algorithm
			void getMD5(uint32_t hash[4], size_t size = 0);
			String getMD5(size_t size = 0);
			
			static String getMD5(const String &str);
			static String getMD5(const void *src, size_t size);
			static String getMD5(Stream &src, size_t size = 0);
			
			/// secure hash algorithm
			void getSHA1(uint32_t hash[5], size_t size = 0);
			String getSHA1(size_t size = 0);
			
			static String getSHA1(const String &str);
			static String getSHA1(const void *src, size_t size);
			static String getSHA1(Stream &src, size_t size = 0);
	};
}

#endif /* __TELLUSIM_CORE_BLOB_H__ */

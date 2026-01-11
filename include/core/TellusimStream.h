// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_STREAM_H__
#define __TELLUSIM_CORE_STREAM_H__

#include <core/TellusimString.h>

/*
 */
namespace Tellusim {
	
	/**
	 * The Stream class provides an abstraction for reading from and writing to streams of data, supporting various formats and encoding methods.
	 * It offers a set of functionalities to manage the stream status, position, and data, including operations for checking if a stream is open, mapped, or available, and querying its size and name.
	 * The class supports a wide range of read and write operations for different data types, from basic integers and floating-point numbers to more complex encoded formats, and strings.
	 * Additionally, the Stream class supports compression and decompression of data using the ZIP and LZ4 algorithms, allowing for both reading and writing compressed streams with different encoding levels.
	 * Whether dealing with raw data, compressed streams, or formatted strings, this class offers flexible and efficient ways to manage data flow within applications.
	 */
	class TS_API Stream {
			
		protected:
			
			TS_DECLARE_PTR_0(Stream, 0)
			
		public:
			
			Stream();
			
			/// move stream
			Stream move();
			
			/// stream status
			bool isOpened() const;
			bool isMapped() const;
			bool isAvailable() const;
			size_t getSize() const;
			String getName() const;
			
			/// stream position
			size_t tell();
			bool seek(size_t offset);
			bool seekBack(size_t offset);
			bool seekCur(int64_t offset);
			
			/// stream data
			const uint8_t *getData() const;
			
			/// read/write stream
			size_t read(void *dest, size_t size);
			size_t write(const void *src, size_t size);
			bool flush();
			
			/// unterminated strings
			bool puts(const char *str);
			bool puts(const String &str);
			bool vprintf(const char *format, va_list args);
			bool printf(const char *format, ...) TS_PRINTF(2, 3);
			template <class... List> bool tprintf(const char *format, List... Args) { return puts(String::tformat(format, Args...)); }
			String gets(bool *status = nullptr);
			
			/// 8-bit integer numbers
			int8_t readi8(bool *status = nullptr);
			bool writei8(int8_t value);
			
			uint8_t readu8(bool *status = nullptr);
			bool writeu8(uint8_t value);
			
			/// 16-bit integer numbers
			int16_t readi16(bool *status = nullptr);
			bool writei16(int16_t value);
			
			uint16_t readu16(bool *status = nullptr);
			bool writeu16(uint16_t value);
			
			/// 32-bit integer numbers
			int32_t readi32(bool *status = nullptr);
			bool writei32(int32_t value);
			
			uint32_t readu32(bool *status = nullptr);
			bool writeu32(uint32_t value);
			
			/// 64-bit integer numbers
			int64_t readi64(bool *status = nullptr);
			bool writei64(int64_t value);
			
			uint64_t readu64(bool *status = nullptr);
			bool writeu64(uint64_t value);
			
			/// 32-bit floating-point numbers
			float32_t readf32(bool *status = nullptr);
			bool writef32(float32_t value);
			
			/// 64-bit floating-point numbers
			float64_t readf64(bool *status = nullptr);
			bool writef64(float64_t value);
			
			/// encoded 32-bit integer numbers
			int32_t readi32e(bool *status = nullptr);
			bool writei32e(int32_t value);
			
			uint32_t readu32e(bool *status = nullptr);
			bool writeu32e(uint32_t value);
			
			/// encoded 64-bit integer numbers
			int64_t readi64e(bool *status = nullptr);
			bool writei64e(int64_t value);
			
			uint64_t readu64e(bool *status = nullptr);
			bool writeu64e(uint64_t value);
			
			/// string with encoded 32-bit integer length
			String readString(bool *status = nullptr);
			bool writeString(const String &str);
			bool writeString(const char *str);
			
			/// string with terminated character
			String readString(char term, bool *status = nullptr, uint32_t size = Maxu32);
			bool writeString(const String &str, char term);
			bool writeString(const char *str, char term);
			
			/// read token
			String readToken(bool *status = nullptr);
			bool readToken(String &dest, bool clear = true);
			
			/// read line
			String readLine(bool *status = nullptr);
			bool readLine(String &dest, bool empty = false, bool clear = true);
			
			/// copy streams
			size_t readStream(Stream &dest, size_t size = 0, bool *status = nullptr);
			size_t writeStream(Stream &src, size_t size = 0, bool *status = nullptr);
			
			/// zip streams with encoded 32-bit length
			size_t readZip(void *dest, size_t size);
			size_t writeZip(const void *src, size_t size, int32_t level = -1);
			size_t writeZipFast(const void *src, size_t size) { return writeZip(src, size, 1); }
			size_t writeZipBest(const void *src, size_t size) { return writeZip(src, size, 9); }
			
			/// lz4 streams with encoded 32-bit length
			size_t readLz4(void *dest, size_t size);
			size_t writeLz4(const void *src, size_t size, int32_t level = -1);
			size_t writeLz4Fast(const void *src, size_t size) { return writeLz4(src, size, 1); }
			size_t writeLz4Best(const void *src, size_t size) { return writeLz4(src, size, 12); }
			
			/// zip streams
			size_t decodeZip(Stream &src, size_t size = 0, bool *status = nullptr, int32_t window = 15);
			size_t encodeZip(Stream &dest, size_t size = 0, bool *status = nullptr, int32_t level = -1);
			size_t encodeZipFast(Stream &dest, size_t size = 0, bool *status = nullptr) { return encodeZip(dest, size, status, 1); }
			size_t encodeZipBest(Stream &dest, size_t size = 0, bool *status = nullptr) { return encodeZip(dest, size, status, 9); }
			
			/// lz4 streams
			size_t decodeLz4(Stream &src, size_t size = 0, bool *status = nullptr);
			size_t encodeLz4(Stream &dest, size_t size = 0, bool *status = nullptr, int32_t level = -1);
			size_t encodeLz4Fast(Stream &dest, size_t size = 0, bool *status = nullptr) { return encodeLz4(dest, size, status, 1); }
			size_t encodeLz4Best(Stream &dest, size_t size = 0, bool *status = nullptr) { return encodeLz4(dest, size, status, 12); }
	};
}

#endif /* __TELLUSIM_CORE_STREAM_H__ */

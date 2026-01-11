// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_FORMAT_PARSER_H__
#define __TELLUSIM_FORMAT_PARSER_H__

#include <TellusimBase.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class String;
	
	/**
	 * The Parser namespace provides functions for handling and processing ASCII text.
	 * It supports a variety of operations, such as recognizing specific characters, reading tokens, and skipping over content like whitespace, comments, or symbols.
	 * These functions are crucial for parsing strings in a structured manner, typically used in the context of processing programming languages, configuration files, or other structured text formats.
	 */
	namespace Parser {
		
		/// character types
		TS_API bool isSpace(char c);
		TS_API bool isAlpha(char c);
		TS_API bool isLower(char c);
		TS_API bool isUpper(char c);
		TS_API bool isLiteral(char c);
		TS_API bool isDecimal(char c);
		TS_API bool isHexadecimal(char c);
		
		/// string types
		TS_API bool isComment(const char *str);
		TS_API bool isNumber(const char *str);
		TS_API bool isFloat(const char *str);
		TS_API bool isSigned(const char *str);
		TS_API bool isUnsigned(const char *str);
		TS_API bool isBom(const char *str);
		
		/// skip symbols
		TS_API uint32_t skipSpaces(const char *str);
		TS_API uint32_t skipSpaces(const char *str, uint32_t &line);
		
		/// skip comment
		TS_API uint32_t skipComment(const char *str);
		TS_API uint32_t skipComment(const char *str, uint32_t &line);
		
		/// expect symbols
		TS_API char getSymbol(const char *str);
		TS_API uint32_t expectSymbol(const char *str, char c);
		TS_API uint32_t expectSymbol(const char *str, char c, uint32_t &line);
		
		/// read space-separated token
		/// \param append Append to the destination
		TS_API uint32_t skipToken(const char *str);
		TS_API uint32_t skipToken(const char *str, const char *term);
		TS_API uint32_t readToken(const char *str, String &dest, bool append = false);
		TS_API uint32_t readToken(const char *str, String &dest, const char *term, bool append = false);
		
		/// expect space-separated token
		TS_API uint32_t expectToken(const char *str, const char *token);
		TS_API uint32_t expectToken(const char *str, const char *token, const char *term);
		
		/// read literal name
		/// \param append Append to the destination
		TS_API uint32_t skipName(const char *str);
		TS_API uint32_t skipName(const char *str, const char *pass);
		TS_API uint32_t readName(const char *str, String &dest, bool append = false);
		TS_API uint32_t readName(const char *str, String &dest, const char *pass, bool append = false);
		
		/// expect literal name
		TS_API uint32_t expectName(const char *str, const char *name);
		TS_API uint32_t expectName(const char *str, const char *name, const char *pass);
		
		/// read floating-point number
		/// \param append Append to the destination
		TS_API uint32_t skipFloat(const char *str);
		TS_API uint32_t readFloat(const char *str, String &dest, bool append = false);
		
		/// read decimal number
		/// \param append Append to the destination
		TS_API uint32_t skipDecimal(const char *str);
		TS_API uint32_t readDecimal(const char *str, String &dest, bool append = false);
		
		/// read hexadecimal number
		/// \param append Append to the destination
		TS_API uint32_t skipHexadecimal(const char *str);
		TS_API uint32_t readHexadecimal(const char *str, String &dest, bool append = false);
		
		/// read floating-point or integer number
		/// \param append Append to the destination
		TS_API uint32_t skipNumber(const char *str);
		TS_API uint32_t readNumber(const char *str, String &dest, bool append = false);
		
		/// read single-quoted symbol
		/// \param enclose Include quote symbols
		/// \param append Append to the destination
		TS_API uint32_t skipSymbol(const char *str);
		TS_API uint32_t readSymbol(const char *str, String &dest, bool enclose = false, bool append = false);
		
		/// read quoted string
		/// \param enclose Include quote symbols
		/// \param append Append to the destination
		TS_API uint32_t skipString(const char *str);
		TS_API uint32_t readString(const char *str, String &dest, bool enclose = false, bool append = false);
		
		/// read region of symbols
		/// \param enclose Include from/begin symbols
		/// \param append Append to the destination
		TS_API uint32_t readRegion(const char *str, String &dest, char from, char to, bool enclose = false, bool append = false);
		
		/// read line of symbols
		/// \param escape Read multiple lines
		/// \param append Append to the destination
		TS_API uint32_t skipLines(const char *str, uint32_t lines);
		TS_API uint32_t skipLine(const char *str, bool escape = false);
		TS_API uint32_t readLine(const char *str, String &dest, bool escape = false, bool append = false);
		
		/// read string with byte ordered mark
		TS_API uint32_t readBom(const char *str, String &dest, bool append = false);
		
		/// throw Parser error
		TS_API void error(const char *format, ...) TS_PRINTF(1, 2);
	}
}

#endif /* __TELLUSIM_FORMAT_PARSER_H__ */

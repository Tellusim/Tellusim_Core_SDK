// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <TellusimApp.h>
#include <TellusimFormat.h>
#include <core/TellusimCore.h>
#include <core/TellusimSystem.h>
#include <core/TellusimDirectory.h>
#include <math/TellusimMath.h>
#include <format/TellusimFormats.h>
#include <platform/TellusimPlatforms.h>
#include <interface/TellusimFont.h>
#include <interface/TellusimControls.h>
#include <interface/TellusimDialogs.h>
#include <geometry/TellusimGeometry.h>
#include <graphics/TellusimGraphics.h>
#include <parallel/TellusimParallels.h>
#include <system/TellusimController.h>
#include <system/TellusimDesktop.h>

#include "../include/TellusimJSBase.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	extern "C" {
	
	// Tellusim::String
	TS_JSAPI String *tsString_new() {
		return new String();
	}
	TS_JSAPI String *tsString_new_1(uint32_t size, char c) {
		return new String(size, c);
	}
	TS_JSAPI String *tsString_new_2(const char *str, uint32_t length) {
		return new String(str, length);
	}
	TS_JSAPI String *tsString_new_3(const wchar_t *str, uint32_t length) {
		return new String(str, length);
	}
	TS_JSAPI String *tsString_new_4(const uint32_t *str, uint32_t length) {
		return new String(str, length);
	}
	TS_JSAPI void tsString_delete(String *self) {
		delete self;
	}
	TS_JSAPI void tsString_reserve(String &self, uint32_t size, bool discard) {
		self.reserve(size, discard);
	}
	TS_JSAPI void tsString_resize(String &self, uint32_t size, char c, bool reserve) {
		self.resize(size, c, reserve);
	}
	TS_JSAPI void tsString_release(String &self) {
		self.release();
	}
	TS_JSAPI void tsString_clear(String &self) {
		self.clear();
	}
	TS_JSAPI void tsString_copy(String &self, const char *str, uint32_t length) {
		self.copy(str, length);
	}
	TS_JSAPI void tsString_copy_1(String &self, const wchar_t *str, uint32_t length) {
		self.copy(str, length);
	}
	TS_JSAPI void tsString_copy_2(String &self, const uint32_t *str, uint32_t length) {
		self.copy(str, length);
	}
	TS_JSAPI void tsString_copy_3(String &self, const String &string, uint32_t length) {
		self.copy(string, length);
	}
	TS_JSAPI void tsString_append(String &self, char c) {
		self.append(c);
	}
	TS_JSAPI void tsString_append_1(String &self, const char *str, uint32_t length) {
		self.append(str, length);
	}
	TS_JSAPI void tsString_append_2(String &self, const String &string, uint32_t length) {
		self.append(string, length);
	}
	TS_JSAPI void tsString_insert(String &self, uint32_t pos, const char *str, uint32_t length) {
		self.insert(pos, str, length);
	}
	TS_JSAPI void tsString_insert_1(String &self, uint32_t pos, const String &string, uint32_t length) {
		self.insert(pos, string, length);
	}
	TS_JSAPI void tsString_removeBack(String &self, uint32_t length) {
		self.removeBack(length);
	}
	TS_JSAPI void tsString_remove(String &self, uint32_t pos, uint32_t length) {
		self.remove(pos, length);
	}
	TS_JSAPI void tsString_reverse(String &self, uint32_t pos, uint32_t length) {
		self.reverse(pos, length);
	}
	TS_JSAPI uint32_t tsString_size(const String &self) {
		return self.size();
	}
	TS_JSAPI bool tsString_empty(const String &self) {
		return self.empty();
	}
	TS_JSAPI const char* tsString_get(const String &self) {
		return self.get();
	}
	TS_JSAPI char tsString_get_1(String &self, uint32_t index) {
		return self.get(index);
	}
	TS_JSAPI char tsString_get_2(const String &self, uint32_t index) {
		return self.get(index);
	}
	TS_JSAPI uint32_t tsString_find(const String &self, char c, uint32_t pos) {
		return self.find(c, pos);
	}
	TS_JSAPI uint32_t tsString_rfind(const String &self, char c, uint32_t pos) {
		return self.rfind(c, pos);
	}
	TS_JSAPI uint32_t tsString_count(const String &self, char c, uint32_t pos) {
		return self.count(c, pos);
	}
	TS_JSAPI uint32_t tsString_find_1(const String &self, const char *str, uint32_t pos) {
		return self.find(str, pos);
	}
	TS_JSAPI uint32_t tsString_rfind_1(const String &self, const char *str, uint32_t pos) {
		return self.rfind(str, pos);
	}
	TS_JSAPI uint32_t tsString_count_1(const String &self, const char *str, uint32_t pos) {
		return self.count(str, pos);
	}
	TS_JSAPI bool tsString_begins(const String &self, const char *str, uint32_t length, uint32_t pos) {
		return self.begins(str, length, pos);
	}
	TS_JSAPI bool tsString_contains(const String &self, const char *str, uint32_t length, uint32_t pos) {
		return self.contains(str, length, pos);
	}
	TS_JSAPI bool tsString_match(const String &self, const char *str, uint32_t length, uint32_t pos) {
		return self.match(str, length, pos);
	}
	TS_JSAPI int32_t tsString_compare(const String &self, const char *str, uint32_t pos) {
		return self.compare(str, pos);
	}
	TS_JSAPI uint32_t tsString_distance(const String &self, const char *str, bool scan, uint32_t pos) {
		return self.distance(str, scan, pos);
	}
	TS_JSAPI const char* tsString_begin(const String &self) {
		return self.begin();
	}
	TS_JSAPI const char* tsString_end(const String &self) {
		return self.end();
	}
	TS_JSAPI char tsString_front(const String &self, uint32_t index) {
		return self.front(index);
	}
	TS_JSAPI char tsString_back(const String &self, uint32_t index) {
		return self.back(index);
	}
	TS_JSAPI char tsString_front_1(String &self, uint32_t index) {
		return self.front(index);
	}
	TS_JSAPI char tsString_back_1(String &self, uint32_t index) {
		return self.back(index);
	}
	TS_JSAPI String *tsString_substring(const String &self, uint32_t pos, uint32_t length) {
		return new String(self.substring(pos, length));
	}
	TS_JSAPI String *tsString_replace(const String &self, char before, char after, uint32_t pos) {
		return new String(self.replace(before, after, pos));
	}
	TS_JSAPI String *tsString_replace_1(const String &self, const char *before, const char *after, uint32_t pos) {
		return new String(self.replace(before, after, pos));
	}
	TS_JSAPI String *tsString_replace_2(const String &self, const String &before, const String &after, uint32_t pos) {
		return new String(self.replace(before, after, pos));
	}
	TS_JSAPI String *tsString_extension(const String &self, const char *extension) {
		return new String(self.extension(extension));
	}
	TS_JSAPI String *tsString_extension_1(const String &self) {
		return new String(self.extension());
	}
	TS_JSAPI String *tsString_pathname(const String &self) {
		return new String(self.pathname());
	}
	TS_JSAPI String *tsString_basename(const String &self) {
		return new String(self.basename());
	}
	TS_JSAPI String *tsString_dirname(const String &self) {
		return new String(self.dirname());
	}
	TS_JSAPI String *tsString_relname(const char *path, const char *str) {
		return new String(String::relname(path, str));
	}
	TS_JSAPI String *tsString_relname_1(const String &path, const String &str) {
		return new String(String::relname(path, str));
	}
	TS_JSAPI String *tsString_capitalize(const String &self, const char *delimiters, const char *spaces) {
		return new String(self.capitalize(delimiters, spaces));
	}
	TS_JSAPI String *tsString_lower(const String &self) {
		return new String(self.lower());
	}
	TS_JSAPI String *tsString_upper(const String &self) {
		return new String(self.upper());
	}
	TS_JSAPI uint32_t tsString_toUtf32(const char *str, uint32_t &code) {
		return String::toUtf32(str, code);
	}
	TS_JSAPI uint32_t tsString_toUtf16(const String &self, wchar_t *d, uint32_t length) {
		return self.toUtf16(d, length);
	}
	TS_JSAPI uint32_t tsString_toUtf32_1(const String &self, uint32_t *d, uint32_t length) {
		return self.toUtf32(d, length);
	}
	TS_JSAPI uint32_t tsString_fromUtf32(String &d, uint32_t code) {
		return String::fromUtf32(d, code);
	}
	TS_JSAPI String *tsString_fromUtf16(const wchar_t *str, uint32_t length) {
		return new String(String::fromUtf16(str, length));
	}
	TS_JSAPI String *tsString_fromUtf32_1(const uint32_t *str, uint32_t length) {
		return new String(String::fromUtf32(str, length));
	}
	TS_JSAPI String *tsString_fromUrl(const char *str, uint32_t length) {
		return new String(String::fromUrl(str, length));
	}
	TS_JSAPI String *tsString_fromUrl_1(const String &string, uint32_t length) {
		return new String(String::fromUrl(string, length));
	}
	TS_JSAPI String *tsString_fromi32(String &d, int32_t value, uint32_t radix) {
		return new String(String::fromi32(d, value, radix));
	}
	TS_JSAPI String *tsString_fromi64(String &d, int64_t value, uint32_t radix) {
		return new String(String::fromi64(d, value, radix));
	}
	TS_JSAPI String *tsString_fromu32(String &d, uint32_t value, uint32_t radix) {
		return new String(String::fromu32(d, value, radix));
	}
	TS_JSAPI String *tsString_fromu64(String &d, uint64_t value, uint32_t radix) {
		return new String(String::fromu64(d, value, radix));
	}
	TS_JSAPI String *tsString_fromf32(String &d, float32_t value, uint32_t digits, bool compact, bool exponent) {
		return new String(String::fromf32(d, value, digits, compact, exponent));
	}
	TS_JSAPI String *tsString_fromf64(String &d, float64_t value, uint32_t digits, bool compact, bool exponent) {
		return new String(String::fromf64(d, value, digits, compact, exponent));
	}
	TS_JSAPI String *tsString_fromi32_1(int32_t value, uint32_t radix) {
		return new String(String::fromi32(value, radix));
	}
	TS_JSAPI String *tsString_fromi64_1(int64_t value, uint32_t radix) {
		return new String(String::fromi64(value, radix));
	}
	TS_JSAPI String *tsString_fromu32_1(uint32_t value, uint32_t radix) {
		return new String(String::fromu32(value, radix));
	}
	TS_JSAPI String *tsString_fromu64_1(uint64_t value, uint32_t radix) {
		return new String(String::fromu64(value, radix));
	}
	TS_JSAPI String *tsString_fromf32_1(float32_t value, uint32_t digits, bool compact, bool exponent) {
		return new String(String::fromf32(value, digits, compact, exponent));
	}
	TS_JSAPI String *tsString_fromf64_1(float64_t value, uint32_t digits, bool compact, bool exponent) {
		return new String(String::fromf64(value, digits, compact, exponent));
	}
	TS_JSAPI int32_t tsString_toi32(const char *str, uint32_t radix, uint32_t *size) {
		return String::toi32(str, radix, size);
	}
	TS_JSAPI int64_t tsString_toi64(const char *str, uint32_t radix, uint32_t *size) {
		return String::toi64(str, radix, size);
	}
	TS_JSAPI uint32_t tsString_tou32(const char *str, uint32_t radix, uint32_t *size) {
		return String::tou32(str, radix, size);
	}
	TS_JSAPI uint64_t tsString_tou64(const char *str, uint32_t radix, uint32_t *size) {
		return String::tou64(str, radix, size);
	}
	TS_JSAPI int32_t tsString_toi32_1(const char *str, uint32_t *size) {
		return String::toi32(str, size);
	}
	TS_JSAPI int64_t tsString_toi64_1(const char *str, uint32_t *size) {
		return String::toi64(str, size);
	}
	TS_JSAPI uint32_t tsString_tou32_1(const char *str, uint32_t *size) {
		return String::tou32(str, size);
	}
	TS_JSAPI uint64_t tsString_tou64_1(const char *str, uint32_t *size) {
		return String::tou64(str, size);
	}
	TS_JSAPI float32_t tsString_tof32(const char *str, uint32_t *size) {
		return String::tof32(str, size);
	}
	TS_JSAPI float64_t tsString_tof64(const char *str, uint32_t *size) {
		return String::tof64(str, size);
	}
	TS_JSAPI int32_t tsString_toi32_2(const String &self, uint32_t radix, uint32_t pos) {
		return self.toi32(radix, pos);
	}
	TS_JSAPI int64_t tsString_toi64_2(const String &self, uint32_t radix, uint32_t pos) {
		return self.toi64(radix, pos);
	}
	TS_JSAPI uint32_t tsString_tou32_2(const String &self, uint32_t radix, uint32_t pos) {
		return self.tou32(radix, pos);
	}
	TS_JSAPI uint64_t tsString_tou64_2(const String &self, uint32_t radix, uint32_t pos) {
		return self.tou64(radix, pos);
	}
	TS_JSAPI float32_t tsString_tof32_1(const String &self, uint32_t pos) {
		return self.tof32(pos);
	}
	TS_JSAPI float64_t tsString_tof64_1(const String &self, uint32_t pos) {
		return self.tof64(pos);
	}
	TS_JSAPI uint32_t tsString_toHashu32(const String &self, uint32_t pos) {
		return self.toHashu32(pos);
	}
	TS_JSAPI uint64_t tsString_toHashu64(const String &self, uint32_t pos) {
		return self.toHashu64(pos);
	}
	TS_JSAPI uint32_t tsString_toRGBAu8(const String &self, uint32_t pos) {
		return self.toRGBAu8(pos);
	}
	TS_JSAPI String *tsString_fromTime(uint64_t usec, uint32_t digits) {
		return new String(String::fromTime(usec, digits));
	}
	TS_JSAPI String *tsString_fromBytes(uint64_t bytes, uint32_t digits) {
		return new String(String::fromBytes(bytes, digits));
	}
	TS_JSAPI String *tsString_fromNumber(uint64_t value, uint32_t digits) {
		return new String(String::fromNumber(value, digits));
	}
	TS_JSAPI String *tsString_fromFrequency(uint64_t hz, uint32_t digits) {
		return new String(String::fromFrequency(hz, digits));
	}
	TS_JSAPI String *tsString_fromLength(float64_t distance, uint32_t digits) {
		return new String(String::fromLength(distance, digits));
	}
	TS_JSAPI String *tsString_fromAngle(float64_t angle, uint32_t digits) {
		return new String(String::fromAngle(angle, digits));
	}
	TS_JSAPI uint64_t tsString_toBytes(const char *str, uint32_t *size) {
		return String::toBytes(str, size);
	}
	TS_JSAPI uint64_t tsString_toNumber(const char *str, uint32_t *size) {
		return String::toNumber(str, size);
	}
	TS_JSAPI uint64_t tsString_toFrequency(const char *str, uint32_t *size) {
		return String::toFrequency(str, size);
	}
	TS_JSAPI float64_t tsString_toLength(const char *str, uint32_t *size) {
		return String::toLength(str, size);
	}
	TS_JSAPI uint64_t tsString_toBytes_1(const String &self, uint32_t pos, uint32_t *size) {
		return self.toBytes(pos, size);
	}
	TS_JSAPI uint64_t tsString_toNumber_1(const String &self, uint32_t pos, uint32_t *size) {
		return self.toNumber(pos, size);
	}
	TS_JSAPI uint64_t tsString_toFrequency_1(const String &self, uint32_t pos, uint32_t *size) {
		return self.toFrequency(pos, size);
	}
	TS_JSAPI float64_t tsString_toLength_1(const String &self, uint32_t pos, uint32_t *size) {
		return self.toLength(pos, size);
	}
	
	// Tellusim::App
	TS_JSAPI App *tsApp_new(int32_t argc, char **argv) {
		return new App(argc, argv);
	}
	TS_JSAPI void tsApp_delete(App *self) {
		delete self;
	}
	TS_JSAPI void tsApp_clear(App &self) {
		self.clear();
	}
	TS_JSAPI uint32_t tsApp_getPlatform(const App &self) {
		return self.getPlatform();
	}
	TS_JSAPI uint32_t tsApp_getDevice(const App &self) {
		return self.getDevice();
	}
	TS_JSAPI uint32_t tsApp_getWidth(const App &self) {
		return self.getWidth();
	}
	TS_JSAPI uint32_t tsApp_getHeight(const App &self) {
		return self.getHeight();
	}
	TS_JSAPI uint32_t tsApp_getMultisample(const App &self) {
		return self.getMultisample();
	}
	TS_JSAPI uint32_t tsApp_getNumArguments(const App &self) {
		return self.getNumArguments();
	}
	TS_JSAPI const String *tsApp_getArgument(const App &self, uint32_t num) {
		return new String(self.getArgument(num));
	}
	TS_JSAPI bool tsApp_isArgument(const App &self, const char *name) {
		return self.isArgument(name);
	}
	TS_JSAPI const String *tsApp_getArgument_1(const App &self, const char *name) {
		return new String(self.getArgument(name));
	}
	TS_JSAPI bool tsApp_create(App &self, uint32_t platform, uint32_t version) {
		return self.create((Platform)platform, version);
	}
	TS_JSAPI void tsApp_setPlatform(uint32_t platform, uint32_t device) {
		App::setPlatform((Platform)platform, device);
	}
	TS_JSAPI void tsApp_setSize(uint32_t width, uint32_t height, uint32_t multisample) {
		App::setSize(width, height, multisample);
	}
	TS_JSAPI bool tsApp_isBuildCore() {
		return App::isBuildCore();
	}
	TS_JSAPI bool tsApp_isBuildDebug() {
		return App::isBuildDebug();
	}
	TS_JSAPI bool tsApp_isBuildFloat64() {
		return App::isBuildFloat64();
	}
	TS_JSAPI String *tsApp_getBuildDate() {
		return new String(App::getBuildDate());
	}
	TS_JSAPI String *tsApp_getBuildInfo() {
		return new String(App::getBuildInfo());
	}
	TS_JSAPI uint32_t tsApp_getVersion() {
		return App::getVersion();
	}
	TS_JSAPI uint64_t tsApp_getAPIHash() {
		return App::getAPIHash();
	}
	
	// Tellusim::Async
	TS_JSAPI Async *tsAsync_new() {
		return new Async();
	}
	TS_JSAPI void tsAsync_delete(Async *self) {
		delete self;
	}
	TS_JSAPI bool tsAsync_equalPtr(const Async &self, const Async &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Async *tsAsync_clonePtr(const Async &self) {
		return new Async(self.clonePtr());
	}
	TS_JSAPI void tsAsync_clearPtr(Async &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsAsync_destroyPtr(Async &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsAsync_acquirePtr(Async &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsAsync_unacquirePtr(Async &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsAsync_isValidPtr(const Async &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsAsync_isOwnerPtr(const Async &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsAsync_isConstPtr(const Async &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsAsync_getCountPtr(const Async &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsAsync_getInternalPtr(const Async &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI bool tsAsync_init(Async &self, uint32_t num) {
		return self.init(num);
	}
	TS_JSAPI bool tsAsync_shutdown(Async &self) {
		return self.shutdown();
	}
	TS_JSAPI bool tsAsync_isInitialized(const Async &self) {
		return self.isInitialized();
	}
	TS_JSAPI uint32_t tsAsync_getNumCores() {
		return Async::getNumCores();
	}
	TS_JSAPI uint32_t tsAsync_getNumThreads(const Async &self) {
		return self.getNumThreads();
	}
	TS_JSAPI void tsAsync_clear(Async &self) {
		self.clear();
	}
	TS_JSAPI uint32_t tsAsync_getNumTasks(const Async &self, bool check) {
		return self.getNumTasks(check);
	}
	TS_JSAPI bool tsAsync_check(const Async &self) {
		return self.check();
	}
	TS_JSAPI bool tsAsync_wait(const Async &self) {
		return self.wait();
	}
	
	// Tellusim::Stream
	TS_JSAPI Stream *tsStream_new() {
		return new Stream();
	}
	TS_JSAPI void tsStream_delete(Stream *self) {
		delete self;
	}
	TS_JSAPI bool tsStream_equalPtr(const Stream &self, const Stream &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Stream *tsStream_clonePtr(const Stream &self) {
		return new Stream(self.clonePtr());
	}
	TS_JSAPI void tsStream_clearPtr(Stream &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsStream_destroyPtr(Stream &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsStream_acquirePtr(Stream &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsStream_unacquirePtr(Stream &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsStream_isValidPtr(const Stream &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsStream_isOwnerPtr(const Stream &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsStream_isConstPtr(const Stream &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsStream_getCountPtr(const Stream &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsStream_getInternalPtr(const Stream &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI Stream *tsStream_move(Stream &self) {
		return new Stream(self.move());
	}
	TS_JSAPI bool tsStream_isOpened(const Stream &self) {
		return self.isOpened();
	}
	TS_JSAPI bool tsStream_isMapped(const Stream &self) {
		return self.isMapped();
	}
	TS_JSAPI bool tsStream_isAvailable(const Stream &self) {
		return self.isAvailable();
	}
	TS_JSAPI size_t tsStream_getSize(const Stream &self) {
		return self.getSize();
	}
	TS_JSAPI String *tsStream_getName(const Stream &self) {
		return new String(self.getName());
	}
	TS_JSAPI size_t tsStream_tell(Stream &self) {
		return self.tell();
	}
	TS_JSAPI bool tsStream_seek(Stream &self, size_t offset) {
		return self.seek(offset);
	}
	TS_JSAPI bool tsStream_seekBack(Stream &self, size_t offset) {
		return self.seekBack(offset);
	}
	TS_JSAPI bool tsStream_seekCur(Stream &self, int64_t offset) {
		return self.seekCur(offset);
	}
	TS_JSAPI const uint8_t* tsStream_getData(const Stream &self) {
		return self.getData();
	}
	TS_JSAPI size_t tsStream_read(Stream &self, void *dest, size_t size) {
		return self.read(dest, size);
	}
	TS_JSAPI size_t tsStream_write(Stream &self, const void *src, size_t size) {
		return self.write(src, size);
	}
	TS_JSAPI bool tsStream_flush(Stream &self) {
		return self.flush();
	}
	TS_JSAPI bool tsStream_puts(Stream &self, const char *str) {
		return self.puts(str);
	}
	TS_JSAPI bool tsStream_puts_1(Stream &self, const String &str) {
		return self.puts(str);
	}
	TS_JSAPI String *tsStream_gets(Stream &self, bool *status) {
		return new String(self.gets(status));
	}
	TS_JSAPI int8_t tsStream_readi8(Stream &self, bool *status) {
		return self.readi8(status);
	}
	TS_JSAPI bool tsStream_writei8(Stream &self, int8_t value) {
		return self.writei8(value);
	}
	TS_JSAPI uint8_t tsStream_readu8(Stream &self, bool *status) {
		return self.readu8(status);
	}
	TS_JSAPI bool tsStream_writeu8(Stream &self, uint8_t value) {
		return self.writeu8(value);
	}
	TS_JSAPI int16_t tsStream_readi16(Stream &self, bool *status) {
		return self.readi16(status);
	}
	TS_JSAPI bool tsStream_writei16(Stream &self, int16_t value) {
		return self.writei16(value);
	}
	TS_JSAPI uint16_t tsStream_readu16(Stream &self, bool *status) {
		return self.readu16(status);
	}
	TS_JSAPI bool tsStream_writeu16(Stream &self, uint16_t value) {
		return self.writeu16(value);
	}
	TS_JSAPI int32_t tsStream_readi32(Stream &self, bool *status) {
		return self.readi32(status);
	}
	TS_JSAPI bool tsStream_writei32(Stream &self, int32_t value) {
		return self.writei32(value);
	}
	TS_JSAPI uint32_t tsStream_readu32(Stream &self, bool *status) {
		return self.readu32(status);
	}
	TS_JSAPI bool tsStream_writeu32(Stream &self, uint32_t value) {
		return self.writeu32(value);
	}
	TS_JSAPI int64_t tsStream_readi64(Stream &self, bool *status) {
		return self.readi64(status);
	}
	TS_JSAPI bool tsStream_writei64(Stream &self, int64_t value) {
		return self.writei64(value);
	}
	TS_JSAPI uint64_t tsStream_readu64(Stream &self, bool *status) {
		return self.readu64(status);
	}
	TS_JSAPI bool tsStream_writeu64(Stream &self, uint64_t value) {
		return self.writeu64(value);
	}
	TS_JSAPI float32_t tsStream_readf32(Stream &self, bool *status) {
		return self.readf32(status);
	}
	TS_JSAPI bool tsStream_writef32(Stream &self, float32_t value) {
		return self.writef32(value);
	}
	TS_JSAPI float64_t tsStream_readf64(Stream &self, bool *status) {
		return self.readf64(status);
	}
	TS_JSAPI bool tsStream_writef64(Stream &self, float64_t value) {
		return self.writef64(value);
	}
	TS_JSAPI int32_t tsStream_readi32e(Stream &self, bool *status) {
		return self.readi32e(status);
	}
	TS_JSAPI bool tsStream_writei32e(Stream &self, int32_t value) {
		return self.writei32e(value);
	}
	TS_JSAPI uint32_t tsStream_readu32e(Stream &self, bool *status) {
		return self.readu32e(status);
	}
	TS_JSAPI bool tsStream_writeu32e(Stream &self, uint32_t value) {
		return self.writeu32e(value);
	}
	TS_JSAPI int64_t tsStream_readi64e(Stream &self, bool *status) {
		return self.readi64e(status);
	}
	TS_JSAPI bool tsStream_writei64e(Stream &self, int64_t value) {
		return self.writei64e(value);
	}
	TS_JSAPI uint64_t tsStream_readu64e(Stream &self, bool *status) {
		return self.readu64e(status);
	}
	TS_JSAPI bool tsStream_writeu64e(Stream &self, uint64_t value) {
		return self.writeu64e(value);
	}
	TS_JSAPI String *tsStream_readString(Stream &self, bool *status) {
		return new String(self.readString(status));
	}
	TS_JSAPI bool tsStream_writeString(Stream &self, const String &str) {
		return self.writeString(str);
	}
	TS_JSAPI bool tsStream_writeString_1(Stream &self, const char *str) {
		return self.writeString(str);
	}
	TS_JSAPI String *tsStream_readString_1(Stream &self, char term, bool *status, uint32_t size) {
		return new String(self.readString(term, status, size));
	}
	TS_JSAPI bool tsStream_writeString_2(Stream &self, const String &str, char term) {
		return self.writeString(str, term);
	}
	TS_JSAPI bool tsStream_writeString_3(Stream &self, const char *str, char term) {
		return self.writeString(str, term);
	}
	TS_JSAPI String *tsStream_readToken(Stream &self, bool *status) {
		return new String(self.readToken(status));
	}
	TS_JSAPI bool tsStream_readToken_1(Stream &self, String &dest, bool clear) {
		return self.readToken(dest, clear);
	}
	TS_JSAPI String *tsStream_readLine(Stream &self, bool *status) {
		return new String(self.readLine(status));
	}
	TS_JSAPI bool tsStream_readLine_1(Stream &self, String &dest, bool empty, bool clear) {
		return self.readLine(dest, empty, clear);
	}
	TS_JSAPI size_t tsStream_readStream(Stream &self, Stream &dest, size_t size, bool *status) {
		return self.readStream(dest, size, status);
	}
	TS_JSAPI size_t tsStream_writeStream(Stream &self, Stream &src, size_t size, bool *status) {
		return self.writeStream(src, size, status);
	}
	TS_JSAPI size_t tsStream_readZip(Stream &self, void *dest, size_t size) {
		return self.readZip(dest, size);
	}
	TS_JSAPI size_t tsStream_writeZip(Stream &self, const void *src, size_t size, int32_t level) {
		return self.writeZip(src, size, level);
	}
	TS_JSAPI size_t tsStream_writeZipFast(Stream &self, const void *src, size_t size) {
		return self.writeZipFast(src, size);
	}
	TS_JSAPI size_t tsStream_writeZipBest(Stream &self, const void *src, size_t size) {
		return self.writeZipBest(src, size);
	}
	TS_JSAPI size_t tsStream_readLz4(Stream &self, void *dest, size_t size) {
		return self.readLz4(dest, size);
	}
	TS_JSAPI size_t tsStream_writeLz4(Stream &self, const void *src, size_t size, int32_t level) {
		return self.writeLz4(src, size, level);
	}
	TS_JSAPI size_t tsStream_writeLz4Fast(Stream &self, const void *src, size_t size) {
		return self.writeLz4Fast(src, size);
	}
	TS_JSAPI size_t tsStream_writeLz4Best(Stream &self, const void *src, size_t size) {
		return self.writeLz4Best(src, size);
	}
	TS_JSAPI size_t tsStream_decodeZip(Stream &self, Stream &src, size_t size, bool *status, int32_t window) {
		return self.decodeZip(src, size, status, window);
	}
	TS_JSAPI size_t tsStream_encodeZip(Stream &self, Stream &dest, size_t size, bool *status, int32_t level) {
		return self.encodeZip(dest, size, status, level);
	}
	TS_JSAPI size_t tsStream_encodeZipFast(Stream &self, Stream &dest, size_t size, bool *status) {
		return self.encodeZipFast(dest, size, status);
	}
	TS_JSAPI size_t tsStream_encodeZipBest(Stream &self, Stream &dest, size_t size, bool *status) {
		return self.encodeZipBest(dest, size, status);
	}
	TS_JSAPI size_t tsStream_decodeLz4(Stream &self, Stream &src, size_t size, bool *status) {
		return self.decodeLz4(src, size, status);
	}
	TS_JSAPI size_t tsStream_encodeLz4(Stream &self, Stream &dest, size_t size, bool *status, int32_t level) {
		return self.encodeLz4(dest, size, status, level);
	}
	TS_JSAPI size_t tsStream_encodeLz4Fast(Stream &self, Stream &dest, size_t size, bool *status) {
		return self.encodeLz4Fast(dest, size, status);
	}
	TS_JSAPI size_t tsStream_encodeLz4Best(Stream &self, Stream &dest, size_t size, bool *status) {
		return self.encodeLz4Best(dest, size, status);
	}
	
	// Tellusim::Blob
	TS_JSAPI Blob *tsBlob_new(const char *name) {
		return new Blob(name);
	}
	TS_JSAPI Blob *tsBlob_new_1(const String &name) {
		return new Blob(name);
	}
	TS_JSAPI Blob *tsBlob_new_2(size_t size, const char *name) {
		return new Blob(size, name);
	}
	TS_JSAPI Blob *tsBlob_new_3(const uint8_t *data, size_t size, const char *name) {
		return new Blob(data, size, name);
	}
	TS_JSAPI Blob *tsBlob_new_4(const Blob &blob, bool move) {
		return new Blob(blob, move);
	}
	TS_JSAPI void tsBlob_delete(Blob *self) {
		delete self;
	}
	TS_JSAPI void tsBlob_release(Blob &self) {
		self.release();
	}
	TS_JSAPI void tsBlob_clear(Blob &self) {
		self.clear();
	}
	TS_JSAPI void tsBlob_setName(Blob &self, const char *name) {
		self.setName(name);
	}
	TS_JSAPI void tsBlob_setName_1(Blob &self, const String &name) {
		self.setName(name);
	}
	TS_JSAPI void tsBlob_setSize(Blob &self, size_t size) {
		self.setSize(size);
	}
	TS_JSAPI void tsBlob_setCapacity(Blob &self, size_t size) {
		self.setCapacity(size);
	}
	TS_JSAPI size_t tsBlob_getCapacity(const Blob &self) {
		return self.getCapacity();
	}
	TS_JSAPI bool tsBlob_setData(Blob &self, const uint8_t *data, size_t size) {
		return self.setData(data, size);
	}
	TS_JSAPI bool tsBlob_setData_1(Blob &self, const Blob &blob) {
		return self.setData(blob);
	}
	TS_JSAPI const uint8_t* tsBlob_getData(const Blob &self) {
		return self.getData();
	}
	TS_JSAPI uint8_t* tsBlob_getData_1(Blob &self) {
		return self.getData();
	}
	TS_JSAPI String *tsBlob_encodeBase64(Blob &self, size_t size) {
		return new String(self.encodeBase64(size));
	}
	TS_JSAPI bool tsBlob_decodeBase64(Blob &self, const char *src) {
		return self.decodeBase64(src);
	}
	TS_JSAPI void tsBlob_getMD5(Blob &self, uint32_t hash[4], size_t size) {
		self.getMD5(hash, size);
	}
	TS_JSAPI String *tsBlob_getMD5_1(Blob &self, size_t size) {
		return new String(self.getMD5(size));
	}
	TS_JSAPI String *tsBlob_getMD5_2(const String &str) {
		return new String(Blob::getMD5(str));
	}
	TS_JSAPI String *tsBlob_getMD5_3(const void *src, size_t size) {
		return new String(Blob::getMD5(src, size));
	}
	TS_JSAPI String *tsBlob_getMD5_4(Stream &src, size_t size) {
		return new String(Blob::getMD5(src, size));
	}
	TS_JSAPI void tsBlob_getSHA1(Blob &self, uint32_t hash[5], size_t size) {
		self.getSHA1(hash, size);
	}
	TS_JSAPI String *tsBlob_getSHA1_1(Blob &self, size_t size) {
		return new String(self.getSHA1(size));
	}
	TS_JSAPI String *tsBlob_getSHA1_2(const String &str) {
		return new String(Blob::getSHA1(str));
	}
	TS_JSAPI String *tsBlob_getSHA1_3(const void *src, size_t size) {
		return new String(Blob::getSHA1(src, size));
	}
	TS_JSAPI String *tsBlob_getSHA1_4(Stream &src, size_t size) {
		return new String(Blob::getSHA1(src, size));
	}
	
	// Tellusim::File
	TS_JSAPI File *tsFile_new() {
		return new File();
	}
	TS_JSAPI void tsFile_delete(File *self) {
		delete self;
	}
	TS_JSAPI bool tsFile_open(File &self, const char *name, const char *mode) {
		return self.open(name, mode);
	}
	TS_JSAPI bool tsFile_open_1(File &self, const String &name, const char *mode) {
		return self.open(name, mode);
	}
	TS_JSAPI bool tsFile_open_2(File &self, int32_t fd, const char *name, const char *mode) {
		return self.open(fd, name, mode);
	}
	TS_JSAPI bool tsFile_popen(File &self, const char *command, const char *mode) {
		return self.popen(command, mode);
	}
	TS_JSAPI bool tsFile_popen_1(File &self, const String &command, const char *mode) {
		return self.popen(command, mode);
	}
	TS_JSAPI void tsFile_close(File &self) {
		self.close();
	}
	TS_JSAPI bool tsFile_isFile(const char *name) {
		return File::isFile(name);
	}
	TS_JSAPI bool tsFile_isFile_1(const String &name) {
		return File::isFile(name);
	}
	TS_JSAPI uint64_t tsFile_getMTime(const char *name) {
		return File::getMTime(name);
	}
	TS_JSAPI size_t tsFile_getSize(const char *name) {
		return File::getSize(name);
	}
	TS_JSAPI bool tsFile_remove(const char *name) {
		return File::remove(name);
	}
	
	// Tellusim::Socket
	TS_JSAPI Socket *tsSocket_new(uint32_t type) {
		return new Socket((Socket::Type)type);
	}
	TS_JSAPI void tsSocket_delete(Socket *self) {
		delete self;
	}
	TS_JSAPI bool tsSocket_open(Socket &self, uint16_t port, uint16_t num) {
		return self.open(port, num);
	}
	TS_JSAPI bool tsSocket_open_1(Socket &self, const char *name, uint16_t port) {
		return self.open(name, port);
	}
	TS_JSAPI bool tsSocket_open_2(Socket &self, const String &name, uint16_t port) {
		return self.open(name, port);
	}
	TS_JSAPI void tsSocket_close(Socket &self) {
		self.close();
	}
	TS_JSAPI bool tsSocket_connect(Socket &self, uint32_t sec, uint32_t usec) {
		return self.connect(sec, usec);
	}
	TS_JSAPI bool tsSocket_accept(Socket &self, Socket &socket) {
		return self.accept(socket);
	}
	TS_JSAPI bool tsSocket_select(Socket &self, uint32_t sec, uint32_t usec) {
		return self.select(sec, usec);
	}
	TS_JSAPI bool tsSocket_setTimeout(Socket &self, uint32_t sec) {
		return self.setTimeout(sec);
	}
	TS_JSAPI uint32_t tsSocket_getTimeout(const Socket &self) {
		return self.getTimeout();
	}
	TS_JSAPI bool tsSocket_setBlock(Socket &self, bool block) {
		return self.setBlock(block);
	}
	TS_JSAPI bool tsSocket_getBlock(const Socket &self) {
		return self.getBlock();
	}
	TS_JSAPI bool tsSocket_setDelay(Socket &self, bool delay) {
		return self.setDelay(delay);
	}
	TS_JSAPI bool tsSocket_getDelay(const Socket &self) {
		return self.getDelay();
	}
	TS_JSAPI void tsSocket_setName(Socket &self, const char *name) {
		self.setName(name);
	}
	TS_JSAPI void tsSocket_setName_1(Socket &self, const String &name) {
		self.setName(name);
	}
	TS_JSAPI uint16_t tsSocket_getPort(const Socket &self) {
		return self.getPort();
	}
	TS_JSAPI int32_t tsSocket_getFD(const Socket &self) {
		return self.getFD();
	}
	TS_JSAPI uint32_t tsSocket_getType(const Socket &self) {
		return self.getType();
	}
	TS_JSAPI String *tsSocket_getAddress(const char *delimiter) {
		return new String(Socket::getAddress(delimiter));
	}
	
	// Tellusim::SocketSSL
	TS_JSAPI SocketSSL *tsSocketSSL_new() {
		return new SocketSSL();
	}
	TS_JSAPI void tsSocketSSL_delete(SocketSSL *self) {
		delete self;
	}
	TS_JSAPI bool tsSocketSSL_equalSocketPtr(const SocketSSL &self, const Socket &base) {
		return self.operator==(base);
	}
	TS_JSAPI SocketSSL *tsSocketSSL_castSocketPtr(const Socket &self) {
		return new SocketSSL(self);
	}
	TS_JSAPI Socket *tsSocketSSL_baseSocketPtr(const SocketSSL &self) {
		return new Socket(self.getSocket());
	}
	TS_JSAPI bool tsSocketSSL_handshake(SocketSSL &self, const char *name) {
		return self.handshake(name);
	}
	TS_JSAPI bool tsSocketSSL_accept(SocketSSL &self, SocketSSL &socket) {
		return self.accept(socket);
	}
	TS_JSAPI bool tsSocketSSL_accept_1(SocketSSL &self, Socket &socket) {
		return self.accept(socket);
	}
	TS_JSAPI bool tsSocketSSL_load(SocketSSL &self, Stream &stream) {
		return self.load(stream);
	}
	TS_JSAPI bool tsSocketSSL_load_1(SocketSSL &self, const char *name) {
		return self.load(name);
	}
	TS_JSAPI bool tsSocketSSL_load_2(SocketSSL &self, const String &name) {
		return self.load(name);
	}
	TS_JSAPI bool tsSocketSSL_isConnected(const SocketSSL &self) {
		return self.isConnected();
	}
	
	// Tellusim::Source
	TS_JSAPI Source *tsSource_new() {
		return new Source();
	}
	TS_JSAPI Source *tsSource_new_1(const uint8_t *data, size_t size, const char *name) {
		return new Source(data, size, name);
	}
	TS_JSAPI void tsSource_delete(Source *self) {
		delete self;
	}
	TS_JSAPI bool tsSource_open(Source &self, const char *name, bool callback, bool write) {
		return self.open(name, callback, write);
	}
	TS_JSAPI bool tsSource_open_1(Source &self, const String &name, bool callback, bool write) {
		return self.open(name, callback, write);
	}
	TS_JSAPI void tsSource_close(Source &self) {
		self.close();
	}
	TS_JSAPI void tsSource_setName(Source &self, const char *name, size_t offset, size_t size) {
		self.setName(name, offset, size);
	}
	TS_JSAPI void tsSource_setName_1(Source &self, const String &name, size_t offset, size_t size) {
		self.setName(name, offset, size);
	}
	TS_JSAPI void tsSource_setData(Source &self, const uint8_t *data, size_t size, const char *name) {
		self.setData(data, size, name);
	}
	TS_JSAPI bool tsSource_isSource(const char *name) {
		return Source::isSource(name);
	}
	TS_JSAPI bool tsSource_isSource_1(const String &name) {
		return Source::isSource(name);
	}
	TS_JSAPI uint64_t tsSource_getMTime(const char *name) {
		return Source::getMTime(name);
	}
	TS_JSAPI size_t tsSource_getSize(const char *name) {
		return Source::getSize(name);
	}
	
	// Tellusim::Date
	TS_JSAPI Date *tsDate_new() {
		return new Date();
	}
	TS_JSAPI Date *tsDate_new_1(int64_t time, bool local) {
		return new Date(time, local);
	}
	TS_JSAPI Date *tsDate_new_2(const char *str, const char *format) {
		return new Date(str, format);
	}
	TS_JSAPI void tsDate_delete(Date *self) {
		delete self;
	}
	TS_JSAPI bool tsDate_equalPtr(const Date &self, const Date &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Date *tsDate_clonePtr(const Date &self) {
		return new Date(self.clonePtr());
	}
	TS_JSAPI void tsDate_clearPtr(Date &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsDate_destroyPtr(Date &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsDate_acquirePtr(Date &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsDate_unacquirePtr(Date &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsDate_isValidPtr(const Date &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsDate_isOwnerPtr(const Date &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsDate_isConstPtr(const Date &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsDate_getCountPtr(const Date &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsDate_getInternalPtr(const Date &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsDate_clear(Date &self) {
		self.clear();
	}
	TS_JSAPI void tsDate_setTime(Date &self, int64_t time, bool local) {
		self.setTime(time, local);
	}
	TS_JSAPI int64_t tsDate_getTime(const Date &self, bool local) {
		return self.getTime(local);
	}
	TS_JSAPI bool tsDate_setString(Date &self, const char *str, const char *format) {
		return self.setString(str, format);
	}
	TS_JSAPI String *tsDate_getString(const Date &self, const char *format) {
		return new String(self.getString(format));
	}
	TS_JSAPI void tsDate_setYear(Date &self, uint32_t year) {
		self.setYear(year);
	}
	TS_JSAPI void tsDate_setMonth(Date &self, uint32_t month) {
		self.setMonth(month);
	}
	TS_JSAPI void tsDate_setDate(Date &self, uint32_t date) {
		self.setDate(date);
	}
	TS_JSAPI void tsDate_setDay(Date &self, uint32_t day) {
		self.setDay(day);
	}
	TS_JSAPI void tsDate_setHours(Date &self, uint32_t hours) {
		self.setHours(hours);
	}
	TS_JSAPI void tsDate_setMinutes(Date &self, uint32_t minutes) {
		self.setMinutes(minutes);
	}
	TS_JSAPI void tsDate_setSeconds(Date &self, uint32_t seconds) {
		self.setSeconds(seconds);
	}
	TS_JSAPI uint32_t tsDate_getYear(const Date &self) {
		return self.getYear();
	}
	TS_JSAPI uint32_t tsDate_getMonth(const Date &self) {
		return self.getMonth();
	}
	TS_JSAPI uint32_t tsDate_getDate(const Date &self) {
		return self.getDate();
	}
	TS_JSAPI uint32_t tsDate_getDay(const Date &self) {
		return self.getDay();
	}
	TS_JSAPI uint32_t tsDate_getHours(const Date &self) {
		return self.getHours();
	}
	TS_JSAPI uint32_t tsDate_getMinutes(const Date &self) {
		return self.getMinutes();
	}
	TS_JSAPI uint32_t tsDate_getSeconds(const Date &self) {
		return self.getSeconds();
	}
	TS_JSAPI int32_t tsDate_getTimeZone() {
		return Date::getTimeZone();
	}
	
	// Tellusim::Info
	TS_JSAPI Info *tsInfo_new() {
		return new Info();
	}
	TS_JSAPI void tsInfo_delete(Info *self) {
		delete self;
	}
	TS_JSAPI bool tsInfo_equalPtr(const Info &self, const Info &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Info *tsInfo_clonePtr(const Info &self) {
		return new Info(self.clonePtr());
	}
	TS_JSAPI void tsInfo_clearPtr(Info &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsInfo_destroyPtr(Info &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsInfo_acquirePtr(Info &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsInfo_unacquirePtr(Info &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsInfo_isValidPtr(const Info &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsInfo_isOwnerPtr(const Info &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsInfo_isConstPtr(const Info &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsInfo_getCountPtr(const Info &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsInfo_getInternalPtr(const Info &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI size_t tsInfo_getSystemMemory(const Info &self) {
		return self.getSystemMemory();
	}
	TS_JSAPI uint64_t tsInfo_getSystemUptime(const Info &self) {
		return self.getSystemUptime();
	}
	TS_JSAPI String *tsInfo_getSystemName(const Info &self) {
		return new String(self.getSystemName());
	}
	TS_JSAPI String *tsInfo_getSystemVersion(const Info &self) {
		return new String(self.getSystemVersion());
	}
	TS_JSAPI String *tsInfo_getKernelVersion(const Info &self) {
		return new String(self.getKernelVersion());
	}
	TS_JSAPI uint32_t tsInfo_getCPUCount(const Info &self) {
		return self.getCPUCount();
	}
	TS_JSAPI String *tsInfo_getCPUName(const Info &self, uint32_t index) {
		return new String(self.getCPUName(index));
	}
	TS_JSAPI String *tsInfo_getCPUVendor(const Info &self, uint32_t index) {
		return new String(self.getCPUVendor(index));
	}
	TS_JSAPI uint32_t tsInfo_getCPUCores(const Info &self, uint32_t index) {
		return self.getCPUCores(index);
	}
	TS_JSAPI uint32_t tsInfo_getCPUThreads(const Info &self, uint32_t index) {
		return self.getCPUThreads(index);
	}
	TS_JSAPI uint64_t tsInfo_getCPUFrequency(const Info &self, uint32_t index) {
		return self.getCPUFrequency(index);
	}
	TS_JSAPI uint32_t tsInfo_getCPUTemperature(const Info &self, uint32_t index) {
		return self.getCPUTemperature(index);
	}
	TS_JSAPI uint32_t tsInfo_getCPUUtilization(const Info &self, uint32_t index) {
		return self.getCPUUtilization(index);
	}
	TS_JSAPI uint32_t tsInfo_getCPUFanSpeed(const Info &self, uint32_t index) {
		return self.getCPUFanSpeed(index);
	}
	TS_JSAPI uint32_t tsInfo_getCPUPower(const Info &self, uint32_t index) {
		return self.getCPUPower(index);
	}
	TS_JSAPI uint32_t tsInfo_getGPUCount(const Info &self) {
		return self.getGPUCount();
	}
	TS_JSAPI String *tsInfo_getGPUName(const Info &self, uint32_t index) {
		return new String(self.getGPUName(index));
	}
	TS_JSAPI String *tsInfo_getGPUVendor(const Info &self, uint32_t index) {
		return new String(self.getGPUVendor(index));
	}
	TS_JSAPI String *tsInfo_getGPUSerial(const Info &self, uint32_t index) {
		return new String(self.getGPUSerial(index));
	}
	TS_JSAPI String *tsInfo_getGPUDevice(const Info &self, uint32_t index) {
		return new String(self.getGPUDevice(index));
	}
	TS_JSAPI String *tsInfo_getGPUVersion(const Info &self, uint32_t index) {
		return new String(self.getGPUVersion(index));
	}
	TS_JSAPI size_t tsInfo_getGPUMemory(const Info &self, uint32_t index) {
		return self.getGPUMemory(index);
	}
	TS_JSAPI uint32_t tsInfo_getGPUScreens(const Info &self, uint32_t index) {
		return self.getGPUScreens(index);
	}
	TS_JSAPI uint64_t tsInfo_getGPUFrequency(const Info &self, uint32_t index) {
		return self.getGPUFrequency(index);
	}
	TS_JSAPI uint32_t tsInfo_getGPUTemperature(const Info &self, uint32_t index) {
		return self.getGPUTemperature(index);
	}
	TS_JSAPI uint32_t tsInfo_getGPUUtilization(const Info &self, uint32_t index) {
		return self.getGPUUtilization(index);
	}
	TS_JSAPI uint32_t tsInfo_getGPUFanSpeed(const Info &self, uint32_t index) {
		return self.getGPUFanSpeed(index);
	}
	TS_JSAPI uint32_t tsInfo_getGPUPower(const Info &self, uint32_t index) {
		return self.getGPUPower(index);
	}
	TS_JSAPI bool tsInfo_isGPUThrottling(const Info &self, uint32_t index) {
		return self.isGPUThrottling(index);
	}
	
	// Tellusim::Directory
	TS_JSAPI Directory *tsDirectory_new() {
		return new Directory();
	}
	TS_JSAPI void tsDirectory_delete(Directory *self) {
		delete self;
	}
	TS_JSAPI bool tsDirectory_equalPtr(const Directory &self, const Directory &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Directory *tsDirectory_clonePtr(const Directory &self) {
		return new Directory(self.clonePtr());
	}
	TS_JSAPI void tsDirectory_clearPtr(Directory &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsDirectory_destroyPtr(Directory &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsDirectory_acquirePtr(Directory &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsDirectory_unacquirePtr(Directory &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsDirectory_isValidPtr(const Directory &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsDirectory_isOwnerPtr(const Directory &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsDirectory_isConstPtr(const Directory &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsDirectory_getCountPtr(const Directory &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsDirectory_getInternalPtr(const Directory &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI bool tsDirectory_open(Directory &self, const char *name, bool children) {
		return self.open(name, children);
	}
	TS_JSAPI bool tsDirectory_open_1(Directory &self, const String &name, bool children) {
		return self.open(name, children);
	}
	TS_JSAPI void tsDirectory_close(Directory &self) {
		self.close();
	}
	TS_JSAPI bool tsDirectory_isOpened(const Directory &self) {
		return self.isOpened();
	}
	TS_JSAPI String *tsDirectory_getName(const Directory &self) {
		return new String(self.getName());
	}
	TS_JSAPI uint32_t tsDirectory_getNumFiles(const Directory &self) {
		return self.getNumFiles();
	}
	TS_JSAPI String *tsDirectory_getFileName(const Directory &self, uint32_t index) {
		return new String(self.getFileName(index));
	}
	TS_JSAPI uint32_t tsDirectory_getFileAttributes(const Directory &self, uint32_t index) {
		return self.getFileAttributes(index);
	}
	TS_JSAPI uint64_t tsDirectory_getFileMTime(const Directory &self, uint32_t index) {
		return self.getFileMTime(index);
	}
	TS_JSAPI uint64_t tsDirectory_getFileATime(const Directory &self, uint32_t index) {
		return self.getFileATime(index);
	}
	TS_JSAPI uint64_t tsDirectory_getFileCTime(const Directory &self, uint32_t index) {
		return self.getFileCTime(index);
	}
	TS_JSAPI size_t tsDirectory_getFileSize(const Directory &self, uint32_t index) {
		return self.getFileSize(index);
	}
	TS_JSAPI uint32_t tsDirectory_getNumDirectories(const Directory &self) {
		return self.getNumDirectories();
	}
	TS_JSAPI String *tsDirectory_getDirectoryName(const Directory &self, uint32_t index) {
		return new String(self.getDirectoryName(index));
	}
	TS_JSAPI uint32_t tsDirectory_getDirectoryAttributes(const Directory &self, uint32_t index) {
		return self.getDirectoryAttributes(index);
	}
	TS_JSAPI uint64_t tsDirectory_getDirectoryCTime(const Directory &self, uint32_t index) {
		return self.getDirectoryCTime(index);
	}
	TS_JSAPI uint32_t tsDirectory_getDirectorySize(const Directory &self, uint32_t index) {
		return self.getDirectorySize(index);
	}
	TS_JSAPI bool tsDirectory_isFile(const char *name) {
		return Directory::isFile(name);
	}
	TS_JSAPI bool tsDirectory_isFile_1(const String &name) {
		return Directory::isFile(name);
	}
	TS_JSAPI bool tsDirectory_setFileAttributes(const char *name, uint32_t attributes) {
		return Directory::setFileAttributes(name, (Directory::Attributes)attributes);
	}
	TS_JSAPI uint32_t tsDirectory_getFileAttributes_1(const char *name) {
		return Directory::getFileAttributes(name);
	}
	TS_JSAPI bool tsDirectory_setFileMTime(const char *name, uint64_t time) {
		return Directory::setFileMTime(name, time);
	}
	TS_JSAPI uint64_t tsDirectory_getFileMTime_1(const char *name) {
		return Directory::getFileMTime(name);
	}
	TS_JSAPI uint64_t tsDirectory_getFileATime_1(const char *name) {
		return Directory::getFileATime(name);
	}
	TS_JSAPI uint64_t tsDirectory_getFileCTime_1(const char *name) {
		return Directory::getFileCTime(name);
	}
	TS_JSAPI size_t tsDirectory_getFileSize_1(const char *name) {
		return Directory::getFileSize(name);
	}
	TS_JSAPI size_t tsDirectory_getFileSize_2(const String &name) {
		return Directory::getFileSize(name);
	}
	TS_JSAPI bool tsDirectory_removeFile(const char *name) {
		return Directory::removeFile(name);
	}
	TS_JSAPI bool tsDirectory_removeFile_1(const String &name) {
		return Directory::removeFile(name);
	}
	TS_JSAPI bool tsDirectory_copyFile(const char *name, const char *new_name, bool attributes) {
		return Directory::copyFile(name, new_name, attributes);
	}
	TS_JSAPI bool tsDirectory_copyFile_1(const String &name, const String &new_name, bool attributes) {
		return Directory::copyFile(name, new_name, attributes);
	}
	TS_JSAPI bool tsDirectory_isDirectory(const char *name) {
		return Directory::isDirectory(name);
	}
	TS_JSAPI bool tsDirectory_isDirectory_1(const String &name) {
		return Directory::isDirectory(name);
	}
	TS_JSAPI bool tsDirectory_changeDirectory(const char *name) {
		return Directory::changeDirectory(name);
	}
	TS_JSAPI bool tsDirectory_changeDirectory_1(const String &name) {
		return Directory::changeDirectory(name);
	}
	TS_JSAPI bool tsDirectory_createDirectory(const char *name, bool children) {
		return Directory::createDirectory(name, children);
	}
	TS_JSAPI bool tsDirectory_createDirectory_1(const String &name, bool children) {
		return Directory::createDirectory(name, children);
	}
	TS_JSAPI bool tsDirectory_removeDirectory(const char *name, bool children) {
		return Directory::removeDirectory(name, children);
	}
	TS_JSAPI bool tsDirectory_removeDirectory_1(const String &name, bool children) {
		return Directory::removeDirectory(name, children);
	}
	TS_JSAPI bool tsDirectory_copyDirectory(const char *name, const char *new_name, bool attributes) {
		return Directory::copyDirectory(name, new_name, attributes);
	}
	TS_JSAPI bool tsDirectory_copyDirectory_1(const String &name, const String &new_name, bool attributes) {
		return Directory::copyDirectory(name, new_name, attributes);
	}
	TS_JSAPI bool tsDirectory_rename(const char *name, const char *new_name) {
		return Directory::rename(name, new_name);
	}
	TS_JSAPI bool tsDirectory_rename_1(const String &name, const String &new_name) {
		return Directory::rename(name, new_name);
	}
	TS_JSAPI String *tsDirectory_getCurrentDirectory() {
		return new String(Directory::getCurrentDirectory());
	}
	TS_JSAPI String *tsDirectory_getBinaryDirectory() {
		return new String(Directory::getBinaryDirectory());
	}
	TS_JSAPI String *tsDirectory_getHomeDirectory() {
		return new String(Directory::getHomeDirectory());
	}
	TS_JSAPI String *tsDirectory_getTempDirectory() {
		return new String(Directory::getTempDirectory());
	}
	TS_JSAPI String *tsDirectory_getConfigDirectory() {
		return new String(Directory::getConfigDirectory());
	}
	TS_JSAPI String *tsDirectory_getDocumentsDirectory() {
		return new String(Directory::getDocumentsDirectory());
	}
	
	// Tellusim::Archive
	TS_JSAPI Archive *tsArchive_new() {
		return new Archive();
	}
	TS_JSAPI void tsArchive_delete(Archive *self) {
		delete self;
	}
	TS_JSAPI bool tsArchive_open(Archive &self, const char *name, const char *type) {
		return self.open(name, type);
	}
	TS_JSAPI bool tsArchive_open_1(Archive &self, const String &name, const char *type) {
		return self.open(name, type);
	}
	TS_JSAPI bool tsArchive_open_2(Archive &self, Stream &stream, const char *type) {
		return self.open(stream, type);
	}
	TS_JSAPI void tsArchive_close(Archive &self) {
		self.close();
	}
	TS_JSAPI bool tsArchive_isOpened(const Archive &self) {
		return self.isOpened();
	}
	TS_JSAPI String *tsArchive_getName(const Archive &self) {
		return new String(self.getName());
	}
	TS_JSAPI uint32_t tsArchive_getNumFiles(const Archive &self) {
		return self.getNumFiles();
	}
	TS_JSAPI String *tsArchive_getFileName(const Archive &self, uint32_t index) {
		return new String(self.getFileName(index));
	}
	TS_JSAPI uint64_t tsArchive_getFileMTime(const Archive &self, uint32_t index) {
		return self.getFileMTime(index);
	}
	TS_JSAPI size_t tsArchive_getFileSize(const Archive &self, uint32_t index) {
		return self.getFileSize(index);
	}
	TS_JSAPI uint32_t tsArchive_findFile(const Archive &self, const char *name) {
		return self.findFile(name);
	}
	TS_JSAPI uint32_t tsArchive_findFile_1(const Archive &self, const String &name) {
		return self.findFile(name);
	}
	TS_JSAPI bool tsArchive_isFile(const Archive &self, const char *name) {
		return self.isFile(name);
	}
	TS_JSAPI bool tsArchive_isFile_1(const Archive &self, const String &name) {
		return self.isFile(name);
	}
	TS_JSAPI Stream *tsArchive_openFile(const Archive &self, const char *name) {
		return new Stream(self.openFile(name));
	}
	TS_JSAPI Stream *tsArchive_openFile_1(const Archive &self, const String &name) {
		return new Stream(self.openFile(name));
	}
	TS_JSAPI Stream *tsArchive_openFile_2(const Archive &self, uint32_t index) {
		return new Stream(self.openFile(index));
	}
	
	// Tellusim::Image
	TS_JSAPI Image *tsImage_new() {
		return new Image();
	}
	TS_JSAPI Image *tsImage_new_1(const char *name, uint32_t flags, uint32_t offset) {
		return new Image(name, (Image::Flags)flags, offset);
	}
	TS_JSAPI Image *tsImage_new_2(Stream &stream, uint32_t flags, uint32_t offset) {
		return new Image(stream, (Image::Flags)flags, offset);
	}
	TS_JSAPI Image *tsImage_new_3(uint32_t type, uint32_t format, const Size &size, uint32_t flags) {
		return new Image((Image::Type)type, (Format)format, size, (Image::Flags)flags);
	}
	TS_JSAPI Image *tsImage_new_4(uint32_t type, uint32_t format, const Size &size, uint32_t layers, uint32_t flags) {
		return new Image((Image::Type)type, (Format)format, size, layers, (Image::Flags)flags);
	}
	TS_JSAPI void tsImage_delete(Image *self) {
		delete self;
	}
	TS_JSAPI bool tsImage_equalPtr(const Image &self, const Image &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Image *tsImage_clonePtr(const Image &self) {
		return new Image(self.clonePtr());
	}
	TS_JSAPI void tsImage_clearPtr(Image &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsImage_destroyPtr(Image &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsImage_acquirePtr(Image &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsImage_unacquirePtr(Image &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsImage_isValidPtr(const Image &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsImage_isOwnerPtr(const Image &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsImage_isConstPtr(const Image &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsImage_getCountPtr(const Image &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsImage_getInternalPtr(const Image &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsImage_clear(Image &self) {
		self.clear();
	}
	TS_JSAPI bool tsImage_isLoaded(const Image &self) {
		return self.isLoaded();
	}
	TS_JSAPI bool tsImage_isAllocated(const Image &self) {
		return self.isAllocated();
	}
	TS_JSAPI uint32_t tsImage_getType(const Image &self) {
		return self.getType();
	}
	TS_JSAPI const char* tsImage_getTypeName(uint32_t type) {
		return Image::getTypeName((Image::Type)type);
	}
	TS_JSAPI const char* tsImage_getTypeName_1(const Image &self) {
		return self.getTypeName();
	}
	TS_JSAPI bool tsImage_is2DType(const Image &self) {
		return self.is2DType();
	}
	TS_JSAPI bool tsImage_is3DType(const Image &self) {
		return self.is3DType();
	}
	TS_JSAPI bool tsImage_isCubeType(const Image &self) {
		return self.isCubeType();
	}
	TS_JSAPI uint32_t tsImage_getFormat(const Image &self) {
		return self.getFormat();
	}
	TS_JSAPI const char* tsImage_getFormatName(const Image &self) {
		return self.getFormatName();
	}
	TS_JSAPI bool tsImage_isColorFormat(const Image &self) {
		return self.isColorFormat();
	}
	TS_JSAPI bool tsImage_isDepthFormat(const Image &self) {
		return self.isDepthFormat();
	}
	TS_JSAPI bool tsImage_isPixelFormat(const Image &self) {
		return self.isPixelFormat();
	}
	TS_JSAPI bool tsImage_isPlainFormat(const Image &self) {
		return self.isPlainFormat();
	}
	TS_JSAPI bool tsImage_isMixedFormat(const Image &self) {
		return self.isMixedFormat();
	}
	TS_JSAPI bool tsImage_isBlockFormat(const Image &self) {
		return self.isBlockFormat();
	}
	TS_JSAPI bool tsImage_isStencilFormat(const Image &self) {
		return self.isStencilFormat();
	}
	TS_JSAPI bool tsImage_isNormFormat(const Image &self) {
		return self.isNormFormat();
	}
	TS_JSAPI bool tsImage_isSRGBFormat(const Image &self) {
		return self.isSRGBFormat();
	}
	TS_JSAPI bool tsImage_isFloatFormat(const Image &self) {
		return self.isFloatFormat();
	}
	TS_JSAPI bool tsImage_isSignedFormat(const Image &self) {
		return self.isSignedFormat();
	}
	TS_JSAPI bool tsImage_isUnsignedFormat(const Image &self) {
		return self.isUnsignedFormat();
	}
	TS_JSAPI bool tsImage_isIntegerFormat(const Image &self) {
		return self.isIntegerFormat();
	}
	TS_JSAPI bool tsImage_isi8Format(const Image &self) {
		return self.isi8Format();
	}
	TS_JSAPI bool tsImage_isu8Format(const Image &self) {
		return self.isu8Format();
	}
	TS_JSAPI bool tsImage_is8BitFormat(const Image &self) {
		return self.is8BitFormat();
	}
	TS_JSAPI bool tsImage_isi16Format(const Image &self) {
		return self.isi16Format();
	}
	TS_JSAPI bool tsImage_isu16Format(const Image &self) {
		return self.isu16Format();
	}
	TS_JSAPI bool tsImage_isf16Format(const Image &self) {
		return self.isf16Format();
	}
	TS_JSAPI bool tsImage_is16BitFormat(const Image &self) {
		return self.is16BitFormat();
	}
	TS_JSAPI bool tsImage_isi32Format(const Image &self) {
		return self.isi32Format();
	}
	TS_JSAPI bool tsImage_isu32Format(const Image &self) {
		return self.isu32Format();
	}
	TS_JSAPI bool tsImage_isf32Format(const Image &self) {
		return self.isf32Format();
	}
	TS_JSAPI bool tsImage_is32BitFormat(const Image &self) {
		return self.is32BitFormat();
	}
	TS_JSAPI bool tsImage_isi64Format(const Image &self) {
		return self.isi64Format();
	}
	TS_JSAPI bool tsImage_isu64Format(const Image &self) {
		return self.isu64Format();
	}
	TS_JSAPI bool tsImage_isf64Format(const Image &self) {
		return self.isf64Format();
	}
	TS_JSAPI bool tsImage_is64BitFormat(const Image &self) {
		return self.is64BitFormat();
	}
	TS_JSAPI bool tsImage_isBC15Format(const Image &self) {
		return self.isBC15Format();
	}
	TS_JSAPI bool tsImage_isBC67Format(const Image &self) {
		return self.isBC67Format();
	}
	TS_JSAPI bool tsImage_isETC2Format(const Image &self) {
		return self.isETC2Format();
	}
	TS_JSAPI bool tsImage_isASTCFormat(const Image &self) {
		return self.isASTCFormat();
	}
	TS_JSAPI uint32_t tsImage_getComponents(const Image &self) {
		return self.getComponents();
	}
	TS_JSAPI uint32_t tsImage_getPixelSize(const Image &self) {
		return self.getPixelSize();
	}
	TS_JSAPI uint32_t tsImage_getBlockSize(const Image &self) {
		return self.getBlockSize();
	}
	TS_JSAPI uint32_t tsImage_getBlockWidth(const Image &self) {
		return self.getBlockWidth();
	}
	TS_JSAPI uint32_t tsImage_getBlockHeight(const Image &self) {
		return self.getBlockHeight();
	}
	TS_JSAPI uint32_t tsImage_getWidth(const Image &self) {
		return self.getWidth();
	}
	TS_JSAPI uint32_t tsImage_getHeight(const Image &self) {
		return self.getHeight();
	}
	TS_JSAPI uint32_t tsImage_getDepth(const Image &self) {
		return self.getDepth();
	}
	TS_JSAPI uint32_t tsImage_getFaces(const Image &self) {
		return self.getFaces();
	}
	TS_JSAPI uint32_t tsImage_getLayers(const Image &self) {
		return self.getLayers();
	}
	TS_JSAPI uint32_t tsImage_getMipmaps(const Image &self) {
		return self.getMipmaps();
	}
	TS_JSAPI uint32_t tsImage_findMipmap(const Image &self, const Size &size) {
		return self.findMipmap(size);
	}
	TS_JSAPI uint32_t tsImage_getWidth_1(const Image &self, uint32_t mipmap) {
		return self.getWidth(mipmap);
	}
	TS_JSAPI uint32_t tsImage_getHeight_1(const Image &self, uint32_t mipmap) {
		return self.getHeight(mipmap);
	}
	TS_JSAPI uint32_t tsImage_getDepth_1(const Image &self, uint32_t mipmap) {
		return self.getDepth(mipmap);
	}
	TS_JSAPI bool tsImage_hasLayers(const Image &self) {
		return self.hasLayers();
	}
	TS_JSAPI bool tsImage_hasMipmaps(const Image &self) {
		return self.hasMipmaps();
	}
	TS_JSAPI Size *tsImage_getSize(const Image &self) {
		return new Size(self.getSize());
	}
	TS_JSAPI Region *tsImage_getRegion(const Image &self) {
		return new Region(self.getRegion());
	}
	TS_JSAPI Slice *tsImage_getSlice(const Image &self) {
		return new Slice(self.getSlice());
	}
	TS_JSAPI Size *tsImage_getSize_1(const Image &self, uint32_t mipmap) {
		return new Size(self.getSize(mipmap));
	}
	TS_JSAPI Region *tsImage_getRegion_1(const Image &self, uint32_t mipmap) {
		return new Region(self.getRegion(mipmap));
	}
	TS_JSAPI Slice *tsImage_getSlice_1(const Image &self, uint32_t mipmap) {
		return new Slice(self.getSlice(mipmap));
	}
	TS_JSAPI void tsImage_setMetaInfo(Image &self, const String &str) {
		self.setMetaInfo(str);
	}
	TS_JSAPI String *tsImage_getMetaInfo(const Image &self) {
		return new String(self.getMetaInfo());
	}
	TS_JSAPI String *tsImage_getDescription(const Image &self) {
		return new String(self.getDescription());
	}
	TS_JSAPI size_t tsImage_getOffset(const Image &self, const Slice &slice, uint32_t alignment) {
		return self.getOffset(slice, alignment);
	}
	TS_JSAPI size_t tsImage_getStride(const Image &self, uint32_t mipmap, uint32_t alignment) {
		return self.getStride(mipmap, alignment);
	}
	TS_JSAPI size_t tsImage_getMipmapSize(const Image &self, uint32_t mipmap, uint32_t alignment) {
		return self.getMipmapSize(mipmap, alignment);
	}
	TS_JSAPI size_t tsImage_getLayerSize(const Image &self, uint32_t alignment) {
		return self.getLayerSize(alignment);
	}
	TS_JSAPI size_t tsImage_getDataSize(const Image &self, uint32_t alignment) {
		return self.getDataSize(alignment);
	}
	TS_JSAPI bool tsImage_create(Image &self, uint32_t type, uint32_t format, const Size &size, uint32_t flags) {
		return self.create((Image::Type)type, (Format)format, size, (Image::Flags)flags);
	}
	TS_JSAPI bool tsImage_create_1(Image &self, uint32_t type, uint32_t format, const Size &size, uint32_t layers, uint32_t flags) {
		return self.create((Image::Type)type, (Format)format, size, layers, (Image::Flags)flags);
	}
	TS_JSAPI bool tsImage_create2D(Image &self, uint32_t format, uint32_t size, uint32_t flags) {
		return self.create2D((Format)format, size, (Image::Flags)flags);
	}
	TS_JSAPI bool tsImage_create3D(Image &self, uint32_t format, uint32_t size, uint32_t flags) {
		return self.create3D((Format)format, size, (Image::Flags)flags);
	}
	TS_JSAPI bool tsImage_createCube(Image &self, uint32_t format, uint32_t size, uint32_t flags) {
		return self.createCube((Format)format, size, (Image::Flags)flags);
	}
	TS_JSAPI bool tsImage_create2D_1(Image &self, uint32_t format, uint32_t width, uint32_t height, uint32_t flags) {
		return self.create2D((Format)format, width, height, (Image::Flags)flags);
	}
	TS_JSAPI bool tsImage_create3D_1(Image &self, uint32_t format, uint32_t width, uint32_t height, uint32_t depth, uint32_t flags) {
		return self.create3D((Format)format, width, height, depth, (Image::Flags)flags);
	}
	TS_JSAPI bool tsImage_create2D_2(Image &self, uint32_t format, uint32_t width, uint32_t height, uint32_t layers, uint32_t flags) {
		return self.create2D((Format)format, width, height, layers, (Image::Flags)flags);
	}
	TS_JSAPI bool tsImage_createCube_1(Image &self, uint32_t format, uint32_t size, uint32_t layers, uint32_t flags) {
		return self.createCube((Format)format, size, layers, (Image::Flags)flags);
	}
	TS_JSAPI bool tsImage_info(Image &self, const char *name, uint32_t flags, uint32_t offset, Async *async) {
		return self.info(name, (Image::Flags)flags, offset, async);
	}
	TS_JSAPI bool tsImage_info_1(Image &self, const String &name, uint32_t flags, uint32_t offset, Async *async) {
		return self.info(name, (Image::Flags)flags, offset, async);
	}
	TS_JSAPI bool tsImage_info_2(Image &self, Stream &stream, uint32_t flags, uint32_t offset, Async *async) {
		return self.info(stream, (Image::Flags)flags, offset, async);
	}
	TS_JSAPI bool tsImage_info_3(Image &self, const char *name, Async *async) {
		return self.info(name, async);
	}
	TS_JSAPI bool tsImage_info_4(Image &self, const String &name, Async *async) {
		return self.info(name, async);
	}
	TS_JSAPI bool tsImage_info_5(Image &self, Stream &stream, Async *async) {
		return self.info(stream, async);
	}
	TS_JSAPI bool tsImage_load(Image &self, const char *name, uint32_t flags, uint32_t offset, Async *async) {
		return self.load(name, (Image::Flags)flags, offset, async);
	}
	TS_JSAPI bool tsImage_load_1(Image &self, const String &name, uint32_t flags, uint32_t offset, Async *async) {
		return self.load(name, (Image::Flags)flags, offset, async);
	}
	TS_JSAPI bool tsImage_load_2(Image &self, Stream &stream, uint32_t flags, uint32_t offset, Async *async) {
		return self.load(stream, (Image::Flags)flags, offset, async);
	}
	TS_JSAPI bool tsImage_load_3(Image &self, const char *name, Async *async) {
		return self.load(name, async);
	}
	TS_JSAPI bool tsImage_load_4(Image &self, const String &name, Async *async) {
		return self.load(name, async);
	}
	TS_JSAPI bool tsImage_load_5(Image &self, Stream &stream, Async *async) {
		return self.load(stream, async);
	}
	TS_JSAPI bool tsImage_save(const Image &self, const char *name, uint32_t flags, uint32_t quality) {
		return self.save(name, (Image::Flags)flags, quality);
	}
	TS_JSAPI bool tsImage_save_1(const Image &self, const String &name, uint32_t flags, uint32_t quality) {
		return self.save(name, (Image::Flags)flags, quality);
	}
	TS_JSAPI bool tsImage_save_2(const Image &self, Stream &stream, uint32_t flags, uint32_t quality) {
		return self.save(stream, (Image::Flags)flags, quality);
	}
	TS_JSAPI bool tsImage_swap(Image &self, uint32_t component_0, uint32_t component_1) {
		return self.swap(component_0, component_1);
	}
	TS_JSAPI bool tsImage_copy(Image &self, const Image &src, uint32_t dest_component, uint32_t src_component) {
		return self.copy(src, dest_component, src_component);
	}
	TS_JSAPI bool tsImage_flipX(Image &self, const Region &region, const Slice &slice) {
		return self.flipX(region, slice);
	}
	TS_JSAPI bool tsImage_flipX_1(Image &self, const Region &region) {
		return self.flipX(region);
	}
	TS_JSAPI bool tsImage_flipX_2(Image &self) {
		return self.flipX();
	}
	TS_JSAPI bool tsImage_flipY(Image &self, const Region &region, const Slice &slice) {
		return self.flipY(region, slice);
	}
	TS_JSAPI bool tsImage_flipY_1(Image &self, const Region &region) {
		return self.flipY(region);
	}
	TS_JSAPI bool tsImage_flipY_2(Image &self) {
		return self.flipY();
	}
	TS_JSAPI bool tsImage_copy_1(Image &self, const Image &src, const Origin &dest_origin, const Region &src_region, const Slice &dest_slice, const Slice &src_slice) {
		return self.copy(src, dest_origin, src_region, dest_slice, src_slice);
	}
	TS_JSAPI bool tsImage_copy_2(Image &self, const Image &src, const Origin &dest_origin, const Region &src_region) {
		return self.copy(src, dest_origin, src_region);
	}
	TS_JSAPI bool tsImage_copy_3(Image &self, const Image &src, const Origin &dest_origin, const Slice &dest_slice) {
		return self.copy(src, dest_origin, dest_slice);
	}
	TS_JSAPI bool tsImage_copy_4(Image &self, const Image &src, const Slice &dest_slice, const Slice &src_slice) {
		return self.copy(src, dest_slice, src_slice);
	}
	TS_JSAPI bool tsImage_copy_5(Image &self, const Image &src, const Origin &dest_origin) {
		return self.copy(src, dest_origin);
	}
	TS_JSAPI bool tsImage_copy_6(Image &self, const Image &src, const Slice &dest_slice) {
		return self.copy(src, dest_slice);
	}
	TS_JSAPI Image *tsImage_toType(const Image &self, uint32_t type, uint32_t flags, Async *async) {
		return new Image(self.toType((Image::Type)type, (Image::Flags)flags, async));
	}
	TS_JSAPI Image *tsImage_toType_1(const Image &self, uint32_t type, Async *async) {
		return new Image(self.toType((Image::Type)type, async));
	}
	TS_JSAPI Image *tsImage_toFormat(const Image &self, uint32_t format, uint32_t flags, Async *async) {
		return new Image(self.toFormat((Format)format, (Image::Flags)flags, async));
	}
	TS_JSAPI Image *tsImage_toFormat_1(const Image &self, uint32_t format, Async *async) {
		return new Image(self.toFormat((Format)format, async));
	}
	TS_JSAPI Image *tsImage_getSlice_2(const Image &self, const Slice &slice) {
		return new Image(self.getSlice(slice));
	}
	TS_JSAPI Image *tsImage_getComponent(const Image &self, uint32_t component) {
		return new Image(self.getComponent(component));
	}
	TS_JSAPI Image *tsImage_getRegion_2(const Image &self, const Region &region, const Slice &slice) {
		return new Image(self.getRegion(region, slice));
	}
	TS_JSAPI Image *tsImage_getRegion_3(const Image &self, const Region &region) {
		return new Image(self.getRegion(region));
	}
	TS_JSAPI Image *tsImage_getRotated(const Image &self, int32_t angle, const Slice &slice) {
		return new Image(self.getRotated(angle, slice));
	}
	TS_JSAPI Image *tsImage_getRotated_1(const Image &self, int32_t angle) {
		return new Image(self.getRotated(angle));
	}
	TS_JSAPI Image *tsImage_getResized(const Image &self, const Size &size, uint32_t min, uint32_t mag, uint32_t flags, Async *async) {
		return new Image(self.getResized(size, (Image::Filter)min, (Image::Filter)mag, (Image::Flags)flags, async));
	}
	TS_JSAPI Image *tsImage_getResized_1(const Image &self, const Size &size, uint32_t min, uint32_t mag, Async *async) {
		return new Image(self.getResized(size, (Image::Filter)min, (Image::Filter)mag, async));
	}
	TS_JSAPI Image *tsImage_getResized_2(const Image &self, const Size &size, Async *async) {
		return new Image(self.getResized(size, async));
	}
	TS_JSAPI Image *tsImage_getMipmapped(const Image &self, uint32_t filter, uint32_t flags, Async *async) {
		return new Image(self.getMipmapped((Image::Filter)filter, (Image::Flags)flags, async));
	}
	TS_JSAPI Image *tsImage_getMipmapped_1(const Image &self, uint32_t filter, Async *async) {
		return new Image(self.getMipmapped((Image::Filter)filter, async));
	}
	TS_JSAPI Image *tsImage_getMipmapped_2(const Image &self, Async *async) {
		return new Image(self.getMipmapped(async));
	}
	TS_JSAPI int32_t tsImage_compare(const Image &self, const Image &image) {
		return self.compare(image);
	}
	TS_JSAPI const uint8_t* tsImage_getData(const Image &self, const Slice &slice) {
		return self.getData(slice);
	}
	TS_JSAPI uint8_t* tsImage_getData_1(Image &self, const Slice &slice) {
		return self.getData(slice);
	}
	TS_JSAPI const uint8_t* tsImage_getData_2(const Image &self, const Origin &origin, const Slice &slice) {
		return self.getData(origin, slice);
	}
	TS_JSAPI uint8_t* tsImage_getData_3(Image &self, const Origin &origin, const Slice &slice) {
		return self.getData(origin, slice);
	}
	TS_JSAPI bool tsImage_setData(Image &self, const void *src, const Slice &slice, uint32_t alignment, size_t stride) {
		return self.setData(src, slice, alignment, stride);
	}
	TS_JSAPI bool tsImage_getData_4(const Image &self, void *dest, const Slice &slice, uint32_t alignment, size_t stride) {
		return self.getData(dest, slice, alignment, stride);
	}
	TS_JSAPI size_t tsImage_getMemory(const Image &self) {
		return self.getMemory();
	}
	
	// Tellusim::ImageSampler
	TS_JSAPI ImageSampler *tsImageSampler_new() {
		return new ImageSampler();
	}
	TS_JSAPI ImageSampler *tsImageSampler_new_1(Image &image, const Slice &slice) {
		return new ImageSampler(image, slice);
	}
	TS_JSAPI ImageSampler *tsImageSampler_new_2(const Image &image, const Slice &slice) {
		return new ImageSampler(image, slice);
	}
	TS_JSAPI void tsImageSampler_delete(ImageSampler *self) {
		delete self;
	}
	TS_JSAPI void tsImageSampler_clear(ImageSampler &self) {
		self.clear();
	}
	TS_JSAPI bool tsImageSampler_isCreated(const ImageSampler &self) {
		return self.isCreated();
	}
	TS_JSAPI uint32_t tsImageSampler_getType(const ImageSampler &self) {
		return self.getType();
	}
	TS_JSAPI bool tsImageSampler_is2DType(const ImageSampler &self) {
		return self.is2DType();
	}
	TS_JSAPI bool tsImageSampler_is3DType(const ImageSampler &self) {
		return self.is3DType();
	}
	TS_JSAPI bool tsImageSampler_isCubeType(const ImageSampler &self) {
		return self.isCubeType();
	}
	TS_JSAPI uint32_t tsImageSampler_getFormat(const ImageSampler &self) {
		return self.getFormat();
	}
	TS_JSAPI const char* tsImageSampler_getFormatName(const ImageSampler &self) {
		return self.getFormatName();
	}
	TS_JSAPI uint32_t tsImageSampler_getWidth(const ImageSampler &self) {
		return self.getWidth();
	}
	TS_JSAPI uint32_t tsImageSampler_getHeight(const ImageSampler &self) {
		return self.getHeight();
	}
	TS_JSAPI uint32_t tsImageSampler_getDepth(const ImageSampler &self) {
		return self.getDepth();
	}
	TS_JSAPI uint32_t tsImageSampler_getFaces(const ImageSampler &self) {
		return self.getFaces();
	}
	TS_JSAPI size_t tsImageSampler_getTexels(const ImageSampler &self) {
		return self.getTexels();
	}
	TS_JSAPI Size *tsImageSampler_getSize(const ImageSampler &self) {
		return new Size(self.getSize());
	}
	TS_JSAPI Region *tsImageSampler_getRegion(const ImageSampler &self) {
		return new Region(self.getRegion());
	}
	TS_JSAPI size_t tsImageSampler_getStride(const ImageSampler &self) {
		return self.getStride();
	}
	TS_JSAPI size_t tsImageSampler_getLayerSize(const ImageSampler &self) {
		return self.getLayerSize();
	}
	TS_JSAPI uint32_t tsImageSampler_getPixelSize(const ImageSampler &self) {
		return self.getPixelSize();
	}
	TS_JSAPI uint32_t tsImageSampler_getComponents(const ImageSampler &self) {
		return self.getComponents();
	}
	TS_JSAPI const uint8_t* tsImageSampler_getData(const ImageSampler &self) {
		return self.getData();
	}
	TS_JSAPI uint8_t* tsImageSampler_getData_1(ImageSampler &self) {
		return self.getData();
	}
	TS_JSAPI bool tsImageSampler_create(ImageSampler &self, Image &image, const Slice &slice) {
		return self.create(image, slice);
	}
	TS_JSAPI bool tsImageSampler_create_1(ImageSampler &self, const Image &image, const Slice &slice) {
		return self.create(image, slice);
	}
	TS_JSAPI bool tsImageSampler_create_2(ImageSampler &self, uint32_t type, uint32_t format, const Size &size, size_t stride, void *data) {
		return self.create((Image::Type)type, (Format)format, size, stride, data);
	}
	TS_JSAPI bool tsImageSampler_create_3(ImageSampler &self, uint32_t type, uint32_t format, const Size &size, size_t stride, const void *data) {
		return self.create((Image::Type)type, (Format)format, size, stride, data);
	}
	TS_JSAPI bool tsImageSampler_create_4(ImageSampler &self, uint32_t type, uint32_t format, const Size &size, size_t stride, size_t layer_size, void *data) {
		return self.create((Image::Type)type, (Format)format, size, stride, layer_size, data);
	}
	TS_JSAPI bool tsImageSampler_create_5(ImageSampler &self, uint32_t type, uint32_t format, const Size &size, size_t stride, size_t layer_size, const void *data) {
		return self.create((Image::Type)type, (Format)format, size, stride, layer_size, data);
	}
	TS_JSAPI bool tsImageSampler_clear_1(ImageSampler &self, const Color &color) {
		return self.clear(color);
	}
	TS_JSAPI bool tsImageSampler_clear_2(ImageSampler &self, const ImageColor &color) {
		return self.clear(color);
	}
	TS_JSAPI bool tsImageSampler_mad(ImageSampler &self, const Color &m, const Color &a) {
		return self.mad(m, a);
	}
	TS_JSAPI void tsImageSampler_set2D(ImageSampler &self, uint32_t x, uint32_t y, const ImageColor &color) {
		self.set2D(x, y, color);
	}
	TS_JSAPI ImageColor *tsImageSampler_get2D(const ImageSampler &self, uint32_t x, uint32_t y, bool repeat) {
		return new ImageColor(self.get2D(x, y, repeat));
	}
	TS_JSAPI ImageColor *tsImageSampler_get2D_1(const ImageSampler &self, float64_t x, float64_t y, bool repeat, uint32_t filter) {
		return new ImageColor(self.get2D(x, y, repeat, (Image::Filter)filter));
	}
	TS_JSAPI void tsImageSampler_set3D(ImageSampler &self, uint32_t x, uint32_t y, uint32_t z, const ImageColor &color) {
		self.set3D(x, y, z, color);
	}
	TS_JSAPI ImageColor *tsImageSampler_get3D(const ImageSampler &self, uint32_t x, uint32_t y, uint32_t z, bool repeat) {
		return new ImageColor(self.get3D(x, y, z, repeat));
	}
	TS_JSAPI ImageColor *tsImageSampler_get3D_1(const ImageSampler &self, float32_t x, float32_t y, float32_t z, bool repeat, uint32_t filter) {
		return new ImageColor(self.get3D(x, y, z, repeat, (Image::Filter)filter));
	}
	TS_JSAPI void tsImageSampler_setCube(ImageSampler &self, float32_t x, float32_t y, float32_t z, const ImageColor &color) {
		self.setCube(x, y, z, color);
	}
	TS_JSAPI ImageColor *tsImageSampler_getCube(const ImageSampler &self, float32_t x, float32_t y, float32_t z, uint32_t filter) {
		return new ImageColor(self.getCube(x, y, z, (Image::Filter)filter));
	}
	TS_JSAPI uint32_t tsImageSampler_getCubeFace(const ImageSampler &self, float32_t x, float32_t y, float32_t z, float32_t &tx, float32_t &ty) {
		return self.getCubeFace(x, y, z, tx, ty);
	}
	TS_JSAPI void tsImageSampler_setTexel(ImageSampler &self, size_t t, const ImageColor &color) {
		self.setTexel(t, color);
	}
	TS_JSAPI ImageColor *tsImageSampler_getTexel(const ImageSampler &self, size_t t) {
		return new ImageColor(self.getTexel(t));
	}
	
	// Tellusim::MeshNode
	TS_JSAPI MeshNode *tsMeshNode_new(const char *name) {
		return new MeshNode(name);
	}
	TS_JSAPI MeshNode *tsMeshNode_new_1(Mesh &mesh, const char *name) {
		return new MeshNode(mesh, name);
	}
	TS_JSAPI MeshNode *tsMeshNode_new_2(MeshNode *parent, const char *name) {
		return new MeshNode(parent, name);
	}
	TS_JSAPI MeshNode *tsMeshNode_new_3(Mesh &mesh, MeshNode *parent, const char *name) {
		return new MeshNode(mesh, parent, name);
	}
	TS_JSAPI void tsMeshNode_delete(MeshNode *self) {
		delete self;
	}
	TS_JSAPI bool tsMeshNode_equalPtr(const MeshNode &self, const MeshNode &ptr) {
		return (self == ptr);
	}
	TS_JSAPI MeshNode *tsMeshNode_clonePtr(const MeshNode &self) {
		return new MeshNode(self.clonePtr());
	}
	TS_JSAPI void tsMeshNode_clearPtr(MeshNode &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsMeshNode_destroyPtr(MeshNode &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsMeshNode_acquirePtr(MeshNode &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsMeshNode_unacquirePtr(MeshNode &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsMeshNode_isValidPtr(const MeshNode &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsMeshNode_isOwnerPtr(const MeshNode &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsMeshNode_isConstPtr(const MeshNode &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsMeshNode_getCountPtr(const MeshNode &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsMeshNode_getInternalPtr(const MeshNode &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsMeshNode_clear(MeshNode &self) {
		self.clear();
	}
	TS_JSAPI MeshNode *tsMeshNode_clone(const MeshNode &self, Mesh &mesh) {
		return new MeshNode(self.clone(mesh));
	}
	TS_JSAPI void tsMeshNode_setName(MeshNode &self, const char *name) {
		self.setName(name);
	}
	TS_JSAPI String *tsMeshNode_getName(const MeshNode &self) {
		return new String(self.getName());
	}
	TS_JSAPI uint32_t tsMeshNode_getIndex(const MeshNode &self) {
		return self.getIndex();
	}
	TS_JSAPI void tsMeshNode_setMesh(MeshNode &self, Mesh &mesh, bool check) {
		self.setMesh(mesh, check);
	}
	TS_JSAPI const Mesh *tsMeshNode_getMesh(const MeshNode &self) {
		return new Mesh(self.getMesh());
	}
	TS_JSAPI Mesh *tsMeshNode_getMesh_1(MeshNode &self) {
		return new Mesh(self.getMesh());
	}
	TS_JSAPI uint32_t tsMeshNode_setParent(MeshNode &self, MeshNode &parent, bool check) {
		return self.setParent(parent, check);
	}
	TS_JSAPI const MeshNode *tsMeshNode_getParent(const MeshNode &self) {
		return new MeshNode(self.getParent());
	}
	TS_JSAPI MeshNode *tsMeshNode_getParent_1(MeshNode &self) {
		return new MeshNode(self.getParent());
	}
	TS_JSAPI bool tsMeshNode_isRoot(const MeshNode &self) {
		return self.isRoot();
	}
	TS_JSAPI void tsMeshNode_reserveChildren(MeshNode &self, uint32_t num_children) {
		self.reserveChildren(num_children);
	}
	TS_JSAPI uint32_t tsMeshNode_addChild(MeshNode &self, MeshNode &child, bool check) {
		return self.addChild(child, check);
	}
	TS_JSAPI bool tsMeshNode_removeChild(MeshNode &self, MeshNode &child) {
		return self.removeChild(child);
	}
	TS_JSAPI void tsMeshNode_releaseChildren(MeshNode &self) {
		self.releaseChildren();
	}
	TS_JSAPI uint32_t tsMeshNode_findChild(const MeshNode &self, const MeshNode &child) {
		return self.findChild(child);
	}
	TS_JSAPI uint32_t tsMeshNode_findChild_1(const MeshNode &self, const char *name) {
		return self.findChild(name);
	}
	TS_JSAPI uint32_t tsMeshNode_getNumChildren(const MeshNode &self) {
		return self.getNumChildren();
	}
	TS_JSAPI const MeshNode *tsMeshNode_getChild(const MeshNode &self, uint32_t index) {
		return new MeshNode(self.getChild(index));
	}
	TS_JSAPI const MeshNode *tsMeshNode_getChild_1(const MeshNode &self, const char *name) {
		return new MeshNode(self.getChild(name));
	}
	TS_JSAPI MeshNode *tsMeshNode_getChild_2(MeshNode &self, uint32_t index) {
		return new MeshNode(self.getChild(index));
	}
	TS_JSAPI MeshNode *tsMeshNode_getChild_3(MeshNode &self, const char *name) {
		return new MeshNode(self.getChild(name));
	}
	TS_JSAPI void tsMeshNode_clearGeometries(MeshNode &self) {
		self.clearGeometries();
	}
	TS_JSAPI void tsMeshNode_reserveGeometries(MeshNode &self, uint32_t num_geometries) {
		self.reserveGeometries(num_geometries);
	}
	TS_JSAPI uint32_t tsMeshNode_addGeometry(MeshNode &self, MeshGeometry &geometry, bool check) {
		return self.addGeometry(geometry, check);
	}
	TS_JSAPI bool tsMeshNode_removeGeometry(MeshNode &self, MeshGeometry &geometry) {
		return self.removeGeometry(geometry);
	}
	TS_JSAPI bool tsMeshNode_replaceGeometry(MeshNode &self, MeshGeometry &old_geometry, MeshGeometry &geometry) {
		return self.replaceGeometry(old_geometry, geometry);
	}
	TS_JSAPI uint32_t tsMeshNode_findGeometry(const MeshNode &self, const MeshGeometry &geometry) {
		return self.findGeometry(geometry);
	}
	TS_JSAPI uint32_t tsMeshNode_getNumGeometries(const MeshNode &self) {
		return self.getNumGeometries();
	}
	TS_JSAPI const MeshGeometry *tsMeshNode_getGeometry(const MeshNode &self, uint32_t index) {
		return new MeshGeometry(self.getGeometry(index));
	}
	TS_JSAPI MeshGeometry *tsMeshNode_getGeometry_1(MeshNode &self, uint32_t index) {
		return new MeshGeometry(self.getGeometry(index));
	}
	TS_JSAPI void tsMeshNode_clearAttachments(MeshNode &self) {
		self.clearAttachments();
	}
	TS_JSAPI void tsMeshNode_reserveAttachments(MeshNode &self, uint32_t num_attachments) {
		self.reserveAttachments(num_attachments);
	}
	TS_JSAPI uint32_t tsMeshNode_addAttachment(MeshNode &self, MeshAttachment &attachment, bool check) {
		return self.addAttachment(attachment, check);
	}
	TS_JSAPI bool tsMeshNode_removeAttachment(MeshNode &self, MeshAttachment &attachment) {
		return self.removeAttachment(attachment);
	}
	TS_JSAPI bool tsMeshNode_replaceAttachment(MeshNode &self, MeshAttachment &old_attachment, MeshAttachment &attachment) {
		return self.replaceAttachment(old_attachment, attachment);
	}
	TS_JSAPI uint32_t tsMeshNode_findAttachment(const MeshNode &self, const MeshAttachment &attachment) {
		return self.findAttachment(attachment);
	}
	TS_JSAPI uint32_t tsMeshNode_findAttachment_1(const MeshNode &self, const char *name) {
		return self.findAttachment(name);
	}
	TS_JSAPI uint32_t tsMeshNode_getNumAttachments(const MeshNode &self) {
		return self.getNumAttachments();
	}
	TS_JSAPI const MeshAttachment *tsMeshNode_getAttachment(const MeshNode &self, uint32_t index) {
		return new MeshAttachment(self.getAttachment(index));
	}
	TS_JSAPI MeshAttachment *tsMeshNode_getAttachment_1(MeshNode &self, uint32_t index) {
		return new MeshAttachment(self.getAttachment(index));
	}
	TS_JSAPI void tsMeshNode_setLocalTransform(MeshNode &self, const Matrix4x3d &transform) {
		self.setLocalTransform(transform);
	}
	TS_JSAPI const Matrix4x3d *tsMeshNode_getLocalTransform(const MeshNode &self) {
		return new Matrix4x3d(self.getLocalTransform());
	}
	TS_JSAPI void tsMeshNode_setGlobalTransform(MeshNode &self, const Matrix4x3d &transform) {
		self.setGlobalTransform(transform);
	}
	TS_JSAPI const Matrix4x3d *tsMeshNode_getGlobalTransform(const MeshNode &self) {
		return new Matrix4x3d(self.getGlobalTransform());
	}
	TS_JSAPI void tsMeshNode_setPivotTransform(MeshNode &self, const Matrix4x3d &transform) {
		self.setPivotTransform(transform);
	}
	TS_JSAPI const Matrix4x3d *tsMeshNode_getPivotTransform(const MeshNode &self) {
		return new Matrix4x3d(self.getPivotTransform());
	}
	TS_JSAPI void tsMeshNode_setMorphTransform(MeshNode &self, const Vector4f &transform) {
		self.setMorphTransform(transform);
	}
	TS_JSAPI const Vector4f *tsMeshNode_getMorphTransform(const MeshNode &self) {
		return new Vector4f(self.getMorphTransform());
	}
	TS_JSAPI void tsMeshNode_createLocalTransforms(MeshNode &self, const Matrix4x3d &itransform) {
		self.createLocalTransforms(itransform);
	}
	TS_JSAPI void tsMeshNode_createGlobalTransforms(MeshNode &self, const Matrix4x3d &transform) {
		self.createGlobalTransforms(transform);
	}
	TS_JSAPI void tsMeshNode_setTransform(MeshNode &self, const Vector3d &scale) {
		self.setTransform(scale);
	}
	TS_JSAPI size_t tsMeshNode_getMemory(const MeshNode &self) {
		return self.getMemory();
	}
	
	// Tellusim::MeshIndices
	TS_JSAPI MeshIndices *tsMeshIndices_new(const char *name) {
		return new MeshIndices(name);
	}
	TS_JSAPI MeshIndices *tsMeshIndices_new_1(uint32_t type, uint32_t format, const char *name) {
		return new MeshIndices((MeshIndices::Type)type, (Format)format, name);
	}
	TS_JSAPI MeshIndices *tsMeshIndices_new_2(uint32_t type, uint32_t format, uint32_t size, const char *name) {
		return new MeshIndices((MeshIndices::Type)type, (Format)format, size, name);
	}
	TS_JSAPI void tsMeshIndices_delete(MeshIndices *self) {
		delete self;
	}
	TS_JSAPI bool tsMeshIndices_equalPtr(const MeshIndices &self, const MeshIndices &ptr) {
		return (self == ptr);
	}
	TS_JSAPI MeshIndices *tsMeshIndices_clonePtr(const MeshIndices &self) {
		return new MeshIndices(self.clonePtr());
	}
	TS_JSAPI void tsMeshIndices_clearPtr(MeshIndices &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsMeshIndices_destroyPtr(MeshIndices &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsMeshIndices_acquirePtr(MeshIndices &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsMeshIndices_unacquirePtr(MeshIndices &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsMeshIndices_isValidPtr(const MeshIndices &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsMeshIndices_isOwnerPtr(const MeshIndices &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsMeshIndices_isConstPtr(const MeshIndices &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsMeshIndices_getCountPtr(const MeshIndices &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsMeshIndices_getInternalPtr(const MeshIndices &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsMeshIndices_clear(MeshIndices &self) {
		self.clear();
	}
	TS_JSAPI void tsMeshIndices_setName(MeshIndices &self, const char *name) {
		self.setName(name);
	}
	TS_JSAPI String *tsMeshIndices_getName(const MeshIndices &self) {
		return new String(self.getName());
	}
	TS_JSAPI void tsMeshIndices_create(MeshIndices &self, uint32_t type, uint32_t format, uint32_t size) {
		self.create((MeshIndices::Type)type, (Format)format, size);
	}
	TS_JSAPI uint32_t tsMeshIndices_getType(const MeshIndices &self) {
		return self.getType();
	}
	TS_JSAPI const char* tsMeshIndices_getTypeName(uint32_t type) {
		return MeshIndices::getTypeName((MeshIndices::Type)type);
	}
	TS_JSAPI const char* tsMeshIndices_getTypeName_1(const MeshIndices &self) {
		return self.getTypeName();
	}
	TS_JSAPI bool tsMeshIndices_isUnknown(const MeshIndices &self) {
		return self.isUnknown();
	}
	TS_JSAPI bool tsMeshIndices_isPoint(const MeshIndices &self) {
		return self.isPoint();
	}
	TS_JSAPI bool tsMeshIndices_isLine(const MeshIndices &self) {
		return self.isLine();
	}
	TS_JSAPI bool tsMeshIndices_isTriangle(const MeshIndices &self) {
		return self.isTriangle();
	}
	TS_JSAPI bool tsMeshIndices_isQuadrilateral(const MeshIndices &self) {
		return self.isQuadrilateral();
	}
	TS_JSAPI bool tsMeshIndices_isTetrahedron(const MeshIndices &self) {
		return self.isTetrahedron();
	}
	TS_JSAPI bool tsMeshIndices_isPrimitive(const MeshIndices &self) {
		return self.isPrimitive();
	}
	TS_JSAPI bool tsMeshIndices_isSolid(const MeshIndices &self) {
		return self.isSolid();
	}
	TS_JSAPI bool tsMeshIndices_isVolume(const MeshIndices &self) {
		return self.isVolume();
	}
	TS_JSAPI bool tsMeshIndices_isMaterial(const MeshIndices &self) {
		return self.isMaterial();
	}
	TS_JSAPI bool tsMeshIndices_isGroup(const MeshIndices &self) {
		return self.isGroup();
	}
	TS_JSAPI bool tsMeshIndices_isJoint(const MeshIndices &self) {
		return self.isJoint();
	}
	TS_JSAPI bool tsMeshIndices_isEdge(const MeshIndices &self) {
		return self.isEdge();
	}
	TS_JSAPI uint32_t tsMeshIndices_getPrimitiveSize(const MeshIndices &self) {
		return self.getPrimitiveSize();
	}
	TS_JSAPI uint32_t tsMeshIndices_getFormat(const MeshIndices &self) {
		return self.getFormat();
	}
	TS_JSAPI const char* tsMeshIndices_getFormatName(const MeshIndices &self) {
		return self.getFormatName();
	}
	TS_JSAPI void tsMeshIndices_setGeometry(MeshIndices &self, MeshGeometry &geometry, bool check) {
		self.setGeometry(geometry, check);
	}
	TS_JSAPI const MeshGeometry *tsMeshIndices_getGeometry(const MeshIndices &self) {
		return new MeshGeometry(self.getGeometry());
	}
	TS_JSAPI MeshGeometry *tsMeshIndices_getGeometry_1(MeshIndices &self) {
		return new MeshGeometry(self.getGeometry());
	}
	TS_JSAPI void tsMeshIndices_setSize(MeshIndices &self, uint32_t size, bool discard, bool clear) {
		self.setSize(size, discard, clear);
	}
	TS_JSAPI uint32_t tsMeshIndices_getSize(const MeshIndices &self) {
		return self.getSize();
	}
	TS_JSAPI uint32_t tsMeshIndices_getStride(const MeshIndices &self) {
		return self.getStride();
	}
	TS_JSAPI size_t tsMeshIndices_getBytes(const MeshIndices &self) {
		return self.getBytes();
	}
	TS_JSAPI void tsMeshIndices_setData(MeshIndices &self, uint32_t value, uint32_t size, uint32_t offset) {
		self.setData(value, size, offset);
	}
	TS_JSAPI void tsMeshIndices_setData_1(MeshIndices &self, const void *src, uint32_t format, uint32_t size, uint32_t repeat) {
		self.setData(src, (Format)format, size, repeat);
	}
	TS_JSAPI void tsMeshIndices_getData(const MeshIndices &self, void *dest, uint32_t format, uint32_t size, uint32_t repeat) {
		self.getData(dest, (Format)format, size, repeat);
	}
	TS_JSAPI const void* tsMeshIndices_getData_1(const MeshIndices &self) {
		return self.getData();
	}
	TS_JSAPI void* tsMeshIndices_getData_2(MeshIndices &self) {
		return self.getData();
	}
	TS_JSAPI void tsMeshIndices_set(MeshIndices &self, uint32_t index, uint32_t value) {
		self.set(index, value);
	}
	TS_JSAPI void tsMeshIndices_set_1(MeshIndices &self, uint32_t index, uint32_t value_0, uint32_t value_1) {
		self.set(index, value_0, value_1);
	}
	TS_JSAPI void tsMeshIndices_set_2(MeshIndices &self, uint32_t index, uint32_t value_0, uint32_t value_1, uint32_t value_2) {
		self.set(index, value_0, value_1, value_2);
	}
	TS_JSAPI void tsMeshIndices_set_3(MeshIndices &self, uint32_t index, uint32_t value_0, uint32_t value_1, uint32_t value_2, uint32_t value_3) {
		self.set(index, value_0, value_1, value_2, value_3);
	}
	TS_JSAPI uint32_t tsMeshIndices_get(const MeshIndices &self, uint32_t index) {
		return self.get(index);
	}
	TS_JSAPI void tsMeshIndices_get_1(const MeshIndices &self, uint32_t index, uint32_t &value_0, uint32_t &value_1) {
		self.get(index, value_0, value_1);
	}
	TS_JSAPI void tsMeshIndices_get_2(const MeshIndices &self, uint32_t index, uint32_t &value_0, uint32_t &value_1, uint32_t &value_2) {
		self.get(index, value_0, value_1, value_2);
	}
	TS_JSAPI void tsMeshIndices_get_3(const MeshIndices &self, uint32_t index, uint32_t &value_0, uint32_t &value_1, uint32_t &value_2, uint32_t &value_3) {
		self.get(index, value_0, value_1, value_2, value_3);
	}
	TS_JSAPI const void* tsMeshIndices_getPtr(const MeshIndices &self, uint32_t index) {
		return self.getPtr(index);
	}
	TS_JSAPI void* tsMeshIndices_getPtr_1(MeshIndices &self, uint32_t index) {
		return self.getPtr(index);
	}
	TS_JSAPI bool tsMeshIndices_isDirect(const MeshIndices &self) {
		return self.isDirect();
	}
	TS_JSAPI bool tsMeshIndices_isUniform(const MeshIndices &self) {
		return self.isUniform();
	}
	TS_JSAPI uint32_t tsMeshIndices_getMinIndex(const MeshIndices &self) {
		return self.getMinIndex();
	}
	TS_JSAPI uint32_t tsMeshIndices_getMaxIndex(const MeshIndices &self) {
		return self.getMaxIndex();
	}
	TS_JSAPI int32_t tsMeshIndices_compare(const MeshIndices &self, const MeshIndices &indices) {
		return self.compare(indices);
	}
	TS_JSAPI void tsMeshIndices_addIndices(MeshIndices &self, const MeshIndices &indices, uint32_t offset, bool expand) {
		self.addIndices(indices, offset, expand);
	}
	TS_JSAPI MeshIndices *tsMeshIndices_toFormat(const MeshIndices &self, uint32_t format) {
		return new MeshIndices(self.toFormat((Format)format));
	}
	TS_JSAPI MeshIndices *tsMeshIndices_toType(const MeshIndices &self, uint32_t type) {
		return new MeshIndices(self.toType((MeshIndices::Type)type));
	}
	TS_JSAPI MeshIndices *tsMeshIndices_toType_1(const MeshIndices &self, uint32_t type, const MeshAttribute &position_attribute) {
		return new MeshIndices(self.toType((MeshIndices::Type)type, position_attribute));
	}
	TS_JSAPI size_t tsMeshIndices_getMemory(const MeshIndices &self) {
		return self.getMemory();
	}
	
	// Tellusim::MeshAttribute
	TS_JSAPI MeshAttribute *tsMeshAttribute_new(const char *name, uint32_t index) {
		return new MeshAttribute(name, index);
	}
	TS_JSAPI MeshAttribute *tsMeshAttribute_new_1(uint32_t type, uint32_t format, const char *name, uint32_t index) {
		return new MeshAttribute((MeshAttribute::Type)type, (Format)format, name, index);
	}
	TS_JSAPI MeshAttribute *tsMeshAttribute_new_2(uint32_t type, uint32_t format, uint32_t size, const char *name, uint32_t index) {
		return new MeshAttribute((MeshAttribute::Type)type, (Format)format, size, name, index);
	}
	TS_JSAPI MeshAttribute *tsMeshAttribute_new_3(uint32_t type, uint32_t format, uint32_t size, uint32_t index) {
		return new MeshAttribute((MeshAttribute::Type)type, (Format)format, size, index);
	}
	TS_JSAPI void tsMeshAttribute_delete(MeshAttribute *self) {
		delete self;
	}
	TS_JSAPI bool tsMeshAttribute_equalPtr(const MeshAttribute &self, const MeshAttribute &ptr) {
		return (self == ptr);
	}
	TS_JSAPI MeshAttribute *tsMeshAttribute_clonePtr(const MeshAttribute &self) {
		return new MeshAttribute(self.clonePtr());
	}
	TS_JSAPI void tsMeshAttribute_clearPtr(MeshAttribute &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsMeshAttribute_destroyPtr(MeshAttribute &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsMeshAttribute_acquirePtr(MeshAttribute &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsMeshAttribute_unacquirePtr(MeshAttribute &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsMeshAttribute_isValidPtr(const MeshAttribute &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsMeshAttribute_isOwnerPtr(const MeshAttribute &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsMeshAttribute_isConstPtr(const MeshAttribute &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsMeshAttribute_getCountPtr(const MeshAttribute &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsMeshAttribute_getInternalPtr(const MeshAttribute &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsMeshAttribute_clear(MeshAttribute &self) {
		self.clear();
	}
	TS_JSAPI void tsMeshAttribute_setName(MeshAttribute &self, const char *name) {
		self.setName(name);
	}
	TS_JSAPI String *tsMeshAttribute_getName(const MeshAttribute &self) {
		return new String(self.getName());
	}
	TS_JSAPI void tsMeshAttribute_create(MeshAttribute &self, uint32_t type, uint32_t format, uint32_t size) {
		self.create((MeshAttribute::Type)type, (Format)format, size);
	}
	TS_JSAPI uint32_t tsMeshAttribute_getType(const MeshAttribute &self) {
		return self.getType();
	}
	TS_JSAPI const char* tsMeshAttribute_getTypeName(uint32_t type) {
		return MeshAttribute::getTypeName((MeshAttribute::Type)type);
	}
	TS_JSAPI const char* tsMeshAttribute_getTypeName_1(const MeshAttribute &self) {
		return self.getTypeName();
	}
	TS_JSAPI bool tsMeshAttribute_isUnknown(const MeshAttribute &self) {
		return self.isUnknown();
	}
	TS_JSAPI bool tsMeshAttribute_isPosition(const MeshAttribute &self) {
		return self.isPosition();
	}
	TS_JSAPI bool tsMeshAttribute_isBasis(const MeshAttribute &self) {
		return self.isBasis();
	}
	TS_JSAPI bool tsMeshAttribute_isNormal(const MeshAttribute &self) {
		return self.isNormal();
	}
	TS_JSAPI bool tsMeshAttribute_isTangent(const MeshAttribute &self) {
		return self.isTangent();
	}
	TS_JSAPI bool tsMeshAttribute_isBinormal(const MeshAttribute &self) {
		return self.isBinormal();
	}
	TS_JSAPI bool tsMeshAttribute_isSpatial(const MeshAttribute &self) {
		return self.isSpatial();
	}
	TS_JSAPI bool tsMeshAttribute_isNormalized(const MeshAttribute &self) {
		return self.isNormalized();
	}
	TS_JSAPI bool tsMeshAttribute_isTexCoord(const MeshAttribute &self) {
		return self.isTexCoord();
	}
	TS_JSAPI bool tsMeshAttribute_isWeights(const MeshAttribute &self) {
		return self.isWeights();
	}
	TS_JSAPI bool tsMeshAttribute_isJoints(const MeshAttribute &self) {
		return self.isJoints();
	}
	TS_JSAPI bool tsMeshAttribute_isColor(const MeshAttribute &self) {
		return self.isColor();
	}
	TS_JSAPI bool tsMeshAttribute_isVertex(const MeshAttribute &self) {
		return self.isVertex();
	}
	TS_JSAPI bool tsMeshAttribute_isCrease(const MeshAttribute &self) {
		return self.isCrease();
	}
	TS_JSAPI uint32_t tsMeshAttribute_getFormat(const MeshAttribute &self) {
		return self.getFormat();
	}
	TS_JSAPI const char* tsMeshAttribute_getFormatName(const MeshAttribute &self) {
		return self.getFormatName();
	}
	TS_JSAPI uint32_t tsMeshAttribute_getComponents(const MeshAttribute &self) {
		return self.getComponents();
	}
	TS_JSAPI bool tsMeshAttribute_isPacked(const MeshAttribute &self) {
		return self.isPacked();
	}
	TS_JSAPI void tsMeshAttribute_setIndex(MeshAttribute &self, uint32_t index) {
		self.setIndex(index);
	}
	TS_JSAPI uint32_t tsMeshAttribute_getIndex(const MeshAttribute &self) {
		return self.getIndex();
	}
	TS_JSAPI void tsMeshAttribute_setIndices(MeshAttribute &self, MeshIndices &indices) {
		self.setIndices(indices);
	}
	TS_JSAPI const MeshIndices *tsMeshAttribute_getIndices(const MeshAttribute &self) {
		return new MeshIndices(self.getIndices());
	}
	TS_JSAPI MeshIndices *tsMeshAttribute_getIndices_1(MeshAttribute &self) {
		return new MeshIndices(self.getIndices());
	}
	TS_JSAPI void tsMeshAttribute_setGeometry(MeshAttribute &self, MeshGeometry &geometry, bool check) {
		self.setGeometry(geometry, check);
	}
	TS_JSAPI const MeshGeometry *tsMeshAttribute_getGeometry(const MeshAttribute &self) {
		return new MeshGeometry(self.getGeometry());
	}
	TS_JSAPI MeshGeometry *tsMeshAttribute_getGeometry_1(MeshAttribute &self) {
		return new MeshGeometry(self.getGeometry());
	}
	TS_JSAPI void tsMeshAttribute_setSize(MeshAttribute &self, uint32_t size, bool discard, bool clear) {
		self.setSize(size, discard, clear);
	}
	TS_JSAPI uint32_t tsMeshAttribute_getSize(const MeshAttribute &self) {
		return self.getSize();
	}
	TS_JSAPI uint32_t tsMeshAttribute_getStride(const MeshAttribute &self) {
		return self.getStride();
	}
	TS_JSAPI size_t tsMeshAttribute_getBytes(const MeshAttribute &self) {
		return self.getBytes();
	}
	TS_JSAPI void tsMeshAttribute_setData(MeshAttribute &self, const void *src, uint32_t size, uint32_t stride) {
		self.setData(src, size, stride);
	}
	TS_JSAPI void tsMeshAttribute_setData_1(MeshAttribute &self, const void *src, Array<uint32_t> &indices, uint32_t stride) {
		self.setData(src, indices, stride);
	}
	TS_JSAPI void tsMeshAttribute_getData(const MeshAttribute &self, void *dest, uint32_t size, uint32_t stride) {
		self.getData(dest, size, stride);
	}
	TS_JSAPI void tsMeshAttribute_getData_1(const MeshAttribute &self, void *dest, const MeshIndices &indices, uint32_t stride) {
		self.getData(dest, indices, stride);
	}
	TS_JSAPI void tsMeshAttribute_getData_2(const MeshAttribute &self, void *dest, Array<uint32_t> &indices, uint32_t stride) {
		self.getData(dest, indices, stride);
	}
	TS_JSAPI const void* tsMeshAttribute_getData_3(const MeshAttribute &self) {
		return self.getData();
	}
	TS_JSAPI void* tsMeshAttribute_getData_4(MeshAttribute &self) {
		return self.getData();
	}
	TS_JSAPI void tsMeshAttribute_setValue(MeshAttribute &self, uint32_t index, const void *src, size_t size) {
		self.setValue(index, src, size);
	}
	TS_JSAPI void tsMeshAttribute_getValue(const MeshAttribute &self, uint32_t index, void *dest, size_t size) {
		self.getValue(index, dest, size);
	}
	TS_JSAPI const void* tsMeshAttribute_getPtr(const MeshAttribute &self, uint32_t index) {
		return self.getPtr(index);
	}
	TS_JSAPI void* tsMeshAttribute_getPtr_1(MeshAttribute &self, uint32_t index) {
		return self.getPtr(index);
	}
	TS_JSAPI int32_t tsMeshAttribute_compare(const MeshAttribute &self, const MeshAttribute &attribute, const Matrix4x3f &transform, float32_t threshold, bool spatial) {
		return self.compare(attribute, transform, threshold, spatial);
	}
	TS_JSAPI void tsMeshAttribute_addAttribute(MeshAttribute &self, const MeshAttribute &attribute) {
		self.addAttribute(attribute);
	}
	TS_JSAPI bool tsMeshAttribute_setTransform(MeshAttribute &self, const Vector3f &scale) {
		return self.setTransform(scale);
	}
	TS_JSAPI bool tsMeshAttribute_setTransform_1(MeshAttribute &self, const Matrix4x3f &transform) {
		return self.setTransform(transform);
	}
	TS_JSAPI bool tsMeshAttribute_morphAttribute(MeshAttribute &self, const MeshAttribute &attribute, float32_t k) {
		return self.morphAttribute(attribute, k);
	}
	TS_JSAPI bool tsMeshAttribute_packAttributes(MeshAttribute &self, const MeshAttribute &attribute_0, const MeshAttribute &attribute_1, uint32_t format) {
		return self.packAttributes(attribute_0, attribute_1, (Format)format);
	}
	TS_JSAPI bool tsMeshAttribute_unpackAttributes(const MeshAttribute &self, MeshAttribute &attribute_0, MeshAttribute &attribute_1) {
		return self.unpackAttributes(attribute_0, attribute_1);
	}
	TS_JSAPI MeshAttribute *tsMeshAttribute_optimizeAttribute(const MeshAttribute &self, MeshIndices &indices) {
		return new MeshAttribute(self.optimizeAttribute(indices));
	}
	TS_JSAPI MeshAttribute *tsMeshAttribute_toDirect(const MeshAttribute &self, const MeshIndices &indices) {
		return new MeshAttribute(self.toDirect(indices));
	}
	TS_JSAPI MeshAttribute *tsMeshAttribute_toFormat(const MeshAttribute &self, uint32_t format) {
		return new MeshAttribute(self.toFormat((Format)format));
	}
	TS_JSAPI MeshAttribute *tsMeshAttribute_toType(const MeshAttribute &self, uint32_t type) {
		return new MeshAttribute(self.toType((MeshAttribute::Type)type));
	}
	TS_JSAPI Matrix4x3f *tsMeshAttribute_getCovarianceMatrix(const MeshAttribute &self) {
		return new Matrix4x3f(self.getCovarianceMatrix());
	}
	TS_JSAPI Matrix4x3f *tsMeshAttribute_getMinTransform(const MeshAttribute &self) {
		return new Matrix4x3f(self.getMinTransform());
	}
	TS_JSAPI BoundBoxf *tsMeshAttribute_getBoundBox(const MeshAttribute &self) {
		return new BoundBoxf(self.getBoundBox());
	}
	TS_JSAPI BoundSpheref *tsMeshAttribute_getBoundSphere(const MeshAttribute &self) {
		return new BoundSpheref(self.getBoundSphere());
	}
	TS_JSAPI size_t tsMeshAttribute_getMemory(const MeshAttribute &self) {
		return self.getMemory();
	}
	
	// Tellusim::MeshJoint
	TS_JSAPI MeshJoint *tsMeshJoint_new(const char *name) {
		return new MeshJoint(name);
	}
	TS_JSAPI MeshJoint *tsMeshJoint_new_1(MeshGeometry &geometry, const char *name) {
		return new MeshJoint(geometry, name);
	}
	TS_JSAPI void tsMeshJoint_delete(MeshJoint *self) {
		delete self;
	}
	TS_JSAPI bool tsMeshJoint_equalPtr(const MeshJoint &self, const MeshJoint &ptr) {
		return (self == ptr);
	}
	TS_JSAPI MeshJoint *tsMeshJoint_clonePtr(const MeshJoint &self) {
		return new MeshJoint(self.clonePtr());
	}
	TS_JSAPI void tsMeshJoint_clearPtr(MeshJoint &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsMeshJoint_destroyPtr(MeshJoint &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsMeshJoint_acquirePtr(MeshJoint &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsMeshJoint_unacquirePtr(MeshJoint &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsMeshJoint_isValidPtr(const MeshJoint &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsMeshJoint_isOwnerPtr(const MeshJoint &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsMeshJoint_isConstPtr(const MeshJoint &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsMeshJoint_getCountPtr(const MeshJoint &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsMeshJoint_getInternalPtr(const MeshJoint &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsMeshJoint_clear(MeshJoint &self) {
		self.clear();
	}
	TS_JSAPI void tsMeshJoint_setName(MeshJoint &self, const char *name) {
		self.setName(name);
	}
	TS_JSAPI String *tsMeshJoint_getName(const MeshJoint &self) {
		return new String(self.getName());
	}
	TS_JSAPI void tsMeshJoint_setNode(MeshJoint &self, MeshNode &node) {
		self.setNode(node);
	}
	TS_JSAPI const MeshNode *tsMeshJoint_getNode(const MeshJoint &self) {
		return new MeshNode(self.getNode());
	}
	TS_JSAPI MeshNode *tsMeshJoint_getNode_1(MeshJoint &self) {
		return new MeshNode(self.getNode());
	}
	TS_JSAPI uint32_t tsMeshJoint_getNodeIndex(const MeshJoint &self) {
		return self.getNodeIndex();
	}
	TS_JSAPI const Matrix4x3d *tsMeshJoint_getLocalTransform(const MeshJoint &self) {
		return new Matrix4x3d(self.getLocalTransform());
	}
	TS_JSAPI const Matrix4x3d *tsMeshJoint_getGlobalTransform(const MeshJoint &self) {
		return new Matrix4x3d(self.getGlobalTransform());
	}
	TS_JSAPI void tsMeshJoint_setIndices(MeshJoint &self, MeshIndices &indices) {
		self.setIndices(indices);
	}
	TS_JSAPI const MeshIndices *tsMeshJoint_getIndices(const MeshJoint &self) {
		return new MeshIndices(self.getIndices());
	}
	TS_JSAPI MeshIndices *tsMeshJoint_getIndices_1(MeshJoint &self) {
		return new MeshIndices(self.getIndices());
	}
	TS_JSAPI void tsMeshJoint_setGeometry(MeshJoint &self, MeshGeometry &geometry, bool check) {
		self.setGeometry(geometry, check);
	}
	TS_JSAPI const MeshGeometry *tsMeshJoint_getGeometry(const MeshJoint &self) {
		return new MeshGeometry(self.getGeometry());
	}
	TS_JSAPI MeshGeometry *tsMeshJoint_getGeometry_1(MeshJoint &self) {
		return new MeshGeometry(self.getGeometry());
	}
	TS_JSAPI void tsMeshJoint_setBoundBox(MeshJoint &self, const BoundBoxf &box) {
		self.setBoundBox(box);
	}
	TS_JSAPI const BoundBoxf *tsMeshJoint_getBoundBox(const MeshJoint &self) {
		return new BoundBoxf(self.getBoundBox());
	}
	TS_JSAPI void tsMeshJoint_setBoundSphere(MeshJoint &self, const BoundSpheref &sphere) {
		self.setBoundSphere(sphere);
	}
	TS_JSAPI const BoundSpheref *tsMeshJoint_getBoundSphere(MeshJoint &self) {
		return new BoundSpheref(self.getBoundSphere());
	}
	TS_JSAPI void tsMeshJoint_setITransform(MeshJoint &self, const Matrix4x3f &itransform) {
		self.setITransform(itransform);
	}
	TS_JSAPI const Matrix4x3f *tsMeshJoint_getITransform(const MeshJoint &self) {
		return new Matrix4x3f(self.getITransform());
	}
	TS_JSAPI int32_t tsMeshJoint_compare(const MeshJoint &self, const MeshJoint &joint) {
		return self.compare(joint);
	}
	TS_JSAPI size_t tsMeshJoint_getMemory(const MeshJoint &self) {
		return self.getMemory();
	}
	
	// Tellusim::MeshMaterial
	TS_JSAPI MeshMaterial *tsMeshMaterial_new(const char *name) {
		return new MeshMaterial(name);
	}
	TS_JSAPI MeshMaterial *tsMeshMaterial_new_1(MeshGeometry &geometry, const char *name) {
		return new MeshMaterial(geometry, name);
	}
	TS_JSAPI void tsMeshMaterial_delete(MeshMaterial *self) {
		delete self;
	}
	TS_JSAPI bool tsMeshMaterial_equalPtr(const MeshMaterial &self, const MeshMaterial &ptr) {
		return (self == ptr);
	}
	TS_JSAPI MeshMaterial *tsMeshMaterial_clonePtr(const MeshMaterial &self) {
		return new MeshMaterial(self.clonePtr());
	}
	TS_JSAPI void tsMeshMaterial_clearPtr(MeshMaterial &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsMeshMaterial_destroyPtr(MeshMaterial &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsMeshMaterial_acquirePtr(MeshMaterial &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsMeshMaterial_unacquirePtr(MeshMaterial &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsMeshMaterial_isValidPtr(const MeshMaterial &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsMeshMaterial_isOwnerPtr(const MeshMaterial &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsMeshMaterial_isConstPtr(const MeshMaterial &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsMeshMaterial_getCountPtr(const MeshMaterial &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsMeshMaterial_getInternalPtr(const MeshMaterial &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsMeshMaterial_clear(MeshMaterial &self) {
		self.clear();
	}
	TS_JSAPI void tsMeshMaterial_setName(MeshMaterial &self, const char *name) {
		self.setName(name);
	}
	TS_JSAPI String *tsMeshMaterial_getName(const MeshMaterial &self) {
		return new String(self.getName());
	}
	TS_JSAPI uint32_t tsMeshMaterial_getIndex(const MeshMaterial &self) {
		return self.getIndex();
	}
	TS_JSAPI void tsMeshMaterial_setIndices(MeshMaterial &self, MeshIndices &indices) {
		self.setIndices(indices);
	}
	TS_JSAPI const MeshIndices *tsMeshMaterial_getIndices(const MeshMaterial &self) {
		return new MeshIndices(self.getIndices());
	}
	TS_JSAPI MeshIndices *tsMeshMaterial_getIndices_1(MeshMaterial &self) {
		return new MeshIndices(self.getIndices());
	}
	TS_JSAPI void tsMeshMaterial_setGeometry(MeshMaterial &self, MeshGeometry &geometry, bool check) {
		self.setGeometry(geometry, check);
	}
	TS_JSAPI const MeshGeometry *tsMeshMaterial_getGeometry(const MeshMaterial &self) {
		return new MeshGeometry(self.getGeometry());
	}
	TS_JSAPI MeshGeometry *tsMeshMaterial_getGeometry_1(MeshMaterial &self) {
		return new MeshGeometry(self.getGeometry());
	}
	TS_JSAPI void tsMeshMaterial_setData(MeshMaterial &self, const char *data) {
		self.setData(data);
	}
	TS_JSAPI void tsMeshMaterial_setData_1(MeshMaterial &self, const String &data) {
		self.setData(data);
	}
	TS_JSAPI String *tsMeshMaterial_getData(const MeshMaterial &self) {
		return new String(self.getData());
	}
	TS_JSAPI void tsMeshMaterial_clearParameters(MeshMaterial &self) {
		self.clearParameters();
	}
	TS_JSAPI bool tsMeshMaterial_removeParameter(MeshMaterial &self, const char *type) {
		return self.removeParameter(type);
	}
	TS_JSAPI void tsMeshMaterial_copyParameters(MeshMaterial &self, const MeshMaterial &material) {
		self.copyParameters(material);
	}
	TS_JSAPI uint32_t tsMeshMaterial_findParameter(const MeshMaterial &self, const char *type) {
		return self.findParameter(type);
	}
	TS_JSAPI bool tsMeshMaterial_hasParameter(const MeshMaterial &self, const char *type) {
		return self.hasParameter(type);
	}
	TS_JSAPI uint32_t tsMeshMaterial_getNumParameters(const MeshMaterial &self) {
		return self.getNumParameters();
	}
	TS_JSAPI String *tsMeshMaterial_getParameterType(const MeshMaterial &self, uint32_t index) {
		return new String(self.getParameterType(index));
	}
	TS_JSAPI void tsMeshMaterial_addParameter(MeshMaterial &self, const char *type, bool value) {
		self.addParameter(type, value);
	}
	TS_JSAPI void tsMeshMaterial_addParameter_1(MeshMaterial &self, const char *type, float32_t value) {
		self.addParameter(type, value);
	}
	TS_JSAPI void tsMeshMaterial_addParameter_2(MeshMaterial &self, const char *type, const Vector4f &value) {
		self.addParameter(type, value);
	}
	TS_JSAPI void tsMeshMaterial_addParameter_3(MeshMaterial &self, const char *type, const Matrix3x2f &value) {
		self.addParameter(type, value);
	}
	TS_JSAPI void tsMeshMaterial_addParameter_4(MeshMaterial &self, const char *type, const Color &color) {
		self.addParameter(type, color);
	}
	TS_JSAPI void tsMeshMaterial_addParameter_5(MeshMaterial &self, const char *type, const char *name, const char *layout) {
		self.addParameter(type, name, layout);
	}
	TS_JSAPI void tsMeshMaterial_addParameter_6(MeshMaterial &self, const char *type, const String &name, const char *layout) {
		self.addParameter(type, name, layout);
	}
	TS_JSAPI void tsMeshMaterial_addParameter_7(MeshMaterial &self, const char *type, const Image &image, const char *layout) {
		self.addParameter(type, image, layout);
	}
	TS_JSAPI void tsMeshMaterial_addParameter_8(MeshMaterial &self, const char *type, Blob &blob, const char *layout) {
		self.addParameter(type, blob, layout);
	}
	TS_JSAPI uint32_t tsMeshMaterial_getParameterFlags(const MeshMaterial &self, uint32_t index) {
		return self.getParameterFlags(index);
	}
	TS_JSAPI bool tsMeshMaterial_hasParameterFlag(const MeshMaterial &self, uint32_t index, uint32_t flags) {
		return self.hasParameterFlag(index, (MeshMaterial::Flags)flags);
	}
	TS_JSAPI bool tsMeshMaterial_hasParameterFlags(const MeshMaterial &self, uint32_t index, uint32_t flags) {
		return self.hasParameterFlags(index, (MeshMaterial::Flags)flags);
	}
	TS_JSAPI bool tsMeshMaterial_getParameterBool(const MeshMaterial &self, uint32_t index, bool value) {
		return self.getParameterBool(index, value);
	}
	TS_JSAPI float32_t tsMeshMaterial_getParameterScalarf32(const MeshMaterial &self, uint32_t index, float32_t value) {
		return self.getParameterScalarf32(index, value);
	}
	TS_JSAPI const Vector4f *tsMeshMaterial_getParameterVector4f(const MeshMaterial &self, uint32_t index, const Vector4f &vector) {
		return new Vector4f(self.getParameterVector4f(index, vector));
	}
	TS_JSAPI const Matrix3x2f *tsMeshMaterial_getParameterMatrix3x2f(const MeshMaterial &self, uint32_t index, const Matrix3x2f &matrix) {
		return new Matrix3x2f(self.getParameterMatrix3x2f(index, matrix));
	}
	TS_JSAPI const Color *tsMeshMaterial_getParameterColor(const MeshMaterial &self, uint32_t index, const Color &color) {
		return new Color(self.getParameterColor(index, color));
	}
	TS_JSAPI String *tsMeshMaterial_getParameterName(const MeshMaterial &self, uint32_t index, const String &name) {
		return new String(self.getParameterName(index, name));
	}
	TS_JSAPI String *tsMeshMaterial_getParameterLayout(const MeshMaterial &self, uint32_t index, const String &layout) {
		return new String(self.getParameterLayout(index, layout));
	}
	TS_JSAPI const Image *tsMeshMaterial_getParameterImage(const MeshMaterial &self, uint32_t index) {
		return new Image(self.getParameterImage(index));
	}
	TS_JSAPI Blob *tsMeshMaterial_getParameterBlob(const MeshMaterial &self, uint32_t index) {
		return new Blob(self.getParameterBlob(index));
	}
	TS_JSAPI Image *tsMeshMaterial_getParameterImage_1(MeshMaterial &self, uint32_t index) {
		return new Image(self.getParameterImage(index));
	}
	TS_JSAPI Blob *tsMeshMaterial_getParameterBlob_1(MeshMaterial &self, uint32_t index) {
		return new Blob(self.getParameterBlob(index));
	}
	TS_JSAPI uint32_t tsMeshMaterial_getParameterFlags_1(const MeshMaterial &self, const char *type) {
		return self.getParameterFlags(type);
	}
	TS_JSAPI bool tsMeshMaterial_hasParameterFlag_1(const MeshMaterial &self, const char *type, uint32_t flags) {
		return self.hasParameterFlag(type, (MeshMaterial::Flags)flags);
	}
	TS_JSAPI bool tsMeshMaterial_hasParameterFlags_1(const MeshMaterial &self, const char *type, uint32_t flags) {
		return self.hasParameterFlags(type, (MeshMaterial::Flags)flags);
	}
	TS_JSAPI bool tsMeshMaterial_getParameterBool_1(const MeshMaterial &self, const char *type, bool value) {
		return self.getParameterBool(type, value);
	}
	TS_JSAPI float32_t tsMeshMaterial_getParameterScalarf32_1(const MeshMaterial &self, const char *type, float32_t value) {
		return self.getParameterScalarf32(type, value);
	}
	TS_JSAPI const Vector4f *tsMeshMaterial_getParameterVector4f_1(const MeshMaterial &self, const char *type, const Vector4f &vector) {
		return new Vector4f(self.getParameterVector4f(type, vector));
	}
	TS_JSAPI const Matrix3x2f *tsMeshMaterial_getParameterMatrix3x2f_1(const MeshMaterial &self, const char *type, const Matrix3x2f &matrix) {
		return new Matrix3x2f(self.getParameterMatrix3x2f(type, matrix));
	}
	TS_JSAPI const Color *tsMeshMaterial_getParameterColor_1(const MeshMaterial &self, const char *type, const Color &color) {
		return new Color(self.getParameterColor(type, color));
	}
	TS_JSAPI String *tsMeshMaterial_getParameterName_1(const MeshMaterial &self, const char *type, const String &name) {
		return new String(self.getParameterName(type, name));
	}
	TS_JSAPI String *tsMeshMaterial_getParameterLayout_1(const MeshMaterial &self, const char *type, const String &layout) {
		return new String(self.getParameterLayout(type, layout));
	}
	TS_JSAPI int32_t tsMeshMaterial_compare(const MeshMaterial &self, const MeshMaterial &material) {
		return self.compare(material);
	}
	TS_JSAPI size_t tsMeshMaterial_getMemory(const MeshMaterial &self) {
		return self.getMemory();
	}
	
	// Tellusim::MeshGeometry
	TS_JSAPI MeshGeometry *tsMeshGeometry_new(const char *name) {
		return new MeshGeometry(name);
	}
	TS_JSAPI MeshGeometry *tsMeshGeometry_new_1(Mesh &mesh, const char *name) {
		return new MeshGeometry(mesh, name);
	}
	TS_JSAPI void tsMeshGeometry_delete(MeshGeometry *self) {
		delete self;
	}
	TS_JSAPI bool tsMeshGeometry_equalPtr(const MeshGeometry &self, const MeshGeometry &ptr) {
		return (self == ptr);
	}
	TS_JSAPI MeshGeometry *tsMeshGeometry_clonePtr(const MeshGeometry &self) {
		return new MeshGeometry(self.clonePtr());
	}
	TS_JSAPI void tsMeshGeometry_clearPtr(MeshGeometry &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsMeshGeometry_destroyPtr(MeshGeometry &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsMeshGeometry_acquirePtr(MeshGeometry &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsMeshGeometry_unacquirePtr(MeshGeometry &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsMeshGeometry_isValidPtr(const MeshGeometry &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsMeshGeometry_isOwnerPtr(const MeshGeometry &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsMeshGeometry_isConstPtr(const MeshGeometry &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsMeshGeometry_getCountPtr(const MeshGeometry &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsMeshGeometry_getInternalPtr(const MeshGeometry &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsMeshGeometry_clear(MeshGeometry &self) {
		self.clear();
	}
	TS_JSAPI void tsMeshGeometry_setName(MeshGeometry &self, const char *name) {
		self.setName(name);
	}
	TS_JSAPI String *tsMeshGeometry_getName(const MeshGeometry &self) {
		return new String(self.getName());
	}
	TS_JSAPI uint32_t tsMeshGeometry_getIndex(const MeshGeometry &self) {
		return self.getIndex();
	}
	TS_JSAPI void tsMeshGeometry_setMesh(MeshGeometry &self, Mesh &mesh, bool check) {
		self.setMesh(mesh, check);
	}
	TS_JSAPI const Mesh *tsMeshGeometry_getMesh(const MeshGeometry &self) {
		return new Mesh(self.getMesh());
	}
	TS_JSAPI Mesh *tsMeshGeometry_getMesh_1(MeshGeometry &self) {
		return new Mesh(self.getMesh());
	}
	TS_JSAPI uint32_t tsMeshGeometry_setParent0(MeshGeometry &self, MeshGeometry &parent, bool check) {
		return self.setParent0(parent, check);
	}
	TS_JSAPI uint32_t tsMeshGeometry_setParent1(MeshGeometry &self, MeshGeometry &parent, bool check) {
		return self.setParent1(parent, check);
	}
	TS_JSAPI const MeshGeometry *tsMeshGeometry_getParent0(const MeshGeometry &self) {
		return new MeshGeometry(self.getParent0());
	}
	TS_JSAPI const MeshGeometry *tsMeshGeometry_getParent1(const MeshGeometry &self) {
		return new MeshGeometry(self.getParent1());
	}
	TS_JSAPI MeshGeometry *tsMeshGeometry_getParent0_1(MeshGeometry &self) {
		return new MeshGeometry(self.getParent0());
	}
	TS_JSAPI MeshGeometry *tsMeshGeometry_getParent1_1(MeshGeometry &self) {
		return new MeshGeometry(self.getParent1());
	}
	TS_JSAPI bool tsMeshGeometry_isRoot(const MeshGeometry &self) {
		return self.isRoot();
	}
	TS_JSAPI void tsMeshGeometry_reserveChildren(MeshGeometry &self, uint32_t num_children) {
		self.reserveChildren(num_children);
	}
	TS_JSAPI uint32_t tsMeshGeometry_addChild0(MeshGeometry &self, MeshGeometry &child, bool check) {
		return self.addChild0(child, check);
	}
	TS_JSAPI uint32_t tsMeshGeometry_addChild1(MeshGeometry &self, MeshGeometry &child, bool check) {
		return self.addChild1(child, check);
	}
	TS_JSAPI bool tsMeshGeometry_removeChild(MeshGeometry &self, MeshGeometry &child) {
		return self.removeChild(child);
	}
	TS_JSAPI void tsMeshGeometry_releaseChildren(MeshGeometry &self) {
		self.releaseChildren();
	}
	TS_JSAPI uint32_t tsMeshGeometry_findChild(const MeshGeometry &self, const MeshGeometry &child) {
		return self.findChild(child);
	}
	TS_JSAPI uint32_t tsMeshGeometry_getNumChildren(const MeshGeometry &self) {
		return self.getNumChildren();
	}
	TS_JSAPI const MeshGeometry *tsMeshGeometry_getChild(const MeshGeometry &self, uint32_t index) {
		return new MeshGeometry(self.getChild(index));
	}
	TS_JSAPI MeshGeometry *tsMeshGeometry_getChild_1(MeshGeometry &self, uint32_t index) {
		return new MeshGeometry(self.getChild(index));
	}
	TS_JSAPI void tsMeshGeometry_clearIndices(MeshGeometry &self) {
		self.clearIndices();
	}
	TS_JSAPI void tsMeshGeometry_reserveIndices(MeshGeometry &self, uint32_t num_indices) {
		self.reserveIndices(num_indices);
	}
	TS_JSAPI uint32_t tsMeshGeometry_addIndices(MeshGeometry &self, MeshIndices &indices, bool check) {
		return self.addIndices(indices, check);
	}
	TS_JSAPI bool tsMeshGeometry_removeIndices(MeshGeometry &self, MeshIndices &indices) {
		return self.removeIndices(indices);
	}
	TS_JSAPI bool tsMeshGeometry_replaceIndices(MeshGeometry &self, MeshIndices &old_indices, MeshIndices &indices) {
		return self.replaceIndices(old_indices, indices);
	}
	TS_JSAPI uint32_t tsMeshGeometry_findIndices(const MeshGeometry &self, const MeshIndices &indices) {
		return self.findIndices(indices);
	}
	TS_JSAPI uint32_t tsMeshGeometry_findIndices_1(const MeshGeometry &self, uint32_t type) {
		return self.findIndices((MeshIndices::Type)type);
	}
	TS_JSAPI bool tsMeshGeometry_hasIndices(const MeshGeometry &self, uint32_t type) {
		return self.hasIndices((MeshIndices::Type)type);
	}
	TS_JSAPI bool tsMeshGeometry_hasSolidIndices(const MeshGeometry &self) {
		return self.hasSolidIndices();
	}
	TS_JSAPI uint32_t tsMeshGeometry_getNumIndices(const MeshGeometry &self, uint32_t type) {
		return self.getNumIndices((MeshIndices::Type)type);
	}
	TS_JSAPI const MeshIndices *tsMeshGeometry_getIndices(const MeshGeometry &self, uint32_t type) {
		return new MeshIndices(self.getIndices((MeshIndices::Type)type));
	}
	TS_JSAPI MeshIndices *tsMeshGeometry_getIndices_1(MeshGeometry &self, uint32_t type) {
		return new MeshIndices(self.getIndices((MeshIndices::Type)type));
	}
	TS_JSAPI uint32_t tsMeshGeometry_getNumIndices_1(const MeshGeometry &self) {
		return self.getNumIndices();
	}
	TS_JSAPI const MeshIndices *tsMeshGeometry_getIndices_2(const MeshGeometry &self, uint32_t index) {
		return new MeshIndices(self.getIndices(index));
	}
	TS_JSAPI MeshIndices *tsMeshGeometry_getIndices_3(MeshGeometry &self, uint32_t index) {
		return new MeshIndices(self.getIndices(index));
	}
	TS_JSAPI void tsMeshGeometry_clearAttributes(MeshGeometry &self) {
		self.clearAttributes();
	}
	TS_JSAPI void tsMeshGeometry_reserveAttributes(MeshGeometry &self, uint32_t num_attributes) {
		self.reserveAttributes(num_attributes);
	}
	TS_JSAPI uint32_t tsMeshGeometry_addAttribute(MeshGeometry &self, MeshAttribute &attribute, bool check) {
		return self.addAttribute(attribute, check);
	}
	TS_JSAPI uint32_t tsMeshGeometry_addAttribute_1(MeshGeometry &self, MeshAttribute &attribute, MeshIndices &indices, bool check) {
		return self.addAttribute(attribute, indices, check);
	}
	TS_JSAPI bool tsMeshGeometry_removeAttribute(MeshGeometry &self, MeshAttribute &attribute) {
		return self.removeAttribute(attribute);
	}
	TS_JSAPI bool tsMeshGeometry_replaceAttribute(MeshGeometry &self, MeshAttribute &old_attribute, MeshAttribute &attribute) {
		return self.replaceAttribute(old_attribute, attribute);
	}
	TS_JSAPI bool tsMeshGeometry_replaceAttributeIndices(MeshGeometry &self, const MeshIndices &old_indices, MeshIndices &indices) {
		return self.replaceAttributeIndices(old_indices, indices);
	}
	TS_JSAPI uint32_t tsMeshGeometry_findAttribute(const MeshGeometry &self, uint32_t type, uint32_t format, uint32_t index) {
		return self.findAttribute((MeshAttribute::Type)type, (Format)format, index);
	}
	TS_JSAPI uint32_t tsMeshGeometry_findAttribute_1(const MeshGeometry &self, uint32_t type, uint32_t index) {
		return self.findAttribute((MeshAttribute::Type)type, index);
	}
	TS_JSAPI uint32_t tsMeshGeometry_findAttribute_2(const MeshGeometry &self, const char *name, uint32_t index) {
		return self.findAttribute(name, index);
	}
	TS_JSAPI uint32_t tsMeshGeometry_findAttribute_3(const MeshGeometry &self, const MeshAttribute &attribute) {
		return self.findAttribute(attribute);
	}
	TS_JSAPI bool tsMeshGeometry_hasAttribute(const MeshGeometry &self, uint32_t type, uint32_t format, uint32_t index) {
		return self.hasAttribute((MeshAttribute::Type)type, (Format)format, index);
	}
	TS_JSAPI bool tsMeshGeometry_hasAttribute_1(const MeshGeometry &self, uint32_t type, uint32_t index) {
		return self.hasAttribute((MeshAttribute::Type)type, index);
	}
	TS_JSAPI bool tsMeshGeometry_hasAttribute_2(const MeshGeometry &self, const char *name, uint32_t index) {
		return self.hasAttribute(name, index);
	}
	TS_JSAPI bool tsMeshGeometry_hasAttribute_3(const MeshGeometry &self, const MeshAttribute &attribute) {
		return self.hasAttribute(attribute);
	}
	TS_JSAPI uint32_t tsMeshGeometry_getNumAttributes(const MeshGeometry &self, uint32_t type) {
		return self.getNumAttributes((MeshAttribute::Type)type);
	}
	TS_JSAPI uint32_t tsMeshGeometry_getNumAttributes_1(const MeshGeometry &self, const MeshIndices &indices) {
		return self.getNumAttributes(indices);
	}
	TS_JSAPI const MeshAttribute *tsMeshGeometry_getAttribute(const MeshGeometry &self, uint32_t type, uint32_t index) {
		return new MeshAttribute(self.getAttribute((MeshAttribute::Type)type, index));
	}
	TS_JSAPI MeshAttribute *tsMeshGeometry_getAttribute_1(MeshGeometry &self, uint32_t type, uint32_t index) {
		return new MeshAttribute(self.getAttribute((MeshAttribute::Type)type, index));
	}
	TS_JSAPI uint32_t tsMeshGeometry_getNumAttributes_2(const MeshGeometry &self) {
		return self.getNumAttributes();
	}
	TS_JSAPI const MeshAttribute *tsMeshGeometry_getAttribute_2(const MeshGeometry &self, uint32_t index) {
		return new MeshAttribute(self.getAttribute(index));
	}
	TS_JSAPI MeshAttribute *tsMeshGeometry_getAttribute_3(MeshGeometry &self, uint32_t index) {
		return new MeshAttribute(self.getAttribute(index));
	}
	TS_JSAPI void tsMeshGeometry_clearJoints(MeshGeometry &self) {
		self.clearJoints();
	}
	TS_JSAPI void tsMeshGeometry_reserveJoints(MeshGeometry &self, uint32_t num_joints) {
		self.reserveJoints(num_joints);
	}
	TS_JSAPI uint32_t tsMeshGeometry_addJoint(MeshGeometry &self, MeshJoint &joint, bool check) {
		return self.addJoint(joint, check);
	}
	TS_JSAPI uint32_t tsMeshGeometry_addJoint_1(MeshGeometry &self, MeshJoint &joint, MeshNode &node, bool check) {
		return self.addJoint(joint, node, check);
	}
	TS_JSAPI bool tsMeshGeometry_removeJoint(MeshGeometry &self, MeshJoint &joint) {
		return self.removeJoint(joint);
	}
	TS_JSAPI bool tsMeshGeometry_replaceJoint(MeshGeometry &self, MeshJoint &old_joint, MeshJoint &joint) {
		return self.replaceJoint(old_joint, joint);
	}
	TS_JSAPI uint32_t tsMeshGeometry_findJoint(const MeshGeometry &self, const MeshJoint &joint) {
		return self.findJoint(joint);
	}
	TS_JSAPI uint32_t tsMeshGeometry_findJoint_1(const MeshGeometry &self, const MeshNode &node) {
		return self.findJoint(node);
	}
	TS_JSAPI uint32_t tsMeshGeometry_findJoint_2(const MeshGeometry &self, const char *name) {
		return self.findJoint(name);
	}
	TS_JSAPI uint32_t tsMeshGeometry_getNumJoints(const MeshGeometry &self) {
		return self.getNumJoints();
	}
	TS_JSAPI const MeshJoint *tsMeshGeometry_getJoint(const MeshGeometry &self, uint32_t index) {
		return new MeshJoint(self.getJoint(index));
	}
	TS_JSAPI MeshJoint *tsMeshGeometry_getJoint_1(MeshGeometry &self, uint32_t index) {
		return new MeshJoint(self.getJoint(index));
	}
	TS_JSAPI void tsMeshGeometry_clearMaterials(MeshGeometry &self) {
		self.clearMaterials();
	}
	TS_JSAPI void tsMeshGeometry_reserveMaterials(MeshGeometry &self, uint32_t num_materials) {
		self.reserveMaterials(num_materials);
	}
	TS_JSAPI uint32_t tsMeshGeometry_addMaterial(MeshGeometry &self, MeshMaterial &material, bool check) {
		return self.addMaterial(material, check);
	}
	TS_JSAPI uint32_t tsMeshGeometry_addMaterial_1(MeshGeometry &self, MeshMaterial &material, MeshIndices &indices, bool check) {
		return self.addMaterial(material, indices, check);
	}
	TS_JSAPI bool tsMeshGeometry_removeMaterial(MeshGeometry &self, MeshMaterial &material) {
		return self.removeMaterial(material);
	}
	TS_JSAPI bool tsMeshGeometry_replaceMaterial(MeshGeometry &self, MeshMaterial &old_material, MeshMaterial &material) {
		return self.replaceMaterial(old_material, material);
	}
	TS_JSAPI uint32_t tsMeshGeometry_findMaterial(const MeshGeometry &self, const MeshMaterial &material) {
		return self.findMaterial(material);
	}
	TS_JSAPI uint32_t tsMeshGeometry_findMaterial_1(const MeshGeometry &self, const char *name) {
		return self.findMaterial(name);
	}
	TS_JSAPI uint32_t tsMeshGeometry_getNumMaterials(const MeshGeometry &self) {
		return self.getNumMaterials();
	}
	TS_JSAPI const MeshMaterial *tsMeshGeometry_getMaterial(const MeshGeometry &self, uint32_t index) {
		return new MeshMaterial(self.getMaterial(index));
	}
	TS_JSAPI MeshMaterial *tsMeshGeometry_getMaterial_1(MeshGeometry &self, uint32_t index) {
		return new MeshMaterial(self.getMaterial(index));
	}
	TS_JSAPI void tsMeshGeometry_setBoundBox(MeshGeometry &self, const BoundBoxf &box) {
		self.setBoundBox(box);
	}
	TS_JSAPI const BoundBoxf *tsMeshGeometry_getBoundBox(const MeshGeometry &self) {
		return new BoundBoxf(self.getBoundBox());
	}
	TS_JSAPI void tsMeshGeometry_setBoundSphere(MeshGeometry &self, const BoundSpheref &sphere) {
		self.setBoundSphere(sphere);
	}
	TS_JSAPI const BoundSpheref *tsMeshGeometry_getBoundSphere(const MeshGeometry &self) {
		return new BoundSpheref(self.getBoundSphere());
	}
	TS_JSAPI bool tsMeshGeometry_setTransform(MeshGeometry &self, const Vector3f &scale) {
		return self.setTransform(scale);
	}
	TS_JSAPI bool tsMeshGeometry_setTransform_1(MeshGeometry &self, const Matrix4x3f &transform, bool apply) {
		return self.setTransform(transform, apply);
	}
	TS_JSAPI const Matrix4x3f *tsMeshGeometry_getTransform(const MeshGeometry &self) {
		return new Matrix4x3f(self.getTransform());
	}
	TS_JSAPI void tsMeshGeometry_setJointITransform(MeshGeometry &self, const Matrix4x3f &itransform) {
		self.setJointITransform(itransform);
	}
	TS_JSAPI const Matrix4x3f *tsMeshGeometry_getJointITransform(const MeshGeometry &self) {
		return new Matrix4x3f(self.getJointITransform());
	}
	TS_JSAPI void tsMeshGeometry_setMinVisibility(MeshGeometry &self, float32_t distance) {
		self.setMinVisibility(distance);
	}
	TS_JSAPI void tsMeshGeometry_setMaxVisibility(MeshGeometry &self, float32_t distance) {
		self.setMaxVisibility(distance);
	}
	TS_JSAPI void tsMeshGeometry_setVisibilityRange(MeshGeometry &self, float32_t min, float32_t max) {
		self.setVisibilityRange(min, max);
	}
	TS_JSAPI float32_t tsMeshGeometry_getMinVisibility(const MeshGeometry &self) {
		return self.getMinVisibility();
	}
	TS_JSAPI float32_t tsMeshGeometry_getMaxVisibility(const MeshGeometry &self) {
		return self.getMaxVisibility();
	}
	TS_JSAPI bool tsMeshGeometry_hasVisibilityRange(const MeshGeometry &self) {
		return self.hasVisibilityRange();
	}
	TS_JSAPI void tsMeshGeometry_setVisibilityError(MeshGeometry &self, float32_t error) {
		self.setVisibilityError(error);
	}
	TS_JSAPI float32_t tsMeshGeometry_getVisibilityError(const MeshGeometry &self) {
		return self.getVisibilityError();
	}
	TS_JSAPI void tsMeshGeometry_flipWinding(MeshGeometry &self) {
		self.flipWinding();
	}
	TS_JSAPI bool tsMeshGeometry_createBounds(MeshGeometry &self, bool force, uint32_t position) {
		return self.createBounds(force, position);
	}
	TS_JSAPI uint32_t tsMeshGeometry_createBasis(MeshGeometry &self, bool force, uint32_t position, uint32_t normal, uint32_t tangent, bool append) {
		return self.createBasis(force, position, normal, tangent, append);
	}
	TS_JSAPI uint32_t tsMeshGeometry_createBasis_1(MeshGeometry &self, float32_t angle, bool force, uint32_t position, uint32_t normal, uint32_t tangent, bool append) {
		return self.createBasis(angle, force, position, normal, tangent, append);
	}
	TS_JSAPI uint32_t tsMeshGeometry_createNormals(MeshGeometry &self, bool force, uint32_t position, bool append) {
		return self.createNormals(force, position, append);
	}
	TS_JSAPI uint32_t tsMeshGeometry_createNormals_1(MeshGeometry &self, float32_t angle, bool force, uint32_t position, bool append) {
		return self.createNormals(angle, force, position, append);
	}
	TS_JSAPI uint32_t tsMeshGeometry_createTangents(MeshGeometry &self, bool force, uint32_t position, uint32_t normal, uint32_t texcoord, bool append) {
		return self.createTangents(force, position, normal, texcoord, append);
	}
	TS_JSAPI uint32_t tsMeshGeometry_createIslands(MeshGeometry &self, uint32_t max_attributes, uint32_t max_primitives, bool force, uint32_t index, uint32_t position, bool append) {
		return self.createIslands(max_attributes, max_primitives, force, index, position, append);
	}
	TS_JSAPI bool tsMeshGeometry_optimizeIndices(MeshGeometry &self, uint32_t cache, bool transparent, uint32_t index, uint32_t position) {
		return self.optimizeIndices(cache, transparent, index, position);
	}
	TS_JSAPI bool tsMeshGeometry_optimizeAttributes(MeshGeometry &self, uint32_t material) {
		return self.optimizeAttributes(material);
	}
	TS_JSAPI void tsMeshGeometry_optimizeMaterials(MeshGeometry &self) {
		self.optimizeMaterials();
	}
	TS_JSAPI void tsMeshGeometry_optimizeOrder(MeshGeometry &self) {
		self.optimizeOrder();
	}
	TS_JSAPI bool tsMeshGeometry_packAttributes(MeshGeometry &self, bool remove) {
		return self.packAttributes(remove);
	}
	TS_JSAPI bool tsMeshGeometry_unpackAttributes(MeshGeometry &self, bool remove) {
		return self.unpackAttributes(remove);
	}
	TS_JSAPI bool tsMeshGeometry_addGeometry(MeshGeometry &self, const MeshGeometry &geometry, const Matrix4x3f &transform) {
		return self.addGeometry(geometry, transform);
	}
	TS_JSAPI int32_t tsMeshGeometry_compare(const MeshGeometry &self, const MeshGeometry &geometry, const Matrix4x3f &transform, float32_t threshold, bool spatial) {
		return self.compare(geometry, transform, threshold, spatial);
	}
	TS_JSAPI bool tsMeshGeometry_isOptimized(const MeshGeometry &self) {
		return self.isOptimized();
	}
	TS_JSAPI bool tsMeshGeometry_validate(const MeshGeometry &self) {
		return self.validate();
	}
	TS_JSAPI size_t tsMeshGeometry_getMemory(const MeshGeometry &self) {
		return self.getMemory();
	}
	
	// Tellusim::MeshTransform
	TS_JSAPI MeshTransform *tsMeshTransform_new() {
		return new MeshTransform();
	}
	TS_JSAPI void tsMeshTransform_delete(MeshTransform *self) {
		delete self;
	}
	TS_JSAPI bool tsMeshTransform_equalPtr(const MeshTransform &self, const MeshTransform &ptr) {
		return (self == ptr);
	}
	TS_JSAPI MeshTransform *tsMeshTransform_clonePtr(const MeshTransform &self) {
		return new MeshTransform(self.clonePtr());
	}
	TS_JSAPI void tsMeshTransform_clearPtr(MeshTransform &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsMeshTransform_destroyPtr(MeshTransform &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsMeshTransform_acquirePtr(MeshTransform &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsMeshTransform_unacquirePtr(MeshTransform &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsMeshTransform_isValidPtr(const MeshTransform &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsMeshTransform_isOwnerPtr(const MeshTransform &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsMeshTransform_isConstPtr(const MeshTransform &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsMeshTransform_getCountPtr(const MeshTransform &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsMeshTransform_getInternalPtr(const MeshTransform &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsMeshTransform_clear(MeshTransform &self) {
		self.clear();
	}
	TS_JSAPI float64_t tsMeshTransform_getMinTime(const MeshTransform &self) {
		return self.getMinTime();
	}
	TS_JSAPI float64_t tsMeshTransform_getMaxTime(const MeshTransform &self) {
		return self.getMaxTime();
	}
	TS_JSAPI void tsMeshTransform_setTransform(MeshTransform &self, float64_t time, const Matrix4x3d &transform, float32_t threshold) {
		self.setTransform(time, transform, threshold);
	}
	TS_JSAPI void tsMeshTransform_setTranslate(MeshTransform &self, float64_t time, const Vector3d &translate, float32_t threshold) {
		self.setTranslate(time, translate, threshold);
	}
	TS_JSAPI void tsMeshTransform_setRotate(MeshTransform &self, float64_t time, const Quaternionf &rotate, float32_t threshold) {
		self.setRotate(time, rotate, threshold);
	}
	TS_JSAPI void tsMeshTransform_setScale(MeshTransform &self, float64_t time, const Vector3f &scale, float32_t threshold) {
		self.setScale(time, scale, threshold);
	}
	TS_JSAPI void tsMeshTransform_setMorph(MeshTransform &self, float64_t time, const Vector4f &morph, float32_t threshold) {
		self.setMorph(time, morph, threshold);
	}
	TS_JSAPI Matrix4x3d *tsMeshTransform_getTransform(const MeshTransform &self, float64_t time) {
		return new Matrix4x3d(self.getTransform(time));
	}
	TS_JSAPI Vector3d *tsMeshTransform_getTranslate(const MeshTransform &self, float64_t time) {
		return new Vector3d(self.getTranslate(time));
	}
	TS_JSAPI Quaternionf *tsMeshTransform_getRotate(const MeshTransform &self, float64_t time) {
		return new Quaternionf(self.getRotate(time));
	}
	TS_JSAPI Vector3f *tsMeshTransform_getScale(const MeshTransform &self, float64_t time) {
		return new Vector3f(self.getScale(time));
	}
	TS_JSAPI Vector4f *tsMeshTransform_getMorph(const MeshTransform &self, float64_t time) {
		return new Vector4f(self.getMorph(time));
	}
	TS_JSAPI bool tsMeshTransform_hasTransformKeys(const MeshTransform &self) {
		return self.hasTransformKeys();
	}
	TS_JSAPI bool tsMeshTransform_hasTranslateKeys(const MeshTransform &self) {
		return self.hasTranslateKeys();
	}
	TS_JSAPI bool tsMeshTransform_hasRotateKeys(const MeshTransform &self) {
		return self.hasRotateKeys();
	}
	TS_JSAPI bool tsMeshTransform_hasScaleKeys(const MeshTransform &self) {
		return self.hasScaleKeys();
	}
	TS_JSAPI bool tsMeshTransform_hasMorphKeys(const MeshTransform &self) {
		return self.hasMorphKeys();
	}
	TS_JSAPI void tsMeshTransform_setTransform_1(MeshTransform &self, const Vector3d &scale) {
		self.setTransform(scale);
	}
	TS_JSAPI void tsMeshTransform_setTransform_2(MeshTransform &self, const Matrix4x3d &transform) {
		self.setTransform(transform);
	}
	TS_JSAPI size_t tsMeshTransform_getMemory(const MeshTransform &self) {
		return self.getMemory();
	}
	
	// Tellusim::MeshAnimation
	TS_JSAPI MeshAnimation *tsMeshAnimation_new(const char *name) {
		return new MeshAnimation(name);
	}
	TS_JSAPI MeshAnimation *tsMeshAnimation_new_1(Mesh &mesh, const char *name) {
		return new MeshAnimation(mesh, name);
	}
	TS_JSAPI void tsMeshAnimation_delete(MeshAnimation *self) {
		delete self;
	}
	TS_JSAPI bool tsMeshAnimation_equalPtr(const MeshAnimation &self, const MeshAnimation &ptr) {
		return (self == ptr);
	}
	TS_JSAPI MeshAnimation *tsMeshAnimation_clonePtr(const MeshAnimation &self) {
		return new MeshAnimation(self.clonePtr());
	}
	TS_JSAPI void tsMeshAnimation_clearPtr(MeshAnimation &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsMeshAnimation_destroyPtr(MeshAnimation &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsMeshAnimation_acquirePtr(MeshAnimation &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsMeshAnimation_unacquirePtr(MeshAnimation &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsMeshAnimation_isValidPtr(const MeshAnimation &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsMeshAnimation_isOwnerPtr(const MeshAnimation &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsMeshAnimation_isConstPtr(const MeshAnimation &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsMeshAnimation_getCountPtr(const MeshAnimation &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsMeshAnimation_getInternalPtr(const MeshAnimation &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsMeshAnimation_clear(MeshAnimation &self) {
		self.clear();
	}
	TS_JSAPI uint32_t tsMeshAnimation_getIndex(const MeshAnimation &self) {
		return self.getIndex();
	}
	TS_JSAPI void tsMeshAnimation_setName(MeshAnimation &self, const char *name) {
		self.setName(name);
	}
	TS_JSAPI String *tsMeshAnimation_getName(const MeshAnimation &self) {
		return new String(self.getName());
	}
	TS_JSAPI void tsMeshAnimation_setMesh(MeshAnimation &self, Mesh &mesh, bool check) {
		self.setMesh(mesh, check);
	}
	TS_JSAPI const Mesh *tsMeshAnimation_getMesh(const MeshAnimation &self) {
		return new Mesh(self.getMesh());
	}
	TS_JSAPI Mesh *tsMeshAnimation_getMesh_1(MeshAnimation &self) {
		return new Mesh(self.getMesh());
	}
	TS_JSAPI float64_t tsMeshAnimation_getMinTime(const MeshAnimation &self) {
		return self.getMinTime();
	}
	TS_JSAPI float64_t tsMeshAnimation_getMaxTime(const MeshAnimation &self) {
		return self.getMaxTime();
	}
	TS_JSAPI void tsMeshAnimation_setNumTransforms(MeshAnimation &self, uint32_t num_transforms) {
		self.setNumTransforms(num_transforms);
	}
	TS_JSAPI uint32_t tsMeshAnimation_getNumTransforms(const MeshAnimation &self) {
		return self.getNumTransforms();
	}
	TS_JSAPI const MeshTransform *tsMeshAnimation_getTransform(const MeshAnimation &self, uint32_t node) {
		return new MeshTransform(self.getTransform(node));
	}
	TS_JSAPI MeshTransform *tsMeshAnimation_getTransform_1(MeshAnimation &self, uint32_t node) {
		return new MeshTransform(self.getTransform(node));
	}
	TS_JSAPI void tsMeshAnimation_setTransform(MeshAnimation &self, float64_t time, uint32_t node, const Matrix4x3d &transform, float32_t threshold) {
		self.setTransform(time, node, transform, threshold);
	}
	TS_JSAPI void tsMeshAnimation_setTranslate(MeshAnimation &self, float64_t time, uint32_t node, const Vector3d &translate, float32_t threshold) {
		self.setTranslate(time, node, translate, threshold);
	}
	TS_JSAPI void tsMeshAnimation_setRotate(MeshAnimation &self, float64_t time, uint32_t node, const Quaternionf &rotate, float32_t threshold) {
		self.setRotate(time, node, rotate, threshold);
	}
	TS_JSAPI void tsMeshAnimation_setScale(MeshAnimation &self, float64_t time, uint32_t node, const Vector3f &scale, float32_t threshold) {
		self.setScale(time, node, scale, threshold);
	}
	TS_JSAPI void tsMeshAnimation_setMorph(MeshAnimation &self, float64_t time, uint32_t node, const Vector4f &morph, float32_t threshold) {
		self.setMorph(time, node, morph, threshold);
	}
	TS_JSAPI void tsMeshAnimation_setTime(MeshAnimation &self, float64_t time, const Matrix4x3d &transform, bool loop, float64_t from, float64_t to) {
		self.setTime(time, transform, loop, from, to);
	}
	TS_JSAPI void tsMeshAnimation_setTime_1(MeshAnimation &self, float64_t time, bool loop, float64_t from, float64_t to) {
		self.setTime(time, loop, from, to);
	}
	TS_JSAPI const Matrix4x3d *tsMeshAnimation_getLocalTransform(const MeshAnimation &self, uint32_t node) {
		return new Matrix4x3d(self.getLocalTransform(node));
	}
	TS_JSAPI const Matrix4x3d *tsMeshAnimation_getLocalTransform_1(const MeshAnimation &self, const MeshNode &node) {
		return new Matrix4x3d(self.getLocalTransform(node));
	}
	TS_JSAPI const Matrix4x3d *tsMeshAnimation_getLocalTransform_2(const MeshAnimation &self, const MeshJoint &joint) {
		return new Matrix4x3d(self.getLocalTransform(joint));
	}
	TS_JSAPI const Matrix4x3d *tsMeshAnimation_getGlobalTransform(const MeshAnimation &self, uint32_t node) {
		return new Matrix4x3d(self.getGlobalTransform(node));
	}
	TS_JSAPI const Matrix4x3d *tsMeshAnimation_getGlobalTransform_1(const MeshAnimation &self, const MeshNode &node) {
		return new Matrix4x3d(self.getGlobalTransform(node));
	}
	TS_JSAPI const Matrix4x3d *tsMeshAnimation_getGlobalTransform_2(const MeshAnimation &self, const MeshJoint &joint) {
		return new Matrix4x3d(self.getGlobalTransform(joint));
	}
	TS_JSAPI const Vector4f *tsMeshAnimation_getMorphTransform(const MeshAnimation &self, uint32_t node) {
		return new Vector4f(self.getMorphTransform(node));
	}
	TS_JSAPI const Vector4f *tsMeshAnimation_getMorphTransform_1(const MeshAnimation &self, const MeshNode &node) {
		return new Vector4f(self.getMorphTransform(node));
	}
	TS_JSAPI BoundBoxd *tsMeshAnimation_getBoundBox(const MeshAnimation &self) {
		return new BoundBoxd(self.getBoundBox());
	}
	TS_JSAPI BoundBoxd *tsMeshAnimation_getBoundBox_1(const MeshAnimation &self, const MeshNode &node) {
		return new BoundBoxd(self.getBoundBox(node));
	}
	TS_JSAPI BoundBoxd *tsMeshAnimation_getBoundBox_2(const MeshAnimation &self, const MeshGeometry &geometry) {
		return new BoundBoxd(self.getBoundBox(geometry));
	}
	TS_JSAPI BoundBoxd *tsMeshAnimation_getBoundBox_3(const MeshAnimation &self, const MeshGeometry &geometry, const Vector4f &morph) {
		return new BoundBoxd(self.getBoundBox(geometry, morph));
	}
	TS_JSAPI void tsMeshAnimation_setTransform_1(MeshAnimation &self, const Vector3d &scale) {
		self.setTransform(scale);
	}
	TS_JSAPI void tsMeshAnimation_setTransform_2(MeshAnimation &self, const Matrix4x3d &transform) {
		self.setTransform(transform);
	}
	TS_JSAPI void tsMeshAnimation_optimizeTransforms(MeshAnimation &self, float32_t threshold) {
		self.optimizeTransforms(threshold);
	}
	TS_JSAPI size_t tsMeshAnimation_getMemory(const MeshAnimation &self) {
		return self.getMemory();
	}
	
	// Tellusim::MeshAttachment
	TS_JSAPI MeshAttachment *tsMeshAttachment_new(const char *name) {
		return new MeshAttachment(name);
	}
	TS_JSAPI MeshAttachment *tsMeshAttachment_new_1(uint32_t type, const char *name) {
		return new MeshAttachment((MeshAttachment::Type)type, name);
	}
	TS_JSAPI MeshAttachment *tsMeshAttachment_new_2(MeshNode &node, const char *name) {
		return new MeshAttachment(node, name);
	}
	TS_JSAPI void tsMeshAttachment_delete(MeshAttachment *self) {
		delete self;
	}
	TS_JSAPI bool tsMeshAttachment_equalPtr(const MeshAttachment &self, const MeshAttachment &ptr) {
		return (self == ptr);
	}
	TS_JSAPI MeshAttachment *tsMeshAttachment_clonePtr(const MeshAttachment &self) {
		return new MeshAttachment(self.clonePtr());
	}
	TS_JSAPI void tsMeshAttachment_clearPtr(MeshAttachment &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsMeshAttachment_destroyPtr(MeshAttachment &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsMeshAttachment_acquirePtr(MeshAttachment &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsMeshAttachment_unacquirePtr(MeshAttachment &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsMeshAttachment_isValidPtr(const MeshAttachment &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsMeshAttachment_isOwnerPtr(const MeshAttachment &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsMeshAttachment_isConstPtr(const MeshAttachment &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsMeshAttachment_getCountPtr(const MeshAttachment &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsMeshAttachment_getInternalPtr(const MeshAttachment &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsMeshAttachment_clear(MeshAttachment &self) {
		self.clear();
	}
	TS_JSAPI void tsMeshAttachment_setType(MeshAttachment &self, uint32_t type) {
		self.setType((MeshAttachment::Type)type);
	}
	TS_JSAPI uint32_t tsMeshAttachment_getType(const MeshAttachment &self) {
		return self.getType();
	}
	TS_JSAPI const char* tsMeshAttachment_getTypeName(uint32_t type) {
		return MeshAttachment::getTypeName((MeshAttachment::Type)type);
	}
	TS_JSAPI const char* tsMeshAttachment_getTypeName_1(const MeshAttachment &self) {
		return self.getTypeName();
	}
	TS_JSAPI bool tsMeshAttachment_isUnknown(const MeshAttachment &self) {
		return self.isUnknown();
	}
	TS_JSAPI bool tsMeshAttachment_isLight(const MeshAttachment &self) {
		return self.isLight();
	}
	TS_JSAPI bool tsMeshAttachment_isCamera(const MeshAttachment &self) {
		return self.isCamera();
	}
	TS_JSAPI void tsMeshAttachment_setName(MeshAttachment &self, const char *name) {
		self.setName(name);
	}
	TS_JSAPI String *tsMeshAttachment_getName(const MeshAttachment &self) {
		return new String(self.getName());
	}
	TS_JSAPI void tsMeshAttachment_setNode(MeshAttachment &self, MeshNode &node, bool check) {
		self.setNode(node, check);
	}
	TS_JSAPI const MeshNode *tsMeshAttachment_getNode(const MeshAttachment &self) {
		return new MeshNode(self.getNode());
	}
	TS_JSAPI MeshNode *tsMeshAttachment_getNode_1(MeshAttachment &self) {
		return new MeshNode(self.getNode());
	}
	TS_JSAPI void tsMeshAttachment_setData(MeshAttachment &self, const char *data) {
		self.setData(data);
	}
	TS_JSAPI void tsMeshAttachment_setData_1(MeshAttachment &self, const String &data) {
		self.setData(data);
	}
	TS_JSAPI String *tsMeshAttachment_getData(const MeshAttachment &self) {
		return new String(self.getData());
	}
	TS_JSAPI void tsMeshAttachment_clearParameters(MeshAttachment &self) {
		self.clearParameters();
	}
	TS_JSAPI bool tsMeshAttachment_removeParameter(MeshAttachment &self, const char *type) {
		return self.removeParameter(type);
	}
	TS_JSAPI void tsMeshAttachment_copyParameters(MeshAttachment &self, const MeshAttachment &attachment) {
		self.copyParameters(attachment);
	}
	TS_JSAPI uint32_t tsMeshAttachment_findParameter(const MeshAttachment &self, const char *type) {
		return self.findParameter(type);
	}
	TS_JSAPI bool tsMeshAttachment_hasParameter(const MeshAttachment &self, const char *type) {
		return self.hasParameter(type);
	}
	TS_JSAPI uint32_t tsMeshAttachment_getNumParameters(const MeshAttachment &self) {
		return self.getNumParameters();
	}
	TS_JSAPI String *tsMeshAttachment_getParameterType(const MeshAttachment &self, uint32_t index) {
		return new String(self.getParameterType(index));
	}
	TS_JSAPI void tsMeshAttachment_addParameter(MeshAttachment &self, const char *type, bool value) {
		self.addParameter(type, value);
	}
	TS_JSAPI void tsMeshAttachment_addParameter_1(MeshAttachment &self, const char *type, float32_t value) {
		self.addParameter(type, value);
	}
	TS_JSAPI void tsMeshAttachment_addParameter_2(MeshAttachment &self, const char *type, const Vector4f &vector) {
		self.addParameter(type, vector);
	}
	TS_JSAPI void tsMeshAttachment_addParameter_3(MeshAttachment &self, const char *type, const Color &color) {
		self.addParameter(type, color);
	}
	TS_JSAPI void tsMeshAttachment_addParameter_4(MeshAttachment &self, const char *type, const char *name) {
		self.addParameter(type, name);
	}
	TS_JSAPI void tsMeshAttachment_addParameter_5(MeshAttachment &self, const char *type, const String &name) {
		self.addParameter(type, name);
	}
	TS_JSAPI uint32_t tsMeshAttachment_getParameterFlags(const MeshAttachment &self, uint32_t index) {
		return self.getParameterFlags(index);
	}
	TS_JSAPI bool tsMeshAttachment_hasParameterFlag(const MeshAttachment &self, uint32_t index, uint32_t flags) {
		return self.hasParameterFlag(index, (MeshAttachment::Flags)flags);
	}
	TS_JSAPI bool tsMeshAttachment_hasParameterFlags(const MeshAttachment &self, uint32_t index, uint32_t flags) {
		return self.hasParameterFlags(index, (MeshAttachment::Flags)flags);
	}
	TS_JSAPI bool tsMeshAttachment_getParameterBool(const MeshAttachment &self, uint32_t index, bool value) {
		return self.getParameterBool(index, value);
	}
	TS_JSAPI float32_t tsMeshAttachment_getParameterScalarf32(const MeshAttachment &self, uint32_t index, float32_t value) {
		return self.getParameterScalarf32(index, value);
	}
	TS_JSAPI const Vector4f *tsMeshAttachment_getParameterVector4f(const MeshAttachment &self, uint32_t index, const Vector4f &vector) {
		return new Vector4f(self.getParameterVector4f(index, vector));
	}
	TS_JSAPI const Color *tsMeshAttachment_getParameterColor(const MeshAttachment &self, uint32_t index, const Color &color) {
		return new Color(self.getParameterColor(index, color));
	}
	TS_JSAPI String *tsMeshAttachment_getParameterName(const MeshAttachment &self, uint32_t index, const String &name) {
		return new String(self.getParameterName(index, name));
	}
	TS_JSAPI uint32_t tsMeshAttachment_getParameterFlags_1(const MeshAttachment &self, const char *type) {
		return self.getParameterFlags(type);
	}
	TS_JSAPI bool tsMeshAttachment_hasParameterFlag_1(const MeshAttachment &self, const char *type, uint32_t flags) {
		return self.hasParameterFlag(type, (MeshAttachment::Flags)flags);
	}
	TS_JSAPI bool tsMeshAttachment_hasParameterFlags_1(const MeshAttachment &self, const char *type, uint32_t flags) {
		return self.hasParameterFlags(type, (MeshAttachment::Flags)flags);
	}
	TS_JSAPI bool tsMeshAttachment_getParameterBool_1(const MeshAttachment &self, const char *type, bool value) {
		return self.getParameterBool(type, value);
	}
	TS_JSAPI float32_t tsMeshAttachment_getParameterScalarf32_1(const MeshAttachment &self, const char *type, float32_t value) {
		return self.getParameterScalarf32(type, value);
	}
	TS_JSAPI const Vector4f *tsMeshAttachment_getParameterVector4f_1(const MeshAttachment &self, const char *type, const Vector4f &vector) {
		return new Vector4f(self.getParameterVector4f(type, vector));
	}
	TS_JSAPI const Color *tsMeshAttachment_getParameterColor_1(const MeshAttachment &self, const char *type, const Color &color) {
		return new Color(self.getParameterColor(type, color));
	}
	TS_JSAPI String *tsMeshAttachment_getParameterName_1(const MeshAttachment &self, const char *type, const String &name) {
		return new String(self.getParameterName(type, name));
	}
	TS_JSAPI void tsMeshAttachment_setTransform(MeshAttachment &self, const Vector3f &scale) {
		self.setTransform(scale);
	}
	TS_JSAPI void tsMeshAttachment_setTransform_1(MeshAttachment &self, const Matrix4x3f &transform) {
		self.setTransform(transform);
	}
	TS_JSAPI const Matrix4x3f *tsMeshAttachment_getTransform(const MeshAttachment &self) {
		return new Matrix4x3f(self.getTransform());
	}
	TS_JSAPI int32_t tsMeshAttachment_compare(const MeshAttachment &self, const MeshAttachment &attachment) {
		return self.compare(attachment);
	}
	TS_JSAPI size_t tsMeshAttachment_getMemory(const MeshAttachment &self) {
		return self.getMemory();
	}
	
	// Tellusim::Mesh
	TS_JSAPI Mesh *tsMesh_new() {
		return new Mesh();
	}
	TS_JSAPI void tsMesh_delete(Mesh *self) {
		delete self;
	}
	TS_JSAPI bool tsMesh_equalPtr(const Mesh &self, const Mesh &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Mesh *tsMesh_clonePtr(const Mesh &self) {
		return new Mesh(self.clonePtr());
	}
	TS_JSAPI void tsMesh_clearPtr(Mesh &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsMesh_destroyPtr(Mesh &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsMesh_acquirePtr(Mesh &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsMesh_unacquirePtr(Mesh &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsMesh_isValidPtr(const Mesh &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsMesh_isOwnerPtr(const Mesh &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsMesh_isConstPtr(const Mesh &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsMesh_getCountPtr(const Mesh &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsMesh_getInternalPtr(const Mesh &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsMesh_clear(Mesh &self) {
		self.clear();
	}
	TS_JSAPI bool tsMesh_isLoaded(const Mesh &self) {
		return self.isLoaded();
	}
	TS_JSAPI bool tsMesh_info(Mesh &self, const char *name, uint32_t flags, Async *async) {
		return self.info(name, (Mesh::Flags)flags, async);
	}
	TS_JSAPI bool tsMesh_info_1(Mesh &self, const String &name, uint32_t flags, Async *async) {
		return self.info(name, (Mesh::Flags)flags, async);
	}
	TS_JSAPI bool tsMesh_info_2(Mesh &self, Stream &stream, uint32_t flags, Async *async) {
		return self.info(stream, (Mesh::Flags)flags, async);
	}
	TS_JSAPI bool tsMesh_info_3(Mesh &self, const char *name, Async *async) {
		return self.info(name, async);
	}
	TS_JSAPI bool tsMesh_info_4(Mesh &self, const String &name, Async *async) {
		return self.info(name, async);
	}
	TS_JSAPI bool tsMesh_info_5(Mesh &self, Stream &stream, Async *async) {
		return self.info(stream, async);
	}
	TS_JSAPI bool tsMesh_load(Mesh &self, const char *name, uint32_t flags, Async *async) {
		return self.load(name, (Mesh::Flags)flags, async);
	}
	TS_JSAPI bool tsMesh_load_1(Mesh &self, const String &name, uint32_t flags, Async *async) {
		return self.load(name, (Mesh::Flags)flags, async);
	}
	TS_JSAPI bool tsMesh_load_2(Mesh &self, Stream &stream, uint32_t flags, Async *async) {
		return self.load(stream, (Mesh::Flags)flags, async);
	}
	TS_JSAPI bool tsMesh_load_3(Mesh &self, const char *name, Async *async) {
		return self.load(name, async);
	}
	TS_JSAPI bool tsMesh_load_4(Mesh &self, const String &name, Async *async) {
		return self.load(name, async);
	}
	TS_JSAPI bool tsMesh_load_5(Mesh &self, Stream &stream, Async *async) {
		return self.load(stream, async);
	}
	TS_JSAPI bool tsMesh_save(const Mesh &self, const char *name, uint32_t flags) {
		return self.save(name, (Mesh::Flags)flags);
	}
	TS_JSAPI bool tsMesh_save_1(const Mesh &self, const String &name, uint32_t flags) {
		return self.save(name, (Mesh::Flags)flags);
	}
	TS_JSAPI bool tsMesh_save_2(const Mesh &self, Stream &stream, uint32_t flags) {
		return self.save(stream, (Mesh::Flags)flags);
	}
	TS_JSAPI void tsMesh_setName(Mesh &self, const char *name) {
		self.setName(name);
	}
	TS_JSAPI String *tsMesh_getName(const Mesh &self) {
		return new String(self.getName());
	}
	TS_JSAPI bool tsMesh_setBasis(Mesh &self, uint32_t front, uint32_t right, uint32_t up) {
		return self.setBasis((Mesh::Axis)front, (Mesh::Axis)right, (Mesh::Axis)up);
	}
	TS_JSAPI bool tsMesh_setBasis_1(Mesh &self, uint32_t basis) {
		return self.setBasis((Mesh::Basis)basis);
	}
	TS_JSAPI uint32_t tsMesh_getFrontAxis(const Mesh &self) {
		return self.getFrontAxis();
	}
	TS_JSAPI uint32_t tsMesh_getRightAxis(const Mesh &self) {
		return self.getRightAxis();
	}
	TS_JSAPI uint32_t tsMesh_getUpAxis(const Mesh &self) {
		return self.getUpAxis();
	}
	TS_JSAPI uint32_t tsMesh_getBasis(const Mesh &self) {
		return self.getBasis();
	}
	TS_JSAPI const char* tsMesh_getFrontAxisName(const Mesh &self) {
		return self.getFrontAxisName();
	}
	TS_JSAPI const char* tsMesh_getRightAxisName(const Mesh &self) {
		return self.getRightAxisName();
	}
	TS_JSAPI const char* tsMesh_getUpAxisName(const Mesh &self) {
		return self.getUpAxisName();
	}
	TS_JSAPI String *tsMesh_getBasisName(const Mesh &self) {
		return new String(self.getBasisName());
	}
	TS_JSAPI void tsMesh_clearNodes(Mesh &self) {
		self.clearNodes();
	}
	TS_JSAPI void tsMesh_reserveNodes(Mesh &self, uint32_t num_nodes) {
		self.reserveNodes(num_nodes);
	}
	TS_JSAPI uint32_t tsMesh_addNode(Mesh &self, MeshNode &node, bool check) {
		return self.addNode(node, check);
	}
	TS_JSAPI bool tsMesh_removeNode(Mesh &self, MeshNode &node) {
		return self.removeNode(node);
	}
	TS_JSAPI uint32_t tsMesh_findNode(const Mesh &self, const MeshNode &node) {
		return self.findNode(node);
	}
	TS_JSAPI uint32_t tsMesh_findNode_1(const Mesh &self, const char *name) {
		return self.findNode(name);
	}
	TS_JSAPI uint32_t tsMesh_getNumNodes(const Mesh &self) {
		return self.getNumNodes();
	}
	TS_JSAPI const MeshNode *tsMesh_getNode(const Mesh &self, uint32_t index) {
		return new MeshNode(self.getNode(index));
	}
	TS_JSAPI MeshNode *tsMesh_getNode_1(Mesh &self, uint32_t index) {
		return new MeshNode(self.getNode(index));
	}
	TS_JSAPI void tsMesh_createLocalTransforms(Mesh &self, const Matrix4x3d &itransform) {
		self.createLocalTransforms(itransform);
	}
	TS_JSAPI void tsMesh_createGlobalTransforms(Mesh &self, const Matrix4x3d &transform) {
		self.createGlobalTransforms(transform);
	}
	TS_JSAPI void tsMesh_clearGeometries(Mesh &self) {
		self.clearGeometries();
	}
	TS_JSAPI void tsMesh_reserveGeometries(Mesh &self, uint32_t num_geometries) {
		self.reserveGeometries(num_geometries);
	}
	TS_JSAPI uint32_t tsMesh_addGeometry(Mesh &self, MeshGeometry &geometry, bool check) {
		return self.addGeometry(geometry, check);
	}
	TS_JSAPI uint32_t tsMesh_addGeometry_1(Mesh &self, MeshGeometry &geometry, MeshNode &node, bool check) {
		return self.addGeometry(geometry, node, check);
	}
	TS_JSAPI bool tsMesh_removeGeometry(Mesh &self, MeshGeometry &geometry) {
		return self.removeGeometry(geometry);
	}
	TS_JSAPI bool tsMesh_replaceGeometry(Mesh &self, MeshGeometry &old_geometry, MeshGeometry &geometry) {
		return self.replaceGeometry(old_geometry, geometry);
	}
	TS_JSAPI uint32_t tsMesh_findGeometry(const Mesh &self, const MeshGeometry &geometry) {
		return self.findGeometry(geometry);
	}
	TS_JSAPI uint32_t tsMesh_findGeometry_1(const Mesh &self, const char *name) {
		return self.findGeometry(name);
	}
	TS_JSAPI uint32_t tsMesh_getNumGeometries(const Mesh &self) {
		return self.getNumGeometries();
	}
	TS_JSAPI const MeshGeometry *tsMesh_getGeometry(const Mesh &self, uint32_t index) {
		return new MeshGeometry(self.getGeometry(index));
	}
	TS_JSAPI MeshGeometry *tsMesh_getGeometry_1(Mesh &self, uint32_t index) {
		return new MeshGeometry(self.getGeometry(index));
	}
	TS_JSAPI bool tsMesh_hasGeometryIndices(const Mesh &self, uint32_t type) {
		return self.hasGeometryIndices((MeshIndices::Type)type);
	}
	TS_JSAPI bool tsMesh_hasGeometryAttribute(const Mesh &self, uint32_t type) {
		return self.hasGeometryAttribute((MeshAttribute::Type)type);
	}
	TS_JSAPI size_t tsMesh_getNumGeometryPositions(const Mesh &self) {
		return self.getNumGeometryPositions();
	}
	TS_JSAPI size_t tsMesh_getNumGeometryPrimitives(const Mesh &self) {
		return self.getNumGeometryPrimitives();
	}
	TS_JSAPI void tsMesh_clearAnimations(Mesh &self) {
		self.clearAnimations();
	}
	TS_JSAPI void tsMesh_reserveAnimations(Mesh &self, uint32_t num_animations) {
		self.reserveAnimations(num_animations);
	}
	TS_JSAPI uint32_t tsMesh_addAnimation(Mesh &self, MeshAnimation &animation, bool check) {
		return self.addAnimation(animation, check);
	}
	TS_JSAPI bool tsMesh_removeAnimation(Mesh &self, MeshAnimation &animation) {
		return self.removeAnimation(animation);
	}
	TS_JSAPI bool tsMesh_replaceAnimation(Mesh &self, MeshAnimation &old_animation, MeshAnimation &animation) {
		return self.replaceAnimation(old_animation, animation);
	}
	TS_JSAPI uint32_t tsMesh_findAnimation(const Mesh &self, const MeshAnimation &animation) {
		return self.findAnimation(animation);
	}
	TS_JSAPI uint32_t tsMesh_findAnimation_1(const Mesh &self, const char *name) {
		return self.findAnimation(name);
	}
	TS_JSAPI uint32_t tsMesh_getNumAnimations(const Mesh &self) {
		return self.getNumAnimations();
	}
	TS_JSAPI const MeshAnimation *tsMesh_getAnimation(const Mesh &self, uint32_t index) {
		return new MeshAnimation(self.getAnimation(index));
	}
	TS_JSAPI MeshAnimation *tsMesh_getAnimation_1(Mesh &self, uint32_t index) {
		return new MeshAnimation(self.getAnimation(index));
	}
	TS_JSAPI BoundBoxd *tsMesh_getBoundBox(const Mesh &self) {
		return new BoundBoxd(self.getBoundBox());
	}
	TS_JSAPI BoundBoxd *tsMesh_getBoundBox_1(const Mesh &self, const MeshNode &node) {
		return new BoundBoxd(self.getBoundBox(node));
	}
	TS_JSAPI BoundBoxd *tsMesh_getBoundBox_2(const Mesh &self, const MeshGeometry &geometry) {
		return new BoundBoxd(self.getBoundBox(geometry));
	}
	TS_JSAPI bool tsMesh_createBounds(Mesh &self, bool force, Async *async) {
		return self.createBounds(force, async);
	}
	TS_JSAPI bool tsMesh_createBounds_1(Mesh &self, Async *async) {
		return self.createBounds(async);
	}
	TS_JSAPI bool tsMesh_createBasis(Mesh &self, bool force, Async *async) {
		return self.createBasis(force, async);
	}
	TS_JSAPI bool tsMesh_createBasis_1(Mesh &self, float32_t angle, bool force, Async *async) {
		return self.createBasis(angle, force, async);
	}
	TS_JSAPI bool tsMesh_createBasis_2(Mesh &self, Async *async) {
		return self.createBasis(async);
	}
	TS_JSAPI bool tsMesh_createBasis_3(Mesh &self, float32_t angle, Async *async) {
		return self.createBasis(angle, async);
	}
	TS_JSAPI bool tsMesh_createNormals(Mesh &self, bool force, Async *async) {
		return self.createNormals(force, async);
	}
	TS_JSAPI bool tsMesh_createNormals_1(Mesh &self, float32_t angle, bool force, Async *async) {
		return self.createNormals(angle, force, async);
	}
	TS_JSAPI bool tsMesh_createNormals_2(Mesh &self, Async *async) {
		return self.createNormals(async);
	}
	TS_JSAPI bool tsMesh_createNormals_3(Mesh &self, float32_t angle, Async *async) {
		return self.createNormals(angle, async);
	}
	TS_JSAPI bool tsMesh_createTangents(Mesh &self, bool force, Async *async) {
		return self.createTangents(force, async);
	}
	TS_JSAPI bool tsMesh_createTangents_1(Mesh &self, Async *async) {
		return self.createTangents(async);
	}
	TS_JSAPI bool tsMesh_createIslands(Mesh &self, uint32_t max_attributes, uint32_t max_primitives, bool force, Async *async) {
		return self.createIslands(max_attributes, max_primitives, force, async);
	}
	TS_JSAPI bool tsMesh_createIslands_1(Mesh &self, uint32_t max_attributes, uint32_t max_primitives, Async *async) {
		return self.createIslands(max_attributes, max_primitives, async);
	}
	TS_JSAPI bool tsMesh_optimizeIndices(Mesh &self, uint32_t cache, bool transparent, Async *async) {
		return self.optimizeIndices(cache, transparent, async);
	}
	TS_JSAPI bool tsMesh_optimizeIndices_1(Mesh &self, Async *async) {
		return self.optimizeIndices(async);
	}
	TS_JSAPI bool tsMesh_optimizeIndices_2(Mesh &self, uint32_t cache, Async *async) {
		return self.optimizeIndices(cache, async);
	}
	TS_JSAPI bool tsMesh_optimizeAttributes(Mesh &self, Async *async) {
		return self.optimizeAttributes(async);
	}
	TS_JSAPI void tsMesh_optimizeMaterials(Mesh &self) {
		self.optimizeMaterials();
	}
	TS_JSAPI bool tsMesh_optimizeWinding(Mesh &self, bool clockwise) {
		return self.optimizeWinding(clockwise);
	}
	TS_JSAPI void tsMesh_optimizeGeometries(Mesh &self, float32_t threshold, uint32_t depth) {
		self.optimizeGeometries(threshold, depth);
	}
	TS_JSAPI void tsMesh_optimizeAnimations(Mesh &self, float32_t threshold) {
		self.optimizeAnimations(threshold);
	}
	TS_JSAPI bool tsMesh_optimizeOrder(Mesh &self) {
		return self.optimizeOrder();
	}
	TS_JSAPI void tsMesh_mergeGeometries(Mesh &self) {
		self.mergeGeometries();
	}
	TS_JSAPI bool tsMesh_packAttributes(Mesh &self, bool remove) {
		return self.packAttributes(remove);
	}
	TS_JSAPI bool tsMesh_unpackAttributes(Mesh &self, bool remove) {
		return self.unpackAttributes(remove);
	}
	TS_JSAPI bool tsMesh_setTransform(Mesh &self, const Vector3d &scale) {
		return self.setTransform(scale);
	}
	TS_JSAPI size_t tsMesh_getMemory(const Mesh &self) {
		return self.getMemory();
	}
	
	// Tellusim::Json
	TS_JSAPI Json *tsJson_new() {
		return new Json();
	}
	TS_JSAPI Json *tsJson_new_1(uint32_t type) {
		return new Json((Json::Type)type);
	}
	TS_JSAPI Json *tsJson_new_2(const char *name, uint32_t type) {
		return new Json(name, (Json::Type)type);
	}
	TS_JSAPI Json *tsJson_new_3(const String &name, uint32_t type) {
		return new Json(name, (Json::Type)type);
	}
	TS_JSAPI Json *tsJson_new_4(Json *parent, const char *name, uint32_t type) {
		return new Json(parent, name, (Json::Type)type);
	}
	TS_JSAPI Json *tsJson_new_5(Json *parent, const String &name, uint32_t type) {
		return new Json(parent, name, (Json::Type)type);
	}
	TS_JSAPI void tsJson_delete(Json *self) {
		delete self;
	}
	TS_JSAPI bool tsJson_equalPtr(const Json &self, const Json &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Json *tsJson_clonePtr(const Json &self) {
		return new Json(self.clonePtr());
	}
	TS_JSAPI void tsJson_clearPtr(Json &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsJson_destroyPtr(Json &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsJson_acquirePtr(Json &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsJson_unacquirePtr(Json &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsJson_isValidPtr(const Json &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsJson_isOwnerPtr(const Json &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsJson_isConstPtr(const Json &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsJson_getCountPtr(const Json &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsJson_getInternalPtr(const Json &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsJson_clear(Json &self) {
		self.clear();
	}
	TS_JSAPI bool tsJson_create(Json &self, const char *str, size_t size, bool owner) {
		return self.create(str, size, owner);
	}
	TS_JSAPI bool tsJson_create_1(Json &self, const String &str, size_t size, bool owner) {
		return self.create(str, size, owner);
	}
	TS_JSAPI bool tsJson_load(Json &self, const char *name) {
		return self.load(name);
	}
	TS_JSAPI bool tsJson_load_1(Json &self, const String &name) {
		return self.load(name);
	}
	TS_JSAPI bool tsJson_load_2(Json &self, Stream &stream) {
		return self.load(stream);
	}
	TS_JSAPI bool tsJson_save(const Json &self, const char *name, bool compact) {
		return self.save(name, compact);
	}
	TS_JSAPI bool tsJson_save_1(const Json &self, const String &name, bool compact) {
		return self.save(name, compact);
	}
	TS_JSAPI bool tsJson_save_2(const Json &self, Stream &stream, bool compact) {
		return self.save(stream, compact);
	}
	TS_JSAPI const Json *tsJson_getRoot(const Json &self) {
		return new Json(self.getRoot());
	}
	TS_JSAPI Json *tsJson_getRoot_1(Json &self) {
		return new Json(self.getRoot());
	}
	TS_JSAPI uint32_t tsJson_setParent(Json &self, Json &parent, bool check) {
		return self.setParent(parent, check);
	}
	TS_JSAPI const Json *tsJson_getParent(const Json &self) {
		return new Json(self.getParent());
	}
	TS_JSAPI Json *tsJson_getParent_1(Json &self) {
		return new Json(self.getParent());
	}
	TS_JSAPI Json *tsJson_addChild(Json &self, const char *name, uint32_t type, bool check) {
		return new Json(self.addChild(name, (Json::Type)type, check));
	}
	TS_JSAPI uint32_t tsJson_addChild_1(Json &self, Json &child, bool check) {
		return self.addChild(child, check);
	}
	TS_JSAPI bool tsJson_removeChild(Json &self, Json &child) {
		return self.removeChild(child);
	}
	TS_JSAPI void tsJson_releaseChildren(Json &self) {
		self.releaseChildren();
	}
	TS_JSAPI uint32_t tsJson_findChild(const Json &self, const char *name) {
		return self.findChild(name);
	}
	TS_JSAPI bool tsJson_isChild(const Json &self, const char *name) {
		return self.isChild(name);
	}
	TS_JSAPI const Json *tsJson_getChild(const Json &self, const char *name) {
		return new Json(self.getChild(name));
	}
	TS_JSAPI Json *tsJson_getChild_1(Json &self, const char *name) {
		return new Json(self.getChild(name));
	}
	TS_JSAPI uint32_t tsJson_getNumChildren(const Json &self) {
		return self.getNumChildren();
	}
	TS_JSAPI const Json *tsJson_getChild_2(const Json &self, uint32_t index) {
		return new Json(self.getChild(index));
	}
	TS_JSAPI Json *tsJson_getChild_3(Json &self, uint32_t index) {
		return new Json(self.getChild(index));
	}
	TS_JSAPI String *tsJson_getPathName(const Json &self) {
		return new String(self.getPathName());
	}
	TS_JSAPI void tsJson_setName(Json &self, const char *name) {
		self.setName(name);
	}
	TS_JSAPI void tsJson_setName_1(Json &self, const String &name) {
		self.setName(name);
	}
	TS_JSAPI String *tsJson_getName(const Json &self) {
		return new String(self.getName());
	}
	TS_JSAPI void tsJson_setType(Json &self, uint32_t type) {
		self.setType((Json::Type)type);
	}
	TS_JSAPI uint32_t tsJson_getType(const Json &self) {
		return self.getType();
	}
	TS_JSAPI const char* tsJson_getTypeName(uint32_t type) {
		return Json::getTypeName((Json::Type)type);
	}
	TS_JSAPI const char* tsJson_getTypeName_1(const Json &self) {
		return self.getTypeName();
	}
	TS_JSAPI bool tsJson_isUnknown(const Json &self) {
		return self.isUnknown();
	}
	TS_JSAPI bool tsJson_isNull(const Json &self) {
		return self.isNull();
	}
	TS_JSAPI bool tsJson_isBool(const Json &self) {
		return self.isBool();
	}
	TS_JSAPI bool tsJson_isNumber(const Json &self) {
		return self.isNumber();
	}
	TS_JSAPI bool tsJson_isString(const Json &self) {
		return self.isString();
	}
	TS_JSAPI bool tsJson_isObject(const Json &self) {
		return self.isObject();
	}
	TS_JSAPI bool tsJson_isArray(const Json &self) {
		return self.isArray();
	}
	TS_JSAPI void tsJson_setData(Json &self, bool value) {
		self.setData(value);
	}
	TS_JSAPI void tsJson_setData_1(Json &self, int32_t value, uint32_t radix) {
		self.setData(value, radix);
	}
	TS_JSAPI void tsJson_setData_2(Json &self, uint32_t value, uint32_t radix) {
		self.setData(value, radix);
	}
	TS_JSAPI void tsJson_setData_3(Json &self, uint64_t value, uint32_t radix) {
		self.setData(value, radix);
	}
	TS_JSAPI void tsJson_setData_4(Json &self, float32_t value, uint32_t digits, bool compact, bool exponent) {
		self.setData(value, digits, compact, exponent);
	}
	TS_JSAPI void tsJson_setData_5(Json &self, float64_t value, uint32_t digits, bool compact, bool exponent) {
		self.setData(value, digits, compact, exponent);
	}
	TS_JSAPI void tsJson_setData_6(Json &self, const char *value) {
		self.setData(value);
	}
	TS_JSAPI void tsJson_setData_7(Json &self, const String &value) {
		self.setData(value);
	}
	TS_JSAPI String *tsJson_getData(const Json &self) {
		return new String(self.getData());
	}
	TS_JSAPI bool tsJson_getDataBool(const Json &self) {
		return self.getDataBool();
	}
	TS_JSAPI int32_t tsJson_getDatai32(const Json &self, uint32_t radix) {
		return self.getDatai32(radix);
	}
	TS_JSAPI uint32_t tsJson_getDatau32(const Json &self, uint32_t radix) {
		return self.getDatau32(radix);
	}
	TS_JSAPI uint64_t tsJson_getDatau64(const Json &self, uint32_t radix) {
		return self.getDatau64(radix);
	}
	TS_JSAPI float32_t tsJson_getDataf32(const Json &self) {
		return self.getDataf32();
	}
	TS_JSAPI float64_t tsJson_getDataf64(const Json &self) {
		return self.getDataf64();
	}
	TS_JSAPI String *tsJson_getNumber(const Json &self) {
		return new String(self.getNumber());
	}
	TS_JSAPI String *tsJson_getString(const Json &self) {
		return new String(self.getString());
	}
	TS_JSAPI bool tsJson_getData_1(const Json &self, const char *name, bool value) {
		return self.getData(name, value);
	}
	TS_JSAPI int32_t tsJson_getData_2(const Json &self, const char *name, int32_t value, uint32_t radix) {
		return self.getData(name, value, radix);
	}
	TS_JSAPI uint32_t tsJson_getData_3(const Json &self, const char *name, uint32_t value, uint32_t radix) {
		return self.getData(name, value, radix);
	}
	TS_JSAPI uint64_t tsJson_getData_4(const Json &self, const char *name, uint64_t value, uint32_t radix) {
		return self.getData(name, value, radix);
	}
	TS_JSAPI float32_t tsJson_getData_5(const Json &self, const char *name, float32_t value) {
		return self.getData(name, value);
	}
	TS_JSAPI float64_t tsJson_getData_6(const Json &self, const char *name, float64_t value) {
		return self.getData(name, value);
	}
	TS_JSAPI String *tsJson_getData_7(const Json &self, const char *name, const String &value) {
		return new String(self.getData(name, value));
	}
	TS_JSAPI void tsJson_setData_8(Json &self, const char **values, uint32_t size) {
		self.setData(values, size);
	}
	TS_JSAPI void tsJson_setData_9(Json &self, const String *values, uint32_t size) {
		self.setData(values, size);
	}
	TS_JSAPI void tsJson_setData_10(Json &self, const int32_t *values, uint32_t size, uint32_t radix) {
		self.setData(values, size, radix);
	}
	TS_JSAPI void tsJson_setData_11(Json &self, const uint32_t *values, uint32_t size, uint32_t radix) {
		self.setData(values, size, radix);
	}
	TS_JSAPI void tsJson_setData_12(Json &self, const float32_t *values, uint32_t size, uint32_t digits, bool compact, bool exponent) {
		self.setData(values, size, digits, compact, exponent);
	}
	TS_JSAPI void tsJson_setData_13(Json &self, const float64_t *values, uint32_t size, uint32_t digits, bool compact, bool exponent) {
		self.setData(values, size, digits, compact, exponent);
	}
	TS_JSAPI uint32_t tsJson_getData_8(const Json &self, String *values, uint32_t size) {
		return self.getData(values, size);
	}
	TS_JSAPI uint32_t tsJson_getData_9(const Json &self, int32_t *values, uint32_t size, uint32_t radix) {
		return self.getData(values, size, radix);
	}
	TS_JSAPI uint32_t tsJson_getData_10(const Json &self, uint32_t *values, uint32_t size, uint32_t radix) {
		return self.getData(values, size, radix);
	}
	TS_JSAPI uint32_t tsJson_getData_11(const Json &self, float32_t *values, uint32_t size) {
		return self.getData(values, size);
	}
	TS_JSAPI uint32_t tsJson_getData_12(const Json &self, float64_t *values, uint32_t size) {
		return self.getData(values, size);
	}
	
	// Tellusim::Xml
	TS_JSAPI Xml *tsXml_new() {
		return new Xml();
	}
	TS_JSAPI Xml *tsXml_new_1(const char *name, const char *attributes) {
		return new Xml(name, attributes);
	}
	TS_JSAPI Xml *tsXml_new_2(const String &name, const char *attributes) {
		return new Xml(name, attributes);
	}
	TS_JSAPI Xml *tsXml_new_3(Xml *parent, const char *name, const char *attributes) {
		return new Xml(parent, name, attributes);
	}
	TS_JSAPI Xml *tsXml_new_4(Xml *parent, const String &name, const char *attributes) {
		return new Xml(parent, name, attributes);
	}
	TS_JSAPI void tsXml_delete(Xml *self) {
		delete self;
	}
	TS_JSAPI bool tsXml_equalPtr(const Xml &self, const Xml &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Xml *tsXml_clonePtr(const Xml &self) {
		return new Xml(self.clonePtr());
	}
	TS_JSAPI void tsXml_clearPtr(Xml &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsXml_destroyPtr(Xml &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsXml_acquirePtr(Xml &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsXml_unacquirePtr(Xml &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsXml_isValidPtr(const Xml &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsXml_isOwnerPtr(const Xml &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsXml_isConstPtr(const Xml &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsXml_getCountPtr(const Xml &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsXml_getInternalPtr(const Xml &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsXml_clear(Xml &self) {
		self.clear();
	}
	TS_JSAPI bool tsXml_create(Xml &self, const char *str, size_t size, bool owner) {
		return self.create(str, size, owner);
	}
	TS_JSAPI bool tsXml_create_1(Xml &self, const String &str, size_t size, bool owner) {
		return self.create(str, size, owner);
	}
	TS_JSAPI bool tsXml_load(Xml &self, const char *name) {
		return self.load(name);
	}
	TS_JSAPI bool tsXml_load_1(Xml &self, const String &name) {
		return self.load(name);
	}
	TS_JSAPI bool tsXml_load_2(Xml &self, Stream &stream) {
		return self.load(stream);
	}
	TS_JSAPI bool tsXml_save(const Xml &self, const char *name, bool compact) {
		return self.save(name, compact);
	}
	TS_JSAPI bool tsXml_save_1(const Xml &self, const String &name, bool compact) {
		return self.save(name, compact);
	}
	TS_JSAPI bool tsXml_save_2(const Xml &self, Stream &stream, bool compact) {
		return self.save(stream, compact);
	}
	TS_JSAPI const Xml *tsXml_getRoot(const Xml &self) {
		return new Xml(self.getRoot());
	}
	TS_JSAPI Xml *tsXml_getRoot_1(Xml &self) {
		return new Xml(self.getRoot());
	}
	TS_JSAPI uint32_t tsXml_setParent(Xml &self, Xml &parent, bool check) {
		return self.setParent(parent, check);
	}
	TS_JSAPI const Xml *tsXml_getParent(const Xml &self) {
		return new Xml(self.getParent());
	}
	TS_JSAPI Xml *tsXml_getParent_1(Xml &self) {
		return new Xml(self.getParent());
	}
	TS_JSAPI Xml *tsXml_addChild(Xml &self, const char *name, bool check) {
		return new Xml(self.addChild(name, check));
	}
	TS_JSAPI uint32_t tsXml_addChild_1(Xml &self, Xml &child, bool check) {
		return self.addChild(child, check);
	}
	TS_JSAPI bool tsXml_removeChild(Xml &self, Xml &child) {
		return self.removeChild(child);
	}
	TS_JSAPI void tsXml_releaseChildren(Xml &self) {
		self.releaseChildren();
	}
	TS_JSAPI uint32_t tsXml_findChild(const Xml &self, const char *name) {
		return self.findChild(name);
	}
	TS_JSAPI bool tsXml_isChild(const Xml &self, const char *name) {
		return self.isChild(name);
	}
	TS_JSAPI const Xml *tsXml_getChild(const Xml &self, const char *name) {
		return new Xml(self.getChild(name));
	}
	TS_JSAPI Xml *tsXml_getChild_1(Xml &self, const char *name) {
		return new Xml(self.getChild(name));
	}
	TS_JSAPI uint32_t tsXml_getNumChildren(const Xml &self) {
		return self.getNumChildren();
	}
	TS_JSAPI const Xml *tsXml_getChild_2(const Xml &self, uint32_t index) {
		return new Xml(self.getChild(index));
	}
	TS_JSAPI Xml *tsXml_getChild_3(Xml &self, uint32_t index) {
		return new Xml(self.getChild(index));
	}
	TS_JSAPI String *tsXml_getPathName(const Xml &self) {
		return new String(self.getPathName());
	}
	TS_JSAPI void tsXml_setName(Xml &self, const char *name) {
		self.setName(name);
	}
	TS_JSAPI void tsXml_setName_1(Xml &self, const String &name) {
		self.setName(name);
	}
	TS_JSAPI String *tsXml_getName(const Xml &self) {
		return new String(self.getName());
	}
	TS_JSAPI void tsXml_setData(Xml &self, bool value) {
		self.setData(value);
	}
	TS_JSAPI void tsXml_setData_1(Xml &self, const char *value) {
		self.setData(value);
	}
	TS_JSAPI void tsXml_setData_2(Xml &self, const String &value) {
		self.setData(value);
	}
	TS_JSAPI void tsXml_setData_3(Xml &self, int32_t value, uint32_t radix) {
		self.setData(value, radix);
	}
	TS_JSAPI void tsXml_setData_4(Xml &self, uint32_t value, uint32_t radix) {
		self.setData(value, radix);
	}
	TS_JSAPI void tsXml_setData_5(Xml &self, uint64_t value, uint32_t radix) {
		self.setData(value, radix);
	}
	TS_JSAPI void tsXml_setData_6(Xml &self, float32_t value, uint32_t digits, bool compact, bool exponent) {
		self.setData(value, digits, compact, exponent);
	}
	TS_JSAPI void tsXml_setData_7(Xml &self, float64_t value, uint32_t digits, bool compact, bool exponent) {
		self.setData(value, digits, compact, exponent);
	}
	TS_JSAPI String *tsXml_getData(const Xml &self) {
		return new String(self.getData());
	}
	TS_JSAPI bool tsXml_getDataBool(const Xml &self) {
		return self.getDataBool();
	}
	TS_JSAPI int32_t tsXml_getDatai32(const Xml &self, uint32_t radix) {
		return self.getDatai32(radix);
	}
	TS_JSAPI uint32_t tsXml_getDatau32(const Xml &self, uint32_t radix) {
		return self.getDatau32(radix);
	}
	TS_JSAPI uint64_t tsXml_getDatau64(const Xml &self, uint32_t radix) {
		return self.getDatau64(radix);
	}
	TS_JSAPI float32_t tsXml_getDataf32(const Xml &self) {
		return self.getDataf32();
	}
	TS_JSAPI float64_t tsXml_getDataf64(const Xml &self) {
		return self.getDataf64();
	}
	TS_JSAPI String *tsXml_getData_1(const Xml &self, const char *name, const String &value) {
		return new String(self.getData(name, value));
	}
	TS_JSAPI bool tsXml_getData_2(const Xml &self, const char *name, bool value) {
		return self.getData(name, value);
	}
	TS_JSAPI int32_t tsXml_getData_3(const Xml &self, const char *name, int32_t value, uint32_t radix) {
		return self.getData(name, value, radix);
	}
	TS_JSAPI uint32_t tsXml_getData_4(const Xml &self, const char *name, uint32_t value, uint32_t radix) {
		return self.getData(name, value, radix);
	}
	TS_JSAPI uint64_t tsXml_getData_5(const Xml &self, const char *name, uint64_t value, uint32_t radix) {
		return self.getData(name, value, radix);
	}
	TS_JSAPI float32_t tsXml_getData_6(const Xml &self, const char *name, float32_t value) {
		return self.getData(name, value);
	}
	TS_JSAPI float64_t tsXml_getData_7(const Xml &self, const char *name, float64_t value) {
		return self.getData(name, value);
	}
	TS_JSAPI void tsXml_setData_8(Xml &self, const char **values, uint32_t size, uint32_t wrap) {
		self.setData(values, size, wrap);
	}
	TS_JSAPI void tsXml_setData_9(Xml &self, const String *values, uint32_t size, uint32_t wrap) {
		self.setData(values, size, wrap);
	}
	TS_JSAPI void tsXml_setData_10(Xml &self, const int32_t *values, uint32_t size, uint32_t radix, uint32_t wrap) {
		self.setData(values, size, radix, wrap);
	}
	TS_JSAPI void tsXml_setData_11(Xml &self, const uint32_t *values, uint32_t size, uint32_t radix, uint32_t wrap) {
		self.setData(values, size, radix, wrap);
	}
	TS_JSAPI void tsXml_setData_12(Xml &self, const float32_t *values, uint32_t size, uint32_t digits, bool compact, bool exponent, uint32_t wrap) {
		self.setData(values, size, digits, compact, exponent, wrap);
	}
	TS_JSAPI void tsXml_setData_13(Xml &self, const float64_t *values, uint32_t size, uint32_t digits, bool compact, bool exponent, uint32_t wrap) {
		self.setData(values, size, digits, compact, exponent, wrap);
	}
	TS_JSAPI uint32_t tsXml_getData_8(const Xml &self, String *values, uint32_t size) {
		return self.getData(values, size);
	}
	TS_JSAPI uint32_t tsXml_getData_9(const Xml &self, int32_t *values, uint32_t size, uint32_t radix) {
		return self.getData(values, size, radix);
	}
	TS_JSAPI uint32_t tsXml_getData_10(const Xml &self, uint32_t *values, uint32_t size, uint32_t radix) {
		return self.getData(values, size, radix);
	}
	TS_JSAPI uint32_t tsXml_getData_11(const Xml &self, float32_t *values, uint32_t size) {
		return self.getData(values, size);
	}
	TS_JSAPI uint32_t tsXml_getData_12(const Xml &self, float64_t *values, uint32_t size) {
		return self.getData(values, size);
	}
	TS_JSAPI uint32_t tsXml_addAttribute(Xml &self, const char *name) {
		return self.addAttribute(name);
	}
	TS_JSAPI bool tsXml_removeAttribute(Xml &self, const char *name) {
		return self.removeAttribute(name);
	}
	TS_JSAPI uint32_t tsXml_findAttribute(const Xml &self, const char *name) {
		return self.findAttribute(name);
	}
	TS_JSAPI bool tsXml_isAttribute(const Xml &self, const char *name) {
		return self.isAttribute(name);
	}
	TS_JSAPI void tsXml_removeAttributes(Xml &self) {
		self.removeAttributes();
	}
	TS_JSAPI uint32_t tsXml_getNumAttributes(const Xml &self) {
		return self.getNumAttributes();
	}
	TS_JSAPI String *tsXml_getAttributeName(const Xml &self, uint32_t index) {
		return new String(self.getAttributeName(index));
	}
	TS_JSAPI bool tsXml_setAttributes(Xml &self, const char *str) {
		return self.setAttributes(str);
	}
	TS_JSAPI void tsXml_setAttribute(Xml &self, uint32_t index, bool value) {
		self.setAttribute(index, value);
	}
	TS_JSAPI void tsXml_setAttribute_1(Xml &self, uint32_t index, const char *value) {
		self.setAttribute(index, value);
	}
	TS_JSAPI void tsXml_setAttribute_2(Xml &self, uint32_t index, const String &value) {
		self.setAttribute(index, value);
	}
	TS_JSAPI void tsXml_setAttribute_3(Xml &self, uint32_t index, int32_t value, uint32_t radix) {
		self.setAttribute(index, value, radix);
	}
	TS_JSAPI void tsXml_setAttribute_4(Xml &self, uint32_t index, uint32_t value, uint32_t radix) {
		self.setAttribute(index, value, radix);
	}
	TS_JSAPI void tsXml_setAttribute_5(Xml &self, uint32_t index, uint64_t value, uint32_t radix) {
		self.setAttribute(index, value, radix);
	}
	TS_JSAPI void tsXml_setAttribute_6(Xml &self, uint32_t index, float32_t value, uint32_t digits, bool compact, bool exponent) {
		self.setAttribute(index, value, digits, compact, exponent);
	}
	TS_JSAPI void tsXml_setAttribute_7(Xml &self, uint32_t index, float64_t value, uint32_t digits, bool compact, bool exponent) {
		self.setAttribute(index, value, digits, compact, exponent);
	}
	TS_JSAPI String *tsXml_getAttribute(const Xml &self, uint32_t index) {
		return new String(self.getAttribute(index));
	}
	TS_JSAPI int32_t tsXml_getAttributei32(const Xml &self, uint32_t index, uint32_t radix) {
		return self.getAttributei32(index, radix);
	}
	TS_JSAPI uint32_t tsXml_getAttributeu32(const Xml &self, uint32_t index, uint32_t radix) {
		return self.getAttributeu32(index, radix);
	}
	TS_JSAPI uint64_t tsXml_getAttributeu64(const Xml &self, uint32_t index, uint32_t radix) {
		return self.getAttributeu64(index, radix);
	}
	TS_JSAPI float32_t tsXml_getAttributef32(const Xml &self, uint32_t index) {
		return self.getAttributef32(index);
	}
	TS_JSAPI float64_t tsXml_getAttributef64(const Xml &self, uint32_t index) {
		return self.getAttributef64(index);
	}
	TS_JSAPI String *tsXml_getAttribute_1(const Xml &self, const char *name, const String &value) {
		return new String(self.getAttribute(name, value));
	}
	TS_JSAPI bool tsXml_getAttribute_2(const Xml &self, const char *name, bool value) {
		return self.getAttribute(name, value);
	}
	TS_JSAPI int32_t tsXml_getAttribute_3(const Xml &self, const char *name, int32_t value, uint32_t radix) {
		return self.getAttribute(name, value, radix);
	}
	TS_JSAPI uint32_t tsXml_getAttribute_4(const Xml &self, const char *name, uint32_t value, uint32_t radix) {
		return self.getAttribute(name, value, radix);
	}
	TS_JSAPI uint64_t tsXml_getAttribute_5(const Xml &self, const char *name, uint64_t value, uint32_t radix) {
		return self.getAttribute(name, value, radix);
	}
	TS_JSAPI float32_t tsXml_getAttribute_6(const Xml &self, const char *name, float32_t value) {
		return self.getAttribute(name, value);
	}
	TS_JSAPI float64_t tsXml_getAttribute_7(const Xml &self, const char *name, float64_t value) {
		return self.getAttribute(name, value);
	}
	TS_JSAPI void tsXml_setAttribute_8(Xml &self, uint32_t index, const char **values, uint32_t size, const char *delimiter) {
		self.setAttribute(index, values, size, delimiter);
	}
	TS_JSAPI void tsXml_setAttribute_9(Xml &self, uint32_t index, const String *values, uint32_t size, const char *delimiter) {
		self.setAttribute(index, values, size, delimiter);
	}
	TS_JSAPI void tsXml_setAttribute_10(Xml &self, uint32_t index, const int32_t *values, uint32_t size, uint32_t radix) {
		self.setAttribute(index, values, size, radix);
	}
	TS_JSAPI void tsXml_setAttribute_11(Xml &self, uint32_t index, const uint32_t *values, uint32_t size, uint32_t radix) {
		self.setAttribute(index, values, size, radix);
	}
	TS_JSAPI void tsXml_setAttribute_12(Xml &self, uint32_t index, const float32_t *values, uint32_t size, uint32_t digits, bool compact, bool exponent) {
		self.setAttribute(index, values, size, digits, compact, exponent);
	}
	TS_JSAPI void tsXml_setAttribute_13(Xml &self, uint32_t index, const float64_t *values, uint32_t size, uint32_t digits, bool compact, bool exponent) {
		self.setAttribute(index, values, size, digits, compact, exponent);
	}
	TS_JSAPI uint32_t tsXml_getAttribute_8(const Xml &self, uint32_t index, String *values, uint32_t size, const char *delimiter) {
		return self.getAttribute(index, values, size, delimiter);
	}
	TS_JSAPI uint32_t tsXml_getAttribute_9(const Xml &self, uint32_t index, int32_t *values, uint32_t size, uint32_t radix) {
		return self.getAttribute(index, values, size, radix);
	}
	TS_JSAPI uint32_t tsXml_getAttribute_10(const Xml &self, uint32_t index, uint32_t *values, uint32_t size, uint32_t radix) {
		return self.getAttribute(index, values, size, radix);
	}
	TS_JSAPI uint32_t tsXml_getAttribute_11(const Xml &self, uint32_t index, float32_t *values, uint32_t size) {
		return self.getAttribute(index, values, size);
	}
	TS_JSAPI uint32_t tsXml_getAttribute_12(const Xml &self, uint32_t index, float64_t *values, uint32_t size) {
		return self.getAttribute(index, values, size);
	}
	
	// Tellusim::Buffer
	TS_JSAPI Buffer *tsBuffer_new() {
		return new Buffer();
	}
	TS_JSAPI void tsBuffer_delete(Buffer *self) {
		delete self;
	}
	TS_JSAPI bool tsBuffer_equalPtr(const Buffer &self, const Buffer &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Buffer *tsBuffer_clonePtr(const Buffer &self) {
		return new Buffer(self.clonePtr());
	}
	TS_JSAPI void tsBuffer_clearPtr(Buffer &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsBuffer_destroyPtr(Buffer &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsBuffer_acquirePtr(Buffer &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsBuffer_unacquirePtr(Buffer &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsBuffer_isValidPtr(const Buffer &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsBuffer_isOwnerPtr(const Buffer &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsBuffer_isConstPtr(const Buffer &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsBuffer_getCountPtr(const Buffer &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsBuffer_getInternalPtr(const Buffer &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI uint32_t tsBuffer_getPlatform(const Buffer &self) {
		return self.getPlatform();
	}
	TS_JSAPI const char* tsBuffer_getPlatformName(const Buffer &self) {
		return self.getPlatformName();
	}
	TS_JSAPI uint32_t tsBuffer_getIndex(const Buffer &self) {
		return self.getIndex();
	}
	TS_JSAPI void tsBuffer_clear(Buffer &self) {
		self.clear();
	}
	TS_JSAPI bool tsBuffer_isCreated(const Buffer &self) {
		return self.isCreated();
	}
	TS_JSAPI void tsBuffer_setName(Buffer &self, const char *name) {
		self.setName(name);
	}
	TS_JSAPI String *tsBuffer_getName(const Buffer &self) {
		return new String(self.getName());
	}
	TS_JSAPI bool tsBuffer_create(Buffer &self, uint32_t flags, size_t size, uint32_t format) {
		return self.create((Buffer::Flags)flags, size, (Format)format);
	}
	TS_JSAPI bool tsBuffer_isMapped(const Buffer &self) {
		return self.isMapped();
	}
	TS_JSAPI uint32_t tsBuffer_getFlags(const Buffer &self) {
		return self.getFlags();
	}
	TS_JSAPI bool tsBuffer_hasFlag(const Buffer &self, uint32_t flags) {
		return self.hasFlag((Buffer::Flags)flags);
	}
	TS_JSAPI bool tsBuffer_hasFlags(const Buffer &self, uint32_t flags) {
		return self.hasFlags((Buffer::Flags)flags);
	}
	TS_JSAPI String *tsBuffer_getFlagsName(const Buffer &self) {
		return new String(self.getFlagsName());
	}
	TS_JSAPI uint32_t tsBuffer_getFormat(const Buffer &self) {
		return self.getFormat();
	}
	TS_JSAPI const char* tsBuffer_getFormatName(const Buffer &self) {
		return self.getFormatName();
	}
	TS_JSAPI uint32_t tsBuffer_getComponents(const Buffer &self) {
		return self.getComponents();
	}
	TS_JSAPI uint32_t tsBuffer_getPixelSize(const Buffer &self) {
		return self.getPixelSize();
	}
	TS_JSAPI size_t tsBuffer_getSize(Buffer &self) {
		return self.getSize();
	}
	TS_JSAPI size_t tsBuffer_getPageSize(Buffer &self) {
		return self.getPageSize();
	}
	TS_JSAPI String *tsBuffer_getDescription(const Buffer &self) {
		return new String(self.getDescription());
	}
	
	// Tellusim::BufferTable
	TS_JSAPI BufferTable *tsBufferTable_new() {
		return new BufferTable();
	}
	TS_JSAPI void tsBufferTable_delete(BufferTable *self) {
		delete self;
	}
	TS_JSAPI bool tsBufferTable_equalPtr(const BufferTable &self, const BufferTable &ptr) {
		return (self == ptr);
	}
	TS_JSAPI BufferTable *tsBufferTable_clonePtr(const BufferTable &self) {
		return new BufferTable(self.clonePtr());
	}
	TS_JSAPI void tsBufferTable_clearPtr(BufferTable &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsBufferTable_destroyPtr(BufferTable &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsBufferTable_acquirePtr(BufferTable &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsBufferTable_unacquirePtr(BufferTable &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsBufferTable_isValidPtr(const BufferTable &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsBufferTable_isOwnerPtr(const BufferTable &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsBufferTable_isConstPtr(const BufferTable &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsBufferTable_getCountPtr(const BufferTable &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsBufferTable_getInternalPtr(const BufferTable &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI uint32_t tsBufferTable_getPlatform(const BufferTable &self) {
		return self.getPlatform();
	}
	TS_JSAPI const char* tsBufferTable_getPlatformName(const BufferTable &self) {
		return self.getPlatformName();
	}
	TS_JSAPI uint32_t tsBufferTable_getIndex(const BufferTable &self) {
		return self.getIndex();
	}
	TS_JSAPI void tsBufferTable_clear(BufferTable &self) {
		self.clear();
	}
	TS_JSAPI bool tsBufferTable_isCreated(const BufferTable &self) {
		return self.isCreated();
	}
	TS_JSAPI void tsBufferTable_setName(BufferTable &self, const char *name) {
		self.setName(name);
	}
	TS_JSAPI String *tsBufferTable_getName(const BufferTable &self) {
		return new String(self.getName());
	}
	TS_JSAPI bool tsBufferTable_create(BufferTable &self, uint32_t size) {
		return self.create(size);
	}
	TS_JSAPI uint32_t tsBufferTable_getSize(const BufferTable &self) {
		return self.getSize();
	}
	TS_JSAPI Buffer *tsBufferTable_get(const BufferTable &self, uint32_t index) {
		return new Buffer(self.get(index));
	}
	TS_JSAPI bool tsBufferTable_isOwner(const BufferTable &self, uint32_t index) {
		return self.isOwner(index);
	}
	TS_JSAPI size_t tsBufferTable_getMemory(const BufferTable &self) {
		return self.getMemory();
	}
	
	// Tellusim::GLESBuffer
	TS_JSAPI GLESBuffer *tsGLESBuffer_new() {
		return new GLESBuffer();
	}
	TS_JSAPI void tsGLESBuffer_delete(GLESBuffer *self) {
		delete self;
	}
	TS_JSAPI bool tsGLESBuffer_equalBufferPtr(const GLESBuffer &self, const Buffer &base) {
		return self.operator==(base);
	}
	TS_JSAPI GLESBuffer *tsGLESBuffer_castBufferPtr(const Buffer &self) {
		return new GLESBuffer(self);
	}
	TS_JSAPI Buffer *tsGLESBuffer_baseBufferPtr(const GLESBuffer &self) {
		return new Buffer(self.getBuffer());
	}
	TS_JSAPI bool tsGLESBuffer_create(GLESBuffer &self, uint32_t flags, uint32_t target, uint32_t buffer_id) {
		return self.create((Buffer::Flags)flags, target, buffer_id);
	}
	TS_JSAPI uint32_t tsGLESBuffer_getTarget(const GLESBuffer &self) {
		return self.getTarget();
	}
	TS_JSAPI uint32_t tsGLESBuffer_getBufferID(const GLESBuffer &self) {
		return self.getBufferID();
	}
	
	// Tellusim::Command::DrawArraysIndirect
	TS_JSAPI Command::DrawArraysIndirect *tsCommandDrawArraysIndirect_new() {
		return new Command::DrawArraysIndirect();
	}
	TS_JSAPI Command::DrawArraysIndirect *tsCommandDrawArraysIndirect_copy(const Command::DrawArraysIndirect &self) {
		return new Command::DrawArraysIndirect(self);
	}
	TS_JSAPI void tsCommandDrawArraysIndirect_delete(Command::DrawArraysIndirect *self) {
		delete self;
	}
	TS_JSAPI void tsCommandDrawArraysIndirect_set_num_vertices(Command::DrawArraysIndirect &self, uint32_t num_vertices) {
		self.num_vertices = num_vertices;
	}
	TS_JSAPI uint32_t tsCommandDrawArraysIndirect_get_num_vertices(const Command::DrawArraysIndirect &self) {
		return self.num_vertices;
	}
	TS_JSAPI void tsCommandDrawArraysIndirect_set_num_instances(Command::DrawArraysIndirect &self, uint32_t num_instances) {
		self.num_instances = num_instances;
	}
	TS_JSAPI uint32_t tsCommandDrawArraysIndirect_get_num_instances(const Command::DrawArraysIndirect &self) {
		return self.num_instances;
	}
	TS_JSAPI void tsCommandDrawArraysIndirect_set_base_vertex(Command::DrawArraysIndirect &self, uint32_t base_vertex) {
		self.base_vertex = base_vertex;
	}
	TS_JSAPI uint32_t tsCommandDrawArraysIndirect_get_base_vertex(const Command::DrawArraysIndirect &self) {
		return self.base_vertex;
	}
	TS_JSAPI void tsCommandDrawArraysIndirect_set_base_instance(Command::DrawArraysIndirect &self, uint32_t base_instance) {
		self.base_instance = base_instance;
	}
	TS_JSAPI uint32_t tsCommandDrawArraysIndirect_get_base_instance(const Command::DrawArraysIndirect &self) {
		return self.base_instance;
	}
	// Tellusim::Command::DrawElementsIndirect
	TS_JSAPI Command::DrawElementsIndirect *tsCommandDrawElementsIndirect_new() {
		return new Command::DrawElementsIndirect();
	}
	TS_JSAPI Command::DrawElementsIndirect *tsCommandDrawElementsIndirect_copy(const Command::DrawElementsIndirect &self) {
		return new Command::DrawElementsIndirect(self);
	}
	TS_JSAPI void tsCommandDrawElementsIndirect_delete(Command::DrawElementsIndirect *self) {
		delete self;
	}
	TS_JSAPI void tsCommandDrawElementsIndirect_set_num_indices(Command::DrawElementsIndirect &self, uint32_t num_indices) {
		self.num_indices = num_indices;
	}
	TS_JSAPI uint32_t tsCommandDrawElementsIndirect_get_num_indices(const Command::DrawElementsIndirect &self) {
		return self.num_indices;
	}
	TS_JSAPI void tsCommandDrawElementsIndirect_set_num_instances(Command::DrawElementsIndirect &self, uint32_t num_instances) {
		self.num_instances = num_instances;
	}
	TS_JSAPI uint32_t tsCommandDrawElementsIndirect_get_num_instances(const Command::DrawElementsIndirect &self) {
		return self.num_instances;
	}
	TS_JSAPI void tsCommandDrawElementsIndirect_set_base_index(Command::DrawElementsIndirect &self, uint32_t base_index) {
		self.base_index = base_index;
	}
	TS_JSAPI uint32_t tsCommandDrawElementsIndirect_get_base_index(const Command::DrawElementsIndirect &self) {
		return self.base_index;
	}
	TS_JSAPI void tsCommandDrawElementsIndirect_set_base_vertex(Command::DrawElementsIndirect &self, int32_t base_vertex) {
		self.base_vertex = base_vertex;
	}
	TS_JSAPI int32_t tsCommandDrawElementsIndirect_get_base_vertex(const Command::DrawElementsIndirect &self) {
		return self.base_vertex;
	}
	TS_JSAPI void tsCommandDrawElementsIndirect_set_base_instance(Command::DrawElementsIndirect &self, uint32_t base_instance) {
		self.base_instance = base_instance;
	}
	TS_JSAPI uint32_t tsCommandDrawElementsIndirect_get_base_instance(const Command::DrawElementsIndirect &self) {
		return self.base_instance;
	}
	// Tellusim::Command::DrawMeshIndirect
	TS_JSAPI Command::DrawMeshIndirect *tsCommandDrawMeshIndirect_new() {
		return new Command::DrawMeshIndirect();
	}
	TS_JSAPI Command::DrawMeshIndirect *tsCommandDrawMeshIndirect_copy(const Command::DrawMeshIndirect &self) {
		return new Command::DrawMeshIndirect(self);
	}
	TS_JSAPI void tsCommandDrawMeshIndirect_delete(Command::DrawMeshIndirect *self) {
		delete self;
	}
	TS_JSAPI void tsCommandDrawMeshIndirect_set_group_width(Command::DrawMeshIndirect &self, uint32_t group_width) {
		self.group_width = group_width;
	}
	TS_JSAPI uint32_t tsCommandDrawMeshIndirect_get_group_width(const Command::DrawMeshIndirect &self) {
		return self.group_width;
	}
	TS_JSAPI void tsCommandDrawMeshIndirect_set_group_height(Command::DrawMeshIndirect &self, uint32_t group_height) {
		self.group_height = group_height;
	}
	TS_JSAPI uint32_t tsCommandDrawMeshIndirect_get_group_height(const Command::DrawMeshIndirect &self) {
		return self.group_height;
	}
	TS_JSAPI void tsCommandDrawMeshIndirect_set_group_depth(Command::DrawMeshIndirect &self, uint32_t group_depth) {
		self.group_depth = group_depth;
	}
	TS_JSAPI uint32_t tsCommandDrawMeshIndirect_get_group_depth(const Command::DrawMeshIndirect &self) {
		return self.group_depth;
	}
	
	// Tellusim::Command
	TS_JSAPI Command *tsCommand_new() {
		return new Command();
	}
	TS_JSAPI void tsCommand_delete(Command *self) {
		delete self;
	}
	TS_JSAPI bool tsCommand_equalPtr(const Command &self, const Command &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Command *tsCommand_clonePtr(const Command &self) {
		return new Command(self.clonePtr());
	}
	TS_JSAPI void tsCommand_clearPtr(Command &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsCommand_destroyPtr(Command &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsCommand_acquirePtr(Command &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsCommand_unacquirePtr(Command &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsCommand_isValidPtr(const Command &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsCommand_isOwnerPtr(const Command &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsCommand_isConstPtr(const Command &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsCommand_getCountPtr(const Command &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsCommand_getInternalPtr(const Command &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI uint32_t tsCommand_getPlatform(const Command &self) {
		return self.getPlatform();
	}
	TS_JSAPI const char* tsCommand_getPlatformName(const Command &self) {
		return self.getPlatformName();
	}
	TS_JSAPI uint32_t tsCommand_getIndex(const Command &self) {
		return self.getIndex();
	}
	TS_JSAPI void tsCommand_setPipeline(Command &self, Pipeline &pipeline) {
		self.setPipeline(pipeline);
	}
	TS_JSAPI Pipeline *tsCommand_getPipeline(const Command &self) {
		return new Pipeline(self.getPipeline());
	}
	TS_JSAPI void tsCommand_setViewport(Command &self, uint32_t index, const Viewport &viewport) {
		self.setViewport(index, viewport);
	}
	TS_JSAPI void tsCommand_setViewports(Command &self, const Viewport *viewports, uint32_t num_viewports) {
		self.setViewports(viewports, num_viewports);
	}
	TS_JSAPI void tsCommand_setScissor(Command &self, uint32_t index, const Scissor &scissor) {
		self.setScissor(index, scissor);
	}
	TS_JSAPI void tsCommand_setScissors(Command &self, const Scissor *scissors, uint32_t num_scissors) {
		self.setScissors(scissors, num_scissors);
	}
	TS_JSAPI void tsCommand_setSampler(Command &self, uint32_t index, Sampler &sampler) {
		self.setSampler(index, sampler);
	}
	TS_JSAPI void tsCommand_setSamplers(Command &self, uint32_t index, Array<Sampler> &samplers) {
		self.setSamplers(index, samplers);
	}
	TS_JSAPI void tsCommand_setTexture(Command &self, uint32_t index, Texture &texture) {
		self.setTexture(index, texture);
	}
	TS_JSAPI void tsCommand_setTexture_1(Command &self, uint32_t index, Texture &texture, const Slice &slice) {
		self.setTexture(index, texture, slice);
	}
	TS_JSAPI void tsCommand_setTextures(Command &self, uint32_t index, Array<Texture> &textures) {
		self.setTextures(index, textures);
	}
	TS_JSAPI void tsCommand_setSurfaceTexture(Command &self, uint32_t index, Texture &texture) {
		self.setSurfaceTexture(index, texture);
	}
	TS_JSAPI void tsCommand_setSurfaceTexture_1(Command &self, uint32_t index, Texture &texture, const Slice &slice, uint32_t format) {
		self.setSurfaceTexture(index, texture, slice, (Format)format);
	}
	TS_JSAPI void tsCommand_setSurfaceTextures(Command &self, uint32_t index, Array<Texture> &textures) {
		self.setSurfaceTextures(index, textures);
	}
	TS_JSAPI void* tsCommand_getUniformData(Command &self, uint32_t index, size_t size) {
		return self.getUniformData(index, size);
	}
	TS_JSAPI void tsCommand_setUniformData(Command &self, uint32_t index, const void *src, size_t size) {
		self.setUniformData(index, src, size);
	}
	TS_JSAPI void tsCommand_setUniformBuffer(Command &self, uint32_t index, Buffer &buffer, size_t offset, size_t size) {
		self.setUniformBuffer(index, buffer, offset, size);
	}
	TS_JSAPI void tsCommand_setUniformOffset(Command &self, uint32_t index, size_t offset, bool relative) {
		self.setUniformOffset(index, offset, relative);
	}
	TS_JSAPI void tsCommand_setUniformBuffers(Command &self, uint32_t index, Array<Buffer> &buffers) {
		self.setUniformBuffers(index, buffers);
	}
	TS_JSAPI void tsCommand_setUniformBuffers_1(Command &self, uint32_t index, Array<Buffer> &buffers, Array<size_t> &offsets) {
		self.setUniformBuffers(index, buffers, offsets);
	}
	TS_JSAPI void* tsCommand_getStorageData(Command &self, uint32_t index, size_t size) {
		return self.getStorageData(index, size);
	}
	TS_JSAPI void tsCommand_setStorageData(Command &self, uint32_t index, const void *src, size_t size) {
		self.setStorageData(index, src, size);
	}
	TS_JSAPI void tsCommand_setStorageBuffer(Command &self, uint32_t index, Buffer &buffer, size_t offset, size_t size) {
		self.setStorageBuffer(index, buffer, offset, size);
	}
	TS_JSAPI void tsCommand_setStorageOffset(Command &self, uint32_t index, size_t offset, bool relative) {
		self.setStorageOffset(index, offset, relative);
	}
	TS_JSAPI void tsCommand_setStorageBuffers(Command &self, uint32_t index, Array<Buffer> &buffers) {
		self.setStorageBuffers(index, buffers);
	}
	TS_JSAPI void tsCommand_setStorageBuffers_1(Command &self, uint32_t index, Array<Buffer> &buffers, Array<size_t> &offsets) {
		self.setStorageBuffers(index, buffers, offsets);
	}
	TS_JSAPI void tsCommand_setTracing(Command &self, uint32_t index, Tracing &tracing) {
		self.setTracing(index, tracing);
	}
	TS_JSAPI void tsCommand_setTracings(Command &self, uint32_t index, Array<Tracing> &tracings) {
		self.setTracings(index, tracings);
	}
	TS_JSAPI void tsCommand_setTexelBuffer(Command &self, uint32_t index, Buffer &buffer) {
		self.setTexelBuffer(index, buffer);
	}
	TS_JSAPI void tsCommand_setTexelBuffers(Command &self, uint32_t index, Array<Buffer> &buffers) {
		self.setTexelBuffers(index, buffers);
	}
	TS_JSAPI void tsCommand_setTextureTable(Command &self, uint32_t index, TextureTable &table) {
		self.setTextureTable(index, table);
	}
	TS_JSAPI void tsCommand_setTextureTables(Command &self, uint32_t index, Array<TextureTable> &tables) {
		self.setTextureTables(index, tables);
	}
	TS_JSAPI void tsCommand_setStorageTable(Command &self, uint32_t index, BufferTable &table) {
		self.setStorageTable(index, table);
	}
	TS_JSAPI void tsCommand_setStorageTables(Command &self, uint32_t index, Array<BufferTable> &tables) {
		self.setStorageTables(index, tables);
	}
	TS_JSAPI void* tsCommand_getVertexData(Command &self, uint32_t index, size_t size) {
		return self.getVertexData(index, size);
	}
	TS_JSAPI void tsCommand_setVertexData(Command &self, uint32_t index, const void *src, size_t size) {
		self.setVertexData(index, src, size);
	}
	TS_JSAPI void tsCommand_setVertexBuffer(Command &self, uint32_t index, Buffer &buffer, size_t offset) {
		self.setVertexBuffer(index, buffer, offset);
	}
	TS_JSAPI void tsCommand_setVertexOffset(Command &self, uint32_t index, size_t offset, bool relative) {
		self.setVertexOffset(index, offset, relative);
	}
	TS_JSAPI void tsCommand_setVertexBuffers(Command &self, uint32_t index, Array<Buffer> &buffers) {
		self.setVertexBuffers(index, buffers);
	}
	TS_JSAPI void tsCommand_setVertexBuffers_1(Command &self, uint32_t index, Array<Buffer> &buffers, Array<size_t> &offsets) {
		self.setVertexBuffers(index, buffers, offsets);
	}
	TS_JSAPI void* tsCommand_getIndexData(Command &self, uint32_t format, size_t size) {
		return self.getIndexData((Format)format, size);
	}
	TS_JSAPI void tsCommand_setIndexData(Command &self, uint32_t format, const void *src, size_t size) {
		self.setIndexData((Format)format, src, size);
	}
	TS_JSAPI void tsCommand_setIndexBuffer(Command &self, uint32_t format, Buffer &buffer, size_t offset) {
		self.setIndexBuffer((Format)format, buffer, offset);
	}
	TS_JSAPI void tsCommand_setIndexOffset(Command &self, size_t offset, bool relative) {
		self.setIndexOffset(offset, relative);
	}
	TS_JSAPI void* tsCommand_getIndirectData(Command &self, size_t size) {
		return self.getIndirectData(size);
	}
	TS_JSAPI void tsCommand_setIndirectData(Command &self, const void *src, size_t size) {
		self.setIndirectData(src, size);
	}
	TS_JSAPI void tsCommand_setIndirectBuffer(Command &self, Buffer &buffer, size_t offset) {
		self.setIndirectBuffer(buffer, offset);
	}
	TS_JSAPI void tsCommand_setIndirectOffset(Command &self, size_t offset, bool relative) {
		self.setIndirectOffset(offset, relative);
	}
	TS_JSAPI void tsCommand_setBlendColor(Command &self, const Color &color) {
		self.setBlendColor(color);
	}
	TS_JSAPI void tsCommand_setBlendColor_1(Command &self, float32_t r, float32_t g, float32_t b, float32_t a) {
		self.setBlendColor(r, g, b, a);
	}
	TS_JSAPI void tsCommand_setStencilRef(Command &self, uint32_t ref) {
		self.setStencilRef(ref);
	}
	TS_JSAPI void tsCommand_drawArrays(Command &self, uint32_t num_vertices, uint32_t base_vertex) {
		self.drawArrays(num_vertices, base_vertex);
	}
	TS_JSAPI void tsCommand_drawArraysInstanced(Command &self, uint32_t num_vertices, uint32_t base_vertex, uint32_t num_instances, uint32_t base_instance) {
		self.drawArraysInstanced(num_vertices, base_vertex, num_instances, base_instance);
	}
	TS_JSAPI void tsCommand_drawArraysIndirect(Command &self, uint32_t num_draws, size_t stride) {
		self.drawArraysIndirect(num_draws, stride);
	}
	TS_JSAPI void tsCommand_drawArraysIndirect_1(Command &self, Buffer &buffer, size_t offset, uint32_t num_draws, size_t stride) {
		self.drawArraysIndirect(buffer, offset, num_draws, stride);
	}
	TS_JSAPI void tsCommand_drawElements(Command &self, uint32_t num_indices, uint32_t base_index, int32_t base_vertex) {
		self.drawElements(num_indices, base_index, base_vertex);
	}
	TS_JSAPI void tsCommand_drawElementsInstanced(Command &self, uint32_t num_indices, uint32_t base_index, uint32_t num_instances) {
		self.drawElementsInstanced(num_indices, base_index, num_instances);
	}
	TS_JSAPI void tsCommand_drawElementsInstanced_1(Command &self, uint32_t num_indices, uint32_t base_index, int32_t base_vertex, uint32_t num_instances, uint32_t base_instance) {
		self.drawElementsInstanced(num_indices, base_index, base_vertex, num_instances, base_instance);
	}
	TS_JSAPI void tsCommand_drawElementsIndirect(Command &self, uint32_t num_draws, size_t stride) {
		self.drawElementsIndirect(num_draws, stride);
	}
	TS_JSAPI void tsCommand_drawElementsIndirect_1(Command &self, Buffer &buffer, size_t offset, uint32_t num_draws, size_t stride) {
		self.drawElementsIndirect(buffer, offset, num_draws, stride);
	}
	TS_JSAPI void tsCommand_drawMesh(Command &self, uint32_t width, uint32_t height, uint32_t depth) {
		self.drawMesh(width, height, depth);
	}
	TS_JSAPI void tsCommand_drawMeshIndirect(Command &self, uint32_t num_draws, size_t stride) {
		self.drawMeshIndirect(num_draws, stride);
	}
	TS_JSAPI void tsCommand_drawMeshIndirect_1(Command &self, Buffer &buffer, size_t offset, uint32_t num_draws, size_t stride) {
		self.drawMeshIndirect(buffer, offset, num_draws, stride);
	}
	TS_JSAPI void tsCommand_beginConditional(Command &self, Buffer &buffer, size_t offset) {
		self.beginConditional(buffer, offset);
	}
	TS_JSAPI void tsCommand_endConditional(Command &self) {
		self.endConditional();
	}
	TS_JSAPI bool tsCommand_beginQuery(Command &self, Query &query) {
		return self.beginQuery(query);
	}
	TS_JSAPI void tsCommand_endQuery(Command &self, Query &query) {
		self.endQuery(query);
	}
	
	// Tellusim::Compute::DispatchIndirect
	TS_JSAPI Compute::DispatchIndirect *tsComputeDispatchIndirect_new() {
		return new Compute::DispatchIndirect();
	}
	TS_JSAPI Compute::DispatchIndirect *tsComputeDispatchIndirect_copy(const Compute::DispatchIndirect &self) {
		return new Compute::DispatchIndirect(self);
	}
	TS_JSAPI void tsComputeDispatchIndirect_delete(Compute::DispatchIndirect *self) {
		delete self;
	}
	TS_JSAPI void tsComputeDispatchIndirect_set_group_width(Compute::DispatchIndirect &self, uint32_t group_width) {
		self.group_width = group_width;
	}
	TS_JSAPI uint32_t tsComputeDispatchIndirect_get_group_width(const Compute::DispatchIndirect &self) {
		return self.group_width;
	}
	TS_JSAPI void tsComputeDispatchIndirect_set_group_height(Compute::DispatchIndirect &self, uint32_t group_height) {
		self.group_height = group_height;
	}
	TS_JSAPI uint32_t tsComputeDispatchIndirect_get_group_height(const Compute::DispatchIndirect &self) {
		return self.group_height;
	}
	TS_JSAPI void tsComputeDispatchIndirect_set_group_depth(Compute::DispatchIndirect &self, uint32_t group_depth) {
		self.group_depth = group_depth;
	}
	TS_JSAPI uint32_t tsComputeDispatchIndirect_get_group_depth(const Compute::DispatchIndirect &self) {
		return self.group_depth;
	}
	
	// Tellusim::Compute
	TS_JSAPI Compute *tsCompute_new() {
		return new Compute();
	}
	TS_JSAPI void tsCompute_delete(Compute *self) {
		delete self;
	}
	TS_JSAPI bool tsCompute_equalPtr(const Compute &self, const Compute &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Compute *tsCompute_clonePtr(const Compute &self) {
		return new Compute(self.clonePtr());
	}
	TS_JSAPI void tsCompute_clearPtr(Compute &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsCompute_destroyPtr(Compute &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsCompute_acquirePtr(Compute &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsCompute_unacquirePtr(Compute &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsCompute_isValidPtr(const Compute &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsCompute_isOwnerPtr(const Compute &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsCompute_isConstPtr(const Compute &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsCompute_getCountPtr(const Compute &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsCompute_getInternalPtr(const Compute &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI uint32_t tsCompute_getPlatform(const Compute &self) {
		return self.getPlatform();
	}
	TS_JSAPI const char* tsCompute_getPlatformName(const Compute &self) {
		return self.getPlatformName();
	}
	TS_JSAPI uint32_t tsCompute_getIndex(const Compute &self) {
		return self.getIndex();
	}
	TS_JSAPI void tsCompute_setKernel(Compute &self, Kernel &kernel) {
		self.setKernel(kernel);
	}
	TS_JSAPI Kernel *tsCompute_getKernel(const Compute &self) {
		return new Kernel(self.getKernel());
	}
	TS_JSAPI void tsCompute_setTraversal(Compute &self, Traversal &traversal) {
		self.setTraversal(traversal);
	}
	TS_JSAPI Traversal *tsCompute_getTraversal(const Compute &self) {
		return new Traversal(self.getTraversal());
	}
	TS_JSAPI void tsCompute_setSampler(Compute &self, uint32_t index, Sampler &sampler) {
		self.setSampler(index, sampler);
	}
	TS_JSAPI void tsCompute_setSamplers(Compute &self, uint32_t index, Array<Sampler> &samplers) {
		self.setSamplers(index, samplers);
	}
	TS_JSAPI void tsCompute_setTexture(Compute &self, uint32_t index, Texture &texture) {
		self.setTexture(index, texture);
	}
	TS_JSAPI void tsCompute_setTexture_1(Compute &self, uint32_t index, Texture &texture, const Slice &slice) {
		self.setTexture(index, texture, slice);
	}
	TS_JSAPI void tsCompute_setTextures(Compute &self, uint32_t index, Array<Texture> &textures) {
		self.setTextures(index, textures);
	}
	TS_JSAPI void tsCompute_setSurfaceTexture(Compute &self, uint32_t index, Texture &texture) {
		self.setSurfaceTexture(index, texture);
	}
	TS_JSAPI void tsCompute_setSurfaceTexture_1(Compute &self, uint32_t index, Texture &texture, const Slice &slice, uint32_t format) {
		self.setSurfaceTexture(index, texture, slice, (Format)format);
	}
	TS_JSAPI void tsCompute_setSurfaceTextures(Compute &self, uint32_t index, Array<Texture> &textures) {
		self.setSurfaceTextures(index, textures);
	}
	TS_JSAPI void* tsCompute_getUniformData(Compute &self, uint32_t index, size_t size) {
		return self.getUniformData(index, size);
	}
	TS_JSAPI void tsCompute_setUniformData(Compute &self, uint32_t index, const void *src, size_t size) {
		self.setUniformData(index, src, size);
	}
	TS_JSAPI void tsCompute_setUniformBuffer(Compute &self, uint32_t index, Buffer &buffer, size_t offset, size_t size) {
		self.setUniformBuffer(index, buffer, offset, size);
	}
	TS_JSAPI void tsCompute_setUniformOffset(Compute &self, uint32_t index, size_t offset, bool relative) {
		self.setUniformOffset(index, offset, relative);
	}
	TS_JSAPI void tsCompute_setUniformBuffers(Compute &self, uint32_t index, Array<Buffer> &buffers) {
		self.setUniformBuffers(index, buffers);
	}
	TS_JSAPI void tsCompute_setUniformBuffers_1(Compute &self, uint32_t index, Array<Buffer> &buffers, Array<size_t> &offsets) {
		self.setUniformBuffers(index, buffers, offsets);
	}
	TS_JSAPI void* tsCompute_getStorageData(Compute &self, uint32_t index, size_t size) {
		return self.getStorageData(index, size);
	}
	TS_JSAPI void tsCompute_setStorageData(Compute &self, uint32_t index, const void *src, size_t size) {
		self.setStorageData(index, src, size);
	}
	TS_JSAPI void tsCompute_setStorageBuffer(Compute &self, uint32_t index, Buffer &buffer, size_t offset, size_t size) {
		self.setStorageBuffer(index, buffer, offset, size);
	}
	TS_JSAPI void tsCompute_setStorageOffset(Compute &self, uint32_t index, size_t offset, bool relative) {
		self.setStorageOffset(index, offset, relative);
	}
	TS_JSAPI void tsCompute_setStorageBuffers(Compute &self, uint32_t index, Array<Buffer> &buffers) {
		self.setStorageBuffers(index, buffers);
	}
	TS_JSAPI void tsCompute_setStorageBuffers_1(Compute &self, uint32_t index, Array<Buffer> &buffers, Array<size_t> &offsets) {
		self.setStorageBuffers(index, buffers, offsets);
	}
	TS_JSAPI void tsCompute_setTracing(Compute &self, uint32_t index, Tracing &tracing) {
		self.setTracing(index, tracing);
	}
	TS_JSAPI void tsCompute_setTracings(Compute &self, uint32_t index, Array<Tracing> &tracings) {
		self.setTracings(index, tracings);
	}
	TS_JSAPI void tsCompute_setTexelBuffer(Compute &self, uint32_t index, Buffer &buffer) {
		self.setTexelBuffer(index, buffer);
	}
	TS_JSAPI void tsCompute_setTexelBuffers(Compute &self, uint32_t index, Array<Buffer> &buffers) {
		self.setTexelBuffers(index, buffers);
	}
	TS_JSAPI void tsCompute_setTextureTable(Compute &self, uint32_t index, TextureTable &table) {
		self.setTextureTable(index, table);
	}
	TS_JSAPI void tsCompute_setTextureTables(Compute &self, uint32_t index, Array<TextureTable> &tables) {
		self.setTextureTables(index, tables);
	}
	TS_JSAPI void tsCompute_setStorageTable(Compute &self, uint32_t index, BufferTable &table) {
		self.setStorageTable(index, table);
	}
	TS_JSAPI void tsCompute_setStorageTables(Compute &self, uint32_t index, Array<BufferTable> &tables) {
		self.setStorageTables(index, tables);
	}
	TS_JSAPI void* tsCompute_getIndirectData(Compute &self, size_t size) {
		return self.getIndirectData(size);
	}
	TS_JSAPI void tsCompute_setIndirectData(Compute &self, const void *src, size_t size) {
		self.setIndirectData(src, size);
	}
	TS_JSAPI void tsCompute_setIndirectBuffer(Compute &self, Buffer &buffer, size_t offset) {
		self.setIndirectBuffer(buffer, offset);
	}
	TS_JSAPI void tsCompute_setIndirectOffset(Compute &self, size_t offset, bool relative) {
		self.setIndirectOffset(offset, relative);
	}
	TS_JSAPI void tsCompute_dispatch(Compute &self, uint32_t width, uint32_t height, uint32_t depth) {
		self.dispatch(width, height, depth);
	}
	TS_JSAPI void tsCompute_dispatch_1(Compute &self, const Texture &texture) {
		self.dispatch(texture);
	}
	TS_JSAPI void tsCompute_dispatch_2(Compute &self, const Size &size) {
		self.dispatch(size);
	}
	TS_JSAPI void tsCompute_dispatchIndirect(Compute &self) {
		self.dispatchIndirect();
	}
	TS_JSAPI bool tsCompute_setBuffer(Compute &self, Buffer &buffer, size_t offset, const void *src, size_t size) {
		return self.setBuffer(buffer, offset, src, size);
	}
	TS_JSAPI bool tsCompute_setBuffer_1(Compute &self, Buffer &buffer, const void *src, size_t size) {
		return self.setBuffer(buffer, src, size);
	}
	TS_JSAPI bool tsCompute_setBuffer_2(Compute &self, Buffer &buffer, const void *src) {
		return self.setBuffer(buffer, src);
	}
	TS_JSAPI bool tsCompute_copyBuffer(Compute &self, Buffer &buffer, size_t dest_offset, Buffer &src, size_t src_offset, size_t size) {
		return self.copyBuffer(buffer, dest_offset, src, src_offset, size);
	}
	TS_JSAPI bool tsCompute_copyBuffer_1(Compute &self, Buffer &buffer, size_t dest_offset, Buffer &src, size_t size) {
		return self.copyBuffer(buffer, dest_offset, src, size);
	}
	TS_JSAPI bool tsCompute_copyBuffer_2(Compute &self, Buffer &buffer, Buffer &src, size_t size) {
		return self.copyBuffer(buffer, src, size);
	}
	TS_JSAPI bool tsCompute_copyBuffer_3(Compute &self, Buffer &buffer, Buffer &src) {
		return self.copyBuffer(buffer, src);
	}
	TS_JSAPI bool tsCompute_clearBuffer(Compute &self, Buffer &buffer, uint32_t format, size_t offset, const void *src, size_t size) {
		return self.clearBuffer(buffer, (Format)format, offset, src, size);
	}
	TS_JSAPI bool tsCompute_clearBuffer_1(Compute &self, Buffer &buffer, uint32_t format, const void *src, size_t size) {
		return self.clearBuffer(buffer, (Format)format, src, size);
	}
	TS_JSAPI bool tsCompute_clearBuffer_2(Compute &self, Buffer &buffer, uint32_t format, const void *src) {
		return self.clearBuffer(buffer, (Format)format, src);
	}
	TS_JSAPI bool tsCompute_clearBuffer_3(Compute &self, Buffer &buffer) {
		return self.clearBuffer(buffer);
	}
	TS_JSAPI bool tsCompute_setTexture_2(Compute &self, Texture &texture, const Origin &dest_origin, const Slice &dest_slice, const Image &image, const Slice &src_slice) {
		return self.setTexture(texture, dest_origin, dest_slice, image, src_slice);
	}
	TS_JSAPI bool tsCompute_setTexture_3(Compute &self, Texture &texture, const Origin &dest_origin, const Image &image) {
		return self.setTexture(texture, dest_origin, image);
	}
	TS_JSAPI bool tsCompute_setTexture_4(Compute &self, Texture &texture, const Slice &dest_slice, const Image &image) {
		return self.setTexture(texture, dest_slice, image);
	}
	TS_JSAPI bool tsCompute_setTexture_5(Compute &self, Texture &texture, const Image &image) {
		return self.setTexture(texture, image);
	}
	TS_JSAPI bool tsCompute_copyTexture(Compute &self, Texture &texture, const Origin &dest_origin, const Slice &dest_slice, Texture &src, const Region &src_region, const Slice &src_slice) {
		return self.copyTexture(texture, dest_origin, dest_slice, src, src_region, src_slice);
	}
	TS_JSAPI bool tsCompute_copyTexture_1(Compute &self, Texture &texture, const Origin &dest_origin, Texture &src, const Region &src_region) {
		return self.copyTexture(texture, dest_origin, src, src_region);
	}
	TS_JSAPI bool tsCompute_copyTexture_2(Compute &self, Texture &texture, const Slice &dest_slice, Texture &src, const Slice &src_slice) {
		return self.copyTexture(texture, dest_slice, src, src_slice);
	}
	TS_JSAPI bool tsCompute_copyTexture_3(Compute &self, Texture &texture, Texture &src) {
		return self.copyTexture(texture, src);
	}
	TS_JSAPI bool tsCompute_clearTexture(Compute &self, Texture &texture, const Region &region, const Slice &slice, const void *src) {
		return self.clearTexture(texture, region, slice, src);
	}
	TS_JSAPI bool tsCompute_clearTexture_1(Compute &self, Texture &texture, const Region &region, const void *src) {
		return self.clearTexture(texture, region, src);
	}
	TS_JSAPI bool tsCompute_clearTexture_2(Compute &self, Texture &texture, const Slice &slice, const void *src) {
		return self.clearTexture(texture, slice, src);
	}
	TS_JSAPI bool tsCompute_clearTexture_3(Compute &self, Texture &texture, const void *src) {
		return self.clearTexture(texture, src);
	}
	TS_JSAPI void tsCompute_barrier(Compute &self, Texture &texture) {
		self.barrier(texture);
	}
	TS_JSAPI void tsCompute_barrier_1(Compute &self, Buffer &buffer) {
		self.barrier(buffer);
	}
	TS_JSAPI void tsCompute_barrier_2(Compute &self, Array<Texture> &textures) {
		self.barrier(textures);
	}
	TS_JSAPI void tsCompute_barrier_3(Compute &self, Array<Buffer> &buffers) {
		self.barrier(buffers);
	}
	TS_JSAPI void tsCompute_beginConditional(Compute &self, Buffer &buffer, size_t offset) {
		self.beginConditional(buffer, offset);
	}
	TS_JSAPI void tsCompute_endConditional(Compute &self) {
		self.endConditional();
	}
	TS_JSAPI bool tsCompute_beginQuery(Compute &self, Query &query) {
		return self.beginQuery(query);
	}
	TS_JSAPI void tsCompute_endQuery(Compute &self, Query &query) {
		self.endQuery(query);
	}
	
	// Tellusim::Context
	TS_JSAPI Context *tsContext_new() {
		return new Context();
	}
	TS_JSAPI Context *tsContext_new_1(uint32_t platform, uint32_t index) {
		return new Context((Platform)platform, index);
	}
	TS_JSAPI void tsContext_delete(Context *self) {
		delete self;
	}
	TS_JSAPI bool tsContext_equalPtr(const Context &self, const Context &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Context *tsContext_clonePtr(const Context &self) {
		return new Context(self.clonePtr());
	}
	TS_JSAPI void tsContext_clearPtr(Context &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsContext_destroyPtr(Context &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsContext_acquirePtr(Context &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsContext_unacquirePtr(Context &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsContext_isValidPtr(const Context &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsContext_isOwnerPtr(const Context &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsContext_isConstPtr(const Context &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsContext_getCountPtr(const Context &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsContext_getInternalPtr(const Context &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI uint32_t tsContext_getPlatform(const Context &self) {
		return self.getPlatform();
	}
	TS_JSAPI const char* tsContext_getPlatformName(const Context &self) {
		return self.getPlatformName();
	}
	TS_JSAPI uint32_t tsContext_getIndex(const Context &self) {
		return self.getIndex();
	}
	TS_JSAPI bool tsContext_isCreated(const Context &self) {
		return self.isCreated();
	}
	TS_JSAPI bool tsContext_create(Context &self) {
		return self.create();
	}
	TS_JSAPI bool tsContext_flush(Context &self) {
		return self.flush();
	}
	TS_JSAPI bool tsContext_finish(Context &self) {
		return self.finish();
	}
	
	// Tellusim::GLESContext
	TS_JSAPI GLESContext *tsGLESContext_new(uint32_t index) {
		return new GLESContext(index);
	}
	TS_JSAPI void tsGLESContext_delete(GLESContext *self) {
		delete self;
	}
	TS_JSAPI bool tsGLESContext_equalContextPtr(const GLESContext &self, const Context &base) {
		return self.operator==(base);
	}
	TS_JSAPI GLESContext *tsGLESContext_castContextPtr(const Context &self) {
		return new GLESContext(self);
	}
	TS_JSAPI Context *tsGLESContext_baseContextPtr(const GLESContext &self) {
		return new Context(self.getContext());
	}
	TS_JSAPI bool tsGLESContext_create(GLESContext &self, void *context) {
		return self.create(context);
	}
	TS_JSAPI void* tsGLESContext_getGLESDisplay(const GLESContext &self) {
		return self.getGLESDisplay();
	}
	TS_JSAPI void* tsGLESContext_getGLESConfig(const GLESContext &self) {
		return self.getGLESConfig();
	}
	TS_JSAPI void* tsGLESContext_getGLESContext(const GLESContext &self) {
		return self.getGLESContext();
	}
	TS_JSAPI String *tsGLESContext_getExtensions() {
		return new String(GLESContext::getExtensions());
	}
	TS_JSAPI bool tsGLESContext_checkExtension(const char *name) {
		return GLESContext::checkExtension(name);
	}
	TS_JSAPI void* tsGLESContext_getProcAddress(const char *name) {
		return GLESContext::getProcAddress(name);
	}
	TS_JSAPI bool tsGLESContext_error(uint32_t result) {
		return GLESContext::error(result);
	}
	TS_JSAPI bool tsGLESContext_check() {
		return GLESContext::check();
	}
	
	// Tellusim::WGContext
	TS_JSAPI WGContext *tsWGContext_new(uint32_t index) {
		return new WGContext(index);
	}
	TS_JSAPI void tsWGContext_delete(WGContext *self) {
		delete self;
	}
	TS_JSAPI bool tsWGContext_equalContextPtr(const WGContext &self, const Context &base) {
		return self.operator==(base);
	}
	TS_JSAPI WGContext *tsWGContext_castContextPtr(const Context &self) {
		return new WGContext(self);
	}
	TS_JSAPI Context *tsWGContext_baseContextPtr(const WGContext &self) {
		return new Context(self.getContext());
	}
	TS_JSAPI bool tsWGContext_open(WGPUInstance instance, WGPUAdapter adapter, WGPUDevice device) {
		return WGContext::open(instance, adapter, device);
	}
	TS_JSAPI bool tsWGContext_create(WGContext &self, WGPUInstance instance, WGPUAdapter adapter, WGPUDevice device) {
		return self.create(instance, adapter, device);
	}
	TS_JSAPI WGPUInstance tsWGContext_getInstance(const WGContext &self) {
		return self.getInstance();
	}
	TS_JSAPI WGPUAdapter tsWGContext_getAdapter(const WGContext &self) {
		return self.getAdapter();
	}
	TS_JSAPI WGPUDevice tsWGContext_getDevice(const WGContext &self) {
		return self.getDevice();
	}
	
	// Tellusim::Query::Statistics
	TS_JSAPI Query::Statistics *tsQueryStatistics_new() {
		return new Query::Statistics();
	}
	TS_JSAPI Query::Statistics *tsQueryStatistics_copy(const Query::Statistics &self) {
		return new Query::Statistics(self);
	}
	TS_JSAPI void tsQueryStatistics_delete(Query::Statistics *self) {
		delete self;
	}
	TS_JSAPI void tsQueryStatistics_set_num_vertices(Query::Statistics &self, uint64_t num_vertices) {
		self.num_vertices = num_vertices;
	}
	TS_JSAPI uint64_t tsQueryStatistics_get_num_vertices(const Query::Statistics &self) {
		return self.num_vertices;
	}
	TS_JSAPI void tsQueryStatistics_set_num_primitives(Query::Statistics &self, uint64_t num_primitives) {
		self.num_primitives = num_primitives;
	}
	TS_JSAPI uint64_t tsQueryStatistics_get_num_primitives(const Query::Statistics &self) {
		return self.num_primitives;
	}
	TS_JSAPI void tsQueryStatistics_set_vertex_invocations(Query::Statistics &self, uint64_t vertex_invocations) {
		self.vertex_invocations = vertex_invocations;
	}
	TS_JSAPI uint64_t tsQueryStatistics_get_vertex_invocations(const Query::Statistics &self) {
		return self.vertex_invocations;
	}
	TS_JSAPI void tsQueryStatistics_set_control_invocations(Query::Statistics &self, uint64_t control_invocations) {
		self.control_invocations = control_invocations;
	}
	TS_JSAPI uint64_t tsQueryStatistics_get_control_invocations(const Query::Statistics &self) {
		return self.control_invocations;
	}
	TS_JSAPI void tsQueryStatistics_set_evaluate_invocations(Query::Statistics &self, uint64_t evaluate_invocations) {
		self.evaluate_invocations = evaluate_invocations;
	}
	TS_JSAPI uint64_t tsQueryStatistics_get_evaluate_invocations(const Query::Statistics &self) {
		return self.evaluate_invocations;
	}
	TS_JSAPI void tsQueryStatistics_set_geometry_invocations(Query::Statistics &self, uint64_t geometry_invocations) {
		self.geometry_invocations = geometry_invocations;
	}
	TS_JSAPI uint64_t tsQueryStatistics_get_geometry_invocations(const Query::Statistics &self) {
		return self.geometry_invocations;
	}
	TS_JSAPI void tsQueryStatistics_set_geometry_primitives(Query::Statistics &self, uint64_t geometry_primitives) {
		self.geometry_primitives = geometry_primitives;
	}
	TS_JSAPI uint64_t tsQueryStatistics_get_geometry_primitives(const Query::Statistics &self) {
		return self.geometry_primitives;
	}
	TS_JSAPI void tsQueryStatistics_set_fragment_invocations(Query::Statistics &self, uint64_t fragment_invocations) {
		self.fragment_invocations = fragment_invocations;
	}
	TS_JSAPI uint64_t tsQueryStatistics_get_fragment_invocations(const Query::Statistics &self) {
		return self.fragment_invocations;
	}
	TS_JSAPI void tsQueryStatistics_set_compute_invocations(Query::Statistics &self, uint64_t compute_invocations) {
		self.compute_invocations = compute_invocations;
	}
	TS_JSAPI uint64_t tsQueryStatistics_get_compute_invocations(const Query::Statistics &self) {
		return self.compute_invocations;
	}
	TS_JSAPI void tsQueryStatistics_set_clipping_invocations(Query::Statistics &self, uint64_t clipping_invocations) {
		self.clipping_invocations = clipping_invocations;
	}
	TS_JSAPI uint64_t tsQueryStatistics_get_clipping_invocations(const Query::Statistics &self) {
		return self.clipping_invocations;
	}
	TS_JSAPI void tsQueryStatistics_set_clipping_primitives(Query::Statistics &self, uint64_t clipping_primitives) {
		self.clipping_primitives = clipping_primitives;
	}
	TS_JSAPI uint64_t tsQueryStatistics_get_clipping_primitives(const Query::Statistics &self) {
		return self.clipping_primitives;
	}
	
	// Tellusim::Query
	TS_JSAPI Query *tsQuery_new() {
		return new Query();
	}
	TS_JSAPI void tsQuery_delete(Query *self) {
		delete self;
	}
	TS_JSAPI bool tsQuery_equalPtr(const Query &self, const Query &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Query *tsQuery_clonePtr(const Query &self) {
		return new Query(self.clonePtr());
	}
	TS_JSAPI void tsQuery_clearPtr(Query &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsQuery_destroyPtr(Query &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsQuery_acquirePtr(Query &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsQuery_unacquirePtr(Query &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsQuery_isValidPtr(const Query &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsQuery_isOwnerPtr(const Query &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsQuery_isConstPtr(const Query &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsQuery_getCountPtr(const Query &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsQuery_getInternalPtr(const Query &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI uint32_t tsQuery_getPlatform(const Query &self) {
		return self.getPlatform();
	}
	TS_JSAPI const char* tsQuery_getPlatformName(const Query &self) {
		return self.getPlatformName();
	}
	TS_JSAPI uint32_t tsQuery_getIndex(const Query &self) {
		return self.getIndex();
	}
	TS_JSAPI void tsQuery_clear(Query &self) {
		self.clear();
	}
	TS_JSAPI bool tsQuery_isCreated(const Query &self) {
		return self.isCreated();
	}
	TS_JSAPI bool tsQuery_isAvailable(const Query &self) {
		return self.isAvailable();
	}
	TS_JSAPI bool tsQuery_isBegan(const Query &self) {
		return self.isBegan();
	}
	TS_JSAPI bool tsQuery_isEnded(const Query &self) {
		return self.isEnded();
	}
	TS_JSAPI bool tsQuery_create(Query &self, uint32_t type) {
		return self.create((Query::Type)type);
	}
	TS_JSAPI uint32_t tsQuery_getType(const Query &self) {
		return self.getType();
	}
	TS_JSAPI const char* tsQuery_getTypeName(uint32_t type) {
		return Query::getTypeName((Query::Type)type);
	}
	TS_JSAPI const char* tsQuery_getTypeName_1(const Query &self) {
		return self.getTypeName();
	}
	TS_JSAPI size_t tsQuery_getTypeSize(const Query &self) {
		return self.getTypeSize();
	}
	TS_JSAPI bool tsQuery_isTime(const Query &self) {
		return self.isTime();
	}
	TS_JSAPI bool tsQuery_isClock(const Query &self) {
		return self.isClock();
	}
	TS_JSAPI bool tsQuery_isSamples(const Query &self) {
		return self.isSamples();
	}
	TS_JSAPI bool tsQuery_isSamples1(const Query &self) {
		return self.isSamples1();
	}
	TS_JSAPI bool tsQuery_isStatistics(const Query &self) {
		return self.isStatistics();
	}
	TS_JSAPI bool tsQuery_isTimeType(const Query &self) {
		return self.isTimeType();
	}
	TS_JSAPI bool tsQuery_isSamplesType(const Query &self) {
		return self.isSamplesType();
	}
	TS_JSAPI bool tsQuery_get(const Query &self, void *dest, size_t size, bool wait) {
		return self.get(dest, size, wait);
	}
	TS_JSAPI uint64_t tsQuery_getTime(const Query &self, bool wait, bool *status) {
		return self.getTime(wait, status);
	}
	TS_JSAPI uint32_t tsQuery_getSamples(const Query &self, bool wait, bool *status) {
		return self.getSamples(wait, status);
	}
	TS_JSAPI Query::Statistics *tsQuery_getStatistics(const Query &self, bool wait, bool *status) {
		return new Query::Statistics(self.getStatistics(wait, status));
	}
	
	// Tellusim::Fence
	TS_JSAPI Fence *tsFence_new() {
		return new Fence();
	}
	TS_JSAPI void tsFence_delete(Fence *self) {
		delete self;
	}
	TS_JSAPI bool tsFence_equalPtr(const Fence &self, const Fence &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Fence *tsFence_clonePtr(const Fence &self) {
		return new Fence(self.clonePtr());
	}
	TS_JSAPI void tsFence_clearPtr(Fence &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsFence_destroyPtr(Fence &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsFence_acquirePtr(Fence &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsFence_unacquirePtr(Fence &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsFence_isValidPtr(const Fence &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsFence_isOwnerPtr(const Fence &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsFence_isConstPtr(const Fence &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsFence_getCountPtr(const Fence &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsFence_getInternalPtr(const Fence &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI uint32_t tsFence_getPlatform(const Fence &self) {
		return self.getPlatform();
	}
	TS_JSAPI const char* tsFence_getPlatformName(const Fence &self) {
		return self.getPlatformName();
	}
	TS_JSAPI uint32_t tsFence_getIndex(const Fence &self) {
		return self.getIndex();
	}
	TS_JSAPI void tsFence_clear(Fence &self) {
		self.clear();
	}
	TS_JSAPI bool tsFence_isCreated(const Fence &self) {
		return self.isCreated();
	}
	TS_JSAPI bool tsFence_create(Fence &self, uint32_t flags) {
		return self.create((Fence::Flags)flags);
	}
	TS_JSAPI uint32_t tsFence_getFlags(const Fence &self) {
		return self.getFlags();
	}
	TS_JSAPI bool tsFence_hasFlag(const Fence &self, uint32_t flags) {
		return self.hasFlag((Fence::Flags)flags);
	}
	TS_JSAPI bool tsFence_hasFlags(const Fence &self, uint32_t flags) {
		return self.hasFlags((Fence::Flags)flags);
	}
	TS_JSAPI String *tsFence_getFlagsName(const Fence &self) {
		return new String(self.getFlagsName());
	}
	TS_JSAPI String *tsFence_getDescription(const Fence &self) {
		return new String(self.getDescription());
	}
	
	// Tellusim::Shader
	TS_JSAPI Shader *tsShader_new() {
		return new Shader();
	}
	TS_JSAPI void tsShader_delete(Shader *self) {
		delete self;
	}
	TS_JSAPI bool tsShader_equalPtr(const Shader &self, const Shader &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Shader *tsShader_clonePtr(const Shader &self) {
		return new Shader(self.clonePtr());
	}
	TS_JSAPI void tsShader_clearPtr(Shader &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsShader_destroyPtr(Shader &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsShader_acquirePtr(Shader &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsShader_unacquirePtr(Shader &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsShader_isValidPtr(const Shader &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsShader_isOwnerPtr(const Shader &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsShader_isConstPtr(const Shader &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsShader_getCountPtr(const Shader &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsShader_getInternalPtr(const Shader &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI uint32_t tsShader_getPlatform(const Shader &self) {
		return self.getPlatform();
	}
	TS_JSAPI const char* tsShader_getPlatformName(const Shader &self) {
		return self.getPlatformName();
	}
	TS_JSAPI uint32_t tsShader_getIndex(const Shader &self) {
		return self.getIndex();
	}
	TS_JSAPI void tsShader_clear(Shader &self) {
		self.clear();
	}
	TS_JSAPI bool tsShader_isCreated(const Shader &self) {
		return self.isCreated();
	}
	TS_JSAPI bool tsShader_saveState(const Shader &self, Stream &stream) {
		return self.saveState(stream);
	}
	TS_JSAPI uint32_t tsShader_getType(const Shader &self) {
		return self.getType();
	}
	TS_JSAPI const char* tsShader_getTypeName(uint32_t type) {
		return Shader::getTypeName((Shader::Type)type);
	}
	TS_JSAPI const char* tsShader_getTypeName_1(const Shader &self) {
		return self.getTypeName();
	}
	TS_JSAPI bool tsShader_isVertex(const Shader &self) {
		return self.isVertex();
	}
	TS_JSAPI bool tsShader_isControl(const Shader &self) {
		return self.isControl();
	}
	TS_JSAPI bool tsShader_isEvaluate(const Shader &self) {
		return self.isEvaluate();
	}
	TS_JSAPI bool tsShader_isGeometry(const Shader &self) {
		return self.isGeometry();
	}
	TS_JSAPI bool tsShader_isFragment(const Shader &self) {
		return self.isFragment();
	}
	TS_JSAPI bool tsShader_isCompute(const Shader &self) {
		return self.isCompute();
	}
	TS_JSAPI bool tsShader_isTask(const Shader &self) {
		return self.isTask();
	}
	TS_JSAPI bool tsShader_isMesh(const Shader &self) {
		return self.isMesh();
	}
	TS_JSAPI bool tsShader_isRayGen(const Shader &self) {
		return self.isRayGen();
	}
	TS_JSAPI bool tsShader_isRayMiss(const Shader &self) {
		return self.isRayMiss();
	}
	TS_JSAPI bool tsShader_isClosest(const Shader &self) {
		return self.isClosest();
	}
	TS_JSAPI bool tsShader_isFirstHit(const Shader &self) {
		return self.isFirstHit();
	}
	TS_JSAPI bool tsShader_isIntersection(const Shader &self) {
		return self.isIntersection();
	}
	TS_JSAPI bool tsShader_isCallable(const Shader &self) {
		return self.isCallable();
	}
	TS_JSAPI bool tsShader_isGraphicsType(const Shader &self) {
		return self.isGraphicsType();
	}
	TS_JSAPI bool tsShader_isTessellationType(const Shader &self) {
		return self.isTessellationType();
	}
	TS_JSAPI bool tsShader_isTracingType(const Shader &self) {
		return self.isTracingType();
	}
	TS_JSAPI bool tsShader_isMeshType(const Shader &self) {
		return self.isMeshType();
	}
	TS_JSAPI String *tsShader_getName(const Shader &self) {
		return new String(self.getName());
	}
	TS_JSAPI String *tsShader_getMacros(const Shader &self) {
		return new String(self.getMacros());
	}
	TS_JSAPI void tsShader_setSamplerOffset(Shader &self, int32_t offset) {
		self.setSamplerOffset(offset);
	}
	TS_JSAPI int32_t tsShader_getSamplerOffset(const Shader &self) {
		return self.getSamplerOffset();
	}
	TS_JSAPI void tsShader_setTextureOffset(Shader &self, int32_t offset) {
		self.setTextureOffset(offset);
	}
	TS_JSAPI int32_t tsShader_getTextureOffset(const Shader &self) {
		return self.getTextureOffset();
	}
	TS_JSAPI void tsShader_setSurfaceOffset(Shader &self, int32_t offset) {
		self.setSurfaceOffset(offset);
	}
	TS_JSAPI int32_t tsShader_getSurfaceOffset(const Shader &self) {
		return self.getSurfaceOffset();
	}
	TS_JSAPI void tsShader_setUniformOffset(Shader &self, int32_t offset) {
		self.setUniformOffset(offset);
	}
	TS_JSAPI int32_t tsShader_getUniformOffset(const Shader &self) {
		return self.getUniformOffset();
	}
	TS_JSAPI void tsShader_setStorageOffset(Shader &self, int32_t offset) {
		self.setStorageOffset(offset);
	}
	TS_JSAPI int32_t tsShader_getStorageOffset(const Shader &self) {
		return self.getStorageOffset();
	}
	TS_JSAPI void tsShader_setTracingOffset(Shader &self, int32_t offset) {
		self.setTracingOffset(offset);
	}
	TS_JSAPI int32_t tsShader_getTracingOffset(const Shader &self) {
		return self.getTracingOffset();
	}
	TS_JSAPI void tsShader_setTexelOffset(Shader &self, int32_t offset) {
		self.setTexelOffset(offset);
	}
	TS_JSAPI int32_t tsShader_getTexelOffset(const Shader &self) {
		return self.getTexelOffset();
	}
	TS_JSAPI void tsShader_setTableOffset(Shader &self, int32_t offset) {
		self.setTableOffset(offset);
	}
	TS_JSAPI int32_t tsShader_getTableOffset(const Shader &self) {
		return self.getTableOffset();
	}
	TS_JSAPI void tsShader_setPatchSize(Shader &self, uint32_t size) {
		self.setPatchSize(size);
	}
	TS_JSAPI uint32_t tsShader_getPatchSize(const Shader &self) {
		return self.getPatchSize();
	}
	TS_JSAPI void tsShader_setInputSize(Shader &self, uint32_t size) {
		self.setInputSize(size);
	}
	TS_JSAPI uint32_t tsShader_getInputSize(const Shader &self) {
		return self.getInputSize();
	}
	TS_JSAPI void tsShader_setOutputSize(Shader &self, uint32_t size) {
		self.setOutputSize(size);
	}
	TS_JSAPI uint32_t tsShader_getOutputSize(const Shader &self) {
		return self.getOutputSize();
	}
	TS_JSAPI bool tsShader_load(Shader &self, uint32_t type, const char *name, const char *format) {
		return self.load((Shader::Type)type, name, "%s", format);
	}
	TS_JSAPI bool tsShader_create(Shader &self, uint32_t type, const char *src, const char *format) {
		return self.create((Shader::Type)type, src, "%s", format);
	}
	TS_JSAPI bool tsShader_load_1(Shader &self, uint32_t type, const char *name, const String &macros, const char **includes, uint32_t size) {
		return self.load((Shader::Type)type, name, macros, includes, size);
	}
	TS_JSAPI bool tsShader_create_1(Shader &self, uint32_t type, const char *src, const String &macros, const char **includes, uint32_t size) {
		return self.create((Shader::Type)type, src, macros, includes, size);
	}
	TS_JSAPI bool tsShader_loadGLSL(Shader &self, uint32_t type, const char *name, const char *format) {
		return self.loadGLSL((Shader::Type)type, name, "%s", format);
	}
	TS_JSAPI bool tsShader_createGLSL(Shader &self, uint32_t type, const char *src, const char *format) {
		return self.createGLSL((Shader::Type)type, src, "%s", format);
	}
	TS_JSAPI bool tsShader_loadGLSL_1(Shader &self, uint32_t type, const char *name, const String &macros, const char **includes, uint32_t size) {
		return self.loadGLSL((Shader::Type)type, name, macros, includes, size);
	}
	TS_JSAPI bool tsShader_createGLSL_1(Shader &self, uint32_t type, const char *src, const String &macros, const char **includes, uint32_t size) {
		return self.createGLSL((Shader::Type)type, src, macros, includes, size);
	}
	TS_JSAPI bool tsShader_loadSPIRV(Shader &self, uint32_t type, const char *name) {
		return self.loadSPIRV((Shader::Type)type, name);
	}
	TS_JSAPI bool tsShader_createSPIRV(Shader &self, uint32_t type, Array<uint32_t> &data) {
		return self.createSPIRV((Shader::Type)type, data);
	}
	TS_JSAPI bool tsShader_hasCache() {
		return Shader::hasCache();
	}
	TS_JSAPI bool tsShader_setCache(const char *name) {
		return Shader::setCache(name);
	}
	TS_JSAPI bool tsShader_loadCache(const String &hash, Stream &stream) {
		return Shader::loadCache(hash, stream);
	}
	TS_JSAPI bool tsShader_saveCache(const String &hash, Stream &stream) {
		return Shader::saveCache(hash, stream);
	}
	TS_JSAPI void tsShader_clearCache() {
		Shader::clearCache();
	}
	TS_JSAPI bool tsShader_isMacro(const char *name) {
		return Shader::isMacro(name);
	}
	TS_JSAPI bool tsShader_setMacro(const char *name, int32_t value) {
		return Shader::setMacro(name, value);
	}
	TS_JSAPI bool tsShader_setMacro_1(const char *name, uint32_t value) {
		return Shader::setMacro(name, value);
	}
	TS_JSAPI bool tsShader_setMacro_2(const char *name, const char *value) {
		return Shader::setMacro(name, value);
	}
	TS_JSAPI bool tsShader_setMacros(const char *macros) {
		return Shader::setMacros(macros);
	}
	TS_JSAPI bool tsShader_removeMacro(const char *name) {
		return Shader::removeMacro(name);
	}
	TS_JSAPI void tsShader_clearMacros() {
		Shader::clearMacros();
	}
	TS_JSAPI bool tsShader_isInclude(const char *name) {
		return Shader::isInclude(name);
	}
	TS_JSAPI bool tsShader_setInclude(const char *name, const String &src) {
		return Shader::setInclude(name, src);
	}
	TS_JSAPI bool tsShader_removeInclude(const char *name) {
		return Shader::removeInclude(name);
	}
	TS_JSAPI void tsShader_clearIncludes() {
		Shader::clearIncludes();
	}
	TS_JSAPI String *tsShader_preprocessor(const char *src, const char *format) {
		return new String(Shader::preprocessor(src, "%s", format));
	}
	TS_JSAPI String *tsShader_preprocessor_1(const char *src, const String &macros, const char **includes, uint32_t size) {
		return new String(Shader::preprocessor(src, macros, includes, size));
	}
	
	// Tellusim::ShaderCompiler
	TS_JSAPI ShaderCompiler *tsShaderCompiler_new() {
		return new ShaderCompiler();
	}
	TS_JSAPI void tsShaderCompiler_delete(ShaderCompiler *self) {
		delete self;
	}
	TS_JSAPI bool tsShaderCompiler_equalShaderPtr(const ShaderCompiler &self, const Shader &base) {
		return self.operator==(base);
	}
	TS_JSAPI ShaderCompiler *tsShaderCompiler_castShaderPtr(const Shader &self) {
		return new ShaderCompiler(self);
	}
	TS_JSAPI Shader *tsShaderCompiler_baseShaderPtr(const ShaderCompiler &self) {
		return new Shader(self.getShader());
	}
	TS_JSAPI void tsShaderCompiler_setFlags(ShaderCompiler &self, uint32_t flags) {
		self.setFlags((ShaderCompiler::Flags)flags);
	}
	TS_JSAPI uint32_t tsShaderCompiler_getFlags(const ShaderCompiler &self) {
		return self.getFlags();
	}
	TS_JSAPI bool tsShaderCompiler_getBinary(const ShaderCompiler &self, Stream &stream, uint32_t platform) {
		return self.getBinary(stream, (Platform)platform);
	}
	TS_JSAPI String *tsShaderCompiler_getSource(const ShaderCompiler &self, uint32_t platform) {
		return new String(self.getSource((Platform)platform));
	}
	
	// Tellusim::GLESShader
	TS_JSAPI GLESShader *tsGLESShader_new() {
		return new GLESShader();
	}
	TS_JSAPI void tsGLESShader_delete(GLESShader *self) {
		delete self;
	}
	TS_JSAPI bool tsGLESShader_equalShaderPtr(const GLESShader &self, const Shader &base) {
		return self.operator==(base);
	}
	TS_JSAPI GLESShader *tsGLESShader_castShaderPtr(const Shader &self) {
		return new GLESShader(self);
	}
	TS_JSAPI Shader *tsGLESShader_baseShaderPtr(const GLESShader &self) {
		return new Shader(self.getShader());
	}
	TS_JSAPI bool tsGLESShader_attachShader(GLESShader &self, uint32_t program_id) {
		return self.attachShader(program_id);
	}
	TS_JSAPI uint32_t tsGLESShader_getShaderType(const GLESShader &self) {
		return self.getShaderType();
	}
	TS_JSAPI uint32_t tsGLESShader_getShaderID(const GLESShader &self) {
		return self.getShaderID();
	}
	
	// Tellusim::Sampler
	TS_JSAPI Sampler *tsSampler_new() {
		return new Sampler();
	}
	TS_JSAPI void tsSampler_delete(Sampler *self) {
		delete self;
	}
	TS_JSAPI bool tsSampler_equalPtr(const Sampler &self, const Sampler &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Sampler *tsSampler_clonePtr(const Sampler &self) {
		return new Sampler(self.clonePtr());
	}
	TS_JSAPI void tsSampler_clearPtr(Sampler &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsSampler_destroyPtr(Sampler &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsSampler_acquirePtr(Sampler &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsSampler_unacquirePtr(Sampler &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsSampler_isValidPtr(const Sampler &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsSampler_isOwnerPtr(const Sampler &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsSampler_isConstPtr(const Sampler &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsSampler_getCountPtr(const Sampler &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsSampler_getInternalPtr(const Sampler &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI uint32_t tsSampler_getPlatform(const Sampler &self) {
		return self.getPlatform();
	}
	TS_JSAPI const char* tsSampler_getPlatformName(const Sampler &self) {
		return self.getPlatformName();
	}
	TS_JSAPI uint32_t tsSampler_getIndex(const Sampler &self) {
		return self.getIndex();
	}
	TS_JSAPI void tsSampler_clear(Sampler &self) {
		self.clear();
	}
	TS_JSAPI bool tsSampler_isCreated(const Sampler &self) {
		return self.isCreated();
	}
	TS_JSAPI bool tsSampler_create(Sampler &self) {
		return self.create();
	}
	TS_JSAPI void tsSampler_setParameters(Sampler &self, const Sampler &sampler) {
		self.setParameters(sampler);
	}
	TS_JSAPI void tsSampler_setFilter(Sampler &self, uint32_t filter) {
		self.setFilter((Sampler::Filter)filter);
	}
	TS_JSAPI uint32_t tsSampler_getFilter(const Sampler &self) {
		return self.getFilter();
	}
	TS_JSAPI bool tsSampler_isPointFilter(const Sampler &self) {
		return self.isPointFilter();
	}
	TS_JSAPI void tsSampler_setAnisotropy(Sampler &self, uint32_t anisotropy) {
		self.setAnisotropy(anisotropy);
	}
	TS_JSAPI uint32_t tsSampler_getAnisotropy(const Sampler &self) {
		return self.getAnisotropy();
	}
	TS_JSAPI bool tsSampler_hasAnisotropy(const Sampler &self) {
		return self.hasAnisotropy();
	}
	TS_JSAPI void tsSampler_setWrapMode(Sampler &self, uint32_t mode) {
		self.setWrapMode((Sampler::WrapMode)mode);
	}
	TS_JSAPI void tsSampler_setWrapMode_1(Sampler &self, uint32_t mode_s, uint32_t mode_t, uint32_t mode_r) {
		self.setWrapMode((Sampler::WrapMode)mode_s, (Sampler::WrapMode)mode_t, (Sampler::WrapMode)mode_r);
	}
	TS_JSAPI void tsSampler_setWrapModeS(Sampler &self, uint32_t mode) {
		self.setWrapModeS((Sampler::WrapMode)mode);
	}
	TS_JSAPI uint32_t tsSampler_getWrapModeS(const Sampler &self) {
		return self.getWrapModeS();
	}
	TS_JSAPI void tsSampler_setWrapModeT(Sampler &self, uint32_t mode) {
		self.setWrapModeT((Sampler::WrapMode)mode);
	}
	TS_JSAPI uint32_t tsSampler_getWrapModeT(const Sampler &self) {
		return self.getWrapModeT();
	}
	TS_JSAPI void tsSampler_setWrapModeR(Sampler &self, uint32_t mode) {
		self.setWrapModeR((Sampler::WrapMode)mode);
	}
	TS_JSAPI uint32_t tsSampler_getWrapModeR(const Sampler &self) {
		return self.getWrapModeR();
	}
	TS_JSAPI void tsSampler_setLod(Sampler &self, float32_t min, float32_t max, float32_t bias) {
		self.setLod(min, max, bias);
	}
	TS_JSAPI void tsSampler_setLodMin(Sampler &self, float32_t min) {
		self.setLodMin(min);
	}
	TS_JSAPI float32_t tsSampler_getLodMin(const Sampler &self) {
		return self.getLodMin();
	}
	TS_JSAPI void tsSampler_setLodMax(Sampler &self, float32_t max) {
		self.setLodMax(max);
	}
	TS_JSAPI float32_t tsSampler_getLodMax(const Sampler &self) {
		return self.getLodMax();
	}
	TS_JSAPI void tsSampler_setLodBias(Sampler &self, float32_t bias) {
		self.setLodBias(bias);
	}
	TS_JSAPI float32_t tsSampler_getLodBias(const Sampler &self) {
		return self.getLodBias();
	}
	TS_JSAPI void tsSampler_setBorderColor(Sampler &self, const Color &color) {
		self.setBorderColor(color);
	}
	TS_JSAPI void tsSampler_setBorderColor_1(Sampler &self, float32_t r, float32_t g, float32_t b, float32_t a) {
		self.setBorderColor(r, g, b, a);
	}
	TS_JSAPI const Color *tsSampler_getBorderColor(const Sampler &self) {
		return new Color(self.getBorderColor());
	}
	TS_JSAPI void tsSampler_setCompareFunc(Sampler &self, uint32_t func) {
		self.setCompareFunc((Sampler::CompareFunc)func);
	}
	TS_JSAPI uint32_t tsSampler_getCompareFunc(const Sampler &self) {
		return self.getCompareFunc();
	}
	TS_JSAPI void tsSampler_setReductionMode(Sampler &self, uint32_t mode) {
		self.setReductionMode((Sampler::ReductionMode)mode);
	}
	TS_JSAPI uint32_t tsSampler_getReductionMode(const Sampler &self) {
		return self.getReductionMode();
	}
	
	// Tellusim::Texture
	TS_JSAPI Texture *tsTexture_new() {
		return new Texture();
	}
	TS_JSAPI void tsTexture_delete(Texture *self) {
		delete self;
	}
	TS_JSAPI bool tsTexture_equalPtr(const Texture &self, const Texture &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Texture *tsTexture_clonePtr(const Texture &self) {
		return new Texture(self.clonePtr());
	}
	TS_JSAPI void tsTexture_clearPtr(Texture &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsTexture_destroyPtr(Texture &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsTexture_acquirePtr(Texture &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsTexture_unacquirePtr(Texture &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsTexture_isValidPtr(const Texture &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsTexture_isOwnerPtr(const Texture &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsTexture_isConstPtr(const Texture &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsTexture_getCountPtr(const Texture &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsTexture_getInternalPtr(const Texture &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI uint32_t tsTexture_getPlatform(const Texture &self) {
		return self.getPlatform();
	}
	TS_JSAPI const char* tsTexture_getPlatformName(const Texture &self) {
		return self.getPlatformName();
	}
	TS_JSAPI uint32_t tsTexture_getIndex(const Texture &self) {
		return self.getIndex();
	}
	TS_JSAPI void tsTexture_clear(Texture &self) {
		self.clear();
	}
	TS_JSAPI bool tsTexture_isCreated(const Texture &self) {
		return self.isCreated();
	}
	TS_JSAPI void tsTexture_setName(Texture &self, const char *name) {
		self.setName(name);
	}
	TS_JSAPI String *tsTexture_getName(const Texture &self) {
		return new String(self.getName());
	}
	TS_JSAPI bool tsTexture_create(Texture &self, uint32_t type, uint32_t format, const Size &size, uint32_t layers, uint32_t flags) {
		return self.create((Texture::Type)type, (Format)format, size, layers, (Texture::Flags)flags);
	}
	TS_JSAPI bool tsTexture_create2D(Texture &self, uint32_t format, uint32_t size, uint32_t flags) {
		return self.create2D((Format)format, size, (Texture::Flags)flags);
	}
	TS_JSAPI bool tsTexture_create3D(Texture &self, uint32_t format, uint32_t size, uint32_t flags) {
		return self.create3D((Format)format, size, (Texture::Flags)flags);
	}
	TS_JSAPI bool tsTexture_createCube(Texture &self, uint32_t format, uint32_t size, uint32_t flags) {
		return self.createCube((Format)format, size, (Texture::Flags)flags);
	}
	TS_JSAPI bool tsTexture_create2D_1(Texture &self, uint32_t format, uint32_t width, uint32_t height, uint32_t flags) {
		return self.create2D((Format)format, width, height, (Texture::Flags)flags);
	}
	TS_JSAPI bool tsTexture_create3D_1(Texture &self, uint32_t format, uint32_t width, uint32_t height, uint32_t depth, uint32_t flags) {
		return self.create3D((Format)format, width, height, depth, (Texture::Flags)flags);
	}
	TS_JSAPI bool tsTexture_create2D_2(Texture &self, uint32_t format, uint32_t width, uint32_t height, uint32_t layers, uint32_t flags) {
		return self.create2D((Format)format, width, height, layers, (Texture::Flags)flags);
	}
	TS_JSAPI bool tsTexture_createCube_1(Texture &self, uint32_t format, uint32_t size, uint32_t layers, uint32_t flags) {
		return self.createCube((Format)format, size, layers, (Texture::Flags)flags);
	}
	TS_JSAPI uint32_t tsTexture_getType(const Texture &self) {
		return self.getType();
	}
	TS_JSAPI const char* tsTexture_getTypeName(uint32_t type) {
		return Texture::getTypeName((Texture::Type)type);
	}
	TS_JSAPI const char* tsTexture_getTypeName_1(const Texture &self) {
		return self.getTypeName();
	}
	TS_JSAPI bool tsTexture_is2DType(const Texture &self) {
		return self.is2DType();
	}
	TS_JSAPI bool tsTexture_is3DType(const Texture &self) {
		return self.is3DType();
	}
	TS_JSAPI bool tsTexture_isCubeType(const Texture &self) {
		return self.isCubeType();
	}
	TS_JSAPI uint32_t tsTexture_getFormat(const Texture &self) {
		return self.getFormat();
	}
	TS_JSAPI const char* tsTexture_getFormatName(const Texture &self) {
		return self.getFormatName();
	}
	TS_JSAPI bool tsTexture_isColorFormat(const Texture &self) {
		return self.isColorFormat();
	}
	TS_JSAPI bool tsTexture_isDepthFormat(const Texture &self) {
		return self.isDepthFormat();
	}
	TS_JSAPI bool tsTexture_isPixelFormat(const Texture &self) {
		return self.isPixelFormat();
	}
	TS_JSAPI bool tsTexture_isPlainFormat(const Texture &self) {
		return self.isPlainFormat();
	}
	TS_JSAPI bool tsTexture_isMixedFormat(const Texture &self) {
		return self.isMixedFormat();
	}
	TS_JSAPI bool tsTexture_isBlockFormat(const Texture &self) {
		return self.isBlockFormat();
	}
	TS_JSAPI bool tsTexture_isStencilFormat(const Texture &self) {
		return self.isStencilFormat();
	}
	TS_JSAPI bool tsTexture_isNormFormat(const Texture &self) {
		return self.isNormFormat();
	}
	TS_JSAPI bool tsTexture_isSRGBFormat(const Texture &self) {
		return self.isSRGBFormat();
	}
	TS_JSAPI bool tsTexture_isFloatFormat(const Texture &self) {
		return self.isFloatFormat();
	}
	TS_JSAPI bool tsTexture_isSignedFormat(const Texture &self) {
		return self.isSignedFormat();
	}
	TS_JSAPI bool tsTexture_isUnsignedFormat(const Texture &self) {
		return self.isUnsignedFormat();
	}
	TS_JSAPI bool tsTexture_isIntegerFormat(const Texture &self) {
		return self.isIntegerFormat();
	}
	TS_JSAPI bool tsTexture_isi8Format(const Texture &self) {
		return self.isi8Format();
	}
	TS_JSAPI bool tsTexture_isu8Format(const Texture &self) {
		return self.isu8Format();
	}
	TS_JSAPI bool tsTexture_is8BitFormat(const Texture &self) {
		return self.is8BitFormat();
	}
	TS_JSAPI bool tsTexture_isi16Format(const Texture &self) {
		return self.isi16Format();
	}
	TS_JSAPI bool tsTexture_isu16Format(const Texture &self) {
		return self.isu16Format();
	}
	TS_JSAPI bool tsTexture_isf16Format(const Texture &self) {
		return self.isf16Format();
	}
	TS_JSAPI bool tsTexture_is16BitFormat(const Texture &self) {
		return self.is16BitFormat();
	}
	TS_JSAPI bool tsTexture_isi32Format(const Texture &self) {
		return self.isi32Format();
	}
	TS_JSAPI bool tsTexture_isu32Format(const Texture &self) {
		return self.isu32Format();
	}
	TS_JSAPI bool tsTexture_isf32Format(const Texture &self) {
		return self.isf32Format();
	}
	TS_JSAPI bool tsTexture_is32BitFormat(const Texture &self) {
		return self.is32BitFormat();
	}
	TS_JSAPI bool tsTexture_isi64Format(const Texture &self) {
		return self.isi64Format();
	}
	TS_JSAPI bool tsTexture_isu64Format(const Texture &self) {
		return self.isu64Format();
	}
	TS_JSAPI bool tsTexture_isf64Format(const Texture &self) {
		return self.isf64Format();
	}
	TS_JSAPI bool tsTexture_is64BitFormat(const Texture &self) {
		return self.is64BitFormat();
	}
	TS_JSAPI bool tsTexture_isBC15Format(const Texture &self) {
		return self.isBC15Format();
	}
	TS_JSAPI bool tsTexture_isBC67Format(const Texture &self) {
		return self.isBC67Format();
	}
	TS_JSAPI bool tsTexture_isETC2Format(const Texture &self) {
		return self.isETC2Format();
	}
	TS_JSAPI bool tsTexture_isASTCFormat(const Texture &self) {
		return self.isASTCFormat();
	}
	TS_JSAPI uint32_t tsTexture_getComponents(const Texture &self) {
		return self.getComponents();
	}
	TS_JSAPI uint32_t tsTexture_getPixelSize(const Texture &self) {
		return self.getPixelSize();
	}
	TS_JSAPI uint32_t tsTexture_getBlockSize(const Texture &self) {
		return self.getBlockSize();
	}
	TS_JSAPI uint32_t tsTexture_getBlockWidth(const Texture &self) {
		return self.getBlockWidth();
	}
	TS_JSAPI uint32_t tsTexture_getBlockHeight(const Texture &self) {
		return self.getBlockHeight();
	}
	TS_JSAPI uint32_t tsTexture_getFlags(const Texture &self) {
		return self.getFlags();
	}
	TS_JSAPI bool tsTexture_hasFlag(const Texture &self, uint32_t flags) {
		return self.hasFlag((Texture::Flags)flags);
	}
	TS_JSAPI bool tsTexture_hasFlags(const Texture &self, uint32_t flags) {
		return self.hasFlags((Texture::Flags)flags);
	}
	TS_JSAPI String *tsTexture_getFlagsName(const Texture &self) {
		return new String(self.getFlagsName());
	}
	TS_JSAPI uint32_t tsTexture_getMultisample(const Texture &self) {
		return self.getMultisample();
	}
	TS_JSAPI bool tsTexture_hasMultisample(const Texture &self) {
		return self.hasMultisample();
	}
	TS_JSAPI uint32_t tsTexture_getWidth(const Texture &self) {
		return self.getWidth();
	}
	TS_JSAPI uint32_t tsTexture_getHeight(const Texture &self) {
		return self.getHeight();
	}
	TS_JSAPI uint32_t tsTexture_getDepth(const Texture &self) {
		return self.getDepth();
	}
	TS_JSAPI uint32_t tsTexture_getFaces(const Texture &self) {
		return self.getFaces();
	}
	TS_JSAPI uint32_t tsTexture_getLayers(const Texture &self) {
		return self.getLayers();
	}
	TS_JSAPI uint32_t tsTexture_getMipmaps(const Texture &self) {
		return self.getMipmaps();
	}
	TS_JSAPI uint32_t tsTexture_findMipmap(const Texture &self, const Size &size) {
		return self.findMipmap(size);
	}
	TS_JSAPI uint32_t tsTexture_getWidth_1(const Texture &self, uint32_t mipmap) {
		return self.getWidth(mipmap);
	}
	TS_JSAPI uint32_t tsTexture_getHeight_1(const Texture &self, uint32_t mipmap) {
		return self.getHeight(mipmap);
	}
	TS_JSAPI uint32_t tsTexture_getDepth_1(const Texture &self, uint32_t mipmap) {
		return self.getDepth(mipmap);
	}
	TS_JSAPI bool tsTexture_hasFaces(const Texture &self) {
		return self.hasFaces();
	}
	TS_JSAPI bool tsTexture_hasLayers(const Texture &self) {
		return self.hasLayers();
	}
	TS_JSAPI bool tsTexture_hasMipmaps(const Texture &self) {
		return self.hasMipmaps();
	}
	TS_JSAPI Size *tsTexture_getSize(const Texture &self) {
		return new Size(self.getSize());
	}
	TS_JSAPI Region *tsTexture_getRegion(const Texture &self) {
		return new Region(self.getRegion());
	}
	TS_JSAPI Slice *tsTexture_getSlice(const Texture &self) {
		return new Slice(self.getSlice());
	}
	TS_JSAPI Size *tsTexture_getSize_1(const Texture &self, uint32_t mipmap) {
		return new Size(self.getSize(mipmap));
	}
	TS_JSAPI Region *tsTexture_getRegion_1(const Texture &self, uint32_t mipmap) {
		return new Region(self.getRegion(mipmap));
	}
	TS_JSAPI Slice *tsTexture_getSlice_1(const Texture &self, uint32_t mipmap) {
		return new Slice(self.getSlice(mipmap));
	}
	TS_JSAPI uint32_t tsTexture_getTileWidth(const Texture &self) {
		return self.getTileWidth();
	}
	TS_JSAPI uint32_t tsTexture_getTileHeight(const Texture &self) {
		return self.getTileHeight();
	}
	TS_JSAPI uint32_t tsTexture_getTileDepth(const Texture &self) {
		return self.getTileDepth();
	}
	TS_JSAPI uint32_t tsTexture_getTileMipmaps(const Texture &self) {
		return self.getTileMipmaps();
	}
	TS_JSAPI Size *tsTexture_getTileSize(const Texture &self) {
		return new Size(self.getTileSize());
	}
	TS_JSAPI String *tsTexture_getDescription(const Texture &self) {
		return new String(self.getDescription());
	}
	TS_JSAPI size_t tsTexture_getMemory(const Texture &self) {
		return self.getMemory();
	}
	
	// Tellusim::TextureTable
	TS_JSAPI TextureTable *tsTextureTable_new() {
		return new TextureTable();
	}
	TS_JSAPI void tsTextureTable_delete(TextureTable *self) {
		delete self;
	}
	TS_JSAPI bool tsTextureTable_equalPtr(const TextureTable &self, const TextureTable &ptr) {
		return (self == ptr);
	}
	TS_JSAPI TextureTable *tsTextureTable_clonePtr(const TextureTable &self) {
		return new TextureTable(self.clonePtr());
	}
	TS_JSAPI void tsTextureTable_clearPtr(TextureTable &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsTextureTable_destroyPtr(TextureTable &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsTextureTable_acquirePtr(TextureTable &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsTextureTable_unacquirePtr(TextureTable &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsTextureTable_isValidPtr(const TextureTable &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsTextureTable_isOwnerPtr(const TextureTable &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsTextureTable_isConstPtr(const TextureTable &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsTextureTable_getCountPtr(const TextureTable &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsTextureTable_getInternalPtr(const TextureTable &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI uint32_t tsTextureTable_getPlatform(const TextureTable &self) {
		return self.getPlatform();
	}
	TS_JSAPI const char* tsTextureTable_getPlatformName(const TextureTable &self) {
		return self.getPlatformName();
	}
	TS_JSAPI uint32_t tsTextureTable_getIndex(const TextureTable &self) {
		return self.getIndex();
	}
	TS_JSAPI void tsTextureTable_clear(TextureTable &self) {
		self.clear();
	}
	TS_JSAPI bool tsTextureTable_isCreated(const TextureTable &self) {
		return self.isCreated();
	}
	TS_JSAPI void tsTextureTable_setName(TextureTable &self, const char *name) {
		self.setName(name);
	}
	TS_JSAPI String *tsTextureTable_getName(const TextureTable &self) {
		return new String(self.getName());
	}
	TS_JSAPI bool tsTextureTable_create(TextureTable &self, uint32_t type, uint32_t size) {
		return self.create((Texture::Type)type, size);
	}
	TS_JSAPI uint32_t tsTextureTable_getType(const TextureTable &self) {
		return self.getType();
	}
	TS_JSAPI const char* tsTextureTable_getTypeName(const TextureTable &self) {
		return self.getTypeName();
	}
	TS_JSAPI uint32_t tsTextureTable_getSize(const TextureTable &self) {
		return self.getSize();
	}
	TS_JSAPI Texture *tsTextureTable_get(const TextureTable &self, uint32_t index) {
		return new Texture(self.get(index));
	}
	TS_JSAPI bool tsTextureTable_isOwner(const TextureTable &self, uint32_t index) {
		return self.isOwner(index);
	}
	TS_JSAPI size_t tsTextureTable_getMemory(const TextureTable &self) {
		return self.getMemory();
	}
	
	// Tellusim::GLESTexture
	TS_JSAPI GLESTexture *tsGLESTexture_new() {
		return new GLESTexture();
	}
	TS_JSAPI void tsGLESTexture_delete(GLESTexture *self) {
		delete self;
	}
	TS_JSAPI bool tsGLESTexture_equalTexturePtr(const GLESTexture &self, const Texture &base) {
		return self.operator==(base);
	}
	TS_JSAPI GLESTexture *tsGLESTexture_castTexturePtr(const Texture &self) {
		return new GLESTexture(self);
	}
	TS_JSAPI Texture *tsGLESTexture_baseTexturePtr(const GLESTexture &self) {
		return new Texture(self.getTexture());
	}
	TS_JSAPI bool tsGLESTexture_create(GLESTexture &self, uint32_t target, uint32_t texture_id, uint32_t flags, uint32_t format) {
		return self.create(target, texture_id, (Texture::Flags)flags, (Format)format);
	}
	TS_JSAPI uint32_t tsGLESTexture_getTarget(const GLESTexture &self) {
		return self.getTarget();
	}
	TS_JSAPI uint32_t tsGLESTexture_getInternalFormat(const GLESTexture &self) {
		return self.getInternalFormat();
	}
	TS_JSAPI uint32_t tsGLESTexture_getTextureID(const GLESTexture &self) {
		return self.getTextureID();
	}
	
	// Tellusim::Tracing::Instance
	TS_JSAPI Tracing::Instance *tsTracingInstance_new() {
		return new Tracing::Instance();
	}
	TS_JSAPI Tracing::Instance *tsTracingInstance_copy(const Tracing::Instance &self) {
		return new Tracing::Instance(self);
	}
	TS_JSAPI void tsTracingInstance_delete(Tracing::Instance *self) {
		delete self;
	}
	TS_JSAPI void tsTracingInstance_set_transform(Tracing::Instance &self, const Matrix4x3f &transform) {
		transform.get(self.transform);
	}
	TS_JSAPI Matrix4x3f *tsTracingInstance_get_transform(const Tracing::Instance &self) {
		return new Matrix4x3f(self.transform);
	}
	TS_JSAPI void tsTracingInstance_set_data(Tracing::Instance &self, uint32_t data) {
		self.data = data;
	}
	TS_JSAPI uint32_t tsTracingInstance_get_data(const Tracing::Instance &self) {
		return self.data;
	}
	TS_JSAPI void tsTracingInstance_set_mask(Tracing::Instance &self, uint32_t mask) {
		self.mask = mask;
	}
	TS_JSAPI uint32_t tsTracingInstance_get_mask(const Tracing::Instance &self) {
		return self.mask;
	}
	TS_JSAPI void tsTracingInstance_set_flags(Tracing::Instance &self, uint32_t flags) {
		self.flags = flags;
	}
	TS_JSAPI uint32_t tsTracingInstance_get_flags(const Tracing::Instance &self) {
		return self.flags;
	}
	TS_JSAPI void tsTracingInstance_set_offset(Tracing::Instance &self, uint32_t offset) {
		self.offset = offset;
	}
	TS_JSAPI uint32_t tsTracingInstance_get_offset(const Tracing::Instance &self) {
		return self.offset;
	}
	TS_JSAPI void tsTracingInstance_set_tracing(Tracing::Instance &self, Tracing *tracing) {
		self.tracing = tracing;
	}
	TS_JSAPI Tracing *tsTracingInstance_get_tracing(const Tracing::Instance &self) {
		return (self.tracing) ? new Tracing(*self.tracing) : nullptr;
	}
	// Tellusim::Tracing::BuildIndirect
	TS_JSAPI Tracing::BuildIndirect *tsTracingBuildIndirect_new() {
		return new Tracing::BuildIndirect();
	}
	TS_JSAPI Tracing::BuildIndirect *tsTracingBuildIndirect_copy(const Tracing::BuildIndirect &self) {
		return new Tracing::BuildIndirect(self);
	}
	TS_JSAPI void tsTracingBuildIndirect_delete(Tracing::BuildIndirect *self) {
		delete self;
	}
	TS_JSAPI void tsTracingBuildIndirect_set_num_primitives(Tracing::BuildIndirect &self, uint32_t num_primitives) {
		self.num_primitives = num_primitives;
	}
	TS_JSAPI uint32_t tsTracingBuildIndirect_get_num_primitives(const Tracing::BuildIndirect &self) {
		return self.num_primitives;
	}
	TS_JSAPI void tsTracingBuildIndirect_set_base_primitive(Tracing::BuildIndirect &self, uint32_t base_primitive) {
		self.base_primitive = base_primitive;
	}
	TS_JSAPI uint32_t tsTracingBuildIndirect_get_base_primitive(const Tracing::BuildIndirect &self) {
		return self.base_primitive;
	}
	TS_JSAPI void tsTracingBuildIndirect_set_base_vertex(Tracing::BuildIndirect &self, uint32_t base_vertex) {
		self.base_vertex = base_vertex;
	}
	TS_JSAPI uint32_t tsTracingBuildIndirect_get_base_vertex(const Tracing::BuildIndirect &self) {
		return self.base_vertex;
	}
	TS_JSAPI void tsTracingBuildIndirect_set_base_transform(Tracing::BuildIndirect &self, uint32_t base_transform) {
		self.base_transform = base_transform;
	}
	TS_JSAPI uint32_t tsTracingBuildIndirect_get_base_transform(const Tracing::BuildIndirect &self) {
		return self.base_transform;
	}
	
	// Tellusim::Tracing
	TS_JSAPI Tracing *tsTracing_new() {
		return new Tracing();
	}
	TS_JSAPI void tsTracing_delete(Tracing *self) {
		delete self;
	}
	TS_JSAPI bool tsTracing_equalPtr(const Tracing &self, const Tracing &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Tracing *tsTracing_clonePtr(const Tracing &self) {
		return new Tracing(self.clonePtr());
	}
	TS_JSAPI void tsTracing_clearPtr(Tracing &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsTracing_destroyPtr(Tracing &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsTracing_acquirePtr(Tracing &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsTracing_unacquirePtr(Tracing &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsTracing_isValidPtr(const Tracing &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsTracing_isOwnerPtr(const Tracing &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsTracing_isConstPtr(const Tracing &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsTracing_getCountPtr(const Tracing &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsTracing_getInternalPtr(const Tracing &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI uint32_t tsTracing_getPlatform(const Tracing &self) {
		return self.getPlatform();
	}
	TS_JSAPI const char* tsTracing_getPlatformName(const Tracing &self) {
		return self.getPlatformName();
	}
	TS_JSAPI uint32_t tsTracing_getIndex(const Tracing &self) {
		return self.getIndex();
	}
	TS_JSAPI void tsTracing_clear(Tracing &self) {
		self.clear();
	}
	TS_JSAPI bool tsTracing_isCreated(const Tracing &self) {
		return self.isCreated();
	}
	TS_JSAPI bool tsTracing_isBuilt(const Tracing &self) {
		return self.isBuilt();
	}
	TS_JSAPI void tsTracing_setName(Tracing &self, const char *name) {
		self.setName(name);
	}
	TS_JSAPI String *tsTracing_getName(const Tracing &self) {
		return new String(self.getName());
	}
	TS_JSAPI bool tsTracing_create(Tracing &self, uint32_t type, uint32_t flags) {
		return self.create((Tracing::Type)type, (Tracing::Flags)flags);
	}
	TS_JSAPI uint32_t tsTracing_getType(const Tracing &self) {
		return self.getType();
	}
	TS_JSAPI const char* tsTracing_getTypeName(uint32_t type) {
		return Tracing::getTypeName((Tracing::Type)type);
	}
	TS_JSAPI const char* tsTracing_getTypeName_1(const Tracing &self) {
		return self.getTypeName();
	}
	TS_JSAPI bool tsTracing_isInstanceType(const Tracing &self) {
		return self.isInstanceType();
	}
	TS_JSAPI bool tsTracing_isTriangleType(const Tracing &self) {
		return self.isTriangleType();
	}
	TS_JSAPI bool tsTracing_isBoundType(const Tracing &self) {
		return self.isBoundType();
	}
	TS_JSAPI bool tsTracing_isGeometryType(const Tracing &self) {
		return self.isGeometryType();
	}
	TS_JSAPI void tsTracing_setParameters(Tracing &self, const Tracing &tracing) {
		self.setParameters(tracing);
	}
	TS_JSAPI uint32_t tsTracing_getNumGeometries(const Tracing &self) {
		return self.getNumGeometries();
	}
	TS_JSAPI void tsTracing_setInstanceBuffer(Tracing &self, uint32_t num_instances, Buffer &buffer, size_t offset) {
		self.setInstanceBuffer(num_instances, buffer, offset);
	}
	TS_JSAPI void tsTracing_setInstanceBuffer_1(Tracing &self, Buffer &buffer, size_t offset) {
		self.setInstanceBuffer(buffer, offset);
	}
	TS_JSAPI void tsTracing_setNumInstances(Tracing &self, uint32_t num_instances) {
		self.setNumInstances(num_instances);
	}
	TS_JSAPI uint32_t tsTracing_getNumInstances(const Tracing &self) {
		return self.getNumInstances();
	}
	TS_JSAPI Buffer *tsTracing_getInstanceBuffer(const Tracing &self) {
		return new Buffer(self.getInstanceBuffer());
	}
	TS_JSAPI size_t tsTracing_getInstanceOffset(const Tracing &self) {
		return self.getInstanceOffset();
	}
	TS_JSAPI uint32_t tsTracing_addVertexBuffer(Tracing &self, uint32_t num_vertices, uint32_t format, size_t stride, Buffer buffer, size_t offset) {
		return self.addVertexBuffer(num_vertices, (Format)format, stride, buffer, offset);
	}
	TS_JSAPI void tsTracing_setVertexBuffer(Tracing &self, uint32_t index, uint32_t num_vertices, Buffer &buffer, size_t offset) {
		self.setVertexBuffer(index, num_vertices, buffer, offset);
	}
	TS_JSAPI void tsTracing_setVertexBuffer_1(Tracing &self, uint32_t index, Buffer &buffer, size_t offset) {
		self.setVertexBuffer(index, buffer, offset);
	}
	TS_JSAPI void tsTracing_setNumVertices(Tracing &self, uint32_t index, uint32_t num_vertices) {
		self.setNumVertices(index, num_vertices);
	}
	TS_JSAPI uint32_t tsTracing_getNumVertices(const Tracing &self, uint32_t index) {
		return self.getNumVertices(index);
	}
	TS_JSAPI uint32_t tsTracing_getVertexFormat(const Tracing &self, uint32_t index) {
		return self.getVertexFormat(index);
	}
	TS_JSAPI uint32_t tsTracing_getVertexStride(const Tracing &self, uint32_t index) {
		return self.getVertexStride(index);
	}
	TS_JSAPI Buffer *tsTracing_getVertexBuffer(const Tracing &self, uint32_t index) {
		return new Buffer(self.getVertexBuffer(index));
	}
	TS_JSAPI size_t tsTracing_getVertexOffset(const Tracing &self, uint32_t index) {
		return self.getVertexOffset(index);
	}
	TS_JSAPI uint32_t tsTracing_addIndexBuffer(Tracing &self, uint32_t num_indices, uint32_t format, Buffer buffer, size_t offset) {
		return self.addIndexBuffer(num_indices, (Format)format, buffer, offset);
	}
	TS_JSAPI void tsTracing_setIndexBuffer(Tracing &self, uint32_t index, uint32_t num_indices, Buffer &buffer, size_t offset) {
		self.setIndexBuffer(index, num_indices, buffer, offset);
	}
	TS_JSAPI void tsTracing_setIndexBuffer_1(Tracing &self, uint32_t index, Buffer &buffer, size_t offset) {
		self.setIndexBuffer(index, buffer, offset);
	}
	TS_JSAPI void tsTracing_setNumIndices(Tracing &self, uint32_t index, uint32_t num_indices) {
		self.setNumIndices(index, num_indices);
	}
	TS_JSAPI uint32_t tsTracing_getNumIndices(const Tracing &self, uint32_t index) {
		return self.getNumIndices(index);
	}
	TS_JSAPI uint32_t tsTracing_getIndexFormat(const Tracing &self, uint32_t index) {
		return self.getIndexFormat(index);
	}
	TS_JSAPI Buffer *tsTracing_getIndexBuffer(const Tracing &self, uint32_t index) {
		return new Buffer(self.getIndexBuffer(index));
	}
	TS_JSAPI size_t tsTracing_getIndexOffset(const Tracing &self, uint32_t index) {
		return self.getIndexOffset(index);
	}
	TS_JSAPI uint32_t tsTracing_addBoundBuffer(Tracing &self, uint32_t num_bounds, size_t stride, Buffer buffer, size_t offset) {
		return self.addBoundBuffer(num_bounds, stride, buffer, offset);
	}
	TS_JSAPI void tsTracing_setBoundBuffer(Tracing &self, uint32_t index, uint32_t num_bounds, Buffer &buffer, size_t offset) {
		self.setBoundBuffer(index, num_bounds, buffer, offset);
	}
	TS_JSAPI void tsTracing_setBoundBuffer_1(Tracing &self, uint32_t index, Buffer &buffer, size_t offset) {
		self.setBoundBuffer(index, buffer, offset);
	}
	TS_JSAPI void tsTracing_setNumBounds(Tracing &self, uint32_t index, uint32_t num_bounds) {
		self.setNumBounds(index, num_bounds);
	}
	TS_JSAPI uint32_t tsTracing_getNumBounds(const Tracing &self, uint32_t index) {
		return self.getNumBounds(index);
	}
	TS_JSAPI uint32_t tsTracing_getBoundStride(const Tracing &self, uint32_t index) {
		return self.getBoundStride(index);
	}
	TS_JSAPI Buffer *tsTracing_getBoundBuffer(const Tracing &self, uint32_t index) {
		return new Buffer(self.getBoundBuffer(index));
	}
	TS_JSAPI size_t tsTracing_getBoundOffset(const Tracing &self, uint32_t index) {
		return self.getBoundOffset(index);
	}
	TS_JSAPI void tsTracing_setIndirectBuffer(Tracing &self, Buffer &buffer, size_t offset) {
		self.setIndirectBuffer(buffer, offset);
	}
	TS_JSAPI Buffer *tsTracing_getIndirectBuffer(const Tracing &self) {
		return new Buffer(self.getIndirectBuffer());
	}
	TS_JSAPI size_t tsTracing_getIndirectOffset(const Tracing &self) {
		return self.getIndirectOffset();
	}
	TS_JSAPI String *tsTracing_getDescription(const Tracing &self) {
		return new String(self.getDescription());
	}
	TS_JSAPI uint64_t tsTracing_getTracingAddress(const Tracing &self) {
		return self.getTracingAddress();
	}
	TS_JSAPI size_t tsTracing_getBuildSize(const Tracing &self) {
		return self.getBuildSize();
	}
	TS_JSAPI size_t tsTracing_getUpdateSize(const Tracing &self) {
		return self.getUpdateSize();
	}
	TS_JSAPI size_t tsTracing_getMemory(const Tracing &self) {
		return self.getMemory();
	}
	
	// Tellusim::Target
	TS_JSAPI Target *tsTarget_new() {
		return new Target();
	}
	TS_JSAPI void tsTarget_delete(Target *self) {
		delete self;
	}
	TS_JSAPI bool tsTarget_equalPtr(const Target &self, const Target &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Target *tsTarget_clonePtr(const Target &self) {
		return new Target(self.clonePtr());
	}
	TS_JSAPI void tsTarget_clearPtr(Target &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsTarget_destroyPtr(Target &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsTarget_acquirePtr(Target &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsTarget_unacquirePtr(Target &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsTarget_isValidPtr(const Target &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsTarget_isOwnerPtr(const Target &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsTarget_isConstPtr(const Target &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsTarget_getCountPtr(const Target &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsTarget_getInternalPtr(const Target &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI uint32_t tsTarget_getPlatform(const Target &self) {
		return self.getPlatform();
	}
	TS_JSAPI const char* tsTarget_getPlatformName(const Target &self) {
		return self.getPlatformName();
	}
	TS_JSAPI uint32_t tsTarget_getIndex(const Target &self) {
		return self.getIndex();
	}
	TS_JSAPI bool tsTarget_begin(Target &self, Fence &fence) {
		return self.begin(fence);
	}
	TS_JSAPI bool tsTarget_begin_1(Target &self) {
		return self.begin();
	}
	TS_JSAPI void tsTarget_end(Target &self, Fence &fence) {
		self.end(fence);
	}
	TS_JSAPI void tsTarget_end_1(Target &self) {
		self.end();
	}
	TS_JSAPI void tsTarget_swap(Target &self, Surface &surface) {
		self.swap(surface);
	}
	TS_JSAPI bool tsTarget_isEnabled(const Target &self) {
		return self.isEnabled();
	}
	TS_JSAPI uint32_t tsTarget_getColorFormat(const Target &self, uint32_t index) {
		return self.getColorFormat(index);
	}
	TS_JSAPI uint32_t tsTarget_getDepthFormat(const Target &self) {
		return self.getDepthFormat();
	}
	TS_JSAPI uint32_t tsTarget_getMultisample(const Target &self) {
		return self.getMultisample();
	}
	TS_JSAPI bool tsTarget_hasMultisample(const Target &self) {
		return self.hasMultisample();
	}
	TS_JSAPI bool tsTarget_isFlipped(const Target &self) {
		return self.isFlipped();
	}
	TS_JSAPI bool tsTarget_isAtomic(const Target &self) {
		return self.isAtomic();
	}
	TS_JSAPI uint32_t tsTarget_getWidth(const Target &self) {
		return self.getWidth();
	}
	TS_JSAPI uint32_t tsTarget_getHeight(const Target &self) {
		return self.getHeight();
	}
	TS_JSAPI uint32_t tsTarget_getDepth(const Target &self) {
		return self.getDepth();
	}
	TS_JSAPI uint32_t tsTarget_getFaces(const Target &self) {
		return self.getFaces();
	}
	TS_JSAPI uint32_t tsTarget_getLayers(const Target &self) {
		return self.getLayers();
	}
	TS_JSAPI uint32_t tsTarget_getMipmaps(const Target &self) {
		return self.getMipmaps();
	}
	TS_JSAPI void tsTarget_setClearColor(Target &self, const Color &color) {
		self.setClearColor(color);
	}
	TS_JSAPI void tsTarget_setClearColor_1(Target &self, uint32_t index, const Color &color) {
		self.setClearColor(index, color);
	}
	TS_JSAPI void tsTarget_setClearColor_2(Target &self, float32_t r, float32_t g, float32_t b, float32_t a) {
		self.setClearColor(r, g, b, a);
	}
	TS_JSAPI void tsTarget_setClearColor_3(Target &self, uint32_t index, float32_t r, float32_t g, float32_t b, float32_t a) {
		self.setClearColor(index, r, g, b, a);
	}
	TS_JSAPI void tsTarget_setColorTexture(Target &self, Texture &texture, uint32_t op, const Slice &slice) {
		self.setColorTexture(texture, (Target::Operation)op, slice);
	}
	TS_JSAPI void tsTarget_setColorTexture_1(Target &self, uint32_t index, Texture &texture, uint32_t op, const Slice &slice) {
		self.setColorTexture(index, texture, (Target::Operation)op, slice);
	}
	TS_JSAPI void tsTarget_setColorResolve(Target &self, Texture &texture, const Slice &slice) {
		self.setColorResolve(texture, slice);
	}
	TS_JSAPI void tsTarget_setColorResolve_1(Target &self, uint32_t index, Texture &texture, const Slice &slice) {
		self.setColorResolve(index, texture, slice);
	}
	TS_JSAPI uint32_t tsTarget_getNumTargets(const Target &self) {
		return self.getNumTargets();
	}
	TS_JSAPI const Color *tsTarget_getClearColor(const Target &self, uint32_t index) {
		return new Color(self.getClearColor(index));
	}
	TS_JSAPI uint32_t tsTarget_getColorOp(const Target &self, uint32_t index) {
		return self.getColorOp(index);
	}
	TS_JSAPI Texture *tsTarget_getColorTexture(const Target &self, uint32_t index) {
		return new Texture(self.getColorTexture(index));
	}
	TS_JSAPI Texture *tsTarget_getColorResolve(const Target &self, uint32_t index) {
		return new Texture(self.getColorResolve(index));
	}
	TS_JSAPI const Slice *tsTarget_getColorTextureSlice(const Target &self, uint32_t index) {
		return new Slice(self.getColorTextureSlice(index));
	}
	TS_JSAPI const Slice *tsTarget_getColorResolveSlice(const Target &self, uint32_t index) {
		return new Slice(self.getColorResolveSlice(index));
	}
	TS_JSAPI void tsTarget_setClearDepth(Target &self, float32_t depth, uint32_t stencil) {
		self.setClearDepth(depth, stencil);
	}
	TS_JSAPI void tsTarget_setDepthTexture(Target &self, Texture &texture, uint32_t op, const Slice &slice) {
		self.setDepthTexture(texture, (Target::Operation)op, slice);
	}
	TS_JSAPI void tsTarget_setDepthResolve(Target &self, Texture &texture, const Slice &slice) {
		self.setDepthResolve(texture, slice);
	}
	TS_JSAPI float32_t tsTarget_getClearDepth(const Target &self) {
		return self.getClearDepth();
	}
	TS_JSAPI uint32_t tsTarget_getClearStencil(const Target &self) {
		return self.getClearStencil();
	}
	TS_JSAPI uint32_t tsTarget_getDepthOp(const Target &self) {
		return self.getDepthOp();
	}
	TS_JSAPI Texture *tsTarget_getDepthTexture(const Target &self) {
		return new Texture(self.getDepthTexture());
	}
	TS_JSAPI Texture *tsTarget_getDepthResolve(const Target &self) {
		return new Texture(self.getDepthResolve());
	}
	TS_JSAPI const Slice *tsTarget_getDepthTextureSlice(const Target &self) {
		return new Slice(self.getDepthTextureSlice());
	}
	TS_JSAPI const Slice *tsTarget_getDepthResolveSlice(const Target &self) {
		return new Slice(self.getDepthResolveSlice());
	}
	
	// Tellusim::GLESTarget
	TS_JSAPI GLESTarget *tsGLESTarget_new() {
		return new GLESTarget();
	}
	TS_JSAPI void tsGLESTarget_delete(GLESTarget *self) {
		delete self;
	}
	TS_JSAPI bool tsGLESTarget_equalTargetPtr(const GLESTarget &self, const Target &base) {
		return self.operator==(base);
	}
	TS_JSAPI GLESTarget *tsGLESTarget_castTargetPtr(const Target &self) {
		return new GLESTarget(self);
	}
	TS_JSAPI Target *tsGLESTarget_baseTargetPtr(const GLESTarget &self) {
		return new Target(self.getTarget());
	}
	TS_JSAPI uint32_t tsGLESTarget_getFramebufferID(const GLESTarget &self) {
		return self.getFramebufferID();
	}
	
	// Tellusim::Device::Features
	TS_JSAPI Device::Features *tsDeviceFeatures_new() {
		return new Device::Features();
	}
	TS_JSAPI Device::Features *tsDeviceFeatures_copy(const Device::Features &self) {
		return new Device::Features(self);
	}
	TS_JSAPI void tsDeviceFeatures_delete(Device::Features *self) {
		delete self;
	}
	TS_JSAPI void tsDeviceFeatures_set_threadAccess(Device::Features &self, bool threadAccess) {
		self.threadAccess = threadAccess;
	}
	TS_JSAPI bool tsDeviceFeatures_get_threadAccess(const Device::Features &self) {
		return self.threadAccess;
	}
	TS_JSAPI void tsDeviceFeatures_set_bufferTable(Device::Features &self, bool bufferTable) {
		self.bufferTable = bufferTable;
	}
	TS_JSAPI bool tsDeviceFeatures_get_bufferTable(const Device::Features &self) {
		return self.bufferTable;
	}
	TS_JSAPI void tsDeviceFeatures_set_bufferSparse(Device::Features &self, bool bufferSparse) {
		self.bufferSparse = bufferSparse;
	}
	TS_JSAPI bool tsDeviceFeatures_get_bufferSparse(const Device::Features &self) {
		return self.bufferSparse;
	}
	TS_JSAPI void tsDeviceFeatures_set_textureTable(Device::Features &self, bool textureTable) {
		self.textureTable = textureTable;
	}
	TS_JSAPI bool tsDeviceFeatures_get_textureTable(const Device::Features &self) {
		return self.textureTable;
	}
	TS_JSAPI void tsDeviceFeatures_set_textureSparse(Device::Features &self, bool textureSparse) {
		self.textureSparse = textureSparse;
	}
	TS_JSAPI bool tsDeviceFeatures_get_textureSparse(const Device::Features &self) {
		return self.textureSparse;
	}
	TS_JSAPI void tsDeviceFeatures_set_textureArrayCube(Device::Features &self, bool textureArrayCube) {
		self.textureArrayCube = textureArrayCube;
	}
	TS_JSAPI bool tsDeviceFeatures_get_textureArrayCube(const Device::Features &self) {
		return self.textureArrayCube;
	}
	TS_JSAPI void tsDeviceFeatures_set_textureArraySparse(Device::Features &self, bool textureArraySparse) {
		self.textureArraySparse = textureArraySparse;
	}
	TS_JSAPI bool tsDeviceFeatures_get_textureArraySparse(const Device::Features &self) {
		return self.textureArraySparse;
	}
	TS_JSAPI void tsDeviceFeatures_set_surfaceMultisample(Device::Features &self, bool surfaceMultisample) {
		self.surfaceMultisample = surfaceMultisample;
	}
	TS_JSAPI bool tsDeviceFeatures_get_surfaceMultisample(const Device::Features &self) {
		return self.surfaceMultisample;
	}
	TS_JSAPI void tsDeviceFeatures_set_drawBaseInstance(Device::Features &self, bool drawBaseInstance) {
		self.drawBaseInstance = drawBaseInstance;
	}
	TS_JSAPI bool tsDeviceFeatures_get_drawBaseInstance(const Device::Features &self) {
		return self.drawBaseInstance;
	}
	TS_JSAPI void tsDeviceFeatures_set_drawIndirectIndex(Device::Features &self, bool drawIndirectIndex) {
		self.drawIndirectIndex = drawIndirectIndex;
	}
	TS_JSAPI bool tsDeviceFeatures_get_drawIndirectIndex(const Device::Features &self) {
		return self.drawIndirectIndex;
	}
	TS_JSAPI void tsDeviceFeatures_set_drawIndirectCount(Device::Features &self, bool drawIndirectCount) {
		self.drawIndirectCount = drawIndirectCount;
	}
	TS_JSAPI bool tsDeviceFeatures_get_drawIndirectCount(const Device::Features &self) {
		return self.drawIndirectCount;
	}
	TS_JSAPI void tsDeviceFeatures_set_taskIndirectCount(Device::Features &self, bool taskIndirectCount) {
		self.taskIndirectCount = taskIndirectCount;
	}
	TS_JSAPI bool tsDeviceFeatures_get_taskIndirectCount(const Device::Features &self) {
		return self.taskIndirectCount;
	}
	TS_JSAPI void tsDeviceFeatures_set_vertexStorage(Device::Features &self, bool vertexStorage) {
		self.vertexStorage = vertexStorage;
	}
	TS_JSAPI bool tsDeviceFeatures_get_vertexStorage(const Device::Features &self) {
		return self.vertexStorage;
	}
	TS_JSAPI void tsDeviceFeatures_set_vertexIndexLayer(Device::Features &self, bool vertexIndexLayer) {
		self.vertexIndexLayer = vertexIndexLayer;
	}
	TS_JSAPI bool tsDeviceFeatures_get_vertexIndexLayer(const Device::Features &self) {
		return self.vertexIndexLayer;
	}
	TS_JSAPI void tsDeviceFeatures_set_geometryPassthrough(Device::Features &self, bool geometryPassthrough) {
		self.geometryPassthrough = geometryPassthrough;
	}
	TS_JSAPI bool tsDeviceFeatures_get_geometryPassthrough(const Device::Features &self) {
		return self.geometryPassthrough;
	}
	TS_JSAPI void tsDeviceFeatures_set_fragmentBarycentric(Device::Features &self, bool fragmentBarycentric) {
		self.fragmentBarycentric = fragmentBarycentric;
	}
	TS_JSAPI bool tsDeviceFeatures_get_fragmentBarycentric(const Device::Features &self) {
		return self.fragmentBarycentric;
	}
	TS_JSAPI void tsDeviceFeatures_set_fragmentStencilExport(Device::Features &self, bool fragmentStencilExport) {
		self.fragmentStencilExport = fragmentStencilExport;
	}
	TS_JSAPI bool tsDeviceFeatures_get_fragmentStencilExport(const Device::Features &self) {
		return self.fragmentStencilExport;
	}
	TS_JSAPI void tsDeviceFeatures_set_blendDualSource(Device::Features &self, bool blendDualSource) {
		self.blendDualSource = blendDualSource;
	}
	TS_JSAPI bool tsDeviceFeatures_get_blendDualSource(const Device::Features &self) {
		return self.blendDualSource;
	}
	TS_JSAPI void tsDeviceFeatures_set_depthRangeOneToOne(Device::Features &self, bool depthRangeOneToOne) {
		self.depthRangeOneToOne = depthRangeOneToOne;
	}
	TS_JSAPI bool tsDeviceFeatures_get_depthRangeOneToOne(const Device::Features &self) {
		return self.depthRangeOneToOne;
	}
	TS_JSAPI void tsDeviceFeatures_set_rasterConservative(Device::Features &self, bool rasterConservative) {
		self.rasterConservative = rasterConservative;
	}
	TS_JSAPI bool tsDeviceFeatures_get_rasterConservative(const Device::Features &self) {
		return self.rasterConservative;
	}
	TS_JSAPI void tsDeviceFeatures_set_renderConditional(Device::Features &self, bool renderConditional) {
		self.renderConditional = renderConditional;
	}
	TS_JSAPI bool tsDeviceFeatures_get_renderConditional(const Device::Features &self) {
		return self.renderConditional;
	}
	TS_JSAPI void tsDeviceFeatures_set_computeTracing(Device::Features &self, bool computeTracing) {
		self.computeTracing = computeTracing;
	}
	TS_JSAPI bool tsDeviceFeatures_get_computeTracing(const Device::Features &self) {
		return self.computeTracing;
	}
	TS_JSAPI void tsDeviceFeatures_set_fragmentTracing(Device::Features &self, bool fragmentTracing) {
		self.fragmentTracing = fragmentTracing;
	}
	TS_JSAPI bool tsDeviceFeatures_get_fragmentTracing(const Device::Features &self) {
		return self.fragmentTracing;
	}
	TS_JSAPI void tsDeviceFeatures_set_traversalTracing(Device::Features &self, bool traversalTracing) {
		self.traversalTracing = traversalTracing;
	}
	TS_JSAPI bool tsDeviceFeatures_get_traversalTracing(const Device::Features &self) {
		return self.traversalTracing;
	}
	TS_JSAPI void tsDeviceFeatures_set_buildIndirectTracing(Device::Features &self, bool buildIndirectTracing) {
		self.buildIndirectTracing = buildIndirectTracing;
	}
	TS_JSAPI bool tsDeviceFeatures_get_buildIndirectTracing(const Device::Features &self) {
		return self.buildIndirectTracing;
	}
	TS_JSAPI void tsDeviceFeatures_set_maxTraversalDepth(Device::Features &self, uint32_t maxTraversalDepth) {
		self.maxTraversalDepth = maxTraversalDepth;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_maxTraversalDepth(const Device::Features &self) {
		return self.maxTraversalDepth;
	}
	TS_JSAPI void tsDeviceFeatures_set_subgroupVote(Device::Features &self, bool subgroupVote) {
		self.subgroupVote = subgroupVote;
	}
	TS_JSAPI bool tsDeviceFeatures_get_subgroupVote(const Device::Features &self) {
		return self.subgroupVote;
	}
	TS_JSAPI void tsDeviceFeatures_set_subgroupMath(Device::Features &self, bool subgroupMath) {
		self.subgroupMath = subgroupMath;
	}
	TS_JSAPI bool tsDeviceFeatures_get_subgroupMath(const Device::Features &self) {
		return self.subgroupMath;
	}
	TS_JSAPI void tsDeviceFeatures_set_subgroupShuffle(Device::Features &self, bool subgroupShuffle) {
		self.subgroupShuffle = subgroupShuffle;
	}
	TS_JSAPI bool tsDeviceFeatures_get_subgroupShuffle(const Device::Features &self) {
		return self.subgroupShuffle;
	}
	TS_JSAPI void tsDeviceFeatures_set_subgroupSize(Device::Features &self, uint32_t subgroupSize) {
		self.subgroupSize = subgroupSize;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_subgroupSize(const Device::Features &self) {
		return self.subgroupSize;
	}
	TS_JSAPI void tsDeviceFeatures_set_minSubgroupSize(Device::Features &self, uint32_t minSubgroupSize) {
		self.minSubgroupSize = minSubgroupSize;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_minSubgroupSize(const Device::Features &self) {
		return self.minSubgroupSize;
	}
	TS_JSAPI void tsDeviceFeatures_set_maxSubgroupSize(Device::Features &self, uint32_t maxSubgroupSize) {
		self.maxSubgroupSize = maxSubgroupSize;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_maxSubgroupSize(const Device::Features &self) {
		return self.maxSubgroupSize;
	}
	TS_JSAPI void tsDeviceFeatures_set_shaderu8(Device::Features &self, bool shaderu8) {
		self.shaderu8 = shaderu8;
	}
	TS_JSAPI bool tsDeviceFeatures_get_shaderu8(const Device::Features &self) {
		return self.shaderu8;
	}
	TS_JSAPI void tsDeviceFeatures_set_shaderf16(Device::Features &self, bool shaderf16) {
		self.shaderf16 = shaderf16;
	}
	TS_JSAPI bool tsDeviceFeatures_get_shaderf16(const Device::Features &self) {
		return self.shaderf16;
	}
	TS_JSAPI void tsDeviceFeatures_set_shaderu16(Device::Features &self, bool shaderu16) {
		self.shaderu16 = shaderu16;
	}
	TS_JSAPI bool tsDeviceFeatures_get_shaderu16(const Device::Features &self) {
		return self.shaderu16;
	}
	TS_JSAPI void tsDeviceFeatures_set_shaderf64(Device::Features &self, bool shaderf64) {
		self.shaderf64 = shaderf64;
	}
	TS_JSAPI bool tsDeviceFeatures_get_shaderf64(const Device::Features &self) {
		return self.shaderf64;
	}
	TS_JSAPI void tsDeviceFeatures_set_shaderu64(Device::Features &self, bool shaderu64) {
		self.shaderu64 = shaderu64;
	}
	TS_JSAPI bool tsDeviceFeatures_get_shaderu64(const Device::Features &self) {
		return self.shaderu64;
	}
	TS_JSAPI void tsDeviceFeatures_set_atomicGroupf32(Device::Features &self, bool atomicGroupf32) {
		self.atomicGroupf32 = atomicGroupf32;
	}
	TS_JSAPI bool tsDeviceFeatures_get_atomicGroupf32(const Device::Features &self) {
		return self.atomicGroupf32;
	}
	TS_JSAPI void tsDeviceFeatures_set_atomicGroupu64(Device::Features &self, bool atomicGroupu64) {
		self.atomicGroupu64 = atomicGroupu64;
	}
	TS_JSAPI bool tsDeviceFeatures_get_atomicGroupu64(const Device::Features &self) {
		return self.atomicGroupu64;
	}
	TS_JSAPI void tsDeviceFeatures_set_atomicBufferf32(Device::Features &self, bool atomicBufferf32) {
		self.atomicBufferf32 = atomicBufferf32;
	}
	TS_JSAPI bool tsDeviceFeatures_get_atomicBufferf32(const Device::Features &self) {
		return self.atomicBufferf32;
	}
	TS_JSAPI void tsDeviceFeatures_set_atomicBufferu64(Device::Features &self, bool atomicBufferu64) {
		self.atomicBufferu64 = atomicBufferu64;
	}
	TS_JSAPI bool tsDeviceFeatures_get_atomicBufferu64(const Device::Features &self) {
		return self.atomicBufferu64;
	}
	TS_JSAPI void tsDeviceFeatures_set_atomicTexturef32(Device::Features &self, bool atomicTexturef32) {
		self.atomicTexturef32 = atomicTexturef32;
	}
	TS_JSAPI bool tsDeviceFeatures_get_atomicTexturef32(const Device::Features &self) {
		return self.atomicTexturef32;
	}
	TS_JSAPI void tsDeviceFeatures_set_atomicTextureu32(Device::Features &self, bool atomicTextureu32) {
		self.atomicTextureu32 = atomicTextureu32;
	}
	TS_JSAPI bool tsDeviceFeatures_get_atomicTextureu32(const Device::Features &self) {
		return self.atomicTextureu32;
	}
	TS_JSAPI void tsDeviceFeatures_set_atomicTextureu64(Device::Features &self, bool atomicTextureu64) {
		self.atomicTextureu64 = atomicTextureu64;
	}
	TS_JSAPI bool tsDeviceFeatures_get_atomicTextureu64(const Device::Features &self) {
		return self.atomicTextureu64;
	}
	TS_JSAPI void tsDeviceFeatures_set_matrix16f16(Device::Features &self, bool matrix16f16) {
		self.matrix16f16 = matrix16f16;
	}
	TS_JSAPI bool tsDeviceFeatures_get_matrix16f16(const Device::Features &self) {
		return self.matrix16f16;
	}
	TS_JSAPI void tsDeviceFeatures_set_matrix16x8x8f16(Device::Features &self, bool matrix16x8x8f16) {
		self.matrix16x8x8f16 = matrix16x8x8f16;
	}
	TS_JSAPI bool tsDeviceFeatures_get_matrix16x8x8f16(const Device::Features &self) {
		return self.matrix16x8x8f16;
	}
	TS_JSAPI void tsDeviceFeatures_set_matrix8x16x16f16(Device::Features &self, bool matrix8x16x16f16) {
		self.matrix8x16x16f16 = matrix8x16x16f16;
	}
	TS_JSAPI bool tsDeviceFeatures_get_matrix8x16x16f16(const Device::Features &self) {
		return self.matrix8x16x16f16;
	}
	TS_JSAPI void tsDeviceFeatures_set_matrix16x8x16f16(Device::Features &self, bool matrix16x8x16f16) {
		self.matrix16x8x16f16 = matrix16x8x16f16;
	}
	TS_JSAPI bool tsDeviceFeatures_get_matrix16x8x16f16(const Device::Features &self) {
		return self.matrix16x8x16f16;
	}
	TS_JSAPI void tsDeviceFeatures_set_matrix16f16f32(Device::Features &self, bool matrix16f16f32) {
		self.matrix16f16f32 = matrix16f16f32;
	}
	TS_JSAPI bool tsDeviceFeatures_get_matrix16f16f32(const Device::Features &self) {
		return self.matrix16f16f32;
	}
	TS_JSAPI void tsDeviceFeatures_set_matrix16x8x8f16f32(Device::Features &self, bool matrix16x8x8f16f32) {
		self.matrix16x8x8f16f32 = matrix16x8x8f16f32;
	}
	TS_JSAPI bool tsDeviceFeatures_get_matrix16x8x8f16f32(const Device::Features &self) {
		return self.matrix16x8x8f16f32;
	}
	TS_JSAPI void tsDeviceFeatures_set_matrix8x16x16f16f32(Device::Features &self, bool matrix8x16x16f16f32) {
		self.matrix8x16x16f16f32 = matrix8x16x16f16f32;
	}
	TS_JSAPI bool tsDeviceFeatures_get_matrix8x16x16f16f32(const Device::Features &self) {
		return self.matrix8x16x16f16f32;
	}
	TS_JSAPI void tsDeviceFeatures_set_matrix16x8x16f16f32(Device::Features &self, bool matrix16x8x16f16f32) {
		self.matrix16x8x16f16f32 = matrix16x8x16f16f32;
	}
	TS_JSAPI bool tsDeviceFeatures_get_matrix16x8x16f16f32(const Device::Features &self) {
		return self.matrix16x8x16f16f32;
	}
	TS_JSAPI void tsDeviceFeatures_set_uniformAlignment(Device::Features &self, uint32_t uniformAlignment) {
		self.uniformAlignment = uniformAlignment;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_uniformAlignment(const Device::Features &self) {
		return self.uniformAlignment;
	}
	TS_JSAPI void tsDeviceFeatures_set_storageAlignment(Device::Features &self, uint32_t storageAlignment) {
		self.storageAlignment = storageAlignment;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_storageAlignment(const Device::Features &self) {
		return self.storageAlignment;
	}
	TS_JSAPI void tsDeviceFeatures_set_maxTexture2DSize(Device::Features &self, uint32_t maxTexture2DSize) {
		self.maxTexture2DSize = maxTexture2DSize;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_maxTexture2DSize(const Device::Features &self) {
		return self.maxTexture2DSize;
	}
	TS_JSAPI void tsDeviceFeatures_set_maxTexture3DSize(Device::Features &self, uint32_t maxTexture3DSize) {
		self.maxTexture3DSize = maxTexture3DSize;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_maxTexture3DSize(const Device::Features &self) {
		return self.maxTexture3DSize;
	}
	TS_JSAPI void tsDeviceFeatures_set_maxTextureLayers(Device::Features &self, uint32_t maxTextureLayers) {
		self.maxTextureLayers = maxTextureLayers;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_maxTextureLayers(const Device::Features &self) {
		return self.maxTextureLayers;
	}
	TS_JSAPI void tsDeviceFeatures_set_maxTextureSamples(Device::Features &self, uint32_t maxTextureSamples) {
		self.maxTextureSamples = maxTextureSamples;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_maxTextureSamples(const Device::Features &self) {
		return self.maxTextureSamples;
	}
	TS_JSAPI void tsDeviceFeatures_set_maxGroupSizeX(Device::Features &self, uint32_t maxGroupSizeX) {
		self.maxGroupSizeX = maxGroupSizeX;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_maxGroupSizeX(const Device::Features &self) {
		return self.maxGroupSizeX;
	}
	TS_JSAPI void tsDeviceFeatures_set_maxGroupSizeY(Device::Features &self, uint32_t maxGroupSizeY) {
		self.maxGroupSizeY = maxGroupSizeY;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_maxGroupSizeY(const Device::Features &self) {
		return self.maxGroupSizeY;
	}
	TS_JSAPI void tsDeviceFeatures_set_maxGroupSizeZ(Device::Features &self, uint32_t maxGroupSizeZ) {
		self.maxGroupSizeZ = maxGroupSizeZ;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_maxGroupSizeZ(const Device::Features &self) {
		return self.maxGroupSizeZ;
	}
	TS_JSAPI void tsDeviceFeatures_set_maxGroupCountX(Device::Features &self, uint32_t maxGroupCountX) {
		self.maxGroupCountX = maxGroupCountX;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_maxGroupCountX(const Device::Features &self) {
		return self.maxGroupCountX;
	}
	TS_JSAPI void tsDeviceFeatures_set_maxGroupCountY(Device::Features &self, uint32_t maxGroupCountY) {
		self.maxGroupCountY = maxGroupCountY;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_maxGroupCountY(const Device::Features &self) {
		return self.maxGroupCountY;
	}
	TS_JSAPI void tsDeviceFeatures_set_maxGroupCountZ(Device::Features &self, uint32_t maxGroupCountZ) {
		self.maxGroupCountZ = maxGroupCountZ;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_maxGroupCountZ(const Device::Features &self) {
		return self.maxGroupCountZ;
	}
	TS_JSAPI void tsDeviceFeatures_set_maxTaskCount(Device::Features &self, uint32_t maxTaskCount) {
		self.maxTaskCount = maxTaskCount;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_maxTaskCount(const Device::Features &self) {
		return self.maxTaskCount;
	}
	TS_JSAPI void tsDeviceFeatures_set_maxTaskMemory(Device::Features &self, uint32_t maxTaskMemory) {
		self.maxTaskMemory = maxTaskMemory;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_maxTaskMemory(const Device::Features &self) {
		return self.maxTaskMemory;
	}
	TS_JSAPI void tsDeviceFeatures_set_maxTaskMeshes(Device::Features &self, uint32_t maxTaskMeshes) {
		self.maxTaskMeshes = maxTaskMeshes;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_maxTaskMeshes(const Device::Features &self) {
		return self.maxTaskMeshes;
	}
	TS_JSAPI void tsDeviceFeatures_set_maxMeshMemory(Device::Features &self, uint32_t maxMeshMemory) {
		self.maxMeshMemory = maxMeshMemory;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_maxMeshMemory(const Device::Features &self) {
		return self.maxMeshMemory;
	}
	TS_JSAPI void tsDeviceFeatures_set_maxMeshVertices(Device::Features &self, uint32_t maxMeshVertices) {
		self.maxMeshVertices = maxMeshVertices;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_maxMeshVertices(const Device::Features &self) {
		return self.maxMeshVertices;
	}
	TS_JSAPI void tsDeviceFeatures_set_maxMeshPrimitives(Device::Features &self, uint32_t maxMeshPrimitives) {
		self.maxMeshPrimitives = maxMeshPrimitives;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_maxMeshPrimitives(const Device::Features &self) {
		return self.maxMeshPrimitives;
	}
	TS_JSAPI void tsDeviceFeatures_set_maxViewportCount(Device::Features &self, uint32_t maxViewportCount) {
		self.maxViewportCount = maxViewportCount;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_maxViewportCount(const Device::Features &self) {
		return self.maxViewportCount;
	}
	TS_JSAPI void tsDeviceFeatures_set_maxClipCullCount(Device::Features &self, uint32_t maxClipCullCount) {
		self.maxClipCullCount = maxClipCullCount;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_maxClipCullCount(const Device::Features &self) {
		return self.maxClipCullCount;
	}
	TS_JSAPI void tsDeviceFeatures_set_maxUniformSize(Device::Features &self, uint64_t maxUniformSize) {
		self.maxUniformSize = maxUniformSize;
	}
	TS_JSAPI uint64_t tsDeviceFeatures_get_maxUniformSize(const Device::Features &self) {
		return self.maxUniformSize;
	}
	TS_JSAPI void tsDeviceFeatures_set_maxStorageSize(Device::Features &self, uint64_t maxStorageSize) {
		self.maxStorageSize = maxStorageSize;
	}
	TS_JSAPI uint64_t tsDeviceFeatures_get_maxStorageSize(const Device::Features &self) {
		return self.maxStorageSize;
	}
	TS_JSAPI void tsDeviceFeatures_set_groupMemory(Device::Features &self, uint32_t groupMemory) {
		self.groupMemory = groupMemory;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_groupMemory(const Device::Features &self) {
		return self.groupMemory;
	}
	TS_JSAPI void tsDeviceFeatures_set_videoMemory(Device::Features &self, uint64_t videoMemory) {
		self.videoMemory = videoMemory;
	}
	TS_JSAPI uint64_t tsDeviceFeatures_get_videoMemory(const Device::Features &self) {
		return self.videoMemory;
	}
	TS_JSAPI void tsDeviceFeatures_set_vendorID(Device::Features &self, uint32_t vendorID) {
		self.vendorID = vendorID;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_vendorID(const Device::Features &self) {
		return self.vendorID;
	}
	TS_JSAPI void tsDeviceFeatures_set_deviceID(Device::Features &self, uint32_t deviceID) {
		self.deviceID = deviceID;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_deviceID(const Device::Features &self) {
		return self.deviceID;
	}
	TS_JSAPI void tsDeviceFeatures_set_pciBusID(Device::Features &self, uint32_t pciBusID) {
		self.pciBusID = pciBusID;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_pciBusID(const Device::Features &self) {
		return self.pciBusID;
	}
	TS_JSAPI void tsDeviceFeatures_set_pciDomainID(Device::Features &self, uint32_t pciDomainID) {
		self.pciDomainID = pciDomainID;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_pciDomainID(const Device::Features &self) {
		return self.pciDomainID;
	}
	TS_JSAPI void tsDeviceFeatures_set_pciDeviceID(Device::Features &self, uint32_t pciDeviceID) {
		self.pciDeviceID = pciDeviceID;
	}
	TS_JSAPI uint32_t tsDeviceFeatures_get_pciDeviceID(const Device::Features &self) {
		return self.pciDeviceID;
	}
	
	// Tellusim::Device
	TS_JSAPI Device *tsDevice_new() {
		return new Device();
	}
	TS_JSAPI Device *tsDevice_new_1(Context &context) {
		return new Device(context);
	}
	TS_JSAPI Device *tsDevice_new_2(Surface &surface) {
		return new Device(surface);
	}
	TS_JSAPI Device *tsDevice_new_3(Window &window) {
		return new Device(window);
	}
	TS_JSAPI void tsDevice_delete(Device *self) {
		delete self;
	}
	TS_JSAPI bool tsDevice_equalPtr(const Device &self, const Device &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Device *tsDevice_clonePtr(const Device &self) {
		return new Device(self.clonePtr());
	}
	TS_JSAPI void tsDevice_clearPtr(Device &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsDevice_destroyPtr(Device &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsDevice_acquirePtr(Device &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsDevice_unacquirePtr(Device &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsDevice_isValidPtr(const Device &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsDevice_isOwnerPtr(const Device &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsDevice_isConstPtr(const Device &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsDevice_getCountPtr(const Device &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsDevice_getInternalPtr(const Device &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI uint32_t tsDevice_getPlatform(const Device &self) {
		return self.getPlatform();
	}
	TS_JSAPI const char* tsDevice_getPlatformName(const Device &self) {
		return self.getPlatformName();
	}
	TS_JSAPI uint32_t tsDevice_getIndex(const Device &self) {
		return self.getIndex();
	}
	TS_JSAPI String *tsDevice_getName(const Device &self) {
		return new String(self.getName());
	}
	TS_JSAPI String *tsDevice_getVendor(const Device &self) {
		return new String(self.getVendor());
	}
	TS_JSAPI String *tsDevice_getVersion(const Device &self) {
		return new String(self.getVersion());
	}
	TS_JSAPI const Device::Features *tsDevice_getFeatures(const Device &self) {
		return new Device::Features(self.getFeatures());
	}
	TS_JSAPI bool tsDevice_hasQuery(const Device &self, uint32_t type) {
		return self.hasQuery((Query::Type)type);
	}
	TS_JSAPI bool tsDevice_hasShader(const Device &self, uint32_t type) {
		return self.hasShader((Shader::Type)type);
	}
	TS_JSAPI bool tsDevice_hasTarget(const Device &self, uint32_t format) {
		return self.hasTarget((Format)format);
	}
	TS_JSAPI bool tsDevice_hasTexture(const Device &self, uint32_t format) {
		return self.hasTexture((Format)format);
	}
	TS_JSAPI bool tsDevice_hasSurface(const Device &self, uint32_t format) {
		return self.hasSurface((Format)format);
	}
	TS_JSAPI Device *tsDevice_createDevice(const Device &self, uint32_t index, uint32_t frames) {
		return new Device(self.createDevice(index, frames));
	}
	TS_JSAPI Device *tsDevice_createCommandDevice(const Device &self, uint32_t frames) {
		return new Device(self.createCommandDevice(frames));
	}
	TS_JSAPI Device *tsDevice_createComputeDevice(const Device &self, uint32_t frames) {
		return new Device(self.createComputeDevice(frames));
	}
	TS_JSAPI Device *tsDevice_createCopyDevice(const Device &self, uint32_t frames) {
		return new Device(self.createCopyDevice(frames));
	}
	TS_JSAPI Query *tsDevice_createQuery(const Device &self) {
		return new Query(self.createQuery());
	}
	TS_JSAPI Query *tsDevice_createQuery_1(const Device &self, uint32_t type) {
		return new Query(self.createQuery((Query::Type)type));
	}
	TS_JSAPI Fence *tsDevice_createFence(const Device &self) {
		return new Fence(self.createFence());
	}
	TS_JSAPI Fence *tsDevice_createFence_1(const Device &self, Fence &shared) {
		return new Fence(self.createFence(shared));
	}
	TS_JSAPI Fence *tsDevice_createFence_2(const Device &self, uint32_t flags) {
		return new Fence(self.createFence((Fence::Flags)flags));
	}
	TS_JSAPI Buffer *tsDevice_createBuffer(const Device &self) {
		return new Buffer(self.createBuffer());
	}
	TS_JSAPI Buffer *tsDevice_createBuffer_1(const Device &self, Buffer &shared) {
		return new Buffer(self.createBuffer(shared));
	}
	TS_JSAPI Buffer *tsDevice_createBuffer_2(const Device &self, uint32_t flags, size_t size, uint32_t format) {
		return new Buffer(self.createBuffer((Buffer::Flags)flags, size, (Format)format));
	}
	TS_JSAPI Buffer *tsDevice_createBuffer_3(const Device &self, uint32_t flags, const void *src, size_t size, uint32_t format) {
		return new Buffer(self.createBuffer((Buffer::Flags)flags, src, size, (Format)format));
	}
	TS_JSAPI Sampler *tsDevice_createSampler(const Device &self) {
		return new Sampler(self.createSampler());
	}
	TS_JSAPI Sampler *tsDevice_createSampler_1(const Device &self, const Sampler &sampler) {
		return new Sampler(self.createSampler(sampler));
	}
	TS_JSAPI Sampler *tsDevice_createSampler_2(const Device &self, uint32_t filter, uint32_t mode, uint32_t anisotropy) {
		return new Sampler(self.createSampler((Sampler::Filter)filter, (Sampler::WrapMode)mode, anisotropy));
	}
	TS_JSAPI Texture *tsDevice_createTexture(const Device &self) {
		return new Texture(self.createTexture());
	}
	TS_JSAPI Texture *tsDevice_createTexture_1(const Device &self, Texture &shared) {
		return new Texture(self.createTexture(shared));
	}
	TS_JSAPI Texture *tsDevice_createTexture_2(const Device &self, uint32_t type, uint32_t format, const Size &size, uint32_t layers, uint32_t flags) {
		return new Texture(self.createTexture((Texture::Type)type, (Format)format, size, layers, (Texture::Flags)flags));
	}
	TS_JSAPI Texture *tsDevice_createTexture_3(const Device &self, uint32_t type, uint32_t format, const Size &size, uint32_t flags) {
		return new Texture(self.createTexture((Texture::Type)type, (Format)format, size, (Texture::Flags)flags));
	}
	TS_JSAPI Texture *tsDevice_createTexture_4(const Device &self, const Image &image, uint32_t flags, Async *async) {
		return new Texture(self.createTexture(image, (Texture::Flags)flags, async));
	}
	TS_JSAPI Texture *tsDevice_createTexture2D(const Device &self, uint32_t format, uint32_t size, uint32_t flags) {
		return new Texture(self.createTexture2D((Format)format, size, (Texture::Flags)flags));
	}
	TS_JSAPI Texture *tsDevice_createTexture3D(const Device &self, uint32_t format, uint32_t size, uint32_t flags) {
		return new Texture(self.createTexture3D((Format)format, size, (Texture::Flags)flags));
	}
	TS_JSAPI Texture *tsDevice_createTextureCube(const Device &self, uint32_t format, uint32_t size, uint32_t flags) {
		return new Texture(self.createTextureCube((Format)format, size, (Texture::Flags)flags));
	}
	TS_JSAPI Texture *tsDevice_createTexture2D_1(const Device &self, uint32_t format, uint32_t width, uint32_t height, uint32_t flags) {
		return new Texture(self.createTexture2D((Format)format, width, height, (Texture::Flags)flags));
	}
	TS_JSAPI Texture *tsDevice_createTexture3D_1(const Device &self, uint32_t format, uint32_t width, uint32_t height, uint32_t depth, uint32_t flags) {
		return new Texture(self.createTexture3D((Format)format, width, height, depth, (Texture::Flags)flags));
	}
	TS_JSAPI Texture *tsDevice_createTexture2D_2(const Device &self, uint32_t format, uint32_t width, uint32_t height, uint32_t layers, uint32_t flags) {
		return new Texture(self.createTexture2D((Format)format, width, height, layers, (Texture::Flags)flags));
	}
	TS_JSAPI Texture *tsDevice_createTextureCube_1(const Device &self, uint32_t format, uint32_t size, uint32_t layers, uint32_t flags) {
		return new Texture(self.createTextureCube((Format)format, size, layers, (Texture::Flags)flags));
	}
	TS_JSAPI Texture *tsDevice_loadTexture(const Device &self, const char *name, uint32_t flags, uint32_t image_flags, uint32_t offset, Async *async) {
		return new Texture(self.loadTexture(name, (Texture::Flags)flags, (Image::Flags)image_flags, offset, async));
	}
	TS_JSAPI Texture *tsDevice_loadTexture_1(const Device &self, const String &name, uint32_t flags, uint32_t image_flags, uint32_t offset, Async *async) {
		return new Texture(self.loadTexture(name, (Texture::Flags)flags, (Image::Flags)image_flags, offset, async));
	}
	TS_JSAPI Texture *tsDevice_loadTexture_2(const Device &self, Stream &stream, uint32_t flags, uint32_t image_flags, uint32_t offset, Async *async) {
		return new Texture(self.loadTexture(stream, (Texture::Flags)flags, (Image::Flags)image_flags, offset, async));
	}
	TS_JSAPI Tracing *tsDevice_createTracing(const Device &self) {
		return new Tracing(self.createTracing());
	}
	TS_JSAPI Tracing *tsDevice_createTracing_1(const Device &self, const Tracing &tracing) {
		return new Tracing(self.createTracing(tracing));
	}
	TS_JSAPI Tracing *tsDevice_createTracing_2(const Device &self, uint32_t num_instances, Buffer instance_buffer, size_t instance_offset, uint32_t flags) {
		return new Tracing(self.createTracing(num_instances, instance_buffer, instance_offset, (Tracing::Flags)flags));
	}
	TS_JSAPI Tracing *tsDevice_createTracing_3(const Device &self, uint32_t num_vertices, uint32_t vertex_format, size_t vertex_stride, uint32_t num_indices, uint32_t index_format, uint32_t flags) {
		return new Tracing(self.createTracing(num_vertices, (Format)vertex_format, vertex_stride, num_indices, (Format)index_format, (Tracing::Flags)flags));
	}
	TS_JSAPI Tracing *tsDevice_createTracing_4(const Device &self, uint32_t num_bounds, size_t bound_stride, Buffer bound_buffer, size_t bound_offset, uint32_t flags) {
		return new Tracing(self.createTracing(num_bounds, bound_stride, bound_buffer, bound_offset, (Tracing::Flags)flags));
	}
	TS_JSAPI BufferTable *tsDevice_createBufferTable(const Device &self) {
		return new BufferTable(self.createBufferTable());
	}
	TS_JSAPI BufferTable *tsDevice_createBufferTable_1(const Device &self, uint32_t size) {
		return new BufferTable(self.createBufferTable(size));
	}
	TS_JSAPI BufferTable *tsDevice_createBufferTable_2(const Device &self, Array<Buffer> &buffers, bool owner) {
		return new BufferTable(self.createBufferTable(buffers, owner));
	}
	TS_JSAPI TextureTable *tsDevice_createTextureTable(const Device &self) {
		return new TextureTable(self.createTextureTable());
	}
	TS_JSAPI TextureTable *tsDevice_createTextureTable_1(const Device &self, uint32_t type, uint32_t size) {
		return new TextureTable(self.createTextureTable((Texture::Type)type, size));
	}
	TS_JSAPI TextureTable *tsDevice_createTextureTable_2(const Device &self, Array<Texture> &textures, bool owner) {
		return new TextureTable(self.createTextureTable(textures, owner));
	}
	TS_JSAPI Shader *tsDevice_createShader(const Device &self) {
		return new Shader(self.createShader());
	}
	TS_JSAPI Shader *tsDevice_loadShader(const Device &self, uint32_t type, const char *name, const char *format) {
		return new Shader(self.loadShader((Shader::Type)type, name, "%s", format));
	}
	TS_JSAPI Shader *tsDevice_loadShaderGLSL(const Device &self, uint32_t type, const char *name, const char *format) {
		return new Shader(self.loadShaderGLSL((Shader::Type)type, name, "%s", format));
	}
	TS_JSAPI Shader *tsDevice_loadShader_1(const Device &self, uint32_t type, const char *name, const String &macros) {
		return new Shader(self.loadShader((Shader::Type)type, name, macros));
	}
	TS_JSAPI Shader *tsDevice_loadShaderGLSL_1(const Device &self, uint32_t type, const char *name, const String &macros) {
		return new Shader(self.loadShaderGLSL((Shader::Type)type, name, macros));
	}
	TS_JSAPI Shader *tsDevice_loadShaderSPIRV(const Device &self, uint32_t type, const char *name) {
		return new Shader(self.loadShaderSPIRV((Shader::Type)type, name));
	}
	TS_JSAPI Shader *tsDevice_createShader_1(const Device &self, uint32_t type, const char *src, const char *format) {
		return new Shader(self.createShader((Shader::Type)type, src, "%s", format));
	}
	TS_JSAPI Shader *tsDevice_createShaderGLSL(const Device &self, uint32_t type, const char *src, const char *format) {
		return new Shader(self.createShaderGLSL((Shader::Type)type, src, "%s", format));
	}
	TS_JSAPI Shader *tsDevice_createShader_2(const Device &self, uint32_t type, const char *src, const String &macros) {
		return new Shader(self.createShader((Shader::Type)type, src, macros));
	}
	TS_JSAPI Shader *tsDevice_createShaderGLSL_1(const Device &self, uint32_t type, const char *src, const String &macros) {
		return new Shader(self.createShaderGLSL((Shader::Type)type, src, macros));
	}
	TS_JSAPI Shader *tsDevice_createShaderSPIRV(const Device &self, uint32_t type, Array<uint32_t> &data) {
		return new Shader(self.createShaderSPIRV((Shader::Type)type, data));
	}
	TS_JSAPI Kernel *tsDevice_createKernel(const Device &self) {
		return new Kernel(self.createKernel());
	}
	TS_JSAPI Kernel *tsDevice_createKernel_1(const Device &self, const Kernel &kernel) {
		return new Kernel(self.createKernel(kernel));
	}
	TS_JSAPI void tsDevice_releaseKernel(const Device &self, Kernel &kernel) {
		self.releaseKernel(kernel);
	}
	TS_JSAPI Pipeline *tsDevice_createPipeline(const Device &self) {
		return new Pipeline(self.createPipeline());
	}
	TS_JSAPI Pipeline *tsDevice_createPipeline_1(const Device &self, const Pipeline &pipeline) {
		return new Pipeline(self.createPipeline(pipeline));
	}
	TS_JSAPI void tsDevice_releasePipeline(const Device &self, Pipeline &pipeline) {
		self.releasePipeline(pipeline);
	}
	TS_JSAPI Traversal *tsDevice_createTraversal(const Device &self) {
		return new Traversal(self.createTraversal());
	}
	TS_JSAPI Traversal *tsDevice_createTraversal_1(const Device &self, const Traversal &traversal) {
		return new Traversal(self.createTraversal(traversal));
	}
	TS_JSAPI void tsDevice_releaseTraversal(const Device &self, Traversal &traversal) {
		self.releaseTraversal(traversal);
	}
	TS_JSAPI Target *tsDevice_createTarget(const Device &self) {
		return new Target(self.createTarget());
	}
	TS_JSAPI Target *tsDevice_createTarget_1(const Device &self, Surface &surface) {
		return new Target(self.createTarget(surface));
	}
	TS_JSAPI Target *tsDevice_createTarget_2(const Device &self, Window &window) {
		return new Target(self.createTarget(window));
	}
	TS_JSAPI Compute *tsDevice_createCompute(const Device &self) {
		return new Compute(self.createCompute());
	}
	TS_JSAPI Command *tsDevice_createCommand(const Device &self) {
		return new Command(self.createCommand());
	}
	TS_JSAPI Command *tsDevice_createCommand_1(const Device &self, Target &target) {
		return new Command(self.createCommand(target));
	}
	TS_JSAPI bool tsDevice_setBuffer(const Device &self, Buffer &buffer, size_t offset, const void *src, size_t size) {
		return self.setBuffer(buffer, offset, src, size);
	}
	TS_JSAPI bool tsDevice_setBuffer_1(const Device &self, Buffer &buffer, const void *src, size_t size) {
		return self.setBuffer(buffer, src, size);
	}
	TS_JSAPI bool tsDevice_setBuffer_2(const Device &self, Buffer &buffer, const void *src) {
		return self.setBuffer(buffer, src);
	}
	TS_JSAPI bool tsDevice_getBuffer(const Device &self, Buffer &buffer, size_t offset, void *dest, size_t size) {
		return self.getBuffer(buffer, offset, dest, size);
	}
	TS_JSAPI bool tsDevice_getBuffer_1(const Device &self, Buffer &buffer, void *dest, size_t size) {
		return self.getBuffer(buffer, dest, size);
	}
	TS_JSAPI bool tsDevice_getBuffer_2(const Device &self, Buffer &buffer, void *dest) {
		return self.getBuffer(buffer, dest);
	}
	TS_JSAPI void* tsDevice_mapBuffer(const Device &self, Buffer &buffer, size_t offset, size_t size) {
		return self.mapBuffer(buffer, offset, size);
	}
	TS_JSAPI void* tsDevice_mapBuffer_1(const Device &self, Buffer &buffer, size_t size) {
		return self.mapBuffer(buffer, size);
	}
	TS_JSAPI void* tsDevice_mapBuffer_2(const Device &self, Buffer &buffer) {
		return self.mapBuffer(buffer);
	}
	TS_JSAPI bool tsDevice_unmapBuffer(const Device &self, Buffer &buffer) {
		return self.unmapBuffer(buffer);
	}
	TS_JSAPI bool tsDevice_copyBuffer(const Device &self, Buffer &buffer, size_t dest_offset, Buffer &src, size_t src_offset, size_t size) {
		return self.copyBuffer(buffer, dest_offset, src, src_offset, size);
	}
	TS_JSAPI bool tsDevice_copyBuffer_1(const Device &self, Buffer &buffer, size_t dest_offset, Buffer &src, size_t size) {
		return self.copyBuffer(buffer, dest_offset, src, size);
	}
	TS_JSAPI bool tsDevice_copyBuffer_2(const Device &self, Buffer &buffer, Buffer &src, size_t size) {
		return self.copyBuffer(buffer, src, size);
	}
	TS_JSAPI bool tsDevice_copyBuffer_3(const Device &self, Buffer &buffer, Buffer &src) {
		return self.copyBuffer(buffer, src);
	}
	TS_JSAPI bool tsDevice_clearBuffer(const Device &self, Buffer &buffer, uint32_t format, size_t offset, const void *src, size_t size) {
		return self.clearBuffer(buffer, (Format)format, offset, src, size);
	}
	TS_JSAPI bool tsDevice_clearBuffer_1(const Device &self, Buffer &buffer, uint32_t format, const void *src, size_t size) {
		return self.clearBuffer(buffer, (Format)format, src, size);
	}
	TS_JSAPI bool tsDevice_clearBuffer_2(const Device &self, Buffer &buffer, uint32_t format, const void *src) {
		return self.clearBuffer(buffer, (Format)format, src);
	}
	TS_JSAPI bool tsDevice_clearBuffer_3(const Device &self, Buffer &buffer) {
		return self.clearBuffer(buffer);
	}
	TS_JSAPI bool tsDevice_bindBuffer(const Device &self, Buffer &buffer, Array<size_t> &offsets, Array<size_t> &sizes, bool commit, Fence &fence) {
		return self.bindBuffer(buffer, offsets, sizes, commit, fence);
	}
	TS_JSAPI bool tsDevice_bindBuffer_1(const Device &self, Buffer &buffer, Array<size_t> &offsets, Array<size_t> &sizes, bool commit) {
		return self.bindBuffer(buffer, offsets, sizes, commit);
	}
	TS_JSAPI bool tsDevice_bindBuffer_2(const Device &self, Buffer &buffer, size_t offset, size_t size, bool commit, Fence &fence) {
		return self.bindBuffer(buffer, offset, size, commit, fence);
	}
	TS_JSAPI bool tsDevice_bindBuffer_3(const Device &self, Buffer &buffer, size_t offset, size_t size, bool commit) {
		return self.bindBuffer(buffer, offset, size, commit);
	}
	TS_JSAPI bool tsDevice_flushBuffer(const Device &self, Buffer &buffer, uint32_t flags) {
		return self.flushBuffer(buffer, (Buffer::Flags)flags);
	}
	TS_JSAPI bool tsDevice_flushBuffers(const Device &self, Array<Buffer> &buffers, uint32_t flags) {
		return self.flushBuffers(buffers, (Buffer::Flags)flags);
	}
	TS_JSAPI void tsDevice_releaseBuffer(const Device &self, Buffer &buffer) {
		self.releaseBuffer(buffer);
	}
	TS_JSAPI void tsDevice_releaseSampler(const Device &self, Sampler &sampler) {
		self.releaseSampler(sampler);
	}
	TS_JSAPI bool tsDevice_setTexture(const Device &self, Texture &texture, const Origin &dest_origin, const Slice &dest_slice, const Image &image, const Slice &src_slice) {
		return self.setTexture(texture, dest_origin, dest_slice, image, src_slice);
	}
	TS_JSAPI bool tsDevice_setTexture_1(const Device &self, Texture &texture, const Origin &dest_origin, const Image &image) {
		return self.setTexture(texture, dest_origin, image);
	}
	TS_JSAPI bool tsDevice_setTexture_2(const Device &self, Texture &texture, const Slice &dest_slice, const Image &image) {
		return self.setTexture(texture, dest_slice, image);
	}
	TS_JSAPI bool tsDevice_setTexture_3(const Device &self, Texture &texture, const Image &image) {
		return self.setTexture(texture, image);
	}
	TS_JSAPI bool tsDevice_getTexture(const Device &self, Texture &texture, const Slice &src_slice, Image &image, const Slice &dest_slice) {
		return self.getTexture(texture, src_slice, image, dest_slice);
	}
	TS_JSAPI bool tsDevice_getTexture_1(const Device &self, Texture &texture, Image &image, const Slice &dest_slice) {
		return self.getTexture(texture, image, dest_slice);
	}
	TS_JSAPI bool tsDevice_getTexture_2(const Device &self, Texture &texture, Image &image) {
		return self.getTexture(texture, image);
	}
	TS_JSAPI bool tsDevice_copyTexture(const Device &self, Texture &texture, const Origin &dest_origin, const Slice &dest_slice, Texture &src, const Region &src_region, const Slice &src_slice) {
		return self.copyTexture(texture, dest_origin, dest_slice, src, src_region, src_slice);
	}
	TS_JSAPI bool tsDevice_copyTexture_1(const Device &self, Texture &texture, const Origin &dest_origin, Texture &src, const Region &src_region) {
		return self.copyTexture(texture, dest_origin, src, src_region);
	}
	TS_JSAPI bool tsDevice_copyTexture_2(const Device &self, Texture &texture, const Slice &dest_slice, Texture &src, const Slice &src_slice) {
		return self.copyTexture(texture, dest_slice, src, src_slice);
	}
	TS_JSAPI bool tsDevice_copyTexture_3(const Device &self, Texture &texture, Texture &src) {
		return self.copyTexture(texture, src);
	}
	TS_JSAPI bool tsDevice_clearTexture(const Device &self, Texture &texture, const Region &region, const Slice &slice, const void *src) {
		return self.clearTexture(texture, region, slice, src);
	}
	TS_JSAPI bool tsDevice_clearTexture_1(const Device &self, Texture &texture, const Region &region, const void *src) {
		return self.clearTexture(texture, region, src);
	}
	TS_JSAPI bool tsDevice_clearTexture_2(const Device &self, Texture &texture, const Slice &slice, const void *src) {
		return self.clearTexture(texture, slice, src);
	}
	TS_JSAPI bool tsDevice_clearTexture_3(const Device &self, Texture &texture, const void *src) {
		return self.clearTexture(texture, src);
	}
	TS_JSAPI bool tsDevice_bindTexture(const Device &self, Texture &texture, const Region *regions, uint32_t num_regions, const Slice *slices, uint32_t num_slices, bool commit, Fence &fence) {
		return self.bindTexture(texture, regions, num_regions, slices, num_slices, commit, fence);
	}
	TS_JSAPI bool tsDevice_bindTexture_1(const Device &self, Texture &texture, const Region *regions, uint32_t num_regions, const Slice *slices, uint32_t num_slices, bool commit) {
		return self.bindTexture(texture, regions, num_regions, slices, num_slices, commit);
	}
	TS_JSAPI bool tsDevice_bindTexture_2(const Device &self, Texture &texture, const Region &region, const Slice &slice, bool commit, Fence &fence) {
		return self.bindTexture(texture, region, slice, commit, fence);
	}
	TS_JSAPI bool tsDevice_bindTexture_3(const Device &self, Texture &texture, const Region &region, const Slice &slice, bool commit) {
		return self.bindTexture(texture, region, slice, commit);
	}
	TS_JSAPI bool tsDevice_createMipmaps(const Device &self, Texture &texture, const Slice &slice) {
		return self.createMipmaps(texture, slice);
	}
	TS_JSAPI bool tsDevice_createMipmaps_1(const Device &self, Texture &texture) {
		return self.createMipmaps(texture);
	}
	TS_JSAPI bool tsDevice_flushTexture(const Device &self, Texture &texture, uint32_t flags) {
		return self.flushTexture(texture, (Texture::Flags)flags);
	}
	TS_JSAPI bool tsDevice_flushTexture_1(const Device &self, Texture &texture, const Slice &slice, uint32_t flags) {
		return self.flushTexture(texture, slice, (Texture::Flags)flags);
	}
	TS_JSAPI bool tsDevice_flushTextures(const Device &self, Array<Texture> &textures, uint32_t flags) {
		return self.flushTextures(textures, (Texture::Flags)flags);
	}
	TS_JSAPI void tsDevice_releaseTexture(const Device &self, Texture &texture) {
		self.releaseTexture(texture);
	}
	TS_JSAPI bool tsDevice_setTracing(const Device &self, Tracing &tracing, const Tracing::Instance *instances, uint32_t num_instances) {
		return self.setTracing(tracing, instances, num_instances);
	}
	TS_JSAPI bool tsDevice_buildTracing(const Device &self, Tracing &tracing, Buffer &buffer, uint32_t flags) {
		return self.buildTracing(tracing, buffer, (Tracing::Flags)flags);
	}
	TS_JSAPI bool tsDevice_buildTracing_1(const Device &self, Tracing &tracing, Buffer &buffer, size_t offset, uint32_t flags) {
		return self.buildTracing(tracing, buffer, offset, (Tracing::Flags)flags);
	}
	TS_JSAPI bool tsDevice_buildTracings(const Device &self, Array<Tracing> &tracings, Buffer &buffer, uint32_t flags) {
		return self.buildTracings(tracings, buffer, (Tracing::Flags)flags);
	}
	TS_JSAPI bool tsDevice_buildTracings_1(const Device &self, Array<Tracing> &tracings, Buffer &buffer, size_t offset, uint32_t flags) {
		return self.buildTracings(tracings, buffer, offset, (Tracing::Flags)flags);
	}
	TS_JSAPI bool tsDevice_copyTracing(const Device &self, Tracing &tracing, Buffer &buffer, size_t offset) {
		return self.copyTracing(tracing, buffer, offset);
	}
	TS_JSAPI bool tsDevice_copyTracings(const Device &self, Array<Tracing> &tracings, Buffer &buffer, size_t offset, size_t stride) {
		return self.copyTracings(tracings, buffer, offset, stride);
	}
	TS_JSAPI bool tsDevice_flushTracing(const Device &self, Tracing &tracing) {
		return self.flushTracing(tracing);
	}
	TS_JSAPI bool tsDevice_flushTracings(const Device &self, Array<Tracing> &tracings) {
		return self.flushTracings(tracings);
	}
	TS_JSAPI void tsDevice_releaseTracing(const Device &self, Tracing &tracing) {
		self.releaseTracing(tracing);
	}
	TS_JSAPI bool tsDevice_setBufferTable(const Device &self, BufferTable &table, uint32_t index, Buffer &buffer, bool owner) {
		return self.setBufferTable(table, index, buffer, owner);
	}
	TS_JSAPI bool tsDevice_setBufferTable_1(const Device &self, BufferTable &table, uint32_t index, Array<Buffer> &buffers, bool owner) {
		return self.setBufferTable(table, index, buffers, owner);
	}
	TS_JSAPI void tsDevice_releaseBufferTable(const Device &self, BufferTable &table) {
		self.releaseBufferTable(table);
	}
	TS_JSAPI bool tsDevice_setTextureTable(const Device &self, TextureTable &table, uint32_t index, Texture &texture, bool owner) {
		return self.setTextureTable(table, index, texture, owner);
	}
	TS_JSAPI bool tsDevice_setTextureTable_1(const Device &self, TextureTable &table, uint32_t index, Array<Texture> &textures, bool owner) {
		return self.setTextureTable(table, index, textures, owner);
	}
	TS_JSAPI void tsDevice_releaseTextureTable(const Device &self, TextureTable &table) {
		self.releaseTextureTable(table);
	}
	TS_JSAPI bool tsDevice_beginQuery(const Device &self, Query &query) {
		return self.beginQuery(query);
	}
	TS_JSAPI void tsDevice_endQuery(const Device &self, Query &query) {
		self.endQuery(query);
	}
	TS_JSAPI bool tsDevice_copyQuery(const Device &self, Query &query, Buffer &buffer, size_t offset) {
		return self.copyQuery(query, buffer, offset);
	}
	TS_JSAPI bool tsDevice_copyQueries(const Device &self, Array<Query> &queries, Buffer &buffer, size_t offset, size_t stride) {
		return self.copyQueries(queries, buffer, offset, stride);
	}
	TS_JSAPI bool tsDevice_waitFence(const Device &self, Fence &fence) {
		return self.waitFence(fence);
	}
	TS_JSAPI bool tsDevice_signalFence(const Device &self, Fence &fence) {
		return self.signalFence(fence);
	}
	TS_JSAPI bool tsDevice_execute(const Device &self, Device &device) {
		return self.execute(device);
	}
	TS_JSAPI bool tsDevice_flip(const Device &self, Fence &fence) {
		return self.flip(fence);
	}
	TS_JSAPI bool tsDevice_flip_1(const Device &self) {
		return self.flip();
	}
	TS_JSAPI bool tsDevice_flush(const Device &self) {
		return self.flush();
	}
	TS_JSAPI bool tsDevice_finish(const Device &self) {
		return self.finish();
	}
	TS_JSAPI bool tsDevice_check(const Device &self) {
		return self.check();
	}
	
	// Tellusim::Kernel
	TS_JSAPI Kernel *tsKernel_new() {
		return new Kernel();
	}
	TS_JSAPI void tsKernel_delete(Kernel *self) {
		delete self;
	}
	TS_JSAPI bool tsKernel_equalPtr(const Kernel &self, const Kernel &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Kernel *tsKernel_clonePtr(const Kernel &self) {
		return new Kernel(self.clonePtr());
	}
	TS_JSAPI void tsKernel_clearPtr(Kernel &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsKernel_destroyPtr(Kernel &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsKernel_acquirePtr(Kernel &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsKernel_unacquirePtr(Kernel &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsKernel_isValidPtr(const Kernel &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsKernel_isOwnerPtr(const Kernel &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsKernel_isConstPtr(const Kernel &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsKernel_getCountPtr(const Kernel &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsKernel_getInternalPtr(const Kernel &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI uint32_t tsKernel_getPlatform(const Kernel &self) {
		return self.getPlatform();
	}
	TS_JSAPI const char* tsKernel_getPlatformName(const Kernel &self) {
		return self.getPlatformName();
	}
	TS_JSAPI uint32_t tsKernel_getIndex(const Kernel &self) {
		return self.getIndex();
	}
	TS_JSAPI void tsKernel_clear(Kernel &self) {
		self.clear();
	}
	TS_JSAPI bool tsKernel_isCreated(const Kernel &self) {
		return self.isCreated();
	}
	TS_JSAPI void tsKernel_setName(Kernel &self, const char *name) {
		self.setName(name);
	}
	TS_JSAPI String *tsKernel_getName(const Kernel &self) {
		return new String(self.getName());
	}
	TS_JSAPI bool tsKernel_create(Kernel &self) {
		return self.create();
	}
	TS_JSAPI void tsKernel_setParameters(Kernel &self, const Kernel &kernel) {
		self.setParameters(kernel);
	}
	TS_JSAPI bool tsKernel_saveState(const Kernel &self, Stream &stream) {
		return self.saveState(stream);
	}
	TS_JSAPI void tsKernel_setShader(Kernel &self, Shader &shader, bool owner) {
		self.setShader(shader, owner);
	}
	TS_JSAPI Shader *tsKernel_getComputeShader(const Kernel &self) {
		return new Shader(self.getComputeShader());
	}
	TS_JSAPI bool tsKernel_loadShader(Kernel &self, const char *name, const char *format) {
		return self.loadShader(name, "%s", format);
	}
	TS_JSAPI bool tsKernel_loadShaderGLSL(Kernel &self, const char *name, const char *format) {
		return self.loadShaderGLSL(name, "%s", format);
	}
	TS_JSAPI bool tsKernel_loadShader_1(Kernel &self, const char *name, const String &macros, const char **includes, uint32_t size) {
		return self.loadShader(name, macros, includes, size);
	}
	TS_JSAPI bool tsKernel_loadShaderGLSL_1(Kernel &self, const char *name, const String &macros, const char **includes, uint32_t size) {
		return self.loadShaderGLSL(name, macros, includes, size);
	}
	TS_JSAPI bool tsKernel_loadShaderSPIRV(Kernel &self, const char *name) {
		return self.loadShaderSPIRV(name);
	}
	TS_JSAPI bool tsKernel_createShader(Kernel &self, const char *src, const char *format) {
		return self.createShader(src, "%s", format);
	}
	TS_JSAPI bool tsKernel_createShaderGLSL(Kernel &self, const char *src, const char *format) {
		return self.createShaderGLSL(src, "%s", format);
	}
	TS_JSAPI bool tsKernel_createShader_1(Kernel &self, const char *src, const String &macros, const char **includes, uint32_t size) {
		return self.createShader(src, macros, includes, size);
	}
	TS_JSAPI bool tsKernel_createShaderGLSL_1(Kernel &self, const char *src, const String &macros, const char **includes, uint32_t size) {
		return self.createShaderGLSL(src, macros, includes, size);
	}
	TS_JSAPI bool tsKernel_createShaderSPIRV(Kernel &self, Array<uint32_t> &data) {
		return self.createShaderSPIRV(data);
	}
	TS_JSAPI uint32_t tsKernel_addSampler(Kernel &self) {
		return self.addSampler();
	}
	TS_JSAPI Kernel *tsKernel_setSamplers(Kernel &self, uint32_t num) {
		return new Kernel(self.setSamplers(num));
	}
	TS_JSAPI uint32_t tsKernel_getNumSamplers(const Kernel &self) {
		return self.getNumSamplers();
	}
	TS_JSAPI Kernel *tsKernel_setSamplerOffset(Kernel &self, uint32_t offset) {
		return new Kernel(self.setSamplerOffset(offset));
	}
	TS_JSAPI uint32_t tsKernel_getSamplerOffset(const Kernel &self) {
		return self.getSamplerOffset();
	}
	TS_JSAPI Kernel *tsKernel_setSamplerArray(Kernel &self, uint32_t index, uint32_t num, bool array) {
		return new Kernel(self.setSamplerArray(index, num, array));
	}
	TS_JSAPI uint32_t tsKernel_getSamplerArray(const Kernel &self, uint32_t index) {
		return self.getSamplerArray(index);
	}
	TS_JSAPI uint32_t tsKernel_addTexture(Kernel &self) {
		return self.addTexture();
	}
	TS_JSAPI Kernel *tsKernel_setTextures(Kernel &self, uint32_t num) {
		return new Kernel(self.setTextures(num));
	}
	TS_JSAPI uint32_t tsKernel_getNumTextures(const Kernel &self) {
		return self.getNumTextures();
	}
	TS_JSAPI Kernel *tsKernel_setTextureOffset(Kernel &self, uint32_t offset) {
		return new Kernel(self.setTextureOffset(offset));
	}
	TS_JSAPI uint32_t tsKernel_getTextureOffset(const Kernel &self) {
		return self.getTextureOffset();
	}
	TS_JSAPI Kernel *tsKernel_setTextureArray(Kernel &self, uint32_t index, uint32_t num, bool array) {
		return new Kernel(self.setTextureArray(index, num, array));
	}
	TS_JSAPI uint32_t tsKernel_getTextureArray(const Kernel &self, uint32_t index) {
		return self.getTextureArray(index);
	}
	TS_JSAPI uint32_t tsKernel_addSurface(Kernel &self) {
		return self.addSurface();
	}
	TS_JSAPI Kernel *tsKernel_setSurfaces(Kernel &self, uint32_t num) {
		return new Kernel(self.setSurfaces(num));
	}
	TS_JSAPI uint32_t tsKernel_getNumSurfaces(const Kernel &self) {
		return self.getNumSurfaces();
	}
	TS_JSAPI Kernel *tsKernel_setSurfaceOffset(Kernel &self, uint32_t offset) {
		return new Kernel(self.setSurfaceOffset(offset));
	}
	TS_JSAPI uint32_t tsKernel_getSurfaceOffset(const Kernel &self) {
		return self.getSurfaceOffset();
	}
	TS_JSAPI Kernel *tsKernel_setSurfaceArray(Kernel &self, uint32_t index, uint32_t num, bool array) {
		return new Kernel(self.setSurfaceArray(index, num, array));
	}
	TS_JSAPI uint32_t tsKernel_getSurfaceArray(const Kernel &self, uint32_t index) {
		return self.getSurfaceArray(index);
	}
	TS_JSAPI uint32_t tsKernel_addUniform(Kernel &self, uint32_t flags) {
		return self.addUniform((BindFlags)flags);
	}
	TS_JSAPI Kernel *tsKernel_setUniforms(Kernel &self, uint32_t num, uint32_t flags) {
		return new Kernel(self.setUniforms(num, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsKernel_getNumUniforms(const Kernel &self) {
		return self.getNumUniforms();
	}
	TS_JSAPI Kernel *tsKernel_setUniformOffset(Kernel &self, uint32_t offset) {
		return new Kernel(self.setUniformOffset(offset));
	}
	TS_JSAPI uint32_t tsKernel_getUniformOffset(const Kernel &self) {
		return self.getUniformOffset();
	}
	TS_JSAPI Kernel *tsKernel_setUniformFlags(Kernel &self, uint32_t index, uint32_t flags) {
		return new Kernel(self.setUniformFlags(index, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsKernel_getUniformFlags(const Kernel &self, uint32_t index) {
		return self.getUniformFlags(index);
	}
	TS_JSAPI uint32_t tsKernel_addStorage(Kernel &self, uint32_t flags) {
		return self.addStorage((BindFlags)flags);
	}
	TS_JSAPI Kernel *tsKernel_setStorages(Kernel &self, uint32_t num, uint32_t flags) {
		return new Kernel(self.setStorages(num, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsKernel_getNumStorages(const Kernel &self) {
		return self.getNumStorages();
	}
	TS_JSAPI Kernel *tsKernel_setStorageOffset(Kernel &self, uint32_t offset) {
		return new Kernel(self.setStorageOffset(offset));
	}
	TS_JSAPI uint32_t tsKernel_getStorageOffset(const Kernel &self) {
		return self.getStorageOffset();
	}
	TS_JSAPI Kernel *tsKernel_setStorageFlags(Kernel &self, uint32_t index, uint32_t flags) {
		return new Kernel(self.setStorageFlags(index, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsKernel_getStorageFlags(const Kernel &self, uint32_t index) {
		return self.getStorageFlags(index);
	}
	TS_JSAPI uint32_t tsKernel_addTracing(Kernel &self) {
		return self.addTracing();
	}
	TS_JSAPI Kernel *tsKernel_setTracings(Kernel &self, uint32_t num) {
		return new Kernel(self.setTracings(num));
	}
	TS_JSAPI uint32_t tsKernel_getNumTracings(const Kernel &self) {
		return self.getNumTracings();
	}
	TS_JSAPI Kernel *tsKernel_setTracingOffset(Kernel &self, uint32_t offset) {
		return new Kernel(self.setTracingOffset(offset));
	}
	TS_JSAPI uint32_t tsKernel_getTracingOffset(const Kernel &self) {
		return self.getTracingOffset();
	}
	TS_JSAPI uint32_t tsKernel_addTexel(Kernel &self) {
		return self.addTexel();
	}
	TS_JSAPI Kernel *tsKernel_setTexels(Kernel &self, uint32_t num) {
		return new Kernel(self.setTexels(num));
	}
	TS_JSAPI uint32_t tsKernel_getNumTexels(const Kernel &self) {
		return self.getNumTexels();
	}
	TS_JSAPI Kernel *tsKernel_setTexelOffset(Kernel &self, uint32_t offset) {
		return new Kernel(self.setTexelOffset(offset));
	}
	TS_JSAPI uint32_t tsKernel_getTexelOffset(const Kernel &self) {
		return self.getTexelOffset();
	}
	TS_JSAPI uint32_t tsKernel_addTable(Kernel &self, uint32_t type, uint32_t size) {
		return self.addTable((TableType)type, size);
	}
	TS_JSAPI uint32_t tsKernel_getNumTables(const Kernel &self) {
		return self.getNumTables();
	}
	TS_JSAPI Kernel *tsKernel_setTableOffset(Kernel &self, uint32_t offset) {
		return new Kernel(self.setTableOffset(offset));
	}
	TS_JSAPI uint32_t tsKernel_getTableOffset(const Kernel &self) {
		return self.getTableOffset();
	}
	TS_JSAPI Kernel *tsKernel_setTableType(Kernel &self, uint32_t index, uint32_t type, uint32_t size, uint32_t flags) {
		return new Kernel(self.setTableType(index, (TableType)type, size, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsKernel_getTableType(const Kernel &self, uint32_t index) {
		return self.getTableType(index);
	}
	TS_JSAPI uint32_t tsKernel_getTableSize(const Kernel &self, uint32_t index) {
		return self.getTableSize(index);
	}
	TS_JSAPI Kernel *tsKernel_setTableFlags(Kernel &self, uint32_t index, uint32_t flags) {
		return new Kernel(self.setTableFlags(index, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsKernel_getTableFlags(const Kernel &self, uint32_t index) {
		return self.getTableFlags(index);
	}
	TS_JSAPI void tsKernel_setGroupSize(Kernel &self, uint32_t width, uint32_t height, uint32_t depth) {
		self.setGroupSize(width, height, depth);
	}
	TS_JSAPI uint32_t tsKernel_getGroupSizeX(const Kernel &self) {
		return self.getGroupSizeX();
	}
	TS_JSAPI uint32_t tsKernel_getGroupSizeY(const Kernel &self) {
		return self.getGroupSizeY();
	}
	TS_JSAPI uint32_t tsKernel_getGroupSizeZ(const Kernel &self) {
		return self.getGroupSizeZ();
	}
	
	// Tellusim::Pipeline
	TS_JSAPI Pipeline *tsPipeline_new() {
		return new Pipeline();
	}
	TS_JSAPI void tsPipeline_delete(Pipeline *self) {
		delete self;
	}
	TS_JSAPI bool tsPipeline_equalPtr(const Pipeline &self, const Pipeline &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Pipeline *tsPipeline_clonePtr(const Pipeline &self) {
		return new Pipeline(self.clonePtr());
	}
	TS_JSAPI void tsPipeline_clearPtr(Pipeline &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsPipeline_destroyPtr(Pipeline &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsPipeline_acquirePtr(Pipeline &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsPipeline_unacquirePtr(Pipeline &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsPipeline_isValidPtr(const Pipeline &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsPipeline_isOwnerPtr(const Pipeline &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsPipeline_isConstPtr(const Pipeline &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsPipeline_getCountPtr(const Pipeline &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsPipeline_getInternalPtr(const Pipeline &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI uint32_t tsPipeline_getPlatform(const Pipeline &self) {
		return self.getPlatform();
	}
	TS_JSAPI const char* tsPipeline_getPlatformName(const Pipeline &self) {
		return self.getPlatformName();
	}
	TS_JSAPI uint32_t tsPipeline_getIndex(const Pipeline &self) {
		return self.getIndex();
	}
	TS_JSAPI void tsPipeline_clear(Pipeline &self) {
		self.clear();
	}
	TS_JSAPI bool tsPipeline_isCreated(const Pipeline &self) {
		return self.isCreated();
	}
	TS_JSAPI void tsPipeline_setName(Pipeline &self, const char *name) {
		self.setName(name);
	}
	TS_JSAPI String *tsPipeline_getName(const Pipeline &self) {
		return new String(self.getName());
	}
	TS_JSAPI bool tsPipeline_create(Pipeline &self) {
		return self.create();
	}
	TS_JSAPI void tsPipeline_setParameters(Pipeline &self, const Pipeline &pipeline) {
		self.setParameters(pipeline);
	}
	TS_JSAPI bool tsPipeline_saveState(const Pipeline &self, Stream &stream) {
		return self.saveState(stream);
	}
	TS_JSAPI void tsPipeline_addShader(Pipeline &self, Shader &shader, bool owner) {
		self.addShader(shader, owner);
	}
	TS_JSAPI Shader *tsPipeline_getVertexShader(const Pipeline &self) {
		return new Shader(self.getVertexShader());
	}
	TS_JSAPI Shader *tsPipeline_getControlShader(const Pipeline &self) {
		return new Shader(self.getControlShader());
	}
	TS_JSAPI Shader *tsPipeline_getEvaluateShader(const Pipeline &self) {
		return new Shader(self.getEvaluateShader());
	}
	TS_JSAPI Shader *tsPipeline_getGeometryShader(const Pipeline &self) {
		return new Shader(self.getGeometryShader());
	}
	TS_JSAPI Shader *tsPipeline_getFragmentShader(const Pipeline &self) {
		return new Shader(self.getFragmentShader());
	}
	TS_JSAPI Shader *tsPipeline_getTaskShader(const Pipeline &self) {
		return new Shader(self.getTaskShader());
	}
	TS_JSAPI Shader *tsPipeline_getMeshShader(const Pipeline &self) {
		return new Shader(self.getMeshShader());
	}
	TS_JSAPI bool tsPipeline_loadShader(Pipeline &self, uint32_t type, const char *name, const char *format) {
		return self.loadShader((Shader::Type)type, name, "%s", format);
	}
	TS_JSAPI bool tsPipeline_loadShaderGLSL(Pipeline &self, uint32_t type, const char *name, const char *format) {
		return self.loadShaderGLSL((Shader::Type)type, name, "%s", format);
	}
	TS_JSAPI bool tsPipeline_loadShader_1(Pipeline &self, uint32_t type, const char *name, const String &macros, const char **includes, uint32_t size) {
		return self.loadShader((Shader::Type)type, name, macros, includes, size);
	}
	TS_JSAPI bool tsPipeline_loadShaderGLSL_1(Pipeline &self, uint32_t type, const char *name, const String &macros, const char **includes, uint32_t size) {
		return self.loadShaderGLSL((Shader::Type)type, name, macros, includes, size);
	}
	TS_JSAPI bool tsPipeline_loadShaderSPIRV(Pipeline &self, uint32_t type, const char *name) {
		return self.loadShaderSPIRV((Shader::Type)type, name);
	}
	TS_JSAPI bool tsPipeline_createShader(Pipeline &self, uint32_t type, const char *src, const char *format) {
		return self.createShader((Shader::Type)type, src, "%s", format);
	}
	TS_JSAPI bool tsPipeline_createShaderGLSL(Pipeline &self, uint32_t type, const char *src, const char *format) {
		return self.createShaderGLSL((Shader::Type)type, src, "%s", format);
	}
	TS_JSAPI bool tsPipeline_createShader_1(Pipeline &self, uint32_t type, const char *src, const String &macros, const char **includes, uint32_t size) {
		return self.createShader((Shader::Type)type, src, macros, includes, size);
	}
	TS_JSAPI bool tsPipeline_createShaderGLSL_1(Pipeline &self, uint32_t type, const char *src, const String &macros, const char **includes, uint32_t size) {
		return self.createShaderGLSL((Shader::Type)type, src, macros, includes, size);
	}
	TS_JSAPI bool tsPipeline_createShaderSPIRV(Pipeline &self, uint32_t type, Array<uint32_t> &data) {
		return self.createShaderSPIRV((Shader::Type)type, data);
	}
	TS_JSAPI uint32_t tsPipeline_addSampler(Pipeline &self, uint32_t mask) {
		return self.addSampler((Shader::Mask)mask);
	}
	TS_JSAPI uint32_t tsPipeline_getNumSamplers(const Pipeline &self) {
		return self.getNumSamplers();
	}
	TS_JSAPI Pipeline *tsPipeline_setSamplerOffset(Pipeline &self, uint32_t offset) {
		return new Pipeline(self.setSamplerOffset(offset));
	}
	TS_JSAPI uint32_t tsPipeline_getSamplerOffset(const Pipeline &self) {
		return self.getSamplerOffset();
	}
	TS_JSAPI Pipeline *tsPipeline_setSamplerMask(Pipeline &self, uint32_t index, uint32_t mask) {
		return new Pipeline(self.setSamplerMask(index, (Shader::Mask)mask));
	}
	TS_JSAPI uint32_t tsPipeline_getSamplerMask(const Pipeline &self, uint32_t index) {
		return self.getSamplerMask(index);
	}
	TS_JSAPI Pipeline *tsPipeline_setSamplerMasks(Pipeline &self, uint32_t index, uint32_t num, uint32_t mask, bool array) {
		return new Pipeline(self.setSamplerMasks(index, num, (Shader::Mask)mask, array));
	}
	TS_JSAPI uint32_t tsPipeline_getSamplerMasks(const Pipeline &self, uint32_t index, uint32_t num) {
		return self.getSamplerMasks(index, num);
	}
	TS_JSAPI Pipeline *tsPipeline_setSamplerArray(Pipeline &self, uint32_t index, uint32_t num, bool array) {
		return new Pipeline(self.setSamplerArray(index, num, array));
	}
	TS_JSAPI uint32_t tsPipeline_getSamplerArray(const Pipeline &self, uint32_t index) {
		return self.getSamplerArray(index);
	}
	TS_JSAPI uint32_t tsPipeline_addTexture(Pipeline &self, uint32_t mask) {
		return self.addTexture((Shader::Mask)mask);
	}
	TS_JSAPI uint32_t tsPipeline_getNumTextures(const Pipeline &self) {
		return self.getNumTextures();
	}
	TS_JSAPI Pipeline *tsPipeline_setTextureOffset(Pipeline &self, uint32_t offset) {
		return new Pipeline(self.setTextureOffset(offset));
	}
	TS_JSAPI uint32_t tsPipeline_getTextureOffset(const Pipeline &self) {
		return self.getTextureOffset();
	}
	TS_JSAPI Pipeline *tsPipeline_setTextureMask(Pipeline &self, uint32_t index, uint32_t mask) {
		return new Pipeline(self.setTextureMask(index, (Shader::Mask)mask));
	}
	TS_JSAPI uint32_t tsPipeline_getTextureMask(const Pipeline &self, uint32_t index) {
		return self.getTextureMask(index);
	}
	TS_JSAPI Pipeline *tsPipeline_setTextureMasks(Pipeline &self, uint32_t index, uint32_t num, uint32_t mask, bool array) {
		return new Pipeline(self.setTextureMasks(index, num, (Shader::Mask)mask, array));
	}
	TS_JSAPI uint32_t tsPipeline_getTextureMasks(const Pipeline &self, uint32_t index, uint32_t num) {
		return self.getTextureMasks(index, num);
	}
	TS_JSAPI Pipeline *tsPipeline_setTextureArray(Pipeline &self, uint32_t index, uint32_t num, bool array) {
		return new Pipeline(self.setTextureArray(index, num, array));
	}
	TS_JSAPI uint32_t tsPipeline_getTextureArray(const Pipeline &self, uint32_t index) {
		return self.getTextureArray(index);
	}
	TS_JSAPI uint32_t tsPipeline_addSurface(Pipeline &self, uint32_t mask) {
		return self.addSurface((Shader::Mask)mask);
	}
	TS_JSAPI uint32_t tsPipeline_getNumSurfaces(const Pipeline &self) {
		return self.getNumSurfaces();
	}
	TS_JSAPI Pipeline *tsPipeline_setSurfaceOffset(Pipeline &self, uint32_t offset) {
		return new Pipeline(self.setSurfaceOffset(offset));
	}
	TS_JSAPI uint32_t tsPipeline_getSurfaceOffset(const Pipeline &self) {
		return self.getSurfaceOffset();
	}
	TS_JSAPI Pipeline *tsPipeline_setSurfaceMask(Pipeline &self, uint32_t index, uint32_t mask) {
		return new Pipeline(self.setSurfaceMask(index, (Shader::Mask)mask));
	}
	TS_JSAPI uint32_t tsPipeline_getSurfaceMask(const Pipeline &self, uint32_t index) {
		return self.getSurfaceMask(index);
	}
	TS_JSAPI Pipeline *tsPipeline_setSurfaceMasks(Pipeline &self, uint32_t index, uint32_t num, uint32_t mask, bool array) {
		return new Pipeline(self.setSurfaceMasks(index, num, (Shader::Mask)mask, array));
	}
	TS_JSAPI uint32_t tsPipeline_getSurfaceMasks(const Pipeline &self, uint32_t index, uint32_t num) {
		return self.getSurfaceMasks(index, num);
	}
	TS_JSAPI Pipeline *tsPipeline_setSurfaceArray(Pipeline &self, uint32_t index, uint32_t num, bool array) {
		return new Pipeline(self.setSurfaceArray(index, num, array));
	}
	TS_JSAPI uint32_t tsPipeline_getSurfaceArray(const Pipeline &self, uint32_t index) {
		return self.getSurfaceArray(index);
	}
	TS_JSAPI uint32_t tsPipeline_addUniform(Pipeline &self, uint32_t mask, uint32_t flags) {
		return self.addUniform((Shader::Mask)mask, (BindFlags)flags);
	}
	TS_JSAPI uint32_t tsPipeline_getNumUniforms(const Pipeline &self) {
		return self.getNumUniforms();
	}
	TS_JSAPI Pipeline *tsPipeline_setUniformOffset(Pipeline &self, uint32_t offset) {
		return new Pipeline(self.setUniformOffset(offset));
	}
	TS_JSAPI uint32_t tsPipeline_getUniformOffset(const Pipeline &self) {
		return self.getUniformOffset();
	}
	TS_JSAPI Pipeline *tsPipeline_setUniformMask(Pipeline &self, uint32_t index, uint32_t mask, uint32_t flags) {
		return new Pipeline(self.setUniformMask(index, (Shader::Mask)mask, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsPipeline_getUniformMask(const Pipeline &self, uint32_t index) {
		return self.getUniformMask(index);
	}
	TS_JSAPI Pipeline *tsPipeline_setUniformMasks(Pipeline &self, uint32_t index, uint32_t num, uint32_t mask, uint32_t flags) {
		return new Pipeline(self.setUniformMasks(index, num, (Shader::Mask)mask, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsPipeline_getUniformMasks(const Pipeline &self, uint32_t index, uint32_t num) {
		return self.getUniformMasks(index, num);
	}
	TS_JSAPI Pipeline *tsPipeline_setUniformFlags(Pipeline &self, uint32_t index, uint32_t flags) {
		return new Pipeline(self.setUniformFlags(index, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsPipeline_getUniformFlags(const Pipeline &self, uint32_t index) {
		return self.getUniformFlags(index);
	}
	TS_JSAPI uint32_t tsPipeline_addStorage(Pipeline &self, uint32_t mask, uint32_t flags) {
		return self.addStorage((Shader::Mask)mask, (BindFlags)flags);
	}
	TS_JSAPI uint32_t tsPipeline_getNumStorages(const Pipeline &self) {
		return self.getNumStorages();
	}
	TS_JSAPI Pipeline *tsPipeline_setStorageOffset(Pipeline &self, uint32_t offset) {
		return new Pipeline(self.setStorageOffset(offset));
	}
	TS_JSAPI uint32_t tsPipeline_getStorageOffset(const Pipeline &self) {
		return self.getStorageOffset();
	}
	TS_JSAPI Pipeline *tsPipeline_setStorageMask(Pipeline &self, uint32_t index, uint32_t mask, uint32_t flags) {
		return new Pipeline(self.setStorageMask(index, (Shader::Mask)mask, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsPipeline_getStorageMask(const Pipeline &self, uint32_t index) {
		return self.getStorageMask(index);
	}
	TS_JSAPI Pipeline *tsPipeline_setStorageMasks(Pipeline &self, uint32_t index, uint32_t num, uint32_t mask, uint32_t flags) {
		return new Pipeline(self.setStorageMasks(index, num, (Shader::Mask)mask, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsPipeline_getStorageMasks(const Pipeline &self, uint32_t index, uint32_t num) {
		return self.getStorageMasks(index, num);
	}
	TS_JSAPI Pipeline *tsPipeline_setStorageFlags(Pipeline &self, uint32_t index, uint32_t flags) {
		return new Pipeline(self.setStorageFlags(index, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsPipeline_getStorageFlags(const Pipeline &self, uint32_t index) {
		return self.getStorageFlags(index);
	}
	TS_JSAPI uint32_t tsPipeline_addTracing(Pipeline &self, uint32_t mask) {
		return self.addTracing((Shader::Mask)mask);
	}
	TS_JSAPI uint32_t tsPipeline_getNumTracings(const Pipeline &self) {
		return self.getNumTracings();
	}
	TS_JSAPI Pipeline *tsPipeline_setTracingOffset(Pipeline &self, uint32_t offset) {
		return new Pipeline(self.setTracingOffset(offset));
	}
	TS_JSAPI uint32_t tsPipeline_getTracingOffset(const Pipeline &self) {
		return self.getTracingOffset();
	}
	TS_JSAPI Pipeline *tsPipeline_setTracingMask(Pipeline &self, uint32_t index, uint32_t mask) {
		return new Pipeline(self.setTracingMask(index, (Shader::Mask)mask));
	}
	TS_JSAPI uint32_t tsPipeline_getTracingMask(const Pipeline &self, uint32_t index) {
		return self.getTracingMask(index);
	}
	TS_JSAPI Pipeline *tsPipeline_setTracingMasks(Pipeline &self, uint32_t index, uint32_t num, uint32_t mask) {
		return new Pipeline(self.setTracingMasks(index, num, (Shader::Mask)mask));
	}
	TS_JSAPI uint32_t tsPipeline_getTracingMasks(const Pipeline &self, uint32_t index, uint32_t num) {
		return self.getTracingMasks(index, num);
	}
	TS_JSAPI uint32_t tsPipeline_addTexel(Pipeline &self, uint32_t mask) {
		return self.addTexel((Shader::Mask)mask);
	}
	TS_JSAPI uint32_t tsPipeline_getNumTexels(const Pipeline &self) {
		return self.getNumTexels();
	}
	TS_JSAPI Pipeline *tsPipeline_setTexelOffset(Pipeline &self, uint32_t offset) {
		return new Pipeline(self.setTexelOffset(offset));
	}
	TS_JSAPI uint32_t tsPipeline_getTexelOffset(const Pipeline &self) {
		return self.getTexelOffset();
	}
	TS_JSAPI Pipeline *tsPipeline_setTexelMask(Pipeline &self, uint32_t index, uint32_t mask) {
		return new Pipeline(self.setTexelMask(index, (Shader::Mask)mask));
	}
	TS_JSAPI uint32_t tsPipeline_getTexelMask(const Pipeline &self, uint32_t index) {
		return self.getTexelMask(index);
	}
	TS_JSAPI Pipeline *tsPipeline_setTexelMasks(Pipeline &self, uint32_t index, uint32_t num, uint32_t mask) {
		return new Pipeline(self.setTexelMasks(index, num, (Shader::Mask)mask));
	}
	TS_JSAPI uint32_t tsPipeline_getTexelMasks(const Pipeline &self, uint32_t index, uint32_t num) {
		return self.getTexelMasks(index, num);
	}
	TS_JSAPI uint32_t tsPipeline_addTable(Pipeline &self, uint32_t type, uint32_t size, uint32_t mask, uint32_t flags) {
		return self.addTable((TableType)type, size, (Shader::Mask)mask, (BindFlags)flags);
	}
	TS_JSAPI uint32_t tsPipeline_getNumTables(const Pipeline &self) {
		return self.getNumTables();
	}
	TS_JSAPI Pipeline *tsPipeline_setTableOffset(Pipeline &self, uint32_t offset) {
		return new Pipeline(self.setTableOffset(offset));
	}
	TS_JSAPI uint32_t tsPipeline_getTableOffset(const Pipeline &self) {
		return self.getTableOffset();
	}
	TS_JSAPI Pipeline *tsPipeline_setTableType(Pipeline &self, uint32_t index, uint32_t type, uint32_t size, uint32_t mask, uint32_t flags) {
		return new Pipeline(self.setTableType(index, (TableType)type, size, (Shader::Mask)mask, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsPipeline_getTableType(const Pipeline &self, uint32_t index) {
		return self.getTableType(index);
	}
	TS_JSAPI uint32_t tsPipeline_getTableSize(const Pipeline &self, uint32_t index) {
		return self.getTableSize(index);
	}
	TS_JSAPI Pipeline *tsPipeline_setTableMask(Pipeline &self, uint32_t index, uint32_t mask, uint32_t flags) {
		return new Pipeline(self.setTableMask(index, (Shader::Mask)mask, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsPipeline_getTableMask(const Pipeline &self, uint32_t index) {
		return self.getTableMask(index);
	}
	TS_JSAPI Pipeline *tsPipeline_setTableFlags(Pipeline &self, uint32_t index, uint32_t flags) {
		return new Pipeline(self.setTableFlags(index, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsPipeline_getTableFlags(const Pipeline &self, uint32_t index) {
		return self.getTableFlags(index);
	}
	TS_JSAPI uint32_t tsPipeline_getNumVertices(const Pipeline &self) {
		return self.getNumVertices();
	}
	TS_JSAPI uint32_t tsPipeline_getVertexStride(const Pipeline &self, uint32_t index) {
		return self.getVertexStride(index);
	}
	TS_JSAPI uint32_t tsPipeline_getVertexRate(const Pipeline &self, uint32_t index) {
		return self.getVertexRate(index);
	}
	TS_JSAPI uint32_t tsPipeline_addAttribute(Pipeline &self, uint32_t attribute, uint32_t format, uint32_t vertex, size_t offset, size_t stride, uint32_t rate) {
		return self.addAttribute((Pipeline::Attribute)attribute, (Format)format, vertex, offset, stride, rate);
	}
	TS_JSAPI Pipeline *tsPipeline_setAttribute(Pipeline &self, uint32_t index, uint32_t attribute, uint32_t format, uint32_t vertex, size_t offset, size_t stride, uint32_t rate) {
		return new Pipeline(self.setAttribute(index, (Pipeline::Attribute)attribute, (Format)format, vertex, offset, stride, rate));
	}
	TS_JSAPI Pipeline *tsPipeline_setAttributeType(Pipeline &self, uint32_t index, uint32_t attribute) {
		return new Pipeline(self.setAttributeType(index, (Pipeline::Attribute)attribute));
	}
	TS_JSAPI Pipeline *tsPipeline_setAttributeFormat(Pipeline &self, uint32_t index, uint32_t format) {
		return new Pipeline(self.setAttributeFormat(index, (Format)format));
	}
	TS_JSAPI Pipeline *tsPipeline_setAttributeVertex(Pipeline &self, uint32_t index, uint32_t vertex) {
		return new Pipeline(self.setAttributeVertex(index, vertex));
	}
	TS_JSAPI Pipeline *tsPipeline_setAttributeOffset(Pipeline &self, uint32_t index, size_t offset) {
		return new Pipeline(self.setAttributeOffset(index, offset));
	}
	TS_JSAPI Pipeline *tsPipeline_setAttributeStride(Pipeline &self, uint32_t index, size_t stride) {
		return new Pipeline(self.setAttributeStride(index, stride));
	}
	TS_JSAPI Pipeline *tsPipeline_setAttributeRate(Pipeline &self, uint32_t index, uint32_t rate) {
		return new Pipeline(self.setAttributeRate(index, rate));
	}
	TS_JSAPI uint32_t tsPipeline_getNumAttributes(const Pipeline &self) {
		return self.getNumAttributes();
	}
	TS_JSAPI uint32_t tsPipeline_getAttributeType(const Pipeline &self, uint32_t index) {
		return self.getAttributeType(index);
	}
	TS_JSAPI uint32_t tsPipeline_getAttributeFormat(const Pipeline &self, uint32_t index) {
		return self.getAttributeFormat(index);
	}
	TS_JSAPI uint32_t tsPipeline_getAttributeVertex(const Pipeline &self, uint32_t index) {
		return self.getAttributeVertex(index);
	}
	TS_JSAPI uint32_t tsPipeline_getAttributeOffset(const Pipeline &self, uint32_t index) {
		return self.getAttributeOffset(index);
	}
	TS_JSAPI uint32_t tsPipeline_getAttributeStride(const Pipeline &self, uint32_t index) {
		return self.getAttributeStride(index);
	}
	TS_JSAPI uint32_t tsPipeline_getAttributeRate(const Pipeline &self, uint32_t index) {
		return self.getAttributeRate(index);
	}
	TS_JSAPI void tsPipeline_setPrimitive(Pipeline &self, uint32_t primitive) {
		self.setPrimitive((Pipeline::Primitive)primitive);
	}
	TS_JSAPI uint32_t tsPipeline_getPrimitive(const Pipeline &self) {
		return self.getPrimitive();
	}
	TS_JSAPI void tsPipeline_setFillMode(Pipeline &self, uint32_t mode) {
		self.setFillMode((Pipeline::FillMode)mode);
	}
	TS_JSAPI uint32_t tsPipeline_getFillMode(const Pipeline &self) {
		return self.getFillMode();
	}
	TS_JSAPI void tsPipeline_setCullMode(Pipeline &self, uint32_t mode) {
		self.setCullMode((Pipeline::CullMode)mode);
	}
	TS_JSAPI uint32_t tsPipeline_getCullMode(const Pipeline &self) {
		return self.getCullMode();
	}
	TS_JSAPI void tsPipeline_setFrontMode(Pipeline &self, uint32_t mode) {
		self.setFrontMode((Pipeline::FrontMode)mode);
	}
	TS_JSAPI uint32_t tsPipeline_getFrontMode(const Pipeline &self) {
		return self.getFrontMode();
	}
	TS_JSAPI void tsPipeline_setDepthBias(Pipeline &self, float32_t bias, float32_t slope, float32_t clamp) {
		self.setDepthBias(bias, slope, clamp);
	}
	TS_JSAPI float32_t tsPipeline_getDepthBias(const Pipeline &self) {
		return self.getDepthBias();
	}
	TS_JSAPI float32_t tsPipeline_getDepthSlope(const Pipeline &self) {
		return self.getDepthSlope();
	}
	TS_JSAPI float32_t tsPipeline_getDepthClamp(const Pipeline &self) {
		return self.getDepthClamp();
	}
	TS_JSAPI void tsPipeline_setMultisample(Pipeline &self, uint32_t multisample) {
		self.setMultisample(multisample);
	}
	TS_JSAPI uint32_t tsPipeline_getMultisample(const Pipeline &self) {
		return self.getMultisample();
	}
	TS_JSAPI void tsPipeline_setSampleMask(Pipeline &self, uint32_t sample_mask) {
		self.setSampleMask(sample_mask);
	}
	TS_JSAPI uint32_t tsPipeline_getSampleMask(const Pipeline &self) {
		return self.getSampleMask();
	}
	TS_JSAPI void tsPipeline_setDepthClip(Pipeline &self, bool enabled) {
		self.setDepthClip(enabled);
	}
	TS_JSAPI bool tsPipeline_getDepthClip(const Pipeline &self) {
		return self.getDepthClip();
	}
	TS_JSAPI void tsPipeline_setDepthReplace(Pipeline &self, bool enabled) {
		self.setDepthReplace(enabled);
	}
	TS_JSAPI bool tsPipeline_getDepthReplace(const Pipeline &self) {
		return self.getDepthReplace();
	}
	TS_JSAPI void tsPipeline_setScissorTest(Pipeline &self, bool enabled) {
		self.setScissorTest(enabled);
	}
	TS_JSAPI bool tsPipeline_getScissorTest(const Pipeline &self) {
		return self.getScissorTest();
	}
	TS_JSAPI void tsPipeline_setRasterDiscard(Pipeline &self, bool enabled) {
		self.setRasterDiscard(enabled);
	}
	TS_JSAPI bool tsPipeline_getRasterDiscard(const Pipeline &self) {
		return self.getRasterDiscard();
	}
	TS_JSAPI void tsPipeline_setSampleShading(Pipeline &self, bool enabled) {
		self.setSampleShading(enabled);
	}
	TS_JSAPI bool tsPipeline_getSampleShading(const Pipeline &self) {
		return self.getSampleShading();
	}
	TS_JSAPI void tsPipeline_setAlphaToCoverage(Pipeline &self, bool enabled) {
		self.setAlphaToCoverage(enabled);
	}
	TS_JSAPI bool tsPipeline_getAlphaToCoverage(const Pipeline &self) {
		return self.getAlphaToCoverage();
	}
	TS_JSAPI void tsPipeline_setMultisampleRaster(Pipeline &self, bool enabled) {
		self.setMultisampleRaster(enabled);
	}
	TS_JSAPI bool tsPipeline_getMultisampleRaster(const Pipeline &self) {
		return self.getMultisampleRaster();
	}
	TS_JSAPI void tsPipeline_setConservativeRaster(Pipeline &self, bool enabled) {
		self.setConservativeRaster(enabled);
	}
	TS_JSAPI bool tsPipeline_getConservativeRaster(const Pipeline &self) {
		return self.getConservativeRaster();
	}
	TS_JSAPI void tsPipeline_setNumViewports(Pipeline &self, uint32_t num_viewports) {
		self.setNumViewports(num_viewports);
	}
	TS_JSAPI uint32_t tsPipeline_getNumTargets(const Pipeline &self) {
		return self.getNumTargets();
	}
	TS_JSAPI uint32_t tsPipeline_getNumViewports(const Pipeline &self) {
		return self.getNumViewports();
	}
	TS_JSAPI void tsPipeline_setNumClipDistances(Pipeline &self, uint32_t num_distances) {
		self.setNumClipDistances(num_distances);
	}
	TS_JSAPI uint32_t tsPipeline_getNumClipDistances(const Pipeline &self) {
		return self.getNumClipDistances();
	}
	TS_JSAPI void tsPipeline_setBlend(Pipeline &self, uint32_t op, uint32_t src, uint32_t dest) {
		self.setBlend((Pipeline::BlendOp)op, (Pipeline::BlendFunc)src, (Pipeline::BlendFunc)dest);
	}
	TS_JSAPI void tsPipeline_setBlendColor(Pipeline &self, uint32_t op, uint32_t src, uint32_t dest) {
		self.setBlendColor((Pipeline::BlendOp)op, (Pipeline::BlendFunc)src, (Pipeline::BlendFunc)dest);
	}
	TS_JSAPI void tsPipeline_setBlendAlpha(Pipeline &self, uint32_t op, uint32_t src, uint32_t dest) {
		self.setBlendAlpha((Pipeline::BlendOp)op, (Pipeline::BlendFunc)src, (Pipeline::BlendFunc)dest);
	}
	TS_JSAPI void tsPipeline_setBlend_1(Pipeline &self, uint32_t index, uint32_t op, uint32_t src, uint32_t dest) {
		self.setBlend(index, (Pipeline::BlendOp)op, (Pipeline::BlendFunc)src, (Pipeline::BlendFunc)dest);
	}
	TS_JSAPI void tsPipeline_setBlendColor_1(Pipeline &self, uint32_t index, uint32_t op, uint32_t src, uint32_t dest) {
		self.setBlendColor(index, (Pipeline::BlendOp)op, (Pipeline::BlendFunc)src, (Pipeline::BlendFunc)dest);
	}
	TS_JSAPI void tsPipeline_setBlendAlpha_1(Pipeline &self, uint32_t index, uint32_t op, uint32_t src, uint32_t dest) {
		self.setBlendAlpha(index, (Pipeline::BlendOp)op, (Pipeline::BlendFunc)src, (Pipeline::BlendFunc)dest);
	}
	TS_JSAPI uint32_t tsPipeline_getBlendColorOp(const Pipeline &self, uint32_t index) {
		return self.getBlendColorOp(index);
	}
	TS_JSAPI uint32_t tsPipeline_getBlendAlphaOp(const Pipeline &self, uint32_t index) {
		return self.getBlendAlphaOp(index);
	}
	TS_JSAPI uint32_t tsPipeline_getBlendSrcColorFunc(const Pipeline &self, uint32_t index) {
		return self.getBlendSrcColorFunc(index);
	}
	TS_JSAPI uint32_t tsPipeline_getBlendSrcAlphaFunc(const Pipeline &self, uint32_t index) {
		return self.getBlendSrcAlphaFunc(index);
	}
	TS_JSAPI uint32_t tsPipeline_getBlendDestColorFunc(const Pipeline &self, uint32_t index) {
		return self.getBlendDestColorFunc(index);
	}
	TS_JSAPI uint32_t tsPipeline_getBlendDestAlphaFunc(const Pipeline &self, uint32_t index) {
		return self.getBlendDestAlphaFunc(index);
	}
	TS_JSAPI void tsPipeline_setColorMask(Pipeline &self, uint32_t mask) {
		self.setColorMask((Pipeline::ColorMask)mask);
	}
	TS_JSAPI void tsPipeline_setColorMask_1(Pipeline &self, uint32_t index, uint32_t mask) {
		self.setColorMask(index, (Pipeline::ColorMask)mask);
	}
	TS_JSAPI void tsPipeline_setColorFormat(Pipeline &self, uint32_t index, uint32_t format) {
		self.setColorFormat(index, (Format)format);
	}
	TS_JSAPI void tsPipeline_setColorFormat_1(Pipeline &self, uint32_t format, uint32_t num) {
		self.setColorFormat((Format)format, num);
	}
	TS_JSAPI uint32_t tsPipeline_getColorMask(const Pipeline &self, uint32_t index) {
		return self.getColorMask(index);
	}
	TS_JSAPI uint32_t tsPipeline_getColorFormat(const Pipeline &self, uint32_t index) {
		return self.getColorFormat(index);
	}
	TS_JSAPI void tsPipeline_setDepthMask(Pipeline &self, uint32_t mask) {
		self.setDepthMask((Pipeline::DepthMask)mask);
	}
	TS_JSAPI void tsPipeline_setDepthFunc(Pipeline &self, uint32_t func) {
		self.setDepthFunc((Pipeline::DepthFunc)func);
	}
	TS_JSAPI void tsPipeline_setDepthFormat(Pipeline &self, uint32_t format) {
		self.setDepthFormat((Format)format);
	}
	TS_JSAPI uint32_t tsPipeline_getDepthMask(const Pipeline &self) {
		return self.getDepthMask();
	}
	TS_JSAPI uint32_t tsPipeline_getDepthFunc(const Pipeline &self) {
		return self.getDepthFunc();
	}
	TS_JSAPI uint32_t tsPipeline_getDepthFormat(const Pipeline &self) {
		return self.getDepthFormat();
	}
	TS_JSAPI void tsPipeline_setStencilMask(Pipeline &self, uint32_t mask) {
		self.setStencilMask(mask);
	}
	TS_JSAPI void tsPipeline_setStencilBackMask(Pipeline &self, uint32_t mask) {
		self.setStencilBackMask(mask);
	}
	TS_JSAPI void tsPipeline_setStencilFrontMask(Pipeline &self, uint32_t mask) {
		self.setStencilFrontMask(mask);
	}
	TS_JSAPI void tsPipeline_setStencilFunc(Pipeline &self, uint32_t func, uint32_t dpass_op) {
		self.setStencilFunc((Pipeline::StencilFunc)func, (Pipeline::StencilOp)dpass_op);
	}
	TS_JSAPI void tsPipeline_setStencilBackFunc(Pipeline &self, uint32_t func, uint32_t dpass_op) {
		self.setStencilBackFunc((Pipeline::StencilFunc)func, (Pipeline::StencilOp)dpass_op);
	}
	TS_JSAPI void tsPipeline_setStencilFrontFunc(Pipeline &self, uint32_t func, uint32_t dpass_op) {
		self.setStencilFrontFunc((Pipeline::StencilFunc)func, (Pipeline::StencilOp)dpass_op);
	}
	TS_JSAPI void tsPipeline_setStencilFunc_1(Pipeline &self, uint32_t func, uint32_t fail_op, uint32_t dfail_op, uint32_t dpass_op) {
		self.setStencilFunc((Pipeline::StencilFunc)func, (Pipeline::StencilOp)fail_op, (Pipeline::StencilOp)dfail_op, (Pipeline::StencilOp)dpass_op);
	}
	TS_JSAPI void tsPipeline_setStencilBackFunc_1(Pipeline &self, uint32_t func, uint32_t fail_op, uint32_t dfail_op, uint32_t dpass_op) {
		self.setStencilBackFunc((Pipeline::StencilFunc)func, (Pipeline::StencilOp)fail_op, (Pipeline::StencilOp)dfail_op, (Pipeline::StencilOp)dpass_op);
	}
	TS_JSAPI void tsPipeline_setStencilFrontFunc_1(Pipeline &self, uint32_t func, uint32_t fail_op, uint32_t dfail_op, uint32_t dpass_op) {
		self.setStencilFrontFunc((Pipeline::StencilFunc)func, (Pipeline::StencilOp)fail_op, (Pipeline::StencilOp)dfail_op, (Pipeline::StencilOp)dpass_op);
	}
	TS_JSAPI uint32_t tsPipeline_getStencilBackMask(const Pipeline &self) {
		return self.getStencilBackMask();
	}
	TS_JSAPI uint32_t tsPipeline_getStencilBackFunc(const Pipeline &self) {
		return self.getStencilBackFunc();
	}
	TS_JSAPI uint32_t tsPipeline_getStencilBackFailOp(const Pipeline &self) {
		return self.getStencilBackFailOp();
	}
	TS_JSAPI uint32_t tsPipeline_getStencilBackDepthFailOp(const Pipeline &self) {
		return self.getStencilBackDepthFailOp();
	}
	TS_JSAPI uint32_t tsPipeline_getStencilBackDepthPassOp(const Pipeline &self) {
		return self.getStencilBackDepthPassOp();
	}
	TS_JSAPI uint32_t tsPipeline_getStencilFrontMask(const Pipeline &self) {
		return self.getStencilFrontMask();
	}
	TS_JSAPI uint32_t tsPipeline_getStencilFrontFunc(const Pipeline &self) {
		return self.getStencilFrontFunc();
	}
	TS_JSAPI uint32_t tsPipeline_getStencilFrontFailOp(const Pipeline &self) {
		return self.getStencilFrontFailOp();
	}
	TS_JSAPI uint32_t tsPipeline_getStencilFrontDepthFailOp(const Pipeline &self) {
		return self.getStencilFrontDepthFailOp();
	}
	TS_JSAPI uint32_t tsPipeline_getStencilFrontDepthPassOp(const Pipeline &self) {
		return self.getStencilFrontDepthPassOp();
	}
	
	// Tellusim::Traversal
	TS_JSAPI Traversal *tsTraversal_new() {
		return new Traversal();
	}
	TS_JSAPI void tsTraversal_delete(Traversal *self) {
		delete self;
	}
	TS_JSAPI bool tsTraversal_equalPtr(const Traversal &self, const Traversal &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Traversal *tsTraversal_clonePtr(const Traversal &self) {
		return new Traversal(self.clonePtr());
	}
	TS_JSAPI void tsTraversal_clearPtr(Traversal &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsTraversal_destroyPtr(Traversal &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsTraversal_acquirePtr(Traversal &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsTraversal_unacquirePtr(Traversal &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsTraversal_isValidPtr(const Traversal &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsTraversal_isOwnerPtr(const Traversal &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsTraversal_isConstPtr(const Traversal &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsTraversal_getCountPtr(const Traversal &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsTraversal_getInternalPtr(const Traversal &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI uint32_t tsTraversal_getPlatform(const Traversal &self) {
		return self.getPlatform();
	}
	TS_JSAPI const char* tsTraversal_getPlatformName(const Traversal &self) {
		return self.getPlatformName();
	}
	TS_JSAPI uint32_t tsTraversal_getIndex(const Traversal &self) {
		return self.getIndex();
	}
	TS_JSAPI void tsTraversal_clear(Traversal &self) {
		self.clear();
	}
	TS_JSAPI bool tsTraversal_isCreated(const Traversal &self) {
		return self.isCreated();
	}
	TS_JSAPI void tsTraversal_setName(Traversal &self, const char *name) {
		self.setName(name);
	}
	TS_JSAPI String *tsTraversal_getName(const Traversal &self) {
		return new String(self.getName());
	}
	TS_JSAPI bool tsTraversal_create(Traversal &self) {
		return self.create();
	}
	TS_JSAPI void tsTraversal_setParameters(Traversal &self, const Traversal &traversal) {
		self.setParameters(traversal);
	}
	TS_JSAPI bool tsTraversal_saveState(const Traversal &self, Stream &stream) {
		return self.saveState(stream);
	}
	TS_JSAPI void tsTraversal_addShader(Traversal &self, Shader &shader, bool owner) {
		self.addShader(shader, owner);
	}
	TS_JSAPI Shader *tsTraversal_getRayGenShader(const Traversal &self) {
		return new Shader(self.getRayGenShader());
	}
	TS_JSAPI bool tsTraversal_loadShader(Traversal &self, uint32_t type, const char *name, const char *format) {
		return self.loadShader((Shader::Type)type, name, "%s", format);
	}
	TS_JSAPI bool tsTraversal_loadShaderGLSL(Traversal &self, uint32_t type, const char *name, const char *format) {
		return self.loadShaderGLSL((Shader::Type)type, name, "%s", format);
	}
	TS_JSAPI bool tsTraversal_loadShader_1(Traversal &self, uint32_t type, const char *name, const String &macros, const char **includes, uint32_t size) {
		return self.loadShader((Shader::Type)type, name, macros, includes, size);
	}
	TS_JSAPI bool tsTraversal_loadShaderGLSL_1(Traversal &self, uint32_t type, const char *name, const String &macros, const char **includes, uint32_t size) {
		return self.loadShaderGLSL((Shader::Type)type, name, macros, includes, size);
	}
	TS_JSAPI bool tsTraversal_loadShaderSPIRV(Traversal &self, uint32_t type, const char *name) {
		return self.loadShaderSPIRV((Shader::Type)type, name);
	}
	TS_JSAPI bool tsTraversal_createShader(Traversal &self, uint32_t type, const char *src, const char *format) {
		return self.createShader((Shader::Type)type, src, "%s", format);
	}
	TS_JSAPI bool tsTraversal_createShaderGLSL(Traversal &self, uint32_t type, const char *src, const char *format) {
		return self.createShaderGLSL((Shader::Type)type, src, "%s", format);
	}
	TS_JSAPI bool tsTraversal_createShader_1(Traversal &self, uint32_t type, const char *src, const String &macros, const char **includes, uint32_t size) {
		return self.createShader((Shader::Type)type, src, macros, includes, size);
	}
	TS_JSAPI bool tsTraversal_createShaderGLSL_1(Traversal &self, uint32_t type, const char *src, const String &macros, const char **includes, uint32_t size) {
		return self.createShaderGLSL((Shader::Type)type, src, macros, includes, size);
	}
	TS_JSAPI bool tsTraversal_createShaderSPIRV(Traversal &self, uint32_t type, Array<uint32_t> &data) {
		return self.createShaderSPIRV((Shader::Type)type, data);
	}
	TS_JSAPI uint32_t tsTraversal_addSampler(Traversal &self, uint32_t mask) {
		return self.addSampler((Shader::Mask)mask);
	}
	TS_JSAPI uint32_t tsTraversal_getNumSamplers(const Traversal &self) {
		return self.getNumSamplers();
	}
	TS_JSAPI Traversal *tsTraversal_setSamplerOffset(Traversal &self, uint32_t offset) {
		return new Traversal(self.setSamplerOffset(offset));
	}
	TS_JSAPI uint32_t tsTraversal_getSamplerOffset(const Traversal &self) {
		return self.getSamplerOffset();
	}
	TS_JSAPI Traversal *tsTraversal_setSamplerMask(Traversal &self, uint32_t index, uint32_t mask) {
		return new Traversal(self.setSamplerMask(index, (Shader::Mask)mask));
	}
	TS_JSAPI uint32_t tsTraversal_getSamplerMask(const Traversal &self, uint32_t index) {
		return self.getSamplerMask(index);
	}
	TS_JSAPI Traversal *tsTraversal_setSamplerMasks(Traversal &self, uint32_t index, uint32_t num, uint32_t mask, bool array) {
		return new Traversal(self.setSamplerMasks(index, num, (Shader::Mask)mask, array));
	}
	TS_JSAPI uint32_t tsTraversal_getSamplerMasks(const Traversal &self, uint32_t index, uint32_t num) {
		return self.getSamplerMasks(index, num);
	}
	TS_JSAPI Traversal *tsTraversal_setSamplerArray(Traversal &self, uint32_t index, uint32_t num, bool array) {
		return new Traversal(self.setSamplerArray(index, num, array));
	}
	TS_JSAPI uint32_t tsTraversal_getSamplerArray(const Traversal &self, uint32_t index) {
		return self.getSamplerArray(index);
	}
	TS_JSAPI uint32_t tsTraversal_addTexture(Traversal &self, uint32_t mask) {
		return self.addTexture((Shader::Mask)mask);
	}
	TS_JSAPI uint32_t tsTraversal_getNumTextures(const Traversal &self) {
		return self.getNumTextures();
	}
	TS_JSAPI Traversal *tsTraversal_setTextureOffset(Traversal &self, uint32_t offset) {
		return new Traversal(self.setTextureOffset(offset));
	}
	TS_JSAPI uint32_t tsTraversal_getTextureOffset(const Traversal &self) {
		return self.getTextureOffset();
	}
	TS_JSAPI Traversal *tsTraversal_setTextureMask(Traversal &self, uint32_t index, uint32_t mask) {
		return new Traversal(self.setTextureMask(index, (Shader::Mask)mask));
	}
	TS_JSAPI uint32_t tsTraversal_getTextureMask(const Traversal &self, uint32_t index) {
		return self.getTextureMask(index);
	}
	TS_JSAPI Traversal *tsTraversal_setTextureMasks(Traversal &self, uint32_t index, uint32_t num, uint32_t mask, bool array) {
		return new Traversal(self.setTextureMasks(index, num, (Shader::Mask)mask, array));
	}
	TS_JSAPI uint32_t tsTraversal_getTextureMasks(const Traversal &self, uint32_t index, uint32_t num) {
		return self.getTextureMasks(index, num);
	}
	TS_JSAPI Traversal *tsTraversal_setTextureArray(Traversal &self, uint32_t index, uint32_t num, bool array) {
		return new Traversal(self.setTextureArray(index, num, array));
	}
	TS_JSAPI uint32_t tsTraversal_getTextureArray(const Traversal &self, uint32_t index) {
		return self.getTextureArray(index);
	}
	TS_JSAPI uint32_t tsTraversal_addSurface(Traversal &self, uint32_t mask) {
		return self.addSurface((Shader::Mask)mask);
	}
	TS_JSAPI uint32_t tsTraversal_getNumSurfaces(const Traversal &self) {
		return self.getNumSurfaces();
	}
	TS_JSAPI Traversal *tsTraversal_setSurfaceOffset(Traversal &self, uint32_t offset) {
		return new Traversal(self.setSurfaceOffset(offset));
	}
	TS_JSAPI uint32_t tsTraversal_getSurfaceOffset(const Traversal &self) {
		return self.getSurfaceOffset();
	}
	TS_JSAPI Traversal *tsTraversal_setSurfaceMask(Traversal &self, uint32_t index, uint32_t mask) {
		return new Traversal(self.setSurfaceMask(index, (Shader::Mask)mask));
	}
	TS_JSAPI uint32_t tsTraversal_getSurfaceMask(const Traversal &self, uint32_t index) {
		return self.getSurfaceMask(index);
	}
	TS_JSAPI Traversal *tsTraversal_setSurfaceMasks(Traversal &self, uint32_t index, uint32_t num, uint32_t mask, bool array) {
		return new Traversal(self.setSurfaceMasks(index, num, (Shader::Mask)mask, array));
	}
	TS_JSAPI uint32_t tsTraversal_getSurfaceMasks(const Traversal &self, uint32_t index, uint32_t num) {
		return self.getSurfaceMasks(index, num);
	}
	TS_JSAPI Traversal *tsTraversal_setSurfaceArray(Traversal &self, uint32_t index, uint32_t num, bool array) {
		return new Traversal(self.setSurfaceArray(index, num, array));
	}
	TS_JSAPI uint32_t tsTraversal_getSurfaceArray(const Traversal &self, uint32_t index) {
		return self.getSurfaceArray(index);
	}
	TS_JSAPI uint32_t tsTraversal_addUniform(Traversal &self, uint32_t mask, uint32_t flags) {
		return self.addUniform((Shader::Mask)mask, (BindFlags)flags);
	}
	TS_JSAPI uint32_t tsTraversal_getNumUniforms(const Traversal &self) {
		return self.getNumUniforms();
	}
	TS_JSAPI Traversal *tsTraversal_setUniformOffset(Traversal &self, uint32_t offset) {
		return new Traversal(self.setUniformOffset(offset));
	}
	TS_JSAPI uint32_t tsTraversal_getUniformOffset(const Traversal &self) {
		return self.getUniformOffset();
	}
	TS_JSAPI Traversal *tsTraversal_setUniformMask(Traversal &self, uint32_t index, uint32_t mask, uint32_t flags) {
		return new Traversal(self.setUniformMask(index, (Shader::Mask)mask, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsTraversal_getUniformMask(const Traversal &self, uint32_t index) {
		return self.getUniformMask(index);
	}
	TS_JSAPI Traversal *tsTraversal_setUniformMasks(Traversal &self, uint32_t index, uint32_t num, uint32_t mask, uint32_t flags) {
		return new Traversal(self.setUniformMasks(index, num, (Shader::Mask)mask, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsTraversal_getUniformMasks(const Traversal &self, uint32_t index, uint32_t num) {
		return self.getUniformMasks(index, num);
	}
	TS_JSAPI Traversal *tsTraversal_setUniformFlags(Traversal &self, uint32_t index, uint32_t flags) {
		return new Traversal(self.setUniformFlags(index, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsTraversal_getUniformFlags(const Traversal &self, uint32_t index) {
		return self.getUniformFlags(index);
	}
	TS_JSAPI uint32_t tsTraversal_addStorage(Traversal &self, uint32_t mask, uint32_t flags) {
		return self.addStorage((Shader::Mask)mask, (BindFlags)flags);
	}
	TS_JSAPI uint32_t tsTraversal_getNumStorages(const Traversal &self) {
		return self.getNumStorages();
	}
	TS_JSAPI Traversal *tsTraversal_setStorageOffset(Traversal &self, uint32_t offset) {
		return new Traversal(self.setStorageOffset(offset));
	}
	TS_JSAPI uint32_t tsTraversal_getStorageOffset(const Traversal &self) {
		return self.getStorageOffset();
	}
	TS_JSAPI Traversal *tsTraversal_setStorageMask(Traversal &self, uint32_t index, uint32_t mask, uint32_t flags) {
		return new Traversal(self.setStorageMask(index, (Shader::Mask)mask, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsTraversal_getStorageMask(const Traversal &self, uint32_t index) {
		return self.getStorageMask(index);
	}
	TS_JSAPI Traversal *tsTraversal_setStorageMasks(Traversal &self, uint32_t index, uint32_t num, uint32_t mask, uint32_t flags) {
		return new Traversal(self.setStorageMasks(index, num, (Shader::Mask)mask, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsTraversal_getStorageMasks(const Traversal &self, uint32_t index, uint32_t num) {
		return self.getStorageMasks(index, num);
	}
	TS_JSAPI Traversal *tsTraversal_setStorageFlags(Traversal &self, uint32_t index, uint32_t flags) {
		return new Traversal(self.setStorageFlags(index, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsTraversal_getStorageFlags(const Traversal &self, uint32_t index) {
		return self.getStorageFlags(index);
	}
	TS_JSAPI uint32_t tsTraversal_addTracing(Traversal &self, uint32_t mask) {
		return self.addTracing((Shader::Mask)mask);
	}
	TS_JSAPI uint32_t tsTraversal_getNumTracings(const Traversal &self) {
		return self.getNumTracings();
	}
	TS_JSAPI Traversal *tsTraversal_setTracingOffset(Traversal &self, uint32_t offset) {
		return new Traversal(self.setTracingOffset(offset));
	}
	TS_JSAPI uint32_t tsTraversal_getTracingOffset(const Traversal &self) {
		return self.getTracingOffset();
	}
	TS_JSAPI Traversal *tsTraversal_setTracingMask(Traversal &self, uint32_t index, uint32_t mask) {
		return new Traversal(self.setTracingMask(index, (Shader::Mask)mask));
	}
	TS_JSAPI uint32_t tsTraversal_getTracingMask(const Traversal &self, uint32_t index) {
		return self.getTracingMask(index);
	}
	TS_JSAPI Traversal *tsTraversal_setTracingMasks(Traversal &self, uint32_t index, uint32_t num, uint32_t mask) {
		return new Traversal(self.setTracingMasks(index, num, (Shader::Mask)mask));
	}
	TS_JSAPI uint32_t tsTraversal_getTracingMasks(const Traversal &self, uint32_t index, uint32_t num) {
		return self.getTracingMasks(index, num);
	}
	TS_JSAPI uint32_t tsTraversal_addTexel(Traversal &self, uint32_t mask) {
		return self.addTexel((Shader::Mask)mask);
	}
	TS_JSAPI uint32_t tsTraversal_getNumTexels(const Traversal &self) {
		return self.getNumTexels();
	}
	TS_JSAPI Traversal *tsTraversal_setTexelOffset(Traversal &self, uint32_t offset) {
		return new Traversal(self.setTexelOffset(offset));
	}
	TS_JSAPI uint32_t tsTraversal_getTexelOffset(const Traversal &self) {
		return self.getTexelOffset();
	}
	TS_JSAPI Traversal *tsTraversal_setTexelMask(Traversal &self, uint32_t index, uint32_t mask) {
		return new Traversal(self.setTexelMask(index, (Shader::Mask)mask));
	}
	TS_JSAPI uint32_t tsTraversal_getTexelMask(const Traversal &self, uint32_t index) {
		return self.getTexelMask(index);
	}
	TS_JSAPI Traversal *tsTraversal_setTexelMasks(Traversal &self, uint32_t index, uint32_t num, uint32_t mask) {
		return new Traversal(self.setTexelMasks(index, num, (Shader::Mask)mask));
	}
	TS_JSAPI uint32_t tsTraversal_getTexelMasks(const Traversal &self, uint32_t index, uint32_t num) {
		return self.getTexelMasks(index, num);
	}
	TS_JSAPI uint32_t tsTraversal_addTable(Traversal &self, uint32_t type, uint32_t size, uint32_t mask, uint32_t flags) {
		return self.addTable((TableType)type, size, (Shader::Mask)mask, (BindFlags)flags);
	}
	TS_JSAPI uint32_t tsTraversal_getNumTables(const Traversal &self) {
		return self.getNumTables();
	}
	TS_JSAPI Traversal *tsTraversal_setTableOffset(Traversal &self, uint32_t offset) {
		return new Traversal(self.setTableOffset(offset));
	}
	TS_JSAPI uint32_t tsTraversal_getTableOffset(const Traversal &self) {
		return self.getTableOffset();
	}
	TS_JSAPI Traversal *tsTraversal_setTableType(Traversal &self, uint32_t index, uint32_t type, uint32_t size, uint32_t mask, uint32_t flags) {
		return new Traversal(self.setTableType(index, (TableType)type, size, (Shader::Mask)mask, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsTraversal_getTableType(const Traversal &self, uint32_t index) {
		return self.getTableType(index);
	}
	TS_JSAPI uint32_t tsTraversal_getTableSize(const Traversal &self, uint32_t index) {
		return self.getTableSize(index);
	}
	TS_JSAPI Traversal *tsTraversal_setTableMask(Traversal &self, uint32_t index, uint32_t mask, uint32_t flags) {
		return new Traversal(self.setTableMask(index, (Shader::Mask)mask, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsTraversal_getTableMask(const Traversal &self, uint32_t index) {
		return self.getTableMask(index);
	}
	TS_JSAPI Traversal *tsTraversal_setTableFlags(Traversal &self, uint32_t index, uint32_t flags) {
		return new Traversal(self.setTableFlags(index, (BindFlags)flags));
	}
	TS_JSAPI uint32_t tsTraversal_getTableFlags(const Traversal &self, uint32_t index) {
		return self.getTableFlags(index);
	}
	TS_JSAPI void tsTraversal_setRecursionDepth(Traversal &self, uint32_t depth) {
		self.setRecursionDepth(depth);
	}
	TS_JSAPI uint32_t tsTraversal_getRecursionDepth(const Traversal &self) {
		return self.getRecursionDepth();
	}
	
	// Tellusim::Surface
	TS_JSAPI Surface *tsSurface_new() {
		return new Surface();
	}
	TS_JSAPI Surface *tsSurface_new_1(Context &context) {
		return new Surface(context);
	}
	TS_JSAPI Surface *tsSurface_new_2(uint32_t platform) {
		return new Surface((Platform)platform);
	}
	TS_JSAPI void tsSurface_delete(Surface *self) {
		delete self;
	}
	TS_JSAPI bool tsSurface_equalPtr(const Surface &self, const Surface &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Surface *tsSurface_clonePtr(const Surface &self) {
		return new Surface(self.clonePtr());
	}
	TS_JSAPI void tsSurface_clearPtr(Surface &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsSurface_destroyPtr(Surface &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsSurface_acquirePtr(Surface &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsSurface_unacquirePtr(Surface &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsSurface_isValidPtr(const Surface &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsSurface_isOwnerPtr(const Surface &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsSurface_isConstPtr(const Surface &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsSurface_getCountPtr(const Surface &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsSurface_getInternalPtr(const Surface &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI uint32_t tsSurface_getPlatform(const Surface &self) {
		return self.getPlatform();
	}
	TS_JSAPI const char* tsSurface_getPlatformName(const Surface &self) {
		return self.getPlatformName();
	}
	TS_JSAPI uint32_t tsSurface_getIndex(const Surface &self) {
		return self.getIndex();
	}
	TS_JSAPI void tsSurface_setSize(Surface &self, uint32_t width, uint32_t height) {
		self.setSize(width, height);
	}
	TS_JSAPI uint32_t tsSurface_getWidth(const Surface &self) {
		return self.getWidth();
	}
	TS_JSAPI uint32_t tsSurface_getHeight(const Surface &self) {
		return self.getHeight();
	}
	TS_JSAPI void tsSurface_setMultisample(Surface &self, uint32_t multisample) {
		self.setMultisample(multisample);
	}
	TS_JSAPI uint32_t tsSurface_getMultisample(const Surface &self) {
		return self.getMultisample();
	}
	TS_JSAPI bool tsSurface_hasMultisample(const Surface &self) {
		return self.hasMultisample();
	}
	TS_JSAPI void tsSurface_setColorLayer(Surface &self, uint32_t layer, uint32_t layers) {
		self.setColorLayer(layer, layers);
	}
	TS_JSAPI void tsSurface_setDepthLayer(Surface &self, uint32_t layer, uint32_t layers) {
		self.setDepthLayer(layer, layers);
	}
	TS_JSAPI uint32_t tsSurface_getColorLayer(const Surface &self) {
		return self.getColorLayer();
	}
	TS_JSAPI uint32_t tsSurface_getDepthLayer(const Surface &self) {
		return self.getDepthLayer();
	}
	TS_JSAPI uint32_t tsSurface_getColorLayers(const Surface &self) {
		return self.getColorLayers();
	}
	TS_JSAPI uint32_t tsSurface_getDepthLayers(const Surface &self) {
		return self.getDepthLayers();
	}
	TS_JSAPI bool tsSurface_hasColorLayers(const Surface &self) {
		return self.hasColorLayers();
	}
	TS_JSAPI bool tsSurface_hasDepthLayers(const Surface &self) {
		return self.hasDepthLayers();
	}
	TS_JSAPI void tsSurface_setColorFormat(Surface &self, uint32_t format) {
		self.setColorFormat((Format)format);
	}
	TS_JSAPI void tsSurface_setDepthFormat(Surface &self, uint32_t format) {
		self.setDepthFormat((Format)format);
	}
	TS_JSAPI uint32_t tsSurface_getColorFormat(const Surface &self) {
		return self.getColorFormat();
	}
	TS_JSAPI uint32_t tsSurface_getDepthFormat(const Surface &self) {
		return self.getDepthFormat();
	}
	
	// Tellusim::GLESSurface
	TS_JSAPI GLESSurface *tsGLESSurface_new() {
		return new GLESSurface();
	}
	TS_JSAPI GLESSurface *tsGLESSurface_new_1(GLESContext &context) {
		return new GLESSurface(context);
	}
	TS_JSAPI void tsGLESSurface_delete(GLESSurface *self) {
		delete self;
	}
	TS_JSAPI bool tsGLESSurface_equalSurfacePtr(const GLESSurface &self, const Surface &base) {
		return self.operator==(base);
	}
	TS_JSAPI GLESSurface *tsGLESSurface_castSurfacePtr(const Surface &self) {
		return new GLESSurface(self);
	}
	TS_JSAPI Surface *tsGLESSurface_baseSurfacePtr(const GLESSurface &self) {
		return new Surface(self.getSurface());
	}
	TS_JSAPI void* tsGLESSurface_getContext(const GLESSurface &self) {
		return self.getContext();
	}
	TS_JSAPI void tsGLESSurface_setColorTextureID(GLESSurface &self, uint32_t texture_id) {
		self.setColorTextureID(texture_id);
	}
	TS_JSAPI void tsGLESSurface_setDepthTextureID(GLESSurface &self, uint32_t texture_id) {
		self.setDepthTextureID(texture_id);
	}
	TS_JSAPI uint32_t tsGLESSurface_getColorTextureID(const GLESSurface &self) {
		return self.getColorTextureID();
	}
	TS_JSAPI uint32_t tsGLESSurface_getDepthTextureID(const GLESSurface &self) {
		return self.getDepthTextureID();
	}
	TS_JSAPI void tsGLESSurface_setFramebufferID(GLESSurface &self, uint32_t framebuffer_id) {
		self.setFramebufferID(framebuffer_id);
	}
	TS_JSAPI uint32_t tsGLESSurface_getFramebufferID(const GLESSurface &self) {
		return self.getFramebufferID();
	}
	TS_JSAPI uint32_t tsGLESSurface_getColorInternalFormat(const GLESSurface &self) {
		return self.getColorInternalFormat();
	}
	TS_JSAPI uint32_t tsGLESSurface_getDepthInternalFormat(const GLESSurface &self) {
		return self.getDepthInternalFormat();
	}
	
	// Tellusim::Window
	static void window_mouse_pressed_callback(Window::Button button, void *self) {
		EM_ASM({ tsWindow.mouse_pressed_callback($0, $1); }, self, (Window::Button)button);
	}
	static Window::MousePressedCallback make_window_mouse_pressed_callback(void *self) {
		auto ret = makeFunction(window_mouse_pressed_callback);
		ret.setArg1(self);
		return ret;
	}
	static void window_mouse_released_callback(Window::Button button, void *self) {
		EM_ASM({ tsWindow.mouse_released_callback($0, $1); }, self, (Window::Button)button);
	}
	static Window::MouseReleasedCallback make_window_mouse_released_callback(void *self) {
		auto ret = makeFunction(window_mouse_released_callback);
		ret.setArg1(self);
		return ret;
	}
	static void window_mouse_changed_callback(int32_t x, int32_t y, void *self) {
		EM_ASM({ tsWindow.mouse_changed_callback($0, $1, $2); }, self, x, y);
	}
	static Window::MouseChangedCallback make_window_mouse_changed_callback(void *self) {
		auto ret = makeFunction(window_mouse_changed_callback);
		ret.setArg2(self);
		return ret;
	}
	static void window_mouse_rotated_callback(Window::Axis axis, float32_t delta, void *self) {
		EM_ASM({ tsWindow.mouse_rotated_callback($0, $1, $2); }, self, (Window::Axis)axis, delta);
	}
	static Window::MouseRotatedCallback make_window_mouse_rotated_callback(void *self) {
		auto ret = makeFunction(window_mouse_rotated_callback);
		ret.setArg2(self);
		return ret;
	}
	static void window_touch_changed_callback(void *self) {
		EM_ASM({ tsWindow.touch_changed_callback($0); }, self);
	}
	static Window::TouchChangedCallback make_window_touch_changed_callback(void *self) {
		auto ret = makeFunction(window_touch_changed_callback);
		ret.setArg0(self);
		return ret;
	}
	static void window_keyboard_pressed_callback(uint32_t key, uint32_t code, void *self) {
		EM_ASM({ tsWindow.keyboard_pressed_callback($0, $1, $2); }, self, key, code);
	}
	static Window::KeyboardPressedCallback make_window_keyboard_pressed_callback(void *self) {
		auto ret = makeFunction(window_keyboard_pressed_callback);
		ret.setArg2(self);
		return ret;
	}
	static void window_keyboard_released_callback(uint32_t key, void *self) {
		EM_ASM({ tsWindow.keyboard_released_callback($0, $1); }, self, key);
	}
	static Window::KeyboardReleasedCallback make_window_keyboard_released_callback(void *self) {
		auto ret = makeFunction(window_keyboard_released_callback);
		ret.setArg1(self);
		return ret;
	}
	static void window_size_changed_callback(uint32_t width, uint32_t height, void *self) {
		EM_ASM({ tsWindow.size_changed_callback($0, $1, $2); }, self, width, height);
	}
	static Window::SizeChangedCallback make_window_size_changed_callback(void *self) {
		auto ret = makeFunction(window_size_changed_callback);
		ret.setArg2(self);
		return ret;
	}
	static void window_focus_changed_callback(bool changed, void *self) {
		EM_ASM({ tsWindow.focus_changed_callback($0, $1); }, self, changed);
	}
	static Window::FocusChangedCallback make_window_focus_changed_callback(void *self) {
		auto ret = makeFunction(window_focus_changed_callback);
		ret.setArg1(self);
		return ret;
	}
	static void window_close_clicked_callback(void *self) {
		EM_ASM({ tsWindow.close_clicked_callback($0); }, self);
	}
	static Window::CloseClickedCallback make_window_close_clicked_callback(void *self) {
		auto ret = makeFunction(window_close_clicked_callback);
		ret.setArg0(self);
		return ret;
	}
	static void window_pause_changed_callback(bool paused, void *self) {
		EM_ASM({ tsWindow.pause_changed_callback($0, $1); }, self, paused);
	}
	static Window::PauseChangedCallback make_window_pause_changed_callback(void *self) {
		auto ret = makeFunction(window_pause_changed_callback);
		ret.setArg1(self);
		return ret;
	}
	static void window_file_dropped_callback(const char *name, uint32_t remain, void *self) {
		EM_ASM({ tsWindow.file_dropped_callback($0, $1, $2); }, self, name, remain);
	}
	static Window::FileDroppedCallback make_window_file_dropped_callback(void *self) {
		auto ret = makeFunction(window_file_dropped_callback);
		ret.setArg2(self);
		return ret;
	}
	static void window_update_callback(void *self) {
		EM_ASM({ tsWindow.update_callback($0); }, self);
	}
	static Window::UpdateCallback make_window_update_callback(void *self) {
		auto ret = makeFunction(window_update_callback);
		ret.setArg0(self);
		return ret;
	}
	static void window_present_callback(void *self) {
		EM_ASM({ tsWindow.present_callback($0); }, self);
	}
	static Window::PresentCallback make_window_present_callback(void *self) {
		auto ret = makeFunction(window_present_callback);
		ret.setArg0(self);
		return ret;
	}
	static bool window_main_loop_callback(void *self) {
		return EM_ASM_INT({ return tsWindow.main_loop_callback($0); }, self) != 0;
	}
	static Window::MainLoopCallback make_window_main_loop_callback(void *self) {
		auto ret = makeFunction(window_main_loop_callback);
		ret.setArg0(self);
		return ret;
	}
	TS_JSAPI Window *tsWindow_new() {
		return new Window();
	}
	TS_JSAPI Window *tsWindow_new_1(uint32_t platform, uint32_t index) {
		return new Window((Platform)platform, index);
	}
	TS_JSAPI Window *tsWindow_new_2(Surface &surface) {
		return new Window(surface);
	}
	TS_JSAPI void tsWindow_delete(Window *self) {
		delete self;
	}
	TS_JSAPI bool tsWindow_equalPtr(const Window &self, const Window &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Window *tsWindow_clonePtr(const Window &self) {
		return new Window(self.clonePtr());
	}
	TS_JSAPI void tsWindow_clearPtr(Window &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsWindow_destroyPtr(Window &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsWindow_acquirePtr(Window &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsWindow_unacquirePtr(Window &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsWindow_isValidPtr(const Window &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsWindow_isOwnerPtr(const Window &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsWindow_isConstPtr(const Window &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsWindow_getCountPtr(const Window &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsWindow_getInternalPtr(const Window &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI uint32_t tsWindow_getNumWindows() {
		return Window::getNumWindows();
	}
	TS_JSAPI Window *tsWindow_getWindow(uint32_t index) {
		return new Window(Window::getWindow(index));
	}
	TS_JSAPI void tsWindow_update(bool wait) {
		Window::update(wait);
	}
	TS_JSAPI uint32_t tsWindow_getPlatform(const Window &self) {
		return self.getPlatform();
	}
	TS_JSAPI const char* tsWindow_getPlatformName(const Window &self) {
		return self.getPlatformName();
	}
	TS_JSAPI uint32_t tsWindow_getIndex(const Window &self) {
		return self.getIndex();
	}
	TS_JSAPI void tsWindow_setSurface(Window &self, Surface &surface) {
		self.setSurface(surface);
	}
	TS_JSAPI Surface *tsWindow_getSurface(const Window &self) {
		return new Surface(self.getSurface());
	}
	TS_JSAPI void* tsWindow_getHandle(const Window &self) {
		return self.getHandle();
	}
	TS_JSAPI bool tsWindow_isCreated(const Window &self) {
		return self.isCreated();
	}
	TS_JSAPI bool tsWindow_create(Window &self, const char *title, uint32_t flags) {
		return self.create(title, (Window::Flags)flags);
	}
	TS_JSAPI bool tsWindow_create_1(Window &self, const String &title, uint32_t flags) {
		return self.create(title, (Window::Flags)flags);
	}
	TS_JSAPI bool tsWindow_create_2(Window &self, uint32_t flags) {
		return self.create((Window::Flags)flags);
	}
	TS_JSAPI void tsWindow_release(Window &self) {
		self.release();
	}
	TS_JSAPI bool tsWindow_clear(Window &self, const Color &color) {
		return self.clear(color);
	}
	TS_JSAPI bool tsWindow_grab(const Window &self, Image &image) {
		return self.grab(image);
	}
	TS_JSAPI bool tsWindow_render(Window &self) {
		return self.render();
	}
	TS_JSAPI bool tsWindow_present(Window &self) {
		return self.present();
	}
	TS_JSAPI bool tsWindow_finish(Window &self) {
		return self.finish();
	}
	TS_JSAPI uint32_t tsWindow_getColorFormat(const Window &self) {
		return self.getColorFormat();
	}
	TS_JSAPI uint32_t tsWindow_getDepthFormat(const Window &self) {
		return self.getDepthFormat();
	}
	TS_JSAPI uint32_t tsWindow_getMultisample(const Window &self) {
		return self.getMultisample();
	}
	TS_JSAPI bool tsWindow_hasMultisample(const Window &self) {
		return self.hasMultisample();
	}
	TS_JSAPI void tsWindow_setFlags(Window &self, uint32_t flags) {
		self.setFlags((Window::Flags)flags);
	}
	TS_JSAPI uint32_t tsWindow_getFlags(const Window &self) {
		return self.getFlags();
	}
	TS_JSAPI bool tsWindow_hasFlag(const Window &self, uint32_t flags) {
		return self.hasFlag((Window::Flags)flags);
	}
	TS_JSAPI bool tsWindow_hasFlags(const Window &self, uint32_t flags) {
		return self.hasFlags((Window::Flags)flags);
	}
	TS_JSAPI void tsWindow_setRefreshRate(Window &self, uint32_t rate) {
		self.setRefreshRate(rate);
	}
	TS_JSAPI uint32_t tsWindow_getRefreshRate(const Window &self) {
		return self.getRefreshRate();
	}
	TS_JSAPI bool tsWindow_setHidden(Window &self, bool hidden) {
		return self.setHidden(hidden);
	}
	TS_JSAPI bool tsWindow_isHidden(const Window &self) {
		return self.isHidden();
	}
	TS_JSAPI bool tsWindow_setFocused(Window &self, bool focused) {
		return self.setFocused(focused);
	}
	TS_JSAPI bool tsWindow_isFocused(const Window &self) {
		return self.isFocused();
	}
	TS_JSAPI bool tsWindow_setMinimized(Window &self, bool minimized) {
		return self.setMinimized(minimized);
	}
	TS_JSAPI bool tsWindow_isMinimized(const Window &self) {
		return self.isMinimized();
	}
	TS_JSAPI bool tsWindow_setFullscreen(Window &self, bool fullscreen) {
		return self.setFullscreen(fullscreen);
	}
	TS_JSAPI bool tsWindow_isFullscreen(const Window &self) {
		return self.isFullscreen();
	}
	TS_JSAPI bool tsWindow_isOccluded(const Window &self) {
		return self.isOccluded();
	}
	TS_JSAPI bool tsWindow_setTitle(Window &self, const char *title) {
		return self.setTitle(title);
	}
	TS_JSAPI bool tsWindow_setTitle_1(Window &self, const String &title) {
		return self.setTitle(title);
	}
	TS_JSAPI String *tsWindow_getTitle(const Window &self) {
		return new String(self.getTitle());
	}
	TS_JSAPI bool tsWindow_setIcon(Window &self, const Image &image) {
		return self.setIcon(image);
	}
	TS_JSAPI Image *tsWindow_getIcon(const Window &self) {
		return new Image(self.getIcon());
	}
	TS_JSAPI bool tsWindow_setGeometry(Window &self, int32_t x, int32_t y, uint32_t width, uint32_t height, bool force) {
		return self.setGeometry(x, y, width, height, force);
	}
	TS_JSAPI bool tsWindow_setPosition(Window &self, int32_t x, int32_t y, bool force) {
		return self.setPosition(x, y, force);
	}
	TS_JSAPI int32_t tsWindow_getPositionX(const Window &self, bool title) {
		return self.getPositionX(title);
	}
	TS_JSAPI int32_t tsWindow_getPositionY(const Window &self, bool title) {
		return self.getPositionY(title);
	}
	TS_JSAPI bool tsWindow_setSize(Window &self, uint32_t width, uint32_t height, bool force) {
		return self.setSize(width, height, force);
	}
	TS_JSAPI uint32_t tsWindow_getWidth(const Window &self) {
		return self.getWidth();
	}
	TS_JSAPI uint32_t tsWindow_getHeight(const Window &self) {
		return self.getHeight();
	}
	TS_JSAPI float32_t tsWindow_getScale(const Window &self) {
		return self.getScale();
	}
	TS_JSAPI uint32_t tsWindow_getDpiX(const Window &self) {
		return self.getDpiX();
	}
	TS_JSAPI uint32_t tsWindow_getDpiY(const Window &self) {
		return self.getDpiY();
	}
	TS_JSAPI bool tsWindow_setMinSize(Window &self, uint32_t width, uint32_t height, bool force) {
		return self.setMinSize(width, height, force);
	}
	TS_JSAPI uint32_t tsWindow_getMinWidth(const Window &self) {
		return self.getMinWidth();
	}
	TS_JSAPI uint32_t tsWindow_getMinHeight(const Window &self) {
		return self.getMinHeight();
	}
	TS_JSAPI bool tsWindow_setMaxSize(Window &self, uint32_t width, uint32_t height, bool force) {
		return self.setMaxSize(width, height, force);
	}
	TS_JSAPI uint32_t tsWindow_getMaxWidth(const Window &self) {
		return self.getMaxWidth();
	}
	TS_JSAPI uint32_t tsWindow_getMaxHeight(const Window &self) {
		return self.getMaxHeight();
	}
	TS_JSAPI bool tsWindow_setMouse(Window &self, int32_t x, int32_t y, bool force) {
		return self.setMouse(x, y, force);
	}
	TS_JSAPI int32_t tsWindow_getMouseX(const Window &self) {
		return self.getMouseX();
	}
	TS_JSAPI int32_t tsWindow_getMouseY(const Window &self) {
		return self.getMouseY();
	}
	TS_JSAPI bool tsWindow_setMouseDelta(Window &self, int32_t dx, int32_t dy) {
		return self.setMouseDelta(dx, dy);
	}
	TS_JSAPI int32_t tsWindow_getMouseDX(const Window &self) {
		return self.getMouseDX();
	}
	TS_JSAPI int32_t tsWindow_getMouseDY(const Window &self) {
		return self.getMouseDY();
	}
	TS_JSAPI bool tsWindow_setMouseHidden(Window &self, bool hidden, bool force) {
		return self.setMouseHidden(hidden, force);
	}
	TS_JSAPI bool tsWindow_isMouseHidden(const Window &self) {
		return self.isMouseHidden();
	}
	TS_JSAPI bool tsWindow_setMouseClipped(Window &self, bool clipped, bool force) {
		return self.setMouseClipped(clipped, force);
	}
	TS_JSAPI bool tsWindow_isMouseClipped(const Window &self) {
		return self.isMouseClipped();
	}
	TS_JSAPI bool tsWindow_isMouseInside(const Window &self) {
		return self.isMouseInside();
	}
	TS_JSAPI bool tsWindow_setMouseCursor(Window &self, uint32_t cursor, bool force) {
		return self.setMouseCursor((Window::Cursor)cursor, force);
	}
	TS_JSAPI uint32_t tsWindow_getMouseCursor(const Window &self) {
		return self.getMouseCursor();
	}
	TS_JSAPI bool tsWindow_setMouseButtons(Window &self, uint32_t buttons) {
		return self.setMouseButtons((Window::Button)buttons);
	}
	TS_JSAPI uint32_t tsWindow_getMouseButtons(const Window &self) {
		return self.getMouseButtons();
	}
	TS_JSAPI bool tsWindow_setMouseButton(Window &self, uint32_t button, bool value) {
		return self.setMouseButton((Window::Button)button, value);
	}
	TS_JSAPI bool tsWindow_getMouseButton(const Window &self, uint32_t button, bool clear) {
		return self.getMouseButton((Window::Button)button, clear);
	}
	TS_JSAPI bool tsWindow_wasMouseButtonReleased(const Window &self, uint32_t button) {
		return self.wasMouseButtonReleased((Window::Button)button);
	}
	TS_JSAPI void tsWindow_releaseMouseButtons(Window &self, uint32_t buttons) {
		self.releaseMouseButtons((Window::Button)buttons);
	}
	TS_JSAPI uint32_t tsWindow_clearMouseButtons(Window &self) {
		return self.clearMouseButtons();
	}
	TS_JSAPI bool tsWindow_setMouseAxis(Window &self, uint32_t axis, float32_t value) {
		return self.setMouseAxis((Window::Axis)axis, value);
	}
	TS_JSAPI float32_t tsWindow_getMouseAxis(const Window &self, uint32_t axis) {
		return self.getMouseAxis((Window::Axis)axis);
	}
	TS_JSAPI float32_t tsWindow_clearMouseAxis(Window &self, uint32_t axis) {
		return self.clearMouseAxis((Window::Axis)axis);
	}
	TS_JSAPI void tsWindow_setMousePressedCallback(Window &self, bool func) {
		self.setMousePressedCallback((func) ? make_window_mouse_pressed_callback(&self) : Window::MousePressedCallback());
	}
	TS_JSAPI void tsWindow_setMouseReleasedCallback(Window &self, bool func) {
		self.setMouseReleasedCallback((func) ? make_window_mouse_released_callback(&self) : Window::MouseReleasedCallback());
	}
	TS_JSAPI void tsWindow_setMouseChangedCallback(Window &self, bool func) {
		self.setMouseChangedCallback((func) ? make_window_mouse_changed_callback(&self) : Window::MouseChangedCallback());
	}
	TS_JSAPI void tsWindow_setMouseRotatedCallback(Window &self, bool func) {
		self.setMouseRotatedCallback((func) ? make_window_mouse_rotated_callback(&self) : Window::MouseRotatedCallback());
	}
	TS_JSAPI uint32_t tsWindow_getNumTouches(const Window &self) {
		return self.getNumTouches();
	}
	TS_JSAPI uint32_t tsWindow_addTouch(Window &self, int32_t x, int32_t y) {
		return self.addTouch(x, y);
	}
	TS_JSAPI int32_t tsWindow_getTouchX(const Window &self, uint32_t touch) {
		return self.getTouchX(touch);
	}
	TS_JSAPI int32_t tsWindow_getTouchY(const Window &self, uint32_t touch) {
		return self.getTouchY(touch);
	}
	TS_JSAPI uint32_t tsWindow_findTouch(const Window &self, int32_t x, int32_t y) {
		return self.findTouch(x, y);
	}
	TS_JSAPI void tsWindow_clearTouches(Window &self) {
		self.clearTouches();
	}
	TS_JSAPI void tsWindow_setTouchChangedCallback(Window &self, bool func) {
		self.setTouchChangedCallback((func) ? make_window_touch_changed_callback(&self) : Window::TouchChangedCallback());
	}
	TS_JSAPI void tsWindow_setKeyboardKey(Window &self, uint32_t key, bool value) {
		self.setKeyboardKey(key, value);
	}
	TS_JSAPI bool tsWindow_getKeyboardKey(const Window &self, uint32_t key, bool clear) {
		return self.getKeyboardKey(key, clear);
	}
	TS_JSAPI bool tsWindow_wasKeyboardKeyPressed(const Window &self, uint32_t key) {
		return self.wasKeyboardKeyPressed(key);
	}
	TS_JSAPI bool tsWindow_wasKeyboardKeyReleased(const Window &self, uint32_t key) {
		return self.wasKeyboardKeyReleased(key);
	}
	TS_JSAPI void tsWindow_setKeyboardPressedCallback(Window &self, bool func) {
		self.setKeyboardPressedCallback((func) ? make_window_keyboard_pressed_callback(&self) : Window::KeyboardPressedCallback());
	}
	TS_JSAPI void tsWindow_setKeyboardReleasedCallback(Window &self, bool func) {
		self.setKeyboardReleasedCallback((func) ? make_window_keyboard_released_callback(&self) : Window::KeyboardReleasedCallback());
	}
	TS_JSAPI void tsWindow_setSizeChangedCallback(Window &self, bool func) {
		self.setSizeChangedCallback((func) ? make_window_size_changed_callback(&self) : Window::SizeChangedCallback());
	}
	TS_JSAPI void tsWindow_setFocusChangedCallback(Window &self, bool func) {
		self.setFocusChangedCallback((func) ? make_window_focus_changed_callback(&self) : Window::FocusChangedCallback());
	}
	TS_JSAPI void tsWindow_setCloseClickedCallback(Window &self, bool func) {
		self.setCloseClickedCallback((func) ? make_window_close_clicked_callback(&self) : Window::CloseClickedCallback());
	}
	TS_JSAPI void tsWindow_setPauseChangedCallback(Window &self, bool func) {
		self.setPauseChangedCallback((func) ? make_window_pause_changed_callback(&self) : Window::PauseChangedCallback());
	}
	TS_JSAPI void tsWindow_setFileDroppedCallback(Window &self, bool func) {
		self.setFileDroppedCallback((func) ? make_window_file_dropped_callback(&self) : Window::FileDroppedCallback());
	}
	TS_JSAPI void tsWindow_setUpdateCallback(Window &self, bool func) {
		self.setUpdateCallback((func) ? make_window_update_callback(&self) : Window::UpdateCallback());
	}
	TS_JSAPI void tsWindow_setPresentCallback(Window &self, bool func) {
		self.setPresentCallback((func) ? make_window_present_callback(&self) : Window::PresentCallback());
	}
	TS_JSAPI bool tsWindow_run(Window &self, bool func) {
		return self.run((func) ? make_window_main_loop_callback(&self) : Window::MainLoopCallback());
	}
	TS_JSAPI bool tsWindow_isRunning(const Window &self) {
		return self.isRunning();
	}
	TS_JSAPI void tsWindow_stop(Window &self) {
		self.stop();
	}
	TS_JSAPI bool tsWindow_setCopyText(Window &self, const char *text) {
		return self.setCopyText(text);
	}
	TS_JSAPI bool tsWindow_setCopyText_1(Window &self, const String &text) {
		return self.setCopyText(text);
	}
	TS_JSAPI String *tsWindow_getPasteText(const Window &self) {
		return new String(self.getPasteText());
	}
	
	// Tellusim::Font
	TS_JSAPI Font *tsFont_new() {
		return new Font();
	}
	TS_JSAPI void tsFont_delete(Font *self) {
		delete self;
	}
	TS_JSAPI bool tsFont_equalPtr(const Font &self, const Font &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Font *tsFont_clonePtr(const Font &self) {
		return new Font(self.clonePtr());
	}
	TS_JSAPI void tsFont_clearPtr(Font &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsFont_destroyPtr(Font &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsFont_acquirePtr(Font &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsFont_unacquirePtr(Font &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsFont_isValidPtr(const Font &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsFont_isOwnerPtr(const Font &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsFont_isConstPtr(const Font &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsFont_getCountPtr(const Font &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsFont_getInternalPtr(const Font &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsFont_clear(Font &self) {
		self.clear();
	}
	TS_JSAPI bool tsFont_isLoaded(const Font &self) {
		return self.isLoaded();
	}
	TS_JSAPI bool tsFont_load(Font &self, const char *name) {
		return self.load(name);
	}
	TS_JSAPI bool tsFont_load_1(Font &self, Stream &stream) {
		return self.load(stream);
	}
	TS_JSAPI float32_t tsFont_getAdvance(Font &self, const FontStyle &style, uint32_t code) {
		return self.getAdvance(style, code);
	}
	TS_JSAPI Rect *tsFont_getRect(Font &self, const Vector3f &position, const FontStyle &style, const char *str) {
		return new Rect(self.getRect(position, style, str));
	}
	TS_JSAPI Rect *tsFont_getRect_1(Font &self, const Vector3f &position, const FontStyle &style, const uint32_t *str) {
		return new Rect(self.getRect(position, style, str));
	}
	TS_JSAPI Rect *tsFont_getRect_2(Font &self, const FontBatch *batches, uint32_t num_batches) {
		return new Rect(self.getRect(batches, num_batches));
	}
	TS_JSAPI Rect *tsFont_getRect_3(Font &self, const FontBatch32 *batches, uint32_t num_batches) {
		return new Rect(self.getRect(batches, num_batches));
	}
	TS_JSAPI void tsFont_create(Font &self, const Device &device, const FontStyle &style, const char *str) {
		self.create(device, style, str);
	}
	TS_JSAPI void tsFont_create_1(Font &self, const Device &device, const FontStyle &style, const uint32_t *str) {
		self.create(device, style, str);
	}
	TS_JSAPI void tsFont_create_2(Font &self, const Device &device, const FontBatch *batches, uint32_t num_batches) {
		self.create(device, batches, num_batches);
	}
	TS_JSAPI void tsFont_create_3(Font &self, const Device &device, const FontBatch32 *batches, uint32_t num_batches) {
		self.create(device, batches, num_batches);
	}
	TS_JSAPI void tsFont_draw(Font &self, Command &command, const Vector3f &position, const FontStyle &style, const char *str) {
		self.draw(command, position, style, str);
	}
	TS_JSAPI void tsFont_draw_1(Font &self, Command &command, const Vector3f &position, const FontStyle &style, const uint32_t *str) {
		self.draw(command, position, style, str);
	}
	TS_JSAPI void tsFont_draw_2(Font &self, Command &command, const FontBatch *batches, uint32_t num_batches) {
		self.draw(command, batches, num_batches);
	}
	TS_JSAPI void tsFont_draw_3(Font &self, Command &command, const FontBatch32 *batches, uint32_t num_batches) {
		self.draw(command, batches, num_batches);
	}
	TS_JSAPI bool tsFont_flush(Font &self, const Device &device) {
		return self.flush(device);
	}
	
	// Tellusim::CanvasElement
	static bool canvas_element_draw_callback(Command command, CanvasElement element, void *self) {
		return EM_ASM_INT({ return tsCanvasElement.draw_callback($0, $1, $2); }, self, new Command(command), new CanvasElement(element)) != 0;
	}
	static CanvasElement::DrawCallback make_canvas_element_draw_callback(void *self) {
		auto ret = makeFunction(canvas_element_draw_callback);
		ret.setArg2(self);
		return ret;
	}
	TS_JSAPI CanvasElement *tsCanvasElement_new() {
		return new CanvasElement();
	}
	TS_JSAPI void tsCanvasElement_delete(CanvasElement *self) {
		delete self;
	}
	TS_JSAPI bool tsCanvasElement_equalPtr(const CanvasElement &self, const CanvasElement &ptr) {
		return (self == ptr);
	}
	TS_JSAPI CanvasElement *tsCanvasElement_clonePtr(const CanvasElement &self) {
		return new CanvasElement(self.clonePtr());
	}
	TS_JSAPI void tsCanvasElement_clearPtr(CanvasElement &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsCanvasElement_destroyPtr(CanvasElement &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsCanvasElement_acquirePtr(CanvasElement &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsCanvasElement_unacquirePtr(CanvasElement &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsCanvasElement_isValidPtr(const CanvasElement &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsCanvasElement_isOwnerPtr(const CanvasElement &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsCanvasElement_isConstPtr(const CanvasElement &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsCanvasElement_getCountPtr(const CanvasElement &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsCanvasElement_getInternalPtr(const CanvasElement &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI uint32_t tsCanvasElement_getType(const CanvasElement &self) {
		return self.getType();
	}
	TS_JSAPI const char* tsCanvasElement_getTypeName(uint32_t type) {
		return CanvasElement::getTypeName((CanvasElement::Type)type);
	}
	TS_JSAPI const char* tsCanvasElement_getTypeName_1(const CanvasElement &self) {
		return self.getTypeName();
	}
	TS_JSAPI bool tsCanvasElement_isText(const CanvasElement &self) {
		return self.isText();
	}
	TS_JSAPI bool tsCanvasElement_isMesh(const CanvasElement &self) {
		return self.isMesh();
	}
	TS_JSAPI bool tsCanvasElement_isRect(const CanvasElement &self) {
		return self.isRect();
	}
	TS_JSAPI bool tsCanvasElement_isTriangle(const CanvasElement &self) {
		return self.isTriangle();
	}
	TS_JSAPI bool tsCanvasElement_isEllipse(const CanvasElement &self) {
		return self.isEllipse();
	}
	TS_JSAPI bool tsCanvasElement_isShape(const CanvasElement &self) {
		return self.isShape();
	}
	TS_JSAPI bool tsCanvasElement_isStrip(const CanvasElement &self) {
		return self.isStrip();
	}
	TS_JSAPI void tsCanvasElement_setCanvas(CanvasElement &self, Canvas &canvas) {
		self.setCanvas(canvas);
	}
	TS_JSAPI const Canvas *tsCanvasElement_getCanvas(const CanvasElement &self) {
		return new Canvas(self.getCanvas());
	}
	TS_JSAPI Canvas *tsCanvasElement_getCanvas_1(CanvasElement &self) {
		return new Canvas(self.getCanvas());
	}
	TS_JSAPI void tsCanvasElement_setMode(CanvasElement &self, uint32_t mode) {
		self.setMode((CanvasElement::Mode)mode);
	}
	TS_JSAPI uint32_t tsCanvasElement_getMode(const CanvasElement &self) {
		return self.getMode();
	}
	TS_JSAPI void tsCanvasElement_setAlign(CanvasElement &self, uint32_t align) {
		self.setAlign((CanvasElement::Align)align);
	}
	TS_JSAPI uint32_t tsCanvasElement_getAlign(const CanvasElement &self) {
		return self.getAlign();
	}
	TS_JSAPI bool tsCanvasElement_hasAlign(const CanvasElement &self, uint32_t align) {
		return self.hasAlign((CanvasElement::Align)align);
	}
	TS_JSAPI bool tsCanvasElement_hasAligns(const CanvasElement &self, uint32_t aligns) {
		return self.hasAligns((CanvasElement::Align)aligns);
	}
	TS_JSAPI void tsCanvasElement_setOrder(CanvasElement &self, int32_t order) {
		self.setOrder(order);
	}
	TS_JSAPI int32_t tsCanvasElement_getOrder(const CanvasElement &self) {
		return self.getOrder();
	}
	TS_JSAPI void tsCanvasElement_setEnabled(CanvasElement &self, bool enabled) {
		self.setEnabled(enabled);
	}
	TS_JSAPI bool tsCanvasElement_isEnabled(const CanvasElement &self) {
		return self.isEnabled();
	}
	TS_JSAPI void tsCanvasElement_clearColor(CanvasElement &self) {
		self.clearColor();
	}
	TS_JSAPI void tsCanvasElement_setColor(CanvasElement &self, uint32_t op) {
		self.setColor((CanvasElement::Stack)op);
	}
	TS_JSAPI void tsCanvasElement_setColor_1(CanvasElement &self, const Color &color, uint32_t op) {
		self.setColor(color, (CanvasElement::Stack)op);
	}
	TS_JSAPI void tsCanvasElement_setColor_2(CanvasElement &self, float32_t r, float32_t g, float32_t b, float32_t a, uint32_t op) {
		self.setColor(r, g, b, a, (CanvasElement::Stack)op);
	}
	TS_JSAPI const Color *tsCanvasElement_getColor(const CanvasElement &self) {
		return new Color(self.getColor());
	}
	TS_JSAPI uint32_t tsCanvasElement_getColorOp(const CanvasElement &self) {
		return self.getColorOp();
	}
	TS_JSAPI void tsCanvasElement_clearTransform(CanvasElement &self) {
		self.clearTransform();
	}
	TS_JSAPI void tsCanvasElement_setTransform(CanvasElement &self, uint32_t op) {
		self.setTransform((CanvasElement::Stack)op);
	}
	TS_JSAPI void tsCanvasElement_setTransform_1(CanvasElement &self, const Matrix4x4f &transform, uint32_t op) {
		self.setTransform(transform, (CanvasElement::Stack)op);
	}
	TS_JSAPI const Matrix4x4f *tsCanvasElement_getTransform(const CanvasElement &self) {
		return new Matrix4x4f(self.getTransform());
	}
	TS_JSAPI uint32_t tsCanvasElement_getTransformOp(const CanvasElement &self) {
		return self.getTransformOp();
	}
	TS_JSAPI void tsCanvasElement_clearScissor(CanvasElement &self) {
		self.clearScissor();
	}
	TS_JSAPI void tsCanvasElement_setScissor(CanvasElement &self, uint32_t op) {
		self.setScissor((CanvasElement::Stack)op);
	}
	TS_JSAPI void tsCanvasElement_setScissor_1(CanvasElement &self, const Rect &scissor, uint32_t op) {
		self.setScissor(scissor, (CanvasElement::Stack)op);
	}
	TS_JSAPI const Rect *tsCanvasElement_getScissor(const CanvasElement &self) {
		return new Rect(self.getScissor());
	}
	TS_JSAPI uint32_t tsCanvasElement_getScissorOp(const CanvasElement &self) {
		return self.getScissorOp();
	}
	TS_JSAPI void tsCanvasElement_setMipmap(CanvasElement &self, float32_t mipmap) {
		self.setMipmap(mipmap);
	}
	TS_JSAPI float32_t tsCanvasElement_getMipmap(const CanvasElement &self) {
		return self.getMipmap();
	}
	TS_JSAPI void tsCanvasElement_setSampler(CanvasElement &self, Sampler &sampler) {
		self.setSampler(sampler);
	}
	TS_JSAPI Sampler *tsCanvasElement_getSampler(const CanvasElement &self) {
		return new Sampler(self.getSampler());
	}
	TS_JSAPI void tsCanvasElement_setFilter(CanvasElement &self, uint32_t filter) {
		self.setFilter((Sampler::Filter)filter);
	}
	TS_JSAPI uint32_t tsCanvasElement_getFilter(const CanvasElement &self) {
		return self.getFilter();
	}
	TS_JSAPI void tsCanvasElement_setAnisotropy(CanvasElement &self, uint32_t anisotropy) {
		self.setAnisotropy(anisotropy);
	}
	TS_JSAPI uint32_t tsCanvasElement_getAnisotropy(const CanvasElement &self) {
		return self.getAnisotropy();
	}
	TS_JSAPI void tsCanvasElement_setWrapMode(CanvasElement &self, uint32_t mode) {
		self.setWrapMode((Sampler::WrapMode)mode);
	}
	TS_JSAPI uint32_t tsCanvasElement_getWrapMode(const CanvasElement &self) {
		return self.getWrapMode();
	}
	TS_JSAPI void tsCanvasElement_setTexture(CanvasElement &self, Texture &texture, bool linear) {
		self.setTexture(texture, linear);
	}
	TS_JSAPI Texture *tsCanvasElement_getTexture(const CanvasElement &self) {
		return new Texture(self.getTexture());
	}
	TS_JSAPI bool tsCanvasElement_getTextureLinear(const CanvasElement &self) {
		return self.getTextureLinear();
	}
	TS_JSAPI void tsCanvasElement_setPipeline(CanvasElement &self, Pipeline pipeline) {
		self.setPipeline(pipeline);
	}
	TS_JSAPI Pipeline *tsCanvasElement_getPipeline(const CanvasElement &self) {
		return new Pipeline(self.getPipeline());
	}
	TS_JSAPI void tsCanvasElement_setPrimitive(CanvasElement &self, uint32_t primitive) {
		self.setPrimitive((Pipeline::Primitive)primitive);
	}
	TS_JSAPI uint32_t tsCanvasElement_getPrimitive(const CanvasElement &self) {
		return self.getPrimitive();
	}
	TS_JSAPI void tsCanvasElement_setCullMode(CanvasElement &self, uint32_t mode) {
		self.setCullMode((Pipeline::CullMode)mode);
	}
	TS_JSAPI uint32_t tsCanvasElement_getCullMode(const CanvasElement &self) {
		return self.getCullMode();
	}
	TS_JSAPI void tsCanvasElement_setFrontMode(CanvasElement &self, uint32_t mode) {
		self.setFrontMode((Pipeline::FrontMode)mode);
	}
	TS_JSAPI uint32_t tsCanvasElement_getFrontMode(const CanvasElement &self) {
		return self.getFrontMode();
	}
	TS_JSAPI void tsCanvasElement_setBlend(CanvasElement &self, uint32_t op, uint32_t src, uint32_t dest) {
		self.setBlend((Pipeline::BlendOp)op, (Pipeline::BlendFunc)src, (Pipeline::BlendFunc)dest);
	}
	TS_JSAPI uint32_t tsCanvasElement_getBlendOp(const CanvasElement &self) {
		return self.getBlendOp();
	}
	TS_JSAPI uint32_t tsCanvasElement_getBlendSrcFunc(const CanvasElement &self) {
		return self.getBlendSrcFunc();
	}
	TS_JSAPI uint32_t tsCanvasElement_getBlendDestFunc(const CanvasElement &self) {
		return self.getBlendDestFunc();
	}
	TS_JSAPI void tsCanvasElement_setColorMask(CanvasElement &self, uint32_t mask) {
		self.setColorMask((Pipeline::ColorMask)mask);
	}
	TS_JSAPI uint32_t tsCanvasElement_getColorMask(const CanvasElement &self) {
		return self.getColorMask();
	}
	TS_JSAPI void tsCanvasElement_setDepthMask(CanvasElement &self, uint32_t mask) {
		self.setDepthMask((Pipeline::DepthMask)mask);
	}
	TS_JSAPI uint32_t tsCanvasElement_getDepthMask(const CanvasElement &self) {
		return self.getDepthMask();
	}
	TS_JSAPI void tsCanvasElement_setDepthFunc(CanvasElement &self, uint32_t func) {
		self.setDepthFunc((Pipeline::DepthFunc)func);
	}
	TS_JSAPI uint32_t tsCanvasElement_getDepthFunc(const CanvasElement &self) {
		return self.getDepthFunc();
	}
	TS_JSAPI void tsCanvasElement_setStencilRef(CanvasElement &self, uint32_t ref) {
		self.setStencilRef(ref);
	}
	TS_JSAPI void tsCanvasElement_setStencilFunc(CanvasElement &self, uint32_t func, uint32_t fail_op, uint32_t dfail_op, uint32_t dpass_op) {
		self.setStencilFunc((Pipeline::StencilFunc)func, (Pipeline::StencilOp)fail_op, (Pipeline::StencilOp)dfail_op, (Pipeline::StencilOp)dpass_op);
	}
	TS_JSAPI uint32_t tsCanvasElement_getStencilRef(const CanvasElement &self) {
		return self.getStencilRef();
	}
	TS_JSAPI uint32_t tsCanvasElement_getStencilFunc(const CanvasElement &self) {
		return self.getStencilFunc();
	}
	TS_JSAPI uint32_t tsCanvasElement_getStencilFailOp(const CanvasElement &self) {
		return self.getStencilFailOp();
	}
	TS_JSAPI uint32_t tsCanvasElement_getStencilDepthFailOp(const CanvasElement &self) {
		return self.getStencilDepthFailOp();
	}
	TS_JSAPI uint32_t tsCanvasElement_getStencilDepthPassOp(const CanvasElement &self) {
		return self.getStencilDepthPassOp();
	}
	TS_JSAPI void tsCanvasElement_setDrawCallback(CanvasElement &self, bool func) {
		self.setDrawCallback((func) ? make_canvas_element_draw_callback(&self) : CanvasElement::DrawCallback());
	}
	TS_JSAPI const Rect *tsCanvasElement_getRect(CanvasElement &self) {
		return new Rect(self.getRect());
	}
	
	// Tellusim::CanvasText
	TS_JSAPI CanvasText *tsCanvasText_new() {
		return new CanvasText();
	}
	TS_JSAPI CanvasText *tsCanvasText_new_1(Canvas &canvas) {
		return new CanvasText(canvas);
	}
	TS_JSAPI CanvasText *tsCanvasText_new_2(Canvas &canvas, const char *text) {
		return new CanvasText(canvas, text);
	}
	TS_JSAPI CanvasText *tsCanvasText_new_3(Canvas &canvas, const String &text) {
		return new CanvasText(canvas, text);
	}
	TS_JSAPI void tsCanvasText_delete(CanvasText *self) {
		delete self;
	}
	TS_JSAPI bool tsCanvasText_equalCanvasElementPtr(const CanvasText &self, const CanvasElement &base) {
		return self.operator==(base);
	}
	TS_JSAPI CanvasText *tsCanvasText_castCanvasElementPtr(const CanvasElement &self) {
		return new CanvasText(self);
	}
	TS_JSAPI CanvasElement *tsCanvasText_baseCanvasElementPtr(const CanvasText &self) {
		return new CanvasElement(self.getCanvasElement());
	}
	TS_JSAPI void tsCanvasText_setFontName(CanvasText &self, const char *name) {
		self.setFontName(name);
	}
	TS_JSAPI void tsCanvasText_setFontName_1(CanvasText &self, const String &name) {
		self.setFontName(name);
	}
	TS_JSAPI String *tsCanvasText_getFontName(const CanvasText &self) {
		return new String(self.getFontName());
	}
	TS_JSAPI void tsCanvasText_setFontColor(CanvasText &self, const Color &color) {
		self.setFontColor(color);
	}
	TS_JSAPI const Color *tsCanvasText_getFontColor(const CanvasText &self) {
		return new Color(self.getFontColor());
	}
	TS_JSAPI bool tsCanvasText_setFontSize(CanvasText &self, uint32_t scale) {
		return self.setFontSize(scale);
	}
	TS_JSAPI uint32_t tsCanvasText_getFontSize(const CanvasText &self) {
		return self.getFontSize();
	}
	TS_JSAPI bool tsCanvasText_setFontScale(CanvasText &self, uint32_t scale) {
		return self.setFontScale(scale);
	}
	TS_JSAPI uint32_t tsCanvasText_getFontScale(const CanvasText &self) {
		return self.getFontScale();
	}
	TS_JSAPI bool tsCanvasText_setFontStyle(CanvasText &self, const FontStyle &style) {
		return self.setFontStyle(style);
	}
	TS_JSAPI const FontStyle *tsCanvasText_getFontStyleConst(const CanvasText &self) {
		return new FontStyle(self.getFontStyleConst());
	}
	TS_JSAPI const FontStyle *tsCanvasText_getFontStyle(const CanvasText &self) {
		return new FontStyle(self.getFontStyle());
	}
	TS_JSAPI FontStyle *tsCanvasText_getFontStyle_1(CanvasText &self) {
		return new FontStyle(self.getFontStyle());
	}
	TS_JSAPI void tsCanvasText_setPosition(CanvasText &self, const Vector3f &position) {
		self.setPosition(position);
	}
	TS_JSAPI void tsCanvasText_setPosition_1(CanvasText &self, float32_t x, float32_t y, float32_t z) {
		self.setPosition(x, y, z);
	}
	TS_JSAPI const Vector3f *tsCanvasText_getPosition(const CanvasText &self) {
		return new Vector3f(self.getPosition());
	}
	TS_JSAPI void tsCanvasText_setText(CanvasText &self, const char *text) {
		self.setText(text);
	}
	TS_JSAPI void tsCanvasText_setText_1(CanvasText &self, const String &text) {
		self.setText(text);
	}
	TS_JSAPI String *tsCanvasText_getText(const CanvasText &self) {
		return new String(self.getText());
	}
	TS_JSAPI void tsCanvasText_clearBatches(CanvasText &self) {
		self.clearBatches();
	}
	TS_JSAPI void tsCanvasText_setBatches(CanvasText &self, const FontBatch *batches, uint32_t num_batches) {
		self.setBatches(batches, num_batches);
	}
	
	// Tellusim::CanvasMesh
	TS_JSAPI CanvasMesh *tsCanvasMesh_new() {
		return new CanvasMesh();
	}
	TS_JSAPI CanvasMesh *tsCanvasMesh_new_1(Canvas &canvas) {
		return new CanvasMesh(canvas);
	}
	TS_JSAPI CanvasMesh *tsCanvasMesh_new_2(Canvas &canvas, uint32_t mode) {
		return new CanvasMesh(canvas, (CanvasElement::Mode)mode);
	}
	TS_JSAPI void tsCanvasMesh_delete(CanvasMesh *self) {
		delete self;
	}
	TS_JSAPI bool tsCanvasMesh_equalCanvasElementPtr(const CanvasMesh &self, const CanvasElement &base) {
		return self.operator==(base);
	}
	TS_JSAPI CanvasMesh *tsCanvasMesh_castCanvasElementPtr(const CanvasElement &self) {
		return new CanvasMesh(self);
	}
	TS_JSAPI CanvasElement *tsCanvasMesh_baseCanvasElementPtr(const CanvasMesh &self) {
		return new CanvasElement(self.getCanvasElement());
	}
	TS_JSAPI void tsCanvasMesh_setTextureName(CanvasMesh &self, const char *name) {
		self.setTextureName(name);
	}
	TS_JSAPI void tsCanvasMesh_setTextureName_1(CanvasMesh &self, const String &name) {
		self.setTextureName(name);
	}
	TS_JSAPI String *tsCanvasMesh_getTextureName(const CanvasMesh &self) {
		return new String(self.getTextureName());
	}
	TS_JSAPI void tsCanvasMesh_setGradientStyle(CanvasMesh &self, const GradientStyle &style) {
		self.setGradientStyle(style);
	}
	TS_JSAPI const GradientStyle *tsCanvasMesh_getGradientStyleConst(const CanvasMesh &self) {
		return new GradientStyle(self.getGradientStyleConst());
	}
	TS_JSAPI const GradientStyle *tsCanvasMesh_getGradientStyle(const CanvasMesh &self) {
		return new GradientStyle(self.getGradientStyle());
	}
	TS_JSAPI GradientStyle *tsCanvasMesh_getGradientStyle_1(CanvasMesh &self) {
		return new GradientStyle(self.getGradientStyle());
	}
	TS_JSAPI void tsCanvasMesh_clearVertices(CanvasMesh &self) {
		self.clearVertices();
	}
	TS_JSAPI void tsCanvasMesh_setNumVertices(CanvasMesh &self, uint32_t num_vertices) {
		self.setNumVertices(num_vertices);
	}
	TS_JSAPI void tsCanvasMesh_reserveVertices(CanvasMesh &self, uint32_t num_vertices) {
		self.reserveVertices(num_vertices);
	}
	TS_JSAPI uint32_t tsCanvasMesh_getNumVertices(const CanvasMesh &self) {
		return self.getNumVertices();
	}
	TS_JSAPI void tsCanvasMesh_setVertices(CanvasMesh &self, const CanvasVertex *vertices, uint32_t num_vertices) {
		self.setVertices(vertices, num_vertices);
	}
	TS_JSAPI void tsCanvasMesh_addVertices(CanvasMesh &self, const CanvasVertex *vertices, uint32_t num_vertices) {
		self.addVertices(vertices, num_vertices);
	}
	TS_JSAPI const CanvasVertex* tsCanvasMesh_getVertices(const CanvasMesh &self) {
		return self.getVertices();
	}
	TS_JSAPI CanvasVertex* tsCanvasMesh_getVertices_1(CanvasMesh &self) {
		return self.getVertices();
	}
	TS_JSAPI void tsCanvasMesh_setVertex(CanvasMesh &self, uint32_t index, const CanvasVertex &vertex) {
		self.setVertex(index, vertex);
	}
	TS_JSAPI const CanvasVertex *tsCanvasMesh_getVertex(const CanvasMesh &self, uint32_t index) {
		return new CanvasVertex(self.getVertex(index));
	}
	TS_JSAPI CanvasVertex *tsCanvasMesh_getVertex_1(CanvasMesh &self, uint32_t index) {
		return new CanvasVertex(self.getVertex(index));
	}
	TS_JSAPI void tsCanvasMesh_setVertexPosition(CanvasMesh &self, uint32_t index, const Vector3f &position) {
		self.setVertexPosition(index, position);
	}
	TS_JSAPI void tsCanvasMesh_setVertexPosition_1(CanvasMesh &self, uint32_t index, float32_t x, float32_t y, float32_t z) {
		self.setVertexPosition(index, x, y, z);
	}
	TS_JSAPI Vector3f *tsCanvasMesh_getVertexPosition(const CanvasMesh &self, uint32_t index) {
		return new Vector3f(self.getVertexPosition(index));
	}
	TS_JSAPI void tsCanvasMesh_setVertexTexCoord(CanvasMesh &self, uint32_t index, const Vector2f &texcoord) {
		self.setVertexTexCoord(index, texcoord);
	}
	TS_JSAPI void tsCanvasMesh_setVertexTexCoord_1(CanvasMesh &self, uint32_t index, float32_t s, float32_t t) {
		self.setVertexTexCoord(index, s, t);
	}
	TS_JSAPI Vector2f *tsCanvasMesh_getVertexTexCoord(const CanvasMesh &self, uint32_t index) {
		return new Vector2f(self.getVertexTexCoord(index));
	}
	TS_JSAPI void tsCanvasMesh_setVertexColor(CanvasMesh &self, uint32_t index, const Color &color) {
		self.setVertexColor(index, color);
	}
	TS_JSAPI void tsCanvasMesh_setVertexColor_1(CanvasMesh &self, uint32_t index, uint32_t color) {
		self.setVertexColor(index, color);
	}
	TS_JSAPI uint32_t tsCanvasMesh_getVertexColor(const CanvasMesh &self, uint32_t index) {
		return self.getVertexColor(index);
	}
	TS_JSAPI uint32_t tsCanvasMesh_addVertex(CanvasMesh &self, const Vector3f &position) {
		return self.addVertex(position);
	}
	TS_JSAPI uint32_t tsCanvasMesh_addVertex_1(CanvasMesh &self, const Vector3f &position, uint32_t color) {
		return self.addVertex(position, color);
	}
	TS_JSAPI uint32_t tsCanvasMesh_addVertex_2(CanvasMesh &self, const Vector3f &position, const Vector2f &texcoord) {
		return self.addVertex(position, texcoord);
	}
	TS_JSAPI uint32_t tsCanvasMesh_addVertex_3(CanvasMesh &self, const Vector3f &position, const Vector2f &texcoord, uint32_t color) {
		return self.addVertex(position, texcoord, color);
	}
	TS_JSAPI uint32_t tsCanvasMesh_addVertex_4(CanvasMesh &self, float32_t x, float32_t y, float32_t z, float32_t s, float32_t t, uint32_t color) {
		return self.addVertex(x, y, z, s, t, color);
	}
	TS_JSAPI uint32_t tsCanvasMesh_addVertex_5(CanvasMesh &self, float32_t x, float32_t y, float32_t z, uint32_t color) {
		return self.addVertex(x, y, z, color);
	}
	TS_JSAPI uint32_t tsCanvasMesh_addVertex_6(CanvasMesh &self, float32_t x, float32_t y, uint32_t color) {
		return self.addVertex(x, y, color);
	}
	TS_JSAPI void tsCanvasMesh_clearIndices(CanvasMesh &self) {
		self.clearIndices();
	}
	TS_JSAPI void tsCanvasMesh_setNumIndices(CanvasMesh &self, uint32_t num_indices) {
		self.setNumIndices(num_indices);
	}
	TS_JSAPI void tsCanvasMesh_reserveIndices(CanvasMesh &self, uint32_t num_indices) {
		self.reserveIndices(num_indices);
	}
	TS_JSAPI uint32_t tsCanvasMesh_getNumIndices(const CanvasMesh &self) {
		return self.getNumIndices();
	}
	TS_JSAPI void tsCanvasMesh_setIndices(CanvasMesh &self, const uint32_t *indices, uint32_t num_indices) {
		self.setIndices(indices, num_indices);
	}
	TS_JSAPI void tsCanvasMesh_addIndices(CanvasMesh &self, const uint32_t *indices, uint32_t num_indices) {
		self.addIndices(indices, num_indices);
	}
	TS_JSAPI const uint32_t* tsCanvasMesh_getIndices(const CanvasMesh &self) {
		return self.getIndices();
	}
	TS_JSAPI uint32_t* tsCanvasMesh_getIndices_1(CanvasMesh &self) {
		return self.getIndices();
	}
	TS_JSAPI void tsCanvasMesh_setIndex(CanvasMesh &self, uint32_t index, uint32_t value) {
		self.setIndex(index, value);
	}
	TS_JSAPI uint32_t tsCanvasMesh_getIndex(const CanvasMesh &self, uint32_t index) {
		return self.getIndex(index);
	}
	TS_JSAPI void tsCanvasMesh_addIndex(CanvasMesh &self, uint32_t i0) {
		self.addIndex(i0);
	}
	TS_JSAPI void tsCanvasMesh_addIndices_1(CanvasMesh &self, uint32_t i0, uint32_t i1) {
		self.addIndices(i0, i1);
	}
	TS_JSAPI void tsCanvasMesh_addIndices_2(CanvasMesh &self, uint32_t i0, uint32_t i1, uint32_t i2) {
		self.addIndices(i0, i1, i2);
	}
	TS_JSAPI void tsCanvasMesh_addIndices_3(CanvasMesh &self, uint32_t i0, uint32_t i1, uint32_t i2, uint32_t i3) {
		self.addIndices(i0, i1, i2, i3);
	}
	TS_JSAPI void tsCanvasMesh_setRect(CanvasMesh &self, const Rect &rect) {
		self.setRect(rect);
	}
	
	// Tellusim::CanvasRect
	TS_JSAPI CanvasRect *tsCanvasRect_new() {
		return new CanvasRect();
	}
	TS_JSAPI CanvasRect *tsCanvasRect_new_1(Canvas &canvas) {
		return new CanvasRect(canvas);
	}
	TS_JSAPI CanvasRect *tsCanvasRect_new_2(Canvas &canvas, float32_t radius) {
		return new CanvasRect(canvas, radius);
	}
	TS_JSAPI CanvasRect *tsCanvasRect_new_3(Canvas &canvas, float32_t radius, const Vector2f &size) {
		return new CanvasRect(canvas, radius, size);
	}
	TS_JSAPI void tsCanvasRect_delete(CanvasRect *self) {
		delete self;
	}
	TS_JSAPI bool tsCanvasRect_equalCanvasElementPtr(const CanvasRect &self, const CanvasElement &base) {
		return self.operator==(base);
	}
	TS_JSAPI CanvasRect *tsCanvasRect_castCanvasElementPtr(const CanvasElement &self) {
		return new CanvasRect(self);
	}
	TS_JSAPI CanvasElement *tsCanvasRect_baseCanvasElementPtr(const CanvasRect &self) {
		return new CanvasElement(self.getCanvasElement());
	}
	TS_JSAPI void tsCanvasRect_setRadius(CanvasRect &self, float32_t radius) {
		self.setRadius(radius);
	}
	TS_JSAPI float32_t tsCanvasRect_getRadius(const CanvasRect &self) {
		return self.getRadius();
	}
	TS_JSAPI void tsCanvasRect_setTextureName(CanvasRect &self, const char *name) {
		self.setTextureName(name);
	}
	TS_JSAPI void tsCanvasRect_setTextureName_1(CanvasRect &self, const String &name) {
		self.setTextureName(name);
	}
	TS_JSAPI String *tsCanvasRect_getTextureName(const CanvasRect &self) {
		return new String(self.getTextureName());
	}
	TS_JSAPI void tsCanvasRect_setStrokeColor(CanvasRect &self, const Color &color) {
		self.setStrokeColor(color);
	}
	TS_JSAPI const Color *tsCanvasRect_getStrokeColor(CanvasRect &self) {
		return new Color(self.getStrokeColor());
	}
	TS_JSAPI void tsCanvasRect_setStrokeStyle(CanvasRect &self, const StrokeStyle &style) {
		self.setStrokeStyle(style);
	}
	TS_JSAPI const StrokeStyle *tsCanvasRect_getStrokeStyleConst(const CanvasRect &self) {
		return new StrokeStyle(self.getStrokeStyleConst());
	}
	TS_JSAPI const StrokeStyle *tsCanvasRect_getStrokeStyle(const CanvasRect &self) {
		return new StrokeStyle(self.getStrokeStyle());
	}
	TS_JSAPI StrokeStyle *tsCanvasRect_getStrokeStyle_1(CanvasRect &self) {
		return new StrokeStyle(self.getStrokeStyle());
	}
	TS_JSAPI void tsCanvasRect_setGradientStyle(CanvasRect &self, const GradientStyle &style) {
		self.setGradientStyle(style);
	}
	TS_JSAPI const GradientStyle *tsCanvasRect_getGradientStyleConst(const CanvasRect &self) {
		return new GradientStyle(self.getGradientStyleConst());
	}
	TS_JSAPI const GradientStyle *tsCanvasRect_getGradientStyle(const CanvasRect &self) {
		return new GradientStyle(self.getGradientStyle());
	}
	TS_JSAPI GradientStyle *tsCanvasRect_getGradientStyle_1(CanvasRect &self) {
		return new GradientStyle(self.getGradientStyle());
	}
	TS_JSAPI void tsCanvasRect_setSize(CanvasRect &self, const Vector2f &size) {
		self.setSize(size);
	}
	TS_JSAPI void tsCanvasRect_setSize_1(CanvasRect &self, float32_t width, float32_t height) {
		self.setSize(width, height);
	}
	TS_JSAPI const Vector2f *tsCanvasRect_getSize(const CanvasRect &self) {
		return new Vector2f(self.getSize());
	}
	TS_JSAPI float32_t tsCanvasRect_getWidth(const CanvasRect &self) {
		return self.getWidth();
	}
	TS_JSAPI float32_t tsCanvasRect_getHeight(const CanvasRect &self) {
		return self.getHeight();
	}
	TS_JSAPI void tsCanvasRect_setPosition(CanvasRect &self, const Vector3f &position) {
		self.setPosition(position);
	}
	TS_JSAPI void tsCanvasRect_setPosition_1(CanvasRect &self, float32_t x, float32_t y, float32_t z) {
		self.setPosition(x, y, z);
	}
	TS_JSAPI const Vector3f *tsCanvasRect_getPosition(const CanvasRect &self) {
		return new Vector3f(self.getPosition());
	}
	TS_JSAPI void tsCanvasRect_setTexCoord(CanvasRect &self, const Rect &texcoord) {
		self.setTexCoord(texcoord);
	}
	TS_JSAPI void tsCanvasRect_setTexCoord_1(CanvasRect &self, float32_t left, float32_t right, float32_t bottom, float32_t top) {
		self.setTexCoord(left, right, bottom, top);
	}
	TS_JSAPI const Rect *tsCanvasRect_getTexCoord(const CanvasRect &self) {
		return new Rect(self.getTexCoord());
	}
	
	// Tellusim::CanvasTriangle
	TS_JSAPI CanvasTriangle *tsCanvasTriangle_new() {
		return new CanvasTriangle();
	}
	TS_JSAPI CanvasTriangle *tsCanvasTriangle_new_1(Canvas &canvas) {
		return new CanvasTriangle(canvas);
	}
	TS_JSAPI CanvasTriangle *tsCanvasTriangle_new_2(Canvas &canvas, float32_t radius) {
		return new CanvasTriangle(canvas, radius);
	}
	TS_JSAPI void tsCanvasTriangle_delete(CanvasTriangle *self) {
		delete self;
	}
	TS_JSAPI bool tsCanvasTriangle_equalCanvasElementPtr(const CanvasTriangle &self, const CanvasElement &base) {
		return self.operator==(base);
	}
	TS_JSAPI CanvasTriangle *tsCanvasTriangle_castCanvasElementPtr(const CanvasElement &self) {
		return new CanvasTriangle(self);
	}
	TS_JSAPI CanvasElement *tsCanvasTriangle_baseCanvasElementPtr(const CanvasTriangle &self) {
		return new CanvasElement(self.getCanvasElement());
	}
	TS_JSAPI void tsCanvasTriangle_setRadius(CanvasTriangle &self, float32_t radius) {
		self.setRadius(radius);
	}
	TS_JSAPI float32_t tsCanvasTriangle_getRadius(const CanvasTriangle &self) {
		return self.getRadius();
	}
	TS_JSAPI void tsCanvasTriangle_setStrokeColor(CanvasTriangle &self, const Color &color) {
		self.setStrokeColor(color);
	}
	TS_JSAPI const Color *tsCanvasTriangle_getStrokeColor(const CanvasTriangle &self) {
		return new Color(self.getStrokeColor());
	}
	TS_JSAPI void tsCanvasTriangle_setStrokeStyle(CanvasTriangle &self, const StrokeStyle &style) {
		self.setStrokeStyle(style);
	}
	TS_JSAPI const StrokeStyle *tsCanvasTriangle_getStrokeStyleConst(const CanvasTriangle &self) {
		return new StrokeStyle(self.getStrokeStyleConst());
	}
	TS_JSAPI const StrokeStyle *tsCanvasTriangle_getStrokeStyle(const CanvasTriangle &self) {
		return new StrokeStyle(self.getStrokeStyle());
	}
	TS_JSAPI StrokeStyle *tsCanvasTriangle_getStrokeStyle_1(CanvasTriangle &self) {
		return new StrokeStyle(self.getStrokeStyle());
	}
	TS_JSAPI void tsCanvasTriangle_setGradientStyle(CanvasTriangle &self, const GradientStyle &style) {
		self.setGradientStyle(style);
	}
	TS_JSAPI const GradientStyle *tsCanvasTriangle_getGradientStyleConst(const CanvasTriangle &self) {
		return new GradientStyle(self.getGradientStyleConst());
	}
	TS_JSAPI const GradientStyle *tsCanvasTriangle_getGradientStyle(const CanvasTriangle &self) {
		return new GradientStyle(self.getGradientStyle());
	}
	TS_JSAPI GradientStyle *tsCanvasTriangle_getGradientStyle_1(CanvasTriangle &self) {
		return new GradientStyle(self.getGradientStyle());
	}
	TS_JSAPI void tsCanvasTriangle_setPosition0(CanvasTriangle &self, const Vector3f &position) {
		self.setPosition0(position);
	}
	TS_JSAPI void tsCanvasTriangle_setPosition1(CanvasTriangle &self, const Vector3f &position) {
		self.setPosition1(position);
	}
	TS_JSAPI void tsCanvasTriangle_setPosition2(CanvasTriangle &self, const Vector3f &position) {
		self.setPosition2(position);
	}
	TS_JSAPI void tsCanvasTriangle_setPosition0_1(CanvasTriangle &self, float32_t x, float32_t y, float32_t z) {
		self.setPosition0(x, y, z);
	}
	TS_JSAPI void tsCanvasTriangle_setPosition1_1(CanvasTriangle &self, float32_t x, float32_t y, float32_t z) {
		self.setPosition1(x, y, z);
	}
	TS_JSAPI void tsCanvasTriangle_setPosition2_1(CanvasTriangle &self, float32_t x, float32_t y, float32_t z) {
		self.setPosition2(x, y, z);
	}
	TS_JSAPI void tsCanvasTriangle_setPosition(CanvasTriangle &self, const Vector3f &position_0, const Vector3f &position_1, const Vector3f &position_2) {
		self.setPosition(position_0, position_1, position_2);
	}
	TS_JSAPI const Vector3f *tsCanvasTriangle_getPosition0(const CanvasTriangle &self) {
		return new Vector3f(self.getPosition0());
	}
	TS_JSAPI const Vector3f *tsCanvasTriangle_getPosition1(const CanvasTriangle &self) {
		return new Vector3f(self.getPosition1());
	}
	TS_JSAPI const Vector3f *tsCanvasTriangle_getPosition2(const CanvasTriangle &self) {
		return new Vector3f(self.getPosition2());
	}
	
	// Tellusim::CanvasEllipse
	TS_JSAPI CanvasEllipse *tsCanvasEllipse_new() {
		return new CanvasEllipse();
	}
	TS_JSAPI CanvasEllipse *tsCanvasEllipse_new_1(Canvas &canvas) {
		return new CanvasEllipse(canvas);
	}
	TS_JSAPI CanvasEllipse *tsCanvasEllipse_new_2(Canvas &canvas, float32_t radius) {
		return new CanvasEllipse(canvas, radius);
	}
	TS_JSAPI void tsCanvasEllipse_delete(CanvasEllipse *self) {
		delete self;
	}
	TS_JSAPI bool tsCanvasEllipse_equalCanvasElementPtr(const CanvasEllipse &self, const CanvasElement &base) {
		return self.operator==(base);
	}
	TS_JSAPI CanvasEllipse *tsCanvasEllipse_castCanvasElementPtr(const CanvasElement &self) {
		return new CanvasEllipse(self);
	}
	TS_JSAPI CanvasElement *tsCanvasEllipse_baseCanvasElementPtr(const CanvasEllipse &self) {
		return new CanvasElement(self.getCanvasElement());
	}
	TS_JSAPI void tsCanvasEllipse_setRadius(CanvasEllipse &self, float32_t radius) {
		self.setRadius(radius);
	}
	TS_JSAPI float32_t tsCanvasEllipse_getRadius(const CanvasEllipse &self) {
		return self.getRadius();
	}
	TS_JSAPI void tsCanvasEllipse_setTextureName(CanvasEllipse &self, const char *name) {
		self.setTextureName(name);
	}
	TS_JSAPI void tsCanvasEllipse_setTextureName_1(CanvasEllipse &self, const String &name) {
		self.setTextureName(name);
	}
	TS_JSAPI String *tsCanvasEllipse_getTextureName(const CanvasEllipse &self) {
		return new String(self.getTextureName());
	}
	TS_JSAPI void tsCanvasEllipse_setStrokeColor(CanvasEllipse &self, const Color &color) {
		self.setStrokeColor(color);
	}
	TS_JSAPI const Color *tsCanvasEllipse_getStrokeColor(const CanvasEllipse &self) {
		return new Color(self.getStrokeColor());
	}
	TS_JSAPI void tsCanvasEllipse_setStrokeStyle(CanvasEllipse &self, const StrokeStyle &style) {
		self.setStrokeStyle(style);
	}
	TS_JSAPI const StrokeStyle *tsCanvasEllipse_getStrokeStyleConst(const CanvasEllipse &self) {
		return new StrokeStyle(self.getStrokeStyleConst());
	}
	TS_JSAPI const StrokeStyle *tsCanvasEllipse_getStrokeStyle(const CanvasEllipse &self) {
		return new StrokeStyle(self.getStrokeStyle());
	}
	TS_JSAPI StrokeStyle *tsCanvasEllipse_getStrokeStyle_1(CanvasEllipse &self) {
		return new StrokeStyle(self.getStrokeStyle());
	}
	TS_JSAPI void tsCanvasEllipse_setGradientStyle(CanvasEllipse &self, const GradientStyle &style) {
		self.setGradientStyle(style);
	}
	TS_JSAPI const GradientStyle *tsCanvasEllipse_getGradientStyleConst(const CanvasEllipse &self) {
		return new GradientStyle(self.getGradientStyleConst());
	}
	TS_JSAPI const GradientStyle *tsCanvasEllipse_getGradientStyle(const CanvasEllipse &self) {
		return new GradientStyle(self.getGradientStyle());
	}
	TS_JSAPI GradientStyle *tsCanvasEllipse_getGradientStyle_1(CanvasEllipse &self) {
		return new GradientStyle(self.getGradientStyle());
	}
	TS_JSAPI void tsCanvasEllipse_setPosition(CanvasEllipse &self, const Vector3f &position) {
		self.setPosition(position);
	}
	TS_JSAPI void tsCanvasEllipse_setPosition0(CanvasEllipse &self, const Vector3f &position) {
		self.setPosition0(position);
	}
	TS_JSAPI void tsCanvasEllipse_setPosition1(CanvasEllipse &self, const Vector3f &position) {
		self.setPosition1(position);
	}
	TS_JSAPI void tsCanvasEllipse_setPosition_1(CanvasEllipse &self, float32_t x, float32_t y, float32_t z) {
		self.setPosition(x, y, z);
	}
	TS_JSAPI void tsCanvasEllipse_setPosition0_1(CanvasEllipse &self, float32_t x, float32_t y, float32_t z) {
		self.setPosition0(x, y, z);
	}
	TS_JSAPI void tsCanvasEllipse_setPosition1_1(CanvasEllipse &self, float32_t x, float32_t y, float32_t z) {
		self.setPosition1(x, y, z);
	}
	TS_JSAPI void tsCanvasEllipse_setPosition_2(CanvasEllipse &self, const Vector3f &position_0, const Vector3f &position_1) {
		self.setPosition(position_0, position_1);
	}
	TS_JSAPI const Vector3f *tsCanvasEllipse_getPosition0(const CanvasEllipse &self) {
		return new Vector3f(self.getPosition0());
	}
	TS_JSAPI const Vector3f *tsCanvasEllipse_getPosition1(const CanvasEllipse &self) {
		return new Vector3f(self.getPosition1());
	}
	TS_JSAPI void tsCanvasEllipse_setTexCoord(CanvasEllipse &self, const Rect &texcoord) {
		self.setTexCoord(texcoord);
	}
	TS_JSAPI void tsCanvasEllipse_setTexCoord_1(CanvasEllipse &self, float32_t left, float32_t right, float32_t bottom, float32_t top) {
		self.setTexCoord(left, right, bottom, top);
	}
	TS_JSAPI const Rect *tsCanvasEllipse_getTexCoord(const CanvasEllipse &self) {
		return new Rect(self.getTexCoord());
	}
	
	// Tellusim::CanvasShape
	TS_JSAPI CanvasShape *tsCanvasShape_new() {
		return new CanvasShape();
	}
	TS_JSAPI CanvasShape *tsCanvasShape_new_1(Canvas &canvas) {
		return new CanvasShape(canvas);
	}
	TS_JSAPI CanvasShape *tsCanvasShape_new_2(Canvas &canvas, bool cubic) {
		return new CanvasShape(canvas, cubic);
	}
	TS_JSAPI void tsCanvasShape_delete(CanvasShape *self) {
		delete self;
	}
	TS_JSAPI bool tsCanvasShape_equalCanvasElementPtr(const CanvasShape &self, const CanvasElement &base) {
		return self.operator==(base);
	}
	TS_JSAPI CanvasShape *tsCanvasShape_castCanvasElementPtr(const CanvasElement &self) {
		return new CanvasShape(self);
	}
	TS_JSAPI CanvasElement *tsCanvasShape_baseCanvasElementPtr(const CanvasShape &self) {
		return new CanvasElement(self.getCanvasElement());
	}
	TS_JSAPI void tsCanvasShape_setCubic(CanvasShape &self, bool cubic) {
		self.setCubic(cubic);
	}
	TS_JSAPI bool tsCanvasShape_isCubic(const CanvasShape &self) {
		return self.isCubic();
	}
	TS_JSAPI void tsCanvasShape_setThreshold(CanvasShape &self, float32_t threshold) {
		self.setThreshold(threshold);
	}
	TS_JSAPI float32_t tsCanvasShape_getThreshold(const CanvasShape &self) {
		return self.getThreshold();
	}
	TS_JSAPI void tsCanvasShape_setStrokeColor(CanvasShape &self, const Color &color) {
		self.setStrokeColor(color);
	}
	TS_JSAPI const Color *tsCanvasShape_getStrokeColor(const CanvasShape &self) {
		return new Color(self.getStrokeColor());
	}
	TS_JSAPI void tsCanvasShape_setStrokeStyle(CanvasShape &self, const StrokeStyle &style) {
		self.setStrokeStyle(style);
	}
	TS_JSAPI const StrokeStyle *tsCanvasShape_getStrokeStyleConst(const CanvasShape &self) {
		return new StrokeStyle(self.getStrokeStyleConst());
	}
	TS_JSAPI const StrokeStyle *tsCanvasShape_getStrokeStyle(const CanvasShape &self) {
		return new StrokeStyle(self.getStrokeStyle());
	}
	TS_JSAPI StrokeStyle *tsCanvasShape_getStrokeStyle_1(CanvasShape &self) {
		return new StrokeStyle(self.getStrokeStyle());
	}
	TS_JSAPI void tsCanvasShape_setGradientStyle(CanvasShape &self, const GradientStyle &style) {
		self.setGradientStyle(style);
	}
	TS_JSAPI const GradientStyle *tsCanvasShape_getGradientStyleConst(const CanvasShape &self) {
		return new GradientStyle(self.getGradientStyleConst());
	}
	TS_JSAPI const GradientStyle *tsCanvasShape_getGradientStyle(const CanvasShape &self) {
		return new GradientStyle(self.getGradientStyle());
	}
	TS_JSAPI GradientStyle *tsCanvasShape_getGradientStyle_1(CanvasShape &self) {
		return new GradientStyle(self.getGradientStyle());
	}
	TS_JSAPI bool tsCanvasShape_createSVG(CanvasShape &self, const char *src, float32_t scale) {
		return self.createSVG(src, scale);
	}
	TS_JSAPI void tsCanvasShape_clearPositions(CanvasShape &self) {
		self.clearPositions();
	}
	TS_JSAPI void tsCanvasShape_setNumPositions(CanvasShape &self, uint32_t num_positions) {
		self.setNumPositions(num_positions);
	}
	TS_JSAPI void tsCanvasShape_reservePositions(CanvasShape &self, uint32_t num_positions) {
		self.reservePositions(num_positions);
	}
	TS_JSAPI uint32_t tsCanvasShape_getNumPositions(const CanvasShape &self) {
		return self.getNumPositions();
	}
	TS_JSAPI void tsCanvasShape_setPositions(CanvasShape &self, const Vector3f *positions, uint32_t num_positions) {
		self.setPositions(positions, num_positions);
	}
	TS_JSAPI void tsCanvasShape_addPositions(CanvasShape &self, const Vector3f *positions, uint32_t num_positions) {
		self.addPositions(positions, num_positions);
	}
	TS_JSAPI const Vector3f* tsCanvasShape_getPositions(const CanvasShape &self) {
		return self.getPositions();
	}
	TS_JSAPI Vector3f* tsCanvasShape_getPositions_1(CanvasShape &self) {
		return self.getPositions();
	}
	TS_JSAPI void tsCanvasShape_setPosition(CanvasShape &self, uint32_t index, const Vector3f &position) {
		self.setPosition(index, position);
	}
	TS_JSAPI void tsCanvasShape_setPosition_1(CanvasShape &self, uint32_t index, float32_t x, float32_t y, float32_t z) {
		self.setPosition(index, x, y, z);
	}
	TS_JSAPI const Vector3f *tsCanvasShape_getPosition(const CanvasShape &self, uint32_t index) {
		return new Vector3f(self.getPosition(index));
	}
	TS_JSAPI Vector3f *tsCanvasShape_getPosition_1(CanvasShape &self, uint32_t index) {
		return new Vector3f(self.getPosition(index));
	}
	TS_JSAPI uint32_t tsCanvasShape_addPosition(CanvasShape &self, const Vector2f &position) {
		return self.addPosition(position);
	}
	TS_JSAPI uint32_t tsCanvasShape_addPosition_1(CanvasShape &self, const Vector3f &position) {
		return self.addPosition(position);
	}
	TS_JSAPI uint32_t tsCanvasShape_addPosition_2(CanvasShape &self, float32_t x, float32_t y, float32_t z) {
		return self.addPosition(x, y, z);
	}
	TS_JSAPI void tsCanvasShape_setTexCoord(CanvasShape &self, const Rect &texcoord) {
		self.setTexCoord(texcoord);
	}
	TS_JSAPI void tsCanvasShape_setTexCoord_1(CanvasShape &self, float32_t left, float32_t right, float32_t bottom, float32_t top) {
		self.setTexCoord(left, right, bottom, top);
	}
	TS_JSAPI const Rect *tsCanvasShape_getTexCoord(const CanvasShape &self) {
		return new Rect(self.getTexCoord());
	}
	
	// Tellusim::CanvasStrip
	TS_JSAPI CanvasStrip *tsCanvasStrip_new() {
		return new CanvasStrip();
	}
	TS_JSAPI CanvasStrip *tsCanvasStrip_new_1(Canvas &canvas) {
		return new CanvasStrip(canvas);
	}
	TS_JSAPI CanvasStrip *tsCanvasStrip_new_2(Canvas &canvas, float32_t width) {
		return new CanvasStrip(canvas, width);
	}
	TS_JSAPI void tsCanvasStrip_delete(CanvasStrip *self) {
		delete self;
	}
	TS_JSAPI bool tsCanvasStrip_equalCanvasElementPtr(const CanvasStrip &self, const CanvasElement &base) {
		return self.operator==(base);
	}
	TS_JSAPI CanvasStrip *tsCanvasStrip_castCanvasElementPtr(const CanvasElement &self) {
		return new CanvasStrip(self);
	}
	TS_JSAPI CanvasElement *tsCanvasStrip_baseCanvasElementPtr(const CanvasStrip &self) {
		return new CanvasElement(self.getCanvasElement());
	}
	TS_JSAPI void tsCanvasStrip_setWidth(CanvasStrip &self, float32_t width) {
		self.setWidth(width);
	}
	TS_JSAPI float32_t tsCanvasStrip_getWidth(const CanvasStrip &self) {
		return self.getWidth();
	}
	TS_JSAPI void tsCanvasStrip_setOffset(CanvasStrip &self, float32_t offset) {
		self.setOffset(offset);
	}
	TS_JSAPI float32_t tsCanvasStrip_getOffset(const CanvasStrip &self) {
		return self.getOffset();
	}
	TS_JSAPI void tsCanvasStrip_setStrokeColor(CanvasStrip &self, const Color &color) {
		self.setStrokeColor(color);
	}
	TS_JSAPI const Color *tsCanvasStrip_getStrokeColor(const CanvasStrip &self) {
		return new Color(self.getStrokeColor());
	}
	TS_JSAPI void tsCanvasStrip_setStrokeStyle(CanvasStrip &self, const StrokeStyle &style) {
		self.setStrokeStyle(style);
	}
	TS_JSAPI const StrokeStyle *tsCanvasStrip_getStrokeStyleConst(const CanvasStrip &self) {
		return new StrokeStyle(self.getStrokeStyleConst());
	}
	TS_JSAPI const StrokeStyle *tsCanvasStrip_getStrokeStyle(const CanvasStrip &self) {
		return new StrokeStyle(self.getStrokeStyle());
	}
	TS_JSAPI StrokeStyle *tsCanvasStrip_getStrokeStyle_1(CanvasStrip &self) {
		return new StrokeStyle(self.getStrokeStyle());
	}
	TS_JSAPI void tsCanvasStrip_createQuadratic(CanvasStrip &self, const Vector2f &p0, const Vector2f &p1, const Vector2f &p2, float32_t threshold) {
		self.createQuadratic(p0, p1, p2, threshold);
	}
	TS_JSAPI void tsCanvasStrip_createQuadratic_1(CanvasStrip &self, const Vector3f &p0, const Vector3f &p1, const Vector3f &p2, float32_t threshold) {
		self.createQuadratic(p0, p1, p2, threshold);
	}
	TS_JSAPI void tsCanvasStrip_createCubic(CanvasStrip &self, const Vector2f &p0, const Vector2f &p1, const Vector2f &p2, const Vector2f &p3, float32_t threshold) {
		self.createCubic(p0, p1, p2, p3, threshold);
	}
	TS_JSAPI void tsCanvasStrip_createCubic_1(CanvasStrip &self, const Vector3f &p0, const Vector3f &p1, const Vector3f &p2, const Vector3f &p3, float32_t threshold) {
		self.createCubic(p0, p1, p2, p3, threshold);
	}
	TS_JSAPI void tsCanvasStrip_clearPositions(CanvasStrip &self) {
		self.clearPositions();
	}
	TS_JSAPI void tsCanvasStrip_setNumPositions(CanvasStrip &self, uint32_t num_positions) {
		self.setNumPositions(num_positions);
	}
	TS_JSAPI void tsCanvasStrip_reservePositions(CanvasStrip &self, uint32_t num_positions) {
		self.reservePositions(num_positions);
	}
	TS_JSAPI uint32_t tsCanvasStrip_getNumPositions(const CanvasStrip &self) {
		return self.getNumPositions();
	}
	TS_JSAPI void tsCanvasStrip_setPositions(CanvasStrip &self, const Vector3f *positions, uint32_t num_positions) {
		self.setPositions(positions, num_positions);
	}
	TS_JSAPI void tsCanvasStrip_addPositions(CanvasStrip &self, const Vector3f *positions, uint32_t num_positions) {
		self.addPositions(positions, num_positions);
	}
	TS_JSAPI const Vector3f* tsCanvasStrip_getPositions(const CanvasStrip &self) {
		return self.getPositions();
	}
	TS_JSAPI Vector3f* tsCanvasStrip_getPositions_1(CanvasStrip &self) {
		return self.getPositions();
	}
	TS_JSAPI void tsCanvasStrip_setPosition(CanvasStrip &self, uint32_t index, const Vector3f &position) {
		self.setPosition(index, position);
	}
	TS_JSAPI void tsCanvasStrip_setPosition_1(CanvasStrip &self, uint32_t index, float32_t x, float32_t y, float32_t z) {
		self.setPosition(index, x, y, z);
	}
	TS_JSAPI const Vector3f *tsCanvasStrip_getPosition(const CanvasStrip &self, uint32_t index) {
		return new Vector3f(self.getPosition(index));
	}
	TS_JSAPI Vector3f *tsCanvasStrip_getPosition_1(CanvasStrip &self, uint32_t index) {
		return new Vector3f(self.getPosition(index));
	}
	TS_JSAPI uint32_t tsCanvasStrip_addPosition(CanvasStrip &self, const Vector2f &position) {
		return self.addPosition(position);
	}
	TS_JSAPI uint32_t tsCanvasStrip_addPosition_1(CanvasStrip &self, const Vector3f &position) {
		return self.addPosition(position);
	}
	TS_JSAPI uint32_t tsCanvasStrip_addPosition_2(CanvasStrip &self, float32_t x, float32_t y, float32_t z) {
		return self.addPosition(x, y, z);
	}
	
	// Tellusim::Canvas
	static bool canvas_create_callback(const Device device, Canvas canvas, uint32_t scale, void *self) {
		return EM_ASM_INT({ return tsCanvas.create_callback($0, $1, $2, $3); }, self, new Device(device), new Canvas(canvas), scale) != 0;
	}
	static Canvas::CreateCallback make_canvas_create_callback(void *self) {
		auto ret = makeFunction(canvas_create_callback);
		ret.setArg3(self);
		return ret;
	}
	static bool canvas_pipeline_callback(Pipeline pipeline, Canvas canvas, CanvasElement element, void *self) {
		return EM_ASM_INT({ return tsCanvas.pipeline_callback($0, $1, $2, $3); }, self, new Pipeline(pipeline), new Canvas(canvas), new CanvasElement(element)) != 0;
	}
	static Canvas::PipelineCallback make_canvas_pipeline_callback(void *self) {
		auto ret = makeFunction(canvas_pipeline_callback);
		ret.setArg3(self);
		return ret;
	}
	static bool canvas_begin_callback(Command command, Canvas canvas, void *self) {
		return EM_ASM_INT({ return tsCanvas.begin_callback($0, $1, $2); }, self, new Command(command), new Canvas(canvas)) != 0;
	}
	static Canvas::BeginCallback make_canvas_begin_callback(void *self) {
		auto ret = makeFunction(canvas_begin_callback);
		ret.setArg2(self);
		return ret;
	}
	static bool canvas_draw_callback(Command command, Canvas canvas, void *self) {
		return EM_ASM_INT({ return tsCanvas.draw_callback($0, $1, $2); }, self, new Command(command), new Canvas(canvas)) != 0;
	}
	static Canvas::DrawCallback make_canvas_draw_callback(void *self) {
		auto ret = makeFunction(canvas_draw_callback);
		ret.setArg2(self);
		return ret;
	}
	TS_JSAPI Canvas *tsCanvas_new() {
		return new Canvas();
	}
	TS_JSAPI Canvas *tsCanvas_new_1(Canvas *parent) {
		return new Canvas(parent);
	}
	TS_JSAPI void tsCanvas_delete(Canvas *self) {
		delete self;
	}
	TS_JSAPI bool tsCanvas_equalPtr(const Canvas &self, const Canvas &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Canvas *tsCanvas_clonePtr(const Canvas &self) {
		return new Canvas(self.clonePtr());
	}
	TS_JSAPI void tsCanvas_clearPtr(Canvas &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsCanvas_destroyPtr(Canvas &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsCanvas_acquirePtr(Canvas &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsCanvas_unacquirePtr(Canvas &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsCanvas_isValidPtr(const Canvas &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsCanvas_isOwnerPtr(const Canvas &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsCanvas_isConstPtr(const Canvas &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsCanvas_getCountPtr(const Canvas &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsCanvas_getInternalPtr(const Canvas &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsCanvas_clear(Canvas &self) {
		self.clear();
	}
	TS_JSAPI bool tsCanvas_isCreated(const Canvas &self) {
		return self.isCreated();
	}
	TS_JSAPI uint32_t tsCanvas_getScale(const Canvas &self, const Target &target, uint32_t scale) {
		return self.getScale(target, scale);
	}
	TS_JSAPI bool tsCanvas_create(Canvas &self, const Device &device, uint32_t color, uint32_t depth, uint32_t multisample, uint32_t scale) {
		return self.create(device, (Format)color, (Format)depth, multisample, scale);
	}
	TS_JSAPI bool tsCanvas_create_1(Canvas &self, const Device &device, const Target &target, uint32_t scale) {
		return self.create(device, target, scale);
	}
	TS_JSAPI void tsCanvas_setPipelineHash(Canvas &self, uint32_t hash) {
		self.setPipelineHash(hash);
	}
	TS_JSAPI uint32_t tsCanvas_getPipelineHash(const Canvas &self) {
		return self.getPipelineHash();
	}
	TS_JSAPI uint32_t tsCanvas_getColorFormat(const Canvas &self) {
		return self.getColorFormat();
	}
	TS_JSAPI uint32_t tsCanvas_getDepthFormat(const Canvas &self) {
		return self.getDepthFormat();
	}
	TS_JSAPI uint32_t tsCanvas_getMultisample(const Canvas &self) {
		return self.getMultisample();
	}
	TS_JSAPI void tsCanvas_setOrder(Canvas &self, int32_t order) {
		self.setOrder(order);
	}
	TS_JSAPI int32_t tsCanvas_getOrder(const Canvas &self) {
		return self.getOrder();
	}
	TS_JSAPI void tsCanvas_setEnabled(Canvas &self, bool enabled) {
		self.setEnabled(enabled);
	}
	TS_JSAPI bool tsCanvas_isEnabled(const Canvas &self) {
		return self.isEnabled();
	}
	TS_JSAPI void tsCanvas_setViewport(Canvas &self, const Viewport &viewport) {
		self.setViewport(viewport);
	}
	TS_JSAPI void tsCanvas_setViewport_1(Canvas &self, uint32_t width, uint32_t height) {
		self.setViewport(width, height);
	}
	TS_JSAPI void tsCanvas_setViewport_2(Canvas &self, float32_t width, float32_t height) {
		self.setViewport(width, height);
	}
	TS_JSAPI const Viewport *tsCanvas_getViewport(const Canvas &self) {
		return new Viewport(self.getViewport());
	}
	TS_JSAPI float32_t tsCanvas_getWidth(const Canvas &self) {
		return self.getWidth();
	}
	TS_JSAPI float32_t tsCanvas_getHeight(const Canvas &self) {
		return self.getHeight();
	}
	TS_JSAPI void tsCanvas_clearColor(Canvas &self) {
		self.clearColor();
	}
	TS_JSAPI void tsCanvas_setColor(Canvas &self, const Color &color) {
		self.setColor(color);
	}
	TS_JSAPI void tsCanvas_setColor_1(Canvas &self, float32_t r, float32_t g, float32_t b, float32_t a) {
		self.setColor(r, g, b, a);
	}
	TS_JSAPI const Color *tsCanvas_getColor(const Canvas &self) {
		return new Color(self.getColor());
	}
	TS_JSAPI void tsCanvas_clearScissor(Canvas &self) {
		self.clearScissor();
	}
	TS_JSAPI void tsCanvas_setScissor(Canvas &self, const Rect &scissor) {
		self.setScissor(scissor);
	}
	TS_JSAPI const Rect *tsCanvas_getScissor(const Canvas &self) {
		return new Rect(self.getScissor());
	}
	TS_JSAPI void tsCanvas_clearTransform(Canvas &self) {
		self.clearTransform();
	}
	TS_JSAPI void tsCanvas_setTransform(Canvas &self, const Matrix4x4f &transform) {
		self.setTransform(transform);
	}
	TS_JSAPI const Matrix4x4f *tsCanvas_getTransform(const Canvas &self) {
		return new Matrix4x4f(self.getTransform());
	}
	TS_JSAPI uint32_t tsCanvas_setParent(Canvas &self, Canvas &parent) {
		return self.setParent(parent);
	}
	TS_JSAPI const Canvas *tsCanvas_getParent(const Canvas &self) {
		return new Canvas(self.getParent());
	}
	TS_JSAPI Canvas *tsCanvas_getParent_1(Canvas &self) {
		return new Canvas(self.getParent());
	}
	TS_JSAPI uint32_t tsCanvas_addChild(Canvas &self, Canvas &child) {
		return self.addChild(child);
	}
	TS_JSAPI bool tsCanvas_removeChild(Canvas &self, Canvas &child) {
		return self.removeChild(child);
	}
	TS_JSAPI bool tsCanvas_raiseChild(Canvas &self, Canvas &child, uint32_t index) {
		return self.raiseChild(child, index);
	}
	TS_JSAPI bool tsCanvas_lowerChild(Canvas &self, Canvas &child, uint32_t index) {
		return self.lowerChild(child, index);
	}
	TS_JSAPI void tsCanvas_releaseChildren(Canvas &self) {
		self.releaseChildren();
	}
	TS_JSAPI uint32_t tsCanvas_findChild(const Canvas &self, const Canvas &child) {
		return self.findChild(child);
	}
	TS_JSAPI bool tsCanvas_isChild(const Canvas &self, const Canvas &child) {
		return self.isChild(child);
	}
	TS_JSAPI uint32_t tsCanvas_getNumChildren(const Canvas &self) {
		return self.getNumChildren();
	}
	TS_JSAPI const Canvas *tsCanvas_getChild(const Canvas &self, uint32_t index) {
		return new Canvas(self.getChild(index));
	}
	TS_JSAPI Canvas *tsCanvas_getChild_1(Canvas &self, uint32_t index) {
		return new Canvas(self.getChild(index));
	}
	TS_JSAPI uint32_t tsCanvas_addElement(Canvas &self, CanvasElement &element) {
		return self.addElement(element);
	}
	TS_JSAPI bool tsCanvas_removeElement(Canvas &self, CanvasElement &element) {
		return self.removeElement(element);
	}
	TS_JSAPI bool tsCanvas_raiseElement(Canvas &self, CanvasElement &element, uint32_t index) {
		return self.raiseElement(element, index);
	}
	TS_JSAPI bool tsCanvas_lowerElement(Canvas &self, CanvasElement &element, uint32_t index) {
		return self.lowerElement(element, index);
	}
	TS_JSAPI uint32_t tsCanvas_findElement(const Canvas &self, const CanvasElement &element) {
		return self.findElement(element);
	}
	TS_JSAPI bool tsCanvas_isElement(const Canvas &self, const CanvasElement &element) {
		return self.isElement(element);
	}
	TS_JSAPI uint32_t tsCanvas_getNumElements(const Canvas &self) {
		return self.getNumElements();
	}
	TS_JSAPI const CanvasElement *tsCanvas_getElement(const Canvas &self, uint32_t index) {
		return new CanvasElement(self.getElement(index));
	}
	TS_JSAPI CanvasElement *tsCanvas_getElement_1(Canvas &self, uint32_t index) {
		return new CanvasElement(self.getElement(index));
	}
	TS_JSAPI bool tsCanvas_isFont(const Canvas &self, const char *name) {
		return self.isFont(name);
	}
	TS_JSAPI bool tsCanvas_addFont(Canvas &self, const char *name, Stream &stream) {
		return self.addFont(name, stream);
	}
	TS_JSAPI void tsCanvas_removeFont(Canvas &self, const char *name) {
		self.removeFont(name);
	}
	TS_JSAPI Font *tsCanvas_getFont(Canvas &self, const char *name) {
		return new Font(self.getFont(name));
	}
	TS_JSAPI bool tsCanvas_isTexture(const Canvas &self, const char *name) {
		return self.isTexture(name);
	}
	TS_JSAPI bool tsCanvas_addTexture(Canvas &self, const char *name, Stream &stream) {
		return self.addTexture(name, stream);
	}
	TS_JSAPI bool tsCanvas_addTexture_1(Canvas &self, const char *name, Texture &texture) {
		return self.addTexture(name, texture);
	}
	TS_JSAPI void tsCanvas_removeTexture(Canvas &self, const char *name) {
		self.removeTexture(name);
	}
	TS_JSAPI Texture *tsCanvas_getTexture(Canvas &self, const char *name) {
		return new Texture(self.getTexture(name));
	}
	TS_JSAPI void tsCanvas_setDepthMask(Canvas &self, uint32_t mask) {
		self.setDepthMask((Pipeline::DepthMask)mask);
	}
	TS_JSAPI uint32_t tsCanvas_getDepthMask(const Canvas &self) {
		return self.getDepthMask();
	}
	TS_JSAPI void tsCanvas_setDepthFunc(Canvas &self, uint32_t func) {
		self.setDepthFunc((Pipeline::DepthFunc)func);
	}
	TS_JSAPI uint32_t tsCanvas_getDepthFunc(const Canvas &self) {
		return self.getDepthFunc();
	}
	TS_JSAPI void tsCanvas_draw(Canvas &self, Command &command, const Target &target) {
		self.draw(command, target);
	}
	TS_JSAPI void tsCanvas_draw_1(Canvas &self, Command &command) {
		self.draw(command);
	}
	TS_JSAPI void tsCanvas_setCreateCallback(Canvas &self, bool func) {
		self.setCreateCallback((func) ? make_canvas_create_callback(&self) : Canvas::CreateCallback());
	}
	TS_JSAPI void tsCanvas_setPipelineCallback(Canvas &self, bool func) {
		self.setPipelineCallback((func) ? make_canvas_pipeline_callback(&self) : Canvas::PipelineCallback());
	}
	TS_JSAPI void tsCanvas_setBeginCallback(Canvas &self, bool func) {
		self.setBeginCallback((func) ? make_canvas_begin_callback(&self) : Canvas::BeginCallback());
	}
	TS_JSAPI void tsCanvas_setDrawCallback(Canvas &self, bool func) {
		self.setDrawCallback((func) ? make_canvas_draw_callback(&self) : Canvas::DrawCallback());
	}
	TS_JSAPI uint32_t tsCanvas_getNumDrawPipelines(const Canvas &self) {
		return self.getNumDrawPipelines();
	}
	TS_JSAPI uint32_t tsCanvas_getNumDrawElements(const Canvas &self) {
		return self.getNumDrawElements();
	}
	TS_JSAPI uint32_t tsCanvas_getNumDrawCommands(const Canvas &self) {
		return self.getNumDrawCommands();
	}
	TS_JSAPI Rect *tsCanvas_getRect(const Canvas &self) {
		return new Rect(self.getRect());
	}
	
	// Tellusim::Control
	TS_JSAPI Control *tsControl_new() {
		return new Control();
	}
	TS_JSAPI Control *tsControl_new_1(Control *parent) {
		return new Control(parent);
	}
	TS_JSAPI Control *tsControl_new_2(Control *parent, float32_t width, float32_t height) {
		return new Control(parent, width, height);
	}
	TS_JSAPI void tsControl_delete(Control *self) {
		delete self;
	}
	TS_JSAPI bool tsControl_equalPtr(const Control &self, const Control &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Control *tsControl_clonePtr(const Control &self) {
		return new Control(self.clonePtr());
	}
	TS_JSAPI void tsControl_clearPtr(Control &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsControl_destroyPtr(Control &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsControl_acquirePtr(Control &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsControl_unacquirePtr(Control &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsControl_isValidPtr(const Control &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsControl_isOwnerPtr(const Control &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsControl_isConstPtr(const Control &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsControl_getCountPtr(const Control &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsControl_getInternalPtr(const Control &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI uint32_t tsControl_getNumControls() {
		return Control::getNumControls();
	}
	TS_JSAPI bool tsControl_isControl(const Control &control) {
		return Control::isControl(control);
	}
	TS_JSAPI uint32_t tsControl_getType(const Control &self) {
		return self.getType();
	}
	TS_JSAPI const char* tsControl_getTypeName(uint32_t type) {
		return Control::getTypeName((Control::Type)type);
	}
	TS_JSAPI const char* tsControl_getTypeName_1(const Control &self) {
		return self.getTypeName();
	}
	TS_JSAPI bool tsControl_isUnknown(const Control &self) {
		return self.isUnknown();
	}
	TS_JSAPI bool tsControl_isRoot(const Control &self) {
		return self.isRoot();
	}
	TS_JSAPI bool tsControl_isText(const Control &self) {
		return self.isText();
	}
	TS_JSAPI bool tsControl_isRect(const Control &self) {
		return self.isRect();
	}
	TS_JSAPI bool tsControl_isGrid(const Control &self) {
		return self.isGrid();
	}
	TS_JSAPI bool tsControl_isGroup(const Control &self) {
		return self.isGroup();
	}
	TS_JSAPI bool tsControl_isPanel(const Control &self) {
		return self.isPanel();
	}
	TS_JSAPI bool tsControl_isDialog(const Control &self) {
		return self.isDialog();
	}
	TS_JSAPI bool tsControl_isWindow(const Control &self) {
		return self.isWindow();
	}
	TS_JSAPI bool tsControl_isCheck(const Control &self) {
		return self.isCheck();
	}
	TS_JSAPI bool tsControl_isCombo(const Control &self) {
		return self.isCombo();
	}
	TS_JSAPI bool tsControl_isButton(const Control &self) {
		return self.isButton();
	}
	TS_JSAPI bool tsControl_isSlider(const Control &self) {
		return self.isSlider();
	}
	TS_JSAPI bool tsControl_isScroll(const Control &self) {
		return self.isScroll();
	}
	TS_JSAPI bool tsControl_isSplit(const Control &self) {
		return self.isSplit();
	}
	TS_JSAPI bool tsControl_isArea(const Control &self) {
		return self.isArea();
	}
	TS_JSAPI bool tsControl_isTree(const Control &self) {
		return self.isTree();
	}
	TS_JSAPI bool tsControl_isEdit(const Control &self) {
		return self.isEdit();
	}
	TS_JSAPI void tsControl_setAlign(Control &self, uint32_t align) {
		self.setAlign((Control::Align)align);
	}
	TS_JSAPI uint32_t tsControl_getAlign(const Control &self) {
		return self.getAlign();
	}
	TS_JSAPI bool tsControl_hasAlign(const Control &self, uint32_t align) {
		return self.hasAlign((Control::Align)align);
	}
	TS_JSAPI bool tsControl_hasAligns(const Control &self, uint32_t aligns) {
		return self.hasAligns((Control::Align)aligns);
	}
	TS_JSAPI bool tsControl_isSpacer(const Control &self) {
		return self.isSpacer();
	}
	TS_JSAPI void tsControl_setCreated(Control &self, bool created) {
		self.setCreated(created);
	}
	TS_JSAPI bool tsControl_isCreated(const Control &self) {
		return self.isCreated();
	}
	TS_JSAPI void tsControl_setEnabled(Control &self, bool enabled) {
		self.setEnabled(enabled);
	}
	TS_JSAPI bool tsControl_isEnabled(const Control &self) {
		return self.isEnabled();
	}
	TS_JSAPI bool tsControl_wasEnabled(const Control &self) {
		return self.wasEnabled();
	}
	TS_JSAPI bool tsControl_wasUpdated(const Control &self) {
		return self.wasUpdated();
	}
	TS_JSAPI void tsControl_setDisabled(Control &self, bool disabled) {
		self.setDisabled(disabled);
	}
	TS_JSAPI bool tsControl_isDisabled(const Control &self) {
		return self.isDisabled();
	}
	TS_JSAPI Canvas *tsControl_getCanvas(const Control &self) {
		return new Canvas(self.getCanvas());
	}
	TS_JSAPI const ControlRoot *tsControl_getRoot(const Control &self, bool local) {
		return new ControlRoot(self.getRoot(local));
	}
	TS_JSAPI ControlRoot *tsControl_getRoot_1(Control &self, bool local) {
		return new ControlRoot(self.getRoot(local));
	}
	TS_JSAPI const ControlPanel *tsControl_getPanel(const Control &self) {
		return new ControlPanel(self.getPanel());
	}
	TS_JSAPI ControlPanel *tsControl_getPanel_1(Control &self) {
		return new ControlPanel(self.getPanel());
	}
	TS_JSAPI uint32_t tsControl_setParent(Control &self, Control &parent) {
		return self.setParent(parent);
	}
	TS_JSAPI const Control *tsControl_getParent(const Control &self) {
		return new Control(self.getParent());
	}
	TS_JSAPI Control *tsControl_getParent_1(Control &self) {
		return new Control(self.getParent());
	}
	TS_JSAPI bool tsControl_isParentEnabled(const Control &self) {
		return self.isParentEnabled();
	}
	TS_JSAPI bool tsControl_isParentDisabled(const Control &self) {
		return self.isParentDisabled();
	}
	TS_JSAPI uint32_t tsControl_addChild(Control &self, Control &child) {
		return self.addChild(child);
	}
	TS_JSAPI Control *tsControl_setChild(Control &self, uint32_t index, Control &child) {
		return new Control(self.setChild(index, child));
	}
	TS_JSAPI bool tsControl_raiseChild(Control &self, Control &child, uint32_t index) {
		return self.raiseChild(child, index);
	}
	TS_JSAPI bool tsControl_lowerChild(Control &self, Control &child, uint32_t index) {
		return self.lowerChild(child, index);
	}
	TS_JSAPI bool tsControl_removeChild(Control &self, Control &child) {
		return self.removeChild(child);
	}
	TS_JSAPI void tsControl_releaseChildren(Control &self) {
		self.releaseChildren();
	}
	TS_JSAPI uint32_t tsControl_findChild(const Control &self, const Control &child) {
		return self.findChild(child);
	}
	TS_JSAPI bool tsControl_isChild(const Control &self, const Control &child, bool hierarchy) {
		return self.isChild(child, hierarchy);
	}
	TS_JSAPI uint32_t tsControl_getNumChildren(const Control &self) {
		return self.getNumChildren();
	}
	TS_JSAPI const Control *tsControl_getChild(const Control &self, uint32_t index) {
		return new Control(self.getChild(index));
	}
	TS_JSAPI Control *tsControl_getChild_1(Control &self, uint32_t index) {
		return new Control(self.getChild(index));
	}
	TS_JSAPI void tsControl_setSize(Control &self, const Vector2f &size) {
		self.setSize(size);
	}
	TS_JSAPI void tsControl_setSize_1(Control &self, float32_t width, float32_t height) {
		self.setSize(width, height);
	}
	TS_JSAPI const Vector2f *tsControl_getSize(const Control &self) {
		return new Vector2f(self.getSize());
	}
	TS_JSAPI float32_t tsControl_getWidth(const Control &self) {
		return self.getWidth();
	}
	TS_JSAPI float32_t tsControl_getHeight(const Control &self) {
		return self.getHeight();
	}
	TS_JSAPI void tsControl_setPosition(Control &self, const Vector3f &position) {
		self.setPosition(position);
	}
	TS_JSAPI void tsControl_setPosition_1(Control &self, float32_t x, float32_t y, float32_t z) {
		self.setPosition(x, y, z);
	}
	TS_JSAPI const Vector3f *tsControl_getPosition(const Control &self) {
		return new Vector3f(self.getPosition());
	}
	TS_JSAPI float32_t tsControl_getPositionX(const Control &self) {
		return self.getPositionX();
	}
	TS_JSAPI float32_t tsControl_getPositionY(const Control &self) {
		return self.getPositionY();
	}
	TS_JSAPI void tsControl_setOffset(Control &self, const Vector3f &offset) {
		self.setOffset(offset);
	}
	TS_JSAPI void tsControl_setOffset_1(Control &self, float32_t x, float32_t y, float32_t z) {
		self.setOffset(x, y, z);
	}
	TS_JSAPI const Vector3f *tsControl_getOffset(const Control &self) {
		return new Vector3f(self.getOffset());
	}
	TS_JSAPI float32_t tsControl_getOffsetX(const Control &self) {
		return self.getOffsetX();
	}
	TS_JSAPI float32_t tsControl_getOffsetY(const Control &self) {
		return self.getOffsetY();
	}
	TS_JSAPI void tsControl_setMargin(Control &self, float32_t value) {
		self.setMargin(value);
	}
	TS_JSAPI void tsControl_setMargin_1(Control &self, float32_t horizontal, float32_t vertical) {
		self.setMargin(horizontal, vertical);
	}
	TS_JSAPI void tsControl_setMargin_2(Control &self, float32_t left, float32_t right, float32_t bottom, float32_t top) {
		self.setMargin(left, right, bottom, top);
	}
	TS_JSAPI void tsControl_setMargin_3(Control &self, const Rect &margin) {
		self.setMargin(margin);
	}
	TS_JSAPI const Rect *tsControl_getMargin(const Control &self) {
		return new Rect(self.getMargin());
	}
	TS_JSAPI const Rect *tsControl_getRect(const Control &self) {
		return new Rect(self.getRect());
	}
	TS_JSAPI uint32_t tsControl_getState(const Control &self) {
		return self.getState();
	}
	
	// Tellusim::ControlRoot
	static void control_root_copy_callback(ControlRoot a0, const char *text, void *self) {
		EM_ASM({ tsControlRoot.copy_callback($0, $1, $2); }, self, new ControlRoot(a0), text);
	}
	static ControlRoot::CopyCallback make_control_root_copy_callback(void *self) {
		auto ret = makeFunction(control_root_copy_callback);
		ret.setArg2(self);
		return ret;
	}
	static String control_root_paste_callback(ControlRoot a0, void *self) {
		return String((const char*)EM_ASM_INT({ return tsControlRoot.paste_callback($0, $1); }, self, new ControlRoot(a0)));
	}
	static ControlRoot::PasteCallback make_control_root_paste_callback(void *self) {
		auto ret = makeFunction(control_root_paste_callback);
		ret.setArg1(self);
		return ret;
	}
	TS_JSAPI ControlRoot *tsControlRoot_new() {
		return new ControlRoot();
	}
	TS_JSAPI ControlRoot *tsControlRoot_new_1(Canvas &canvas, bool blob) {
		return new ControlRoot(canvas, blob);
	}
	TS_JSAPI void tsControlRoot_delete(ControlRoot *self) {
		delete self;
	}
	TS_JSAPI bool tsControlRoot_equalControlPtr(const ControlRoot &self, const Control &base) {
		return self.operator==(base);
	}
	TS_JSAPI ControlRoot *tsControlRoot_castControlPtr(const Control &self) {
		return new ControlRoot(self);
	}
	TS_JSAPI Control *tsControlRoot_baseControlPtr(const ControlRoot &self) {
		return new Control(self.getControl());
	}
	TS_JSAPI void tsControlRoot_setViewport(ControlRoot &self, const Viewport &viewport) {
		self.setViewport(viewport);
	}
	TS_JSAPI void tsControlRoot_setViewport_1(ControlRoot &self, uint32_t width, uint32_t height) {
		self.setViewport(width, height);
	}
	TS_JSAPI void tsControlRoot_setViewport_2(ControlRoot &self, float32_t width, float32_t height) {
		self.setViewport(width, height);
	}
	TS_JSAPI const Viewport *tsControlRoot_getViewport(const ControlRoot &self) {
		return new Viewport(self.getViewport());
	}
	TS_JSAPI String *tsControlRoot_getFontName(const ControlRoot &self) {
		return new String(self.getFontName());
	}
	TS_JSAPI void tsControlRoot_setFontName(ControlRoot &self, const char *name) {
		self.setFontName(name);
	}
	TS_JSAPI void tsControlRoot_setFontName_1(ControlRoot &self, const String &name) {
		self.setFontName(name);
	}
	TS_JSAPI bool tsControlRoot_setFontSize(ControlRoot &self, uint32_t size, bool update) {
		return self.setFontSize(size, update);
	}
	TS_JSAPI uint32_t tsControlRoot_getFontSize(const ControlRoot &self) {
		return self.getFontSize();
	}
	TS_JSAPI bool tsControlRoot_setFontScale(ControlRoot &self, uint32_t scale, bool update) {
		return self.setFontScale(scale, update);
	}
	TS_JSAPI uint32_t tsControlRoot_getFontScale(const ControlRoot &self) {
		return self.getFontScale();
	}
	TS_JSAPI bool tsControlRoot_setFontStyle(ControlRoot &self, const FontStyle &style, bool update) {
		return self.setFontStyle(style, update);
	}
	TS_JSAPI const FontStyle *tsControlRoot_getFontStyle(const ControlRoot &self) {
		return new FontStyle(self.getFontStyle());
	}
	TS_JSAPI FontStyle *tsControlRoot_getFontStyle_1(ControlRoot &self) {
		return new FontStyle(self.getFontStyle());
	}
	TS_JSAPI String *tsControlRoot_getTextureName(const ControlRoot &self) {
		return new String(self.getTextureName());
	}
	TS_JSAPI bool tsControlRoot_setTextureName(ControlRoot &self, const char *name, uint32_t width, uint32_t height, float32_t border) {
		return self.setTextureName(name, width, height, border);
	}
	TS_JSAPI bool tsControlRoot_setTextureName_1(ControlRoot &self, const String &name, uint32_t width, uint32_t height, float32_t border) {
		return self.setTextureName(name, width, height, border);
	}
	TS_JSAPI float32_t tsControlRoot_getTextureWidth(const ControlRoot &self) {
		return self.getTextureWidth();
	}
	TS_JSAPI float32_t tsControlRoot_getTextureHeight(const ControlRoot &self) {
		return self.getTextureHeight();
	}
	TS_JSAPI void tsControlRoot_setTextColor(ControlRoot &self, uint32_t type, uint32_t state, const Color &color) {
		self.setTextColor((Control::Type)type, (Control::State)state, color);
	}
	TS_JSAPI void tsControlRoot_setTextOffset(ControlRoot &self, uint32_t type, uint32_t state, const Vector3f &offset) {
		self.setTextOffset((Control::Type)type, (Control::State)state, offset);
	}
	TS_JSAPI const Color *tsControlRoot_getTextColor(const ControlRoot &self, uint32_t type, uint32_t state) {
		return new Color(self.getTextColor((Control::Type)type, (Control::State)state));
	}
	TS_JSAPI const Vector3f *tsControlRoot_getTextOffset(const ControlRoot &self, uint32_t type, uint32_t state) {
		return new Vector3f(self.getTextOffset((Control::Type)type, (Control::State)state));
	}
	TS_JSAPI void tsControlRoot_setMeshColor(ControlRoot &self, uint32_t mesh, uint32_t state, const Color &color) {
		self.setMeshColor((Control::Mesh)mesh, (Control::State)state, color);
	}
	TS_JSAPI void tsControlRoot_setMeshRegion(ControlRoot &self, uint32_t mesh, const Rect &grid, const Rect &region, const Vector2f &border) {
		self.setMeshRegion((Control::Mesh)mesh, grid, region, border);
	}
	TS_JSAPI void tsControlRoot_setMeshRegions(ControlRoot &self, uint32_t mesh, const Rect &grid, const Rect &regions, const Vector2f &border) {
		self.setMeshRegions((Control::Mesh)mesh, grid, regions, border);
	}
	TS_JSAPI uint32_t tsControlRoot_getMeshColor(const ControlRoot &self, uint32_t mesh, uint32_t state) {
		return self.getMeshColor((Control::Mesh)mesh, (Control::State)state);
	}
	TS_JSAPI const Rect *tsControlRoot_getMeshGrid(const ControlRoot &self, uint32_t mesh) {
		return new Rect(self.getMeshGrid((Control::Mesh)mesh));
	}
	TS_JSAPI const Rect *tsControlRoot_getMeshMargin(const ControlRoot &self, uint32_t mesh) {
		return new Rect(self.getMeshMargin((Control::Mesh)mesh));
	}
	TS_JSAPI const Rect *tsControlRoot_getMeshRegion(const ControlRoot &self, uint32_t mesh, uint32_t state) {
		return new Rect(self.getMeshRegion((Control::Mesh)mesh, (Control::State)state));
	}
	TS_JSAPI void tsControlRoot_setGroupRadius(ControlRoot &self, float32_t radius) {
		self.setGroupRadius(radius);
	}
	TS_JSAPI void tsControlRoot_setGroupColor(ControlRoot &self, const Color &color) {
		self.setGroupColor(color);
	}
	TS_JSAPI float32_t tsControlRoot_getGroupRadius(const ControlRoot &self) {
		return self.getGroupRadius();
	}
	TS_JSAPI const Color *tsControlRoot_getGroupColor(const ControlRoot &self) {
		return new Color(self.getGroupColor());
	}
	TS_JSAPI void tsControlRoot_setPanelRadius(ControlRoot &self, float32_t radius) {
		self.setPanelRadius(radius);
	}
	TS_JSAPI void tsControlRoot_setPanelColor(ControlRoot &self, const Color &color) {
		self.setPanelColor(color);
	}
	TS_JSAPI float32_t tsControlRoot_getPanelRadius(const ControlRoot &self) {
		return self.getPanelRadius();
	}
	TS_JSAPI const Color *tsControlRoot_getPanelColor(const ControlRoot &self) {
		return new Color(self.getPanelColor());
	}
	TS_JSAPI void tsControlRoot_setCheckedColor(ControlRoot &self, const Color &color) {
		self.setCheckedColor(color);
	}
	TS_JSAPI const Color *tsControlRoot_getCheckedColor(const ControlRoot &self) {
		return new Color(self.getCheckedColor());
	}
	TS_JSAPI void tsControlRoot_setSplitSize(ControlRoot &self, float32_t size) {
		self.setSplitSize(size);
	}
	TS_JSAPI float32_t tsControlRoot_getSplitSize(const ControlRoot &self) {
		return self.getSplitSize();
	}
	TS_JSAPI void tsControlRoot_setMousePosition(ControlRoot &self, const Vector2f &position) {
		self.setMousePosition(position);
	}
	TS_JSAPI void tsControlRoot_setMouse(ControlRoot &self, int32_t x, int32_t y, uint32_t buttons) {
		self.setMouse(x, y, (Control::Button)buttons);
	}
	TS_JSAPI void tsControlRoot_setMouse_1(ControlRoot &self, float32_t x, float32_t y, uint32_t buttons) {
		self.setMouse(x, y, (Control::Button)buttons);
	}
	TS_JSAPI const Vector2f *tsControlRoot_getMouse(const ControlRoot &self) {
		return new Vector2f(self.getMouse());
	}
	TS_JSAPI uint32_t tsControlRoot_getMouseButtons(const ControlRoot &self) {
		return self.getMouseButtons();
	}
	TS_JSAPI float32_t tsControlRoot_getMouseX(const ControlRoot &self) {
		return self.getMouseX();
	}
	TS_JSAPI float32_t tsControlRoot_getMouseY(const ControlRoot &self) {
		return self.getMouseY();
	}
	TS_JSAPI void tsControlRoot_setMouseOffset(ControlRoot &self, const Vector2f &offset) {
		self.setMouseOffset(offset);
	}
	TS_JSAPI const Vector2f *tsControlRoot_getMouseOffset(const ControlRoot &self) {
		return new Vector2f(self.getMouseOffset());
	}
	TS_JSAPI void tsControlRoot_setMouseAxis(ControlRoot &self, uint32_t axis, float32_t delta) {
		self.setMouseAxis((Control::Axis)axis, delta);
	}
	TS_JSAPI void tsControlRoot_setMouseAlign(ControlRoot &self, uint32_t align, bool clear) {
		self.setMouseAlign((Control::Align)align, clear);
	}
	TS_JSAPI uint32_t tsControlRoot_getMouseAlign(const ControlRoot &self) {
		return self.getMouseAlign();
	}
	TS_JSAPI bool tsControlRoot_hasMouseAlign(const ControlRoot &self, uint32_t align) {
		return self.hasMouseAlign((Control::Align)align);
	}
	TS_JSAPI bool tsControlRoot_hasMouseAligns(const ControlRoot &self, uint32_t aligns) {
		return self.hasMouseAligns((Control::Align)aligns);
	}
	TS_JSAPI bool tsControlRoot_setKeyboardKey(ControlRoot &self, uint32_t key, uint32_t code, bool value) {
		return self.setKeyboardKey(key, code, value);
	}
	TS_JSAPI bool tsControlRoot_getKeyboardKey(ControlRoot &self, uint32_t key, bool clear) {
		return self.getKeyboardKey(key, clear);
	}
	TS_JSAPI void tsControlRoot_clearCurrentControl(ControlRoot &self) {
		self.clearCurrentControl();
	}
	TS_JSAPI void tsControlRoot_setCurrentControl(ControlRoot &self, Control control, bool grab) {
		self.setCurrentControl(control, grab);
	}
	TS_JSAPI Control *tsControlRoot_getCurrentControl(const ControlRoot &self) {
		return new Control(self.getCurrentControl());
	}
	TS_JSAPI bool tsControlRoot_isCurrentControl(const ControlRoot &self) {
		return self.isCurrentControl();
	}
	TS_JSAPI bool tsControlRoot_getControlGrab(const ControlRoot &self) {
		return self.getControlGrab();
	}
	TS_JSAPI void tsControlRoot_clearFocusedControl(ControlRoot &self) {
		self.clearFocusedControl();
	}
	TS_JSAPI void tsControlRoot_setFocusedControl(ControlRoot &self, Control control) {
		self.setFocusedControl(control);
	}
	TS_JSAPI Control *tsControlRoot_getFocusedControl(const ControlRoot &self) {
		return new Control(self.getFocusedControl());
	}
	TS_JSAPI bool tsControlRoot_isFocusedControl(const ControlRoot &self) {
		return self.isFocusedControl();
	}
	TS_JSAPI void tsControlRoot_clearMouseControl(ControlRoot &self) {
		self.clearMouseControl();
	}
	TS_JSAPI void tsControlRoot_setMouseControl(ControlRoot &self, Control control) {
		self.setMouseControl(control);
	}
	TS_JSAPI Control *tsControlRoot_getMouseControl(const ControlRoot &self) {
		return new Control(self.getMouseControl());
	}
	TS_JSAPI bool tsControlRoot_isMouseControl(const ControlRoot &self) {
		return self.isMouseControl();
	}
	TS_JSAPI void tsControlRoot_clearInputControl(ControlRoot &self) {
		self.clearInputControl();
	}
	TS_JSAPI void tsControlRoot_setInputControl(ControlRoot &self, Control control) {
		self.setInputControl(control);
	}
	TS_JSAPI Control *tsControlRoot_getInputControl(const ControlRoot &self) {
		return new Control(self.getInputControl());
	}
	TS_JSAPI bool tsControlRoot_isInputControl(const ControlRoot &self) {
		return self.isInputControl();
	}
	TS_JSAPI void tsControlRoot_clearModalControl(ControlRoot &self) {
		self.clearModalControl();
	}
	TS_JSAPI void tsControlRoot_setModalControl(ControlRoot &self, Control control, bool disabled) {
		self.setModalControl(control, disabled);
	}
	TS_JSAPI Control *tsControlRoot_getModalControl(const ControlRoot &self) {
		return new Control(self.getModalControl());
	}
	TS_JSAPI bool tsControlRoot_isModalDisabled(const ControlRoot &self) {
		return self.isModalDisabled();
	}
	TS_JSAPI bool tsControlRoot_isModalControl(const ControlRoot &self) {
		return self.isModalControl();
	}
	TS_JSAPI void tsControlRoot_setOverlayOrder(ControlRoot &self, int32_t order) {
		self.setOverlayOrder(order);
	}
	TS_JSAPI int32_t tsControlRoot_getOverlayOrder(const ControlRoot &self) {
		return self.getOverlayOrder();
	}
	TS_JSAPI bool tsControlRoot_update(ControlRoot &self, uint32_t scale, int32_t order) {
		return self.update(scale, order);
	}
	TS_JSAPI void tsControlRoot_setCopyText(ControlRoot &self, const char *text) {
		self.setCopyText(text);
	}
	TS_JSAPI void tsControlRoot_setCopyText_1(ControlRoot &self, const String &text) {
		self.setCopyText(text);
	}
	TS_JSAPI String *tsControlRoot_getPasteText(ControlRoot &self) {
		return new String(self.getPasteText());
	}
	TS_JSAPI void tsControlRoot_setCopyCallback(ControlRoot &self, bool func) {
		self.setCopyCallback((func) ? make_control_root_copy_callback(&self) : ControlRoot::CopyCallback());
	}
	TS_JSAPI void tsControlRoot_setPasteCallback(ControlRoot &self, bool func) {
		self.setPasteCallback((func) ? make_control_root_paste_callback(&self) : ControlRoot::PasteCallback());
	}
	
	// Tellusim::ControlText
	TS_JSAPI ControlText *tsControlText_new() {
		return new ControlText();
	}
	TS_JSAPI ControlText *tsControlText_new_1(Control *parent) {
		return new ControlText(parent);
	}
	TS_JSAPI ControlText *tsControlText_new_2(Control *parent, const char *text) {
		return new ControlText(parent, text);
	}
	TS_JSAPI ControlText *tsControlText_new_3(Control *parent, const String &text) {
		return new ControlText(parent, text);
	}
	TS_JSAPI void tsControlText_delete(ControlText *self) {
		delete self;
	}
	TS_JSAPI bool tsControlText_equalControlPtr(const ControlText &self, const Control &base) {
		return self.operator==(base);
	}
	TS_JSAPI ControlText *tsControlText_castControlPtr(const Control &self) {
		return new ControlText(self);
	}
	TS_JSAPI Control *tsControlText_baseControlPtr(const ControlText &self) {
		return new Control(self.getControl());
	}
	TS_JSAPI void tsControlText_setCallback(ControlText &self, bool callback) {
		self.setCallback(callback);
	}
	TS_JSAPI bool tsControlText_getCallback(const ControlText &self) {
		return self.getCallback();
	}
	TS_JSAPI void tsControlText_setMode(ControlText &self, uint32_t mode) {
		self.setMode((CanvasElement::Mode)mode);
	}
	TS_JSAPI uint32_t tsControlText_getMode(const ControlText &self) {
		return self.getMode();
	}
	TS_JSAPI void tsControlText_setPipeline(ControlText &self, Pipeline &pipeline) {
		self.setPipeline(pipeline);
	}
	TS_JSAPI void tsControlText_setPipeline_1(ControlText &self, Pipeline &pipeline, bool func) {
		self.setPipeline(pipeline, (func) ? make_canvas_element_draw_callback(&self) : CanvasElement::DrawCallback());
	}
	TS_JSAPI Pipeline *tsControlText_getPipeline(const ControlText &self) {
		return new Pipeline(self.getPipeline());
	}
	TS_JSAPI void tsControlText_setColor(ControlText &self, const Color &color) {
		self.setColor(color);
	}
	TS_JSAPI void tsControlText_setColor_1(ControlText &self, float32_t r, float32_t g, float32_t b, float32_t a) {
		self.setColor(r, g, b, a);
	}
	TS_JSAPI const Color *tsControlText_getColor(const ControlText &self) {
		return new Color(self.getColor());
	}
	TS_JSAPI void tsControlText_setFilter(ControlText &self, uint32_t filter) {
		self.setFilter((Sampler::Filter)filter);
	}
	TS_JSAPI uint32_t tsControlText_getFilter(const ControlText &self) {
		return self.getFilter();
	}
	TS_JSAPI void tsControlText_setAnisotropy(ControlText &self, uint32_t anisotropy) {
		self.setAnisotropy(anisotropy);
	}
	TS_JSAPI uint32_t tsControlText_getAnisotropy(const ControlText &self) {
		return self.getAnisotropy();
	}
	TS_JSAPI void tsControlText_setBlend(ControlText &self, uint32_t op, uint32_t src, uint32_t dest) {
		self.setBlend((Pipeline::BlendOp)op, (Pipeline::BlendFunc)src, (Pipeline::BlendFunc)dest);
	}
	TS_JSAPI uint32_t tsControlText_getBlendOp(const ControlText &self) {
		return self.getBlendOp();
	}
	TS_JSAPI uint32_t tsControlText_getBlendSrcFunc(const ControlText &self) {
		return self.getBlendSrcFunc();
	}
	TS_JSAPI uint32_t tsControlText_getBlendDestFunc(const ControlText &self) {
		return self.getBlendDestFunc();
	}
	TS_JSAPI void tsControlText_setFontName(ControlText &self, const char *name) {
		self.setFontName(name);
	}
	TS_JSAPI void tsControlText_setFontName_1(ControlText &self, const String &name) {
		self.setFontName(name);
	}
	TS_JSAPI String *tsControlText_getFontName(const ControlText &self) {
		return new String(self.getFontName());
	}
	TS_JSAPI void tsControlText_setFontColor(ControlText &self, const Color &color) {
		self.setFontColor(color);
	}
	TS_JSAPI const Color *tsControlText_getFontColor(const ControlText &self) {
		return new Color(self.getFontColor());
	}
	TS_JSAPI bool tsControlText_setFontSize(ControlText &self, uint32_t size) {
		return self.setFontSize(size);
	}
	TS_JSAPI uint32_t tsControlText_getFontSize(const ControlText &self) {
		return self.getFontSize();
	}
	TS_JSAPI bool tsControlText_setFontStyle(ControlText &self, const FontStyle &style) {
		return self.setFontStyle(style);
	}
	TS_JSAPI const FontStyle *tsControlText_getFontStyleConst(const ControlText &self) {
		return new FontStyle(self.getFontStyleConst());
	}
	TS_JSAPI const FontStyle *tsControlText_getFontStyle(const ControlText &self) {
		return new FontStyle(self.getFontStyle());
	}
	TS_JSAPI FontStyle *tsControlText_getFontStyle_1(ControlText &self) {
		return new FontStyle(self.getFontStyle());
	}
	TS_JSAPI void tsControlText_setFontAlign(ControlText &self, uint32_t align) {
		self.setFontAlign((Control::Align)align);
	}
	TS_JSAPI uint32_t tsControlText_getFontAlign(const ControlText &self) {
		return self.getFontAlign();
	}
	TS_JSAPI bool tsControlText_hasFontAlign(const ControlText &self, uint32_t align) {
		return self.hasFontAlign((Control::Align)align);
	}
	TS_JSAPI bool tsControlText_hasFontAligns(const ControlText &self, uint32_t aligns) {
		return self.hasFontAligns((Control::Align)aligns);
	}
	TS_JSAPI void tsControlText_setText(ControlText &self, const char *text) {
		self.setText(text);
	}
	TS_JSAPI void tsControlText_setText_1(ControlText &self, const String &text) {
		self.setText(text);
	}
	TS_JSAPI String *tsControlText_getText(const ControlText &self) {
		return new String(self.getText());
	}
	TS_JSAPI CanvasText *tsControlText_getCanvasText(ControlText &self) {
		return new CanvasText(self.getCanvasText());
	}
	
	// Tellusim::ControlRect
	static bool control_rect_inside_callback(ControlRect a0, float32_t x, float32_t y, void *self) {
		return EM_ASM_INT({ return tsControlRect.inside_callback($0, $1, $2, $3); }, self, new ControlRect(a0), x, y) != 0;
	}
	static ControlRect::InsideCallback make_control_rect_inside_callback(void *self) {
		auto ret = makeFunction(control_rect_inside_callback);
		ret.setArg3(self);
		return ret;
	}
	static void control_rect_pressed_callback(ControlRect a0, float32_t x, float32_t y, void *self) {
		EM_ASM({ tsControlRect.pressed_callback($0, $1, $2, $3); }, self, new ControlRect(a0), x, y);
	}
	static ControlRect::PressedCallback make_control_rect_pressed_callback(void *self) {
		auto ret = makeFunction(control_rect_pressed_callback);
		ret.setArg3(self);
		return ret;
	}
	static void control_rect_released_callback(ControlRect a0, float32_t x, float32_t y, void *self) {
		EM_ASM({ tsControlRect.released_callback($0, $1, $2, $3); }, self, new ControlRect(a0), x, y);
	}
	static ControlRect::ReleasedCallback make_control_rect_released_callback(void *self) {
		auto ret = makeFunction(control_rect_released_callback);
		ret.setArg3(self);
		return ret;
	}
	static void control_rect_clicked_callback(ControlRect a0, void *self) {
		EM_ASM({ tsControlRect.clicked_callback($0, $1); }, self, new ControlRect(a0));
	}
	static ControlRect::ClickedCallback make_control_rect_clicked_callback(void *self) {
		auto ret = makeFunction(control_rect_clicked_callback);
		ret.setArg1(self);
		return ret;
	}
	TS_JSAPI ControlRect *tsControlRect_new() {
		return new ControlRect();
	}
	TS_JSAPI ControlRect *tsControlRect_new_1(Control *parent) {
		return new ControlRect(parent);
	}
	TS_JSAPI ControlRect *tsControlRect_new_2(Control *parent, Texture &texture) {
		return new ControlRect(parent, texture);
	}
	TS_JSAPI ControlRect *tsControlRect_new_3(Control *parent, const char *name) {
		return new ControlRect(parent, name);
	}
	TS_JSAPI ControlRect *tsControlRect_new_4(Control *parent, uint32_t mode) {
		return new ControlRect(parent, (CanvasElement::Mode)mode);
	}
	TS_JSAPI void tsControlRect_delete(ControlRect *self) {
		delete self;
	}
	TS_JSAPI bool tsControlRect_equalControlPtr(const ControlRect &self, const Control &base) {
		return self.operator==(base);
	}
	TS_JSAPI ControlRect *tsControlRect_castControlPtr(const Control &self) {
		return new ControlRect(self);
	}
	TS_JSAPI Control *tsControlRect_baseControlPtr(const ControlRect &self) {
		return new Control(self.getControl());
	}
	TS_JSAPI void tsControlRect_setCallback(ControlRect &self, bool callback) {
		self.setCallback(callback);
	}
	TS_JSAPI bool tsControlRect_getCallback(const ControlRect &self) {
		return self.getCallback();
	}
	TS_JSAPI void tsControlRect_setFullscreen(ControlRect &self, bool fullscreen) {
		self.setFullscreen(fullscreen);
	}
	TS_JSAPI bool tsControlRect_isFullscreen(const ControlRect &self) {
		return self.isFullscreen();
	}
	TS_JSAPI void tsControlRect_setMode(ControlRect &self, uint32_t mode) {
		self.setMode((CanvasElement::Mode)mode);
	}
	TS_JSAPI uint32_t tsControlRect_getMode(const ControlRect &self) {
		return self.getMode();
	}
	TS_JSAPI void tsControlRect_setPipeline(ControlRect &self, Pipeline &pipeline) {
		self.setPipeline(pipeline);
	}
	TS_JSAPI void tsControlRect_setPipeline_1(ControlRect &self, Pipeline &pipeline, bool func) {
		self.setPipeline(pipeline, (func) ? make_canvas_element_draw_callback(&self) : CanvasElement::DrawCallback());
	}
	TS_JSAPI Pipeline *tsControlRect_getPipeline(const ControlRect &self) {
		return new Pipeline(self.getPipeline());
	}
	TS_JSAPI void tsControlRect_setRadius(ControlRect &self, float32_t radius) {
		self.setRadius(radius);
	}
	TS_JSAPI float32_t tsControlRect_getRadius(const ControlRect &self) {
		return self.getRadius();
	}
	TS_JSAPI void tsControlRect_setColor(ControlRect &self, const Color &color) {
		self.setColor(color);
	}
	TS_JSAPI void tsControlRect_setColor_1(ControlRect &self, float32_t r, float32_t g, float32_t b, float32_t a) {
		self.setColor(r, g, b, a);
	}
	TS_JSAPI const Color *tsControlRect_getColor(const ControlRect &self) {
		return new Color(self.getColor());
	}
	TS_JSAPI void tsControlRect_setStrokeStyle(ControlRect &self, const StrokeStyle &style) {
		self.setStrokeStyle(style);
	}
	TS_JSAPI const StrokeStyle *tsControlRect_getStrokeStyleConst(const ControlRect &self) {
		return new StrokeStyle(self.getStrokeStyleConst());
	}
	TS_JSAPI const StrokeStyle *tsControlRect_getStrokeStyle(const ControlRect &self) {
		return new StrokeStyle(self.getStrokeStyle());
	}
	TS_JSAPI StrokeStyle *tsControlRect_getStrokeStyle_1(ControlRect &self) {
		return new StrokeStyle(self.getStrokeStyle());
	}
	TS_JSAPI void tsControlRect_setGradientStyle(ControlRect &self, const GradientStyle &style) {
		self.setGradientStyle(style);
	}
	TS_JSAPI const GradientStyle *tsControlRect_getGradientStyleConst(const ControlRect &self) {
		return new GradientStyle(self.getGradientStyleConst());
	}
	TS_JSAPI const GradientStyle *tsControlRect_getGradientStyle(const ControlRect &self) {
		return new GradientStyle(self.getGradientStyle());
	}
	TS_JSAPI GradientStyle *tsControlRect_getGradientStyle_1(ControlRect &self) {
		return new GradientStyle(self.getGradientStyle());
	}
	TS_JSAPI void tsControlRect_setMipmap(ControlRect &self, float32_t mipmap) {
		self.setMipmap(mipmap);
	}
	TS_JSAPI float32_t tsControlRect_getMipmap(const ControlRect &self) {
		return self.getMipmap();
	}
	TS_JSAPI void tsControlRect_setFilter(ControlRect &self, uint32_t filter) {
		self.setFilter((Sampler::Filter)filter);
	}
	TS_JSAPI uint32_t tsControlRect_getFilter(const ControlRect &self) {
		return self.getFilter();
	}
	TS_JSAPI void tsControlRect_setAnisotropy(ControlRect &self, uint32_t anisotropy) {
		self.setAnisotropy(anisotropy);
	}
	TS_JSAPI uint32_t tsControlRect_getAnisotropy(const ControlRect &self) {
		return self.getAnisotropy();
	}
	TS_JSAPI void tsControlRect_setWrapMode(ControlRect &self, uint32_t mode) {
		self.setWrapMode((Sampler::WrapMode)mode);
	}
	TS_JSAPI uint32_t tsControlRect_getWrapMode(const ControlRect &self) {
		return self.getWrapMode();
	}
	TS_JSAPI void tsControlRect_setBlend(ControlRect &self, uint32_t op, uint32_t src, uint32_t dest) {
		self.setBlend((Pipeline::BlendOp)op, (Pipeline::BlendFunc)src, (Pipeline::BlendFunc)dest);
	}
	TS_JSAPI uint32_t tsControlRect_getBlendOp(const ControlRect &self) {
		return self.getBlendOp();
	}
	TS_JSAPI uint32_t tsControlRect_getBlendSrcFunc(const ControlRect &self) {
		return self.getBlendSrcFunc();
	}
	TS_JSAPI uint32_t tsControlRect_getBlendDestFunc(const ControlRect &self) {
		return self.getBlendDestFunc();
	}
	TS_JSAPI void tsControlRect_setTexture(ControlRect &self, Texture &texture, bool linear) {
		self.setTexture(texture, linear);
	}
	TS_JSAPI Texture *tsControlRect_getTexture(const ControlRect &self) {
		return new Texture(self.getTexture());
	}
	TS_JSAPI bool tsControlRect_getTextureLinear(const ControlRect &self) {
		return self.getTextureLinear();
	}
	TS_JSAPI void tsControlRect_setTextureName(ControlRect &self, const char *name) {
		self.setTextureName(name);
	}
	TS_JSAPI void tsControlRect_setTextureName_1(ControlRect &self, const String &name) {
		self.setTextureName(name);
	}
	TS_JSAPI String *tsControlRect_getTextureName(const ControlRect &self) {
		return new String(self.getTextureName());
	}
	TS_JSAPI void tsControlRect_setTextureScale(ControlRect &self, float32_t scale_x, float32_t scale_y) {
		self.setTextureScale(scale_x, scale_y);
	}
	TS_JSAPI float32_t tsControlRect_getTextureScaleX(const ControlRect &self) {
		return self.getTextureScaleX();
	}
	TS_JSAPI float32_t tsControlRect_getTextureScaleY(const ControlRect &self) {
		return self.getTextureScaleY();
	}
	TS_JSAPI void tsControlRect_setTextureFlip(ControlRect &self, bool flip_x, bool flip_y) {
		self.setTextureFlip(flip_x, flip_y);
	}
	TS_JSAPI bool tsControlRect_getTextureFlipX(const ControlRect &self) {
		return self.getTextureFlipX();
	}
	TS_JSAPI bool tsControlRect_getTextureFlipY(const ControlRect &self) {
		return self.getTextureFlipY();
	}
	TS_JSAPI void tsControlRect_setTextureProj(ControlRect &self, bool projection) {
		self.setTextureProj(projection);
	}
	TS_JSAPI bool tsControlRect_getTextureProj(const ControlRect &self) {
		return self.getTextureProj();
	}
	TS_JSAPI void tsControlRect_setTexCoord(ControlRect &self, const Rect &texcoord) {
		self.setTexCoord(texcoord);
	}
	TS_JSAPI void tsControlRect_setTexCoord_1(ControlRect &self, float32_t left, float32_t right, float32_t bottom, float32_t top) {
		self.setTexCoord(left, right, bottom, top);
	}
	TS_JSAPI const Rect *tsControlRect_getTexCoord(const ControlRect &self) {
		return new Rect(self.getTexCoord());
	}
	TS_JSAPI void tsControlRect_setInsideCallback(ControlRect &self, bool func) {
		self.setInsideCallback((func) ? make_control_rect_inside_callback(&self) : ControlRect::InsideCallback());
	}
	TS_JSAPI void tsControlRect_setPressedCallback(ControlRect &self, bool func) {
		self.setPressedCallback((func) ? make_control_rect_pressed_callback(&self) : ControlRect::PressedCallback());
	}
	TS_JSAPI void tsControlRect_setReleasedCallback(ControlRect &self, bool func) {
		self.setReleasedCallback((func) ? make_control_rect_released_callback(&self) : ControlRect::ReleasedCallback());
	}
	TS_JSAPI void tsControlRect_setClickedCallback(ControlRect &self, bool func) {
		self.setClickedCallback((func) ? make_control_rect_clicked_callback(&self) : ControlRect::ClickedCallback());
	}
	TS_JSAPI void tsControlRect_setClicked2Callback(ControlRect &self, bool func) {
		self.setClicked2Callback((func) ? make_control_rect_clicked_callback(&self) : ControlRect::ClickedCallback());
	}
	TS_JSAPI void tsControlRect_setClickedRightCallback(ControlRect &self, bool func) {
		self.setClickedRightCallback((func) ? make_control_rect_clicked_callback(&self) : ControlRect::ClickedCallback());
	}
	TS_JSAPI CanvasRect *tsControlRect_getCanvasRect(ControlRect &self) {
		return new CanvasRect(self.getCanvasRect());
	}
	TS_JSAPI CanvasMesh *tsControlRect_getCanvasMesh(ControlRect &self) {
		return new CanvasMesh(self.getCanvasMesh());
	}
	
	// Tellusim::ControlGrid
	TS_JSAPI ControlGrid *tsControlGrid_new() {
		return new ControlGrid();
	}
	TS_JSAPI ControlGrid *tsControlGrid_new_1(Control *parent) {
		return new ControlGrid(parent);
	}
	TS_JSAPI ControlGrid *tsControlGrid_new_2(Control *parent, uint32_t columns) {
		return new ControlGrid(parent, columns);
	}
	TS_JSAPI ControlGrid *tsControlGrid_new_3(Control *parent, uint32_t columns, float32_t x, float32_t y) {
		return new ControlGrid(parent, columns, x, y);
	}
	TS_JSAPI void tsControlGrid_delete(ControlGrid *self) {
		delete self;
	}
	TS_JSAPI bool tsControlGrid_equalControlPtr(const ControlGrid &self, const Control &base) {
		return self.operator==(base);
	}
	TS_JSAPI ControlGrid *tsControlGrid_castControlPtr(const Control &self) {
		return new ControlGrid(self);
	}
	TS_JSAPI Control *tsControlGrid_baseControlPtr(const ControlGrid &self) {
		return new Control(self.getControl());
	}
	TS_JSAPI void tsControlGrid_setColumns(ControlGrid &self, uint32_t columns) {
		self.setColumns(columns);
	}
	TS_JSAPI uint32_t tsControlGrid_getColumns(const ControlGrid &self) {
		return self.getColumns();
	}
	TS_JSAPI void tsControlGrid_setSpacing(ControlGrid &self, const Vector2f &spacing) {
		self.setSpacing(spacing);
	}
	TS_JSAPI void tsControlGrid_setSpacing_1(ControlGrid &self, float32_t x, float32_t y) {
		self.setSpacing(x, y);
	}
	TS_JSAPI const Vector2f *tsControlGrid_getSpacing(const ControlGrid &self) {
		return new Vector2f(self.getSpacing());
	}
	TS_JSAPI void tsControlGrid_setColumnRatio(ControlGrid &self, uint32_t index, float32_t ratio) {
		self.setColumnRatio(index, ratio);
	}
	TS_JSAPI float32_t tsControlGrid_getColumnRatio(const ControlGrid &self, uint32_t index) {
		return self.getColumnRatio(index);
	}
	TS_JSAPI void tsControlGrid_setColumnSpacing(ControlGrid &self, uint32_t index, float32_t spacing) {
		self.setColumnSpacing(index, spacing);
	}
	TS_JSAPI float32_t tsControlGrid_getColumnSpacing(const ControlGrid &self, uint32_t index) {
		return self.getColumnSpacing(index);
	}
	TS_JSAPI void tsControlGrid_setRowSpacing(ControlGrid &self, uint32_t index, float32_t spacing) {
		self.setRowSpacing(index, spacing);
	}
	TS_JSAPI float32_t tsControlGrid_getRowSpacing(const ControlGrid &self, uint32_t index) {
		return self.getRowSpacing(index);
	}
	TS_JSAPI const Vector2f *tsControlGrid_getControlsSize(const ControlGrid &self) {
		return new Vector2f(self.getControlsSize());
	}
	
	// Tellusim::ControlGroup
	static void control_group_clicked_callback(ControlGroup a0, void *self) {
		EM_ASM({ tsControlGroup.clicked_callback($0, $1); }, self, new ControlGroup(a0));
	}
	static ControlGroup::ClickedCallback make_control_group_clicked_callback(void *self) {
		auto ret = makeFunction(control_group_clicked_callback);
		ret.setArg1(self);
		return ret;
	}
	TS_JSAPI ControlGroup *tsControlGroup_new() {
		return new ControlGroup();
	}
	TS_JSAPI ControlGroup *tsControlGroup_new_1(Control *parent, bool above) {
		return new ControlGroup(parent, above);
	}
	TS_JSAPI ControlGroup *tsControlGroup_new_2(Control *parent, const char *text, bool above) {
		return new ControlGroup(parent, text, above);
	}
	TS_JSAPI ControlGroup *tsControlGroup_new_3(Control *parent, const String &text, bool above) {
		return new ControlGroup(parent, text, above);
	}
	TS_JSAPI ControlGroup *tsControlGroup_new_4(Control *parent, const char *text, uint32_t columns, bool above) {
		return new ControlGroup(parent, text, columns, above);
	}
	TS_JSAPI ControlGroup *tsControlGroup_new_5(Control *parent, const char *text, uint32_t columns, float32_t x, float32_t y, bool above) {
		return new ControlGroup(parent, text, columns, x, y, above);
	}
	TS_JSAPI void tsControlGroup_delete(ControlGroup *self) {
		delete self;
	}
	TS_JSAPI bool tsControlGroup_equalControlTextPtr(const ControlGroup &self, const ControlText &base) {
		return self.operator==(base);
	}
	TS_JSAPI ControlGroup *tsControlGroup_castControlTextPtr(const ControlText &self) {
		return new ControlGroup(self);
	}
	TS_JSAPI ControlText *tsControlGroup_baseControlTextPtr(const ControlGroup &self) {
		return new ControlText(self.getControlText());
	}
	TS_JSAPI void tsControlGroup_setAbove(ControlGroup &self, bool above, bool text) {
		self.setAbove(above, text);
	}
	TS_JSAPI bool tsControlGroup_isAbove(const ControlGroup &self) {
		return self.isAbove();
	}
	TS_JSAPI bool tsControlGroup_isBelow(const ControlGroup &self) {
		return self.isBelow();
	}
	TS_JSAPI void tsControlGroup_setFoldable(ControlGroup &self, bool foldable) {
		self.setFoldable(foldable);
	}
	TS_JSAPI bool tsControlGroup_isFoldable(const ControlGroup &self) {
		return self.isFoldable();
	}
	TS_JSAPI void tsControlGroup_setExpanded(ControlGroup &self, bool expanded) {
		self.setExpanded(expanded);
	}
	TS_JSAPI bool tsControlGroup_isExpanded(const ControlGroup &self) {
		return self.isExpanded();
	}
	TS_JSAPI void tsControlGroup_setBackground(ControlGroup &self, bool background) {
		self.setBackground(background);
	}
	TS_JSAPI bool tsControlGroup_getBackground(const ControlGroup &self) {
		return self.getBackground();
	}
	TS_JSAPI void tsControlGroup_setGroupRadius(ControlGroup &self, float32_t radius) {
		self.setGroupRadius(radius);
	}
	TS_JSAPI float32_t tsControlGroup_getGroupRadius(const ControlGroup &self) {
		return self.getGroupRadius();
	}
	TS_JSAPI void tsControlGroup_setGroupColor(ControlGroup &self, const Color &color) {
		self.setGroupColor(color);
	}
	TS_JSAPI const Color *tsControlGroup_getGroupColor(const ControlGroup &self) {
		return new Color(self.getGroupColor());
	}
	TS_JSAPI void tsControlGroup_setStrokeStyle(ControlGroup &self, const StrokeStyle &style) {
		self.setStrokeStyle(style);
	}
	TS_JSAPI const StrokeStyle *tsControlGroup_getStrokeStyleConst(const ControlGroup &self) {
		return new StrokeStyle(self.getStrokeStyleConst());
	}
	TS_JSAPI const StrokeStyle *tsControlGroup_getStrokeStyle(const ControlGroup &self) {
		return new StrokeStyle(self.getStrokeStyle());
	}
	TS_JSAPI StrokeStyle *tsControlGroup_getStrokeStyle_1(ControlGroup &self) {
		return new StrokeStyle(self.getStrokeStyle());
	}
	TS_JSAPI void tsControlGroup_setGradientStyle(ControlGroup &self, const GradientStyle &style) {
		self.setGradientStyle(style);
	}
	TS_JSAPI const GradientStyle *tsControlGroup_getGradientStyleConst(const ControlGroup &self) {
		return new GradientStyle(self.getGradientStyleConst());
	}
	TS_JSAPI const GradientStyle *tsControlGroup_getGradientStyle(const ControlGroup &self) {
		return new GradientStyle(self.getGradientStyle());
	}
	TS_JSAPI GradientStyle *tsControlGroup_getGradientStyle_1(ControlGroup &self) {
		return new GradientStyle(self.getGradientStyle());
	}
	TS_JSAPI void tsControlGroup_setFoldedText(ControlGroup &self, const char *text) {
		self.setFoldedText(text);
	}
	TS_JSAPI void tsControlGroup_setFoldedText_1(ControlGroup &self, const String &text) {
		self.setFoldedText(text);
	}
	TS_JSAPI String *tsControlGroup_getFoldedText(const ControlGroup &self) {
		return new String(self.getFoldedText());
	}
	TS_JSAPI void tsControlGroup_setExpandedText(ControlGroup &self, const char *text) {
		self.setExpandedText(text);
	}
	TS_JSAPI void tsControlGroup_setExpandedText_1(ControlGroup &self, const String &text) {
		self.setExpandedText(text);
	}
	TS_JSAPI String *tsControlGroup_getExpandedText(const ControlGroup &self) {
		return new String(self.getExpandedText());
	}
	TS_JSAPI void tsControlGroup_setColumns(ControlGroup &self, uint32_t columns) {
		self.setColumns(columns);
	}
	TS_JSAPI uint32_t tsControlGroup_getColumns(const ControlGroup &self) {
		return self.getColumns();
	}
	TS_JSAPI void tsControlGroup_setSpacing(ControlGroup &self, const Vector2f &spacing) {
		self.setSpacing(spacing);
	}
	TS_JSAPI void tsControlGroup_setSpacing_1(ControlGroup &self, float32_t x, float32_t y) {
		self.setSpacing(x, y);
	}
	TS_JSAPI const Vector2f *tsControlGroup_getSpacing(const ControlGroup &self) {
		return new Vector2f(self.getSpacing());
	}
	TS_JSAPI void tsControlGroup_setColumnRatio(ControlGroup &self, uint32_t index, float32_t ratio) {
		self.setColumnRatio(index, ratio);
	}
	TS_JSAPI float32_t tsControlGroup_getColumnRatio(const ControlGroup &self, uint32_t index) {
		return self.getColumnRatio(index);
	}
	TS_JSAPI void tsControlGroup_setColumnSpacing(ControlGroup &self, uint32_t index, float32_t spacing) {
		self.setColumnSpacing(index, spacing);
	}
	TS_JSAPI float32_t tsControlGroup_getColumnSpacing(const ControlGroup &self, uint32_t index) {
		return self.getColumnSpacing(index);
	}
	TS_JSAPI void tsControlGroup_setRowSpacing(ControlGroup &self, uint32_t index, float32_t spacing) {
		self.setRowSpacing(index, spacing);
	}
	TS_JSAPI float32_t tsControlGroup_getRowSpacing(const ControlGroup &self, uint32_t index) {
		return self.getRowSpacing(index);
	}
	TS_JSAPI const Vector2f *tsControlGroup_getControlsSize(const ControlGroup &self) {
		return new Vector2f(self.getControlsSize());
	}
	TS_JSAPI void tsControlGroup_setClickedCallback(ControlGroup &self, bool func) {
		self.setClickedCallback((func) ? make_control_group_clicked_callback(&self) : ControlGroup::ClickedCallback());
	}
	TS_JSAPI bool tsControlGroup_isClicked(ControlGroup &self) {
		return self.isClicked();
	}
	TS_JSAPI CanvasRect *tsControlGroup_getCanvasRect(ControlGroup &self) {
		return new CanvasRect(self.getCanvasRect());
	}
	
	// Tellusim::ControlPanel
	TS_JSAPI ControlPanel *tsControlPanel_new() {
		return new ControlPanel();
	}
	TS_JSAPI ControlPanel *tsControlPanel_new_1(Control *parent) {
		return new ControlPanel(parent);
	}
	TS_JSAPI ControlPanel *tsControlPanel_new_2(Control *parent, uint32_t columns) {
		return new ControlPanel(parent, columns);
	}
	TS_JSAPI ControlPanel *tsControlPanel_new_3(Control *parent, uint32_t columns, float32_t x, float32_t y) {
		return new ControlPanel(parent, columns, x, y);
	}
	TS_JSAPI void tsControlPanel_delete(ControlPanel *self) {
		delete self;
	}
	TS_JSAPI bool tsControlPanel_equalControlRectPtr(const ControlPanel &self, const ControlRect &base) {
		return self.operator==(base);
	}
	TS_JSAPI ControlPanel *tsControlPanel_castControlRectPtr(const ControlRect &self) {
		return new ControlPanel(self);
	}
	TS_JSAPI ControlRect *tsControlPanel_baseControlRectPtr(const ControlPanel &self) {
		return new ControlRect(self.getControlRect());
	}
	TS_JSAPI void tsControlPanel_setColumns(ControlPanel &self, uint32_t columns) {
		self.setColumns(columns);
	}
	TS_JSAPI uint32_t tsControlPanel_getColumns(const ControlPanel &self) {
		return self.getColumns();
	}
	TS_JSAPI void tsControlPanel_setSpacing(ControlPanel &self, const Vector2f &spacing) {
		self.setSpacing(spacing);
	}
	TS_JSAPI void tsControlPanel_setSpacing_1(ControlPanel &self, float32_t x, float32_t y) {
		self.setSpacing(x, y);
	}
	TS_JSAPI const Vector2f *tsControlPanel_getSpacing(const ControlPanel &self) {
		return new Vector2f(self.getSpacing());
	}
	TS_JSAPI void tsControlPanel_setColumnRatio(ControlPanel &self, uint32_t index, float32_t ratio) {
		self.setColumnRatio(index, ratio);
	}
	TS_JSAPI float32_t tsControlPanel_getColumnRatio(const ControlPanel &self, uint32_t index) {
		return self.getColumnRatio(index);
	}
	TS_JSAPI void tsControlPanel_setColumnSpacing(ControlPanel &self, uint32_t index, float32_t spacing) {
		self.setColumnSpacing(index, spacing);
	}
	TS_JSAPI float32_t tsControlPanel_getColumnSpacing(const ControlPanel &self, uint32_t index) {
		return self.getColumnSpacing(index);
	}
	TS_JSAPI void tsControlPanel_setRowSpacing(ControlPanel &self, uint32_t index, float32_t spacing) {
		self.setRowSpacing(index, spacing);
	}
	TS_JSAPI float32_t tsControlPanel_getRowSpacing(const ControlPanel &self, uint32_t index) {
		return self.getRowSpacing(index);
	}
	TS_JSAPI const Vector2f *tsControlPanel_getControlsSize(const ControlPanel &self) {
		return new Vector2f(self.getControlsSize());
	}
	
	// Tellusim::ControlDialog
	static void control_dialog_updated_callback(ControlDialog a0, void *self) {
		EM_ASM({ tsControlDialog.updated_callback($0, $1); }, self, new ControlDialog(a0));
	}
	static ControlDialog::UpdatedCallback make_control_dialog_updated_callback(void *self) {
		auto ret = makeFunction(control_dialog_updated_callback);
		ret.setArg1(self);
		return ret;
	}
	TS_JSAPI ControlDialog *tsControlDialog_new() {
		return new ControlDialog();
	}
	TS_JSAPI ControlDialog *tsControlDialog_new_1(Control *parent) {
		return new ControlDialog(parent);
	}
	TS_JSAPI ControlDialog *tsControlDialog_new_2(Control *parent, uint32_t columns) {
		return new ControlDialog(parent, columns);
	}
	TS_JSAPI ControlDialog *tsControlDialog_new_3(Control *parent, uint32_t columns, float32_t x, float32_t y) {
		return new ControlDialog(parent, columns, x, y);
	}
	TS_JSAPI void tsControlDialog_delete(ControlDialog *self) {
		delete self;
	}
	TS_JSAPI bool tsControlDialog_equalControlPanelPtr(const ControlDialog &self, const ControlPanel &base) {
		return self.operator==(base);
	}
	TS_JSAPI ControlDialog *tsControlDialog_castControlPanelPtr(const ControlPanel &self) {
		return new ControlDialog(self);
	}
	TS_JSAPI ControlPanel *tsControlDialog_baseControlPanelPtr(const ControlDialog &self) {
		return new ControlPanel(self.getControlPanel());
	}
	TS_JSAPI void tsControlDialog_setConstrained(ControlDialog &self, bool constrained) {
		self.setConstrained(constrained);
	}
	TS_JSAPI bool tsControlDialog_isConstrained(const ControlDialog &self) {
		return self.isConstrained();
	}
	TS_JSAPI void tsControlDialog_setResizable(ControlDialog &self, bool resizable) {
		self.setResizable(resizable);
	}
	TS_JSAPI bool tsControlDialog_isResizable(const ControlDialog &self) {
		return self.isResizable();
	}
	TS_JSAPI void tsControlDialog_setMoveable(ControlDialog &self, bool moveable) {
		self.setMoveable(moveable);
	}
	TS_JSAPI bool tsControlDialog_isMoveable(const ControlDialog &self) {
		return self.isMoveable();
	}
	TS_JSAPI void tsControlDialog_setResizeArea(ControlDialog &self, float32_t area) {
		self.setResizeArea(area);
	}
	TS_JSAPI float32_t tsControlDialog_getResizeArea(const ControlDialog &self) {
		return self.getResizeArea();
	}
	TS_JSAPI uint32_t tsControlDialog_getResizeAlign(const ControlDialog &self) {
		return self.getResizeAlign();
	}
	TS_JSAPI bool tsControlDialog_hasResizeAlign(const ControlDialog &self, uint32_t align) {
		return self.hasResizeAlign((Control::Align)align);
	}
	TS_JSAPI bool tsControlDialog_hasResizeAligns(const ControlDialog &self, uint32_t aligns) {
		return self.hasResizeAligns((Control::Align)aligns);
	}
	TS_JSAPI void tsControlDialog_setMousePosition(ControlDialog &self, const Vector2f &position) {
		self.setMousePosition(position);
	}
	TS_JSAPI const Vector2f *tsControlDialog_getMousePosition(const ControlDialog &self) {
		return new Vector2f(self.getMousePosition());
	}
	TS_JSAPI void tsControlDialog_setUpdatedCallback(ControlDialog &self, bool func) {
		self.setUpdatedCallback((func) ? make_control_dialog_updated_callback(&self) : ControlDialog::UpdatedCallback());
	}
	TS_JSAPI bool tsControlDialog_isUpdated(ControlDialog &self) {
		return self.isUpdated();
	}
	
	// Tellusim::ControlWindow
	TS_JSAPI ControlWindow *tsControlWindow_new() {
		return new ControlWindow();
	}
	TS_JSAPI ControlWindow *tsControlWindow_new_1(ControlRoot *root, Window &parent, Window &window) {
		return new ControlWindow(root, parent, window);
	}
	TS_JSAPI ControlWindow *tsControlWindow_new_2(ControlRoot *root, Window &parent, Window &window, uint32_t columns) {
		return new ControlWindow(root, parent, window, columns);
	}
	TS_JSAPI ControlWindow *tsControlWindow_new_3(ControlRoot *root, Window &parent, Window &window, uint32_t columns, float32_t x, float32_t y) {
		return new ControlWindow(root, parent, window, columns, x, y);
	}
	TS_JSAPI void tsControlWindow_delete(ControlWindow *self) {
		delete self;
	}
	TS_JSAPI bool tsControlWindow_equalControlDialogPtr(const ControlWindow &self, const ControlDialog &base) {
		return self.operator==(base);
	}
	TS_JSAPI ControlWindow *tsControlWindow_castControlDialogPtr(const ControlDialog &self) {
		return new ControlWindow(self);
	}
	TS_JSAPI ControlDialog *tsControlWindow_baseControlDialogPtr(const ControlWindow &self) {
		return new ControlDialog(self.getControlDialog());
	}
	TS_JSAPI Window *tsControlWindow_getParentWindow(const ControlWindow &self) {
		return new Window(self.getParentWindow());
	}
	TS_JSAPI Window *tsControlWindow_getDialogWindow(const ControlWindow &self) {
		return new Window(self.getDialogWindow());
	}
	
	// Tellusim::ControlCheck
	static void control_check_clicked_callback(ControlCheck a0, void *self) {
		EM_ASM({ tsControlCheck.clicked_callback($0, $1); }, self, new ControlCheck(a0));
	}
	static ControlCheck::ClickedCallback make_control_check_clicked_callback(void *self) {
		auto ret = makeFunction(control_check_clicked_callback);
		ret.setArg1(self);
		return ret;
	}
	TS_JSAPI ControlCheck *tsControlCheck_new() {
		return new ControlCheck();
	}
	TS_JSAPI ControlCheck *tsControlCheck_new_1(Control *parent) {
		return new ControlCheck(parent);
	}
	TS_JSAPI ControlCheck *tsControlCheck_new_2(Control *parent, const char *text) {
		return new ControlCheck(parent, text);
	}
	TS_JSAPI ControlCheck *tsControlCheck_new_3(Control *parent, const String &text) {
		return new ControlCheck(parent, text);
	}
	TS_JSAPI ControlCheck *tsControlCheck_new_4(Control *parent, const char *text, bool checked) {
		return new ControlCheck(parent, text, checked);
	}
	TS_JSAPI ControlCheck *tsControlCheck_new_5(Control *parent, const String &text, bool checked) {
		return new ControlCheck(parent, text, checked);
	}
	TS_JSAPI void tsControlCheck_delete(ControlCheck *self) {
		delete self;
	}
	TS_JSAPI bool tsControlCheck_equalControlTextPtr(const ControlCheck &self, const ControlText &base) {
		return self.operator==(base);
	}
	TS_JSAPI ControlCheck *tsControlCheck_castControlTextPtr(const ControlText &self) {
		return new ControlCheck(self);
	}
	TS_JSAPI ControlText *tsControlCheck_baseControlTextPtr(const ControlCheck &self) {
		return new ControlText(self.getControlText());
	}
	TS_JSAPI void tsControlCheck_setCheckText(ControlCheck &self, const char *text) {
		self.setCheckText(text);
	}
	TS_JSAPI void tsControlCheck_setCheckText_1(ControlCheck &self, const String &text) {
		self.setCheckText(text);
	}
	TS_JSAPI String *tsControlCheck_getCheckText(const ControlCheck &self) {
		return new String(self.getCheckText());
	}
	TS_JSAPI void tsControlCheck_setCheckColor(ControlCheck &self, const Color &color) {
		self.setCheckColor(color);
	}
	TS_JSAPI const Color *tsControlCheck_getCheckColor(const ControlCheck &self) {
		return new Color(self.getCheckColor());
	}
	TS_JSAPI void tsControlCheck_setCheckedColor(ControlCheck &self, const Color &color) {
		self.setCheckedColor(color);
	}
	TS_JSAPI const Color *tsControlCheck_getCheckedColor(const ControlCheck &self) {
		return new Color(self.getCheckedColor());
	}
	TS_JSAPI bool tsControlCheck_switchChecked(ControlCheck &self, bool callback) {
		return self.switchChecked(callback);
	}
	TS_JSAPI void tsControlCheck_setChecked(ControlCheck &self, bool checked, bool callback) {
		self.setChecked(checked, callback);
	}
	TS_JSAPI bool tsControlCheck_isChecked(const ControlCheck &self) {
		return self.isChecked();
	}
	TS_JSAPI void tsControlCheck_setClickedCallback(ControlCheck &self, bool func) {
		self.setClickedCallback((func) ? make_control_check_clicked_callback(&self) : ControlCheck::ClickedCallback());
	}
	TS_JSAPI bool tsControlCheck_isClicked(ControlCheck &self) {
		return self.isClicked();
	}
	TS_JSAPI CanvasMesh *tsControlCheck_getCanvasMesh(ControlCheck &self) {
		return new CanvasMesh(self.getCanvasMesh());
	}
	
	// Tellusim::ControlCombo
	static void control_combo_clicked_callback(ControlCombo a0, void *self) {
		EM_ASM({ tsControlCombo.clicked_callback($0, $1); }, self, new ControlCombo(a0));
	}
	static ControlCombo::ClickedCallback make_control_combo_clicked_callback(void *self) {
		auto ret = makeFunction(control_combo_clicked_callback);
		ret.setArg1(self);
		return ret;
	}
	static void control_combo_changed_callback(ControlCombo a0, void *self) {
		EM_ASM({ tsControlCombo.changed_callback($0, $1); }, self, new ControlCombo(a0));
	}
	static ControlCombo::ChangedCallback make_control_combo_changed_callback(void *self) {
		auto ret = makeFunction(control_combo_changed_callback);
		ret.setArg1(self);
		return ret;
	}
	TS_JSAPI ControlCombo *tsControlCombo_new() {
		return new ControlCombo();
	}
	TS_JSAPI ControlCombo *tsControlCombo_new_1(Control *parent) {
		return new ControlCombo(parent);
	}
	TS_JSAPI void tsControlCombo_delete(ControlCombo *self) {
		delete self;
	}
	TS_JSAPI bool tsControlCombo_equalControlTextPtr(const ControlCombo &self, const ControlText &base) {
		return self.operator==(base);
	}
	TS_JSAPI ControlCombo *tsControlCombo_castControlTextPtr(const ControlText &self) {
		return new ControlCombo(self);
	}
	TS_JSAPI ControlText *tsControlCombo_baseControlTextPtr(const ControlCombo &self) {
		return new ControlText(self.getControlText());
	}
	TS_JSAPI void tsControlCombo_setTextEnabled(ControlCombo &self, bool enabled) {
		self.setTextEnabled(enabled);
	}
	TS_JSAPI bool tsControlCombo_isTextEnabled(const ControlCombo &self) {
		return self.isTextEnabled();
	}
	TS_JSAPI void tsControlCombo_setMultiSelection(ControlCombo &self, bool multi_selection) {
		self.setMultiSelection(multi_selection);
	}
	TS_JSAPI bool tsControlCombo_isMultiSelection(const ControlCombo &self) {
		return self.isMultiSelection();
	}
	TS_JSAPI void tsControlCombo_setComboText(ControlCombo &self, const char *text) {
		self.setComboText(text);
	}
	TS_JSAPI void tsControlCombo_setComboText_1(ControlCombo &self, const String &text) {
		self.setComboText(text);
	}
	TS_JSAPI String *tsControlCombo_getComboText(const ControlCombo &self) {
		return new String(self.getComboText());
	}
	TS_JSAPI void tsControlCombo_setComboColor(ControlCombo &self, const Color &color) {
		self.setComboColor(color);
	}
	TS_JSAPI const Color *tsControlCombo_getComboColor(const ControlCombo &self) {
		return new Color(self.getComboColor());
	}
	TS_JSAPI void tsControlCombo_setItemsSpacing(ControlCombo &self, float32_t spacing) {
		self.setItemsSpacing(spacing);
	}
	TS_JSAPI float32_t tsControlCombo_getItemsSpacing(const ControlCombo &self) {
		return self.getItemsSpacing();
	}
	TS_JSAPI void tsControlCombo_clearItems(ControlCombo &self) {
		self.clearItems();
	}
	TS_JSAPI uint32_t tsControlCombo_addItem(ControlCombo &self, const char *text) {
		return self.addItem(text);
	}
	TS_JSAPI uint32_t tsControlCombo_addItem_1(ControlCombo &self, const String &text) {
		return self.addItem(text);
	}
	TS_JSAPI void tsControlCombo_addItem_2(ControlCombo &self, uint32_t index, const char *text) {
		self.addItem(index, text);
	}
	TS_JSAPI void tsControlCombo_addItem_3(ControlCombo &self, uint32_t index, const String &text) {
		self.addItem(index, text);
	}
	TS_JSAPI void tsControlCombo_removeItem(ControlCombo &self, uint32_t index) {
		self.removeItem(index);
	}
	TS_JSAPI uint32_t tsControlCombo_getNumItems(const ControlCombo &self) {
		return self.getNumItems();
	}
	TS_JSAPI bool tsControlCombo_switchItemSelected(ControlCombo &self, uint32_t index) {
		return self.switchItemSelected(index);
	}
	TS_JSAPI void tsControlCombo_setItemSelected(ControlCombo &self, uint32_t index, bool selected) {
		self.setItemSelected(index, selected);
	}
	TS_JSAPI bool tsControlCombo_isItemSelected(const ControlCombo &self, uint32_t index) {
		return self.isItemSelected(index);
	}
	TS_JSAPI void tsControlCombo_setItemText(ControlCombo &self, uint32_t index, const char *text) {
		self.setItemText(index, text);
	}
	TS_JSAPI void tsControlCombo_setItemText_1(ControlCombo &self, uint32_t index, const String &text) {
		self.setItemText(index, text);
	}
	TS_JSAPI String *tsControlCombo_getItemText(const ControlCombo &self, uint32_t index) {
		return new String(self.getItemText(index));
	}
	TS_JSAPI uint32_t tsControlCombo_findItemText(const ControlCombo &self, const char *text) {
		return self.findItemText(text);
	}
	TS_JSAPI uint32_t tsControlCombo_findItemText_1(const ControlCombo &self, const String &text) {
		return self.findItemText(text);
	}
	TS_JSAPI void tsControlCombo_setItemColor(ControlCombo &self, uint32_t index, const Color &color) {
		self.setItemColor(index, color);
	}
	TS_JSAPI const Color *tsControlCombo_getItemColor(const ControlCombo &self, uint32_t index) {
		return new Color(self.getItemColor(index));
	}
	TS_JSAPI void tsControlCombo_setCurrentIndex(ControlCombo &self, uint32_t index, bool callback) {
		self.setCurrentIndex(index, callback);
	}
	TS_JSAPI bool tsControlCombo_setCurrentText(ControlCombo &self, const char *text, bool callback) {
		return self.setCurrentText(text, callback);
	}
	TS_JSAPI bool tsControlCombo_setCurrentText_1(ControlCombo &self, const String &text, bool callback) {
		return self.setCurrentText(text, callback);
	}
	TS_JSAPI uint32_t tsControlCombo_getCurrentIndex(const ControlCombo &self) {
		return self.getCurrentIndex();
	}
	TS_JSAPI String *tsControlCombo_getCurrentText(const ControlCombo &self) {
		return new String(self.getCurrentText());
	}
	TS_JSAPI void tsControlCombo_setClickedCallback(ControlCombo &self, bool func) {
		self.setClickedCallback((func) ? make_control_combo_clicked_callback(&self) : ControlCombo::ClickedCallback());
	}
	TS_JSAPI bool tsControlCombo_isClicked(ControlCombo &self) {
		return self.isClicked();
	}
	TS_JSAPI void tsControlCombo_setChangedCallback(ControlCombo &self, bool func) {
		self.setChangedCallback((func) ? make_control_combo_changed_callback(&self) : ControlCombo::ChangedCallback());
	}
	TS_JSAPI bool tsControlCombo_isChanged(ControlCombo &self) {
		return self.isChanged();
	}
	TS_JSAPI CanvasMesh *tsControlCombo_getCanvasMesh(ControlCombo &self) {
		return new CanvasMesh(self.getCanvasMesh());
	}
	
	// Tellusim::ControlButton
	static void control_button_pressed_callback(ControlButton a0, float32_t x, float32_t y, void *self) {
		EM_ASM({ tsControlButton.pressed_callback($0, $1, $2, $3); }, self, new ControlButton(a0), x, y);
	}
	static ControlButton::PressedCallback make_control_button_pressed_callback(void *self) {
		auto ret = makeFunction(control_button_pressed_callback);
		ret.setArg3(self);
		return ret;
	}
	static void control_button_released_callback(ControlButton a0, float32_t x, float32_t y, void *self) {
		EM_ASM({ tsControlButton.released_callback($0, $1, $2, $3); }, self, new ControlButton(a0), x, y);
	}
	static ControlButton::ReleasedCallback make_control_button_released_callback(void *self) {
		auto ret = makeFunction(control_button_released_callback);
		ret.setArg3(self);
		return ret;
	}
	static void control_button_clicked_callback(ControlButton a0, void *self) {
		EM_ASM({ tsControlButton.clicked_callback($0, $1); }, self, new ControlButton(a0));
	}
	static ControlButton::ClickedCallback make_control_button_clicked_callback(void *self) {
		auto ret = makeFunction(control_button_clicked_callback);
		ret.setArg1(self);
		return ret;
	}
	TS_JSAPI ControlButton *tsControlButton_new() {
		return new ControlButton();
	}
	TS_JSAPI ControlButton *tsControlButton_new_1(Control *parent) {
		return new ControlButton(parent);
	}
	TS_JSAPI ControlButton *tsControlButton_new_2(Control *parent, const char *text) {
		return new ControlButton(parent, text);
	}
	TS_JSAPI ControlButton *tsControlButton_new_3(Control *parent, const String &text) {
		return new ControlButton(parent, text);
	}
	TS_JSAPI void tsControlButton_delete(ControlButton *self) {
		delete self;
	}
	TS_JSAPI bool tsControlButton_equalControlTextPtr(const ControlButton &self, const ControlText &base) {
		return self.operator==(base);
	}
	TS_JSAPI ControlButton *tsControlButton_castControlTextPtr(const ControlText &self) {
		return new ControlButton(self);
	}
	TS_JSAPI ControlText *tsControlButton_baseControlTextPtr(const ControlButton &self) {
		return new ControlText(self.getControlText());
	}
	TS_JSAPI void tsControlButton_setBackground(ControlButton &self, bool background) {
		self.setBackground(background);
	}
	TS_JSAPI bool tsControlButton_getBackground(const ControlButton &self) {
		return self.getBackground();
	}
	TS_JSAPI void tsControlButton_setButtonMode(ControlButton &self, uint32_t mode) {
		self.setButtonMode((CanvasElement::Mode)mode);
	}
	TS_JSAPI uint32_t tsControlButton_getButtonMode(const ControlButton &self) {
		return self.getButtonMode();
	}
	TS_JSAPI void tsControlButton_setButtonRadius(ControlButton &self, float32_t radius) {
		self.setButtonRadius(radius);
	}
	TS_JSAPI float32_t tsControlButton_getButtonRadius(const ControlButton &self) {
		return self.getButtonRadius();
	}
	TS_JSAPI void tsControlButton_setButtonColor(ControlButton &self, const Color &color) {
		self.setButtonColor(color);
	}
	TS_JSAPI const Color *tsControlButton_getButtonColor(const ControlButton &self) {
		return new Color(self.getButtonColor());
	}
	TS_JSAPI void tsControlButton_setStrokeStyle(ControlButton &self, const StrokeStyle &style) {
		self.setStrokeStyle(style);
	}
	TS_JSAPI const StrokeStyle *tsControlButton_getStrokeStyleConst(const ControlButton &self) {
		return new StrokeStyle(self.getStrokeStyleConst());
	}
	TS_JSAPI const StrokeStyle *tsControlButton_getStrokeStyle(const ControlButton &self) {
		return new StrokeStyle(self.getStrokeStyle());
	}
	TS_JSAPI StrokeStyle *tsControlButton_getStrokeStyle_1(ControlButton &self) {
		return new StrokeStyle(self.getStrokeStyle());
	}
	TS_JSAPI void tsControlButton_setGradientStyle(ControlButton &self, const GradientStyle &style) {
		self.setGradientStyle(style);
	}
	TS_JSAPI const GradientStyle *tsControlButton_getGradientStyleConst(const ControlButton &self) {
		return new GradientStyle(self.getGradientStyleConst());
	}
	TS_JSAPI const GradientStyle *tsControlButton_getGradientStyle(const ControlButton &self) {
		return new GradientStyle(self.getGradientStyle());
	}
	TS_JSAPI GradientStyle *tsControlButton_getGradientStyle_1(ControlButton &self) {
		return new GradientStyle(self.getGradientStyle());
	}
	TS_JSAPI void tsControlButton_setPressedCallback(ControlButton &self, bool func) {
		self.setPressedCallback((func) ? make_control_button_pressed_callback(&self) : ControlButton::PressedCallback());
	}
	TS_JSAPI bool tsControlButton_isPressed(ControlButton &self) {
		return self.isPressed();
	}
	TS_JSAPI void tsControlButton_setReleasedCallback(ControlButton &self, bool func) {
		self.setReleasedCallback((func) ? make_control_button_released_callback(&self) : ControlButton::ReleasedCallback());
	}
	TS_JSAPI bool tsControlButton_isReleased(ControlButton &self) {
		return self.isReleased();
	}
	TS_JSAPI void tsControlButton_setClickedCallback(ControlButton &self, bool func) {
		self.setClickedCallback((func) ? make_control_button_clicked_callback(&self) : ControlButton::ClickedCallback());
	}
	TS_JSAPI bool tsControlButton_isClicked(ControlButton &self) {
		return self.isClicked();
	}
	TS_JSAPI CanvasRect *tsControlButton_getCanvasRect(ControlButton &self) {
		return new CanvasRect(self.getCanvasRect());
	}
	TS_JSAPI CanvasMesh *tsControlButton_getCanvasMesh(ControlButton &self) {
		return new CanvasMesh(self.getCanvasMesh());
	}
	
	// Tellusim::ControlSlider
	static String control_slider_format_callback(ControlSlider a0, void *self) {
		return String((const char*)EM_ASM_INT({ return tsControlSlider.format_callback($0, $1); }, self, new ControlSlider(a0)));
	}
	static ControlSlider::FormatCallback make_control_slider_format_callback(void *self) {
		auto ret = makeFunction(control_slider_format_callback);
		ret.setArg1(self);
		return ret;
	}
	static void control_slider_pressed_callback(ControlSlider a0, void *self) {
		EM_ASM({ tsControlSlider.pressed_callback($0, $1); }, self, new ControlSlider(a0));
	}
	static ControlSlider::PressedCallback make_control_slider_pressed_callback(void *self) {
		auto ret = makeFunction(control_slider_pressed_callback);
		ret.setArg1(self);
		return ret;
	}
	static void control_slider_released_callback(ControlSlider a0, void *self) {
		EM_ASM({ tsControlSlider.released_callback($0, $1); }, self, new ControlSlider(a0));
	}
	static ControlSlider::ReleasedCallback make_control_slider_released_callback(void *self) {
		auto ret = makeFunction(control_slider_released_callback);
		ret.setArg1(self);
		return ret;
	}
	static void control_slider_clicked_callback(ControlSlider a0, void *self) {
		EM_ASM({ tsControlSlider.clicked_callback($0, $1); }, self, new ControlSlider(a0));
	}
	static ControlSlider::ClickedCallback make_control_slider_clicked_callback(void *self) {
		auto ret = makeFunction(control_slider_clicked_callback);
		ret.setArg1(self);
		return ret;
	}
	static void control_slider_changed_callback(ControlSlider a0, void *self) {
		EM_ASM({ tsControlSlider.changed_callback($0, $1); }, self, new ControlSlider(a0));
	}
	static ControlSlider::ChangedCallback make_control_slider_changed_callback(void *self) {
		auto ret = makeFunction(control_slider_changed_callback);
		ret.setArg1(self);
		return ret;
	}
	TS_JSAPI ControlSlider *tsControlSlider_new() {
		return new ControlSlider();
	}
	TS_JSAPI ControlSlider *tsControlSlider_new_1(Control *parent) {
		return new ControlSlider(parent);
	}
	TS_JSAPI ControlSlider *tsControlSlider_new_2(Control *parent, const char *text) {
		return new ControlSlider(parent, text);
	}
	TS_JSAPI ControlSlider *tsControlSlider_new_3(Control *parent, const String &text) {
		return new ControlSlider(parent, text);
	}
	TS_JSAPI ControlSlider *tsControlSlider_new_4(Control *parent, const char *text, uint32_t digits) {
		return new ControlSlider(parent, text, digits);
	}
	TS_JSAPI ControlSlider *tsControlSlider_new_5(Control *parent, const char *text, uint32_t digits, float64_t value) {
		return new ControlSlider(parent, text, digits, value);
	}
	TS_JSAPI ControlSlider *tsControlSlider_new_6(Control *parent, const char *text, uint32_t digits, float64_t value, float64_t min, float64_t max) {
		return new ControlSlider(parent, text, digits, value, min, max);
	}
	TS_JSAPI ControlSlider *tsControlSlider_new_7(Control *parent, const char *text, float64_t value, float64_t min, float64_t max) {
		return new ControlSlider(parent, text, value, min, max);
	}
	TS_JSAPI ControlSlider *tsControlSlider_new_8(Control *parent, const char *text, uint32_t value, uint32_t min, uint32_t max) {
		return new ControlSlider(parent, text, value, min, max);
	}
	TS_JSAPI ControlSlider *tsControlSlider_new_9(Control *parent, const char *text, int32_t value, int32_t min, int32_t max) {
		return new ControlSlider(parent, text, value, min, max);
	}
	TS_JSAPI void tsControlSlider_delete(ControlSlider *self) {
		delete self;
	}
	TS_JSAPI bool tsControlSlider_equalControlTextPtr(const ControlSlider &self, const ControlText &base) {
		return self.operator==(base);
	}
	TS_JSAPI ControlSlider *tsControlSlider_castControlTextPtr(const ControlText &self) {
		return new ControlSlider(self);
	}
	TS_JSAPI ControlText *tsControlSlider_baseControlTextPtr(const ControlSlider &self) {
		return new ControlText(self.getControlText());
	}
	TS_JSAPI void tsControlSlider_setConstrained(ControlSlider &self, bool constrained) {
		self.setConstrained(constrained);
	}
	TS_JSAPI bool tsControlSlider_isConstrained(const ControlSlider &self) {
		return self.isConstrained();
	}
	TS_JSAPI void tsControlSlider_setTextEnabled(ControlSlider &self, bool enabled) {
		self.setTextEnabled(enabled);
	}
	TS_JSAPI bool tsControlSlider_isTextEnabled(const ControlSlider &self) {
		return self.isTextEnabled();
	}
	TS_JSAPI void tsControlSlider_setSliderColor(ControlSlider &self, const Color &color) {
		self.setSliderColor(color);
	}
	TS_JSAPI const Color *tsControlSlider_getSliderColor(const ControlSlider &self) {
		return new Color(self.getSliderColor());
	}
	TS_JSAPI void tsControlSlider_setDigits(ControlSlider &self, uint32_t digits) {
		self.setDigits(digits);
	}
	TS_JSAPI uint32_t tsControlSlider_getDigits(const ControlSlider &self) {
		return self.getDigits();
	}
	TS_JSAPI void tsControlSlider_setStep(ControlSlider &self, float64_t step) {
		self.setStep(step);
	}
	TS_JSAPI float64_t tsControlSlider_getStep(const ControlSlider &self) {
		return self.getStep();
	}
	TS_JSAPI void tsControlSlider_setBase(ControlSlider &self, float64_t base) {
		self.setBase(base);
	}
	TS_JSAPI float64_t tsControlSlider_getBase(const ControlSlider &self) {
		return self.getBase();
	}
	TS_JSAPI void tsControlSlider_setFormat(ControlSlider &self, const char *format) {
		self.setFormat(format);
	}
	TS_JSAPI void tsControlSlider_setFormat_1(ControlSlider &self, const String &format) {
		self.setFormat(format);
	}
	TS_JSAPI String *tsControlSlider_getFormat(const ControlSlider &self) {
		return new String(self.getFormat());
	}
	TS_JSAPI void tsControlSlider_setValue(ControlSlider &self, float64_t value, bool callback, bool exponent) {
		self.setValue(value, callback, exponent);
	}
	TS_JSAPI float64_t tsControlSlider_getValue(const ControlSlider &self, bool exponent) {
		return self.getValue(exponent);
	}
	TS_JSAPI float32_t tsControlSlider_getValuef32(const ControlSlider &self, bool exponent) {
		return self.getValuef32(exponent);
	}
	TS_JSAPI uint32_t tsControlSlider_getValueu32(const ControlSlider &self, bool exponent) {
		return self.getValueu32(exponent);
	}
	TS_JSAPI int32_t tsControlSlider_getValuei32(const ControlSlider &self, bool exponent) {
		return self.getValuei32(exponent);
	}
	TS_JSAPI void tsControlSlider_setRange(ControlSlider &self, float64_t min, float64_t max, bool exponent) {
		self.setRange(min, max, exponent);
	}
	TS_JSAPI float64_t tsControlSlider_getMinRange(const ControlSlider &self, bool exponent) {
		return self.getMinRange(exponent);
	}
	TS_JSAPI float64_t tsControlSlider_getMaxRange(const ControlSlider &self, bool exponent) {
		return self.getMaxRange(exponent);
	}
	TS_JSAPI void tsControlSlider_setHandleSize(ControlSlider &self, float32_t size) {
		self.setHandleSize(size);
	}
	TS_JSAPI float32_t tsControlSlider_getHandleSize(const ControlSlider &self) {
		return self.getHandleSize();
	}
	TS_JSAPI void tsControlSlider_setFormatCallback(ControlSlider &self, bool func) {
		self.setFormatCallback((func) ? make_control_slider_format_callback(&self) : ControlSlider::FormatCallback());
	}
	TS_JSAPI void tsControlSlider_setPressedCallback(ControlSlider &self, bool func) {
		self.setPressedCallback((func) ? make_control_slider_pressed_callback(&self) : ControlSlider::PressedCallback());
	}
	TS_JSAPI bool tsControlSlider_isPressed(ControlSlider &self) {
		return self.isPressed();
	}
	TS_JSAPI void tsControlSlider_setReleasedCallback(ControlSlider &self, bool func) {
		self.setReleasedCallback((func) ? make_control_slider_released_callback(&self) : ControlSlider::ReleasedCallback());
	}
	TS_JSAPI bool tsControlSlider_isReleased(ControlSlider &self) {
		return self.isReleased();
	}
	TS_JSAPI void tsControlSlider_setClickedCallback(ControlSlider &self, bool func) {
		self.setClickedCallback((func) ? make_control_slider_clicked_callback(&self) : ControlSlider::ClickedCallback());
	}
	TS_JSAPI void tsControlSlider_setClicked2Callback(ControlSlider &self, bool func) {
		self.setClicked2Callback((func) ? make_control_slider_clicked_callback(&self) : ControlSlider::ClickedCallback());
	}
	TS_JSAPI void tsControlSlider_setClickedRightCallback(ControlSlider &self, bool func) {
		self.setClickedRightCallback((func) ? make_control_slider_clicked_callback(&self) : ControlSlider::ClickedCallback());
	}
	TS_JSAPI bool tsControlSlider_isClicked(ControlSlider &self) {
		return self.isClicked();
	}
	TS_JSAPI void tsControlSlider_setChangedCallback(ControlSlider &self, bool func) {
		self.setChangedCallback((func) ? make_control_slider_changed_callback(&self) : ControlSlider::ChangedCallback());
	}
	TS_JSAPI bool tsControlSlider_isChanged(ControlSlider &self, bool clear) {
		return self.isChanged(clear);
	}
	TS_JSAPI CanvasMesh *tsControlSlider_getCanvasMesh(ControlSlider &self) {
		return new CanvasMesh(self.getCanvasMesh());
	}
	
	// Tellusim::ControlScroll
	static void control_scroll_clicked_callback(ControlScroll a0, void *self) {
		EM_ASM({ tsControlScroll.clicked_callback($0, $1); }, self, new ControlScroll(a0));
	}
	static ControlScroll::ClickedCallback make_control_scroll_clicked_callback(void *self) {
		auto ret = makeFunction(control_scroll_clicked_callback);
		ret.setArg1(self);
		return ret;
	}
	static void control_scroll_changed_callback(ControlScroll a0, void *self) {
		EM_ASM({ tsControlScroll.changed_callback($0, $1); }, self, new ControlScroll(a0));
	}
	static ControlScroll::ChangedCallback make_control_scroll_changed_callback(void *self) {
		auto ret = makeFunction(control_scroll_changed_callback);
		ret.setArg1(self);
		return ret;
	}
	TS_JSAPI ControlScroll *tsControlScroll_new() {
		return new ControlScroll();
	}
	TS_JSAPI ControlScroll *tsControlScroll_new_1(Control *parent, bool vertical) {
		return new ControlScroll(parent, vertical);
	}
	TS_JSAPI ControlScroll *tsControlScroll_new_2(Control *parent, float64_t value, bool vertical) {
		return new ControlScroll(parent, value, vertical);
	}
	TS_JSAPI ControlScroll *tsControlScroll_new_3(Control *parent, float64_t value, float64_t frame, float64_t range, bool vertical) {
		return new ControlScroll(parent, value, frame, range, vertical);
	}
	TS_JSAPI ControlScroll *tsControlScroll_new_4(Control *parent, uint32_t value, uint32_t frame, uint32_t range, bool vertical) {
		return new ControlScroll(parent, value, frame, range, vertical);
	}
	TS_JSAPI ControlScroll *tsControlScroll_new_5(Control *parent, int32_t value, int32_t frame, int32_t range, bool vertical) {
		return new ControlScroll(parent, value, frame, range, vertical);
	}
	TS_JSAPI void tsControlScroll_delete(ControlScroll *self) {
		delete self;
	}
	TS_JSAPI bool tsControlScroll_equalControlTextPtr(const ControlScroll &self, const ControlText &base) {
		return self.operator==(base);
	}
	TS_JSAPI ControlScroll *tsControlScroll_castControlTextPtr(const ControlText &self) {
		return new ControlScroll(self);
	}
	TS_JSAPI ControlText *tsControlScroll_baseControlTextPtr(const ControlScroll &self) {
		return new ControlText(self.getControlText());
	}
	TS_JSAPI void tsControlScroll_setVertical(ControlScroll &self, bool vertical, bool text) {
		self.setVertical(vertical, text);
	}
	TS_JSAPI bool tsControlScroll_isHorizontal(const ControlScroll &self) {
		return self.isHorizontal();
	}
	TS_JSAPI bool tsControlScroll_isVertical(const ControlScroll &self) {
		return self.isVertical();
	}
	TS_JSAPI void tsControlScroll_setPrevText(ControlScroll &self, const char *text) {
		self.setPrevText(text);
	}
	TS_JSAPI void tsControlScroll_setPrevText_1(ControlScroll &self, const String &text) {
		self.setPrevText(text);
	}
	TS_JSAPI String *tsControlScroll_getPrevText(const ControlScroll &self) {
		return new String(self.getPrevText());
	}
	TS_JSAPI void tsControlScroll_setNextText(ControlScroll &self, const char *text) {
		self.setNextText(text);
	}
	TS_JSAPI void tsControlScroll_setNextText_1(ControlScroll &self, const String &text) {
		self.setNextText(text);
	}
	TS_JSAPI String *tsControlScroll_getNextText(const ControlScroll &self) {
		return new String(self.getNextText());
	}
	TS_JSAPI void tsControlScroll_setScrollColor(ControlScroll &self, const Color &color) {
		self.setScrollColor(color);
	}
	TS_JSAPI const Color *tsControlScroll_getScrollColor(const ControlScroll &self) {
		return new Color(self.getScrollColor());
	}
	TS_JSAPI void tsControlScroll_setStep(ControlScroll &self, float64_t step) {
		self.setStep(step);
	}
	TS_JSAPI float64_t tsControlScroll_getStep(const ControlScroll &self) {
		return self.getStep();
	}
	TS_JSAPI void tsControlScroll_setValue(ControlScroll &self, float64_t value, bool callback) {
		self.setValue(value, callback);
	}
	TS_JSAPI float64_t tsControlScroll_getValue(const ControlScroll &self) {
		return self.getValue();
	}
	TS_JSAPI void tsControlScroll_setFrame(ControlScroll &self, float64_t frame) {
		self.setFrame(frame);
	}
	TS_JSAPI float64_t tsControlScroll_getFrame(const ControlScroll &self) {
		return self.getFrame();
	}
	TS_JSAPI void tsControlScroll_setRange(ControlScroll &self, float64_t range) {
		self.setRange(range);
	}
	TS_JSAPI float64_t tsControlScroll_getRange(const ControlScroll &self) {
		return self.getRange();
	}
	TS_JSAPI void tsControlScroll_setFrameAlign(ControlScroll &self, uint32_t align) {
		self.setFrameAlign((Control::Align)align);
	}
	TS_JSAPI uint32_t tsControlScroll_getFrameAlign(const ControlScroll &self) {
		return self.getFrameAlign();
	}
	TS_JSAPI bool tsControlScroll_hasFrameAlign(const ControlScroll &self, uint32_t align) {
		return self.hasFrameAlign((Control::Align)align);
	}
	TS_JSAPI bool tsControlScroll_hasFrameAligns(const ControlScroll &self, uint32_t aligns) {
		return self.hasFrameAligns((Control::Align)aligns);
	}
	TS_JSAPI void tsControlScroll_setClickedCallback(ControlScroll &self, bool func) {
		self.setClickedCallback((func) ? make_control_scroll_clicked_callback(&self) : ControlScroll::ClickedCallback());
	}
	TS_JSAPI bool tsControlScroll_isClicked(ControlScroll &self) {
		return self.isClicked();
	}
	TS_JSAPI void tsControlScroll_setChangedCallback(ControlScroll &self, bool func) {
		self.setChangedCallback((func) ? make_control_scroll_changed_callback(&self) : ControlScroll::ChangedCallback());
	}
	TS_JSAPI bool tsControlScroll_isChanged(ControlScroll &self, bool clear) {
		return self.isChanged(clear);
	}
	TS_JSAPI CanvasMesh *tsControlScroll_getCanvasMesh(ControlScroll &self) {
		return new CanvasMesh(self.getCanvasMesh());
	}
	
	// Tellusim::ControlSplit
	TS_JSAPI ControlSplit *tsControlSplit_new() {
		return new ControlSplit();
	}
	TS_JSAPI ControlSplit *tsControlSplit_new_1(Control *parent, bool vertical) {
		return new ControlSplit(parent, vertical);
	}
	TS_JSAPI ControlSplit *tsControlSplit_new_2(Control *parent, float32_t value, bool vertical) {
		return new ControlSplit(parent, value, vertical);
	}
	TS_JSAPI void tsControlSplit_delete(ControlSplit *self) {
		delete self;
	}
	TS_JSAPI bool tsControlSplit_equalControlPtr(const ControlSplit &self, const Control &base) {
		return self.operator==(base);
	}
	TS_JSAPI ControlSplit *tsControlSplit_castControlPtr(const Control &self) {
		return new ControlSplit(self);
	}
	TS_JSAPI Control *tsControlSplit_baseControlPtr(const ControlSplit &self) {
		return new Control(self.getControl());
	}
	TS_JSAPI void tsControlSplit_setAbsolute(ControlSplit &self, bool absolute) {
		self.setAbsolute(absolute);
	}
	TS_JSAPI bool tsControlSplit_isAbsolute(const ControlSplit &self) {
		return self.isAbsolute();
	}
	TS_JSAPI void tsControlSplit_setVertical(ControlSplit &self, bool vertical) {
		self.setVertical(vertical);
	}
	TS_JSAPI bool tsControlSplit_isHorizontal(const ControlSplit &self) {
		return self.isHorizontal();
	}
	TS_JSAPI bool tsControlSplit_isVertical(const ControlSplit &self) {
		return self.isVertical();
	}
	TS_JSAPI void tsControlSplit_setValue(ControlSplit &self, float32_t value) {
		self.setValue(value);
	}
	TS_JSAPI float32_t tsControlSplit_getValue(const ControlSplit &self) {
		return self.getValue();
	}
	TS_JSAPI void tsControlSplit_setHandleSize(ControlSplit &self, float32_t size) {
		self.setHandleSize(size);
	}
	TS_JSAPI float32_t tsControlSplit_getHandleSize(const ControlSplit &self) {
		return self.getHandleSize();
	}
	TS_JSAPI const Vector2f *tsControlSplit_getControlsSize(const ControlSplit &self) {
		return new Vector2f(self.getControlsSize());
	}
	
	// Tellusim::ControlArea
	TS_JSAPI ControlArea *tsControlArea_new() {
		return new ControlArea();
	}
	TS_JSAPI ControlArea *tsControlArea_new_1(Control *parent) {
		return new ControlArea(parent);
	}
	TS_JSAPI ControlArea *tsControlArea_new_2(Control *parent, uint32_t columns) {
		return new ControlArea(parent, columns);
	}
	TS_JSAPI ControlArea *tsControlArea_new_3(Control *parent, bool horizontal, bool vertical) {
		return new ControlArea(parent, horizontal, vertical);
	}
	TS_JSAPI ControlArea *tsControlArea_new_4(Control *parent, uint32_t columns, float32_t x, float32_t y) {
		return new ControlArea(parent, columns, x, y);
	}
	TS_JSAPI void tsControlArea_delete(ControlArea *self) {
		delete self;
	}
	TS_JSAPI bool tsControlArea_equalControlPtr(const ControlArea &self, const Control &base) {
		return self.operator==(base);
	}
	TS_JSAPI ControlArea *tsControlArea_castControlPtr(const Control &self) {
		return new ControlArea(self);
	}
	TS_JSAPI Control *tsControlArea_baseControlPtr(const ControlArea &self) {
		return new Control(self.getControl());
	}
	TS_JSAPI void tsControlArea_setAbsolute(ControlArea &self, bool absolute) {
		self.setAbsolute(absolute);
	}
	TS_JSAPI bool tsControlArea_isAbsolute(const ControlArea &self) {
		return self.isAbsolute();
	}
	TS_JSAPI void tsControlArea_setScalable(ControlArea &self, bool scalable) {
		self.setScalable(scalable);
	}
	TS_JSAPI bool tsControlArea_isScalable(const ControlArea &self) {
		return self.isScalable();
	}
	TS_JSAPI void tsControlArea_setScrollable(ControlArea &self, bool scrollable) {
		self.setScrollable(scrollable);
	}
	TS_JSAPI bool tsControlArea_isScrollable(const ControlArea &self) {
		return self.isScrollable();
	}
	TS_JSAPI void tsControlArea_setScale(ControlArea &self, float32_t scale) {
		self.setScale(scale);
	}
	TS_JSAPI float32_t tsControlArea_getScale(const ControlArea &self) {
		return self.getScale();
	}
	TS_JSAPI void tsControlArea_setScaleRange(ControlArea &self, float32_t min, float32_t max) {
		self.setScaleRange(min, max);
	}
	TS_JSAPI float32_t tsControlArea_getMinScale(const ControlArea &self) {
		return self.getMinScale();
	}
	TS_JSAPI float32_t tsControlArea_getMaxScale(const ControlArea &self) {
		return self.getMaxScale();
	}
	TS_JSAPI void tsControlArea_setHorizontalStep(ControlArea &self, float64_t step) {
		self.setHorizontalStep(step);
	}
	TS_JSAPI void tsControlArea_setVerticalStep(ControlArea &self, float64_t step) {
		self.setVerticalStep(step);
	}
	TS_JSAPI void tsControlArea_setStep(ControlArea &self, float64_t horizontal, float64_t vertical) {
		self.setStep(horizontal, vertical);
	}
	TS_JSAPI float64_t tsControlArea_getHorizontalStep(const ControlArea &self) {
		return self.getHorizontalStep();
	}
	TS_JSAPI float64_t tsControlArea_getVerticalStep(const ControlArea &self) {
		return self.getVerticalStep();
	}
	TS_JSAPI void tsControlArea_setHorizontalValue(ControlArea &self, float64_t value) {
		self.setHorizontalValue(value);
	}
	TS_JSAPI void tsControlArea_setVerticalValue(ControlArea &self, float64_t value) {
		self.setVerticalValue(value);
	}
	TS_JSAPI void tsControlArea_setValue(ControlArea &self, float64_t horizontal, float64_t vertical) {
		self.setValue(horizontal, vertical);
	}
	TS_JSAPI float64_t tsControlArea_getHorizontalValue(const ControlArea &self) {
		return self.getHorizontalValue();
	}
	TS_JSAPI float64_t tsControlArea_getVerticalValue(const ControlArea &self) {
		return self.getVerticalValue();
	}
	TS_JSAPI void tsControlArea_setFrameAlign(ControlArea &self, uint32_t align) {
		self.setFrameAlign((Control::Align)align);
	}
	TS_JSAPI uint32_t tsControlArea_getFrameAlign(const ControlArea &self) {
		return self.getFrameAlign();
	}
	TS_JSAPI float64_t tsControlArea_getHorizontalFrame(const ControlArea &self) {
		return self.getHorizontalFrame();
	}
	TS_JSAPI float64_t tsControlArea_getVerticalFrame(const ControlArea &self) {
		return self.getVerticalFrame();
	}
	TS_JSAPI float64_t tsControlArea_getHorizontalRange(const ControlArea &self) {
		return self.getHorizontalRange();
	}
	TS_JSAPI float64_t tsControlArea_getVerticalRange(const ControlArea &self) {
		return self.getVerticalRange();
	}
	TS_JSAPI void tsControlArea_setHorizontalEnabled(ControlArea &self, bool enabled, bool dynamic) {
		self.setHorizontalEnabled(enabled, dynamic);
	}
	TS_JSAPI bool tsControlArea_isHorizontalEnabled(const ControlArea &self) {
		return self.isHorizontalEnabled();
	}
	TS_JSAPI bool tsControlArea_isHorizontalDynamic(const ControlArea &self) {
		return self.isHorizontalDynamic();
	}
	TS_JSAPI bool tsControlArea_isHorizontalHidden(const ControlArea &self) {
		return self.isHorizontalHidden();
	}
	TS_JSAPI const ControlScroll *tsControlArea_getHorizontalScroll(const ControlArea &self) {
		return new ControlScroll(self.getHorizontalScroll());
	}
	TS_JSAPI ControlScroll *tsControlArea_getHorizontalScroll_1(ControlArea &self) {
		return new ControlScroll(self.getHorizontalScroll());
	}
	TS_JSAPI void tsControlArea_setVerticalEnabled(ControlArea &self, bool enabled, bool dynamic) {
		self.setVerticalEnabled(enabled, dynamic);
	}
	TS_JSAPI bool tsControlArea_isVerticalEnabled(const ControlArea &self) {
		return self.isVerticalEnabled();
	}
	TS_JSAPI bool tsControlArea_isVerticalDynamic(const ControlArea &self) {
		return self.isVerticalDynamic();
	}
	TS_JSAPI bool tsControlArea_isVerticalHidden(const ControlArea &self) {
		return self.isVerticalHidden();
	}
	TS_JSAPI const ControlScroll *tsControlArea_getVerticalScroll(const ControlArea &self) {
		return new ControlScroll(self.getVerticalScroll());
	}
	TS_JSAPI ControlScroll *tsControlArea_getVerticalScroll_1(ControlArea &self) {
		return new ControlScroll(self.getVerticalScroll());
	}
	TS_JSAPI bool tsControlArea_setFontSize(ControlArea &self, uint32_t size) {
		return self.setFontSize(size);
	}
	TS_JSAPI uint32_t tsControlArea_getFontSize(const ControlArea &self) {
		return self.getFontSize();
	}
	TS_JSAPI bool tsControlArea_setFontStyle(ControlArea &self, const FontStyle &style) {
		return self.setFontStyle(style);
	}
	TS_JSAPI const FontStyle *tsControlArea_getFontStyleConst(const ControlArea &self) {
		return new FontStyle(self.getFontStyleConst());
	}
	TS_JSAPI const FontStyle *tsControlArea_getFontStyle(const ControlArea &self) {
		return new FontStyle(self.getFontStyle());
	}
	TS_JSAPI FontStyle *tsControlArea_getFontStyle_1(ControlArea &self) {
		return new FontStyle(self.getFontStyle());
	}
	TS_JSAPI void tsControlArea_setColumns(ControlArea &self, uint32_t columns) {
		self.setColumns(columns);
	}
	TS_JSAPI uint32_t tsControlArea_getColumns(const ControlArea &self) {
		return self.getColumns();
	}
	TS_JSAPI void tsControlArea_setSpacing(ControlArea &self, const Vector2f &spacing) {
		self.setSpacing(spacing);
	}
	TS_JSAPI void tsControlArea_setSpacing_1(ControlArea &self, float32_t x, float32_t y) {
		self.setSpacing(x, y);
	}
	TS_JSAPI const Vector2f *tsControlArea_getSpacing(const ControlArea &self) {
		return new Vector2f(self.getSpacing());
	}
	TS_JSAPI void tsControlArea_setColumnRatio(ControlArea &self, uint32_t index, float32_t ratio) {
		self.setColumnRatio(index, ratio);
	}
	TS_JSAPI float32_t tsControlArea_getColumnRatio(const ControlArea &self, uint32_t index) {
		return self.getColumnRatio(index);
	}
	TS_JSAPI void tsControlArea_setColumnSpacing(ControlArea &self, uint32_t index, float32_t spacing) {
		self.setColumnSpacing(index, spacing);
	}
	TS_JSAPI float32_t tsControlArea_getColumnSpacing(const ControlArea &self, uint32_t index) {
		return self.getColumnSpacing(index);
	}
	TS_JSAPI void tsControlArea_setRowSpacing(ControlArea &self, uint32_t index, float32_t spacing) {
		self.setRowSpacing(index, spacing);
	}
	TS_JSAPI float32_t tsControlArea_getRowSpacing(const ControlArea &self, uint32_t index) {
		return self.getRowSpacing(index);
	}
	TS_JSAPI const Vector2f *tsControlArea_getControlsSize(const ControlArea &self) {
		return new Vector2f(self.getControlsSize());
	}
	TS_JSAPI const Vector2f *tsControlArea_getControlsOffset(const ControlArea &self) {
		return new Vector2f(self.getControlsOffset());
	}
	TS_JSAPI const Rect *tsControlArea_getViewRect(const ControlArea &self) {
		return new Rect(self.getViewRect());
	}
	
	// Tellusim::ControlTree
	static void control_tree_changed_callback(ControlTree a0, uint32_t item, void *self) {
		EM_ASM({ tsControlTree.changed_callback($0, $1, $2); }, self, new ControlTree(a0), item);
	}
	static ControlTree::ChangedCallback make_control_tree_changed_callback(void *self) {
		auto ret = makeFunction(control_tree_changed_callback);
		ret.setArg2(self);
		return ret;
	}
	static bool control_tree_dragged_callback(ControlTree a0, uint32_t item, void *self) {
		return EM_ASM_INT({ return tsControlTree.dragged_callback($0, $1, $2); }, self, new ControlTree(a0), item) != 0;
	}
	static ControlTree::DraggedCallback make_control_tree_dragged_callback(void *self) {
		auto ret = makeFunction(control_tree_dragged_callback);
		ret.setArg2(self);
		return ret;
	}
	static void control_tree_dropped_callback(ControlTree a0, uint32_t item, void *self) {
		EM_ASM({ tsControlTree.dropped_callback($0, $1, $2); }, self, new ControlTree(a0), item);
	}
	static ControlTree::DroppedCallback make_control_tree_dropped_callback(void *self) {
		auto ret = makeFunction(control_tree_dropped_callback);
		ret.setArg2(self);
		return ret;
	}
	static void control_tree_clicked_callback(ControlTree a0, uint32_t item, void *self) {
		EM_ASM({ tsControlTree.clicked_callback($0, $1, $2); }, self, new ControlTree(a0), item);
	}
	static ControlTree::ClickedCallback make_control_tree_clicked_callback(void *self) {
		auto ret = makeFunction(control_tree_clicked_callback);
		ret.setArg2(self);
		return ret;
	}
	static void control_tree_expanded_callback(ControlTree a0, uint32_t item, void *self) {
		EM_ASM({ tsControlTree.expanded_callback($0, $1, $2); }, self, new ControlTree(a0), item);
	}
	static ControlTree::ExpandedCallback make_control_tree_expanded_callback(void *self) {
		auto ret = makeFunction(control_tree_expanded_callback);
		ret.setArg2(self);
		return ret;
	}
	static void control_tree_selected_callback(ControlTree a0, void *self) {
		EM_ASM({ tsControlTree.selected_callback($0, $1); }, self, new ControlTree(a0));
	}
	static ControlTree::SelectedCallback make_control_tree_selected_callback(void *self) {
		auto ret = makeFunction(control_tree_selected_callback);
		ret.setArg1(self);
		return ret;
	}
	TS_JSAPI ControlTree *tsControlTree_new() {
		return new ControlTree();
	}
	TS_JSAPI ControlTree *tsControlTree_new_1(Control *parent) {
		return new ControlTree(parent);
	}
	TS_JSAPI void tsControlTree_delete(ControlTree *self) {
		delete self;
	}
	TS_JSAPI bool tsControlTree_equalControlTextPtr(const ControlTree &self, const ControlText &base) {
		return self.operator==(base);
	}
	TS_JSAPI ControlTree *tsControlTree_castControlTextPtr(const ControlText &self) {
		return new ControlTree(self);
	}
	TS_JSAPI ControlText *tsControlTree_baseControlTextPtr(const ControlTree &self) {
		return new ControlText(self.getControlText());
	}
	TS_JSAPI void tsControlTree_setSelectable(ControlTree &self, bool selectable) {
		self.setSelectable(selectable);
	}
	TS_JSAPI bool tsControlTree_isSelectable(const ControlTree &self) {
		return self.isSelectable();
	}
	TS_JSAPI void tsControlTree_setMultiSelection(ControlTree &self, bool multi_selection) {
		self.setMultiSelection(multi_selection);
	}
	TS_JSAPI bool tsControlTree_isMultiSelection(const ControlTree &self) {
		return self.isMultiSelection();
	}
	TS_JSAPI void tsControlTree_setFoldedText(ControlTree &self, const char *text) {
		self.setFoldedText(text);
	}
	TS_JSAPI void tsControlTree_setFoldedText_1(ControlTree &self, const String &text) {
		self.setFoldedText(text);
	}
	TS_JSAPI String *tsControlTree_getFoldedText(const ControlTree &self) {
		return new String(self.getFoldedText());
	}
	TS_JSAPI void tsControlTree_setExpandedText(ControlTree &self, const char *text) {
		self.setExpandedText(text);
	}
	TS_JSAPI void tsControlTree_setExpandedText_1(ControlTree &self, const String &text) {
		self.setExpandedText(text);
	}
	TS_JSAPI String *tsControlTree_getExpandedText(const ControlTree &self) {
		return new String(self.getExpandedText());
	}
	TS_JSAPI void tsControlTree_setTexture(ControlTree &self, Texture &texture, uint32_t rows, uint32_t columns) {
		self.setTexture(texture, rows, columns);
	}
	TS_JSAPI Texture *tsControlTree_getTexture(const ControlTree &self) {
		return new Texture(self.getTexture());
	}
	TS_JSAPI void tsControlTree_setTextureName(ControlTree &self, const char *name, uint32_t rows, uint32_t columns) {
		self.setTextureName(name, rows, columns);
	}
	TS_JSAPI void tsControlTree_setTextureName_1(ControlTree &self, const String &name, uint32_t rows, uint32_t columns) {
		self.setTextureName(name, rows, columns);
	}
	TS_JSAPI String *tsControlTree_getTextureName(const ControlTree &self) {
		return new String(self.getTextureName());
	}
	TS_JSAPI void tsControlTree_setTextureGrid(ControlTree &self, uint32_t rows, uint32_t columns) {
		self.setTextureGrid(rows, columns);
	}
	TS_JSAPI uint32_t tsControlTree_getTextureRows(const ControlTree &self) {
		return self.getTextureRows();
	}
	TS_JSAPI uint32_t tsControlTree_getTextureColumns(const ControlTree &self) {
		return self.getTextureColumns();
	}
	TS_JSAPI void tsControlTree_clearItems(ControlTree &self) {
		self.clearItems();
	}
	TS_JSAPI uint32_t tsControlTree_addItem(ControlTree &self, const char *text, uint32_t parent, bool expanded) {
		return self.addItem(text, parent, expanded);
	}
	TS_JSAPI uint32_t tsControlTree_addItem_1(ControlTree &self, const String &text, uint32_t parent, bool expanded) {
		return self.addItem(text, parent, expanded);
	}
	TS_JSAPI void tsControlTree_removeItem(ControlTree &self, uint32_t item, bool children) {
		self.removeItem(item, children);
	}
	TS_JSAPI void tsControlTree_viewItem(ControlTree &self, uint32_t item) {
		self.viewItem(item);
	}
	TS_JSAPI uint32_t tsControlTree_getNumItems(const ControlTree &self) {
		return self.getNumItems();
	}
	TS_JSAPI uint32_t tsControlTree_getItem(const ControlTree &self, uint32_t index) {
		return self.getItem(index);
	}
	TS_JSAPI bool tsControlTree_switchItemHidden(ControlTree &self, uint32_t item, bool children) {
		return self.switchItemHidden(item, children);
	}
	TS_JSAPI void tsControlTree_setItemHidden(ControlTree &self, uint32_t item, bool hidden, bool children) {
		self.setItemHidden(item, hidden, children);
	}
	TS_JSAPI bool tsControlTree_isItemHidden(const ControlTree &self, uint32_t item) {
		return self.isItemHidden(item);
	}
	TS_JSAPI bool tsControlTree_switchItemExpanded(ControlTree &self, uint32_t item, bool children) {
		return self.switchItemExpanded(item, children);
	}
	TS_JSAPI void tsControlTree_setItemExpanded(ControlTree &self, uint32_t item, bool expanded, bool children) {
		self.setItemExpanded(item, expanded, children);
	}
	TS_JSAPI bool tsControlTree_isItemExpanded(const ControlTree &self, uint32_t item) {
		return self.isItemExpanded(item);
	}
	TS_JSAPI bool tsControlTree_switchItemSelected(ControlTree &self, uint32_t item, bool children) {
		return self.switchItemSelected(item, children);
	}
	TS_JSAPI void tsControlTree_setItemSelected(ControlTree &self, uint32_t item, bool selected, bool children) {
		self.setItemSelected(item, selected, children);
	}
	TS_JSAPI bool tsControlTree_isItemSelected(const ControlTree &self, uint32_t item) {
		return self.isItemSelected(item);
	}
	TS_JSAPI void tsControlTree_setItemParent(ControlTree &self, uint32_t item, uint32_t parent) {
		self.setItemParent(item, parent);
	}
	TS_JSAPI uint32_t tsControlTree_getItemParent(const ControlTree &self, uint32_t item) {
		return self.getItemParent(item);
	}
	TS_JSAPI bool tsControlTree_isItemParent(const ControlTree &self, uint32_t item, uint32_t parent, bool hierarchy) {
		return self.isItemParent(item, parent, hierarchy);
	}
	TS_JSAPI void tsControlTree_addItemChild(ControlTree &self, uint32_t item, uint32_t child) {
		self.addItemChild(item, child);
	}
	TS_JSAPI void tsControlTree_removeItemChild(ControlTree &self, uint32_t item, uint32_t child) {
		self.removeItemChild(item, child);
	}
	TS_JSAPI void tsControlTree_addItemChildren(ControlTree &self, uint32_t item, Array<uint32_t> &children) {
		self.addItemChildren(item, children);
	}
	TS_JSAPI void tsControlTree_removeItemChildren(ControlTree &self, uint32_t item, Array<uint32_t> &children) {
		self.removeItemChildren(item, children);
	}
	TS_JSAPI uint32_t tsControlTree_findItemChild(const ControlTree &self, uint32_t item, uint32_t child) {
		return self.findItemChild(item, child);
	}
	TS_JSAPI bool tsControlTree_isItemChild(const ControlTree &self, uint32_t item, uint32_t child) {
		return self.isItemChild(item, child);
	}
	TS_JSAPI uint32_t tsControlTree_getNumItemChildren(const ControlTree &self, uint32_t item) {
		return self.getNumItemChildren(item);
	}
	TS_JSAPI uint32_t tsControlTree_getItemChild(const ControlTree &self, uint32_t item, uint32_t index) {
		return self.getItemChild(item, index);
	}
	TS_JSAPI void tsControlTree_setItemText(ControlTree &self, uint32_t item, const char *text) {
		self.setItemText(item, text);
	}
	TS_JSAPI void tsControlTree_setItemText_1(ControlTree &self, uint32_t item, const String &text) {
		self.setItemText(item, text);
	}
	TS_JSAPI String *tsControlTree_getItemText(const ControlTree &self, uint32_t item) {
		return new String(self.getItemText(item));
	}
	TS_JSAPI uint32_t tsControlTree_findItemText(const ControlTree &self, const char *text) {
		return self.findItemText(text);
	}
	TS_JSAPI uint32_t tsControlTree_findItemText_1(const ControlTree &self, const String &text) {
		return self.findItemText(text);
	}
	TS_JSAPI void tsControlTree_setItemColor(ControlTree &self, uint32_t item, const Color &color) {
		self.setItemColor(item, color);
	}
	TS_JSAPI const Color *tsControlTree_getItemColor(const ControlTree &self, uint32_t item) {
		return new Color(self.getItemColor(item));
	}
	TS_JSAPI void tsControlTree_setItemTexture(ControlTree &self, uint32_t item, uint32_t row, uint32_t column) {
		self.setItemTexture(item, row, column);
	}
	TS_JSAPI uint32_t tsControlTree_getItemTextureRow(const ControlTree &self, uint32_t item) {
		return self.getItemTextureRow(item);
	}
	TS_JSAPI uint32_t tsControlTree_getItemTextureColumn(const ControlTree &self, uint32_t item) {
		return self.getItemTextureColumn(item);
	}
	TS_JSAPI void tsControlTree_setItemData(ControlTree &self, uint32_t item, void *data) {
		self.setItemData(item, data);
	}
	TS_JSAPI void* tsControlTree_getItemData(const ControlTree &self, uint32_t item) {
		return self.getItemData(item);
	}
	TS_JSAPI uint32_t tsControlTree_getFocusedItem(const ControlTree &self) {
		return self.getFocusedItem();
	}
	TS_JSAPI void tsControlTree_setCurrentItem(ControlTree &self, uint32_t item, bool select, bool view, bool callback) {
		self.setCurrentItem(item, select, view, callback);
	}
	TS_JSAPI uint32_t tsControlTree_getCurrentItem(const ControlTree &self) {
		return self.getCurrentItem();
	}
	TS_JSAPI String *tsControlTree_getCurrentText(const ControlTree &self) {
		return new String(self.getCurrentText());
	}
	TS_JSAPI void tsControlTree_setSelection(ControlTree &self) {
		self.setSelection();
	}
	TS_JSAPI void tsControlTree_clearSelection(ControlTree &self) {
		self.clearSelection();
	}
	TS_JSAPI void tsControlTree_inverseSelection(ControlTree &self) {
		self.inverseSelection();
	}
	TS_JSAPI uint32_t tsControlTree_getNumSelectedItems(const ControlTree &self) {
		return self.getNumSelectedItems();
	}
	TS_JSAPI uint32_t tsControlTree_getSelectedItem(const ControlTree &self, uint32_t index) {
		return self.getSelectedItem(index);
	}
	TS_JSAPI void tsControlTree_setChangedCallback(ControlTree &self, bool func) {
		self.setChangedCallback((func) ? make_control_tree_changed_callback(&self) : ControlTree::ChangedCallback());
	}
	TS_JSAPI void tsControlTree_setDraggedCallback(ControlTree &self, bool func) {
		self.setDraggedCallback((func) ? make_control_tree_dragged_callback(&self) : ControlTree::DraggedCallback());
	}
	TS_JSAPI void tsControlTree_setDroppedCallback(ControlTree &self, bool func) {
		self.setDroppedCallback((func) ? make_control_tree_dropped_callback(&self) : ControlTree::DroppedCallback());
	}
	TS_JSAPI void tsControlTree_setClickedCallback(ControlTree &self, bool func) {
		self.setClickedCallback((func) ? make_control_tree_clicked_callback(&self) : ControlTree::ClickedCallback());
	}
	TS_JSAPI void tsControlTree_setClicked2Callback(ControlTree &self, bool func) {
		self.setClicked2Callback((func) ? make_control_tree_clicked_callback(&self) : ControlTree::ClickedCallback());
	}
	TS_JSAPI void tsControlTree_setClickedRightCallback(ControlTree &self, bool func) {
		self.setClickedRightCallback((func) ? make_control_tree_clicked_callback(&self) : ControlTree::ClickedCallback());
	}
	TS_JSAPI void tsControlTree_setExpandedCallback(ControlTree &self, bool func) {
		self.setExpandedCallback((func) ? make_control_tree_expanded_callback(&self) : ControlTree::ExpandedCallback());
	}
	TS_JSAPI void tsControlTree_setSelectedCallback(ControlTree &self, bool func) {
		self.setSelectedCallback((func) ? make_control_tree_selected_callback(&self) : ControlTree::SelectedCallback());
	}
	
	// Tellusim::ControlEdit
	static void control_edit_clicked_callback(ControlEdit a0, void *self) {
		EM_ASM({ tsControlEdit.clicked_callback($0, $1); }, self, new ControlEdit(a0));
	}
	static ControlEdit::ClickedCallback make_control_edit_clicked_callback(void *self) {
		auto ret = makeFunction(control_edit_clicked_callback);
		ret.setArg1(self);
		return ret;
	}
	static void control_edit_changed_callback(ControlEdit a0, void *self) {
		EM_ASM({ tsControlEdit.changed_callback($0, $1); }, self, new ControlEdit(a0));
	}
	static ControlEdit::ChangedCallback make_control_edit_changed_callback(void *self) {
		auto ret = makeFunction(control_edit_changed_callback);
		ret.setArg1(self);
		return ret;
	}
	static void control_edit_returned_callback(ControlEdit a0, void *self) {
		EM_ASM({ tsControlEdit.returned_callback($0, $1); }, self, new ControlEdit(a0));
	}
	static ControlEdit::ReturnedCallback make_control_edit_returned_callback(void *self) {
		auto ret = makeFunction(control_edit_returned_callback);
		ret.setArg1(self);
		return ret;
	}
	TS_JSAPI ControlEdit *tsControlEdit_new() {
		return new ControlEdit();
	}
	TS_JSAPI ControlEdit *tsControlEdit_new_1(Control *parent) {
		return new ControlEdit(parent);
	}
	TS_JSAPI ControlEdit *tsControlEdit_new_2(Control *parent, const char *text) {
		return new ControlEdit(parent, text);
	}
	TS_JSAPI ControlEdit *tsControlEdit_new_3(Control *parent, const String &text) {
		return new ControlEdit(parent, text);
	}
	TS_JSAPI void tsControlEdit_delete(ControlEdit *self) {
		delete self;
	}
	TS_JSAPI bool tsControlEdit_equalControlTextPtr(const ControlEdit &self, const ControlText &base) {
		return self.operator==(base);
	}
	TS_JSAPI ControlEdit *tsControlEdit_castControlTextPtr(const ControlText &self) {
		return new ControlEdit(self);
	}
	TS_JSAPI ControlText *tsControlEdit_baseControlTextPtr(const ControlEdit &self) {
		return new ControlText(self.getControlText());
	}
	TS_JSAPI void tsControlEdit_setFrame(ControlEdit &self, bool frame) {
		self.setFrame(frame);
	}
	TS_JSAPI bool tsControlEdit_getFrame(const ControlEdit &self) {
		return self.getFrame();
	}
	TS_JSAPI void tsControlEdit_setBackground(ControlEdit &self, bool background) {
		self.setBackground(background);
	}
	TS_JSAPI bool tsControlEdit_getBackground(const ControlEdit &self) {
		return self.getBackground();
	}
	TS_JSAPI void tsControlEdit_setEditColor(ControlEdit &self, const Color &color) {
		self.setEditColor(color);
	}
	TS_JSAPI const Color *tsControlEdit_getEditColor(const ControlEdit &self) {
		return new Color(self.getEditColor());
	}
	TS_JSAPI void tsControlEdit_setEditMode(ControlEdit &self, uint32_t mode) {
		self.setEditMode((ControlEdit::EditMode)mode);
	}
	TS_JSAPI uint32_t tsControlEdit_getEditMode(const ControlEdit &self) {
		return self.getEditMode();
	}
	TS_JSAPI void tsControlEdit_setPasswordCode(ControlEdit &self, uint32_t code) {
		self.setPasswordCode(code);
	}
	TS_JSAPI uint32_t tsControlEdit_getPasswordCode(const ControlEdit &self) {
		return self.getPasswordCode();
	}
	TS_JSAPI uint32_t tsControlEdit_getNumCodes(const ControlEdit &self) {
		return self.getNumCodes();
	}
	TS_JSAPI const uint32_t* tsControlEdit_getCodes(const ControlEdit &self) {
		return self.getCodes();
	}
	TS_JSAPI void tsControlEdit_setCurrentIndex(ControlEdit &self, uint32_t index, uint32_t selection_index) {
		self.setCurrentIndex(index, selection_index);
	}
	TS_JSAPI uint32_t tsControlEdit_getCurrentIndex(const ControlEdit &self) {
		return self.getCurrentIndex();
	}
	TS_JSAPI uint32_t tsControlEdit_getSelectionIndex(const ControlEdit &self) {
		return self.getSelectionIndex();
	}
	TS_JSAPI void tsControlEdit_setSelection(ControlEdit &self, bool current, bool changed) {
		self.setSelection(current, changed);
	}
	TS_JSAPI void tsControlEdit_clearSelection(ControlEdit &self) {
		self.clearSelection();
	}
	TS_JSAPI String *tsControlEdit_getSelectedText(const ControlEdit &self) {
		return new String(self.getSelectedText());
	}
	TS_JSAPI bool tsControlEdit_updateKeyboard(ControlEdit &self, ControlRoot &root, uint32_t key, uint32_t code) {
		return self.updateKeyboard(root, key, code);
	}
	TS_JSAPI void tsControlEdit_setClickedCallback(ControlEdit &self, bool func) {
		self.setClickedCallback((func) ? make_control_edit_clicked_callback(&self) : ControlEdit::ClickedCallback());
	}
	TS_JSAPI bool tsControlEdit_isClicked(ControlEdit &self) {
		return self.isClicked();
	}
	TS_JSAPI void tsControlEdit_setChangedCallback(ControlEdit &self, bool func) {
		self.setChangedCallback((func) ? make_control_edit_changed_callback(&self) : ControlEdit::ChangedCallback());
	}
	TS_JSAPI bool tsControlEdit_isChanged(ControlEdit &self) {
		return self.isChanged();
	}
	TS_JSAPI void tsControlEdit_setReturnedCallback(ControlEdit &self, bool func) {
		self.setReturnedCallback((func) ? make_control_edit_returned_callback(&self) : ControlEdit::ReturnedCallback());
	}
	TS_JSAPI bool tsControlEdit_isReturned(ControlEdit &self) {
		return self.isReturned();
	}
	TS_JSAPI CanvasMesh *tsControlEdit_getCanvasMesh(ControlEdit &self) {
		return new CanvasMesh(self.getCanvasMesh());
	}
	
	// Tellusim::DialogMessage
	static bool dialog_message_update_callback(void *self) {
		return EM_ASM_INT({ return tsDialogMessage.update_callback($0); }, self) != 0;
	}
	static DialogMessage::UpdateCallback make_dialog_message_update_callback(void *self) {
		auto ret = makeFunction(dialog_message_update_callback);
		ret.setArg0(self);
		return ret;
	}
	TS_JSAPI DialogMessage *tsDialogMessage_new(const char *title, const char *message) {
		return new DialogMessage(title, message);
	}
	TS_JSAPI DialogMessage *tsDialogMessage_new_1(const String &title, const char *message) {
		return new DialogMessage(title, message);
	}
	TS_JSAPI DialogMessage *tsDialogMessage_new_2(const char *title, const String &message) {
		return new DialogMessage(title, message);
	}
	TS_JSAPI DialogMessage *tsDialogMessage_new_3(const String &title, const String &message) {
		return new DialogMessage(title, message);
	}
	TS_JSAPI void tsDialogMessage_delete(DialogMessage *self) {
		delete self;
	}
	TS_JSAPI bool tsDialogMessage_equalPtr(const DialogMessage &self, const DialogMessage &ptr) {
		return (self == ptr);
	}
	TS_JSAPI DialogMessage *tsDialogMessage_clonePtr(const DialogMessage &self) {
		return new DialogMessage(self.clonePtr());
	}
	TS_JSAPI void tsDialogMessage_clearPtr(DialogMessage &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsDialogMessage_destroyPtr(DialogMessage &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsDialogMessage_acquirePtr(DialogMessage &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsDialogMessage_unacquirePtr(DialogMessage &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsDialogMessage_isValidPtr(const DialogMessage &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsDialogMessage_isOwnerPtr(const DialogMessage &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsDialogMessage_isConstPtr(const DialogMessage &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsDialogMessage_getCountPtr(const DialogMessage &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsDialogMessage_getInternalPtr(const DialogMessage &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsDialogMessage_setPosition(DialogMessage &self, int32_t x, int32_t y) {
		self.setPosition(x, y);
	}
	TS_JSAPI int32_t tsDialogMessage_getPositionX(const DialogMessage &self) {
		return self.getPositionX();
	}
	TS_JSAPI int32_t tsDialogMessage_getPositionY(const DialogMessage &self) {
		return self.getPositionY();
	}
	TS_JSAPI void tsDialogMessage_setTitle(DialogMessage &self, const char *title) {
		self.setTitle(title);
	}
	TS_JSAPI void tsDialogMessage_setTitle_1(DialogMessage &self, const String &title) {
		self.setTitle(title);
	}
	TS_JSAPI String *tsDialogMessage_getTitle(const DialogMessage &self) {
		return new String(self.getTitle());
	}
	TS_JSAPI void tsDialogMessage_setMessage(DialogMessage &self, const char *message) {
		self.setMessage(message);
	}
	TS_JSAPI void tsDialogMessage_setMessage_1(DialogMessage &self, const String &message) {
		self.setMessage(message);
	}
	TS_JSAPI String *tsDialogMessage_getMessage(const DialogMessage &self) {
		return new String(self.getMessage());
	}
	TS_JSAPI void tsDialogMessage_setUpdateCallback(DialogMessage &self, bool func) {
		self.setUpdateCallback((func) ? make_dialog_message_update_callback(&self) : DialogMessage::UpdateCallback());
	}
	TS_JSAPI uint32_t tsDialogMessage_run(DialogMessage &self, uint32_t flags) {
		return self.run((DialogMessage::Flags)flags);
	}
	
	// Tellusim::DialogFileOpen
	static bool dialog_file_open_update_callback(void *self) {
		return EM_ASM_INT({ return tsDialogFileOpen.update_callback($0); }, self) != 0;
	}
	static DialogFileOpen::UpdateCallback make_dialog_file_open_update_callback(void *self) {
		auto ret = makeFunction(dialog_file_open_update_callback);
		ret.setArg0(self);
		return ret;
	}
	TS_JSAPI DialogFileOpen *tsDialogFileOpen_new(const char *title, const char *name) {
		return new DialogFileOpen(title, name);
	}
	TS_JSAPI DialogFileOpen *tsDialogFileOpen_new_1(const String &title, const char *name) {
		return new DialogFileOpen(title, name);
	}
	TS_JSAPI DialogFileOpen *tsDialogFileOpen_new_2(const char *title, const String &name) {
		return new DialogFileOpen(title, name);
	}
	TS_JSAPI DialogFileOpen *tsDialogFileOpen_new_3(const String &title, const String &name) {
		return new DialogFileOpen(title, name);
	}
	TS_JSAPI void tsDialogFileOpen_delete(DialogFileOpen *self) {
		delete self;
	}
	TS_JSAPI bool tsDialogFileOpen_equalPtr(const DialogFileOpen &self, const DialogFileOpen &ptr) {
		return (self == ptr);
	}
	TS_JSAPI DialogFileOpen *tsDialogFileOpen_clonePtr(const DialogFileOpen &self) {
		return new DialogFileOpen(self.clonePtr());
	}
	TS_JSAPI void tsDialogFileOpen_clearPtr(DialogFileOpen &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsDialogFileOpen_destroyPtr(DialogFileOpen &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsDialogFileOpen_acquirePtr(DialogFileOpen &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsDialogFileOpen_unacquirePtr(DialogFileOpen &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsDialogFileOpen_isValidPtr(const DialogFileOpen &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsDialogFileOpen_isOwnerPtr(const DialogFileOpen &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsDialogFileOpen_isConstPtr(const DialogFileOpen &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsDialogFileOpen_getCountPtr(const DialogFileOpen &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsDialogFileOpen_getInternalPtr(const DialogFileOpen &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsDialogFileOpen_setPosition(DialogFileOpen &self, int32_t x, int32_t y) {
		self.setPosition(x, y);
	}
	TS_JSAPI int32_t tsDialogFileOpen_getPositionX(const DialogFileOpen &self) {
		return self.getPositionX();
	}
	TS_JSAPI int32_t tsDialogFileOpen_getPositionY(const DialogFileOpen &self) {
		return self.getPositionY();
	}
	TS_JSAPI void tsDialogFileOpen_setTitle(DialogFileOpen &self, const char *title) {
		self.setTitle(title);
	}
	TS_JSAPI void tsDialogFileOpen_setTitle_1(DialogFileOpen &self, const String &title) {
		self.setTitle(title);
	}
	TS_JSAPI String *tsDialogFileOpen_getTitle(const DialogFileOpen &self) {
		return new String(self.getTitle());
	}
	TS_JSAPI void tsDialogFileOpen_setFilter(DialogFileOpen &self, const char *filter) {
		self.setFilter(filter);
	}
	TS_JSAPI void tsDialogFileOpen_setFilter_1(DialogFileOpen &self, const String &filter) {
		self.setFilter(filter);
	}
	TS_JSAPI String *tsDialogFileOpen_getFilter(const DialogFileOpen &self) {
		return new String(self.getFilter());
	}
	TS_JSAPI void tsDialogFileOpen_setFile(DialogFileOpen &self, const char *name) {
		self.setFile(name);
	}
	TS_JSAPI void tsDialogFileOpen_setFile_1(DialogFileOpen &self, const String &name) {
		self.setFile(name);
	}
	TS_JSAPI String *tsDialogFileOpen_getFile(const DialogFileOpen &self) {
		return new String(self.getFile());
	}
	TS_JSAPI void tsDialogFileOpen_setUpdateCallback(DialogFileOpen &self, bool func) {
		self.setUpdateCallback((func) ? make_dialog_file_open_update_callback(&self) : DialogFileOpen::UpdateCallback());
	}
	TS_JSAPI uint32_t tsDialogFileOpen_run(DialogFileOpen &self, uint32_t flags) {
		return self.run((DialogFileOpen::Flags)flags);
	}
	
	// Tellusim::DialogFileSave
	static bool dialog_file_save_update_callback(void *self) {
		return EM_ASM_INT({ return tsDialogFileSave.update_callback($0); }, self) != 0;
	}
	static DialogFileSave::UpdateCallback make_dialog_file_save_update_callback(void *self) {
		auto ret = makeFunction(dialog_file_save_update_callback);
		ret.setArg0(self);
		return ret;
	}
	TS_JSAPI DialogFileSave *tsDialogFileSave_new(const char *title, const char *name) {
		return new DialogFileSave(title, name);
	}
	TS_JSAPI DialogFileSave *tsDialogFileSave_new_1(const String &title, const char *name) {
		return new DialogFileSave(title, name);
	}
	TS_JSAPI DialogFileSave *tsDialogFileSave_new_2(const char *title, const String &name) {
		return new DialogFileSave(title, name);
	}
	TS_JSAPI DialogFileSave *tsDialogFileSave_new_3(const String &title, const String &name) {
		return new DialogFileSave(title, name);
	}
	TS_JSAPI void tsDialogFileSave_delete(DialogFileSave *self) {
		delete self;
	}
	TS_JSAPI bool tsDialogFileSave_equalPtr(const DialogFileSave &self, const DialogFileSave &ptr) {
		return (self == ptr);
	}
	TS_JSAPI DialogFileSave *tsDialogFileSave_clonePtr(const DialogFileSave &self) {
		return new DialogFileSave(self.clonePtr());
	}
	TS_JSAPI void tsDialogFileSave_clearPtr(DialogFileSave &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsDialogFileSave_destroyPtr(DialogFileSave &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsDialogFileSave_acquirePtr(DialogFileSave &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsDialogFileSave_unacquirePtr(DialogFileSave &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsDialogFileSave_isValidPtr(const DialogFileSave &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsDialogFileSave_isOwnerPtr(const DialogFileSave &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsDialogFileSave_isConstPtr(const DialogFileSave &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsDialogFileSave_getCountPtr(const DialogFileSave &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsDialogFileSave_getInternalPtr(const DialogFileSave &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsDialogFileSave_setPosition(DialogFileSave &self, int32_t x, int32_t y) {
		self.setPosition(x, y);
	}
	TS_JSAPI int32_t tsDialogFileSave_getPositionX(const DialogFileSave &self) {
		return self.getPositionX();
	}
	TS_JSAPI int32_t tsDialogFileSave_getPositionY(const DialogFileSave &self) {
		return self.getPositionY();
	}
	TS_JSAPI void tsDialogFileSave_setTitle(DialogFileSave &self, const char *title) {
		self.setTitle(title);
	}
	TS_JSAPI void tsDialogFileSave_setTitle_1(DialogFileSave &self, const String &title) {
		self.setTitle(title);
	}
	TS_JSAPI String *tsDialogFileSave_getTitle(const DialogFileSave &self) {
		return new String(self.getTitle());
	}
	TS_JSAPI void tsDialogFileSave_setFilter(DialogFileSave &self, const char *filter) {
		self.setFilter(filter);
	}
	TS_JSAPI void tsDialogFileSave_setFilter_1(DialogFileSave &self, const String &filter) {
		self.setFilter(filter);
	}
	TS_JSAPI String *tsDialogFileSave_getFilter(const DialogFileSave &self) {
		return new String(self.getFilter());
	}
	TS_JSAPI void tsDialogFileSave_setFile(DialogFileSave &self, const char *name) {
		self.setFile(name);
	}
	TS_JSAPI void tsDialogFileSave_setFile_1(DialogFileSave &self, const String &name) {
		self.setFile(name);
	}
	TS_JSAPI String *tsDialogFileSave_getFile(const DialogFileSave &self) {
		return new String(self.getFile());
	}
	TS_JSAPI void tsDialogFileSave_setUpdateCallback(DialogFileSave &self, bool func) {
		self.setUpdateCallback((func) ? make_dialog_file_save_update_callback(&self) : DialogFileSave::UpdateCallback());
	}
	TS_JSAPI uint32_t tsDialogFileSave_run(DialogFileSave &self, uint32_t flags) {
		return self.run((DialogFileSave::Flags)flags);
	}
	
	// Tellusim::DialogDirectory
	static bool dialog_directory_update_callback(void *self) {
		return EM_ASM_INT({ return tsDialogDirectory.update_callback($0); }, self) != 0;
	}
	static DialogDirectory::UpdateCallback make_dialog_directory_update_callback(void *self) {
		auto ret = makeFunction(dialog_directory_update_callback);
		ret.setArg0(self);
		return ret;
	}
	TS_JSAPI DialogDirectory *tsDialogDirectory_new(const char *title, const char *name) {
		return new DialogDirectory(title, name);
	}
	TS_JSAPI DialogDirectory *tsDialogDirectory_new_1(const String &title, const char *name) {
		return new DialogDirectory(title, name);
	}
	TS_JSAPI DialogDirectory *tsDialogDirectory_new_2(const char *title, const String &name) {
		return new DialogDirectory(title, name);
	}
	TS_JSAPI DialogDirectory *tsDialogDirectory_new_3(const String &title, const String &name) {
		return new DialogDirectory(title, name);
	}
	TS_JSAPI void tsDialogDirectory_delete(DialogDirectory *self) {
		delete self;
	}
	TS_JSAPI bool tsDialogDirectory_equalPtr(const DialogDirectory &self, const DialogDirectory &ptr) {
		return (self == ptr);
	}
	TS_JSAPI DialogDirectory *tsDialogDirectory_clonePtr(const DialogDirectory &self) {
		return new DialogDirectory(self.clonePtr());
	}
	TS_JSAPI void tsDialogDirectory_clearPtr(DialogDirectory &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsDialogDirectory_destroyPtr(DialogDirectory &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsDialogDirectory_acquirePtr(DialogDirectory &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsDialogDirectory_unacquirePtr(DialogDirectory &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsDialogDirectory_isValidPtr(const DialogDirectory &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsDialogDirectory_isOwnerPtr(const DialogDirectory &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsDialogDirectory_isConstPtr(const DialogDirectory &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsDialogDirectory_getCountPtr(const DialogDirectory &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsDialogDirectory_getInternalPtr(const DialogDirectory &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsDialogDirectory_setPosition(DialogDirectory &self, int32_t x, int32_t y) {
		self.setPosition(x, y);
	}
	TS_JSAPI int32_t tsDialogDirectory_getPositionX(const DialogDirectory &self) {
		return self.getPositionX();
	}
	TS_JSAPI int32_t tsDialogDirectory_getPositionY(const DialogDirectory &self) {
		return self.getPositionY();
	}
	TS_JSAPI void tsDialogDirectory_setTitle(DialogDirectory &self, const char *title) {
		self.setTitle(title);
	}
	TS_JSAPI void tsDialogDirectory_setTitle_1(DialogDirectory &self, const String &title) {
		self.setTitle(title);
	}
	TS_JSAPI String *tsDialogDirectory_getTitle(const DialogDirectory &self) {
		return new String(self.getTitle());
	}
	TS_JSAPI void tsDialogDirectory_setDirectory(DialogDirectory &self, const char *name) {
		self.setDirectory(name);
	}
	TS_JSAPI void tsDialogDirectory_setDirectory_1(DialogDirectory &self, const String &name) {
		self.setDirectory(name);
	}
	TS_JSAPI String *tsDialogDirectory_getDirectory(const DialogDirectory &self) {
		return new String(self.getDirectory());
	}
	TS_JSAPI void tsDialogDirectory_setUpdateCallback(DialogDirectory &self, bool func) {
		self.setUpdateCallback((func) ? make_dialog_directory_update_callback(&self) : DialogDirectory::UpdateCallback());
	}
	TS_JSAPI uint32_t tsDialogDirectory_run(DialogDirectory &self, uint32_t flags) {
		return self.run((DialogDirectory::Flags)flags);
	}
	
	// Tellusim::DialogProgress
	TS_JSAPI DialogProgress *tsDialogProgress_new(const char *title, const char *message) {
		return new DialogProgress(title, message);
	}
	TS_JSAPI DialogProgress *tsDialogProgress_new_1(const String &title, const char *message) {
		return new DialogProgress(title, message);
	}
	TS_JSAPI DialogProgress *tsDialogProgress_new_2(const char *title, const String &message) {
		return new DialogProgress(title, message);
	}
	TS_JSAPI DialogProgress *tsDialogProgress_new_3(const String &title, const String &message) {
		return new DialogProgress(title, message);
	}
	TS_JSAPI void tsDialogProgress_delete(DialogProgress *self) {
		delete self;
	}
	TS_JSAPI bool tsDialogProgress_equalPtr(const DialogProgress &self, const DialogProgress &ptr) {
		return (self == ptr);
	}
	TS_JSAPI DialogProgress *tsDialogProgress_clonePtr(const DialogProgress &self) {
		return new DialogProgress(self.clonePtr());
	}
	TS_JSAPI void tsDialogProgress_clearPtr(DialogProgress &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsDialogProgress_destroyPtr(DialogProgress &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsDialogProgress_acquirePtr(DialogProgress &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsDialogProgress_unacquirePtr(DialogProgress &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsDialogProgress_isValidPtr(const DialogProgress &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsDialogProgress_isOwnerPtr(const DialogProgress &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsDialogProgress_isConstPtr(const DialogProgress &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsDialogProgress_getCountPtr(const DialogProgress &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsDialogProgress_getInternalPtr(const DialogProgress &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsDialogProgress_setPosition(DialogProgress &self, int32_t x, int32_t y) {
		self.setPosition(x, y);
	}
	TS_JSAPI int32_t tsDialogProgress_getPositionX(const DialogProgress &self) {
		return self.getPositionX();
	}
	TS_JSAPI int32_t tsDialogProgress_getPositionY(const DialogProgress &self) {
		return self.getPositionY();
	}
	TS_JSAPI void tsDialogProgress_setTitle(DialogProgress &self, const char *title) {
		self.setTitle(title);
	}
	TS_JSAPI void tsDialogProgress_setTitle_1(DialogProgress &self, const String &title) {
		self.setTitle(title);
	}
	TS_JSAPI String *tsDialogProgress_getTitle(const DialogProgress &self) {
		return new String(self.getTitle());
	}
	TS_JSAPI void tsDialogProgress_setMessage(DialogProgress &self, const char *message) {
		self.setMessage(message);
	}
	TS_JSAPI void tsDialogProgress_setMessage_1(DialogProgress &self, const String &message) {
		self.setMessage(message);
	}
	TS_JSAPI String *tsDialogProgress_getMessage(const DialogProgress &self) {
		return new String(self.getMessage());
	}
	TS_JSAPI void tsDialogProgress_setProgress(DialogProgress &self, uint32_t progress) {
		self.setProgress(progress);
	}
	TS_JSAPI uint32_t tsDialogProgress_getProgress(const DialogProgress &self) {
		return self.getProgress();
	}
	TS_JSAPI uint32_t tsDialogProgress_run(DialogProgress &self, uint32_t flags) {
		return self.run((DialogProgress::Flags)flags);
	}
	TS_JSAPI void tsDialogProgress_close(DialogProgress &self) {
		self.close();
	}
	
	// Tellusim::DialogColor
	static void dialog_color_changed_callback(Color a0, void *self) {
		EM_ASM({ tsDialogColor.changed_callback($0, $1); }, self, new Color(a0));
	}
	static DialogColor::ChangedCallback make_dialog_color_changed_callback(void *self) {
		auto ret = makeFunction(dialog_color_changed_callback);
		ret.setArg1(self);
		return ret;
	}
	static bool dialog_color_update_callback(void *self) {
		return EM_ASM_INT({ return tsDialogColor.update_callback($0); }, self) != 0;
	}
	static DialogColor::UpdateCallback make_dialog_color_update_callback(void *self) {
		auto ret = makeFunction(dialog_color_update_callback);
		ret.setArg0(self);
		return ret;
	}
	TS_JSAPI DialogColor *tsDialogColor_new(const char *title, const Color &color) {
		return new DialogColor(title, color);
	}
	TS_JSAPI DialogColor *tsDialogColor_new_1(const String &title, const Color &color) {
		return new DialogColor(title, color);
	}
	TS_JSAPI void tsDialogColor_delete(DialogColor *self) {
		delete self;
	}
	TS_JSAPI bool tsDialogColor_equalPtr(const DialogColor &self, const DialogColor &ptr) {
		return (self == ptr);
	}
	TS_JSAPI DialogColor *tsDialogColor_clonePtr(const DialogColor &self) {
		return new DialogColor(self.clonePtr());
	}
	TS_JSAPI void tsDialogColor_clearPtr(DialogColor &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsDialogColor_destroyPtr(DialogColor &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsDialogColor_acquirePtr(DialogColor &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsDialogColor_unacquirePtr(DialogColor &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsDialogColor_isValidPtr(const DialogColor &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsDialogColor_isOwnerPtr(const DialogColor &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsDialogColor_isConstPtr(const DialogColor &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsDialogColor_getCountPtr(const DialogColor &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsDialogColor_getInternalPtr(const DialogColor &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsDialogColor_setPosition(DialogColor &self, int32_t x, int32_t y) {
		self.setPosition(x, y);
	}
	TS_JSAPI int32_t tsDialogColor_getPositionX(const DialogColor &self) {
		return self.getPositionX();
	}
	TS_JSAPI int32_t tsDialogColor_getPositionY(const DialogColor &self) {
		return self.getPositionY();
	}
	TS_JSAPI void tsDialogColor_setTitle(DialogColor &self, const char *title) {
		self.setTitle(title);
	}
	TS_JSAPI void tsDialogColor_setTitle_1(DialogColor &self, const String &title) {
		self.setTitle(title);
	}
	TS_JSAPI String *tsDialogColor_getTitle(const DialogColor &self) {
		return new String(self.getTitle());
	}
	TS_JSAPI void tsDialogColor_setColor(DialogColor &self, const Color &color, bool callback) {
		self.setColor(color, callback);
	}
	TS_JSAPI const Color *tsDialogColor_getColor(const DialogColor &self) {
		return new Color(self.getColor());
	}
	TS_JSAPI void tsDialogColor_setChangedCallback(DialogColor &self, bool func) {
		self.setChangedCallback((func) ? make_dialog_color_changed_callback(&self) : DialogColor::ChangedCallback());
	}
	TS_JSAPI void tsDialogColor_setUpdateCallback(DialogColor &self, bool func) {
		self.setUpdateCallback((func) ? make_dialog_color_update_callback(&self) : DialogColor::UpdateCallback());
	}
	TS_JSAPI uint32_t tsDialogColor_run(DialogColor &self, uint32_t flags) {
		return self.run((DialogColor::Flags)flags);
	}
	
	// Tellusim::DialogMenu
	static void dialog_menu_clicked_callback(void *self) {
		EM_ASM({ tsDialogMenu.clicked_callback($0); }, self);
	}
	static DialogMenu::ClickedCallback make_dialog_menu_clicked_callback(void *self) {
		auto ret = makeFunction(dialog_menu_clicked_callback);
		ret.setArg0(self);
		return ret;
	}
	static void dialog_menu_changed_callback(bool a0, void *self) {
		EM_ASM({ tsDialogMenu.changed_callback($0, $1); }, self, a0);
	}
	static DialogMenu::ChangedCallback make_dialog_menu_changed_callback(void *self) {
		auto ret = makeFunction(dialog_menu_changed_callback);
		ret.setArg1(self);
		return ret;
	}
	static bool dialog_menu_update_callback(void *self) {
		return EM_ASM_INT({ return tsDialogMenu.update_callback($0); }, self) != 0;
	}
	static DialogMenu::UpdateCallback make_dialog_menu_update_callback(void *self) {
		auto ret = makeFunction(dialog_menu_update_callback);
		ret.setArg0(self);
		return ret;
	}
	TS_JSAPI DialogMenu *tsDialogMenu_new() {
		return new DialogMenu();
	}
	TS_JSAPI void tsDialogMenu_delete(DialogMenu *self) {
		delete self;
	}
	TS_JSAPI bool tsDialogMenu_equalPtr(const DialogMenu &self, const DialogMenu &ptr) {
		return (self == ptr);
	}
	TS_JSAPI DialogMenu *tsDialogMenu_clonePtr(const DialogMenu &self) {
		return new DialogMenu(self.clonePtr());
	}
	TS_JSAPI void tsDialogMenu_clearPtr(DialogMenu &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsDialogMenu_destroyPtr(DialogMenu &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsDialogMenu_acquirePtr(DialogMenu &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsDialogMenu_unacquirePtr(DialogMenu &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsDialogMenu_isValidPtr(const DialogMenu &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsDialogMenu_isOwnerPtr(const DialogMenu &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsDialogMenu_isConstPtr(const DialogMenu &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsDialogMenu_getCountPtr(const DialogMenu &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsDialogMenu_getInternalPtr(const DialogMenu &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsDialogMenu_setPosition(DialogMenu &self, int32_t x, int32_t y) {
		self.setPosition(x, y);
	}
	TS_JSAPI int32_t tsDialogMenu_getPositionX(const DialogMenu &self) {
		return self.getPositionX();
	}
	TS_JSAPI int32_t tsDialogMenu_getPositionY(const DialogMenu &self) {
		return self.getPositionY();
	}
	TS_JSAPI uint32_t tsDialogMenu_getNumItems(const DialogMenu &self) {
		return self.getNumItems();
	}
	TS_JSAPI void tsDialogMenu_setItemText(DialogMenu &self, uint32_t index, const char *text) {
		self.setItemText(index, text);
	}
	TS_JSAPI void tsDialogMenu_setItemText_1(DialogMenu &self, uint32_t index, const String &text) {
		self.setItemText(index, text);
	}
	TS_JSAPI String *tsDialogMenu_getItemText(const DialogMenu &self, uint32_t index) {
		return new String(self.getItemText(index));
	}
	TS_JSAPI void tsDialogMenu_setItemKey(DialogMenu &self, uint32_t index, const char *key) {
		self.setItemKey(index, key);
	}
	TS_JSAPI String *tsDialogMenu_getItemKey(const DialogMenu &self, uint32_t index) {
		return new String(self.getItemKey(index));
	}
	TS_JSAPI void tsDialogMenu_setItemImage(DialogMenu &self, uint32_t index, const Image &image) {
		self.setItemImage(index, image);
	}
	TS_JSAPI Image *tsDialogMenu_getItemImage(const DialogMenu &self, uint32_t index) {
		return new Image(self.getItemImage(index));
	}
	TS_JSAPI void tsDialogMenu_setItemChecked(DialogMenu &self, uint32_t index, bool checked, bool callback) {
		self.setItemChecked(index, checked, callback);
	}
	TS_JSAPI bool tsDialogMenu_isItemChecked(const DialogMenu &self, uint32_t index) {
		return self.isItemChecked(index);
	}
	TS_JSAPI void tsDialogMenu_setItemEnabled(DialogMenu &self, uint32_t index, bool enabled) {
		self.setItemEnabled(index, enabled);
	}
	TS_JSAPI bool tsDialogMenu_isItemEnabled(const DialogMenu &self, uint32_t index) {
		return self.isItemEnabled(index);
	}
	TS_JSAPI void tsDialogMenu_setItemHidden(DialogMenu &self, uint32_t index, bool hidden) {
		self.setItemHidden(index, hidden);
	}
	TS_JSAPI bool tsDialogMenu_isItemHidden(const DialogMenu &self, uint32_t index) {
		return self.isItemHidden(index);
	}
	TS_JSAPI void tsDialogMenu_setItemsGroup(DialogMenu &self, uint32_t index, uint32_t size) {
		self.setItemsGroup(index, size);
	}
	TS_JSAPI uint32_t tsDialogMenu_getItemGroupIndex(const DialogMenu &self, uint32_t index) {
		return self.getItemGroupIndex(index);
	}
	TS_JSAPI uint32_t tsDialogMenu_getItemGroupSize(const DialogMenu &self, uint32_t index) {
		return self.getItemGroupSize(index);
	}
	TS_JSAPI uint32_t tsDialogMenu_addItem(DialogMenu &self, const char *text, const char *key) {
		return self.addItem(text, key);
	}
	TS_JSAPI uint32_t tsDialogMenu_addItem_1(DialogMenu &self, const String &text, const char *key) {
		return self.addItem(text, key);
	}
	TS_JSAPI uint32_t tsDialogMenu_addItem_2(DialogMenu &self, const char *text, const Image &image, const char *key) {
		return self.addItem(text, image, key);
	}
	TS_JSAPI uint32_t tsDialogMenu_addItem_3(DialogMenu &self, const String &text, const Image &image, const char *key) {
		return self.addItem(text, image, key);
	}
	TS_JSAPI uint32_t tsDialogMenu_addItem_4(DialogMenu &self, const char *text, bool func, const char *key) {
		return self.addItem(text, (func) ? make_dialog_menu_clicked_callback(&self) : DialogMenu::ClickedCallback(), key);
	}
	TS_JSAPI uint32_t tsDialogMenu_addItem_5(DialogMenu &self, const String &text, bool func, const char *key) {
		return self.addItem(text, (func) ? make_dialog_menu_clicked_callback(&self) : DialogMenu::ClickedCallback(), key);
	}
	TS_JSAPI uint32_t tsDialogMenu_addItem_6(DialogMenu &self, const char *text, const Image &image, bool func, const char *key) {
		return self.addItem(text, image, (func) ? make_dialog_menu_clicked_callback(&self) : DialogMenu::ClickedCallback(), key);
	}
	TS_JSAPI uint32_t tsDialogMenu_addItem_7(DialogMenu &self, const String &text, const Image &image, bool func, const char *key) {
		return self.addItem(text, image, (func) ? make_dialog_menu_clicked_callback(&self) : DialogMenu::ClickedCallback(), key);
	}
	TS_JSAPI uint32_t tsDialogMenu_addItem_8(DialogMenu &self, const char *text, bool checked, bool func, const char *key) {
		return self.addItem(text, checked, (func) ? make_dialog_menu_changed_callback(&self) : DialogMenu::ChangedCallback(), key);
	}
	TS_JSAPI uint32_t tsDialogMenu_addItem_9(DialogMenu &self, const String &text, bool checked, bool func, const char *key) {
		return self.addItem(text, checked, (func) ? make_dialog_menu_changed_callback(&self) : DialogMenu::ChangedCallback(), key);
	}
	TS_JSAPI uint32_t tsDialogMenu_addItem_10(DialogMenu &self, const char *text, const Image &image, bool checked, bool func, const char *key) {
		return self.addItem(text, image, checked, (func) ? make_dialog_menu_changed_callback(&self) : DialogMenu::ChangedCallback(), key);
	}
	TS_JSAPI uint32_t tsDialogMenu_addItem_11(DialogMenu &self, const String &text, const Image &image, bool checked, bool func, const char *key) {
		return self.addItem(text, image, checked, (func) ? make_dialog_menu_changed_callback(&self) : DialogMenu::ChangedCallback(), key);
	}
	TS_JSAPI void tsDialogMenu_setUpdateCallback(DialogMenu &self, bool func) {
		self.setUpdateCallback((func) ? make_dialog_menu_update_callback(&self) : DialogMenu::UpdateCallback());
	}
	TS_JSAPI uint32_t tsDialogMenu_run(DialogMenu &self, uint32_t flags) {
		return self.run((DialogMenu::Flags)flags);
	}
	
	// Tellusim::CubeFilter
	TS_JSAPI CubeFilter *tsCubeFilter_new() {
		return new CubeFilter();
	}
	TS_JSAPI void tsCubeFilter_delete(CubeFilter *self) {
		delete self;
	}
	TS_JSAPI bool tsCubeFilter_equalPtr(const CubeFilter &self, const CubeFilter &ptr) {
		return (self == ptr);
	}
	TS_JSAPI CubeFilter *tsCubeFilter_clonePtr(const CubeFilter &self) {
		return new CubeFilter(self.clonePtr());
	}
	TS_JSAPI void tsCubeFilter_clearPtr(CubeFilter &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsCubeFilter_destroyPtr(CubeFilter &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsCubeFilter_acquirePtr(CubeFilter &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsCubeFilter_unacquirePtr(CubeFilter &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsCubeFilter_isValidPtr(const CubeFilter &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsCubeFilter_isOwnerPtr(const CubeFilter &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsCubeFilter_isConstPtr(const CubeFilter &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsCubeFilter_getCountPtr(const CubeFilter &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsCubeFilter_getInternalPtr(const CubeFilter &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsCubeFilter_clear(CubeFilter &self) {
		self.clear();
	}
	TS_JSAPI bool tsCubeFilter_isCreated(const CubeFilter &self, uint32_t mode) {
		return self.isCreated((CubeFilter::Mode)mode);
	}
	TS_JSAPI uint32_t tsCubeFilter_getGroupSize(const CubeFilter &self) {
		return self.getGroupSize();
	}
	TS_JSAPI uint32_t tsCubeFilter_getMaxOrder(const CubeFilter &self) {
		return self.getMaxOrder();
	}
	TS_JSAPI uint32_t tsCubeFilter_getMaxSize(const CubeFilter &self) {
		return self.getMaxSize();
	}
	TS_JSAPI uint32_t tsCubeFilter_getHarmonics(const CubeFilter &self) {
		return self.getHarmonics();
	}
	TS_JSAPI bool tsCubeFilter_create(CubeFilter &self, const Device &device, uint32_t mode, uint32_t order, uint32_t size, uint32_t groups) {
		return self.create(device, (CubeFilter::Mode)mode, order, size, groups);
	}
	TS_JSAPI bool tsCubeFilter_create_1(CubeFilter &self, const Device &device, uint32_t flags, uint32_t order, uint32_t size, uint32_t groups) {
		return self.create(device, (CubeFilter::Flags)flags, order, size, groups);
	}
	TS_JSAPI bool tsCubeFilter_dispatch(const CubeFilter &self, Compute &compute, Buffer &buffer, uint32_t offset, Texture &texture, const Slice &slice) {
		return self.dispatch(compute, buffer, offset, texture, slice);
	}
	TS_JSAPI bool tsCubeFilter_dispatch_1(const CubeFilter &self, Compute &compute, Buffer &buffer, uint32_t offset, Texture &texture) {
		return self.dispatch(compute, buffer, offset, texture);
	}
	TS_JSAPI bool tsCubeFilter_dispatch_2(const CubeFilter &self, Compute &compute, Texture &texture, const Slice &slice, Buffer &buffer, uint32_t offset) {
		return self.dispatch(compute, texture, slice, buffer, offset);
	}
	TS_JSAPI bool tsCubeFilter_dispatch_3(const CubeFilter &self, Compute &compute, Texture &texture, Buffer &buffer, uint32_t offset) {
		return self.dispatch(compute, texture, buffer, offset);
	}
	TS_JSAPI bool tsCubeFilter_dispatch_4(const CubeFilter &self, Compute &compute, Texture &dest, Texture &src, const Slice &dest_slice, const Slice &src_slice) {
		return self.dispatch(compute, dest, src, dest_slice, src_slice);
	}
	TS_JSAPI bool tsCubeFilter_dispatch_5(const CubeFilter &self, Compute &compute, Texture &dest, Texture &src, const Slice &src_slice) {
		return self.dispatch(compute, dest, src, src_slice);
	}
	TS_JSAPI bool tsCubeFilter_dispatch_6(const CubeFilter &self, Compute &compute, Texture &dest, Texture &src) {
		return self.dispatch(compute, dest, src);
	}
	
	// Tellusim::DecoderJPEG
	TS_JSAPI DecoderJPEG *tsDecoderJPEG_new() {
		return new DecoderJPEG();
	}
	TS_JSAPI void tsDecoderJPEG_delete(DecoderJPEG *self) {
		delete self;
	}
	TS_JSAPI bool tsDecoderJPEG_equalPtr(const DecoderJPEG &self, const DecoderJPEG &ptr) {
		return (self == ptr);
	}
	TS_JSAPI DecoderJPEG *tsDecoderJPEG_clonePtr(const DecoderJPEG &self) {
		return new DecoderJPEG(self.clonePtr());
	}
	TS_JSAPI void tsDecoderJPEG_clearPtr(DecoderJPEG &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsDecoderJPEG_destroyPtr(DecoderJPEG &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsDecoderJPEG_acquirePtr(DecoderJPEG &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsDecoderJPEG_unacquirePtr(DecoderJPEG &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsDecoderJPEG_isValidPtr(const DecoderJPEG &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsDecoderJPEG_isOwnerPtr(const DecoderJPEG &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsDecoderJPEG_isConstPtr(const DecoderJPEG &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsDecoderJPEG_getCountPtr(const DecoderJPEG &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsDecoderJPEG_getInternalPtr(const DecoderJPEG &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsDecoderJPEG_clear(DecoderJPEG &self) {
		self.clear();
	}
	TS_JSAPI bool tsDecoderJPEG_isCreated(const DecoderJPEG &self, uint32_t mode) {
		return self.isCreated((DecoderJPEG::Mode)mode);
	}
	TS_JSAPI bool tsDecoderJPEG_isYUV(uint32_t mode) {
		return DecoderJPEG::isYUV((DecoderJPEG::Mode)mode);
	}
	TS_JSAPI bool tsDecoderJPEG_create(DecoderJPEG &self, const Device &device, uint32_t mode) {
		return self.create(device, (DecoderJPEG::Mode)mode);
	}
	TS_JSAPI bool tsDecoderJPEG_create_1(DecoderJPEG &self, const Device &device, uint32_t flags) {
		return self.create(device, (DecoderJPEG::Flags)flags);
	}
	TS_JSAPI bool tsDecoderJPEG_load(const char *name, Image &image, uint32_t* mode, Size &size) {
		TS_ASSERT(mode);
		return DecoderJPEG::load(name, image, (DecoderJPEG::Mode&)*mode, size);
	}
	TS_JSAPI bool tsDecoderJPEG_load_1(Stream &stream, Image &image, uint32_t* mode, Size &size) {
		TS_ASSERT(mode);
		return DecoderJPEG::load(stream, image, (DecoderJPEG::Mode&)*mode, size);
	}
	TS_JSAPI Texture *tsDecoderJPEG_loadTexture(const DecoderJPEG &self, const Device &device, const char *name, uint32_t flags) {
		return new Texture(self.loadTexture(device, name, (Texture::Flags)flags));
	}
	TS_JSAPI Texture *tsDecoderJPEG_loadTexture_1(const DecoderJPEG &self, const Device &device, Stream &stream, uint32_t flags) {
		return new Texture(self.loadTexture(device, stream, (Texture::Flags)flags));
	}
	TS_JSAPI bool tsDecoderJPEG_dispatch(const DecoderJPEG &self, Compute &compute, uint32_t mode, Texture &dest, Texture &src, const Slice &dest_slice, const Slice &src_slice) {
		return self.dispatch(compute, (DecoderJPEG::Mode)mode, dest, src, dest_slice, src_slice);
	}
	TS_JSAPI bool tsDecoderJPEG_dispatch_1(const DecoderJPEG &self, Compute &compute, uint32_t mode, Texture &dest, Texture &src, const Slice &src_slice) {
		return self.dispatch(compute, (DecoderJPEG::Mode)mode, dest, src, src_slice);
	}
	TS_JSAPI bool tsDecoderJPEG_dispatch_2(const DecoderJPEG &self, Compute &compute, uint32_t mode, Texture &dest, Texture &src) {
		return self.dispatch(compute, (DecoderJPEG::Mode)mode, dest, src);
	}
	TS_JSAPI bool tsDecoderJPEG_dispatchYUV(const DecoderJPEG &self, Compute &compute, uint32_t mode, Texture &dest, Texture &src, const Slice &dest_slice, const Slice &src_slice) {
		return self.dispatchYUV(compute, (DecoderJPEG::Mode)mode, dest, src, dest_slice, src_slice);
	}
	TS_JSAPI bool tsDecoderJPEG_dispatchYUV_1(const DecoderJPEG &self, Compute &compute, uint32_t mode, Texture &dest, Texture &src, const Slice &src_slice) {
		return self.dispatchYUV(compute, (DecoderJPEG::Mode)mode, dest, src, src_slice);
	}
	TS_JSAPI bool tsDecoderJPEG_dispatchYUV_2(const DecoderJPEG &self, Compute &compute, uint32_t mode, Texture &dest, Texture &src) {
		return self.dispatchYUV(compute, (DecoderJPEG::Mode)mode, dest, src);
	}
	
	// Tellusim::EncoderBC15
	TS_JSAPI EncoderBC15 *tsEncoderBC15_new() {
		return new EncoderBC15();
	}
	TS_JSAPI void tsEncoderBC15_delete(EncoderBC15 *self) {
		delete self;
	}
	TS_JSAPI bool tsEncoderBC15_equalPtr(const EncoderBC15 &self, const EncoderBC15 &ptr) {
		return (self == ptr);
	}
	TS_JSAPI EncoderBC15 *tsEncoderBC15_clonePtr(const EncoderBC15 &self) {
		return new EncoderBC15(self.clonePtr());
	}
	TS_JSAPI void tsEncoderBC15_clearPtr(EncoderBC15 &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsEncoderBC15_destroyPtr(EncoderBC15 &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsEncoderBC15_acquirePtr(EncoderBC15 &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsEncoderBC15_unacquirePtr(EncoderBC15 &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsEncoderBC15_isValidPtr(const EncoderBC15 &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsEncoderBC15_isOwnerPtr(const EncoderBC15 &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsEncoderBC15_isConstPtr(const EncoderBC15 &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsEncoderBC15_getCountPtr(const EncoderBC15 &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsEncoderBC15_getInternalPtr(const EncoderBC15 &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsEncoderBC15_clear(EncoderBC15 &self) {
		self.clear();
	}
	TS_JSAPI bool tsEncoderBC15_isCreated(const EncoderBC15 &self, uint32_t mode) {
		return self.isCreated((EncoderBC15::Mode)mode);
	}
	TS_JSAPI bool tsEncoderBC15_create(EncoderBC15 &self, const Device &device, uint32_t mode) {
		return self.create(device, (EncoderBC15::Mode)mode);
	}
	TS_JSAPI bool tsEncoderBC15_create_1(EncoderBC15 &self, const Device &device, uint32_t flags) {
		return self.create(device, (EncoderBC15::Flags)flags);
	}
	TS_JSAPI bool tsEncoderBC15_dispatch(const EncoderBC15 &self, Compute &compute, uint32_t mode, Texture &dest, Texture &src, const Slice &dest_slice, const Slice &src_slice) {
		return self.dispatch(compute, (EncoderBC15::Mode)mode, dest, src, dest_slice, src_slice);
	}
	TS_JSAPI bool tsEncoderBC15_dispatch_1(const EncoderBC15 &self, Compute &compute, uint32_t mode, Texture &dest, Texture &src, const Slice &src_slice) {
		return self.dispatch(compute, (EncoderBC15::Mode)mode, dest, src, src_slice);
	}
	TS_JSAPI bool tsEncoderBC15_dispatch_2(const EncoderBC15 &self, Compute &compute, uint32_t mode, Texture &dest, Texture &src) {
		return self.dispatch(compute, (EncoderBC15::Mode)mode, dest, src);
	}
	
	// Tellusim::EncoderBC67
	TS_JSAPI EncoderBC67 *tsEncoderBC67_new() {
		return new EncoderBC67();
	}
	TS_JSAPI void tsEncoderBC67_delete(EncoderBC67 *self) {
		delete self;
	}
	TS_JSAPI bool tsEncoderBC67_equalPtr(const EncoderBC67 &self, const EncoderBC67 &ptr) {
		return (self == ptr);
	}
	TS_JSAPI EncoderBC67 *tsEncoderBC67_clonePtr(const EncoderBC67 &self) {
		return new EncoderBC67(self.clonePtr());
	}
	TS_JSAPI void tsEncoderBC67_clearPtr(EncoderBC67 &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsEncoderBC67_destroyPtr(EncoderBC67 &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsEncoderBC67_acquirePtr(EncoderBC67 &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsEncoderBC67_unacquirePtr(EncoderBC67 &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsEncoderBC67_isValidPtr(const EncoderBC67 &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsEncoderBC67_isOwnerPtr(const EncoderBC67 &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsEncoderBC67_isConstPtr(const EncoderBC67 &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsEncoderBC67_getCountPtr(const EncoderBC67 &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsEncoderBC67_getInternalPtr(const EncoderBC67 &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsEncoderBC67_clear(EncoderBC67 &self) {
		self.clear();
	}
	TS_JSAPI bool tsEncoderBC67_isCreated(const EncoderBC67 &self, uint32_t mode) {
		return self.isCreated((EncoderBC67::Mode)mode);
	}
	TS_JSAPI bool tsEncoderBC67_create(EncoderBC67 &self, const Device &device, uint32_t mode) {
		return self.create(device, (EncoderBC67::Mode)mode);
	}
	TS_JSAPI bool tsEncoderBC67_create_1(EncoderBC67 &self, const Device &device, uint32_t flags) {
		return self.create(device, (EncoderBC67::Flags)flags);
	}
	TS_JSAPI bool tsEncoderBC67_dispatch(const EncoderBC67 &self, Compute &compute, uint32_t mode, Texture &dest, Texture &src, const Slice &dest_slice, const Slice &src_slice, uint32_t components) {
		return self.dispatch(compute, (EncoderBC67::Mode)mode, dest, src, dest_slice, src_slice, components);
	}
	TS_JSAPI bool tsEncoderBC67_dispatch_1(const EncoderBC67 &self, Compute &compute, uint32_t mode, Texture &dest, Texture &src, const Slice &src_slice, uint32_t components) {
		return self.dispatch(compute, (EncoderBC67::Mode)mode, dest, src, src_slice, components);
	}
	TS_JSAPI bool tsEncoderBC67_dispatch_2(const EncoderBC67 &self, Compute &compute, uint32_t mode, Texture &dest, Texture &src, uint32_t components) {
		return self.dispatch(compute, (EncoderBC67::Mode)mode, dest, src, components);
	}
	
	// Tellusim::EncoderASTC
	TS_JSAPI EncoderASTC *tsEncoderASTC_new() {
		return new EncoderASTC();
	}
	TS_JSAPI void tsEncoderASTC_delete(EncoderASTC *self) {
		delete self;
	}
	TS_JSAPI bool tsEncoderASTC_equalPtr(const EncoderASTC &self, const EncoderASTC &ptr) {
		return (self == ptr);
	}
	TS_JSAPI EncoderASTC *tsEncoderASTC_clonePtr(const EncoderASTC &self) {
		return new EncoderASTC(self.clonePtr());
	}
	TS_JSAPI void tsEncoderASTC_clearPtr(EncoderASTC &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsEncoderASTC_destroyPtr(EncoderASTC &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsEncoderASTC_acquirePtr(EncoderASTC &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsEncoderASTC_unacquirePtr(EncoderASTC &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsEncoderASTC_isValidPtr(const EncoderASTC &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsEncoderASTC_isOwnerPtr(const EncoderASTC &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsEncoderASTC_isConstPtr(const EncoderASTC &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsEncoderASTC_getCountPtr(const EncoderASTC &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsEncoderASTC_getInternalPtr(const EncoderASTC &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsEncoderASTC_clear(EncoderASTC &self) {
		self.clear();
	}
	TS_JSAPI bool tsEncoderASTC_isCreated(const EncoderASTC &self, uint32_t mode) {
		return self.isCreated((EncoderASTC::Mode)mode);
	}
	TS_JSAPI bool tsEncoderASTC_create(EncoderASTC &self, const Device &device, uint32_t mode) {
		return self.create(device, (EncoderASTC::Mode)mode);
	}
	TS_JSAPI bool tsEncoderASTC_create_1(EncoderASTC &self, const Device &device, uint32_t flags) {
		return self.create(device, (EncoderASTC::Flags)flags);
	}
	TS_JSAPI bool tsEncoderASTC_dispatch(const EncoderASTC &self, Compute &compute, uint32_t mode, Texture &dest, Texture &src, const Slice &dest_slice, const Slice &src_slice, uint32_t components) {
		return self.dispatch(compute, (EncoderASTC::Mode)mode, dest, src, dest_slice, src_slice, components);
	}
	TS_JSAPI bool tsEncoderASTC_dispatch_1(const EncoderASTC &self, Compute &compute, uint32_t mode, Texture &dest, Texture &src, const Slice &src_slice, uint32_t components) {
		return self.dispatch(compute, (EncoderASTC::Mode)mode, dest, src, src_slice, components);
	}
	TS_JSAPI bool tsEncoderASTC_dispatch_2(const EncoderASTC &self, Compute &compute, uint32_t mode, Texture &dest, Texture &src, uint32_t components) {
		return self.dispatch(compute, (EncoderASTC::Mode)mode, dest, src, components);
	}
	
	// Tellusim::MeshModel::Meshlet
	TS_JSAPI MeshModel::Meshlet *tsMeshModelMeshlet_new() {
		return new MeshModel::Meshlet();
	}
	TS_JSAPI MeshModel::Meshlet *tsMeshModelMeshlet_copy(const MeshModel::Meshlet &self) {
		return new MeshModel::Meshlet(self);
	}
	TS_JSAPI void tsMeshModelMeshlet_delete(MeshModel::Meshlet *self) {
		delete self;
	}
	TS_JSAPI void tsMeshModelMeshlet_set_num_primitives(MeshModel::Meshlet &self, uint32_t num_primitives) {
		self.num_primitives = num_primitives;
	}
	TS_JSAPI uint32_t tsMeshModelMeshlet_get_num_primitives(const MeshModel::Meshlet &self) {
		return self.num_primitives;
	}
	TS_JSAPI void tsMeshModelMeshlet_set_num_vertices(MeshModel::Meshlet &self, uint32_t num_vertices) {
		self.num_vertices = num_vertices;
	}
	TS_JSAPI uint32_t tsMeshModelMeshlet_get_num_vertices(const MeshModel::Meshlet &self) {
		return self.num_vertices;
	}
	TS_JSAPI void tsMeshModelMeshlet_set_base_index(MeshModel::Meshlet &self, uint32_t base_index) {
		self.base_index = base_index;
	}
	TS_JSAPI uint32_t tsMeshModelMeshlet_get_base_index(const MeshModel::Meshlet &self) {
		return self.base_index;
	}
	TS_JSAPI void tsMeshModelMeshlet_set_base_vertex(MeshModel::Meshlet &self, uint32_t base_vertex) {
		self.base_vertex = base_vertex;
	}
	TS_JSAPI uint32_t tsMeshModelMeshlet_get_base_vertex(const MeshModel::Meshlet &self) {
		return self.base_vertex;
	}
	TS_JSAPI void tsMeshModelMeshlet_set_bound_sphere(MeshModel::Meshlet &self, const Vector4f &bound_sphere) {
		bound_sphere.get(self.bound_sphere);
	}
	TS_JSAPI Vector4f *tsMeshModelMeshlet_get_bound_sphere(const MeshModel::Meshlet &self) {
		return new Vector4f(self.bound_sphere);
	}
	TS_JSAPI void tsMeshModelMeshlet_set_normal_angle(MeshModel::Meshlet &self, const Vector4f &normal_angle) {
		normal_angle.get(self.normal_angle);
	}
	TS_JSAPI Vector4f *tsMeshModelMeshlet_get_normal_angle(const MeshModel::Meshlet &self) {
		return new Vector4f(self.normal_angle);
	}
	
	// Tellusim::MeshModel
	static bool mesh_model_create_callback(const void *src, size_t size, bool owner, void *self) {
		return EM_ASM_INT({ return tsMeshModel.create_callback($0, $1, $2, $3); }, self, src, size, owner) != 0;
	}
	static MeshModel::CreateCallback make_mesh_model_create_callback(void *self) {
		auto ret = makeFunction(mesh_model_create_callback);
		ret.setArg3(self);
		return ret;
	}
	TS_JSAPI MeshModel *tsMeshModel_new() {
		return new MeshModel();
	}
	TS_JSAPI void tsMeshModel_delete(MeshModel *self) {
		delete self;
	}
	TS_JSAPI void tsMeshModel_clear(MeshModel &self) {
		self.clear();
	}
	TS_JSAPI bool tsMeshModel_isCreated(const MeshModel &self) {
		return self.isCreated();
	}
	TS_JSAPI uint32_t tsMeshModel_getFlags(const MeshModel &self) {
		return self.getFlags();
	}
	TS_JSAPI bool tsMeshModel_hasFlag(const MeshModel &self, uint32_t flags) {
		return self.hasFlag((MeshModel::Flags)flags);
	}
	TS_JSAPI bool tsMeshModel_hasFlags(const MeshModel &self, uint32_t flags) {
		return self.hasFlags((MeshModel::Flags)flags);
	}
	TS_JSAPI bool tsMeshModel_load(MeshModel &self, const Device &device, const Pipeline &pipeline, const char *name, uint32_t flags, Async *async) {
		return self.load(device, pipeline, name, (MeshModel::Flags)flags, async);
	}
	TS_JSAPI bool tsMeshModel_load_1(MeshModel &self, const Device &device, const Pipeline &pipeline, Stream &stream, uint32_t flags, Async *async) {
		return self.load(device, pipeline, stream, (MeshModel::Flags)flags, async);
	}
	TS_JSAPI bool tsMeshModel_create(MeshModel &self, const Device &device, const Pipeline &pipeline, const char *name, uint32_t flags) {
		return self.create(device, pipeline, name, (MeshModel::Flags)flags);
	}
	TS_JSAPI bool tsMeshModel_create_1(MeshModel &self, const Device &device, const Pipeline &pipeline, const Mesh &mesh, uint32_t flags) {
		return self.create(device, pipeline, mesh, (MeshModel::Flags)flags);
	}
	TS_JSAPI bool tsMeshModel_create_2(MeshModel &self, const Device &device, const Pipeline &pipeline, const MeshGeometry &geometry, uint32_t flags) {
		return self.create(device, pipeline, geometry, (MeshModel::Flags)flags);
	}
	TS_JSAPI bool tsMeshModel_create_3(MeshModel &self, const Device &device, const Pipeline &pipeline, Array<MeshGeometry> &geometries, uint32_t flags) {
		return self.create(device, pipeline, geometries, (MeshModel::Flags)flags);
	}
	TS_JSAPI void tsMeshModel_setVertexBufferCallback(MeshModel &self, bool func) {
		self.setVertexBufferCallback((func) ? make_mesh_model_create_callback(&self) : MeshModel::CreateCallback());
	}
	TS_JSAPI void tsMeshModel_setIndexBufferCallback(MeshModel &self, bool func) {
		self.setIndexBufferCallback((func) ? make_mesh_model_create_callback(&self) : MeshModel::CreateCallback());
	}
	TS_JSAPI void tsMeshModel_setMeshBufferCallback(MeshModel &self, bool func) {
		self.setMeshBufferCallback((func) ? make_mesh_model_create_callback(&self) : MeshModel::CreateCallback());
	}
	TS_JSAPI void tsMeshModel_setBuffers(const MeshModel &self, Command &command, uint32_t index, const Pipeline *pipeline) {
		self.setBuffers(command, index, pipeline);
	}
	TS_JSAPI void tsMeshModel_draw(const MeshModel &self, Command &command) {
		self.draw(command);
	}
	TS_JSAPI void tsMeshModel_draw_1(const MeshModel &self, Command &command, uint32_t geometry) {
		self.draw(command, geometry);
	}
	TS_JSAPI void tsMeshModel_draw_2(const MeshModel &self, Command &command, uint32_t geometry, uint32_t material) {
		self.draw(command, geometry, material);
	}
	TS_JSAPI void tsMeshModel_drawInstanced(const MeshModel &self, Command &command, uint32_t geometry, uint32_t num_instances, uint32_t base_instance) {
		self.drawInstanced(command, geometry, num_instances, base_instance);
	}
	TS_JSAPI void tsMeshModel_drawInstanced_1(const MeshModel &self, Command &command, uint32_t geometry, uint32_t material, uint32_t num_instances, uint32_t base_instance) {
		self.drawInstanced(command, geometry, material, num_instances, base_instance);
	}
	TS_JSAPI uint32_t tsMeshModel_getNumVertices(const MeshModel &self) {
		return self.getNumVertices();
	}
	TS_JSAPI uint32_t tsMeshModel_getNumVertexBuffers(const MeshModel &self) {
		return self.getNumVertexBuffers();
	}
	TS_JSAPI uint32_t tsMeshModel_getVertexBufferStride(const MeshModel &self, uint32_t index) {
		return self.getVertexBufferStride(index);
	}
	TS_JSAPI size_t tsMeshModel_getVertexBufferOffset(const MeshModel &self, uint32_t index) {
		return self.getVertexBufferOffset(index);
	}
	TS_JSAPI Buffer *tsMeshModel_getVertexBuffer(const MeshModel &self) {
		return new Buffer(self.getVertexBuffer());
	}
	TS_JSAPI uint32_t tsMeshModel_getNumIndices(const MeshModel &self) {
		return self.getNumIndices();
	}
	TS_JSAPI uint32_t tsMeshModel_getIndexFormat(const MeshModel &self) {
		return self.getIndexFormat();
	}
	TS_JSAPI Buffer *tsMeshModel_getIndexBuffer(const MeshModel &self) {
		return new Buffer(self.getIndexBuffer());
	}
	TS_JSAPI uint32_t tsMeshModel_getNumMeshlets(const MeshModel &self) {
		return self.getNumMeshlets();
	}
	TS_JSAPI Buffer *tsMeshModel_getMeshletBuffer(const MeshModel &self) {
		return new Buffer(self.getMeshletBuffer());
	}
	TS_JSAPI uint32_t tsMeshModel_getNumGeometries(const MeshModel &self) {
		return self.getNumGeometries();
	}
	TS_JSAPI uint32_t tsMeshModel_getNumGeometryIndices(const MeshModel &self, uint32_t geometry) {
		return self.getNumGeometryIndices(geometry);
	}
	TS_JSAPI uint32_t tsMeshModel_getNumGeometryVertices(const MeshModel &self, uint32_t geometry) {
		return self.getNumGeometryVertices(geometry);
	}
	TS_JSAPI uint32_t tsMeshModel_getNumGeometryMeshlets(const MeshModel &self, uint32_t geometry) {
		return self.getNumGeometryMeshlets(geometry);
	}
	TS_JSAPI uint32_t tsMeshModel_getGeometryBaseIndex(const MeshModel &self, uint32_t geometry) {
		return self.getGeometryBaseIndex(geometry);
	}
	TS_JSAPI uint32_t tsMeshModel_getGeometryBaseVertex(const MeshModel &self, uint32_t geometry) {
		return self.getGeometryBaseVertex(geometry);
	}
	TS_JSAPI uint32_t tsMeshModel_getGeometryBaseMeshlet(const MeshModel &self, uint32_t geometry) {
		return self.getGeometryBaseMeshlet(geometry);
	}
	TS_JSAPI uint32_t tsMeshModel_getNumMaterials(const MeshModel &self, uint32_t geometry) {
		return self.getNumMaterials(geometry);
	}
	TS_JSAPI uint32_t tsMeshModel_getNumMaterialIndices(const MeshModel &self, uint32_t geometry, uint32_t material) {
		return self.getNumMaterialIndices(geometry, material);
	}
	TS_JSAPI uint32_t tsMeshModel_getNumMaterialVertices(const MeshModel &self, uint32_t geometry, uint32_t material) {
		return self.getNumMaterialVertices(geometry, material);
	}
	TS_JSAPI uint32_t tsMeshModel_getNumMaterialMeshlets(const MeshModel &self, uint32_t geometry, uint32_t material) {
		return self.getNumMaterialMeshlets(geometry, material);
	}
	TS_JSAPI uint32_t tsMeshModel_getMaterialBaseIndex(const MeshModel &self, uint32_t geometry, uint32_t material) {
		return self.getMaterialBaseIndex(geometry, material);
	}
	TS_JSAPI uint32_t tsMeshModel_getMaterialBaseVertex(const MeshModel &self, uint32_t geometry, uint32_t material) {
		return self.getMaterialBaseVertex(geometry, material);
	}
	TS_JSAPI uint32_t tsMeshModel_getMaterialBaseMeshlet(const MeshModel &self, uint32_t geometry, uint32_t material) {
		return self.getMaterialBaseMeshlet(geometry, material);
	}
	TS_JSAPI size_t tsMeshModel_getMemory(const MeshModel &self) {
		return self.getMemory();
	}
	
	// Tellusim::SeparableFilter
	TS_JSAPI SeparableFilter *tsSeparableFilter_new() {
		return new SeparableFilter();
	}
	TS_JSAPI void tsSeparableFilter_delete(SeparableFilter *self) {
		delete self;
	}
	TS_JSAPI bool tsSeparableFilter_equalPtr(const SeparableFilter &self, const SeparableFilter &ptr) {
		return (self == ptr);
	}
	TS_JSAPI SeparableFilter *tsSeparableFilter_clonePtr(const SeparableFilter &self) {
		return new SeparableFilter(self.clonePtr());
	}
	TS_JSAPI void tsSeparableFilter_clearPtr(SeparableFilter &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsSeparableFilter_destroyPtr(SeparableFilter &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsSeparableFilter_acquirePtr(SeparableFilter &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsSeparableFilter_unacquirePtr(SeparableFilter &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsSeparableFilter_isValidPtr(const SeparableFilter &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsSeparableFilter_isOwnerPtr(const SeparableFilter &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsSeparableFilter_isConstPtr(const SeparableFilter &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsSeparableFilter_getCountPtr(const SeparableFilter &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsSeparableFilter_getInternalPtr(const SeparableFilter &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsSeparableFilter_clear(SeparableFilter &self) {
		self.clear();
	}
	TS_JSAPI bool tsSeparableFilter_isCreated(const SeparableFilter &self, uint32_t format, uint32_t size) {
		return self.isCreated((Format)format, size);
	}
	TS_JSAPI void tsSeparableFilter_setInputSource(SeparableFilter &self, uint32_t mode, const char *src) {
		self.setInputSource((SeparableFilter::Mode)mode, src);
	}
	TS_JSAPI String *tsSeparableFilter_getInputSource(const SeparableFilter &self, uint32_t mode) {
		return new String(self.getInputSource((SeparableFilter::Mode)mode));
	}
	TS_JSAPI void tsSeparableFilter_setKernelSource(SeparableFilter &self, uint32_t mode, const char *src) {
		self.setKernelSource((SeparableFilter::Mode)mode, src);
	}
	TS_JSAPI String *tsSeparableFilter_getKernelSource(const SeparableFilter &self, uint32_t mode) {
		return new String(self.getKernelSource((SeparableFilter::Mode)mode));
	}
	TS_JSAPI void tsSeparableFilter_setOutputSource(SeparableFilter &self, uint32_t mode, const char *src) {
		self.setOutputSource((SeparableFilter::Mode)mode, src);
	}
	TS_JSAPI String *tsSeparableFilter_getOutputSource(const SeparableFilter &self, uint32_t mode) {
		return new String(self.getOutputSource((SeparableFilter::Mode)mode));
	}
	TS_JSAPI bool tsSeparableFilter_create(SeparableFilter &self, const Device &device, uint32_t format, uint32_t size, uint32_t flags) {
		return self.create(device, (Format)format, size, (SeparableFilter::Flags)flags);
	}
	TS_JSAPI void tsSeparableFilter_setWeights(SeparableFilter &self, uint32_t mode, Array<Vector4f> &weights, bool normalize) {
		self.setWeights((SeparableFilter::Mode)mode, weights, normalize);
	}
	TS_JSAPI void tsSeparableFilter_setWeights_1(SeparableFilter &self, uint32_t mode, Array<float32_t> &weights, bool normalize) {
		self.setWeights((SeparableFilter::Mode)mode, weights, normalize);
	}
	TS_JSAPI void tsSeparableFilter_setGaussianWeights(SeparableFilter &self, uint32_t size, const Vector4f &sigma) {
		self.setGaussianWeights(size, sigma);
	}
	TS_JSAPI void tsSeparableFilter_setGaussianWeights_1(SeparableFilter &self, uint32_t size, float32_t sigma) {
		self.setGaussianWeights(size, sigma);
	}
	TS_JSAPI void tsSeparableFilter_setSobelXWeights(SeparableFilter &self, uint32_t size) {
		self.setSobelXWeights(size);
	}
	TS_JSAPI void tsSeparableFilter_setSobelYWeights(SeparableFilter &self, uint32_t size) {
		self.setSobelYWeights(size);
	}
	TS_JSAPI void tsSeparableFilter_setBoxWeights(SeparableFilter &self, uint32_t size) {
		self.setBoxWeights(size);
	}
	TS_JSAPI bool tsSeparableFilter_dispatch(const SeparableFilter &self, Compute &compute, uint32_t mode, uint32_t size, Texture &dest, Texture &src, const Slice &dest_slice, const Slice &src_slice, const Vector4f &parameters) {
		return self.dispatch(compute, (SeparableFilter::Mode)mode, size, dest, src, dest_slice, src_slice, parameters);
	}
	TS_JSAPI bool tsSeparableFilter_dispatch_1(const SeparableFilter &self, Compute &compute, uint32_t mode, uint32_t size, Texture &dest, Texture &src, const Slice &src_slice, const Vector4f &parameters) {
		return self.dispatch(compute, (SeparableFilter::Mode)mode, size, dest, src, src_slice, parameters);
	}
	TS_JSAPI bool tsSeparableFilter_dispatch_2(const SeparableFilter &self, Compute &compute, uint32_t mode, uint32_t size, Texture &dest, Texture &src, const Vector4f &parameters) {
		return self.dispatch(compute, (SeparableFilter::Mode)mode, size, dest, src, parameters);
	}
	
	// Tellusim::PrefixScan::DispatchParameters
	TS_JSAPI PrefixScan::DispatchParameters *tsPrefixScanDispatchParameters_new() {
		return new PrefixScan::DispatchParameters();
	}
	TS_JSAPI PrefixScan::DispatchParameters *tsPrefixScanDispatchParameters_copy(const PrefixScan::DispatchParameters &self) {
		return new PrefixScan::DispatchParameters(self);
	}
	TS_JSAPI void tsPrefixScanDispatchParameters_delete(PrefixScan::DispatchParameters *self) {
		delete self;
	}
	TS_JSAPI void tsPrefixScanDispatchParameters_set_offset(PrefixScan::DispatchParameters &self, uint32_t offset) {
		self.offset = offset;
	}
	TS_JSAPI uint32_t tsPrefixScanDispatchParameters_get_offset(const PrefixScan::DispatchParameters &self) {
		return self.offset;
	}
	TS_JSAPI void tsPrefixScanDispatchParameters_set_size(PrefixScan::DispatchParameters &self, uint32_t size) {
		self.size = size;
	}
	TS_JSAPI uint32_t tsPrefixScanDispatchParameters_get_size(const PrefixScan::DispatchParameters &self) {
		return self.size;
	}
	
	// Tellusim::PrefixScan
	TS_JSAPI PrefixScan *tsPrefixScan_new() {
		return new PrefixScan();
	}
	TS_JSAPI void tsPrefixScan_delete(PrefixScan *self) {
		delete self;
	}
	TS_JSAPI bool tsPrefixScan_equalPtr(const PrefixScan &self, const PrefixScan &ptr) {
		return (self == ptr);
	}
	TS_JSAPI PrefixScan *tsPrefixScan_clonePtr(const PrefixScan &self) {
		return new PrefixScan(self.clonePtr());
	}
	TS_JSAPI void tsPrefixScan_clearPtr(PrefixScan &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsPrefixScan_destroyPtr(PrefixScan &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsPrefixScan_acquirePtr(PrefixScan &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsPrefixScan_unacquirePtr(PrefixScan &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsPrefixScan_isValidPtr(const PrefixScan &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsPrefixScan_isOwnerPtr(const PrefixScan &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsPrefixScan_isConstPtr(const PrefixScan &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsPrefixScan_getCountPtr(const PrefixScan &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsPrefixScan_getInternalPtr(const PrefixScan &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsPrefixScan_clear(PrefixScan &self) {
		self.clear();
	}
	TS_JSAPI bool tsPrefixScan_isCreated(const PrefixScan &self, uint32_t flags) {
		return self.isCreated((PrefixScan::Flags)flags);
	}
	TS_JSAPI uint32_t tsPrefixScan_getGroupSize(const PrefixScan &self) {
		return self.getGroupSize();
	}
	TS_JSAPI uint32_t tsPrefixScan_getScanElements(const PrefixScan &self) {
		return self.getScanElements();
	}
	TS_JSAPI uint32_t tsPrefixScan_getMaxElements(const PrefixScan &self) {
		return self.getMaxElements();
	}
	TS_JSAPI uint32_t tsPrefixScan_getMaxRegions(const PrefixScan &self) {
		return self.getMaxRegions();
	}
	TS_JSAPI bool tsPrefixScan_create(PrefixScan &self, const Device &device, uint32_t mode, uint32_t groups, uint32_t regions, Async *async) {
		return self.create(device, (PrefixScan::Mode)mode, groups, regions, async);
	}
	TS_JSAPI bool tsPrefixScan_create_1(PrefixScan &self, const Device &device, uint32_t flags, uint32_t groups, uint32_t regions, Async *async) {
		return self.create(device, (PrefixScan::Flags)flags, groups, regions, async);
	}
	TS_JSAPI bool tsPrefixScan_dispatch(PrefixScan &self, Compute &compute, Buffer &data, uint32_t offset, uint32_t size, uint32_t stride) {
		return self.dispatch(compute, data, offset, size, stride);
	}
	TS_JSAPI bool tsPrefixScan_dispatch_1(PrefixScan &self, Compute &compute, Buffer &data, uint32_t count, const uint32_t *offsets, const uint32_t *sizes, uint32_t flags, uint32_t stride) {
		return self.dispatch(compute, data, count, offsets, sizes, (PrefixScan::Flags)flags, stride);
	}
	TS_JSAPI bool tsPrefixScan_dispatchIndirect(PrefixScan &self, Compute &compute, Buffer &data, Buffer &dispatch, uint32_t offset, uint32_t flags, uint32_t max_size, uint32_t stride) {
		return self.dispatchIndirect(compute, data, dispatch, offset, (PrefixScan::Flags)flags, max_size, stride);
	}
	TS_JSAPI bool tsPrefixScan_dispatchIndirect_1(PrefixScan &self, Compute &compute, Buffer &data, uint32_t count, Buffer &dispatch, uint32_t offset, uint32_t flags, uint32_t max_size, uint32_t stride) {
		return self.dispatchIndirect(compute, data, count, dispatch, offset, (PrefixScan::Flags)flags, max_size, stride);
	}
	TS_JSAPI bool tsPrefixScan_dispatchIndirect_2(PrefixScan &self, Compute &compute, Buffer &data, Buffer &count, Buffer &dispatch, uint32_t count_offset, uint32_t dispatch_offset, uint32_t flags, uint32_t max_size, uint32_t stride) {
		return self.dispatchIndirect(compute, data, count, dispatch, count_offset, dispatch_offset, (PrefixScan::Flags)flags, max_size, stride);
	}
	
	// Tellusim::RadixSort::DispatchParameters
	TS_JSAPI RadixSort::DispatchParameters *tsRadixSortDispatchParameters_new() {
		return new RadixSort::DispatchParameters();
	}
	TS_JSAPI RadixSort::DispatchParameters *tsRadixSortDispatchParameters_copy(const RadixSort::DispatchParameters &self) {
		return new RadixSort::DispatchParameters(self);
	}
	TS_JSAPI void tsRadixSortDispatchParameters_delete(RadixSort::DispatchParameters *self) {
		delete self;
	}
	TS_JSAPI void tsRadixSortDispatchParameters_set_keys_offset(RadixSort::DispatchParameters &self, uint32_t keys_offset) {
		self.keys_offset = keys_offset;
	}
	TS_JSAPI uint32_t tsRadixSortDispatchParameters_get_keys_offset(const RadixSort::DispatchParameters &self) {
		return self.keys_offset;
	}
	TS_JSAPI void tsRadixSortDispatchParameters_set_data_offset(RadixSort::DispatchParameters &self, uint32_t data_offset) {
		self.data_offset = data_offset;
	}
	TS_JSAPI uint32_t tsRadixSortDispatchParameters_get_data_offset(const RadixSort::DispatchParameters &self) {
		return self.data_offset;
	}
	TS_JSAPI void tsRadixSortDispatchParameters_set_size(RadixSort::DispatchParameters &self, uint32_t size) {
		self.size = size;
	}
	TS_JSAPI uint32_t tsRadixSortDispatchParameters_get_size(const RadixSort::DispatchParameters &self) {
		return self.size;
	}
	
	// Tellusim::RadixSort
	TS_JSAPI RadixSort *tsRadixSort_new() {
		return new RadixSort();
	}
	TS_JSAPI void tsRadixSort_delete(RadixSort *self) {
		delete self;
	}
	TS_JSAPI bool tsRadixSort_equalPtr(const RadixSort &self, const RadixSort &ptr) {
		return (self == ptr);
	}
	TS_JSAPI RadixSort *tsRadixSort_clonePtr(const RadixSort &self) {
		return new RadixSort(self.clonePtr());
	}
	TS_JSAPI void tsRadixSort_clearPtr(RadixSort &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsRadixSort_destroyPtr(RadixSort &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsRadixSort_acquirePtr(RadixSort &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsRadixSort_unacquirePtr(RadixSort &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsRadixSort_isValidPtr(const RadixSort &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsRadixSort_isOwnerPtr(const RadixSort &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsRadixSort_isConstPtr(const RadixSort &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsRadixSort_getCountPtr(const RadixSort &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsRadixSort_getInternalPtr(const RadixSort &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsRadixSort_clear(RadixSort &self) {
		self.clear();
	}
	TS_JSAPI bool tsRadixSort_isCreated(const RadixSort &self, uint32_t flags) {
		return self.isCreated((RadixSort::Flags)flags);
	}
	TS_JSAPI uint32_t tsRadixSort_getDataSize(const RadixSort &self) {
		return self.getDataSize();
	}
	TS_JSAPI uint32_t tsRadixSort_getGroupSize(const RadixSort &self) {
		return self.getGroupSize();
	}
	TS_JSAPI uint32_t tsRadixSort_getSortElements(const RadixSort &self) {
		return self.getSortElements();
	}
	TS_JSAPI uint32_t tsRadixSort_getUpdateElements(const RadixSort &self) {
		return self.getUpdateElements();
	}
	TS_JSAPI uint32_t tsRadixSort_getMaxElements(const RadixSort &self) {
		return self.getMaxElements();
	}
	TS_JSAPI uint32_t tsRadixSort_getMaxRegions(const RadixSort &self) {
		return self.getMaxRegions();
	}
	TS_JSAPI PrefixScan *tsRadixSort_getPrefixScan(const RadixSort &self) {
		return new PrefixScan(self.getPrefixScan());
	}
	TS_JSAPI Buffer *tsRadixSort_getDataBuffer(const RadixSort &self) {
		return new Buffer(self.getDataBuffer());
	}
	TS_JSAPI bool tsRadixSort_create(RadixSort &self, const Device &device, uint32_t mode, PrefixScan &scan, uint32_t size, uint32_t groups, uint32_t regions, Async *async) {
		return self.create(device, (RadixSort::Mode)mode, scan, size, groups, regions, async);
	}
	TS_JSAPI bool tsRadixSort_create_1(RadixSort &self, const Device &device, uint32_t flags, PrefixScan &scan, uint32_t size, uint32_t groups, uint32_t regions, Async *async) {
		return self.create(device, (RadixSort::Flags)flags, scan, size, groups, regions, async);
	}
	TS_JSAPI bool tsRadixSort_dispatch(RadixSort &self, Compute &compute, Buffer &data, uint32_t keys_offset, uint32_t data_offset, uint32_t size, uint32_t flags, uint32_t bits) {
		return self.dispatch(compute, data, keys_offset, data_offset, size, (RadixSort::Flags)flags, bits);
	}
	TS_JSAPI bool tsRadixSort_dispatch_1(RadixSort &self, Compute &compute, Buffer &data, uint32_t count, const uint32_t *keys_offsets, const uint32_t *data_offsets, const uint32_t *sizes, uint32_t flags, uint32_t bits) {
		return self.dispatch(compute, data, count, keys_offsets, data_offsets, sizes, (RadixSort::Flags)flags, bits);
	}
	TS_JSAPI bool tsRadixSort_dispatchIndirect(RadixSort &self, Compute &compute, Buffer &data, Buffer &dispatch, uint32_t offset, uint32_t flags, uint32_t bits, uint32_t max_size) {
		return self.dispatchIndirect(compute, data, dispatch, offset, (RadixSort::Flags)flags, bits, max_size);
	}
	TS_JSAPI bool tsRadixSort_dispatchIndirect_1(RadixSort &self, Compute &compute, Buffer &data, uint32_t count, Buffer &dispatch, uint32_t offset, uint32_t flags, uint32_t bits, uint32_t max_size) {
		return self.dispatchIndirect(compute, data, count, dispatch, offset, (RadixSort::Flags)flags, bits, max_size);
	}
	TS_JSAPI bool tsRadixSort_dispatchIndirect_2(RadixSort &self, Compute &compute, Buffer &data, Buffer &count, Buffer &dispatch, uint32_t count_offset, uint32_t dispatch_offset, uint32_t flags, uint32_t bits, uint32_t max_size) {
		return self.dispatchIndirect(compute, data, count, dispatch, count_offset, dispatch_offset, (RadixSort::Flags)flags, bits, max_size);
	}
	
	// Tellusim::BitonicSort::DispatchParameters
	TS_JSAPI BitonicSort::DispatchParameters *tsBitonicSortDispatchParameters_new() {
		return new BitonicSort::DispatchParameters();
	}
	TS_JSAPI BitonicSort::DispatchParameters *tsBitonicSortDispatchParameters_copy(const BitonicSort::DispatchParameters &self) {
		return new BitonicSort::DispatchParameters(self);
	}
	TS_JSAPI void tsBitonicSortDispatchParameters_delete(BitonicSort::DispatchParameters *self) {
		delete self;
	}
	TS_JSAPI void tsBitonicSortDispatchParameters_set_keys_offset(BitonicSort::DispatchParameters &self, uint32_t keys_offset) {
		self.keys_offset = keys_offset;
	}
	TS_JSAPI uint32_t tsBitonicSortDispatchParameters_get_keys_offset(const BitonicSort::DispatchParameters &self) {
		return self.keys_offset;
	}
	TS_JSAPI void tsBitonicSortDispatchParameters_set_data_offset(BitonicSort::DispatchParameters &self, uint32_t data_offset) {
		self.data_offset = data_offset;
	}
	TS_JSAPI uint32_t tsBitonicSortDispatchParameters_get_data_offset(const BitonicSort::DispatchParameters &self) {
		return self.data_offset;
	}
	TS_JSAPI void tsBitonicSortDispatchParameters_set_size(BitonicSort::DispatchParameters &self, uint32_t size) {
		self.size = size;
	}
	TS_JSAPI uint32_t tsBitonicSortDispatchParameters_get_size(const BitonicSort::DispatchParameters &self) {
		return self.size;
	}
	
	// Tellusim::BitonicSort
	TS_JSAPI BitonicSort *tsBitonicSort_new() {
		return new BitonicSort();
	}
	TS_JSAPI void tsBitonicSort_delete(BitonicSort *self) {
		delete self;
	}
	TS_JSAPI bool tsBitonicSort_equalPtr(const BitonicSort &self, const BitonicSort &ptr) {
		return (self == ptr);
	}
	TS_JSAPI BitonicSort *tsBitonicSort_clonePtr(const BitonicSort &self) {
		return new BitonicSort(self.clonePtr());
	}
	TS_JSAPI void tsBitonicSort_clearPtr(BitonicSort &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsBitonicSort_destroyPtr(BitonicSort &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsBitonicSort_acquirePtr(BitonicSort &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsBitonicSort_unacquirePtr(BitonicSort &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsBitonicSort_isValidPtr(const BitonicSort &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsBitonicSort_isOwnerPtr(const BitonicSort &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsBitonicSort_isConstPtr(const BitonicSort &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsBitonicSort_getCountPtr(const BitonicSort &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsBitonicSort_getInternalPtr(const BitonicSort &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsBitonicSort_clear(BitonicSort &self) {
		self.clear();
	}
	TS_JSAPI bool tsBitonicSort_isCreated(const BitonicSort &self, uint32_t flags) {
		return self.isCreated((BitonicSort::Flags)flags);
	}
	TS_JSAPI uint32_t tsBitonicSort_getDataSize(const BitonicSort &self) {
		return self.getDataSize();
	}
	TS_JSAPI uint32_t tsBitonicSort_getGroupSize(const BitonicSort &self) {
		return self.getGroupSize();
	}
	TS_JSAPI uint32_t tsBitonicSort_getSortElements(const BitonicSort &self) {
		return self.getSortElements();
	}
	TS_JSAPI uint32_t tsBitonicSort_getMaxRegions(const BitonicSort &self) {
		return self.getMaxRegions();
	}
	TS_JSAPI bool tsBitonicSort_create(BitonicSort &self, const Device &device, uint32_t mode, uint32_t size, uint32_t groups, uint32_t regions, Async *async) {
		return self.create(device, (BitonicSort::Mode)mode, size, groups, regions, async);
	}
	TS_JSAPI bool tsBitonicSort_create_1(BitonicSort &self, const Device &device, uint32_t flags, uint32_t size, uint32_t groups, uint32_t regions, Async *async) {
		return self.create(device, (BitonicSort::Flags)flags, size, groups, regions, async);
	}
	TS_JSAPI bool tsBitonicSort_dispatch(BitonicSort &self, Compute &compute, Buffer &data, uint32_t keys_offset, uint32_t data_offset, uint32_t size, uint32_t flags) {
		return self.dispatch(compute, data, keys_offset, data_offset, size, (BitonicSort::Flags)flags);
	}
	TS_JSAPI bool tsBitonicSort_dispatch_1(BitonicSort &self, Compute &compute, Buffer &data, uint32_t count, const uint32_t *keys_offsets, const uint32_t *data_offsets, const uint32_t *sizes, uint32_t flags) {
		return self.dispatch(compute, data, count, keys_offsets, data_offsets, sizes, (BitonicSort::Flags)flags);
	}
	TS_JSAPI bool tsBitonicSort_dispatchIndirect(BitonicSort &self, Compute &compute, Buffer &data, Buffer &dispatch, uint32_t offset, uint32_t flags) {
		return self.dispatchIndirect(compute, data, dispatch, offset, (BitonicSort::Flags)flags);
	}
	TS_JSAPI bool tsBitonicSort_dispatchIndirect_1(BitonicSort &self, Compute &compute, Buffer &data, uint32_t count, Buffer &dispatch, uint32_t offset, uint32_t flags) {
		return self.dispatchIndirect(compute, data, count, dispatch, offset, (BitonicSort::Flags)flags);
	}
	TS_JSAPI bool tsBitonicSort_dispatchIndirect_2(BitonicSort &self, Compute &compute, Buffer &data, Buffer &count, Buffer &dispatch, uint32_t count_offset, uint32_t dispatch_offset, uint32_t flags) {
		return self.dispatchIndirect(compute, data, count, dispatch, count_offset, dispatch_offset, (BitonicSort::Flags)flags);
	}
	
	// Tellusim::SpatialGrid::DispatchParameters
	TS_JSAPI SpatialGrid::DispatchParameters *tsSpatialGridDispatchParameters_new() {
		return new SpatialGrid::DispatchParameters();
	}
	TS_JSAPI SpatialGrid::DispatchParameters *tsSpatialGridDispatchParameters_copy(const SpatialGrid::DispatchParameters &self) {
		return new SpatialGrid::DispatchParameters(self);
	}
	TS_JSAPI void tsSpatialGridDispatchParameters_delete(SpatialGrid::DispatchParameters *self) {
		delete self;
	}
	TS_JSAPI void tsSpatialGridDispatchParameters_set_offset(SpatialGrid::DispatchParameters &self, uint32_t offset) {
		self.offset = offset;
	}
	TS_JSAPI uint32_t tsSpatialGridDispatchParameters_get_offset(const SpatialGrid::DispatchParameters &self) {
		return self.offset;
	}
	TS_JSAPI void tsSpatialGridDispatchParameters_set_size(SpatialGrid::DispatchParameters &self, uint32_t size) {
		self.size = size;
	}
	TS_JSAPI uint32_t tsSpatialGridDispatchParameters_get_size(const SpatialGrid::DispatchParameters &self) {
		return self.size;
	}
	
	// Tellusim::SpatialGrid
	TS_JSAPI SpatialGrid *tsSpatialGrid_new() {
		return new SpatialGrid();
	}
	TS_JSAPI void tsSpatialGrid_delete(SpatialGrid *self) {
		delete self;
	}
	TS_JSAPI bool tsSpatialGrid_equalPtr(const SpatialGrid &self, const SpatialGrid &ptr) {
		return (self == ptr);
	}
	TS_JSAPI SpatialGrid *tsSpatialGrid_clonePtr(const SpatialGrid &self) {
		return new SpatialGrid(self.clonePtr());
	}
	TS_JSAPI void tsSpatialGrid_clearPtr(SpatialGrid &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsSpatialGrid_destroyPtr(SpatialGrid &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsSpatialGrid_acquirePtr(SpatialGrid &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsSpatialGrid_unacquirePtr(SpatialGrid &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsSpatialGrid_isValidPtr(const SpatialGrid &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsSpatialGrid_isOwnerPtr(const SpatialGrid &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsSpatialGrid_isConstPtr(const SpatialGrid &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsSpatialGrid_getCountPtr(const SpatialGrid &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsSpatialGrid_getInternalPtr(const SpatialGrid &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsSpatialGrid_clear(SpatialGrid &self) {
		self.clear();
	}
	TS_JSAPI bool tsSpatialGrid_isCreated(const SpatialGrid &self) {
		return self.isCreated();
	}
	TS_JSAPI uint32_t tsSpatialGrid_getGroupSize(const SpatialGrid &self) {
		return self.getGroupSize();
	}
	TS_JSAPI RadixSort *tsSpatialGrid_getRadixSort(const SpatialGrid &self) {
		return new RadixSort(self.getRadixSort());
	}
	TS_JSAPI bool tsSpatialGrid_create(SpatialGrid &self, const Device &device, RadixSort &sort, uint32_t groups) {
		return self.create(device, sort, groups);
	}
	TS_JSAPI bool tsSpatialGrid_dispatch(SpatialGrid &self, Compute &compute, Buffer &data, uint32_t offset, uint32_t size, uint32_t bits) {
		return self.dispatch(compute, data, offset, size, bits);
	}
	TS_JSAPI bool tsSpatialGrid_dispatchIndirect(SpatialGrid &self, Compute &compute, Buffer &data, Buffer &dispatch, uint32_t offset, uint32_t max_size) {
		return self.dispatchIndirect(compute, data, dispatch, offset, max_size);
	}
	
	// Tellusim::SpatialTree::Node
	TS_JSAPI SpatialTree::Node *tsSpatialTreeNode_new() {
		return new SpatialTree::Node();
	}
	TS_JSAPI SpatialTree::Node *tsSpatialTreeNode_copy(const SpatialTree::Node &self) {
		return new SpatialTree::Node(self);
	}
	TS_JSAPI void tsSpatialTreeNode_delete(SpatialTree::Node *self) {
		delete self;
	}
	TS_JSAPI void tsSpatialTreeNode_set_bound_min(SpatialTree::Node &self, const Vector3f &bound_min) {
		bound_min.get(self.bound_min);
	}
	TS_JSAPI Vector3f *tsSpatialTreeNode_get_bound_min(const SpatialTree::Node &self) {
		return new Vector3f(self.bound_min);
	}
	TS_JSAPI void tsSpatialTreeNode_set_is_enabled(SpatialTree::Node &self, uint32_t is_enabled) {
		self.is_enabled = is_enabled;
	}
	TS_JSAPI uint32_t tsSpatialTreeNode_get_is_enabled(const SpatialTree::Node &self) {
		return self.is_enabled;
	}
	TS_JSAPI void tsSpatialTreeNode_set_bound_max(SpatialTree::Node &self, const Vector3f &bound_max) {
		bound_max.get(self.bound_max);
	}
	TS_JSAPI Vector3f *tsSpatialTreeNode_get_bound_max(const SpatialTree::Node &self) {
		return new Vector3f(self.bound_max);
	}
	TS_JSAPI void tsSpatialTreeNode_set_data(SpatialTree::Node &self, uint32_t data) {
		self.data = data;
	}
	TS_JSAPI uint32_t tsSpatialTreeNode_get_data(const SpatialTree::Node &self) {
		return self.data;
	}
	TS_JSAPI void tsSpatialTreeNode_set_left(SpatialTree::Node &self, uint32_t left) {
		self.left = left;
	}
	TS_JSAPI uint32_t tsSpatialTreeNode_get_left(const SpatialTree::Node &self) {
		return self.left;
	}
	TS_JSAPI void tsSpatialTreeNode_set_right(SpatialTree::Node &self, uint32_t right) {
		self.right = right;
	}
	TS_JSAPI uint32_t tsSpatialTreeNode_get_right(const SpatialTree::Node &self) {
		return self.right;
	}
	TS_JSAPI void tsSpatialTreeNode_set_parent(SpatialTree::Node &self, uint32_t parent) {
		self.parent = parent;
	}
	TS_JSAPI uint32_t tsSpatialTreeNode_get_parent(const SpatialTree::Node &self) {
		return self.parent;
	}
	TS_JSAPI void tsSpatialTreeNode_set_spatial(SpatialTree::Node &self, uint32_t spatial) {
		self.spatial = spatial;
	}
	TS_JSAPI uint32_t tsSpatialTreeNode_get_spatial(const SpatialTree::Node &self) {
		return self.spatial;
	}
	// Tellusim::SpatialTree::LeafNodef16
	TS_JSAPI SpatialTree::LeafNodef16 *tsSpatialTreeLeafNodef16_new() {
		return new SpatialTree::LeafNodef16();
	}
	TS_JSAPI SpatialTree::LeafNodef16 *tsSpatialTreeLeafNodef16_copy(const SpatialTree::LeafNodef16 &self) {
		return new SpatialTree::LeafNodef16(self);
	}
	TS_JSAPI void tsSpatialTreeLeafNodef16_delete(SpatialTree::LeafNodef16 *self) {
		delete self;
	}
	TS_JSAPI void tsSpatialTreeLeafNodef16_set_center(SpatialTree::LeafNodef16 &self, const Vector3f &center) {
		center.get(self.center);
	}
	TS_JSAPI Vector3f *tsSpatialTreeLeafNodef16_get_center(const SpatialTree::LeafNodef16 &self) {
		return new Vector3f(self.center);
	}
	TS_JSAPI void tsSpatialTreeLeafNodef16_set_data(SpatialTree::LeafNodef16 &self, uint32_t data) {
		self.data = data;
	}
	TS_JSAPI uint32_t tsSpatialTreeLeafNodef16_get_data(const SpatialTree::LeafNodef16 &self) {
		return self.data;
	}
	TS_JSAPI void tsSpatialTreeLeafNodef16_set_is_enabled(SpatialTree::LeafNodef16 &self, uint16_t is_enabled) {
		self.is_enabled = is_enabled;
	}
	TS_JSAPI uint16_t tsSpatialTreeLeafNodef16_get_is_enabled(const SpatialTree::LeafNodef16 &self) {
		return self.is_enabled;
	}
	TS_JSAPI void tsSpatialTreeLeafNodef16_set_data_1(SpatialTree::LeafNodef16 &self, uint32_t data_1) {
		self.data_1 = data_1;
	}
	TS_JSAPI uint32_t tsSpatialTreeLeafNodef16_get_data_1(const SpatialTree::LeafNodef16 &self) {
		return self.data_1;
	}
	TS_JSAPI void tsSpatialTreeLeafNodef16_set_data_2(SpatialTree::LeafNodef16 &self, uint32_t data_2) {
		self.data_2 = data_2;
	}
	TS_JSAPI uint32_t tsSpatialTreeLeafNodef16_get_data_2(const SpatialTree::LeafNodef16 &self) {
		return self.data_2;
	}
	TS_JSAPI void tsSpatialTreeLeafNodef16_set_left(SpatialTree::LeafNodef16 &self, uint32_t left) {
		self.left = left;
	}
	TS_JSAPI uint32_t tsSpatialTreeLeafNodef16_get_left(const SpatialTree::LeafNodef16 &self) {
		return self.left;
	}
	TS_JSAPI void tsSpatialTreeLeafNodef16_set_right(SpatialTree::LeafNodef16 &self, uint32_t right) {
		self.right = right;
	}
	TS_JSAPI uint32_t tsSpatialTreeLeafNodef16_get_right(const SpatialTree::LeafNodef16 &self) {
		return self.right;
	}
	TS_JSAPI void tsSpatialTreeLeafNodef16_set_parent(SpatialTree::LeafNodef16 &self, uint32_t parent) {
		self.parent = parent;
	}
	TS_JSAPI uint32_t tsSpatialTreeLeafNodef16_get_parent(const SpatialTree::LeafNodef16 &self) {
		return self.parent;
	}
	TS_JSAPI void tsSpatialTreeLeafNodef16_set_spatial(SpatialTree::LeafNodef16 &self, uint32_t spatial) {
		self.spatial = spatial;
	}
	TS_JSAPI uint32_t tsSpatialTreeLeafNodef16_get_spatial(const SpatialTree::LeafNodef16 &self) {
		return self.spatial;
	}
	// Tellusim::SpatialTree::DispatchParameters
	TS_JSAPI SpatialTree::DispatchParameters *tsSpatialTreeDispatchParameters_new() {
		return new SpatialTree::DispatchParameters();
	}
	TS_JSAPI SpatialTree::DispatchParameters *tsSpatialTreeDispatchParameters_copy(const SpatialTree::DispatchParameters &self) {
		return new SpatialTree::DispatchParameters(self);
	}
	TS_JSAPI void tsSpatialTreeDispatchParameters_delete(SpatialTree::DispatchParameters *self) {
		delete self;
	}
	TS_JSAPI void tsSpatialTreeDispatchParameters_set_offset(SpatialTree::DispatchParameters &self, uint32_t offset) {
		self.offset = offset;
	}
	TS_JSAPI uint32_t tsSpatialTreeDispatchParameters_get_offset(const SpatialTree::DispatchParameters &self) {
		return self.offset;
	}
	TS_JSAPI void tsSpatialTreeDispatchParameters_set_size(SpatialTree::DispatchParameters &self, uint32_t size) {
		self.size = size;
	}
	TS_JSAPI uint32_t tsSpatialTreeDispatchParameters_get_size(const SpatialTree::DispatchParameters &self) {
		return self.size;
	}
	
	// Tellusim::SpatialTree
	TS_JSAPI SpatialTree *tsSpatialTree_new() {
		return new SpatialTree();
	}
	TS_JSAPI void tsSpatialTree_delete(SpatialTree *self) {
		delete self;
	}
	TS_JSAPI bool tsSpatialTree_equalPtr(const SpatialTree &self, const SpatialTree &ptr) {
		return (self == ptr);
	}
	TS_JSAPI SpatialTree *tsSpatialTree_clonePtr(const SpatialTree &self) {
		return new SpatialTree(self.clonePtr());
	}
	TS_JSAPI void tsSpatialTree_clearPtr(SpatialTree &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsSpatialTree_destroyPtr(SpatialTree &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsSpatialTree_acquirePtr(SpatialTree &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsSpatialTree_unacquirePtr(SpatialTree &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsSpatialTree_isValidPtr(const SpatialTree &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsSpatialTree_isOwnerPtr(const SpatialTree &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsSpatialTree_isConstPtr(const SpatialTree &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsSpatialTree_getCountPtr(const SpatialTree &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsSpatialTree_getInternalPtr(const SpatialTree &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsSpatialTree_clear(SpatialTree &self) {
		self.clear();
	}
	TS_JSAPI bool tsSpatialTree_isCreated(const SpatialTree &self, uint32_t flags) {
		return self.isCreated((SpatialTree::Flags)flags);
	}
	TS_JSAPI uint32_t tsSpatialTree_getGroupSize(const SpatialTree &self) {
		return self.getGroupSize();
	}
	TS_JSAPI uint32_t tsSpatialTree_getBoundsNodes(const SpatialTree &self) {
		return self.getBoundsNodes();
	}
	TS_JSAPI uint32_t tsSpatialTree_getMaxNodes(const SpatialTree &self) {
		return self.getMaxNodes();
	}
	TS_JSAPI uint32_t tsSpatialTree_getMaxRegions(const SpatialTree &self) {
		return self.getMaxRegions();
	}
	TS_JSAPI RadixSort *tsSpatialTree_getRadixSort(const SpatialTree &self) {
		return new RadixSort(self.getRadixSort());
	}
	TS_JSAPI Buffer *tsSpatialTree_getHashBuffer(const SpatialTree &self) {
		return new Buffer(self.getHashBuffer());
	}
	TS_JSAPI Buffer *tsSpatialTree_getParentsBuffer(const SpatialTree &self) {
		return new Buffer(self.getParentsBuffer());
	}
	TS_JSAPI Buffer *tsSpatialTree_getCounterBuffer(const SpatialTree &self) {
		return new Buffer(self.getCounterBuffer());
	}
	TS_JSAPI bool tsSpatialTree_create(SpatialTree &self, const Device &device, uint32_t mode, RadixSort &sort, uint32_t size, uint32_t groups, uint32_t regions, Async *async) {
		return self.create(device, (SpatialTree::Mode)mode, sort, size, groups, regions, async);
	}
	TS_JSAPI bool tsSpatialTree_create_1(SpatialTree &self, const Device &device, uint32_t flags, RadixSort &sort, uint32_t size, uint32_t groups, uint32_t regions, Async *async) {
		return self.create(device, (SpatialTree::Flags)flags, sort, size, groups, regions, async);
	}
	TS_JSAPI bool tsSpatialTree_dispatch(SpatialTree &self, Compute &compute, uint32_t hash, Buffer &nodes, uint32_t offset, uint32_t size, uint32_t flags) {
		return self.dispatch(compute, (SpatialTree::Hash)hash, nodes, offset, size, (SpatialTree::Flags)flags);
	}
	TS_JSAPI bool tsSpatialTree_dispatch_1(SpatialTree &self, Compute &compute, uint32_t hash, Buffer &nodes, uint32_t count, const uint32_t *offsets, const uint32_t *sizes, uint32_t flags) {
		return self.dispatch(compute, (SpatialTree::Hash)hash, nodes, count, offsets, sizes, (SpatialTree::Flags)flags);
	}
	TS_JSAPI bool tsSpatialTree_dispatchIndirect(SpatialTree &self, Compute &compute, uint32_t hash, Buffer &nodes, Buffer &dispatch, uint32_t offset, uint32_t max_size, uint32_t flags) {
		return self.dispatchIndirect(compute, (SpatialTree::Hash)hash, nodes, dispatch, offset, max_size, (SpatialTree::Flags)flags);
	}
	TS_JSAPI bool tsSpatialTree_dispatchIndirect_1(SpatialTree &self, Compute &compute, uint32_t hash, Buffer &nodes, uint32_t count, Buffer &dispatch, uint32_t offset, uint32_t max_size, uint32_t flags) {
		return self.dispatchIndirect(compute, (SpatialTree::Hash)hash, nodes, count, dispatch, offset, max_size, (SpatialTree::Flags)flags);
	}
	
	// Tellusim::FourierTransform
	TS_JSAPI FourierTransform *tsFourierTransform_new() {
		return new FourierTransform();
	}
	TS_JSAPI void tsFourierTransform_delete(FourierTransform *self) {
		delete self;
	}
	TS_JSAPI bool tsFourierTransform_equalPtr(const FourierTransform &self, const FourierTransform &ptr) {
		return (self == ptr);
	}
	TS_JSAPI FourierTransform *tsFourierTransform_clonePtr(const FourierTransform &self) {
		return new FourierTransform(self.clonePtr());
	}
	TS_JSAPI void tsFourierTransform_clearPtr(FourierTransform &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsFourierTransform_destroyPtr(FourierTransform &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsFourierTransform_acquirePtr(FourierTransform &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsFourierTransform_unacquirePtr(FourierTransform &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsFourierTransform_isValidPtr(const FourierTransform &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsFourierTransform_isOwnerPtr(const FourierTransform &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsFourierTransform_isConstPtr(const FourierTransform &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsFourierTransform_getCountPtr(const FourierTransform &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsFourierTransform_getInternalPtr(const FourierTransform &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsFourierTransform_clear(FourierTransform &self) {
		self.clear();
	}
	TS_JSAPI bool tsFourierTransform_isCreated(const FourierTransform &self, uint32_t mode) {
		return self.isCreated((FourierTransform::Mode)mode);
	}
	TS_JSAPI bool tsFourierTransform_isCreated_1(const FourierTransform &self, uint32_t flags) {
		return self.isCreated((FourierTransform::Flags)flags);
	}
	TS_JSAPI uint32_t tsFourierTransform_getMaxWidth(const FourierTransform &self) {
		return self.getMaxWidth();
	}
	TS_JSAPI uint32_t tsFourierTransform_getMaxHeight(const FourierTransform &self) {
		return self.getMaxHeight();
	}
	TS_JSAPI uint32_t tsFourierTransform_getAlignedSize(const FourierTransform &self, uint32_t size) {
		return self.getAlignedSize(size);
	}
	TS_JSAPI bool tsFourierTransform_create(FourierTransform &self, const Device &device, uint32_t mode, uint32_t width, uint32_t height, Async *async) {
		return self.create(device, (FourierTransform::Mode)mode, width, height, async);
	}
	TS_JSAPI bool tsFourierTransform_create_1(FourierTransform &self, const Device &device, uint32_t flags, uint32_t width, uint32_t height, Async *async) {
		return self.create(device, (FourierTransform::Flags)flags, width, height, async);
	}
	TS_JSAPI bool tsFourierTransform_dispatch(const FourierTransform &self, Compute &compute, uint32_t mode, uint32_t op, Texture &dest, Texture &src, const Slice &dest_slice, const Slice &src_slice) {
		return self.dispatch(compute, (FourierTransform::Mode)mode, (FourierTransform::Operation)op, dest, src, dest_slice, src_slice);
	}
	TS_JSAPI bool tsFourierTransform_dispatch_1(const FourierTransform &self, Compute &compute, uint32_t mode, uint32_t op, Texture &dest, Texture &src, const Slice &src_slice) {
		return self.dispatch(compute, (FourierTransform::Mode)mode, (FourierTransform::Operation)op, dest, src, src_slice);
	}
	TS_JSAPI bool tsFourierTransform_dispatch_2(const FourierTransform &self, Compute &compute, uint32_t mode, uint32_t op, Texture &dest, Texture &src) {
		return self.dispatch(compute, (FourierTransform::Mode)mode, (FourierTransform::Operation)op, dest, src);
	}
	
	// Tellusim::TensorGraph
	TS_JSAPI TensorGraph *tsTensorGraph_new() {
		return new TensorGraph();
	}
	TS_JSAPI void tsTensorGraph_delete(TensorGraph *self) {
		delete self;
	}
	TS_JSAPI bool tsTensorGraph_equalPtr(const TensorGraph &self, const TensorGraph &ptr) {
		return (self == ptr);
	}
	TS_JSAPI TensorGraph *tsTensorGraph_clonePtr(const TensorGraph &self) {
		return new TensorGraph(self.clonePtr());
	}
	TS_JSAPI void tsTensorGraph_clearPtr(TensorGraph &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsTensorGraph_destroyPtr(TensorGraph &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsTensorGraph_acquirePtr(TensorGraph &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsTensorGraph_unacquirePtr(TensorGraph &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsTensorGraph_isValidPtr(const TensorGraph &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsTensorGraph_isOwnerPtr(const TensorGraph &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsTensorGraph_isConstPtr(const TensorGraph &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsTensorGraph_getCountPtr(const TensorGraph &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsTensorGraph_getInternalPtr(const TensorGraph &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI void tsTensorGraph_clear(TensorGraph &self) {
		self.clear();
	}
	TS_JSAPI bool tsTensorGraph_isCreated(const TensorGraph &self) {
		return self.isCreated();
	}
	TS_JSAPI bool tsTensorGraph_create(TensorGraph &self, const Device &device, uint32_t flags, uint32_t masks, Async *async) {
		return self.create(device, (TensorGraph::Flags)flags, (TensorGraph::Masks)masks, async);
	}
	TS_JSAPI bool tsTensorGraph_dispatch(const TensorGraph &self, Compute &compute, uint32_t op, const Tensor &dest, uint32_t flags) {
		return self.dispatch(compute, (TensorGraph::Operation)op, dest, (TensorGraph::Flags)flags);
	}
	TS_JSAPI bool tsTensorGraph_dispatch_1(const TensorGraph &self, Compute &compute, uint32_t op, Tensor &dest, const Tensor &src_0, uint32_t flags) {
		return self.dispatch(compute, (TensorGraph::Operation)op, dest, src_0, (TensorGraph::Flags)flags);
	}
	TS_JSAPI bool tsTensorGraph_dispatch_2(const TensorGraph &self, Compute &compute, uint32_t op, Tensor &dest, const Tensor &src_0, const Tensor &src_1, uint32_t flags) {
		return self.dispatch(compute, (TensorGraph::Operation)op, dest, src_0, src_1, (TensorGraph::Flags)flags);
	}
	TS_JSAPI bool tsTensorGraph_dispatch_3(const TensorGraph &self, Compute &compute, uint32_t op, Tensor &dest, const Tensor &src_0, const Tensor &src_1, const Tensor &src_2, uint32_t flags) {
		return self.dispatch(compute, (TensorGraph::Operation)op, dest, src_0, src_1, src_2, (TensorGraph::Flags)flags);
	}
	TS_JSAPI bool tsTensorGraph_dispatch_4(const TensorGraph &self, Compute &compute, const Tensor &dest, Texture &src, const Region &region, const Slice &slice) {
		return self.dispatch(compute, dest, src, region, slice);
	}
	TS_JSAPI bool tsTensorGraph_dispatch_5(const TensorGraph &self, Compute &compute, const Tensor &dest, Texture &src, const Slice &slice) {
		return self.dispatch(compute, dest, src, slice);
	}
	TS_JSAPI bool tsTensorGraph_dispatch_6(const TensorGraph &self, Compute &compute, Texture &dest, const Tensor &src, const Region &region, const Slice &slice) {
		return self.dispatch(compute, dest, src, region, slice);
	}
	TS_JSAPI bool tsTensorGraph_dispatch_7(const TensorGraph &self, Compute &compute, Texture &dest, const Tensor &src, const Slice &slice) {
		return self.dispatch(compute, dest, src, slice);
	}
	
	// Tellusim::Controller
	static void controller_button_pressed_callback(Controller controller, Controller::Button button, void *self) {
		EM_ASM({ tsController.button_pressed_callback($0, $1, $2); }, self, new Controller(controller), (Controller::Button)button);
	}
	static Controller::ButtonPressedCallback make_controller_button_pressed_callback(void *self) {
		auto ret = makeFunction(controller_button_pressed_callback);
		ret.setArg2(self);
		return ret;
	}
	static void controller_button_released_callback(Controller controller, Controller::Button button, void *self) {
		EM_ASM({ tsController.button_released_callback($0, $1, $2); }, self, new Controller(controller), (Controller::Button)button);
	}
	static Controller::ButtonReleasedCallback make_controller_button_released_callback(void *self) {
		auto ret = makeFunction(controller_button_released_callback);
		ret.setArg2(self);
		return ret;
	}
	static void controller_connected_callback(Controller controller, void *self) {
		EM_ASM({ tsController.connected_callback($0, $1); }, self, new Controller(controller));
	}
	static Controller::ConnectedCallback make_controller_connected_callback(void *self) {
		auto ret = makeFunction(controller_connected_callback);
		ret.setArg1(self);
		return ret;
	}
	static void controller_disconnected_callback(Controller controller, void *self) {
		EM_ASM({ tsController.disconnected_callback($0, $1); }, self, new Controller(controller));
	}
	static Controller::DisconnectedCallback make_controller_disconnected_callback(void *self) {
		auto ret = makeFunction(controller_disconnected_callback);
		ret.setArg1(self);
		return ret;
	}
	TS_JSAPI Controller *tsController_new() {
		return new Controller();
	}
	TS_JSAPI Controller *tsController_new_1(uint32_t index) {
		return new Controller(index);
	}
	TS_JSAPI Controller *tsController_new_2(uint32_t type, uint32_t index) {
		return new Controller((Controller::Type)type, index);
	}
	TS_JSAPI void tsController_delete(Controller *self) {
		delete self;
	}
	TS_JSAPI bool tsController_equalPtr(const Controller &self, const Controller &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Controller *tsController_clonePtr(const Controller &self) {
		return new Controller(self.clonePtr());
	}
	TS_JSAPI void tsController_clearPtr(Controller &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsController_destroyPtr(Controller &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsController_acquirePtr(Controller &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsController_unacquirePtr(Controller &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsController_isValidPtr(const Controller &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsController_isOwnerPtr(const Controller &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsController_isConstPtr(const Controller &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsController_getCountPtr(const Controller &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsController_getInternalPtr(const Controller &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI uint32_t tsController_getNumControllers() {
		return Controller::getNumControllers();
	}
	TS_JSAPI uint32_t tsController_findController(const char *name) {
		return Controller::findController(name);
	}
	TS_JSAPI Controller *tsController_getController(uint32_t index) {
		return new Controller(Controller::getController(index));
	}
	TS_JSAPI void tsController_update() {
		Controller::update();
	}
	TS_JSAPI void tsController_setType(Controller &self, uint32_t type) {
		self.setType((Controller::Type)type);
	}
	TS_JSAPI uint32_t tsController_getType(const Controller &self) {
		return self.getType();
	}
	TS_JSAPI const char* tsController_getTypeName(uint32_t type) {
		return Controller::getTypeName((Controller::Type)type);
	}
	TS_JSAPI const char* tsController_getTypeName_1(const Controller &self) {
		return self.getTypeName();
	}
	TS_JSAPI bool tsController_isUnknown(const Controller &self) {
		return self.isUnknown();
	}
	TS_JSAPI bool tsController_isJoystick(const Controller &self) {
		return self.isJoystick();
	}
	TS_JSAPI bool tsController_isGamePad(const Controller &self) {
		return self.isGamePad();
	}
	TS_JSAPI bool tsController_isWheel(const Controller &self) {
		return self.isWheel();
	}
	TS_JSAPI void tsController_setIndex(Controller &self, uint32_t index) {
		self.setIndex(index);
	}
	TS_JSAPI uint32_t tsController_getIndex(const Controller &self) {
		return self.getIndex();
	}
	TS_JSAPI void tsController_setName(Controller &self, const char *name) {
		self.setName(name);
	}
	TS_JSAPI String *tsController_getName(const Controller &self) {
		return new String(self.getName());
	}
	TS_JSAPI void tsController_setModel(Controller &self, const char *model) {
		self.setModel(model);
	}
	TS_JSAPI String *tsController_getModel(const Controller &self) {
		return new String(self.getModel());
	}
	TS_JSAPI bool tsController_isConnected(const Controller &self) {
		return self.isConnected();
	}
	TS_JSAPI bool tsController_wasConnected(const Controller &self) {
		return self.wasConnected();
	}
	TS_JSAPI bool tsController_connect(Controller &self, const char *name) {
		return self.connect(name);
	}
	TS_JSAPI void tsController_release(Controller &self) {
		self.release();
	}
	TS_JSAPI void tsController_setStickName(Controller &self, uint32_t stick, const char *name) {
		self.setStickName((Controller::Stick)stick, name);
	}
	TS_JSAPI String *tsController_getStickName(const Controller &self, uint32_t stick) {
		return new String(self.getStickName((Controller::Stick)stick));
	}
	TS_JSAPI uint32_t tsController_findStick(const Controller &self, const char *name) {
		return self.findStick(name);
	}
	TS_JSAPI void tsController_setStick(Controller &self, uint32_t stick, float32_t x, float32_t y) {
		self.setStick((Controller::Stick)stick, x, y);
	}
	TS_JSAPI float32_t tsController_getStickX(const Controller &self, uint32_t stick) {
		return self.getStickX((Controller::Stick)stick);
	}
	TS_JSAPI float32_t tsController_getStickY(const Controller &self, uint32_t stick) {
		return self.getStickY((Controller::Stick)stick);
	}
	TS_JSAPI void tsController_setAxisName(Controller &self, uint32_t axis, const char *name) {
		self.setAxisName((Controller::Axis)axis, name);
	}
	TS_JSAPI String *tsController_getAxisName(const Controller &self, uint32_t axis) {
		return new String(self.getAxisName((Controller::Axis)axis));
	}
	TS_JSAPI uint32_t tsController_findAxis(const Controller &self, const char *name) {
		return self.findAxis(name);
	}
	TS_JSAPI void tsController_setAxis(Controller &self, uint32_t axis, float32_t value) {
		self.setAxis((Controller::Axis)axis, value);
	}
	TS_JSAPI float32_t tsController_getAxis(const Controller &self, uint32_t axis) {
		return self.getAxis((Controller::Axis)axis);
	}
	TS_JSAPI void tsController_setButtonName(Controller &self, uint32_t button, const char *name) {
		self.setButtonName((Controller::Button)button, name);
	}
	TS_JSAPI String *tsController_getButtonName(const Controller &self, uint32_t button) {
		return new String(self.getButtonName((Controller::Button)button));
	}
	TS_JSAPI uint32_t tsController_findButton(const Controller &self, const char *name) {
		return self.findButton(name);
	}
	TS_JSAPI void tsController_setButton(Controller &self, uint32_t button, bool value) {
		self.setButton((Controller::Button)button, value);
	}
	TS_JSAPI bool tsController_getButton(const Controller &self, uint32_t button, bool clear) {
		return self.getButton((Controller::Button)button, clear);
	}
	TS_JSAPI bool tsController_wasButtonPressed(const Controller &self, uint32_t button) {
		return self.wasButtonPressed((Controller::Button)button);
	}
	TS_JSAPI bool tsController_wasButtonReleased(const Controller &self, uint32_t button) {
		return self.wasButtonReleased((Controller::Button)button);
	}
	TS_JSAPI void tsController_setButtonValue(Controller &self, uint32_t button, float32_t value) {
		self.setButtonValue((Controller::Button)button, value);
	}
	TS_JSAPI float32_t tsController_getButtonValue(const Controller &self, uint32_t button) {
		return self.getButtonValue((Controller::Button)button);
	}
	TS_JSAPI void tsController_setMotorName(Controller &self, uint32_t motor, const char *name) {
		self.setMotorName((Controller::Motor)motor, name);
	}
	TS_JSAPI String *tsController_getMotorName(const Controller &self, uint32_t motor) {
		return new String(self.getMotorName((Controller::Motor)motor));
	}
	TS_JSAPI uint32_t tsController_findMotor(const Controller &self, const char *name) {
		return self.findMotor(name);
	}
	TS_JSAPI void tsController_setMotor(Controller &self, uint32_t motor, float32_t value) {
		self.setMotor((Controller::Motor)motor, value);
	}
	TS_JSAPI float32_t tsController_getMotor(const Controller &self, uint32_t motor) {
		return self.getMotor((Controller::Motor)motor);
	}
	TS_JSAPI void tsController_setButtonPressedCallback(Controller &self, bool func) {
		self.setButtonPressedCallback((func) ? make_controller_button_pressed_callback(&self) : Controller::ButtonPressedCallback());
	}
	TS_JSAPI void tsController_setButtonReleasedCallback(Controller &self, bool func) {
		self.setButtonReleasedCallback((func) ? make_controller_button_released_callback(&self) : Controller::ButtonReleasedCallback());
	}
	TS_JSAPI void tsController_setConnectedCallback(Controller &self, bool func) {
		self.setConnectedCallback((func) ? make_controller_connected_callback(&self) : Controller::ConnectedCallback());
	}
	TS_JSAPI void tsController_setDisconnectedCallback(Controller &self, bool func) {
		self.setDisconnectedCallback((func) ? make_controller_disconnected_callback(&self) : Controller::DisconnectedCallback());
	}
	
	// Tellusim::Desktop
	TS_JSAPI Desktop *tsDesktop_new() {
		return new Desktop();
	}
	TS_JSAPI void tsDesktop_delete(Desktop *self) {
		delete self;
	}
	TS_JSAPI bool tsDesktop_equalPtr(const Desktop &self, const Desktop &ptr) {
		return (self == ptr);
	}
	TS_JSAPI Desktop *tsDesktop_clonePtr(const Desktop &self) {
		return new Desktop(self.clonePtr());
	}
	TS_JSAPI void tsDesktop_clearPtr(Desktop &self) {
		self.clearPtr();
	}
	TS_JSAPI void tsDesktop_destroyPtr(Desktop &self) {
		self.destroyPtr();
	}
	TS_JSAPI void tsDesktop_acquirePtr(Desktop &self) {
		self.acquirePtr();
	}
	TS_JSAPI void tsDesktop_unacquirePtr(Desktop &self) {
		self.unacquirePtr();
	}
	TS_JSAPI bool tsDesktop_isValidPtr(const Desktop &self) {
		return self.isValidPtr();
	}
	TS_JSAPI bool tsDesktop_isOwnerPtr(const Desktop &self) {
		return self.isOwnerPtr();
	}
	TS_JSAPI bool tsDesktop_isConstPtr(const Desktop &self) {
		return self.isConstPtr();
	}
	TS_JSAPI uint32_t tsDesktop_getCountPtr(const Desktop &self) {
		return self.getCountPtr();
	}
	TS_JSAPI const void *tsDesktop_getInternalPtr(const Desktop &self) {
		return self.getInternalPtr();
	}
	TS_JSAPI bool tsDesktop_update(Desktop &self) {
		return self.update();
	}
	TS_JSAPI uint32_t tsDesktop_getWidth(const Desktop &self) {
		return self.getWidth();
	}
	TS_JSAPI uint32_t tsDesktop_getHeight(const Desktop &self) {
		return self.getHeight();
	}
	TS_JSAPI int32_t tsDesktop_getPositionX(const Desktop &self) {
		return self.getPositionX();
	}
	TS_JSAPI int32_t tsDesktop_getPositionY(const Desktop &self) {
		return self.getPositionY();
	}
	TS_JSAPI float32_t tsDesktop_getScale(const Desktop &self) {
		return self.getScale();
	}
	TS_JSAPI uint32_t tsDesktop_getNumScreens(const Desktop &self) {
		return self.getNumScreens();
	}
	TS_JSAPI String *tsDesktop_getScreenName(const Desktop &self, uint32_t index) {
		return new String(self.getScreenName(index));
	}
	TS_JSAPI String *tsDesktop_getScreenDevice(const Desktop &self, uint32_t index) {
		return new String(self.getScreenDevice(index));
	}
	TS_JSAPI uint32_t tsDesktop_getScreenWidth(const Desktop &self, uint32_t index) {
		return self.getScreenWidth(index);
	}
	TS_JSAPI uint32_t tsDesktop_getScreenHeight(const Desktop &self, uint32_t index) {
		return self.getScreenHeight(index);
	}
	TS_JSAPI int32_t tsDesktop_getScreenPositionX(const Desktop &self, uint32_t index) {
		return self.getScreenPositionX(index);
	}
	TS_JSAPI int32_t tsDesktop_getScreenPositionY(const Desktop &self, uint32_t index) {
		return self.getScreenPositionY(index);
	}
	TS_JSAPI uint32_t tsDesktop_getScreenFrequency(const Desktop &self, uint32_t index) {
		return self.getScreenFrequency(index);
	}
	TS_JSAPI uint32_t tsDesktop_getNumModes(const Desktop &self, uint32_t index) {
		return self.getNumModes(index);
	}
	TS_JSAPI uint32_t tsDesktop_getModeWidth(const Desktop &self, uint32_t index, uint32_t mode) {
		return self.getModeWidth(index, mode);
	}
	TS_JSAPI uint32_t tsDesktop_getModeHeight(const Desktop &self, uint32_t index, uint32_t mode) {
		return self.getModeHeight(index, mode);
	}
	TS_JSAPI uint32_t tsDesktop_getModeIndex(const Desktop &self, uint32_t index, uint32_t width, uint32_t height) {
		return self.getModeIndex(index, width, height);
	}
	TS_JSAPI bool tsDesktop_setMode(Desktop &self, uint32_t index, uint32_t width, uint32_t height) {
		return self.setMode(index, width, height);
	}
	TS_JSAPI bool tsDesktop_restoreMode(Desktop &self, uint32_t index) {
		return self.restoreMode(index);
	}
	TS_JSAPI uint32_t tsDesktop_getWidth_1(const Desktop &self, uint32_t index) {
		return self.getWidth(index);
	}
	TS_JSAPI uint32_t tsDesktop_getHeight_1(const Desktop &self, uint32_t index) {
		return self.getHeight(index);
	}
	TS_JSAPI int32_t tsDesktop_getPositionX_1(const Desktop &self, uint32_t index) {
		return self.getPositionX(index);
	}
	TS_JSAPI int32_t tsDesktop_getPositionY_1(const Desktop &self, uint32_t index) {
		return self.getPositionY(index);
	}
	TS_JSAPI uint32_t tsDesktop_getScreenIndex(const Desktop &self, int32_t x, int32_t y) {
		return self.getScreenIndex(x, y);
	}
	TS_JSAPI bool tsDesktop_setMouse(const Desktop &self, int32_t x, int32_t y) {
		return self.setMouse(x, y);
	}
	TS_JSAPI bool tsDesktop_getMouse(const Desktop &self, int32_t &x, int32_t &y) {
		return self.getMouse(x, y);
	}
	
	// Tellusim
	TS_JSAPI const char* ts_getPlatformName(uint32_t platform) {
		return getPlatformName((Platform)platform);
	}
	TS_JSAPI uint32_t ts_findPlatformName(const char *name) {
		return findPlatformName(name);
	}
	TS_JSAPI bool ts_isPlatformAvailable(uint32_t platform) {
		return isPlatformAvailable((Platform)platform);
	}
	TS_JSAPI const char* ts_getFormatName(uint32_t format) {
		return getFormatName((Format)format);
	}
	TS_JSAPI uint32_t ts_findFormatName(const char *name) {
		return findFormatName(name);
	}
	TS_JSAPI const char* ts_getGLSLFormatName(uint32_t format) {
		return getGLSLFormatName((Format)format);
	}
	TS_JSAPI uint32_t ts_findGLSLFormatName(const char *name) {
		return findGLSLFormatName(name);
	}
	TS_JSAPI bool ts_isColorFormat(uint32_t format) {
		return isColorFormat((Format)format);
	}
	TS_JSAPI bool ts_isDepthFormat(uint32_t format) {
		return isDepthFormat((Format)format);
	}
	TS_JSAPI bool ts_isPixelFormat(uint32_t format) {
		return isPixelFormat((Format)format);
	}
	TS_JSAPI bool ts_isPlainFormat(uint32_t format) {
		return isPlainFormat((Format)format);
	}
	TS_JSAPI bool ts_isMixedFormat(uint32_t format) {
		return isMixedFormat((Format)format);
	}
	TS_JSAPI bool ts_isBlockFormat(uint32_t format) {
		return isBlockFormat((Format)format);
	}
	TS_JSAPI bool ts_isStencilFormat(uint32_t format) {
		return isStencilFormat((Format)format);
	}
	TS_JSAPI uint32_t ts_toPixelFormat(uint32_t format) {
		return toPixelFormat((Format)format);
	}
	TS_JSAPI bool ts_isNormFormat(uint32_t format) {
		return isNormFormat((Format)format);
	}
	TS_JSAPI bool ts_isSRGBFormat(uint32_t format) {
		return isSRGBFormat((Format)format);
	}
	TS_JSAPI bool ts_isSignedFormat(uint32_t format) {
		return isSignedFormat((Format)format);
	}
	TS_JSAPI bool ts_isUnsignedFormat(uint32_t format) {
		return isUnsignedFormat((Format)format);
	}
	TS_JSAPI bool ts_isIntegerFormat(uint32_t format) {
		return isIntegerFormat((Format)format);
	}
	TS_JSAPI bool ts_isFloatFormat(uint32_t format) {
		return isFloatFormat((Format)format);
	}
	TS_JSAPI uint32_t ts_toNormFormat(uint32_t format) {
		return toNormFormat((Format)format);
	}
	TS_JSAPI uint32_t ts_toSRGBFormat(uint32_t format) {
		return toSRGBFormat((Format)format);
	}
	TS_JSAPI uint32_t ts_toSignedFormat(uint32_t format) {
		return toSignedFormat((Format)format);
	}
	TS_JSAPI uint32_t ts_toUnsignedFormat(uint32_t format) {
		return toUnsignedFormat((Format)format);
	}
	TS_JSAPI uint32_t ts_toFloatFormat(uint32_t format) {
		return toFloatFormat((Format)format);
	}
	TS_JSAPI bool ts_isi8Format(uint32_t format) {
		return isi8Format((Format)format);
	}
	TS_JSAPI bool ts_isu8Format(uint32_t format) {
		return isu8Format((Format)format);
	}
	TS_JSAPI bool ts_is8BitFormat(uint32_t format) {
		return is8BitFormat((Format)format);
	}
	TS_JSAPI uint32_t ts_to8BitFormat(uint32_t format) {
		return to8BitFormat((Format)format);
	}
	TS_JSAPI bool ts_isi16Format(uint32_t format) {
		return isi16Format((Format)format);
	}
	TS_JSAPI bool ts_isu16Format(uint32_t format) {
		return isu16Format((Format)format);
	}
	TS_JSAPI bool ts_isf16Format(uint32_t format) {
		return isf16Format((Format)format);
	}
	TS_JSAPI bool ts_is16BitFormat(uint32_t format) {
		return is16BitFormat((Format)format);
	}
	TS_JSAPI uint32_t ts_to16BitFormat(uint32_t format) {
		return to16BitFormat((Format)format);
	}
	TS_JSAPI bool ts_isi32Format(uint32_t format) {
		return isi32Format((Format)format);
	}
	TS_JSAPI bool ts_isu32Format(uint32_t format) {
		return isu32Format((Format)format);
	}
	TS_JSAPI bool ts_isf32Format(uint32_t format) {
		return isf32Format((Format)format);
	}
	TS_JSAPI bool ts_is32BitFormat(uint32_t format) {
		return is32BitFormat((Format)format);
	}
	TS_JSAPI uint32_t ts_to32BitFormat(uint32_t format) {
		return to32BitFormat((Format)format);
	}
	TS_JSAPI bool ts_isi64Format(uint32_t format) {
		return isi64Format((Format)format);
	}
	TS_JSAPI bool ts_isu64Format(uint32_t format) {
		return isu64Format((Format)format);
	}
	TS_JSAPI bool ts_isf64Format(uint32_t format) {
		return isf64Format((Format)format);
	}
	TS_JSAPI bool ts_is64BitFormat(uint32_t format) {
		return is64BitFormat((Format)format);
	}
	TS_JSAPI bool ts_isBC15Format(uint32_t format) {
		return isBC15Format((Format)format);
	}
	TS_JSAPI bool ts_isBC67Format(uint32_t format) {
		return isBC67Format((Format)format);
	}
	TS_JSAPI bool ts_isETC2Format(uint32_t format) {
		return isETC2Format((Format)format);
	}
	TS_JSAPI bool ts_isASTCFormat(uint32_t format) {
		return isASTCFormat((Format)format);
	}
	TS_JSAPI uint32_t ts_getFormatComponents(uint32_t format) {
		return getFormatComponents((Format)format);
	}
	TS_JSAPI uint32_t ts_toFormatComponents(uint32_t format, uint32_t components) {
		return toFormatComponents((Format)format, components);
	}
	TS_JSAPI uint32_t ts_getFormatPixelSize(uint32_t format) {
		return getFormatPixelSize((Format)format);
	}
	TS_JSAPI uint32_t ts_getFormatBlockSize(uint32_t format) {
		return getFormatBlockSize((Format)format);
	}
	TS_JSAPI uint32_t ts_getFormatBlockWidth(uint32_t format) {
		return getFormatBlockWidth((Format)format);
	}
	TS_JSAPI uint32_t ts_getFormatBlockHeight(uint32_t format) {
		return getFormatBlockHeight((Format)format);
	}
	TS_JSAPI uint32_t ts_getPixelFormatValue(uint32_t format, float32_t value[4], const void *src, uint32_t stride) {
		return getPixelFormatValue((Format)format, value, src, stride);
	}
	TS_JSAPI uint32_t ts_setPixelFormatValue(uint32_t format, void *dest, const float32_t value[4], uint32_t stride) {
		return setPixelFormatValue((Format)format, dest, value, stride);
	}
	
	// Tellusim::Allocator
	TS_JSAPI void* tsAllocator_allocate(size_t size) {
		return Allocator::allocate(size);
	}
	TS_JSAPI void* tsAllocator_reallocate(void *ptr, size_t old_size, size_t new_size) {
		return Allocator::reallocate(ptr, old_size, new_size);
	}
	TS_JSAPI void tsAllocator_free(const void *ptr, size_t size) {
		Allocator::free(ptr, size);
	}
	TS_JSAPI size_t tsAllocator_getMemory() {
		return Allocator::getMemory();
	}
	TS_JSAPI size_t tsAllocator_getAllocations() {
		return Allocator::getAllocations();
	}
	
	// Tellusim::Log
	TS_JSAPI void tsLog_setLevel(uint32_t level) {
		Log::setLevel((Log::Level)level);
	}
	TS_JSAPI uint32_t tsLog_getLevel() {
		return Log::getLevel();
	}
	TS_JSAPI void tsLog_unlockCallback() {
		Log::unlockCallback();
	}
	TS_JSAPI void tsLog_lockCallback() {
		Log::lockCallback();
	}
	TS_JSAPI void tsLog_print(const char *str) {
		Log::print(str);
	}
	TS_JSAPI void tsLog_print_1(uint32_t level, const char *str) {
		Log::print((Log::Level)level, str);
	}
	TS_JSAPI void tsLog_printe(uint32_t level, const char *str) {
		Log::printe((Log::Level)level, str);
	}
	
	// Tellusim::Time
	TS_JSAPI uint64_t tsTime_current() {
		return Time::current();
	}
	TS_JSAPI float64_t tsTime_seconds() {
		return Time::seconds();
	}
	TS_JSAPI void tsTime_sleep(uint32_t usec) {
		Time::sleep(usec);
	}
	
	// Tellusim::System
	TS_JSAPI uint32_t tsSystem_getThreadID() {
		return System::getThreadID();
	}
	TS_JSAPI bool tsSystem_setEnvironment(const char *name, const char *value) {
		return System::setEnvironment(name, value);
	}
	TS_JSAPI bool tsSystem_setEnvironment_1(const String &name, const char *value) {
		return System::setEnvironment(name, value);
	}
	TS_JSAPI String *tsSystem_getEnvironment(const char *name) {
		return new String(System::getEnvironment(name));
	}
	TS_JSAPI String *tsSystem_getEnvironment_1(const String &name) {
		return new String(System::getEnvironment(name));
	}
	TS_JSAPI void* tsSystem_loadLibrary(const char *name) {
		return System::loadLibrary(name);
	}
	TS_JSAPI void* tsSystem_loadLibrary_1(const String &name) {
		return System::loadLibrary(name);
	}
	TS_JSAPI void* tsSystem_getFunction(void *handle, const char *name) {
		return System::getFunction(handle, name);
	}
	TS_JSAPI void* tsSystem_getFunction_1(void *handle, const String &name) {
		return System::getFunction(handle, name);
	}
	TS_JSAPI void tsSystem_closeLibrary(void *handle) {
		System::closeLibrary(handle);
	}
	TS_JSAPI int32_t tsSystem_exec(const char *command, bool wait, bool console) {
		return System::exec(command, wait, console);
	}
	TS_JSAPI int32_t tsSystem_exec_1(const String &command, bool wait, bool console) {
		return System::exec(command, wait, console);
	}
	TS_JSAPI bool tsSystem_open(const char *command) {
		return System::open(command);
	}
	TS_JSAPI bool tsSystem_open_1(const String &command) {
		return System::open(command);
	}
	
	// Tellusim::MeshGraph
	static bool mesh_graph_progress_callback(uint32_t progress) {
		return EM_ASM_INT({ return tsMeshGraph.progress_callback($0); }, progress) != 0;
	}
	TS_JSAPI bool tsMeshGraph_create(Mesh &dest, Mesh &src, uint32_t max_attributes, uint32_t max_primitives, bool func, Async *async) {
		auto func_ts = makeFunction(mesh_graph_progress_callback);
		return MeshGraph::create(dest, src, max_attributes, max_primitives, (func) ? &func_ts : nullptr, async);
	}
	
	// Tellusim::MeshReduce
	static bool mesh_reduce_progress_callback(uint32_t progress) {
		return EM_ASM_INT({ return tsMeshReduce.progress_callback($0); }, progress) != 0;
	}
	TS_JSAPI bool tsMeshReduce_collapse(Mesh &dest, const Mesh &src, float32_t ratio, float32_t threshold, bool func) {
		auto func_ts = makeFunction(mesh_reduce_progress_callback);
		return MeshReduce::collapse(dest, src, ratio, threshold, (func) ? &func_ts : nullptr);
	}
	TS_JSAPI bool tsMeshReduce_collapse_1(MeshGeometry &dest, const MeshGeometry &src, float32_t ratio, float32_t threshold, bool func, uint32_t position) {
		auto func_ts = makeFunction(mesh_reduce_progress_callback);
		return MeshReduce::collapse(dest, src, ratio, threshold, (func) ? &func_ts : nullptr, position);
	}
	
	// Tellusim::MeshRefine
	TS_JSAPI bool tsMeshRefine_subdiv(Mesh &dest, const Mesh &src, uint32_t steps, float32_t weight) {
		return MeshRefine::subdiv(dest, src, steps, weight);
	}
	TS_JSAPI bool tsMeshRefine_subdiv_1(MeshGeometry &dest, const MeshGeometry &src, uint32_t steps, float32_t weight, uint32_t position) {
		return MeshRefine::subdiv(dest, src, steps, weight, position);
	}
	
	// Tellusim::MeshSolid
	static bool mesh_solid_progress_callback(uint32_t progress) {
		return EM_ASM_INT({ return tsMeshSolid.progress_callback($0); }, progress) != 0;
	}
	TS_JSAPI bool tsMeshSolid_create(Mesh &dest, const Mesh &src, float32_t ratio, float32_t threshold, bool func) {
		auto func_ts = makeFunction(mesh_solid_progress_callback);
		return MeshSolid::create(dest, src, ratio, threshold, (func) ? &func_ts : nullptr);
	}
	TS_JSAPI bool tsMeshSolid_create_1(MeshGeometry &dest, const MeshGeometry &src, float32_t ratio, float32_t threshold, bool func, uint32_t position) {
		auto func_ts = makeFunction(mesh_solid_progress_callback);
		return MeshSolid::create(dest, src, ratio, threshold, (func) ? &func_ts : nullptr, position);
	}
	
	} /* extern "C" */
	
} /* namespace Tellusim */

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimTime.h>
#include <core/TellusimDirectory.h>
#include <interface/TellusimDialogs.h>
#if _IOS
	#include <system/TellusimiOS.h>
#elif _ANDROID
	#include <system/TellusimAndroid.h>
#endif

#include "../include/TellusimLogger.h"

/*
 */
#ifndef TS_LOGGER_DATE
	#define TS_LOGGER_DATE "yyyy-MM-dd"
#endif
#ifndef TS_LOGGER_TIME
	#define TS_LOGGER_TIME "HH:mm:ss"
#endif
#ifndef TS_LOGGER_TYPE
	#define TS_LOGGER_TYPE ".log"
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
	Logger::Logger(Flags flags, const char *log_name) : flags(flags) {
		
		// init time
		time = (Time::current() / Time::Seconds) * Time::Seconds;
		
		// log file path
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
		
		// create log file
		if(!log_name || !log_name[0]) log_name = TS_APP_NAME TS_LOGGER_TYPE;
		name = String(log_name);
		if(path) {
			if(!hasFlag(FlagClear) && File::isFile(path + name)) file.open(path + name, "rb+");
			if(!file || !file.isOpened()) file.open(path + name, "wb");
			else file.seekBack(0);
		}
		if(file && file.isOpened()) {
			name = path + name;
		} else {
			path.clear();
			if(!hasFlag(FlagClear) && File::isFile(name)) file.open(name, "rb+");
			if(!file || !file.isOpened()) file.open(name, "wb");
			else file.seekBack(0);
		}
		
		// log delimiter
		if(file && file.isOpened() && file.getSize()) file.puts("\n");
		
		// set log callback
		Log::setCallback(callback, this);
		
		// started message
		if(file && file.isOpened()) {
			String message;
			message = TS_APP_NAME " " TS_APP_VERSION " Started";
			message += Date((int64_t)time / Time::Seconds).getString(" (" TS_LOGGER_DATE " " TS_LOGGER_TIME ")\n");
			file.puts(message.get());
		}
	}
	
	Logger::~Logger() {
		
		// started message
		if(file && file.isOpened()) {
			String message;
			message = TS_APP_NAME " " TS_APP_VERSION " Finished";
			message += Date((int64_t)time / Time::Seconds).getString(" (" TS_LOGGER_DATE " " TS_LOGGER_TIME ")\n");
			file.puts(message.get());
		}
		
		// log callback
		Log::setCallback(nullptr);
		
		// close file
		if(file && file.isOpened()) file.close();
	}
	
	/*
	 */
	void Logger::clearBuffer() {
		AtomicLock atomic(lock);
		buffer.clear();
	}
	
	String Logger::getBuffer() const {
		String ret;
		AtomicLock atomic(lock);
		for(const String &s : buffer) {
			ret += s;
		}
		return ret;
	}
	
	String Logger::getDump() const {
		AtomicLock atomic(lock);
		return dump;
	}
	
	/*
	 */
	bool Logger::callback(Log::Level level, uint64_t time, const char *s, void *data) {
		
		// carriage return
		String str = String(s);
		Logger *log = (Logger*)data;
		if(str && (str.front() == '\r' || str.back() == '\r')) {
			return !log->hasFlag(FlagPrint);
		}
		
		// atomic lock
		AtomicLock atomic(log->lock);
		
		// dump log messages
		if(log->hasFlag(FlagDump)) {
			log->dump += str;
		}
		
		// log buffer
		if(log->buffer.size() > BufferSize) {
			for(uint32_t i = 0; i + 1 < log->buffer.size(); i++) {
				log->buffer[i] = move(log->buffer[i + 1]);
			}
			log->buffer.removeBack();
		}
		log->buffer.append(str);
		
		// file log
		if(log->file && log->file.isOpened()) {
			if(log->hasFlag(FlagDate | FlagTime)) {
				time += log->time;
				Date date = Date((int64_t)(time / Time::Seconds));
				if(log->hasFlags(FlagDate | FlagTime)) log->file.puts(date.getString(TS_LOGGER_DATE " " TS_LOGGER_TIME));
				else if(log->hasFlag(FlagDate)) log->file.puts(date.getString(TS_LOGGER_DATE));
				else if(log->hasFlag(FlagTime)) log->file.puts(date.getString(TS_LOGGER_TIME));
			}
			log->file.printf(" %3u ms: ", (uint32_t)((time / Time::MSeconds) % 1000));
			log->file.puts(str);
			log->file.flush();
		}
		
		// fatal error
		if(level == Log::Fatal) {
			atomic.lock.unlock();
			Log::unlockCallback();
			Log::setCallback(nullptr);
			String message = log->getBuffer().append("\nFatal Error\n");
			DialogMessage dialog(TS_APP_NAME " " TS_APP_VERSION, message);
			dialog.run(DialogMessage::FlagError | DialogMessage::FlagClose);
			if(log->file && log->file.isOpened()) {
				message = TS_APP_NAME " " TS_APP_VERSION " Fatal Error";
				message += Date((int64_t)time / Time::Seconds).getString(" (" TS_LOGGER_DATE " " TS_LOGGER_TIME ")\n");
				log->file.puts(message);
				log->file.close();
			}
			Log::lockCallback();
			atomic.lock.lock();
		}
		
		// print log messages
		return !log->hasFlag(FlagPrint);
	}
}

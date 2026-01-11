// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimBlob.h>
#include <core/TellusimDirectory.h>
#include <format/TellusimArchive.h>

#include "../include/TellusimStreamer.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	Streamer::Streamer(Flags flags) : flags(flags) {
		
		// save callbacks
		open_func = Source::getOpenCallback();
		is_func = Source::getIsCallback();
		
		// save callback data
		callback_data = Source::getCallbackData();
		
		// set source callback
		Source::setCallback(Streamer::open_callback, Streamer::is_callback, this);
	}
	
	Streamer::~Streamer() {
		
		clear();
		
		// restore source callback
		Source::setCallback(open_func, is_func, callback_data);
	}
	
	/*
	 */
	void Streamer::clear() {
		
		AtomicLock atomic(lock);
		
		archives.clear();
		files.clear();
		names.clear();
	}
	
	/*
	 */
	void Streamer::addPrefix(const char *name, const char *value) {
		Prefix &prefix = prefixes.append();
		prefix.name = name;
		prefix.value = value;
	}
	
	void Streamer::addPrefix(const String &name, const String &value) {
		Prefix &prefix = prefixes.append();
		prefix.name = name;
		prefix.value = value;
	}
	
	/*
	 */
	void Streamer::addBlob(const char *blob_name, const uint8_t (*blob)[256]) {
		
		AtomicLock atomic(lock);
		
		// blob name
		String name = String(blob_name);
		
		// streamer file
		uint32_t file_index = files.size();
		StreamerFile &file = files.append();
		file.name = name;
		file.size = 0;
		file.mtime = 0;
		file.file_index = Maxu32;
		file.archive_index = Maxu32;
		file.blob = blob;
		
		// streamer names
		if(!hasFlag(FlagCase)) name = name.lower();
		names.append(name.reverse(), file_index);
	}
	
	void Streamer::addBlob(const String &name, const uint8_t (*blob)[256]) {
		addBlob(name.get(), blob);
	}
	
	/*
	 */
	bool Streamer::loadArchive(const char *name) {
		
		// open source
		Source source;
		if(!source.open(name)) {
			TS_LOGF(Error, "Streamer::loadArchive(): can't open \"%s\" file\n", name);
			return false;
		}
		
		// load archive
		AtomicLock atomic(lock);
		return load_archive(source, name);
	}
	
	bool Streamer::loadArchive(const String &name) {
		
		// open source
		Source source;
		if(!source.open(name)) {
			TS_LOGF(Error, "Streamer::loadArchive(): can't open \"%s\" file\n", name.get());
			return false;
		}
		
		// load archive
		AtomicLock atomic(lock);
		return load_archive(source, name.get());
	}
	
	bool Streamer::load_archive(Stream &stream, const char *name, const char *type, uint32_t file_index) {
		
		// load archive
		Archive *archive = new Archive();
		if(!archive->open(stream, type)) {
			TS_LOGF(Error, "Streamer::load_archive(): can't open \"%s\" archive\n", name);
			delete archive;
			return false;
		}
		
		// skip recursive archive assets
		if(file_index != Maxu32 && (archive->isFile("object.asset") || archive->isFile("material.asset"))) {
			String archive_name = String(name);
			if(!hasFlag(FlagCase)) archive_name = archive_name.lower();
			names.append(archive_name.reverse(), file_index);
			delete archive;
			return true;
		}
		
		// register archive
		uint32_t archive_index = archives.size();
		archives.append(makeAutoPtr(archive));
		
		// archive files
		for(uint32_t i = 0; i < archive->getNumFiles(); i++) {
			
			// archive file
			String name = archive->getFileName(i);
			uint64_t mtime = archive->getFileMTime(i);
			size_t size = archive->getFileSize(i);
			
			// streamer file
			uint32_t file_index = files.size();
			StreamerFile &file = files.append();
			file.name = name;
			file.size = size;
			file.mtime = mtime;
			file.file_index = i;
			file.archive_index = archive_index;
			file.blob = nullptr;
			
			// recursive archive
			if(hasFlag(FlagRecursive) && ArchiveStream::check(name) && name.extension() != "asset") {
				
				// open source
				Stream stream = archive->openFile(i);
				if(!stream) {
					TS_LOGF(Error, "Streamer::load_archive(): can't open \"%s\" file\n", name.get());
					return false;
				}
				
				// load archive
				String type = name.extension();
				if(!load_archive(stream, name.get(), type.get(), file_index)) return false;
			}
			else {
				
				// streamer names
				if(!hasFlag(FlagCase)) name = name.lower();
				names.append(name.reverse(), file_index);
			}
		}
		
		return true;
	}
	
	/*
	 */
	bool Streamer::loadDirectory(const char *name) {
		
		// load directory
		Directory directory;
		if(!directory.open(name, true)) {
			TS_LOGF(Error, "Streamer::loadDirectory(): can't open \"%s\" directory\n", name);
			return false;
		}
		
		AtomicLock atomic(lock);
		
		// directory files
		for(uint32_t i = 0; i < directory.getNumFiles(); i++) {
			
			// directory file
			String name = directory.getFileName(i);
			uint64_t mtime = directory.getFileMTime(i);
			size_t size = directory.getFileSize(i);
			
			// streamer file
			uint32_t file_index = files.size();
			StreamerFile &file = files.append();
			file.name = directory.getName(); file.name += "/"; file.name += name;
			file.size = size;
			file.mtime = mtime;
			file.file_index = Maxu32;
			file.archive_index = Maxu32;
			file.blob = nullptr;
			
			// recursive archive
			if(hasFlag(FlagRecursive) && ArchiveStream::check(name) && name.extension() != "asset") {
				
				// open source
				Source source;
				if(!source.open(file.name, false)) {
					TS_LOGF(Error, "Streamer::loadDirectory(): can't open \"%s\" file\n", name.get());
					return false;
				}
				
				// load archive
				String type = name.extension();
				if(!load_archive(source, name.get(), type.get(), file_index)) return false;
			}
			else {
				
				// streamer names
				if(!hasFlag(FlagCase)) name = name.lower();
				names.append(name.reverse(), file_index);
			}
		}
		
		return true;
	}
	
	bool Streamer::loadDirectory(const String &name) {
		return loadDirectory(name.get());
	}
	
	/*
	 */
	uint32_t Streamer::findFile(const char *file_name) {
		
		// file name
		String name = String(file_name);
		if(!hasFlag(FlagCase)) name = name.lower();
		
		// file prefix
		for(const Prefix &prefix : prefixes) {
			if(name.begins(prefix.name.get())) name = prefix.value + (name.get() + prefix.name.size());
		}
		
		// find name
		name = name.reverse();
		auto it = names.find(name);
		if(!it) it = names.next(name);
		if(it && it->key.begins(name.get())) return it->data;
		return Maxu32;
	}
	
	uint32_t Streamer::findFile(const String &name) {
		return findFile(name.get());
	}
	
	/*
	 */
	Stream Streamer::openFile(const char *name) {
		uint32_t index = findFile(name);
		if(index != Maxu32) return openFile(index);
		return Stream::null;
	}
	
	Stream Streamer::openFile(const String &name) {
		uint32_t index = findFile(name);
		if(index != Maxu32) return openFile(index);
		return Stream::null;
	}
	
	Stream Streamer::openFile(uint32_t index) {
		
		// streamer file
		StreamerFile &file = files[index];
		
		// blob stream
		if(file.blob) {
			return Blob(file.blob);
		}
		
		// archive stream
		if(file.archive_index != Maxu32) {
			Archive *archive = archives[file.archive_index].get();
			Stream stream = archive->openFile(file.file_index);
			if(stream) return stream;
		}
		
		Source source;
		
		// directory stream
		if(source.open(file.name, false)) {
			return move(source);
		}
		
		return Stream::null;
	}
	
	/*
	 */
	Stream Streamer::open_callback(const char *name, void *data) {
		
		Streamer *streamer = (Streamer*)data;
		
		// streamer callback
		uint32_t index = streamer->findFile(name);
		if(index != Maxu32) {
			Stream stream = streamer->openFile(index);
			if(stream) return move(stream);
		}
		
		// old source callback
		if(streamer->open_func) {
			Stream stream = streamer->open_func(name, streamer->callback_data);
			if(stream) return move(stream);
		}
		
		Source source;
		
		// direct stream
		if(source.open(name, false)) return move(source);
		
		// empty stream
		return Stream::null;
	}
	
	bool Streamer::is_callback(const char *name, void *data) {
		
		Streamer *streamer = (Streamer*)data;
		
		// streamer callback
		if(streamer->findFile(name) != Maxu32) return true;
		
		// old source callback
		return (streamer->is_func && streamer->is_func(name, streamer->callback_data));
	}
}

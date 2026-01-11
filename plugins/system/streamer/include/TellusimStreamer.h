// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_SYSTEM_STREAMER_H__
#define __TELLUSIM_PLUGINS_SYSTEM_STREAMER_H__

#include <core/TellusimMap.h>
#include <core/TellusimArray.h>
#include <core/TellusimAtomic.h>
#include <core/TellusimSource.h>
#include <core/TellusimPointer.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Archive;
	
	/**
	 * Streamer
	 */
	class Streamer {
			
		public:
			
			/// Streamer flags
			enum Flags {
				FlagNone = 0,
				FlagCase		= (1 << 0),		// case sensivity
				FlagRecursive	= (1 << 1),		// recursive archives
				DefaultFlags	= FlagCase,
			};
			
			/// streamer constructor
			explicit Streamer(Flags flags = DefaultFlags);
			virtual ~Streamer();
			
			/// disable copying
			Streamer(const Streamer&) = delete;
			Streamer &operator=(const Streamer&) = delete;
			
			/// clear streamer
			void clear();
			
			/// streamer flags
			void setFlags(Flags f) { flags = f; }
			TS_INLINE Flags getFlags() const { return flags; }
			
			TS_INLINE bool hasFlag(Flags flags) const { return ((getFlags() & flags) != FlagNone); }
			TS_INLINE bool hasFlags(Flags flags) const { return ((getFlags() & flags) == flags); }
			
			/// streamer prefixes
			void addPrefix(const char *name, const char *value = nullptr);
			void addPrefix(const String &name, const String &value = String::null);
			
			/// streamer blobs
			void addBlob(const char *name, const uint8_t (*blob)[256]);
			void addBlob(const String &name, const uint8_t (*blob)[256]);
			
			/// streamer archives
			bool loadArchive(const char *name);
			bool loadArchive(const String &name);
			
			/// streamer directories
			bool loadDirectory(const char *name);
			bool loadDirectory(const String &name);
			
			/// find file
			uint32_t findFile(const char *name);
			uint32_t findFile(const String &name);
			
			/// check file
			TS_INLINE bool isFile(const char *name) { return (findFile(name) != Maxu32); }
			TS_INLINE bool isFile(const String &name) { return (findFile(name) != Maxu32); }
			
			/// open file
			Stream openFile(const char *name);
			Stream openFile(const String &name);
			Stream openFile(uint32_t index);
			
			/// streamer files
			TS_INLINE uint32_t getNumFiles() const { return files.size(); }
			TS_INLINE const String &getFileName(uint32_t index) const { return files[index].name; }
			TS_INLINE uint64_t getFileMTime(uint32_t index) const { return files[index].mtime; }
			TS_INLINE size_t getFileSize(uint32_t index) const { return files[index].size; }
			
			/// streamer archives
			TS_INLINE uint32_t getNumArchives() const { return archives.size(); }
			TS_INLINE const Archive &getArchive(uint32_t index) const { return archives[index].ref(); }
			
		private:
			
			/// load archive
			bool load_archive(Stream &stream, const char *name, const char *type = nullptr, uint32_t file_index = Maxu32);
			
			/// stream callback
			static Stream open_callback(const char *name, void *data);
			static bool is_callback(const char *name, void *data);
			
			struct Prefix {
				String name;							// prefix name
				String value;							// prefix value
			};
			
			struct StreamerFile {
				String name;							// file name
				size_t size = 0;						// file size
				uint64_t mtime = 0;						// file mtime
				uint32_t file_index = Maxu32;			// file index
				uint32_t archive_index = Maxu32;		// archive index
				const uint8_t (*blob)[256] = nullptr;	// file blob
			};
			
			SpinLock lock;								// streamer lock
			
			Flags flags = FlagNone;						// streamer flags
			
			Array<Prefix> prefixes;						// streamer prefixes
			
			Array<AutoPtr<Archive>> archives;			// streamer archives
			
			Array<StreamerFile> files;					// streamer files
			
			Map<String, uint32_t> names;				// streamer names
			
			Source::OpenCallback *open_func = nullptr;	// source open callback
			Source::IsCallback *is_func = nullptr;		// source is callback
			void *callback_data = nullptr;				// callback data
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(Streamer::Flags)
}

#endif /* __TELLUSIM_PLUGINS_SYSTEM_STREAMER_H__ */

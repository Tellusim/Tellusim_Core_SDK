// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_FORMAT_ARCHIVE_H__
#define __TELLUSIM_FORMAT_ARCHIVE_H__

#include <core/TellusimStream.h>

/*
 */
namespace Tellusim {
	
	/**
	 * The Archive class provides functionality for managing and accessing archive files.
	 * It allows opening and closing archives from various sources, including file names, strings, and streams.
	 * The class provides methods for retrieving metadata about files within the archive, such as file names, sizes, and modification times.
	 * Additionally, it supports searching for specific files by name or index and enables accessing files within the archive through a stream interface for reading.
	 */
	class TS_API Archive {
			
			TS_DECLARE_NONCOPY(Archive, 4)
			
		public:
			
			Archive();
			
			/// open/close archive
			bool open(const char *name, const char *type = nullptr);
			bool open(const String &name, const char *type = nullptr);
			bool open(Stream &stream, const char *type = nullptr);
			void close();
			
			/// archive status
			bool isOpened() const;
			String getName() const;
			
			/// files list
			uint32_t getNumFiles() const;
			String getFileName(uint32_t index) const;
			uint64_t getFileMTime(uint32_t index) const;
			size_t getFileSize(uint32_t index) const;
			
			/// find file
			uint32_t findFile(const char *name) const;
			uint32_t findFile(const String &name) const;
			bool isFile(const char *name) const;
			bool isFile(const String &name) const;
			
			/// open file
			Stream openFile(const char *name) const;
			Stream openFile(const String &name) const;
			Stream openFile(uint32_t index) const;
	};
	
	/**
	 * The ArchiveStream class is a base class designed for creating custom archive formats.
	 * It provides virtual methods for opening archive streams, accessing metadata about the files within the archive (such as file names, sizes, and modification times), and opening individual files from the archive.
	 * This class serves as a base class for implementing specific archive stream formats, allowing for the customization and extension of archive handling functionality.
	 * It also includes static methods for checking supported formats and retrieving a list of compatible formats, providing flexibility in managing and working with various custom archive formats.
	 */
	class TS_API ArchiveStream {
			
			TS_DECLARE_NONCOPY(ArchiveStream, 0)
			
		protected:
			
			ArchiveStream();
			ArchiveStream(const char *name);
			ArchiveStream(const InitializerList<const char*> &names);
			
		public:
			
			/// create instance
			virtual ArchiveStream *instance() const = 0;
			virtual void destructor(ArchiveStream *instance) const = 0;
			
			/// open archive
			virtual bool open(Stream &stream, const char *name) = 0;
			
			/// files list
			virtual uint32_t getNumFiles() const = 0;
			virtual const String &getFileName(uint32_t index) const = 0;
			virtual uint64_t getFileMTime(uint32_t index) const = 0;
			virtual size_t getFileSize(uint32_t index) const = 0;
			
			/// open file
			virtual Stream openFile(uint32_t index) = 0;
			
			/// archive stream formats
			static bool check(const String &name);
			
			/// list of supported formats
			static String getFormats();
	};
}

#endif /* __TELLUSIM_FORMAT_ARCHIVE_H__ */

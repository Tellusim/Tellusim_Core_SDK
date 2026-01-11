// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_INTERFACE_FONT_H__
#define __TELLUSIM_INTERFACE_FONT_H__

#include <interface/TellusimTypes.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Stream;
	class Command;
	class Device;
	
	/**
	 * The Font class provides functionality for loading, managing, and rendering fonts, supporting multiple font styles and sizes.
	 * It allows checking if a font is loaded, retrieving glyph advances, and calculating text bounding rectangles for both single and batched text.
	 * The class supports creating and drawing text using a specified font style, either character by character or in batches.
	 */
	class TS_API Font {
			
		private:
			
			TS_DECLARE_PTR(Font, 0)
			
		public:
			
			Font();
			
			/// clear font
			void clear();
			
			/// check font
			bool isLoaded() const;
			
			/// load font
			bool load(const char *name);
			bool load(Stream &stream);
			
			/// glyph advance
			float32_t getAdvance(const FontStyle &style, uint32_t code);
			
			/// text rectangle
			Rect getRect(const Vector3f &position, const FontStyle &style, const char *str);
			Rect getRect(const Vector3f &position, const FontStyle &style, const uint32_t *str);
			
			template <class Type> TS_INLINE Rect getRect(const Vector3f &position, uint32_t size, const Type *str) { return getRect(position, FontStyle(size), str); }
			
			/// batched text rectangle
			Rect getRect(const FontBatch *batches, uint32_t num_batches);
			Rect getRect(const FontBatch32 *batches, uint32_t num_batches);
			
			/// create text
			void create(const Device &device, const FontStyle &style, const char *str);
			void create(const Device &device, const FontStyle &style, const uint32_t *str);
			
			template <class Type> TS_INLINE void create(const Device &device, uint32_t size, const Type *str) { return create(device, FontStyle(size), str); }
			
			/// create batched text
			void create(const Device &device, const FontBatch *batches, uint32_t num_batches);
			void create(const Device &device, const FontBatch32 *batches, uint32_t num_batches);
			
			/// draw text
			void draw(Command &command, const Vector3f &position, const FontStyle &style, const char *str);
			void draw(Command &command, const Vector3f &position, const FontStyle &style, const uint32_t *str);
			
			template <class Type> TS_INLINE void draw(Command *command, const Vector3f &position, uint32_t size, const Type *str) { draw(command, position, FontStyle(size), str); }
			template <class Type> TS_INLINE void draw(Command *command, const Vector3f &position, uint32_t size, const Color &color, const Type *str) { draw(command, position, FontStyle(size, color), str); }
			
			/// draw batched text
			void draw(Command &command, const FontBatch *batches, uint32_t num_batches);
			void draw(Command &command, const FontBatch32 *batches, uint32_t num_batches);
			
			/// flush textures
			bool flush(const Device &device);
	};
}

#endif /* __TELLUSIM_INTERFACE_FONT_H__ */

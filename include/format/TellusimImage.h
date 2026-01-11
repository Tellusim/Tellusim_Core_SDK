// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_FORMAT_IMAGE_H__
#define __TELLUSIM_FORMAT_IMAGE_H__

#include <TellusimTypes.h>
#include <TellusimFormat.h>
#include <math/TellusimColor.h>
#include <math/TellusimFloat.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Async;
	class String;
	class Stream;
	
	/**
	 * The Image class provides a comprehensive set of methods for working with images, supporting various image types (2D, 3D, Cube) and formats.
	 * It allows the creation, manipulation, and conversion of images, with functionality for operations like loading, saving, resizing, flipping, rotating, and comparing images.
	 * The class supports a variety of image flags to control behavior (e.g., mipmaps, compression), as well as different image filters for resizing and minification.
	 * It offers methods for querying image properties such as dimensions, format, components, and layout, and includes the ability to manipulate image slices, regions, and components.
	 * The class also provides advanced features like handling image metadata, creating mipmaps, and obtaining the raw image data for processing or manipulation.
	 * Additionally, it supports asynchronous operations for optimized performance when dealing with large image data.
	 */
	class TS_API Image {
			
			TS_DECLARE_PTR(Image, 0)
			
		public:
			
			/// Image types
			enum Type {
				TypeUnknown = 0,
				Type2D,
				Type3D,
				TypeCube,
				NumTypes,
			};
			
			/// Image flags
			enum Flags {
				FlagNone = 0,
				FlagMipmaps		= (1 << 0),		// create mipmaps
				FlagNoClear		= (1 << 1),		// do not clear
				FlagNoAllocate	= (1 << 2),		// do not allocate
				FlagFast		= (1 << 3),		// fast compression
				FlagBest		= (1 << 4),		// best compression
				FlagPerceptual	= (1 << 5),		// perceptual block encoding
				FlagPanorama	= (1 << 6),		// cube to panorama type conversion
				FlagNormalize	= (1 << 7),		// normalize format conversion
				FlagGamma		= (1 << 8),		// gamma format conversion
				FlagSRGB		= (1 << 9),		// sRGB format conversion
				NumFlags = 10,
			};
			
			/// Image filters
			enum Filter {
				FilterUnknown = 0,
				FilterPoint,					// point filter
				FilterLinear,					// linear magnification filter
				FilterCubic,					// cubic magnification filter
				FilterSinc,						// sinc minification filter
				FilterBox,						// box minification filter
				FilterMax,						// max minification filter
				FilterMin,						// min minification filter
				FilterMip,						// mip minification filter
				FilterCR,						// Catmull-Rom filter
				NumFilters,
			};
			
			Image();
			explicit Image(const char *name, Flags flags = FlagNone, uint32_t offset = 0);
			explicit Image(Stream &stream, Flags flags = FlagNone, uint32_t offset = 0);
			Image(Type type, Format format, const Size &size, Flags flags = FlagNone);
			Image(Type type, Format format, const Size &size, uint32_t layers, Flags flags = FlagNone);
			
			/// clear image
			void clear();
			
			/// check image
			bool isLoaded() const;
			bool isAllocated() const;
			
			/// image type
			Type getType() const;
			
			static const char *getTypeName(Type type);
			const char *getTypeName() const;
			
			TS_INLINE bool is2DType() const { return (getType() == Type2D); }
			TS_INLINE bool is3DType() const { return (getType() == Type3D); }
			TS_INLINE bool isCubeType() const { return (getType() == TypeCube); }
			
			/// image format
			Format getFormat() const;
			
			TS_INLINE const char *getFormatName() const { return Tellusim::getFormatName(getFormat()); }
			
			TS_INLINE bool isColorFormat() const { return Tellusim::isColorFormat(getFormat()); }
			TS_INLINE bool isDepthFormat() const { return Tellusim::isDepthFormat(getFormat()); }
			TS_INLINE bool isPixelFormat() const { return Tellusim::isPixelFormat(getFormat()); }
			TS_INLINE bool isPlainFormat() const { return Tellusim::isPlainFormat(getFormat()); }
			TS_INLINE bool isMixedFormat() const { return Tellusim::isMixedFormat(getFormat()); }
			TS_INLINE bool isBlockFormat() const { return Tellusim::isBlockFormat(getFormat()); }
			TS_INLINE bool isStencilFormat() const { return Tellusim::isStencilFormat(getFormat()); }
			
			TS_INLINE bool isNormFormat() const { return Tellusim::isNormFormat(getFormat()); }
			TS_INLINE bool isSRGBFormat() const { return Tellusim::isSRGBFormat(getFormat()); }
			TS_INLINE bool isFloatFormat() const { return Tellusim::isFloatFormat(getFormat()); }
			TS_INLINE bool isSignedFormat() const { return Tellusim::isSignedFormat(getFormat()); }
			TS_INLINE bool isUnsignedFormat() const { return Tellusim::isUnsignedFormat(getFormat()); }
			TS_INLINE bool isIntegerFormat() const { return Tellusim::isIntegerFormat(getFormat()); }
			
			TS_INLINE bool isi8Format() const { return Tellusim::isi8Format(getFormat()); }
			TS_INLINE bool isu8Format() const { return Tellusim::isu8Format(getFormat()); }
			TS_INLINE bool is8BitFormat() const { return Tellusim::is8BitFormat(getFormat()); }
			
			TS_INLINE bool isi16Format() const { return Tellusim::isi16Format(getFormat()); }
			TS_INLINE bool isu16Format() const { return Tellusim::isu16Format(getFormat()); }
			TS_INLINE bool isf16Format() const { return Tellusim::isf16Format(getFormat()); }
			TS_INLINE bool is16BitFormat() const { return Tellusim::is16BitFormat(getFormat()); }
			
			TS_INLINE bool isi32Format() const { return Tellusim::isi32Format(getFormat()); }
			TS_INLINE bool isu32Format() const { return Tellusim::isu32Format(getFormat()); }
			TS_INLINE bool isf32Format() const { return Tellusim::isf32Format(getFormat()); }
			TS_INLINE bool is32BitFormat() const { return Tellusim::is32BitFormat(getFormat()); }
			
			TS_INLINE bool isi64Format() const { return Tellusim::isi64Format(getFormat()); }
			TS_INLINE bool isu64Format() const { return Tellusim::isu64Format(getFormat()); }
			TS_INLINE bool isf64Format() const { return Tellusim::isf64Format(getFormat()); }
			TS_INLINE bool is64BitFormat() const { return Tellusim::is64BitFormat(getFormat()); }
			
			TS_INLINE bool isBC15Format() const { return Tellusim::isBC15Format(getFormat()); }
			TS_INLINE bool isBC67Format() const { return Tellusim::isBC67Format(getFormat()); }
			TS_INLINE bool isETC2Format() const { return Tellusim::isETC2Format(getFormat()); }
			TS_INLINE bool isASTCFormat() const { return Tellusim::isASTCFormat(getFormat()); }
			
			TS_INLINE uint32_t getComponents() const { return getFormatComponents(getFormat()); }
			TS_INLINE uint32_t getPixelSize() const { return getFormatPixelSize(getFormat()); }
			TS_INLINE uint32_t getBlockSize() const { return getFormatBlockSize(getFormat()); }
			TS_INLINE uint32_t getBlockWidth() const { return getFormatBlockWidth(getFormat()); }
			TS_INLINE uint32_t getBlockHeight() const { return getFormatBlockHeight(getFormat()); }
			
			/// image dimension
			uint32_t getWidth() const;
			uint32_t getHeight() const;
			uint32_t getDepth() const;
			uint32_t getFaces() const;
			uint32_t getLayers() const;
			uint32_t getMipmaps() const;
			uint32_t findMipmap(const Size &size) const;
			uint32_t getWidth(uint32_t mipmap) const;
			uint32_t getHeight(uint32_t mipmap) const;
			uint32_t getDepth(uint32_t mipmap) const;
			
			TS_INLINE bool hasLayers() const { return (getLayers() > 1); }
			TS_INLINE bool hasMipmaps() const { return (getMipmaps() > 1); }
			
			Size getSize() const;
			Region getRegion() const;
			Slice getSlice() const;
			Size getSize(uint32_t mipmap) const;
			Region getRegion(uint32_t mipmap) const;
			Slice getSlice(uint32_t mipmap) const;
			
			/// image meta info
			void setMetaInfo(const String &str);
			String getMetaInfo() const;
			
			/// image description
			String getDescription() const;
			
			/// image layout
			size_t getOffset(const Slice &slice, uint32_t alignment = 1) const;
			size_t getStride(uint32_t mipmap = 0, uint32_t alignment = 1) const;
			size_t getMipmapSize(uint32_t mipmap, uint32_t alignment = 1) const;
			size_t getLayerSize(uint32_t alignment = 1) const;
			size_t getDataSize(uint32_t alignment = 1) const;
			
			/// create image
			bool create(Type type, Format format, const Size &size, Flags flags = FlagNone);
			bool create(Type type, Format format, const Size &size, uint32_t layers, Flags flags = FlagNone);
			
			bool create2D(Format format, uint32_t size, Flags flags = FlagNone);
			bool create3D(Format format, uint32_t size, Flags flags = FlagNone);
			bool createCube(Format format, uint32_t size, Flags flags = FlagNone);
			
			bool create2D(Format format, uint32_t width, uint32_t height, Flags flags = FlagNone);
			bool create3D(Format format, uint32_t width, uint32_t height, uint32_t depth, Flags flags = FlagNone);
			
			bool create2D(Format format, uint32_t width, uint32_t height, uint32_t layers, Flags flags = FlagNone);
			bool createCube(Format format, uint32_t size, uint32_t layers, Flags flags = FlagNone);
			
			/// info image
			bool info(const char *name, Flags flags = FlagNone, uint32_t offset = 0, Async *async = nullptr);
			bool info(const String &name, Flags flags = FlagNone, uint32_t offset = 0, Async *async = nullptr);
			bool info(Stream &stream, Flags flags = FlagNone, uint32_t offset = 0, Async *async = nullptr);
			
			bool info(const char *name, Async *async) { return info(name, FlagNone, 0, async); }
			bool info(const String &name, Async *async) { return info(name, FlagNone, 0, async); }
			bool info(Stream &stream, Async *async) { return info(stream, FlagNone, 0, async); }
			
			/// load image
			bool load(const char *name, Flags flags = FlagNone, uint32_t offset = 0, Async *async = nullptr);
			bool load(const String &name, Flags flags = FlagNone, uint32_t offset = 0, Async *async = nullptr);
			bool load(Stream &stream, Flags flags = FlagNone, uint32_t offset = 0, Async *async = nullptr);
			
			bool load(const char *name, Async *async) { return load(name, FlagNone, 0, async); }
			bool load(const String &name, Async *async) { return load(name, FlagNone, 0, async); }
			bool load(Stream &stream, Async *async) { return load(stream, FlagNone, 0, async); }
			
			/// save image
			bool save(const char *name, Flags flags = FlagNone, uint32_t quality = 95) const;
			bool save(const String &name, Flags flags = FlagNone, uint32_t quality = 95) const;
			bool save(Stream &stream, Flags flags = FlagNone, uint32_t quality = 95) const;
			
			/// image components
			bool swap(uint32_t component_0, uint32_t component_1);
			bool copy(const Image &src, uint32_t dest_component, uint32_t src_component);
			
			/// flip horizontally
			bool flipX(const Region &region, const Slice &slice);
			bool flipX(const Region &region);
			bool flipX();
			
			/// flip vertically
			bool flipY(const Region &region, const Slice &slice);
			bool flipY(const Region &region);
			bool flipY();
			
			/// copy image
			bool copy(const Image &src, const Origin &dest_origin, const Region &src_region, const Slice &dest_slice, const Slice &src_slice);
			bool copy(const Image &src, const Origin &dest_origin, const Region &src_region);
			bool copy(const Image &src, const Origin &dest_origin, const Slice &dest_slice);
			bool copy(const Image &src, const Slice &dest_slice, const Slice &src_slice);
			bool copy(const Image &src, const Origin &dest_origin);
			bool copy(const Image &src, const Slice &dest_slice);
			
			/// convert image to type
			Image toType(Type type, Flags flags, Async *async = nullptr) const;
			Image toType(Type type, Async *async = nullptr) const { return toType(type, FlagNone, async); }
			
			/// convert image to format
			Image toFormat(Format format, Flags flags, Async *async = nullptr) const;
			Image toFormat(Format format, Async *async = nullptr) const { return toFormat(format, FlagNone, async); }
			
			/// get image slice
			Image getSlice(const Slice &slice) const;
			
			/// get image component
			Image getComponent(uint32_t component) const;
			
			/// get image region
			Image getRegion(const Region &region, const Slice &slice) const;
			Image getRegion(const Region &region) const;
			
			/// get rotated image
			Image getRotated(int32_t angle, const Slice &slice) const;
			Image getRotated(int32_t angle) const;
			
			/// get resized image
			Image getResized(const Size &size, Filter min, Filter mag, Flags flags, Async *async = nullptr) const;
			Image getResized(const Size &size, Filter min, Filter mag = FilterCubic, Async *async = nullptr) const { return getResized(size, min, mag, FlagNone, async); }
			Image getResized(const Size &size, Async *async = nullptr) const { return getResized(size, FilterSinc, FilterCubic, FlagNone, async); }
			
			/// get mipmapped image
			Image getMipmapped(Filter filter, Flags flags, Async *async = nullptr) const;
			Image getMipmapped(Filter filter, Async *async = nullptr) const { return getMipmapped(filter, FlagNone, async); }
			Image getMipmapped(Async *async = nullptr) const { return getMipmapped(FilterMip, FlagNone, async); }
			
			/// compare images
			int32_t compare(const Image &image) const;
			
			/// image data
			const uint8_t *getData(const Slice &slice = Slice()) const;
			uint8_t *getData(const Slice &slice = Slice());
			
			const uint8_t *getData(const Origin &origin, const Slice &slice = Slice()) const;
			uint8_t *getData(const Origin &origin, const Slice &slice = Slice());
			
			bool setData(const void *src, const Slice &slice = Slice(), uint32_t alignment = 1, size_t stride = 0);
			bool getData(void *dest, const Slice &slice = Slice(), uint32_t alignment = 1, size_t stride = 0) const;
			
			/// memory usage
			size_t getMemory() const;
	};
	
	/**
	 * The ImageColor struct represents a color value with multiple formats, including integer, unsigned integer, half-precision, and full-precision floating point.
	 * It supports flexibility in initialization, allowing the color to be specified as individual components or as a single value for all components.
	 * The struct provides multiple constructors for different data types, including support for copying, as well as conversion between different color formats.
	 */
	struct TS_ALIGNAS16 ImageColor {
		
		ImageColor() : f { 0.0f, 0.0f, 0.0f, 0.0f } { }
		ImageColor(const ImageColor &c) : uv { c.u.r, c.u.g, c.u.b, c.u.a } { }
		explicit ImageColor(int32_t i) : iv { i, i, i, i } { }
		explicit ImageColor(uint32_t u) : uv { u, u, u, u } { }
		explicit ImageColor(float16_t h) : hv { h, h, h, h } { }
		explicit ImageColor(float32_t f) : fv { f, f, f, f } { }
		explicit ImageColor(const int32_t *iv) : iv { iv[0], iv[1], iv[2], iv[3] } { }
		explicit ImageColor(const uint32_t *uv) : uv { uv[0], uv[1], uv[2], uv[3] } { }
		explicit ImageColor(const float16_t *hv) : hv { hv[0], hv[1], hv[2], hv[3] } { }
		explicit ImageColor(const float32_t *fv) : fv { fv[0], fv[1], fv[2], fv[3] } { }
		ImageColor(int32_t l, int32_t a) : iv { l, l, l, a } { }
		ImageColor(uint32_t l, uint32_t a) : uv { l, l, l, a } { }
		ImageColor(float16_t l, float16_t a) : hv { l, l, l, a } { }
		ImageColor(float32_t l, float32_t a) : fv { l, l, l, a } { }
		ImageColor(int32_t r, int32_t g, int32_t b, int32_t a) : iv { r, g, b, a } { }
		ImageColor(uint32_t r, uint32_t g, uint32_t b, uint32_t a) : uv { r, g, b, a } { }
		ImageColor(float16_t r, float16_t g, float16_t b, float16_t a) : hv { r, g, b, a } { }
		ImageColor(float32_t r, float32_t g, float32_t b, float32_t a) : fv { r, g, b, a } { }
		ImageColor(const Color &color, Format format) { set(color, format); }
		
		/// color value
		TS_INLINE void set(const Color &color, Format format) {
			setPixelFormatValue(format, fv, color.c, Size);
		}
		TS_INLINE Color get(Format format) const {
			Color ret; getPixelFormatValue(format, ret.c, fv, Size); return ret;
		}
		
		/// assignment operator
		TS_INLINE ImageColor &operator=(const ImageColor &c) {
			f.r = c.f.r; f.g = c.f.g; f.b = c.f.b; f.a = c.f.a;
			return *this;
		}
		
		enum {
			Size = 4,
		};
		
		union {
			struct { int32_t r, g, b, a; } i;
			struct { uint32_t r, g, b, a; } u;
			struct { float16_t r, g, b, a; } h;
			struct { float32_t r, g, b, a; } f;
			int32_t iv[Size];
			uint32_t uv[Size];
			float16_t hv[Size];
			float32_t fv[Size];
		};
	};
	
	/**
	 * The ImageSampler class provides a flexible and efficient interface for working with image data in various formats and dimensions.
	 * It supports 2D, 3D, and Cube image types, allowing for easy manipulation of image color data at the texel level.
	 * The class offers constructors for creating samplers from both mutable and immutable images, with optional slice support.
	 */
	class TS_API ImageSampler {
			
			TS_DECLARE_COPY(ImageSampler, 16)
			
		public:
			
			using Type = Image::Type;
			using Filter = Image::Filter;
			
			ImageSampler();
			explicit ImageSampler(Image &image, const Slice &slice = Slice());
			explicit ImageSampler(const Image &image, const Slice &slice = Slice());
			
			/// clear sampler
			void clear();
			
			/// check sampler
			bool isCreated() const;
			
			/// sampler type
			Type getType() const;
			
			TS_INLINE bool is2DType() const { return (getType() == Image::Type2D); }
			TS_INLINE bool is3DType() const { return (getType() == Image::Type3D); }
			TS_INLINE bool isCubeType() const { return (getType() == Image::TypeCube); }
			
			/// sampler format
			Format getFormat() const;
			
			TS_INLINE const char *getFormatName() const { return Tellusim::getFormatName(getFormat()); }
			
			/// sampler dimension
			uint32_t getWidth() const;
			uint32_t getHeight() const;
			uint32_t getDepth() const;
			uint32_t getFaces() const;
			size_t getTexels() const;
			
			TS_INLINE Size getSize() const { return Size(getWidth(), getHeight(), getDepth()); }
			TS_INLINE Region getRegion() const { return Region(getWidth(), getHeight(), getDepth()); }
			
			/// sampler layout
			size_t getStride() const;
			size_t getLayerSize() const;
			uint32_t getPixelSize() const;
			uint32_t getComponents() const;
			
			/// sampler data
			const uint8_t *getData() const;
			uint8_t *getData();
			
			/// create sampler
			bool create(Image &image, const Slice &slice = Slice());
			bool create(const Image &image, const Slice &slice = Slice());
			bool create(Type type, Format format, const Size &size, size_t stride, void *data);
			bool create(Type type, Format format, const Size &size, size_t stride, const void *data);
			bool create(Type type, Format format, const Size &size, size_t stride, size_t layer_size, void *data);
			bool create(Type type, Format format, const Size &size, size_t stride, size_t layer_size, const void *data);
			
			/// clear image
			bool clear(const Color &color);
			bool clear(const ImageColor &color);
			
			/// multiply accumulate image
			bool mad(const Color &m, const Color &a);
			
			/// 2D image colors
			void set2D(uint32_t x, uint32_t y, const ImageColor &color);
			ImageColor get2D(uint32_t x, uint32_t y, bool repeat = false) const;
			ImageColor get2D(float64_t x, float64_t y, bool repeat = false, Filter filter = Image::FilterLinear) const;
			
			/// 3D image colors
			void set3D(uint32_t x, uint32_t y, uint32_t z, const ImageColor &color);
			ImageColor get3D(uint32_t x, uint32_t y, uint32_t z, bool repeat = false) const;
			ImageColor get3D(float32_t x, float32_t y, float32_t z, bool repeat = false, Filter filter = Image::FilterLinear) const;
			
			/// Cube image colors
			void setCube(float32_t x, float32_t y, float32_t z, const ImageColor &color);
			ImageColor getCube(float32_t x, float32_t y, float32_t z, Filter filter = Image::FilterLinear) const;
			uint32_t getCubeFace(float32_t x, float32_t y, float32_t z, float32_t &tx, float32_t &ty) const;
			
			/// Texel image colors
			void setTexel(size_t t, const ImageColor &color);
			ImageColor getTexel(size_t t) const;
	};
	
	/**
	 * The ImageStream class is a base class designed for creating custom image stream formats, providing virtual methods for loading and saving images through streams.
	 * It supports handling different image types and formats, serving as a foundation for implementing specific image stream formats and enabling the customization and extension of image handling functionality.
	 * The class also includes static methods for checking supported formats and retrieving lists of compatible load and save formats, offering flexibility in managing and working with various image stream formats.
	 */
	class TS_API ImageStream {
			
			TS_DECLARE_NONCOPY(ImageStream, 0)
			
		protected:
			
			enum Flags {
				FlagNone = 0,
				FlagLoad		= (1 << 0),
				FlagSave		= (1 << 1),
				FlagLoadSave	= (FlagLoad | FlagSave),
			};
			
			ImageStream(Flags flags, const char *name, uint32_t magic = 0);
			ImageStream(Flags flags, const InitializerList<const char*> &names, uint32_t magic = 0);
			ImageStream(Flags flags, const InitializerList<const char*> &names, const InitializerList<uint32_t> &magics);
			
		public:
			
			virtual bool info(Stream &stream, Image &image, Image::Flags flags, uint32_t offset, Async *async);
			virtual bool load(Stream &stream, Image &image, Image::Flags flags, uint32_t offset, Async *async);
			virtual bool save(Stream &stream, const Image &image, Image::Flags flags, uint32_t quality);
			
			/// image stream formats
			static bool check(const String &name, uint32_t magic = 0);
			
			/// list of supported formats
			static String getLoadFormats();
			static String getSaveFormats();
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(Image::Flags)
}

#endif /* __TELLUSIM_FORMAT_IMAGE_H__ */

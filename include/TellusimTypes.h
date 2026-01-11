// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_TYPES_H__
#define __TELLUSIM_TYPES_H__

#include <TellusimBase.h>

/*
 */
namespace Tellusim {
	
	/*****************************************************************************\
	 *
	 * Origin
	 *
	\*****************************************************************************/
	
	/**
	 * The Origin struct represents a point in 2D or 3D space with integer coordinates.
	 * It provides constructors to initialize the point in either 2D (with x and y coordinates) or 3D (with x, y, and z coordinates) space.
	 * By default, the x, y, and z values are set to zero.
	 */
	struct Origin {
		
		Origin() { }
		Origin(uint32_t x, uint32_t y) : x(x), y(y) { }
		Origin(uint32_t x, uint32_t y, uint32_t z) : x(x), y(y), z(z) { }
		
		uint32_t x = 0;
		uint32_t y = 0;
		uint32_t z = 0;
	};
	
	TS_INLINE bool operator==(const Origin &o0, const Origin &o1) {
		return (o0.x == o1.x && o0.y == o1.y && o0.z == o1.z);
	}
	TS_INLINE bool operator!=(const Origin &o0, const Origin &o1) {
		return (o0.x != o1.x || o0.y != o1.y || o0.z != o1.z);
	}
	
	TS_INLINE Origin operator*(const Origin &o0, const Origin &o1) {
		return Origin(o0.x * o1.x, o0.y * o1.y, o0.z * o1.z);
	}
	TS_INLINE Origin operator/(const Origin &o0, const Origin &o1) {
		return Origin(o0.x / o1.x, o0.y / o1.y, o0.z / o1.z);
	}
	
	TS_INLINE Origin operator+(const Origin &o0, const Origin &o1) {
		return Origin(o0.x + o1.x, o0.y + o1.y, o0.z + o1.z);
	}
	TS_INLINE Origin operator-(const Origin &o0, const Origin &o1) {
		TS_ASSERT(o0.x >= o1.x && o0.y >= o1.y && o0.z >= o1.z && "Origin::operator-(): invalid origin");
		return Origin(o0.x - o1.x, o0.y - o1.y, o0.z - o1.z);
	}
	
	TS_INLINE Origin operator<<(const Origin &o, uint32_t m) {
		return Origin(o.x << m, o.y << m, o.z << m);
	}
	TS_INLINE Origin operator>>(const Origin &o, uint32_t m) {
		return Origin(o.x >> m, o.y >> m, o.z >> m);
	}
	
	TS_INLINE Origin operator*(const Origin &o, uint32_t f) {
		return Origin(o.x * f, o.y * f, o.z * f);
	}
	TS_INLINE Origin operator/(const Origin &o, uint32_t f) {
		return Origin(o.x / f, o.y / f, o.z / f);
	}
	
	TS_INLINE Origin operator*(const Origin &o, float32_t f) {
		return Origin((uint32_t)(o.x * f), (uint32_t)(o.y * f), (uint32_t)(o.z * f));
	}
	
	/*****************************************************************************\
	 *
	 * Size
	 *
	\*****************************************************************************/
	
	/**
	 * The Size struct represents a 2D or 3D size, commonly used for defining dimensions such as width, height, and depth.
	 * It provides multiple constructors to initialize the size in 2D (with width and height), 3D (with width, height, and depth), or as a uniform size for all dimensions (when a single size value is provided for width and height).
	 * By default, all values are set to zero.
	 */
	struct Size {
		
		Size() { }
		explicit Size(uint32_t size) : width(size), height(size), depth(1) { }
		Size(uint32_t width, uint32_t height) : width(width), height(height), depth(1) { }
		Size(uint32_t width, uint32_t height, uint32_t depth) : width(width), height(height), depth(depth) { }
		
		uint32_t width = 0;
		uint32_t height = 0;
		uint32_t depth = 0;
	};
	
	TS_INLINE bool operator==(const Size &s0, const Size &s1) {
		return (s0.width == s1.width && s0.height == s1.height && s0.depth == s1.depth);
	}
	TS_INLINE bool operator!=(const Size &s0, const Size &s1) {
		return (s0.width != s1.width || s0.height != s1.height || s0.depth != s1.depth);
	}
	
	TS_INLINE Size operator*(const Size &s0, const Size &s1) {
		return Size(s0.width * s1.width, s0.height * s1.height, s0.depth * s1.depth);
	}
	TS_INLINE Size operator/(const Size &s0, const Size &s1) {
		return Size(s0.width / s1.width, s0.height / s1.height, s0.depth / s1.depth);
	}
	
	TS_INLINE Size operator+(const Size &s0, const Size &s1) {
		return Size(s0.width + s1.width, s0.height + s1.height, s0.depth + s1.depth);
	}
	TS_INLINE Size operator-(const Size &s0, const Size &s1) {
		TS_ASSERT(s0.width >= s1.width && s0.height >= s1.height && s0.depth >= s1.depth && "Size::operator-(): invalid size");
		return Size(s0.width - s1.width, s0.height - s1.height, s0.depth - s1.depth);
	}
	
	TS_INLINE Size operator<<(const Size &s, uint32_t m) {
		return Size(s.width << m, s.height << m, s.depth << m);
	}
	TS_INLINE Size operator>>(const Size &s, uint32_t m) {
		return Size(s.width >> m, s.height >> m, s.depth >> m);
	}
	
	TS_INLINE Size operator*(const Size &s, uint32_t f) {
		return Size(s.width * f, s.height * f, s.depth * f);
	}
	TS_INLINE Size operator/(const Size &s, uint32_t f) {
		return Size(s.width / f, s.height / f, s.depth / f);
	}
	
	TS_INLINE Size operator*(const Size &s, float32_t f) {
		return Size((uint32_t)(s.width * f), (uint32_t)(s.height * f), (uint32_t)(s.depth * f));
	}
	
	/*****************************************************************************\
	 *
	 * Region
	 *
	\*****************************************************************************/
	
	/**
	 * The Region struct defines a 2D or 3D region in space, typically used to represent areas or volumes within a larger structure, such as an image, texture, or 3D object.
	 * It provides several constructors to initialize the region with specific coordinates (x, y, z) and dimensions (width, height, depth).
	 * The Region can be initialized using a variety of combinations, such as specifying just the size, the origin and size, or the full region in 3D space.
	 * Additionally, it includes methods to retrieve the Origin (the starting point of the region) and the Size (the dimensions of the region).
	 * By default, all values are set to zero.
	 */
	struct Region {
		
		Region() { }
		Region(uint32_t width, uint32_t height) : width(width), height(height), depth(1) { }
		Region(uint32_t width, uint32_t height, uint32_t depth) : width(width), height(height), depth(depth) { }
		Region(uint32_t x, uint32_t y, uint32_t width, uint32_t height) : x(x), y(y), width(width), height(height), depth(1) { }
		Region(uint32_t x, uint32_t y, uint32_t z, uint32_t width, uint32_t height, uint32_t depth) : x(x), y(y), z(z), width(width), height(height), depth(depth) { }
		Region(const Origin &origin, const Size &size) : x(origin.x), y(origin.y), z(origin.z), width(size.width), height(size.height), depth(size.depth) { }
		explicit Region(const Size &size) : width(size.width), height(size.height), depth(size.depth) { }
		
		/// region parameters
		TS_INLINE Origin getOrigin() const { return Origin(x, y, z); }
		TS_INLINE Size getSize() const { return Size(width, height, depth); }
		
		uint32_t x = 0;
		uint32_t y = 0;
		uint32_t z = 0;
		uint32_t width = 0;
		uint32_t height = 0;
		uint32_t depth = 0;
	};
	
	TS_INLINE bool operator==(const Region &r0, const Region &r1) {
		return (r0.x == r1.x && r0.y == r1.y && r0.z == r1.z && r0.width == r1.width && r0.height == r1.height && r0.depth == r1.depth);
	}
	TS_INLINE bool operator!=(const Region &r0, const Region &r1) {
		return (r0.x != r1.x || r0.y != r1.y || r0.z != r1.z || r0.width != r1.width || r0.height != r1.height || r0.depth != r1.depth);
	}
	
	TS_INLINE Region operator+(const Region &r, const Origin &o) {
		TS_ASSERT(r.width > o.x && r.height > o.y && r.depth > o.z && "Region::operator+(): invalid origin");
		return Region(r.x + o.x, r.y + o.y, r.z + o.z, r.width - o.x, r.height - o.y, r.depth - o.z);
	}
	
	TS_INLINE Region operator+(const Region &r, const Size &s) {
		return Region(r.x, r.y, r.z, r.width + s.width, r.height + s.height, r.depth + s.depth);
	}
	TS_INLINE Region operator-(const Region &r, const Size &s) {
		TS_ASSERT(r.width >= s.width && r.height >= s.height && r.depth >= s.depth && "Region::operator-(): invalid size");
		return Region(r.x, r.y, r.z, r.width - s.width, r.height - s.height, r.depth - s.depth);
	}
	
	TS_INLINE Region operator<<(const Region &r, uint32_t m) {
		return Region(r.getOrigin() << m, r.getSize() << m);
	}
	TS_INLINE Region operator>>(const Region &r, uint32_t m) {
		return Region(r.getOrigin() >> m, r.getSize() >> m);
	}
	
	TS_INLINE Region operator*(const Region &r, uint32_t f) {
		return Region(r.getOrigin() * f, r.getSize() * f);
	}
	TS_INLINE Region operator/(const Region &r, uint32_t f) {
		return Region(r.getOrigin() / f, r.getSize() / f);
	}
	
	TS_INLINE Region operator*(const Region &r, float32_t f) {
		return Region(r.getOrigin() * f, r.getSize() * f);
	}
	
	/*****************************************************************************\
	 *
	 * Slice
	 *
	\*****************************************************************************/
	
	/**
	 * The Face struct represents a single face of a cube image.
	 * It contains two members: base, which specifies the base index of the face, and size, which indicates the number of faces.
	 * It is typically used in the context of cube maps, where each face of the cube is treated as an individual image.
	 */
	struct Face {
		
		Face() { }
		explicit Face(uint32_t base) : base(base) { }
		Face(uint32_t base, uint32_t size) : base(base), size(size) { }
		
		uint32_t base = 0;
		uint32_t size = 1;
	};
	
	/**
	 * The Layer struct defines a layer in a texture array, where base specifies the starting index of the layer, and size represents the number of layers.
	 * Layers allow the storage of multiple images in a single texture, typically used for 2D and Cube array textures.
	 */
	struct Layer {
		
		Layer() { }
		explicit Layer(uint32_t base) : base(base) { }
		Layer(uint32_t base, uint32_t size) : base(base), size(size) { }
		
		uint32_t base = 0;
		uint32_t size = 1;
	};
	
	/**
	 * The Mipmap struct represents a level of a mipmap chain.
	 * It has two members: base, indicating the base level of the mipmap, and size, which defines the number of mipmap levels.
	 * Mipmaps are precomputed textures at various levels of detail used in 3D rendering to improve performance and visual quality.
	 */
	struct Mipmap {
		
		Mipmap() { }
		explicit Mipmap(uint32_t base) : base(base) { }
		Mipmap(uint32_t base, uint32_t size) : base(base), size(size) { }
		
		uint32_t base = 0;
		uint32_t size = 1;
	};
	
	/**
	 * The Slice struct defines a specific subset of a texture or image, using faces, layers, and mipmaps.
	 * It can be configured to represent a single face, layer, or mipmap level of an image.
	 * The struct includes methods for checking if the slice has multiple faces, layers, or mipmaps, and for adjusting or replacing slice sizes and bases.
	 */
	struct Slice {
		
		Slice() { }
		Slice(const Face &f) : face(f.base), faces(f.size) { }
		Slice(const Layer &l) : layer(l.base), layers(l.size) { }
		Slice(const Mipmap &m) : mipmap(m.base), mipmaps(m.size) { }
		Slice(const Layer &l, const Face &f) : face(f.base), faces(f.size), layer(l.base), layers(l.size) { }
		Slice(const Face &f, const Mipmap &m) : face(f.base), faces(f.size), mipmap(m.base), mipmaps(m.size) { }
		Slice(const Layer &l, const Mipmap &m) : layer(l.base), layers(l.size), mipmap(m.base), mipmaps(m.size) { }
		Slice(const Layer &l, const Face &f, const Mipmap &m) : face(f.base), faces(f.size), layer(l.base), layers(l.size), mipmap(m.base), mipmaps(m.size) { }
		
		/// slice parameters
		TS_INLINE bool hasFaces() const { return (faces > 1); }
		TS_INLINE bool hasLayers() const { return (layers > 1); }
		TS_INLINE bool hasMipmaps() const { return (mipmaps > 1); }
		TS_INLINE Face getFace() const { return Face(face, faces); }
		TS_INLINE Layer getLayer() const { return Layer(layer, layers); }
		TS_INLINE Mipmap getMipmap() const { return Mipmap(mipmap, mipmaps); }
		
		/// set slice parameters
		Slice setFace(uint32_t base, uint32_t size = 1) const { return Slice(getLayer(), Face(base, size), getMipmap()); }
		Slice setLayer(uint32_t base, uint32_t size = 1) const { return Slice(Layer(base, size), getFace(), getMipmap()); }
		Slice setMipmap(uint32_t base, uint32_t size = 1) const { return Slice(getLayer(), getFace(), Mipmap(base, size)); }
		
		/// replace slice sizes
		Slice setSize(const Slice &s) const {
			TS_ASSERT(s.faces && s.layers && s.mipmaps && "Slice::setSize(): invalid slice");
			return Slice(Layer(layer, s.layers), Face(face, s.faces), Mipmap(mipmap, s.mipmaps));
		}
		
		/// increment slice bases
		Slice addBase(const Slice &s) const {
			TS_ASSERT(faces > s.face && layers > s.layer && mipmaps > s.mipmap && "Slice::addBase(): invalid slice");
			return Slice(Layer(layer + s.layer, layers - s.layer), Face(face + s.face, faces - s.face), Mipmap(mipmap + s.mipmap, mipmaps - s.mipmap));
		}
		
		uint32_t face = 0;
		uint32_t faces = 1;
		uint32_t layer = 0;
		uint32_t layers = 1;
		uint32_t mipmap = 0;
		uint32_t mipmaps = 1;
	};
	
	TS_INLINE bool operator==(const Slice &s0, const Slice &s1) {
		return (s0.face == s1.face && s0.faces == s1.faces && s0.layer == s1.layer && s0.layers == s1.layers && s0.mipmap == s1.mipmap && s0.mipmaps == s1.mipmaps);
	}
	TS_INLINE bool operator!=(const Slice &s0, const Slice &s1) {
		return (s0.face != s1.face || s0.faces != s1.faces || s0.layer != s1.layer || s0.layers != s1.layers || s0.mipmap != s1.mipmap || s0.mipmaps != s1.mipmaps);
	}
	
	/*****************************************************************************\
	 *
	 * Viewport
	 *
	\*****************************************************************************/
	
	/**
	 * The Viewport struct represents a 2D rectangular area in a 3D space used for rendering.
	 * It defines the position and size of the viewport as well as the near and far clipping planes.
	 * The struct contains four main properties: x, y, width, and height, which describe the position and dimensions of the viewport.
	 * It also includes znear and zfar properties, which define the near and far planes for depth clipping.
	 */
	struct Viewport {
		
		Viewport() { }
		Viewport(float32_t width, float32_t height) : width(width), height(height) { }
		Viewport(float32_t x, float32_t y, float32_t width, float32_t height) : x(x), y(y), width(width), height(height) { }
		Viewport(float32_t x, float32_t y, float32_t width, float32_t height, float32_t znear, float32_t zfar) : x(x), y(y), width(width), height(height), znear(znear), zfar(zfar) { }
		
		TS_INLINE float32_t getLeft() const { return x; }
		TS_INLINE float32_t getBottom() const { return y; }
		TS_INLINE float32_t getRight() const { return x + width; }
		TS_INLINE float32_t getTop() const { return y + height; }
		
		float32_t x = 0.0f;
		float32_t y = 0.0f;
		float32_t width = 1.0f;
		float32_t height = 1.0f;
		float32_t znear = 0.0f;
		float32_t zfar = 1.0f;
	};
	
	TS_INLINE bool operator==(const Viewport &v0, const Viewport &v1) {
		return (v0.x == v1.x && v0.y == v1.y && v0.width == v1.width && v0.height == v1.height && v0.znear == v1.znear && v0.zfar == v1.zfar);
	}
	TS_INLINE bool operator!=(const Viewport &v0, const Viewport &v1) {
		return (v0.x != v1.x || v0.y != v1.y || v0.width != v1.width || v0.height != v1.height || v0.znear != v1.znear || v0.zfar != v1.zfar);
	}
	
	/*****************************************************************************\
	 *
	 * Scissor
	 *
	\*****************************************************************************/
	
	/**
	 * The Scissor struct is used to define a clipping region, ensuring that rendering operations only affect the specified area within the defined boundaries.
	 * It is used to optimize rendering or to focus on specific regions of the screen.
	 */
	struct Scissor {
		
		Scissor() { }
		Scissor(int32_t width, int32_t height) : width(width), height(height) { }
		Scissor(int32_t x, int32_t y, int32_t width, int32_t height) : x(x), y(y), width(width), height(height) { }
		
		int32_t x = 0;
		int32_t y = 0;
		int32_t width = Maxi16;
		int32_t height = Maxi16;
	};
	
	TS_INLINE bool operator==(const Scissor &s0, const Scissor &s1) {
		return (s0.x == s1.x && s0.y == s1.y && s0.width == s1.width && s0.height == s1.height);
	}
	TS_INLINE bool operator!=(const Scissor &s0, const Scissor &s1) {
		return (s0.x != s1.x || s0.y != s1.y || s0.width != s1.width || s0.height != s1.height);
	}
}

#endif /* __TELLUSIM_TYPES_H__ */

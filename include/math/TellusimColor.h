// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_MATH_COLOR_H__
#define __TELLUSIM_MATH_COLOR_H__

#include <core/TellusimLog.h>
#include <math/TellusimScalar.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	struct Color;
	
	/// color types
	template <> struct IsPod<Color> { enum { Result = 1 }; };
	
	/*****************************************************************************\
	 *
	 * Color
	 *
	\*****************************************************************************/
	
	/**
	 * The Color struct represents a four-component color with red, green, blue, and alpha channels, offering a flexible and efficient interface for defining, manipulating, and converting colors across different formats.
	 * It supports various constructors, including grayscale, HTML strings, RGBAu8 integers, HSV values, and temperature-based inputs.
	 * The struct provides utilities for setting and retrieving color data, checking color properties, and performing color arithmetic operations.
	 * It includes functions to convert between gamma and linear color spaces, as well as sRGB and linear formats, and supports multiple packed RGBA formats.
	 */
	struct Color final {
		
		Color() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) { }
		explicit Color(const char *src) { setHTML(src); }
		explicit Color(uint32_t color) { setRGBAu8(color); }
		explicit Color(float32_t c) : r(c), g(c), b(c), a(c) { }
		Color(float32_t l, float32_t a) : r(l), g(l), b(l), a(a) { }
		Color(const Color &c, float32_t a) : r(c.r), g(c.g), b(c.b), a(a) { }
		explicit Color(const float32_t *c, uint32_t size = Size) { set(c, size); }
		Color(uint32_t r, uint32_t g, uint32_t b, uint32_t a = 255) { setRGBAu8(r, g, b, a); }
		Color(float32_t r, float32_t g, float32_t b, float32_t a = 1.0f) : r(r), g(g), b(b), a(a) { }
		
		/// update color data
		TS_INLINE void set(const Color &c, float32_t A) {
			r = c.r; g = c.g; b = c.b; a = A;
		}
		TS_INLINE void set(float32_t R, float32_t G, float32_t B, float32_t A) {
			r = R; g = G; b = B; a = A;
		}
		TS_INLINE void set(const float32_t *TS_RESTRICT c, uint32_t size = Size) {
			if(size == 4) {
				r = c[0]; g = c[1]; b = c[2]; a = c[3];
			} else if(size == 3) {
				r = c[0]; g = c[1]; b = c[2]; a = 1.0f;
			} else if(size == 2) {
				r = c[0]; g = c[0]; b = c[0]; a = c[1];
			} else if(size == 1) {
				r = c[0]; g = c[0]; b = c[0]; a = c[0];
			} else {
				TS_ASSERT(0 && "Color::set(): invalid size");
			}
		}
		TS_INLINE void get(float32_t *TS_RESTRICT c, uint32_t size = Size) const {
			if(size == 4) {
				c[0] = r; c[1] = g; c[2] = b; c[3] = a;
			} else if(size == 3) {
				c[0] = r; c[1] = g; c[2] = b;
			} else {
				TS_ASSERT(0 && "Color::get(): invalid size");
			}
		}
		
		/// check color
		TS_INLINE bool isValid() const { return (r != 0.0f || g != 0.0f || b != 0.0f || a != 0.0f); }
		explicit TS_INLINE operator bool() const { return isValid(); }
		
		/// color parameters
		TS_INLINE bool isBlack() const { return (r == 0.0f && g == 0.0f && b == 0.0f); }
		TS_INLINE bool isWhite() const { return (r == 1.0f && g == 1.0f && b == 1.0f); }
		TS_INLINE bool isTransparent() const { return (a == 0.0f); }
		TS_INLINE bool isOpaque() const { return (a == 1.0f); }
		
		/// color operators
		TS_INLINE Color &operator*=(float32_t l) {
			r *= l; g *= l; b *= l; return *this;
		}
		TS_INLINE Color &operator/=(float32_t l) {
			r /= l; g /= l; b /= l; return *this;
		}
		TS_INLINE Color &operator+=(float32_t l) {
			r += l; g += l; b += l; return *this;
		}
		TS_INLINE Color &operator-=(float32_t l) {
			r -= l; g -= l; b -= l; return *this;
		}
		TS_INLINE Color &operator*=(const Color &c) {
			r *= c.r; g *= c.g; b *= c.b; a *= c.a; return *this;
		}
		TS_INLINE Color &operator/=(const Color &c) {
			r /= c.r; g /= c.g; b /= c.b; a /= c.a; return *this;
		}
		TS_INLINE Color &operator+=(const Color &c) {
			r += c.r; g += c.g; b += c.b; a += c.a; return *this;
		}
		TS_INLINE Color &operator-=(const Color &c) {
			r -= c.r; g -= c.g; b -= c.b; a -= c.a; return *this;
		}
		
		/// gamma format
		TS_INLINE void gammaToLinear(float32_t *TS_RESTRICT v) const {
			v[0] = pow(r, 2.2f);
			v[1] = pow(g, 2.2f);
			v[2] = pow(b, 2.2f);
			v[3] = a;
		}
		TS_INLINE void linearToGamma(float32_t *TS_RESTRICT v) const {
			v[0] = pow(r, 1.0f / 2.2f);
			v[1] = pow(g, 1.0f / 2.2f);
			v[2] = pow(b, 1.0f / 2.2f);
			v[3] = a;
		}
		TS_INLINE Color gammaToLinear() const {
			Color ret; gammaToLinear(ret.c); return ret;
		}
		TS_INLINE Color linearToGamma() const {
			Color ret; linearToGamma(ret.c); return ret;
		}
		
		/// sRGB format
		TS_INLINE void sRGBtoLinear(float32_t *TS_RESTRICT v) const {
			v[0] = (r < 0.040449936f) ? r / 12.92f : pow((r + 0.055f) / 1.055f, 2.4f);
			v[1] = (g < 0.040449936f) ? g / 12.92f : pow((g + 0.055f) / 1.055f, 2.4f);
			v[2] = (b < 0.040449936f) ? b / 12.92f : pow((b + 0.055f) / 1.055f, 2.4f);
			v[3] = a;
		}
		TS_INLINE void linearToSRGB(float32_t *TS_RESTRICT v) const {
			v[0] = (r < 0.0031308f) ? r * 12.92f : pow(r, 1.0f / 2.4f) * 1.055f - 0.055f;
			v[1] = (g < 0.0031308f) ? g * 12.92f : pow(g, 1.0f / 2.4f) * 1.055f - 0.055f;
			v[2] = (b < 0.0031308f) ? b * 12.92f : pow(b, 1.0f / 2.4f) * 1.055f - 0.055f;
			v[3] = a;
		}
		TS_INLINE Color sRGBtoLinear() const {
			Color ret; sRGBtoLinear(ret.c); return ret;
		}
		TS_INLINE Color linearToSRGB() const {
			Color ret; linearToSRGB(ret.c); return ret;
		}
		
		/// RGBAu8 color components
		void setRGBAu8(uint32_t R, uint32_t G, uint32_t B, uint32_t A) {
			r = (float32_t)(R & 255u) / 255.0f;
			g = (float32_t)(G & 255u) / 255.0f;
			b = (float32_t)(B & 255u) / 255.0f;
			a = (float32_t)(A & 255u) / 255.0f;
		}
		TS_INLINE uint8_t getRu8() const { return (uint8_t)(clamp(r, 0.0f, 1.0f) * 255.0f); }
		TS_INLINE uint8_t getGu8() const { return (uint8_t)(clamp(g, 0.0f, 1.0f) * 255.0f); }
		TS_INLINE uint8_t getBu8() const { return (uint8_t)(clamp(b, 0.0f, 1.0f) * 255.0f); }
		TS_INLINE uint8_t getAu8() const { return (uint8_t)(clamp(a, 0.0f, 1.0f) * 255.0f); }
		
		/// RGBAu8 color format
		void setRGBAu8(uint32_t color) { setRGBAu8(color >> 0u, color >> 8u, color >> 16u, color >> 24u); }
		void setBGRAu8(uint32_t color) { setRGBAu8(color >> 16u, color >> 8u, color >> 0u, color >> 24u); }
		void setABGRu8(uint32_t color) { setRGBAu8(color >> 24u, color >> 16u, color >> 8u, color >> 0u); }
		uint32_t getRGBAu8() const { return (getRu8() << 0u) | (getGu8() << 8u) | (getBu8() << 16u) | (getAu8() << 24u); }
		uint32_t getBGRAu8() const { return (getRu8() << 16u) | (getGu8() << 8u) | (getBu8() << 0u) | (getAu8() << 24u); }
		uint32_t getABGRu8() const { return (getRu8() << 24u) | (getGu8() << 16u) | (getBu8() << 8u) | (getAu8() << 0u); }
		
		/// HTML color format
		TS_API bool setHTML(const char *src);
		static Color html(const char *src) {
			Color ret; ret.setHTML(src); return ret;
		}
		
		/// HSV color format
		TS_API bool setHSV(float32_t h, float32_t s, float32_t v);
		TS_API bool getHSV(float32_t &h, float32_t &s, float32_t &v) const;
		static Color hsv(float32_t h, float32_t s, float32_t v) {
			Color ret; ret.setHSV(h, s, v); return ret;
		}
		
		/// temperature in K
		TS_API void setTemperature(float32_t t);
		static Color temperature(float32_t t) {
			Color ret; ret.setTemperature(t); return ret;
		}
		
		/// Color data
		TS_INLINE const float32_t &operator[](uint32_t index) const {
			TS_ASSERT(index < Size);
			return c[index];
		}
		TS_INLINE float32_t &operator[](uint32_t index) {
			TS_ASSERT(index < Size);
			return c[index];
		}
		
		/// default colors
		TS_API static const Color zero;
		TS_API static const Color black;
		TS_API static const Color white;
		TS_API static const Color gray;
		
		/// rgb colors
		TS_API static const Color red;
		TS_API static const Color yellow;
		TS_API static const Color green;
		TS_API static const Color cyan;
		TS_API static const Color blue;
		TS_API static const Color magenta;
		
		enum {
			Size = 4,
		};
		
		union {
			struct {
				float32_t r, g, b, a;
			};
			float32_t c[Size];
		};
	};
	
	/// color to scalar operators
	TS_INLINE Color operator*(const Color &c, float32_t l) {
		return Color(c.r * l, c.g * l, c.b * l, c.a);
	}
	TS_INLINE Color operator/(const Color &c, float32_t l) {
		return Color(c.r / l, c.g / l, c.b / l, c.a);
	}
	TS_INLINE Color operator+(const Color &c, float32_t l) {
		return Color(c.r + l, c.g + l, c.b + l, c.a);
	}
	TS_INLINE Color operator-(const Color &c, float32_t l) {
		return Color(c.r - l, c.g - l, c.b - l, c.a);
	}
	
	/// color to color operators
	TS_INLINE Color operator*(const Color &c0, const Color &c1) {
		return Color(c0.r * c1.r, c0.g * c1.g, c0.b * c1.b, c0.a * c1.a);
	}
	TS_INLINE Color operator/(const Color &c0, const Color &c1) {
		return Color(c0.r / c1.r, c0.g / c1.g, c0.b / c1.b, c0.a / c1.a);
	}
	TS_INLINE Color operator+(const Color &c0, const Color &c1) {
		return Color(c0.r + c1.r, c0.g + c1.g, c0.b + c1.b, c0.a + c1.a);
	}
	TS_INLINE Color operator-(const Color &c0, const Color &c1) {
		return Color(c0.r - c1.r, c0.g - c1.g, c0.b - c1.b, c0.a - c1.a);
	}
	
	/// comparison operators
	TS_INLINE bool operator==(const Color &c0, const Color &c1) {
		return (c0.r == c1.r && c0.g == c1.g && c0.b == c1.b && c0.a == c1.a);
	}
	TS_INLINE bool operator!=(const Color &c0, const Color &c1) {
		return (c0.r != c1.r || c0.g != c1.g || c0.b != c1.b || c0.a != c1.a);
	}
	TS_INLINE bool compare(const Color &c0, const Color &c1, float32_t a) {
		return (compare(c0.r, c1.r, a) && compare(c0.g, c1.g, a) && compare(c0.b, c1.b, a) && compare(c0.a, c1.a, a));
	}
	TS_INLINE bool compare(const Color &c0, const Color &c1, float32_t a, float32_t r) {
		return (compare(c0.r, c1.r, a, r) && compare(c0.g, c1.g, a, r) && compare(c0.b, c1.b, a, r) && compare(c0.a, c1.a, a, r));
	}
	
	/// min/max functions
	TS_INLINE Color min(const Color &c0, const Color &c1) {
		return Color(min(c0.r, c1.r), min(c0.g, c1.g), min(c0.b, c1.b), min(c0.a, c1.a));
	}
	TS_INLINE Color max(const Color &c0, const Color &c1) {
		return Color(max(c0.r, c1.r), max(c0.g, c1.g), max(c0.b, c1.b), max(c0.a, c1.a));
	}
	
	/// range functions
	TS_INLINE Color saturate(const Color &c) {
		return Color(saturate(c.r), saturate(c.g), saturate(c.b), saturate(c.a));
	}
	TS_INLINE Color clamp(const Color &c, float32_t c0, float32_t c1) {
		return Color(clamp(c.r, c0, c1), clamp(c.g, c0, c1), clamp(c.b, c0, c1), clamp(c.a, c0, c1));
	}
	TS_INLINE Color clamp(const Color &c, const Color &c0, const Color &c1) {
		return Color(clamp(c.r, c0.r, c1.r), clamp(c.g, c0.g, c1.g), clamp(c.b, c0.b, c1.b), clamp(c.a, c0.a, c1.a));
	}
	
	/// color functions
	TS_INLINE float32_t length2(const Color &c) {
		return c.r * c.r + c.g * c.g + c.b * c.b;
	}
	TS_INLINE float32_t length(const Color &c) {
		return sqrt(length2(c));
	}
	TS_INLINE Color normalize(const Color &c) {
		return c * Color(rsqrt(length2(c)), 1.0f);
	}
	TS_INLINE Color lerp(const Color &c0, const Color &c1, float32_t k) {
		return c0 + (c1 - c0) * Color(k, k);
	}
	TS_INLINE Color lerp(const Color &c0, const Color &c1, const Color &k) {
		return c0 + (c1 - c0) * k;
	}
}

#endif /* __TELLUSIM_MATH_COLOR_H__ */

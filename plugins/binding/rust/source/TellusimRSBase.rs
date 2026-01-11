// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

use std::fmt;
use std::mem;
use std::ops;
use std::ptr;
use std::ffi::{ c_void, c_char, CStr, CString };

pub use crate::math::*;
pub use crate::api::*;

/* 8-bit integer constants
 */
pub const MINI8: i32 = -127 - 1;
pub const MAXI8: i32 =  127;
pub const MAXU8: u32 = 255;

/* 16-bit integer constants
 */
pub const MINI16: i32 = -32767 - 1;
pub const MAXI16: i32 =  32767;
pub const MAXU16: u32 = 65535;

/* 32-bit integer constants
 */
pub const MINI32: i32 = -2147483647 - 1;
pub const MAXI32: i32 =  2147483647;
pub const MAXU32: u32 = 4294967295;

/* 64-bit integer constants
 */
pub const MINI64: i64 = -9223372036854775807 - 1;
pub const MAXI64: i64 =  9223372036854775807;
pub const MAXU64: u64 = 18446744073709551615;

/* 16-bit floating point constants
 */
pub const MINF16: f32 = 5.96046448e-08;
pub const MAXF16: f32 = 65504.0;

/* 32-bit floating point constants
 */
pub const MINF32: f32 = 1.17549435e-38;
pub const MAXF32: f32 = 3.40282346e+38;
pub const PI: f32 = 3.141592653589793;
pub const PI2: f32 = 6.283185307179586;
pub const PI05: f32 = 1.570796326794897;
pub const SQRT2: f32 = 1.4142135623730951;
pub const DEG2RAD: f32 = 0.017453292519943;
pub const RAD2DEG: f32 = 57.295779513082325;

/* 64-bit floating point constants
 */
pub const MINF64: f64 = 2.22507385850720138e-308;
pub const MAXF64: f64 = 1.79769313486231571e+308;
pub const PID: f64 = 3.141592653589793115997963468544;
pub const PI2D: f64 = 6.283185307179586231995926937088;
pub const PI05D: f64 = 1.570796326794896557998981734272;
pub const SQRT2D: f64 = 1.414213562373095145474621858739;
pub const DEG2RADD: f64 = 0.017453292519943295474371680598;
pub const RAD2DEGD: f64 = 57.295779513082322864647721871734;

/*****************************************************************************\
 *
 * Utils
 *
\*****************************************************************************/

/*
 */
pub fn get_cstring(string: *const c_char) -> std::string::String {
	unsafe {
		CStr::from_ptr(string).to_string_lossy().into_owned()
	}
}

pub fn get_string(this: *mut c_void) -> std::string::String {
	unsafe {
		let ret = CStr::from_ptr(tsString_get_c(this)).to_string_lossy().into_owned();
		tsString_delete(this);
		ret
	}
}

/*
 */
extern "C" {
	fn tsString_delete(this: *mut c_void);
	fn tsString_get_c(this: *const c_void) -> *const c_char;
}

/*****************************************************************************\
 *
 * Log
 *
\*****************************************************************************/

/*
 */
#[macro_export]
macro_rules! ts_log {
	($level:ident, $str:expr) => {
		log::print_with_level(LogLevel::$level, $str);
	}
}

#[macro_export]
macro_rules! ts_loge {
	($level:ident, $str:expr) => {
		log::printe(LogLevel::$level, $str);
	}
}

#[macro_export]
macro_rules! ts_logf {
	($level:ident, $($args:expr),*) => {
		log::print_with_level(LogLevel::$level, &format!($($args),*));
	}
}

#[macro_export]
macro_rules! ts_logef {
	($level:ident, $($args:expr),*) => {
		log::printe(LogLevel::$level, &format!($($args),*));
	}
}

/*****************************************************************************\
 *
 * Color
 *
\*****************************************************************************/

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct Color {
	pub r: f32,
	pub g: f32,
	pub b: f32,
	pub a: f32,
}

/*
 */
impl Color {
	
	pub fn new_s(c: f32) -> Color {
		Color { r: c, g: c, b: c, a: c }
	}
	pub fn new_la(l: f32, a: f32) -> Color {
		Color { r: l, g: l, b: l, a: a }
	}
	pub fn new_rgb(r: f32, g: f32, b: f32) -> Color {
		Color { r: r, g: g, b: b, a: 1.0 }
	}
	pub fn new(r: f32, g: f32, b: f32, a: f32) -> Color {
		Color { r: r, g: g, b: b, a: a }
	}
	pub fn new_a(c: &[f32]) -> Color {
		Color { r: c[0], g: c[1], b: c[2], a: c[3] }
	}
	
	pub fn gamma_to_linear(&self) -> Color {
		let mut ret = Color::default();
		unsafe { tsColor_gammaToLinear(&mut ret, self); }
		ret
	}
	pub fn linear_to_gamma(&self) -> Color {
		let mut ret = Color::default();
		unsafe { tsColor_linearToGamma(&mut ret, self); }
		ret
	}
	
	pub fn srgb_to_linear(&self) -> Color {
		let mut ret = Color::default();
		unsafe { tsColor_sRGBtoLinear(&mut ret, self); }
		ret
	}
	pub fn linear_to_srgb(&self) -> Color {
		let mut ret = Color::default();
		unsafe { tsColor_linearToSRGB(&mut ret, self); }
		ret
	}
	
	pub fn set_rgbau8(&mut self, color: u32) {
		unsafe { tsColor_setRGBAu8(self, color) }
	}
	pub fn rgbau8(&self) -> u32 {
		unsafe { tsColor_getRGBAu8(self) }
	}
	
	pub fn set_bgrau8(&mut self, color: u32) {
		unsafe { tsColor_setBGRAu8(self, color) }
	}
	pub fn bgrau8(&self) -> u32 {
		unsafe { tsColor_getBGRAu8(self) }
	}
	
	pub fn set_abgru8(&mut self, color: u32) {
		unsafe { tsColor_setABGRu8(self, color) }
	}
	pub fn abgru8(&self) -> u32 {
		unsafe { tsColor_getABGRu8(self) }
	}
	
	pub fn html(src: &str) -> Color {
		let mut ret = Color::default();
		let src_ = CString::new(src).unwrap();
		unsafe { tsColor_html(&mut ret, src_.as_ptr()); }
		ret
	}
	pub fn hsv(h: f32, s: f32, v: f32) -> Color {
		let mut ret = Color::default();
		unsafe { tsColor_hsv(&mut ret, h, s, v); }
		ret
	}
	pub fn temperature(t: f32) -> Color {
		let mut ret = Color::default();
		unsafe { tsColor_temperature(&mut ret, t); }
		ret
	}
	
	pub fn min(c0: &Color, c1: &Color) -> Color {
		let mut ret = Color::default();
		unsafe { tsColor_min(&mut ret, c0, c1); }
		ret
	}
	pub fn max(c0: &Color, c1: &Color) -> Color {
		let mut ret = Color::default();
		unsafe { tsColor_max(&mut ret, c0, c1); }
		ret
	}
	
	pub fn clamp(&self, c0: &Color, c1: &Color) -> Color {
		let mut ret = Color::default();
		unsafe { tsColor_clamp(&mut ret, self, c0, c1); }
		ret
	}
	pub fn saturate(&self) -> Color {
		let mut ret = Color::default();
		unsafe { tsColor_saturate(&mut ret, self); }
		ret
	}
	
	pub fn lerp(c0: &Color, c1: &Color, k: f32) -> Color {
		let mut ret = Color::default();
		unsafe { tsColor_lerp(&mut ret, c0, c1, k); }
		ret
	}
	
	pub fn zero() -> Color {
		Color { r: 0.0, g: 0.0, b: 0.0, a: 0.0 }
	}
	pub fn black() -> Color {
		Color { r: 0.0, g: 0.0, b: 0.0, a: 1.0 }
	}
	pub fn white() -> Color {
		Color { r: 1.0, g: 1.0, b: 1.0, a: 1.0 }
	}
	pub fn gray() -> Color {
		Color { r: 0.5, g: 0.5, b: 0.5, a: 1.0 }
	}
	
	pub fn red() -> Color {
		Color { r: 1.0, g: 0.0, b: 0.0, a: 1.0 }
	}
	pub fn yellow() -> Color {
		Color { r: 1.0, g: 1.0, b: 0.0, a: 1.0 }
	}
	pub fn green() -> Color {
		Color { r: 0.0, g: 1.0, b: 0.0, a: 1.0 }
	}
	pub fn cyan() -> Color {
		Color { r: 0.0, g: 1.0, b: 1.0, a: 1.0 }
	}
	pub fn blue() -> Color {
		Color { r: 0.0, g: 0.0, b: 1.0, a: 1.0 }
	}
	pub fn magenta() -> Color {
		Color { r: 1.0, g: 0.0, b: 1.0, a: 1.0 }
	}
}

/*
 */
impl fmt::Display for Color {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "({0} {1} {2} {3})", self.r, self.g, self.b, self.a)
	}
}

/*
 */
super::declare_scalar_op!(Color, f32, Mul, mul, tsColor_mul1);
super::declare_scalar_op!(Color, f32, Div, div, tsColor_div1);
super::declare_scalar_op!(Color, f32, Add, add, tsColor_add1);
super::declare_scalar_op!(Color, f32, Sub, sub, tsColor_sub1);

/*
 */
super::declare_vector_op!(Color, Mul, mul, tsColor_mul);
super::declare_vector_op!(Color, Div, div, tsColor_div);
super::declare_vector_op!(Color, Add, add, tsColor_add);
super::declare_vector_op!(Color, Sub, sub, tsColor_sub);

/*
 */
extern "C" {
	fn tsColor_gammaToLinear(ret: *mut Color, c: *const Color) -> *mut Color;
	fn tsColor_linearToGamma(ret: *mut Color, c: *const Color) -> *mut Color;
	fn tsColor_sRGBtoLinear(ret: *mut Color, c: *const Color) -> *mut Color;
	fn tsColor_linearToSRGB(ret: *mut Color, c: *const Color) -> *mut Color;
	fn tsColor_setRGBAu8(c: *mut Color, color: u32);
	fn tsColor_getRGBAu8(c: *const Color) -> u32;
	fn tsColor_setBGRAu8(c: *mut Color, color: u32);
	fn tsColor_getBGRAu8(c: *const Color) -> u32;
	fn tsColor_setABGRu8(c: *mut Color, color: u32);
	fn tsColor_getABGRu8(c: *const Color) -> u32;
	fn tsColor_html(ret: *mut Color, src: *const c_char) -> *mut Color;
	fn tsColor_hsv(ret: *mut Color, h: f32, s: f32, v: f32) -> *mut Color;
	fn tsColor_temperature(ret: *mut Color, t: f32) -> *mut Color;
	fn tsColor_mul1(ret: *mut Color, c0: *const Color, c1: f32) -> *mut Color;
	fn tsColor_div1(ret: *mut Color, c0: *const Color, c1: f32) -> *mut Color;
	fn tsColor_add1(ret: *mut Color, c0: *const Color, c1: f32) -> *mut Color;
	fn tsColor_sub1(ret: *mut Color, c0: *const Color, c1: f32) -> *mut Color;
	fn tsColor_mul(ret: *mut Color, c0: *const Color, c1: *const Color) -> *mut Color;
	fn tsColor_div(ret: *mut Color, c0: *const Color, c1: *const Color) -> *mut Color;
	fn tsColor_add(ret: *mut Color, c0: *const Color, c1: *const Color) -> *mut Color;
	fn tsColor_sub(ret: *mut Color, c0: *const Color, c1: *const Color) -> *mut Color;
	fn tsColor_min(ret: *mut Color, c0: *const Color, c1: *const Color) -> *mut Color;
	fn tsColor_max(ret: *mut Color, c0: *const Color, c1: *const Color) -> *mut Color;
	fn tsColor_clamp(ret: *mut Color, c: *const Color, c0: *const Color, c1: *const Color) -> *mut Color;
	fn tsColor_saturate(ret: *mut Color, c: *const Color) -> *mut Color;
	fn tsColor_lerp(ret: *mut Color, c0: *const Color, c1: *const Color, k: f32) -> *mut Color;
}

/*****************************************************************************\
 *
 * ImageColor
 *
\*****************************************************************************/

/*
 */
#[repr(C, align(16))]
#[derive(Copy, Clone, Default)]
pub struct ImageColor {
	pub r: u32,
	pub g: u32,
	pub b: u32,
	pub a: u32,
}

/*
 */
impl ImageColor {
	
	pub fn new_s(c: u32) -> ImageColor {
		ImageColor { r: c, g: c, b: c, a: c }
	}
	pub fn new_la(l: u32, a: u32) -> ImageColor {
		ImageColor { r: l, g: l, b: l, a: a }
	}
	pub fn new_rgb(r: u32, g: u32, b: u32) -> ImageColor {
		ImageColor { r: r, g: g, b: b, a: 255 }
	}
	pub fn new_v4i(v: &Vector4i) -> ImageColor {
		ImageColor { r: v.x as u32, g: v.y as u32, b: v.z as u32, a: v.w as u32 }
	}
	pub fn new_v4u(v: &Vector4u) -> ImageColor {
		ImageColor { r: v.x, g: v.y, b: v.z, a: v.w }
	}
	pub fn new_v4f(v: &Vector4f) -> ImageColor {
		let mut ret = ImageColor::default();
		unsafe { tsImageColor_set_f(&mut ret, v); }
		ret
	}
	pub fn new_cf(c: &Color, format: Format) -> ImageColor {
		let mut ret = ImageColor::default();
		unsafe { tsImageColor_set_c(&mut ret, c, format); }
		ret
	}
	pub fn new_a(c: &[u32]) -> ImageColor {
		ImageColor { r: c[0], g: c[1], b: c[2], a: c[3] }
	}
	
	pub fn set_v4i(&mut self, v: &Vector4i) {
		unsafe { tsImageColor_set_i(self, v); }
	}
	pub fn v4i(&self) -> Vector4i {
		let mut ret = Vector4i::default();
		unsafe { tsImageColor_get_i(self, &mut ret); }
		ret
	}
	pub fn set_v4u(&mut self, v: &Vector4u) {
		unsafe { tsImageColor_set_u(self, v); }
	}
	pub fn v4u(&self) -> Vector4u {
		let mut ret = Vector4u::default();
		unsafe { tsImageColor_get_u(self, &mut ret); }
		ret
	}
	pub fn set_v4f(&mut self, v: &Vector4f) {
		unsafe { tsImageColor_set_f(self, v); }
	}
	pub fn v4f(&self) -> Vector4f {
		let mut ret = Vector4f::default();
		unsafe { tsImageColor_get_f(self, &mut ret); }
		ret
	}
	pub fn set_color(&mut self, c: &Color, format: Format) {
		unsafe { tsImageColor_set_c(self, c, format); }
	}
	pub fn color(&self, format: Format) -> Color {
		let mut ret = Color::default();
		unsafe { tsImageColor_get_c(self, &mut ret, format); }
		ret
	}
}

/*
 */
impl fmt::Display for ImageColor {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "({0} {1} {2} {3})", self.r, self.g, self.b, self.a)
	}
}

/*
 */
extern "C" {
	fn tsImageColor_set_i(c: *mut ImageColor, src: *const Vector4i);
	fn tsImageColor_get_i(c: *const ImageColor, dest: *mut Vector4i);
	fn tsImageColor_set_u(c: *mut ImageColor, src: *const Vector4u);
	fn tsImageColor_get_u(c: *const ImageColor, dest: *mut Vector4u);
	fn tsImageColor_set_f(c: *mut ImageColor, src: *const Vector4f);
	fn tsImageColor_get_f(c: *const ImageColor, dest: *mut Vector4f);
	fn tsImageColor_set_c(c: *mut ImageColor, src: *const Color, format: Format);
	fn tsImageColor_get_c(c: *const ImageColor, dest: *mut Color, format: Format);
}

/*****************************************************************************\
 *
 * BoundRect
 *
\*****************************************************************************/

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct BoundRectf {
	pub min: Vector2f,
	pub max: Vector2f,
}

impl BoundRectf {
	
	pub fn new(min: &Vector2f, max: &Vector2f) -> BoundRectf {
		BoundRectf { min: *min, max: *max }
	}
	pub fn new_brd(br: &BoundRectd) -> BoundRectf {
		let mut ret = BoundRectf::default();
		unsafe { tsBoundRectf_set_brd(&mut ret, br); }
		ret
	}
	pub fn new_bc(bc: &BoundCirclef) -> BoundRectf {
		let mut ret = BoundRectf::default();
		unsafe { tsBoundRectf_set_bc(&mut ret, bc); }
		ret
	}
	
	pub fn expand_v(&mut self, v: &Vector2f) {
		unsafe { tsBoundRectf_expand1(self, v); }
	}
	pub fn expand(&mut self, br: &BoundRectf) {
		unsafe { tsBoundRectf_expand(self, br); }
	}
	
	pub fn inside_v(&self, v: &Vector2f) -> bool {
		unsafe { tsBoundRectf_inside1(self, v) }
	}
	pub fn inside(&self, br: &BoundRectf) -> bool {
		unsafe { tsBoundRectf_inside(self, br) }
	}
	
	pub fn distance(&self, v: &Vector2f) -> f32 {
		unsafe { tsBoundRectf_distance(self, v) }
	}
}

impl fmt::Display for BoundRectf {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "{0} : {1}", self.min, self.max)
	}
}

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct BoundRectd {
	pub min: Vector2d,
	pub max: Vector2d,
}

impl BoundRectd {
	
	pub fn new(min: &Vector2d, max: &Vector2d) -> BoundRectd {
		BoundRectd { min: *min, max: *max }
	}
	pub fn new_brf(br: &BoundRectf) -> BoundRectd {
		let mut ret = BoundRectd::default();
		unsafe { tsBoundRectd_set_brf(&mut ret, br); }
		ret
	}
	pub fn new_bc(bc: &BoundCircled) -> BoundRectd {
		let mut ret = BoundRectd::default();
		unsafe { tsBoundRectd_set_bc(&mut ret, bc); }
		ret
	}
	
	pub fn expand_v(&mut self, v: &Vector2d) {
		unsafe { tsBoundRectd_expand1(self, v); }
	}
	pub fn expand(&mut self, br: &BoundRectd) {
		unsafe { tsBoundRectd_expand(self, br); }
	}
	
	pub fn inside_v(&self, v: &Vector2d) -> bool {
		unsafe { tsBoundRectd_inside1(self, v) }
	}
	pub fn inside(&self, br: &BoundRectd) -> bool {
		unsafe { tsBoundRectd_inside(self, br) }
	}
	
	pub fn distance(&self, v: &Vector2d) -> f64 {
		unsafe { tsBoundRectd_distance(self, v) }
	}
}

impl fmt::Display for BoundRectd {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "{0} : {1}", self.min, self.max)
	}
}

/*
 */
extern "C" {
	fn tsBoundRectf_set_brd(ret: *mut BoundRectf, r: *const BoundRectd) -> *mut BoundRectf;
	fn tsBoundRectf_set_bc(ret: *mut BoundRectf, c: *const BoundCirclef) -> *mut BoundRectf;
	fn tsBoundRectf_expand1(ret: *mut BoundRectf, v: *const Vector2f) -> *mut BoundRectf;
	fn tsBoundRectf_expand(ret: *mut BoundRectf, r: *const BoundRectf) -> *mut BoundRectf;
	fn tsBoundRectf_inside1(br: *const BoundRectf, v: *const Vector2f) -> bool;
	fn tsBoundRectf_inside(br: *const BoundRectf, r: *const BoundRectf) -> bool;
	fn tsBoundRectf_distance(br: *const BoundRectf, v: *const Vector2f) -> f32;
}

extern "C" {
	fn tsBoundRectd_set_brf(ret: *mut BoundRectd, r: *const BoundRectf) -> *mut BoundRectd;
	fn tsBoundRectd_set_bc(ret: *mut BoundRectd, c: *const BoundCircled) -> *mut BoundRectd;
	fn tsBoundRectd_expand1(ret: *mut BoundRectd, v: *const Vector2d) -> *mut BoundRectd;
	fn tsBoundRectd_expand(ret: *mut BoundRectd, r: *const BoundRectd) -> *mut BoundRectd;
	fn tsBoundRectd_inside1(br: *const BoundRectd, v: *const Vector2d) -> bool;
	fn tsBoundRectd_inside(br: *const BoundRectd, r: *const BoundRectd) -> bool;
	fn tsBoundRectd_distance(br: *const BoundRectd, v: *const Vector2d) -> f64;
}

/*****************************************************************************\
 *
 * BoundCircle
 *
\*****************************************************************************/

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct BoundCirclef {
	pub center: Vector2f,
	pub radius: f32,
}

impl BoundCirclef {
	
	pub fn new(center: &Vector2f, radius: f32) -> BoundCirclef {
		BoundCirclef { center: *center, radius: radius }
	}
	pub fn new_bcd(bc: &BoundCircled) -> BoundCirclef {
		let mut ret = BoundCirclef::default();
		unsafe { tsBoundCirclef_set_bcd(&mut ret, bc); }
		ret
	}
	pub fn new_br(br: &BoundRectf) -> BoundCirclef {
		let mut ret = BoundCirclef::default();
		unsafe { tsBoundCirclef_set_br(&mut ret, br); }
		ret
	}
	
	pub fn expand_v(&mut self, v: &Vector2f) {
		unsafe { tsBoundCirclef_expand1(self, v); }
	}
	pub fn expand(&mut self, bc: &BoundCirclef) {
		unsafe { tsBoundCirclef_expand(self, bc); }
	}
	
	pub fn expand_radius_v(&mut self, v: &Vector2f) {
		unsafe { tsBoundCirclef_expandRadius1(self, v); }
	}
	pub fn expand_radius(&mut self, bc: &BoundCirclef) {
		unsafe { tsBoundCirclef_expandRadius(self, bc); }
	}
	
	pub fn inside_v(&self, v: &Vector2f) -> bool {
		unsafe { tsBoundCirclef_inside1(self, v) }
	}
	pub fn inside(&self, bc: &BoundCirclef) -> bool {
		unsafe { tsBoundCirclef_inside(self, bc) }
	}
	
	pub fn distance(&self, v: &Vector2f) -> f32 {
		unsafe { tsBoundCirclef_distance(self, v) }
	}
}

impl fmt::Display for BoundCirclef {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "{0} : {1}", self.center, self.radius)
	}
}

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct BoundCircled {
	pub center: Vector2d,
	pub radius: f64,
}

impl BoundCircled {
	
	pub fn new(center: &Vector2d, radius: f64) -> BoundCircled {
		BoundCircled { center: *center, radius: radius }
	}
	pub fn new_bcf(bc: &BoundCirclef) -> BoundCircled {
		let mut ret = BoundCircled::default();
		unsafe { tsBoundCircled_set_bcf(&mut ret, bc); }
		ret
	}
	pub fn new_br(br: &BoundRectd) -> BoundCircled {
		let mut ret = BoundCircled::default();
		unsafe { tsBoundCircled_set_br(&mut ret, br); }
		ret
	}
	
	pub fn expand_v(&mut self, v: &Vector2d) {
		unsafe { tsBoundCircled_expand1(self, v); }
	}
	pub fn expand(&mut self, bc: &BoundCircled) {
		unsafe { tsBoundCircled_expand(self, bc); }
	}
	
	pub fn expand_radius_v(&mut self, v: &Vector2d) {
		unsafe { tsBoundCircled_expandRadius1(self, v); }
	}
	pub fn expand_radius(&mut self, bc: &BoundCircled) {
		unsafe { tsBoundCircled_expandRadius(self, bc); }
	}
	
	pub fn inside_v(&self, v: &Vector2d) -> bool {
		unsafe { tsBoundCircled_inside1(self, v) }
	}
	pub fn inside(&self, bc: &BoundCircled) -> bool {
		unsafe { tsBoundCircled_inside(self, bc) }
	}
	
	pub fn distance(&self, v: &Vector2d) -> f64 {
		unsafe { tsBoundCircled_distance(self, v) }
	}
}

impl fmt::Display for BoundCircled {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "{0} : {1}", self.center, self.radius)
	}
}

/*
 */
extern "C" {
	fn tsBoundCirclef_set_bcd(ret: *mut BoundCirclef, c: *const BoundCircled) -> *mut BoundCirclef;
	fn tsBoundCirclef_set_br(ret: *mut BoundCirclef, r: *const BoundRectf) -> *mut BoundCirclef;
	fn tsBoundCirclef_expand1(ret: *mut BoundCirclef, v: *const Vector2f) -> *mut BoundCirclef;
	fn tsBoundCirclef_expand(ret: *mut BoundCirclef, c: *const BoundCirclef) -> *mut BoundCirclef;
	fn tsBoundCirclef_expandRadius1(ret: *mut BoundCirclef, v: *const Vector2f) -> *mut BoundCirclef;
	fn tsBoundCirclef_expandRadius(ret: *mut BoundCirclef, c: *const BoundCirclef) -> *mut BoundCirclef;
	fn tsBoundCirclef_inside1(bc: *const BoundCirclef, v: *const Vector2f) -> bool;
	fn tsBoundCirclef_inside(bc: *const BoundCirclef, c: *const BoundCirclef) -> bool;
	fn tsBoundCirclef_distance(bc: *const BoundCirclef, v: *const Vector2f) -> f32;
}

extern "C" {
	fn tsBoundCircled_set_bcf(ret: *mut BoundCircled, c: *const BoundCirclef) -> *mut BoundCircled;
	fn tsBoundCircled_set_br(ret: *mut BoundCircled, r: *const BoundRectd) -> *mut BoundCircled;
	fn tsBoundCircled_expand1(ret: *mut BoundCircled, v: *const Vector2d) -> *mut BoundCircled;
	fn tsBoundCircled_expand(ret: *mut BoundCircled, c: *const BoundCircled) -> *mut BoundCircled;
	fn tsBoundCircled_expandRadius1(ret: *mut BoundCircled, v: *const Vector2d) -> *mut BoundCircled;
	fn tsBoundCircled_expandRadius(ret: *mut BoundCircled, c: *const BoundCircled) -> *mut BoundCircled;
	fn tsBoundCircled_inside1(bc: *const BoundCircled, v: *const Vector2d) -> bool;
	fn tsBoundCircled_inside(bc: *const BoundCircled, c: *const BoundCircled) -> bool;
	fn tsBoundCircled_distance(bc: *const BoundCircled, v: *const Vector2d) -> f64;
}

/*****************************************************************************\
 *
 * BoundBox
 *
\*****************************************************************************/

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct BoundBoxf {
	pub min: Vector3f,
	pub max: Vector3f,
}

impl BoundBoxf {
	
	pub fn new(min: &Vector3f, max: &Vector3f) -> BoundBoxf {
		BoundBoxf { min: *min, max: *max }
	}
	pub fn new_bbd(bb: &BoundBoxd) -> BoundBoxf {
		let mut ret = BoundBoxf::default();
		unsafe { tsBoundBoxf_set_bbd(&mut ret, bb); }
		ret
	}
	pub fn new_bs(bs: &BoundSpheref) -> BoundBoxf {
		let mut ret = BoundBoxf::default();
		unsafe { tsBoundBoxf_set_bs(&mut ret, bs); }
		ret
	}
	
	pub fn expand_v(&mut self, v: &Vector3f) {
		unsafe { tsBoundBoxf_expand1(self, v); }
	}
	pub fn expand(&mut self, bb: &BoundBoxf) {
		unsafe { tsBoundBoxf_expand(self, bb); }
	}
	
	pub fn inside_v(&self, v: &Vector3f) -> bool {
		unsafe { tsBoundBoxf_inside1(self, v) }
	}
	pub fn inside(&self, bb: &BoundBoxf) -> bool {
		unsafe { tsBoundBoxf_inside(self, bb) }
	}
	
	pub fn distance(&self, v: &Vector3f) -> f32 {
		unsafe { tsBoundBoxf_distance(self, v) }
	}
}

impl fmt::Display for BoundBoxf {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "{0} : {1}", self.min, self.max)
	}
}

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct BoundBoxd {
	pub min: Vector3d,
	pub max: Vector3d,
}

impl BoundBoxd {
	
	pub fn new(min: &Vector3d, max: &Vector3d) -> BoundBoxd {
		BoundBoxd { min: *min, max: *max }
	}
	pub fn new_bbf(bb: &BoundBoxf) -> BoundBoxd {
		let mut ret = BoundBoxd::default();
		unsafe { tsBoundBoxd_set_bbf(&mut ret, bb); }
		ret
	}
	pub fn new_bs(bs: &BoundSphered) -> BoundBoxd {
		let mut ret = BoundBoxd::default();
		unsafe { tsBoundBoxd_set_bs(&mut ret, bs); }
		ret
	}
	
	pub fn expand_v(&mut self, v: &Vector3d) {
		unsafe { tsBoundBoxd_expand1(self, v); }
	}
	pub fn expand(&mut self, bb: &BoundBoxd) {
		unsafe { tsBoundBoxd_expand(self, bb); }
	}
	
	pub fn inside_v(&self, v: &Vector3d) -> bool {
		unsafe { tsBoundBoxd_inside1(self, v) }
	}
	pub fn inside(&self, bb: &BoundBoxd) -> bool {
		unsafe { tsBoundBoxd_inside(self, bb) }
	}
	
	pub fn distance(&self, v: &Vector3d) -> f64 {
		unsafe { tsBoundBoxd_distance(self, v) }
	}
}

impl fmt::Display for BoundBoxd {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "{0} : {1}", self.min, self.max)
	}
}

/*
 */
extern "C" {
	fn tsBoundBoxf_set_bbd(ret: *mut BoundBoxf, b: *const BoundBoxd) -> *mut BoundBoxf;
	fn tsBoundBoxf_set_bs(ret: *mut BoundBoxf, s: *const BoundSpheref) -> *mut BoundBoxf;
	fn tsBoundBoxf_expand1(ret: *mut BoundBoxf, v: *const Vector3f) -> *mut BoundBoxf;
	fn tsBoundBoxf_expand(ret: *mut BoundBoxf, b: *const BoundBoxf) -> *mut BoundBoxf;
	fn tsBoundBoxf_inside1(bb: *const BoundBoxf, v: *const Vector3f) -> bool;
	fn tsBoundBoxf_inside(bb: *const BoundBoxf, b: *const BoundBoxf) -> bool;
	fn tsBoundBoxf_distance(bb: *const BoundBoxf, v: *const Vector3f) -> f32;
}

extern "C" {
	fn tsBoundBoxd_set_bbf(ret: *mut BoundBoxd, b: *const BoundBoxf) -> *mut BoundBoxd;
	fn tsBoundBoxd_set_bs(ret: *mut BoundBoxd, s: *const BoundSphered) -> *mut BoundBoxd;
	fn tsBoundBoxd_expand1(ret: *mut BoundBoxd, v: *const Vector3d) -> *mut BoundBoxd;
	fn tsBoundBoxd_expand(ret: *mut BoundBoxd, b: *const BoundBoxd) -> *mut BoundBoxd;
	fn tsBoundBoxd_inside1(bb: *const BoundBoxd, v: *const Vector3d) -> bool;
	fn tsBoundBoxd_inside(bb: *const BoundBoxd, b: *const BoundBoxd) -> bool;
	fn tsBoundBoxd_distance(bb: *const BoundBoxd, v: *const Vector3d) -> f64;
}

/*****************************************************************************\
 *
 * BoundSphere
 *
\*****************************************************************************/

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct BoundSpheref {
	pub center: Vector3f,
	pub radius: f32,
}

impl BoundSpheref {
	
	pub fn new(center: &Vector3f, radius: f32) -> BoundSpheref {
		BoundSpheref { center: *center, radius: radius }
	}
	pub fn new_bsd(bs: &BoundSphered) -> BoundSpheref {
		let mut ret = BoundSpheref::default();
		unsafe { tsBoundSpheref_set_bsd(&mut ret, bs); }
		ret
	}
	pub fn new_bb(bb: &BoundBoxf) -> BoundSpheref {
		let mut ret = BoundSpheref::default();
		unsafe { tsBoundSpheref_set_bb(&mut ret, bb); }
		ret
	}
	
	pub fn expand_v(&mut self, v: &Vector3f) {
		unsafe { tsBoundSpheref_expand1(self, v); }
	}
	pub fn expand(&mut self, bs: &BoundSpheref) {
		unsafe { tsBoundSpheref_expand(self, bs); }
	}
	
	pub fn expand_radius_v(&mut self, v: &Vector3f) {
		unsafe { tsBoundSpheref_expandRadius1(self, v); }
	}
	pub fn expand_radius(&mut self, bs: &BoundSpheref) {
		unsafe { tsBoundSpheref_expandRadius(self, bs); }
	}
	
	pub fn inside_v(&self, v: &Vector3f) -> bool {
		unsafe { tsBoundSpheref_inside1(self, v) }
	}
	pub fn inside(&self, bs: &BoundSpheref) -> bool {
		unsafe { tsBoundSpheref_inside(self, bs) }
	}
	
	pub fn distance(&self, v: &Vector3f) -> f32 {
		unsafe { tsBoundSpheref_distance(self, v) }
	}
}

impl fmt::Display for BoundSpheref {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "{0} : {1}", self.center, self.radius)
	}
}

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct BoundSphered {
	pub center: Vector3d,
	pub radius: f64,
}

impl BoundSphered {
	
	pub fn new(center: &Vector3d, radius: f64) -> BoundSphered {
		BoundSphered { center: *center, radius: radius }
	}
	pub fn new_bsf(bs: &BoundSpheref) -> BoundSphered {
		let mut ret = BoundSphered::default();
		unsafe { tsBoundSphered_set_bsf(&mut ret, bs); }
		ret
	}
	pub fn new_bb(bb: &BoundBoxd) -> BoundSphered {
		let mut ret = BoundSphered::default();
		unsafe { tsBoundSphered_set_bb(&mut ret, bb); }
		ret
	}
	
	pub fn expand_v(&mut self, v: &Vector3d) {
		unsafe { tsBoundSphered_expand1(self, v); }
	}
	pub fn expand(&mut self, bs: &BoundSphered) {
		unsafe { tsBoundSphered_expand(self, bs); }
	}
	
	pub fn expand_radius_v(&mut self, v: &Vector3d) {
		unsafe { tsBoundSphered_expandRadius1(self, v); }
	}
	pub fn expand_radius(&mut self, bs: &BoundSphered) {
		unsafe { tsBoundSphered_expandRadius(self, bs); }
	}
	
	pub fn inside_v(&self, v: &Vector3d) -> bool {
		unsafe { tsBoundSphered_inside1(self, v) }
	}
	pub fn inside(&self, bs: &BoundSphered) -> bool {
		unsafe { tsBoundSphered_inside(self, bs) }
	}
	
	pub fn distance(&self, v: &Vector3d) -> f64 {
		unsafe { tsBoundSphered_distance(self, v) }
	}
}

impl fmt::Display for BoundSphered {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "{0} : {1}", self.center, self.radius)
	}
}

/*
 */
extern "C" {
	fn tsBoundSpheref_set_bsd(ret: *mut BoundSpheref, s: *const BoundSphered) -> *mut BoundSpheref;
	fn tsBoundSpheref_set_bb(ret: *mut BoundSpheref, b: *const BoundBoxf) -> *mut BoundSpheref;
	fn tsBoundSpheref_expand1(ret: *mut BoundSpheref, v: *const Vector3f) -> *mut BoundSpheref;
	fn tsBoundSpheref_expand(ret: *mut BoundSpheref, s: *const BoundSpheref) -> *mut BoundSpheref;
	fn tsBoundSpheref_expandRadius1(ret: *mut BoundSpheref, v: *const Vector3f) -> *mut BoundSpheref;
	fn tsBoundSpheref_expandRadius(ret: *mut BoundSpheref, s: *const BoundSpheref) -> *mut BoundSpheref;
	fn tsBoundSpheref_inside1(bs: *const BoundSpheref, v: *const Vector3f) -> bool;
	fn tsBoundSpheref_inside(bs: *const BoundSpheref, s: *const BoundSpheref) -> bool;
	fn tsBoundSpheref_distance(bs: *const BoundSpheref, v: *const Vector3f) -> f32;
}

extern "C" {
	fn tsBoundSphered_set_bsf(ret: *mut BoundSphered, s: *const BoundSpheref) -> *mut BoundSphered;
	fn tsBoundSphered_set_bb(ret: *mut BoundSphered, b: *const BoundBoxd) -> *mut BoundSphered;
	fn tsBoundSphered_expand1(ret: *mut BoundSphered, v: *const Vector3d) -> *mut BoundSphered;
	fn tsBoundSphered_expand(ret: *mut BoundSphered, s: *const BoundSphered) -> *mut BoundSphered;
	fn tsBoundSphered_expandRadius1(ret: *mut BoundSphered, v: *const Vector3d) -> *mut BoundSphered;
	fn tsBoundSphered_expandRadius(ret: *mut BoundSphered, s: *const BoundSphered) -> *mut BoundSphered;
	fn tsBoundSphered_inside1(bs: *const BoundSphered, v: *const Vector3d) -> bool;
	fn tsBoundSphered_inside(bs: *const BoundSphered, s: *const BoundSphered) -> bool;
	fn tsBoundSphered_distance(bs: *const BoundSphered, v: *const Vector3d) -> f64;
}

/*****************************************************************************\
 *
 * BoundFrustum
 *
\*****************************************************************************/

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct BoundFrustumf {
	pub projection: Matrix4x4f,
	pub modelview: Matrix4x4f,
	pub camera: Vector3f,
	pub plane_l: Vector4f,
	pub plane_r: Vector4f,
	pub plane_b: Vector4f,
	pub plane_t: Vector4f,
	pub plane_n: Vector4f,
	pub plane_f: Vector4f,
	pub sign_l: u32,
	pub sign_r: u32,
	pub sign_b: u32,
	pub sign_t: u32,
	pub sign_n: u32,
	pub sign_f: u32,
}

impl BoundFrustumf {
	
	pub fn new(p: &Matrix4x4f, m: &Matrix4x4f, c: &Vector3f, l: &Vector4f, r: &Vector4f, b: &Vector4f, t: &Vector4f, n: &Vector4f, f: &Vector4f) -> BoundFrustumf {
		BoundFrustumf { projection: *p, modelview: *m, camera: *c, plane_l: *l, plane_r: *r, plane_b: *b, plane_t: *t, plane_n: *n, plane_f: *f, sign_l: 0, sign_r: 0, sign_b: 0, sign_t: 0, sign_n: 0, sign_f: 0 }
	}
	pub fn new_bfd(bf: &BoundFrustumd) -> BoundFrustumf {
		let mut ret = BoundFrustumf::default();
		unsafe { tsBoundFrustumf_set_bfd(&mut ret, bf); }
		ret
	}
	pub fn new_pm(projection: &Matrix4x4f, modelview: &Matrix4x4f) -> BoundFrustumf {
		let mut ret = BoundFrustumf::default();
		unsafe { tsBoundFrustumf_set(&mut ret, projection, modelview, 1.0); }
		ret
	}
	pub fn new_pma(projection: &Matrix4x4f, modelview: &Matrix4x4f, aspect: f32) -> BoundFrustumf {
		let mut ret = BoundFrustumf::default();
		unsafe { tsBoundFrustumf_set(&mut ret, projection, modelview, aspect); }
		ret
	}
	
	pub fn inside_bb(&self, bb: &BoundBoxf) -> bool {
		unsafe { tsBoundFrustumf_inside_bb(self, bb) }
	}
	pub fn inside_bs(&self, bs: &BoundSpheref) -> bool {
		unsafe { tsBoundFrustumf_inside_bs(self, bs) }
	}
}

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct BoundFrustumd {
	pub projection: Matrix4x4d,
	pub modelview: Matrix4x4d,
	pub camera: Vector3d,
	pub plane_l: Vector4d,
	pub plane_r: Vector4d,
	pub plane_b: Vector4d,
	pub plane_t: Vector4d,
	pub plane_n: Vector4d,
	pub plane_f: Vector4d,
	pub sign_l: u32,
	pub sign_r: u32,
	pub sign_b: u32,
	pub sign_t: u32,
	pub sign_n: u32,
	pub sign_f: u32,
}

impl BoundFrustumd {
	
	pub fn new(p: &Matrix4x4d, m: &Matrix4x4d, c: &Vector3d, l: &Vector4d, r: &Vector4d, b: &Vector4d, t: &Vector4d, n: &Vector4d, f: &Vector4d) -> BoundFrustumd {
		BoundFrustumd { projection: *p, modelview: *m, camera: *c, plane_l: *l, plane_r: *r, plane_b: *b, plane_t: *t, plane_n: *n, plane_f: *f, sign_l: 0, sign_r: 0, sign_b: 0, sign_t: 0, sign_n: 0, sign_f: 0 }
	}
	pub fn new_bff(bf: &BoundFrustumf) -> BoundFrustumd {
		let mut ret = BoundFrustumd::default();
		unsafe { tsBoundFrustumd_set_bff(&mut ret, bf); }
		ret
	}
	pub fn new_pm(projection: &Matrix4x4d, modelview: &Matrix4x4d) -> BoundFrustumd {
		let mut ret = BoundFrustumd::default();
		unsafe { tsBoundFrustumd_set(&mut ret, projection, modelview, 1.0); }
		ret
	}
	pub fn new_pma(projection: &Matrix4x4d, modelview: &Matrix4x4d, aspect: f64) -> BoundFrustumd {
		let mut ret = BoundFrustumd::default();
		unsafe { tsBoundFrustumd_set(&mut ret, projection, modelview, aspect); }
		ret
	}
	
	pub fn inside_bb(&self, bb: &BoundBoxd) -> bool {
		unsafe { tsBoundFrustumd_inside_bb(self, bb) }
	}
	pub fn inside_bs(&self, bs: &BoundSphered) -> bool {
		unsafe { tsBoundFrustumd_inside_bs(self, bs) }
	}
}

/*
 */
extern "C" {
	fn tsBoundFrustumf_set_bfd(ret: *mut BoundFrustumf, bf: *const BoundFrustumd) -> *mut BoundFrustumf;
	fn tsBoundFrustumf_set(ret: *mut BoundFrustumf, projection: *const Matrix4x4f, modelview: *const Matrix4x4f, aspect: f32) -> *mut BoundFrustumf;
	fn tsBoundFrustumf_inside_bb(bf: *const BoundFrustumf, bb: *const BoundBoxf) -> bool;
	fn tsBoundFrustumf_inside_bs(bf: *const BoundFrustumf, bs: *const BoundSpheref) -> bool;
}

extern "C" {
	fn tsBoundFrustumd_set_bff(ret: *mut BoundFrustumd, bf: *const BoundFrustumf) -> *mut BoundFrustumd;
	fn tsBoundFrustumd_set(ret: *mut BoundFrustumd, projection: *const Matrix4x4d, modelview: *const Matrix4x4d, aspect: f64) -> *mut BoundFrustumd;
	fn tsBoundFrustumd_inside_bb(bf: *const BoundFrustumd, bb: *const BoundBoxd) -> bool;
	fn tsBoundFrustumd_inside_bs(bf: *const BoundFrustumd, bs: *const BoundSphered) -> bool;
}

/*****************************************************************************\
 *
 * Platform
 *
\*****************************************************************************/

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct Origin {
	pub x: u32,
	pub y: u32,
	pub z: u32,
}

impl Origin {
	pub fn new_2(x: u32, y: u32) -> Origin {
		Origin { x: x, y: y, z: 0 }
	}
	pub fn new_3(x: u32, y: u32, z: u32) -> Origin {
		Origin { x: x, y: y, z: z }
	}
}

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct Size {
	pub width: u32,
	pub height: u32,
	pub depth: u32,
}

impl Size {
	pub fn new_2(width: u32, height: u32) -> Size {
		Size { width: width, height: height, depth: 1 }
	}
	pub fn new_3(width: u32, height: u32, depth: u32) -> Size {
		Size { width: width, height: height, depth: depth }
	}
}

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct Region {
	pub x: u32,
	pub y: u32,
	pub z: u32,
	pub width: u32,
	pub height: u32,
	pub depth: u32,
}

impl Region {
	pub fn new_2(x: u32, y: u32, width: u32, height: u32) -> Region {
		Region { x: x, y: y, z: 0, width: width, height: height, depth: 1 }
	}
	pub fn new_3(x: u32, y: u32, z: u32, width: u32, height: u32, depth: u32) -> Region {
		Region { x: x, y: y, z: z, width: width, height: height, depth: depth }
	}
}

/*
 */
#[derive(Copy, Clone)]
pub struct Face {
	pub base: u32,
	pub size: u32,
}

impl Default for Face {
	fn default() -> Face {
		Face { base: 0, size: 1 }
	}
}

impl Face {
	pub fn new(base: u32, size: u32) -> Face {
		Face { base: base, size: size }
	}
}

/*
 */
#[derive(Copy, Clone)]
pub struct Layer {
	pub base: u32,
	pub size: u32,
}

impl Default for Layer {
	fn default() -> Layer {
		Layer { base: 0, size: 1 }
	}
}

impl Layer {
	pub fn new(base: u32, size: u32) -> Layer {
		Layer { base: base, size: size }
	}
}

/*
 */
#[derive(Copy, Clone)]
pub struct Mipmap {
	pub base: u32,
	pub size: u32,
}

impl Default for Mipmap {
	fn default() -> Mipmap {
		Mipmap { base: 0, size: 1 }
	}
}

impl Mipmap {
	pub fn new(base: u32, size: u32) -> Mipmap {
		Mipmap { base: base, size: size }
	}
}

/*
 */
#[repr(C)]
#[derive(Copy, Clone)]
pub struct Slice {
	pub face: u32,
	pub faces: u32,
	pub layer: u32,
	pub layers: u32,
	pub mipmap: u32,
	pub mipmaps: u32,
}

impl Default for Slice {
	fn default() -> Slice {
		Slice { face: 0, faces: 1, layer: 0, layers: 1, mipmap: 0, mipmaps: 1 }
	}
}

impl Slice {
	pub fn new_f(f: &Face) -> Slice {
		Slice { face: f.base, faces: f.size, layer: 0, layers: 1, mipmap: 0, mipmaps: 1 }
	}
	pub fn new_l(l: &Layer) -> Slice {
		Slice { face: 0, faces: 1, layer: l.base, layers: l.size, mipmap: 0, mipmaps: 1 }
	}
	pub fn new_m(m: &Mipmap) -> Slice {
		Slice { face: 0, faces: 1, layer: 0, layers: 1, mipmap: m.base, mipmaps: m.size }
	}
	pub fn new_lf(l: &Layer, f: &Face) -> Slice {
		Slice { face: f.base, faces: f.size, layer: l.base, layers: l.size, mipmap: 0, mipmaps: 1 }
	}
	pub fn new_fm(f: &Face, m: &Mipmap) -> Slice {
		Slice { face: f.base, faces: f.size, layer: 0, layers: 1, mipmap: m.base, mipmaps: m.size }
	}
	pub fn new_lm(l: &Layer, m: &Mipmap) -> Slice {
		Slice { face: 0, faces: 1, layer: l.base, layers: l.size, mipmap: m.base, mipmaps: m.size }
	}
	pub fn new_lfm(l: &Layer, f: &Face, m: &Mipmap) -> Slice {
		Slice { face: f.base, faces: f.size, layer: l.base, layers: l.size, mipmap: m.base, mipmaps: m.size }
	}
	pub fn new(face: u32, layer: u32, mipmap: u32) -> Slice {
		Slice { face: face, faces: 1, layer: layer, layers: 1, mipmap: mipmap, mipmaps: 1 }
	}
}

/*
 */
#[repr(C)]
#[derive(Copy, Clone)]
pub struct Viewport {
	pub x: f32,
	pub y: f32,
	pub width: f32,
	pub height: f32,
	pub znear: f32,
	pub zfar: f32,
}

impl Default for Viewport {
	fn default() -> Viewport {
		Viewport { x: 0.0, y: 0.0, width: 1.0, height: 1.0, znear: 0.0, zfar: 1.0 }
	}
}

impl Viewport {
	pub fn new_wh(width: f32, height: f32) -> Viewport {
		Viewport { x: 0.0, y: 0.0, width: width, height: height, znear: 0.0, zfar: 1.0 }
	}
	pub fn new_xywh(x: f32, y: f32, width: f32, height: f32) -> Viewport {
		Viewport { x: x, y: y, width: width, height: height, znear: 0.0, zfar: 1.0 }
	}
	pub fn new(x: f32, y: f32, width: f32, height: f32, znear: f32, zfar: f32) -> Viewport {
		Viewport { x: x, y: y, width: width, height: height, znear: znear, zfar: zfar }
	}
}

/*
 */
#[repr(C)]
#[derive(Copy, Clone)]
pub struct Scissor {
	pub x: i32,
	pub y: i32,
	pub width: i32,
	pub height: i32,
}

impl Default for Scissor {
	fn default() -> Scissor {
		Scissor { x: 0, y: 0, width: MAXI16 as i32, height: MAXI16 as i32 }
	}
}

impl Scissor {
	pub fn new_wh(width: i32, height: i32) -> Scissor {
		Scissor { x: 0, y: 0, width: width, height: height }
	}
	pub fn new(x: i32, y: i32, width: i32, height: i32) -> Scissor {
		Scissor { x: x, y: y, width: width, height: height }
	}
}

/*
 */
impl Command {
	pub fn set_uniform<Type>(&mut self, index: u32, data: &Type) {
		Command::set_uniform_data(self, index, data as *const _ as *const c_void, mem::size_of::<Type>())
	}
	pub fn set_uniform_array<Type>(&mut self, index: u32, data: &[Type]) {
		Command::set_uniform_data(self, index, data.as_ptr() as *const c_void, mem::size_of::<Type>() * data.len())
	}
	pub fn set_uniform_vec<Type>(&mut self, index: u32, data: &Vec<Type>) {
		Command::set_uniform_data(self, index, data.as_ptr() as *const c_void, mem::size_of::<Type>() * data.len())
	}
	pub fn set_storage<Type>(&mut self, index: u32, data: &Type) {
		Command::set_storage_data(self, index, data as *const _ as *const c_void, mem::size_of::<Type>())
	}
	pub fn set_storage_array<Type>(&mut self, index: u32, data: &[Type]) {
		Command::set_storage_data(self, index, data.as_ptr() as *const c_void, mem::size_of::<Type>() * data.len())
	}
	pub fn set_storage_vec<Type>(&mut self, index: u32, data: &Vec<Type>) {
		Command::set_storage_data(self, index, data.as_ptr() as *const c_void, mem::size_of::<Type>() * data.len())
	}
	pub fn set_vertices<Type>(&mut self, index: u32, data: &[Type]) {
		Command::set_vertex_data(self, index, data.as_ptr() as *const c_void, mem::size_of::<Type>() * data.len())
	}
	pub fn set_indices<Type>(&mut self, data: &[Type]) {
		let format = match mem::size_of::<Type>() {
			1 => Format::Ru8,
			2 => Format::Ru16,
			4 => Format::Ru32,
			_ => Format::Unknown,
		};
		Command::set_index_data(self, format, data.as_ptr() as *const c_void, mem::size_of::<Type>() * data.len())
	}
	pub fn set_indirect<Type>(&mut self, data: &Type) {
		Command::set_indirect_data(self, data as *const _ as *const c_void, mem::size_of::<Type>())
	}
	pub fn set_indirect_array<Type>(&mut self, data: &[Type]) {
		Command::set_indirect_data(self, data.as_ptr() as *const c_void, mem::size_of::<Type>() * data.len())
	}
}

/*
 */
impl Compute {
	pub fn set_uniform<Type>(&mut self, index: u32, data: &Type) {
		Compute::set_uniform_data(self, index, data as *const _ as *const c_void, mem::size_of::<Type>())
	}
	pub fn set_uniform_array<Type>(&mut self, index: u32, data: &[Type]) {
		Compute::set_uniform_data(self, index, data.as_ptr() as *const c_void, mem::size_of::<Type>() * data.len())
	}
	pub fn set_uniform_vec<Type>(&mut self, index: u32, data: &Vec<Type>) {
		Compute::set_uniform_data(self, index, data.as_ptr() as *const c_void, mem::size_of::<Type>() * data.len())
	}
	pub fn set_storage<Type>(&mut self, index: u32, data: &Type) {
		Compute::set_storage_data(self, index, data as *const _ as *const c_void, mem::size_of::<Type>())
	}
	pub fn set_storage_array<Type>(&mut self, index: u32, data: &[Type]) {
		Compute::set_storage_data(self, index, data.as_ptr() as *const c_void, mem::size_of::<Type>() * data.len())
	}
	pub fn set_storage_vec<Type>(&mut self, index: u32, data: &Vec<Type>) {
		Compute::set_storage_data(self, index, data.as_ptr() as *const c_void, mem::size_of::<Type>() * data.len())
	}
	pub fn set_indirect<Type>(&mut self, data: &Type) {
		Compute::set_indirect_data(self, data as *const _ as *const c_void, mem::size_of::<Type>())
	}
	pub fn set_indirect_array<Type>(&mut self, data: &[Type]) {
		Compute::set_indirect_data(self, data.as_ptr() as *const c_void, mem::size_of::<Type>() * data.len())
	}
}

/*
 */
impl Device {
	pub fn create_buffer_with_flags_array<Type>(&self, flags: BufferFlags, data: &[Type]) -> Buffer {
		DeviceTrait::create_buffer_with_flags_src(self, flags, data.as_ptr() as *const c_void, mem::size_of::<Type>() * data.len())
	}
	pub fn create_buffer_with_flags_vec<Type>(&self, flags: BufferFlags, data: &Vec<Type>) -> Buffer {
		DeviceTrait::create_buffer_with_flags_src(self, flags, data.as_ptr() as *const c_void, mem::size_of::<Type>() * data.len())
	}
}

/*****************************************************************************\
 *
 * Interface
 *
\*****************************************************************************/

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct Rect {
	pub left: f32,
	pub right: f32,
	pub bottom: f32,
	pub top: f32,
}

impl Rect {
	
	pub fn new() -> Rect {
		Rect { left: MAXF32, right: -MAXF32, bottom: MAXF32, top: -MAXF32 }
	}
	pub fn new_v(value: f32) -> Rect {
		Rect { left: value, right: value, bottom: value, top: value }
	}
	pub fn new_hv(horizontal: f32, vertical: f32) -> Rect {
		Rect { left: horizontal, right: horizontal, bottom: vertical, top: vertical }
	}
	pub fn new_lrbt(left: f32, right: f32, bottom: f32, top: f32) -> Rect {
		Rect { left: left, right: right, bottom: bottom, top: top }
	}
}

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct FontStyle {
	pub size: u32,
	pub scale: u32,
	pub fixed: bool,
	pub kerning: bool,
	pub spacing: Vector2f,
	pub color: Color,
	pub offset: Vector3f,
	pub shadow: Color,
}

impl FontStyle {
	
	pub fn new() -> FontStyle {
		FontStyle { size: 16, scale: 100, fixed: false, kerning: true, spacing: Vector2f::zero(), color: Color::white(), offset: Vector3f::zero(), shadow: Color::black() }
	}
	pub fn new_with_size(size: u32) -> FontStyle {
		FontStyle { size: size, scale: 100, fixed: false, kerning: true, spacing: Vector2f::zero(), color: Color::white(), offset: Vector3f::zero(), shadow: Color::black() }
	}
	pub fn new_with_color(color: Color) -> FontStyle {
		FontStyle { size: 16, scale: 100, fixed: false, kerning: true, spacing: Vector2f::zero(), color: color, offset: Vector3f::zero(), shadow: Color::black() }
	}
	pub fn new_with_size_color(size: u32, color: Color) -> FontStyle {
		FontStyle { size: size, scale: 100, fixed: false, kerning: true, spacing: Vector2f::zero(), color: color, offset: Vector3f::zero(), shadow: Color::black() }
	}
}

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct StrokeStyle {
	pub width: f32,
	pub offset: f32,
	pub color: Color,
}

impl StrokeStyle {
	
	pub fn new_with_width(width: f32) -> StrokeStyle {
		StrokeStyle { width: width, offset: 0.0, color: Color::white() }
	}
	pub fn new_with_color(color: Color) -> StrokeStyle {
		StrokeStyle { width: 0.0, offset: 0.0, color: color }
	}
	pub fn new_with_width_offset(width: f32, offset: f32) -> StrokeStyle {
		StrokeStyle { width: width, offset: offset, color: Color::white() }
	}
	pub fn new_with_width_color(width: f32, color: Color) -> StrokeStyle {
		StrokeStyle { width: width, offset: 0.0, color: color }
	}
	pub fn new_with_width_offset_color(width: f32, offset: f32, color: Color) -> StrokeStyle {
		StrokeStyle { width: width, offset: offset, color: color }
	}
}

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct GradientStyle {
	pub radius: f32,
	pub length: f32,
	pub center: Vector2f,
	pub axis: Vector2f,
	pub color_0: Color,
	pub color_1: Color,
}

impl GradientStyle {
	
	pub fn new_with_colors(c0: Color, c1: Color) -> GradientStyle {
		GradientStyle { radius: 0.0, length: 0.0, center: Vector2f::zero(), axis: Vector2f::zero(), color_0: c0, color_1: c1 }
	}
	pub fn new_with_radius_color(radius: f32, center: Vector2f) -> GradientStyle {
		GradientStyle { radius: radius, length: 0.0, center: center, axis: Vector2f::zero(), color_0: Color::white(), color_1: Color::white() }
	}
	pub fn new_with_length_center_axis(length: f32, center: Vector2f, axis: Vector2f) -> GradientStyle {
		GradientStyle { radius: 0.0, length: length, center: center, axis: axis, color_0: Color::white(), color_1: Color::white() }
	}
	pub fn new_with_radius_center_colors(radius: f32, center: Vector2f, c0: Color, c1: Color) -> GradientStyle {
		GradientStyle { radius: radius, length: 0.0, center: center, axis: Vector2f::zero(), color_0: c0, color_1: c1 }
	}
	pub fn new_with_length_center_axis_colors(length: f32, center: Vector2f, axis: Vector2f, c0: Color, c1: Color) -> GradientStyle {
		GradientStyle { radius: 0.0, length: length, center: center, axis: axis, color_0: c0, color_1: c1 }
	}
}

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct CanvasVertex {
	pub position: Vector3f,
	pub texcoord: Vector2f,
	pub color: u32,
}

#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct CanvasShapeVertex {
	pub position: Vector4f,
	pub parameters: Vector4f,
	pub texcoord: Vector2f,
	pub padding: Vector2u,
}

#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct CanvasStripVertex {
	pub position: Vector4f,
	pub parameters: Vector4f,
	pub adjacencies: Vector4f,
}

/*****************************************************************************\
 *
 * Parallel
 *
\*****************************************************************************/

/*
 */
#[repr(C)]
#[derive(Copy, Clone)]
pub struct Tensor {
	pub buffer: *mut c_void,
	pub format: Format,
	pub offset: usize,
	pub axis: u32,
	pub kernel: u32,
	pub stride: u32,
	pub padding: u32,
	pub dilation: u32,
	pub scale: f32,
	pub bias: f32,
	pub width: u32,
	pub height: u32,
	pub depth: u32,
	pub layers: u32,
}

/*
 */
impl Tensor {
	
	pub fn new() -> Tensor {
		Tensor { buffer: ptr::null_mut(), format: Format::Unknown, offset: 0, axis: 0, kernel: 2, stride: 1, padding: 0, dilation: 1, scale: 1.0, bias: 0.0, width: 0, height: 1, depth: 1, layers: 1 }
	}
	pub fn new_with_buffer(buffer: &Buffer) -> Tensor {
		Tensor { buffer: buffer.this_ptr(), format: Format::Unknown, offset: 0, axis: 0, kernel: 2, stride: 1, padding: 0, dilation: 1, scale: 1.0, bias: 0.0, width: 0, height: 1, depth: 1, layers: 1 }
	}
	pub fn new_with_format(buffer: &Buffer, format: Format) -> Tensor {
		Tensor { buffer: buffer.this_ptr(), format: format, offset: 0, axis: 0, kernel: 2, stride: 1, padding: 0, dilation: 1, scale: 1.0, bias: 0.0, width: 0, height: 1, depth: 1, layers: 1 }
	}
	pub fn new_with_width(buffer: &Buffer, format: Format, width: u32) -> Tensor {
		Tensor { buffer: buffer.this_ptr(), format: format, offset: 0, axis: 0, kernel: 2, stride: 1, padding: 0, dilation: 1, scale: 1.0, bias: 0.0, width: width, height: 1, depth: 1, layers: 1 }
	}
	pub fn new_with_width_height(buffer: &Buffer, format: Format, width: u32, height: u32) -> Tensor {
		Tensor { buffer: buffer.this_ptr(), format: format, offset: 0, axis: 0, kernel: 2, stride: 1, padding: 0, dilation: 1, scale: 1.0, bias: 0.0, width: width, height: height, depth: 1, layers: 1 }
	}
	pub fn new_with_width_height_depth(buffer: &Buffer, format: Format, width: u32, height: u32, depth: u32) -> Tensor {
		Tensor { buffer: buffer.this_ptr(), format: format, offset: 0, axis: 0, kernel: 2, stride: 1, padding: 0, dilation: 1, scale: 1.0, bias: 0.0, width: width, height: height, depth: depth, layers: 1 }
	}
	pub fn new_with_size(buffer: &Buffer, format: Format, width: u32, height: u32, depth: u32, layers: u32) -> Tensor {
		Tensor { buffer: buffer.this_ptr(), format: format, offset: 0, axis: 0, kernel: 2, stride: 1, padding: 0, dilation: 1, scale: 1.0, bias: 0.0, width: width, height: height, depth: depth, layers: layers }
	}
	pub fn new_with_tensor_width(tensor: &Tensor, width: u32) -> Tensor {
		Tensor { buffer: tensor.buffer, format: tensor.format, offset: 0, axis: 0, kernel: 2, stride: 1, padding: 0, dilation: 1, scale: 1.0, bias: 0.0, width: width, height: 1, depth: 1, layers: 1 }
	}
	pub fn new_with_tensor_width_height(tensor: &Tensor, width: u32, height: u32) -> Tensor {
		Tensor { buffer: tensor.buffer, format: tensor.format, offset: 0, axis: 0, kernel: 2, stride: 1, padding: 0, dilation: 1, scale: 1.0, bias: 0.0, width: width, height: height, depth: 1, layers: 1 }
	}
	pub fn new_with_tensor_width_height_depth(tensor: &Tensor, width: u32, height: u32, depth: u32) -> Tensor {
		Tensor { buffer: tensor.buffer, format: tensor.format, offset: 0, axis: 0, kernel: 2, stride: 1, padding: 0, dilation: 1, scale: 1.0, bias: 0.0, width: width, height: height, depth: depth, layers: 1 }
	}
	pub fn new_with_tensor_size(tensor: &Tensor, width: u32, height: u32, depth: u32, layers: u32) -> Tensor {
		Tensor { buffer: tensor.buffer, format: tensor.format, offset: tensor.offset, axis: 0, kernel: 2, stride: 1, padding: 0, dilation: 1, scale: 1.0, bias: 0.0, width: width, height: height, depth: depth, layers: layers }
	}
	
	pub fn size(&self) -> u32 {
		self.width * self.height * self.depth * self.layers
	}
	pub fn bytes(&self) -> usize {
		(self.size() as usize) * (format_pixel_size(self.format) as usize)
	}
	
	pub fn set_axis(&self, axis: u32) -> Tensor {
		let mut ret = self.clone();
		ret.axis = axis;
		ret
	}
	pub fn set_kernel(&self, kernel: u32) -> Tensor {
		let mut ret = self.clone();
		ret.kernel = kernel;
		ret
	}
	pub fn set_stride(&self, stride: u32) -> Tensor {
		let mut ret = self.clone();
		ret.stride = stride;
		ret
	}
	pub fn set_padding(&self, padding: u32) -> Tensor {
		let mut ret = self.clone();
		ret.padding = padding;
		ret
	}
	pub fn set_dilation(&self, dilation: u32) -> Tensor {
		let mut ret = self.clone();
		ret.dilation = dilation;
		ret
	}
	
	pub fn set_scale_bias(&self, scale: f32, bias: f32) -> Tensor {
		let mut ret = self.clone();
		ret.scale = scale;
		ret.bias = bias;
		ret
	}
	pub fn set_scale(&self, scale: f32) -> Tensor {
		let mut ret = self.clone();
		ret.scale = scale;
		ret
	}
	pub fn set_bias(&self, bias: f32) -> Tensor {
		let mut ret = self.clone();
		ret.bias = bias;
		ret
	}
}

/*
 */
impl fmt::Display for Tensor {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "[{0}x{1}x{2}x{3}]", self.width, self.height, self.depth, self.layers)
	}
}

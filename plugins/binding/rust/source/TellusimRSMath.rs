// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

use std::fmt;
use std::ops;

pub use crate::base::*;

/*****************************************************************************\
 *
 * Scalars
 *
\*****************************************************************************/

/* 32-bit signed integer numbers
 */
pub fn min3i32(v0: i32, v1: i32, v2: i32) -> i32 { if v0 < v1 { i32::min(v0, v2) } else { i32::min(v1, v2) } }
pub fn max3i32(v0: i32, v1: i32, v2: i32) -> i32 { if v0 < v1 { i32::max(v1, v2) } else { i32::max(v0, v2) } }
pub fn min4i32(v0: i32, v1: i32, v2: i32, v3: i32) -> i32 { if v0 < v1 { min3i32(v0, v2, v3) } else { min3i32(v1, v2, v3) } }
pub fn max4i32(v0: i32, v1: i32, v2: i32, v3: i32) -> i32 { if v0 < v1 { max3i32(v1, v2, v3) } else { max3i32(v0, v2, v3) } }
pub fn midi32(v0: i32, v1: i32, v2: i32) -> i32 { if v0 < v1 { if v1 < v2 { v1 } else { i32::max(v0, v2) } } else { if v0 < v2 { v0 } else { i32::max(v1, v2) } } }
pub fn clampi32(v: i32, v0: i32, v1: i32) -> i32 { i32::min(i32::max(v, v0), v1) }

/* 64-bit signed integer numbers
 */
pub fn min3i64(v0: i64, v1: i64, v2: i64) -> i64 { if v0 < v1 { i64::min(v0, v2) } else { i64::min(v1, v2) } }
pub fn max3i64(v0: i64, v1: i64, v2: i64) -> i64 { if v0 < v1 { i64::max(v1, v2) } else { i64::max(v0, v2) } }
pub fn min4i64(v0: i64, v1: i64, v2: i64, v3: i64) -> i64 { if v0 < v1 { min3i64(v0, v2, v3) } else { min3i64(v1, v2, v3) } }
pub fn max4i64(v0: i64, v1: i64, v2: i64, v3: i64) -> i64 { if v0 < v1 { max3i64(v1, v2, v3) } else { max3i64(v0, v2, v3) } }
pub fn midi64(v0: i64, v1: i64, v2: i64) -> i64 { if v0 < v1 { if v1 < v2 { v1 } else { i64::max(v0, v2) } } else { if v0 < v2 { v0 } else { i64::max(v1, v2) } } }
pub fn clampi64(v: i64, v0: i64, v1: i64) -> i64 { i64::min(i64::max(v, v0), v1) }

/* 32-bit unsigned integer numbers
 */
pub fn ispotu32(x: u32) -> bool { (x & (x - 1)) == 0 }
pub fn isalignedu32(a: u32, b: u32) -> bool { if ispotu32(b) { (a & (b - 1)) == 0 } else { (a / b) * b == a } }
pub fn npotu32(x: u32) -> u32 { let mut ret: u32 = 1; while ret < x { ret += ret } ret }
pub fn alignu32(a: u32, b: u32) -> u32 { if ispotu32(b) { (a + b - 1) & !(b - 1) } else { ((a + b - 1) / b) * b } }
pub fn udivu32(a: u32, b: u32) -> u32 { (a + b - 1) / b }

pub fn min3u32(v0: u32, v1: u32, v2: u32) -> u32 { if v0 < v1 { u32::min(v0, v2) } else { u32::min(v1, v2) } }
pub fn max3u32(v0: u32, v1: u32, v2: u32) -> u32 { if v0 < v1 { u32::max(v1, v2) } else { u32::max(v0, v2) } }
pub fn min4u32(v0: u32, v1: u32, v2: u32, v3: u32) -> u32 { if v0 < v1 { min3u32(v0, v2, v3) } else { min3u32(v1, v2, v3) } }
pub fn max4u32(v0: u32, v1: u32, v2: u32, v3: u32) -> u32 { if v0 < v1 { max3u32(v1, v2, v3) } else { max3u32(v0, v2, v3) } }
pub fn midu32(v0: u32, v1: u32, v2: u32) -> u32 { if v0 < v1 { if v1 < v2 { v1 } else { u32::max(v0, v2) } } else { if v0 < v2 { v0 } else { u32::max(v1, v2) } } }
pub fn clampu32(v: u32, v0: u32, v1: u32) -> u32 { u32::min(u32::max(v, v0), v1) }

/* 64-bit unsigned integer numbers
 */
pub fn ispotu64(x: u64) -> bool { (x & (x - 1)) == 0 }
pub fn isalignedu64(a: u64, b: u64) -> bool { if ispotu64(b) { (a & (b - 1)) == 0 } else { (a / b) * b == a } }
pub fn npotu64(x: u64) -> u64 { let mut ret: u64 = 1; while ret < x { ret += ret } ret }
pub fn alignu64(a: u64, b: u64) -> u64 { if ispotu64(b) { (a + b - 1) & !(b - 1) } else { ((a + b - 1) / b) * b } }
pub fn udivu64(a: u64, b: u64) -> u64 { (a + b - 1) / b }

pub fn min3u64(v0: u64, v1: u64, v2: u64) -> u64 { if v0 < v1 { u64::min(v0, v2) } else { u64::min(v1, v2) } }
pub fn max3u64(v0: u64, v1: u64, v2: u64) -> u64 { if v0 < v1 { u64::max(v1, v2) } else { u64::max(v0, v2) } }
pub fn min4u64(v0: u64, v1: u64, v2: u64, v3: u64) -> u64 { if v0 < v1 { min3u64(v0, v2, v3) } else { min3u64(v1, v2, v3) } }
pub fn max4u64(v0: u64, v1: u64, v2: u64, v3: u64) -> u64 { if v0 < v1 { max3u64(v1, v2, v3) } else { max3u64(v0, v2, v3) } }
pub fn midu64(v0: u64, v1: u64, v2: u64) -> u64 { if v0 < v1 { if v1 < v2 { v1 } else { u64::max(v0, v2) } } else { if v0 < v2 { v0 } else { u64::max(v1, v2) } } }
pub fn clampu64(v: u64, v0: u64, v1: u64) -> u64 { u64::min(u64::max(v, v0), v1) }

/* 32-bit floating point numbers
 */
pub fn min3f32(v0: f32, v1: f32, v2: f32) -> f32 { if v0 < v1 { f32::min(v0, v2) } else { f32::min(v1, v2) } }
pub fn max3f32(v0: f32, v1: f32, v2: f32) -> f32 { if v0 < v1 { f32::max(v1, v2) } else { f32::max(v0, v2) } }
pub fn min4f32(v0: f32, v1: f32, v2: f32, v3: f32) -> f32 { if v0 < v1 { min3f32(v0, v2, v3) } else { min3f32(v1, v2, v3) } }
pub fn max4f32(v0: f32, v1: f32, v2: f32, v3: f32) -> f32 { if v0 < v1 { max3f32(v1, v2, v3) } else { max3f32(v0, v2, v3) } }
pub fn midf32(v0: f32, v1: f32, v2: f32) -> f32 { if v0 < v1 { if v1 < v2 { v1 } else { f32::max(v0, v2) } } else { if v0 < v2 { v0 } else { f32::max(v1, v2) } } }
pub fn clampf32(v: f32, v0: f32, v1: f32) -> f32 { f32::min(f32::max(v, v0), v1) }
pub fn saturatef32(v: f32) -> f32 { f32::min(f32::max(v, 0.0), 1.0) }

pub fn lerpf32(v0: f32, v1: f32, k: f32) -> f32 { v0 + (v1 - v0) * k }

/* 64-bit floating point numbers
 */
pub fn min3f64(v0: f64, v1: f64, v2: f64) -> f64 { if v0 < v1 { f64::min(v0, v2) } else { f64::min(v1, v2) } }
pub fn max3f64(v0: f64, v1: f64, v2: f64) -> f64 { if v0 < v1 { f64::max(v1, v2) } else { f64::max(v0, v2) } }
pub fn min4f64(v0: f64, v1: f64, v2: f64, v3: f64) -> f64 { if v0 < v1 { min3f64(v0, v2, v3) } else { min3f64(v1, v2, v3) } }
pub fn max4f64(v0: f64, v1: f64, v2: f64, v3: f64) -> f64 { if v0 < v1 { max3f64(v1, v2, v3) } else { max3f64(v0, v2, v3) } }
pub fn midf64(v0: f64, v1: f64, v2: f64) -> f64 { if v0 < v1 { if v1 < v2 { v1 } else { f64::max(v0, v2) } } else { if v0 < v2 { v0 } else { f64::max(v1, v2) } } }
pub fn clampf64(v: f64, v0: f64, v1: f64) -> f64 { f64::min(f64::max(v, v0), v1) }
pub fn saturatef64(v: f64) -> f64 { f64::min(f64::max(v, 0.0), 1.0) }

pub fn lerpf64(v0: f64, v1: f64, k: f64) -> f64 { v0 + (v1 - v0) * k }

/* packed floating point numbers
 */
pub fn f32tof16(f: f32) -> u16 { unsafe { ts_f32tof16(f) } }
pub fn f16tof32(h: u16) -> f32 { unsafe { ts_f16tof32(h) } }
pub fn f32tof21(f: f32) -> u32 { unsafe { ts_f32tof21(f) } }
pub fn f21tof32(h: u32) -> f32 { unsafe { ts_f21tof32(h) } }
pub fn f32tof24(f: f32) -> u32 { unsafe { ts_f32tof24(f) } }
pub fn f24tof32(h: u32) -> f32 { unsafe { ts_f24tof32(h) } }

/*
 */
extern "C" {
	fn ts_f32tof16(f: f32) -> u16;
	fn ts_f16tof32(h: u16) -> f32;
	fn ts_f32tof21(f: f32) -> u32;
	fn ts_f21tof32(h: u32) -> f32;
	fn ts_f32tof24(f: f32) -> u32;
	fn ts_f24tof32(h: u32) -> f32;
}

/*****************************************************************************\
 *
 * Operators
 *
\*****************************************************************************/

/*
 */
#[macro_export]
macro_rules! declare_op {
	($type:ty, $arg:ty, $ret:ty, $trait:ident, $name:ident, $func:ident) => {
		impl ops::$trait<$arg> for $type {
			type Output = $ret;
			fn $name(self, arg: $arg) -> $ret {
				let mut ret = <$ret>::default();
				unsafe { $func(&mut ret, &self, &arg); }
				ret
			}
		}
		impl ops::$trait<&$arg> for $type {
			type Output = $ret;
			fn $name(self, arg: &$arg) -> $ret {
				let mut ret = <$ret>::default();
				unsafe { $func(&mut ret, &self, arg); }
				ret
			}
		}
		impl ops::$trait<$arg> for &$type {
			type Output = $ret;
			fn $name(self, arg: $arg) -> $ret {
				let mut ret = <$ret>::default();
				unsafe { $func(&mut ret, self, &arg); }
				ret
			}
		}
		impl ops::$trait<&$arg> for &$type {
			type Output = $ret;
			fn $name(self, arg: &$arg) -> $ret {
				let mut ret = <$ret>::default();
				unsafe { $func(&mut ret, self, arg); }
				ret
			}
		}
	}
}

/*
 */
#[macro_export]
macro_rules! declare_neg_op {
	($type:ty, $func:ident) => {
		impl ops::Neg for $type {
			type Output = $type;
			fn neg(self) -> $type {
				let mut ret = <$type>::default();
				unsafe { $func(&mut ret, &self); }
				ret
			}
		}
		impl ops::Neg for &$type {
			type Output = $type;
			fn neg(self) -> $type {
				let mut ret = <$type>::default();
				unsafe { $func(&mut ret, self); }
				ret
			}
		}
	}
}

/*
 */
#[macro_export]
macro_rules! declare_scalar_op {
	($type:ty, $arg:ty, $trait:ident, $name:ident, $func:ident) => {
		impl ops::$trait<$arg> for $type {
			type Output = $type;
			fn $name(self, v1: $arg) -> $type {
				let mut ret = <$type>::default();
				unsafe { $func(&mut ret, &self, v1); }
				ret
			}
		}
		impl ops::$trait<$arg> for &$type {
			type Output = $type;
			fn $name(self, v1: $arg) -> $type {
				let mut ret = <$type>::default();
				unsafe { $func(&mut ret, self, v1); }
				ret
			}
		}
	}
}

/*
 */
#[macro_export]
macro_rules! declare_vector_op {
	($type:ty, $trait:ident, $name:ident, $func:ident) => {
		super::declare_op!($type, $type, $type, $trait, $name, $func);
	}
}

/*****************************************************************************\
 *
 * Vector2i
 *
\*****************************************************************************/

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct Vector2i {
	pub x: i32,
	pub y: i32,
}

/*
 */
impl Vector2i {
	
	pub fn new_s(v: i32) -> Vector2i {
		Vector2i { x: v, y: v }
	}
	pub fn new_v2u(v: &Vector2u) -> Vector2i {
		Vector2i { x: v.x as i32, y: v.y as i32 }
	}
	pub fn new_v2f(v: &Vector2f) -> Vector2i {
		Vector2i { x: v.x as i32, y: v.y as i32 }
	}
	pub fn new_v2d(v: &Vector2d) -> Vector2i {
		Vector2i { x: v.x as i32, y: v.y as i32 }
	}
	pub fn new_v3(v: &Vector3i) -> Vector2i {
		Vector2i { x: v.x, y: v.y }
	}
	pub fn new_v4(v: &Vector4i) -> Vector2i {
		Vector2i { x: v.x, y: v.y }
	}
	pub fn new(x: i32, y: i32) -> Vector2i {
		Vector2i { x: x, y: y }
	}
	pub fn new_a(v: &[i32]) -> Vector2i {
		Vector2i { x: v[0], y: v[1] }
	}
	
	pub fn abs(&self) -> Vector2i {
		let mut ret = Vector2i::default();
		unsafe { tsVector2i_abs(&mut ret, self); }
		ret
	}
	
	pub fn min(v0: &Vector2i, v1: &Vector2i) -> Vector2i {
		let mut ret = Vector2i::default();
		unsafe { tsVector2i_min(&mut ret, v0, v1); }
		ret
	}
	pub fn max(v0: &Vector2i, v1: &Vector2i) -> Vector2i {
		let mut ret = Vector2i::default();
		unsafe { tsVector2i_max(&mut ret, v0, v1); }
		ret
	}
	pub fn clamp(&self, v0: &Vector2i, v1: &Vector2i) -> Vector2i {
		let mut ret = Vector2i::default();
		unsafe { tsVector2i_clamp(&mut ret, self, v0, v1); }
		ret
	}
	
	pub fn zero() -> Vector2i {
		Vector2i { x: 0, y: 0 }
	}
	pub fn one() -> Vector2i {
		Vector2i { x: 1, y: 1 }
	}
}

/*
 */
impl fmt::Display for Vector2i {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "({0} {1})", self.x, self.y)
	}
}

/*
 */
declare_neg_op!(Vector2i, tsVector2i_neg);

/*
 */
declare_scalar_op!(Vector2i, i32, Mul, mul, tsVector2i_mul1);
declare_scalar_op!(Vector2i, i32, Div, div, tsVector2i_div1);
declare_scalar_op!(Vector2i, i32, Add, add, tsVector2i_add1);
declare_scalar_op!(Vector2i, i32, Sub, sub, tsVector2i_sub1);
declare_scalar_op!(Vector2i, i32, BitAnd, bitand, tsVector2i_and1);
declare_scalar_op!(Vector2i, i32, BitOr,  bitor,  tsVector2i_or1);
declare_scalar_op!(Vector2i, i32, BitXor, bitxor, tsVector2i_xor1);
declare_scalar_op!(Vector2i, i32, Shl, shl, tsVector2i_shl1);
declare_scalar_op!(Vector2i, i32, Shr, shr, tsVector2i_shr1);

/*
 */
declare_vector_op!(Vector2i, Mul, mul, tsVector2i_mul);
declare_vector_op!(Vector2i, Div, div, tsVector2i_div);
declare_vector_op!(Vector2i, Add, add, tsVector2i_add);
declare_vector_op!(Vector2i, Sub, sub, tsVector2i_sub);
declare_vector_op!(Vector2i, BitAnd, bitand, tsVector2i_and);
declare_vector_op!(Vector2i, BitOr,  bitor,  tsVector2i_or);
declare_vector_op!(Vector2i, BitXor, bitxor, tsVector2i_xor);

/*
 */
extern "C" {
	fn tsVector2i_abs(ret: *mut Vector2i, v: *const Vector2i) -> *mut Vector2i;
	fn tsVector2i_neg(ret: *mut Vector2i, v: *const Vector2i) -> *mut Vector2i;
	fn tsVector2i_mul1(ret: *mut Vector2i, v0: *const Vector2i, v1: i32) -> *mut Vector2i;
	fn tsVector2i_div1(ret: *mut Vector2i, v0: *const Vector2i, v1: i32) -> *mut Vector2i;
	fn tsVector2i_add1(ret: *mut Vector2i, v0: *const Vector2i, v1: i32) -> *mut Vector2i;
	fn tsVector2i_sub1(ret: *mut Vector2i, v0: *const Vector2i, v1: i32) -> *mut Vector2i;
	fn tsVector2i_and1(ret: *mut Vector2i, v0: *const Vector2i, v1: i32) -> *mut Vector2i;
	fn tsVector2i_or1(ret: *mut Vector2i, v0: *const Vector2i, v1: i32) -> *mut Vector2i;
	fn tsVector2i_xor1(ret: *mut Vector2i, v0: *const Vector2i, v1: i32) -> *mut Vector2i;
	fn tsVector2i_shl1(ret: *mut Vector2i, v0: *const Vector2i, v1: i32) -> *mut Vector2i;
	fn tsVector2i_shr1(ret: *mut Vector2i, v0: *const Vector2i, v1: i32) -> *mut Vector2i;
	fn tsVector2i_mul(ret: *mut Vector2i, v0: *const Vector2i, v1: *const Vector2i) -> *mut Vector2i;
	fn tsVector2i_div(ret: *mut Vector2i, v0: *const Vector2i, v1: *const Vector2i) -> *mut Vector2i;
	fn tsVector2i_add(ret: *mut Vector2i, v0: *const Vector2i, v1: *const Vector2i) -> *mut Vector2i;
	fn tsVector2i_sub(ret: *mut Vector2i, v0: *const Vector2i, v1: *const Vector2i) -> *mut Vector2i;
	fn tsVector2i_and(ret: *mut Vector2i, v0: *const Vector2i, v1: *const Vector2i) -> *mut Vector2i;
	fn tsVector2i_or(ret: *mut Vector2i, v0: *const Vector2i, v1: *const Vector2i) -> *mut Vector2i;
	fn tsVector2i_xor(ret: *mut Vector2i, v0: *const Vector2i, v1: *const Vector2i) -> *mut Vector2i;
	fn tsVector2i_min(ret: *mut Vector2i, v0: *const Vector2i, v1: *const Vector2i) -> *mut Vector2i;
	fn tsVector2i_max(ret: *mut Vector2i, v0: *const Vector2i, v1: *const Vector2i) -> *mut Vector2i;
	fn tsVector2i_clamp(ret: *mut Vector2i, v: *const Vector2i, v0: *const Vector2i, v1: *const Vector2i) -> *mut Vector2i;
}

/*****************************************************************************\
 *
 * Vector2u
 *
\*****************************************************************************/

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct Vector2u {
	pub x: u32,
	pub y: u32,
}

/*
 */
impl Vector2u {
	
	pub fn new_s(v: u32) -> Vector2u {
		Vector2u { x: v, y: v }
	}
	pub fn new_v2u(v: &Vector2i) -> Vector2u {
		Vector2u { x: v.x as u32, y: v.y as u32 }
	}
	pub fn new_v2f(v: &Vector2f) -> Vector2u {
		Vector2u { x: v.x as u32, y: v.y as u32 }
	}
	pub fn new_v2d(v: &Vector2d) -> Vector2u {
		Vector2u { x: v.x as u32, y: v.y as u32 }
	}
	pub fn new_v3(v: &Vector3u) -> Vector2u {
		Vector2u { x: v.x, y: v.y }
	}
	pub fn new_v4(v: &Vector4u) -> Vector2u {
		Vector2u { x: v.x, y: v.y }
	}
	pub fn new(x: u32, y: u32) -> Vector2u {
		Vector2u { x: x, y: y }
	}
	pub fn new_a(v: &[u32]) -> Vector2u {
		Vector2u { x: v[0], y: v[1] }
	}
	
	pub fn min(v0: &Vector2u, v1: &Vector2u) -> Vector2u {
		let mut ret = Vector2u::default();
		unsafe { tsVector2u_min(&mut ret, v0, v1); }
		ret
	}
	pub fn max(v0: &Vector2u, v1: &Vector2u) -> Vector2u {
		let mut ret = Vector2u::default();
		unsafe { tsVector2u_max(&mut ret, v0, v1); }
		ret
	}
	pub fn clamp(&self, v0: &Vector2u, v1: &Vector2u) -> Vector2u {
		let mut ret = Vector2u::default();
		unsafe { tsVector2u_clamp(&mut ret, self, v0, v1); }
		ret
	}
	
	pub fn zero() -> Vector2u {
		Vector2u { x: 0, y: 0 }
	}
	pub fn one() -> Vector2u {
		Vector2u { x: 1, y: 1 }
	}
}

/*
 */
impl fmt::Display for Vector2u {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "({0} {1})", self.x, self.y)
	}
}

/*
 */
declare_scalar_op!(Vector2u, u32, Mul, mul, tsVector2u_mul1);
declare_scalar_op!(Vector2u, u32, Div, div, tsVector2u_div1);
declare_scalar_op!(Vector2u, u32, Add, add, tsVector2u_add1);
declare_scalar_op!(Vector2u, u32, Sub, sub, tsVector2u_sub1);
declare_scalar_op!(Vector2u, u32, BitAnd, bitand, tsVector2u_and1);
declare_scalar_op!(Vector2u, u32, BitOr,  bitor,  tsVector2u_or1);
declare_scalar_op!(Vector2u, u32, BitXor, bitxor, tsVector2u_xor1);
declare_scalar_op!(Vector2u, u32, Shl, shl, tsVector2u_shl1);
declare_scalar_op!(Vector2u, u32, Shr, shr, tsVector2u_shr1);

/*
 */
declare_vector_op!(Vector2u, Mul, mul, tsVector2u_mul);
declare_vector_op!(Vector2u, Div, div, tsVector2u_div);
declare_vector_op!(Vector2u, Add, add, tsVector2u_add);
declare_vector_op!(Vector2u, Sub, sub, tsVector2u_sub);
declare_vector_op!(Vector2u, BitAnd, bitand, tsVector2u_and);
declare_vector_op!(Vector2u, BitOr,  bitor,  tsVector2u_or);
declare_vector_op!(Vector2u, BitXor, bitxor, tsVector2u_xor);

/*
 */
extern "C" {
	fn tsVector2u_mul1(ret: *mut Vector2u, v0: *const Vector2u, v1: u32) -> *mut Vector2u;
	fn tsVector2u_div1(ret: *mut Vector2u, v0: *const Vector2u, v1: u32) -> *mut Vector2u;
	fn tsVector2u_add1(ret: *mut Vector2u, v0: *const Vector2u, v1: u32) -> *mut Vector2u;
	fn tsVector2u_sub1(ret: *mut Vector2u, v0: *const Vector2u, v1: u32) -> *mut Vector2u;
	fn tsVector2u_and1(ret: *mut Vector2u, v0: *const Vector2u, v1: u32) -> *mut Vector2u;
	fn tsVector2u_or1(ret: *mut Vector2u, v0: *const Vector2u, v1: u32) -> *mut Vector2u;
	fn tsVector2u_xor1(ret: *mut Vector2u, v0: *const Vector2u, v1: u32) -> *mut Vector2u;
	fn tsVector2u_shl1(ret: *mut Vector2u, v0: *const Vector2u, v1: u32) -> *mut Vector2u;
	fn tsVector2u_shr1(ret: *mut Vector2u, v0: *const Vector2u, v1: u32) -> *mut Vector2u;
	fn tsVector2u_mul(ret: *mut Vector2u, v0: *const Vector2u, v1: *const Vector2u) -> *mut Vector2u;
	fn tsVector2u_div(ret: *mut Vector2u, v0: *const Vector2u, v1: *const Vector2u) -> *mut Vector2u;
	fn tsVector2u_add(ret: *mut Vector2u, v0: *const Vector2u, v1: *const Vector2u) -> *mut Vector2u;
	fn tsVector2u_sub(ret: *mut Vector2u, v0: *const Vector2u, v1: *const Vector2u) -> *mut Vector2u;
	fn tsVector2u_and(ret: *mut Vector2u, v0: *const Vector2u, v1: *const Vector2u) -> *mut Vector2u;
	fn tsVector2u_or(ret: *mut Vector2u, v0: *const Vector2u, v1: *const Vector2u) -> *mut Vector2u;
	fn tsVector2u_xor(ret: *mut Vector2u, v0: *const Vector2u, v1: *const Vector2u) -> *mut Vector2u;
	fn tsVector2u_min(ret: *mut Vector2u, v0: *const Vector2u, v1: *const Vector2u) -> *mut Vector2u;
	fn tsVector2u_max(ret: *mut Vector2u, v0: *const Vector2u, v1: *const Vector2u) -> *mut Vector2u;
	fn tsVector2u_clamp(ret: *mut Vector2u, v: *const Vector2u, v0: *const Vector2u, v1: *const Vector2u) -> *mut Vector2u;
}

/*****************************************************************************\
 *
 * Vector2f
 *
\*****************************************************************************/

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct Vector2f {
	pub x: f32,
	pub y: f32,
}

/*
 */
impl Vector2f {
	
	pub fn new_s(v: f32) -> Vector2f {
		Vector2f { x: v, y: v }
	}
	pub fn new_v2i(v: &Vector2i) -> Vector2f {
		Vector2f { x: v.x as f32, y: v.y as f32 }
	}
	pub fn new_v2u(v: &Vector2u) -> Vector2f {
		Vector2f { x: v.x as f32, y: v.y as f32 }
	}
	pub fn new_v2d(v: &Vector2d) -> Vector2f {
		Vector2f { x: v.x as f32, y: v.y as f32 }
	}
	pub fn new_v3(v: &Vector3f) -> Vector2f {
		Vector2f { x: v.x, y: v.y }
	}
	pub fn new_v4(v: &Vector4f) -> Vector2f {
		Vector2f { x: v.x, y: v.y }
	}
	pub fn new(x: f32, y: f32) -> Vector2f {
		Vector2f { x: x, y: y }
	}
	pub fn new_a(v: &[f32]) -> Vector2f {
		Vector2f { x: v[0], y: v[1] }
	}
	
	pub fn abs(&self) -> Vector2f {
		let mut ret = Vector2f::default();
		unsafe { tsVector2f_abs(&mut ret, self); }
		ret
	}
	
	pub fn min(v0: &Vector2f, v1: &Vector2f) -> Vector2f {
		let mut ret = Vector2f::default();
		unsafe { tsVector2f_min(&mut ret, v0, v1); }
		ret
	}
	pub fn max(v0: &Vector2f, v1: &Vector2f) -> Vector2f {
		let mut ret = Vector2f::default();
		unsafe { tsVector2f_max(&mut ret, v0, v1); }
		ret
	}
	pub fn clamp(&self, v0: &Vector2f, v1: &Vector2f) -> Vector2f {
		let mut ret = Vector2f::default();
		unsafe { tsVector2f_clamp(&mut ret, self, v0, v1); }
		ret
	}
	pub fn saturate(&self) -> Vector2f {
		let mut ret = Vector2f::default();
		unsafe { tsVector2f_saturate(&mut ret, self); }
		ret
	}
	
	pub fn dot(v0: &Vector2f, v1: &Vector2f) -> f32 {
		unsafe { tsVector2f_dot(v0, v1) }
	}
	pub fn cross(v0: &Vector2f, v1: &Vector2f) -> f32 {
		unsafe { tsVector2f_cross(v0, v1) }
	}
	
	pub fn length(&self) -> f32 {
		unsafe { tsVector2f_length(self) }
	}
	pub fn normalize(&self) -> Vector2f {
		let mut ret = Vector2f::default();
		unsafe { tsVector2f_normalize(&mut ret, self); }
		ret
	}
	
	pub fn lerp(v0: &Vector2f, v1: &Vector2f, k: f32) -> Vector2f {
		let mut ret = Vector2f::default();
		unsafe { tsVector2f_lerp(&mut ret, v0, v1, k); }
		ret
	}
	
	pub fn zero() -> Vector2f {
		Vector2f { x: 0.0, y: 0.0 }
	}
	pub fn one() -> Vector2f {
		Vector2f { x: 1.0, y: 1.0 }
	}
}

/*
 */
impl fmt::Display for Vector2f {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "({0} {1})", self.x, self.y)
	}
}

/*
 */
declare_neg_op!(Vector2f, tsVector2f_neg);

/*
 */
declare_scalar_op!(Vector2f, f32, Mul, mul, tsVector2f_mul1);
declare_scalar_op!(Vector2f, f32, Div, div, tsVector2f_div1);
declare_scalar_op!(Vector2f, f32, Add, add, tsVector2f_add1);
declare_scalar_op!(Vector2f, f32, Sub, sub, tsVector2f_sub1);

/*
 */
declare_vector_op!(Vector2f, Mul, mul, tsVector2f_mul);
declare_vector_op!(Vector2f, Div, div, tsVector2f_div);
declare_vector_op!(Vector2f, Add, add, tsVector2f_add);
declare_vector_op!(Vector2f, Sub, sub, tsVector2f_sub);

/*
 */
extern "C" {
	fn tsVector2f_abs(ret: *mut Vector2f, v: *const Vector2f) -> *mut Vector2f;
	fn tsVector2f_neg(ret: *mut Vector2f, v: *const Vector2f) -> *mut Vector2f;
	fn tsVector2f_mul1(ret: *mut Vector2f, v0: *const Vector2f, v1: f32) -> *mut Vector2f;
	fn tsVector2f_div1(ret: *mut Vector2f, v0: *const Vector2f, v1: f32) -> *mut Vector2f;
	fn tsVector2f_add1(ret: *mut Vector2f, v0: *const Vector2f, v1: f32) -> *mut Vector2f;
	fn tsVector2f_sub1(ret: *mut Vector2f, v0: *const Vector2f, v1: f32) -> *mut Vector2f;
	fn tsVector2f_mul(ret: *mut Vector2f, v0: *const Vector2f, v1: *const Vector2f) -> *mut Vector2f;
	fn tsVector2f_div(ret: *mut Vector2f, v0: *const Vector2f, v1: *const Vector2f) -> *mut Vector2f;
	fn tsVector2f_add(ret: *mut Vector2f, v0: *const Vector2f, v1: *const Vector2f) -> *mut Vector2f;
	fn tsVector2f_sub(ret: *mut Vector2f, v0: *const Vector2f, v1: *const Vector2f) -> *mut Vector2f;
	fn tsVector2f_min(ret: *mut Vector2f, v0: *const Vector2f, v1: *const Vector2f) -> *mut Vector2f;
	fn tsVector2f_max(ret: *mut Vector2f, v0: *const Vector2f, v1: *const Vector2f) -> *mut Vector2f;
	fn tsVector2f_clamp(ret: *mut Vector2f, v: *const Vector2f, v0: *const Vector2f, v1: *const Vector2f) -> *mut Vector2f;
	fn tsVector2f_saturate(ret: *mut Vector2f, v: *const Vector2f) -> *mut Vector2f;
	fn tsVector2f_dot(v0: *const Vector2f, v1: *const Vector2f) -> f32;
	fn tsVector2f_cross(v0: *const Vector2f, v1: *const Vector2f) -> f32;
	fn tsVector2f_length(v: *const Vector2f) -> f32;
	fn tsVector2f_normalize(ret: *mut Vector2f, v: *const Vector2f) -> *mut Vector2f;
	fn tsVector2f_lerp(ret: *mut Vector2f, v0: *const Vector2f, v1: *const Vector2f, k: f32) -> *mut Vector2f;
}

/*****************************************************************************\
 *
 * Vector2d
 *
\*****************************************************************************/

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct Vector2d {
	pub x: f64,
	pub y: f64,
}

/*
 */
impl Vector2d {
	
	pub fn new_s(v: f64) -> Vector2d {
		Vector2d { x: v, y: v }
	}
	pub fn new_v2i(v: &Vector2i) -> Vector2d {
		Vector2d { x: v.x as f64, y: v.y as f64 }
	}
	pub fn new_v2u(v: &Vector2u) -> Vector2d {
		Vector2d { x: v.x as f64, y: v.y as f64 }
	}
	pub fn new_v2f(v: &Vector2d) -> Vector2d {
		Vector2d { x: v.x as f64, y: v.y as f64 }
	}
	pub fn new_v3(v: &Vector3d) -> Vector2d {
		Vector2d { x: v.x, y: v.y }
	}
	pub fn new_v4(v: &Vector4d) -> Vector2d {
		Vector2d { x: v.x, y: v.y }
	}
	pub fn new(x: f64, y: f64) -> Vector2d {
		Vector2d { x: x, y: y }
	}
	pub fn new_a(v: &[f64]) -> Vector2d {
		Vector2d { x: v[0], y: v[1] }
	}
	
	pub fn abs(&self) -> Vector2d {
		let mut ret = Vector2d::default();
		unsafe { tsVector2d_abs(&mut ret, self); }
		ret
	}
	
	pub fn min(v0: &Vector2d, v1: &Vector2d) -> Vector2d {
		let mut ret = Vector2d::default();
		unsafe { tsVector2d_min(&mut ret, v0, v1); }
		ret
	}
	pub fn max(v0: &Vector2d, v1: &Vector2d) -> Vector2d {
		let mut ret = Vector2d::default();
		unsafe { tsVector2d_max(&mut ret, v0, v1); }
		ret
	}
	pub fn clamp(&self, v0: &Vector2d, v1: &Vector2d) -> Vector2d {
		let mut ret = Vector2d::default();
		unsafe { tsVector2d_clamp(&mut ret, self, v0, v1); }
		ret
	}
	pub fn saturate(&self) -> Vector2d {
		let mut ret = Vector2d::default();
		unsafe { tsVector2d_saturate(&mut ret, self); }
		ret
	}
	
	pub fn dot(v0: &Vector2d, v1: &Vector2d) -> f64 {
		unsafe { tsVector2d_dot(v0, v1) }
	}
	pub fn cross(v0: &Vector2d, v1: &Vector2d) -> f64 {
		unsafe { tsVector2d_cross(v0, v1) }
	}
	
	pub fn length(&self) -> f64 {
		unsafe { tsVector2d_length(self) }
	}
	pub fn normalize(&self) -> Vector2d {
		let mut ret = Vector2d::default();
		unsafe { tsVector2d_normalize(&mut ret, self); }
		ret
	}
	
	pub fn lerp(v0: &Vector2d, v1: &Vector2d, k: f64) -> Vector2d {
		let mut ret = Vector2d::default();
		unsafe { tsVector2d_lerp(&mut ret, v0, v1, k); }
		ret
	}
	
	pub fn zero() -> Vector2d {
		Vector2d { x: 0.0, y: 0.0 }
	}
	pub fn one() -> Vector2d {
		Vector2d { x: 1.0, y: 1.0 }
	}
}

/*
 */
impl fmt::Display for Vector2d {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "({0} {1})", self.x, self.y)
	}
}

/*
 */
declare_neg_op!(Vector2d, tsVector2d_neg);

/*
 */
declare_scalar_op!(Vector2d, f64, Mul, mul, tsVector2d_mul1);
declare_scalar_op!(Vector2d, f64, Div, div, tsVector2d_div1);
declare_scalar_op!(Vector2d, f64, Add, add, tsVector2d_add1);
declare_scalar_op!(Vector2d, f64, Sub, sub, tsVector2d_sub1);

/*
 */
declare_vector_op!(Vector2d, Mul, mul, tsVector2d_mul);
declare_vector_op!(Vector2d, Div, div, tsVector2d_div);
declare_vector_op!(Vector2d, Add, add, tsVector2d_add);
declare_vector_op!(Vector2d, Sub, sub, tsVector2d_sub);

/*
 */
extern "C" {
	fn tsVector2d_abs(ret: *mut Vector2d, v: *const Vector2d) -> *mut Vector2d;
	fn tsVector2d_neg(ret: *mut Vector2d, v: *const Vector2d) -> *mut Vector2d;
	fn tsVector2d_mul1(ret: *mut Vector2d, v0: *const Vector2d, v1: f64) -> *mut Vector2d;
	fn tsVector2d_div1(ret: *mut Vector2d, v0: *const Vector2d, v1: f64) -> *mut Vector2d;
	fn tsVector2d_add1(ret: *mut Vector2d, v0: *const Vector2d, v1: f64) -> *mut Vector2d;
	fn tsVector2d_sub1(ret: *mut Vector2d, v0: *const Vector2d, v1: f64) -> *mut Vector2d;
	fn tsVector2d_mul(ret: *mut Vector2d, v0: *const Vector2d, v1: *const Vector2d) -> *mut Vector2d;
	fn tsVector2d_div(ret: *mut Vector2d, v0: *const Vector2d, v1: *const Vector2d) -> *mut Vector2d;
	fn tsVector2d_add(ret: *mut Vector2d, v0: *const Vector2d, v1: *const Vector2d) -> *mut Vector2d;
	fn tsVector2d_sub(ret: *mut Vector2d, v0: *const Vector2d, v1: *const Vector2d) -> *mut Vector2d;
	fn tsVector2d_min(ret: *mut Vector2d, v0: *const Vector2d, v1: *const Vector2d) -> *mut Vector2d;
	fn tsVector2d_max(ret: *mut Vector2d, v0: *const Vector2d, v1: *const Vector2d) -> *mut Vector2d;
	fn tsVector2d_clamp(ret: *mut Vector2d, v: *const Vector2d, v0: *const Vector2d, v1: *const Vector2d) -> *mut Vector2d;
	fn tsVector2d_saturate(ret: *mut Vector2d, v: *const Vector2d) -> *mut Vector2d;
	fn tsVector2d_dot(v0: *const Vector2d, v1: *const Vector2d) -> f64;
	fn tsVector2d_cross(v0: *const Vector2d, v1: *const Vector2d) -> f64;
	fn tsVector2d_length(v: *const Vector2d) -> f64;
	fn tsVector2d_normalize(ret: *mut Vector2d, v: *const Vector2d) -> *mut Vector2d;
	fn tsVector2d_lerp(ret: *mut Vector2d, v0: *const Vector2d, v1: *const Vector2d, k: f64) -> *mut Vector2d;
}

/*****************************************************************************\
 *
 * Vector3i
 *
\*****************************************************************************/

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct Vector3i {
	pub x: i32,
	pub y: i32,
	pub z: i32,
}

/*
 */
impl Vector3i {
	
	pub fn new_s(v: i32) -> Vector3i {
		Vector3i { x: v, y: v, z: v }
	}
	pub fn new_v2(v: &Vector2i, z: i32) -> Vector3i {
		Vector3i { x: v.x, y: v.y, z: z }
	}
	pub fn new_v3u(v: &Vector3u) -> Vector3i {
		Vector3i { x: v.x as i32, y: v.y as i32, z: v.z as i32 }
	}
	pub fn new_v3f(v: &Vector3f) -> Vector3i {
		Vector3i { x: v.x as i32, y: v.y as i32, z: v.z as i32 }
	}
	pub fn new_v3d(v: &Vector3d) -> Vector3i {
		Vector3i { x: v.x as i32, y: v.y as i32, z: v.z as i32 }
	}
	pub fn new_v4(v: &Vector4i) -> Vector3i {
		Vector3i { x: v.x, y: v.y, z: v.z }
	}
	pub fn new(x: i32, y: i32, z: i32) -> Vector3i {
		Vector3i { x: x, y: y, z: z }
	}
	pub fn new_a(v: &[i32]) -> Vector3i {
		Vector3i { x: v[0], y: v[1], z: v[2] }
	}
	
	pub fn abs(&self) -> Vector3i {
		let mut ret = Vector3i::default();
		unsafe { tsVector3i_abs(&mut ret, self); }
		ret
	}
	
	pub fn min(v0: &Vector3i, v1: &Vector3i) -> Vector3i {
		let mut ret = Vector3i::default();
		unsafe { tsVector3i_min(&mut ret, v0, v1); }
		ret
	}
	pub fn max(v0: &Vector3i, v1: &Vector3i) -> Vector3i {
		let mut ret = Vector3i::default();
		unsafe { tsVector3i_max(&mut ret, v0, v1); }
		ret
	}
	pub fn clamp(&self, v0: &Vector3i, v1: &Vector3i) -> Vector3i {
		let mut ret = Vector3i::default();
		unsafe { tsVector3i_clamp(&mut ret, self, v0, v1); }
		ret
	}
	
	pub fn zero() -> Vector3i {
		Vector3i { x: 0, y: 0, z: 0 }
	}
	pub fn one() -> Vector3i {
		Vector3i { x: 1, y: 1, z: 1 }
	}
}

/*
 */
impl fmt::Display for Vector3i {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "({0} {1} {2})", self.x, self.y, self.z)
	}
}

/*
 */
declare_neg_op!(Vector3i, tsVector3i_neg);

/*
 */
declare_scalar_op!(Vector3i, i32, Mul, mul, tsVector3i_mul1);
declare_scalar_op!(Vector3i, i32, Div, div, tsVector3i_div1);
declare_scalar_op!(Vector3i, i32, Add, add, tsVector3i_add1);
declare_scalar_op!(Vector3i, i32, Sub, sub, tsVector3i_sub1);
declare_scalar_op!(Vector3i, i32, BitAnd, bitand, tsVector3i_and1);
declare_scalar_op!(Vector3i, i32, BitOr,  bitor,  tsVector3i_or1);
declare_scalar_op!(Vector3i, i32, BitXor, bitxor, tsVector3i_xor1);
declare_scalar_op!(Vector3i, i32, Shl, shl, tsVector3i_shl1);
declare_scalar_op!(Vector3i, i32, Shr, shr, tsVector3i_shr1);

/*
 */
declare_vector_op!(Vector3i, Mul, mul, tsVector3i_mul);
declare_vector_op!(Vector3i, Div, div, tsVector3i_div);
declare_vector_op!(Vector3i, Add, add, tsVector3i_add);
declare_vector_op!(Vector3i, Sub, sub, tsVector3i_sub);
declare_vector_op!(Vector3i, BitAnd, bitand, tsVector3i_and);
declare_vector_op!(Vector3i, BitOr,  bitor,  tsVector3i_or);
declare_vector_op!(Vector3i, BitXor, bitxor, tsVector3i_xor);

/*
 */
extern "C" {
	fn tsVector3i_abs(ret: *mut Vector3i, v: *const Vector3i) -> *mut Vector3i;
	fn tsVector3i_neg(ret: *mut Vector3i, v: *const Vector3i) -> *mut Vector3i;
	fn tsVector3i_mul1(ret: *mut Vector3i, v0: *const Vector3i, v1: i32) -> *mut Vector3i;
	fn tsVector3i_div1(ret: *mut Vector3i, v0: *const Vector3i, v1: i32) -> *mut Vector3i;
	fn tsVector3i_add1(ret: *mut Vector3i, v0: *const Vector3i, v1: i32) -> *mut Vector3i;
	fn tsVector3i_sub1(ret: *mut Vector3i, v0: *const Vector3i, v1: i32) -> *mut Vector3i;
	fn tsVector3i_and1(ret: *mut Vector3i, v0: *const Vector3i, v1: i32) -> *mut Vector3i;
	fn tsVector3i_or1(ret: *mut Vector3i, v0: *const Vector3i, v1: i32) -> *mut Vector3i;
	fn tsVector3i_xor1(ret: *mut Vector3i, v0: *const Vector3i, v1: i32) -> *mut Vector3i;
	fn tsVector3i_shl1(ret: *mut Vector3i, v0: *const Vector3i, v1: i32) -> *mut Vector3i;
	fn tsVector3i_shr1(ret: *mut Vector3i, v0: *const Vector3i, v1: i32) -> *mut Vector3i;
	fn tsVector3i_mul(ret: *mut Vector3i, v0: *const Vector3i, v1: *const Vector3i) -> *mut Vector3i;
	fn tsVector3i_div(ret: *mut Vector3i, v0: *const Vector3i, v1: *const Vector3i) -> *mut Vector3i;
	fn tsVector3i_add(ret: *mut Vector3i, v0: *const Vector3i, v1: *const Vector3i) -> *mut Vector3i;
	fn tsVector3i_sub(ret: *mut Vector3i, v0: *const Vector3i, v1: *const Vector3i) -> *mut Vector3i;
	fn tsVector3i_and(ret: *mut Vector3i, v0: *const Vector3i, v1: *const Vector3i) -> *mut Vector3i;
	fn tsVector3i_or(ret: *mut Vector3i, v0: *const Vector3i, v1: *const Vector3i) -> *mut Vector3i;
	fn tsVector3i_xor(ret: *mut Vector3i, v0: *const Vector3i, v1: *const Vector3i) -> *mut Vector3i;
	fn tsVector3i_min(ret: *mut Vector3i, v0: *const Vector3i, v1: *const Vector3i) -> *mut Vector3i;
	fn tsVector3i_max(ret: *mut Vector3i, v0: *const Vector3i, v1: *const Vector3i) -> *mut Vector3i;
	fn tsVector3i_clamp(ret: *mut Vector3i, v: *const Vector3i, v0: *const Vector3i, v1: *const Vector3i) -> *mut Vector3i;
}

/*****************************************************************************\
 *
 * Vector3u
 *
\*****************************************************************************/

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct Vector3u {
	pub x: u32,
	pub y: u32,
	pub z: u32,
}

/*
 */
impl Vector3u {
	
	pub fn new_s(v: u32) -> Vector3u {
		Vector3u { x: v, y: v, z: v }
	}
	pub fn new_v2(v: &Vector2u, z: u32) -> Vector3u {
		Vector3u { x: v.x, y: v.y, z: z }
	}
	pub fn new_v3i(v: &Vector3i) -> Vector3u {
		Vector3u { x: v.x as u32, y: v.y as u32, z: v.z as u32 }
	}
	pub fn new_v3f(v: &Vector3f) -> Vector3u {
		Vector3u { x: v.x as u32, y: v.y as u32, z: v.z as u32 }
	}
	pub fn new_v3d(v: &Vector3d) -> Vector3u {
		Vector3u { x: v.x as u32, y: v.y as u32, z: v.z as u32 }
	}
	pub fn new_v4(v: &Vector4u) -> Vector3u {
		Vector3u { x: v.x, y: v.y, z: v.z }
	}
	pub fn new(x: u32, y: u32, z: u32) -> Vector3u {
		Vector3u { x: x, y: y, z: z }
	}
	pub fn new_a(v: &[u32]) -> Vector3u {
		Vector3u { x: v[0], y: v[1], z: v[2] }
	}
	
	pub fn min(v0: &Vector3u, v1: &Vector3u) -> Vector3u {
		let mut ret = Vector3u::default();
		unsafe { tsVector3u_min(&mut ret, v0, v1); }
		ret
	}
	pub fn max(v0: &Vector3u, v1: &Vector3u) -> Vector3u {
		let mut ret = Vector3u::default();
		unsafe { tsVector3u_max(&mut ret, v0, v1); }
		ret
	}
	pub fn clamp(&self, v0: &Vector3u, v1: &Vector3u) -> Vector3u {
		let mut ret = Vector3u::default();
		unsafe { tsVector3u_clamp(&mut ret, self, v0, v1); }
		ret
	}
	
	pub fn zero() -> Vector3u {
		Vector3u { x: 0, y: 0, z: 0 }
	}
	pub fn one() -> Vector3u {
		Vector3u { x: 1, y: 1, z: 1 }
	}
}

/*
 */
impl fmt::Display for Vector3u {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "({0} {1} {2})", self.x, self.y, self.z)
	}
}

/*
 */
declare_scalar_op!(Vector3u, u32, Mul, mul, tsVector3u_mul1);
declare_scalar_op!(Vector3u, u32, Div, div, tsVector3u_div1);
declare_scalar_op!(Vector3u, u32, Add, add, tsVector3u_add1);
declare_scalar_op!(Vector3u, u32, Sub, sub, tsVector3u_sub1);
declare_scalar_op!(Vector3u, u32, BitAnd, bitand, tsVector3u_and1);
declare_scalar_op!(Vector3u, u32, BitOr,  bitor,  tsVector3u_or1);
declare_scalar_op!(Vector3u, u32, BitXor, bitxor, tsVector3u_xor1);
declare_scalar_op!(Vector3u, u32, Shl, shl, tsVector3u_shl1);
declare_scalar_op!(Vector3u, u32, Shr, shr, tsVector3u_shr1);

/*
 */
declare_vector_op!(Vector3u, Mul, mul, tsVector3u_mul);
declare_vector_op!(Vector3u, Div, div, tsVector3u_div);
declare_vector_op!(Vector3u, Add, add, tsVector3u_add);
declare_vector_op!(Vector3u, Sub, sub, tsVector3u_sub);
declare_vector_op!(Vector3u, BitAnd, bitand, tsVector3u_and);
declare_vector_op!(Vector3u, BitOr,  bitor,  tsVector3u_or);
declare_vector_op!(Vector3u, BitXor, bitxor, tsVector3u_xor);

/*
 */
extern "C" {
	fn tsVector3u_mul1(ret: *mut Vector3u, v0: *const Vector3u, v1: u32) -> *mut Vector3u;
	fn tsVector3u_div1(ret: *mut Vector3u, v0: *const Vector3u, v1: u32) -> *mut Vector3u;
	fn tsVector3u_add1(ret: *mut Vector3u, v0: *const Vector3u, v1: u32) -> *mut Vector3u;
	fn tsVector3u_sub1(ret: *mut Vector3u, v0: *const Vector3u, v1: u32) -> *mut Vector3u;
	fn tsVector3u_and1(ret: *mut Vector3u, v0: *const Vector3u, v1: u32) -> *mut Vector3u;
	fn tsVector3u_or1(ret: *mut Vector3u, v0: *const Vector3u, v1: u32) -> *mut Vector3u;
	fn tsVector3u_xor1(ret: *mut Vector3u, v0: *const Vector3u, v1: u32) -> *mut Vector3u;
	fn tsVector3u_shl1(ret: *mut Vector3u, v0: *const Vector3u, v1: u32) -> *mut Vector3u;
	fn tsVector3u_shr1(ret: *mut Vector3u, v0: *const Vector3u, v1: u32) -> *mut Vector3u;
	fn tsVector3u_mul(ret: *mut Vector3u, v0: *const Vector3u, v1: *const Vector3u) -> *mut Vector3u;
	fn tsVector3u_div(ret: *mut Vector3u, v0: *const Vector3u, v1: *const Vector3u) -> *mut Vector3u;
	fn tsVector3u_add(ret: *mut Vector3u, v0: *const Vector3u, v1: *const Vector3u) -> *mut Vector3u;
	fn tsVector3u_sub(ret: *mut Vector3u, v0: *const Vector3u, v1: *const Vector3u) -> *mut Vector3u;
	fn tsVector3u_and(ret: *mut Vector3u, v0: *const Vector3u, v1: *const Vector3u) -> *mut Vector3u;
	fn tsVector3u_or(ret: *mut Vector3u, v0: *const Vector3u, v1: *const Vector3u) -> *mut Vector3u;
	fn tsVector3u_xor(ret: *mut Vector3u, v0: *const Vector3u, v1: *const Vector3u) -> *mut Vector3u;
	fn tsVector3u_min(ret: *mut Vector3u, v0: *const Vector3u, v1: *const Vector3u) -> *mut Vector3u;
	fn tsVector3u_max(ret: *mut Vector3u, v0: *const Vector3u, v1: *const Vector3u) -> *mut Vector3u;
	fn tsVector3u_clamp(ret: *mut Vector3u, v: *const Vector3u, v0: *const Vector3u, v1: *const Vector3u) -> *mut Vector3u;
}

/*****************************************************************************\
 *
 * Vector3f
 *
\*****************************************************************************/

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct Vector3f {
	pub x: f32,
	pub y: f32,
	pub z: f32,
}

/*
 */
impl Vector3f {
	
	pub fn new_s(v: f32) -> Vector3f {
		Vector3f { x: v, y: v, z: v }
	}
	pub fn new_v2(v: &Vector2f, z: f32) -> Vector3f {
		Vector3f { x: v.x, y: v.y, z: z }
	}
	pub fn new_v3i(v: &Vector3i) -> Vector3f {
		Vector3f { x: v.x as f32, y: v.y as f32, z: v.z as f32 }
	}
	pub fn new_v3u(v: &Vector3u) -> Vector3f {
		Vector3f { x: v.x as f32, y: v.y as f32, z: v.z as f32 }
	}
	pub fn new_v3d(v: &Vector3d) -> Vector3f {
		Vector3f { x: v.x as f32, y: v.y as f32, z: v.z as f32 }
	}
	pub fn new_v4(v: &Vector4f) -> Vector3f {
		Vector3f { x: v.x, y: v.y, z: v.z }
	}
	pub fn new(x: f32, y: f32, z: f32) -> Vector3f {
		Vector3f { x: x, y: y, z: z }
	}
	pub fn newf(v: &[f32]) -> Vector3f {
		Vector3f { x: v[0], y: v[1], z: v[2] }
	}
	
	pub fn abs(&self) -> Vector3f {
		let mut ret = Vector3f::default();
		unsafe { tsVector3f_abs(&mut ret, self); }
		ret
	}
	
	pub fn min(v0: &Vector3f, v1: &Vector3f) -> Vector3f {
		let mut ret = Vector3f::default();
		unsafe { tsVector3f_min(&mut ret, v0, v1); }
		ret
	}
	pub fn max(v0: &Vector3f, v1: &Vector3f) -> Vector3f {
		let mut ret = Vector3f::default();
		unsafe { tsVector3f_max(&mut ret, v0, v1); }
		ret
	}
	pub fn clamp(&self, v0: &Vector3f, v1: &Vector3f) -> Vector3f {
		let mut ret = Vector3f::default();
		unsafe { tsVector3f_clamp(&mut ret, self, v0, v1); }
		ret
	}
	pub fn saturate(&self) -> Vector3f {
		let mut ret = Vector3f::default();
		unsafe { tsVector3f_saturate(&mut ret, self); }
		ret
	}
	
	pub fn dot(v0: &Vector3f, v1: &Vector3f) -> f32 {
		unsafe { tsVector3f_dot(v0, v1) }
	}
	pub fn cross(v0: &Vector3f, v1: &Vector3f) -> Vector3f {
		let mut ret = Vector3f::default();
		unsafe { tsVector3f_cross(&mut ret, v0, v1); }
		ret
	}
	
	pub fn length(&self) -> f32 {
		unsafe { tsVector3f_length(self) }
	}
	pub fn normalize(&self) -> Vector3f {
		let mut ret = Vector3f::default();
		unsafe { tsVector3f_normalize(&mut ret, self); }
		ret
	}
	
	pub fn lerp(v0: &Vector3f, v1: &Vector3f, k: f32) -> Vector3f {
		let mut ret = Vector3f::default();
		unsafe { tsVector3f_lerp(&mut ret, v0, v1, k); }
		ret
	}
	
	pub fn zero() -> Vector3f {
		Vector3f { x: 0.0, y: 0.0, z: 0.0 }
	}
	pub fn one() -> Vector3f {
		Vector3f { x: 1.0, y: 1.0, z: 1.0 }
	}
}

/*
 */
impl fmt::Display for Vector3f {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "({0} {1} {2})", self.x, self.y, self.z)
	}
}

/*
 */
declare_neg_op!(Vector3f, tsVector3f_neg);

/*
 */
declare_scalar_op!(Vector3f, f32, Mul, mul, tsVector3f_mul1);
declare_scalar_op!(Vector3f, f32, Div, div, tsVector3f_div1);
declare_scalar_op!(Vector3f, f32, Add, add, tsVector3f_add1);
declare_scalar_op!(Vector3f, f32, Sub, sub, tsVector3f_sub1);

/*
 */
declare_vector_op!(Vector3f, Mul, mul, tsVector3f_mul);
declare_vector_op!(Vector3f, Div, div, tsVector3f_div);
declare_vector_op!(Vector3f, Add, add, tsVector3f_add);
declare_vector_op!(Vector3f, Sub, sub, tsVector3f_sub);

/*
 */
extern "C" {
	fn tsVector3f_abs(ret: *mut Vector3f, v: *const Vector3f) -> *mut Vector3f;
	fn tsVector3f_neg(ret: *mut Vector3f, v: *const Vector3f) -> *mut Vector3f;
	fn tsVector3f_mul1(ret: *mut Vector3f, v0: *const Vector3f, v1: f32) -> *mut Vector3f;
	fn tsVector3f_div1(ret: *mut Vector3f, v0: *const Vector3f, v1: f32) -> *mut Vector3f;
	fn tsVector3f_add1(ret: *mut Vector3f, v0: *const Vector3f, v1: f32) -> *mut Vector3f;
	fn tsVector3f_sub1(ret: *mut Vector3f, v0: *const Vector3f, v1: f32) -> *mut Vector3f;
	fn tsVector3f_mul(ret: *mut Vector3f, v0: *const Vector3f, v1: *const Vector3f) -> *mut Vector3f;
	fn tsVector3f_div(ret: *mut Vector3f, v0: *const Vector3f, v1: *const Vector3f) -> *mut Vector3f;
	fn tsVector3f_add(ret: *mut Vector3f, v0: *const Vector3f, v1: *const Vector3f) -> *mut Vector3f;
	fn tsVector3f_sub(ret: *mut Vector3f, v0: *const Vector3f, v1: *const Vector3f) -> *mut Vector3f;
	fn tsVector3f_min(ret: *mut Vector3f, v0: *const Vector3f, v1: *const Vector3f) -> *mut Vector3f;
	fn tsVector3f_max(ret: *mut Vector3f, v0: *const Vector3f, v1: *const Vector3f) -> *mut Vector3f;
	fn tsVector3f_clamp(ret: *mut Vector3f, v: *const Vector3f, v0: *const Vector3f, v1: *const Vector3f) -> *mut Vector3f;
	fn tsVector3f_saturate(ret: *mut Vector3f, v: *const Vector3f) -> *mut Vector3f;
	fn tsVector3f_dot(v0: *const Vector3f, v1: *const Vector3f) -> f32;
	fn tsVector3f_cross(ret: *mut Vector3f, v0: *const Vector3f, v1: *const Vector3f) -> *mut Vector3f;
	fn tsVector3f_length(v: *const Vector3f) -> f32;
	fn tsVector3f_normalize(ret: *mut Vector3f, v: *const Vector3f) -> *mut Vector3f;
	fn tsVector3f_lerp(ret: *mut Vector3f, v0: *const Vector3f, v1: *const Vector3f, k: f32) -> *mut Vector3f;
}

/*****************************************************************************\
 *
 * Vector3d
 *
\*****************************************************************************/

/*
 */
#[repr(C)]
#[derive(Copy, Clone, Default)]
pub struct Vector3d {
	pub x: f64,
	pub y: f64,
	pub z: f64,
}

/*
 */
impl Vector3d {
	
	pub fn new_s(v: f64) -> Vector3d {
		Vector3d { x: v, y: v, z: v }
	}
	pub fn new_v2(v: &Vector2d, z: f64) -> Vector3d {
		Vector3d { x: v.x, y: v.y, z: z }
	}
	pub fn new_v3i(v: &Vector3i) -> Vector3d {
		Vector3d { x: v.x as f64, y: v.y as f64, z: v.z as f64 }
	}
	pub fn new_v3u(v: &Vector3u) -> Vector3d {
		Vector3d { x: v.x as f64, y: v.y as f64, z: v.z as f64 }
	}
	pub fn new_v3f(v: &Vector3f) -> Vector3d {
		Vector3d { x: v.x as f64, y: v.y as f64, z: v.z as f64 }
	}
	pub fn new_v4(v: &Vector4d) -> Vector3d {
		Vector3d { x: v.x, y: v.y, z: v.z }
	}
	pub fn new(x: f64, y: f64, z: f64) -> Vector3d {
		Vector3d { x: x, y: y, z: z }
	}
	pub fn new_a(v: &[f64]) -> Vector3d {
		Vector3d { x: v[0], y: v[1], z: v[2] }
	}
	
	pub fn abs(&self) -> Vector3d {
		let mut ret = Vector3d::default();
		unsafe { tsVector3d_abs(&mut ret, self); }
		ret
	}
	
	pub fn min(v0: &Vector3d, v1: &Vector3d) -> Vector3d {
		let mut ret = Vector3d::default();
		unsafe { tsVector3d_min(&mut ret, v0, v1); }
		ret
	}
	pub fn max(v0: &Vector3d, v1: &Vector3d) -> Vector3d {
		let mut ret = Vector3d::default();
		unsafe { tsVector3d_max(&mut ret, v0, v1); }
		ret
	}
	pub fn clamp(&self, v0: &Vector3d, v1: &Vector3d) -> Vector3d {
		let mut ret = Vector3d::default();
		unsafe { tsVector3d_clamp(&mut ret, self, v0, v1); }
		ret
	}
	pub fn saturate(&self) -> Vector3d {
		let mut ret = Vector3d::default();
		unsafe { tsVector3d_saturate(&mut ret, self); }
		ret
	}
	
	pub fn dot(v0: &Vector3d, v1: &Vector3d) -> f64 {
		unsafe { tsVector3d_dot(v0, v1) }
	}
	pub fn cross(v0: &Vector3d, v1: &Vector3d) -> Vector3d {
		let mut ret = Vector3d::default();
		unsafe { tsVector3d_cross(&mut ret, v0, v1); }
		ret
	}
	
	pub fn length(&self) -> f64 {
		unsafe { tsVector3d_length(self) }
	}
	pub fn normalize(&self) -> Vector3d {
		let mut ret = Vector3d::default();
		unsafe { tsVector3d_normalize(&mut ret, self); }
		ret
	}
	
	pub fn lerp(v0: &Vector3d, v1: &Vector3d, k: f64) -> Vector3d {
		let mut ret = Vector3d::default();
		unsafe { tsVector3d_lerp(&mut ret, v0, v1, k); }
		ret
	}
	
	pub fn zero() -> Vector3d {
		Vector3d { x: 0.0, y: 0.0, z: 0.0 }
	}
	pub fn one() -> Vector3d {
		Vector3d { x: 1.0, y: 1.0, z: 1.0 }
	}
}

/*
 */
impl fmt::Display for Vector3d {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "({0} {1} {2})", self.x, self.y, self.z)
	}
}

/*
 */
declare_neg_op!(Vector3d, tsVector3d_neg);

/*
 */
declare_scalar_op!(Vector3d, f64, Mul, mul, tsVector3d_mul1);
declare_scalar_op!(Vector3d, f64, Div, div, tsVector3d_div1);
declare_scalar_op!(Vector3d, f64, Add, add, tsVector3d_add1);
declare_scalar_op!(Vector3d, f64, Sub, sub, tsVector3d_sub1);

/*
 */
declare_vector_op!(Vector3d, Mul, mul, tsVector3d_mul);
declare_vector_op!(Vector3d, Div, div, tsVector3d_div);
declare_vector_op!(Vector3d, Add, add, tsVector3d_add);
declare_vector_op!(Vector3d, Sub, sub, tsVector3d_sub);

/*
 */
extern "C" {
	fn tsVector3d_abs(ret: *mut Vector3d, v: *const Vector3d) -> *mut Vector3d;
	fn tsVector3d_neg(ret: *mut Vector3d, v: *const Vector3d) -> *mut Vector3d;
	fn tsVector3d_mul1(ret: *mut Vector3d, v0: *const Vector3d, v1: f64) -> *mut Vector3d;
	fn tsVector3d_div1(ret: *mut Vector3d, v0: *const Vector3d, v1: f64) -> *mut Vector3d;
	fn tsVector3d_add1(ret: *mut Vector3d, v0: *const Vector3d, v1: f64) -> *mut Vector3d;
	fn tsVector3d_sub1(ret: *mut Vector3d, v0: *const Vector3d, v1: f64) -> *mut Vector3d;
	fn tsVector3d_mul(ret: *mut Vector3d, v0: *const Vector3d, v1: *const Vector3d) -> *mut Vector3d;
	fn tsVector3d_div(ret: *mut Vector3d, v0: *const Vector3d, v1: *const Vector3d) -> *mut Vector3d;
	fn tsVector3d_add(ret: *mut Vector3d, v0: *const Vector3d, v1: *const Vector3d) -> *mut Vector3d;
	fn tsVector3d_sub(ret: *mut Vector3d, v0: *const Vector3d, v1: *const Vector3d) -> *mut Vector3d;
	fn tsVector3d_min(ret: *mut Vector3d, v0: *const Vector3d, v1: *const Vector3d) -> *mut Vector3d;
	fn tsVector3d_max(ret: *mut Vector3d, v0: *const Vector3d, v1: *const Vector3d) -> *mut Vector3d;
	fn tsVector3d_clamp(ret: *mut Vector3d, v: *const Vector3d, v0: *const Vector3d, v1: *const Vector3d) -> *mut Vector3d;
	fn tsVector3d_saturate(ret: *mut Vector3d, v: *const Vector3d) -> *mut Vector3d;
	fn tsVector3d_dot(v0: *const Vector3d, v1: *const Vector3d) -> f64;
	fn tsVector3d_cross(ret: *mut Vector3d, v0: *const Vector3d, v1: *const Vector3d) -> *mut Vector3d;
	fn tsVector3d_length(v: *const Vector3d) -> f64;
	fn tsVector3d_normalize(ret: *mut Vector3d, v: *const Vector3d) -> *mut Vector3d;
	fn tsVector3d_lerp(ret: *mut Vector3d, v0: *const Vector3d, v1: *const Vector3d, k: f64) -> *mut Vector3d;
}

/*****************************************************************************\
 *
 * Vector4i
 *
\*****************************************************************************/

/*
 */
#[repr(C, align(16))]
#[derive(Copy, Clone, Default)]
pub struct Vector4i {
	pub x: i32,
	pub y: i32,
	pub z: i32,
	pub w: i32,
}

/*
 */
impl Vector4i {
	
	pub fn new_s(v: i32) -> Vector4i {
		Vector4i { x: v, y: v, z: v, w: v }
	}
	pub fn new_v2(v: &Vector2i, z: i32, w: i32) -> Vector4i {
		Vector4i { x: v.x, y: v.y, z: z, w: w }
	}
	pub fn new_v3(v: &Vector3i, w: i32) -> Vector4i {
		Vector4i { x: v.x, y: v.y, z: v.z, w: w }
	}
	pub fn new(x: i32, y: i32, z: i32, w: i32) -> Vector4i {
		Vector4i { x: x, y: y, z: z, w: w }
	}
	pub fn new_a(v: &[i32]) -> Vector4i {
		Vector4i { x: v[0], y: v[1], z: v[2], w: v[3] }
	}
	
	pub fn abs(&self) -> Vector4i {
		let mut ret = Vector4i::default();
		unsafe { tsVector4i_abs(&mut ret, self); }
		ret
	}
	
	pub fn min(v0: &Vector4i, v1: &Vector4i) -> Vector4i {
		let mut ret = Vector4i::default();
		unsafe { tsVector4i_min(&mut ret, v0, v1); }
		ret
	}
	pub fn max(v0: &Vector4i, v1: &Vector4i) -> Vector4i {
		let mut ret = Vector4i::default();
		unsafe { tsVector4i_max(&mut ret, v0, v1); }
		ret
	}
	pub fn clamp(&self, v0: &Vector4i, v1: &Vector4i) -> Vector4i {
		let mut ret = Vector4i::default();
		unsafe { tsVector4i_clamp(&mut ret, self, v0, v1); }
		ret
	}
	
	pub fn zero() -> Vector4i {
		Vector4i { x: 0, y: 0, z: 0, w: 0 }
	}
	pub fn one() -> Vector4i {
		Vector4i { x: 1, y: 1, z: 1, w: 1 }
	}
}

/*
 */
impl fmt::Display for Vector4i {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "({0} {1} {2} {3})", self.x, self.y, self.z, self.w)
	}
}

/*
 */
declare_neg_op!(Vector4i, tsVector4i_neg);

/*
 */
declare_scalar_op!(Vector4i, i32, Mul, mul, tsVector4i_mul1);
declare_scalar_op!(Vector4i, i32, Div, div, tsVector4i_div1);
declare_scalar_op!(Vector4i, i32, Add, add, tsVector4i_add1);
declare_scalar_op!(Vector4i, i32, Sub, sub, tsVector4i_sub1);
declare_scalar_op!(Vector4i, i32, BitAnd, bitand, tsVector4i_and1);
declare_scalar_op!(Vector4i, i32, BitOr,  bitor,  tsVector4i_or1);
declare_scalar_op!(Vector4i, i32, BitXor, bitxor, tsVector4i_xor1);
declare_scalar_op!(Vector4i, i32, Shl, shl, tsVector4i_shl1);
declare_scalar_op!(Vector4i, i32, Shr, shr, tsVector4i_shr1);

/*
 */
declare_vector_op!(Vector4i, Mul, mul, tsVector4i_mul);
declare_vector_op!(Vector4i, Div, div, tsVector4i_div);
declare_vector_op!(Vector4i, Add, add, tsVector4i_add);
declare_vector_op!(Vector4i, Sub, sub, tsVector4i_sub);
declare_vector_op!(Vector4i, BitAnd, bitand, tsVector4i_and);
declare_vector_op!(Vector4i, BitOr,  bitor,  tsVector4i_or);
declare_vector_op!(Vector4i, BitXor, bitxor, tsVector4i_xor);

/*
 */
extern "C" {
	fn tsVector4i_abs(ret: *mut Vector4i, v: *const Vector4i) -> *mut Vector4i;
	fn tsVector4i_neg(ret: *mut Vector4i, v: *const Vector4i) -> *mut Vector4i;
	fn tsVector4i_mul1(ret: *mut Vector4i, v0: *const Vector4i, v1: i32) -> *mut Vector4i;
	fn tsVector4i_div1(ret: *mut Vector4i, v0: *const Vector4i, v1: i32) -> *mut Vector4i;
	fn tsVector4i_add1(ret: *mut Vector4i, v0: *const Vector4i, v1: i32) -> *mut Vector4i;
	fn tsVector4i_sub1(ret: *mut Vector4i, v0: *const Vector4i, v1: i32) -> *mut Vector4i;
	fn tsVector4i_and1(ret: *mut Vector4i, v0: *const Vector4i, v1: i32) -> *mut Vector4i;
	fn tsVector4i_or1(ret: *mut Vector4i, v0: *const Vector4i, v1: i32) -> *mut Vector4i;
	fn tsVector4i_xor1(ret: *mut Vector4i, v0: *const Vector4i, v1: i32) -> *mut Vector4i;
	fn tsVector4i_shl1(ret: *mut Vector4i, v0: *const Vector4i, v1: i32) -> *mut Vector4i;
	fn tsVector4i_shr1(ret: *mut Vector4i, v0: *const Vector4i, v1: i32) -> *mut Vector4i;
	fn tsVector4i_mul(ret: *mut Vector4i, v0: *const Vector4i, v1: *const Vector4i) -> *mut Vector4i;
	fn tsVector4i_div(ret: *mut Vector4i, v0: *const Vector4i, v1: *const Vector4i) -> *mut Vector4i;
	fn tsVector4i_add(ret: *mut Vector4i, v0: *const Vector4i, v1: *const Vector4i) -> *mut Vector4i;
	fn tsVector4i_sub(ret: *mut Vector4i, v0: *const Vector4i, v1: *const Vector4i) -> *mut Vector4i;
	fn tsVector4i_and(ret: *mut Vector4i, v0: *const Vector4i, v1: *const Vector4i) -> *mut Vector4i;
	fn tsVector4i_or(ret: *mut Vector4i, v0: *const Vector4i, v1: *const Vector4i) -> *mut Vector4i;
	fn tsVector4i_xor(ret: *mut Vector4i, v0: *const Vector4i, v1: *const Vector4i) -> *mut Vector4i;
	fn tsVector4i_min(ret: *mut Vector4i, v0: *const Vector4i, v1: *const Vector4i) -> *mut Vector4i;
	fn tsVector4i_max(ret: *mut Vector4i, v0: *const Vector4i, v1: *const Vector4i) -> *mut Vector4i;
	fn tsVector4i_clamp(ret: *mut Vector4i, v: *const Vector4i, v0: *const Vector4i, v1: *const Vector4i) -> *mut Vector4i;
}

/*****************************************************************************\
 *
 * Vector4u
 *
\*****************************************************************************/

/*
 */
#[repr(C, align(16))]
#[derive(Copy, Clone, Default)]
pub struct Vector4u {
	pub x: u32,
	pub y: u32,
	pub z: u32,
	pub w: u32,
}

/*
 */
impl Vector4u {
	
	pub fn new_s(v: u32) -> Vector4u {
		Vector4u { x: v, y: v, z: v, w: v }
	}
	pub fn new_v2(v: &Vector2u, z: u32, w: u32) -> Vector4u {
		Vector4u { x: v.x, y: v.y, z: z, w: w }
	}
	pub fn new_v3(v: &Vector3u, w: u32) -> Vector4u {
		Vector4u { x: v.x, y: v.y, z: v.z, w: w }
	}
	pub fn new_v4i(v: &Vector4i) -> Vector4u {
		Vector4u { x: v.x as u32, y: v.y as u32, z: v.z as u32, w: v.w as u32 }
	}
	pub fn new_v4f(v: &Vector4f) -> Vector4u {
		Vector4u { x: v.x as u32, y: v.y as u32, z: v.z as u32, w: v.w as u32 }
	}
	pub fn new_v4d(v: &Vector4d) -> Vector4u {
		Vector4u { x: v.x as u32, y: v.y as u32, z: v.z as u32, w: v.w as u32 }
	}
	pub fn new(x: u32, y: u32, z: u32, w: u32) -> Vector4u {
		Vector4u { x: x, y: y, z: z, w: w }
	}
	pub fn new_a(v: &[u32]) -> Vector4u {
		Vector4u { x: v[0], y: v[1], z: v[2], w: v[3] }
	}
	
	pub fn min(v0: &Vector4u, v1: &Vector4u) -> Vector4u {
		let mut ret = Vector4u::default();
		unsafe { tsVector4u_min(&mut ret, v0, v1); }
		ret
	}
	pub fn max(v0: &Vector4u, v1: &Vector4u) -> Vector4u {
		let mut ret = Vector4u::default();
		unsafe { tsVector4u_max(&mut ret, v0, v1); }
		ret
	}
	pub fn clamp(&self, v0: &Vector4u, v1: &Vector4u) -> Vector4u {
		let mut ret = Vector4u::default();
		unsafe { tsVector4u_clamp(&mut ret, self, v0, v1); }
		ret
	}
	
	pub fn zero() -> Vector4u {
		Vector4u { x: 0, y: 0, z: 0, w: 0 }
	}
	pub fn one() -> Vector4u {
		Vector4u { x: 1, y: 1, z: 1, w: 1 }
	}
}

/*
 */
impl fmt::Display for Vector4u {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "({0} {1} {2} {3})", self.x, self.y, self.z, self.w)
	}
}

/*
 */
declare_scalar_op!(Vector4u, u32, Mul, mul, tsVector4u_mul1);
declare_scalar_op!(Vector4u, u32, Div, div, tsVector4u_div1);
declare_scalar_op!(Vector4u, u32, Add, add, tsVector4u_add1);
declare_scalar_op!(Vector4u, u32, Sub, sub, tsVector4u_sub1);
declare_scalar_op!(Vector4u, u32, BitAnd, bitand, tsVector4u_and1);
declare_scalar_op!(Vector4u, u32, BitOr,  bitor,  tsVector4u_or1);
declare_scalar_op!(Vector4u, u32, BitXor, bitxor, tsVector4u_xor1);
declare_scalar_op!(Vector4u, u32, Shl, shl, tsVector4u_shl1);
declare_scalar_op!(Vector4u, u32, Shr, shr, tsVector4u_shr1);

/*
 */
declare_vector_op!(Vector4u, Mul, mul, tsVector4u_mul);
declare_vector_op!(Vector4u, Div, div, tsVector4u_div);
declare_vector_op!(Vector4u, Add, add, tsVector4u_add);
declare_vector_op!(Vector4u, Sub, sub, tsVector4u_sub);
declare_vector_op!(Vector4u, BitAnd, bitand, tsVector4u_and);
declare_vector_op!(Vector4u, BitOr,  bitor,  tsVector4u_or);
declare_vector_op!(Vector4u, BitXor, bitxor, tsVector4u_xor);

/*
 */
extern "C" {
	fn tsVector4u_mul1(ret: *mut Vector4u, v0: *const Vector4u, v1: u32) -> *mut Vector4u;
	fn tsVector4u_div1(ret: *mut Vector4u, v0: *const Vector4u, v1: u32) -> *mut Vector4u;
	fn tsVector4u_add1(ret: *mut Vector4u, v0: *const Vector4u, v1: u32) -> *mut Vector4u;
	fn tsVector4u_sub1(ret: *mut Vector4u, v0: *const Vector4u, v1: u32) -> *mut Vector4u;
	fn tsVector4u_and1(ret: *mut Vector4u, v0: *const Vector4u, v1: u32) -> *mut Vector4u;
	fn tsVector4u_or1(ret: *mut Vector4u, v0: *const Vector4u, v1: u32) -> *mut Vector4u;
	fn tsVector4u_xor1(ret: *mut Vector4u, v0: *const Vector4u, v1: u32) -> *mut Vector4u;
	fn tsVector4u_shl1(ret: *mut Vector4u, v0: *const Vector4u, v1: u32) -> *mut Vector4u;
	fn tsVector4u_shr1(ret: *mut Vector4u, v0: *const Vector4u, v1: u32) -> *mut Vector4u;
	fn tsVector4u_mul(ret: *mut Vector4u, v0: *const Vector4u, v1: *const Vector4u) -> *mut Vector4u;
	fn tsVector4u_div(ret: *mut Vector4u, v0: *const Vector4u, v1: *const Vector4u) -> *mut Vector4u;
	fn tsVector4u_add(ret: *mut Vector4u, v0: *const Vector4u, v1: *const Vector4u) -> *mut Vector4u;
	fn tsVector4u_sub(ret: *mut Vector4u, v0: *const Vector4u, v1: *const Vector4u) -> *mut Vector4u;
	fn tsVector4u_and(ret: *mut Vector4u, v0: *const Vector4u, v1: *const Vector4u) -> *mut Vector4u;
	fn tsVector4u_or(ret: *mut Vector4u, v0: *const Vector4u, v1: *const Vector4u) -> *mut Vector4u;
	fn tsVector4u_xor(ret: *mut Vector4u, v0: *const Vector4u, v1: *const Vector4u) -> *mut Vector4u;
	fn tsVector4u_min(ret: *mut Vector4u, v0: *const Vector4u, v1: *const Vector4u) -> *mut Vector4u;
	fn tsVector4u_max(ret: *mut Vector4u, v0: *const Vector4u, v1: *const Vector4u) -> *mut Vector4u;
	fn tsVector4u_clamp(ret: *mut Vector4u, v: *const Vector4u, v0: *const Vector4u, v1: *const Vector4u) -> *mut Vector4u;
}

/*****************************************************************************\
 *
 * Vector4f
 *
\*****************************************************************************/

/*
 */
#[repr(C, align(16))]
#[derive(Copy, Clone, Default)]
pub struct Vector4f {
	pub x: f32,
	pub y: f32,
	pub z: f32,
	pub w: f32,
}

/*
 */
impl Vector4f {
	
	pub fn new_s(v: f32) -> Vector4f {
		Vector4f { x: v, y: v, z: v, w: v }
	}
	pub fn new_v2(v: &Vector2f, z: f32, w: f32) -> Vector4f {
		Vector4f { x: v.x, y: v.y, z: z, w: w }
	}
	pub fn new_v3(v: &Vector3f, w: f32) -> Vector4f {
		Vector4f { x: v.x, y: v.y, z: v.z, w: w }
	}
	pub fn new_v4i(v: &Vector4i) -> Vector4f {
		Vector4f { x: v.x as f32, y: v.y as f32, z: v.z as f32, w: v.w as f32 }
	}
	pub fn new_v4u(v: &Vector4u) -> Vector4f {
		Vector4f { x: v.x as f32, y: v.y as f32, z: v.z as f32, w: v.w as f32 }
	}
	pub fn new_v4d(v: &Vector4d) -> Vector4f {
		Vector4f { x: v.x as f32, y: v.y as f32, z: v.z as f32, w: v.w as f32 }
	}
	pub fn new(x: f32, y: f32, z: f32, w: f32) -> Vector4f {
		Vector4f { x: x, y: y, z: z, w: w }
	}
	pub fn new_a(v: &[f32]) -> Vector4f {
		Vector4f { x: v[0], y: v[1], z: v[2], w: v[3] }
	}
	
	pub fn abs(&self) -> Vector4f {
		let mut ret = Vector4f::default();
		unsafe { tsVector4f_abs(&mut ret, self); }
		ret
	}
	
	pub fn min(v0: &Vector4f, v1: &Vector4f) -> Vector4f {
		let mut ret = Vector4f::default();
		unsafe { tsVector4f_min(&mut ret, v0, v1); }
		ret
	}
	pub fn max(v0: &Vector4f, v1: &Vector4f) -> Vector4f {
		let mut ret = Vector4f::default();
		unsafe { tsVector4f_max(&mut ret, v0, v1); }
		ret
	}
	pub fn clamp(&self, v0: &Vector4f, v1: &Vector4f) -> Vector4f {
		let mut ret = Vector4f::default();
		unsafe { tsVector4f_clamp(&mut ret, self, v0, v1); }
		ret
	}
	pub fn saturate(&self) -> Vector4f {
		let mut ret = Vector4f::default();
		unsafe { tsVector4f_saturate(&mut ret, self); }
		ret
	}
	
	pub fn dot(v0: &Vector4f, v1: &Vector4f) -> f32 {
		unsafe { tsVector4f_dot(v0, v1) }
	}
	pub fn dot33(v0: &Vector4f, v1: &Vector4f) -> f32 {
		unsafe { tsVector4f_dot33(v0, v1) }
	}
	pub fn dot43(v0: &Vector4f, v1: &Vector4f) -> f32 {
		unsafe { tsVector4f_dot43(v0, v1) }
	}
	pub fn dot34(v0: &Vector4f, v1: &Vector4f) -> f32 {
		unsafe { tsVector4f_dot34(v0, v1) }
	}
	pub fn cross(v0: &Vector4f, v1: &Vector4f) -> Vector4f {
		let mut ret = Vector4f::default();
		unsafe { tsVector4f_cross(&mut ret, v0, v1); }
		ret
	}
	
	pub fn length(&self) -> f32 {
		unsafe { tsVector4f_length(self) }
	}
	pub fn length3(&self) -> f32 {
		unsafe { tsVector4f_length3(self) }
	}
	pub fn normalize(&self) -> Vector4f {
		let mut ret = Vector4f::default();
		unsafe { tsVector4f_normalize(&mut ret, self); }
		ret
	}
	pub fn normalize3(&self) -> Vector4f {
		let mut ret = Vector4f::default();
		unsafe { tsVector4f_normalize3(&mut ret, self); }
		ret
	}
	
	pub fn lerp(v0: &Vector4f, v1: &Vector4f, k: f32) -> Vector4f {
		let mut ret = Vector4f::default();
		unsafe { tsVector4f_lerp(&mut ret, v0, v1, k); }
		ret
	}
	
	pub fn zero() -> Vector4f {
		Vector4f { x: 0.0, y: 0.0, z: 0.0, w: 0.0 }
	}
	pub fn one() -> Vector4f {
		Vector4f { x: 1.0, y: 1.0, z: 1.0, w: 1.0 }
	}
}

/*
 */
impl fmt::Display for Vector4f {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "({0} {1} {2} {3})", self.x, self.y, self.z, self.w)
	}
}

/*
 */
declare_neg_op!(Vector4f, tsVector4f_neg);

/*
 */
declare_scalar_op!(Vector4f, f32, Mul, mul, tsVector4f_mul1);
declare_scalar_op!(Vector4f, f32, Div, div, tsVector4f_div1);
declare_scalar_op!(Vector4f, f32, Add, add, tsVector4f_add1);
declare_scalar_op!(Vector4f, f32, Sub, sub, tsVector4f_sub1);

/*
 */
declare_vector_op!(Vector4f, Mul, mul, tsVector4f_mul);
declare_vector_op!(Vector4f, Div, div, tsVector4f_div);
declare_vector_op!(Vector4f, Add, add, tsVector4f_add);
declare_vector_op!(Vector4f, Sub, sub, tsVector4f_sub);

/*
 */
extern "C" {
	fn tsVector4f_abs(ret: *mut Vector4f, v: *const Vector4f) -> *mut Vector4f;
	fn tsVector4f_neg(ret: *mut Vector4f, v: *const Vector4f) -> *mut Vector4f;
	fn tsVector4f_mul1(ret: *mut Vector4f, v0: *const Vector4f, v1: f32) -> *mut Vector4f;
	fn tsVector4f_div1(ret: *mut Vector4f, v0: *const Vector4f, v1: f32) -> *mut Vector4f;
	fn tsVector4f_add1(ret: *mut Vector4f, v0: *const Vector4f, v1: f32) -> *mut Vector4f;
	fn tsVector4f_sub1(ret: *mut Vector4f, v0: *const Vector4f, v1: f32) -> *mut Vector4f;
	fn tsVector4f_mul(ret: *mut Vector4f, v0: *const Vector4f, v1: *const Vector4f) -> *mut Vector4f;
	fn tsVector4f_div(ret: *mut Vector4f, v0: *const Vector4f, v1: *const Vector4f) -> *mut Vector4f;
	fn tsVector4f_add(ret: *mut Vector4f, v0: *const Vector4f, v1: *const Vector4f) -> *mut Vector4f;
	fn tsVector4f_sub(ret: *mut Vector4f, v0: *const Vector4f, v1: *const Vector4f) -> *mut Vector4f;
	fn tsVector4f_min(ret: *mut Vector4f, v0: *const Vector4f, v1: *const Vector4f) -> *mut Vector4f;
	fn tsVector4f_max(ret: *mut Vector4f, v0: *const Vector4f, v1: *const Vector4f) -> *mut Vector4f;
	fn tsVector4f_clamp(ret: *mut Vector4f, v: *const Vector4f, v0: *const Vector4f, v1: *const Vector4f) -> *mut Vector4f;
	fn tsVector4f_saturate(ret: *mut Vector4f, v: *const Vector4f) -> *mut Vector4f;
	fn tsVector4f_dot(v0: *const Vector4f, v1: *const Vector4f) -> f32;
	fn tsVector4f_dot33(v0: *const Vector4f, v1: *const Vector4f) -> f32;
	fn tsVector4f_dot43(v0: *const Vector4f, v1: *const Vector4f) -> f32;
	fn tsVector4f_dot34(v0: *const Vector4f, v1: *const Vector4f) -> f32;
	fn tsVector4f_cross(ret: *mut Vector4f, v0: *const Vector4f, v1: *const Vector4f) -> *mut Vector4f;
	fn tsVector4f_length(v: *const Vector4f) -> f32;
	fn tsVector4f_length3(v: *const Vector4f) -> f32;
	fn tsVector4f_normalize(ret: *mut Vector4f, v: *const Vector4f) -> *mut Vector4f;
	fn tsVector4f_normalize3(ret: *mut Vector4f, v: *const Vector4f) -> *mut Vector4f;
	fn tsVector4f_lerp(ret: *mut Vector4f, v0: *const Vector4f, v1: *const Vector4f, k: f32) -> *mut Vector4f;
}

/*****************************************************************************\
 *
 * Vector4d
 *
\*****************************************************************************/

/*
 */
#[repr(C, align(16))]
#[derive(Copy, Clone, Default)]
pub struct Vector4d {
	pub x: f64,
	pub y: f64,
	pub z: f64,
	pub w: f64,
}

/*
 */
impl Vector4d {
	
	pub fn new_s(v: f64) -> Vector4d {
		Vector4d { x: v, y: v, z: v, w: v }
	}
	pub fn new_v2(v: &Vector2d, z: f64, w: f64) -> Vector4d {
		Vector4d { x: v.x, y: v.y, z: z, w: w }
	}
	pub fn new_v3(v: &Vector3d, w: f64) -> Vector4d {
		Vector4d { x: v.x, y: v.y, z: v.z, w: w }
	}
	pub fn new_v4i(v: &Vector4i) -> Vector4d {
		Vector4d { x: v.x as f64, y: v.y as f64, z: v.z as f64, w: v.w as f64 }
	}
	pub fn new_v4u(v: &Vector4u) -> Vector4d {
		Vector4d { x: v.x as f64, y: v.y as f64, z: v.z as f64, w: v.w as f64 }
	}
	pub fn new_v4f(v: &Vector4f) -> Vector4d {
		Vector4d { x: v.x as f64, y: v.y as f64, z: v.z as f64, w: v.w as f64 }
	}
	pub fn new(x: f64, y: f64, z: f64, w: f64) -> Vector4d {
		Vector4d { x: x, y: y, z: z, w: w }
	}
	pub fn new_a(v: &[f64]) -> Vector4d {
		Vector4d { x: v[0], y: v[1], z: v[2], w: v[3] }
	}
	
	pub fn abs(&self) -> Vector4d {
		let mut ret = Vector4d::default();
		unsafe { tsVector4d_abs(&mut ret, self); }
		ret
	}
	
	pub fn min(v0: &Vector4d, v1: &Vector4d) -> Vector4d {
		let mut ret = Vector4d::default();
		unsafe { tsVector4d_min(&mut ret, v0, v1); }
		ret
	}
	pub fn max(v0: &Vector4d, v1: &Vector4d) -> Vector4d {
		let mut ret = Vector4d::default();
		unsafe { tsVector4d_max(&mut ret, v0, v1); }
		ret
	}
	pub fn clamp(&self, v0: &Vector4d, v1: &Vector4d) -> Vector4d {
		let mut ret = Vector4d::default();
		unsafe { tsVector4d_clamp(&mut ret, self, v0, v1); }
		ret
	}
	pub fn saturate(&self) -> Vector4d {
		let mut ret = Vector4d::default();
		unsafe { tsVector4d_saturate(&mut ret, self); }
		ret
	}
	
	pub fn dot(v0: &Vector4d, v1: &Vector4d) -> f64 {
		unsafe { tsVector4d_dot(v0, v1) }
	}
	pub fn dot33(v0: &Vector4d, v1: &Vector4d) -> f64 {
		unsafe { tsVector4d_dot33(v0, v1) }
	}
	pub fn dot43(v0: &Vector4d, v1: &Vector4d) -> f64 {
		unsafe { tsVector4d_dot43(v0, v1) }
	}
	pub fn dot34(v0: &Vector4d, v1: &Vector4d) -> f64 {
		unsafe { tsVector4d_dot34(v0, v1) }
	}
	pub fn cross(v0: &Vector4d, v1: &Vector4d) -> Vector4d {
		let mut ret = Vector4d::default();
		unsafe { tsVector4d_cross(&mut ret, v0, v1); }
		ret
	}
	
	pub fn length(&self) -> f64 {
		unsafe { tsVector4d_length(self) }
	}
	pub fn length3(&self) -> f64 {
		unsafe { tsVector4d_length3(self) }
	}
	pub fn normalize(&self) -> Vector4d {
		let mut ret = Vector4d::default();
		unsafe { tsVector4d_normalize(&mut ret, self); }
		ret
	}
	pub fn normalize3(&self) -> Vector4d {
		let mut ret = Vector4d::default();
		unsafe { tsVector4d_normalize3(&mut ret, self); }
		ret
	}
	
	pub fn lerp(v0: &Vector4d, v1: &Vector4d, k: f64) -> Vector4d {
		let mut ret = Vector4d::default();
		unsafe { tsVector4d_lerp(&mut ret, v0, v1, k); }
		ret
	}
	
	pub fn zero() -> Vector4d {
		Vector4d { x: 0.0, y: 0.0, z: 0.0, w: 0.0 }
	}
	pub fn one() -> Vector4d {
		Vector4d { x: 1.0, y: 1.0, z: 1.0, w: 1.0 }
	}
}

/*
 */
impl fmt::Display for Vector4d {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "({0} {1} {2} {3})", self.x, self.y, self.z, self.w)
	}
}

/*
 */
declare_neg_op!(Vector4d, tsVector4d_neg);

/*
 */
declare_scalar_op!(Vector4d, f64, Mul, mul, tsVector4d_mul1);
declare_scalar_op!(Vector4d, f64, Div, div, tsVector4d_div1);
declare_scalar_op!(Vector4d, f64, Add, add, tsVector4d_add1);
declare_scalar_op!(Vector4d, f64, Sub, sub, tsVector4d_sub1);

/*
 */
declare_vector_op!(Vector4d, Mul, mul, tsVector4d_mul);
declare_vector_op!(Vector4d, Div, div, tsVector4d_div);
declare_vector_op!(Vector4d, Add, add, tsVector4d_add);
declare_vector_op!(Vector4d, Sub, sub, tsVector4d_sub);

/*
 */
extern "C" {
	fn tsVector4d_abs(ret: *mut Vector4d, v: *const Vector4d) -> *mut Vector4d;
	fn tsVector4d_neg(ret: *mut Vector4d, v: *const Vector4d) -> *mut Vector4d;
	fn tsVector4d_mul1(ret: *mut Vector4d, v0: *const Vector4d, v1: f64) -> *mut Vector4d;
	fn tsVector4d_div1(ret: *mut Vector4d, v0: *const Vector4d, v1: f64) -> *mut Vector4d;
	fn tsVector4d_add1(ret: *mut Vector4d, v0: *const Vector4d, v1: f64) -> *mut Vector4d;
	fn tsVector4d_sub1(ret: *mut Vector4d, v0: *const Vector4d, v1: f64) -> *mut Vector4d;
	fn tsVector4d_mul(ret: *mut Vector4d, v0: *const Vector4d, v1: *const Vector4d) -> *mut Vector4d;
	fn tsVector4d_div(ret: *mut Vector4d, v0: *const Vector4d, v1: *const Vector4d) -> *mut Vector4d;
	fn tsVector4d_add(ret: *mut Vector4d, v0: *const Vector4d, v1: *const Vector4d) -> *mut Vector4d;
	fn tsVector4d_sub(ret: *mut Vector4d, v0: *const Vector4d, v1: *const Vector4d) -> *mut Vector4d;
	fn tsVector4d_min(ret: *mut Vector4d, v0: *const Vector4d, v1: *const Vector4d) -> *mut Vector4d;
	fn tsVector4d_max(ret: *mut Vector4d, v0: *const Vector4d, v1: *const Vector4d) -> *mut Vector4d;
	fn tsVector4d_clamp(ret: *mut Vector4d, v: *const Vector4d, v0: *const Vector4d, v1: *const Vector4d) -> *mut Vector4d;
	fn tsVector4d_saturate(ret: *mut Vector4d, v: *const Vector4d) -> *mut Vector4d;
	fn tsVector4d_dot(v0: *const Vector4d, v1: *const Vector4d) -> f64;
	fn tsVector4d_dot33(v0: *const Vector4d, v1: *const Vector4d) -> f64;
	fn tsVector4d_dot43(v0: *const Vector4d, v1: *const Vector4d) -> f64;
	fn tsVector4d_dot34(v0: *const Vector4d, v1: *const Vector4d) -> f64;
	fn tsVector4d_cross(ret: *mut Vector4d, v0: *const Vector4d, v1: *const Vector4d) -> *mut Vector4d;
	fn tsVector4d_length(v: *const Vector4d) -> f64;
	fn tsVector4d_length3(v: *const Vector4d) -> f64;
	fn tsVector4d_normalize(ret: *mut Vector4d, v: *const Vector4d) -> *mut Vector4d;
	fn tsVector4d_normalize3(ret: *mut Vector4d, v: *const Vector4d) -> *mut Vector4d;
	fn tsVector4d_lerp(ret: *mut Vector4d, v0: *const Vector4d, v1: *const Vector4d, k: f64) -> *mut Vector4d;
}

/*****************************************************************************\
 *
 * Matrix3x2f
 *
\*****************************************************************************/

/*
 */
#[repr(C)]
#[derive(Copy, Clone)]
pub struct Matrix3x2f {
	pub row_0: Vector3f,
	pub row_1: Vector3f,
}

/*
 */
impl Matrix3x2f {
	
	pub fn new(row_0: &Vector3f, row_1: &Vector3f) -> Matrix3x2f {
		Matrix3x2f { row_0: *row_0, row_1: *row_1 }
	}
	pub fn new_a(src: &[f32]) -> Matrix3x2f {
		let mut ret = Matrix3x2f::default();
		unsafe { tsMatrix3x2f_set(&mut ret, src.as_ptr(), src.len() as u32, 1) }
		ret
	}
	
	pub fn set(&mut self, src: &[f32]) {
		unsafe { tsMatrix3x2f_set(self, src.as_ptr(), src.len() as u32, 1) }
	}
	pub fn set_column_major(&mut self, src: &[f32]) {
		unsafe { tsMatrix3x2f_set(self, src.as_ptr(), src.len() as u32, 0) }
	}
	pub fn get(&self, dest: &mut [f32]) {
		unsafe { tsMatrix3x2f_get(self, dest.as_mut_ptr(), dest.len() as u32, 1) }
	}
	pub fn get_column_major(&self, dest: &mut [f32]) {
		unsafe { tsMatrix3x2f_get(self, dest.as_mut_ptr(), dest.len() as u32, 0) }
	}
	
	pub fn scale_s(s: f32) -> Matrix3x2f {
		let mut ret = Matrix3x2f::default();
		unsafe { tsMatrix3x2f_scale(&mut ret, s, s); }
		ret
	}
	pub fn scale(x: f32, y: f32) -> Matrix3x2f {
		let mut ret = Matrix3x2f::default();
		unsafe { tsMatrix3x2f_scale(&mut ret, x, y); }
		ret
	}
	pub fn translate(x: f32, y: f32) -> Matrix3x2f {
		let mut ret = Matrix3x2f::default();
		unsafe { tsMatrix3x2f_translate(&mut ret, x, y); }
		ret
	}
	pub fn rotate(angle: f32) -> Matrix3x2f {
		let mut ret = Matrix3x2f::default();
		unsafe { tsMatrix3x2f_rotate(&mut ret, angle); }
		ret
	}
	
	pub fn transpose(&self) -> Matrix3x2f {
		let mut ret = Matrix3x2f::default();
		unsafe { tsMatrix3x2f_transpose(&mut ret, self); }
		ret
	}
	pub fn inverse(&self) -> Matrix3x2f {
		let mut ret = Matrix3x2f::default();
		unsafe { tsMatrix3x2f_inverse(&mut ret, self); }
		ret
	}
	
	pub fn identity() -> Matrix3x2f {
		Matrix3x2f { row_0: Vector3f::new(1.0, 0.0, 0.0), row_1: Vector3f::new(0.0, 1.0, 0.0) }
	}
}

/*
 */
impl Default for Matrix3x2f {
	fn default() -> Matrix3x2f {
		Matrix3x2f::identity()
	}
}

/*
 */
impl fmt::Display for Matrix3x2f {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "{0} : {1}", self.row_0, self.row_1)
	}
}

/*
 */
declare_op!(Matrix3x2f, Vector2f, Vector2f, Mul, mul, tsMatrix3x2f_mul2);
declare_op!(Vector2f, Matrix3x2f, Vector2f, Mul, mul, tsMatrix3x2f_mul2t);
declare_vector_op!(Matrix3x2f, Mul, mul, tsMatrix3x2f_mul);

/*
 */
extern "C" {
	fn tsMatrix3x2f_set(m: *mut Matrix3x2f, src: *const f32, size: u32, row_major: i32);
	fn tsMatrix3x2f_get(m: *const Matrix3x2f, dest: *mut f32, size: u32, row_major: i32);
	fn tsMatrix3x2f_scale(ret: *mut Matrix3x2f, x: f32, y: f32) -> *mut Matrix3x2f;
	fn tsMatrix3x2f_translate(ret: *mut Matrix3x2f, x: f32, y: f32) -> *mut Matrix3x2f;
	fn tsMatrix3x2f_rotate(ret: *mut Matrix3x2f, angle: f32) -> *mut Matrix3x2f;
	fn tsMatrix3x2f_mul2(ret: *mut Vector2f, q: *const Matrix3x2f, v: *const Vector2f) -> *mut Matrix3x2f;
	fn tsMatrix3x2f_mul2t(ret: *mut Vector2f, v: *const Vector2f, q: *const Matrix3x2f) -> *mut Matrix3x2f;
	fn tsMatrix3x2f_mul(ret: *mut Matrix3x2f, v0: *const Matrix3x2f, v1: *const Matrix3x2f) -> *mut Matrix3x2f;
	fn tsMatrix3x2f_transpose(ret: *mut Matrix3x2f, v: *const Matrix3x2f) -> *mut Matrix3x2f;
	fn tsMatrix3x2f_inverse(ret: *mut Matrix3x2f, v: *const Matrix3x2f) -> *mut Matrix3x2f;
}

/*****************************************************************************\
 *
 * Matrix3x2d
 *
\*****************************************************************************/

/*
 */
#[repr(C)]
#[derive(Copy, Clone)]
pub struct Matrix3x2d {
	pub row_0: Vector3d,
	pub row_1: Vector3d,
}

/*
 */
impl Matrix3x2d {
	
	pub fn new(row_0: &Vector3d, row_1: &Vector3d) -> Matrix3x2d {
		Matrix3x2d { row_0: *row_0, row_1: *row_1 }
	}
	pub fn new_a(src: &[f64]) -> Matrix3x2d {
		let mut ret = Matrix3x2d::default();
		unsafe { tsMatrix3x2d_set(&mut ret, src.as_ptr(), src.len() as u32, 1) }
		ret
	}
	
	pub fn set(&mut self, src: &[f64]) {
		unsafe { tsMatrix3x2d_set(self, src.as_ptr(), src.len() as u32, 1) }
	}
	pub fn set_column_major(&mut self, src: &[f64]) {
		unsafe { tsMatrix3x2d_set(self, src.as_ptr(), src.len() as u32, 0) }
	}
	pub fn get(&self, dest: &mut [f64]) {
		unsafe { tsMatrix3x2d_get(self, dest.as_mut_ptr(), dest.len() as u32, 1) }
	}
	pub fn get_column_major(&self, dest: &mut [f64]) {
		unsafe { tsMatrix3x2d_get(self, dest.as_mut_ptr(), dest.len() as u32, 0) }
	}
	
	pub fn scale_s(s: f64) -> Matrix3x2d {
		let mut ret = Matrix3x2d::default();
		unsafe { tsMatrix3x2d_scale(&mut ret, s, s); }
		ret
	}
	pub fn scale(x: f64, y: f64) -> Matrix3x2d {
		let mut ret = Matrix3x2d::default();
		unsafe { tsMatrix3x2d_scale(&mut ret, x, y); }
		ret
	}
	pub fn translate(x: f64, y: f64) -> Matrix3x2d {
		let mut ret = Matrix3x2d::default();
		unsafe { tsMatrix3x2d_translate(&mut ret, x, y); }
		ret
	}
	pub fn rotate(angle: f64) -> Matrix3x2d {
		let mut ret = Matrix3x2d::default();
		unsafe { tsMatrix3x2d_rotate(&mut ret, angle); }
		ret
	}
	
	pub fn transpose(&self) -> Matrix3x2d {
		let mut ret = Matrix3x2d::default();
		unsafe { tsMatrix3x2d_transpose(&mut ret, self); }
		ret
	}
	pub fn inverse(&self) -> Matrix3x2d {
		let mut ret = Matrix3x2d::default();
		unsafe { tsMatrix3x2d_inverse(&mut ret, self); }
		ret
	}
	
	pub fn identity() -> Matrix3x2d {
		Matrix3x2d { row_0: Vector3d::new(1.0, 0.0, 0.0), row_1: Vector3d::new(0.0, 1.0, 0.0) }
	}
}

/*
 */
impl Default for Matrix3x2d {
	fn default() -> Matrix3x2d {
		Matrix3x2d::identity()
	}
}

/*
 */
impl fmt::Display for Matrix3x2d {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "{0} : {1}", self.row_0, self.row_1)
	}
}

/*
 */
declare_op!(Matrix3x2d, Vector2d, Vector2d, Mul, mul, tsMatrix3x2d_mul2);
declare_op!(Vector2d, Matrix3x2d, Vector2d, Mul, mul, tsMatrix3x2d_mul2t);
declare_vector_op!(Matrix3x2d, Mul, mul, tsMatrix3x2d_mul);

/*
 */
extern "C" {
	fn tsMatrix3x2d_set(m: *mut Matrix3x2d, src: *const f64, size: u32, row_major: i32);
	fn tsMatrix3x2d_get(m: *const Matrix3x2d, dest: *mut f64, size: u32, row_major: i32);
	fn tsMatrix3x2d_scale(ret: *mut Matrix3x2d, x: f64, y: f64) -> *mut Matrix3x2d;
	fn tsMatrix3x2d_translate(ret: *mut Matrix3x2d, x: f64, y: f64) -> *mut Matrix3x2d;
	fn tsMatrix3x2d_rotate(ret: *mut Matrix3x2d, angle: f64) -> *mut Matrix3x2d;
	fn tsMatrix3x2d_mul2(ret: *mut Vector2d, q: *const Matrix3x2d, v: *const Vector2d) -> *mut Matrix3x2d;
	fn tsMatrix3x2d_mul2t(ret: *mut Vector2d, v: *const Vector2d, q: *const Matrix3x2d) -> *mut Matrix3x2d;
	fn tsMatrix3x2d_mul(ret: *mut Matrix3x2d, v0: *const Matrix3x2d, v1: *const Matrix3x2d) -> *mut Matrix3x2d;
	fn tsMatrix3x2d_transpose(ret: *mut Matrix3x2d, v: *const Matrix3x2d) -> *mut Matrix3x2d;
	fn tsMatrix3x2d_inverse(ret: *mut Matrix3x2d, v: *const Matrix3x2d) -> *mut Matrix3x2d;
}

/*****************************************************************************\
 *
 * Matrix4x3f
 *
\*****************************************************************************/

/*
 */
#[repr(C, align(16))]
#[derive(Copy, Clone)]
pub struct Matrix4x3f {
	pub row_0: Vector4f,
	pub row_1: Vector4f,
	pub row_2: Vector4f,
}

/*
 */
impl Matrix4x3f {
	
	pub fn new(row_0: &Vector4f, row_1: &Vector4f, row_2: &Vector4f) -> Matrix4x3f {
		Matrix4x3f { row_0: *row_0, row_1: *row_1, row_2: *row_2 }
	}
	pub fn new_m4x3d(m: &Matrix4x3d) -> Matrix4x3f {
		Matrix4x3f { row_0: Vector4f::new_v4d(&m.row_0), row_1: Vector4f::new_v4d(&m.row_1), row_2: Vector4f::new_v4d(&m.row_2) }
	}
	pub fn new_m4x4(m: &Matrix4x4f) -> Matrix4x3f {
		Matrix4x3f { row_0: m.row_0, row_1: m.row_1, row_2: m.row_2 }
	}
	pub fn new_q(q: &Quaternionf) -> Matrix4x3f {
		let mut ret = Matrix4x3f::default();
		unsafe { tsQuaternionf_get(q, &mut ret.row_0, &mut ret.row_1, &mut ret.row_2) }
		ret
	}
	pub fn new_a(src: &[f32]) -> Matrix4x3f {
		let mut ret = Matrix4x3f::default();
		unsafe { tsMatrix4x3f_set(&mut ret, src.as_ptr(), src.len() as u32, 1) }
		ret
	}
	
	pub fn set(&mut self, src: &[f32]) {
		unsafe { tsMatrix4x3f_set(self, src.as_ptr(), src.len() as u32, 1) }
	}
	pub fn set_column_major(&mut self, src: &[f32]) {
		unsafe { tsMatrix4x3f_set(self, src.as_ptr(), src.len() as u32, 0) }
	}
	pub fn set_q(&mut self, q: &Quaternionf) {
		unsafe { tsQuaternionf_get(q, &mut self.row_0, &mut self.row_1, &mut self.row_2) }
	}
	pub fn get(&self, dest: &mut [f32]) {
		unsafe { tsMatrix4x3f_get(self, dest.as_mut_ptr(), dest.len() as u32, 1) }
	}
	pub fn get_column_major(&self, dest: &mut [f32]) {
		unsafe { tsMatrix4x3f_get(self, dest.as_mut_ptr(), dest.len() as u32, 0) }
	}
	pub fn get_q(&self, q: &mut Quaternionf) {
		unsafe { tsQuaternionf_set(q, &self.row_0, &self.row_1, &self.row_2) }
	}
	
	pub fn scale_s(s: f32) -> Matrix4x3f {
		let mut ret = Matrix4x3f::default();
		unsafe { tsMatrix4x3f_scale(&mut ret, s, s, s); }
		ret
	}
	pub fn scale(x: f32, y: f32, z: f32) -> Matrix4x3f {
		let mut ret = Matrix4x3f::default();
		unsafe { tsMatrix4x3f_scale(&mut ret, x, y, z); }
		ret
	}
	pub fn scale_v3(v: &Vector3f) -> Matrix4x3f {
		let mut ret = Matrix4x3f::default();
		unsafe { tsMatrix4x3f_scale(&mut ret, v.x, v.y, v.z); }
		ret
	}
	pub fn translate(x: f32, y: f32, z: f32) -> Matrix4x3f {
		let mut ret = Matrix4x3f::default();
		unsafe { tsMatrix4x3f_translate(&mut ret, x, y, z); }
		ret
	}
	pub fn translate_v3(v: &Vector3f) -> Matrix4x3f {
		let mut ret = Matrix4x3f::default();
		unsafe { tsMatrix4x3f_translate(&mut ret, v.x, v.y, v.z); }
		ret
	}
	pub fn rotate_x(angle: f32) -> Matrix4x3f {
		let mut ret = Matrix4x3f::default();
		unsafe { tsMatrix4x3f_rotateX(&mut ret, angle); }
		ret
	}
	pub fn rotate_y(angle: f32) -> Matrix4x3f {
		let mut ret = Matrix4x3f::default();
		unsafe { tsMatrix4x3f_rotateY(&mut ret, angle); }
		ret
	}
	pub fn rotate_z(angle: f32) -> Matrix4x3f {
		let mut ret = Matrix4x3f::default();
		unsafe { tsMatrix4x3f_rotateZ(&mut ret, angle); }
		ret
	}
	pub fn rotate(axis: &Vector3f, angle: f32) -> Matrix4x3f {
		let mut ret = Matrix4x3f::default();
		unsafe { tsMatrix4x3f_rotate(&mut ret, axis, angle); }
		ret
	}
	
	pub fn look_at(from: &Vector3f, to: &Vector3f, up: &Vector3f) -> Matrix4x3f {
		let mut ret = Matrix4x3f::default();
		unsafe { tsMatrix4x3f_lookAt(&mut ret, from, to, up); }
		ret
	}
	pub fn place_to(to: &Vector3f, from: &Vector3f, up: &Vector3f) -> Matrix4x3f {
		let mut ret = Matrix4x3f::default();
		unsafe { tsMatrix4x3f_placeTo(&mut ret, to, from, up); }
		ret
	}
	pub fn compose(t: &Vector3f, r: &Quaternionf, s: &Vector3f) -> Matrix4x3f {
		let mut ret = Matrix4x3f::default();
		unsafe { tsMatrix4x3f_compose(&mut ret, t, r, s); }
		ret
	}
	pub fn basis(normal: &Vector3f, t: &Vector3f) -> Matrix4x3f {
		let mut ret = Matrix4x3f::default();
		unsafe { tsMatrix4x3f_basis(&mut ret, normal, t); }
		ret
	}
	
	pub fn normalize(&self) -> Matrix4x3f {
		let mut ret = Matrix4x3f::default();
		unsafe { tsMatrix4x3f_normalize(&mut ret, self); }
		ret
	}
	pub fn transpose(&self) -> Matrix4x3f {
		let mut ret = Matrix4x3f::default();
		unsafe { tsMatrix4x3f_transpose(&mut ret, self); }
		ret
	}
	pub fn inverse(&self) -> Matrix4x3f {
		let mut ret = Matrix4x3f::default();
		unsafe { tsMatrix4x3f_inverse(&mut ret, self); }
		ret
	}
	pub fn inverse33(&self) -> Matrix4x3f {
		let mut ret = Matrix4x3f::default();
		unsafe { tsMatrix4x3f_inverse33(&mut ret, self); }
		ret
	}
	
	pub fn identity() -> Matrix4x3f {
		Matrix4x3f { row_0: Vector4f::new(1.0, 0.0, 0.0, 0.0), row_1: Vector4f::new(0.0, 1.0, 0.0, 0.0), row_2: Vector4f::new(0.0, 0.0, 1.0, 0.0) }
	}
}

/*
 */
impl Default for Matrix4x3f {
	fn default() -> Matrix4x3f {
		Matrix4x3f::identity()
	}
}

/*
 */
impl fmt::Display for Matrix4x3f {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "{0} : {1} : {2}", self.row_0, self.row_1, self.row_2)
	}
}

/*
 */
declare_op!(Matrix4x3f, Vector2f, Vector2f, Mul, mul, tsMatrix4x3f_mul2);
declare_op!(Matrix4x3f, Vector3f, Vector3f, Mul, mul, tsMatrix4x3f_mul3);
declare_op!(Matrix4x3f, Vector4f, Vector4f, Mul, mul, tsMatrix4x3f_mul4);
declare_op!(Matrix4x3f, BoundRectf, BoundRectf, Mul, mul, tsMatrix4x3f_mul_br);
declare_op!(Matrix4x3f, BoundCirclef, BoundCirclef, Mul, mul, tsMatrix4x3f_mul_bc);
declare_op!(Matrix4x3f, BoundBoxf, BoundBoxf, Mul, mul, tsMatrix4x3f_mul_bb);
declare_op!(Matrix4x3f, BoundSpheref, BoundSpheref, Mul, mul, tsMatrix4x3f_mul_bs);
declare_op!(Vector2f, Matrix4x3f, Vector2f, Mul, mul, tsMatrix4x3f_mul2t);
declare_op!(Vector3f, Matrix4x3f, Vector3f, Mul, mul, tsMatrix4x3f_mul3t);
declare_op!(Vector4f, Matrix4x3f, Vector4f, Mul, mul, tsMatrix4x3f_mul4t);
declare_vector_op!(Matrix4x3f, Mul, mul, tsMatrix4x3f_mul);

/*
 */
extern "C" {
	fn tsMatrix4x3f_set(m: *mut Matrix4x3f, src: *const f32, size: u32, row_major: i32);
	fn tsMatrix4x3f_get(m: *const Matrix4x3f, dest: *mut f32, size: u32, row_major: i32);
	fn tsMatrix4x3f_scale(ret: *mut Matrix4x3f, x: f32, y: f32, z: f32) -> *mut Matrix4x3f;
	fn tsMatrix4x3f_translate(ret: *mut Matrix4x3f, x: f32, y: f32, z: f32) -> *mut Matrix4x3f;
	fn tsMatrix4x3f_rotateX(ret: *mut Matrix4x3f, angle: f32) -> *mut Matrix4x3f;
	fn tsMatrix4x3f_rotateY(ret: *mut Matrix4x3f, angle: f32) -> *mut Matrix4x3f;
	fn tsMatrix4x3f_rotateZ(ret: *mut Matrix4x3f, angle: f32) -> *mut Matrix4x3f;
	fn tsMatrix4x3f_rotate(ret: *mut Matrix4x3f, axis: *const Vector3f, angle: f32) -> *mut Matrix4x3f;
	fn tsMatrix4x3f_lookAt(ret: *mut Matrix4x3f, from: *const Vector3f, to: *const Vector3f, up: *const Vector3f) -> *mut Matrix4x3f;
	fn tsMatrix4x3f_placeTo(ret: *mut Matrix4x3f, to: *const Vector3f, from: *const Vector3f, up: *const Vector3f) -> *mut Matrix4x3f;
	fn tsMatrix4x3f_compose(ret: *mut Matrix4x3f, t: *const Vector3f, r: *const Quaternionf, s: *const Vector3f) -> *mut Matrix4x3f;
	fn tsMatrix4x3f_basis(ret: *mut Matrix4x3f, normal: *const Vector3f, t: *const Vector3f) -> *mut Matrix4x3f;
	fn tsMatrix4x3f_mul2(ret: *mut Vector2f, m: *const Matrix4x3f, v: *const Vector2f) -> *mut Matrix4x3f;
	fn tsMatrix4x3f_mul3(ret: *mut Vector3f, m: *const Matrix4x3f, v: *const Vector3f) -> *mut Matrix4x3f;
	fn tsMatrix4x3f_mul4(ret: *mut Vector4f, m: *const Matrix4x3f, v: *const Vector4f) -> *mut Matrix4x3f;
	fn tsMatrix4x3f_mul_br(ret: *mut BoundRectf, m: *const Matrix4x3f, r: *const BoundRectf) -> *mut BoundRectf;
	fn tsMatrix4x3f_mul_bc(ret: *mut BoundCirclef, m: *const Matrix4x3f, c: *const BoundCirclef) -> *mut BoundCirclef;
	fn tsMatrix4x3f_mul_bb(ret: *mut BoundBoxf, m: *const Matrix4x3f, b: *const BoundBoxf) -> *mut BoundBoxf;
	fn tsMatrix4x3f_mul_bs(ret: *mut BoundSpheref, m: *const Matrix4x3f, s: *const BoundSpheref) -> *mut BoundSpheref;
	fn tsMatrix4x3f_mul2t(ret: *mut Vector2f, v: *const Vector2f, m: *const Matrix4x3f) -> *mut Matrix4x3f;
	fn tsMatrix4x3f_mul3t(ret: *mut Vector3f, v: *const Vector3f, m: *const Matrix4x3f) -> *mut Matrix4x3f;
	fn tsMatrix4x3f_mul4t(ret: *mut Vector4f, v: *const Vector4f, m: *const Matrix4x3f) -> *mut Matrix4x3f;
	fn tsMatrix4x3f_mul(ret: *mut Matrix4x3f, v0: *const Matrix4x3f, v1: *const Matrix4x3f) -> *mut Matrix4x3f;
	fn tsMatrix4x3f_normalize(ret: *mut Matrix4x3f, v: *const Matrix4x3f) -> *mut Matrix4x3f;
	fn tsMatrix4x3f_transpose(ret: *mut Matrix4x3f, v: *const Matrix4x3f) -> *mut Matrix4x3f;
	fn tsMatrix4x3f_inverse(ret: *mut Matrix4x3f, v: *const Matrix4x3f) -> *mut Matrix4x3f;
	fn tsMatrix4x3f_inverse33(ret: *mut Matrix4x3f, v: *const Matrix4x3f) -> *mut Matrix4x3f;
	fn tsMatrix4x3f_lerp(ret: *mut Matrix4x3f, v0: *const Matrix4x3f, v1: *const Matrix4x3f, k: f32) -> *mut Matrix4x3f;
}

/*****************************************************************************\
 *
 * Matrix4x3d
 *
\*****************************************************************************/

/*
 */
#[repr(C, align(16))]
#[derive(Copy, Clone)]
pub struct Matrix4x3d {
	pub row_0: Vector4d,
	pub row_1: Vector4d,
	pub row_2: Vector4d,
}

/*
 */
impl Matrix4x3d {
	
	pub fn new(row_0: &Vector4d, row_1: &Vector4d, row_2: &Vector4d) -> Matrix4x3d {
		Matrix4x3d { row_0: *row_0, row_1: *row_1, row_2: *row_2 }
	}
	pub fn new_m4x3f(m: &Matrix4x3f) -> Matrix4x3d {
		Matrix4x3d { row_0: Vector4d::new_v4f(&m.row_0), row_1: Vector4d::new_v4f(&m.row_1), row_2: Vector4d::new_v4f(&m.row_2) }
	}
	pub fn new_m4x4(m: &Matrix4x4d) -> Matrix4x3d {
		Matrix4x3d { row_0: m.row_0, row_1: m.row_1, row_2: m.row_2 }
	}
	pub fn new_q(q: &Quaterniond) -> Matrix4x3d {
		let mut ret = Matrix4x3d::default();
		unsafe { tsQuaterniond_get(q, &mut ret.row_0, &mut ret.row_1, &mut ret.row_2) }
		ret
	}
	pub fn new_a(src: &[f64]) -> Matrix4x3d {
		let mut ret = Matrix4x3d::default();
		unsafe { tsMatrix4x3d_set(&mut ret, src.as_ptr(), src.len() as u32, 1) }
		ret
	}
	
	pub fn set(&mut self, src: &[f64]) {
		unsafe { tsMatrix4x3d_set(self, src.as_ptr(), src.len() as u32, 1) }
	}
	pub fn set_column_major(&mut self, src: &[f64]) {
		unsafe { tsMatrix4x3d_set(self, src.as_ptr(), src.len() as u32, 0) }
	}
	pub fn set_q(&mut self, q: &Quaterniond) {
		unsafe { tsQuaterniond_get(q, &mut self.row_0, &mut self.row_1, &mut self.row_2) }
	}
	pub fn get(&self, dest: &mut [f64]) {
		unsafe { tsMatrix4x3d_get(self, dest.as_mut_ptr(), dest.len() as u32, 1) }
	}
	pub fn get_column_major(&self, dest: &mut [f64]) {
		unsafe { tsMatrix4x3d_get(self, dest.as_mut_ptr(), dest.len() as u32, 0) }
	}
	pub fn get_q(&self, q: &mut Quaterniond) {
		unsafe { tsQuaterniond_set(q, &self.row_0, &self.row_1, &self.row_2) }
	}
	
	pub fn scale_s(s: f64) -> Matrix4x3d {
		let mut ret = Matrix4x3d::default();
		unsafe { tsMatrix4x3d_scale(&mut ret, s, s, s); }
		ret
	}
	pub fn scale(x: f64, y: f64, z: f64) -> Matrix4x3d {
		let mut ret = Matrix4x3d::default();
		unsafe { tsMatrix4x3d_scale(&mut ret, x, y, z); }
		ret
	}
	pub fn scale_v3(v: &Vector3d) -> Matrix4x3d {
		let mut ret = Matrix4x3d::default();
		unsafe { tsMatrix4x3d_scale(&mut ret, v.x, v.y, v.z); }
		ret
	}
	pub fn translate(x: f64, y: f64, z: f64) -> Matrix4x3d {
		let mut ret = Matrix4x3d::default();
		unsafe { tsMatrix4x3d_translate(&mut ret, x, y, z); }
		ret
	}
	pub fn translate_v3(v: &Vector3d) -> Matrix4x3d {
		let mut ret = Matrix4x3d::default();
		unsafe { tsMatrix4x3d_translate(&mut ret, v.x, v.y, v.z); }
		ret
	}
	pub fn rotate_x(angle: f64) -> Matrix4x3d {
		let mut ret = Matrix4x3d::default();
		unsafe { tsMatrix4x3d_rotateX(&mut ret, angle); }
		ret
	}
	pub fn rotate_y(angle: f64) -> Matrix4x3d {
		let mut ret = Matrix4x3d::default();
		unsafe { tsMatrix4x3d_rotateY(&mut ret, angle); }
		ret
	}
	pub fn rotate_z(angle: f64) -> Matrix4x3d {
		let mut ret = Matrix4x3d::default();
		unsafe { tsMatrix4x3d_rotateZ(&mut ret, angle); }
		ret
	}
	pub fn rotate(axis: &Vector3d, angle: f64) -> Matrix4x3d {
		let mut ret = Matrix4x3d::default();
		unsafe { tsMatrix4x3d_rotate(&mut ret, axis, angle); }
		ret
	}
	
	pub fn look_at(from: &Vector3d, to: &Vector3d, up: &Vector3d) -> Matrix4x3d {
		let mut ret = Matrix4x3d::default();
		unsafe { tsMatrix4x3d_lookAt(&mut ret, from, to, up); }
		ret
	}
	pub fn place_to(to: &Vector3d, from: &Vector3d, up: &Vector3d) -> Matrix4x3d {
		let mut ret = Matrix4x3d::default();
		unsafe { tsMatrix4x3d_placeTo(&mut ret, to, from, up); }
		ret
	}
	pub fn compose(t: &Vector3d, r: &Quaterniond, s: &Vector3d) -> Matrix4x3d {
		let mut ret = Matrix4x3d::default();
		unsafe { tsMatrix4x3d_compose(&mut ret, t, r, s); }
		ret
	}
	pub fn basis(normal: &Vector3d, t: &Vector3d) -> Matrix4x3d {
		let mut ret = Matrix4x3d::default();
		unsafe { tsMatrix4x3d_basis(&mut ret, normal, t); }
		ret
	}
	
	pub fn normalize(&self) -> Matrix4x3d {
		let mut ret = Matrix4x3d::default();
		unsafe { tsMatrix4x3d_normalize(&mut ret, self); }
		ret
	}
	pub fn transpose(&self) -> Matrix4x3d {
		let mut ret = Matrix4x3d::default();
		unsafe { tsMatrix4x3d_transpose(&mut ret, self); }
		ret
	}
	pub fn inverse(&self) -> Matrix4x3d {
		let mut ret = Matrix4x3d::default();
		unsafe { tsMatrix4x3d_inverse(&mut ret, self); }
		ret
	}
	pub fn inverse33(&self) -> Matrix4x3d {
		let mut ret = Matrix4x3d::default();
		unsafe { tsMatrix4x3d_inverse33(&mut ret, self); }
		ret
	}
	
	pub fn identity() -> Matrix4x3d {
		Matrix4x3d { row_0: Vector4d::new(1.0, 0.0, 0.0, 0.0), row_1: Vector4d::new(0.0, 1.0, 0.0, 0.0), row_2: Vector4d::new(0.0, 0.0, 1.0, 0.0) }
	}
}

/*
 */
impl Default for Matrix4x3d {
	fn default() -> Matrix4x3d {
		Matrix4x3d::identity()
	}
}

/*
 */
impl fmt::Display for Matrix4x3d {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "{0} : {1} : {2}", self.row_0, self.row_1, self.row_2)
	}
}

/*
 */
declare_op!(Matrix4x3d, Vector2d, Vector2d, Mul, mul, tsMatrix4x3d_mul2);
declare_op!(Matrix4x3d, Vector3d, Vector3d, Mul, mul, tsMatrix4x3d_mul3);
declare_op!(Matrix4x3d, Vector4d, Vector4d, Mul, mul, tsMatrix4x3d_mul4);
declare_op!(Matrix4x3d, BoundRectd, BoundRectd, Mul, mul, tsMatrix4x3d_mul_br);
declare_op!(Matrix4x3d, BoundCircled, BoundCircled, Mul, mul, tsMatrix4x3d_mul_bc);
declare_op!(Matrix4x3d, BoundBoxd, BoundBoxd, Mul, mul, tsMatrix4x3d_mul_bb);
declare_op!(Matrix4x3d, BoundSphered, BoundSphered, Mul, mul, tsMatrix4x3d_mul_bs);
declare_op!(Vector2d, Matrix4x3d, Vector2d, Mul, mul, tsMatrix4x3d_mul2t);
declare_op!(Vector3d, Matrix4x3d, Vector3d, Mul, mul, tsMatrix4x3d_mul3t);
declare_op!(Vector4d, Matrix4x3d, Vector4d, Mul, mul, tsMatrix4x3d_mul4t);
declare_vector_op!(Matrix4x3d, Mul, mul, tsMatrix4x3d_mul);

/*
 */
extern "C" {
	fn tsMatrix4x3d_set(m: *mut Matrix4x3d, src: *const f64, size: u32, row_major: i32);
	fn tsMatrix4x3d_get(m: *const Matrix4x3d, dest: *mut f64, size: u32, row_major: i32);
	fn tsMatrix4x3d_scale(ret: *mut Matrix4x3d, x: f64, y: f64, z: f64) -> *mut Matrix4x3d;
	fn tsMatrix4x3d_translate(ret: *mut Matrix4x3d, x: f64, y: f64, z: f64) -> *mut Matrix4x3d;
	fn tsMatrix4x3d_rotateX(ret: *mut Matrix4x3d, angle: f64) -> *mut Matrix4x3d;
	fn tsMatrix4x3d_rotateY(ret: *mut Matrix4x3d, angle: f64) -> *mut Matrix4x3d;
	fn tsMatrix4x3d_rotateZ(ret: *mut Matrix4x3d, angle: f64) -> *mut Matrix4x3d;
	fn tsMatrix4x3d_rotate(ret: *mut Matrix4x3d, axis: *const Vector3d, angle: f64) -> *mut Matrix4x3d;
	fn tsMatrix4x3d_lookAt(ret: *mut Matrix4x3d, from: *const Vector3d, to: *const Vector3d, up: *const Vector3d) -> *mut Matrix4x3d;
	fn tsMatrix4x3d_placeTo(ret: *mut Matrix4x3d, to: *const Vector3d, from: *const Vector3d, up: *const Vector3d) -> *mut Matrix4x3d;
	fn tsMatrix4x3d_compose(ret: *mut Matrix4x3d, t: *const Vector3d, r: *const Quaterniond, s: *const Vector3d) -> *mut Matrix4x3d;
	fn tsMatrix4x3d_basis(ret: *mut Matrix4x3d, normal: *const Vector3d, t: *const Vector3d) -> *mut Matrix4x3d;
	fn tsMatrix4x3d_mul2(ret: *mut Vector2d, m: *const Matrix4x3d, v: *const Vector2d) -> *mut Matrix4x3d;
	fn tsMatrix4x3d_mul3(ret: *mut Vector3d, m: *const Matrix4x3d, v: *const Vector3d) -> *mut Matrix4x3d;
	fn tsMatrix4x3d_mul4(ret: *mut Vector4d, m: *const Matrix4x3d, v: *const Vector4d) -> *mut Matrix4x3d;
	fn tsMatrix4x3d_mul_br(ret: *mut BoundRectd, m: *const Matrix4x3d, r: *const BoundRectd) -> *mut BoundRectd;
	fn tsMatrix4x3d_mul_bc(ret: *mut BoundCircled, m: *const Matrix4x3d, c: *const BoundCircled) -> *mut BoundCircled;
	fn tsMatrix4x3d_mul_bb(ret: *mut BoundBoxd, m: *const Matrix4x3d, b: *const BoundBoxd) -> *mut BoundBoxd;
	fn tsMatrix4x3d_mul_bs(ret: *mut BoundSphered, m: *const Matrix4x3d, s: *const BoundSphered) -> *mut BoundSphered;
	fn tsMatrix4x3d_mul2t(ret: *mut Vector2d, v: *const Vector2d, m: *const Matrix4x3d) -> *mut Matrix4x3d;
	fn tsMatrix4x3d_mul3t(ret: *mut Vector3d, v: *const Vector3d, m: *const Matrix4x3d) -> *mut Matrix4x3d;
	fn tsMatrix4x3d_mul4t(ret: *mut Vector4d, v: *const Vector4d, m: *const Matrix4x3d) -> *mut Matrix4x3d;
	fn tsMatrix4x3d_mul(ret: *mut Matrix4x3d, v0: *const Matrix4x3d, v1: *const Matrix4x3d) -> *mut Matrix4x3d;
	fn tsMatrix4x3d_normalize(ret: *mut Matrix4x3d, v: *const Matrix4x3d) -> *mut Matrix4x3d;
	fn tsMatrix4x3d_transpose(ret: *mut Matrix4x3d, v: *const Matrix4x3d) -> *mut Matrix4x3d;
	fn tsMatrix4x3d_inverse(ret: *mut Matrix4x3d, v: *const Matrix4x3d) -> *mut Matrix4x3d;
	fn tsMatrix4x3d_inverse33(ret: *mut Matrix4x3d, v: *const Matrix4x3d) -> *mut Matrix4x3d;
	fn tsMatrix4x3d_lerp(ret: *mut Matrix4x3d, v0: *const Matrix4x3d, v1: *const Matrix4x3d, k: f64) -> *mut Matrix4x3d;
}

/*****************************************************************************\
 *
 * Matrix4x4f
 *
\*****************************************************************************/

/*
 */
#[repr(C, align(16))]
#[derive(Copy, Clone)]
pub struct Matrix4x4f {
	pub row_0: Vector4f,
	pub row_1: Vector4f,
	pub row_2: Vector4f,
	pub row_3: Vector4f,
}

/*
 */
impl Matrix4x4f {
	
	pub fn new(row_0: &Vector4f, row_1: &Vector4f, row_2: &Vector4f, row_3: &Vector4f) -> Matrix4x4f {
		Matrix4x4f { row_0: *row_0, row_1: *row_1, row_2: *row_2, row_3: *row_3 }
	}
	pub fn new_m4x3(m: &Matrix4x3f) -> Matrix4x4f {
		Matrix4x4f { row_0: m.row_0, row_1: m.row_1, row_2: m.row_2, row_3: Vector4f::new(0.0, 0.0, 0.0, 1.0) }
	}
	pub fn new_m4x4d(m: &Matrix4x4d) -> Matrix4x4f {
		Matrix4x4f { row_0: Vector4f::new_v4d(&m.row_0), row_1: Vector4f::new_v4d(&m.row_1), row_2: Vector4f::new_v4d(&m.row_2), row_3: Vector4f::new_v4d(&m.row_3) }
	}
	pub fn new_q(q: &Quaternionf) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsQuaternionf_get(q, &mut ret.row_0, &mut ret.row_1, &mut ret.row_2) }
		ret
	}
	pub fn new_a(src: &[f32]) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_set(&mut ret, src.as_ptr(), src.len() as u32, 1) }
		ret
	}
	
	pub fn set(&mut self, src: &[f32]) {
		unsafe { tsMatrix4x4f_set(self, src.as_ptr(), src.len() as u32, 1) }
	}
	pub fn set_column_major(&mut self, src: &[f32]) {
		unsafe { tsMatrix4x4f_set(self, src.as_ptr(), src.len() as u32, 0) }
	}
	pub fn set_q(&mut self, q: &Quaternionf) {
		unsafe { tsQuaternionf_get(q, &mut self.row_0, &mut self.row_1, &mut self.row_2) }
		self.row_3 = Vector4f::new(0.0, 0.0, 0.0, 1.0)
	}
	pub fn get(&self, dest: &mut [f32]) {
		unsafe { tsMatrix4x4f_get(self, dest.as_mut_ptr(), dest.len() as u32, 1) }
	}
	pub fn get_column_major(&self, dest: &mut [f32]) {
		unsafe { tsMatrix4x4f_get(self, dest.as_mut_ptr(), dest.len() as u32, 0) }
	}
	pub fn get_q(&self, q: &mut Quaternionf) {
		unsafe { tsQuaternionf_set(q, &self.row_0, &self.row_1, &self.row_2) }
	}
	
	pub fn scale_s(s: f32) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_scale(&mut ret, s, s, s); }
		ret
	}
	pub fn scale(x: f32, y: f32, z: f32) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_scale(&mut ret, x, y, z); }
		ret
	}
	pub fn scale_v3(v: &Vector3f) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_scale(&mut ret, v.x, v.y, v.z); }
		ret
	}
	pub fn translate(x: f32, y: f32, z: f32) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_translate(&mut ret, x, y, z); }
		ret
	}
	pub fn translate_v3(v: &Vector3f) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_translate(&mut ret, v.x, v.y, v.z); }
		ret
	}
	pub fn rotate_x(angle: f32) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_rotateX(&mut ret, angle); }
		ret
	}
	pub fn rotate_y(angle: f32) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_rotateY(&mut ret, angle); }
		ret
	}
	pub fn rotate_z(angle: f32) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_rotateZ(&mut ret, angle); }
		ret
	}
	pub fn rotate(axis: &Vector3f, angle: f32) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_rotate(&mut ret, axis, angle); }
		ret
	}
	
	pub fn look_at(from: &Vector3f, to: &Vector3f, up: &Vector3f) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_lookAt(&mut ret, from, to, up); }
		ret
	}
	pub fn place_to(to: &Vector3f, from: &Vector3f, up: &Vector3f) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_placeTo(&mut ret, to, from, up); }
		ret
	}
	pub fn compose(t: &Vector3f, r: &Quaternionf, s: &Vector3f) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_compose(&mut ret, t, r, s); }
		ret
	}
	pub fn basis(normal: &Vector3f, t: &Vector3f) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_basis(&mut ret, normal, t); }
		ret
	}
	
	pub fn ortho(left: f32, right: f32, bottom: f32, top: f32, znear: f32, zfar: f32) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_ortho(&mut ret, left, right, bottom, top, znear, zfar); }
		ret
	}
	pub fn frustum(left: f32, right: f32, bottom: f32, top: f32, znear: f32, zfar: f32) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_frustum(&mut ret, left, right, bottom, top, znear, zfar, 0); }
		ret
	}
	pub fn frustum_reverse(left: f32, right: f32, bottom: f32, top: f32, znear: f32, zfar: f32) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_frustum(&mut ret, left, right, bottom, top, znear, zfar, 1); }
		ret
	}
	pub fn frustum_infinity(left: f32, right: f32, bottom: f32, top: f32, znear: f32) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_frustumi(&mut ret, left, right, bottom, top, znear, 0); }
		ret
	}
	pub fn frustum_infinity_reverse(left: f32, right: f32, bottom: f32, top: f32, znear: f32) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_frustumi(&mut ret, left, right, bottom, top, znear, 1); }
		ret
	}
	pub fn perspective(fov: f32, aspect: f32, znear: f32, zfar: f32) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_perspective(&mut ret, fov, aspect, znear, zfar, 0); }
		ret
	}
	pub fn perspective_reverse(fov: f32, aspect: f32, znear: f32, zfar: f32) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_perspective(&mut ret, fov, aspect, znear, zfar, 1); }
		ret
	}
	pub fn perspective_infinity(fov: f32, aspect: f32, znear: f32) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_perspectivei(&mut ret, fov, aspect, znear, 0); }
		ret
	}
	pub fn perspective_infinity_reverse(fov: f32, aspect: f32, znear: f32) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_perspectivei(&mut ret, fov, aspect, znear, 1); }
		ret
	}
	
	pub fn normalize(&self) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_normalize(&mut ret, self); }
		ret
	}
	pub fn transpose(&self) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_transpose(&mut ret, self); }
		ret
	}
	pub fn inverse(&self) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_inverse(&mut ret, self); }
		ret
	}
	pub fn inverse43(&self) -> Matrix4x4f {
		let mut ret = Matrix4x4f::default();
		unsafe { tsMatrix4x4f_inverse43(&mut ret, self); }
		ret
	}
	
	pub fn identity() -> Matrix4x4f {
		Matrix4x4f { row_0: Vector4f::new(1.0, 0.0, 0.0, 0.0), row_1: Vector4f::new(0.0, 1.0, 0.0, 0.0), row_2: Vector4f::new(0.0, 0.0, 1.0, 0.0), row_3: Vector4f::new(0.0, 0.0, 0.0, 1.0) }
	}
}

/*
 */
impl Default for Matrix4x4f {
	fn default() -> Matrix4x4f {
		Matrix4x4f::identity()
	}
}

/*
 */
impl fmt::Display for Matrix4x4f {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "{0} : {1} : {2} : {3}", self.row_0, self.row_1, self.row_2, self.row_3)
	}
}

/*
 */
declare_op!(Matrix4x4f, Vector2f, Vector2f, Mul, mul, tsMatrix4x4f_mul2);
declare_op!(Matrix4x4f, Vector3f, Vector3f, Mul, mul, tsMatrix4x4f_mul3);
declare_op!(Matrix4x4f, Vector4f, Vector4f, Mul, mul, tsMatrix4x4f_mul4);
declare_op!(Matrix4x4f, BoundRectf, BoundRectf, Mul, mul, tsMatrix4x4f_mul_br);
declare_op!(Matrix4x4f, BoundCirclef, BoundCirclef, Mul, mul, tsMatrix4x4f_mul_bc);
declare_op!(Matrix4x4f, BoundBoxf, BoundBoxf, Mul, mul, tsMatrix4x4f_mul_bb);
declare_op!(Matrix4x4f, BoundSpheref, BoundSpheref, Mul, mul, tsMatrix4x4f_mul_bs);
declare_op!(Vector2f, Matrix4x4f, Vector2f, Mul, mul, tsMatrix4x4f_mul2t);
declare_op!(Vector3f, Matrix4x4f, Vector3f, Mul, mul, tsMatrix4x4f_mul3t);
declare_op!(Vector4f, Matrix4x4f, Vector4f, Mul, mul, tsMatrix4x4f_mul4t);
declare_vector_op!(Matrix4x4f, Mul, mul, tsMatrix4x4f_mul);

/*
 */
extern "C" {
	fn tsMatrix4x4f_set(m: *mut Matrix4x4f, src: *const f32, size: u32, row_major: i32);
	fn tsMatrix4x4f_get(m: *const Matrix4x4f, dest: *mut f32, size: u32, row_major: i32);
	fn tsMatrix4x4f_scale(ret: *mut Matrix4x4f, x: f32, y: f32, z: f32) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_translate(ret: *mut Matrix4x4f, x: f32, y: f32, z: f32) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_rotateX(ret: *mut Matrix4x4f, angle: f32) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_rotateY(ret: *mut Matrix4x4f, angle: f32) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_rotateZ(ret: *mut Matrix4x4f, angle: f32) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_rotate(ret: *mut Matrix4x4f, axis: *const Vector3f, angle: f32) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_lookAt(ret: *mut Matrix4x4f, from: *const Vector3f, to: *const Vector3f, up: *const Vector3f) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_placeTo(ret: *mut Matrix4x4f, to: *const Vector3f, from: *const Vector3f, up: *const Vector3f) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_compose(ret: *mut Matrix4x4f, t: *const Vector3f, r: *const Quaternionf, s: *const Vector3f) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_basis(ret: *mut Matrix4x4f, normal: *const Vector3f, t: *const Vector3f) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_ortho(ret: *mut Matrix4x4f, left: f32, right: f32, bottom: f32, top: f32, znear: f32, zfar: f32) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_frustum(ret: *mut Matrix4x4f, left: f32, right: f32, bottom: f32, top: f32, znear: f32, zfar: f32, reverse: i32) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_frustumi(ret: *mut Matrix4x4f, left: f32, right: f32, bottom: f32, top: f32, znear: f32, reverse: i32) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_perspective(ret: *mut Matrix4x4f, fov: f32, aspect: f32, znear: f32, zfar: f32, reverse: i32) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_perspectivei(ret: *mut Matrix4x4f, fov: f32, aspect: f32, znear: f32, reverse: i32) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_mul2(ret: *mut Vector2f, m: *const Matrix4x4f, v: *const Vector2f) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_mul3(ret: *mut Vector3f, m: *const Matrix4x4f, v: *const Vector3f) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_mul4(ret: *mut Vector4f, m: *const Matrix4x4f, v: *const Vector4f) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_mul_br(ret: *mut BoundRectf, m: *const Matrix4x4f, r: *const BoundRectf) -> *mut BoundRectf;
	fn tsMatrix4x4f_mul_bc(ret: *mut BoundCirclef, m: *const Matrix4x4f, c: *const BoundCirclef) -> *mut BoundCirclef;
	fn tsMatrix4x4f_mul_bb(ret: *mut BoundBoxf, m: *const Matrix4x4f, b: *const BoundBoxf) -> *mut BoundBoxf;
	fn tsMatrix4x4f_mul_bs(ret: *mut BoundSpheref, m: *const Matrix4x4f, s: *const BoundSpheref) -> *mut BoundSpheref;
	fn tsMatrix4x4f_mul2t(ret: *mut Vector2f, v: *const Vector2f, m: *const Matrix4x4f) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_mul3t(ret: *mut Vector3f, v: *const Vector3f, m: *const Matrix4x4f) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_mul4t(ret: *mut Vector4f, v: *const Vector4f, m: *const Matrix4x4f) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_mul(ret: *mut Matrix4x4f, v0: *const Matrix4x4f, v1: *const Matrix4x4f) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_normalize(ret: *mut Matrix4x4f, v: *const Matrix4x4f) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_transpose(ret: *mut Matrix4x4f, v: *const Matrix4x4f) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_inverse(ret: *mut Matrix4x4f, v: *const Matrix4x4f) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_inverse43(ret: *mut Matrix4x4f, v: *const Matrix4x4f) -> *mut Matrix4x4f;
	fn tsMatrix4x4f_lerp(ret: *mut Matrix4x4f, v0: *const Matrix4x4f, v1: *const Matrix4x4f, k: f32) -> *mut Matrix4x4f;
}

/*****************************************************************************\
 *
 * Matrix4x4d
 *
\*****************************************************************************/

/*
 */
#[repr(C, align(16))]
#[derive(Copy, Clone)]
pub struct Matrix4x4d {
	pub row_0: Vector4d,
	pub row_1: Vector4d,
	pub row_2: Vector4d,
	pub row_3: Vector4d,
}

/*
 */
impl Matrix4x4d {
	
	pub fn new(row_0: &Vector4d, row_1: &Vector4d, row_2: &Vector4d, row_3: &Vector4d) -> Matrix4x4d {
		Matrix4x4d { row_0: *row_0, row_1: *row_1, row_2: *row_2, row_3: *row_3 }
	}
	pub fn new_m4x3(m: &Matrix4x3d) -> Matrix4x4d {
		Matrix4x4d { row_0: m.row_0, row_1: m.row_1, row_2: m.row_2, row_3: Vector4d::new(0.0, 0.0, 0.0, 1.0) }
	}
	pub fn new_m4x4f(m: &Matrix4x4f) -> Matrix4x4d {
		Matrix4x4d { row_0: Vector4d::new_v4f(&m.row_0), row_1: Vector4d::new_v4f(&m.row_1), row_2: Vector4d::new_v4f(&m.row_2), row_3: Vector4d::new_v4f(&m.row_3) }
	}
	pub fn new_q(q: &Quaterniond) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsQuaterniond_get(q, &mut ret.row_0, &mut ret.row_1, &mut ret.row_2) }
		ret
	}
	pub fn new_a(src: &[f64]) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_set(&mut ret, src.as_ptr(), src.len() as u32, 1) }
		ret
	}
	
	pub fn set(&mut self, src: &[f64]) {
		unsafe { tsMatrix4x4d_set(self, src.as_ptr(), src.len() as u32, 1) }
	}
	pub fn set_column_major(&mut self, src: &[f64]) {
		unsafe { tsMatrix4x4d_set(self, src.as_ptr(), src.len() as u32, 0) }
	}
	pub fn set_q(&mut self, q: &Quaterniond) {
		unsafe { tsQuaterniond_get(q, &mut self.row_0, &mut self.row_1, &mut self.row_2) }
		self.row_3 = Vector4d::new(0.0, 0.0, 0.0, 1.0)
	}
	pub fn get(&self, dest: &mut [f64]) {
		unsafe { tsMatrix4x4d_get(self, dest.as_mut_ptr(), dest.len() as u32, 1) }
	}
	pub fn get_column_major(&self, dest: &mut [f64]) {
		unsafe { tsMatrix4x4d_get(self, dest.as_mut_ptr(), dest.len() as u32, 0) }
	}
	pub fn get_q(&self, q: &mut Quaterniond) {
		unsafe { tsQuaterniond_set(q, &self.row_0, &self.row_1, &self.row_2) }
	}
	
	pub fn scale_s(s: f64) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_scale(&mut ret, s, s, s); }
		ret
	}
	pub fn scale(x: f64, y: f64, z: f64) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_scale(&mut ret, x, y, z); }
		ret
	}
	pub fn scale_v3(v: &Vector3d) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_scale(&mut ret, v.x, v.y, v.z); }
		ret
	}
	pub fn translate(x: f64, y: f64, z: f64) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_translate(&mut ret, x, y, z); }
		ret
	}
	pub fn translate_v3(v: &Vector3d) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_translate(&mut ret, v.x, v.y, v.z); }
		ret
	}
	pub fn rotate_x(angle: f64) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_rotateX(&mut ret, angle); }
		ret
	}
	pub fn rotate_y(angle: f64) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_rotateY(&mut ret, angle); }
		ret
	}
	pub fn rotate_z(angle: f64) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_rotateZ(&mut ret, angle); }
		ret
	}
	pub fn rotate(axis: &Vector3d, angle: f64) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_rotate(&mut ret, axis, angle); }
		ret
	}
	
	pub fn look_at(from: &Vector3d, to: &Vector3d, up: &Vector3d) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_lookAt(&mut ret, from, to, up); }
		ret
	}
	pub fn place_to(to: &Vector3d, from: &Vector3d, up: &Vector3d) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_placeTo(&mut ret, to, from, up); }
		ret
	}
	pub fn compose(t: &Vector3d, r: &Quaterniond, s: &Vector3d) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_compose(&mut ret, t, r, s); }
		ret
	}
	pub fn basis(normal: &Vector3d, t: &Vector3d) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_basis(&mut ret, normal, t); }
		ret
	}
	
	pub fn ortho(left: f64, right: f64, bottom: f64, top: f64, znear: f64, zfar: f64) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_ortho(&mut ret, left, right, bottom, top, znear, zfar); }
		ret
	}
	pub fn frustum(left: f64, right: f64, bottom: f64, top: f64, znear: f64, zfar: f64) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_frustum(&mut ret, left, right, bottom, top, znear, zfar, 0); }
		ret
	}
	pub fn frustum_reverse(left: f64, right: f64, bottom: f64, top: f64, znear: f64, zfar: f64) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_frustum(&mut ret, left, right, bottom, top, znear, zfar, 1); }
		ret
	}
	pub fn frustum_infinity(left: f64, right: f64, bottom: f64, top: f64, znear: f64) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_frustumi(&mut ret, left, right, bottom, top, znear, 0); }
		ret
	}
	pub fn frustum_infinity_reverse(left: f64, right: f64, bottom: f64, top: f64, znear: f64) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_frustumi(&mut ret, left, right, bottom, top, znear, 1); }
		ret
	}
	pub fn perspective(fov: f64, aspect: f64, znear: f64, zfar: f64) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_perspective(&mut ret, fov, aspect, znear, zfar, 0); }
		ret
	}
	pub fn perspective_reverse(fov: f64, aspect: f64, znear: f64, zfar: f64) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_perspective(&mut ret, fov, aspect, znear, zfar, 1); }
		ret
	}
	pub fn perspective_infinity(fov: f64, aspect: f64, znear: f64) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_perspectivei(&mut ret, fov, aspect, znear, 0); }
		ret
	}
	pub fn perspective_infinity_reverse(fov: f64, aspect: f64, znear: f64) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_perspectivei(&mut ret, fov, aspect, znear, 1); }
		ret
	}
	
	pub fn normalize(&self) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_normalize(&mut ret, self); }
		ret
	}
	pub fn transpose(&self) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_transpose(&mut ret, self); }
		ret
	}
	pub fn inverse(&self) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_inverse(&mut ret, self); }
		ret
	}
	pub fn inverse43(&self) -> Matrix4x4d {
		let mut ret = Matrix4x4d::default();
		unsafe { tsMatrix4x4d_inverse43(&mut ret, self); }
		ret
	}
	
	pub fn identity() -> Matrix4x4d {
		Matrix4x4d { row_0: Vector4d::new(1.0, 0.0, 0.0, 0.0), row_1: Vector4d::new(0.0, 1.0, 0.0, 0.0), row_2: Vector4d::new(0.0, 0.0, 1.0, 0.0), row_3: Vector4d::new(0.0, 0.0, 0.0, 1.0) }
	}
}

/*
 */
impl Default for Matrix4x4d {
	fn default() -> Matrix4x4d {
		Matrix4x4d::identity()
	}
}

/*
 */
impl fmt::Display for Matrix4x4d {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "{0} : {1} : {2} : {3}", self.row_0, self.row_1, self.row_2, self.row_3)
	}
}

/*
 */
declare_op!(Matrix4x4d, Vector2d, Vector2d, Mul, mul, tsMatrix4x4d_mul2);
declare_op!(Matrix4x4d, Vector3d, Vector3d, Mul, mul, tsMatrix4x4d_mul3);
declare_op!(Matrix4x4d, Vector4d, Vector4d, Mul, mul, tsMatrix4x4d_mul4);
declare_op!(Matrix4x4d, BoundRectd, BoundRectd, Mul, mul, tsMatrix4x4d_mul_br);
declare_op!(Matrix4x4d, BoundCircled, BoundCircled, Mul, mul, tsMatrix4x4d_mul_bc);
declare_op!(Matrix4x4d, BoundBoxd, BoundBoxd, Mul, mul, tsMatrix4x4d_mul_bb);
declare_op!(Matrix4x4d, BoundSphered, BoundSphered, Mul, mul, tsMatrix4x4d_mul_bs);
declare_op!(Vector2d, Matrix4x4d, Vector2d, Mul, mul, tsMatrix4x4d_mul2t);
declare_op!(Vector3d, Matrix4x4d, Vector3d, Mul, mul, tsMatrix4x4d_mul3t);
declare_op!(Vector4d, Matrix4x4d, Vector4d, Mul, mul, tsMatrix4x4d_mul4t);
declare_vector_op!(Matrix4x4d, Mul, mul, tsMatrix4x4d_mul);

/*
 */
extern "C" {
	fn tsMatrix4x4d_set(m: *mut Matrix4x4d, src: *const f64, size: u32, row_major: i32);
	fn tsMatrix4x4d_get(m: *const Matrix4x4d, dest: *mut f64, size: u32, row_major: i32);
	fn tsMatrix4x4d_scale(ret: *mut Matrix4x4d, x: f64, y: f64, z: f64) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_translate(ret: *mut Matrix4x4d, x: f64, y: f64, z: f64) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_rotateX(ret: *mut Matrix4x4d, angle: f64) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_rotateY(ret: *mut Matrix4x4d, angle: f64) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_rotateZ(ret: *mut Matrix4x4d, angle: f64) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_rotate(ret: *mut Matrix4x4d, axis: *const Vector3d, angle: f64) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_lookAt(ret: *mut Matrix4x4d, from: *const Vector3d, to: *const Vector3d, up: *const Vector3d) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_placeTo(ret: *mut Matrix4x4d, to: *const Vector3d, from: *const Vector3d, up: *const Vector3d) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_compose(ret: *mut Matrix4x4d, t: *const Vector3d, r: *const Quaterniond, s: *const Vector3d) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_basis(ret: *mut Matrix4x4d, normal: *const Vector3d, t: *const Vector3d) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_ortho(ret: *mut Matrix4x4d, left: f64, right: f64, bottom: f64, top: f64, znear: f64, zfar: f64) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_frustum(ret: *mut Matrix4x4d, left: f64, right: f64, bottom: f64, top: f64, znear: f64, zfar: f64, reverse: i32) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_frustumi(ret: *mut Matrix4x4d, left: f64, right: f64, bottom: f64, top: f64, znear: f64, reverse: i32) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_perspective(ret: *mut Matrix4x4d, fov: f64, aspect: f64, znear: f64, zfar: f64, reverse: i32) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_perspectivei(ret: *mut Matrix4x4d, fov: f64, aspect: f64, znear: f64, reverse: i32) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_mul2(ret: *mut Vector2d, m: *const Matrix4x4d, v: *const Vector2d) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_mul3(ret: *mut Vector3d, m: *const Matrix4x4d, v: *const Vector3d) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_mul4(ret: *mut Vector4d, m: *const Matrix4x4d, v: *const Vector4d) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_mul_br(ret: *mut BoundRectd, m: *const Matrix4x4d, r: *const BoundRectd) -> *mut BoundRectd;
	fn tsMatrix4x4d_mul_bc(ret: *mut BoundCircled, m: *const Matrix4x4d, c: *const BoundCircled) -> *mut BoundCircled;
	fn tsMatrix4x4d_mul_bb(ret: *mut BoundBoxd, m: *const Matrix4x4d, b: *const BoundBoxd) -> *mut BoundBoxd;
	fn tsMatrix4x4d_mul_bs(ret: *mut BoundSphered, m: *const Matrix4x4d, s: *const BoundSphered) -> *mut BoundSphered;
	fn tsMatrix4x4d_mul2t(ret: *mut Vector2d, v: *const Vector2d, m: *const Matrix4x4d) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_mul3t(ret: *mut Vector3d, v: *const Vector3d, m: *const Matrix4x4d) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_mul4t(ret: *mut Vector4d, v: *const Vector4d, m: *const Matrix4x4d) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_mul(ret: *mut Matrix4x4d, v0: *const Matrix4x4d, v1: *const Matrix4x4d) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_normalize(ret: *mut Matrix4x4d, v: *const Matrix4x4d) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_transpose(ret: *mut Matrix4x4d, v: *const Matrix4x4d) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_inverse(ret: *mut Matrix4x4d, v: *const Matrix4x4d) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_inverse43(ret: *mut Matrix4x4d, v: *const Matrix4x4d) -> *mut Matrix4x4d;
	fn tsMatrix4x4d_lerp(ret: *mut Matrix4x4d, v0: *const Matrix4x4d, v1: *const Matrix4x4d, k: f64) -> *mut Matrix4x4d;
}

/*****************************************************************************\
 *
 * Quaternionf
 *
\*****************************************************************************/

/*
 */
#[repr(C, align(16))]
#[derive(Copy, Clone)]
pub struct Quaternionf {
	pub x: f32,
	pub y: f32,
	pub z: f32,
	pub w: f32,
}

/*
 */
impl Quaternionf {
	
	pub fn new(x: f32, y: f32, z: f32, w: f32) -> Quaternionf {
		Quaternionf { x: x, y: y, z: z, w: w }
	}
	pub fn new_qd(q: &Quaterniond) -> Quaternionf {
		Quaternionf { x: q.x as f32, y: q.y as f32, z: q.z as f32, w: q.w as f32 }
	}
	pub fn new_m4x3(m: &Matrix4x3f) -> Quaternionf {
		let mut ret = Quaternionf::default();
		unsafe { tsQuaternionf_set(&mut ret, &m.row_0, &m.row_1, &m.row_2); }
		ret
	}
	pub fn new_m4x4(m: &Matrix4x4f) -> Quaternionf {
		let mut ret = Quaternionf::default();
		unsafe { tsQuaternionf_set(&mut ret, &m.row_0, &m.row_1, &m.row_2); }
		ret
	}
	pub fn new_a(v: &[f32]) -> Quaternionf {
		Quaternionf { x: v[0], y: v[1], z: v[2], w: v[3] }
	}
	
	pub fn set_m4x3(&mut self, m: &Matrix4x3f) {
		unsafe { tsQuaternionf_set(self, &m.row_0, &m.row_1, &m.row_2); }
	}
	pub fn set_m4x4(&mut self, m: &Matrix4x4f) {
		unsafe { tsQuaternionf_set(self, &m.row_0, &m.row_1, &m.row_2); }
	}
	pub fn get_m4x3(&self, m: &mut Matrix4x3f) {
		unsafe { tsQuaternionf_get(self, &mut m.row_0, &mut m.row_1, &mut m.row_2); }
	}
	pub fn get_m4x4(&self, m: &mut Matrix4x4f) {
		unsafe { tsQuaternionf_get(self, &mut m.row_0, &mut m.row_1, &mut m.row_2); }
		m.row_3 = Vector4f::new(0.0, 0.0, 0.0, 1.0);
	}
	
	pub fn rotate_x(angle: f32) -> Quaternionf {
		let mut ret = Quaternionf::default();
		unsafe { tsQuaternionf_rotateX(&mut ret, angle); }
		ret
	}
	pub fn rotate_y(angle: f32) -> Quaternionf {
		let mut ret = Quaternionf::default();
		unsafe { tsQuaternionf_rotateY(&mut ret, angle); }
		ret
	}
	pub fn rotate_z(angle: f32) -> Quaternionf {
		let mut ret = Quaternionf::default();
		unsafe { tsQuaternionf_rotateZ(&mut ret, angle); }
		ret
	}
	pub fn rotate_xyz(angles: &Vector3f) -> Quaternionf {
		let mut ret = Quaternionf::default();
		unsafe { tsQuaternionf_rotateXYZ(&mut ret, angles); }
		ret
	}
	pub fn rotate_zyx(angles: &Vector3f) -> Quaternionf {
		let mut ret = Quaternionf::default();
		unsafe { tsQuaternionf_rotateZYX(&mut ret, angles); }
		ret
	}
	pub fn rotate(axis: &Vector3f, angle: f32) -> Quaternionf {
		let mut ret = Quaternionf::default();
		unsafe { tsQuaternionf_rotate(&mut ret, axis, angle); }
		ret
	}
	
	pub fn normalize(&self) -> Quaternionf {
		let mut ret = Quaternionf::default();
		unsafe { tsQuaternionf_normalize(&mut ret, self); }
		ret
	}
	pub fn inverse(&self) -> Quaternionf {
		let mut ret = Quaternionf::default();
		unsafe { tsQuaternionf_inverse(&mut ret, self); }
		ret
	}
	
	pub fn lerp(v0: &Quaternionf, v1: &Quaternionf, k: f32) -> Quaternionf {
		let mut ret = Quaternionf::default();
		unsafe { tsQuaternionf_lerp(&mut ret, v0, v1, k); }
		ret
	}
	pub fn slerp(v0: &Quaternionf, v1: &Quaternionf, k: f32) -> Quaternionf {
		let mut ret = Quaternionf::default();
		unsafe { tsQuaternionf_slerp(&mut ret, v0, v1, k); }
		ret
	}
	
	pub fn identity() -> Quaternionf {
		Quaternionf { x: 0.0, y: 0.0, z: 0.0, w: 1.0 }
	}
}

/*
 */
impl Default for Quaternionf {
	fn default() -> Quaternionf {
		Quaternionf::identity()
	}
}

/*
 */
impl fmt::Display for Quaternionf {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "({0} {1} {2} {3})", self.x, self.y, self.z, self.w)
	}
}

/*
 */
declare_op!(Quaternionf, Vector2f, Vector2f, Mul, mul, tsQuaternionf_mul2);
declare_op!(Quaternionf, Vector3f, Vector3f, Mul, mul, tsQuaternionf_mul3);
declare_op!(Quaternionf, Vector4f, Vector4f, Mul, mul, tsQuaternionf_mul4);
declare_op!(Vector2f, Quaternionf, Vector2f, Mul, mul, tsQuaternionf_mul2t);
declare_op!(Vector3f, Quaternionf, Vector3f, Mul, mul, tsQuaternionf_mul3t);
declare_op!(Vector4f, Quaternionf, Vector4f, Mul, mul, tsQuaternionf_mul4t);
declare_scalar_op!(Quaternionf, f32, Mul, mul, tsQuaternionf_mul1);
declare_vector_op!(Quaternionf, Mul, mul, tsQuaternionf_mul);

/*
 */
extern "C" {
	fn tsQuaternionf_set(q: *mut Quaternionf, row_0: *const Vector4f, row_1: *const Vector4f, row_2: *const Vector4f);
	fn tsQuaternionf_get(q: *const Quaternionf, row_0: *mut Vector4f, row_1: *mut Vector4f, row_2: *mut Vector4f);
	fn tsQuaternionf_rotateX(ret: *mut Quaternionf, angle: f32) -> *mut Quaternionf;
	fn tsQuaternionf_rotateY(ret: *mut Quaternionf, angle: f32) -> *mut Quaternionf;
	fn tsQuaternionf_rotateZ(ret: *mut Quaternionf, angle: f32) -> *mut Quaternionf;
	fn tsQuaternionf_rotateXYZ(ret: *mut Quaternionf, angles: *const Vector3f) -> *mut Quaternionf;
	fn tsQuaternionf_rotateZYX(ret: *mut Quaternionf, angles: *const Vector3f) -> *mut Quaternionf;
	fn tsQuaternionf_rotate(ret: *mut Quaternionf, axis: *const Vector3f, angle: f32) -> *mut Quaternionf;
	fn tsQuaternionf_mul2(ret: *mut Vector2f, q: *const Quaternionf, v: *const Vector2f) -> *mut Quaternionf;
	fn tsQuaternionf_mul3(ret: *mut Vector3f, q: *const Quaternionf, v: *const Vector3f) -> *mut Quaternionf;
	fn tsQuaternionf_mul4(ret: *mut Vector4f, q: *const Quaternionf, v: *const Vector4f) -> *mut Quaternionf;
	fn tsQuaternionf_mul2t(ret: *mut Vector2f, v: *const Vector2f, q: *const Quaternionf) -> *mut Quaternionf;
	fn tsQuaternionf_mul3t(ret: *mut Vector3f, v: *const Vector3f, q: *const Quaternionf) -> *mut Quaternionf;
	fn tsQuaternionf_mul4t(ret: *mut Vector4f, v: *const Vector4f, q: *const Quaternionf) -> *mut Quaternionf;
	fn tsQuaternionf_mul1(ret: *mut Quaternionf, q: *const Quaternionf, v: f32) -> *mut Quaternionf;
	fn tsQuaternionf_mul(ret: *mut Quaternionf, q0: *const Quaternionf, q1: *const Quaternionf) -> *mut Quaternionf;
	fn tsQuaternionf_normalize(ret: *mut Quaternionf, v: *const Quaternionf) -> *mut Quaternionf;
	fn tsQuaternionf_inverse(ret: *mut Quaternionf, v: *const Quaternionf) -> *mut Quaternionf;
	fn tsQuaternionf_lerp(ret: *mut Quaternionf, v0: *const Quaternionf, v1: *const Quaternionf, k: f32) -> *mut Quaternionf;
	fn tsQuaternionf_slerp(ret: *mut Quaternionf, v0: *const Quaternionf, v1: *const Quaternionf, k: f32) -> *mut Quaternionf;
}

/*****************************************************************************\
 *
 * Quaterniond
 *
\*****************************************************************************/

/*
 */
#[repr(C, align(16))]
#[derive(Copy, Clone)]
pub struct Quaterniond {
	pub x: f64,
	pub y: f64,
	pub z: f64,
	pub w: f64,
}

/*
 */
impl Quaterniond {
	
	pub fn new(x: f64, y: f64, z: f64, w: f64) -> Quaterniond {
		Quaterniond { x: x, y: y, z: z, w: w }
	}
	pub fn new_qf(q: &Quaternionf) -> Quaterniond {
		Quaterniond { x: q.x as f64, y: q.y as f64, z: q.z as f64, w: q.w as f64 }
	}
	pub fn new_m4x3(m: &Matrix4x3d) -> Quaterniond {
		let mut ret = Quaterniond::default();
		unsafe { tsQuaterniond_set(&mut ret, &m.row_0, &m.row_1, &m.row_2); }
		ret
	}
	pub fn new_m4x4(m: &Matrix4x4d) -> Quaterniond {
		let mut ret = Quaterniond::default();
		unsafe { tsQuaterniond_set(&mut ret, &m.row_0, &m.row_1, &m.row_2); }
		ret
	}
	pub fn new_a(v: &[f64]) -> Quaterniond {
		Quaterniond { x: v[0], y: v[1], z: v[2], w: v[3] }
	}
	
	pub fn set_m4x3(&mut self, m: &Matrix4x3d) {
		unsafe { tsQuaterniond_set(self, &m.row_0, &m.row_1, &m.row_2); }
	}
	pub fn set_m4x4(&mut self, m: &Matrix4x4d) {
		unsafe { tsQuaterniond_set(self, &m.row_0, &m.row_1, &m.row_2); }
	}
	pub fn get_m4x3(&self, m: &mut Matrix4x3d) {
		unsafe { tsQuaterniond_get(self, &mut m.row_0, &mut m.row_1, &mut m.row_2); }
	}
	pub fn get_m4x4(&self, m: &mut Matrix4x4d) {
		unsafe { tsQuaterniond_get(self, &mut m.row_0, &mut m.row_1, &mut m.row_2); }
		m.row_3 = Vector4d::new(0.0, 0.0, 0.0, 1.0);
	}
	
	pub fn rotate_x(angle: f64) -> Quaterniond {
		let mut ret = Quaterniond::default();
		unsafe { tsQuaterniond_rotateX(&mut ret, angle); }
		ret
	}
	pub fn rotate_y(angle: f64) -> Quaterniond {
		let mut ret = Quaterniond::default();
		unsafe { tsQuaterniond_rotateY(&mut ret, angle); }
		ret
	}
	pub fn rotate_z(angle: f64) -> Quaterniond {
		let mut ret = Quaterniond::default();
		unsafe { tsQuaterniond_rotateZ(&mut ret, angle); }
		ret
	}
	pub fn rotate_xyz(angles: &Vector3d) -> Quaterniond {
		let mut ret = Quaterniond::default();
		unsafe { tsQuaterniond_rotateXYZ(&mut ret, angles); }
		ret
	}
	pub fn rotate_zyx(angles: &Vector3d) -> Quaterniond {
		let mut ret = Quaterniond::default();
		unsafe { tsQuaterniond_rotateZYX(&mut ret, angles); }
		ret
	}
	pub fn rotate(axis: &Vector3d, angle: f64) -> Quaterniond {
		let mut ret = Quaterniond::default();
		unsafe { tsQuaterniond_rotate(&mut ret, axis, angle); }
		ret
	}
	
	pub fn normalize(&self) -> Quaterniond {
		let mut ret = Quaterniond::default();
		unsafe { tsQuaterniond_normalize(&mut ret, self); }
		ret
	}
	pub fn inverse(&self) -> Quaterniond {
		let mut ret = Quaterniond::default();
		unsafe { tsQuaterniond_inverse(&mut ret, self); }
		ret
	}
	
	pub fn lerp(v0: &Quaterniond, v1: &Quaterniond, k: f64) -> Quaterniond {
		let mut ret = Quaterniond::default();
		unsafe { tsQuaterniond_lerp(&mut ret, v0, v1, k); }
		ret
	}
	pub fn slerp(v0: &Quaterniond, v1: &Quaterniond, k: f64) -> Quaterniond {
		let mut ret = Quaterniond::default();
		unsafe { tsQuaterniond_slerp(&mut ret, v0, v1, k); }
		ret
	}
	
	pub fn identity() -> Quaterniond {
		Quaterniond { x: 0.0, y: 0.0, z: 0.0, w: 1.0 }
	}
}

/*
 */
impl Default for Quaterniond {
	fn default() -> Quaterniond {
		Quaterniond::identity()
	}
}

/*
 */
impl fmt::Display for Quaterniond {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "({0} {1} {2} {3})", self.x, self.y, self.z, self.w)
	}
}

/*
 */
declare_op!(Quaterniond, Vector2d, Vector2d, Mul, mul, tsQuaterniond_mul2);
declare_op!(Quaterniond, Vector3d, Vector3d, Mul, mul, tsQuaterniond_mul3);
declare_op!(Quaterniond, Vector4d, Vector4d, Mul, mul, tsQuaterniond_mul4);
declare_op!(Vector2d, Quaterniond, Vector2d, Mul, mul, tsQuaterniond_mul2t);
declare_op!(Vector3d, Quaterniond, Vector3d, Mul, mul, tsQuaterniond_mul3t);
declare_op!(Vector4d, Quaterniond, Vector4d, Mul, mul, tsQuaterniond_mul4t);
declare_scalar_op!(Quaterniond, f64, Mul, mul, tsQuaterniond_mul1);
declare_vector_op!(Quaterniond, Mul, mul, tsQuaterniond_mul);

/*
 */
extern "C" {
	fn tsQuaterniond_set(q: *mut Quaterniond, row_0: *const Vector4d, row_1: *const Vector4d, row_2: *const Vector4d);
	fn tsQuaterniond_get(q: *const Quaterniond, row_0: *mut Vector4d, row_1: *mut Vector4d, row_2: *mut Vector4d);
	fn tsQuaterniond_rotateX(ret: *mut Quaterniond, angle: f64) -> *mut Quaterniond;
	fn tsQuaterniond_rotateY(ret: *mut Quaterniond, angle: f64) -> *mut Quaterniond;
	fn tsQuaterniond_rotateZ(ret: *mut Quaterniond, angle: f64) -> *mut Quaterniond;
	fn tsQuaterniond_rotateXYZ(ret: *mut Quaterniond, angles: *const Vector3d) -> *mut Quaterniond;
	fn tsQuaterniond_rotateZYX(ret: *mut Quaterniond, angles: *const Vector3d) -> *mut Quaterniond;
	fn tsQuaterniond_rotate(ret: *mut Quaterniond, axis: *const Vector3d, angle: f64) -> *mut Quaterniond;
	fn tsQuaterniond_mul2(ret: *mut Vector2d, q: *const Quaterniond, v: *const Vector2d) -> *mut Quaterniond;
	fn tsQuaterniond_mul3(ret: *mut Vector3d, q: *const Quaterniond, v: *const Vector3d) -> *mut Quaterniond;
	fn tsQuaterniond_mul4(ret: *mut Vector4d, q: *const Quaterniond, v: *const Vector4d) -> *mut Quaterniond;
	fn tsQuaterniond_mul2t(ret: *mut Vector2d, v: *const Vector2d, q: *const Quaterniond) -> *mut Quaterniond;
	fn tsQuaterniond_mul3t(ret: *mut Vector3d, v: *const Vector3d, q: *const Quaterniond) -> *mut Quaterniond;
	fn tsQuaterniond_mul4t(ret: *mut Vector4d, v: *const Vector4d, q: *const Quaterniond) -> *mut Quaterniond;
	fn tsQuaterniond_mul1(ret: *mut Quaterniond, q: *const Quaterniond, v: f64) -> *mut Quaterniond;
	fn tsQuaterniond_mul(ret: *mut Quaterniond, q0: *const Quaterniond, q1: *const Quaterniond) -> *mut Quaterniond;
	fn tsQuaterniond_normalize(ret: *mut Quaterniond, v: *const Quaterniond) -> *mut Quaterniond;
	fn tsQuaterniond_inverse(ret: *mut Quaterniond, v: *const Quaterniond) -> *mut Quaterniond;
	fn tsQuaterniond_lerp(ret: *mut Quaterniond, v0: *const Quaterniond, v1: *const Quaterniond, k: f64) -> *mut Quaterniond;
	fn tsQuaterniond_slerp(ret: *mut Quaterniond, v0: *const Quaterniond, v1: *const Quaterniond, k: f64) -> *mut Quaterniond;
}

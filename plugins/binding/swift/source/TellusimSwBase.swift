// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

/* 8-bit integer constants
 */
public let MINI8: Int32 = -127 - 1
public let MAXI8: Int32 =  127
public let MAXU8: UInt32 = 255

/* 16-bit integer constants
 */
public let Mini16: Int32 = -32767 - 1
public let Maxi16: Int32 =  32767
public let Maxu16: UInt32 = 65535

/* 32-bit integer constants
 */
public let Mini32: Int32 = -2147483647 - 1
public let Maxi32: Int32 =  2147483647
public let Maxu32: UInt32 = 4294967295

/* 64-bit integer constants
 */
public let Mini64: Int64 = -9223372036854775807 - 1
public let Maxi64: Int64 =  9223372036854775807
public let Maxu64: UInt64 = 18446744073709551615

/* 16-bit floating point constants
 */
public let Minf16: Float32 = 5.96046448e-08
public let Maxf16: Float32 = 65504.0

/* 32-bit floating point constants
 */
public let Maxf32: Float32 = 3.40282346e+38
public let Pi: Float32 = 3.141592653589793
public let Pi2: Float32 = 6.283185307179586
public let Pi05: Float32 = 1.570796326794897
public let Sqrt2: Float32 = 1.4142135623730951
public let Deg2Rad: Float32 = 0.017453292519943
public let Rad2Deg: Float32 = 57.295779513082325

/* 64-bit floating point constants
 */
public let Maxf64: Float64 = 1.79769313486231571e+308
public let Pid: Float64 = 3.141592653589793115997963468544
public let Pi2d: Float64 = 6.283185307179586231995926937088
public let Pi05d: Float64 = 1.570796326794896557998981734272
public let Sqrt2d: Float64 = 1.414213562373095145474621858739
public let Deg2Radd: Float64 = 0.017453292519943295474371680598
public let Rad2Degd: Float64 = 57.295779513082322864647721871734

/*****************************************************************************\
 *
 * Log
 *
\*****************************************************************************/

/*
 */
public extension Log {
	
	static func printf(_ format: String, _ args: CVarArg...) {
		withVaList(args) { argv in
			Log.vprintf(format, argv)
		}
	}
	
	static func printf(_ level: Log.Level, _ format: String, _ args: CVarArg...) {
		withVaList(args) { argv in
			Log.vprintf(level, format, argv)
		}
	}
	static func printef(_ level: Log.Level, _ format: String, _ args: CVarArg...) {
		withVaList(args) { argv in
			Log.vprintef(level, format, argv)
		}
	}
}

/*****************************************************************************\
 *
 * Color
 *
\*****************************************************************************/

/*
 */
public extension TSColor {
	
	init(_ c: Float32) { self.init(); self.r = c; self.g = c; self.b = c; self.a = c }
	init(_ l: Float32, _ a: Float32) { self.init(); self.r = l; self.g = l; self.b = l; self.a = a }
	init(_ r: Float32, _ g: Float32, _ b: Float32, _ a: Float32) { self.init(); self.r = r; self.g = g; self.b = b; self.a = a }
	init(_ c: [Float32]) { self.init(); self.r = c[0]; self.g = c[1]; self.b = c[2]; self.a = c[3] }
	
	func gammaToLinear() -> TSColor { var ret = TSColor(), c = self; tsColor_gammaToLinear(&ret, &c); return ret }
	func linearToGamma() -> TSColor { var ret = TSColor(), c = self; tsColor_linearToGamma(&ret, &c); return ret }
	
	func sRGBtoLinear() -> TSColor { var ret = TSColor(), c = self; tsColor_sRGBtoLinear(&ret, &c); return ret }
	func linearToSRGB() -> TSColor { var ret = TSColor(), c = self; tsColor_linearToSRGB(&ret, &c); return ret }
	
	mutating func setRGBAu8(_ color: UInt32) { tsColor_setRGBAu8(&self, color) }
	func getRGBAu8() -> UInt32 { var c = self; return tsColor_getRGBAu8(&c) }
	
	mutating func setBGRAu8(_ color: UInt32) { tsColor_setBGRAu8(&self, color) }
	func getBGRAu8() -> UInt32 { var c = self; return tsColor_getBGRAu8(&c) }
	
	mutating func setABGRu8(_ color: UInt32) { tsColor_setABGRu8(&self, color) }
	func getABGRu8() -> UInt32 { var c = self; return tsColor_getABGRu8(&c) }
	
	static func html(_ src: String) -> TSColor { var ret = TSColor(); tsColor_html(&ret, src); return ret }
	static func hsv(_ h : Float32, _ s: Float32, _ v: Float32) -> TSColor { var ret = TSColor(); tsColor_hsv(&ret, h, s, v); return ret }
	static func temperature(_ t: Float32) -> TSColor { var ret = TSColor(); tsColor_temperature(&ret, t); return ret }
	
	static let zero = TSColor(0.0, 0.0, 0.0, 0.0)
	static let black = TSColor(0.0, 0.0, 0.0, 1.0)
	static let white = TSColor(1.0, 1.0, 1.0, 1.0)
	static let gray = TSColor(0.5, 0.5, 0.5, 1.0)
	
	static let red = TSColor(1.0, 0.0, 0.0, 1.0)
	static let yellow = TSColor(1.0, 1.0, 0.0, 1.0)
	static let green = TSColor(0.0, 1.0, 0.0, 1.0)
	static let cyan = TSColor(0.0, 1.0, 1.0, 1.0)
	static let blue = TSColor(0.0, 0.0, 1.0, 1.0)
	static let magenta = TSColor(1.0, 0.0, 1.0, 1.0)
}

extension TSColor : CustomStringConvertible {
	public var description: String { "(\(r) \(g) \(b) \(a))" }
}

/*
 */
public func *(c0: TSColor, c1: Float32) -> TSColor { TSColor(c0.r * c1, c0.g * c1, c0.b * c1, c0.a * c1) }
public func /(c0: TSColor, c1: Float32) -> TSColor { TSColor(c0.r / c1, c0.g / c1, c0.b / c1, c0.a / c1) }
public func +(c0: TSColor, c1: Float32) -> TSColor { TSColor(c0.r + c1, c0.g + c1, c0.b + c1, c0.a + c1) }
public func -(c0: TSColor, c1: Float32) -> TSColor { TSColor(c0.r - c1, c0.g - c1, c0.b - c1, c0.a - c1) }

public func *(c0: TSColor, c1: TSColor) -> TSColor { TSColor(c0.r * c1.r, c0.g * c1.g, c0.b * c1.b, c0.a * c1.a) }
public func /(c0: TSColor, c1: TSColor) -> TSColor { TSColor(c0.r / c1.r, c0.g / c1.g, c0.b / c1.b, c0.a / c1.a) }
public func +(c0: TSColor, c1: TSColor) -> TSColor { TSColor(c0.r + c1.r, c0.g + c1.g, c0.b + c1.b, c0.a + c1.a) }
public func -(c0: TSColor, c1: TSColor) -> TSColor { TSColor(c0.r - c1.r, c0.g - c1.g, c0.b - c1.b, c0.a - c1.a) }

/*
 */
public func min(_ c0: TSColor, _ c1: TSColor) -> TSColor { TSColor(min(c0.r, c1.r), min(c0.g, c1.g), min(c0.b, c1.b), min(c0.a, c1.a)) }
public func max(_ c0: TSColor, _ c1: TSColor) -> TSColor { TSColor(max(c0.r, c1.r), max(c0.g, c1.g), max(c0.b, c1.b), max(c0.a, c1.a)) }

public func clamp(_ c: TSColor, _ c0: TSColor, _ c1: TSColor) -> TSColor { TSColor(clamp(c.r, c0.r, c1.r), clamp(c.g, c0.g, c1.g), clamp(c.b, c0.b, c1.b), clamp(c.a, c0.a, c1.a)) }
public func saturate(_ c: TSColor) -> TSColor { TSColor(saturate(c.r), saturate(c.g), saturate(c.b), saturate(c.a)) }

public func lerp(_ c: TSColor, _ c0: TSColor, _ c1: TSColor, k: Float32) -> TSColor { c0 + (c1 - c0) * k }

/*****************************************************************************\
 *
 * ImageColor
 *
\*****************************************************************************/

/*
 */
public extension TSImageColor {
	
	init(_ c: Int32) { self.init(); self.i.r = c; self.i.g = c; self.i.b = c; self.i.a = c }
	init(_ c: UInt32) { self.init(); self.u.r = c; self.u.g = c; self.u.b = c; self.u.a = c }
	init(_ c: UInt16) { self.init(); self.h.r = c; self.h.g = c; self.h.b = c; self.h.a = c }
	init(_ c: Float32) { self.init(); self.f.r = c; self.f.g = c; self.f.b = c; self.f.a = c }
	init(_ l: Int32, _ a: Int32) { self.init(); self.i.r = l; self.i.g = l; self.i.b = l; self.i.a = a }
	init(_ l: UInt32, _ a: UInt32) { self.init(); self.u.r = l; self.u.g = l; self.u.b = l; self.u.a = a }
	init(_ l: UInt16, _ a: UInt16) { self.init(); self.h.r = l; self.h.g = l; self.h.b = l; self.h.a = a }
	init(_ l: Float32, _ a: Float32) { self.init(); self.f.r = l; self.f.g = l; self.f.b = l; self.f.a = a }
	init(_ r: Int32, _ g: Int32, _ b: Int32, _ a: Int32) { self.init(); self.i.r = r; self.i.g = g; self.i.b = b; self.i.a = a }
	init(_ r: UInt32, _ g: UInt32, _ b: UInt32, _ a: UInt32) { self.init(); self.u.r = r; self.u.g = g; self.u.b = b; self.u.a = a }
	init(_ r: UInt16, _ g: UInt16, _ b: UInt16, _ a: UInt16) { self.init(); self.h.r = r; self.h.g = g; self.h.b = b; self.h.a = a }
	init(_ r: Float32, _ g: Float32, _ b: Float32, _ a: Float32) { self.init(); self.f.r = r; self.f.g = g; self.f.b = b; self.f.a = a }
	init(_ c: TSColor, _ format: UInt32) { self.init(); set(c, format) }
	
	mutating func set(_ src: TSColor, _ format: UInt32) { var src = src; tsImageColor_set(&self, &src, format) }
	func get(_ dest: inout TSColor, _ format: UInt32) { var c = self; tsImageColor_get(&c, &dest, format) }
}

extension TSImageColor : CustomStringConvertible {
	public var description: String { "(\(u.r) \(u.g) \(u.b) \(u.a))" }
}

/*****************************************************************************\
 *
 * Bounds
 *
\*****************************************************************************/

/*
 */
public extension TSBoundRectf {
	
	init(_ min: TSVector2f, _ max: TSVector2f) { self.init(); self.min = min; self.max = max }
	init(_ br: TSBoundRectf) { self.init(); self.min = br.min; self.max = br.max }
	init(_ br: TSBoundRectd) { var br = br; self.init(); tsBoundRectf_set_brd(&self, &br) }
	init(_ bc: TSBoundCirclef) { var bc = bc; self.init(); tsBoundRectf_set_bc(&self, &bc) }
	
	mutating func expand(_ v: TSVector2f) { var v = v; tsBoundRectf_expand1(&self, &v) }
	mutating func expand(_ br: TSBoundRectf) { var br = br; tsBoundRectf_expand(&self, &br) }
	
	func inside(_ v: TSVector2f) -> Bool { var b = self, v = v; return tsBoundRectf_inside1(&b, &v) }
	func inside(_ br: TSBoundRectf) -> Bool { var b = self, br = br; return tsBoundRectf_inside(&b, &br) }
	
	func distance(_ v: TSVector2f) -> Float32 { var b = self, v = v; return tsBoundRectf_distance(&b, &v) }
}

public func *(_ m: TSMatrix4x3f, _ b: TSBoundRectf) -> TSBoundRectf { var ret = TSBoundRectf(), m = m, b = b; tsMatrix4x3f_mul_br(&ret, &m, &b); return ret }
public func *(_ m: TSMatrix4x4f, _ b: TSBoundRectf) -> TSBoundRectf { var ret = TSBoundRectf(), m = m, b = b; tsMatrix4x4f_mul_br(&ret, &m, &b); return ret }

/*
 */
public extension TSBoundRectd {
	
	init(_ min: TSVector2d, _ max: TSVector2d) { self.init(); self.min = min; self.max = max }
	init(_ br: TSBoundRectd) { self.init(); self.min = br.min; self.max = br.max }
	init(_ br: TSBoundRectf) { var br = br; self.init(); tsBoundRectd_set_brf(&self, &br) }
	init(_ bc: TSBoundCircled) { var bc = bc; self.init(); tsBoundRectd_set_bc(&self, &bc) }
	
	mutating func expand(_ v: TSVector2d) { var v = v; tsBoundRectd_expand1(&self, &v) }
	mutating func expand(_ br: TSBoundRectd) { var br = br; tsBoundRectd_expand(&self, &br) }
	
	func inside(_ v: TSVector2d) -> Bool { var b = self, v = v; return tsBoundRectd_inside1(&b, &v) }
	func inside(_ br: TSBoundRectd) -> Bool { var b = self, br = br; return tsBoundRectd_inside(&b, &br) }
	
	func distance(_ v: TSVector2d) -> Float64 { var b = self, v = v; return tsBoundRectd_distance(&b, &v) }
}

public func *(_ m: TSMatrix4x3d, _ b: TSBoundRectd) -> TSBoundRectd { var ret = TSBoundRectd(), m = m, b = b; tsMatrix4x3d_mul_br(&ret, &m, &b); return ret }
public func *(_ m: TSMatrix4x4d, _ b: TSBoundRectd) -> TSBoundRectd { var ret = TSBoundRectd(), m = m, b = b; tsMatrix4x4d_mul_br(&ret, &m, &b); return ret }

/*
 */
public extension TSBoundCirclef {
	
	init(_ center: TSVector2f, _ radius: Float32) { self.init(); self.center = center; self.radius = radius }
	init(_ bc: TSBoundCirclef) { self.init(); self.center = bc.center; self.radius = bc.radius }
	init(_ bc: TSBoundCircled) { var bc = bc; self.init(); tsBoundCirclef_set_bcd(&self, &bc) }
	init(_ br: TSBoundRectf) { var br = br; self.init(); tsBoundCirclef_set_br(&self, &br) }
	
	mutating func expand(_ v: TSVector2f) { var v = v; tsBoundCirclef_expand1(&self, &v) }
	mutating func expand(_ bc: TSBoundCirclef) { var bc = bc; tsBoundCirclef_expand(&self, &bc) }
	
	mutating func expandRadius(_ v: TSVector2f) { var v = v; tsBoundCirclef_expandRadius1(&self, &v) }
	mutating func expandRadius(_ bc: TSBoundCirclef) { var bc = bc; tsBoundCirclef_expandRadius(&self, &bc) }
	
	func inside(_ v: TSVector2f) -> Bool { var b = self, v = v; return tsBoundCirclef_inside1(&b, &v) }
	func inside(_ bc: TSBoundCirclef) -> Bool { var b = self, bc = bc; return tsBoundCirclef_inside(&b, &bc) }
	
	func distance(_ v: TSVector2f) -> Float32 { var b = self, v = v; return tsBoundCirclef_distance(&b, &v) }
}

public func *(_ m: TSMatrix4x3f, _ b: TSBoundCirclef) -> TSBoundCirclef { var ret = TSBoundCirclef(), m = m, b = b; tsMatrix4x3f_mul_bc(&ret, &m, &b); return ret }
public func *(_ m: TSMatrix4x4f, _ b: TSBoundCirclef) -> TSBoundCirclef { var ret = TSBoundCirclef(), m = m, b = b; tsMatrix4x4f_mul_bc(&ret, &m, &b); return ret }

/*
 */
public extension TSBoundCircled {
	
	init(_ center: TSVector2d, _ radius: Float64) { self.init(); self.center = center; self.radius = radius }
	init(_ bc: TSBoundCircled) { self.init(); self.center = bc.center; self.radius = bc.radius }
	init(_ bc: TSBoundCirclef) { var bc = bc; self.init(); tsBoundCircled_set_bcf(&self, &bc) }
	init(_ br: TSBoundRectd) { var br = br; self.init(); tsBoundCircled_set_br(&self, &br) }
	
	mutating func expand(_ v: TSVector2d) { var v = v; tsBoundCircled_expand1(&self, &v) }
	mutating func expand(_ bc: TSBoundCircled) { var bc = bc; tsBoundCircled_expand(&self, &bc) }
	
	mutating func expandRadius(_ v: TSVector2d) { var v = v; tsBoundCircled_expandRadius1(&self, &v) }
	mutating func expandRadius(_ bc: TSBoundCircled) { var bc = bc; tsBoundCircled_expandRadius(&self, &bc) }
	
	func inside(_ v: TSVector2d) -> Bool { var b = self, v = v; return tsBoundCircled_inside1(&b, &v) }
	func inside(_ bc: TSBoundCircled) -> Bool { var b = self, bc = bc; return tsBoundCircled_inside(&b, &bc) }
	
	func distance(_ v: TSVector2d) -> Float64 { var b = self, v = v; return tsBoundCircled_distance(&b, &v) }
}

public func *(_ m: TSMatrix4x3d, _ b: TSBoundCircled) -> TSBoundCircled { var ret = TSBoundCircled(), m = m, b = b; tsMatrix4x3d_mul_bc(&ret, &m, &b); return ret }
public func *(_ m: TSMatrix4x4d, _ b: TSBoundCircled) -> TSBoundCircled { var ret = TSBoundCircled(), m = m, b = b; tsMatrix4x4d_mul_bc(&ret, &m, &b); return ret }

/*
 */
public extension TSBoundBoxf {
	
	init(_ min: TSVector3f, _ max: TSVector3f) { self.init(); self.min = min; self.max = max }
	init(_ bb: TSBoundBoxf) { self.init(); self.min = bb.min; self.max = bb.max }
	init(_ bb: TSBoundBoxd) { var bb = bb; self.init(); tsBoundBoxf_set_bbd(&self, &bb) }
	init(_ bs: TSBoundSpheref) { var bs = bs; self.init(); tsBoundBoxf_set_bs(&self, &bs) }
	
	mutating func expand(_ v: TSVector3f) { var v = v; tsBoundBoxf_expand1(&self, &v) }
	mutating func expand(_ bb: TSBoundBoxf) { var bb = bb; tsBoundBoxf_expand(&self, &bb) }
	
	func inside(_ v: TSVector3f) -> Bool { var b = self, v = v; return tsBoundBoxf_inside1(&b, &v) }
	func inside(_ bb: TSBoundBoxf) -> Bool { var b = self, bb = bb; return tsBoundBoxf_inside(&b, &bb) }
	
	func distance(_ v: TSVector3f) -> Float32 { var b = self, v = v; return tsBoundBoxf_distance(&b, &v) }
}

public func *(_ m: TSMatrix4x3f, _ b: TSBoundBoxf) -> TSBoundBoxf { var ret = TSBoundBoxf(), m = m, b = b; tsMatrix4x3f_mul_bb(&ret, &m, &b); return ret }
public func *(_ m: TSMatrix4x4f, _ b: TSBoundBoxf) -> TSBoundBoxf { var ret = TSBoundBoxf(), m = m, b = b; tsMatrix4x4f_mul_bb(&ret, &m, &b); return ret }

/*
 */
public extension TSBoundBoxd {
	
	init(_ min: TSVector3d, _ max: TSVector3d) { self.init(); self.min = min; self.max = max }
	init(_ bb: TSBoundBoxd) { self.init(); self.min = bb.min; self.max = bb.max }
	init(_ bb: TSBoundBoxf) { var bb = bb; self.init(); tsBoundBoxd_set_bbf(&self, &bb) }
	init(_ bs: TSBoundSphered) { var bs = bs; self.init(); tsBoundBoxd_set_bs(&self, &bs) }
	
	mutating func expand(_ v: TSVector3d) { var v = v; tsBoundBoxd_expand1(&self, &v) }
	mutating func expand(_ bb: TSBoundBoxd) { var bb = bb; tsBoundBoxd_expand(&self, &bb) }
	
	func inside(_ v: TSVector3d) -> Bool { var b = self, v = v; return tsBoundBoxd_inside1(&b, &v) }
	func inside(_ bb: TSBoundBoxd) -> Bool { var b = self, bb = bb; return tsBoundBoxd_inside(&b, &bb) }
	
	func distance(_ v: TSVector3d) -> Float64 { var b = self, v = v; return tsBoundBoxd_distance(&b, &v) }
}

public func *(_ m: TSMatrix4x3d, _ b: TSBoundBoxd) -> TSBoundBoxd { var ret = TSBoundBoxd(), m = m, b = b; tsMatrix4x3d_mul_bb(&ret, &m, &b); return ret }
public func *(_ m: TSMatrix4x4d, _ b: TSBoundBoxd) -> TSBoundBoxd { var ret = TSBoundBoxd(), m = m, b = b; tsMatrix4x4d_mul_bb(&ret, &m, &b); return ret }

/*
 */
public extension TSBoundSpheref {
	
	init(_ center: TSVector3f, _ radius: Float32) { self.init(); self.center = center; self.radius = radius }
	init(_ bs: TSBoundSpheref) { self.init(); self.center = bs.center; self.radius = bs.radius }
	init(_ bs: TSBoundSphered) { var bs = bs; self.init(); tsBoundSpheref_set_bsd(&self, &bs) }
	init(_ bb: TSBoundBoxf) { var bb = bb; self.init(); tsBoundSpheref_set_bb(&self, &bb) }
	
	mutating func expand(_ v: TSVector3f) { var v = v; tsBoundSpheref_expand1(&self, &v) }
	mutating func expand(_ bs: TSBoundSpheref) { var bs = bs; tsBoundSpheref_expand(&self, &bs) }
	
	mutating func expandRadius(_ v: TSVector3f) { var v = v; tsBoundSpheref_expandRadius1(&self, &v) }
	mutating func expandRadius(_ bs: TSBoundSpheref) { var bs = bs; tsBoundSpheref_expandRadius(&self, &bs) }
	
	func inside(_ v: TSVector3f) -> Bool { var b = self, v = v; return tsBoundSpheref_inside1(&b, &v) }
	func inside(_ bs: TSBoundSpheref) -> Bool { var b = self, bs = bs; return tsBoundSpheref_inside(&b, &bs) }
	
	func distance(_ v: TSVector3f) -> Float32 { var b = self, v = v; return tsBoundSpheref_distance(&b, &v) }
}

public func *(_ m: TSMatrix4x3f, _ b: TSBoundSpheref) -> TSBoundSpheref { var ret = TSBoundSpheref(), m = m, b = b; tsMatrix4x3f_mul_bs(&ret, &m, &b); return ret }
public func *(_ m: TSMatrix4x4f, _ b: TSBoundSpheref) -> TSBoundSpheref { var ret = TSBoundSpheref(), m = m, b = b; tsMatrix4x4f_mul_bs(&ret, &m, &b); return ret }

/*
 */
public extension TSBoundSphered {
	
	init(_ center: TSVector3d, _ radius: Float64) { self.init(); self.center = center; self.radius = radius }
	init(_ bs: TSBoundSphered) { self.init(); self.center = bs.center; self.radius = bs.radius }
	init(_ bs: TSBoundSpheref) { var bs = bs; self.init(); tsBoundSphered_set_bsf(&self, &bs) }
	init(_ bb: TSBoundBoxd) { var bb = bb; self.init(); tsBoundSphered_set_bb(&self, &bb) }
	
	mutating func expand(_ v: TSVector3d) { var v = v; tsBoundSphered_expand1(&self, &v) }
	mutating func expand(_ bs: TSBoundSphered) { var bs = bs; tsBoundSphered_expand(&self, &bs) }
	
	mutating func expandRadius(_ v: TSVector3d) { var v = v; tsBoundSphered_expandRadius1(&self, &v) }
	mutating func expandRadius(_ bs: TSBoundSphered) { var bs = bs; tsBoundSphered_expandRadius(&self, &bs) }
	
	func inside(_ v: TSVector3d) -> Bool { var b = self, v = v; return tsBoundSphered_inside1(&b, &v) }
	func inside(_ bs: TSBoundSphered) -> Bool { var b = self, bs = bs; return tsBoundSphered_inside(&b, &bs) }
	
	func distance(_ v: TSVector3d) -> Float64 { var b = self, v = v; return tsBoundSphered_distance(&b, &v) }
}

public func *(_ m: TSMatrix4x3d, _ b: TSBoundSphered) -> TSBoundSphered { var ret = TSBoundSphered(), m = m, b = b; tsMatrix4x3d_mul_bs(&ret, &m, &b); return ret }
public func *(_ m: TSMatrix4x4d, _ b: TSBoundSphered) -> TSBoundSphered { var ret = TSBoundSphered(), m = m, b = b; tsMatrix4x4d_mul_bs(&ret, &m, &b); return ret }

/*
 */
public extension TSBoundFrustumf {
	
	init(_ bf: TSBoundFrustumd) { var bf = bf; self.init(); tsBoundFrustumf_set_bfd(&self, &bf) }
	init(_ p: TSMatrix4x4f, _ m: TSMatrix4x4f, _ a: Float32 = 1.0) { self.init(); self.set(p, m, a) }
	
	mutating func set(_ p: TSMatrix4x4f, _ m: TSMatrix4x4f, _ a: Float32 = 1.0) { var p = p, m = m; tsBoundFrustumf_set(&self, &p, &m, a) }
	
	func inside(_ bb: TSBoundBoxf) -> Bool { var b = self, bb = bb; return tsBoundFrustumf_inside_bb(&b, &bb) }
	func inside(_ bs: TSBoundSpheref) -> Bool { var b = self, bs = bs; return tsBoundFrustumf_inside_bs(&b, &bs) }
}

/*
 */
public extension TSBoundFrustumd {
	
	init(_ bf: TSBoundFrustumf) { var bf = bf; self.init(); tsBoundFrustumd_set_bff(&self, &bf) }
	init(_ p: TSMatrix4x4d, _ m: TSMatrix4x4d, _ a: Float64 = 1.0) { self.init(); self.set(p, m, a) }
	
	mutating func set(_ p: TSMatrix4x4d, _ m: TSMatrix4x4d, _ a: Float64 = 1.0) { var p = p, m = m; tsBoundFrustumd_set(&self, &p, &m, a) }
	
	func inside(_ bb: TSBoundBoxd) -> Bool { var b = self, bb = bb; return tsBoundFrustumd_inside_bb(&b, &bb) }
	func inside(_ bs: TSBoundSphered) -> Bool { var b = self, bs = bs; return tsBoundFrustumd_inside_bs(&b, &bs) }
}

/*****************************************************************************\
 *
 * Interface
 *
\*****************************************************************************/

/*
 */
public extension TSRect {
	
	init(_ value : Float32) { self.init(); self.left = value; self.right = value; self.bottom = value; self.top = value }
	init(_ horizontal: Float32, _ vertical: Float32) { self.init(); self.left = horizontal; self.right = horizontal; self.bottom = vertical; self.top = vertical }
	init(_ left: Float32, _ right: Float32, _ bottom: Float32, _ top: Float32) { self.init(); self.left = left; self.right = right; self.bottom = bottom; self.top = top }
}

/*
 */
public extension TSFontStyle {
	
	init(_ size: UInt32) { self.init(); self.size = size; self.scale = 100; self.fixed = 0; self.kerning = 1; self.spacing = Vector2f.zero; self.color = Color.white; self.offset = Vector3f.zero; self.shadow = Color.black }
	init(_ color: Color) { self.init(); self.size = 16; self.scale = 100; self.fixed = 0; self.kerning = 1; self.spacing = Vector2f.zero; self.color = color; self.offset = Vector3f.zero; self.shadow = Color.black }
	init(_ size: UInt32, _ color: Color) { self.init(); self.size = size; self.scale = 100; self.fixed = 0; self.kerning = 1; self.spacing = Vector2f.zero; self.color = color; self.offset = Vector3f.zero; self.shadow = Color.black }
}

/*
 */
public extension TSStrokeStyle {
	
	init(_ width: Float32) { self.init(); self.width = width; self.offset = 0.0; self.color = Color.white }
	init(_ color: Color) { self.init(); self.width = 0.0; self.offset = 0.0; self.color = color }
	init(_ width: Float32, _ offset: Float32) { self.init(); self.width = width; self.offset = offset; self.color = Color.white }
	init(_ width: Float32, _ color: Color) { self.init(); self.width = width; self.offset = 0.0; self.color = color }
	init(_ width: Float32, _ offset: Float32, _ color : Color) { self.init(); self.width = width; self.offset = offset; self.color = color }
}

/*
 */
public extension TSGradientStyle {
	
	init(_ c0: Color, _ c1: Color) { self.init(); self.radius = 0.0; self.length = 0.0; self.center = Vector2f.zero; self.axis = Vector2f.zero; self.color_0 = c0; self.color_1 = c1 }
	init(_ radius: Float32, _ center: Vector2f) { self.init(); self.radius = radius; self.length = 0.0; self.center = center; self.axis = Vector2f.zero; self.color_0 = Color.white; self.color_1 = Color.white }
	init(_ length: Float32, _ center: Vector2f, _ axis: Vector2f) { self.init(); self.radius = 0.0; self.length = length; self.center = center; self.axis = axis; self.color_0 = Color.white; self.color_1 = Color.white }
	init(_ radius: Float32, _ center: Vector2f, _ c0: Color, _ c1: Color) { self.init(); self.radius = radius; self.length = 0.0; self.center = center; self.axis = Vector2f.zero; self.color_0 = c0; self.color_1 = c1 }
	init(_ length: Float32, _ center: Vector2f, _ axis: Vector2f, _ c0: Color, _ c1: Color) { self.init(); self.radius = 0.0; self.length = length; self.center = center; self.axis = axis; self.color_0 = c0; self.color_1 = c1 }
}

/*****************************************************************************\
 *
 * Format
 *
\*****************************************************************************/

/*
 */
public extension MeshAttribute {
	
	func set<Type>(_ index: UInt32, _ value: Type) {
		let stride = Int(stride())
		withUnsafePointer(to: value) { src in
			(data() + stride * Int(index)).copyMemory(from: src, byteCount: MemoryLayout<Type>.size)
		}
	}
}

/*****************************************************************************\
 *
 * Platform
 *
\*****************************************************************************/

/*
 */
public extension TSOrigin {
	
	init(_ x: UInt32, _ y: UInt32) { self.init(); self.x = x; self.y = y; self.z = 0 }
	init(_ x: UInt32, _ y: UInt32, _ z: UInt32) { self.init(); self.x = x; self.y = y; self.z = 0 }
}

/*
 */
public extension TSSize {
	
	init(_ width: UInt32, _ height: UInt32) { self.init(); self.width = width; self.height = height; self.depth = 1 }
	init(_ width: UInt32, _ height: UInt32, _ depth: UInt32) { self.init(); self.width = width; self.height = height; self.depth = depth }
}

/*
 */
public extension TSRegion {
	
	init(_ width: UInt32, _ height: UInt32) { self.init(); self.x = 0; self.y = 0; self.z = 0; self.width = width; self.height = height; self.depth = 1 }
	init(_ width: UInt32, _ height: UInt32, _ depth: UInt32) { self.init(); self.x = 0; self.y = 0; self.z = 0; self.width = width; self.height = height; self.depth = depth }
	init(_ x: UInt32, _ y: UInt32, _ width: UInt32, _ height: UInt32) { self.init(); self.x = x; self.y = y; self.z = 0; self.width = width; self.height = height; self.depth = 1 }
	init(_ x: UInt32, _ y: UInt32, _ z: UInt32, _ width: UInt32, _ height: UInt32, _ depth: UInt32) { self.init(); self.x = x; self.y = y; self.z = z; self.width = width; self.height = height; self.depth = depth }
}

/*
 */
public extension App {
	
	convenience override init() {
		self.init(CommandLine.arguments)
	}
	convenience init(_ arguments: [String]) {
		var args = arguments.compactMap{strdup($0)}
		self.init(Int32(args.count), &args)
	}
}

/*
 */
public extension Command {
	
	func setUniform<Type>(_ index: UInt32, _ data: inout Type) {
		withUnsafePointer(to: data) { src in
			setUniformData(index, src, MemoryLayout<Type>.size)
		}
	}
	func setUniform<Type>(_ index: UInt32, _ data: inout [Type]) {
		data.withUnsafeBytes { src in
			setUniformData(index, src.baseAddress!, data.count * MemoryLayout<Type>.size)
		}
	}
	
	func setStorage<Type>(_ index: UInt32, _ data: inout Type) {
		withUnsafePointer(to: data) { src in
			setStorageData(index, src, MemoryLayout<Type>.size)
		}
	}
	func setStorage<Type>(_ index: UInt32, _ data: inout [Type]) {
		data.withUnsafeBytes { src in
			setStorageData(index, src.baseAddress!, data.count * MemoryLayout<Type>.size)
		}
	}
	
	func setVertices<Type>(_ index: UInt32, _ data: inout [Type]) {
		data.withUnsafeBytes { src in
			setVertexData(index, src.baseAddress!, data.count * MemoryLayout<Type>.size)
		}
	}
	
	func setIndices(_ data: inout [UInt32]) {
		setIndexData(Format.Ru32, data, data.count * 4)
	}
	func setIndices(_ data: inout [UInt16]) {
		setIndexData(Format.Ru16, data, data.count * 2)
	}
	func setIndices<Type>(_ format: Format, _ data: inout [Type]) {
		data.withUnsafeBytes { src in
			setIndexData(format, src.baseAddress!, data.count * MemoryLayout<Type>.size)
		}
	}
}

/*
 */
public extension Compute {
	
	func setUniform<Type>(_ index: UInt32, _ data: inout Type) {
		withUnsafePointer(to: data) { src in
			setUniformData(index, src, MemoryLayout<Type>.size)
		}
	}
	func setUniform<Type>(_ index: UInt32, _ data: inout [Type]) {
		data.withUnsafeBytes { src in
			setUniformData(index, src.baseAddress!, data.count * MemoryLayout<Type>.size)
		}
	}
	
	func setStorage<Type>(_ index: UInt32, _ data: inout Type) {
		withUnsafePointer(to: data) { src in
			setStorageData(index, src, MemoryLayout<Type>.size)
		}
	}
	func setStorage<Type>(_ index: UInt32, _ data: inout [Type]) {
		data.withUnsafeBytes { src in
			setStorageData(index, src.baseAddress!, data.count * MemoryLayout<Type>.size)
		}
	}
}

/*****************************************************************************\
 *
 * Parallel
 *
\*****************************************************************************/

/*
 */
public extension TSTensor {
	
	init(_ width: UInt32 = 0) { self.init(); kernel = 2; stride = 1; dilation = 1; scale = 1.0; self.width = width; height = 1; depth = 1; layers = 1 }
	init(_ buffer: Buffer) { self.init(); self.buffer = buffer.getSelfPtr(); kernel = 2; stride = 1; dilation = 1; scale = 1.0; height = 1; depth = 1; layers = 1 }
	init(_ buffer: Buffer, _ offset: Int = 0) { self.init(); self.buffer = buffer.getSelfPtr(); self.offset = offset; kernel = 2; stride = 1; dilation = 1; scale = 1.0; height = 1; depth = 1; layers = 1 }
	init(_ buffer: Buffer, _ format: Format, _ width: UInt32 = 0, _ height : UInt32 = 1, _ depth: UInt32 = 1, _ layers: UInt32 = 1) { self.init(); self.buffer = buffer.getSelfPtr(); self.format = UInt32(format.rawValue); kernel = 2; stride = 1; dilation = 1; scale = 1.0; self.width = width; self.height = height; self.depth = depth; self.layers = layers }
	init(_ tensor: TSTensor, _ width: UInt32 = 0, _ height : UInt32 = 1, _ depth: UInt32 = 1, _ layers: UInt32 = 1) { self.init(); buffer = tensor.buffer; format = tensor.format; offset = tensor.offset; kernel = 2; stride = 1; dilation = 1; scale = 1.0; self.width = width; self.height = height; self.depth = depth; self.layers = layers }
	
	func setAxis(_ axis: UInt32) -> TSTensor { var ret = self; ret.axis = axis; return ret }
	func setKernel(_ kernel: UInt32) -> TSTensor { var ret = self; ret.kernel = kernel; return ret }
	func setStride(_ stride: UInt32) -> TSTensor { var ret = self; ret.stride = stride; return ret }
	func setPadding(_ padding: UInt32) -> TSTensor { var ret = self; ret.padding = padding; return ret }
	func setDilation(_ dilation: UInt32) -> TSTensor { var ret = self; ret.dilation = dilation; return ret }
	
	func setScaleBias(_ scale: Float32, _ bias: Float32) -> TSTensor { var ret = self; ret.scale = scale; ret.bias = bias; return ret }
	func setScale(_ scale: Float32) -> TSTensor { var ret = self; ret.scale = scale; return ret }
	func setBias(_ bias: Float32) -> TSTensor { var ret = self; ret.bias = bias; return ret }
}

extension TSTensor : CustomStringConvertible {
	public var description: String { "[\(width)x\(height)x\(depth)x\(layers)]" }
}

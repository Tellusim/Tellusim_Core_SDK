// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

/*****************************************************************************\
 *
 * Scalars
 *
\*****************************************************************************/

/* 32-bit signed integer numbers
 */
public func min(_ v0: Int32, _ v1: Int32, _ v2: Int32) -> Int32 { v0 < v1 ? min(v0, v2) : min(v1, v2) }
public func max(_ v0: Int32, _ v1: Int32, _ v2: Int32) -> Int32 { v0 < v1 ? max(v1, v2) : max(v0, v2) }
public func min(_ v0: Int32, _ v1: Int32, _ v2: Int32, _ v3: Int32) -> Int32 { v0 < v1 ? min(v0, v2, v3) : min(v1, v2, v3) }
public func max(_ v0: Int32, _ v1: Int32, _ v2: Int32, _ v3: Int32) -> Int32 { v0 < v1 ? max(v1, v2, v3) : max(v0, v2, v3) }
public func mid(_ v0: Int32, _ v1: Int32, _ v2: Int32) -> Int32 { v0 < v1 ? (v1 < v2 ? v1 : max(v0, v2)) : (v0 < v2 ? v0 : max(v1, v2)) }
public func clamp(_ v: Int32, _ v0: Int32, _ v1: Int32) -> Int32 { min(max(v, v0), v1) }

/* 64-bit signed integer numbers
 */
public func min(_ v0: Int64, _ v1: Int64, _ v2: Int64) -> Int64 { v0 < v1 ? min(v0, v2) : min(v1, v2) }
public func max(_ v0: Int64, _ v1: Int64, _ v2: Int64) -> Int64 { v0 < v1 ? max(v1, v2) : max(v0, v2) }
public func min(_ v0: Int64, _ v1: Int64, _ v2: Int64, _ v3: Int64) -> Int64 { v0 < v1 ? min(v0, v2, v3) : min(v1, v2, v3) }
public func max(_ v0: Int64, _ v1: Int64, _ v2: Int64, _ v3: Int64) -> Int64 { v0 < v1 ? max(v1, v2, v3) : max(v0, v2, v3) }
public func mid(_ v0: Int64, _ v1: Int64, _ v2: Int64) -> Int64 { v0 < v1 ? (v1 < v2 ? v1 : max(v0, v2)) : (v0 < v2 ? v0 : max(v1, v2)) }
public func clamp(_ v: Int64, _ v0: Int64, _ v1: Int64) -> Int64 { min(max(v, v0), v1) }

/* 32-bit unsigned integer numbers
 */
public func ispot(_ x: UInt32) -> Bool { (x & (x - 1)) == 0 }
public func isaligned(_ a: UInt32, _ b: UInt32) -> Bool { ispot(b) ? ((a & (b - 1)) == 0) : ((a / b) * b == a) }
public func npot(_ x: UInt32) -> UInt32 { var ret = UInt32(1); while ret < x { ret += ret }; return ret }
public func align(_ a: UInt32, _ b: UInt32) -> UInt32 { ispot(b) ? ((a + b - 1) & ~(b - 1)) : (((a + b - 1) / b) * b) }
public func udiv(_ a: UInt32, _ b: UInt32) -> UInt32 { (a + b - 1) / b }

public func min(_ v0: UInt32, _ v1: UInt32, _ v2: UInt32) -> UInt32 { v0 < v1 ? min(v0, v2) : min(v1, v2) }
public func max(_ v0: UInt32, _ v1: UInt32, _ v2: UInt32) -> UInt32 { v0 < v1 ? max(v1, v2) : max(v0, v2) }
public func min(_ v0: UInt32, _ v1: UInt32, _ v2: UInt32, _ v3: UInt32) -> UInt32 { v0 < v1 ? min(v0, v2, v3) : min(v1, v2, v3) }
public func max(_ v0: UInt32, _ v1: UInt32, _ v2: UInt32, _ v3: UInt32) -> UInt32 { v0 < v1 ? max(v1, v2, v3) : max(v0, v2, v3) }
public func mid(_ v0: UInt32, _ v1: UInt32, _ v2: UInt32) -> UInt32 { v0 < v1 ? (v1 < v2 ? v1 : max(v0, v2)) : (v0 < v2 ? v0 : max(v1, v2)) }
public func clamp(_ v: UInt32, _ v0: UInt32, _ v1: UInt32) -> UInt32 { min(max(v, v0), v1) }

/* 64-bit unsigned integer numbers
 */
public func ispot(_ x: UInt64) -> Bool { (x & (x - 1)) == 0 }
public func isaligned(_ a: UInt64, _ b: UInt64) -> Bool { ispot(b) ? ((a & (b - 1)) == 0) : ((a / b) * b == a) }
public func npot(_ x: UInt64) -> UInt64 { var ret = UInt64(1); while ret < x { ret += ret }; return ret }
public func align(_ a: UInt64, _ b: UInt64) -> UInt64 { ispot(b) ? ((a + b - 1) & ~(b - 1)) : (((a + b - 1) / b) * b) }
public func udiv(_ a: UInt64, _ b: UInt64) -> UInt64 { (a + b - 1) / b }

public func min(_ v0: UInt64, _ v1: UInt64, _ v2: UInt64) -> UInt64 { v0 < v1 ? min(v0, v2) : min(v1, v2) }
public func max(_ v0: UInt64, _ v1: UInt64, _ v2: UInt64) -> UInt64 { v0 < v1 ? max(v1, v2) : max(v0, v2) }
public func min(_ v0: UInt64, _ v1: UInt64, _ v2: UInt64, _ v3: UInt64) -> UInt64 { v0 < v1 ? min(v0, v2, v3) : min(v1, v2, v3) }
public func max(_ v0: UInt64, _ v1: UInt64, _ v2: UInt64, _ v3: UInt64) -> UInt64 { v0 < v1 ? max(v1, v2, v3) : max(v0, v2, v3) }
public func mid(_ v0: UInt64, _ v1: UInt64, _ v2: UInt64) -> UInt64 { v0 < v1 ? (v1 < v2 ? v1 : max(v0, v2)) : (v0 < v2 ? v0 : max(v1, v2)) }
public func clamp(_ v: UInt64, _ v0: UInt64, _ v1: UInt64) -> UInt64 { min(max(v, v0), v1) }

/* 32-bit floating point numbers
 */
public func min(_ v0: Float32, _ v1: Float32, _ v2: Float32) -> Float32 { v0 < v1 ? min(v0, v2) : min(v1, v2) }
public func max(_ v0: Float32, _ v1: Float32, _ v2: Float32) -> Float32 { v0 < v1 ? max(v1, v2) : max(v0, v2) }
public func min(_ v0: Float32, _ v1: Float32, _ v2: Float32, _ v3: Float32) -> Float32 { v0 < v1 ? min(v0, v2, v3) : min(v1, v2, v3) }
public func max(_ v0: Float32, _ v1: Float32, _ v2: Float32, _ v3: Float32) -> Float32 { v0 < v1 ? max(v1, v2, v3) : max(v0, v2, v3) }
public func mid(_ v0: Float32, _ v1: Float32, _ v2: Float32) -> Float32 { v0 < v1 ? (v1 < v2 ? v1 : max(v0, v2)) : (v0 < v2 ? v0 : max(v1, v2)) }
public func clamp(_ v: Float32, _ v0: Float32, _ v1: Float32) -> Float32 { min(max(v, v0), v1) }
public func saturate(_ v: Float32) -> Float32 { min(max(v, 0.0), 1.0) }

public func lerp(_ v0: Float32, _ v1: Float32, _ k: Float32) -> Float32 { v0 + (v1 - v0) * k }

/* 64-bit floating point numbers
 */
public func min(_ v0: Float64, _ v1: Float64, _ v2: Float64) -> Float64 { v0 < v1 ? min(v0, v2) : min(v1, v2) }
public func max(_ v0: Float64, _ v1: Float64, _ v2: Float64) -> Float64 { v0 < v1 ? max(v1, v2) : max(v0, v2) }
public func min(_ v0: Float64, _ v1: Float64, _ v2: Float64, _ v3: Float64) -> Float64 { v0 < v1 ? min(v0, v2, v3) : min(v1, v2, v3) }
public func max(_ v0: Float64, _ v1: Float64, _ v2: Float64, _ v3: Float64) -> Float64 { v0 < v1 ? max(v1, v2, v3) : max(v0, v2, v3) }
public func mid(_ v0: Float64, _ v1: Float64, _ v2: Float64) -> Float64 { v0 < v1 ? (v1 < v2 ? v1 : max(v0, v2)) : (v0 < v2 ? v0 : max(v1, v2)) }
public func clamp(_ v: Float64, _ v0: Float64, _ v1: Float64) -> Float64 { min(max(v, v0), v1) }
public func saturate(_ v: Float64) -> Float64 { min(max(v, 0.0), 1.0) }

public func lerp(_ v0: Float64, _ v1: Float64, _ k: Float64) -> Float64 { v0 + (v1 - v0) * k }

/* packed floating point numbers
 */
public func f32tof16(_ f: Float32) -> UInt16 { ts_f32tof16(f) }
public func f16tof32(_ h: UInt16) -> Float32 { ts_f16tof32(h) }
public func f32tof21(_ f: Float32) -> UInt32 { ts_f32tof21(f) }
public func f21tof32(_ h: UInt32) -> Float32 { ts_f21tof32(h) }
public func f32tof24(_ f: Float32) -> UInt32 { ts_f32tof24(f) }
public func f24tof32(_ h: UInt32) -> Float32 { ts_f24tof32(h) }

/*****************************************************************************\
 *
 * Vector2i
 *
\*****************************************************************************/

/*
 */
public extension TSVector2i {
	
	init(_ v: Int32) { self.init(); self.x = v; self.y = v }
	init(_ x: Int32, _ y: Int32) { self.init(); self.x = x; self.y = y }
	init(_ v: TSVector2u) { self.init(); self.x = Int32(v.x); self.y = Int32(v.y) }
	init(_ v: TSVector2f) { self.init(); self.x = Int32(v.x); self.y = Int32(v.y) }
	init(_ v: TSVector2d) { self.init(); self.x = Int32(v.x); self.y = Int32(v.y) }
	init(_ v: TSVector3i) { self.init(); self.x = v.x; self.y = v.y }
	init(_ v: TSVector4i) { self.init(); self.x = v.x; self.y = v.y }
	init(_ v: [Int32]) { self.init(); self.x = v[0]; self.y = v[1] }
	
	static let zero = TSVector2i(0)
	static let one = TSVector2i(1)
}

extension TSVector2i : CustomStringConvertible {
	public var description: String { "(\(x) \(y))" }
}

/*
 */
public prefix func -(v: TSVector2i) -> TSVector2i { TSVector2i(-v.x, -v.y) }

public func *(v0: TSVector2i, v1: Int32) -> TSVector2i { TSVector2i(v0.x * v1, v0.y * v1) }
public func /(v0: TSVector2i, v1: Int32) -> TSVector2i { TSVector2i(v0.x / v1, v0.y / v1) }
public func +(v0: TSVector2i, v1: Int32) -> TSVector2i { TSVector2i(v0.x + v1, v0.y + v1) }
public func -(v0: TSVector2i, v1: Int32) -> TSVector2i { TSVector2i(v0.x - v1, v0.y - v1) }
public func &(v0: TSVector2i, v1: Int32) -> TSVector2i { TSVector2i(v0.x & v1, v0.y & v1) }
public func |(v0: TSVector2i, v1: Int32) -> TSVector2i { TSVector2i(v0.x | v1, v0.y | v1) }
public func ^(v0: TSVector2i, v1: Int32) -> TSVector2i { TSVector2i(v0.x ^ v1, v0.y ^ v1) }
public func <<(v0: TSVector2i, v1: Int32) -> TSVector2i { TSVector2i(v0.x << v1, v0.y << v1) }
public func >>(v0: TSVector2i, v1: Int32) -> TSVector2i { TSVector2i(v0.x >> v1, v0.y >> v1) }

public func *(v0: TSVector2i, v1: TSVector2i) -> TSVector2i { TSVector2i(v0.x * v1.x, v0.y * v1.y) }
public func /(v0: TSVector2i, v1: TSVector2i) -> TSVector2i { TSVector2i(v0.x / v1.x, v0.y / v1.y) }
public func +(v0: TSVector2i, v1: TSVector2i) -> TSVector2i { TSVector2i(v0.x + v1.x, v0.y + v1.y) }
public func -(v0: TSVector2i, v1: TSVector2i) -> TSVector2i { TSVector2i(v0.x - v1.x, v0.y - v1.y) }
public func &(v0: TSVector2i, v1: TSVector2i) -> TSVector2i { TSVector2i(v0.x & v1.x, v0.y & v1.y) }
public func |(v0: TSVector2i, v1: TSVector2i) -> TSVector2i { TSVector2i(v0.x | v1.x, v0.y | v1.y) }
public func ^(v0: TSVector2i, v1: TSVector2i) -> TSVector2i { TSVector2i(v0.x ^ v1.x, v0.y ^ v1.y) }

/*
 */
public func abs(_ v: TSVector2i) -> TSVector2i { TSVector2i(abs(v.x), abs(v.y)) }

public func min(_ v0: TSVector2i, _ v1: TSVector2i) -> TSVector2i { TSVector2i(min(v0.x, v1.x), min(v0.y, v1.y)) }
public func max(_ v0: TSVector2i, _ v1: TSVector2i) -> TSVector2i { TSVector2i(max(v0.x, v1.x), max(v0.y, v1.y)) }

public func clamp(_ v: TSVector2i, _ v0: TSVector2i, _ v1: TSVector2i) -> TSVector2i { TSVector2i(clamp(v.x, v0.x, v1.x), clamp(v.y, v0.y, v1.y)) }

/*****************************************************************************\
 *
 * Vector2u
 *
\*****************************************************************************/

/*
 */
public extension TSVector2u {
	
	init(_ v: UInt32) { self.init(); self.x = v; self.y = v }
	init(_ x: UInt32, _ y: UInt32) { self.init(); self.x = x; self.y = y }
	init(_ v: TSVector2i) { self.init(); self.x = UInt32(v.x); self.y = UInt32(v.y) }
	init(_ v: TSVector2f) { self.init(); self.x = UInt32(v.x); self.y = UInt32(v.y) }
	init(_ v: TSVector2d) { self.init(); self.x = UInt32(v.x); self.y = UInt32(v.y) }
	init(_ v: TSVector3u) { self.init(); self.x = v.x; self.y = v.y }
	init(_ v: TSVector4u) { self.init(); self.x = v.x; self.y = v.y }
	init(_ v: [UInt32]) { self.init(); self.x = v[0]; self.y = v[1] }
	
	static let zero = TSVector2u(0)
	static let one = TSVector2u(1)
}

extension TSVector2u : CustomStringConvertible {
	public var description: String { "(\(x) \(y))" }
}

/*
 */
public func *(v0: TSVector2u, v1: UInt32) -> TSVector2u { TSVector2u(v0.x * v1, v0.y * v1) }
public func /(v0: TSVector2u, v1: UInt32) -> TSVector2u { TSVector2u(v0.x / v1, v0.y / v1) }
public func +(v0: TSVector2u, v1: UInt32) -> TSVector2u { TSVector2u(v0.x + v1, v0.y + v1) }
public func -(v0: TSVector2u, v1: UInt32) -> TSVector2u { TSVector2u(v0.x - v1, v0.y - v1) }
public func &(v0: TSVector2u, v1: UInt32) -> TSVector2u { TSVector2u(v0.x & v1, v0.y & v1) }
public func |(v0: TSVector2u, v1: UInt32) -> TSVector2u { TSVector2u(v0.x | v1, v0.y | v1) }
public func ^(v0: TSVector2u, v1: UInt32) -> TSVector2u { TSVector2u(v0.x ^ v1, v0.y ^ v1) }
public func <<(v0: TSVector2u, v1: UInt32) -> TSVector2u { TSVector2u(v0.x << v1, v0.y << v1) }
public func >>(v0: TSVector2u, v1: UInt32) -> TSVector2u { TSVector2u(v0.x >> v1, v0.y >> v1) }

public func *(v0: TSVector2u, v1: TSVector2u) -> TSVector2u { TSVector2u(v0.x * v1.x, v0.y * v1.y) }
public func /(v0: TSVector2u, v1: TSVector2u) -> TSVector2u { TSVector2u(v0.x / v1.x, v0.y / v1.y) }
public func +(v0: TSVector2u, v1: TSVector2u) -> TSVector2u { TSVector2u(v0.x + v1.x, v0.y + v1.y) }
public func -(v0: TSVector2u, v1: TSVector2u) -> TSVector2u { TSVector2u(v0.x - v1.x, v0.y - v1.y) }
public func &(v0: TSVector2u, v1: TSVector2u) -> TSVector2u { TSVector2u(v0.x & v1.x, v0.y & v1.y) }
public func |(v0: TSVector2u, v1: TSVector2u) -> TSVector2u { TSVector2u(v0.x | v1.x, v0.y | v1.y) }
public func ^(v0: TSVector2u, v1: TSVector2u) -> TSVector2u { TSVector2u(v0.x ^ v1.x, v0.y ^ v1.y) }

/*
 */
public func min(_ v0: TSVector2u, _ v1: TSVector2u) -> TSVector2u { TSVector2u(min(v0.x, v1.x), min(v0.y, v1.y)) }
public func max(_ v0: TSVector2u, _ v1: TSVector2u) -> TSVector2u { TSVector2u(max(v0.x, v1.x), max(v0.y, v1.y)) }

public func clamp(_ v: TSVector2u, _ v0: TSVector2u, _ v1: TSVector2u) -> TSVector2u { TSVector2u(clamp(v.x, v0.x, v1.x), clamp(v.y, v0.y, v1.y)) }

/*****************************************************************************\
 *
 * Vector2f
 *
\*****************************************************************************/

/*
 */
public extension TSVector2f {
	
	init(_ v: Float32) { self.init(); self.x = v; self.y = v }
	init(_ x: Float32, _ y: Float32) { self.init(); self.x = x; self.y = y }
	init(_ v: TSVector2i) { self.init(); self.x = Float32(v.x); self.y = Float32(v.y) }
	init(_ v: TSVector2u) { self.init(); self.x = Float32(v.x); self.y = Float32(v.y) }
	init(_ v: TSVector2d) { self.init(); self.x = Float32(v.x); self.y = Float32(v.y) }
	init(_ v: TSVector3f) { self.init(); self.x = v.x; self.y = v.y }
	init(_ v: TSVector4f) { self.init(); self.x = v.x; self.y = v.y }
	init(_ v: [Float32]) { self.init(); self.x = v[0]; self.y = v[1] }
	
	static let zero = TSVector2f(0.0)
	static let one = TSVector2f(1.0)
}

extension TSVector2f : CustomStringConvertible {
	public var description: String { "(\(x) \(y))" }
}

/*
 */
public prefix func -(v: TSVector2f) -> TSVector2f { TSVector2f(-v.x, -v.y) }

public func *(v0: TSVector2f, v1: Float32) -> TSVector2f { TSVector2f(v0.x * v1, v0.y * v1) }
public func /(v0: TSVector2f, v1: Float32) -> TSVector2f { TSVector2f(v0.x / v1, v0.y / v1) }
public func +(v0: TSVector2f, v1: Float32) -> TSVector2f { TSVector2f(v0.x + v1, v0.y + v1) }
public func -(v0: TSVector2f, v1: Float32) -> TSVector2f { TSVector2f(v0.x - v1, v0.y - v1) }

public func *(v0: TSVector2f, v1: TSVector2f) -> TSVector2f { TSVector2f(v0.x * v1.x, v0.y * v1.y) }
public func /(v0: TSVector2f, v1: TSVector2f) -> TSVector2f { TSVector2f(v0.x / v1.x, v0.y / v1.y) }
public func +(v0: TSVector2f, v1: TSVector2f) -> TSVector2f { TSVector2f(v0.x + v1.x, v0.y + v1.y) }
public func -(v0: TSVector2f, v1: TSVector2f) -> TSVector2f { TSVector2f(v0.x - v1.x, v0.y - v1.y) }

/*
 */
public func abs(_ v: TSVector2f) -> TSVector2f { TSVector2f(abs(v.x), abs(v.y)) }

public func min(_ v0: TSVector2f, _ v1: TSVector2f) -> TSVector2f { TSVector2f(min(v0.x, v1.x), min(v0.y, v1.y)) }
public func max(_ v0: TSVector2f, _ v1: TSVector2f) -> TSVector2f { TSVector2f(max(v0.x, v1.x), max(v0.y, v1.y)) }

public func clamp(_ v: TSVector2f, _ v0: TSVector2f, _ v1: TSVector2f) -> TSVector2f { TSVector2f(clamp(v.x, v0.x, v1.x), clamp(v.y, v0.y, v1.y)) }
public func saturate(_ v: TSVector2f) -> TSVector2f { TSVector2f(saturate(v.x), saturate(v.y)) }

public func dot(_ v0: TSVector2f, _ v1: TSVector2f) -> Float32 { v0.x * v1.x + v0.y * v1.y }
public func cross(_ v0: TSVector2f, _ v1: TSVector2f) -> Float32 { v0.y * v1.x - v0.x * v1.y }

public func length2(_ v: TSVector2f) -> Float32 { v.x * v.x + v.y * v.y }
public func length(_ v: TSVector2f) -> Float32 { sqrt(length2(v)) }
public func normalize(_ v: TSVector2f) -> TSVector2f { v * (1.0 / length(v)) }

public func lerp(_ v0: TSVector2f, _ v1: TSVector2f, k: Float32) -> TSVector2f { v0 + (v1 - v0) * k }
public func lerp(_ v0: TSVector2f, _ v1: TSVector2f, k: TSVector2f) -> TSVector2f { v0 + (v1 - v0) * k }

/*****************************************************************************\
 *
 * Vector2d
 *
\*****************************************************************************/

/*
 */
public extension TSVector2d {
	
	init(_ v: Float64) { self.init(); self.x = v; self.y = v }
	init(_ x: Float64, _ y: Float64) { self.init(); self.x = x; self.y = y }
	init(_ v: TSVector2i) { self.init(); self.x = Float64(v.x); self.y = Float64(v.y) }
	init(_ v: TSVector2u) { self.init(); self.x = Float64(v.x); self.y = Float64(v.y) }
	init(_ v: TSVector2f) { self.init(); self.x = Float64(v.x); self.y = Float64(v.y) }
	init(_ v: TSVector3d) { self.init(); self.x = v.x; self.y = v.y }
	init(_ v: TSVector4d) { self.init(); self.x = v.x; self.y = v.y }
	init(_ v: [Float64]) { self.init(); self.x = v[0]; self.y = v[1] }
	
	static let zero = TSVector2d(0.0)
	static let one = TSVector2d(1.0)
}

extension TSVector2d : CustomStringConvertible {
	public var description: String { "(\(x) \(y))" }
}

/*
 */
public prefix func -(v: TSVector2d) -> TSVector2d { TSVector2d(-v.x, -v.y) }

public func *(v0: TSVector2d, v1: Float64) -> TSVector2d { TSVector2d(v0.x * v1, v0.y * v1) }
public func /(v0: TSVector2d, v1: Float64) -> TSVector2d { TSVector2d(v0.x / v1, v0.y / v1) }
public func +(v0: TSVector2d, v1: Float64) -> TSVector2d { TSVector2d(v0.x + v1, v0.y + v1) }
public func -(v0: TSVector2d, v1: Float64) -> TSVector2d { TSVector2d(v0.x - v1, v0.y - v1) }

public func *(v0: TSVector2d, v1: TSVector2d) -> TSVector2d { TSVector2d(v0.x * v1.x, v0.y * v1.y) }
public func /(v0: TSVector2d, v1: TSVector2d) -> TSVector2d { TSVector2d(v0.x / v1.x, v0.y / v1.y) }
public func +(v0: TSVector2d, v1: TSVector2d) -> TSVector2d { TSVector2d(v0.x + v1.x, v0.y + v1.y) }
public func -(v0: TSVector2d, v1: TSVector2d) -> TSVector2d { TSVector2d(v0.x - v1.x, v0.y - v1.y) }

/*
 */
public func abs(_ v: TSVector2d) -> TSVector2d { TSVector2d(abs(v.x), abs(v.y)) }

public func min(_ v0: TSVector2d, _ v1: TSVector2d) -> TSVector2d { TSVector2d(min(v0.x, v1.x), min(v0.y, v1.y)) }
public func max(_ v0: TSVector2d, _ v1: TSVector2d) -> TSVector2d { TSVector2d(max(v0.x, v1.x), max(v0.y, v1.y)) }

public func clamp(_ v: TSVector2d, _ v0: TSVector2d, _ v1: TSVector2d) -> TSVector2d { TSVector2d(clamp(v.x, v0.x, v1.x), clamp(v.y, v0.y, v1.y)) }
public func saturate(_ v: TSVector2d) -> TSVector2d { TSVector2d(saturate(v.x), saturate(v.y)) }

public func dot(_ v0: TSVector2d, _ v1: TSVector2d) -> Float64 { v0.x * v1.x + v0.y * v1.y }
public func cross(_ v0: TSVector2d, _ v1: TSVector2d) -> Float64 { v0.y * v1.x - v0.x * v1.y }

public func length2(_ v: TSVector2d) -> Float64 { v.x * v.x + v.y * v.y }
public func length(_ v: TSVector2d) -> Float64 { sqrt(length2(v)) }
public func normalize(_ v: TSVector2d) -> TSVector2d { v * (1.0 / length(v)) }

public func lerp(_ v0: TSVector2d, _ v1: TSVector2d, k: Float64) -> TSVector2d { v0 + (v1 - v0) * k }
public func lerp(_ v0: TSVector2d, _ v1: TSVector2d, k: TSVector2d) -> TSVector2d { v0 + (v1 - v0) * k }

/*****************************************************************************\
 *
 * Vector3i
 *
\*****************************************************************************/

/*
 */
public extension TSVector3i {
	
	init(_ v: Int32) { self.init(); self.x = v; self.y = v; self.z = v }
	init(_ x: Int32, _ y: Int32, _ z: Int32) { self.init(); self.x = x; self.y = y; self.z = z }
	init(_ v: TSVector2i, _ z: Int32) { self.init(); self.x = v.x; self.y = v.y; self.z = z }
	init(_ v: TSVector3u) { self.init(); self.x = Int32(v.x); self.y = Int32(v.y); self.z = Int32(v.z) }
	init(_ v: TSVector3f) { self.init(); self.x = Int32(v.x); self.y = Int32(v.y); self.z = Int32(v.z) }
	init(_ v: TSVector3d) { self.init(); self.x = Int32(v.x); self.y = Int32(v.y); self.z = Int32(v.z) }
	init(_ v: TSVector4i) { self.init(); self.x = v.x; self.y = v.y; self.z = v.z }
	init(_ v: [Int32]) { self.init(); self.x = v[0]; self.y = v[1]; self.z = v[2] }
	
	static let zero = TSVector3i(0)
	static let one = TSVector3i(1)
}

extension TSVector3i : CustomStringConvertible {
	public var description: String { "(\(x) \(y) \(z))" }
}

/*
 */
public prefix func -(v: TSVector3i) -> TSVector3i { TSVector3i(-v.x, -v.y, -v.z) }

public func *(v0: TSVector3i, v1: Int32) -> TSVector3i { TSVector3i(v0.x * v1, v0.y * v1, v0.z * v1) }
public func /(v0: TSVector3i, v1: Int32) -> TSVector3i { TSVector3i(v0.x / v1, v0.y / v1, v0.z / v1) }
public func +(v0: TSVector3i, v1: Int32) -> TSVector3i { TSVector3i(v0.x + v1, v0.y + v1, v0.z + v1) }
public func -(v0: TSVector3i, v1: Int32) -> TSVector3i { TSVector3i(v0.x - v1, v0.y - v1, v0.z - v1) }
public func &(v0: TSVector3i, v1: Int32) -> TSVector3i { TSVector3i(v0.x & v1, v0.y & v1, v0.z & v1) }
public func |(v0: TSVector3i, v1: Int32) -> TSVector3i { TSVector3i(v0.x | v1, v0.y | v1, v0.z | v1) }
public func ^(v0: TSVector3i, v1: Int32) -> TSVector3i { TSVector3i(v0.x ^ v1, v0.y ^ v1, v0.z ^ v1) }
public func <<(v0: TSVector3i, v1: Int32) -> TSVector3i { TSVector3i(v0.x << v1, v0.y << v1, v0.z << v1) }
public func >>(v0: TSVector3i, v1: Int32) -> TSVector3i { TSVector3i(v0.x >> v1, v0.y >> v1, v0.z >> v1) }

public func *(v0: TSVector3i, v1: TSVector3i) -> TSVector3i { TSVector3i(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z) }
public func /(v0: TSVector3i, v1: TSVector3i) -> TSVector3i { TSVector3i(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z) }
public func +(v0: TSVector3i, v1: TSVector3i) -> TSVector3i { TSVector3i(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z) }
public func -(v0: TSVector3i, v1: TSVector3i) -> TSVector3i { TSVector3i(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z) }
public func &(v0: TSVector3i, v1: TSVector3i) -> TSVector3i { TSVector3i(v0.x & v1.x, v0.y & v1.y, v0.z & v1.z) }
public func |(v0: TSVector3i, v1: TSVector3i) -> TSVector3i { TSVector3i(v0.x | v1.x, v0.y | v1.y, v0.z | v1.z) }
public func ^(v0: TSVector3i, v1: TSVector3i) -> TSVector3i { TSVector3i(v0.x ^ v1.x, v0.y ^ v1.y, v0.z ^ v1.z) }

/*
 */
public func abs(_ v: TSVector3i) -> TSVector3i { TSVector3i(abs(v.x), abs(v.y), abs(v.z)) }

public func min(_ v0: TSVector3i, _ v1: TSVector3i) -> TSVector3i { TSVector3i(min(v0.x, v1.x), min(v0.y, v1.y), min(v0.z, v1.z)) }
public func max(_ v0: TSVector3i, _ v1: TSVector3i) -> TSVector3i { TSVector3i(max(v0.x, v1.x), max(v0.y, v1.y), max(v0.z, v1.z)) }

public func clamp(_ v: TSVector3i, _ v0: TSVector3i, _ v1: TSVector3i) -> TSVector3i { TSVector3i(clamp(v.x, v0.x, v1.x), clamp(v.y, v0.y, v1.y), clamp(v.z, v0.z, v1.z)) }

/*****************************************************************************\
 *
 * Vector3u
 *
\*****************************************************************************/

/*
 */
public extension TSVector3u {
	
	init(_ v: UInt32) { self.init(); self.x = v; self.y = v; self.z = v }
	init(_ x: UInt32, _ y: UInt32, _ z: UInt32) { self.init(); self.x = x; self.y = y; self.z = z }
	init(_ v: TSVector2u, _ z: UInt32) { self.init(); self.x = v.x; self.y = v.y; self.z = z }
	init(_ v: TSVector3i) { self.init(); self.x = UInt32(v.x); self.y = UInt32(v.y); self.z = UInt32(v.z) }
	init(_ v: TSVector3f) { self.init(); self.x = UInt32(v.x); self.y = UInt32(v.y); self.z = UInt32(v.z) }
	init(_ v: TSVector3d) { self.init(); self.x = UInt32(v.x); self.y = UInt32(v.y); self.z = UInt32(v.z) }
	init(_ v: TSVector4u) { self.init(); self.x = v.x; self.y = v.y; self.z = v.z }
	init(_ v: [UInt32]) { self.init(); self.x = v[0]; self.y = v[1]; self.z = v[2] }
	
	static let zero = TSVector3u(0)
	static let one = TSVector3u(1)
}

extension TSVector3u : CustomStringConvertible {
	public var description: String { "(\(x) \(y) \(z))" }
}

/*
 */
public func *(v0: TSVector3u, v1: UInt32) -> TSVector3u { TSVector3u(v0.x * v1, v0.y * v1, v0.z * v1) }
public func /(v0: TSVector3u, v1: UInt32) -> TSVector3u { TSVector3u(v0.x / v1, v0.y / v1, v0.z / v1) }
public func +(v0: TSVector3u, v1: UInt32) -> TSVector3u { TSVector3u(v0.x + v1, v0.y + v1, v0.z + v1) }
public func -(v0: TSVector3u, v1: UInt32) -> TSVector3u { TSVector3u(v0.x - v1, v0.y - v1, v0.z - v1) }
public func &(v0: TSVector3u, v1: UInt32) -> TSVector3u { TSVector3u(v0.x & v1, v0.y & v1, v0.z & v1) }
public func |(v0: TSVector3u, v1: UInt32) -> TSVector3u { TSVector3u(v0.x | v1, v0.y | v1, v0.z | v1) }
public func ^(v0: TSVector3u, v1: UInt32) -> TSVector3u { TSVector3u(v0.x ^ v1, v0.y ^ v1, v0.z ^ v1) }
public func <<(v0: TSVector3u, v1: UInt32) -> TSVector3u { TSVector3u(v0.x << v1, v0.y << v1, v0.z << v1) }
public func >>(v0: TSVector3u, v1: UInt32) -> TSVector3u { TSVector3u(v0.x >> v1, v0.y >> v1, v0.z >> v1) }

public func *(v0: TSVector3u, v1: TSVector3u) -> TSVector3u { TSVector3u(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z) }
public func /(v0: TSVector3u, v1: TSVector3u) -> TSVector3u { TSVector3u(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z) }
public func +(v0: TSVector3u, v1: TSVector3u) -> TSVector3u { TSVector3u(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z) }
public func -(v0: TSVector3u, v1: TSVector3u) -> TSVector3u { TSVector3u(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z) }
public func &(v0: TSVector3u, v1: TSVector3u) -> TSVector3u { TSVector3u(v0.x & v1.x, v0.y & v1.y, v0.z & v1.z) }
public func |(v0: TSVector3u, v1: TSVector3u) -> TSVector3u { TSVector3u(v0.x | v1.x, v0.y | v1.y, v0.z | v1.z) }
public func ^(v0: TSVector3u, v1: TSVector3u) -> TSVector3u { TSVector3u(v0.x ^ v1.x, v0.y ^ v1.y, v0.z ^ v1.z) }

/*
 */
public func min(_ v0: TSVector3u, _ v1: TSVector3u) -> TSVector3u { TSVector3u(min(v0.x, v1.x), min(v0.y, v1.y), min(v0.z, v1.z)) }
public func max(_ v0: TSVector3u, _ v1: TSVector3u) -> TSVector3u { TSVector3u(max(v0.x, v1.x), max(v0.y, v1.y), max(v0.z, v1.z)) }

public func clamp(_ v: TSVector3u, _ v0: TSVector3u, _ v1: TSVector3u) -> TSVector3u { TSVector3u(clamp(v.x, v0.x, v1.x), clamp(v.y, v0.y, v1.y), clamp(v.z, v0.z, v1.z)) }

/*****************************************************************************\
 *
 * Vector3f
 *
\*****************************************************************************/

/*
 */
public extension TSVector3f {
	
	init(_ v: Float32) { self.init(); self.x = v; self.y = v; self.z = v }
	init(_ x: Float32, _ y: Float32, _ z: Float32) { self.init(); self.x = x; self.y = y; self.z = z }
	init(_ v: TSVector2f, _ z: Float32) { self.init(); self.x = v.x; self.y = v.y; self.z = z }
	init(_ v: TSVector3i) { self.init(); self.x = Float32(v.x); self.y = Float32(v.y); self.z = Float32(v.z) }
	init(_ v: TSVector3u) { self.init(); self.x = Float32(v.x); self.y = Float32(v.y); self.z = Float32(v.z) }
	init(_ v: TSVector3d) { self.init(); self.x = Float32(v.x); self.y = Float32(v.y); self.z = Float32(v.z) }
	init(_ v: TSVector4f) { self.init(); self.x = v.x; self.y = v.y; self.z = v.z }
	init(_ v: [Float32]) { self.init(); self.x = v[0]; self.y = v[1]; self.z = v[2] }
	
	static let zero = TSVector3f(0.0)
	static let one = TSVector3f(1.0)
}

extension TSVector3f : CustomStringConvertible {
	public var description: String { "(\(x) \(y) \(z))" }
}

/*
 */
public prefix func -(v: TSVector3f) -> TSVector3f { TSVector3f(-v.x, -v.y, -v.z) }

public func *(v0: TSVector3f, v1: Float32) -> TSVector3f { TSVector3f(v0.x * v1, v0.y * v1, v0.z * v1) }
public func /(v0: TSVector3f, v1: Float32) -> TSVector3f { TSVector3f(v0.x / v1, v0.y / v1, v0.z / v1) }
public func +(v0: TSVector3f, v1: Float32) -> TSVector3f { TSVector3f(v0.x + v1, v0.y + v1, v0.z + v1) }
public func -(v0: TSVector3f, v1: Float32) -> TSVector3f { TSVector3f(v0.x - v1, v0.y - v1, v0.z - v1) }

public func *(v0: TSVector3f, v1: TSVector3f) -> TSVector3f { TSVector3f(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z) }
public func /(v0: TSVector3f, v1: TSVector3f) -> TSVector3f { TSVector3f(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z) }
public func +(v0: TSVector3f, v1: TSVector3f) -> TSVector3f { TSVector3f(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z) }
public func -(v0: TSVector3f, v1: TSVector3f) -> TSVector3f { TSVector3f(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z) }

/*
 */
public func abs(_ v: TSVector3f) -> TSVector3f { TSVector3f(abs(v.x), abs(v.y), abs(v.z)) }

public func min(_ v0: TSVector3f, _ v1: TSVector3f) -> TSVector3f { TSVector3f(min(v0.x, v1.x), min(v0.y, v1.y), min(v0.z, v1.z)) }
public func max(_ v0: TSVector3f, _ v1: TSVector3f) -> TSVector3f { TSVector3f(max(v0.x, v1.x), max(v0.y, v1.y), max(v0.z, v1.z)) }

public func clamp(_ v: TSVector3f, _ v0: TSVector3f, _ v1: TSVector3f) -> TSVector3f { TSVector3f(clamp(v.x, v0.x, v1.x), clamp(v.y, v0.y, v1.y), clamp(v.z, v0.z, v1.z)) }
public func saturate(_ v: TSVector3f) -> TSVector3f { TSVector3f(saturate(v.x), saturate(v.y), saturate(v.z)) }

public func dot(_ v0: TSVector3f, _ v1: TSVector3f) -> Float32 { v0.x * v1.x + v0.y * v1.y + v0.z * v1.z }
public func dot32(_ v0: TSVector3f, _ v1: TSVector3f) -> Float32 { v0.x * v1.x + v0.y * v1.y + v0.z }
public func dot23(_ v0: TSVector3f, _ v1: TSVector3f) -> Float32 { v0.x * v1.x + v0.y * v1.y + v1.z }
public func dot22(_ v0: TSVector3f, _ v1: TSVector3f) -> Float32 { v0.x * v1.x + v0.y * v1.y }
public func cross(_ v0: TSVector3f, _ v1: TSVector3f) -> TSVector3f {
	let x = v0.y * v1.z - v0.z * v1.y
	let y = v0.z * v1.x - v0.x * v1.z
	let z = v0.x * v1.y - v0.y * v1.x
	return TSVector3f(x, y, z)
}

public func length2(_ v: TSVector3f) -> Float32 { v.x * v.x + v.y * v.y + v.z * v.z }
public func length(_ v: TSVector3f) -> Float32 { sqrt(length2(v)) }
public func normalize(_ v: TSVector3f) -> TSVector3f { v * (1.0 / length(v)) }

public func lerp(_ v0: TSVector3f, _ v1: TSVector3f, k: Float32) -> TSVector3f { v0 + (v1 - v0) * k }
public func lerp(_ v0: TSVector3f, _ v1: TSVector3f, k: TSVector3f) -> TSVector3f { v0 + (v1 - v0) * k }

/*****************************************************************************\
 *
 * Vector3d
 *
\*****************************************************************************/

/*
 */
public extension TSVector3d {
	
	init(_ v: Float64) { self.init(); self.x = v; self.y = v; self.z = v }
	init(_ x: Float64, _ y: Float64, _ z: Float64) { self.init(); self.x = x; self.y = y; self.z = z }
	init(_ v: TSVector2d, _ z: Float64) { self.init(); self.x = v.x; self.y = v.y; self.z = z }
	init(_ v: TSVector3i) { self.init(); self.x = Float64(v.x); self.y = Float64(v.y); self.z = Float64(v.z) }
	init(_ v: TSVector3u) { self.init(); self.x = Float64(v.x); self.y = Float64(v.y); self.z = Float64(v.z) }
	init(_ v: TSVector3f) { self.init(); self.x = Float64(v.x); self.y = Float64(v.y); self.z = Float64(v.z) }
	init(_ v: TSVector4d) { self.init(); self.x = v.x; self.y = v.y; self.z = v.z }
	init(_ v: [Float64]) { self.init(); self.x = v[0]; self.y = v[1]; self.z = v[2] }
	
	static let zero = TSVector3d(0.0)
	static let one = TSVector3d(1.0)
}

extension TSVector3d : CustomStringConvertible {
	public var description: String { "(\(x) \(y) \(z))" }
}

/*
 */
public prefix func -(v: TSVector3d) -> TSVector3d { TSVector3d(-v.x, -v.y, -v.z) }

public func *(v0: TSVector3d, v1: Float64) -> TSVector3d { TSVector3d(v0.x * v1, v0.y * v1, v0.z * v1) }
public func /(v0: TSVector3d, v1: Float64) -> TSVector3d { TSVector3d(v0.x / v1, v0.y / v1, v0.z / v1) }
public func +(v0: TSVector3d, v1: Float64) -> TSVector3d { TSVector3d(v0.x + v1, v0.y + v1, v0.z + v1) }
public func -(v0: TSVector3d, v1: Float64) -> TSVector3d { TSVector3d(v0.x - v1, v0.y - v1, v0.z - v1) }

public func *(v0: TSVector3d, v1: TSVector3d) -> TSVector3d { TSVector3d(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z) }
public func /(v0: TSVector3d, v1: TSVector3d) -> TSVector3d { TSVector3d(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z) }
public func +(v0: TSVector3d, v1: TSVector3d) -> TSVector3d { TSVector3d(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z) }
public func -(v0: TSVector3d, v1: TSVector3d) -> TSVector3d { TSVector3d(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z) }

/*
 */
public func abs(_ v: TSVector3d) -> TSVector3d { TSVector3d(abs(v.x), abs(v.y), abs(v.z)) }

public func min(_ v0: TSVector3d, _ v1: TSVector3d) -> TSVector3d { TSVector3d(min(v0.x, v1.x), min(v0.y, v1.y), min(v0.z, v1.z)) }
public func max(_ v0: TSVector3d, _ v1: TSVector3d) -> TSVector3d { TSVector3d(max(v0.x, v1.x), max(v0.y, v1.y), max(v0.z, v1.z)) }

public func clamp(_ v: TSVector3d, _ v0: TSVector3d, _ v1: TSVector3d) -> TSVector3d { TSVector3d(clamp(v.x, v0.x, v1.x), clamp(v.y, v0.y, v1.y), clamp(v.z, v0.z, v1.z)) }
public func saturate(_ v: TSVector3d) -> TSVector3d { TSVector3d(saturate(v.x), saturate(v.y), saturate(v.z)) }

public func dot(_ v0: TSVector3d, _ v1: TSVector3d) -> Float64 { v0.x * v1.x + v0.y * v1.y + v0.z * v1.z }
public func dot32(_ v0: TSVector3d, _ v1: TSVector3d) -> Float64 { v0.x * v1.x + v0.y * v1.y + v0.z }
public func dot23(_ v0: TSVector3d, _ v1: TSVector3d) -> Float64 { v0.x * v1.x + v0.y * v1.y + v1.z }
public func dot22(_ v0: TSVector3d, _ v1: TSVector3d) -> Float64 { v0.x * v1.x + v0.y * v1.y }
public func cross(_ v0: TSVector3d, _ v1: TSVector3d) -> TSVector3d {
	let x = v0.y * v1.z - v0.z * v1.y
	let y = v0.z * v1.x - v0.x * v1.z
	let z = v0.x * v1.y - v0.y * v1.x
	return TSVector3d(x, y, z)
}

public func length2(_ v: TSVector3d) -> Float64 { v.x * v.x + v.y * v.y + v.z * v.z }
public func length(_ v: TSVector3d) -> Float64 { sqrt(length2(v)) }
public func normalize(_ v: TSVector3d) -> TSVector3d { v * (1.0 / length(v)) }

public func lerp(_ v0: TSVector3d, _ v1: TSVector3d, k: Float64) -> TSVector3d { v0 + (v1 - v0) * k }
public func lerp(_ v0: TSVector3d, _ v1: TSVector3d, k: TSVector3d) -> TSVector3d { v0 + (v1 - v0) * k }

/*****************************************************************************\
 *
 * Vector4i
 *
\*****************************************************************************/

/*
 */
public extension TSVector4i {
	
	init(_ v: Int32) { self.init(); self.x = v; self.y = v; self.z = v; self.w = v }
	init(_ x: Int32, _ y: Int32, _ z: Int32, _ w: Int32) { self.init(); self.x = x; self.y = y; self.z = z; self.w = w }
	init(_ v: TSVector2i, _ z: Int32, _ w: Int32) { self.init(); self.x = v.x; self.y = v.y; self.z = z; self.w = w }
	init(_ v: TSVector3i, _ w: Int32) { self.init(); self.x = v.x; self.y = v.y; self.z = v.z; self.w = w }
	init(_ v: TSVector4u) { self.init(); self.x = Int32(v.x); self.y = Int32(v.y); self.z = Int32(v.z); self.w = Int32(v.w) }
	init(_ v: TSVector4f) { self.init(); self.x = Int32(v.x); self.y = Int32(v.y); self.z = Int32(v.z); self.w = Int32(v.w) }
	init(_ v: TSVector4d) { self.init(); self.x = Int32(v.x); self.y = Int32(v.y); self.z = Int32(v.z); self.w = Int32(v.w) }
	init(_ v: [Int32]) { self.init(); self.x = v[0]; self.y = v[1]; self.z = v[2]; self.w = v[3] }
	
	static let zero = TSVector4i(0)
	static let one = TSVector4i(1)
}

extension TSVector4i : CustomStringConvertible {
	public var description: String { "(\(x) \(y) \(z) \(w))" }
}

/*
 */
public prefix func -(v: TSVector4i) -> TSVector4i { TSVector4i(-v.x, -v.y, -v.z, -v.w) }

public func *(v0: TSVector4i, v1: Int32) -> TSVector4i { TSVector4i(v0.x * v1, v0.y * v1, v0.z * v1, v0.w * v1) }
public func /(v0: TSVector4i, v1: Int32) -> TSVector4i { TSVector4i(v0.x / v1, v0.y / v1, v0.z / v1, v0.w / v1) }
public func +(v0: TSVector4i, v1: Int32) -> TSVector4i { TSVector4i(v0.x + v1, v0.y + v1, v0.z + v1, v0.w + v1) }
public func -(v0: TSVector4i, v1: Int32) -> TSVector4i { TSVector4i(v0.x - v1, v0.y - v1, v0.z - v1, v0.w - v1) }
public func &(v0: TSVector4i, v1: Int32) -> TSVector4i { TSVector4i(v0.x & v1, v0.y & v1, v0.z & v1, v0.w & v1) }
public func |(v0: TSVector4i, v1: Int32) -> TSVector4i { TSVector4i(v0.x | v1, v0.y | v1, v0.z | v1, v0.w | v1) }
public func ^(v0: TSVector4i, v1: Int32) -> TSVector4i { TSVector4i(v0.x ^ v1, v0.y ^ v1, v0.z ^ v1, v0.w ^ v1) }
public func <<(v0: TSVector4i, v1: Int32) -> TSVector4i { TSVector4i(v0.x << v1, v0.y << v1, v0.z << v1, v0.w << v1) }
public func >>(v0: TSVector4i, v1: Int32) -> TSVector4i { TSVector4i(v0.x >> v1, v0.y >> v1, v0.z >> v1, v0.w >> v1) }

public func *(v0: TSVector4i, v1: TSVector4i) -> TSVector4i { TSVector4i(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z, v0.w * v1.w) }
public func /(v0: TSVector4i, v1: TSVector4i) -> TSVector4i { TSVector4i(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z, v0.w / v1.w) }
public func +(v0: TSVector4i, v1: TSVector4i) -> TSVector4i { TSVector4i(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w) }
public func -(v0: TSVector4i, v1: TSVector4i) -> TSVector4i { TSVector4i(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w) }
public func &(v0: TSVector4i, v1: TSVector4i) -> TSVector4i { TSVector4i(v0.x & v1.x, v0.y & v1.y, v0.z & v1.z, v0.w & v1.w) }
public func |(v0: TSVector4i, v1: TSVector4i) -> TSVector4i { TSVector4i(v0.x | v1.x, v0.y | v1.y, v0.z | v1.z, v0.w | v1.w) }
public func ^(v0: TSVector4i, v1: TSVector4i) -> TSVector4i { TSVector4i(v0.x ^ v1.x, v0.y ^ v1.y, v0.z ^ v1.z, v0.w ^ v1.w) }

/*
 */
public func abs(_ v: TSVector4i) -> TSVector4i { TSVector4i(abs(v.x), abs(v.y), abs(v.z), abs(v.w)) }

public func min(_ v0: TSVector4i, _ v1: TSVector4i) -> TSVector4i { TSVector4i(min(v0.x, v1.x), min(v0.y, v1.y), min(v0.z, v1.z), min(v0.w, v1.w)) }
public func max(_ v0: TSVector4i, _ v1: TSVector4i) -> TSVector4i { TSVector4i(max(v0.x, v1.x), max(v0.y, v1.y), max(v0.z, v1.z), max(v0.w, v1.w)) }

public func clamp(_ v: TSVector4i, _ v0: TSVector4i, _ v1: TSVector4i) -> TSVector4i { TSVector4i(clamp(v.x, v0.x, v1.x), clamp(v.y, v0.y, v1.y), clamp(v.z, v0.z, v1.z), clamp(v.w, v0.w, v1.w)) }

/*****************************************************************************\
 *
 * Vector4u
 *
\*****************************************************************************/

/*
 */
public extension TSVector4u {
	
	init(_ v: UInt32) { self.init(); self.x = v; self.y = v; self.z = v; self.w = v }
	init(_ x: UInt32, _ y: UInt32, _ z: UInt32, _ w: UInt32) { self.init(); self.x = x; self.y = y; self.z = z; self.w = w }
	init(_ v: TSVector2u, _ z: UInt32, _ w: UInt32) { self.init(); self.x = v.x; self.y = v.y; self.z = z; self.w = w }
	init(_ v: TSVector3u, _ w: UInt32) { self.init(); self.x = v.x; self.y = v.y; self.z = v.z; self.w = w }
	init(_ v: TSVector4i) { self.init(); self.x = UInt32(v.x); self.y = UInt32(v.y); self.z = UInt32(v.z); self.w = UInt32(v.w) }
	init(_ v: TSVector4f) { self.init(); self.x = UInt32(v.x); self.y = UInt32(v.y); self.z = UInt32(v.z); self.w = UInt32(v.w) }
	init(_ v: TSVector4d) { self.init(); self.x = UInt32(v.x); self.y = UInt32(v.y); self.z = UInt32(v.z); self.w = UInt32(v.w) }
	init(_ v: [UInt32]) { self.init(); self.x = v[0]; self.y = v[1]; self.z = v[2]; self.w = v[3] }
	
	static let zero = TSVector4u(0)
	static let one = TSVector4u(1)
}

extension TSVector4u : CustomStringConvertible {
	public var description: String { "(\(x) \(y) \(z) \(w))" }
}

/*
 */
public func *(v0: TSVector4u, v1: UInt32) -> TSVector4u { TSVector4u(v0.x * v1, v0.y * v1, v0.z * v1, v0.w * v1) }
public func /(v0: TSVector4u, v1: UInt32) -> TSVector4u { TSVector4u(v0.x / v1, v0.y / v1, v0.z / v1, v0.w / v1) }
public func +(v0: TSVector4u, v1: UInt32) -> TSVector4u { TSVector4u(v0.x + v1, v0.y + v1, v0.z + v1, v0.w + v1) }
public func -(v0: TSVector4u, v1: UInt32) -> TSVector4u { TSVector4u(v0.x - v1, v0.y - v1, v0.z - v1, v0.w - v1) }
public func &(v0: TSVector4u, v1: UInt32) -> TSVector4u { TSVector4u(v0.x & v1, v0.y & v1, v0.z & v1, v0.w & v1) }
public func |(v0: TSVector4u, v1: UInt32) -> TSVector4u { TSVector4u(v0.x | v1, v0.y | v1, v0.z | v1, v0.w | v1) }
public func ^(v0: TSVector4u, v1: UInt32) -> TSVector4u { TSVector4u(v0.x ^ v1, v0.y ^ v1, v0.z ^ v1, v0.w ^ v1) }
public func <<(v0: TSVector4u, v1: UInt32) -> TSVector4u { TSVector4u(v0.x << v1, v0.y << v1, v0.z << v1, v0.w << v1) }
public func >>(v0: TSVector4u, v1: UInt32) -> TSVector4u { TSVector4u(v0.x >> v1, v0.y >> v1, v0.z >> v1, v0.w >> v1) }

public func *(v0: TSVector4u, v1: TSVector4u) -> TSVector4u { TSVector4u(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z, v0.w * v1.w) }
public func /(v0: TSVector4u, v1: TSVector4u) -> TSVector4u { TSVector4u(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z, v0.w / v1.w) }
public func +(v0: TSVector4u, v1: TSVector4u) -> TSVector4u { TSVector4u(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w) }
public func -(v0: TSVector4u, v1: TSVector4u) -> TSVector4u { TSVector4u(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w) }
public func &(v0: TSVector4u, v1: TSVector4u) -> TSVector4u { TSVector4u(v0.x & v1.x, v0.y & v1.y, v0.z & v1.z, v0.w & v1.w) }
public func |(v0: TSVector4u, v1: TSVector4u) -> TSVector4u { TSVector4u(v0.x | v1.x, v0.y | v1.y, v0.z | v1.z, v0.w | v1.w) }
public func ^(v0: TSVector4u, v1: TSVector4u) -> TSVector4u { TSVector4u(v0.x ^ v1.x, v0.y ^ v1.y, v0.z ^ v1.z, v0.w ^ v1.w) }

/*
 */
public func min(_ v0: TSVector4u, _ v1: TSVector4u) -> TSVector4u { TSVector4u(min(v0.x, v1.x), min(v0.y, v1.y), min(v0.z, v1.z), min(v0.w, v1.w)) }
public func max(_ v0: TSVector4u, _ v1: TSVector4u) -> TSVector4u { TSVector4u(max(v0.x, v1.x), max(v0.y, v1.y), max(v0.z, v1.z), max(v0.w, v1.w)) }

public func clamp(_ v: TSVector4u, _ v0: TSVector4u, _ v1: TSVector4u) -> TSVector4u { TSVector4u(clamp(v.x, v0.x, v1.x), clamp(v.y, v0.y, v1.y), clamp(v.z, v0.z, v1.z), clamp(v.w, v0.w, v1.w)) }

/*****************************************************************************\
 *
 * Vector4f
 *
\*****************************************************************************/

/*
 */
public extension TSVector4f {
	
	init(_ v: Float32) { self.init(); self.x = v; self.y = v; self.z = v; self.w = v }
	init(_ x: Float32, _ y: Float32, _ z: Float32, _ w: Float32) { self.init(); self.x = x; self.y = y; self.z = z; self.w = w }
	init(_ v: TSVector2f, _ z: Float32, _ w: Float32) { self.init(); self.x = v.x; self.y = v.y; self.z = z; self.w = w }
	init(_ v: TSVector3f, _ w: Float32) { self.init(); self.x = v.x; self.y = v.y; self.z = v.z; self.w = w }
	init(_ v: TSVector4i) { self.init(); self.x = Float32(v.x); self.y = Float32(v.y); self.z = Float32(v.z); self.w = Float32(v.w) }
	init(_ v: TSVector4u) { self.init(); self.x = Float32(v.x); self.y = Float32(v.y); self.z = Float32(v.z); self.w = Float32(v.w) }
	init(_ v: TSVector4d) { self.init(); self.x = Float32(v.x); self.y = Float32(v.y); self.z = Float32(v.z); self.w = Float32(v.w) }
	init(_ v: [Float32]) { self.init(); self.x = v[0]; self.y = v[1]; self.z = v[2]; self.w = v[3] }
	
	static let zero = TSVector4f(0.0)
	static let one = TSVector4f(1.0)
}

extension TSVector4f : CustomStringConvertible {
	public var description: String { "(\(x) \(y) \(z) \(w))" }
}

/*
 */
public prefix func -(v: TSVector4f) -> TSVector4f { TSVector4f(-v.x, -v.y, -v.z, -v.w) }

public func *(v0: TSVector4f, v1: Float32) -> TSVector4f { TSVector4f(v0.x * v1, v0.y * v1, v0.z * v1, v0.w * v1) }
public func /(v0: TSVector4f, v1: Float32) -> TSVector4f { TSVector4f(v0.x / v1, v0.y / v1, v0.z / v1, v0.w / v1) }
public func +(v0: TSVector4f, v1: Float32) -> TSVector4f { TSVector4f(v0.x + v1, v0.y + v1, v0.z + v1, v0.w + v1) }
public func -(v0: TSVector4f, v1: Float32) -> TSVector4f { TSVector4f(v0.x - v1, v0.y - v1, v0.z - v1, v0.w - v1) }

public func *(v0: TSVector4f, v1: TSVector4f) -> TSVector4f { TSVector4f(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z, v0.w * v1.w) }
public func /(v0: TSVector4f, v1: TSVector4f) -> TSVector4f { TSVector4f(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z, v0.w / v1.w) }
public func +(v0: TSVector4f, v1: TSVector4f) -> TSVector4f { TSVector4f(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w) }
public func -(v0: TSVector4f, v1: TSVector4f) -> TSVector4f { TSVector4f(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w) }

/*
 */
public func abs(_ v: TSVector4f) -> TSVector4f { TSVector4f(abs(v.x), abs(v.y), abs(v.z), abs(v.w)) }

public func min(_ v0: TSVector4f, _ v1: TSVector4f) -> TSVector4f { TSVector4f(min(v0.x, v1.x), min(v0.y, v1.y), min(v0.z, v1.z), min(v0.w, v1.w)) }
public func max(_ v0: TSVector4f, _ v1: TSVector4f) -> TSVector4f { TSVector4f(max(v0.x, v1.x), max(v0.y, v1.y), max(v0.z, v1.z), max(v0.w, v1.w)) }

public func clamp(_ v: TSVector4f, _ v0: TSVector4f, _ v1: TSVector4f) -> TSVector4f { TSVector4f(clamp(v.x, v0.x, v1.x), clamp(v.y, v0.y, v1.y), clamp(v.z, v0.z, v1.z), clamp(v.w, v0.w, v1.w)) }
public func saturate(_ v: TSVector4f) -> TSVector4f { TSVector4f(saturate(v.x), saturate(v.y), saturate(v.z), saturate(v.w)) }

public func dot(_ v0: TSVector4f, _ v1: TSVector4f) -> Float32 { v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w * v1.w }
public func dot(_ v0: TSVector4f, _ v1: TSVector3f) -> Float32 { v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w }
public func dot(_ v0: TSVector3f, _ v1: TSVector4f) -> Float32 { v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v1.w }
public func dot3(_ v0: TSVector4f, _ v1: TSVector3f) -> Float32 { v0.x * v1.x + v0.y * v1.y + v0.z * v1.z }
public func dot3(_ v0: TSVector3f, _ v1: TSVector4f) -> Float32 { v0.x * v1.x + v0.y * v1.y + v0.z * v1.z }
public func dot43(_ v0: TSVector4f, _ v1: TSVector4f) -> Float32 { v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w }
public func dot34(_ v0: TSVector4f, _ v1: TSVector4f) -> Float32 { v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v1.w }
public func dot33(_ v0: TSVector4f, _ v1: TSVector4f) -> Float32 { v0.x * v1.x + v0.y * v1.y + v0.z * v1.z }
public func cross(_ v0: TSVector4f, _ v1: TSVector4f) -> TSVector4f {
	let x = v0.y * v1.z - v0.z * v1.y
	let y = v0.z * v1.x - v0.x * v1.z
	let z = v0.x * v1.y - v0.y * v1.x
	return TSVector4f(x, y, z, 0.0)
}

public func length2(_ v: TSVector4f) -> Float32 { v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w }
public func length23(_ v: TSVector4f) -> Float32 { v.x * v.x + v.y * v.y + v.z * v.z }
public func length(_ v: TSVector4f) -> Float32 { sqrt(length2(v)) }
public func length3(_ v: TSVector4f) -> Float32 { sqrt(length23(v)) }
public func normalize(_ v: TSVector4f) -> TSVector4f { v * (1.0 / length(v)) }
public func normalize3(_ v: TSVector4f) -> TSVector4f { v * (1.0 / length3(v)) }

public func lerp(_ v0: TSVector4f, _ v1: TSVector4f, k: Float32) -> TSVector4f { v0 + (v1 - v0) * k }
public func lerp(_ v0: TSVector4f, _ v1: TSVector4f, k: TSVector4f) -> TSVector4f { v0 + (v1 - v0) * k }

/*****************************************************************************\
 *
 * Vector4d
 *
\*****************************************************************************/

/*
 */
public extension TSVector4d {
	
	init(_ v: Float64) { self.init(); self.x = v; self.y = v; self.z = v; self.w = v }
	init(_ x: Float64, _ y: Float64, _ z: Float64, _ w: Float64) { self.init(); self.x = x; self.y = y; self.z = z; self.w = w }
	init(_ v: TSVector2d, _ z: Float64, _ w: Float64) { self.init(); self.x = v.x; self.y = v.y; self.z = z; self.w = w }
	init(_ v: TSVector3d, _ w: Float64) { self.init(); self.x = v.x; self.y = v.y; self.z = v.z; self.w = w }
	init(_ v: TSVector4i) { self.init(); self.x = Float64(v.x); self.y = Float64(v.y); self.z = Float64(v.z); self.w = Float64(v.w) }
	init(_ v: TSVector4u) { self.init(); self.x = Float64(v.x); self.y = Float64(v.y); self.z = Float64(v.z); self.w = Float64(v.w) }
	init(_ v: TSVector4f) { self.init(); self.x = Float64(v.x); self.y = Float64(v.y); self.z = Float64(v.z); self.w = Float64(v.w) }
	init(_ v: [Float64]) { self.init(); self.x = v[0]; self.y = v[1]; self.z = v[2]; self.w = v[3] }
	
	static let zero = TSVector4d(0.0)
	static let one = TSVector4d(1.0)
}

extension TSVector4d : CustomStringConvertible {
	public var description: String { "(\(x) \(y) \(z) \(w))" }
}

/*
 */
public prefix func -(v: TSVector4d) -> TSVector4d { TSVector4d(-v.x, -v.y, -v.z, -v.w) }

public func *(v0: TSVector4d, v1: Float64) -> TSVector4d { TSVector4d(v0.x * v1, v0.y * v1, v0.z * v1, v0.w * v1) }
public func /(v0: TSVector4d, v1: Float64) -> TSVector4d { TSVector4d(v0.x / v1, v0.y / v1, v0.z / v1, v0.w / v1) }
public func +(v0: TSVector4d, v1: Float64) -> TSVector4d { TSVector4d(v0.x + v1, v0.y + v1, v0.z + v1, v0.w + v1) }
public func -(v0: TSVector4d, v1: Float64) -> TSVector4d { TSVector4d(v0.x - v1, v0.y - v1, v0.z - v1, v0.w - v1) }

public func *(v0: TSVector4d, v1: TSVector4d) -> TSVector4d { TSVector4d(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z, v0.w * v1.w) }
public func /(v0: TSVector4d, v1: TSVector4d) -> TSVector4d { TSVector4d(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z, v0.w / v1.w) }
public func +(v0: TSVector4d, v1: TSVector4d) -> TSVector4d { TSVector4d(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w) }
public func -(v0: TSVector4d, v1: TSVector4d) -> TSVector4d { TSVector4d(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w) }

/*
 */
public func abs(_ v: TSVector4d) -> TSVector4d { TSVector4d(abs(v.x), abs(v.y), abs(v.z), abs(v.w)) }

public func min(_ v0: TSVector4d, _ v1: TSVector4d) -> TSVector4d { TSVector4d(min(v0.x, v1.x), min(v0.y, v1.y), min(v0.z, v1.z), min(v0.w, v1.w)) }
public func max(_ v0: TSVector4d, _ v1: TSVector4d) -> TSVector4d { TSVector4d(max(v0.x, v1.x), max(v0.y, v1.y), max(v0.z, v1.z), max(v0.w, v1.w)) }

public func clamp(_ v: TSVector4d, _ v0: TSVector4d, _ v1: TSVector4d) -> TSVector4d { TSVector4d(clamp(v.x, v0.x, v1.x), clamp(v.y, v0.y, v1.y), clamp(v.z, v0.z, v1.z), clamp(v.w, v0.w, v1.w)) }
public func saturate(_ v: TSVector4d) -> TSVector4d { TSVector4d(saturate(v.x), saturate(v.y), saturate(v.z), saturate(v.w)) }

public func dot(_ v0: TSVector4d, _ v1: TSVector4d) -> Float64 { v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w * v1.w }
public func dot(_ v0: TSVector4d, _ v1: TSVector3d) -> Float64 { v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w }
public func dot(_ v0: TSVector3d, _ v1: TSVector4d) -> Float64 { v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v1.w }
public func dot3(_ v0: TSVector4d, _ v1: TSVector3d) -> Float64 { v0.x * v1.x + v0.y * v1.y + v0.z * v1.z }
public func dot3(_ v0: TSVector3d, _ v1: TSVector4d) -> Float64 { v0.x * v1.x + v0.y * v1.y + v0.z * v1.z }
public func dot43(_ v0: TSVector4d, _ v1: TSVector4d) -> Float64 { v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w }
public func dot34(_ v0: TSVector4d, _ v1: TSVector4d) -> Float64 { v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v1.w }
public func dot33(_ v0: TSVector4d, _ v1: TSVector4d) -> Float64 { v0.x * v1.x + v0.y * v1.y + v0.z * v1.z }
public func cross(_ v0: TSVector4d, _ v1: TSVector4d) -> TSVector4d {
	let x = v0.y * v1.z - v0.z * v1.y
	let y = v0.z * v1.x - v0.x * v1.z
	let z = v0.x * v1.y - v0.y * v1.x
	return TSVector4d(x, y, z, 0.0)
}

public func length2(_ v: TSVector4d) -> Float64 { v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w }
public func length23(_ v: TSVector4d) -> Float64 { v.x * v.x + v.y * v.y + v.z * v.z }
public func length(_ v: TSVector4d) -> Float64 { sqrt(length2(v)) }
public func length3(_ v: TSVector4d) -> Float64 { sqrt(length23(v)) }
public func normalize(_ v: TSVector4d) -> TSVector4d { v * (1.0 / length(v)) }
public func normalize3(_ v: TSVector4d) -> TSVector4d { v * (1.0 / length3(v)) }

public func lerp(_ v0: TSVector4d, _ v1: TSVector4d, k: Float64) -> TSVector4d { v0 + (v1 - v0) * k }
public func lerp(_ v0: TSVector4d, _ v1: TSVector4d, k: TSVector4d) -> TSVector4d { v0 + (v1 - v0) * k }

/*****************************************************************************\
 *
 * Matrix3x2f
 *
\*****************************************************************************/

/*
 */
public extension TSMatrix3x2f {
	
	init(_ row_0: TSVector3f, _ row_1: TSVector3f) { self.init(); self.row_0 = row_0; self.row_1 = row_1 }
	init(_ m: TSMatrix3x2d) { self.init(); self.row_0 = TSVector3f(m.row_0); self.row_1 = TSVector3f(m.row_1) }
	init(_ m: [Float32], _ row_major: Bool = true) { self.init(); tsMatrix3x2f_set(&self, m, UInt32(m.count), row_major) }
	
	mutating func set(_ src: [Float32], _ row_major: Bool = true) { tsMatrix3x2f_set(&self, src, UInt32(src.count), row_major) }
	func get(_ dest: inout [Float32], _ row_major: Bool = true) { var m = self; tsMatrix3x2f_get(&m, &dest, UInt32(dest.count), row_major) }
	
	static func scale(_ s: Float32) -> TSMatrix3x2f { var ret = TSMatrix3x2f(); tsMatrix3x2f_scale(&ret, s, s); return ret }
	static func scale(_ x: Float32, _ y: Float32) -> TSMatrix3x2f { var ret = TSMatrix3x2f(); tsMatrix3x2f_scale(&ret, x, y); return ret }
	static func scale(_ s: TSVector2f) -> TSMatrix3x2f { var ret = TSMatrix3x2f(); tsMatrix3x2f_scale(&ret, s.x, s.y); return ret }
	static func translate(_ x: Float32, _ y: Float32) -> TSMatrix3x2f { var ret = TSMatrix3x2f(); tsMatrix3x2f_translate(&ret, x, y); return ret }
	static func translate(_ t: TSVector2f) -> TSMatrix3x2f { var ret = TSMatrix3x2f(); tsMatrix3x2f_translate(&ret, t.x, t.y); return ret }
	static func rotate(_ angle: Float32) -> TSMatrix3x2f { var ret = TSMatrix3x2f(); tsMatrix3x2f_rotate(&ret, angle); return ret }
	
	static let zero = TSMatrix3x2f(TSVector3f.zero, TSVector3f.zero)
	static let identity = TSMatrix3x2f(TSVector3f(1.0, 0.0, 0.0), TSVector3f(0.0, 1.0, 0.0))
}

extension TSMatrix3x2f : CustomStringConvertible {
	public var description: String { "(\(row_0) \(row_1))" }
}

/*
 */
public func *(_ m: TSMatrix3x2f, _ v: TSVector2f) -> TSVector2f { var ret = TSVector2f(), m = m, v = v; tsMatrix3x2f_mul2(&ret, &m, &v); return ret }
public func *(_ v: TSVector2f, _ m: TSMatrix3x2f) -> TSVector2f { var ret = TSVector2f(), v = v, m = m; tsMatrix3x2f_mul2t(&ret, &v, &m); return ret }
public func *(_ m0: TSMatrix3x2f, _ m1: TSMatrix3x2f) -> TSMatrix3x2f { var ret = TSMatrix3x2f(), m0 = m0, m1 = m1; tsMatrix3x2f_mul(&ret, &m0, &m1); return ret }

/*
 */
public func transpose(_ m: TSMatrix3x2f) -> TSMatrix3x2f { var ret = TSMatrix3x2f(), m = m; tsMatrix3x2f_transpose(&ret, &m); return ret }
public func inverse(_ m: TSMatrix3x2f) -> TSMatrix3x2f { var ret = TSMatrix3x2f(), m = m; tsMatrix3x2f_inverse(&ret, &m); return ret }

/*****************************************************************************\
 *
 * Matrix3x2d
 *
\*****************************************************************************/

/*
 */
public extension TSMatrix3x2d {
	
	init(_ row_0: TSVector3d, _ row_1: TSVector3d) { self.init(); self.row_0 = row_0; self.row_1 = row_1 }
	init(_ m: TSMatrix3x2f) { self.init(); self.row_0 = TSVector3d(m.row_0); self.row_1 = TSVector3d(m.row_1) }
	init(_ m: [Float64], _ row_major: Bool = true) { self.init(); tsMatrix3x2d_set(&self, m, UInt32(m.count), row_major) }
	
	mutating func set(_ src: [Float64], _ row_major: Bool = true) { tsMatrix3x2d_set(&self, src, UInt32(src.count), row_major) }
	func get(_ dest: inout [Float64], _ row_major: Bool = true) { var m = self; tsMatrix3x2d_get(&m, &dest, UInt32(dest.count), row_major) }
	
	static let zero = TSMatrix3x2d(TSVector3d.zero, TSVector3d.zero)
	static let identity = TSMatrix3x2d(TSVector3d(1.0, 0.0, 0.0), TSVector3d(0.0, 1.0, 0.0))
}

extension TSMatrix3x2d : CustomStringConvertible {
	public var description: String { "(\(row_0) \(row_1))" }
}

/*
 */
public func *(_ m: TSMatrix3x2d, _ v: TSVector2d) -> TSVector2d { var ret = TSVector2d(), m = m, v = v; tsMatrix3x2d_mul2(&ret, &m, &v); return ret }
public func *(_ v: TSVector2d, _ m: TSMatrix3x2d) -> TSVector2d { var ret = TSVector2d(), v = v, m = m; tsMatrix3x2d_mul2t(&ret, &v, &m); return ret }
public func *(_ m0: TSMatrix3x2d, _ m1: TSMatrix3x2d) -> TSMatrix3x2d { var ret = TSMatrix3x2d(), m0 = m0, m1 = m1; tsMatrix3x2d_mul(&ret, &m0, &m1); return ret }

/*
 */
public func transpose(_ m: TSMatrix3x2d) -> TSMatrix3x2d { var ret = TSMatrix3x2d(), m = m; tsMatrix3x2d_transpose(&ret, &m); return ret }
public func inverse(_ m: TSMatrix3x2d) -> TSMatrix3x2d { var ret = TSMatrix3x2d(), m = m; tsMatrix3x2d_inverse(&ret, &m); return ret }

/*****************************************************************************\
 *
 * Matrix4x3f
 *
\*****************************************************************************/

/*
 */
public extension TSMatrix4x3f {
	
	init(_ m: TSMatrix4x4f) { self.init(); self.row_0 = m.row_0; self.row_1 = m.row_1; self.row_2 = m.row_2 }
	init(_ m: TSMatrix4x3d) { self.init(); self.row_0 = TSVector4f(m.row_0); self.row_1 = TSVector4f(m.row_1); self.row_2 = TSVector4f(m.row_2) }
	init(_ row_0: TSVector4f, _ row_1: TSVector4f, _ row_2: TSVector4f) { self.init(); self.row_0 = row_0; self.row_1 = row_1; self.row_2 = row_2 }
	init(_ m: [Float32], _ row_major: Bool = true) { self.init(); set(m, row_major) }
	init(_ q: TSQuaternionf) { self.init(); set(q) }
	
	mutating func set(_ src: [Float32], _ row_major: Bool = true) { tsMatrix4x3f_set(&self, src, UInt32(src.count), row_major) }
	func get(_ dest: inout [Float32], _ row_major: Bool = true) { var m = self; tsMatrix4x3f_get(&m, &dest, UInt32(dest.count), row_major) }
	mutating func set(_ q: TSQuaternionf) { var q = q; tsQuaternionf_get(&q, &rows.0) }
	func get(_ q: inout TSQuaternionf) { var m = self; tsQuaternionf_set(&q, &m.rows.0) }
	
	static func scale(_ s: Float32) -> TSMatrix4x3f { var ret = TSMatrix4x3f(); tsMatrix4x3f_scale(&ret, s, s, s); return ret }
	static func scale(_ x: Float32, _ y: Float32, _ z: Float32) -> TSMatrix4x3f { var ret = TSMatrix4x3f(); tsMatrix4x3f_scale(&ret, x, y, z); return ret }
	static func scale(_ s: TSVector3f) -> TSMatrix4x3f { var ret = TSMatrix4x3f(); tsMatrix4x3f_scale(&ret, s.x, s.y, s.z); return ret }
	static func translate(_ x: Float32, _ y: Float32, _ z: Float32) -> TSMatrix4x3f { var ret = TSMatrix4x3f(); tsMatrix4x3f_translate(&ret, x, y, z); return ret }
	static func translate(_ t: TSVector3f) -> TSMatrix4x3f { var ret = TSMatrix4x3f(); tsMatrix4x3f_translate(&ret, t.x, t.y, t.z); return ret }
	static func rotateX(_ angle: Float32) -> TSMatrix4x3f { var ret = TSMatrix4x3f(); tsMatrix4x3f_rotateX(&ret, angle); return ret }
	static func rotateY(_ angle: Float32) -> TSMatrix4x3f { var ret = TSMatrix4x3f(); tsMatrix4x3f_rotateY(&ret, angle); return ret }
	static func rotateZ(_ angle: Float32) -> TSMatrix4x3f { var ret = TSMatrix4x3f(); tsMatrix4x3f_rotateZ(&ret, angle); return ret }
	static func rotate(_ axis: TSVector3f, _ angle: Float32) -> TSMatrix4x3f { var ret = TSMatrix4x3f(), axis = axis; tsMatrix4x3f_rotate(&ret, &axis, angle); return ret }
	
	static func lookAt(_ from: TSVector3f, _ to: TSVector3f, _ up: TSVector3f) -> TSMatrix4x3f { var ret = TSMatrix4x3f(), from = from, to = to, up = up; tsMatrix4x3f_lookAt(&ret, &from, &to, &up); return ret }
	static func placeTo(_ to: TSVector3f, _ from: TSVector3f, _ up: TSVector3f) -> TSMatrix4x3f { var ret = TSMatrix4x3f(), to = to, from = from, up = up; tsMatrix4x3f_placeTo(&ret, &to, &from, &up); return ret }
	static func compose(_ t: TSVector3f, _ r: TSQuaternionf, _ s: TSVector3f) -> TSMatrix4x3f { var ret = TSMatrix4x3f(), t = t, r = r, s = s; tsMatrix4x3f_compose(&ret, &t, &r, &s); return ret }
	static func basis(_ normal: TSVector3f, _ t: TSVector3f) -> TSMatrix4x3f { var ret = TSMatrix4x3f(), normal = normal, t = t; tsMatrix4x3f_basis(&ret, &normal, &t); return ret }
	
	static let zero = TSMatrix4x3f(TSVector4f.zero, TSVector4f.zero, TSVector4f.zero)
	static let identity = TSMatrix4x3f(TSVector4f(1.0, 0.0, 0.0, 0.0), TSVector4f(0.0, 1.0, 0.0, 0.0), TSVector4f(0.0, 0.0, 1.0, 0.0))
}

extension TSMatrix4x3f : CustomStringConvertible {
	public var description: String { "(\(row_0) \(row_1) \(row_2))" }
}

/*
 */
public func *(_ m: TSMatrix4x3f, _ v: TSVector2f) -> TSVector2f { var ret = TSVector2f(), m = m, v = v; tsMatrix4x3f_mul2(&ret, &m, &v); return ret }
public func *(_ m: TSMatrix4x3f, _ v: TSVector3f) -> TSVector3f { var ret = TSVector3f(), m = m, v = v; tsMatrix4x3f_mul3(&ret, &m, &v); return ret }
public func *(_ m: TSMatrix4x3f, _ v: TSVector4f) -> TSVector4f { var ret = TSVector4f(), m = m, v = v; tsMatrix4x3f_mul4(&ret, &m, &v); return ret }
public func *(_ v: TSVector2f, _ m: TSMatrix4x3f) -> TSVector2f { var ret = TSVector2f(), v = v, m = m; tsMatrix4x3f_mul2t(&ret, &v, &m); return ret }
public func *(_ v: TSVector3f, _ m: TSMatrix4x3f) -> TSVector3f { var ret = TSVector3f(), v = v, m = m; tsMatrix4x3f_mul3t(&ret, &v, &m); return ret }
public func *(_ v: TSVector4f, _ m: TSMatrix4x3f) -> TSVector4f { var ret = TSVector4f(), v = v, m = m; tsMatrix4x3f_mul4t(&ret, &v, &m); return ret }
public func *(_ m0: TSMatrix4x3f, _ m1: TSMatrix4x3f) -> TSMatrix4x3f { var ret = TSMatrix4x3f(), m0 = m0, m1 = m1; tsMatrix4x3f_mul(&ret, &m0, &m1); return ret }

/*
 */
public func normalize(_ m: TSMatrix4x3f) -> TSMatrix4x3f { var ret = TSMatrix4x3f(), m = m; tsMatrix4x3f_normalize(&ret, &m); return ret }
public func transpose(_ m: TSMatrix4x3f) -> TSMatrix4x3f { var ret = TSMatrix4x3f(), m = m; tsMatrix4x3f_transpose(&ret, &m); return ret }
public func inverse(_ m: TSMatrix4x3f) -> TSMatrix4x3f { var ret = TSMatrix4x3f(), m = m; tsMatrix4x3f_inverse(&ret, &m); return ret }
public func inverse33(_ m: TSMatrix4x3f) -> TSMatrix4x3f { var ret = TSMatrix4x3f(), m = m; tsMatrix4x3f_inverse33(&ret, &m); return ret }

public func lerp(_ m0: TSMatrix4x3f, _ m1: TSMatrix4x3f, _ k: Float32) -> TSMatrix4x3f { var ret = TSMatrix4x3f(), m0 = m0, m1 = m1; tsMatrix4x3f_lerp(&ret, &m0, &m1, k); return ret }

/*****************************************************************************\
 *
 * Matrix4x3d
 *
\*****************************************************************************/

/*
 */
public extension TSMatrix4x3d {
	
	init(_ m: TSMatrix4x4d) { self.init(); self.row_0 = m.row_0; self.row_1 = m.row_1; self.row_2 = m.row_2 }
	init(_ m: TSMatrix4x3f) { self.init(); self.row_0 = TSVector4d(m.row_0); self.row_1 = TSVector4d(m.row_1); self.row_2 = TSVector4d(m.row_2) }
	init(_ row_0: TSVector4d, _ row_1: TSVector4d, _ row_2: TSVector4d) { self.init(); self.row_0 = row_0; self.row_1 = row_1; self.row_2 = row_2 }
	init(_ m: [Float64], _ row_major: Bool = true) { self.init(); set(m, row_major) }
	init(_ q: TSQuaterniond) { self.init(); set(q) }
	
	mutating func set(_ src: [Float64], _ row_major: Bool = true) { tsMatrix4x3d_set(&self, src, UInt32(src.count), row_major) }
	func get(_ dest: inout [Float64], _ row_major: Bool = true) { var m = self; tsMatrix4x3d_get(&m, &dest, UInt32(dest.count), row_major) }
	mutating func set(_ q: TSQuaterniond) { var q = q; tsQuaterniond_get(&q, &rows.0) }
	func get(_ q: inout TSQuaterniond) { var m = self; tsQuaterniond_set(&q, &m.rows.0) }
	
	static func scale(_ s: Float64) -> TSMatrix4x3d { var ret = TSMatrix4x3d(); tsMatrix4x3d_scale(&ret, s, s, s); return ret }
	static func scale(_ x: Float64, _ y: Float64, _ z: Float64) -> TSMatrix4x3d { var ret = TSMatrix4x3d(); tsMatrix4x3d_scale(&ret, x, y, z); return ret }
	static func scale(_ s: TSVector3d) -> TSMatrix4x3d { var ret = TSMatrix4x3d(); tsMatrix4x3d_scale(&ret, s.x, s.y, s.z); return ret }
	static func translate(_ x: Float64, _ y: Float64, _ z: Float64) -> TSMatrix4x3d { var ret = TSMatrix4x3d(); tsMatrix4x3d_translate(&ret, x, y, z); return ret }
	static func translate(_ t: TSVector3d) -> TSMatrix4x3d { var ret = TSMatrix4x3d(); tsMatrix4x3d_translate(&ret, t.x, t.y, t.z); return ret }
	static func rotateX(_ angle: Float64) -> TSMatrix4x3d { var ret = TSMatrix4x3d(); tsMatrix4x3d_rotateX(&ret, angle); return ret }
	static func rotateY(_ angle: Float64) -> TSMatrix4x3d { var ret = TSMatrix4x3d(); tsMatrix4x3d_rotateY(&ret, angle); return ret }
	static func rotateZ(_ angle: Float64) -> TSMatrix4x3d { var ret = TSMatrix4x3d(); tsMatrix4x3d_rotateZ(&ret, angle); return ret }
	static func rotate(_ axis: TSVector3d, _ angle: Float64) -> TSMatrix4x3d { var ret = TSMatrix4x3d(), axis = axis; tsMatrix4x3d_rotate(&ret, &axis, angle); return ret }
	
	static func lookAt(_ from: TSVector3d, _ to: TSVector3d, _ up: TSVector3d) -> TSMatrix4x3d { var ret = TSMatrix4x3d(), from = from, to = to, up = up; tsMatrix4x3d_lookAt(&ret, &from, &to, &up); return ret }
	static func placeTo(_ to: TSVector3d, _ from: TSVector3d, _ up: TSVector3d) -> TSMatrix4x3d { var ret = TSMatrix4x3d(), to = to, from = from, up = up; tsMatrix4x3d_placeTo(&ret, &to, &from, &up); return ret }
	static func compose(_ t: TSVector3d, _ r: TSQuaterniond, _ s: TSVector3d) -> TSMatrix4x3d { var ret = TSMatrix4x3d(), t = t, r = r, s = s; tsMatrix4x3d_compose(&ret, &t, &r, &s); return ret }
	static func basis(_ normal: TSVector3d, _ t: TSVector3d) -> TSMatrix4x3d { var ret = TSMatrix4x3d(), normal = normal, t = t; tsMatrix4x3d_basis(&ret, &normal, &t); return ret }
	
	static let zero = TSMatrix4x3d(TSVector4d.zero, TSVector4d.zero, TSVector4d.zero)
	static let identity = TSMatrix4x3d(TSVector4d(1.0, 0.0, 0.0, 0.0), TSVector4d(0.0, 1.0, 0.0, 0.0), TSVector4d(0.0, 0.0, 1.0, 0.0))
}

extension TSMatrix4x3d : CustomStringConvertible {
	public var description: String { "(\(row_0) \(row_1) \(row_2))" }
}

/*
 */
public func *(_ m: TSMatrix4x3d, _ v: TSVector2d) -> TSVector2d { var ret = TSVector2d(), m = m, v = v; tsMatrix4x3d_mul2(&ret, &m, &v); return ret }
public func *(_ m: TSMatrix4x3d, _ v: TSVector3d) -> TSVector3d { var ret = TSVector3d(), m = m, v = v; tsMatrix4x3d_mul3(&ret, &m, &v); return ret }
public func *(_ m: TSMatrix4x3d, _ v: TSVector4d) -> TSVector4d { var ret = TSVector4d(), m = m, v = v; tsMatrix4x3d_mul4(&ret, &m, &v); return ret }
public func *(_ v: TSVector2d, _ m: TSMatrix4x3d) -> TSVector2d { var ret = TSVector2d(), v = v, m = m; tsMatrix4x3d_mul2t(&ret, &v, &m); return ret }
public func *(_ v: TSVector3d, _ m: TSMatrix4x3d) -> TSVector3d { var ret = TSVector3d(), v = v, m = m; tsMatrix4x3d_mul3t(&ret, &v, &m); return ret }
public func *(_ v: TSVector4d, _ m: TSMatrix4x3d) -> TSVector4d { var ret = TSVector4d(), v = v, m = m; tsMatrix4x3d_mul4t(&ret, &v, &m); return ret }
public func *(_ m0: TSMatrix4x3d, _ m1: TSMatrix4x3d) -> TSMatrix4x3d { var ret = TSMatrix4x3d(), m0 = m0, m1 = m1; tsMatrix4x3d_mul(&ret, &m0, &m1); return ret }

/*
 */
public func normalize(_ m: TSMatrix4x3d) -> TSMatrix4x3d { var ret = TSMatrix4x3d(), m = m; tsMatrix4x3d_normalize(&ret, &m); return ret }
public func transpose(_ m: TSMatrix4x3d) -> TSMatrix4x3d { var ret = TSMatrix4x3d(), m = m; tsMatrix4x3d_transpose(&ret, &m); return ret }
public func inverse(_ m: TSMatrix4x3d) -> TSMatrix4x3d { var ret = TSMatrix4x3d(), m = m; tsMatrix4x3d_inverse(&ret, &m); return ret }
public func inverse33(_ m: TSMatrix4x3d) -> TSMatrix4x3d { var ret = TSMatrix4x3d(), m = m; tsMatrix4x3d_inverse33(&ret, &m); return ret }

public func lerp(_ m0: TSMatrix4x3d, _ m1: TSMatrix4x3d, _ k: Float64) -> TSMatrix4x3d { var ret = TSMatrix4x3d(), m0 = m0, m1 = m1; tsMatrix4x3d_lerp(&ret, &m0, &m1, k); return ret }

/*****************************************************************************\
 *
 * Matrix4x4f
 *
\*****************************************************************************/

/*
 */
public extension TSMatrix4x4f {
	
	init(_ m: TSMatrix4x3f) { self.init(); self.row_0 = m.row_0; self.row_1 = m.row_1; self.row_2 = m.row_2; self.row_3 = TSVector4f(0.0, 0.0, 0.0, 1.0) }
	init(_ m: TSMatrix4x4d) { self.init(); self.row_0 = TSVector4f(m.row_0); self.row_1 = TSVector4f(m.row_1); self.row_2 = TSVector4f(m.row_2); self.row_3 = TSVector4f(m.row_3) }
	init(_ row_0: TSVector4f, _ row_1: TSVector4f, _ row_2: TSVector4f, _ row_3: TSVector4f) { self.init(); self.row_0 = row_0; self.row_1 = row_1; self.row_2 = row_2; self.row_3 = row_3 }
	init(_ m: [Float32], _ row_major: Bool = true) { self.init(); set(m, row_major) }
	init(_ q: TSQuaternionf) { self.init(); set(q) }
	
	mutating func set(_ src: [Float32], _ row_major: Bool = true) { tsMatrix4x4f_set(&self, src, UInt32(src.count), row_major) }
	func get(_ dest: inout [Float32], _ row_major: Bool = true) { var m = self; tsMatrix4x4f_get(&m, &dest, UInt32(dest.count), row_major) }
	mutating func set(_ q: TSQuaternionf) { var q = q; tsQuaternionf_get(&q, &rows.0); row_3 = TSVector4f(0.0, 0.0, 0.0, 1.0) }
	func get(_ q: inout TSQuaternionf) { var m = self; tsQuaternionf_set(&q, &m.rows.0) }
	
	static func scale(_ s: Float32) -> TSMatrix4x4f { var ret = TSMatrix4x4f(); tsMatrix4x4f_scale(&ret, s, s, s); return ret }
	static func scale(_ x: Float32, _ y: Float32, _ z: Float32) -> TSMatrix4x4f { var ret = TSMatrix4x4f(); tsMatrix4x4f_scale(&ret, x, y, z); return ret }
	static func scale(_ s: TSVector3f) -> TSMatrix4x4f { var ret = TSMatrix4x4f(); tsMatrix4x4f_scale(&ret, s.x, s.y, s.z); return ret }
	static func translate(_ x: Float32, _ y: Float32, _ z: Float32) -> TSMatrix4x4f { var ret = TSMatrix4x4f(); tsMatrix4x4f_translate(&ret, x, y, z); return ret }
	static func translate(_ t: TSVector3f) -> TSMatrix4x4f { var ret = TSMatrix4x4f(); tsMatrix4x4f_translate(&ret, t.x, t.y, t.z); return ret }
	static func rotateX(_ angle: Float32) -> TSMatrix4x4f { var ret = TSMatrix4x4f(); tsMatrix4x4f_rotateX(&ret, angle); return ret }
	static func rotateY(_ angle: Float32) -> TSMatrix4x4f { var ret = TSMatrix4x4f(); tsMatrix4x4f_rotateY(&ret, angle); return ret }
	static func rotateZ(_ angle: Float32) -> TSMatrix4x4f { var ret = TSMatrix4x4f(); tsMatrix4x4f_rotateZ(&ret, angle); return ret }
	static func rotate(_ axis: TSVector3f, _ angle: Float32) -> TSMatrix4x4f { var ret = TSMatrix4x4f(), axis = axis; tsMatrix4x4f_rotate(&ret, &axis, angle); return ret }
	
	static func lookAt(_ from: TSVector3f, _ to: TSVector3f, _ up: TSVector3f) -> TSMatrix4x4f { var ret = TSMatrix4x4f(), from = from, to = to, up = up; tsMatrix4x4f_lookAt(&ret, &from, &to, &up); return ret }
	static func placeTo(_ to: TSVector3f, _ from: TSVector3f, _ up: TSVector3f) -> TSMatrix4x4f { var ret = TSMatrix4x4f(), to = to, from = from, up = up; tsMatrix4x4f_placeTo(&ret, &to, &from, &up); return ret }
	static func compose(_ t: TSVector3f, _ r: TSQuaternionf, _ s: TSVector3f) -> TSMatrix4x4f { var ret = TSMatrix4x4f(), t = t, r = r, s = s; tsMatrix4x4f_compose(&ret, &t, &r, &s); return ret }
	static func basis(_ normal: TSVector3f, _ t: TSVector3f) -> TSMatrix4x4f { var ret = TSMatrix4x4f(), normal = normal, t = t; tsMatrix4x4f_basis(&ret, &normal, &t); return ret }
	
	static func ortho(_ left: Float32, _ right: Float32, _ bottom: Float32, _ top: Float32, _ znear: Float32, _ zfar: Float32) -> TSMatrix4x4f { var ret = TSMatrix4x4f(); tsMatrix4x4f_ortho(&ret, left, right, bottom, top, znear, zfar); return ret }
	static func frustum(_ left: Float32, _ right: Float32, _ bottom: Float32, _ top: Float32, _ znear: Float32, _ zfar: Float32, _ reverse: Bool = false) -> TSMatrix4x4f { var ret = TSMatrix4x4f(); tsMatrix4x4f_frustum(&ret, left, right, bottom, top, znear, zfar, reverse); return ret }
	static func frustum(_ left: Float32, _ right: Float32, _ bottom: Float32, _ top: Float32, _ znear: Float32, _ reverse: Bool = false) -> TSMatrix4x4f { var ret = TSMatrix4x4f(); tsMatrix4x4f_frustumi(&ret, left, right, bottom, top, znear, reverse); return ret }
	static func perspective(_ fov: Float32, _ aspect: Float32, _ znear: Float32, _ zfar: Float32, _ reverse: Bool = false) -> TSMatrix4x4f { var ret = TSMatrix4x4f(); tsMatrix4x4f_perspective(&ret, fov, aspect, znear, zfar, reverse); return ret }
	static func perspective(_ fov: Float32, _ aspect: Float32, _ znear: Float32, _ reverse: Bool = false) -> TSMatrix4x4f { var ret = TSMatrix4x4f(); tsMatrix4x4f_perspectivei(&ret, fov, aspect, znear, reverse); return ret }
	
	static let zero = TSMatrix4x4f(TSVector4f.zero, TSVector4f.zero, TSVector4f.zero, TSVector4f.zero)
	static let identity = TSMatrix4x4f(TSVector4f(1.0, 0.0, 0.0, 0.0), TSVector4f(0.0, 1.0, 0.0, 0.0), TSVector4f(0.0, 0.0, 1.0, 0.0), TSVector4f(0.0, 0.0, 0.0, 1.0))
}

extension TSMatrix4x4f : CustomStringConvertible {
	public var description: String { "(\(row_0) \(row_1) \(row_2) \(row_3))" }
}

/*
 */
public func *(_ m: TSMatrix4x4f, _ v: TSVector2f) -> TSVector2f { var ret = TSVector2f(), m = m, v = v; tsMatrix4x4f_mul2(&ret, &m, &v); return ret }
public func *(_ m: TSMatrix4x4f, _ v: TSVector3f) -> TSVector3f { var ret = TSVector3f(), m = m, v = v; tsMatrix4x4f_mul3(&ret, &m, &v); return ret }
public func *(_ m: TSMatrix4x4f, _ v: TSVector4f) -> TSVector4f { var ret = TSVector4f(), m = m, v = v; tsMatrix4x4f_mul4(&ret, &m, &v); return ret }
public func *(_ v: TSVector2f, _ m: TSMatrix4x4f) -> TSVector2f { var ret = TSVector2f(), v = v, m = m; tsMatrix4x4f_mul2t(&ret, &v, &m); return ret }
public func *(_ v: TSVector3f, _ m: TSMatrix4x4f) -> TSVector3f { var ret = TSVector3f(), v = v, m = m; tsMatrix4x4f_mul3t(&ret, &v, &m); return ret }
public func *(_ v: TSVector4f, _ m: TSMatrix4x4f) -> TSVector4f { var ret = TSVector4f(), v = v, m = m; tsMatrix4x4f_mul4t(&ret, &v, &m); return ret }
public func *(_ m0: TSMatrix4x4f, _ m1: TSMatrix4x4f) -> TSMatrix4x4f { var ret = TSMatrix4x4f(), m0 = m0, m1 = m1; tsMatrix4x4f_mul(&ret, &m0, &m1); return ret }

/*
 */
public func normalize(_ m: TSMatrix4x4f) -> TSMatrix4x4f { var ret = TSMatrix4x4f(), m = m; tsMatrix4x4f_normalize(&ret, &m); return ret }
public func transpose(_ m: TSMatrix4x4f) -> TSMatrix4x4f { var ret = TSMatrix4x4f(), m = m; tsMatrix4x4f_transpose(&ret, &m); return ret }
public func inverse(_ m: TSMatrix4x4f) -> TSMatrix4x4f { var ret = TSMatrix4x4f(), m = m; tsMatrix4x4f_inverse(&ret, &m); return ret }
public func inverse43(_ m: TSMatrix4x4f) -> TSMatrix4x4f { var ret = TSMatrix4x4f(), m = m; tsMatrix4x4f_inverse43(&ret, &m); return ret }

public func lerp(_ m0: TSMatrix4x4f, _ m1: TSMatrix4x4f, _ k: Float32) -> TSMatrix4x4f { var ret = TSMatrix4x4f(), m0 = m0, m1 = m1; tsMatrix4x4f_lerp(&ret, &m0, &m1, k); return ret }

/*****************************************************************************\
 *
 * Matrix4x4d
 *
\*****************************************************************************/

/*
 */
public extension TSMatrix4x4d {
	
	init(_ m: TSMatrix4x3d) { self.init(); self.row_0 = m.row_0; self.row_1 = m.row_1; self.row_2 = m.row_2; self.row_3 = TSVector4d(0.0, 0.0, 0.0, 1.0) }
	init(_ m: TSMatrix4x4f) { self.init(); self.row_0 = TSVector4d(m.row_0); self.row_1 = TSVector4d(m.row_1); self.row_2 = TSVector4d(m.row_2); self.row_3 = TSVector4d(m.row_3) }
	init(_ row_0: TSVector4d, _ row_1: TSVector4d, _ row_2: TSVector4d, _ row_3: TSVector4d) { self.init(); self.row_0 = row_0; self.row_1 = row_1; self.row_2 = row_2; self.row_3 = row_3 }
	init(_ m: [Float64], _ row_major: Bool = true) { self.init(); set(m, row_major) }
	init(_ q: TSQuaterniond) { self.init(); set(q) }
	
	mutating func set(_ src: [Float64], _ row_major: Bool = true) { tsMatrix4x4d_set(&self, src, UInt32(src.count), row_major) }
	func get(_ dest: inout [Float64], _ row_major: Bool = true) { var m = self; tsMatrix4x4d_get(&m, &dest, UInt32(dest.count), row_major) }
	mutating func set(_ q: TSQuaterniond) { var q = q; tsQuaterniond_get(&q, &rows.0); row_3 = TSVector4d(0.0, 0.0, 0.0, 1.0) }
	func get(_ q: inout TSQuaterniond) { var m = self; tsQuaterniond_set(&q, &m.rows.0) }
	
	static func scale(_ s: Float64) -> TSMatrix4x4d { var ret = TSMatrix4x4d(); tsMatrix4x4d_scale(&ret, s, s, s); return ret }
	static func scale(_ x: Float64, _ y: Float64, _ z: Float64) -> TSMatrix4x4d { var ret = TSMatrix4x4d(); tsMatrix4x4d_scale(&ret, x, y, z); return ret }
	static func scale(_ s: TSVector3d) -> TSMatrix4x4d { var ret = TSMatrix4x4d(); tsMatrix4x4d_scale(&ret, s.x, s.y, s.z); return ret }
	static func translate(_ x: Float64, _ y: Float64, _ z: Float64) -> TSMatrix4x4d { var ret = TSMatrix4x4d(); tsMatrix4x4d_translate(&ret, x, y, z); return ret }
	static func translate(_ t: TSVector3d) -> TSMatrix4x4d { var ret = TSMatrix4x4d(); tsMatrix4x4d_translate(&ret, t.x, t.y, t.z); return ret }
	static func rotateX(_ angle: Float64) -> TSMatrix4x4d { var ret = TSMatrix4x4d(); tsMatrix4x4d_rotateX(&ret, angle); return ret }
	static func rotateY(_ angle: Float64) -> TSMatrix4x4d { var ret = TSMatrix4x4d(); tsMatrix4x4d_rotateY(&ret, angle); return ret }
	static func rotateZ(_ angle: Float64) -> TSMatrix4x4d { var ret = TSMatrix4x4d(); tsMatrix4x4d_rotateZ(&ret, angle); return ret }
	static func rotate(_ axis: TSVector3d, _ angle: Float64) -> TSMatrix4x4d { var ret = TSMatrix4x4d(), axis = axis; tsMatrix4x4d_rotate(&ret, &axis, angle); return ret }
	
	static func lookAt(_ from: TSVector3d, _ to: TSVector3d, _ up: TSVector3d) -> TSMatrix4x4d { var ret = TSMatrix4x4d(), from = from, to = to, up = up; tsMatrix4x4d_lookAt(&ret, &from, &to, &up); return ret }
	static func placeTo(_ to: TSVector3d, _ from: TSVector3d, _ up: TSVector3d) -> TSMatrix4x4d { var ret = TSMatrix4x4d(), to = to, from = from, up = up; tsMatrix4x4d_placeTo(&ret, &to, &from, &up); return ret }
	static func compose(_ t: TSVector3d, _ r: TSQuaterniond, _ s: TSVector3d) -> TSMatrix4x4d { var ret = TSMatrix4x4d(), t = t, r = r, s = s; tsMatrix4x4d_compose(&ret, &t, &r, &s); return ret }
	static func basis(_ normal: TSVector3d, _ t: TSVector3d) -> TSMatrix4x4d { var ret = TSMatrix4x4d(), normal = normal, t = t; tsMatrix4x4d_basis(&ret, &normal, &t); return ret }
	
	static func ortho(_ left: Float64, _ right: Float64, _ bottom: Float64, _ top: Float64, _ znear: Float64, _ zfar: Float64) -> TSMatrix4x4d { var ret = TSMatrix4x4d(); tsMatrix4x4d_ortho(&ret, left, right, bottom, top, znear, zfar); return ret }
	static func frustum(_ left: Float64, _ right: Float64, _ bottom: Float64, _ top: Float64, _ znear: Float64, _ zfar: Float64, _ reverse: Bool = false) -> TSMatrix4x4d { var ret = TSMatrix4x4d(); tsMatrix4x4d_frustum(&ret, left, right, bottom, top, znear, zfar, reverse); return ret }
	static func frustum(_ left: Float64, _ right: Float64, _ bottom: Float64, _ top: Float64, _ znear: Float64, _ reverse: Bool = false) -> TSMatrix4x4d { var ret = TSMatrix4x4d(); tsMatrix4x4d_frustumi(&ret, left, right, bottom, top, znear, reverse); return ret }
	static func perspective(_ fov: Float64, _ aspect: Float64, _ znear: Float64, _ zfar: Float64, _ reverse: Bool = false) -> TSMatrix4x4d { var ret = TSMatrix4x4d(); tsMatrix4x4d_perspective(&ret, fov, aspect, znear, zfar, reverse); return ret }
	static func perspective(_ fov: Float64, _ aspect: Float64, _ znear: Float64, _ reverse: Bool = false) -> TSMatrix4x4d { var ret = TSMatrix4x4d(); tsMatrix4x4d_perspectivei(&ret, fov, aspect, znear, reverse); return ret }
	
	static let zero = TSMatrix4x4d(TSVector4d.zero, TSVector4d.zero, TSVector4d.zero, TSVector4d.zero)
	static let identity = TSMatrix4x4d(TSVector4d(1.0, 0.0, 0.0, 0.0), TSVector4d(0.0, 1.0, 0.0, 0.0), TSVector4d(0.0, 0.0, 1.0, 0.0), TSVector4d(0.0, 0.0, 0.0, 1.0))
}

extension TSMatrix4x4d : CustomStringConvertible {
	public var description: String { "(\(row_0) \(row_1) \(row_2) \(row_3))" }
}

/*
 */
public func *(_ m: TSMatrix4x4d, _ v: TSVector2d) -> TSVector2d { var ret = TSVector2d(), m = m, v = v; tsMatrix4x4d_mul2(&ret, &m, &v); return ret }
public func *(_ m: TSMatrix4x4d, _ v: TSVector3d) -> TSVector3d { var ret = TSVector3d(), m = m, v = v; tsMatrix4x4d_mul3(&ret, &m, &v); return ret }
public func *(_ m: TSMatrix4x4d, _ v: TSVector4d) -> TSVector4d { var ret = TSVector4d(), m = m, v = v; tsMatrix4x4d_mul4(&ret, &m, &v); return ret }
public func *(_ v: TSVector2d, _ m: TSMatrix4x4d) -> TSVector2d { var ret = TSVector2d(), v = v, m = m; tsMatrix4x4d_mul2t(&ret, &v, &m); return ret }
public func *(_ v: TSVector3d, _ m: TSMatrix4x4d) -> TSVector3d { var ret = TSVector3d(), v = v, m = m; tsMatrix4x4d_mul3t(&ret, &v, &m); return ret }
public func *(_ v: TSVector4d, _ m: TSMatrix4x4d) -> TSVector4d { var ret = TSVector4d(), v = v, m = m; tsMatrix4x4d_mul4t(&ret, &v, &m); return ret }
public func *(_ m0: TSMatrix4x4d, _ m1: TSMatrix4x4d) -> TSMatrix4x4d { var ret = TSMatrix4x4d(), m0 = m0, m1 = m1; tsMatrix4x4d_mul(&ret, &m0, &m1); return ret }

/*
 */
public func normalize(_ m: TSMatrix4x4d) -> TSMatrix4x4d { var ret = TSMatrix4x4d(), m = m; tsMatrix4x4d_normalize(&ret, &m); return ret }
public func transpose(_ m: TSMatrix4x4d) -> TSMatrix4x4d { var ret = TSMatrix4x4d(), m = m; tsMatrix4x4d_transpose(&ret, &m); return ret }
public func inverse(_ m: TSMatrix4x4d) -> TSMatrix4x4d { var ret = TSMatrix4x4d(), m = m; tsMatrix4x4d_inverse(&ret, &m); return ret }
public func inverse43(_ m: TSMatrix4x4d) -> TSMatrix4x4d { var ret = TSMatrix4x4d(), m = m; tsMatrix4x4d_inverse43(&ret, &m); return ret }

public func lerp(_ m0: TSMatrix4x4d, _ m1: TSMatrix4x4d, _ k: Float64) -> TSMatrix4x4d { var ret = TSMatrix4x4d(), m0 = m0, m1 = m1; tsMatrix4x4d_lerp(&ret, &m0, &m1, k); return ret }

/*****************************************************************************\
 *
 * Quaternionf
 *
\*****************************************************************************/

/*
 */
public extension TSQuaternionf {
	
	init(_ q: TSQuaterniond) { self.init(); self.x = Float32(q.x); self.y = Float32(q.y); self.z = Float32(q.z); self.w = Float32(q.w) }
	init(_ x: Float32, _ y: Float32, _ z: Float32, _ w: Float32) { self.init(); self.x = x; self.y = y; self.z = z; self.w = w }
	init(_ q: [Float32]) { self.init(); self.x = q[0]; self.y = q[1]; self.z = q[2]; self.w = q[3] }
	init(_ m: TSMatrix4x3f) { self.init(); self.set(m) }
	init(_ m: TSMatrix4x4f) { self.init(); self.set(m) }
	
	mutating func set(_ m: TSMatrix4x3f) { var m = m; tsQuaternionf_set(&self, &m.rows.0) }
	mutating func set(_ m: TSMatrix4x4f) { var m = m; tsQuaternionf_set(&self, &m.rows.0) }
	func get(_ m: inout TSMatrix4x3f) { var q = self; tsQuaternionf_get(&q, &m.rows.0) }
	func get(_ m: inout TSMatrix4x4f) { var q = self; tsQuaternionf_get(&q, &m.rows.0) }
	
	static func rotateX(_ angle: Float32) -> TSQuaternionf { var ret = TSQuaternionf(); tsQuaternionf_rotateX(&ret, angle); return ret }
	static func rotateY(_ angle: Float32) -> TSQuaternionf { var ret = TSQuaternionf(); tsQuaternionf_rotateY(&ret, angle); return ret }
	static func rotateZ(_ angle: Float32) -> TSQuaternionf { var ret = TSQuaternionf(); tsQuaternionf_rotateZ(&ret, angle); return ret }
	static func rotateXYZ(_ angles: TSVector3f) -> TSQuaternionf { var ret = TSQuaternionf(), angles = angles; tsQuaternionf_rotateXYZ(&ret, &angles); return ret }
	static func rotateZYX(_ angles: TSVector3f) -> TSQuaternionf { var ret = TSQuaternionf(), angles = angles; tsQuaternionf_rotateZYX(&ret, &angles); return ret }
	static func rotate(_ axis: TSVector3f, _ angle: Float32) -> TSQuaternionf { var ret = TSQuaternionf(), axis = axis; tsQuaternionf_rotate(&ret, &axis, angle); return ret }
	
	static let zero = TSQuaternionf(0.0, 0.0, 0.0, 0.0)
	static let identity = TSQuaternionf(0.0, 0.0, 0.0, 1.0)
}

extension TSQuaternionf : CustomStringConvertible {
	public var description: String { "(\(x) \(y) \(z) \(w))" }
}

/*
 */
public func *(_ q: TSQuaternionf, _ v: TSVector2f) -> TSVector2f { var ret = TSVector2f(), q = q, v = v; tsQuaternionf_mul2(&ret, &q, &v); return ret }
public func *(_ q: TSQuaternionf, _ v: TSVector3f) -> TSVector3f { var ret = TSVector3f(), q = q, v = v; tsQuaternionf_mul3(&ret, &q, &v); return ret }
public func *(_ q: TSQuaternionf, _ v: TSVector4f) -> TSVector4f { var ret = TSVector4f(), q = q, v = v; tsQuaternionf_mul4(&ret, &q, &v); return ret }
public func *(_ v: TSVector2f, _ q: TSQuaternionf) -> TSVector2f { var ret = TSVector2f(), v = v, q = q; tsQuaternionf_mul2t(&ret, &v, &q); return ret }
public func *(_ v: TSVector3f, _ q: TSQuaternionf) -> TSVector3f { var ret = TSVector3f(), v = v, q = q; tsQuaternionf_mul3t(&ret, &v, &q); return ret }
public func *(_ v: TSVector4f, _ q: TSQuaternionf) -> TSVector4f { var ret = TSVector4f(), v = v, q = q; tsQuaternionf_mul4t(&ret, &v, &q); return ret }
public func *(_ q: TSQuaternionf, _ v: Float32) -> TSQuaternionf { var ret = TSQuaternionf(), q = q; tsQuaternionf_mul1(&ret, &q, v); return ret }
public func *(_ q0: TSQuaternionf, _ q1: TSQuaternionf) -> TSQuaternionf { var ret = TSQuaternionf(), q0 = q0, q1 = q1; tsQuaternionf_mul(&ret, &q0, &q1); return ret }

/*
 */
public func normalize(_ q: TSQuaternionf) -> TSQuaternionf { var ret = TSQuaternionf(), q = q; tsQuaternionf_normalize(&ret, &q); return ret }
public func inverse(_ q: TSQuaternionf) -> TSQuaternionf { var ret = TSQuaternionf(), q = q; tsQuaternionf_inverse(&ret, &q); return ret }

public func lerp(_ q0: TSQuaternionf, _ q1: TSQuaternionf, _ k: Float32) -> TSQuaternionf { var ret = TSQuaternionf(), q0 = q0, q1 = q1; tsQuaternionf_lerp(&ret, &q0, &q1, k); return ret }
public func slerp(_ q0: TSQuaternionf, _ q1: TSQuaternionf, _ k: Float32) -> TSQuaternionf { var ret = TSQuaternionf(), q0 = q0, q1 = q1; tsQuaternionf_slerp(&ret, &q0, &q1, k); return ret }

/*****************************************************************************\
 *
 * Quaterniond
 *
\*****************************************************************************/

/*
 */
public extension TSQuaterniond {
	
	init(_ q: TSQuaternionf) { self.init(); self.x = Float64(q.x); self.y = Float64(q.y); self.z = Float64(q.z); self.w = Float64(q.w) }
	init(_ x: Float64, _ y: Float64, _ z: Float64, _ w: Float64) { self.init(); self.x = x; self.y = y; self.z = z; self.w = w }
	init(_ q: [Float64]) { self.init(); self.x = q[0]; self.y = q[1]; self.z = q[2]; self.w = q[3] }
	init(_ m: TSMatrix4x3d) { self.init(); self.set(m) }
	init(_ m: TSMatrix4x4d) { self.init(); self.set(m) }
	
	mutating func set(_ m: TSMatrix4x3d) { var m = m; tsQuaterniond_set(&self, &m.rows.0) }
	mutating func set(_ m: TSMatrix4x4d) { var m = m; tsQuaterniond_set(&self, &m.rows.0) }
	func get(_ m: inout TSMatrix4x3d) { var q = self; tsQuaterniond_get(&q, &m.rows.0) }
	func get(_ m: inout TSMatrix4x4d) { var q = self; tsQuaterniond_get(&q, &m.rows.0) }
	
	static func rotateX(_ angle: Float64) -> TSQuaterniond { var ret = TSQuaterniond(); tsQuaterniond_rotateX(&ret, angle); return ret }
	static func rotateY(_ angle: Float64) -> TSQuaterniond { var ret = TSQuaterniond(); tsQuaterniond_rotateY(&ret, angle); return ret }
	static func rotateZ(_ angle: Float64) -> TSQuaterniond { var ret = TSQuaterniond(); tsQuaterniond_rotateZ(&ret, angle); return ret }
	static func rotateXYZ(_ angles: TSVector3d) -> TSQuaterniond { var ret = TSQuaterniond(), angles = angles; tsQuaterniond_rotateXYZ(&ret, &angles); return ret }
	static func rotateZYX(_ angles: TSVector3d) -> TSQuaterniond { var ret = TSQuaterniond(), angles = angles; tsQuaterniond_rotateZYX(&ret, &angles); return ret }
	static func rotate(_ axis: TSVector3d, _ angle: Float64) -> TSQuaterniond { var ret = TSQuaterniond(), axis = axis; tsQuaterniond_rotate(&ret, &axis, angle); return ret }
	
	static let zero = TSQuaterniond(0.0, 0.0, 0.0, 0.0)
	static let identity = TSQuaterniond(0.0, 0.0, 0.0, 1.0)
}

extension TSQuaterniond : CustomStringConvertible {
	public var description: String { "(\(x) \(y) \(z) \(w))" }
}

/*
 */
public func *(_ q: TSQuaterniond, _ v: TSVector2d) -> TSVector2d { var ret = TSVector2d(), q = q, v = v; tsQuaterniond_mul2(&ret, &q, &v); return ret }
public func *(_ q: TSQuaterniond, _ v: TSVector3d) -> TSVector3d { var ret = TSVector3d(), q = q, v = v; tsQuaterniond_mul3(&ret, &q, &v); return ret }
public func *(_ q: TSQuaterniond, _ v: TSVector4d) -> TSVector4d { var ret = TSVector4d(), q = q, v = v; tsQuaterniond_mul4(&ret, &q, &v); return ret }
public func *(_ v: TSVector2d, _ q: TSQuaterniond) -> TSVector2d { var ret = TSVector2d(), v = v, q = q; tsQuaterniond_mul2t(&ret, &v, &q); return ret }
public func *(_ v: TSVector3d, _ q: TSQuaterniond) -> TSVector3d { var ret = TSVector3d(), v = v, q = q; tsQuaterniond_mul3t(&ret, &v, &q); return ret }
public func *(_ v: TSVector4d, _ q: TSQuaterniond) -> TSVector4d { var ret = TSVector4d(), v = v, q = q; tsQuaterniond_mul4t(&ret, &v, &q); return ret }
public func *(_ q: TSQuaterniond, _ v: Float64) -> TSQuaterniond { var ret = TSQuaterniond(), q = q; tsQuaterniond_mul1(&ret, &q, v); return ret }
public func *(_ q0: TSQuaterniond, _ q1: TSQuaterniond) -> TSQuaterniond { var ret = TSQuaterniond(), q0 = q0, q1 = q1; tsQuaterniond_mul(&ret, &q0, &q1); return ret }

/*
 */
public func normalize(_ q: TSQuaterniond) -> TSQuaterniond { var ret = TSQuaterniond(), q = q; tsQuaterniond_normalize(&ret, &q); return ret }
public func inverse(_ q: TSQuaterniond) -> TSQuaterniond { var ret = TSQuaterniond(), q = q; tsQuaterniond_inverse(&ret, &q); return ret }

public func lerp(_ q0: TSQuaterniond, _ q1: TSQuaterniond, _ k: Float64) -> TSQuaterniond { var ret = TSQuaterniond(), q0 = q0, q1 = q1; tsQuaterniond_lerp(&ret, &q0, &q1, k); return ret }
public func slerp(_ q0: TSQuaterniond, _ q1: TSQuaterniond, _ k: Float64) -> TSQuaterniond { var ret = TSQuaterniond(), q0 = q0, q1 = q1; tsQuaterniond_slerp(&ret, &q0, &q1, k); return ret }

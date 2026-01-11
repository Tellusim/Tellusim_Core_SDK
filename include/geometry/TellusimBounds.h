// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GEOMETRY_BOUNDS_H__
#define __TELLUSIM_GEOMETRY_BOUNDS_H__

#include <TellusimBase.h>
#include <core/TellusimType.h>
#include <math/TellusimMatrix.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	template <class Type, class Vector2> struct BoundRect;
	template <class Type, class Vector2> struct BoundCircle;
	template <class Type, class Vector3> struct BoundBox;
	template <class Type, class Vector3> struct BoundSphere;
	template <class Type> struct BoundFrustum;
	
	/*****************************************************************************\
	 *
	 * BoundRect
	 *
	\*****************************************************************************/
	
	/**
	 * BoundRect class
	 */
	template <class T, class Vector2 = Tellusim::Vector2<T>> struct BoundRect {
		
		using Type = T;
		using Vector = Vector2;
		using BoundCircle = Tellusim::BoundCircle<Type, Vector2>;
		
		BoundRect() : min(Vector2(Maxf32)), max(Vector2(-Maxf32)) { }
		BoundRect(const BoundRect &br) : min(br.min), max(br.max) { }
		BoundRect(const Vector2 &br_min, const Vector2 &br_max) : min(br_min), max(br_max) { }
		BoundRect(const Vector2 &bc_center, Type bc_radius) { set(bc_center, bc_radius); }
		BoundRect(const BoundRect &br, const BoundCircle &bc) { set(br, bc); }
		explicit BoundRect(const BoundCircle &bc) { set(bc.center, bc.radius); }
		template <class CType, class CVector> explicit BoundRect(const Tellusim::BoundRect<CType, CVector> &br) : min(Vector2(br.min)), max(Vector2(br.max)) { }
		template <class CType, class CVector> explicit BoundRect(const Tellusim::BoundCircle<CType, CVector> &bc) { set(Vector2(bc.center), Type(bc.radius)); }
		BoundRect(const Vector2 *TS_RESTRICT points, uint32_t num_points) { set(points, num_points); }
		
		/// clear bound rect
		void clear() {
			min = Vector2(Maxf32);
			max = Vector2(-Maxf32);
		}
		
		/// check bound rect
		TS_INLINE bool isValid() const { return (min.x <= max.x); }
		explicit TS_INLINE operator bool() const { return isValid(); }
		
		/// set bound rect
		TS_INLINE void set(const Vector2 &br_min, const Vector2 &br_max) {
			min = br_min;
			max = br_max;
		}
		TS_INLINE void set(const BoundRect &br) {
			min = br.min;
			max = br.max;
		}
		
		/// set bound circle
		TS_INLINE void set(const Vector2 &bc_center, Type bc_radius) {
			min = bc_center - Vector2(bc_radius);
			max = bc_center + Vector2(bc_radius);
		}
		TS_INLINE void set(const BoundCircle &bc) {
			min = bc.center - Vector2(bc.radius);
			max = bc.center + Vector2(bc.radius);
		}
		
		/// set minimal bound rect
		TS_INLINE void set(const Vector2 &br_min, const Vector2 &br_max, const Vector2 &bc_center, const Type &bc_radius) {
			min = Tellusim::max(br_min, bc_center - Vector2(bc_radius));
			max = Tellusim::min(br_max, bc_center + Vector2(bc_radius));
		}
		TS_INLINE void set(const BoundRect &br, const BoundCircle &bc) {
			set(br.min, br.max, bc.center, bc.radius);
		}
		
		/// set bound rect
		void set(const Vector2 *TS_RESTRICT points, uint32_t num_points) {
			if(num_points > 0) {
				Vector2 br_min = points[0];
				Vector2 br_max = points[0];
				for(uint32_t i = 1; i < num_points; i++) {
					br_min = Tellusim::min(br_min, points[i]);
					br_max = Tellusim::max(br_max, points[i]);
				}
				min = br_min;
				max = br_max;
			} else {
				clear();
			}
		}
		
		/// expand by point
		TS_INLINE void expand(const Vector2 &point) {
			min = Tellusim::min(min, point);
			max = Tellusim::max(max, point);
		}
		
		/// expand by bound rect
		TS_INLINE void expand(const Vector2 &br_min, const Vector2 &br_max) {
			min = Tellusim::min(min, br_min);
			max = Tellusim::max(max, br_max);
		}
		TS_INLINE void expand(const BoundRect &br) {
			expand(br.min, br.max);
		}
		
		/// expand by bound circle
		TS_INLINE void expand(const Vector2 &bc_center, Type bc_radius) {
			min = Tellusim::min(min, bc_center - Vector2(bc_radius));
			max = Tellusim::max(max, bc_center + Vector2(bc_radius));
		}
		TS_INLINE void expand(const BoundCircle &bc) {
			expand(bc.center, bc.radius);
		}
		
		/// inside point
		TS_INLINE bool inside(const Vector2 &point) const {
			if((point.x < min.x) || (max.x < point.x)) return false;
			if((point.y < min.y) || (max.y < point.y)) return false;
			return true;
		}
		
		/// inside bound rect
		TS_INLINE bool inside(const Vector2 &br_min, const Vector2 &br_max) const {
			if((br_max.x < min.x) || (max.x < br_min.x)) return false;
			if((br_max.y < min.y) || (max.y < br_min.y)) return false;
			return true;
		}
		TS_INLINE bool inside(const BoundRect &br) const {
			return inside(br.min, br.max);
		}
		
		/// inside bound circle
		TS_INLINE bool inside(const Vector2 &bc_center, Type bc_radius) const {
			return inside(bc_center - bc_radius, bc_center + bc_radius);
		}
		TS_INLINE bool inside(const BoundCircle &bc) const {
			return inside(bc.center - bc.radius, bc.center + bc.radius);
		}
		
		/// signed distance to the bound rect
		TS_INLINE Type distance(const Vector2 &point) const {
			Vector2 size = max - min;
			Vector2 center = (min + max) * Type(0.5f);
			Vector2 direction = abs(point - center) - size * Type(0.5f);
			Type distance = Tellusim::min(Tellusim::max(direction.x, direction.y), Type(0.0f));
			return length(Tellusim::max(direction, Vector2(0.0f))) + distance;
		}
		
		/// bound rect ray intersection
		TS_INLINE Vector2 trace(const Vector2 &point, const Vector2 &idirection) const {
			Type min_x = (min.x - point.x) * idirection.x;
			Type max_x = (max.x - point.x) * idirection.x;
			Type min_y = (min.y - point.y) * idirection.y;
			Type max_y = (max.y - point.y) * idirection.y;
			if(min_x > max_x) swap(min_x, max_x);
			if(min_y > max_y) swap(min_y, max_y);
			min_x = Tellusim::max(min_x, min_y);
			max_x = Tellusim::min(max_x, max_y);
			return Vector2(min_x, max_x);
		}
		
		/// to bound circle
		TS_INLINE Vector2 getCenter() const {
			return (min + max) * Type(0.5f);
		}
		TS_INLINE Type getRadius() const {
			return length(max - min) * Type(0.5f);
		}
		
		/// bound rect parameters
		TS_INLINE Vector2 getSize() const {
			return max - min;
		}
		TS_INLINE const Vector2 &getMin() const {
			return min;
		}
		TS_INLINE const Vector2 &getMax() const {
			return max;
		}
		TS_INLINE const Vector2 *getPoints() const {
			return points;
		}
		TS_INLINE Type getArea(Type threshold = 1e-8f) const {
			Vector2 size = Tellusim::max(max - min, Vector2(threshold));
			return size.x * size.y;
		}
		
		union {
			struct {
				Vector2 min;	// minimum coordinates
				Vector2 max;	// maximum coordinates
			};
			Vector2 points[2];
		};
	};
	
	/// comparison operators
	template <class Type, class Vector> TS_INLINE bool operator==(const BoundRect<Type, Vector> &br0, const BoundRect<Type, Vector> &br1) {
		return (br0.min == br1.min && br0.max == br1.max);
	}
	
	template <class Type, class Vector> TS_INLINE bool operator!=(const BoundRect<Type, Vector> &br0, const BoundRect<Type, Vector> &br1) {
		return (br0.min != br1.min || br0.max != br1.max);
	}
	
	/// matrix to bound rect multiplication
	template <class LType, class RType, class RVector> TS_INLINE BoundRect<RType, RVector> operator*(const Matrix4x3<LType> &m, const BoundRect<RType, RVector> &br) {
		RVector center = br.getCenter();
		RVector radius = br.max - center;
		RType x = RType(abs(m.m00) * radius.x + abs(m.m01) * radius.y);
		RType y = RType(abs(m.m10) * radius.x + abs(m.m11) * radius.y);
		center = m * center;
		radius.set(x, y);
		return BoundRect<RType, RVector>(center - radius, center + radius);
	}
	
	template <class LType, class RType, class RVector> TS_INLINE BoundRect<RType, RVector> operator*(const Matrix4x4<LType> &m, const BoundRect<RType, RVector> &br) {
		RVector center = br.getCenter();
		RVector radius = br.max - center;
		RType x = RType(abs(m.m00) * radius.x + abs(m.m01) * radius.y);
		RType y = RType(abs(m.m10) * radius.x + abs(m.m11) * radius.y);
		center = m * center;
		radius.set(x, y);
		return BoundRect<RType, RVector>(center - radius, center + radius);
	}
	
	/// BoundRect types
	using BoundRectf = BoundRect<float32_t>;
	using BoundRectd = BoundRect<float64_t>;
	
	/*****************************************************************************\
	 *
	 * BoundCircle
	 *
	\*****************************************************************************/
	
	/**
	 * BoundCircle class
	 */
	template <class T, class Vector2 = Tellusim::Vector2<T>> struct BoundCircle {
		
		using Type = T;
		using Vector = Vector2;
		using BoundRect = Tellusim::BoundRect<Type, Vector2>;
		
		BoundCircle() : center(Vector2(0.0f)), radius(-Maxf32) { }
		BoundCircle(const BoundCircle &bc) : center(bc.center), radius(bc.radius) { }
		BoundCircle(const Vector2 &br_min, const Vector2 &br_max) { set(br_min, br_max); }
		BoundCircle(const Vector2 &bc_center, Type bc_radius) : center(bc_center), radius(bc_radius) { }
		explicit BoundCircle(const BoundRect &br) { set(br.min, br.max); }
		template <class CType, class CVector> explicit BoundCircle(const Tellusim::BoundRect<CType, CVector> &br) { set(Vector2(br.min), Vector2(br.max)); }
		template <class CType, class CVector> explicit BoundCircle(const Tellusim::BoundCircle<CType, CVector> &bc) : center(Vector2(bc.center)), radius(Type(bc.radius)) { }
		BoundCircle(const Vector2 *TS_RESTRICT points, uint32_t num_points) { set(points, num_points); }
		
		/// clear bound circle
		void clear() {
			center = Vector2(0.0f);
			radius = -Maxf32;
		}
		
		/// check bound circle
		TS_INLINE bool isValid() const { return (radius > 0.0f); }
		explicit TS_INLINE operator bool() const { return isValid(); }
		
		/// set bound rect
		TS_INLINE void set(const Vector2 &br_min, const Vector2 &br_max) {
			center = (br_min + br_max) * Type(0.5f);
			radius = length(br_max - center);
		}
		TS_INLINE void set(const BoundRect &br) {
			center = (br.min + br.max) * Type(0.5f);
			radius = length(br.max - center);
		}
		
		/// set bound circle
		TS_INLINE void set(const Vector2 &bc_center, Type bc_radius) {
			center = bc_center;
			radius = bc_radius;
		}
		TS_INLINE void set(const BoundCircle &bc) {
			center = bc.center;
			radius = bc.radius;
		}
		
		/// set bound circle
		void set(const Vector2 *TS_RESTRICT points, uint32_t num_points) {
			if(num_points > 1) {
				radius = Maxf32;
				center = Vector2(0.0f);
				for(uint32_t i = 0; i < 4; i++) {
					Vector2 br_min = points[0];
					Vector2 br_max = points[0];
					Type bc_radius2 = 0.0f;
					Type min_distance = Maxf32;
					Type max_distance = -Maxf32;
					#define TS_DECLARE_BOUND_SPHERE_SET(DISTANCE) { \
						for(uint32_t j = 0; j < num_points; j++) { \
							Type distance = DISTANCE; \
							br_min = select(br_min, points[j], distance - min_distance); \
							br_max = select(br_max, points[j], max_distance - distance); \
							min_distance = min(min_distance, distance); \
							max_distance = max(max_distance, distance); \
						} \
					}
					if(i == 0) TS_DECLARE_BOUND_SPHERE_SET(points[j].x)
					else if(i == 1) TS_DECLARE_BOUND_SPHERE_SET(points[j].y)
					else if(i == 2) TS_DECLARE_BOUND_SPHERE_SET(points[j].x + points[j].y)
					else if(i == 3) TS_DECLARE_BOUND_SPHERE_SET(points[j].x - points[j].y)
					#undef TS_DECLARE_BOUND_SPHERE_SET
					Vector2 bc_center = (br_min + br_max) * Type(0.5f);
					for(uint32_t j = 0; j < num_points; j++) {
						bc_radius2 = max(bc_radius2, length2(points[j] - bc_center));
					}
					Type bc_radius = sqrt(bc_radius2);
					if(radius > bc_radius2) {
						center = bc_center;
						radius = bc_radius;
					}
				}
			} else if(num_points) {
				center = points[0];
				radius = Minf32;
			} else {
				clear();
			}
		}
		
		/// expand by point
		void expand(const Vector2 &point) {
			if(isValid()) {
				Vector2 direction = point - center;
				Type length2 = Tellusim::length2(direction);
				if(length2 > radius * radius) {
					Type length = sqrt(length2);
					center = (point + center + direction * (-radius / length)) * Type(0.5f);
					radius = (radius + length) * 0.5f;
				}
			} else {
				center = point;
				radius = Minf32;
			}
		}
		
		/// expand by bound rect
		void expand(const Vector2 &br_min, const Vector2 &br_max) {
			Vector2 br_center = (br_min + br_max) * Type(0.5f);
			Type br_radius = length(br_max - br_center);
			expand(br_center, br_radius);
		}
		TS_INLINE void expand(const BoundRect &br) {
			expand(br.min, br.max);
		}
		
		/// expand by bound circle
		void expand(const Vector2 &bc_center, Type bc_radius) {
			if(isValid()) {
				Vector2 direction = bc_center - center;
				Type length2 = Tellusim::length2(direction);
				if(length2 > 0.0f) {
					Type length = sqrt(length2);
					if(radius < bc_radius - length) {
						center = bc_center;
						radius = bc_radius;
					} else if(radius < bc_radius + length) {
						center = (bc_center + center + direction * ((bc_radius - radius) / length)) * Type(0.5f);
						radius = (bc_radius + radius + length) * 0.5f;
					}
				} else {
					radius = max(radius, bc_radius);
				}
			} else {
				center = bc_center;
				radius = bc_radius;
			}
		}
		TS_INLINE void expand(const BoundCircle &bc) {
			expand(bc.center, bc.radius);
		}
		
		/// expand by minimal bounds
		TS_INLINE void expand(const Vector2 &br_min, const Vector2 &br_max, const Vector2 &bc_center, Type bc_radius) {
			Vector2 br_center = (br_min + br_max) * Type(0.5f);
			Type br_radius = length(br_max - br_center);
			expand(select(bc_center, br_center, br_radius - bc_radius), min(br_radius, bc_radius));
		}
		TS_INLINE void expand(const BoundRect &br, const BoundCircle &bc) {
			expand(br.min, br.max, bc.center, bc.radius);
		}
		
		/// expand radius by point
		TS_INLINE void expandRadius(const Vector2 &point) {
			radius = max(radius, length(point - center));
		}
		
		/// expand radius by bound rect
		void expandRadius(const Vector2 &br_min, const Vector2 &br_max) {
			radius = max(radius, length(Vector2(br_min.x, br_min.y) - center));
			radius = max(radius, length(Vector2(br_max.x, br_min.y) - center));
			radius = max(radius, length(Vector2(br_min.x, br_max.y) - center));
			radius = max(radius, length(Vector2(br_max.x, br_max.y) - center));
		}
		TS_INLINE void expandRadius(const BoundRect &br) {
			expandRadius(br.min, br.max);
		}
		
		/// expand radius by bound circle
		TS_INLINE void expandRadius(const Vector2 &bc_center, Type bc_radius) {
			radius = max(radius, length(bc_center - center) + bc_radius);
		}
		TS_INLINE void expandRadius(const BoundCircle &bc) {
			expandRadius(bc.center, bc.radius);
		}
		
		/// inside point
		TS_INLINE bool inside(const Vector2 &point) const {
			return (length2(point - center) <= radius * radius);
		}
		
		/// inside bound rect
		TS_INLINE bool inside(const Vector2 &br_min, const Vector2 &br_max) const {
			return (length2(min(max(center, br_min), br_max) - center) <= radius * radius);
		}
		TS_INLINE bool inside(const BoundRect &br) const {
			return inside(br.min, br.max);
		}
		
		/// inside bound circle
		TS_INLINE bool inside(const Vector2 &bc_center, Type bc_radius) const {
			return (length2(bc_center - center) <= (bc_radius + radius) * (bc_radius + radius));
		}
		TS_INLINE bool inside(const BoundCircle &bc) const {
			return inside(bc.center, bc.radius);
		}
		
		/// signed distance to bound circle
		TS_INLINE Type distance(const Vector2 &point) const {
			return length(point - center) - radius;
		}
		
		/// to bound rect
		TS_INLINE Vector2 getMin() const {
			return center - Vector2(radius);
		}
		TS_INLINE Vector2 getMax() const {
			return center + Vector2(radius);
		}
		
		/// bound circle parameters
		TS_INLINE const Vector2 &getCenter() const {
			return center;
		}
		TS_INLINE Type getRadius() const {
			return radius;
		}
		TS_INLINE Type getArea() const {
			return radius * radius * Pi;
		}
		
		Vector2 center;			// center of circle
		Type radius;			// radius of circle
	};
	
	/// comparison operators
	template <class Type, class Vector> TS_INLINE bool operator==(const BoundCircle<Type, Vector> &bc0, const BoundCircle<Type, Vector> &bc1) {
		return (bc0.center == bc1.center && bc0.radius == bc1.radius);
	}
	
	template <class Type, class Vector> TS_INLINE bool operator!=(const BoundCircle<Type, Vector> &bc0, const BoundCircle<Type, Vector> &bc1) {
		return (bc0.center != bc1.center || bc0.radius != bc1.radius);
	}
	
	/// matrix to bound circle multiplication
	template <class LType, class RType, class RVector> TS_INLINE BoundCircle<RType, RVector> operator*(const Matrix4x3<LType> &m, const BoundCircle<RType, RVector> &bc) {
		RVector center = m * bc.center;
		LType x = m.m00 * m.m00 + m.m10 * m.m10;
		LType y = m.m01 * m.m01 + m.m11 * m.m11;
		return BoundCircle<RType, RVector>(center, RType(bc.radius * sqrt(max(x, y))));
	}
	
	template <class LType, class RType, class RVector> TS_INLINE BoundCircle<RType, RVector> operator*(const Matrix4x4<LType> &m, const BoundCircle<RType, RVector> &bc) {
		RVector center = m * bc.center;
		LType x = m.m00 * m.m00 + m.m10 * m.m10;
		LType y = m.m01 * m.m01 + m.m11 * m.m11;
		return BoundCircle<RType, RVector>(center, RType(bc.radius * sqrt(max(x, y))));
	}
	
	/// BoundCircle types
	using BoundCirclef = BoundCircle<float32_t>;
	using BoundCircled = BoundCircle<float64_t>;
	
	/*****************************************************************************\
	 *
	 * BoundBox
	 *
	\*****************************************************************************/
	
	/**
	 * BoundBox class
	 */
	template <class T, class Vector3 = Tellusim::Vector3<T>> struct BoundBox {
		
		using Type = T;
		using Vector = Vector3;
		using Vector2 = Tellusim::Vector2<Type>;
		using BoundSphere = Tellusim::BoundSphere<Type, Vector3>;
		
		BoundBox() : min(Vector3(Maxf32)), max(Vector3(-Maxf32)) { }
		BoundBox(const BoundBox &bb) : min(bb.min), max(bb.max) { }
		BoundBox(const Vector3 &bb_min, const Vector3 &bb_max) : min(bb_min), max(bb_max) { }
		BoundBox(const Vector3 &bs_center, Type bs_radius) { set(bs_center, bs_radius); }
		BoundBox(const BoundBox &bb, const BoundSphere &bs) { set(bb, bs); }
		explicit BoundBox(const BoundSphere &bs) { set(bs.center, bs.radius); }
		template <class CType, class CVector> explicit BoundBox(const Tellusim::BoundBox<CType, CVector> &bb) : min(Vector3(bb.min)), max(Vector3(bb.max)) { }
		template <class CType, class CVector> explicit BoundBox(const Tellusim::BoundSphere<CType, CVector> &bs) { set(Vector3(bs.center), Type(bs.radius)); }
		BoundBox(const Vector3 *TS_RESTRICT points, uint32_t num_points) { set(points, num_points); }
		
		/// clear bound box
		void clear() {
			min = Vector3(Maxf32);
			max = Vector3(-Maxf32);
		}
		
		/// check bound box
		TS_INLINE bool isValid() const { return (min.x <= max.x); }
		explicit TS_INLINE operator bool() const { return isValid(); }
		
		/// set bound box
		TS_INLINE void set(const Vector3 &bb_min, const Vector3 &bb_max) {
			min = bb_min;
			max = bb_max;
		}
		TS_INLINE void set(const BoundBox &bb) {
			min = bb.min;
			max = bb.max;
		}
		
		/// set bound sphere
		TS_INLINE void set(const Vector3 &bs_center, Type bs_radius) {
			min = bs_center - Vector3(bs_radius);
			max = bs_center + Vector3(bs_radius);
		}
		TS_INLINE void set(const BoundSphere &bs) {
			min = bs.center - Vector3(bs.radius);
			max = bs.center + Vector3(bs.radius);
		}
		
		/// set minimal bound box
		TS_INLINE void set(const Vector3 &bb_min, const Vector3 &bb_max, const Vector3 &bs_center, Type bs_radius) {
			min = Tellusim::max(bb_min, bs_center - Vector3(bs_radius));
			max = Tellusim::min(bb_max, bs_center + Vector3(bs_radius));
		}
		TS_INLINE void set(const BoundBox &bb, const BoundSphere &bs) {
			set(bb.min, bb.max, bs.center, bs.radius);
		}
		
		/// set bound box
		void set(const Vector3 *TS_RESTRICT points, uint32_t num_points) {
			if(num_points > 0) {
				Vector3 bb_min = points[0];
				Vector3 bb_max = points[0];
				for(uint32_t i = 1; i < num_points; i++) {
					bb_min = Tellusim::min(bb_min, points[i]);
					bb_max = Tellusim::max(bb_max, points[i]);
				}
				min = bb_min;
				max = bb_max;
			} else {
				clear();
			}
		}
		
		/// expand by point
		TS_INLINE void expand(const Vector3 &point) {
			min = Tellusim::min(min, point);
			max = Tellusim::max(max, point);
		}
		
		/// expand by bound box
		TS_INLINE void expand(const Vector3 &bb_min, const Vector3 &bb_max) {
			min = Tellusim::min(min, bb_min);
			max = Tellusim::max(max, bb_max);
		}
		TS_INLINE void expand(const BoundBox &bb) {
			expand(bb.min, bb.max);
		}
		
		/// expand by bound sphere
		TS_INLINE void expand(const Vector3 &bs_center, Type bs_radius) {
			min = Tellusim::min(min, bs_center - Vector3(bs_radius));
			max = Tellusim::max(max, bs_center + Vector3(bs_radius));
		}
		TS_INLINE void expand(const BoundSphere &bs) {
			expand(bs.center, bs.radius);
		}
		
		/// expand by minimal bounds
		TS_INLINE void expand(const Vector3 &bb_min, const Vector3 &bb_max, const Vector3 &bs_center, Type bs_radius) {
			min = Tellusim::min(min, Tellusim::max(bb_min, bs_center - Vector3(bs_radius)));
			max = Tellusim::max(max, Tellusim::min(bb_max, bs_center + Vector3(bs_radius)));
		}
		TS_INLINE void expand(const BoundBox &bb, const BoundSphere &bs) {
			expand(bb.min, bb.max, bs.center, bs.radius);
		}
		
		/// shrink by bound box
		TS_INLINE void shrink(const Vector3 &bb_min, const Vector3 &bb_max) {
			min = Tellusim::max(min, bb_min);
			max = Tellusim::min(max, bb_max);
		}
		TS_INLINE void shrink(const BoundBox &bb) {
			shrink(bb.min, bb.max);
		}
		
		/// shrink by bound sphere
		TS_INLINE void shrink(const Vector3 &bs_center, Type bs_radius) {
			min = Tellusim::max(min, bs_center - Vector3(bs_radius));
			max = Tellusim::min(max, bs_center + Vector3(bs_radius));
		}
		TS_INLINE void shrink(const BoundSphere &bs) {
			shrink(bs.center, bs.radius);
		}
		
		/// inside point
		TS_INLINE bool inside(const Vector3 &point) const {
			if((point.x < min.x) || (max.x < point.x)) return false;
			if((point.y < min.y) || (max.y < point.y)) return false;
			if((point.z < min.z) || (max.z < point.z)) return false;
			return true;
		}
		
		/// inside bound box
		TS_INLINE bool inside(const Vector3 &bb_min, const Vector3 &bb_max) const {
			if((bb_max.x < min.x) || (max.x < bb_min.x)) return false;
			if((bb_max.y < min.y) || (max.y < bb_min.y)) return false;
			if((bb_max.z < min.z) || (max.z < bb_min.z)) return false;
			return true;
		}
		TS_INLINE bool inside(const BoundBox &bb) const {
			return inside(bb.min, bb.max);
		}
		
		/// inside bound sphere
		TS_INLINE bool inside(const Vector3 &bs_center, Type bs_radius) const {
			return inside(bs_center - bs_radius, bs_center + bs_radius);
		}
		TS_INLINE bool inside(const BoundSphere &bs) const {
			return inside(bs.center - bs.radius, bs.center + bs.radius);
		}
		
		/// signed distance to the bound box
		TS_INLINE Type distance(const Vector3 &point) const {
			Vector3 size = max - min;
			Vector3 center = (min + max) * Type(0.5f);
			Vector3 direction = abs(point - center) - size * Type(0.5f);
			Type distance = Tellusim::min(Tellusim::max(direction.x, direction.y, direction.z), Type(0.0f));
			return length(Tellusim::max(direction, Vector3(0.0f))) + distance;
		}
		
		/// bound box ray intersection
		TS_INLINE Vector2 trace(const Vector3 &point, const Vector3 &idirection) const {
			Type min_x = (min.x - point.x) * idirection.x;
			Type max_x = (max.x - point.x) * idirection.x;
			Type min_y = (min.y - point.y) * idirection.y;
			Type max_y = (max.y - point.y) * idirection.y;
			Type min_z = (min.z - point.z) * idirection.z;
			Type max_z = (max.z - point.z) * idirection.z;
			if(min_x > max_x) swap(min_x, max_x);
			if(min_y > max_y) swap(min_y, max_y);
			if(min_z > max_z) swap(min_z, max_z);
			min_x = Tellusim::max(min_x, min_y, min_z);
			max_x = Tellusim::min(max_x, max_y, max_z);
			return Vector2(min_x, max_x);
		}
		
		/// to bound sphere
		TS_INLINE Vector3 getCenter() const {
			return (min + max) * Type(0.5f);
		}
		TS_INLINE Type getRadius() const {
			return length(max - min) * Type(0.5f);
		}
		
		/// bound box parameters
		TS_INLINE Vector3 getSize() const {
			return max - min;
		}
		TS_INLINE const Vector3 &getMin() const {
			return min;
		}
		TS_INLINE const Vector3 &getMax() const {
			return max;
		}
		TS_INLINE const Vector3 *getPoints() const {
			return points;
		}
		TS_INLINE Type getVolume(Type threshold = 1e-8f) const {
			Vector3 size = Tellusim::max(max - min, Vector3(threshold));
			return size.x * size.y * size.z;
		}
		
		union {
			struct {
				Vector3 min;	// minimum coordinates
				Vector3 max;	// maximum coordinates
			};
			Vector3 points[2];
		};
	};
	
	/// comparison operators
	template <class Type, class Vector> TS_INLINE bool operator==(const BoundBox<Type, Vector> &bb0, const BoundBox<Type, Vector> &bb1) {
		return (bb0.min == bb1.min && bb0.max == bb1.max);
	}
	
	template <class Type, class Vector> TS_INLINE bool operator!=(const BoundBox<Type, Vector> &bb0, const BoundBox<Type, Vector> &bb1) {
		return (bb0.min != bb1.min || bb0.max != bb1.max);
	}
	
	/// matrix to bound box multiplication
	template <class LType, class RType, class RVector> TS_INLINE BoundBox<RType, RVector> operator*(const Matrix4x3<LType> &m, const BoundBox<RType, RVector> &bb) {
		RVector center = bb.getCenter();
		RVector radius = bb.max - center;
		RType x = RType(radius.x * abs(m.m00) + radius.y * abs(m.m01) + radius.z * abs(m.m02));
		RType y = RType(radius.x * abs(m.m10) + radius.y * abs(m.m11) + radius.z * abs(m.m12));
		RType z = RType(radius.x * abs(m.m20) + radius.y * abs(m.m21) + radius.z * abs(m.m22));
		center = m * center;
		radius.set(x, y, z);
		return BoundBox<RType, RVector>(center - radius, center + radius);
	}
	
	template <class LType, class RType, class RVector> TS_INLINE BoundBox<RType, RVector> operator*(const Matrix4x4<LType> &m, const BoundBox<RType, RVector> &bb) {
		RVector center = bb.getCenter();
		RVector radius = bb.max - center;
		RType x = RType(radius.x * abs(m.m00) + radius.y * abs(m.m01) + radius.z * abs(m.m02));
		RType y = RType(radius.x * abs(m.m10) + radius.y * abs(m.m11) + radius.z * abs(m.m12));
		RType z = RType(radius.x * abs(m.m20) + radius.y * abs(m.m21) + radius.z * abs(m.m22));
		center = m * center;
		radius.set(x, y, z);
		return BoundBox<RType, RVector>(center - radius, center + radius);
	}
	
	/// BoundBox types
	using BoundBoxf = BoundBox<float32_t>;
	using BoundBoxd = BoundBox<float64_t>;
	
	/*****************************************************************************\
	 *
	 * BoundSphere
	 *
	\*****************************************************************************/
	
	/**
	 * BoundSphere class
	 */
	template <class T, class Vector3 = Tellusim::Vector3<T>> struct BoundSphere {
		
		using Type = T;
		using Vector = Vector3;
		using BoundBox = Tellusim::BoundBox<Type, Vector3>;
		
		BoundSphere() : center(Vector3(0.0f)), radius(-Maxf32) { }
		BoundSphere(const BoundSphere &bs) : center(bs.center), radius(bs.radius) { }
		BoundSphere(const Vector3 &bb_min, const Vector3 &bb_max) { set(bb_min, bb_max); }
		BoundSphere(const Vector3 &bs_center, Type bs_radius) : center(bs_center), radius(bs_radius) { }
		explicit BoundSphere(const BoundBox &bb) { set(bb.min, bb.max); }
		template <class CType, class CVector> explicit BoundSphere(const Tellusim::BoundBox<CType, CVector> &bb) { set(Vector3(bb.min), Vector3(bb.max)); }
		template <class CType, class CVector> explicit BoundSphere(const Tellusim::BoundSphere<CType, CVector> &bs) : center(Vector3(bs.center)), radius(Type(bs.radius)) { }
		BoundSphere(const Vector3 *TS_RESTRICT points, uint32_t num_points) { set(points, num_points); }
		
		/// clear bound sphere
		void clear() {
			center = Vector3(0.0f);
			radius = -Maxf32;
		}
		
		/// check bound sphere
		TS_INLINE bool isValid() const { return (radius > 0.0f); }
		explicit TS_INLINE operator bool() const { return isValid(); }
		
		/// set bound box
		TS_INLINE void set(const Vector3 &bb_min, const Vector3 &bb_max) {
			center = (bb_min + bb_max) * Type(0.5f);
			radius = length(bb_max - center);
		}
		TS_INLINE void set(const BoundBox &bb) {
			center = (bb.min + bb.max) * Type(0.5f);
			radius = length(bb.max - center);
		}
		
		/// set bound sphere
		TS_INLINE void set(const Vector3 &bs_center, Type bs_radius) {
			center = bs_center;
			radius = bs_radius;
		}
		TS_INLINE void set(const BoundSphere &bs) {
			center = bs.center;
			radius = bs.radius;
		}
		
		/// set bound sphere
		void set(const Vector3 *TS_RESTRICT points, uint32_t num_points) {
			if(num_points > 1) {
				radius = Maxf32;
				center = Vector3(0.0f);
				for(uint32_t i = 0; i < 13; i++) {
					Vector3 bb_min = points[0];
					Vector3 bb_max = points[0];
					Type bs_radius2 = 0.0f;
					Type min_distance = Maxf32;
					Type max_distance = -Maxf32;
					#define TS_DECLARE_BOUND_SPHERE_SET(DISTANCE) { \
						for(uint32_t j = 0; j < num_points; j++) { \
							Type distance = DISTANCE; \
							bb_min = select(bb_min, points[j], distance - min_distance); \
							bb_max = select(bb_max, points[j], max_distance - distance); \
							min_distance = min(min_distance, distance); \
							max_distance = max(max_distance, distance); \
						} \
					}
					if(i == 0) TS_DECLARE_BOUND_SPHERE_SET(points[j].x)
					else if(i == 1) TS_DECLARE_BOUND_SPHERE_SET(points[j].y)
					else if(i == 2) TS_DECLARE_BOUND_SPHERE_SET(points[j].z)
					else if(i == 3) TS_DECLARE_BOUND_SPHERE_SET(points[j].x + points[j].y)
					else if(i == 4) TS_DECLARE_BOUND_SPHERE_SET(points[j].x - points[j].y)
					else if(i == 5) TS_DECLARE_BOUND_SPHERE_SET(points[j].x + points[j].z)
					else if(i == 6) TS_DECLARE_BOUND_SPHERE_SET(points[j].x - points[j].z)
					else if(i == 7) TS_DECLARE_BOUND_SPHERE_SET(points[j].y + points[j].z)
					else if(i == 8) TS_DECLARE_BOUND_SPHERE_SET(points[j].y - points[j].z)
					else if(i == 9)  TS_DECLARE_BOUND_SPHERE_SET(points[j].x + points[j].y + points[j].z)
					else if(i == 10) TS_DECLARE_BOUND_SPHERE_SET(points[j].x + points[j].y - points[j].z)
					else if(i == 11) TS_DECLARE_BOUND_SPHERE_SET(points[j].x - points[j].y + points[j].z)
					else if(i == 12) TS_DECLARE_BOUND_SPHERE_SET(points[j].x - points[j].y - points[j].z)
					#undef TS_DECLARE_BOUND_SPHERE_SET
					Vector3 bs_center = (bb_min + bb_max) * Type(0.5f);
					for(uint32_t j = 0; j < num_points; j++) {
						bs_radius2 = max(bs_radius2, length2(points[j] - bs_center));
					}
					Type bs_radius = sqrt(bs_radius2);
					if(radius > bs_radius2) {
						center = bs_center;
						radius = bs_radius;
					}
				}
			} else if(num_points) {
				center = points[0];
				radius = Minf32;
			} else {
				clear();
			}
		}
		
		/// expand by point
		void expand(const Vector3 &point) {
			if(isValid()) {
				Vector3 direction = point - center;
				Type length2 = Tellusim::length2(direction);
				if(length2 > radius * radius) {
					Type length = sqrt(length2);
					center = (point + center + direction * (-radius / length)) * Type(0.5f);
					radius = (radius + length) * 0.5f;
				}
			} else {
				center = point;
				radius = Minf32;
			}
		}
		
		/// expand by bound box
		void expand(const Vector3 &bb_min, const Vector3 &bb_max) {
			Vector3 bb_center = (bb_min + bb_max) * Type(0.5f);
			Type bb_radius = length(bb_max - bb_center);
			expand(bb_center, bb_radius);
		}
		TS_INLINE void expand(const BoundBox &bb) {
			expand(bb.min, bb.max);
		}
		
		/// expand by bound sphere
		void expand(const Vector3 &bs_center, Type bs_radius) {
			if(isValid()) {
				Vector3 direction = bs_center - center;
				Type length2 = Tellusim::length2(direction);
				if(length2 > 0.0f) {
					Type length = sqrt(length2);
					if(radius < bs_radius - length) {
						center = bs_center;
						radius = bs_radius;
					} else if(radius < bs_radius + length) {
						center = (bs_center + center + direction * ((bs_radius - radius) / length)) * Type(0.5f);
						radius = (bs_radius + radius + length) * 0.5f;
					}
				} else {
					radius = max(radius, bs_radius);
				}
			} else {
				center = bs_center;
				radius = bs_radius;
			}
		}
		TS_INLINE void expand(const BoundSphere &bs) {
			expand(bs.center, bs.radius);
		}
		
		/// expand by minimal bounds
		TS_INLINE void expand(const Vector3 &bb_min, const Vector3 &bb_max, const Vector3 &bs_center, Type bs_radius) {
			Vector3 bb_center = (bb_min + bb_max) * Type(0.5f);
			Type bb_radius = length(bb_max - bb_center);
			expand(select(bs_center, bb_center, bb_radius - bs_radius), min(bb_radius, bs_radius));
		}
		TS_INLINE void expand(const BoundBox &bb, const BoundSphere &bs) {
			expand(bb.min, bb.max, bs.center, bs.radius);
		}
		
		/// expand radius by point
		TS_INLINE void expandRadius(const Vector3 &point) {
			radius = max(radius, length(point - center));
		}
		
		/// expand radius by bound box
		void expandRadius(const Vector3 &bb_min, const Vector3 &bb_max) {
			radius = max(radius, length(Vector3(bb_min.x, bb_min.y, bb_min.z) - center));
			radius = max(radius, length(Vector3(bb_max.x, bb_min.y, bb_min.z) - center));
			radius = max(radius, length(Vector3(bb_min.x, bb_max.y, bb_min.z) - center));
			radius = max(radius, length(Vector3(bb_max.x, bb_max.y, bb_min.z) - center));
			radius = max(radius, length(Vector3(bb_min.x, bb_min.y, bb_max.z) - center));
			radius = max(radius, length(Vector3(bb_max.x, bb_min.y, bb_max.z) - center));
			radius = max(radius, length(Vector3(bb_min.x, bb_max.y, bb_max.z) - center));
			radius = max(radius, length(Vector3(bb_max.x, bb_max.y, bb_max.z) - center));
		}
		TS_INLINE void expandRadius(const BoundBox &bb) {
			expandRadius(bb.min, bb.max);
		}
		
		/// expand radius by bound sphere
		TS_INLINE void expandRadius(const Vector3 &bs_center, Type bs_radius) {
			radius = max(radius, length(bs_center - center) + bs_radius);
		}
		TS_INLINE void expandRadius(const BoundSphere &bs) {
			expandRadius(bs.center, bs.radius);
		}
		
		/// inside point
		TS_INLINE bool inside(const Vector3 &point) const {
			return (length2(point - center) <= radius * radius);
		}
		
		/// inside bound box
		TS_INLINE bool inside(const Vector3 &bb_min, const Vector3 &bb_max) const {
			return (length2(min(max(center, bb_min), bb_max) - center) <= radius * radius);
		}
		TS_INLINE bool inside(const BoundBox &bb) const {
			return inside(bb.min, bb.max);
		}
		
		/// inside bound sphere
		TS_INLINE bool inside(const Vector3 &bs_center, Type bs_radius) const {
			return (length2(bs_center - center) <= (bs_radius + radius) * (bs_radius + radius));
		}
		TS_INLINE bool inside(const BoundSphere &bs) const {
			return inside(bs.center, bs.radius);
		}
		
		/// signed distance to bound sphere
		TS_INLINE Type distance(const Vector3 &point) const {
			return length(point - center) - radius;
		}
		
		/// to bound box
		TS_INLINE Vector3 getMin() const {
			return center - Vector3(radius);
		}
		TS_INLINE Vector3 getMax() const {
			return center + Vector3(radius);
		}
		
		/// bound sphere parameters
		TS_INLINE const Vector3 &getCenter() const {
			return center;
		}
		TS_INLINE Type getRadius() const {
			return radius;
		}
		TS_INLINE Type getVolume() const {
			return radius * radius * radius * (4.0f / 3.0f * Pi);
		}
		
		Vector3 center;			// center of sphere
		Type radius;			// radius of sphere
	};
	
	/// comparison operators
	template <class Type, class Vector> TS_INLINE bool operator==(const BoundSphere<Type, Vector> &bs0, const BoundSphere<Type, Vector> &bs1) {
		return (bs0.center == bs1.center && bs0.radius == bs1.radius);
	}
	
	template <class Type, class Vector> TS_INLINE bool operator!=(const BoundSphere<Type, Vector> &bs0, const BoundSphere<Type, Vector> &bs1) {
		return (bs0.center != bs1.center || bs0.radius != bs1.radius);
	}
	
	/// matrix to bound sphere multiplication
	template <class LType, class RType, class RVector> TS_INLINE BoundSphere<RType, RVector> operator*(const Matrix4x3<LType> &m, const BoundSphere<RType, RVector> &bs) {
		RVector center = m * bs.center;
		LType x = m.m00 * m.m00 + m.m10 * m.m10 + m.m20 * m.m20;
		LType y = m.m01 * m.m01 + m.m11 * m.m11 + m.m21 * m.m21;
		LType z = m.m02 * m.m02 + m.m12 * m.m12 + m.m22 * m.m22;
		return BoundSphere<RType, RVector>(center, RType(bs.radius * sqrt(max(x, y, z))));
	}
	
	template <class LType, class RType, class RVector> TS_INLINE BoundSphere<RType, RVector> operator*(const Matrix4x4<LType> &m, const BoundSphere<RType, RVector> &bs) {
		RVector center = m * bs.center;
		LType x = m.m00 * m.m00 + m.m10 * m.m10 + m.m20 * m.m20;
		LType y = m.m01 * m.m01 + m.m11 * m.m11 + m.m21 * m.m21;
		LType z = m.m02 * m.m02 + m.m12 * m.m12 + m.m22 * m.m22;
		return BoundSphere<RType, RVector>(center, RType(bs.radius * sqrt(max(x, y, z))));
	}
	
	/// BoundSphere types
	using BoundSpheref = BoundSphere<float32_t>;
	using BoundSphered = BoundSphere<float64_t>;
	
	/*****************************************************************************\
	 *
	 * BoundFrustum
	 *
	\*****************************************************************************/
	
	/**
	 * BoundFrustum class
	 */
	template <class T> struct BoundFrustum {
		
		using Type = T;
		using Vector3 = Tellusim::Vector3<Type>;
		using Vector4 = Tellusim::Vector4<Type>;
		using Matrix4x4 = Tellusim::Matrix4x4<Type>;
		
		BoundFrustum() { }
		BoundFrustum(const Matrix4x4 &projection, const Matrix4x4 &modelview, Type aspect = 1.0f) { set(projection, modelview, aspect); }
		BoundFrustum(const BoundFrustum &bf) : projection(bf.projection), modelview(bf.modelview), camera(bf.camera) {
			for(uint32_t i = 0; i < 6; i++) {
				planes[i] = bf.planes[i];
				signs[i][0] = bf.signs[i][0];
				signs[i][1] = bf.signs[i][1];
				signs[i][2] = bf.signs[i][2];
			}
		}
		template<class CType> explicit BoundFrustum(const BoundFrustum<CType> &bf) : projection(Matrix4x4(bf.projection)), modelview(Matrix4x4(bf.modelview)), camera(Vector3(bf.camera)) {
			for(uint32_t i = 0; i < 6; i++) {
				planes[i] = Vector4(bf.planes[i]);
				signs[i][0] = bf.signs[i][0];
				signs[i][1] = bf.signs[i][1];
				signs[i][2] = bf.signs[i][2];
			}
		}
		
		/// bound frustum from matrix
		void set(const Matrix4x4 &p, const Matrix4x4 &m, Type aspect = 1.0f) {
			
			projection = p;
			if(aspect != 1.0f) projection.m00 /= aspect;
			
			modelview = m;
			camera = inverse43(modelview).getTranslate();
			
			Matrix4x4 mvp = projection * modelview;
			plane_l.set(mvp.m30 + mvp.m00, mvp.m31 + mvp.m01, mvp.m32 + mvp.m02, mvp.m33 + mvp.m03);
			plane_r.set(mvp.m30 - mvp.m00, mvp.m31 - mvp.m01, mvp.m32 - mvp.m02, mvp.m33 - mvp.m03);
			plane_b.set(mvp.m30 + mvp.m10, mvp.m31 + mvp.m11, mvp.m32 + mvp.m12, mvp.m33 + mvp.m13);
			plane_t.set(mvp.m30 - mvp.m10, mvp.m31 - mvp.m11, mvp.m32 - mvp.m12, mvp.m33 - mvp.m13);
			plane_n.set(mvp.m30 + mvp.m20, mvp.m31 + mvp.m21, mvp.m32 + mvp.m22, mvp.m33 + mvp.m23);
			plane_f.set(mvp.m30 - mvp.m20, mvp.m31 - mvp.m21, mvp.m32 - mvp.m22, mvp.m33 - mvp.m23);
			plane_l /= length3(plane_l);
			plane_r /= length3(plane_r);
			plane_b /= length3(plane_b);
			plane_t /= length3(plane_t);
			plane_n /= length3(plane_n);
			plane_f /= length3(plane_f);
			
			for(uint32_t i = 0; i < 3; i++) {
				sign_l[i] = (plane_l.v[i] > 0.0f) ? 1 : 0;
				sign_r[i] = (plane_r.v[i] > 0.0f) ? 1 : 0;
				sign_b[i] = (plane_b.v[i] > 0.0f) ? 1 : 0;
				sign_t[i] = (plane_t.v[i] > 0.0f) ? 1 : 0;
				sign_n[i] = (plane_n.v[i] > 0.0f) ? 1 : 0;
				sign_f[i] = (plane_f.v[i] > 0.0f) ? 1 : 0;
			}
		}
		
		/// inside bound box
		template <class BType, class BVector> bool inside4(const BoundBox<BType, BVector> &bb) const {
			const BVector *points = bb.points;
			if(points[sign_l[0]].x * plane_l.x + points[sign_l[1]].y * plane_l.y + points[sign_l[2]].z * plane_l.z + plane_l.w < 0.0f) return false;
			if(points[sign_r[0]].x * plane_r.x + points[sign_r[1]].y * plane_r.y + points[sign_r[2]].z * plane_r.z + plane_r.w < 0.0f) return false;
			if(points[sign_b[0]].x * plane_b.x + points[sign_b[1]].y * plane_b.y + points[sign_b[2]].z * plane_b.z + plane_b.w < 0.0f) return false;
			if(points[sign_t[0]].x * plane_t.x + points[sign_t[1]].y * plane_t.y + points[sign_t[2]].z * plane_t.z + plane_t.w < 0.0f) return false;
			return true;
		}
		template <class BType, class BVector> bool inside(const BoundBox<BType, BVector> &bb) const {
			const BVector *points = bb.points;
			if(points[sign_l[0]].x * plane_l.x + points[sign_l[1]].y * plane_l.y + points[sign_l[2]].z * plane_l.z + plane_l.w < 0.0f) return false;
			if(points[sign_r[0]].x * plane_r.x + points[sign_r[1]].y * plane_r.y + points[sign_r[2]].z * plane_r.z + plane_r.w < 0.0f) return false;
			if(points[sign_b[0]].x * plane_b.x + points[sign_b[1]].y * plane_b.y + points[sign_b[2]].z * plane_b.z + plane_b.w < 0.0f) return false;
			if(points[sign_t[0]].x * plane_t.x + points[sign_t[1]].y * plane_t.y + points[sign_t[2]].z * plane_t.z + plane_t.w < 0.0f) return false;
			if(points[sign_n[0]].x * plane_n.x + points[sign_n[1]].y * plane_n.y + points[sign_n[2]].z * plane_n.z + plane_n.w < 0.0f) return false;
			if(points[sign_f[0]].x * plane_f.x + points[sign_f[1]].y * plane_f.y + points[sign_f[2]].z * plane_f.z + plane_f.w < 0.0f) return false;
			return true;
		}
		template <class BType, class BVector> bool insideAll4(const BoundBox<BType, BVector> &bb) const {
			const BVector *points = bb.points;
			if(points[1 - sign_l[0]].x * plane_l.x + points[1 - sign_l[1]].y * plane_l.y + points[1 - sign_l[2]].z * plane_l.z + plane_l.w < 0.0f) return false;
			if(points[1 - sign_r[0]].x * plane_r.x + points[1 - sign_r[1]].y * plane_r.y + points[1 - sign_r[2]].z * plane_r.z + plane_r.w < 0.0f) return false;
			if(points[1 - sign_b[0]].x * plane_b.x + points[1 - sign_b[1]].y * plane_b.y + points[1 - sign_b[2]].z * plane_b.z + plane_b.w < 0.0f) return false;
			if(points[1 - sign_t[0]].x * plane_t.x + points[1 - sign_t[1]].y * plane_t.y + points[1 - sign_t[2]].z * plane_t.z + plane_t.w < 0.0f) return false;
			return true;
		}
		template <class BType, class BVector> bool insideAll(const BoundBox<BType, BVector> &bb) const {
			const BVector *points = bb.points;
			if(points[1 - sign_l[0]].x * plane_l.x + points[1 - sign_l[1]].y * plane_l.y + points[1 - sign_l[2]].z * plane_l.z + plane_l.w < 0.0f) return false;
			if(points[1 - sign_r[0]].x * plane_r.x + points[1 - sign_r[1]].y * plane_r.y + points[1 - sign_r[2]].z * plane_r.z + plane_r.w < 0.0f) return false;
			if(points[1 - sign_b[0]].x * plane_b.x + points[1 - sign_b[1]].y * plane_b.y + points[1 - sign_b[2]].z * plane_b.z + plane_b.w < 0.0f) return false;
			if(points[1 - sign_t[0]].x * plane_t.x + points[1 - sign_t[1]].y * plane_t.y + points[1 - sign_t[2]].z * plane_t.z + plane_t.w < 0.0f) return false;
			if(points[1 - sign_n[0]].x * plane_n.x + points[1 - sign_n[1]].y * plane_n.y + points[1 - sign_n[2]].z * plane_n.z + plane_n.w < 0.0f) return false;
			if(points[1 - sign_f[0]].x * plane_f.x + points[1 - sign_f[1]].y * plane_f.y + points[1 - sign_f[2]].z * plane_f.z + plane_f.w < 0.0f) return false;
			return true;
		}
		
		/// inside bound sphere
		template <class BType, class BVector> bool inside4(const BoundSphere<BType, BVector> &bs) const {
			BType radius = -bs.radius;
			BVector center = bs.center;
			if(dot(plane_l, center) < radius) return false;
			if(dot(plane_r, center) < radius) return false;
			if(dot(plane_b, center) < radius) return false;
			if(dot(plane_t, center) < radius) return false;
			return true;
		}
		template <class BType, class BVector> bool inside(const BoundSphere<BType, BVector> &bs) const {
			BType radius = -bs.radius;
			BVector center = bs.center;
			if(dot(plane_l, center) < radius) return false;
			if(dot(plane_r, center) < radius) return false;
			if(dot(plane_b, center) < radius) return false;
			if(dot(plane_t, center) < radius) return false;
			if(dot(plane_n, center) < radius) return false;
			if(dot(plane_f, center) < radius) return false;
			return true;
		}
		template <class BType, class BVector> bool insideAll4(const BoundSphere<BType, BVector> &bs) const {
			BType radius = bs.radius;
			BVector center = bs.center;
			if(dot(plane_l, center) < radius) return false;
			if(dot(plane_r, center) < radius) return false;
			if(dot(plane_b, center) < radius) return false;
			if(dot(plane_t, center) < radius) return false;
			return true;
		}
		template <class BType, class BVector> bool insideAll(const BoundSphere<BType, BVector> &bs) const {
			BType radius = bs.radius;
			BVector center = bs.center;
			if(dot(plane_l, center) < radius) return false;
			if(dot(plane_r, center) < radius) return false;
			if(dot(plane_b, center) < radius) return false;
			if(dot(plane_t, center) < radius) return false;
			if(dot(plane_n, center) < radius) return false;
			if(dot(plane_f, center) < radius) return false;
			return true;
		}
		
		/// bound frustum parameters
		TS_INLINE const Matrix4x4 &getProjection() const {
			return projection;
		}
		TS_INLINE const Matrix4x4 &getModelview() const {
			return modelview;
		}
		TS_INLINE const Vector3 &getCamera() const {
			return camera;
		}
		
		Matrix4x4 projection;			// projection matrix
		Matrix4x4 modelview;			// modelview matrix
		Vector3 camera;					// camera position
		
		union {
			struct {
				Vector4 plane_l;		// left clipping plane
				Vector4 plane_r;		// right clipping plane
				Vector4 plane_b;		// bottom clipping plane
				Vector4 plane_t;		// top clipping plane
				Vector4 plane_n;		// near clipping plane
				Vector4 plane_f;		// far clipping plane
			};
			Vector4 planes[6];
		};
		
		union {
			struct {
				uint8_t sign_l[4];		// left clipping plane sign
				uint8_t sign_r[4];		// right clipping plane sign
				uint8_t sign_b[4];		// bottom clipping plane sign
				uint8_t sign_t[4];		// top clipping plane sign
				uint8_t sign_n[4];		// near clipping plane sign
				uint8_t sign_f[4];		// far clipping plane sign
			};
			uint8_t signs[6][4];
		};
	};
	
	/// BoundFrustum types
	using BoundFrustumf = BoundFrustum<float32_t>;
	using BoundFrustumd = BoundFrustum<float64_t>;
}

#endif /* __TELLUSIM_GEOMETRY_BOUNDS_H__ */

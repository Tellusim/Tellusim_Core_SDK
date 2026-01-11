// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GEOMETRY_POLYGON_H__
#define __TELLUSIM_GEOMETRY_POLYGON_H__

#include <geometry/TellusimBasis.h>
#include <geometry/TellusimTriangle.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Polygon utils
	 */
	template <uint32_t Capacity = 256> struct Polygon final {
		
		/// 3D polygon normal
		template<class Type>
		static Vector3<Type> normal(const Vector3<Type> *vertices, uint32_t num_vertices) {
			
			TS_ASSERT(num_vertices >= 3 && "Polygon::normal(): invalid vertices");
			
			/// vertex bounds
			uint32_t min_index[3] = {};
			uint32_t max_index[3] = {};
			Vector3<Type> min_vertex = vertices[0];
			Vector3<Type> max_vertex = vertices[0];
			for(uint32_t i = 0; i < num_vertices; i++) {
				const Vector3<Type> &vertex = vertices[i];
				if(min_vertex.x > vertex.x) { min_vertex.x = vertex.x; min_index[0] = i; }
				if(min_vertex.y > vertex.y) { min_vertex.y = vertex.y; min_index[1] = i; }
				if(min_vertex.z > vertex.z) { min_vertex.z = vertex.z; min_index[2] = i; }
				if(max_vertex.x < vertex.x) { max_vertex.x = vertex.x; max_index[0] = i; }
				if(max_vertex.y < vertex.y) { max_vertex.y = vertex.y; max_index[1] = i; }
				if(max_vertex.z < vertex.z) { max_vertex.z = vertex.z; max_index[2] = i; }
			}
			
			/// maximum axis
			uint32_t axis = 0;
			Vector3<Type> size = max_vertex - min_vertex;
			if(size.y > size.x) {
				if(size.z > size.y) axis = 2;
				else axis = 1;
			} else {
				if(size.z > size.x) axis = 2;
				else axis = 0;
			}
			
			/// maximum area
			Type max_area = -Maxf32;
			Vector3<Type> max_normal;
			min_vertex = vertices[min_index[axis]];
			max_vertex = vertices[max_index[axis]] - min_vertex;
			for(uint32_t i = 0; i < num_vertices; i++) {
				Vector3<Type> normal = cross(vertices[i] - min_vertex, max_vertex);
				Type area = length2(normal);
				if(max_area < area) {
					max_normal = normal;
					max_area = area;
				}
			}
			
			return max_normal;
		}
		
		/// triangulate 3D polygon
		template <class Type, class Index>
		static uint32_t triangulate(const Vector3<Type> *vertices, uint32_t num_vertices, Index *indices) {
			
			TS_ASSERT(num_vertices >= 3 && "Polygon::triangulate(): invalid vertices");
			TS_ASSERT(num_vertices < Capacity && "Polygon::triangulate(): too many vertices");
			
			/// polygon normal
			Vector3<Type> normal = Polygon::normal(vertices, num_vertices);
			
			/// triangulate polygon
			return triangulate(vertices, num_vertices, normal, indices);
		}
		
		/// triangulate 3D polygon with specified normal
		template <class Type, class Index>
		static uint32_t triangulate(const Vector3<Type> *vertices, uint32_t num_vertices, const Vector3<Type> &normal, Index *indices) {
			
			TS_ASSERT(num_vertices >= 3 && "Polygon::triangulate(): invalid vertices");
			TS_ASSERT(num_vertices < Capacity && "Polygon::triangulate(): too many vertices");
			
			/// polygon normal basis
			Vector3<Type> tangent, binormal;
			Basis::ortho(normal, tangent, binormal);
			
			/// project polygon vertices
			Vector2<Type> buffer[Capacity];
			for(uint32_t i = 0; i < num_vertices; i++) {
				Vector3<Type> vertex = vertices[i] - vertices[0];
				buffer[i].x = dot(vertex, tangent);
				buffer[i].y = dot(vertex, binormal);
			}
			
			/// triangulate polygon
			return triangulate(buffer, num_vertices, indices);
		}
		
		/// triangulate 2D polygon
		template <class Type, class Index>
		static uint32_t triangulate(const Vector2<Type> *vertices, uint32_t num_vertices, Index *indices) {
			
			TS_ASSERT(num_vertices >= 3 && "Polygon::triangulate(): invalid vertices");
			TS_ASSERT(num_vertices < Capacity && "Polygon::triangulate(): too many vertices");
			
			/// triangle polygon
			if(num_vertices == 3) {
				indices[0] = 0;
				indices[1] = 1;
				indices[2] = 2;
				return 3;
			}
			
			/// signed polygon area
			Type area = cross(vertices[0], vertices[num_vertices - 1]);
			for(uint32_t i = 1; i < num_vertices; i++) {
				area += cross(vertices[i], vertices[i - 1]);
			}
			
			/// polygon winding
			uint32_t next[Capacity];
			uint32_t prev[Capacity];
			if(area < 0.0f) {
				prev[num_vertices - 1] = 0;
				next[0] = num_vertices - 1;
				for(uint32_t i = 1; i < num_vertices; i++) {
					prev[i - 1] = i;
					next[i] = i - 1;
				}
			} else {
				prev[0] = num_vertices - 1;
				next[num_vertices - 1] = 0;
				for(uint32_t i = 1; i < num_vertices; i++) {
					prev[i] = i - 1;
					next[i - 1] = i;
				}
			}
			
			/// vertex angles
			Type angles[Capacity];
			for(uint32_t i = 0; i < num_vertices; i++) {
				if(vertices[prev[i]] != vertices[i] && vertices[next[i]] != vertices[i]) {
					angles[i] = Triangle::angle(vertices[prev[i]], vertices[i], vertices[next[i]]);
				} else {
					next[prev[i]] = next[i];
					prev[next[i]] = prev[i];
					angles[i] = Maxf32;
				}
			}
			
			/// triangulate polygon
			uint32_t num_indices = 0;
			for(uint32_t i = 0; num_vertices >= 3; i = prev[i], num_vertices--) {
				
				/// find next vertex
				Type min_angle = Maxf32;
				Type max_angle = -Maxf32;
				uint32_t min_index = Maxu32;
				uint32_t max_index = Maxu32;
				for(uint32_t j = 0; j < num_vertices; j++) {
					if((angles[i] >= 0.0f && min_angle > angles[i]) || (angles[i] <= 0.0f && max_angle < angles[i])) {
						bool is_ear = true;
						const Vector2<Type> &v0 = vertices[prev[i]];
						const Vector2<Type> &v1 = vertices[i];
						const Vector2<Type> &v2 = vertices[next[i]];
						Vector2<Type> min_vertex = min(v0, min(v1, v2));
						Vector2<Type> max_vertex = max(v0, max(v1, v2));
						for(uint32_t k = next[next[i]]; k != prev[i]; k = next[k]) {
							const Vector2<Type> &vertex = vertices[k];
							if(min_vertex.x > vertex.x || min_vertex.y > vertex.y) continue;
							if(max_vertex.x < vertex.x || max_vertex.y < vertex.y) continue;
							if(vertex == v0 || vertex == v1 || vertex == v2) continue;
							if(!Triangle::inside(v0, v1, v2, vertex)) continue;
							is_ear = false;
							break;
						}
						if(is_ear && angles[i] >= 0.0f && min_angle > angles[i]) {
							min_angle = angles[i];
							min_index = i;
						}
						if(is_ear && angles[i] <= 0.0f && max_angle < angles[i]) {
							max_angle = angles[i];
							max_index = i;
						}
					}
					i = next[i];
				}
				
				/// next vertex
				i = min_index;
				if(i == Maxu32) i = max_index;
				if(i == Maxu32) break;
				
				/// update angles
				const Vector2<Type> &v0 = vertices[prev[i]];
				const Vector2<Type> &v2 = vertices[next[i]];
				angles[prev[i]] = Triangle::angle(vertices[prev[prev[i]]], v0, v2);
				angles[next[i]] = Triangle::angle(v0, v2, vertices[next[next[i]]]);
				
				/// next triangle
				if(area < 0.0f) {
					indices[0] = (Index)next[i];
					indices[1] = (Index)i;
					indices[2] = (Index)prev[i];
				} else {
					indices[0] = (Index)prev[i];
					indices[1] = (Index)i;
					indices[2] = (Index)next[i];
				}
				next[prev[i]] = next[i];
				prev[next[i]] = prev[i];
				num_indices += 3;
				indices += 3;
			}
			
			return num_indices;
		}
	};
}

#endif /* __TELLUSIM_GEOMETRY_POLYGON_H__ */

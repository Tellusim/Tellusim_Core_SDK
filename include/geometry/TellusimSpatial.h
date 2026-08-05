// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GEOMETRY_SPATIAL_H__
#define __TELLUSIM_GEOMETRY_SPATIAL_H__

#include <core/TellusimArray.h>
#include <geometry/TellusimBounds.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Spatial utils
	 */
	namespace Spatial {
		
		/// number of iterations
		enum {
			MinIterations = 1,
			MaxIterations = 8,
			DefaultIterations = 4,
		};
		
		/// Spatial Node
		template <class Type, uint32_t Size> struct Node {
			
			using Bound = Type;		// bound type
			enum { Axes = Size };	// bound axes
			
			Bound bound;			// node bound
			uint32_t left;			// left child index bigger than the spatial node index in the case of leaf node
			uint32_t right;			// right child index bigger than the spatial node index in the case of leaf node
			uint32_t parent;		// parent node index or next node visiting index for optimized tree
			uint32_t spatial;		// spatial node index for leaf node or number of tree nodes for non-leaf nodes
		};
		
		/// Node types
		using Node2f = Node<BoundRect<float32_t, Vector2<float32_t>>, 2>;
		using Node2d = Node<BoundRect<float64_t, Vector2<float64_t>>, 2>;
		using Node3f = Node<BoundBox<float32_t, Vector3<float32_t>>, 3>;
		using Node3d = Node<BoundBox<float64_t, Vector3<float64_t>>, 3>;
		using Node4f = Node<BoundBox<float32_t, Vector4<float32_t>>, 3>;
		using Node4d = Node<BoundBox<float64_t, Vector4<float64_t>>, 3>;
		
		/// Create spatial tree
		template <class Type, class Vector> Type get_weight(const BoundRect<Type, Vector> &bound) {
			return bound.getArea();
		}
		template <class Type, class Vector> Type get_weight(const BoundBox<Type, Vector> &bound) {
			return bound.getVolume();
		}
		template <class Bound> typename Bound::Type get_weight(const Bound &bound) {
			typename Bound::Vector size = bound.max - bound.min;
			typename Bound::Type weight = size.v[0] * size.v[1];
			if(Bound::Vector::Size == 3) weight *= size.v[2];
			return weight;
		}
		template <class Type, class Node>
		static uint32_t create_nodes(Node *nodes, uint32_t num_nodes, uint32_t *indices, uint32_t &counter, uint32_t index, uint32_t left, uint32_t right, uint32_t iterations) {
			
			TS_STATIC_ASSERT((uint32_t)Node::Axes <= Node::Bound::Vector::Size);
			TS_STATIC_ASSERT(Node::Axes >= 2 && Node::Axes <= 3);
			
			using Bound = typename Node::Bound;
			using Vector = typename Bound::Vector;
			
			/// leaf node
			if(left == right) {
				uint32_t index = indices[left];
				nodes[index].spatial = index - num_nodes;
				return index;
			}
			
			/// node bounds
			Bound node_bound;
			Vector node_min = Vector(0.0f);
			Vector node_max = Vector(0.0f);
			Vector distances[MaxIterations];
			for(uint32_t i = left; i <= right; i++) {
				const Bound &bound = nodes[indices[i]].bound;
				node_bound.expand(bound);
				node_min += bound.min;
				node_max += bound.max;
			}
			nodes[index].bound = node_bound;
			distances[0] = (node_bound.min + node_bound.max);
			if(iterations > 0) {
				distances[1] = (node_min + node_max) / Type(right - left + 1);
				distances[2] = (node_bound.min * (Type)2.0f + node_bound.max) * (Type)(2.0f / 3.0f);
				distances[3] = (node_bound.min + node_bound.max * (Type)2.0f) * (Type)(2.0f / 3.0f);
				if(iterations > 3) {
					distances[4] = (node_bound.min * (Type)3.0f + node_bound.max) * (Type)(2.0f / 4.0f);
					distances[5] = (node_bound.min + node_bound.max * (Type)3.0f) * (Type)(2.0f / 4.0f);
					distances[6] = (node_bound.min * (Type)4.0f + node_bound.max) * (Type)(2.0f / 5.0f);
					distances[7] = (node_bound.min + node_bound.max * (Type)4.0f) * (Type)(2.0f / 5.0f);
				}
			}
			
			/// two children nodes
			if(right - left == 1) {
				uint32_t left_index = indices[left];
				uint32_t right_index = indices[right];
				nodes[index].left = left_index;
				nodes[index].right = right_index;
				nodes[index].spatial = num_nodes;
				nodes[left_index].parent = index;
				nodes[right_index].parent = index;
				nodes[left_index].spatial = left_index - num_nodes;
				nodes[right_index].spatial = right_index - num_nodes;
				return index;
			}
			
			/// best split axis
			Type split_weight = Maxf32;
			Type split_distance = 0.0f;
			uint32_t split_axis = Maxu32;
			uint32_t split_counter[(uint32_t)MaxIterations * Node::Axes] = {};
			Bound left_bounds[(uint32_t)MaxIterations * Node::Axes];
			Bound right_bounds[(uint32_t)MaxIterations * Node::Axes];
			for(uint32_t i = left; i <= right; i++) {
				const Bound &bound = nodes[indices[i]].bound;
				Vector center = bound.min + bound.max;
				#define TS_DECLARE_COMPARE(CONDITION, INDEX) { \
					if(CONDITION) { left_bounds[INDEX].expand(bound); } \
					else { right_bounds[INDEX].expand(bound); split_counter[INDEX]++; } \
				}
				for(uint32_t j = 0, k = 0; j < iterations; j++) {
					const Vector &distance = distances[j];
					for(uint32_t l = 0; l < Node::Axes; l++, k++) {
						TS_DECLARE_COMPARE(center.v[l] > distance.v[l], k)
					}
				}
				#undef TS_DECLARE_COMPARE
			}
			for(uint32_t i = 0; i < Node::Axes; i++) {
				for(uint32_t j = 0, k = 0; j < iterations; j++, k += Node::Axes) {
					Type weight = get_weight(left_bounds[i + k]) + get_weight(right_bounds[i + k]);
					if(split_counter[i + k] != 0 && split_counter[i + k] != right - left + 1 && split_weight > weight) {
						split_distance = distances[j].v[i];
						split_weight = weight;
						split_axis = i;
					}
				}
			}
			
			/// can't find split plane
			if(split_axis == Maxu32) {
				
				/// node with maximum weight
				Type max_weight = -Maxf32;
				uint32_t max_index = left;
				for(uint32_t i = left; i <= right; i++) {
					const Node &node = nodes[indices[i]];
					Type weight = get_weight(node.bound);
					if(max_weight < weight) {
						max_weight = weight;
						max_index = i;
					}
				}
				swap(indices[max_index], indices[right]);
				
				/// create unbalanced tree
				uint32_t left_index = ++counter;
				uint32_t right_index = indices[right];
				create_nodes<Type>(nodes, num_nodes, indices, counter, left_index, left, right - 1, iterations);
				nodes[index].left = left_index;
				nodes[index].right = right_index;
				nodes[index].spatial = num_nodes;
				nodes[left_index].parent = index;
				nodes[right_index].parent = index;
				nodes[right_index].spatial = right_index - num_nodes;
				return index;
			}
			
			/// split nodes
			uint32_t left_nodes = 0;
			uint32_t right_nodes = 0;
			for(uint32_t i = left; i <= right; i++) {
				const Bound &bound = nodes[indices[i]].bound;
				Type center = bound.min.v[split_axis] + bound.max.v[split_axis];
				if(center > split_distance) indices[left + left_nodes++] = indices[i];
				else indices[num_nodes + right_nodes++] = indices[i];
			}
			for(uint32_t i = 0; i < right_nodes; i++) {
				indices[left + left_nodes + i] = indices[num_nodes + i];
			}
			
			/// create balanced tree
			uint32_t left_index = (left_nodes > 1) ? ++counter : 0;
			uint32_t right_index = (right_nodes > 1) ? ++counter : 0;
			left_index = create_nodes<Type>(nodes, num_nodes, indices, counter, left_index, left, left + left_nodes - 1, iterations);
			right_index = create_nodes<Type>(nodes, num_nodes, indices, counter, right_index, left + left_nodes, right, iterations);
			nodes[index].left = left_index;
			nodes[index].right = right_index;
			nodes[index].spatial = num_nodes;
			nodes[left_index].parent = index;
			nodes[right_index].parent = index;
			return index;
		}
		
		/// Create spatial tree
		/// Root node will be the first element of nodes array.
		/// Leaf nodes is the second half of input nodes array.
		/// The size of nodes and indices arrays must be 2x of nodes number.
		/// The second half of nodes and indices (optional) arrays must be initialized.
		/// \param nodes Input array of nodes (must contain 4 elements).
		/// \param indices Temporary array of indices.
		/// \param num_nodes Number of nodes.
		/// \param iterations Number of iterations.
		template <class Type, class Node>
		static void create(Node *nodes, uint32_t *indices, uint32_t num_nodes, uint32_t iterations = DefaultIterations) {
			
			TS_ASSERT(iterations >= MinIterations && iterations <= MaxIterations && "Spatial::create(): invalid number of iterations");
			
			/// simple tree
			if(num_nodes == 0) {
				for(uint32_t i = 0; i < 4; i++) {
					nodes[i].left = 0;
					nodes[i].right = 0;
					nodes[i].parent = Maxu32;
					nodes[i].spatial = Maxu32;
				}
				return;
			}
			else if(num_nodes == 1) {
				nodes[0].left = 1;
				nodes[0].right = 2;
				nodes[0].parent = Maxu32;
				nodes[0].spatial = 1;
				nodes[0].bound = nodes[1].bound;
				nodes[1].parent = 0;
				nodes[1].spatial = 1;
				for(uint32_t i = 2; i < 4; i++) {
					nodes[i].left = 0;
					nodes[i].right = 0;
					nodes[i].parent = Maxu32;
					nodes[i].spatial = Maxu32;
				}
				return;
			}
			else if(num_nodes == 2) {
				nodes[0].left = 2;
				nodes[0].right = 3;
				nodes[0].parent = Maxu32;
				nodes[0].spatial = 2;
				nodes[0].bound.min = min(nodes[2].bound.min, nodes[3].bound.min);
				nodes[0].bound.max = max(nodes[2].bound.max, nodes[3].bound.max);
				nodes[1].left = 0;
				nodes[1].right = 0;
				nodes[1].parent = Maxu32;
				nodes[1].spatial = Maxu32;
				nodes[2].parent = 0;
				nodes[2].spatial = 2;
				nodes[3].parent = 0;
				nodes[3].spatial = 3;
				return;
			}
			
			/// create indices
			for(uint32_t i = 0; i < num_nodes; i++) {
				indices[i] = num_nodes + i;
			}
			
			/// create nodes
			uint32_t index = 0;
			uint32_t counter = 0;
			nodes[0].parent = Maxu32;
			nodes[num_nodes - 1].left = 0;
			nodes[num_nodes - 1].right = 0;
			nodes[num_nodes - 1].parent = Maxu32;
			nodes[num_nodes - 1].spatial = Maxu32;
			create_nodes<Type>(nodes, num_nodes, indices, counter, index, 0, num_nodes - 1, iterations);
		}
		template <class Type, class Node>
		static void create(Node *nodes, uint32_t num_nodes, uint32_t iterations = DefaultIterations) {
			Array<uint32_t> indices(num_nodes * 2);
			create<Type>(nodes, indices.get(), num_nodes, iterations);
		}
		
		/// Optimize spatial tree for stack-less traversal
		/// Node parent becomes the next visiting node index
		/// \param nodes Spatial tree root.
		/// \param buffer Temporary array of nodes.
		/// \param indices Temporary array of indices.
		/// \param num_nodes Number of nodes in the spatial tree.
		template <class Type, class Node, uint32_t Depth = 1024>
		static void optimize(Node *nodes, Node *buffer, uint32_t *indices, uint32_t num_nodes) {
			for(uint32_t i = 0; i < num_nodes; i++) {
				buffer[i] = nodes[i];
				indices[i] = Maxu32;
			}
			num_nodes = 0;
			uint32_t depth = 0;
			uint32_t index = 0;
			uint32_t stack[Depth];
			while(true) {
				indices[index] = num_nodes;
				Node &node = nodes[num_nodes++];
				node = buffer[index];
				node.parent = Maxu32;
				if(node.left < node.spatial) {
					if(depth) node.parent = stack[depth - 1];
					if(node.right < node.spatial) {
						TS_ASSERT(depth < Depth && "Spatial::optimize(): stack overflow");
						stack[depth++] = node.right;
					}
					index = node.left;
					continue;
				}
				if(node.right < node.spatial) {
					if(depth) node.parent = stack[depth - 1];
					index = node.right;
					continue;
				}
				if(depth == 0) break;
				node.parent = stack[--depth];
				index = node.parent;
			}
			for(uint32_t i = 0; i < num_nodes; i++) {
				Node &node = nodes[i];
				if(node.left < num_nodes) node.left = indices[node.left];
				if(node.right < num_nodes) node.right = indices[node.right];
				if(node.parent < num_nodes) node.parent = indices[node.parent];
				if(node.left < num_nodes && node.right >= num_nodes) swap(node.left, node.right);
			}
		}
		template <class Type, class Node, uint32_t Depth = 1024>
		static void optimize(Node *nodes, uint32_t num_nodes) {
			Array<Node> buffer(num_nodes);
			Array<uint32_t> indices(num_nodes);
			optimize<Type, Node, Depth>(nodes, buffer.get(), indices.get(), num_nodes);
		}
		
		/// Spatial tree intersection
		/// The size of indices array must be bigger than the number of nodes
		/// \param nodes Spatial tree root.
		/// \param indices Output spatial node indices.
		/// \param num_indices Number of output indices.
		/// \returns Number of spatial nodes.
		template <class Bound, class Node, uint32_t Depth = 1024>
		static uint32_t intersection(const Bound &bound, const Node *nodes, uint32_t *indices, uint32_t num_indices) {
			uint32_t ret = 0;
			uint32_t index = 0;
			uint32_t depth = 0;
			uint32_t stack[Depth];
			while(true) {
				const Node &node = nodes[index];
				const Node &left_node = nodes[node.left];
				const Node &right_node = nodes[node.right];
				bool left = (left_node.parent != Maxu32 && bound.inside(left_node.bound));
				bool right = (right_node.parent != Maxu32 && bound.inside(right_node.bound));
				if(left && node.left >= node.spatial) {
					TS_ASSERT(ret < num_indices && "Spatial::intersection(): indices overflow");
					indices[ret++] = node.left - node.spatial;
					left = false;
				}
				if(right && node.right >= node.spatial) {
					TS_ASSERT(ret < num_indices && "Spatial::intersection(): indices overflow");
					indices[ret++] = node.right - node.spatial;
					right = false;
				}
				if(left) {
					if(right) {
						TS_ASSERT(depth < Depth && "Spatial::intersection(): stack overflow");
						stack[depth++] = node.right;
					}
					index = node.left;
					continue;
				}
				if(right) {
					index = node.right;
					continue;
				}
				if(depth == 0) break;
				index = stack[--depth];
			}
			return ret;
		}
		template <class Bound, class Node, uint32_t Depth = 1024>
		static uint32_t intersection(const Bound &bound, const Node *nodes, Array<uint32_t> &indices) {
			indices.clear();
			uint32_t index = 0;
			uint32_t depth = 0;
			uint32_t stack[Depth];
			while(true) {
				const Node &node = nodes[index];
				const Node &left_node = nodes[node.left];
				const Node &right_node = nodes[node.right];
				bool left = (left_node.parent != Maxu32 && bound.inside(left_node.bound));
				bool right = (right_node.parent != Maxu32 && bound.inside(right_node.bound));
				if(left && node.left >= node.spatial) {
					indices.append(node.left - node.spatial);
					left = false;
				}
				if(right && node.right >= node.spatial) {
					indices.append(node.right - node.spatial);
					right = false;
				}
				if(left) {
					if(right) {
						TS_ASSERT(depth < Depth && "Spatial::intersection(): stack overflow");
						stack[depth++] = node.right;
					}
					index = node.left;
					continue;
				}
				if(right) {
					index = node.right;
					continue;
				}
				if(depth == 0) break;
				index = stack[--depth];
			}
			return indices.size();
		}
		
		/// Inside spatial tree intersection
		/// The size of indices array must be bigger than the number of nodes
		/// \param nodes Spatial tree root.
		/// \param indices Output spatial node indices.
		/// \param num_indices Number of output indices.
		/// \returns Number of spatial nodes.
		template <class Vector, class Node, uint32_t Depth = 1024>
		static uint32_t insideIntersection(const Vector &point, const Node *nodes, uint32_t *indices, uint32_t num_indices) {
			uint32_t ret = 0;
			uint32_t index = 0;
			uint32_t depth = 0;
			uint32_t stack[Depth];
			while(true) {
				const Node &node = nodes[index];
				const Node &left_node = nodes[node.left];
				const Node &right_node = nodes[node.right];
				bool left = (left_node.parent != Maxu32 && left_node.bound.inside(point));
				bool right = (right_node.parent != Maxu32 && right_node.bound.inside(point));
				if(left && node.left >= node.spatial) {
					TS_ASSERT(ret < num_indices && "Spatial::intersection(): indices overflow");
					indices[ret++] = node.left - node.spatial;
					left = false;
				}
				if(right && node.right >= node.spatial) {
					TS_ASSERT(ret < num_indices && "Spatial::intersection(): indices overflow");
					indices[ret++] = node.right - node.spatial;
					right = false;
				}
				if(left) {
					if(right) {
						TS_ASSERT(depth < Depth && "Spatial::intersection(): stack overflow");
						stack[depth++] = node.right;
					}
					index = node.left;
					continue;
				}
				if(right) {
					index = node.right;
					continue;
				}
				if(depth == 0) break;
				index = stack[--depth];
			}
			return ret;
		}
		template <class Vector, class Node, uint32_t Depth = 1024>
		static uint32_t insideIntersection(const Vector &point, const Node *nodes, Array<uint32_t> &indices) {
			indices.clear();
			uint32_t index = 0;
			uint32_t depth = 0;
			uint32_t stack[Depth];
			while(true) {
				const Node &node = nodes[index];
				const Node &left_node = nodes[node.left];
				const Node &right_node = nodes[node.right];
				bool left = (left_node.parent != Maxu32 && left_node.bound.inside(point));
				bool right = (right_node.parent != Maxu32 && right_node.bound.inside(point));
				if(left && node.left >= node.spatial) {
					indices.append(node.left - node.spatial);
					left = false;
				}
				if(right && node.right >= node.spatial) {
					indices.append(node.right - node.spatial);
					right = false;
				}
				if(left) {
					if(right) {
						TS_ASSERT(depth < Depth && "Spatial::intersection(): stack overflow");
						stack[depth++] = node.right;
					}
					index = node.left;
					continue;
				}
				if(right) {
					index = node.right;
					continue;
				}
				if(depth == 0) break;
				index = stack[--depth];
			}
			return indices.size();
		}
		
		/// Closest spatial tree intersection
		/// \param nodes Spatial tree root.
		/// \returns Closest node index.
		template <class Type, class Vector, class Node, uint32_t Depth = 1024>
		static uint32_t closestIntersection(const Vector &point, const Node *nodes) {
			uint32_t ret = Maxu32;
			uint32_t index = 0;
			uint32_t depth = 0;
			uint32_t stack[Depth];
			Type distance = Maxf32;
			while(true) {
				const Node &node = nodes[index];
				const Node &left_node = nodes[node.left];
				const Node &right_node = nodes[node.right];
				Type left_distance = left_node.bound.distance(point);
				Type right_distance = right_node.bound.distance(point);
				bool left = (left_node.parent != Maxu32 && left_distance < distance);
				bool right = (right_node.parent != Maxu32 && right_distance < distance);
				if(left && node.left >= node.spatial) {
					if(distance > left_distance) {
						ret = node.left - node.spatial;
						distance = left_distance;
					}
					left = false;
				}
				if(right && node.right >= node.spatial) {
					if(distance > right_distance) {
						ret = node.right - node.spatial;
						distance = right_distance;
					}
					right = false;
				}
				if(left && right) {
					TS_ASSERT(depth < Depth && "Spatial::closestIntersection(): stack overflow");
					if(left_distance < right_distance) {
						stack[depth++] = node.right;
						index = node.left;
						continue;
					} else {
						stack[depth++] = node.left;
						index = node.right;
						continue;
					}
				} else if(left) {
					index = node.left;
					continue;
				} else if(right) {
					index = node.right;
					continue;
				}
				if(depth == 0) break;
				index = stack[--depth];
			}
			return ret;
		}
	}
}

#endif /* __TELLUSIM_GEOMETRY_SPATIAL_H__ */

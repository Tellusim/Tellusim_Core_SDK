// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_GEOMETRY_ATLAS_H__
#define __TELLUSIM_GEOMETRY_ATLAS_H__

#include <geometry/TellusimBounds.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Atlas utils
	 */
	template <class Type> class Atlas {
			
		public:
			
			using Bound = Type;						// bound type
			using Vector = typename Type::Vector;	// Vector type
			enum { Axes = Vector::Size };			// vector axes
			
			/// Atlas Node
			struct Node {
				Bound bound;						// node bound
				Node *left = nullptr;				// left child
				Node *right = nullptr;				// right child
				Node *parent = nullptr;				// parent node
				uint32_t axis = Maxu32;				// split axis
			};
			
			/// constructors
			Atlas() : root(new Node()) { }
			Atlas(const Atlas &atlas) { root = clone(nullptr, atlas.root); }
			Atlas(Atlas &&atlas) { root = atlas.root; atlas.root = nullptr; }
			explicit Atlas(const Vector &size) : Atlas() { set(size); }
			explicit Atlas(const Bound &bound) : Atlas() { set(bound); }
			~Atlas() { release(root); }
			
			/// clear atlas
			void clear() {
				release(root->left);
				release(root->right);
				root->left = nullptr;
				root->right = nullptr;
				root->axis = Maxu32;
			}
			
			/// set atlas size
			void set(const Vector &size) {
				clear();
				root->bound.set(Vector::zero, size);
			}
			void set(const Bound &bound) {
				clear();
				root->bound = bound;
			}
			
			/// assignment operators
			Atlas &operator=(const Atlas &atlas) {
				if(&atlas != this) {
					release(root);
					root = clone(nullptr, atlas.root);
				}
				return *this;
			}
			Atlas &operator=(Atlas &&atlas) {
				release(root);
				root = atlas.root;
				atlas.root = nullptr;
				return *this;
			}
			
			/// atlas root
			TS_INLINE const Node *getRoot() const {
				return root;
			}
			
			/// insert node into the atlas
			Node *insert(const Vector &size) {
				return insert(root, size);
			}
			
			/// remove node from the atlas
			bool remove(Node *node) {
				if(is_leaf(node)) {
					node->axis = Maxu32;
					Node *parent = node->parent;
					while(parent && ((parent->left == node && is_free(parent->right)) || (parent->right == node && is_free(parent->left)))) {
						node = parent;
						release(node->left);
						release(node->right);
						node->left = nullptr;
						node->right = nullptr;
						node->axis = Maxu32;
						parent = node->parent;
					}
					return true;
				}
				return false;
			}
			
		private:
			
			/// weight parameter
			template <class T> static T get_weight(const Vector2<T> &size) {
				return size.x * size.y;
			}
			template <class T> static T get_weight(const Vector3<T> &size) {
				return size.x * size.y * size.z;
			}
			template <class T, class V> static T get_weight(const BoundRect<T, V> &bound) {
				return bound.getArea();
			}
			template <class T, class V> static T get_weight(const BoundBox<T, V> &bound) {
				return bound.getVolume();
			}
			
			/// best split axis
			template <class T, class V> static uint32_t get_axis(const BoundRect<T, V> &bound, const Vector &size) {
				Vector difference = bound.getSize() - size;
				if(difference.x >= 0.0f && difference.y >= 0.0f) {
					if(difference.x > difference.y) return 0;
					return 1;
				}
				return Axes;
			}
			template <class T, class V> static uint32_t get_axis(const BoundBox<T, V> &bound, const Vector &size) {
				Vector difference = bound.getSize() - size;
				if(difference.x >= 0.0f && difference.y >= 0.0f && difference.z >= 0.0) {
					if(difference.y > difference.z) {
						if(difference.x > difference.y) return 0;
						return 1;
					} else {
						if(difference.x > difference.z) return 0;
						return 2;
					}
				}
				return Axes;
			}
			
			/// node type
			TS_INLINE static bool is_free(const Node *node) {
				return (node && !node->left && !node->right && node->axis == Maxu32);
			}
			TS_INLINE static bool is_leaf(const Node *node) {
				return (node && !node->left && !node->right && node->axis == Axes);
			}
			
			/// release atlas
			static void release(Node *node) {
				if(node != nullptr) {
					if(node->left) release(node->left);
					if(node->right) release(node->right);
					delete node;
				}
			}
			
			/// clone atlas
			static Node *clone(Node *parent, const Node *src) {
				if(src != nullptr) {
					Node *node = new Node();
					node->parent = parent;
					node->left = clone(node, src->left);
					node->right = clone(node, src->right);
					return node;
				}
				return nullptr;
			}
			
			/// split node and return left
			static Node *split(Node *node, const Vector &size, uint32_t axis) {
				Node *left = new Node();
				Node *right = new Node();
				left->bound = node->bound;
				right->bound = node->bound;
				left->bound.max[axis] = left->bound.min[axis] + size[axis];
				right->bound.min[axis] = left->bound.max[axis];
				left->parent = node;
				right->parent = node;
				node->left = left;
				node->right = right;
				node->axis = axis;
				left->axis = Axes;
				return left;
			}
			
			/// insert node into the atlas
			static Node *insert(Node *node, const Vector &size, float32_t threshold = 1.1f) {
				uint32_t axis = get_axis(node->bound, size);
				if(axis < Axes) {
					if(is_free(node)) {
						float32_t weight = get_weight(size) * threshold;
						if(get_weight(node->bound) > weight) {
							Node *ret = split(node, size, axis);
							if(get_weight(ret->bound) > weight) {
								axis = (axis + 1) % Axes;
								ret = split(ret, size, axis);
								if(Axes > 2 && get_weight(ret->bound) > weight) {
									axis = (axis + 1) % Axes;
									return split(ret, size, axis);
								}
								return ret;
							}
							return ret;
						}
						node->axis = Axes;
						return node;
					}
					if(node->left && node->right) {
						if(get_weight(node->left->bound) < get_weight(node->right->bound)) {
							Node *ret = insert(node->left, size, threshold);
							if(!ret) ret = insert(node->right, size, threshold);
							if(ret) return ret;
						} else {
							Node *ret = insert(node->right, size, threshold);
							if(!ret) ret = insert(node->left, size, threshold);
							if(ret) return ret;
						}
					}
				}
				return nullptr;
			}
			
			Node *root = nullptr;		// root of the atlas
	};
	
	/// Atlas types
	using Atlas2f = Atlas<BoundRect<float32_t>>;
	using Atlas3f = Atlas<BoundBox<float32_t>>;
}

#endif /* __TELLUSIM_GEOMETRY_ATLAS_H__ */

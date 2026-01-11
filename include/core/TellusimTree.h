// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_TREE_H__
#define __TELLUSIM_CORE_TREE_H__

#include <TellusimBase.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Tree container
	 */
	template <class Type, class Compare> class Tree {
			
		private:
			
			/// tree node
			struct TreeNode {
				
				TreeNode() : left(nullptr), right(nullptr), parent(nullptr), height(0) { }
				TreeNode(TreeNode *parent, const Type &data) : left(nullptr), right(nullptr), parent(parent), height(0), data(data) { }
				~TreeNode() { }
				
				/// minimum node
				TreeNode *min() {
					TreeNode *node = this;
					while(node->left) node = node->left;
					return node;
				}
				const TreeNode *min() const {
					const TreeNode *node = this;
					while(node->left) node = node->left;
					return node;
				}
				
				/// maximum node
				TreeNode *max() {
					TreeNode *node = this;
					while(node->right) node = node->right;
					return node;
				}
				const TreeNode *max() const {
					const TreeNode *node = this;
					while(node->right) node = node->right;
					return node;
				}
				
				/// previous node
				TreeNode *prev() {
					if(left) return left->max();
					TreeNode *node = this;
					TreeNode *prev = parent;
					while(prev && node == prev->left) {
						node = prev;
						prev = prev->parent;
					}
					return prev;
				}
				const TreeNode *prev() const {
					if(left) return left->max();
					const TreeNode *node = this;
					const TreeNode *prev = parent;
					while(prev && node == prev->left) {
						node = prev;
						prev = prev->parent;
					}
					return prev;
				}
				
				/// next node
				TreeNode *next() {
					if(right) return right->min();
					TreeNode *node = this;
					TreeNode *next = parent;
					while(next && node == next->right) {
						node = next;
						next = next->parent;
					}
					return next;
				}
				const TreeNode *next() const {
					if(right) return right->min();
					const TreeNode *node = this;
					const TreeNode *next = parent;
					while(next && node == next->right) {
						node = next;
						next = next->parent;
					}
					return next;
				}
				
				TreeNode *left;		// left child
				TreeNode *right;	// right child
				TreeNode *parent;	// parent node
				
				int32_t height;		// node height
				
				Type data;			// node data
			};
			
			/// tree implementation
			struct TreeImpl {
				
				TreeImpl() : root(nullptr), length(0) { }
				~TreeImpl() { release(root); }
				
				/// clear tree
				void clear() {
					release(root);
					root = nullptr;
					length = 0;
				}
				
				void release(TreeNode *node) {
					if(node != nullptr) {
						if(node->left) release(node->left);
						if(node->right) release(node->right);
						delete node;
					}
				}
				
				/// swap trees
				void swap(TreeImpl &impl) {
					Tellusim::swap(root, impl.root);
					Tellusim::swap(length, impl.length);
				}
				
				/// copy tree
				void copy(const TreeImpl &impl) {
					release(root);
					root = clone(nullptr, impl.root);
					length = impl.length;
				}
				void move(TreeImpl &impl) {
					release(root);
					root = impl.root;
					length = impl.length;
					impl.root = nullptr;
					impl.length = 0;
				}
				
				TreeNode *clone(TreeNode *parent, const TreeNode *src) {
					if(src != nullptr) {
						TreeNode *node = new TreeNode(parent, src->data);
						node->left = clone(node, src->left);
						node->right = clone(node, src->right);
						node->height = src->height;
						return node;
					}
					return nullptr;
				}
				
				/// find value
				template <class T> TreeNode *find(const T &value) const {
					
					if(root == nullptr) return nullptr;
					
					Compare compare;
					TreeNode *node = root;
					while(true) {
						int32_t ret = compare(node->data, value);
						if(ret > 0) {
							if(!node->left) break;
							node = node->left;
						} else if(ret < 0) {
							if(!node->right) break;
							node = node->right;
						} else {
							return node;
						}
					}
					
					return nullptr;
				}
				
				/// find range
				template <class T> TreeNode *prev(const T &value) const {
					
					if(root == nullptr) return nullptr;
					
					Compare compare;
					TreeNode *node = root;
					while(true) {
						int32_t ret = compare(node->data, value);
						if(ret > 0) {
							if(node->left == nullptr) return node->prev();
							node = node->left;
						} else if(ret < 0) {
							if(node->right == nullptr) return node;
							node = node->right;
						} else {
							return node->prev();
						}
					}
					
					return nullptr;
				}
				
				template <class T> TreeNode *next(const T &value) const {
					
					if(root == nullptr) return nullptr;
					
					Compare compare;
					TreeNode *node = root;
					while(true) {
						int32_t ret = compare(node->data, value);
						if(ret > 0) {
							if(node->left == nullptr) return node;
							node = node->left;
						} else if(ret < 0) {
							if(node->right == nullptr) return node->next();
							node = node->right;
						} else {
							return node->next();
						}
					}
					
					return nullptr;
				}
				
				/// append the value
				TreeNode *append(const Type &value) {
					
					if(root == nullptr) {
						root = new TreeNode(nullptr, value);
						length++;
						return root;
					}
					
					Compare compare;
					TreeNode *node = root;
					while(true) {
						int32_t ret = compare(node->data, value);
						if(ret > 0) {
							if(node->left == nullptr) {
								TreeNode *left = new TreeNode(node, value);
								node->left = left;
								while(node) node = balance(node)->parent;
								length++;
								return left;
							}
							node = node->left;
						} else if(ret < 0) {
							if(node->right == nullptr) {
								TreeNode *right = new TreeNode(node, value);
								node->right = right;
								while(node) node = balance(node)->parent;
								length++;
								return right;
							}
							node = node->right;
						} else {
							node->data = value;
							return node;
						}
					}
					
					return nullptr;
				}
				
				/// remove the value
				template <class T> bool remove(const T &value) {
					
					TreeNode *node = find(value);
					if(node == nullptr) return false;
					
					return remove(node);
				}
				
				bool remove(TreeNode *node) {
					
					if(node == nullptr) return false;
					
					TreeNode *update = nullptr;
					TreeNode *parent = node->parent;
					if(node->left == nullptr) {
						if(node->right == nullptr) {
							if(parent == nullptr) root = nullptr;
							else if(parent->left == node) parent->left = nullptr;
							else parent->right = nullptr;
						} else {
							if(parent == nullptr) root = node->right;
							else if(parent->left == node) parent->left = node->right;
							else parent->right = node->right;
							node->right->parent = parent;
						}
						update = parent;
					} else if(node->right == nullptr) {
						if(parent == nullptr) root = node->left;
						else if(parent->left == node) parent->left = node->left;
						else parent->right = node->left;
						node->left->parent = parent;
						update = parent;
					} else {
						TreeNode *next = nullptr;
						if(get_balance(node) > 0) {
							if(node->left->right) {
								next = node->left->right;
								while(next->right) next = next->right;
								next->parent->right = next->left;
								if(next->left) next->left->parent = next->parent;
								next->left = node->left;
								next->right = node->right;
								node->left->parent = next;
								node->right->parent = next;
								update = next->parent;
							} else {
								next = node->left;
								next->right = node->right;
								node->right->parent = next;
								update = next;
							}
						} else {
							if(node->right->left) {
								next = node->right->left;
								while(next->left) next = next->left;
								next->parent->left = next->right;
								if(next->right) next->right->parent = next->parent;
								next->left = node->left;
								next->right = node->right;
								node->left->parent = next;
								node->right->parent = next;
								update = next->parent;
							} else {
								next = node->right;
								next->left = node->left;
								node->left->parent = next;
								update = next;
							}
						}
						if(parent == nullptr) root = next;
						else if(parent->left == node) parent->left = next;
						else parent->right = next;
						next->parent = parent;
					}
					if(update) balance(update);
					delete node;
					length--;
					
					return true;
				}
				
				/// balance tree
				TS_INLINE static int32_t get_balance(TreeNode *node) {
					if(node->left) {
						if(node->right) return node->left->height - node->right->height;
						return node->left->height + 1;
					} else if(node->right) {
						return -node->right->height - 1;
					}
					return 0;
				}
				
				TS_INLINE TreeNode *balance(TreeNode *node) {
					int32_t ret = 0;
					if(node->left) {
						int32_t left = node->left->height + 1;
						if(node->right) {
							int32_t right = node->right->height + 1;
							if(left > right) node->height = left;
							else node->height = right;
							ret = left - right;
						} else {
							node->height = left;
							ret = left;
						}
					} else if(node->right) {
						int32_t right = node->right->height + 1;
						node->height = right;
						ret = -right;
					} else {
						node->height = 0;
					}
					if(ret > 1) {
						if(get_balance(node->left) < 0) rotate_left(node->left);
						node = rotate_right(node);
					} else if(ret < -1) {
						if(get_balance(node->right) > 0) rotate_right(node->right);
						node = rotate_left(node);
					}
					return node;
				}
				
				/// rotate tree
				TreeNode *rotate_left(TreeNode *node) {
					TreeNode *right = node->right;
					node->right = right->left;
					if(right->left) right->left->parent = node;
					right->parent = node->parent;
					if(node->parent == nullptr) root = right;
					else if(node->parent->left == node) node->parent->left = right;
					else node->parent->right = right;
					right->left = node;
					node->parent = right;
					node->height--;
					return right;
				}
				
				TreeNode *rotate_right(TreeNode *node) {
					TreeNode *left = node->left;
					node->left = left->right;
					if(left->right) left->right->parent = node;
					left->parent = node->parent;
					if(node->parent == nullptr) root = left;
					else if(node->parent->left == node) node->parent->left = left;
					else node->parent->right = left;
					left->right = node;
					node->parent = left;
					node->height--;
					return left;
				}
				
				TreeNode *root;		// root of the tree
				uint32_t length;	// number of nodes
			};
			
		public:
			
			/// Iterator
			class Iterator {
					
				private:
					
					friend class Tree;
					
					Iterator(TreeNode *root, TreeNode *node) : root(root), node(node) { }
					
				public:
					
					Iterator() : root(nullptr), node(nullptr) { }
					Iterator(const Iterator &it) : root(it.root), node(it.node) { }
					
					void clear() { root = nullptr; node = nullptr; }
					
					Iterator &operator=(const Iterator &it) { root = it.root; node = it.node; return *this; }
					
					explicit TS_INLINE operator bool() const { return (node != nullptr); }
					TS_INLINE bool operator==(const Iterator &it) const { return (root == it.root && node == it.node); }
					TS_INLINE bool operator!=(const Iterator &it) const { return (root != it.root || node != it.node); }
					
					TS_INLINE Iterator &operator++() { if(node) node = node->next(); return *this; }
					TS_INLINE Iterator &operator--() { if(node) node = node->prev(); return *this; }
					TS_INLINE Iterator operator++(int32_t) { TreeNode *n = node; if(node) node = node->next(); return Iterator(root, n); }
					TS_INLINE Iterator operator--(int32_t) { TreeNode *n = node; if(node) node = node->prev(); return Iterator(root, n); }
					TS_INLINE Iterator left() { return Iterator(root, (node) ? node->left : nullptr); }
					TS_INLINE Iterator right() { return Iterator(root, (node) ? node->right : nullptr); }
					TS_INLINE Iterator next() { return Iterator(root, (node) ? node->next() : nullptr); }
					TS_INLINE Iterator prev() { return Iterator(root, (node) ? node->prev() : nullptr); }
					
					TS_INLINE Type &operator*() const { return node->data; }
					TS_INLINE Type *operator->() const { return &node->data; }
					TS_INLINE Type &get() const { return node->data; }
					
				private:
					
					TreeNode *root;
					TreeNode *node;
			};
			
			/// Constant iterator
			class ConstIterator {
					
				private:
					
					friend class Tree;
					
					ConstIterator(const TreeNode *root, const TreeNode *node) : root(root), node(node) { }
					
				public:
					
					ConstIterator() : root(nullptr), node(nullptr) { }
					ConstIterator(const Iterator &it) : root(it.root), node(it.node) { }
					ConstIterator(const ConstIterator &it) : root(it.root), node(it.node) { }
					
					void clear() { root = nullptr; node = nullptr; }
					
					ConstIterator &operator=(const Iterator &it) { root = it.root; node = it.node; return *this; }
					ConstIterator &operator=(const ConstIterator &it) { root = it.root; node = it.node; return *this; }
					
					explicit TS_INLINE operator bool() const { return (node != nullptr); }
					TS_INLINE bool operator==(const ConstIterator &it) const { return (root == it.root && node == it.node); }
					TS_INLINE bool operator!=(const ConstIterator &it) const { return (root != it.root || node != it.node); }
					
					TS_INLINE ConstIterator &operator++() { if(node) node = node->next(); return *this; }
					TS_INLINE ConstIterator &operator--() { if(node) node = node->prev(); return *this; }
					TS_INLINE ConstIterator operator++(int32_t) { const TreeNode *n = node; if(node) node = node->next(); return ConstIterator(root, n); }
					TS_INLINE ConstIterator operator--(int32_t) { const TreeNode *n = node; if(node) node = node->prev(); return ConstIterator(root, n); }
					TS_INLINE ConstIterator left() { return ConstIterator(root, (node) ? node->left : nullptr); }
					TS_INLINE ConstIterator right() { return ConstIterator(root, (node) ? node->right : nullptr); }
					TS_INLINE ConstIterator next() { return ConstIterator(root, (node) ? node->next() : nullptr); }
					TS_INLINE ConstIterator prev() { return ConstIterator(root, (node) ? node->prev() : nullptr); }
					
					TS_INLINE const Type &operator*() const { return node->data; }
					TS_INLINE const Type *operator->() const { return &node->data; }
					TS_INLINE const Type &get() const { return node->data; }
					
				private:
					
					const TreeNode *root;
					const TreeNode *node;
			};
			
			/// constructors
			Tree() { }
			Tree(const Tree &tree) { impl.copy(tree.impl); }
			Tree(Tree &&tree) { impl.move(tree.impl); }
			~Tree() { }
			
			/// clear tree
			TS_INLINE void clear() {
				impl.clear();
			}
			
			/// swap trees
			TS_INLINE void swap(Tree &t) {
				impl.swap(t.impl);
			}
			
			/// copy tree
			TS_INLINE void copy(const Tree &tree) {
				impl.copy(tree.impl);
			}
			TS_INLINE void move(Tree &&tree) {
				impl.move(tree.impl);
			}
			
			/// assignment operators
			TS_INLINE Tree &operator=(const Tree &tree) {
				if(&tree != this) impl.copy(tree.impl);
				return *this;
			}
			TS_INLINE Tree &operator=(Tree &&tree) {
				impl.move(tree.impl);
				return *this;
			}
			
			/// append value
			TS_INLINE Iterator append(const Type &value) {
				TreeNode *node = impl.append(value);
				return Iterator(impl.root, node);
			}
			template <class C> void append(const Tree<Type, C> &tree) {
				for(const auto &data: tree) impl.append(data);
			}
			
			/// remove value
			template <class T> TS_INLINE bool remove(const T &value) {
				return impl.remove(value);
			}
			TS_INLINE bool remove(const Iterator &it) {
				return impl.remove(it.node);
			}
			TS_INLINE bool remove(const ConstIterator &it) {
				return impl.remove(it.node);
			}
			
			/// tree info
			TS_INLINE bool empty() const { return (impl.length == 0); }
			explicit TS_INLINE operator bool() const { return (impl.length != 0); }
			TS_INLINE size_t memory() const { return sizeof(TreeNode) * impl.length; }
			TS_INLINE uint32_t size() const { return impl.length; }
			
			/// tree data
			template <class T> TS_INLINE Iterator find(const T &value) {
				return Iterator(impl.root, impl.find(value));
			}
			template <class T> TS_INLINE ConstIterator find(const T &value) const {
				return ConstIterator(impl.root, impl.find(value));
			}
			
			/// tree range
			template <class T> TS_INLINE Iterator prev(const T &value) {
				return Iterator(impl.root, impl.prev(value));
			}
			template <class T> TS_INLINE Iterator next(const T &value) {
				return Iterator(impl.root, impl.next(value));
			}
			template <class T> TS_INLINE ConstIterator prev(const T &value) const {
				return ConstIterator(impl.root, impl.prev(value));
			}
			template <class T> TS_INLINE ConstIterator next(const T &value) const {
				return ConstIterator(impl.root, impl.next(value));
			}
			
			/// tree iterators
			Iterator root() { return Iterator(impl.root, impl.root); }
			Iterator begin() { return Iterator(impl.root, (impl.root) ? impl.root->min() : nullptr); }
			Iterator back() { return Iterator(impl.root, (impl.root) ? impl.root->max() : nullptr); }
			Iterator end() { return Iterator(impl.root, nullptr); }
			ConstIterator root() const { return ConstIterator(impl.root, impl.root); }
			ConstIterator begin() const { return ConstIterator(impl.root, (impl.root) ? impl.root->min() : nullptr); }
			ConstIterator back() const { return ConstIterator(impl.root, (impl.root) ? impl.root->max() : nullptr); }
			ConstIterator end() const { return ConstIterator(impl.root, nullptr); }
			
		private:
			
			TreeImpl impl;		// tree implementation
	};
}

#endif /* __TELLUSIM_CORE_TREE_H__ */

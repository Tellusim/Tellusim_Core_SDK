// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_RADIX_H__
#define __TELLUSIM_CORE_RADIX_H__

#include <TellusimBase.h>

/*
 */
namespace Tellusim {
	
	/**
	 * RadixMap container
	 */
	template <class Key, class Type, uint32_t Size = 32> class RadixMap {
			
		private:
			
			enum {
				Step		= 8,
				Radix4		= 4,
				Radix16		= 16,
				Radix64		= 64,
				Radix256	= 256,
			};
			
			TS_STATIC_ASSERT(Size % Step == 0);
			
			/// radix node
			struct Node {
				
				Node(Node *parent, uint16_t capacity) : parent(parent), capacity(capacity) { }
				virtual ~Node() { }
				
				/// release node
				virtual void release(uint32_t shift) = 0;
				
				/// node info
				virtual size_t memory(uint32_t shift) const = 0;
				virtual uint32_t size(uint32_t shift) const = 0;
				
				/// node iterator
				virtual uint32_t find(const Node *node) const = 0;
				virtual Node *min(uint32_t shift, uint32_t &index) = 0;
				virtual Node *max(uint32_t shift, uint32_t &index) = 0;
				virtual Node *prev(uint32_t shift, uint32_t &index) = 0;
				virtual Node *next(uint32_t shift, uint32_t &index) = 0;
				
				/// find value
				virtual Node *find(Key key, uint32_t shift, uint32_t &index) = 0;
				
				/// node value
				virtual Node *append(Key key, uint32_t shift, uint32_t &index) = 0;
				virtual bool remove(Key key, uint32_t shift) = 0;
				
				/// node data
				virtual Type &ref(uint32_t index) = 0;
				virtual Type *get(uint32_t index) = 0;
				
				/// node data
				TS_INLINE static Node *allocate() {
					return (Node*)(new Type());
				}
				TS_INLINE static void release(Node *ptr) {
					delete (Type*)ptr;
				}
				
				Node *parent = nullptr;		// parent node
				
				uint16_t length = 0;		// node length
				uint16_t capacity = 0;		// node capacity
			};
			
			/// radix node with N elements
			template <uint32_t Capacity> struct NodeN : public Node {
				
				explicit NodeN(Node *parent) : Node(parent, Capacity) { }
				
				/// release node
				virtual void release(uint32_t shift) {
					for(uint32_t i = 0; i < Node::length; i++) {
						if(shift) {
							data[i]->release(shift - Step);
							delete data[i];
						} else {
							Node::release(data[i]);
						}
						data[i] = nullptr;
						keys[i] = 0;
					}
					Node::length = 0;
				}
				
				/// node info
				virtual size_t memory(uint32_t shift) const {
					size_t ret = sizeof(NodeN<Capacity>);
					for(uint32_t i = 0; i < Node::length; i++) {
						if(shift) ret += data[i]->memory(shift - Step);
						else ret += sizeof(Type);
					}
					return ret;
				}
				virtual uint32_t size(uint32_t shift) const {
					uint32_t ret = 0;
					for(uint32_t i = 0; i < Node::length; i++) {
						if(shift) ret += data[i]->size(shift - Step);
						else ret++;
					}
					return ret;
				}
				
				/// node iterator
				virtual uint32_t find(const Node *node) const {
					for(uint32_t i = 0; i < Node::length; i++) {
						if(data[i] == node) return i;
					}
					return Maxu32;
				}
				virtual Node *min(uint32_t shift, uint32_t &index) {
					for(uint32_t i = 0; i < Node::length; i++) {
						if(shift) {
							Node *ret = data[i]->min(shift - Step, index);
							if(ret) return ret;
						} else {
							index = i;
							return this;
						}
					}
					index = Maxu32;
					return nullptr;
				}
				virtual Node *max(uint32_t shift, uint32_t &index) {
					for(uint32_t i = Node::length - 1; i < Capacity; i--) {
						if(shift) {
							Node *ret = data[i]->max(shift - Step, index);
							if(ret) return ret;
						} else {
							index = i;
							return this;
						}
					}
					index = Maxu32;
					return nullptr;
				}
				virtual Node *prev(uint32_t shift, uint32_t &index) {
					if(--index < Node::length) {
						if(shift) return data[index]->max(shift - Step, index);
						return this;
					}
					if(Node::parent) {
						index = Node::parent->find(this);
						return Node::parent->prev(shift + Step, index);
					}
					index = Maxu32;
					return nullptr;
				}
				virtual Node *next(uint32_t shift, uint32_t &index) {
					if(++index < Node::length) {
						if(shift) return data[index]->min(shift - Step, index);
						return this;
					}
					if(Node::parent) {
						index = Node::parent->find(this);
						return Node::parent->next(shift + Step, index);
					}
					index = Maxu32;
					return nullptr;
				}
				
				/// find value
				virtual Node *find(Key key, uint32_t shift, uint32_t &index) {
					uint8_t radix = (uint8_t)(key >> shift);
					for(uint32_t i = 0; i < Node::length; i++) {
						if(keys[i] == radix) {
							if(shift) {
								return data[i]->find(key, shift - Step, index);
							} else {
								index = i;
								return this;
							}
						} else if(keys[i] > radix) {
							break;
						}
					}
					index = Maxu32;
					return nullptr;
				}
				
				/// node value
				virtual Node *append(Key key, uint32_t shift, uint32_t &index) {
					uint32_t position = Node::length;
					uint8_t radix = (uint8_t)(key >> shift);
					for(uint32_t i = 0; i < Node::length; i++) {
						if(keys[i] == radix) {
							if(shift) {
								data[i] = expand(shift - Step, data[i]);
								return data[i]->append(key, shift - Step, index);
							} else {
								index = i;
								return this;
							}
						} else if(keys[i] > radix) {
							position = i;
							break;
						}
					}
					for(uint32_t i = Node::length; i > position; i--) {
						if(keys[i - 1] > radix) {
							keys[i] = keys[i - 1];
							data[i] = data[i - 1];
						}
					}
					Node::length++;
					keys[position] = radix;
					if(shift) {
						data[position] = new NodeN<Radix4>(this);
						return data[position]->append(key, shift - Step, index);
					}
					data[position] = Node::allocate();
					index = position;
					return this;
				}
				virtual bool remove(Key key, uint32_t shift) {
					uint8_t radix = (uint8_t)(key >> shift);
					for(uint32_t i = 0; i < Node::length; i++) {
						if(keys[i] == radix) {
							if(shift) {
								if(data[i]->remove(key, shift - Step)) {
									data[i] = shrink(shift - Step, data[i]);
									if(data[i] == nullptr) {
										Node::length--;
										for(uint32_t j = i; j < Node::length; j++) {
											keys[j] = keys[j + 1];
											data[j] = data[j + 1];
										}
									}
									return true;
								}
								return false;
							}
							Node::length--;
							Node::release(data[i]);
							for(uint32_t j = i; j < Node::length; j++) {
								keys[j] = keys[j + 1];
								data[j] = data[j + 1];
							}
							return true;
						} else if(keys[i] > radix) {
							break;
						}
					}
					return false;
				}
				
				/// node data
				virtual Type &ref(uint32_t index) {
					TS_ASSERT(index < Node::length && "RadixMap::NodeN::ref(): invalid index");
					TS_ASSERT(data[index] && "RadixMap::NodeN::ref(): pointer is null");
					return *(Type*)data[index];
				}
				virtual Type *get(uint32_t index) {
					TS_ASSERT(index < Node::length && "RadixMap::NodeN::get(): invalid index");
					return (Type*)data[index];
				}
				
				uint8_t keys[Capacity] = {};	// node keys
				Node *data[Capacity] = {};		// node pointers
			};
			
			/// radix node with 64 elements
			struct Node64 : public Node {
				
				explicit Node64(Node *parent) : Node(parent, Radix64) {
					memset(keys, Maxu8, Radix256);
				}
				
				/// release node
				virtual void release(uint32_t shift) {
					for(uint32_t i = 0; i < Radix64; i++) {
						if(data[i]) {
							if(shift) {
								data[i]->release(shift - Step);
								delete data[i];
							} else {
								Node::release(data[i]);
							}
							data[i] = nullptr;
						}
					}
					memset(keys, Maxu8, Radix256);
					Node::length = 0;
				}
				
				/// node info
				virtual size_t memory(uint32_t shift) const {
					size_t ret = sizeof(Node64);
					for(uint32_t i = 0; i < Radix64; i++) {
						if(data[i]) {
							if(shift) ret += data[i]->memory(shift - Step);
							else ret += sizeof(Type);
						}
					}
					return ret;
				}
				virtual uint32_t size(uint32_t shift) const {
					uint32_t ret = 0;
					for(uint32_t i = 0; i < Radix64; i++) {
						if(data[i]) {
							if(shift) ret += data[i]->size(shift - Step);
							else ret++;
						}
					}
					return ret;
				}
				
				/// node iterator
				virtual uint32_t find(const Node *node) const {
					for(uint32_t i = 0; i < Radix64; i++) {
						if(data[i] == node) {
							for(uint32_t j = 0; j < Radix256; j++) {
								if(keys[j] == i) return j;
							}
						}
					}
					return Maxu32;
				}
				virtual Node *min(uint32_t shift, uint32_t &index) {
					for(uint32_t i = 0; i < Radix256; i++) {
						if(keys[i] != Maxu8) {
							if(shift) {
								Node *ret = data[keys[i]]->min(shift - Step, index);
								if(ret) return ret;
							} else {
								index = i;
								return this;
							}
						}
					}
					index = Maxu32;
					return nullptr;
				}
				virtual Node *max(uint32_t shift, uint32_t &index) {
					for(uint32_t i = Radix256 - 1; i < Radix256; i--) {
						if(keys[i] != Maxu8) {
							if(shift) {
								Node *ret = data[keys[i]]->max(shift - Step, index);
								if(ret) return ret;
							} else {
								index = i;
								return this;
							}
						}
					}
					index = Maxu32;
					return nullptr;
				}
				virtual Node *prev(uint32_t shift, uint32_t &index) {
					for(index--; index < Radix256; index--) {
						if(keys[index] != Maxu8) {
							if(shift) return data[keys[index]]->max(shift - Step, index);
							return this;
						}
					}
					if(Node::parent) {
						index = Node::parent->find(this);
						return Node::parent->prev(shift + Step, index);
					}
					index = Maxu32;
					return nullptr;
				}
				virtual Node *next(uint32_t shift, uint32_t &index) {
					for(index++; index < Radix256; index++) {
						if(keys[index] != Maxu8) {
							if(shift) return data[keys[index]]->min(shift - Step, index);
							return this;
						}
					}
					if(Node::parent) {
						index = Node::parent->find(this);
						return Node::parent->next(shift + Step, index);
					}
					index = Maxu32;
					return nullptr;
				}
				
				/// find value
				virtual Node *find(Key key, uint32_t shift, uint32_t &index) {
					uint8_t radix = (uint8_t)(key >> shift);
					if(keys[radix] != Maxu8) {
						if(shift) return data[keys[radix]]->find(key, shift - Step, index);
						index = radix;
						return this;
					}
					index = Maxu32;
					return nullptr;
				}
				
				/// node value
				virtual Node *append(Key key, uint32_t shift, uint32_t &index) {
					uint8_t radix = (uint8_t)(key >> shift);
					if(shift) {
						if(keys[radix] != Maxu8) {
							data[keys[radix]] = expand(shift - Step, data[keys[radix]]);
						} else {
							for(uint32_t i = 0; i < Radix64; i++) {
								if(data[i] == nullptr) {
									keys[radix] = (uint8_t)i;
									Node::length++;
									break;
								}
							}
							data[keys[radix]] = new NodeN<Radix4>(this);
						}
						return data[keys[radix]]->append(key, shift - Step, index);
					}
					if(keys[radix] == Maxu8) {
						for(uint32_t i = 0; i < Radix64; i++) {
							if(data[i] == nullptr) {
								keys[radix] = (uint8_t)i;
								Node::length++;
								break;
							}
						}
						data[keys[radix]] = Node::allocate();
					}
					index = radix;
					return this;
				}
				virtual bool remove(Key key, uint32_t shift) {
					uint8_t radix = (uint8_t)(key >> shift);
					if(shift) {
						if(keys[radix] != Maxu8 && data[keys[radix]]->remove(key, shift - Step)) {
							data[keys[radix]] = shrink(shift - Step, data[keys[radix]]);
							if(data[keys[radix]] == nullptr) {
								keys[radix] = Maxu8;
								Node::length--;
							}
							return true;
						}
						return false;
					}
					if(keys[radix] != Maxu8) {
						Node::release(data[keys[radix]]);
						data[keys[radix]] = nullptr;
						keys[radix] = Maxu8;
						Node::length--;
						return true;
					}
					return false;
				}
				
				/// node data
				virtual Type &ref(uint32_t index) {
					TS_ASSERT(keys[index] != Maxu8 && "RadixMap::Node64::ref(): invalid index");
					TS_ASSERT(data[keys[index]] && "RadixMap::Node64::ref(): pointer is null");
					return *(Type*)data[keys[index]];
				}
				virtual Type *get(uint32_t index) {
					TS_ASSERT(keys[index] != Maxu8 && "RadixMap::Node64::get(): invalid index");
					return (Type*)data[keys[index]];
				}
				
				uint8_t keys[Radix256];			// node keys
				Node *data[Radix64] = {};		// node pointers
			};
			
			/// radix node with 256 elements
			struct Node256 : public Node {
				
				explicit Node256(Node *parent) : Node(parent, Radix256) { }
				
				/// release node
				virtual void release(uint32_t shift) {
					for(uint32_t i = 0; i < Radix256; i++) {
						if(data[i]) {
							if(shift) {
								data[i]->release(shift - Step);
								delete data[i];
							} else {
								Node::release(data[i]);
							}
							data[i] = nullptr;
						}
					}
					Node::length = 0;
				}
				
				/// node info
				virtual size_t memory(uint32_t shift) const {
					size_t ret = sizeof(Node256);
					for(uint32_t i = 0; i < Radix256; i++) {
						if(data[i]) {
							if(shift) ret += data[i]->memory(shift - Step);
							else ret += sizeof(Type);
						}
					}
					return ret;
				}
				virtual uint32_t size(uint32_t shift) const {
					uint32_t ret = 0;
					for(uint32_t i = 0; i < Radix256; i++) {
						if(data[i]) {
							if(shift) ret += data[i]->size(shift - Step);
							else ret++;
						}
					}
					return ret;
				}
				
				/// node iterator
				virtual uint32_t find(const Node *node) const {
					for(uint32_t i = 0; i < Radix256; i++) {
						if(data[i] == node) return i;
					}
					return Maxu32;
				}
				virtual Node *min(uint32_t shift, uint32_t &index) {
					for(uint32_t i = 0; i < Radix256; i++) {
						if(data[i]) {
							if(shift) {
								Node *ret = data[i]->min(shift - Step, index);
								if(ret) return ret;
							} else {
								index = i;
								return this;
							}
						}
					}
					index = Maxu32;
					return nullptr;
				}
				virtual Node *max(uint32_t shift, uint32_t &index) {
					for(uint32_t i = Radix256 - 1; i < Radix256; i++) {
						if(data[i]) {
							if(shift) {
								Node *ret = data[i]->max(shift - Step, index);
								if(ret) return ret;
							} else {
								index = i;
								return this;
							}
						}
					}
					index = Maxu32;
					return nullptr;
				}
				virtual Node *prev(uint32_t shift, uint32_t &index) {
					for(index--; index < Radix256; index--) {
						if(data[index]) {
							if(shift) return data[index]->max(shift - Step, index);
							return this;
						}
					}
					if(Node::parent) {
						index = Node::parent->find(this);
						return Node::parent->prev(shift + Step, index);
					}
					index = Maxu32;
					return nullptr;
				}
				virtual Node *next(uint32_t shift, uint32_t &index) {
					for(index++; index < Radix256; index++) {
						if(data[index]) {
							if(shift) return data[index]->min(shift - Step, index);
							return this;
						}
					}
					if(Node::parent) {
						index = Node::parent->find(this);
						return Node::parent->next(shift + Step, index);
					}
					index = Maxu32;
					return nullptr;
				}
				
				/// find value
				virtual Node *find(Key key, uint32_t shift, uint32_t &index) {
					uint8_t radix = (uint8_t)(key >> shift);
					if(data[radix]) {
						if(shift) return data[radix]->find(key, shift - Step, index);
						index = radix;
						return this;
					}
					index = Maxu32;
					return nullptr;
				}
				
				/// node value
				virtual Node *append(Key key, uint32_t shift, uint32_t &index) {
					uint8_t radix = (uint8_t)(key >> shift);
					if(shift) {
						if(data[radix]) {
							data[radix] = expand(shift - Step, data[radix]);
						} else {
							data[radix] = new NodeN<Radix4>(this);
							Node::length++;
						}
						return data[radix]->append(key, shift - Step, index);
					}
					if(data[radix] == nullptr) {
						data[radix] = Node::allocate();
						Node::length++;
					}
					index = radix;
					return this;
				}
				virtual bool remove(Key key, uint32_t shift) {
					uint8_t radix = (uint8_t)(key >> shift);
					if(shift) {
						if(data[radix] && data[radix]->remove(key, shift - Step)) {
							data[radix] = shrink(shift - Step, data[radix]);
							if(data[radix] == nullptr) {
								Node::length--;
							}
							return true;
						}
						return false;
					}
					if(data[radix]) {
						Node::release(data[radix]);
						data[radix] = nullptr;
						Node::length--;
						return true;
					}
					return false;
				}
				
				/// node data
				virtual Type &ref(uint32_t index) {
					TS_ASSERT(data[index] && "RadixMap::Node256::ref(): pointer is null");
					return *(Type*)data[index];
				}
				virtual Type *get(uint32_t index) {
					return (Type*)data[index];
				}
				
				Node *data[Radix256] = {};		// node pointers
			};
			
			/// expand node
			static Node *expand(uint32_t shift, Node *node) {
				if(node->length + 1 == node->capacity) {
					if(node->capacity == Radix4) {
						NodeN<Radix16> *dest = new NodeN<Radix16>(node->parent);
						const NodeN<Radix4> *src = (const NodeN<Radix4>*)node;
						if(shift) {
							for(uint32_t i = 0; i < node->length; i++) {
								dest->keys[i] = src->keys[i];
								dest->data[i] = src->data[i];
								dest->data[i]->parent = dest;
							}
						} else {
							for(uint32_t i = 0; i < node->length; i++) {
								dest->keys[i] = src->keys[i];
								dest->data[i] = src->data[i];
							}
						}
						dest->length = src->length;
						delete node;
						return dest;
					}
					if(node->capacity == Radix16) {
						Node64 *dest = new Node64(node->parent);
						const NodeN<Radix16> *src = (const NodeN<Radix16>*)node;
						if(shift) {
							for(uint32_t i = 0; i < node->length; i++) {
								dest->keys[src->keys[i]] = (uint8_t)i;
								dest->data[i] = src->data[i];
								dest->data[i]->parent = dest;
							}
						} else {
							for(uint32_t i = 0; i < node->length; i++) {
								dest->keys[src->keys[i]] = (uint8_t)i;
								dest->data[i] = src->data[i];
							}
						}
						dest->length = src->length;
						delete node;
						return dest;
					}
					if(node->capacity == Radix64) {
						Node256 *dest = new Node256(node->parent);
						const Node64 *src = (const Node64*)node;
						if(shift) {
							for(uint32_t i = 0; i < Radix256; i++) {
								if(src->keys[i] != Maxu8) {
									dest->data[i] = src->data[src->keys[i]];
									dest->data[i]->parent = dest;
								}
							}
						} else {
							for(uint32_t i = 0; i < Radix256; i++) {
								if(src->keys[i] != Maxu8) {
									dest->data[i] = src->data[src->keys[i]];
								}
							}
						}
						dest->length = src->length;
						delete node;
						return dest;
					}
				}
				return node;
			}
			
			/// shrink node
			static Node *shrink(uint32_t shift, Node *node) {
				if(node->length == 0) {
					delete node;
					return nullptr;
				}
				if(node->length < Radix4 && node->capacity == Radix16) {
					NodeN<Radix4> *dest = new NodeN<Radix4>(node->parent);
					const NodeN<Radix16> *src = (const NodeN<Radix16>*)node;
					if(shift) {
						for(uint32_t i = 0; i < node->length; i++) {
							dest->keys[i] = src->keys[i];
							dest->data[i] = src->data[i];
							dest->data[i]->parent = dest;
						}
					} else {
						for(uint32_t i = 0; i < node->length; i++) {
							dest->keys[i] = src->keys[i];
							dest->data[i] = src->data[i];
						}
					}
					dest->length = src->length;
					delete node;
					return dest;
				}
				if(node->length < Radix16 && node->capacity == Radix64) {
					NodeN<Radix16> *dest = new NodeN<Radix16>(node->parent);
					const Node64 *src = (const Node64*)node;
					if(shift) {
						for(uint32_t i = 0, j = 0; i < Radix256; i++) {
							if(src->keys[i] != Maxu8) {
								dest->keys[j] = (uint8_t)i;
								dest->data[j] = src->data[src->keys[i]];
								dest->data[j++]->parent = dest;
							}
						}
					} else {
						for(uint32_t i = 0, j = 0; i < Radix256; i++) {
							if(src->keys[i] != Maxu8) {
								dest->keys[j] = (uint8_t)i;
								dest->data[j++] = src->data[src->keys[i]];
							}
						}
					}
					dest->length = src->length;
					delete node;
					return dest;
				}
				if(node->length < Radix64 && node->capacity == Radix256) {
					Node64 *dest = new Node64(node->parent);
					const Node256 *src = (const Node256*)node;
					if(shift) {
						for(uint32_t i = 0, j = 0; i < Radix256; i++) {
							if(src->data[i]) {
								dest->keys[i] = (uint8_t)j;
								dest->data[j] = src->data[i];
								dest->data[j++]->parent = dest;
							}
						}
					} else {
						for(uint32_t i = 0, j = 0; i < Radix256; i++) {
							if(src->data[i]) {
								dest->keys[i] = (uint8_t)j;
								dest->data[j++] = src->data[i];
							}
						}
					}
					dest->length = src->length;
					delete node;
					return dest;
				}
				return node;
			}
			
		public:
			
			/// Iterator
			class Iterator {
					
				private:
					
					friend class RadixMap;
					
					Iterator(Node *root, Node *node, uint32_t index) : root(root), node(node), index(index) { }
					
				public:
					
					Iterator() : root(nullptr), node(nullptr), index(Maxu32) { }
					Iterator(const Iterator &it) : root(it.root), node(it.node), index(it.index) { }
					
					void clear() { root = nullptr; node = nullptr; index = Maxu32; }
					
					Iterator &operator=(const Iterator &it) { root = it.root; node = it.node; index = it.index; return *this; }
					
					explicit TS_INLINE operator bool() const { return (node != nullptr && index != Maxu32); }
					TS_INLINE bool operator==(const Iterator &it) const { return (root == it.root && node == it.node && index == it.index); }
					TS_INLINE bool operator!=(const Iterator &it) const { return (root != it.root || node != it.node || index != it.index); }
					
					TS_INLINE Iterator &operator++() { if(node) node = node->next(0, index); return *this; }
					TS_INLINE Iterator &operator--() { if(node) node = node->prev(0, index); return *this; }
					TS_INLINE Iterator operator++(int32_t) { Node *n = node; uint32_t i = index; if(node) node = node->next(0, index); return Iterator(root, n, i); }
					TS_INLINE Iterator operator--(int32_t) { Node *n = node; uint32_t i = index; if(node) node = node->prev(0, index); return Iterator(root, n, i); }
					TS_INLINE Iterator next() { uint32_t i = index; Node *n = (node) ? node->next(0, i) : nullptr; return Iterator(root, n, i); }
					TS_INLINE Iterator prev() { uint32_t i = index; Node *n = (node) ? node->prev(0, i) : nullptr; return Iterator(root, n, i); }
					
					TS_INLINE Type &operator*() { return node->ref(index); }
					TS_INLINE Type *operator->() { return node->get(index); }
					TS_INLINE Type &get() { return node->ref(index); }
					
				private:
					
					Node *root;
					Node *node;
					uint32_t index;
			};
			
			/// Constant iterator
			class ConstIterator {
					
				private:
					
					friend class RadixMap;
					
					ConstIterator(Node *root, Node *node, uint32_t index) : root(root), node(node), index(index) { }
					
				public:
					
					ConstIterator() : root(nullptr), node(nullptr), index(Maxu32) { }
					ConstIterator(const Iterator &it) : root(it.root), node(it.node), index(it.index) { }
					
					void clear() { root = nullptr; node = nullptr; index = Maxu32; }
					
					ConstIterator &operator=(const Iterator &it) { root = it.root; node = it.node; index = it.index; return *this; }
					ConstIterator &operator=(const ConstIterator &it) { root = it.root; node = it.node; index = it.index; return *this; }
					
					explicit TS_INLINE operator bool() const { return (node != nullptr && index != Maxu32); }
					TS_INLINE bool operator==(const ConstIterator &it) const { return (root == it.root && node == it.node && index == it.index); }
					TS_INLINE bool operator!=(const ConstIterator &it) const { return (root != it.root || node != it.node || index != it.index); }
					
					TS_INLINE ConstIterator &operator++() { if(node) node = node->next(0, index); return *this; }
					TS_INLINE ConstIterator &operator--() { if(node) node = node->prev(0, index); return *this; }
					TS_INLINE ConstIterator operator++(int32_t) { Node *n = node; uint32_t i = index; if(node) node = node->next(0, index); return Iterator(root, n, i); }
					TS_INLINE ConstIterator operator--(int32_t) { Node *n = node; uint32_t i = index; if(node) node = node->prev(0, index); return Iterator(root, n, i); }
					TS_INLINE ConstIterator next() { uint32_t i = index; Node *n = (node) ? node->next(0, i) : nullptr; return Iterator(root, n, i); }
					TS_INLINE ConstIterator prev() { uint32_t i = index; Node *n = (node) ? node->prev(0, i) : nullptr; return Iterator(root, n, i); }
					
					TS_INLINE const Type &operator*() const { return node->ref(index); }
					TS_INLINE const Type *operator->() const { return node->get(index); }
					TS_INLINE const Type &get() const { return node->ref(index); }
					
				private:
					
					Node *root;
					Node *node;
					uint32_t index;
			};
			
			/// constructors
			RadixMap() { }
			RadixMap(const RadixMap&) = delete;
			RadixMap(RadixMap &&map) { move(map); }
			~RadixMap() { clear(); }
			
			/// clear map
			void clear() {
				if(root) root->release(Size - Step);
				delete root;
				root = nullptr;
			}
			
			/// swap maps
			TS_INLINE void swap(RadixMap &map) {
				Tellusim::swap(root, map.root);
			}
			
			/// move map
			TS_INLINE void move(RadixMap &&map) {
				clear();
				root = map.root;
				map.root = nullptr;
			}
			
			/// assignment operators
			RadixMap &operator=(const RadixMap&) = delete;
			RadixMap &operator=(RadixMap &&map) {
				move(map);
				return *this;
			}
			
			/// append value
			TS_INLINE Iterator append(Key value) {
				uint32_t index = Maxu32;
				root = (root) ? expand(Size - Step, root) : new NodeN<Radix4>(nullptr);
				Node *node = root->append(value, Size - Step, index);
				return Iterator(root, node, index);
			}
			TS_INLINE Iterator append(Key value, const Type &data) {
				uint32_t index = Maxu32;
				root = (root) ? expand(Size - Step, root) : new NodeN<Radix4>(nullptr);
				Node *node = root->append(value, Size - Step, index);
				if(node) node->ref(index) = data;
				return Iterator(root, node, index);
			}
			
			/// remove value
			TS_INLINE bool remove(uint32_t value) {
				return (root && root->remove(value, Size - Step));
			}
			
			/// map info
			TS_INLINE bool empty() const { return (root) ? (root->length == 0) : true; }
			explicit TS_INLINE operator bool() const { return (root) ? (root->length != 0) : false; }
			TS_INLINE size_t memory() const { return (root) ? root->memory(Size - Step) : 0; }
			TS_INLINE uint32_t size() const { return (root) ? root->size(Size - Step) : 0; }
			
			/// map data
			TS_INLINE Iterator find(Key value) {
				uint32_t index = Maxu32;
				Node *node = (root) ? root->find(value, Size - Step, index) : nullptr;
				return Iterator(root, node, index);
			}
			TS_INLINE ConstIterator find(Key value) const {
				uint32_t index = Maxu32;
				Node *node = (root) ? root->find(value, Size - Step, index) : nullptr;
				return ConstIterator(root, node, index);
			}
			TS_INLINE const Type &operator[](Key value) const {
				uint32_t index = Maxu32;
				Node *node = (root) ? root->find(value, Size - Step, index) : nullptr;
				TS_ASSERT(node && "RadixMap::operator[](): invalid key");
				return node->ref(index);
			}
			TS_INLINE Type &operator[](Key value) {
				uint32_t index = Maxu32;
				root = (root) ? expand(Size - Step, root) : new NodeN<Radix4>(nullptr);
				Node *node = root->append(value, Size - Step, index);
				return node->ref(index);
			}
			TS_INLINE const Type &get(Key value) const {
				uint32_t index = Maxu32;
				Node *node = (root) ? root->find(value, Size - Step, index) : nullptr;
				TS_ASSERT(node && "RadixMap::get(): invalid key");
				return node->ref(index);
			}
			TS_INLINE Type &get(Key value) {
				uint32_t index = Maxu32;
				root = (root) ? expand(Size - Step, root) : new NodeN<Radix4>(nullptr);
				Node *node = root->append(value, Size - Step, index);
				return node->ref(index);
			}
			
			/// map iterators
			TS_INLINE Iterator begin() {
				uint32_t index = Maxu32;
				Node *node = (root) ? root->min(Size - Step, index) : nullptr;
				return Iterator(root, node, index);
			}
			TS_INLINE Iterator back() {
				uint32_t index = Maxu32;
				Node *node = (root) ? root->max(Size - Step, index) : nullptr;
				return Iterator(root, node, index);
			}
			TS_INLINE Iterator end() {
				return Iterator(root, nullptr, Maxu32);
			}
			TS_INLINE ConstIterator begin() const {
				uint32_t index = Maxu32;
				Node *node = (root) ? root->min(Size - Step, index) : nullptr;
				return ConstIterator(root, node, index);
			}
			TS_INLINE ConstIterator back() const {
				uint32_t index = Maxu32;
				Node *node = (root) ? root->max(Size - Step, index) : nullptr;
				return ConstIterator(root, node, index);
			}
			TS_INLINE ConstIterator end() const {
				return ConstIterator(root, nullptr, Maxu32);
			}
			
		private:
			
			Node *root = nullptr;		// root node
	};
}

#endif /* __TELLUSIM_CORE_RADIX_H__ */

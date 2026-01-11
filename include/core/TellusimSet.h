// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_SET_H__
#define __TELLUSIM_CORE_SET_H__

#include <core/TellusimTree.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Set default compare
	 */
	template <class Type> struct SetCompare {
		TS_INLINE int32_t operator()(const Type &s0, const Type &s1) const {
			if(s0 == s1) return 0;
			if(s0 < s1) return -1;
			return 1;
		}
		template <class T> TS_INLINE int32_t operator()(const Type &s0, const T &s1) const {
			if(s0 == s1) return 0;
			if(s0 < s1) return -1;
			return 1;
		}
		template <class T> TS_INLINE int32_t operator()(const T &s0, const Type &s1) const {
			if(s0 == s1) return 0;
			if(s0 < s1) return -1;
			return 1;
		}
	};
	
	template <> struct SetCompare<const char*> {
		TS_INLINE int32_t operator()(const char *s0, const char *s1) const {
			return strcmp(s0, s1);
		}
		template <class T> TS_INLINE int32_t operator()(const char *s0, const T &s1) const {
			if(s0 == s1) return 0;
			if(s0 < s1) return -1;
			return 1;
		}
		template <class T> TS_INLINE int32_t operator()(const T &s0, const char *s1) const {
			if(s0 == s1) return 0;
			if(s0 < s1) return -1;
			return 1;
		}
	};
	
	/**
	 * Set container
	 */
	template <class Type, class Compare = SetCompare<Type>> class Set {
			
		public:
			
			/// tree types
			using Tree = Tellusim::Tree<Type, Compare>;
			using Iterator = typename Tree::Iterator;
			using ConstIterator = typename Tree::ConstIterator;
			
			Set() { }
			Set(const Set &set) { tree.copy(set.tree); }
			Set(const InitializerList<Type> &list) { copy(list); }
			Set(Set &&set) { tree.move((Tree&&)set.tree); }
			~Set() { }
			
			/// clear set
			TS_INLINE void clear() {
				tree.clear();
			}
			
			/// swap sets
			TS_INLINE void swap(Set &set) {
				tree.swap(set.tree);
			}
			
			/// copy set
			TS_INLINE void copy(const Set &set) {
				tree.copy(set.tree);
			}
			void copy(const InitializerList<Type> &list) {
				tree.clear();
				for(const auto &it : list) {
					tree.append(it);
				}
			}
			
			/// assignment operators
			TS_INLINE Set &operator=(const Set &set) {
				if(&set != this) tree.copy(set.tree);
				return *this;
			}
			TS_INLINE Set &operator=(Set &&set) {
				tree.move((Tree&&)set.tree);
				return *this;
			}
			TS_INLINE Set &operator=(const InitializerList<Type> &list) {
				copy(list);
				return *this;
			}
			
			/// append value
			TS_INLINE Iterator append(const Type &value) {
				return tree.append(value);
			}
			template <class C> void append(const Set<Type, C> &set) {
				for(const auto &it : set) {
					tree.append(it);
				}
			}
			
			/// remove value
			template <class T> TS_INLINE bool remove(const T &value) {
				return tree.remove(value);
			}
			TS_INLINE bool remove(const Iterator &it) {
				return tree.remove(it);
			}
			TS_INLINE bool remove(const ConstIterator &it) {
				return tree.remove(it);
			}
			
			/// set info
			TS_INLINE bool empty() const { return tree.empty(); }
			explicit TS_INLINE operator bool() const { return (bool)tree; }
			TS_INLINE size_t memory() const { return tree.memory(); }
			TS_INLINE uint32_t size() const { return tree.size(); }
			
			/// set data
			template <class T> TS_INLINE Iterator find(const T &value) {
				return tree.find(value);
			}
			template <class T> TS_INLINE ConstIterator find(const T &value) const {
				return tree.find(value);
			}
			
			/// set range
			template <class T> TS_INLINE Iterator prev(const T &value) {
				return tree.prev(value);
			}
			template <class T> TS_INLINE Iterator next(const T &value) {
				return tree.next(value);
			}
			template <class T> TS_INLINE ConstIterator prev(const T &value) const {
				return tree.prev(value);
			}
			template <class T> TS_INLINE ConstIterator next(const T &value) const {
				return tree.next(value);
			}
			
			/// set iterators
			TS_INLINE Iterator root() { return tree.root(); }
			TS_INLINE Iterator begin() { return tree.begin(); }
			TS_INLINE Iterator back() { return tree.back(); }
			TS_INLINE Iterator end() { return tree.end(); }
			TS_INLINE ConstIterator root() const { return tree.root(); }
			TS_INLINE ConstIterator begin() const { return tree.begin(); }
			TS_INLINE ConstIterator back() const { return tree.back(); }
			TS_INLINE ConstIterator end() const { return tree.end(); }
			
		private:
			
			Tree tree;		// set implementation
	};
	
	/**
	 * Swap sets
	 */
	template <class Type, class Compare> void swap(Set<Type, Compare> &s0, Set<Type, Compare> &s1) {
		s0.swap(s1);
	}
}

#endif /* __TELLUSIM_CORE_SET_H__ */

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_MAP_H__
#define __TELLUSIM_CORE_MAP_H__

#include <core/TellusimTree.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Map data
	 */
	template <class Key, class Type> struct MapData {
		MapData() { }
		MapData(const Key &key, const Type &data) : key(key), data(data) { }
		TS_INLINE const Type &operator*() const { return data; }
		TS_INLINE const Type *operator->() const { return &data; }
		TS_INLINE const Type &get() const { return data; }
		TS_INLINE Type &operator*() { return data; }
		TS_INLINE Type *operator->() { return &data; }
		TS_INLINE Type &get() { return data; }
		Key key;
		Type data;
	};
	
	/**
	 * Map default compare
	 */
	template <class Key, class Type> struct MapCompare {
		TS_INLINE int32_t operator()(const MapData<Key, Type> &m0, const MapData<Key, Type> &m1) const {
			if(m0.key == m1.key) return 0;
			if(m0.key < m1.key) return -1;
			return 1;
		}
		template <class K> TS_INLINE int32_t operator()(const MapData<Key, Type> &m, const K &key) const {
			if(m.key == key) return 0;
			if(m.key < key) return -1;
			return 1;
		}
		template <class K> TS_INLINE int32_t operator()(const K &key, const MapData<Key, Type> &m) const {
			if(key == m.key) return 0;
			if(key < m.key) return -1;
			return 1;
		}
	};
	
	template <class Type> struct MapCompare<const char*, Type> {
		TS_INLINE int32_t operator()(const MapData<const char*, Type> &m0, const MapData<const char*, Type> &m1) const {
			return strcmp(m0.key, m1.key);
		}
		template <class K> TS_INLINE int32_t operator()(const MapData<const char*, Type> &m, const K &key) const {
			if(m.key == key) return 0;
			if(m.key < key) return -1;
			return 1;
		}
		template <class K> TS_INLINE int32_t operator()(const K &key, const MapData<const char*, Type> &m) const {
			if(key == m.key) return 0;
			if(key < m.key) return -1;
			return 1;
		}
	};
	
	/**
	 * Map container
	 */
	template <class Key, class Type, class Compare = MapCompare<Key, Type>> class Map {
			
		public:
			
			/// tree types
			using Tree = Tellusim::Tree<MapData<Key, Type>, Compare>;
			using Iterator = typename Tree::Iterator;
			using ConstIterator = typename Tree::ConstIterator;
			
			Map() { }
			Map(const Map &map) { tree.copy(map.tree); }
			Map(const InitializerList<MapData<Key, Type>> &list) { copy(list); }
			Map(Map &&map) { tree.move((Tree&&)map.tree); }
			~Map() { }
			
			/// clear map
			TS_INLINE void clear() {
				tree.clear();
			}
			
			/// swap maps
			TS_INLINE void swap(Map &map) {
				tree.swap(map.tree);
			}
			
			/// copy map
			TS_INLINE void copy(const Map &map) {
				tree.copy(map.tree);
			}
			void copy(const InitializerList<MapData<Key, Type>> &list) {
				tree.clear();
				for(const auto &it : list) {
					tree.append(it);
				}
			}
			
			/// assignment operators
			TS_INLINE Map &operator=(const Map &map) {
				if(&map != this) tree.copy(map.tree);
				return *this;
			}
			TS_INLINE Map &operator=(Map &&map) {
				tree.move((Tree&&)map.tree);
				return *this;
			}
			TS_INLINE Map &operator=(const InitializerList<MapData<Key, Type>> &list) {
				copy(list);
				return *this;
			}
			
			/// append value
			TS_INLINE Iterator append(const Key &key) {
				return tree.append(MapData<Key, Type>(key, Type()));
			}
			TS_INLINE Iterator append(const Key &key, const Type &data) {
				return tree.append(MapData<Key, Type>(key, data));
			}
			template <class C> void append(const Map<Key, Type, C> &map) {
				for(const auto &it : map) {
					tree.append(it);
				}
			}
			
			/// remove value
			template <class K> TS_INLINE bool remove(const K &key) {
				return tree.remove(key);
			}
			TS_INLINE bool remove(const Iterator &it) {
				return tree.remove(it);
			}
			TS_INLINE bool remove(const ConstIterator &it) {
				return tree.remove(it);
			}
			
			/// map info
			TS_INLINE bool empty() const { return tree.empty(); }
			explicit TS_INLINE operator bool() const { return (bool)tree; }
			TS_INLINE size_t memory() const { return tree.memory(); }
			TS_INLINE uint32_t size() const { return tree.size(); }
			
			/// map data
			template <class K> TS_INLINE Iterator find(const K &key) {
				return tree.find(key);
			}
			template <class K> TS_INLINE ConstIterator find(const K &key) const {
				return tree.find(key);
			}
			template <class K> TS_INLINE const Type &operator[](const K &key) const {
				ConstIterator it = tree.find(key);
				TS_ASSERT(it && "Map::operator[](): invalid key");
				return it->data;
			}
			template <class K> TS_INLINE Type &operator[](const K &key) {
				Iterator it = tree.find(key);
				TS_ASSERT(it && "Map::operator[](): invalid key");
				return it->data;
			}
			template <class K> TS_INLINE const Type &get(const K &key) const {
				ConstIterator it = tree.find(key);
				TS_ASSERT(it && "Map::get(): invalid key");
				return it->data;
			}
			template <class K> TS_INLINE Type &get(const K &key) {
				Iterator it = tree.find(key);
				TS_ASSERT(it && "Map::get(): invalid key");
				return it->data;
			}
			
			template <class D> bool checkData(const D &data) {
				for(auto it = tree.begin(); it; ++it) {
					if(it->data == data) return true;
				}
				return false;
			}
			template <class D> Iterator findData(const D &data) {
				for(auto it = tree.begin(); it; ++it) {
					if(it->data == data) return it;
				}
				return tree.end();
			}
			template <class D> ConstIterator findData(const D &data) const {
				for(auto it = tree.begin(); it; ++it) {
					if(it->data == data) return it;
				}
				return tree.end();
			}
			
			/// map range
			template <class K> TS_INLINE Iterator prev(const K &key) {
				return tree.prev(key);
			}
			template <class K> TS_INLINE Iterator next(const K &key) {
				return tree.next(key);
			}
			template <class K> TS_INLINE ConstIterator prev(const K &key) const {
				return tree.prev(key);
			}
			template <class K> TS_INLINE ConstIterator next(const K &key) const {
				return tree.next(key);
			}
			
			/// map iterators
			TS_INLINE Iterator root() { return tree.root(); }
			TS_INLINE Iterator begin() { return tree.begin(); }
			TS_INLINE Iterator back() { return tree.back(); }
			TS_INLINE Iterator end() { return tree.end(); }
			TS_INLINE ConstIterator root() const { return tree.root(); }
			TS_INLINE ConstIterator begin() const { return tree.begin(); }
			TS_INLINE ConstIterator back() const { return tree.back(); }
			TS_INLINE ConstIterator end() const { return tree.end(); }
			
		private:
			
			Tree tree;		// map implementation
	};
	
	/**
	 * Swap maps
	 */
	template <class Key, class Type, class Compare> void swap(Map<Key, Type, Compare> &m0, Map<Key, Type, Compare> &m1) {
		m0.swap(m1);
	}
}

#endif /* __TELLUSIM_CORE_MAP_H__ */

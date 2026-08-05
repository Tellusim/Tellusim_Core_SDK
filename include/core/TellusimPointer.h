// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_POINTER_H__
#define __TELLUSIM_CORE_POINTER_H__

#include <TellusimBase.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Default destructor
	 */
	template <class Type> struct DefaultDestructor {
		
		/// delete pointer
		static void destructor(Type *ptr) {
			delete ptr;
		}
	};
	
	/**
	 * Auto pointer
	 */
	template <class Type, class Destructor = DefaultDestructor<Type>> class AutoPtr {
			
		public:
			
			/// constructors
			AutoPtr() : ptr(nullptr) { }
			template <class T> explicit AutoPtr(T *ptr) : ptr(ptr) { }
			AutoPtr(const AutoPtr &p) : ptr(p.ptr) { p.ptr = nullptr; }
			~AutoPtr() { clear(); }
			
			/// clear pointer
			TS_INLINE void clear() {
				Destructor::destructor(ptr);
				ptr = nullptr;
			}
			
			/// release pointer
			TS_INLINE Type *release() {
				Type *ret = ptr;
				ptr = nullptr;
				return ret;
			}
			
			/// create pointer
			TS_INLINE Type **create() {
				clear();
				return &ptr;
			}
			
			/// assignment operator
			AutoPtr<Type, Destructor> &operator=(const AutoPtr &p) {
				if(ptr == p.ptr) return *this;
				clear();
				ptr = p.ptr;
				p.ptr = nullptr;
				return *this;
			}
			
			/// compare functions
			TS_INLINE bool operator==(const AutoPtr &p) const { return (ptr == p.ptr); }
			TS_INLINE bool operator!=(const AutoPtr &p) const { return (ptr != p.ptr); }
			TS_INLINE bool operator==(const Type *p) const { return (ptr == p); }
			TS_INLINE bool operator!=(const Type *p) const { return (ptr != p); }
			
			TS_INLINE bool operator<(const AutoPtr &p) const { return (ptr < p.ptr); }
			TS_INLINE bool operator>(const AutoPtr &p) const { return (ptr > p.ptr); }
			TS_INLINE bool operator<(const Type *p) const { return (ptr < p); }
			TS_INLINE bool operator>(const Type *p) const { return (ptr > p); }
			
			/// access operators
			TS_INLINE Type &operator*() const {
				TS_ASSERT(!empty() && "AutoPtr::operator*(): pointer is null");
				return *ptr;
			}
			TS_INLINE Type *operator->() const {
				TS_ASSERT(!empty() && "AutoPtr::operator->(): pointer is null");
				return ptr;
			}
			
			/// get pointer
			TS_INLINE bool empty() const { return (ptr == nullptr); }
			explicit TS_INLINE operator bool() const { return (ptr != nullptr); }
			TS_INLINE const Type &ref() const { TS_ASSERT(!empty() && "AutoPtr::ref(): pointer is null"); return *ptr; }
			TS_INLINE Type &ref() { TS_ASSERT(!empty() && "AutoPtr::ref(): pointer is null"); return *ptr; }
			TS_INLINE const Type *get() const { return ptr; }
			TS_INLINE Type *get() { return ptr; }
			
		private:
			
			mutable Type *ptr;
	};
	
	/**
	 * Smart pointer
	 */
	template <class Type, class Destructor = DefaultDestructor<Type>> class SmartPtr {
			
		public:
			
			/// constructors
			SmartPtr() : ptr(nullptr), counter(nullptr) { }
			template <class T> explicit SmartPtr(T *ptr) : ptr(ptr), counter(nullptr) { retain(); }
			SmartPtr(const SmartPtr &p) : ptr(p.ptr), counter(p.counter) { retain(); }
			~SmartPtr() { release(); }
			
			/// clear pointer
			TS_INLINE void clear() {
				release();
				ptr = nullptr;
				counter = nullptr;
			}
			
			/// destroy pointer
			void destroy() {
				release();
				if(counter && !(*counter & (uint32_t)DestroyBit)) {
					Destructor::destructor(ptr);
					*counter |= (uint32_t)DestroyBit;
				}
				ptr = nullptr;
				counter = nullptr;
			}
			
			/// create pointer
			TS_INLINE Type **create() {
				clear();
				counter = new uint32_t(1);
				return &ptr;
			}
			
			/// assignment operator
			SmartPtr<Type, Destructor> &operator=(const SmartPtr &p) {
				if(ptr == p.ptr) return *this;
				release();
				ptr = p.ptr;
				counter = p.counter;
				retain();
				return *this;
			}
			
			/// compare functions
			TS_INLINE bool operator==(const SmartPtr &p) const { return (ptr == p.ptr && counter == p.counter); }
			TS_INLINE bool operator!=(const SmartPtr &p) const { return (ptr != p.ptr || counter != p.counter); }
			TS_INLINE bool operator==(const Type *p) const { return (ptr == p); }
			TS_INLINE bool operator!=(const Type *p) const { return (ptr != p); }
			
			TS_INLINE bool operator<(const SmartPtr &p) const { return (ptr < p.ptr); }
			TS_INLINE bool operator>(const SmartPtr &p) const { return (ptr > p.ptr); }
			TS_INLINE bool operator<(const Type *p) const { return (ptr < p); }
			TS_INLINE bool operator>(const Type *p) const { return (ptr > p); }
			
			/// access operators
			TS_INLINE Type &operator*() const {
				TS_ASSERT(!empty() && "SmartPtr::operator*(): pointer is null");
				return *ptr;
			}
			TS_INLINE Type *operator->() const {
				TS_ASSERT(!empty() && "SmartPtr::operator->(): pointer is null");
				return ptr;
			}
			
			/// get pointer
			TS_INLINE bool empty() const { return (ptr == nullptr || (*counter & (uint32_t)DestroyBit)); }
			TS_INLINE uint32_t count() const { if(counter) return (*counter & CounterMask); return 0; }
			explicit TS_INLINE operator bool() const { return (ptr != nullptr && !(*counter & (uint32_t)DestroyBit)); }
			TS_INLINE const Type &ref() const { TS_ASSERT(!empty() && "SmartPtr::ref(): pointer is null"); return *ptr; }
			TS_INLINE Type &ref() { TS_ASSERT(!empty() && "SmartPtr::ref(): pointer is null"); return *ptr; }
			TS_INLINE const Type *get() const { if(counter && (*counter & (uint32_t)DestroyBit)) return nullptr; return ptr; }
			TS_INLINE Type *get() { if(counter && (*counter & (uint32_t)DestroyBit)) return nullptr; return ptr; }
			
		private:
			
			enum {
				DestroyBit = (int32_t)(1u << (sizeof(uint32_t) * 8u - 1u)),
				CounterMask = ~DestroyBit,
			};
			
			/// retain pointer
			void retain() {
				if(ptr) {
					if(counter) (*counter) += 1;
					else counter = new uint32_t(1);
				}
			}
			
			/// release pointer
			void release() {
				if(counter) {
					TS_ASSERT((*counter & CounterMask) && "SmartPtr::release(): counter underflow");
					if((((*counter) -= 1) & CounterMask) == 0) {
						if(!(*counter & (uint32_t)DestroyBit)) Destructor::destructor(ptr);
						ptr = nullptr;
						delete counter;
						counter = nullptr;
					}
				}
			}
			
			mutable Type *ptr;
			volatile uint32_t *counter;
	};
	
	/**
	 * Make functions
	 */
	template <class Type, class Destructor = DefaultDestructor<Type>> AutoPtr<Type, Destructor> makeAutoPtr(Type *ptr) {
		return AutoPtr<Type, Destructor>(ptr);
	}
	
	template <class Type, class Destructor = DefaultDestructor<Type>> SmartPtr<Type, Destructor> makeSmartPtr(Type *ptr) {
		return SmartPtr<Type, Destructor>(ptr);
	}
	
	/*
	 */
	#if _WIN32
		
		/**
		 * Com destructor
		 */
		template <class Type> struct ReleaseDestructor {
			
			/// release pointer
			static void destructor(Type *ptr) {
				if(ptr) ptr->Release();
			}
		};
		
		/**
		 * Com pointers
		 */
		template <class Type> using AutoComPtr = AutoPtr<Type, ReleaseDestructor<Type>>;
		template <class Type> using SmartComPtr = SmartPtr<Type, ReleaseDestructor<Type>>;
		
		/**
		 * Make functions
		 */
		template <class Type> AutoComPtr<Type> makeAutoComPtr(Type *ptr) {
			return AutoComPtr<Type>(ptr);
		}
		
		template <class Type> SmartComPtr<Type> makeSmartComPtr(Type *ptr) {
			return SmartComPtr<Type>(ptr);
		}
		
	#endif
}

#endif /* __TELLUSIM_CORE_POINTER_H__ */

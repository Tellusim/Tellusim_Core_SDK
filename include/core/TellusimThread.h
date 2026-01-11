// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_THREAD_H__
#define __TELLUSIM_CORE_THREAD_H__

#include <TellusimBase.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Hardware thread
	 */
	class TS_API Thread {
			
			TS_DECLARE_NONCOPY(Thread, 21)
			
		public:
			
			Thread();
			
			/// run the thread
			bool run(uint32_t stack = 1024 * 1024);
			
			/// stop the thread
			bool stop(bool wait = false);
			
			/// wait for the signal
			bool wait();
			
			/// wake up the thread
			bool signal();
			
			/// terminate the thread
			bool terminate();
			
			/// thread status
			bool isRunning() const;
			bool isStopped() const;
			bool isWaiting() const;
			
		protected:
			
			/// thread process
			virtual void process();
	};
	
	/**
	 * Thread function
	 */
	template <class Func> class ThreadFunction0 : public Thread {
		public:
			ThreadFunction0(const Func &func) : func(func) { }
		protected:
			virtual void process() { while(isRunning()) func(this); }
			Func func;
	};
	
	template <class Func, class A0> class ThreadFunction1 : public Thread {
		public:
			ThreadFunction1(const Func &func, A0 a0) : func(func), a0(a0) { }
		protected:
			virtual void process() { while(isRunning()) func(this, a0); }
			Func func;
			A0 a0;
	};
	
	template <class Func, class A0, class A1> class ThreadFunction2 : public Thread {
		public:
			ThreadFunction2(const Func &func, A0 a0, A1 a1) : func(func), a0(a0), a1(a1) { }
		protected:
			virtual void process() { while(isRunning()) func(this, a0, a1); }
			Func func;
			A0 a0;
			A1 a1;
	};
	
	template <class Func, class A0, class A1, class A2> class ThreadFunction3 : public Thread {
		public:
			ThreadFunction3(const Func &func, A0 a0, A1 a1, A2 a2) : func(func), a0(a0), a1(a1), a2(a2) { }
		protected:
			virtual void process() { while(isRunning()) func(this, a0, a1, a2); }
			Func func;
			A0 a0;
			A1 a1;
			A2 a2;
	};
	
	template <class Func, class A0, class A1, class A2, class A3> class ThreadFunction4 : public Thread {
		public:
			ThreadFunction4(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3) : func(func), a0(a0), a1(a1), a2(a2), a3(a3) { }
		protected:
			virtual void process() { while(isRunning()) func(this, a0, a1, a2, a3); }
			Func func;
			A0 a0;
			A1 a1;
			A2 a2;
			A3 a3;
	};
	
	/**
	 * Make thread function
	 */
	template <class Func> Thread *makeThreadFunction(const Func &func) {
		return new ThreadFunction0<Func>(func);
	}
	
	template <class Func, class A0> Thread *makeThreadFunction(const Func &func, A0 a0) {
		return new ThreadFunction1<Func, A0>(func, a0);
	}
	
	template <class Func, class A0, class A1> Thread *makeThreadFunction(const Func &func, A0 a0, A1 a1) {
		return new ThreadFunction2<Func, A0, A1>(func, a0, a1);
	}
	
	template <class Func, class A0, class A1, class A2> Thread *makeThreadFunction(const Func &func, A0 a0, A1 a1, A2 a2) {
		return new ThreadFunction3<Func, A0, A1, A2>(func, a0, a1, a2);
	}
	
	template <class Func, class A0, class A1, class A2, class A3> Thread *makeThreadFunction(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3) {
		return new ThreadFunction4<Func, A0, A1, A2, A3>(func, a0, a1, a2, a3);
	}
	
	/**
	 * Thread class member function
	 */
	template <class Class, class Func> class ThreadClassFunction0 : public Thread {
		public:
			ThreadClassFunction0(Class *c, const Func &func) : c(c), func(func) { }
		protected:
			virtual void process() { while(isRunning()) (c->*func)(this); }
			Class *c;
			Func func;
	};
	
	template <class Class, class Func, class A0> class ThreadClassFunction1 : public Thread {
		public:
			ThreadClassFunction1(Class *c, const Func &func, A0 a0) : c(c), func(func), a0(a0) { }
		protected:
			virtual void process() { while(isRunning()) (c->*func)(this, a0); }
			Class *c;
			Func func;
			A0 a0;
	};
	
	template <class Class, class Func, class A0, class A1> class ThreadClassFunction2 : public Thread {
		public:
			ThreadClassFunction2(Class *c, const Func &func, A0 a0, A1 a1) : c(c), func(func), a0(a0), a1(a1) { }
		protected:
			virtual void process() { while(isRunning()) (c->*func)(this, a0, a1); }
			Class *c;
			Func func;
			A0 a0;
			A1 a1;
	};
	
	template <class Class, class Func, class A0, class A1, class A2> class ThreadClassFunction3 : public Thread {
		public:
			ThreadClassFunction3(Class *c, const Func &func, A0 a0, A1 a1, A2 a2) : c(c), func(func), a0(a0), a1(a1), a2(a2) { }
		protected:
			virtual void process() { while(isRunning()) (c->*func)(this, a0, a1, a2); }
			Class *c;
			Func func;
			A0 a0;
			A1 a1;
			A2 a2;
	};
	
	template <class Class, class Func, class A0, class A1, class A2, class A3> class ThreadClassFunction4 : public Thread {
		public:
			ThreadClassFunction4(Class *c, const Func &func, A0 a0, A1 a1, A2 a2, A3 a3) : c(c), func(func), a0(a0), a1(a1), a2(a2), a3(a3) { }
		protected:
			virtual void process() { while(isRunning()) (c->*func)(this, a0, a1, a2, a3); }
			Class *c;
			Func func;
			A0 a0;
			A1 a1;
			A2 a2;
			A3 a3;
	};
	
	/**
	 * Make thread class member function
	 */
	template <class Class, class Func> Thread *makeThreadClassFunction(Class *c, const Func &func) {
		return new ThreadClassFunction0<Class, Func>(c, func);
	}
	
	template <class Class, class Func, class A0> Thread *makeThreadClassFunction(Class *c, const Func &func, A0 a0) {
		return new ThreadClassFunction1<Class, Func, A0>(c, func, a0);
	}
	
	template <class Class, class Func, class A0, class A1> Thread *makeThreadClassFunction(Class *c, const Func &func, A0 a0, A1 a1) {
		return new ThreadClassFunction2<Class, Func, A0, A1>(c, func, a0, a1);
	}
	
	template <class Class, class Func, class A0, class A1, class A2> Thread *makeThreadClassFunction(Class *c, const Func &func, A0 a0, A1 a1, A2 a2) {
		return new ThreadClassFunction3<Class, Func, A0, A1, A2>(c, func, a0, a1, a2);
	}
	
	template <class Class, class Func, class A0, class A1, class A2, class A3> Thread *makeThreadClassFunction(Class *c, const Func &func, A0 a0, A1 a1, A2 a2, A3 a3) {
		return new ThreadClassFunction4<Class, Func, A0, A1, A2, A3>(c, func, a0, a1, a2, a3);
	}
}

#endif /* __TELLUSIM_CORE_THREAD_H__ */

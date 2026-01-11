// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_ASYNC_H__
#define __TELLUSIM_CORE_ASYNC_H__

#include <core/TellusimArray.h>
#include <core/TellusimFunction.h>

/*
 */
namespace Tellusim {
	
	/**
	 * Async function return type
	 */
	template <class Type> struct AsyncFunctionRet {
		using Ret = Type;
	};
	template <class Type> struct AsyncFunctionRet<Type&> {
		using Ret = Type;
	};
	template <class Type> struct AsyncFunctionRet<const Type&> {
		using Ret = Type;
	};
	template <> struct AsyncFunctionRet<void> {
		using Ret = void*;
	};
	
	/**
	 * Async function base class
	 */
	class AsyncFunctionBase {
			
		public:
			
			virtual ~AsyncFunctionBase() { }
			
			/// run function
			virtual void run() = 0;
			
			/// function result
			virtual void *get() = 0;
			
			/// release function pointer
			static void release(AsyncFunctionBase *func) {
				delete func;
			}
	};
	
	/**
	 * Async function template
	 */
	template <class Func> class AsyncFunction final : public AsyncFunctionBase {
			
		public:
			
			AsyncFunction(const Func &func) : func(func) { }
			virtual ~AsyncFunction() { }
			
			/// function return type
			using Ret = typename Func::Ret;
			using Type = typename AsyncFunctionRet<Ret>::Ret;
			
			/// run function
			virtual void run() { do_run(TypeToType<Ret>()); }
			
			/// return value pointer
			virtual void *get() { return do_get(TypeToType<Ret>()); }
			
		private:
			
			void do_run(TypeToType<void>) { func.run(); }
			template <class Type> void do_run(Type) { ret = func.run(); }
			
			void *do_get(TypeToType<void>) { return nullptr; }
			template <class Type> void *do_get(TypeToType<Type>) { return &ret; }
			template <class Type> void *do_get(TypeToType<Type*>) { return ret; }
			template <class Type> void *do_get(TypeToType<const Type*>) { return (void*)ret; }
			
			Func func;			// function type
			Type ret;			// function result
	};
	
	template <class Func> AsyncFunctionBase *makeAsyncFunction(const Func &func) {
		return new AsyncFunction<Function<Func>>(Function<Func>(func));
	}
	template <class Func, class A0> AsyncFunctionBase *makeAsyncFunction(const Func &func, A0 a0) {
		return new AsyncFunction<Function<Func>>(Function<Func>(func, a0));
	}
	template <class Func, class A0, class A1> AsyncFunctionBase *makeAsyncFunction(const Func &func, A0 a0, A1 a1) {
		return new AsyncFunction<Function<Func>>(Function<Func>(func, a0, a1));
	}
	template <class Func, class A0, class A1, class A2> AsyncFunctionBase *makeAsyncFunction(const Func &func, A0 a0, A1 a1, A2 a2) {
		return new AsyncFunction<Function<Func>>(Function<Func>(func, a0, a1, a2));
	}
	template <class Func, class A0, class A1, class A2, class A3> AsyncFunctionBase *makeAsyncFunction(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3) {
		return new AsyncFunction<Function<Func>>(Function<Func>(func, a0, a1, a2, a3));
	}
	template <class Func, class A0, class A1, class A2, class A3, class A4> AsyncFunctionBase *makeAsyncFunction(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) {
		return new AsyncFunction<Function<Func>>(Function<Func>(func, a0, a1, a2, a3, a4));
	}
	template <class Func, class A0, class A1, class A2, class A3, class A4, class A5> AsyncFunctionBase *makeAsyncFunction(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) {
		return new AsyncFunction<Function<Func>>(Function<Func>(func, a0, a1, a2, a3, a4, a5));
	}
	template <class Func, class A0, class A1, class A2, class A3, class A4, class A5, class A6> AsyncFunctionBase *makeAsyncFunction(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) {
		return new AsyncFunction<Function<Func>>(Function<Func>(func, a0, a1, a2, a3, a4, a5, a6));
	}
	template <class Func, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7> AsyncFunctionBase *makeAsyncFunction(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) {
		return new AsyncFunction<Function<Func>>(Function<Func>(func, a0, a1, a2, a3, a4, a5, a6, a7));
	}
	template <class Func> AsyncFunctionBase *makeAsyncFunction(const Function<Func> &func) {
		return new AsyncFunction<Function<Func>>(func);
	}
	
	/**
	 * The Async class in the Tellusim API is a high-performance, multithreaded task scheduler designed for executing functions asynchronously across multiple CPU threads.
	 * It allows developers to dispatch tasks-functions with or without return values-either immediately or with a specific CPU affinity mask, enabling fine-grained control over thread usage.
	 * Internally, tasks are encapsulated using the AsyncFunction system, which supports various function signatures and handles function invocation and result storage.
	 * The Async class includes an inner Task class that represents individual asynchronous jobs. These tasks can be queued, cleared, canceled, or monitored for completion, and they offer mechanisms for retrieving return values in a type-safe way.
	 * This architecture is particularly suited for real-time or compute-intensive applications, such as rendering or simulation engines, where efficient CPU utilization and concurrent task execution are critical.
	 */
	class TS_API Async {
			
			TS_DECLARE_PTR(Async, 0)
			
		public:
			
			/// Task
			class TS_API Task {
					
					TS_DECLARE_COPY(Task, 0)
					
				public:
					
					Task();
					
					/// comparison operators
					bool operator==(const Task &task) const;
					bool operator!=(const Task &task) const;
					
					/// task info
					bool empty() const;
					explicit TS_INLINE operator bool() const { return !empty(); }
					
					/// clear functions queue
					void clear();
					
					/// cancel functions queue
					void cancel();
					
					/// queue thread index
					uint32_t index();
					
					/// number of queued functions
					uint32_t size() const;
					
					/// run the function on the queue
					template <class Func> TS_INLINE Task &run(const Func &func) {
						run(makeAsyncFunction(func));
						return *this;
					}
					template <class Func, class A0> TS_INLINE Task &run(const Func &func, A0 a0) {
						run(makeAsyncFunction(func, a0));
						return *this;
					}
					template <class Func, class A0, class A1> TS_INLINE Task &run(const Func &func, A0 a0, A1 a1) {
						run(makeAsyncFunction(func, a0, a1));
						return *this;
					}
					template <class Func, class A0, class A1, class A2> TS_INLINE Task &run(const Func &func, A0 a0, A1 a1, A2 a2) {
						run(makeAsyncFunction(func, a0, a1, a2));
						return *this;
					}
					template <class Func, class A0, class A1, class A2, class A3> TS_INLINE Task &run(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3) {
						run(makeAsyncFunction(func, a0, a1, a2, a3));
						return *this;
					}
					template <class Func, class A0, class A1, class A2, class A3, class A4> TS_INLINE Task &run(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) {
						run(makeAsyncFunction(func, a0, a1, a2, a3, a4));
						return *this;
					}
					template <class Func, class A0, class A1, class A2, class A3, class A4, class A5> TS_INLINE Task &run(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) {
						run(makeAsyncFunction(func, a0, a1, a2, a3, a4, a5));
						return *this;
					}
					template <class Func, class A0, class A1, class A2, class A3, class A4, class A5, class A6> TS_INLINE Task &run(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) {
						run(makeAsyncFunction(func, a0, a1, a2, a3, a4, a5, a6));
						return *this;
					}
					template <class Func, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7> TS_INLINE Task &run(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) {
						run(makeAsyncFunction(func, a0, a1, a2, a3, a4, a5, a6, a7));
						return *this;
					}
					template <class Func> TS_INLINE Task &run(const Function<Func> &func) {
						run(makeAsyncFunction(func));
						return *this;
					}
					
					/// check task completion status
					bool check(uint32_t num = Maxu32) const;
					
					/// waiting for the task completion
					bool wait(uint32_t num = Maxu32) const;
					
					/// function result
					template <class Ret> TS_INLINE const Ret &get(uint32_t num = 0) const {
						return *static_cast<const Ret*>(get(num));
					}
					template <class Ret> TS_INLINE Ret getPtr(uint32_t num = 0) const {
						return static_cast<Ret>(get(num));
					}
					TS_INLINE bool getBool(uint32_t num = 0) const {
						return *static_cast<const bool*>(get(num));
					}
					
				private:
					
					friend class Async;
					
					Task(Async *async, uint64_t mask);
					Task(Async *async, AsyncFunctionBase *func, uint64_t mask);
					
					void run(AsyncFunctionBase *func);
					void *get(uint32_t num) const;
			};
			
			Async();
			
			/// initialize threads
			bool init(uint32_t num = 0);
			
			/// shutdown threads
			bool shutdown();
			
			/// check status
			bool isInitialized() const;
			
			/// number of threads
			static uint32_t getNumCores();
			uint32_t getNumThreads() const;
			
			/// temporary tasks
			void append(const Task &task);
			void clear();
			
			/// number of temporary tasks
			uint32_t getNumTasks(bool check = false) const;
			
			/// run function
			TS_INLINE Task run(uint32_t mask) {
				return Task(this, mask);
			}
			TS_INLINE Task run(uint64_t mask = ~0ull) {
				return Task(this, mask);
			}
			template <class Func> TS_INLINE Task run(const Func &func, uint64_t mask = ~0ull) {
				return Task(this, makeAsyncFunction(func), mask);
			}
			template <class Func, class A0> TS_INLINE Task run(const Func &func, A0 a0, uint64_t mask = ~0ull) {
				return Task(this, makeAsyncFunction(func, a0), mask);
			}
			template <class Func, class A0, class A1> TS_INLINE Task run(const Func &func, A0 a0, A1 a1, uint64_t mask = ~0ull) {
				return Task(this, makeAsyncFunction(func, a0, a1), mask);
			}
			template <class Func, class A0, class A1, class A2> TS_INLINE Task run(const Func &func, A0 a0, A1 a1, A2 a2, uint64_t mask = ~0ull) {
				return Task(this, makeAsyncFunction(func, a0, a1, a2), mask);
			}
			template <class Func, class A0, class A1, class A2, class A3> TS_INLINE Task run(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, uint64_t mask = ~0ull) {
				return Task(this, makeAsyncFunction(func, a0, a1, a2, a3), mask);
			}
			template <class Func, class A0, class A1, class A2, class A3, class A4> TS_INLINE Task run(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, uint64_t mask = ~0ull) {
				return Task(this, makeAsyncFunction(func, a0, a1, a2, a3, a4), mask);
			}
			template <class Func, class A0, class A1, class A2, class A3, class A4, class A5> TS_INLINE Task run(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, uint64_t mask = ~0ull) {
				return Task(this, makeAsyncFunction(func, a0, a1, a2, a3, a4, a5), mask);
			}
			template <class Func, class A0, class A1, class A2, class A3, class A4, class A5, class A6> TS_INLINE Task run(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, uint64_t mask = ~0ull) {
				return Task(this, makeAsyncFunction(func, a0, a1, a2, a3, a4, a5, a6), mask);
			}
			template <class Func, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7> TS_INLINE Task run(const Func &func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, uint64_t mask = ~0ull) {
				return Task(this, makeAsyncFunction(func, a0, a1, a2, a3, a4, a5, a6, a7), mask);
			}
			template <class Func> TS_INLINE Task run(const Function<Func> &func, uint64_t mask = ~0ull) {
				return Task(this, makeAsyncFunction(func), mask);
			}
			
			/// check completion status
			bool check(const Task *tasks, uint32_t num) const;
			bool check(const Array<Task> &tasks) const;
			bool check() const;
			
			/// waiting for the completion
			bool wait(const Task *tasks, uint32_t num) const;
			bool wait(const Array<Task> &tasks) const;
			bool wait() const;
	};
}

#endif /* __TELLUSIM_CORE_ASYNC_H__ */

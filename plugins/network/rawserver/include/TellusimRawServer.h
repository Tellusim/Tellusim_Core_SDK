// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_NETWORK_RAW_SERVER_H__
#define __TELLUSIM_PLUGINS_NETWORK_RAW_SERVER_H__

#include <core/TellusimBlob.h>
#include <core/TellusimArray.h>
#include <core/TellusimSocket.h>
#include <core/TellusimThread.h>
#include <core/TellusimPointer.h>

/*
 */
namespace Tellusim {
	
	/**
	 * RawSession
	 */
	class RawSession {
			
		public:
			
			/// session constructor
			explicit RawSession(Socket &socket);
			virtual ~RawSession();
			
			/// disable copying
			RawSession(const RawSession&) = delete;
			RawSession &operator=(const RawSession&) = delete;
			
			/// session socket
			TS_INLINE Socket &getSocket() { return socket; }
			TS_INLINE const Socket &getSocket() const { return socket; }
			TS_INLINE uint16_t getPort() const { return socket.getPort(); }
			TS_INLINE int32_t getFD() const { return socket.getFD(); }
			
			/// session timeout
			void setTimeout(uint32_t timeout);
			TS_INLINE uint32_t getTimeout() const { return timeout; }
			
			/// write data size
			virtual uint32_t getWriteSize() const;
			
			/// read session data
			virtual bool read() = 0;
			
			/// write session data
			virtual bool write();
			
		protected:
			
			Socket socket;				// session socket
			
			uint32_t timeout = 8;		// timeout in seconds
	};
	
	/**
	 * RawServer
	 */
	class RawServer {
			
		public:
			
			/// server constructor
			RawServer();
			virtual ~RawServer();
			
			/// disable copying
			RawServer(const RawServer&) = delete;
			RawServer &operator=(const RawServer&) = delete;
			
			/// server socket
			TS_INLINE Socket &getSocket() { return socket; }
			TS_INLINE const Socket &getSocket() const { return socket; }
			TS_INLINE uint16_t getPort() const { return socket.getPort(); }
			TS_INLINE int32_t getFD() const { return socket.getFD(); }
			
			/// server timeout
			void setTimeout(uint32_t timeout);
			TS_INLINE uint32_t getTimeout() const { return timeout; }
			
			/// server status
			TS_INLINE bool isRunning() const { return is_running; }
			
			/// initialize server
			virtual bool init(uint16_t port, uint16_t num = 32);
			
			/// run the server
			virtual bool run();
			
			/// stop the server
			virtual void stop();
			
		private:
			
			/// create session instance
			virtual RawSession *create_session(Socket &socket) = 0;
			
			/// process session
			void session_process(Thread *thread, RawSession *session);
			
			Socket socket;							// server socket
			
			uint32_t timeout = 8;					// timeout in seconds
			
			volatile bool is_running = false;		// server is running
			
			Array<AutoPtr<Thread>> threads;			// session threads
			Array<AutoPtr<RawSession>> sessions;	// session pointers
	};
}

#endif /* __TELLUSIM_PLUGINS_NETWORK_RAW_SERVER_H__ */

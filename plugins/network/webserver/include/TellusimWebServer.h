// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_NETWORK_WEB_SERVER_H__
#define __TELLUSIM_PLUGINS_NETWORK_WEB_SERVER_H__

#include <core/TellusimBlob.h>
#include <core/TellusimArray.h>
#include <core/TellusimSocket.h>
#include <core/TellusimThread.h>
#include <core/TellusimPointer.h>

/*
 */
namespace Tellusim {
	
	/**
	 * WebSession
	 */
	class WebSession {
			
		public:
			
			/// session constructor
			explicit WebSession(Socket &socket);
			virtual ~WebSession();
			
			/// disable copying
			WebSession(const WebSession&) = delete;
			WebSession &operator=(const WebSession&) = delete;
			
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
			
			struct Request;
			
			/// read request
			bool read_request(Request &request);
			
			/// request filename
			static String get_filename(const Request &request);
			
			/// websocket handshake
			static String get_handshake(const Request &request);
			
			/// read/write websocket
			bool read_socket(Blob &blob);
			static bool write_socket(Stream &dest, const Blob &blob, bool binary);
			
			struct Request {
				String url;						// request url
				String cookie;					// request cookie
				String browser;					// request browser
				String address;					// request address
				String upgrade;					// request upgrade
				String websocket;				// request websocket
				String connection;				// request connection
				String parameters;				// request parameters
				uint32_t begin = Maxu32;		// range begin
				uint32_t end = Maxu32;			// range end
			};
			
			Socket socket;						// session socket
			
			uint32_t timeout = 8;				// timeout in seconds
	};
	
	/**
	 * WebServer
	 */
	class WebServer {
			
		public:
			
			/// server constructor
			WebServer();
			virtual ~WebServer();
			
			/// disable copying
			WebServer(const WebServer&) = delete;
			WebServer &operator=(const WebServer&) = delete;
			
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
			virtual WebSession *create_session(Socket &socket) = 0;
			
			/// process session
			void session_process(Thread *thread, WebSession *session);
			
			Socket socket;							// server socket
			
			uint32_t timeout = 8;					// timeout in seconds
			
			volatile bool is_running = false;		// server is running
			
			Array<AutoPtr<Thread>> threads;			// session threads
			Array<AutoPtr<WebSession>> sessions;	// session pointers
	};
}

#endif /* __TELLUSIM_PLUGINS_NETWORK_WEB_SERVER_H__ */

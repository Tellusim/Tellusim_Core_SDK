// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_CORE_SOCKET_H__
#define __TELLUSIM_CORE_SOCKET_H__

#include <core/TellusimStream.h>

/*
 */
namespace Tellusim {
	
	/**
	 * The Socket class extends the Stream class and provides an abstraction for working with network sockets, supporting both stream and datagram socket types.
	 * It offers functionality for opening and closing sockets, connecting to remote addresses, and accepting incoming connections.
	 * The class supports socket-specific operations such as selecting sockets for activity, setting timeouts, and configuring blocking and delay behaviors.
	 */
	class TS_API Socket : public Stream {
			
			TS_DECLARE_PTR_0(Socket, 2)
			
		public:
			
			/// Socket type
			enum Type {
				TypeStream = 0,
				TypeDatagram,
				NumTypes,
			};
			
			explicit Socket(Type type = TypeStream);
			
			/// open/close socket
			bool open(uint16_t port, uint16_t num = 32);
			bool open(const char *name, uint16_t port);
			bool open(const String &name, uint16_t port);
			void close();
			
			/// stream socket
			bool connect(uint32_t sec, uint32_t usec = 0);
			virtual bool accept(Socket &socket);
			
			/// socket operations
			bool select(uint32_t sec, uint32_t usec = 0);
			
			/// socket timeout
			bool setTimeout(uint32_t sec);
			uint32_t getTimeout() const;
			
			/// socket blocking
			bool setBlock(bool block);
			bool getBlock() const;
			
			/// sockey delay
			bool setDelay(bool delay);
			bool getDelay() const;
			
			/// socket parameters
			void setName(const char *name);
			void setName(const String &name);
			uint16_t getPort() const;
			int32_t getFD() const;
			Type getType() const;
			
			/// socket utils
			/// \param delimiter A literal delimiter between multiple addresses. The first address is returned if not provided.
			static String getAddress(const char *delimiter = nullptr);
	};
	
	/**
	 * The SocketSSL class extends the Socket class and provides additional functionality for handling secure SSL/TLS connections.
	 * It offers methods for performing the SSL handshake, which establishes a secure connection, as well as accepting SSL-based socket connections.
	 * The class includes capabilities for loading SSL certificates from streams or file names, enabling secure communication through encryption.
	 */
	class TS_API SocketSSL : public Socket {
			
			TS_DECLARE_PTR_1(SocketSSL, Socket, 0)
			
		public:
			
			SocketSSL();
			
			/// stream socket
			bool handshake(const char *name = nullptr);
			virtual bool accept(SocketSSL &socket);
			virtual bool accept(Socket &socket);
			
			/// socket certificate
			bool load(Stream &stream);
			bool load(const char *name);
			bool load(const String &name);
			
			/// socket status
			bool isConnected() const;
	};
}

#endif /* __TELLUSIM_CORE_SOCKET_H__ */

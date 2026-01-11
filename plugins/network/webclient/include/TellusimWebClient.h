// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_NETWORK_WEB_CLIENT_H__
#define __TELLUSIM_PLUGINS_NETWORK_WEB_CLIENT_H__

#include <core/TellusimSocket.h>
#include <core/TellusimFunction.h>

/*
 */
namespace Tellusim {
	
	/**
	 * WebClient
	 */
	class WebClient {
			
		public:
			
			/// client constructor
			WebClient();
			explicit WebClient(Socket &socket);
			~WebClient();
			
			/// disable copying
			WebClient(const WebClient&) = delete;
			WebClient &operator=(const WebClient&) = delete;
			
			/// close client
			void close();
			
			/// client socket
			void setSocket(Socket &socket);
			TS_INLINE Socket &getSocket() { return socket; }
			TS_INLINE const Socket &getSocket() const { return socket; }
			
			/// client timeout
			void setTimeout(uint32_t timeout);
			TS_INLINE uint32_t getTimeout() const { return timeout; }
			
			/// client name
			void setName(const char *name);
			TS_INLINE const String &getName() const { return name; }
			
			/// client proxy
			void setProxy(const String &name, uint32_t port);
			TS_INLINE const String &getProxyName() const { return proxy_name; }
			TS_INLINE uint32_t getProxyPort() const { return proxy_port; }
			
			/// load certificate
			bool load(Stream &stream);
			bool load(const char *name);
			
			/// connect client
			bool open(const String &url, uint32_t port = Maxu32);
			bool connect(const String &url, uint32_t port = Maxu32);
			bool handshake(const char *name = nullptr);
			
			/// server address
			TS_INLINE bool isOpened() const { return socket.isOpened(); }
			TS_INLINE bool isConnected() const { return (bool)host; }
			TS_INLINE const String &getHost() const { return host; }
			TS_INLINE uint32_t getPort() const { return port; }
			
			/// client requests
			bool get(const String &url, const String &header = String::null);
			bool post(const String &url, const String &data, const String &header = String::null);
			
			/// server response
			TS_INLINE const String &getResponse() const { return response; }
			TS_INLINE uint32_t getOffset() const { return offset; }
			TS_INLINE size_t getSize() const { return size; }
			
			/// response code
			const char *getCodeName() const;
			TS_INLINE uint32_t getCode() const { return code; }
			TS_INLINE uint32_t getContent() const { return content; }
			TS_INLINE uint32_t getTransfer() const { return transfer; }
			
			/// read response data
			using ReadCallback = Function<bool(size_t offset, size_t size, size_t speed)>;
			bool read(Stream &stream, const ReadCallback &func, size_t block = 0);
			bool read(Stream &stream);
			
			enum Content {
				ContentUnknown = 0,
				ContentDeflate,
			};
			
			enum Transfer {
				TransferUnknown = 0,
				TransferChunked,
			};
			
			enum Code {
				CodeUnknown = 0,
				CodeOk					= 200,
				CodeNoContent			= 204,
				CodeBadRequest			= 400,
				CodeUnauthorized		= 401,
				CodeForbidden			= 403,
				CodeNotFound			= 404,
				CodeRequestTimeout		= 408,
				CodeUpgradeRequired		= 426,
				CodeTooManyRequests		= 429,
				CodeInternalServerError	= 500,
				CodeNotImplemented		= 501,
				CodeBadGateway			= 502,
				CodeServiceUnavailable	= 503,
				CodeGetewayTimeout		= 504,
			};
			
		protected:
			
			enum {
				ProxyOk			= 0,
				ProxyVersion	= 5,
				ProxyNoAuth		= 0,
				ProxyIPV4		= 1,
				ProxyIPV6		= 4,
				ProxyName		= 3,
				ProxyConnect	= 1,
				ProxyBind		= 2,
				ProxyUDP		= 3,
			};
			
			/// socks5 proxy
			bool open_proxy(const String &name, uint32_t port);
			
			/// read response
			void clear_response();
			bool read_response();
			
			/// read chunked response
			bool read_chunked(Stream &stream);
			
			uint32_t timeout = 8;					// timeout in seconds
			
			Socket socket;							// client socket
			
			String name;							// client name
			
			String host;							// host name
			uint32_t port = 0;						// port number
			
			String response;						// server response
			uint32_t offset = Maxu32;				// response offset
			size_t size = MaxSize;					// response size
			
			Code code = CodeUnknown;				// response code
			Content content = ContentUnknown;		// response content
			Transfer transfer = TransferUnknown;	// response transfer
			
			String proxy_name;						// proxy host name
			uint32_t proxy_port = 0;				// proxy port number
	};
}

#endif /* __TELLUSIM_PLUGINS_NETWORK_WEB_CLIENT_H__ */

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <core/TellusimBlob.h>
#include <core/TellusimArray.h>
#include <core/TellusimEndian.h>
#include <math/TellusimScalar.h>
#include <format/TellusimParser.h>

#include "../include/TellusimWebClient.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	WebClient::WebClient() {
		
	}
	
	WebClient::WebClient(Socket &socket) : socket(socket) {
		
	}
	
	WebClient::~WebClient() {
		close();
	}
	
	/*
	 */
	void WebClient::close() {
		
		// close socket
		socket.clearPtr();
		socket = Socket();
		
		// host name
		host.clear();
		port = 0;
		
		// clear response
		clear_response();
	}
	
	void WebClient::clear_response() {
		
		// response data
		response.clear();
		offset = Maxu32;
		size = MaxSize;
		
		// response code
		code = CodeUnknown;
		content = ContentUnknown;
		transfer = TransferUnknown;
	}
	
	/*
	 */
	void WebClient::setSocket(Socket &s) {
		close();
		socket = s;
	}
	
	/*
	 */
	void WebClient::setTimeout(uint32_t t) {
		timeout = t;
	}
	
	/*
	 */
	void WebClient::setName(const char *n) {
		name = n;
	}
	
	/*
	 */
	void WebClient::setProxy(const String &n, uint32_t p) {
		proxy_name = n;
		proxy_port = p;
	}
	
	/*
	 */
	bool WebClient::load(Stream &stream) {
		if(socket) {
			SocketSSL socket_ssl = SocketSSL(socket);
			if(!socket_ssl || !socket_ssl.load(stream)) return false;
		} else {
			SocketSSL socket_ssl;
			if(!socket_ssl.load(stream)) return false;
			socket = socket_ssl;
		}
		return true;
	}
	
	bool WebClient::load(const char *name) {
		if(socket) {
			SocketSSL socket_ssl = SocketSSL(socket);
			if(!socket_ssl || !socket_ssl.load(name)) return false;
		} else {
			SocketSSL socket_ssl;
			if(!socket_ssl.load(name)) return false;
			socket = socket_ssl;
		}
		return true;
	}
	
	/*
	 */
	bool WebClient::open_proxy(const String &name, uint32_t port) {
		
		// create SSL socket
		if(!socket && port == 443) {
			SocketSSL socket_ssl;
			socket = socket_ssl;
		}
		
		// open proxy socket
		if(!socket.open(proxy_name, (uint16_t)proxy_port)) {
			TS_LOGF(Error, "WebClient::open_proxy(): can't open proxy socket to %s:%u\n", proxy_name.get(), proxy_port);
			return false;
		}
		
		// socket timeout
		if(!socket.setTimeout(getTimeout())) {
			TS_LOG(Error, "WebClient::open_proxy(): can't set socket timeout\n");
			return false;
		}
		// connect proxy socket
		if(!socket.connect(getTimeout())) {
			TS_LOGF(Error, "WebClient::open_proxy(): can't connect socket to %s:%u\n", proxy_name.get(), proxy_port);
			return false;
		}
		
		// proxy negotiation
		Array<uint8_t> request = { ProxyVersion, 1, ProxyNoAuth };
		if(socket.write(request.get(), request.bytes()) != request.bytes()) {
			TS_LOG(Error, "WebClient::open_proxy(): can't write proxy request\n");
			return false;
		}
		Array<uint8_t> response(2);
		if(socket.read(response.get(), response.bytes()) != response.bytes()) {
			TS_LOG(Error, "WebClient::open_proxy(): can't read proxy response\n");
			return false;
		}
		if(response[0] != ProxyVersion || response[1] != ProxyOk) {
			TS_LOGF(Error, "WebClient::open_proxy(): invalid proxy response %u %u\n", response[0], response[1]);
			return false;
		}
		
		// proxy connect command
		request = { ProxyVersion, ProxyConnect, 0, ProxyName, (uint8_t)host.size() };
		request.append((const uint8_t*)host.get(), host.size());
		request.append((port >> 8) & 0xff); request.append((port >> 0) & 0xff);
		if(socket.write(request.get(), request.bytes()) != request.bytes()) {
			TS_LOG(Error, "WebClient::open_proxy(): can't write proxy request\n");
			return false;
		}
		response.resize(4);
		if(socket.read(response.get(), response.bytes()) != response.bytes()) {
			TS_LOG(Error, "WebClient::open_proxy(): can't read proxy response\n");
			return false;
		}
		if(response[0] != ProxyVersion || response[1] != ProxyOk || response[2]) {
			TS_LOGF(Error, "WebClient::open_proxy(): can't open proxy %u %u %u %u\n", response[0], response[1], response[2], response[3]);
			return false;
		}
		if(response[3] == ProxyIPV4) {
			uint32_t address = bigEndian(socket.readu32());
			uint32_t port = bigEndian(socket.readu16());
			if(address && port) {
				const uint8_t *ipv4 = (const uint8_t*)&address;
				proxy_name = String::format("%u.%u.%u.%u", ipv4[3], ipv4[2], ipv4[1], ipv4[0]);
				proxy_port = port;
			}
			socket.setName(name);
		} else {
			TS_LOGF(Error, "WebClient::open_proxy(): unknown address type %u\n", response[3]);
		}
		
		return true;
	}
	
	/*
	 */
	bool WebClient::open(const String &url, uint32_t p) {
		
		// protocol
		String protocol;
		uint32_t pos = url.find("://");
		if(pos != Maxu32) {
			protocol = url.substring(0, pos).lower();
			host = url.substring(pos + 3);
		} else {
			host = url;
		}
		port = p;
		
		// host name
		pos = host.find("/");
		if(pos != Maxu32) {
			host.resize(pos);
		}
		
		// port number
		pos = host.rfind(":");
		if(pos != Maxu32) {
			port = String::tou32(host.get() + pos + 1);
			host.resize(pos);
		}
		if(port == Maxu32) {
			if(protocol == "http") port = 80;
			else if(protocol == "https") port = 443;
			else {
				if(!protocol) TS_LOG(Error, "WebClient::open(): unknown protocol\n");
				else TS_LOGF(Error, "WebClient::open(): unknown protocol \"%s\"\n", protocol.get());
				close();
				return false;
			}
		}
		
		// open proxy
		if(getProxyName() && !open_proxy(host, port)) {
			TS_LOGF(Error, "WebClient::open(): can't open proxy to %s:%u\n", host.get(), port);
			close();
			return false;
		}
		
		// open socket
		if(!getProxyName() && !socket.open(host, (uint16_t)port)) {
			TS_LOGF(Error, "WebClient::open(): can't open socket to %s:%u\n", host.get(), port);
			close();
			return false;
		}
		
		return true;
	}
	
	bool WebClient::connect(const String &url, uint32_t port) {
		
		// open socket
		if(!socket.isOpened() && !open(url, port)) return false;
		
		// socket timeout
		if(!socket.setTimeout(getTimeout())) {
			TS_LOG(Error, "WebClient::connect(): can't set socket timeout\n");
			return false;
		}
		
		// connect socket
		if(!socket.connect(getTimeout())) {
			if(port != Maxu32) TS_LOGF(Error, "WebClient::connect(): can't connect socket to %s:%u\n", host.get(), port);
			else TS_LOGF(Error, "WebClient::connect(): can't connect socket to %s\n", host.get());
			return false;
		}
		
		return true;
	}
	
	bool WebClient::handshake(const char *name) {
		
		// check host
		if(!isConnected()) {
			TS_LOG(Error, "WebClient::get(): client is not connected\n");
			return false;
		}
		
		// SSL handshake
		if(socket) {
			SocketSSL socket_ssl = SocketSSL(socket);
			if(socket_ssl) return socket_ssl.handshake(name);
		}
		
		return false;
	}
	
	/*
	 */
	bool WebClient::get(const String &url, const String &header) {
		
		// check host
		if(!isConnected()) {
			TS_LOG(Error, "WebClient::get(): client is not connected\n");
			return false;
		}
		
		// parse url
		uint32_t offset = 0;
		uint32_t pos = url.find("://");
		if(pos != Maxu32) {
			offset = pos + 3;
			pos = url.find("/", offset);
			if(pos != Maxu32) offset = pos;
		}
		
		// get request
		String request;
		request += "GET "; request += (url.get() + offset); request += " HTTP/1.1\r\n";
		request += "Host: "; request += getHost(); request += "\r\n";
		if(getName()) request += String::format("User-Agent: %s\r\n", getName().get());
		request += "Accept-Encoding: gzip, deflate\r\n";
		request += "Connection: keep-alive\r\n";
		request += "Accept: text/html\r\n";
		if(header) request += header;
		request += "\r\n";
		
		// write request
		if(socket.write(request.get(), request.size()) != request.size()) {
			TS_LOG(Error, "WebClient::get(): can't write request\n");
			close();
			return false;
		}
		
		// wait for the answer
		if(!socket.select(getTimeout())) {
			TS_LOG(Error, "WebClient::get(): can't wait response\n");
			close();
			return false;
		}
		
		// read response
		if(!read_response()) {
			TS_LOG(Error, "WebClient::get(): can't read response\n");
			close();
			return false;
		}
		
		return true;
	}
	
	/*
	 */
	bool WebClient::post(const String &url, const String &data, const String &header) {
		
		// check address
		if(!isConnected()) {
			TS_LOG(Error, "WebClient::post(): client is not connected\n");
			return false;
		}
		
		// parse url
		uint32_t offset = 0;
		uint32_t pos = url.find("://");
		if(pos != Maxu32) {
			offset = pos + 3;
			pos = url.find("/", offset);
			if(pos != Maxu32) offset = pos;
		}
		
		// get request
		String request;
		request += "POST "; request += url; request += " HTTP/1.1\r\n";
		request += "Host: "; request += getHost(); request += "\r\n";
		if(getName()) request += String::format("User-Agent: %s\r\n", getName().get());
		request += "Content-Type: application/x-www-form-urlencoded\r\n";
		request += String::format("Content-Length: %u\r\n", data.size());
		request += "Connection: keep-alive\r\n";
		if(header) request += header;
		request += "\r\n";
		request += data;
		
		// write request
		if(socket.write(request.get(), request.size()) != request.size()) {
			TS_LOG(Error, "WebClient::post(): can't write request\n");
			close();
			return false;
		}
		
		// wait for the answer
		if(!socket.select(getTimeout())) {
			TS_LOG(Error, "WebClient::post(): can't wait response\n");
			close();
			return false;
		}
		
		// read response
		if(!read_response()) {
			TS_LOG(Error, "WebClient::post(): can't read response\n");
			close();
			return false;
		}
		
		return true;
	}
	
	/*
	 */
	bool WebClient::read_response() {
		
		// clear response
		clear_response();
		
		// get response
		response.resize(4);
		size_t s = socket.read(response.get(), response.size());
		if(s == 0) return false;
		
		// read response
		response.resize((uint32_t)(s + socket.getSize()));
		response.resize((uint32_t)(s + socket.read(response.get() + s, response.size() - s)));
		
		// parse response
		String line, token;
		const char *r = response.get();
		while(*r && r < response.get() + response.size()) {
			if(*r == '\n' && r[1] == '\r' && r[2] == '\n') {
				r += 3;
				break;
			}
			r += Parser::readLine(r, line);
			line = line.lower();
			const char *l = line.get();
			l += Parser::readToken(l, token);
			if(token == "http/1.1") code = (Code)String::tou32(l);
			else if(token == "content-length:") size = (size_t)String::tou64(l);
			else if(token == "content-encoding:") {
				Parser::readToken(l, token);
				if(token == "deflate") content = ContentDeflate;
				else if(token == "gzip") content = ContentDeflate;
			}
			else if(token == "transfer-encoding:") {
				Parser::readToken(l, token);
				if(token == "chunked") transfer = TransferChunked;
			}
		}
		if(code == CodeUnknown) return false;
		
		// data offset
		offset = (uint32_t)(r - response.get());
		
		return true;
	}
	
	/*
	 */
	bool WebClient::read_chunked(Stream &stream) {
		
		// check response
		if(getCode() != CodeOk) {
			TS_LOGF(Error, "WebClient::read_chunked(): invalid code %u%s\n", getCode(), getCodeName());
			close();
			return false;
		}
		if(getOffset() == Maxu32) {
			TS_LOG(Error, "WebClient::read_chunked(): invalid response\n");
			close();
			return false;
		}
		
		// response blob
		Blob response_blob;
		Stream *dest = &stream;
		if(getContent() == ContentDeflate) {
			dest = &response_blob;
		}
		
		// read response
		while(true) {
			
			// empty response
			if(!response || response.size() == getOffset()) {
				
				// get response
				response.resize(4);
				size_t s = socket.read(response.get(), response.size());
				if(s == 0) {
					TS_LOG(Error, "WebClient::read_chunked(): can't read response\n");
					close();
					return false;
				}
				
				// read response
				response.resize((uint32_t)(s + socket.getSize()));
				response.resize((uint32_t)(s + socket.read(response.get() + s, response.size() - s)));
				offset = 0;
			}
			
			// chunk size
			uint32_t length = 0;
			const char *r = response.get() + getOffset();
			size_t size = String::tou32(r, 16, &length);
			if(size == 0) break;
			
			// next line
			r += length;
			while(*r && r < response.get() + response.size()) {
				if(*r == '\r' && r[1] == '\n') {
					r += 2;
					break;
				}
				r++;
			}
			
			// response data
			size_t s = min((size_t)(response.get() + response.size() - r), size);
			if(s && dest->write(r, s) != s) {
				TS_LOG(Error, "WebClient::read_chunked(): can't write stream\n");
				close();
				return false;
			}
			
			// read data
			if(size > s && socket.readStream(*dest, size - s) != size - s) {
				TS_LOG(Error, "WebClient::read_chunked(): can't read stream\n");
				close();
				return false;
			}
			
			// clear response
			response.clear();
		}
		
		// decompress data
		if(getContent() == ContentDeflate) {
			if(!response_blob.seek(0) || stream.decodeZip(response_blob, 0, nullptr, 15 + 16) == 0) {
				TS_LOG(Error, "WebClient::read_chunked(): can't decode stream\n");
				close();
				return false;
			}
		}
		
		// clear response
		clear_response();
		
		return true;
	}
	
	/*
	 */
	bool WebClient::read(Stream &stream, const ReadCallback &func, size_t block) {
		
		// chunked transfer
		if(getTransfer() == TransferChunked) return read_chunked(stream);
		
		// check response
		if(getCode() != CodeOk) {
			TS_LOGF(Error, "WebClient::read(): invalid code %u%s\n", getCode(), getCodeName());
			close();
			return false;
		}
		if(getOffset() == Maxu32 || getSize() == MaxSize) {
			TS_LOG(Error, "WebClient::read(): invalid response\n");
			close();
			return false;
		}
		
		// default block size
		if(block == 0) block = 1024 * 128;
		
		// response blob
		Blob response_blob;
		Stream *dest = &stream;
		if(getContent() == ContentDeflate) {
			dest = &response_blob;
		}
		
		// response data
		uint64_t begin = Time::current();
		size_t s = response.size() - getOffset();
		if(s && dest->write(response.get() + getOffset(), s) != s) {
			TS_LOG(Error, "WebClient::read(): can't write stream\n");
			close();
			return false;
		}
		if(func && !func(s, size, 0)) {
			close();
			return false;
		}
		
		// read data
		while(size > s) {
			size_t ret = socket.readStream(*dest, min(size - s, block));
			if(ret == 0) {
				TS_LOG(Error, "WebClient::read(): can't read stream\n");
				close();
				return false;
			}
			s += ret;
			if(func && !func(s, size, (size_t)((uint64_t)s * 1000 / max(((Time::current() - begin) * 1000 / Time::Seconds), (uint64_t)1)))) {
				close();
				return false;
			}
		}
		
		// decompress data
		if(getContent() == ContentDeflate) {
			if(!response_blob.seek(0) || stream.decodeZip(response_blob, 0, nullptr, 15 + 16) == 0) {
				TS_LOG(Error, "WebClient::read(): can't decode stream\n");
				close();
				return false;
			}
		}
		
		// clear response
		clear_response();
		
		return true;
	}
	
	bool WebClient::read(Stream &stream) {
		
		// chunked transfer
		if(getTransfer() == TransferChunked) return read_chunked(stream);
		
		// check response
		if(getCode() != CodeOk) {
			TS_LOGF(Error, "WebClient::read(): invalid code %u%s\n", getCode(), getCodeName());
			close();
			return false;
		}
		if(getOffset() == Maxu32 || getSize() == MaxSize) {
			TS_LOG(Error, "WebClient::read(): invalid response\n");
			close();
			return false;
		}
		
		// response blob
		Blob response_blob;
		Stream *dest = &stream;
		if(getContent() == ContentDeflate) {
			dest = &response_blob;
		}
		
		// response data
		size_t s = response.size() - getOffset();
		if(s && dest->write(response.get() + getOffset(), s) != s) {
			TS_LOG(Error, "WebClient::read(): can't write stream\n");
			close();
			return false;
		}
		
		// read data
		if(size > s && socket.readStream(*dest, size - s) != size - s) {
			TS_LOG(Error, "WebClient::read(): can't read stream\n");
			close();
			return false;
		}
		
		// decompress data
		if(getContent() == ContentDeflate) {
			if(!response_blob.seek(0) || stream.decodeZip(response_blob, 0, nullptr, 15 + 16) == 0) {
				TS_LOG(Error, "WebClient::read(): can't decode stream\n");
				close();
				return false;
			}
		}
		
		// clear response
		clear_response();
		
		return true;
	}
	
	/*
	 */
	const char *WebClient::getCodeName() const {
		if(code == 400) return " Bad Request";
		if(code == 401) return " Unauthorized";
		if(code == 403) return " Forbidden";
		if(code == 404) return " Not Found";
		if(code == 408) return " Request Timeout";
		if(code == 426) return " Upgrade Required";
		if(code == 429) return " Too Many Requests";
		if(code == 500) return " Internal Server Error";
		if(code == 501) return " Not Implemented";
		if(code == 502) return " Bad Gateway";
		if(code == 503) return " Service Unavailable";
		if(code == 504) return " Gateway Timeout";
		if(code == 505) return " HTTP Version Not Supported";
		return "";
	}
}

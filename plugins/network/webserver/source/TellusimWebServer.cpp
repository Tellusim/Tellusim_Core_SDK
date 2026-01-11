// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#if _WIN32
	#include <winsock2.h>
	#pragma comment(lib, "ws2_32.lib")
#else
	#include <sys/poll.h>
#endif

#include <core/TellusimLog.h>
#include <core/TellusimBlob.h>
#include <core/TellusimEndian.h>
#include <core/TellusimFunction.h>
#include <math/TellusimScalar.h>
#include <format/TellusimParser.h>

#include "../include/TellusimWebServer.h"

/*
 */
namespace Tellusim {
	
	/*****************************************************************************\
	 *
	 * WebSession
	 *
	\*****************************************************************************/
	
	/*
	 */
	WebSession::WebSession(Socket &socket) : socket(socket) {
		
	}
	
	WebSession::~WebSession() {
		
	}
	
	/*
	 */
	void WebSession::setTimeout(uint32_t t) {
		timeout = t;
	}
	
	/*
	 */
	uint32_t WebSession::getWriteSize() const {
		return 0;
	}
	
	/*
	 */
	bool WebSession::write() {
		return false;
	}
	
	/*
	 */
	bool WebSession::read_request(Request &request) {
		
		String token;
		
		// read request
		String buffer(1024);
		if(socket.read(buffer.get(), buffer.size()) == 0) {
			return false;
		}
		
		// parse request
		const char *s = buffer.get();
		while(*s) {
			s += Parser::readToken(s, token);
			s += Parser::skipSpaces(s);
			token = token.lower();
			if(token == "get" && !request.url) {
				s += Parser::readToken(s, request.url);
				uint32_t pos = request.url.find('?');
				if(pos != Maxu32) {
					request.parameters = request.url.get() + pos + 1;
					request.url.resize(pos);
				}
			}
			else if(token == "cookie:" && !request.cookie) {
				s += Parser::readToken(s, request.cookie);
			}
			else if(token == "user-agent:" && !request.browser) {
				s += Parser::readLine(s, request.browser);
			}
			else if(token == "x-forwarded-for:" && !request.address) {
				s += Parser::readLine(s, request.address);
			}
			else if(token == "upgrade:" && !request.upgrade) {
				s += Parser::readToken(s, request.upgrade);
				request.upgrade = request.upgrade.lower();
			}
			else if(token == "sec-websocket-key:" && !request.websocket) {
				s += Parser::readLine(s, request.websocket);
			}
			else if(token == "connection:" && !request.connection) {
				s += Parser::readToken(s, request.connection);
			}
			else if(token == "range:") {
				s += Parser::readName(s, token);
				s += Parser::skipSpaces(s);
				if(token.lower() == "bytes" && *s == '=') {
					s += Parser::skipSpaces(s + 1) + 1;
					if(Parser::isDecimal(*s)) {
						request.begin = String::tou32(s);
						s += Parser::skipDecimal(s);
						s += Parser::skipSpaces(s);
						if(*s == '-') {
							s += Parser::skipSpaces(s + 1) + 1;
							if(Parser::isDecimal(*s)) {
								request.end = String::tou32(s);
								s += Parser::skipDecimal(s);
							}
						}
					} else if(*s == '-') {
						s += Parser::skipSpaces(s + 1) + 1;
						if(Parser::isDecimal(*s)) {
							request.end = String::tou32(s);
							s += Parser::skipDecimal(s);
						}
					} else {
						request.url.clear();
						break;
					}
				} else {
					request.url.clear();
					break;
				}
			}
			if(!Parser::isSpace(*s)) s += Parser::skipLine(s);
		}
		
		// check request
		if(!request.url) {
			TS_LOGF(Error, "WebSession::read_request(): can't parse request\n%s\n", buffer.get());
			return false;
		}
		
		return true;
	}
	
	/*
	 */
	String WebSession::get_filename(const Request &request) {
		
		// check request
		if(!request.url) {
			TS_LOG(Error, "WebSession::get_filename(): invalid request\n");
			return String::null;
		}
		
		// file name
		String name = request.url;
		if(name == "/") name = "index.html";
		
		// safe path
		name = name.replace("../", "/").replace("./", "/");
		while(name.begins("/")) name.remove(0);
		
		return name;
	}
	
	/*
	 */
	String WebSession::get_handshake(const Request &request) {
		
		// check request
		if(!request.websocket) {
			TS_LOG(Error, "WebSession::get_handshake(): invalid request\n");
			return String::null;
		}
		
		// response string
		Blob blob;
		blob.puts(request.websocket);
		blob.puts("258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
		blob.seek(0);
		
		// response hash
		uint32_t hash[5];
		blob.getSHA1(hash);
		
		// write hash
		blob.clear();
		for(uint32_t i = 0; i < TS_COUNTOF(hash); i++) {
			blob.writeu32(bigEndian(hash[i]));
		}
		blob.seek(0);
		
		// encode hash
		return blob.encodeBase64();
	}
	
	/*
	 */
	bool WebSession::read_socket(Blob &blob) {
		
		// read opcode
		bool status = true;
		uint32_t opcode = socket.readu8(&status);
		if(!status) {
			TS_LOGE(Error, "WebSession::read_socket(): can't read opcode\n");
			return false;
		}
		
		// read short length
		uint32_t length = socket.readu8(&status);
		if(!status) {
			TS_LOGE(Error, "WebSession::read_socket(): can't read length\n");
			return false;
		}
		
		// extended payload length
		uint32_t size = length & 0x7f;
		if(size == 126) size = bigEndian(socket.readu16(&status));
		else if(size == 127) size = (uint32_t)bigEndian(socket.readu64(&status));
		if(!status) {
			TS_LOGE(Error, "WebSession::read_socket(): can't read size\n");
			return false;
		}
		
		// read mask
		uint8_t mask[4] = {};
		if((length & 0x80) && socket.read(mask, sizeof(mask)) != sizeof(mask)) {
			TS_LOGE(Error, "WebSession::read_socket(): can't read mask\n");
			return false;
		}
		
		// read data
		blob.seek(0);
		blob.setSize(size);
		if(socket.read(blob.getData(), blob.getSize()) != blob.getSize()) {
			TS_LOGE(Error, "WebSession::read_socket(): can't read data\n");
			return false;
		}
		
		// unmask data
		if(length & 0x80) {
			uint8_t *data = blob.getData();
			for(uint32_t i = 0; i < size; i++) {
				data[i] ^= mask[i & 0x03];
			}
		}
		
		// check opcode type
		if(opcode != 129 && opcode != 130) blob.clear();
		return true;
	}
	
	bool WebSession::write_socket(Stream &stream, const Blob &blob, bool binary) {
		
		// write header
		bool status = stream.writeu8(binary ? 130 : 129);
		if(blob.getSize() > Maxu16) status & stream.writeu8(127) && stream.writeu64(bigEndian((uint64_t)blob.getSize()));
		else if(blob.getSize() > 125) status &= stream.writeu8(126) && stream.writeu16(bigEndian((uint16_t)blob.getSize()));
		else status &= stream.writeu8((uint8_t)blob.getSize());
		if(!status) {
			TS_LOGE(Error, "WebSession::write_socket(): can't write header\n");
			return false;
		}
		
		// write data
		if(stream.write(blob.getData(), blob.getSize()) != blob.getSize()) {
			TS_LOGE(Error, "WebSession::write_socket(): can't write data\n");
			return false;
		}
		
		return true;
	}
	
	/*****************************************************************************\
	 *
	 * WebServer
	 *
	\*****************************************************************************/
	
	/*
	 */
	WebServer::WebServer() {
		
	}
	
	WebServer::~WebServer() {
		
		// release socket
		socket.clearPtr();
		
		// terminate session threads
		for(uint32_t i = 0; i < threads.size(); i++) {
			if(threads[i] && threads[i]->isRunning()) {
				threads[i]->terminate();
				threads[i]->stop(true);
			}
		}
		threads.release();
		
		// release sessions
		for(uint32_t i = 0; i < sessions.size(); i++) {
			sessions[i].clear();
		}
		sessions.release();
	}
	
	/*
	 */
	void WebServer::setTimeout(uint32_t t) {
		timeout = t;
	}
	
	/*
	 */
	bool WebServer::init(uint16_t port, uint16_t num) {
		
		// server socket
		socket = Socket(Socket::TypeStream);
		if(!socket.open(port, num) || !socket.setBlock(false) || !socket.setDelay(false)) {
			TS_LOGE(Error, "WebServer::init(): can't create socket\n");
			return false;
		}
		
		return true;
	}
	
	/*
	 */
	void WebServer::session_process(Thread *thread, WebSession *session) {
		
		// server fd
		pollfd fd = {};
		fd.fd = session->getFD();
		fd.events = POLLIN;
		if(session->getWriteSize()) fd.events |= POLLOUT;
		
		// waiting for descriptor activity
		#if _WIN32
			int32_t ret = WSAPoll(&fd, 1, getTimeout() * 1000);
		#else
			int32_t ret = poll(&fd, 1, getTimeout() * 1000);
		#endif
		if(ret < 0) {
			TS_LOGE(Error, "WebServer::session_process(): can't pool descriptor\n");
			thread->terminate();
			thread->stop(true);
			return;
		}
		
		// read socket
		if((fd.revents & POLLIN) && (!session->getSocket().isAvailable() || !session->read())) {
			thread->terminate();
			thread->stop(true);
			return;
		}
		
		// write socket
		if((fd.revents & POLLOUT) && !session->write()) {
			thread->terminate();
			thread->stop(true);
			return;
		}
		
		// session timeout
		if(ret == 0) {
			thread->terminate();
			thread->stop(true);
			return;
		}
	}
	
	/*
	 */
	bool WebServer::run() {
		
		is_running = true;
		
		// run the server
		while(isRunning()) {
			
			// server fd
			pollfd fd = {};
			fd.fd = socket.getFD();
			fd.events = POLLIN;
			
			// waiting for descriptor activity
			#if _WIN32
				int32_t ret = WSAPoll(&fd, 1, getTimeout() * 1000);
			#else
				int32_t ret = poll(&fd, 1, getTimeout() * 1000);
			#endif
			if(ret < 0) {
				TS_LOGE(Error, "WebServer::run(): can't pool descriptor\n");
				continue;
			}
			
			// server socket
			if((fd.revents & POLLIN)) {
				Socket session_socket = Socket();
				if(socket.accept(session_socket)) {
					if(!session_socket.setBlock(false) || !session_socket.setDelay(false)) {
						TS_LOG(Error, "WebServer::run(): can't create session socket\n");
						continue;
					}
					AutoPtr<WebSession> session = makeAutoPtr(create_session(session_socket));
					AutoPtr<Thread> thread = makeAutoPtr(makeThreadFunction(makeClassFunction(this, &WebServer::session_process, nullptr, session.get())));
					if(!thread->run()) {
						TS_LOG(Error, "WebServer::run(): can't run session thread\n");
						continue;
					}
					threads.append(thread);
					sessions.append(session);
				}
			}
			
			// release terminated threads
			for(uint32_t i = 0; i < threads.size(); i++) {
				if(threads[i] && !threads[i]->isRunning()) {
					threads[i].clear();
					sessions[i].clear();
					threads.removeFast(i);
					sessions.removeFast(i--);
				}
			}
		}
		
		return true;
	}
	
	/*
	 */
	void WebServer::stop() {
		is_running = false;
	}
}

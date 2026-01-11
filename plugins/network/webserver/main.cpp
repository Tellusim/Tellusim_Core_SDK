// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <core/TellusimSource.h>
#include <core/TellusimSystem.h>

#include "include/TellusimWebServer.h"

/*
 */
using namespace Tellusim;

/*
 */
namespace Tellusim {
	
	/*
	 */
	class Session : public WebSession {
			
		public:
			
			Session(Socket &socket) : WebSession(socket) {
				TS_LOG(Message, "Session::Session(): called\n");
			}
			virtual ~Session() {
				TS_LOG(Message, "Session::~Session(): called\n");
			}
			
			// read data
			virtual bool read() {
				
				// read websocket
				if(websocket) {
					
					// read message
					Blob read_blob;
					if(!read_socket(read_blob)) return false;
					TS_LOGF(Message, "Session::read(): %s\n", read_blob.gets().get());
					
					// write response
					return write_socket(getSocket(), read_blob, false);
				}
				
				// read request
				Request request;
				if(!read_request(request)) return false;
				
				// server header
				String header, type, response;
				header = "Server: Tellusim::WebServer\r\n"
					"Access-Control-Allow-Origin: *\r\n"
					"Cache-Control: no-cache\r\n"
					"Connection: keep-alive\r\n"
					"Keep-Alive: timeout=8\r\n";
				
				// request extension
				String extension = request.url.extension().lower();
				
				// server request
				if(request.url == "/" || extension == "html" || extension == "js") {
					
					if(extension == "js") type = "application/javascript";
					else type = "text/html; charset=UTF-8";
					
					Source source;
					if(source.open("www/" + get_filename(request))) response = source.gets();
					else TS_LOGF(Error, "Session::read(): can't open \"%s\" file\n", request.url.get());
				}
				else if(request.url == "/socket" && request.upgrade == "websocket" && request.websocket) {
					
					websocket = true;
					socket.setBlock(true);
					
					response = String::format("HTTP/1.1 101 Switching Protocols\r\n%s"
						"Upgrade: websocket\r\n"
						"Connection: Upgrade\r\n"
						"Sec-WebSocket-Accept: %s\r\n"
						"\r\n", header.get(), get_handshake(request).get());
				}
				else {
					TS_LOGF(Error, "Session::read(): unknown server request \"%s\"\n", request.url.get());
				}
				
				// content type
				if(type) header += String::format("Content-Type: %s\r\n", type.get());
				
				// server response
				if(!response.begins("HTTP")) {
					if(response) response = String::format("HTTP/1.1 200 Ok\r\n%sContent-Length: %u\r\n\r\n", header.get(), response.size()) + response;
					else response = String::format("HTTP/1.1 404 Not Found\r\n%sContent-Length: 0\r\n\r\n", header.get());
				}
				
				// write response
				socket.puts(response);
				
				return true;
			}
			
		private:
			
			bool websocket = false;
	};
	
	/*
	 */
	class Server : public WebServer {
			
		public:
			
			Server() {
				TS_LOG(Message, "Server::Server(): called\n");
			}
			virtual ~Server() {
				TS_LOG(Message, "Server::~Server(): called\n");
			}
			
		private:
			
			// create session instance
			virtual WebSession *create_session(Socket &socket) {
				return new Session(socket);
			}
	};
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create server
	Server server;
	
	// server timeout
	server.setTimeout(1);
	
	// initialize server
	if(!server.init(8080)) return 1;
	
	// open system browser and stop the server
	#if !_IOS
		System::open("http://localhost:8080\n");
		AutoPtr<Thread> thread = makeAutoPtr(makeThreadFunction([&](Thread *thread) {
			Time::sleep(Time::Seconds * 4);
			thread->stop();
			server.stop();
		}));
		if(!thread->run()) return 1;
	#endif
	
	// run the server
	if(!server.run()) return 1;
	
	return 0;
}

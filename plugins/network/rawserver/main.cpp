// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <core/TellusimSource.h>
#include <core/TellusimSystem.h>

#include "include/TellusimRawServer.h"

/*
 */
using namespace Tellusim;

/*
 */
namespace Tellusim {
	
	/*
	 */
	class Session : public RawSession {
			
		public:
			
			Session(Socket &socket) : RawSession(socket) {
				TS_LOG(Message, "Session::Session(): called\n");
			}
			virtual ~Session() {
				TS_LOG(Message, "Session::~Session(): called\n");
			}
			
			// read data
			virtual bool read() {
				
				// read request
				String request = socket.readString();
				TS_LOGF(Message, "String::read(): request: %s\n", request.get());
				
				// write response
				String response = request + " " + String::fromBytes(request.size());
				socket.writeString(response);
				
				return true;
			}
	};
	
	/*
	 */
	class Server : public RawServer {
			
		public:
			
			Server() {
				TS_LOG(Message, "Server::Server(): called\n");
			}
			virtual ~Server() {
				TS_LOG(Message, "Server::~Server(): called\n");
			}
			
		private:
			
			// create session instance
			virtual RawSession *create_session(Socket &socket) {
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
	if(!server.init(62823)) return 1;
	
	// client thread
	AutoPtr<Thread> thread = makeAutoPtr(makeThreadFunction([&](Thread *thread) {
		Time::sleep(Time::Seconds / 2);
		Socket socket;
		if(socket.open("localhost", server.getPort()) && socket.connect(2)) {
			if(socket.writeString("Hello")) TS_LOGF(Message, "%s: response: %s\n", argv[0], socket.readString().get());
			if(socket.writeString("RawServer")) TS_LOGF(Message, "%s: response: %s\n", argv[0], socket.readString().get());
		}
		thread->stop();
		server.stop();
	}));
	if(!thread->run()) return 1;
	
	// run the server
	if(!server.run()) return 1;
	
	return 0;
}

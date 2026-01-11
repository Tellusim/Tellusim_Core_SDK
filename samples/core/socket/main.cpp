// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <core/TellusimAsync.h>
#include <core/TellusimSocket.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// datagram sockets
	if(argc > 1) {
		
		uint64_t data[64] = {};
		
		uint32_t size = 0;
		uint32_t packets = 0;
		uint32_t block = 1024 * 1024;
		uint64_t begin = Time::current();
		
		// sender
		if(!strcmp(argv[1], "-s")) {
			
			Socket socket(Socket::TypeDatagram);
			if(!socket.open("10.0.0.255", 8080) || !socket.setBlock(false)) {
				TS_LOG(Error, "can't open socket\n");
				return 1;
			}
			
			while(true) {
				data[0]++;
				size_t write = socket.write(data, sizeof(data));
				if(!write) continue;
				size += (uint32_t)write;
				packets++;
				if(size > block) {
					uint64_t end = Time::current();
					TS_LOGF(Message, "send %9s %u      \r", String::fromBytes((size_t)(size * 1000000ll / (end - begin))).get(), packets);
					size -= block;
					packets = 0;
					begin = end;
				}
			}
		}
		// receiver
		else if(!strcmp(argv[1], "-r")) {
			
			Socket socket(Socket::TypeDatagram);
			if(!socket.open(8080) || !socket.setBlock(false)) {
				TS_LOG(Error, "can't open socket\n");
				return 1;
			}
			
			while(true) {
				size_t read = socket.read(data, sizeof(data));
				if(!read) continue;
				size += (uint32_t)read;
				packets++;
				if(size > block) {
					uint64_t end = Time::current();
					TS_LOGF(Message, "recv %9s %u      \r", String::fromBytes((size_t)(size * 1000000ll / (end - begin))).get(), packets);
					size -= block;
					packets = 0;
					begin = end;
				}
			}
		}
		// unknown mode
		else {
			TS_LOGF(Error, "unknown mode %s\n", argv[1]);
		}
		
		return 0;
	}
	
	// non-blocking tcp sockets
	if(1) {
		
		uint64_t begin = Time::current();
		Socket socket(Socket::TypeStream);
		if(!socket.open("webclient.tellusim.com", 80)) TS_LOG(Error, "can't open socket\n");
		else if(!socket.connect(2)) TS_LOG(Error, "can't connect socket\n");
		else if(!socket.setBlock(false)) TS_LOG(Error, "can't unblock socket\n");
		else if(!socket.puts("GET / HTTP/1.0\r\nUser-Agent: Tellusim\r\nHost: webclient.tellusim.com\r\n\r\n")) TS_LOG(Error, "can't write socket\n");
		else if(!socket.select(2)) TS_LOG(Error, "can't select socket\n");
		else TS_LOGF(Message, "%s\n", socket.gets().get());
		TS_LOGF(Message, "total: %s\n\n", String::fromTime(Time::current() - begin).get());
	}
	
	// non-blocking tcp sockets
	if(1) {
		
		SocketSSL socket;
		uint64_t begin = Time::current();
		if(!socket.open("webclient.tellusim.com", 443)) TS_LOG(Error, "can't open socket\n");
		else if(!socket.load("cacert.crt")) TS_LOG(Error, "can't load cacert.crt\n");
		else if(!socket.connect(2)) TS_LOG(Error, "can't connect socket\n");
		else if(!socket.setBlock(false)) TS_LOG(Error, "can't unblock socket\n");
		else if(!socket.puts("GET / HTTP/1.0\r\nUser-Agent: Tellusim\r\nHost: webclient.tellusim.com\r\n\r\n")) TS_LOG(Error, "can't write socket\n");
		else if(!socket.select(2)) TS_LOG(Error, "can't select socket\n");
		else TS_LOGF(Message, "%s\n", socket.gets().get());
		TS_LOGF(Message, "total: %s\n\n", String::fromTime(Time::current() - begin).get());
	}
	
	// threaded blocking tcp sockets
	if(1) {
		
		Async async;
		if(!async.init(1)) return 1;
		
		auto task = async.run();
		uint64_t begin = Time::current();
		Socket socket(Socket::TypeStream);
		task.run([](Async::Task *task, Socket *socket) {
			if(!socket->open("tellusim.com", 80)) TS_LOG(Error, "can't open socket\n"), socket->close();
			else task->run([](Async::Task *task, Socket *socket) {
				if(!socket->connect(2)) TS_LOG(Error, "can't connect socket\n"), socket->close();
				else task->run([](Async::Task *task, Socket *socket) {
					if(!socket->puts("GET / HTTP/1.0\r\nUser-Agent: Tellusim\r\nHost: tellusim.com\r\n\r\n")) TS_LOG(Error, "can't write socket\n"), socket->close();
					else task->run([](Async::Task *task, Socket *socket) {
						if(!socket->select(2)) TS_LOG(Error, "can't select socket\n"), socket->close();
						else task->run([](Async::Task *task, Socket *socket) {
							TS_LOGF(Message, "%s\n", socket->gets().get());
							socket->close();
						}, task, socket);
					}, task, socket);
				}, task, socket);
			}, task, socket);
		}, &task, &socket);
		
		// waiting for completion
		uint64_t wait_begin = Time::current();
		task.wait(1); while(socket.isOpened()) { Time::sleep(1000); }
		TS_LOGF(Message, "wait: %s\n", String::fromTime(Time::current() - wait_begin).get());
		TS_LOGF(Message, "total: %s\n\n", String::fromTime(Time::current() - begin).get());
	}
	
	// host address
	if(1) {
		Log::print("\n");
		TS_LOGF(Message, "%s\n", Socket::getAddress(", ").get());
	}
	
	return 0;
}

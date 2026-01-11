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

#include "../include/TellusimRawServer.h"

/*
 */
namespace Tellusim {
	
	/*****************************************************************************\
	 *
	 * RawSession
	 *
	\*****************************************************************************/
	
	/*
	 */
	RawSession::RawSession(Socket &socket) : socket(socket) {
		
	}
	
	RawSession::~RawSession() {
		
	}
	
	/*
	 */
	void RawSession::setTimeout(uint32_t t) {
		timeout = t;
	}
	
	/*
	 */
	uint32_t RawSession::getWriteSize() const {
		return 0;
	}
	
	/*
	 */
	bool RawSession::write() {
		return false;
	}
	
	/*****************************************************************************\
	 *
	 * RawServer
	 *
	\*****************************************************************************/
	
	/*
	 */
	RawServer::RawServer() {
		
	}
	
	RawServer::~RawServer() {
		
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
		sessions.release();
	}
	
	/*
	 */
	void RawServer::setTimeout(uint32_t t) {
		timeout = t;
	}
	
	/*
	 */
	bool RawServer::init(uint16_t port, uint16_t num) {
		
		// server socket
		socket = Socket(Socket::TypeStream);
		if(!socket.open(port, num) || !socket.setBlock(false) || !socket.setDelay(false)) {
			TS_LOGE(Error, "RawServer::init(): can't create socket\n");
			return false;
		}
		
		return true;
	}
	
	/*
	 */
	void RawServer::session_process(Thread *thread, RawSession *session) {
		
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
			TS_LOGE(Error, "RawServer::session_process(): can't pool descriptor\n");
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
	bool RawServer::run() {
		
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
				TS_LOGE(Error, "RawServer::run(): can't pool descriptor\n");
				continue;
			}
			
			// server socket
			if((fd.revents & POLLIN)) {
				Socket session_socket = Socket();
				if(socket.accept(session_socket)) {
					if(!session_socket.setDelay(false)) {
						TS_LOG(Error, "RawServer::run(): can't create session socket\n");
						continue;
					}
					AutoPtr<RawSession> session = makeAutoPtr(create_session(session_socket));
					AutoPtr<Thread> thread = makeAutoPtr(makeThreadFunction(makeClassFunction(this, &RawServer::session_process, nullptr, session.get())));
					if(!thread->run()) {
						TS_LOG(Error, "RawServer::run(): can't run session thread\n");
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
	void RawServer::stop() {
		is_running = false;
	}
}

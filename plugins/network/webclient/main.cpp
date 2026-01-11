// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <core/TellusimLog.h>
#include <core/TellusimTime.h>
#include <core/TellusimBlob.h>
#include <core/TellusimFile.h>

#include "include/TellusimWebClient.h"

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	String url = String("webclient.tellusim.com");
	
	if(1) {
		
		Log::print("\n");
		
		WebClient client;
		
		// client name
		client.setName("Tellusim::WebClient");
		
		// connect client
		if(!client.connect("http://" + url + ":80")) return 1;
		
		// get request
		{
			Blob blob;
			if(client.get(String("/")) && client.read(blob)) {
				blob.seek(0);
				TS_LOG(Message, blob.gets().get());
			}
		}
		{
			Blob blob;
			if(client.get(String("/blob.sha1")) && client.read(blob)) {
				blob.seek(0);
				TS_LOG(Message, blob.gets().get());
			}
		}
		{
			Blob blob;
			if(client.get(String("/blob")) && client.read(blob)) {
				blob.seek(0);
				TS_LOGF(Message, "%s %u\n", blob.getSHA1().get(), (uint32_t)blob.getSize());
			}
		}
		
		// post request
		{
			Blob blob;
			if(client.post(String("/"), String("name=name&data=data")) && client.read(blob)) {
				blob.seek(0);
				TS_LOG(Message, blob.gets().get());
			}
		}
	}
	
	if(1) {
		
		Log::print("\n");
		
		WebClient client;
		
		// client name
		client.setName("Tellusim::WebClientSSL");
		
		// connect client
		if(!client.load("www/DigiCertCA.pem")) return 1;
		if(!client.connect("https://" + url + ":443")) return 1;
		
		// get request
		{
			Blob blob;
			if(client.get(String("/")) && client.read(blob)) {
				blob.seek(0);
				TS_LOG(Message, blob.gets().get());
			}
		}
		{
			Blob blob;
			if(client.get(String("/blob.sha1")) && client.read(blob)) {
				blob.seek(0);
				TS_LOG(Message, blob.gets().get());
			}
		}
		{
			Blob blob;
			if(client.get(String("/blob")) && client.read(blob)) {
				blob.seek(0);
				TS_LOGF(Message, "%s %u\n", blob.getSHA1().get(), (uint32_t)blob.getSize());
			}
		}
		
		// post request
		{
			Blob blob;
			if(client.post(String("/"), String("name=name&data=data")) && client.read(blob)) {
				blob.seek(0);
				TS_LOG(Message, blob.gets().get());
			}
		}
	}
	
	if(0) {
		
		Log::print("\n");
		
		WebClient client;
		
		// client name
		client.setName("Tellusim::WebClientSSL");
		
		// open proxy
		client.setProxy(String("127.0.0.1"), 8888);
		if(!client.open("https://" + url)) return 1;
		
		// handshake connection
		if(!client.load("www/DigiCertCA.pem")) return 1;
		if(!client.handshake()) return 1;
		
		// get request
		Blob blob;
		if(client.get(String("/")) && client.read(blob)) {
			blob.seek(0);
			TS_LOG(Message, blob.gets().get());
		}
	}
	
	if(1) {
		
		Log::print("\n");
		
		WebClient client;
		
		// client name
		client.setName("Tellusim::WebClientSSL");
		
		// connect client
		if(!client.load("www/DigiCertCA.pem")) return 1;
		if(!client.connect(String("https://tellusim.com:443"))) return 1;
		
		// get response
		Blob blob;
		if(client.get(String("/")) && client.read(blob)) {
			blob.seek(0);
			TS_LOG(Message, blob.gets().get());
		}
	}
	
	return 0;
}

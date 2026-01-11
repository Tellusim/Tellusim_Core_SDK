// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

/*
 */
function init() {
	
	let websocket = new WebSocket('ws://' + window.location.host + '/socket');
	
	websocket.onopen = function(event) {
		websocket.send('ping');
	}
	
	websocket.onmessage = function(event) {
		if(event.data == 'ping') websocket.send(event.data + ' pong');
	}
}

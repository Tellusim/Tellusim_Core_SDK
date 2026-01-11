// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

/*
 */
var items_json = undefined;
var current_tab = undefined;
var settings_button = undefined;
var settings_api = undefined;
var settings_size = undefined;
var settings_device = undefined;
var settings_binary = undefined;
var settings_panel = undefined;
var storage_prefix = "ts_core_sdk_";

/*
 */
function create_tabs() {
	
	// tab group
	let tab_group = document.getElementById("tab_group");
	
	// restore current key
	let current_key = localStorage.getItem(storage_prefix + "current_key");
	
	// create tab buttons
	for(let items_key in items_json) {
		
		// create tab button
		let tab_button = document.createElement("button");
		tab_button.className = "tab-button";
		tab_button.textContent = items_key;
		tab_group.appendChild(tab_button);
		
		// tab button callback
		tab_button.onclick = (function(tab_button, items_key) {
			return function() { tab_clicked(tab_button, items_key); };
		})(tab_button, items_key);
		
		// active tab
		if(!current_tab && !current_key) tab_clicked(tab_button, items_key);
		else if(current_key == items_key) tab_clicked(tab_button, items_key);
	}
}

/*
 */
function tab_clicked(tab_button, items_key) {
	
	// switch tab
	if(current_tab == tab_button) return;
	if(current_tab) current_tab.className = "tab-button";
	tab_button.className = "tab-button tab-button-active";
	current_tab = tab_button;
	
	// save current key
	localStorage.setItem(storage_prefix + "current_key", items_key);
	
	// clear items
	let items_table = document.getElementById("items_table");
	while(items_table.firstChild) {
		items_table.removeChild(items_table.firstChild);
	}
	
	// create items
	create_items(items_key);
}

/*
 */
function create_reference(name, title, postfix, item, references) {
	
	// open reference
	if(name in item) {
		
		// target name
		let target = "open/" + item[name];
		
		// target reference
		let reference = document.createElement("a");
		reference.className = "item-reference";
		references.appendChild(reference);
		reference.textContent = title;
		reference.title = item[name] + postfix;
		
		// target reference clicked callback
		reference.onclick = (function(target, name) {
			return function() {
				let request = new XMLHttpRequest();
				request.open("GET", target, true);
				request.onreadystatechange = function() {
					if(request.readyState === request.DONE && request.status === 200) {
						if(request.responseText == "0") alert("cannot open " + name);
					}
				}
				request.send(null);
			};
		})(target, name);
	}
}

/*
 */
function create_items(items_key) {
	
	// item json
	let item_json = items_json[items_key];
	
	// items table
	let items_table = document.getElementById("items_table");
	
	// create items table
	for(let item_key in item_json) {
		
		// load item
		let item = item_json[item_key];
		let title = item["title"];
		
		// item row
		let item_row = document.createElement("div");
		item_row.className = "item-row";
		items_table.appendChild(item_row);
		
		// item left container
		let item_left = document.createElement("div");
		item_left.className = "item-left";
		item_row.appendChild(item_left);
		
		// item image
		let item_image = document.createElement("img");
		item_image.className = "item-image";
		item_image.src = item["image"];
		item_image.title = title;
		item_left.appendChild(item_image);
		
		// item right container
		let item_right = document.createElement("div");
		item_right.className = "item-right";
		item_row.appendChild(item_right);
		
		// item title
		let item_title = document.createElement("p");
		item_title.className = "item-title";
		item_right.appendChild(item_title);
		item_title.textContent = title;
		
		// item line
		let item_line = document.createElement("hr");
		item_line.className = "item-line";
		item_right.appendChild(item_line);
		
		// item text
		let item_text = document.createElement("p");
		item_text.className = "item-text";
		item_right.appendChild(item_text);
		item_text.innerHTML = item["text"];
		
		// item references
		let item_references = document.createElement("div");
		item_references.className = "item-references";
		item_right.appendChild(item_references);
		
		// open resource
		if("open" in item) {
			
			// resource name
			let name = "open/" + item["open"];
			
			// image title
			item_image.title = item["open"];
			
			// item image clicked callback
			item_image.onclick = (function(name) {
				return function() {
					let request = new XMLHttpRequest();
					request.open("GET", name, true);
					request.send(null);
				};
			})(name);
		}
		
		// exec command
		if("exec" in item || "scene" in item) {
			
			// exec command
			let command = "exec/";
			
			// open reference
			let run_reference = document.createElement("a");
			run_reference.className = "item-reference";
			item_references.appendChild(run_reference);
			
			// exec command
			if("exec" in item) {
				if("path" in item) {
					if(get_platform() == "windows") {
						command += "cmd.exe /c cd " + item["path"] + " && ";
						item_image.title = item["path"] + "/" + item["exec"];
						if(!item["exec"].includes(".")) item_image.title += ".exe";
					} else {
						command += "cd ./" + item["path"] + " && ./";
						item_image.title = item["path"] + "/" + item["exec"];
					}
				} else {
					item_image.title = item["exec"];
				}
				command += item["exec"] + "%s";
				run_reference.textContent = "Run Binary";
			}
			// open scene
			else if("scene" in item) {
				command += "ts_explorer%s -s " + item["scene"];
				item_image.title = item["scene"];
				run_reference.textContent = "Open Scene";
			}
			
			// command arguments
			if("args" in item) command += " " + item["args"];
			
			// item image clicked callback
			item_image.onclick = (function(command) {
				return function() {
					let request = new XMLHttpRequest();
					let settings = settings_binary.value + " " + settings_api.value + " " + settings_size.value + " " + settings_device.value;
					if(!command.includes(".")) settings = settings_binary.value + settings;
					request.open("GET", command.replace("%s", settings), true);
					request.onreadystatechange = function() {
						if(request.readyState === request.DONE && request.status === 200) {
							if(request.responseText == "0") alert("cannot run binary");
						}
					}
					request.send(null);
				};
			})(command);
			
			// run reference clicked callback
			run_reference.title = item_image.title;
			run_reference.onclick = item_image.onclick;
		}
		
		// open path reference
		create_reference("path", "Directory", "/", item, item_references);
		
		// open project reference
		if("project" in item && (get_platform() == "windows" || get_platform() == "macos")) {
			
			let extension = undefined;
			if(get_platform() == "windows") extension = ".vcxproj";
			if(get_platform() == "macos") extension = ".xcodeproj";
			
			// project name
			let project = "open/" + item["project"] + extension;
			
			// project reference
			let project_reference = document.createElement("a");
			project_reference.className = "item-reference";
			item_references.appendChild(project_reference);
			project_reference.textContent = "Project";
			project_reference.title = item["project"] + extension;
			
			// project reference clicked callback
			project_reference.onclick = (function(project) {
				return function() {
					let request = new XMLHttpRequest();
					request.open("GET", project, true);
					request.onreadystatechange = function() {
						if(request.readyState === request.DONE && request.status === 200) {
							if(request.responseText == "0") alert("cannot open project");
						}
					}
					request.send(null);
				};
			})(project);
		}
		
		// open references
		create_reference("readme", "Readme", "", item, item_references);
		create_reference("source", "Source", "", item, item_references);
		create_reference("csharp", "C# Source", "", item, item_references);
		create_reference("rust", "Rust Source", "", item, item_references);
		create_reference("swift", "Swift Source", "", item, item_references);
		create_reference("python", "Python Source", "", item, item_references);
	}
}

/*
 */
function create_generator() {
	
	// create project tab
	let tab_menu = document.getElementById("tab_menu");
	let tab_project = document.createElement("div");
	tab_project.className = "tab-project";
	tab_menu.appendChild(tab_project);
	
	// create project button
	project_button = document.createElement("button");
	project_button.className = "tab-button";
	project_button.textContent = "New Project";
	project_button.style.whiteSpace = "nowrap";
	tab_project.appendChild(project_button);
	
	// reference clicked callback
	project_button.onclick = function() {
		let request = new XMLHttpRequest();
		request.open("GET", "exec/ts_project", true);
		request.onreadystatechange = function() {
			if(request.readyState === request.DONE && request.status === 200) {
				if(request.responseText == "0") alert("cannot run binary");
			}
		}
		request.send(null);
	};
}

/*
 */
function add_settings(settings, text, value) {
	let option = document.createElement("option");
	settings.add(option);
	option.text = text;
	option.value = value;
}

/*
 */
function save_settings() {
	localStorage.setItem(storage_prefix + "settings_api", settings_api.selectedIndex);
	localStorage.setItem(storage_prefix + "settings_size", settings_size.selectedIndex);
	localStorage.setItem(storage_prefix + "settings_device", settings_device.selectedIndex);
	localStorage.setItem(storage_prefix + "settings_binary", settings_binary.selectedIndex);
}

/*
 */
function create_settings() {
	
	// create settings tab
	let tab_menu = document.getElementById("tab_menu");
	let tab_settings = document.createElement("div");
	tab_settings.className = "tab-settings";
	tab_menu.appendChild(tab_settings);
	
	// create settings button
	settings_button = document.createElement("button");
	settings_button.className = "tab-button";
	settings_button.textContent = "Settings";
	tab_settings.appendChild(settings_button);
	
	// settings elements
	settings_api = document.getElementById("settings_api");
	settings_size = document.getElementById("settings_size");
	settings_device = document.getElementById("settings_device");
	settings_binary = document.getElementById("settings_binary");
	settings_panel = document.getElementById("settings_panel");
	tab_settings.appendChild(settings_panel);
	
	// create settings
	if(get_platform() == "windows") {
		add_settings(settings_api, "Default", "");
		add_settings(settings_api, "Vulkan", "-vk");
		add_settings(settings_api, "OpenGL", "-gl");
		add_settings(settings_api, "Direct3D12", "-d3d12");
		add_settings(settings_api, "Direct3D11", "-d3d11");
	}
	else if(get_platform() == "linux") {
		add_settings(settings_api, "Default", "");
		add_settings(settings_api, "Vulkan", "-vk");
		add_settings(settings_api, "OpenGL", "-gl");
		add_settings(settings_api, "OpenGLES", "-gles");
	}
	else if(get_platform() == "macos") {
		add_settings(settings_api, "Default", "");
		add_settings(settings_api, "Metal", "-mtl");
	}
	add_settings(settings_size, "Default", "");
	add_settings(settings_size, "1280x720", "-mode hd");
	add_settings(settings_size, "1600x900", "-mode hd+");
	add_settings(settings_size, "1920x1080", "-mode fhd");
	add_settings(settings_size, "2560x1440", "-mode 2k");
	add_settings(settings_size, "3840x2160", "-mode 4k");
	add_settings(settings_device, "Default", "");
	add_settings(settings_device, "First", "-device 0");
	add_settings(settings_device, "Second", "-device 1");
	add_settings(settings_device, "Third", "-device 2");
	add_settings(settings_binary, "Release", "");
	add_settings(settings_binary, "Debug", "d");
	
	// restore settings
	let api_index = localStorage.getItem(storage_prefix + "settings_api");
	let size_index = localStorage.getItem(storage_prefix + "settings_size");
	let device_index = localStorage.getItem(storage_prefix + "settings_device");
	let binary_index = localStorage.getItem(storage_prefix + "settings_binary");
	
	if(api_index) settings_api.selectedIndex = api_index;
	if(size_index) settings_size.selectedIndex = size_index;
	if(device_index) settings_device.selectedIndex = device_index;
	if(binary_index) settings_binary.selectedIndex = binary_index;
	
	// settings clicked callback
	settings_button.onclick = function() {
		if(settings_panel.style.display != "block") {
			settings_panel.style.display = "block";
		} else {
			settings_panel.style.display = "none";
			save_settings();
		}
	};
	
	// window clicked callback
	window.onclick = function(event) {
		if(event.target != settings_button && event.target != settings_panel && !settings_panel.contains(event.target)) {
			settings_panel.style.display = "none";
			save_settings();
		}
	};
}

/*
 */
function preload_images() {
	
	// items
	for(let items_key in items_json) {
		let item_json = items_json[items_key];
		
		// item
		for(let item_key in item_json) {
			let item = item_json[item_key];
			
			// image
			if("image" in item) {
				let image = new Image();
				image.src = item["image"];
			}
		}
	}
}

/*
 */
function init() {
	
	// sdk info
	let info = document.getElementById("tab_info");
	info.innerHTML += " " + get_date();
	
	// load items
	let request = new XMLHttpRequest();
	request.open("GET", "items.js", true);
	request.onreadystatechange = function() {
		if(request.readyState === request.DONE && request.status === 200) {
			let response = request.responseText;
			if(response.length > 0) {
				items_json = JSON.parse(response);
				create_tabs();
				create_generator();
				create_settings();
				preload_images();
			}
		}
	};
	request.send(null);
}

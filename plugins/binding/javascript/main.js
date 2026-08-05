// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

/*
 */
var Module = {
	preRun: () => {
		Module.FS.createPreloadedFile('/', 'main.shader', 'main.shader', true, false);
	},
};

/*
 */
Tellusim(Module).then(ts => {
	ts.run(main);
});

/*
 */
function create_mesh(ts, steps, radius, texcoord) {
	
	// create mesh
	let mesh = new ts.Mesh();
	
	// create vertices
	let num_vertices = (steps.x + 1) * (steps.y + 1);
	let positions = new ts.MeshAttribute(ts.MeshAttribute.Type.Position, ts.Format.RGBf32, num_vertices);
	let normals = new ts.MeshAttribute(ts.MeshAttribute.Type.Normal, ts.Format.RGBf32, num_vertices);
	let tangents = new ts.MeshAttribute(ts.MeshAttribute.Type.Tangent, ts.Format.RGBAf32, num_vertices);
	let texcoords = new ts.MeshAttribute(ts.MeshAttribute.Type.TexCoord, ts.Format.RGf32, num_vertices);
	
	let vertex = 0;
	let isteps = ts.Vector2f.one().div(new ts.Vector2f(steps));
	let aspect = radius.x / radius.y;
	console.log('' + isteps + ' ' + aspect + ' ' + ts.Base.Pi05);
	for(let j = 0; j <= steps.y; j++) {
		let ty = j * isteps.y;
		let z = -Math.cos(ty * ts.Base.Pi2 - ts.Base.Pi05);
		let r = Math.sin(ty * ts.Base.Pi2 - ts.Base.Pi05);
		for(let i = 0; i <= steps.x; i++) {
			let tx = i * isteps.x;
			let x = -Math.sin(tx * ts.Base.Pi2);
			let y = Math.cos(tx * ts.Base.Pi2);
			positions.set(vertex, new ts.Vector3f(x * (r * radius.y + radius.x), y * (r * radius.y + radius.x), z * radius.y));
			normals.set(vertex, new ts.Vector3f(x * r, y * r, z));
			tangents.set(vertex, new ts.Vector4f(-y, x, 0.0, 1.0));
			texcoords.set(vertex, (new ts.Vector2f(tx * aspect, ty)).mul(texcoord));
			vertex++;
		}
	}
	
	let basis = new ts.MeshAttribute(ts.MeshAttribute.Type.Basis, ts.Format.RGBAu32, num_vertices);
	basis.packAttributes(normals, tangents, ts.Format.RGBAf16);
	
	// create indices
	let num_indices = steps.x * steps.y * 4;
	let indices_format = (num_vertices < ts.Maxu16) ? ts.Format.Ru16 : ts.Format.Ru32;
	let indices = new ts.MeshIndices(ts.MeshIndices.Type.Quadrilateral, indices_format, num_indices);
	
	let index = 0;
	for(let j = 0; j < steps.y; j++) {
		for(let i = 0; i < steps.x; i++) {
			vertex = (steps.x + 1) * j + i;
			indices.set(index, vertex, vertex + 1, vertex + steps.x + 2, vertex + steps.x + 1);
			index += 4;
		}
	}
	
	// create geometry
	let geometry = new ts.MeshGeometry(mesh);
	geometry.addAttribute(positions, indices);
	geometry.addAttribute(basis, indices);
	geometry.addAttribute(normals, indices);
	geometry.addAttribute(texcoords, indices);
	
	// geometry bounds
	let hsize = new ts.Vector3f(new ts.Vector2f(radius.x + radius.y), radius.y);
	geometry.setBoundBox(new ts.BoundBoxf(hsize.neg(), hsize));
	
	// create bounds
	mesh.createBounds();
	
	return mesh;
}

/*
 */
function create_image(ts, size, frame) {
	
	// create image
	let image = new ts.Image();
	image.create2D(ts.Format.RGBAu8n, size);
	
	// create sampler
	let sampler = new ts.ImageSampler(image, new ts.Slice());
	
	// fill image
	let color = new ts.ImageColor(255);
	for(let y = 0; y < size; y++) {
		for(let x = 0; x < size; x++) {
			let v = (((x - (frame ^ y)) ^ (y + (frame ^ x))) & 255) / 63.0;
			color.ri = Math.cos(ts.Base.Pi * 1.0 + v) * 127.5 + 127.5;
			color.gi = Math.cos(ts.Base.Pi * 0.5 + v) * 127.5 + 127.5;
			color.bi = Math.cos(ts.Base.Pi * 0.0 + v) * 127.5 + 127.5;
			sampler.set2D(x, y, color);
		}
	}
	
	return image;
}

/*
 */
function main(ts, app) {
	
	// create window
	let window = new ts.Window(app.platform, app.device);
	if(!window.isValidPtr()) return;
	
	window.setSize(app.width, app.height);
	window.setCloseClickedCallback(function() {
		window.stop();
	});
	window.setKeyboardPressedCallback(function(key, code) {
		if(key == ts.Window.Key.Esc) window.stop();
	});
	
	let title = window.platform_name + ' Tellusim::JavaScript';
	if(!window.create(title, ts.Window.Flags.Default | ts.Window.Flags.VerticalSync) || !window.setHidden(false)) return;
	
	// create device
	let device = new ts.Device(window);
	if(!device.isValidPtr()) return;
	
	// device features
	ts.Log.print(ts.Log.Level.Message, 'Features:\n' + device.features + '\n');
	ts.Log.print(ts.Log.Level.Message, 'Device: ' + device.name + '\n');
	
	// build info
	ts.Log.print(ts.Log.Level.Message, 'Build: ' + ts.App.getBuildInfo() + '\n');
	
	// create target
	let target = device.createTarget(window);
	if(!target.isValidPtr()) return;
	
	////////////////////////////////
	// core test
	////////////////////////////////
	
	let blob = new ts.Blob();
	blob.writeString(title);
	
	blob.seek(0);
	ts.Log.print(ts.Log.Level.Message, 'Stream: ' + blob.readString() + '\n');
	
	////////////////////////////////
	// bounds test
	////////////////////////////////
	
	// 32-bit floating point
	let bound_boxf = new ts.BoundBoxf(ts.Vector3f.one().neg(), ts.Vector3f.one());
	let bound_spheref = new ts.BoundSpheref(bound_boxf);
	let bound_frustumf = new ts.BoundFrustumf(ts.Matrix4x4f.perspective(60.0, 1.0, 0.1, 1000.0), ts.Matrix4x4f.lookAt(ts.Vector3f.one(), ts.Vector3f.zero(), new ts.Vector3f(0.0, 0.0, 1.0)));
	ts.Log.print(ts.Log.Level.Message, ' ' + bound_boxf + ' ' + bound_frustumf.inside(bound_boxf) + ' ' + bound_spheref + ' ' + bound_frustumf.inside(bound_spheref) + '\n');
	bound_boxf = ts.Matrix4x3f.translate(10.0, 0.0, 0.0).mul(bound_boxf);
	bound_spheref = ts.Matrix4x4f.translate(10.0, 0.0, 0.0).mul(bound_spheref);
	ts.Log.print(ts.Log.Level.Message, ' ' + bound_boxf + ' ' + bound_frustumf.inside(bound_boxf) + ' ' + bound_spheref + ' ' + bound_frustumf.inside(bound_spheref) + '\n');
	
	// 64-bit floating point
	let bound_boxd = new ts.BoundBoxd(ts.Vector3d.one().neg(), ts.Vector3d.one());
	let bound_sphered = new ts.BoundSphered(bound_boxd);
	let bound_frustumd = new ts.BoundFrustumd(ts.Matrix4x4d.perspective(60.0, 1.0, 0.1, 1000.0), ts.Matrix4x4d.lookAt(ts.Vector3d.one(), ts.Vector3d.zero(), new ts.Vector3d(0.0, 0.0, 1.0)));
	ts.Log.print(ts.Log.Level.Message, ' ' + bound_boxd + ' ' + bound_frustumd.inside(bound_boxd) + ' ' + bound_sphered + ' ' + bound_frustumd.inside(bound_sphered) + '\n');
	bound_boxd = ts.Matrix4x3d.translate(10.0, 0.0, 0.0).mul(bound_boxd);
	bound_sphered = ts.Matrix4x4d.translate(10.0, 0.0, 0.0).mul(bound_sphered);
	ts.Log.print(ts.Log.Level.Message, ' ' + bound_boxd + ' ' + bound_frustumd.inside(bound_boxd) + ' ' + bound_sphered + ' ' + bound_frustumd.inside(bound_sphered) + '\n');
	
	////////////////////////////////
	// platform test
	////////////////////////////////
	
	// create pipeline
	let pipeline = device.createPipeline();
	pipeline.setUniformMask(0, ts.Shader.Mask.Fragment);
	pipeline.setColorFormat(window.color_format);
	pipeline.setDepthFormat(window.depth_format);
	pipeline.setDepthMask(ts.Pipeline.DepthMask.None);
	pipeline.addAttribute(ts.Pipeline.Attribute.Position, ts.Format.RGf32, 0, 0, 8);
	if(!pipeline.loadShaderGLSL(ts.Shader.Type.Vertex, "main.shader", "VERTEX_SHADER=1")) return;
	if(!pipeline.loadShaderGLSL(ts.Shader.Type.Fragment, "main.shader", "FRAGMENT_SHADER=1")) return;
	if(!pipeline.create()) return;
	
	// geometry vertices
	let vertices = new Float32Array([ 3.0, -1.0, -1.0, -1.0, -1.0, 3.0]);
	
	// geometry indices
	let indices = new Int16Array([ 0, 1, 2 ]);
	
	////////////////////////////////
	// interface test
	////////////////////////////////
	
	// create canvas
	let canvas = new ts.Canvas();
	
	// create root controls
	let root = new ts.ControlRoot(canvas, true);
	root.setFontSize(24);
	
	// create dialog
	let dialog = new ts.ControlDialog(root, 1, 8.0, 8.0);
	dialog.setUpdatedCallback(function(dialog) {
		let x = dialog.position_x;
		let y = dialog.position_y;
		let width = dialog.width;
		let height = dialog.height;
		ts.Log.print(ts.Log.Level.Message, 'Dialog Updated ' + x + ' ' + y + ' ' + width + 'x' + height + '\n');
	});
	dialog.setAlign(ts.Control.Align.Center);
	dialog.setSize(240.0, 180.0);
	
	// create text
	let text = new ts.ControlText(dialog, title);
	text.setAlign(ts.Control.Align.CenterX);
	
	// create button
	let button = new ts.ControlButton(dialog, 'Button');
	button.setClickedCallback(function(button) {
		ts.Log.print(ts.Log.Level.Message, button.text + ' Clicked\n');
	});
	button.setAlign(ts.Control.Align.Expand);
	button.setMargin(0.0, 0.0, 0.0, 16.0);
	
	// create sliders
	let color = ts.Color.white();
	let slider_r = new ts.ControlSlider(dialog, "R", 2, color.r, 0.0, 1.0);
	let slider_g = new ts.ControlSlider(dialog, "G", 2, color.g, 0.0, 1.0);
	let slider_b = new ts.ControlSlider(dialog, "B", 2, color.b, 0.0, 1.0);
	slider_r.setChangedCallback(function(slider) { color.r = slider.valuef32; });
	slider_g.setChangedCallback(function(slider) { color.g = slider.valuef32; });
	slider_b.setChangedCallback(function(slider) { color.b = slider.valuef32; });
	slider_r.setAlign(ts.Control.Align.ExpandX);
	slider_g.setAlign(ts.Control.Align.ExpandX);
	slider_b.setAlign(ts.Control.Align.ExpandX);
	
	////////////////////////////////
	// render test
	////////////////////////////////
	
	// vertex shader
	let vertex_shader = `
		layout(location = 0) in vec4 in_position;
		layout(location = 1) in vec3 in_normal;
		layout(location = 2) in vec2 in_texcoord;
		layout(row_major, binding = 0) uniform CommonParameters {
			mat4 projection;
			mat4 modelview;
			mat4 transform;
			vec4 camera;
		};
		layout(location = 0) out vec3 s_direction;
		layout(location = 1) out vec3 s_normal;
		layout(location = 2) out vec2 s_texcoord;
		void main() {
			vec4 position = transform * in_position;
			gl_Position = projection * (modelview * position);
			s_direction = camera.xyz - position.xyz;
			s_normal = (transform * vec4(in_normal, 0.0f)).xyz;
			s_texcoord = in_texcoord;
		}
	`;
	
	// fragment shader
	let fragment_shader = `
		layout(binding = 0, set = 1) uniform texture2D in_texture;
		layout(binding = 0, set = 2) uniform sampler in_sampler;
		layout(location = 0) in vec3 s_direction;
		layout(location = 1) in vec3 s_normal;
		layout(location = 2) in vec2 s_texcoord;
		layout(location = 0) out vec4 out_color;
		void main() {
			vec3 direction = normalize(s_direction);
			vec3 normal = normalize(s_normal);
			float diffuse = clamp(dot(direction, normal), 0.0f, 1.0f);
			float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0f, 1.0f), 16.0f);
			out_color = texture(sampler2D(in_texture, in_sampler), s_texcoord) * diffuse + specular;
		}
	`;
	
	// create render pipeline
	let render_pipeline = device.createPipeline();
	render_pipeline.setUniformMask(0, ts.Shader.Mask.Vertex);
	render_pipeline.setTextureMask(0, ts.Shader.Mask.Fragment);
	render_pipeline.setSamplerMask(0, ts.Shader.Mask.Fragment);
	render_pipeline.setColorFormat(window.color_format);
	render_pipeline.setDepthFormat(window.depth_format);
	render_pipeline.setDepthFunc(ts.Pipeline.DepthFunc.LessEqual);
	render_pipeline.addAttribute(ts.Pipeline.Attribute.Position, ts.Format.RGBf32, 0, 0, 32);
	render_pipeline.addAttribute(ts.Pipeline.Attribute.Normal, ts.Format.RGBf32, 0, 12, 32);
	render_pipeline.addAttribute(ts.Pipeline.Attribute.TexCoord, ts.Format.RGf32, 0, 24, 32);
	if(!render_pipeline.createShaderGLSL(ts.Shader.Type.Vertex, vertex_shader)) return;
	if(!render_pipeline.createShaderGLSL(ts.Shader.Type.Fragment, fragment_shader)) return;
	if(!render_pipeline.create()) return;
	
	// create mesh
	let mesh = create_mesh(ts, new ts.Vector2i(64, 32), new ts.Vector2f(8.0, 2.0), 2.0);
	
	// create model
	let model = new ts.MeshModel();
	if(!model.create(device, render_pipeline, mesh)) return;
	
	// create sampler
	let sampler = device.createSampler(ts.Sampler.Filter.Linear, ts.Sampler.WrapMode.Repeat);
	if(!sampler.isValidPtr()) return;
	
	// create texture
	let image = create_image(ts, 256, 0);
	let texture = device.createTexture(image);
	if(!texture.isValidPtr()) return;
	
	////////////////////////////////
	// main loop
	////////////////////////////////
	
	let texture_frame = 0;
	let texture_ifps = 1.0 / 30.0;
	let texture_time = ts.Time.seconds();
	
	window.run(function() {
		
		// update window
		ts.Window.update(false);
		
		// render window
		if(!window.render()) return false;
		
		// update texture
		if(ts.Time.seconds() - texture_time > texture_ifps) {
			texture_time += texture_ifps;
			image = create_image(ts, 256, texture_frame);
			device.setTexture(texture, image);
			image.destroyPtr();
			texture_frame++;
		}
		
		// update interface
		{
			// window size
			let height = app.height;
			let width = Math.floor(height * window.width / window.height);
			let mouse_x = width * window.mouse_x / window.width;
			let mouse_y = height * window.mouse_y / window.height;
			
			// mouse button
			let buttons = ts.Control.Button.None;
			if((window.mouse_buttons & ts.Window.Button.Left) != ts.Window.Button.None) buttons |= ts.Control.Button.Left;
			if((window.mouse_buttons & ts.Window.Button.Left2) != ts.Window.Button.None) buttons |= ts.Control.Button.Left;
			
			// update controls
			root.setViewport(width, height);
			root.setMouse(mouse_x, mouse_y, buttons);
			while(root.update(canvas.getScale(target))) { }
			
			// create canvas
			canvas.create(device, target);
		}
		
		target.begin();
			
			let command = device.createCommand(target);
			
			// common parameters
			let time = ts.Time.seconds();
			let parameters_buffer = new ArrayBuffer(64 + 32);
			let parameters = new Float32Array(parameters_buffer);
			parameters.set(ts.Matrix4x4f.rotateZ(time * 16.0).getArray());
			parameters.set(color.getArray(), 16);
			parameters.set([ time ], 20);
			
			// draw background
			command.setPipeline(pipeline);
			command.setUniform(0, parameters);
			command.setVertices(0, vertices);
			command.setIndices(indices);
			command.drawElements(3);
			
			// render parameters
			let camera_position = new ts.Vector3f(12.0, 12.0, 6.0);
			parameters_buffer = new ArrayBuffer(64 * 3 + 16);
			parameters = new Float32Array(parameters_buffer);
			parameters.set(ts.Matrix4x4f.perspective(60.0, window.width / window.height, 0.1, 1000.0).getArray());
			parameters.set(ts.Matrix4x4f.lookAt(camera_position, new ts.Vector3f.zero(), new ts.Vector3f(0.0, 0.0, 1.0)).getArray(), 16);
			parameters.set(ts.Matrix4x4f.rotateZ(time * 24.0).mul(ts.Matrix4x4f.rotateX(time * 16.0)).getArray(), 32);
			parameters.set(camera_position.getArray(), 48);
			
			// draw mesh
			command.setPipeline(render_pipeline);
			command.setUniform(0, parameters);
			command.setSampler(0, sampler);
			command.setTexture(0, texture);
			model.setBuffers(command);
			model.draw(command);
			
			// draw canvas
			canvas.draw(command, target);
			
			// destroy pointer
			command.destroyPtr();
			
		target.end();
		
		// present window
		if(!window.present()) return false;
		
		// check device
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	// destroy resources
	root.destroyPtr();
	
	// done
	ts.Log.print(ts.Log.Level.Message, "Done\n");
}

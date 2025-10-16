// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

import Tellusim

/*
 */
func create_mesh(_ steps: Vector2u,_ radius: Vector2f,_ texcoord: Float32) -> Mesh {
	
	// create mesh
	let mesh = Mesh()
	
	// create vertices
	let num_vertices = (steps.x + 1) * (steps.y + 1)
	let positions = MeshAttribute(MeshAttribute.Kind.Position, Format.RGBf32, num_vertices)
	let normals = MeshAttribute(MeshAttribute.Kind.Normal, Format.RGBf32, num_vertices)
	let tangents = MeshAttribute(MeshAttribute.Kind.Tangent, Format.RGBAf32, num_vertices)
	let texcoords = MeshAttribute(MeshAttribute.Kind.TexCoord, Format.RGf32, num_vertices)
	
	var vertex = UInt32(0)
	let isteps = Vector2f(1.0) / Vector2f(steps)
	let aspect = radius.x / radius.y
	for j in 0 ... steps.y {
		let ty = Float32(j) * isteps.y
		let z = -cos(ty * Pi2 - Pi05)
		let r = sin(ty * Pi2 - Pi05)
		for i in 0 ... steps.x {
			let tx = Float32(i) * isteps.x
			let x = -sin(tx * Pi2)
			let y = cos(tx * Pi2)
			positions.set(vertex, Vector3f(x * (r * radius.y + radius.x), y * (r * radius.y + radius.x), z * radius.y))
			normals.set(vertex, Vector3f(x * r, y * r, z))
			tangents.set(vertex, Vector4f(-y, x, 0.0, 1.0))
			texcoords.set(vertex, Vector2f(tx * aspect, ty) * texcoord)
			vertex += 1
		}
	}
	
	let basis = MeshAttribute(MeshAttribute.Kind.Basis, Format.RGBAu32, num_vertices)
	basis.packAttributes(normals, tangents, Format.RGBAf16)
	
	// create indices
	let num_indices = steps.x * steps.y * 4
	let indices_format = (num_vertices < Maxu16) ? Format.Ru16 : Format.Ru32
	let indices = MeshIndices(MeshIndices.Kind.Quadrilateral, indices_format, num_indices)
	
	var index = UInt32(0)
	for j in 0 ..< steps.y {
		for i in 0 ..< steps.x {
			vertex = (steps.x + 1) * j + i
			indices.set(index, vertex, vertex + 1, vertex + steps.x + 2, vertex + steps.x + 1)
			index += 4
		}
	}
	
	// create geometry
	let geometry = MeshGeometry(mesh)
	geometry.addAttribute(positions, indices)
	geometry.addAttribute(basis, indices)
	geometry.addAttribute(normals, indices)
	geometry.addAttribute(texcoords, indices)
	
	// geometry bounds
	let hsize = Vector3f(Vector2f(radius.x + radius.y), radius.y)
	geometry.setBoundBox(BoundBoxf(min: -hsize, max: hsize))
	
	// create bounds
	mesh.createBounds()
	
	return mesh
}

/*
 */
func create_image(_ size: UInt32,_ frame: UInt32) -> Image {
	
	// create image
	let image = Image()
	image.create2D(Format.RGBAu8n, size, Image.Flags.None)
	
	// create sampler
	let sampler = ImageSampler(image)
	
	// fill image
	for y in 0 ..< size {
		for x in 0 ..< size {
			let v = Float32(((Int32(x) - Int32(frame ^ y)) ^ (Int32(y) + Int32(frame ^ x))) & 255) / 63.0
			let r = UInt32(cos(Pi * 1.0 + v) * 127.5 + 127.5)
			let g = UInt32(cos(Pi * 0.5 + v) * 127.5 + 127.5)
			let b = UInt32(cos(Pi * 0.0 + v) * 127.5 + 127.5)
			sampler.set2D(x, y, ImageColor(r, g, b, 255))
		}
	}
	
	return image
}

/*
 */
func main_() -> Int32 {
	
	// create app
	let app = App()
	if !app.create(Platform.Any, UInt32(App.Values.Version.rawValue)) { return 1 }
	
	// create window
	let window = Window(app.platform(), app.device())
	if !window { return 1 }
	
	window.setSize(app.width(), app.height())
	window.setCloseClickedCallback(Window.CloseClickedFunction({() in window.stop() }))
	window.setKeyboardPressedCallback(Window.KeyboardPressedFunction({ (key: UInt32, code: UInt32) in
		if key == Window.Key.Esc.rawValue { window.stop() }
		if key == Window.Key.F12.rawValue {
			let image = Image()
			if window.grab(image) && image.save("screenshot.png") {
				Log.print(Log.Level.Message, "Screenshot\n")
			}
		}
	}))
	
	let title = window.platformName() + " Tellusim::Swift"
	if !window.create(title) || !window.setHidden(false) { return 1 }
	
	// create device
	let device = Device(window)
	if !device { return 1 }
	
	// device features
	Log.print(Log.Level.Message, "Features: \(device.features())\n")
	Log.print(Log.Level.Message, "Device: \(device.name())\n")
	
	// build info
	Log.print(Log.Level.Message, "Build: \(App.buildInfo())\n")
	
	// create target
	let target = device.createTarget(window)
	if !target { return 1 }
	
	////////////////////////////////
	// core test
	////////////////////////////////
	
	let blob = Blob()
	blob.writeString(title)
	
	blob.seek(0)
	Log.print(Log.Level.Message, "Stream: \(blob.readString())\n")
	
	////////////////////////////////
	// bounds test
	////////////////////////////////
	
	// 32-bit floating point
	var bound_boxf = BoundBoxf(-Vector3f.one, Vector3f.one)
	var bound_spheref = BoundSpheref(bound_boxf)
	let bound_frustumf = BoundFrustumf(Matrix4x4f.perspective(60.0, 1.0, 0.1, 1000.0), Matrix4x4f.lookAt(Vector3f.one, Vector3f.zero, Vector3f(0.0, 0.0, 1.0)))
	Log.print(Log.Level.Message, "\(bound_boxf) \(bound_frustumf.inside(bound_boxf)) \(bound_spheref) \(bound_frustumf.inside(bound_spheref))\n")
	bound_boxf = Matrix4x3f.translate(10.0, 0.0, 0.0) * bound_boxf
	bound_spheref = Matrix4x4f.translate(10.0, 0.0, 0.0) * bound_spheref
	Log.print(Log.Level.Message, "\(bound_boxf) \(bound_frustumf.inside(bound_boxf)) \(bound_spheref) \(bound_frustumf.inside(bound_spheref))\n")
	
	// 64-bit floating point
	var bound_boxd = BoundBoxd(-Vector3d.one, Vector3d.one)
	var bound_sphered = BoundSphered(bound_boxd)
	let bound_frustumd = BoundFrustumd(Matrix4x4d.perspective(60.0, 1.0, 0.1, 1000.0), Matrix4x4d.lookAt(Vector3d.one, Vector3d.zero, Vector3d(0.0, 0.0, 1.0)))
	Log.print(Log.Level.Message, "\(bound_boxd) \(bound_frustumd.inside(bound_boxd)) \(bound_sphered) \(bound_frustumd.inside(bound_sphered))\n")
	bound_boxd = Matrix4x3d.translate(10.0, 0.0, 0.0) * bound_boxd
	bound_sphered = Matrix4x4d.translate(10.0, 0.0, 0.0) * bound_sphered
	Log.print(Log.Level.Message, "\(bound_boxd) \(bound_frustumd.inside(bound_boxd)) \(bound_sphered) \(bound_frustumd.inside(bound_sphered))\n")
	
	////////////////////////////////
	// platform test
	////////////////////////////////
	
	// create pipeline
	let pipeline = device.createPipeline()
	pipeline.setUniformMask(0, Shader.Mask.Fragment)
	pipeline.setColorFormat(window.colorFormat())
	pipeline.setDepthFormat(window.depthFormat())
	pipeline.setDepthMask(Pipeline.DepthMask.None)
	pipeline.addAttribute(Pipeline.Attribute.Position, Format.RGf32, 0, 0, 8)
	if !pipeline.loadShaderGLSL(Shader.Kind.Vertex, "main.shader", "VERTEX_SHADER=1") { return 1 }
	if !pipeline.loadShaderGLSL(Shader.Kind.Fragment, "main.shader", "FRAGMENT_SHADER=1") { return 1 }
	if !pipeline.create() { return 1 }
	
	// geometry vertices
	var vertices: [Vector2f] = [ Vector2f(3.0, -1.0), Vector2f(-1.0, -1.0), Vector2f(-1.0, 3.0) ]
	
	// geometry indices
	var indices: [UInt16] = [ 0, 1, 2 ]
	
	////////////////////////////////
	// interface test
	////////////////////////////////
	
	// create canvas
	let canvas = Canvas()
	
	// create root controls
	let root = ControlRoot(canvas, true)
	root.setFontSize(24)
	
	// create dialog
	let dialog = ControlDialog(root, 1, 8.0, 8.0)
	dialog.setUpdatedCallback(ControlDialog.UpdatedFunction({ (dialog: ControlDialog) in
		let x = dialog.positionX()
		let y = dialog.positionY()
		let width = dialog.width()
		let height = dialog.height()
		Log.printf(Log.Level.Message, "Dialog Updated %.0f %.0f %.0fx%.0f\n", x, y, width, height)
	}))
	dialog.setAlign(Control.Align.Center)
	dialog.setSize(240.0, 180.0)
	
	// create text
	let text = ControlText(dialog, title)
	text.setAlign(Control.Align.CenterX)
	
	// create button
	let button = ControlButton(dialog, "Button")
	button.setClickedCallback(ControlButton.ClickedFunction({ (button: ControlButton) in
		Log.print(Log.Level.Message, "\(button.text()) Clicked\n")
	}))
	button.setAlign(Control.Align.Expand)
	button.setMargin(0.0, 0.0, 0.0, 16.0)
	
	// common parameters
	struct CommonParameters {
		var transform: Matrix4x4f
		var color: Color
		var time: Float32
	}
	var parameters = CommonParameters(
		transform: Matrix4x4f.identity,
		color: Color(1.0),
		time: 0.0
	)
	
	// create sliders
	let slider_r = ControlSlider(dialog, "R", 2, Float64(parameters.color.r), 0.0, 1.0)
	let slider_g = ControlSlider(dialog, "G", 2, Float64(parameters.color.g), 0.0, 1.0)
	let slider_b = ControlSlider(dialog, "B", 2, Float64(parameters.color.b), 0.0, 1.0)
	slider_r.setChangedCallback(ControlSlider.ChangedFunction({ (slider: ControlSlider) in parameters.color.r = slider.valuef32() }))
	slider_g.setChangedCallback(ControlSlider.ChangedFunction({ (slider: ControlSlider) in parameters.color.g = slider.valuef32() }))
	slider_b.setChangedCallback(ControlSlider.ChangedFunction({ (slider: ControlSlider) in parameters.color.b = slider.valuef32() }))
	slider_r.setAlign(Control.Align.ExpandX)
	slider_g.setAlign(Control.Align.ExpandX)
	slider_b.setAlign(Control.Align.ExpandX)
	
    ////////////////////////////////
	// render test
	////////////////////////////////
	
	// vertex shader
	let vertex_shader = """
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
	"""
	
	// fragment shader
	let fragment_shader = """
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
	"""
	
	// create render pipeline
	let render_pipeline = device.createPipeline()
	render_pipeline.setUniformMask(0, Shader.Mask.Vertex)
	render_pipeline.setTextureMask(0, Shader.Mask.Fragment)
	render_pipeline.setSamplerMask(0, Shader.Mask.Fragment)
	render_pipeline.setColorFormat(window.colorFormat())
	render_pipeline.setDepthFormat(window.depthFormat())
	render_pipeline.setDepthFunc(Pipeline.DepthFunc.LessEqual)
	render_pipeline.addAttribute(Pipeline.Attribute.Position, Format.RGBf32, 0, 0, 32)
	render_pipeline.addAttribute(Pipeline.Attribute.Normal, Format.RGBf32, 0, 12, 32)
	render_pipeline.addAttribute(Pipeline.Attribute.TexCoord, Format.RGf32, 0, 24, 32)
	if !render_pipeline.createShaderGLSL(Shader.Kind.Vertex, vertex_shader) { return 1 }
	if !render_pipeline.createShaderGLSL(Shader.Kind.Fragment, fragment_shader) { return 1 }
	if !render_pipeline.create() { return 1 }
	
	// create mesh
	let mesh = create_mesh(Vector2u(64, 32), Vector2f(8.0, 2.0), 2.0)
	
	// create model
	let model = MeshModel()
	if !model.create(device, render_pipeline, mesh) { return 1 }
	
	// create sampler
	let sampler = device.createSampler(Sampler.Filter.Linear, Sampler.WrapMode.Repeat)
	if !sampler { return 1 }
	
	// create texture
	let texture_image = create_image(256, 0)
	let texture = device.createTexture(texture_image)
	if !texture { return 1 }
	
	////////////////////////////////
	// main loop
	////////////////////////////////
	
    var texture_frame = UInt32(0)
	let texture_ifps = 1.0 / 30.0
	var texture_time = Time.seconds()
	
	// main loop
	window.run(Window.MainLoopFunction({ () -> Bool in
		
		// update window
		Window.update()
		
		// render window
		if !window.render() { return false }
		
        // update texture
		if Time.seconds() - texture_time > texture_ifps {
			texture_time += texture_ifps
			let image = create_image(256, texture_frame)
		    device.setTexture(texture, image)
			texture_frame += 1
		}
		
		// update interface
		if true {
			
			// window size
			let height = Float32(app.height())
			let width = floor(height * Float32(window.width()) / Float32(window.height()))
			let mouse_x = width * Float32(window.mouseX()) / Float32(window.width())
			let mouse_y = height * Float32(window.mouseY()) / Float32(window.height())
			
			// mouse button
			var buttons = Control.Button.None
			if (window.mouseButtons() & Window.Button.Left) != Window.Button.None { buttons |= Control.Button.Left }
			if (window.mouseButtons() & Window.Button.Left2) != Window.Button.None { buttons |= Control.Button.Left }
			
			// update controls
			root.setViewport(width, height)
			root.setMouse(mouse_x, mouse_y, buttons)
			while root.update(canvas.scale(target)) { }
			
			// create canvas
			canvas.create(device, target)
		}
		
		// window target
		if target.begin() {
			
			let command = device.createCommand(target)
			
			// current time
			let time = Float32(Time.seconds())
			
			// common parameters
			parameters.transform = Matrix4x4f.rotateZ(time * 16.0)
			parameters.time = time
			
			// draw background
			command.setPipeline(pipeline)
			command.setUniform(0, &parameters)
			command.setVertices(0, &vertices)
			command.setIndices(&indices)
			command.drawElements(3)
			
            // render parameters
			struct RenderParameters {
				var projection: Matrix4x4f
				var modelview: Matrix4x4f
				var transform: Matrix4x4f
				var camera: Vector3f
			}
			let camera = Vector3f(12.0, 12.0, 6.0)
			var render_parameters = RenderParameters(
				projection: Matrix4x4f.perspective(60.0, Float32(window.width()) / Float32(window.height()), 0.1, 1000.0),
			    modelview: Matrix4x4f.lookAt(camera, Vector3f.zero, Vector3f(0.0, 0.0, 1.0)),
			    transform: Matrix4x4f.rotateZ(time * 24.0) * Matrix4x4f.rotateX(time * 16.0),
				camera: camera
			)
			
			// draw mesh
			command.setPipeline(render_pipeline)
			command.setUniform(0, &render_parameters)
			command.setSampler(0, sampler)
			command.setTexture(0, texture)
			model.setBuffers(command)
			model.draw(command)
			
			// draw canvas
			canvas.draw(command, target)
		}
		target.end()
		
		// present window
		if !window.present() { return false }
		
		// check device
		if !device.check() { return false }
		
		return true
	}))
	
	// finish context
	window.finish()
	
	// destroy resources
	root.destroyPtr()
	
	// done
	Log.print(Log.Level.Message, "Done\n")
	
	return 0
}

/*
 */
#if IOS
	
	import UIKit
	
	class AppDelegate: UIResponder, UIApplicationDelegate {
		
		func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
			Log.print(Log.Level.Verbose, "didFinishLaunchingWithOptions(): is called\n")
			DispatchQueue.main.asyncAfter(deadline: .now() + 0.1) {
				chdir(Bundle.main.bundlePath)
				Log.printf(Log.Level.Message, "main: %d\n", main_())
			}
			return true
		}
		
		func applicationWillResignActive(_ application: UIApplication) {
			Log.print(Log.Level.Verbose, "applicationWillResignActive(): is called\n")
		}
		
		func applicationDidEnterBackground(_ application: UIApplication) {
			Log.print(Log.Level.Verbose, "applicationDidEnterBackground(): is called\n")
		}
		
		func applicationWillEnterForeground(_ application: UIApplication) {
			Log.print(Log.Level.Verbose, "applicationWillEnterForeground(): is called\n")
		}
		
		func applicationDidBecomeActive(_ application: UIApplication) {
			Log.print(Log.Level.Verbose, "applicationDidBecomeActive(): is called\n")
		}
	}
	
	UIApplicationMain(CommandLine.argc, CommandLine.unsafeArgv, nil, NSStringFromClass(AppDelegate.self))
	
#else
	
	Log.printf(Log.Level.Message, "main: %d\n", main_())
	
#endif

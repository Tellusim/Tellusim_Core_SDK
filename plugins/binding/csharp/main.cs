// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

using System;
using Tellusim;
using System.Threading;
using System.Runtime.InteropServices;

/*
 */
class CSharp {
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct CommonParameters {
		public Matrix4x4f transform;
		public Color color;
		public float time;
	}
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct RenderParameters {
		public Matrix4x4f projection;
		public Matrix4x4f modelview;
		public Matrix4x4f transform;
		public Vector3f camera;
	}
	
	/*
	 */
	static Mesh create_mesh(in Vector2u steps, in Vector2f radius, float texcoord) {
		
		// create mesh
		Mesh mesh = new Mesh();
		
		// create vertices
		uint num_vertices = (steps.x + 1) * (steps.y + 1);
		MeshAttribute positions = new MeshAttribute(MeshAttribute.Type.Position, Format.RGBf32, num_vertices);
		MeshAttribute normals = new MeshAttribute(MeshAttribute.Type.Normal, Format.RGBf32, num_vertices);
		MeshAttribute tangents = new MeshAttribute(MeshAttribute.Type.Tangent, Format.RGBAf32, num_vertices);
		MeshAttribute texcoords = new MeshAttribute(MeshAttribute.Type.TexCoord, Format.RGf32, num_vertices);
		
		uint vertex = 0;
		Vector2f isteps = new Vector2f(1.0f) / new Vector2f(steps);
		float aspect = radius.x / radius.y;
		for(uint j = 0; j <= steps.y; j++) {
			float ty = j * isteps.y;
			float z = -(float)Math.Cos(ty * Base.Pi2 - Base.Pi05);
			float r = (float)Math.Sin(ty * Base.Pi2 - Base.Pi05);
			for(uint i = 0; i <= steps.x; i++) {
				float tx = i * isteps.x;
				float x = -(float)Math.Sin(tx * Base.Pi2);
				float y = (float)Math.Cos(tx * Base.Pi2);
				positions.set(vertex, new Vector3f(x * (r * radius.y + radius.x), y * (r * radius.y + radius.x), z * radius.y));
				normals.set(vertex, new Vector3f(x * r, y * r, z));
				tangents.set(vertex, new Vector4f(-y, x, 0.0f, 1.0f));
				texcoords.set(vertex, new Vector2f(tx * aspect, ty) * texcoord);
				vertex++;
			}
		}
		
		MeshAttribute basis = new MeshAttribute(MeshAttribute.Type.Basis, Format.RGBAu32, num_vertices);
		basis.packAttributes(normals, tangents, Format.RGBAf16);
		
		// create indices
		uint num_indices = steps.x * steps.y * 4;
		Format indices_format = (num_vertices < Base.Maxu16) ? Format.Ru16 : Format.Ru32;
		MeshIndices indices = new MeshIndices(MeshIndices.Type.Quadrilateral, indices_format, num_indices);
		
		uint index = 0;
		for(uint j = 0; j < steps.y; j++) {
			for(uint i = 0; i < steps.x; i++) {
				vertex = (steps.x + 1) * j + i;
				indices.set(index, vertex, vertex + 1, vertex + steps.x + 2, vertex + steps.x + 1);
				index += 4;
			}
		}
		
		// create geometry
		MeshGeometry geometry = new MeshGeometry(mesh);
		geometry.addAttribute(positions, indices);
		geometry.addAttribute(basis, indices);
		geometry.addAttribute(normals, indices);
		geometry.addAttribute(texcoords, indices);
		
		// geometry bounds
		Vector3f hsize = new Vector3f(new Vector2f(radius.x + radius.y), radius.y);
		geometry.setBoundBox(new BoundBoxf(-hsize, hsize));
		
		// create bounds
		mesh.createBounds();
		
		return mesh;
	}
	
	/*
	 */
	static Image create_image(uint size, uint frame) {
		
		// create image
		Image image = new Image();
		image.create2D(Format.RGBAu8n, size);
		
		// create sampler
		ImageSampler sampler = new ImageSampler(image, new Layer(0));
		
		// fill image
		ImageColor color = new ImageColor(255);
		for(uint y = 0; y < size; y++) {
			for(uint x = 0; x < size; x++) {
				float v = (float)(((x - (frame ^ y)) ^ (y + (frame ^ x))) & 255) / 63.0f;
				color.r = (uint)(Math.Cos(Base.Pi * 1.0f + v) * 127.5f + 127.5f);
				color.g = (uint)(Math.Cos(Base.Pi * 0.5f + v) * 127.5f + 127.5f);
				color.b = (uint)(Math.Cos(Base.Pi * 0.0f + v) * 127.5f + 127.5f);
				sampler.set2D(x, y, color);
			}
		}
		
		return image;
	}
	
	/*
	 */
	[STAThread]
	static void Main(string[] args) {
		
		// create app
		App app = new App(args);
		if(!app.create(Platform.Any)) return;
		
		// create window
		Window window = new Window(app.getPlatform(), app.getDevice());
		if(!window) return;
		
		window.setSize(app.getWidth(), app.getHeight());
		window.setCloseClickedCallback((IntPtr data) => { window.stop(); });
		window.setKeyboardPressedCallback((uint key, uint code, IntPtr data) => {
			if(key == (uint)Window.Key.Esc) window.stop();
			if(key == (uint)Window.Key.F12) {
				Image image = new Image();
				if(window.grab(image) && image.save("screenshot.png")) {
					Log.printf(Log.Level.Message, "Screenshot\n");
				}
			}
		});
		
		string title = window.getPlatformName() + " Tellusim::CSharp";
		if(!window.create(title, Window.Flags.Default | Window.Flags.VerticalSync) || !window.setHidden(false)) return;
		
		// create device
		Device device = new Device(window);
		if(!device) return;
		
		// device features
		Log.printf(Log.Level.Message, "Features:\n{0}\n", device.getFeatures().ToString());
		Log.printf(Log.Level.Message, "Device: {0}\n", device.getName());
		
		// build info
		Log.printf(Log.Level.Message, "Build: {0}\n", App.getBuildInfo());
		
		// create target
		Target target = device.createTarget(window);
		if(!target) return;
		
		////////////////////////////////
		// core test
		////////////////////////////////
		
		Blob blob = new Blob();
		blob.writeString(title);
		
		blob.seek(0);
		Log.printf(Log.Level.Message, "Stream: {0}\n", blob.readString());
		
		////////////////////////////////
		// bounds test
		////////////////////////////////
		
		// 32-bit floating point
		BoundBoxf bound_boxf = new BoundBoxf(-Vector3f.one, Vector3f.one);
		BoundSpheref bound_spheref = new BoundSpheref(bound_boxf);
		BoundFrustumf bound_frustumf = new BoundFrustumf(Matrix4x4f.perspective(60.0f, 1.0f, 0.1f, 1000.0f), Matrix4x4f.lookAt(Vector3f.one, Vector3f.zero, new Vector3f(0.0f, 0.0f, 1.0f)));
		Log.printf(Log.Level.Message, "{0} {1} {2} {3}\n", bound_boxf, bound_frustumf.inside(bound_boxf), bound_spheref, bound_frustumf.inside(bound_spheref));
		bound_boxf = Matrix4x3f.translate(10.0f, 0.0f, 0.0f) * bound_boxf;
		bound_spheref = Matrix4x4f.translate(10.0f, 0.0f, 0.0f) * bound_spheref;
		Log.printf(Log.Level.Message, "{0} {1} {2} {3}\n", bound_boxf, bound_frustumf.inside(bound_boxf), bound_spheref, bound_frustumf.inside(bound_spheref));
		
		// 64-bit floating point
		BoundBoxd bound_boxd = new BoundBoxd(-Vector3d.one, Vector3d.one);
		BoundSphered bound_sphered = new BoundSphered(bound_boxd);
		BoundFrustumd bound_frustumd = new BoundFrustumd(Matrix4x4d.perspective(60.0, 1.0, 0.1, 1000.0), Matrix4x4d.lookAt(Vector3d.one, Vector3d.zero, new Vector3d(0.0, 0.0, 1.0)));
		Log.printf(Log.Level.Message, "{0} {1} {2} {3}\n", bound_boxd, bound_frustumd.inside(bound_boxd), bound_sphered, bound_frustumd.inside(bound_sphered));
		bound_boxd = Matrix4x3d.translate(10.0, 0.0, 0.0) * bound_boxd;
		bound_sphered = Matrix4x4d.translate(10.0, 0.0, 0.0) * bound_sphered;
		Log.printf(Log.Level.Message, "{0} {1} {2} {3}\n", bound_boxd, bound_frustumd.inside(bound_boxd), bound_sphered, bound_frustumd.inside(bound_sphered));
		
		////////////////////////////////
		// platform test
		////////////////////////////////
		
		// create pipeline
		Pipeline pipeline = device.createPipeline();
		pipeline.setUniformMask(0, Shader.Mask.Fragment);
		pipeline.setColorFormat(window.getColorFormat());
		pipeline.setDepthFormat(window.getDepthFormat());
		pipeline.setDepthMask(Pipeline.DepthMask.None);
		pipeline.addAttribute(Pipeline.Attribute.Position, Format.RGf32, 0, 0, 8);
		if(!pipeline.loadShaderGLSL(Shader.Type.Vertex, "main.shader", "VERTEX_SHADER=1")) return;
		if(!pipeline.loadShaderGLSL(Shader.Type.Fragment, "main.shader", "FRAGMENT_SHADER=1")) return;
		if(!pipeline.create()) return;
		
		// geometry vertices
		Vector2f[] vertices = new Vector2f[] { new Vector2f(3.0f, -1.0f), new Vector2f(-1.0f, -1.0f), new Vector2f(-1.0f, 3.0f) };
		
		// geometry indices
		short[] indices = new short[] { 0, 1, 2 };
		
		////////////////////////////////
		// interface test
		////////////////////////////////
		
		// create canvas
		Canvas canvas = new Canvas();
		
		// create root controls
		ControlRoot root = new ControlRoot(canvas, true);
		root.setFontSize(24);
		
		// create dialog
		ControlDialog dialog = new ControlDialog(root, 1, 8.0f, 8.0f);
		dialog.setUpdatedCallback((ControlDialog dialog_, IntPtr data) => {
			float x = dialog_.getPositionX();
			float y = dialog_.getPositionY();
			float width = dialog_.getWidth();
			float height = dialog_.getHeight();
			Log.printf(Log.Level.Message, "Dialog Updated {0} {1} {2}x{3}\n", x, y, width, height);
		});
		dialog.setAlign(Control.Align.Center);
		dialog.setSize(240.0f, 180.0f);
		
		// create text
		ControlText text = new ControlText(dialog, title);
		text.setAlign(Control.Align.CenterX);
		
		// create button
		ControlButton button = new ControlButton(dialog, "Button");
		button.setClickedCallback((ControlButton button_, IntPtr data) => {
			Log.printf(Log.Level.Message, "{0} Clicked\n", button_.getText());
		});
		button.setAlign(Control.Align.Expand);
		button.setMargin(0.0f, 0.0f, 0.0f, 16.0f);
		
		// common parameters
		CommonParameters parameters = new CommonParameters();
		parameters.color = Color.white;
		
		// create sliders
		ControlSlider slider_r = new ControlSlider(dialog, "R", 2, parameters.color.r, 0.0, 1.0);
		ControlSlider slider_g = new ControlSlider(dialog, "G", 2, parameters.color.g, 0.0, 1.0);
		ControlSlider slider_b = new ControlSlider(dialog, "B", 2, parameters.color.b, 0.0, 1.0);
		slider_r.setChangedCallback((ControlSlider slider, IntPtr data) => { parameters.color.r = slider.getValuef32(); });
		slider_g.setChangedCallback((ControlSlider slider, IntPtr data) => { parameters.color.g = slider.getValuef32(); });
		slider_b.setChangedCallback((ControlSlider slider, IntPtr data) => { parameters.color.b = slider.getValuef32(); });
		slider_r.setFormatCallback((ControlSlider slider, IntPtr data) => { return "Value " + Tellusim.String.fromf32(slider.getValuef32(), 2); });
		slider_g.setFormatCallback((ControlSlider slider, IntPtr data) => { return "Value " + Tellusim.String.fromf32(slider.getValuef32(), 2); });
		slider_b.setFormatCallback((ControlSlider slider, IntPtr data) => { return "Value " + Tellusim.String.fromf32(slider.getValuef32(), 2); });
		slider_r.setAlign(Control.Align.ExpandX);
		slider_g.setAlign(Control.Align.ExpandX);
		slider_b.setAlign(Control.Align.ExpandX);
		
		////////////////////////////////
		// render test
		////////////////////////////////
		
		// vertex shader
		string vertex_shader = @"
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
		";
		
		// fragment shader
		string fragment_shader = @"
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
		";
		
		// create render pipeline
		Pipeline render_pipeline = device.createPipeline();
		render_pipeline.setUniformMask(0, Shader.Mask.Vertex);
		render_pipeline.setTextureMask(0, Shader.Mask.Fragment);
		render_pipeline.setSamplerMask(0, Shader.Mask.Fragment);
		render_pipeline.setColorFormat(window.getColorFormat());
		render_pipeline.setDepthFormat(window.getDepthFormat());
		render_pipeline.setDepthFunc(Pipeline.DepthFunc.LessEqual);
		render_pipeline.addAttribute(Pipeline.Attribute.Position, Format.RGBf32, 0, 0, 32);
		render_pipeline.addAttribute(Pipeline.Attribute.Normal, Format.RGBf32, 0, 12, 32);
		render_pipeline.addAttribute(Pipeline.Attribute.TexCoord, Format.RGf32, 0, 24, 32);
		if(!render_pipeline.createShaderGLSL(Shader.Type.Vertex, vertex_shader)) return;
		if(!render_pipeline.createShaderGLSL(Shader.Type.Fragment, fragment_shader)) return;
		if(!render_pipeline.create()) return;
		
		// create mesh
		Mesh mesh = create_mesh(new Vector2u(64, 32), new Vector2f(8.0f, 2.0f), 2.0f);
		
		// create model
		MeshModel model = new MeshModel();
		if(!model.create(device, render_pipeline, mesh)) return;
		
		// create sampler
		Sampler sampler = device.createSampler(Sampler.Filter.Linear, Sampler.WrapMode.Repeat);
		if(!sampler) return;
		
		// create texture
		Image texture_image = create_image(256, 0);
		Texture texture = device.createTexture(texture_image);
		if(!texture) return;
		
		////////////////////////////////
		// main loop
		////////////////////////////////
		
		uint texture_frame = 0;
		double texture_ifps = 1.0 / 30.0;
		double texture_time = Time.seconds();
		
		// main loop
		window.run((IntPtr data) => {
			
			// update window
			Window.update();
			
			// render window
			if(!window.render()) return false;
			
			// update texture
			if(Time.seconds() - texture_time > texture_ifps) {
				texture_time += texture_ifps;
				texture_image = create_image(256, texture_frame);
				device.setTexture(texture, texture_image);
				texture_frame++;
			}
			
			// update interface
			{
				// window size
				float height = app.getHeight();
				float width = (float)Math.Floor(height * window.getWidth() / window.getHeight());
				float mouse_x = width * window.getMouseX() / window.getWidth();
				float mouse_y = height * window.getMouseY() / window.getHeight();
				
				// mouse button
				Control.Button buttons = Control.Button.None;
				if((window.getMouseButtons() & Window.Button.Left) != Window.Button.None) buttons |= Control.Button.Left;
				if((window.getMouseButtons() & Window.Button.Left2) != Window.Button.None) buttons |= Control.Button.Left;
				
				// update controls
				root.setViewport(width, height);
				root.setMouse(mouse_x, mouse_y, buttons);
				while(root.update(canvas.getScale(target))) { }
				
				// create canvas
				canvas.create(device, target);
			}
			
			// window target
			target.begin();
			{
				Command command = device.createCommand(target);
				
				// common parameters
				float time = (float)Time.seconds();
				parameters.transform = Matrix4x4f.rotateZ(time * 16.0f);
				parameters.time = time;
				
				// draw background
				command.setPipeline(pipeline);
				command.setUniform(0, parameters);
				command.setVertices(0, vertices);
				command.setIndices(indices);
				command.drawElements(3);
				
				// render parameters
				RenderParameters render_parameters = new RenderParameters();
				render_parameters.camera = new Vector3f(12.0f, 12.0f, 6.0f);
				render_parameters.projection = Matrix4x4f.perspective(60.0f, (float)window.getWidth() / (float)window.getHeight(), 0.1f, 1000.0f);
				render_parameters.modelview = Matrix4x4f.lookAt(render_parameters.camera, Vector3f.zero, new Vector3f(0.0f, 0.0f, 1.0f));
				render_parameters.transform = Matrix4x4f.rotateZ(time * 24.0f) * Matrix4x4f.rotateX(time * 16.0f);
				
				// draw mesh
				command.setPipeline(render_pipeline);
				command.setUniform(0, render_parameters);
				command.setSampler(0, sampler);
				command.setTexture(0, texture);
				model.setBuffers(command);
				model.draw(command);
				
				// draw canvas
				canvas.draw(command, target);
				
				command.destroyPtr();
			}
			target.end();
			
			// present window
			if(!window.present()) return false;
			
			// check device
			if(!device.check()) return false;
			
			// memory
			GC.Collect();
			GC.WaitForPendingFinalizers();
			
			return true;
		});
		
		// finish context
		window.finish();
		
		// destroy resources
		root.destroyPtr();
		
		// keep window alive
		window.unacquirePtr();
		
		// done
		Log.print(Log.Level.Message, "Done\n");
	}
}

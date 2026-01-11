// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.main;

import com.tellusim.*;

import java.lang.Math;
import java.nio.ByteOrder;
import java.nio.ByteBuffer;

/*
 */
public class main {
	
	/*
	 */
	static {
		Base.loadDebug();
	}
	
	/*
	 */
	static Mesh create_mesh(Vector2i steps, Vector2f radius, float texcoord) {
		
		// create mesh
		Mesh mesh = new Mesh();
		
		// create vertices
		int num_vertices = (steps.x() + 1) * (steps.y() + 1);
		MeshAttribute positions = new MeshAttribute(MeshAttribute.Type.Position, Format.RGBf32, num_vertices);
		MeshAttribute normals = new MeshAttribute(MeshAttribute.Type.Normal, Format.RGBf32, num_vertices);
		MeshAttribute tangents = new MeshAttribute(MeshAttribute.Type.Tangent, Format.RGBAf32, num_vertices);
		MeshAttribute texcoords = new MeshAttribute(MeshAttribute.Type.TexCoord, Format.RGf32, num_vertices);
		
		int vertex = 0;
		Vector2f isteps = (new Vector2f(1.0f)).div(new Vector2f(steps));
		float aspect = radius.x() / radius.y();
		for(int j = 0; j <= steps.y(); j++) {
			float ty = j * isteps.y();
			float z = -(float)Math.cos(ty * Base.Pi2 - Base.Pi05);
			float r = (float)Math.sin(ty * Base.Pi2 - Base.Pi05);
			for(int i = 0; i <= steps.x(); i++) {
				float tx = i * isteps.x();
				float x = -(float)Math.sin(tx * Base.Pi2);
				float y = (float)Math.cos(tx * Base.Pi2);
				positions.set(vertex, new Vector3f(x * (r * radius.y() + radius.x()), y * (r * radius.y() + radius.x()), z * radius.y()));
				normals.set(vertex, new Vector3f(x * r, y * r, z));
				tangents.set(vertex, new Vector4f(-y, x, 0.0f, 1.0f));
				texcoords.set(vertex, (new Vector2f(tx * aspect, ty)).mul(texcoord));
				vertex++;
			}
		}
		
		MeshAttribute basis = new MeshAttribute(MeshAttribute.Type.Basis, Format.RGBAu32, num_vertices);
		basis.packAttributes(normals, tangents, Format.RGBAf16);
		
		// create indices
		int num_indices = steps.x() * steps.y() * 4;
		Format.Enum indices_format = (num_vertices < Base.Maxu16) ? Format.Ru16 : Format.Ru32;
		MeshIndices indices = new MeshIndices(MeshIndices.Type.Quadrilateral, indices_format, num_indices);
		
		int index = 0;
		for(int j = 0; j < steps.y(); j++) {
			for(int i = 0; i < steps.x(); i++) {
				vertex = (steps.x() + 1) * j + i;
				indices.set(index, vertex, vertex + 1, vertex + steps.x() + 2, vertex + steps.x() + 1);
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
		Vector3f hsize = new Vector3f(new Vector2f(radius.x() + radius.y()), radius.y());
		geometry.setBoundBox(new BoundBoxf(hsize.neg(), hsize));
		
		// create bounds
		mesh.createBounds();
		
		return mesh;
	}
	
	/*
	 */
	static Image create_image(int size, int frame) {
		
		// create image
		Image image = new Image();
		image.create2D(Format.RGBAu8n, size);
		
		// create sampler
		ImageSampler sampler = new ImageSampler(image, new Slice());
		
		// fill image
		ImageColor color = new ImageColor(255);
		for(int y = 0; y < size; y++) {
			for(int x = 0; x < size; x++) {
				float v = (float)(((x - (frame ^ y)) ^ (y + (frame ^ x))) & 255) / 63.0f;
				color.setR((int)(Math.cos(Base.Pi * 1.0f + v) * 127.5f + 127.5f));
				color.setG((int)(Math.cos(Base.Pi * 0.5f + v) * 127.5f + 127.5f));
				color.setB((int)(Math.cos(Base.Pi * 0.0f + v) * 127.5f + 127.5f));
				sampler.set2D(x, y, color);
			}
		}
		
		return image;
	}
	
	/*
	 */
	public static void main(String[] args) {
		
		// create app
		App app = new App(args);
		if(!app.create(Platform.Any)) return;
		
		// create window
		Window window = new Window(app.getPlatform(), app.getDevice());
		if(!window.isValidPtr()) return;
		
		window.setSize(app.getWidth(), app.getHeight());
		window.setCloseClickedCallback(new Window.CloseClickedCallback() {
			public void run() { window.stop(); }
		});
		window.setKeyboardPressedCallback(new Window.KeyboardPressedCallback() {
			public void run(int key, int code) {
				if(key == Window.Key.Esc.value) window.stop();
				if(key == Window.Key.F12.value) {
					Image image = new Image();
					if(window.grab(image) && image.save("screenshot.png")) {
						Log.print(Log.Level.Message, "Screenshot\n");
					}
				}
			}
		});
		
		String title = window.getPlatformName() + " Tellusim::Java";
		if(!window.create(title, Window.Flags.Default.or(Window.Flags.VerticalSync)) || !window.setHidden(false)) return;
		
		// create device
		Device device = new Device(window);
		if(!device.isValidPtr()) return;
		
		// device features
		Log.printf(Log.Level.Message, "Features:\n%s\n", device.getFeatures());
		Log.printf(Log.Level.Message, "Device: %s\n", device.getName());
		
		// build info
		Log.printf(Log.Level.Message, "Build: %s\n", app.getBuildInfo());
		
		// create target
		Target target = device.createTarget(window);
		if(!target.isValidPtr()) return;
		
		////////////////////////////////
		// core test
		////////////////////////////////
		
		Blob blob = new Blob();
		blob.writeString(title);
		
		blob.seek(0);
		Log.printf(Log.Level.Message, "Stream: %s\n", blob.readString());
		
		////////////////////////////////
		// bounds test
		////////////////////////////////
		
		// 32-bit floating point
		BoundBoxf bound_boxf = new BoundBoxf(Vector3f.one().neg(), Vector3f.one());
		BoundSpheref bound_spheref = new BoundSpheref(bound_boxf);
		BoundFrustumf bound_frustumf = new BoundFrustumf(Matrix4x4f.perspective(60.0f, 1.0f, 0.1f, 1000.0f), Matrix4x4f.lookAt(Vector3f.one(), Vector3f.zero(), new Vector3f(0.0f, 0.0f, 1.0f)));
		Log.printf(Log.Level.Message, "%s %b %s %b\n", bound_boxf.toString(), bound_frustumf.inside(bound_boxf), bound_spheref.toString(), bound_frustumf.inside(bound_spheref));
		bound_boxf = Matrix4x3f.translate(10.0f, 0.0f, 0.0f).mul(bound_boxf);
		bound_spheref = Matrix4x4f.translate(10.0f, 0.0f, 0.0f).mul(bound_spheref);
		Log.printf(Log.Level.Message, "%s %b %s %b\n", bound_boxf.toString(), bound_frustumf.inside(bound_boxf), bound_spheref.toString(), bound_frustumf.inside(bound_spheref));
		
		// 64-bit floating point
		BoundBoxd bound_boxd = new BoundBoxd(Vector3d.one().neg(), Vector3d.one());
		BoundSphered bound_sphered = new BoundSphered(bound_boxd);
		BoundFrustumd bound_frustumd = new BoundFrustumd(Matrix4x4d.perspective(60.0, 1.0, 0.1, 1000.0), Matrix4x4d.lookAt(Vector3d.one(), Vector3d.zero(), new Vector3d(0.0, 0.0, 1.0)));
		Log.printf(Log.Level.Message, "%s %b %s %b\n", bound_boxd.toString(), bound_frustumd.inside(bound_boxd), bound_sphered.toString(), bound_frustumd.inside(bound_sphered));
		bound_boxd = Matrix4x3d.translate(10.0, 0.0, 0.0).mul(bound_boxd);
		bound_sphered = Matrix4x4d.translate(10.0, 0.0, 0.0).mul(bound_sphered);
		Log.printf(Log.Level.Message, "%s %b %s %b\n", bound_boxd.toString(), bound_frustumd.inside(bound_boxd), bound_sphered.toString(), bound_frustumd.inside(bound_sphered));
		
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
		ControlDialog dialog = new ControlDialog(root.ref(), 1, 8.0f, 8.0f);
		dialog.setUpdatedCallback(new ControlDialog.UpdatedCallback() {
			public void run(ControlDialog dialog) {
				int x = (int)dialog.getPositionX();
				int y = (int)dialog.getPositionY();
				int width = (int)dialog.getWidth();
				int height = (int)dialog.getHeight();
				Log.printf(Log.Level.Message, "Dialog Updated %d %d %dx%d\n", x, y, width, height);
			}
		});
		dialog.setAlign(Control.Align.Center);
		dialog.setSize(240.0f, 180.0f);
		
		// create text
		ControlText text = new ControlText(dialog.ref(), title);
		text.setAlign(Control.Align.CenterX);
		
		// create button
		ControlButton button = new ControlButton(dialog.ref(), "Button");
		button.setClickedCallback(new ControlButton.ClickedCallback() {
			public void run(ControlButton button) {
				Log.printf(Log.Level.Message, "%s Clicked\n", button.getText());
			}
		});
		button.setAlign(Control.Align.Expand);
		button.setMargin(0.0f, 0.0f, 0.0f, 16.0f);
		
		// create sliders
		Color color = Color.white();
		ControlSlider slider_r = new ControlSlider(dialog.ref(), "R", 2, color.r(), 0.0, 1.0);
		ControlSlider slider_g = new ControlSlider(dialog.ref(), "G", 2, color.g(), 0.0, 1.0);
		ControlSlider slider_b = new ControlSlider(dialog.ref(), "B", 2, color.b(), 0.0, 1.0);
		slider_r.setChangedCallback(new ControlSlider.ChangedCallback() { public void run(ControlSlider slider) { color.setR(slider.getValuef32()); } });
		slider_g.setChangedCallback(new ControlSlider.ChangedCallback() { public void run(ControlSlider slider) { color.setG(slider.getValuef32()); } });
		slider_b.setChangedCallback(new ControlSlider.ChangedCallback() { public void run(ControlSlider slider) { color.setB(slider.getValuef32()); } });
		slider_r.setFormatCallback(new ControlSlider.FormatCallback() { public String run(ControlSlider slider) { return "Value " + TSString.fromf32(slider.getValuef32(), 2); } });
		slider_g.setFormatCallback(new ControlSlider.FormatCallback() { public String run(ControlSlider slider) { return "Value " + TSString.fromf32(slider.getValuef32(), 2); } });
		slider_b.setFormatCallback(new ControlSlider.FormatCallback() { public String run(ControlSlider slider) { return "Value " + TSString.fromf32(slider.getValuef32(), 2); } });
		slider_r.setAlign(Control.Align.ExpandX);
		slider_g.setAlign(Control.Align.ExpandX);
		slider_b.setAlign(Control.Align.ExpandX);
		
		////////////////////////////////
		// render test
		////////////////////////////////
		
		// vertex shader
		String vertex_shader =
			"layout(location = 0) in vec4 in_position;\n" +
			"layout(location = 1) in vec3 in_normal;\n" +
			"layout(location = 2) in vec2 in_texcoord;\n" +
			"layout(row_major, binding = 0) uniform CommonParameters {\n" +
			"	mat4 projection;\n" +
			"	mat4 modelview;\n" +
			"	mat4 transform;\n" +
			"	vec4 camera;\n" +
			"};\n" +
			"layout(location = 0) out vec3 s_direction;\n" +
			"layout(location = 1) out vec3 s_normal;\n" +
			"layout(location = 2) out vec2 s_texcoord;\n" +
			"void main() {\n" +
			"	vec4 position = transform * in_position;\n" +
			"	gl_Position = projection * (modelview * position);\n" +
			"	s_direction = camera.xyz - position.xyz;\n" +
			"	s_normal = (transform * vec4(in_normal, 0.0f)).xyz;\n" +
			"	s_texcoord = in_texcoord;\n" +
			"}\n";
		
		// fragment shader
		String fragment_shader =
			"layout(binding = 0, set = 1) uniform texture2D in_texture;\n" +
			"layout(binding = 0, set = 2) uniform sampler in_sampler;\n" +
			"layout(location = 0) in vec3 s_direction;\n" +
			"layout(location = 1) in vec3 s_normal;\n" +
			"layout(location = 2) in vec2 s_texcoord;\n" +
			"layout(location = 0) out vec4 out_color;\n" +
			"void main() {\n" +
			"	vec3 direction = normalize(s_direction);\n" +
			"	vec3 normal = normalize(s_normal);\n" +
			"	float diffuse = clamp(dot(direction, normal), 0.0f, 1.0f);\n" +
			"	float specular = pow(clamp(dot(reflect(-direction, normal), direction), 0.0f, 1.0f), 16.0f);\n" +
			"	out_color = texture(sampler2D(in_texture, in_sampler), s_texcoord) * diffuse + specular;\n" +
			"}";
		
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
		Mesh mesh = create_mesh(new Vector2i(64, 32), new Vector2f(8.0f, 2.0f), 2.0f);
		
		// create model
		MeshModel model = new MeshModel();
		if(!model.create(device, render_pipeline, mesh)) return;
		
		// create sampler
		Sampler sampler = device.createSampler(Sampler.Filter.Linear, Sampler.WrapMode.Repeat);
		if(!sampler.isValidPtr()) return;
		
		// create texture
		Image texture_image = create_image(256, 0);
		Texture texture = device.createTexture(texture_image);
		if(!texture.isValidPtr()) return;
		
		////////////////////////////////
		// main loop
		////////////////////////////////
		
		// main loop
		window.run(new Window.MainLoopCallback() {
			
			int texture_frame = 0;
			double texture_ifps = 1.0 / 30.0;
			double texture_time = Time.seconds();
			
			public boolean run() {
				
				// update window
				Window.update();
				
				// render window
				if(!window.render()) return false;
				
				// update texture
				if(Time.seconds() - texture_time > texture_ifps) {
					texture_time += texture_ifps;
					Image image = create_image(256, texture_frame);
					device.setTexture(texture, image);
					texture_frame++;
				}
				
				// update interface
				{
					// window size
					float height = app.getHeight();
					float width = (float)Math.floor(height * window.getWidth() / window.getHeight());
					float mouse_x = width * window.getMouseX() / window.getWidth();
					float mouse_y = height * window.getMouseY() / window.getHeight();
					
					// mouse button
					int buttons = 0;
					if((window.getMouseButtons().value & Window.Button.Left.value) != 0) buttons |= Control.Button.Left.value;
					if((window.getMouseButtons().value & Window.Button.Left2.value) != 0) buttons |= Control.Button.Left.value;
					
					// update controls
					root.setViewport(width, height);
					root.setMouse(mouse_x, mouse_y, new Control.Button(buttons));
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
					ByteBuffer parameters = ByteBuffer.allocate(64 + 32).order(ByteOrder.LITTLE_ENDIAN);
					parameters.put(Matrix4x4f.rotateZ(time * 16.0f).getBytes());
					parameters.put(color.getBytes());
					parameters.putFloat(time);
					
					// draw background
					command.setPipeline(pipeline);
					command.setUniform(0, parameters);
					command.setVertices(0, vertices);
					command.setIndices(indices);
					command.drawElements(3);
					
					// render parameters
					Vector3f camera = new Vector3f(12.0f, 12.0f, 6.0f);
					parameters = ByteBuffer.allocate(64 * 3 + 16).order(ByteOrder.LITTLE_ENDIAN);
					parameters.put(Matrix4x4f.perspective(60.0f, (float)window.getWidth() / (float)window.getHeight(), 0.1f, 1000.0f).getBytes());
					parameters.put(Matrix4x4f.lookAt(camera, Vector3f.zero(), new Vector3f(0.0f, 0.0f, 1.0f)).getBytes());
					parameters.put(Matrix4x4f.rotateZ(time * 24.0f).mul(Matrix4x4f.rotateX(time * 16.0f)).getBytes());
					parameters.put(camera.getBytes());
					
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
				}
				target.end();
				
				// present window
				if(!window.present()) return false;
				
				// check device
				if(!device.check()) return false;
				
				// memory
				System.gc();
				
				return true;
			}
		});
		
		// finish context
		window.finish();
		
		// destroy resources
		root.destroyPtr();
		
		// done
		Log.print(Log.Level.Message, "Done\n");
	}
}

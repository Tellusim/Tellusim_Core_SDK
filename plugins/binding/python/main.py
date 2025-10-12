#!/usr/bin/env python3

# Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/

import sys
import math

from tellusimd import *

#
# create mesh
#
def create_mesh(steps, radius, texcoord):
	
	# create mesh
	mesh = Mesh()
	
	# create vertices
	num_vertices = (steps.x + 1) * (steps.y + 1)
	positions = MeshAttribute(MeshAttribute.TypePosition, FormatRGBf32, num_vertices)
	normals = MeshAttribute(MeshAttribute.TypeNormal, FormatRGBf32, num_vertices)
	tangents = MeshAttribute(MeshAttribute.TypeTangent, FormatRGBAf32, num_vertices)
	texcoords = MeshAttribute(MeshAttribute.TypeTexCoord, FormatRGf32, num_vertices)
	
	vertex = 0
	isteps = 1.0 / Vector2f(steps)
	aspect = radius.x / radius.y
	for j in range(steps.y + 1):
		ty = j * isteps.y
		z = -math.cos(ty * Pi2 - Pi05)
		r = math.sin(ty * Pi2 - Pi05)
		for i in range(steps.x + 1):
			tx = i * isteps.x
			x = -math.sin(tx * Pi2)
			y = math.cos(tx * Pi2)
			positions.set(vertex, Vector3f(x * (r * radius.y + radius.x), y * (r * radius.y + radius.x), z * radius.y))
			normals.set(vertex, Vector3f(x * r, y * r, z))
			tangents.set(vertex, Vector4f(-y, x, 0.0, 1.0))
			texcoords.set(vertex, Vector2f(tx * aspect, ty) * texcoord)
			vertex += 1
	
	basis = MeshAttribute(MeshAttribute.TypeBasis, FormatRGBAu32, num_vertices)
	basis.packAttributes(normals, tangents, FormatRGBAf16)
	
	# create indices
	num_indices = steps.x * steps.y * 4
	indices_format = FormatRu16 if num_vertices < Maxu16 else FormatRu32
	indices = MeshIndices(MeshIndices.TypeQuadrilateral, indices_format, num_indices)
	
	index = 0
	for j in range(steps.y):
		for i in range(steps.x):
			vertex = (steps.x + 1) * j + i
			indices.set(index, vertex, vertex + 1, vertex + steps.x + 2, vertex + steps.x + 1)
			index += 4
	
	# create geometry
	geometry = MeshGeometry(mesh)
	geometry.addAttribute(positions, indices)
	geometry.addAttribute(basis, indices)
	geometry.addAttribute(normals, indices)
	geometry.addAttribute(texcoords, indices)
	
	# geometry bounds
	hsize = Vector3f(Vector2f(radius.x + radius.y), radius.y)
	geometry.setBoundBox(BoundBoxf(-hsize, hsize))
	
	# create bounds
	mesh.createBounds()
	
	return mesh

#
# create image
#
def create_image(size, frame):
	
	# create image
	image = Image()
	image.create2D(FormatRGBAu8n, size)
	
	# create sampler
	sampler = ImageSampler(image)
	
	# fill image
	color = ImageColor(255)
	for y in range(size):
		for x in range(size):
			v = (((x - (frame ^ y)) ^ (y + (frame ^ x))) & 255) / 63.0
			color.r = int(math.cos(Pi * 1.0 + v) * 127.5 + 127.5)
			color.g = int(math.cos(Pi * 0.5 + v) * 127.5 + 127.5)
			color.b = int(math.cos(Pi * 0.0 + v) * 127.5 + 127.5)
			sampler.set2D(x, y, color)
	
	return image

#
# main
#
def main(argv):
	
	# create App
	app = App(argv)
	if not app.create(PlatformAny): return 1
	
	# create Window
	window = Window(app.platform, app.device)
	if not window: return 1
	
	window.setSize(app.width, app.height)
	window.setCloseClickedCallback(lambda: window.stop())
	
	def clicked_callback(key, code):
		if key == Window.KeyEsc: window.stop()
		if key == Window.KeyF12:
			image = Image()
			if window.grab(image) and image.save('screenshot.png'):
				Log.print(Log.Message, 'Screenshot\n')
	
	window.setKeyboardPressedCallback(clicked_callback)
	
	title = window.platform_name + ' Tellusim::Python'
	if not window.create(title, Window.DefaultFlags | Window.FlagVerticalSync) or not window.setHidden(False): return 1
	
	# create device
	device = Device(window)
	if not device: return 1
	
	# device features
	Log.printf(Log.Message, 'Features:\n%s\n', device.features)
	Log.printf(Log.Message, 'Device: %s\n', device.name)
	
	# build info
	Log.printf(Log.Message, 'Build: %s\n', App.getBuildInfo())
	
	# create target
	target = device.createTarget(window)
	if not target: return 1
	
	################################
	# core test
	################################
	
	blob = Blob()
	blob.writeString(title)
	
	blob.seek(0)
	Log.printf(Log.Message, 'Stream: %s\n', blob.readString())
	
	################################
	# bounds test
	################################
	
	# 32-bit floating point
	bound_boxf = BoundBoxf(-Vector3f.one, Vector3f.one)
	bound_spheref = BoundSpheref(bound_boxf)
	bound_frustumf = BoundFrustumf(Matrix4x4f.perspective(60.0, 1.0, 0.1, 1000.0), Matrix4x4f.lookAt(Vector3f.one, Vector3f.zero, Vector3f(0.0, 0.0, 1.0)))
	Log.printf(Log.Message, "%s %u %s %u\n", str(bound_boxf), bound_frustumf.inside(bound_boxf), str(bound_spheref), bound_frustumf.inside(bound_spheref))
	bound_boxf = Matrix4x3f.translate(10.0, 0.0, 0.0) * bound_boxf
	bound_spheref = Matrix4x4f.translate(10.0, 0.0, 0.0) * bound_spheref
	Log.printf(Log.Message, "%s %u %s %u\n", str(bound_boxf), bound_frustumf.inside(bound_boxf), str(bound_spheref), bound_frustumf.inside(bound_spheref))
	
	# 64-bit floating point
	bound_boxd = BoundBoxd(-Vector3d.one, Vector3d.one)
	bound_sphered = BoundSphered(bound_boxd)
	bound_frustumd = BoundFrustumd(Matrix4x4d.perspective(60.0, 1.0, 0.1, 1000.0), Matrix4x4d.lookAt(Vector3d.one, Vector3d.zero, Vector3d(0.0, 0.0, 1.0)))
	Log.printf(Log.Message, "%s %u %s %u\n", str(bound_boxd), bound_frustumd.inside(bound_boxd), str(bound_sphered), bound_frustumd.inside(bound_sphered))
	bound_boxd = Matrix4x3d.translate(10.0, 0.0, 0.0) * bound_boxd
	bound_sphered = Matrix4x4d.translate(10.0, 0.0, 0.0) * bound_sphered
	Log.printf(Log.Message, "%s %u %s %u\n", str(bound_boxd), bound_frustumd.inside(bound_boxd), str(bound_sphered), bound_frustumd.inside(bound_sphered))
	
	################################
	# platform test
	################################
	
	# create pipeline
	pipeline = device.createPipeline()
	pipeline.setUniformMask(0, Shader.MaskFragment)
	pipeline.setColorFormat(window.color_format)
	pipeline.setDepthFormat(window.depth_format)
	pipeline.setDepthMask(Pipeline.DepthMaskNone)
	pipeline.addAttribute(Pipeline.AttributePosition, FormatRGf32, 0, 0, 8)
	if not pipeline.loadShaderGLSL(Shader.TypeVertex, 'main.shader', 'VERTEX_SHADER=1'): return 1
	if not pipeline.loadShaderGLSL(Shader.TypeFragment, 'main.shader', 'FRAGMENT_SHADER=1'): return 1
	if not pipeline.create(): return 1
	
	# geometry vertices
	vertices = bytearray(Vector2f(3.0, -1.0)) + Vector2f(-1.0, -1.0) + Vector2f(-1.0, 3.0)
	
	# geometry indices
	indices = bytearray(Vector3u(0, 1, 2))
	
	################################
	# interface test
	################################
	
	# create canvas
	canvas = Canvas()
	
	# create root controls
	root = ControlRoot(canvas, True)
	root.setFontSize(24)
	
	# create dialog
	dialog = ControlDialog(root, 1, 8.0, 8.0)
	def updated_callback(dialog):
		x = int(dialog.position_x)
		y = int(dialog.position_y)
		width = int(dialog.width)
		height = int(dialog.height)
		Log.printf(Log.Message, 'Dialog Updated %d %d %ux%u\n', x, y, width, height)
	dialog.setUpdatedCallback(updated_callback)
	dialog.setAlign(Control.AlignCenter)
	dialog.setSize(240.0, 180.0)
	
	# create text
	text = ControlText(dialog, title)
	text.setAlign(Control.AlignCenterX)
	
	# create button
	button = ControlButton(dialog, 'Button')
	def clicked_callback(button): Log.printf(Log.Message, '%s Clicked\n', button.text)
	button.setClickedCallback(clicked_callback)
	button.setAlign(Control.AlignExpand)
	button.setMargin(0.0, 0.0, 0.0, 16.0)
	
	# common parameters
	color = Color.white
	
	# create sliders
	slider_r = ControlSlider(dialog, 'R', 2, color.r, 0.0, 1.0)
	slider_g = ControlSlider(dialog, 'G', 2, color.g, 0.0, 1.0)
	slider_b = ControlSlider(dialog, 'B', 2, color.b, 0.0, 1.0)
	def changed_r_callback(slider): color.r = slider.valuef32
	def changed_g_callback(slider): color.g = slider.valuef32
	def changed_b_callback(slider): color.b = slider.valuef32
	slider_r.setChangedCallback(changed_r_callback)
	slider_g.setChangedCallback(changed_g_callback)
	slider_b.setChangedCallback(changed_b_callback)
	slider_r.setAlign(Control.AlignExpandX)
	slider_g.setAlign(Control.AlignExpandX)
	slider_b.setAlign(Control.AlignExpandX)
	
	################################
	# render test
	################################
	
	# vertex shader
	vertex_shader = '''
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
	'''
	
	# fragment shader
	fragment_shader = '''
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
	'''
	
	# create render pipeline
	render_pipeline = device.createPipeline()
	render_pipeline.setUniformMask(0, Shader.MaskVertex)
	render_pipeline.setTextureMask(0, Shader.MaskFragment)
	render_pipeline.setSamplerMask(0, Shader.MaskFragment)
	render_pipeline.setColorFormat(window.color_format)
	render_pipeline.setDepthFormat(window.depth_format)
	render_pipeline.setDepthFunc(Pipeline.DepthFuncLessEqual)
	render_pipeline.addAttribute(Pipeline.AttributePosition, FormatRGBf32, 0, 0, 32)
	render_pipeline.addAttribute(Pipeline.AttributeNormal, FormatRGBf32, 0, 12, 32)
	render_pipeline.addAttribute(Pipeline.AttributeTexCoord, FormatRGf32, 0, 24, 32)
	if not render_pipeline.createShaderGLSL(Shader.TypeVertex, vertex_shader): return 1
	if not render_pipeline.createShaderGLSL(Shader.TypeFragment, fragment_shader): return 1
	if not render_pipeline.create(): return 1
	
	# create mesh
	mesh = create_mesh(Vector2u(64, 32), Vector2f(8.0, 2.0), 2.0)
	
	# create model
	model = MeshModel()
	if not model.create(device, render_pipeline, mesh): return
	
	# create sampler
	sampler = device.createSampler(Sampler.FilterLinear, Sampler.WrapModeRepeat)
	if not sampler: return
	
	# create texture
	texture_image = create_image(256, 0)
	texture = device.createTexture(texture_image)
	if not texture: return
		
	################################
	# main loop
	################################
	
	texture_frame = 0
	texture_ifps = 1.0 / 3.0
	texture_time = Time.seconds()
	
	# main loop
	def main_loop():
		nonlocal texture_frame
		nonlocal texture_ifps
		nonlocal texture_time
		
		# update window
		Window.update()
		
		# render window
		if not window.render(): return False
		
		# update texture
		if Time.seconds() - texture_time > texture_ifps:
			texture_time += texture_ifps
			image = create_image(128, texture_frame)
			device.setTexture(texture, image)
			texture_frame += 1
		
		# update interface
		if True:
			
			# window size
			height = app.height
			width = math.floor(height * window.width / window.height)
			mouse_x = width * window.mouse_x / window.width
			mouse_y = height * window.mouse_y / window.height
			
			# mouse button
			buttons = Control.ButtonNone
			if window.mouse_buttons & Window.ButtonLeft: buttons |= Control.ButtonLeft
			if window.mouse_buttons & Window.ButtonLeft2: buttons |= Control.ButtonLeft
			
			# update controls
			root.setViewport(width, height)
			root.setMouse(mouse_x, mouse_y, buttons)
			while root.update(canvas.getScale(target)): pass
			
			# create canvas
			canvas.create(device, target)
		
		# window target
		if target.begin():
			
			command = device.createCommand(target)
			
			# current time
			time = Time.seconds()
			
			# common parameters
			parameters = bytearray()
			parameters += Matrix4x4f.rotateZ(time * 16.0)
			parameters += color
			parameters += Scalarf(time)
			
			# draw background
			command.setPipeline(pipeline)
			command.setUniform(0, parameters)
			command.setVertices(0, vertices)
			command.setIndices(FormatRu32, indices)
			command.drawElements(3)
			
			# render parameters
			parameters = bytearray()
			camera = Vector3f(12.0, 12.0, 6.0)
			parameters += Matrix4x4f.perspective(60.0, window.width / window.height, 0.1, 1000.0)
			parameters += Matrix4x4f.lookAt(camera, Vector3f.zero, Vector3f(0.0, 0.0, 1.0))
			parameters += Matrix4x4f.rotateZ(time * 24.0) * Matrix4x4f.rotateX(time * 16.0)
			parameters += camera
			
			# draw mesh
			command.setPipeline(render_pipeline)
			command.setUniform(0, parameters)
			command.setSampler(0, sampler)
			command.setTexture(0, texture)
			model.setBuffers(command)
			model.draw(command)
			
			# draw canvas
			canvas.draw(command, target)
			
			command = None
			
			target.end()
		
		# present window
		if not window.present(): return False
		
		# check device
		if not device.check(): return False
		
		return True
	
	window.run(main_loop)
	
	# finish context
	window.finish()
	
	# done
	Log.print(Log.Message, 'Done\n')
	
	return 0

#
# entry point
#
if __name__ == '__main__':
	try:
		exit(main(sys.argv))
	except Exception as error:
		print('\n' + str(error))
		exit(1)

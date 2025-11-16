#!/usr/bin/env python3

# Tellusim Compute Application Template

import sys

from tellusimd import *

#
# main
#
def main(argv):
	
	app = None
	window = None
	device = None
	target = None
	
	surface = None
	
	kernel = None
	pipeline = None
	
	#
	# create function responsible for initialization
	#
	def create():
		
		nonlocal app
		
		# create app
		app = App(argv)
		if not app.create():
			Log.print(Log.Error, 'create(): can\'t create App\n')
			return False
		
		# create window
		if not create_window():
			return False
		
		# create resources
		if not create_resources():
			return False
		
		# additional initialization code can go here
		
		return True
	
	#
	# update function for logic updates
	#
	def update():
		
		# your update logic here
		
		return True
	
	#
	# dispatch function to handle the compute commands
	#
	def dispatch(compute):
		
		nonlocal surface
		
		# resize surface texture
		width = window.width
		height = window.height
		if not surface or surface.width != width or surface.height != height:
			if surface: device.releaseTexture(surface)
			surface = device.createTexture2D(FormatRGBAu8n, width, height, flags = Texture.FlagSurface)
			if not surface:
				Log.print(Log.Error, 'dispatch(): can\'t create Texture\n')
				return False
		
		# compute uniform parameters
		parameters = bytearray()
		parameters += Scalarf(Time.seconds())
		
		# dispatch kernel
		compute.setKernel(kernel)
		compute.setUniform(0, parameters)
		compute.setSurfaceTexture(0, surface)
		compute.dispatch(surface)
		compute.barrier(surface)
		
		# your dispatch code here
		
		return True
	
	#
	# render function to handle the drawing commands
	#
	def render(command):
		
		# draw fullscreen triangle
		command.setPipeline(pipeline)
		command.setTexture(0, surface)
		command.drawArrays(3)
		
		# your rendering code here
		
		return True
	
	#
	# helper function to create and initialize the Window
	#
	def create_window():
		
		nonlocal window, device, target
		
		# create Window
		window = Window(app.platform, app.device)
		if not window or not window.setSize(app.width, app.height) \
			or not window.create(window.platform_name + ' Python @NAME@') or not window.setHidden(False):
			Log.print(Log.Error, 'create_window(): can\'t create Window\n')
			return False
		
		# set Window callbacks
		def pressed_callback(key, code):
			if key == Window.KeyF4 and window.getKeyboardKey(Window.Key.Alt): window.stop()
			if key == Window.KeyEsc: window.stop()
		window.setKeyboardPressedCallback(pressed_callback)
		window.setCloseClickedCallback(lambda: window.stop())
		
		# create Device
		device = Device(window)
		if not device:
			Log.print(Log.Error, 'create_window(): can\'t create Device\n')
			return False
		
		# create Target
		target = device.createTarget(window)
		if not target:
			Log.print(Log.Error, 'create_window(): can\'t create Target\n')
			return False
		
		return True
	
	#
	# helper function to create and load resources
	#
	def create_resources():
		
		nonlocal kernel, pipeline
		
		# create kernel
		kernel = device.createKernel().setSurfaces(1).setUniforms(1)
		if not kernel.loadShaderGLSL("main.shader", "COMPUTE_SHADER=1"):
			Log.print(Log.Error, 'create_resources(): can\'t load Compute shader\n')
			return False
		if not kernel.create():
			Log.print(Log.Error, 'create_resources(): can\'t create Kernel\n')
			return False
		
		# create pipeline
		pipeline = device.createPipeline()
		pipeline.setTextureMask(0, Shader.MaskFragment)
		pipeline.setColorFormat(window.getColorFormat())
		pipeline.setDepthFormat(window.getDepthFormat())
		if not pipeline.loadShaderGLSL(Shader.TypeVertex, "main.shader", "VERTEX_SHADER=1"):
			Log.print(Log.Error, 'create_resources(): can\'t load Vertex shader\n')
			return False
		if not pipeline.loadShaderGLSL(Shader.TypeFragment, "main.shader", "FRAGMENT_SHADER=1"):
			Log.print(Log.Error, 'create_resources(): can\'t load Fragment shader\n')
			return False
		if not pipeline.create():
			Log.print(Log.Error, 'create_resources(): can\'t create Pipeline\n')
			return False
		
		# your resource creation code here
		
		return True
	
	#
	# helper function to render the Window
	#
	def render_window():
		
		# update events
		Window.update()
		
		# update application
		if not update(): return False
		
		# render window
		if not window.render(): return False
		
		# compute target
		if True:
			
			compute = device.createCompute()
			
			# dispatch application
			if not dispatch(compute): return False
			
			compute = None
		
		# flush surface texture
		device.flushTexture(surface)
		
		# window target
		if target.begin():
			
			command = device.createCommand(target)
			
			# render application
			if not render(command):
				target.end()
				return False
			
			command = None
			
			target.end()
		
		# present window
		if not window.present(): return False
		
		# check errors
		if not device.check(): return False
		
		return True
	
	# create the application
	if not create():
		return 1
	
	# run the application
	window.run(render_window)
	
	# finish context
	window.finish()
	
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

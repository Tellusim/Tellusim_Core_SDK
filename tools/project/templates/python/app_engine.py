#!/usr/bin/env python3

# Tellusim Engine SDK Application Template

import sys
import math
import threading

from tellusimd import *

#
# main
#
def main(argv):
	
	app = None					# Application interface
	window = None				# Window interface
	device = None				# Device interface
	target = None				# Target interface
	
	main_async = None			# main Async
	process_async = None		# process Async
	process_thread = None		# process Thread
	
	scene_manager = None		# SceneManager interface
	scene = None				# Scene interface
	
	graph = None				# Graph interface
	node_camera = None			# NodeCamera interface
	camera = None				# CameraPerspective interface
	
	torus_node = None			# NodeObject interface
	
	render_manager = None		# RenderManager interface
	render_renderer = None		# RenderRenderer interface
	render_spatial = None		# RenderSpatial interface
	render_frame = None			# RenderFrame interface
	
	counter = 0					# frame counter
	
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
		
		# create scene
		if not create_scene():
			return False
		
		# create render
		if not create_render():
			return False
		
		# load scene
		def graph_callback(stream_id, graph):
			nonlocal torus_node
			Log.print(Log.Message, 'create(): scene is loaded\n')
			torus_node = NodeObject(graph.getNode('Torus Node'))
		stream = scene_manager.getStream()
		stream.loadGraph(scene, 'scene.graphx', graph_callback, SceneStream.DefaultFlags)
		
		# additional initialization code can go here
		
		return True
	
	#
	# update function for logic updates
	#
	def update():
		
		# update scene
		angle = Time.seconds() * 16.0
		node_camera.setGlobalTransform(Matrix4x3d.placeTo(Matrix4x3d.rotateZ(-angle) * Vector3d(2.0, 2.0, 1.0), Vector3d.zero, Vector3d(0.0, 0.0, 1.0)))
		node_camera.updateScene()
		if torus_node != None and torus_node.isValidPtr():
			torus_node.setPivotTransform(Matrix4x3f.rotateX(angle * 3.0) * Matrix4x3f.rotateZ(angle * 2.0))
			torus_node.updateScene()
		
		# your update logic here
		
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
	# helper function to create and initialize Scene
	#
	def create_scene():
		
		nonlocal main_async, process_async, process_thread, scene_manager
		nonlocal scene, graph, camera, node_camera
		
		# main async
		main_async = Async()
		if not main_async.init():
			Log.print(Log.Error, 'create_scene(): can\'t initialize main Async\n')
			return False
		
		# process async
		process_async = Async()
		if not process_async.init():
			Log.print(Log.Error, 'create_scene(): can\'t initialize process Async\n')
			return False
		
		# cache location
		SceneManager.setShaderCache('shader.cache')
		SceneManager.setTextureCache('texture.cache')
		
		Log.print(Log.Verbose, 'create_scene(): create SceneManager\n')
		
		# scene flags
		manager_flags = SceneManager.DefaultFlags
		
		# create scene manager
		scene_manager = SceneManager()
		if not scene_manager.create(device, manager_flags, tasks = main_async):
			Log.print(Log.Error, 'create_scene(): can\'t create SceneManager\n')
			return False
		
		Log.print(Log.Verbose, 'create_scene(): SceneManager is ready\n')
		
		# create process thread
		def process_callback():
			while scene_manager and not scene_manager.isTerminated():
				if not scene_manager.process(process_async): Time.sleep(1000)
			Log.print(Log.Message, 'Thread Done\n')
		process_thread = threading.Thread(None, process_callback)
		process_thread.start()
		
		# initialize scene
		scene = Scene(scene_manager)
		graph = Graph(scene)
		
		# create camera
		camera = CameraPerspective(scene)
		node_camera = NodeCamera(graph, camera)
		
		return True
	
	#
	# helper function to create and initialize Render
	#
	def create_render():
		
		nonlocal render_manager, render_renderer, render_spatial, render_frame
		
		Log.print(Log.Verbose, 'create_render(): create RenderManager\n')
		
		# render flags
		manager_flags = RenderManager.FlagShadowMap | RenderManager.FlagAntialiasing | RenderManager.FlagMotionBuffer
		renderer_flags = RenderRenderer.FlagMotionBuffer | RenderRenderer.FlagScreenOcclusion | RenderRenderer.FlagScreenReflection | RenderRenderer.FlagAntialiasing | RenderRenderer.FlagMotionBuffer
		
		# create render manager
		render_manager = RenderManager(scene_manager)
		render_manager.setRendererFlags(device, renderer_flags)
		render_manager.setDrawParameters(device, window.color_format, window.depth_format, window.multisample)
		if not render_manager.create(device, manager_flags, tasks = main_async):
			Log.print(Log.Error, 'create_render(): can\'t create manager\n')
			return False
		
		Log.print(Log.Verbose, 'create_render(): RenderManager is ready\n')
		
		render_renderer = render_manager.renderer
		render_spatial = render_manager.spatial
		
		# create render frame
		render_frame = RenderFrame(render_manager, node_camera)
		
		# scene render
		scene.setRender(render_renderer.scene_render)
		
		return True
	
	#
	# helper function to render the Scene
	#
	def render_scene():
		
		# update RenderManager
		render_manager.update()
		
		# render flags
		spatial_flags = RenderSpatial.FlagAntialiasing
		renderer_flags = render_manager.renderer_flags
		
		# dispatch compute
		if True:
			
			compute = device.createCompute()
			
			# dispatch frame intersection
			render_spatial.dispatchFrame(compute, render_frame, spatial_flags)
			
			# dispatch shadow map intersection
			render_spatial.dispatchShadowMap(compute, render_frame, spatial_flags)
			
			# dispatch shadow map command generation
			render_renderer.dispatchShadowMap(compute, render_frame, renderer_flags)
			
			compute = None
		
		# render shadow map
		if True:
			
			# flush buffers
			scene_manager.flush(device)
			render_manager.flush(device)
			render_frame.flush(device)
			
			# draw deferred
			render_renderer.drawShadowMap(device, render_frame, renderer_flags)
		
		# dispatch compute
		if True:
			
			compute = device.createCompute()
			
			# dispatch frame object intersection
			render_spatial.dispatchObjects(compute, render_frame, spatial_flags)
			
			# dispatch draw command generation
			render_renderer.dispatchFrame(compute, render_frame, renderer_flags)
			
			compute = None
		
		# render frame
		if True:
			
			# flush buffers
			scene_manager.flush(device)
			render_manager.flush(device)
			render_frame.flush(device)
			
			# draw deferred
			render_renderer.drawDeferred(device, render_frame, renderer_flags)
		
		# dispatch compute
		if True:
			
			compute = device.createCompute()
			
			# dispatch render
			render_renderer.dispatchScreen(device, compute, render_frame, renderer_flags)
			render_renderer.dispatchOcclusion(device, compute, render_frame, renderer_flags)
			render_renderer.dispatchLight(device, compute, render_frame, renderer_flags)
			render_renderer.dispatchOccluder(device, compute, render_frame, renderer_flags)
			render_renderer.dispatchFeedback(device, compute, render_frame, renderer_flags)
			render_renderer.dispatchLuminance(device, compute, render_frame, renderer_flags)
			render_renderer.dispatchComposite(device, compute, render_frame, renderer_flags)
			
			compute = None
		
		return True
	
	#
	# helper function to render the Window
	#
	def render_window():
		
		nonlocal counter
		
		# update events
		Window.update()
		
		# update application
		if not update(): return False
		
		# render window
		if not window.render(): return False
		
		# resize RenderFrame with 200% upscale
		width = window.width
		height = window.height
		texture = render_frame.composite_texture
		if not texture.isValidPtr() or texture.width != width or texture.height != height:
			if not device.finish(): return False
			render_frame.create(device, render_renderer, int(width / 2), int(height / 2), Size(width, height))
		
		# create Scene
		if not scene.create(device, main_async):
			Log.print(Log.Error, 'render_window(): can\'t create Scene\n')
			return False
		
		# update Scene
		scene.setTime(Time.seconds())
		scene.update(device)
		
		# scene flags
		usec = 10000
		scene_flags = SceneManager.FlagNone
		
		# update SceneManager
		if not scene_manager.update(device, main_async, counter, 0, usec, scene_flags):
			Log.print(Log.Error, 'render_window(): can\'t update SceneManager\n')
			return False
		counter += 1
		
		# dispatch compute
		if True:
			
			compute = device.createCompute()
			
			# dispatch SceneManager
			scene_manager.dispatch(device, compute)
			
			# dispatch Scene
			scene.dispatch(device, compute)
			
			compute = None
		
		# render scene
		if not render_scene():
			Log.print(Log.Error, 'render_window(): can\'t render RenderFrame\n')
			return False
		
		# window target
		if target.begin():
			command = device.createCommand(target)
			texture = render_frame.composite_texture
			flipped = (target.isFlipped() ^ render_renderer.isTargetFlipped())
			render_manager.getDraw().drawTexture(command, texture, flipped, RenderDraw.ModeComposite)
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
	
	# stop process thread
	scene_manager.terminate()
	
	# finish device
	device.finish()
	
	# release render
	render_frame.clearPtr()
	render_manager.clearPtr()
	
	# clear scene
	scene.clear()
	scene_manager.update(device, main_async)
	device.finish()
	
	# wait thread
	process_thread.join()
	
	# release scene
	scene.clearPtr()
	scene_manager.clearPtr()
	
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

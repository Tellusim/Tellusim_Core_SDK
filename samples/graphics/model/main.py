#!/usr/bin/env python3

# Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/

import sys
import math

from tellusimd import *

#
# main
#
def main(argv):
	
	# create app
	app = App(sys.argv)
	if not app.create(): return 1
	
	# create window
	window = Window(app.getPlatform(), app.getDevice())
	if not window: return 1
	
	window.setSize(app.getWidth(), app.getHeight())
	window.setCloseClickedCallback(lambda: window.stop())
	window.setKeyboardPressedCallback(lambda key, code: window.stop() if key == Window.KeyEsc else None)
	
	title = window.getPlatformName() + ' Tellusim::Model Python'
	if not window.create(title) or not window.setHidden(False): return 1
	
	# create device
	device = Device(window)
	if not device: return 1
	
	# create pipeline
	pipeline = device.createPipeline()
	pipeline.setUniformMask(0, Shader.MaskVertex)
	pipeline.setUniformMask(1, Shader.MaskVertex)
	pipeline.addAttribute(Pipeline.AttributePosition, FormatRGBf32, 0, offset = 0, stride = 24)
	pipeline.addAttribute(Pipeline.AttributeNormal, FormatRGBf32, 0, offset = 12, stride = 24)
	pipeline.setColorFormat(window.getColorFormat())
	pipeline.setDepthFormat(window.getDepthFormat())
	pipeline.setDepthFunc(Pipeline.DepthFuncLessEqual)
	if not pipeline.loadShaderGLSL(Shader.TypeVertex, 'main.shader', 'VERTEX_SHADER=1'): return 1
	if not pipeline.loadShaderGLSL(Shader.TypeFragment, 'main.shader', 'FRAGMENT_SHADER=1'): return 1
	if not pipeline.create(): return 1
	
	# load mesh
	mesh = Mesh()
	if not mesh.load('model.dae'): return 1
	
	# create model
	model = MeshModel()
	if not model.create(device, pipeline, mesh): return 1
	
	# create target
	target = device.createTarget(window)
	
	# FPS counter
	fps_time = Time.seconds()
	fps_counter = 0
	
	# main loop
	def main_loop():
		nonlocal fps_counter
		nonlocal fps_time
		
		Window.update()
		
		if not window.render(): return False
		
		# current time
		fps_counter += 1
		time = Time.seconds()
		if time - fps_time > 1.0:
			window.setTitle('{0} {1:.1f} FPS'.format(title, fps_counter / (time - fps_time)))
			fps_time = time
			fps_counter = 0
		
		# window target
		target.setClearColor(0.2, 0.2, 0.2, 1.0)
		if target.begin():
			
			# create command list
			command = device.createCommand(target)
			
			# set pipeline
			command.setPipeline(pipeline)
			
			# set model buffers
			model.setBuffers(command)
			
			# set common parameters
			common_parameters = bytearray()
			camera = Vector4f(3.0, 3.0, 3.0, 0.0)
			projection = Matrix4x4f.perspective(60.0, window.getWidth() / window.getHeight(), 0.1, 1000.0)
			modelview = Matrix4x4f.lookAt(camera.xyz, Vector3f(0.0, 0.0, 0.0), Vector3f(0.0, 0.0, 1.0))
			if target.isFlipped(): projection = Matrix4x4f.scale(1.0, -1.0, 1.0) * projection
			common_parameters += projection
			common_parameters += modelview
			common_parameters += camera
			command.setUniform(0, common_parameters)
			
			# draw model
			for node in mesh.getNodes():
				transform = Matrix4x3f.rotateX(time * 16.0) * Matrix4x3f.rotateZ(time * 32.0) * Matrix4x3f(node.getGlobalTransform() * node.getPivotTransform())
				for geometry in node.getGeometries():
					geometry_transform = Matrix4x4f(transform * geometry.getTransform())
					if geometry.getNumMaterials():
						for material in geometry.getMaterials():
							model_parameters = bytearray()
							model_parameters += geometry_transform
							model_parameters += material.getParameterColor(MeshMaterial.TypeDiffuse)
							command.setUniform(1, model_parameters)
							model.draw(command, geometry.getIndex(), material.getIndex())
					else:
						model_parameters = bytearray()
						model_parameters += geometry_transform
						model_parameters += Color(1.0)
						command.setUniform(1, model_parameters)
						model.draw(command, geometry.getIndex())
			
			command = None
			
			target.end()
		
		if not window.present(): return False
		
		device.check()
		
		return True
	
	window.run(main_loop)
	
	# finish context
	window.finish()
	
	# done
	Log.print('Done\n')
	
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

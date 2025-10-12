#!/usr/bin/env python3

# Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/

import sys

import numpy as np

from tellusimd import *

#
# main
#
def main(argv):
	
	# create app
	app = App(sys.argv)
	if not app.create(): return 1
	
	# create window
	window = Window(app.platform, app.device)
	if not window: return 1
	
	window.setSize(app.width, app.height)
	window.setCloseClickedCallback(lambda: window.stop())
	window.setKeyboardPressedCallback(lambda key, code: window.stop() if key == Window.KeyEsc else None)
	
	title = window.platform_name + ' Tellusim::NumPy'
	if not window.create(title) or not window.setHidden(False): return 1
	
	# create device
	device = Device(window)
	if not device: return 1
	
	# create pipeline
	pipeline = device.createPipeline()
	pipeline.setUniformMask(0, Shader.MaskVertex)
	pipeline.addAttribute(Pipeline.AttributePosition, FormatRf32, 0, offset = 0, stride = 4)
	pipeline.addAttribute(Pipeline.AttributePosition, FormatRf32, 1, offset = 0, stride = 4)
	pipeline.addAttribute(Pipeline.AttributePosition, FormatRf32, 2, offset = 0, stride = 4)
	pipeline.setColorFormat(window.color_format)
	pipeline.setDepthFormat(window.depth_format)
	pipeline.setDepthFunc(Pipeline.DepthFuncLessEqual)
	pipeline.setFillMode(Pipeline.FillModeLine)
	if not pipeline.loadShaderGLSL(Shader.TypeVertex, 'main.shader', 'VERTEX_SHADER=1'): return 1
	if not pipeline.loadShaderGLSL(Shader.TypeFragment, 'main.shader', 'FRAGMENT_SHADER=1'): return 1
	if not pipeline.create(): return 1
	
	# create target
	target = device.createTarget(window)
	
	# create grid
	size = 48
	
	# create vertices
	x = np.linspace(-16.0, 16.0, size, dtype = 'f')
	y = np.linspace(-16.0, 16.0, size, dtype = 'f')
	x, y = np.meshgrid(x, y)
	
	# create indices
	i0 = np.arange(size * size, dtype = 'i').reshape(size, size)
	i1 = np.concatenate((i0[:-1, :-1].ravel(), i0[1:, 1:].ravel()))
	i2 = np.concatenate((i0[:-1, 1:].ravel(), i0[:-1, 1:].ravel()))
	i3 = np.concatenate((i0[1:, :-1].ravel(), i0[1:, :-1].ravel()))
	indices = np.ravel((i1, i2, i3), order = 'f')
	
	# main loop
	def main_loop():
		nonlocal size
		
		Window.update()
		
		if not window.render(): return False
		
		# window target
		target.setClearColor(0.2, 0.2, 0.2, 1.0)
		if target.begin():
			
			# update data
			time = Time.seconds()
			z = np.sin(x * 0.5 + time) * 2.0 + np.cos(y * 0.5 + time) * 2.0
			
			# create command list
			command = device.createCommand(target)
			
			# set pipeline
			command.setPipeline(pipeline)
			
			# set vertices
			command.setVertexData(0, x)
			command.setVertexData(1, y)
			command.setVertexData(2, z)
			
			# set indices
			command.setIndexData(FormatRu32, indices)
			
			# set common parameters
			common_parameters = bytearray()
			projection = Matrix4x4f.perspective(60.0, window.width / window.height, 0.1, 1000.0)
			common_parameters += Matrix4x4f.scale(1.0, -1.0, 1.0) * projection if target.isFlipped() else projection
			common_parameters += Matrix4x4f.lookAt(Matrix4x3f.rotateZ(time * 4.0) * Vector3f(16.0), Vector3f(0.0), Vector3f(0.0, 0.0, 1.0))
			command.setUniform(0, common_parameters)
			
			# draw elements
			command.drawElements(len(indices))
			
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

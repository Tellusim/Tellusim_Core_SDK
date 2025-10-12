#!/usr/bin/env python3

# Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/

import sys

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
	
	title = window.getPlatformName() + ' Tellusim::Compute Python'
	if not window.create(title) or not window.setHidden(False): return 1
	
	# create device
	device = Device(window)
	if not device: return 1
	
	# check compute shader support
	if not device.hasShader(Shader.TypeCompute):
		Log.print(Log.Error, 'compute shader is not supported\n')
		return 0
	
	# create kernel
	kernel = device.createKernel().setSamplers(1).setTextures(1).setSurfaces(1).setUniforms(1)
	if not kernel.loadShaderGLSL('main.shader', 'COMPUTE_SHADER=1'): return 1
	if not kernel.create(): return 1
	
	# create pipeline
	pipeline = device.createPipeline()
	pipeline.setSamplerMask(0, Shader.MaskFragment)
	pipeline.setTextureMask(0, Shader.MaskFragment)
	pipeline.setColorFormat(window.getColorFormat())
	pipeline.setDepthFormat(window.getDepthFormat())
	if not pipeline.loadShaderGLSL(Shader.TypeVertex, 'main.shader', 'VERTEX_SHADER=1'): return 1
	if not pipeline.loadShaderGLSL(Shader.TypeFragment, 'main.shader', 'FRAGMENT_SHADER=1'): return 1
	if not pipeline.create(): return 1
	
	# create sampler
	sampler = device.createSampler(Sampler.FilterLinear, Sampler.WrapModeRepeat)
	if not sampler: return 1
	
	# create texture
	texture = device.loadTexture('texture.png')
	if not texture: return 1
	
	# create surface
	width = 2048
	height = 2048
	surface = device.createTexture2D(FormatRGBAu8n, width, height, flags = Texture.FlagSurface)
	if not surface: return 1
	
	# create target
	target = device.createTarget(window)
	
	# main loop
	def main_loop():
		
		Window.update()
		
		if not window.render(): return False
		
		if True:
			
			# create command list
			compute = device.createCompute()
			
			# set kernel
			compute.setKernel(kernel)
			compute.setSampler(0, sampler)
			compute.setTexture(0, texture)
			compute.setSurfaceTexture(0, surface)
			
			# set compute parameters
			compute_parameters = bytearray()
			compute_parameters += Vector2u(width, height)
			compute_parameters += Scalarf(window.getWidth() / window.getHeight())
			compute_parameters += Scalarf(Time.seconds())
			compute.setUniform(0, compute_parameters)
			
			# dispatch kernel
			compute.dispatch(width, height)
			compute.barrier(surface)
			
			compute = None
		
		# flush texture
		device.flushTexture(surface)
		
		# window target
		if target.begin():
			
			# create command list
			command = device.createCommand(target)
			
			# draw surface
			command.setPipeline(pipeline)
			command.setSampler(0, sampler)
			command.setTexture(0, surface)
			command.drawArrays(3)
			
			command = None
			
			target.end()
		
		if not window.present(): return False
		
		if not device.check(): return False
		
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

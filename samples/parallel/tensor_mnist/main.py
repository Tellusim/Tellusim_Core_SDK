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
	window = Window(app.platform, app.device)
	if not window: return 1
	
	window.setSize(app.width, app.height)
	window.setCloseClickedCallback(lambda: window.stop())
	window.setKeyboardPressedCallback(lambda key, code: window.stop() if key == Window.KeyEsc else None)
	
	title = window.platform_name + ' Tellusim::TensorMnist Python'
	if not window.create(title) or not window.setHidden(False): return 1
	
	# create device
	device = Device(window)
	if not device: return 1
	
	# check compute tracing support
	if not device.hasShader(Shader.TypeCompute):
		Log.print(Log.Error, 'compute shader is not supported\n')
		return 0
	
	# shader cache
	Shader.setCache('main.cache');
	
	# create pipeline
	pipeline = device.createPipeline()
	pipeline.setSamplerMask(0, Shader.MaskFragment)
	pipeline.setTextureMasks(0, 2, Shader.MaskFragment)
	pipeline.setStorageMask(0, Shader.MaskFragment)
	pipeline.setColorFormat(window.color_format)
	pipeline.setDepthFormat(window.depth_format)
	if not pipeline.loadShaderGLSL(Shader.TypeVertex, 'main.shader', 'VERTEX_SHADER=1'): return 1
	if not pipeline.loadShaderGLSL(Shader.TypeFragment, 'main.shader', 'FRAGMENT_SHADER=1'): return 1
	if not pipeline.create(): return 1
	
	# create sampler
	sampler = device.createSampler(Sampler.FilterLinear, Sampler.WrapModeClamp)
	if not sampler: return 1
	
	# create textures
	texture = device.loadTexture('texture.png')
	numbers = device.loadTexture('numbers.png')
	if not texture or not numbers: return 1
	
	# create tensor graph
	tensor_graph = TensorGraph()
	if not tensor_graph.create(device, TensorGraph.FlagsAll & ~TensorGraph.FlagFormatRf16): return 1
	
	# model tensors
	tensors = []
	
	# load model
	source = Source()
	if not source.open('model.bin'): return 1
	while source.isAvailable():
		size = source.readu8()
		if size == 0xff: break
		tensor = Tensor()
		if size > 3: tensor.layers = source.readu16()
		if size > 2: tensor.depth = source.readu16()
		if size > 1: tensor.height = source.readu16()
		if size > 0: tensor.width = source.readu16()
		tensor.offset = source.readu32() * 4
		name = source.readString(0)
		Log.printf(Log.Message, '%u: %s [%ux%ux%ux%u]\n', len(tensors), name, tensor.width, tensor.height, tensor.depth, tensor.layers)
		tensors.append(tensor)
	
	# model weights
	weights = bytearray(source.readu32() * 4)
	if source.read(weights) != len(weights): return 1
	weights_buffer = device.createBuffer(Buffer.FlagStorage, weights)
	if not weights_buffer: return 1
	
	# tensor buffer
	for tensor in tensors:
		tensor.buffer = weights_buffer
		tensor.format = FormatRf32
	
	# create texture tensor
	size = 28
	width = udiv(texture.width, size)
	height = udiv(texture.height, size)
	layers = width * height
	texture_buffer = device.createBuffer(Buffer.FlagStorage, size * size * layers * 4)
	texture_tensor = Tensor(texture_buffer, FormatRf32, size, size, 1, layers)
	if not texture_buffer: return 1
	
	# create temporary buffers
	tensor_0_buffer = device.createBuffer(Buffer.FlagStorage, 1024 * 1024 * 16)
	tensor_1_buffer = device.createBuffer(Buffer.FlagStorage, 1024 * 1024 * 16)
	if not tensor_0_buffer or not tensor_1_buffer: return 1
	
	# create target
	target = device.createTarget(window)
	
	# main loop
	def main_loop():
		
		Window.update()
		
		if not window.render(): return False
		
		if True:
			
			# create command list
			compute = device.createCompute()
			
			# copy texture to tensor
			tensor_graph.dispatch(compute, texture_tensor, texture)
			
			# first convolution
			tensor_0 = Tensor(tensor_0_buffer)
			tensor_graph.dispatch(compute, TensorGraph.Conv, tensor_0, texture_tensor.set(stride = 2, padding = 1), tensors[0], TensorGraph.FlagReLU)
			
			# first max pool
			tensor_1 = Tensor(tensor_1_buffer)
			tensor_graph.dispatch(compute, TensorGraph.MaxPool, tensor_1, tensor_0.set(stride = 2))
			
			# first batch normalization
			tensor_2 = Tensor(tensor_0_buffer)
			tensor_graph.dispatch(compute, TensorGraph.BatchNorm, tensor_2, tensor_1, tensors[3], tensors[4])
			
			tensor_3 = Tensor(tensor_1_buffer)
			tensor_graph.dispatch(compute, TensorGraph.BatchMad, tensor_3, tensor_2, tensors[1], tensors[2])
			
			# second convolution
			tensor_4 = Tensor(tensor_0_buffer)
			tensor_graph.dispatch(compute, TensorGraph.Conv, tensor_4, tensor_3.set(stride = 2, padding = 1), tensors[5], TensorGraph.FlagReLU)
			
			# second max pool
			tensor_5 = Tensor(tensor_1_buffer)
			tensor_graph.dispatch(compute, TensorGraph.MaxPool, tensor_5, tensor_4.set(stride = 2))
			
			# second batch normalization
			tensor_6 = Tensor(tensor_0_buffer)
			tensor_graph.dispatch(compute, TensorGraph.BatchNorm, tensor_6, tensor_5, tensors[8], tensors[9])
			
			tensor_7 = Tensor(tensor_1_buffer)
			tensor_graph.dispatch(compute, TensorGraph.BatchMad, tensor_7, tensor_6, tensors[6], tensors[7])
			
			# matrix multiplication and addition
			tensor_8 = Tensor(tensor_0_buffer);
			tensor_7 = Tensor(tensor_7, tensor_7.width * tensor_7.height * tensor_7.depth, tensor_7.layers)
			tensor_graph.dispatch(compute, TensorGraph.MatMul, tensor_8, tensor_7, tensors[10], tensors[11], TensorGraph.FlagTranspose)
			
			compute = None
		
		# flush buffer
		device.flushBuffer(tensor_0_buffer)
		
		# window target
		if target.begin():
			
			# create command list
			command = device.createCommand(target)
			
			# draw surface
			command.setPipeline(pipeline)
			command.setSampler(0, sampler)
			command.setTexture(0, texture)
			command.setTexture(1, numbers)
			command.setStorageBuffer(0, tensor_0_buffer)
			command.drawArrays(3)
			
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

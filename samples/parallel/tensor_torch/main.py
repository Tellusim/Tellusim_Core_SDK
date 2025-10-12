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
	
	title = window.platform_name + ' Tellusim::TensorTorch Python'
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
	pipeline.setTextureMask(0, Shader.MaskFragment)
	pipeline.setColorFormat(window.color_format)
	pipeline.setDepthFormat(window.depth_format)
	if not pipeline.loadShaderGLSL(Shader.TypeVertex, 'main.shader', 'VERTEX_SHADER=1'): return 1
	if not pipeline.loadShaderGLSL(Shader.TypeFragment, 'main.shader', 'FRAGMENT_SHADER=1'): return 1
	if not pipeline.create(): return 1
	
	# create kernel
	kernel = device.createKernel().setUniforms(1).setStorages(1)
	if not kernel.loadShaderGLSL('main.shader', 'COMPUTE_SHADER=1'): return 1
	if not kernel.create(): return 1
	
	# create sampler
	sampler = device.createSampler(Sampler.FilterLinear, Sampler.WrapModeClamp)
	if not sampler: return 1
	
	# create texture
	texture = device.loadTexture('texture.jpg')
	if not texture: return 1
	
	# create surface
	surface = device.createTexture2D(FormatRGBAu8n, texture.width, texture.height, flags = Texture.FlagSurface)
	if not surface: return 1
	
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
	size = 64
	width = udiv(texture.width, size)
	height = udiv(texture.height, size)
	layers = width * height
	texture_buffer = device.createBuffer(Buffer.FlagStorage, size * size * 3 * layers * 4)
	texture_tensor = Tensor(texture_buffer, FormatRf32, size, size, 3, layers)
	if not texture_buffer: return 1
	
	# create temporary buffers
	tensor_0_buffer = device.createBuffer(Buffer.FlagStorage, texture_buffer.size)
	tensor_1_buffer = device.createBuffer(Buffer.FlagStorage, texture_buffer.size)
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
			tensor_graph.dispatch(compute, TensorGraph.Conv, tensor_0, texture_tensor.set(stride = 3, padding = 2), tensors[0], TensorGraph.FlagSiLU)
			
			# first batch normalization
			tensor_1 = Tensor(tensor_1_buffer)
			tensor_graph.dispatch(compute, TensorGraph.BatchMad, tensor_1, tensor_0, tensors[1], tensors[2])
			
			# second convolution
			tensor_2 = Tensor(tensor_0_buffer)
			tensor_graph.dispatch(compute, TensorGraph.Conv, tensor_2, tensor_1.set(stride = 2, padding = 2), tensors[5], TensorGraph.FlagSiLU)
			
			# second batch normalization
			tensor_3 = Tensor(tensor_1_buffer)
			tensor_graph.dispatch(compute, TensorGraph.BatchMad, tensor_3, tensor_2, tensors[6], tensors[7])
			
			# third convolution
			tensor_4 = Tensor(tensor_0_buffer)
			tensor_graph.dispatch(compute, TensorGraph.Conv, tensor_4, tensor_3.set(stride = 2, padding = 1), tensors[10], TensorGraph.FlagSiLU)
			
			# third batch normalization
			tensor_5 = Tensor(tensor_1_buffer)
			tensor_graph.dispatch(compute, TensorGraph.BatchMad, tensor_5, tensor_4, tensors[11], tensors[12])
			
			# fourth convolution
			tensor_6 = Tensor(tensor_0_buffer)
			tensor_graph.dispatch(compute, TensorGraph.Conv, tensor_6, tensor_5.set(stride = 1, padding = 1), tensors[15], TensorGraph.FlagSiLU)
			
			# quantize tensor
			compute.setKernel(kernel)
			compute.setUniform(0, tensor_6.size)
			compute.setStorageBuffer(0, tensor_6.buffer)
			compute.dispatch(tensor_6.width, tensor_6.height, tensor_6.depth * layers)
			compute.barrier(tensor_0_buffer)
			
			# first deconvolution
			tensor_7 = Tensor(tensor_1_buffer)
			tensor_graph.dispatch(compute, TensorGraph.DeConv, tensor_7, tensor_6.set(stride = 1, padding = 1), tensors[16], TensorGraph.FlagSiLU)
			
			# second deconvolution
			tensor_8 = Tensor(tensor_0_buffer)
			tensor_graph.dispatch(compute, TensorGraph.DeConv, tensor_8, tensor_7.set(stride = 2, padding = 1), tensors[17], TensorGraph.FlagSiLU)
			
			# third deconvolution
			tensor_9 = Tensor(tensor_1_buffer)
			tensor_graph.dispatch(compute, TensorGraph.DeConv, tensor_9, tensor_8.set(stride = 2, padding = 1), tensors[18], TensorGraph.FlagSiLU)
			
			# fourth deconvolution
			texture_tensor.padding = 1
			tensor_graph.dispatch(compute, TensorGraph.DeConv, texture_tensor, tensor_9.set(stride = 3, padding = 1), tensors[19], TensorGraph.FlagSigm)
			
			# copy tensor to texture
			tensor_graph.dispatch(compute, surface, texture_tensor)
			
			compute = None
		
		# flush surface
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

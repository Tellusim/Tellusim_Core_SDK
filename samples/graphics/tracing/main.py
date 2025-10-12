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
	
	title = window.getPlatformName() + ' Tellusim::Tracing Python'
	if not window.create(title) or not window.setHidden(False): return 1
	
	# scene size
	grid_size = 3
	num_instances = grid_size * 2 + 1
	num_instances2 = num_instances * num_instances
	
	# create device
	device = Device(window)
	if not device: return 1
	
	# check compute tracing support
	if not device.getFeatures().computeTracing:
		Log.print(Log.Error, 'compute tracing is not supported\n')
		return 0
	
	# create pipeline
	pipeline = device.createPipeline()
	pipeline.setTextureMask(0, Shader.MaskFragment)
	pipeline.setColorFormat(window.getColorFormat())
	pipeline.setDepthFormat(window.getDepthFormat())
	if not pipeline.loadShaderGLSL(Shader.TypeVertex, 'main.shader', 'VERTEX_SHADER=1'): return 1
	if not pipeline.loadShaderGLSL(Shader.TypeFragment, 'main.shader', 'FRAGMENT_SHADER=1'): return 1
	if not pipeline.create(): return 1
	
	# create vertex pipeline
	vertex_pipeline = device.createPipeline()
	vertex_pipeline.addAttribute(Pipeline.AttributePosition, FormatRGBf32, 0, offset = 0, stride = 32)
	vertex_pipeline.addAttribute(Pipeline.AttributeNormal, FormatRGBf32, 0, offset = 16, stride = 32)
	
	# create tracing pipeline
	tracing_pipeline = None
	if device.getFeatures().fragmentTracing:
		tracing_pipeline = device.createPipeline();
		tracing_pipeline.setUniformMask(0, Shader.MaskFragment);
		tracing_pipeline.setStorageMasks(0, 2, Shader.MaskFragment);
		tracing_pipeline.setTracingMask(0, Shader.MaskFragment);
		tracing_pipeline.setColorFormat(window.getColorFormat());
		tracing_pipeline.setDepthFormat(window.getDepthFormat());
		if not tracing_pipeline.loadShaderGLSL(Shader.TypeVertex, 'main.shader', 'VERTEX_SHADER=1'): return 1
		if not tracing_pipeline.loadShaderGLSL(Shader.TypeFragment, 'main.shader', 'FRAGMENT_SHADER=1; FRAGMENT_TRACING=1'): return 1
		if not tracing_pipeline.create(): return 1
	
	# create kernel
	kernel = device.createKernel().setUniforms(1).setStorages(2).setSurfaces(1).setTracings(1)
	if not kernel.loadShaderGLSL('main.shader', 'COMPUTE_SHADER=1; GROUP_SIZE=8u'): return 1
	if not kernel.create(): return 1
	
	# load mesh
	mesh = Mesh()
	src_mesh = Mesh()
	if not src_mesh.load('model.glb'): return 1
	if not MeshRefine.subdiv(mesh, src_mesh, 5): return 1
	mesh.createNormals()
	mesh.optimizeIndices(32)
	
	# create model geometry
	model_geometry = MeshModel()
	if not model_geometry.create(device, vertex_pipeline, mesh, MeshModel.DefaultFlags | MeshModel.FlagIndices32 | MeshModel.FlagBufferStorage | MeshModel.FlagBufferTracing | MeshModel.FlagBufferAddress): return 1
	vertex_buffer = model_geometry.getVertexBuffer()
	index_buffer = model_geometry.getIndexBuffer()
	
	# create model tracing
	model_tracing = device.createTracing()
	model_tracing.addVertexBuffer(model_geometry.getNumGeometryVertices(0), vertex_pipeline.getAttributeFormat(0), model_geometry.getVertexBufferStride(0), vertex_buffer)
	model_tracing.addIndexBuffer(model_geometry.getNumIndices(), model_geometry.getIndexFormat(), index_buffer)
	if not model_tracing.create(Tracing.TypeTriangle, Tracing.FlagCompact | Tracing.FlagFastTrace): return 1
	
	# create scratch buffer
	scratch_buffer = device.createBuffer(Buffer.FlagStorage | Buffer.FlagScratch, model_tracing.getBuildSize() + 1024 * 8)
	if not scratch_buffer: return 1
	
	# build model tracing
	if not device.buildTracing(model_tracing, scratch_buffer, Tracing.FlagCompact): return 1
	device.flushTracing(model_tracing)
	
	# create instances
	instances = []
	for i in range(num_instances2):
		instance = TracingInstance()
		instance.mask = 0xff
		instance.tracing = model_tracing
		instances.append(instance)
	
	# create instances buffer
	instances_buffer = device.createBuffer(Buffer.FlagStorage | Buffer.FlagTracing, 64 * num_instances2)
	if not instances_buffer: return 1
	
	# create instance tracing
	instance_tracing = device.createTracing(num_instances2, instances_buffer)
	if not instance_tracing: return 1
	
	# tracing surface
	surface = None
	
	# create target
	target = device.createTarget(window)
	
	# FPS counter
	fps_time = Time.seconds()
	fps_counter = 0
	
	# main loop
	def main_loop():
		nonlocal surface
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
		
		# common parameters
		common_parameters = bytearray()
		camera = Matrix4x4f.rotateZ(math.sin(time) * 4.0) * Vector4f(16.0, 0.0, 8.0, 0.0)
		projection = Matrix4x4f.perspective(70.0, window.getWidth() / window.getHeight(), 0.1, True)
		imodelview = Matrix4x4f.placeTo(camera.xyz, Vector3f(0.0, 0.0, -3.0), Vector3f(0.0, 0.0, 1.0))
		light = Vector4f(12.0, 0.0, 6.0, 0.0)
		common_parameters += projection
		common_parameters += imodelview
		common_parameters += camera
		common_parameters += light
		
		# instance parameters
		i = 0
		for y in range(-grid_size, grid_size + 1):
			for x in range(-grid_size, grid_size + 1):
				translate = Matrix4x3f.translate(x * 4.0, y * 4.0, 4.0)
				rotate = Matrix4x3f.rotateZ(time * 32.0) * Matrix4x3f.rotateX(90.0)
				scale = Matrix4x3f.scale(Vector3f(math.sin(time + i) * 0.2 + 0.8))
				instances[i].transform = translate * rotate * scale
				i += 1
		
		# build instance tracing
		if not device.setTracing(instance_tracing, instances): return False
		if not device.buildTracing(instance_tracing, scratch_buffer): return False
		device.flushTracing(instance_tracing)
		
		# fragment tracing
		if tracing_pipeline and window.getKeyboardKey(ord('1')):
			
			# window target
			if target.begin():
				
				# create command list
				command = device.createCommand(target)
				
				# draw surface
				command.setPipeline(tracing_pipeline)
				command.setUniform(0, common_parameters)
				command.setStorageBuffer(0, vertex_buffer)
				command.setStorageBuffer(1, index_buffer)
				command.setTracing(0, instance_tracing)
				command.drawArrays(3)
				
				command = None
				
				target.end()
			
		# compute tracing
		else:
			
			# create surface
			width = window.getWidth()
			height = window.getHeight()
			if surface == None or surface.getWidth() != width or surface.getHeight() != height:
				window.finish()
				surface = device.createTexture2D(FormatRGBAu8n, width, height, flags = Texture.FlagSurface)
			
			# trace scene
			if True:
				
				# create command list
				compute = device.createCompute()
				
				# dispatch kernel
				compute.setKernel(kernel)
				compute.setUniform(0, common_parameters)
				compute.setSurfaceTexture(0, surface)
				compute.setStorageBuffer(0, vertex_buffer)
				compute.setStorageBuffer(1, index_buffer)
				compute.setTracing(0, instance_tracing)
				compute.dispatch(surface)
				compute.barrier(surface)
				
				compute = None
			
			# flush surface
			device.flushTexture(surface)
			
			# window target
			if target.begin():
				
				# create command list
				command = device.createCommand(target)
				
				# draw surface
				command.setPipeline(pipeline)
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

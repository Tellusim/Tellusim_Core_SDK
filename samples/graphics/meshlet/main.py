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
	
	title = window.getPlatformName() + ' Tellusim::Meshlet Python'
	if not window.create(title) or not window.setHidden(False): return 1
	
	# scene size
	grid_size = 4
	num_instances = grid_size * 2 + 1
	num_instances2 = num_instances * num_instances
	
	# mesh parameters
	group_size = 32
	max_vertices = 64
	max_primitives = 126
	mesh_flags = MeshModel.FlagMeshlet64x126
	
	# create device
	device = Device(window)
	if not device: return 1
	
	# create common pipeline
	common_pipeline = device.createPipeline()
	common_pipeline.setColorFormat(window.getColorFormat())
	common_pipeline.setDepthFormat(window.getDepthFormat())
	common_pipeline.setDepthFunc(Pipeline.DepthFuncGreater)
	common_pipeline.setCullMode(Pipeline.CullModeFront if window.getPlatform() == PlatformVK else Pipeline.CullModeBack)
	
	# vertex pipeline
	vertex_pipeline = device.createPipeline(common_pipeline)
	vertex_pipeline.setUniformMask(0, Shader.MaskVertex)
	vertex_pipeline.setUniformMask(1, Shader.MaskVertex)
	vertex_pipeline.addAttribute(Pipeline.AttributePosition, FormatRGBf32, 0, offset = 0, stride = 32)
	vertex_pipeline.addAttribute(Pipeline.AttributeNormal, FormatRGBf32, 0, offset = 16, stride = 32)
	if not vertex_pipeline.loadShaderGLSL(Shader.TypeVertex, 'main.shader', 'VERTEX_PIPELINE=1; VERTEX_SHADER=1; NUM_INSTANCES={0}u'.format(num_instances2)): return 1
	if not vertex_pipeline.loadShaderGLSL(Shader.TypeFragment, 'main.shader', 'VERTEX_PIPELINE=1; FRAGMENT_SHADER=1'): return 1
	if not vertex_pipeline.create(): return 1
	
	# mesh pipeline
	mesh_pipeline = None
	if device.hasShader(Shader.TypeTask):
		mesh_pipeline = device.createPipeline(common_pipeline)
		mesh_pipeline.setUniformMask(0, Shader.MaskMesh)
		mesh_pipeline.setUniformMask(1, Shader.MaskTask | Shader.MaskMesh)
		mesh_pipeline.setStorageMasks(0, 3, Shader.MaskMesh)
		if not mesh_pipeline.loadShaderGLSL(Shader.TypeTask, 'main.shader', 'MESH_PIPELINE=1; TASK_SHADER=1'): return 1
		if not mesh_pipeline.loadShaderGLSL(Shader.TypeMesh, 'main.shader', 'MESH_PIPELINE=1; MESH_SHADER=1; GROUP_SIZE={0}u; NUM_VERTICES={1}u; NUM_PRIMITIVES={2}u; NUM_INSTANCES={3}u'.format(group_size, max_vertices, max_primitives, num_instances2)): return 1
		if not mesh_pipeline.loadShaderGLSL(Shader.TypeFragment, 'main.shader', 'MESH_PIPELINE=1; FRAGMENT_SHADER=1'): return 1
		if not mesh_pipeline.create(): return 1
	
	# compute pipeline
	draw_kernel = None
	clear_kernel = None
	compute_pipeline = None
	if device.hasShader(Shader.TypeCompute):
		
		# create compute pipeline
		compute_pipeline = device.createPipeline()
		compute_pipeline.setTextureMask(0, Shader.MaskFragment)
		compute_pipeline.setColorFormat(window.getColorFormat())
		compute_pipeline.setDepthFormat(window.getDepthFormat())
		if not compute_pipeline.loadShaderGLSL(Shader.TypeVertex, 'main.shader', 'COMPUTE_PIPELINE=1; VERTEX_SHADER=1'): return 1
		if not compute_pipeline.loadShaderGLSL(Shader.TypeFragment, 'main.shader', 'COMPUTE_PIPELINE=1; FRAGMENT_SHADER=1'): return 1
		if not compute_pipeline.create(): return 1
		
		# create draw kernel
		draw_kernel = device.createKernel().setSurfaces(2).setUniforms(2).setStorages(3)
		if not draw_kernel.loadShaderGLSL('main.shader', 'COMPUTE_PIPELINE=1; COMPUTE_DRAW_SHADER=1; GROUP_SIZE={0}u; NUM_VERTICES={1}u; NUM_PRIMITIVES={2}u; NUM_INSTANCES={3}u'.format(npot(max_primitives), max_vertices, max_primitives, num_instances2)): return 1
		if not draw_kernel.create(): return 1
		
		# create clear kernel
		clear_kernel = device.createKernel().setUniforms(1).setSurfaces(1)
		if not clear_kernel.loadShaderGLSL('main.shader', 'COMPUTE_PIPELINE=1; COMPUTE_CLEAR_SHADER=1'): return 1
		if not clear_kernel.create(): return 1
	
	# load mesh
	mesh = Mesh()
	src_mesh = Mesh()
	if not src_mesh.load('model.glb'): return 1
	if not MeshRefine.subdiv(mesh, src_mesh, 5): return 1
	mesh.createNormals()
	mesh.createIslands(max_vertices, max_primitives)
	
	# create vertex model
	vertex_model = MeshModel()
	if not vertex_model.create(device, vertex_pipeline, mesh, MeshModel.DefaultFlags): return 1
	
	# create mesh model
	mesh_model = MeshModel()
	if not mesh_model.create(device, vertex_pipeline, mesh, MeshModel.DefaultFlags | mesh_flags): return 1
	
	# mesh info
	num_meshlets = mesh_model.getNumMeshlets()
	num_vertices = num_instances2 * vertex_model.getNumVertices()
	num_primitives = num_instances2 * vertex_model.getNumIndices() // 3
	Log.printf(Log.Message, '  Vertices: %s\n', String.fromNumber(num_vertices))
	Log.printf(Log.Message, 'Primitives: %s\n', String.fromNumber(num_primitives))
	Log.printf(Log.Message, '  Meshlets: %u (%u)\n', num_meshlets * num_instances2, num_meshlets)
	Log.printf(Log.Message, ' Instances: %u\n', num_instances2)
	Log.printf(Log.Message, ' GroupSize: %u\n', group_size)
	
	# compute surfaces
	depth_surface = None
	color_surface = None
	
	# create target
	target = device.createTarget(window)
	target.setClearColor(0.2, 0.2, 0.2, 1.0)
	target.setClearDepth(0.0)
	
	# current mode
	mode = 'Vertex'
	if mesh_pipeline: mode = 'Mesh'
	if compute_pipeline: mode = 'Compute'
	
	# FPS counter
	fps_time = Time.seconds()
	fps_counter = 0
	
	# main loop
	def main_loop():
		nonlocal mode
		nonlocal depth_surface
		nonlocal color_surface
		nonlocal fps_counter
		nonlocal fps_time
		
		Window.update()
		
		if not window.render(): return False
		
		# switch mode
		if window.getKeyboardKey(ord('1')): mode = 'Vertex'
		elif window.getKeyboardKey(ord('2')) and mesh_pipeline: mode = 'Mesh'
		elif window.getKeyboardKey(ord('3')) and compute_pipeline: mode = 'Compute'
		
		# current time
		fps_counter += 1
		time = Time.seconds()
		if time - fps_time > 1.0:
			window.setTitle('{0} {1} {2:.1f} FPS'.format(title, mode, fps_counter / (time - fps_time)))
			fps_time = time
			fps_counter = 0
		
		# common parameters
		common_parameters = bytearray()
		camera = Vector4f(4.0 + grid_size * 3.0, 0.0, 1.0, 0.0)
		projection = Matrix4x4f.perspective(60.0, window.getWidth() / window.getHeight(), 0.1, reverse = True)
		modelview = Matrix4x4f.lookAt(camera.xyz, camera.xyz + Vector3f(-16.0, 0.0, -4.0), Vector3f(0.0, 0.0, 1.0))
		if target.isFlipped(): projection = Matrix4x4f.scale(1.0, -1.0, 1.0) * projection
		common_parameters += projection
		common_parameters += modelview
		common_parameters += camera
		
		# transform parameters
		transforms = bytearray()
		for y in range(-grid_size, grid_size + 1):
			for x in range(-grid_size, grid_size + 1):
				translate = Matrix4x3f.translate(x * 3.2, y * 3.2, 0.0)
				rotate = Matrix4x3f.rotateZ(time * 32.0 + y * 2715.53) * Matrix4x3f.rotateX(time * 16.0 + x * 9774.37)
				scale = Matrix4x3f.scale(Vector3f(math.sin(time + (x ^ y) * 13.73) * 0.2 + 0.8))
				transforms += translate * rotate * scale
		
		# compute rasterization
		if mode == 'Compute':
			
			# create surfaces
			if not depth_surface or depth_surface.getWidth() != window.getWidth() or depth_surface.getHeight() != window.getHeight():
				window.finish()
				depth_surface = device.createTexture2D(FormatRu32, window.getWidth(), window.getHeight(), flags = Texture.FlagSurface | Texture.FlagBuffer)
				color_surface = device.createTexture2D(FormatRu32, window.getWidth(), window.getHeight(), flags = Texture.FlagSurface | Texture.FlagBuffer)
			
			# create command list
			compute = device.createCompute()
			
			# clear depth surface
			compute.setKernel(clear_kernel)
			compute.setUniform(0, Scalarf(0.0))
			compute.setSurfaceTexture(0, depth_surface)
			compute.dispatch(depth_surface)
			compute.barrier(depth_surface)
			
			# clear color texture
			compute.setKernel(clear_kernel)
			compute.setUniform(0, Scalaru(target.getClearColor().getRGBAu8()))
			compute.setSurfaceTexture(0, color_surface)
			compute.dispatch(color_surface)
			compute.barrier(color_surface)
			
			# dispatch compute kernel
			compute.setKernel(draw_kernel)
			compute.setUniform(0, common_parameters)
			compute.setSurfaceTexture(0, depth_surface)
			compute.setSurfaceTexture(1, color_surface)
			compute.setStorage(0, transforms)
			compute.setStorageBuffer(1, mesh_model.getVertexBuffer())
			compute.setStorageBuffer(2, mesh_model.getMeshletBuffer())
			
			# compute parameters
			max_groups = device.getFeatures().maxGroupCountX
			for i in range(0, num_meshlets * num_instances2, max_groups):
				size = min(num_meshlets * num_instances2 - i, max_groups)
				compute_parameters = bytearray()
				compute_parameters += Vector2u(num_meshlets, i)
				compute_parameters += Vector2f(window.getWidth(), window.getHeight())
				compute_parameters += Scalarf(align(window.getWidth(), 64))
				compute.setUniform(1, compute_parameters)
				compute.dispatch(npot(max_primitives) * size)
			
			compute = None
			
			# flush surface
			device.flushTextures([ depth_surface, color_surface ])
		
		# window target
		if target.begin():
			
			# create command list
			command = device.createCommand(target)
			
			# mesh pipeline
			if mode == 'Mesh':
				
				command.setPipeline(mesh_pipeline)
				command.setUniform(0, common_parameters)
				command.setStorage(0, transforms)
				command.setStorageBuffer(1, mesh_model.getVertexBuffer())
				command.setStorageBuffer(2, mesh_model.getMeshletBuffer())
				
				max_meshlets = device.getFeatures().maxTaskMeshes
				for i in range(0, num_meshlets, max_meshlets):
					size = min(num_meshlets - i, max_meshlets)
					command.setUniform(1, Vector2u(size, i))
					command.drawMesh(num_instances2)
				
			# compute pipeline
			elif mode == 'Compute':
				
				command.setPipeline(compute_pipeline)
				command.setTexture(0, color_surface)
				command.drawArrays(3)
				
			# vertex pipeline
			else:
				
				command.setPipeline(vertex_pipeline)
				command.setUniform(0, common_parameters)
				command.setUniform(1, transforms)
				vertex_model.setBuffers(command)
				vertex_model.drawInstanced(command, 0, num_instances2)
			
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

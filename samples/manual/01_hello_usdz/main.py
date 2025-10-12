#!/usr/bin/env python3

# Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/

import sys
import math

from tellusimd import *

#
# create material texture
#
def create_texture(device, material, type):
	
	# find material parameter
	index = material.findParameter(type)
	if index == Maxu32 or not material.hasParameterFlag(index, MeshMaterial.FlagBlob): return None
	
	# load image
	image = Image()
	blob = material.getParameterBlob(index)
	if not image.load(blob): return None
	
	# create texture
	return device.createTexture(image, Texture.FlagMipmaps)

#
# main
#
def main(argv):
	
	# create app
	app = App(argv)
	if not app.create(): return 1
	
	# create window
	window = Window(app.getPlatform(), app.getDevice())
	if not window or not window.setSize(app.getWidth(), app.getHeight()): return 1
	if not window.create('01 Hello USDZ Python') or not window.setHidden(False): return 1
	window.setKeyboardPressedCallback(lambda key, code: window.stop() if key == Window.KeyEsc else None)
	
	# create device
	device = Device(window)
	if not device: return 1
	
	# create pipeline
	pipeline = device.createPipeline()
	pipeline.setSamplerMask(0, Shader.MaskFragment)
	pipeline.setTextureMasks(0, 3, Shader.MaskFragment)
	pipeline.setUniformMasks(0, 2, Shader.MaskVertex)
	pipeline.addAttribute(Pipeline.AttributePosition, FormatRGBf32, 0, offset = 0, stride = 80)
	pipeline.addAttribute(Pipeline.AttributeNormal, FormatRGBf32, 0, offset = 12, stride = 80)
	pipeline.addAttribute(Pipeline.AttributeTangent, FormatRGBAf32, 0, offset = 24, stride = 80)
	pipeline.addAttribute(Pipeline.AttributeTexCoord, FormatRGf32, 0, offset = 40, stride = 80)
	pipeline.addAttribute(Pipeline.AttributeWeights, FormatRGBAf32, 1, offset = 48, stride = 80)
	pipeline.addAttribute(Pipeline.AttributeJoints, FormatRGBAu32, 1, offset = 64, stride = 80)
	pipeline.setColorFormat(window.getColorFormat())
	pipeline.setDepthFormat(window.getDepthFormat())
	pipeline.setDepthFunc(Pipeline.DepthFuncLess)
	if not pipeline.loadShaderGLSL(Shader.TypeVertex, 'main.shader', 'VERTEX_SHADER=1'): return 1
	if not pipeline.loadShaderGLSL(Shader.TypeFragment, 'main.shader', 'FRAGMENT_SHADER=1'): return 1
	if not pipeline.create(): return 1
	
	# load mesh
	mesh = Mesh()
	if not mesh.load('model.usdz'): return 1
	if not mesh.getNumGeometries(): return 1
	if not mesh.getNumAnimations(): return 1
	mesh.setBasis(Mesh.BasisZUpRight)
	mesh.createTangents()
	
	# create model
	model = MeshModel()
	if not model.create(device, pipeline, mesh): return 1
	
	# create textures
	normal_textures = []
	diffuse_textures = []
	roughness_textures = []
	for geometry in mesh.getGeometries():
		for material in geometry.getMaterials():
			normal_textures.append(create_texture(device, material, MeshMaterial.TypeNormal))
			diffuse_textures.append(create_texture(device, material, MeshMaterial.TypeDiffuse))
			roughness_textures.append(create_texture(device, material, MeshMaterial.TypeRoughness))
	
	# create sampler
	sampler = device.createSampler(Sampler.FilterTrilinear, Sampler.WrapModeRepeat)
	if not sampler: return 1
	
	# create target
	target = device.createTarget(window)
	target.setClearColor(Color.gray)
	
	# main loop
	def main_loop():
		
		Window.update()
		
		if not window.render(): return False
		
		# window target
		if target.begin():
			
			# create command list
			command = device.createCommand(target)
			
			# set pipeline
			command.setPipeline(pipeline)
			
			# set sampler
			command.setSampler(0, sampler)
			
			# set model buffers
			model.setBuffers(command)
			
			# set common parameters
			camera = Vector4f(0.0, -180.0, 180.0, 0.0)
			projection = Matrix4x4f.perspective(60.0, window.getWidth() / window.getHeight(), 0.1, 1000.0)
			modelview = Matrix4x4f.lookAt(camera.xyz, Vector3f(0.0, 0.0, 80.0), Vector3f(0.0, 0.0, 1.0))
			if target.isFlipped(): projection = Matrix4x4f.scale(1.0, -1.0, 1.0) * projection
			common_parameters = bytearray(projection)
			common_parameters += modelview
			common_parameters += camera
			command.setUniform(0, common_parameters)
			
			# mesh animation
			time = Time.seconds()
			animation = mesh.getAnimation(0)
			animation.setTime(time, Matrix4x3d.rotateZ(math.sin(time) * 30.0))
			
			# draw geometries
			texture_index = 0
			for geometry in mesh.getGeometries():
				
				# joint transforms
				joint_parameters = bytearray()
				for joint in geometry.getJoints():
					transform = Matrix4x3f(animation.getGlobalTransform(joint)) * joint.getITransform() * geometry.getTransform()
					joint_parameters += transform.row_0
					joint_parameters += transform.row_1
					joint_parameters += transform.row_2
				command.setUniform(1, joint_parameters)
				
				# draw materials
				for material in geometry.getMaterials():
					command.setTexture(0, normal_textures[texture_index])
					command.setTexture(1, diffuse_textures[texture_index])
					command.setTexture(2, roughness_textures[texture_index])
					model.draw(command, geometry.getIndex(), material.getIndex())
					texture_index += 1
			
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

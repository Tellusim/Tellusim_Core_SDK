// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.main;

import com.tellusim.*

import kotlin.math.*

import java.nio.ByteOrder
import java.nio.ByteBuffer

/*
 */
fun create_texture(device: Device, material: MeshMaterial, type: String): Texture? {
	
	// find material parameter
	val index = material.findParameter(type)
	if(index == Base.Maxu32 || !material.hasParameterFlag(index, MeshMaterial.Flags.Blob)) return null
	
	// load image
	val image = Image()
	val blob = material.getParameterBlob(index)
	if(!image.load(blob)) return null
	
	// create texture
	return device.createTexture(image, Texture.Flags.Mipmaps)
}

/*
 */
fun main(args: Array<String>) {
	
	// load library
	Base.loadDebug()
	
	// create app
	val app = App(args)
	if(!app.create(Platform.Any)) return
	
	// create window
	val window = Window(app.platform, app.device)
	if(!window.isValidPtr() || !window.setSize(app.width, app.height)) return
	if(!window.create("01 Hello USDZ Kotlin") || !window.setHidden(false)) return
	window.setKeyboardPressedCallback(object: Window.KeyboardPressedCallback() {
		override fun run(key: Int, code: Int) {
			if(key == Window.Key.Esc.value) window.stop()
		}
	})
	
	// create device
	val device = Device(window)
	if(!device.isValidPtr()) return
	
	// create pipeline
	val pipeline = device.createPipeline()
	pipeline.setSamplerMask(0, Shader.Mask.Fragment)
	pipeline.setTextureMasks(0, 3, Shader.Mask.Fragment)
	pipeline.setUniformMasks(0, 2, Shader.Mask.Vertex)
	pipeline.addAttribute(Pipeline.Attribute.Position, Format.RGBf32, 0, 0, 80)
	pipeline.addAttribute(Pipeline.Attribute.Normal, Format.RGBf32, 0, 12, 80)
	pipeline.addAttribute(Pipeline.Attribute.Tangent, Format.RGBAf32, 0, 24, 80)
	pipeline.addAttribute(Pipeline.Attribute.TexCoord, Format.RGf32, 0, 40, 80)
	pipeline.addAttribute(Pipeline.Attribute.Weights, Format.RGBAf32, 0, 48, 80)
	pipeline.addAttribute(Pipeline.Attribute.Joints, Format.RGBAu32, 0, 64, 80)
	pipeline.setColorFormat(window.colorFormat)
	pipeline.setDepthFormat(window.depthFormat)
	pipeline.setDepthFunc(Pipeline.DepthFunc.Less)
	if(!pipeline.loadShaderGLSL(Shader.Type.Vertex, "main.shader", "VERTEX_SHADER=1")) return
	if(!pipeline.loadShaderGLSL(Shader.Type.Fragment, "main.shader", "FRAGMENT_SHADER=1")) return
	if(!pipeline.create()) return
	
	// load mesh
	val mesh = Mesh()
	if(!mesh.load("model.usdz")) return
	if(mesh.numGeometries == 0) return
	if(mesh.numAnimations == 0) return
	mesh.setBasis(Mesh.Basis.ZUpRight)
	mesh.createTangents()
	
	// create model
	val model = MeshModel()
	if(!model.create(device, pipeline, mesh)) return
	
	// create textures
	var normal_textures = ArrayList<Texture?>()
	var diffuse_textures = ArrayList<Texture?>()
	var roughness_textures = ArrayList<Texture?>()
	for(i in 0 .. mesh.numGeometries - 1) {
		val geometry = mesh.getGeometry(i)
		for(j in 0 .. geometry.numMaterials - 1) {
			val material = geometry.getMaterial(j)
			normal_textures.add(create_texture(device, material, "normal"))
			diffuse_textures.add(create_texture(device, material, "diffuse"))
			roughness_textures.add(create_texture(device, material, "roughness"))
		}
	}
	
	// create sampler
	val sampler = device.createSampler(Sampler.Filter.Trilinear, Sampler.WrapMode.Repeat)
	if(!sampler.isValidPtr()) return
	
	// create target
	val target = device.createTarget(window)
	target.clearColor = Color.gray()
	
	// main loop
	window.run(object: Window.MainLoopCallback() {
		override fun run(): Boolean {
			
			// update window
			Window.update()
			
			// render window
			if(!window.render()) return false
			
			// window target
			if(target.begin()) {
				
				// create command list
				val command = device.createCommand(target)
				
				// set pipeline
				command.setPipeline(pipeline)
				
				// set sampler
				command.setSampler(0, sampler)
				
				// set model buffers
				model.setBuffers(command)
				
				// common parameters
				val camera = Vector3f(0.0f, -180.0f, 180.0f)
				var projection = Matrix4x4f.perspective(60.0f, window.width.toFloat() / window.height.toFloat(), 0.1f, 1000.0f)
				val modelview = Matrix4x4f.lookAt(camera, Vector3f(0.0f, 0.0f, 80.0f), Vector3f(0.0f, 0.0f, 1.0f))
				if(target.isFlipped()) projection = Matrix4x4f.scale(1.0f, -1.0f, 1.0f) * projection
				val common_parameters = ByteBuffer.allocate(256).order(ByteOrder.LITTLE_ENDIAN)
				common_parameters.put(projection.bytes)
				common_parameters.put(modelview.bytes)
				common_parameters.put(camera.bytes)
				command.setUniform(0, common_parameters)
				
				// mesh animation
				val time = Time.seconds()
				val animation = mesh.getAnimation(0)
				animation.setTime(time, Matrix4x3d.rotateZ(Math.sin(time) * 30.0))
				
				// draw geometries
				var texture_index = 0
				var joint_parameters = arrayOfNulls<Matrix4x3f>(64)
				for(j in 0 .. mesh.numGeometries - 1) {
					val geometry = mesh.getGeometry(j)
					
					// joint transforms
					for(i in 0 .. geometry.numJoints - 1) {
						val joint = geometry.getJoint(i)
						joint_parameters[i] = Matrix4x3f(animation.getGlobalTransform(joint)) * joint.iTransform * geometry.transform
					}
					command.setUniform(1, joint_parameters)
					
					// draw materials
					for(i in 0 .. geometry.numMaterials - 1) {
						val material = geometry.getMaterial(i)
						command.setTexture(0, normal_textures.get(texture_index))
						command.setTexture(1, diffuse_textures.get(texture_index))
						command.setTexture(2, roughness_textures.get(texture_index))
						model.draw(command, geometry.index, material.index)
						texture_index++
					}
				}
				
				command.destroyPtr()
			}
			target.end()
			
			// present window
			if(!window.present()) return false
			
			// check device
			if(!device.check()) return false
			
			// memory
			System.gc()
			
			return true
		}
	})
	
	// finish context
	window.finish()
}

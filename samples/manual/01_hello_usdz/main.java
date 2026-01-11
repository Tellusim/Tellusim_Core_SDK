// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.main;

import com.tellusim.*;

import java.lang.Math;
import java.nio.ByteOrder;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;

/*
 */
public class main {
	
	/*
	 */
	static {
		Base.loadDebug();
	}
	
	/*
	 */
	static Texture create_texture(Device device, MeshMaterial material, String type) {
		
		// find material parameter
		int index = material.findParameter(type);
		if(index == Base.Maxu32 || !material.hasParameterFlag(index, MeshMaterial.Flags.Blob)) return null;
		
		// load image
		Image image = new Image();
		Blob blob = material.getParameterBlob(index);
		if(!image.load(blob)) return null;
		
		// create texture
		return device.createTexture(image, Texture.Flags.Mipmaps);
	}
	
	/*
	 */
	public static void main(String[] args) {
		
		// create app
		App app = new App(args);
		if(!app.create(Platform.Any)) return;
		
		// create window
		Window window = new Window(app.getPlatform(), app.getDevice());
		if(!window.isValidPtr() || !window.setSize(app.getWidth(), app.getHeight())) return;
		if(!window.create("01 Hello USDZ Java") || !window.setHidden(false)) return;
		window.setKeyboardPressedCallback(new Window.KeyboardPressedCallback() {
			public void run(int key, int code) {
				if(key == Window.Key.Esc.value) window.stop();
			}
		});
		
		// create device
		Device device = new Device(window);
		if(!device.isValidPtr()) return;
		
		// create pipeline
		Pipeline pipeline = device.createPipeline();
		pipeline.setSamplerMask(0, Shader.Mask.Fragment);
		pipeline.setTextureMasks(0, 3, Shader.Mask.Fragment);
		pipeline.setUniformMasks(0, 2, Shader.Mask.Vertex);
		pipeline.addAttribute(Pipeline.Attribute.Position, Format.RGBf32, 0, 0, 80);
		pipeline.addAttribute(Pipeline.Attribute.Normal, Format.RGBf32, 0, 12, 80);
		pipeline.addAttribute(Pipeline.Attribute.Tangent, Format.RGBAf32, 0, 24, 80);
		pipeline.addAttribute(Pipeline.Attribute.TexCoord, Format.RGf32, 0, 40, 80);
		pipeline.addAttribute(Pipeline.Attribute.Weights, Format.RGBAf32, 0, 48, 80);
		pipeline.addAttribute(Pipeline.Attribute.Joints, Format.RGBAu32, 0, 64, 80);
		pipeline.setColorFormat(window.getColorFormat());
		pipeline.setDepthFormat(window.getDepthFormat());
		pipeline.setDepthFunc(Pipeline.DepthFunc.Less);
		if(!pipeline.loadShaderGLSL(Shader.Type.Vertex, "main.shader", "VERTEX_SHADER=1")) return;
		if(!pipeline.loadShaderGLSL(Shader.Type.Fragment, "main.shader", "FRAGMENT_SHADER=1")) return;
		if(!pipeline.create()) return;
		
		// load mesh
		Mesh mesh = new Mesh();
		if(!mesh.load("model.usdz")) return;
		if(mesh.getNumGeometries() == 0) return;
		if(mesh.getNumAnimations() == 0) return;
		mesh.setBasis(Mesh.Basis.ZUpRight);
		mesh.createTangents();
		
		// create model
		MeshModel model = new MeshModel();
		if(!model.create(device, pipeline, mesh)) return;
		
		// create textures
		List<Texture> normal_textures = new ArrayList<Texture>();
		List<Texture> diffuse_textures = new ArrayList<Texture>();
		List<Texture> roughness_textures = new ArrayList<Texture>();
		for(int i = 0; i < mesh.getNumGeometries(); i++) {
			MeshGeometry geometry = mesh.getGeometry(i);
			for(int j = 0; j < geometry.getNumMaterials(); j++) {
				MeshMaterial material = geometry.getMaterial(j);
				normal_textures.add(create_texture(device, material, "normal"));
				diffuse_textures.add(create_texture(device, material, "diffuse"));
				roughness_textures.add(create_texture(device, material, "roughness"));
			}
		}
		
		// create sampler
		Sampler sampler = device.createSampler(Sampler.Filter.Trilinear, Sampler.WrapMode.Repeat);
		if(!sampler.isValidPtr()) return;
		
		// create target
		Target target = device.createTarget(window);
		target.setClearColor(Color.gray());
		
		// main loop
		window.run(new Window.MainLoopCallback() {
			public boolean run() {
				
				// update window
				Window.update();
				
				// render window
				if(!window.render()) return false;
				
				// window target
				target.begin();
				{
					// create command list
					Command command = device.createCommand(target);
					
					// set pipeline
					command.setPipeline(pipeline);
					
					// set sampler
					command.setSampler(0, sampler);
					
					// set model buffers
					model.setBuffers(command);
					
					// common parameters
					Vector3f camera = new Vector3f(0.0f, -180.0f, 180.0f);
					Matrix4x4f projection = Matrix4x4f.perspective(60.0f, (float)window.getWidth() / (float)window.getHeight(), 0.1f, 1000.0f);
					Matrix4x4f modelview = Matrix4x4f.lookAt(camera, new Vector3f(0.0f, 0.0f, 80.0f), new Vector3f(0.0f, 0.0f, 1.0f));
					if(target.isFlipped()) projection = Matrix4x4f.scale(1.0f, -1.0f, 1.0f).mul(projection);
					ByteBuffer common_parameters = ByteBuffer.allocate(256).order(ByteOrder.LITTLE_ENDIAN);
					common_parameters.put(projection.getBytes());
					common_parameters.put(modelview.getBytes());
					common_parameters.put(camera.getBytes());
					command.setUniform(0, common_parameters);
					
					// mesh animation
					double time = Time.seconds();
					MeshAnimation animation = mesh.getAnimation(0);
					animation.setTime(time, Matrix4x3d.rotateZ(Math.sin(time) * 30.0));
					
					// draw geometries
					int texture_index = 0;
					Matrix4x3f[] joint_parameters = new Matrix4x3f[64];
					for(int j = 0; j < mesh.getNumGeometries(); j++) {
						MeshGeometry geometry = mesh.getGeometry(j);
						
						// joint transforms
						for(int i = 0; i < geometry.getNumJoints(); i++) {
							MeshJoint joint = geometry.getJoint(i);
							joint_parameters[i] = (new Matrix4x3f(animation.getGlobalTransform(joint))).mul(joint.getITransform()).mul(geometry.getTransform());
						}
						command.setUniform(1, joint_parameters);
						
						// draw materials
						for(int i = 0; i < geometry.getNumMaterials(); i++) {
							MeshMaterial material = geometry.getMaterial(i);
							command.setTexture(0, normal_textures.get(texture_index));
							command.setTexture(1, diffuse_textures.get(texture_index));
							command.setTexture(2, roughness_textures.get(texture_index));
							model.draw(command, geometry.getIndex(), material.getIndex());
							texture_index++;
						}
					}
					
					command.destroyPtr();
				}
				target.end();
				
				// present window
				if(!window.present()) return false;
				
				// check device
				if(!device.check()) return false;
				
				// memory
				System.gc();
				
				return true;
			}
		});
		
		// finish context
		window.finish();
	}
}

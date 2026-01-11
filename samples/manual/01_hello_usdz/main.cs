// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

using System;
using Tellusim;
using System.Collections.Generic;
using System.Runtime.InteropServices;

/*
 */
class USDZ {
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct CommonParameters {
		public Matrix4x4f projection;
		public Matrix4x4f modelview;
		public Vector4f camera;
	}
	
	/*
	 */
	static Texture create_texture(Device device, MeshMaterial material, string type) {
		
		// find material parameter
		uint index = material.findParameter(type);
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
	[STAThread]
	static void Main(string[] args) {
		
		// create app
		App app = new App(args);
		if(!app.create(Platform.Any)) return;
		
		// create window
		Window window = new Window(app.getPlatform(), app.getDevice());
		if(!window || !window.setSize(app.getWidth(), app.getHeight())) return;
		if(!window.create("01 Hello USDZ CSharp") || !window.setHidden(false)) return;
		window.setKeyboardPressedCallback((uint key, uint code, IntPtr data) => { if(key == (uint)Window.Key.Esc) window.stop(); });
		
		// create device
		Device device = new Device(window);
		if(!device) return;
		
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
		List<Texture> normal_textures = new List<Texture>();
		List<Texture> diffuse_textures = new List<Texture>();
		List<Texture> roughness_textures = new List<Texture>();
		for(uint i = 0; i < mesh.getNumGeometries(); i++) {
			MeshGeometry geometry = mesh.getGeometry(i);
			for(uint j = 0; j < geometry.getNumMaterials(); j++) {
				MeshMaterial material = geometry.getMaterial(j);
				normal_textures.Add(create_texture(device, material, "normal"));
				diffuse_textures.Add(create_texture(device, material, "diffuse"));
				roughness_textures.Add(create_texture(device, material, "roughness"));
			}
		}
		
		// create sampler
		Sampler sampler = device.createSampler(Sampler.Filter.Trilinear, Sampler.WrapMode.Repeat);
		if(!sampler) return;
		
		// create target
		Target target = device.createTarget(window);
		target.setClearColor(Color.gray);
		
		// main loop
		window.run((IntPtr data) => {
			
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
				CommonParameters common_parameters = new CommonParameters();
				common_parameters.camera = new Vector4f(0.0f, -180.0f, 180.0f, 0.0f);
				common_parameters.projection = Matrix4x4f.perspective(60.0f, (float)window.getWidth() / (float)window.getHeight(), 0.1f, 1000.0f);
				common_parameters.modelview = Matrix4x4f.lookAt(new Vector3f(common_parameters.camera), new Vector3f(0.0f, 0.0f, 80.0f), new Vector3f(0.0f, 0.0f, 1.0f));
				if(target.isFlipped()) common_parameters.projection = Matrix4x4f.scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
				command.setUniform(0, common_parameters);
				
				// mesh animation
				double time = Time.seconds();
				MeshAnimation animation = mesh.getAnimation(0);
				animation.setTime(time, Matrix4x3d.rotateZ(Math.Sin(time) * 30.0));
				
				// draw geometries
				int texture_index = 0;
				Matrix4x3f[] joint_parameters = new Matrix4x3f[64];
				for(uint j = 0; j < mesh.getNumGeometries(); j++) {
					MeshGeometry geometry = mesh.getGeometry(j);
					
					// joint transforms
					for(uint i = 0; i < geometry.getNumJoints(); i++) {
						MeshJoint joint = geometry.getJoint(i);
						joint_parameters[i] = new Matrix4x3f(animation.getGlobalTransform(joint)) * joint.getITransform() * geometry.getTransform();
					}
					command.setUniform(1, joint_parameters);
					
					// draw materials
					for(uint i = 0; i < geometry.getNumMaterials(); i++) {
						MeshMaterial material = geometry.getMaterial(i);
						command.setTexture(0, normal_textures[texture_index]);
						command.setTexture(1, diffuse_textures[texture_index]);
						command.setTexture(2, roughness_textures[texture_index]);
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
			GC.Collect();
			GC.WaitForPendingFinalizers();
			
			return true;
		});
		
		// finish context
		window.finish();
		
		// keep window alive
		window.unacquirePtr();
	}
}

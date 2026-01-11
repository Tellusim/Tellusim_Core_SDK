// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

using System;
using Tellusim;
using Buffer = Tellusim.Buffer;
using tsTracing = Tellusim.Tracing;
using System.Runtime.InteropServices;

/*
 */
class Tracing {
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct CommonParameters {
		public Matrix4x4f projection;
		public Matrix4x4f imodelview;
		public Vector4f camera;
		public Vector4f light;
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
		if(!window) return;
		
		window.setSize(app.getWidth(), app.getHeight());
		window.setCloseClickedCallback((IntPtr data) => { window.stop(); });
		window.setKeyboardPressedCallback((uint key, uint code, IntPtr data) => { if(key == (uint)Window.Key.Esc) window.stop(); });
		
		string title = window.getPlatformName() + " Tellusim::Tracing CSharp";
		if(!window.create(title) || !window.setHidden(false)) return;
		
		// scene size
		const int grid_size = 3;
		const uint num_instances = grid_size * 2 + 1;
		const uint num_instances2 = num_instances * num_instances;
		
		// create device
		Device device = new Device(window);
		if(!device) return;
		
		// check compute tracing support
		if(!device.getFeatures().computeTracing) {
			Log.print(Log.Level.Error, "compute tracing is not supported\n");
			return;
		}
		
		// create pipeline
		Pipeline pipeline = device.createPipeline();
		pipeline.setTextureMask(0, Shader.Mask.Fragment);
		pipeline.setColorFormat(window.getColorFormat());
		pipeline.setDepthFormat(window.getDepthFormat());
		if(!pipeline.loadShaderGLSL(Shader.Type.Vertex, "main.shader", "VERTEX_SHADER=1")) return;
		if(!pipeline.loadShaderGLSL(Shader.Type.Fragment, "main.shader", "FRAGMENT_SHADER=1")) return;
		if(!pipeline.create()) return;
		
		// create vertex pipeline
		Pipeline vertex_pipeline = device.createPipeline();
		vertex_pipeline.addAttribute(Pipeline.Attribute.Position, Format.RGBf32, 0, 0, 32);
		vertex_pipeline.addAttribute(Pipeline.Attribute.Normal, Format.RGBf32, 0, 16, 32);
		
		// create kernel
		Kernel kernel = device.createKernel().setUniforms(1).setStorages(2).setSurfaces(1).setTracings(1);
		if(!kernel.loadShaderGLSL("main.shader", "COMPUTE_SHADER=1; GROUP_SIZE=8u")) return;
		if(!kernel.create()) return;
		
		// load mesh
		Mesh mesh = new Mesh();
		Mesh src_mesh = new Mesh();
		if(!src_mesh.load("model.glb")) return;
		if(!MeshRefine.subdiv(mesh, src_mesh, 5)) return;
		mesh.createNormals();
		mesh.optimizeIndices(32);
		
		// create model geometry
		MeshModel model_geometry = new MeshModel();
		if(!model_geometry.create(device, vertex_pipeline, mesh, MeshModel.Flags.Default | MeshModel.Flags.Indices32 | MeshModel.Flags.BufferStorage | MeshModel.Flags.BufferTracing | MeshModel.Flags.BufferAddress)) return;
		Buffer vertex_buffer = model_geometry.getVertexBuffer();
		Buffer index_buffer = model_geometry.getIndexBuffer();
		
		// create model tracing
		tsTracing model_tracing = device.createTracing();
		model_tracing.addVertexBuffer(model_geometry.getNumGeometryVertices(0), vertex_pipeline.getAttributeFormat(0), model_geometry.getVertexBufferStride(0), vertex_buffer);
		model_tracing.addIndexBuffer(model_geometry.getNumIndices(), model_geometry.getIndexFormat(), index_buffer);
		if(!model_tracing.create(tsTracing.Type.Triangle, tsTracing.Flags.Compact | tsTracing.Flags.FastTrace)) return;
		
		// create scratch buffer
		Buffer scratch_buffer = device.createBuffer(Buffer.Flags.Storage | Buffer.Flags.Scratch, model_tracing.getBuildSize() + 1024 * 8);
		if(!scratch_buffer) return;
		
		// build model tracing
		if(!device.buildTracing(model_tracing, scratch_buffer, tsTracing.Flags.Compact)) return;
		device.flushTracing(model_tracing);
		
		// create instances
		tsTracing.Instance[] instances = new tsTracing.Instance[num_instances2];
		for(uint i = 0; i < num_instances2; i++) {
			instances[i].mask = 0xff;
			instances[i].tracing = model_tracing.getSelfPtr();
		}
		
		// create instances buffer
		Buffer instances_buffer = device.createBuffer(Buffer.Flags.Storage | Buffer.Flags.Tracing, 64 * num_instances2);
		if(!instances_buffer) return;
		
		// create instance tracing
		tsTracing instance_tracing = device.createTracing(num_instances2, instances_buffer);
		if(!instance_tracing) return;
		
		// tracing surface
		Texture surface = null;
		
		// create target
		Target target = device.createTarget(window);
		
		// main loop
		window.run((IntPtr data) => {
			
			// update window
			Window.update();
			
			// render window
			if(!window.render()) return false;
			
			// current time
			float time = (float)Time.seconds();
			
			// common parameters
			CommonParameters common_parameters = new CommonParameters();
			common_parameters.camera = Matrix4x4f.rotateZ((float)Math.Sin(time) * 4.0f) * new Vector4f(16.0f, 0.0f, 8.0f, 0.0f);
			common_parameters.projection = Matrix4x4f.perspective(70.0f, (float)window.getWidth() / window.getHeight(), 0.1f, true);
			common_parameters.imodelview = Matrix4x4f.placeTo(new Vector3f(common_parameters.camera), new Vector3f(0.0f, 0.0f, -3.0f), new Vector3f(0.0f, 0.0f, 1.0f));
			common_parameters.light = new Vector4f(12.0f, 0.0f, 6.0f, 0.0f);
			
			// instance parameters
			for(int i = 0, y = -grid_size; y <= grid_size; y++) {
				for(int x = -grid_size; x <= grid_size; x++, i++) {
					Matrix4x3f translate = Matrix4x3f.translate(x * 4.0f, y * 4.0f, 4.0f);
					Matrix4x3f scale = Matrix4x3f.scale((float)Math.Sin(time + i) * 0.2f + 0.8f);
					Matrix4x3f rotate = Matrix4x3f.rotateZ(time * 32.0f) * Matrix4x3f.rotateX(90.0f);
					instances[i].transform = translate * rotate * scale;
				}
			}
			
			// build instance tracing
			if(!device.setTracing(instance_tracing, instances)) return false;
			if(!device.buildTracing(instance_tracing, scratch_buffer)) return false;
			device.flushTracing(instance_tracing);
			
			// create surface
			uint width = window.getWidth();
			uint height = window.getHeight();
			if(!surface || surface.getWidth() != width || surface.getHeight() != height) {
				window.finish();
				surface = device.createTexture2D(Format.RGBAu8n, width, height, Texture.Flags.Surface);
			}
			
			// trace scene
			{
				// create command list
				Compute compute = device.createCompute();
				
				// dispatch kernel
				compute.setKernel(kernel);
				compute.setUniform(0, common_parameters);
				compute.setSurfaceTexture(0, surface);
				compute.setStorageBuffer(0, vertex_buffer);
				compute.setStorageBuffer(1, index_buffer);
				compute.setTracing(0, instance_tracing);
				compute.dispatch(surface);
				compute.barrier(surface);
				
				compute.destroyPtr();
			}
			
			// flush surface
			device.flushTexture(surface);
			
			// window target
			target.begin();
			{
				Command command = device.createCommand(target);
				
				// draw surface
				command.setPipeline(pipeline);
				command.setTexture(0, surface);
				command.drawArrays(3);
				
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

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

using System;
using Tellusim;
using Buffer = Tellusim.Buffer;
using System.Runtime.InteropServices;

/*
 */
class Tracing {
	
	// current mode
	enum Mode {
		Vertex = 0,
		Mesh,
		Compute,
	};
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct CommonParameters {
		public Matrix4x4f projection;
		public Matrix4x4f modelview;
		public Vector4f camera;
	}
	
	[StructLayout(LayoutKind.Sequential)]
	struct ComputeParameters {
		public uint num_meshlets;
		public uint group_offset;
		public Vector2f surface_size;
		public float surface_stride;
	};
	
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
		
		string title = window.getPlatformName() + " Tellusim::Meshlet CSharp";
		if(!window.create(title) || !window.setHidden(false)) return;
		
		// scene size
		const int grid_size = 4;
		const uint num_instances = grid_size * 2 + 1;
		const uint num_instances2 = num_instances * num_instances;
		
		// mesh parameters
		const uint group_size = 32;
		const uint max_vertices = 64;
		const uint max_primitives = 126;
		MeshModel.Flags mesh_flags = MeshModel.Flags.Meshlet64x126;
		
		// create device
		Device device = new Device(window);
		if(!device) return;
		
		// create common pipeline
		Pipeline common_pipeline = device.createPipeline();
		common_pipeline.setColorFormat(window.getColorFormat());
		common_pipeline.setDepthFormat(window.getDepthFormat());
		common_pipeline.setDepthFunc(Pipeline.DepthFunc.Greater);
		common_pipeline.setCullMode((window.getPlatform() == Platform.VK) ? Pipeline.CullMode.Front : Pipeline.CullMode.Back);
		
		// vertex pipeline
		Pipeline vertex_pipeline = device.createPipeline(common_pipeline);
		vertex_pipeline.setUniformMask(0, Shader.Mask.Vertex);
		vertex_pipeline.setUniformMask(1, Shader.Mask.Vertex);
		vertex_pipeline.addAttribute(Pipeline.Attribute.Position, Format.RGBf32, 0, 0, 32);
		vertex_pipeline.addAttribute(Pipeline.Attribute.Normal, Format.RGBf32, 0, 16, 32);
		if(!vertex_pipeline.loadShaderGLSL(Shader.Type.Vertex, "main.shader", "VERTEX_PIPELINE=1; VERTEX_SHADER=1; NUM_INSTANCES={0}u", num_instances2)) return;
		if(!vertex_pipeline.loadShaderGLSL(Shader.Type.Fragment, "main.shader", "VERTEX_PIPELINE=1; FRAGMENT_SHADER=1")) return;
		if(!vertex_pipeline.create()) return;
		
		// mesh pipeline
		Pipeline mesh_pipeline = null;
		if(device.hasShader(Shader.Type.Task)) {
			mesh_pipeline = device.createPipeline(common_pipeline);
			mesh_pipeline.setUniformMask(0, Shader.Mask.Mesh);
			mesh_pipeline.setUniformMask(1, Shader.Mask.Task | Shader.Mask.Mesh);
			mesh_pipeline.setStorageMasks(0, 3, Shader.Mask.Mesh);
			if(!mesh_pipeline.loadShaderGLSL(Shader.Type.Task, "main.shader", "MESH_PIPELINE=1; TASK_SHADER=1")) return;
			if(!mesh_pipeline.loadShaderGLSL(Shader.Type.Mesh, "main.shader", "MESH_PIPELINE=1; MESH_SHADER=1; GROUP_SIZE={0}u; NUM_VERTICES={1}u; NUM_PRIMITIVES={2}u; NUM_INSTANCES={3}u", group_size, max_vertices, max_primitives, num_instances2)) return;
			if(!mesh_pipeline.loadShaderGLSL(Shader.Type.Fragment, "main.shader", "MESH_PIPELINE=1; FRAGMENT_SHADER=1")) return;
			if(!mesh_pipeline.create()) return;
		}
		
		// compute pipeline
		Kernel draw_kernel = null;
		Kernel clear_kernel = null;
		Pipeline compute_pipeline = null;
		if(device.hasShader(Shader.Type.Compute)) {
			
			// create compute pipeline
			compute_pipeline = device.createPipeline();
			compute_pipeline.setTextureMask(0, Shader.Mask.Fragment);
			compute_pipeline.setColorFormat(window.getColorFormat());
			compute_pipeline.setDepthFormat(window.getDepthFormat());
			if(!compute_pipeline.loadShaderGLSL(Shader.Type.Vertex, "main.shader", "COMPUTE_PIPELINE=1; VERTEX_SHADER=1")) return;
			if(!compute_pipeline.loadShaderGLSL(Shader.Type.Fragment, "main.shader", "COMPUTE_PIPELINE=1; FRAGMENT_SHADER=1")) return;
			if(!compute_pipeline.create()) return;
			
			// create draw kernel
			draw_kernel = device.createKernel().setSurfaces(2).setUniforms(2).setStorages(3);
			if(!draw_kernel.loadShaderGLSL("main.shader", "COMPUTE_PIPELINE=1; COMPUTE_DRAW_SHADER=1; COLOR_SHADING=1; GROUP_SIZE={0}u; NUM_VERTICES={1}u; NUM_PRIMITIVES={2}u; NUM_INSTANCES={3}u", Base.npot(max_primitives), max_vertices, max_primitives, num_instances2)) return;
			if(!draw_kernel.create()) return;
			
			// create clear kernel
			clear_kernel = device.createKernel().setUniforms(1).setSurfaces(1);
			if(!clear_kernel.loadShaderGLSL("main.shader", "COMPUTE_PIPELINE=1; COMPUTE_CLEAR_SHADER=1")) return;
			if(!clear_kernel.create()) return;
		}
		
		// load mesh
		Mesh mesh = new Mesh();
		Mesh src_mesh = new Mesh();
		if(!src_mesh.load("model.glb")) return;
		if(!MeshRefine.subdiv(mesh, src_mesh, 5)) return;
		mesh.createNormals();
		mesh.createIslands(max_vertices, max_primitives);
		
		// create vertex model
		MeshModel vertex_model = new MeshModel();
		if(!vertex_model.create(device, vertex_pipeline, mesh, MeshModel.Flags.Default)) return;
		
		// create mesh model
		MeshModel mesh_model = new MeshModel();
		if(!mesh_model.create(device, vertex_pipeline, mesh, MeshModel.Flags.Default | mesh_flags)) return;
		Buffer mesh_vertex_buffer = mesh_model.getVertexBuffer();
		Buffer mesh_meshlet_buffer = mesh_model.getMeshletBuffer();
		
		// mesh info
		uint num_meshlets = mesh_model.getNumMeshlets();
		uint num_vertices = num_instances2 * vertex_model.getNumVertices();
		uint num_primitives = num_instances2 * vertex_model.getNumIndices() / 3;
		Log.printf(Log.Level.Message, "  Vertices: {0}\n", Tellusim.String.fromNumber(num_vertices));
		Log.printf(Log.Level.Message, "Primitives: {0}\n", Tellusim.String.fromNumber(num_primitives));
		Log.printf(Log.Level.Message, "  Meshlets: {0} ({1})\n", num_meshlets * num_instances2, num_meshlets);
		Log.printf(Log.Level.Message, " Instances: {0}\n", num_instances2);
		Log.printf(Log.Level.Message, " GroupSize: {0}\n", group_size);
		
		// compute surfaces
		Texture depth_surface = null;
		Texture color_surface = null;
		
		// create target
		Target target = device.createTarget(window);
		target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		target.setClearDepth(0.0f);
		
		// current mode
		Mode mode = Mode.Vertex;
		if(mesh_pipeline) mode = Mode.Mesh;
		if(compute_pipeline) mode = Mode.Compute;
		
		// instance transforms
		Matrix4x3f[] transforms = new Matrix4x3f[num_instances2];
		
		// main loop
		window.run((IntPtr data) => {
			
			// update window
			Window.update();
			
			// render window
			if(!window.render()) return false;
			
			// switch mode
			if(window.getKeyboardKey('1')) mode = Mode.Vertex;
			else if(window.getKeyboardKey('2') && mesh_pipeline) mode = Mode.Mesh;
			else if(window.getKeyboardKey('3') && compute_pipeline) mode = Mode.Compute;
			
			// current time
			float time = (float)Time.seconds();
			
			// common parameters
			CommonParameters common_parameters = new CommonParameters();
			common_parameters.camera = new Vector4f(4.0f + grid_size * 3.0f, 0.0f, 1.0f, 0.0f);
			common_parameters.projection = Matrix4x4f.perspective(60.0f, (float)window.getWidth() / window.getHeight(), 0.1f, true);
			common_parameters.modelview = Matrix4x4f.lookAt(new Vector3f(common_parameters.camera), new Vector3f(common_parameters.camera) + new Vector3f(-16.0f, 0.0f, -4.0f), new Vector3f(0.0f, 0.0f, 1.0f));
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f.scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			
			// transform parameters
			for(int i = 0, y = -grid_size; y <= grid_size; y++) {
				for(int x = -grid_size; x <= grid_size; x++, i++) {
					Matrix4x3f translate = Matrix4x3f.translate(x * 3.2f, y * 3.2f, 0.0f);
					Matrix4x3f rotate = Matrix4x3f.rotateZ(time * 32.0f + y * 2715.53f) * Matrix4x3f.rotateX(time * 16.0f + x * 9774.37f);
					Matrix4x3f scale = Matrix4x3f.scale((float)Math.Sin(time + (x ^ y) * 13.73f) * 0.2f + 0.8f);
					transforms[i] = translate * rotate * scale;
				}
			}
			
			// compute rasterization
			if(mode == Mode.Compute) {
				
				// create surfaces
				if(!depth_surface || depth_surface.getWidth() != window.getWidth() || depth_surface.getHeight() != window.getHeight()) {
					window.finish();
					depth_surface = device.createTexture2D(Format.Ru32, window.getWidth(), window.getHeight(), Texture.Flags.Surface | Texture.Flags.Buffer);
					color_surface = device.createTexture2D(Format.Ru32, window.getWidth(), window.getHeight(), Texture.Flags.Surface | Texture.Flags.Buffer);
				}
				
				// create command list
				Compute compute = device.createCompute();
				
				// clear depth surface
				compute.setKernel(clear_kernel);
				compute.setUniform(0, 0.0f);
				compute.setSurfaceTexture(0, depth_surface);
				compute.dispatch(depth_surface);
				compute.barrier(depth_surface);
				
				// clear color texture
				compute.setKernel(clear_kernel);
				compute.setUniform(0, target.getClearColor().getBGRAu8());
				compute.setSurfaceTexture(0, color_surface);
				compute.dispatch(color_surface);
				compute.barrier(color_surface);
				
				// compute parameters
				ComputeParameters compute_parameters;
				compute_parameters.num_meshlets = num_meshlets;
				compute_parameters.surface_size = new Vector2f(window.getWidth(), window.getHeight());
				compute_parameters.surface_stride = (float)Base.align(window.getWidth(), 64);
				
				// dispatch compute kernel
				compute.setKernel(draw_kernel);
				compute.setUniform(0, common_parameters);
				compute.setSurfaceTexture(0, depth_surface);
				compute.setSurfaceTexture(1, color_surface);
				compute.setStorage(0, transforms);
				compute.setStorageBuffer(1, mesh_vertex_buffer);
				compute.setStorageBuffer(2, mesh_meshlet_buffer);
				uint max_groups = device.getFeatures().maxGroupCountX;
				for(uint i = 0; i < num_meshlets * num_instances2; i += max_groups) {
					uint size = Base.min(num_meshlets * num_instances2 - i, max_groups);
					compute_parameters.group_offset = i;
					compute.setUniform(1, compute_parameters);
					compute.dispatch(Base.npot(max_primitives) * size);
				}
				
				// flush surface
				device.flushTexture(depth_surface);
				device.flushTexture(color_surface);
				
				compute.destroyPtr();
			}
			
			// window target
			target.begin();
			{
				// create command list
				Command command = device.createCommand(target);
				
				// mesh pipeline
				if(mode == Mode.Mesh) {
					command.setPipeline(mesh_pipeline);
					command.setUniform(0, common_parameters);
					command.setStorage(0, transforms);
					command.setStorageBuffer(1, mesh_vertex_buffer);
					command.setStorageBuffer(2, mesh_meshlet_buffer);
					uint max_meshlets = device.getFeatures().maxTaskMeshes;
					for(uint i = 0; i < num_meshlets; i += max_meshlets) {
						uint size = Base.min(num_meshlets - i, max_meshlets);
						command.setUniform(1, new Vector2u(size, i));
						command.drawMesh(num_instances2);
					}
				}
				// compute pipeline
				else if(mode == Mode.Compute) {
					command.setPipeline(compute_pipeline);
					command.setTexture(0, color_surface);
					command.drawArrays(3);
				}
				// vertex pipeline
				else {
					command.setPipeline(vertex_pipeline);
					command.setUniform(0, common_parameters);
					command.setUniform(1, transforms);
					vertex_model.setBuffers(command);
					vertex_model.drawInstanced(command, 0, num_instances2);
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

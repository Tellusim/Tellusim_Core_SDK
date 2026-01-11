// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

using System;
using Tellusim;
using Buffer = Tellusim.Buffer;
using System.Collections.Generic;

/*
 */
class TensorTorch {
	
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
		
		string title = window.getPlatformName() + " Tellusim::TensorMnist CSharp";
		if(!window.create(title) || !window.setHidden(false)) return;
		
		// create device
		Device device = new Device(window);
		if(!device) return;
		
		// check compute tracing support
		if(!device.hasShader(Shader.Type.Compute)) {
			Log.print(Log.Level.Error, "compute shader is not supported\n");
			return;
		}
		
		// create pipeline
		Pipeline pipeline = device.createPipeline();
		pipeline.setSamplerMask(0, Shader.Mask.Fragment);
		pipeline.setTextureMasks(0, 2, Shader.Mask.Fragment);
		pipeline.setStorageMask(0, Shader.Mask.Fragment);
		pipeline.setColorFormat(window.getColorFormat());
		pipeline.setDepthFormat(window.getDepthFormat());
		if(!pipeline.loadShaderGLSL(Shader.Type.Vertex, "main.shader", "VERTEX_SHADER=1")) return;
		if(!pipeline.loadShaderGLSL(Shader.Type.Fragment, "main.shader", "FRAGMENT_SHADER=1")) return;
		if(!pipeline.create()) return;
		
		// create sampler
		Sampler sampler = device.createSampler(Sampler.Filter.Linear, Sampler.WrapMode.Clamp);
		if(!sampler) return;
		
		// create textures
		Texture texture = device.loadTexture("texture.png");
		Texture numbers = device.loadTexture("numbers.png");
		if(!texture || !numbers) return;
		
		// create tensor graph
		TensorGraph tensor_graph = new TensorGraph();
		if(!tensor_graph.create(device, TensorGraph.Flags.All & ~TensorGraph.Flags.FormatRf16)) return;
		
		// model tensors
		List<Tensor> tensors = new List<Tensor>();
		
		// load model
		Source source = new Source();
		if(!source.open("model.bin")) return;
		while(source.isAvailable()) {
			uint size = source.readu8();
			if(size == 0xff) break;
			Tensor tensor = new Tensor(0);
			if(size > 3) tensor.layers = source.readu16();
			if(size > 2) tensor.depth = source.readu16();
			if(size > 1) tensor.height = source.readu16();
			if(size > 0) tensor.width = source.readu16();
			tensor.offset = source.readu32() * 4;
			string name = source.readString('\0');
			Log.printf(Log.Level.Message, "{0}: {1} [{2}x{3}x{4}x{5}]\n", tensors.Count, name, tensor.width, tensor.height, tensor.depth, tensor.layers);
			tensors.Add(tensor);
		}
		
		// model weights
		float[] weights = new float[source.readu32()];
		if(source.read(ref weights) != (ulong)weights.Length * 4) return;
		Buffer weights_buffer = device.createBuffer(Buffer.Flags.Storage, weights);
		if(!weights_buffer) return;
		
		// tensor buffer
		for(int i = 0; i < tensors.Count; i++) {
			Tensor tensor = tensors[i];
			tensor.buffer = weights_buffer.getSelfPtr();
			tensor.format = Format.Rf32;
			tensors[i] = tensor;
		}
		
		// create texture tensor
		uint tile = 28;
		uint width = Base.udiv(texture.getWidth(), tile);
		uint height = Base.udiv(texture.getHeight(), tile);
		uint layers = width * height;
		Buffer texture_buffer = device.createBuffer(Buffer.Flags.Storage, tile * tile * layers * 4);
		Tensor texture_tensor = new Tensor(texture_buffer, Format.Rf32, tile, tile, 1, layers);
		if(!texture_buffer) return;
		
		// create temporary buffer
		Buffer tensor_0_buffer = device.createBuffer(Buffer.Flags.Storage, 1024 * 1024 * 16);
		Buffer tensor_1_buffer = device.createBuffer(Buffer.Flags.Storage, 1024 * 1024 * 16);
		if(!tensor_0_buffer || !tensor_1_buffer) return;
		
		// create target
		Target target = device.createTarget(window);
		
		// main loop
		window.run((IntPtr data) => {
			
			// update window
			Window.update();
			
			// render window
			if(!window.render()) return false;
			
			// trace scene
			{
				// create command list
				Compute compute = device.createCompute();
				
				// copy texture to tensor
				tensor_graph.dispatch(compute, texture_tensor, texture, texture.getSlice());
				
				// first convolution
				Tensor tensor_0 = new Tensor(tensor_0_buffer);
				tensor_graph.dispatch(compute, TensorGraph.Operation.Conv, ref tensor_0, texture_tensor.setStride(2).setPadding(1), tensors[0], TensorGraph.Flags.ReLU);
				
				// first max pool
				Tensor tensor_1 = new Tensor(tensor_1_buffer);
				tensor_graph.dispatch(compute, TensorGraph.Operation.MaxPool, ref tensor_1, tensor_0.setStride(2));
				
				// first batch normalization
				Tensor tensor_2 = new Tensor(tensor_0_buffer);
				tensor_graph.dispatch(compute, TensorGraph.Operation.BatchNorm, ref tensor_2, tensor_1, tensors[3], tensors[4]);
				
				Tensor tensor_3 = new Tensor(tensor_1_buffer);
				tensor_graph.dispatch(compute, TensorGraph.Operation.BatchMad, ref tensor_3, tensor_2, tensors[1], tensors[2]);
				
				// second convolution
				Tensor tensor_4 = new Tensor(tensor_0_buffer);
				tensor_graph.dispatch(compute, TensorGraph.Operation.Conv, ref tensor_4, tensor_3.setStride(2).setPadding(1), tensors[5], TensorGraph.Flags.ReLU);
				
				// second max pool
				Tensor tensor_5 = new Tensor(tensor_1_buffer);
				tensor_graph.dispatch(compute, TensorGraph.Operation.MaxPool, ref tensor_5, tensor_4.setStride(2));
				
				// second batch normalization
				Tensor tensor_6 = new Tensor(tensor_0_buffer);
				tensor_graph.dispatch(compute, TensorGraph.Operation.BatchNorm, ref tensor_6, tensor_5, tensors[8], tensors[9]);
				
				Tensor tensor_7 = new Tensor(tensor_1_buffer);
				tensor_graph.dispatch(compute, TensorGraph.Operation.BatchMad, ref tensor_7, tensor_6, tensors[6], tensors[7]);
				
				// matrix multiplication and addition
				Tensor tensor_8 = new Tensor(tensor_0_buffer);
				tensor_7 = new Tensor(tensor_7, tensor_7.width * tensor_7.height * tensor_7.depth, tensor_7.layers);
				tensor_graph.dispatch(compute, TensorGraph.Operation.MatMul, ref tensor_8, tensor_7, tensors[10], tensors[11], TensorGraph.Flags.Transpose);
				
				compute.destroyPtr();
			}
			
			// flush buffer
			device.flushBuffer(tensor_0_buffer);
			
			// window target
			target.begin();
			{
				Command command = device.createCommand(target);
				
				// draw surface
				command.setPipeline(pipeline);
				command.setSampler(0, sampler);
				command.setTexture(0, texture);
				command.setTexture(1, numbers);
				command.setStorageBuffer(0, tensor_0_buffer);
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

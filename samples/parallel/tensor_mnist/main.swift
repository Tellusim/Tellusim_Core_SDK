// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

import Tellusim

/*
 */
func main() -> Int32 {
	
	// create app
	let app = App()
	if !app.create(Platform.Any, UInt32(App.Values.Version.rawValue)) { return 1 }
	
	// create window
	let window = Window(app.platform(), app.device())
	if !window { return 1 }
	
	window.setSize(app.width(), app.height())
	
	window.setCloseClickedCallback(Window.CloseClickedFunction({ () in
		window.stop()
	}))
	
	window.setKeyboardPressedCallback(Window.KeyboardPressedFunction({ (key: UInt32, code: UInt32) in
		if key == Window.Key.Esc.rawValue { window.stop() }
	}))
	
	let title = window.platformName() + " Tellusim::TensorMnist Swift"
	if !window.create(title) || !window.setHidden(false) { return 1 }
	
	// create device
	let device = Device(window)
	if !device { return 1 }
	
	// check compute shader support
	if !device.hasShader(Shader.Kind.Compute) {
		Log.print(Log.Level.Error, "compute shader is not supported\n")
		return 0
	}
	
	// shader cache
	Shader.setCache("main.cache")
	
	// create pipeline
	let pipeline = device.createPipeline()
	pipeline.setSamplerMask(0, Shader.Mask.Fragment)
	pipeline.setTextureMasks(0, 2, Shader.Mask.Fragment)
	pipeline.setStorageMask(0, Shader.Mask.Fragment)
	pipeline.setColorFormat(window.colorFormat())
	pipeline.setDepthFormat(window.depthFormat())
	if !pipeline.loadShaderGLSL(Shader.Kind.Vertex, "main.shader", "VERTEX_SHADER=1") { return 1 }
	if !pipeline.loadShaderGLSL(Shader.Kind.Fragment, "main.shader", "FRAGMENT_SHADER=1") { return 1 }
	if !pipeline.create() { return 1 }
	
	// create sampler
	let sampler = device.createSampler(Sampler.Filter.Linear, Sampler.WrapMode.Clamp)
	if !sampler { return 1 }
	
	// create textures
	let texture = device.loadTexture("texture.png")
	let numbers = device.loadTexture("numbers.png")
	if !texture || !numbers { return 1 }
	
	// create tensor graph
	let tensor_graph = TensorGraph()
	if !tensor_graph.create(device, TensorGraph.Flags.All & ~TensorGraph.Flags.FormatRf16) { return 1 }
	
	// model tensors
	var tensors = [Tensor]()
	
	// load model
	let source = Source()
	if !source.open("model.bin") { return 1 }
	while source.isAvailable() {
		let size = source.readu8()
		if size == 0xff { break }
		var tensor = Tensor(0)
		if size > 3 { tensor.layers = UInt32(source.readu16()) }
		if size > 2 { tensor.depth = UInt32(source.readu16()) }
		if size > 1 { tensor.height = UInt32(source.readu16()) }
		if size > 0 { tensor.width = UInt32(source.readu16()) }
		tensor.offset = Int(source.readu32()) * 4
		let name = source.readString(0)
		Log.print(Log.Level.Message, String(format: "%u: %@ [%ux%ux%ux%u]\n", tensors.count, name, tensor.width, tensor.height, tensor.depth, tensor.layers))
		tensors.append(tensor)
	}
	
	// model weights
	var weights = [Float32](repeating: 0, count: Int(source.readu32()))
	if source.read(&weights, weights.count * 4) != weights.count * 4 { return 1 }
	let weights_buffer = device.createBuffer(Buffer.Flags.Storage, &weights, weights.count * 4)
	if !weights_buffer { return 1 }
	
	// tensor buffer
	for i in 0 ..< tensors.count {
		tensors[i].buffer = weights_buffer.getSelfPtr()
		tensors[i].format = UInt32(Format.Rf32.rawValue)
	}
	
	// create texture tensor
	let size = UInt32(28)
	let width = udiv(texture.width(), size)
	let height = udiv(texture.height(), size)
	let layers = width * height
	let texture_buffer = device.createBuffer(Buffer.Flags.Storage, Int(size * size * layers * 4))
	let texture_tensor = Tensor(texture_buffer, Format.Rf32, size, size, 1, layers)
	if !texture_buffer { return 1 }
	
	// create temporary buffers
	let tensor_0_buffer = device.createBuffer(Buffer.Flags.Storage, 1024 * 1024 * 16)
	let tensor_1_buffer = device.createBuffer(Buffer.Flags.Storage, 1024 * 1024 * 16)
	if !tensor_0_buffer || !tensor_1_buffer { return 1 }
	
	// create target
	let target = device.createTarget(window)
	
	// main loop
	window.run(Window.MainLoopFunction({ () -> Bool in
		
		// update window
		Window.update()
		
		// render window
		if !window.render() { return false }
		
		if true {
			
			// create command list
			let compute = device.createCompute()
			
			// copy texture to tensor
			tensor_graph.dispatch(compute, texture_tensor, texture)
			
			// first convolution
			var tensor_0 = Tensor(tensor_0_buffer)
			tensor_graph.dispatch(compute, TensorGraph.Operation.Conv, &tensor_0, texture_tensor.setStride(2).setPadding(1), tensors[0], TensorGraph.Flags.ReLU)
			
			// first max pool
			var tensor_1 = Tensor(tensor_1_buffer)
			tensor_graph.dispatch(compute, TensorGraph.Operation.MaxPool, &tensor_1, tensor_0.setStride(2))
			
			// first batch normalization
			var tensor_2 = Tensor(tensor_0_buffer)
			tensor_graph.dispatch(compute, TensorGraph.Operation.BatchNorm, &tensor_2, tensor_1, tensors[3], tensors[4])
			
			var tensor_3 = Tensor(tensor_1_buffer)
			tensor_graph.dispatch(compute, TensorGraph.Operation.BatchMad, &tensor_3, tensor_2, tensors[1], tensors[2])
			
			// second convolution
			var tensor_4 = Tensor(tensor_0_buffer)
			tensor_graph.dispatch(compute, TensorGraph.Operation.Conv, &tensor_4, tensor_3.setStride(2).setPadding(1), tensors[5], TensorGraph.Flags.ReLU)
			
			// second max pool
			var tensor_5 = Tensor(tensor_1_buffer)
			tensor_graph.dispatch(compute, TensorGraph.Operation.MaxPool, &tensor_5, tensor_4.setStride(2))
			
			// second batch normalization
			var tensor_6 = Tensor(tensor_0_buffer)
			tensor_graph.dispatch(compute, TensorGraph.Operation.BatchNorm, &tensor_6, tensor_5, tensors[8], tensors[9])
			
			var tensor_7 = Tensor(tensor_1_buffer)
			tensor_graph.dispatch(compute, TensorGraph.Operation.BatchMad, &tensor_7, tensor_6, tensors[6], tensors[7])
			
			// matrix multiplication and addition
			var tensor_8 = Tensor(tensor_0_buffer)
			tensor_7 = Tensor(tensor_7, tensor_7.width * tensor_7.height * tensor_7.depth, tensor_7.layers)
			tensor_graph.dispatch(compute, TensorGraph.Operation.MatMul, &tensor_8, tensor_7, tensors[10], tensors[11], TensorGraph.Flags.Transpose)
		}
		
		// flush buffer
		device.flushBuffer(tensor_0_buffer)
		
		// window target
		if target.begin() {
			
			// create command list
			let command = device.createCommand(target)
			
			// draw surface
			command.setPipeline(pipeline)
			command.setSampler(0, sampler)
			command.setTexture(0, texture)
			command.setTexture(1, numbers)
			command.setStorageBuffer(0, tensor_0_buffer)
			command.drawArrays(3)
		}
		target.end()
		
		if !window.present() { return false }
		
		// check errors
		if !device.check() { return false }
		
		return true
	}))
	
	// finish context
	window.finish()
	
	return 0
}

/*
 */
print(main())

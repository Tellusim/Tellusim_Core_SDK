// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#if _MACOS || _IOS
	#include <Metal/Metal.h>
#endif

#include <common/common.h>
#include <common/sample_controls.h>
#include <format/TellusimMesh.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCompute.h>
#include <platform/TellusimCommand.h>
#include <geometry/TellusimMeshRefine.h>
#include <graphics/TellusimMeshModel.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Meshlet", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// scene size
	constexpr int32_t grid_size = 4;
	constexpr uint32_t num_instances = grid_size * 2 + 1;
	constexpr uint32_t num_instances2 = num_instances * num_instances;
	
	// command line arguments
	uint32_t mode_index = Maxu32;
	uint32_t meshlet_mode = Maxu32;
	if(app.isArgument("mode")) mode_index = app.getArgument("mode").tou32();
	if(app.isArgument("meshlet")) meshlet_mode = app.getArgument("meshlet").tou32();
	
	// mesh parameters
	uint32_t max_vertices = 0;
	uint32_t max_primitives = 0;
	constexpr uint32_t group_size = 32;
	if(meshlet_mode == Maxu32) meshlet_mode = 1;
	MeshModel::Flags mesh_flags = MeshModel::FlagNone;
	if(meshlet_mode == 0) {
		max_vertices = 64;
		max_primitives = 84;
		mesh_flags = MeshModel::FlagMeshlet64x84;
	} else if(meshlet_mode == 1) {
		max_vertices = 64;
		max_primitives = 126;
		mesh_flags = MeshModel::FlagMeshlet64x126;
	} else if(meshlet_mode == 2) {
		max_vertices = 96;
		max_primitives = 169;
		mesh_flags = MeshModel::FlagMeshlet96x169;
	} else if(meshlet_mode == 3) {
		max_vertices = 128;
		max_primitives = 212;
		mesh_flags = MeshModel::FlagMeshlet128x212;
	} else {
		return 1;
	}
	
	// structures
	struct Vertex {
		float32_t position[4];
		float32_t normal[4];
	};
	
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Vector4f camera;
	};
	
	struct ComputeParameters {
		uint32_t num_meshlets;
		uint32_t group_offset;
		Vector2f surface_size;
		float32_t surface_stride;
		uint32_t padding[3];
	};
	
	struct IndexingParameters {
		uint32_t num_meshlets;
		uint32_t base_group;
	};
	
	struct IndirectParameters {
		uint32_t num_instances;
		uint32_t num_meshlets;
		uint32_t num_indices;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create common pipeline
	Pipeline common_pipeline = device.createPipeline();
	common_pipeline.setColorFormat(window.getColorFormat());
	common_pipeline.setDepthFormat(window.getDepthFormat());
	common_pipeline.setDepthFunc(Pipeline::DepthFuncGreater);
	common_pipeline.setCullMode((window.getPlatform() == PlatformVK) ? Pipeline::CullModeFront : Pipeline::CullModeBack);
	
	// vertex pipeline
	Pipeline vertex_pipeline = device.createPipeline(common_pipeline);
	vertex_pipeline.setUniformMask(0, Shader::MaskVertex);
	vertex_pipeline.setUniformMask(1, Shader::MaskVertex);
	vertex_pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, offsetof(Vertex, position), sizeof(Vertex));
	vertex_pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, offsetof(Vertex, normal), sizeof(Vertex));
	if(!vertex_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_PIPELINE=1; VERTEX_SHADER=1; NUM_INSTANCES=%uu", num_instances2)) return 1;
	if(!vertex_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "VERTEX_PIPELINE=1; FRAGMENT_SHADER=1")) return 1;
	if(!vertex_pipeline.create()) return 1;
	
	// create primitive pipeline
	Pipeline primitive_pipeline = device.createPipeline(common_pipeline);
	primitive_pipeline.setUniformMasks(0, 2, Shader::MaskVertex);
	primitive_pipeline.setStorageMasks(0, 3, Shader::MaskVertex);
	if(!primitive_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1; NUM_PRIMITIVES=%uu; PRIMITIVE_PIPELINE=1", max_primitives)) return 1;
	if(!primitive_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "PRIMITIVE_PIPELINE=1; FRAGMENT_SHADER=1")) return 1;
	if(!primitive_pipeline.create()) return 1;
	
	// create indexing pipeline
	Pipeline indexing_pipeline = device.createPipeline(common_pipeline);
	indexing_pipeline.setUniformMasks(0, 2, Shader::MaskVertex);
	indexing_pipeline.setStorageMasks(0, 3, Shader::MaskVertex);
	if(!indexing_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1; NUM_PRIMITIVES=%uu; INDEXING_PIPELINE=1", max_primitives)) return 1;
	if(!indexing_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "INDEXING_PIPELINE=1; FRAGMENT_SHADER=1")) return 1;
	if(!indexing_pipeline.create()) return 1;
	
	// create indirect pipeline
	Pipeline indirect_pipeline = device.createPipeline(common_pipeline);
	indirect_pipeline.setUniformMask(0, Shader::MaskVertex);
	indirect_pipeline.setUniformMask(1, Shader::MaskVertex);
	indirect_pipeline.addAttribute(Pipeline::AttributePosition, FormatRGBf32, 0, offsetof(Vertex, position), sizeof(Vertex));
	indirect_pipeline.addAttribute(Pipeline::AttributeNormal, FormatRGBf32, 0, offsetof(Vertex, normal), sizeof(Vertex));
	indirect_pipeline.addAttribute(Pipeline::AttributeTexCoord, FormatRu32, 1, 0, sizeof(uint32_t), 1);
	if(!indirect_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1; NUM_INSTANCES=%uu; INDIRECT_PIPELINE=1", num_instances2)) return 1;
	if(!indirect_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "INDIRECT_PIPELINE=1; FRAGMENT_SHADER=1")) return 1;
	#if _MACOS || _IOS
		MTLPipeline(indirect_pipeline).setIndirect(true);
	#endif
	if(!indirect_pipeline.create()) return 1;
	
	// mesh pipeline
	Pipeline mesh_pipeline;
	if(device.hasShader(Shader::TypeTask)) {
		mesh_pipeline = device.createPipeline(common_pipeline);
		mesh_pipeline.setUniformMask(0, Shader::MaskMesh);
		mesh_pipeline.setUniformMask(1, Shader::MaskTask | Shader::MaskMesh);
		mesh_pipeline.setStorageMasks(0, 3, Shader::MaskMesh);
		if(!mesh_pipeline.loadShaderGLSL(Shader::TypeTask, "main.shader", "MESH_PIPELINE=1; TASK_SHADER=1")) return 1;
		if(!mesh_pipeline.loadShaderGLSL(Shader::TypeMesh, "main.shader", "MESH_PIPELINE=1; MESH_SHADER=1; GROUP_SIZE=%uu; NUM_VERTICES=%uu; NUM_PRIMITIVES=%uu; NUM_INSTANCES=%uu", group_size, max_vertices, max_primitives, num_instances2)) return 1;
		if(!mesh_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "MESH_PIPELINE=1; FRAGMENT_SHADER=1")) return 1;
		if(!mesh_pipeline.create()) return 1;
	}
	
	// compute pipeline
	Kernel clear_kernel;
	Kernel draw_shading_kernel;
	Kernel draw_solid_kernel;
	Pipeline compute_pipeline;
	if(device.hasShader(Shader::TypeCompute)) {
		
		// create compute pipeline
		compute_pipeline = device.createPipeline();
		compute_pipeline.setTextureMask(0, Shader::MaskFragment);
		compute_pipeline.setColorFormat(window.getColorFormat());
		compute_pipeline.setDepthFormat(window.getDepthFormat());
		if(!compute_pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "COMPUTE_PIPELINE=1; VERTEX_SHADER=1")) return 1;
		if(!compute_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "COMPUTE_PIPELINE=1; FRAGMENT_SHADER=1")) return 1;
		if(!compute_pipeline.create()) return 1;
		
		// create clear kernel
		clear_kernel = device.createKernel().setUniforms(1).setSurfaces(1);
		if(!clear_kernel.loadShaderGLSL("main.shader", "COMPUTE_PIPELINE=1; COMPUTE_CLEAR_SHADER=1")) return 1;
		if(!clear_kernel.create()) return 1;
		
		// create draw shading kernel
		draw_shading_kernel = device.createKernel().setSurfaces(2).setUniforms(2).setStorages(3);
		if(!draw_shading_kernel.loadShaderGLSL("main.shader", "COMPUTE_PIPELINE=1; COMPUTE_DRAW_SHADER=1; COLOR_SHADING=1; GROUP_SIZE=%uu; NUM_VERTICES=%uu; NUM_PRIMITIVES=%uu; NUM_INSTANCES=%uu", npot(max_primitives), max_vertices, max_primitives, num_instances2)) return 1;
		if(!draw_shading_kernel.create()) return 1;
		
		// create draw index kernel
		draw_solid_kernel = device.createKernel().setSurfaces(2).setUniforms(2).setStorages(3);
		if(!draw_solid_kernel.loadShaderGLSL("main.shader", "COMPUTE_PIPELINE=1; COMPUTE_DRAW_SHADER=1; COLOR_SOLID=1; GROUP_SIZE=%uu; NUM_VERTICES=%uu; NUM_PRIMITIVES=%uu; NUM_INSTANCES=%uu", npot(max_primitives), max_vertices, max_primitives, num_instances2)) return 1;
		if(!draw_solid_kernel.create()) return 1;
	}
	
	// create indexing kernel
	uint32_t indexing_group = npot(udiv(max_primitives, 4));
	Kernel indexing_kernel = device.createKernel().setUniforms(1).setStorages(2);
	if(!indexing_kernel.loadShaderGLSL("main.shader", "GROUP_SIZE=%uu; INDEXING_SHADER=1", indexing_group)) return 1;
	if(!indexing_kernel.create()) return 1;
	
	// create indirect kernel
	Kernel indirect_kernel = device.createKernel().setUniforms(1).setStorages(3);
	if(!indirect_kernel.loadShaderGLSL("main.shader", "INDIRECT_SHADER=1")) return 1;
	if(!indirect_kernel.create()) return 1;
	
	// create command kernel
	#if _MACOS || _IOS
		MTLKernel command_kernel = MTLKernel(move(device.createKernel().setUniforms(1).setStorages(3)));
		if(!command_kernel.loadShader("main.shader", "COMMAND_SHADER=1")) return 1;
		if(!command_kernel.create()) return 1;
	#endif
	
	// load mesh
	Mesh mesh, src_mesh;
	if(!src_mesh.load("model.glb")) return 1;
	if(!MeshRefine::subdiv(mesh, src_mesh, 5)) return 1;
	mesh.createNormals();
	mesh.createIslands(max_vertices, max_primitives);
	
	// create vertex model
	MeshModel vertex_model;
	if(!vertex_model.create(device, vertex_pipeline, mesh, MeshModel::DefaultFlags)) return 1;
	
	// create mesh model
	MeshModel mesh_model;
	if(!mesh_model.create(device, vertex_pipeline, mesh, MeshModel::DefaultFlags | mesh_flags)) return 1;
	Buffer mesh_vertex_buffer = mesh_model.getVertexBuffer();
	Buffer mesh_meshlet_buffer = mesh_model.getMeshletBuffer();
	
	// mesh info
	uint32_t num_meshlets = mesh_model.getNumMeshlets();
	uint32_t num_vertices = num_instances2 * vertex_model.getNumVertices();
	uint32_t num_primitives = num_instances2 * vertex_model.getNumIndices() / 3;
	TS_LOGF(Message, "  Vertices: %s\n", String::fromNumber(num_vertices).get());
	TS_LOGF(Message, "Primitives: %s\n", String::fromNumber(num_primitives).get());
	TS_LOGF(Message, "  Meshlets: %u (%u)\n", num_meshlets * num_instances2, num_meshlets);
	TS_LOGF(Message, " Instances: %u\n", num_instances2);
	TS_LOGF(Message, " GroupSize: %u\n", group_size);
	TS_LOGF(Message, "    Vertex: %s\n", String::fromBytes(mesh_vertex_buffer.getSize()).get());
	TS_LOGF(Message, "   Meshlet: %s\n", String::fromBytes(mesh_meshlet_buffer.getSize()).get());
	
	// create instance buffer
	Array<uint32_t> instance_data;
	instance_data.reserve(num_meshlets * num_instances2);
	for(uint32_t i = 0; i < num_instances2; i++) {
		for(uint32_t j = 0; j < num_meshlets; j++) {
			instance_data.append((i << 16) | j);
		}
	}
	Buffer instance_buffer = device.createBuffer(Buffer::FlagVertex, instance_data.get(), instance_data.bytes());
	TS_LOGF(Message, "  Instance: %s\n", String::fromBytes(instance_buffer.getSize()).get());
	
	// create indexing buffer
	Buffer indexing_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagIndex, sizeof(uint32_t) * indexing_group * num_meshlets * num_instances2 * 12);
	TS_LOGF(Message, "  Indexing: %s\n", String::fromBytes(indexing_buffer.getSize()).get());
	
	// create indirect buffer
	uint32_t num_indices = (uint32_t)mesh_meshlet_buffer.getSize() - num_meshlets * 16;
	Buffer index_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagIndex, sizeof(uint16_t) * (num_indices + num_meshlets * 4));
	Buffer indirect_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagIndirect, sizeof(Command::DrawElementsIndirect) * num_meshlets * num_instances2);
	{
		// create command list
		Compute compute = device.createCompute();
		
		// indirect parameters
		IndirectParameters indirect_parameters;
		indirect_parameters.num_instances = num_instances2;
		indirect_parameters.num_meshlets = num_meshlets;
		indirect_parameters.num_indices = num_indices;
		
		// dispatch indirect kernel
		compute.setKernel(indirect_kernel);
		compute.setUniform(0, indirect_parameters);
		compute.setStorageBuffer(0, mesh_meshlet_buffer);
		compute.setStorageBuffer(1, indirect_buffer);
		compute.setStorageBuffer(2, index_buffer);
		compute.dispatch(max(udiv(num_indices, 4u), num_meshlets * num_instances2));
		
		compute.barrier(indirect_buffer);
		compute.barrier(index_buffer);
	}
	TS_LOGF(Message, "     Index: %s\n", String::fromBytes(index_buffer.getSize()).get());
	TS_LOGF(Message, "  Indirect: %s\n", String::fromBytes(indirect_buffer.getSize()).get());
	
	device.flushBuffer(indirect_buffer);
	device.flushBuffer(index_buffer);
	
	// create command buffer
	#if _MACOS || _IOS
		
		device.finish();
		
		// create command buffer descriptor
		MTLIndirectCommandBufferDescriptor *command_descriptor = [MTLIndirectCommandBufferDescriptor new];
		command_descriptor.commandTypes = MTLIndirectCommandTypeDrawIndexed;
		command_descriptor.inheritBuffers = YES;
		command_descriptor.inheritPipelineState = YES;
		command_descriptor.maxVertexBufferBindCount = 0;
		command_descriptor.maxFragmentBufferBindCount = 0;
		
		// create command buffer
		uint32_t num_commands = num_meshlets * num_instances2;
		id<MTLDevice> mtl_device = (__bridge id<MTLDevice>)MTLDevice(device).getMTLDevice();
		id<MTLIndirectCommandBuffer> command_buffer = [mtl_device newIndirectCommandBufferWithDescriptor:command_descriptor maxCommandCount:num_commands options:MTLResourceStorageModePrivate];
		
		// create argument buffer
		id<MTLArgumentEncoder> argument_encoder = [(__bridge id<MTLFunction>)command_kernel.getComputeFunction() newArgumentEncoderWithBufferIndex:3];
		MTLBuffer argument_buffer = MTLBuffer(device.createBuffer(Buffer::FlagDynamic | Buffer::FlagStorage, argument_encoder.encodedLength));
		[argument_encoder setArgumentBuffer:(__bridge id<MTLBuffer>)argument_buffer.getMTLBuffer() offset:0];
		[argument_encoder setIndirectCommandBuffer:command_buffer atIndex:0];
		
	#endif
	
	// create queries
	Query draw_query;
	if(device.hasQuery(Query::TypeTime)) {
		draw_query = device.createQuery(Query::TypeTime);
		if(!draw_query) return 1;
	}
	
	// create target
	Target target = device.createTarget(window);
	target.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	target.setClearDepth(0.0f);
	
	// compute surfaces
	Texture depth_surface;
	Texture color_surface;
	
	// create canvas
	Canvas canvas;
	
	// create controls
	ControlRoot root(canvas, true);
	
	ControlPanel left_panel(&root, 1, 0.0f, 8.0f);
	left_panel.setAlign(Control::AlignLeftTop);
	left_panel.setPosition(8.0f, -8.0f);
	
	ControlText info_text(&left_panel);
	info_text.setAlign(Control::AlignLeft);
	
	ControlPanel right_panel(&root, 1, 0.0f, 8.0f);
	right_panel.setAlign(Control::AlignRightTop);
	right_panel.setPosition(-8.0f, -8.0f);
	
	ControlCombo mode_combo(&right_panel);
	String mode = String::format(" %ux%u", max_vertices, max_primitives);
	const uint32_t instanced_index = mode_combo.addItem("DrawInstanced");
	const uint32_t primitive_index = mode_combo.addItem(("DrawPrimitive" + mode).get());
	const uint32_t indexing_index = mode_combo.addItem(("DrawIndexing" + mode).get());
	const uint32_t indirect_index = mode_combo.addItem(("DrawIndirect" + mode).get());
	#if _MACOS || _IOS
		const uint32_t commands_index = mode_combo.addItem(("ExecuteCommands" + mode).get());
	#endif
	const uint32_t mesh_index = (mesh_pipeline) ? mode_combo.addItem(("DrawMesh" + mode).get()) : Maxu32;
	const uint32_t compute_shading_index = (compute_pipeline) ? mode_combo.addItem(("ComputeShading" + mode).get()) : Maxu32;
	const uint32_t compute_solid_index = (compute_pipeline) ? mode_combo.addItem(("ComputeSolid" + mode).get()) : Maxu32;
	if(mode_index < mode_combo.getNumItems()) mode_combo.setCurrentIndex(mode_index);
	else if(compute_shading_index != Maxu32) mode_combo.setCurrentIndex(compute_shading_index);
	else if(mesh_index != Maxu32) mode_combo.setCurrentIndex(mesh_index);
	else mode_combo.setCurrentIndex(indirect_index);
	
	ControlCheck animation_check(&right_panel, "Animation", true);
	animation_check.setAlign(Control::AlignLeft);
	
	float32_t animation_time = 0.0f;
	float32_t old_animation_time = 0.0f;
	
	// instance transforms
	Array<Matrix4x3f> transforms(num_instances2);
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		using Tellusim::sin;
		
		Window::update();
		
		if(!window.render()) return false;
		
		// draw mode
		uint32_t mode = mode_combo.getCurrentIndex();
		
		// window title
		if(fps > 0.0f || frame_counter == 0) {
			String triangles = String::fromNumber((uint64_t)(num_primitives * fps));
			String draw_time = String::fromTime(((bool)draw_query && draw_query.isAvailable()) ? draw_query.getTime() : 0);
			info_text.setText(String::format("FPS: %.1f\nTris: %s/S\nDraw: %s", fps, triangles.get(), draw_time.get()));
		}
		
		// update keyboard
		for(uint32_t i = 0; i < mode_combo.getNumItems(); i++) {
			if(window.getKeyboardKey('1' + i, true)) mode_combo.setCurrentIndex(i);
		}
		if(window.getKeyboardKey(' ', true)) animation_check.switchChecked();
		
		// update controls
		update_controls(window, root);
		canvas.create(device, target);
		
		// animation time
		if(animation_check.isChecked()) animation_time += time - old_animation_time;
		old_animation_time = time;
		
		// common parameters
		CommonParameters common_parameters;
		common_parameters.camera = Vector4f(4.0f + grid_size * 3.0f, 0.0f, 1.0f, 0.0f);
		common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, true);
		common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f(common_parameters.camera) + Vector3f(-16.0f, 0.0f, -4.0f), Vector3f::oneZ);
		if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
		
		// transform parameters
		transforms.clear();
		for(int32_t y = -grid_size; y <= grid_size; y++) {
			for(int32_t x = -grid_size; x <= grid_size; x++) {
				Matrix4x3f translate = Matrix4x3f::translate(x * 3.2f, y * 3.2f, 0.0f);
				Matrix4x3f rotate = Matrix4x3f::rotateZ(animation_time * 32.0f + y * 2715.53f) * Matrix4x3f::rotateX(animation_time * 16.0f + x * 9774.37f);
				Matrix4x3f scale = Matrix4x3f::scale(sin(animation_time + (x ^ y) * 13.73f) * 0.2f + 0.8f);
				transforms.append(translate * rotate * scale);
			}
		}
		
		// indexing mode
		if(mode == indexing_index && !window.getKeyboardKey('u')) {
			
			// create command list
			Compute compute = device.createCompute();
			
			// indexing parameters
			IndexingParameters indexing_parameters;
			indexing_parameters.num_meshlets = num_meshlets;
			
			// dispatch indexing kernel
			compute.setKernel(indexing_kernel);
			compute.setUniform(0, num_meshlets);
			compute.setStorageBuffer(0, mesh_meshlet_buffer);
			compute.setStorageBuffer(1, indexing_buffer);
			uint32_t max_groups = device.getFeatures().maxGroupCountX;
			for(uint32_t i = 0; i < num_instances2 * num_meshlets; i += max_groups) {
				uint32_t size = min(num_instances2 * num_meshlets - i, max_groups);
				indexing_parameters.base_group = i;
				compute.setUniform(0, indexing_parameters);
				compute.dispatch(indexing_group * size);
			}
			
			compute.barrier(indexing_buffer);
			
			device.flushBuffer(indexing_buffer);
		}
		
		// create command buffer
		#if _MACOS || _IOS
			
			else if(mode == commands_index && !window.getKeyboardKey('u')) {
				
				// create command list
				Compute compute = device.createCompute();
				
				// indirect parameters
				IndirectParameters indirect_parameters;
				indirect_parameters.num_instances = num_instances2;
				indirect_parameters.num_meshlets = num_meshlets;
				indirect_parameters.num_indices = num_indices;
				
				// dispatch command kernel
				compute.setKernel(command_kernel);
				compute.setUniform(0, indirect_parameters);
				compute.setStorageBuffer(0, mesh_meshlet_buffer);
				compute.setStorageBuffer(1, index_buffer);
				compute.setStorageBuffer(2, argument_buffer);
				id<MTLComputeCommandEncoder> encoder = (__bridge id<MTLComputeCommandEncoder>)MTLCompute(compute).getEncoder();
				[encoder useResource:(__bridge id<MTLBuffer>)MTLBuffer(index_buffer).getMTLBuffer() usage:MTLResourceUsageRead];
				[encoder useResource:command_buffer usage:MTLResourceUsageWrite];
				compute.dispatch(num_meshlets * num_instances2);
			}
			
		#endif
		
		// compute rasterization
		else if(mode == compute_shading_index || mode == compute_solid_index) {
			
			// create surfaces
			if(!depth_surface || depth_surface.getWidth() != window.getWidth() || depth_surface.getHeight() != window.getHeight()) {
				window.finish();
				depth_surface = device.createTexture2D(FormatRu32, window.getWidth(), window.getHeight(), Texture::FlagSurface | Texture::FlagBuffer);
				color_surface = device.createTexture2D(FormatRu32, window.getWidth(), window.getHeight(), Texture::FlagSurface | Texture::FlagBuffer);
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
			compute.setUniform(0, target.getClearColor().getRGBAu8());
			compute.setSurfaceTexture(0, color_surface);
			compute.dispatch(color_surface);
			compute.barrier(color_surface);
			
			// compute parameters
			ComputeParameters compute_parameters;
			compute_parameters.num_meshlets = num_meshlets;
			compute_parameters.surface_size = Vector2f(Vector2u(window.getWidth(), window.getHeight()));
			compute_parameters.surface_stride = (float32_t)TS_ALIGN64(window.getWidth());
			
			// begin query
			if(draw_query) compute.beginQuery(draw_query);
			
			// dispatch compute kernel
			if(mode == compute_shading_index) compute.setKernel(draw_shading_kernel);
			else if(mode == compute_solid_index) compute.setKernel(draw_solid_kernel);
			compute.setUniform(0, common_parameters);
			compute.setSurfaceTextures(0, { depth_surface, color_surface });
			compute.setStorageData(0, transforms.get(), transforms.bytes());
			compute.setStorageBuffers(1, { mesh_vertex_buffer, mesh_meshlet_buffer });
			uint32_t max_groups = device.getFeatures().maxGroupCountX;
			for(uint32_t i = 0; i < num_meshlets * num_instances2; i += max_groups) {
				uint32_t size = min(num_meshlets * num_instances2 - i, max_groups);
				compute_parameters.group_offset = i;
				compute.setUniform(1, compute_parameters);
				compute.dispatch(npot(max_primitives) * size);
			}
			
			// end query
			if(draw_query) compute.endQuery(draw_query);
			
			// flush surface
			device.flushTextures({ depth_surface, color_surface });
		}
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// begin query
			if(draw_query && mode != compute_shading_index && mode != compute_solid_index) command.beginQuery(draw_query);
			
			// draw instanced
			if(mode == instanced_index) {
				command.setPipeline(vertex_pipeline);
				command.setUniform(0, common_parameters);
				command.setUniformData(1, transforms.get(), transforms.bytes());
				vertex_model.setBuffers(command);
				vertex_model.drawInstanced(command, 0, num_instances2);
			}
			// draw arrays
			else if(mode == primitive_index) {
				command.setPipeline(primitive_pipeline);
				command.setUniform(0, common_parameters);
				command.setUniform(1, num_meshlets);
				command.setStorageData(0, transforms.get(), transforms.bytes());
				command.setStorageBuffer(1, mesh_vertex_buffer);
				command.setStorageBuffer(2, mesh_meshlet_buffer);
				command.drawArrays(max_primitives * num_meshlets * num_instances2 * 3);
			}
			// draw elements
			else if(mode == indexing_index) {
				command.setPipeline(indexing_pipeline);
				command.setUniform(0, common_parameters);
				command.setUniform(1, num_meshlets);
				command.setStorageData(0, transforms.get(), transforms.bytes());
				command.setStorageBuffer(1, mesh_vertex_buffer);
				command.setStorageBuffer(2, mesh_meshlet_buffer);
				command.setIndexBuffer(FormatRu32, indexing_buffer);
				command.drawElements(indexing_group * num_meshlets * num_instances2 * 12);
			}
			// draw elements indirect
			else if(mode == indirect_index) {
				command.setPipeline(indirect_pipeline);
				command.setUniform(0, common_parameters);
				command.setUniformData(1, transforms.get(), transforms.bytes());
				command.setVertexBuffer(0, mesh_vertex_buffer);
				command.setVertexBuffer(1, instance_buffer);
				command.setIndexBuffer(FormatRu16, index_buffer);
				command.setIndirectBuffer(indirect_buffer);
				command.drawElementsIndirect(num_meshlets * num_instances2);
			}
			// execute commands
			#if _MACOS || _IOS
				else if(mode == commands_index) {
					command.setPipeline(indirect_pipeline);
					command.setUniform(0, common_parameters);
					command.setUniformData(1, transforms.get(), transforms.bytes());
					command.setVertexBuffer(0, mesh_vertex_buffer);
					command.setVertexBuffer(1, instance_buffer);
					id<MTLRenderCommandEncoder> encoder = (__bridge id<MTLRenderCommandEncoder>)MTLCommand(command).getEncoder();
					[encoder useResource:(__bridge id<MTLBuffer>)MTLBuffer(index_buffer).getMTLBuffer() usage:MTLResourceUsageRead stages:MTLRenderStageVertex];
					[encoder executeCommandsInBuffer:command_buffer withRange:NSMakeRange(0, num_meshlets * num_instances2)];
				}
			#endif
			// mesh shader
			else if(mode == mesh_index) {
				command.setPipeline(mesh_pipeline);
				command.setUniform(0, common_parameters);
				command.setStorageData(0, transforms.get(), transforms.bytes());
				command.setStorageBuffers(1, { mesh_vertex_buffer, mesh_meshlet_buffer });
				uint32_t max_meshlets = device.getFeatures().maxTaskMeshes;
				for(uint32_t i = 0; i < num_meshlets; i += max_meshlets) {
					uint32_t size = min(num_meshlets - i, max_meshlets);
					command.setUniform(1, Vector2u(size, i));
					if(window.getKeyboardKey('i')) {
						command.setIndirect(Command::DrawMeshIndirect { num_instances2, 1, 1 });
						command.drawMeshIndirect(1);
					} else {
						command.drawMesh(num_instances2);
					}
				}
			}
			// compute shader
			else if(mode == compute_shading_index || mode == compute_solid_index) {
				command.setPipeline(compute_pipeline);
				command.setTexture(0, color_surface);
				command.drawArrays(3);
			}
			
			// end query
			if(draw_query && mode != compute_shading_index && mode != compute_solid_index) command.endQuery(draw_query);
			
			// draw canvas
			canvas.draw(command, target);
		}
		target.end();
		
		if(!window.present()) return false;
		
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	return 0;
}

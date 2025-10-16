// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#if _MACOS || _IOS || _TVOS
	#include <Metal/Metal.h>
#endif

#include <common/common.h>
#include <common/sample_controls.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimPipeline.h>
#include <platform/TellusimCommand.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::Indirect", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// number of objects
	constexpr int32_t size = 512;
	
	// structures
	struct CommonParameters {
		Matrix4x4f projection;
		Matrix4x4f modelview;
		Vector4f camera;
	};
	
	// create device
	Device device(window);
	if(!device) return 1;
	
	// create pipeline
	Pipeline pipeline = device.createPipeline();
	pipeline.setUniformMask(0, Shader::MaskVertex);
	pipeline.addAttribute(Pipeline::AttributePosition, FormatRGf32, 0, 0, sizeof(float32_t) * 2);
	pipeline.setMultisample(window.getMultisample());
	pipeline.setColorFormat(window.getColorFormat());
	pipeline.setDepthFormat(window.getDepthFormat());
	pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
	if(!pipeline.loadShaderGLSL(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1")) return 1;
	if(!pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
	#if _MACOS || _IOS || _TVOS
		MTLPipeline(pipeline).setIndirect(true);
	#endif
	if(!pipeline.create()) return 1;
	
	// create mesh pipeline
	Pipeline mesh_pipeline;
	if(device.hasShader(Shader::TypeTask)) {
		mesh_pipeline = device.createPipeline();
		mesh_pipeline.setUniformMasks(0, 2, Shader::MaskTask | Shader::MaskMesh);
		mesh_pipeline.setStorageMasks(0, 3, Shader::MaskTask | Shader::MaskMesh);
		mesh_pipeline.setColorFormat(window.getColorFormat());
		mesh_pipeline.setDepthFormat(window.getDepthFormat());
		mesh_pipeline.setDepthFunc(Pipeline::DepthFuncLessEqual);
		if(!mesh_pipeline.loadShaderGLSL(Shader::TypeTask, "main.shader", "TASK_SHADER=1")) return 1;
		if(!mesh_pipeline.loadShaderGLSL(Shader::TypeMesh, "main.shader", "MESH_SHADER=1")) return 1;
		if(!mesh_pipeline.loadShaderGLSL(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1")) return 1;
		if(!mesh_pipeline.create()) return 1;
	}
	
	// create draw buffers
	float32_t grid_size = 5.0f;
	float32_t quad_size = 2.0f;
	Array<Vector2f> vertices;
	Array<uint32_t> indices;
	Array<uint32_t> counts;
	Array<Command::DrawElementsIndirect> indirects;
	for(int32_t i = 0; i <= size; i++) {
		for(int32_t y = -i; y <= i; y++) {
			float32_t position_y = y * grid_size;
			for(int32_t x = -i; x <= i; x += (y != -i && y != i) ? i * 2 : 1) {
				if(y != -i && y != i && x != -i && x != i) continue;
				float32_t position_x = x * grid_size;
				
				uint32_t base_vertex = vertices.size();
				uint32_t base_index = indices.size();
				
				vertices.append(Vector2f(position_x - quad_size, position_y - quad_size));
				vertices.append(Vector2f(position_x + quad_size, position_y - quad_size));
				vertices.append(Vector2f(position_x - quad_size, position_y + quad_size));
				vertices.append(Vector2f(position_x + quad_size, position_y + quad_size));
				
				indices.append(base_vertex + 0);
				indices.append(base_vertex + 1);
				indices.append(base_vertex + 2);
				indices.append(base_vertex + 3);
				indices.append(base_vertex + 2);
				indices.append(base_vertex + 1);
				
				Command::DrawElementsIndirect &indirect = indirects.append();
				indirect.num_indices = 6;
				indirect.num_instances = 1;
				indirect.base_index = base_index;
				indirect.base_vertex = 0;
				indirect.base_instance = 0;
			}
		}
		counts.append(indirects.size());
	}
	
	// create buffers
	Buffer::Flags buffer_flags = (mesh_pipeline) ? Buffer::FlagStorage : Buffer::FlagNone;
	Buffer vertex_buffer = device.createBuffer(Buffer::FlagVertex | buffer_flags, vertices.get(), vertices.bytes());
	Buffer index_buffer = device.createBuffer(Buffer::FlagIndex | buffer_flags, indices.get(), indices.bytes());
	Buffer indirect_buffer = device.createBuffer(Buffer::FlagIndirect | buffer_flags, indirects.get(), indirects.bytes());
	Buffer count_buffer = device.createBuffer(Buffer::FlagIndirect, counts.get(), counts.bytes());
	if(!vertex_buffer || !index_buffer || !indirect_buffer || !count_buffer) return 1;
	
	#if _MACOS || _IOS || _TVOS
		
		// create indirect command buffer descriptor
		MTLIndirectCommandBufferDescriptor *indirect_descriptor = [MTLIndirectCommandBufferDescriptor new];
		indirect_descriptor.commandTypes = MTLIndirectCommandTypeDrawIndexed;
		indirect_descriptor.inheritBuffers = YES;
		indirect_descriptor.inheritPipelineState = YES;
		indirect_descriptor.maxVertexBufferBindCount = 0;
		indirect_descriptor.maxFragmentBufferBindCount = 0;
		
		// create indirect command buffer
		id<MTLDevice> mtl_device = (__bridge id<MTLDevice>)MTLDevice(device).getMTLDevice();
		id<MTLBuffer> mtl_index_buffer = (__bridge id<MTLBuffer>)MTLBuffer(index_buffer).getMTLBuffer();
		id<MTLIndirectCommandBuffer> command_buffer = [mtl_device newIndirectCommandBufferWithDescriptor:indirect_descriptor maxCommandCount:indirects.size() options:0];
		for(uint32_t i = 0; i < indirects.size(); i++) {
			const Command::DrawElementsIndirect &indirect = indirects[i];
			id<MTLIndirectRenderCommand> command = [command_buffer indirectRenderCommandAtIndex:i];
			[command drawIndexedPrimitives:MTLPrimitiveTypeTriangle indexCount:indirect.num_indices
				indexType:MTLIndexTypeUInt32 indexBuffer:mtl_index_buffer
				indexBufferOffset:indirect.base_index * 4 instanceCount:indirect.num_instances baseVertex:indirect.base_vertex baseInstance:indirect.base_instance];
		}
		
		// copy indirect command buffer
		id<MTLIndirectCommandBuffer> indirect_command_buffer = [mtl_device newIndirectCommandBufferWithDescriptor:indirect_descriptor maxCommandCount:indirects.size() options:MTLResourceStorageModePrivate];
		{
			id<MTLBlitCommandEncoder> blit_encoder = (__bridge id<MTLBlitCommandEncoder>)MTLDevice(device).getBlitEncoder();
			[blit_encoder copyIndirectCommandBuffer:command_buffer sourceRange:NSMakeRange(0, indirects.size()) destination:indirect_command_buffer destinationIndex:0];
			MTLDevice(device).endEncoder();
		}
		
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
	uint32_t single_elements_index = mode_combo.addItem("Single DrawElements");
	uint32_t multiple_elements_index = mode_combo.addItem("Multiple DrawElements");
	uint32_t multiple_indirect_index = mode_combo.addItem("Multiple DrawIndirect");
	#if _MACOS || _IOS || _TVOS
		uint32_t single_commands_index = mode_combo.addItem("Single ExecuteCommands");
	#else
		uint32_t multi_indirect_index = mode_combo.addItem("Single MultiIndirect");
		uint32_t multi_indirect_count_index = (device.getFeatures().drawIndirectCount) ? mode_combo.addItem("Single MultiIndirectCount") : Maxu32;
	#endif
	uint32_t single_mesh_index = (mesh_pipeline) ? mode_combo.addItem("Single DrawMesh") : Maxu32;
	
	ControlCombo count_combo(&right_panel);
	count_combo.setAlign(Control::AlignExpandX);
	for(uint32_t i = 8; i < counts.size(); i <<= 1) {
		uint32_t index = count_combo.addItem(String::format("Count %u", counts[i]));
		counts[index] = i;
	}
	count_combo.setCurrentIndex(3);
	
	ControlCheck animation_check(&right_panel, "Animation");
	animation_check.setAlign(Control::AlignLeft);
	
	float32_t animation_time = 0.0f;
	float32_t old_animation_time = 0.0f;
	
	uint32_t old_count = Maxu32;
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		using Tellusim::sin;
		using Tellusim::cos;
		
		Window::update();
		
		if(!window.render()) return false;
		
		// draw mode
		uint32_t mode = mode_combo.getCurrentIndex();
		uint32_t count = counts[counts[count_combo.getCurrentIndex()]];
		
		// FPS counter
		if(fps > 0.0f || old_count != count) {
			String dips = String::fromNumber((uint32_t)(count * fps));
			String triangles = String::fromNumber((uint32_t)(count * 2 * fps));
			String draw_time = String::fromTime(((bool)draw_query && draw_query.isAvailable()) ? draw_query.getTime() : 0);
			info_text.setText(String::format("FPS: %.1f\nTris: %s/S\nDips: %s/S\nDraw: %s", fps, triangles.get(), dips.get(), draw_time.get()));
			old_count = count;
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
		
		// window target
		target.begin();
		{
			// create command list
			Command command = device.createCommand(target);
			
			// set pipeline
			command.setPipeline(pipeline);
			
			// set buffers
			command.setVertexBuffer(0, vertex_buffer);
			command.setIndexBuffer(FormatRu32, index_buffer);
			
			// common parameters
			CommonParameters common_parameters;
			common_parameters.camera = Vector4f(-sin(animation_time * 0.1f) * 100.0f, -cos(animation_time * 0.1f) * 100.0f, 40.0f, 0.0f);
			common_parameters.projection = Matrix4x4f::perspective(60.0f, (float32_t)window.getWidth() / window.getHeight(), 0.1f, 10000.0f);
			common_parameters.modelview = Matrix4x4f::lookAt(Vector3f(common_parameters.camera), Vector3f(0.0f, 0.0f, -20.0f), Vector3f::oneZ);
			if(target.isFlipped()) common_parameters.projection = Matrix4x4f::scale(1.0f, -1.0f, 1.0f) * common_parameters.projection;
			command.setUniform(0, common_parameters);
			
			// begin query
			if(draw_query) command.beginQuery(draw_query);
			
			// single draw elements
			if(mode == single_elements_index) {
				command.drawElements(count * 6);
			}
			// multiple draw elements
			else if(mode == multiple_elements_index) {
				for(uint32_t i = 0; i < count; i++) {
					command.drawElements(6, i * 6);
				}
			}
			// multiple draw indirect
			else if(mode == multiple_indirect_index) {
				command.setIndirectBuffer(indirect_buffer);
				for(uint32_t i = 0; i < count; i++) {
					command.setIndirectOffset(sizeof(Command::DrawElementsIndirect) * i);
					command.drawElementsIndirect(1);
				}
			}
			#if _MACOS || _IOS || _TVOS
				// single commands
				else if(mode == single_commands_index) {
					id<MTLRenderCommandEncoder> encoder = (__bridge id<MTLRenderCommandEncoder>)MTLCommand(command).getEncoder();
					[encoder useResource:mtl_index_buffer usage:MTLResourceUsageRead stages:MTLRenderStageVertex];
					[encoder executeCommandsInBuffer:indirect_command_buffer withRange:NSMakeRange(0, count)];
				}
			#else
				// single multi indirect
				else if(mode == multi_indirect_index) {
					command.setIndirectBuffer(indirect_buffer);
					command.drawElementsIndirect(count);
				}
				// single multi indirect count
				else if(mode == multi_indirect_count_index) {
					command.setIndirectBuffer(indirect_buffer);
					command.drawElementsIndirect(count_buffer, sizeof(uint32_t) * counts[count_combo.getCurrentIndex()], indirects.size());
				}
			#endif
			// single mesh shader
			else if(mode == single_mesh_index) {
				command.setPipeline(mesh_pipeline);
				command.setUniform(0, common_parameters);
				command.setStorageBuffers(0, { indirect_buffer, vertex_buffer, index_buffer });
				uint32_t max_tasks = device.getFeatures().maxTaskCount;
				for(uint32_t i = 0; i < count; i += max_tasks) {
					command.setUniform(1, i);
					command.drawMesh(min(count - i, max_tasks));
				}
			}
			
			// end query
			if(draw_query) command.endQuery(draw_query);
			
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

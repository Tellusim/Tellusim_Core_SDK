// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <vulkan/vulkan.h>

#include <common/common.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimSurface.h>
#include <platform/TellusimContext.h>
#include <platform/TellusimCommand.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	App::setPlatform(PlatformVK);
	
	DECLARE_WINDOW
	
	// create window
	String title = String::format("%s Tellusim::VKPipeline", window.getPlatformName());
	DECLARE_WINDOW_CREATE(title)
	
	// create device
	VKDevice device(window);
	if(!device) return 1;
	
	// load vertex shader
	VKShader vertex_shader = VKShader(device.loadShader(Shader::TypeVertex, "main.shader", "VERTEX_SHADER=1"));
	if(!vertex_shader) return 1;
	
	// load fragment shader
	VKShader fragment_shader = VKShader(device.loadShader(Shader::TypeFragment, "main.shader", "FRAGMENT_SHADER=1"));
	if(!fragment_shader) return 1;
	
	// create pipeline layout
	VkPipelineLayout pipeline_layout = VK_NULL_HANDLE;
	{
		VkPushConstantRange constant_range = {};
		constant_range.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		constant_range.offset = 0;
		constant_range.size = sizeof(float32_t) * 2;
		
		VkPipelineLayoutCreateInfo pipeline_layout_info = {};
		pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipeline_layout_info.pushConstantRangeCount = 1;
		pipeline_layout_info.pPushConstantRanges = &constant_range;
		
		VkDevice vk_device = device.getVKDevice();
		PFN_vkCreatePipelineLayout vkCreatePipelineLayout = (PFN_vkCreatePipelineLayout)VKContext::getProcAddress("vkCreatePipelineLayout");
		if(VKContext::error(vkCreatePipelineLayout(vk_device, &pipeline_layout_info, nullptr, &pipeline_layout))) return 1;
	}
	
	// create pipeline cache
	VkPipelineCache pipeline_cache = VK_NULL_HANDLE;
	{
		VkPipelineCacheCreateInfo pipeline_cache_info = {};
		pipeline_cache_info.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
		
		VkDevice vk_device = device.getVKDevice();
		PFN_vkCreatePipelineCache vkCreatePipelineCache = (PFN_vkCreatePipelineCache)VKContext::getProcAddress("vkCreatePipelineCache");
		if(VKContext::error(vkCreatePipelineCache(vk_device, &pipeline_cache_info, nullptr, &pipeline_cache))) return 1;
	}
	
	// create pipeline
	VkPipeline pipeline = VK_NULL_HANDLE;
	{
		// shader stages
		VkPipelineShaderStageCreateInfo stages_info[2] = {};
		
		stages_info[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		stages_info[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
		stages_info[0].module = vertex_shader.getModule();
		stages_info[0].pName = "main";
		
		stages_info[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		stages_info[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		stages_info[1].module = fragment_shader.getModule();
		stages_info[1].pName = "main";
		
		// vertex input state
		VkPipelineVertexInputStateCreateInfo vertex_input_info = {};
		vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		
		// input assembly state
		VkPipelineInputAssemblyStateCreateInfo input_assembly_info = {};
		input_assembly_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		input_assembly_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		input_assembly_info.primitiveRestartEnable = VK_FALSE;
		
		// viewport state
		VkPipelineViewportStateCreateInfo viewport_state_info = {};
		viewport_state_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewport_state_info.viewportCount = 1;
		viewport_state_info.scissorCount = 1;
		
		// rasterization state
		VkPipelineRasterizationStateCreateInfo rasterization_state_info = {};
		rasterization_state_info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterization_state_info.depthClampEnable = VK_FALSE;
		rasterization_state_info.rasterizerDiscardEnable = VK_FALSE;
		rasterization_state_info.polygonMode = VK_POLYGON_MODE_FILL;
		rasterization_state_info.cullMode = VK_CULL_MODE_BACK_BIT;
		rasterization_state_info.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		rasterization_state_info.depthBiasEnable = VK_FALSE;
		rasterization_state_info.depthBiasConstantFactor = 0.0f;
		rasterization_state_info.depthBiasClamp = 0.0f;
		rasterization_state_info.depthBiasSlopeFactor = 0.0f;
		rasterization_state_info.lineWidth = 1.0f;
		
		// multisample state
		VkPipelineMultisampleStateCreateInfo multisample_state_info = {};
		multisample_state_info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisample_state_info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		multisample_state_info.sampleShadingEnable = VK_FALSE;
		multisample_state_info.minSampleShading = 1.0f;
		multisample_state_info.pSampleMask = nullptr;
		multisample_state_info.alphaToCoverageEnable = VK_FALSE;
		multisample_state_info.alphaToOneEnable = VK_FALSE;
		
		// depth stencil state
		VkPipelineDepthStencilStateCreateInfo depth_stencil_state_info = {};
		depth_stencil_state_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		depth_stencil_state_info.depthTestEnable = VK_FALSE;
		depth_stencil_state_info.depthWriteEnable = VK_FALSE;
		depth_stencil_state_info.depthCompareOp = VK_COMPARE_OP_ALWAYS;
		depth_stencil_state_info.depthBoundsTestEnable = VK_FALSE;
		depth_stencil_state_info.stencilTestEnable = VK_FALSE;
		depth_stencil_state_info.front.failOp = VK_STENCIL_OP_KEEP;
		depth_stencil_state_info.front.passOp = VK_STENCIL_OP_KEEP;
		depth_stencil_state_info.front.depthFailOp = VK_STENCIL_OP_KEEP;
		depth_stencil_state_info.front.compareOp = VK_COMPARE_OP_NEVER;
		depth_stencil_state_info.front.compareMask = 0;
		depth_stencil_state_info.front.writeMask = 0;
		depth_stencil_state_info.front.reference = 0;
		depth_stencil_state_info.back = depth_stencil_state_info.front;
		depth_stencil_state_info.minDepthBounds = 0.0f;
		depth_stencil_state_info.maxDepthBounds = 1.0f;
		
		// color blend state
		VkPipelineColorBlendAttachmentState color_blend_attachment = {};
		color_blend_attachment.blendEnable = VK_FALSE;
		color_blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_ZERO;
		color_blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
		color_blend_attachment.colorBlendOp = VK_BLEND_OP_ADD;
		color_blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		color_blend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		color_blend_attachment.alphaBlendOp = VK_BLEND_OP_ADD;
		color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		
		VkPipelineColorBlendStateCreateInfo color_blend_state_info = {};
		color_blend_state_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		color_blend_state_info.logicOpEnable = VK_FALSE;
		color_blend_state_info.logicOp = VK_LOGIC_OP_CLEAR;
		color_blend_state_info.attachmentCount = 1;
		color_blend_state_info.pAttachments = &color_blend_attachment;
		
		// dynamic states
		static const VkDynamicState dynamic_states[] = {
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_SCISSOR,
		};
		VkPipelineDynamicStateCreateInfo dynamic_state_info = {};
		dynamic_state_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamic_state_info.dynamicStateCount = TS_COUNTOF(dynamic_states);
		dynamic_state_info.pDynamicStates = dynamic_states;
		
		// create pipeline
		VkGraphicsPipelineCreateInfo pipeline_info = {};
		pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipeline_info.stageCount = TS_COUNTOF(stages_info);
		pipeline_info.pStages = stages_info;
		pipeline_info.pVertexInputState = &vertex_input_info;
		pipeline_info.pInputAssemblyState = &input_assembly_info;
		pipeline_info.pTessellationState = nullptr;
		pipeline_info.pViewportState = &viewport_state_info;
		pipeline_info.pRasterizationState = &rasterization_state_info;
		pipeline_info.pMultisampleState = &multisample_state_info;
		pipeline_info.pDepthStencilState = &depth_stencil_state_info;
		pipeline_info.pColorBlendState = &color_blend_state_info;
		pipeline_info.pDynamicState = &dynamic_state_info;
		pipeline_info.layout = pipeline_layout;
		pipeline_info.renderPass = VKSurface(window.getSurface()).getRenderPass();
		
		VkDevice vk_device = device.getVKDevice();
		PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines)VKContext::getProcAddress("vkCreateGraphicsPipelines");
		if(VKContext::error(vkCreateGraphicsPipelines(vk_device, pipeline_cache, 1, &pipeline_info, nullptr, &pipeline))) return 1;
	}
	
	// create target
	Target target = device.createTarget(window);
	target.setClearColor(Color("#ac162c"));
	
	// get functions
	PFN_vkCmdBindPipeline vkCmdBindPipeline = (PFN_vkCmdBindPipeline)VKContext::getProcAddress("vkCmdBindPipeline");
	PFN_vkCmdSetViewport vkCmdSetViewport = (PFN_vkCmdSetViewport)VKContext::getProcAddress("vkCmdSetViewport");
	PFN_vkCmdSetScissor vkCmdSetScissor = (PFN_vkCmdSetScissor)VKContext::getProcAddress("vkCmdSetScissor");
	PFN_vkCmdPushConstants vkCmdPushConstants = (PFN_vkCmdPushConstants)VKContext::getProcAddress("vkCmdPushConstants");
	PFN_vkCmdDraw vkCmdDraw = (PFN_vkCmdDraw)VKContext::getProcAddress("vkCmdDraw");
	
	// main loop
	DECLARE_GLOBAL
	window.run([&]() {
		DECLARE_COMMON
		
		Window::update();
		
		if(!window.render()) return false;
		
		// window title
		if(fps > 0.0f) window.setTitle(String::format("%s %.1f FPS", title.get(), fps));
		
		// window target
		target.begin();
		{
			// create command list
			VKCommand command = VKCommand(device.createCommand(target));
			
			// get command buffer
			VkCommandBuffer command_buffer = command.getVKCommand();
			
			// bind pipeline
			vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
			
			// set viewport
			VkViewport viewport = {};
			viewport.width = (float32_t)target.getWidth();
			viewport.height = (float32_t)target.getHeight();
			viewport.minDepth = 0.0f;
			viewport.maxDepth = 1.0f;
			vkCmdSetViewport(command_buffer, 0, 1, &viewport);
			
			// set scissor
			VkRect2D scissor = {};
			scissor.extent.width = target.getWidth();
			scissor.extent.height = target.getHeight();
			vkCmdSetScissor(command_buffer, 0, 1, &scissor);
			
			// create parameters
			float32_t parameters[2];
			parameters[0] = (float32_t)target.getWidth() / target.getHeight();
			parameters[1] = time;
			
			// set parameters
			vkCmdPushConstants(command_buffer, pipeline_layout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(parameters), parameters);
			
			// draw triangle
			vkCmdDraw(command_buffer, 3, 1, 0, 0);
		}
		target.end();
		
		if(!window.present()) return false;
		
		if(!device.check()) return false;
		
		return true;
	});
	
	// finish context
	window.finish();
	
	// destroy pipeline
	VkDevice vk_device = device.getVKDevice();
	PFN_vkDestroyPipeline vkDestroyPipeline = (PFN_vkDestroyPipeline)VKContext::getProcAddress("vkDestroyPipeline");
	PFN_vkDestroyPipelineCache vkDestroyPipelineCache = (PFN_vkDestroyPipelineCache)VKContext::getProcAddress("vkDestroyPipelineCache");
	PFN_vkDestroyPipelineLayout vkDestroyPipelineLayout = (PFN_vkDestroyPipelineLayout)VKContext::getProcAddress("vkDestroyPipelineLayout");
	vkDestroyPipeline(vk_device, pipeline, nullptr);
	vkDestroyPipelineCache(vk_device, pipeline_cache, nullptr);
	vkDestroyPipelineLayout(vk_device, pipeline_layout, nullptr);
	
	return 0;
}

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <platform/TellusimContext.h>

#include "../include/TellusimVK.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	namespace VK {
		
		/*
		 */
		bool init() {
			
			// function address
			#define GET_ADDRESS(TYPE, NAME) { \
				NAME = (TYPE)VKContext::getProcAddress(#NAME); \
				if(NAME == nullptr && is_core) { \
					TS_LOGF(Error, "VK::init(): can't get %s function\n", #NAME); \
					return false; \
				} \
			}
			
			// core functions
			bool is_core = true;
			
			// Vulkan 10 functions
			GET_ADDRESS(PFN_vkCreateInstance, vkCreateInstance)
			GET_ADDRESS(PFN_vkDestroyInstance, vkDestroyInstance)
			GET_ADDRESS(PFN_vkEnumeratePhysicalDevices, vkEnumeratePhysicalDevices)
			GET_ADDRESS(PFN_vkGetPhysicalDeviceFeatures, vkGetPhysicalDeviceFeatures)
			GET_ADDRESS(PFN_vkGetPhysicalDeviceFormatProperties, vkGetPhysicalDeviceFormatProperties)
			GET_ADDRESS(PFN_vkGetPhysicalDeviceImageFormatProperties, vkGetPhysicalDeviceImageFormatProperties)
			GET_ADDRESS(PFN_vkGetPhysicalDeviceProperties, vkGetPhysicalDeviceProperties)
			GET_ADDRESS(PFN_vkGetPhysicalDeviceQueueFamilyProperties, vkGetPhysicalDeviceQueueFamilyProperties)
			GET_ADDRESS(PFN_vkGetPhysicalDeviceMemoryProperties, vkGetPhysicalDeviceMemoryProperties)
			GET_ADDRESS(PFN_vkGetInstanceProcAddr, vkGetInstanceProcAddr)
			GET_ADDRESS(PFN_vkGetDeviceProcAddr, vkGetDeviceProcAddr)
			GET_ADDRESS(PFN_vkCreateDevice, vkCreateDevice)
			GET_ADDRESS(PFN_vkDestroyDevice, vkDestroyDevice)
			GET_ADDRESS(PFN_vkEnumerateInstanceExtensionProperties, vkEnumerateInstanceExtensionProperties)
			GET_ADDRESS(PFN_vkEnumerateDeviceExtensionProperties, vkEnumerateDeviceExtensionProperties)
			GET_ADDRESS(PFN_vkEnumerateInstanceLayerProperties, vkEnumerateInstanceLayerProperties)
			GET_ADDRESS(PFN_vkEnumerateDeviceLayerProperties, vkEnumerateDeviceLayerProperties)
			GET_ADDRESS(PFN_vkGetDeviceQueue, vkGetDeviceQueue)
			GET_ADDRESS(PFN_vkQueueSubmit, vkQueueSubmit)
			GET_ADDRESS(PFN_vkQueueWaitIdle, vkQueueWaitIdle)
			GET_ADDRESS(PFN_vkDeviceWaitIdle, vkDeviceWaitIdle)
			GET_ADDRESS(PFN_vkAllocateMemory, vkAllocateMemory)
			GET_ADDRESS(PFN_vkFreeMemory, vkFreeMemory)
			GET_ADDRESS(PFN_vkMapMemory, vkMapMemory)
			GET_ADDRESS(PFN_vkUnmapMemory, vkUnmapMemory)
			GET_ADDRESS(PFN_vkFlushMappedMemoryRanges, vkFlushMappedMemoryRanges)
			GET_ADDRESS(PFN_vkInvalidateMappedMemoryRanges, vkInvalidateMappedMemoryRanges)
			GET_ADDRESS(PFN_vkGetDeviceMemoryCommitment, vkGetDeviceMemoryCommitment)
			GET_ADDRESS(PFN_vkBindBufferMemory, vkBindBufferMemory)
			GET_ADDRESS(PFN_vkBindImageMemory, vkBindImageMemory)
			GET_ADDRESS(PFN_vkGetBufferMemoryRequirements, vkGetBufferMemoryRequirements)
			GET_ADDRESS(PFN_vkGetImageMemoryRequirements, vkGetImageMemoryRequirements)
			GET_ADDRESS(PFN_vkGetImageSparseMemoryRequirements, vkGetImageSparseMemoryRequirements)
			GET_ADDRESS(PFN_vkGetPhysicalDeviceSparseImageFormatProperties, vkGetPhysicalDeviceSparseImageFormatProperties)
			GET_ADDRESS(PFN_vkQueueBindSparse, vkQueueBindSparse)
			GET_ADDRESS(PFN_vkCreateFence, vkCreateFence)
			GET_ADDRESS(PFN_vkDestroyFence, vkDestroyFence)
			GET_ADDRESS(PFN_vkResetFences, vkResetFences)
			GET_ADDRESS(PFN_vkGetFenceStatus, vkGetFenceStatus)
			GET_ADDRESS(PFN_vkWaitForFences, vkWaitForFences)
			GET_ADDRESS(PFN_vkCreateSemaphore, vkCreateSemaphore)
			GET_ADDRESS(PFN_vkDestroySemaphore, vkDestroySemaphore)
			GET_ADDRESS(PFN_vkCreateEvent, vkCreateEvent)
			GET_ADDRESS(PFN_vkDestroyEvent, vkDestroyEvent)
			GET_ADDRESS(PFN_vkGetEventStatus, vkGetEventStatus)
			GET_ADDRESS(PFN_vkSetEvent, vkSetEvent)
			GET_ADDRESS(PFN_vkResetEvent, vkResetEvent)
			GET_ADDRESS(PFN_vkCreateQueryPool, vkCreateQueryPool)
			GET_ADDRESS(PFN_vkDestroyQueryPool, vkDestroyQueryPool)
			GET_ADDRESS(PFN_vkGetQueryPoolResults, vkGetQueryPoolResults)
			GET_ADDRESS(PFN_vkCreateBuffer, vkCreateBuffer)
			GET_ADDRESS(PFN_vkDestroyBuffer, vkDestroyBuffer)
			GET_ADDRESS(PFN_vkCreateBufferView, vkCreateBufferView)
			GET_ADDRESS(PFN_vkDestroyBufferView, vkDestroyBufferView)
			GET_ADDRESS(PFN_vkCreateImage, vkCreateImage)
			GET_ADDRESS(PFN_vkDestroyImage, vkDestroyImage)
			GET_ADDRESS(PFN_vkGetImageSubresourceLayout, vkGetImageSubresourceLayout)
			GET_ADDRESS(PFN_vkCreateImageView, vkCreateImageView)
			GET_ADDRESS(PFN_vkDestroyImageView, vkDestroyImageView)
			GET_ADDRESS(PFN_vkCreateShaderModule, vkCreateShaderModule)
			GET_ADDRESS(PFN_vkDestroyShaderModule, vkDestroyShaderModule)
			GET_ADDRESS(PFN_vkCreatePipelineCache, vkCreatePipelineCache)
			GET_ADDRESS(PFN_vkDestroyPipelineCache, vkDestroyPipelineCache)
			GET_ADDRESS(PFN_vkGetPipelineCacheData, vkGetPipelineCacheData)
			GET_ADDRESS(PFN_vkMergePipelineCaches, vkMergePipelineCaches)
			GET_ADDRESS(PFN_vkCreateGraphicsPipelines, vkCreateGraphicsPipelines)
			GET_ADDRESS(PFN_vkCreateComputePipelines, vkCreateComputePipelines)
			GET_ADDRESS(PFN_vkDestroyPipeline, vkDestroyPipeline)
			GET_ADDRESS(PFN_vkCreatePipelineLayout, vkCreatePipelineLayout)
			GET_ADDRESS(PFN_vkDestroyPipelineLayout, vkDestroyPipelineLayout)
			GET_ADDRESS(PFN_vkCreateSampler, vkCreateSampler)
			GET_ADDRESS(PFN_vkDestroySampler, vkDestroySampler)
			GET_ADDRESS(PFN_vkCreateDescriptorSetLayout, vkCreateDescriptorSetLayout)
			GET_ADDRESS(PFN_vkDestroyDescriptorSetLayout, vkDestroyDescriptorSetLayout)
			GET_ADDRESS(PFN_vkCreateDescriptorPool, vkCreateDescriptorPool)
			GET_ADDRESS(PFN_vkDestroyDescriptorPool, vkDestroyDescriptorPool)
			GET_ADDRESS(PFN_vkResetDescriptorPool, vkResetDescriptorPool)
			GET_ADDRESS(PFN_vkAllocateDescriptorSets, vkAllocateDescriptorSets)
			GET_ADDRESS(PFN_vkFreeDescriptorSets, vkFreeDescriptorSets)
			GET_ADDRESS(PFN_vkUpdateDescriptorSets, vkUpdateDescriptorSets)
			GET_ADDRESS(PFN_vkCreateFramebuffer, vkCreateFramebuffer)
			GET_ADDRESS(PFN_vkDestroyFramebuffer, vkDestroyFramebuffer)
			GET_ADDRESS(PFN_vkCreateRenderPass, vkCreateRenderPass)
			GET_ADDRESS(PFN_vkDestroyRenderPass, vkDestroyRenderPass)
			GET_ADDRESS(PFN_vkGetRenderAreaGranularity, vkGetRenderAreaGranularity)
			GET_ADDRESS(PFN_vkCreateCommandPool, vkCreateCommandPool)
			GET_ADDRESS(PFN_vkDestroyCommandPool, vkDestroyCommandPool)
			GET_ADDRESS(PFN_vkResetCommandPool, vkResetCommandPool)
			GET_ADDRESS(PFN_vkAllocateCommandBuffers, vkAllocateCommandBuffers)
			GET_ADDRESS(PFN_vkFreeCommandBuffers, vkFreeCommandBuffers)
			GET_ADDRESS(PFN_vkBeginCommandBuffer, vkBeginCommandBuffer)
			GET_ADDRESS(PFN_vkEndCommandBuffer, vkEndCommandBuffer)
			GET_ADDRESS(PFN_vkResetCommandBuffer, vkResetCommandBuffer)
			GET_ADDRESS(PFN_vkCmdBindPipeline, vkCmdBindPipeline)
			GET_ADDRESS(PFN_vkCmdSetViewport, vkCmdSetViewport)
			GET_ADDRESS(PFN_vkCmdSetScissor, vkCmdSetScissor)
			GET_ADDRESS(PFN_vkCmdSetLineWidth, vkCmdSetLineWidth)
			GET_ADDRESS(PFN_vkCmdSetDepthBias, vkCmdSetDepthBias)
			GET_ADDRESS(PFN_vkCmdSetBlendConstants, vkCmdSetBlendConstants)
			GET_ADDRESS(PFN_vkCmdSetDepthBounds, vkCmdSetDepthBounds)
			GET_ADDRESS(PFN_vkCmdSetStencilCompareMask, vkCmdSetStencilCompareMask)
			GET_ADDRESS(PFN_vkCmdSetStencilWriteMask, vkCmdSetStencilWriteMask)
			GET_ADDRESS(PFN_vkCmdSetStencilReference, vkCmdSetStencilReference)
			GET_ADDRESS(PFN_vkCmdBindDescriptorSets, vkCmdBindDescriptorSets)
			GET_ADDRESS(PFN_vkCmdBindIndexBuffer, vkCmdBindIndexBuffer)
			GET_ADDRESS(PFN_vkCmdBindVertexBuffers, vkCmdBindVertexBuffers)
			GET_ADDRESS(PFN_vkCmdDraw, vkCmdDraw)
			GET_ADDRESS(PFN_vkCmdDrawIndexed, vkCmdDrawIndexed)
			GET_ADDRESS(PFN_vkCmdDrawIndirect, vkCmdDrawIndirect)
			GET_ADDRESS(PFN_vkCmdDrawIndexedIndirect, vkCmdDrawIndexedIndirect)
			GET_ADDRESS(PFN_vkCmdDispatch, vkCmdDispatch)
			GET_ADDRESS(PFN_vkCmdDispatchIndirect, vkCmdDispatchIndirect)
			GET_ADDRESS(PFN_vkCmdCopyBuffer, vkCmdCopyBuffer)
			GET_ADDRESS(PFN_vkCmdCopyImage, vkCmdCopyImage)
			GET_ADDRESS(PFN_vkCmdBlitImage, vkCmdBlitImage)
			GET_ADDRESS(PFN_vkCmdCopyBufferToImage, vkCmdCopyBufferToImage)
			GET_ADDRESS(PFN_vkCmdCopyImageToBuffer, vkCmdCopyImageToBuffer)
			GET_ADDRESS(PFN_vkCmdUpdateBuffer, vkCmdUpdateBuffer)
			GET_ADDRESS(PFN_vkCmdFillBuffer, vkCmdFillBuffer)
			GET_ADDRESS(PFN_vkCmdClearColorImage, vkCmdClearColorImage)
			GET_ADDRESS(PFN_vkCmdClearDepthStencilImage, vkCmdClearDepthStencilImage)
			GET_ADDRESS(PFN_vkCmdClearAttachments, vkCmdClearAttachments)
			GET_ADDRESS(PFN_vkCmdResolveImage, vkCmdResolveImage)
			GET_ADDRESS(PFN_vkCmdSetEvent, vkCmdSetEvent)
			GET_ADDRESS(PFN_vkCmdResetEvent, vkCmdResetEvent)
			GET_ADDRESS(PFN_vkCmdWaitEvents, vkCmdWaitEvents)
			GET_ADDRESS(PFN_vkCmdPipelineBarrier, vkCmdPipelineBarrier)
			GET_ADDRESS(PFN_vkCmdBeginQuery, vkCmdBeginQuery)
			GET_ADDRESS(PFN_vkCmdEndQuery, vkCmdEndQuery)
			GET_ADDRESS(PFN_vkCmdResetQueryPool, vkCmdResetQueryPool)
			GET_ADDRESS(PFN_vkCmdWriteTimestamp, vkCmdWriteTimestamp)
			GET_ADDRESS(PFN_vkCmdCopyQueryPoolResults, vkCmdCopyQueryPoolResults)
			GET_ADDRESS(PFN_vkCmdPushConstants, vkCmdPushConstants)
			GET_ADDRESS(PFN_vkCmdBeginRenderPass, vkCmdBeginRenderPass)
			GET_ADDRESS(PFN_vkCmdNextSubpass, vkCmdNextSubpass)
			GET_ADDRESS(PFN_vkCmdEndRenderPass, vkCmdEndRenderPass)
			GET_ADDRESS(PFN_vkCmdExecuteCommands, vkCmdExecuteCommands)
			
			// Vulkan extensions
			is_core = false;
			
			// Vulkan 11 functions
			GET_ADDRESS(PFN_vkEnumerateInstanceVersion, vkEnumerateInstanceVersion)
			GET_ADDRESS(PFN_vkBindBufferMemory2, vkBindBufferMemory2)
			GET_ADDRESS(PFN_vkBindImageMemory2, vkBindImageMemory2)
			GET_ADDRESS(PFN_vkGetDeviceGroupPeerMemoryFeatures, vkGetDeviceGroupPeerMemoryFeatures)
			GET_ADDRESS(PFN_vkCmdSetDeviceMask, vkCmdSetDeviceMask)
			GET_ADDRESS(PFN_vkCmdDispatchBase, vkCmdDispatchBase)
			GET_ADDRESS(PFN_vkEnumeratePhysicalDeviceGroups, vkEnumeratePhysicalDeviceGroups)
			GET_ADDRESS(PFN_vkGetImageMemoryRequirements2, vkGetImageMemoryRequirements2)
			GET_ADDRESS(PFN_vkGetBufferMemoryRequirements2, vkGetBufferMemoryRequirements2)
			GET_ADDRESS(PFN_vkGetImageSparseMemoryRequirements2, vkGetImageSparseMemoryRequirements2)
			GET_ADDRESS(PFN_vkGetPhysicalDeviceFeatures2, vkGetPhysicalDeviceFeatures2)
			GET_ADDRESS(PFN_vkGetPhysicalDeviceProperties2, vkGetPhysicalDeviceProperties2)
			GET_ADDRESS(PFN_vkGetPhysicalDeviceFormatProperties2, vkGetPhysicalDeviceFormatProperties2)
			GET_ADDRESS(PFN_vkGetPhysicalDeviceImageFormatProperties2, vkGetPhysicalDeviceImageFormatProperties2)
			GET_ADDRESS(PFN_vkGetPhysicalDeviceQueueFamilyProperties2, vkGetPhysicalDeviceQueueFamilyProperties2)
			GET_ADDRESS(PFN_vkGetPhysicalDeviceMemoryProperties2, vkGetPhysicalDeviceMemoryProperties2)
			GET_ADDRESS(PFN_vkGetPhysicalDeviceSparseImageFormatProperties2, vkGetPhysicalDeviceSparseImageFormatProperties2)
			GET_ADDRESS(PFN_vkTrimCommandPool, vkTrimCommandPool)
			GET_ADDRESS(PFN_vkGetDeviceQueue2, vkGetDeviceQueue2)
			GET_ADDRESS(PFN_vkCreateSamplerYcbcrConversion, vkCreateSamplerYcbcrConversion)
			GET_ADDRESS(PFN_vkDestroySamplerYcbcrConversion, vkDestroySamplerYcbcrConversion)
			GET_ADDRESS(PFN_vkCreateDescriptorUpdateTemplate, vkCreateDescriptorUpdateTemplate)
			GET_ADDRESS(PFN_vkDestroyDescriptorUpdateTemplate, vkDestroyDescriptorUpdateTemplate)
			GET_ADDRESS(PFN_vkUpdateDescriptorSetWithTemplate, vkUpdateDescriptorSetWithTemplate)
			GET_ADDRESS(PFN_vkGetPhysicalDeviceExternalBufferProperties, vkGetPhysicalDeviceExternalBufferProperties)
			GET_ADDRESS(PFN_vkGetPhysicalDeviceExternalFenceProperties, vkGetPhysicalDeviceExternalFenceProperties)
			GET_ADDRESS(PFN_vkGetPhysicalDeviceExternalSemaphoreProperties, vkGetPhysicalDeviceExternalSemaphoreProperties)
			GET_ADDRESS(PFN_vkGetDescriptorSetLayoutSupport, vkGetDescriptorSetLayoutSupport)
			
			// Vulkan 12 functions
			GET_ADDRESS(PFN_vkCmdDrawIndirectCount, vkCmdDrawIndirectCount)
			GET_ADDRESS(PFN_vkCmdDrawIndexedIndirectCount, vkCmdDrawIndexedIndirectCount)
			GET_ADDRESS(PFN_vkCreateRenderPass2, vkCreateRenderPass2)
			GET_ADDRESS(PFN_vkCmdBeginRenderPass2, vkCmdBeginRenderPass2)
			GET_ADDRESS(PFN_vkCmdNextSubpass2, vkCmdNextSubpass2)
			GET_ADDRESS(PFN_vkCmdEndRenderPass2, vkCmdEndRenderPass2)
			GET_ADDRESS(PFN_vkResetQueryPool, vkResetQueryPool)
			GET_ADDRESS(PFN_vkGetSemaphoreCounterValue, vkGetSemaphoreCounterValue)
			GET_ADDRESS(PFN_vkWaitSemaphores, vkWaitSemaphores)
			GET_ADDRESS(PFN_vkSignalSemaphore, vkSignalSemaphore)
			GET_ADDRESS(PFN_vkGetBufferDeviceAddress, vkGetBufferDeviceAddress)
			GET_ADDRESS(PFN_vkGetBufferOpaqueCaptureAddress, vkGetBufferOpaqueCaptureAddress)
			GET_ADDRESS(PFN_vkGetDeviceMemoryOpaqueCaptureAddress, vkGetDeviceMemoryOpaqueCaptureAddress)
			
			// Vulkan 13 functions
			GET_ADDRESS(PFN_vkGetPhysicalDeviceToolProperties, vkGetPhysicalDeviceToolProperties)
			GET_ADDRESS(PFN_vkCreatePrivateDataSlot, vkCreatePrivateDataSlot)
			GET_ADDRESS(PFN_vkDestroyPrivateDataSlot, vkDestroyPrivateDataSlot)
			GET_ADDRESS(PFN_vkSetPrivateData, vkSetPrivateData)
			GET_ADDRESS(PFN_vkGetPrivateData, vkGetPrivateData)
			GET_ADDRESS(PFN_vkCmdSetEvent2, vkCmdSetEvent2)
			GET_ADDRESS(PFN_vkCmdResetEvent2, vkCmdResetEvent2)
			GET_ADDRESS(PFN_vkCmdWaitEvents2, vkCmdWaitEvents2)
			GET_ADDRESS(PFN_vkCmdPipelineBarrier2, vkCmdPipelineBarrier2)
			GET_ADDRESS(PFN_vkCmdWriteTimestamp2, vkCmdWriteTimestamp2)
			GET_ADDRESS(PFN_vkQueueSubmit2, vkQueueSubmit2)
			GET_ADDRESS(PFN_vkCmdCopyBuffer2, vkCmdCopyBuffer2)
			GET_ADDRESS(PFN_vkCmdCopyImage2, vkCmdCopyImage2)
			GET_ADDRESS(PFN_vkCmdCopyBufferToImage2, vkCmdCopyBufferToImage2)
			GET_ADDRESS(PFN_vkCmdCopyImageToBuffer2, vkCmdCopyImageToBuffer2)
			GET_ADDRESS(PFN_vkCmdBlitImage2, vkCmdBlitImage2)
			GET_ADDRESS(PFN_vkCmdResolveImage2, vkCmdResolveImage2)
			GET_ADDRESS(PFN_vkCmdBeginRendering, vkCmdBeginRendering)
			GET_ADDRESS(PFN_vkCmdEndRendering, vkCmdEndRendering)
			GET_ADDRESS(PFN_vkCmdSetCullMode, vkCmdSetCullMode)
			GET_ADDRESS(PFN_vkCmdSetFrontFace, vkCmdSetFrontFace)
			GET_ADDRESS(PFN_vkCmdSetPrimitiveTopology, vkCmdSetPrimitiveTopology)
			GET_ADDRESS(PFN_vkCmdSetViewportWithCount, vkCmdSetViewportWithCount)
			GET_ADDRESS(PFN_vkCmdSetScissorWithCount, vkCmdSetScissorWithCount)
			GET_ADDRESS(PFN_vkCmdBindVertexBuffers2, vkCmdBindVertexBuffers2)
			GET_ADDRESS(PFN_vkCmdSetDepthTestEnable, vkCmdSetDepthTestEnable)
			GET_ADDRESS(PFN_vkCmdSetDepthWriteEnable, vkCmdSetDepthWriteEnable)
			GET_ADDRESS(PFN_vkCmdSetDepthCompareOp, vkCmdSetDepthCompareOp)
			GET_ADDRESS(PFN_vkCmdSetDepthBoundsTestEnable, vkCmdSetDepthBoundsTestEnable)
			GET_ADDRESS(PFN_vkCmdSetStencilTestEnable, vkCmdSetStencilTestEnable)
			GET_ADDRESS(PFN_vkCmdSetStencilOp, vkCmdSetStencilOp)
			GET_ADDRESS(PFN_vkCmdSetRasterizerDiscardEnable, vkCmdSetRasterizerDiscardEnable)
			GET_ADDRESS(PFN_vkCmdSetDepthBiasEnable, vkCmdSetDepthBiasEnable)
			GET_ADDRESS(PFN_vkCmdSetPrimitiveRestartEnable, vkCmdSetPrimitiveRestartEnable)
			GET_ADDRESS(PFN_vkGetDeviceBufferMemoryRequirements, vkGetDeviceBufferMemoryRequirements)
			GET_ADDRESS(PFN_vkGetDeviceImageMemoryRequirements, vkGetDeviceImageMemoryRequirements)
			GET_ADDRESS(PFN_vkGetDeviceImageSparseMemoryRequirements, vkGetDeviceImageSparseMemoryRequirements)
			
			// Vulkan 14 functions
			GET_ADDRESS(PFN_vkCmdSetLineStipple, vkCmdSetLineStipple)
			GET_ADDRESS(PFN_vkMapMemory2, vkMapMemory2)
			GET_ADDRESS(PFN_vkUnmapMemory2, vkUnmapMemory2)
			GET_ADDRESS(PFN_vkCmdBindIndexBuffer2, vkCmdBindIndexBuffer2)
			GET_ADDRESS(PFN_vkGetRenderingAreaGranularity, vkGetRenderingAreaGranularity)
			GET_ADDRESS(PFN_vkGetDeviceImageSubresourceLayout, vkGetDeviceImageSubresourceLayout)
			GET_ADDRESS(PFN_vkGetImageSubresourceLayout2, vkGetImageSubresourceLayout2)
			GET_ADDRESS(PFN_vkCmdPushDescriptorSet, vkCmdPushDescriptorSet)
			GET_ADDRESS(PFN_vkCmdPushDescriptorSetWithTemplate, vkCmdPushDescriptorSetWithTemplate)
			GET_ADDRESS(PFN_vkCmdSetRenderingAttachmentLocations, vkCmdSetRenderingAttachmentLocations)
			GET_ADDRESS(PFN_vkCmdSetRenderingInputAttachmentIndices, vkCmdSetRenderingInputAttachmentIndices)
			GET_ADDRESS(PFN_vkCmdBindDescriptorSets2, vkCmdBindDescriptorSets2)
			GET_ADDRESS(PFN_vkCmdPushConstants2, vkCmdPushConstants2)
			GET_ADDRESS(PFN_vkCmdPushDescriptorSet2, vkCmdPushDescriptorSet2)
			GET_ADDRESS(PFN_vkCmdPushDescriptorSetWithTemplate2, vkCmdPushDescriptorSetWithTemplate2)
			GET_ADDRESS(PFN_vkCopyMemoryToImage, vkCopyMemoryToImage)
			GET_ADDRESS(PFN_vkCopyImageToMemory, vkCopyImageToMemory)
			GET_ADDRESS(PFN_vkCopyImageToImage, vkCopyImageToImage)
			GET_ADDRESS(PFN_vkTransitionImageLayout, vkTransitionImageLayout)
			
			// KHR draw indirect count
			GET_ADDRESS(PFN_vkCmdDrawIndirectCountKHR, vkCmdDrawIndirectCountKHR)
			GET_ADDRESS(PFN_vkCmdDrawIndexedIndirectCountKHR, vkCmdDrawIndexedIndirectCountKHR)
			
			// KHR buffer device address
			GET_ADDRESS(PFN_vkGetBufferDeviceAddressKHR, vkGetBufferDeviceAddressKHR)
			
			// KHR acceleration structure
			GET_ADDRESS(PFN_vkCreateAccelerationStructureKHR, vkCreateAccelerationStructureKHR)
			GET_ADDRESS(PFN_vkDestroyAccelerationStructureKHR, vkDestroyAccelerationStructureKHR)
			GET_ADDRESS(PFN_vkCmdBuildAccelerationStructuresKHR, vkCmdBuildAccelerationStructuresKHR)
			GET_ADDRESS(PFN_vkCmdBuildAccelerationStructuresIndirectKHR, vkCmdBuildAccelerationStructuresIndirectKHR)
			GET_ADDRESS(PFN_vkBuildAccelerationStructuresKHR, vkBuildAccelerationStructuresKHR)
			GET_ADDRESS(PFN_vkCopyAccelerationStructureKHR, vkCopyAccelerationStructureKHR)
			GET_ADDRESS(PFN_vkCopyAccelerationStructureToMemoryKHR, vkCopyAccelerationStructureToMemoryKHR)
			GET_ADDRESS(PFN_vkCopyMemoryToAccelerationStructureKHR, vkCopyMemoryToAccelerationStructureKHR)
			GET_ADDRESS(PFN_vkWriteAccelerationStructuresPropertiesKHR, vkWriteAccelerationStructuresPropertiesKHR)
			GET_ADDRESS(PFN_vkCmdCopyAccelerationStructureKHR, vkCmdCopyAccelerationStructureKHR)
			GET_ADDRESS(PFN_vkCmdCopyAccelerationStructureToMemoryKHR, vkCmdCopyAccelerationStructureToMemoryKHR)
			GET_ADDRESS(PFN_vkCmdCopyMemoryToAccelerationStructureKHR, vkCmdCopyMemoryToAccelerationStructureKHR)
			GET_ADDRESS(PFN_vkGetAccelerationStructureDeviceAddressKHR, vkGetAccelerationStructureDeviceAddressKHR)
			GET_ADDRESS(PFN_vkCmdWriteAccelerationStructuresPropertiesKHR, vkCmdWriteAccelerationStructuresPropertiesKHR)
			GET_ADDRESS(PFN_vkGetDeviceAccelerationStructureCompatibilityKHR, vkGetDeviceAccelerationStructureCompatibilityKHR)
			GET_ADDRESS(PFN_vkGetAccelerationStructureBuildSizesKHR, vkGetAccelerationStructureBuildSizesKHR)
			
			// KHR ray tracing pipeline
			GET_ADDRESS(PFN_vkCmdTraceRaysKHR, vkCmdTraceRaysKHR)
			GET_ADDRESS(PFN_vkCreateRayTracingPipelinesKHR, vkCreateRayTracingPipelinesKHR)
			GET_ADDRESS(PFN_vkGetRayTracingShaderGroupHandlesKHR, vkGetRayTracingShaderGroupHandlesKHR)
			GET_ADDRESS(PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR, vkGetRayTracingCaptureReplayShaderGroupHandlesKHR)
			GET_ADDRESS(PFN_vkCmdTraceRaysIndirectKHR, vkCmdTraceRaysIndirectKHR)
			GET_ADDRESS(PFN_vkGetRayTracingShaderGroupStackSizeKHR, vkGetRayTracingShaderGroupStackSizeKHR)
			GET_ADDRESS(PFN_vkCmdSetRayTracingPipelineStackSizeKHR, vkCmdSetRayTracingPipelineStackSizeKHR)
			
			// EXT external memory host
			GET_ADDRESS(PFN_vkGetMemoryHostPointerPropertiesEXT, vkGetMemoryHostPointerPropertiesEXT)
			
			// EXT conditional rendering
			GET_ADDRESS(PFN_vkCmdBeginConditionalRenderingEXT, vkCmdBeginConditionalRenderingEXT)
			GET_ADDRESS(PFN_vkCmdEndConditionalRenderingEXT, vkCmdEndConditionalRenderingEXT)
			
			// EXT mesh shader
			GET_ADDRESS(PFN_vkCmdDrawMeshTasksEXT, vkCmdDrawMeshTasksEXT)
			GET_ADDRESS(PFN_vkCmdDrawMeshTasksIndirectEXT, vkCmdDrawMeshTasksIndirectEXT)
			GET_ADDRESS(PFN_vkCmdDrawMeshTasksIndirectCountEXT, vkCmdDrawMeshTasksIndirectCountEXT)
			
			#undef GET_ADDRESS
			
			return true;
		}
	}
	
	/*****************************************************************************\
	 *
	 * Vulkan functions
	 *
	\*****************************************************************************/
	
	// Vulkan 10 functions
	PFN_vkCreateInstance vkCreateInstance = nullptr;
	PFN_vkDestroyInstance vkDestroyInstance = nullptr;
	PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices = nullptr;
	PFN_vkGetPhysicalDeviceFeatures vkGetPhysicalDeviceFeatures = nullptr;
	PFN_vkGetPhysicalDeviceFormatProperties vkGetPhysicalDeviceFormatProperties = nullptr;
	PFN_vkGetPhysicalDeviceImageFormatProperties vkGetPhysicalDeviceImageFormatProperties = nullptr;
	PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties = nullptr;
	PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties = nullptr;
	PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties = nullptr;
	PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = nullptr;
	PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr = nullptr;
	PFN_vkCreateDevice vkCreateDevice = nullptr;
	PFN_vkDestroyDevice vkDestroyDevice = nullptr;
	PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties = nullptr;
	PFN_vkEnumerateDeviceExtensionProperties vkEnumerateDeviceExtensionProperties = nullptr;
	PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties = nullptr;
	PFN_vkEnumerateDeviceLayerProperties vkEnumerateDeviceLayerProperties = nullptr;
	PFN_vkGetDeviceQueue vkGetDeviceQueue = nullptr;
	PFN_vkQueueSubmit vkQueueSubmit = nullptr;
	PFN_vkQueueWaitIdle vkQueueWaitIdle = nullptr;
	PFN_vkDeviceWaitIdle vkDeviceWaitIdle = nullptr;
	PFN_vkAllocateMemory vkAllocateMemory = nullptr;
	PFN_vkFreeMemory vkFreeMemory = nullptr;
	PFN_vkMapMemory vkMapMemory = nullptr;
	PFN_vkUnmapMemory vkUnmapMemory = nullptr;
	PFN_vkFlushMappedMemoryRanges vkFlushMappedMemoryRanges = nullptr;
	PFN_vkInvalidateMappedMemoryRanges vkInvalidateMappedMemoryRanges = nullptr;
	PFN_vkGetDeviceMemoryCommitment vkGetDeviceMemoryCommitment = nullptr;
	PFN_vkBindBufferMemory vkBindBufferMemory = nullptr;
	PFN_vkBindImageMemory vkBindImageMemory = nullptr;
	PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements = nullptr;
	PFN_vkGetImageMemoryRequirements vkGetImageMemoryRequirements = nullptr;
	PFN_vkGetImageSparseMemoryRequirements vkGetImageSparseMemoryRequirements = nullptr;
	PFN_vkGetPhysicalDeviceSparseImageFormatProperties vkGetPhysicalDeviceSparseImageFormatProperties = nullptr;
	PFN_vkQueueBindSparse vkQueueBindSparse = nullptr;
	PFN_vkCreateFence vkCreateFence = nullptr;
	PFN_vkDestroyFence vkDestroyFence = nullptr;
	PFN_vkResetFences vkResetFences = nullptr;
	PFN_vkGetFenceStatus vkGetFenceStatus = nullptr;
	PFN_vkWaitForFences vkWaitForFences = nullptr;
	PFN_vkCreateSemaphore vkCreateSemaphore = nullptr;
	PFN_vkDestroySemaphore vkDestroySemaphore = nullptr;
	PFN_vkCreateEvent vkCreateEvent = nullptr;
	PFN_vkDestroyEvent vkDestroyEvent = nullptr;
	PFN_vkGetEventStatus vkGetEventStatus = nullptr;
	PFN_vkSetEvent vkSetEvent = nullptr;
	PFN_vkResetEvent vkResetEvent = nullptr;
	PFN_vkCreateQueryPool vkCreateQueryPool = nullptr;
	PFN_vkDestroyQueryPool vkDestroyQueryPool = nullptr;
	PFN_vkGetQueryPoolResults vkGetQueryPoolResults = nullptr;
	PFN_vkCreateBuffer vkCreateBuffer = nullptr;
	PFN_vkDestroyBuffer vkDestroyBuffer = nullptr;
	PFN_vkCreateBufferView vkCreateBufferView = nullptr;
	PFN_vkDestroyBufferView vkDestroyBufferView = nullptr;
	PFN_vkCreateImage vkCreateImage = nullptr;
	PFN_vkDestroyImage vkDestroyImage = nullptr;
	PFN_vkGetImageSubresourceLayout vkGetImageSubresourceLayout = nullptr;
	PFN_vkCreateImageView vkCreateImageView = nullptr;
	PFN_vkDestroyImageView vkDestroyImageView = nullptr;
	PFN_vkCreateShaderModule vkCreateShaderModule = nullptr;
	PFN_vkDestroyShaderModule vkDestroyShaderModule = nullptr;
	PFN_vkCreatePipelineCache vkCreatePipelineCache = nullptr;
	PFN_vkDestroyPipelineCache vkDestroyPipelineCache = nullptr;
	PFN_vkGetPipelineCacheData vkGetPipelineCacheData = nullptr;
	PFN_vkMergePipelineCaches vkMergePipelineCaches = nullptr;
	PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines = nullptr;
	PFN_vkCreateComputePipelines vkCreateComputePipelines = nullptr;
	PFN_vkDestroyPipeline vkDestroyPipeline = nullptr;
	PFN_vkCreatePipelineLayout vkCreatePipelineLayout = nullptr;
	PFN_vkDestroyPipelineLayout vkDestroyPipelineLayout = nullptr;
	PFN_vkCreateSampler vkCreateSampler = nullptr;
	PFN_vkDestroySampler vkDestroySampler = nullptr;
	PFN_vkCreateDescriptorSetLayout vkCreateDescriptorSetLayout = nullptr;
	PFN_vkDestroyDescriptorSetLayout vkDestroyDescriptorSetLayout = nullptr;
	PFN_vkCreateDescriptorPool vkCreateDescriptorPool = nullptr;
	PFN_vkDestroyDescriptorPool vkDestroyDescriptorPool = nullptr;
	PFN_vkResetDescriptorPool vkResetDescriptorPool = nullptr;
	PFN_vkAllocateDescriptorSets vkAllocateDescriptorSets = nullptr;
	PFN_vkFreeDescriptorSets vkFreeDescriptorSets = nullptr;
	PFN_vkUpdateDescriptorSets vkUpdateDescriptorSets = nullptr;
	PFN_vkCreateFramebuffer vkCreateFramebuffer = nullptr;
	PFN_vkDestroyFramebuffer vkDestroyFramebuffer = nullptr;
	PFN_vkCreateRenderPass vkCreateRenderPass = nullptr;
	PFN_vkDestroyRenderPass vkDestroyRenderPass = nullptr;
	PFN_vkGetRenderAreaGranularity vkGetRenderAreaGranularity = nullptr;
	PFN_vkCreateCommandPool vkCreateCommandPool = nullptr;
	PFN_vkDestroyCommandPool vkDestroyCommandPool = nullptr;
	PFN_vkResetCommandPool vkResetCommandPool = nullptr;
	PFN_vkAllocateCommandBuffers vkAllocateCommandBuffers = nullptr;
	PFN_vkFreeCommandBuffers vkFreeCommandBuffers = nullptr;
	PFN_vkBeginCommandBuffer vkBeginCommandBuffer = nullptr;
	PFN_vkEndCommandBuffer vkEndCommandBuffer = nullptr;
	PFN_vkResetCommandBuffer vkResetCommandBuffer = nullptr;
	PFN_vkCmdBindPipeline vkCmdBindPipeline = nullptr;
	PFN_vkCmdSetViewport vkCmdSetViewport = nullptr;
	PFN_vkCmdSetScissor vkCmdSetScissor = nullptr;
	PFN_vkCmdSetLineWidth vkCmdSetLineWidth = nullptr;
	PFN_vkCmdSetDepthBias vkCmdSetDepthBias = nullptr;
	PFN_vkCmdSetBlendConstants vkCmdSetBlendConstants = nullptr;
	PFN_vkCmdSetDepthBounds vkCmdSetDepthBounds = nullptr;
	PFN_vkCmdSetStencilCompareMask vkCmdSetStencilCompareMask = nullptr;
	PFN_vkCmdSetStencilWriteMask vkCmdSetStencilWriteMask = nullptr;
	PFN_vkCmdSetStencilReference vkCmdSetStencilReference = nullptr;
	PFN_vkCmdBindDescriptorSets vkCmdBindDescriptorSets = nullptr;
	PFN_vkCmdBindIndexBuffer vkCmdBindIndexBuffer = nullptr;
	PFN_vkCmdBindVertexBuffers vkCmdBindVertexBuffers = nullptr;
	PFN_vkCmdDraw vkCmdDraw = nullptr;
	PFN_vkCmdDrawIndexed vkCmdDrawIndexed = nullptr;
	PFN_vkCmdDrawIndirect vkCmdDrawIndirect = nullptr;
	PFN_vkCmdDrawIndexedIndirect vkCmdDrawIndexedIndirect = nullptr;
	PFN_vkCmdDispatch vkCmdDispatch = nullptr;
	PFN_vkCmdDispatchIndirect vkCmdDispatchIndirect = nullptr;
	PFN_vkCmdCopyBuffer vkCmdCopyBuffer = nullptr;
	PFN_vkCmdCopyImage vkCmdCopyImage = nullptr;
	PFN_vkCmdBlitImage vkCmdBlitImage = nullptr;
	PFN_vkCmdCopyBufferToImage vkCmdCopyBufferToImage = nullptr;
	PFN_vkCmdCopyImageToBuffer vkCmdCopyImageToBuffer = nullptr;
	PFN_vkCmdUpdateBuffer vkCmdUpdateBuffer = nullptr;
	PFN_vkCmdFillBuffer vkCmdFillBuffer = nullptr;
	PFN_vkCmdClearColorImage vkCmdClearColorImage = nullptr;
	PFN_vkCmdClearDepthStencilImage vkCmdClearDepthStencilImage = nullptr;
	PFN_vkCmdClearAttachments vkCmdClearAttachments = nullptr;
	PFN_vkCmdResolveImage vkCmdResolveImage = nullptr;
	PFN_vkCmdSetEvent vkCmdSetEvent = nullptr;
	PFN_vkCmdResetEvent vkCmdResetEvent = nullptr;
	PFN_vkCmdWaitEvents vkCmdWaitEvents = nullptr;
	PFN_vkCmdPipelineBarrier vkCmdPipelineBarrier = nullptr;
	PFN_vkCmdBeginQuery vkCmdBeginQuery = nullptr;
	PFN_vkCmdEndQuery vkCmdEndQuery = nullptr;
	PFN_vkCmdResetQueryPool vkCmdResetQueryPool = nullptr;
	PFN_vkCmdWriteTimestamp vkCmdWriteTimestamp = nullptr;
	PFN_vkCmdCopyQueryPoolResults vkCmdCopyQueryPoolResults = nullptr;
	PFN_vkCmdPushConstants vkCmdPushConstants = nullptr;
	PFN_vkCmdBeginRenderPass vkCmdBeginRenderPass = nullptr;
	PFN_vkCmdNextSubpass vkCmdNextSubpass = nullptr;
	PFN_vkCmdEndRenderPass vkCmdEndRenderPass = nullptr;
	PFN_vkCmdExecuteCommands vkCmdExecuteCommands = nullptr;
	
	// Vulkan 11 functions
	PFN_vkEnumerateInstanceVersion vkEnumerateInstanceVersion = nullptr;
	PFN_vkBindBufferMemory2 vkBindBufferMemory2 = nullptr;
	PFN_vkBindImageMemory2 vkBindImageMemory2 = nullptr;
	PFN_vkGetDeviceGroupPeerMemoryFeatures vkGetDeviceGroupPeerMemoryFeatures = nullptr;
	PFN_vkCmdSetDeviceMask vkCmdSetDeviceMask = nullptr;
	PFN_vkCmdDispatchBase vkCmdDispatchBase = nullptr;
	PFN_vkEnumeratePhysicalDeviceGroups vkEnumeratePhysicalDeviceGroups = nullptr;
	PFN_vkGetImageMemoryRequirements2 vkGetImageMemoryRequirements2 = nullptr;
	PFN_vkGetBufferMemoryRequirements2 vkGetBufferMemoryRequirements2 = nullptr;
	PFN_vkGetImageSparseMemoryRequirements2 vkGetImageSparseMemoryRequirements2 = nullptr;
	PFN_vkGetPhysicalDeviceFeatures2 vkGetPhysicalDeviceFeatures2 = nullptr;
	PFN_vkGetPhysicalDeviceProperties2 vkGetPhysicalDeviceProperties2 = nullptr;
	PFN_vkGetPhysicalDeviceFormatProperties2 vkGetPhysicalDeviceFormatProperties2 = nullptr;
	PFN_vkGetPhysicalDeviceImageFormatProperties2 vkGetPhysicalDeviceImageFormatProperties2 = nullptr;
	PFN_vkGetPhysicalDeviceQueueFamilyProperties2 vkGetPhysicalDeviceQueueFamilyProperties2 = nullptr;
	PFN_vkGetPhysicalDeviceMemoryProperties2 vkGetPhysicalDeviceMemoryProperties2 = nullptr;
	PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 vkGetPhysicalDeviceSparseImageFormatProperties2 = nullptr;
	PFN_vkTrimCommandPool vkTrimCommandPool = nullptr;
	PFN_vkGetDeviceQueue2 vkGetDeviceQueue2 = nullptr;
	PFN_vkCreateSamplerYcbcrConversion vkCreateSamplerYcbcrConversion = nullptr;
	PFN_vkDestroySamplerYcbcrConversion vkDestroySamplerYcbcrConversion = nullptr;
	PFN_vkCreateDescriptorUpdateTemplate vkCreateDescriptorUpdateTemplate = nullptr;
	PFN_vkDestroyDescriptorUpdateTemplate vkDestroyDescriptorUpdateTemplate = nullptr;
	PFN_vkUpdateDescriptorSetWithTemplate vkUpdateDescriptorSetWithTemplate = nullptr;
	PFN_vkGetPhysicalDeviceExternalBufferProperties vkGetPhysicalDeviceExternalBufferProperties = nullptr;
	PFN_vkGetPhysicalDeviceExternalFenceProperties vkGetPhysicalDeviceExternalFenceProperties = nullptr;
	PFN_vkGetPhysicalDeviceExternalSemaphoreProperties vkGetPhysicalDeviceExternalSemaphoreProperties = nullptr;
	PFN_vkGetDescriptorSetLayoutSupport vkGetDescriptorSetLayoutSupport = nullptr;
	
	// Vulkan 12 functions
	PFN_vkCmdDrawIndirectCount vkCmdDrawIndirectCount = nullptr;
	PFN_vkCmdDrawIndexedIndirectCount vkCmdDrawIndexedIndirectCount = nullptr;
	PFN_vkCreateRenderPass2 vkCreateRenderPass2 = nullptr;
	PFN_vkCmdBeginRenderPass2 vkCmdBeginRenderPass2 = nullptr;
	PFN_vkCmdNextSubpass2 vkCmdNextSubpass2 = nullptr;
	PFN_vkCmdEndRenderPass2 vkCmdEndRenderPass2 = nullptr;
	PFN_vkResetQueryPool vkResetQueryPool = nullptr;
	PFN_vkGetSemaphoreCounterValue vkGetSemaphoreCounterValue = nullptr;
	PFN_vkWaitSemaphores vkWaitSemaphores = nullptr;
	PFN_vkSignalSemaphore vkSignalSemaphore = nullptr;
	PFN_vkGetBufferDeviceAddress vkGetBufferDeviceAddress = nullptr;
	PFN_vkGetBufferOpaqueCaptureAddress vkGetBufferOpaqueCaptureAddress = nullptr;
	PFN_vkGetDeviceMemoryOpaqueCaptureAddress vkGetDeviceMemoryOpaqueCaptureAddress = nullptr;
	
	// Vulkan 13 functions
	PFN_vkGetPhysicalDeviceToolProperties vkGetPhysicalDeviceToolProperties = nullptr;
	PFN_vkCreatePrivateDataSlot vkCreatePrivateDataSlot = nullptr;
	PFN_vkDestroyPrivateDataSlot vkDestroyPrivateDataSlot = nullptr;
	PFN_vkSetPrivateData vkSetPrivateData = nullptr;
	PFN_vkGetPrivateData vkGetPrivateData = nullptr;
	PFN_vkCmdSetEvent2 vkCmdSetEvent2 = nullptr;
	PFN_vkCmdResetEvent2 vkCmdResetEvent2 = nullptr;
	PFN_vkCmdWaitEvents2 vkCmdWaitEvents2 = nullptr;
	PFN_vkCmdPipelineBarrier2 vkCmdPipelineBarrier2 = nullptr;
	PFN_vkCmdWriteTimestamp2 vkCmdWriteTimestamp2 = nullptr;
	PFN_vkQueueSubmit2 vkQueueSubmit2 = nullptr;
	PFN_vkCmdCopyBuffer2 vkCmdCopyBuffer2 = nullptr;
	PFN_vkCmdCopyImage2 vkCmdCopyImage2 = nullptr;
	PFN_vkCmdCopyBufferToImage2 vkCmdCopyBufferToImage2 = nullptr;
	PFN_vkCmdCopyImageToBuffer2 vkCmdCopyImageToBuffer2 = nullptr;
	PFN_vkCmdBlitImage2 vkCmdBlitImage2 = nullptr;
	PFN_vkCmdResolveImage2 vkCmdResolveImage2 = nullptr;
	PFN_vkCmdBeginRendering vkCmdBeginRendering = nullptr;
	PFN_vkCmdEndRendering vkCmdEndRendering = nullptr;
	PFN_vkCmdSetCullMode vkCmdSetCullMode = nullptr;
	PFN_vkCmdSetFrontFace vkCmdSetFrontFace = nullptr;
	PFN_vkCmdSetPrimitiveTopology vkCmdSetPrimitiveTopology = nullptr;
	PFN_vkCmdSetViewportWithCount vkCmdSetViewportWithCount = nullptr;
	PFN_vkCmdSetScissorWithCount vkCmdSetScissorWithCount = nullptr;
	PFN_vkCmdBindVertexBuffers2 vkCmdBindVertexBuffers2 = nullptr;
	PFN_vkCmdSetDepthTestEnable vkCmdSetDepthTestEnable = nullptr;
	PFN_vkCmdSetDepthWriteEnable vkCmdSetDepthWriteEnable = nullptr;
	PFN_vkCmdSetDepthCompareOp vkCmdSetDepthCompareOp = nullptr;
	PFN_vkCmdSetDepthBoundsTestEnable vkCmdSetDepthBoundsTestEnable = nullptr;
	PFN_vkCmdSetStencilTestEnable vkCmdSetStencilTestEnable = nullptr;
	PFN_vkCmdSetStencilOp vkCmdSetStencilOp = nullptr;
	PFN_vkCmdSetRasterizerDiscardEnable vkCmdSetRasterizerDiscardEnable = nullptr;
	PFN_vkCmdSetDepthBiasEnable vkCmdSetDepthBiasEnable = nullptr;
	PFN_vkCmdSetPrimitiveRestartEnable vkCmdSetPrimitiveRestartEnable = nullptr;
	PFN_vkGetDeviceBufferMemoryRequirements vkGetDeviceBufferMemoryRequirements = nullptr;
	PFN_vkGetDeviceImageMemoryRequirements vkGetDeviceImageMemoryRequirements = nullptr;
	PFN_vkGetDeviceImageSparseMemoryRequirements vkGetDeviceImageSparseMemoryRequirements = nullptr;
	
	// Vulkan 14 functions
	PFN_vkCmdSetLineStipple vkCmdSetLineStipple = nullptr;
	PFN_vkMapMemory2 vkMapMemory2 = nullptr;
	PFN_vkUnmapMemory2 vkUnmapMemory2 = nullptr;
	PFN_vkCmdBindIndexBuffer2 vkCmdBindIndexBuffer2 = nullptr;
	PFN_vkGetRenderingAreaGranularity vkGetRenderingAreaGranularity = nullptr;
	PFN_vkGetDeviceImageSubresourceLayout vkGetDeviceImageSubresourceLayout = nullptr;
	PFN_vkGetImageSubresourceLayout2 vkGetImageSubresourceLayout2 = nullptr;
	PFN_vkCmdPushDescriptorSet vkCmdPushDescriptorSet = nullptr;
	PFN_vkCmdPushDescriptorSetWithTemplate vkCmdPushDescriptorSetWithTemplate = nullptr;
	PFN_vkCmdSetRenderingAttachmentLocations vkCmdSetRenderingAttachmentLocations = nullptr;
	PFN_vkCmdSetRenderingInputAttachmentIndices vkCmdSetRenderingInputAttachmentIndices = nullptr;
	PFN_vkCmdBindDescriptorSets2 vkCmdBindDescriptorSets2 = nullptr;
	PFN_vkCmdPushConstants2 vkCmdPushConstants2 = nullptr;
	PFN_vkCmdPushDescriptorSet2 vkCmdPushDescriptorSet2 = nullptr;
	PFN_vkCmdPushDescriptorSetWithTemplate2 vkCmdPushDescriptorSetWithTemplate2 = nullptr;
	PFN_vkCopyMemoryToImage vkCopyMemoryToImage = nullptr;
	PFN_vkCopyImageToMemory vkCopyImageToMemory = nullptr;
	PFN_vkCopyImageToImage vkCopyImageToImage = nullptr;
	PFN_vkTransitionImageLayout vkTransitionImageLayout = nullptr;
	
	// KHR draw indirect count
	PFN_vkCmdDrawIndirectCountKHR vkCmdDrawIndirectCountKHR = nullptr;
	PFN_vkCmdDrawIndexedIndirectCountKHR vkCmdDrawIndexedIndirectCountKHR = nullptr;
	
	// KHR buffer device address
	PFN_vkGetBufferDeviceAddressKHR vkGetBufferDeviceAddressKHR = nullptr;
	
	// KHR acceleration structure
	PFN_vkCreateAccelerationStructureKHR vkCreateAccelerationStructureKHR = nullptr;
	PFN_vkDestroyAccelerationStructureKHR vkDestroyAccelerationStructureKHR = nullptr;
	PFN_vkCmdBuildAccelerationStructuresKHR vkCmdBuildAccelerationStructuresKHR = nullptr;
	PFN_vkCmdBuildAccelerationStructuresIndirectKHR vkCmdBuildAccelerationStructuresIndirectKHR = nullptr;
	PFN_vkBuildAccelerationStructuresKHR vkBuildAccelerationStructuresKHR = nullptr;
	PFN_vkCopyAccelerationStructureKHR vkCopyAccelerationStructureKHR = nullptr;
	PFN_vkCopyAccelerationStructureToMemoryKHR vkCopyAccelerationStructureToMemoryKHR = nullptr;
	PFN_vkCopyMemoryToAccelerationStructureKHR vkCopyMemoryToAccelerationStructureKHR = nullptr;
	PFN_vkWriteAccelerationStructuresPropertiesKHR vkWriteAccelerationStructuresPropertiesKHR = nullptr;
	PFN_vkCmdCopyAccelerationStructureKHR vkCmdCopyAccelerationStructureKHR = nullptr;
	PFN_vkCmdCopyAccelerationStructureToMemoryKHR vkCmdCopyAccelerationStructureToMemoryKHR = nullptr;
	PFN_vkCmdCopyMemoryToAccelerationStructureKHR vkCmdCopyMemoryToAccelerationStructureKHR = nullptr;
	PFN_vkGetAccelerationStructureDeviceAddressKHR vkGetAccelerationStructureDeviceAddressKHR = nullptr;
	PFN_vkCmdWriteAccelerationStructuresPropertiesKHR vkCmdWriteAccelerationStructuresPropertiesKHR = nullptr;
	PFN_vkGetDeviceAccelerationStructureCompatibilityKHR vkGetDeviceAccelerationStructureCompatibilityKHR = nullptr;
	PFN_vkGetAccelerationStructureBuildSizesKHR vkGetAccelerationStructureBuildSizesKHR = nullptr;
	
	// KHR ray tracing pipeline
	PFN_vkCmdTraceRaysKHR vkCmdTraceRaysKHR = nullptr;
	PFN_vkCreateRayTracingPipelinesKHR vkCreateRayTracingPipelinesKHR = nullptr;
	PFN_vkGetRayTracingShaderGroupHandlesKHR vkGetRayTracingShaderGroupHandlesKHR = nullptr;
	PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR vkGetRayTracingCaptureReplayShaderGroupHandlesKHR = nullptr;
	PFN_vkCmdTraceRaysIndirectKHR vkCmdTraceRaysIndirectKHR = nullptr;
	PFN_vkGetRayTracingShaderGroupStackSizeKHR vkGetRayTracingShaderGroupStackSizeKHR = nullptr;
	PFN_vkCmdSetRayTracingPipelineStackSizeKHR vkCmdSetRayTracingPipelineStackSizeKHR = nullptr;
	
	// EXT external memory host
	PFN_vkGetMemoryHostPointerPropertiesEXT vkGetMemoryHostPointerPropertiesEXT = nullptr;
	
	// EXT conditional rendering
	PFN_vkCmdBeginConditionalRenderingEXT vkCmdBeginConditionalRenderingEXT = nullptr;
	PFN_vkCmdEndConditionalRenderingEXT vkCmdEndConditionalRenderingEXT = nullptr;
	
	// EXT mesh shader
	PFN_vkCmdDrawMeshTasksEXT vkCmdDrawMeshTasksEXT = nullptr;
	PFN_vkCmdDrawMeshTasksIndirectEXT vkCmdDrawMeshTasksIndirectEXT = nullptr;
	PFN_vkCmdDrawMeshTasksIndirectCountEXT vkCmdDrawMeshTasksIndirectCountEXT = nullptr;
}

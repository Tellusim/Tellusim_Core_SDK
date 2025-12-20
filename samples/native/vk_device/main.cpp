// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <vulkan/vulkan.h>

#include <platform/TellusimContext.h>
#include <platform/TellusimDevice.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create context
	VKContext context;
	if(!context.create()) return 1;
	
	// create device
	VKDevice device(context);
	if(!device) return 1;
	
	// device name
	TS_LOGF(Message, "%s (%s)\n", device.getName().get(), device.getPlatformName());
	if(device.getVendor()) TS_LOGF(Message, "Vendor: %s\n", device.getVendor().get());
	if(device.getVersion()) TS_LOGF(Message, "Version: %s\n", device.getVersion().get());
	
	// device features
	#define FEATURE(NAME) if(features) Log::printf("  " #NAME ": %u\n", (uint32_t)features->NAME);
	#define FEATURE_X(NAME) if(features) Log::printf("  " #NAME ": 0x%x\n", (uint32_t)features->NAME);
	#define FEATURE_U(NAME) if(features) Log::printf("  " #NAME ": %u\n", (uint32_t)features->NAME);
	#define FEATURE_V(NAME) if(features) Log::printf("  " #NAME ": %u %u %u\n", (uint32_t)features->NAME[0], (uint32_t)features->NAME[1], (uint32_t)features->NAME[2]);
	#define FEATURE_S(NAME) if(features) Log::printf("  " #NAME ": %s\n", features->NAME);
	
	#define FEATURE2(PREFIX, NAME) if(features) Log::printf("  " #NAME ": %u\n", (uint32_t)features->PREFIX.NAME);
	#define FEATURE2_X(PREFIX, NAME) if(features) Log::printf("  " #NAME ": 0x%x\n", (uint32_t)features->PREFIX.NAME);
	#define FEATURE2_U(PREFIX, NAME) if(features) Log::printf("  " #NAME ": %u\n", (uint32_t)features->PREFIX.NAME);
	#define FEATURE2_V(PREFIX, NAME) if(features) Log::printf("  " #NAME ": %u %u %u\n", (uint32_t)features->PREFIX.NAME[0], (uint32_t)features->PREFIX.NAME[1], (uint32_t)features->PREFIX.NAME[2]);
	#define FEATURE2_S(PREFIX, NAME) if(features) Log::printf("  " #NAME ": %s\n", features->PREFIX.NAME);
	
	{
		auto *features = (const VkPhysicalDeviceFeatures2*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2);
		if(features) Log::printf("\nFeatures:\n");
		FEATURE2(features, robustBufferAccess)
		FEATURE2(features, fullDrawIndexUint32)
		FEATURE2(features, imageCubeArray)
		FEATURE2(features, independentBlend)
		FEATURE2(features, geometryShader)
		FEATURE2(features, tessellationShader)
		FEATURE2(features, sampleRateShading)
		FEATURE2(features, dualSrcBlend)
		FEATURE2(features, logicOp)
		FEATURE2(features, multiDrawIndirect)
		FEATURE2(features, drawIndirectFirstInstance)
		FEATURE2(features, depthClamp)
		FEATURE2(features, depthBiasClamp)
		FEATURE2(features, fillModeNonSolid)
		FEATURE2(features, depthBounds)
		FEATURE2(features, wideLines)
		FEATURE2(features, largePoints)
		FEATURE2(features, alphaToOne)
		FEATURE2(features, multiViewport)
		FEATURE2(features, samplerAnisotropy)
		FEATURE2(features, textureCompressionETC2)
		FEATURE2(features, textureCompressionASTC_LDR)
		FEATURE2(features, textureCompressionBC)
		FEATURE2(features, occlusionQueryPrecise)
		FEATURE2(features, pipelineStatisticsQuery)
		FEATURE2(features, vertexPipelineStoresAndAtomics)
		FEATURE2(features, fragmentStoresAndAtomics)
		FEATURE2(features, shaderTessellationAndGeometryPointSize)
		FEATURE2(features, shaderImageGatherExtended)
		FEATURE2(features, shaderStorageImageExtendedFormats)
		FEATURE2(features, shaderStorageImageMultisample)
		FEATURE2(features, shaderStorageImageReadWithoutFormat)
		FEATURE2(features, shaderStorageImageWriteWithoutFormat)
		FEATURE2(features, shaderUniformBufferArrayDynamicIndexing)
		FEATURE2(features, shaderSampledImageArrayDynamicIndexing)
		FEATURE2(features, shaderStorageBufferArrayDynamicIndexing)
		FEATURE2(features, shaderStorageImageArrayDynamicIndexing)
		FEATURE2(features, shaderClipDistance)
		FEATURE2(features, shaderCullDistance)
		FEATURE2(features, shaderFloat64)
		FEATURE2(features, shaderInt64)
		FEATURE2(features, shaderInt16)
		FEATURE2(features, shaderResourceResidency)
		FEATURE2(features, shaderResourceMinLod)
		FEATURE2(features, sparseBinding)
		FEATURE2(features, sparseResidencyBuffer)
		FEATURE2(features, sparseResidencyImage2D)
		FEATURE2(features, sparseResidencyImage3D)
		FEATURE2(features, sparseResidency2Samples)
		FEATURE2(features, sparseResidency4Samples)
		FEATURE2(features, sparseResidency8Samples)
		FEATURE2(features, sparseResidency16Samples)
		FEATURE2(features, sparseResidencyAliased)
		FEATURE2(features, variableMultisampleRate)
		FEATURE2(features, inheritedQueries)
	}
	{
		auto *features = (const VkPhysicalDeviceProperties2*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2);
		if(features) Log::printf("\nProperties:\n");
		FEATURE2_X(properties, apiVersion)
		FEATURE2_X(properties, driverVersion)
		FEATURE2_X(properties, vendorID)
		FEATURE2_X(properties, deviceID)
		FEATURE2_U(properties, deviceType)
		FEATURE2_S(properties, deviceName)
	}
	{
		auto *features = (const VkPhysicalDeviceProperties2*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2);
		if(features) Log::printf("\nLimits:\n");
		FEATURE2_U(properties.limits, maxImageDimension1D)
		FEATURE2_U(properties.limits, maxImageDimension2D)
		FEATURE2_U(properties.limits, maxImageDimension3D)
		FEATURE2_U(properties.limits, maxImageDimensionCube)
		FEATURE2_U(properties.limits, maxImageArrayLayers)
		FEATURE2_U(properties.limits, maxTexelBufferElements)
		FEATURE2_U(properties.limits, maxUniformBufferRange)
		FEATURE2_U(properties.limits, maxStorageBufferRange)
		FEATURE2_U(properties.limits, maxPushConstantsSize)
		FEATURE2_U(properties.limits, maxMemoryAllocationCount)
		FEATURE2_U(properties.limits, maxSamplerAllocationCount)
	}
	{
		auto *features = (const VkPhysicalDeviceProperties2*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2);
		if(features) Log::printf("\nSparseProperties:\n");
		FEATURE2_U(properties.sparseProperties, residencyStandard2DBlockShape)
		FEATURE2_U(properties.sparseProperties, residencyStandard2DMultisampleBlockShape)
		FEATURE2_U(properties.sparseProperties, residencyStandard3DBlockShape)
		FEATURE2_U(properties.sparseProperties, residencyAlignedMipSize)
		FEATURE2_U(properties.sparseProperties, residencyNonResidentStrict)
	}
	
	{
		auto *features = (const VkPhysicalDeviceSubgroupProperties*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_PROPERTIES);
		if(features) Log::printf("\nSubgroupProperties:\n");
		FEATURE_U(subgroupSize)
		FEATURE_U(supportedStages)
		FEATURE_U(supportedOperations)
		FEATURE_U(quadOperationsInAllStages)
	}
	
	{
		auto *features = (const VkPhysicalDevice16BitStorageFeaturesKHR*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_16BIT_STORAGE_FEATURES_KHR);
		if(features) Log::printf("\n16bitStorageFeatures:\n");
		FEATURE(storageBuffer16BitAccess)
		FEATURE(uniformAndStorageBuffer16BitAccess)
		FEATURE(storagePushConstant16)
		FEATURE(storageInputOutput16)
	}
	
	{
		auto *features = (const VkPhysicalDeviceShaderDrawParametersFeatures*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DRAW_PARAMETERS_FEATURES);
		if(features) Log::printf("\nShaderDrawParametersFeatures:\n");
		FEATURE(shaderDrawParameters)
	}
	
	{
		auto *features = (const VkPhysicalDeviceShaderAtomicInt64Features*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_INT64_FEATURES);
		if(features) Log::printf("\nShaderAtomicInt64Features:\n");
		FEATURE(shaderBufferInt64Atomics)
		FEATURE(shaderSharedInt64Atomics)
	}
	
	{
		auto *features = (const VkPhysicalDeviceFloat16Int8FeaturesKHR*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FLOAT16_INT8_FEATURES_KHR);
		if(features) Log::printf("\nShaderFloat16Int8Features:\n");
		FEATURE(shaderFloat16)
		FEATURE(shaderInt8)
	}
	
	{
		auto *features = (const VkPhysicalDeviceShaderIntegerDotProductFeaturesKHR*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_DOT_PRODUCT_FEATURES_KHR);
		if(features) Log::printf("\nShaderIntegerDotProductFeatures:\n");
		FEATURE(shaderIntegerDotProduct)
	}
	
	{
		auto *features = (const VkPhysicalDeviceShaderIntegerDotProductPropertiesKHR*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_DOT_PRODUCT_PROPERTIES_KHR);
		if(features) Log::printf("\nShaderIntegerDotProductProperties:\n");
		FEATURE_U(integerDotProduct8BitUnsignedAccelerated)
		FEATURE_U(integerDotProduct8BitSignedAccelerated)
		FEATURE_U(integerDotProduct8BitMixedSignednessAccelerated)
		FEATURE_U(integerDotProduct4x8BitPackedUnsignedAccelerated)
		FEATURE_U(integerDotProduct4x8BitPackedSignedAccelerated)
		FEATURE_U(integerDotProduct4x8BitPackedMixedSignednessAccelerated)
		FEATURE_U(integerDotProduct16BitUnsignedAccelerated)
		FEATURE_U(integerDotProduct16BitSignedAccelerated)
		FEATURE_U(integerDotProduct16BitMixedSignednessAccelerated)
		FEATURE_U(integerDotProduct32BitUnsignedAccelerated)
		FEATURE_U(integerDotProduct32BitSignedAccelerated)
		FEATURE_U(integerDotProduct32BitMixedSignednessAccelerated)
		FEATURE_U(integerDotProduct64BitUnsignedAccelerated)
		FEATURE_U(integerDotProduct64BitSignedAccelerated)
		FEATURE_U(integerDotProduct64BitMixedSignednessAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating8BitUnsignedAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating8BitSignedAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating8BitMixedSignednessAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating4x8BitPackedUnsignedAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating4x8BitPackedSignedAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating4x8BitPackedMixedSignednessAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating16BitUnsignedAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating16BitSignedAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating16BitMixedSignednessAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating32BitUnsignedAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating32BitSignedAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating32BitMixedSignednessAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating64BitUnsignedAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating64BitSignedAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating64BitMixedSignednessAccelerated)
	}
	
	{
		auto *features = (const VkPhysicalDeviceDescriptorIndexingFeatures*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES);
		if(features) Log::printf("\nDescriptorIndexingFeatures:\n");
		FEATURE(shaderInputAttachmentArrayDynamicIndexing)
		FEATURE(shaderUniformTexelBufferArrayDynamicIndexing)
		FEATURE(shaderStorageTexelBufferArrayDynamicIndexing)
		FEATURE(shaderUniformBufferArrayNonUniformIndexing)
		FEATURE(shaderSampledImageArrayNonUniformIndexing)
		FEATURE(shaderStorageBufferArrayNonUniformIndexing)
		FEATURE(shaderStorageImageArrayNonUniformIndexing)
		FEATURE(shaderInputAttachmentArrayNonUniformIndexing)
		FEATURE(shaderUniformTexelBufferArrayNonUniformIndexing)
		FEATURE(shaderStorageTexelBufferArrayNonUniformIndexing)
		FEATURE(descriptorBindingUniformBufferUpdateAfterBind)
		FEATURE(descriptorBindingSampledImageUpdateAfterBind)
		FEATURE(descriptorBindingStorageImageUpdateAfterBind)
		FEATURE(descriptorBindingStorageBufferUpdateAfterBind)
		FEATURE(descriptorBindingUniformTexelBufferUpdateAfterBind)
		FEATURE(descriptorBindingStorageTexelBufferUpdateAfterBind)
		FEATURE(descriptorBindingUpdateUnusedWhilePending)
		FEATURE(descriptorBindingPartiallyBound)
		FEATURE(descriptorBindingVariableDescriptorCount)
		FEATURE(runtimeDescriptorArray)
	}
	
	{
		auto *features = (const VkPhysicalDeviceTimelineSemaphoreFeatures*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES);
		if(features) Log::printf("\nTimelineSemephoreFeatures:\n");
		FEATURE(timelineSemaphore)
	}
	
	{
		auto *features = (const VkPhysicalDeviceBufferDeviceAddressFeatures*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_ADDRESS_FEATURES_EXT);
		if(features) Log::printf("\nBufferDeviceAddressFeatures:\n");
		FEATURE(bufferDeviceAddress)
		FEATURE(bufferDeviceAddressCaptureReplay)
		FEATURE(bufferDeviceAddressMultiDevice)
	}
	
	{
		auto *features = (const VkPhysicalDeviceFragmentShaderBarycentricFeaturesKHR*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_BARYCENTRIC_FEATURES_KHR);
		if(features) Log::printf("\nFragmentShaderBarycentricFeatures:\n");
		FEATURE(fragmentShaderBarycentric)
	}
	
	{
		auto *features = (const VkPhysicalDeviceCooperativeMatrixFeaturesKHR*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_FEATURES_KHR);
		if(features) Log::printf("\nCooperativeMatrixFeatures:\n");
		FEATURE(cooperativeMatrix)
		FEATURE(cooperativeMatrixRobustBufferAccess)
	}
	
	{
		auto *features = (const VkPhysicalDeviceVulkan11Features*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES);
		if(features) Log::printf("\nFeatures11:\n");
		FEATURE(storageBuffer16BitAccess)
		FEATURE(uniformAndStorageBuffer16BitAccess)
		FEATURE(storagePushConstant16)
		FEATURE(storageInputOutput16)
		FEATURE(multiview)
		FEATURE(multiviewGeometryShader)
		FEATURE(multiviewTessellationShader)
		FEATURE(variablePointersStorageBuffer)
		FEATURE(variablePointers)
		FEATURE(protectedMemory)
		FEATURE(samplerYcbcrConversion)
		FEATURE(shaderDrawParameters)
	}
	{
		auto *features = (const VkPhysicalDeviceVulkan11Properties*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_PROPERTIES);
		if(features) Log::printf("\nProperties11:\n");
		FEATURE_U(deviceNodeMask)
		FEATURE_U(deviceLUIDValid)
		FEATURE_U(subgroupSize)
		FEATURE_X(subgroupSupportedStages)
		FEATURE_X(subgroupSupportedOperations)
		FEATURE_U(subgroupQuadOperationsInAllStages)
		FEATURE_X(pointClippingBehavior)
		FEATURE_U(maxMultiviewViewCount)
		FEATURE_U(maxMultiviewInstanceIndex)
		FEATURE_U(protectedNoFault)
		FEATURE_U(maxPerSetDescriptors)
		FEATURE_U(maxMemoryAllocationSize)
	}
	{
		auto *features = (const VkPhysicalDeviceVulkan12Features*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES);
		if(features) Log::printf("\nFeatures12:\n");
		FEATURE(samplerMirrorClampToEdge)
		FEATURE(drawIndirectCount)
		FEATURE(storageBuffer8BitAccess)
		FEATURE(uniformAndStorageBuffer8BitAccess)
		FEATURE(storagePushConstant8)
		FEATURE(shaderBufferInt64Atomics)
		FEATURE(shaderSharedInt64Atomics)
		FEATURE(shaderFloat16)
		FEATURE(shaderInt8)
		FEATURE(descriptorIndexing)
		FEATURE(shaderInputAttachmentArrayDynamicIndexing)
		FEATURE(shaderUniformTexelBufferArrayDynamicIndexing)
		FEATURE(shaderStorageTexelBufferArrayDynamicIndexing)
		FEATURE(shaderUniformBufferArrayNonUniformIndexing)
		FEATURE(shaderSampledImageArrayNonUniformIndexing)
		FEATURE(shaderStorageBufferArrayNonUniformIndexing)
		FEATURE(shaderStorageImageArrayNonUniformIndexing)
		FEATURE(shaderInputAttachmentArrayNonUniformIndexing)
		FEATURE(shaderUniformTexelBufferArrayNonUniformIndexing)
		FEATURE(shaderStorageTexelBufferArrayNonUniformIndexing)
		FEATURE(descriptorBindingUniformBufferUpdateAfterBind)
		FEATURE(descriptorBindingSampledImageUpdateAfterBind)
		FEATURE(descriptorBindingStorageImageUpdateAfterBind)
		FEATURE(descriptorBindingStorageBufferUpdateAfterBind)
		FEATURE(descriptorBindingUniformTexelBufferUpdateAfterBind)
		FEATURE(descriptorBindingStorageTexelBufferUpdateAfterBind)
		FEATURE(descriptorBindingUpdateUnusedWhilePending)
		FEATURE(descriptorBindingPartiallyBound)
		FEATURE(descriptorBindingVariableDescriptorCount)
		FEATURE(runtimeDescriptorArray)
		FEATURE(samplerFilterMinmax)
		FEATURE(scalarBlockLayout)
		FEATURE(imagelessFramebuffer)
		FEATURE(uniformBufferStandardLayout)
		FEATURE(shaderSubgroupExtendedTypes)
		FEATURE(separateDepthStencilLayouts)
		FEATURE(hostQueryReset)
		FEATURE(timelineSemaphore)
		FEATURE(bufferDeviceAddress)
		FEATURE(bufferDeviceAddressCaptureReplay)
		FEATURE(bufferDeviceAddressMultiDevice)
		FEATURE(vulkanMemoryModel)
		FEATURE(vulkanMemoryModelDeviceScope)
		FEATURE(vulkanMemoryModelAvailabilityVisibilityChains)
		FEATURE(shaderOutputViewportIndex)
		FEATURE(shaderOutputLayer)
		FEATURE(subgroupBroadcastDynamicId)
	}
	{
		auto *features = (const VkPhysicalDeviceVulkan12Properties*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_PROPERTIES);
		if(features) Log::printf("\nProperties12:\n");
		FEATURE_X(driverID)
		FEATURE_S(driverName)
		FEATURE_S(driverInfo)
		FEATURE_X(denormBehaviorIndependence)
		FEATURE_X(roundingModeIndependence)
		FEATURE_U(shaderSignedZeroInfNanPreserveFloat16)
		FEATURE_U(shaderSignedZeroInfNanPreserveFloat32)
		FEATURE_U(shaderSignedZeroInfNanPreserveFloat64)
		FEATURE_U(shaderDenormPreserveFloat16)
		FEATURE_U(shaderDenormPreserveFloat32)
		FEATURE_U(shaderDenormPreserveFloat64)
		FEATURE_U(shaderDenormFlushToZeroFloat16)
		FEATURE_U(shaderDenormFlushToZeroFloat32)
		FEATURE_U(shaderDenormFlushToZeroFloat64)
		FEATURE_U(shaderRoundingModeRTEFloat16)
		FEATURE_U(shaderRoundingModeRTEFloat32)
		FEATURE_U(shaderRoundingModeRTEFloat64)
		FEATURE_U(shaderRoundingModeRTZFloat16)
		FEATURE_U(shaderRoundingModeRTZFloat32)
		FEATURE_U(shaderRoundingModeRTZFloat64)
		FEATURE_U(maxUpdateAfterBindDescriptorsInAllPools)
		FEATURE_U(shaderUniformBufferArrayNonUniformIndexingNative)
		FEATURE_U(shaderSampledImageArrayNonUniformIndexingNative)
		FEATURE_U(shaderStorageBufferArrayNonUniformIndexingNative)
		FEATURE_U(shaderStorageImageArrayNonUniformIndexingNative)
		FEATURE_U(shaderInputAttachmentArrayNonUniformIndexingNative)
		FEATURE_U(robustBufferAccessUpdateAfterBind)
		FEATURE_U(quadDivergentImplicitLod)
		FEATURE_U(maxPerStageDescriptorUpdateAfterBindSamplers)
		FEATURE_U(maxPerStageDescriptorUpdateAfterBindUniformBuffers)
		FEATURE_U(maxPerStageDescriptorUpdateAfterBindStorageBuffers)
		FEATURE_U(maxPerStageDescriptorUpdateAfterBindSampledImages)
		FEATURE_U(maxPerStageDescriptorUpdateAfterBindStorageImages)
		FEATURE_U(maxPerStageDescriptorUpdateAfterBindInputAttachments)
		FEATURE_U(maxPerStageUpdateAfterBindResources)
		FEATURE_U(maxDescriptorSetUpdateAfterBindSamplers)
		FEATURE_U(maxDescriptorSetUpdateAfterBindUniformBuffers)
		FEATURE_U(maxDescriptorSetUpdateAfterBindUniformBuffersDynamic)
		FEATURE_U(maxDescriptorSetUpdateAfterBindStorageBuffers)
		FEATURE_U(maxDescriptorSetUpdateAfterBindStorageBuffersDynamic)
		FEATURE_U(maxDescriptorSetUpdateAfterBindSampledImages)
		FEATURE_U(maxDescriptorSetUpdateAfterBindStorageImages)
		FEATURE_U(maxDescriptorSetUpdateAfterBindInputAttachments)
		FEATURE_X(supportedDepthResolveModes)
		FEATURE_X(supportedStencilResolveModes)
		FEATURE_U(independentResolveNone)
		FEATURE_U(independentResolve)
		FEATURE_U(filterMinmaxSingleComponentFormats)
		FEATURE_U(filterMinmaxImageComponentMapping)
		FEATURE_U(maxTimelineSemaphoreValueDifference)
		FEATURE_X(framebufferIntegerColorSampleCounts)
	}
	
	{
		auto *features = (const VkPhysicalDeviceVulkan13Features*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES);
		if(features) Log::printf("\nFeatures13:\n");
		FEATURE(robustImageAccess)
		FEATURE(inlineUniformBlock)
		FEATURE(descriptorBindingInlineUniformBlockUpdateAfterBind)
		FEATURE(pipelineCreationCacheControl)
		FEATURE(privateData)
		FEATURE(shaderDemoteToHelperInvocation)
		FEATURE(shaderTerminateInvocation)
		FEATURE(subgroupSizeControl)
		FEATURE(computeFullSubgroups)
		FEATURE(synchronization2)
		FEATURE(textureCompressionASTC_HDR)
		FEATURE(shaderZeroInitializeWorkgroupMemory)
		FEATURE(dynamicRendering)
		FEATURE(shaderIntegerDotProduct)
		FEATURE(maintenance4)
	}
	{
		auto *features = (const VkPhysicalDeviceVulkan13Properties*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_PROPERTIES);
		if(features) Log::printf("\nProperties13:\n");
		FEATURE_U(minSubgroupSize)
		FEATURE_U(maxSubgroupSize)
		FEATURE_U(maxComputeWorkgroupSubgroups)
		FEATURE_X(requiredSubgroupSizeStages)
		FEATURE_U(maxInlineUniformBlockSize)
		FEATURE_U(maxPerStageDescriptorInlineUniformBlocks)
		FEATURE_U(maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks)
		FEATURE_U(maxDescriptorSetInlineUniformBlocks)
		FEATURE_U(maxDescriptorSetUpdateAfterBindInlineUniformBlocks)
		FEATURE_U(maxInlineUniformTotalSize)
		FEATURE_U(integerDotProduct8BitUnsignedAccelerated)
		FEATURE_U(integerDotProduct8BitSignedAccelerated)
		FEATURE_U(integerDotProduct8BitMixedSignednessAccelerated)
		FEATURE_U(integerDotProduct4x8BitPackedUnsignedAccelerated)
		FEATURE_U(integerDotProduct4x8BitPackedSignedAccelerated)
		FEATURE_U(integerDotProduct4x8BitPackedMixedSignednessAccelerated)
		FEATURE_U(integerDotProduct16BitUnsignedAccelerated)
		FEATURE_U(integerDotProduct16BitSignedAccelerated)
		FEATURE_U(integerDotProduct16BitMixedSignednessAccelerated)
		FEATURE_U(integerDotProduct32BitUnsignedAccelerated)
		FEATURE_U(integerDotProduct32BitSignedAccelerated)
		FEATURE_U(integerDotProduct32BitMixedSignednessAccelerated)
		FEATURE_U(integerDotProduct64BitUnsignedAccelerated)
		FEATURE_U(integerDotProduct64BitSignedAccelerated)
		FEATURE_U(integerDotProduct64BitMixedSignednessAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating8BitUnsignedAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating8BitSignedAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating8BitMixedSignednessAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating4x8BitPackedUnsignedAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating4x8BitPackedSignedAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating4x8BitPackedMixedSignednessAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating16BitUnsignedAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating16BitSignedAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating16BitMixedSignednessAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating32BitUnsignedAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating32BitSignedAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating32BitMixedSignednessAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating64BitUnsignedAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating64BitSignedAccelerated)
		FEATURE_U(integerDotProductAccumulatingSaturating64BitMixedSignednessAccelerated)
		FEATURE_U(storageTexelBufferOffsetAlignmentBytes)
		FEATURE_U(storageTexelBufferOffsetSingleTexelAlignment)
		FEATURE_U(uniformTexelBufferOffsetAlignmentBytes)
		FEATURE_U(uniformTexelBufferOffsetSingleTexelAlignment)
		FEATURE_U(maxBufferSize)
	}
	
	{
		auto *features = (const VkPhysicalDeviceVulkan14Features*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_FEATURES);
		if(features) Log::printf("\nFeatures14:\n");
		FEATURE(globalPriorityQuery)
		FEATURE(shaderSubgroupRotate)
		FEATURE(shaderSubgroupRotateClustered)
		FEATURE(shaderFloatControls2)
		FEATURE(shaderExpectAssume)
		FEATURE(rectangularLines)
		FEATURE(bresenhamLines)
		FEATURE(smoothLines)
		FEATURE(stippledRectangularLines)
		FEATURE(stippledBresenhamLines)
		FEATURE(stippledSmoothLines)
		FEATURE(vertexAttributeInstanceRateDivisor)
		FEATURE(vertexAttributeInstanceRateZeroDivisor)
		FEATURE(indexTypeUint8)
		FEATURE(dynamicRenderingLocalRead)
		FEATURE(maintenance5)
		FEATURE(maintenance6)
		FEATURE(pipelineProtectedAccess)
		FEATURE(pipelineRobustness)
		FEATURE(hostImageCopy)
		FEATURE(pushDescriptor)
	}
	{
		auto *features = (const VkPhysicalDeviceVulkan14Properties*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_PROPERTIES);
		if(features) Log::printf("\nProperties14:\n");
		FEATURE_U(lineSubPixelPrecisionBits)
		FEATURE_U(maxVertexAttribDivisor)
		FEATURE_U(supportsNonZeroFirstInstance)
		FEATURE_U(maxPushDescriptors)
		FEATURE_U(dynamicRenderingLocalReadDepthStencilAttachments)
		FEATURE_U(dynamicRenderingLocalReadMultisampledAttachments)
		FEATURE_U(earlyFragmentMultisampleCoverageAfterSampleCounting)
		FEATURE_U(earlyFragmentSampleMaskTestBeforeSampleCounting)
		FEATURE_U(depthStencilSwizzleOneSupport)
		FEATURE_U(polygonModePointSize)
		FEATURE_U(nonStrictSinglePixelWideLinesUseParallelogram)
		FEATURE_U(nonStrictWideLinesUseParallelogram)
		FEATURE_U(blockTexelViewCompatibleMultipleLayers)
		FEATURE_U(maxCombinedImageSamplerDescriptorCount)
		FEATURE_U(fragmentShadingRateClampCombinerInputs)
		FEATURE_X(defaultRobustnessStorageBuffers)
		FEATURE_X(defaultRobustnessUniformBuffers)
		FEATURE_X(defaultRobustnessVertexInputs)
		FEATURE_X(defaultRobustnessImages)
		FEATURE_U(copySrcLayoutCount)
		FEATURE_U(copyDstLayoutCount)
		FEATURE_U(identicalMemoryTypeRequirements)
	}
	
	{
		auto *features = (const VkPhysicalDeviceAccelerationStructureFeaturesKHR*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR);
		if(features) Log::printf("\nAccelerationStructureFeatures:\n");
		FEATURE(accelerationStructure)
		FEATURE(accelerationStructureCaptureReplay)
		FEATURE(accelerationStructureIndirectBuild)
		FEATURE(accelerationStructureHostCommands)
		FEATURE(descriptorBindingAccelerationStructureUpdateAfterBind)
	}
	{
		auto *features = (const VkPhysicalDeviceAccelerationStructurePropertiesKHR*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_PROPERTIES_KHR);
		if(features) Log::printf("\nAccelerationStructureProperties:\n");
		FEATURE_U(maxGeometryCount)
		FEATURE_U(maxInstanceCount)
		FEATURE_U(maxPrimitiveCount)
		FEATURE_U(maxPerStageDescriptorAccelerationStructures)
		FEATURE_U(maxPerStageDescriptorUpdateAfterBindAccelerationStructures)
		FEATURE_U(maxDescriptorSetAccelerationStructures)
		FEATURE_U(maxDescriptorSetUpdateAfterBindAccelerationStructures)
		FEATURE_U(minAccelerationStructureScratchOffsetAlignment)
	}
	
	{
		auto *features = (const VkPhysicalDeviceRayTracingPipelineFeaturesKHR*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR);
		if(features) Log::printf("\nRayTracingPipelineFeatures:\n");
		FEATURE(rayTracingPipeline)
		FEATURE(rayTracingPipelineShaderGroupHandleCaptureReplay)
		FEATURE(rayTracingPipelineShaderGroupHandleCaptureReplayMixed)
		FEATURE(rayTracingPipelineTraceRaysIndirect)
		FEATURE(rayTraversalPrimitiveCulling)
	}
	{
		auto *features = (const VkPhysicalDeviceRayTracingPipelinePropertiesKHR*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_PROPERTIES_KHR);
		if(features) Log::printf("\nRayTracingPipelineProperties:\n");
		FEATURE_U(shaderGroupHandleSize)
		FEATURE_U(maxRayRecursionDepth)
		FEATURE_U(maxShaderGroupStride)
		FEATURE_U(shaderGroupBaseAlignment)
		FEATURE_U(shaderGroupHandleCaptureReplaySize)
		FEATURE_U(maxRayDispatchInvocationCount)
		FEATURE_U(shaderGroupHandleAlignment)
		FEATURE_U(maxRayHitAttributeSize)
	}
	
	{
		auto *features = (const VkPhysicalDeviceRayQueryFeaturesKHR*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_QUERY_FEATURES_KHR);
		if(features) Log::printf("\nRayQueryFeatures:\n");
		FEATURE(rayQuery)
	}
	
	{
		auto *features = (const VkPhysicalDeviceExternalMemoryHostPropertiesEXT*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_HOST_PROPERTIES_EXT);
		if(features) Log::printf("\nExternalMemoryHostPropertiesEXT:\n");
		FEATURE_U(minImportedHostPointerAlignment)
	}
	
	{
		auto *features = (const VkPhysicalDeviceConservativeRasterizationPropertiesEXT*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONSERVATIVE_RASTERIZATION_PROPERTIES_EXT);
		if(features) Log::printf("\nConservativeRasterPropertiesEXT:\n");
		FEATURE_U(primitiveOverestimationSize)
		FEATURE_U(maxExtraPrimitiveOverestimationSize)
		FEATURE_U(extraPrimitiveOverestimationSizeGranularity)
		FEATURE_U(primitiveUnderestimation)
		FEATURE_U(conservativePointAndLineRasterization)
		FEATURE_U(degenerateTrianglesRasterized)
		FEATURE_U(degenerateLinesRasterized)
		FEATURE_U(fullyCoveredFragmentShaderInputVariable)
		FEATURE_U(conservativeRasterizationPostDepthCoverage)
	}
	
	{
		auto *features = (const VkPhysicalDeviceConditionalRenderingFeaturesEXT*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONDITIONAL_RENDERING_FEATURES_EXT);
		if(features) Log::printf("\nConditionalRenderingFeaturesEXT:\n");
		FEATURE(conditionalRendering)
		FEATURE(inheritedConditionalRendering)
	}
	
	{
		auto *features = (const VkPhysicalDeviceSubgroupSizeControlFeaturesEXT*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_FEATURES_EXT);
		if(features) Log::printf("\nSubgroupSizeControlFeaturesEXT:\n");
		FEATURE(subgroupSizeControl)
		FEATURE(computeFullSubgroups)
	}
	{
		auto *features = (const VkPhysicalDeviceSubgroupSizeControlPropertiesEXT*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_PROPERTIES_EXT);
		if(features) Log::printf("\nSubgroupSizeControlPropertiesEXT:\n");
		FEATURE_U(minSubgroupSize)
		FEATURE_U(maxSubgroupSize)
		FEATURE_U(maxComputeWorkgroupSubgroups)
		FEATURE_U(requiredSubgroupSizeStages)
	}
	
	{
		auto *features = (const VkPhysicalDeviceShaderAtomicFloatFeaturesEXT*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT);
		if(features) Log::printf("\nShaderAtomicFloatFeaturesEXT:\n");
		FEATURE(shaderBufferFloat32Atomics)
		FEATURE(shaderBufferFloat32AtomicAdd)
		FEATURE(shaderBufferFloat64Atomics)
		FEATURE(shaderBufferFloat64AtomicAdd)
		FEATURE(shaderSharedFloat32Atomics)
		FEATURE(shaderSharedFloat32AtomicAdd)
		FEATURE(shaderSharedFloat64Atomics)
		FEATURE(shaderSharedFloat64AtomicAdd)
		FEATURE(shaderImageFloat32Atomics)
		FEATURE(shaderImageFloat32AtomicAdd)
		FEATURE(sparseImageFloat32Atomics)
		FEATURE(sparseImageFloat32AtomicAdd)
	}
	
	{
		auto *features = (const VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_ATOMIC_INT64_FEATURES_EXT);
		if(features) Log::printf("\nShaderImageAtomicInt64FeaturesEXT:\n");
		FEATURE(shaderImageInt64Atomics)
		FEATURE(sparseImageInt64Atomics)
	}
	
	{
		auto *features = (const VkPhysicalDeviceMeshShaderFeaturesEXT*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_EXT);
		if(features) Log::printf("\nMeshShaderFeaturesEXT:\n");
		FEATURE(taskShader)
		FEATURE(meshShader)
		FEATURE(multiviewMeshShader)
		FEATURE(primitiveFragmentShadingRateMeshShader)
		FEATURE(meshShaderQueries)
	}
	
	{
		auto *features = (const VkPhysicalDeviceMeshShaderPropertiesEXT*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_EXT);
		if(features) Log::printf("\nMeshShaderPropertiesEXT:\n");
		FEATURE_U(maxTaskWorkGroupTotalCount)
		FEATURE_V(maxTaskWorkGroupCount)
		FEATURE_U(maxTaskWorkGroupInvocations)
		FEATURE_V(maxTaskWorkGroupSize)
		FEATURE_U(maxTaskPayloadSize)
		FEATURE_U(maxTaskSharedMemorySize)
		FEATURE_U(maxTaskPayloadAndSharedMemorySize)
		FEATURE_U(maxMeshWorkGroupTotalCount)
		FEATURE_V(maxMeshWorkGroupCount)
		FEATURE_U(maxMeshWorkGroupInvocations)
		FEATURE_V(maxMeshWorkGroupSize)
		FEATURE_U(maxMeshSharedMemorySize)
		FEATURE_U(maxMeshPayloadAndSharedMemorySize)
		FEATURE_U(maxMeshOutputMemorySize)
		FEATURE_U(maxMeshPayloadAndOutputMemorySize)
		FEATURE_U(maxMeshOutputComponents)
		FEATURE_U(maxMeshOutputVertices)
		FEATURE_U(maxMeshOutputPrimitives)
		FEATURE_U(maxMeshOutputLayers)
		FEATURE_U(maxMeshMultiviewViewCount)
		FEATURE_U(meshOutputPerVertexGranularity)
		FEATURE_U(meshOutputPerPrimitiveGranularity)
		FEATURE_U(maxPreferredTaskWorkGroupInvocations)
		FEATURE_U(maxPreferredMeshWorkGroupInvocations)
		FEATURE_U(prefersLocalInvocationVertexOutput)
		FEATURE_U(prefersLocalInvocationPrimitiveOutput)
		FEATURE_U(prefersCompactVertexOutput)
		FEATURE_U(prefersCompactPrimitiveOutput)
	}
	
	{
		auto *features = (const VkPhysicalDevicePCIBusInfoPropertiesEXT*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PCI_BUS_INFO_PROPERTIES_EXT);
		if(features) Log::printf("\nPCIBusInfoPropertiesEXT:\n");
		FEATURE_U(pciDomain)
		FEATURE_U(pciBus)
		FEATURE_U(pciDevice)
		FEATURE_U(pciFunction)
	}
	
	{
		auto *features = (const VkPhysicalDeviceMemoryProperties2*)device.getVKFeatures(VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2);
		if(features) Log::printf("\nMemory:\n");
		if(features) {
			const VkPhysicalDeviceMemoryProperties &memory = features->memoryProperties;
			for(uint32_t i = 0; i < memory.memoryTypeCount; i++) {
				String flags;
				const auto &type = memory.memoryTypes[i];
				if(type.propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) flags += "; deviceLocal";
				if(type.propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) flags += "; hostVisible";
				if(type.propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) flags += "; hostCoherent";
				if(type.propertyFlags & VK_MEMORY_PROPERTY_HOST_CACHED_BIT) flags += "; hostCached";
				if(type.propertyFlags & VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT) flags += "; lazilyAllocated";
				if(type.propertyFlags & VK_MEMORY_PROPERTY_PROTECTED_BIT) flags += "; protected";
				if(type.propertyFlags & VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD) flags += "; deviceCoherentAMD";
				if(type.propertyFlags & VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD) flags += "; deviceUncachedAMD";
				if(type.propertyFlags & VK_MEMORY_PROPERTY_RDMA_CAPABLE_BIT_NV) flags += "; rdmaCapableNV";
				Log::printf("  type: %u; heap: %u; flags: 0x%x%s\n", i, type.heapIndex, type.propertyFlags, flags.get());
			}
			for(uint32_t i = 0; i < memory.memoryHeapCount; i++) {
				String flags;
				const auto &heap = memory.memoryHeaps[i];
				if(heap.flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) flags += "; deviceLocal";
				if(heap.flags & VK_MEMORY_HEAP_MULTI_INSTANCE_BIT) flags += "; multiInstance";
				Log::printf("  heap: %u; %s; flags: 0x%x%s\n", i, String::fromBytes(heap.size).get(), heap.flags, flags.get());
			}
		}
	}
	
	// finish context
	context.finish();
	
	return 0;
}

// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimContext.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create app
	App app(argc, argv);
	if(!app.create()) return 1;
	
	// create context
	Context context(app.getPlatform(), app.getDevice());
	if(!context || !context.create()) return 1;
	
	// create device
	Device device(context);
	if(!device) return 1;
	
	// device name
	TS_LOGF(Message, "%s (%s)\n", device.getName().get(), device.getPlatformName());
	if(device.getVendor()) TS_LOGF(Message, "Vendor: %s\n", device.getVendor().get());
	if(device.getVersion()) TS_LOGF(Message, "Version: %s\n", device.getVersion().get());
	
	// device features
	const Device::Features &features = device.getFeatures();
	
	#define DECLARE_PRINT_BOOL(NAME) TS_LOGF(Message, #NAME ": %s\n", features.NAME ? "true" : "false")
	#define DECLARE_PRINT_UINT(NAME) TS_LOGF(Message, #NAME ": %u\n", features.NAME)
	#define DECLARE_PRINT_UHEX(NAME) TS_LOGF(Message, #NAME ": 0x%x\n", features.NAME)
	#define DECLARE_PRINT_UXYZ(NAME) TS_LOGF(Message, #NAME ": %u %u %u\n", features.NAME ## X, features.NAME ## Y, features.NAME ## Z)
	#define DECLARE_PRINT_SIZE(NAME) TS_LOGF(Message, #NAME ": %s\n", String::fromBytes(features.NAME).get())
	
	DECLARE_PRINT_BOOL(threadAccess);
	
	DECLARE_PRINT_BOOL(bufferTable);
	DECLARE_PRINT_BOOL(bufferSparse);
	
	DECLARE_PRINT_BOOL(textureTable);
	DECLARE_PRINT_BOOL(textureSparse);
	DECLARE_PRINT_BOOL(textureArrayCube);
	DECLARE_PRINT_BOOL(textureArraySparse);
	DECLARE_PRINT_BOOL(surfaceMultisample);
	
	DECLARE_PRINT_BOOL(drawBaseInstance);
	DECLARE_PRINT_BOOL(drawIndirectIndex);
	DECLARE_PRINT_BOOL(drawIndirectCount);
	DECLARE_PRINT_BOOL(taskIndirectCount);
	
	DECLARE_PRINT_BOOL(vertexStorage);
	DECLARE_PRINT_BOOL(vertexIndexLayer);
	DECLARE_PRINT_BOOL(geometryPassthrough);
	DECLARE_PRINT_BOOL(fragmentBarycentric);
	DECLARE_PRINT_BOOL(fragmentStencilExport);
	
	DECLARE_PRINT_BOOL(blendDualSource);
	DECLARE_PRINT_BOOL(depthRangeOneToOne);
	DECLARE_PRINT_BOOL(rasterConservative);
	
	DECLARE_PRINT_BOOL(renderConditional);
	
	DECLARE_PRINT_BOOL(computeTracing);
	DECLARE_PRINT_BOOL(fragmentTracing);
	DECLARE_PRINT_BOOL(traversalTracing);
	DECLARE_PRINT_BOOL(buildIndirectTracing);
	DECLARE_PRINT_UINT(maxTraversalDepth);
	
	DECLARE_PRINT_BOOL(subgroupVote);
	DECLARE_PRINT_BOOL(subgroupMath);
	DECLARE_PRINT_BOOL(subgroupShuffle);
	DECLARE_PRINT_UINT(subgroupSize);
	DECLARE_PRINT_UINT(minSubgroupSize);
	DECLARE_PRINT_UINT(maxSubgroupSize);
	
	DECLARE_PRINT_BOOL(shaderu8);
	DECLARE_PRINT_BOOL(shaderf16);
	DECLARE_PRINT_BOOL(shaderu16);
	DECLARE_PRINT_BOOL(shaderf64);
	DECLARE_PRINT_BOOL(shaderu64);
	
	DECLARE_PRINT_BOOL(atomicGroupf32);
	DECLARE_PRINT_BOOL(atomicGroupu64);
	DECLARE_PRINT_BOOL(atomicBufferf32);
	DECLARE_PRINT_BOOL(atomicBufferu64);
	DECLARE_PRINT_BOOL(atomicTexturef32);
	DECLARE_PRINT_BOOL(atomicTextureu32);
	DECLARE_PRINT_BOOL(atomicTextureu64);
	
	DECLARE_PRINT_BOOL(matrix16f16);
	DECLARE_PRINT_BOOL(matrix16x8x8f16);
	DECLARE_PRINT_BOOL(matrix16x8x16f16);
	DECLARE_PRINT_BOOL(matrix16f16f32);
	DECLARE_PRINT_BOOL(matrix16x8x8f16f32);
	DECLARE_PRINT_BOOL(matrix16x8x16f16f32);
	
	DECLARE_PRINT_UINT(uniformAlignment);
	DECLARE_PRINT_UINT(storageAlignment);
	
	DECLARE_PRINT_UINT(maxTexture2DSize);
	DECLARE_PRINT_UINT(maxTexture3DSize);
	DECLARE_PRINT_UINT(maxTextureLayers);
	DECLARE_PRINT_UINT(maxTextureSamples);
	
	DECLARE_PRINT_UXYZ(maxGroupSize);
	DECLARE_PRINT_UXYZ(maxGroupCount);
	
	DECLARE_PRINT_UINT(maxTaskCount);
	DECLARE_PRINT_SIZE(maxTaskMemory);
	DECLARE_PRINT_UINT(maxTaskMeshes);
	
	DECLARE_PRINT_SIZE(maxMeshMemory);
	DECLARE_PRINT_UINT(maxMeshVertices);
	DECLARE_PRINT_UINT(maxMeshPrimitives);
	
	DECLARE_PRINT_UINT(maxViewportCount);
	DECLARE_PRINT_UINT(maxClipCullCount);
	
	DECLARE_PRINT_SIZE(maxUniformSize);
	DECLARE_PRINT_SIZE(maxStorageSize);
	
	DECLARE_PRINT_SIZE(groupMemory);
	DECLARE_PRINT_SIZE(videoMemory);
	
	DECLARE_PRINT_UHEX(vendorID);
	DECLARE_PRINT_UHEX(deviceID);
	DECLARE_PRINT_UHEX(pciBusID);
	DECLARE_PRINT_UHEX(pciDomainID);
	DECLARE_PRINT_UHEX(pciDeviceID);
	
	// finish context
	context.finish();
	
	return 0;
}

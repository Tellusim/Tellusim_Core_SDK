// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <d3d11_4.h>

#include <platform/TellusimContext.h>
#include <platform/TellusimDevice.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create context
	D3D11Context context;
	if(!context.create()) return 1;
	
	// create device
	D3D11Device device(context);
	if(!device) return 1;
	
	// device name
	TS_LOGF(Message, "%s (%s)\n", device.getName().get(), device.getPlatformName());
	if(device.getVendor()) TS_LOGF(Message, "Vendor: %s\n", device.getVendor().get());
	if(device.getVersion()) TS_LOGF(Message, "Version: %s\n", device.getVersion().get());
	
	// device features
	#define FEATURE(NAME) if(features) Log::printf("  " #NAME ": %u\n", (uint32_t)features->NAME);
	
	{
		auto *features = (const D3D11_FEATURE_DATA_D3D11_OPTIONS*)device.getD3D11Features(0);
		if(features) Log::printf("\nFeatures:\n");
		FEATURE(OutputMergerLogicOp)
		FEATURE(UAVOnlyRenderingForcedSampleCount)
		FEATURE(DiscardAPIsSeenByDriver)
		FEATURE(FlagsForUpdateAndCopySeenByDriver)
		FEATURE(ClearView)
		FEATURE(CopyWithOverlap)
		FEATURE(ConstantBufferPartialUpdate)
		FEATURE(ConstantBufferOffsetting)
		FEATURE(MapNoOverwriteOnDynamicConstantBuffer)
		FEATURE(MapNoOverwriteOnDynamicBufferSRV)
		FEATURE(MultisampleRTVWithForcedSampleCountOne)
		FEATURE(SAD4ShaderInstructions)
		FEATURE(ExtendedDoublesShaderInstructions)
		FEATURE(ExtendedResourceSharing)
	}
	
	{
		auto *features = (const D3D11_FEATURE_DATA_D3D11_OPTIONS1*)device.getD3D11Features(1);
		if(features) Log::printf("\nFeatures1:\n");
		FEATURE(TiledResourcesTier)
		FEATURE(MinMaxFiltering)
		FEATURE(ClearViewAlsoSupportsDepthOnlyFormats)
		FEATURE(MapOnDefaultBuffers)
	}
	
	{
		auto *features = (const D3D11_FEATURE_DATA_D3D11_OPTIONS2*)device.getD3D11Features(2);
		if(features) Log::printf("\nFeatures2:\n");
		FEATURE(PSSpecifiedStencilRefSupported)
		FEATURE(TypedUAVLoadAdditionalFormats)
		FEATURE(ROVsSupported)
		FEATURE(ConservativeRasterizationTier)
		FEATURE(TiledResourcesTier)
		FEATURE(MapOnDefaultTextures)
		FEATURE(StandardSwizzle)
		FEATURE(UnifiedMemoryArchitecture)
	}
	
	{
		auto *features = (const D3D11_FEATURE_DATA_D3D11_OPTIONS3*)device.getD3D11Features(3);
		if(features) Log::printf("\nFeatures3:\n");
		FEATURE(VPAndRTArrayIndexFromAnyShaderFeedingRasterizer)
	}
	
	{
		auto *features = (const D3D11_FEATURE_DATA_D3D11_OPTIONS4*)device.getD3D11Features(4);
		if(features) Log::printf("\nFeatures4:\n");
		FEATURE(ExtendedNV12SharedTextureSupported)
	}
	
	{
		auto *features = (const D3D11_FEATURE_DATA_D3D11_OPTIONS5*)device.getD3D11Features(5);
		if(features) Log::printf("\nFeatures5:\n");
		FEATURE(SharedResourceTier)
	}
	
	// finish context
	context.finish();
	
	return 0;
}

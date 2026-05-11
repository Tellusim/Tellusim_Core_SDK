// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <d3d12.h>

#include <TellusimApp.h>
#include <platform/TellusimContext.h>
#include <platform/TellusimDevice.h>

/*
 */
#define D3D12_SDK_PATH	"../d3d12_common"

/*
 */
using namespace Tellusim;

/*
 */
extern "C" {
	__declspec(dllexport) extern const char *D3D12SDKPath = D3D12_SDK_PATH;
	__declspec(dllexport) extern const uint32_t D3D12SDKVersion = D3D12_PREVIEW_SDK_VERSION;
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create app
	App app(argc, argv);
	if(!app.create()) return 1;
	
	// create context
	D3D12Context context(app.getDevice());
	if(!context.create()) return 1;
	
	// create device
	D3D12Device device(context);
	if(!device) return 1;
	
	// device name
	TS_LOGF(Message, "%s (%s)\n", device.getName().get(), device.getPlatformName());
	if(device.getVendor()) TS_LOGF(Message, "Vendor: %s\n", device.getVendor().get());
	if(device.getVersion()) TS_LOGF(Message, "Version: %s\n", device.getVersion().get());
	
	// device features
	#define FEATURE(NAME) if(features) Log::printf("  " #NAME ": %u\n", (uint32_t)features->NAME);
	
	{
		auto *features = (const D3D12_FEATURE_DATA_D3D12_OPTIONS*)device.getD3D12Features(0);
		if(features) Log::printf("\nFeatures:\n");
		FEATURE(DoublePrecisionFloatShaderOps)
		FEATURE(OutputMergerLogicOp)
		FEATURE(MinPrecisionSupport)
		FEATURE(TiledResourcesTier)
		FEATURE(ResourceBindingTier)
		FEATURE(PSSpecifiedStencilRefSupported)
		FEATURE(TypedUAVLoadAdditionalFormats)
		FEATURE(ROVsSupported)
		FEATURE(ConservativeRasterizationTier)
		FEATURE(MaxGPUVirtualAddressBitsPerResource)
		FEATURE(StandardSwizzle64KBSupported)
		FEATURE(CrossNodeSharingTier)
		FEATURE(CrossAdapterRowMajorTextureSupported)
		FEATURE(VPAndRTArrayIndexFromAnyShaderFeedingRasterizerSupportedWithoutGSEmulation)
		FEATURE(ResourceHeapTier)
	}
	
	{
		auto *features = (const D3D12_FEATURE_DATA_D3D12_OPTIONS1*)device.getD3D12Features(1);
		if(features) Log::printf("\nFeatures1:\n");
		FEATURE(WaveOps)
		FEATURE(WaveLaneCountMin)
		FEATURE(WaveLaneCountMax)
		FEATURE(TotalLaneCount)
		FEATURE(ExpandedComputeResourceStates)
		FEATURE(Int64ShaderOps)
	}
	
	{
		auto *features = (const D3D12_FEATURE_DATA_D3D12_OPTIONS2*)device.getD3D12Features(2);
		if(features) Log::printf("\nFeatures2:\n");
		FEATURE(DepthBoundsTestSupported)
		FEATURE(ProgrammableSamplePositionsTier)
	}
	
	{
		auto *features = (const D3D12_FEATURE_DATA_D3D12_OPTIONS3*)device.getD3D12Features(3);
		if(features) Log::printf("\nFeatures3:\n");
		FEATURE(CopyQueueTimestampQueriesSupported)
		FEATURE(CastingFullyTypedFormatSupported)
		FEATURE(WriteBufferImmediateSupportFlags)
		FEATURE(ViewInstancingTier)
		FEATURE(BarycentricsSupported)
	}
	
	{
		auto *features = (const D3D12_FEATURE_DATA_D3D12_OPTIONS4*)device.getD3D12Features(4);
		if(features) Log::printf("\nFeatures4:\n");
		FEATURE(MSAA64KBAlignedTextureSupported)
		FEATURE(SharedResourceCompatibilityTier)
		FEATURE(Native16BitShaderOpsSupported)
	}
	
	{
		auto *features = (const D3D12_FEATURE_DATA_D3D12_OPTIONS5*)device.getD3D12Features(5);
		if(features) Log::printf("\nFeatures5:\n");
		FEATURE(SRVOnlyTiledResourceTier3)
		FEATURE(RenderPassesTier)
		FEATURE(RaytracingTier)
	}
	
	{
		auto *features = (const D3D12_FEATURE_DATA_D3D12_OPTIONS6*)device.getD3D12Features(6);
		if(features) Log::printf("\nFeatures6:\n");
		FEATURE(AdditionalShadingRatesSupported)
		FEATURE(PerPrimitiveShadingRateSupportedWithViewportIndexing)
		FEATURE(VariableShadingRateTier)
		FEATURE(ShadingRateImageTileSize)
		FEATURE(BackgroundProcessingSupported)
	}
	
	{
		auto *features = (const D3D12_FEATURE_DATA_D3D12_OPTIONS7*)device.getD3D12Features(7);
		if(features) Log::printf("\nFeatures7:\n");
		FEATURE(MeshShaderTier)
		FEATURE(SamplerFeedbackTier)
	}
	
	{
		auto *features = (const D3D12_FEATURE_DATA_D3D12_OPTIONS8*)device.getD3D12Features(8);
		if(features) Log::printf("\nFeatures8:\n");
		FEATURE(UnalignedBlockTexturesSupported)
	}
	
	{
		auto *features = (const D3D12_FEATURE_DATA_D3D12_OPTIONS9*)device.getD3D12Features(9);
		if(features) Log::printf("\nFeatures9:\n");
		FEATURE(MeshShaderPipelineStatsSupported)
		FEATURE(MeshShaderSupportsFullRangeRenderTargetArrayIndex)
		FEATURE(AtomicInt64OnTypedResourceSupported)
		FEATURE(AtomicInt64OnGroupSharedSupported)
		FEATURE(DerivativesInMeshAndAmplificationShadersSupported)
		FEATURE(WaveMMATier)
	}
	
	{
		auto *features = (const D3D12_FEATURE_DATA_D3D12_OPTIONS10*)device.getD3D12Features(10);
		if(features) Log::printf("\nFeatures10:\n");
		FEATURE(VariableRateShadingSumCombinerSupported)
		FEATURE(MeshShaderPerPrimitiveShadingRateSupported)
	}
	
	{
		auto *features = (const D3D12_FEATURE_DATA_D3D12_OPTIONS11*)device.getD3D12Features(11);
		if(features) Log::printf("\nFeatures11:\n");
		FEATURE(AtomicInt64OnDescriptorHeapResourceSupported)
	}
	
	{
		auto *features = (const D3D12_FEATURE_DATA_D3D12_OPTIONS12*)device.getD3D12Features(12);
		if(features) Log::printf("\nFeatures12:\n");
		FEATURE(MSPrimitivesPipelineStatisticIncludesCulledPrimitives)
		FEATURE(EnhancedBarriersSupported)
		FEATURE(RelaxedFormatCastingSupported)
	}
	
	{
		auto *features = (const D3D12_FEATURE_DATA_D3D12_OPTIONS13*)device.getD3D12Features(13);
		if(features) Log::printf("\nFeatures13:\n");
		FEATURE(UnrestrictedBufferTextureCopyPitchSupported)
		FEATURE(UnrestrictedVertexElementAlignmentSupported)
		FEATURE(InvertedViewportHeightFlipsYSupported)
		FEATURE(InvertedViewportDepthFlipsZSupported)
		FEATURE(TextureCopyBetweenDimensionsSupported)
		FEATURE(AlphaBlendFactorSupported)
	}
	
	{
		auto *features = (const D3D12_FEATURE_DATA_D3D12_OPTIONS14*)device.getD3D12Features(14);
		if(features) Log::printf("\nFeatures14:\n");
		FEATURE(AdvancedTextureOpsSupported)
		FEATURE(WriteableMSAATexturesSupported)
		FEATURE(IndependentFrontAndBackStencilRefMaskSupported)
	}
	
	{
		auto *features = (const D3D12_FEATURE_DATA_D3D12_OPTIONS15*)device.getD3D12Features(15);
		if(features) Log::printf("\nFeatures15:\n");
		FEATURE(TriangleFanSupported)
		FEATURE(DynamicIndexBufferStripCutSupported)
	}
	
	{
		auto *features = (const D3D12_FEATURE_DATA_D3D12_OPTIONS16*)device.getD3D12Features(16);
		if(features) Log::printf("\nFeatures16:\n");
		FEATURE(DynamicDepthBiasSupported)
		FEATURE(GPUUploadHeapSupported)
	}
	
	{
		auto *features = (const D3D12_FEATURE_DATA_D3D12_OPTIONS17*)device.getD3D12Features(17);
		if(features) Log::printf("\nFeatures17:\n");
		FEATURE(NonNormalizedCoordinateSamplersSupported)
		FEATURE(ManualWriteTrackingResourceSupported)
	}
	
	{
		auto *features = (const D3D12_FEATURE_DATA_D3D12_OPTIONS18*)device.getD3D12Features(18);
		if(features) Log::printf("\nFeatures18:\n");
		FEATURE(RenderPassesValid)
	}
	
	{
		auto *features = (const D3D12_FEATURE_DATA_D3D12_OPTIONS19*)device.getD3D12Features(19);
		if(features) Log::printf("\nFeatures19:\n");
		FEATURE(MismatchingOutputDimensionsSupported)
		FEATURE(SupportedSampleCountsWithNoOutputs)
		FEATURE(PointSamplingAddressesNeverRoundUp)
		FEATURE(RasterizerDesc2Supported)
		FEATURE(NarrowQuadrilateralLinesSupported)
		FEATURE(AnisoFilterWithPointMipSupported)
		FEATURE(MaxSamplerDescriptorHeapSize)
		FEATURE(MaxSamplerDescriptorHeapSizeWithStaticSamplers)
		FEATURE(MaxViewDescriptorHeapSize)
		FEATURE(ComputeOnlyCustomHeapSupported)
	}
	
	{
		auto *features = (const D3D12_FEATURE_DATA_D3D12_OPTIONS20*)device.getD3D12Features(20);
		if(features) Log::printf("\nFeatures20:\n");
		FEATURE(ComputeOnlyWriteWatchSupported)
		FEATURE(RecreateAtTier)
	}
	
	{
		auto *features = (const D3D12_FEATURE_DATA_D3D12_OPTIONS21*)device.getD3D12Features(21);
		if(features) Log::printf("\nFeatures21:\n");
		FEATURE(WorkGraphsTier)
		FEATURE(ExecuteIndirectTier)
		FEATURE(SampleCmpGradientAndBiasSupported)
		FEATURE(ExtendedCommandInfoSupported)
	}
	
	{
		auto *features = (const D3D12_FEATURE_DATA_D3D12_OPTIONS22*)device.getD3D12Features(22);
		if(features) Log::printf("\nFeatures22:\n");
    	FEATURE(ShaderExecutionReorderingActuallyReorders)
    	FEATURE(CreateByteOffsetViewsSupported)
    	FEATURE(Max1DDispatchSize)
    	FEATURE(Max1DDispatchMeshSize)
	}
	
	// shader model
	Log::printf("\nShaderModel: %x\n", device.getShaderModel());
	
	// finish context
	context.finish();
	
	return 0;
}

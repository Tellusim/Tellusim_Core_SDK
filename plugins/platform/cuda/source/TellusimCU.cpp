// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <platform/TellusimContext.h>

#include "../include/TellusimCU.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	namespace CU {
		
		/*
		 */
		bool init() {
			
			// function address
			#define GET_ADDRESS(TYPE, NAME) { \
				NAME = (TYPE)CUContext::getProcAddress(#NAME); \
				if(NAME == nullptr && is_core) { \
					TS_LOGF(Error, "CU::init(): can't get %s function\n", #NAME); \
					return false; \
				} \
			}
			
			// core functions
			bool is_core = true;
			
			// Cuda functions
			GET_ADDRESS(PFN_cuGetErrorString, cuGetErrorString)
			GET_ADDRESS(PFN_cuGetErrorName, cuGetErrorName)
			GET_ADDRESS(PFN_cuInit, cuInit)
			GET_ADDRESS(PFN_cuDriverGetVersion, cuDriverGetVersion)
			GET_ADDRESS(PFN_cuDeviceGet, cuDeviceGet)
			GET_ADDRESS(PFN_cuDeviceGetCount, cuDeviceGetCount)
			GET_ADDRESS(PFN_cuDeviceGetName, cuDeviceGetName)
			GET_ADDRESS(PFN_cuDeviceGetUuid, cuDeviceGetUuid)
			GET_ADDRESS(PFN_cuDeviceTotalMem, cuDeviceTotalMem)
			GET_ADDRESS(PFN_cuDeviceGetAttribute, cuDeviceGetAttribute)
			GET_ADDRESS(PFN_cuDevicePrimaryCtxRetain, cuDevicePrimaryCtxRetain)
			GET_ADDRESS(PFN_cuDevicePrimaryCtxRelease, cuDevicePrimaryCtxRelease)
			GET_ADDRESS(PFN_cuDevicePrimaryCtxSetFlags, cuDevicePrimaryCtxSetFlags)
			GET_ADDRESS(PFN_cuDevicePrimaryCtxGetState, cuDevicePrimaryCtxGetState)
			GET_ADDRESS(PFN_cuDevicePrimaryCtxReset, cuDevicePrimaryCtxReset)
			GET_ADDRESS(PFN_cuCtxCreate, cuCtxCreate)
			GET_ADDRESS(PFN_cuCtxDestroy, cuCtxDestroy)
			GET_ADDRESS(PFN_cuCtxPushCurrent, cuCtxPushCurrent)
			GET_ADDRESS(PFN_cuCtxPopCurrent, cuCtxPopCurrent)
			GET_ADDRESS(PFN_cuCtxSetCurrent, cuCtxSetCurrent)
			GET_ADDRESS(PFN_cuCtxGetCurrent, cuCtxGetCurrent)
			GET_ADDRESS(PFN_cuCtxGetDevice, cuCtxGetDevice)
			GET_ADDRESS(PFN_cuCtxGetFlags, cuCtxGetFlags)
			GET_ADDRESS(PFN_cuCtxSynchronize, cuCtxSynchronize)
			GET_ADDRESS(PFN_cuCtxSetLimit, cuCtxSetLimit)
			GET_ADDRESS(PFN_cuCtxGetLimit, cuCtxGetLimit)
			GET_ADDRESS(PFN_cuCtxGetCacheConfig, cuCtxGetCacheConfig)
			GET_ADDRESS(PFN_cuCtxSetCacheConfig, cuCtxSetCacheConfig)
			GET_ADDRESS(PFN_cuCtxGetSharedMemConfig, cuCtxGetSharedMemConfig)
			GET_ADDRESS(PFN_cuCtxSetSharedMemConfig, cuCtxSetSharedMemConfig)
			GET_ADDRESS(PFN_cuCtxGetApiVersion, cuCtxGetApiVersion)
			GET_ADDRESS(PFN_cuCtxGetStreamPriorityRange, cuCtxGetStreamPriorityRange)
			GET_ADDRESS(PFN_cuModuleLoad, cuModuleLoad)
			GET_ADDRESS(PFN_cuModuleLoadData, cuModuleLoadData)
			GET_ADDRESS(PFN_cuModuleLoadDataEx, cuModuleLoadDataEx)
			GET_ADDRESS(PFN_cuModuleLoadFatBinary, cuModuleLoadFatBinary)
			GET_ADDRESS(PFN_cuModuleUnload, cuModuleUnload)
			GET_ADDRESS(PFN_cuModuleGetFunction, cuModuleGetFunction)
			GET_ADDRESS(PFN_cuModuleGetGlobal, cuModuleGetGlobal)
			GET_ADDRESS(PFN_cuModuleGetTexRef, cuModuleGetTexRef)
			GET_ADDRESS(PFN_cuModuleGetSurfRef, cuModuleGetSurfRef)
			GET_ADDRESS(PFN_cuLinkCreate, cuLinkCreate)
			GET_ADDRESS(PFN_cuLinkAddData, cuLinkAddData)
			GET_ADDRESS(PFN_cuLinkAddFile, cuLinkAddFile)
			GET_ADDRESS(PFN_cuLinkComplete, cuLinkComplete)
			GET_ADDRESS(PFN_cuLinkDestroy, cuLinkDestroy)
			GET_ADDRESS(PFN_cuMemGetInfo, cuMemGetInfo)
			GET_ADDRESS(PFN_cuMemAlloc, cuMemAlloc)
			GET_ADDRESS(PFN_cuMemAllocPitch, cuMemAllocPitch)
			GET_ADDRESS(PFN_cuMemFree, cuMemFree)
			GET_ADDRESS(PFN_cuMemGetAddressRange, cuMemGetAddressRange)
			GET_ADDRESS(PFN_cuMemAllocHost, cuMemAllocHost)
			GET_ADDRESS(PFN_cuMemFreeHost, cuMemFreeHost)
			GET_ADDRESS(PFN_cuMemHostAlloc, cuMemHostAlloc)
			GET_ADDRESS(PFN_cuMemHostGetDevicePointer, cuMemHostGetDevicePointer)
			GET_ADDRESS(PFN_cuMemHostGetFlags, cuMemHostGetFlags)
			GET_ADDRESS(PFN_cuMemAllocManaged, cuMemAllocManaged)
			GET_ADDRESS(PFN_cuDeviceGetByPCIBusId, cuDeviceGetByPCIBusId)
			GET_ADDRESS(PFN_cuDeviceGetPCIBusId, cuDeviceGetPCIBusId)
			GET_ADDRESS(PFN_cuIpcGetEventHandle, cuIpcGetEventHandle)
			GET_ADDRESS(PFN_cuIpcOpenEventHandle, cuIpcOpenEventHandle)
			GET_ADDRESS(PFN_cuIpcGetMemHandle, cuIpcGetMemHandle)
			GET_ADDRESS(PFN_cuIpcOpenMemHandle, cuIpcOpenMemHandle)
			GET_ADDRESS(PFN_cuIpcCloseMemHandle, cuIpcCloseMemHandle)
			GET_ADDRESS(PFN_cuMemHostRegister, cuMemHostRegister)
			GET_ADDRESS(PFN_cuMemHostUnregister, cuMemHostUnregister)
			GET_ADDRESS(PFN_cuMemcpy, cuMemcpy)
			GET_ADDRESS(PFN_cuMemcpyPeer, cuMemcpyPeer)
			GET_ADDRESS(PFN_cuMemcpyHtoD, cuMemcpyHtoD)
			GET_ADDRESS(PFN_cuMemcpyDtoH, cuMemcpyDtoH)
			GET_ADDRESS(PFN_cuMemcpyDtoD, cuMemcpyDtoD)
			GET_ADDRESS(PFN_cuMemcpyDtoA, cuMemcpyDtoA)
			GET_ADDRESS(PFN_cuMemcpyAtoD, cuMemcpyAtoD)
			GET_ADDRESS(PFN_cuMemcpyHtoA, cuMemcpyHtoA)
			GET_ADDRESS(PFN_cuMemcpyAtoH, cuMemcpyAtoH)
			GET_ADDRESS(PFN_cuMemcpyAtoA, cuMemcpyAtoA)
			GET_ADDRESS(PFN_cuMemcpy2D, cuMemcpy2D)
			GET_ADDRESS(PFN_cuMemcpy2DUnaligned, cuMemcpy2DUnaligned)
			GET_ADDRESS(PFN_cuMemcpy3D, cuMemcpy3D)
			GET_ADDRESS(PFN_cuMemcpy3DPeer, cuMemcpy3DPeer)
			GET_ADDRESS(PFN_cuMemcpyAsync, cuMemcpyAsync)
			GET_ADDRESS(PFN_cuMemcpyPeerAsync, cuMemcpyPeerAsync)
			GET_ADDRESS(PFN_cuMemcpyHtoDAsync, cuMemcpyHtoDAsync)
			GET_ADDRESS(PFN_cuMemcpyDtoHAsync, cuMemcpyDtoHAsync)
			GET_ADDRESS(PFN_cuMemcpyDtoDAsync, cuMemcpyDtoDAsync)
			GET_ADDRESS(PFN_cuMemcpyHtoAAsync, cuMemcpyHtoAAsync)
			GET_ADDRESS(PFN_cuMemcpyAtoHAsync, cuMemcpyAtoHAsync)
			GET_ADDRESS(PFN_cuMemcpy2DAsync, cuMemcpy2DAsync)
			GET_ADDRESS(PFN_cuMemcpy3DAsync, cuMemcpy3DAsync)
			GET_ADDRESS(PFN_cuMemcpy3DPeerAsync, cuMemcpy3DPeerAsync)
			GET_ADDRESS(PFN_cuMemsetD8, cuMemsetD8)
			GET_ADDRESS(PFN_cuMemsetD16, cuMemsetD16)
			GET_ADDRESS(PFN_cuMemsetD32, cuMemsetD32)
			GET_ADDRESS(PFN_cuMemsetD2D8, cuMemsetD2D8)
			GET_ADDRESS(PFN_cuMemsetD2D16, cuMemsetD2D16)
			GET_ADDRESS(PFN_cuMemsetD2D32, cuMemsetD2D32)
			GET_ADDRESS(PFN_cuMemsetD8Async, cuMemsetD8Async)
			GET_ADDRESS(PFN_cuMemsetD16Async, cuMemsetD16Async)
			GET_ADDRESS(PFN_cuMemsetD32Async, cuMemsetD32Async)
			GET_ADDRESS(PFN_cuMemsetD2D8Async, cuMemsetD2D8Async)
			GET_ADDRESS(PFN_cuMemsetD2D16Async, cuMemsetD2D16Async)
			GET_ADDRESS(PFN_cuMemsetD2D32Async, cuMemsetD2D32Async)
			GET_ADDRESS(PFN_cuArrayCreate, cuArrayCreate)
			GET_ADDRESS(PFN_cuArrayGetDescriptor, cuArrayGetDescriptor)
			GET_ADDRESS(PFN_cuArrayDestroy, cuArrayDestroy)
			GET_ADDRESS(PFN_cuArray3DCreate, cuArray3DCreate)
			GET_ADDRESS(PFN_cuArray3DGetDescriptor, cuArray3DGetDescriptor)
			GET_ADDRESS(PFN_cuMipmappedArrayCreate, cuMipmappedArrayCreate)
			GET_ADDRESS(PFN_cuMipmappedArrayGetLevel, cuMipmappedArrayGetLevel)
			GET_ADDRESS(PFN_cuMipmappedArrayDestroy, cuMipmappedArrayDestroy)
			GET_ADDRESS(PFN_cuPointerGetAttribute, cuPointerGetAttribute)
			GET_ADDRESS(PFN_cuMemPrefetchAsync, cuMemPrefetchAsync)
			GET_ADDRESS(PFN_cuMemAdvise, cuMemAdvise)
			GET_ADDRESS(PFN_cuMemRangeGetAttribute, cuMemRangeGetAttribute)
			GET_ADDRESS(PFN_cuMemRangeGetAttributes, cuMemRangeGetAttributes)
			GET_ADDRESS(PFN_cuPointerSetAttribute, cuPointerSetAttribute)
			GET_ADDRESS(PFN_cuPointerGetAttributes, cuPointerGetAttributes)
			GET_ADDRESS(PFN_cuStreamCreate, cuStreamCreate)
			GET_ADDRESS(PFN_cuStreamCreateWithPriority, cuStreamCreateWithPriority)
			GET_ADDRESS(PFN_cuStreamGetPriority, cuStreamGetPriority)
			GET_ADDRESS(PFN_cuStreamGetFlags, cuStreamGetFlags)
			GET_ADDRESS(PFN_cuStreamGetCtx, cuStreamGetCtx)
			GET_ADDRESS(PFN_cuStreamWaitEvent, cuStreamWaitEvent)
			GET_ADDRESS(PFN_cuStreamAddCallback, cuStreamAddCallback)
			GET_ADDRESS(PFN_cuStreamBeginCapture, cuStreamBeginCapture)
			GET_ADDRESS(PFN_cuStreamEndCapture, cuStreamEndCapture)
			GET_ADDRESS(PFN_cuStreamIsCapturing, cuStreamIsCapturing)
			GET_ADDRESS(PFN_cuStreamAttachMemAsync, cuStreamAttachMemAsync)
			GET_ADDRESS(PFN_cuStreamQuery, cuStreamQuery)
			GET_ADDRESS(PFN_cuStreamSynchronize, cuStreamSynchronize)
			GET_ADDRESS(PFN_cuStreamDestroy, cuStreamDestroy)
			GET_ADDRESS(PFN_cuEventCreate, cuEventCreate)
			GET_ADDRESS(PFN_cuEventRecord, cuEventRecord)
			GET_ADDRESS(PFN_cuEventQuery, cuEventQuery)
			GET_ADDRESS(PFN_cuEventSynchronize, cuEventSynchronize)
			GET_ADDRESS(PFN_cuEventDestroy, cuEventDestroy)
			GET_ADDRESS(PFN_cuEventElapsedTime, cuEventElapsedTime)
			GET_ADDRESS(PFN_cuImportExternalMemory, cuImportExternalMemory)
			GET_ADDRESS(PFN_cuExternalMemoryGetMappedBuffer, cuExternalMemoryGetMappedBuffer)
			GET_ADDRESS(PFN_cuExternalMemoryGetMappedMipmappedArray, cuExternalMemoryGetMappedMipmappedArray)
			GET_ADDRESS(PFN_cuDestroyExternalMemory, cuDestroyExternalMemory)
			GET_ADDRESS(PFN_cuImportExternalSemaphore, cuImportExternalSemaphore)
			GET_ADDRESS(PFN_cuSignalExternalSemaphoresAsync, cuSignalExternalSemaphoresAsync)
			GET_ADDRESS(PFN_cuWaitExternalSemaphoresAsync, cuWaitExternalSemaphoresAsync)
			GET_ADDRESS(PFN_cuDestroyExternalSemaphore, cuDestroyExternalSemaphore)
			GET_ADDRESS(PFN_cuStreamWaitValue32, cuStreamWaitValue32)
			GET_ADDRESS(PFN_cuStreamWaitValue64, cuStreamWaitValue64)
			GET_ADDRESS(PFN_cuStreamWriteValue32, cuStreamWriteValue32)
			GET_ADDRESS(PFN_cuStreamWriteValue64, cuStreamWriteValue64)
			GET_ADDRESS(PFN_cuStreamBatchMemOp, cuStreamBatchMemOp)
			GET_ADDRESS(PFN_cuFuncGetAttribute, cuFuncGetAttribute)
			GET_ADDRESS(PFN_cuFuncSetAttribute, cuFuncSetAttribute)
			GET_ADDRESS(PFN_cuFuncSetCacheConfig, cuFuncSetCacheConfig)
			GET_ADDRESS(PFN_cuFuncSetSharedMemConfig, cuFuncSetSharedMemConfig)
			GET_ADDRESS(PFN_cuLaunchKernel, cuLaunchKernel)
			GET_ADDRESS(PFN_cuLaunchCooperativeKernel, cuLaunchCooperativeKernel)
			GET_ADDRESS(PFN_cuLaunchCooperativeKernelMultiDevice, cuLaunchCooperativeKernelMultiDevice)
			GET_ADDRESS(PFN_cuLaunchHostFunc, cuLaunchHostFunc)
			GET_ADDRESS(PFN_cuGraphCreate, cuGraphCreate)
			GET_ADDRESS(PFN_cuGraphAddKernelNode, cuGraphAddKernelNode)
			GET_ADDRESS(PFN_cuGraphKernelNodeGetParams, cuGraphKernelNodeGetParams)
			GET_ADDRESS(PFN_cuGraphKernelNodeSetParams, cuGraphKernelNodeSetParams)
			GET_ADDRESS(PFN_cuGraphAddMemcpyNode, cuGraphAddMemcpyNode)
			GET_ADDRESS(PFN_cuGraphMemcpyNodeGetParams, cuGraphMemcpyNodeGetParams)
			GET_ADDRESS(PFN_cuGraphMemcpyNodeSetParams, cuGraphMemcpyNodeSetParams)
			GET_ADDRESS(PFN_cuGraphAddMemsetNode, cuGraphAddMemsetNode)
			GET_ADDRESS(PFN_cuGraphMemsetNodeGetParams, cuGraphMemsetNodeGetParams)
			GET_ADDRESS(PFN_cuGraphMemsetNodeSetParams, cuGraphMemsetNodeSetParams)
			GET_ADDRESS(PFN_cuGraphAddHostNode, cuGraphAddHostNode)
			GET_ADDRESS(PFN_cuGraphHostNodeGetParams, cuGraphHostNodeGetParams)
			GET_ADDRESS(PFN_cuGraphHostNodeSetParams, cuGraphHostNodeSetParams)
			GET_ADDRESS(PFN_cuGraphAddChildGraphNode, cuGraphAddChildGraphNode)
			GET_ADDRESS(PFN_cuGraphChildGraphNodeGetGraph, cuGraphChildGraphNodeGetGraph)
			GET_ADDRESS(PFN_cuGraphAddEmptyNode, cuGraphAddEmptyNode)
			GET_ADDRESS(PFN_cuGraphClone, cuGraphClone)
			GET_ADDRESS(PFN_cuGraphNodeFindInClone, cuGraphNodeFindInClone)
			GET_ADDRESS(PFN_cuGraphNodeGetType, cuGraphNodeGetType)
			GET_ADDRESS(PFN_cuGraphGetNodes, cuGraphGetNodes)
			GET_ADDRESS(PFN_cuGraphGetRootNodes, cuGraphGetRootNodes)
			GET_ADDRESS(PFN_cuGraphGetEdges, cuGraphGetEdges)
			GET_ADDRESS(PFN_cuGraphNodeGetDependencies, cuGraphNodeGetDependencies)
			GET_ADDRESS(PFN_cuGraphNodeGetDependentNodes, cuGraphNodeGetDependentNodes)
			GET_ADDRESS(PFN_cuGraphAddDependencies, cuGraphAddDependencies)
			GET_ADDRESS(PFN_cuGraphRemoveDependencies, cuGraphRemoveDependencies)
			GET_ADDRESS(PFN_cuGraphDestroyNode, cuGraphDestroyNode)
			GET_ADDRESS(PFN_cuGraphInstantiate, cuGraphInstantiate)
			GET_ADDRESS(PFN_cuGraphLaunch, cuGraphLaunch)
			GET_ADDRESS(PFN_cuGraphExecDestroy, cuGraphExecDestroy)
			GET_ADDRESS(PFN_cuGraphDestroy, cuGraphDestroy)
			GET_ADDRESS(PFN_cuOccupancyMaxActiveBlocksPerMultiprocessor, cuOccupancyMaxActiveBlocksPerMultiprocessor)
			GET_ADDRESS(PFN_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags, cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags)
			GET_ADDRESS(PFN_cuOccupancyMaxPotentialBlockSize, cuOccupancyMaxPotentialBlockSize)
			GET_ADDRESS(PFN_cuOccupancyMaxPotentialBlockSizeWithFlags, cuOccupancyMaxPotentialBlockSizeWithFlags)
			GET_ADDRESS(PFN_cuTexRefSetArray, cuTexRefSetArray)
			GET_ADDRESS(PFN_cuTexRefSetMipmappedArray, cuTexRefSetMipmappedArray)
			GET_ADDRESS(PFN_cuTexRefSetAddress, cuTexRefSetAddress)
			GET_ADDRESS(PFN_cuTexRefSetAddress2D, cuTexRefSetAddress2D)
			GET_ADDRESS(PFN_cuTexRefSetFormat, cuTexRefSetFormat)
			GET_ADDRESS(PFN_cuTexRefSetAddressMode, cuTexRefSetAddressMode)
			GET_ADDRESS(PFN_cuTexRefSetFilterMode, cuTexRefSetFilterMode)
			GET_ADDRESS(PFN_cuTexRefSetMipmapFilterMode, cuTexRefSetMipmapFilterMode)
			GET_ADDRESS(PFN_cuTexRefSetMipmapLevelBias, cuTexRefSetMipmapLevelBias)
			GET_ADDRESS(PFN_cuTexRefSetMipmapLevelClamp, cuTexRefSetMipmapLevelClamp)
			GET_ADDRESS(PFN_cuTexRefSetMaxAnisotropy, cuTexRefSetMaxAnisotropy)
			GET_ADDRESS(PFN_cuTexRefSetBorderColor, cuTexRefSetBorderColor)
			GET_ADDRESS(PFN_cuTexRefSetFlags, cuTexRefSetFlags)
			GET_ADDRESS(PFN_cuTexRefGetAddress, cuTexRefGetAddress)
			GET_ADDRESS(PFN_cuTexRefGetArray, cuTexRefGetArray)
			GET_ADDRESS(PFN_cuTexRefGetMipmappedArray, cuTexRefGetMipmappedArray)
			GET_ADDRESS(PFN_cuTexRefGetAddressMode, cuTexRefGetAddressMode)
			GET_ADDRESS(PFN_cuTexRefGetFilterMode, cuTexRefGetFilterMode)
			GET_ADDRESS(PFN_cuTexRefGetFormat, cuTexRefGetFormat)
			GET_ADDRESS(PFN_cuTexRefGetMipmapFilterMode, cuTexRefGetMipmapFilterMode)
			GET_ADDRESS(PFN_cuTexRefGetMipmapLevelBias, cuTexRefGetMipmapLevelBias)
			GET_ADDRESS(PFN_cuTexRefGetMipmapLevelClamp, cuTexRefGetMipmapLevelClamp)
			GET_ADDRESS(PFN_cuTexRefGetMaxAnisotropy, cuTexRefGetMaxAnisotropy)
			GET_ADDRESS(PFN_cuTexRefGetBorderColor, cuTexRefGetBorderColor)
			GET_ADDRESS(PFN_cuTexRefGetFlags, cuTexRefGetFlags)
			GET_ADDRESS(PFN_cuSurfRefSetArray, cuSurfRefSetArray)
			GET_ADDRESS(PFN_cuSurfRefGetArray, cuSurfRefGetArray)
			GET_ADDRESS(PFN_cuTexObjectCreate, cuTexObjectCreate)
			GET_ADDRESS(PFN_cuTexObjectDestroy, cuTexObjectDestroy)
			GET_ADDRESS(PFN_cuTexObjectGetResourceDesc, cuTexObjectGetResourceDesc)
			GET_ADDRESS(PFN_cuTexObjectGetTextureDesc, cuTexObjectGetTextureDesc)
			GET_ADDRESS(PFN_cuTexObjectGetResourceViewDesc, cuTexObjectGetResourceViewDesc)
			GET_ADDRESS(PFN_cuSurfObjectCreate, cuSurfObjectCreate)
			GET_ADDRESS(PFN_cuSurfObjectDestroy, cuSurfObjectDestroy)
			GET_ADDRESS(PFN_cuSurfObjectGetResourceDesc, cuSurfObjectGetResourceDesc)
			GET_ADDRESS(PFN_cuDeviceCanAccessPeer, cuDeviceCanAccessPeer)
			GET_ADDRESS(PFN_cuCtxEnablePeerAccess, cuCtxEnablePeerAccess)
			GET_ADDRESS(PFN_cuCtxDisablePeerAccess, cuCtxDisablePeerAccess)
			GET_ADDRESS(PFN_cuDeviceGetP2PAttribute, cuDeviceGetP2PAttribute)
			GET_ADDRESS(PFN_cuGraphicsUnregisterResource, cuGraphicsUnregisterResource)
			GET_ADDRESS(PFN_cuGraphicsSubResourceGetMappedArray, cuGraphicsSubResourceGetMappedArray)
			GET_ADDRESS(PFN_cuGraphicsResourceGetMappedMipmappedArray, cuGraphicsResourceGetMappedMipmappedArray)
			GET_ADDRESS(PFN_cuGraphicsResourceGetMappedPointer, cuGraphicsResourceGetMappedPointer)
			GET_ADDRESS(PFN_cuGraphicsResourceSetMapFlags, cuGraphicsResourceSetMapFlags)
			GET_ADDRESS(PFN_cuGraphicsMapResources, cuGraphicsMapResources)
			GET_ADDRESS(PFN_cuGraphicsUnmapResources, cuGraphicsUnmapResources)
			GET_ADDRESS(PFN_cuGetExportTable, cuGetExportTable)
			
			return true;
		}
	}
	
	/*****************************************************************************\
	 *
	 * Cuda functions
	 *
	\*****************************************************************************/
	
	// Cuda functions
	PFN_cuGetErrorString cuGetErrorString = nullptr;
	PFN_cuGetErrorName cuGetErrorName = nullptr;
	PFN_cuInit cuInit = nullptr;
	PFN_cuDriverGetVersion cuDriverGetVersion = nullptr;
	PFN_cuDeviceGet cuDeviceGet = nullptr;
	PFN_cuDeviceGetCount cuDeviceGetCount = nullptr;
	PFN_cuDeviceGetName cuDeviceGetName = nullptr;
	PFN_cuDeviceGetUuid cuDeviceGetUuid = nullptr;
	PFN_cuDeviceTotalMem cuDeviceTotalMem = nullptr;
	PFN_cuDeviceGetAttribute cuDeviceGetAttribute = nullptr;
	PFN_cuDevicePrimaryCtxRetain cuDevicePrimaryCtxRetain = nullptr;
	PFN_cuDevicePrimaryCtxRelease cuDevicePrimaryCtxRelease = nullptr;
	PFN_cuDevicePrimaryCtxSetFlags cuDevicePrimaryCtxSetFlags = nullptr;
	PFN_cuDevicePrimaryCtxGetState cuDevicePrimaryCtxGetState = nullptr;
	PFN_cuDevicePrimaryCtxReset cuDevicePrimaryCtxReset = nullptr;
	PFN_cuCtxCreate cuCtxCreate = nullptr;
	PFN_cuCtxDestroy cuCtxDestroy = nullptr;
	PFN_cuCtxPushCurrent cuCtxPushCurrent = nullptr;
	PFN_cuCtxPopCurrent cuCtxPopCurrent = nullptr;
	PFN_cuCtxSetCurrent cuCtxSetCurrent = nullptr;
	PFN_cuCtxGetCurrent cuCtxGetCurrent = nullptr;
	PFN_cuCtxGetDevice cuCtxGetDevice = nullptr;
	PFN_cuCtxGetFlags cuCtxGetFlags = nullptr;
	PFN_cuCtxSynchronize cuCtxSynchronize = nullptr;
	PFN_cuCtxSetLimit cuCtxSetLimit = nullptr;
	PFN_cuCtxGetLimit cuCtxGetLimit = nullptr;
	PFN_cuCtxGetCacheConfig cuCtxGetCacheConfig = nullptr;
	PFN_cuCtxSetCacheConfig cuCtxSetCacheConfig = nullptr;
	PFN_cuCtxGetSharedMemConfig cuCtxGetSharedMemConfig = nullptr;
	PFN_cuCtxSetSharedMemConfig cuCtxSetSharedMemConfig = nullptr;
	PFN_cuCtxGetApiVersion cuCtxGetApiVersion = nullptr;
	PFN_cuCtxGetStreamPriorityRange cuCtxGetStreamPriorityRange = nullptr;
	PFN_cuModuleLoad cuModuleLoad = nullptr;
	PFN_cuModuleLoadData cuModuleLoadData = nullptr;
	PFN_cuModuleLoadDataEx cuModuleLoadDataEx = nullptr;
	PFN_cuModuleLoadFatBinary cuModuleLoadFatBinary = nullptr;
	PFN_cuModuleUnload cuModuleUnload = nullptr;
	PFN_cuModuleGetFunction cuModuleGetFunction = nullptr;
	PFN_cuModuleGetGlobal cuModuleGetGlobal = nullptr;
	PFN_cuModuleGetTexRef cuModuleGetTexRef = nullptr;
	PFN_cuModuleGetSurfRef cuModuleGetSurfRef = nullptr;
	PFN_cuLinkCreate cuLinkCreate = nullptr;
	PFN_cuLinkAddData cuLinkAddData = nullptr;
	PFN_cuLinkAddFile cuLinkAddFile = nullptr;
	PFN_cuLinkComplete cuLinkComplete = nullptr;
	PFN_cuLinkDestroy cuLinkDestroy = nullptr;
	PFN_cuMemGetInfo cuMemGetInfo = nullptr;
	PFN_cuMemAlloc cuMemAlloc = nullptr;
	PFN_cuMemAllocPitch cuMemAllocPitch = nullptr;
	PFN_cuMemFree cuMemFree = nullptr;
	PFN_cuMemGetAddressRange cuMemGetAddressRange = nullptr;
	PFN_cuMemAllocHost cuMemAllocHost = nullptr;
	PFN_cuMemFreeHost cuMemFreeHost = nullptr;
	PFN_cuMemHostAlloc cuMemHostAlloc = nullptr;
	PFN_cuMemHostGetDevicePointer cuMemHostGetDevicePointer = nullptr;
	PFN_cuMemHostGetFlags cuMemHostGetFlags = nullptr;
	PFN_cuMemAllocManaged cuMemAllocManaged = nullptr;
	PFN_cuDeviceGetByPCIBusId cuDeviceGetByPCIBusId = nullptr;
	PFN_cuDeviceGetPCIBusId cuDeviceGetPCIBusId = nullptr;
	PFN_cuIpcGetEventHandle cuIpcGetEventHandle = nullptr;
	PFN_cuIpcOpenEventHandle cuIpcOpenEventHandle = nullptr;
	PFN_cuIpcGetMemHandle cuIpcGetMemHandle = nullptr;
	PFN_cuIpcOpenMemHandle cuIpcOpenMemHandle = nullptr;
	PFN_cuIpcCloseMemHandle cuIpcCloseMemHandle = nullptr;
	PFN_cuMemHostRegister cuMemHostRegister = nullptr;
	PFN_cuMemHostUnregister cuMemHostUnregister = nullptr;
	PFN_cuMemcpy cuMemcpy = nullptr;
	PFN_cuMemcpyPeer cuMemcpyPeer = nullptr;
	PFN_cuMemcpyHtoD cuMemcpyHtoD = nullptr;
	PFN_cuMemcpyDtoH cuMemcpyDtoH = nullptr;
	PFN_cuMemcpyDtoD cuMemcpyDtoD = nullptr;
	PFN_cuMemcpyDtoA cuMemcpyDtoA = nullptr;
	PFN_cuMemcpyAtoD cuMemcpyAtoD = nullptr;
	PFN_cuMemcpyHtoA cuMemcpyHtoA = nullptr;
	PFN_cuMemcpyAtoH cuMemcpyAtoH = nullptr;
	PFN_cuMemcpyAtoA cuMemcpyAtoA = nullptr;
	PFN_cuMemcpy2D cuMemcpy2D = nullptr;
	PFN_cuMemcpy2DUnaligned cuMemcpy2DUnaligned = nullptr;
	PFN_cuMemcpy3D cuMemcpy3D = nullptr;
	PFN_cuMemcpy3DPeer cuMemcpy3DPeer = nullptr;
	PFN_cuMemcpyAsync cuMemcpyAsync = nullptr;
	PFN_cuMemcpyPeerAsync cuMemcpyPeerAsync = nullptr;
	PFN_cuMemcpyHtoDAsync cuMemcpyHtoDAsync = nullptr;
	PFN_cuMemcpyDtoHAsync cuMemcpyDtoHAsync = nullptr;
	PFN_cuMemcpyDtoDAsync cuMemcpyDtoDAsync = nullptr;
	PFN_cuMemcpyHtoAAsync cuMemcpyHtoAAsync = nullptr;
	PFN_cuMemcpyAtoHAsync cuMemcpyAtoHAsync = nullptr;
	PFN_cuMemcpy2DAsync cuMemcpy2DAsync = nullptr;
	PFN_cuMemcpy3DAsync cuMemcpy3DAsync = nullptr;
	PFN_cuMemcpy3DPeerAsync cuMemcpy3DPeerAsync = nullptr;
	PFN_cuMemsetD8 cuMemsetD8 = nullptr;
	PFN_cuMemsetD16 cuMemsetD16 = nullptr;
	PFN_cuMemsetD32 cuMemsetD32 = nullptr;
	PFN_cuMemsetD2D8 cuMemsetD2D8 = nullptr;
	PFN_cuMemsetD2D16 cuMemsetD2D16 = nullptr;
	PFN_cuMemsetD2D32 cuMemsetD2D32 = nullptr;
	PFN_cuMemsetD8Async cuMemsetD8Async = nullptr;
	PFN_cuMemsetD16Async cuMemsetD16Async = nullptr;
	PFN_cuMemsetD32Async cuMemsetD32Async = nullptr;
	PFN_cuMemsetD2D8Async cuMemsetD2D8Async = nullptr;
	PFN_cuMemsetD2D16Async cuMemsetD2D16Async = nullptr;
	PFN_cuMemsetD2D32Async cuMemsetD2D32Async = nullptr;
	PFN_cuArrayCreate cuArrayCreate = nullptr;
	PFN_cuArrayGetDescriptor cuArrayGetDescriptor = nullptr;
	PFN_cuArrayDestroy cuArrayDestroy = nullptr;
	PFN_cuArray3DCreate cuArray3DCreate = nullptr;
	PFN_cuArray3DGetDescriptor cuArray3DGetDescriptor = nullptr;
	PFN_cuMipmappedArrayCreate cuMipmappedArrayCreate = nullptr;
	PFN_cuMipmappedArrayGetLevel cuMipmappedArrayGetLevel = nullptr;
	PFN_cuMipmappedArrayDestroy cuMipmappedArrayDestroy = nullptr;
	PFN_cuPointerGetAttribute cuPointerGetAttribute = nullptr;
	PFN_cuMemPrefetchAsync cuMemPrefetchAsync = nullptr;
	PFN_cuMemAdvise cuMemAdvise = nullptr;
	PFN_cuMemRangeGetAttribute cuMemRangeGetAttribute = nullptr;
	PFN_cuMemRangeGetAttributes cuMemRangeGetAttributes = nullptr;
	PFN_cuPointerSetAttribute cuPointerSetAttribute = nullptr;
	PFN_cuPointerGetAttributes cuPointerGetAttributes = nullptr;
	PFN_cuStreamCreate cuStreamCreate = nullptr;
	PFN_cuStreamCreateWithPriority cuStreamCreateWithPriority = nullptr;
	PFN_cuStreamGetPriority cuStreamGetPriority = nullptr;
	PFN_cuStreamGetFlags cuStreamGetFlags = nullptr;
	PFN_cuStreamGetCtx cuStreamGetCtx = nullptr;
	PFN_cuStreamWaitEvent cuStreamWaitEvent = nullptr;
	PFN_cuStreamAddCallback cuStreamAddCallback = nullptr;
	PFN_cuStreamBeginCapture cuStreamBeginCapture = nullptr;
	PFN_cuStreamEndCapture cuStreamEndCapture = nullptr;
	PFN_cuStreamIsCapturing cuStreamIsCapturing = nullptr;
	PFN_cuStreamAttachMemAsync cuStreamAttachMemAsync = nullptr;
	PFN_cuStreamQuery cuStreamQuery = nullptr;
	PFN_cuStreamSynchronize cuStreamSynchronize = nullptr;
	PFN_cuStreamDestroy cuStreamDestroy = nullptr;
	PFN_cuEventCreate cuEventCreate = nullptr;
	PFN_cuEventRecord cuEventRecord = nullptr;
	PFN_cuEventQuery cuEventQuery = nullptr;
	PFN_cuEventSynchronize cuEventSynchronize = nullptr;
	PFN_cuEventDestroy cuEventDestroy = nullptr;
	PFN_cuEventElapsedTime cuEventElapsedTime = nullptr;
	PFN_cuImportExternalMemory cuImportExternalMemory = nullptr;
	PFN_cuExternalMemoryGetMappedBuffer cuExternalMemoryGetMappedBuffer = nullptr;
	PFN_cuExternalMemoryGetMappedMipmappedArray cuExternalMemoryGetMappedMipmappedArray = nullptr;
	PFN_cuDestroyExternalMemory cuDestroyExternalMemory = nullptr;
	PFN_cuImportExternalSemaphore cuImportExternalSemaphore = nullptr;
	PFN_cuSignalExternalSemaphoresAsync cuSignalExternalSemaphoresAsync = nullptr;
	PFN_cuWaitExternalSemaphoresAsync cuWaitExternalSemaphoresAsync = nullptr;
	PFN_cuDestroyExternalSemaphore cuDestroyExternalSemaphore = nullptr;
	PFN_cuStreamWaitValue32 cuStreamWaitValue32 = nullptr;
	PFN_cuStreamWaitValue64 cuStreamWaitValue64 = nullptr;
	PFN_cuStreamWriteValue32 cuStreamWriteValue32 = nullptr;
	PFN_cuStreamWriteValue64 cuStreamWriteValue64 = nullptr;
	PFN_cuStreamBatchMemOp cuStreamBatchMemOp = nullptr;
	PFN_cuFuncGetAttribute cuFuncGetAttribute = nullptr;
	PFN_cuFuncSetAttribute cuFuncSetAttribute = nullptr;
	PFN_cuFuncSetCacheConfig cuFuncSetCacheConfig = nullptr;
	PFN_cuFuncSetSharedMemConfig cuFuncSetSharedMemConfig = nullptr;
	PFN_cuLaunchKernel cuLaunchKernel = nullptr;
	PFN_cuLaunchCooperativeKernel cuLaunchCooperativeKernel = nullptr;
	PFN_cuLaunchCooperativeKernelMultiDevice cuLaunchCooperativeKernelMultiDevice = nullptr;
	PFN_cuLaunchHostFunc cuLaunchHostFunc = nullptr;
	PFN_cuGraphCreate cuGraphCreate = nullptr;
	PFN_cuGraphAddKernelNode cuGraphAddKernelNode = nullptr;
	PFN_cuGraphKernelNodeGetParams cuGraphKernelNodeGetParams = nullptr;
	PFN_cuGraphKernelNodeSetParams cuGraphKernelNodeSetParams = nullptr;
	PFN_cuGraphAddMemcpyNode cuGraphAddMemcpyNode = nullptr;
	PFN_cuGraphMemcpyNodeGetParams cuGraphMemcpyNodeGetParams = nullptr;
	PFN_cuGraphMemcpyNodeSetParams cuGraphMemcpyNodeSetParams = nullptr;
	PFN_cuGraphAddMemsetNode cuGraphAddMemsetNode = nullptr;
	PFN_cuGraphMemsetNodeGetParams cuGraphMemsetNodeGetParams = nullptr;
	PFN_cuGraphMemsetNodeSetParams cuGraphMemsetNodeSetParams = nullptr;
	PFN_cuGraphAddHostNode cuGraphAddHostNode = nullptr;
	PFN_cuGraphHostNodeGetParams cuGraphHostNodeGetParams = nullptr;
	PFN_cuGraphHostNodeSetParams cuGraphHostNodeSetParams = nullptr;
	PFN_cuGraphAddChildGraphNode cuGraphAddChildGraphNode = nullptr;
	PFN_cuGraphChildGraphNodeGetGraph cuGraphChildGraphNodeGetGraph = nullptr;
	PFN_cuGraphAddEmptyNode cuGraphAddEmptyNode = nullptr;
	PFN_cuGraphClone cuGraphClone = nullptr;
	PFN_cuGraphNodeFindInClone cuGraphNodeFindInClone = nullptr;
	PFN_cuGraphNodeGetType cuGraphNodeGetType = nullptr;
	PFN_cuGraphGetNodes cuGraphGetNodes = nullptr;
	PFN_cuGraphGetRootNodes cuGraphGetRootNodes = nullptr;
	PFN_cuGraphGetEdges cuGraphGetEdges = nullptr;
	PFN_cuGraphNodeGetDependencies cuGraphNodeGetDependencies = nullptr;
	PFN_cuGraphNodeGetDependentNodes cuGraphNodeGetDependentNodes = nullptr;
	PFN_cuGraphAddDependencies cuGraphAddDependencies = nullptr;
	PFN_cuGraphRemoveDependencies cuGraphRemoveDependencies = nullptr;
	PFN_cuGraphDestroyNode cuGraphDestroyNode = nullptr;
	PFN_cuGraphInstantiate cuGraphInstantiate = nullptr;
	PFN_cuGraphLaunch cuGraphLaunch = nullptr;
	PFN_cuGraphExecDestroy cuGraphExecDestroy = nullptr;
	PFN_cuGraphDestroy cuGraphDestroy = nullptr;
	PFN_cuOccupancyMaxActiveBlocksPerMultiprocessor cuOccupancyMaxActiveBlocksPerMultiprocessor = nullptr;
	PFN_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags = nullptr;
	PFN_cuOccupancyMaxPotentialBlockSize cuOccupancyMaxPotentialBlockSize = nullptr;
	PFN_cuOccupancyMaxPotentialBlockSizeWithFlags cuOccupancyMaxPotentialBlockSizeWithFlags = nullptr;
	PFN_cuTexRefSetArray cuTexRefSetArray = nullptr;
	PFN_cuTexRefSetMipmappedArray cuTexRefSetMipmappedArray = nullptr;
	PFN_cuTexRefSetAddress cuTexRefSetAddress = nullptr;
	PFN_cuTexRefSetAddress2D cuTexRefSetAddress2D = nullptr;
	PFN_cuTexRefSetFormat cuTexRefSetFormat = nullptr;
	PFN_cuTexRefSetAddressMode cuTexRefSetAddressMode = nullptr;
	PFN_cuTexRefSetFilterMode cuTexRefSetFilterMode = nullptr;
	PFN_cuTexRefSetMipmapFilterMode cuTexRefSetMipmapFilterMode = nullptr;
	PFN_cuTexRefSetMipmapLevelBias cuTexRefSetMipmapLevelBias = nullptr;
	PFN_cuTexRefSetMipmapLevelClamp cuTexRefSetMipmapLevelClamp = nullptr;
	PFN_cuTexRefSetMaxAnisotropy cuTexRefSetMaxAnisotropy = nullptr;
	PFN_cuTexRefSetBorderColor cuTexRefSetBorderColor = nullptr;
	PFN_cuTexRefSetFlags cuTexRefSetFlags = nullptr;
	PFN_cuTexRefGetAddress cuTexRefGetAddress = nullptr;
	PFN_cuTexRefGetArray cuTexRefGetArray = nullptr;
	PFN_cuTexRefGetMipmappedArray cuTexRefGetMipmappedArray = nullptr;
	PFN_cuTexRefGetAddressMode cuTexRefGetAddressMode = nullptr;
	PFN_cuTexRefGetFilterMode cuTexRefGetFilterMode = nullptr;
	PFN_cuTexRefGetFormat cuTexRefGetFormat = nullptr;
	PFN_cuTexRefGetMipmapFilterMode cuTexRefGetMipmapFilterMode = nullptr;
	PFN_cuTexRefGetMipmapLevelBias cuTexRefGetMipmapLevelBias = nullptr;
	PFN_cuTexRefGetMipmapLevelClamp cuTexRefGetMipmapLevelClamp = nullptr;
	PFN_cuTexRefGetMaxAnisotropy cuTexRefGetMaxAnisotropy = nullptr;
	PFN_cuTexRefGetBorderColor cuTexRefGetBorderColor = nullptr;
	PFN_cuTexRefGetFlags cuTexRefGetFlags = nullptr;
	PFN_cuSurfRefSetArray cuSurfRefSetArray = nullptr;
	PFN_cuSurfRefGetArray cuSurfRefGetArray = nullptr;
	PFN_cuTexObjectCreate cuTexObjectCreate = nullptr;
	PFN_cuTexObjectDestroy cuTexObjectDestroy = nullptr;
	PFN_cuTexObjectGetResourceDesc cuTexObjectGetResourceDesc = nullptr;
	PFN_cuTexObjectGetTextureDesc cuTexObjectGetTextureDesc = nullptr;
	PFN_cuTexObjectGetResourceViewDesc cuTexObjectGetResourceViewDesc = nullptr;
	PFN_cuSurfObjectCreate cuSurfObjectCreate = nullptr;
	PFN_cuSurfObjectDestroy cuSurfObjectDestroy = nullptr;
	PFN_cuSurfObjectGetResourceDesc cuSurfObjectGetResourceDesc = nullptr;
	PFN_cuDeviceCanAccessPeer cuDeviceCanAccessPeer = nullptr;
	PFN_cuCtxEnablePeerAccess cuCtxEnablePeerAccess = nullptr;
	PFN_cuCtxDisablePeerAccess cuCtxDisablePeerAccess = nullptr;
	PFN_cuDeviceGetP2PAttribute cuDeviceGetP2PAttribute = nullptr;
	PFN_cuGraphicsUnregisterResource cuGraphicsUnregisterResource = nullptr;
	PFN_cuGraphicsSubResourceGetMappedArray cuGraphicsSubResourceGetMappedArray = nullptr;
	PFN_cuGraphicsResourceGetMappedMipmappedArray cuGraphicsResourceGetMappedMipmappedArray = nullptr;
	PFN_cuGraphicsResourceGetMappedPointer cuGraphicsResourceGetMappedPointer = nullptr;
	PFN_cuGraphicsResourceSetMapFlags cuGraphicsResourceSetMapFlags = nullptr;
	PFN_cuGraphicsMapResources cuGraphicsMapResources = nullptr;
	PFN_cuGraphicsUnmapResources cuGraphicsUnmapResources = nullptr;
	PFN_cuGetExportTable cuGetExportTable = nullptr;
}

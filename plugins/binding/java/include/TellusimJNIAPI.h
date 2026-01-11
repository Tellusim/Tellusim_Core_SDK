// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_JNI_API_H__
#define __TELLUSIM_JNI_API_H__

#include <TellusimApp.h>
#include <TellusimFormat.h>
#include <core/TellusimCore.h>
#include <core/TellusimSystem.h>
#include <core/TellusimDirectory.h>
#include <math/TellusimMath.h>
#include <format/TellusimFormats.h>
#include <platform/TellusimPlatforms.h>
#include <interface/TellusimFont.h>
#include <interface/TellusimControls.h>
#include <interface/TellusimDialogs.h>
#include <geometry/TellusimGeometry.h>
#include <graphics/TellusimGraphics.h>
#include <parallel/TellusimParallels.h>
#include <system/TellusimController.h>
#include <system/TellusimDesktop.h>

#include "TellusimJNIBase.h"

/*
 */
namespace Tellusim {
	
	/// Tellusim Interfaces
	#define newString(...) (jlong)(new String(__VA_ARGS__))
	#define newApp(...) (jlong)(new App(__VA_ARGS__))
	#define newAsync(...) (jlong)(new Async(__VA_ARGS__))
	#define newStream(...) (jlong)(new Stream(__VA_ARGS__))
	#define newBlob(...) (jlong)(new Blob(__VA_ARGS__))
	#define newFile(...) (jlong)(new File(__VA_ARGS__))
	#define newSocket(...) (jlong)(new Socket(__VA_ARGS__))
	#define newSocketSSL(...) (jlong)(new SocketSSL(__VA_ARGS__))
	#define newSource(...) (jlong)(new Source(__VA_ARGS__))
	#define newDate(...) (jlong)(new Date(__VA_ARGS__))
	#define newInfo(...) (jlong)(new Info(__VA_ARGS__))
	#define newDirectory(...) (jlong)(new Directory(__VA_ARGS__))
	#define newArchive(...) (jlong)(new Archive(__VA_ARGS__))
	#define newImage(...) (jlong)(new Image(__VA_ARGS__))
	#define newImageSampler(...) (jlong)(new ImageSampler(__VA_ARGS__))
	#define newMeshNode(...) (jlong)(new MeshNode(__VA_ARGS__))
	#define newMeshIndices(...) (jlong)(new MeshIndices(__VA_ARGS__))
	#define newMeshAttribute(...) (jlong)(new MeshAttribute(__VA_ARGS__))
	#define newMeshJoint(...) (jlong)(new MeshJoint(__VA_ARGS__))
	#define newMeshMaterial(...) (jlong)(new MeshMaterial(__VA_ARGS__))
	#define newMeshGeometry(...) (jlong)(new MeshGeometry(__VA_ARGS__))
	#define newMeshTransform(...) (jlong)(new MeshTransform(__VA_ARGS__))
	#define newMeshAnimation(...) (jlong)(new MeshAnimation(__VA_ARGS__))
	#define newMeshAttachment(...) (jlong)(new MeshAttachment(__VA_ARGS__))
	#define newMesh(...) (jlong)(new Mesh(__VA_ARGS__))
	#define newJson(...) (jlong)(new Json(__VA_ARGS__))
	#define newXml(...) (jlong)(new Xml(__VA_ARGS__))
	#define newBuffer(...) (jlong)(new Buffer(__VA_ARGS__))
	#define newBufferTable(...) (jlong)(new BufferTable(__VA_ARGS__))
	#define newD3D12Buffer(...) (jlong)(new D3D12Buffer(__VA_ARGS__))
	#define newD3D11Buffer(...) (jlong)(new D3D11Buffer(__VA_ARGS__))
	#define newMTLBuffer(...) (jlong)(new MTLBuffer(__VA_ARGS__))
	#define newVKBuffer(...) (jlong)(new VKBuffer(__VA_ARGS__))
	#define newGLBuffer(...) (jlong)(new GLBuffer(__VA_ARGS__))
	#define newGLESBuffer(...) (jlong)(new GLESBuffer(__VA_ARGS__))
	#define newCUBuffer(...) (jlong)(new CUBuffer(__VA_ARGS__))
	#define newHIPBuffer(...) (jlong)(new HIPBuffer(__VA_ARGS__))
	#define newFUBuffer(...) (jlong)(new FUBuffer(__VA_ARGS__))
	#define newCommand(...) (jlong)(new Command(__VA_ARGS__))
	#define newCommandDrawArraysIndirect(...) (jlong)(new Command::DrawArraysIndirect(__VA_ARGS__))
	#define newCommandDrawElementsIndirect(...) (jlong)(new Command::DrawElementsIndirect(__VA_ARGS__))
	#define newCommandDrawMeshIndirect(...) (jlong)(new Command::DrawMeshIndirect(__VA_ARGS__))
	#define newD3D12Command(...) (jlong)(new D3D12Command(__VA_ARGS__))
	#define newMTLCommand(...) (jlong)(new MTLCommand(__VA_ARGS__))
	#define newVKCommand(...) (jlong)(new VKCommand(__VA_ARGS__))
	#define newFUCommand(...) (jlong)(new FUCommand(__VA_ARGS__))
	#define newCompute(...) (jlong)(new Compute(__VA_ARGS__))
	#define newComputeDispatchIndirect(...) (jlong)(new Compute::DispatchIndirect(__VA_ARGS__))
	#define newD3D12Compute(...) (jlong)(new D3D12Compute(__VA_ARGS__))
	#define newMTLCompute(...) (jlong)(new MTLCompute(__VA_ARGS__))
	#define newVKCompute(...) (jlong)(new VKCompute(__VA_ARGS__))
	#define newFUCompute(...) (jlong)(new FUCompute(__VA_ARGS__))
	#define newContext(...) (jlong)(new Context(__VA_ARGS__))
	#define newD3D12Context(...) (jlong)(new D3D12Context(__VA_ARGS__))
	#define newD3D11Context(...) (jlong)(new D3D11Context(__VA_ARGS__))
	#define newMTLContext(...) (jlong)(new MTLContext(__VA_ARGS__))
	#define newVKContext(...) (jlong)(new VKContext(__VA_ARGS__))
	#define newGLContext(...) (jlong)(new GLContext(__VA_ARGS__))
	#define newGLESContext(...) (jlong)(new GLESContext(__VA_ARGS__))
	#define newWGContext(...) (jlong)(new WGContext(__VA_ARGS__))
	#define newCUContext(...) (jlong)(new CUContext(__VA_ARGS__))
	#define newHIPContext(...) (jlong)(new HIPContext(__VA_ARGS__))
	#define newQuery(...) (jlong)(new Query(__VA_ARGS__))
	#define newQueryStatistics(...) (jlong)(new Query::Statistics(__VA_ARGS__))
	#define newFUQuery(...) (jlong)(new FUQuery(__VA_ARGS__))
	#define newFence(...) (jlong)(new Fence(__VA_ARGS__))
	#define newVKFence(...) (jlong)(new VKFence(__VA_ARGS__))
	#define newFUFence(...) (jlong)(new FUFence(__VA_ARGS__))
	#define newShader(...) (jlong)(new Shader(__VA_ARGS__))
	#define newShaderCompiler(...) (jlong)(new ShaderCompiler(__VA_ARGS__))
	#define newD3D12Shader(...) (jlong)(new D3D12Shader(__VA_ARGS__))
	#define newD3D11Shader(...) (jlong)(new D3D11Shader(__VA_ARGS__))
	#define newMTLShader(...) (jlong)(new MTLShader(__VA_ARGS__))
	#define newVKShader(...) (jlong)(new VKShader(__VA_ARGS__))
	#define newGLShader(...) (jlong)(new GLShader(__VA_ARGS__))
	#define newGLESShader(...) (jlong)(new GLESShader(__VA_ARGS__))
	#define newCUShader(...) (jlong)(new CUShader(__VA_ARGS__))
	#define newHIPShader(...) (jlong)(new HIPShader(__VA_ARGS__))
	#define newFUShader(...) (jlong)(new FUShader(__VA_ARGS__))
	#define newSampler(...) (jlong)(new Sampler(__VA_ARGS__))
	#define newMTLSampler(...) (jlong)(new MTLSampler(__VA_ARGS__))
	#define newFUSampler(...) (jlong)(new FUSampler(__VA_ARGS__))
	#define newTexture(...) (jlong)(new Texture(__VA_ARGS__))
	#define newTextureTable(...) (jlong)(new TextureTable(__VA_ARGS__))
	#define newD3D12Texture(...) (jlong)(new D3D12Texture(__VA_ARGS__))
	#define newD3D11Texture(...) (jlong)(new D3D11Texture(__VA_ARGS__))
	#define newMTLTexture(...) (jlong)(new MTLTexture(__VA_ARGS__))
	#define newVKTexture(...) (jlong)(new VKTexture(__VA_ARGS__))
	#define newGLTexture(...) (jlong)(new GLTexture(__VA_ARGS__))
	#define newGLESTexture(...) (jlong)(new GLESTexture(__VA_ARGS__))
	#define newCUTexture(...) (jlong)(new CUTexture(__VA_ARGS__))
	#define newHIPTexture(...) (jlong)(new HIPTexture(__VA_ARGS__))
	#define newFUTexture(...) (jlong)(new FUTexture(__VA_ARGS__))
	#define newTracing(...) (jlong)(new Tracing(__VA_ARGS__))
	#define newTracingInstance(...) (jlong)(new Tracing::Instance(__VA_ARGS__))
	#define newTracingBuildIndirect(...) (jlong)(new Tracing::BuildIndirect(__VA_ARGS__))
	#define newD3D12Tracing(...) (jlong)(new D3D12Tracing(__VA_ARGS__))
	#define newMTLTracing(...) (jlong)(new MTLTracing(__VA_ARGS__))
	#define newVKTracing(...) (jlong)(new VKTracing(__VA_ARGS__))
	#define newFUTracing(...) (jlong)(new FUTracing(__VA_ARGS__))
	#define newTarget(...) (jlong)(new Target(__VA_ARGS__))
	#define newD3D12Target(...) (jlong)(new D3D12Target(__VA_ARGS__))
	#define newD3D11Target(...) (jlong)(new D3D11Target(__VA_ARGS__))
	#define newMTLTarget(...) (jlong)(new MTLTarget(__VA_ARGS__))
	#define newVKTarget(...) (jlong)(new VKTarget(__VA_ARGS__))
	#define newGLTarget(...) (jlong)(new GLTarget(__VA_ARGS__))
	#define newGLESTarget(...) (jlong)(new GLESTarget(__VA_ARGS__))
	#define newFUTarget(...) (jlong)(new FUTarget(__VA_ARGS__))
	#define newDevice(...) (jlong)(new Device(__VA_ARGS__))
	#define newDeviceFeatures(...) (jlong)(new Device::Features(__VA_ARGS__))
	#define newD3D12Device(...) (jlong)(new D3D12Device(__VA_ARGS__))
	#define newD3D11Device(...) (jlong)(new D3D11Device(__VA_ARGS__))
	#define newMTLDevice(...) (jlong)(new MTLDevice(__VA_ARGS__))
	#define newVKDevice(...) (jlong)(new VKDevice(__VA_ARGS__))
	#define newFUDevice(...) (jlong)(new FUDevice(__VA_ARGS__))
	#define newKernel(...) (jlong)(new Kernel(__VA_ARGS__))
	#define newD3D12Kernel(...) (jlong)(new D3D12Kernel(__VA_ARGS__))
	#define newMTLKernel(...) (jlong)(new MTLKernel(__VA_ARGS__))
	#define newFUKernel(...) (jlong)(new FUKernel(__VA_ARGS__))
	#define newPipeline(...) (jlong)(new Pipeline(__VA_ARGS__))
	#define newD3D12Pipeline(...) (jlong)(new D3D12Pipeline(__VA_ARGS__))
	#define newMTLPipeline(...) (jlong)(new MTLPipeline(__VA_ARGS__))
	#define newFUPipeline(...) (jlong)(new FUPipeline(__VA_ARGS__))
	#define newTraversal(...) (jlong)(new Traversal(__VA_ARGS__))
	#define newD3D12Traversal(...) (jlong)(new D3D12Traversal(__VA_ARGS__))
	#define newFUTraversal(...) (jlong)(new FUTraversal(__VA_ARGS__))
	#define newSurface(...) (jlong)(new Surface(__VA_ARGS__))
	#define newD3D12Surface(...) (jlong)(new D3D12Surface(__VA_ARGS__))
	#define newD3D11Surface(...) (jlong)(new D3D11Surface(__VA_ARGS__))
	#define newMTLSurface(...) (jlong)(new MTLSurface(__VA_ARGS__))
	#define newVKSurface(...) (jlong)(new VKSurface(__VA_ARGS__))
	#define newGLSurface(...) (jlong)(new GLSurface(__VA_ARGS__))
	#define newGLESSurface(...) (jlong)(new GLESSurface(__VA_ARGS__))
	#define newWindow(...) (jlong)(new Window(__VA_ARGS__))
	#define newFont(...) (jlong)(new Font(__VA_ARGS__))
	#define newCanvasElement(...) (jlong)(new CanvasElement(__VA_ARGS__))
	#define newCanvasText(...) (jlong)(new CanvasText(__VA_ARGS__))
	#define newCanvasMesh(...) (jlong)(new CanvasMesh(__VA_ARGS__))
	#define newCanvasRect(...) (jlong)(new CanvasRect(__VA_ARGS__))
	#define newCanvasTriangle(...) (jlong)(new CanvasTriangle(__VA_ARGS__))
	#define newCanvasEllipse(...) (jlong)(new CanvasEllipse(__VA_ARGS__))
	#define newCanvasShape(...) (jlong)(new CanvasShape(__VA_ARGS__))
	#define newCanvasStrip(...) (jlong)(new CanvasStrip(__VA_ARGS__))
	#define newCanvas(...) (jlong)(new Canvas(__VA_ARGS__))
	#define newControl(...) (jlong)(new Control(__VA_ARGS__))
	#define newControlRoot(...) (jlong)(new ControlRoot(__VA_ARGS__))
	#define newControlText(...) (jlong)(new ControlText(__VA_ARGS__))
	#define newControlRect(...) (jlong)(new ControlRect(__VA_ARGS__))
	#define newControlGrid(...) (jlong)(new ControlGrid(__VA_ARGS__))
	#define newControlGroup(...) (jlong)(new ControlGroup(__VA_ARGS__))
	#define newControlPanel(...) (jlong)(new ControlPanel(__VA_ARGS__))
	#define newControlDialog(...) (jlong)(new ControlDialog(__VA_ARGS__))
	#define newControlWindow(...) (jlong)(new ControlWindow(__VA_ARGS__))
	#define newControlCheck(...) (jlong)(new ControlCheck(__VA_ARGS__))
	#define newControlCombo(...) (jlong)(new ControlCombo(__VA_ARGS__))
	#define newControlButton(...) (jlong)(new ControlButton(__VA_ARGS__))
	#define newControlSlider(...) (jlong)(new ControlSlider(__VA_ARGS__))
	#define newControlScroll(...) (jlong)(new ControlScroll(__VA_ARGS__))
	#define newControlSplit(...) (jlong)(new ControlSplit(__VA_ARGS__))
	#define newControlArea(...) (jlong)(new ControlArea(__VA_ARGS__))
	#define newControlTree(...) (jlong)(new ControlTree(__VA_ARGS__))
	#define newControlEdit(...) (jlong)(new ControlEdit(__VA_ARGS__))
	#define newDialogMessage(...) (jlong)(new DialogMessage(__VA_ARGS__))
	#define newDialogFileOpen(...) (jlong)(new DialogFileOpen(__VA_ARGS__))
	#define newDialogFileSave(...) (jlong)(new DialogFileSave(__VA_ARGS__))
	#define newDialogDirectory(...) (jlong)(new DialogDirectory(__VA_ARGS__))
	#define newDialogProgress(...) (jlong)(new DialogProgress(__VA_ARGS__))
	#define newDialogColor(...) (jlong)(new DialogColor(__VA_ARGS__))
	#define newDialogMenu(...) (jlong)(new DialogMenu(__VA_ARGS__))
	#define newCubeFilter(...) (jlong)(new CubeFilter(__VA_ARGS__))
	#define newDecoderJPEG(...) (jlong)(new DecoderJPEG(__VA_ARGS__))
	#define newEncoderBC15(...) (jlong)(new EncoderBC15(__VA_ARGS__))
	#define newEncoderBC67(...) (jlong)(new EncoderBC67(__VA_ARGS__))
	#define newEncoderASTC(...) (jlong)(new EncoderASTC(__VA_ARGS__))
	#define newMeshModel(...) (jlong)(new MeshModel(__VA_ARGS__))
	#define newMeshModelMeshlet(...) (jlong)(new MeshModel::Meshlet(__VA_ARGS__))
	#define newSeparableFilter(...) (jlong)(new SeparableFilter(__VA_ARGS__))
	#define newPrefixScan(...) (jlong)(new PrefixScan(__VA_ARGS__))
	#define newPrefixScanDispatchParameters(...) (jlong)(new PrefixScan::DispatchParameters(__VA_ARGS__))
	#define newRadixSort(...) (jlong)(new RadixSort(__VA_ARGS__))
	#define newRadixSortDispatchParameters(...) (jlong)(new RadixSort::DispatchParameters(__VA_ARGS__))
	#define newBitonicSort(...) (jlong)(new BitonicSort(__VA_ARGS__))
	#define newBitonicSortDispatchParameters(...) (jlong)(new BitonicSort::DispatchParameters(__VA_ARGS__))
	#define newSpatialGrid(...) (jlong)(new SpatialGrid(__VA_ARGS__))
	#define newSpatialGridDispatchParameters(...) (jlong)(new SpatialGrid::DispatchParameters(__VA_ARGS__))
	#define newSpatialTree(...) (jlong)(new SpatialTree(__VA_ARGS__))
	#define newSpatialTreeNode(...) (jlong)(new SpatialTree::Node(__VA_ARGS__))
	#define newSpatialTreeLeafNodef16(...) (jlong)(new SpatialTree::LeafNodef16(__VA_ARGS__))
	#define newSpatialTreeDispatchParameters(...) (jlong)(new SpatialTree::DispatchParameters(__VA_ARGS__))
	#define newFourierTransform(...) (jlong)(new FourierTransform(__VA_ARGS__))
	#define newTensorGraph(...) (jlong)(new TensorGraph(__VA_ARGS__))
	#define newController(...) (jlong)(new Controller(__VA_ARGS__))
	#define newDesktop(...) (jlong)(new Desktop(__VA_ARGS__))
	
	/// Interfaces
	TS_INLINE String &toString(jlong self) { return *(String*)self; }
	TS_INLINE App &toApp(jlong self) { return *(App*)self; }
	TS_INLINE Async &toAsync(jlong self) { return *(Async*)self; }
	TS_INLINE Async::Task &toAsyncTask(jlong self) { return *(Async::Task*)self; }
	TS_INLINE Stream &toStream(jlong self) { return *(Stream*)self; }
	TS_INLINE Blob &toBlob(jlong self) { return *(Blob*)self; }
	TS_INLINE File &toFile(jlong self) { return *(File*)self; }
	TS_INLINE Socket &toSocket(jlong self) { return *(Socket*)self; }
	TS_INLINE SocketSSL &toSocketSSL(jlong self) { return *(SocketSSL*)self; }
	TS_INLINE Source &toSource(jlong self) { return *(Source*)self; }
	TS_INLINE Date &toDate(jlong self) { return *(Date*)self; }
	TS_INLINE Info &toInfo(jlong self) { return *(Info*)self; }
	TS_INLINE Directory &toDirectory(jlong self) { return *(Directory*)self; }
	TS_INLINE Archive &toArchive(jlong self) { return *(Archive*)self; }
	TS_INLINE Image &toImage(jlong self) { return *(Image*)self; }
	TS_INLINE ImageSampler &toImageSampler(jlong self) { return *(ImageSampler*)self; }
	TS_INLINE MeshNode &toMeshNode(jlong self) { return *(MeshNode*)self; }
	TS_INLINE MeshIndices &toMeshIndices(jlong self) { return *(MeshIndices*)self; }
	TS_INLINE MeshAttribute &toMeshAttribute(jlong self) { return *(MeshAttribute*)self; }
	TS_INLINE MeshJoint &toMeshJoint(jlong self) { return *(MeshJoint*)self; }
	TS_INLINE MeshMaterial &toMeshMaterial(jlong self) { return *(MeshMaterial*)self; }
	TS_INLINE MeshGeometry &toMeshGeometry(jlong self) { return *(MeshGeometry*)self; }
	TS_INLINE MeshTransform &toMeshTransform(jlong self) { return *(MeshTransform*)self; }
	TS_INLINE MeshAnimation &toMeshAnimation(jlong self) { return *(MeshAnimation*)self; }
	TS_INLINE MeshAttachment &toMeshAttachment(jlong self) { return *(MeshAttachment*)self; }
	TS_INLINE Mesh &toMesh(jlong self) { return *(Mesh*)self; }
	TS_INLINE Json &toJson(jlong self) { return *(Json*)self; }
	TS_INLINE Xml &toXml(jlong self) { return *(Xml*)self; }
	TS_INLINE Buffer &toBuffer(jlong self) { return *(Buffer*)self; }
	TS_INLINE BufferTable &toBufferTable(jlong self) { return *(BufferTable*)self; }
	TS_INLINE D3D12Buffer &toD3D12Buffer(jlong self) { return *(D3D12Buffer*)self; }
	TS_INLINE D3D11Buffer &toD3D11Buffer(jlong self) { return *(D3D11Buffer*)self; }
	TS_INLINE MTLBuffer &toMTLBuffer(jlong self) { return *(MTLBuffer*)self; }
	TS_INLINE VKBuffer &toVKBuffer(jlong self) { return *(VKBuffer*)self; }
	TS_INLINE GLBuffer &toGLBuffer(jlong self) { return *(GLBuffer*)self; }
	TS_INLINE GLESBuffer &toGLESBuffer(jlong self) { return *(GLESBuffer*)self; }
	TS_INLINE CUBuffer &toCUBuffer(jlong self) { return *(CUBuffer*)self; }
	TS_INLINE HIPBuffer &toHIPBuffer(jlong self) { return *(HIPBuffer*)self; }
	TS_INLINE FUBuffer &toFUBuffer(jlong self) { return *(FUBuffer*)self; }
	TS_INLINE Command &toCommand(jlong self) { return *(Command*)self; }
	TS_INLINE Command::DrawArraysIndirect &toCommandDrawArraysIndirect(jlong self) { return *(Command::DrawArraysIndirect*)self; }
	TS_INLINE Command::DrawElementsIndirect &toCommandDrawElementsIndirect(jlong self) { return *(Command::DrawElementsIndirect*)self; }
	TS_INLINE Command::DrawMeshIndirect &toCommandDrawMeshIndirect(jlong self) { return *(Command::DrawMeshIndirect*)self; }
	TS_INLINE D3D12Command &toD3D12Command(jlong self) { return *(D3D12Command*)self; }
	TS_INLINE MTLCommand &toMTLCommand(jlong self) { return *(MTLCommand*)self; }
	TS_INLINE VKCommand &toVKCommand(jlong self) { return *(VKCommand*)self; }
	TS_INLINE FUCommand &toFUCommand(jlong self) { return *(FUCommand*)self; }
	TS_INLINE Compute &toCompute(jlong self) { return *(Compute*)self; }
	TS_INLINE Compute::DispatchIndirect &toComputeDispatchIndirect(jlong self) { return *(Compute::DispatchIndirect*)self; }
	TS_INLINE D3D12Compute &toD3D12Compute(jlong self) { return *(D3D12Compute*)self; }
	TS_INLINE MTLCompute &toMTLCompute(jlong self) { return *(MTLCompute*)self; }
	TS_INLINE VKCompute &toVKCompute(jlong self) { return *(VKCompute*)self; }
	TS_INLINE FUCompute &toFUCompute(jlong self) { return *(FUCompute*)self; }
	TS_INLINE Context &toContext(jlong self) { return *(Context*)self; }
	TS_INLINE D3D12Context &toD3D12Context(jlong self) { return *(D3D12Context*)self; }
	TS_INLINE D3D11Context &toD3D11Context(jlong self) { return *(D3D11Context*)self; }
	TS_INLINE MTLContext &toMTLContext(jlong self) { return *(MTLContext*)self; }
	TS_INLINE VKContext &toVKContext(jlong self) { return *(VKContext*)self; }
	TS_INLINE GLContext &toGLContext(jlong self) { return *(GLContext*)self; }
	TS_INLINE GLESContext &toGLESContext(jlong self) { return *(GLESContext*)self; }
	TS_INLINE WGContext &toWGContext(jlong self) { return *(WGContext*)self; }
	TS_INLINE CUContext &toCUContext(jlong self) { return *(CUContext*)self; }
	TS_INLINE HIPContext &toHIPContext(jlong self) { return *(HIPContext*)self; }
	TS_INLINE Query &toQuery(jlong self) { return *(Query*)self; }
	TS_INLINE Query::Statistics &toQueryStatistics(jlong self) { return *(Query::Statistics*)self; }
	TS_INLINE FUQuery &toFUQuery(jlong self) { return *(FUQuery*)self; }
	TS_INLINE Fence &toFence(jlong self) { return *(Fence*)self; }
	TS_INLINE VKFence &toVKFence(jlong self) { return *(VKFence*)self; }
	TS_INLINE FUFence &toFUFence(jlong self) { return *(FUFence*)self; }
	TS_INLINE Shader &toShader(jlong self) { return *(Shader*)self; }
	TS_INLINE ShaderCompiler &toShaderCompiler(jlong self) { return *(ShaderCompiler*)self; }
	TS_INLINE D3D12Shader &toD3D12Shader(jlong self) { return *(D3D12Shader*)self; }
	TS_INLINE D3D11Shader &toD3D11Shader(jlong self) { return *(D3D11Shader*)self; }
	TS_INLINE MTLShader &toMTLShader(jlong self) { return *(MTLShader*)self; }
	TS_INLINE VKShader &toVKShader(jlong self) { return *(VKShader*)self; }
	TS_INLINE GLShader &toGLShader(jlong self) { return *(GLShader*)self; }
	TS_INLINE GLESShader &toGLESShader(jlong self) { return *(GLESShader*)self; }
	TS_INLINE CUShader &toCUShader(jlong self) { return *(CUShader*)self; }
	TS_INLINE HIPShader &toHIPShader(jlong self) { return *(HIPShader*)self; }
	TS_INLINE FUShader &toFUShader(jlong self) { return *(FUShader*)self; }
	TS_INLINE Sampler &toSampler(jlong self) { return *(Sampler*)self; }
	TS_INLINE MTLSampler &toMTLSampler(jlong self) { return *(MTLSampler*)self; }
	TS_INLINE FUSampler &toFUSampler(jlong self) { return *(FUSampler*)self; }
	TS_INLINE Texture &toTexture(jlong self) { return *(Texture*)self; }
	TS_INLINE TextureTable &toTextureTable(jlong self) { return *(TextureTable*)self; }
	TS_INLINE D3D12Texture &toD3D12Texture(jlong self) { return *(D3D12Texture*)self; }
	TS_INLINE D3D11Texture &toD3D11Texture(jlong self) { return *(D3D11Texture*)self; }
	TS_INLINE MTLTexture &toMTLTexture(jlong self) { return *(MTLTexture*)self; }
	TS_INLINE VKTexture &toVKTexture(jlong self) { return *(VKTexture*)self; }
	TS_INLINE GLTexture &toGLTexture(jlong self) { return *(GLTexture*)self; }
	TS_INLINE GLESTexture &toGLESTexture(jlong self) { return *(GLESTexture*)self; }
	TS_INLINE CUTexture &toCUTexture(jlong self) { return *(CUTexture*)self; }
	TS_INLINE HIPTexture &toHIPTexture(jlong self) { return *(HIPTexture*)self; }
	TS_INLINE FUTexture &toFUTexture(jlong self) { return *(FUTexture*)self; }
	TS_INLINE Tracing &toTracing(jlong self) { return *(Tracing*)self; }
	TS_INLINE Tracing::Instance &toTracingInstance(jlong self) { return *(Tracing::Instance*)self; }
	TS_INLINE Tracing::BuildIndirect &toTracingBuildIndirect(jlong self) { return *(Tracing::BuildIndirect*)self; }
	TS_INLINE D3D12Tracing &toD3D12Tracing(jlong self) { return *(D3D12Tracing*)self; }
	TS_INLINE D3D12Tracing::D3D12Instance &toD3D12TracingD3D12Instance(jlong self) { return *(D3D12Tracing::D3D12Instance*)self; }
	TS_INLINE MTLTracing &toMTLTracing(jlong self) { return *(MTLTracing*)self; }
	TS_INLINE MTLTracing::MTLInstance &toMTLTracingMTLInstance(jlong self) { return *(MTLTracing::MTLInstance*)self; }
	TS_INLINE VKTracing &toVKTracing(jlong self) { return *(VKTracing*)self; }
	TS_INLINE VKTracing::VKInstance &toVKTracingVKInstance(jlong self) { return *(VKTracing::VKInstance*)self; }
	TS_INLINE FUTracing &toFUTracing(jlong self) { return *(FUTracing*)self; }
	TS_INLINE Target &toTarget(jlong self) { return *(Target*)self; }
	TS_INLINE D3D12Target &toD3D12Target(jlong self) { return *(D3D12Target*)self; }
	TS_INLINE D3D11Target &toD3D11Target(jlong self) { return *(D3D11Target*)self; }
	TS_INLINE MTLTarget &toMTLTarget(jlong self) { return *(MTLTarget*)self; }
	TS_INLINE VKTarget &toVKTarget(jlong self) { return *(VKTarget*)self; }
	TS_INLINE GLTarget &toGLTarget(jlong self) { return *(GLTarget*)self; }
	TS_INLINE GLESTarget &toGLESTarget(jlong self) { return *(GLESTarget*)self; }
	TS_INLINE FUTarget &toFUTarget(jlong self) { return *(FUTarget*)self; }
	TS_INLINE Device &toDevice(jlong self) { return *(Device*)self; }
	TS_INLINE Device::Features &toDeviceFeatures(jlong self) { return *(Device::Features*)self; }
	TS_INLINE D3D12Device &toD3D12Device(jlong self) { return *(D3D12Device*)self; }
	TS_INLINE D3D11Device &toD3D11Device(jlong self) { return *(D3D11Device*)self; }
	TS_INLINE MTLDevice &toMTLDevice(jlong self) { return *(MTLDevice*)self; }
	TS_INLINE VKDevice &toVKDevice(jlong self) { return *(VKDevice*)self; }
	TS_INLINE FUDevice &toFUDevice(jlong self) { return *(FUDevice*)self; }
	TS_INLINE Kernel &toKernel(jlong self) { return *(Kernel*)self; }
	TS_INLINE D3D12Kernel &toD3D12Kernel(jlong self) { return *(D3D12Kernel*)self; }
	TS_INLINE MTLKernel &toMTLKernel(jlong self) { return *(MTLKernel*)self; }
	TS_INLINE FUKernel &toFUKernel(jlong self) { return *(FUKernel*)self; }
	TS_INLINE Pipeline &toPipeline(jlong self) { return *(Pipeline*)self; }
	TS_INLINE D3D12Pipeline &toD3D12Pipeline(jlong self) { return *(D3D12Pipeline*)self; }
	TS_INLINE MTLPipeline &toMTLPipeline(jlong self) { return *(MTLPipeline*)self; }
	TS_INLINE FUPipeline &toFUPipeline(jlong self) { return *(FUPipeline*)self; }
	TS_INLINE Traversal &toTraversal(jlong self) { return *(Traversal*)self; }
	TS_INLINE D3D12Traversal &toD3D12Traversal(jlong self) { return *(D3D12Traversal*)self; }
	TS_INLINE FUTraversal &toFUTraversal(jlong self) { return *(FUTraversal*)self; }
	TS_INLINE Surface &toSurface(jlong self) { return *(Surface*)self; }
	TS_INLINE D3D12Surface &toD3D12Surface(jlong self) { return *(D3D12Surface*)self; }
	TS_INLINE D3D11Surface &toD3D11Surface(jlong self) { return *(D3D11Surface*)self; }
	TS_INLINE MTLSurface &toMTLSurface(jlong self) { return *(MTLSurface*)self; }
	TS_INLINE VKSurface &toVKSurface(jlong self) { return *(VKSurface*)self; }
	TS_INLINE GLSurface &toGLSurface(jlong self) { return *(GLSurface*)self; }
	TS_INLINE GLESSurface &toGLESSurface(jlong self) { return *(GLESSurface*)self; }
	TS_INLINE Window &toWindow(jlong self) { return *(Window*)self; }
	TS_INLINE Font &toFont(jlong self) { return *(Font*)self; }
	TS_INLINE CanvasElement &toCanvasElement(jlong self) { return *(CanvasElement*)self; }
	TS_INLINE CanvasText &toCanvasText(jlong self) { return *(CanvasText*)self; }
	TS_INLINE CanvasMesh &toCanvasMesh(jlong self) { return *(CanvasMesh*)self; }
	TS_INLINE CanvasRect &toCanvasRect(jlong self) { return *(CanvasRect*)self; }
	TS_INLINE CanvasTriangle &toCanvasTriangle(jlong self) { return *(CanvasTriangle*)self; }
	TS_INLINE CanvasEllipse &toCanvasEllipse(jlong self) { return *(CanvasEllipse*)self; }
	TS_INLINE CanvasShape &toCanvasShape(jlong self) { return *(CanvasShape*)self; }
	TS_INLINE CanvasStrip &toCanvasStrip(jlong self) { return *(CanvasStrip*)self; }
	TS_INLINE Canvas &toCanvas(jlong self) { return *(Canvas*)self; }
	TS_INLINE Control &toControl(jlong self) { return *(Control*)self; }
	TS_INLINE ControlRoot &toControlRoot(jlong self) { return *(ControlRoot*)self; }
	TS_INLINE ControlText &toControlText(jlong self) { return *(ControlText*)self; }
	TS_INLINE ControlRect &toControlRect(jlong self) { return *(ControlRect*)self; }
	TS_INLINE ControlGrid &toControlGrid(jlong self) { return *(ControlGrid*)self; }
	TS_INLINE ControlGroup &toControlGroup(jlong self) { return *(ControlGroup*)self; }
	TS_INLINE ControlPanel &toControlPanel(jlong self) { return *(ControlPanel*)self; }
	TS_INLINE ControlDialog &toControlDialog(jlong self) { return *(ControlDialog*)self; }
	TS_INLINE ControlWindow &toControlWindow(jlong self) { return *(ControlWindow*)self; }
	TS_INLINE ControlCheck &toControlCheck(jlong self) { return *(ControlCheck*)self; }
	TS_INLINE ControlCombo &toControlCombo(jlong self) { return *(ControlCombo*)self; }
	TS_INLINE ControlButton &toControlButton(jlong self) { return *(ControlButton*)self; }
	TS_INLINE ControlSlider &toControlSlider(jlong self) { return *(ControlSlider*)self; }
	TS_INLINE ControlScroll &toControlScroll(jlong self) { return *(ControlScroll*)self; }
	TS_INLINE ControlSplit &toControlSplit(jlong self) { return *(ControlSplit*)self; }
	TS_INLINE ControlArea &toControlArea(jlong self) { return *(ControlArea*)self; }
	TS_INLINE ControlTree &toControlTree(jlong self) { return *(ControlTree*)self; }
	TS_INLINE ControlEdit &toControlEdit(jlong self) { return *(ControlEdit*)self; }
	TS_INLINE DialogMessage &toDialogMessage(jlong self) { return *(DialogMessage*)self; }
	TS_INLINE DialogFileOpen &toDialogFileOpen(jlong self) { return *(DialogFileOpen*)self; }
	TS_INLINE DialogFileSave &toDialogFileSave(jlong self) { return *(DialogFileSave*)self; }
	TS_INLINE DialogDirectory &toDialogDirectory(jlong self) { return *(DialogDirectory*)self; }
	TS_INLINE DialogProgress &toDialogProgress(jlong self) { return *(DialogProgress*)self; }
	TS_INLINE DialogColor &toDialogColor(jlong self) { return *(DialogColor*)self; }
	TS_INLINE DialogMenu &toDialogMenu(jlong self) { return *(DialogMenu*)self; }
	TS_INLINE CubeFilter &toCubeFilter(jlong self) { return *(CubeFilter*)self; }
	TS_INLINE DecoderJPEG &toDecoderJPEG(jlong self) { return *(DecoderJPEG*)self; }
	TS_INLINE EncoderBC15 &toEncoderBC15(jlong self) { return *(EncoderBC15*)self; }
	TS_INLINE EncoderBC67 &toEncoderBC67(jlong self) { return *(EncoderBC67*)self; }
	TS_INLINE EncoderASTC &toEncoderASTC(jlong self) { return *(EncoderASTC*)self; }
	TS_INLINE MeshModel &toMeshModel(jlong self) { return *(MeshModel*)self; }
	TS_INLINE MeshModel::Meshlet &toMeshModelMeshlet(jlong self) { return *(MeshModel::Meshlet*)self; }
	TS_INLINE SeparableFilter &toSeparableFilter(jlong self) { return *(SeparableFilter*)self; }
	TS_INLINE PrefixScan &toPrefixScan(jlong self) { return *(PrefixScan*)self; }
	TS_INLINE PrefixScan::DispatchParameters &toPrefixScanDispatchParameters(jlong self) { return *(PrefixScan::DispatchParameters*)self; }
	TS_INLINE RadixSort &toRadixSort(jlong self) { return *(RadixSort*)self; }
	TS_INLINE RadixSort::DispatchParameters &toRadixSortDispatchParameters(jlong self) { return *(RadixSort::DispatchParameters*)self; }
	TS_INLINE BitonicSort &toBitonicSort(jlong self) { return *(BitonicSort*)self; }
	TS_INLINE BitonicSort::DispatchParameters &toBitonicSortDispatchParameters(jlong self) { return *(BitonicSort::DispatchParameters*)self; }
	TS_INLINE SpatialGrid &toSpatialGrid(jlong self) { return *(SpatialGrid*)self; }
	TS_INLINE SpatialGrid::DispatchParameters &toSpatialGridDispatchParameters(jlong self) { return *(SpatialGrid::DispatchParameters*)self; }
	TS_INLINE SpatialTree &toSpatialTree(jlong self) { return *(SpatialTree*)self; }
	TS_INLINE SpatialTree::Node &toSpatialTreeNode(jlong self) { return *(SpatialTree::Node*)self; }
	TS_INLINE SpatialTree::LeafNodef16 &toSpatialTreeLeafNodef16(jlong self) { return *(SpatialTree::LeafNodef16*)self; }
	TS_INLINE SpatialTree::DispatchParameters &toSpatialTreeDispatchParameters(jlong self) { return *(SpatialTree::DispatchParameters*)self; }
	TS_INLINE FourierTransform &toFourierTransform(jlong self) { return *(FourierTransform*)self; }
	TS_INLINE TensorGraph &toTensorGraph(jlong self) { return *(TensorGraph*)self; }
	TS_INLINE Controller &toController(jlong self) { return *(Controller*)self; }
	TS_INLINE Desktop &toDesktop(jlong self) { return *(Desktop*)self; }
	
	/// Tellusim API
	bool jniInitAPI(JNIEnv *env);
}

#endif /* __TELLUSIM_JNI_API_H__ */

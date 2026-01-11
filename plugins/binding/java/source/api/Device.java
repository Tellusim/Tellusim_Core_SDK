// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;
import java.lang.ref.Cleaner;

/*
 */
public class Device {
	
	public static class Features {
		public Features() { this(new_()); }
		public Features(Features ptr) { this(copy_(ptr.self)); }
		public void setThreadAccess(boolean threadAccess) { set_threadAccess_(self, threadAccess); }
		public boolean getThreadAccess() { return get_threadAccess_(self); }
		public void setBufferTable(boolean bufferTable) { set_bufferTable_(self, bufferTable); }
		public boolean getBufferTable() { return get_bufferTable_(self); }
		public void setBufferSparse(boolean bufferSparse) { set_bufferSparse_(self, bufferSparse); }
		public boolean getBufferSparse() { return get_bufferSparse_(self); }
		public void setTextureTable(boolean textureTable) { set_textureTable_(self, textureTable); }
		public boolean getTextureTable() { return get_textureTable_(self); }
		public void setTextureSparse(boolean textureSparse) { set_textureSparse_(self, textureSparse); }
		public boolean getTextureSparse() { return get_textureSparse_(self); }
		public void setTextureArrayCube(boolean textureArrayCube) { set_textureArrayCube_(self, textureArrayCube); }
		public boolean getTextureArrayCube() { return get_textureArrayCube_(self); }
		public void setTextureArraySparse(boolean textureArraySparse) { set_textureArraySparse_(self, textureArraySparse); }
		public boolean getTextureArraySparse() { return get_textureArraySparse_(self); }
		public void setSurfaceMultisample(boolean surfaceMultisample) { set_surfaceMultisample_(self, surfaceMultisample); }
		public boolean getSurfaceMultisample() { return get_surfaceMultisample_(self); }
		public void setDrawBaseInstance(boolean drawBaseInstance) { set_drawBaseInstance_(self, drawBaseInstance); }
		public boolean getDrawBaseInstance() { return get_drawBaseInstance_(self); }
		public void setDrawIndirectIndex(boolean drawIndirectIndex) { set_drawIndirectIndex_(self, drawIndirectIndex); }
		public boolean getDrawIndirectIndex() { return get_drawIndirectIndex_(self); }
		public void setDrawIndirectCount(boolean drawIndirectCount) { set_drawIndirectCount_(self, drawIndirectCount); }
		public boolean getDrawIndirectCount() { return get_drawIndirectCount_(self); }
		public void setTaskIndirectCount(boolean taskIndirectCount) { set_taskIndirectCount_(self, taskIndirectCount); }
		public boolean getTaskIndirectCount() { return get_taskIndirectCount_(self); }
		public void setVertexStorage(boolean vertexStorage) { set_vertexStorage_(self, vertexStorage); }
		public boolean getVertexStorage() { return get_vertexStorage_(self); }
		public void setVertexIndexLayer(boolean vertexIndexLayer) { set_vertexIndexLayer_(self, vertexIndexLayer); }
		public boolean getVertexIndexLayer() { return get_vertexIndexLayer_(self); }
		public void setGeometryPassthrough(boolean geometryPassthrough) { set_geometryPassthrough_(self, geometryPassthrough); }
		public boolean getGeometryPassthrough() { return get_geometryPassthrough_(self); }
		public void setFragmentBarycentric(boolean fragmentBarycentric) { set_fragmentBarycentric_(self, fragmentBarycentric); }
		public boolean getFragmentBarycentric() { return get_fragmentBarycentric_(self); }
		public void setFragmentStencilExport(boolean fragmentStencilExport) { set_fragmentStencilExport_(self, fragmentStencilExport); }
		public boolean getFragmentStencilExport() { return get_fragmentStencilExport_(self); }
		public void setBlendDualSource(boolean blendDualSource) { set_blendDualSource_(self, blendDualSource); }
		public boolean getBlendDualSource() { return get_blendDualSource_(self); }
		public void setDepthRangeOneToOne(boolean depthRangeOneToOne) { set_depthRangeOneToOne_(self, depthRangeOneToOne); }
		public boolean getDepthRangeOneToOne() { return get_depthRangeOneToOne_(self); }
		public void setRasterConservative(boolean rasterConservative) { set_rasterConservative_(self, rasterConservative); }
		public boolean getRasterConservative() { return get_rasterConservative_(self); }
		public void setRenderConditional(boolean renderConditional) { set_renderConditional_(self, renderConditional); }
		public boolean getRenderConditional() { return get_renderConditional_(self); }
		public void setComputeTracing(boolean computeTracing) { set_computeTracing_(self, computeTracing); }
		public boolean getComputeTracing() { return get_computeTracing_(self); }
		public void setFragmentTracing(boolean fragmentTracing) { set_fragmentTracing_(self, fragmentTracing); }
		public boolean getFragmentTracing() { return get_fragmentTracing_(self); }
		public void setTraversalTracing(boolean traversalTracing) { set_traversalTracing_(self, traversalTracing); }
		public boolean getTraversalTracing() { return get_traversalTracing_(self); }
		public void setBuildIndirectTracing(boolean buildIndirectTracing) { set_buildIndirectTracing_(self, buildIndirectTracing); }
		public boolean getBuildIndirectTracing() { return get_buildIndirectTracing_(self); }
		public void setMaxTraversalDepth(int maxTraversalDepth) { set_maxTraversalDepth_(self, maxTraversalDepth); }
		public int getMaxTraversalDepth() { return get_maxTraversalDepth_(self); }
		public void setSubgroupVote(boolean subgroupVote) { set_subgroupVote_(self, subgroupVote); }
		public boolean getSubgroupVote() { return get_subgroupVote_(self); }
		public void setSubgroupMath(boolean subgroupMath) { set_subgroupMath_(self, subgroupMath); }
		public boolean getSubgroupMath() { return get_subgroupMath_(self); }
		public void setSubgroupShuffle(boolean subgroupShuffle) { set_subgroupShuffle_(self, subgroupShuffle); }
		public boolean getSubgroupShuffle() { return get_subgroupShuffle_(self); }
		public void setSubgroupSize(int subgroupSize) { set_subgroupSize_(self, subgroupSize); }
		public int getSubgroupSize() { return get_subgroupSize_(self); }
		public void setMinSubgroupSize(int minSubgroupSize) { set_minSubgroupSize_(self, minSubgroupSize); }
		public int getMinSubgroupSize() { return get_minSubgroupSize_(self); }
		public void setMaxSubgroupSize(int maxSubgroupSize) { set_maxSubgroupSize_(self, maxSubgroupSize); }
		public int getMaxSubgroupSize() { return get_maxSubgroupSize_(self); }
		public void setShaderu8(boolean shaderu8) { set_shaderu8_(self, shaderu8); }
		public boolean getShaderu8() { return get_shaderu8_(self); }
		public void setShaderf16(boolean shaderf16) { set_shaderf16_(self, shaderf16); }
		public boolean getShaderf16() { return get_shaderf16_(self); }
		public void setShaderu16(boolean shaderu16) { set_shaderu16_(self, shaderu16); }
		public boolean getShaderu16() { return get_shaderu16_(self); }
		public void setShaderf64(boolean shaderf64) { set_shaderf64_(self, shaderf64); }
		public boolean getShaderf64() { return get_shaderf64_(self); }
		public void setShaderu64(boolean shaderu64) { set_shaderu64_(self, shaderu64); }
		public boolean getShaderu64() { return get_shaderu64_(self); }
		public void setAtomicGroupf32(boolean atomicGroupf32) { set_atomicGroupf32_(self, atomicGroupf32); }
		public boolean getAtomicGroupf32() { return get_atomicGroupf32_(self); }
		public void setAtomicGroupu64(boolean atomicGroupu64) { set_atomicGroupu64_(self, atomicGroupu64); }
		public boolean getAtomicGroupu64() { return get_atomicGroupu64_(self); }
		public void setAtomicBufferf32(boolean atomicBufferf32) { set_atomicBufferf32_(self, atomicBufferf32); }
		public boolean getAtomicBufferf32() { return get_atomicBufferf32_(self); }
		public void setAtomicBufferu64(boolean atomicBufferu64) { set_atomicBufferu64_(self, atomicBufferu64); }
		public boolean getAtomicBufferu64() { return get_atomicBufferu64_(self); }
		public void setAtomicTexturef32(boolean atomicTexturef32) { set_atomicTexturef32_(self, atomicTexturef32); }
		public boolean getAtomicTexturef32() { return get_atomicTexturef32_(self); }
		public void setAtomicTextureu32(boolean atomicTextureu32) { set_atomicTextureu32_(self, atomicTextureu32); }
		public boolean getAtomicTextureu32() { return get_atomicTextureu32_(self); }
		public void setAtomicTextureu64(boolean atomicTextureu64) { set_atomicTextureu64_(self, atomicTextureu64); }
		public boolean getAtomicTextureu64() { return get_atomicTextureu64_(self); }
		public void setMatrix16f16(boolean matrix16f16) { set_matrix16f16_(self, matrix16f16); }
		public boolean getMatrix16f16() { return get_matrix16f16_(self); }
		public void setMatrix16x8x8f16(boolean matrix16x8x8f16) { set_matrix16x8x8f16_(self, matrix16x8x8f16); }
		public boolean getMatrix16x8x8f16() { return get_matrix16x8x8f16_(self); }
		public void setMatrix8x16x16f16(boolean matrix8x16x16f16) { set_matrix8x16x16f16_(self, matrix8x16x16f16); }
		public boolean getMatrix8x16x16f16() { return get_matrix8x16x16f16_(self); }
		public void setMatrix16x8x16f16(boolean matrix16x8x16f16) { set_matrix16x8x16f16_(self, matrix16x8x16f16); }
		public boolean getMatrix16x8x16f16() { return get_matrix16x8x16f16_(self); }
		public void setMatrix16f16f32(boolean matrix16f16f32) { set_matrix16f16f32_(self, matrix16f16f32); }
		public boolean getMatrix16f16f32() { return get_matrix16f16f32_(self); }
		public void setMatrix16x8x8f16f32(boolean matrix16x8x8f16f32) { set_matrix16x8x8f16f32_(self, matrix16x8x8f16f32); }
		public boolean getMatrix16x8x8f16f32() { return get_matrix16x8x8f16f32_(self); }
		public void setMatrix8x16x16f16f32(boolean matrix8x16x16f16f32) { set_matrix8x16x16f16f32_(self, matrix8x16x16f16f32); }
		public boolean getMatrix8x16x16f16f32() { return get_matrix8x16x16f16f32_(self); }
		public void setMatrix16x8x16f16f32(boolean matrix16x8x16f16f32) { set_matrix16x8x16f16f32_(self, matrix16x8x16f16f32); }
		public boolean getMatrix16x8x16f16f32() { return get_matrix16x8x16f16f32_(self); }
		public void setUniformAlignment(int uniformAlignment) { set_uniformAlignment_(self, uniformAlignment); }
		public int getUniformAlignment() { return get_uniformAlignment_(self); }
		public void setStorageAlignment(int storageAlignment) { set_storageAlignment_(self, storageAlignment); }
		public int getStorageAlignment() { return get_storageAlignment_(self); }
		public void setMaxTexture2DSize(int maxTexture2DSize) { set_maxTexture2DSize_(self, maxTexture2DSize); }
		public int getMaxTexture2DSize() { return get_maxTexture2DSize_(self); }
		public void setMaxTexture3DSize(int maxTexture3DSize) { set_maxTexture3DSize_(self, maxTexture3DSize); }
		public int getMaxTexture3DSize() { return get_maxTexture3DSize_(self); }
		public void setMaxTextureLayers(int maxTextureLayers) { set_maxTextureLayers_(self, maxTextureLayers); }
		public int getMaxTextureLayers() { return get_maxTextureLayers_(self); }
		public void setMaxTextureSamples(int maxTextureSamples) { set_maxTextureSamples_(self, maxTextureSamples); }
		public int getMaxTextureSamples() { return get_maxTextureSamples_(self); }
		public void setMaxGroupSizeX(int maxGroupSizeX) { set_maxGroupSizeX_(self, maxGroupSizeX); }
		public int getMaxGroupSizeX() { return get_maxGroupSizeX_(self); }
		public void setMaxGroupSizeY(int maxGroupSizeY) { set_maxGroupSizeY_(self, maxGroupSizeY); }
		public int getMaxGroupSizeY() { return get_maxGroupSizeY_(self); }
		public void setMaxGroupSizeZ(int maxGroupSizeZ) { set_maxGroupSizeZ_(self, maxGroupSizeZ); }
		public int getMaxGroupSizeZ() { return get_maxGroupSizeZ_(self); }
		public void setMaxGroupCountX(int maxGroupCountX) { set_maxGroupCountX_(self, maxGroupCountX); }
		public int getMaxGroupCountX() { return get_maxGroupCountX_(self); }
		public void setMaxGroupCountY(int maxGroupCountY) { set_maxGroupCountY_(self, maxGroupCountY); }
		public int getMaxGroupCountY() { return get_maxGroupCountY_(self); }
		public void setMaxGroupCountZ(int maxGroupCountZ) { set_maxGroupCountZ_(self, maxGroupCountZ); }
		public int getMaxGroupCountZ() { return get_maxGroupCountZ_(self); }
		public void setMaxTaskCount(int maxTaskCount) { set_maxTaskCount_(self, maxTaskCount); }
		public int getMaxTaskCount() { return get_maxTaskCount_(self); }
		public void setMaxTaskMemory(int maxTaskMemory) { set_maxTaskMemory_(self, maxTaskMemory); }
		public int getMaxTaskMemory() { return get_maxTaskMemory_(self); }
		public void setMaxTaskMeshes(int maxTaskMeshes) { set_maxTaskMeshes_(self, maxTaskMeshes); }
		public int getMaxTaskMeshes() { return get_maxTaskMeshes_(self); }
		public void setMaxMeshMemory(int maxMeshMemory) { set_maxMeshMemory_(self, maxMeshMemory); }
		public int getMaxMeshMemory() { return get_maxMeshMemory_(self); }
		public void setMaxMeshVertices(int maxMeshVertices) { set_maxMeshVertices_(self, maxMeshVertices); }
		public int getMaxMeshVertices() { return get_maxMeshVertices_(self); }
		public void setMaxMeshPrimitives(int maxMeshPrimitives) { set_maxMeshPrimitives_(self, maxMeshPrimitives); }
		public int getMaxMeshPrimitives() { return get_maxMeshPrimitives_(self); }
		public void setMaxViewportCount(int maxViewportCount) { set_maxViewportCount_(self, maxViewportCount); }
		public int getMaxViewportCount() { return get_maxViewportCount_(self); }
		public void setMaxClipCullCount(int maxClipCullCount) { set_maxClipCullCount_(self, maxClipCullCount); }
		public int getMaxClipCullCount() { return get_maxClipCullCount_(self); }
		public void setMaxUniformSize(long maxUniformSize) { set_maxUniformSize_(self, maxUniformSize); }
		public long getMaxUniformSize() { return get_maxUniformSize_(self); }
		public void setMaxStorageSize(long maxStorageSize) { set_maxStorageSize_(self, maxStorageSize); }
		public long getMaxStorageSize() { return get_maxStorageSize_(self); }
		public void setGroupMemory(int groupMemory) { set_groupMemory_(self, groupMemory); }
		public int getGroupMemory() { return get_groupMemory_(self); }
		public void setVideoMemory(long videoMemory) { set_videoMemory_(self, videoMemory); }
		public long getVideoMemory() { return get_videoMemory_(self); }
		public void setVendorID(int vendorID) { set_vendorID_(self, vendorID); }
		public int getVendorID() { return get_vendorID_(self); }
		public void setDeviceID(int deviceID) { set_deviceID_(self, deviceID); }
		public int getDeviceID() { return get_deviceID_(self); }
		public void setPciBusID(int pciBusID) { set_pciBusID_(self, pciBusID); }
		public int getPciBusID() { return get_pciBusID_(self); }
		public void setPciDomainID(int pciDomainID) { set_pciDomainID_(self, pciDomainID); }
		public int getPciDomainID() { return get_pciDomainID_(self); }
		public void setPciDeviceID(int pciDeviceID) { set_pciDeviceID_(self, pciDeviceID); }
		public int getPciDeviceID() { return get_pciDeviceID_(self); }
		public String toString() {
			String ret = "threadAccess: " + getThreadAccess();
			ret += "\nbufferTable: " + getBufferTable();
			ret += "\nbufferSparse: " + getBufferSparse();
			ret += "\ntextureTable: " + getTextureTable();
			ret += "\ntextureSparse: " + getTextureSparse();
			ret += "\ntextureArrayCube: " + getTextureArrayCube();
			ret += "\ntextureArraySparse: " + getTextureArraySparse();
			ret += "\nsurfaceMultisample: " + getSurfaceMultisample();
			ret += "\ndrawBaseInstance: " + getDrawBaseInstance();
			ret += "\ndrawIndirectIndex: " + getDrawIndirectIndex();
			ret += "\ndrawIndirectCount: " + getDrawIndirectCount();
			ret += "\ntaskIndirectCount: " + getTaskIndirectCount();
			ret += "\nvertexStorage: " + getVertexStorage();
			ret += "\nvertexIndexLayer: " + getVertexIndexLayer();
			ret += "\ngeometryPassthrough: " + getGeometryPassthrough();
			ret += "\nfragmentBarycentric: " + getFragmentBarycentric();
			ret += "\nfragmentStencilExport: " + getFragmentStencilExport();
			ret += "\nblendDualSource: " + getBlendDualSource();
			ret += "\ndepthRangeOneToOne: " + getDepthRangeOneToOne();
			ret += "\nrasterConservative: " + getRasterConservative();
			ret += "\nrenderConditional: " + getRenderConditional();
			ret += "\ncomputeTracing: " + getComputeTracing();
			ret += "\nfragmentTracing: " + getFragmentTracing();
			ret += "\ntraversalTracing: " + getTraversalTracing();
			ret += "\nbuildIndirectTracing: " + getBuildIndirectTracing();
			ret += "\nmaxTraversalDepth: " + getMaxTraversalDepth();
			ret += "\nsubgroupVote: " + getSubgroupVote();
			ret += "\nsubgroupMath: " + getSubgroupMath();
			ret += "\nsubgroupShuffle: " + getSubgroupShuffle();
			ret += "\nsubgroupSize: " + getSubgroupSize();
			ret += "\nminSubgroupSize: " + getMinSubgroupSize();
			ret += "\nmaxSubgroupSize: " + getMaxSubgroupSize();
			ret += "\nshaderu8: " + getShaderu8();
			ret += "\nshaderf16: " + getShaderf16();
			ret += "\nshaderu16: " + getShaderu16();
			ret += "\nshaderf64: " + getShaderf64();
			ret += "\nshaderu64: " + getShaderu64();
			ret += "\natomicGroupf32: " + getAtomicGroupf32();
			ret += "\natomicGroupu64: " + getAtomicGroupu64();
			ret += "\natomicBufferf32: " + getAtomicBufferf32();
			ret += "\natomicBufferu64: " + getAtomicBufferu64();
			ret += "\natomicTexturef32: " + getAtomicTexturef32();
			ret += "\natomicTextureu32: " + getAtomicTextureu32();
			ret += "\natomicTextureu64: " + getAtomicTextureu64();
			ret += "\nmatrix16f16: " + getMatrix16f16();
			ret += "\nmatrix16x8x8f16: " + getMatrix16x8x8f16();
			ret += "\nmatrix8x16x16f16: " + getMatrix8x16x16f16();
			ret += "\nmatrix16x8x16f16: " + getMatrix16x8x16f16();
			ret += "\nmatrix16f16f32: " + getMatrix16f16f32();
			ret += "\nmatrix16x8x8f16f32: " + getMatrix16x8x8f16f32();
			ret += "\nmatrix8x16x16f16f32: " + getMatrix8x16x16f16f32();
			ret += "\nmatrix16x8x16f16f32: " + getMatrix16x8x16f16f32();
			ret += "\nuniformAlignment: " + getUniformAlignment();
			ret += "\nstorageAlignment: " + getStorageAlignment();
			ret += "\nmaxTexture2DSize: " + getMaxTexture2DSize();
			ret += "\nmaxTexture3DSize: " + getMaxTexture3DSize();
			ret += "\nmaxTextureLayers: " + getMaxTextureLayers();
			ret += "\nmaxTextureSamples: " + getMaxTextureSamples();
			ret += "\nmaxGroupSizeX: " + getMaxGroupSizeX();
			ret += "\nmaxGroupSizeY: " + getMaxGroupSizeY();
			ret += "\nmaxGroupSizeZ: " + getMaxGroupSizeZ();
			ret += "\nmaxGroupCountX: " + getMaxGroupCountX();
			ret += "\nmaxGroupCountY: " + getMaxGroupCountY();
			ret += "\nmaxGroupCountZ: " + getMaxGroupCountZ();
			ret += "\nmaxTaskCount: " + getMaxTaskCount();
			ret += "\nmaxTaskMemory: " + getMaxTaskMemory();
			ret += "\nmaxTaskMeshes: " + getMaxTaskMeshes();
			ret += "\nmaxMeshMemory: " + getMaxMeshMemory();
			ret += "\nmaxMeshVertices: " + getMaxMeshVertices();
			ret += "\nmaxMeshPrimitives: " + getMaxMeshPrimitives();
			ret += "\nmaxViewportCount: " + getMaxViewportCount();
			ret += "\nmaxClipCullCount: " + getMaxClipCullCount();
			ret += "\nmaxUniformSize: " + getMaxUniformSize();
			ret += "\nmaxStorageSize: " + getMaxStorageSize();
			ret += "\ngroupMemory: " + getGroupMemory();
			ret += "\nvideoMemory: " + getVideoMemory();
			ret += "\nvendorID: " + getVendorID();
			ret += "\ndeviceID: " + getDeviceID();
			ret += "\npciBusID: " + getPciBusID();
			ret += "\npciDomainID: " + getPciDomainID();
			ret += "\npciDeviceID: " + getPciDeviceID();
			return ret;
		}
		private static native long new_();
		private static native long copy_(long self);
		private static native void delete_(long self);
		private static native void set_threadAccess_(long self, boolean threadAccess);
		private static native boolean get_threadAccess_(long self);
		private static native void set_bufferTable_(long self, boolean bufferTable);
		private static native boolean get_bufferTable_(long self);
		private static native void set_bufferSparse_(long self, boolean bufferSparse);
		private static native boolean get_bufferSparse_(long self);
		private static native void set_textureTable_(long self, boolean textureTable);
		private static native boolean get_textureTable_(long self);
		private static native void set_textureSparse_(long self, boolean textureSparse);
		private static native boolean get_textureSparse_(long self);
		private static native void set_textureArrayCube_(long self, boolean textureArrayCube);
		private static native boolean get_textureArrayCube_(long self);
		private static native void set_textureArraySparse_(long self, boolean textureArraySparse);
		private static native boolean get_textureArraySparse_(long self);
		private static native void set_surfaceMultisample_(long self, boolean surfaceMultisample);
		private static native boolean get_surfaceMultisample_(long self);
		private static native void set_drawBaseInstance_(long self, boolean drawBaseInstance);
		private static native boolean get_drawBaseInstance_(long self);
		private static native void set_drawIndirectIndex_(long self, boolean drawIndirectIndex);
		private static native boolean get_drawIndirectIndex_(long self);
		private static native void set_drawIndirectCount_(long self, boolean drawIndirectCount);
		private static native boolean get_drawIndirectCount_(long self);
		private static native void set_taskIndirectCount_(long self, boolean taskIndirectCount);
		private static native boolean get_taskIndirectCount_(long self);
		private static native void set_vertexStorage_(long self, boolean vertexStorage);
		private static native boolean get_vertexStorage_(long self);
		private static native void set_vertexIndexLayer_(long self, boolean vertexIndexLayer);
		private static native boolean get_vertexIndexLayer_(long self);
		private static native void set_geometryPassthrough_(long self, boolean geometryPassthrough);
		private static native boolean get_geometryPassthrough_(long self);
		private static native void set_fragmentBarycentric_(long self, boolean fragmentBarycentric);
		private static native boolean get_fragmentBarycentric_(long self);
		private static native void set_fragmentStencilExport_(long self, boolean fragmentStencilExport);
		private static native boolean get_fragmentStencilExport_(long self);
		private static native void set_blendDualSource_(long self, boolean blendDualSource);
		private static native boolean get_blendDualSource_(long self);
		private static native void set_depthRangeOneToOne_(long self, boolean depthRangeOneToOne);
		private static native boolean get_depthRangeOneToOne_(long self);
		private static native void set_rasterConservative_(long self, boolean rasterConservative);
		private static native boolean get_rasterConservative_(long self);
		private static native void set_renderConditional_(long self, boolean renderConditional);
		private static native boolean get_renderConditional_(long self);
		private static native void set_computeTracing_(long self, boolean computeTracing);
		private static native boolean get_computeTracing_(long self);
		private static native void set_fragmentTracing_(long self, boolean fragmentTracing);
		private static native boolean get_fragmentTracing_(long self);
		private static native void set_traversalTracing_(long self, boolean traversalTracing);
		private static native boolean get_traversalTracing_(long self);
		private static native void set_buildIndirectTracing_(long self, boolean buildIndirectTracing);
		private static native boolean get_buildIndirectTracing_(long self);
		private static native void set_maxTraversalDepth_(long self, int maxTraversalDepth);
		private static native int get_maxTraversalDepth_(long self);
		private static native void set_subgroupVote_(long self, boolean subgroupVote);
		private static native boolean get_subgroupVote_(long self);
		private static native void set_subgroupMath_(long self, boolean subgroupMath);
		private static native boolean get_subgroupMath_(long self);
		private static native void set_subgroupShuffle_(long self, boolean subgroupShuffle);
		private static native boolean get_subgroupShuffle_(long self);
		private static native void set_subgroupSize_(long self, int subgroupSize);
		private static native int get_subgroupSize_(long self);
		private static native void set_minSubgroupSize_(long self, int minSubgroupSize);
		private static native int get_minSubgroupSize_(long self);
		private static native void set_maxSubgroupSize_(long self, int maxSubgroupSize);
		private static native int get_maxSubgroupSize_(long self);
		private static native void set_shaderu8_(long self, boolean shaderu8);
		private static native boolean get_shaderu8_(long self);
		private static native void set_shaderf16_(long self, boolean shaderf16);
		private static native boolean get_shaderf16_(long self);
		private static native void set_shaderu16_(long self, boolean shaderu16);
		private static native boolean get_shaderu16_(long self);
		private static native void set_shaderf64_(long self, boolean shaderf64);
		private static native boolean get_shaderf64_(long self);
		private static native void set_shaderu64_(long self, boolean shaderu64);
		private static native boolean get_shaderu64_(long self);
		private static native void set_atomicGroupf32_(long self, boolean atomicGroupf32);
		private static native boolean get_atomicGroupf32_(long self);
		private static native void set_atomicGroupu64_(long self, boolean atomicGroupu64);
		private static native boolean get_atomicGroupu64_(long self);
		private static native void set_atomicBufferf32_(long self, boolean atomicBufferf32);
		private static native boolean get_atomicBufferf32_(long self);
		private static native void set_atomicBufferu64_(long self, boolean atomicBufferu64);
		private static native boolean get_atomicBufferu64_(long self);
		private static native void set_atomicTexturef32_(long self, boolean atomicTexturef32);
		private static native boolean get_atomicTexturef32_(long self);
		private static native void set_atomicTextureu32_(long self, boolean atomicTextureu32);
		private static native boolean get_atomicTextureu32_(long self);
		private static native void set_atomicTextureu64_(long self, boolean atomicTextureu64);
		private static native boolean get_atomicTextureu64_(long self);
		private static native void set_matrix16f16_(long self, boolean matrix16f16);
		private static native boolean get_matrix16f16_(long self);
		private static native void set_matrix16x8x8f16_(long self, boolean matrix16x8x8f16);
		private static native boolean get_matrix16x8x8f16_(long self);
		private static native void set_matrix8x16x16f16_(long self, boolean matrix8x16x16f16);
		private static native boolean get_matrix8x16x16f16_(long self);
		private static native void set_matrix16x8x16f16_(long self, boolean matrix16x8x16f16);
		private static native boolean get_matrix16x8x16f16_(long self);
		private static native void set_matrix16f16f32_(long self, boolean matrix16f16f32);
		private static native boolean get_matrix16f16f32_(long self);
		private static native void set_matrix16x8x8f16f32_(long self, boolean matrix16x8x8f16f32);
		private static native boolean get_matrix16x8x8f16f32_(long self);
		private static native void set_matrix8x16x16f16f32_(long self, boolean matrix8x16x16f16f32);
		private static native boolean get_matrix8x16x16f16f32_(long self);
		private static native void set_matrix16x8x16f16f32_(long self, boolean matrix16x8x16f16f32);
		private static native boolean get_matrix16x8x16f16f32_(long self);
		private static native void set_uniformAlignment_(long self, int uniformAlignment);
		private static native int get_uniformAlignment_(long self);
		private static native void set_storageAlignment_(long self, int storageAlignment);
		private static native int get_storageAlignment_(long self);
		private static native void set_maxTexture2DSize_(long self, int maxTexture2DSize);
		private static native int get_maxTexture2DSize_(long self);
		private static native void set_maxTexture3DSize_(long self, int maxTexture3DSize);
		private static native int get_maxTexture3DSize_(long self);
		private static native void set_maxTextureLayers_(long self, int maxTextureLayers);
		private static native int get_maxTextureLayers_(long self);
		private static native void set_maxTextureSamples_(long self, int maxTextureSamples);
		private static native int get_maxTextureSamples_(long self);
		private static native void set_maxGroupSizeX_(long self, int maxGroupSizeX);
		private static native int get_maxGroupSizeX_(long self);
		private static native void set_maxGroupSizeY_(long self, int maxGroupSizeY);
		private static native int get_maxGroupSizeY_(long self);
		private static native void set_maxGroupSizeZ_(long self, int maxGroupSizeZ);
		private static native int get_maxGroupSizeZ_(long self);
		private static native void set_maxGroupCountX_(long self, int maxGroupCountX);
		private static native int get_maxGroupCountX_(long self);
		private static native void set_maxGroupCountY_(long self, int maxGroupCountY);
		private static native int get_maxGroupCountY_(long self);
		private static native void set_maxGroupCountZ_(long self, int maxGroupCountZ);
		private static native int get_maxGroupCountZ_(long self);
		private static native void set_maxTaskCount_(long self, int maxTaskCount);
		private static native int get_maxTaskCount_(long self);
		private static native void set_maxTaskMemory_(long self, int maxTaskMemory);
		private static native int get_maxTaskMemory_(long self);
		private static native void set_maxTaskMeshes_(long self, int maxTaskMeshes);
		private static native int get_maxTaskMeshes_(long self);
		private static native void set_maxMeshMemory_(long self, int maxMeshMemory);
		private static native int get_maxMeshMemory_(long self);
		private static native void set_maxMeshVertices_(long self, int maxMeshVertices);
		private static native int get_maxMeshVertices_(long self);
		private static native void set_maxMeshPrimitives_(long self, int maxMeshPrimitives);
		private static native int get_maxMeshPrimitives_(long self);
		private static native void set_maxViewportCount_(long self, int maxViewportCount);
		private static native int get_maxViewportCount_(long self);
		private static native void set_maxClipCullCount_(long self, int maxClipCullCount);
		private static native int get_maxClipCullCount_(long self);
		private static native void set_maxUniformSize_(long self, long maxUniformSize);
		private static native long get_maxUniformSize_(long self);
		private static native void set_maxStorageSize_(long self, long maxStorageSize);
		private static native long get_maxStorageSize_(long self);
		private static native void set_groupMemory_(long self, int groupMemory);
		private static native int get_groupMemory_(long self);
		private static native void set_videoMemory_(long self, long videoMemory);
		private static native long get_videoMemory_(long self);
		private static native void set_vendorID_(long self, int vendorID);
		private static native int get_vendorID_(long self);
		private static native void set_deviceID_(long self, int deviceID);
		private static native int get_deviceID_(long self);
		private static native void set_pciBusID_(long self, int pciBusID);
		private static native int get_pciBusID_(long self);
		private static native void set_pciDomainID_(long self, int pciDomainID);
		private static native int get_pciDomainID_(long self);
		private static native void set_pciDeviceID_(long self, int pciDeviceID);
		private static native int get_pciDeviceID_(long self);
		protected Features(long self) {
			cleaner.register(this, new Destructor(self));
			this.self = self;
		}
		protected static long[] self_(Features[] ptr) {
			long[] self = new long[ptr.length];
			for(int i = 0; i < ptr.length; i++) self[i] = ptr[i].self;
			return self;
		}
		private static class Destructor implements Runnable {
			Destructor(long self) { this.self = self; }
			public void run() { delete_(self); }
			private long self;
		}
		private static Cleaner cleaner = Cleaner.create();
		protected long self;
	}
	
	public Device() { init_(new_()); }
	public Device(Context context) { init_(new_1(context.self)); }
	public Device(Surface surface) { init_(new_2(surface.self)); }
	public Device(Window window) { init_(new_3(window.self)); }
	public Device[] ref() { return new Device[] { this }; }
	public boolean equalPtr(Device ptr) { return equal_ptr(self, ptr.self); }
	public Device clonePtr() { return new Device(clone_ptr(self)); }
	public void clearPtr() { clear_ptr(self); }
	public void destroyPtr() { destroy_ptr(self); }
	public void acquirePtr() { acquire_ptr(self); }
	public void unacquirePtr() { unacquire_ptr(self); }
	public boolean isValidPtr() { return is_valid_ptr(self); }
	public boolean isOwnerPtr() { return is_owner_ptr(self); }
	public boolean isConstPtr() { return is_const_ptr(self); }
	public int getCountPtr() { return get_count_ptr(self); }
	public long getInternalPtr() { return get_internal_ptr(self); }
	public Platform getPlatform() { return new Platform(get_platform(self)); }
	public String getPlatformName() { return get_platform_name(self); }
	public int getIndex() { return get_index(self); }
	public String getName() { return get_name(self); }
	public String getVendor() { return get_vendor(self); }
	public String getVersion() { return get_version(self); }
	public Features getFeatures() { return new Features(get_features(self)); }
	public boolean hasQuery(Query.Type type) { return has_query(self, type.value); }
	public boolean hasQuery(Query.Type.Enum type) { return has_query(self, type.value); }
	public boolean hasShader(Shader.Type type) { return has_shader(self, type.value); }
	public boolean hasShader(Shader.Type.Enum type) { return has_shader(self, type.value); }
	public boolean hasTarget(Format format) { return has_target(self, format.value); }
	public boolean hasTarget(Format.Enum format) { return has_target(self, format.value); }
	public boolean hasTexture(Format format) { return has_texture(self, format.value); }
	public boolean hasTexture(Format.Enum format) { return has_texture(self, format.value); }
	public boolean hasSurface(Format format) { return has_surface(self, format.value); }
	public boolean hasSurface(Format.Enum format) { return has_surface(self, format.value); }
	public Device createDevice(int index) { return new Device(create_device(self, index, 3)); }
	public Device createDevice(int index, int frames) { return new Device(create_device(self, index, frames)); }
	public Device createCommandDevice() { return new Device(create_command_device(self, 3)); }
	public Device createCommandDevice(int frames) { return new Device(create_command_device(self, frames)); }
	public Device createComputeDevice() { return new Device(create_compute_device(self, 3)); }
	public Device createComputeDevice(int frames) { return new Device(create_compute_device(self, frames)); }
	public Device createCopyDevice() { return new Device(create_copy_device(self, 3)); }
	public Device createCopyDevice(int frames) { return new Device(create_copy_device(self, frames)); }
	public Query createQuery() { return new Query(create_query(self)); }
	public Query createQuery(Query.Type type) { return new Query(create_query_1(self, type.value)); }
	public Query createQuery(Query.Type.Enum type) { return new Query(create_query_1(self, type.value)); }
	public Fence createFence() { return new Fence(create_fence(self)); }
	public Fence createFence(Fence shared) { return new Fence(create_fence_1(self, shared.self)); }
	public Fence createFence(Fence.Flags flags) { return new Fence(create_fence_2(self, flags.value)); }
	public Fence createFence(Fence.Flags.Enum flags) { return new Fence(create_fence_2(self, flags.value)); }
	public Buffer createBuffer() { return new Buffer(create_buffer(self)); }
	public Buffer createBuffer(Buffer shared) { return new Buffer(create_buffer_1(self, shared.self)); }
	public Buffer createBuffer(Buffer.Flags flags, long size) { return new Buffer(create_buffer_2(self, flags.value, size, Format.Unknown.value)); }
	public Buffer createBuffer(Buffer.Flags.Enum flags, long size) { return new Buffer(create_buffer_2(self, flags.value, size, Format.Unknown.value)); }
	public Buffer createBuffer(Buffer.Flags flags, long size, Format format) { return new Buffer(create_buffer_2(self, flags.value, size, format.value)); }
	public Buffer createBuffer(Buffer.Flags.Enum flags, long size, Format format) { return new Buffer(create_buffer_2(self, flags.value, size, format.value)); }
	public Buffer createBuffer(Buffer.Flags.Enum flags, long size, Format.Enum format) { return new Buffer(create_buffer_2(self, flags.value, size, format.value)); }
	public Buffer createBuffer(Buffer.Flags flags, long size, Format.Enum format) { return new Buffer(create_buffer_2(self, flags.value, size, format.value)); }
	public Buffer createBuffer(Buffer.Flags flags, byte[] src) { return new Buffer(create_buffer_3(self, flags.value, src, Format.Unknown.value)); }
	public Buffer createBuffer(Buffer.Flags.Enum flags, byte[] src) { return new Buffer(create_buffer_3(self, flags.value, src, Format.Unknown.value)); }
	public Buffer createBuffer(Buffer.Flags flags, byte[] src, Format format) { return new Buffer(create_buffer_3(self, flags.value, src, format.value)); }
	public Buffer createBuffer(Buffer.Flags.Enum flags, byte[] src, Format format) { return new Buffer(create_buffer_3(self, flags.value, src, format.value)); }
	public Buffer createBuffer(Buffer.Flags.Enum flags, byte[] src, Format.Enum format) { return new Buffer(create_buffer_3(self, flags.value, src, format.value)); }
	public Buffer createBuffer(Buffer.Flags flags, byte[] src, Format.Enum format) { return new Buffer(create_buffer_3(self, flags.value, src, format.value)); }
	public Sampler createSampler() { return new Sampler(create_sampler(self)); }
	public Sampler createSampler(Sampler sampler) { return new Sampler(create_sampler_1(self, sampler.self)); }
	public Sampler createSampler(Sampler.Filter filter) { return new Sampler(create_sampler_2(self, filter.value, Sampler.WrapMode.Repeat.value, Sampler.MaxAnisotropy)); }
	public Sampler createSampler(Sampler.Filter.Enum filter) { return new Sampler(create_sampler_2(self, filter.value, Sampler.WrapMode.Repeat.value, Sampler.MaxAnisotropy)); }
	public Sampler createSampler(Sampler.Filter filter, Sampler.WrapMode mode) { return new Sampler(create_sampler_2(self, filter.value, mode.value, Sampler.MaxAnisotropy)); }
	public Sampler createSampler(Sampler.Filter.Enum filter, Sampler.WrapMode mode) { return new Sampler(create_sampler_2(self, filter.value, mode.value, Sampler.MaxAnisotropy)); }
	public Sampler createSampler(Sampler.Filter.Enum filter, Sampler.WrapMode.Enum mode) { return new Sampler(create_sampler_2(self, filter.value, mode.value, Sampler.MaxAnisotropy)); }
	public Sampler createSampler(Sampler.Filter filter, Sampler.WrapMode.Enum mode) { return new Sampler(create_sampler_2(self, filter.value, mode.value, Sampler.MaxAnisotropy)); }
	public Sampler createSampler(Sampler.Filter filter, Sampler.WrapMode mode, int anisotropy) { return new Sampler(create_sampler_2(self, filter.value, mode.value, anisotropy)); }
	public Sampler createSampler(Sampler.Filter.Enum filter, Sampler.WrapMode mode, int anisotropy) { return new Sampler(create_sampler_2(self, filter.value, mode.value, anisotropy)); }
	public Sampler createSampler(Sampler.Filter.Enum filter, Sampler.WrapMode.Enum mode, int anisotropy) { return new Sampler(create_sampler_2(self, filter.value, mode.value, anisotropy)); }
	public Sampler createSampler(Sampler.Filter filter, Sampler.WrapMode.Enum mode, int anisotropy) { return new Sampler(create_sampler_2(self, filter.value, mode.value, anisotropy)); }
	public Texture createTexture() { return new Texture(create_texture(self)); }
	public Texture createTexture(Texture shared) { return new Texture(create_texture_1(self, shared.self)); }
	public Texture createTexture(Texture.Type type, Format format, Size size, int layers) { return new Texture(create_texture_2(self, type.value, format.value, size.self, layers, Texture.Flags.Default.value)); }
	public Texture createTexture(Texture.Type.Enum type, Format format, Size size, int layers) { return new Texture(create_texture_2(self, type.value, format.value, size.self, layers, Texture.Flags.Default.value)); }
	public Texture createTexture(Texture.Type.Enum type, Format.Enum format, Size size, int layers) { return new Texture(create_texture_2(self, type.value, format.value, size.self, layers, Texture.Flags.Default.value)); }
	public Texture createTexture(Texture.Type type, Format.Enum format, Size size, int layers) { return new Texture(create_texture_2(self, type.value, format.value, size.self, layers, Texture.Flags.Default.value)); }
	public Texture createTexture(Texture.Type type, Format format, Size size, int layers, Texture.Flags flags) { return new Texture(create_texture_2(self, type.value, format.value, size.self, layers, flags.value)); }
	public Texture createTexture(Texture.Type.Enum type, Format format, Size size, int layers, Texture.Flags flags) { return new Texture(create_texture_2(self, type.value, format.value, size.self, layers, flags.value)); }
	public Texture createTexture(Texture.Type.Enum type, Format.Enum format, Size size, int layers, Texture.Flags flags) { return new Texture(create_texture_2(self, type.value, format.value, size.self, layers, flags.value)); }
	public Texture createTexture(Texture.Type.Enum type, Format format, Size size, int layers, Texture.Flags.Enum flags) { return new Texture(create_texture_2(self, type.value, format.value, size.self, layers, flags.value)); }
	public Texture createTexture(Texture.Type type, Format.Enum format, Size size, int layers, Texture.Flags flags) { return new Texture(create_texture_2(self, type.value, format.value, size.self, layers, flags.value)); }
	public Texture createTexture(Texture.Type type, Format.Enum format, Size size, int layers, Texture.Flags.Enum flags) { return new Texture(create_texture_2(self, type.value, format.value, size.self, layers, flags.value)); }
	public Texture createTexture(Texture.Type type, Format format, Size size, int layers, Texture.Flags.Enum flags) { return new Texture(create_texture_2(self, type.value, format.value, size.self, layers, flags.value)); }
	public Texture createTexture(Texture.Type type, Format format, Size size) { return new Texture(create_texture_3(self, type.value, format.value, size.self, Texture.Flags.Default.value)); }
	public Texture createTexture(Texture.Type.Enum type, Format format, Size size) { return new Texture(create_texture_3(self, type.value, format.value, size.self, Texture.Flags.Default.value)); }
	public Texture createTexture(Texture.Type.Enum type, Format.Enum format, Size size) { return new Texture(create_texture_3(self, type.value, format.value, size.self, Texture.Flags.Default.value)); }
	public Texture createTexture(Texture.Type type, Format.Enum format, Size size) { return new Texture(create_texture_3(self, type.value, format.value, size.self, Texture.Flags.Default.value)); }
	public Texture createTexture(Texture.Type type, Format format, Size size, Texture.Flags flags) { return new Texture(create_texture_3(self, type.value, format.value, size.self, flags.value)); }
	public Texture createTexture(Texture.Type.Enum type, Format format, Size size, Texture.Flags flags) { return new Texture(create_texture_3(self, type.value, format.value, size.self, flags.value)); }
	public Texture createTexture(Texture.Type.Enum type, Format.Enum format, Size size, Texture.Flags flags) { return new Texture(create_texture_3(self, type.value, format.value, size.self, flags.value)); }
	public Texture createTexture(Texture.Type.Enum type, Format format, Size size, Texture.Flags.Enum flags) { return new Texture(create_texture_3(self, type.value, format.value, size.self, flags.value)); }
	public Texture createTexture(Texture.Type type, Format.Enum format, Size size, Texture.Flags flags) { return new Texture(create_texture_3(self, type.value, format.value, size.self, flags.value)); }
	public Texture createTexture(Texture.Type type, Format.Enum format, Size size, Texture.Flags.Enum flags) { return new Texture(create_texture_3(self, type.value, format.value, size.self, flags.value)); }
	public Texture createTexture(Texture.Type type, Format format, Size size, Texture.Flags.Enum flags) { return new Texture(create_texture_3(self, type.value, format.value, size.self, flags.value)); }
	public Texture createTexture(Image image) { return new Texture(create_texture_4(self, image.self, Texture.Flags.Default.value, 0)); }
	public Texture createTexture(Image image, Texture.Flags flags) { return new Texture(create_texture_4(self, image.self, flags.value, 0)); }
	public Texture createTexture(Image image, Texture.Flags.Enum flags) { return new Texture(create_texture_4(self, image.self, flags.value, 0)); }
	public Texture createTexture(Image image, Texture.Flags flags, Async async) { return new Texture(create_texture_4(self, image.self, flags.value, async.self)); }
	public Texture createTexture(Image image, Texture.Flags.Enum flags, Async async) { return new Texture(create_texture_4(self, image.self, flags.value, async.self)); }
	public Texture createTexture2D(Format format, int size) { return new Texture(create_texture2d(self, format.value, size, Texture.Flags.Default.value)); }
	public Texture createTexture2D(Format.Enum format, int size) { return new Texture(create_texture2d(self, format.value, size, Texture.Flags.Default.value)); }
	public Texture createTexture2D(Format format, int size, Texture.Flags flags) { return new Texture(create_texture2d(self, format.value, size, flags.value)); }
	public Texture createTexture2D(Format.Enum format, int size, Texture.Flags flags) { return new Texture(create_texture2d(self, format.value, size, flags.value)); }
	public Texture createTexture2D(Format.Enum format, int size, Texture.Flags.Enum flags) { return new Texture(create_texture2d(self, format.value, size, flags.value)); }
	public Texture createTexture2D(Format format, int size, Texture.Flags.Enum flags) { return new Texture(create_texture2d(self, format.value, size, flags.value)); }
	public Texture createTexture3D(Format format, int size) { return new Texture(create_texture3d(self, format.value, size, Texture.Flags.Default.value)); }
	public Texture createTexture3D(Format.Enum format, int size) { return new Texture(create_texture3d(self, format.value, size, Texture.Flags.Default.value)); }
	public Texture createTexture3D(Format format, int size, Texture.Flags flags) { return new Texture(create_texture3d(self, format.value, size, flags.value)); }
	public Texture createTexture3D(Format.Enum format, int size, Texture.Flags flags) { return new Texture(create_texture3d(self, format.value, size, flags.value)); }
	public Texture createTexture3D(Format.Enum format, int size, Texture.Flags.Enum flags) { return new Texture(create_texture3d(self, format.value, size, flags.value)); }
	public Texture createTexture3D(Format format, int size, Texture.Flags.Enum flags) { return new Texture(create_texture3d(self, format.value, size, flags.value)); }
	public Texture createTextureCube(Format format, int size) { return new Texture(create_texture_cube(self, format.value, size, Texture.Flags.Default.value)); }
	public Texture createTextureCube(Format.Enum format, int size) { return new Texture(create_texture_cube(self, format.value, size, Texture.Flags.Default.value)); }
	public Texture createTextureCube(Format format, int size, Texture.Flags flags) { return new Texture(create_texture_cube(self, format.value, size, flags.value)); }
	public Texture createTextureCube(Format.Enum format, int size, Texture.Flags flags) { return new Texture(create_texture_cube(self, format.value, size, flags.value)); }
	public Texture createTextureCube(Format.Enum format, int size, Texture.Flags.Enum flags) { return new Texture(create_texture_cube(self, format.value, size, flags.value)); }
	public Texture createTextureCube(Format format, int size, Texture.Flags.Enum flags) { return new Texture(create_texture_cube(self, format.value, size, flags.value)); }
	public Texture createTexture2D(Format format, int width, int height) { return new Texture(create_texture2d_1(self, format.value, width, height, Texture.Flags.Default.value)); }
	public Texture createTexture2D(Format.Enum format, int width, int height) { return new Texture(create_texture2d_1(self, format.value, width, height, Texture.Flags.Default.value)); }
	public Texture createTexture2D(Format format, int width, int height, Texture.Flags flags) { return new Texture(create_texture2d_1(self, format.value, width, height, flags.value)); }
	public Texture createTexture2D(Format.Enum format, int width, int height, Texture.Flags flags) { return new Texture(create_texture2d_1(self, format.value, width, height, flags.value)); }
	public Texture createTexture2D(Format.Enum format, int width, int height, Texture.Flags.Enum flags) { return new Texture(create_texture2d_1(self, format.value, width, height, flags.value)); }
	public Texture createTexture2D(Format format, int width, int height, Texture.Flags.Enum flags) { return new Texture(create_texture2d_1(self, format.value, width, height, flags.value)); }
	public Texture createTexture3D(Format format, int width, int height, int depth) { return new Texture(create_texture3d_1(self, format.value, width, height, depth, Texture.Flags.Default.value)); }
	public Texture createTexture3D(Format.Enum format, int width, int height, int depth) { return new Texture(create_texture3d_1(self, format.value, width, height, depth, Texture.Flags.Default.value)); }
	public Texture createTexture3D(Format format, int width, int height, int depth, Texture.Flags flags) { return new Texture(create_texture3d_1(self, format.value, width, height, depth, flags.value)); }
	public Texture createTexture3D(Format.Enum format, int width, int height, int depth, Texture.Flags flags) { return new Texture(create_texture3d_1(self, format.value, width, height, depth, flags.value)); }
	public Texture createTexture3D(Format.Enum format, int width, int height, int depth, Texture.Flags.Enum flags) { return new Texture(create_texture3d_1(self, format.value, width, height, depth, flags.value)); }
	public Texture createTexture3D(Format format, int width, int height, int depth, Texture.Flags.Enum flags) { return new Texture(create_texture3d_1(self, format.value, width, height, depth, flags.value)); }
	public Texture createTexture2D(Format format, int width, int height, int layers) { return new Texture(create_texture2d_2(self, format.value, width, height, layers, Texture.Flags.Default.value)); }
	public Texture createTexture2D(Format.Enum format, int width, int height, int layers) { return new Texture(create_texture2d_2(self, format.value, width, height, layers, Texture.Flags.Default.value)); }
	public Texture createTexture2D(Format format, int width, int height, int layers, Texture.Flags flags) { return new Texture(create_texture2d_2(self, format.value, width, height, layers, flags.value)); }
	public Texture createTexture2D(Format.Enum format, int width, int height, int layers, Texture.Flags flags) { return new Texture(create_texture2d_2(self, format.value, width, height, layers, flags.value)); }
	public Texture createTexture2D(Format.Enum format, int width, int height, int layers, Texture.Flags.Enum flags) { return new Texture(create_texture2d_2(self, format.value, width, height, layers, flags.value)); }
	public Texture createTexture2D(Format format, int width, int height, int layers, Texture.Flags.Enum flags) { return new Texture(create_texture2d_2(self, format.value, width, height, layers, flags.value)); }
	public Texture createTextureCube(Format format, int size, int layers) { return new Texture(create_texture_cube_1(self, format.value, size, layers, Texture.Flags.Default.value)); }
	public Texture createTextureCube(Format.Enum format, int size, int layers) { return new Texture(create_texture_cube_1(self, format.value, size, layers, Texture.Flags.Default.value)); }
	public Texture createTextureCube(Format format, int size, int layers, Texture.Flags flags) { return new Texture(create_texture_cube_1(self, format.value, size, layers, flags.value)); }
	public Texture createTextureCube(Format.Enum format, int size, int layers, Texture.Flags flags) { return new Texture(create_texture_cube_1(self, format.value, size, layers, flags.value)); }
	public Texture createTextureCube(Format.Enum format, int size, int layers, Texture.Flags.Enum flags) { return new Texture(create_texture_cube_1(self, format.value, size, layers, flags.value)); }
	public Texture createTextureCube(Format format, int size, int layers, Texture.Flags.Enum flags) { return new Texture(create_texture_cube_1(self, format.value, size, layers, flags.value)); }
	public Texture loadTexture(String name) { return new Texture(load_texture(self, name, Texture.Flags.Default.value, Image.Flags.None.value, 0, 0)); }
	public Texture loadTexture(String name, Texture.Flags flags) { return new Texture(load_texture(self, name, flags.value, Image.Flags.None.value, 0, 0)); }
	public Texture loadTexture(String name, Texture.Flags.Enum flags) { return new Texture(load_texture(self, name, flags.value, Image.Flags.None.value, 0, 0)); }
	public Texture loadTexture(String name, Texture.Flags flags, Image.Flags image_flags) { return new Texture(load_texture(self, name, flags.value, image_flags.value, 0, 0)); }
	public Texture loadTexture(String name, Texture.Flags.Enum flags, Image.Flags image_flags) { return new Texture(load_texture(self, name, flags.value, image_flags.value, 0, 0)); }
	public Texture loadTexture(String name, Texture.Flags.Enum flags, Image.Flags.Enum image_flags) { return new Texture(load_texture(self, name, flags.value, image_flags.value, 0, 0)); }
	public Texture loadTexture(String name, Texture.Flags flags, Image.Flags.Enum image_flags) { return new Texture(load_texture(self, name, flags.value, image_flags.value, 0, 0)); }
	public Texture loadTexture(String name, Texture.Flags flags, Image.Flags image_flags, int offset) { return new Texture(load_texture(self, name, flags.value, image_flags.value, offset, 0)); }
	public Texture loadTexture(String name, Texture.Flags.Enum flags, Image.Flags image_flags, int offset) { return new Texture(load_texture(self, name, flags.value, image_flags.value, offset, 0)); }
	public Texture loadTexture(String name, Texture.Flags.Enum flags, Image.Flags.Enum image_flags, int offset) { return new Texture(load_texture(self, name, flags.value, image_flags.value, offset, 0)); }
	public Texture loadTexture(String name, Texture.Flags flags, Image.Flags.Enum image_flags, int offset) { return new Texture(load_texture(self, name, flags.value, image_flags.value, offset, 0)); }
	public Texture loadTexture(String name, Texture.Flags flags, Image.Flags image_flags, int offset, Async async) { return new Texture(load_texture(self, name, flags.value, image_flags.value, offset, async.self)); }
	public Texture loadTexture(String name, Texture.Flags.Enum flags, Image.Flags image_flags, int offset, Async async) { return new Texture(load_texture(self, name, flags.value, image_flags.value, offset, async.self)); }
	public Texture loadTexture(String name, Texture.Flags.Enum flags, Image.Flags.Enum image_flags, int offset, Async async) { return new Texture(load_texture(self, name, flags.value, image_flags.value, offset, async.self)); }
	public Texture loadTexture(String name, Texture.Flags flags, Image.Flags.Enum image_flags, int offset, Async async) { return new Texture(load_texture(self, name, flags.value, image_flags.value, offset, async.self)); }
	public Texture loadTexture(TSString name) { return new Texture(load_texture_1(self, name.self, Texture.Flags.Default.value, Image.Flags.None.value, 0, 0)); }
	public Texture loadTexture(TSString name, Texture.Flags flags) { return new Texture(load_texture_1(self, name.self, flags.value, Image.Flags.None.value, 0, 0)); }
	public Texture loadTexture(TSString name, Texture.Flags.Enum flags) { return new Texture(load_texture_1(self, name.self, flags.value, Image.Flags.None.value, 0, 0)); }
	public Texture loadTexture(TSString name, Texture.Flags flags, Image.Flags image_flags) { return new Texture(load_texture_1(self, name.self, flags.value, image_flags.value, 0, 0)); }
	public Texture loadTexture(TSString name, Texture.Flags.Enum flags, Image.Flags image_flags) { return new Texture(load_texture_1(self, name.self, flags.value, image_flags.value, 0, 0)); }
	public Texture loadTexture(TSString name, Texture.Flags.Enum flags, Image.Flags.Enum image_flags) { return new Texture(load_texture_1(self, name.self, flags.value, image_flags.value, 0, 0)); }
	public Texture loadTexture(TSString name, Texture.Flags flags, Image.Flags.Enum image_flags) { return new Texture(load_texture_1(self, name.self, flags.value, image_flags.value, 0, 0)); }
	public Texture loadTexture(TSString name, Texture.Flags flags, Image.Flags image_flags, int offset) { return new Texture(load_texture_1(self, name.self, flags.value, image_flags.value, offset, 0)); }
	public Texture loadTexture(TSString name, Texture.Flags.Enum flags, Image.Flags image_flags, int offset) { return new Texture(load_texture_1(self, name.self, flags.value, image_flags.value, offset, 0)); }
	public Texture loadTexture(TSString name, Texture.Flags.Enum flags, Image.Flags.Enum image_flags, int offset) { return new Texture(load_texture_1(self, name.self, flags.value, image_flags.value, offset, 0)); }
	public Texture loadTexture(TSString name, Texture.Flags flags, Image.Flags.Enum image_flags, int offset) { return new Texture(load_texture_1(self, name.self, flags.value, image_flags.value, offset, 0)); }
	public Texture loadTexture(TSString name, Texture.Flags flags, Image.Flags image_flags, int offset, Async async) { return new Texture(load_texture_1(self, name.self, flags.value, image_flags.value, offset, async.self)); }
	public Texture loadTexture(TSString name, Texture.Flags.Enum flags, Image.Flags image_flags, int offset, Async async) { return new Texture(load_texture_1(self, name.self, flags.value, image_flags.value, offset, async.self)); }
	public Texture loadTexture(TSString name, Texture.Flags.Enum flags, Image.Flags.Enum image_flags, int offset, Async async) { return new Texture(load_texture_1(self, name.self, flags.value, image_flags.value, offset, async.self)); }
	public Texture loadTexture(TSString name, Texture.Flags flags, Image.Flags.Enum image_flags, int offset, Async async) { return new Texture(load_texture_1(self, name.self, flags.value, image_flags.value, offset, async.self)); }
	public Texture loadTexture(Stream stream) { return new Texture(load_texture_2(self, stream.self, Texture.Flags.Default.value, Image.Flags.None.value, 0, 0)); }
	public Texture loadTexture(Stream stream, Texture.Flags flags) { return new Texture(load_texture_2(self, stream.self, flags.value, Image.Flags.None.value, 0, 0)); }
	public Texture loadTexture(Stream stream, Texture.Flags.Enum flags) { return new Texture(load_texture_2(self, stream.self, flags.value, Image.Flags.None.value, 0, 0)); }
	public Texture loadTexture(Stream stream, Texture.Flags flags, Image.Flags image_flags) { return new Texture(load_texture_2(self, stream.self, flags.value, image_flags.value, 0, 0)); }
	public Texture loadTexture(Stream stream, Texture.Flags.Enum flags, Image.Flags image_flags) { return new Texture(load_texture_2(self, stream.self, flags.value, image_flags.value, 0, 0)); }
	public Texture loadTexture(Stream stream, Texture.Flags.Enum flags, Image.Flags.Enum image_flags) { return new Texture(load_texture_2(self, stream.self, flags.value, image_flags.value, 0, 0)); }
	public Texture loadTexture(Stream stream, Texture.Flags flags, Image.Flags.Enum image_flags) { return new Texture(load_texture_2(self, stream.self, flags.value, image_flags.value, 0, 0)); }
	public Texture loadTexture(Stream stream, Texture.Flags flags, Image.Flags image_flags, int offset) { return new Texture(load_texture_2(self, stream.self, flags.value, image_flags.value, offset, 0)); }
	public Texture loadTexture(Stream stream, Texture.Flags.Enum flags, Image.Flags image_flags, int offset) { return new Texture(load_texture_2(self, stream.self, flags.value, image_flags.value, offset, 0)); }
	public Texture loadTexture(Stream stream, Texture.Flags.Enum flags, Image.Flags.Enum image_flags, int offset) { return new Texture(load_texture_2(self, stream.self, flags.value, image_flags.value, offset, 0)); }
	public Texture loadTexture(Stream stream, Texture.Flags flags, Image.Flags.Enum image_flags, int offset) { return new Texture(load_texture_2(self, stream.self, flags.value, image_flags.value, offset, 0)); }
	public Texture loadTexture(Stream stream, Texture.Flags flags, Image.Flags image_flags, int offset, Async async) { return new Texture(load_texture_2(self, stream.self, flags.value, image_flags.value, offset, async.self)); }
	public Texture loadTexture(Stream stream, Texture.Flags.Enum flags, Image.Flags image_flags, int offset, Async async) { return new Texture(load_texture_2(self, stream.self, flags.value, image_flags.value, offset, async.self)); }
	public Texture loadTexture(Stream stream, Texture.Flags.Enum flags, Image.Flags.Enum image_flags, int offset, Async async) { return new Texture(load_texture_2(self, stream.self, flags.value, image_flags.value, offset, async.self)); }
	public Texture loadTexture(Stream stream, Texture.Flags flags, Image.Flags.Enum image_flags, int offset, Async async) { return new Texture(load_texture_2(self, stream.self, flags.value, image_flags.value, offset, async.self)); }
	public Tracing createTracing() { return new Tracing(create_tracing(self)); }
	public Tracing createTracing(Tracing tracing) { return new Tracing(create_tracing_1(self, tracing.self)); }
	public Tracing createTracing(int num_instances) { return new Tracing(create_tracing_2(self, num_instances, (new Buffer()).self, 0, Tracing.Flags.Default.value)); }
	public Tracing createTracing(int num_instances, Buffer instance_buffer) { return new Tracing(create_tracing_2(self, num_instances, instance_buffer.self, 0, Tracing.Flags.Default.value)); }
	public Tracing createTracing(int num_instances, Buffer instance_buffer, long instance_offset) { return new Tracing(create_tracing_2(self, num_instances, instance_buffer.self, instance_offset, Tracing.Flags.Default.value)); }
	public Tracing createTracing(int num_instances, Buffer instance_buffer, long instance_offset, Tracing.Flags flags) { return new Tracing(create_tracing_2(self, num_instances, instance_buffer.self, instance_offset, flags.value)); }
	public Tracing createTracing(int num_instances, Buffer instance_buffer, long instance_offset, Tracing.Flags.Enum flags) { return new Tracing(create_tracing_2(self, num_instances, instance_buffer.self, instance_offset, flags.value)); }
	public Tracing createTracing(int num_vertices, Format vertex_format, long vertex_stride, int num_indices, Format index_format) { return new Tracing(create_tracing_3(self, num_vertices, vertex_format.value, vertex_stride, num_indices, index_format.value, Tracing.Flags.Default.value)); }
	public Tracing createTracing(int num_vertices, Format.Enum vertex_format, long vertex_stride, int num_indices, Format index_format) { return new Tracing(create_tracing_3(self, num_vertices, vertex_format.value, vertex_stride, num_indices, index_format.value, Tracing.Flags.Default.value)); }
	public Tracing createTracing(int num_vertices, Format.Enum vertex_format, long vertex_stride, int num_indices, Format.Enum index_format) { return new Tracing(create_tracing_3(self, num_vertices, vertex_format.value, vertex_stride, num_indices, index_format.value, Tracing.Flags.Default.value)); }
	public Tracing createTracing(int num_vertices, Format vertex_format, long vertex_stride, int num_indices, Format.Enum index_format) { return new Tracing(create_tracing_3(self, num_vertices, vertex_format.value, vertex_stride, num_indices, index_format.value, Tracing.Flags.Default.value)); }
	public Tracing createTracing(int num_vertices, Format vertex_format, long vertex_stride, int num_indices, Format index_format, Tracing.Flags flags) { return new Tracing(create_tracing_3(self, num_vertices, vertex_format.value, vertex_stride, num_indices, index_format.value, flags.value)); }
	public Tracing createTracing(int num_vertices, Format.Enum vertex_format, long vertex_stride, int num_indices, Format index_format, Tracing.Flags flags) { return new Tracing(create_tracing_3(self, num_vertices, vertex_format.value, vertex_stride, num_indices, index_format.value, flags.value)); }
	public Tracing createTracing(int num_vertices, Format.Enum vertex_format, long vertex_stride, int num_indices, Format.Enum index_format, Tracing.Flags flags) { return new Tracing(create_tracing_3(self, num_vertices, vertex_format.value, vertex_stride, num_indices, index_format.value, flags.value)); }
	public Tracing createTracing(int num_vertices, Format.Enum vertex_format, long vertex_stride, int num_indices, Format index_format, Tracing.Flags.Enum flags) { return new Tracing(create_tracing_3(self, num_vertices, vertex_format.value, vertex_stride, num_indices, index_format.value, flags.value)); }
	public Tracing createTracing(int num_vertices, Format vertex_format, long vertex_stride, int num_indices, Format.Enum index_format, Tracing.Flags flags) { return new Tracing(create_tracing_3(self, num_vertices, vertex_format.value, vertex_stride, num_indices, index_format.value, flags.value)); }
	public Tracing createTracing(int num_vertices, Format vertex_format, long vertex_stride, int num_indices, Format.Enum index_format, Tracing.Flags.Enum flags) { return new Tracing(create_tracing_3(self, num_vertices, vertex_format.value, vertex_stride, num_indices, index_format.value, flags.value)); }
	public Tracing createTracing(int num_vertices, Format vertex_format, long vertex_stride, int num_indices, Format index_format, Tracing.Flags.Enum flags) { return new Tracing(create_tracing_3(self, num_vertices, vertex_format.value, vertex_stride, num_indices, index_format.value, flags.value)); }
	public Tracing createTracing(int num_bounds, long bound_stride) { return new Tracing(create_tracing_4(self, num_bounds, bound_stride, (new Buffer()).self, 0, Tracing.Flags.Default.value)); }
	public Tracing createTracing(int num_bounds, long bound_stride, Buffer bound_buffer) { return new Tracing(create_tracing_4(self, num_bounds, bound_stride, bound_buffer.self, 0, Tracing.Flags.Default.value)); }
	public Tracing createTracing(int num_bounds, long bound_stride, Buffer bound_buffer, long bound_offset) { return new Tracing(create_tracing_4(self, num_bounds, bound_stride, bound_buffer.self, bound_offset, Tracing.Flags.Default.value)); }
	public Tracing createTracing(int num_bounds, long bound_stride, Buffer bound_buffer, long bound_offset, Tracing.Flags flags) { return new Tracing(create_tracing_4(self, num_bounds, bound_stride, bound_buffer.self, bound_offset, flags.value)); }
	public Tracing createTracing(int num_bounds, long bound_stride, Buffer bound_buffer, long bound_offset, Tracing.Flags.Enum flags) { return new Tracing(create_tracing_4(self, num_bounds, bound_stride, bound_buffer.self, bound_offset, flags.value)); }
	public BufferTable createBufferTable() { return new BufferTable(create_buffer_table(self)); }
	public BufferTable createBufferTable(int size) { return new BufferTable(create_buffer_table_1(self, size)); }
	public BufferTable createBufferTable(Buffer[] buffers) { return new BufferTable(create_buffer_table_2(self, Buffer.self_(buffers), false)); }
	public BufferTable createBufferTable(Buffer[] buffers, boolean owner) { return new BufferTable(create_buffer_table_2(self, Buffer.self_(buffers), owner)); }
	public TextureTable createTextureTable() { return new TextureTable(create_texture_table(self)); }
	public TextureTable createTextureTable(Texture.Type type, int size) { return new TextureTable(create_texture_table_1(self, type.value, size)); }
	public TextureTable createTextureTable(Texture.Type.Enum type, int size) { return new TextureTable(create_texture_table_1(self, type.value, size)); }
	public TextureTable createTextureTable(Texture[] textures) { return new TextureTable(create_texture_table_2(self, Texture.self_(textures), false)); }
	public TextureTable createTextureTable(Texture[] textures, boolean owner) { return new TextureTable(create_texture_table_2(self, Texture.self_(textures), owner)); }
	public Shader createShader() { return new Shader(create_shader(self)); }
	public Shader loadShader(Shader.Type type, String name, String format) { return new Shader(load_shader(self, type.value, name, format)); }
	public Shader loadShader(Shader.Type.Enum type, String name, String format) { return new Shader(load_shader(self, type.value, name, format)); }
	public Shader loadShaderGLSL(Shader.Type type, String name, String format) { return new Shader(load_shader_glsl(self, type.value, name, format)); }
	public Shader loadShaderGLSL(Shader.Type.Enum type, String name, String format) { return new Shader(load_shader_glsl(self, type.value, name, format)); }
	public Shader loadShader(Shader.Type type, String name) { return new Shader(load_shader_1(self, type.value, name, (new TSString()).self)); }
	public Shader loadShader(Shader.Type.Enum type, String name) { return new Shader(load_shader_1(self, type.value, name, (new TSString()).self)); }
	public Shader loadShader(Shader.Type type, String name, TSString macros) { return new Shader(load_shader_1(self, type.value, name, macros.self)); }
	public Shader loadShader(Shader.Type.Enum type, String name, TSString macros) { return new Shader(load_shader_1(self, type.value, name, macros.self)); }
	public Shader loadShaderGLSL(Shader.Type type, String name) { return new Shader(load_shader_glsl_1(self, type.value, name, (new TSString()).self)); }
	public Shader loadShaderGLSL(Shader.Type.Enum type, String name) { return new Shader(load_shader_glsl_1(self, type.value, name, (new TSString()).self)); }
	public Shader loadShaderGLSL(Shader.Type type, String name, TSString macros) { return new Shader(load_shader_glsl_1(self, type.value, name, macros.self)); }
	public Shader loadShaderGLSL(Shader.Type.Enum type, String name, TSString macros) { return new Shader(load_shader_glsl_1(self, type.value, name, macros.self)); }
	public Shader loadShaderSPIRV(Shader.Type type, String name) { return new Shader(load_shader_spirv(self, type.value, name)); }
	public Shader loadShaderSPIRV(Shader.Type.Enum type, String name) { return new Shader(load_shader_spirv(self, type.value, name)); }
	public Shader createShader(Shader.Type type, String src, String format) { return new Shader(create_shader_1(self, type.value, src, format)); }
	public Shader createShader(Shader.Type.Enum type, String src, String format) { return new Shader(create_shader_1(self, type.value, src, format)); }
	public Shader createShaderGLSL(Shader.Type type, String src, String format) { return new Shader(create_shader_glsl(self, type.value, src, format)); }
	public Shader createShaderGLSL(Shader.Type.Enum type, String src, String format) { return new Shader(create_shader_glsl(self, type.value, src, format)); }
	public Shader createShader(Shader.Type type, String src) { return new Shader(create_shader_2(self, type.value, src, (new TSString()).self)); }
	public Shader createShader(Shader.Type.Enum type, String src) { return new Shader(create_shader_2(self, type.value, src, (new TSString()).self)); }
	public Shader createShader(Shader.Type type, String src, TSString macros) { return new Shader(create_shader_2(self, type.value, src, macros.self)); }
	public Shader createShader(Shader.Type.Enum type, String src, TSString macros) { return new Shader(create_shader_2(self, type.value, src, macros.self)); }
	public Shader createShaderGLSL(Shader.Type type, String src) { return new Shader(create_shader_glsl_1(self, type.value, src, (new TSString()).self)); }
	public Shader createShaderGLSL(Shader.Type.Enum type, String src) { return new Shader(create_shader_glsl_1(self, type.value, src, (new TSString()).self)); }
	public Shader createShaderGLSL(Shader.Type type, String src, TSString macros) { return new Shader(create_shader_glsl_1(self, type.value, src, macros.self)); }
	public Shader createShaderGLSL(Shader.Type.Enum type, String src, TSString macros) { return new Shader(create_shader_glsl_1(self, type.value, src, macros.self)); }
	public Shader createShaderSPIRV(Shader.Type type, int[] data) { return new Shader(create_shader_spirv(self, type.value, data)); }
	public Shader createShaderSPIRV(Shader.Type.Enum type, int[] data) { return new Shader(create_shader_spirv(self, type.value, data)); }
	public Kernel createKernel() { return new Kernel(create_kernel(self)); }
	public Kernel createKernel(Kernel kernel) { return new Kernel(create_kernel_1(self, kernel.self)); }
	public void releaseKernel(Kernel kernel) { release_kernel(self, kernel.self); }
	public Pipeline createPipeline() { return new Pipeline(create_pipeline(self)); }
	public Pipeline createPipeline(Pipeline pipeline) { return new Pipeline(create_pipeline_1(self, pipeline.self)); }
	public void releasePipeline(Pipeline pipeline) { release_pipeline(self, pipeline.self); }
	public Traversal createTraversal() { return new Traversal(create_traversal(self)); }
	public Traversal createTraversal(Traversal traversal) { return new Traversal(create_traversal_1(self, traversal.self)); }
	public void releaseTraversal(Traversal traversal) { release_traversal(self, traversal.self); }
	public Target createTarget() { return new Target(create_target(self)); }
	public Target createTarget(Surface surface) { return new Target(create_target_1(self, surface.self)); }
	public Target createTarget(Window window) { return new Target(create_target_2(self, window.self)); }
	public Compute createCompute() { return new Compute(create_compute(self)); }
	public Command createCommand() { return new Command(create_command(self)); }
	public Command createCommand(Target target) { return new Command(create_command_1(self, target.self)); }
	public boolean setBuffer(Buffer buffer, long offset, byte[] src) { return set_buffer(self, buffer.self, offset, src); }
	public boolean setBuffer(Buffer buffer, byte[] src) { return set_buffer_1(self, buffer.self, src); }
	public boolean setBuffer(Buffer buffer, long src) { return set_buffer_2(self, buffer.self, src); }
	public boolean getBuffer(Buffer buffer, long offset, byte[] dest) { return get_buffer(self, buffer.self, offset, dest); }
	public boolean getBuffer(Buffer buffer, byte[] dest) { return get_buffer_1(self, buffer.self, dest); }
	public boolean getBuffer(Buffer buffer, long dest) { return get_buffer_2(self, buffer.self, dest); }
	public long mapBuffer(Buffer buffer, long offset, long size) { return map_buffer(self, buffer.self, offset, size); }
	public long mapBuffer(Buffer buffer, long size) { return map_buffer_1(self, buffer.self, size); }
	public long mapBuffer(Buffer buffer) { return map_buffer_2(self, buffer.self); }
	public boolean unmapBuffer(Buffer buffer) { return unmap_buffer(self, buffer.self); }
	public boolean copyBuffer(Buffer buffer, long dest_offset, Buffer src, long src_offset, long size) { return copy_buffer(self, buffer.self, dest_offset, src.self, src_offset, size); }
	public boolean copyBuffer(Buffer buffer, long dest_offset, Buffer src, long size) { return copy_buffer_1(self, buffer.self, dest_offset, src.self, size); }
	public boolean copyBuffer(Buffer buffer, Buffer src, long size) { return copy_buffer_2(self, buffer.self, src.self, size); }
	public boolean copyBuffer(Buffer buffer, Buffer src) { return copy_buffer_3(self, buffer.self, src.self); }
	public boolean clearBuffer(Buffer buffer, Format format, long offset, byte[] src) { return clear_buffer(self, buffer.self, format.value, offset, src); }
	public boolean clearBuffer(Buffer buffer, Format.Enum format, long offset, byte[] src) { return clear_buffer(self, buffer.self, format.value, offset, src); }
	public boolean clearBuffer(Buffer buffer, Format format, byte[] src) { return clear_buffer_1(self, buffer.self, format.value, src); }
	public boolean clearBuffer(Buffer buffer, Format.Enum format, byte[] src) { return clear_buffer_1(self, buffer.self, format.value, src); }
	public boolean clearBuffer(Buffer buffer, Format format, long src) { return clear_buffer_2(self, buffer.self, format.value, src); }
	public boolean clearBuffer(Buffer buffer, Format.Enum format, long src) { return clear_buffer_2(self, buffer.self, format.value, src); }
	public boolean clearBuffer(Buffer buffer) { return clear_buffer_3(self, buffer.self); }
	public boolean bindBuffer(Buffer buffer, long[] offsets, long[] sizes, boolean commit, Fence fence) { return bind_buffer(self, buffer.self, offsets, sizes, commit, fence.self); }
	public boolean bindBuffer(Buffer buffer, long[] offsets, long[] sizes, boolean commit) { return bind_buffer_1(self, buffer.self, offsets, sizes, commit); }
	public boolean bindBuffer(Buffer buffer, long offset, long size, boolean commit, Fence fence) { return bind_buffer_2(self, buffer.self, offset, size, commit, fence.self); }
	public boolean bindBuffer(Buffer buffer, long offset, long size, boolean commit) { return bind_buffer_3(self, buffer.self, offset, size, commit); }
	public boolean flushBuffer(Buffer buffer) { return flush_buffer(self, buffer.self, Buffer.Flags.None.value); }
	public boolean flushBuffer(Buffer buffer, Buffer.Flags flags) { return flush_buffer(self, buffer.self, flags.value); }
	public boolean flushBuffer(Buffer buffer, Buffer.Flags.Enum flags) { return flush_buffer(self, buffer.self, flags.value); }
	public boolean flushBuffers(Buffer[] buffers) { return flush_buffers(self, Buffer.self_(buffers), Buffer.Flags.None.value); }
	public boolean flushBuffers(Buffer[] buffers, Buffer.Flags flags) { return flush_buffers(self, Buffer.self_(buffers), flags.value); }
	public boolean flushBuffers(Buffer[] buffers, Buffer.Flags.Enum flags) { return flush_buffers(self, Buffer.self_(buffers), flags.value); }
	public void releaseBuffer(Buffer buffer) { release_buffer(self, buffer.self); }
	public void releaseSampler(Sampler sampler) { release_sampler(self, sampler.self); }
	public boolean setTexture(Texture texture, Origin dest_origin, Slice dest_slice, Image image, Slice src_slice) { return set_texture(self, texture.self, dest_origin.self, dest_slice.self, image.self, src_slice.self); }
	public boolean setTexture(Texture texture, Origin dest_origin, Image image) { return set_texture_1(self, texture.self, dest_origin.self, image.self); }
	public boolean setTexture(Texture texture, Slice dest_slice, Image image) { return set_texture_2(self, texture.self, dest_slice.self, image.self); }
	public boolean setTexture(Texture texture, Image image) { return set_texture_3(self, texture.self, image.self); }
	public boolean getTexture(Texture texture, Slice src_slice, Image image, Slice dest_slice) { return get_texture(self, texture.self, src_slice.self, image.self, dest_slice.self); }
	public boolean getTexture(Texture texture, Image image, Slice dest_slice) { return get_texture_1(self, texture.self, image.self, dest_slice.self); }
	public boolean getTexture(Texture texture, Image image) { return get_texture_2(self, texture.self, image.self); }
	public boolean copyTexture(Texture texture, Origin dest_origin, Slice dest_slice, Texture src, Region src_region, Slice src_slice) { return copy_texture(self, texture.self, dest_origin.self, dest_slice.self, src.self, src_region.self, src_slice.self); }
	public boolean copyTexture(Texture texture, Origin dest_origin, Texture src, Region src_region) { return copy_texture_1(self, texture.self, dest_origin.self, src.self, src_region.self); }
	public boolean copyTexture(Texture texture, Slice dest_slice, Texture src, Slice src_slice) { return copy_texture_2(self, texture.self, dest_slice.self, src.self, src_slice.self); }
	public boolean copyTexture(Texture texture, Texture src) { return copy_texture_3(self, texture.self, src.self); }
	public boolean clearTexture(Texture texture, Region region, Slice slice, long src) { return clear_texture(self, texture.self, region.self, slice.self, src); }
	public boolean clearTexture(Texture texture, Region region, long src) { return clear_texture_1(self, texture.self, region.self, src); }
	public boolean clearTexture(Texture texture, Slice slice, long src) { return clear_texture_2(self, texture.self, slice.self, src); }
	public boolean clearTexture(Texture texture, long src) { return clear_texture_3(self, texture.self, src); }
	public boolean bindTexture(Texture texture, Region[] regions, Slice[] slices, boolean commit, Fence fence) { return bind_texture(self, texture.self, Region.self_(regions), Slice.self_(slices), commit, fence.self); }
	public boolean bindTexture(Texture texture, Region[] regions, Slice[] slices, boolean commit) { return bind_texture_1(self, texture.self, Region.self_(regions), Slice.self_(slices), commit); }
	public boolean bindTexture(Texture texture, Region region, Slice slice, boolean commit, Fence fence) { return bind_texture_2(self, texture.self, region.self, slice.self, commit, fence.self); }
	public boolean bindTexture(Texture texture, Region region, Slice slice, boolean commit) { return bind_texture_3(self, texture.self, region.self, slice.self, commit); }
	public boolean createMipmaps(Texture texture, Slice slice) { return create_mipmaps(self, texture.self, slice.self); }
	public boolean createMipmaps(Texture texture) { return create_mipmaps_1(self, texture.self); }
	public boolean flushTexture(Texture texture) { return flush_texture(self, texture.self, Texture.Flags.None.value); }
	public boolean flushTexture(Texture texture, Texture.Flags flags) { return flush_texture(self, texture.self, flags.value); }
	public boolean flushTexture(Texture texture, Texture.Flags.Enum flags) { return flush_texture(self, texture.self, flags.value); }
	public boolean flushTexture(Texture texture, Slice slice) { return flush_texture_1(self, texture.self, slice.self, Texture.Flags.None.value); }
	public boolean flushTexture(Texture texture, Slice slice, Texture.Flags flags) { return flush_texture_1(self, texture.self, slice.self, flags.value); }
	public boolean flushTexture(Texture texture, Slice slice, Texture.Flags.Enum flags) { return flush_texture_1(self, texture.self, slice.self, flags.value); }
	public boolean flushTextures(Texture[] textures) { return flush_textures(self, Texture.self_(textures), Texture.Flags.None.value); }
	public boolean flushTextures(Texture[] textures, Texture.Flags flags) { return flush_textures(self, Texture.self_(textures), flags.value); }
	public boolean flushTextures(Texture[] textures, Texture.Flags.Enum flags) { return flush_textures(self, Texture.self_(textures), flags.value); }
	public void releaseTexture(Texture texture) { release_texture(self, texture.self); }
	public boolean setTracing(Tracing tracing, Tracing.Instance[] instances) { return set_tracing(self, tracing.self, Tracing.Instance.self_(instances)); }
	public boolean buildTracing(Tracing tracing, Buffer buffer) { return build_tracing(self, tracing.self, buffer.self, Tracing.Flags.None.value); }
	public boolean buildTracing(Tracing tracing, Buffer buffer, Tracing.Flags flags) { return build_tracing(self, tracing.self, buffer.self, flags.value); }
	public boolean buildTracing(Tracing tracing, Buffer buffer, Tracing.Flags.Enum flags) { return build_tracing(self, tracing.self, buffer.self, flags.value); }
	public boolean buildTracing(Tracing tracing, Buffer buffer, long offset) { return build_tracing_1(self, tracing.self, buffer.self, offset, Tracing.Flags.None.value); }
	public boolean buildTracing(Tracing tracing, Buffer buffer, long offset, Tracing.Flags flags) { return build_tracing_1(self, tracing.self, buffer.self, offset, flags.value); }
	public boolean buildTracing(Tracing tracing, Buffer buffer, long offset, Tracing.Flags.Enum flags) { return build_tracing_1(self, tracing.self, buffer.self, offset, flags.value); }
	public boolean buildTracings(Tracing[] tracings, Buffer buffer) { return build_tracings(self, Tracing.self_(tracings), buffer.self, Tracing.Flags.None.value); }
	public boolean buildTracings(Tracing[] tracings, Buffer buffer, Tracing.Flags flags) { return build_tracings(self, Tracing.self_(tracings), buffer.self, flags.value); }
	public boolean buildTracings(Tracing[] tracings, Buffer buffer, Tracing.Flags.Enum flags) { return build_tracings(self, Tracing.self_(tracings), buffer.self, flags.value); }
	public boolean buildTracings(Tracing[] tracings, Buffer buffer, long offset) { return build_tracings_1(self, Tracing.self_(tracings), buffer.self, offset, Tracing.Flags.None.value); }
	public boolean buildTracings(Tracing[] tracings, Buffer buffer, long offset, Tracing.Flags flags) { return build_tracings_1(self, Tracing.self_(tracings), buffer.self, offset, flags.value); }
	public boolean buildTracings(Tracing[] tracings, Buffer buffer, long offset, Tracing.Flags.Enum flags) { return build_tracings_1(self, Tracing.self_(tracings), buffer.self, offset, flags.value); }
	public boolean copyTracing(Tracing tracing, Buffer buffer) { return copy_tracing(self, tracing.self, buffer.self, 0); }
	public boolean copyTracing(Tracing tracing, Buffer buffer, long offset) { return copy_tracing(self, tracing.self, buffer.self, offset); }
	public boolean copyTracings(Tracing[] tracings, Buffer buffer, long offset) { return copy_tracings(self, Tracing.self_(tracings), buffer.self, offset, 0); }
	public boolean copyTracings(Tracing[] tracings, Buffer buffer, long offset, long stride) { return copy_tracings(self, Tracing.self_(tracings), buffer.self, offset, stride); }
	public boolean flushTracing(Tracing tracing) { return flush_tracing(self, tracing.self); }
	public boolean flushTracings(Tracing[] tracings) { return flush_tracings(self, Tracing.self_(tracings)); }
	public void releaseTracing(Tracing tracing) { release_tracing(self, tracing.self); }
	public boolean setBufferTable(BufferTable table, int index, Buffer buffer) { return set_buffer_table(self, table.self, index, buffer.self, false); }
	public boolean setBufferTable(BufferTable table, int index, Buffer buffer, boolean owner) { return set_buffer_table(self, table.self, index, buffer.self, owner); }
	public boolean setBufferTable(BufferTable table, int index, Buffer[] buffers) { return set_buffer_table_1(self, table.self, index, Buffer.self_(buffers), false); }
	public boolean setBufferTable(BufferTable table, int index, Buffer[] buffers, boolean owner) { return set_buffer_table_1(self, table.self, index, Buffer.self_(buffers), owner); }
	public void releaseBufferTable(BufferTable table) { release_buffer_table(self, table.self); }
	public boolean setTextureTable(TextureTable table, int index, Texture texture) { return set_texture_table(self, table.self, index, texture.self, false); }
	public boolean setTextureTable(TextureTable table, int index, Texture texture, boolean owner) { return set_texture_table(self, table.self, index, texture.self, owner); }
	public boolean setTextureTable(TextureTable table, int index, Texture[] textures) { return set_texture_table_1(self, table.self, index, Texture.self_(textures), false); }
	public boolean setTextureTable(TextureTable table, int index, Texture[] textures, boolean owner) { return set_texture_table_1(self, table.self, index, Texture.self_(textures), owner); }
	public void releaseTextureTable(TextureTable table) { release_texture_table(self, table.self); }
	public boolean beginQuery(Query query) { return begin_query(self, query.self); }
	public void endQuery(Query query) { end_query(self, query.self); }
	public boolean copyQuery(Query query, Buffer buffer) { return copy_query(self, query.self, buffer.self, 0); }
	public boolean copyQuery(Query query, Buffer buffer, long offset) { return copy_query(self, query.self, buffer.self, offset); }
	public boolean copyQueries(Query[] queries, Buffer buffer) { return copy_queries(self, Query.self_(queries), buffer.self, 0, 0); }
	public boolean copyQueries(Query[] queries, Buffer buffer, long offset) { return copy_queries(self, Query.self_(queries), buffer.self, offset, 0); }
	public boolean copyQueries(Query[] queries, Buffer buffer, long offset, long stride) { return copy_queries(self, Query.self_(queries), buffer.self, offset, stride); }
	public boolean waitFence(Fence fence) { return wait_fence(self, fence.self); }
	public boolean signalFence(Fence fence) { return signal_fence(self, fence.self); }
	public boolean execute(Device device) { return execute_(self, device.self); }
	public boolean flip(Fence fence) { return flip_(self, fence.self); }
	public boolean flip() { return flip_1(self); }
	public boolean flush() { return flush_(self); }
	public boolean finish() { return finish_(self); }
	public boolean check() { return check_(self); }
	
	private static native long new_();
	private static native long new_1(long context);
	private static native long new_2(long surface);
	private static native long new_3(long window);
	private static native void delete_(long self);
	private static native boolean equal_ptr(long self, long ptr);
	private static native long clone_ptr(long self);
	private static native void clear_ptr(long self);
	private static native void destroy_ptr(long self);
	private static native void acquire_ptr(long self);
	private static native void unacquire_ptr(long self);
	private static native boolean is_valid_ptr(long self);
	private static native boolean is_owner_ptr(long self);
	private static native boolean is_const_ptr(long self);
	private static native int get_count_ptr(long self);
	private static native long get_internal_ptr(long self);
	private static native int get_platform(long self);
	private static native String get_platform_name(long self);
	private static native int get_index(long self);
	private static native String get_name(long self);
	private static native String get_vendor(long self);
	private static native String get_version(long self);
	private static native long get_features(long self);
	private static native boolean has_query(long self, int type);
	private static native boolean has_shader(long self, int type);
	private static native boolean has_target(long self, int format);
	private static native boolean has_texture(long self, int format);
	private static native boolean has_surface(long self, int format);
	private static native long create_device(long self, int index, int frames);
	private static native long create_command_device(long self, int frames);
	private static native long create_compute_device(long self, int frames);
	private static native long create_copy_device(long self, int frames);
	private static native long create_query(long self);
	private static native long create_query_1(long self, int type);
	private static native long create_fence(long self);
	private static native long create_fence_1(long self, long shared);
	private static native long create_fence_2(long self, int flags);
	private static native long create_buffer(long self);
	private static native long create_buffer_1(long self, long shared);
	private static native long create_buffer_2(long self, int flags, long size, int format);
	private static native long create_buffer_3(long self, int flags, byte[] src, int format);
	private static native long create_sampler(long self);
	private static native long create_sampler_1(long self, long sampler);
	private static native long create_sampler_2(long self, int filter, int mode, int anisotropy);
	private static native long create_texture(long self);
	private static native long create_texture_1(long self, long shared);
	private static native long create_texture_2(long self, int type, int format, long size, int layers, int flags);
	private static native long create_texture_3(long self, int type, int format, long size, int flags);
	private static native long create_texture_4(long self, long image, int flags, long async);
	private static native long create_texture2d(long self, int format, int size, int flags);
	private static native long create_texture3d(long self, int format, int size, int flags);
	private static native long create_texture_cube(long self, int format, int size, int flags);
	private static native long create_texture2d_1(long self, int format, int width, int height, int flags);
	private static native long create_texture3d_1(long self, int format, int width, int height, int depth, int flags);
	private static native long create_texture2d_2(long self, int format, int width, int height, int layers, int flags);
	private static native long create_texture_cube_1(long self, int format, int size, int layers, int flags);
	private static native long load_texture(long self, String name, int flags, int image_flags, int offset, long async);
	private static native long load_texture_1(long self, long name, int flags, int image_flags, int offset, long async);
	private static native long load_texture_2(long self, long stream, int flags, int image_flags, int offset, long async);
	private static native long create_tracing(long self);
	private static native long create_tracing_1(long self, long tracing);
	private static native long create_tracing_2(long self, int num_instances, long instance_buffer, long instance_offset, int flags);
	private static native long create_tracing_3(long self, int num_vertices, int vertex_format, long vertex_stride, int num_indices, int index_format, int flags);
	private static native long create_tracing_4(long self, int num_bounds, long bound_stride, long bound_buffer, long bound_offset, int flags);
	private static native long create_buffer_table(long self);
	private static native long create_buffer_table_1(long self, int size);
	private static native long create_buffer_table_2(long self, long[] buffers, boolean owner);
	private static native long create_texture_table(long self);
	private static native long create_texture_table_1(long self, int type, int size);
	private static native long create_texture_table_2(long self, long[] textures, boolean owner);
	private static native long create_shader(long self);
	private static native long load_shader(long self, int type, String name, String format);
	private static native long load_shader_glsl(long self, int type, String name, String format);
	private static native long load_shader_1(long self, int type, String name, long macros);
	private static native long load_shader_glsl_1(long self, int type, String name, long macros);
	private static native long load_shader_spirv(long self, int type, String name);
	private static native long create_shader_1(long self, int type, String src, String format);
	private static native long create_shader_glsl(long self, int type, String src, String format);
	private static native long create_shader_2(long self, int type, String src, long macros);
	private static native long create_shader_glsl_1(long self, int type, String src, long macros);
	private static native long create_shader_spirv(long self, int type, int[] data);
	private static native long create_kernel(long self);
	private static native long create_kernel_1(long self, long kernel);
	private static native void release_kernel(long self, long kernel);
	private static native long create_pipeline(long self);
	private static native long create_pipeline_1(long self, long pipeline);
	private static native void release_pipeline(long self, long pipeline);
	private static native long create_traversal(long self);
	private static native long create_traversal_1(long self, long traversal);
	private static native void release_traversal(long self, long traversal);
	private static native long create_target(long self);
	private static native long create_target_1(long self, long surface);
	private static native long create_target_2(long self, long window);
	private static native long create_compute(long self);
	private static native long create_command(long self);
	private static native long create_command_1(long self, long target);
	private static native boolean set_buffer(long self, long buffer, long offset, byte[] src);
	private static native boolean set_buffer_1(long self, long buffer, byte[] src);
	private static native boolean set_buffer_2(long self, long buffer, long src);
	private static native boolean get_buffer(long self, long buffer, long offset, byte[] dest);
	private static native boolean get_buffer_1(long self, long buffer, byte[] dest);
	private static native boolean get_buffer_2(long self, long buffer, long dest);
	private static native long map_buffer(long self, long buffer, long offset, long size);
	private static native long map_buffer_1(long self, long buffer, long size);
	private static native long map_buffer_2(long self, long buffer);
	private static native boolean unmap_buffer(long self, long buffer);
	private static native boolean copy_buffer(long self, long buffer, long dest_offset, long src, long src_offset, long size);
	private static native boolean copy_buffer_1(long self, long buffer, long dest_offset, long src, long size);
	private static native boolean copy_buffer_2(long self, long buffer, long src, long size);
	private static native boolean copy_buffer_3(long self, long buffer, long src);
	private static native boolean clear_buffer(long self, long buffer, int format, long offset, byte[] src);
	private static native boolean clear_buffer_1(long self, long buffer, int format, byte[] src);
	private static native boolean clear_buffer_2(long self, long buffer, int format, long src);
	private static native boolean clear_buffer_3(long self, long buffer);
	private static native boolean bind_buffer(long self, long buffer, long[] offsets, long[] sizes, boolean commit, long fence);
	private static native boolean bind_buffer_1(long self, long buffer, long[] offsets, long[] sizes, boolean commit);
	private static native boolean bind_buffer_2(long self, long buffer, long offset, long size, boolean commit, long fence);
	private static native boolean bind_buffer_3(long self, long buffer, long offset, long size, boolean commit);
	private static native boolean flush_buffer(long self, long buffer, int flags);
	private static native boolean flush_buffers(long self, long[] buffers, int flags);
	private static native void release_buffer(long self, long buffer);
	private static native void release_sampler(long self, long sampler);
	private static native boolean set_texture(long self, long texture, long dest_origin, long dest_slice, long image, long src_slice);
	private static native boolean set_texture_1(long self, long texture, long dest_origin, long image);
	private static native boolean set_texture_2(long self, long texture, long dest_slice, long image);
	private static native boolean set_texture_3(long self, long texture, long image);
	private static native boolean get_texture(long self, long texture, long src_slice, long image, long dest_slice);
	private static native boolean get_texture_1(long self, long texture, long image, long dest_slice);
	private static native boolean get_texture_2(long self, long texture, long image);
	private static native boolean copy_texture(long self, long texture, long dest_origin, long dest_slice, long src, long src_region, long src_slice);
	private static native boolean copy_texture_1(long self, long texture, long dest_origin, long src, long src_region);
	private static native boolean copy_texture_2(long self, long texture, long dest_slice, long src, long src_slice);
	private static native boolean copy_texture_3(long self, long texture, long src);
	private static native boolean clear_texture(long self, long texture, long region, long slice, long src);
	private static native boolean clear_texture_1(long self, long texture, long region, long src);
	private static native boolean clear_texture_2(long self, long texture, long slice, long src);
	private static native boolean clear_texture_3(long self, long texture, long src);
	private static native boolean bind_texture(long self, long texture, long[] regions, long[] slices, boolean commit, long fence);
	private static native boolean bind_texture_1(long self, long texture, long[] regions, long[] slices, boolean commit);
	private static native boolean bind_texture_2(long self, long texture, long region, long slice, boolean commit, long fence);
	private static native boolean bind_texture_3(long self, long texture, long region, long slice, boolean commit);
	private static native boolean create_mipmaps(long self, long texture, long slice);
	private static native boolean create_mipmaps_1(long self, long texture);
	private static native boolean flush_texture(long self, long texture, int flags);
	private static native boolean flush_texture_1(long self, long texture, long slice, int flags);
	private static native boolean flush_textures(long self, long[] textures, int flags);
	private static native void release_texture(long self, long texture);
	private static native boolean set_tracing(long self, long tracing, long[] instances);
	private static native boolean build_tracing(long self, long tracing, long buffer, int flags);
	private static native boolean build_tracing_1(long self, long tracing, long buffer, long offset, int flags);
	private static native boolean build_tracings(long self, long[] tracings, long buffer, int flags);
	private static native boolean build_tracings_1(long self, long[] tracings, long buffer, long offset, int flags);
	private static native boolean copy_tracing(long self, long tracing, long buffer, long offset);
	private static native boolean copy_tracings(long self, long[] tracings, long buffer, long offset, long stride);
	private static native boolean flush_tracing(long self, long tracing);
	private static native boolean flush_tracings(long self, long[] tracings);
	private static native void release_tracing(long self, long tracing);
	private static native boolean set_buffer_table(long self, long table, int index, long buffer, boolean owner);
	private static native boolean set_buffer_table_1(long self, long table, int index, long[] buffers, boolean owner);
	private static native void release_buffer_table(long self, long table);
	private static native boolean set_texture_table(long self, long table, int index, long texture, boolean owner);
	private static native boolean set_texture_table_1(long self, long table, int index, long[] textures, boolean owner);
	private static native void release_texture_table(long self, long table);
	private static native boolean begin_query(long self, long query);
	private static native void end_query(long self, long query);
	private static native boolean copy_query(long self, long query, long buffer, long offset);
	private static native boolean copy_queries(long self, long[] queries, long buffer, long offset, long stride);
	private static native boolean wait_fence(long self, long fence);
	private static native boolean signal_fence(long self, long fence);
	private static native boolean execute_(long self, long device);
	private static native boolean flip_(long self, long fence);
	private static native boolean flip_1(long self);
	private static native boolean flush_(long self);
	private static native boolean finish_(long self);
	private static native boolean check_(long self);
	
	protected Device(long self) {
		init_(self);
	}
	public static Device Null() {
		return new Device((long)0);
	}
	protected void init_(long self) {
		if(self != 0) cleaner.register(this, new Destructor(self));
		this.self = self;
	}
	protected static long[] self_(Device[] ptr) {
		long[] self = new long[ptr.length];
		for(int i = 0; i < ptr.length; i++) self[i] = ptr[i].self;
		return self;
	}
	private static class Destructor implements Runnable {
		Destructor(long self) { this.self = self; }
		public void run() { delete_(self); }
		private long self;
	}
	
	private static Cleaner cleaner = Cleaner.create();
	
	protected long self;
}

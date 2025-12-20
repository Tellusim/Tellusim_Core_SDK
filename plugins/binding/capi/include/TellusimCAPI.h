// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_C_API_H__
#define __TELLUSIM_C_API_H__

#include "TellusimCBase.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Tellusim Handles
typedef struct TSString_t *TSString;
typedef struct TSApp_t *TSApp;
typedef struct TSAsync_t *TSAsync;
typedef struct TSStream_t *TSStream;
typedef struct TSBlob_t *TSBlob;
typedef struct TSFile_t *TSFile;
typedef struct TSSocket_t *TSSocket;
typedef struct TSSocketSSL_t *TSSocketSSL;
typedef struct TSSource_t *TSSource;
typedef struct TSDate_t *TSDate;
typedef struct TSInfo_t *TSInfo;
typedef struct TSDirectory_t *TSDirectory;
typedef struct TSArchive_t *TSArchive;
typedef struct TSImage_t *TSImage;
typedef struct TSImageSampler_t *TSImageSampler;
typedef struct TSMeshNode_t *TSMeshNode;
typedef struct TSMeshIndices_t *TSMeshIndices;
typedef struct TSMeshAttribute_t *TSMeshAttribute;
typedef struct TSMeshJoint_t *TSMeshJoint;
typedef struct TSMeshMaterial_t *TSMeshMaterial;
typedef struct TSMeshGeometry_t *TSMeshGeometry;
typedef struct TSMeshTransform_t *TSMeshTransform;
typedef struct TSMeshAnimation_t *TSMeshAnimation;
typedef struct TSMeshAttachment_t *TSMeshAttachment;
typedef struct TSMesh_t *TSMesh;
typedef struct TSJson_t *TSJson;
typedef struct TSXml_t *TSXml;
typedef struct TSBuffer_t *TSBuffer;
typedef struct TSBufferTable_t *TSBufferTable;
typedef struct TSD3D12Buffer_t *TSD3D12Buffer;
typedef struct TSD3D11Buffer_t *TSD3D11Buffer;
typedef struct TSMTLBuffer_t *TSMTLBuffer;
typedef struct TSVKBuffer_t *TSVKBuffer;
typedef struct TSGLBuffer_t *TSGLBuffer;
typedef struct TSGLESBuffer_t *TSGLESBuffer;
typedef struct TSCUBuffer_t *TSCUBuffer;
typedef struct TSHIPBuffer_t *TSHIPBuffer;
typedef struct TSFUBuffer_t *TSFUBuffer;
typedef struct TSCommand_t *TSCommand;
typedef struct TSD3D12Command_t *TSD3D12Command;
typedef struct TSMTLCommand_t *TSMTLCommand;
typedef struct TSVKCommand_t *TSVKCommand;
typedef struct TSFUCommand_t *TSFUCommand;
typedef struct TSCompute_t *TSCompute;
typedef struct TSD3D12Compute_t *TSD3D12Compute;
typedef struct TSMTLCompute_t *TSMTLCompute;
typedef struct TSVKCompute_t *TSVKCompute;
typedef struct TSFUCompute_t *TSFUCompute;
typedef struct TSContext_t *TSContext;
typedef struct TSD3D12Context_t *TSD3D12Context;
typedef struct TSD3D11Context_t *TSD3D11Context;
typedef struct TSMTLContext_t *TSMTLContext;
typedef struct TSVKContext_t *TSVKContext;
typedef struct TSGLContext_t *TSGLContext;
typedef struct TSGLESContext_t *TSGLESContext;
typedef struct TSWGContext_t *TSWGContext;
typedef struct TSCUContext_t *TSCUContext;
typedef struct TSHIPContext_t *TSHIPContext;
typedef struct TSQuery_t *TSQuery;
typedef struct TSFUQuery_t *TSFUQuery;
typedef struct TSFence_t *TSFence;
typedef struct TSVKFence_t *TSVKFence;
typedef struct TSFUFence_t *TSFUFence;
typedef struct TSShader_t *TSShader;
typedef struct TSShaderCompiler_t *TSShaderCompiler;
typedef struct TSD3D12Shader_t *TSD3D12Shader;
typedef struct TSD3D11Shader_t *TSD3D11Shader;
typedef struct TSMTLShader_t *TSMTLShader;
typedef struct TSVKShader_t *TSVKShader;
typedef struct TSGLShader_t *TSGLShader;
typedef struct TSGLESShader_t *TSGLESShader;
typedef struct TSCUShader_t *TSCUShader;
typedef struct TSHIPShader_t *TSHIPShader;
typedef struct TSFUShader_t *TSFUShader;
typedef struct TSSampler_t *TSSampler;
typedef struct TSMTLSampler_t *TSMTLSampler;
typedef struct TSFUSampler_t *TSFUSampler;
typedef struct TSTexture_t *TSTexture;
typedef struct TSTextureTable_t *TSTextureTable;
typedef struct TSD3D12Texture_t *TSD3D12Texture;
typedef struct TSD3D11Texture_t *TSD3D11Texture;
typedef struct TSMTLTexture_t *TSMTLTexture;
typedef struct TSVKTexture_t *TSVKTexture;
typedef struct TSGLTexture_t *TSGLTexture;
typedef struct TSGLESTexture_t *TSGLESTexture;
typedef struct TSCUTexture_t *TSCUTexture;
typedef struct TSHIPTexture_t *TSHIPTexture;
typedef struct TSFUTexture_t *TSFUTexture;
typedef struct TSTracing_t *TSTracing;
typedef struct TSD3D12Tracing_t *TSD3D12Tracing;
typedef struct TSMTLTracing_t *TSMTLTracing;
typedef struct TSVKTracing_t *TSVKTracing;
typedef struct TSFUTracing_t *TSFUTracing;
typedef struct TSTarget_t *TSTarget;
typedef struct TSD3D12Target_t *TSD3D12Target;
typedef struct TSD3D11Target_t *TSD3D11Target;
typedef struct TSMTLTarget_t *TSMTLTarget;
typedef struct TSVKTarget_t *TSVKTarget;
typedef struct TSGLTarget_t *TSGLTarget;
typedef struct TSGLESTarget_t *TSGLESTarget;
typedef struct TSFUTarget_t *TSFUTarget;
typedef struct TSDevice_t *TSDevice;
typedef struct TSD3D12Device_t *TSD3D12Device;
typedef struct TSD3D11Device_t *TSD3D11Device;
typedef struct TSMTLDevice_t *TSMTLDevice;
typedef struct TSVKDevice_t *TSVKDevice;
typedef struct TSFUDevice_t *TSFUDevice;
typedef struct TSKernel_t *TSKernel;
typedef struct TSD3D12Kernel_t *TSD3D12Kernel;
typedef struct TSMTLKernel_t *TSMTLKernel;
typedef struct TSFUKernel_t *TSFUKernel;
typedef struct TSPipeline_t *TSPipeline;
typedef struct TSD3D12Pipeline_t *TSD3D12Pipeline;
typedef struct TSMTLPipeline_t *TSMTLPipeline;
typedef struct TSFUPipeline_t *TSFUPipeline;
typedef struct TSTraversal_t *TSTraversal;
typedef struct TSD3D12Traversal_t *TSD3D12Traversal;
typedef struct TSFUTraversal_t *TSFUTraversal;
typedef struct TSSurface_t *TSSurface;
typedef struct TSD3D12Surface_t *TSD3D12Surface;
typedef struct TSD3D11Surface_t *TSD3D11Surface;
typedef struct TSMTLSurface_t *TSMTLSurface;
typedef struct TSVKSurface_t *TSVKSurface;
typedef struct TSGLSurface_t *TSGLSurface;
typedef struct TSGLESSurface_t *TSGLESSurface;
typedef struct TSWindow_t *TSWindow;
typedef struct TSFont_t *TSFont;
typedef struct TSCanvasElement_t *TSCanvasElement;
typedef struct TSCanvasText_t *TSCanvasText;
typedef struct TSCanvasMesh_t *TSCanvasMesh;
typedef struct TSCanvasRect_t *TSCanvasRect;
typedef struct TSCanvasTriangle_t *TSCanvasTriangle;
typedef struct TSCanvasEllipse_t *TSCanvasEllipse;
typedef struct TSCanvasShape_t *TSCanvasShape;
typedef struct TSCanvasStrip_t *TSCanvasStrip;
typedef struct TSCanvas_t *TSCanvas;
typedef struct TSControl_t *TSControl;
typedef struct TSControlRoot_t *TSControlRoot;
typedef struct TSControlText_t *TSControlText;
typedef struct TSControlRect_t *TSControlRect;
typedef struct TSControlGrid_t *TSControlGrid;
typedef struct TSControlGroup_t *TSControlGroup;
typedef struct TSControlPanel_t *TSControlPanel;
typedef struct TSControlDialog_t *TSControlDialog;
typedef struct TSControlWindow_t *TSControlWindow;
typedef struct TSControlCheck_t *TSControlCheck;
typedef struct TSControlCombo_t *TSControlCombo;
typedef struct TSControlButton_t *TSControlButton;
typedef struct TSControlSlider_t *TSControlSlider;
typedef struct TSControlScroll_t *TSControlScroll;
typedef struct TSControlSplit_t *TSControlSplit;
typedef struct TSControlArea_t *TSControlArea;
typedef struct TSControlTree_t *TSControlTree;
typedef struct TSControlEdit_t *TSControlEdit;
typedef struct TSDialogMessage_t *TSDialogMessage;
typedef struct TSDialogFileOpen_t *TSDialogFileOpen;
typedef struct TSDialogFileSave_t *TSDialogFileSave;
typedef struct TSDialogDirectory_t *TSDialogDirectory;
typedef struct TSDialogProgress_t *TSDialogProgress;
typedef struct TSDialogColor_t *TSDialogColor;
typedef struct TSDialogMenu_t *TSDialogMenu;
typedef struct TSCubeFilter_t *TSCubeFilter;
typedef struct TSDecoderJPEG_t *TSDecoderJPEG;
typedef struct TSEncoderBC15_t *TSEncoderBC15;
typedef struct TSEncoderBC67_t *TSEncoderBC67;
typedef struct TSEncoderASTC_t *TSEncoderASTC;
typedef struct TSMeshModel_t *TSMeshModel;
typedef struct TSSeparableFilter_t *TSSeparableFilter;
typedef struct TSPrefixScan_t *TSPrefixScan;
typedef struct TSRadixSort_t *TSRadixSort;
typedef struct TSBitonicSort_t *TSBitonicSort;
typedef struct TSSpatialGrid_t *TSSpatialGrid;
typedef struct TSSpatialTree_t *TSSpatialTree;
typedef struct TSFourierTransform_t *TSFourierTransform;
typedef struct TSTensorGraph_t *TSTensorGraph;
typedef struct TSController_t *TSController;
typedef struct TSDesktop_t *TSDesktop;

/// Tellusim::Vendor
typedef enum TS_Vendor {
	TS_VendorARM = 0x13b5,
	TS_VendorAMD = 0x1002,
	TS_VendorApple = 0x106b,
	TS_VendorIntel = 0x8086,
	TS_VendorNvidia = 0x10de,
	TS_VendorQualcomm = 0x5143,
	TS_Vendor_Maxi32 = 0x7fffffff,
} TS_Vendor;

/// Tellusim::Platform
typedef enum TS_Platform {
	TS_PlatformUnknown = 0,
	TS_PlatformFusion,
	TS_PlatformD3D12,
	TS_PlatformD3D11,
	TS_PlatformMTL,
	TS_PlatformVK,
	TS_PlatformGL,
	TS_PlatformGLES,
	TS_PlatformWG,
	TS_PlatformCU,
	TS_PlatformHIP,
	TS_PlatformAny,
	TS_PlatformNumPlatforms,
	TS_Platform_Maxi32 = 0x7fffffff,
} TS_Platform;

/// Tellusim::BindFlags
typedef enum TS_BindFlags {
	TS_BindBindFlagNone = 0,
	TS_BindBindFlagFixed = 1,
	TS_BindBindFlagRead = 2,
	TS_BindFlags_Maxi32 = 0x7fffffff,
} TS_BindFlags;

/// Tellusim::TableType
typedef enum TS_TableType {
	TS_TableTypeTexture = 0,
	TS_TableTypeStorage,
	TS_TableTypeNumTableTypes,
	TS_TableType_Maxi32 = 0x7fffffff,
} TS_TableType;

/// Tellusim::Format
typedef enum TS_Format {
	TS_FormatUnknown = 0,
	TS_FormatRi8,
	TS_FormatRu8,
	TS_FormatRi8n,
	TS_FormatRu8n,
	TS_FormatRGi8,
	TS_FormatRGu8,
	TS_FormatRGi8n,
	TS_FormatRGu8n,
	TS_FormatRGBi8,
	TS_FormatRGBu8,
	TS_FormatRGBi8n,
	TS_FormatRGBu8n,
	TS_FormatRGBu8ns,
	TS_FormatRGBAi8,
	TS_FormatRGBAu8,
	TS_FormatRGBAi8n,
	TS_FormatRGBAu8n,
	TS_FormatRGBAu8ns,
	TS_FormatBGRAu8n,
	TS_FormatBGRAu8ns,
	TS_FormatRi16,
	TS_FormatRu16,
	TS_FormatRi16n,
	TS_FormatRu16n,
	TS_FormatRf16,
	TS_FormatRGi16,
	TS_FormatRGu16,
	TS_FormatRGi16n,
	TS_FormatRGu16n,
	TS_FormatRGf16,
	TS_FormatRGBi16,
	TS_FormatRGBu16,
	TS_FormatRGBi16n,
	TS_FormatRGBu16n,
	TS_FormatRGBf16,
	TS_FormatRGBAi16,
	TS_FormatRGBAu16,
	TS_FormatRGBAi16n,
	TS_FormatRGBAu16n,
	TS_FormatRGBAf16,
	TS_FormatRi32,
	TS_FormatRu32,
	TS_FormatRf32,
	TS_FormatRGi32,
	TS_FormatRGu32,
	TS_FormatRGf32,
	TS_FormatRGBi32,
	TS_FormatRGBu32,
	TS_FormatRGBf32,
	TS_FormatRGBAi32,
	TS_FormatRGBAu32,
	TS_FormatRGBAf32,
	TS_FormatRi64,
	TS_FormatRu64,
	TS_FormatRf64,
	TS_FormatRGi64,
	TS_FormatRGu64,
	TS_FormatRGf64,
	TS_FormatRGBi64,
	TS_FormatRGBu64,
	TS_FormatRGBf64,
	TS_FormatRGBAi64,
	TS_FormatRGBAu64,
	TS_FormatRGBAf64,
	TS_FormatRGBAu4n,
	TS_FormatRGBu5Au1n,
	TS_FormatRu5Gu6Bu5n,
	TS_FormatRGBu10Au2,
	TS_FormatRGBu10Au2n,
	TS_FormatRGf11Bf10,
	TS_FormatRGBf9Eu5,
	TS_FormatRGBf21,
	TS_FormatBC1RGBu8n,
	TS_FormatBC1RGBu8ns,
	TS_FormatBC1RGBAu8n,
	TS_FormatBC1RGBAu8ns,
	TS_FormatBC2RGBAu8n,
	TS_FormatBC2RGBAu8ns,
	TS_FormatBC3RGBAu8n,
	TS_FormatBC3RGBAu8ns,
	TS_FormatBC4Ri8n,
	TS_FormatBC4Ru8n,
	TS_FormatBC5RGi8n,
	TS_FormatBC5RGu8n,
	TS_FormatBC6RGBf16s,
	TS_FormatBC6RGBf16u,
	TS_FormatBC7RGBAu8n,
	TS_FormatBC7RGBAu8ns,
	TS_FormatEACRi8n,
	TS_FormatEACRu8n,
	TS_FormatEACRGi8n,
	TS_FormatEACRGu8n,
	TS_FormatETC2RGBu8n,
	TS_FormatETC2RGBu8ns,
	TS_FormatETC2RGBAu8n,
	TS_FormatETC2RGBAu8ns,
	TS_FormatETC2RGBu8Au1n,
	TS_FormatETC2RGBu8Au1ns,
	TS_FormatASTC44RGBAu8n,
	TS_FormatASTC44RGBAu8ns,
	TS_FormatASTC44RGBAf16,
	TS_FormatASTC54RGBAu8n,
	TS_FormatASTC54RGBAu8ns,
	TS_FormatASTC54RGBAf16,
	TS_FormatASTC55RGBAu8n,
	TS_FormatASTC55RGBAu8ns,
	TS_FormatASTC55RGBAf16,
	TS_FormatASTC65RGBAu8n,
	TS_FormatASTC65RGBAu8ns,
	TS_FormatASTC65RGBAf16,
	TS_FormatASTC66RGBAu8n,
	TS_FormatASTC66RGBAu8ns,
	TS_FormatASTC66RGBAf16,
	TS_FormatASTC85RGBAu8n,
	TS_FormatASTC85RGBAu8ns,
	TS_FormatASTC85RGBAf16,
	TS_FormatASTC86RGBAu8n,
	TS_FormatASTC86RGBAu8ns,
	TS_FormatASTC86RGBAf16,
	TS_FormatASTC88RGBAu8n,
	TS_FormatASTC88RGBAu8ns,
	TS_FormatASTC88RGBAf16,
	TS_FormatDu16,
	TS_FormatDu16Su8,
	TS_FormatDu24,
	TS_FormatDu24Su8,
	TS_FormatDf32,
	TS_FormatDf32Su8,
	TS_FormatNumFormats,
	TS_Format_Maxi32 = 0x7fffffff,
} TS_Format;

/// Tellusim::App::
typedef enum TS_App {
	TS_AppVersion_19 = 20221010,
	TS_AppVersion_20 = 20221109,
	TS_AppVersion_21 = 20221122,
	TS_AppVersion_22 = 20221222,
	TS_AppVersion_23 = 20230117,
	TS_AppVersion_24 = 20230217,
	TS_AppVersion_25 = 20230402,
	TS_AppVersion_26 = 20230509,
	TS_AppVersion_27 = 20230612,
	TS_AppVersion_28 = 20230718,
	TS_AppVersion_29 = 20230824,
	TS_AppVersion_30 = 20231029,
	TS_AppVersion_31 = 20231113,
	TS_AppVersion_32 = 20231212,
	TS_AppVersion_33 = 20240116,
	TS_AppVersion_34 = 20240216,
	TS_AppVersion_35 = 20240320,
	TS_AppVersion_36 = 20240427,
	TS_AppVersion_37 = 20240515,
	TS_AppVersion_38 = 20250215,
	TS_AppVersion_39 = 20250322,
	TS_AppVersion_40 = 20250429,
	TS_AppVersion_41 = 20250816,
	TS_AppVersion_42 = 20251102,
	TS_AppVersion_43 = 20251220,
	TS_AppVersion = 20251220,
	TS_App_Maxi32 = 0x7fffffff,
} TS_App;

/// Tellusim::Socket::Type
typedef enum TS_SocketType {
	TS_SocketTypeStream = 0,
	TS_SocketTypeDatagram,
	TS_SocketTypeNumTypes,
	TS_SocketType_Maxi32 = 0x7fffffff,
} TS_SocketType;

/// Tellusim::Directory::Attributes
typedef enum TS_DirectoryAttributes {
	TS_DirectoryAttributeNone = 0,
	TS_DirectoryAttributeRead = 1,
	TS_DirectoryAttributeWrite = 2,
	TS_DirectoryAttributeHidden = 4,
	TS_DirectoryAttributeExecute = 8,
	TS_DirectoryAttributeTemporary = 16,
	TS_DirectoryNumAttributes = 5,
	TS_DirectoryAttributes_Maxi32 = 0x7fffffff,
} TS_DirectoryAttributes;

/// Tellusim::Image::Type
typedef enum TS_ImageType {
	TS_ImageTypeUnknown = 0,
	TS_ImageType2D,
	TS_ImageType3D,
	TS_ImageTypeCube,
	TS_ImageTypeNumTypes,
	TS_ImageType_Maxi32 = 0x7fffffff,
} TS_ImageType;

/// Tellusim::Image::Flags
typedef enum TS_ImageFlags {
	TS_ImageFlagNone = 0,
	TS_ImageFlagMipmaps = 1,
	TS_ImageFlagNoClear = 2,
	TS_ImageFlagNoAllocate = 4,
	TS_ImageFlagFast = 8,
	TS_ImageFlagBest = 16,
	TS_ImageFlagPerceptual = 32,
	TS_ImageFlagPanorama = 64,
	TS_ImageFlagNormalize = 128,
	TS_ImageFlagGamma = 256,
	TS_ImageFlagSRGB = 512,
	TS_ImageNumFlags = 10,
	TS_ImageFlags_Maxi32 = 0x7fffffff,
} TS_ImageFlags;

/// Tellusim::Image::Filter
typedef enum TS_ImageFilter {
	TS_ImageFilterUnknown = 0,
	TS_ImageFilterPoint,
	TS_ImageFilterLinear,
	TS_ImageFilterCubic,
	TS_ImageFilterSinc,
	TS_ImageFilterBox,
	TS_ImageFilterMax,
	TS_ImageFilterMin,
	TS_ImageFilterMip,
	TS_ImageFilterCR,
	TS_ImageFilterNumFilters,
	TS_ImageFilter_Maxi32 = 0x7fffffff,
} TS_ImageFilter;

/// Tellusim::MeshIndices::Type
typedef enum TS_MeshIndicesType {
	TS_MeshIndicesTypeUnknown = 0,
	TS_MeshIndicesTypePoint,
	TS_MeshIndicesTypeLine,
	TS_MeshIndicesTypeTriangle,
	TS_MeshIndicesTypeQuadrilateral,
	TS_MeshIndicesTypeTetrahedron,
	TS_MeshIndicesTypeMaterial,
	TS_MeshIndicesTypeIsland,
	TS_MeshIndicesTypeGroup,
	TS_MeshIndicesTypeJoint,
	TS_MeshIndicesTypeEdge,
	TS_MeshIndicesTypeNumTypes,
	TS_MeshIndicesType_Maxi32 = 0x7fffffff,
} TS_MeshIndicesType;

/// Tellusim::MeshAttribute::Type
typedef enum TS_MeshAttributeType {
	TS_MeshAttributeTypeUnknown = 0,
	TS_MeshAttributeTypePosition,
	TS_MeshAttributeTypeBasis,
	TS_MeshAttributeTypeNormal,
	TS_MeshAttributeTypeTangent,
	TS_MeshAttributeTypeBinormal,
	TS_MeshAttributeTypeTexCoord,
	TS_MeshAttributeTypeWeights,
	TS_MeshAttributeTypeJoints,
	TS_MeshAttributeTypeColor,
	TS_MeshAttributeTypeCrease,
	TS_MeshAttributeTypeIndex,
	TS_MeshAttributeTypeNumTypes,
	TS_MeshAttributeType_Maxi32 = 0x7fffffff,
} TS_MeshAttributeType;

/// Tellusim::MeshMaterial::Flags
typedef enum TS_MeshMaterialFlags {
	TS_MeshMaterialFlagNone = 0,
	TS_MeshMaterialFlagBool = 1,
	TS_MeshMaterialFlagScalarf32 = 2,
	TS_MeshMaterialFlagVector4f = 4,
	TS_MeshMaterialFlagMatrix3x2f = 8,
	TS_MeshMaterialFlagColor = 16,
	TS_MeshMaterialFlagName = 32,
	TS_MeshMaterialFlagLayout = 64,
	TS_MeshMaterialFlagBlob = 128,
	TS_MeshMaterialFlagImage = 256,
	TS_MeshMaterialFlagTexture = 416,
	TS_MeshMaterialFlags_Maxi32 = 0x7fffffff,
} TS_MeshMaterialFlags;

/// Tellusim::MeshAttachment::Type
typedef enum TS_MeshAttachmentType {
	TS_MeshAttachmentTypeUnknown = 0,
	TS_MeshAttachmentTypeLightGlobal,
	TS_MeshAttachmentTypeLightPoint,
	TS_MeshAttachmentTypeLightSpot,
	TS_MeshAttachmentTypeLightImage,
	TS_MeshAttachmentTypeCameraPerspective,
	TS_MeshAttachmentTypeCameraOrthographic,
	TS_MeshAttachmentTypeNumTypes,
	TS_MeshAttachmentType_Maxi32 = 0x7fffffff,
} TS_MeshAttachmentType;

/// Tellusim::MeshAttachment::Flags
typedef enum TS_MeshAttachmentFlags {
	TS_MeshAttachmentFlagNone = 0,
	TS_MeshAttachmentFlagBool = 1,
	TS_MeshAttachmentFlagScalarf32 = 2,
	TS_MeshAttachmentFlagVector4f = 4,
	TS_MeshAttachmentFlagColor = 8,
	TS_MeshAttachmentFlagName = 16,
	TS_MeshAttachmentFlags_Maxi32 = 0x7fffffff,
} TS_MeshAttachmentFlags;

/// Tellusim::Mesh::Flags
typedef enum TS_MeshFlags {
	TS_MeshFlagNone = 0,
	TS_MeshFlagEmbed = 1,
	TS_MeshFlag32Bit = 2,
	TS_MeshFlags_Maxi32 = 0x7fffffff,
} TS_MeshFlags;

/// Tellusim::Mesh::Basis
typedef enum TS_MeshBasis {
	TS_MeshBasisUnknown = 0,
	TS_MeshBasisXUpRight,
	TS_MeshBasisYUpRight,
	TS_MeshBasisZUpRight,
	TS_MeshBasisXUpLeft,
	TS_MeshBasisYUpLeft,
	TS_MeshBasisZUpLeft,
	TS_MeshBasisZUpMaya,
	TS_MeshBasisNumBases,
	TS_MeshBasis_Maxi32 = 0x7fffffff,
} TS_MeshBasis;

/// Tellusim::Mesh::Axis
typedef enum TS_MeshAxis {
	TS_MeshAxisUnknown = 0,
	TS_MeshAxisPX,
	TS_MeshAxisPY,
	TS_MeshAxisPZ,
	TS_MeshAxisNX,
	TS_MeshAxisNY,
	TS_MeshAxisNZ,
	TS_MeshAxisNumAxes,
	TS_MeshAxis_Maxi32 = 0x7fffffff,
} TS_MeshAxis;

/// Tellusim::Json::Type
typedef enum TS_JsonType {
	TS_JsonTypeUnknown = 0,
	TS_JsonTypeNull,
	TS_JsonTypeBool,
	TS_JsonTypeNumber,
	TS_JsonTypeString,
	TS_JsonTypeObject,
	TS_JsonTypeArray,
	TS_JsonTypeNumTypes,
	TS_JsonType_Maxi32 = 0x7fffffff,
} TS_JsonType;

/// Tellusim::Buffer::Flags
typedef enum TS_BufferFlags {
	TS_BufferFlagNone = 0,
	TS_BufferFlagRead = 1,
	TS_BufferFlagWrite = 2,
	TS_BufferFlagSource = 4,
	TS_BufferFlagSparse = 8,
	TS_BufferFlagShared = 16,
	TS_BufferFlagMapped = 32,
	TS_BufferFlagExtern = 64,
	TS_BufferFlagInterop = 128,
	TS_BufferFlagDynamic = 256,
	TS_BufferFlagUniform = 512,
	TS_BufferFlagStorage = 1024,
	TS_BufferFlagAddress = 2048,
	TS_BufferFlagTracing = 4096,
	TS_BufferFlagScratch = 8192,
	TS_BufferFlagBinding = 16384,
	TS_BufferFlagIndirect = 32768,
	TS_BufferFlagConditional = 65536,
	TS_BufferFlagVertex = 131072,
	TS_BufferFlagIndex = 262144,
	TS_BufferFlagTexel = 524288,
	TS_BufferFlagAccel = 1048576,
	TS_BufferDefaultFlags = 0,
	TS_BufferNumFlags = 21,
	TS_BufferFlags_Maxi32 = 0x7fffffff,
} TS_BufferFlags;

/// Tellusim::Query::Type
typedef enum TS_QueryType {
	TS_QueryTypeUnknown = 0,
	TS_QueryTypeTime,
	TS_QueryTypeClock,
	TS_QueryTypeSamples,
	TS_QueryTypeSamples1,
	TS_QueryTypeStatistics,
	TS_QueryTypeNumTypes,
	TS_QueryType_Maxi32 = 0x7fffffff,
} TS_QueryType;

/// Tellusim::Fence::Flags
typedef enum TS_FenceFlags {
	TS_FenceFlagNone = 0,
	TS_FenceFlagSemaphore = 1,
	TS_FenceFlagSignaled = 2,
	TS_FenceFlagShared = 4,
	TS_FenceFlagExtern = 8,
	TS_FenceDefaultFlags = 0,
	TS_FenceNumFlags = 4,
	TS_FenceFlags_Maxi32 = 0x7fffffff,
} TS_FenceFlags;

/// Tellusim::Shader::Type
typedef enum TS_ShaderType {
	TS_ShaderTypeUnknown = 0,
	TS_ShaderTypeVertex,
	TS_ShaderTypeControl,
	TS_ShaderTypeEvaluate,
	TS_ShaderTypeGeometry,
	TS_ShaderTypeFragment,
	TS_ShaderTypeCompute,
	TS_ShaderTypeTask,
	TS_ShaderTypeMesh,
	TS_ShaderTypeRayGen,
	TS_ShaderTypeRayMiss,
	TS_ShaderTypeClosest,
	TS_ShaderTypeFirstHit,
	TS_ShaderTypeIntersection,
	TS_ShaderTypeCallable,
	TS_ShaderTypeNumTypes,
	TS_ShaderType_Maxi32 = 0x7fffffff,
} TS_ShaderType;

/// Tellusim::Shader::Mask
typedef enum TS_ShaderMask {
	TS_ShaderMaskNone = 0,
	TS_ShaderMaskVertex = 2,
	TS_ShaderMaskControl = 4,
	TS_ShaderMaskEvaluate = 8,
	TS_ShaderMaskGeometry = 16,
	TS_ShaderMaskFragment = 32,
	TS_ShaderMaskCompute = 64,
	TS_ShaderMaskTask = 128,
	TS_ShaderMaskMesh = 256,
	TS_ShaderMaskRayGen = 512,
	TS_ShaderMaskRayMiss = 1024,
	TS_ShaderMaskClosest = 2048,
	TS_ShaderMaskFirstHit = 4096,
	TS_ShaderMaskIntersection = 8192,
	TS_ShaderMaskCallable = 16384,
	TS_ShaderMaskVertexFragment = 34,
	TS_ShaderMaskGraphics = 62,
	TS_ShaderMaskTracing = 32256,
	TS_ShaderMaskAll = 32766,
	TS_ShaderMask_Maxi32 = 0x7fffffff,
} TS_ShaderMask;

/// Tellusim::ShaderCompiler::Flags
typedef enum TS_ShaderCompilerFlags {
	TS_ShaderCompilerFlagNone = 0,
	TS_ShaderCompilerFlagMSLIndirect = 1,
	TS_ShaderCompilerFlags_Maxi32 = 0x7fffffff,
} TS_ShaderCompilerFlags;

/// Tellusim::Sampler::Filter
typedef enum TS_SamplerFilter {
	TS_SamplerFilterPoint = 0,
	TS_SamplerFilterLinear,
	TS_SamplerFilterBipoint,
	TS_SamplerFilterBilinear,
	TS_SamplerFilterTrilinear,
	TS_SamplerFilterNumFilters,
	TS_SamplerFilter_Maxi32 = 0x7fffffff,
} TS_SamplerFilter;

/// Tellusim::Sampler::
typedef enum TS_Sampler {
	TS_SamplerMinAnisotropy = 1,
	TS_SamplerMaxAnisotropy = 16,
	TS_Sampler_Maxi32 = 0x7fffffff,
} TS_Sampler;

/// Tellusim::Sampler::WrapMode
typedef enum TS_SamplerWrapMode {
	TS_SamplerWrapModeClamp = 0,
	TS_SamplerWrapModeRepeat,
	TS_SamplerWrapModeMirror,
	TS_SamplerWrapModeBorder,
	TS_SamplerWrapModeNumWrapModes,
	TS_SamplerWrapMode_Maxi32 = 0x7fffffff,
} TS_SamplerWrapMode;

/// Tellusim::Sampler::CompareFunc
typedef enum TS_SamplerCompareFunc {
	TS_SamplerCompareFuncNone = 0,
	TS_SamplerCompareFuncEqual,
	TS_SamplerCompareFuncLess,
	TS_SamplerCompareFuncGreater,
	TS_SamplerCompareFuncNotEqual,
	TS_SamplerCompareFuncLessEqual,
	TS_SamplerCompareFuncGreaterEqual,
	TS_SamplerCompareFuncNumCompareFunctions,
	TS_SamplerCompareFunc_Maxi32 = 0x7fffffff,
} TS_SamplerCompareFunc;

/// Tellusim::Sampler::ReductionMode
typedef enum TS_SamplerReductionMode {
	TS_SamplerReductionModeAverage = 0,
	TS_SamplerReductionModeMin,
	TS_SamplerReductionModeMax,
	TS_SamplerReductionModeNumReductionModes,
	TS_SamplerReductionMode_Maxi32 = 0x7fffffff,
} TS_SamplerReductionMode;

/// Tellusim::Texture::Type
typedef enum TS_TextureType {
	TS_TextureTypeUnknown = 0,
	TS_TextureType2D,
	TS_TextureType3D,
	TS_TextureTypeCube,
	TS_TextureTypeNumTypes,
	TS_TextureType_Maxi32 = 0x7fffffff,
} TS_TextureType;

/// Tellusim::Texture::Flags
typedef enum TS_TextureFlags {
	TS_TextureFlagNone = 0,
	TS_TextureFlagRead = 1,
	TS_TextureFlagWrite = 2,
	TS_TextureFlagTarget = 4,
	TS_TextureFlagBuffer = 8,
	TS_TextureFlagSource = 16,
	TS_TextureFlagSparse = 32,
	TS_TextureFlagShared = 64,
	TS_TextureFlagExtern = 128,
	TS_TextureFlagInterop = 256,
	TS_TextureFlagSurface = 512,
	TS_TextureFlagMutable = 1024,
	TS_TextureFlagMipmaps = 2048,
	TS_TextureFlagGenerate = 4096,
	TS_TextureFlagFormatNorm = 8192,
	TS_TextureFlagFormatSRGB = 16384,
	TS_TextureFlagFormatSigned = 32768,
	TS_TextureFlagMultisample2 = 65536,
	TS_TextureFlagMultisample4 = 131072,
	TS_TextureFlagMultisample8 = 262144,
	TS_TextureFlagClearOne = 524288,
	TS_TextureFlagClearZero = 1048576,
	TS_TextureFlagClearNormal = 2097152,
	TS_TextureFlagMultisample = 458752,
	TS_TextureDefaultFlags = 0,
	TS_TextureNumFlags = 22,
	TS_TextureFlags_Maxi32 = 0x7fffffff,
} TS_TextureFlags;

/// Tellusim::Tracing::Type
typedef enum TS_TracingType {
	TS_TracingTypeUnknown = 0,
	TS_TracingTypeInstance,
	TS_TracingTypeTriangle,
	TS_TracingTypeBound,
	TS_TracingTypeNumTypes,
	TS_TracingType_Maxi32 = 0x7fffffff,
} TS_TracingType;

/// Tellusim::Tracing::Flags
typedef enum TS_TracingFlags {
	TS_TracingFlagNone = 0,
	TS_TracingFlagInfo = 1,
	TS_TracingFlagUpdate = 2,
	TS_TracingFlagCompact = 4,
	TS_TracingFlagTransparent = 8,
	TS_TracingFlagFastBuild = 16,
	TS_TracingFlagFastTrace = 32,
	TS_TracingDefaultFlags = 0,
	TS_TracingNumFlags = 6,
	TS_TracingFlags_Maxi32 = 0x7fffffff,
} TS_TracingFlags;

/// Tellusim::Tracing::
typedef enum TS_Tracing {
	TS_TracingInstanceSize = 64,
	TS_Tracing_Maxi32 = 0x7fffffff,
} TS_Tracing;

/// Tellusim::Target::Operation
typedef enum TS_TargetOperation {
	TS_TargetOperationBeginLoad = 1,
	TS_TargetOperationBeginClear = 2,
	TS_TargetOperationBeginDiscard = 4,
	TS_TargetOperationBeginMask = 7,
	TS_TargetOperationEndStore = 8,
	TS_TargetOperationEndResolve = 16,
	TS_TargetOperationEndDiscard = 32,
	TS_TargetOperationEndMask = 56,
	TS_TargetOperationOpNone = 0,
	TS_TargetOperationOpLoad = 1,
	TS_TargetOperationOpLoadStore = 9,
	TS_TargetOperationOpClearStore = 10,
	TS_TargetOperationOpClearDiscard = 34,
	TS_TargetOperationOpDefault = 10,
	TS_TargetOperation_Maxi32 = 0x7fffffff,
} TS_TargetOperation;

/// Tellusim::Pipeline::Primitive
typedef enum TS_PipelinePrimitive {
	TS_PipelinePrimitivePoint = 0,
	TS_PipelinePrimitivePointPatch,
	TS_PipelinePrimitiveLine,
	TS_PipelinePrimitiveLineAdj,
	TS_PipelinePrimitiveLineStrip,
	TS_PipelinePrimitiveLinePatch,
	TS_PipelinePrimitiveTriangle,
	TS_PipelinePrimitiveTriangleAdj,
	TS_PipelinePrimitiveTriangleStrip,
	TS_PipelinePrimitiveTrianglePatch,
	TS_PipelinePrimitiveQuadrilateralPatch,
	TS_PipelinePrimitiveNumPrimitiveTypes,
	TS_PipelinePrimitive_Maxi32 = 0x7fffffff,
} TS_PipelinePrimitive;

/// Tellusim::Pipeline::Attribute
typedef enum TS_PipelineAttribute {
	TS_PipelineAttributePosition = 0,
	TS_PipelineAttributeBasis,
	TS_PipelineAttributeNormal,
	TS_PipelineAttributeTangent,
	TS_PipelineAttributeBinormal,
	TS_PipelineAttributeTexCoord,
	TS_PipelineAttributeWeights,
	TS_PipelineAttributeJoints,
	TS_PipelineAttributeColor,
	TS_PipelineAttributeIndex,
	TS_PipelineAttributeNumAttributeTypes,
	TS_PipelineAttribute_Maxi32 = 0x7fffffff,
} TS_PipelineAttribute;

/// Tellusim::Pipeline::FillMode
typedef enum TS_PipelineFillMode {
	TS_PipelineFillModeLine = 0,
	TS_PipelineFillModeSolid,
	TS_PipelineFillModeNumFillModes,
	TS_PipelineFillMode_Maxi32 = 0x7fffffff,
} TS_PipelineFillMode;

/// Tellusim::Pipeline::CullMode
typedef enum TS_PipelineCullMode {
	TS_PipelineCullModeNone = 0,
	TS_PipelineCullModeBack,
	TS_PipelineCullModeFront,
	TS_PipelineCullModeNumCullModes,
	TS_PipelineCullMode_Maxi32 = 0x7fffffff,
} TS_PipelineCullMode;

/// Tellusim::Pipeline::FrontMode
typedef enum TS_PipelineFrontMode {
	TS_PipelineFrontModeCCW = 0,
	TS_PipelineFrontModeCW,
	TS_PipelineFrontModeNumFrontModes,
	TS_PipelineFrontMode_Maxi32 = 0x7fffffff,
} TS_PipelineFrontMode;

/// Tellusim::Pipeline::BlendOp
typedef enum TS_PipelineBlendOp {
	TS_PipelineBlendOpAdd = 0,
	TS_PipelineBlendOpSub,
	TS_PipelineBlendOpMin,
	TS_PipelineBlendOpMax,
	TS_PipelineBlendOpNumBlendOperations,
	TS_PipelineBlendOp_Maxi32 = 0x7fffffff,
} TS_PipelineBlendOp;

/// Tellusim::Pipeline::BlendFunc
typedef enum TS_PipelineBlendFunc {
	TS_PipelineBlendFuncNone = 0,
	TS_PipelineBlendFuncZero,
	TS_PipelineBlendFuncOne,
	TS_PipelineBlendFuncSrcColor,
	TS_PipelineBlendFuncSrcAlpha,
	TS_PipelineBlendFuncSrc1Color,
	TS_PipelineBlendFuncSrc1Alpha,
	TS_PipelineBlendFuncDestColor,
	TS_PipelineBlendFuncDestAlpha,
	TS_PipelineBlendFuncFactorColor,
	TS_PipelineBlendFuncFactorAlpha,
	TS_PipelineBlendFuncInvSrcColor,
	TS_PipelineBlendFuncInvSrcAlpha,
	TS_PipelineBlendFuncInvSrc1Color,
	TS_PipelineBlendFuncInvSrc1Alpha,
	TS_PipelineBlendFuncInvDestColor,
	TS_PipelineBlendFuncInvDestAlpha,
	TS_PipelineBlendFuncInvFactorColor,
	TS_PipelineBlendFuncInvFactorAlpha,
	TS_PipelineBlendFuncNumBlendFunctions,
	TS_PipelineBlendFunc_Maxi32 = 0x7fffffff,
} TS_PipelineBlendFunc;

/// Tellusim::Pipeline::ColorMask
typedef enum TS_PipelineColorMask {
	TS_PipelineColorMaskNone = 0,
	TS_PipelineColorMaskR = 1,
	TS_PipelineColorMaskG = 2,
	TS_PipelineColorMaskB = 4,
	TS_PipelineColorMaskA = 8,
	TS_PipelineColorMaskUnknown = 16,
	TS_PipelineColorMaskRGB = 7,
	TS_PipelineColorMaskAll = 15,
	TS_PipelineColorMask_Maxi32 = 0x7fffffff,
} TS_PipelineColorMask;

/// Tellusim::Pipeline::DepthMask
typedef enum TS_PipelineDepthMask {
	TS_PipelineDepthMaskNone = 0,
	TS_PipelineDepthMaskRead,
	TS_PipelineDepthMaskWrite,
	TS_PipelineDepthMaskNumDepthMasks,
	TS_PipelineDepthMask_Maxi32 = 0x7fffffff,
} TS_PipelineDepthMask;

/// Tellusim::Pipeline::DepthFunc
typedef enum TS_PipelineDepthFunc {
	TS_PipelineDepthFuncNone = 0,
	TS_PipelineDepthFuncNever,
	TS_PipelineDepthFuncAlways,
	TS_PipelineDepthFuncEqual,
	TS_PipelineDepthFuncLess,
	TS_PipelineDepthFuncGreater,
	TS_PipelineDepthFuncNotEqual,
	TS_PipelineDepthFuncLessEqual,
	TS_PipelineDepthFuncGreaterEqual,
	TS_PipelineDepthFuncNumDepthFunctions,
	TS_PipelineDepthFunc_Maxi32 = 0x7fffffff,
} TS_PipelineDepthFunc;

/// Tellusim::Pipeline::StencilOp
typedef enum TS_PipelineStencilOp {
	TS_PipelineStencilOpKeep = 0,
	TS_PipelineStencilOpInvert,
	TS_PipelineStencilOpReplace,
	TS_PipelineStencilOpIncrWrap,
	TS_PipelineStencilOpDecrWrap,
	TS_PipelineStencilOpIncrSat,
	TS_PipelineStencilOpDecrSat,
	TS_PipelineStencilOpNumStencilOperations,
	TS_PipelineStencilOp_Maxi32 = 0x7fffffff,
} TS_PipelineStencilOp;

/// Tellusim::Pipeline::StencilFunc
typedef enum TS_PipelineStencilFunc {
	TS_PipelineStencilFuncNone = 0,
	TS_PipelineStencilFuncNever,
	TS_PipelineStencilFuncAlways,
	TS_PipelineStencilFuncEqual,
	TS_PipelineStencilFuncLess,
	TS_PipelineStencilFuncGreater,
	TS_PipelineStencilFuncNotEqual,
	TS_PipelineStencilFuncLessEqual,
	TS_PipelineStencilFuncGreaterEqual,
	TS_PipelineStencilFuncNumStencilFunctions,
	TS_PipelineStencilFunc_Maxi32 = 0x7fffffff,
} TS_PipelineStencilFunc;

/// Tellusim::Window::Flags
typedef enum TS_WindowFlags {
	TS_WindowFlagNone = 0,
	TS_WindowFlagTitle = 1,
	TS_WindowFlagClose = 2,
	TS_WindowFlagFrame = 4,
	TS_WindowFlagResize = 8,
	TS_WindowFlagMinimize = 16,
	TS_WindowFlagMaximize = 32,
	TS_WindowFlagTransient = 64,
	TS_WindowFlagFullscreen = 128,
	TS_WindowFlagTransparent = 256,
	TS_WindowFlagFileDropped = 512,
	TS_WindowFlagMultisample2 = 1024,
	TS_WindowFlagMultisample4 = 2048,
	TS_WindowFlagMultisample8 = 4096,
	TS_WindowFlagVerticalSync = 8192,
	TS_WindowFlagRefreshSync = 16384,
	TS_WindowFlagColorRGBAu8ns = 32768,
	TS_WindowFlagColorRGBu10Au2n = 65536,
	TS_WindowFlagColorRGBAf16 = 131072,
	TS_WindowFlagMultisample = 7168,
	TS_WindowDefaultFlags = 59,
	TS_WindowNumFlags = 18,
	TS_WindowFlags_Maxi32 = 0x7fffffff,
} TS_WindowFlags;

/// Tellusim::Window::Cursor
typedef enum TS_WindowCursor {
	TS_WindowCursorArrow = 0,
	TS_WindowCursorInvalid,
	TS_WindowCursorLeft,
	TS_WindowCursorRight,
	TS_WindowCursorBottom,
	TS_WindowCursorTop,
	TS_WindowCursorWidth,
	TS_WindowCursorHeight,
	TS_WindowCursorMajor,
	TS_WindowCursorMinor,
	TS_WindowCursorAll,
	TS_WindowCursorNumCursors,
	TS_WindowCursor_Maxi32 = 0x7fffffff,
} TS_WindowCursor;

/// Tellusim::Window::Button
typedef enum TS_WindowButton {
	TS_WindowButtonNone = 0,
	TS_WindowButtonLeft = 1,
	TS_WindowButtonLeft2 = 2,
	TS_WindowButtonRight = 4,
	TS_WindowButtonRight2 = 8,
	TS_WindowButtonMiddle = 16,
	TS_WindowButtonMiddle2 = 32,
	TS_WindowButtonBack = 64,
	TS_WindowButtonBack2 = 128,
	TS_WindowButtonForward = 256,
	TS_WindowButtonForward2 = 512,
	TS_WindowButtonNumButtons = 10,
	TS_WindowButton_Maxi32 = 0x7fffffff,
} TS_WindowButton;

/// Tellusim::Window::Axis
typedef enum TS_WindowAxis {
	TS_WindowAxisX = 0,
	TS_WindowAxisY,
	TS_WindowAxisZ,
	TS_WindowAxisW,
	TS_WindowAxisNumAxes,
	TS_WindowAxis_Maxi32 = 0x7fffffff,
} TS_WindowAxis;

/// Tellusim::Window::
typedef enum TS_Window {
	TS_WindowNumTouches = 16,
	TS_Window_Maxi32 = 0x7fffffff,
} TS_Window;

/// Tellusim::Window::Key
typedef enum TS_WindowKey {
	TS_WindowKeyNone = 128,
	TS_WindowKeyEsc,
	TS_WindowKeyTab,
	TS_WindowKeyBackspace,
	TS_WindowKeyDelete,
	TS_WindowKeyInsert,
	TS_WindowKeyReturn,
	TS_WindowKeyPause,
	TS_WindowKeyPrior,
	TS_WindowKeyNext,
	TS_WindowKeyEnd,
	TS_WindowKeyHome,
	TS_WindowKeyUp,
	TS_WindowKeyDown,
	TS_WindowKeyLeft,
	TS_WindowKeyRight,
	TS_WindowKeyNum,
	TS_WindowKeyCaps,
	TS_WindowKeyScroll,
	TS_WindowKeyShift,
	TS_WindowKeyCtrl,
	TS_WindowKeyAlt,
	TS_WindowKeyWin,
	TS_WindowKeyCmd,
	TS_WindowKeyMenu,
	TS_WindowKeyF1,
	TS_WindowKeyF2,
	TS_WindowKeyF3,
	TS_WindowKeyF4,
	TS_WindowKeyF5,
	TS_WindowKeyF6,
	TS_WindowKeyF7,
	TS_WindowKeyF8,
	TS_WindowKeyF9,
	TS_WindowKeyF10,
	TS_WindowKeyF11,
	TS_WindowKeyF12,
	TS_WindowKeyNumKeys,
	TS_WindowKey_Maxi32 = 0x7fffffff,
} TS_WindowKey;

/// Tellusim::CanvasElement::Type
typedef enum TS_CanvasElementType {
	TS_CanvasElementTypeUnknown = 0,
	TS_CanvasElementTypeText,
	TS_CanvasElementTypeMesh,
	TS_CanvasElementTypeRect,
	TS_CanvasElementTypeTriangle,
	TS_CanvasElementTypeEllipse,
	TS_CanvasElementTypeShape,
	TS_CanvasElementTypeStrip,
	TS_CanvasElementTypeNumTypes,
	TS_CanvasElementType_Maxi32 = 0x7fffffff,
} TS_CanvasElementType;

/// Tellusim::CanvasElement::Mode
typedef enum TS_CanvasElementMode {
	TS_CanvasElementModeSolid = 0,
	TS_CanvasElementModeTexture,
	TS_CanvasElementModeTextureFetch,
	TS_CanvasElementModeTextureClamp,
	TS_CanvasElementModeTextureCubic,
	TS_CanvasElementModeTextureCubic3x3,
	TS_CanvasElementModeTextureCubic5x5,
	TS_CanvasElementModeTextureRed,
	TS_CanvasElementModeTextureGreen,
	TS_CanvasElementModeTextureBlue,
	TS_CanvasElementModeTextureAlpha,
	TS_CanvasElementModeTextureYOG,
	TS_CanvasElementModeGradient,
	TS_CanvasElementModeNumModes,
	TS_CanvasElementMode_Maxi32 = 0x7fffffff,
} TS_CanvasElementMode;

/// Tellusim::CanvasElement::Align
typedef enum TS_CanvasElementAlign {
	TS_CanvasElementAlignNone = 0,
	TS_CanvasElementAlignLeft = 1,
	TS_CanvasElementAlignRight = 2,
	TS_CanvasElementAlignBottom = 4,
	TS_CanvasElementAlignTop = 8,
	TS_CanvasElementAlignCenterX = 16,
	TS_CanvasElementAlignCenterY = 32,
	TS_CanvasElementAlignLeftBottom = 5,
	TS_CanvasElementAlignLeftTop = 9,
	TS_CanvasElementAlignRightBottom = 6,
	TS_CanvasElementAlignRightTop = 10,
	TS_CanvasElementAlignCenter = 48,
	TS_CanvasElementAlignNumAligns = 6,
	TS_CanvasElementAlign_Maxi32 = 0x7fffffff,
} TS_CanvasElementAlign;

/// Tellusim::CanvasElement::Stack
typedef enum TS_CanvasElementStack {
	TS_CanvasElementStackNone = 0,
	TS_CanvasElementStackPush = 1,
	TS_CanvasElementStackPop = 2,
	TS_CanvasElementStackSet = 4,
	TS_CanvasElementStackMul = 8,
	TS_CanvasElementStackGet = 16,
	TS_CanvasElementStack_Maxi32 = 0x7fffffff,
} TS_CanvasElementStack;

/// Tellusim::Control::Type
typedef enum TS_ControlType {
	TS_ControlTypeUnknown = 0,
	TS_ControlTypeRoot,
	TS_ControlTypeText,
	TS_ControlTypeRect,
	TS_ControlTypeGrid,
	TS_ControlTypeGroup,
	TS_ControlTypePanel,
	TS_ControlTypeDialog,
	TS_ControlTypeWindow,
	TS_ControlTypeCheck,
	TS_ControlTypeCombo,
	TS_ControlTypeButton,
	TS_ControlTypeSlider,
	TS_ControlTypeScroll,
	TS_ControlTypeSplit,
	TS_ControlTypeArea,
	TS_ControlTypeTree,
	TS_ControlTypeEdit,
	TS_ControlTypeNumTypes,
	TS_ControlType_Maxi32 = 0x7fffffff,
} TS_ControlType;

/// Tellusim::Control::State
typedef enum TS_ControlState {
	TS_ControlStateUnknown = 0,
	TS_ControlStateNormal,
	TS_ControlStateFocused,
	TS_ControlStatePressed,
	TS_ControlStateDisabled,
	TS_ControlStateNumStates,
	TS_ControlState_Maxi32 = 0x7fffffff,
} TS_ControlState;

/// Tellusim::Control::Mesh
typedef enum TS_ControlMesh {
	TS_ControlMeshCheck = 0,
	TS_ControlMeshButton,
	TS_ControlMeshSliderLine,
	TS_ControlMeshHScrollLine,
	TS_ControlMeshVScrollLine,
	TS_ControlMeshSliderHandle,
	TS_ControlMeshHScrollHandle,
	TS_ControlMeshVScrollHandle,
	TS_ControlMeshBackground,
	TS_ControlMeshSelection,
	TS_ControlMeshBorder,
	TS_ControlMeshFrame,
	TS_ControlMeshNumMeshes,
	TS_ControlMesh_Maxi32 = 0x7fffffff,
} TS_ControlMesh;

/// Tellusim::Control::Align
typedef enum TS_ControlAlign {
	TS_ControlAlignNone = 0,
	TS_ControlAlignLeft = 1,
	TS_ControlAlignRight = 2,
	TS_ControlAlignBottom = 4,
	TS_ControlAlignTop = 8,
	TS_ControlAlignCenterX = 16,
	TS_ControlAlignCenterY = 32,
	TS_ControlAlignExpandX = 64,
	TS_ControlAlignExpandY = 128,
	TS_ControlAlignOverlap = 256,
	TS_ControlAlignSpacer = 512,
	TS_ControlAlignAspect = 1024,
	TS_ControlAlignLocal = 2048,
	TS_ControlAlignLeftBottom = 5,
	TS_ControlAlignLeftTop = 9,
	TS_ControlAlignRightBottom = 6,
	TS_ControlAlignRightTop = 10,
	TS_ControlAlignCenter = 48,
	TS_ControlAlignExpand = 192,
	TS_ControlAlignNumAligns = 12,
	TS_ControlAlign_Maxi32 = 0x7fffffff,
} TS_ControlAlign;

/// Tellusim::Control::Button
typedef enum TS_ControlButton {
	TS_ControlButtonNone = 0,
	TS_ControlButtonLeft = 1,
	TS_ControlButtonLeft2 = 2,
	TS_ControlButtonRight = 4,
	TS_ControlButtonRight2 = 8,
	TS_ControlButtonMiddle = 16,
	TS_ControlButtonMiddle2 = 32,
	TS_ControlButtonNumButtons = 6,
	TS_ControlButton_Maxi32 = 0x7fffffff,
} TS_ControlButton;

/// Tellusim::Control::Axis
typedef enum TS_ControlAxis {
	TS_ControlAxisUnknown = 0,
	TS_ControlAxisX,
	TS_ControlAxisY,
	TS_ControlAxisZ,
	TS_ControlAxisW,
	TS_ControlAxisNumAxes,
	TS_ControlAxis_Maxi32 = 0x7fffffff,
} TS_ControlAxis;

/// Tellusim::Control::Key
typedef enum TS_ControlKey {
	TS_ControlKeyNone = 128,
	TS_ControlKeyTab,
	TS_ControlKeyBackspace,
	TS_ControlKeyDelete,
	TS_ControlKeyInsert,
	TS_ControlKeyReturn,
	TS_ControlKeyPrior,
	TS_ControlKeyNext,
	TS_ControlKeyEnd,
	TS_ControlKeyHome,
	TS_ControlKeyUp,
	TS_ControlKeyDown,
	TS_ControlKeyLeft,
	TS_ControlKeyRight,
	TS_ControlKeyShift,
	TS_ControlKeyCtrl,
	TS_ControlKeyAlt,
	TS_ControlKeyCmd,
	TS_ControlKeyNumKeys,
	TS_ControlKey_Maxi32 = 0x7fffffff,
} TS_ControlKey;

/// Tellusim::ControlEdit::EditMode
typedef enum TS_ControlEditEditMode {
	TS_ControlEditEditModeText,
	TS_ControlEditEditModePassword,
	TS_ControlEditEditModeNumber,
	TS_ControlEditEditModeSigned,
	TS_ControlEditEditModeUnsigned,
	TS_ControlEditEditModeHexadecimal,
	TS_ControlEditEditMode_Maxi32 = 0x7fffffff,
} TS_ControlEditEditMode;

/// Tellusim::DialogMessage::Flags
typedef enum TS_DialogMessageFlags {
	TS_DialogMessageFlagNone = 0,
	TS_DialogMessageFlagYes = 1,
	TS_DialogMessageFlagNo = 2,
	TS_DialogMessageFlagOk = 4,
	TS_DialogMessageFlagCancel = 8,
	TS_DialogMessageFlagClose = 16,
	TS_DialogMessageFlagMessage = 32,
	TS_DialogMessageFlagWarning = 64,
	TS_DialogMessageFlagQuestion = 128,
	TS_DialogMessageFlagError = 256,
	TS_DialogMessageFlagMouse = 512,
	TS_DialogMessageFlagYesNo = 3,
	TS_DialogMessageFlagOkCancel = 12,
	TS_DialogMessageDefaultFlags = 4,
	TS_DialogMessageNumFlags = 10,
	TS_DialogMessageFlags_Maxi32 = 0x7fffffff,
} TS_DialogMessageFlags;

/// Tellusim::DialogMessage::Result
typedef enum TS_DialogMessageResult {
	TS_DialogMessageResultClose = 0,
	TS_DialogMessageResultCancel,
	TS_DialogMessageResultOk,
	TS_DialogMessageResultNo,
	TS_DialogMessageResultYes,
	TS_DialogMessageResultNumResults,
	TS_DialogMessageResult_Maxi32 = 0x7fffffff,
} TS_DialogMessageResult;

/// Tellusim::DialogFileOpen::Flags
typedef enum TS_DialogFileOpenFlags {
	TS_DialogFileOpenFlagNone = 0,
	TS_DialogFileOpenFlagHidden = 1,
	TS_DialogFileOpenFlagMouse = 2,
	TS_DialogFileOpenDefaultFlags = 0,
	TS_DialogFileOpenNumFlags = 2,
	TS_DialogFileOpenFlags_Maxi32 = 0x7fffffff,
} TS_DialogFileOpenFlags;

/// Tellusim::DialogFileOpen::Result
typedef enum TS_DialogFileOpenResult {
	TS_DialogFileOpenResultCancel = 0,
	TS_DialogFileOpenResultOk,
	TS_DialogFileOpenResultNumResults,
	TS_DialogFileOpenResult_Maxi32 = 0x7fffffff,
} TS_DialogFileOpenResult;

/// Tellusim::DialogFileSave::Flags
typedef enum TS_DialogFileSaveFlags {
	TS_DialogFileSaveFlagNone = 0,
	TS_DialogFileSaveFlagHidden = 1,
	TS_DialogFileSaveFlagOverwrite = 2,
	TS_DialogFileSaveFlagMouse = 4,
	TS_DialogFileSaveDefaultFlags = 2,
	TS_DialogFileSaveNumFlags = 3,
	TS_DialogFileSaveFlags_Maxi32 = 0x7fffffff,
} TS_DialogFileSaveFlags;

/// Tellusim::DialogFileSave::Result
typedef enum TS_DialogFileSaveResult {
	TS_DialogFileSaveResultCancel = 0,
	TS_DialogFileSaveResultOk,
	TS_DialogFileSaveResultNumResults,
	TS_DialogFileSaveResult_Maxi32 = 0x7fffffff,
} TS_DialogFileSaveResult;

/// Tellusim::DialogDirectory::Flags
typedef enum TS_DialogDirectoryFlags {
	TS_DialogDirectoryFlagNone = 0,
	TS_DialogDirectoryFlagMouse = 1,
	TS_DialogDirectoryDefaultFlags = 0,
	TS_DialogDirectoryNumFlags = 1,
	TS_DialogDirectoryFlags_Maxi32 = 0x7fffffff,
} TS_DialogDirectoryFlags;

/// Tellusim::DialogDirectory::Result
typedef enum TS_DialogDirectoryResult {
	TS_DialogDirectoryResultCancel = 0,
	TS_DialogDirectoryResultOk,
	TS_DialogDirectoryResultNumResults,
	TS_DialogDirectoryResult_Maxi32 = 0x7fffffff,
} TS_DialogDirectoryResult;

/// Tellusim::DialogProgress::Flags
typedef enum TS_DialogProgressFlags {
	TS_DialogProgressFlagNone = 0,
	TS_DialogProgressFlagMouse = 1,
	TS_DialogProgressDefaultFlags = 0,
	TS_DialogProgressNumFlags = 1,
	TS_DialogProgressFlags_Maxi32 = 0x7fffffff,
} TS_DialogProgressFlags;

/// Tellusim::DialogProgress::Result
typedef enum TS_DialogProgressResult {
	TS_DialogProgressResultCancel = 0,
	TS_DialogProgressResultOk,
	TS_DialogProgressResultNumResults,
	TS_DialogProgressResult_Maxi32 = 0x7fffffff,
} TS_DialogProgressResult;

/// Tellusim::DialogColor::Flags
typedef enum TS_DialogColorFlags {
	TS_DialogColorFlagNone = 0,
	TS_DialogColorFlagAlpha = 1,
	TS_DialogColorFlagMouse = 2,
	TS_DialogColorDefaultFlags = 0,
	TS_DialogColorNumFlags = 2,
	TS_DialogColorFlags_Maxi32 = 0x7fffffff,
} TS_DialogColorFlags;

/// Tellusim::DialogColor::Result
typedef enum TS_DialogColorResult {
	TS_DialogColorResultCancel = 0,
	TS_DialogColorResultOk,
	TS_DialogColorResultNumResults,
	TS_DialogColorResult_Maxi32 = 0x7fffffff,
} TS_DialogColorResult;

/// Tellusim::DialogMenu::Flags
typedef enum TS_DialogMenuFlags {
	TS_DialogMenuFlagNone = 0,
	TS_DialogMenuFlagMouse = 1,
	TS_DialogMenuDefaultFlags = 0,
	TS_DialogMenuNumFlags = 1,
	TS_DialogMenuFlags_Maxi32 = 0x7fffffff,
} TS_DialogMenuFlags;

/// Tellusim::DialogMenu::Result
typedef enum TS_DialogMenuResult {
	TS_DialogMenuResultCancel = 0,
	TS_DialogMenuResultClick,
	TS_DialogMenuResultNumResults,
	TS_DialogMenuResult_Maxi32 = 0x7fffffff,
} TS_DialogMenuResult;

/// Tellusim::CubeFilter::Mode
typedef enum TS_CubeFilterMode {
	TS_CubeFilterModeCube = 0,
	TS_CubeFilterModePanorama,
	TS_CubeFilterModeNumModes,
	TS_CubeFilterMode_Maxi32 = 0x7fffffff,
} TS_CubeFilterMode;

/// Tellusim::CubeFilter::Flags
typedef enum TS_CubeFilterFlags {
	TS_CubeFilterFlagCube = 1,
	TS_CubeFilterFlagPanorama = 2,
	TS_CubeFilterAll = 3,
	TS_CubeFilterFlags_Maxi32 = 0x7fffffff,
} TS_CubeFilterFlags;

/// Tellusim::DecoderJPEG::Mode
typedef enum TS_DecoderJPEGMode {
	TS_DecoderJPEGModeR = 0,
	TS_DecoderJPEGModeRG,
	TS_DecoderJPEGModeRGBA,
	TS_DecoderJPEGModeYUV444,
	TS_DecoderJPEGModeYUV422H,
	TS_DecoderJPEGModeYUV422V,
	TS_DecoderJPEGModeYUV420,
	TS_DecoderJPEGModeNumModes,
	TS_DecoderJPEGMode_Maxi32 = 0x7fffffff,
} TS_DecoderJPEGMode;

/// Tellusim::DecoderJPEG::Flags
typedef enum TS_DecoderJPEGFlags {
	TS_DecoderJPEGFlagNone = 0,
	TS_DecoderJPEGFlagR = 1,
	TS_DecoderJPEGFlagRG = 2,
	TS_DecoderJPEGFlagRGBA = 4,
	TS_DecoderJPEGFlagYUV444 = 8,
	TS_DecoderJPEGFlagYUV422H = 16,
	TS_DecoderJPEGFlagYUV422V = 32,
	TS_DecoderJPEGFlagYUV420 = 64,
	TS_DecoderJPEGAll = 127,
	TS_DecoderJPEGFlags_Maxi32 = 0x7fffffff,
} TS_DecoderJPEGFlags;

/// Tellusim::EncoderBC15::Mode
typedef enum TS_EncoderBC15Mode {
	TS_EncoderBC15ModeBC1RGBu8n = 0,
	TS_EncoderBC15ModeBC2RGBAu8n,
	TS_EncoderBC15ModeBC3RGBAu8n,
	TS_EncoderBC15ModeBC4Ru8n,
	TS_EncoderBC15ModeBC5RGu8n,
	TS_EncoderBC15ModeNumModes,
	TS_EncoderBC15Mode_Maxi32 = 0x7fffffff,
} TS_EncoderBC15Mode;

/// Tellusim::EncoderBC15::Flags
typedef enum TS_EncoderBC15Flags {
	TS_EncoderBC15FlagNone = 0,
	TS_EncoderBC15FlagBC1RGBu8n = 1,
	TS_EncoderBC15FlagBC2RGBAu8n = 2,
	TS_EncoderBC15FlagBC3RGBAu8n = 4,
	TS_EncoderBC15FlagBC4Ru8n = 8,
	TS_EncoderBC15FlagBC5RGu8n = 16,
	TS_EncoderBC15FlagCube = 64,
	TS_EncoderBC15BC13 = 7,
	TS_EncoderBC15BC45 = 24,
	TS_EncoderBC15All = 31,
	TS_EncoderBC15Flags_Maxi32 = 0x7fffffff,
} TS_EncoderBC15Flags;

/// Tellusim::EncoderBC67::Mode
typedef enum TS_EncoderBC67Mode {
	TS_EncoderBC67ModeBC6RGBf16s = 0,
	TS_EncoderBC67ModeBC6RGBf16u,
	TS_EncoderBC67ModeBC7RGBAu8n,
	TS_EncoderBC67ModeNumModes,
	TS_EncoderBC67Mode_Maxi32 = 0x7fffffff,
} TS_EncoderBC67Mode;

/// Tellusim::EncoderBC67::Flags
typedef enum TS_EncoderBC67Flags {
	TS_EncoderBC67FlagNone = 0,
	TS_EncoderBC67FlagBC6RGBf16s = 1,
	TS_EncoderBC67FlagBC6RGBf16u = 2,
	TS_EncoderBC67FlagBC7RGBAu8n = 4,
	TS_EncoderBC67FlagCube = 16,
	TS_EncoderBC67All = 7,
	TS_EncoderBC67Flags_Maxi32 = 0x7fffffff,
} TS_EncoderBC67Flags;

/// Tellusim::EncoderASTC::Mode
typedef enum TS_EncoderASTCMode {
	TS_EncoderASTCModeASTC44RGBAu8n = 0,
	TS_EncoderASTCModeASTC54RGBAu8n,
	TS_EncoderASTCModeASTC55RGBAu8n,
	TS_EncoderASTCModeNumModes,
	TS_EncoderASTCMode_Maxi32 = 0x7fffffff,
} TS_EncoderASTCMode;

/// Tellusim::EncoderASTC::Flags
typedef enum TS_EncoderASTCFlags {
	TS_EncoderASTCFlagNone = 0,
	TS_EncoderASTCFlagASTC44RGBAu8n = 1,
	TS_EncoderASTCFlagASTC54RGBAu8n = 2,
	TS_EncoderASTCFlagASTC55RGBAu8n = 4,
	TS_EncoderASTCFlagCube = 16,
	TS_EncoderASTCAll = 7,
	TS_EncoderASTCFlags_Maxi32 = 0x7fffffff,
} TS_EncoderASTCFlags;

/// Tellusim::MeshModel::Flags
typedef enum TS_MeshModelFlags {
	TS_MeshModelFlagNone = 0,
	TS_MeshModelFlagDirect = 1,
	TS_MeshModelFlagVerbose = 2,
	TS_MeshModelFlagOptimize = 4,
	TS_MeshModelFlagMaterials = 8,
	TS_MeshModelFlagIndices10 = 16,
	TS_MeshModelFlagIndices16 = 32,
	TS_MeshModelFlagIndices32 = 64,
	TS_MeshModelFlagMeshlet64x84 = 128,
	TS_MeshModelFlagMeshlet64x126 = 256,
	TS_MeshModelFlagMeshlet96x169 = 512,
	TS_MeshModelFlagMeshlet128x212 = 1024,
	TS_MeshModelFlagBufferWrite = 2048,
	TS_MeshModelFlagBufferSource = 4096,
	TS_MeshModelFlagBufferStorage = 8192,
	TS_MeshModelFlagBufferTracing = 16384,
	TS_MeshModelFlagBufferAddress = 32768,
	TS_MeshModelFlagBufferTexel = 65536,
	TS_MeshModelFlagMeshlets = 1920,
	TS_MeshModelDefaultFlags = 10,
	TS_MeshModelNumFlags = 17,
	TS_MeshModelFlags_Maxi32 = 0x7fffffff,
} TS_MeshModelFlags;

/// Tellusim::SeparableFilter::Mode
typedef enum TS_SeparableFilterMode {
	TS_SeparableFilterModeHorizontal = 0,
	TS_SeparableFilterModeVertical,
	TS_SeparableFilterModeNumModes,
	TS_SeparableFilterMode_Maxi32 = 0x7fffffff,
} TS_SeparableFilterMode;

/// Tellusim::SeparableFilter::Flags
typedef enum TS_SeparableFilterFlags {
	TS_SeparableFilterFlagNone = 0,
	TS_SeparableFilterFlagRepeat = 1,
	TS_SeparableFilterFlagZero = 2,
	TS_SeparableFilterDefaultFlags = 0,
	TS_SeparableFilterFlags_Maxi32 = 0x7fffffff,
} TS_SeparableFilterFlags;

/// Tellusim::PrefixScan::Mode
typedef enum TS_PrefixScanMode {
	TS_PrefixScanModeSingle = 0,
	TS_PrefixScanModeMultiple,
	TS_PrefixScanModeNumModes,
	TS_PrefixScanMode_Maxi32 = 0x7fffffff,
} TS_PrefixScanMode;

/// Tellusim::PrefixScan::Flags
typedef enum TS_PrefixScanFlags {
	TS_PrefixScanFlagNone = 0,
	TS_PrefixScanFlagSingle = 1,
	TS_PrefixScanFlagMultiple = 2,
	TS_PrefixScanFlagIndirect = 4,
	TS_PrefixScanFlagRepeat = 8,
	TS_PrefixScanAll = 7,
	TS_PrefixScanFlags_Maxi32 = 0x7fffffff,
} TS_PrefixScanFlags;

/// Tellusim::RadixSort::Mode
typedef enum TS_RadixSortMode {
	TS_RadixSortModeSingle = 0,
	TS_RadixSortModeMultiple,
	TS_RadixSortModeNumModes,
	TS_RadixSortMode_Maxi32 = 0x7fffffff,
} TS_RadixSortMode;

/// Tellusim::RadixSort::Flags
typedef enum TS_RadixSortFlags {
	TS_RadixSortFlagNone = 0,
	TS_RadixSortFlagSingle = 1,
	TS_RadixSortFlagMultiple = 2,
	TS_RadixSortFlagIndirect = 4,
	TS_RadixSortFlagOrder = 8,
	TS_RadixSortFlagTracing = 16,
	TS_RadixSortFlagScratch = 32,
	TS_RadixSortAll = 15,
	TS_RadixSortFlags_Maxi32 = 0x7fffffff,
} TS_RadixSortFlags;

/// Tellusim::BitonicSort::Mode
typedef enum TS_BitonicSortMode {
	TS_BitonicSortModeSingle = 0,
	TS_BitonicSortModeMultiple,
	TS_BitonicSortModeNumModes,
	TS_BitonicSortMode_Maxi32 = 0x7fffffff,
} TS_BitonicSortMode;

/// Tellusim::BitonicSort::Flags
typedef enum TS_BitonicSortFlags {
	TS_BitonicSortFlagNone = 0,
	TS_BitonicSortFlagSingle = 1,
	TS_BitonicSortFlagMultiple = 2,
	TS_BitonicSortFlagIndirect = 4,
	TS_BitonicSortFlagOrder = 8,
	TS_BitonicSortAll = 15,
	TS_BitonicSortFlags_Maxi32 = 0x7fffffff,
} TS_BitonicSortFlags;

/// Tellusim::SpatialTree::Mode
typedef enum TS_SpatialTreeMode {
	TS_SpatialTreeModeSingle = 0,
	TS_SpatialTreeModeMultiple,
	TS_SpatialTreeModeNumModes,
	TS_SpatialTreeMode_Maxi32 = 0x7fffffff,
} TS_SpatialTreeMode;

/// Tellusim::SpatialTree::Hash
typedef enum TS_SpatialTreeHash {
	TS_SpatialTreeHashXYZ10,
	TS_SpatialTreeHashXYZ9,
	TS_SpatialTreeHashXYZ8,
	TS_SpatialTreeHashXY15,
	TS_SpatialTreeHashXY14,
	TS_SpatialTreeHashXY12,
	TS_SpatialTreeHashXY10,
	TS_SpatialTreeHash_Maxi32 = 0x7fffffff,
} TS_SpatialTreeHash;

/// Tellusim::SpatialTree::Flags
typedef enum TS_SpatialTreeFlags {
	TS_SpatialTreeFlagNone = 0,
	TS_SpatialTreeFlagSingle = 1,
	TS_SpatialTreeFlagMultiple = 2,
	TS_SpatialTreeFlagUpdate = 4,
	TS_SpatialTreeFlagOptimize = 8,
	TS_SpatialTreeFlagTracing = 16,
	TS_SpatialTreeFlagScratch = 32,
	TS_SpatialTreeFlagAtomic = 64,
	TS_SpatialTreeFlagLeafNodef16 = 128,
	TS_SpatialTreeFlagSpatialData = 256,
	TS_SpatialTreeFlagSingleUpdate = 5,
	TS_SpatialTreeFlagMultipleUpdate = 6,
	TS_SpatialTreeFlagSingleOptimize = 9,
	TS_SpatialTreeFlagMultipleOptimize = 10,
	TS_SpatialTreeAll = 3,
	TS_SpatialTreeAllOptimize = 11,
	TS_SpatialTreeFlags_Maxi32 = 0x7fffffff,
} TS_SpatialTreeFlags;

/// Tellusim::FourierTransform::Mode
typedef enum TS_FourierTransformMode {
	TS_FourierTransformModeRf16i = 0,
	TS_FourierTransformModeRf32i,
	TS_FourierTransformModeRGf16i,
	TS_FourierTransformModeRGf32i,
	TS_FourierTransformModeRGBf16c,
	TS_FourierTransformModeRGBf21c,
	TS_FourierTransformModeRGBf16p,
	TS_FourierTransformModeRGBf32p,
	TS_FourierTransformModeNumModes,
	TS_FourierTransformMode_Maxi32 = 0x7fffffff,
} TS_FourierTransformMode;

/// Tellusim::FourierTransform::Flags
typedef enum TS_FourierTransformFlags {
	TS_FourierTransformFlagNone = 0,
	TS_FourierTransformFlagRf16i = 1,
	TS_FourierTransformFlagRf32i = 2,
	TS_FourierTransformFlagRGf16i = 4,
	TS_FourierTransformFlagRGf32i = 8,
	TS_FourierTransformFlagRGBf16c = 16,
	TS_FourierTransformFlagRGBf21c = 32,
	TS_FourierTransformFlagRGBf16p = 64,
	TS_FourierTransformFlagRGBf32p = 128,
	TS_FourierTransformFlagNpot = 256,
	TS_FourierTransformInterleaved = 15,
	TS_FourierTransformComplex = 48,
	TS_FourierTransformPlanar = 192,
	TS_FourierTransformAll = 511,
	TS_FourierTransformFlags_Maxi32 = 0x7fffffff,
} TS_FourierTransformFlags;

/// Tellusim::FourierTransform::Operation
typedef enum TS_FourierTransformOperation {
	TS_FourierTransformOperationForwardCtoC = 0,
	TS_FourierTransformOperationBackwardCtoC,
	TS_FourierTransformOperationForwardRtoC,
	TS_FourierTransformOperationBackwardCtoR,
	TS_FourierTransformOperationNumOperations,
	TS_FourierTransformOperation_Maxi32 = 0x7fffffff,
} TS_FourierTransformOperation;

/// Tellusim::TensorGraph::Operation
typedef enum TS_TensorGraphOperation {
	TS_TensorGraphOperationClear = 0,
	TS_TensorGraphOperationRange,
	TS_TensorGraphOperationCopy,
	TS_TensorGraphOperationCat,
	TS_TensorGraphOperationTranspose,
	TS_TensorGraphOperationMatMul,
	TS_TensorGraphOperationMul,
	TS_TensorGraphOperationMad,
	TS_TensorGraphOperationDiv,
	TS_TensorGraphOperationAdd,
	TS_TensorGraphOperationConv,
	TS_TensorGraphOperationDeConv,
	TS_TensorGraphOperationBatchNorm,
	TS_TensorGraphOperationBatchMad,
	TS_TensorGraphOperationSoftMin,
	TS_TensorGraphOperationSoftMax,
	TS_TensorGraphOperationMaxPool,
	TS_TensorGraphOperationAvgPool,
	TS_TensorGraphOperationGELU,
	TS_TensorGraphOperationReLU,
	TS_TensorGraphOperationSiLU,
	TS_TensorGraphOperationSigm,
	TS_TensorGraphOperationTanh,
	TS_TensorGraphOperationSin,
	TS_TensorGraphOperationCos,
	TS_TensorGraphOperationExp,
	TS_TensorGraphOperationNumOperations,
	TS_TensorGraphOperation_Maxi32 = 0x7fffffff,
} TS_TensorGraphOperation;

/// Tellusim::TensorGraph::Flags
typedef enum TS_TensorGraphFlags {
	TS_TensorGraphFlagNone = 0,
	TS_TensorGraphFlagSizeQuery = 1,
	TS_TensorGraphFlagFormatRf32 = 2,
	TS_TensorGraphFlagFormatRf16 = 4,
	TS_TensorGraphFlagTranspose = 8,
	TS_TensorGraphFlagWrapClamp = 16,
	TS_TensorGraphFlagWrapRepeat = 32,
	TS_TensorGraphFlagReadScale = 64,
	TS_TensorGraphFlagReadBias = 128,
	TS_TensorGraphFlagConvert = 256,
	TS_TensorGraphFlagKernel = 512,
	TS_TensorGraphFlagGELU = 1024,
	TS_TensorGraphFlagReLU = 2048,
	TS_TensorGraphFlagSiLU = 4096,
	TS_TensorGraphFlagSigm = 8192,
	TS_TensorGraphFlagTanh = 16384,
	TS_TensorGraphFlagSin = 32768,
	TS_TensorGraphFlagCos = 65536,
	TS_TensorGraphFlagExp = 131072,
	TS_TensorGraphFlagFormat = 6,
	TS_TensorGraphFlagWrap = 48,
	TS_TensorGraphFlagRead = 192,
	TS_TensorGraphFlagUnit = 7168,
	TS_TensorGraphFlagMath = 253952,
	TS_TensorGraphAll = 262142,
	TS_TensorGraphFlags_Maxi32 = 0x7fffffff,
} TS_TensorGraphFlags;

/// Tellusim::TensorGraph::Masks
typedef enum TS_TensorGraphMasks {
	TS_TensorGraphMasksMaskNone = 0,
	TS_TensorGraphMasksMaskClear = 1,
	TS_TensorGraphMasksMaskRange = 2,
	TS_TensorGraphMasksMaskCopy = 4,
	TS_TensorGraphMasksMaskCat = 8,
	TS_TensorGraphMasksMaskTranspose = 16,
	TS_TensorGraphMasksMaskMatMul = 32,
	TS_TensorGraphMasksMaskMul = 64,
	TS_TensorGraphMasksMaskMad = 128,
	TS_TensorGraphMasksMaskDiv = 256,
	TS_TensorGraphMasksMaskAdd = 512,
	TS_TensorGraphMasksMaskConv = 1024,
	TS_TensorGraphMasksMaskDeConv = 2048,
	TS_TensorGraphMasksMaskBatchNorm = 4096,
	TS_TensorGraphMasksMaskBatchMad = 8192,
	TS_TensorGraphMasksMaskSoftMin = 16384,
	TS_TensorGraphMasksMaskSoftMax = 32768,
	TS_TensorGraphMasksMaskMaxPool = 65536,
	TS_TensorGraphMasksMaskAvgPool = 131072,
	TS_TensorGraphMasksMaskGELU = 262144,
	TS_TensorGraphMasksMaskReLU = 524288,
	TS_TensorGraphMasksMaskSiLU = 1048576,
	TS_TensorGraphMasksMaskSigm = 2097152,
	TS_TensorGraphMasksMaskTanh = 4194304,
	TS_TensorGraphMasksMaskSin = 8388608,
	TS_TensorGraphMasksMaskCos = 16777216,
	TS_TensorGraphMasksMaskExp = 33554432,
	TS_TensorGraphMasksAll = 67108863,
	TS_TensorGraphMasks_Maxi32 = 0x7fffffff,
} TS_TensorGraphMasks;

/// Tellusim::Controller::Type
typedef enum TS_ControllerType {
	TS_ControllerTypeUnknown = 0,
	TS_ControllerTypeJoystick,
	TS_ControllerTypeGamePad,
	TS_ControllerTypeWheel,
	TS_ControllerTypeNumTypes,
	TS_ControllerType_Maxi32 = 0x7fffffff,
} TS_ControllerType;

/// Tellusim::Controller::Stick
typedef enum TS_ControllerStick {
	TS_ControllerStickLeft = 0,
	TS_ControllerStickRight,
	TS_ControllerStickNumSticks,
	TS_ControllerStick_Maxi32 = 0x7fffffff,
} TS_ControllerStick;

/// Tellusim::Controller::Axis
typedef enum TS_ControllerAxis {
	TS_ControllerAxisX = 0,
	TS_ControllerAxisY,
	TS_ControllerAxisZ,
	TS_ControllerAxisRX,
	TS_ControllerAxisRY,
	TS_ControllerAxisRZ,
	TS_ControllerAxisNumAxes = 16,
	TS_ControllerAxis_Maxi32 = 0x7fffffff,
} TS_ControllerAxis;

/// Tellusim::Controller::Button
typedef enum TS_ControllerButton {
	TS_ControllerButtonLeft = 0,
	TS_ControllerButtonRight,
	TS_ControllerButtonDown,
	TS_ControllerButtonUp,
	TS_ControllerButtonHome,
	TS_ControllerButtonShoulderLeft,
	TS_ControllerButtonShoulderRight,
	TS_ControllerButtonTriggerLeft,
	TS_ControllerButtonTriggerRight,
	TS_ControllerButtonStickLeft,
	TS_ControllerButtonStickRight,
	TS_ControllerButtonA,
	TS_ControllerButtonB,
	TS_ControllerButtonX,
	TS_ControllerButtonY,
	TS_ControllerButtonView,
	TS_ControllerButtonMenu,
	TS_ControllerButtonL1 = 5,
	TS_ControllerButtonR1,
	TS_ControllerButtonL2,
	TS_ControllerButtonR2,
	TS_ControllerButtonL3,
	TS_ControllerButtonR3,
	TS_ControllerButtonCross,
	TS_ControllerButtonCircle,
	TS_ControllerButtonSquare,
	TS_ControllerButtonTriangle,
	TS_ControllerButtonShare,
	TS_ControllerButtonOptions,
	TS_ControllerButtonNumButtons = 32,
	TS_ControllerButton_Maxi32 = 0x7fffffff,
} TS_ControllerButton;

/// Tellusim::Controller::Motor
typedef enum TS_ControllerMotor {
	TS_ControllerMotorLow = 0,
	TS_ControllerMotorHigh,
	TS_ControllerMotorNumMotors,
	TS_ControllerMotor_Maxi32 = 0x7fffffff,
} TS_ControllerMotor;

/// Tellusim::Log::Level
typedef enum TS_LogLevel {
	TS_LogLevelFatal = 0,
	TS_LogLevelError,
	TS_LogLevelWarning,
	TS_LogLevelMessage,
	TS_LogLevelVerbose,
	TS_LogLevelUnknown,
	TS_LogLevelNumLevels,
	TS_LogLevel_Maxi32 = 0x7fffffff,
} TS_LogLevel;

/// Tellusim::Time::
typedef enum TS_Time {
	TS_TimeSeconds = 1000000u,
	TS_TimeMSeconds = 1000u,
	TS_TimeUSeconds = 1u,
	TS_Time_Maxi32 = 0x7fffffff,
} TS_Time;

/// Tellusim::Command
typedef struct TSCommandDrawArraysIndirect {
	uint32_t num_vertices;
	uint32_t num_instances;
	uint32_t base_vertex;
	uint32_t base_instance;
} TSCommandDrawArraysIndirect;

typedef struct TSCommandDrawElementsIndirect {
	uint32_t num_indices;
	uint32_t num_instances;
	uint32_t base_index;
	int32_t base_vertex;
	uint32_t base_instance;
} TSCommandDrawElementsIndirect;

typedef struct TSCommandDrawMeshIndirect {
	uint32_t group_width;
	uint32_t group_height;
	uint32_t group_depth;
	uint32_t padding;
} TSCommandDrawMeshIndirect;

/// Tellusim::Compute
typedef struct TSComputeDispatchIndirect {
	uint32_t group_width;
	uint32_t group_height;
	uint32_t group_depth;
	uint32_t padding;
} TSComputeDispatchIndirect;

/// Tellusim::Query
typedef struct TSQueryStatistics {
	uint64_t num_vertices;
	uint64_t num_primitives;
	uint64_t vertex_invocations;
	uint64_t control_invocations;
	uint64_t evaluate_invocations;
	uint64_t geometry_invocations;
	uint64_t geometry_primitives;
	uint64_t fragment_invocations;
	uint64_t compute_invocations;
	uint64_t clipping_invocations;
	uint64_t clipping_primitives;
} TSQueryStatistics;

/// Tellusim::Tracing
typedef TS_CALIGNAS16(struct) TSTracingInstance {
	float32_t transform[12];
	uint32_t data;
	uint32_t mask;
	uint32_t flags;
	uint32_t offset;
	TSTracing *tracing;
} TSTracingInstance;

typedef struct TSTracingBuildIndirect {
	uint32_t num_primitives;
	uint32_t base_primitive;
	uint32_t base_vertex;
	uint32_t base_transform;
} TSTracingBuildIndirect;

/// Tellusim::Device
typedef struct TSDeviceFeatures {
	uint8_t threadAccess;
	uint8_t bufferTable;
	uint8_t bufferSparse;
	uint8_t textureTable;
	uint8_t textureSparse;
	uint8_t textureArrayCube;
	uint8_t textureArraySparse;
	uint8_t surfaceMultisample;
	uint8_t drawBaseInstance;
	uint8_t drawIndirectIndex;
	uint8_t drawIndirectCount;
	uint8_t taskIndirectCount;
	uint8_t vertexStorage;
	uint8_t vertexIndexLayer;
	uint8_t geometryPassthrough;
	uint8_t fragmentBarycentric;
	uint8_t fragmentStencilExport;
	uint8_t blendDualSource;
	uint8_t depthRangeOneToOne;
	uint8_t rasterConservative;
	uint8_t renderConditional;
	uint8_t computeTracing;
	uint8_t fragmentTracing;
	uint8_t traversalTracing;
	uint8_t buildIndirectTracing;
	uint32_t maxTraversalDepth;
	uint8_t subgroupVote;
	uint8_t subgroupMath;
	uint8_t subgroupShuffle;
	uint32_t subgroupSize;
	uint32_t minSubgroupSize;
	uint32_t maxSubgroupSize;
	uint8_t shaderu8;
	uint8_t shaderf16;
	uint8_t shaderu16;
	uint8_t shaderf64;
	uint8_t shaderu64;
	uint8_t atomicGroupf32;
	uint8_t atomicGroupu64;
	uint8_t atomicBufferf32;
	uint8_t atomicBufferu64;
	uint8_t atomicTexturef32;
	uint8_t atomicTextureu32;
	uint8_t atomicTextureu64;
	uint8_t matrix16f16;
	uint8_t matrix16x8x8f16;
	uint8_t matrix16x8x16f16;
	uint8_t matrix16f16f32;
	uint8_t matrix16x8x8f16f32;
	uint8_t matrix16x8x16f16f32;
	uint32_t uniformAlignment;
	uint32_t storageAlignment;
	uint32_t maxTexture2DSize;
	uint32_t maxTexture3DSize;
	uint32_t maxTextureLayers;
	uint32_t maxTextureSamples;
	uint32_t maxGroupSizeX;
	uint32_t maxGroupSizeY;
	uint32_t maxGroupSizeZ;
	uint32_t maxGroupCountX;
	uint32_t maxGroupCountY;
	uint32_t maxGroupCountZ;
	uint32_t maxTaskCount;
	uint32_t maxTaskMemory;
	uint32_t maxTaskMeshes;
	uint32_t maxMeshMemory;
	uint32_t maxMeshVertices;
	uint32_t maxMeshPrimitives;
	uint32_t maxViewportCount;
	uint32_t maxClipCullCount;
	uint64_t maxUniformSize;
	uint64_t maxStorageSize;
	uint32_t groupMemory;
	uint64_t videoMemory;
	uint32_t vendorID;
	uint32_t deviceID;
	uint32_t pciBusID;
	uint32_t pciDomainID;
	uint32_t pciDeviceID;
} TSDeviceFeatures;

/// Tellusim::MeshModel
typedef struct TSMeshModelMeshlet {
	uint32_t num_primitives;
	uint32_t num_vertices;
	uint32_t base_index;
	uint32_t base_vertex;
	float32_t bound_sphere[4];
	float32_t normal_angle[4];
} TSMeshModelMeshlet;

/// Tellusim::PrefixScan
typedef struct TSPrefixScanDispatchParameters {
	uint32_t offset;
	uint32_t size;
	uint32_t padding_0;
	uint32_t padding_1;
} TSPrefixScanDispatchParameters;

/// Tellusim::RadixSort
typedef struct TSRadixSortDispatchParameters {
	uint32_t keys_offset;
	uint32_t data_offset;
	uint32_t size;
	uint32_t padding;
} TSRadixSortDispatchParameters;

/// Tellusim::BitonicSort
typedef struct TSBitonicSortDispatchParameters {
	uint32_t keys_offset;
	uint32_t data_offset;
	uint32_t size;
	uint32_t padding;
} TSBitonicSortDispatchParameters;

/// Tellusim::SpatialGrid
typedef struct TSSpatialGridDispatchParameters {
	uint32_t offset;
	uint32_t size;
	uint32_t padding_0;
	uint32_t padding_1;
} TSSpatialGridDispatchParameters;

/// Tellusim::SpatialTree
typedef struct TSSpatialTreeNode {
	float32_t bound_min[3];
	uint32_t is_enabled;
	float32_t bound_max[3];
	uint32_t data;
	uint32_t left;
	uint32_t right;
	uint32_t parent;
	uint32_t spatial;
} TSSpatialTreeNode;

typedef struct TSSpatialTreeLeafNodef16 {
	float32_t center[3];
	uint32_t data;
	uint16_t size[3];
	uint16_t is_enabled;
	uint32_t data_1;
	uint32_t data_2;
	uint32_t left;
	uint32_t right;
	uint32_t parent;
	uint32_t spatial;
} TSSpatialTreeLeafNodef16;

typedef struct TSSpatialTreeDispatchParameters {
	uint32_t offset;
	uint32_t size;
	uint32_t padding_0;
	uint32_t padding_1;
} TSSpatialTreeDispatchParameters;

/// Tellusim::String
TS_CAPI TSString TS_CCALL tsString_new(void);
TS_CAPI TSString TS_CCALL tsString_new_uc(uint32_t size, char c);
TS_CAPI TSString TS_CCALL tsString_new_su(const char *str, uint32_t length);
TS_CAPI TSString TS_CCALL tsString_new_wu(const wchar_t *str, uint32_t length);
TS_CAPI TSString TS_CCALL tsString_new_upu(const uint32_t *str, uint32_t length);
TS_CAPI void TS_CCALL tsString_delete(TSString self);
TS_CAPI void TS_CCALL tsString_reserve(TSString self, uint32_t size, bool_t discard);
TS_CAPI void TS_CCALL tsString_resize(TSString self, uint32_t size, char c, bool_t reserve);
TS_CAPI void TS_CCALL tsString_release(TSString self);
TS_CAPI void TS_CCALL tsString_clear(TSString self);
TS_CAPI void TS_CCALL tsString_copy_su(TSString self, const char *str, uint32_t length);
TS_CAPI void TS_CCALL tsString_copy_wu(TSString self, const wchar_t *str, uint32_t length);
TS_CAPI void TS_CCALL tsString_copy_upu(TSString self, const uint32_t *str, uint32_t length);
TS_CAPI void TS_CCALL tsString_copy_cSu(TSString self, const TSString string, uint32_t length);
TS_CAPI void TS_CCALL tsString_append_c(TSString self, char c);
TS_CAPI void TS_CCALL tsString_append_su(TSString self, const char *str, uint32_t length);
TS_CAPI void TS_CCALL tsString_append_cSu(TSString self, const TSString string, uint32_t length);
TS_CAPI void TS_CCALL tsString_insert_usu(TSString self, uint32_t pos, const char *str, uint32_t length);
TS_CAPI void TS_CCALL tsString_insert_ucSu(TSString self, uint32_t pos, const TSString string, uint32_t length);
TS_CAPI void TS_CCALL tsString_removeBack(TSString self, uint32_t length);
TS_CAPI void TS_CCALL tsString_remove(TSString self, uint32_t pos, uint32_t length);
TS_CAPI void TS_CCALL tsString_reverse(TSString self, uint32_t pos, uint32_t length);
TS_CAPI uint32_t TS_CCALL tsString_size(TSString self);
TS_CAPI bool_t TS_CCALL tsString_empty(TSString self);
TS_CAPI char* TS_CCALL tsString_get(TSString self);
TS_CAPI const char* TS_CCALL tsString_get_c(TSString self);
TS_CAPI char TS_CCALL tsString_get_u(TSString self, uint32_t index);
TS_CAPI char TS_CCALL tsString_get_cu(TSString self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsString_find_ccu(TSString self, char c, uint32_t pos);
TS_CAPI uint32_t TS_CCALL tsString_rfind_ccu(TSString self, char c, uint32_t pos);
TS_CAPI uint32_t TS_CCALL tsString_count_ccu(TSString self, char c, uint32_t pos);
TS_CAPI uint32_t TS_CCALL tsString_find_csu(TSString self, const char *str, uint32_t pos);
TS_CAPI uint32_t TS_CCALL tsString_rfind_csu(TSString self, const char *str, uint32_t pos);
TS_CAPI uint32_t TS_CCALL tsString_count_csu(TSString self, const char *str, uint32_t pos);
TS_CAPI bool_t TS_CCALL tsString_begins(TSString self, const char *str, uint32_t length, uint32_t pos);
TS_CAPI bool_t TS_CCALL tsString_contains(TSString self, const char *str, uint32_t length, uint32_t pos);
TS_CAPI bool_t TS_CCALL tsString_match(TSString self, const char *str, uint32_t length, uint32_t pos);
TS_CAPI int32_t TS_CCALL tsString_compare(TSString self, const char *str, uint32_t pos);
TS_CAPI uint32_t TS_CCALL tsString_distance(TSString self, const char *str, bool_t scan, uint32_t pos);
TS_CAPI const char* TS_CCALL tsString_begin(TSString self);
TS_CAPI const char* TS_CCALL tsString_end(TSString self);
TS_CAPI char TS_CCALL tsString_front_cu(TSString self, uint32_t index);
TS_CAPI char TS_CCALL tsString_back_cu(TSString self, uint32_t index);
TS_CAPI char TS_CCALL tsString_front_u(TSString self, uint32_t index);
TS_CAPI char TS_CCALL tsString_back_u(TSString self, uint32_t index);
TS_CAPI TSString TS_CCALL tsString_substring(TSString self, uint32_t pos, uint32_t length);
TS_CAPI TSString TS_CCALL tsString_replace_cccu(TSString self, char before, char after, uint32_t pos);
TS_CAPI TSString TS_CCALL tsString_replace_cssu(TSString self, const char *before, const char *after, uint32_t pos);
TS_CAPI TSString TS_CCALL tsString_replace_ccScSu(TSString self, const TSString before, const TSString after, uint32_t pos);
TS_CAPI TSString TS_CCALL tsString_extension_cs(TSString self, const char *extension);
TS_CAPI TSString TS_CCALL tsString_extension_c(TSString self);
TS_CAPI TSString TS_CCALL tsString_pathname(TSString self);
TS_CAPI TSString TS_CCALL tsString_basename(TSString self);
TS_CAPI TSString TS_CCALL tsString_dirname(TSString self);
TS_CAPI TSString TS_CCALL tsString_relname_ss(const char *path, const char *str);
TS_CAPI TSString TS_CCALL tsString_relname_cScS(const TSString path, const TSString str);
TS_CAPI TSString TS_CCALL tsString_capitalize(TSString self, const char *delimiters, const char *spaces);
TS_CAPI TSString TS_CCALL tsString_lower(TSString self);
TS_CAPI TSString TS_CCALL tsString_upper(TSString self);
TS_CAPI uint32_t TS_CCALL tsString_toUtf32_sur(const char *str, uint32_t *code);
TS_CAPI uint32_t TS_CCALL tsString_toUtf16(TSString self, wchar_t *d, uint32_t length);
TS_CAPI uint32_t TS_CCALL tsString_toUtf32_curu(TSString self, uint32_t *d, uint32_t length);
TS_CAPI uint32_t TS_CCALL tsString_fromUtf32_Su(TSString d, uint32_t code);
TS_CAPI TSString TS_CCALL tsString_fromUtf16(const wchar_t *str, uint32_t length);
TS_CAPI TSString TS_CCALL tsString_fromUtf32_upu(const uint32_t *str, uint32_t length);
TS_CAPI TSString TS_CCALL tsString_fromUrl_su(const char *str, uint32_t length);
TS_CAPI TSString TS_CCALL tsString_fromUrl_cSu(const TSString string, uint32_t length);
TS_CAPI uint32_t TS_CCALL tsString_vscanf(TSString self, const char *format, va_list args);
TS_CAPI void TS_CCALL tsString_vprintf(TSString self, const char *format, va_list args);
TS_CAPI TSString TS_CCALL tsString_vformat(const char *format, va_list args);
TS_CAPI TSString TS_CCALL tsString_fromi32_Siu(TSString d, int32_t value, uint32_t radix);
TS_CAPI TSString TS_CCALL tsString_fromi64_Si64u(TSString d, int64_t value, uint32_t radix);
TS_CAPI TSString TS_CCALL tsString_fromu32_Suu(TSString d, uint32_t value, uint32_t radix);
TS_CAPI TSString TS_CCALL tsString_fromu64_Su64u(TSString d, uint64_t value, uint32_t radix);
TS_CAPI TSString TS_CCALL tsString_fromf32_Sfubb(TSString d, float32_t value, uint32_t digits, bool_t compact, bool_t exponent);
TS_CAPI TSString TS_CCALL tsString_fromf64_Sf64ubb(TSString d, float64_t value, uint32_t digits, bool_t compact, bool_t exponent);
TS_CAPI TSString TS_CCALL tsString_fromi32_iu(int32_t value, uint32_t radix);
TS_CAPI TSString TS_CCALL tsString_fromi64_i64u(int64_t value, uint32_t radix);
TS_CAPI TSString TS_CCALL tsString_fromu32_uu(uint32_t value, uint32_t radix);
TS_CAPI TSString TS_CCALL tsString_fromu64_u64u(uint64_t value, uint32_t radix);
TS_CAPI TSString TS_CCALL tsString_fromf32_fubb(float32_t value, uint32_t digits, bool_t compact, bool_t exponent);
TS_CAPI TSString TS_CCALL tsString_fromf64_f64ubb(float64_t value, uint32_t digits, bool_t compact, bool_t exponent);
TS_CAPI int32_t TS_CCALL tsString_toi32_suur(const char *str, uint32_t radix, uint32_t *size);
TS_CAPI int64_t TS_CCALL tsString_toi64_suur(const char *str, uint32_t radix, uint32_t *size);
TS_CAPI uint32_t TS_CCALL tsString_tou32_suur(const char *str, uint32_t radix, uint32_t *size);
TS_CAPI uint64_t TS_CCALL tsString_tou64_suur(const char *str, uint32_t radix, uint32_t *size);
TS_CAPI int32_t TS_CCALL tsString_toi32_sur(const char *str, uint32_t *size);
TS_CAPI int64_t TS_CCALL tsString_toi64_sur(const char *str, uint32_t *size);
TS_CAPI uint32_t TS_CCALL tsString_tou32_sur(const char *str, uint32_t *size);
TS_CAPI uint64_t TS_CCALL tsString_tou64_sur(const char *str, uint32_t *size);
TS_CAPI float32_t TS_CCALL tsString_tof32_sur(const char *str, uint32_t *size);
TS_CAPI float64_t TS_CCALL tsString_tof64_sur(const char *str, uint32_t *size);
TS_CAPI int32_t TS_CCALL tsString_toi32_cuu(TSString self, uint32_t radix, uint32_t pos);
TS_CAPI int64_t TS_CCALL tsString_toi64_cuu(TSString self, uint32_t radix, uint32_t pos);
TS_CAPI uint32_t TS_CCALL tsString_tou32_cuu(TSString self, uint32_t radix, uint32_t pos);
TS_CAPI uint64_t TS_CCALL tsString_tou64_cuu(TSString self, uint32_t radix, uint32_t pos);
TS_CAPI float32_t TS_CCALL tsString_tof32_cu(TSString self, uint32_t pos);
TS_CAPI float64_t TS_CCALL tsString_tof64_cu(TSString self, uint32_t pos);
TS_CAPI uint32_t TS_CCALL tsString_toHashu32(TSString self, uint32_t pos);
TS_CAPI uint64_t TS_CCALL tsString_toHashu64(TSString self, uint32_t pos);
TS_CAPI uint32_t TS_CCALL tsString_toRGBAu8(TSString self, uint32_t pos);
TS_CAPI TSString TS_CCALL tsString_fromTime(uint64_t usec, uint32_t digits);
TS_CAPI TSString TS_CCALL tsString_fromBytes(uint64_t bytes, uint32_t digits);
TS_CAPI TSString TS_CCALL tsString_fromNumber(uint64_t value, uint32_t digits);
TS_CAPI TSString TS_CCALL tsString_fromFrequency(uint64_t hz, uint32_t digits);
TS_CAPI TSString TS_CCALL tsString_fromLength(float64_t distance, uint32_t digits);
TS_CAPI TSString TS_CCALL tsString_fromAngle(float64_t angle, uint32_t digits);
TS_CAPI uint64_t TS_CCALL tsString_toBytes_sur(const char *str, uint32_t *size);
TS_CAPI uint64_t TS_CCALL tsString_toNumber_sur(const char *str, uint32_t *size);
TS_CAPI uint64_t TS_CCALL tsString_toFrequency_sur(const char *str, uint32_t *size);
TS_CAPI float64_t TS_CCALL tsString_toLength_sur(const char *str, uint32_t *size);
TS_CAPI uint64_t TS_CCALL tsString_toBytes_cuur(TSString self, uint32_t pos, uint32_t *size);
TS_CAPI uint64_t TS_CCALL tsString_toNumber_cuur(TSString self, uint32_t pos, uint32_t *size);
TS_CAPI uint64_t TS_CCALL tsString_toFrequency_cuur(TSString self, uint32_t pos, uint32_t *size);
TS_CAPI float64_t TS_CCALL tsString_toLength_cuur(TSString self, uint32_t pos, uint32_t *size);

/// Tellusim::App
TS_CAPI TSApp TS_CCALL tsApp_new(int32_t argc, char **argv);
TS_CAPI void TS_CCALL tsApp_delete(TSApp self);
TS_CAPI void TS_CCALL tsApp_clear(TSApp self);
TS_CAPI TS_Platform TS_CCALL tsApp_getPlatform(TSApp self);
TS_CAPI uint32_t TS_CCALL tsApp_getDevice(TSApp self);
TS_CAPI uint32_t TS_CCALL tsApp_getWidth(TSApp self);
TS_CAPI uint32_t TS_CCALL tsApp_getHeight(TSApp self);
TS_CAPI uint32_t TS_CCALL tsApp_getMultisample(TSApp self);
TS_CAPI uint32_t TS_CCALL tsApp_getNumArguments(TSApp self);
TS_CAPI TSString TS_CCALL tsApp_getArgument_cu(TSApp self, uint32_t num);
TS_CAPI bool_t TS_CCALL tsApp_isArgument(TSApp self, const char *name);
TS_CAPI TSString TS_CCALL tsApp_getArgument_cs(TSApp self, const char *name);
TS_CAPI bool_t TS_CCALL tsApp_create(TSApp self, TS_Platform platform, uint32_t version);
TS_CAPI void TS_CCALL tsApp_setPlatform(TS_Platform platform, uint32_t device);
TS_CAPI void TS_CCALL tsApp_setSize(uint32_t width, uint32_t height, uint32_t multisample);
TS_CAPI bool_t TS_CCALL tsApp_isBuildCore(void);
TS_CAPI bool_t TS_CCALL tsApp_isBuildDebug(void);
TS_CAPI bool_t TS_CCALL tsApp_isBuildFloat64(void);
TS_CAPI TSString TS_CCALL tsApp_getBuildDate(void);
TS_CAPI TSString TS_CCALL tsApp_getBuildInfo(void);
TS_CAPI uint32_t TS_CCALL tsApp_getVersion(void);
TS_CAPI uint64_t TS_CCALL tsApp_getAPIHash(void);

/// Tellusim::Async
TS_CAPI TSAsync TS_CCALL tsAsync_new(void);
TS_CAPI void TS_CCALL tsAsync_delete(TSAsync self);
TS_CAPI bool_t TS_CCALL tsAsync_equalPtr(const TSAsync self, const TSAsync ptr);
TS_CAPI TSAsync TS_CCALL tsAsync_copyPtr(const TSAsync self);
TS_CAPI TSAsync TS_CCALL tsAsync_clonePtr(const TSAsync self);
TS_CAPI void TS_CCALL tsAsync_clearPtr(TSAsync self);
TS_CAPI void TS_CCALL tsAsync_destroyPtr(TSAsync self);
TS_CAPI void TS_CCALL tsAsync_acquirePtr(TSAsync self);
TS_CAPI void TS_CCALL tsAsync_unacquirePtr(TSAsync self);
TS_CAPI bool_t TS_CCALL tsAsync_isValidPtr(const TSAsync self);
TS_CAPI bool_t TS_CCALL tsAsync_isOwnerPtr(const TSAsync self);
TS_CAPI bool_t TS_CCALL tsAsync_isConstPtr(const TSAsync self);
TS_CAPI uint32_t TS_CCALL tsAsync_getCountPtr(const TSAsync self);
TS_CAPI const void* TS_CCALL tsAsync_getInternalPtr(const TSAsync self);
TS_CAPI bool_t TS_CCALL tsAsync_init(TSAsync self, uint32_t num);
TS_CAPI bool_t TS_CCALL tsAsync_shutdown(TSAsync self);
TS_CAPI bool_t TS_CCALL tsAsync_isInitialized(TSAsync self);
TS_CAPI uint32_t TS_CCALL tsAsync_getNumCores(void);
TS_CAPI uint32_t TS_CCALL tsAsync_getNumThreads(TSAsync self);
TS_CAPI void TS_CCALL tsAsync_clear(TSAsync self);
TS_CAPI uint32_t TS_CCALL tsAsync_getNumTasks(TSAsync self, bool_t check);
TS_CAPI bool_t TS_CCALL tsAsync_check_c(TSAsync self);
TS_CAPI bool_t TS_CCALL tsAsync_wait_c(TSAsync self);

/// Tellusim::Stream
TS_CAPI TSStream TS_CCALL tsStream_new(void);
TS_CAPI void TS_CCALL tsStream_delete(TSStream self);
TS_CAPI bool_t TS_CCALL tsStream_equalPtr(const TSStream self, const TSStream ptr);
TS_CAPI TSStream TS_CCALL tsStream_copyPtr(const TSStream self);
TS_CAPI TSStream TS_CCALL tsStream_clonePtr(const TSStream self);
TS_CAPI void TS_CCALL tsStream_clearPtr(TSStream self);
TS_CAPI void TS_CCALL tsStream_destroyPtr(TSStream self);
TS_CAPI void TS_CCALL tsStream_acquirePtr(TSStream self);
TS_CAPI void TS_CCALL tsStream_unacquirePtr(TSStream self);
TS_CAPI bool_t TS_CCALL tsStream_isValidPtr(const TSStream self);
TS_CAPI bool_t TS_CCALL tsStream_isOwnerPtr(const TSStream self);
TS_CAPI bool_t TS_CCALL tsStream_isConstPtr(const TSStream self);
TS_CAPI uint32_t TS_CCALL tsStream_getCountPtr(const TSStream self);
TS_CAPI const void* TS_CCALL tsStream_getInternalPtr(const TSStream self);
TS_CAPI TSStream TS_CCALL tsStream_move(TSStream self);
TS_CAPI bool_t TS_CCALL tsStream_isOpened(TSStream self);
TS_CAPI bool_t TS_CCALL tsStream_isMapped(TSStream self);
TS_CAPI bool_t TS_CCALL tsStream_isAvailable(TSStream self);
TS_CAPI size_t TS_CCALL tsStream_getSize(TSStream self);
TS_CAPI TSString TS_CCALL tsStream_getName(TSStream self);
TS_CAPI size_t TS_CCALL tsStream_tell(TSStream self);
TS_CAPI bool_t TS_CCALL tsStream_seek(TSStream self, size_t offset);
TS_CAPI bool_t TS_CCALL tsStream_seekBack(TSStream self, size_t offset);
TS_CAPI bool_t TS_CCALL tsStream_seekCur(TSStream self, int64_t offset);
TS_CAPI const uint8_t* TS_CCALL tsStream_getData(TSStream self);
TS_CAPI size_t TS_CCALL tsStream_read(TSStream self, void *dest, size_t size);
TS_CAPI size_t TS_CCALL tsStream_write(TSStream self, const void *src, size_t size);
TS_CAPI bool_t TS_CCALL tsStream_flush(TSStream self);
TS_CAPI bool_t TS_CCALL tsStream_puts_s(TSStream self, const char *str);
TS_CAPI bool_t TS_CCALL tsStream_puts_cS(TSStream self, const TSString str);
TS_CAPI bool_t TS_CCALL tsStream_vprintf(TSStream self, const char *format, va_list args);
TS_CAPI bool_t TS_CCALL tsStream_printf(TSStream self, const char *format);
TS_CAPI TSString TS_CCALL tsStream_gets(TSStream self, uint8_t *status);
TS_CAPI int8_t TS_CCALL tsStream_readi8(TSStream self, uint8_t *status);
TS_CAPI bool_t TS_CCALL tsStream_writei8(TSStream self, int8_t value);
TS_CAPI uint8_t TS_CCALL tsStream_readu8(TSStream self, uint8_t *status);
TS_CAPI bool_t TS_CCALL tsStream_writeu8(TSStream self, uint8_t value);
TS_CAPI int16_t TS_CCALL tsStream_readi16(TSStream self, uint8_t *status);
TS_CAPI bool_t TS_CCALL tsStream_writei16(TSStream self, int16_t value);
TS_CAPI uint16_t TS_CCALL tsStream_readu16(TSStream self, uint8_t *status);
TS_CAPI bool_t TS_CCALL tsStream_writeu16(TSStream self, uint16_t value);
TS_CAPI int32_t TS_CCALL tsStream_readi32(TSStream self, uint8_t *status);
TS_CAPI bool_t TS_CCALL tsStream_writei32(TSStream self, int32_t value);
TS_CAPI uint32_t TS_CCALL tsStream_readu32(TSStream self, uint8_t *status);
TS_CAPI bool_t TS_CCALL tsStream_writeu32(TSStream self, uint32_t value);
TS_CAPI int64_t TS_CCALL tsStream_readi64(TSStream self, uint8_t *status);
TS_CAPI bool_t TS_CCALL tsStream_writei64(TSStream self, int64_t value);
TS_CAPI uint64_t TS_CCALL tsStream_readu64(TSStream self, uint8_t *status);
TS_CAPI bool_t TS_CCALL tsStream_writeu64(TSStream self, uint64_t value);
TS_CAPI float32_t TS_CCALL tsStream_readf32(TSStream self, uint8_t *status);
TS_CAPI bool_t TS_CCALL tsStream_writef32(TSStream self, float32_t value);
TS_CAPI float64_t TS_CCALL tsStream_readf64(TSStream self, uint8_t *status);
TS_CAPI bool_t TS_CCALL tsStream_writef64(TSStream self, float64_t value);
TS_CAPI int32_t TS_CCALL tsStream_readi32e(TSStream self, uint8_t *status);
TS_CAPI bool_t TS_CCALL tsStream_writei32e(TSStream self, int32_t value);
TS_CAPI uint32_t TS_CCALL tsStream_readu32e(TSStream self, uint8_t *status);
TS_CAPI bool_t TS_CCALL tsStream_writeu32e(TSStream self, uint32_t value);
TS_CAPI int64_t TS_CCALL tsStream_readi64e(TSStream self, uint8_t *status);
TS_CAPI bool_t TS_CCALL tsStream_writei64e(TSStream self, int64_t value);
TS_CAPI uint64_t TS_CCALL tsStream_readu64e(TSStream self, uint8_t *status);
TS_CAPI bool_t TS_CCALL tsStream_writeu64e(TSStream self, uint64_t value);
TS_CAPI TSString TS_CCALL tsStream_readString_br(TSStream self, uint8_t *status);
TS_CAPI bool_t TS_CCALL tsStream_writeString_cS(TSStream self, const TSString str);
TS_CAPI bool_t TS_CCALL tsStream_writeString_s(TSStream self, const char *str);
TS_CAPI TSString TS_CCALL tsStream_readString_cbru(TSStream self, char term, uint8_t *status, uint32_t size);
TS_CAPI bool_t TS_CCALL tsStream_writeString_cSc(TSStream self, const TSString str, char term);
TS_CAPI bool_t TS_CCALL tsStream_writeString_sc(TSStream self, const char *str, char term);
TS_CAPI TSString TS_CCALL tsStream_readToken_br(TSStream self, uint8_t *status);
TS_CAPI bool_t TS_CCALL tsStream_readToken_Sb(TSStream self, TSString dest, bool_t clear);
TS_CAPI TSString TS_CCALL tsStream_readLine_br(TSStream self, uint8_t *status);
TS_CAPI bool_t TS_CCALL tsStream_readLine_Sbb(TSStream self, TSString dest, bool_t empty, bool_t clear);
TS_CAPI size_t TS_CCALL tsStream_readStream(TSStream self, TSStream dest, size_t size, uint8_t *status);
TS_CAPI size_t TS_CCALL tsStream_writeStream(TSStream self, TSStream src, size_t size, uint8_t *status);
TS_CAPI size_t TS_CCALL tsStream_readZip(TSStream self, void *dest, size_t size);
TS_CAPI size_t TS_CCALL tsStream_writeZip(TSStream self, const void *src, size_t size, int32_t level);
TS_CAPI size_t TS_CCALL tsStream_writeZipFast(TSStream self, const void *src, size_t size);
TS_CAPI size_t TS_CCALL tsStream_writeZipBest(TSStream self, const void *src, size_t size);
TS_CAPI size_t TS_CCALL tsStream_readLz4(TSStream self, void *dest, size_t size);
TS_CAPI size_t TS_CCALL tsStream_writeLz4(TSStream self, const void *src, size_t size, int32_t level);
TS_CAPI size_t TS_CCALL tsStream_writeLz4Fast(TSStream self, const void *src, size_t size);
TS_CAPI size_t TS_CCALL tsStream_writeLz4Best(TSStream self, const void *src, size_t size);
TS_CAPI size_t TS_CCALL tsStream_decodeZip(TSStream self, TSStream src, size_t size, uint8_t *status, int32_t window);
TS_CAPI size_t TS_CCALL tsStream_encodeZip(TSStream self, TSStream dest, size_t size, uint8_t *status, int32_t level);
TS_CAPI size_t TS_CCALL tsStream_encodeZipFast(TSStream self, TSStream dest, size_t size, uint8_t *status);
TS_CAPI size_t TS_CCALL tsStream_encodeZipBest(TSStream self, TSStream dest, size_t size, uint8_t *status);
TS_CAPI size_t TS_CCALL tsStream_decodeLz4(TSStream self, TSStream src, size_t size, uint8_t *status);
TS_CAPI size_t TS_CCALL tsStream_encodeLz4(TSStream self, TSStream dest, size_t size, uint8_t *status, int32_t level);
TS_CAPI size_t TS_CCALL tsStream_encodeLz4Fast(TSStream self, TSStream dest, size_t size, uint8_t *status);
TS_CAPI size_t TS_CCALL tsStream_encodeLz4Best(TSStream self, TSStream dest, size_t size, uint8_t *status);

/// Tellusim::Blob
TS_CAPI TSBlob TS_CCALL tsBlob_new_s(const char *name);
TS_CAPI TSBlob TS_CCALL tsBlob_new_cS(const TSString name);
TS_CAPI TSBlob TS_CCALL tsBlob_new_zs(size_t size, const char *name);
TS_CAPI TSBlob TS_CCALL tsBlob_new_u8pzs(const uint8_t *data, size_t size, const char *name);
TS_CAPI TSBlob TS_CCALL tsBlob_new_bls(const uint8_t (*blob)[256], const char *name);
TS_CAPI TSBlob TS_CCALL tsBlob_new_cBb(const TSBlob blob, bool_t move);
TS_CAPI void TS_CCALL tsBlob_delete(TSBlob self);
TS_CAPI bool_t TS_CCALL tsBlob_equalPtr(const TSBlob self, const TSBlob ptr);
TS_CAPI TSBlob TS_CCALL tsBlob_copyPtr(const TSBlob self);
TS_CAPI TSBlob TS_CCALL tsBlob_clonePtr(const TSBlob self);
TS_CAPI void TS_CCALL tsBlob_clearPtr(TSBlob self);
TS_CAPI void TS_CCALL tsBlob_destroyPtr(TSBlob self);
TS_CAPI void TS_CCALL tsBlob_acquirePtr(TSBlob self);
TS_CAPI void TS_CCALL tsBlob_unacquirePtr(TSBlob self);
TS_CAPI bool_t TS_CCALL tsBlob_isValidPtr(const TSBlob self);
TS_CAPI bool_t TS_CCALL tsBlob_isOwnerPtr(const TSBlob self);
TS_CAPI bool_t TS_CCALL tsBlob_isConstPtr(const TSBlob self);
TS_CAPI uint32_t TS_CCALL tsBlob_getCountPtr(const TSBlob self);
TS_CAPI const void* TS_CCALL tsBlob_getInternalPtr(const TSBlob self);
TS_CAPI void TS_CCALL tsBlob_release(TSBlob self);
TS_CAPI void TS_CCALL tsBlob_clear(TSBlob self);
TS_CAPI void TS_CCALL tsBlob_setName_s(TSBlob self, const char *name);
TS_CAPI void TS_CCALL tsBlob_setName_cS(TSBlob self, const TSString name);
TS_CAPI void TS_CCALL tsBlob_setSize(TSBlob self, size_t size);
TS_CAPI void TS_CCALL tsBlob_setCapacity(TSBlob self, size_t size);
TS_CAPI size_t TS_CCALL tsBlob_getCapacity(TSBlob self);
TS_CAPI bool_t TS_CCALL tsBlob_setData_u8pz(TSBlob self, const uint8_t *data, size_t size);
TS_CAPI bool_t TS_CCALL tsBlob_setData_bl(TSBlob self, const uint8_t (*blob)[256]);
TS_CAPI bool_t TS_CCALL tsBlob_setData_cB(TSBlob self, const TSBlob blob);
TS_CAPI const uint8_t* TS_CCALL tsBlob_getData_c(TSBlob self);
TS_CAPI uint8_t* TS_CCALL tsBlob_getData(TSBlob self);
TS_CAPI TSString TS_CCALL tsBlob_encodeBase64(TSBlob self, size_t size);
TS_CAPI bool_t TS_CCALL tsBlob_decodeBase64(TSBlob self, const char *src);
TS_CAPI void TS_CCALL tsBlob_getMD5_urz(TSBlob self, uint32_t hash[4], size_t size);
TS_CAPI TSString TS_CCALL tsBlob_getMD5_z(TSBlob self, size_t size);
TS_CAPI TSString TS_CCALL tsBlob_getMD5_cS(const TSString str);
TS_CAPI TSString TS_CCALL tsBlob_getMD5_pz(const void *src, size_t size);
TS_CAPI TSString TS_CCALL tsBlob_getMD5_Stz(TSStream src, size_t size);
TS_CAPI void TS_CCALL tsBlob_getSHA1_urz(TSBlob self, uint32_t hash[5], size_t size);
TS_CAPI TSString TS_CCALL tsBlob_getSHA1_z(TSBlob self, size_t size);
TS_CAPI TSString TS_CCALL tsBlob_getSHA1_cS(const TSString str);
TS_CAPI TSString TS_CCALL tsBlob_getSHA1_pz(const void *src, size_t size);
TS_CAPI TSString TS_CCALL tsBlob_getSHA1_Stz(TSStream src, size_t size);

/// Tellusim::File
TS_CAPI TSFile TS_CCALL tsFile_new(void);
TS_CAPI void TS_CCALL tsFile_delete(TSFile self);
TS_CAPI bool_t TS_CCALL tsFile_equalPtr(const TSFile self, const TSFile ptr);
TS_CAPI TSFile TS_CCALL tsFile_copyPtr(const TSFile self);
TS_CAPI TSFile TS_CCALL tsFile_clonePtr(const TSFile self);
TS_CAPI void TS_CCALL tsFile_clearPtr(TSFile self);
TS_CAPI void TS_CCALL tsFile_destroyPtr(TSFile self);
TS_CAPI void TS_CCALL tsFile_acquirePtr(TSFile self);
TS_CAPI void TS_CCALL tsFile_unacquirePtr(TSFile self);
TS_CAPI bool_t TS_CCALL tsFile_isValidPtr(const TSFile self);
TS_CAPI bool_t TS_CCALL tsFile_isOwnerPtr(const TSFile self);
TS_CAPI bool_t TS_CCALL tsFile_isConstPtr(const TSFile self);
TS_CAPI uint32_t TS_CCALL tsFile_getCountPtr(const TSFile self);
TS_CAPI const void* TS_CCALL tsFile_getInternalPtr(const TSFile self);
TS_CAPI bool_t TS_CCALL tsFile_open_ss(TSFile self, const char *name, const char *mode);
TS_CAPI bool_t TS_CCALL tsFile_open_cSs(TSFile self, const TSString name, const char *mode);
TS_CAPI bool_t TS_CCALL tsFile_open_iss(TSFile self, int32_t fd, const char *name, const char *mode);
TS_CAPI bool_t TS_CCALL tsFile_popen_ss(TSFile self, const char *command, const char *mode);
TS_CAPI bool_t TS_CCALL tsFile_popen_cSs(TSFile self, const TSString command, const char *mode);
TS_CAPI void TS_CCALL tsFile_close(TSFile self);
TS_CAPI bool_t TS_CCALL tsFile_isFile_s(const char *name);
TS_CAPI bool_t TS_CCALL tsFile_isFile_cS(const TSString name);
TS_CAPI uint64_t TS_CCALL tsFile_getMTime(const char *name);
TS_CAPI size_t TS_CCALL tsFile_getSize(const char *name);
TS_CAPI bool_t TS_CCALL tsFile_remove(const char *name);

/// Tellusim::Socket
TS_CAPI TSSocket TS_CCALL tsSocket_new(TS_SocketType type);
TS_CAPI void TS_CCALL tsSocket_delete(TSSocket self);
TS_CAPI bool_t TS_CCALL tsSocket_equalPtr(const TSSocket self, const TSSocket ptr);
TS_CAPI TSSocket TS_CCALL tsSocket_copyPtr(const TSSocket self);
TS_CAPI TSSocket TS_CCALL tsSocket_clonePtr(const TSSocket self);
TS_CAPI void TS_CCALL tsSocket_clearPtr(TSSocket self);
TS_CAPI void TS_CCALL tsSocket_destroyPtr(TSSocket self);
TS_CAPI void TS_CCALL tsSocket_acquirePtr(TSSocket self);
TS_CAPI void TS_CCALL tsSocket_unacquirePtr(TSSocket self);
TS_CAPI bool_t TS_CCALL tsSocket_isValidPtr(const TSSocket self);
TS_CAPI bool_t TS_CCALL tsSocket_isOwnerPtr(const TSSocket self);
TS_CAPI bool_t TS_CCALL tsSocket_isConstPtr(const TSSocket self);
TS_CAPI uint32_t TS_CCALL tsSocket_getCountPtr(const TSSocket self);
TS_CAPI const void* TS_CCALL tsSocket_getInternalPtr(const TSSocket self);
TS_CAPI bool_t TS_CCALL tsSocket_open_u16u16(TSSocket self, uint16_t port, uint16_t num);
TS_CAPI bool_t TS_CCALL tsSocket_open_su16(TSSocket self, const char *name, uint16_t port);
TS_CAPI bool_t TS_CCALL tsSocket_open_cSu16(TSSocket self, const TSString name, uint16_t port);
TS_CAPI void TS_CCALL tsSocket_close(TSSocket self);
TS_CAPI bool_t TS_CCALL tsSocket_connect(TSSocket self, uint32_t sec, uint32_t usec);
TS_CAPI bool_t TS_CCALL tsSocket_accept(TSSocket self, TSSocket socket);
TS_CAPI bool_t TS_CCALL tsSocket_select(TSSocket self, uint32_t sec, uint32_t usec);
TS_CAPI bool_t TS_CCALL tsSocket_setTimeout(TSSocket self, uint32_t sec);
TS_CAPI uint32_t TS_CCALL tsSocket_getTimeout(TSSocket self);
TS_CAPI bool_t TS_CCALL tsSocket_setBlock(TSSocket self, bool_t block);
TS_CAPI bool_t TS_CCALL tsSocket_getBlock(TSSocket self);
TS_CAPI bool_t TS_CCALL tsSocket_setDelay(TSSocket self, bool_t delay);
TS_CAPI bool_t TS_CCALL tsSocket_getDelay(TSSocket self);
TS_CAPI void TS_CCALL tsSocket_setName_s(TSSocket self, const char *name);
TS_CAPI void TS_CCALL tsSocket_setName_cS(TSSocket self, const TSString name);
TS_CAPI uint16_t TS_CCALL tsSocket_getPort(TSSocket self);
TS_CAPI int32_t TS_CCALL tsSocket_getFD(TSSocket self);
TS_CAPI TS_SocketType TS_CCALL tsSocket_getType(TSSocket self);
TS_CAPI TSString TS_CCALL tsSocket_getAddress(const char *delimiter);

/// Tellusim::SocketSSL
TS_CAPI TSSocketSSL TS_CCALL tsSocketSSL_new(void);
TS_CAPI void TS_CCALL tsSocketSSL_delete(TSSocketSSL self);
TS_CAPI bool_t TS_CCALL tsSocketSSL_equalPtr(const TSSocketSSL self, const TSSocketSSL ptr);
TS_CAPI TSSocketSSL TS_CCALL tsSocketSSL_copyPtr(const TSSocketSSL self);
TS_CAPI TSSocketSSL TS_CCALL tsSocketSSL_clonePtr(const TSSocketSSL self);
TS_CAPI void TS_CCALL tsSocketSSL_clearPtr(TSSocketSSL self);
TS_CAPI void TS_CCALL tsSocketSSL_destroyPtr(TSSocketSSL self);
TS_CAPI void TS_CCALL tsSocketSSL_acquirePtr(TSSocketSSL self);
TS_CAPI void TS_CCALL tsSocketSSL_unacquirePtr(TSSocketSSL self);
TS_CAPI bool_t TS_CCALL tsSocketSSL_isValidPtr(const TSSocketSSL self);
TS_CAPI bool_t TS_CCALL tsSocketSSL_isOwnerPtr(const TSSocketSSL self);
TS_CAPI bool_t TS_CCALL tsSocketSSL_isConstPtr(const TSSocketSSL self);
TS_CAPI uint32_t TS_CCALL tsSocketSSL_getCountPtr(const TSSocketSSL self);
TS_CAPI const void* TS_CCALL tsSocketSSL_getInternalPtr(const TSSocketSSL self);
TS_CAPI bool_t TS_CCALL tsSocketSSL_equalSocketPtr(const TSSocketSSL self, const TSSocket base);
TS_CAPI TSSocketSSL TS_CCALL tsSocketSSL_castSocketPtr(TSSocket base);
TS_CAPI TSSocket TS_CCALL tsSocketSSL_baseSocketPtr(TSSocketSSL self);
TS_CAPI bool_t TS_CCALL tsSocketSSL_handshake(TSSocketSSL self, const char *name);
TS_CAPI bool_t TS_CCALL tsSocketSSL_accept_SS(TSSocketSSL self, TSSocketSSL socket);
TS_CAPI bool_t TS_CCALL tsSocketSSL_accept_S(TSSocketSSL self, TSSocket socket);
TS_CAPI bool_t TS_CCALL tsSocketSSL_load_St(TSSocketSSL self, TSStream stream);
TS_CAPI bool_t TS_CCALL tsSocketSSL_load_s(TSSocketSSL self, const char *name);
TS_CAPI bool_t TS_CCALL tsSocketSSL_load_cS(TSSocketSSL self, const TSString name);
TS_CAPI bool_t TS_CCALL tsSocketSSL_isConnected(TSSocketSSL self);

/// Tellusim::Source
TS_CAPI TSSource TS_CCALL tsSource_new(void);
TS_CAPI TSSource TS_CCALL tsSource_new_u8pzs(const uint8_t *data, size_t size, const char *name);
TS_CAPI void TS_CCALL tsSource_delete(TSSource self);
TS_CAPI bool_t TS_CCALL tsSource_equalPtr(const TSSource self, const TSSource ptr);
TS_CAPI TSSource TS_CCALL tsSource_copyPtr(const TSSource self);
TS_CAPI TSSource TS_CCALL tsSource_clonePtr(const TSSource self);
TS_CAPI void TS_CCALL tsSource_clearPtr(TSSource self);
TS_CAPI void TS_CCALL tsSource_destroyPtr(TSSource self);
TS_CAPI void TS_CCALL tsSource_acquirePtr(TSSource self);
TS_CAPI void TS_CCALL tsSource_unacquirePtr(TSSource self);
TS_CAPI bool_t TS_CCALL tsSource_isValidPtr(const TSSource self);
TS_CAPI bool_t TS_CCALL tsSource_isOwnerPtr(const TSSource self);
TS_CAPI bool_t TS_CCALL tsSource_isConstPtr(const TSSource self);
TS_CAPI uint32_t TS_CCALL tsSource_getCountPtr(const TSSource self);
TS_CAPI const void* TS_CCALL tsSource_getInternalPtr(const TSSource self);
TS_CAPI bool_t TS_CCALL tsSource_open_sbb(TSSource self, const char *name, bool_t callback, bool_t write);
TS_CAPI bool_t TS_CCALL tsSource_open_cSbb(TSSource self, const TSString name, bool_t callback, bool_t write);
TS_CAPI void TS_CCALL tsSource_close(TSSource self);
TS_CAPI void TS_CCALL tsSource_setName_szz(TSSource self, const char *name, size_t offset, size_t size);
TS_CAPI void TS_CCALL tsSource_setName_cSzz(TSSource self, const TSString name, size_t offset, size_t size);
TS_CAPI void TS_CCALL tsSource_setData(TSSource self, const uint8_t *data, size_t size, const char *name);
TS_CAPI bool_t TS_CCALL tsSource_isSource_s(const char *name);
TS_CAPI bool_t TS_CCALL tsSource_isSource_cS(const TSString name);
TS_CAPI uint64_t TS_CCALL tsSource_getMTime(const char *name);
TS_CAPI size_t TS_CCALL tsSource_getSize(const char *name);
TS_CAPI void TS_CCALL tsSource_setCallback_SOCpr(TSSourceOpenCallback open_func, void *data);
TS_CAPI void TS_CCALL tsSource_setCallback_SOCSICpr(TSSourceOpenCallback open_func, TSSourceIsCallback is_func, void *data);
TS_CAPI void* TS_CCALL tsSource_getCallbackData(void);

/// Tellusim::Date
TS_CAPI TSDate TS_CCALL tsDate_new(void);
TS_CAPI TSDate TS_CCALL tsDate_new_i64b(int64_t time, bool_t local);
TS_CAPI TSDate TS_CCALL tsDate_new_ss(const char *str, const char *format);
TS_CAPI void TS_CCALL tsDate_delete(TSDate self);
TS_CAPI bool_t TS_CCALL tsDate_equalPtr(const TSDate self, const TSDate ptr);
TS_CAPI TSDate TS_CCALL tsDate_copyPtr(const TSDate self);
TS_CAPI TSDate TS_CCALL tsDate_clonePtr(const TSDate self);
TS_CAPI void TS_CCALL tsDate_clearPtr(TSDate self);
TS_CAPI void TS_CCALL tsDate_destroyPtr(TSDate self);
TS_CAPI void TS_CCALL tsDate_acquirePtr(TSDate self);
TS_CAPI void TS_CCALL tsDate_unacquirePtr(TSDate self);
TS_CAPI bool_t TS_CCALL tsDate_isValidPtr(const TSDate self);
TS_CAPI bool_t TS_CCALL tsDate_isOwnerPtr(const TSDate self);
TS_CAPI bool_t TS_CCALL tsDate_isConstPtr(const TSDate self);
TS_CAPI uint32_t TS_CCALL tsDate_getCountPtr(const TSDate self);
TS_CAPI const void* TS_CCALL tsDate_getInternalPtr(const TSDate self);
TS_CAPI void TS_CCALL tsDate_clear(TSDate self);
TS_CAPI void TS_CCALL tsDate_setTime(TSDate self, int64_t time, bool_t local);
TS_CAPI int64_t TS_CCALL tsDate_getTime(TSDate self, bool_t local);
TS_CAPI bool_t TS_CCALL tsDate_setString(TSDate self, const char *str, const char *format);
TS_CAPI TSString TS_CCALL tsDate_getString(TSDate self, const char *format);
TS_CAPI void TS_CCALL tsDate_setYear(TSDate self, uint32_t year);
TS_CAPI void TS_CCALL tsDate_setMonth(TSDate self, uint32_t month);
TS_CAPI void TS_CCALL tsDate_setDate(TSDate self, uint32_t date);
TS_CAPI void TS_CCALL tsDate_setDay(TSDate self, uint32_t day);
TS_CAPI void TS_CCALL tsDate_setHours(TSDate self, uint32_t hours);
TS_CAPI void TS_CCALL tsDate_setMinutes(TSDate self, uint32_t minutes);
TS_CAPI void TS_CCALL tsDate_setSeconds(TSDate self, uint32_t seconds);
TS_CAPI uint32_t TS_CCALL tsDate_getYear(TSDate self);
TS_CAPI uint32_t TS_CCALL tsDate_getMonth(TSDate self);
TS_CAPI uint32_t TS_CCALL tsDate_getDate(TSDate self);
TS_CAPI uint32_t TS_CCALL tsDate_getDay(TSDate self);
TS_CAPI uint32_t TS_CCALL tsDate_getHours(TSDate self);
TS_CAPI uint32_t TS_CCALL tsDate_getMinutes(TSDate self);
TS_CAPI uint32_t TS_CCALL tsDate_getSeconds(TSDate self);
TS_CAPI int32_t TS_CCALL tsDate_getTimeZone(void);

/// Tellusim::Info
TS_CAPI TSInfo TS_CCALL tsInfo_new(void);
TS_CAPI void TS_CCALL tsInfo_delete(TSInfo self);
TS_CAPI bool_t TS_CCALL tsInfo_equalPtr(const TSInfo self, const TSInfo ptr);
TS_CAPI TSInfo TS_CCALL tsInfo_copyPtr(const TSInfo self);
TS_CAPI TSInfo TS_CCALL tsInfo_clonePtr(const TSInfo self);
TS_CAPI void TS_CCALL tsInfo_clearPtr(TSInfo self);
TS_CAPI void TS_CCALL tsInfo_destroyPtr(TSInfo self);
TS_CAPI void TS_CCALL tsInfo_acquirePtr(TSInfo self);
TS_CAPI void TS_CCALL tsInfo_unacquirePtr(TSInfo self);
TS_CAPI bool_t TS_CCALL tsInfo_isValidPtr(const TSInfo self);
TS_CAPI bool_t TS_CCALL tsInfo_isOwnerPtr(const TSInfo self);
TS_CAPI bool_t TS_CCALL tsInfo_isConstPtr(const TSInfo self);
TS_CAPI uint32_t TS_CCALL tsInfo_getCountPtr(const TSInfo self);
TS_CAPI const void* TS_CCALL tsInfo_getInternalPtr(const TSInfo self);
TS_CAPI size_t TS_CCALL tsInfo_getSystemMemory(TSInfo self);
TS_CAPI uint64_t TS_CCALL tsInfo_getSystemUptime(TSInfo self);
TS_CAPI TSString TS_CCALL tsInfo_getSystemName(TSInfo self);
TS_CAPI TSString TS_CCALL tsInfo_getSystemVersion(TSInfo self);
TS_CAPI TSString TS_CCALL tsInfo_getKernelVersion(TSInfo self);
TS_CAPI uint32_t TS_CCALL tsInfo_getCPUCount(TSInfo self);
TS_CAPI TSString TS_CCALL tsInfo_getCPUName(TSInfo self, uint32_t index);
TS_CAPI TSString TS_CCALL tsInfo_getCPUVendor(TSInfo self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsInfo_getCPUCores(TSInfo self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsInfo_getCPUThreads(TSInfo self, uint32_t index);
TS_CAPI uint64_t TS_CCALL tsInfo_getCPUFrequency(TSInfo self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsInfo_getCPUTemperature(TSInfo self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsInfo_getCPUUtilization(TSInfo self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsInfo_getCPUFanSpeed(TSInfo self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsInfo_getCPUPower(TSInfo self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsInfo_getGPUCount(TSInfo self);
TS_CAPI TSString TS_CCALL tsInfo_getGPUName(TSInfo self, uint32_t index);
TS_CAPI TSString TS_CCALL tsInfo_getGPUVendor(TSInfo self, uint32_t index);
TS_CAPI TSString TS_CCALL tsInfo_getGPUSerial(TSInfo self, uint32_t index);
TS_CAPI TSString TS_CCALL tsInfo_getGPUDevice(TSInfo self, uint32_t index);
TS_CAPI TSString TS_CCALL tsInfo_getGPUVersion(TSInfo self, uint32_t index);
TS_CAPI size_t TS_CCALL tsInfo_getGPUMemory(TSInfo self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsInfo_getGPUScreens(TSInfo self, uint32_t index);
TS_CAPI uint64_t TS_CCALL tsInfo_getGPUFrequency(TSInfo self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsInfo_getGPUTemperature(TSInfo self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsInfo_getGPUUtilization(TSInfo self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsInfo_getGPUFanSpeed(TSInfo self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsInfo_getGPUPower(TSInfo self, uint32_t index);
TS_CAPI bool_t TS_CCALL tsInfo_isGPUThrottling(TSInfo self, uint32_t index);

/// Tellusim::Directory
TS_CAPI TSDirectory TS_CCALL tsDirectory_new(void);
TS_CAPI void TS_CCALL tsDirectory_delete(TSDirectory self);
TS_CAPI bool_t TS_CCALL tsDirectory_equalPtr(const TSDirectory self, const TSDirectory ptr);
TS_CAPI TSDirectory TS_CCALL tsDirectory_copyPtr(const TSDirectory self);
TS_CAPI TSDirectory TS_CCALL tsDirectory_clonePtr(const TSDirectory self);
TS_CAPI void TS_CCALL tsDirectory_clearPtr(TSDirectory self);
TS_CAPI void TS_CCALL tsDirectory_destroyPtr(TSDirectory self);
TS_CAPI void TS_CCALL tsDirectory_acquirePtr(TSDirectory self);
TS_CAPI void TS_CCALL tsDirectory_unacquirePtr(TSDirectory self);
TS_CAPI bool_t TS_CCALL tsDirectory_isValidPtr(const TSDirectory self);
TS_CAPI bool_t TS_CCALL tsDirectory_isOwnerPtr(const TSDirectory self);
TS_CAPI bool_t TS_CCALL tsDirectory_isConstPtr(const TSDirectory self);
TS_CAPI uint32_t TS_CCALL tsDirectory_getCountPtr(const TSDirectory self);
TS_CAPI const void* TS_CCALL tsDirectory_getInternalPtr(const TSDirectory self);
TS_CAPI bool_t TS_CCALL tsDirectory_open_sb(TSDirectory self, const char *name, bool_t children);
TS_CAPI bool_t TS_CCALL tsDirectory_open_cSb(TSDirectory self, const TSString name, bool_t children);
TS_CAPI void TS_CCALL tsDirectory_close(TSDirectory self);
TS_CAPI bool_t TS_CCALL tsDirectory_isOpened(TSDirectory self);
TS_CAPI TSString TS_CCALL tsDirectory_getName(TSDirectory self);
TS_CAPI uint32_t TS_CCALL tsDirectory_getNumFiles(TSDirectory self);
TS_CAPI TSString TS_CCALL tsDirectory_getFileName(TSDirectory self, uint32_t index);
TS_CAPI TS_DirectoryAttributes TS_CCALL tsDirectory_getFileAttributes_cu(TSDirectory self, uint32_t index);
TS_CAPI uint64_t TS_CCALL tsDirectory_getFileMTime_cu(TSDirectory self, uint32_t index);
TS_CAPI uint64_t TS_CCALL tsDirectory_getFileATime_cu(TSDirectory self, uint32_t index);
TS_CAPI uint64_t TS_CCALL tsDirectory_getFileCTime_cu(TSDirectory self, uint32_t index);
TS_CAPI size_t TS_CCALL tsDirectory_getFileSize_cu(TSDirectory self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsDirectory_getNumDirectories(TSDirectory self);
TS_CAPI TSString TS_CCALL tsDirectory_getDirectoryName(TSDirectory self, uint32_t index);
TS_CAPI TS_DirectoryAttributes TS_CCALL tsDirectory_getDirectoryAttributes(TSDirectory self, uint32_t index);
TS_CAPI uint64_t TS_CCALL tsDirectory_getDirectoryCTime(TSDirectory self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsDirectory_getDirectorySize(TSDirectory self, uint32_t index);
TS_CAPI bool_t TS_CCALL tsDirectory_isFile_s(const char *name);
TS_CAPI bool_t TS_CCALL tsDirectory_isFile_cS(const TSString name);
TS_CAPI bool_t TS_CCALL tsDirectory_setFileAttributes(const char *name, TS_DirectoryAttributes attributes);
TS_CAPI TS_DirectoryAttributes TS_CCALL tsDirectory_getFileAttributes_s(const char *name);
TS_CAPI bool_t TS_CCALL tsDirectory_setFileMTime(const char *name, uint64_t time);
TS_CAPI uint64_t TS_CCALL tsDirectory_getFileMTime_s(const char *name);
TS_CAPI uint64_t TS_CCALL tsDirectory_getFileATime_s(const char *name);
TS_CAPI uint64_t TS_CCALL tsDirectory_getFileCTime_s(const char *name);
TS_CAPI size_t TS_CCALL tsDirectory_getFileSize_s(const char *name);
TS_CAPI size_t TS_CCALL tsDirectory_getFileSize_cS(const TSString name);
TS_CAPI bool_t TS_CCALL tsDirectory_removeFile_s(const char *name);
TS_CAPI bool_t TS_CCALL tsDirectory_removeFile_cS(const TSString name);
TS_CAPI bool_t TS_CCALL tsDirectory_copyFile_ssb(const char *name, const char *new_name, bool_t attributes);
TS_CAPI bool_t TS_CCALL tsDirectory_copyFile_cScSb(const TSString name, const TSString new_name, bool_t attributes);
TS_CAPI bool_t TS_CCALL tsDirectory_isDirectory_s(const char *name);
TS_CAPI bool_t TS_CCALL tsDirectory_isDirectory_cS(const TSString name);
TS_CAPI bool_t TS_CCALL tsDirectory_changeDirectory_s(const char *name);
TS_CAPI bool_t TS_CCALL tsDirectory_changeDirectory_cS(const TSString name);
TS_CAPI bool_t TS_CCALL tsDirectory_createDirectory_sb(const char *name, bool_t children);
TS_CAPI bool_t TS_CCALL tsDirectory_createDirectory_cSb(const TSString name, bool_t children);
TS_CAPI bool_t TS_CCALL tsDirectory_removeDirectory_sb(const char *name, bool_t children);
TS_CAPI bool_t TS_CCALL tsDirectory_removeDirectory_cSb(const TSString name, bool_t children);
TS_CAPI bool_t TS_CCALL tsDirectory_copyDirectory_ssb(const char *name, const char *new_name, bool_t attributes);
TS_CAPI bool_t TS_CCALL tsDirectory_copyDirectory_cScSb(const TSString name, const TSString new_name, bool_t attributes);
TS_CAPI bool_t TS_CCALL tsDirectory_rename_ss(const char *name, const char *new_name);
TS_CAPI bool_t TS_CCALL tsDirectory_rename_cScS(const TSString name, const TSString new_name);
TS_CAPI TSString TS_CCALL tsDirectory_getCurrentDirectory(void);
TS_CAPI TSString TS_CCALL tsDirectory_getBinaryDirectory(void);
TS_CAPI TSString TS_CCALL tsDirectory_getHomeDirectory(void);
TS_CAPI TSString TS_CCALL tsDirectory_getTempDirectory(void);
TS_CAPI TSString TS_CCALL tsDirectory_getConfigDirectory(void);
TS_CAPI TSString TS_CCALL tsDirectory_getDocumentsDirectory(void);

/// Tellusim::Archive
TS_CAPI TSArchive TS_CCALL tsArchive_new(void);
TS_CAPI void TS_CCALL tsArchive_delete(TSArchive self);
TS_CAPI bool_t TS_CCALL tsArchive_open_ss(TSArchive self, const char *name, const char *type);
TS_CAPI bool_t TS_CCALL tsArchive_open_cSs(TSArchive self, const TSString name, const char *type);
TS_CAPI bool_t TS_CCALL tsArchive_open_Sts(TSArchive self, TSStream stream, const char *type);
TS_CAPI void TS_CCALL tsArchive_close(TSArchive self);
TS_CAPI bool_t TS_CCALL tsArchive_isOpened(TSArchive self);
TS_CAPI TSString TS_CCALL tsArchive_getName(TSArchive self);
TS_CAPI uint32_t TS_CCALL tsArchive_getNumFiles(TSArchive self);
TS_CAPI TSString TS_CCALL tsArchive_getFileName(TSArchive self, uint32_t index);
TS_CAPI uint64_t TS_CCALL tsArchive_getFileMTime(TSArchive self, uint32_t index);
TS_CAPI size_t TS_CCALL tsArchive_getFileSize(TSArchive self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsArchive_findFile_cs(TSArchive self, const char *name);
TS_CAPI uint32_t TS_CCALL tsArchive_findFile_ccS(TSArchive self, const TSString name);
TS_CAPI bool_t TS_CCALL tsArchive_isFile_cs(TSArchive self, const char *name);
TS_CAPI bool_t TS_CCALL tsArchive_isFile_ccS(TSArchive self, const TSString name);
TS_CAPI TSStream TS_CCALL tsArchive_openFile_cs(TSArchive self, const char *name);
TS_CAPI TSStream TS_CCALL tsArchive_openFile_ccS(TSArchive self, const TSString name);
TS_CAPI TSStream TS_CCALL tsArchive_openFile_cu(TSArchive self, uint32_t index);

/// Tellusim::Image
TS_CAPI TSImage TS_CCALL tsImage_new(void);
TS_CAPI TSImage TS_CCALL tsImage_new_sIFu(const char *name, TS_ImageFlags flags, uint32_t offset);
TS_CAPI TSImage TS_CCALL tsImage_new_StIFu(TSStream stream, TS_ImageFlags flags, uint32_t offset);
TS_CAPI TSImage TS_CCALL tsImage_new_ITFcSIF(TS_ImageType type, TS_Format format, const TSSize *size, TS_ImageFlags flags);
TS_CAPI TSImage TS_CCALL tsImage_new_ITFcSuIF(TS_ImageType type, TS_Format format, const TSSize *size, uint32_t layers, TS_ImageFlags flags);
TS_CAPI void TS_CCALL tsImage_delete(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_equalPtr(const TSImage self, const TSImage ptr);
TS_CAPI TSImage TS_CCALL tsImage_copyPtr(const TSImage self);
TS_CAPI TSImage TS_CCALL tsImage_clonePtr(const TSImage self);
TS_CAPI void TS_CCALL tsImage_clearPtr(TSImage self);
TS_CAPI void TS_CCALL tsImage_destroyPtr(TSImage self);
TS_CAPI void TS_CCALL tsImage_acquirePtr(TSImage self);
TS_CAPI void TS_CCALL tsImage_unacquirePtr(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isValidPtr(const TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isOwnerPtr(const TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isConstPtr(const TSImage self);
TS_CAPI uint32_t TS_CCALL tsImage_getCountPtr(const TSImage self);
TS_CAPI const void* TS_CCALL tsImage_getInternalPtr(const TSImage self);
TS_CAPI void TS_CCALL tsImage_clear(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isLoaded(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isAllocated(TSImage self);
TS_CAPI TS_ImageType TS_CCALL tsImage_getType(TSImage self);
TS_CAPI const char* TS_CCALL tsImage_getTypeName_IT(TS_ImageType type);
TS_CAPI const char* TS_CCALL tsImage_getTypeName_c(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_is2DType(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_is3DType(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isCubeType(TSImage self);
TS_CAPI TS_Format TS_CCALL tsImage_getFormat(TSImage self);
TS_CAPI const char* TS_CCALL tsImage_getFormatName(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isColorFormat(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isDepthFormat(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isPixelFormat(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isPlainFormat(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isMixedFormat(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isBlockFormat(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isStencilFormat(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isNormFormat(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isSRGBFormat(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isFloatFormat(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isSignedFormat(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isUnsignedFormat(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isIntegerFormat(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isi8Format(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isu8Format(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_is8BitFormat(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isi16Format(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isu16Format(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isf16Format(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_is16BitFormat(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isi32Format(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isu32Format(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isf32Format(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_is32BitFormat(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isi64Format(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isu64Format(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isf64Format(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_is64BitFormat(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isBC15Format(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isBC67Format(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isETC2Format(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_isASTCFormat(TSImage self);
TS_CAPI uint32_t TS_CCALL tsImage_getComponents(TSImage self);
TS_CAPI uint32_t TS_CCALL tsImage_getPixelSize(TSImage self);
TS_CAPI uint32_t TS_CCALL tsImage_getBlockSize(TSImage self);
TS_CAPI uint32_t TS_CCALL tsImage_getBlockWidth(TSImage self);
TS_CAPI uint32_t TS_CCALL tsImage_getBlockHeight(TSImage self);
TS_CAPI uint32_t TS_CCALL tsImage_getWidth_c(TSImage self);
TS_CAPI uint32_t TS_CCALL tsImage_getHeight_c(TSImage self);
TS_CAPI uint32_t TS_CCALL tsImage_getDepth_c(TSImage self);
TS_CAPI uint32_t TS_CCALL tsImage_getFaces(TSImage self);
TS_CAPI uint32_t TS_CCALL tsImage_getLayers(TSImage self);
TS_CAPI uint32_t TS_CCALL tsImage_getMipmaps(TSImage self);
TS_CAPI uint32_t TS_CCALL tsImage_findMipmap(TSImage self, const TSSize *size);
TS_CAPI uint32_t TS_CCALL tsImage_getWidth_cu(TSImage self, uint32_t mipmap);
TS_CAPI uint32_t TS_CCALL tsImage_getHeight_cu(TSImage self, uint32_t mipmap);
TS_CAPI uint32_t TS_CCALL tsImage_getDepth_cu(TSImage self, uint32_t mipmap);
TS_CAPI bool_t TS_CCALL tsImage_hasLayers(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_hasMipmaps(TSImage self);
TS_CAPI TSSize TS_CCALL tsImage_getSize_c(TSImage self);
TS_CAPI TSRegion TS_CCALL tsImage_getRegion_c(TSImage self);
TS_CAPI TSSlice TS_CCALL tsImage_getSlice_c(TSImage self);
TS_CAPI TSSize TS_CCALL tsImage_getSize_cu(TSImage self, uint32_t mipmap);
TS_CAPI TSRegion TS_CCALL tsImage_getRegion_cu(TSImage self, uint32_t mipmap);
TS_CAPI TSSlice TS_CCALL tsImage_getSlice_cu(TSImage self, uint32_t mipmap);
TS_CAPI void TS_CCALL tsImage_setMetaInfo(TSImage self, const TSString str);
TS_CAPI TSString TS_CCALL tsImage_getMetaInfo(TSImage self);
TS_CAPI TSString TS_CCALL tsImage_getDescription(TSImage self);
TS_CAPI size_t TS_CCALL tsImage_getOffset(TSImage self, const TSSlice *slice, uint32_t alignment);
TS_CAPI size_t TS_CCALL tsImage_getStride(TSImage self, uint32_t mipmap, uint32_t alignment);
TS_CAPI size_t TS_CCALL tsImage_getMipmapSize(TSImage self, uint32_t mipmap, uint32_t alignment);
TS_CAPI size_t TS_CCALL tsImage_getLayerSize(TSImage self, uint32_t alignment);
TS_CAPI size_t TS_CCALL tsImage_getDataSize(TSImage self, uint32_t alignment);
TS_CAPI bool_t TS_CCALL tsImage_create_ITFcSIF(TSImage self, TS_ImageType type, TS_Format format, const TSSize *size, TS_ImageFlags flags);
TS_CAPI bool_t TS_CCALL tsImage_create_ITFcSuIF(TSImage self, TS_ImageType type, TS_Format format, const TSSize *size, uint32_t layers, TS_ImageFlags flags);
TS_CAPI bool_t TS_CCALL tsImage_create2D_FuIF(TSImage self, TS_Format format, uint32_t size, TS_ImageFlags flags);
TS_CAPI bool_t TS_CCALL tsImage_create3D_FuIF(TSImage self, TS_Format format, uint32_t size, TS_ImageFlags flags);
TS_CAPI bool_t TS_CCALL tsImage_createCube_FuIF(TSImage self, TS_Format format, uint32_t size, TS_ImageFlags flags);
TS_CAPI bool_t TS_CCALL tsImage_create2D_FuuIF(TSImage self, TS_Format format, uint32_t width, uint32_t height, TS_ImageFlags flags);
TS_CAPI bool_t TS_CCALL tsImage_create3D_FuuuIF(TSImage self, TS_Format format, uint32_t width, uint32_t height, uint32_t depth, TS_ImageFlags flags);
TS_CAPI bool_t TS_CCALL tsImage_create2D_FuuuIF(TSImage self, TS_Format format, uint32_t width, uint32_t height, uint32_t layers, TS_ImageFlags flags);
TS_CAPI bool_t TS_CCALL tsImage_createCube_FuuIF(TSImage self, TS_Format format, uint32_t size, uint32_t layers, TS_ImageFlags flags);
TS_CAPI bool_t TS_CCALL tsImage_info_sIFuA(TSImage self, const char *name, TS_ImageFlags flags, uint32_t offset, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsImage_info_cSIFuA(TSImage self, const TSString name, TS_ImageFlags flags, uint32_t offset, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsImage_info_StIFuA(TSImage self, TSStream stream, TS_ImageFlags flags, uint32_t offset, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsImage_info_sA(TSImage self, const char *name, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsImage_info_cSA(TSImage self, const TSString name, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsImage_info_StA(TSImage self, TSStream stream, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsImage_load_sIFuA(TSImage self, const char *name, TS_ImageFlags flags, uint32_t offset, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsImage_load_cSIFuA(TSImage self, const TSString name, TS_ImageFlags flags, uint32_t offset, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsImage_load_StIFuA(TSImage self, TSStream stream, TS_ImageFlags flags, uint32_t offset, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsImage_load_sA(TSImage self, const char *name, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsImage_load_cSA(TSImage self, const TSString name, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsImage_load_StA(TSImage self, TSStream stream, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsImage_save_csIFu(TSImage self, const char *name, TS_ImageFlags flags, uint32_t quality);
TS_CAPI bool_t TS_CCALL tsImage_save_ccSIFu(TSImage self, const TSString name, TS_ImageFlags flags, uint32_t quality);
TS_CAPI bool_t TS_CCALL tsImage_save_cStIFu(TSImage self, TSStream stream, TS_ImageFlags flags, uint32_t quality);
TS_CAPI bool_t TS_CCALL tsImage_swap(TSImage self, uint32_t component_0, uint32_t component_1);
TS_CAPI bool_t TS_CCALL tsImage_copy_cIuu(TSImage self, const TSImage src, uint32_t dest_component, uint32_t src_component);
TS_CAPI bool_t TS_CCALL tsImage_flipX_cRcS(TSImage self, const TSRegion *region, const TSSlice *slice);
TS_CAPI bool_t TS_CCALL tsImage_flipX_cR(TSImage self, const TSRegion *region);
TS_CAPI bool_t TS_CCALL tsImage_flipX(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_flipY_cRcS(TSImage self, const TSRegion *region, const TSSlice *slice);
TS_CAPI bool_t TS_CCALL tsImage_flipY_cR(TSImage self, const TSRegion *region);
TS_CAPI bool_t TS_CCALL tsImage_flipY(TSImage self);
TS_CAPI bool_t TS_CCALL tsImage_copy_cIcOcRcScS(TSImage self, const TSImage src, const TSOrigin *dest_origin, const TSRegion *src_region, const TSSlice *dest_slice, const TSSlice *src_slice);
TS_CAPI bool_t TS_CCALL tsImage_copy_cIcOcR(TSImage self, const TSImage src, const TSOrigin *dest_origin, const TSRegion *src_region);
TS_CAPI bool_t TS_CCALL tsImage_copy_cIcOcS(TSImage self, const TSImage src, const TSOrigin *dest_origin, const TSSlice *dest_slice);
TS_CAPI bool_t TS_CCALL tsImage_copy_cIcScS(TSImage self, const TSImage src, const TSSlice *dest_slice, const TSSlice *src_slice);
TS_CAPI bool_t TS_CCALL tsImage_copy_cIcO(TSImage self, const TSImage src, const TSOrigin *dest_origin);
TS_CAPI bool_t TS_CCALL tsImage_copy_cIcS(TSImage self, const TSImage src, const TSSlice *dest_slice);
TS_CAPI TSImage TS_CCALL tsImage_toType_cITIFA(TSImage self, TS_ImageType type, TS_ImageFlags flags, TSAsync *async);
TS_CAPI TSImage TS_CCALL tsImage_toType_cITA(TSImage self, TS_ImageType type, TSAsync *async);
TS_CAPI TSImage TS_CCALL tsImage_toFormat_cFIFA(TSImage self, TS_Format format, TS_ImageFlags flags, TSAsync *async);
TS_CAPI TSImage TS_CCALL tsImage_toFormat_cFA(TSImage self, TS_Format format, TSAsync *async);
TS_CAPI TSImage TS_CCALL tsImage_getSlice_ccS(TSImage self, const TSSlice *slice);
TS_CAPI TSImage TS_CCALL tsImage_getComponent(TSImage self, uint32_t component);
TS_CAPI TSImage TS_CCALL tsImage_getRegion_ccRcS(TSImage self, const TSRegion *region, const TSSlice *slice);
TS_CAPI TSImage TS_CCALL tsImage_getRegion_ccR(TSImage self, const TSRegion *region);
TS_CAPI TSImage TS_CCALL tsImage_getRotated_cicS(TSImage self, int32_t angle, const TSSlice *slice);
TS_CAPI TSImage TS_CCALL tsImage_getRotated_ci(TSImage self, int32_t angle);
TS_CAPI TSImage TS_CCALL tsImage_getResized_ccSIFIFIFA(TSImage self, const TSSize *size, TS_ImageFilter min, TS_ImageFilter mag, TS_ImageFlags flags, TSAsync *async);
TS_CAPI TSImage TS_CCALL tsImage_getResized_ccSIFIFA(TSImage self, const TSSize *size, TS_ImageFilter min, TS_ImageFilter mag, TSAsync *async);
TS_CAPI TSImage TS_CCALL tsImage_getResized_ccSA(TSImage self, const TSSize *size, TSAsync *async);
TS_CAPI TSImage TS_CCALL tsImage_getMipmapped_cIFIFA(TSImage self, TS_ImageFilter filter, TS_ImageFlags flags, TSAsync *async);
TS_CAPI TSImage TS_CCALL tsImage_getMipmapped_cIFA(TSImage self, TS_ImageFilter filter, TSAsync *async);
TS_CAPI TSImage TS_CCALL tsImage_getMipmapped_cA(TSImage self, TSAsync *async);
TS_CAPI int32_t TS_CCALL tsImage_compare(TSImage self, const TSImage image);
TS_CAPI const uint8_t* TS_CCALL tsImage_getData_ccS(TSImage self, const TSSlice *slice);
TS_CAPI uint8_t* TS_CCALL tsImage_getData_cS(TSImage self, const TSSlice *slice);
TS_CAPI const uint8_t* TS_CCALL tsImage_getData_ccOcS(TSImage self, const TSOrigin *origin, const TSSlice *slice);
TS_CAPI uint8_t* TS_CCALL tsImage_getData_cOcS(TSImage self, const TSOrigin *origin, const TSSlice *slice);
TS_CAPI bool_t TS_CCALL tsImage_setData(TSImage self, const void *src, const TSSlice *slice, uint32_t alignment, size_t stride);
TS_CAPI bool_t TS_CCALL tsImage_getData_cprcSuz(TSImage self, void *dest, const TSSlice *slice, uint32_t alignment, size_t stride);
TS_CAPI size_t TS_CCALL tsImage_getMemory(TSImage self);

/// Tellusim::ImageSampler
TS_CAPI TSImageSampler TS_CCALL tsImageSampler_new(void);
TS_CAPI TSImageSampler TS_CCALL tsImageSampler_new_IcS(TSImage image, const TSSlice *slice);
TS_CAPI TSImageSampler TS_CCALL tsImageSampler_new_cIcS(const TSImage image, const TSSlice *slice);
TS_CAPI void TS_CCALL tsImageSampler_delete(TSImageSampler self);
TS_CAPI void TS_CCALL tsImageSampler_clear(TSImageSampler self);
TS_CAPI bool_t TS_CCALL tsImageSampler_isCreated(TSImageSampler self);
TS_CAPI TS_ImageType TS_CCALL tsImageSampler_getType(TSImageSampler self);
TS_CAPI bool_t TS_CCALL tsImageSampler_is2DType(TSImageSampler self);
TS_CAPI bool_t TS_CCALL tsImageSampler_is3DType(TSImageSampler self);
TS_CAPI bool_t TS_CCALL tsImageSampler_isCubeType(TSImageSampler self);
TS_CAPI TS_Format TS_CCALL tsImageSampler_getFormat(TSImageSampler self);
TS_CAPI const char* TS_CCALL tsImageSampler_getFormatName(TSImageSampler self);
TS_CAPI uint32_t TS_CCALL tsImageSampler_getWidth(TSImageSampler self);
TS_CAPI uint32_t TS_CCALL tsImageSampler_getHeight(TSImageSampler self);
TS_CAPI uint32_t TS_CCALL tsImageSampler_getDepth(TSImageSampler self);
TS_CAPI uint32_t TS_CCALL tsImageSampler_getFaces(TSImageSampler self);
TS_CAPI size_t TS_CCALL tsImageSampler_getTexels(TSImageSampler self);
TS_CAPI TSSize TS_CCALL tsImageSampler_getSize(TSImageSampler self);
TS_CAPI TSRegion TS_CCALL tsImageSampler_getRegion(TSImageSampler self);
TS_CAPI size_t TS_CCALL tsImageSampler_getStride(TSImageSampler self);
TS_CAPI size_t TS_CCALL tsImageSampler_getLayerSize(TSImageSampler self);
TS_CAPI uint32_t TS_CCALL tsImageSampler_getPixelSize(TSImageSampler self);
TS_CAPI uint32_t TS_CCALL tsImageSampler_getComponents(TSImageSampler self);
TS_CAPI const uint8_t* TS_CCALL tsImageSampler_getData_c(TSImageSampler self);
TS_CAPI uint8_t* TS_CCALL tsImageSampler_getData(TSImageSampler self);
TS_CAPI bool_t TS_CCALL tsImageSampler_create_IcS(TSImageSampler self, TSImage image, const TSSlice *slice);
TS_CAPI bool_t TS_CCALL tsImageSampler_create_cIcS(TSImageSampler self, const TSImage image, const TSSlice *slice);
TS_CAPI bool_t TS_CCALL tsImageSampler_create_ITFcSzpr(TSImageSampler self, TS_ImageType type, TS_Format format, const TSSize *size, size_t stride, void *data);
TS_CAPI bool_t TS_CCALL tsImageSampler_create_ITFcSzp(TSImageSampler self, TS_ImageType type, TS_Format format, const TSSize *size, size_t stride, const void *data);
TS_CAPI bool_t TS_CCALL tsImageSampler_create_ITFcSzzpr(TSImageSampler self, TS_ImageType type, TS_Format format, const TSSize *size, size_t stride, size_t layer_size, void *data);
TS_CAPI bool_t TS_CCALL tsImageSampler_create_ITFcSzzp(TSImageSampler self, TS_ImageType type, TS_Format format, const TSSize *size, size_t stride, size_t layer_size, const void *data);
TS_CAPI bool_t TS_CCALL tsImageSampler_clear_cC(TSImageSampler self, const TSColor *color);
TS_CAPI bool_t TS_CCALL tsImageSampler_clear_cIC(TSImageSampler self, const TSImageColor *color);
TS_CAPI bool_t TS_CCALL tsImageSampler_mad(TSImageSampler self, const TSColor *m, const TSColor *a);
TS_CAPI void TS_CCALL tsImageSampler_set2D(TSImageSampler self, uint32_t x, uint32_t y, const TSImageColor *color);
TS_CAPI TSImageColor TS_CCALL tsImageSampler_get2D_cuub(TSImageSampler self, uint32_t x, uint32_t y, bool_t repeat);
TS_CAPI TSImageColor TS_CCALL tsImageSampler_get2D_cf64f64bIF(TSImageSampler self, float64_t x, float64_t y, bool_t repeat, TS_ImageFilter filter);
TS_CAPI void TS_CCALL tsImageSampler_set3D(TSImageSampler self, uint32_t x, uint32_t y, uint32_t z, const TSImageColor *color);
TS_CAPI TSImageColor TS_CCALL tsImageSampler_get3D_cuuub(TSImageSampler self, uint32_t x, uint32_t y, uint32_t z, bool_t repeat);
TS_CAPI TSImageColor TS_CCALL tsImageSampler_get3D_cfffbIF(TSImageSampler self, float32_t x, float32_t y, float32_t z, bool_t repeat, TS_ImageFilter filter);
TS_CAPI void TS_CCALL tsImageSampler_setCube(TSImageSampler self, float32_t x, float32_t y, float32_t z, const TSImageColor *color);
TS_CAPI TSImageColor TS_CCALL tsImageSampler_getCube(TSImageSampler self, float32_t x, float32_t y, float32_t z, TS_ImageFilter filter);
TS_CAPI uint32_t TS_CCALL tsImageSampler_getCubeFace(TSImageSampler self, float32_t x, float32_t y, float32_t z, float32_t *tx, float32_t *ty);
TS_CAPI void TS_CCALL tsImageSampler_setTexel(TSImageSampler self, size_t t, const TSImageColor *color);
TS_CAPI TSImageColor TS_CCALL tsImageSampler_getTexel(TSImageSampler self, size_t t);

/// Tellusim::MeshNode
TS_CAPI TSMeshNode TS_CCALL tsMeshNode_new_s(const char *name);
TS_CAPI TSMeshNode TS_CCALL tsMeshNode_new_Ms(TSMesh mesh, const char *name);
TS_CAPI TSMeshNode TS_CCALL tsMeshNode_new_MNs(TSMeshNode *parent, const char *name);
TS_CAPI TSMeshNode TS_CCALL tsMeshNode_new_MMNs(TSMesh mesh, TSMeshNode *parent, const char *name);
TS_CAPI void TS_CCALL tsMeshNode_delete(TSMeshNode self);
TS_CAPI bool_t TS_CCALL tsMeshNode_equalPtr(const TSMeshNode self, const TSMeshNode ptr);
TS_CAPI TSMeshNode TS_CCALL tsMeshNode_copyPtr(const TSMeshNode self);
TS_CAPI TSMeshNode TS_CCALL tsMeshNode_clonePtr(const TSMeshNode self);
TS_CAPI void TS_CCALL tsMeshNode_clearPtr(TSMeshNode self);
TS_CAPI void TS_CCALL tsMeshNode_destroyPtr(TSMeshNode self);
TS_CAPI void TS_CCALL tsMeshNode_acquirePtr(TSMeshNode self);
TS_CAPI void TS_CCALL tsMeshNode_unacquirePtr(TSMeshNode self);
TS_CAPI bool_t TS_CCALL tsMeshNode_isValidPtr(const TSMeshNode self);
TS_CAPI bool_t TS_CCALL tsMeshNode_isOwnerPtr(const TSMeshNode self);
TS_CAPI bool_t TS_CCALL tsMeshNode_isConstPtr(const TSMeshNode self);
TS_CAPI uint32_t TS_CCALL tsMeshNode_getCountPtr(const TSMeshNode self);
TS_CAPI const void* TS_CCALL tsMeshNode_getInternalPtr(const TSMeshNode self);
TS_CAPI void TS_CCALL tsMeshNode_clear(TSMeshNode self);
TS_CAPI TSMeshNode TS_CCALL tsMeshNode_clone(TSMeshNode self, TSMesh mesh);
TS_CAPI void TS_CCALL tsMeshNode_setName(TSMeshNode self, const char *name);
TS_CAPI TSString TS_CCALL tsMeshNode_getName(TSMeshNode self);
TS_CAPI uint32_t TS_CCALL tsMeshNode_getIndex(TSMeshNode self);
TS_CAPI void TS_CCALL tsMeshNode_setMesh(TSMeshNode self, TSMesh mesh, bool_t check);
TS_CAPI TSMesh TS_CCALL tsMeshNode_getMesh_c(TSMeshNode self);
TS_CAPI TSMesh TS_CCALL tsMeshNode_getMesh(TSMeshNode self);
TS_CAPI uint32_t TS_CCALL tsMeshNode_setParent(TSMeshNode self, TSMeshNode parent, bool_t check);
TS_CAPI TSMeshNode TS_CCALL tsMeshNode_getParent_c(TSMeshNode self);
TS_CAPI TSMeshNode TS_CCALL tsMeshNode_getParent(TSMeshNode self);
TS_CAPI bool_t TS_CCALL tsMeshNode_isRoot(TSMeshNode self);
TS_CAPI void TS_CCALL tsMeshNode_reserveChildren(TSMeshNode self, uint32_t num_children);
TS_CAPI uint32_t TS_CCALL tsMeshNode_addChild(TSMeshNode self, TSMeshNode child, bool_t check);
TS_CAPI bool_t TS_CCALL tsMeshNode_removeChild(TSMeshNode self, TSMeshNode child);
TS_CAPI void TS_CCALL tsMeshNode_releaseChildren(TSMeshNode self);
TS_CAPI uint32_t TS_CCALL tsMeshNode_findChild_ccMN(TSMeshNode self, const TSMeshNode child);
TS_CAPI uint32_t TS_CCALL tsMeshNode_findChild_cs(TSMeshNode self, const char *name);
TS_CAPI uint32_t TS_CCALL tsMeshNode_getNumChildren(TSMeshNode self);
TS_CAPI TSMeshNode TS_CCALL tsMeshNode_getChild_cu(TSMeshNode self, uint32_t index);
TS_CAPI TSMeshNode TS_CCALL tsMeshNode_getChild_cs(TSMeshNode self, const char *name);
TS_CAPI TSMeshNode TS_CCALL tsMeshNode_getChild_u(TSMeshNode self, uint32_t index);
TS_CAPI TSMeshNode TS_CCALL tsMeshNode_getChild_s(TSMeshNode self, const char *name);
TS_CAPI void TS_CCALL tsMeshNode_clearGeometries(TSMeshNode self);
TS_CAPI void TS_CCALL tsMeshNode_reserveGeometries(TSMeshNode self, uint32_t num_geometries);
TS_CAPI uint32_t TS_CCALL tsMeshNode_addGeometry(TSMeshNode self, TSMeshGeometry geometry, bool_t check);
TS_CAPI bool_t TS_CCALL tsMeshNode_removeGeometry(TSMeshNode self, TSMeshGeometry geometry);
TS_CAPI bool_t TS_CCALL tsMeshNode_replaceGeometry(TSMeshNode self, TSMeshGeometry old_geometry, TSMeshGeometry geometry);
TS_CAPI uint32_t TS_CCALL tsMeshNode_findGeometry(TSMeshNode self, const TSMeshGeometry geometry);
TS_CAPI uint32_t TS_CCALL tsMeshNode_getNumGeometries(TSMeshNode self);
TS_CAPI TSMeshGeometry TS_CCALL tsMeshNode_getGeometry_cu(TSMeshNode self, uint32_t index);
TS_CAPI TSMeshGeometry TS_CCALL tsMeshNode_getGeometry_u(TSMeshNode self, uint32_t index);
TS_CAPI void TS_CCALL tsMeshNode_clearAttachments(TSMeshNode self);
TS_CAPI void TS_CCALL tsMeshNode_reserveAttachments(TSMeshNode self, uint32_t num_attachments);
TS_CAPI uint32_t TS_CCALL tsMeshNode_addAttachment(TSMeshNode self, TSMeshAttachment attachment, bool_t check);
TS_CAPI bool_t TS_CCALL tsMeshNode_removeAttachment(TSMeshNode self, TSMeshAttachment attachment);
TS_CAPI bool_t TS_CCALL tsMeshNode_replaceAttachment(TSMeshNode self, TSMeshAttachment old_attachment, TSMeshAttachment attachment);
TS_CAPI uint32_t TS_CCALL tsMeshNode_findAttachment_ccMA(TSMeshNode self, const TSMeshAttachment attachment);
TS_CAPI uint32_t TS_CCALL tsMeshNode_findAttachment_cs(TSMeshNode self, const char *name);
TS_CAPI uint32_t TS_CCALL tsMeshNode_getNumAttachments(TSMeshNode self);
TS_CAPI TSMeshAttachment TS_CCALL tsMeshNode_getAttachment_cu(TSMeshNode self, uint32_t index);
TS_CAPI TSMeshAttachment TS_CCALL tsMeshNode_getAttachment_u(TSMeshNode self, uint32_t index);
TS_CAPI void TS_CCALL tsMeshNode_setLocalTransform(TSMeshNode self, const TSMatrix4x3d *transform);
TS_CAPI TSMatrix4x3d TS_CCALL tsMeshNode_getLocalTransform(TSMeshNode self);
TS_CAPI void TS_CCALL tsMeshNode_setGlobalTransform(TSMeshNode self, const TSMatrix4x3d *transform);
TS_CAPI TSMatrix4x3d TS_CCALL tsMeshNode_getGlobalTransform(TSMeshNode self);
TS_CAPI void TS_CCALL tsMeshNode_setPivotTransform(TSMeshNode self, const TSMatrix4x3d *transform);
TS_CAPI TSMatrix4x3d TS_CCALL tsMeshNode_getPivotTransform(TSMeshNode self);
TS_CAPI void TS_CCALL tsMeshNode_setMorphTransform(TSMeshNode self, const TSVector4f *transform);
TS_CAPI TSVector4f TS_CCALL tsMeshNode_getMorphTransform(TSMeshNode self);
TS_CAPI void TS_CCALL tsMeshNode_createLocalTransforms(TSMeshNode self, const TSMatrix4x3d *itransform);
TS_CAPI void TS_CCALL tsMeshNode_createGlobalTransforms(TSMeshNode self, const TSMatrix4x3d *transform);
TS_CAPI void TS_CCALL tsMeshNode_setTransform(TSMeshNode self, const TSVector3d *scale);
TS_CAPI size_t TS_CCALL tsMeshNode_getMemory(TSMeshNode self);

/// Tellusim::MeshIndices
TS_CAPI TSMeshIndices TS_CCALL tsMeshIndices_new_s(const char *name);
TS_CAPI TSMeshIndices TS_CCALL tsMeshIndices_new_MITFs(TS_MeshIndicesType type, TS_Format format, const char *name);
TS_CAPI TSMeshIndices TS_CCALL tsMeshIndices_new_MITFus(TS_MeshIndicesType type, TS_Format format, uint32_t size, const char *name);
TS_CAPI void TS_CCALL tsMeshIndices_delete(TSMeshIndices self);
TS_CAPI bool_t TS_CCALL tsMeshIndices_equalPtr(const TSMeshIndices self, const TSMeshIndices ptr);
TS_CAPI TSMeshIndices TS_CCALL tsMeshIndices_copyPtr(const TSMeshIndices self);
TS_CAPI TSMeshIndices TS_CCALL tsMeshIndices_clonePtr(const TSMeshIndices self);
TS_CAPI void TS_CCALL tsMeshIndices_clearPtr(TSMeshIndices self);
TS_CAPI void TS_CCALL tsMeshIndices_destroyPtr(TSMeshIndices self);
TS_CAPI void TS_CCALL tsMeshIndices_acquirePtr(TSMeshIndices self);
TS_CAPI void TS_CCALL tsMeshIndices_unacquirePtr(TSMeshIndices self);
TS_CAPI bool_t TS_CCALL tsMeshIndices_isValidPtr(const TSMeshIndices self);
TS_CAPI bool_t TS_CCALL tsMeshIndices_isOwnerPtr(const TSMeshIndices self);
TS_CAPI bool_t TS_CCALL tsMeshIndices_isConstPtr(const TSMeshIndices self);
TS_CAPI uint32_t TS_CCALL tsMeshIndices_getCountPtr(const TSMeshIndices self);
TS_CAPI const void* TS_CCALL tsMeshIndices_getInternalPtr(const TSMeshIndices self);
TS_CAPI void TS_CCALL tsMeshIndices_clear(TSMeshIndices self);
TS_CAPI void TS_CCALL tsMeshIndices_setName(TSMeshIndices self, const char *name);
TS_CAPI TSString TS_CCALL tsMeshIndices_getName(TSMeshIndices self);
TS_CAPI void TS_CCALL tsMeshIndices_create(TSMeshIndices self, TS_MeshIndicesType type, TS_Format format, uint32_t size);
TS_CAPI TS_MeshIndicesType TS_CCALL tsMeshIndices_getType(TSMeshIndices self);
TS_CAPI const char* TS_CCALL tsMeshIndices_getTypeName_MIT(TS_MeshIndicesType type);
TS_CAPI const char* TS_CCALL tsMeshIndices_getTypeName_c(TSMeshIndices self);
TS_CAPI bool_t TS_CCALL tsMeshIndices_isUnknown(TSMeshIndices self);
TS_CAPI bool_t TS_CCALL tsMeshIndices_isPoint(TSMeshIndices self);
TS_CAPI bool_t TS_CCALL tsMeshIndices_isLine(TSMeshIndices self);
TS_CAPI bool_t TS_CCALL tsMeshIndices_isTriangle(TSMeshIndices self);
TS_CAPI bool_t TS_CCALL tsMeshIndices_isQuadrilateral(TSMeshIndices self);
TS_CAPI bool_t TS_CCALL tsMeshIndices_isTetrahedron(TSMeshIndices self);
TS_CAPI bool_t TS_CCALL tsMeshIndices_isPrimitive(TSMeshIndices self);
TS_CAPI bool_t TS_CCALL tsMeshIndices_isSolid(TSMeshIndices self);
TS_CAPI bool_t TS_CCALL tsMeshIndices_isVolume(TSMeshIndices self);
TS_CAPI bool_t TS_CCALL tsMeshIndices_isMaterial(TSMeshIndices self);
TS_CAPI bool_t TS_CCALL tsMeshIndices_isGroup(TSMeshIndices self);
TS_CAPI bool_t TS_CCALL tsMeshIndices_isJoint(TSMeshIndices self);
TS_CAPI bool_t TS_CCALL tsMeshIndices_isEdge(TSMeshIndices self);
TS_CAPI uint32_t TS_CCALL tsMeshIndices_getPrimitiveSize(TSMeshIndices self);
TS_CAPI TS_Format TS_CCALL tsMeshIndices_getFormat(TSMeshIndices self);
TS_CAPI const char* TS_CCALL tsMeshIndices_getFormatName(TSMeshIndices self);
TS_CAPI void TS_CCALL tsMeshIndices_setGeometry(TSMeshIndices self, TSMeshGeometry geometry, bool_t check);
TS_CAPI TSMeshGeometry TS_CCALL tsMeshIndices_getGeometry_c(TSMeshIndices self);
TS_CAPI TSMeshGeometry TS_CCALL tsMeshIndices_getGeometry(TSMeshIndices self);
TS_CAPI void TS_CCALL tsMeshIndices_setSize(TSMeshIndices self, uint32_t size, bool_t discard, bool_t clear);
TS_CAPI uint32_t TS_CCALL tsMeshIndices_getSize(TSMeshIndices self);
TS_CAPI uint32_t TS_CCALL tsMeshIndices_getStride(TSMeshIndices self);
TS_CAPI size_t TS_CCALL tsMeshIndices_getBytes(TSMeshIndices self);
TS_CAPI void TS_CCALL tsMeshIndices_setData_uuu(TSMeshIndices self, uint32_t value, uint32_t size, uint32_t offset);
TS_CAPI void TS_CCALL tsMeshIndices_setData_pFuu(TSMeshIndices self, const void *src, TS_Format format, uint32_t size, uint32_t repeat);
TS_CAPI void TS_CCALL tsMeshIndices_getData_cprFuu(TSMeshIndices self, void *dest, TS_Format format, uint32_t size, uint32_t repeat);
TS_CAPI const void* TS_CCALL tsMeshIndices_getData_c(TSMeshIndices self);
TS_CAPI void* TS_CCALL tsMeshIndices_getData(TSMeshIndices self);
TS_CAPI void TS_CCALL tsMeshIndices_set_uu(TSMeshIndices self, uint32_t index, uint32_t value);
TS_CAPI void TS_CCALL tsMeshIndices_set_uuu(TSMeshIndices self, uint32_t index, uint32_t value_0, uint32_t value_1);
TS_CAPI void TS_CCALL tsMeshIndices_set_uuuu(TSMeshIndices self, uint32_t index, uint32_t value_0, uint32_t value_1, uint32_t value_2);
TS_CAPI void TS_CCALL tsMeshIndices_set_uuuuu(TSMeshIndices self, uint32_t index, uint32_t value_0, uint32_t value_1, uint32_t value_2, uint32_t value_3);
TS_CAPI uint32_t TS_CCALL tsMeshIndices_get_cu(TSMeshIndices self, uint32_t index);
TS_CAPI void TS_CCALL tsMeshIndices_get_cuurur(TSMeshIndices self, uint32_t index, uint32_t *value_0, uint32_t *value_1);
TS_CAPI void TS_CCALL tsMeshIndices_get_cuururur(TSMeshIndices self, uint32_t index, uint32_t *value_0, uint32_t *value_1, uint32_t *value_2);
TS_CAPI void TS_CCALL tsMeshIndices_get_cuurururur(TSMeshIndices self, uint32_t index, uint32_t *value_0, uint32_t *value_1, uint32_t *value_2, uint32_t *value_3);
TS_CAPI const void* TS_CCALL tsMeshIndices_getPtr_cu(TSMeshIndices self, uint32_t index);
TS_CAPI void* TS_CCALL tsMeshIndices_getPtr_u(TSMeshIndices self, uint32_t index);
TS_CAPI bool_t TS_CCALL tsMeshIndices_isDirect(TSMeshIndices self);
TS_CAPI bool_t TS_CCALL tsMeshIndices_isUniform(TSMeshIndices self);
TS_CAPI uint32_t TS_CCALL tsMeshIndices_getMinIndex(TSMeshIndices self);
TS_CAPI uint32_t TS_CCALL tsMeshIndices_getMaxIndex(TSMeshIndices self);
TS_CAPI int32_t TS_CCALL tsMeshIndices_compare(TSMeshIndices self, const TSMeshIndices indices);
TS_CAPI void TS_CCALL tsMeshIndices_addIndices(TSMeshIndices self, const TSMeshIndices indices, uint32_t offset, bool_t expand);
TS_CAPI TSMeshIndices TS_CCALL tsMeshIndices_toFormat(TSMeshIndices self, TS_Format format);
TS_CAPI TSMeshIndices TS_CCALL tsMeshIndices_toType_cMIT(TSMeshIndices self, TS_MeshIndicesType type);
TS_CAPI TSMeshIndices TS_CCALL tsMeshIndices_toType_cMITcMA(TSMeshIndices self, TS_MeshIndicesType type, const TSMeshAttribute position_attribute);
TS_CAPI size_t TS_CCALL tsMeshIndices_getMemory(TSMeshIndices self);

/// Tellusim::MeshAttribute
TS_CAPI TSMeshAttribute TS_CCALL tsMeshAttribute_new_su(const char *name, uint32_t index);
TS_CAPI TSMeshAttribute TS_CCALL tsMeshAttribute_new_MATFsu(TS_MeshAttributeType type, TS_Format format, const char *name, uint32_t index);
TS_CAPI TSMeshAttribute TS_CCALL tsMeshAttribute_new_MATFusu(TS_MeshAttributeType type, TS_Format format, uint32_t size, const char *name, uint32_t index);
TS_CAPI TSMeshAttribute TS_CCALL tsMeshAttribute_new_MATFuu(TS_MeshAttributeType type, TS_Format format, uint32_t size, uint32_t index);
TS_CAPI void TS_CCALL tsMeshAttribute_delete(TSMeshAttribute self);
TS_CAPI bool_t TS_CCALL tsMeshAttribute_equalPtr(const TSMeshAttribute self, const TSMeshAttribute ptr);
TS_CAPI TSMeshAttribute TS_CCALL tsMeshAttribute_copyPtr(const TSMeshAttribute self);
TS_CAPI TSMeshAttribute TS_CCALL tsMeshAttribute_clonePtr(const TSMeshAttribute self);
TS_CAPI void TS_CCALL tsMeshAttribute_clearPtr(TSMeshAttribute self);
TS_CAPI void TS_CCALL tsMeshAttribute_destroyPtr(TSMeshAttribute self);
TS_CAPI void TS_CCALL tsMeshAttribute_acquirePtr(TSMeshAttribute self);
TS_CAPI void TS_CCALL tsMeshAttribute_unacquirePtr(TSMeshAttribute self);
TS_CAPI bool_t TS_CCALL tsMeshAttribute_isValidPtr(const TSMeshAttribute self);
TS_CAPI bool_t TS_CCALL tsMeshAttribute_isOwnerPtr(const TSMeshAttribute self);
TS_CAPI bool_t TS_CCALL tsMeshAttribute_isConstPtr(const TSMeshAttribute self);
TS_CAPI uint32_t TS_CCALL tsMeshAttribute_getCountPtr(const TSMeshAttribute self);
TS_CAPI const void* TS_CCALL tsMeshAttribute_getInternalPtr(const TSMeshAttribute self);
TS_CAPI void TS_CCALL tsMeshAttribute_clear(TSMeshAttribute self);
TS_CAPI void TS_CCALL tsMeshAttribute_setName(TSMeshAttribute self, const char *name);
TS_CAPI TSString TS_CCALL tsMeshAttribute_getName(TSMeshAttribute self);
TS_CAPI void TS_CCALL tsMeshAttribute_create(TSMeshAttribute self, TS_MeshAttributeType type, TS_Format format, uint32_t size);
TS_CAPI TS_MeshAttributeType TS_CCALL tsMeshAttribute_getType(TSMeshAttribute self);
TS_CAPI const char* TS_CCALL tsMeshAttribute_getTypeName_MAT(TS_MeshAttributeType type);
TS_CAPI const char* TS_CCALL tsMeshAttribute_getTypeName_c(TSMeshAttribute self);
TS_CAPI bool_t TS_CCALL tsMeshAttribute_isUnknown(TSMeshAttribute self);
TS_CAPI bool_t TS_CCALL tsMeshAttribute_isPosition(TSMeshAttribute self);
TS_CAPI bool_t TS_CCALL tsMeshAttribute_isBasis(TSMeshAttribute self);
TS_CAPI bool_t TS_CCALL tsMeshAttribute_isNormal(TSMeshAttribute self);
TS_CAPI bool_t TS_CCALL tsMeshAttribute_isTangent(TSMeshAttribute self);
TS_CAPI bool_t TS_CCALL tsMeshAttribute_isBinormal(TSMeshAttribute self);
TS_CAPI bool_t TS_CCALL tsMeshAttribute_isSpatial(TSMeshAttribute self);
TS_CAPI bool_t TS_CCALL tsMeshAttribute_isNormalized(TSMeshAttribute self);
TS_CAPI bool_t TS_CCALL tsMeshAttribute_isTexCoord(TSMeshAttribute self);
TS_CAPI bool_t TS_CCALL tsMeshAttribute_isWeights(TSMeshAttribute self);
TS_CAPI bool_t TS_CCALL tsMeshAttribute_isJoints(TSMeshAttribute self);
TS_CAPI bool_t TS_CCALL tsMeshAttribute_isColor(TSMeshAttribute self);
TS_CAPI bool_t TS_CCALL tsMeshAttribute_isVertex(TSMeshAttribute self);
TS_CAPI bool_t TS_CCALL tsMeshAttribute_isCrease(TSMeshAttribute self);
TS_CAPI TS_Format TS_CCALL tsMeshAttribute_getFormat(TSMeshAttribute self);
TS_CAPI const char* TS_CCALL tsMeshAttribute_getFormatName(TSMeshAttribute self);
TS_CAPI uint32_t TS_CCALL tsMeshAttribute_getComponents(TSMeshAttribute self);
TS_CAPI bool_t TS_CCALL tsMeshAttribute_isPacked(TSMeshAttribute self);
TS_CAPI void TS_CCALL tsMeshAttribute_setIndex(TSMeshAttribute self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsMeshAttribute_getIndex(TSMeshAttribute self);
TS_CAPI void TS_CCALL tsMeshAttribute_setIndices(TSMeshAttribute self, TSMeshIndices indices);
TS_CAPI TSMeshIndices TS_CCALL tsMeshAttribute_getIndices_c(TSMeshAttribute self);
TS_CAPI TSMeshIndices TS_CCALL tsMeshAttribute_getIndices(TSMeshAttribute self);
TS_CAPI void TS_CCALL tsMeshAttribute_setGeometry(TSMeshAttribute self, TSMeshGeometry geometry, bool_t check);
TS_CAPI TSMeshGeometry TS_CCALL tsMeshAttribute_getGeometry_c(TSMeshAttribute self);
TS_CAPI TSMeshGeometry TS_CCALL tsMeshAttribute_getGeometry(TSMeshAttribute self);
TS_CAPI void TS_CCALL tsMeshAttribute_setSize(TSMeshAttribute self, uint32_t size, bool_t discard, bool_t clear);
TS_CAPI uint32_t TS_CCALL tsMeshAttribute_getSize(TSMeshAttribute self);
TS_CAPI uint32_t TS_CCALL tsMeshAttribute_getStride(TSMeshAttribute self);
TS_CAPI size_t TS_CCALL tsMeshAttribute_getBytes(TSMeshAttribute self);
TS_CAPI void TS_CCALL tsMeshAttribute_setData_puu(TSMeshAttribute self, const void *src, uint32_t size, uint32_t stride);
TS_CAPI void TS_CCALL tsMeshAttribute_setData_pcA32u(TSMeshAttribute self, const void *src, const uint32_t *indices, uint32_t indices_size, uint32_t stride);
TS_CAPI void TS_CCALL tsMeshAttribute_getData_cpruu(TSMeshAttribute self, void *dest, uint32_t size, uint32_t stride);
TS_CAPI void TS_CCALL tsMeshAttribute_getData_cprcMIu(TSMeshAttribute self, void *dest, const TSMeshIndices indices, uint32_t stride);
TS_CAPI void TS_CCALL tsMeshAttribute_getData_cprcA32u(TSMeshAttribute self, void *dest, const uint32_t *indices, uint32_t indices_size, uint32_t stride);
TS_CAPI const void* TS_CCALL tsMeshAttribute_getData_c(TSMeshAttribute self);
TS_CAPI void* TS_CCALL tsMeshAttribute_getData(TSMeshAttribute self);
TS_CAPI void TS_CCALL tsMeshAttribute_setValue(TSMeshAttribute self, uint32_t index, const void *src, size_t size);
TS_CAPI void TS_CCALL tsMeshAttribute_getValue(TSMeshAttribute self, uint32_t index, void *dest, size_t size);
TS_CAPI const void* TS_CCALL tsMeshAttribute_getPtr_cu(TSMeshAttribute self, uint32_t index);
TS_CAPI void* TS_CCALL tsMeshAttribute_getPtr_u(TSMeshAttribute self, uint32_t index);
TS_CAPI int32_t TS_CCALL tsMeshAttribute_compare(TSMeshAttribute self, const TSMeshAttribute attribute, const TSMatrix4x3f *transform, float32_t threshold, bool_t spatial);
TS_CAPI void TS_CCALL tsMeshAttribute_addAttribute(TSMeshAttribute self, const TSMeshAttribute attribute);
TS_CAPI bool_t TS_CCALL tsMeshAttribute_setTransform(TSMeshAttribute self, const TSMatrix4x3f *transform);
TS_CAPI bool_t TS_CCALL tsMeshAttribute_morphAttribute(TSMeshAttribute self, const TSMeshAttribute attribute, float32_t k);
TS_CAPI bool_t TS_CCALL tsMeshAttribute_packAttributes(TSMeshAttribute self, const TSMeshAttribute attribute_0, const TSMeshAttribute attribute_1, TS_Format format);
TS_CAPI bool_t TS_CCALL tsMeshAttribute_unpackAttributes(TSMeshAttribute self, TSMeshAttribute attribute_0, TSMeshAttribute attribute_1);
TS_CAPI TSMeshAttribute TS_CCALL tsMeshAttribute_optimizeAttribute(TSMeshAttribute self, TSMeshIndices indices);
TS_CAPI TSMeshAttribute TS_CCALL tsMeshAttribute_toDirect(TSMeshAttribute self, const TSMeshIndices indices);
TS_CAPI TSMeshAttribute TS_CCALL tsMeshAttribute_toFormat(TSMeshAttribute self, TS_Format format);
TS_CAPI TSMeshAttribute TS_CCALL tsMeshAttribute_toType(TSMeshAttribute self, TS_MeshAttributeType type);
TS_CAPI TSMatrix4x3f TS_CCALL tsMeshAttribute_getCovarianceMatrix(TSMeshAttribute self);
TS_CAPI TSMatrix4x3f TS_CCALL tsMeshAttribute_getMinTransform(TSMeshAttribute self);
TS_CAPI TSBoundBoxf TS_CCALL tsMeshAttribute_getBoundBox(TSMeshAttribute self);
TS_CAPI TSBoundSpheref TS_CCALL tsMeshAttribute_getBoundSphere(TSMeshAttribute self);
TS_CAPI size_t TS_CCALL tsMeshAttribute_getMemory(TSMeshAttribute self);

/// Tellusim::MeshJoint
TS_CAPI TSMeshJoint TS_CCALL tsMeshJoint_new_s(const char *name);
TS_CAPI TSMeshJoint TS_CCALL tsMeshJoint_new_MGs(TSMeshGeometry geometry, const char *name);
TS_CAPI void TS_CCALL tsMeshJoint_delete(TSMeshJoint self);
TS_CAPI bool_t TS_CCALL tsMeshJoint_equalPtr(const TSMeshJoint self, const TSMeshJoint ptr);
TS_CAPI TSMeshJoint TS_CCALL tsMeshJoint_copyPtr(const TSMeshJoint self);
TS_CAPI TSMeshJoint TS_CCALL tsMeshJoint_clonePtr(const TSMeshJoint self);
TS_CAPI void TS_CCALL tsMeshJoint_clearPtr(TSMeshJoint self);
TS_CAPI void TS_CCALL tsMeshJoint_destroyPtr(TSMeshJoint self);
TS_CAPI void TS_CCALL tsMeshJoint_acquirePtr(TSMeshJoint self);
TS_CAPI void TS_CCALL tsMeshJoint_unacquirePtr(TSMeshJoint self);
TS_CAPI bool_t TS_CCALL tsMeshJoint_isValidPtr(const TSMeshJoint self);
TS_CAPI bool_t TS_CCALL tsMeshJoint_isOwnerPtr(const TSMeshJoint self);
TS_CAPI bool_t TS_CCALL tsMeshJoint_isConstPtr(const TSMeshJoint self);
TS_CAPI uint32_t TS_CCALL tsMeshJoint_getCountPtr(const TSMeshJoint self);
TS_CAPI const void* TS_CCALL tsMeshJoint_getInternalPtr(const TSMeshJoint self);
TS_CAPI void TS_CCALL tsMeshJoint_clear(TSMeshJoint self);
TS_CAPI void TS_CCALL tsMeshJoint_setName(TSMeshJoint self, const char *name);
TS_CAPI TSString TS_CCALL tsMeshJoint_getName(TSMeshJoint self);
TS_CAPI void TS_CCALL tsMeshJoint_setNode(TSMeshJoint self, TSMeshNode node);
TS_CAPI TSMeshNode TS_CCALL tsMeshJoint_getNode_c(TSMeshJoint self);
TS_CAPI TSMeshNode TS_CCALL tsMeshJoint_getNode(TSMeshJoint self);
TS_CAPI uint32_t TS_CCALL tsMeshJoint_getNodeIndex(TSMeshJoint self);
TS_CAPI TSMatrix4x3d TS_CCALL tsMeshJoint_getLocalTransform(TSMeshJoint self);
TS_CAPI TSMatrix4x3d TS_CCALL tsMeshJoint_getGlobalTransform(TSMeshJoint self);
TS_CAPI void TS_CCALL tsMeshJoint_setIndices(TSMeshJoint self, TSMeshIndices indices);
TS_CAPI TSMeshIndices TS_CCALL tsMeshJoint_getIndices_c(TSMeshJoint self);
TS_CAPI TSMeshIndices TS_CCALL tsMeshJoint_getIndices(TSMeshJoint self);
TS_CAPI void TS_CCALL tsMeshJoint_setGeometry(TSMeshJoint self, TSMeshGeometry geometry, bool_t check);
TS_CAPI TSMeshGeometry TS_CCALL tsMeshJoint_getGeometry_c(TSMeshJoint self);
TS_CAPI TSMeshGeometry TS_CCALL tsMeshJoint_getGeometry(TSMeshJoint self);
TS_CAPI void TS_CCALL tsMeshJoint_setBoundBox(TSMeshJoint self, const TSBoundBoxf *box);
TS_CAPI TSBoundBoxf TS_CCALL tsMeshJoint_getBoundBox(TSMeshJoint self);
TS_CAPI void TS_CCALL tsMeshJoint_setBoundSphere(TSMeshJoint self, const TSBoundSpheref *sphere);
TS_CAPI TSBoundSpheref TS_CCALL tsMeshJoint_getBoundSphere(TSMeshJoint self);
TS_CAPI void TS_CCALL tsMeshJoint_setITransform(TSMeshJoint self, const TSMatrix4x3f *itransform);
TS_CAPI TSMatrix4x3f TS_CCALL tsMeshJoint_getITransform(TSMeshJoint self);
TS_CAPI int32_t TS_CCALL tsMeshJoint_compare(TSMeshJoint self, const TSMeshJoint joint);
TS_CAPI size_t TS_CCALL tsMeshJoint_getMemory(TSMeshJoint self);

/// Tellusim::MeshMaterial
TS_CAPI TSMeshMaterial TS_CCALL tsMeshMaterial_new_s(const char *name);
TS_CAPI TSMeshMaterial TS_CCALL tsMeshMaterial_new_MGs(TSMeshGeometry geometry, const char *name);
TS_CAPI void TS_CCALL tsMeshMaterial_delete(TSMeshMaterial self);
TS_CAPI bool_t TS_CCALL tsMeshMaterial_equalPtr(const TSMeshMaterial self, const TSMeshMaterial ptr);
TS_CAPI TSMeshMaterial TS_CCALL tsMeshMaterial_copyPtr(const TSMeshMaterial self);
TS_CAPI TSMeshMaterial TS_CCALL tsMeshMaterial_clonePtr(const TSMeshMaterial self);
TS_CAPI void TS_CCALL tsMeshMaterial_clearPtr(TSMeshMaterial self);
TS_CAPI void TS_CCALL tsMeshMaterial_destroyPtr(TSMeshMaterial self);
TS_CAPI void TS_CCALL tsMeshMaterial_acquirePtr(TSMeshMaterial self);
TS_CAPI void TS_CCALL tsMeshMaterial_unacquirePtr(TSMeshMaterial self);
TS_CAPI bool_t TS_CCALL tsMeshMaterial_isValidPtr(const TSMeshMaterial self);
TS_CAPI bool_t TS_CCALL tsMeshMaterial_isOwnerPtr(const TSMeshMaterial self);
TS_CAPI bool_t TS_CCALL tsMeshMaterial_isConstPtr(const TSMeshMaterial self);
TS_CAPI uint32_t TS_CCALL tsMeshMaterial_getCountPtr(const TSMeshMaterial self);
TS_CAPI const void* TS_CCALL tsMeshMaterial_getInternalPtr(const TSMeshMaterial self);
TS_CAPI void TS_CCALL tsMeshMaterial_clear(TSMeshMaterial self);
TS_CAPI void TS_CCALL tsMeshMaterial_setName(TSMeshMaterial self, const char *name);
TS_CAPI TSString TS_CCALL tsMeshMaterial_getName(TSMeshMaterial self);
TS_CAPI uint32_t TS_CCALL tsMeshMaterial_getIndex(TSMeshMaterial self);
TS_CAPI void TS_CCALL tsMeshMaterial_setIndices(TSMeshMaterial self, TSMeshIndices indices);
TS_CAPI TSMeshIndices TS_CCALL tsMeshMaterial_getIndices_c(TSMeshMaterial self);
TS_CAPI TSMeshIndices TS_CCALL tsMeshMaterial_getIndices(TSMeshMaterial self);
TS_CAPI void TS_CCALL tsMeshMaterial_setGeometry(TSMeshMaterial self, TSMeshGeometry geometry, bool_t check);
TS_CAPI TSMeshGeometry TS_CCALL tsMeshMaterial_getGeometry_c(TSMeshMaterial self);
TS_CAPI TSMeshGeometry TS_CCALL tsMeshMaterial_getGeometry(TSMeshMaterial self);
TS_CAPI void TS_CCALL tsMeshMaterial_setData_s(TSMeshMaterial self, const char *data);
TS_CAPI void TS_CCALL tsMeshMaterial_setData_cS(TSMeshMaterial self, const TSString data);
TS_CAPI TSString TS_CCALL tsMeshMaterial_getData(TSMeshMaterial self);
TS_CAPI void TS_CCALL tsMeshMaterial_clearParameters(TSMeshMaterial self);
TS_CAPI bool_t TS_CCALL tsMeshMaterial_removeParameter(TSMeshMaterial self, const char *type);
TS_CAPI void TS_CCALL tsMeshMaterial_copyParameters(TSMeshMaterial self, const TSMeshMaterial material);
TS_CAPI uint32_t TS_CCALL tsMeshMaterial_findParameter(TSMeshMaterial self, const char *type);
TS_CAPI bool_t TS_CCALL tsMeshMaterial_hasParameter(TSMeshMaterial self, const char *type);
TS_CAPI uint32_t TS_CCALL tsMeshMaterial_getNumParameters(TSMeshMaterial self);
TS_CAPI TSString TS_CCALL tsMeshMaterial_getParameterType(TSMeshMaterial self, uint32_t index);
TS_CAPI void TS_CCALL tsMeshMaterial_addParameter_sb(TSMeshMaterial self, const char *type, bool_t value);
TS_CAPI void TS_CCALL tsMeshMaterial_addParameter_sf(TSMeshMaterial self, const char *type, float32_t value);
TS_CAPI void TS_CCALL tsMeshMaterial_addParameter_scV4(TSMeshMaterial self, const char *type, const TSVector4f *value);
TS_CAPI void TS_CCALL tsMeshMaterial_addParameter_scM32(TSMeshMaterial self, const char *type, const TSMatrix3x2f *value);
TS_CAPI void TS_CCALL tsMeshMaterial_addParameter_scC(TSMeshMaterial self, const char *type, const TSColor *color);
TS_CAPI void TS_CCALL tsMeshMaterial_addParameter_sss(TSMeshMaterial self, const char *type, const char *name, const char *layout);
TS_CAPI void TS_CCALL tsMeshMaterial_addParameter_scSs(TSMeshMaterial self, const char *type, const TSString name, const char *layout);
TS_CAPI void TS_CCALL tsMeshMaterial_addParameter_scIs(TSMeshMaterial self, const char *type, const TSImage image, const char *layout);
TS_CAPI void TS_CCALL tsMeshMaterial_addParameter_sBs(TSMeshMaterial self, const char *type, TSBlob blob, const char *layout);
TS_CAPI TS_MeshMaterialFlags TS_CCALL tsMeshMaterial_getParameterFlags_cu(TSMeshMaterial self, uint32_t index);
TS_CAPI bool_t TS_CCALL tsMeshMaterial_hasParameterFlag_cuMMF(TSMeshMaterial self, uint32_t index, TS_MeshMaterialFlags flags);
TS_CAPI bool_t TS_CCALL tsMeshMaterial_hasParameterFlags_cuMMF(TSMeshMaterial self, uint32_t index, TS_MeshMaterialFlags flags);
TS_CAPI bool_t TS_CCALL tsMeshMaterial_getParameterBool_cub(TSMeshMaterial self, uint32_t index, bool_t value);
TS_CAPI float32_t TS_CCALL tsMeshMaterial_getParameterScalarf32_cuf(TSMeshMaterial self, uint32_t index, float32_t value);
TS_CAPI TSVector4f TS_CCALL tsMeshMaterial_getParameterVector4f_cucV4(TSMeshMaterial self, uint32_t index, const TSVector4f *vector);
TS_CAPI TSMatrix3x2f TS_CCALL tsMeshMaterial_getParameterMatrix3x2f_cucM32(TSMeshMaterial self, uint32_t index, const TSMatrix3x2f *matrix);
TS_CAPI TSColor TS_CCALL tsMeshMaterial_getParameterColor_cucC(TSMeshMaterial self, uint32_t index, const TSColor *color);
TS_CAPI TSString TS_CCALL tsMeshMaterial_getParameterName_cucS(TSMeshMaterial self, uint32_t index, const TSString name);
TS_CAPI TSString TS_CCALL tsMeshMaterial_getParameterLayout_cucS(TSMeshMaterial self, uint32_t index, const TSString layout);
TS_CAPI TSImage TS_CCALL tsMeshMaterial_getParameterImage_cu(TSMeshMaterial self, uint32_t index);
TS_CAPI TSBlob TS_CCALL tsMeshMaterial_getParameterBlob_cu(TSMeshMaterial self, uint32_t index);
TS_CAPI TSImage TS_CCALL tsMeshMaterial_getParameterImage_u(TSMeshMaterial self, uint32_t index);
TS_CAPI TSBlob TS_CCALL tsMeshMaterial_getParameterBlob_u(TSMeshMaterial self, uint32_t index);
TS_CAPI TS_MeshMaterialFlags TS_CCALL tsMeshMaterial_getParameterFlags_cs(TSMeshMaterial self, const char *type);
TS_CAPI bool_t TS_CCALL tsMeshMaterial_hasParameterFlag_csMMF(TSMeshMaterial self, const char *type, TS_MeshMaterialFlags flags);
TS_CAPI bool_t TS_CCALL tsMeshMaterial_hasParameterFlags_csMMF(TSMeshMaterial self, const char *type, TS_MeshMaterialFlags flags);
TS_CAPI bool_t TS_CCALL tsMeshMaterial_getParameterBool_csb(TSMeshMaterial self, const char *type, bool_t value);
TS_CAPI float32_t TS_CCALL tsMeshMaterial_getParameterScalarf32_csf(TSMeshMaterial self, const char *type, float32_t value);
TS_CAPI TSVector4f TS_CCALL tsMeshMaterial_getParameterVector4f_cscV4(TSMeshMaterial self, const char *type, const TSVector4f *vector);
TS_CAPI TSMatrix3x2f TS_CCALL tsMeshMaterial_getParameterMatrix3x2f_cscM32(TSMeshMaterial self, const char *type, const TSMatrix3x2f *matrix);
TS_CAPI TSColor TS_CCALL tsMeshMaterial_getParameterColor_cscC(TSMeshMaterial self, const char *type, const TSColor *color);
TS_CAPI TSString TS_CCALL tsMeshMaterial_getParameterName_cscS(TSMeshMaterial self, const char *type, const TSString name);
TS_CAPI TSString TS_CCALL tsMeshMaterial_getParameterLayout_cscS(TSMeshMaterial self, const char *type, const TSString layout);
TS_CAPI int32_t TS_CCALL tsMeshMaterial_compare(TSMeshMaterial self, const TSMeshMaterial material);
TS_CAPI size_t TS_CCALL tsMeshMaterial_getMemory(TSMeshMaterial self);
TS_CAPI extern const char* tsMeshMaterialTypeBump;
TS_CAPI extern const char* tsMeshMaterialTypeHeight;
TS_CAPI extern const char* tsMeshMaterialTypeNormal;
TS_CAPI extern const char* tsMeshMaterialTypeEmission;
TS_CAPI extern const char* tsMeshMaterialTypeOcclusion;
TS_CAPI extern const char* tsMeshMaterialTypeOpacity;
TS_CAPI extern const char* tsMeshMaterialTypeAmbient;
TS_CAPI extern const char* tsMeshMaterialTypeDiffuse;
TS_CAPI extern const char* tsMeshMaterialTypeSpecular;
TS_CAPI extern const char* tsMeshMaterialTypeMetallic;
TS_CAPI extern const char* tsMeshMaterialTypeRoughness;
TS_CAPI extern const char* tsMeshMaterialTypeShininess;
TS_CAPI extern const char* tsMeshMaterialTypeGlossiness;
TS_CAPI extern const char* tsMeshMaterialTypeTransparent;
TS_CAPI extern const char* tsMeshMaterialTypeTransparency;
TS_CAPI extern const char* tsMeshMaterialTypeTransmission;
TS_CAPI extern const char* tsMeshMaterialTypeReflective;
TS_CAPI extern const char* tsMeshMaterialTypeReflectivity;
TS_CAPI extern const char* tsMeshMaterialTypeRefractiveIndex;
TS_CAPI extern const char* tsMeshMaterialTypeClearcoat;
TS_CAPI extern const char* tsMeshMaterialTypeClearcoatNormal;
TS_CAPI extern const char* tsMeshMaterialTypeClearcoatRoughness;
TS_CAPI extern const char* tsMeshMaterialTypeClearcoatGlossiness;
TS_CAPI extern const char* tsMeshMaterialTypeIridescence;
TS_CAPI extern const char* tsMeshMaterialTypeIridescenceThickness;
TS_CAPI extern const char* tsMeshMaterialTypeIridescenceRefractiveIndex;
TS_CAPI extern const char* tsMeshMaterialTypeSheen;
TS_CAPI extern const char* tsMeshMaterialTypeSheenRoughness;
TS_CAPI extern const char* tsMeshMaterialTypeVolume;
TS_CAPI extern const char* tsMeshMaterialTypeVolumeThickness;
TS_CAPI extern const char* tsMeshMaterialTypeAnisotropy;
TS_CAPI extern const char* tsMeshMaterialTypeAnisotropyAngle;
TS_CAPI extern const char* tsMeshMaterialTypeDoubleSided;
TS_CAPI extern const char* tsMeshMaterialTypeAlphaBlend;
TS_CAPI extern const char* tsMeshMaterialTypeAlphaMask;
TS_CAPI extern const char* tsMeshMaterialTypeTechnique;
TS_CAPI extern const char* tsMeshMaterialTypeTexCoord;

/// Tellusim::MeshGeometry
TS_CAPI TSMeshGeometry TS_CCALL tsMeshGeometry_new_s(const char *name);
TS_CAPI TSMeshGeometry TS_CCALL tsMeshGeometry_new_Ms(TSMesh mesh, const char *name);
TS_CAPI void TS_CCALL tsMeshGeometry_delete(TSMeshGeometry self);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_equalPtr(const TSMeshGeometry self, const TSMeshGeometry ptr);
TS_CAPI TSMeshGeometry TS_CCALL tsMeshGeometry_copyPtr(const TSMeshGeometry self);
TS_CAPI TSMeshGeometry TS_CCALL tsMeshGeometry_clonePtr(const TSMeshGeometry self);
TS_CAPI void TS_CCALL tsMeshGeometry_clearPtr(TSMeshGeometry self);
TS_CAPI void TS_CCALL tsMeshGeometry_destroyPtr(TSMeshGeometry self);
TS_CAPI void TS_CCALL tsMeshGeometry_acquirePtr(TSMeshGeometry self);
TS_CAPI void TS_CCALL tsMeshGeometry_unacquirePtr(TSMeshGeometry self);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_isValidPtr(const TSMeshGeometry self);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_isOwnerPtr(const TSMeshGeometry self);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_isConstPtr(const TSMeshGeometry self);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_getCountPtr(const TSMeshGeometry self);
TS_CAPI const void* TS_CCALL tsMeshGeometry_getInternalPtr(const TSMeshGeometry self);
TS_CAPI void TS_CCALL tsMeshGeometry_clear(TSMeshGeometry self);
TS_CAPI void TS_CCALL tsMeshGeometry_setName(TSMeshGeometry self, const char *name);
TS_CAPI TSString TS_CCALL tsMeshGeometry_getName(TSMeshGeometry self);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_getIndex(TSMeshGeometry self);
TS_CAPI void TS_CCALL tsMeshGeometry_setMesh(TSMeshGeometry self, TSMesh mesh, bool_t check);
TS_CAPI TSMesh TS_CCALL tsMeshGeometry_getMesh_c(TSMeshGeometry self);
TS_CAPI TSMesh TS_CCALL tsMeshGeometry_getMesh(TSMeshGeometry self);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_setParent0(TSMeshGeometry self, TSMeshGeometry parent, bool_t check);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_setParent1(TSMeshGeometry self, TSMeshGeometry parent, bool_t check);
TS_CAPI TSMeshGeometry TS_CCALL tsMeshGeometry_getParent0_c(TSMeshGeometry self);
TS_CAPI TSMeshGeometry TS_CCALL tsMeshGeometry_getParent1_c(TSMeshGeometry self);
TS_CAPI TSMeshGeometry TS_CCALL tsMeshGeometry_getParent0(TSMeshGeometry self);
TS_CAPI TSMeshGeometry TS_CCALL tsMeshGeometry_getParent1(TSMeshGeometry self);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_isRoot(TSMeshGeometry self);
TS_CAPI void TS_CCALL tsMeshGeometry_reserveChildren(TSMeshGeometry self, uint32_t num_children);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_addChild0(TSMeshGeometry self, TSMeshGeometry child, bool_t check);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_addChild1(TSMeshGeometry self, TSMeshGeometry child, bool_t check);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_removeChild(TSMeshGeometry self, TSMeshGeometry child);
TS_CAPI void TS_CCALL tsMeshGeometry_releaseChildren(TSMeshGeometry self);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_findChild(TSMeshGeometry self, const TSMeshGeometry child);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_getNumChildren(TSMeshGeometry self);
TS_CAPI TSMeshGeometry TS_CCALL tsMeshGeometry_getChild_cu(TSMeshGeometry self, uint32_t index);
TS_CAPI TSMeshGeometry TS_CCALL tsMeshGeometry_getChild_u(TSMeshGeometry self, uint32_t index);
TS_CAPI void TS_CCALL tsMeshGeometry_clearIndices(TSMeshGeometry self);
TS_CAPI void TS_CCALL tsMeshGeometry_reserveIndices(TSMeshGeometry self, uint32_t num_indices);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_addIndices(TSMeshGeometry self, TSMeshIndices indices, bool_t check);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_removeIndices(TSMeshGeometry self, TSMeshIndices indices);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_replaceIndices(TSMeshGeometry self, TSMeshIndices old_indices, TSMeshIndices indices);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_findIndices_ccMI(TSMeshGeometry self, const TSMeshIndices indices);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_findIndices_cMIT(TSMeshGeometry self, TS_MeshIndicesType type);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_hasIndices(TSMeshGeometry self, TS_MeshIndicesType type);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_hasSolidIndices(TSMeshGeometry self);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_getNumIndices_cMIT(TSMeshGeometry self, TS_MeshIndicesType type);
TS_CAPI TSMeshIndices TS_CCALL tsMeshGeometry_getIndices_cMIT(TSMeshGeometry self, TS_MeshIndicesType type);
TS_CAPI TSMeshIndices TS_CCALL tsMeshGeometry_getIndices_MIT(TSMeshGeometry self, TS_MeshIndicesType type);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_getNumIndices_c(TSMeshGeometry self);
TS_CAPI TSMeshIndices TS_CCALL tsMeshGeometry_getIndices_cu(TSMeshGeometry self, uint32_t index);
TS_CAPI TSMeshIndices TS_CCALL tsMeshGeometry_getIndices_u(TSMeshGeometry self, uint32_t index);
TS_CAPI void TS_CCALL tsMeshGeometry_clearAttributes(TSMeshGeometry self);
TS_CAPI void TS_CCALL tsMeshGeometry_reserveAttributes(TSMeshGeometry self, uint32_t num_attributes);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_addAttribute_MAb(TSMeshGeometry self, TSMeshAttribute attribute, bool_t check);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_addAttribute_MAMIb(TSMeshGeometry self, TSMeshAttribute attribute, TSMeshIndices indices, bool_t check);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_removeAttribute(TSMeshGeometry self, TSMeshAttribute attribute);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_replaceAttribute(TSMeshGeometry self, TSMeshAttribute old_attribute, TSMeshAttribute attribute);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_replaceAttributeIndices(TSMeshGeometry self, const TSMeshIndices old_indices, TSMeshIndices indices);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_findAttribute_cMATFu(TSMeshGeometry self, TS_MeshAttributeType type, TS_Format format, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_findAttribute_cMATu(TSMeshGeometry self, TS_MeshAttributeType type, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_findAttribute_csu(TSMeshGeometry self, const char *name, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_findAttribute_ccMA(TSMeshGeometry self, const TSMeshAttribute attribute);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_hasAttribute_cMATFu(TSMeshGeometry self, TS_MeshAttributeType type, TS_Format format, uint32_t index);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_hasAttribute_cMATu(TSMeshGeometry self, TS_MeshAttributeType type, uint32_t index);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_hasAttribute_csu(TSMeshGeometry self, const char *name, uint32_t index);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_hasAttribute_ccMA(TSMeshGeometry self, const TSMeshAttribute attribute);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_getNumAttributes_cMAT(TSMeshGeometry self, TS_MeshAttributeType type);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_getNumAttributes_ccMI(TSMeshGeometry self, const TSMeshIndices indices);
TS_CAPI TSMeshAttribute TS_CCALL tsMeshGeometry_getAttribute_cMATu(TSMeshGeometry self, TS_MeshAttributeType type, uint32_t index);
TS_CAPI TSMeshAttribute TS_CCALL tsMeshGeometry_getAttribute_MATu(TSMeshGeometry self, TS_MeshAttributeType type, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_getNumAttributes_c(TSMeshGeometry self);
TS_CAPI TSMeshAttribute TS_CCALL tsMeshGeometry_getAttribute_cu(TSMeshGeometry self, uint32_t index);
TS_CAPI TSMeshAttribute TS_CCALL tsMeshGeometry_getAttribute_u(TSMeshGeometry self, uint32_t index);
TS_CAPI void TS_CCALL tsMeshGeometry_clearJoints(TSMeshGeometry self);
TS_CAPI void TS_CCALL tsMeshGeometry_reserveJoints(TSMeshGeometry self, uint32_t num_joints);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_addJoint_MJb(TSMeshGeometry self, TSMeshJoint joint, bool_t check);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_addJoint_MJMNb(TSMeshGeometry self, TSMeshJoint joint, TSMeshNode node, bool_t check);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_removeJoint(TSMeshGeometry self, TSMeshJoint joint);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_replaceJoint(TSMeshGeometry self, TSMeshJoint old_joint, TSMeshJoint joint);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_findJoint_ccMJ(TSMeshGeometry self, const TSMeshJoint joint);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_findJoint_ccMN(TSMeshGeometry self, const TSMeshNode node);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_findJoint_cs(TSMeshGeometry self, const char *name);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_getNumJoints(TSMeshGeometry self);
TS_CAPI TSMeshJoint TS_CCALL tsMeshGeometry_getJoint_cu(TSMeshGeometry self, uint32_t index);
TS_CAPI TSMeshJoint TS_CCALL tsMeshGeometry_getJoint_u(TSMeshGeometry self, uint32_t index);
TS_CAPI void TS_CCALL tsMeshGeometry_clearMaterials(TSMeshGeometry self);
TS_CAPI void TS_CCALL tsMeshGeometry_reserveMaterials(TSMeshGeometry self, uint32_t num_materials);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_addMaterial_MMb(TSMeshGeometry self, TSMeshMaterial material, bool_t check);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_addMaterial_MMMIb(TSMeshGeometry self, TSMeshMaterial material, TSMeshIndices indices, bool_t check);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_removeMaterial(TSMeshGeometry self, TSMeshMaterial material);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_replaceMaterial(TSMeshGeometry self, TSMeshMaterial old_material, TSMeshMaterial material);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_findMaterial_ccMM(TSMeshGeometry self, const TSMeshMaterial material);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_findMaterial_cs(TSMeshGeometry self, const char *name);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_getNumMaterials(TSMeshGeometry self);
TS_CAPI TSMeshMaterial TS_CCALL tsMeshGeometry_getMaterial_cu(TSMeshGeometry self, uint32_t index);
TS_CAPI TSMeshMaterial TS_CCALL tsMeshGeometry_getMaterial_u(TSMeshGeometry self, uint32_t index);
TS_CAPI void TS_CCALL tsMeshGeometry_setBoundBox(TSMeshGeometry self, const TSBoundBoxf *box);
TS_CAPI TSBoundBoxf TS_CCALL tsMeshGeometry_getBoundBox(TSMeshGeometry self);
TS_CAPI void TS_CCALL tsMeshGeometry_setBoundSphere(TSMeshGeometry self, const TSBoundSpheref *sphere);
TS_CAPI TSBoundSpheref TS_CCALL tsMeshGeometry_getBoundSphere(TSMeshGeometry self);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_setTransform_cV3(TSMeshGeometry self, const TSVector3f *scale);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_setTransform_cM43b(TSMeshGeometry self, const TSMatrix4x3f *transform, bool_t apply);
TS_CAPI TSMatrix4x3f TS_CCALL tsMeshGeometry_getTransform(TSMeshGeometry self);
TS_CAPI void TS_CCALL tsMeshGeometry_setJointITransform(TSMeshGeometry self, const TSMatrix4x3f *itransform);
TS_CAPI TSMatrix4x3f TS_CCALL tsMeshGeometry_getJointITransform(TSMeshGeometry self);
TS_CAPI void TS_CCALL tsMeshGeometry_setMinVisibility(TSMeshGeometry self, float32_t distance);
TS_CAPI void TS_CCALL tsMeshGeometry_setMaxVisibility(TSMeshGeometry self, float32_t distance);
TS_CAPI void TS_CCALL tsMeshGeometry_setVisibilityRange(TSMeshGeometry self, float32_t min, float32_t max);
TS_CAPI float32_t TS_CCALL tsMeshGeometry_getMinVisibility(TSMeshGeometry self);
TS_CAPI float32_t TS_CCALL tsMeshGeometry_getMaxVisibility(TSMeshGeometry self);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_hasVisibilityRange(TSMeshGeometry self);
TS_CAPI void TS_CCALL tsMeshGeometry_setVisibilityError(TSMeshGeometry self, float32_t error);
TS_CAPI float32_t TS_CCALL tsMeshGeometry_getVisibilityError(TSMeshGeometry self);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_createBounds(TSMeshGeometry self, bool_t force, uint32_t position);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_createBasis_buuub(TSMeshGeometry self, bool_t force, uint32_t position, uint32_t normal, uint32_t tangent, bool_t append);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_createBasis_fbuuub(TSMeshGeometry self, float32_t angle, bool_t force, uint32_t position, uint32_t normal, uint32_t tangent, bool_t append);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_createNormals_bub(TSMeshGeometry self, bool_t force, uint32_t position, bool_t append);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_createNormals_fbub(TSMeshGeometry self, float32_t angle, bool_t force, uint32_t position, bool_t append);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_createTangents(TSMeshGeometry self, bool_t force, uint32_t position, uint32_t normal, uint32_t texcoord, bool_t append);
TS_CAPI uint32_t TS_CCALL tsMeshGeometry_createIslands(TSMeshGeometry self, uint32_t max_attributes, uint32_t max_primitives, bool_t force, uint32_t index, uint32_t position, bool_t append);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_optimizeIndices(TSMeshGeometry self, uint32_t cache, bool_t transparent, uint32_t index, uint32_t position);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_optimizeAttributes(TSMeshGeometry self, uint32_t material);
TS_CAPI void TS_CCALL tsMeshGeometry_optimizeMaterials(TSMeshGeometry self);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_packAttributes(TSMeshGeometry self, bool_t remove);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_unpackAttributes(TSMeshGeometry self, bool_t remove);
TS_CAPI int32_t TS_CCALL tsMeshGeometry_compare(TSMeshGeometry self, const TSMeshGeometry geometry, const TSMatrix4x3f *transform, float32_t threshold, bool_t spatial);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_isOptimized(TSMeshGeometry self);
TS_CAPI bool_t TS_CCALL tsMeshGeometry_validate(TSMeshGeometry self);
TS_CAPI size_t TS_CCALL tsMeshGeometry_getMemory(TSMeshGeometry self);

/// Tellusim::MeshTransform
TS_CAPI TSMeshTransform TS_CCALL tsMeshTransform_new(void);
TS_CAPI void TS_CCALL tsMeshTransform_delete(TSMeshTransform self);
TS_CAPI bool_t TS_CCALL tsMeshTransform_equalPtr(const TSMeshTransform self, const TSMeshTransform ptr);
TS_CAPI TSMeshTransform TS_CCALL tsMeshTransform_copyPtr(const TSMeshTransform self);
TS_CAPI TSMeshTransform TS_CCALL tsMeshTransform_clonePtr(const TSMeshTransform self);
TS_CAPI void TS_CCALL tsMeshTransform_clearPtr(TSMeshTransform self);
TS_CAPI void TS_CCALL tsMeshTransform_destroyPtr(TSMeshTransform self);
TS_CAPI void TS_CCALL tsMeshTransform_acquirePtr(TSMeshTransform self);
TS_CAPI void TS_CCALL tsMeshTransform_unacquirePtr(TSMeshTransform self);
TS_CAPI bool_t TS_CCALL tsMeshTransform_isValidPtr(const TSMeshTransform self);
TS_CAPI bool_t TS_CCALL tsMeshTransform_isOwnerPtr(const TSMeshTransform self);
TS_CAPI bool_t TS_CCALL tsMeshTransform_isConstPtr(const TSMeshTransform self);
TS_CAPI uint32_t TS_CCALL tsMeshTransform_getCountPtr(const TSMeshTransform self);
TS_CAPI const void* TS_CCALL tsMeshTransform_getInternalPtr(const TSMeshTransform self);
TS_CAPI void TS_CCALL tsMeshTransform_clear(TSMeshTransform self);
TS_CAPI float64_t TS_CCALL tsMeshTransform_getMinTime(TSMeshTransform self);
TS_CAPI float64_t TS_CCALL tsMeshTransform_getMaxTime(TSMeshTransform self);
TS_CAPI void TS_CCALL tsMeshTransform_setTransform_f64cM43f(TSMeshTransform self, float64_t time, const TSMatrix4x3d *transform, float32_t threshold);
TS_CAPI void TS_CCALL tsMeshTransform_setTranslate(TSMeshTransform self, float64_t time, const TSVector3d *translate, float32_t threshold);
TS_CAPI void TS_CCALL tsMeshTransform_setRotate(TSMeshTransform self, float64_t time, const TSQuaternionf *rotate, float32_t threshold);
TS_CAPI void TS_CCALL tsMeshTransform_setScale(TSMeshTransform self, float64_t time, const TSVector3f *scale, float32_t threshold);
TS_CAPI void TS_CCALL tsMeshTransform_setMorph(TSMeshTransform self, float64_t time, const TSVector4f *morph, float32_t threshold);
TS_CAPI TSMatrix4x3d TS_CCALL tsMeshTransform_getTransform(TSMeshTransform self, float64_t time);
TS_CAPI TSVector3d TS_CCALL tsMeshTransform_getTranslate(TSMeshTransform self, float64_t time);
TS_CAPI TSQuaternionf TS_CCALL tsMeshTransform_getRotate(TSMeshTransform self, float64_t time);
TS_CAPI TSVector3f TS_CCALL tsMeshTransform_getScale(TSMeshTransform self, float64_t time);
TS_CAPI TSVector4f TS_CCALL tsMeshTransform_getMorph(TSMeshTransform self, float64_t time);
TS_CAPI bool_t TS_CCALL tsMeshTransform_hasTransformKeys(TSMeshTransform self);
TS_CAPI bool_t TS_CCALL tsMeshTransform_hasTranslateKeys(TSMeshTransform self);
TS_CAPI bool_t TS_CCALL tsMeshTransform_hasRotateKeys(TSMeshTransform self);
TS_CAPI bool_t TS_CCALL tsMeshTransform_hasScaleKeys(TSMeshTransform self);
TS_CAPI bool_t TS_CCALL tsMeshTransform_hasMorphKeys(TSMeshTransform self);
TS_CAPI void TS_CCALL tsMeshTransform_setTransform_cV3(TSMeshTransform self, const TSVector3d *scale);
TS_CAPI void TS_CCALL tsMeshTransform_setTransform_cM43(TSMeshTransform self, const TSMatrix4x3d *transform);
TS_CAPI size_t TS_CCALL tsMeshTransform_getMemory(TSMeshTransform self);

/// Tellusim::MeshAnimation
TS_CAPI TSMeshAnimation TS_CCALL tsMeshAnimation_new_s(const char *name);
TS_CAPI TSMeshAnimation TS_CCALL tsMeshAnimation_new_Ms(TSMesh mesh, const char *name);
TS_CAPI void TS_CCALL tsMeshAnimation_delete(TSMeshAnimation self);
TS_CAPI bool_t TS_CCALL tsMeshAnimation_equalPtr(const TSMeshAnimation self, const TSMeshAnimation ptr);
TS_CAPI TSMeshAnimation TS_CCALL tsMeshAnimation_copyPtr(const TSMeshAnimation self);
TS_CAPI TSMeshAnimation TS_CCALL tsMeshAnimation_clonePtr(const TSMeshAnimation self);
TS_CAPI void TS_CCALL tsMeshAnimation_clearPtr(TSMeshAnimation self);
TS_CAPI void TS_CCALL tsMeshAnimation_destroyPtr(TSMeshAnimation self);
TS_CAPI void TS_CCALL tsMeshAnimation_acquirePtr(TSMeshAnimation self);
TS_CAPI void TS_CCALL tsMeshAnimation_unacquirePtr(TSMeshAnimation self);
TS_CAPI bool_t TS_CCALL tsMeshAnimation_isValidPtr(const TSMeshAnimation self);
TS_CAPI bool_t TS_CCALL tsMeshAnimation_isOwnerPtr(const TSMeshAnimation self);
TS_CAPI bool_t TS_CCALL tsMeshAnimation_isConstPtr(const TSMeshAnimation self);
TS_CAPI uint32_t TS_CCALL tsMeshAnimation_getCountPtr(const TSMeshAnimation self);
TS_CAPI const void* TS_CCALL tsMeshAnimation_getInternalPtr(const TSMeshAnimation self);
TS_CAPI void TS_CCALL tsMeshAnimation_clear(TSMeshAnimation self);
TS_CAPI uint32_t TS_CCALL tsMeshAnimation_getIndex(TSMeshAnimation self);
TS_CAPI void TS_CCALL tsMeshAnimation_setName(TSMeshAnimation self, const char *name);
TS_CAPI TSString TS_CCALL tsMeshAnimation_getName(TSMeshAnimation self);
TS_CAPI void TS_CCALL tsMeshAnimation_setMesh(TSMeshAnimation self, TSMesh mesh, bool_t check);
TS_CAPI TSMesh TS_CCALL tsMeshAnimation_getMesh_c(TSMeshAnimation self);
TS_CAPI TSMesh TS_CCALL tsMeshAnimation_getMesh(TSMeshAnimation self);
TS_CAPI float64_t TS_CCALL tsMeshAnimation_getMinTime(TSMeshAnimation self);
TS_CAPI float64_t TS_CCALL tsMeshAnimation_getMaxTime(TSMeshAnimation self);
TS_CAPI void TS_CCALL tsMeshAnimation_setNumTransforms(TSMeshAnimation self, uint32_t num_transforms);
TS_CAPI uint32_t TS_CCALL tsMeshAnimation_getNumTransforms(TSMeshAnimation self);
TS_CAPI TSMeshTransform TS_CCALL tsMeshAnimation_getTransform_cu(TSMeshAnimation self, uint32_t node);
TS_CAPI TSMeshTransform TS_CCALL tsMeshAnimation_getTransform_u(TSMeshAnimation self, uint32_t node);
TS_CAPI void TS_CCALL tsMeshAnimation_setTransform_f64ucM43f(TSMeshAnimation self, float64_t time, uint32_t node, const TSMatrix4x3d *transform, float32_t threshold);
TS_CAPI void TS_CCALL tsMeshAnimation_setTranslate(TSMeshAnimation self, float64_t time, uint32_t node, const TSVector3d *translate, float32_t threshold);
TS_CAPI void TS_CCALL tsMeshAnimation_setRotate(TSMeshAnimation self, float64_t time, uint32_t node, const TSQuaternionf *rotate, float32_t threshold);
TS_CAPI void TS_CCALL tsMeshAnimation_setScale(TSMeshAnimation self, float64_t time, uint32_t node, const TSVector3f *scale, float32_t threshold);
TS_CAPI void TS_CCALL tsMeshAnimation_setMorph(TSMeshAnimation self, float64_t time, uint32_t node, const TSVector4f *morph, float32_t threshold);
TS_CAPI void TS_CCALL tsMeshAnimation_setTime_f64cM43bf64f64(TSMeshAnimation self, float64_t time, const TSMatrix4x3d *transform, bool_t loop, float64_t from, float64_t to);
TS_CAPI void TS_CCALL tsMeshAnimation_setTime_f64bf64f64(TSMeshAnimation self, float64_t time, bool_t loop, float64_t from, float64_t to);
TS_CAPI TSMatrix4x3d TS_CCALL tsMeshAnimation_getLocalTransform_cu(TSMeshAnimation self, uint32_t node);
TS_CAPI TSMatrix4x3d TS_CCALL tsMeshAnimation_getLocalTransform_ccMN(TSMeshAnimation self, const TSMeshNode node);
TS_CAPI TSMatrix4x3d TS_CCALL tsMeshAnimation_getLocalTransform_ccMJ(TSMeshAnimation self, const TSMeshJoint joint);
TS_CAPI TSMatrix4x3d TS_CCALL tsMeshAnimation_getGlobalTransform_cu(TSMeshAnimation self, uint32_t node);
TS_CAPI TSMatrix4x3d TS_CCALL tsMeshAnimation_getGlobalTransform_ccMN(TSMeshAnimation self, const TSMeshNode node);
TS_CAPI TSMatrix4x3d TS_CCALL tsMeshAnimation_getGlobalTransform_ccMJ(TSMeshAnimation self, const TSMeshJoint joint);
TS_CAPI TSVector4f TS_CCALL tsMeshAnimation_getMorphTransform_cu(TSMeshAnimation self, uint32_t node);
TS_CAPI TSVector4f TS_CCALL tsMeshAnimation_getMorphTransform_ccMN(TSMeshAnimation self, const TSMeshNode node);
TS_CAPI TSBoundBoxd TS_CCALL tsMeshAnimation_getBoundBox_c(TSMeshAnimation self);
TS_CAPI TSBoundBoxd TS_CCALL tsMeshAnimation_getBoundBox_ccMN(TSMeshAnimation self, const TSMeshNode node);
TS_CAPI TSBoundBoxd TS_CCALL tsMeshAnimation_getBoundBox_ccMG(TSMeshAnimation self, const TSMeshGeometry geometry);
TS_CAPI TSBoundBoxd TS_CCALL tsMeshAnimation_getBoundBox_ccMGcV4(TSMeshAnimation self, const TSMeshGeometry geometry, const TSVector4f *morph);
TS_CAPI void TS_CCALL tsMeshAnimation_setTransform_cV3(TSMeshAnimation self, const TSVector3d *scale);
TS_CAPI void TS_CCALL tsMeshAnimation_setTransform_cM43(TSMeshAnimation self, const TSMatrix4x3d *transform);
TS_CAPI void TS_CCALL tsMeshAnimation_optimizeTransforms(TSMeshAnimation self, float32_t threshold);
TS_CAPI size_t TS_CCALL tsMeshAnimation_getMemory(TSMeshAnimation self);

/// Tellusim::MeshAttachment
TS_CAPI TSMeshAttachment TS_CCALL tsMeshAttachment_new_s(const char *name);
TS_CAPI TSMeshAttachment TS_CCALL tsMeshAttachment_new_MATs(TS_MeshAttachmentType type, const char *name);
TS_CAPI TSMeshAttachment TS_CCALL tsMeshAttachment_new_MNs(TSMeshNode node, const char *name);
TS_CAPI void TS_CCALL tsMeshAttachment_delete(TSMeshAttachment self);
TS_CAPI bool_t TS_CCALL tsMeshAttachment_equalPtr(const TSMeshAttachment self, const TSMeshAttachment ptr);
TS_CAPI TSMeshAttachment TS_CCALL tsMeshAttachment_copyPtr(const TSMeshAttachment self);
TS_CAPI TSMeshAttachment TS_CCALL tsMeshAttachment_clonePtr(const TSMeshAttachment self);
TS_CAPI void TS_CCALL tsMeshAttachment_clearPtr(TSMeshAttachment self);
TS_CAPI void TS_CCALL tsMeshAttachment_destroyPtr(TSMeshAttachment self);
TS_CAPI void TS_CCALL tsMeshAttachment_acquirePtr(TSMeshAttachment self);
TS_CAPI void TS_CCALL tsMeshAttachment_unacquirePtr(TSMeshAttachment self);
TS_CAPI bool_t TS_CCALL tsMeshAttachment_isValidPtr(const TSMeshAttachment self);
TS_CAPI bool_t TS_CCALL tsMeshAttachment_isOwnerPtr(const TSMeshAttachment self);
TS_CAPI bool_t TS_CCALL tsMeshAttachment_isConstPtr(const TSMeshAttachment self);
TS_CAPI uint32_t TS_CCALL tsMeshAttachment_getCountPtr(const TSMeshAttachment self);
TS_CAPI const void* TS_CCALL tsMeshAttachment_getInternalPtr(const TSMeshAttachment self);
TS_CAPI void TS_CCALL tsMeshAttachment_clear(TSMeshAttachment self);
TS_CAPI void TS_CCALL tsMeshAttachment_setType(TSMeshAttachment self, TS_MeshAttachmentType type);
TS_CAPI TS_MeshAttachmentType TS_CCALL tsMeshAttachment_getType(TSMeshAttachment self);
TS_CAPI const char* TS_CCALL tsMeshAttachment_getTypeName_MAT(TS_MeshAttachmentType type);
TS_CAPI const char* TS_CCALL tsMeshAttachment_getTypeName_c(TSMeshAttachment self);
TS_CAPI bool_t TS_CCALL tsMeshAttachment_isUnknown(TSMeshAttachment self);
TS_CAPI bool_t TS_CCALL tsMeshAttachment_isLight(TSMeshAttachment self);
TS_CAPI bool_t TS_CCALL tsMeshAttachment_isCamera(TSMeshAttachment self);
TS_CAPI void TS_CCALL tsMeshAttachment_setName(TSMeshAttachment self, const char *name);
TS_CAPI TSString TS_CCALL tsMeshAttachment_getName(TSMeshAttachment self);
TS_CAPI void TS_CCALL tsMeshAttachment_setNode(TSMeshAttachment self, TSMeshNode node, bool_t check);
TS_CAPI TSMeshNode TS_CCALL tsMeshAttachment_getNode_c(TSMeshAttachment self);
TS_CAPI TSMeshNode TS_CCALL tsMeshAttachment_getNode(TSMeshAttachment self);
TS_CAPI void TS_CCALL tsMeshAttachment_setData_s(TSMeshAttachment self, const char *data);
TS_CAPI void TS_CCALL tsMeshAttachment_setData_cS(TSMeshAttachment self, const TSString data);
TS_CAPI TSString TS_CCALL tsMeshAttachment_getData(TSMeshAttachment self);
TS_CAPI void TS_CCALL tsMeshAttachment_clearParameters(TSMeshAttachment self);
TS_CAPI bool_t TS_CCALL tsMeshAttachment_removeParameter(TSMeshAttachment self, const char *type);
TS_CAPI void TS_CCALL tsMeshAttachment_copyParameters(TSMeshAttachment self, const TSMeshAttachment attachment);
TS_CAPI uint32_t TS_CCALL tsMeshAttachment_findParameter(TSMeshAttachment self, const char *type);
TS_CAPI bool_t TS_CCALL tsMeshAttachment_hasParameter(TSMeshAttachment self, const char *type);
TS_CAPI uint32_t TS_CCALL tsMeshAttachment_getNumParameters(TSMeshAttachment self);
TS_CAPI TSString TS_CCALL tsMeshAttachment_getParameterType(TSMeshAttachment self, uint32_t index);
TS_CAPI void TS_CCALL tsMeshAttachment_addParameter_sb(TSMeshAttachment self, const char *type, bool_t value);
TS_CAPI void TS_CCALL tsMeshAttachment_addParameter_sf(TSMeshAttachment self, const char *type, float32_t value);
TS_CAPI void TS_CCALL tsMeshAttachment_addParameter_scV4(TSMeshAttachment self, const char *type, const TSVector4f *vector);
TS_CAPI void TS_CCALL tsMeshAttachment_addParameter_scC(TSMeshAttachment self, const char *type, const TSColor *color);
TS_CAPI void TS_CCALL tsMeshAttachment_addParameter_ss(TSMeshAttachment self, const char *type, const char *name);
TS_CAPI void TS_CCALL tsMeshAttachment_addParameter_scS(TSMeshAttachment self, const char *type, const TSString name);
TS_CAPI TS_MeshAttachmentFlags TS_CCALL tsMeshAttachment_getParameterFlags_cu(TSMeshAttachment self, uint32_t index);
TS_CAPI bool_t TS_CCALL tsMeshAttachment_hasParameterFlag_cuMAF(TSMeshAttachment self, uint32_t index, TS_MeshAttachmentFlags flags);
TS_CAPI bool_t TS_CCALL tsMeshAttachment_hasParameterFlags_cuMAF(TSMeshAttachment self, uint32_t index, TS_MeshAttachmentFlags flags);
TS_CAPI bool_t TS_CCALL tsMeshAttachment_getParameterBool_cub(TSMeshAttachment self, uint32_t index, bool_t value);
TS_CAPI float32_t TS_CCALL tsMeshAttachment_getParameterScalarf32_cuf(TSMeshAttachment self, uint32_t index, float32_t value);
TS_CAPI TSVector4f TS_CCALL tsMeshAttachment_getParameterVector4f_cucV4(TSMeshAttachment self, uint32_t index, const TSVector4f *vector);
TS_CAPI TSColor TS_CCALL tsMeshAttachment_getParameterColor_cucC(TSMeshAttachment self, uint32_t index, const TSColor *color);
TS_CAPI TSString TS_CCALL tsMeshAttachment_getParameterName_cucS(TSMeshAttachment self, uint32_t index, const TSString name);
TS_CAPI TS_MeshAttachmentFlags TS_CCALL tsMeshAttachment_getParameterFlags_cs(TSMeshAttachment self, const char *type);
TS_CAPI bool_t TS_CCALL tsMeshAttachment_hasParameterFlag_csMAF(TSMeshAttachment self, const char *type, TS_MeshAttachmentFlags flags);
TS_CAPI bool_t TS_CCALL tsMeshAttachment_hasParameterFlags_csMAF(TSMeshAttachment self, const char *type, TS_MeshAttachmentFlags flags);
TS_CAPI bool_t TS_CCALL tsMeshAttachment_getParameterBool_csb(TSMeshAttachment self, const char *type, bool_t value);
TS_CAPI float32_t TS_CCALL tsMeshAttachment_getParameterScalarf32_csf(TSMeshAttachment self, const char *type, float32_t value);
TS_CAPI TSVector4f TS_CCALL tsMeshAttachment_getParameterVector4f_cscV4(TSMeshAttachment self, const char *type, const TSVector4f *vector);
TS_CAPI TSColor TS_CCALL tsMeshAttachment_getParameterColor_cscC(TSMeshAttachment self, const char *type, const TSColor *color);
TS_CAPI TSString TS_CCALL tsMeshAttachment_getParameterName_cscS(TSMeshAttachment self, const char *type, const TSString name);
TS_CAPI void TS_CCALL tsMeshAttachment_setTransform_cV3(TSMeshAttachment self, const TSVector3f *scale);
TS_CAPI void TS_CCALL tsMeshAttachment_setTransform_cM43(TSMeshAttachment self, const TSMatrix4x3f *transform);
TS_CAPI TSMatrix4x3f TS_CCALL tsMeshAttachment_getTransform(TSMeshAttachment self);
TS_CAPI int32_t TS_CCALL tsMeshAttachment_compare(TSMeshAttachment self, const TSMeshAttachment attachment);
TS_CAPI size_t TS_CCALL tsMeshAttachment_getMemory(TSMeshAttachment self);
TS_CAPI extern const char* tsMeshAttachmentTypeColor;
TS_CAPI extern const char* tsMeshAttachmentTypeIntensity;
TS_CAPI extern const char* tsMeshAttachmentTypeTemperature;
TS_CAPI extern const char* tsMeshAttachmentTypeInnerAngle;
TS_CAPI extern const char* tsMeshAttachmentTypeOuterAngle;
TS_CAPI extern const char* tsMeshAttachmentTypeAttenuation;
TS_CAPI extern const char* tsMeshAttachmentTypeDiffuse;
TS_CAPI extern const char* tsMeshAttachmentTypeSpecular;
TS_CAPI extern const char* tsMeshAttachmentTypeWidth;
TS_CAPI extern const char* tsMeshAttachmentTypeHeight;
TS_CAPI extern const char* tsMeshAttachmentTypeRadius;
TS_CAPI extern const char* tsMeshAttachmentTypeLength;
TS_CAPI extern const char* tsMeshAttachmentTypeShadow;
TS_CAPI extern const char* tsMeshAttachmentTypeAspect;
TS_CAPI extern const char* tsMeshAttachmentTypeFovX;
TS_CAPI extern const char* tsMeshAttachmentTypeFovY;
TS_CAPI extern const char* tsMeshAttachmentTypeSizeX;
TS_CAPI extern const char* tsMeshAttachmentTypeSizeY;
TS_CAPI extern const char* tsMeshAttachmentTypeZNear;
TS_CAPI extern const char* tsMeshAttachmentTypeZFar;
TS_CAPI extern const char* tsMeshAttachmentTypeFStop;
TS_CAPI extern const char* tsMeshAttachmentTypeExposure;
TS_CAPI extern const char* tsMeshAttachmentTypeApertureX;
TS_CAPI extern const char* tsMeshAttachmentTypeApertureY;
TS_CAPI extern const char* tsMeshAttachmentTypeFocalLength;
TS_CAPI extern const char* tsMeshAttachmentTypeFocusDistance;

/// Tellusim::Mesh
TS_CAPI TSMesh TS_CCALL tsMesh_new(void);
TS_CAPI void TS_CCALL tsMesh_delete(TSMesh self);
TS_CAPI bool_t TS_CCALL tsMesh_equalPtr(const TSMesh self, const TSMesh ptr);
TS_CAPI TSMesh TS_CCALL tsMesh_copyPtr(const TSMesh self);
TS_CAPI TSMesh TS_CCALL tsMesh_clonePtr(const TSMesh self);
TS_CAPI void TS_CCALL tsMesh_clearPtr(TSMesh self);
TS_CAPI void TS_CCALL tsMesh_destroyPtr(TSMesh self);
TS_CAPI void TS_CCALL tsMesh_acquirePtr(TSMesh self);
TS_CAPI void TS_CCALL tsMesh_unacquirePtr(TSMesh self);
TS_CAPI bool_t TS_CCALL tsMesh_isValidPtr(const TSMesh self);
TS_CAPI bool_t TS_CCALL tsMesh_isOwnerPtr(const TSMesh self);
TS_CAPI bool_t TS_CCALL tsMesh_isConstPtr(const TSMesh self);
TS_CAPI uint32_t TS_CCALL tsMesh_getCountPtr(const TSMesh self);
TS_CAPI const void* TS_CCALL tsMesh_getInternalPtr(const TSMesh self);
TS_CAPI void TS_CCALL tsMesh_clear(TSMesh self);
TS_CAPI bool_t TS_CCALL tsMesh_isLoaded(TSMesh self);
TS_CAPI bool_t TS_CCALL tsMesh_info_sMFA(TSMesh self, const char *name, TS_MeshFlags flags, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_info_cSMFA(TSMesh self, const TSString name, TS_MeshFlags flags, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_info_StMFA(TSMesh self, TSStream stream, TS_MeshFlags flags, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_info_sA(TSMesh self, const char *name, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_info_cSA(TSMesh self, const TSString name, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_info_StA(TSMesh self, TSStream stream, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_load_sMFA(TSMesh self, const char *name, TS_MeshFlags flags, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_load_cSMFA(TSMesh self, const TSString name, TS_MeshFlags flags, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_load_StMFA(TSMesh self, TSStream stream, TS_MeshFlags flags, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_load_sA(TSMesh self, const char *name, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_load_cSA(TSMesh self, const TSString name, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_load_StA(TSMesh self, TSStream stream, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_save_csMF(TSMesh self, const char *name, TS_MeshFlags flags);
TS_CAPI bool_t TS_CCALL tsMesh_save_ccSMF(TSMesh self, const TSString name, TS_MeshFlags flags);
TS_CAPI bool_t TS_CCALL tsMesh_save_cStMF(TSMesh self, TSStream stream, TS_MeshFlags flags);
TS_CAPI void TS_CCALL tsMesh_setName(TSMesh self, const char *name);
TS_CAPI TSString TS_CCALL tsMesh_getName(TSMesh self);
TS_CAPI bool_t TS_CCALL tsMesh_setBasis_MAMAMA(TSMesh self, TS_MeshAxis front, TS_MeshAxis right, TS_MeshAxis up);
TS_CAPI bool_t TS_CCALL tsMesh_setBasis_MB(TSMesh self, TS_MeshBasis basis);
TS_CAPI TS_MeshAxis TS_CCALL tsMesh_getFrontAxis(TSMesh self);
TS_CAPI TS_MeshAxis TS_CCALL tsMesh_getRightAxis(TSMesh self);
TS_CAPI TS_MeshAxis TS_CCALL tsMesh_getUpAxis(TSMesh self);
TS_CAPI TS_MeshBasis TS_CCALL tsMesh_getBasis(TSMesh self);
TS_CAPI const char* TS_CCALL tsMesh_getFrontAxisName(TSMesh self);
TS_CAPI const char* TS_CCALL tsMesh_getRightAxisName(TSMesh self);
TS_CAPI const char* TS_CCALL tsMesh_getUpAxisName(TSMesh self);
TS_CAPI TSString TS_CCALL tsMesh_getBasisName(TSMesh self);
TS_CAPI void TS_CCALL tsMesh_clearNodes(TSMesh self);
TS_CAPI void TS_CCALL tsMesh_reserveNodes(TSMesh self, uint32_t num_nodes);
TS_CAPI uint32_t TS_CCALL tsMesh_addNode(TSMesh self, TSMeshNode node, bool_t check);
TS_CAPI bool_t TS_CCALL tsMesh_removeNode(TSMesh self, TSMeshNode node);
TS_CAPI uint32_t TS_CCALL tsMesh_findNode_ccMN(TSMesh self, const TSMeshNode node);
TS_CAPI uint32_t TS_CCALL tsMesh_findNode_cs(TSMesh self, const char *name);
TS_CAPI uint32_t TS_CCALL tsMesh_getNumNodes(TSMesh self);
TS_CAPI TSMeshNode TS_CCALL tsMesh_getNode_cu(TSMesh self, uint32_t index);
TS_CAPI TSMeshNode TS_CCALL tsMesh_getNode_u(TSMesh self, uint32_t index);
TS_CAPI void TS_CCALL tsMesh_createLocalTransforms(TSMesh self, const TSMatrix4x3d *itransform);
TS_CAPI void TS_CCALL tsMesh_createGlobalTransforms(TSMesh self, const TSMatrix4x3d *transform);
TS_CAPI void TS_CCALL tsMesh_clearGeometries(TSMesh self);
TS_CAPI void TS_CCALL tsMesh_reserveGeometries(TSMesh self, uint32_t num_geometries);
TS_CAPI uint32_t TS_CCALL tsMesh_addGeometry_MGb(TSMesh self, TSMeshGeometry geometry, bool_t check);
TS_CAPI uint32_t TS_CCALL tsMesh_addGeometry_MGMNb(TSMesh self, TSMeshGeometry geometry, TSMeshNode node, bool_t check);
TS_CAPI bool_t TS_CCALL tsMesh_removeGeometry(TSMesh self, TSMeshGeometry geometry);
TS_CAPI bool_t TS_CCALL tsMesh_replaceGeometry(TSMesh self, TSMeshGeometry old_geometry, TSMeshGeometry geometry);
TS_CAPI uint32_t TS_CCALL tsMesh_findGeometry_ccMG(TSMesh self, const TSMeshGeometry geometry);
TS_CAPI uint32_t TS_CCALL tsMesh_findGeometry_cs(TSMesh self, const char *name);
TS_CAPI uint32_t TS_CCALL tsMesh_getNumGeometries(TSMesh self);
TS_CAPI TSMeshGeometry TS_CCALL tsMesh_getGeometry_cu(TSMesh self, uint32_t index);
TS_CAPI TSMeshGeometry TS_CCALL tsMesh_getGeometry_u(TSMesh self, uint32_t index);
TS_CAPI bool_t TS_CCALL tsMesh_hasGeometryIndices(TSMesh self, TS_MeshIndicesType type);
TS_CAPI bool_t TS_CCALL tsMesh_hasGeometryAttribute(TSMesh self, TS_MeshAttributeType type);
TS_CAPI size_t TS_CCALL tsMesh_getNumGeometryPositions(TSMesh self);
TS_CAPI size_t TS_CCALL tsMesh_getNumGeometryPrimitives(TSMesh self);
TS_CAPI void TS_CCALL tsMesh_clearAnimations(TSMesh self);
TS_CAPI void TS_CCALL tsMesh_reserveAnimations(TSMesh self, uint32_t num_animations);
TS_CAPI uint32_t TS_CCALL tsMesh_addAnimation(TSMesh self, TSMeshAnimation animation, bool_t check);
TS_CAPI bool_t TS_CCALL tsMesh_removeAnimation(TSMesh self, TSMeshAnimation animation);
TS_CAPI bool_t TS_CCALL tsMesh_replaceAnimation(TSMesh self, TSMeshAnimation old_animation, TSMeshAnimation animation);
TS_CAPI uint32_t TS_CCALL tsMesh_findAnimation_ccMA(TSMesh self, const TSMeshAnimation animation);
TS_CAPI uint32_t TS_CCALL tsMesh_findAnimation_cs(TSMesh self, const char *name);
TS_CAPI uint32_t TS_CCALL tsMesh_getNumAnimations(TSMesh self);
TS_CAPI TSMeshAnimation TS_CCALL tsMesh_getAnimation_cu(TSMesh self, uint32_t index);
TS_CAPI TSMeshAnimation TS_CCALL tsMesh_getAnimation_u(TSMesh self, uint32_t index);
TS_CAPI TSBoundBoxd TS_CCALL tsMesh_getBoundBox_c(TSMesh self);
TS_CAPI TSBoundBoxd TS_CCALL tsMesh_getBoundBox_ccMN(TSMesh self, const TSMeshNode node);
TS_CAPI TSBoundBoxd TS_CCALL tsMesh_getBoundBox_ccMG(TSMesh self, const TSMeshGeometry geometry);
TS_CAPI bool_t TS_CCALL tsMesh_createBounds_bA(TSMesh self, bool_t force, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_createBounds_A(TSMesh self, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_createBasis_bA(TSMesh self, bool_t force, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_createBasis_fbA(TSMesh self, float32_t angle, bool_t force, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_createBasis_A(TSMesh self, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_createBasis_fA(TSMesh self, float32_t angle, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_createNormals_bA(TSMesh self, bool_t force, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_createNormals_fbA(TSMesh self, float32_t angle, bool_t force, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_createNormals_A(TSMesh self, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_createNormals_fA(TSMesh self, float32_t angle, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_createTangents_bA(TSMesh self, bool_t force, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_createTangents_A(TSMesh self, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_createIslands_uubA(TSMesh self, uint32_t max_attributes, uint32_t max_primitives, bool_t force, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_createIslands_uuA(TSMesh self, uint32_t max_attributes, uint32_t max_primitives, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_optimizeIndices_ubA(TSMesh self, uint32_t cache, bool_t transparent, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_optimizeIndices_A(TSMesh self, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_optimizeIndices_uA(TSMesh self, uint32_t cache, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMesh_optimizeAttributes(TSMesh self, TSAsync *async);
TS_CAPI void TS_CCALL tsMesh_optimizeMaterials(TSMesh self);
TS_CAPI bool_t TS_CCALL tsMesh_optimizeWinding(TSMesh self, bool_t clockwise);
TS_CAPI void TS_CCALL tsMesh_optimizeGeometries(TSMesh self, float32_t threshold, uint32_t depth);
TS_CAPI void TS_CCALL tsMesh_optimizeAnimations(TSMesh self, float32_t threshold);
TS_CAPI bool_t TS_CCALL tsMesh_optimizeOrder(TSMesh self);
TS_CAPI void TS_CCALL tsMesh_mergeGeometries(TSMesh self);
TS_CAPI bool_t TS_CCALL tsMesh_packAttributes(TSMesh self, bool_t remove);
TS_CAPI bool_t TS_CCALL tsMesh_unpackAttributes(TSMesh self, bool_t remove);
TS_CAPI bool_t TS_CCALL tsMesh_setTransform(TSMesh self, const TSVector3d *scale);
TS_CAPI size_t TS_CCALL tsMesh_getMemory(TSMesh self);

/// Tellusim::Json
TS_CAPI TSJson TS_CCALL tsJson_new(void);
TS_CAPI TSJson TS_CCALL tsJson_new_JT(TS_JsonType type);
TS_CAPI TSJson TS_CCALL tsJson_new_sJT(const char *name, TS_JsonType type);
TS_CAPI TSJson TS_CCALL tsJson_new_cSJT(const TSString name, TS_JsonType type);
TS_CAPI TSJson TS_CCALL tsJson_new_JsJT(TSJson *parent, const char *name, TS_JsonType type);
TS_CAPI TSJson TS_CCALL tsJson_new_JcSJT(TSJson *parent, const TSString name, TS_JsonType type);
TS_CAPI void TS_CCALL tsJson_delete(TSJson self);
TS_CAPI bool_t TS_CCALL tsJson_equalPtr(const TSJson self, const TSJson ptr);
TS_CAPI TSJson TS_CCALL tsJson_copyPtr(const TSJson self);
TS_CAPI TSJson TS_CCALL tsJson_clonePtr(const TSJson self);
TS_CAPI void TS_CCALL tsJson_clearPtr(TSJson self);
TS_CAPI void TS_CCALL tsJson_destroyPtr(TSJson self);
TS_CAPI void TS_CCALL tsJson_acquirePtr(TSJson self);
TS_CAPI void TS_CCALL tsJson_unacquirePtr(TSJson self);
TS_CAPI bool_t TS_CCALL tsJson_isValidPtr(const TSJson self);
TS_CAPI bool_t TS_CCALL tsJson_isOwnerPtr(const TSJson self);
TS_CAPI bool_t TS_CCALL tsJson_isConstPtr(const TSJson self);
TS_CAPI uint32_t TS_CCALL tsJson_getCountPtr(const TSJson self);
TS_CAPI const void* TS_CCALL tsJson_getInternalPtr(const TSJson self);
TS_CAPI void TS_CCALL tsJson_clear(TSJson self);
TS_CAPI bool_t TS_CCALL tsJson_create_szb(TSJson self, const char *str, size_t size, bool_t owner);
TS_CAPI bool_t TS_CCALL tsJson_create_cSzb(TSJson self, const TSString str, size_t size, bool_t owner);
TS_CAPI bool_t TS_CCALL tsJson_load_s(TSJson self, const char *name);
TS_CAPI bool_t TS_CCALL tsJson_load_cS(TSJson self, const TSString name);
TS_CAPI bool_t TS_CCALL tsJson_load_St(TSJson self, TSStream stream);
TS_CAPI bool_t TS_CCALL tsJson_save_csb(TSJson self, const char *name, bool_t compact);
TS_CAPI bool_t TS_CCALL tsJson_save_ccSb(TSJson self, const TSString name, bool_t compact);
TS_CAPI bool_t TS_CCALL tsJson_save_cStb(TSJson self, TSStream stream, bool_t compact);
TS_CAPI TSJson TS_CCALL tsJson_getRoot_c(TSJson self);
TS_CAPI TSJson TS_CCALL tsJson_getRoot(TSJson self);
TS_CAPI uint32_t TS_CCALL tsJson_setParent(TSJson self, TSJson parent, bool_t check);
TS_CAPI TSJson TS_CCALL tsJson_getParent_c(TSJson self);
TS_CAPI TSJson TS_CCALL tsJson_getParent(TSJson self);
TS_CAPI TSJson TS_CCALL tsJson_addChild_sJTb(TSJson self, const char *name, TS_JsonType type, bool_t check);
TS_CAPI uint32_t TS_CCALL tsJson_addChild_Jb(TSJson self, TSJson child, bool_t check);
TS_CAPI bool_t TS_CCALL tsJson_removeChild(TSJson self, TSJson child);
TS_CAPI void TS_CCALL tsJson_releaseChildren(TSJson self);
TS_CAPI uint32_t TS_CCALL tsJson_findChild(TSJson self, const char *name);
TS_CAPI bool_t TS_CCALL tsJson_isChild(TSJson self, const char *name);
TS_CAPI TSJson TS_CCALL tsJson_getChild_cs(TSJson self, const char *name);
TS_CAPI TSJson TS_CCALL tsJson_getChild_s(TSJson self, const char *name);
TS_CAPI uint32_t TS_CCALL tsJson_getNumChildren(TSJson self);
TS_CAPI TSJson TS_CCALL tsJson_getChild_cu(TSJson self, uint32_t index);
TS_CAPI TSJson TS_CCALL tsJson_getChild_u(TSJson self, uint32_t index);
TS_CAPI TSString TS_CCALL tsJson_getPathName(TSJson self);
TS_CAPI void TS_CCALL tsJson_setName_s(TSJson self, const char *name);
TS_CAPI void TS_CCALL tsJson_setName_cS(TSJson self, const TSString name);
TS_CAPI TSString TS_CCALL tsJson_getName(TSJson self);
TS_CAPI void TS_CCALL tsJson_setType(TSJson self, TS_JsonType type);
TS_CAPI TS_JsonType TS_CCALL tsJson_getType(TSJson self);
TS_CAPI const char* TS_CCALL tsJson_getTypeName_JT(TS_JsonType type);
TS_CAPI const char* TS_CCALL tsJson_getTypeName_c(TSJson self);
TS_CAPI bool_t TS_CCALL tsJson_isUnknown(TSJson self);
TS_CAPI bool_t TS_CCALL tsJson_isNull(TSJson self);
TS_CAPI bool_t TS_CCALL tsJson_isBool(TSJson self);
TS_CAPI bool_t TS_CCALL tsJson_isNumber(TSJson self);
TS_CAPI bool_t TS_CCALL tsJson_isString(TSJson self);
TS_CAPI bool_t TS_CCALL tsJson_isObject(TSJson self);
TS_CAPI bool_t TS_CCALL tsJson_isArray(TSJson self);
TS_CAPI void TS_CCALL tsJson_setData_b(TSJson self, bool_t value);
TS_CAPI void TS_CCALL tsJson_setData_iu(TSJson self, int32_t value, uint32_t radix);
TS_CAPI void TS_CCALL tsJson_setData_uu(TSJson self, uint32_t value, uint32_t radix);
TS_CAPI void TS_CCALL tsJson_setData_u64u(TSJson self, uint64_t value, uint32_t radix);
TS_CAPI void TS_CCALL tsJson_setData_fubb(TSJson self, float32_t value, uint32_t digits, bool_t compact, bool_t exponent);
TS_CAPI void TS_CCALL tsJson_setData_f64ubb(TSJson self, float64_t value, uint32_t digits, bool_t compact, bool_t exponent);
TS_CAPI void TS_CCALL tsJson_setData_s(TSJson self, const char *value);
TS_CAPI void TS_CCALL tsJson_setData_cS(TSJson self, const TSString value);
TS_CAPI TSString TS_CCALL tsJson_getData_c(TSJson self);
TS_CAPI bool_t TS_CCALL tsJson_getDataBool(TSJson self);
TS_CAPI int32_t TS_CCALL tsJson_getDatai32(TSJson self, uint32_t radix);
TS_CAPI uint32_t TS_CCALL tsJson_getDatau32(TSJson self, uint32_t radix);
TS_CAPI uint64_t TS_CCALL tsJson_getDatau64(TSJson self, uint32_t radix);
TS_CAPI float32_t TS_CCALL tsJson_getDataf32(TSJson self);
TS_CAPI float64_t TS_CCALL tsJson_getDataf64(TSJson self);
TS_CAPI TSString TS_CCALL tsJson_getNumber(TSJson self);
TS_CAPI TSString TS_CCALL tsJson_getString(TSJson self);
TS_CAPI bool_t TS_CCALL tsJson_getData_csb(TSJson self, const char *name, bool_t value);
TS_CAPI int32_t TS_CCALL tsJson_getData_csiu(TSJson self, const char *name, int32_t value, uint32_t radix);
TS_CAPI uint32_t TS_CCALL tsJson_getData_csuu(TSJson self, const char *name, uint32_t value, uint32_t radix);
TS_CAPI uint64_t TS_CCALL tsJson_getData_csu64u(TSJson self, const char *name, uint64_t value, uint32_t radix);
TS_CAPI float32_t TS_CCALL tsJson_getData_csf(TSJson self, const char *name, float32_t value);
TS_CAPI float64_t TS_CCALL tsJson_getData_csf64(TSJson self, const char *name, float64_t value);
TS_CAPI TSString TS_CCALL tsJson_getData_cscS(TSJson self, const char *name, const TSString value);
TS_CAPI void TS_CCALL tsJson_setData_spu(TSJson self, const char **values, uint32_t size);
TS_CAPI void TS_CCALL tsJson_setData_cSu(TSJson self, const TSString *values, uint32_t size);
TS_CAPI void TS_CCALL tsJson_setData_ipuu(TSJson self, const int32_t *values, uint32_t size, uint32_t radix);
TS_CAPI void TS_CCALL tsJson_setData_upuu(TSJson self, const uint32_t *values, uint32_t size, uint32_t radix);
TS_CAPI void TS_CCALL tsJson_setData_fpuubb(TSJson self, const float32_t *values, uint32_t size, uint32_t digits, bool_t compact, bool_t exponent);
TS_CAPI void TS_CCALL tsJson_setData_f64puubb(TSJson self, const float64_t *values, uint32_t size, uint32_t digits, bool_t compact, bool_t exponent);
TS_CAPI uint32_t TS_CCALL tsJson_getData_cSu(TSJson self, TSString *values, uint32_t size);
TS_CAPI uint32_t TS_CCALL tsJson_getData_ciruu(TSJson self, int32_t *values, uint32_t size, uint32_t radix);
TS_CAPI uint32_t TS_CCALL tsJson_getData_curuu(TSJson self, uint32_t *values, uint32_t size, uint32_t radix);
TS_CAPI uint32_t TS_CCALL tsJson_getData_cfru(TSJson self, float32_t *values, uint32_t size);
TS_CAPI uint32_t TS_CCALL tsJson_getData_cf64ru(TSJson self, float64_t *values, uint32_t size);

/// Tellusim::Xml
TS_CAPI TSXml TS_CCALL tsXml_new(void);
TS_CAPI TSXml TS_CCALL tsXml_new_ss(const char *name, const char *attributes);
TS_CAPI TSXml TS_CCALL tsXml_new_cSs(const TSString name, const char *attributes);
TS_CAPI TSXml TS_CCALL tsXml_new_Xss(TSXml *parent, const char *name, const char *attributes);
TS_CAPI TSXml TS_CCALL tsXml_new_XcSs(TSXml *parent, const TSString name, const char *attributes);
TS_CAPI void TS_CCALL tsXml_delete(TSXml self);
TS_CAPI bool_t TS_CCALL tsXml_equalPtr(const TSXml self, const TSXml ptr);
TS_CAPI TSXml TS_CCALL tsXml_copyPtr(const TSXml self);
TS_CAPI TSXml TS_CCALL tsXml_clonePtr(const TSXml self);
TS_CAPI void TS_CCALL tsXml_clearPtr(TSXml self);
TS_CAPI void TS_CCALL tsXml_destroyPtr(TSXml self);
TS_CAPI void TS_CCALL tsXml_acquirePtr(TSXml self);
TS_CAPI void TS_CCALL tsXml_unacquirePtr(TSXml self);
TS_CAPI bool_t TS_CCALL tsXml_isValidPtr(const TSXml self);
TS_CAPI bool_t TS_CCALL tsXml_isOwnerPtr(const TSXml self);
TS_CAPI bool_t TS_CCALL tsXml_isConstPtr(const TSXml self);
TS_CAPI uint32_t TS_CCALL tsXml_getCountPtr(const TSXml self);
TS_CAPI const void* TS_CCALL tsXml_getInternalPtr(const TSXml self);
TS_CAPI void TS_CCALL tsXml_clear(TSXml self);
TS_CAPI bool_t TS_CCALL tsXml_create_szb(TSXml self, const char *str, size_t size, bool_t owner);
TS_CAPI bool_t TS_CCALL tsXml_create_cSzb(TSXml self, const TSString str, size_t size, bool_t owner);
TS_CAPI bool_t TS_CCALL tsXml_load_s(TSXml self, const char *name);
TS_CAPI bool_t TS_CCALL tsXml_load_cS(TSXml self, const TSString name);
TS_CAPI bool_t TS_CCALL tsXml_load_St(TSXml self, TSStream stream);
TS_CAPI bool_t TS_CCALL tsXml_save_csb(TSXml self, const char *name, bool_t compact);
TS_CAPI bool_t TS_CCALL tsXml_save_ccSb(TSXml self, const TSString name, bool_t compact);
TS_CAPI bool_t TS_CCALL tsXml_save_cStb(TSXml self, TSStream stream, bool_t compact);
TS_CAPI TSXml TS_CCALL tsXml_getRoot_c(TSXml self);
TS_CAPI TSXml TS_CCALL tsXml_getRoot(TSXml self);
TS_CAPI uint32_t TS_CCALL tsXml_setParent(TSXml self, TSXml parent, bool_t check);
TS_CAPI TSXml TS_CCALL tsXml_getParent_c(TSXml self);
TS_CAPI TSXml TS_CCALL tsXml_getParent(TSXml self);
TS_CAPI TSXml TS_CCALL tsXml_addChild_sb(TSXml self, const char *name, bool_t check);
TS_CAPI uint32_t TS_CCALL tsXml_addChild_Xb(TSXml self, TSXml child, bool_t check);
TS_CAPI bool_t TS_CCALL tsXml_removeChild(TSXml self, TSXml child);
TS_CAPI void TS_CCALL tsXml_releaseChildren(TSXml self);
TS_CAPI uint32_t TS_CCALL tsXml_findChild(TSXml self, const char *name);
TS_CAPI bool_t TS_CCALL tsXml_isChild(TSXml self, const char *name);
TS_CAPI TSXml TS_CCALL tsXml_getChild_cs(TSXml self, const char *name);
TS_CAPI TSXml TS_CCALL tsXml_getChild_s(TSXml self, const char *name);
TS_CAPI uint32_t TS_CCALL tsXml_getNumChildren(TSXml self);
TS_CAPI TSXml TS_CCALL tsXml_getChild_cu(TSXml self, uint32_t index);
TS_CAPI TSXml TS_CCALL tsXml_getChild_u(TSXml self, uint32_t index);
TS_CAPI TSString TS_CCALL tsXml_getPathName(TSXml self);
TS_CAPI void TS_CCALL tsXml_setName_s(TSXml self, const char *name);
TS_CAPI void TS_CCALL tsXml_setName_cS(TSXml self, const TSString name);
TS_CAPI TSString TS_CCALL tsXml_getName(TSXml self);
TS_CAPI void TS_CCALL tsXml_setData_b(TSXml self, bool_t value);
TS_CAPI void TS_CCALL tsXml_setData_s(TSXml self, const char *value);
TS_CAPI void TS_CCALL tsXml_setData_cS(TSXml self, const TSString value);
TS_CAPI void TS_CCALL tsXml_setData_iu(TSXml self, int32_t value, uint32_t radix);
TS_CAPI void TS_CCALL tsXml_setData_uu(TSXml self, uint32_t value, uint32_t radix);
TS_CAPI void TS_CCALL tsXml_setData_u64u(TSXml self, uint64_t value, uint32_t radix);
TS_CAPI void TS_CCALL tsXml_setData_fubb(TSXml self, float32_t value, uint32_t digits, bool_t compact, bool_t exponent);
TS_CAPI void TS_CCALL tsXml_setData_f64ubb(TSXml self, float64_t value, uint32_t digits, bool_t compact, bool_t exponent);
TS_CAPI TSString TS_CCALL tsXml_getData_c(TSXml self);
TS_CAPI bool_t TS_CCALL tsXml_getDataBool(TSXml self);
TS_CAPI int32_t TS_CCALL tsXml_getDatai32(TSXml self, uint32_t radix);
TS_CAPI uint32_t TS_CCALL tsXml_getDatau32(TSXml self, uint32_t radix);
TS_CAPI uint64_t TS_CCALL tsXml_getDatau64(TSXml self, uint32_t radix);
TS_CAPI float32_t TS_CCALL tsXml_getDataf32(TSXml self);
TS_CAPI float64_t TS_CCALL tsXml_getDataf64(TSXml self);
TS_CAPI TSString TS_CCALL tsXml_getData_cscS(TSXml self, const char *name, const TSString value);
TS_CAPI bool_t TS_CCALL tsXml_getData_csb(TSXml self, const char *name, bool_t value);
TS_CAPI int32_t TS_CCALL tsXml_getData_csiu(TSXml self, const char *name, int32_t value, uint32_t radix);
TS_CAPI uint32_t TS_CCALL tsXml_getData_csuu(TSXml self, const char *name, uint32_t value, uint32_t radix);
TS_CAPI uint64_t TS_CCALL tsXml_getData_csu64u(TSXml self, const char *name, uint64_t value, uint32_t radix);
TS_CAPI float32_t TS_CCALL tsXml_getData_csf(TSXml self, const char *name, float32_t value);
TS_CAPI float64_t TS_CCALL tsXml_getData_csf64(TSXml self, const char *name, float64_t value);
TS_CAPI void TS_CCALL tsXml_setData_spuu(TSXml self, const char **values, uint32_t size, uint32_t wrap);
TS_CAPI void TS_CCALL tsXml_setData_cSuu(TSXml self, const TSString *values, uint32_t size, uint32_t wrap);
TS_CAPI void TS_CCALL tsXml_setData_ipuuu(TSXml self, const int32_t *values, uint32_t size, uint32_t radix, uint32_t wrap);
TS_CAPI void TS_CCALL tsXml_setData_upuuu(TSXml self, const uint32_t *values, uint32_t size, uint32_t radix, uint32_t wrap);
TS_CAPI void TS_CCALL tsXml_setData_fpuubbu(TSXml self, const float32_t *values, uint32_t size, uint32_t digits, bool_t compact, bool_t exponent, uint32_t wrap);
TS_CAPI void TS_CCALL tsXml_setData_f64puubbu(TSXml self, const float64_t *values, uint32_t size, uint32_t digits, bool_t compact, bool_t exponent, uint32_t wrap);
TS_CAPI uint32_t TS_CCALL tsXml_getData_cSu(TSXml self, TSString *values, uint32_t size);
TS_CAPI uint32_t TS_CCALL tsXml_getData_ciruu(TSXml self, int32_t *values, uint32_t size, uint32_t radix);
TS_CAPI uint32_t TS_CCALL tsXml_getData_curuu(TSXml self, uint32_t *values, uint32_t size, uint32_t radix);
TS_CAPI uint32_t TS_CCALL tsXml_getData_cfru(TSXml self, float32_t *values, uint32_t size);
TS_CAPI uint32_t TS_CCALL tsXml_getData_cf64ru(TSXml self, float64_t *values, uint32_t size);
TS_CAPI uint32_t TS_CCALL tsXml_addAttribute(TSXml self, const char *name);
TS_CAPI bool_t TS_CCALL tsXml_removeAttribute(TSXml self, const char *name);
TS_CAPI uint32_t TS_CCALL tsXml_findAttribute(TSXml self, const char *name);
TS_CAPI bool_t TS_CCALL tsXml_isAttribute(TSXml self, const char *name);
TS_CAPI void TS_CCALL tsXml_removeAttributes(TSXml self);
TS_CAPI uint32_t TS_CCALL tsXml_getNumAttributes(TSXml self);
TS_CAPI TSString TS_CCALL tsXml_getAttributeName(TSXml self, uint32_t index);
TS_CAPI bool_t TS_CCALL tsXml_setAttributes(TSXml self, const char *str);
TS_CAPI void TS_CCALL tsXml_setAttribute_ub(TSXml self, uint32_t index, bool_t value);
TS_CAPI void TS_CCALL tsXml_setAttribute_us(TSXml self, uint32_t index, const char *value);
TS_CAPI void TS_CCALL tsXml_setAttribute_ucS(TSXml self, uint32_t index, const TSString value);
TS_CAPI void TS_CCALL tsXml_setAttribute_uiu(TSXml self, uint32_t index, int32_t value, uint32_t radix);
TS_CAPI void TS_CCALL tsXml_setAttribute_uuu(TSXml self, uint32_t index, uint32_t value, uint32_t radix);
TS_CAPI void TS_CCALL tsXml_setAttribute_uu64u(TSXml self, uint32_t index, uint64_t value, uint32_t radix);
TS_CAPI void TS_CCALL tsXml_setAttribute_ufubb(TSXml self, uint32_t index, float32_t value, uint32_t digits, bool_t compact, bool_t exponent);
TS_CAPI void TS_CCALL tsXml_setAttribute_uf64ubb(TSXml self, uint32_t index, float64_t value, uint32_t digits, bool_t compact, bool_t exponent);
TS_CAPI TSString TS_CCALL tsXml_getAttribute_cu(TSXml self, uint32_t index);
TS_CAPI int32_t TS_CCALL tsXml_getAttributei32(TSXml self, uint32_t index, uint32_t radix);
TS_CAPI uint32_t TS_CCALL tsXml_getAttributeu32(TSXml self, uint32_t index, uint32_t radix);
TS_CAPI uint64_t TS_CCALL tsXml_getAttributeu64(TSXml self, uint32_t index, uint32_t radix);
TS_CAPI float32_t TS_CCALL tsXml_getAttributef32(TSXml self, uint32_t index);
TS_CAPI float64_t TS_CCALL tsXml_getAttributef64(TSXml self, uint32_t index);
TS_CAPI TSString TS_CCALL tsXml_getAttribute_cscS(TSXml self, const char *name, const TSString value);
TS_CAPI bool_t TS_CCALL tsXml_getAttribute_csb(TSXml self, const char *name, bool_t value);
TS_CAPI int32_t TS_CCALL tsXml_getAttribute_csiu(TSXml self, const char *name, int32_t value, uint32_t radix);
TS_CAPI uint32_t TS_CCALL tsXml_getAttribute_csuu(TSXml self, const char *name, uint32_t value, uint32_t radix);
TS_CAPI uint64_t TS_CCALL tsXml_getAttribute_csu64u(TSXml self, const char *name, uint64_t value, uint32_t radix);
TS_CAPI float32_t TS_CCALL tsXml_getAttribute_csf(TSXml self, const char *name, float32_t value);
TS_CAPI float64_t TS_CCALL tsXml_getAttribute_csf64(TSXml self, const char *name, float64_t value);
TS_CAPI void TS_CCALL tsXml_setAttribute_uspus(TSXml self, uint32_t index, const char **values, uint32_t size, const char *delimiter);
TS_CAPI void TS_CCALL tsXml_setAttribute_ucSus(TSXml self, uint32_t index, const TSString *values, uint32_t size, const char *delimiter);
TS_CAPI void TS_CCALL tsXml_setAttribute_uipuu(TSXml self, uint32_t index, const int32_t *values, uint32_t size, uint32_t radix);
TS_CAPI void TS_CCALL tsXml_setAttribute_uupuu(TSXml self, uint32_t index, const uint32_t *values, uint32_t size, uint32_t radix);
TS_CAPI void TS_CCALL tsXml_setAttribute_ufpuubb(TSXml self, uint32_t index, const float32_t *values, uint32_t size, uint32_t digits, bool_t compact, bool_t exponent);
TS_CAPI void TS_CCALL tsXml_setAttribute_uf64puubb(TSXml self, uint32_t index, const float64_t *values, uint32_t size, uint32_t digits, bool_t compact, bool_t exponent);
TS_CAPI uint32_t TS_CCALL tsXml_getAttribute_cuSus(TSXml self, uint32_t index, TSString *values, uint32_t size, const char *delimiter);
TS_CAPI uint32_t TS_CCALL tsXml_getAttribute_cuiruu(TSXml self, uint32_t index, int32_t *values, uint32_t size, uint32_t radix);
TS_CAPI uint32_t TS_CCALL tsXml_getAttribute_cuuruu(TSXml self, uint32_t index, uint32_t *values, uint32_t size, uint32_t radix);
TS_CAPI uint32_t TS_CCALL tsXml_getAttribute_cufru(TSXml self, uint32_t index, float32_t *values, uint32_t size);
TS_CAPI uint32_t TS_CCALL tsXml_getAttribute_cuf64ru(TSXml self, uint32_t index, float64_t *values, uint32_t size);

/// Tellusim::Buffer
TS_CAPI TSBuffer TS_CCALL tsBuffer_new(void);
TS_CAPI void TS_CCALL tsBuffer_delete(TSBuffer self);
TS_CAPI bool_t TS_CCALL tsBuffer_equalPtr(const TSBuffer self, const TSBuffer ptr);
TS_CAPI TSBuffer TS_CCALL tsBuffer_copyPtr(const TSBuffer self);
TS_CAPI TSBuffer TS_CCALL tsBuffer_clonePtr(const TSBuffer self);
TS_CAPI void TS_CCALL tsBuffer_clearPtr(TSBuffer self);
TS_CAPI void TS_CCALL tsBuffer_destroyPtr(TSBuffer self);
TS_CAPI void TS_CCALL tsBuffer_acquirePtr(TSBuffer self);
TS_CAPI void TS_CCALL tsBuffer_unacquirePtr(TSBuffer self);
TS_CAPI bool_t TS_CCALL tsBuffer_isValidPtr(const TSBuffer self);
TS_CAPI bool_t TS_CCALL tsBuffer_isOwnerPtr(const TSBuffer self);
TS_CAPI bool_t TS_CCALL tsBuffer_isConstPtr(const TSBuffer self);
TS_CAPI uint32_t TS_CCALL tsBuffer_getCountPtr(const TSBuffer self);
TS_CAPI const void* TS_CCALL tsBuffer_getInternalPtr(const TSBuffer self);
TS_CAPI TS_Platform TS_CCALL tsBuffer_getPlatform(TSBuffer self);
TS_CAPI const char* TS_CCALL tsBuffer_getPlatformName(TSBuffer self);
TS_CAPI uint32_t TS_CCALL tsBuffer_getIndex(TSBuffer self);
TS_CAPI void TS_CCALL tsBuffer_clear(TSBuffer self);
TS_CAPI bool_t TS_CCALL tsBuffer_isCreated(TSBuffer self);
TS_CAPI void TS_CCALL tsBuffer_setName(TSBuffer self, const char *name);
TS_CAPI TSString TS_CCALL tsBuffer_getName(TSBuffer self);
TS_CAPI bool_t TS_CCALL tsBuffer_create(TSBuffer self, TS_BufferFlags flags, size_t size, TS_Format format);
TS_CAPI bool_t TS_CCALL tsBuffer_isMapped(TSBuffer self);
TS_CAPI TS_BufferFlags TS_CCALL tsBuffer_getFlags(TSBuffer self);
TS_CAPI bool_t TS_CCALL tsBuffer_hasFlag(TSBuffer self, TS_BufferFlags flags);
TS_CAPI bool_t TS_CCALL tsBuffer_hasFlags(TSBuffer self, TS_BufferFlags flags);
TS_CAPI TSString TS_CCALL tsBuffer_getFlagsName(TSBuffer self);
TS_CAPI TS_Format TS_CCALL tsBuffer_getFormat(TSBuffer self);
TS_CAPI const char* TS_CCALL tsBuffer_getFormatName(TSBuffer self);
TS_CAPI uint32_t TS_CCALL tsBuffer_getComponents(TSBuffer self);
TS_CAPI uint32_t TS_CCALL tsBuffer_getPixelSize(TSBuffer self);
TS_CAPI size_t TS_CCALL tsBuffer_getSize(TSBuffer self);
TS_CAPI size_t TS_CCALL tsBuffer_getPageSize(TSBuffer self);
TS_CAPI TSString TS_CCALL tsBuffer_getDescription(TSBuffer self);

/// Tellusim::BufferTable
TS_CAPI TSBufferTable TS_CCALL tsBufferTable_new(void);
TS_CAPI void TS_CCALL tsBufferTable_delete(TSBufferTable self);
TS_CAPI bool_t TS_CCALL tsBufferTable_equalPtr(const TSBufferTable self, const TSBufferTable ptr);
TS_CAPI TSBufferTable TS_CCALL tsBufferTable_copyPtr(const TSBufferTable self);
TS_CAPI TSBufferTable TS_CCALL tsBufferTable_clonePtr(const TSBufferTable self);
TS_CAPI void TS_CCALL tsBufferTable_clearPtr(TSBufferTable self);
TS_CAPI void TS_CCALL tsBufferTable_destroyPtr(TSBufferTable self);
TS_CAPI void TS_CCALL tsBufferTable_acquirePtr(TSBufferTable self);
TS_CAPI void TS_CCALL tsBufferTable_unacquirePtr(TSBufferTable self);
TS_CAPI bool_t TS_CCALL tsBufferTable_isValidPtr(const TSBufferTable self);
TS_CAPI bool_t TS_CCALL tsBufferTable_isOwnerPtr(const TSBufferTable self);
TS_CAPI bool_t TS_CCALL tsBufferTable_isConstPtr(const TSBufferTable self);
TS_CAPI uint32_t TS_CCALL tsBufferTable_getCountPtr(const TSBufferTable self);
TS_CAPI const void* TS_CCALL tsBufferTable_getInternalPtr(const TSBufferTable self);
TS_CAPI TS_Platform TS_CCALL tsBufferTable_getPlatform(TSBufferTable self);
TS_CAPI const char* TS_CCALL tsBufferTable_getPlatformName(TSBufferTable self);
TS_CAPI uint32_t TS_CCALL tsBufferTable_getIndex(TSBufferTable self);
TS_CAPI void TS_CCALL tsBufferTable_clear(TSBufferTable self);
TS_CAPI bool_t TS_CCALL tsBufferTable_isCreated(TSBufferTable self);
TS_CAPI void TS_CCALL tsBufferTable_setName(TSBufferTable self, const char *name);
TS_CAPI TSString TS_CCALL tsBufferTable_getName(TSBufferTable self);
TS_CAPI bool_t TS_CCALL tsBufferTable_create(TSBufferTable self, uint32_t size);
TS_CAPI uint32_t TS_CCALL tsBufferTable_getSize(TSBufferTable self);
TS_CAPI TSBuffer TS_CCALL tsBufferTable_get(TSBufferTable self, uint32_t index);
TS_CAPI bool_t TS_CCALL tsBufferTable_isOwner(TSBufferTable self, uint32_t index);
TS_CAPI size_t TS_CCALL tsBufferTable_getMemory(TSBufferTable self);

/// Tellusim::D3D12Buffer
TS_CAPI TSD3D12Buffer TS_CCALL tsD3D12Buffer_new(void);
TS_CAPI void TS_CCALL tsD3D12Buffer_delete(TSD3D12Buffer self);
TS_CAPI bool_t TS_CCALL tsD3D12Buffer_equalPtr(const TSD3D12Buffer self, const TSD3D12Buffer ptr);
TS_CAPI TSD3D12Buffer TS_CCALL tsD3D12Buffer_copyPtr(const TSD3D12Buffer self);
TS_CAPI TSD3D12Buffer TS_CCALL tsD3D12Buffer_clonePtr(const TSD3D12Buffer self);
TS_CAPI void TS_CCALL tsD3D12Buffer_clearPtr(TSD3D12Buffer self);
TS_CAPI void TS_CCALL tsD3D12Buffer_destroyPtr(TSD3D12Buffer self);
TS_CAPI void TS_CCALL tsD3D12Buffer_acquirePtr(TSD3D12Buffer self);
TS_CAPI void TS_CCALL tsD3D12Buffer_unacquirePtr(TSD3D12Buffer self);
TS_CAPI bool_t TS_CCALL tsD3D12Buffer_isValidPtr(const TSD3D12Buffer self);
TS_CAPI bool_t TS_CCALL tsD3D12Buffer_isOwnerPtr(const TSD3D12Buffer self);
TS_CAPI bool_t TS_CCALL tsD3D12Buffer_isConstPtr(const TSD3D12Buffer self);
TS_CAPI uint32_t TS_CCALL tsD3D12Buffer_getCountPtr(const TSD3D12Buffer self);
TS_CAPI const void* TS_CCALL tsD3D12Buffer_getInternalPtr(const TSD3D12Buffer self);
TS_CAPI bool_t TS_CCALL tsD3D12Buffer_equalBufferPtr(const TSD3D12Buffer self, const TSBuffer base);
TS_CAPI TSD3D12Buffer TS_CCALL tsD3D12Buffer_castBufferPtr(TSBuffer base);
TS_CAPI TSBuffer TS_CCALL tsD3D12Buffer_baseBufferPtr(TSD3D12Buffer self);
TS_CAPI bool_t TS_CCALL tsD3D12Buffer_create(TSD3D12Buffer self, TS_BufferFlags flags, ID3D12Resource *buffer, uint32_t state);
TS_CAPI ID3D12Resource* TS_CCALL tsD3D12Buffer_getD3D12Buffer(TSD3D12Buffer self);
TS_CAPI size_t TS_CCALL tsD3D12Buffer_getUnorderedAccessView(TSD3D12Buffer self);
TS_CAPI size_t TS_CCALL tsD3D12Buffer_getShaderResourceView(TSD3D12Buffer self);
TS_CAPI uint64_t TS_CCALL tsD3D12Buffer_getBufferAddress(TSD3D12Buffer self);
TS_CAPI void TS_CCALL tsD3D12Buffer_setBufferState(TSD3D12Buffer self, uint32_t state);
TS_CAPI uint32_t TS_CCALL tsD3D12Buffer_getBufferState(TSD3D12Buffer self);
TS_CAPI void* TS_CCALL tsD3D12Buffer_getSharedHandle(TSD3D12Buffer self);
TS_CAPI void* TS_CCALL tsD3D12Buffer_getInteropHandle(TSD3D12Buffer self);

/// Tellusim::D3D11Buffer
TS_CAPI TSD3D11Buffer TS_CCALL tsD3D11Buffer_new(void);
TS_CAPI void TS_CCALL tsD3D11Buffer_delete(TSD3D11Buffer self);
TS_CAPI bool_t TS_CCALL tsD3D11Buffer_equalPtr(const TSD3D11Buffer self, const TSD3D11Buffer ptr);
TS_CAPI TSD3D11Buffer TS_CCALL tsD3D11Buffer_copyPtr(const TSD3D11Buffer self);
TS_CAPI TSD3D11Buffer TS_CCALL tsD3D11Buffer_clonePtr(const TSD3D11Buffer self);
TS_CAPI void TS_CCALL tsD3D11Buffer_clearPtr(TSD3D11Buffer self);
TS_CAPI void TS_CCALL tsD3D11Buffer_destroyPtr(TSD3D11Buffer self);
TS_CAPI void TS_CCALL tsD3D11Buffer_acquirePtr(TSD3D11Buffer self);
TS_CAPI void TS_CCALL tsD3D11Buffer_unacquirePtr(TSD3D11Buffer self);
TS_CAPI bool_t TS_CCALL tsD3D11Buffer_isValidPtr(const TSD3D11Buffer self);
TS_CAPI bool_t TS_CCALL tsD3D11Buffer_isOwnerPtr(const TSD3D11Buffer self);
TS_CAPI bool_t TS_CCALL tsD3D11Buffer_isConstPtr(const TSD3D11Buffer self);
TS_CAPI uint32_t TS_CCALL tsD3D11Buffer_getCountPtr(const TSD3D11Buffer self);
TS_CAPI const void* TS_CCALL tsD3D11Buffer_getInternalPtr(const TSD3D11Buffer self);
TS_CAPI bool_t TS_CCALL tsD3D11Buffer_equalBufferPtr(const TSD3D11Buffer self, const TSBuffer base);
TS_CAPI TSD3D11Buffer TS_CCALL tsD3D11Buffer_castBufferPtr(TSBuffer base);
TS_CAPI TSBuffer TS_CCALL tsD3D11Buffer_baseBufferPtr(TSD3D11Buffer self);
TS_CAPI bool_t TS_CCALL tsD3D11Buffer_create(TSD3D11Buffer self, TS_BufferFlags flags, ID3D11Buffer *buffer);
TS_CAPI ID3D11Buffer* TS_CCALL tsD3D11Buffer_getD3D11Buffer(TSD3D11Buffer self);
TS_CAPI ID3D11UnorderedAccessView* TS_CCALL tsD3D11Buffer_getUnorderedAccessView(TSD3D11Buffer self);
TS_CAPI ID3D11ShaderResourceView* TS_CCALL tsD3D11Buffer_getShaderResourceView(TSD3D11Buffer self);
TS_CAPI void* TS_CCALL tsD3D11Buffer_getInteropHandle(TSD3D11Buffer self);

/// Tellusim::MTLBuffer
TS_CAPI TSMTLBuffer TS_CCALL tsMTLBuffer_new(void);
TS_CAPI void TS_CCALL tsMTLBuffer_delete(TSMTLBuffer self);
TS_CAPI bool_t TS_CCALL tsMTLBuffer_equalPtr(const TSMTLBuffer self, const TSMTLBuffer ptr);
TS_CAPI TSMTLBuffer TS_CCALL tsMTLBuffer_copyPtr(const TSMTLBuffer self);
TS_CAPI TSMTLBuffer TS_CCALL tsMTLBuffer_clonePtr(const TSMTLBuffer self);
TS_CAPI void TS_CCALL tsMTLBuffer_clearPtr(TSMTLBuffer self);
TS_CAPI void TS_CCALL tsMTLBuffer_destroyPtr(TSMTLBuffer self);
TS_CAPI void TS_CCALL tsMTLBuffer_acquirePtr(TSMTLBuffer self);
TS_CAPI void TS_CCALL tsMTLBuffer_unacquirePtr(TSMTLBuffer self);
TS_CAPI bool_t TS_CCALL tsMTLBuffer_isValidPtr(const TSMTLBuffer self);
TS_CAPI bool_t TS_CCALL tsMTLBuffer_isOwnerPtr(const TSMTLBuffer self);
TS_CAPI bool_t TS_CCALL tsMTLBuffer_isConstPtr(const TSMTLBuffer self);
TS_CAPI uint32_t TS_CCALL tsMTLBuffer_getCountPtr(const TSMTLBuffer self);
TS_CAPI const void* TS_CCALL tsMTLBuffer_getInternalPtr(const TSMTLBuffer self);
TS_CAPI bool_t TS_CCALL tsMTLBuffer_equalBufferPtr(const TSMTLBuffer self, const TSBuffer base);
TS_CAPI TSMTLBuffer TS_CCALL tsMTLBuffer_castBufferPtr(TSBuffer base);
TS_CAPI TSBuffer TS_CCALL tsMTLBuffer_baseBufferPtr(TSMTLBuffer self);
TS_CAPI bool_t TS_CCALL tsMTLBuffer_create(TSMTLBuffer self, TS_BufferFlags flags, void *buffer);
TS_CAPI void* TS_CCALL tsMTLBuffer_getMTLBuffer(TSMTLBuffer self);
TS_CAPI void* TS_CCALL tsMTLBuffer_getSharedPtr(TSMTLBuffer self);

/// Tellusim::VKBuffer
TS_CAPI TSVKBuffer TS_CCALL tsVKBuffer_new(void);
TS_CAPI void TS_CCALL tsVKBuffer_delete(TSVKBuffer self);
TS_CAPI bool_t TS_CCALL tsVKBuffer_equalPtr(const TSVKBuffer self, const TSVKBuffer ptr);
TS_CAPI TSVKBuffer TS_CCALL tsVKBuffer_copyPtr(const TSVKBuffer self);
TS_CAPI TSVKBuffer TS_CCALL tsVKBuffer_clonePtr(const TSVKBuffer self);
TS_CAPI void TS_CCALL tsVKBuffer_clearPtr(TSVKBuffer self);
TS_CAPI void TS_CCALL tsVKBuffer_destroyPtr(TSVKBuffer self);
TS_CAPI void TS_CCALL tsVKBuffer_acquirePtr(TSVKBuffer self);
TS_CAPI void TS_CCALL tsVKBuffer_unacquirePtr(TSVKBuffer self);
TS_CAPI bool_t TS_CCALL tsVKBuffer_isValidPtr(const TSVKBuffer self);
TS_CAPI bool_t TS_CCALL tsVKBuffer_isOwnerPtr(const TSVKBuffer self);
TS_CAPI bool_t TS_CCALL tsVKBuffer_isConstPtr(const TSVKBuffer self);
TS_CAPI uint32_t TS_CCALL tsVKBuffer_getCountPtr(const TSVKBuffer self);
TS_CAPI const void* TS_CCALL tsVKBuffer_getInternalPtr(const TSVKBuffer self);
TS_CAPI bool_t TS_CCALL tsVKBuffer_equalBufferPtr(const TSVKBuffer self, const TSBuffer base);
TS_CAPI TSVKBuffer TS_CCALL tsVKBuffer_castBufferPtr(TSBuffer base);
TS_CAPI TSBuffer TS_CCALL tsVKBuffer_baseBufferPtr(TSVKBuffer self);
TS_CAPI bool_t TS_CCALL tsVKBuffer_create(TSVKBuffer self, TS_BufferFlags flags, size_t size, VkBuffer buffer, uint32_t access);
TS_CAPI VkBuffer TS_CCALL tsVKBuffer_getVKBuffer(TSVKBuffer self);
TS_CAPI VkBufferView TS_CCALL tsVKBuffer_getBufferView(TSVKBuffer self);
TS_CAPI uint64_t TS_CCALL tsVKBuffer_getBufferAddress(TSVKBuffer self);
TS_CAPI void TS_CCALL tsVKBuffer_setBufferAccess(TSVKBuffer self, uint32_t access);
TS_CAPI uint32_t TS_CCALL tsVKBuffer_getBufferAccess(TSVKBuffer self);
TS_CAPI void* TS_CCALL tsVKBuffer_getSharedPtr(TSVKBuffer self);
TS_CAPI void* TS_CCALL tsVKBuffer_getInteropHandle(TSVKBuffer self);

/// Tellusim::GLBuffer
TS_CAPI TSGLBuffer TS_CCALL tsGLBuffer_new(void);
TS_CAPI void TS_CCALL tsGLBuffer_delete(TSGLBuffer self);
TS_CAPI bool_t TS_CCALL tsGLBuffer_equalPtr(const TSGLBuffer self, const TSGLBuffer ptr);
TS_CAPI TSGLBuffer TS_CCALL tsGLBuffer_copyPtr(const TSGLBuffer self);
TS_CAPI TSGLBuffer TS_CCALL tsGLBuffer_clonePtr(const TSGLBuffer self);
TS_CAPI void TS_CCALL tsGLBuffer_clearPtr(TSGLBuffer self);
TS_CAPI void TS_CCALL tsGLBuffer_destroyPtr(TSGLBuffer self);
TS_CAPI void TS_CCALL tsGLBuffer_acquirePtr(TSGLBuffer self);
TS_CAPI void TS_CCALL tsGLBuffer_unacquirePtr(TSGLBuffer self);
TS_CAPI bool_t TS_CCALL tsGLBuffer_isValidPtr(const TSGLBuffer self);
TS_CAPI bool_t TS_CCALL tsGLBuffer_isOwnerPtr(const TSGLBuffer self);
TS_CAPI bool_t TS_CCALL tsGLBuffer_isConstPtr(const TSGLBuffer self);
TS_CAPI uint32_t TS_CCALL tsGLBuffer_getCountPtr(const TSGLBuffer self);
TS_CAPI const void* TS_CCALL tsGLBuffer_getInternalPtr(const TSGLBuffer self);
TS_CAPI bool_t TS_CCALL tsGLBuffer_equalBufferPtr(const TSGLBuffer self, const TSBuffer base);
TS_CAPI TSGLBuffer TS_CCALL tsGLBuffer_castBufferPtr(TSBuffer base);
TS_CAPI TSBuffer TS_CCALL tsGLBuffer_baseBufferPtr(TSGLBuffer self);
TS_CAPI bool_t TS_CCALL tsGLBuffer_create(TSGLBuffer self, TS_BufferFlags flags, uint32_t target, uint32_t buffer_id);
TS_CAPI uint32_t TS_CCALL tsGLBuffer_getTarget(TSGLBuffer self);
TS_CAPI uint32_t TS_CCALL tsGLBuffer_getBufferID(TSGLBuffer self);

/// Tellusim::GLESBuffer
TS_CAPI TSGLESBuffer TS_CCALL tsGLESBuffer_new(void);
TS_CAPI void TS_CCALL tsGLESBuffer_delete(TSGLESBuffer self);
TS_CAPI bool_t TS_CCALL tsGLESBuffer_equalPtr(const TSGLESBuffer self, const TSGLESBuffer ptr);
TS_CAPI TSGLESBuffer TS_CCALL tsGLESBuffer_copyPtr(const TSGLESBuffer self);
TS_CAPI TSGLESBuffer TS_CCALL tsGLESBuffer_clonePtr(const TSGLESBuffer self);
TS_CAPI void TS_CCALL tsGLESBuffer_clearPtr(TSGLESBuffer self);
TS_CAPI void TS_CCALL tsGLESBuffer_destroyPtr(TSGLESBuffer self);
TS_CAPI void TS_CCALL tsGLESBuffer_acquirePtr(TSGLESBuffer self);
TS_CAPI void TS_CCALL tsGLESBuffer_unacquirePtr(TSGLESBuffer self);
TS_CAPI bool_t TS_CCALL tsGLESBuffer_isValidPtr(const TSGLESBuffer self);
TS_CAPI bool_t TS_CCALL tsGLESBuffer_isOwnerPtr(const TSGLESBuffer self);
TS_CAPI bool_t TS_CCALL tsGLESBuffer_isConstPtr(const TSGLESBuffer self);
TS_CAPI uint32_t TS_CCALL tsGLESBuffer_getCountPtr(const TSGLESBuffer self);
TS_CAPI const void* TS_CCALL tsGLESBuffer_getInternalPtr(const TSGLESBuffer self);
TS_CAPI bool_t TS_CCALL tsGLESBuffer_equalBufferPtr(const TSGLESBuffer self, const TSBuffer base);
TS_CAPI TSGLESBuffer TS_CCALL tsGLESBuffer_castBufferPtr(TSBuffer base);
TS_CAPI TSBuffer TS_CCALL tsGLESBuffer_baseBufferPtr(TSGLESBuffer self);
TS_CAPI bool_t TS_CCALL tsGLESBuffer_create(TSGLESBuffer self, TS_BufferFlags flags, uint32_t target, uint32_t buffer_id);
TS_CAPI uint32_t TS_CCALL tsGLESBuffer_getTarget(TSGLESBuffer self);
TS_CAPI uint32_t TS_CCALL tsGLESBuffer_getBufferID(TSGLESBuffer self);

/// Tellusim::CUBuffer
TS_CAPI TSCUBuffer TS_CCALL tsCUBuffer_new(void);
TS_CAPI void TS_CCALL tsCUBuffer_delete(TSCUBuffer self);
TS_CAPI bool_t TS_CCALL tsCUBuffer_equalPtr(const TSCUBuffer self, const TSCUBuffer ptr);
TS_CAPI TSCUBuffer TS_CCALL tsCUBuffer_copyPtr(const TSCUBuffer self);
TS_CAPI TSCUBuffer TS_CCALL tsCUBuffer_clonePtr(const TSCUBuffer self);
TS_CAPI void TS_CCALL tsCUBuffer_clearPtr(TSCUBuffer self);
TS_CAPI void TS_CCALL tsCUBuffer_destroyPtr(TSCUBuffer self);
TS_CAPI void TS_CCALL tsCUBuffer_acquirePtr(TSCUBuffer self);
TS_CAPI void TS_CCALL tsCUBuffer_unacquirePtr(TSCUBuffer self);
TS_CAPI bool_t TS_CCALL tsCUBuffer_isValidPtr(const TSCUBuffer self);
TS_CAPI bool_t TS_CCALL tsCUBuffer_isOwnerPtr(const TSCUBuffer self);
TS_CAPI bool_t TS_CCALL tsCUBuffer_isConstPtr(const TSCUBuffer self);
TS_CAPI uint32_t TS_CCALL tsCUBuffer_getCountPtr(const TSCUBuffer self);
TS_CAPI const void* TS_CCALL tsCUBuffer_getInternalPtr(const TSCUBuffer self);
TS_CAPI bool_t TS_CCALL tsCUBuffer_equalBufferPtr(const TSCUBuffer self, const TSBuffer base);
TS_CAPI TSCUBuffer TS_CCALL tsCUBuffer_castBufferPtr(TSBuffer base);
TS_CAPI TSBuffer TS_CCALL tsCUBuffer_baseBufferPtr(TSCUBuffer self);
TS_CAPI size_t TS_CCALL tsCUBuffer_getBufferPtr(TSCUBuffer self);
TS_CAPI uint8_t* TS_CCALL tsCUBuffer_getBufferData(TSCUBuffer self);
TS_CAPI CUevent TS_CCALL tsCUBuffer_getBufferEvent(TSCUBuffer self);
TS_CAPI uint32_t TS_CCALL tsCUBuffer_getArrayFormat(TSCUBuffer self);
TS_CAPI uint32_t TS_CCALL tsCUBuffer_getArrayChannels(TSCUBuffer self);
TS_CAPI CUexternalMemory TS_CCALL tsCUBuffer_getSharedMemory(TSCUBuffer self);

/// Tellusim::HIPBuffer
TS_CAPI TSHIPBuffer TS_CCALL tsHIPBuffer_new(void);
TS_CAPI void TS_CCALL tsHIPBuffer_delete(TSHIPBuffer self);
TS_CAPI bool_t TS_CCALL tsHIPBuffer_equalPtr(const TSHIPBuffer self, const TSHIPBuffer ptr);
TS_CAPI TSHIPBuffer TS_CCALL tsHIPBuffer_copyPtr(const TSHIPBuffer self);
TS_CAPI TSHIPBuffer TS_CCALL tsHIPBuffer_clonePtr(const TSHIPBuffer self);
TS_CAPI void TS_CCALL tsHIPBuffer_clearPtr(TSHIPBuffer self);
TS_CAPI void TS_CCALL tsHIPBuffer_destroyPtr(TSHIPBuffer self);
TS_CAPI void TS_CCALL tsHIPBuffer_acquirePtr(TSHIPBuffer self);
TS_CAPI void TS_CCALL tsHIPBuffer_unacquirePtr(TSHIPBuffer self);
TS_CAPI bool_t TS_CCALL tsHIPBuffer_isValidPtr(const TSHIPBuffer self);
TS_CAPI bool_t TS_CCALL tsHIPBuffer_isOwnerPtr(const TSHIPBuffer self);
TS_CAPI bool_t TS_CCALL tsHIPBuffer_isConstPtr(const TSHIPBuffer self);
TS_CAPI uint32_t TS_CCALL tsHIPBuffer_getCountPtr(const TSHIPBuffer self);
TS_CAPI const void* TS_CCALL tsHIPBuffer_getInternalPtr(const TSHIPBuffer self);
TS_CAPI bool_t TS_CCALL tsHIPBuffer_equalBufferPtr(const TSHIPBuffer self, const TSBuffer base);
TS_CAPI TSHIPBuffer TS_CCALL tsHIPBuffer_castBufferPtr(TSBuffer base);
TS_CAPI TSBuffer TS_CCALL tsHIPBuffer_baseBufferPtr(TSHIPBuffer self);
TS_CAPI void* TS_CCALL tsHIPBuffer_getBufferPtr(TSHIPBuffer self);
TS_CAPI uint8_t* TS_CCALL tsHIPBuffer_getBufferData(TSHIPBuffer self);
TS_CAPI void* TS_CCALL tsHIPBuffer_getBufferEvent(TSHIPBuffer self);
TS_CAPI uint32_t TS_CCALL tsHIPBuffer_getArrayFormat(TSHIPBuffer self);
TS_CAPI uint32_t TS_CCALL tsHIPBuffer_getArrayChannels(TSHIPBuffer self);
TS_CAPI void* TS_CCALL tsHIPBuffer_getSharedMemory(TSHIPBuffer self);

/// Tellusim::FUBuffer
TS_CAPI TSFUBuffer TS_CCALL tsFUBuffer_new(void);
TS_CAPI TSFUBuffer TS_CCALL tsFUBuffer_new_cABb(const TSBuffer *buffers, uint32_t buffers_size, bool_t owner);
TS_CAPI void TS_CCALL tsFUBuffer_delete(TSFUBuffer self);
TS_CAPI bool_t TS_CCALL tsFUBuffer_equalPtr(const TSFUBuffer self, const TSFUBuffer ptr);
TS_CAPI TSFUBuffer TS_CCALL tsFUBuffer_copyPtr(const TSFUBuffer self);
TS_CAPI TSFUBuffer TS_CCALL tsFUBuffer_clonePtr(const TSFUBuffer self);
TS_CAPI void TS_CCALL tsFUBuffer_clearPtr(TSFUBuffer self);
TS_CAPI void TS_CCALL tsFUBuffer_destroyPtr(TSFUBuffer self);
TS_CAPI void TS_CCALL tsFUBuffer_acquirePtr(TSFUBuffer self);
TS_CAPI void TS_CCALL tsFUBuffer_unacquirePtr(TSFUBuffer self);
TS_CAPI bool_t TS_CCALL tsFUBuffer_isValidPtr(const TSFUBuffer self);
TS_CAPI bool_t TS_CCALL tsFUBuffer_isOwnerPtr(const TSFUBuffer self);
TS_CAPI bool_t TS_CCALL tsFUBuffer_isConstPtr(const TSFUBuffer self);
TS_CAPI uint32_t TS_CCALL tsFUBuffer_getCountPtr(const TSFUBuffer self);
TS_CAPI const void* TS_CCALL tsFUBuffer_getInternalPtr(const TSFUBuffer self);
TS_CAPI bool_t TS_CCALL tsFUBuffer_equalBufferPtr(const TSFUBuffer self, const TSBuffer base);
TS_CAPI TSFUBuffer TS_CCALL tsFUBuffer_castBufferPtr(TSBuffer base);
TS_CAPI TSBuffer TS_CCALL tsFUBuffer_baseBufferPtr(TSFUBuffer self);
TS_CAPI void TS_CCALL tsFUBuffer_setMask(TSFUBuffer self, uint32_t mask);
TS_CAPI uint32_t TS_CCALL tsFUBuffer_getMask(TSFUBuffer self);
TS_CAPI uint32_t TS_CCALL tsFUBuffer_getNumBuffers(TSFUBuffer self);
TS_CAPI TSBuffer TS_CCALL tsFUBuffer_getBuffer_cu(TSFUBuffer self, uint32_t index);
TS_CAPI TSBuffer TS_CCALL tsFUBuffer_getBuffer_u(TSFUBuffer self, uint32_t index);

/// Tellusim::Command
TS_CAPI TSCommand TS_CCALL tsCommand_new(void);
TS_CAPI void TS_CCALL tsCommand_delete(TSCommand self);
TS_CAPI bool_t TS_CCALL tsCommand_equalPtr(const TSCommand self, const TSCommand ptr);
TS_CAPI TSCommand TS_CCALL tsCommand_copyPtr(const TSCommand self);
TS_CAPI TSCommand TS_CCALL tsCommand_clonePtr(const TSCommand self);
TS_CAPI void TS_CCALL tsCommand_clearPtr(TSCommand self);
TS_CAPI void TS_CCALL tsCommand_destroyPtr(TSCommand self);
TS_CAPI void TS_CCALL tsCommand_acquirePtr(TSCommand self);
TS_CAPI void TS_CCALL tsCommand_unacquirePtr(TSCommand self);
TS_CAPI bool_t TS_CCALL tsCommand_isValidPtr(const TSCommand self);
TS_CAPI bool_t TS_CCALL tsCommand_isOwnerPtr(const TSCommand self);
TS_CAPI bool_t TS_CCALL tsCommand_isConstPtr(const TSCommand self);
TS_CAPI uint32_t TS_CCALL tsCommand_getCountPtr(const TSCommand self);
TS_CAPI const void* TS_CCALL tsCommand_getInternalPtr(const TSCommand self);
TS_CAPI TS_Platform TS_CCALL tsCommand_getPlatform(TSCommand self);
TS_CAPI const char* TS_CCALL tsCommand_getPlatformName(TSCommand self);
TS_CAPI uint32_t TS_CCALL tsCommand_getIndex(TSCommand self);
TS_CAPI void TS_CCALL tsCommand_setPipeline(TSCommand self, TSPipeline pipeline);
TS_CAPI TSPipeline TS_CCALL tsCommand_getPipeline(TSCommand self);
TS_CAPI void TS_CCALL tsCommand_setViewport(TSCommand self, uint32_t index, const TSViewport *viewport);
TS_CAPI void TS_CCALL tsCommand_setViewports(TSCommand self, const TSViewport *viewports, uint32_t num_viewports);
TS_CAPI void TS_CCALL tsCommand_setScissor(TSCommand self, uint32_t index, const TSScissor *scissor);
TS_CAPI void TS_CCALL tsCommand_setScissors(TSCommand self, const TSScissor *scissors, uint32_t num_scissors);
TS_CAPI void TS_CCALL tsCommand_setSampler(TSCommand self, uint32_t index, TSSampler sampler);
TS_CAPI void TS_CCALL tsCommand_setSamplers_ucAS(TSCommand self, uint32_t index, const TSSampler *samplers, uint32_t samplers_size);
TS_CAPI void TS_CCALL tsCommand_setTexture_uT(TSCommand self, uint32_t index, TSTexture texture);
TS_CAPI void TS_CCALL tsCommand_setTexture_uTcS(TSCommand self, uint32_t index, TSTexture texture, const TSSlice *slice);
TS_CAPI void TS_CCALL tsCommand_setTextures_ucAT(TSCommand self, uint32_t index, const TSTexture *textures, uint32_t textures_size);
TS_CAPI void TS_CCALL tsCommand_setSurfaceTexture_uT(TSCommand self, uint32_t index, TSTexture texture);
TS_CAPI void TS_CCALL tsCommand_setSurfaceTexture_uTcSF(TSCommand self, uint32_t index, TSTexture texture, const TSSlice *slice, TS_Format format);
TS_CAPI void TS_CCALL tsCommand_setSurfaceTextures_ucAT(TSCommand self, uint32_t index, const TSTexture *textures, uint32_t textures_size);
TS_CAPI void* TS_CCALL tsCommand_getUniformData(TSCommand self, uint32_t index, size_t size);
TS_CAPI void TS_CCALL tsCommand_setUniformData(TSCommand self, uint32_t index, const void *src, size_t size);
TS_CAPI void TS_CCALL tsCommand_setUniformBuffer(TSCommand self, uint32_t index, TSBuffer buffer, size_t offset, size_t size);
TS_CAPI void TS_CCALL tsCommand_setUniformOffset(TSCommand self, uint32_t index, size_t offset, bool_t relative);
TS_CAPI void TS_CCALL tsCommand_setUniformBuffers_ucAB(TSCommand self, uint32_t index, const TSBuffer *buffers, uint32_t buffers_size);
TS_CAPI void TS_CCALL tsCommand_setUniformBuffers_ucABcA(TSCommand self, uint32_t index, const TSBuffer *buffers, uint32_t buffers_size, const size_t *offsets, uint32_t offsets_size);
TS_CAPI void* TS_CCALL tsCommand_getStorageData(TSCommand self, uint32_t index, size_t size);
TS_CAPI void TS_CCALL tsCommand_setStorageData(TSCommand self, uint32_t index, const void *src, size_t size);
TS_CAPI void TS_CCALL tsCommand_setStorageBuffer(TSCommand self, uint32_t index, TSBuffer buffer, size_t offset, size_t size);
TS_CAPI void TS_CCALL tsCommand_setStorageOffset(TSCommand self, uint32_t index, size_t offset, bool_t relative);
TS_CAPI void TS_CCALL tsCommand_setStorageBuffers_ucAB(TSCommand self, uint32_t index, const TSBuffer *buffers, uint32_t buffers_size);
TS_CAPI void TS_CCALL tsCommand_setStorageBuffers_ucABcA(TSCommand self, uint32_t index, const TSBuffer *buffers, uint32_t buffers_size, const size_t *offsets, uint32_t offsets_size);
TS_CAPI void TS_CCALL tsCommand_setTracing(TSCommand self, uint32_t index, TSTracing tracing);
TS_CAPI void TS_CCALL tsCommand_setTracings_ucAT(TSCommand self, uint32_t index, const TSTracing *tracings, uint32_t tracings_size);
TS_CAPI void TS_CCALL tsCommand_setTexelBuffer(TSCommand self, uint32_t index, TSBuffer buffer);
TS_CAPI void TS_CCALL tsCommand_setTexelBuffers_ucAB(TSCommand self, uint32_t index, const TSBuffer *buffers, uint32_t buffers_size);
TS_CAPI void TS_CCALL tsCommand_setTextureTable(TSCommand self, uint32_t index, TSTextureTable table);
TS_CAPI void TS_CCALL tsCommand_setTextureTables_ucATT(TSCommand self, uint32_t index, const TSTextureTable *tables, uint32_t tables_size);
TS_CAPI void TS_CCALL tsCommand_setStorageTable(TSCommand self, uint32_t index, TSBufferTable table);
TS_CAPI void TS_CCALL tsCommand_setStorageTables_ucABT(TSCommand self, uint32_t index, const TSBufferTable *tables, uint32_t tables_size);
TS_CAPI void* TS_CCALL tsCommand_getVertexData(TSCommand self, uint32_t index, size_t size);
TS_CAPI void TS_CCALL tsCommand_setVertexData(TSCommand self, uint32_t index, const void *src, size_t size);
TS_CAPI void TS_CCALL tsCommand_setVertexBuffer(TSCommand self, uint32_t index, TSBuffer buffer, size_t offset);
TS_CAPI void TS_CCALL tsCommand_setVertexOffset(TSCommand self, uint32_t index, size_t offset, bool_t relative);
TS_CAPI void TS_CCALL tsCommand_setVertexBuffers_ucAB(TSCommand self, uint32_t index, const TSBuffer *buffers, uint32_t buffers_size);
TS_CAPI void TS_CCALL tsCommand_setVertexBuffers_ucABcA(TSCommand self, uint32_t index, const TSBuffer *buffers, uint32_t buffers_size, const size_t *offsets, uint32_t offsets_size);
TS_CAPI void* TS_CCALL tsCommand_getIndexData(TSCommand self, TS_Format format, size_t size);
TS_CAPI void TS_CCALL tsCommand_setIndexData(TSCommand self, TS_Format format, const void *src, size_t size);
TS_CAPI void TS_CCALL tsCommand_setIndexBuffer(TSCommand self, TS_Format format, TSBuffer buffer, size_t offset);
TS_CAPI void TS_CCALL tsCommand_setIndexOffset(TSCommand self, size_t offset, bool_t relative);
TS_CAPI void* TS_CCALL tsCommand_getIndirectData(TSCommand self, size_t size);
TS_CAPI void TS_CCALL tsCommand_setIndirectData(TSCommand self, const void *src, size_t size);
TS_CAPI void TS_CCALL tsCommand_setIndirectBuffer(TSCommand self, TSBuffer buffer, size_t offset);
TS_CAPI void TS_CCALL tsCommand_setIndirectOffset(TSCommand self, size_t offset, bool_t relative);
TS_CAPI void TS_CCALL tsCommand_setBlendColor_cC(TSCommand self, const TSColor *color);
TS_CAPI void TS_CCALL tsCommand_setBlendColor_ffff(TSCommand self, float32_t r, float32_t g, float32_t b, float32_t a);
TS_CAPI void TS_CCALL tsCommand_setStencilRef(TSCommand self, uint32_t ref);
TS_CAPI void TS_CCALL tsCommand_drawArrays(TSCommand self, uint32_t num_vertices, uint32_t base_vertex);
TS_CAPI void TS_CCALL tsCommand_drawArraysInstanced(TSCommand self, uint32_t num_vertices, uint32_t base_vertex, uint32_t num_instances, uint32_t base_instance);
TS_CAPI void TS_CCALL tsCommand_drawArraysIndirect_uz(TSCommand self, uint32_t num_draws, size_t stride);
TS_CAPI void TS_CCALL tsCommand_drawArraysIndirect_Bzuz(TSCommand self, TSBuffer buffer, size_t offset, uint32_t num_draws, size_t stride);
TS_CAPI void TS_CCALL tsCommand_drawElements(TSCommand self, uint32_t num_indices, uint32_t base_index, int32_t base_vertex);
TS_CAPI void TS_CCALL tsCommand_drawElementsInstanced_uuu(TSCommand self, uint32_t num_indices, uint32_t base_index, uint32_t num_instances);
TS_CAPI void TS_CCALL tsCommand_drawElementsInstanced_uuiuu(TSCommand self, uint32_t num_indices, uint32_t base_index, int32_t base_vertex, uint32_t num_instances, uint32_t base_instance);
TS_CAPI void TS_CCALL tsCommand_drawElementsIndirect_uz(TSCommand self, uint32_t num_draws, size_t stride);
TS_CAPI void TS_CCALL tsCommand_drawElementsIndirect_Bzuz(TSCommand self, TSBuffer buffer, size_t offset, uint32_t num_draws, size_t stride);
TS_CAPI void TS_CCALL tsCommand_drawMesh(TSCommand self, uint32_t width, uint32_t height, uint32_t depth);
TS_CAPI void TS_CCALL tsCommand_drawMeshIndirect_uz(TSCommand self, uint32_t num_draws, size_t stride);
TS_CAPI void TS_CCALL tsCommand_drawMeshIndirect_Bzuz(TSCommand self, TSBuffer buffer, size_t offset, uint32_t num_draws, size_t stride);
TS_CAPI void TS_CCALL tsCommand_beginConditional(TSCommand self, TSBuffer buffer, size_t offset);
TS_CAPI void TS_CCALL tsCommand_endConditional(TSCommand self);
TS_CAPI bool_t TS_CCALL tsCommand_beginQuery(TSCommand self, TSQuery query);
TS_CAPI void TS_CCALL tsCommand_endQuery(TSCommand self, TSQuery query);

/// Tellusim::D3D12Command
TS_CAPI TSD3D12Command TS_CCALL tsD3D12Command_new(void);
TS_CAPI void TS_CCALL tsD3D12Command_delete(TSD3D12Command self);
TS_CAPI bool_t TS_CCALL tsD3D12Command_equalPtr(const TSD3D12Command self, const TSD3D12Command ptr);
TS_CAPI TSD3D12Command TS_CCALL tsD3D12Command_copyPtr(const TSD3D12Command self);
TS_CAPI TSD3D12Command TS_CCALL tsD3D12Command_clonePtr(const TSD3D12Command self);
TS_CAPI void TS_CCALL tsD3D12Command_clearPtr(TSD3D12Command self);
TS_CAPI void TS_CCALL tsD3D12Command_destroyPtr(TSD3D12Command self);
TS_CAPI void TS_CCALL tsD3D12Command_acquirePtr(TSD3D12Command self);
TS_CAPI void TS_CCALL tsD3D12Command_unacquirePtr(TSD3D12Command self);
TS_CAPI bool_t TS_CCALL tsD3D12Command_isValidPtr(const TSD3D12Command self);
TS_CAPI bool_t TS_CCALL tsD3D12Command_isOwnerPtr(const TSD3D12Command self);
TS_CAPI bool_t TS_CCALL tsD3D12Command_isConstPtr(const TSD3D12Command self);
TS_CAPI uint32_t TS_CCALL tsD3D12Command_getCountPtr(const TSD3D12Command self);
TS_CAPI const void* TS_CCALL tsD3D12Command_getInternalPtr(const TSD3D12Command self);
TS_CAPI bool_t TS_CCALL tsD3D12Command_equalCommandPtr(const TSD3D12Command self, const TSCommand base);
TS_CAPI TSD3D12Command TS_CCALL tsD3D12Command_castCommandPtr(TSCommand base);
TS_CAPI TSCommand TS_CCALL tsD3D12Command_baseCommandPtr(TSD3D12Command self);
TS_CAPI ID3D12GraphicsCommandList* TS_CCALL tsD3D12Command_getD3D12Command(TSD3D12Command self);
TS_CAPI void TS_CCALL tsD3D12Command_update(TSD3D12Command self);

/// Tellusim::MTLCommand
TS_CAPI TSMTLCommand TS_CCALL tsMTLCommand_new(void);
TS_CAPI void TS_CCALL tsMTLCommand_delete(TSMTLCommand self);
TS_CAPI bool_t TS_CCALL tsMTLCommand_equalPtr(const TSMTLCommand self, const TSMTLCommand ptr);
TS_CAPI TSMTLCommand TS_CCALL tsMTLCommand_copyPtr(const TSMTLCommand self);
TS_CAPI TSMTLCommand TS_CCALL tsMTLCommand_clonePtr(const TSMTLCommand self);
TS_CAPI void TS_CCALL tsMTLCommand_clearPtr(TSMTLCommand self);
TS_CAPI void TS_CCALL tsMTLCommand_destroyPtr(TSMTLCommand self);
TS_CAPI void TS_CCALL tsMTLCommand_acquirePtr(TSMTLCommand self);
TS_CAPI void TS_CCALL tsMTLCommand_unacquirePtr(TSMTLCommand self);
TS_CAPI bool_t TS_CCALL tsMTLCommand_isValidPtr(const TSMTLCommand self);
TS_CAPI bool_t TS_CCALL tsMTLCommand_isOwnerPtr(const TSMTLCommand self);
TS_CAPI bool_t TS_CCALL tsMTLCommand_isConstPtr(const TSMTLCommand self);
TS_CAPI uint32_t TS_CCALL tsMTLCommand_getCountPtr(const TSMTLCommand self);
TS_CAPI const void* TS_CCALL tsMTLCommand_getInternalPtr(const TSMTLCommand self);
TS_CAPI bool_t TS_CCALL tsMTLCommand_equalCommandPtr(const TSMTLCommand self, const TSCommand base);
TS_CAPI TSMTLCommand TS_CCALL tsMTLCommand_castCommandPtr(TSCommand base);
TS_CAPI TSCommand TS_CCALL tsMTLCommand_baseCommandPtr(TSMTLCommand self);
TS_CAPI void* TS_CCALL tsMTLCommand_getEncoder(TSMTLCommand self);
TS_CAPI void TS_CCALL tsMTLCommand_flush_prb(TSMTLCommand self, void *encoder, bool_t enqueue);
TS_CAPI void TS_CCALL tsMTLCommand_flush_bb(TSMTLCommand self, bool_t create, bool_t enqueue);
TS_CAPI void TS_CCALL tsMTLCommand_update(TSMTLCommand self);

/// Tellusim::VKCommand
TS_CAPI TSVKCommand TS_CCALL tsVKCommand_new(void);
TS_CAPI void TS_CCALL tsVKCommand_delete(TSVKCommand self);
TS_CAPI bool_t TS_CCALL tsVKCommand_equalPtr(const TSVKCommand self, const TSVKCommand ptr);
TS_CAPI TSVKCommand TS_CCALL tsVKCommand_copyPtr(const TSVKCommand self);
TS_CAPI TSVKCommand TS_CCALL tsVKCommand_clonePtr(const TSVKCommand self);
TS_CAPI void TS_CCALL tsVKCommand_clearPtr(TSVKCommand self);
TS_CAPI void TS_CCALL tsVKCommand_destroyPtr(TSVKCommand self);
TS_CAPI void TS_CCALL tsVKCommand_acquirePtr(TSVKCommand self);
TS_CAPI void TS_CCALL tsVKCommand_unacquirePtr(TSVKCommand self);
TS_CAPI bool_t TS_CCALL tsVKCommand_isValidPtr(const TSVKCommand self);
TS_CAPI bool_t TS_CCALL tsVKCommand_isOwnerPtr(const TSVKCommand self);
TS_CAPI bool_t TS_CCALL tsVKCommand_isConstPtr(const TSVKCommand self);
TS_CAPI uint32_t TS_CCALL tsVKCommand_getCountPtr(const TSVKCommand self);
TS_CAPI const void* TS_CCALL tsVKCommand_getInternalPtr(const TSVKCommand self);
TS_CAPI bool_t TS_CCALL tsVKCommand_equalCommandPtr(const TSVKCommand self, const TSCommand base);
TS_CAPI TSVKCommand TS_CCALL tsVKCommand_castCommandPtr(TSCommand base);
TS_CAPI TSCommand TS_CCALL tsVKCommand_baseCommandPtr(TSVKCommand self);
TS_CAPI VkCommandBuffer TS_CCALL tsVKCommand_getVKCommand(TSVKCommand self);
TS_CAPI VkDescriptorSet TS_CCALL tsVKCommand_getSamplerDescriptor(TSVKCommand self);
TS_CAPI VkDescriptorSet TS_CCALL tsVKCommand_getImageDescriptor(TSVKCommand self);
TS_CAPI VkDescriptorSet TS_CCALL tsVKCommand_getBufferDescriptor(TSVKCommand self);
TS_CAPI VkDescriptorSet TS_CCALL tsVKCommand_getTracingDescriptor(TSVKCommand self);
TS_CAPI VkDescriptorSet TS_CCALL tsVKCommand_getTexelDescriptor(TSVKCommand self);
TS_CAPI void TS_CCALL tsVKCommand_update(TSVKCommand self);

/// Tellusim::FUCommand
TS_CAPI TSFUCommand TS_CCALL tsFUCommand_new(void);
TS_CAPI TSFUCommand TS_CCALL tsFUCommand_new_cACb(const TSCommand *commands, uint32_t commands_size, bool_t owner);
TS_CAPI void TS_CCALL tsFUCommand_delete(TSFUCommand self);
TS_CAPI bool_t TS_CCALL tsFUCommand_equalPtr(const TSFUCommand self, const TSFUCommand ptr);
TS_CAPI TSFUCommand TS_CCALL tsFUCommand_copyPtr(const TSFUCommand self);
TS_CAPI TSFUCommand TS_CCALL tsFUCommand_clonePtr(const TSFUCommand self);
TS_CAPI void TS_CCALL tsFUCommand_clearPtr(TSFUCommand self);
TS_CAPI void TS_CCALL tsFUCommand_destroyPtr(TSFUCommand self);
TS_CAPI void TS_CCALL tsFUCommand_acquirePtr(TSFUCommand self);
TS_CAPI void TS_CCALL tsFUCommand_unacquirePtr(TSFUCommand self);
TS_CAPI bool_t TS_CCALL tsFUCommand_isValidPtr(const TSFUCommand self);
TS_CAPI bool_t TS_CCALL tsFUCommand_isOwnerPtr(const TSFUCommand self);
TS_CAPI bool_t TS_CCALL tsFUCommand_isConstPtr(const TSFUCommand self);
TS_CAPI uint32_t TS_CCALL tsFUCommand_getCountPtr(const TSFUCommand self);
TS_CAPI const void* TS_CCALL tsFUCommand_getInternalPtr(const TSFUCommand self);
TS_CAPI bool_t TS_CCALL tsFUCommand_equalCommandPtr(const TSFUCommand self, const TSCommand base);
TS_CAPI TSFUCommand TS_CCALL tsFUCommand_castCommandPtr(TSCommand base);
TS_CAPI TSCommand TS_CCALL tsFUCommand_baseCommandPtr(TSFUCommand self);
TS_CAPI void TS_CCALL tsFUCommand_setMask(TSFUCommand self, uint32_t mask);
TS_CAPI uint32_t TS_CCALL tsFUCommand_getMask(TSFUCommand self);
TS_CAPI uint32_t TS_CCALL tsFUCommand_getNumCommands(TSFUCommand self);
TS_CAPI TSCommand TS_CCALL tsFUCommand_getCommand_cu(TSFUCommand self, uint32_t index);
TS_CAPI TSCommand TS_CCALL tsFUCommand_getCommand_u(TSFUCommand self, uint32_t index);

/// Tellusim::Compute
TS_CAPI TSCompute TS_CCALL tsCompute_new(void);
TS_CAPI void TS_CCALL tsCompute_delete(TSCompute self);
TS_CAPI bool_t TS_CCALL tsCompute_equalPtr(const TSCompute self, const TSCompute ptr);
TS_CAPI TSCompute TS_CCALL tsCompute_copyPtr(const TSCompute self);
TS_CAPI TSCompute TS_CCALL tsCompute_clonePtr(const TSCompute self);
TS_CAPI void TS_CCALL tsCompute_clearPtr(TSCompute self);
TS_CAPI void TS_CCALL tsCompute_destroyPtr(TSCompute self);
TS_CAPI void TS_CCALL tsCompute_acquirePtr(TSCompute self);
TS_CAPI void TS_CCALL tsCompute_unacquirePtr(TSCompute self);
TS_CAPI bool_t TS_CCALL tsCompute_isValidPtr(const TSCompute self);
TS_CAPI bool_t TS_CCALL tsCompute_isOwnerPtr(const TSCompute self);
TS_CAPI bool_t TS_CCALL tsCompute_isConstPtr(const TSCompute self);
TS_CAPI uint32_t TS_CCALL tsCompute_getCountPtr(const TSCompute self);
TS_CAPI const void* TS_CCALL tsCompute_getInternalPtr(const TSCompute self);
TS_CAPI TS_Platform TS_CCALL tsCompute_getPlatform(TSCompute self);
TS_CAPI const char* TS_CCALL tsCompute_getPlatformName(TSCompute self);
TS_CAPI uint32_t TS_CCALL tsCompute_getIndex(TSCompute self);
TS_CAPI void TS_CCALL tsCompute_setKernel(TSCompute self, TSKernel kernel);
TS_CAPI TSKernel TS_CCALL tsCompute_getKernel(TSCompute self);
TS_CAPI void TS_CCALL tsCompute_setTraversal(TSCompute self, TSTraversal traversal);
TS_CAPI TSTraversal TS_CCALL tsCompute_getTraversal(TSCompute self);
TS_CAPI void TS_CCALL tsCompute_setSampler(TSCompute self, uint32_t index, TSSampler sampler);
TS_CAPI void TS_CCALL tsCompute_setSamplers_ucAS(TSCompute self, uint32_t index, const TSSampler *samplers, uint32_t samplers_size);
TS_CAPI void TS_CCALL tsCompute_setTexture_uT(TSCompute self, uint32_t index, TSTexture texture);
TS_CAPI void TS_CCALL tsCompute_setTexture_uTcS(TSCompute self, uint32_t index, TSTexture texture, const TSSlice *slice);
TS_CAPI void TS_CCALL tsCompute_setTextures_ucAT(TSCompute self, uint32_t index, const TSTexture *textures, uint32_t textures_size);
TS_CAPI void TS_CCALL tsCompute_setSurfaceTexture_uT(TSCompute self, uint32_t index, TSTexture texture);
TS_CAPI void TS_CCALL tsCompute_setSurfaceTexture_uTcSF(TSCompute self, uint32_t index, TSTexture texture, const TSSlice *slice, TS_Format format);
TS_CAPI void TS_CCALL tsCompute_setSurfaceTextures_ucAT(TSCompute self, uint32_t index, const TSTexture *textures, uint32_t textures_size);
TS_CAPI void* TS_CCALL tsCompute_getUniformData(TSCompute self, uint32_t index, size_t size);
TS_CAPI void TS_CCALL tsCompute_setUniformData(TSCompute self, uint32_t index, const void *src, size_t size);
TS_CAPI void TS_CCALL tsCompute_setUniformBuffer(TSCompute self, uint32_t index, TSBuffer buffer, size_t offset, size_t size);
TS_CAPI void TS_CCALL tsCompute_setUniformOffset(TSCompute self, uint32_t index, size_t offset, bool_t relative);
TS_CAPI void TS_CCALL tsCompute_setUniformBuffers_ucAB(TSCompute self, uint32_t index, const TSBuffer *buffers, uint32_t buffers_size);
TS_CAPI void TS_CCALL tsCompute_setUniformBuffers_ucABcA(TSCompute self, uint32_t index, const TSBuffer *buffers, uint32_t buffers_size, const size_t *offsets, uint32_t offsets_size);
TS_CAPI void* TS_CCALL tsCompute_getStorageData(TSCompute self, uint32_t index, size_t size);
TS_CAPI void TS_CCALL tsCompute_setStorageData(TSCompute self, uint32_t index, const void *src, size_t size);
TS_CAPI void TS_CCALL tsCompute_setStorageBuffer(TSCompute self, uint32_t index, TSBuffer buffer, size_t offset, size_t size);
TS_CAPI void TS_CCALL tsCompute_setStorageOffset(TSCompute self, uint32_t index, size_t offset, bool_t relative);
TS_CAPI void TS_CCALL tsCompute_setStorageBuffers_ucAB(TSCompute self, uint32_t index, const TSBuffer *buffers, uint32_t buffers_size);
TS_CAPI void TS_CCALL tsCompute_setStorageBuffers_ucABcA(TSCompute self, uint32_t index, const TSBuffer *buffers, uint32_t buffers_size, const size_t *offsets, uint32_t offsets_size);
TS_CAPI void TS_CCALL tsCompute_setTracing(TSCompute self, uint32_t index, TSTracing tracing);
TS_CAPI void TS_CCALL tsCompute_setTracings_ucAT(TSCompute self, uint32_t index, const TSTracing *tracings, uint32_t tracings_size);
TS_CAPI void TS_CCALL tsCompute_setTexelBuffer(TSCompute self, uint32_t index, TSBuffer buffer);
TS_CAPI void TS_CCALL tsCompute_setTexelBuffers_ucAB(TSCompute self, uint32_t index, const TSBuffer *buffers, uint32_t buffers_size);
TS_CAPI void TS_CCALL tsCompute_setTextureTable(TSCompute self, uint32_t index, TSTextureTable table);
TS_CAPI void TS_CCALL tsCompute_setTextureTables_ucATT(TSCompute self, uint32_t index, const TSTextureTable *tables, uint32_t tables_size);
TS_CAPI void TS_CCALL tsCompute_setStorageTable(TSCompute self, uint32_t index, TSBufferTable table);
TS_CAPI void TS_CCALL tsCompute_setStorageTables_ucABT(TSCompute self, uint32_t index, const TSBufferTable *tables, uint32_t tables_size);
TS_CAPI void* TS_CCALL tsCompute_getIndirectData(TSCompute self, size_t size);
TS_CAPI void TS_CCALL tsCompute_setIndirectData(TSCompute self, const void *src, size_t size);
TS_CAPI void TS_CCALL tsCompute_setIndirectBuffer(TSCompute self, TSBuffer buffer, size_t offset);
TS_CAPI void TS_CCALL tsCompute_setIndirectOffset(TSCompute self, size_t offset, bool_t relative);
TS_CAPI void TS_CCALL tsCompute_dispatch_uuu(TSCompute self, uint32_t width, uint32_t height, uint32_t depth);
TS_CAPI void TS_CCALL tsCompute_dispatch_cT(TSCompute self, const TSTexture texture);
TS_CAPI void TS_CCALL tsCompute_dispatch_cS(TSCompute self, const TSSize *size);
TS_CAPI void TS_CCALL tsCompute_dispatchIndirect(TSCompute self);
TS_CAPI bool_t TS_CCALL tsCompute_setBuffer_Bzpz(TSCompute self, TSBuffer buffer, size_t offset, const void *src, size_t size);
TS_CAPI bool_t TS_CCALL tsCompute_setBuffer_Bpz(TSCompute self, TSBuffer buffer, const void *src, size_t size);
TS_CAPI bool_t TS_CCALL tsCompute_setBuffer_Bp(TSCompute self, TSBuffer buffer, const void *src);
TS_CAPI bool_t TS_CCALL tsCompute_copyBuffer_BzBzz(TSCompute self, TSBuffer buffer, size_t dest_offset, TSBuffer src, size_t src_offset, size_t size);
TS_CAPI bool_t TS_CCALL tsCompute_copyBuffer_BzBz(TSCompute self, TSBuffer buffer, size_t dest_offset, TSBuffer src, size_t size);
TS_CAPI bool_t TS_CCALL tsCompute_copyBuffer_BBz(TSCompute self, TSBuffer buffer, TSBuffer src, size_t size);
TS_CAPI bool_t TS_CCALL tsCompute_copyBuffer_BB(TSCompute self, TSBuffer buffer, TSBuffer src);
TS_CAPI bool_t TS_CCALL tsCompute_clearBuffer_BFzpz(TSCompute self, TSBuffer buffer, TS_Format format, size_t offset, const void *src, size_t size);
TS_CAPI bool_t TS_CCALL tsCompute_clearBuffer_BFpz(TSCompute self, TSBuffer buffer, TS_Format format, const void *src, size_t size);
TS_CAPI bool_t TS_CCALL tsCompute_clearBuffer_BFp(TSCompute self, TSBuffer buffer, TS_Format format, const void *src);
TS_CAPI bool_t TS_CCALL tsCompute_clearBuffer_B(TSCompute self, TSBuffer buffer);
TS_CAPI bool_t TS_CCALL tsCompute_setTexture_TcOcScIcS(TSCompute self, TSTexture texture, const TSOrigin *dest_origin, const TSSlice *dest_slice, const TSImage image, const TSSlice *src_slice);
TS_CAPI bool_t TS_CCALL tsCompute_setTexture_TcOcI(TSCompute self, TSTexture texture, const TSOrigin *dest_origin, const TSImage image);
TS_CAPI bool_t TS_CCALL tsCompute_setTexture_TcScI(TSCompute self, TSTexture texture, const TSSlice *dest_slice, const TSImage image);
TS_CAPI bool_t TS_CCALL tsCompute_setTexture_TcI(TSCompute self, TSTexture texture, const TSImage image);
TS_CAPI bool_t TS_CCALL tsCompute_copyTexture_TcOcSTcRcS(TSCompute self, TSTexture texture, const TSOrigin *dest_origin, const TSSlice *dest_slice, TSTexture src, const TSRegion *src_region, const TSSlice *src_slice);
TS_CAPI bool_t TS_CCALL tsCompute_copyTexture_TcOTcR(TSCompute self, TSTexture texture, const TSOrigin *dest_origin, TSTexture src, const TSRegion *src_region);
TS_CAPI bool_t TS_CCALL tsCompute_copyTexture_TcSTcS(TSCompute self, TSTexture texture, const TSSlice *dest_slice, TSTexture src, const TSSlice *src_slice);
TS_CAPI bool_t TS_CCALL tsCompute_copyTexture_TT(TSCompute self, TSTexture texture, TSTexture src);
TS_CAPI bool_t TS_CCALL tsCompute_clearTexture_TcRcSp(TSCompute self, TSTexture texture, const TSRegion *region, const TSSlice *slice, const void *src);
TS_CAPI bool_t TS_CCALL tsCompute_clearTexture_TcRp(TSCompute self, TSTexture texture, const TSRegion *region, const void *src);
TS_CAPI bool_t TS_CCALL tsCompute_clearTexture_TcSp(TSCompute self, TSTexture texture, const TSSlice *slice, const void *src);
TS_CAPI bool_t TS_CCALL tsCompute_clearTexture_Tp(TSCompute self, TSTexture texture, const void *src);
TS_CAPI void TS_CCALL tsCompute_barrier_T(TSCompute self, TSTexture texture);
TS_CAPI void TS_CCALL tsCompute_barrier_B(TSCompute self, TSBuffer buffer);
TS_CAPI void TS_CCALL tsCompute_barrier_cAT(TSCompute self, const TSTexture *textures, uint32_t textures_size);
TS_CAPI void TS_CCALL tsCompute_barrier_cAB(TSCompute self, const TSBuffer *buffers, uint32_t buffers_size);
TS_CAPI void TS_CCALL tsCompute_beginConditional(TSCompute self, TSBuffer buffer, size_t offset);
TS_CAPI void TS_CCALL tsCompute_endConditional(TSCompute self);
TS_CAPI bool_t TS_CCALL tsCompute_beginQuery(TSCompute self, TSQuery query);
TS_CAPI void TS_CCALL tsCompute_endQuery(TSCompute self, TSQuery query);

/// Tellusim::D3D12Compute
TS_CAPI TSD3D12Compute TS_CCALL tsD3D12Compute_new(void);
TS_CAPI void TS_CCALL tsD3D12Compute_delete(TSD3D12Compute self);
TS_CAPI bool_t TS_CCALL tsD3D12Compute_equalPtr(const TSD3D12Compute self, const TSD3D12Compute ptr);
TS_CAPI TSD3D12Compute TS_CCALL tsD3D12Compute_copyPtr(const TSD3D12Compute self);
TS_CAPI TSD3D12Compute TS_CCALL tsD3D12Compute_clonePtr(const TSD3D12Compute self);
TS_CAPI void TS_CCALL tsD3D12Compute_clearPtr(TSD3D12Compute self);
TS_CAPI void TS_CCALL tsD3D12Compute_destroyPtr(TSD3D12Compute self);
TS_CAPI void TS_CCALL tsD3D12Compute_acquirePtr(TSD3D12Compute self);
TS_CAPI void TS_CCALL tsD3D12Compute_unacquirePtr(TSD3D12Compute self);
TS_CAPI bool_t TS_CCALL tsD3D12Compute_isValidPtr(const TSD3D12Compute self);
TS_CAPI bool_t TS_CCALL tsD3D12Compute_isOwnerPtr(const TSD3D12Compute self);
TS_CAPI bool_t TS_CCALL tsD3D12Compute_isConstPtr(const TSD3D12Compute self);
TS_CAPI uint32_t TS_CCALL tsD3D12Compute_getCountPtr(const TSD3D12Compute self);
TS_CAPI const void* TS_CCALL tsD3D12Compute_getInternalPtr(const TSD3D12Compute self);
TS_CAPI bool_t TS_CCALL tsD3D12Compute_equalComputePtr(const TSD3D12Compute self, const TSCompute base);
TS_CAPI TSD3D12Compute TS_CCALL tsD3D12Compute_castComputePtr(TSCompute base);
TS_CAPI TSCompute TS_CCALL tsD3D12Compute_baseComputePtr(TSD3D12Compute self);
TS_CAPI ID3D12GraphicsCommandList* TS_CCALL tsD3D12Compute_getCommand(TSD3D12Compute self);
TS_CAPI void TS_CCALL tsD3D12Compute_update(TSD3D12Compute self);

/// Tellusim::MTLCompute
TS_CAPI TSMTLCompute TS_CCALL tsMTLCompute_new(void);
TS_CAPI void TS_CCALL tsMTLCompute_delete(TSMTLCompute self);
TS_CAPI bool_t TS_CCALL tsMTLCompute_equalPtr(const TSMTLCompute self, const TSMTLCompute ptr);
TS_CAPI TSMTLCompute TS_CCALL tsMTLCompute_copyPtr(const TSMTLCompute self);
TS_CAPI TSMTLCompute TS_CCALL tsMTLCompute_clonePtr(const TSMTLCompute self);
TS_CAPI void TS_CCALL tsMTLCompute_clearPtr(TSMTLCompute self);
TS_CAPI void TS_CCALL tsMTLCompute_destroyPtr(TSMTLCompute self);
TS_CAPI void TS_CCALL tsMTLCompute_acquirePtr(TSMTLCompute self);
TS_CAPI void TS_CCALL tsMTLCompute_unacquirePtr(TSMTLCompute self);
TS_CAPI bool_t TS_CCALL tsMTLCompute_isValidPtr(const TSMTLCompute self);
TS_CAPI bool_t TS_CCALL tsMTLCompute_isOwnerPtr(const TSMTLCompute self);
TS_CAPI bool_t TS_CCALL tsMTLCompute_isConstPtr(const TSMTLCompute self);
TS_CAPI uint32_t TS_CCALL tsMTLCompute_getCountPtr(const TSMTLCompute self);
TS_CAPI const void* TS_CCALL tsMTLCompute_getInternalPtr(const TSMTLCompute self);
TS_CAPI bool_t TS_CCALL tsMTLCompute_equalComputePtr(const TSMTLCompute self, const TSCompute base);
TS_CAPI TSMTLCompute TS_CCALL tsMTLCompute_castComputePtr(TSCompute base);
TS_CAPI TSCompute TS_CCALL tsMTLCompute_baseComputePtr(TSMTLCompute self);
TS_CAPI void* TS_CCALL tsMTLCompute_getEncoder(TSMTLCompute self);
TS_CAPI void TS_CCALL tsMTLCompute_flush_prb(TSMTLCompute self, void *encoder, bool_t enqueue);
TS_CAPI void TS_CCALL tsMTLCompute_flush_bb(TSMTLCompute self, bool_t create, bool_t enqueue);
TS_CAPI void TS_CCALL tsMTLCompute_update(TSMTLCompute self);

/// Tellusim::VKCompute
TS_CAPI TSVKCompute TS_CCALL tsVKCompute_new(void);
TS_CAPI void TS_CCALL tsVKCompute_delete(TSVKCompute self);
TS_CAPI bool_t TS_CCALL tsVKCompute_equalPtr(const TSVKCompute self, const TSVKCompute ptr);
TS_CAPI TSVKCompute TS_CCALL tsVKCompute_copyPtr(const TSVKCompute self);
TS_CAPI TSVKCompute TS_CCALL tsVKCompute_clonePtr(const TSVKCompute self);
TS_CAPI void TS_CCALL tsVKCompute_clearPtr(TSVKCompute self);
TS_CAPI void TS_CCALL tsVKCompute_destroyPtr(TSVKCompute self);
TS_CAPI void TS_CCALL tsVKCompute_acquirePtr(TSVKCompute self);
TS_CAPI void TS_CCALL tsVKCompute_unacquirePtr(TSVKCompute self);
TS_CAPI bool_t TS_CCALL tsVKCompute_isValidPtr(const TSVKCompute self);
TS_CAPI bool_t TS_CCALL tsVKCompute_isOwnerPtr(const TSVKCompute self);
TS_CAPI bool_t TS_CCALL tsVKCompute_isConstPtr(const TSVKCompute self);
TS_CAPI uint32_t TS_CCALL tsVKCompute_getCountPtr(const TSVKCompute self);
TS_CAPI const void* TS_CCALL tsVKCompute_getInternalPtr(const TSVKCompute self);
TS_CAPI bool_t TS_CCALL tsVKCompute_equalComputePtr(const TSVKCompute self, const TSCompute base);
TS_CAPI TSVKCompute TS_CCALL tsVKCompute_castComputePtr(TSCompute base);
TS_CAPI TSCompute TS_CCALL tsVKCompute_baseComputePtr(TSVKCompute self);
TS_CAPI VkCommandBuffer TS_CCALL tsVKCompute_getCommand(TSVKCompute self);
TS_CAPI VkDescriptorSet TS_CCALL tsVKCompute_getSamplerDescriptor(TSVKCompute self);
TS_CAPI VkDescriptorSet TS_CCALL tsVKCompute_getImageDescriptor(TSVKCompute self);
TS_CAPI VkDescriptorSet TS_CCALL tsVKCompute_getBufferDescriptor(TSVKCompute self);
TS_CAPI VkDescriptorSet TS_CCALL tsVKCompute_getTracingDescriptor(TSVKCompute self);
TS_CAPI VkDescriptorSet TS_CCALL tsVKCompute_getTexelDescriptor(TSVKCompute self);
TS_CAPI void TS_CCALL tsVKCompute_update(TSVKCompute self);

/// Tellusim::FUCompute
TS_CAPI TSFUCompute TS_CCALL tsFUCompute_new(void);
TS_CAPI TSFUCompute TS_CCALL tsFUCompute_new_cACb(const TSCompute *computes, uint32_t computes_size, bool_t owner);
TS_CAPI void TS_CCALL tsFUCompute_delete(TSFUCompute self);
TS_CAPI bool_t TS_CCALL tsFUCompute_equalPtr(const TSFUCompute self, const TSFUCompute ptr);
TS_CAPI TSFUCompute TS_CCALL tsFUCompute_copyPtr(const TSFUCompute self);
TS_CAPI TSFUCompute TS_CCALL tsFUCompute_clonePtr(const TSFUCompute self);
TS_CAPI void TS_CCALL tsFUCompute_clearPtr(TSFUCompute self);
TS_CAPI void TS_CCALL tsFUCompute_destroyPtr(TSFUCompute self);
TS_CAPI void TS_CCALL tsFUCompute_acquirePtr(TSFUCompute self);
TS_CAPI void TS_CCALL tsFUCompute_unacquirePtr(TSFUCompute self);
TS_CAPI bool_t TS_CCALL tsFUCompute_isValidPtr(const TSFUCompute self);
TS_CAPI bool_t TS_CCALL tsFUCompute_isOwnerPtr(const TSFUCompute self);
TS_CAPI bool_t TS_CCALL tsFUCompute_isConstPtr(const TSFUCompute self);
TS_CAPI uint32_t TS_CCALL tsFUCompute_getCountPtr(const TSFUCompute self);
TS_CAPI const void* TS_CCALL tsFUCompute_getInternalPtr(const TSFUCompute self);
TS_CAPI bool_t TS_CCALL tsFUCompute_equalComputePtr(const TSFUCompute self, const TSCompute base);
TS_CAPI TSFUCompute TS_CCALL tsFUCompute_castComputePtr(TSCompute base);
TS_CAPI TSCompute TS_CCALL tsFUCompute_baseComputePtr(TSFUCompute self);
TS_CAPI void TS_CCALL tsFUCompute_setMask(TSFUCompute self, uint32_t mask);
TS_CAPI uint32_t TS_CCALL tsFUCompute_getMask(TSFUCompute self);
TS_CAPI uint32_t TS_CCALL tsFUCompute_getNumComputes(TSFUCompute self);
TS_CAPI TSCompute TS_CCALL tsFUCompute_getCompute_cu(TSFUCompute self, uint32_t index);
TS_CAPI TSCompute TS_CCALL tsFUCompute_getCompute_u(TSFUCompute self, uint32_t index);

/// Tellusim::Context
TS_CAPI TSContext TS_CCALL tsContext_new(void);
TS_CAPI TSContext TS_CCALL tsContext_new_Pu(TS_Platform platform, uint32_t index);
TS_CAPI void TS_CCALL tsContext_delete(TSContext self);
TS_CAPI bool_t TS_CCALL tsContext_equalPtr(const TSContext self, const TSContext ptr);
TS_CAPI TSContext TS_CCALL tsContext_copyPtr(const TSContext self);
TS_CAPI TSContext TS_CCALL tsContext_clonePtr(const TSContext self);
TS_CAPI void TS_CCALL tsContext_clearPtr(TSContext self);
TS_CAPI void TS_CCALL tsContext_destroyPtr(TSContext self);
TS_CAPI void TS_CCALL tsContext_acquirePtr(TSContext self);
TS_CAPI void TS_CCALL tsContext_unacquirePtr(TSContext self);
TS_CAPI bool_t TS_CCALL tsContext_isValidPtr(const TSContext self);
TS_CAPI bool_t TS_CCALL tsContext_isOwnerPtr(const TSContext self);
TS_CAPI bool_t TS_CCALL tsContext_isConstPtr(const TSContext self);
TS_CAPI uint32_t TS_CCALL tsContext_getCountPtr(const TSContext self);
TS_CAPI const void* TS_CCALL tsContext_getInternalPtr(const TSContext self);
TS_CAPI TS_Platform TS_CCALL tsContext_getPlatform(TSContext self);
TS_CAPI const char* TS_CCALL tsContext_getPlatformName(TSContext self);
TS_CAPI uint32_t TS_CCALL tsContext_getIndex(TSContext self);
TS_CAPI bool_t TS_CCALL tsContext_isCreated(TSContext self);
TS_CAPI bool_t TS_CCALL tsContext_create(TSContext self);
TS_CAPI bool_t TS_CCALL tsContext_flush(TSContext self);
TS_CAPI bool_t TS_CCALL tsContext_finish(TSContext self);

/// Tellusim::D3D12Context
TS_CAPI TSD3D12Context TS_CCALL tsD3D12Context_new(void);
TS_CAPI void TS_CCALL tsD3D12Context_delete(TSD3D12Context self);
TS_CAPI bool_t TS_CCALL tsD3D12Context_equalPtr(const TSD3D12Context self, const TSD3D12Context ptr);
TS_CAPI TSD3D12Context TS_CCALL tsD3D12Context_copyPtr(const TSD3D12Context self);
TS_CAPI TSD3D12Context TS_CCALL tsD3D12Context_clonePtr(const TSD3D12Context self);
TS_CAPI void TS_CCALL tsD3D12Context_clearPtr(TSD3D12Context self);
TS_CAPI void TS_CCALL tsD3D12Context_destroyPtr(TSD3D12Context self);
TS_CAPI void TS_CCALL tsD3D12Context_acquirePtr(TSD3D12Context self);
TS_CAPI void TS_CCALL tsD3D12Context_unacquirePtr(TSD3D12Context self);
TS_CAPI bool_t TS_CCALL tsD3D12Context_isValidPtr(const TSD3D12Context self);
TS_CAPI bool_t TS_CCALL tsD3D12Context_isOwnerPtr(const TSD3D12Context self);
TS_CAPI bool_t TS_CCALL tsD3D12Context_isConstPtr(const TSD3D12Context self);
TS_CAPI uint32_t TS_CCALL tsD3D12Context_getCountPtr(const TSD3D12Context self);
TS_CAPI const void* TS_CCALL tsD3D12Context_getInternalPtr(const TSD3D12Context self);
TS_CAPI bool_t TS_CCALL tsD3D12Context_equalContextPtr(const TSD3D12Context self, const TSContext base);
TS_CAPI TSD3D12Context TS_CCALL tsD3D12Context_castContextPtr(TSContext base);
TS_CAPI TSContext TS_CCALL tsD3D12Context_baseContextPtr(TSD3D12Context self);
TS_CAPI bool_t TS_CCALL tsD3D12Context_create(TSD3D12Context self, ID3D12Device *device, ID3D12CommandQueue *queue);
TS_CAPI IDXGIFactory4* TS_CCALL tsD3D12Context_getFactory(TSD3D12Context self);
TS_CAPI ID3D12Device* TS_CCALL tsD3D12Context_getDevice(TSD3D12Context self);
TS_CAPI ID3D12CommandQueue* TS_CCALL tsD3D12Context_getQueue(TSD3D12Context self);
TS_CAPI ID3D12GraphicsCommandList* TS_CCALL tsD3D12Context_getCommand(TSD3D12Context self);
TS_CAPI void* TS_CCALL tsD3D12Context_getProcAddress(const char *name);
TS_CAPI bool_t TS_CCALL tsD3D12Context_error(uint32_t result);

/// Tellusim::D3D11Context
TS_CAPI TSD3D11Context TS_CCALL tsD3D11Context_new(void);
TS_CAPI void TS_CCALL tsD3D11Context_delete(TSD3D11Context self);
TS_CAPI bool_t TS_CCALL tsD3D11Context_equalPtr(const TSD3D11Context self, const TSD3D11Context ptr);
TS_CAPI TSD3D11Context TS_CCALL tsD3D11Context_copyPtr(const TSD3D11Context self);
TS_CAPI TSD3D11Context TS_CCALL tsD3D11Context_clonePtr(const TSD3D11Context self);
TS_CAPI void TS_CCALL tsD3D11Context_clearPtr(TSD3D11Context self);
TS_CAPI void TS_CCALL tsD3D11Context_destroyPtr(TSD3D11Context self);
TS_CAPI void TS_CCALL tsD3D11Context_acquirePtr(TSD3D11Context self);
TS_CAPI void TS_CCALL tsD3D11Context_unacquirePtr(TSD3D11Context self);
TS_CAPI bool_t TS_CCALL tsD3D11Context_isValidPtr(const TSD3D11Context self);
TS_CAPI bool_t TS_CCALL tsD3D11Context_isOwnerPtr(const TSD3D11Context self);
TS_CAPI bool_t TS_CCALL tsD3D11Context_isConstPtr(const TSD3D11Context self);
TS_CAPI uint32_t TS_CCALL tsD3D11Context_getCountPtr(const TSD3D11Context self);
TS_CAPI const void* TS_CCALL tsD3D11Context_getInternalPtr(const TSD3D11Context self);
TS_CAPI bool_t TS_CCALL tsD3D11Context_equalContextPtr(const TSD3D11Context self, const TSContext base);
TS_CAPI TSD3D11Context TS_CCALL tsD3D11Context_castContextPtr(TSContext base);
TS_CAPI TSContext TS_CCALL tsD3D11Context_baseContextPtr(TSD3D11Context self);
TS_CAPI bool_t TS_CCALL tsD3D11Context_create(TSD3D11Context self, ID3D11Device *device);
TS_CAPI IDXGIFactory* TS_CCALL tsD3D11Context_getFactory(TSD3D11Context self);
TS_CAPI ID3D11Device* TS_CCALL tsD3D11Context_getDevice(TSD3D11Context self);
TS_CAPI ID3D11DeviceContext* TS_CCALL tsD3D11Context_getD3D11Context(TSD3D11Context self);
TS_CAPI void* TS_CCALL tsD3D11Context_getProcAddress(const char *name);
TS_CAPI bool_t TS_CCALL tsD3D11Context_error(uint32_t result);

/// Tellusim::MTLContext
TS_CAPI TSMTLContext TS_CCALL tsMTLContext_new(void);
TS_CAPI void TS_CCALL tsMTLContext_delete(TSMTLContext self);
TS_CAPI bool_t TS_CCALL tsMTLContext_equalPtr(const TSMTLContext self, const TSMTLContext ptr);
TS_CAPI TSMTLContext TS_CCALL tsMTLContext_copyPtr(const TSMTLContext self);
TS_CAPI TSMTLContext TS_CCALL tsMTLContext_clonePtr(const TSMTLContext self);
TS_CAPI void TS_CCALL tsMTLContext_clearPtr(TSMTLContext self);
TS_CAPI void TS_CCALL tsMTLContext_destroyPtr(TSMTLContext self);
TS_CAPI void TS_CCALL tsMTLContext_acquirePtr(TSMTLContext self);
TS_CAPI void TS_CCALL tsMTLContext_unacquirePtr(TSMTLContext self);
TS_CAPI bool_t TS_CCALL tsMTLContext_isValidPtr(const TSMTLContext self);
TS_CAPI bool_t TS_CCALL tsMTLContext_isOwnerPtr(const TSMTLContext self);
TS_CAPI bool_t TS_CCALL tsMTLContext_isConstPtr(const TSMTLContext self);
TS_CAPI uint32_t TS_CCALL tsMTLContext_getCountPtr(const TSMTLContext self);
TS_CAPI const void* TS_CCALL tsMTLContext_getInternalPtr(const TSMTLContext self);
TS_CAPI bool_t TS_CCALL tsMTLContext_equalContextPtr(const TSMTLContext self, const TSContext base);
TS_CAPI TSMTLContext TS_CCALL tsMTLContext_castContextPtr(TSContext base);
TS_CAPI TSContext TS_CCALL tsMTLContext_baseContextPtr(TSMTLContext self);
TS_CAPI bool_t TS_CCALL tsMTLContext_create(TSMTLContext self, void *device, void *queue);
TS_CAPI void* TS_CCALL tsMTLContext_getDevice(TSMTLContext self);
TS_CAPI void* TS_CCALL tsMTLContext_getQueue(TSMTLContext self);
TS_CAPI void* TS_CCALL tsMTLContext_getCommand(TSMTLContext self);
TS_CAPI void* TS_CCALL tsMTLContext_getEncoder(TSMTLContext self);
TS_CAPI void* TS_CCALL tsMTLContext_getRenderEncoder(TSMTLContext self, void *descriptor);
TS_CAPI void* TS_CCALL tsMTLContext_getComputeEncoder(TSMTLContext self);
TS_CAPI void* TS_CCALL tsMTLContext_getTracingEncoder(TSMTLContext self);
TS_CAPI void* TS_CCALL tsMTLContext_getBlitEncoder(TSMTLContext self);
TS_CAPI void TS_CCALL tsMTLContext_endEncoder(TSMTLContext self);

/// Tellusim::VKContext
TS_CAPI TSVKContext TS_CCALL tsVKContext_new(void);
TS_CAPI void TS_CCALL tsVKContext_delete(TSVKContext self);
TS_CAPI bool_t TS_CCALL tsVKContext_equalPtr(const TSVKContext self, const TSVKContext ptr);
TS_CAPI TSVKContext TS_CCALL tsVKContext_copyPtr(const TSVKContext self);
TS_CAPI TSVKContext TS_CCALL tsVKContext_clonePtr(const TSVKContext self);
TS_CAPI void TS_CCALL tsVKContext_clearPtr(TSVKContext self);
TS_CAPI void TS_CCALL tsVKContext_destroyPtr(TSVKContext self);
TS_CAPI void TS_CCALL tsVKContext_acquirePtr(TSVKContext self);
TS_CAPI void TS_CCALL tsVKContext_unacquirePtr(TSVKContext self);
TS_CAPI bool_t TS_CCALL tsVKContext_isValidPtr(const TSVKContext self);
TS_CAPI bool_t TS_CCALL tsVKContext_isOwnerPtr(const TSVKContext self);
TS_CAPI bool_t TS_CCALL tsVKContext_isConstPtr(const TSVKContext self);
TS_CAPI uint32_t TS_CCALL tsVKContext_getCountPtr(const TSVKContext self);
TS_CAPI const void* TS_CCALL tsVKContext_getInternalPtr(const TSVKContext self);
TS_CAPI bool_t TS_CCALL tsVKContext_equalContextPtr(const TSVKContext self, const TSContext base);
TS_CAPI TSVKContext TS_CCALL tsVKContext_castContextPtr(TSContext base);
TS_CAPI TSContext TS_CCALL tsVKContext_baseContextPtr(TSVKContext self);
TS_CAPI bool_t TS_CCALL tsVKContext_create(TSVKContext self, VkInstance instance, PFN_vkGetInstanceProcAddr func, VkPhysicalDevice adapter, VkDevice device, uint32_t family, uint32_t index);
TS_CAPI VkInstance TS_CCALL tsVKContext_getInstance(TSVKContext self);
TS_CAPI VkPhysicalDevice TS_CCALL tsVKContext_getAdapter(TSVKContext self);
TS_CAPI VkDevice TS_CCALL tsVKContext_getDevice(TSVKContext self);
TS_CAPI VkQueue TS_CCALL tsVKContext_getQueue(TSVKContext self);
TS_CAPI VkCommandBuffer TS_CCALL tsVKContext_getCommand(TSVKContext self);
TS_CAPI uint32_t TS_CCALL tsVKContext_getFamily(TSVKContext self);
TS_CAPI uint32_t TS_CCALL tsVKContext_getNumQueues(TSVKContext self);
TS_CAPI uint32_t TS_CCALL tsVKContext_getQueueFlags(TSVKContext self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsVKContext_getQueueFamily(TSVKContext self, uint32_t index);
TS_CAPI void TS_CCALL tsVKContext_addContextExtension(const char *name);
TS_CAPI void TS_CCALL tsVKContext_addAdapterExtension(const char *name);
TS_CAPI void TS_CCALL tsVKContext_addAdapterFeatures(void *features);
TS_CAPI PFN_vkGetInstanceProcAddr TS_CCALL tsVKContext_getInstanceProcAddress(void);
TS_CAPI PFN_vkGetDeviceProcAddr TS_CCALL tsVKContext_getDeviceProcAddress(void);
TS_CAPI void* TS_CCALL tsVKContext_getProcAddress(const char *name);
TS_CAPI bool_t TS_CCALL tsVKContext_error(uint32_t result);

/// Tellusim::GLContext
TS_CAPI TSGLContext TS_CCALL tsGLContext_new(void);
TS_CAPI void TS_CCALL tsGLContext_delete(TSGLContext self);
TS_CAPI bool_t TS_CCALL tsGLContext_equalPtr(const TSGLContext self, const TSGLContext ptr);
TS_CAPI TSGLContext TS_CCALL tsGLContext_copyPtr(const TSGLContext self);
TS_CAPI TSGLContext TS_CCALL tsGLContext_clonePtr(const TSGLContext self);
TS_CAPI void TS_CCALL tsGLContext_clearPtr(TSGLContext self);
TS_CAPI void TS_CCALL tsGLContext_destroyPtr(TSGLContext self);
TS_CAPI void TS_CCALL tsGLContext_acquirePtr(TSGLContext self);
TS_CAPI void TS_CCALL tsGLContext_unacquirePtr(TSGLContext self);
TS_CAPI bool_t TS_CCALL tsGLContext_isValidPtr(const TSGLContext self);
TS_CAPI bool_t TS_CCALL tsGLContext_isOwnerPtr(const TSGLContext self);
TS_CAPI bool_t TS_CCALL tsGLContext_isConstPtr(const TSGLContext self);
TS_CAPI uint32_t TS_CCALL tsGLContext_getCountPtr(const TSGLContext self);
TS_CAPI const void* TS_CCALL tsGLContext_getInternalPtr(const TSGLContext self);
TS_CAPI bool_t TS_CCALL tsGLContext_equalContextPtr(const TSGLContext self, const TSContext base);
TS_CAPI TSGLContext TS_CCALL tsGLContext_castContextPtr(TSContext base);
TS_CAPI TSContext TS_CCALL tsGLContext_baseContextPtr(TSGLContext self);
TS_CAPI bool_t TS_CCALL tsGLContext_create(TSGLContext self, void *context);
TS_CAPI void* TS_CCALL tsGLContext_getGLDisplay(TSGLContext self);
TS_CAPI void* TS_CCALL tsGLContext_getGLVisual(TSGLContext self);
TS_CAPI void* TS_CCALL tsGLContext_getGLConfig(TSGLContext self);
TS_CAPI void* TS_CCALL tsGLContext_getGLSurface(TSGLContext self);
TS_CAPI void* TS_CCALL tsGLContext_getGLContext(TSGLContext self);
TS_CAPI void* TS_CCALL tsGLContext_getProcAddress(const char *name);
TS_CAPI bool_t TS_CCALL tsGLContext_error(uint32_t result);
TS_CAPI bool_t TS_CCALL tsGLContext_check(void);

/// Tellusim::GLESContext
TS_CAPI TSGLESContext TS_CCALL tsGLESContext_new(void);
TS_CAPI void TS_CCALL tsGLESContext_delete(TSGLESContext self);
TS_CAPI bool_t TS_CCALL tsGLESContext_equalPtr(const TSGLESContext self, const TSGLESContext ptr);
TS_CAPI TSGLESContext TS_CCALL tsGLESContext_copyPtr(const TSGLESContext self);
TS_CAPI TSGLESContext TS_CCALL tsGLESContext_clonePtr(const TSGLESContext self);
TS_CAPI void TS_CCALL tsGLESContext_clearPtr(TSGLESContext self);
TS_CAPI void TS_CCALL tsGLESContext_destroyPtr(TSGLESContext self);
TS_CAPI void TS_CCALL tsGLESContext_acquirePtr(TSGLESContext self);
TS_CAPI void TS_CCALL tsGLESContext_unacquirePtr(TSGLESContext self);
TS_CAPI bool_t TS_CCALL tsGLESContext_isValidPtr(const TSGLESContext self);
TS_CAPI bool_t TS_CCALL tsGLESContext_isOwnerPtr(const TSGLESContext self);
TS_CAPI bool_t TS_CCALL tsGLESContext_isConstPtr(const TSGLESContext self);
TS_CAPI uint32_t TS_CCALL tsGLESContext_getCountPtr(const TSGLESContext self);
TS_CAPI const void* TS_CCALL tsGLESContext_getInternalPtr(const TSGLESContext self);
TS_CAPI bool_t TS_CCALL tsGLESContext_equalContextPtr(const TSGLESContext self, const TSContext base);
TS_CAPI TSGLESContext TS_CCALL tsGLESContext_castContextPtr(TSContext base);
TS_CAPI TSContext TS_CCALL tsGLESContext_baseContextPtr(TSGLESContext self);
TS_CAPI bool_t TS_CCALL tsGLESContext_create(TSGLESContext self, void *context);
TS_CAPI void* TS_CCALL tsGLESContext_getGLESDisplay(TSGLESContext self);
TS_CAPI void* TS_CCALL tsGLESContext_getGLESConfig(TSGLESContext self);
TS_CAPI void* TS_CCALL tsGLESContext_getGLESContext(TSGLESContext self);
TS_CAPI void* TS_CCALL tsGLESContext_getProcAddress(const char *name);
TS_CAPI bool_t TS_CCALL tsGLESContext_error(uint32_t result);
TS_CAPI bool_t TS_CCALL tsGLESContext_check(void);

/// Tellusim::WGContext
TS_CAPI TSWGContext TS_CCALL tsWGContext_new(void);
TS_CAPI void TS_CCALL tsWGContext_delete(TSWGContext self);
TS_CAPI bool_t TS_CCALL tsWGContext_equalPtr(const TSWGContext self, const TSWGContext ptr);
TS_CAPI TSWGContext TS_CCALL tsWGContext_copyPtr(const TSWGContext self);
TS_CAPI TSWGContext TS_CCALL tsWGContext_clonePtr(const TSWGContext self);
TS_CAPI void TS_CCALL tsWGContext_clearPtr(TSWGContext self);
TS_CAPI void TS_CCALL tsWGContext_destroyPtr(TSWGContext self);
TS_CAPI void TS_CCALL tsWGContext_acquirePtr(TSWGContext self);
TS_CAPI void TS_CCALL tsWGContext_unacquirePtr(TSWGContext self);
TS_CAPI bool_t TS_CCALL tsWGContext_isValidPtr(const TSWGContext self);
TS_CAPI bool_t TS_CCALL tsWGContext_isOwnerPtr(const TSWGContext self);
TS_CAPI bool_t TS_CCALL tsWGContext_isConstPtr(const TSWGContext self);
TS_CAPI uint32_t TS_CCALL tsWGContext_getCountPtr(const TSWGContext self);
TS_CAPI const void* TS_CCALL tsWGContext_getInternalPtr(const TSWGContext self);
TS_CAPI bool_t TS_CCALL tsWGContext_equalContextPtr(const TSWGContext self, const TSContext base);
TS_CAPI TSWGContext TS_CCALL tsWGContext_castContextPtr(TSContext base);
TS_CAPI TSContext TS_CCALL tsWGContext_baseContextPtr(TSWGContext self);
TS_CAPI bool_t TS_CCALL tsWGContext_open(WGPUInstance instance, WGPUAdapter adapter, WGPUDevice device);
TS_CAPI bool_t TS_CCALL tsWGContext_create(TSWGContext self, WGPUInstance instance, WGPUAdapter adapter, WGPUDevice device);
TS_CAPI WGPUInstance TS_CCALL tsWGContext_getInstance(TSWGContext self);
TS_CAPI WGPUAdapter TS_CCALL tsWGContext_getAdapter(TSWGContext self);
TS_CAPI WGPUDevice TS_CCALL tsWGContext_getDevice(TSWGContext self);

/// Tellusim::CUContext
TS_CAPI TSCUContext TS_CCALL tsCUContext_new(void);
TS_CAPI void TS_CCALL tsCUContext_delete(TSCUContext self);
TS_CAPI bool_t TS_CCALL tsCUContext_equalPtr(const TSCUContext self, const TSCUContext ptr);
TS_CAPI TSCUContext TS_CCALL tsCUContext_copyPtr(const TSCUContext self);
TS_CAPI TSCUContext TS_CCALL tsCUContext_clonePtr(const TSCUContext self);
TS_CAPI void TS_CCALL tsCUContext_clearPtr(TSCUContext self);
TS_CAPI void TS_CCALL tsCUContext_destroyPtr(TSCUContext self);
TS_CAPI void TS_CCALL tsCUContext_acquirePtr(TSCUContext self);
TS_CAPI void TS_CCALL tsCUContext_unacquirePtr(TSCUContext self);
TS_CAPI bool_t TS_CCALL tsCUContext_isValidPtr(const TSCUContext self);
TS_CAPI bool_t TS_CCALL tsCUContext_isOwnerPtr(const TSCUContext self);
TS_CAPI bool_t TS_CCALL tsCUContext_isConstPtr(const TSCUContext self);
TS_CAPI uint32_t TS_CCALL tsCUContext_getCountPtr(const TSCUContext self);
TS_CAPI const void* TS_CCALL tsCUContext_getInternalPtr(const TSCUContext self);
TS_CAPI bool_t TS_CCALL tsCUContext_equalContextPtr(const TSCUContext self, const TSContext base);
TS_CAPI TSCUContext TS_CCALL tsCUContext_castContextPtr(TSContext base);
TS_CAPI TSContext TS_CCALL tsCUContext_baseContextPtr(TSCUContext self);
TS_CAPI int32_t TS_CCALL tsCUContext_getDevice(TSCUContext self);
TS_CAPI CUcontext TS_CCALL tsCUContext_getCUContext(TSCUContext self);
TS_CAPI CUstream TS_CCALL tsCUContext_getStream(TSCUContext self);
TS_CAPI void* TS_CCALL tsCUContext_getProcAddress(const char *name);
TS_CAPI bool_t TS_CCALL tsCUContext_error(uint32_t result);

/// Tellusim::HIPContext
TS_CAPI TSHIPContext TS_CCALL tsHIPContext_new(void);
TS_CAPI void TS_CCALL tsHIPContext_delete(TSHIPContext self);
TS_CAPI bool_t TS_CCALL tsHIPContext_equalPtr(const TSHIPContext self, const TSHIPContext ptr);
TS_CAPI TSHIPContext TS_CCALL tsHIPContext_copyPtr(const TSHIPContext self);
TS_CAPI TSHIPContext TS_CCALL tsHIPContext_clonePtr(const TSHIPContext self);
TS_CAPI void TS_CCALL tsHIPContext_clearPtr(TSHIPContext self);
TS_CAPI void TS_CCALL tsHIPContext_destroyPtr(TSHIPContext self);
TS_CAPI void TS_CCALL tsHIPContext_acquirePtr(TSHIPContext self);
TS_CAPI void TS_CCALL tsHIPContext_unacquirePtr(TSHIPContext self);
TS_CAPI bool_t TS_CCALL tsHIPContext_isValidPtr(const TSHIPContext self);
TS_CAPI bool_t TS_CCALL tsHIPContext_isOwnerPtr(const TSHIPContext self);
TS_CAPI bool_t TS_CCALL tsHIPContext_isConstPtr(const TSHIPContext self);
TS_CAPI uint32_t TS_CCALL tsHIPContext_getCountPtr(const TSHIPContext self);
TS_CAPI const void* TS_CCALL tsHIPContext_getInternalPtr(const TSHIPContext self);
TS_CAPI bool_t TS_CCALL tsHIPContext_equalContextPtr(const TSHIPContext self, const TSContext base);
TS_CAPI TSHIPContext TS_CCALL tsHIPContext_castContextPtr(TSContext base);
TS_CAPI TSContext TS_CCALL tsHIPContext_baseContextPtr(TSHIPContext self);
TS_CAPI int32_t TS_CCALL tsHIPContext_getDevice(TSHIPContext self);
TS_CAPI void* TS_CCALL tsHIPContext_getHIPContext(TSHIPContext self);
TS_CAPI void* TS_CCALL tsHIPContext_getStream(TSHIPContext self);
TS_CAPI void* TS_CCALL tsHIPContext_getProcAddress(const char *name);
TS_CAPI bool_t TS_CCALL tsHIPContext_error(uint32_t result);

/// Tellusim::Query
TS_CAPI TSQuery TS_CCALL tsQuery_new(void);
TS_CAPI void TS_CCALL tsQuery_delete(TSQuery self);
TS_CAPI bool_t TS_CCALL tsQuery_equalPtr(const TSQuery self, const TSQuery ptr);
TS_CAPI TSQuery TS_CCALL tsQuery_copyPtr(const TSQuery self);
TS_CAPI TSQuery TS_CCALL tsQuery_clonePtr(const TSQuery self);
TS_CAPI void TS_CCALL tsQuery_clearPtr(TSQuery self);
TS_CAPI void TS_CCALL tsQuery_destroyPtr(TSQuery self);
TS_CAPI void TS_CCALL tsQuery_acquirePtr(TSQuery self);
TS_CAPI void TS_CCALL tsQuery_unacquirePtr(TSQuery self);
TS_CAPI bool_t TS_CCALL tsQuery_isValidPtr(const TSQuery self);
TS_CAPI bool_t TS_CCALL tsQuery_isOwnerPtr(const TSQuery self);
TS_CAPI bool_t TS_CCALL tsQuery_isConstPtr(const TSQuery self);
TS_CAPI uint32_t TS_CCALL tsQuery_getCountPtr(const TSQuery self);
TS_CAPI const void* TS_CCALL tsQuery_getInternalPtr(const TSQuery self);
TS_CAPI TS_Platform TS_CCALL tsQuery_getPlatform(TSQuery self);
TS_CAPI const char* TS_CCALL tsQuery_getPlatformName(TSQuery self);
TS_CAPI uint32_t TS_CCALL tsQuery_getIndex(TSQuery self);
TS_CAPI void TS_CCALL tsQuery_clear(TSQuery self);
TS_CAPI bool_t TS_CCALL tsQuery_isCreated(TSQuery self);
TS_CAPI bool_t TS_CCALL tsQuery_isAvailable(TSQuery self);
TS_CAPI bool_t TS_CCALL tsQuery_isBegan(TSQuery self);
TS_CAPI bool_t TS_CCALL tsQuery_isEnded(TSQuery self);
TS_CAPI bool_t TS_CCALL tsQuery_create(TSQuery self, TS_QueryType type);
TS_CAPI TS_QueryType TS_CCALL tsQuery_getType(TSQuery self);
TS_CAPI const char* TS_CCALL tsQuery_getTypeName_QT(TS_QueryType type);
TS_CAPI const char* TS_CCALL tsQuery_getTypeName_c(TSQuery self);
TS_CAPI size_t TS_CCALL tsQuery_getTypeSize(TSQuery self);
TS_CAPI bool_t TS_CCALL tsQuery_isTime(TSQuery self);
TS_CAPI bool_t TS_CCALL tsQuery_isClock(TSQuery self);
TS_CAPI bool_t TS_CCALL tsQuery_isSamples(TSQuery self);
TS_CAPI bool_t TS_CCALL tsQuery_isSamples1(TSQuery self);
TS_CAPI bool_t TS_CCALL tsQuery_isStatistics(TSQuery self);
TS_CAPI bool_t TS_CCALL tsQuery_isTimeType(TSQuery self);
TS_CAPI bool_t TS_CCALL tsQuery_isSamplesType(TSQuery self);
TS_CAPI bool_t TS_CCALL tsQuery_get(TSQuery self, void *dest, size_t size, bool_t wait);
TS_CAPI uint64_t TS_CCALL tsQuery_getTime(TSQuery self, bool_t wait, uint8_t *status);
TS_CAPI uint32_t TS_CCALL tsQuery_getSamples(TSQuery self, bool_t wait, uint8_t *status);
TS_CAPI TSQueryStatistics TS_CCALL tsQuery_getStatistics(TSQuery self, bool_t wait, uint8_t *status);

/// Tellusim::FUQuery
TS_CAPI TSFUQuery TS_CCALL tsFUQuery_new(void);
TS_CAPI TSFUQuery TS_CCALL tsFUQuery_new_cAQb(const TSQuery *queries, uint32_t queries_size, bool_t owner);
TS_CAPI void TS_CCALL tsFUQuery_delete(TSFUQuery self);
TS_CAPI bool_t TS_CCALL tsFUQuery_equalPtr(const TSFUQuery self, const TSFUQuery ptr);
TS_CAPI TSFUQuery TS_CCALL tsFUQuery_copyPtr(const TSFUQuery self);
TS_CAPI TSFUQuery TS_CCALL tsFUQuery_clonePtr(const TSFUQuery self);
TS_CAPI void TS_CCALL tsFUQuery_clearPtr(TSFUQuery self);
TS_CAPI void TS_CCALL tsFUQuery_destroyPtr(TSFUQuery self);
TS_CAPI void TS_CCALL tsFUQuery_acquirePtr(TSFUQuery self);
TS_CAPI void TS_CCALL tsFUQuery_unacquirePtr(TSFUQuery self);
TS_CAPI bool_t TS_CCALL tsFUQuery_isValidPtr(const TSFUQuery self);
TS_CAPI bool_t TS_CCALL tsFUQuery_isOwnerPtr(const TSFUQuery self);
TS_CAPI bool_t TS_CCALL tsFUQuery_isConstPtr(const TSFUQuery self);
TS_CAPI uint32_t TS_CCALL tsFUQuery_getCountPtr(const TSFUQuery self);
TS_CAPI const void* TS_CCALL tsFUQuery_getInternalPtr(const TSFUQuery self);
TS_CAPI bool_t TS_CCALL tsFUQuery_equalQueryPtr(const TSFUQuery self, const TSQuery base);
TS_CAPI TSFUQuery TS_CCALL tsFUQuery_castQueryPtr(TSQuery base);
TS_CAPI TSQuery TS_CCALL tsFUQuery_baseQueryPtr(TSFUQuery self);
TS_CAPI void TS_CCALL tsFUQuery_setMask(TSFUQuery self, uint32_t mask);
TS_CAPI uint32_t TS_CCALL tsFUQuery_getMask(TSFUQuery self);
TS_CAPI uint32_t TS_CCALL tsFUQuery_getNumQueries(TSFUQuery self);
TS_CAPI TSQuery TS_CCALL tsFUQuery_getQuery_cu(TSFUQuery self, uint32_t index);
TS_CAPI TSQuery TS_CCALL tsFUQuery_getQuery_u(TSFUQuery self, uint32_t index);

/// Tellusim::Fence
TS_CAPI TSFence TS_CCALL tsFence_new(void);
TS_CAPI void TS_CCALL tsFence_delete(TSFence self);
TS_CAPI bool_t TS_CCALL tsFence_equalPtr(const TSFence self, const TSFence ptr);
TS_CAPI TSFence TS_CCALL tsFence_copyPtr(const TSFence self);
TS_CAPI TSFence TS_CCALL tsFence_clonePtr(const TSFence self);
TS_CAPI void TS_CCALL tsFence_clearPtr(TSFence self);
TS_CAPI void TS_CCALL tsFence_destroyPtr(TSFence self);
TS_CAPI void TS_CCALL tsFence_acquirePtr(TSFence self);
TS_CAPI void TS_CCALL tsFence_unacquirePtr(TSFence self);
TS_CAPI bool_t TS_CCALL tsFence_isValidPtr(const TSFence self);
TS_CAPI bool_t TS_CCALL tsFence_isOwnerPtr(const TSFence self);
TS_CAPI bool_t TS_CCALL tsFence_isConstPtr(const TSFence self);
TS_CAPI uint32_t TS_CCALL tsFence_getCountPtr(const TSFence self);
TS_CAPI const void* TS_CCALL tsFence_getInternalPtr(const TSFence self);
TS_CAPI TS_Platform TS_CCALL tsFence_getPlatform(TSFence self);
TS_CAPI const char* TS_CCALL tsFence_getPlatformName(TSFence self);
TS_CAPI uint32_t TS_CCALL tsFence_getIndex(TSFence self);
TS_CAPI void TS_CCALL tsFence_clear(TSFence self);
TS_CAPI bool_t TS_CCALL tsFence_isCreated(TSFence self);
TS_CAPI bool_t TS_CCALL tsFence_create(TSFence self, TS_FenceFlags flags);
TS_CAPI TS_FenceFlags TS_CCALL tsFence_getFlags(TSFence self);
TS_CAPI bool_t TS_CCALL tsFence_hasFlag(TSFence self, TS_FenceFlags flags);
TS_CAPI bool_t TS_CCALL tsFence_hasFlags(TSFence self, TS_FenceFlags flags);
TS_CAPI TSString TS_CCALL tsFence_getFlagsName(TSFence self);
TS_CAPI TSString TS_CCALL tsFence_getDescription(TSFence self);

/// Tellusim::VKFence
TS_CAPI TSVKFence TS_CCALL tsVKFence_new(void);
TS_CAPI void TS_CCALL tsVKFence_delete(TSVKFence self);
TS_CAPI bool_t TS_CCALL tsVKFence_equalPtr(const TSVKFence self, const TSVKFence ptr);
TS_CAPI TSVKFence TS_CCALL tsVKFence_copyPtr(const TSVKFence self);
TS_CAPI TSVKFence TS_CCALL tsVKFence_clonePtr(const TSVKFence self);
TS_CAPI void TS_CCALL tsVKFence_clearPtr(TSVKFence self);
TS_CAPI void TS_CCALL tsVKFence_destroyPtr(TSVKFence self);
TS_CAPI void TS_CCALL tsVKFence_acquirePtr(TSVKFence self);
TS_CAPI void TS_CCALL tsVKFence_unacquirePtr(TSVKFence self);
TS_CAPI bool_t TS_CCALL tsVKFence_isValidPtr(const TSVKFence self);
TS_CAPI bool_t TS_CCALL tsVKFence_isOwnerPtr(const TSVKFence self);
TS_CAPI bool_t TS_CCALL tsVKFence_isConstPtr(const TSVKFence self);
TS_CAPI uint32_t TS_CCALL tsVKFence_getCountPtr(const TSVKFence self);
TS_CAPI const void* TS_CCALL tsVKFence_getInternalPtr(const TSVKFence self);
TS_CAPI bool_t TS_CCALL tsVKFence_equalFencePtr(const TSVKFence self, const TSFence base);
TS_CAPI TSVKFence TS_CCALL tsVKFence_castFencePtr(TSFence base);
TS_CAPI TSFence TS_CCALL tsVKFence_baseFencePtr(TSVKFence self);
TS_CAPI VkFence TS_CCALL tsVKFence_getVKFence(TSVKFence self);
TS_CAPI VkSemaphore TS_CCALL tsVKFence_getSemaphore(TSVKFence self);
TS_CAPI void* TS_CCALL tsVKFence_getSharedHandle(TSVKFence self);

/// Tellusim::FUFence
TS_CAPI TSFUFence TS_CCALL tsFUFence_new(void);
TS_CAPI TSFUFence TS_CCALL tsFUFence_new_cAFb(const TSFence *fences, uint32_t fences_size, bool_t owner);
TS_CAPI void TS_CCALL tsFUFence_delete(TSFUFence self);
TS_CAPI bool_t TS_CCALL tsFUFence_equalPtr(const TSFUFence self, const TSFUFence ptr);
TS_CAPI TSFUFence TS_CCALL tsFUFence_copyPtr(const TSFUFence self);
TS_CAPI TSFUFence TS_CCALL tsFUFence_clonePtr(const TSFUFence self);
TS_CAPI void TS_CCALL tsFUFence_clearPtr(TSFUFence self);
TS_CAPI void TS_CCALL tsFUFence_destroyPtr(TSFUFence self);
TS_CAPI void TS_CCALL tsFUFence_acquirePtr(TSFUFence self);
TS_CAPI void TS_CCALL tsFUFence_unacquirePtr(TSFUFence self);
TS_CAPI bool_t TS_CCALL tsFUFence_isValidPtr(const TSFUFence self);
TS_CAPI bool_t TS_CCALL tsFUFence_isOwnerPtr(const TSFUFence self);
TS_CAPI bool_t TS_CCALL tsFUFence_isConstPtr(const TSFUFence self);
TS_CAPI uint32_t TS_CCALL tsFUFence_getCountPtr(const TSFUFence self);
TS_CAPI const void* TS_CCALL tsFUFence_getInternalPtr(const TSFUFence self);
TS_CAPI bool_t TS_CCALL tsFUFence_equalFencePtr(const TSFUFence self, const TSFence base);
TS_CAPI TSFUFence TS_CCALL tsFUFence_castFencePtr(TSFence base);
TS_CAPI TSFence TS_CCALL tsFUFence_baseFencePtr(TSFUFence self);
TS_CAPI void TS_CCALL tsFUFence_setMask(TSFUFence self, uint32_t mask);
TS_CAPI uint32_t TS_CCALL tsFUFence_getMask(TSFUFence self);
TS_CAPI uint32_t TS_CCALL tsFUFence_getNumFences(TSFUFence self);
TS_CAPI TSFence TS_CCALL tsFUFence_getFence_cu(TSFUFence self, uint32_t index);
TS_CAPI TSFence TS_CCALL tsFUFence_getFence_u(TSFUFence self, uint32_t index);

/// Tellusim::Shader
TS_CAPI TSShader TS_CCALL tsShader_new(void);
TS_CAPI void TS_CCALL tsShader_delete(TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_equalPtr(const TSShader self, const TSShader ptr);
TS_CAPI TSShader TS_CCALL tsShader_copyPtr(const TSShader self);
TS_CAPI TSShader TS_CCALL tsShader_clonePtr(const TSShader self);
TS_CAPI void TS_CCALL tsShader_clearPtr(TSShader self);
TS_CAPI void TS_CCALL tsShader_destroyPtr(TSShader self);
TS_CAPI void TS_CCALL tsShader_acquirePtr(TSShader self);
TS_CAPI void TS_CCALL tsShader_unacquirePtr(TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_isValidPtr(const TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_isOwnerPtr(const TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_isConstPtr(const TSShader self);
TS_CAPI uint32_t TS_CCALL tsShader_getCountPtr(const TSShader self);
TS_CAPI const void* TS_CCALL tsShader_getInternalPtr(const TSShader self);
TS_CAPI TS_Platform TS_CCALL tsShader_getPlatform(TSShader self);
TS_CAPI const char* TS_CCALL tsShader_getPlatformName(TSShader self);
TS_CAPI uint32_t TS_CCALL tsShader_getIndex(TSShader self);
TS_CAPI void TS_CCALL tsShader_clear(TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_isCreated(TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_saveState(TSShader self, TSStream stream);
TS_CAPI TS_ShaderType TS_CCALL tsShader_getType(TSShader self);
TS_CAPI const char* TS_CCALL tsShader_getTypeName_ST(TS_ShaderType type);
TS_CAPI const char* TS_CCALL tsShader_getTypeName_c(TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_isVertex(TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_isControl(TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_isEvaluate(TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_isGeometry(TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_isFragment(TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_isCompute(TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_isTask(TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_isMesh(TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_isRayGen(TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_isRayMiss(TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_isClosest(TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_isFirstHit(TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_isIntersection(TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_isCallable(TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_isGraphicsType(TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_isTessellationType(TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_isTracingType(TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_isMeshType(TSShader self);
TS_CAPI TSString TS_CCALL tsShader_getName(TSShader self);
TS_CAPI TSString TS_CCALL tsShader_getMacros(TSShader self);
TS_CAPI void TS_CCALL tsShader_setSamplerOffset(TSShader self, int32_t offset);
TS_CAPI int32_t TS_CCALL tsShader_getSamplerOffset(TSShader self);
TS_CAPI void TS_CCALL tsShader_setTextureOffset(TSShader self, int32_t offset);
TS_CAPI int32_t TS_CCALL tsShader_getTextureOffset(TSShader self);
TS_CAPI void TS_CCALL tsShader_setSurfaceOffset(TSShader self, int32_t offset);
TS_CAPI int32_t TS_CCALL tsShader_getSurfaceOffset(TSShader self);
TS_CAPI void TS_CCALL tsShader_setUniformOffset(TSShader self, int32_t offset);
TS_CAPI int32_t TS_CCALL tsShader_getUniformOffset(TSShader self);
TS_CAPI void TS_CCALL tsShader_setStorageOffset(TSShader self, int32_t offset);
TS_CAPI int32_t TS_CCALL tsShader_getStorageOffset(TSShader self);
TS_CAPI void TS_CCALL tsShader_setTracingOffset(TSShader self, int32_t offset);
TS_CAPI int32_t TS_CCALL tsShader_getTracingOffset(TSShader self);
TS_CAPI void TS_CCALL tsShader_setTexelOffset(TSShader self, int32_t offset);
TS_CAPI int32_t TS_CCALL tsShader_getTexelOffset(TSShader self);
TS_CAPI void TS_CCALL tsShader_setTableOffset(TSShader self, int32_t offset);
TS_CAPI int32_t TS_CCALL tsShader_getTableOffset(TSShader self);
TS_CAPI void TS_CCALL tsShader_setPatchSize(TSShader self, uint32_t size);
TS_CAPI uint32_t TS_CCALL tsShader_getPatchSize(TSShader self);
TS_CAPI void TS_CCALL tsShader_setInputSize(TSShader self, uint32_t size);
TS_CAPI uint32_t TS_CCALL tsShader_getInputSize(TSShader self);
TS_CAPI void TS_CCALL tsShader_setOutputSize(TSShader self, uint32_t size);
TS_CAPI uint32_t TS_CCALL tsShader_getOutputSize(TSShader self);
TS_CAPI bool_t TS_CCALL tsShader_load_STss(TSShader self, TS_ShaderType type, const char *name, const char *format);
TS_CAPI bool_t TS_CCALL tsShader_create_STss(TSShader self, TS_ShaderType type, const char *src, const char *format);
TS_CAPI bool_t TS_CCALL tsShader_load_STscSspu(TSShader self, TS_ShaderType type, const char *name, const TSString macros, const char **includes, uint32_t size);
TS_CAPI bool_t TS_CCALL tsShader_create_STscSspu(TSShader self, TS_ShaderType type, const char *src, const TSString macros, const char **includes, uint32_t size);
TS_CAPI bool_t TS_CCALL tsShader_loadGLSL_STss(TSShader self, TS_ShaderType type, const char *name, const char *format);
TS_CAPI bool_t TS_CCALL tsShader_createGLSL_STss(TSShader self, TS_ShaderType type, const char *src, const char *format);
TS_CAPI bool_t TS_CCALL tsShader_loadGLSL_STscSspu(TSShader self, TS_ShaderType type, const char *name, const TSString macros, const char **includes, uint32_t size);
TS_CAPI bool_t TS_CCALL tsShader_createGLSL_STscSspu(TSShader self, TS_ShaderType type, const char *src, const TSString macros, const char **includes, uint32_t size);
TS_CAPI bool_t TS_CCALL tsShader_loadSPIRV(TSShader self, TS_ShaderType type, const char *name);
TS_CAPI bool_t TS_CCALL tsShader_createSPIRV(TSShader self, TS_ShaderType type, const uint32_t *data, uint32_t data_size);
TS_CAPI bool_t TS_CCALL tsShader_hasCache(void);
TS_CAPI bool_t TS_CCALL tsShader_setCache(const char *name);
TS_CAPI bool_t TS_CCALL tsShader_loadCache(const TSString hash, TSStream stream);
TS_CAPI bool_t TS_CCALL tsShader_saveCache(const TSString hash, TSStream stream);
TS_CAPI void TS_CCALL tsShader_clearCache(void);
TS_CAPI bool_t TS_CCALL tsShader_isMacro(const char *name);
TS_CAPI bool_t TS_CCALL tsShader_setMacro_si(const char *name, int32_t value);
TS_CAPI bool_t TS_CCALL tsShader_setMacro_su(const char *name, uint32_t value);
TS_CAPI bool_t TS_CCALL tsShader_setMacro_ss(const char *name, const char *value);
TS_CAPI bool_t TS_CCALL tsShader_setMacros(const char *macros);
TS_CAPI bool_t TS_CCALL tsShader_removeMacro(const char *name);
TS_CAPI void TS_CCALL tsShader_clearMacros(void);
TS_CAPI bool_t TS_CCALL tsShader_isInclude(const char *name);
TS_CAPI bool_t TS_CCALL tsShader_setInclude(const char *name, const TSString src);
TS_CAPI bool_t TS_CCALL tsShader_removeInclude(const char *name);
TS_CAPI void TS_CCALL tsShader_clearIncludes(void);
TS_CAPI TSString TS_CCALL tsShader_preprocessor_ss(const char *src, const char *format);
TS_CAPI TSString TS_CCALL tsShader_preprocessor_scSspu(const char *src, const TSString macros, const char **includes, uint32_t size);

/// Tellusim::ShaderCompiler
TS_CAPI TSShaderCompiler TS_CCALL tsShaderCompiler_new(void);
TS_CAPI void TS_CCALL tsShaderCompiler_delete(TSShaderCompiler self);
TS_CAPI bool_t TS_CCALL tsShaderCompiler_equalPtr(const TSShaderCompiler self, const TSShaderCompiler ptr);
TS_CAPI TSShaderCompiler TS_CCALL tsShaderCompiler_copyPtr(const TSShaderCompiler self);
TS_CAPI TSShaderCompiler TS_CCALL tsShaderCompiler_clonePtr(const TSShaderCompiler self);
TS_CAPI void TS_CCALL tsShaderCompiler_clearPtr(TSShaderCompiler self);
TS_CAPI void TS_CCALL tsShaderCompiler_destroyPtr(TSShaderCompiler self);
TS_CAPI void TS_CCALL tsShaderCompiler_acquirePtr(TSShaderCompiler self);
TS_CAPI void TS_CCALL tsShaderCompiler_unacquirePtr(TSShaderCompiler self);
TS_CAPI bool_t TS_CCALL tsShaderCompiler_isValidPtr(const TSShaderCompiler self);
TS_CAPI bool_t TS_CCALL tsShaderCompiler_isOwnerPtr(const TSShaderCompiler self);
TS_CAPI bool_t TS_CCALL tsShaderCompiler_isConstPtr(const TSShaderCompiler self);
TS_CAPI uint32_t TS_CCALL tsShaderCompiler_getCountPtr(const TSShaderCompiler self);
TS_CAPI const void* TS_CCALL tsShaderCompiler_getInternalPtr(const TSShaderCompiler self);
TS_CAPI bool_t TS_CCALL tsShaderCompiler_equalShaderPtr(const TSShaderCompiler self, const TSShader base);
TS_CAPI TSShaderCompiler TS_CCALL tsShaderCompiler_castShaderPtr(TSShader base);
TS_CAPI TSShader TS_CCALL tsShaderCompiler_baseShaderPtr(TSShaderCompiler self);
TS_CAPI void TS_CCALL tsShaderCompiler_setFlags(TSShaderCompiler self, TS_ShaderCompilerFlags flags);
TS_CAPI TS_ShaderCompilerFlags TS_CCALL tsShaderCompiler_getFlags(TSShaderCompiler self);
TS_CAPI bool_t TS_CCALL tsShaderCompiler_getBinary(TSShaderCompiler self, TSStream stream, TS_Platform platform);
TS_CAPI TSString TS_CCALL tsShaderCompiler_getSource(TSShaderCompiler self, TS_Platform platform);

/// Tellusim::D3D12Shader
TS_CAPI TSD3D12Shader TS_CCALL tsD3D12Shader_new(void);
TS_CAPI void TS_CCALL tsD3D12Shader_delete(TSD3D12Shader self);
TS_CAPI bool_t TS_CCALL tsD3D12Shader_equalPtr(const TSD3D12Shader self, const TSD3D12Shader ptr);
TS_CAPI TSD3D12Shader TS_CCALL tsD3D12Shader_copyPtr(const TSD3D12Shader self);
TS_CAPI TSD3D12Shader TS_CCALL tsD3D12Shader_clonePtr(const TSD3D12Shader self);
TS_CAPI void TS_CCALL tsD3D12Shader_clearPtr(TSD3D12Shader self);
TS_CAPI void TS_CCALL tsD3D12Shader_destroyPtr(TSD3D12Shader self);
TS_CAPI void TS_CCALL tsD3D12Shader_acquirePtr(TSD3D12Shader self);
TS_CAPI void TS_CCALL tsD3D12Shader_unacquirePtr(TSD3D12Shader self);
TS_CAPI bool_t TS_CCALL tsD3D12Shader_isValidPtr(const TSD3D12Shader self);
TS_CAPI bool_t TS_CCALL tsD3D12Shader_isOwnerPtr(const TSD3D12Shader self);
TS_CAPI bool_t TS_CCALL tsD3D12Shader_isConstPtr(const TSD3D12Shader self);
TS_CAPI uint32_t TS_CCALL tsD3D12Shader_getCountPtr(const TSD3D12Shader self);
TS_CAPI const void* TS_CCALL tsD3D12Shader_getInternalPtr(const TSD3D12Shader self);
TS_CAPI bool_t TS_CCALL tsD3D12Shader_equalShaderPtr(const TSD3D12Shader self, const TSShader base);
TS_CAPI TSD3D12Shader TS_CCALL tsD3D12Shader_castShaderPtr(TSShader base);
TS_CAPI TSShader TS_CCALL tsD3D12Shader_baseShaderPtr(TSD3D12Shader self);
TS_CAPI ID3DBlob* TS_CCALL tsD3D12Shader_getShaderBlob(TSD3D12Shader self);

/// Tellusim::D3D11Shader
TS_CAPI TSD3D11Shader TS_CCALL tsD3D11Shader_new(void);
TS_CAPI void TS_CCALL tsD3D11Shader_delete(TSD3D11Shader self);
TS_CAPI bool_t TS_CCALL tsD3D11Shader_equalPtr(const TSD3D11Shader self, const TSD3D11Shader ptr);
TS_CAPI TSD3D11Shader TS_CCALL tsD3D11Shader_copyPtr(const TSD3D11Shader self);
TS_CAPI TSD3D11Shader TS_CCALL tsD3D11Shader_clonePtr(const TSD3D11Shader self);
TS_CAPI void TS_CCALL tsD3D11Shader_clearPtr(TSD3D11Shader self);
TS_CAPI void TS_CCALL tsD3D11Shader_destroyPtr(TSD3D11Shader self);
TS_CAPI void TS_CCALL tsD3D11Shader_acquirePtr(TSD3D11Shader self);
TS_CAPI void TS_CCALL tsD3D11Shader_unacquirePtr(TSD3D11Shader self);
TS_CAPI bool_t TS_CCALL tsD3D11Shader_isValidPtr(const TSD3D11Shader self);
TS_CAPI bool_t TS_CCALL tsD3D11Shader_isOwnerPtr(const TSD3D11Shader self);
TS_CAPI bool_t TS_CCALL tsD3D11Shader_isConstPtr(const TSD3D11Shader self);
TS_CAPI uint32_t TS_CCALL tsD3D11Shader_getCountPtr(const TSD3D11Shader self);
TS_CAPI const void* TS_CCALL tsD3D11Shader_getInternalPtr(const TSD3D11Shader self);
TS_CAPI bool_t TS_CCALL tsD3D11Shader_equalShaderPtr(const TSD3D11Shader self, const TSShader base);
TS_CAPI TSD3D11Shader TS_CCALL tsD3D11Shader_castShaderPtr(TSShader base);
TS_CAPI TSShader TS_CCALL tsD3D11Shader_baseShaderPtr(TSD3D11Shader self);
TS_CAPI void* TS_CCALL tsD3D11Shader_getD3D11Shader(TSD3D11Shader self);
TS_CAPI ID3DBlob* TS_CCALL tsD3D11Shader_getShaderBlob(TSD3D11Shader self);

/// Tellusim::MTLShader
TS_CAPI TSMTLShader TS_CCALL tsMTLShader_new(void);
TS_CAPI void TS_CCALL tsMTLShader_delete(TSMTLShader self);
TS_CAPI bool_t TS_CCALL tsMTLShader_equalPtr(const TSMTLShader self, const TSMTLShader ptr);
TS_CAPI TSMTLShader TS_CCALL tsMTLShader_copyPtr(const TSMTLShader self);
TS_CAPI TSMTLShader TS_CCALL tsMTLShader_clonePtr(const TSMTLShader self);
TS_CAPI void TS_CCALL tsMTLShader_clearPtr(TSMTLShader self);
TS_CAPI void TS_CCALL tsMTLShader_destroyPtr(TSMTLShader self);
TS_CAPI void TS_CCALL tsMTLShader_acquirePtr(TSMTLShader self);
TS_CAPI void TS_CCALL tsMTLShader_unacquirePtr(TSMTLShader self);
TS_CAPI bool_t TS_CCALL tsMTLShader_isValidPtr(const TSMTLShader self);
TS_CAPI bool_t TS_CCALL tsMTLShader_isOwnerPtr(const TSMTLShader self);
TS_CAPI bool_t TS_CCALL tsMTLShader_isConstPtr(const TSMTLShader self);
TS_CAPI uint32_t TS_CCALL tsMTLShader_getCountPtr(const TSMTLShader self);
TS_CAPI const void* TS_CCALL tsMTLShader_getInternalPtr(const TSMTLShader self);
TS_CAPI bool_t TS_CCALL tsMTLShader_equalShaderPtr(const TSMTLShader self, const TSShader base);
TS_CAPI TSMTLShader TS_CCALL tsMTLShader_castShaderPtr(TSShader base);
TS_CAPI TSShader TS_CCALL tsMTLShader_baseShaderPtr(TSMTLShader self);
TS_CAPI void TS_CCALL tsMTLShader_setIndirect(TSMTLShader self, bool_t enabled);
TS_CAPI bool_t TS_CCALL tsMTLShader_isIndirect(TSMTLShader self);
TS_CAPI void* TS_CCALL tsMTLShader_getLibrary(TSMTLShader self);
TS_CAPI void* TS_CCALL tsMTLShader_getFunction(TSMTLShader self);

/// Tellusim::VKShader
TS_CAPI TSVKShader TS_CCALL tsVKShader_new(void);
TS_CAPI void TS_CCALL tsVKShader_delete(TSVKShader self);
TS_CAPI bool_t TS_CCALL tsVKShader_equalPtr(const TSVKShader self, const TSVKShader ptr);
TS_CAPI TSVKShader TS_CCALL tsVKShader_copyPtr(const TSVKShader self);
TS_CAPI TSVKShader TS_CCALL tsVKShader_clonePtr(const TSVKShader self);
TS_CAPI void TS_CCALL tsVKShader_clearPtr(TSVKShader self);
TS_CAPI void TS_CCALL tsVKShader_destroyPtr(TSVKShader self);
TS_CAPI void TS_CCALL tsVKShader_acquirePtr(TSVKShader self);
TS_CAPI void TS_CCALL tsVKShader_unacquirePtr(TSVKShader self);
TS_CAPI bool_t TS_CCALL tsVKShader_isValidPtr(const TSVKShader self);
TS_CAPI bool_t TS_CCALL tsVKShader_isOwnerPtr(const TSVKShader self);
TS_CAPI bool_t TS_CCALL tsVKShader_isConstPtr(const TSVKShader self);
TS_CAPI uint32_t TS_CCALL tsVKShader_getCountPtr(const TSVKShader self);
TS_CAPI const void* TS_CCALL tsVKShader_getInternalPtr(const TSVKShader self);
TS_CAPI bool_t TS_CCALL tsVKShader_equalShaderPtr(const TSVKShader self, const TSShader base);
TS_CAPI TSVKShader TS_CCALL tsVKShader_castShaderPtr(TSShader base);
TS_CAPI TSShader TS_CCALL tsVKShader_baseShaderPtr(TSVKShader self);
TS_CAPI VkShaderModule TS_CCALL tsVKShader_getModule(TSVKShader self);

/// Tellusim::GLShader
TS_CAPI TSGLShader TS_CCALL tsGLShader_new(void);
TS_CAPI void TS_CCALL tsGLShader_delete(TSGLShader self);
TS_CAPI bool_t TS_CCALL tsGLShader_equalPtr(const TSGLShader self, const TSGLShader ptr);
TS_CAPI TSGLShader TS_CCALL tsGLShader_copyPtr(const TSGLShader self);
TS_CAPI TSGLShader TS_CCALL tsGLShader_clonePtr(const TSGLShader self);
TS_CAPI void TS_CCALL tsGLShader_clearPtr(TSGLShader self);
TS_CAPI void TS_CCALL tsGLShader_destroyPtr(TSGLShader self);
TS_CAPI void TS_CCALL tsGLShader_acquirePtr(TSGLShader self);
TS_CAPI void TS_CCALL tsGLShader_unacquirePtr(TSGLShader self);
TS_CAPI bool_t TS_CCALL tsGLShader_isValidPtr(const TSGLShader self);
TS_CAPI bool_t TS_CCALL tsGLShader_isOwnerPtr(const TSGLShader self);
TS_CAPI bool_t TS_CCALL tsGLShader_isConstPtr(const TSGLShader self);
TS_CAPI uint32_t TS_CCALL tsGLShader_getCountPtr(const TSGLShader self);
TS_CAPI const void* TS_CCALL tsGLShader_getInternalPtr(const TSGLShader self);
TS_CAPI bool_t TS_CCALL tsGLShader_equalShaderPtr(const TSGLShader self, const TSShader base);
TS_CAPI TSGLShader TS_CCALL tsGLShader_castShaderPtr(TSShader base);
TS_CAPI TSShader TS_CCALL tsGLShader_baseShaderPtr(TSGLShader self);
TS_CAPI bool_t TS_CCALL tsGLShader_attachShader(TSGLShader self, uint32_t program_id);
TS_CAPI uint32_t TS_CCALL tsGLShader_getShaderType(TSGLShader self);
TS_CAPI uint32_t TS_CCALL tsGLShader_getShaderID(TSGLShader self);

/// Tellusim::GLESShader
TS_CAPI TSGLESShader TS_CCALL tsGLESShader_new(void);
TS_CAPI void TS_CCALL tsGLESShader_delete(TSGLESShader self);
TS_CAPI bool_t TS_CCALL tsGLESShader_equalPtr(const TSGLESShader self, const TSGLESShader ptr);
TS_CAPI TSGLESShader TS_CCALL tsGLESShader_copyPtr(const TSGLESShader self);
TS_CAPI TSGLESShader TS_CCALL tsGLESShader_clonePtr(const TSGLESShader self);
TS_CAPI void TS_CCALL tsGLESShader_clearPtr(TSGLESShader self);
TS_CAPI void TS_CCALL tsGLESShader_destroyPtr(TSGLESShader self);
TS_CAPI void TS_CCALL tsGLESShader_acquirePtr(TSGLESShader self);
TS_CAPI void TS_CCALL tsGLESShader_unacquirePtr(TSGLESShader self);
TS_CAPI bool_t TS_CCALL tsGLESShader_isValidPtr(const TSGLESShader self);
TS_CAPI bool_t TS_CCALL tsGLESShader_isOwnerPtr(const TSGLESShader self);
TS_CAPI bool_t TS_CCALL tsGLESShader_isConstPtr(const TSGLESShader self);
TS_CAPI uint32_t TS_CCALL tsGLESShader_getCountPtr(const TSGLESShader self);
TS_CAPI const void* TS_CCALL tsGLESShader_getInternalPtr(const TSGLESShader self);
TS_CAPI bool_t TS_CCALL tsGLESShader_equalShaderPtr(const TSGLESShader self, const TSShader base);
TS_CAPI TSGLESShader TS_CCALL tsGLESShader_castShaderPtr(TSShader base);
TS_CAPI TSShader TS_CCALL tsGLESShader_baseShaderPtr(TSGLESShader self);
TS_CAPI bool_t TS_CCALL tsGLESShader_attachShader(TSGLESShader self, uint32_t program_id);
TS_CAPI uint32_t TS_CCALL tsGLESShader_getShaderType(TSGLESShader self);
TS_CAPI uint32_t TS_CCALL tsGLESShader_getShaderID(TSGLESShader self);

/// Tellusim::CUShader
TS_CAPI TSCUShader TS_CCALL tsCUShader_new(void);
TS_CAPI void TS_CCALL tsCUShader_delete(TSCUShader self);
TS_CAPI bool_t TS_CCALL tsCUShader_equalPtr(const TSCUShader self, const TSCUShader ptr);
TS_CAPI TSCUShader TS_CCALL tsCUShader_copyPtr(const TSCUShader self);
TS_CAPI TSCUShader TS_CCALL tsCUShader_clonePtr(const TSCUShader self);
TS_CAPI void TS_CCALL tsCUShader_clearPtr(TSCUShader self);
TS_CAPI void TS_CCALL tsCUShader_destroyPtr(TSCUShader self);
TS_CAPI void TS_CCALL tsCUShader_acquirePtr(TSCUShader self);
TS_CAPI void TS_CCALL tsCUShader_unacquirePtr(TSCUShader self);
TS_CAPI bool_t TS_CCALL tsCUShader_isValidPtr(const TSCUShader self);
TS_CAPI bool_t TS_CCALL tsCUShader_isOwnerPtr(const TSCUShader self);
TS_CAPI bool_t TS_CCALL tsCUShader_isConstPtr(const TSCUShader self);
TS_CAPI uint32_t TS_CCALL tsCUShader_getCountPtr(const TSCUShader self);
TS_CAPI const void* TS_CCALL tsCUShader_getInternalPtr(const TSCUShader self);
TS_CAPI bool_t TS_CCALL tsCUShader_equalShaderPtr(const TSCUShader self, const TSShader base);
TS_CAPI TSCUShader TS_CCALL tsCUShader_castShaderPtr(TSShader base);
TS_CAPI TSShader TS_CCALL tsCUShader_baseShaderPtr(TSCUShader self);
TS_CAPI CUmodule TS_CCALL tsCUShader_getModule(TSCUShader self);
TS_CAPI CUfunction TS_CCALL tsCUShader_getFunction(TSCUShader self);

/// Tellusim::HIPShader
TS_CAPI TSHIPShader TS_CCALL tsHIPShader_new(void);
TS_CAPI void TS_CCALL tsHIPShader_delete(TSHIPShader self);
TS_CAPI bool_t TS_CCALL tsHIPShader_equalPtr(const TSHIPShader self, const TSHIPShader ptr);
TS_CAPI TSHIPShader TS_CCALL tsHIPShader_copyPtr(const TSHIPShader self);
TS_CAPI TSHIPShader TS_CCALL tsHIPShader_clonePtr(const TSHIPShader self);
TS_CAPI void TS_CCALL tsHIPShader_clearPtr(TSHIPShader self);
TS_CAPI void TS_CCALL tsHIPShader_destroyPtr(TSHIPShader self);
TS_CAPI void TS_CCALL tsHIPShader_acquirePtr(TSHIPShader self);
TS_CAPI void TS_CCALL tsHIPShader_unacquirePtr(TSHIPShader self);
TS_CAPI bool_t TS_CCALL tsHIPShader_isValidPtr(const TSHIPShader self);
TS_CAPI bool_t TS_CCALL tsHIPShader_isOwnerPtr(const TSHIPShader self);
TS_CAPI bool_t TS_CCALL tsHIPShader_isConstPtr(const TSHIPShader self);
TS_CAPI uint32_t TS_CCALL tsHIPShader_getCountPtr(const TSHIPShader self);
TS_CAPI const void* TS_CCALL tsHIPShader_getInternalPtr(const TSHIPShader self);
TS_CAPI bool_t TS_CCALL tsHIPShader_equalShaderPtr(const TSHIPShader self, const TSShader base);
TS_CAPI TSHIPShader TS_CCALL tsHIPShader_castShaderPtr(TSShader base);
TS_CAPI TSShader TS_CCALL tsHIPShader_baseShaderPtr(TSHIPShader self);
TS_CAPI void* TS_CCALL tsHIPShader_getModule(TSHIPShader self);
TS_CAPI void* TS_CCALL tsHIPShader_getFunction(TSHIPShader self);

/// Tellusim::FUShader
TS_CAPI TSFUShader TS_CCALL tsFUShader_new(void);
TS_CAPI TSFUShader TS_CCALL tsFUShader_new_cASb(const TSShader *shaders, uint32_t shaders_size, bool_t owner);
TS_CAPI void TS_CCALL tsFUShader_delete(TSFUShader self);
TS_CAPI bool_t TS_CCALL tsFUShader_equalPtr(const TSFUShader self, const TSFUShader ptr);
TS_CAPI TSFUShader TS_CCALL tsFUShader_copyPtr(const TSFUShader self);
TS_CAPI TSFUShader TS_CCALL tsFUShader_clonePtr(const TSFUShader self);
TS_CAPI void TS_CCALL tsFUShader_clearPtr(TSFUShader self);
TS_CAPI void TS_CCALL tsFUShader_destroyPtr(TSFUShader self);
TS_CAPI void TS_CCALL tsFUShader_acquirePtr(TSFUShader self);
TS_CAPI void TS_CCALL tsFUShader_unacquirePtr(TSFUShader self);
TS_CAPI bool_t TS_CCALL tsFUShader_isValidPtr(const TSFUShader self);
TS_CAPI bool_t TS_CCALL tsFUShader_isOwnerPtr(const TSFUShader self);
TS_CAPI bool_t TS_CCALL tsFUShader_isConstPtr(const TSFUShader self);
TS_CAPI uint32_t TS_CCALL tsFUShader_getCountPtr(const TSFUShader self);
TS_CAPI const void* TS_CCALL tsFUShader_getInternalPtr(const TSFUShader self);
TS_CAPI bool_t TS_CCALL tsFUShader_equalShaderPtr(const TSFUShader self, const TSShader base);
TS_CAPI TSFUShader TS_CCALL tsFUShader_castShaderPtr(TSShader base);
TS_CAPI TSShader TS_CCALL tsFUShader_baseShaderPtr(TSFUShader self);
TS_CAPI void TS_CCALL tsFUShader_setMask(TSFUShader self, uint32_t mask);
TS_CAPI uint32_t TS_CCALL tsFUShader_getMask(TSFUShader self);
TS_CAPI uint32_t TS_CCALL tsFUShader_getNumShaders(TSFUShader self);
TS_CAPI TSShader TS_CCALL tsFUShader_getShader_cu(TSFUShader self, uint32_t index);
TS_CAPI TSShader TS_CCALL tsFUShader_getShader_u(TSFUShader self, uint32_t index);

/// Tellusim::Sampler
TS_CAPI TSSampler TS_CCALL tsSampler_new(void);
TS_CAPI void TS_CCALL tsSampler_delete(TSSampler self);
TS_CAPI bool_t TS_CCALL tsSampler_equalPtr(const TSSampler self, const TSSampler ptr);
TS_CAPI TSSampler TS_CCALL tsSampler_copyPtr(const TSSampler self);
TS_CAPI TSSampler TS_CCALL tsSampler_clonePtr(const TSSampler self);
TS_CAPI void TS_CCALL tsSampler_clearPtr(TSSampler self);
TS_CAPI void TS_CCALL tsSampler_destroyPtr(TSSampler self);
TS_CAPI void TS_CCALL tsSampler_acquirePtr(TSSampler self);
TS_CAPI void TS_CCALL tsSampler_unacquirePtr(TSSampler self);
TS_CAPI bool_t TS_CCALL tsSampler_isValidPtr(const TSSampler self);
TS_CAPI bool_t TS_CCALL tsSampler_isOwnerPtr(const TSSampler self);
TS_CAPI bool_t TS_CCALL tsSampler_isConstPtr(const TSSampler self);
TS_CAPI uint32_t TS_CCALL tsSampler_getCountPtr(const TSSampler self);
TS_CAPI const void* TS_CCALL tsSampler_getInternalPtr(const TSSampler self);
TS_CAPI TS_Platform TS_CCALL tsSampler_getPlatform(TSSampler self);
TS_CAPI const char* TS_CCALL tsSampler_getPlatformName(TSSampler self);
TS_CAPI uint32_t TS_CCALL tsSampler_getIndex(TSSampler self);
TS_CAPI void TS_CCALL tsSampler_clear(TSSampler self);
TS_CAPI bool_t TS_CCALL tsSampler_isCreated(TSSampler self);
TS_CAPI bool_t TS_CCALL tsSampler_create(TSSampler self);
TS_CAPI void TS_CCALL tsSampler_setParameters(TSSampler self, const TSSampler sampler);
TS_CAPI void TS_CCALL tsSampler_setFilter(TSSampler self, TS_SamplerFilter filter);
TS_CAPI TS_SamplerFilter TS_CCALL tsSampler_getFilter(TSSampler self);
TS_CAPI bool_t TS_CCALL tsSampler_isPointFilter(TSSampler self);
TS_CAPI void TS_CCALL tsSampler_setAnisotropy(TSSampler self, uint32_t anisotropy);
TS_CAPI uint32_t TS_CCALL tsSampler_getAnisotropy(TSSampler self);
TS_CAPI bool_t TS_CCALL tsSampler_hasAnisotropy(TSSampler self);
TS_CAPI void TS_CCALL tsSampler_setWrapMode_SWM(TSSampler self, TS_SamplerWrapMode mode);
TS_CAPI void TS_CCALL tsSampler_setWrapMode_SWMSWMSWM(TSSampler self, TS_SamplerWrapMode mode_s, TS_SamplerWrapMode mode_t, TS_SamplerWrapMode mode_r);
TS_CAPI void TS_CCALL tsSampler_setWrapModeS(TSSampler self, TS_SamplerWrapMode mode);
TS_CAPI TS_SamplerWrapMode TS_CCALL tsSampler_getWrapModeS(TSSampler self);
TS_CAPI void TS_CCALL tsSampler_setWrapModeT(TSSampler self, TS_SamplerWrapMode mode);
TS_CAPI TS_SamplerWrapMode TS_CCALL tsSampler_getWrapModeT(TSSampler self);
TS_CAPI void TS_CCALL tsSampler_setWrapModeR(TSSampler self, TS_SamplerWrapMode mode);
TS_CAPI TS_SamplerWrapMode TS_CCALL tsSampler_getWrapModeR(TSSampler self);
TS_CAPI void TS_CCALL tsSampler_setLod(TSSampler self, float32_t min, float32_t max, float32_t bias);
TS_CAPI void TS_CCALL tsSampler_setLodMin(TSSampler self, float32_t min);
TS_CAPI float32_t TS_CCALL tsSampler_getLodMin(TSSampler self);
TS_CAPI void TS_CCALL tsSampler_setLodMax(TSSampler self, float32_t max);
TS_CAPI float32_t TS_CCALL tsSampler_getLodMax(TSSampler self);
TS_CAPI void TS_CCALL tsSampler_setLodBias(TSSampler self, float32_t bias);
TS_CAPI float32_t TS_CCALL tsSampler_getLodBias(TSSampler self);
TS_CAPI void TS_CCALL tsSampler_setBorderColor_cC(TSSampler self, const TSColor *color);
TS_CAPI void TS_CCALL tsSampler_setBorderColor_ffff(TSSampler self, float32_t r, float32_t g, float32_t b, float32_t a);
TS_CAPI TSColor TS_CCALL tsSampler_getBorderColor(TSSampler self);
TS_CAPI void TS_CCALL tsSampler_setCompareFunc(TSSampler self, TS_SamplerCompareFunc func);
TS_CAPI TS_SamplerCompareFunc TS_CCALL tsSampler_getCompareFunc(TSSampler self);
TS_CAPI void TS_CCALL tsSampler_setReductionMode(TSSampler self, TS_SamplerReductionMode mode);
TS_CAPI TS_SamplerReductionMode TS_CCALL tsSampler_getReductionMode(TSSampler self);

/// Tellusim::MTLSampler
TS_CAPI TSMTLSampler TS_CCALL tsMTLSampler_new(void);
TS_CAPI void TS_CCALL tsMTLSampler_delete(TSMTLSampler self);
TS_CAPI bool_t TS_CCALL tsMTLSampler_equalPtr(const TSMTLSampler self, const TSMTLSampler ptr);
TS_CAPI TSMTLSampler TS_CCALL tsMTLSampler_copyPtr(const TSMTLSampler self);
TS_CAPI TSMTLSampler TS_CCALL tsMTLSampler_clonePtr(const TSMTLSampler self);
TS_CAPI void TS_CCALL tsMTLSampler_clearPtr(TSMTLSampler self);
TS_CAPI void TS_CCALL tsMTLSampler_destroyPtr(TSMTLSampler self);
TS_CAPI void TS_CCALL tsMTLSampler_acquirePtr(TSMTLSampler self);
TS_CAPI void TS_CCALL tsMTLSampler_unacquirePtr(TSMTLSampler self);
TS_CAPI bool_t TS_CCALL tsMTLSampler_isValidPtr(const TSMTLSampler self);
TS_CAPI bool_t TS_CCALL tsMTLSampler_isOwnerPtr(const TSMTLSampler self);
TS_CAPI bool_t TS_CCALL tsMTLSampler_isConstPtr(const TSMTLSampler self);
TS_CAPI uint32_t TS_CCALL tsMTLSampler_getCountPtr(const TSMTLSampler self);
TS_CAPI const void* TS_CCALL tsMTLSampler_getInternalPtr(const TSMTLSampler self);
TS_CAPI bool_t TS_CCALL tsMTLSampler_equalSamplerPtr(const TSMTLSampler self, const TSSampler base);
TS_CAPI TSMTLSampler TS_CCALL tsMTLSampler_castSamplerPtr(TSSampler base);
TS_CAPI TSSampler TS_CCALL tsMTLSampler_baseSamplerPtr(TSMTLSampler self);
TS_CAPI void TS_CCALL tsMTLSampler_setIndirect(TSMTLSampler self, bool_t enabled);
TS_CAPI bool_t TS_CCALL tsMTLSampler_isIndirect(TSMTLSampler self);

/// Tellusim::FUSampler
TS_CAPI TSFUSampler TS_CCALL tsFUSampler_new(void);
TS_CAPI TSFUSampler TS_CCALL tsFUSampler_new_cASb(const TSSampler *samplers, uint32_t samplers_size, bool_t owner);
TS_CAPI void TS_CCALL tsFUSampler_delete(TSFUSampler self);
TS_CAPI bool_t TS_CCALL tsFUSampler_equalPtr(const TSFUSampler self, const TSFUSampler ptr);
TS_CAPI TSFUSampler TS_CCALL tsFUSampler_copyPtr(const TSFUSampler self);
TS_CAPI TSFUSampler TS_CCALL tsFUSampler_clonePtr(const TSFUSampler self);
TS_CAPI void TS_CCALL tsFUSampler_clearPtr(TSFUSampler self);
TS_CAPI void TS_CCALL tsFUSampler_destroyPtr(TSFUSampler self);
TS_CAPI void TS_CCALL tsFUSampler_acquirePtr(TSFUSampler self);
TS_CAPI void TS_CCALL tsFUSampler_unacquirePtr(TSFUSampler self);
TS_CAPI bool_t TS_CCALL tsFUSampler_isValidPtr(const TSFUSampler self);
TS_CAPI bool_t TS_CCALL tsFUSampler_isOwnerPtr(const TSFUSampler self);
TS_CAPI bool_t TS_CCALL tsFUSampler_isConstPtr(const TSFUSampler self);
TS_CAPI uint32_t TS_CCALL tsFUSampler_getCountPtr(const TSFUSampler self);
TS_CAPI const void* TS_CCALL tsFUSampler_getInternalPtr(const TSFUSampler self);
TS_CAPI bool_t TS_CCALL tsFUSampler_equalSamplerPtr(const TSFUSampler self, const TSSampler base);
TS_CAPI TSFUSampler TS_CCALL tsFUSampler_castSamplerPtr(TSSampler base);
TS_CAPI TSSampler TS_CCALL tsFUSampler_baseSamplerPtr(TSFUSampler self);
TS_CAPI void TS_CCALL tsFUSampler_setMask(TSFUSampler self, uint32_t mask);
TS_CAPI uint32_t TS_CCALL tsFUSampler_getMask(TSFUSampler self);
TS_CAPI uint32_t TS_CCALL tsFUSampler_getNumSamplers(TSFUSampler self);
TS_CAPI TSSampler TS_CCALL tsFUSampler_getSampler_cu(TSFUSampler self, uint32_t index);
TS_CAPI TSSampler TS_CCALL tsFUSampler_getSampler_u(TSFUSampler self, uint32_t index);

/// Tellusim::Texture
TS_CAPI TSTexture TS_CCALL tsTexture_new(void);
TS_CAPI void TS_CCALL tsTexture_delete(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_equalPtr(const TSTexture self, const TSTexture ptr);
TS_CAPI TSTexture TS_CCALL tsTexture_copyPtr(const TSTexture self);
TS_CAPI TSTexture TS_CCALL tsTexture_clonePtr(const TSTexture self);
TS_CAPI void TS_CCALL tsTexture_clearPtr(TSTexture self);
TS_CAPI void TS_CCALL tsTexture_destroyPtr(TSTexture self);
TS_CAPI void TS_CCALL tsTexture_acquirePtr(TSTexture self);
TS_CAPI void TS_CCALL tsTexture_unacquirePtr(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isValidPtr(const TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isOwnerPtr(const TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isConstPtr(const TSTexture self);
TS_CAPI uint32_t TS_CCALL tsTexture_getCountPtr(const TSTexture self);
TS_CAPI const void* TS_CCALL tsTexture_getInternalPtr(const TSTexture self);
TS_CAPI TS_Platform TS_CCALL tsTexture_getPlatform(TSTexture self);
TS_CAPI const char* TS_CCALL tsTexture_getPlatformName(TSTexture self);
TS_CAPI uint32_t TS_CCALL tsTexture_getIndex(TSTexture self);
TS_CAPI void TS_CCALL tsTexture_clear(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isCreated(TSTexture self);
TS_CAPI void TS_CCALL tsTexture_setName(TSTexture self, const char *name);
TS_CAPI TSString TS_CCALL tsTexture_getName(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_create(TSTexture self, TS_TextureType type, TS_Format format, const TSSize *size, uint32_t layers, TS_TextureFlags flags);
TS_CAPI bool_t TS_CCALL tsTexture_create2D_FuTF(TSTexture self, TS_Format format, uint32_t size, TS_TextureFlags flags);
TS_CAPI bool_t TS_CCALL tsTexture_create3D_FuTF(TSTexture self, TS_Format format, uint32_t size, TS_TextureFlags flags);
TS_CAPI bool_t TS_CCALL tsTexture_createCube_FuTF(TSTexture self, TS_Format format, uint32_t size, TS_TextureFlags flags);
TS_CAPI bool_t TS_CCALL tsTexture_create2D_FuuTF(TSTexture self, TS_Format format, uint32_t width, uint32_t height, TS_TextureFlags flags);
TS_CAPI bool_t TS_CCALL tsTexture_create3D_FuuuTF(TSTexture self, TS_Format format, uint32_t width, uint32_t height, uint32_t depth, TS_TextureFlags flags);
TS_CAPI bool_t TS_CCALL tsTexture_create2D_FuuuTF(TSTexture self, TS_Format format, uint32_t width, uint32_t height, uint32_t layers, TS_TextureFlags flags);
TS_CAPI bool_t TS_CCALL tsTexture_createCube_FuuTF(TSTexture self, TS_Format format, uint32_t size, uint32_t layers, TS_TextureFlags flags);
TS_CAPI TS_TextureType TS_CCALL tsTexture_getType(TSTexture self);
TS_CAPI const char* TS_CCALL tsTexture_getTypeName_TT(TS_TextureType type);
TS_CAPI const char* TS_CCALL tsTexture_getTypeName_c(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_is2DType(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_is3DType(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isCubeType(TSTexture self);
TS_CAPI TS_Format TS_CCALL tsTexture_getFormat(TSTexture self);
TS_CAPI const char* TS_CCALL tsTexture_getFormatName(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isColorFormat(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isDepthFormat(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isPixelFormat(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isPlainFormat(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isMixedFormat(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isBlockFormat(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isStencilFormat(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isNormFormat(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isSRGBFormat(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isFloatFormat(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isSignedFormat(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isUnsignedFormat(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isIntegerFormat(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isi8Format(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isu8Format(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_is8BitFormat(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isi16Format(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isu16Format(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isf16Format(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_is16BitFormat(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isi32Format(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isu32Format(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isf32Format(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_is32BitFormat(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isi64Format(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isu64Format(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isf64Format(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_is64BitFormat(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isBC15Format(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isBC67Format(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isETC2Format(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_isASTCFormat(TSTexture self);
TS_CAPI uint32_t TS_CCALL tsTexture_getComponents(TSTexture self);
TS_CAPI uint32_t TS_CCALL tsTexture_getPixelSize(TSTexture self);
TS_CAPI uint32_t TS_CCALL tsTexture_getBlockSize(TSTexture self);
TS_CAPI uint32_t TS_CCALL tsTexture_getBlockWidth(TSTexture self);
TS_CAPI uint32_t TS_CCALL tsTexture_getBlockHeight(TSTexture self);
TS_CAPI TS_TextureFlags TS_CCALL tsTexture_getFlags(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_hasFlag(TSTexture self, TS_TextureFlags flags);
TS_CAPI bool_t TS_CCALL tsTexture_hasFlags(TSTexture self, TS_TextureFlags flags);
TS_CAPI TSString TS_CCALL tsTexture_getFlagsName(TSTexture self);
TS_CAPI uint32_t TS_CCALL tsTexture_getMultisample(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_hasMultisample(TSTexture self);
TS_CAPI uint32_t TS_CCALL tsTexture_getWidth_c(TSTexture self);
TS_CAPI uint32_t TS_CCALL tsTexture_getHeight_c(TSTexture self);
TS_CAPI uint32_t TS_CCALL tsTexture_getDepth_c(TSTexture self);
TS_CAPI uint32_t TS_CCALL tsTexture_getFaces(TSTexture self);
TS_CAPI uint32_t TS_CCALL tsTexture_getLayers(TSTexture self);
TS_CAPI uint32_t TS_CCALL tsTexture_getMipmaps(TSTexture self);
TS_CAPI uint32_t TS_CCALL tsTexture_findMipmap(TSTexture self, const TSSize *size);
TS_CAPI uint32_t TS_CCALL tsTexture_getWidth_cu(TSTexture self, uint32_t mipmap);
TS_CAPI uint32_t TS_CCALL tsTexture_getHeight_cu(TSTexture self, uint32_t mipmap);
TS_CAPI uint32_t TS_CCALL tsTexture_getDepth_cu(TSTexture self, uint32_t mipmap);
TS_CAPI bool_t TS_CCALL tsTexture_hasFaces(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_hasLayers(TSTexture self);
TS_CAPI bool_t TS_CCALL tsTexture_hasMipmaps(TSTexture self);
TS_CAPI TSSize TS_CCALL tsTexture_getSize_c(TSTexture self);
TS_CAPI TSRegion TS_CCALL tsTexture_getRegion_c(TSTexture self);
TS_CAPI TSSlice TS_CCALL tsTexture_getSlice_c(TSTexture self);
TS_CAPI TSSize TS_CCALL tsTexture_getSize_cu(TSTexture self, uint32_t mipmap);
TS_CAPI TSRegion TS_CCALL tsTexture_getRegion_cu(TSTexture self, uint32_t mipmap);
TS_CAPI TSSlice TS_CCALL tsTexture_getSlice_cu(TSTexture self, uint32_t mipmap);
TS_CAPI uint32_t TS_CCALL tsTexture_getTileWidth(TSTexture self);
TS_CAPI uint32_t TS_CCALL tsTexture_getTileHeight(TSTexture self);
TS_CAPI uint32_t TS_CCALL tsTexture_getTileDepth(TSTexture self);
TS_CAPI uint32_t TS_CCALL tsTexture_getTileMipmaps(TSTexture self);
TS_CAPI TSSize TS_CCALL tsTexture_getTileSize(TSTexture self);
TS_CAPI TSString TS_CCALL tsTexture_getDescription(TSTexture self);
TS_CAPI size_t TS_CCALL tsTexture_getMemory(TSTexture self);

/// Tellusim::TextureTable
TS_CAPI TSTextureTable TS_CCALL tsTextureTable_new(void);
TS_CAPI void TS_CCALL tsTextureTable_delete(TSTextureTable self);
TS_CAPI bool_t TS_CCALL tsTextureTable_equalPtr(const TSTextureTable self, const TSTextureTable ptr);
TS_CAPI TSTextureTable TS_CCALL tsTextureTable_copyPtr(const TSTextureTable self);
TS_CAPI TSTextureTable TS_CCALL tsTextureTable_clonePtr(const TSTextureTable self);
TS_CAPI void TS_CCALL tsTextureTable_clearPtr(TSTextureTable self);
TS_CAPI void TS_CCALL tsTextureTable_destroyPtr(TSTextureTable self);
TS_CAPI void TS_CCALL tsTextureTable_acquirePtr(TSTextureTable self);
TS_CAPI void TS_CCALL tsTextureTable_unacquirePtr(TSTextureTable self);
TS_CAPI bool_t TS_CCALL tsTextureTable_isValidPtr(const TSTextureTable self);
TS_CAPI bool_t TS_CCALL tsTextureTable_isOwnerPtr(const TSTextureTable self);
TS_CAPI bool_t TS_CCALL tsTextureTable_isConstPtr(const TSTextureTable self);
TS_CAPI uint32_t TS_CCALL tsTextureTable_getCountPtr(const TSTextureTable self);
TS_CAPI const void* TS_CCALL tsTextureTable_getInternalPtr(const TSTextureTable self);
TS_CAPI TS_Platform TS_CCALL tsTextureTable_getPlatform(TSTextureTable self);
TS_CAPI const char* TS_CCALL tsTextureTable_getPlatformName(TSTextureTable self);
TS_CAPI uint32_t TS_CCALL tsTextureTable_getIndex(TSTextureTable self);
TS_CAPI void TS_CCALL tsTextureTable_clear(TSTextureTable self);
TS_CAPI bool_t TS_CCALL tsTextureTable_isCreated(TSTextureTable self);
TS_CAPI void TS_CCALL tsTextureTable_setName(TSTextureTable self, const char *name);
TS_CAPI TSString TS_CCALL tsTextureTable_getName(TSTextureTable self);
TS_CAPI bool_t TS_CCALL tsTextureTable_create(TSTextureTable self, TS_TextureType type, uint32_t size);
TS_CAPI TS_TextureType TS_CCALL tsTextureTable_getType(TSTextureTable self);
TS_CAPI const char* TS_CCALL tsTextureTable_getTypeName(TSTextureTable self);
TS_CAPI uint32_t TS_CCALL tsTextureTable_getSize(TSTextureTable self);
TS_CAPI TSTexture TS_CCALL tsTextureTable_get(TSTextureTable self, uint32_t index);
TS_CAPI bool_t TS_CCALL tsTextureTable_isOwner(TSTextureTable self, uint32_t index);
TS_CAPI size_t TS_CCALL tsTextureTable_getMemory(TSTextureTable self);

/// Tellusim::D3D12Texture
TS_CAPI TSD3D12Texture TS_CCALL tsD3D12Texture_new(void);
TS_CAPI void TS_CCALL tsD3D12Texture_delete(TSD3D12Texture self);
TS_CAPI bool_t TS_CCALL tsD3D12Texture_equalPtr(const TSD3D12Texture self, const TSD3D12Texture ptr);
TS_CAPI TSD3D12Texture TS_CCALL tsD3D12Texture_copyPtr(const TSD3D12Texture self);
TS_CAPI TSD3D12Texture TS_CCALL tsD3D12Texture_clonePtr(const TSD3D12Texture self);
TS_CAPI void TS_CCALL tsD3D12Texture_clearPtr(TSD3D12Texture self);
TS_CAPI void TS_CCALL tsD3D12Texture_destroyPtr(TSD3D12Texture self);
TS_CAPI void TS_CCALL tsD3D12Texture_acquirePtr(TSD3D12Texture self);
TS_CAPI void TS_CCALL tsD3D12Texture_unacquirePtr(TSD3D12Texture self);
TS_CAPI bool_t TS_CCALL tsD3D12Texture_isValidPtr(const TSD3D12Texture self);
TS_CAPI bool_t TS_CCALL tsD3D12Texture_isOwnerPtr(const TSD3D12Texture self);
TS_CAPI bool_t TS_CCALL tsD3D12Texture_isConstPtr(const TSD3D12Texture self);
TS_CAPI uint32_t TS_CCALL tsD3D12Texture_getCountPtr(const TSD3D12Texture self);
TS_CAPI const void* TS_CCALL tsD3D12Texture_getInternalPtr(const TSD3D12Texture self);
TS_CAPI bool_t TS_CCALL tsD3D12Texture_equalTexturePtr(const TSD3D12Texture self, const TSTexture base);
TS_CAPI TSD3D12Texture TS_CCALL tsD3D12Texture_castTexturePtr(TSTexture base);
TS_CAPI TSTexture TS_CCALL tsD3D12Texture_baseTexturePtr(TSD3D12Texture self);
TS_CAPI bool_t TS_CCALL tsD3D12Texture_create(TSD3D12Texture self, TS_TextureType type, ID3D12Resource *texture, uint32_t state, TS_TextureFlags flags, TS_Format format);
TS_CAPI uint32_t TS_CCALL tsD3D12Texture_getDXGIFormat(TSD3D12Texture self);
TS_CAPI ID3D12Resource* TS_CCALL tsD3D12Texture_getD3D12Texture(TSD3D12Texture self);
TS_CAPI size_t TS_CCALL tsD3D12Texture_getShaderResourceView(TSD3D12Texture self);
TS_CAPI size_t TS_CCALL tsD3D12Texture_getRenderTargetView(TSD3D12Texture self);
TS_CAPI size_t TS_CCALL tsD3D12Texture_getDepthStencilView(TSD3D12Texture self);
TS_CAPI size_t TS_CCALL tsD3D12Texture_getUnorderedAccessView(TSD3D12Texture self);
TS_CAPI void TS_CCALL tsD3D12Texture_setTextureState(TSD3D12Texture self, uint32_t state);
TS_CAPI uint32_t TS_CCALL tsD3D12Texture_getTextureState(TSD3D12Texture self);
TS_CAPI void* TS_CCALL tsD3D12Texture_getSharedHandle(TSD3D12Texture self);
TS_CAPI void* TS_CCALL tsD3D12Texture_getInteropHandle(TSD3D12Texture self);

/// Tellusim::D3D11Texture
TS_CAPI TSD3D11Texture TS_CCALL tsD3D11Texture_new(void);
TS_CAPI void TS_CCALL tsD3D11Texture_delete(TSD3D11Texture self);
TS_CAPI bool_t TS_CCALL tsD3D11Texture_equalPtr(const TSD3D11Texture self, const TSD3D11Texture ptr);
TS_CAPI TSD3D11Texture TS_CCALL tsD3D11Texture_copyPtr(const TSD3D11Texture self);
TS_CAPI TSD3D11Texture TS_CCALL tsD3D11Texture_clonePtr(const TSD3D11Texture self);
TS_CAPI void TS_CCALL tsD3D11Texture_clearPtr(TSD3D11Texture self);
TS_CAPI void TS_CCALL tsD3D11Texture_destroyPtr(TSD3D11Texture self);
TS_CAPI void TS_CCALL tsD3D11Texture_acquirePtr(TSD3D11Texture self);
TS_CAPI void TS_CCALL tsD3D11Texture_unacquirePtr(TSD3D11Texture self);
TS_CAPI bool_t TS_CCALL tsD3D11Texture_isValidPtr(const TSD3D11Texture self);
TS_CAPI bool_t TS_CCALL tsD3D11Texture_isOwnerPtr(const TSD3D11Texture self);
TS_CAPI bool_t TS_CCALL tsD3D11Texture_isConstPtr(const TSD3D11Texture self);
TS_CAPI uint32_t TS_CCALL tsD3D11Texture_getCountPtr(const TSD3D11Texture self);
TS_CAPI const void* TS_CCALL tsD3D11Texture_getInternalPtr(const TSD3D11Texture self);
TS_CAPI bool_t TS_CCALL tsD3D11Texture_equalTexturePtr(const TSD3D11Texture self, const TSTexture base);
TS_CAPI TSD3D11Texture TS_CCALL tsD3D11Texture_castTexturePtr(TSTexture base);
TS_CAPI TSTexture TS_CCALL tsD3D11Texture_baseTexturePtr(TSD3D11Texture self);
TS_CAPI bool_t TS_CCALL tsD3D11Texture_create(TSD3D11Texture self, TS_TextureType type, ID3D11Texture2D *texture, TS_TextureFlags flags, TS_Format format);
TS_CAPI uint32_t TS_CCALL tsD3D11Texture_getDXGIFormat(TSD3D11Texture self);
TS_CAPI ID3D11Texture2D* TS_CCALL tsD3D11Texture_getD3D11Texture(TSD3D11Texture self);
TS_CAPI ID3D11ShaderResourceView* TS_CCALL tsD3D11Texture_getShaderResourceView(TSD3D11Texture self);
TS_CAPI ID3D11RenderTargetView* TS_CCALL tsD3D11Texture_getRenderTargetView(TSD3D11Texture self);
TS_CAPI ID3D11DepthStencilView* TS_CCALL tsD3D11Texture_getDepthStencilView(TSD3D11Texture self);
TS_CAPI ID3D11UnorderedAccessView* TS_CCALL tsD3D11Texture_getUnorderedAccessView(TSD3D11Texture self);
TS_CAPI void* TS_CCALL tsD3D11Texture_getInteropHandle(TSD3D11Texture self);

/// Tellusim::MTLTexture
TS_CAPI TSMTLTexture TS_CCALL tsMTLTexture_new(void);
TS_CAPI void TS_CCALL tsMTLTexture_delete(TSMTLTexture self);
TS_CAPI bool_t TS_CCALL tsMTLTexture_equalPtr(const TSMTLTexture self, const TSMTLTexture ptr);
TS_CAPI TSMTLTexture TS_CCALL tsMTLTexture_copyPtr(const TSMTLTexture self);
TS_CAPI TSMTLTexture TS_CCALL tsMTLTexture_clonePtr(const TSMTLTexture self);
TS_CAPI void TS_CCALL tsMTLTexture_clearPtr(TSMTLTexture self);
TS_CAPI void TS_CCALL tsMTLTexture_destroyPtr(TSMTLTexture self);
TS_CAPI void TS_CCALL tsMTLTexture_acquirePtr(TSMTLTexture self);
TS_CAPI void TS_CCALL tsMTLTexture_unacquirePtr(TSMTLTexture self);
TS_CAPI bool_t TS_CCALL tsMTLTexture_isValidPtr(const TSMTLTexture self);
TS_CAPI bool_t TS_CCALL tsMTLTexture_isOwnerPtr(const TSMTLTexture self);
TS_CAPI bool_t TS_CCALL tsMTLTexture_isConstPtr(const TSMTLTexture self);
TS_CAPI uint32_t TS_CCALL tsMTLTexture_getCountPtr(const TSMTLTexture self);
TS_CAPI const void* TS_CCALL tsMTLTexture_getInternalPtr(const TSMTLTexture self);
TS_CAPI bool_t TS_CCALL tsMTLTexture_equalTexturePtr(const TSMTLTexture self, const TSTexture base);
TS_CAPI TSMTLTexture TS_CCALL tsMTLTexture_castTexturePtr(TSTexture base);
TS_CAPI TSTexture TS_CCALL tsMTLTexture_baseTexturePtr(TSMTLTexture self);
TS_CAPI bool_t TS_CCALL tsMTLTexture_create(TSMTLTexture self, void *texture, TS_TextureFlags flags, TS_Format format);
TS_CAPI uint32_t TS_CCALL tsMTLTexture_getPixelFormat(TSMTLTexture self);
TS_CAPI uint32_t TS_CCALL tsMTLTexture_getTextureType(TSMTLTexture self);
TS_CAPI void* TS_CCALL tsMTLTexture_getMTLTexture(TSMTLTexture self);
TS_CAPI void* TS_CCALL tsMTLTexture_getMTLBuffer(TSMTLTexture self);
TS_CAPI void* TS_CCALL tsMTLTexture_getSharedPtr(TSMTLTexture self);

/// Tellusim::VKTexture
TS_CAPI TSVKTexture TS_CCALL tsVKTexture_new(void);
TS_CAPI void TS_CCALL tsVKTexture_delete(TSVKTexture self);
TS_CAPI bool_t TS_CCALL tsVKTexture_equalPtr(const TSVKTexture self, const TSVKTexture ptr);
TS_CAPI TSVKTexture TS_CCALL tsVKTexture_copyPtr(const TSVKTexture self);
TS_CAPI TSVKTexture TS_CCALL tsVKTexture_clonePtr(const TSVKTexture self);
TS_CAPI void TS_CCALL tsVKTexture_clearPtr(TSVKTexture self);
TS_CAPI void TS_CCALL tsVKTexture_destroyPtr(TSVKTexture self);
TS_CAPI void TS_CCALL tsVKTexture_acquirePtr(TSVKTexture self);
TS_CAPI void TS_CCALL tsVKTexture_unacquirePtr(TSVKTexture self);
TS_CAPI bool_t TS_CCALL tsVKTexture_isValidPtr(const TSVKTexture self);
TS_CAPI bool_t TS_CCALL tsVKTexture_isOwnerPtr(const TSVKTexture self);
TS_CAPI bool_t TS_CCALL tsVKTexture_isConstPtr(const TSVKTexture self);
TS_CAPI uint32_t TS_CCALL tsVKTexture_getCountPtr(const TSVKTexture self);
TS_CAPI const void* TS_CCALL tsVKTexture_getInternalPtr(const TSVKTexture self);
TS_CAPI bool_t TS_CCALL tsVKTexture_equalTexturePtr(const TSVKTexture self, const TSTexture base);
TS_CAPI TSVKTexture TS_CCALL tsVKTexture_castTexturePtr(TSTexture base);
TS_CAPI TSTexture TS_CCALL tsVKTexture_baseTexturePtr(TSVKTexture self);
TS_CAPI bool_t TS_CCALL tsVKTexture_create(TSVKTexture self, TS_TextureType type, uint32_t format, VkImage texture, uint32_t layout, TS_TextureFlags flags, TS_Format texture_format);
TS_CAPI uint32_t TS_CCALL tsVKTexture_getPixelFormat(TSVKTexture self);
TS_CAPI VkImage TS_CCALL tsVKTexture_getVKTexture(TSVKTexture self);
TS_CAPI VkImageView TS_CCALL tsVKTexture_getTextureView(TSVKTexture self);
TS_CAPI void TS_CCALL tsVKTexture_setTextureLayout(TSVKTexture self, uint32_t layout);
TS_CAPI uint32_t TS_CCALL tsVKTexture_getTextureLayout(TSVKTexture self);
TS_CAPI void TS_CCALL tsVKTexture_getTextureRange(TSVKTexture self, void *range, const TSSlice *slice);
TS_CAPI void* TS_CCALL tsVKTexture_getSharedPtr(TSVKTexture self);
TS_CAPI void* TS_CCALL tsVKTexture_getInteropHandle(TSVKTexture self);

/// Tellusim::GLTexture
TS_CAPI TSGLTexture TS_CCALL tsGLTexture_new(void);
TS_CAPI void TS_CCALL tsGLTexture_delete(TSGLTexture self);
TS_CAPI bool_t TS_CCALL tsGLTexture_equalPtr(const TSGLTexture self, const TSGLTexture ptr);
TS_CAPI TSGLTexture TS_CCALL tsGLTexture_copyPtr(const TSGLTexture self);
TS_CAPI TSGLTexture TS_CCALL tsGLTexture_clonePtr(const TSGLTexture self);
TS_CAPI void TS_CCALL tsGLTexture_clearPtr(TSGLTexture self);
TS_CAPI void TS_CCALL tsGLTexture_destroyPtr(TSGLTexture self);
TS_CAPI void TS_CCALL tsGLTexture_acquirePtr(TSGLTexture self);
TS_CAPI void TS_CCALL tsGLTexture_unacquirePtr(TSGLTexture self);
TS_CAPI bool_t TS_CCALL tsGLTexture_isValidPtr(const TSGLTexture self);
TS_CAPI bool_t TS_CCALL tsGLTexture_isOwnerPtr(const TSGLTexture self);
TS_CAPI bool_t TS_CCALL tsGLTexture_isConstPtr(const TSGLTexture self);
TS_CAPI uint32_t TS_CCALL tsGLTexture_getCountPtr(const TSGLTexture self);
TS_CAPI const void* TS_CCALL tsGLTexture_getInternalPtr(const TSGLTexture self);
TS_CAPI bool_t TS_CCALL tsGLTexture_equalTexturePtr(const TSGLTexture self, const TSTexture base);
TS_CAPI TSGLTexture TS_CCALL tsGLTexture_castTexturePtr(TSTexture base);
TS_CAPI TSTexture TS_CCALL tsGLTexture_baseTexturePtr(TSGLTexture self);
TS_CAPI bool_t TS_CCALL tsGLTexture_create(TSGLTexture self, uint32_t target, uint32_t texture_id, TS_TextureFlags flags, TS_Format format);
TS_CAPI uint32_t TS_CCALL tsGLTexture_getTarget(TSGLTexture self);
TS_CAPI uint32_t TS_CCALL tsGLTexture_getInternalFormat(TSGLTexture self);
TS_CAPI uint32_t TS_CCALL tsGLTexture_getTextureID(TSGLTexture self);

/// Tellusim::GLESTexture
TS_CAPI TSGLESTexture TS_CCALL tsGLESTexture_new(void);
TS_CAPI void TS_CCALL tsGLESTexture_delete(TSGLESTexture self);
TS_CAPI bool_t TS_CCALL tsGLESTexture_equalPtr(const TSGLESTexture self, const TSGLESTexture ptr);
TS_CAPI TSGLESTexture TS_CCALL tsGLESTexture_copyPtr(const TSGLESTexture self);
TS_CAPI TSGLESTexture TS_CCALL tsGLESTexture_clonePtr(const TSGLESTexture self);
TS_CAPI void TS_CCALL tsGLESTexture_clearPtr(TSGLESTexture self);
TS_CAPI void TS_CCALL tsGLESTexture_destroyPtr(TSGLESTexture self);
TS_CAPI void TS_CCALL tsGLESTexture_acquirePtr(TSGLESTexture self);
TS_CAPI void TS_CCALL tsGLESTexture_unacquirePtr(TSGLESTexture self);
TS_CAPI bool_t TS_CCALL tsGLESTexture_isValidPtr(const TSGLESTexture self);
TS_CAPI bool_t TS_CCALL tsGLESTexture_isOwnerPtr(const TSGLESTexture self);
TS_CAPI bool_t TS_CCALL tsGLESTexture_isConstPtr(const TSGLESTexture self);
TS_CAPI uint32_t TS_CCALL tsGLESTexture_getCountPtr(const TSGLESTexture self);
TS_CAPI const void* TS_CCALL tsGLESTexture_getInternalPtr(const TSGLESTexture self);
TS_CAPI bool_t TS_CCALL tsGLESTexture_equalTexturePtr(const TSGLESTexture self, const TSTexture base);
TS_CAPI TSGLESTexture TS_CCALL tsGLESTexture_castTexturePtr(TSTexture base);
TS_CAPI TSTexture TS_CCALL tsGLESTexture_baseTexturePtr(TSGLESTexture self);
TS_CAPI bool_t TS_CCALL tsGLESTexture_create(TSGLESTexture self, uint32_t target, uint32_t texture_id, TS_TextureFlags flags, TS_Format format);
TS_CAPI uint32_t TS_CCALL tsGLESTexture_getTarget(TSGLESTexture self);
TS_CAPI uint32_t TS_CCALL tsGLESTexture_getInternalFormat(TSGLESTexture self);
TS_CAPI uint32_t TS_CCALL tsGLESTexture_getTextureID(TSGLESTexture self);

/// Tellusim::CUTexture
TS_CAPI TSCUTexture TS_CCALL tsCUTexture_new(void);
TS_CAPI void TS_CCALL tsCUTexture_delete(TSCUTexture self);
TS_CAPI bool_t TS_CCALL tsCUTexture_equalPtr(const TSCUTexture self, const TSCUTexture ptr);
TS_CAPI TSCUTexture TS_CCALL tsCUTexture_copyPtr(const TSCUTexture self);
TS_CAPI TSCUTexture TS_CCALL tsCUTexture_clonePtr(const TSCUTexture self);
TS_CAPI void TS_CCALL tsCUTexture_clearPtr(TSCUTexture self);
TS_CAPI void TS_CCALL tsCUTexture_destroyPtr(TSCUTexture self);
TS_CAPI void TS_CCALL tsCUTexture_acquirePtr(TSCUTexture self);
TS_CAPI void TS_CCALL tsCUTexture_unacquirePtr(TSCUTexture self);
TS_CAPI bool_t TS_CCALL tsCUTexture_isValidPtr(const TSCUTexture self);
TS_CAPI bool_t TS_CCALL tsCUTexture_isOwnerPtr(const TSCUTexture self);
TS_CAPI bool_t TS_CCALL tsCUTexture_isConstPtr(const TSCUTexture self);
TS_CAPI uint32_t TS_CCALL tsCUTexture_getCountPtr(const TSCUTexture self);
TS_CAPI const void* TS_CCALL tsCUTexture_getInternalPtr(const TSCUTexture self);
TS_CAPI bool_t TS_CCALL tsCUTexture_equalTexturePtr(const TSCUTexture self, const TSTexture base);
TS_CAPI TSCUTexture TS_CCALL tsCUTexture_castTexturePtr(TSTexture base);
TS_CAPI TSTexture TS_CCALL tsCUTexture_baseTexturePtr(TSCUTexture self);
TS_CAPI CUarray TS_CCALL tsCUTexture_getTextureLevel(TSCUTexture self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsCUTexture_getArrayFormat(TSCUTexture self);
TS_CAPI uint32_t TS_CCALL tsCUTexture_getArrayChannels(TSCUTexture self);
TS_CAPI CUexternalMemory TS_CCALL tsCUTexture_getSharedMemory(TSCUTexture self);

/// Tellusim::HIPTexture
TS_CAPI TSHIPTexture TS_CCALL tsHIPTexture_new(void);
TS_CAPI void TS_CCALL tsHIPTexture_delete(TSHIPTexture self);
TS_CAPI bool_t TS_CCALL tsHIPTexture_equalPtr(const TSHIPTexture self, const TSHIPTexture ptr);
TS_CAPI TSHIPTexture TS_CCALL tsHIPTexture_copyPtr(const TSHIPTexture self);
TS_CAPI TSHIPTexture TS_CCALL tsHIPTexture_clonePtr(const TSHIPTexture self);
TS_CAPI void TS_CCALL tsHIPTexture_clearPtr(TSHIPTexture self);
TS_CAPI void TS_CCALL tsHIPTexture_destroyPtr(TSHIPTexture self);
TS_CAPI void TS_CCALL tsHIPTexture_acquirePtr(TSHIPTexture self);
TS_CAPI void TS_CCALL tsHIPTexture_unacquirePtr(TSHIPTexture self);
TS_CAPI bool_t TS_CCALL tsHIPTexture_isValidPtr(const TSHIPTexture self);
TS_CAPI bool_t TS_CCALL tsHIPTexture_isOwnerPtr(const TSHIPTexture self);
TS_CAPI bool_t TS_CCALL tsHIPTexture_isConstPtr(const TSHIPTexture self);
TS_CAPI uint32_t TS_CCALL tsHIPTexture_getCountPtr(const TSHIPTexture self);
TS_CAPI const void* TS_CCALL tsHIPTexture_getInternalPtr(const TSHIPTexture self);
TS_CAPI bool_t TS_CCALL tsHIPTexture_equalTexturePtr(const TSHIPTexture self, const TSTexture base);
TS_CAPI TSHIPTexture TS_CCALL tsHIPTexture_castTexturePtr(TSTexture base);
TS_CAPI TSTexture TS_CCALL tsHIPTexture_baseTexturePtr(TSHIPTexture self);
TS_CAPI void* TS_CCALL tsHIPTexture_getTextureArray(TSHIPTexture self);
TS_CAPI void* TS_CCALL tsHIPTexture_getTextureLevel(TSHIPTexture self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsHIPTexture_getArrayFormat(TSHIPTexture self);
TS_CAPI uint32_t TS_CCALL tsHIPTexture_getArrayChannels(TSHIPTexture self);
TS_CAPI void* TS_CCALL tsHIPTexture_getSharedMemory(TSHIPTexture self);

/// Tellusim::FUTexture
TS_CAPI TSFUTexture TS_CCALL tsFUTexture_new(void);
TS_CAPI TSFUTexture TS_CCALL tsFUTexture_new_cATb(const TSTexture *textures, uint32_t textures_size, bool_t owner);
TS_CAPI void TS_CCALL tsFUTexture_delete(TSFUTexture self);
TS_CAPI bool_t TS_CCALL tsFUTexture_equalPtr(const TSFUTexture self, const TSFUTexture ptr);
TS_CAPI TSFUTexture TS_CCALL tsFUTexture_copyPtr(const TSFUTexture self);
TS_CAPI TSFUTexture TS_CCALL tsFUTexture_clonePtr(const TSFUTexture self);
TS_CAPI void TS_CCALL tsFUTexture_clearPtr(TSFUTexture self);
TS_CAPI void TS_CCALL tsFUTexture_destroyPtr(TSFUTexture self);
TS_CAPI void TS_CCALL tsFUTexture_acquirePtr(TSFUTexture self);
TS_CAPI void TS_CCALL tsFUTexture_unacquirePtr(TSFUTexture self);
TS_CAPI bool_t TS_CCALL tsFUTexture_isValidPtr(const TSFUTexture self);
TS_CAPI bool_t TS_CCALL tsFUTexture_isOwnerPtr(const TSFUTexture self);
TS_CAPI bool_t TS_CCALL tsFUTexture_isConstPtr(const TSFUTexture self);
TS_CAPI uint32_t TS_CCALL tsFUTexture_getCountPtr(const TSFUTexture self);
TS_CAPI const void* TS_CCALL tsFUTexture_getInternalPtr(const TSFUTexture self);
TS_CAPI bool_t TS_CCALL tsFUTexture_equalTexturePtr(const TSFUTexture self, const TSTexture base);
TS_CAPI TSFUTexture TS_CCALL tsFUTexture_castTexturePtr(TSTexture base);
TS_CAPI TSTexture TS_CCALL tsFUTexture_baseTexturePtr(TSFUTexture self);
TS_CAPI void TS_CCALL tsFUTexture_setMask(TSFUTexture self, uint32_t mask);
TS_CAPI uint32_t TS_CCALL tsFUTexture_getMask(TSFUTexture self);
TS_CAPI uint32_t TS_CCALL tsFUTexture_getNumTextures(TSFUTexture self);
TS_CAPI TSTexture TS_CCALL tsFUTexture_getTexture_cu(TSFUTexture self, uint32_t index);
TS_CAPI TSTexture TS_CCALL tsFUTexture_getTexture_u(TSFUTexture self, uint32_t index);

/// Tellusim::Tracing
TS_CAPI TSTracing TS_CCALL tsTracing_new(void);
TS_CAPI void TS_CCALL tsTracing_delete(TSTracing self);
TS_CAPI bool_t TS_CCALL tsTracing_equalPtr(const TSTracing self, const TSTracing ptr);
TS_CAPI TSTracing TS_CCALL tsTracing_copyPtr(const TSTracing self);
TS_CAPI TSTracing TS_CCALL tsTracing_clonePtr(const TSTracing self);
TS_CAPI void TS_CCALL tsTracing_clearPtr(TSTracing self);
TS_CAPI void TS_CCALL tsTracing_destroyPtr(TSTracing self);
TS_CAPI void TS_CCALL tsTracing_acquirePtr(TSTracing self);
TS_CAPI void TS_CCALL tsTracing_unacquirePtr(TSTracing self);
TS_CAPI bool_t TS_CCALL tsTracing_isValidPtr(const TSTracing self);
TS_CAPI bool_t TS_CCALL tsTracing_isOwnerPtr(const TSTracing self);
TS_CAPI bool_t TS_CCALL tsTracing_isConstPtr(const TSTracing self);
TS_CAPI uint32_t TS_CCALL tsTracing_getCountPtr(const TSTracing self);
TS_CAPI const void* TS_CCALL tsTracing_getInternalPtr(const TSTracing self);
TS_CAPI TS_Platform TS_CCALL tsTracing_getPlatform(TSTracing self);
TS_CAPI const char* TS_CCALL tsTracing_getPlatformName(TSTracing self);
TS_CAPI uint32_t TS_CCALL tsTracing_getIndex(TSTracing self);
TS_CAPI void TS_CCALL tsTracing_clear(TSTracing self);
TS_CAPI bool_t TS_CCALL tsTracing_isCreated(TSTracing self);
TS_CAPI bool_t TS_CCALL tsTracing_isBuilt(TSTracing self);
TS_CAPI void TS_CCALL tsTracing_setName(TSTracing self, const char *name);
TS_CAPI TSString TS_CCALL tsTracing_getName(TSTracing self);
TS_CAPI bool_t TS_CCALL tsTracing_create(TSTracing self, TS_TracingType type, TS_TracingFlags flags);
TS_CAPI TS_TracingType TS_CCALL tsTracing_getType(TSTracing self);
TS_CAPI const char* TS_CCALL tsTracing_getTypeName_TT(TS_TracingType type);
TS_CAPI const char* TS_CCALL tsTracing_getTypeName_c(TSTracing self);
TS_CAPI bool_t TS_CCALL tsTracing_isInstanceType(TSTracing self);
TS_CAPI bool_t TS_CCALL tsTracing_isTriangleType(TSTracing self);
TS_CAPI bool_t TS_CCALL tsTracing_isBoundType(TSTracing self);
TS_CAPI bool_t TS_CCALL tsTracing_isGeometryType(TSTracing self);
TS_CAPI void TS_CCALL tsTracing_setParameters(TSTracing self, const TSTracing tracing);
TS_CAPI uint32_t TS_CCALL tsTracing_getNumGeometries(TSTracing self);
TS_CAPI void TS_CCALL tsTracing_setInstanceBuffer_uBz(TSTracing self, uint32_t num_instances, TSBuffer buffer, size_t offset);
TS_CAPI void TS_CCALL tsTracing_setInstanceBuffer_Bz(TSTracing self, TSBuffer buffer, size_t offset);
TS_CAPI void TS_CCALL tsTracing_setNumInstances(TSTracing self, uint32_t num_instances);
TS_CAPI uint32_t TS_CCALL tsTracing_getNumInstances(TSTracing self);
TS_CAPI TSBuffer TS_CCALL tsTracing_getInstanceBuffer(TSTracing self);
TS_CAPI size_t TS_CCALL tsTracing_getInstanceOffset(TSTracing self);
TS_CAPI uint32_t TS_CCALL tsTracing_addVertexBuffer(TSTracing self, uint32_t num_vertices, TS_Format format, size_t stride, TSBuffer buffer, size_t offset);
TS_CAPI void TS_CCALL tsTracing_setVertexBuffer_uuBz(TSTracing self, uint32_t index, uint32_t num_vertices, TSBuffer buffer, size_t offset);
TS_CAPI void TS_CCALL tsTracing_setVertexBuffer_uBz(TSTracing self, uint32_t index, TSBuffer buffer, size_t offset);
TS_CAPI void TS_CCALL tsTracing_setNumVertices(TSTracing self, uint32_t index, uint32_t num_vertices);
TS_CAPI uint32_t TS_CCALL tsTracing_getNumVertices(TSTracing self, uint32_t index);
TS_CAPI TS_Format TS_CCALL tsTracing_getVertexFormat(TSTracing self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsTracing_getVertexStride(TSTracing self, uint32_t index);
TS_CAPI TSBuffer TS_CCALL tsTracing_getVertexBuffer(TSTracing self, uint32_t index);
TS_CAPI size_t TS_CCALL tsTracing_getVertexOffset(TSTracing self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsTracing_addIndexBuffer(TSTracing self, uint32_t num_indices, TS_Format format, TSBuffer buffer, size_t offset);
TS_CAPI void TS_CCALL tsTracing_setIndexBuffer_uuBz(TSTracing self, uint32_t index, uint32_t num_indices, TSBuffer buffer, size_t offset);
TS_CAPI void TS_CCALL tsTracing_setIndexBuffer_uBz(TSTracing self, uint32_t index, TSBuffer buffer, size_t offset);
TS_CAPI void TS_CCALL tsTracing_setNumIndices(TSTracing self, uint32_t index, uint32_t num_indices);
TS_CAPI uint32_t TS_CCALL tsTracing_getNumIndices(TSTracing self, uint32_t index);
TS_CAPI TS_Format TS_CCALL tsTracing_getIndexFormat(TSTracing self, uint32_t index);
TS_CAPI TSBuffer TS_CCALL tsTracing_getIndexBuffer(TSTracing self, uint32_t index);
TS_CAPI size_t TS_CCALL tsTracing_getIndexOffset(TSTracing self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsTracing_addBoundBuffer(TSTracing self, uint32_t num_bounds, size_t stride, TSBuffer buffer, size_t offset);
TS_CAPI void TS_CCALL tsTracing_setBoundBuffer_uuBz(TSTracing self, uint32_t index, uint32_t num_bounds, TSBuffer buffer, size_t offset);
TS_CAPI void TS_CCALL tsTracing_setBoundBuffer_uBz(TSTracing self, uint32_t index, TSBuffer buffer, size_t offset);
TS_CAPI void TS_CCALL tsTracing_setNumBounds(TSTracing self, uint32_t index, uint32_t num_bounds);
TS_CAPI uint32_t TS_CCALL tsTracing_getNumBounds(TSTracing self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsTracing_getBoundStride(TSTracing self, uint32_t index);
TS_CAPI TSBuffer TS_CCALL tsTracing_getBoundBuffer(TSTracing self, uint32_t index);
TS_CAPI size_t TS_CCALL tsTracing_getBoundOffset(TSTracing self, uint32_t index);
TS_CAPI void TS_CCALL tsTracing_setIndirectBuffer(TSTracing self, TSBuffer buffer, size_t offset);
TS_CAPI TSBuffer TS_CCALL tsTracing_getIndirectBuffer(TSTracing self);
TS_CAPI size_t TS_CCALL tsTracing_getIndirectOffset(TSTracing self);
TS_CAPI TSString TS_CCALL tsTracing_getDescription(TSTracing self);
TS_CAPI uint64_t TS_CCALL tsTracing_getTracingAddress(TSTracing self);
TS_CAPI size_t TS_CCALL tsTracing_getBuildSize(TSTracing self);
TS_CAPI size_t TS_CCALL tsTracing_getUpdateSize(TSTracing self);
TS_CAPI size_t TS_CCALL tsTracing_getMemory(TSTracing self);

/// Tellusim::D3D12Tracing
TS_CAPI TSD3D12Tracing TS_CCALL tsD3D12Tracing_new(void);
TS_CAPI void TS_CCALL tsD3D12Tracing_delete(TSD3D12Tracing self);
TS_CAPI bool_t TS_CCALL tsD3D12Tracing_equalPtr(const TSD3D12Tracing self, const TSD3D12Tracing ptr);
TS_CAPI TSD3D12Tracing TS_CCALL tsD3D12Tracing_copyPtr(const TSD3D12Tracing self);
TS_CAPI TSD3D12Tracing TS_CCALL tsD3D12Tracing_clonePtr(const TSD3D12Tracing self);
TS_CAPI void TS_CCALL tsD3D12Tracing_clearPtr(TSD3D12Tracing self);
TS_CAPI void TS_CCALL tsD3D12Tracing_destroyPtr(TSD3D12Tracing self);
TS_CAPI void TS_CCALL tsD3D12Tracing_acquirePtr(TSD3D12Tracing self);
TS_CAPI void TS_CCALL tsD3D12Tracing_unacquirePtr(TSD3D12Tracing self);
TS_CAPI bool_t TS_CCALL tsD3D12Tracing_isValidPtr(const TSD3D12Tracing self);
TS_CAPI bool_t TS_CCALL tsD3D12Tracing_isOwnerPtr(const TSD3D12Tracing self);
TS_CAPI bool_t TS_CCALL tsD3D12Tracing_isConstPtr(const TSD3D12Tracing self);
TS_CAPI uint32_t TS_CCALL tsD3D12Tracing_getCountPtr(const TSD3D12Tracing self);
TS_CAPI const void* TS_CCALL tsD3D12Tracing_getInternalPtr(const TSD3D12Tracing self);
TS_CAPI bool_t TS_CCALL tsD3D12Tracing_equalTracingPtr(const TSD3D12Tracing self, const TSTracing base);
TS_CAPI TSD3D12Tracing TS_CCALL tsD3D12Tracing_castTracingPtr(TSTracing base);
TS_CAPI TSTracing TS_CCALL tsD3D12Tracing_baseTracingPtr(TSD3D12Tracing self);
TS_CAPI void* TS_CCALL tsD3D12Tracing_getGeometryDesc(TSD3D12Tracing self, uint32_t index);
TS_CAPI void* TS_CCALL tsD3D12Tracing_getBuildInputs(TSD3D12Tracing self);
TS_CAPI void* TS_CCALL tsD3D12Tracing_getPrebuildInfo(TSD3D12Tracing self);
TS_CAPI void* TS_CCALL tsD3D12Tracing_getBuildDesc(TSD3D12Tracing self);
TS_CAPI TSBuffer TS_CCALL tsD3D12Tracing_getTracingBuffer(TSD3D12Tracing self);
TS_CAPI size_t TS_CCALL tsD3D12Tracing_getShaderResourceView(TSD3D12Tracing self);

/// Tellusim::MTLTracing
TS_CAPI TSMTLTracing TS_CCALL tsMTLTracing_new(void);
TS_CAPI void TS_CCALL tsMTLTracing_delete(TSMTLTracing self);
TS_CAPI bool_t TS_CCALL tsMTLTracing_equalPtr(const TSMTLTracing self, const TSMTLTracing ptr);
TS_CAPI TSMTLTracing TS_CCALL tsMTLTracing_copyPtr(const TSMTLTracing self);
TS_CAPI TSMTLTracing TS_CCALL tsMTLTracing_clonePtr(const TSMTLTracing self);
TS_CAPI void TS_CCALL tsMTLTracing_clearPtr(TSMTLTracing self);
TS_CAPI void TS_CCALL tsMTLTracing_destroyPtr(TSMTLTracing self);
TS_CAPI void TS_CCALL tsMTLTracing_acquirePtr(TSMTLTracing self);
TS_CAPI void TS_CCALL tsMTLTracing_unacquirePtr(TSMTLTracing self);
TS_CAPI bool_t TS_CCALL tsMTLTracing_isValidPtr(const TSMTLTracing self);
TS_CAPI bool_t TS_CCALL tsMTLTracing_isOwnerPtr(const TSMTLTracing self);
TS_CAPI bool_t TS_CCALL tsMTLTracing_isConstPtr(const TSMTLTracing self);
TS_CAPI uint32_t TS_CCALL tsMTLTracing_getCountPtr(const TSMTLTracing self);
TS_CAPI const void* TS_CCALL tsMTLTracing_getInternalPtr(const TSMTLTracing self);
TS_CAPI bool_t TS_CCALL tsMTLTracing_equalTracingPtr(const TSMTLTracing self, const TSTracing base);
TS_CAPI TSMTLTracing TS_CCALL tsMTLTracing_castTracingPtr(TSTracing base);
TS_CAPI TSTracing TS_CCALL tsMTLTracing_baseTracingPtr(TSMTLTracing self);
TS_CAPI void* TS_CCALL tsMTLTracing_getGeometryDesc(TSMTLTracing self, uint32_t index);
TS_CAPI void* TS_CCALL tsMTLTracing_getPrimitiveDesc(TSMTLTracing self);
TS_CAPI void* TS_CCALL tsMTLTracing_getInstanceDesc(TSMTLTracing self);
TS_CAPI void* TS_CCALL tsMTLTracing_getAccelerationStructure(TSMTLTracing self);

/// Tellusim::VKTracing
TS_CAPI TSVKTracing TS_CCALL tsVKTracing_new(void);
TS_CAPI void TS_CCALL tsVKTracing_delete(TSVKTracing self);
TS_CAPI bool_t TS_CCALL tsVKTracing_equalPtr(const TSVKTracing self, const TSVKTracing ptr);
TS_CAPI TSVKTracing TS_CCALL tsVKTracing_copyPtr(const TSVKTracing self);
TS_CAPI TSVKTracing TS_CCALL tsVKTracing_clonePtr(const TSVKTracing self);
TS_CAPI void TS_CCALL tsVKTracing_clearPtr(TSVKTracing self);
TS_CAPI void TS_CCALL tsVKTracing_destroyPtr(TSVKTracing self);
TS_CAPI void TS_CCALL tsVKTracing_acquirePtr(TSVKTracing self);
TS_CAPI void TS_CCALL tsVKTracing_unacquirePtr(TSVKTracing self);
TS_CAPI bool_t TS_CCALL tsVKTracing_isValidPtr(const TSVKTracing self);
TS_CAPI bool_t TS_CCALL tsVKTracing_isOwnerPtr(const TSVKTracing self);
TS_CAPI bool_t TS_CCALL tsVKTracing_isConstPtr(const TSVKTracing self);
TS_CAPI uint32_t TS_CCALL tsVKTracing_getCountPtr(const TSVKTracing self);
TS_CAPI const void* TS_CCALL tsVKTracing_getInternalPtr(const TSVKTracing self);
TS_CAPI bool_t TS_CCALL tsVKTracing_equalTracingPtr(const TSVKTracing self, const TSTracing base);
TS_CAPI TSVKTracing TS_CCALL tsVKTracing_castTracingPtr(TSTracing base);
TS_CAPI TSTracing TS_CCALL tsVKTracing_baseTracingPtr(TSVKTracing self);
TS_CAPI void* TS_CCALL tsVKTracing_getBuildGeometryInfo(TSVKTracing self);
TS_CAPI void* TS_CCALL tsVKTracing_getBuildSizeInfo(TSVKTracing self);
TS_CAPI TSBuffer TS_CCALL tsVKTracing_getTracingBuffer(TSVKTracing self);
TS_CAPI VkAccelerationStructureKHR TS_CCALL tsVKTracing_getAccelerationStructure(TSVKTracing self);

/// Tellusim::FUTracing
TS_CAPI TSFUTracing TS_CCALL tsFUTracing_new(void);
TS_CAPI TSFUTracing TS_CCALL tsFUTracing_new_cATb(const TSTracing *tracings, uint32_t tracings_size, bool_t owner);
TS_CAPI void TS_CCALL tsFUTracing_delete(TSFUTracing self);
TS_CAPI bool_t TS_CCALL tsFUTracing_equalPtr(const TSFUTracing self, const TSFUTracing ptr);
TS_CAPI TSFUTracing TS_CCALL tsFUTracing_copyPtr(const TSFUTracing self);
TS_CAPI TSFUTracing TS_CCALL tsFUTracing_clonePtr(const TSFUTracing self);
TS_CAPI void TS_CCALL tsFUTracing_clearPtr(TSFUTracing self);
TS_CAPI void TS_CCALL tsFUTracing_destroyPtr(TSFUTracing self);
TS_CAPI void TS_CCALL tsFUTracing_acquirePtr(TSFUTracing self);
TS_CAPI void TS_CCALL tsFUTracing_unacquirePtr(TSFUTracing self);
TS_CAPI bool_t TS_CCALL tsFUTracing_isValidPtr(const TSFUTracing self);
TS_CAPI bool_t TS_CCALL tsFUTracing_isOwnerPtr(const TSFUTracing self);
TS_CAPI bool_t TS_CCALL tsFUTracing_isConstPtr(const TSFUTracing self);
TS_CAPI uint32_t TS_CCALL tsFUTracing_getCountPtr(const TSFUTracing self);
TS_CAPI const void* TS_CCALL tsFUTracing_getInternalPtr(const TSFUTracing self);
TS_CAPI bool_t TS_CCALL tsFUTracing_equalTracingPtr(const TSFUTracing self, const TSTracing base);
TS_CAPI TSFUTracing TS_CCALL tsFUTracing_castTracingPtr(TSTracing base);
TS_CAPI TSTracing TS_CCALL tsFUTracing_baseTracingPtr(TSFUTracing self);
TS_CAPI void TS_CCALL tsFUTracing_setMask(TSFUTracing self, uint32_t mask);
TS_CAPI uint32_t TS_CCALL tsFUTracing_getMask(TSFUTracing self);
TS_CAPI uint32_t TS_CCALL tsFUTracing_getNumTracings(TSFUTracing self);
TS_CAPI TSTracing TS_CCALL tsFUTracing_getTracing_cu(TSFUTracing self, uint32_t index);
TS_CAPI TSTracing TS_CCALL tsFUTracing_getTracing_u(TSFUTracing self, uint32_t index);

/// Tellusim::Target
TS_CAPI TSTarget TS_CCALL tsTarget_new(void);
TS_CAPI void TS_CCALL tsTarget_delete(TSTarget self);
TS_CAPI bool_t TS_CCALL tsTarget_equalPtr(const TSTarget self, const TSTarget ptr);
TS_CAPI TSTarget TS_CCALL tsTarget_copyPtr(const TSTarget self);
TS_CAPI TSTarget TS_CCALL tsTarget_clonePtr(const TSTarget self);
TS_CAPI void TS_CCALL tsTarget_clearPtr(TSTarget self);
TS_CAPI void TS_CCALL tsTarget_destroyPtr(TSTarget self);
TS_CAPI void TS_CCALL tsTarget_acquirePtr(TSTarget self);
TS_CAPI void TS_CCALL tsTarget_unacquirePtr(TSTarget self);
TS_CAPI bool_t TS_CCALL tsTarget_isValidPtr(const TSTarget self);
TS_CAPI bool_t TS_CCALL tsTarget_isOwnerPtr(const TSTarget self);
TS_CAPI bool_t TS_CCALL tsTarget_isConstPtr(const TSTarget self);
TS_CAPI uint32_t TS_CCALL tsTarget_getCountPtr(const TSTarget self);
TS_CAPI const void* TS_CCALL tsTarget_getInternalPtr(const TSTarget self);
TS_CAPI TS_Platform TS_CCALL tsTarget_getPlatform(TSTarget self);
TS_CAPI const char* TS_CCALL tsTarget_getPlatformName(TSTarget self);
TS_CAPI uint32_t TS_CCALL tsTarget_getIndex(TSTarget self);
TS_CAPI bool_t TS_CCALL tsTarget_begin_F(TSTarget self, TSFence fence);
TS_CAPI bool_t TS_CCALL tsTarget_begin(TSTarget self);
TS_CAPI void TS_CCALL tsTarget_end_F(TSTarget self, TSFence fence);
TS_CAPI void TS_CCALL tsTarget_end(TSTarget self);
TS_CAPI void TS_CCALL tsTarget_swap(TSTarget self, TSSurface surface);
TS_CAPI bool_t TS_CCALL tsTarget_isEnabled(TSTarget self);
TS_CAPI TS_Format TS_CCALL tsTarget_getColorFormat(TSTarget self, uint32_t index);
TS_CAPI TS_Format TS_CCALL tsTarget_getDepthFormat(TSTarget self);
TS_CAPI uint32_t TS_CCALL tsTarget_getMultisample(TSTarget self);
TS_CAPI bool_t TS_CCALL tsTarget_hasMultisample(TSTarget self);
TS_CAPI bool_t TS_CCALL tsTarget_isFlipped(TSTarget self);
TS_CAPI bool_t TS_CCALL tsTarget_isAtomic(TSTarget self);
TS_CAPI uint32_t TS_CCALL tsTarget_getWidth(TSTarget self);
TS_CAPI uint32_t TS_CCALL tsTarget_getHeight(TSTarget self);
TS_CAPI uint32_t TS_CCALL tsTarget_getDepth(TSTarget self);
TS_CAPI uint32_t TS_CCALL tsTarget_getFaces(TSTarget self);
TS_CAPI uint32_t TS_CCALL tsTarget_getLayers(TSTarget self);
TS_CAPI uint32_t TS_CCALL tsTarget_getMipmaps(TSTarget self);
TS_CAPI void TS_CCALL tsTarget_setClearColor_cC(TSTarget self, const TSColor *color);
TS_CAPI void TS_CCALL tsTarget_setClearColor_ucC(TSTarget self, uint32_t index, const TSColor *color);
TS_CAPI void TS_CCALL tsTarget_setClearColor_ffff(TSTarget self, float32_t r, float32_t g, float32_t b, float32_t a);
TS_CAPI void TS_CCALL tsTarget_setClearColor_uffff(TSTarget self, uint32_t index, float32_t r, float32_t g, float32_t b, float32_t a);
TS_CAPI void TS_CCALL tsTarget_setColorTexture_TTOcS(TSTarget self, TSTexture texture, TS_TargetOperation op, const TSSlice *slice);
TS_CAPI void TS_CCALL tsTarget_setColorTexture_uTTOcS(TSTarget self, uint32_t index, TSTexture texture, TS_TargetOperation op, const TSSlice *slice);
TS_CAPI void TS_CCALL tsTarget_setColorResolve_TcS(TSTarget self, TSTexture texture, const TSSlice *slice);
TS_CAPI void TS_CCALL tsTarget_setColorResolve_uTcS(TSTarget self, uint32_t index, TSTexture texture, const TSSlice *slice);
TS_CAPI uint32_t TS_CCALL tsTarget_getNumTargets(TSTarget self);
TS_CAPI TSColor TS_CCALL tsTarget_getClearColor(TSTarget self, uint32_t index);
TS_CAPI TS_TargetOperation TS_CCALL tsTarget_getColorOp(TSTarget self, uint32_t index);
TS_CAPI TSTexture TS_CCALL tsTarget_getColorTexture(TSTarget self, uint32_t index);
TS_CAPI TSTexture TS_CCALL tsTarget_getColorResolve(TSTarget self, uint32_t index);
TS_CAPI TSSlice TS_CCALL tsTarget_getColorTextureSlice(TSTarget self, uint32_t index);
TS_CAPI TSSlice TS_CCALL tsTarget_getColorResolveSlice(TSTarget self, uint32_t index);
TS_CAPI void TS_CCALL tsTarget_setClearDepth(TSTarget self, float32_t depth, uint32_t stencil);
TS_CAPI void TS_CCALL tsTarget_setDepthTexture(TSTarget self, TSTexture texture, TS_TargetOperation op, const TSSlice *slice);
TS_CAPI void TS_CCALL tsTarget_setDepthResolve(TSTarget self, TSTexture texture, const TSSlice *slice);
TS_CAPI float32_t TS_CCALL tsTarget_getClearDepth(TSTarget self);
TS_CAPI uint32_t TS_CCALL tsTarget_getClearStencil(TSTarget self);
TS_CAPI TS_TargetOperation TS_CCALL tsTarget_getDepthOp(TSTarget self);
TS_CAPI TSTexture TS_CCALL tsTarget_getDepthTexture(TSTarget self);
TS_CAPI TSTexture TS_CCALL tsTarget_getDepthResolve(TSTarget self);
TS_CAPI TSSlice TS_CCALL tsTarget_getDepthTextureSlice(TSTarget self);
TS_CAPI TSSlice TS_CCALL tsTarget_getDepthResolveSlice(TSTarget self);

/// Tellusim::D3D12Target
TS_CAPI TSD3D12Target TS_CCALL tsD3D12Target_new(void);
TS_CAPI void TS_CCALL tsD3D12Target_delete(TSD3D12Target self);
TS_CAPI bool_t TS_CCALL tsD3D12Target_equalPtr(const TSD3D12Target self, const TSD3D12Target ptr);
TS_CAPI TSD3D12Target TS_CCALL tsD3D12Target_copyPtr(const TSD3D12Target self);
TS_CAPI TSD3D12Target TS_CCALL tsD3D12Target_clonePtr(const TSD3D12Target self);
TS_CAPI void TS_CCALL tsD3D12Target_clearPtr(TSD3D12Target self);
TS_CAPI void TS_CCALL tsD3D12Target_destroyPtr(TSD3D12Target self);
TS_CAPI void TS_CCALL tsD3D12Target_acquirePtr(TSD3D12Target self);
TS_CAPI void TS_CCALL tsD3D12Target_unacquirePtr(TSD3D12Target self);
TS_CAPI bool_t TS_CCALL tsD3D12Target_isValidPtr(const TSD3D12Target self);
TS_CAPI bool_t TS_CCALL tsD3D12Target_isOwnerPtr(const TSD3D12Target self);
TS_CAPI bool_t TS_CCALL tsD3D12Target_isConstPtr(const TSD3D12Target self);
TS_CAPI uint32_t TS_CCALL tsD3D12Target_getCountPtr(const TSD3D12Target self);
TS_CAPI const void* TS_CCALL tsD3D12Target_getInternalPtr(const TSD3D12Target self);
TS_CAPI bool_t TS_CCALL tsD3D12Target_equalTargetPtr(const TSD3D12Target self, const TSTarget base);
TS_CAPI TSD3D12Target TS_CCALL tsD3D12Target_castTargetPtr(TSTarget base);
TS_CAPI TSTarget TS_CCALL tsD3D12Target_baseTargetPtr(TSD3D12Target self);
TS_CAPI size_t* TS_CCALL tsD3D12Target_getRenderTargetViews(TSD3D12Target self);
TS_CAPI size_t TS_CCALL tsD3D12Target_getDepthStencilView(TSD3D12Target self);

/// Tellusim::D3D11Target
TS_CAPI TSD3D11Target TS_CCALL tsD3D11Target_new(void);
TS_CAPI void TS_CCALL tsD3D11Target_delete(TSD3D11Target self);
TS_CAPI bool_t TS_CCALL tsD3D11Target_equalPtr(const TSD3D11Target self, const TSD3D11Target ptr);
TS_CAPI TSD3D11Target TS_CCALL tsD3D11Target_copyPtr(const TSD3D11Target self);
TS_CAPI TSD3D11Target TS_CCALL tsD3D11Target_clonePtr(const TSD3D11Target self);
TS_CAPI void TS_CCALL tsD3D11Target_clearPtr(TSD3D11Target self);
TS_CAPI void TS_CCALL tsD3D11Target_destroyPtr(TSD3D11Target self);
TS_CAPI void TS_CCALL tsD3D11Target_acquirePtr(TSD3D11Target self);
TS_CAPI void TS_CCALL tsD3D11Target_unacquirePtr(TSD3D11Target self);
TS_CAPI bool_t TS_CCALL tsD3D11Target_isValidPtr(const TSD3D11Target self);
TS_CAPI bool_t TS_CCALL tsD3D11Target_isOwnerPtr(const TSD3D11Target self);
TS_CAPI bool_t TS_CCALL tsD3D11Target_isConstPtr(const TSD3D11Target self);
TS_CAPI uint32_t TS_CCALL tsD3D11Target_getCountPtr(const TSD3D11Target self);
TS_CAPI const void* TS_CCALL tsD3D11Target_getInternalPtr(const TSD3D11Target self);
TS_CAPI bool_t TS_CCALL tsD3D11Target_equalTargetPtr(const TSD3D11Target self, const TSTarget base);
TS_CAPI TSD3D11Target TS_CCALL tsD3D11Target_castTargetPtr(TSTarget base);
TS_CAPI TSTarget TS_CCALL tsD3D11Target_baseTargetPtr(TSD3D11Target self);
TS_CAPI ID3D11RenderTargetView** TS_CCALL tsD3D11Target_getRenderTargetViews(TSD3D11Target self);
TS_CAPI ID3D11DepthStencilView* TS_CCALL tsD3D11Target_getDepthStencilView(TSD3D11Target self);

/// Tellusim::MTLTarget
TS_CAPI TSMTLTarget TS_CCALL tsMTLTarget_new(void);
TS_CAPI void TS_CCALL tsMTLTarget_delete(TSMTLTarget self);
TS_CAPI bool_t TS_CCALL tsMTLTarget_equalPtr(const TSMTLTarget self, const TSMTLTarget ptr);
TS_CAPI TSMTLTarget TS_CCALL tsMTLTarget_copyPtr(const TSMTLTarget self);
TS_CAPI TSMTLTarget TS_CCALL tsMTLTarget_clonePtr(const TSMTLTarget self);
TS_CAPI void TS_CCALL tsMTLTarget_clearPtr(TSMTLTarget self);
TS_CAPI void TS_CCALL tsMTLTarget_destroyPtr(TSMTLTarget self);
TS_CAPI void TS_CCALL tsMTLTarget_acquirePtr(TSMTLTarget self);
TS_CAPI void TS_CCALL tsMTLTarget_unacquirePtr(TSMTLTarget self);
TS_CAPI bool_t TS_CCALL tsMTLTarget_isValidPtr(const TSMTLTarget self);
TS_CAPI bool_t TS_CCALL tsMTLTarget_isOwnerPtr(const TSMTLTarget self);
TS_CAPI bool_t TS_CCALL tsMTLTarget_isConstPtr(const TSMTLTarget self);
TS_CAPI uint32_t TS_CCALL tsMTLTarget_getCountPtr(const TSMTLTarget self);
TS_CAPI const void* TS_CCALL tsMTLTarget_getInternalPtr(const TSMTLTarget self);
TS_CAPI bool_t TS_CCALL tsMTLTarget_equalTargetPtr(const TSMTLTarget self, const TSTarget base);
TS_CAPI TSMTLTarget TS_CCALL tsMTLTarget_castTargetPtr(TSTarget base);
TS_CAPI TSTarget TS_CCALL tsMTLTarget_baseTargetPtr(TSMTLTarget self);
TS_CAPI void* TS_CCALL tsMTLTarget_getDescriptor(TSMTLTarget self);

/// Tellusim::VKTarget
TS_CAPI TSVKTarget TS_CCALL tsVKTarget_new(void);
TS_CAPI void TS_CCALL tsVKTarget_delete(TSVKTarget self);
TS_CAPI bool_t TS_CCALL tsVKTarget_equalPtr(const TSVKTarget self, const TSVKTarget ptr);
TS_CAPI TSVKTarget TS_CCALL tsVKTarget_copyPtr(const TSVKTarget self);
TS_CAPI TSVKTarget TS_CCALL tsVKTarget_clonePtr(const TSVKTarget self);
TS_CAPI void TS_CCALL tsVKTarget_clearPtr(TSVKTarget self);
TS_CAPI void TS_CCALL tsVKTarget_destroyPtr(TSVKTarget self);
TS_CAPI void TS_CCALL tsVKTarget_acquirePtr(TSVKTarget self);
TS_CAPI void TS_CCALL tsVKTarget_unacquirePtr(TSVKTarget self);
TS_CAPI bool_t TS_CCALL tsVKTarget_isValidPtr(const TSVKTarget self);
TS_CAPI bool_t TS_CCALL tsVKTarget_isOwnerPtr(const TSVKTarget self);
TS_CAPI bool_t TS_CCALL tsVKTarget_isConstPtr(const TSVKTarget self);
TS_CAPI uint32_t TS_CCALL tsVKTarget_getCountPtr(const TSVKTarget self);
TS_CAPI const void* TS_CCALL tsVKTarget_getInternalPtr(const TSVKTarget self);
TS_CAPI bool_t TS_CCALL tsVKTarget_equalTargetPtr(const TSVKTarget self, const TSTarget base);
TS_CAPI TSVKTarget TS_CCALL tsVKTarget_castTargetPtr(TSTarget base);
TS_CAPI TSTarget TS_CCALL tsVKTarget_baseTargetPtr(TSVKTarget self);
TS_CAPI VkRenderPass TS_CCALL tsVKTarget_getRenderPass(TSVKTarget self);
TS_CAPI VkFramebuffer TS_CCALL tsVKTarget_getFramebuffer(TSVKTarget self);

/// Tellusim::GLTarget
TS_CAPI TSGLTarget TS_CCALL tsGLTarget_new(void);
TS_CAPI void TS_CCALL tsGLTarget_delete(TSGLTarget self);
TS_CAPI bool_t TS_CCALL tsGLTarget_equalPtr(const TSGLTarget self, const TSGLTarget ptr);
TS_CAPI TSGLTarget TS_CCALL tsGLTarget_copyPtr(const TSGLTarget self);
TS_CAPI TSGLTarget TS_CCALL tsGLTarget_clonePtr(const TSGLTarget self);
TS_CAPI void TS_CCALL tsGLTarget_clearPtr(TSGLTarget self);
TS_CAPI void TS_CCALL tsGLTarget_destroyPtr(TSGLTarget self);
TS_CAPI void TS_CCALL tsGLTarget_acquirePtr(TSGLTarget self);
TS_CAPI void TS_CCALL tsGLTarget_unacquirePtr(TSGLTarget self);
TS_CAPI bool_t TS_CCALL tsGLTarget_isValidPtr(const TSGLTarget self);
TS_CAPI bool_t TS_CCALL tsGLTarget_isOwnerPtr(const TSGLTarget self);
TS_CAPI bool_t TS_CCALL tsGLTarget_isConstPtr(const TSGLTarget self);
TS_CAPI uint32_t TS_CCALL tsGLTarget_getCountPtr(const TSGLTarget self);
TS_CAPI const void* TS_CCALL tsGLTarget_getInternalPtr(const TSGLTarget self);
TS_CAPI bool_t TS_CCALL tsGLTarget_equalTargetPtr(const TSGLTarget self, const TSTarget base);
TS_CAPI TSGLTarget TS_CCALL tsGLTarget_castTargetPtr(TSTarget base);
TS_CAPI TSTarget TS_CCALL tsGLTarget_baseTargetPtr(TSGLTarget self);
TS_CAPI uint32_t TS_CCALL tsGLTarget_getFramebufferID(TSGLTarget self);

/// Tellusim::GLESTarget
TS_CAPI TSGLESTarget TS_CCALL tsGLESTarget_new(void);
TS_CAPI void TS_CCALL tsGLESTarget_delete(TSGLESTarget self);
TS_CAPI bool_t TS_CCALL tsGLESTarget_equalPtr(const TSGLESTarget self, const TSGLESTarget ptr);
TS_CAPI TSGLESTarget TS_CCALL tsGLESTarget_copyPtr(const TSGLESTarget self);
TS_CAPI TSGLESTarget TS_CCALL tsGLESTarget_clonePtr(const TSGLESTarget self);
TS_CAPI void TS_CCALL tsGLESTarget_clearPtr(TSGLESTarget self);
TS_CAPI void TS_CCALL tsGLESTarget_destroyPtr(TSGLESTarget self);
TS_CAPI void TS_CCALL tsGLESTarget_acquirePtr(TSGLESTarget self);
TS_CAPI void TS_CCALL tsGLESTarget_unacquirePtr(TSGLESTarget self);
TS_CAPI bool_t TS_CCALL tsGLESTarget_isValidPtr(const TSGLESTarget self);
TS_CAPI bool_t TS_CCALL tsGLESTarget_isOwnerPtr(const TSGLESTarget self);
TS_CAPI bool_t TS_CCALL tsGLESTarget_isConstPtr(const TSGLESTarget self);
TS_CAPI uint32_t TS_CCALL tsGLESTarget_getCountPtr(const TSGLESTarget self);
TS_CAPI const void* TS_CCALL tsGLESTarget_getInternalPtr(const TSGLESTarget self);
TS_CAPI bool_t TS_CCALL tsGLESTarget_equalTargetPtr(const TSGLESTarget self, const TSTarget base);
TS_CAPI TSGLESTarget TS_CCALL tsGLESTarget_castTargetPtr(TSTarget base);
TS_CAPI TSTarget TS_CCALL tsGLESTarget_baseTargetPtr(TSGLESTarget self);
TS_CAPI uint32_t TS_CCALL tsGLESTarget_getFramebufferID(TSGLESTarget self);

/// Tellusim::FUTarget
TS_CAPI TSFUTarget TS_CCALL tsFUTarget_new(void);
TS_CAPI TSFUTarget TS_CCALL tsFUTarget_new_cATb(const TSTarget *targets, uint32_t targets_size, bool_t owner);
TS_CAPI void TS_CCALL tsFUTarget_delete(TSFUTarget self);
TS_CAPI bool_t TS_CCALL tsFUTarget_equalPtr(const TSFUTarget self, const TSFUTarget ptr);
TS_CAPI TSFUTarget TS_CCALL tsFUTarget_copyPtr(const TSFUTarget self);
TS_CAPI TSFUTarget TS_CCALL tsFUTarget_clonePtr(const TSFUTarget self);
TS_CAPI void TS_CCALL tsFUTarget_clearPtr(TSFUTarget self);
TS_CAPI void TS_CCALL tsFUTarget_destroyPtr(TSFUTarget self);
TS_CAPI void TS_CCALL tsFUTarget_acquirePtr(TSFUTarget self);
TS_CAPI void TS_CCALL tsFUTarget_unacquirePtr(TSFUTarget self);
TS_CAPI bool_t TS_CCALL tsFUTarget_isValidPtr(const TSFUTarget self);
TS_CAPI bool_t TS_CCALL tsFUTarget_isOwnerPtr(const TSFUTarget self);
TS_CAPI bool_t TS_CCALL tsFUTarget_isConstPtr(const TSFUTarget self);
TS_CAPI uint32_t TS_CCALL tsFUTarget_getCountPtr(const TSFUTarget self);
TS_CAPI const void* TS_CCALL tsFUTarget_getInternalPtr(const TSFUTarget self);
TS_CAPI bool_t TS_CCALL tsFUTarget_equalTargetPtr(const TSFUTarget self, const TSTarget base);
TS_CAPI TSFUTarget TS_CCALL tsFUTarget_castTargetPtr(TSTarget base);
TS_CAPI TSTarget TS_CCALL tsFUTarget_baseTargetPtr(TSFUTarget self);
TS_CAPI void TS_CCALL tsFUTarget_setMask(TSFUTarget self, uint32_t mask);
TS_CAPI uint32_t TS_CCALL tsFUTarget_getMask(TSFUTarget self);
TS_CAPI uint32_t TS_CCALL tsFUTarget_getNumTargets(TSFUTarget self);
TS_CAPI TSTarget TS_CCALL tsFUTarget_getTarget_cu(TSFUTarget self, uint32_t index);
TS_CAPI TSTarget TS_CCALL tsFUTarget_getTarget_u(TSFUTarget self, uint32_t index);

/// Tellusim::Device
TS_CAPI TSDevice TS_CCALL tsDevice_new(void);
TS_CAPI TSDevice TS_CCALL tsDevice_new_C(TSContext context);
TS_CAPI TSDevice TS_CCALL tsDevice_new_S(TSSurface surface);
TS_CAPI TSDevice TS_CCALL tsDevice_new_W(TSWindow window);
TS_CAPI void TS_CCALL tsDevice_delete(TSDevice self);
TS_CAPI bool_t TS_CCALL tsDevice_equalPtr(const TSDevice self, const TSDevice ptr);
TS_CAPI TSDevice TS_CCALL tsDevice_copyPtr(const TSDevice self);
TS_CAPI TSDevice TS_CCALL tsDevice_clonePtr(const TSDevice self);
TS_CAPI void TS_CCALL tsDevice_clearPtr(TSDevice self);
TS_CAPI void TS_CCALL tsDevice_destroyPtr(TSDevice self);
TS_CAPI void TS_CCALL tsDevice_acquirePtr(TSDevice self);
TS_CAPI void TS_CCALL tsDevice_unacquirePtr(TSDevice self);
TS_CAPI bool_t TS_CCALL tsDevice_isValidPtr(const TSDevice self);
TS_CAPI bool_t TS_CCALL tsDevice_isOwnerPtr(const TSDevice self);
TS_CAPI bool_t TS_CCALL tsDevice_isConstPtr(const TSDevice self);
TS_CAPI uint32_t TS_CCALL tsDevice_getCountPtr(const TSDevice self);
TS_CAPI const void* TS_CCALL tsDevice_getInternalPtr(const TSDevice self);
TS_CAPI TS_Platform TS_CCALL tsDevice_getPlatform(TSDevice self);
TS_CAPI const char* TS_CCALL tsDevice_getPlatformName(TSDevice self);
TS_CAPI uint32_t TS_CCALL tsDevice_getIndex(TSDevice self);
TS_CAPI TSString TS_CCALL tsDevice_getName(TSDevice self);
TS_CAPI TSString TS_CCALL tsDevice_getVendor(TSDevice self);
TS_CAPI TSString TS_CCALL tsDevice_getVersion(TSDevice self);
TS_CAPI TSDeviceFeatures TS_CCALL tsDevice_getFeatures(TSDevice self);
TS_CAPI bool_t TS_CCALL tsDevice_hasQuery(TSDevice self, TS_QueryType type);
TS_CAPI bool_t TS_CCALL tsDevice_hasShader(TSDevice self, TS_ShaderType type);
TS_CAPI bool_t TS_CCALL tsDevice_hasTarget(TSDevice self, TS_Format format);
TS_CAPI bool_t TS_CCALL tsDevice_hasTexture(TSDevice self, TS_Format format);
TS_CAPI bool_t TS_CCALL tsDevice_hasSurface(TSDevice self, TS_Format format);
TS_CAPI TSDevice TS_CCALL tsDevice_createDevice(TSDevice self, uint32_t index, uint32_t frames);
TS_CAPI TSDevice TS_CCALL tsDevice_createCommandDevice(TSDevice self, uint32_t frames);
TS_CAPI TSDevice TS_CCALL tsDevice_createComputeDevice(TSDevice self, uint32_t frames);
TS_CAPI TSDevice TS_CCALL tsDevice_createCopyDevice(TSDevice self, uint32_t frames);
TS_CAPI TSQuery TS_CCALL tsDevice_createQuery_c(TSDevice self);
TS_CAPI TSQuery TS_CCALL tsDevice_createQuery_cQT(TSDevice self, TS_QueryType type);
TS_CAPI TSFence TS_CCALL tsDevice_createFence_c(TSDevice self);
TS_CAPI TSFence TS_CCALL tsDevice_createFence_cF(TSDevice self, TSFence shared);
TS_CAPI TSFence TS_CCALL tsDevice_createFence_cFF(TSDevice self, TS_FenceFlags flags);
TS_CAPI TSBuffer TS_CCALL tsDevice_createBuffer_c(TSDevice self);
TS_CAPI TSBuffer TS_CCALL tsDevice_createBuffer_cB(TSDevice self, TSBuffer shared);
TS_CAPI TSBuffer TS_CCALL tsDevice_createBuffer_cBFzF(TSDevice self, TS_BufferFlags flags, size_t size, TS_Format format);
TS_CAPI TSBuffer TS_CCALL tsDevice_createBuffer_cBFpzF(TSDevice self, TS_BufferFlags flags, const void *src, size_t size, TS_Format format);
TS_CAPI TSSampler TS_CCALL tsDevice_createSampler_c(TSDevice self);
TS_CAPI TSSampler TS_CCALL tsDevice_createSampler_ccS(TSDevice self, const TSSampler sampler);
TS_CAPI TSSampler TS_CCALL tsDevice_createSampler_cSFSWMu(TSDevice self, TS_SamplerFilter filter, TS_SamplerWrapMode mode, uint32_t anisotropy);
TS_CAPI TSTexture TS_CCALL tsDevice_createTexture_c(TSDevice self);
TS_CAPI TSTexture TS_CCALL tsDevice_createTexture_cT(TSDevice self, TSTexture shared);
TS_CAPI TSTexture TS_CCALL tsDevice_createTexture_cTTFcSuTF(TSDevice self, TS_TextureType type, TS_Format format, const TSSize *size, uint32_t layers, TS_TextureFlags flags);
TS_CAPI TSTexture TS_CCALL tsDevice_createTexture_cTTFcSTF(TSDevice self, TS_TextureType type, TS_Format format, const TSSize *size, TS_TextureFlags flags);
TS_CAPI TSTexture TS_CCALL tsDevice_createTexture_ccITFA(TSDevice self, const TSImage image, TS_TextureFlags flags, TSAsync *async);
TS_CAPI TSTexture TS_CCALL tsDevice_createTexture2D_cFuTF(TSDevice self, TS_Format format, uint32_t size, TS_TextureFlags flags);
TS_CAPI TSTexture TS_CCALL tsDevice_createTexture3D_cFuTF(TSDevice self, TS_Format format, uint32_t size, TS_TextureFlags flags);
TS_CAPI TSTexture TS_CCALL tsDevice_createTextureCube_cFuTF(TSDevice self, TS_Format format, uint32_t size, TS_TextureFlags flags);
TS_CAPI TSTexture TS_CCALL tsDevice_createTexture2D_cFuuTF(TSDevice self, TS_Format format, uint32_t width, uint32_t height, TS_TextureFlags flags);
TS_CAPI TSTexture TS_CCALL tsDevice_createTexture3D_cFuuuTF(TSDevice self, TS_Format format, uint32_t width, uint32_t height, uint32_t depth, TS_TextureFlags flags);
TS_CAPI TSTexture TS_CCALL tsDevice_createTexture2D_cFuuuTF(TSDevice self, TS_Format format, uint32_t width, uint32_t height, uint32_t layers, TS_TextureFlags flags);
TS_CAPI TSTexture TS_CCALL tsDevice_createTextureCube_cFuuTF(TSDevice self, TS_Format format, uint32_t size, uint32_t layers, TS_TextureFlags flags);
TS_CAPI TSTexture TS_CCALL tsDevice_loadTexture_csTFIFuA(TSDevice self, const char *name, TS_TextureFlags flags, TS_ImageFlags image_flags, uint32_t offset, TSAsync *async);
TS_CAPI TSTexture TS_CCALL tsDevice_loadTexture_ccSTFIFuA(TSDevice self, const TSString name, TS_TextureFlags flags, TS_ImageFlags image_flags, uint32_t offset, TSAsync *async);
TS_CAPI TSTexture TS_CCALL tsDevice_loadTexture_cStTFIFuA(TSDevice self, TSStream stream, TS_TextureFlags flags, TS_ImageFlags image_flags, uint32_t offset, TSAsync *async);
TS_CAPI TSTracing TS_CCALL tsDevice_createTracing_c(TSDevice self);
TS_CAPI TSTracing TS_CCALL tsDevice_createTracing_ccT(TSDevice self, const TSTracing tracing);
TS_CAPI TSTracing TS_CCALL tsDevice_createTracing_cuBzTF(TSDevice self, uint32_t num_instances, TSBuffer instance_buffer, size_t instance_offset, TS_TracingFlags flags);
TS_CAPI TSTracing TS_CCALL tsDevice_createTracing_cuFzuFTF(TSDevice self, uint32_t num_vertices, TS_Format vertex_format, size_t vertex_stride, uint32_t num_indices, TS_Format index_format, TS_TracingFlags flags);
TS_CAPI TSTracing TS_CCALL tsDevice_createTracing_cuzBzTF(TSDevice self, uint32_t num_bounds, size_t bound_stride, TSBuffer bound_buffer, size_t bound_offset, TS_TracingFlags flags);
TS_CAPI TSBufferTable TS_CCALL tsDevice_createBufferTable_c(TSDevice self);
TS_CAPI TSBufferTable TS_CCALL tsDevice_createBufferTable_cu(TSDevice self, uint32_t size);
TS_CAPI TSBufferTable TS_CCALL tsDevice_createBufferTable_ccABb(TSDevice self, const TSBuffer *buffers, uint32_t buffers_size, bool_t owner);
TS_CAPI TSTextureTable TS_CCALL tsDevice_createTextureTable_c(TSDevice self);
TS_CAPI TSTextureTable TS_CCALL tsDevice_createTextureTable_cTTu(TSDevice self, TS_TextureType type, uint32_t size);
TS_CAPI TSTextureTable TS_CCALL tsDevice_createTextureTable_ccATb(TSDevice self, const TSTexture *textures, uint32_t textures_size, bool_t owner);
TS_CAPI TSShader TS_CCALL tsDevice_createShader_c(TSDevice self);
TS_CAPI TSShader TS_CCALL tsDevice_loadShader_cSTss(TSDevice self, TS_ShaderType type, const char *name, const char *format);
TS_CAPI TSShader TS_CCALL tsDevice_loadShaderGLSL_cSTss(TSDevice self, TS_ShaderType type, const char *name, const char *format);
TS_CAPI TSShader TS_CCALL tsDevice_loadShader_cSTscS(TSDevice self, TS_ShaderType type, const char *name, const TSString macros);
TS_CAPI TSShader TS_CCALL tsDevice_loadShaderGLSL_cSTscS(TSDevice self, TS_ShaderType type, const char *name, const TSString macros);
TS_CAPI TSShader TS_CCALL tsDevice_loadShaderSPIRV(TSDevice self, TS_ShaderType type, const char *name);
TS_CAPI TSShader TS_CCALL tsDevice_createShader_cSTss(TSDevice self, TS_ShaderType type, const char *src, const char *format);
TS_CAPI TSShader TS_CCALL tsDevice_createShaderGLSL_cSTss(TSDevice self, TS_ShaderType type, const char *src, const char *format);
TS_CAPI TSShader TS_CCALL tsDevice_createShader_cSTscS(TSDevice self, TS_ShaderType type, const char *src, const TSString macros);
TS_CAPI TSShader TS_CCALL tsDevice_createShaderGLSL_cSTscS(TSDevice self, TS_ShaderType type, const char *src, const TSString macros);
TS_CAPI TSShader TS_CCALL tsDevice_createShaderSPIRV(TSDevice self, TS_ShaderType type, const uint32_t *data, uint32_t data_size);
TS_CAPI TSKernel TS_CCALL tsDevice_createKernel_c(TSDevice self);
TS_CAPI TSKernel TS_CCALL tsDevice_createKernel_ccK(TSDevice self, const TSKernel kernel);
TS_CAPI void TS_CCALL tsDevice_releaseKernel(TSDevice self, TSKernel kernel);
TS_CAPI TSPipeline TS_CCALL tsDevice_createPipeline_c(TSDevice self);
TS_CAPI TSPipeline TS_CCALL tsDevice_createPipeline_ccP(TSDevice self, const TSPipeline pipeline);
TS_CAPI void TS_CCALL tsDevice_releasePipeline(TSDevice self, TSPipeline pipeline);
TS_CAPI TSTraversal TS_CCALL tsDevice_createTraversal_c(TSDevice self);
TS_CAPI TSTraversal TS_CCALL tsDevice_createTraversal_ccT(TSDevice self, const TSTraversal traversal);
TS_CAPI void TS_CCALL tsDevice_releaseTraversal(TSDevice self, TSTraversal traversal);
TS_CAPI TSTarget TS_CCALL tsDevice_createTarget_c(TSDevice self);
TS_CAPI TSTarget TS_CCALL tsDevice_createTarget_cS(TSDevice self, TSSurface surface);
TS_CAPI TSTarget TS_CCALL tsDevice_createTarget_cW(TSDevice self, TSWindow window);
TS_CAPI TSCompute TS_CCALL tsDevice_createCompute(TSDevice self);
TS_CAPI TSCommand TS_CCALL tsDevice_createCommand_c(TSDevice self);
TS_CAPI TSCommand TS_CCALL tsDevice_createCommand_cT(TSDevice self, TSTarget target);
TS_CAPI bool_t TS_CCALL tsDevice_setBuffer_cBzpz(TSDevice self, TSBuffer buffer, size_t offset, const void *src, size_t size);
TS_CAPI bool_t TS_CCALL tsDevice_setBuffer_cBpz(TSDevice self, TSBuffer buffer, const void *src, size_t size);
TS_CAPI bool_t TS_CCALL tsDevice_setBuffer_cBp(TSDevice self, TSBuffer buffer, const void *src);
TS_CAPI bool_t TS_CCALL tsDevice_getBuffer_cBzprz(TSDevice self, TSBuffer buffer, size_t offset, void *dest, size_t size);
TS_CAPI bool_t TS_CCALL tsDevice_getBuffer_cBprz(TSDevice self, TSBuffer buffer, void *dest, size_t size);
TS_CAPI bool_t TS_CCALL tsDevice_getBuffer_cBpr(TSDevice self, TSBuffer buffer, void *dest);
TS_CAPI void* TS_CCALL tsDevice_mapBuffer_cBzz(TSDevice self, TSBuffer buffer, size_t offset, size_t size);
TS_CAPI void* TS_CCALL tsDevice_mapBuffer_cBz(TSDevice self, TSBuffer buffer, size_t size);
TS_CAPI void* TS_CCALL tsDevice_mapBuffer_cB(TSDevice self, TSBuffer buffer);
TS_CAPI bool_t TS_CCALL tsDevice_unmapBuffer(TSDevice self, TSBuffer buffer);
TS_CAPI bool_t TS_CCALL tsDevice_copyBuffer_cBzBzz(TSDevice self, TSBuffer buffer, size_t dest_offset, TSBuffer src, size_t src_offset, size_t size);
TS_CAPI bool_t TS_CCALL tsDevice_copyBuffer_cBzBz(TSDevice self, TSBuffer buffer, size_t dest_offset, TSBuffer src, size_t size);
TS_CAPI bool_t TS_CCALL tsDevice_copyBuffer_cBBz(TSDevice self, TSBuffer buffer, TSBuffer src, size_t size);
TS_CAPI bool_t TS_CCALL tsDevice_copyBuffer_cBB(TSDevice self, TSBuffer buffer, TSBuffer src);
TS_CAPI bool_t TS_CCALL tsDevice_clearBuffer_cBFzpz(TSDevice self, TSBuffer buffer, TS_Format format, size_t offset, const void *src, size_t size);
TS_CAPI bool_t TS_CCALL tsDevice_clearBuffer_cBFpz(TSDevice self, TSBuffer buffer, TS_Format format, const void *src, size_t size);
TS_CAPI bool_t TS_CCALL tsDevice_clearBuffer_cBFp(TSDevice self, TSBuffer buffer, TS_Format format, const void *src);
TS_CAPI bool_t TS_CCALL tsDevice_clearBuffer_cB(TSDevice self, TSBuffer buffer);
TS_CAPI bool_t TS_CCALL tsDevice_bindBuffer_cBcAcAbF(TSDevice self, TSBuffer buffer, const size_t *offsets, uint32_t offsets_size, const size_t *sizes, uint32_t sizes_size, bool_t commit, TSFence fence);
TS_CAPI bool_t TS_CCALL tsDevice_bindBuffer_cBcAcAb(TSDevice self, TSBuffer buffer, const size_t *offsets, uint32_t offsets_size, const size_t *sizes, uint32_t sizes_size, bool_t commit);
TS_CAPI bool_t TS_CCALL tsDevice_bindBuffer_cBzzbF(TSDevice self, TSBuffer buffer, size_t offset, size_t size, bool_t commit, TSFence fence);
TS_CAPI bool_t TS_CCALL tsDevice_bindBuffer_cBzzb(TSDevice self, TSBuffer buffer, size_t offset, size_t size, bool_t commit);
TS_CAPI bool_t TS_CCALL tsDevice_flushBuffer(TSDevice self, TSBuffer buffer, TS_BufferFlags flags);
TS_CAPI bool_t TS_CCALL tsDevice_flushBuffers_ccABBF(TSDevice self, const TSBuffer *buffers, uint32_t buffers_size, TS_BufferFlags flags);
TS_CAPI void TS_CCALL tsDevice_releaseBuffer(TSDevice self, TSBuffer buffer);
TS_CAPI void TS_CCALL tsDevice_releaseSampler(TSDevice self, TSSampler sampler);
TS_CAPI bool_t TS_CCALL tsDevice_setTexture_cTcOcScIcS(TSDevice self, TSTexture texture, const TSOrigin *dest_origin, const TSSlice *dest_slice, const TSImage image, const TSSlice *src_slice);
TS_CAPI bool_t TS_CCALL tsDevice_setTexture_cTcOcI(TSDevice self, TSTexture texture, const TSOrigin *dest_origin, const TSImage image);
TS_CAPI bool_t TS_CCALL tsDevice_setTexture_cTcScI(TSDevice self, TSTexture texture, const TSSlice *dest_slice, const TSImage image);
TS_CAPI bool_t TS_CCALL tsDevice_setTexture_cTcI(TSDevice self, TSTexture texture, const TSImage image);
TS_CAPI bool_t TS_CCALL tsDevice_getTexture_cTcSIcS(TSDevice self, TSTexture texture, const TSSlice *src_slice, TSImage image, const TSSlice *dest_slice);
TS_CAPI bool_t TS_CCALL tsDevice_getTexture_cTIcS(TSDevice self, TSTexture texture, TSImage image, const TSSlice *dest_slice);
TS_CAPI bool_t TS_CCALL tsDevice_getTexture_cTI(TSDevice self, TSTexture texture, TSImage image);
TS_CAPI bool_t TS_CCALL tsDevice_copyTexture_cTcOcSTcRcS(TSDevice self, TSTexture texture, const TSOrigin *dest_origin, const TSSlice *dest_slice, TSTexture src, const TSRegion *src_region, const TSSlice *src_slice);
TS_CAPI bool_t TS_CCALL tsDevice_copyTexture_cTcOTcR(TSDevice self, TSTexture texture, const TSOrigin *dest_origin, TSTexture src, const TSRegion *src_region);
TS_CAPI bool_t TS_CCALL tsDevice_copyTexture_cTcSTcS(TSDevice self, TSTexture texture, const TSSlice *dest_slice, TSTexture src, const TSSlice *src_slice);
TS_CAPI bool_t TS_CCALL tsDevice_copyTexture_cTT(TSDevice self, TSTexture texture, TSTexture src);
TS_CAPI bool_t TS_CCALL tsDevice_clearTexture_cTcRcSp(TSDevice self, TSTexture texture, const TSRegion *region, const TSSlice *slice, const void *src);
TS_CAPI bool_t TS_CCALL tsDevice_clearTexture_cTcRp(TSDevice self, TSTexture texture, const TSRegion *region, const void *src);
TS_CAPI bool_t TS_CCALL tsDevice_clearTexture_cTcSp(TSDevice self, TSTexture texture, const TSSlice *slice, const void *src);
TS_CAPI bool_t TS_CCALL tsDevice_clearTexture_cTp(TSDevice self, TSTexture texture, const void *src);
TS_CAPI bool_t TS_CCALL tsDevice_bindTexture_cTcRucSubF(TSDevice self, TSTexture texture, const TSRegion *regions, uint32_t num_regions, const TSSlice *slices, uint32_t num_slices, bool_t commit, TSFence fence);
TS_CAPI bool_t TS_CCALL tsDevice_bindTexture_cTcRucSub(TSDevice self, TSTexture texture, const TSRegion *regions, uint32_t num_regions, const TSSlice *slices, uint32_t num_slices, bool_t commit);
TS_CAPI bool_t TS_CCALL tsDevice_bindTexture_cTcRcSbF(TSDevice self, TSTexture texture, const TSRegion *region, const TSSlice *slice, bool_t commit, TSFence fence);
TS_CAPI bool_t TS_CCALL tsDevice_bindTexture_cTcRcSb(TSDevice self, TSTexture texture, const TSRegion *region, const TSSlice *slice, bool_t commit);
TS_CAPI bool_t TS_CCALL tsDevice_createMipmaps_cTcS(TSDevice self, TSTexture texture, const TSSlice *slice);
TS_CAPI bool_t TS_CCALL tsDevice_createMipmaps_cT(TSDevice self, TSTexture texture);
TS_CAPI bool_t TS_CCALL tsDevice_flushTexture_cTTF(TSDevice self, TSTexture texture, TS_TextureFlags flags);
TS_CAPI bool_t TS_CCALL tsDevice_flushTexture_cTcSTF(TSDevice self, TSTexture texture, const TSSlice *slice, TS_TextureFlags flags);
TS_CAPI bool_t TS_CCALL tsDevice_flushTextures_ccATTF(TSDevice self, const TSTexture *textures, uint32_t textures_size, TS_TextureFlags flags);
TS_CAPI void TS_CCALL tsDevice_releaseTexture(TSDevice self, TSTexture texture);
TS_CAPI bool_t TS_CCALL tsDevice_setTracing(TSDevice self, TSTracing tracing, const TSTracingInstance *instances, uint32_t num_instances);
TS_CAPI bool_t TS_CCALL tsDevice_buildTracing_cTBTF(TSDevice self, TSTracing tracing, TSBuffer buffer, TS_TracingFlags flags);
TS_CAPI bool_t TS_CCALL tsDevice_buildTracing_cTBzTF(TSDevice self, TSTracing tracing, TSBuffer buffer, size_t offset, TS_TracingFlags flags);
TS_CAPI bool_t TS_CCALL tsDevice_buildTracings_ccATBTF(TSDevice self, const TSTracing *tracings, uint32_t tracings_size, TSBuffer buffer, TS_TracingFlags flags);
TS_CAPI bool_t TS_CCALL tsDevice_buildTracings_ccATBzTF(TSDevice self, const TSTracing *tracings, uint32_t tracings_size, TSBuffer buffer, size_t offset, TS_TracingFlags flags);
TS_CAPI bool_t TS_CCALL tsDevice_copyTracing(TSDevice self, TSTracing tracing, TSBuffer buffer, size_t offset);
TS_CAPI bool_t TS_CCALL tsDevice_copyTracings(TSDevice self, const TSTracing *tracings, uint32_t tracings_size, TSBuffer buffer, size_t offset, size_t stride);
TS_CAPI bool_t TS_CCALL tsDevice_flushTracing(TSDevice self, TSTracing tracing);
TS_CAPI bool_t TS_CCALL tsDevice_flushTracings(TSDevice self, const TSTracing *tracings, uint32_t tracings_size);
TS_CAPI void TS_CCALL tsDevice_releaseTracing(TSDevice self, TSTracing tracing);
TS_CAPI bool_t TS_CCALL tsDevice_setBufferTable_cBTuBb(TSDevice self, TSBufferTable table, uint32_t index, TSBuffer buffer, bool_t owner);
TS_CAPI bool_t TS_CCALL tsDevice_setBufferTable_cBTucABb(TSDevice self, TSBufferTable table, uint32_t index, const TSBuffer *buffers, uint32_t buffers_size, bool_t owner);
TS_CAPI void TS_CCALL tsDevice_releaseBufferTable(TSDevice self, TSBufferTable table);
TS_CAPI bool_t TS_CCALL tsDevice_setTextureTable_cTTuTb(TSDevice self, TSTextureTable table, uint32_t index, TSTexture texture, bool_t owner);
TS_CAPI bool_t TS_CCALL tsDevice_setTextureTable_cTTucATb(TSDevice self, TSTextureTable table, uint32_t index, const TSTexture *textures, uint32_t textures_size, bool_t owner);
TS_CAPI void TS_CCALL tsDevice_releaseTextureTable(TSDevice self, TSTextureTable table);
TS_CAPI bool_t TS_CCALL tsDevice_beginQuery(TSDevice self, TSQuery query);
TS_CAPI void TS_CCALL tsDevice_endQuery(TSDevice self, TSQuery query);
TS_CAPI bool_t TS_CCALL tsDevice_copyQuery(TSDevice self, TSQuery query, TSBuffer buffer, size_t offset);
TS_CAPI bool_t TS_CCALL tsDevice_copyQueries_ccAQBzz(TSDevice self, const TSQuery *queries, uint32_t queries_size, TSBuffer buffer, size_t offset, size_t stride);
TS_CAPI bool_t TS_CCALL tsDevice_waitFence(TSDevice self, TSFence fence);
TS_CAPI bool_t TS_CCALL tsDevice_signalFence(TSDevice self, TSFence fence);
TS_CAPI bool_t TS_CCALL tsDevice_execute(TSDevice self, TSDevice device);
TS_CAPI bool_t TS_CCALL tsDevice_flip_cF(TSDevice self, TSFence fence);
TS_CAPI bool_t TS_CCALL tsDevice_flip_c(TSDevice self);
TS_CAPI bool_t TS_CCALL tsDevice_flush(TSDevice self);
TS_CAPI bool_t TS_CCALL tsDevice_finish(TSDevice self);
TS_CAPI bool_t TS_CCALL tsDevice_check(TSDevice self);

/// Tellusim::D3D12Device
TS_CAPI TSD3D12Device TS_CCALL tsD3D12Device_new(void);
TS_CAPI TSD3D12Device TS_CCALL tsD3D12Device_new_C(TSContext context);
TS_CAPI TSD3D12Device TS_CCALL tsD3D12Device_new_S(TSSurface surface);
TS_CAPI TSD3D12Device TS_CCALL tsD3D12Device_new_W(TSWindow window);
TS_CAPI void TS_CCALL tsD3D12Device_delete(TSD3D12Device self);
TS_CAPI bool_t TS_CCALL tsD3D12Device_equalPtr(const TSD3D12Device self, const TSD3D12Device ptr);
TS_CAPI TSD3D12Device TS_CCALL tsD3D12Device_copyPtr(const TSD3D12Device self);
TS_CAPI TSD3D12Device TS_CCALL tsD3D12Device_clonePtr(const TSD3D12Device self);
TS_CAPI void TS_CCALL tsD3D12Device_clearPtr(TSD3D12Device self);
TS_CAPI void TS_CCALL tsD3D12Device_destroyPtr(TSD3D12Device self);
TS_CAPI void TS_CCALL tsD3D12Device_acquirePtr(TSD3D12Device self);
TS_CAPI void TS_CCALL tsD3D12Device_unacquirePtr(TSD3D12Device self);
TS_CAPI bool_t TS_CCALL tsD3D12Device_isValidPtr(const TSD3D12Device self);
TS_CAPI bool_t TS_CCALL tsD3D12Device_isOwnerPtr(const TSD3D12Device self);
TS_CAPI bool_t TS_CCALL tsD3D12Device_isConstPtr(const TSD3D12Device self);
TS_CAPI uint32_t TS_CCALL tsD3D12Device_getCountPtr(const TSD3D12Device self);
TS_CAPI const void* TS_CCALL tsD3D12Device_getInternalPtr(const TSD3D12Device self);
TS_CAPI bool_t TS_CCALL tsD3D12Device_equalDevicePtr(const TSD3D12Device self, const TSDevice base);
TS_CAPI TSD3D12Device TS_CCALL tsD3D12Device_castDevicePtr(TSDevice base);
TS_CAPI TSDevice TS_CCALL tsD3D12Device_baseDevicePtr(TSD3D12Device self);
TS_CAPI void TS_CCALL tsD3D12Device_setBufferState(TSD3D12Device self, TSBuffer buffer, uint32_t state);
TS_CAPI void TS_CCALL tsD3D12Device_setTextureState(TSD3D12Device self, TSTexture texture, uint32_t state);
TS_CAPI ID3D12Device* TS_CCALL tsD3D12Device_getD3D12Device(TSD3D12Device self);
TS_CAPI ID3D12CommandQueue* TS_CCALL tsD3D12Device_getQueue(TSD3D12Device self);
TS_CAPI ID3D12GraphicsCommandList* TS_CCALL tsD3D12Device_getCommand(TSD3D12Device self);
TS_CAPI const void* TS_CCALL tsD3D12Device_getD3D12Features(TSD3D12Device self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsD3D12Device_getShaderModel(TSD3D12Device self);

/// Tellusim::D3D11Device
TS_CAPI TSD3D11Device TS_CCALL tsD3D11Device_new(void);
TS_CAPI TSD3D11Device TS_CCALL tsD3D11Device_new_C(TSContext context);
TS_CAPI TSD3D11Device TS_CCALL tsD3D11Device_new_S(TSSurface surface);
TS_CAPI TSD3D11Device TS_CCALL tsD3D11Device_new_W(TSWindow window);
TS_CAPI void TS_CCALL tsD3D11Device_delete(TSD3D11Device self);
TS_CAPI bool_t TS_CCALL tsD3D11Device_equalPtr(const TSD3D11Device self, const TSD3D11Device ptr);
TS_CAPI TSD3D11Device TS_CCALL tsD3D11Device_copyPtr(const TSD3D11Device self);
TS_CAPI TSD3D11Device TS_CCALL tsD3D11Device_clonePtr(const TSD3D11Device self);
TS_CAPI void TS_CCALL tsD3D11Device_clearPtr(TSD3D11Device self);
TS_CAPI void TS_CCALL tsD3D11Device_destroyPtr(TSD3D11Device self);
TS_CAPI void TS_CCALL tsD3D11Device_acquirePtr(TSD3D11Device self);
TS_CAPI void TS_CCALL tsD3D11Device_unacquirePtr(TSD3D11Device self);
TS_CAPI bool_t TS_CCALL tsD3D11Device_isValidPtr(const TSD3D11Device self);
TS_CAPI bool_t TS_CCALL tsD3D11Device_isOwnerPtr(const TSD3D11Device self);
TS_CAPI bool_t TS_CCALL tsD3D11Device_isConstPtr(const TSD3D11Device self);
TS_CAPI uint32_t TS_CCALL tsD3D11Device_getCountPtr(const TSD3D11Device self);
TS_CAPI const void* TS_CCALL tsD3D11Device_getInternalPtr(const TSD3D11Device self);
TS_CAPI bool_t TS_CCALL tsD3D11Device_equalDevicePtr(const TSD3D11Device self, const TSDevice base);
TS_CAPI TSD3D11Device TS_CCALL tsD3D11Device_castDevicePtr(TSDevice base);
TS_CAPI TSDevice TS_CCALL tsD3D11Device_baseDevicePtr(TSD3D11Device self);
TS_CAPI ID3D11Device* TS_CCALL tsD3D11Device_getD3D11Device(TSD3D11Device self);
TS_CAPI ID3D11DeviceContext* TS_CCALL tsD3D11Device_getCommand(TSD3D11Device self);
TS_CAPI const void* TS_CCALL tsD3D11Device_getD3D11Features(TSD3D11Device self, uint32_t index);

/// Tellusim::MTLDevice
TS_CAPI TSMTLDevice TS_CCALL tsMTLDevice_new(void);
TS_CAPI TSMTLDevice TS_CCALL tsMTLDevice_new_C(TSContext context);
TS_CAPI TSMTLDevice TS_CCALL tsMTLDevice_new_S(TSSurface surface);
TS_CAPI TSMTLDevice TS_CCALL tsMTLDevice_new_W(TSWindow window);
TS_CAPI void TS_CCALL tsMTLDevice_delete(TSMTLDevice self);
TS_CAPI bool_t TS_CCALL tsMTLDevice_equalPtr(const TSMTLDevice self, const TSMTLDevice ptr);
TS_CAPI TSMTLDevice TS_CCALL tsMTLDevice_copyPtr(const TSMTLDevice self);
TS_CAPI TSMTLDevice TS_CCALL tsMTLDevice_clonePtr(const TSMTLDevice self);
TS_CAPI void TS_CCALL tsMTLDevice_clearPtr(TSMTLDevice self);
TS_CAPI void TS_CCALL tsMTLDevice_destroyPtr(TSMTLDevice self);
TS_CAPI void TS_CCALL tsMTLDevice_acquirePtr(TSMTLDevice self);
TS_CAPI void TS_CCALL tsMTLDevice_unacquirePtr(TSMTLDevice self);
TS_CAPI bool_t TS_CCALL tsMTLDevice_isValidPtr(const TSMTLDevice self);
TS_CAPI bool_t TS_CCALL tsMTLDevice_isOwnerPtr(const TSMTLDevice self);
TS_CAPI bool_t TS_CCALL tsMTLDevice_isConstPtr(const TSMTLDevice self);
TS_CAPI uint32_t TS_CCALL tsMTLDevice_getCountPtr(const TSMTLDevice self);
TS_CAPI const void* TS_CCALL tsMTLDevice_getInternalPtr(const TSMTLDevice self);
TS_CAPI bool_t TS_CCALL tsMTLDevice_equalDevicePtr(const TSMTLDevice self, const TSDevice base);
TS_CAPI TSMTLDevice TS_CCALL tsMTLDevice_castDevicePtr(TSDevice base);
TS_CAPI TSDevice TS_CCALL tsMTLDevice_baseDevicePtr(TSMTLDevice self);
TS_CAPI void* TS_CCALL tsMTLDevice_getMTLDevice(TSMTLDevice self);
TS_CAPI void* TS_CCALL tsMTLDevice_getQueue(TSMTLDevice self);
TS_CAPI void* TS_CCALL tsMTLDevice_getCommand(TSMTLDevice self);
TS_CAPI void* TS_CCALL tsMTLDevice_getEncoder(TSMTLDevice self);
TS_CAPI void* TS_CCALL tsMTLDevice_getRenderEncoder(TSMTLDevice self, void *descriptor);
TS_CAPI void* TS_CCALL tsMTLDevice_getComputeEncoder(TSMTLDevice self);
TS_CAPI void* TS_CCALL tsMTLDevice_getTracingEncoder(TSMTLDevice self);
TS_CAPI void* TS_CCALL tsMTLDevice_getBlitEncoder(TSMTLDevice self);
TS_CAPI void TS_CCALL tsMTLDevice_endEncoder(TSMTLDevice self);

/// Tellusim::VKDevice
TS_CAPI TSVKDevice TS_CCALL tsVKDevice_new(void);
TS_CAPI TSVKDevice TS_CCALL tsVKDevice_new_C(TSContext context);
TS_CAPI TSVKDevice TS_CCALL tsVKDevice_new_S(TSSurface surface);
TS_CAPI TSVKDevice TS_CCALL tsVKDevice_new_W(TSWindow window);
TS_CAPI void TS_CCALL tsVKDevice_delete(TSVKDevice self);
TS_CAPI bool_t TS_CCALL tsVKDevice_equalPtr(const TSVKDevice self, const TSVKDevice ptr);
TS_CAPI TSVKDevice TS_CCALL tsVKDevice_copyPtr(const TSVKDevice self);
TS_CAPI TSVKDevice TS_CCALL tsVKDevice_clonePtr(const TSVKDevice self);
TS_CAPI void TS_CCALL tsVKDevice_clearPtr(TSVKDevice self);
TS_CAPI void TS_CCALL tsVKDevice_destroyPtr(TSVKDevice self);
TS_CAPI void TS_CCALL tsVKDevice_acquirePtr(TSVKDevice self);
TS_CAPI void TS_CCALL tsVKDevice_unacquirePtr(TSVKDevice self);
TS_CAPI bool_t TS_CCALL tsVKDevice_isValidPtr(const TSVKDevice self);
TS_CAPI bool_t TS_CCALL tsVKDevice_isOwnerPtr(const TSVKDevice self);
TS_CAPI bool_t TS_CCALL tsVKDevice_isConstPtr(const TSVKDevice self);
TS_CAPI uint32_t TS_CCALL tsVKDevice_getCountPtr(const TSVKDevice self);
TS_CAPI const void* TS_CCALL tsVKDevice_getInternalPtr(const TSVKDevice self);
TS_CAPI bool_t TS_CCALL tsVKDevice_equalDevicePtr(const TSVKDevice self, const TSDevice base);
TS_CAPI TSVKDevice TS_CCALL tsVKDevice_castDevicePtr(TSDevice base);
TS_CAPI TSDevice TS_CCALL tsVKDevice_baseDevicePtr(TSVKDevice self);
TS_CAPI void TS_CCALL tsVKDevice_setBufferAccess(TSVKDevice self, TSBuffer buffer, uint32_t access);
TS_CAPI void TS_CCALL tsVKDevice_setTextureLayout(TSVKDevice self, TSTexture texture, uint32_t layout);
TS_CAPI bool_t TS_CCALL tsVKDevice_waitVKFence(TSVKDevice self, void *fence, uint64_t timeout, bool_t reset);
TS_CAPI bool_t TS_CCALL tsVKDevice_signalVKFence(TSVKDevice self, void *fence);
TS_CAPI void TS_CCALL tsVKDevice_waitSemaphore(TSVKDevice self, void *semaphore, uint32_t mask);
TS_CAPI void TS_CCALL tsVKDevice_signalSemaphore(TSVKDevice self, void *semaphore);
TS_CAPI bool_t TS_CCALL tsVKDevice_hasMemoryType(TSVKDevice self, uint32_t flags);
TS_CAPI uint32_t TS_CCALL tsVKDevice_getMemoryIndex(TSVKDevice self, uint32_t types, uint32_t flags);
TS_CAPI VkInstance TS_CCALL tsVKDevice_getInstance(TSVKDevice self);
TS_CAPI VkPhysicalDevice TS_CCALL tsVKDevice_getAdapter(TSVKDevice self);
TS_CAPI VkDevice TS_CCALL tsVKDevice_getVKDevice(TSVKDevice self);
TS_CAPI VkQueue TS_CCALL tsVKDevice_getQueue(TSVKDevice self);
TS_CAPI VkCommandBuffer TS_CCALL tsVKDevice_getCommand(TSVKDevice self);
TS_CAPI uint32_t TS_CCALL tsVKDevice_getFamily(TSVKDevice self);
TS_CAPI const void* TS_CCALL tsVKDevice_getVKFeatures(TSVKDevice self, uint32_t type);

/// Tellusim::FUDevice
TS_CAPI TSFUDevice TS_CCALL tsFUDevice_new(void);
TS_CAPI TSFUDevice TS_CCALL tsFUDevice_new_cADb(const TSDevice *devices, uint32_t devices_size, bool_t owner);
TS_CAPI void TS_CCALL tsFUDevice_delete(TSFUDevice self);
TS_CAPI bool_t TS_CCALL tsFUDevice_equalPtr(const TSFUDevice self, const TSFUDevice ptr);
TS_CAPI TSFUDevice TS_CCALL tsFUDevice_copyPtr(const TSFUDevice self);
TS_CAPI TSFUDevice TS_CCALL tsFUDevice_clonePtr(const TSFUDevice self);
TS_CAPI void TS_CCALL tsFUDevice_clearPtr(TSFUDevice self);
TS_CAPI void TS_CCALL tsFUDevice_destroyPtr(TSFUDevice self);
TS_CAPI void TS_CCALL tsFUDevice_acquirePtr(TSFUDevice self);
TS_CAPI void TS_CCALL tsFUDevice_unacquirePtr(TSFUDevice self);
TS_CAPI bool_t TS_CCALL tsFUDevice_isValidPtr(const TSFUDevice self);
TS_CAPI bool_t TS_CCALL tsFUDevice_isOwnerPtr(const TSFUDevice self);
TS_CAPI bool_t TS_CCALL tsFUDevice_isConstPtr(const TSFUDevice self);
TS_CAPI uint32_t TS_CCALL tsFUDevice_getCountPtr(const TSFUDevice self);
TS_CAPI const void* TS_CCALL tsFUDevice_getInternalPtr(const TSFUDevice self);
TS_CAPI bool_t TS_CCALL tsFUDevice_equalDevicePtr(const TSFUDevice self, const TSDevice base);
TS_CAPI TSFUDevice TS_CCALL tsFUDevice_castDevicePtr(TSDevice base);
TS_CAPI TSDevice TS_CCALL tsFUDevice_baseDevicePtr(TSFUDevice self);
TS_CAPI void TS_CCALL tsFUDevice_setMask(TSFUDevice self, uint32_t mask);
TS_CAPI uint32_t TS_CCALL tsFUDevice_getMask(TSFUDevice self);
TS_CAPI uint32_t TS_CCALL tsFUDevice_getNumDevices(TSFUDevice self);
TS_CAPI TSDevice TS_CCALL tsFUDevice_getDevice_cu(TSFUDevice self, uint32_t index);
TS_CAPI TSDevice TS_CCALL tsFUDevice_getDevice_u(TSFUDevice self, uint32_t index);

/// Tellusim::Kernel
TS_CAPI TSKernel TS_CCALL tsKernel_new(void);
TS_CAPI void TS_CCALL tsKernel_delete(TSKernel self);
TS_CAPI bool_t TS_CCALL tsKernel_equalPtr(const TSKernel self, const TSKernel ptr);
TS_CAPI TSKernel TS_CCALL tsKernel_copyPtr(const TSKernel self);
TS_CAPI TSKernel TS_CCALL tsKernel_clonePtr(const TSKernel self);
TS_CAPI void TS_CCALL tsKernel_clearPtr(TSKernel self);
TS_CAPI void TS_CCALL tsKernel_destroyPtr(TSKernel self);
TS_CAPI void TS_CCALL tsKernel_acquirePtr(TSKernel self);
TS_CAPI void TS_CCALL tsKernel_unacquirePtr(TSKernel self);
TS_CAPI bool_t TS_CCALL tsKernel_isValidPtr(const TSKernel self);
TS_CAPI bool_t TS_CCALL tsKernel_isOwnerPtr(const TSKernel self);
TS_CAPI bool_t TS_CCALL tsKernel_isConstPtr(const TSKernel self);
TS_CAPI uint32_t TS_CCALL tsKernel_getCountPtr(const TSKernel self);
TS_CAPI const void* TS_CCALL tsKernel_getInternalPtr(const TSKernel self);
TS_CAPI TS_Platform TS_CCALL tsKernel_getPlatform(TSKernel self);
TS_CAPI const char* TS_CCALL tsKernel_getPlatformName(TSKernel self);
TS_CAPI uint32_t TS_CCALL tsKernel_getIndex(TSKernel self);
TS_CAPI void TS_CCALL tsKernel_clear(TSKernel self);
TS_CAPI bool_t TS_CCALL tsKernel_isCreated(TSKernel self);
TS_CAPI void TS_CCALL tsKernel_setName(TSKernel self, const char *name);
TS_CAPI TSString TS_CCALL tsKernel_getName(TSKernel self);
TS_CAPI bool_t TS_CCALL tsKernel_create(TSKernel self);
TS_CAPI void TS_CCALL tsKernel_setParameters(TSKernel self, const TSKernel kernel);
TS_CAPI bool_t TS_CCALL tsKernel_saveState(TSKernel self, TSStream stream);
TS_CAPI void TS_CCALL tsKernel_setShader(TSKernel self, TSShader shader, bool_t owner);
TS_CAPI TSShader TS_CCALL tsKernel_getComputeShader(TSKernel self);
TS_CAPI bool_t TS_CCALL tsKernel_loadShader_ss(TSKernel self, const char *name, const char *format);
TS_CAPI bool_t TS_CCALL tsKernel_loadShaderGLSL_ss(TSKernel self, const char *name, const char *format);
TS_CAPI bool_t TS_CCALL tsKernel_loadShader_scSspu(TSKernel self, const char *name, const TSString macros, const char **includes, uint32_t size);
TS_CAPI bool_t TS_CCALL tsKernel_loadShaderGLSL_scSspu(TSKernel self, const char *name, const TSString macros, const char **includes, uint32_t size);
TS_CAPI bool_t TS_CCALL tsKernel_loadShaderSPIRV(TSKernel self, const char *name);
TS_CAPI bool_t TS_CCALL tsKernel_createShader_ss(TSKernel self, const char *src, const char *format);
TS_CAPI bool_t TS_CCALL tsKernel_createShaderGLSL_ss(TSKernel self, const char *src, const char *format);
TS_CAPI bool_t TS_CCALL tsKernel_createShader_scSspu(TSKernel self, const char *src, const TSString macros, const char **includes, uint32_t size);
TS_CAPI bool_t TS_CCALL tsKernel_createShaderGLSL_scSspu(TSKernel self, const char *src, const TSString macros, const char **includes, uint32_t size);
TS_CAPI bool_t TS_CCALL tsKernel_createShaderSPIRV(TSKernel self, const uint32_t *data, uint32_t data_size);
TS_CAPI uint32_t TS_CCALL tsKernel_addSampler(TSKernel self);
TS_CAPI TSKernel TS_CCALL tsKernel_setSamplers(TSKernel self, uint32_t num);
TS_CAPI uint32_t TS_CCALL tsKernel_getNumSamplers(TSKernel self);
TS_CAPI TSKernel TS_CCALL tsKernel_setSamplerOffset(TSKernel self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsKernel_getSamplerOffset(TSKernel self);
TS_CAPI TSKernel TS_CCALL tsKernel_setSamplerArray(TSKernel self, uint32_t index, uint32_t num, bool_t array);
TS_CAPI uint32_t TS_CCALL tsKernel_getSamplerArray(TSKernel self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsKernel_addTexture(TSKernel self);
TS_CAPI TSKernel TS_CCALL tsKernel_setTextures(TSKernel self, uint32_t num);
TS_CAPI uint32_t TS_CCALL tsKernel_getNumTextures(TSKernel self);
TS_CAPI TSKernel TS_CCALL tsKernel_setTextureOffset(TSKernel self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsKernel_getTextureOffset(TSKernel self);
TS_CAPI TSKernel TS_CCALL tsKernel_setTextureArray(TSKernel self, uint32_t index, uint32_t num, bool_t array);
TS_CAPI uint32_t TS_CCALL tsKernel_getTextureArray(TSKernel self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsKernel_addSurface(TSKernel self);
TS_CAPI TSKernel TS_CCALL tsKernel_setSurfaces(TSKernel self, uint32_t num);
TS_CAPI uint32_t TS_CCALL tsKernel_getNumSurfaces(TSKernel self);
TS_CAPI TSKernel TS_CCALL tsKernel_setSurfaceOffset(TSKernel self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsKernel_getSurfaceOffset(TSKernel self);
TS_CAPI TSKernel TS_CCALL tsKernel_setSurfaceArray(TSKernel self, uint32_t index, uint32_t num, bool_t array);
TS_CAPI uint32_t TS_CCALL tsKernel_getSurfaceArray(TSKernel self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsKernel_addUniform(TSKernel self, TS_BindFlags flags);
TS_CAPI TSKernel TS_CCALL tsKernel_setUniforms(TSKernel self, uint32_t num, TS_BindFlags flags);
TS_CAPI uint32_t TS_CCALL tsKernel_getNumUniforms(TSKernel self);
TS_CAPI TSKernel TS_CCALL tsKernel_setUniformOffset(TSKernel self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsKernel_getUniformOffset(TSKernel self);
TS_CAPI TSKernel TS_CCALL tsKernel_setUniformFlags(TSKernel self, uint32_t index, TS_BindFlags flags);
TS_CAPI TS_BindFlags TS_CCALL tsKernel_getUniformFlags(TSKernel self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsKernel_addStorage(TSKernel self, TS_BindFlags flags);
TS_CAPI TSKernel TS_CCALL tsKernel_setStorages(TSKernel self, uint32_t num, TS_BindFlags flags);
TS_CAPI uint32_t TS_CCALL tsKernel_getNumStorages(TSKernel self);
TS_CAPI TSKernel TS_CCALL tsKernel_setStorageOffset(TSKernel self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsKernel_getStorageOffset(TSKernel self);
TS_CAPI TSKernel TS_CCALL tsKernel_setStorageFlags(TSKernel self, uint32_t index, TS_BindFlags flags);
TS_CAPI TS_BindFlags TS_CCALL tsKernel_getStorageFlags(TSKernel self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsKernel_addTracing(TSKernel self);
TS_CAPI TSKernel TS_CCALL tsKernel_setTracings(TSKernel self, uint32_t num);
TS_CAPI uint32_t TS_CCALL tsKernel_getNumTracings(TSKernel self);
TS_CAPI TSKernel TS_CCALL tsKernel_setTracingOffset(TSKernel self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsKernel_getTracingOffset(TSKernel self);
TS_CAPI uint32_t TS_CCALL tsKernel_addTexel(TSKernel self);
TS_CAPI TSKernel TS_CCALL tsKernel_setTexels(TSKernel self, uint32_t num);
TS_CAPI uint32_t TS_CCALL tsKernel_getNumTexels(TSKernel self);
TS_CAPI TSKernel TS_CCALL tsKernel_setTexelOffset(TSKernel self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsKernel_getTexelOffset(TSKernel self);
TS_CAPI uint32_t TS_CCALL tsKernel_addTable(TSKernel self, TS_TableType type, uint32_t size);
TS_CAPI uint32_t TS_CCALL tsKernel_getNumTables(TSKernel self);
TS_CAPI TSKernel TS_CCALL tsKernel_setTableOffset(TSKernel self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsKernel_getTableOffset(TSKernel self);
TS_CAPI TSKernel TS_CCALL tsKernel_setTableType(TSKernel self, uint32_t index, TS_TableType type, uint32_t size, TS_BindFlags flags);
TS_CAPI TS_TableType TS_CCALL tsKernel_getTableType(TSKernel self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsKernel_getTableSize(TSKernel self, uint32_t index);
TS_CAPI TSKernel TS_CCALL tsKernel_setTableFlags(TSKernel self, uint32_t index, TS_BindFlags flags);
TS_CAPI TS_BindFlags TS_CCALL tsKernel_getTableFlags(TSKernel self, uint32_t index);
TS_CAPI void TS_CCALL tsKernel_setGroupSize(TSKernel self, uint32_t width, uint32_t height, uint32_t depth);
TS_CAPI uint32_t TS_CCALL tsKernel_getGroupSizeX(TSKernel self);
TS_CAPI uint32_t TS_CCALL tsKernel_getGroupSizeY(TSKernel self);
TS_CAPI uint32_t TS_CCALL tsKernel_getGroupSizeZ(TSKernel self);

/// Tellusim::D3D12Kernel
TS_CAPI TSD3D12Kernel TS_CCALL tsD3D12Kernel_new(void);
TS_CAPI void TS_CCALL tsD3D12Kernel_delete(TSD3D12Kernel self);
TS_CAPI bool_t TS_CCALL tsD3D12Kernel_equalPtr(const TSD3D12Kernel self, const TSD3D12Kernel ptr);
TS_CAPI TSD3D12Kernel TS_CCALL tsD3D12Kernel_copyPtr(const TSD3D12Kernel self);
TS_CAPI TSD3D12Kernel TS_CCALL tsD3D12Kernel_clonePtr(const TSD3D12Kernel self);
TS_CAPI void TS_CCALL tsD3D12Kernel_clearPtr(TSD3D12Kernel self);
TS_CAPI void TS_CCALL tsD3D12Kernel_destroyPtr(TSD3D12Kernel self);
TS_CAPI void TS_CCALL tsD3D12Kernel_acquirePtr(TSD3D12Kernel self);
TS_CAPI void TS_CCALL tsD3D12Kernel_unacquirePtr(TSD3D12Kernel self);
TS_CAPI bool_t TS_CCALL tsD3D12Kernel_isValidPtr(const TSD3D12Kernel self);
TS_CAPI bool_t TS_CCALL tsD3D12Kernel_isOwnerPtr(const TSD3D12Kernel self);
TS_CAPI bool_t TS_CCALL tsD3D12Kernel_isConstPtr(const TSD3D12Kernel self);
TS_CAPI uint32_t TS_CCALL tsD3D12Kernel_getCountPtr(const TSD3D12Kernel self);
TS_CAPI const void* TS_CCALL tsD3D12Kernel_getInternalPtr(const TSD3D12Kernel self);
TS_CAPI bool_t TS_CCALL tsD3D12Kernel_equalKernelPtr(const TSD3D12Kernel self, const TSKernel base);
TS_CAPI TSD3D12Kernel TS_CCALL tsD3D12Kernel_castKernelPtr(TSKernel base);
TS_CAPI TSKernel TS_CCALL tsD3D12Kernel_baseKernelPtr(TSD3D12Kernel self);
TS_CAPI ID3D12RootSignature* TS_CCALL tsD3D12Kernel_getRootSignature(TSD3D12Kernel self);

/// Tellusim::MTLKernel
TS_CAPI TSMTLKernel TS_CCALL tsMTLKernel_new(void);
TS_CAPI void TS_CCALL tsMTLKernel_delete(TSMTLKernel self);
TS_CAPI bool_t TS_CCALL tsMTLKernel_equalPtr(const TSMTLKernel self, const TSMTLKernel ptr);
TS_CAPI TSMTLKernel TS_CCALL tsMTLKernel_copyPtr(const TSMTLKernel self);
TS_CAPI TSMTLKernel TS_CCALL tsMTLKernel_clonePtr(const TSMTLKernel self);
TS_CAPI void TS_CCALL tsMTLKernel_clearPtr(TSMTLKernel self);
TS_CAPI void TS_CCALL tsMTLKernel_destroyPtr(TSMTLKernel self);
TS_CAPI void TS_CCALL tsMTLKernel_acquirePtr(TSMTLKernel self);
TS_CAPI void TS_CCALL tsMTLKernel_unacquirePtr(TSMTLKernel self);
TS_CAPI bool_t TS_CCALL tsMTLKernel_isValidPtr(const TSMTLKernel self);
TS_CAPI bool_t TS_CCALL tsMTLKernel_isOwnerPtr(const TSMTLKernel self);
TS_CAPI bool_t TS_CCALL tsMTLKernel_isConstPtr(const TSMTLKernel self);
TS_CAPI uint32_t TS_CCALL tsMTLKernel_getCountPtr(const TSMTLKernel self);
TS_CAPI const void* TS_CCALL tsMTLKernel_getInternalPtr(const TSMTLKernel self);
TS_CAPI bool_t TS_CCALL tsMTLKernel_equalKernelPtr(const TSMTLKernel self, const TSKernel base);
TS_CAPI TSMTLKernel TS_CCALL tsMTLKernel_castKernelPtr(TSKernel base);
TS_CAPI TSKernel TS_CCALL tsMTLKernel_baseKernelPtr(TSMTLKernel self);
TS_CAPI void TS_CCALL tsMTLKernel_setIndirect(TSMTLKernel self, bool_t enabled);
TS_CAPI bool_t TS_CCALL tsMTLKernel_isIndirect(TSMTLKernel self);
TS_CAPI void* TS_CCALL tsMTLKernel_getComputeFunction(TSMTLKernel self);

/// Tellusim::FUKernel
TS_CAPI TSFUKernel TS_CCALL tsFUKernel_new(void);
TS_CAPI TSFUKernel TS_CCALL tsFUKernel_new_cAKb(const TSKernel *kernels, uint32_t kernels_size, bool_t owner);
TS_CAPI void TS_CCALL tsFUKernel_delete(TSFUKernel self);
TS_CAPI bool_t TS_CCALL tsFUKernel_equalPtr(const TSFUKernel self, const TSFUKernel ptr);
TS_CAPI TSFUKernel TS_CCALL tsFUKernel_copyPtr(const TSFUKernel self);
TS_CAPI TSFUKernel TS_CCALL tsFUKernel_clonePtr(const TSFUKernel self);
TS_CAPI void TS_CCALL tsFUKernel_clearPtr(TSFUKernel self);
TS_CAPI void TS_CCALL tsFUKernel_destroyPtr(TSFUKernel self);
TS_CAPI void TS_CCALL tsFUKernel_acquirePtr(TSFUKernel self);
TS_CAPI void TS_CCALL tsFUKernel_unacquirePtr(TSFUKernel self);
TS_CAPI bool_t TS_CCALL tsFUKernel_isValidPtr(const TSFUKernel self);
TS_CAPI bool_t TS_CCALL tsFUKernel_isOwnerPtr(const TSFUKernel self);
TS_CAPI bool_t TS_CCALL tsFUKernel_isConstPtr(const TSFUKernel self);
TS_CAPI uint32_t TS_CCALL tsFUKernel_getCountPtr(const TSFUKernel self);
TS_CAPI const void* TS_CCALL tsFUKernel_getInternalPtr(const TSFUKernel self);
TS_CAPI bool_t TS_CCALL tsFUKernel_equalKernelPtr(const TSFUKernel self, const TSKernel base);
TS_CAPI TSFUKernel TS_CCALL tsFUKernel_castKernelPtr(TSKernel base);
TS_CAPI TSKernel TS_CCALL tsFUKernel_baseKernelPtr(TSFUKernel self);
TS_CAPI void TS_CCALL tsFUKernel_setMask(TSFUKernel self, uint32_t mask);
TS_CAPI uint32_t TS_CCALL tsFUKernel_getMask(TSFUKernel self);
TS_CAPI uint32_t TS_CCALL tsFUKernel_getNumKernels(TSFUKernel self);
TS_CAPI TSKernel TS_CCALL tsFUKernel_getKernel_cu(TSFUKernel self, uint32_t index);
TS_CAPI TSKernel TS_CCALL tsFUKernel_getKernel_u(TSFUKernel self, uint32_t index);

/// Tellusim::Pipeline
TS_CAPI TSPipeline TS_CCALL tsPipeline_new(void);
TS_CAPI void TS_CCALL tsPipeline_delete(TSPipeline self);
TS_CAPI bool_t TS_CCALL tsPipeline_equalPtr(const TSPipeline self, const TSPipeline ptr);
TS_CAPI TSPipeline TS_CCALL tsPipeline_copyPtr(const TSPipeline self);
TS_CAPI TSPipeline TS_CCALL tsPipeline_clonePtr(const TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_clearPtr(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_destroyPtr(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_acquirePtr(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_unacquirePtr(TSPipeline self);
TS_CAPI bool_t TS_CCALL tsPipeline_isValidPtr(const TSPipeline self);
TS_CAPI bool_t TS_CCALL tsPipeline_isOwnerPtr(const TSPipeline self);
TS_CAPI bool_t TS_CCALL tsPipeline_isConstPtr(const TSPipeline self);
TS_CAPI uint32_t TS_CCALL tsPipeline_getCountPtr(const TSPipeline self);
TS_CAPI const void* TS_CCALL tsPipeline_getInternalPtr(const TSPipeline self);
TS_CAPI TS_Platform TS_CCALL tsPipeline_getPlatform(TSPipeline self);
TS_CAPI const char* TS_CCALL tsPipeline_getPlatformName(TSPipeline self);
TS_CAPI uint32_t TS_CCALL tsPipeline_getIndex(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_clear(TSPipeline self);
TS_CAPI bool_t TS_CCALL tsPipeline_isCreated(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_setName(TSPipeline self, const char *name);
TS_CAPI TSString TS_CCALL tsPipeline_getName(TSPipeline self);
TS_CAPI bool_t TS_CCALL tsPipeline_create(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_setParameters(TSPipeline self, const TSPipeline pipeline);
TS_CAPI bool_t TS_CCALL tsPipeline_saveState(TSPipeline self, TSStream stream);
TS_CAPI void TS_CCALL tsPipeline_addShader(TSPipeline self, TSShader shader, bool_t owner);
TS_CAPI TSShader TS_CCALL tsPipeline_getVertexShader(TSPipeline self);
TS_CAPI TSShader TS_CCALL tsPipeline_getControlShader(TSPipeline self);
TS_CAPI TSShader TS_CCALL tsPipeline_getEvaluateShader(TSPipeline self);
TS_CAPI TSShader TS_CCALL tsPipeline_getGeometryShader(TSPipeline self);
TS_CAPI TSShader TS_CCALL tsPipeline_getFragmentShader(TSPipeline self);
TS_CAPI TSShader TS_CCALL tsPipeline_getTaskShader(TSPipeline self);
TS_CAPI TSShader TS_CCALL tsPipeline_getMeshShader(TSPipeline self);
TS_CAPI bool_t TS_CCALL tsPipeline_loadShader_STss(TSPipeline self, TS_ShaderType type, const char *name, const char *format);
TS_CAPI bool_t TS_CCALL tsPipeline_loadShaderGLSL_STss(TSPipeline self, TS_ShaderType type, const char *name, const char *format);
TS_CAPI bool_t TS_CCALL tsPipeline_loadShader_STscSspu(TSPipeline self, TS_ShaderType type, const char *name, const TSString macros, const char **includes, uint32_t size);
TS_CAPI bool_t TS_CCALL tsPipeline_loadShaderGLSL_STscSspu(TSPipeline self, TS_ShaderType type, const char *name, const TSString macros, const char **includes, uint32_t size);
TS_CAPI bool_t TS_CCALL tsPipeline_loadShaderSPIRV(TSPipeline self, TS_ShaderType type, const char *name);
TS_CAPI bool_t TS_CCALL tsPipeline_createShader_STss(TSPipeline self, TS_ShaderType type, const char *src, const char *format);
TS_CAPI bool_t TS_CCALL tsPipeline_createShaderGLSL_STss(TSPipeline self, TS_ShaderType type, const char *src, const char *format);
TS_CAPI bool_t TS_CCALL tsPipeline_createShader_STscSspu(TSPipeline self, TS_ShaderType type, const char *src, const TSString macros, const char **includes, uint32_t size);
TS_CAPI bool_t TS_CCALL tsPipeline_createShaderGLSL_STscSspu(TSPipeline self, TS_ShaderType type, const char *src, const TSString macros, const char **includes, uint32_t size);
TS_CAPI bool_t TS_CCALL tsPipeline_createShaderSPIRV(TSPipeline self, TS_ShaderType type, const uint32_t *data, uint32_t data_size);
TS_CAPI uint32_t TS_CCALL tsPipeline_addSampler(TSPipeline self, TS_ShaderMask mask);
TS_CAPI uint32_t TS_CCALL tsPipeline_getNumSamplers(TSPipeline self);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setSamplerOffset(TSPipeline self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsPipeline_getSamplerOffset(TSPipeline self);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setSamplerMask(TSPipeline self, uint32_t index, TS_ShaderMask mask);
TS_CAPI TS_ShaderMask TS_CCALL tsPipeline_getSamplerMask(TSPipeline self, uint32_t index);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setSamplerMasks(TSPipeline self, uint32_t index, uint32_t num, TS_ShaderMask mask, bool_t array);
TS_CAPI TS_ShaderMask TS_CCALL tsPipeline_getSamplerMasks(TSPipeline self, uint32_t index, uint32_t num);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setSamplerArray(TSPipeline self, uint32_t index, uint32_t num, bool_t array);
TS_CAPI uint32_t TS_CCALL tsPipeline_getSamplerArray(TSPipeline self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsPipeline_addTexture(TSPipeline self, TS_ShaderMask mask);
TS_CAPI uint32_t TS_CCALL tsPipeline_getNumTextures(TSPipeline self);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setTextureOffset(TSPipeline self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsPipeline_getTextureOffset(TSPipeline self);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setTextureMask(TSPipeline self, uint32_t index, TS_ShaderMask mask);
TS_CAPI TS_ShaderMask TS_CCALL tsPipeline_getTextureMask(TSPipeline self, uint32_t index);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setTextureMasks(TSPipeline self, uint32_t index, uint32_t num, TS_ShaderMask mask, bool_t array);
TS_CAPI TS_ShaderMask TS_CCALL tsPipeline_getTextureMasks(TSPipeline self, uint32_t index, uint32_t num);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setTextureArray(TSPipeline self, uint32_t index, uint32_t num, bool_t array);
TS_CAPI uint32_t TS_CCALL tsPipeline_getTextureArray(TSPipeline self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsPipeline_addSurface(TSPipeline self, TS_ShaderMask mask);
TS_CAPI uint32_t TS_CCALL tsPipeline_getNumSurfaces(TSPipeline self);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setSurfaceOffset(TSPipeline self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsPipeline_getSurfaceOffset(TSPipeline self);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setSurfaceMask(TSPipeline self, uint32_t index, TS_ShaderMask mask);
TS_CAPI TS_ShaderMask TS_CCALL tsPipeline_getSurfaceMask(TSPipeline self, uint32_t index);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setSurfaceMasks(TSPipeline self, uint32_t index, uint32_t num, TS_ShaderMask mask, bool_t array);
TS_CAPI TS_ShaderMask TS_CCALL tsPipeline_getSurfaceMasks(TSPipeline self, uint32_t index, uint32_t num);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setSurfaceArray(TSPipeline self, uint32_t index, uint32_t num, bool_t array);
TS_CAPI uint32_t TS_CCALL tsPipeline_getSurfaceArray(TSPipeline self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsPipeline_addUniform(TSPipeline self, TS_ShaderMask mask, TS_BindFlags flags);
TS_CAPI uint32_t TS_CCALL tsPipeline_getNumUniforms(TSPipeline self);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setUniformOffset(TSPipeline self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsPipeline_getUniformOffset(TSPipeline self);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setUniformMask(TSPipeline self, uint32_t index, TS_ShaderMask mask, TS_BindFlags flags);
TS_CAPI TS_ShaderMask TS_CCALL tsPipeline_getUniformMask(TSPipeline self, uint32_t index);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setUniformMasks(TSPipeline self, uint32_t index, uint32_t num, TS_ShaderMask mask, TS_BindFlags flags);
TS_CAPI TS_ShaderMask TS_CCALL tsPipeline_getUniformMasks(TSPipeline self, uint32_t index, uint32_t num);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setUniformFlags(TSPipeline self, uint32_t index, TS_BindFlags flags);
TS_CAPI TS_BindFlags TS_CCALL tsPipeline_getUniformFlags(TSPipeline self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsPipeline_addStorage(TSPipeline self, TS_ShaderMask mask, TS_BindFlags flags);
TS_CAPI uint32_t TS_CCALL tsPipeline_getNumStorages(TSPipeline self);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setStorageOffset(TSPipeline self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsPipeline_getStorageOffset(TSPipeline self);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setStorageMask(TSPipeline self, uint32_t index, TS_ShaderMask mask, TS_BindFlags flags);
TS_CAPI TS_ShaderMask TS_CCALL tsPipeline_getStorageMask(TSPipeline self, uint32_t index);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setStorageMasks(TSPipeline self, uint32_t index, uint32_t num, TS_ShaderMask mask, TS_BindFlags flags);
TS_CAPI TS_ShaderMask TS_CCALL tsPipeline_getStorageMasks(TSPipeline self, uint32_t index, uint32_t num);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setStorageFlags(TSPipeline self, uint32_t index, TS_BindFlags flags);
TS_CAPI TS_BindFlags TS_CCALL tsPipeline_getStorageFlags(TSPipeline self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsPipeline_addTracing(TSPipeline self, TS_ShaderMask mask);
TS_CAPI uint32_t TS_CCALL tsPipeline_getNumTracings(TSPipeline self);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setTracingOffset(TSPipeline self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsPipeline_getTracingOffset(TSPipeline self);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setTracingMask(TSPipeline self, uint32_t index, TS_ShaderMask mask);
TS_CAPI TS_ShaderMask TS_CCALL tsPipeline_getTracingMask(TSPipeline self, uint32_t index);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setTracingMasks(TSPipeline self, uint32_t index, uint32_t num, TS_ShaderMask mask);
TS_CAPI TS_ShaderMask TS_CCALL tsPipeline_getTracingMasks(TSPipeline self, uint32_t index, uint32_t num);
TS_CAPI uint32_t TS_CCALL tsPipeline_addTexel(TSPipeline self, TS_ShaderMask mask);
TS_CAPI uint32_t TS_CCALL tsPipeline_getNumTexels(TSPipeline self);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setTexelOffset(TSPipeline self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsPipeline_getTexelOffset(TSPipeline self);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setTexelMask(TSPipeline self, uint32_t index, TS_ShaderMask mask);
TS_CAPI TS_ShaderMask TS_CCALL tsPipeline_getTexelMask(TSPipeline self, uint32_t index);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setTexelMasks(TSPipeline self, uint32_t index, uint32_t num, TS_ShaderMask mask);
TS_CAPI TS_ShaderMask TS_CCALL tsPipeline_getTexelMasks(TSPipeline self, uint32_t index, uint32_t num);
TS_CAPI uint32_t TS_CCALL tsPipeline_addTable(TSPipeline self, TS_TableType type, uint32_t size, TS_ShaderMask mask, TS_BindFlags flags);
TS_CAPI uint32_t TS_CCALL tsPipeline_getNumTables(TSPipeline self);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setTableOffset(TSPipeline self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsPipeline_getTableOffset(TSPipeline self);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setTableType(TSPipeline self, uint32_t index, TS_TableType type, uint32_t size, TS_ShaderMask mask, TS_BindFlags flags);
TS_CAPI TS_TableType TS_CCALL tsPipeline_getTableType(TSPipeline self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsPipeline_getTableSize(TSPipeline self, uint32_t index);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setTableMask(TSPipeline self, uint32_t index, TS_ShaderMask mask, TS_BindFlags flags);
TS_CAPI TS_ShaderMask TS_CCALL tsPipeline_getTableMask(TSPipeline self, uint32_t index);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setTableFlags(TSPipeline self, uint32_t index, TS_BindFlags flags);
TS_CAPI TS_BindFlags TS_CCALL tsPipeline_getTableFlags(TSPipeline self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsPipeline_getNumVertices(TSPipeline self);
TS_CAPI uint32_t TS_CCALL tsPipeline_getVertexStride(TSPipeline self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsPipeline_getVertexRate(TSPipeline self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsPipeline_addAttribute(TSPipeline self, TS_PipelineAttribute attribute, TS_Format format, uint32_t vertex, size_t offset, size_t stride, uint32_t rate);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setAttribute(TSPipeline self, uint32_t index, TS_PipelineAttribute attribute, TS_Format format, uint32_t vertex, size_t offset, size_t stride, uint32_t rate);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setAttributeType(TSPipeline self, uint32_t index, TS_PipelineAttribute attribute);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setAttributeFormat(TSPipeline self, uint32_t index, TS_Format format);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setAttributeVertex(TSPipeline self, uint32_t index, uint32_t vertex);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setAttributeOffset(TSPipeline self, uint32_t index, size_t offset);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setAttributeStride(TSPipeline self, uint32_t index, size_t stride);
TS_CAPI TSPipeline TS_CCALL tsPipeline_setAttributeRate(TSPipeline self, uint32_t index, uint32_t rate);
TS_CAPI uint32_t TS_CCALL tsPipeline_getNumAttributes(TSPipeline self);
TS_CAPI TS_PipelineAttribute TS_CCALL tsPipeline_getAttributeType(TSPipeline self, uint32_t index);
TS_CAPI TS_Format TS_CCALL tsPipeline_getAttributeFormat(TSPipeline self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsPipeline_getAttributeVertex(TSPipeline self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsPipeline_getAttributeOffset(TSPipeline self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsPipeline_getAttributeStride(TSPipeline self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsPipeline_getAttributeRate(TSPipeline self, uint32_t index);
TS_CAPI void TS_CCALL tsPipeline_setPrimitive(TSPipeline self, TS_PipelinePrimitive primitive);
TS_CAPI TS_PipelinePrimitive TS_CCALL tsPipeline_getPrimitive(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_setFillMode(TSPipeline self, TS_PipelineFillMode mode);
TS_CAPI TS_PipelineFillMode TS_CCALL tsPipeline_getFillMode(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_setCullMode(TSPipeline self, TS_PipelineCullMode mode);
TS_CAPI TS_PipelineCullMode TS_CCALL tsPipeline_getCullMode(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_setFrontMode(TSPipeline self, TS_PipelineFrontMode mode);
TS_CAPI TS_PipelineFrontMode TS_CCALL tsPipeline_getFrontMode(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_setDepthBias(TSPipeline self, float32_t bias, float32_t slope, float32_t clamp);
TS_CAPI float32_t TS_CCALL tsPipeline_getDepthBias(TSPipeline self);
TS_CAPI float32_t TS_CCALL tsPipeline_getDepthSlope(TSPipeline self);
TS_CAPI float32_t TS_CCALL tsPipeline_getDepthClamp(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_setMultisample(TSPipeline self, uint32_t multisample);
TS_CAPI uint32_t TS_CCALL tsPipeline_getMultisample(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_setSampleMask(TSPipeline self, uint32_t sample_mask);
TS_CAPI uint32_t TS_CCALL tsPipeline_getSampleMask(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_setDepthClip(TSPipeline self, bool_t enabled);
TS_CAPI bool_t TS_CCALL tsPipeline_getDepthClip(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_setDepthReplace(TSPipeline self, bool_t enabled);
TS_CAPI bool_t TS_CCALL tsPipeline_getDepthReplace(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_setScissorTest(TSPipeline self, bool_t enabled);
TS_CAPI bool_t TS_CCALL tsPipeline_getScissorTest(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_setRasterDiscard(TSPipeline self, bool_t enabled);
TS_CAPI bool_t TS_CCALL tsPipeline_getRasterDiscard(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_setSampleShading(TSPipeline self, bool_t enabled);
TS_CAPI bool_t TS_CCALL tsPipeline_getSampleShading(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_setAlphaToCoverage(TSPipeline self, bool_t enabled);
TS_CAPI bool_t TS_CCALL tsPipeline_getAlphaToCoverage(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_setMultisampleRaster(TSPipeline self, bool_t enabled);
TS_CAPI bool_t TS_CCALL tsPipeline_getMultisampleRaster(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_setConservativeRaster(TSPipeline self, bool_t enabled);
TS_CAPI bool_t TS_CCALL tsPipeline_getConservativeRaster(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_setNumViewports(TSPipeline self, uint32_t num_viewports);
TS_CAPI uint32_t TS_CCALL tsPipeline_getNumTargets(TSPipeline self);
TS_CAPI uint32_t TS_CCALL tsPipeline_getNumViewports(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_setNumClipDistances(TSPipeline self, uint32_t num_distances);
TS_CAPI uint32_t TS_CCALL tsPipeline_getNumClipDistances(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_setBlend_PBOPBFPBF(TSPipeline self, TS_PipelineBlendOp op, TS_PipelineBlendFunc src, TS_PipelineBlendFunc dest);
TS_CAPI void TS_CCALL tsPipeline_setBlendColor_PBOPBFPBF(TSPipeline self, TS_PipelineBlendOp op, TS_PipelineBlendFunc src, TS_PipelineBlendFunc dest);
TS_CAPI void TS_CCALL tsPipeline_setBlendAlpha_PBOPBFPBF(TSPipeline self, TS_PipelineBlendOp op, TS_PipelineBlendFunc src, TS_PipelineBlendFunc dest);
TS_CAPI void TS_CCALL tsPipeline_setBlend_uPBOPBFPBF(TSPipeline self, uint32_t index, TS_PipelineBlendOp op, TS_PipelineBlendFunc src, TS_PipelineBlendFunc dest);
TS_CAPI void TS_CCALL tsPipeline_setBlendColor_uPBOPBFPBF(TSPipeline self, uint32_t index, TS_PipelineBlendOp op, TS_PipelineBlendFunc src, TS_PipelineBlendFunc dest);
TS_CAPI void TS_CCALL tsPipeline_setBlendAlpha_uPBOPBFPBF(TSPipeline self, uint32_t index, TS_PipelineBlendOp op, TS_PipelineBlendFunc src, TS_PipelineBlendFunc dest);
TS_CAPI TS_PipelineBlendOp TS_CCALL tsPipeline_getBlendColorOp(TSPipeline self, uint32_t index);
TS_CAPI TS_PipelineBlendOp TS_CCALL tsPipeline_getBlendAlphaOp(TSPipeline self, uint32_t index);
TS_CAPI TS_PipelineBlendFunc TS_CCALL tsPipeline_getBlendSrcColorFunc(TSPipeline self, uint32_t index);
TS_CAPI TS_PipelineBlendFunc TS_CCALL tsPipeline_getBlendSrcAlphaFunc(TSPipeline self, uint32_t index);
TS_CAPI TS_PipelineBlendFunc TS_CCALL tsPipeline_getBlendDestColorFunc(TSPipeline self, uint32_t index);
TS_CAPI TS_PipelineBlendFunc TS_CCALL tsPipeline_getBlendDestAlphaFunc(TSPipeline self, uint32_t index);
TS_CAPI void TS_CCALL tsPipeline_setColorMask_PCM(TSPipeline self, TS_PipelineColorMask mask);
TS_CAPI void TS_CCALL tsPipeline_setColorMask_uPCM(TSPipeline self, uint32_t index, TS_PipelineColorMask mask);
TS_CAPI void TS_CCALL tsPipeline_setColorFormat_uF(TSPipeline self, uint32_t index, TS_Format format);
TS_CAPI void TS_CCALL tsPipeline_setColorFormat_Fu(TSPipeline self, TS_Format format, uint32_t num);
TS_CAPI TS_PipelineColorMask TS_CCALL tsPipeline_getColorMask(TSPipeline self, uint32_t index);
TS_CAPI TS_Format TS_CCALL tsPipeline_getColorFormat(TSPipeline self, uint32_t index);
TS_CAPI void TS_CCALL tsPipeline_setDepthMask(TSPipeline self, TS_PipelineDepthMask mask);
TS_CAPI void TS_CCALL tsPipeline_setDepthFunc(TSPipeline self, TS_PipelineDepthFunc func);
TS_CAPI void TS_CCALL tsPipeline_setDepthFormat(TSPipeline self, TS_Format format);
TS_CAPI TS_PipelineDepthMask TS_CCALL tsPipeline_getDepthMask(TSPipeline self);
TS_CAPI TS_PipelineDepthFunc TS_CCALL tsPipeline_getDepthFunc(TSPipeline self);
TS_CAPI TS_Format TS_CCALL tsPipeline_getDepthFormat(TSPipeline self);
TS_CAPI void TS_CCALL tsPipeline_setStencilMask(TSPipeline self, uint32_t mask);
TS_CAPI void TS_CCALL tsPipeline_setStencilBackMask(TSPipeline self, uint32_t mask);
TS_CAPI void TS_CCALL tsPipeline_setStencilFrontMask(TSPipeline self, uint32_t mask);
TS_CAPI void TS_CCALL tsPipeline_setStencilFunc_PSFPSO(TSPipeline self, TS_PipelineStencilFunc func, TS_PipelineStencilOp dpass_op);
TS_CAPI void TS_CCALL tsPipeline_setStencilBackFunc_PSFPSO(TSPipeline self, TS_PipelineStencilFunc func, TS_PipelineStencilOp dpass_op);
TS_CAPI void TS_CCALL tsPipeline_setStencilFrontFunc_PSFPSO(TSPipeline self, TS_PipelineStencilFunc func, TS_PipelineStencilOp dpass_op);
TS_CAPI void TS_CCALL tsPipeline_setStencilFunc_PSFPSOPSOPSO(TSPipeline self, TS_PipelineStencilFunc func, TS_PipelineStencilOp fail_op, TS_PipelineStencilOp dfail_op, TS_PipelineStencilOp dpass_op);
TS_CAPI void TS_CCALL tsPipeline_setStencilBackFunc_PSFPSOPSOPSO(TSPipeline self, TS_PipelineStencilFunc func, TS_PipelineStencilOp fail_op, TS_PipelineStencilOp dfail_op, TS_PipelineStencilOp dpass_op);
TS_CAPI void TS_CCALL tsPipeline_setStencilFrontFunc_PSFPSOPSOPSO(TSPipeline self, TS_PipelineStencilFunc func, TS_PipelineStencilOp fail_op, TS_PipelineStencilOp dfail_op, TS_PipelineStencilOp dpass_op);
TS_CAPI uint32_t TS_CCALL tsPipeline_getStencilBackMask(TSPipeline self);
TS_CAPI TS_PipelineStencilFunc TS_CCALL tsPipeline_getStencilBackFunc(TSPipeline self);
TS_CAPI TS_PipelineStencilOp TS_CCALL tsPipeline_getStencilBackFailOp(TSPipeline self);
TS_CAPI TS_PipelineStencilOp TS_CCALL tsPipeline_getStencilBackDepthFailOp(TSPipeline self);
TS_CAPI TS_PipelineStencilOp TS_CCALL tsPipeline_getStencilBackDepthPassOp(TSPipeline self);
TS_CAPI uint32_t TS_CCALL tsPipeline_getStencilFrontMask(TSPipeline self);
TS_CAPI TS_PipelineStencilFunc TS_CCALL tsPipeline_getStencilFrontFunc(TSPipeline self);
TS_CAPI TS_PipelineStencilOp TS_CCALL tsPipeline_getStencilFrontFailOp(TSPipeline self);
TS_CAPI TS_PipelineStencilOp TS_CCALL tsPipeline_getStencilFrontDepthFailOp(TSPipeline self);
TS_CAPI TS_PipelineStencilOp TS_CCALL tsPipeline_getStencilFrontDepthPassOp(TSPipeline self);

/// Tellusim::D3D12Pipeline
TS_CAPI TSD3D12Pipeline TS_CCALL tsD3D12Pipeline_new(void);
TS_CAPI void TS_CCALL tsD3D12Pipeline_delete(TSD3D12Pipeline self);
TS_CAPI bool_t TS_CCALL tsD3D12Pipeline_equalPtr(const TSD3D12Pipeline self, const TSD3D12Pipeline ptr);
TS_CAPI TSD3D12Pipeline TS_CCALL tsD3D12Pipeline_copyPtr(const TSD3D12Pipeline self);
TS_CAPI TSD3D12Pipeline TS_CCALL tsD3D12Pipeline_clonePtr(const TSD3D12Pipeline self);
TS_CAPI void TS_CCALL tsD3D12Pipeline_clearPtr(TSD3D12Pipeline self);
TS_CAPI void TS_CCALL tsD3D12Pipeline_destroyPtr(TSD3D12Pipeline self);
TS_CAPI void TS_CCALL tsD3D12Pipeline_acquirePtr(TSD3D12Pipeline self);
TS_CAPI void TS_CCALL tsD3D12Pipeline_unacquirePtr(TSD3D12Pipeline self);
TS_CAPI bool_t TS_CCALL tsD3D12Pipeline_isValidPtr(const TSD3D12Pipeline self);
TS_CAPI bool_t TS_CCALL tsD3D12Pipeline_isOwnerPtr(const TSD3D12Pipeline self);
TS_CAPI bool_t TS_CCALL tsD3D12Pipeline_isConstPtr(const TSD3D12Pipeline self);
TS_CAPI uint32_t TS_CCALL tsD3D12Pipeline_getCountPtr(const TSD3D12Pipeline self);
TS_CAPI const void* TS_CCALL tsD3D12Pipeline_getInternalPtr(const TSD3D12Pipeline self);
TS_CAPI bool_t TS_CCALL tsD3D12Pipeline_equalPipelinePtr(const TSD3D12Pipeline self, const TSPipeline base);
TS_CAPI TSD3D12Pipeline TS_CCALL tsD3D12Pipeline_castPipelinePtr(TSPipeline base);
TS_CAPI TSPipeline TS_CCALL tsD3D12Pipeline_basePipelinePtr(TSD3D12Pipeline self);
TS_CAPI ID3D12RootSignature* TS_CCALL tsD3D12Pipeline_getRootSignature(TSD3D12Pipeline self);

/// Tellusim::MTLPipeline
TS_CAPI TSMTLPipeline TS_CCALL tsMTLPipeline_new(void);
TS_CAPI void TS_CCALL tsMTLPipeline_delete(TSMTLPipeline self);
TS_CAPI bool_t TS_CCALL tsMTLPipeline_equalPtr(const TSMTLPipeline self, const TSMTLPipeline ptr);
TS_CAPI TSMTLPipeline TS_CCALL tsMTLPipeline_copyPtr(const TSMTLPipeline self);
TS_CAPI TSMTLPipeline TS_CCALL tsMTLPipeline_clonePtr(const TSMTLPipeline self);
TS_CAPI void TS_CCALL tsMTLPipeline_clearPtr(TSMTLPipeline self);
TS_CAPI void TS_CCALL tsMTLPipeline_destroyPtr(TSMTLPipeline self);
TS_CAPI void TS_CCALL tsMTLPipeline_acquirePtr(TSMTLPipeline self);
TS_CAPI void TS_CCALL tsMTLPipeline_unacquirePtr(TSMTLPipeline self);
TS_CAPI bool_t TS_CCALL tsMTLPipeline_isValidPtr(const TSMTLPipeline self);
TS_CAPI bool_t TS_CCALL tsMTLPipeline_isOwnerPtr(const TSMTLPipeline self);
TS_CAPI bool_t TS_CCALL tsMTLPipeline_isConstPtr(const TSMTLPipeline self);
TS_CAPI uint32_t TS_CCALL tsMTLPipeline_getCountPtr(const TSMTLPipeline self);
TS_CAPI const void* TS_CCALL tsMTLPipeline_getInternalPtr(const TSMTLPipeline self);
TS_CAPI bool_t TS_CCALL tsMTLPipeline_equalPipelinePtr(const TSMTLPipeline self, const TSPipeline base);
TS_CAPI TSMTLPipeline TS_CCALL tsMTLPipeline_castPipelinePtr(TSPipeline base);
TS_CAPI TSPipeline TS_CCALL tsMTLPipeline_basePipelinePtr(TSMTLPipeline self);
TS_CAPI void TS_CCALL tsMTLPipeline_setIndirect(TSMTLPipeline self, bool_t enabled);
TS_CAPI bool_t TS_CCALL tsMTLPipeline_isIndirect(TSMTLPipeline self);
TS_CAPI void* TS_CCALL tsMTLPipeline_getVertexFunction(TSMTLPipeline self);
TS_CAPI void* TS_CCALL tsMTLPipeline_getFragmentFunction(TSMTLPipeline self);

/// Tellusim::FUPipeline
TS_CAPI TSFUPipeline TS_CCALL tsFUPipeline_new(void);
TS_CAPI TSFUPipeline TS_CCALL tsFUPipeline_new_cAPb(const TSPipeline *pipelines, uint32_t pipelines_size, bool_t owner);
TS_CAPI void TS_CCALL tsFUPipeline_delete(TSFUPipeline self);
TS_CAPI bool_t TS_CCALL tsFUPipeline_equalPtr(const TSFUPipeline self, const TSFUPipeline ptr);
TS_CAPI TSFUPipeline TS_CCALL tsFUPipeline_copyPtr(const TSFUPipeline self);
TS_CAPI TSFUPipeline TS_CCALL tsFUPipeline_clonePtr(const TSFUPipeline self);
TS_CAPI void TS_CCALL tsFUPipeline_clearPtr(TSFUPipeline self);
TS_CAPI void TS_CCALL tsFUPipeline_destroyPtr(TSFUPipeline self);
TS_CAPI void TS_CCALL tsFUPipeline_acquirePtr(TSFUPipeline self);
TS_CAPI void TS_CCALL tsFUPipeline_unacquirePtr(TSFUPipeline self);
TS_CAPI bool_t TS_CCALL tsFUPipeline_isValidPtr(const TSFUPipeline self);
TS_CAPI bool_t TS_CCALL tsFUPipeline_isOwnerPtr(const TSFUPipeline self);
TS_CAPI bool_t TS_CCALL tsFUPipeline_isConstPtr(const TSFUPipeline self);
TS_CAPI uint32_t TS_CCALL tsFUPipeline_getCountPtr(const TSFUPipeline self);
TS_CAPI const void* TS_CCALL tsFUPipeline_getInternalPtr(const TSFUPipeline self);
TS_CAPI bool_t TS_CCALL tsFUPipeline_equalPipelinePtr(const TSFUPipeline self, const TSPipeline base);
TS_CAPI TSFUPipeline TS_CCALL tsFUPipeline_castPipelinePtr(TSPipeline base);
TS_CAPI TSPipeline TS_CCALL tsFUPipeline_basePipelinePtr(TSFUPipeline self);
TS_CAPI void TS_CCALL tsFUPipeline_setMask(TSFUPipeline self, uint32_t mask);
TS_CAPI uint32_t TS_CCALL tsFUPipeline_getMask(TSFUPipeline self);
TS_CAPI uint32_t TS_CCALL tsFUPipeline_getNumPipelines(TSFUPipeline self);
TS_CAPI TSPipeline TS_CCALL tsFUPipeline_getPipeline_cu(TSFUPipeline self, uint32_t index);
TS_CAPI TSPipeline TS_CCALL tsFUPipeline_getPipeline_u(TSFUPipeline self, uint32_t index);

/// Tellusim::Traversal
TS_CAPI TSTraversal TS_CCALL tsTraversal_new(void);
TS_CAPI void TS_CCALL tsTraversal_delete(TSTraversal self);
TS_CAPI bool_t TS_CCALL tsTraversal_equalPtr(const TSTraversal self, const TSTraversal ptr);
TS_CAPI TSTraversal TS_CCALL tsTraversal_copyPtr(const TSTraversal self);
TS_CAPI TSTraversal TS_CCALL tsTraversal_clonePtr(const TSTraversal self);
TS_CAPI void TS_CCALL tsTraversal_clearPtr(TSTraversal self);
TS_CAPI void TS_CCALL tsTraversal_destroyPtr(TSTraversal self);
TS_CAPI void TS_CCALL tsTraversal_acquirePtr(TSTraversal self);
TS_CAPI void TS_CCALL tsTraversal_unacquirePtr(TSTraversal self);
TS_CAPI bool_t TS_CCALL tsTraversal_isValidPtr(const TSTraversal self);
TS_CAPI bool_t TS_CCALL tsTraversal_isOwnerPtr(const TSTraversal self);
TS_CAPI bool_t TS_CCALL tsTraversal_isConstPtr(const TSTraversal self);
TS_CAPI uint32_t TS_CCALL tsTraversal_getCountPtr(const TSTraversal self);
TS_CAPI const void* TS_CCALL tsTraversal_getInternalPtr(const TSTraversal self);
TS_CAPI TS_Platform TS_CCALL tsTraversal_getPlatform(TSTraversal self);
TS_CAPI const char* TS_CCALL tsTraversal_getPlatformName(TSTraversal self);
TS_CAPI uint32_t TS_CCALL tsTraversal_getIndex(TSTraversal self);
TS_CAPI void TS_CCALL tsTraversal_clear(TSTraversal self);
TS_CAPI bool_t TS_CCALL tsTraversal_isCreated(TSTraversal self);
TS_CAPI void TS_CCALL tsTraversal_setName(TSTraversal self, const char *name);
TS_CAPI TSString TS_CCALL tsTraversal_getName(TSTraversal self);
TS_CAPI bool_t TS_CCALL tsTraversal_create(TSTraversal self);
TS_CAPI void TS_CCALL tsTraversal_setParameters(TSTraversal self, const TSTraversal traversal);
TS_CAPI bool_t TS_CCALL tsTraversal_saveState(TSTraversal self, TSStream stream);
TS_CAPI void TS_CCALL tsTraversal_addShader(TSTraversal self, TSShader shader, bool_t owner);
TS_CAPI TSShader TS_CCALL tsTraversal_getRayGenShader(TSTraversal self);
TS_CAPI bool_t TS_CCALL tsTraversal_loadShader_STss(TSTraversal self, TS_ShaderType type, const char *name, const char *format);
TS_CAPI bool_t TS_CCALL tsTraversal_loadShaderGLSL_STss(TSTraversal self, TS_ShaderType type, const char *name, const char *format);
TS_CAPI bool_t TS_CCALL tsTraversal_loadShader_STscSspu(TSTraversal self, TS_ShaderType type, const char *name, const TSString macros, const char **includes, uint32_t size);
TS_CAPI bool_t TS_CCALL tsTraversal_loadShaderGLSL_STscSspu(TSTraversal self, TS_ShaderType type, const char *name, const TSString macros, const char **includes, uint32_t size);
TS_CAPI bool_t TS_CCALL tsTraversal_loadShaderSPIRV(TSTraversal self, TS_ShaderType type, const char *name);
TS_CAPI bool_t TS_CCALL tsTraversal_createShader_STss(TSTraversal self, TS_ShaderType type, const char *src, const char *format);
TS_CAPI bool_t TS_CCALL tsTraversal_createShaderGLSL_STss(TSTraversal self, TS_ShaderType type, const char *src, const char *format);
TS_CAPI bool_t TS_CCALL tsTraversal_createShader_STscSspu(TSTraversal self, TS_ShaderType type, const char *src, const TSString macros, const char **includes, uint32_t size);
TS_CAPI bool_t TS_CCALL tsTraversal_createShaderGLSL_STscSspu(TSTraversal self, TS_ShaderType type, const char *src, const TSString macros, const char **includes, uint32_t size);
TS_CAPI bool_t TS_CCALL tsTraversal_createShaderSPIRV(TSTraversal self, TS_ShaderType type, const uint32_t *data, uint32_t data_size);
TS_CAPI uint32_t TS_CCALL tsTraversal_addSampler(TSTraversal self, TS_ShaderMask mask);
TS_CAPI uint32_t TS_CCALL tsTraversal_getNumSamplers(TSTraversal self);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setSamplerOffset(TSTraversal self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsTraversal_getSamplerOffset(TSTraversal self);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setSamplerMask(TSTraversal self, uint32_t index, TS_ShaderMask mask);
TS_CAPI TS_ShaderMask TS_CCALL tsTraversal_getSamplerMask(TSTraversal self, uint32_t index);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setSamplerMasks(TSTraversal self, uint32_t index, uint32_t num, TS_ShaderMask mask, bool_t array);
TS_CAPI TS_ShaderMask TS_CCALL tsTraversal_getSamplerMasks(TSTraversal self, uint32_t index, uint32_t num);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setSamplerArray(TSTraversal self, uint32_t index, uint32_t num, bool_t array);
TS_CAPI uint32_t TS_CCALL tsTraversal_getSamplerArray(TSTraversal self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsTraversal_addTexture(TSTraversal self, TS_ShaderMask mask);
TS_CAPI uint32_t TS_CCALL tsTraversal_getNumTextures(TSTraversal self);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setTextureOffset(TSTraversal self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsTraversal_getTextureOffset(TSTraversal self);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setTextureMask(TSTraversal self, uint32_t index, TS_ShaderMask mask);
TS_CAPI TS_ShaderMask TS_CCALL tsTraversal_getTextureMask(TSTraversal self, uint32_t index);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setTextureMasks(TSTraversal self, uint32_t index, uint32_t num, TS_ShaderMask mask, bool_t array);
TS_CAPI TS_ShaderMask TS_CCALL tsTraversal_getTextureMasks(TSTraversal self, uint32_t index, uint32_t num);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setTextureArray(TSTraversal self, uint32_t index, uint32_t num, bool_t array);
TS_CAPI uint32_t TS_CCALL tsTraversal_getTextureArray(TSTraversal self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsTraversal_addSurface(TSTraversal self, TS_ShaderMask mask);
TS_CAPI uint32_t TS_CCALL tsTraversal_getNumSurfaces(TSTraversal self);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setSurfaceOffset(TSTraversal self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsTraversal_getSurfaceOffset(TSTraversal self);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setSurfaceMask(TSTraversal self, uint32_t index, TS_ShaderMask mask);
TS_CAPI TS_ShaderMask TS_CCALL tsTraversal_getSurfaceMask(TSTraversal self, uint32_t index);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setSurfaceMasks(TSTraversal self, uint32_t index, uint32_t num, TS_ShaderMask mask, bool_t array);
TS_CAPI TS_ShaderMask TS_CCALL tsTraversal_getSurfaceMasks(TSTraversal self, uint32_t index, uint32_t num);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setSurfaceArray(TSTraversal self, uint32_t index, uint32_t num, bool_t array);
TS_CAPI uint32_t TS_CCALL tsTraversal_getSurfaceArray(TSTraversal self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsTraversal_addUniform(TSTraversal self, TS_ShaderMask mask, TS_BindFlags flags);
TS_CAPI uint32_t TS_CCALL tsTraversal_getNumUniforms(TSTraversal self);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setUniformOffset(TSTraversal self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsTraversal_getUniformOffset(TSTraversal self);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setUniformMask(TSTraversal self, uint32_t index, TS_ShaderMask mask, TS_BindFlags flags);
TS_CAPI TS_ShaderMask TS_CCALL tsTraversal_getUniformMask(TSTraversal self, uint32_t index);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setUniformMasks(TSTraversal self, uint32_t index, uint32_t num, TS_ShaderMask mask, TS_BindFlags flags);
TS_CAPI TS_ShaderMask TS_CCALL tsTraversal_getUniformMasks(TSTraversal self, uint32_t index, uint32_t num);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setUniformFlags(TSTraversal self, uint32_t index, TS_BindFlags flags);
TS_CAPI TS_BindFlags TS_CCALL tsTraversal_getUniformFlags(TSTraversal self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsTraversal_addStorage(TSTraversal self, TS_ShaderMask mask, TS_BindFlags flags);
TS_CAPI uint32_t TS_CCALL tsTraversal_getNumStorages(TSTraversal self);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setStorageOffset(TSTraversal self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsTraversal_getStorageOffset(TSTraversal self);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setStorageMask(TSTraversal self, uint32_t index, TS_ShaderMask mask, TS_BindFlags flags);
TS_CAPI TS_ShaderMask TS_CCALL tsTraversal_getStorageMask(TSTraversal self, uint32_t index);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setStorageMasks(TSTraversal self, uint32_t index, uint32_t num, TS_ShaderMask mask, TS_BindFlags flags);
TS_CAPI TS_ShaderMask TS_CCALL tsTraversal_getStorageMasks(TSTraversal self, uint32_t index, uint32_t num);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setStorageFlags(TSTraversal self, uint32_t index, TS_BindFlags flags);
TS_CAPI TS_BindFlags TS_CCALL tsTraversal_getStorageFlags(TSTraversal self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsTraversal_addTracing(TSTraversal self, TS_ShaderMask mask);
TS_CAPI uint32_t TS_CCALL tsTraversal_getNumTracings(TSTraversal self);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setTracingOffset(TSTraversal self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsTraversal_getTracingOffset(TSTraversal self);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setTracingMask(TSTraversal self, uint32_t index, TS_ShaderMask mask);
TS_CAPI TS_ShaderMask TS_CCALL tsTraversal_getTracingMask(TSTraversal self, uint32_t index);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setTracingMasks(TSTraversal self, uint32_t index, uint32_t num, TS_ShaderMask mask);
TS_CAPI TS_ShaderMask TS_CCALL tsTraversal_getTracingMasks(TSTraversal self, uint32_t index, uint32_t num);
TS_CAPI uint32_t TS_CCALL tsTraversal_addTexel(TSTraversal self, TS_ShaderMask mask);
TS_CAPI uint32_t TS_CCALL tsTraversal_getNumTexels(TSTraversal self);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setTexelOffset(TSTraversal self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsTraversal_getTexelOffset(TSTraversal self);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setTexelMask(TSTraversal self, uint32_t index, TS_ShaderMask mask);
TS_CAPI TS_ShaderMask TS_CCALL tsTraversal_getTexelMask(TSTraversal self, uint32_t index);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setTexelMasks(TSTraversal self, uint32_t index, uint32_t num, TS_ShaderMask mask);
TS_CAPI TS_ShaderMask TS_CCALL tsTraversal_getTexelMasks(TSTraversal self, uint32_t index, uint32_t num);
TS_CAPI uint32_t TS_CCALL tsTraversal_addTable(TSTraversal self, TS_TableType type, uint32_t size, TS_ShaderMask mask, TS_BindFlags flags);
TS_CAPI uint32_t TS_CCALL tsTraversal_getNumTables(TSTraversal self);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setTableOffset(TSTraversal self, uint32_t offset);
TS_CAPI uint32_t TS_CCALL tsTraversal_getTableOffset(TSTraversal self);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setTableType(TSTraversal self, uint32_t index, TS_TableType type, uint32_t size, TS_ShaderMask mask, TS_BindFlags flags);
TS_CAPI TS_TableType TS_CCALL tsTraversal_getTableType(TSTraversal self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsTraversal_getTableSize(TSTraversal self, uint32_t index);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setTableMask(TSTraversal self, uint32_t index, TS_ShaderMask mask, TS_BindFlags flags);
TS_CAPI TS_ShaderMask TS_CCALL tsTraversal_getTableMask(TSTraversal self, uint32_t index);
TS_CAPI TSTraversal TS_CCALL tsTraversal_setTableFlags(TSTraversal self, uint32_t index, TS_BindFlags flags);
TS_CAPI TS_BindFlags TS_CCALL tsTraversal_getTableFlags(TSTraversal self, uint32_t index);
TS_CAPI void TS_CCALL tsTraversal_setRecursionDepth(TSTraversal self, uint32_t depth);
TS_CAPI uint32_t TS_CCALL tsTraversal_getRecursionDepth(TSTraversal self);

/// Tellusim::D3D12Traversal
TS_CAPI TSD3D12Traversal TS_CCALL tsD3D12Traversal_new(void);
TS_CAPI void TS_CCALL tsD3D12Traversal_delete(TSD3D12Traversal self);
TS_CAPI bool_t TS_CCALL tsD3D12Traversal_equalPtr(const TSD3D12Traversal self, const TSD3D12Traversal ptr);
TS_CAPI TSD3D12Traversal TS_CCALL tsD3D12Traversal_copyPtr(const TSD3D12Traversal self);
TS_CAPI TSD3D12Traversal TS_CCALL tsD3D12Traversal_clonePtr(const TSD3D12Traversal self);
TS_CAPI void TS_CCALL tsD3D12Traversal_clearPtr(TSD3D12Traversal self);
TS_CAPI void TS_CCALL tsD3D12Traversal_destroyPtr(TSD3D12Traversal self);
TS_CAPI void TS_CCALL tsD3D12Traversal_acquirePtr(TSD3D12Traversal self);
TS_CAPI void TS_CCALL tsD3D12Traversal_unacquirePtr(TSD3D12Traversal self);
TS_CAPI bool_t TS_CCALL tsD3D12Traversal_isValidPtr(const TSD3D12Traversal self);
TS_CAPI bool_t TS_CCALL tsD3D12Traversal_isOwnerPtr(const TSD3D12Traversal self);
TS_CAPI bool_t TS_CCALL tsD3D12Traversal_isConstPtr(const TSD3D12Traversal self);
TS_CAPI uint32_t TS_CCALL tsD3D12Traversal_getCountPtr(const TSD3D12Traversal self);
TS_CAPI const void* TS_CCALL tsD3D12Traversal_getInternalPtr(const TSD3D12Traversal self);
TS_CAPI bool_t TS_CCALL tsD3D12Traversal_equalTraversalPtr(const TSD3D12Traversal self, const TSTraversal base);
TS_CAPI TSD3D12Traversal TS_CCALL tsD3D12Traversal_castTraversalPtr(TSTraversal base);
TS_CAPI TSTraversal TS_CCALL tsD3D12Traversal_baseTraversalPtr(TSD3D12Traversal self);
TS_CAPI ID3D12RootSignature* TS_CCALL tsD3D12Traversal_getRootSignature(TSD3D12Traversal self);

/// Tellusim::FUTraversal
TS_CAPI TSFUTraversal TS_CCALL tsFUTraversal_new(void);
TS_CAPI TSFUTraversal TS_CCALL tsFUTraversal_new_cATb(const TSTraversal *traversals, uint32_t traversals_size, bool_t owner);
TS_CAPI void TS_CCALL tsFUTraversal_delete(TSFUTraversal self);
TS_CAPI bool_t TS_CCALL tsFUTraversal_equalPtr(const TSFUTraversal self, const TSFUTraversal ptr);
TS_CAPI TSFUTraversal TS_CCALL tsFUTraversal_copyPtr(const TSFUTraversal self);
TS_CAPI TSFUTraversal TS_CCALL tsFUTraversal_clonePtr(const TSFUTraversal self);
TS_CAPI void TS_CCALL tsFUTraversal_clearPtr(TSFUTraversal self);
TS_CAPI void TS_CCALL tsFUTraversal_destroyPtr(TSFUTraversal self);
TS_CAPI void TS_CCALL tsFUTraversal_acquirePtr(TSFUTraversal self);
TS_CAPI void TS_CCALL tsFUTraversal_unacquirePtr(TSFUTraversal self);
TS_CAPI bool_t TS_CCALL tsFUTraversal_isValidPtr(const TSFUTraversal self);
TS_CAPI bool_t TS_CCALL tsFUTraversal_isOwnerPtr(const TSFUTraversal self);
TS_CAPI bool_t TS_CCALL tsFUTraversal_isConstPtr(const TSFUTraversal self);
TS_CAPI uint32_t TS_CCALL tsFUTraversal_getCountPtr(const TSFUTraversal self);
TS_CAPI const void* TS_CCALL tsFUTraversal_getInternalPtr(const TSFUTraversal self);
TS_CAPI bool_t TS_CCALL tsFUTraversal_equalTraversalPtr(const TSFUTraversal self, const TSTraversal base);
TS_CAPI TSFUTraversal TS_CCALL tsFUTraversal_castTraversalPtr(TSTraversal base);
TS_CAPI TSTraversal TS_CCALL tsFUTraversal_baseTraversalPtr(TSFUTraversal self);
TS_CAPI void TS_CCALL tsFUTraversal_setMask(TSFUTraversal self, uint32_t mask);
TS_CAPI uint32_t TS_CCALL tsFUTraversal_getMask(TSFUTraversal self);
TS_CAPI uint32_t TS_CCALL tsFUTraversal_getNumTraversals(TSFUTraversal self);
TS_CAPI TSTraversal TS_CCALL tsFUTraversal_getTraversal_cu(TSFUTraversal self, uint32_t index);
TS_CAPI TSTraversal TS_CCALL tsFUTraversal_getTraversal_u(TSFUTraversal self, uint32_t index);

/// Tellusim::Surface
TS_CAPI TSSurface TS_CCALL tsSurface_new(void);
TS_CAPI TSSurface TS_CCALL tsSurface_new_C(TSContext context);
TS_CAPI TSSurface TS_CCALL tsSurface_new_P(TS_Platform platform);
TS_CAPI void TS_CCALL tsSurface_delete(TSSurface self);
TS_CAPI bool_t TS_CCALL tsSurface_equalPtr(const TSSurface self, const TSSurface ptr);
TS_CAPI TSSurface TS_CCALL tsSurface_copyPtr(const TSSurface self);
TS_CAPI TSSurface TS_CCALL tsSurface_clonePtr(const TSSurface self);
TS_CAPI void TS_CCALL tsSurface_clearPtr(TSSurface self);
TS_CAPI void TS_CCALL tsSurface_destroyPtr(TSSurface self);
TS_CAPI void TS_CCALL tsSurface_acquirePtr(TSSurface self);
TS_CAPI void TS_CCALL tsSurface_unacquirePtr(TSSurface self);
TS_CAPI bool_t TS_CCALL tsSurface_isValidPtr(const TSSurface self);
TS_CAPI bool_t TS_CCALL tsSurface_isOwnerPtr(const TSSurface self);
TS_CAPI bool_t TS_CCALL tsSurface_isConstPtr(const TSSurface self);
TS_CAPI uint32_t TS_CCALL tsSurface_getCountPtr(const TSSurface self);
TS_CAPI const void* TS_CCALL tsSurface_getInternalPtr(const TSSurface self);
TS_CAPI TS_Platform TS_CCALL tsSurface_getPlatform(TSSurface self);
TS_CAPI const char* TS_CCALL tsSurface_getPlatformName(TSSurface self);
TS_CAPI uint32_t TS_CCALL tsSurface_getIndex(TSSurface self);
TS_CAPI void TS_CCALL tsSurface_setSize(TSSurface self, uint32_t width, uint32_t height);
TS_CAPI uint32_t TS_CCALL tsSurface_getWidth(TSSurface self);
TS_CAPI uint32_t TS_CCALL tsSurface_getHeight(TSSurface self);
TS_CAPI void TS_CCALL tsSurface_setMultisample(TSSurface self, uint32_t multisample);
TS_CAPI uint32_t TS_CCALL tsSurface_getMultisample(TSSurface self);
TS_CAPI bool_t TS_CCALL tsSurface_hasMultisample(TSSurface self);
TS_CAPI void TS_CCALL tsSurface_setColorLayer(TSSurface self, uint32_t layer, uint32_t layers);
TS_CAPI void TS_CCALL tsSurface_setDepthLayer(TSSurface self, uint32_t layer, uint32_t layers);
TS_CAPI uint32_t TS_CCALL tsSurface_getColorLayer(TSSurface self);
TS_CAPI uint32_t TS_CCALL tsSurface_getDepthLayer(TSSurface self);
TS_CAPI uint32_t TS_CCALL tsSurface_getColorLayers(TSSurface self);
TS_CAPI uint32_t TS_CCALL tsSurface_getDepthLayers(TSSurface self);
TS_CAPI bool_t TS_CCALL tsSurface_hasColorLayers(TSSurface self);
TS_CAPI bool_t TS_CCALL tsSurface_hasDepthLayers(TSSurface self);
TS_CAPI void TS_CCALL tsSurface_setColorFormat(TSSurface self, TS_Format format);
TS_CAPI void TS_CCALL tsSurface_setDepthFormat(TSSurface self, TS_Format format);
TS_CAPI TS_Format TS_CCALL tsSurface_getColorFormat(TSSurface self);
TS_CAPI TS_Format TS_CCALL tsSurface_getDepthFormat(TSSurface self);

/// Tellusim::D3D12Surface
TS_CAPI TSD3D12Surface TS_CCALL tsD3D12Surface_new(void);
TS_CAPI TSD3D12Surface TS_CCALL tsD3D12Surface_new_D3D12C(TSD3D12Context context);
TS_CAPI void TS_CCALL tsD3D12Surface_delete(TSD3D12Surface self);
TS_CAPI bool_t TS_CCALL tsD3D12Surface_equalPtr(const TSD3D12Surface self, const TSD3D12Surface ptr);
TS_CAPI TSD3D12Surface TS_CCALL tsD3D12Surface_copyPtr(const TSD3D12Surface self);
TS_CAPI TSD3D12Surface TS_CCALL tsD3D12Surface_clonePtr(const TSD3D12Surface self);
TS_CAPI void TS_CCALL tsD3D12Surface_clearPtr(TSD3D12Surface self);
TS_CAPI void TS_CCALL tsD3D12Surface_destroyPtr(TSD3D12Surface self);
TS_CAPI void TS_CCALL tsD3D12Surface_acquirePtr(TSD3D12Surface self);
TS_CAPI void TS_CCALL tsD3D12Surface_unacquirePtr(TSD3D12Surface self);
TS_CAPI bool_t TS_CCALL tsD3D12Surface_isValidPtr(const TSD3D12Surface self);
TS_CAPI bool_t TS_CCALL tsD3D12Surface_isOwnerPtr(const TSD3D12Surface self);
TS_CAPI bool_t TS_CCALL tsD3D12Surface_isConstPtr(const TSD3D12Surface self);
TS_CAPI uint32_t TS_CCALL tsD3D12Surface_getCountPtr(const TSD3D12Surface self);
TS_CAPI const void* TS_CCALL tsD3D12Surface_getInternalPtr(const TSD3D12Surface self);
TS_CAPI bool_t TS_CCALL tsD3D12Surface_equalSurfacePtr(const TSD3D12Surface self, const TSSurface base);
TS_CAPI TSD3D12Surface TS_CCALL tsD3D12Surface_castSurfacePtr(TSSurface base);
TS_CAPI TSSurface TS_CCALL tsD3D12Surface_baseSurfacePtr(TSD3D12Surface self);
TS_CAPI IDXGIFactory4* TS_CCALL tsD3D12Surface_getFactory(TSD3D12Surface self);
TS_CAPI ID3D12Device* TS_CCALL tsD3D12Surface_getDevice(TSD3D12Surface self);
TS_CAPI ID3D12CommandQueue* TS_CCALL tsD3D12Surface_getQueue(TSD3D12Surface self);
TS_CAPI ID3D12GraphicsCommandList* TS_CCALL tsD3D12Surface_getCommand(TSD3D12Surface self);
TS_CAPI void TS_CCALL tsD3D12Surface_setSwapChain(TSD3D12Surface self, IDXGISwapChain *swap_chain);
TS_CAPI IDXGISwapChain* TS_CCALL tsD3D12Surface_getSwapChain(TSD3D12Surface self);
TS_CAPI void TS_CCALL tsD3D12Surface_setRenderTarget(TSD3D12Surface self, ID3D12Resource *render_target);
TS_CAPI void TS_CCALL tsD3D12Surface_setDepthStencil(TSD3D12Surface self, ID3D12Resource *depth_stencil);
TS_CAPI ID3D12Resource* TS_CCALL tsD3D12Surface_getRenderTarget(TSD3D12Surface self);
TS_CAPI ID3D12Resource* TS_CCALL tsD3D12Surface_getDepthStencil(TSD3D12Surface self);
TS_CAPI void TS_CCALL tsD3D12Surface_setRenderTargetView(TSD3D12Surface self, size_t render_target_view);
TS_CAPI void TS_CCALL tsD3D12Surface_setDepthStencilView(TSD3D12Surface self, size_t depth_stencil_view);
TS_CAPI size_t TS_CCALL tsD3D12Surface_getRenderTargetView(TSD3D12Surface self);
TS_CAPI size_t TS_CCALL tsD3D12Surface_getDepthStencilView(TSD3D12Surface self);
TS_CAPI uint32_t TS_CCALL tsD3D12Surface_getColorDXGIFormat(TSD3D12Surface self);
TS_CAPI uint32_t TS_CCALL tsD3D12Surface_getDepthDXGIFormat(TSD3D12Surface self);

/// Tellusim::D3D11Surface
TS_CAPI TSD3D11Surface TS_CCALL tsD3D11Surface_new(void);
TS_CAPI TSD3D11Surface TS_CCALL tsD3D11Surface_new_D3D11C(TSD3D11Context context);
TS_CAPI void TS_CCALL tsD3D11Surface_delete(TSD3D11Surface self);
TS_CAPI bool_t TS_CCALL tsD3D11Surface_equalPtr(const TSD3D11Surface self, const TSD3D11Surface ptr);
TS_CAPI TSD3D11Surface TS_CCALL tsD3D11Surface_copyPtr(const TSD3D11Surface self);
TS_CAPI TSD3D11Surface TS_CCALL tsD3D11Surface_clonePtr(const TSD3D11Surface self);
TS_CAPI void TS_CCALL tsD3D11Surface_clearPtr(TSD3D11Surface self);
TS_CAPI void TS_CCALL tsD3D11Surface_destroyPtr(TSD3D11Surface self);
TS_CAPI void TS_CCALL tsD3D11Surface_acquirePtr(TSD3D11Surface self);
TS_CAPI void TS_CCALL tsD3D11Surface_unacquirePtr(TSD3D11Surface self);
TS_CAPI bool_t TS_CCALL tsD3D11Surface_isValidPtr(const TSD3D11Surface self);
TS_CAPI bool_t TS_CCALL tsD3D11Surface_isOwnerPtr(const TSD3D11Surface self);
TS_CAPI bool_t TS_CCALL tsD3D11Surface_isConstPtr(const TSD3D11Surface self);
TS_CAPI uint32_t TS_CCALL tsD3D11Surface_getCountPtr(const TSD3D11Surface self);
TS_CAPI const void* TS_CCALL tsD3D11Surface_getInternalPtr(const TSD3D11Surface self);
TS_CAPI bool_t TS_CCALL tsD3D11Surface_equalSurfacePtr(const TSD3D11Surface self, const TSSurface base);
TS_CAPI TSD3D11Surface TS_CCALL tsD3D11Surface_castSurfacePtr(TSSurface base);
TS_CAPI TSSurface TS_CCALL tsD3D11Surface_baseSurfacePtr(TSD3D11Surface self);
TS_CAPI IDXGIFactory* TS_CCALL tsD3D11Surface_getFactory(TSD3D11Surface self);
TS_CAPI ID3D11Device* TS_CCALL tsD3D11Surface_getDevice(TSD3D11Surface self);
TS_CAPI ID3D11DeviceContext* TS_CCALL tsD3D11Surface_getContext(TSD3D11Surface self);
TS_CAPI void TS_CCALL tsD3D11Surface_setSwapChain(TSD3D11Surface self, IDXGISwapChain *swap_chain);
TS_CAPI IDXGISwapChain* TS_CCALL tsD3D11Surface_getSwapChain(TSD3D11Surface self);
TS_CAPI void TS_CCALL tsD3D11Surface_setRenderTarget(TSD3D11Surface self, ID3D11Texture2D *render_target);
TS_CAPI void TS_CCALL tsD3D11Surface_setDepthStencil(TSD3D11Surface self, ID3D11Texture2D *depth_stencil);
TS_CAPI ID3D11Texture2D* TS_CCALL tsD3D11Surface_getRenderTarget(TSD3D11Surface self);
TS_CAPI ID3D11Texture2D* TS_CCALL tsD3D11Surface_getDepthStencil(TSD3D11Surface self);
TS_CAPI void TS_CCALL tsD3D11Surface_setRenderTargetView(TSD3D11Surface self, ID3D11RenderTargetView *render_target_view);
TS_CAPI void TS_CCALL tsD3D11Surface_setDepthStencilView(TSD3D11Surface self, ID3D11DepthStencilView *depth_stencil_view);
TS_CAPI ID3D11RenderTargetView* TS_CCALL tsD3D11Surface_getRenderTargetView(TSD3D11Surface self);
TS_CAPI ID3D11DepthStencilView* TS_CCALL tsD3D11Surface_getDepthStencilView(TSD3D11Surface self);
TS_CAPI uint32_t TS_CCALL tsD3D11Surface_getColorDXGIFormat(TSD3D11Surface self);
TS_CAPI uint32_t TS_CCALL tsD3D11Surface_getDepthDXGIFormat(TSD3D11Surface self);

/// Tellusim::MTLSurface
TS_CAPI TSMTLSurface TS_CCALL tsMTLSurface_new(void);
TS_CAPI TSMTLSurface TS_CCALL tsMTLSurface_new_M(TSMTLContext context);
TS_CAPI void TS_CCALL tsMTLSurface_delete(TSMTLSurface self);
TS_CAPI bool_t TS_CCALL tsMTLSurface_equalPtr(const TSMTLSurface self, const TSMTLSurface ptr);
TS_CAPI TSMTLSurface TS_CCALL tsMTLSurface_copyPtr(const TSMTLSurface self);
TS_CAPI TSMTLSurface TS_CCALL tsMTLSurface_clonePtr(const TSMTLSurface self);
TS_CAPI void TS_CCALL tsMTLSurface_clearPtr(TSMTLSurface self);
TS_CAPI void TS_CCALL tsMTLSurface_destroyPtr(TSMTLSurface self);
TS_CAPI void TS_CCALL tsMTLSurface_acquirePtr(TSMTLSurface self);
TS_CAPI void TS_CCALL tsMTLSurface_unacquirePtr(TSMTLSurface self);
TS_CAPI bool_t TS_CCALL tsMTLSurface_isValidPtr(const TSMTLSurface self);
TS_CAPI bool_t TS_CCALL tsMTLSurface_isOwnerPtr(const TSMTLSurface self);
TS_CAPI bool_t TS_CCALL tsMTLSurface_isConstPtr(const TSMTLSurface self);
TS_CAPI uint32_t TS_CCALL tsMTLSurface_getCountPtr(const TSMTLSurface self);
TS_CAPI const void* TS_CCALL tsMTLSurface_getInternalPtr(const TSMTLSurface self);
TS_CAPI bool_t TS_CCALL tsMTLSurface_equalSurfacePtr(const TSMTLSurface self, const TSSurface base);
TS_CAPI TSMTLSurface TS_CCALL tsMTLSurface_castSurfacePtr(TSSurface base);
TS_CAPI TSSurface TS_CCALL tsMTLSurface_baseSurfacePtr(TSMTLSurface self);
TS_CAPI void* TS_CCALL tsMTLSurface_getDevice(TSMTLSurface self);
TS_CAPI void* TS_CCALL tsMTLSurface_getQueue(TSMTLSurface self);
TS_CAPI void* TS_CCALL tsMTLSurface_getCommand(TSMTLSurface self);
TS_CAPI void TS_CCALL tsMTLSurface_setDescriptor(TSMTLSurface self, void *descriptor);
TS_CAPI void* TS_CCALL tsMTLSurface_getDescriptor(TSMTLSurface self);
TS_CAPI uint32_t TS_CCALL tsMTLSurface_getColorPixelFormat(TSMTLSurface self);
TS_CAPI uint32_t TS_CCALL tsMTLSurface_getDepthPixelFormat(TSMTLSurface self);

/// Tellusim::VKSurface
TS_CAPI TSVKSurface TS_CCALL tsVKSurface_new(void);
TS_CAPI TSVKSurface TS_CCALL tsVKSurface_new_V(TSVKContext context);
TS_CAPI void TS_CCALL tsVKSurface_delete(TSVKSurface self);
TS_CAPI bool_t TS_CCALL tsVKSurface_equalPtr(const TSVKSurface self, const TSVKSurface ptr);
TS_CAPI TSVKSurface TS_CCALL tsVKSurface_copyPtr(const TSVKSurface self);
TS_CAPI TSVKSurface TS_CCALL tsVKSurface_clonePtr(const TSVKSurface self);
TS_CAPI void TS_CCALL tsVKSurface_clearPtr(TSVKSurface self);
TS_CAPI void TS_CCALL tsVKSurface_destroyPtr(TSVKSurface self);
TS_CAPI void TS_CCALL tsVKSurface_acquirePtr(TSVKSurface self);
TS_CAPI void TS_CCALL tsVKSurface_unacquirePtr(TSVKSurface self);
TS_CAPI bool_t TS_CCALL tsVKSurface_isValidPtr(const TSVKSurface self);
TS_CAPI bool_t TS_CCALL tsVKSurface_isOwnerPtr(const TSVKSurface self);
TS_CAPI bool_t TS_CCALL tsVKSurface_isConstPtr(const TSVKSurface self);
TS_CAPI uint32_t TS_CCALL tsVKSurface_getCountPtr(const TSVKSurface self);
TS_CAPI const void* TS_CCALL tsVKSurface_getInternalPtr(const TSVKSurface self);
TS_CAPI bool_t TS_CCALL tsVKSurface_equalSurfacePtr(const TSVKSurface self, const TSSurface base);
TS_CAPI TSVKSurface TS_CCALL tsVKSurface_castSurfacePtr(TSSurface base);
TS_CAPI TSSurface TS_CCALL tsVKSurface_baseSurfacePtr(TSVKSurface self);
TS_CAPI VkInstance TS_CCALL tsVKSurface_getInstance(TSVKSurface self);
TS_CAPI VkPhysicalDevice TS_CCALL tsVKSurface_getAdapter(TSVKSurface self);
TS_CAPI VkDevice TS_CCALL tsVKSurface_getDevice(TSVKSurface self);
TS_CAPI VkQueue TS_CCALL tsVKSurface_getQueue(TSVKSurface self);
TS_CAPI VkCommandBuffer TS_CCALL tsVKSurface_getCommand(TSVKSurface self);
TS_CAPI uint32_t TS_CCALL tsVKSurface_getFamily(TSVKSurface self);
TS_CAPI void TS_CCALL tsVKSurface_setSwapChain(TSVKSurface self, VkSwapchainKHR swap_chain);
TS_CAPI VkSwapchainKHR TS_CCALL tsVKSurface_getSwapChain(TSVKSurface self);
TS_CAPI void TS_CCALL tsVKSurface_setColorImage(TSVKSurface self, VkImage image);
TS_CAPI void TS_CCALL tsVKSurface_setDepthImage(TSVKSurface self, VkImage image);
TS_CAPI VkImage TS_CCALL tsVKSurface_getColorImage(TSVKSurface self);
TS_CAPI VkImage TS_CCALL tsVKSurface_getDepthImage(TSVKSurface self);
TS_CAPI void TS_CCALL tsVKSurface_setColorImageView(TSVKSurface self, VkImageView image_view);
TS_CAPI void TS_CCALL tsVKSurface_setDepthImageView(TSVKSurface self, VkImageView image_view);
TS_CAPI VkImageView TS_CCALL tsVKSurface_getColorImageView(TSVKSurface self);
TS_CAPI VkImageView TS_CCALL tsVKSurface_getDepthImageView(TSVKSurface self);
TS_CAPI void TS_CCALL tsVKSurface_setRenderPass(TSVKSurface self, VkRenderPass render_pass);
TS_CAPI void TS_CCALL tsVKSurface_setFramebuffer(TSVKSurface self, VkFramebuffer framebuffer);
TS_CAPI VkRenderPass TS_CCALL tsVKSurface_getRenderPass(TSVKSurface self);
TS_CAPI VkFramebuffer TS_CCALL tsVKSurface_getFramebuffer(TSVKSurface self);
TS_CAPI uint32_t TS_CCALL tsVKSurface_getColorPixelFormat(TSVKSurface self);
TS_CAPI uint32_t TS_CCALL tsVKSurface_getDepthPixelFormat(TSVKSurface self);

/// Tellusim::GLSurface
TS_CAPI TSGLSurface TS_CCALL tsGLSurface_new(void);
TS_CAPI TSGLSurface TS_CCALL tsGLSurface_new_G(TSGLContext context);
TS_CAPI void TS_CCALL tsGLSurface_delete(TSGLSurface self);
TS_CAPI bool_t TS_CCALL tsGLSurface_equalPtr(const TSGLSurface self, const TSGLSurface ptr);
TS_CAPI TSGLSurface TS_CCALL tsGLSurface_copyPtr(const TSGLSurface self);
TS_CAPI TSGLSurface TS_CCALL tsGLSurface_clonePtr(const TSGLSurface self);
TS_CAPI void TS_CCALL tsGLSurface_clearPtr(TSGLSurface self);
TS_CAPI void TS_CCALL tsGLSurface_destroyPtr(TSGLSurface self);
TS_CAPI void TS_CCALL tsGLSurface_acquirePtr(TSGLSurface self);
TS_CAPI void TS_CCALL tsGLSurface_unacquirePtr(TSGLSurface self);
TS_CAPI bool_t TS_CCALL tsGLSurface_isValidPtr(const TSGLSurface self);
TS_CAPI bool_t TS_CCALL tsGLSurface_isOwnerPtr(const TSGLSurface self);
TS_CAPI bool_t TS_CCALL tsGLSurface_isConstPtr(const TSGLSurface self);
TS_CAPI uint32_t TS_CCALL tsGLSurface_getCountPtr(const TSGLSurface self);
TS_CAPI const void* TS_CCALL tsGLSurface_getInternalPtr(const TSGLSurface self);
TS_CAPI bool_t TS_CCALL tsGLSurface_equalSurfacePtr(const TSGLSurface self, const TSSurface base);
TS_CAPI TSGLSurface TS_CCALL tsGLSurface_castSurfacePtr(TSSurface base);
TS_CAPI TSSurface TS_CCALL tsGLSurface_baseSurfacePtr(TSGLSurface self);
TS_CAPI void* TS_CCALL tsGLSurface_getContext(TSGLSurface self);
TS_CAPI void TS_CCALL tsGLSurface_setColorTextureID(TSGLSurface self, uint32_t texture_id);
TS_CAPI void TS_CCALL tsGLSurface_setDepthTextureID(TSGLSurface self, uint32_t texture_id);
TS_CAPI uint32_t TS_CCALL tsGLSurface_getColorTextureID(TSGLSurface self);
TS_CAPI uint32_t TS_CCALL tsGLSurface_getDepthTextureID(TSGLSurface self);
TS_CAPI void TS_CCALL tsGLSurface_setFramebufferID(TSGLSurface self, uint32_t framebuffer_id);
TS_CAPI uint32_t TS_CCALL tsGLSurface_getFramebufferID(TSGLSurface self);
TS_CAPI uint32_t TS_CCALL tsGLSurface_getColorInternalFormat(TSGLSurface self);
TS_CAPI uint32_t TS_CCALL tsGLSurface_getDepthInternalFormat(TSGLSurface self);

/// Tellusim::GLESSurface
TS_CAPI TSGLESSurface TS_CCALL tsGLESSurface_new(void);
TS_CAPI TSGLESSurface TS_CCALL tsGLESSurface_new_G(TSGLESContext context);
TS_CAPI void TS_CCALL tsGLESSurface_delete(TSGLESSurface self);
TS_CAPI bool_t TS_CCALL tsGLESSurface_equalPtr(const TSGLESSurface self, const TSGLESSurface ptr);
TS_CAPI TSGLESSurface TS_CCALL tsGLESSurface_copyPtr(const TSGLESSurface self);
TS_CAPI TSGLESSurface TS_CCALL tsGLESSurface_clonePtr(const TSGLESSurface self);
TS_CAPI void TS_CCALL tsGLESSurface_clearPtr(TSGLESSurface self);
TS_CAPI void TS_CCALL tsGLESSurface_destroyPtr(TSGLESSurface self);
TS_CAPI void TS_CCALL tsGLESSurface_acquirePtr(TSGLESSurface self);
TS_CAPI void TS_CCALL tsGLESSurface_unacquirePtr(TSGLESSurface self);
TS_CAPI bool_t TS_CCALL tsGLESSurface_isValidPtr(const TSGLESSurface self);
TS_CAPI bool_t TS_CCALL tsGLESSurface_isOwnerPtr(const TSGLESSurface self);
TS_CAPI bool_t TS_CCALL tsGLESSurface_isConstPtr(const TSGLESSurface self);
TS_CAPI uint32_t TS_CCALL tsGLESSurface_getCountPtr(const TSGLESSurface self);
TS_CAPI const void* TS_CCALL tsGLESSurface_getInternalPtr(const TSGLESSurface self);
TS_CAPI bool_t TS_CCALL tsGLESSurface_equalSurfacePtr(const TSGLESSurface self, const TSSurface base);
TS_CAPI TSGLESSurface TS_CCALL tsGLESSurface_castSurfacePtr(TSSurface base);
TS_CAPI TSSurface TS_CCALL tsGLESSurface_baseSurfacePtr(TSGLESSurface self);
TS_CAPI void* TS_CCALL tsGLESSurface_getContext(TSGLESSurface self);
TS_CAPI void TS_CCALL tsGLESSurface_setColorTextureID(TSGLESSurface self, uint32_t texture_id);
TS_CAPI void TS_CCALL tsGLESSurface_setDepthTextureID(TSGLESSurface self, uint32_t texture_id);
TS_CAPI uint32_t TS_CCALL tsGLESSurface_getColorTextureID(TSGLESSurface self);
TS_CAPI uint32_t TS_CCALL tsGLESSurface_getDepthTextureID(TSGLESSurface self);
TS_CAPI void TS_CCALL tsGLESSurface_setFramebufferID(TSGLESSurface self, uint32_t framebuffer_id);
TS_CAPI uint32_t TS_CCALL tsGLESSurface_getFramebufferID(TSGLESSurface self);
TS_CAPI uint32_t TS_CCALL tsGLESSurface_getColorInternalFormat(TSGLESSurface self);
TS_CAPI uint32_t TS_CCALL tsGLESSurface_getDepthInternalFormat(TSGLESSurface self);

/// Tellusim::Window
typedef void (*TSWindowMousePressedCallback)(TS_WindowButton button, void *data_);
typedef void (*TSWindowMouseReleasedCallback)(TS_WindowButton button, void *data_);
typedef void (*TSWindowMouseChangedCallback)(int32_t x, int32_t y, void *data_);
typedef void (*TSWindowMouseRotatedCallback)(TS_WindowAxis axis, float32_t delta, void *data_);
typedef void (*TSWindowTouchChangedCallback)(void *data_);
typedef void (*TSWindowKeyboardPressedCallback)(uint32_t key, uint32_t code, void *data_);
typedef void (*TSWindowKeyboardReleasedCallback)(uint32_t key, void *data_);
typedef void (*TSWindowSizeChangedCallback)(uint32_t width, uint32_t height, void *data_);
typedef void (*TSWindowFocusChangedCallback)(bool_t changed, void *data_);
typedef void (*TSWindowCloseClickedCallback)(void *data_);
typedef void (*TSWindowPauseChangedCallback)(bool_t paused, void *data_);
typedef void (*TSWindowFileDroppedCallback)(const char *name, uint32_t remain, void *data_);
typedef void (*TSWindowUpdateCallback)(void *data_);
typedef void (*TSWindowPresentCallback)(void *data_);
typedef bool_t (*TSWindowMainLoopCallback)(void *data_);
TS_CAPI TSWindow TS_CCALL tsWindow_new(void);
TS_CAPI TSWindow TS_CCALL tsWindow_new_Pu(TS_Platform platform, uint32_t index);
TS_CAPI TSWindow TS_CCALL tsWindow_new_S(TSSurface surface);
TS_CAPI void TS_CCALL tsWindow_delete(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_equalPtr(const TSWindow self, const TSWindow ptr);
TS_CAPI TSWindow TS_CCALL tsWindow_copyPtr(const TSWindow self);
TS_CAPI TSWindow TS_CCALL tsWindow_clonePtr(const TSWindow self);
TS_CAPI void TS_CCALL tsWindow_clearPtr(TSWindow self);
TS_CAPI void TS_CCALL tsWindow_destroyPtr(TSWindow self);
TS_CAPI void TS_CCALL tsWindow_acquirePtr(TSWindow self);
TS_CAPI void TS_CCALL tsWindow_unacquirePtr(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_isValidPtr(const TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_isOwnerPtr(const TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_isConstPtr(const TSWindow self);
TS_CAPI uint32_t TS_CCALL tsWindow_getCountPtr(const TSWindow self);
TS_CAPI const void* TS_CCALL tsWindow_getInternalPtr(const TSWindow self);
TS_CAPI uint32_t TS_CCALL tsWindow_getNumWindows(void);
TS_CAPI TSWindow TS_CCALL tsWindow_getWindow(uint32_t index);
TS_CAPI void TS_CCALL tsWindow_update(bool_t wait);
TS_CAPI TS_Platform TS_CCALL tsWindow_getPlatform(TSWindow self);
TS_CAPI const char* TS_CCALL tsWindow_getPlatformName(TSWindow self);
TS_CAPI uint32_t TS_CCALL tsWindow_getIndex(TSWindow self);
TS_CAPI void TS_CCALL tsWindow_setSurface(TSWindow self, TSSurface surface);
TS_CAPI TSSurface TS_CCALL tsWindow_getSurface(TSWindow self);
TS_CAPI void* TS_CCALL tsWindow_getHandle(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_isCreated(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_create_sWF(TSWindow self, const char *title, TS_WindowFlags flags);
TS_CAPI bool_t TS_CCALL tsWindow_create_cSWF(TSWindow self, const TSString title, TS_WindowFlags flags);
TS_CAPI bool_t TS_CCALL tsWindow_create_WF(TSWindow self, TS_WindowFlags flags);
TS_CAPI void TS_CCALL tsWindow_release(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_clear(TSWindow self, const TSColor *color);
TS_CAPI bool_t TS_CCALL tsWindow_grab(TSWindow self, TSImage image);
TS_CAPI bool_t TS_CCALL tsWindow_render(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_present(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_finish(TSWindow self);
TS_CAPI TS_Format TS_CCALL tsWindow_getColorFormat(TSWindow self);
TS_CAPI TS_Format TS_CCALL tsWindow_getDepthFormat(TSWindow self);
TS_CAPI uint32_t TS_CCALL tsWindow_getMultisample(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_hasMultisample(TSWindow self);
TS_CAPI void TS_CCALL tsWindow_setFlags(TSWindow self, TS_WindowFlags flags);
TS_CAPI TS_WindowFlags TS_CCALL tsWindow_getFlags(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_hasFlag(TSWindow self, TS_WindowFlags flags);
TS_CAPI bool_t TS_CCALL tsWindow_hasFlags(TSWindow self, TS_WindowFlags flags);
TS_CAPI void TS_CCALL tsWindow_setRefreshRate(TSWindow self, uint32_t rate);
TS_CAPI uint32_t TS_CCALL tsWindow_getRefreshRate(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_setHidden(TSWindow self, bool_t hidden);
TS_CAPI bool_t TS_CCALL tsWindow_isHidden(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_setFocused(TSWindow self, bool_t focused);
TS_CAPI bool_t TS_CCALL tsWindow_isFocused(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_setMinimized(TSWindow self, bool_t minimized);
TS_CAPI bool_t TS_CCALL tsWindow_isMinimized(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_setFullscreen(TSWindow self, bool_t fullscreen);
TS_CAPI bool_t TS_CCALL tsWindow_isFullscreen(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_isOccluded(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_setTitle_s(TSWindow self, const char *title);
TS_CAPI bool_t TS_CCALL tsWindow_setTitle_cS(TSWindow self, const TSString title);
TS_CAPI TSString TS_CCALL tsWindow_getTitle(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_setIcon(TSWindow self, const TSImage image);
TS_CAPI TSImage TS_CCALL tsWindow_getIcon(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_setGeometry(TSWindow self, int32_t x, int32_t y, uint32_t width, uint32_t height, bool_t force);
TS_CAPI bool_t TS_CCALL tsWindow_setPosition(TSWindow self, int32_t x, int32_t y, bool_t force);
TS_CAPI int32_t TS_CCALL tsWindow_getPositionX(TSWindow self, bool_t title);
TS_CAPI int32_t TS_CCALL tsWindow_getPositionY(TSWindow self, bool_t title);
TS_CAPI bool_t TS_CCALL tsWindow_setSize(TSWindow self, uint32_t width, uint32_t height, bool_t force);
TS_CAPI uint32_t TS_CCALL tsWindow_getWidth(TSWindow self);
TS_CAPI uint32_t TS_CCALL tsWindow_getHeight(TSWindow self);
TS_CAPI float32_t TS_CCALL tsWindow_getScale(TSWindow self);
TS_CAPI uint32_t TS_CCALL tsWindow_getDpiX(TSWindow self);
TS_CAPI uint32_t TS_CCALL tsWindow_getDpiY(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_setMinSize(TSWindow self, uint32_t width, uint32_t height, bool_t force);
TS_CAPI uint32_t TS_CCALL tsWindow_getMinWidth(TSWindow self);
TS_CAPI uint32_t TS_CCALL tsWindow_getMinHeight(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_setMaxSize(TSWindow self, uint32_t width, uint32_t height, bool_t force);
TS_CAPI uint32_t TS_CCALL tsWindow_getMaxWidth(TSWindow self);
TS_CAPI uint32_t TS_CCALL tsWindow_getMaxHeight(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_setMouse(TSWindow self, int32_t x, int32_t y, bool_t force);
TS_CAPI int32_t TS_CCALL tsWindow_getMouseX(TSWindow self);
TS_CAPI int32_t TS_CCALL tsWindow_getMouseY(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_setMouseDelta(TSWindow self, int32_t dx, int32_t dy);
TS_CAPI int32_t TS_CCALL tsWindow_getMouseDX(TSWindow self);
TS_CAPI int32_t TS_CCALL tsWindow_getMouseDY(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_setMouseHidden(TSWindow self, bool_t hidden, bool_t force);
TS_CAPI bool_t TS_CCALL tsWindow_isMouseHidden(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_setMouseClipped(TSWindow self, bool_t clipped, bool_t force);
TS_CAPI bool_t TS_CCALL tsWindow_isMouseClipped(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_isMouseInside(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_setMouseCursor(TSWindow self, TS_WindowCursor cursor, bool_t force);
TS_CAPI TS_WindowCursor TS_CCALL tsWindow_getMouseCursor(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_setMouseButtons(TSWindow self, TS_WindowButton buttons);
TS_CAPI TS_WindowButton TS_CCALL tsWindow_getMouseButtons(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_setMouseButton(TSWindow self, TS_WindowButton button, bool_t value);
TS_CAPI bool_t TS_CCALL tsWindow_getMouseButton(TSWindow self, TS_WindowButton button, bool_t clear);
TS_CAPI bool_t TS_CCALL tsWindow_wasMouseButtonReleased(TSWindow self, TS_WindowButton button);
TS_CAPI void TS_CCALL tsWindow_releaseMouseButtons(TSWindow self, TS_WindowButton buttons);
TS_CAPI TS_WindowButton TS_CCALL tsWindow_clearMouseButtons(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_setMouseAxis(TSWindow self, TS_WindowAxis axis, float32_t value);
TS_CAPI float32_t TS_CCALL tsWindow_getMouseAxis(TSWindow self, TS_WindowAxis axis);
TS_CAPI float32_t TS_CCALL tsWindow_clearMouseAxis(TSWindow self, TS_WindowAxis axis);
TS_CAPI void TS_CCALL tsWindow_setMousePressedCallback(TSWindow self, const TSWindowMousePressedCallback func, void *data_);
TS_CAPI void TS_CCALL tsWindow_setMouseReleasedCallback(TSWindow self, const TSWindowMouseReleasedCallback func, void *data_);
TS_CAPI void TS_CCALL tsWindow_setMouseChangedCallback(TSWindow self, const TSWindowMouseChangedCallback func, void *data_);
TS_CAPI void TS_CCALL tsWindow_setMouseRotatedCallback(TSWindow self, const TSWindowMouseRotatedCallback func, void *data_);
TS_CAPI uint32_t TS_CCALL tsWindow_getNumTouches(TSWindow self);
TS_CAPI uint32_t TS_CCALL tsWindow_addTouch(TSWindow self, int32_t x, int32_t y);
TS_CAPI int32_t TS_CCALL tsWindow_getTouchX(TSWindow self, uint32_t touch);
TS_CAPI int32_t TS_CCALL tsWindow_getTouchY(TSWindow self, uint32_t touch);
TS_CAPI uint32_t TS_CCALL tsWindow_findTouch(TSWindow self, int32_t x, int32_t y);
TS_CAPI void TS_CCALL tsWindow_clearTouches(TSWindow self);
TS_CAPI void TS_CCALL tsWindow_setTouchChangedCallback(TSWindow self, const TSWindowTouchChangedCallback func, void *data_);
TS_CAPI void TS_CCALL tsWindow_setKeyboardKey(TSWindow self, uint32_t key, bool_t value);
TS_CAPI bool_t TS_CCALL tsWindow_getKeyboardKey(TSWindow self, uint32_t key, bool_t clear);
TS_CAPI bool_t TS_CCALL tsWindow_wasKeyboardKeyPressed(TSWindow self, uint32_t key);
TS_CAPI bool_t TS_CCALL tsWindow_wasKeyboardKeyReleased(TSWindow self, uint32_t key);
TS_CAPI void TS_CCALL tsWindow_setKeyboardPressedCallback(TSWindow self, const TSWindowKeyboardPressedCallback func, void *data_);
TS_CAPI void TS_CCALL tsWindow_setKeyboardReleasedCallback(TSWindow self, const TSWindowKeyboardReleasedCallback func, void *data_);
TS_CAPI void TS_CCALL tsWindow_setSizeChangedCallback(TSWindow self, const TSWindowSizeChangedCallback func, void *data_);
TS_CAPI void TS_CCALL tsWindow_setFocusChangedCallback(TSWindow self, const TSWindowFocusChangedCallback func, void *data_);
TS_CAPI void TS_CCALL tsWindow_setCloseClickedCallback(TSWindow self, const TSWindowCloseClickedCallback func, void *data_);
TS_CAPI void TS_CCALL tsWindow_setPauseChangedCallback(TSWindow self, const TSWindowPauseChangedCallback func, void *data_);
TS_CAPI void TS_CCALL tsWindow_setFileDroppedCallback(TSWindow self, const TSWindowFileDroppedCallback func, void *data_);
TS_CAPI void TS_CCALL tsWindow_setUpdateCallback(TSWindow self, const TSWindowUpdateCallback func, void *data_);
TS_CAPI void TS_CCALL tsWindow_setPresentCallback(TSWindow self, const TSWindowPresentCallback func, void *data_);
TS_CAPI bool_t TS_CCALL tsWindow_run(TSWindow self, const TSWindowMainLoopCallback func, void *data_);
TS_CAPI bool_t TS_CCALL tsWindow_isRunning(TSWindow self);
TS_CAPI void TS_CCALL tsWindow_stop(TSWindow self);
TS_CAPI bool_t TS_CCALL tsWindow_setCopyText_s(TSWindow self, const char *text);
TS_CAPI bool_t TS_CCALL tsWindow_setCopyText_cS(TSWindow self, const TSString text);
TS_CAPI TSString TS_CCALL tsWindow_getPasteText(TSWindow self);

/// Tellusim::Font
TS_CAPI TSFont TS_CCALL tsFont_new(void);
TS_CAPI void TS_CCALL tsFont_delete(TSFont self);
TS_CAPI bool_t TS_CCALL tsFont_equalPtr(const TSFont self, const TSFont ptr);
TS_CAPI TSFont TS_CCALL tsFont_copyPtr(const TSFont self);
TS_CAPI TSFont TS_CCALL tsFont_clonePtr(const TSFont self);
TS_CAPI void TS_CCALL tsFont_clearPtr(TSFont self);
TS_CAPI void TS_CCALL tsFont_destroyPtr(TSFont self);
TS_CAPI void TS_CCALL tsFont_acquirePtr(TSFont self);
TS_CAPI void TS_CCALL tsFont_unacquirePtr(TSFont self);
TS_CAPI bool_t TS_CCALL tsFont_isValidPtr(const TSFont self);
TS_CAPI bool_t TS_CCALL tsFont_isOwnerPtr(const TSFont self);
TS_CAPI bool_t TS_CCALL tsFont_isConstPtr(const TSFont self);
TS_CAPI uint32_t TS_CCALL tsFont_getCountPtr(const TSFont self);
TS_CAPI const void* TS_CCALL tsFont_getInternalPtr(const TSFont self);
TS_CAPI void TS_CCALL tsFont_clear(TSFont self);
TS_CAPI bool_t TS_CCALL tsFont_isLoaded(TSFont self);
TS_CAPI bool_t TS_CCALL tsFont_load_s(TSFont self, const char *name);
TS_CAPI bool_t TS_CCALL tsFont_load_St(TSFont self, TSStream stream);
TS_CAPI float32_t TS_CCALL tsFont_getAdvance(TSFont self, const TSFontStyle *style, uint32_t code);
TS_CAPI TSRect TS_CCALL tsFont_getRect_cV3cFSs(TSFont self, const TSVector3f *position, const TSFontStyle *style, const char *str);
TS_CAPI TSRect TS_CCALL tsFont_getRect_cV3cFSup(TSFont self, const TSVector3f *position, const TSFontStyle *style, const uint32_t *str);
TS_CAPI TSRect TS_CCALL tsFont_getRect_cFBu(TSFont self, const TSFontBatch *batches, uint32_t num_batches);
TS_CAPI TSRect TS_CCALL tsFont_getRect_cFB32u(TSFont self, const TSFontBatch32 *batches, uint32_t num_batches);
TS_CAPI void TS_CCALL tsFont_create_cDcFSs(TSFont self, const TSDevice device, const TSFontStyle *style, const char *str);
TS_CAPI void TS_CCALL tsFont_create_cDcFSup(TSFont self, const TSDevice device, const TSFontStyle *style, const uint32_t *str);
TS_CAPI void TS_CCALL tsFont_create_cDcFBu(TSFont self, const TSDevice device, const TSFontBatch *batches, uint32_t num_batches);
TS_CAPI void TS_CCALL tsFont_create_cDcFB32u(TSFont self, const TSDevice device, const TSFontBatch32 *batches, uint32_t num_batches);
TS_CAPI void TS_CCALL tsFont_draw_CcV3cFSs(TSFont self, TSCommand command, const TSVector3f *position, const TSFontStyle *style, const char *str);
TS_CAPI void TS_CCALL tsFont_draw_CcV3cFSup(TSFont self, TSCommand command, const TSVector3f *position, const TSFontStyle *style, const uint32_t *str);
TS_CAPI void TS_CCALL tsFont_draw_CcFBu(TSFont self, TSCommand command, const TSFontBatch *batches, uint32_t num_batches);
TS_CAPI void TS_CCALL tsFont_draw_CcFB32u(TSFont self, TSCommand command, const TSFontBatch32 *batches, uint32_t num_batches);
TS_CAPI bool_t TS_CCALL tsFont_flush(TSFont self, const TSDevice device);

/// Tellusim::CanvasElement
typedef bool_t (*TSCanvasElementDrawCallback)(TSCommand command, TSCanvasElement element, void *data_);
TS_CAPI TSCanvasElement TS_CCALL tsCanvasElement_new(void);
TS_CAPI void TS_CCALL tsCanvasElement_delete(TSCanvasElement self);
TS_CAPI bool_t TS_CCALL tsCanvasElement_equalPtr(const TSCanvasElement self, const TSCanvasElement ptr);
TS_CAPI TSCanvasElement TS_CCALL tsCanvasElement_copyPtr(const TSCanvasElement self);
TS_CAPI TSCanvasElement TS_CCALL tsCanvasElement_clonePtr(const TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_clearPtr(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_destroyPtr(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_acquirePtr(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_unacquirePtr(TSCanvasElement self);
TS_CAPI bool_t TS_CCALL tsCanvasElement_isValidPtr(const TSCanvasElement self);
TS_CAPI bool_t TS_CCALL tsCanvasElement_isOwnerPtr(const TSCanvasElement self);
TS_CAPI bool_t TS_CCALL tsCanvasElement_isConstPtr(const TSCanvasElement self);
TS_CAPI uint32_t TS_CCALL tsCanvasElement_getCountPtr(const TSCanvasElement self);
TS_CAPI const void* TS_CCALL tsCanvasElement_getInternalPtr(const TSCanvasElement self);
TS_CAPI TS_CanvasElementType TS_CCALL tsCanvasElement_getType(TSCanvasElement self);
TS_CAPI const char* TS_CCALL tsCanvasElement_getTypeName_CET(TS_CanvasElementType type);
TS_CAPI const char* TS_CCALL tsCanvasElement_getTypeName_c(TSCanvasElement self);
TS_CAPI bool_t TS_CCALL tsCanvasElement_isText(TSCanvasElement self);
TS_CAPI bool_t TS_CCALL tsCanvasElement_isMesh(TSCanvasElement self);
TS_CAPI bool_t TS_CCALL tsCanvasElement_isRect(TSCanvasElement self);
TS_CAPI bool_t TS_CCALL tsCanvasElement_isTriangle(TSCanvasElement self);
TS_CAPI bool_t TS_CCALL tsCanvasElement_isEllipse(TSCanvasElement self);
TS_CAPI bool_t TS_CCALL tsCanvasElement_isShape(TSCanvasElement self);
TS_CAPI bool_t TS_CCALL tsCanvasElement_isStrip(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_setCanvas(TSCanvasElement self, TSCanvas canvas);
TS_CAPI TSCanvas TS_CCALL tsCanvasElement_getCanvas_c(TSCanvasElement self);
TS_CAPI TSCanvas TS_CCALL tsCanvasElement_getCanvas(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_setMode(TSCanvasElement self, TS_CanvasElementMode mode);
TS_CAPI TS_CanvasElementMode TS_CCALL tsCanvasElement_getMode(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_setAlign(TSCanvasElement self, TS_CanvasElementAlign align);
TS_CAPI TS_CanvasElementAlign TS_CCALL tsCanvasElement_getAlign(TSCanvasElement self);
TS_CAPI bool_t TS_CCALL tsCanvasElement_hasAlign(TSCanvasElement self, TS_CanvasElementAlign align);
TS_CAPI bool_t TS_CCALL tsCanvasElement_hasAligns(TSCanvasElement self, TS_CanvasElementAlign aligns);
TS_CAPI void TS_CCALL tsCanvasElement_setOrder(TSCanvasElement self, int32_t order);
TS_CAPI int32_t TS_CCALL tsCanvasElement_getOrder(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_setEnabled(TSCanvasElement self, bool_t enabled);
TS_CAPI bool_t TS_CCALL tsCanvasElement_isEnabled(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_clearColor(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_setColor_CES(TSCanvasElement self, TS_CanvasElementStack op);
TS_CAPI void TS_CCALL tsCanvasElement_setColor_cCCES(TSCanvasElement self, const TSColor *color, TS_CanvasElementStack op);
TS_CAPI void TS_CCALL tsCanvasElement_setColor_ffffCES(TSCanvasElement self, float32_t r, float32_t g, float32_t b, float32_t a, TS_CanvasElementStack op);
TS_CAPI TSColor TS_CCALL tsCanvasElement_getColor(TSCanvasElement self);
TS_CAPI TS_CanvasElementStack TS_CCALL tsCanvasElement_getColorOp(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_clearTransform(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_setTransform_CES(TSCanvasElement self, TS_CanvasElementStack op);
TS_CAPI void TS_CCALL tsCanvasElement_setTransform_cM44CES(TSCanvasElement self, const TSMatrix4x4f *transform, TS_CanvasElementStack op);
TS_CAPI TSMatrix4x4f TS_CCALL tsCanvasElement_getTransform(TSCanvasElement self);
TS_CAPI TS_CanvasElementStack TS_CCALL tsCanvasElement_getTransformOp(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_clearScissor(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_setScissor_CES(TSCanvasElement self, TS_CanvasElementStack op);
TS_CAPI void TS_CCALL tsCanvasElement_setScissor_cRCES(TSCanvasElement self, const TSRect *scissor, TS_CanvasElementStack op);
TS_CAPI TSRect TS_CCALL tsCanvasElement_getScissor(TSCanvasElement self);
TS_CAPI TS_CanvasElementStack TS_CCALL tsCanvasElement_getScissorOp(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_setMipmap(TSCanvasElement self, float32_t mipmap);
TS_CAPI float32_t TS_CCALL tsCanvasElement_getMipmap(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_setSampler(TSCanvasElement self, TSSampler sampler);
TS_CAPI TSSampler TS_CCALL tsCanvasElement_getSampler(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_setFilter(TSCanvasElement self, TS_SamplerFilter filter);
TS_CAPI TS_SamplerFilter TS_CCALL tsCanvasElement_getFilter(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_setAnisotropy(TSCanvasElement self, uint32_t anisotropy);
TS_CAPI uint32_t TS_CCALL tsCanvasElement_getAnisotropy(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_setWrapMode(TSCanvasElement self, TS_SamplerWrapMode mode);
TS_CAPI TS_SamplerWrapMode TS_CCALL tsCanvasElement_getWrapMode(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_setTexture(TSCanvasElement self, TSTexture texture, bool_t linear);
TS_CAPI TSTexture TS_CCALL tsCanvasElement_getTexture(TSCanvasElement self);
TS_CAPI bool_t TS_CCALL tsCanvasElement_getTextureLinear(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_setPipeline(TSCanvasElement self, TSPipeline pipeline);
TS_CAPI TSPipeline TS_CCALL tsCanvasElement_getPipeline(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_setPrimitive(TSCanvasElement self, TS_PipelinePrimitive primitive);
TS_CAPI TS_PipelinePrimitive TS_CCALL tsCanvasElement_getPrimitive(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_setCullMode(TSCanvasElement self, TS_PipelineCullMode mode);
TS_CAPI TS_PipelineCullMode TS_CCALL tsCanvasElement_getCullMode(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_setFrontMode(TSCanvasElement self, TS_PipelineFrontMode mode);
TS_CAPI TS_PipelineFrontMode TS_CCALL tsCanvasElement_getFrontMode(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_setBlend(TSCanvasElement self, TS_PipelineBlendOp op, TS_PipelineBlendFunc src, TS_PipelineBlendFunc dest);
TS_CAPI TS_PipelineBlendOp TS_CCALL tsCanvasElement_getBlendOp(TSCanvasElement self);
TS_CAPI TS_PipelineBlendFunc TS_CCALL tsCanvasElement_getBlendSrcFunc(TSCanvasElement self);
TS_CAPI TS_PipelineBlendFunc TS_CCALL tsCanvasElement_getBlendDestFunc(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_setColorMask(TSCanvasElement self, TS_PipelineColorMask mask);
TS_CAPI TS_PipelineColorMask TS_CCALL tsCanvasElement_getColorMask(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_setDepthMask(TSCanvasElement self, TS_PipelineDepthMask mask);
TS_CAPI TS_PipelineDepthMask TS_CCALL tsCanvasElement_getDepthMask(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_setDepthFunc(TSCanvasElement self, TS_PipelineDepthFunc func);
TS_CAPI TS_PipelineDepthFunc TS_CCALL tsCanvasElement_getDepthFunc(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_setStencilRef(TSCanvasElement self, uint32_t ref);
TS_CAPI void TS_CCALL tsCanvasElement_setStencilFunc(TSCanvasElement self, TS_PipelineStencilFunc func, TS_PipelineStencilOp fail_op, TS_PipelineStencilOp dfail_op, TS_PipelineStencilOp dpass_op);
TS_CAPI uint32_t TS_CCALL tsCanvasElement_getStencilRef(TSCanvasElement self);
TS_CAPI TS_PipelineStencilFunc TS_CCALL tsCanvasElement_getStencilFunc(TSCanvasElement self);
TS_CAPI TS_PipelineStencilOp TS_CCALL tsCanvasElement_getStencilFailOp(TSCanvasElement self);
TS_CAPI TS_PipelineStencilOp TS_CCALL tsCanvasElement_getStencilDepthFailOp(TSCanvasElement self);
TS_CAPI TS_PipelineStencilOp TS_CCALL tsCanvasElement_getStencilDepthPassOp(TSCanvasElement self);
TS_CAPI void TS_CCALL tsCanvasElement_setDrawCallback(TSCanvasElement self, const TSCanvasElementDrawCallback func, void *data_);
TS_CAPI TSRect TS_CCALL tsCanvasElement_getRect(TSCanvasElement self);

/// Tellusim::CanvasText
TS_CAPI TSCanvasText TS_CCALL tsCanvasText_new(void);
TS_CAPI TSCanvasText TS_CCALL tsCanvasText_new_C(TSCanvas canvas);
TS_CAPI TSCanvasText TS_CCALL tsCanvasText_new_Cs(TSCanvas canvas, const char *text);
TS_CAPI TSCanvasText TS_CCALL tsCanvasText_new_CcS(TSCanvas canvas, const TSString text);
TS_CAPI void TS_CCALL tsCanvasText_delete(TSCanvasText self);
TS_CAPI bool_t TS_CCALL tsCanvasText_equalPtr(const TSCanvasText self, const TSCanvasText ptr);
TS_CAPI TSCanvasText TS_CCALL tsCanvasText_copyPtr(const TSCanvasText self);
TS_CAPI TSCanvasText TS_CCALL tsCanvasText_clonePtr(const TSCanvasText self);
TS_CAPI void TS_CCALL tsCanvasText_clearPtr(TSCanvasText self);
TS_CAPI void TS_CCALL tsCanvasText_destroyPtr(TSCanvasText self);
TS_CAPI void TS_CCALL tsCanvasText_acquirePtr(TSCanvasText self);
TS_CAPI void TS_CCALL tsCanvasText_unacquirePtr(TSCanvasText self);
TS_CAPI bool_t TS_CCALL tsCanvasText_isValidPtr(const TSCanvasText self);
TS_CAPI bool_t TS_CCALL tsCanvasText_isOwnerPtr(const TSCanvasText self);
TS_CAPI bool_t TS_CCALL tsCanvasText_isConstPtr(const TSCanvasText self);
TS_CAPI uint32_t TS_CCALL tsCanvasText_getCountPtr(const TSCanvasText self);
TS_CAPI const void* TS_CCALL tsCanvasText_getInternalPtr(const TSCanvasText self);
TS_CAPI bool_t TS_CCALL tsCanvasText_equalCanvasElementPtr(const TSCanvasText self, const TSCanvasElement base);
TS_CAPI TSCanvasText TS_CCALL tsCanvasText_castCanvasElementPtr(TSCanvasElement base);
TS_CAPI TSCanvasElement TS_CCALL tsCanvasText_baseCanvasElementPtr(TSCanvasText self);
TS_CAPI void TS_CCALL tsCanvasText_setFontName_s(TSCanvasText self, const char *name);
TS_CAPI void TS_CCALL tsCanvasText_setFontName_cS(TSCanvasText self, const TSString name);
TS_CAPI TSString TS_CCALL tsCanvasText_getFontName(TSCanvasText self);
TS_CAPI void TS_CCALL tsCanvasText_setFontColor(TSCanvasText self, const TSColor *color);
TS_CAPI TSColor TS_CCALL tsCanvasText_getFontColor(TSCanvasText self);
TS_CAPI bool_t TS_CCALL tsCanvasText_setFontSize(TSCanvasText self, uint32_t scale);
TS_CAPI uint32_t TS_CCALL tsCanvasText_getFontSize(TSCanvasText self);
TS_CAPI bool_t TS_CCALL tsCanvasText_setFontScale(TSCanvasText self, uint32_t scale);
TS_CAPI uint32_t TS_CCALL tsCanvasText_getFontScale(TSCanvasText self);
TS_CAPI bool_t TS_CCALL tsCanvasText_setFontStyle(TSCanvasText self, const TSFontStyle *style);
TS_CAPI TSFontStyle TS_CCALL tsCanvasText_getFontStyleConst(TSCanvasText self);
TS_CAPI TSFontStyle TS_CCALL tsCanvasText_getFontStyle_c(TSCanvasText self);
TS_CAPI TSFontStyle TS_CCALL tsCanvasText_getFontStyle(TSCanvasText self);
TS_CAPI void TS_CCALL tsCanvasText_setPosition_cV3(TSCanvasText self, const TSVector3f *position);
TS_CAPI void TS_CCALL tsCanvasText_setPosition_fff(TSCanvasText self, float32_t x, float32_t y, float32_t z);
TS_CAPI TSVector3f TS_CCALL tsCanvasText_getPosition(TSCanvasText self);
TS_CAPI void TS_CCALL tsCanvasText_setText_s(TSCanvasText self, const char *text);
TS_CAPI void TS_CCALL tsCanvasText_setText_cS(TSCanvasText self, const TSString text);
TS_CAPI TSString TS_CCALL tsCanvasText_getText(TSCanvasText self);
TS_CAPI void TS_CCALL tsCanvasText_clearBatches(TSCanvasText self);
TS_CAPI void TS_CCALL tsCanvasText_setBatches_cFBu(TSCanvasText self, const TSFontBatch *batches, uint32_t num_batches);

/// Tellusim::CanvasMesh
TS_CAPI TSCanvasMesh TS_CCALL tsCanvasMesh_new(void);
TS_CAPI TSCanvasMesh TS_CCALL tsCanvasMesh_new_C(TSCanvas canvas);
TS_CAPI TSCanvasMesh TS_CCALL tsCanvasMesh_new_CCEM(TSCanvas canvas, TS_CanvasElementMode mode);
TS_CAPI void TS_CCALL tsCanvasMesh_delete(TSCanvasMesh self);
TS_CAPI bool_t TS_CCALL tsCanvasMesh_equalPtr(const TSCanvasMesh self, const TSCanvasMesh ptr);
TS_CAPI TSCanvasMesh TS_CCALL tsCanvasMesh_copyPtr(const TSCanvasMesh self);
TS_CAPI TSCanvasMesh TS_CCALL tsCanvasMesh_clonePtr(const TSCanvasMesh self);
TS_CAPI void TS_CCALL tsCanvasMesh_clearPtr(TSCanvasMesh self);
TS_CAPI void TS_CCALL tsCanvasMesh_destroyPtr(TSCanvasMesh self);
TS_CAPI void TS_CCALL tsCanvasMesh_acquirePtr(TSCanvasMesh self);
TS_CAPI void TS_CCALL tsCanvasMesh_unacquirePtr(TSCanvasMesh self);
TS_CAPI bool_t TS_CCALL tsCanvasMesh_isValidPtr(const TSCanvasMesh self);
TS_CAPI bool_t TS_CCALL tsCanvasMesh_isOwnerPtr(const TSCanvasMesh self);
TS_CAPI bool_t TS_CCALL tsCanvasMesh_isConstPtr(const TSCanvasMesh self);
TS_CAPI uint32_t TS_CCALL tsCanvasMesh_getCountPtr(const TSCanvasMesh self);
TS_CAPI const void* TS_CCALL tsCanvasMesh_getInternalPtr(const TSCanvasMesh self);
TS_CAPI bool_t TS_CCALL tsCanvasMesh_equalCanvasElementPtr(const TSCanvasMesh self, const TSCanvasElement base);
TS_CAPI TSCanvasMesh TS_CCALL tsCanvasMesh_castCanvasElementPtr(TSCanvasElement base);
TS_CAPI TSCanvasElement TS_CCALL tsCanvasMesh_baseCanvasElementPtr(TSCanvasMesh self);
TS_CAPI void TS_CCALL tsCanvasMesh_setTextureName_s(TSCanvasMesh self, const char *name);
TS_CAPI void TS_CCALL tsCanvasMesh_setTextureName_cS(TSCanvasMesh self, const TSString name);
TS_CAPI TSString TS_CCALL tsCanvasMesh_getTextureName(TSCanvasMesh self);
TS_CAPI void TS_CCALL tsCanvasMesh_setGradientStyle(TSCanvasMesh self, const TSGradientStyle *style);
TS_CAPI TSGradientStyle TS_CCALL tsCanvasMesh_getGradientStyleConst(TSCanvasMesh self);
TS_CAPI TSGradientStyle TS_CCALL tsCanvasMesh_getGradientStyle_c(TSCanvasMesh self);
TS_CAPI TSGradientStyle TS_CCALL tsCanvasMesh_getGradientStyle(TSCanvasMesh self);
TS_CAPI void TS_CCALL tsCanvasMesh_clearVertices(TSCanvasMesh self);
TS_CAPI void TS_CCALL tsCanvasMesh_setNumVertices(TSCanvasMesh self, uint32_t num_vertices);
TS_CAPI void TS_CCALL tsCanvasMesh_reserveVertices(TSCanvasMesh self, uint32_t num_vertices);
TS_CAPI uint32_t TS_CCALL tsCanvasMesh_getNumVertices(TSCanvasMesh self);
TS_CAPI void TS_CCALL tsCanvasMesh_setVertices(TSCanvasMesh self, const TSCanvasVertex *vertices, uint32_t num_vertices);
TS_CAPI void TS_CCALL tsCanvasMesh_addVertices(TSCanvasMesh self, const TSCanvasVertex *vertices, uint32_t num_vertices);
TS_CAPI TSCanvasVertex* TS_CCALL tsCanvasMesh_getVertices_c(TSCanvasMesh self);
TS_CAPI TSCanvasVertex* TS_CCALL tsCanvasMesh_getVertices(TSCanvasMesh self);
TS_CAPI void TS_CCALL tsCanvasMesh_setVertex(TSCanvasMesh self, uint32_t index, const TSCanvasVertex *vertex);
TS_CAPI TSCanvasVertex TS_CCALL tsCanvasMesh_getVertex_cu(TSCanvasMesh self, uint32_t index);
TS_CAPI TSCanvasVertex TS_CCALL tsCanvasMesh_getVertex_u(TSCanvasMesh self, uint32_t index);
TS_CAPI void TS_CCALL tsCanvasMesh_setVertexPosition_ucV3(TSCanvasMesh self, uint32_t index, const TSVector3f *position);
TS_CAPI void TS_CCALL tsCanvasMesh_setVertexPosition_ufff(TSCanvasMesh self, uint32_t index, float32_t x, float32_t y, float32_t z);
TS_CAPI TSVector3f TS_CCALL tsCanvasMesh_getVertexPosition(TSCanvasMesh self, uint32_t index);
TS_CAPI void TS_CCALL tsCanvasMesh_setVertexTexCoord_ucV2(TSCanvasMesh self, uint32_t index, const TSVector2f *texcoord);
TS_CAPI void TS_CCALL tsCanvasMesh_setVertexTexCoord_uff(TSCanvasMesh self, uint32_t index, float32_t s, float32_t t);
TS_CAPI TSVector2f TS_CCALL tsCanvasMesh_getVertexTexCoord(TSCanvasMesh self, uint32_t index);
TS_CAPI void TS_CCALL tsCanvasMesh_setVertexColor_ucC(TSCanvasMesh self, uint32_t index, const TSColor *color);
TS_CAPI void TS_CCALL tsCanvasMesh_setVertexColor_uu(TSCanvasMesh self, uint32_t index, uint32_t color);
TS_CAPI uint32_t TS_CCALL tsCanvasMesh_getVertexColor(TSCanvasMesh self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsCanvasMesh_addVertex_cV3(TSCanvasMesh self, const TSVector3f *position);
TS_CAPI uint32_t TS_CCALL tsCanvasMesh_addVertex_cV3u(TSCanvasMesh self, const TSVector3f *position, uint32_t color);
TS_CAPI uint32_t TS_CCALL tsCanvasMesh_addVertex_cV3cV2(TSCanvasMesh self, const TSVector3f *position, const TSVector2f *texcoord);
TS_CAPI uint32_t TS_CCALL tsCanvasMesh_addVertex_cV3cV2u(TSCanvasMesh self, const TSVector3f *position, const TSVector2f *texcoord, uint32_t color);
TS_CAPI uint32_t TS_CCALL tsCanvasMesh_addVertex_fffffu(TSCanvasMesh self, float32_t x, float32_t y, float32_t z, float32_t s, float32_t t, uint32_t color);
TS_CAPI uint32_t TS_CCALL tsCanvasMesh_addVertex_fffu(TSCanvasMesh self, float32_t x, float32_t y, float32_t z, uint32_t color);
TS_CAPI uint32_t TS_CCALL tsCanvasMesh_addVertex_ffu(TSCanvasMesh self, float32_t x, float32_t y, uint32_t color);
TS_CAPI void TS_CCALL tsCanvasMesh_clearIndices(TSCanvasMesh self);
TS_CAPI void TS_CCALL tsCanvasMesh_setNumIndices(TSCanvasMesh self, uint32_t num_indices);
TS_CAPI void TS_CCALL tsCanvasMesh_reserveIndices(TSCanvasMesh self, uint32_t num_indices);
TS_CAPI uint32_t TS_CCALL tsCanvasMesh_getNumIndices(TSCanvasMesh self);
TS_CAPI void TS_CCALL tsCanvasMesh_setIndices(TSCanvasMesh self, const uint32_t *indices, uint32_t num_indices);
TS_CAPI void TS_CCALL tsCanvasMesh_addIndices_upu(TSCanvasMesh self, const uint32_t *indices, uint32_t num_indices);
TS_CAPI const uint32_t* TS_CCALL tsCanvasMesh_getIndices_c(TSCanvasMesh self);
TS_CAPI uint32_t* TS_CCALL tsCanvasMesh_getIndices(TSCanvasMesh self);
TS_CAPI void TS_CCALL tsCanvasMesh_setIndex(TSCanvasMesh self, uint32_t index, uint32_t value);
TS_CAPI uint32_t TS_CCALL tsCanvasMesh_getIndex(TSCanvasMesh self, uint32_t index);
TS_CAPI void TS_CCALL tsCanvasMesh_addIndex(TSCanvasMesh self, uint32_t i0);
TS_CAPI void TS_CCALL tsCanvasMesh_addIndices_uu(TSCanvasMesh self, uint32_t i0, uint32_t i1);
TS_CAPI void TS_CCALL tsCanvasMesh_addIndices_uuu(TSCanvasMesh self, uint32_t i0, uint32_t i1, uint32_t i2);
TS_CAPI void TS_CCALL tsCanvasMesh_addIndices_uuuu(TSCanvasMesh self, uint32_t i0, uint32_t i1, uint32_t i2, uint32_t i3);
TS_CAPI void TS_CCALL tsCanvasMesh_setRect(TSCanvasMesh self, const TSRect *rect);

/// Tellusim::CanvasRect
TS_CAPI TSCanvasRect TS_CCALL tsCanvasRect_new(void);
TS_CAPI TSCanvasRect TS_CCALL tsCanvasRect_new_C(TSCanvas canvas);
TS_CAPI TSCanvasRect TS_CCALL tsCanvasRect_new_Cf(TSCanvas canvas, float32_t radius);
TS_CAPI TSCanvasRect TS_CCALL tsCanvasRect_new_CfcV2(TSCanvas canvas, float32_t radius, const TSVector2f *size);
TS_CAPI void TS_CCALL tsCanvasRect_delete(TSCanvasRect self);
TS_CAPI bool_t TS_CCALL tsCanvasRect_equalPtr(const TSCanvasRect self, const TSCanvasRect ptr);
TS_CAPI TSCanvasRect TS_CCALL tsCanvasRect_copyPtr(const TSCanvasRect self);
TS_CAPI TSCanvasRect TS_CCALL tsCanvasRect_clonePtr(const TSCanvasRect self);
TS_CAPI void TS_CCALL tsCanvasRect_clearPtr(TSCanvasRect self);
TS_CAPI void TS_CCALL tsCanvasRect_destroyPtr(TSCanvasRect self);
TS_CAPI void TS_CCALL tsCanvasRect_acquirePtr(TSCanvasRect self);
TS_CAPI void TS_CCALL tsCanvasRect_unacquirePtr(TSCanvasRect self);
TS_CAPI bool_t TS_CCALL tsCanvasRect_isValidPtr(const TSCanvasRect self);
TS_CAPI bool_t TS_CCALL tsCanvasRect_isOwnerPtr(const TSCanvasRect self);
TS_CAPI bool_t TS_CCALL tsCanvasRect_isConstPtr(const TSCanvasRect self);
TS_CAPI uint32_t TS_CCALL tsCanvasRect_getCountPtr(const TSCanvasRect self);
TS_CAPI const void* TS_CCALL tsCanvasRect_getInternalPtr(const TSCanvasRect self);
TS_CAPI bool_t TS_CCALL tsCanvasRect_equalCanvasElementPtr(const TSCanvasRect self, const TSCanvasElement base);
TS_CAPI TSCanvasRect TS_CCALL tsCanvasRect_castCanvasElementPtr(TSCanvasElement base);
TS_CAPI TSCanvasElement TS_CCALL tsCanvasRect_baseCanvasElementPtr(TSCanvasRect self);
TS_CAPI void TS_CCALL tsCanvasRect_setRadius(TSCanvasRect self, float32_t radius);
TS_CAPI float32_t TS_CCALL tsCanvasRect_getRadius(TSCanvasRect self);
TS_CAPI void TS_CCALL tsCanvasRect_setTextureName_s(TSCanvasRect self, const char *name);
TS_CAPI void TS_CCALL tsCanvasRect_setTextureName_cS(TSCanvasRect self, const TSString name);
TS_CAPI TSString TS_CCALL tsCanvasRect_getTextureName(TSCanvasRect self);
TS_CAPI void TS_CCALL tsCanvasRect_setStrokeColor(TSCanvasRect self, const TSColor *color);
TS_CAPI TSColor TS_CCALL tsCanvasRect_getStrokeColor(TSCanvasRect self);
TS_CAPI void TS_CCALL tsCanvasRect_setStrokeStyle(TSCanvasRect self, const TSStrokeStyle *style);
TS_CAPI TSStrokeStyle TS_CCALL tsCanvasRect_getStrokeStyleConst(TSCanvasRect self);
TS_CAPI TSStrokeStyle TS_CCALL tsCanvasRect_getStrokeStyle_c(TSCanvasRect self);
TS_CAPI TSStrokeStyle TS_CCALL tsCanvasRect_getStrokeStyle(TSCanvasRect self);
TS_CAPI void TS_CCALL tsCanvasRect_setGradientStyle(TSCanvasRect self, const TSGradientStyle *style);
TS_CAPI TSGradientStyle TS_CCALL tsCanvasRect_getGradientStyleConst(TSCanvasRect self);
TS_CAPI TSGradientStyle TS_CCALL tsCanvasRect_getGradientStyle_c(TSCanvasRect self);
TS_CAPI TSGradientStyle TS_CCALL tsCanvasRect_getGradientStyle(TSCanvasRect self);
TS_CAPI void TS_CCALL tsCanvasRect_setSize_cV2(TSCanvasRect self, const TSVector2f *size);
TS_CAPI void TS_CCALL tsCanvasRect_setSize_ff(TSCanvasRect self, float32_t width, float32_t height);
TS_CAPI TSVector2f TS_CCALL tsCanvasRect_getSize(TSCanvasRect self);
TS_CAPI float32_t TS_CCALL tsCanvasRect_getWidth(TSCanvasRect self);
TS_CAPI float32_t TS_CCALL tsCanvasRect_getHeight(TSCanvasRect self);
TS_CAPI void TS_CCALL tsCanvasRect_setPosition_cV3(TSCanvasRect self, const TSVector3f *position);
TS_CAPI void TS_CCALL tsCanvasRect_setPosition_fff(TSCanvasRect self, float32_t x, float32_t y, float32_t z);
TS_CAPI TSVector3f TS_CCALL tsCanvasRect_getPosition(TSCanvasRect self);
TS_CAPI void TS_CCALL tsCanvasRect_setTexCoord_cR(TSCanvasRect self, const TSRect *texcoord);
TS_CAPI void TS_CCALL tsCanvasRect_setTexCoord_ffff(TSCanvasRect self, float32_t left, float32_t right, float32_t bottom, float32_t top);
TS_CAPI TSRect TS_CCALL tsCanvasRect_getTexCoord(TSCanvasRect self);

/// Tellusim::CanvasTriangle
TS_CAPI TSCanvasTriangle TS_CCALL tsCanvasTriangle_new(void);
TS_CAPI TSCanvasTriangle TS_CCALL tsCanvasTriangle_new_C(TSCanvas canvas);
TS_CAPI TSCanvasTriangle TS_CCALL tsCanvasTriangle_new_Cf(TSCanvas canvas, float32_t radius);
TS_CAPI void TS_CCALL tsCanvasTriangle_delete(TSCanvasTriangle self);
TS_CAPI bool_t TS_CCALL tsCanvasTriangle_equalPtr(const TSCanvasTriangle self, const TSCanvasTriangle ptr);
TS_CAPI TSCanvasTriangle TS_CCALL tsCanvasTriangle_copyPtr(const TSCanvasTriangle self);
TS_CAPI TSCanvasTriangle TS_CCALL tsCanvasTriangle_clonePtr(const TSCanvasTriangle self);
TS_CAPI void TS_CCALL tsCanvasTriangle_clearPtr(TSCanvasTriangle self);
TS_CAPI void TS_CCALL tsCanvasTriangle_destroyPtr(TSCanvasTriangle self);
TS_CAPI void TS_CCALL tsCanvasTriangle_acquirePtr(TSCanvasTriangle self);
TS_CAPI void TS_CCALL tsCanvasTriangle_unacquirePtr(TSCanvasTriangle self);
TS_CAPI bool_t TS_CCALL tsCanvasTriangle_isValidPtr(const TSCanvasTriangle self);
TS_CAPI bool_t TS_CCALL tsCanvasTriangle_isOwnerPtr(const TSCanvasTriangle self);
TS_CAPI bool_t TS_CCALL tsCanvasTriangle_isConstPtr(const TSCanvasTriangle self);
TS_CAPI uint32_t TS_CCALL tsCanvasTriangle_getCountPtr(const TSCanvasTriangle self);
TS_CAPI const void* TS_CCALL tsCanvasTriangle_getInternalPtr(const TSCanvasTriangle self);
TS_CAPI bool_t TS_CCALL tsCanvasTriangle_equalCanvasElementPtr(const TSCanvasTriangle self, const TSCanvasElement base);
TS_CAPI TSCanvasTriangle TS_CCALL tsCanvasTriangle_castCanvasElementPtr(TSCanvasElement base);
TS_CAPI TSCanvasElement TS_CCALL tsCanvasTriangle_baseCanvasElementPtr(TSCanvasTriangle self);
TS_CAPI void TS_CCALL tsCanvasTriangle_setRadius(TSCanvasTriangle self, float32_t radius);
TS_CAPI float32_t TS_CCALL tsCanvasTriangle_getRadius(TSCanvasTriangle self);
TS_CAPI void TS_CCALL tsCanvasTriangle_setStrokeColor(TSCanvasTriangle self, const TSColor *color);
TS_CAPI TSColor TS_CCALL tsCanvasTriangle_getStrokeColor(TSCanvasTriangle self);
TS_CAPI void TS_CCALL tsCanvasTriangle_setStrokeStyle(TSCanvasTriangle self, const TSStrokeStyle *style);
TS_CAPI TSStrokeStyle TS_CCALL tsCanvasTriangle_getStrokeStyleConst(TSCanvasTriangle self);
TS_CAPI TSStrokeStyle TS_CCALL tsCanvasTriangle_getStrokeStyle_c(TSCanvasTriangle self);
TS_CAPI TSStrokeStyle TS_CCALL tsCanvasTriangle_getStrokeStyle(TSCanvasTriangle self);
TS_CAPI void TS_CCALL tsCanvasTriangle_setGradientStyle(TSCanvasTriangle self, const TSGradientStyle *style);
TS_CAPI TSGradientStyle TS_CCALL tsCanvasTriangle_getGradientStyleConst(TSCanvasTriangle self);
TS_CAPI TSGradientStyle TS_CCALL tsCanvasTriangle_getGradientStyle_c(TSCanvasTriangle self);
TS_CAPI TSGradientStyle TS_CCALL tsCanvasTriangle_getGradientStyle(TSCanvasTriangle self);
TS_CAPI void TS_CCALL tsCanvasTriangle_setPosition0_cV3(TSCanvasTriangle self, const TSVector3f *position);
TS_CAPI void TS_CCALL tsCanvasTriangle_setPosition1_cV3(TSCanvasTriangle self, const TSVector3f *position);
TS_CAPI void TS_CCALL tsCanvasTriangle_setPosition2_cV3(TSCanvasTriangle self, const TSVector3f *position);
TS_CAPI void TS_CCALL tsCanvasTriangle_setPosition0_fff(TSCanvasTriangle self, float32_t x, float32_t y, float32_t z);
TS_CAPI void TS_CCALL tsCanvasTriangle_setPosition1_fff(TSCanvasTriangle self, float32_t x, float32_t y, float32_t z);
TS_CAPI void TS_CCALL tsCanvasTriangle_setPosition2_fff(TSCanvasTriangle self, float32_t x, float32_t y, float32_t z);
TS_CAPI void TS_CCALL tsCanvasTriangle_setPosition(TSCanvasTriangle self, const TSVector3f *position_0, const TSVector3f *position_1, const TSVector3f *position_2);
TS_CAPI TSVector3f TS_CCALL tsCanvasTriangle_getPosition0(TSCanvasTriangle self);
TS_CAPI TSVector3f TS_CCALL tsCanvasTriangle_getPosition1(TSCanvasTriangle self);
TS_CAPI TSVector3f TS_CCALL tsCanvasTriangle_getPosition2(TSCanvasTriangle self);

/// Tellusim::CanvasEllipse
TS_CAPI TSCanvasEllipse TS_CCALL tsCanvasEllipse_new(void);
TS_CAPI TSCanvasEllipse TS_CCALL tsCanvasEllipse_new_C(TSCanvas canvas);
TS_CAPI TSCanvasEllipse TS_CCALL tsCanvasEllipse_new_Cf(TSCanvas canvas, float32_t radius);
TS_CAPI void TS_CCALL tsCanvasEllipse_delete(TSCanvasEllipse self);
TS_CAPI bool_t TS_CCALL tsCanvasEllipse_equalPtr(const TSCanvasEllipse self, const TSCanvasEllipse ptr);
TS_CAPI TSCanvasEllipse TS_CCALL tsCanvasEllipse_copyPtr(const TSCanvasEllipse self);
TS_CAPI TSCanvasEllipse TS_CCALL tsCanvasEllipse_clonePtr(const TSCanvasEllipse self);
TS_CAPI void TS_CCALL tsCanvasEllipse_clearPtr(TSCanvasEllipse self);
TS_CAPI void TS_CCALL tsCanvasEllipse_destroyPtr(TSCanvasEllipse self);
TS_CAPI void TS_CCALL tsCanvasEllipse_acquirePtr(TSCanvasEllipse self);
TS_CAPI void TS_CCALL tsCanvasEllipse_unacquirePtr(TSCanvasEllipse self);
TS_CAPI bool_t TS_CCALL tsCanvasEllipse_isValidPtr(const TSCanvasEllipse self);
TS_CAPI bool_t TS_CCALL tsCanvasEllipse_isOwnerPtr(const TSCanvasEllipse self);
TS_CAPI bool_t TS_CCALL tsCanvasEllipse_isConstPtr(const TSCanvasEllipse self);
TS_CAPI uint32_t TS_CCALL tsCanvasEllipse_getCountPtr(const TSCanvasEllipse self);
TS_CAPI const void* TS_CCALL tsCanvasEllipse_getInternalPtr(const TSCanvasEllipse self);
TS_CAPI bool_t TS_CCALL tsCanvasEllipse_equalCanvasElementPtr(const TSCanvasEllipse self, const TSCanvasElement base);
TS_CAPI TSCanvasEllipse TS_CCALL tsCanvasEllipse_castCanvasElementPtr(TSCanvasElement base);
TS_CAPI TSCanvasElement TS_CCALL tsCanvasEllipse_baseCanvasElementPtr(TSCanvasEllipse self);
TS_CAPI void TS_CCALL tsCanvasEllipse_setRadius(TSCanvasEllipse self, float32_t radius);
TS_CAPI float32_t TS_CCALL tsCanvasEllipse_getRadius(TSCanvasEllipse self);
TS_CAPI void TS_CCALL tsCanvasEllipse_setTextureName_s(TSCanvasEllipse self, const char *name);
TS_CAPI void TS_CCALL tsCanvasEllipse_setTextureName_cS(TSCanvasEllipse self, const TSString name);
TS_CAPI TSString TS_CCALL tsCanvasEllipse_getTextureName(TSCanvasEllipse self);
TS_CAPI void TS_CCALL tsCanvasEllipse_setStrokeColor(TSCanvasEllipse self, const TSColor *color);
TS_CAPI TSColor TS_CCALL tsCanvasEllipse_getStrokeColor(TSCanvasEllipse self);
TS_CAPI void TS_CCALL tsCanvasEllipse_setStrokeStyle(TSCanvasEllipse self, const TSStrokeStyle *style);
TS_CAPI TSStrokeStyle TS_CCALL tsCanvasEllipse_getStrokeStyleConst(TSCanvasEllipse self);
TS_CAPI TSStrokeStyle TS_CCALL tsCanvasEllipse_getStrokeStyle_c(TSCanvasEllipse self);
TS_CAPI TSStrokeStyle TS_CCALL tsCanvasEllipse_getStrokeStyle(TSCanvasEllipse self);
TS_CAPI void TS_CCALL tsCanvasEllipse_setGradientStyle(TSCanvasEllipse self, const TSGradientStyle *style);
TS_CAPI TSGradientStyle TS_CCALL tsCanvasEllipse_getGradientStyleConst(TSCanvasEllipse self);
TS_CAPI TSGradientStyle TS_CCALL tsCanvasEllipse_getGradientStyle_c(TSCanvasEllipse self);
TS_CAPI TSGradientStyle TS_CCALL tsCanvasEllipse_getGradientStyle(TSCanvasEllipse self);
TS_CAPI void TS_CCALL tsCanvasEllipse_setPosition_cV3(TSCanvasEllipse self, const TSVector3f *position);
TS_CAPI void TS_CCALL tsCanvasEllipse_setPosition0_cV3(TSCanvasEllipse self, const TSVector3f *position);
TS_CAPI void TS_CCALL tsCanvasEllipse_setPosition1_cV3(TSCanvasEllipse self, const TSVector3f *position);
TS_CAPI void TS_CCALL tsCanvasEllipse_setPosition_fff(TSCanvasEllipse self, float32_t x, float32_t y, float32_t z);
TS_CAPI void TS_CCALL tsCanvasEllipse_setPosition0_fff(TSCanvasEllipse self, float32_t x, float32_t y, float32_t z);
TS_CAPI void TS_CCALL tsCanvasEllipse_setPosition1_fff(TSCanvasEllipse self, float32_t x, float32_t y, float32_t z);
TS_CAPI void TS_CCALL tsCanvasEllipse_setPosition_cV3cV3(TSCanvasEllipse self, const TSVector3f *position_0, const TSVector3f *position_1);
TS_CAPI TSVector3f TS_CCALL tsCanvasEllipse_getPosition0(TSCanvasEllipse self);
TS_CAPI TSVector3f TS_CCALL tsCanvasEllipse_getPosition1(TSCanvasEllipse self);
TS_CAPI void TS_CCALL tsCanvasEllipse_setTexCoord_cR(TSCanvasEllipse self, const TSRect *texcoord);
TS_CAPI void TS_CCALL tsCanvasEllipse_setTexCoord_ffff(TSCanvasEllipse self, float32_t left, float32_t right, float32_t bottom, float32_t top);
TS_CAPI TSRect TS_CCALL tsCanvasEllipse_getTexCoord(TSCanvasEllipse self);

/// Tellusim::CanvasShape
TS_CAPI TSCanvasShape TS_CCALL tsCanvasShape_new(void);
TS_CAPI TSCanvasShape TS_CCALL tsCanvasShape_new_C(TSCanvas canvas);
TS_CAPI TSCanvasShape TS_CCALL tsCanvasShape_new_Cb(TSCanvas canvas, bool_t cubic);
TS_CAPI void TS_CCALL tsCanvasShape_delete(TSCanvasShape self);
TS_CAPI bool_t TS_CCALL tsCanvasShape_equalPtr(const TSCanvasShape self, const TSCanvasShape ptr);
TS_CAPI TSCanvasShape TS_CCALL tsCanvasShape_copyPtr(const TSCanvasShape self);
TS_CAPI TSCanvasShape TS_CCALL tsCanvasShape_clonePtr(const TSCanvasShape self);
TS_CAPI void TS_CCALL tsCanvasShape_clearPtr(TSCanvasShape self);
TS_CAPI void TS_CCALL tsCanvasShape_destroyPtr(TSCanvasShape self);
TS_CAPI void TS_CCALL tsCanvasShape_acquirePtr(TSCanvasShape self);
TS_CAPI void TS_CCALL tsCanvasShape_unacquirePtr(TSCanvasShape self);
TS_CAPI bool_t TS_CCALL tsCanvasShape_isValidPtr(const TSCanvasShape self);
TS_CAPI bool_t TS_CCALL tsCanvasShape_isOwnerPtr(const TSCanvasShape self);
TS_CAPI bool_t TS_CCALL tsCanvasShape_isConstPtr(const TSCanvasShape self);
TS_CAPI uint32_t TS_CCALL tsCanvasShape_getCountPtr(const TSCanvasShape self);
TS_CAPI const void* TS_CCALL tsCanvasShape_getInternalPtr(const TSCanvasShape self);
TS_CAPI bool_t TS_CCALL tsCanvasShape_equalCanvasElementPtr(const TSCanvasShape self, const TSCanvasElement base);
TS_CAPI TSCanvasShape TS_CCALL tsCanvasShape_castCanvasElementPtr(TSCanvasElement base);
TS_CAPI TSCanvasElement TS_CCALL tsCanvasShape_baseCanvasElementPtr(TSCanvasShape self);
TS_CAPI void TS_CCALL tsCanvasShape_setCubic(TSCanvasShape self, bool_t cubic);
TS_CAPI bool_t TS_CCALL tsCanvasShape_isCubic(TSCanvasShape self);
TS_CAPI void TS_CCALL tsCanvasShape_setThreshold(TSCanvasShape self, float32_t threshold);
TS_CAPI float32_t TS_CCALL tsCanvasShape_getThreshold(TSCanvasShape self);
TS_CAPI void TS_CCALL tsCanvasShape_setStrokeColor(TSCanvasShape self, const TSColor *color);
TS_CAPI TSColor TS_CCALL tsCanvasShape_getStrokeColor(TSCanvasShape self);
TS_CAPI void TS_CCALL tsCanvasShape_setStrokeStyle(TSCanvasShape self, const TSStrokeStyle *style);
TS_CAPI TSStrokeStyle TS_CCALL tsCanvasShape_getStrokeStyleConst(TSCanvasShape self);
TS_CAPI TSStrokeStyle TS_CCALL tsCanvasShape_getStrokeStyle_c(TSCanvasShape self);
TS_CAPI TSStrokeStyle TS_CCALL tsCanvasShape_getStrokeStyle(TSCanvasShape self);
TS_CAPI void TS_CCALL tsCanvasShape_setGradientStyle(TSCanvasShape self, const TSGradientStyle *style);
TS_CAPI TSGradientStyle TS_CCALL tsCanvasShape_getGradientStyleConst(TSCanvasShape self);
TS_CAPI TSGradientStyle TS_CCALL tsCanvasShape_getGradientStyle_c(TSCanvasShape self);
TS_CAPI TSGradientStyle TS_CCALL tsCanvasShape_getGradientStyle(TSCanvasShape self);
TS_CAPI bool_t TS_CCALL tsCanvasShape_createSVG(TSCanvasShape self, const char *src, float32_t scale);
TS_CAPI void TS_CCALL tsCanvasShape_clearPositions(TSCanvasShape self);
TS_CAPI void TS_CCALL tsCanvasShape_setNumPositions(TSCanvasShape self, uint32_t num_positions);
TS_CAPI void TS_CCALL tsCanvasShape_reservePositions(TSCanvasShape self, uint32_t num_positions);
TS_CAPI uint32_t TS_CCALL tsCanvasShape_getNumPositions(TSCanvasShape self);
TS_CAPI void TS_CCALL tsCanvasShape_setPositions(TSCanvasShape self, const TSVector3f *positions, uint32_t num_positions);
TS_CAPI void TS_CCALL tsCanvasShape_addPositions(TSCanvasShape self, const TSVector3f *positions, uint32_t num_positions);
TS_CAPI TSVector3f* TS_CCALL tsCanvasShape_getPositions_c(TSCanvasShape self);
TS_CAPI TSVector3f* TS_CCALL tsCanvasShape_getPositions(TSCanvasShape self);
TS_CAPI void TS_CCALL tsCanvasShape_setPosition_ucV3(TSCanvasShape self, uint32_t index, const TSVector3f *position);
TS_CAPI void TS_CCALL tsCanvasShape_setPosition_ufff(TSCanvasShape self, uint32_t index, float32_t x, float32_t y, float32_t z);
TS_CAPI TSVector3f TS_CCALL tsCanvasShape_getPosition_cu(TSCanvasShape self, uint32_t index);
TS_CAPI TSVector3f TS_CCALL tsCanvasShape_getPosition_u(TSCanvasShape self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsCanvasShape_addPosition_cV2(TSCanvasShape self, const TSVector2f *position);
TS_CAPI uint32_t TS_CCALL tsCanvasShape_addPosition_cV3(TSCanvasShape self, const TSVector3f *position);
TS_CAPI uint32_t TS_CCALL tsCanvasShape_addPosition_fff(TSCanvasShape self, float32_t x, float32_t y, float32_t z);
TS_CAPI void TS_CCALL tsCanvasShape_setTexCoord_cR(TSCanvasShape self, const TSRect *texcoord);
TS_CAPI void TS_CCALL tsCanvasShape_setTexCoord_ffff(TSCanvasShape self, float32_t left, float32_t right, float32_t bottom, float32_t top);
TS_CAPI TSRect TS_CCALL tsCanvasShape_getTexCoord(TSCanvasShape self);

/// Tellusim::CanvasStrip
TS_CAPI TSCanvasStrip TS_CCALL tsCanvasStrip_new(void);
TS_CAPI TSCanvasStrip TS_CCALL tsCanvasStrip_new_C(TSCanvas canvas);
TS_CAPI TSCanvasStrip TS_CCALL tsCanvasStrip_new_Cf(TSCanvas canvas, float32_t width);
TS_CAPI void TS_CCALL tsCanvasStrip_delete(TSCanvasStrip self);
TS_CAPI bool_t TS_CCALL tsCanvasStrip_equalPtr(const TSCanvasStrip self, const TSCanvasStrip ptr);
TS_CAPI TSCanvasStrip TS_CCALL tsCanvasStrip_copyPtr(const TSCanvasStrip self);
TS_CAPI TSCanvasStrip TS_CCALL tsCanvasStrip_clonePtr(const TSCanvasStrip self);
TS_CAPI void TS_CCALL tsCanvasStrip_clearPtr(TSCanvasStrip self);
TS_CAPI void TS_CCALL tsCanvasStrip_destroyPtr(TSCanvasStrip self);
TS_CAPI void TS_CCALL tsCanvasStrip_acquirePtr(TSCanvasStrip self);
TS_CAPI void TS_CCALL tsCanvasStrip_unacquirePtr(TSCanvasStrip self);
TS_CAPI bool_t TS_CCALL tsCanvasStrip_isValidPtr(const TSCanvasStrip self);
TS_CAPI bool_t TS_CCALL tsCanvasStrip_isOwnerPtr(const TSCanvasStrip self);
TS_CAPI bool_t TS_CCALL tsCanvasStrip_isConstPtr(const TSCanvasStrip self);
TS_CAPI uint32_t TS_CCALL tsCanvasStrip_getCountPtr(const TSCanvasStrip self);
TS_CAPI const void* TS_CCALL tsCanvasStrip_getInternalPtr(const TSCanvasStrip self);
TS_CAPI bool_t TS_CCALL tsCanvasStrip_equalCanvasElementPtr(const TSCanvasStrip self, const TSCanvasElement base);
TS_CAPI TSCanvasStrip TS_CCALL tsCanvasStrip_castCanvasElementPtr(TSCanvasElement base);
TS_CAPI TSCanvasElement TS_CCALL tsCanvasStrip_baseCanvasElementPtr(TSCanvasStrip self);
TS_CAPI void TS_CCALL tsCanvasStrip_setWidth(TSCanvasStrip self, float32_t width);
TS_CAPI float32_t TS_CCALL tsCanvasStrip_getWidth(TSCanvasStrip self);
TS_CAPI void TS_CCALL tsCanvasStrip_setOffset(TSCanvasStrip self, float32_t offset);
TS_CAPI float32_t TS_CCALL tsCanvasStrip_getOffset(TSCanvasStrip self);
TS_CAPI void TS_CCALL tsCanvasStrip_setStrokeColor(TSCanvasStrip self, const TSColor *color);
TS_CAPI TSColor TS_CCALL tsCanvasStrip_getStrokeColor(TSCanvasStrip self);
TS_CAPI void TS_CCALL tsCanvasStrip_setStrokeStyle(TSCanvasStrip self, const TSStrokeStyle *style);
TS_CAPI TSStrokeStyle TS_CCALL tsCanvasStrip_getStrokeStyleConst(TSCanvasStrip self);
TS_CAPI TSStrokeStyle TS_CCALL tsCanvasStrip_getStrokeStyle_c(TSCanvasStrip self);
TS_CAPI TSStrokeStyle TS_CCALL tsCanvasStrip_getStrokeStyle(TSCanvasStrip self);
TS_CAPI void TS_CCALL tsCanvasStrip_createQuadratic_cV2cV2cV2f(TSCanvasStrip self, const TSVector2f *p0, const TSVector2f *p1, const TSVector2f *p2, float32_t threshold);
TS_CAPI void TS_CCALL tsCanvasStrip_createQuadratic_cV3cV3cV3f(TSCanvasStrip self, const TSVector3f *p0, const TSVector3f *p1, const TSVector3f *p2, float32_t threshold);
TS_CAPI void TS_CCALL tsCanvasStrip_createCubic_cV2cV2cV2cV2f(TSCanvasStrip self, const TSVector2f *p0, const TSVector2f *p1, const TSVector2f *p2, const TSVector2f *p3, float32_t threshold);
TS_CAPI void TS_CCALL tsCanvasStrip_createCubic_cV3cV3cV3cV3f(TSCanvasStrip self, const TSVector3f *p0, const TSVector3f *p1, const TSVector3f *p2, const TSVector3f *p3, float32_t threshold);
TS_CAPI void TS_CCALL tsCanvasStrip_clearPositions(TSCanvasStrip self);
TS_CAPI void TS_CCALL tsCanvasStrip_setNumPositions(TSCanvasStrip self, uint32_t num_positions);
TS_CAPI void TS_CCALL tsCanvasStrip_reservePositions(TSCanvasStrip self, uint32_t num_positions);
TS_CAPI uint32_t TS_CCALL tsCanvasStrip_getNumPositions(TSCanvasStrip self);
TS_CAPI void TS_CCALL tsCanvasStrip_setPositions(TSCanvasStrip self, const TSVector3f *positions, uint32_t num_positions);
TS_CAPI void TS_CCALL tsCanvasStrip_addPositions(TSCanvasStrip self, const TSVector3f *positions, uint32_t num_positions);
TS_CAPI TSVector3f* TS_CCALL tsCanvasStrip_getPositions_c(TSCanvasStrip self);
TS_CAPI TSVector3f* TS_CCALL tsCanvasStrip_getPositions(TSCanvasStrip self);
TS_CAPI void TS_CCALL tsCanvasStrip_setPosition_ucV3(TSCanvasStrip self, uint32_t index, const TSVector3f *position);
TS_CAPI void TS_CCALL tsCanvasStrip_setPosition_ufff(TSCanvasStrip self, uint32_t index, float32_t x, float32_t y, float32_t z);
TS_CAPI TSVector3f TS_CCALL tsCanvasStrip_getPosition_cu(TSCanvasStrip self, uint32_t index);
TS_CAPI TSVector3f TS_CCALL tsCanvasStrip_getPosition_u(TSCanvasStrip self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsCanvasStrip_addPosition_cV2(TSCanvasStrip self, const TSVector2f *position);
TS_CAPI uint32_t TS_CCALL tsCanvasStrip_addPosition_cV3(TSCanvasStrip self, const TSVector3f *position);
TS_CAPI uint32_t TS_CCALL tsCanvasStrip_addPosition_fff(TSCanvasStrip self, float32_t x, float32_t y, float32_t z);

/// Tellusim::Canvas
typedef bool_t (*TSCanvasCreateCallback)(const TSDevice device, TSCanvas canvas, uint32_t scale, void *data_);
typedef bool_t (*TSCanvasPipelineCallback)(TSPipeline pipeline, TSCanvas canvas, TSCanvasElement element, void *data_);
typedef bool_t (*TSCanvasBeginCallback)(TSCommand command, TSCanvas canvas, void *data_);
typedef bool_t (*TSCanvasDrawCallback)(TSCommand command, TSCanvas canvas, void *data_);
TS_CAPI TSCanvas TS_CCALL tsCanvas_new(void);
TS_CAPI TSCanvas TS_CCALL tsCanvas_new_C(TSCanvas *parent);
TS_CAPI void TS_CCALL tsCanvas_delete(TSCanvas self);
TS_CAPI bool_t TS_CCALL tsCanvas_equalPtr(const TSCanvas self, const TSCanvas ptr);
TS_CAPI TSCanvas TS_CCALL tsCanvas_copyPtr(const TSCanvas self);
TS_CAPI TSCanvas TS_CCALL tsCanvas_clonePtr(const TSCanvas self);
TS_CAPI void TS_CCALL tsCanvas_clearPtr(TSCanvas self);
TS_CAPI void TS_CCALL tsCanvas_destroyPtr(TSCanvas self);
TS_CAPI void TS_CCALL tsCanvas_acquirePtr(TSCanvas self);
TS_CAPI void TS_CCALL tsCanvas_unacquirePtr(TSCanvas self);
TS_CAPI bool_t TS_CCALL tsCanvas_isValidPtr(const TSCanvas self);
TS_CAPI bool_t TS_CCALL tsCanvas_isOwnerPtr(const TSCanvas self);
TS_CAPI bool_t TS_CCALL tsCanvas_isConstPtr(const TSCanvas self);
TS_CAPI uint32_t TS_CCALL tsCanvas_getCountPtr(const TSCanvas self);
TS_CAPI const void* TS_CCALL tsCanvas_getInternalPtr(const TSCanvas self);
TS_CAPI void TS_CCALL tsCanvas_clear(TSCanvas self);
TS_CAPI bool_t TS_CCALL tsCanvas_isCreated(TSCanvas self);
TS_CAPI uint32_t TS_CCALL tsCanvas_getScale(TSCanvas self, const TSTarget target, uint32_t scale);
TS_CAPI bool_t TS_CCALL tsCanvas_create_cDFFuu(TSCanvas self, const TSDevice device, TS_Format color, TS_Format depth, uint32_t multisample, uint32_t scale);
TS_CAPI bool_t TS_CCALL tsCanvas_create_cDcTu(TSCanvas self, const TSDevice device, const TSTarget target, uint32_t scale);
TS_CAPI void TS_CCALL tsCanvas_setPipelineHash(TSCanvas self, uint32_t hash);
TS_CAPI uint32_t TS_CCALL tsCanvas_getPipelineHash(TSCanvas self);
TS_CAPI TS_Format TS_CCALL tsCanvas_getColorFormat(TSCanvas self);
TS_CAPI TS_Format TS_CCALL tsCanvas_getDepthFormat(TSCanvas self);
TS_CAPI uint32_t TS_CCALL tsCanvas_getMultisample(TSCanvas self);
TS_CAPI void TS_CCALL tsCanvas_setOrder(TSCanvas self, int32_t order);
TS_CAPI int32_t TS_CCALL tsCanvas_getOrder(TSCanvas self);
TS_CAPI void TS_CCALL tsCanvas_setEnabled(TSCanvas self, bool_t enabled);
TS_CAPI bool_t TS_CCALL tsCanvas_isEnabled(TSCanvas self);
TS_CAPI void TS_CCALL tsCanvas_setViewport_cV(TSCanvas self, const TSViewport *viewport);
TS_CAPI void TS_CCALL tsCanvas_setViewport_uu(TSCanvas self, uint32_t width, uint32_t height);
TS_CAPI void TS_CCALL tsCanvas_setViewport_ff(TSCanvas self, float32_t width, float32_t height);
TS_CAPI TSViewport TS_CCALL tsCanvas_getViewport(TSCanvas self);
TS_CAPI float32_t TS_CCALL tsCanvas_getWidth(TSCanvas self);
TS_CAPI float32_t TS_CCALL tsCanvas_getHeight(TSCanvas self);
TS_CAPI void TS_CCALL tsCanvas_clearColor(TSCanvas self);
TS_CAPI void TS_CCALL tsCanvas_setColor_cC(TSCanvas self, const TSColor *color);
TS_CAPI void TS_CCALL tsCanvas_setColor_ffff(TSCanvas self, float32_t r, float32_t g, float32_t b, float32_t a);
TS_CAPI TSColor TS_CCALL tsCanvas_getColor(TSCanvas self);
TS_CAPI void TS_CCALL tsCanvas_clearScissor(TSCanvas self);
TS_CAPI void TS_CCALL tsCanvas_setScissor(TSCanvas self, const TSRect *scissor);
TS_CAPI TSRect TS_CCALL tsCanvas_getScissor(TSCanvas self);
TS_CAPI void TS_CCALL tsCanvas_clearTransform(TSCanvas self);
TS_CAPI void TS_CCALL tsCanvas_setTransform(TSCanvas self, const TSMatrix4x4f *transform);
TS_CAPI TSMatrix4x4f TS_CCALL tsCanvas_getTransform(TSCanvas self);
TS_CAPI uint32_t TS_CCALL tsCanvas_setParent(TSCanvas self, TSCanvas parent);
TS_CAPI TSCanvas TS_CCALL tsCanvas_getParent_c(TSCanvas self);
TS_CAPI TSCanvas TS_CCALL tsCanvas_getParent(TSCanvas self);
TS_CAPI uint32_t TS_CCALL tsCanvas_addChild(TSCanvas self, TSCanvas child);
TS_CAPI bool_t TS_CCALL tsCanvas_removeChild(TSCanvas self, TSCanvas child);
TS_CAPI bool_t TS_CCALL tsCanvas_raiseChild(TSCanvas self, TSCanvas child, uint32_t index);
TS_CAPI bool_t TS_CCALL tsCanvas_lowerChild(TSCanvas self, TSCanvas child, uint32_t index);
TS_CAPI void TS_CCALL tsCanvas_releaseChildren(TSCanvas self);
TS_CAPI uint32_t TS_CCALL tsCanvas_findChild(TSCanvas self, const TSCanvas child);
TS_CAPI bool_t TS_CCALL tsCanvas_isChild(TSCanvas self, const TSCanvas child);
TS_CAPI uint32_t TS_CCALL tsCanvas_getNumChildren(TSCanvas self);
TS_CAPI TSCanvas TS_CCALL tsCanvas_getChild_cu(TSCanvas self, uint32_t index);
TS_CAPI TSCanvas TS_CCALL tsCanvas_getChild_u(TSCanvas self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsCanvas_addElement(TSCanvas self, TSCanvasElement element);
TS_CAPI bool_t TS_CCALL tsCanvas_removeElement(TSCanvas self, TSCanvasElement element);
TS_CAPI bool_t TS_CCALL tsCanvas_raiseElement(TSCanvas self, TSCanvasElement element, uint32_t index);
TS_CAPI bool_t TS_CCALL tsCanvas_lowerElement(TSCanvas self, TSCanvasElement element, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsCanvas_findElement(TSCanvas self, const TSCanvasElement element);
TS_CAPI bool_t TS_CCALL tsCanvas_isElement(TSCanvas self, const TSCanvasElement element);
TS_CAPI uint32_t TS_CCALL tsCanvas_getNumElements(TSCanvas self);
TS_CAPI TSCanvasElement TS_CCALL tsCanvas_getElement_cu(TSCanvas self, uint32_t index);
TS_CAPI TSCanvasElement TS_CCALL tsCanvas_getElement_u(TSCanvas self, uint32_t index);
TS_CAPI bool_t TS_CCALL tsCanvas_isFont(TSCanvas self, const char *name);
TS_CAPI bool_t TS_CCALL tsCanvas_addFont_sSt(TSCanvas self, const char *name, TSStream stream);
TS_CAPI bool_t TS_CCALL tsCanvas_addFont_sbl(TSCanvas self, const char *name, const uint8_t (*blob)[256]);
TS_CAPI void TS_CCALL tsCanvas_removeFont(TSCanvas self, const char *name);
TS_CAPI TSFont TS_CCALL tsCanvas_getFont(TSCanvas self, const char *name);
TS_CAPI bool_t TS_CCALL tsCanvas_isTexture(TSCanvas self, const char *name);
TS_CAPI bool_t TS_CCALL tsCanvas_addTexture_sSt(TSCanvas self, const char *name, TSStream stream);
TS_CAPI bool_t TS_CCALL tsCanvas_addTexture_sT(TSCanvas self, const char *name, TSTexture texture);
TS_CAPI bool_t TS_CCALL tsCanvas_addTexture_sbl(TSCanvas self, const char *name, const uint8_t (*blob)[256]);
TS_CAPI void TS_CCALL tsCanvas_removeTexture(TSCanvas self, const char *name);
TS_CAPI TSTexture TS_CCALL tsCanvas_getTexture(TSCanvas self, const char *name);
TS_CAPI void TS_CCALL tsCanvas_setDepthMask(TSCanvas self, TS_PipelineDepthMask mask);
TS_CAPI TS_PipelineDepthMask TS_CCALL tsCanvas_getDepthMask(TSCanvas self);
TS_CAPI void TS_CCALL tsCanvas_setDepthFunc(TSCanvas self, TS_PipelineDepthFunc func);
TS_CAPI TS_PipelineDepthFunc TS_CCALL tsCanvas_getDepthFunc(TSCanvas self);
TS_CAPI void TS_CCALL tsCanvas_draw_CcT(TSCanvas self, TSCommand command, const TSTarget target);
TS_CAPI void TS_CCALL tsCanvas_draw_C(TSCanvas self, TSCommand command);
TS_CAPI void TS_CCALL tsCanvas_setCreateCallback(TSCanvas self, const TSCanvasCreateCallback func, void *data_);
TS_CAPI void TS_CCALL tsCanvas_setPipelineCallback(TSCanvas self, const TSCanvasPipelineCallback func, void *data_);
TS_CAPI void TS_CCALL tsCanvas_setBeginCallback(TSCanvas self, const TSCanvasBeginCallback func, void *data_);
TS_CAPI void TS_CCALL tsCanvas_setDrawCallback(TSCanvas self, const TSCanvasDrawCallback func, void *data_);
TS_CAPI uint32_t TS_CCALL tsCanvas_getNumDrawPipelines(TSCanvas self);
TS_CAPI uint32_t TS_CCALL tsCanvas_getNumDrawElements(TSCanvas self);
TS_CAPI uint32_t TS_CCALL tsCanvas_getNumDrawCommands(TSCanvas self);
TS_CAPI TSRect TS_CCALL tsCanvas_getRect(TSCanvas self);

/// Tellusim::Control
TS_CAPI TSControl TS_CCALL tsControl_new(void);
TS_CAPI TSControl TS_CCALL tsControl_new_C(TSControl *parent);
TS_CAPI TSControl TS_CCALL tsControl_new_Cff(TSControl *parent, float32_t width, float32_t height);
TS_CAPI void TS_CCALL tsControl_delete(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_equalPtr(const TSControl self, const TSControl ptr);
TS_CAPI TSControl TS_CCALL tsControl_copyPtr(const TSControl self);
TS_CAPI TSControl TS_CCALL tsControl_clonePtr(const TSControl self);
TS_CAPI void TS_CCALL tsControl_clearPtr(TSControl self);
TS_CAPI void TS_CCALL tsControl_destroyPtr(TSControl self);
TS_CAPI void TS_CCALL tsControl_acquirePtr(TSControl self);
TS_CAPI void TS_CCALL tsControl_unacquirePtr(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_isValidPtr(const TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_isOwnerPtr(const TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_isConstPtr(const TSControl self);
TS_CAPI uint32_t TS_CCALL tsControl_getCountPtr(const TSControl self);
TS_CAPI const void* TS_CCALL tsControl_getInternalPtr(const TSControl self);
TS_CAPI uint32_t TS_CCALL tsControl_getNumControls(void);
TS_CAPI bool_t TS_CCALL tsControl_isControl(const TSControl control);
TS_CAPI TS_ControlType TS_CCALL tsControl_getType(TSControl self);
TS_CAPI const char* TS_CCALL tsControl_getTypeName_CT(TS_ControlType type);
TS_CAPI const char* TS_CCALL tsControl_getTypeName_c(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_isUnknown(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_isRoot(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_isText(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_isRect(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_isGrid(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_isGroup(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_isPanel(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_isDialog(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_isWindow(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_isCheck(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_isCombo(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_isButton(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_isSlider(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_isScroll(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_isSplit(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_isArea(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_isTree(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_isEdit(TSControl self);
TS_CAPI void TS_CCALL tsControl_setAlign(TSControl self, TS_ControlAlign align);
TS_CAPI TS_ControlAlign TS_CCALL tsControl_getAlign(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_hasAlign(TSControl self, TS_ControlAlign align);
TS_CAPI bool_t TS_CCALL tsControl_hasAligns(TSControl self, TS_ControlAlign aligns);
TS_CAPI bool_t TS_CCALL tsControl_isSpacer(TSControl self);
TS_CAPI void TS_CCALL tsControl_setCreated(TSControl self, bool_t created);
TS_CAPI bool_t TS_CCALL tsControl_isCreated(TSControl self);
TS_CAPI void TS_CCALL tsControl_setEnabled(TSControl self, bool_t enabled);
TS_CAPI bool_t TS_CCALL tsControl_isEnabled(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_wasEnabled(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_wasUpdated(TSControl self);
TS_CAPI void TS_CCALL tsControl_setDisabled(TSControl self, bool_t disabled);
TS_CAPI bool_t TS_CCALL tsControl_isDisabled(TSControl self);
TS_CAPI TSCanvas TS_CCALL tsControl_getCanvas(TSControl self);
TS_CAPI TSControlRoot TS_CCALL tsControl_getRoot_cb(TSControl self, bool_t local);
TS_CAPI TSControlRoot TS_CCALL tsControl_getRoot_b(TSControl self, bool_t local);
TS_CAPI TSControlPanel TS_CCALL tsControl_getPanel_c(TSControl self);
TS_CAPI TSControlPanel TS_CCALL tsControl_getPanel(TSControl self);
TS_CAPI uint32_t TS_CCALL tsControl_setParent(TSControl self, TSControl parent);
TS_CAPI TSControl TS_CCALL tsControl_getParent_c(TSControl self);
TS_CAPI TSControl TS_CCALL tsControl_getParent(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_isParentEnabled(TSControl self);
TS_CAPI bool_t TS_CCALL tsControl_isParentDisabled(TSControl self);
TS_CAPI uint32_t TS_CCALL tsControl_addChild(TSControl self, TSControl child);
TS_CAPI TSControl TS_CCALL tsControl_setChild(TSControl self, uint32_t index, TSControl child);
TS_CAPI bool_t TS_CCALL tsControl_raiseChild(TSControl self, TSControl child, uint32_t index);
TS_CAPI bool_t TS_CCALL tsControl_lowerChild(TSControl self, TSControl child, uint32_t index);
TS_CAPI bool_t TS_CCALL tsControl_removeChild(TSControl self, TSControl child);
TS_CAPI void TS_CCALL tsControl_releaseChildren(TSControl self);
TS_CAPI uint32_t TS_CCALL tsControl_findChild(TSControl self, const TSControl child);
TS_CAPI bool_t TS_CCALL tsControl_isChild(TSControl self, const TSControl child, bool_t hierarchy);
TS_CAPI uint32_t TS_CCALL tsControl_getNumChildren(TSControl self);
TS_CAPI TSControl TS_CCALL tsControl_getChild_cu(TSControl self, uint32_t index);
TS_CAPI TSControl TS_CCALL tsControl_getChild_u(TSControl self, uint32_t index);
TS_CAPI void TS_CCALL tsControl_setSize_cV2(TSControl self, const TSVector2f *size);
TS_CAPI void TS_CCALL tsControl_setSize_ff(TSControl self, float32_t width, float32_t height);
TS_CAPI TSVector2f TS_CCALL tsControl_getSize(TSControl self);
TS_CAPI float32_t TS_CCALL tsControl_getWidth(TSControl self);
TS_CAPI float32_t TS_CCALL tsControl_getHeight(TSControl self);
TS_CAPI void TS_CCALL tsControl_setPosition_cV3(TSControl self, const TSVector3f *position);
TS_CAPI void TS_CCALL tsControl_setPosition_fff(TSControl self, float32_t x, float32_t y, float32_t z);
TS_CAPI TSVector3f TS_CCALL tsControl_getPosition(TSControl self);
TS_CAPI float32_t TS_CCALL tsControl_getPositionX(TSControl self);
TS_CAPI float32_t TS_CCALL tsControl_getPositionY(TSControl self);
TS_CAPI void TS_CCALL tsControl_setOffset_cV3(TSControl self, const TSVector3f *offset);
TS_CAPI void TS_CCALL tsControl_setOffset_fff(TSControl self, float32_t x, float32_t y, float32_t z);
TS_CAPI TSVector3f TS_CCALL tsControl_getOffset(TSControl self);
TS_CAPI float32_t TS_CCALL tsControl_getOffsetX(TSControl self);
TS_CAPI float32_t TS_CCALL tsControl_getOffsetY(TSControl self);
TS_CAPI void TS_CCALL tsControl_setMargin_f(TSControl self, float32_t value);
TS_CAPI void TS_CCALL tsControl_setMargin_ff(TSControl self, float32_t horizontal, float32_t vertical);
TS_CAPI void TS_CCALL tsControl_setMargin_ffff(TSControl self, float32_t left, float32_t right, float32_t bottom, float32_t top);
TS_CAPI void TS_CCALL tsControl_setMargin_cR(TSControl self, const TSRect *margin);
TS_CAPI TSRect TS_CCALL tsControl_getMargin(TSControl self);
TS_CAPI TSRect TS_CCALL tsControl_getRect(TSControl self);
TS_CAPI TS_ControlState TS_CCALL tsControl_getState(TSControl self);

/// Tellusim::ControlRoot
typedef void (*TSControlRootCopyCallback)(TSControlRoot a0, const char *text, void *data_);
typedef TSString (*TSControlRootPasteCallback)(TSControlRoot a0, void *data_);
TS_CAPI TSControlRoot TS_CCALL tsControlRoot_new(void);
TS_CAPI TSControlRoot TS_CCALL tsControlRoot_new_Cb(TSCanvas canvas, bool_t blob);
TS_CAPI void TS_CCALL tsControlRoot_delete(TSControlRoot self);
TS_CAPI bool_t TS_CCALL tsControlRoot_equalPtr(const TSControlRoot self, const TSControlRoot ptr);
TS_CAPI TSControlRoot TS_CCALL tsControlRoot_copyPtr(const TSControlRoot self);
TS_CAPI TSControlRoot TS_CCALL tsControlRoot_clonePtr(const TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_clearPtr(TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_destroyPtr(TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_acquirePtr(TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_unacquirePtr(TSControlRoot self);
TS_CAPI bool_t TS_CCALL tsControlRoot_isValidPtr(const TSControlRoot self);
TS_CAPI bool_t TS_CCALL tsControlRoot_isOwnerPtr(const TSControlRoot self);
TS_CAPI bool_t TS_CCALL tsControlRoot_isConstPtr(const TSControlRoot self);
TS_CAPI uint32_t TS_CCALL tsControlRoot_getCountPtr(const TSControlRoot self);
TS_CAPI const void* TS_CCALL tsControlRoot_getInternalPtr(const TSControlRoot self);
TS_CAPI bool_t TS_CCALL tsControlRoot_equalControlPtr(const TSControlRoot self, const TSControl base);
TS_CAPI TSControlRoot TS_CCALL tsControlRoot_castControlPtr(TSControl base);
TS_CAPI TSControl TS_CCALL tsControlRoot_baseControlPtr(TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_setViewport_cV(TSControlRoot self, const TSViewport *viewport);
TS_CAPI void TS_CCALL tsControlRoot_setViewport_uu(TSControlRoot self, uint32_t width, uint32_t height);
TS_CAPI void TS_CCALL tsControlRoot_setViewport_ff(TSControlRoot self, float32_t width, float32_t height);
TS_CAPI TSViewport TS_CCALL tsControlRoot_getViewport(TSControlRoot self);
TS_CAPI TSString TS_CCALL tsControlRoot_getFontName(TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_setFontName_s(TSControlRoot self, const char *name);
TS_CAPI void TS_CCALL tsControlRoot_setFontName_cS(TSControlRoot self, const TSString name);
TS_CAPI bool_t TS_CCALL tsControlRoot_setFontBlob(TSControlRoot self, const uint8_t (*blob)[256], const char *name);
TS_CAPI bool_t TS_CCALL tsControlRoot_setFontSize(TSControlRoot self, uint32_t size, bool_t update);
TS_CAPI uint32_t TS_CCALL tsControlRoot_getFontSize(TSControlRoot self);
TS_CAPI bool_t TS_CCALL tsControlRoot_setFontScale(TSControlRoot self, uint32_t scale, bool_t update);
TS_CAPI uint32_t TS_CCALL tsControlRoot_getFontScale(TSControlRoot self);
TS_CAPI bool_t TS_CCALL tsControlRoot_setFontStyle(TSControlRoot self, const TSFontStyle *style, bool_t update);
TS_CAPI TSFontStyle TS_CCALL tsControlRoot_getFontStyle_c(TSControlRoot self);
TS_CAPI TSFontStyle TS_CCALL tsControlRoot_getFontStyle(TSControlRoot self);
TS_CAPI TSString TS_CCALL tsControlRoot_getTextureName(TSControlRoot self);
TS_CAPI bool_t TS_CCALL tsControlRoot_setTextureName_suuf(TSControlRoot self, const char *name, uint32_t width, uint32_t height, float32_t border);
TS_CAPI bool_t TS_CCALL tsControlRoot_setTextureName_cSuuf(TSControlRoot self, const TSString name, uint32_t width, uint32_t height, float32_t border);
TS_CAPI bool_t TS_CCALL tsControlRoot_setTextureBlob(TSControlRoot self, const uint8_t (*blob)[256], const char *name, uint32_t width, uint32_t height, float32_t border);
TS_CAPI float32_t TS_CCALL tsControlRoot_getTextureWidth(TSControlRoot self);
TS_CAPI float32_t TS_CCALL tsControlRoot_getTextureHeight(TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_setTextColor(TSControlRoot self, TS_ControlType type, TS_ControlState state, const TSColor *color);
TS_CAPI void TS_CCALL tsControlRoot_setTextOffset(TSControlRoot self, TS_ControlType type, TS_ControlState state, const TSVector3f *offset);
TS_CAPI TSColor TS_CCALL tsControlRoot_getTextColor(TSControlRoot self, TS_ControlType type, TS_ControlState state);
TS_CAPI TSVector3f TS_CCALL tsControlRoot_getTextOffset(TSControlRoot self, TS_ControlType type, TS_ControlState state);
TS_CAPI void TS_CCALL tsControlRoot_setMeshColor(TSControlRoot self, TS_ControlMesh mesh, TS_ControlState state, const TSColor *color);
TS_CAPI void TS_CCALL tsControlRoot_setMeshRegion(TSControlRoot self, TS_ControlMesh mesh, const TSRect *grid, const TSRect *region, const TSVector2f *border);
TS_CAPI void TS_CCALL tsControlRoot_setMeshRegions(TSControlRoot self, TS_ControlMesh mesh, const TSRect *grid, const TSRect *regions, const TSVector2f *border);
TS_CAPI uint32_t TS_CCALL tsControlRoot_getMeshColor(TSControlRoot self, TS_ControlMesh mesh, TS_ControlState state);
TS_CAPI TSRect TS_CCALL tsControlRoot_getMeshGrid(TSControlRoot self, TS_ControlMesh mesh);
TS_CAPI TSRect TS_CCALL tsControlRoot_getMeshMargin(TSControlRoot self, TS_ControlMesh mesh);
TS_CAPI TSRect TS_CCALL tsControlRoot_getMeshRegion(TSControlRoot self, TS_ControlMesh mesh, TS_ControlState state);
TS_CAPI void TS_CCALL tsControlRoot_setGroupRadius(TSControlRoot self, float32_t radius);
TS_CAPI void TS_CCALL tsControlRoot_setGroupColor(TSControlRoot self, const TSColor *color);
TS_CAPI float32_t TS_CCALL tsControlRoot_getGroupRadius(TSControlRoot self);
TS_CAPI TSColor TS_CCALL tsControlRoot_getGroupColor(TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_setPanelRadius(TSControlRoot self, float32_t radius);
TS_CAPI void TS_CCALL tsControlRoot_setPanelColor(TSControlRoot self, const TSColor *color);
TS_CAPI float32_t TS_CCALL tsControlRoot_getPanelRadius(TSControlRoot self);
TS_CAPI TSColor TS_CCALL tsControlRoot_getPanelColor(TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_setCheckedColor(TSControlRoot self, const TSColor *color);
TS_CAPI TSColor TS_CCALL tsControlRoot_getCheckedColor(TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_setSplitSize(TSControlRoot self, float32_t size);
TS_CAPI float32_t TS_CCALL tsControlRoot_getSplitSize(TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_setMouse_iiCB(TSControlRoot self, int32_t x, int32_t y, TS_ControlButton buttons);
TS_CAPI void TS_CCALL tsControlRoot_setMouse_ffCB(TSControlRoot self, float32_t x, float32_t y, TS_ControlButton buttons);
TS_CAPI TSVector2f TS_CCALL tsControlRoot_getMouse(TSControlRoot self);
TS_CAPI TS_ControlButton TS_CCALL tsControlRoot_getMouseButtons(TSControlRoot self);
TS_CAPI float32_t TS_CCALL tsControlRoot_getMouseX(TSControlRoot self);
TS_CAPI float32_t TS_CCALL tsControlRoot_getMouseY(TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_setMouseOffset(TSControlRoot self, const TSVector2f *offset);
TS_CAPI TSVector2f TS_CCALL tsControlRoot_getMouseOffset(TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_setMouseAxis(TSControlRoot self, TS_ControlAxis axis, float32_t delta);
TS_CAPI void TS_CCALL tsControlRoot_setMouseAlign(TSControlRoot self, TS_ControlAlign align, bool_t clear);
TS_CAPI TS_ControlAlign TS_CCALL tsControlRoot_getMouseAlign(TSControlRoot self);
TS_CAPI bool_t TS_CCALL tsControlRoot_hasMouseAlign(TSControlRoot self, TS_ControlAlign align);
TS_CAPI bool_t TS_CCALL tsControlRoot_hasMouseAligns(TSControlRoot self, TS_ControlAlign aligns);
TS_CAPI bool_t TS_CCALL tsControlRoot_setKeyboardKey(TSControlRoot self, uint32_t key, uint32_t code, bool_t value);
TS_CAPI bool_t TS_CCALL tsControlRoot_getKeyboardKey(TSControlRoot self, uint32_t key, bool_t clear);
TS_CAPI void TS_CCALL tsControlRoot_clearCurrentControl(TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_setCurrentControl(TSControlRoot self, TSControl control, bool_t grab);
TS_CAPI TSControl TS_CCALL tsControlRoot_getCurrentControl(TSControlRoot self);
TS_CAPI bool_t TS_CCALL tsControlRoot_isCurrentControl(TSControlRoot self);
TS_CAPI bool_t TS_CCALL tsControlRoot_getControlGrab(TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_clearFocusedControl(TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_setFocusedControl(TSControlRoot self, TSControl control);
TS_CAPI TSControl TS_CCALL tsControlRoot_getFocusedControl(TSControlRoot self);
TS_CAPI bool_t TS_CCALL tsControlRoot_isFocusedControl(TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_clearMouseControl(TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_setMouseControl(TSControlRoot self, TSControl control);
TS_CAPI TSControl TS_CCALL tsControlRoot_getMouseControl(TSControlRoot self);
TS_CAPI bool_t TS_CCALL tsControlRoot_isMouseControl(TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_clearInputControl(TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_setInputControl(TSControlRoot self, TSControl control);
TS_CAPI TSControl TS_CCALL tsControlRoot_getInputControl(TSControlRoot self);
TS_CAPI bool_t TS_CCALL tsControlRoot_isInputControl(TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_clearModalControl(TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_setModalControl(TSControlRoot self, TSControl control, bool_t disabled);
TS_CAPI TSControl TS_CCALL tsControlRoot_getModalControl(TSControlRoot self);
TS_CAPI bool_t TS_CCALL tsControlRoot_isModalDisabled(TSControlRoot self);
TS_CAPI bool_t TS_CCALL tsControlRoot_isModalControl(TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_setOverlayOrder(TSControlRoot self, int32_t order);
TS_CAPI int32_t TS_CCALL tsControlRoot_getOverlayOrder(TSControlRoot self);
TS_CAPI bool_t TS_CCALL tsControlRoot_update(TSControlRoot self, uint32_t scale, int32_t order);
TS_CAPI void TS_CCALL tsControlRoot_setCopyText_s(TSControlRoot self, const char *text);
TS_CAPI void TS_CCALL tsControlRoot_setCopyText_cS(TSControlRoot self, const TSString text);
TS_CAPI TSString TS_CCALL tsControlRoot_getPasteText(TSControlRoot self);
TS_CAPI void TS_CCALL tsControlRoot_setCopyCallback(TSControlRoot self, const TSControlRootCopyCallback func, void *data_);
TS_CAPI void TS_CCALL tsControlRoot_setPasteCallback(TSControlRoot self, const TSControlRootPasteCallback func, void *data_);

/// Tellusim::ControlText
TS_CAPI TSControlText TS_CCALL tsControlText_new(void);
TS_CAPI TSControlText TS_CCALL tsControlText_new_C(TSControl *parent);
TS_CAPI TSControlText TS_CCALL tsControlText_new_Cs(TSControl *parent, const char *text);
TS_CAPI TSControlText TS_CCALL tsControlText_new_CcS(TSControl *parent, const TSString text);
TS_CAPI void TS_CCALL tsControlText_delete(TSControlText self);
TS_CAPI bool_t TS_CCALL tsControlText_equalPtr(const TSControlText self, const TSControlText ptr);
TS_CAPI TSControlText TS_CCALL tsControlText_copyPtr(const TSControlText self);
TS_CAPI TSControlText TS_CCALL tsControlText_clonePtr(const TSControlText self);
TS_CAPI void TS_CCALL tsControlText_clearPtr(TSControlText self);
TS_CAPI void TS_CCALL tsControlText_destroyPtr(TSControlText self);
TS_CAPI void TS_CCALL tsControlText_acquirePtr(TSControlText self);
TS_CAPI void TS_CCALL tsControlText_unacquirePtr(TSControlText self);
TS_CAPI bool_t TS_CCALL tsControlText_isValidPtr(const TSControlText self);
TS_CAPI bool_t TS_CCALL tsControlText_isOwnerPtr(const TSControlText self);
TS_CAPI bool_t TS_CCALL tsControlText_isConstPtr(const TSControlText self);
TS_CAPI uint32_t TS_CCALL tsControlText_getCountPtr(const TSControlText self);
TS_CAPI const void* TS_CCALL tsControlText_getInternalPtr(const TSControlText self);
TS_CAPI bool_t TS_CCALL tsControlText_equalControlPtr(const TSControlText self, const TSControl base);
TS_CAPI TSControlText TS_CCALL tsControlText_castControlPtr(TSControl base);
TS_CAPI TSControl TS_CCALL tsControlText_baseControlPtr(TSControlText self);
TS_CAPI void TS_CCALL tsControlText_setCallback(TSControlText self, bool_t callback);
TS_CAPI bool_t TS_CCALL tsControlText_getCallback(TSControlText self);
TS_CAPI void TS_CCALL tsControlText_setMode(TSControlText self, TS_CanvasElementMode mode);
TS_CAPI TS_CanvasElementMode TS_CCALL tsControlText_getMode(TSControlText self);
TS_CAPI void TS_CCALL tsControlText_setPipeline_P(TSControlText self, TSPipeline pipeline);
TS_CAPI void TS_CCALL tsControlText_setPipeline_PcCEDC(TSControlText self, TSPipeline pipeline, const TSCanvasElementDrawCallback func, void *data_);
TS_CAPI TSPipeline TS_CCALL tsControlText_getPipeline(TSControlText self);
TS_CAPI void TS_CCALL tsControlText_setColor_cC(TSControlText self, const TSColor *color);
TS_CAPI void TS_CCALL tsControlText_setColor_ffff(TSControlText self, float32_t r, float32_t g, float32_t b, float32_t a);
TS_CAPI TSColor TS_CCALL tsControlText_getColor(TSControlText self);
TS_CAPI void TS_CCALL tsControlText_setFilter(TSControlText self, TS_SamplerFilter filter);
TS_CAPI TS_SamplerFilter TS_CCALL tsControlText_getFilter(TSControlText self);
TS_CAPI void TS_CCALL tsControlText_setAnisotropy(TSControlText self, uint32_t anisotropy);
TS_CAPI uint32_t TS_CCALL tsControlText_getAnisotropy(TSControlText self);
TS_CAPI void TS_CCALL tsControlText_setBlend(TSControlText self, TS_PipelineBlendOp op, TS_PipelineBlendFunc src, TS_PipelineBlendFunc dest);
TS_CAPI TS_PipelineBlendOp TS_CCALL tsControlText_getBlendOp(TSControlText self);
TS_CAPI TS_PipelineBlendFunc TS_CCALL tsControlText_getBlendSrcFunc(TSControlText self);
TS_CAPI TS_PipelineBlendFunc TS_CCALL tsControlText_getBlendDestFunc(TSControlText self);
TS_CAPI void TS_CCALL tsControlText_setFontName_s(TSControlText self, const char *name);
TS_CAPI void TS_CCALL tsControlText_setFontName_cS(TSControlText self, const TSString name);
TS_CAPI TSString TS_CCALL tsControlText_getFontName(TSControlText self);
TS_CAPI void TS_CCALL tsControlText_setFontColor(TSControlText self, const TSColor *color);
TS_CAPI TSColor TS_CCALL tsControlText_getFontColor(TSControlText self);
TS_CAPI bool_t TS_CCALL tsControlText_setFontSize(TSControlText self, uint32_t size);
TS_CAPI uint32_t TS_CCALL tsControlText_getFontSize(TSControlText self);
TS_CAPI bool_t TS_CCALL tsControlText_setFontStyle(TSControlText self, const TSFontStyle *style);
TS_CAPI TSFontStyle TS_CCALL tsControlText_getFontStyleConst(TSControlText self);
TS_CAPI TSFontStyle TS_CCALL tsControlText_getFontStyle_c(TSControlText self);
TS_CAPI TSFontStyle TS_CCALL tsControlText_getFontStyle(TSControlText self);
TS_CAPI void TS_CCALL tsControlText_setFontAlign(TSControlText self, TS_ControlAlign align);
TS_CAPI TS_ControlAlign TS_CCALL tsControlText_getFontAlign(TSControlText self);
TS_CAPI bool_t TS_CCALL tsControlText_hasFontAlign(TSControlText self, TS_ControlAlign align);
TS_CAPI bool_t TS_CCALL tsControlText_hasFontAligns(TSControlText self, TS_ControlAlign aligns);
TS_CAPI void TS_CCALL tsControlText_setText_s(TSControlText self, const char *text);
TS_CAPI void TS_CCALL tsControlText_setText_cS(TSControlText self, const TSString text);
TS_CAPI TSString TS_CCALL tsControlText_getText(TSControlText self);
TS_CAPI TSCanvasText TS_CCALL tsControlText_getCanvasText(TSControlText self);

/// Tellusim::ControlRect
typedef bool_t (*TSControlRectInsideCallback)(TSControlRect a0, float32_t x, float32_t y, void *data_);
typedef void (*TSControlRectPressedCallback)(TSControlRect a0, float32_t x, float32_t y, void *data_);
typedef void (*TSControlRectReleasedCallback)(TSControlRect a0, float32_t x, float32_t y, void *data_);
typedef void (*TSControlRectClickedCallback)(TSControlRect a0, void *data_);
TS_CAPI TSControlRect TS_CCALL tsControlRect_new(void);
TS_CAPI TSControlRect TS_CCALL tsControlRect_new_C(TSControl *parent);
TS_CAPI TSControlRect TS_CCALL tsControlRect_new_CT(TSControl *parent, TSTexture texture);
TS_CAPI TSControlRect TS_CCALL tsControlRect_new_Cs(TSControl *parent, const char *name);
TS_CAPI TSControlRect TS_CCALL tsControlRect_new_CCEM(TSControl *parent, TS_CanvasElementMode mode);
TS_CAPI void TS_CCALL tsControlRect_delete(TSControlRect self);
TS_CAPI bool_t TS_CCALL tsControlRect_equalPtr(const TSControlRect self, const TSControlRect ptr);
TS_CAPI TSControlRect TS_CCALL tsControlRect_copyPtr(const TSControlRect self);
TS_CAPI TSControlRect TS_CCALL tsControlRect_clonePtr(const TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_clearPtr(TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_destroyPtr(TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_acquirePtr(TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_unacquirePtr(TSControlRect self);
TS_CAPI bool_t TS_CCALL tsControlRect_isValidPtr(const TSControlRect self);
TS_CAPI bool_t TS_CCALL tsControlRect_isOwnerPtr(const TSControlRect self);
TS_CAPI bool_t TS_CCALL tsControlRect_isConstPtr(const TSControlRect self);
TS_CAPI uint32_t TS_CCALL tsControlRect_getCountPtr(const TSControlRect self);
TS_CAPI const void* TS_CCALL tsControlRect_getInternalPtr(const TSControlRect self);
TS_CAPI bool_t TS_CCALL tsControlRect_equalControlPtr(const TSControlRect self, const TSControl base);
TS_CAPI TSControlRect TS_CCALL tsControlRect_castControlPtr(TSControl base);
TS_CAPI TSControl TS_CCALL tsControlRect_baseControlPtr(TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_setCallback(TSControlRect self, bool_t callback);
TS_CAPI bool_t TS_CCALL tsControlRect_getCallback(TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_setFullscreen(TSControlRect self, bool_t fullscreen);
TS_CAPI bool_t TS_CCALL tsControlRect_isFullscreen(TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_setMode(TSControlRect self, TS_CanvasElementMode mode);
TS_CAPI TS_CanvasElementMode TS_CCALL tsControlRect_getMode(TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_setPipeline_P(TSControlRect self, TSPipeline pipeline);
TS_CAPI void TS_CCALL tsControlRect_setPipeline_PcCEDC(TSControlRect self, TSPipeline pipeline, const TSCanvasElementDrawCallback func, void *data_);
TS_CAPI TSPipeline TS_CCALL tsControlRect_getPipeline(TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_setRadius(TSControlRect self, float32_t radius);
TS_CAPI float32_t TS_CCALL tsControlRect_getRadius(TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_setColor_cC(TSControlRect self, const TSColor *color);
TS_CAPI void TS_CCALL tsControlRect_setColor_ffff(TSControlRect self, float32_t r, float32_t g, float32_t b, float32_t a);
TS_CAPI TSColor TS_CCALL tsControlRect_getColor(TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_setStrokeStyle(TSControlRect self, const TSStrokeStyle *style);
TS_CAPI TSStrokeStyle TS_CCALL tsControlRect_getStrokeStyleConst(TSControlRect self);
TS_CAPI TSStrokeStyle TS_CCALL tsControlRect_getStrokeStyle_c(TSControlRect self);
TS_CAPI TSStrokeStyle TS_CCALL tsControlRect_getStrokeStyle(TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_setGradientStyle(TSControlRect self, const TSGradientStyle *style);
TS_CAPI TSGradientStyle TS_CCALL tsControlRect_getGradientStyleConst(TSControlRect self);
TS_CAPI TSGradientStyle TS_CCALL tsControlRect_getGradientStyle_c(TSControlRect self);
TS_CAPI TSGradientStyle TS_CCALL tsControlRect_getGradientStyle(TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_setMipmap(TSControlRect self, float32_t mipmap);
TS_CAPI float32_t TS_CCALL tsControlRect_getMipmap(TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_setFilter(TSControlRect self, TS_SamplerFilter filter);
TS_CAPI TS_SamplerFilter TS_CCALL tsControlRect_getFilter(TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_setAnisotropy(TSControlRect self, uint32_t anisotropy);
TS_CAPI uint32_t TS_CCALL tsControlRect_getAnisotropy(TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_setWrapMode(TSControlRect self, TS_SamplerWrapMode mode);
TS_CAPI TS_SamplerWrapMode TS_CCALL tsControlRect_getWrapMode(TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_setBlend(TSControlRect self, TS_PipelineBlendOp op, TS_PipelineBlendFunc src, TS_PipelineBlendFunc dest);
TS_CAPI TS_PipelineBlendOp TS_CCALL tsControlRect_getBlendOp(TSControlRect self);
TS_CAPI TS_PipelineBlendFunc TS_CCALL tsControlRect_getBlendSrcFunc(TSControlRect self);
TS_CAPI TS_PipelineBlendFunc TS_CCALL tsControlRect_getBlendDestFunc(TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_setTexture(TSControlRect self, TSTexture texture, bool_t linear);
TS_CAPI TSTexture TS_CCALL tsControlRect_getTexture(TSControlRect self);
TS_CAPI bool_t TS_CCALL tsControlRect_getTextureLinear(TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_setTextureName_s(TSControlRect self, const char *name);
TS_CAPI void TS_CCALL tsControlRect_setTextureName_cS(TSControlRect self, const TSString name);
TS_CAPI TSString TS_CCALL tsControlRect_getTextureName(TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_setTextureScale(TSControlRect self, float32_t scale_x, float32_t scale_y);
TS_CAPI float32_t TS_CCALL tsControlRect_getTextureScaleX(TSControlRect self);
TS_CAPI float32_t TS_CCALL tsControlRect_getTextureScaleY(TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_setTextureFlip(TSControlRect self, bool_t flip_x, bool_t flip_y);
TS_CAPI bool_t TS_CCALL tsControlRect_getTextureFlipX(TSControlRect self);
TS_CAPI bool_t TS_CCALL tsControlRect_getTextureFlipY(TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_setTextureProj(TSControlRect self, bool_t projection);
TS_CAPI bool_t TS_CCALL tsControlRect_getTextureProj(TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_setTexCoord_cR(TSControlRect self, const TSRect *texcoord);
TS_CAPI void TS_CCALL tsControlRect_setTexCoord_ffff(TSControlRect self, float32_t left, float32_t right, float32_t bottom, float32_t top);
TS_CAPI TSRect TS_CCALL tsControlRect_getTexCoord(TSControlRect self);
TS_CAPI void TS_CCALL tsControlRect_setInsideCallback(TSControlRect self, const TSControlRectInsideCallback func, void *data_);
TS_CAPI void TS_CCALL tsControlRect_setPressedCallback(TSControlRect self, const TSControlRectPressedCallback func, void *data_);
TS_CAPI void TS_CCALL tsControlRect_setReleasedCallback(TSControlRect self, const TSControlRectReleasedCallback func, void *data_);
TS_CAPI void TS_CCALL tsControlRect_setClickedCallback(TSControlRect self, const TSControlRectClickedCallback func, void *data_);
TS_CAPI void TS_CCALL tsControlRect_setClicked2Callback(TSControlRect self, const TSControlRectClickedCallback func, void *data_);
TS_CAPI void TS_CCALL tsControlRect_setClickedRightCallback(TSControlRect self, const TSControlRectClickedCallback func, void *data_);
TS_CAPI TSCanvasRect TS_CCALL tsControlRect_getCanvasRect(TSControlRect self);
TS_CAPI TSCanvasMesh TS_CCALL tsControlRect_getCanvasMesh(TSControlRect self);

/// Tellusim::ControlGrid
TS_CAPI TSControlGrid TS_CCALL tsControlGrid_new(void);
TS_CAPI TSControlGrid TS_CCALL tsControlGrid_new_C(TSControl *parent);
TS_CAPI TSControlGrid TS_CCALL tsControlGrid_new_Cu(TSControl *parent, uint32_t columns);
TS_CAPI TSControlGrid TS_CCALL tsControlGrid_new_Cuff(TSControl *parent, uint32_t columns, float32_t x, float32_t y);
TS_CAPI void TS_CCALL tsControlGrid_delete(TSControlGrid self);
TS_CAPI bool_t TS_CCALL tsControlGrid_equalPtr(const TSControlGrid self, const TSControlGrid ptr);
TS_CAPI TSControlGrid TS_CCALL tsControlGrid_copyPtr(const TSControlGrid self);
TS_CAPI TSControlGrid TS_CCALL tsControlGrid_clonePtr(const TSControlGrid self);
TS_CAPI void TS_CCALL tsControlGrid_clearPtr(TSControlGrid self);
TS_CAPI void TS_CCALL tsControlGrid_destroyPtr(TSControlGrid self);
TS_CAPI void TS_CCALL tsControlGrid_acquirePtr(TSControlGrid self);
TS_CAPI void TS_CCALL tsControlGrid_unacquirePtr(TSControlGrid self);
TS_CAPI bool_t TS_CCALL tsControlGrid_isValidPtr(const TSControlGrid self);
TS_CAPI bool_t TS_CCALL tsControlGrid_isOwnerPtr(const TSControlGrid self);
TS_CAPI bool_t TS_CCALL tsControlGrid_isConstPtr(const TSControlGrid self);
TS_CAPI uint32_t TS_CCALL tsControlGrid_getCountPtr(const TSControlGrid self);
TS_CAPI const void* TS_CCALL tsControlGrid_getInternalPtr(const TSControlGrid self);
TS_CAPI bool_t TS_CCALL tsControlGrid_equalControlPtr(const TSControlGrid self, const TSControl base);
TS_CAPI TSControlGrid TS_CCALL tsControlGrid_castControlPtr(TSControl base);
TS_CAPI TSControl TS_CCALL tsControlGrid_baseControlPtr(TSControlGrid self);
TS_CAPI void TS_CCALL tsControlGrid_setColumns(TSControlGrid self, uint32_t columns);
TS_CAPI uint32_t TS_CCALL tsControlGrid_getColumns(TSControlGrid self);
TS_CAPI void TS_CCALL tsControlGrid_setSpacing_cV2(TSControlGrid self, const TSVector2f *spacing);
TS_CAPI void TS_CCALL tsControlGrid_setSpacing_ff(TSControlGrid self, float32_t x, float32_t y);
TS_CAPI TSVector2f TS_CCALL tsControlGrid_getSpacing(TSControlGrid self);
TS_CAPI void TS_CCALL tsControlGrid_setColumnRatio(TSControlGrid self, uint32_t index, float32_t ratio);
TS_CAPI float32_t TS_CCALL tsControlGrid_getColumnRatio(TSControlGrid self, uint32_t index);
TS_CAPI TSVector2f TS_CCALL tsControlGrid_getControlsSize(TSControlGrid self);

/// Tellusim::ControlGroup
typedef void (*TSControlGroupClickedCallback)(TSControlGroup a0, void *data_);
TS_CAPI TSControlGroup TS_CCALL tsControlGroup_new(void);
TS_CAPI TSControlGroup TS_CCALL tsControlGroup_new_Cb(TSControl *parent, bool_t above);
TS_CAPI TSControlGroup TS_CCALL tsControlGroup_new_Csb(TSControl *parent, const char *text, bool_t above);
TS_CAPI TSControlGroup TS_CCALL tsControlGroup_new_CcSb(TSControl *parent, const TSString text, bool_t above);
TS_CAPI TSControlGroup TS_CCALL tsControlGroup_new_Csub(TSControl *parent, const char *text, uint32_t columns, bool_t above);
TS_CAPI TSControlGroup TS_CCALL tsControlGroup_new_Csuffb(TSControl *parent, const char *text, uint32_t columns, float32_t x, float32_t y, bool_t above);
TS_CAPI void TS_CCALL tsControlGroup_delete(TSControlGroup self);
TS_CAPI bool_t TS_CCALL tsControlGroup_equalPtr(const TSControlGroup self, const TSControlGroup ptr);
TS_CAPI TSControlGroup TS_CCALL tsControlGroup_copyPtr(const TSControlGroup self);
TS_CAPI TSControlGroup TS_CCALL tsControlGroup_clonePtr(const TSControlGroup self);
TS_CAPI void TS_CCALL tsControlGroup_clearPtr(TSControlGroup self);
TS_CAPI void TS_CCALL tsControlGroup_destroyPtr(TSControlGroup self);
TS_CAPI void TS_CCALL tsControlGroup_acquirePtr(TSControlGroup self);
TS_CAPI void TS_CCALL tsControlGroup_unacquirePtr(TSControlGroup self);
TS_CAPI bool_t TS_CCALL tsControlGroup_isValidPtr(const TSControlGroup self);
TS_CAPI bool_t TS_CCALL tsControlGroup_isOwnerPtr(const TSControlGroup self);
TS_CAPI bool_t TS_CCALL tsControlGroup_isConstPtr(const TSControlGroup self);
TS_CAPI uint32_t TS_CCALL tsControlGroup_getCountPtr(const TSControlGroup self);
TS_CAPI const void* TS_CCALL tsControlGroup_getInternalPtr(const TSControlGroup self);
TS_CAPI bool_t TS_CCALL tsControlGroup_equalControlTextPtr(const TSControlGroup self, const TSControlText base);
TS_CAPI TSControlGroup TS_CCALL tsControlGroup_castControlTextPtr(TSControlText base);
TS_CAPI TSControlText TS_CCALL tsControlGroup_baseControlTextPtr(TSControlGroup self);
TS_CAPI bool_t TS_CCALL tsControlGroup_equalControlPtr(const TSControlGroup self, const TSControl base);
TS_CAPI TSControlGroup TS_CCALL tsControlGroup_castControlPtr(TSControl base);
TS_CAPI TSControl TS_CCALL tsControlGroup_baseControlPtr(TSControlGroup self);
TS_CAPI void TS_CCALL tsControlGroup_setAbove(TSControlGroup self, bool_t above, bool_t text);
TS_CAPI bool_t TS_CCALL tsControlGroup_isAbove(TSControlGroup self);
TS_CAPI bool_t TS_CCALL tsControlGroup_isBelow(TSControlGroup self);
TS_CAPI void TS_CCALL tsControlGroup_setFoldable(TSControlGroup self, bool_t foldable);
TS_CAPI bool_t TS_CCALL tsControlGroup_isFoldable(TSControlGroup self);
TS_CAPI void TS_CCALL tsControlGroup_setExpanded(TSControlGroup self, bool_t expanded);
TS_CAPI bool_t TS_CCALL tsControlGroup_isExpanded(TSControlGroup self);
TS_CAPI void TS_CCALL tsControlGroup_setBackground(TSControlGroup self, bool_t background);
TS_CAPI bool_t TS_CCALL tsControlGroup_getBackground(TSControlGroup self);
TS_CAPI void TS_CCALL tsControlGroup_setGroupRadius(TSControlGroup self, float32_t radius);
TS_CAPI float32_t TS_CCALL tsControlGroup_getGroupRadius(TSControlGroup self);
TS_CAPI void TS_CCALL tsControlGroup_setGroupColor(TSControlGroup self, const TSColor *color);
TS_CAPI TSColor TS_CCALL tsControlGroup_getGroupColor(TSControlGroup self);
TS_CAPI void TS_CCALL tsControlGroup_setStrokeStyle(TSControlGroup self, const TSStrokeStyle *style);
TS_CAPI TSStrokeStyle TS_CCALL tsControlGroup_getStrokeStyleConst(TSControlGroup self);
TS_CAPI TSStrokeStyle TS_CCALL tsControlGroup_getStrokeStyle_c(TSControlGroup self);
TS_CAPI TSStrokeStyle TS_CCALL tsControlGroup_getStrokeStyle(TSControlGroup self);
TS_CAPI void TS_CCALL tsControlGroup_setGradientStyle(TSControlGroup self, const TSGradientStyle *style);
TS_CAPI TSGradientStyle TS_CCALL tsControlGroup_getGradientStyleConst(TSControlGroup self);
TS_CAPI TSGradientStyle TS_CCALL tsControlGroup_getGradientStyle_c(TSControlGroup self);
TS_CAPI TSGradientStyle TS_CCALL tsControlGroup_getGradientStyle(TSControlGroup self);
TS_CAPI void TS_CCALL tsControlGroup_setFoldedText_s(TSControlGroup self, const char *text);
TS_CAPI void TS_CCALL tsControlGroup_setFoldedText_cS(TSControlGroup self, const TSString text);
TS_CAPI TSString TS_CCALL tsControlGroup_getFoldedText(TSControlGroup self);
TS_CAPI void TS_CCALL tsControlGroup_setExpandedText_s(TSControlGroup self, const char *text);
TS_CAPI void TS_CCALL tsControlGroup_setExpandedText_cS(TSControlGroup self, const TSString text);
TS_CAPI TSString TS_CCALL tsControlGroup_getExpandedText(TSControlGroup self);
TS_CAPI void TS_CCALL tsControlGroup_setColumns(TSControlGroup self, uint32_t columns);
TS_CAPI uint32_t TS_CCALL tsControlGroup_getColumns(TSControlGroup self);
TS_CAPI void TS_CCALL tsControlGroup_setSpacing_cV2(TSControlGroup self, const TSVector2f *spacing);
TS_CAPI void TS_CCALL tsControlGroup_setSpacing_ff(TSControlGroup self, float32_t x, float32_t y);
TS_CAPI TSVector2f TS_CCALL tsControlGroup_getSpacing(TSControlGroup self);
TS_CAPI void TS_CCALL tsControlGroup_setColumnRatio(TSControlGroup self, uint32_t index, float32_t ratio);
TS_CAPI float32_t TS_CCALL tsControlGroup_getColumnRatio(TSControlGroup self, uint32_t index);
TS_CAPI TSVector2f TS_CCALL tsControlGroup_getControlsSize(TSControlGroup self);
TS_CAPI void TS_CCALL tsControlGroup_setClickedCallback(TSControlGroup self, const TSControlGroupClickedCallback func, void *data_);
TS_CAPI bool_t TS_CCALL tsControlGroup_isClicked(TSControlGroup self);
TS_CAPI TSCanvasRect TS_CCALL tsControlGroup_getCanvasRect(TSControlGroup self);

/// Tellusim::ControlPanel
TS_CAPI TSControlPanel TS_CCALL tsControlPanel_new(void);
TS_CAPI TSControlPanel TS_CCALL tsControlPanel_new_C(TSControl *parent);
TS_CAPI TSControlPanel TS_CCALL tsControlPanel_new_Cu(TSControl *parent, uint32_t columns);
TS_CAPI TSControlPanel TS_CCALL tsControlPanel_new_Cuff(TSControl *parent, uint32_t columns, float32_t x, float32_t y);
TS_CAPI void TS_CCALL tsControlPanel_delete(TSControlPanel self);
TS_CAPI bool_t TS_CCALL tsControlPanel_equalPtr(const TSControlPanel self, const TSControlPanel ptr);
TS_CAPI TSControlPanel TS_CCALL tsControlPanel_copyPtr(const TSControlPanel self);
TS_CAPI TSControlPanel TS_CCALL tsControlPanel_clonePtr(const TSControlPanel self);
TS_CAPI void TS_CCALL tsControlPanel_clearPtr(TSControlPanel self);
TS_CAPI void TS_CCALL tsControlPanel_destroyPtr(TSControlPanel self);
TS_CAPI void TS_CCALL tsControlPanel_acquirePtr(TSControlPanel self);
TS_CAPI void TS_CCALL tsControlPanel_unacquirePtr(TSControlPanel self);
TS_CAPI bool_t TS_CCALL tsControlPanel_isValidPtr(const TSControlPanel self);
TS_CAPI bool_t TS_CCALL tsControlPanel_isOwnerPtr(const TSControlPanel self);
TS_CAPI bool_t TS_CCALL tsControlPanel_isConstPtr(const TSControlPanel self);
TS_CAPI uint32_t TS_CCALL tsControlPanel_getCountPtr(const TSControlPanel self);
TS_CAPI const void* TS_CCALL tsControlPanel_getInternalPtr(const TSControlPanel self);
TS_CAPI bool_t TS_CCALL tsControlPanel_equalControlRectPtr(const TSControlPanel self, const TSControlRect base);
TS_CAPI TSControlPanel TS_CCALL tsControlPanel_castControlRectPtr(TSControlRect base);
TS_CAPI TSControlRect TS_CCALL tsControlPanel_baseControlRectPtr(TSControlPanel self);
TS_CAPI bool_t TS_CCALL tsControlPanel_equalControlPtr(const TSControlPanel self, const TSControl base);
TS_CAPI TSControlPanel TS_CCALL tsControlPanel_castControlPtr(TSControl base);
TS_CAPI TSControl TS_CCALL tsControlPanel_baseControlPtr(TSControlPanel self);
TS_CAPI void TS_CCALL tsControlPanel_setColumns(TSControlPanel self, uint32_t columns);
TS_CAPI uint32_t TS_CCALL tsControlPanel_getColumns(TSControlPanel self);
TS_CAPI void TS_CCALL tsControlPanel_setSpacing_cV2(TSControlPanel self, const TSVector2f *spacing);
TS_CAPI void TS_CCALL tsControlPanel_setSpacing_ff(TSControlPanel self, float32_t x, float32_t y);
TS_CAPI TSVector2f TS_CCALL tsControlPanel_getSpacing(TSControlPanel self);
TS_CAPI void TS_CCALL tsControlPanel_setColumnRatio(TSControlPanel self, uint32_t index, float32_t ratio);
TS_CAPI float32_t TS_CCALL tsControlPanel_getColumnRatio(TSControlPanel self, uint32_t index);
TS_CAPI TSVector2f TS_CCALL tsControlPanel_getControlsSize(TSControlPanel self);

/// Tellusim::ControlDialog
typedef void (*TSControlDialogUpdatedCallback)(TSControlDialog a0, void *data_);
TS_CAPI TSControlDialog TS_CCALL tsControlDialog_new(void);
TS_CAPI TSControlDialog TS_CCALL tsControlDialog_new_C(TSControl *parent);
TS_CAPI TSControlDialog TS_CCALL tsControlDialog_new_Cu(TSControl *parent, uint32_t columns);
TS_CAPI TSControlDialog TS_CCALL tsControlDialog_new_Cuff(TSControl *parent, uint32_t columns, float32_t x, float32_t y);
TS_CAPI void TS_CCALL tsControlDialog_delete(TSControlDialog self);
TS_CAPI bool_t TS_CCALL tsControlDialog_equalPtr(const TSControlDialog self, const TSControlDialog ptr);
TS_CAPI TSControlDialog TS_CCALL tsControlDialog_copyPtr(const TSControlDialog self);
TS_CAPI TSControlDialog TS_CCALL tsControlDialog_clonePtr(const TSControlDialog self);
TS_CAPI void TS_CCALL tsControlDialog_clearPtr(TSControlDialog self);
TS_CAPI void TS_CCALL tsControlDialog_destroyPtr(TSControlDialog self);
TS_CAPI void TS_CCALL tsControlDialog_acquirePtr(TSControlDialog self);
TS_CAPI void TS_CCALL tsControlDialog_unacquirePtr(TSControlDialog self);
TS_CAPI bool_t TS_CCALL tsControlDialog_isValidPtr(const TSControlDialog self);
TS_CAPI bool_t TS_CCALL tsControlDialog_isOwnerPtr(const TSControlDialog self);
TS_CAPI bool_t TS_CCALL tsControlDialog_isConstPtr(const TSControlDialog self);
TS_CAPI uint32_t TS_CCALL tsControlDialog_getCountPtr(const TSControlDialog self);
TS_CAPI const void* TS_CCALL tsControlDialog_getInternalPtr(const TSControlDialog self);
TS_CAPI bool_t TS_CCALL tsControlDialog_equalControlPanelPtr(const TSControlDialog self, const TSControlPanel base);
TS_CAPI TSControlDialog TS_CCALL tsControlDialog_castControlPanelPtr(TSControlPanel base);
TS_CAPI TSControlPanel TS_CCALL tsControlDialog_baseControlPanelPtr(TSControlDialog self);
TS_CAPI bool_t TS_CCALL tsControlDialog_equalControlRectPtr(const TSControlDialog self, const TSControlRect base);
TS_CAPI TSControlDialog TS_CCALL tsControlDialog_castControlRectPtr(TSControlRect base);
TS_CAPI TSControlRect TS_CCALL tsControlDialog_baseControlRectPtr(TSControlDialog self);
TS_CAPI bool_t TS_CCALL tsControlDialog_equalControlPtr(const TSControlDialog self, const TSControl base);
TS_CAPI TSControlDialog TS_CCALL tsControlDialog_castControlPtr(TSControl base);
TS_CAPI TSControl TS_CCALL tsControlDialog_baseControlPtr(TSControlDialog self);
TS_CAPI void TS_CCALL tsControlDialog_setConstrained(TSControlDialog self, bool_t constrained);
TS_CAPI bool_t TS_CCALL tsControlDialog_isConstrained(TSControlDialog self);
TS_CAPI void TS_CCALL tsControlDialog_setResizable(TSControlDialog self, bool_t resizable);
TS_CAPI bool_t TS_CCALL tsControlDialog_isResizable(TSControlDialog self);
TS_CAPI void TS_CCALL tsControlDialog_setMoveable(TSControlDialog self, bool_t moveable);
TS_CAPI bool_t TS_CCALL tsControlDialog_isMoveable(TSControlDialog self);
TS_CAPI void TS_CCALL tsControlDialog_setResizeArea(TSControlDialog self, float32_t area);
TS_CAPI float32_t TS_CCALL tsControlDialog_getResizeArea(TSControlDialog self);
TS_CAPI TS_ControlAlign TS_CCALL tsControlDialog_getResizeAlign(TSControlDialog self);
TS_CAPI bool_t TS_CCALL tsControlDialog_hasResizeAlign(TSControlDialog self, TS_ControlAlign align);
TS_CAPI bool_t TS_CCALL tsControlDialog_hasResizeAligns(TSControlDialog self, TS_ControlAlign aligns);
TS_CAPI void TS_CCALL tsControlDialog_setMousePosition(TSControlDialog self, const TSVector2f *position);
TS_CAPI TSVector2f TS_CCALL tsControlDialog_getMousePosition(TSControlDialog self);
TS_CAPI void TS_CCALL tsControlDialog_setUpdatedCallback(TSControlDialog self, const TSControlDialogUpdatedCallback func, void *data_);
TS_CAPI bool_t TS_CCALL tsControlDialog_isUpdated(TSControlDialog self);

/// Tellusim::ControlWindow
TS_CAPI TSControlWindow TS_CCALL tsControlWindow_new(void);
TS_CAPI TSControlWindow TS_CCALL tsControlWindow_new_CRWW(TSControlRoot *root, TSWindow parent, TSWindow window);
TS_CAPI TSControlWindow TS_CCALL tsControlWindow_new_CRWWu(TSControlRoot *root, TSWindow parent, TSWindow window, uint32_t columns);
TS_CAPI TSControlWindow TS_CCALL tsControlWindow_new_CRWWuff(TSControlRoot *root, TSWindow parent, TSWindow window, uint32_t columns, float32_t x, float32_t y);
TS_CAPI void TS_CCALL tsControlWindow_delete(TSControlWindow self);
TS_CAPI bool_t TS_CCALL tsControlWindow_equalPtr(const TSControlWindow self, const TSControlWindow ptr);
TS_CAPI TSControlWindow TS_CCALL tsControlWindow_copyPtr(const TSControlWindow self);
TS_CAPI TSControlWindow TS_CCALL tsControlWindow_clonePtr(const TSControlWindow self);
TS_CAPI void TS_CCALL tsControlWindow_clearPtr(TSControlWindow self);
TS_CAPI void TS_CCALL tsControlWindow_destroyPtr(TSControlWindow self);
TS_CAPI void TS_CCALL tsControlWindow_acquirePtr(TSControlWindow self);
TS_CAPI void TS_CCALL tsControlWindow_unacquirePtr(TSControlWindow self);
TS_CAPI bool_t TS_CCALL tsControlWindow_isValidPtr(const TSControlWindow self);
TS_CAPI bool_t TS_CCALL tsControlWindow_isOwnerPtr(const TSControlWindow self);
TS_CAPI bool_t TS_CCALL tsControlWindow_isConstPtr(const TSControlWindow self);
TS_CAPI uint32_t TS_CCALL tsControlWindow_getCountPtr(const TSControlWindow self);
TS_CAPI const void* TS_CCALL tsControlWindow_getInternalPtr(const TSControlWindow self);
TS_CAPI bool_t TS_CCALL tsControlWindow_equalControlDialogPtr(const TSControlWindow self, const TSControlDialog base);
TS_CAPI TSControlWindow TS_CCALL tsControlWindow_castControlDialogPtr(TSControlDialog base);
TS_CAPI TSControlDialog TS_CCALL tsControlWindow_baseControlDialogPtr(TSControlWindow self);
TS_CAPI bool_t TS_CCALL tsControlWindow_equalControlPanelPtr(const TSControlWindow self, const TSControlPanel base);
TS_CAPI TSControlWindow TS_CCALL tsControlWindow_castControlPanelPtr(TSControlPanel base);
TS_CAPI TSControlPanel TS_CCALL tsControlWindow_baseControlPanelPtr(TSControlWindow self);
TS_CAPI bool_t TS_CCALL tsControlWindow_equalControlRectPtr(const TSControlWindow self, const TSControlRect base);
TS_CAPI TSControlWindow TS_CCALL tsControlWindow_castControlRectPtr(TSControlRect base);
TS_CAPI TSControlRect TS_CCALL tsControlWindow_baseControlRectPtr(TSControlWindow self);
TS_CAPI bool_t TS_CCALL tsControlWindow_equalControlPtr(const TSControlWindow self, const TSControl base);
TS_CAPI TSControlWindow TS_CCALL tsControlWindow_castControlPtr(TSControl base);
TS_CAPI TSControl TS_CCALL tsControlWindow_baseControlPtr(TSControlWindow self);
TS_CAPI TSWindow TS_CCALL tsControlWindow_getParentWindow(TSControlWindow self);
TS_CAPI TSWindow TS_CCALL tsControlWindow_getDialogWindow(TSControlWindow self);

/// Tellusim::ControlCheck
typedef void (*TSControlCheckClickedCallback)(TSControlCheck a0, void *data_);
TS_CAPI TSControlCheck TS_CCALL tsControlCheck_new(void);
TS_CAPI TSControlCheck TS_CCALL tsControlCheck_new_C(TSControl *parent);
TS_CAPI TSControlCheck TS_CCALL tsControlCheck_new_Cs(TSControl *parent, const char *text);
TS_CAPI TSControlCheck TS_CCALL tsControlCheck_new_CcS(TSControl *parent, const TSString text);
TS_CAPI TSControlCheck TS_CCALL tsControlCheck_new_Csb(TSControl *parent, const char *text, bool_t checked);
TS_CAPI TSControlCheck TS_CCALL tsControlCheck_new_CcSb(TSControl *parent, const TSString text, bool_t checked);
TS_CAPI void TS_CCALL tsControlCheck_delete(TSControlCheck self);
TS_CAPI bool_t TS_CCALL tsControlCheck_equalPtr(const TSControlCheck self, const TSControlCheck ptr);
TS_CAPI TSControlCheck TS_CCALL tsControlCheck_copyPtr(const TSControlCheck self);
TS_CAPI TSControlCheck TS_CCALL tsControlCheck_clonePtr(const TSControlCheck self);
TS_CAPI void TS_CCALL tsControlCheck_clearPtr(TSControlCheck self);
TS_CAPI void TS_CCALL tsControlCheck_destroyPtr(TSControlCheck self);
TS_CAPI void TS_CCALL tsControlCheck_acquirePtr(TSControlCheck self);
TS_CAPI void TS_CCALL tsControlCheck_unacquirePtr(TSControlCheck self);
TS_CAPI bool_t TS_CCALL tsControlCheck_isValidPtr(const TSControlCheck self);
TS_CAPI bool_t TS_CCALL tsControlCheck_isOwnerPtr(const TSControlCheck self);
TS_CAPI bool_t TS_CCALL tsControlCheck_isConstPtr(const TSControlCheck self);
TS_CAPI uint32_t TS_CCALL tsControlCheck_getCountPtr(const TSControlCheck self);
TS_CAPI const void* TS_CCALL tsControlCheck_getInternalPtr(const TSControlCheck self);
TS_CAPI bool_t TS_CCALL tsControlCheck_equalControlTextPtr(const TSControlCheck self, const TSControlText base);
TS_CAPI TSControlCheck TS_CCALL tsControlCheck_castControlTextPtr(TSControlText base);
TS_CAPI TSControlText TS_CCALL tsControlCheck_baseControlTextPtr(TSControlCheck self);
TS_CAPI bool_t TS_CCALL tsControlCheck_equalControlPtr(const TSControlCheck self, const TSControl base);
TS_CAPI TSControlCheck TS_CCALL tsControlCheck_castControlPtr(TSControl base);
TS_CAPI TSControl TS_CCALL tsControlCheck_baseControlPtr(TSControlCheck self);
TS_CAPI void TS_CCALL tsControlCheck_setCheckText_s(TSControlCheck self, const char *text);
TS_CAPI void TS_CCALL tsControlCheck_setCheckText_cS(TSControlCheck self, const TSString text);
TS_CAPI TSString TS_CCALL tsControlCheck_getCheckText(TSControlCheck self);
TS_CAPI void TS_CCALL tsControlCheck_setCheckColor(TSControlCheck self, const TSColor *color);
TS_CAPI TSColor TS_CCALL tsControlCheck_getCheckColor(TSControlCheck self);
TS_CAPI void TS_CCALL tsControlCheck_setCheckedColor(TSControlCheck self, const TSColor *color);
TS_CAPI TSColor TS_CCALL tsControlCheck_getCheckedColor(TSControlCheck self);
TS_CAPI bool_t TS_CCALL tsControlCheck_switchChecked(TSControlCheck self, bool_t callback);
TS_CAPI void TS_CCALL tsControlCheck_setChecked(TSControlCheck self, bool_t checked, bool_t callback);
TS_CAPI bool_t TS_CCALL tsControlCheck_isChecked(TSControlCheck self);
TS_CAPI void TS_CCALL tsControlCheck_setClickedCallback(TSControlCheck self, const TSControlCheckClickedCallback func, void *data_);
TS_CAPI bool_t TS_CCALL tsControlCheck_isClicked(TSControlCheck self);
TS_CAPI TSCanvasMesh TS_CCALL tsControlCheck_getCanvasMesh(TSControlCheck self);

/// Tellusim::ControlCombo
typedef void (*TSControlComboClickedCallback)(TSControlCombo a0, void *data_);
typedef void (*TSControlComboChangedCallback)(TSControlCombo a0, void *data_);
TS_CAPI TSControlCombo TS_CCALL tsControlCombo_new(void);
TS_CAPI TSControlCombo TS_CCALL tsControlCombo_new_C(TSControl *parent);
TS_CAPI void TS_CCALL tsControlCombo_delete(TSControlCombo self);
TS_CAPI bool_t TS_CCALL tsControlCombo_equalPtr(const TSControlCombo self, const TSControlCombo ptr);
TS_CAPI TSControlCombo TS_CCALL tsControlCombo_copyPtr(const TSControlCombo self);
TS_CAPI TSControlCombo TS_CCALL tsControlCombo_clonePtr(const TSControlCombo self);
TS_CAPI void TS_CCALL tsControlCombo_clearPtr(TSControlCombo self);
TS_CAPI void TS_CCALL tsControlCombo_destroyPtr(TSControlCombo self);
TS_CAPI void TS_CCALL tsControlCombo_acquirePtr(TSControlCombo self);
TS_CAPI void TS_CCALL tsControlCombo_unacquirePtr(TSControlCombo self);
TS_CAPI bool_t TS_CCALL tsControlCombo_isValidPtr(const TSControlCombo self);
TS_CAPI bool_t TS_CCALL tsControlCombo_isOwnerPtr(const TSControlCombo self);
TS_CAPI bool_t TS_CCALL tsControlCombo_isConstPtr(const TSControlCombo self);
TS_CAPI uint32_t TS_CCALL tsControlCombo_getCountPtr(const TSControlCombo self);
TS_CAPI const void* TS_CCALL tsControlCombo_getInternalPtr(const TSControlCombo self);
TS_CAPI bool_t TS_CCALL tsControlCombo_equalControlTextPtr(const TSControlCombo self, const TSControlText base);
TS_CAPI TSControlCombo TS_CCALL tsControlCombo_castControlTextPtr(TSControlText base);
TS_CAPI TSControlText TS_CCALL tsControlCombo_baseControlTextPtr(TSControlCombo self);
TS_CAPI bool_t TS_CCALL tsControlCombo_equalControlPtr(const TSControlCombo self, const TSControl base);
TS_CAPI TSControlCombo TS_CCALL tsControlCombo_castControlPtr(TSControl base);
TS_CAPI TSControl TS_CCALL tsControlCombo_baseControlPtr(TSControlCombo self);
TS_CAPI void TS_CCALL tsControlCombo_setTextEnabled(TSControlCombo self, bool_t enabled);
TS_CAPI bool_t TS_CCALL tsControlCombo_isTextEnabled(TSControlCombo self);
TS_CAPI void TS_CCALL tsControlCombo_setMultiSelection(TSControlCombo self, bool_t multi_selection);
TS_CAPI bool_t TS_CCALL tsControlCombo_isMultiSelection(TSControlCombo self);
TS_CAPI void TS_CCALL tsControlCombo_setComboText_s(TSControlCombo self, const char *text);
TS_CAPI void TS_CCALL tsControlCombo_setComboText_cS(TSControlCombo self, const TSString text);
TS_CAPI TSString TS_CCALL tsControlCombo_getComboText(TSControlCombo self);
TS_CAPI void TS_CCALL tsControlCombo_setComboColor(TSControlCombo self, const TSColor *color);
TS_CAPI TSColor TS_CCALL tsControlCombo_getComboColor(TSControlCombo self);
TS_CAPI void TS_CCALL tsControlCombo_setItemsSpacing(TSControlCombo self, float32_t spacing);
TS_CAPI float32_t TS_CCALL tsControlCombo_getItemsSpacing(TSControlCombo self);
TS_CAPI void TS_CCALL tsControlCombo_clearItems(TSControlCombo self);
TS_CAPI uint32_t TS_CCALL tsControlCombo_addItem_s(TSControlCombo self, const char *text);
TS_CAPI uint32_t TS_CCALL tsControlCombo_addItem_cS(TSControlCombo self, const TSString text);
TS_CAPI void TS_CCALL tsControlCombo_addItem_us(TSControlCombo self, uint32_t index, const char *text);
TS_CAPI void TS_CCALL tsControlCombo_addItem_ucS(TSControlCombo self, uint32_t index, const TSString text);
TS_CAPI void TS_CCALL tsControlCombo_removeItem(TSControlCombo self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsControlCombo_getNumItems(TSControlCombo self);
TS_CAPI bool_t TS_CCALL tsControlCombo_switchItemSelected(TSControlCombo self, uint32_t index);
TS_CAPI void TS_CCALL tsControlCombo_setItemSelected(TSControlCombo self, uint32_t index, bool_t selected);
TS_CAPI bool_t TS_CCALL tsControlCombo_isItemSelected(TSControlCombo self, uint32_t index);
TS_CAPI void TS_CCALL tsControlCombo_setItemText_us(TSControlCombo self, uint32_t index, const char *text);
TS_CAPI void TS_CCALL tsControlCombo_setItemText_ucS(TSControlCombo self, uint32_t index, const TSString text);
TS_CAPI TSString TS_CCALL tsControlCombo_getItemText(TSControlCombo self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsControlCombo_findItemText_cs(TSControlCombo self, const char *text);
TS_CAPI uint32_t TS_CCALL tsControlCombo_findItemText_ccS(TSControlCombo self, const TSString text);
TS_CAPI void TS_CCALL tsControlCombo_setItemColor(TSControlCombo self, uint32_t index, const TSColor *color);
TS_CAPI TSColor TS_CCALL tsControlCombo_getItemColor(TSControlCombo self, uint32_t index);
TS_CAPI void TS_CCALL tsControlCombo_setCurrentIndex(TSControlCombo self, uint32_t index, bool_t callback);
TS_CAPI bool_t TS_CCALL tsControlCombo_setCurrentText_sb(TSControlCombo self, const char *text, bool_t callback);
TS_CAPI bool_t TS_CCALL tsControlCombo_setCurrentText_cSb(TSControlCombo self, const TSString text, bool_t callback);
TS_CAPI uint32_t TS_CCALL tsControlCombo_getCurrentIndex(TSControlCombo self);
TS_CAPI TSString TS_CCALL tsControlCombo_getCurrentText(TSControlCombo self);
TS_CAPI void TS_CCALL tsControlCombo_setClickedCallback(TSControlCombo self, const TSControlComboClickedCallback func, void *data_);
TS_CAPI bool_t TS_CCALL tsControlCombo_isClicked(TSControlCombo self);
TS_CAPI void TS_CCALL tsControlCombo_setChangedCallback(TSControlCombo self, const TSControlComboChangedCallback func, void *data_);
TS_CAPI bool_t TS_CCALL tsControlCombo_isChanged(TSControlCombo self);
TS_CAPI TSCanvasMesh TS_CCALL tsControlCombo_getCanvasMesh(TSControlCombo self);

/// Tellusim::ControlButton
typedef void (*TSControlButtonPressedCallback)(TSControlButton a0, float32_t x, float32_t y, void *data_);
typedef void (*TSControlButtonReleasedCallback)(TSControlButton a0, float32_t x, float32_t y, void *data_);
typedef void (*TSControlButtonClickedCallback)(TSControlButton a0, void *data_);
TS_CAPI TSControlButton TS_CCALL tsControlButton_new(void);
TS_CAPI TSControlButton TS_CCALL tsControlButton_new_C(TSControl *parent);
TS_CAPI TSControlButton TS_CCALL tsControlButton_new_Cs(TSControl *parent, const char *text);
TS_CAPI TSControlButton TS_CCALL tsControlButton_new_CcS(TSControl *parent, const TSString text);
TS_CAPI void TS_CCALL tsControlButton_delete(TSControlButton self);
TS_CAPI bool_t TS_CCALL tsControlButton_equalPtr(const TSControlButton self, const TSControlButton ptr);
TS_CAPI TSControlButton TS_CCALL tsControlButton_copyPtr(const TSControlButton self);
TS_CAPI TSControlButton TS_CCALL tsControlButton_clonePtr(const TSControlButton self);
TS_CAPI void TS_CCALL tsControlButton_clearPtr(TSControlButton self);
TS_CAPI void TS_CCALL tsControlButton_destroyPtr(TSControlButton self);
TS_CAPI void TS_CCALL tsControlButton_acquirePtr(TSControlButton self);
TS_CAPI void TS_CCALL tsControlButton_unacquirePtr(TSControlButton self);
TS_CAPI bool_t TS_CCALL tsControlButton_isValidPtr(const TSControlButton self);
TS_CAPI bool_t TS_CCALL tsControlButton_isOwnerPtr(const TSControlButton self);
TS_CAPI bool_t TS_CCALL tsControlButton_isConstPtr(const TSControlButton self);
TS_CAPI uint32_t TS_CCALL tsControlButton_getCountPtr(const TSControlButton self);
TS_CAPI const void* TS_CCALL tsControlButton_getInternalPtr(const TSControlButton self);
TS_CAPI bool_t TS_CCALL tsControlButton_equalControlTextPtr(const TSControlButton self, const TSControlText base);
TS_CAPI TSControlButton TS_CCALL tsControlButton_castControlTextPtr(TSControlText base);
TS_CAPI TSControlText TS_CCALL tsControlButton_baseControlTextPtr(TSControlButton self);
TS_CAPI bool_t TS_CCALL tsControlButton_equalControlPtr(const TSControlButton self, const TSControl base);
TS_CAPI TSControlButton TS_CCALL tsControlButton_castControlPtr(TSControl base);
TS_CAPI TSControl TS_CCALL tsControlButton_baseControlPtr(TSControlButton self);
TS_CAPI void TS_CCALL tsControlButton_setBackground(TSControlButton self, bool_t background);
TS_CAPI bool_t TS_CCALL tsControlButton_getBackground(TSControlButton self);
TS_CAPI void TS_CCALL tsControlButton_setButtonMode(TSControlButton self, TS_CanvasElementMode mode);
TS_CAPI TS_CanvasElementMode TS_CCALL tsControlButton_getButtonMode(TSControlButton self);
TS_CAPI void TS_CCALL tsControlButton_setButtonRadius(TSControlButton self, float32_t radius);
TS_CAPI float32_t TS_CCALL tsControlButton_getButtonRadius(TSControlButton self);
TS_CAPI void TS_CCALL tsControlButton_setButtonColor(TSControlButton self, const TSColor *color);
TS_CAPI TSColor TS_CCALL tsControlButton_getButtonColor(TSControlButton self);
TS_CAPI void TS_CCALL tsControlButton_setStrokeStyle(TSControlButton self, const TSStrokeStyle *style);
TS_CAPI TSStrokeStyle TS_CCALL tsControlButton_getStrokeStyleConst(TSControlButton self);
TS_CAPI TSStrokeStyle TS_CCALL tsControlButton_getStrokeStyle_c(TSControlButton self);
TS_CAPI TSStrokeStyle TS_CCALL tsControlButton_getStrokeStyle(TSControlButton self);
TS_CAPI void TS_CCALL tsControlButton_setGradientStyle(TSControlButton self, const TSGradientStyle *style);
TS_CAPI TSGradientStyle TS_CCALL tsControlButton_getGradientStyleConst(TSControlButton self);
TS_CAPI TSGradientStyle TS_CCALL tsControlButton_getGradientStyle_c(TSControlButton self);
TS_CAPI TSGradientStyle TS_CCALL tsControlButton_getGradientStyle(TSControlButton self);
TS_CAPI void TS_CCALL tsControlButton_setPressedCallback(TSControlButton self, const TSControlButtonPressedCallback func, void *data_);
TS_CAPI bool_t TS_CCALL tsControlButton_isPressed(TSControlButton self);
TS_CAPI void TS_CCALL tsControlButton_setReleasedCallback(TSControlButton self, const TSControlButtonReleasedCallback func, void *data_);
TS_CAPI bool_t TS_CCALL tsControlButton_isReleased(TSControlButton self);
TS_CAPI void TS_CCALL tsControlButton_setClickedCallback(TSControlButton self, const TSControlButtonClickedCallback func, void *data_);
TS_CAPI bool_t TS_CCALL tsControlButton_isClicked(TSControlButton self);
TS_CAPI TSCanvasRect TS_CCALL tsControlButton_getCanvasRect(TSControlButton self);
TS_CAPI TSCanvasMesh TS_CCALL tsControlButton_getCanvasMesh(TSControlButton self);

/// Tellusim::ControlSlider
typedef TSString (*TSControlSliderFormatCallback)(TSControlSlider a0, void *data_);
typedef void (*TSControlSliderPressedCallback)(TSControlSlider a0, void *data_);
typedef void (*TSControlSliderReleasedCallback)(TSControlSlider a0, void *data_);
typedef void (*TSControlSliderClickedCallback)(TSControlSlider a0, void *data_);
typedef void (*TSControlSliderChangedCallback)(TSControlSlider a0, void *data_);
TS_CAPI TSControlSlider TS_CCALL tsControlSlider_new(void);
TS_CAPI TSControlSlider TS_CCALL tsControlSlider_new_C(TSControl *parent);
TS_CAPI TSControlSlider TS_CCALL tsControlSlider_new_Cs(TSControl *parent, const char *text);
TS_CAPI TSControlSlider TS_CCALL tsControlSlider_new_CcS(TSControl *parent, const TSString text);
TS_CAPI TSControlSlider TS_CCALL tsControlSlider_new_Csu(TSControl *parent, const char *text, uint32_t digits);
TS_CAPI TSControlSlider TS_CCALL tsControlSlider_new_Csuf64(TSControl *parent, const char *text, uint32_t digits, float64_t value);
TS_CAPI TSControlSlider TS_CCALL tsControlSlider_new_Csuf64f64f64(TSControl *parent, const char *text, uint32_t digits, float64_t value, float64_t min, float64_t max);
TS_CAPI TSControlSlider TS_CCALL tsControlSlider_new_Csf64f64f64(TSControl *parent, const char *text, float64_t value, float64_t min, float64_t max);
TS_CAPI TSControlSlider TS_CCALL tsControlSlider_new_Csuuu(TSControl *parent, const char *text, uint32_t value, uint32_t min, uint32_t max);
TS_CAPI TSControlSlider TS_CCALL tsControlSlider_new_Csiii(TSControl *parent, const char *text, int32_t value, int32_t min, int32_t max);
TS_CAPI void TS_CCALL tsControlSlider_delete(TSControlSlider self);
TS_CAPI bool_t TS_CCALL tsControlSlider_equalPtr(const TSControlSlider self, const TSControlSlider ptr);
TS_CAPI TSControlSlider TS_CCALL tsControlSlider_copyPtr(const TSControlSlider self);
TS_CAPI TSControlSlider TS_CCALL tsControlSlider_clonePtr(const TSControlSlider self);
TS_CAPI void TS_CCALL tsControlSlider_clearPtr(TSControlSlider self);
TS_CAPI void TS_CCALL tsControlSlider_destroyPtr(TSControlSlider self);
TS_CAPI void TS_CCALL tsControlSlider_acquirePtr(TSControlSlider self);
TS_CAPI void TS_CCALL tsControlSlider_unacquirePtr(TSControlSlider self);
TS_CAPI bool_t TS_CCALL tsControlSlider_isValidPtr(const TSControlSlider self);
TS_CAPI bool_t TS_CCALL tsControlSlider_isOwnerPtr(const TSControlSlider self);
TS_CAPI bool_t TS_CCALL tsControlSlider_isConstPtr(const TSControlSlider self);
TS_CAPI uint32_t TS_CCALL tsControlSlider_getCountPtr(const TSControlSlider self);
TS_CAPI const void* TS_CCALL tsControlSlider_getInternalPtr(const TSControlSlider self);
TS_CAPI bool_t TS_CCALL tsControlSlider_equalControlTextPtr(const TSControlSlider self, const TSControlText base);
TS_CAPI TSControlSlider TS_CCALL tsControlSlider_castControlTextPtr(TSControlText base);
TS_CAPI TSControlText TS_CCALL tsControlSlider_baseControlTextPtr(TSControlSlider self);
TS_CAPI bool_t TS_CCALL tsControlSlider_equalControlPtr(const TSControlSlider self, const TSControl base);
TS_CAPI TSControlSlider TS_CCALL tsControlSlider_castControlPtr(TSControl base);
TS_CAPI TSControl TS_CCALL tsControlSlider_baseControlPtr(TSControlSlider self);
TS_CAPI void TS_CCALL tsControlSlider_setConstrained(TSControlSlider self, bool_t constrained);
TS_CAPI bool_t TS_CCALL tsControlSlider_isConstrained(TSControlSlider self);
TS_CAPI void TS_CCALL tsControlSlider_setTextEnabled(TSControlSlider self, bool_t enabled);
TS_CAPI bool_t TS_CCALL tsControlSlider_isTextEnabled(TSControlSlider self);
TS_CAPI void TS_CCALL tsControlSlider_setSliderColor(TSControlSlider self, const TSColor *color);
TS_CAPI TSColor TS_CCALL tsControlSlider_getSliderColor(TSControlSlider self);
TS_CAPI void TS_CCALL tsControlSlider_setDigits(TSControlSlider self, uint32_t digits);
TS_CAPI uint32_t TS_CCALL tsControlSlider_getDigits(TSControlSlider self);
TS_CAPI void TS_CCALL tsControlSlider_setStep(TSControlSlider self, float64_t step);
TS_CAPI float64_t TS_CCALL tsControlSlider_getStep(TSControlSlider self);
TS_CAPI void TS_CCALL tsControlSlider_setBase(TSControlSlider self, float64_t base);
TS_CAPI float64_t TS_CCALL tsControlSlider_getBase(TSControlSlider self);
TS_CAPI void TS_CCALL tsControlSlider_setFormat_s(TSControlSlider self, const char *format);
TS_CAPI void TS_CCALL tsControlSlider_setFormat_cS(TSControlSlider self, const TSString format);
TS_CAPI TSString TS_CCALL tsControlSlider_getFormat(TSControlSlider self);
TS_CAPI void TS_CCALL tsControlSlider_setValue(TSControlSlider self, float64_t value, bool_t callback, bool_t exponent);
TS_CAPI float64_t TS_CCALL tsControlSlider_getValue(TSControlSlider self, bool_t exponent);
TS_CAPI float32_t TS_CCALL tsControlSlider_getValuef32(TSControlSlider self, bool_t exponent);
TS_CAPI uint32_t TS_CCALL tsControlSlider_getValueu32(TSControlSlider self, bool_t exponent);
TS_CAPI int32_t TS_CCALL tsControlSlider_getValuei32(TSControlSlider self, bool_t exponent);
TS_CAPI void TS_CCALL tsControlSlider_setRange(TSControlSlider self, float64_t min, float64_t max, bool_t exponent);
TS_CAPI float64_t TS_CCALL tsControlSlider_getMinRange(TSControlSlider self, bool_t exponent);
TS_CAPI float64_t TS_CCALL tsControlSlider_getMaxRange(TSControlSlider self, bool_t exponent);
TS_CAPI void TS_CCALL tsControlSlider_setHandleSize(TSControlSlider self, float32_t size);
TS_CAPI float32_t TS_CCALL tsControlSlider_getHandleSize(TSControlSlider self);
TS_CAPI void TS_CCALL tsControlSlider_setFormatCallback(TSControlSlider self, const TSControlSliderFormatCallback func, void *data_);
TS_CAPI void TS_CCALL tsControlSlider_setPressedCallback(TSControlSlider self, const TSControlSliderPressedCallback func, void *data_);
TS_CAPI bool_t TS_CCALL tsControlSlider_isPressed(TSControlSlider self);
TS_CAPI void TS_CCALL tsControlSlider_setReleasedCallback(TSControlSlider self, const TSControlSliderReleasedCallback func, void *data_);
TS_CAPI bool_t TS_CCALL tsControlSlider_isReleased(TSControlSlider self);
TS_CAPI void TS_CCALL tsControlSlider_setClickedCallback(TSControlSlider self, const TSControlSliderClickedCallback func, void *data_);
TS_CAPI void TS_CCALL tsControlSlider_setClicked2Callback(TSControlSlider self, const TSControlSliderClickedCallback func, void *data_);
TS_CAPI void TS_CCALL tsControlSlider_setClickedRightCallback(TSControlSlider self, const TSControlSliderClickedCallback func, void *data_);
TS_CAPI bool_t TS_CCALL tsControlSlider_isClicked(TSControlSlider self);
TS_CAPI void TS_CCALL tsControlSlider_setChangedCallback(TSControlSlider self, const TSControlSliderChangedCallback func, void *data_);
TS_CAPI bool_t TS_CCALL tsControlSlider_isChanged(TSControlSlider self, bool_t clear);
TS_CAPI TSCanvasMesh TS_CCALL tsControlSlider_getCanvasMesh(TSControlSlider self);

/// Tellusim::ControlScroll
typedef void (*TSControlScrollClickedCallback)(TSControlScroll a0, void *data_);
typedef void (*TSControlScrollChangedCallback)(TSControlScroll a0, void *data_);
TS_CAPI TSControlScroll TS_CCALL tsControlScroll_new(void);
TS_CAPI TSControlScroll TS_CCALL tsControlScroll_new_Cb(TSControl *parent, bool_t vertical);
TS_CAPI TSControlScroll TS_CCALL tsControlScroll_new_Cf64b(TSControl *parent, float64_t value, bool_t vertical);
TS_CAPI TSControlScroll TS_CCALL tsControlScroll_new_Cf64f64f64b(TSControl *parent, float64_t value, float64_t frame, float64_t range, bool_t vertical);
TS_CAPI TSControlScroll TS_CCALL tsControlScroll_new_Cuuub(TSControl *parent, uint32_t value, uint32_t frame, uint32_t range, bool_t vertical);
TS_CAPI TSControlScroll TS_CCALL tsControlScroll_new_Ciiib(TSControl *parent, int32_t value, int32_t frame, int32_t range, bool_t vertical);
TS_CAPI void TS_CCALL tsControlScroll_delete(TSControlScroll self);
TS_CAPI bool_t TS_CCALL tsControlScroll_equalPtr(const TSControlScroll self, const TSControlScroll ptr);
TS_CAPI TSControlScroll TS_CCALL tsControlScroll_copyPtr(const TSControlScroll self);
TS_CAPI TSControlScroll TS_CCALL tsControlScroll_clonePtr(const TSControlScroll self);
TS_CAPI void TS_CCALL tsControlScroll_clearPtr(TSControlScroll self);
TS_CAPI void TS_CCALL tsControlScroll_destroyPtr(TSControlScroll self);
TS_CAPI void TS_CCALL tsControlScroll_acquirePtr(TSControlScroll self);
TS_CAPI void TS_CCALL tsControlScroll_unacquirePtr(TSControlScroll self);
TS_CAPI bool_t TS_CCALL tsControlScroll_isValidPtr(const TSControlScroll self);
TS_CAPI bool_t TS_CCALL tsControlScroll_isOwnerPtr(const TSControlScroll self);
TS_CAPI bool_t TS_CCALL tsControlScroll_isConstPtr(const TSControlScroll self);
TS_CAPI uint32_t TS_CCALL tsControlScroll_getCountPtr(const TSControlScroll self);
TS_CAPI const void* TS_CCALL tsControlScroll_getInternalPtr(const TSControlScroll self);
TS_CAPI bool_t TS_CCALL tsControlScroll_equalControlTextPtr(const TSControlScroll self, const TSControlText base);
TS_CAPI TSControlScroll TS_CCALL tsControlScroll_castControlTextPtr(TSControlText base);
TS_CAPI TSControlText TS_CCALL tsControlScroll_baseControlTextPtr(TSControlScroll self);
TS_CAPI bool_t TS_CCALL tsControlScroll_equalControlPtr(const TSControlScroll self, const TSControl base);
TS_CAPI TSControlScroll TS_CCALL tsControlScroll_castControlPtr(TSControl base);
TS_CAPI TSControl TS_CCALL tsControlScroll_baseControlPtr(TSControlScroll self);
TS_CAPI void TS_CCALL tsControlScroll_setVertical(TSControlScroll self, bool_t vertical, bool_t text);
TS_CAPI bool_t TS_CCALL tsControlScroll_isHorizontal(TSControlScroll self);
TS_CAPI bool_t TS_CCALL tsControlScroll_isVertical(TSControlScroll self);
TS_CAPI void TS_CCALL tsControlScroll_setPrevText_s(TSControlScroll self, const char *text);
TS_CAPI void TS_CCALL tsControlScroll_setPrevText_cS(TSControlScroll self, const TSString text);
TS_CAPI TSString TS_CCALL tsControlScroll_getPrevText(TSControlScroll self);
TS_CAPI void TS_CCALL tsControlScroll_setNextText_s(TSControlScroll self, const char *text);
TS_CAPI void TS_CCALL tsControlScroll_setNextText_cS(TSControlScroll self, const TSString text);
TS_CAPI TSString TS_CCALL tsControlScroll_getNextText(TSControlScroll self);
TS_CAPI void TS_CCALL tsControlScroll_setScrollColor(TSControlScroll self, const TSColor *color);
TS_CAPI TSColor TS_CCALL tsControlScroll_getScrollColor(TSControlScroll self);
TS_CAPI void TS_CCALL tsControlScroll_setStep(TSControlScroll self, float64_t step);
TS_CAPI float64_t TS_CCALL tsControlScroll_getStep(TSControlScroll self);
TS_CAPI void TS_CCALL tsControlScroll_setValue(TSControlScroll self, float64_t value, bool_t callback);
TS_CAPI float64_t TS_CCALL tsControlScroll_getValue(TSControlScroll self);
TS_CAPI void TS_CCALL tsControlScroll_setFrame(TSControlScroll self, float64_t frame);
TS_CAPI float64_t TS_CCALL tsControlScroll_getFrame(TSControlScroll self);
TS_CAPI void TS_CCALL tsControlScroll_setRange(TSControlScroll self, float64_t range);
TS_CAPI float64_t TS_CCALL tsControlScroll_getRange(TSControlScroll self);
TS_CAPI void TS_CCALL tsControlScroll_setFrameAlign(TSControlScroll self, TS_ControlAlign align);
TS_CAPI TS_ControlAlign TS_CCALL tsControlScroll_getFrameAlign(TSControlScroll self);
TS_CAPI bool_t TS_CCALL tsControlScroll_hasFrameAlign(TSControlScroll self, TS_ControlAlign align);
TS_CAPI bool_t TS_CCALL tsControlScroll_hasFrameAligns(TSControlScroll self, TS_ControlAlign aligns);
TS_CAPI void TS_CCALL tsControlScroll_setClickedCallback(TSControlScroll self, const TSControlScrollClickedCallback func, void *data_);
TS_CAPI bool_t TS_CCALL tsControlScroll_isClicked(TSControlScroll self);
TS_CAPI void TS_CCALL tsControlScroll_setChangedCallback(TSControlScroll self, const TSControlScrollChangedCallback func, void *data_);
TS_CAPI bool_t TS_CCALL tsControlScroll_isChanged(TSControlScroll self, bool_t clear);
TS_CAPI TSCanvasMesh TS_CCALL tsControlScroll_getCanvasMesh(TSControlScroll self);

/// Tellusim::ControlSplit
TS_CAPI TSControlSplit TS_CCALL tsControlSplit_new(void);
TS_CAPI TSControlSplit TS_CCALL tsControlSplit_new_Cb(TSControl *parent, bool_t vertical);
TS_CAPI TSControlSplit TS_CCALL tsControlSplit_new_Cfb(TSControl *parent, float32_t value, bool_t vertical);
TS_CAPI void TS_CCALL tsControlSplit_delete(TSControlSplit self);
TS_CAPI bool_t TS_CCALL tsControlSplit_equalPtr(const TSControlSplit self, const TSControlSplit ptr);
TS_CAPI TSControlSplit TS_CCALL tsControlSplit_copyPtr(const TSControlSplit self);
TS_CAPI TSControlSplit TS_CCALL tsControlSplit_clonePtr(const TSControlSplit self);
TS_CAPI void TS_CCALL tsControlSplit_clearPtr(TSControlSplit self);
TS_CAPI void TS_CCALL tsControlSplit_destroyPtr(TSControlSplit self);
TS_CAPI void TS_CCALL tsControlSplit_acquirePtr(TSControlSplit self);
TS_CAPI void TS_CCALL tsControlSplit_unacquirePtr(TSControlSplit self);
TS_CAPI bool_t TS_CCALL tsControlSplit_isValidPtr(const TSControlSplit self);
TS_CAPI bool_t TS_CCALL tsControlSplit_isOwnerPtr(const TSControlSplit self);
TS_CAPI bool_t TS_CCALL tsControlSplit_isConstPtr(const TSControlSplit self);
TS_CAPI uint32_t TS_CCALL tsControlSplit_getCountPtr(const TSControlSplit self);
TS_CAPI const void* TS_CCALL tsControlSplit_getInternalPtr(const TSControlSplit self);
TS_CAPI bool_t TS_CCALL tsControlSplit_equalControlPtr(const TSControlSplit self, const TSControl base);
TS_CAPI TSControlSplit TS_CCALL tsControlSplit_castControlPtr(TSControl base);
TS_CAPI TSControl TS_CCALL tsControlSplit_baseControlPtr(TSControlSplit self);
TS_CAPI void TS_CCALL tsControlSplit_setAbsolute(TSControlSplit self, bool_t absolute);
TS_CAPI bool_t TS_CCALL tsControlSplit_isAbsolute(TSControlSplit self);
TS_CAPI void TS_CCALL tsControlSplit_setVertical(TSControlSplit self, bool_t vertical);
TS_CAPI bool_t TS_CCALL tsControlSplit_isHorizontal(TSControlSplit self);
TS_CAPI bool_t TS_CCALL tsControlSplit_isVertical(TSControlSplit self);
TS_CAPI void TS_CCALL tsControlSplit_setValue(TSControlSplit self, float32_t value);
TS_CAPI float32_t TS_CCALL tsControlSplit_getValue(TSControlSplit self);
TS_CAPI void TS_CCALL tsControlSplit_setHandleSize(TSControlSplit self, float32_t size);
TS_CAPI float32_t TS_CCALL tsControlSplit_getHandleSize(TSControlSplit self);
TS_CAPI TSVector2f TS_CCALL tsControlSplit_getControlsSize(TSControlSplit self);

/// Tellusim::ControlArea
TS_CAPI TSControlArea TS_CCALL tsControlArea_new(void);
TS_CAPI TSControlArea TS_CCALL tsControlArea_new_C(TSControl *parent);
TS_CAPI TSControlArea TS_CCALL tsControlArea_new_Cu(TSControl *parent, uint32_t columns);
TS_CAPI TSControlArea TS_CCALL tsControlArea_new_Cbb(TSControl *parent, bool_t horizontal, bool_t vertical);
TS_CAPI TSControlArea TS_CCALL tsControlArea_new_Cuff(TSControl *parent, uint32_t columns, float32_t x, float32_t y);
TS_CAPI void TS_CCALL tsControlArea_delete(TSControlArea self);
TS_CAPI bool_t TS_CCALL tsControlArea_equalPtr(const TSControlArea self, const TSControlArea ptr);
TS_CAPI TSControlArea TS_CCALL tsControlArea_copyPtr(const TSControlArea self);
TS_CAPI TSControlArea TS_CCALL tsControlArea_clonePtr(const TSControlArea self);
TS_CAPI void TS_CCALL tsControlArea_clearPtr(TSControlArea self);
TS_CAPI void TS_CCALL tsControlArea_destroyPtr(TSControlArea self);
TS_CAPI void TS_CCALL tsControlArea_acquirePtr(TSControlArea self);
TS_CAPI void TS_CCALL tsControlArea_unacquirePtr(TSControlArea self);
TS_CAPI bool_t TS_CCALL tsControlArea_isValidPtr(const TSControlArea self);
TS_CAPI bool_t TS_CCALL tsControlArea_isOwnerPtr(const TSControlArea self);
TS_CAPI bool_t TS_CCALL tsControlArea_isConstPtr(const TSControlArea self);
TS_CAPI uint32_t TS_CCALL tsControlArea_getCountPtr(const TSControlArea self);
TS_CAPI const void* TS_CCALL tsControlArea_getInternalPtr(const TSControlArea self);
TS_CAPI bool_t TS_CCALL tsControlArea_equalControlPtr(const TSControlArea self, const TSControl base);
TS_CAPI TSControlArea TS_CCALL tsControlArea_castControlPtr(TSControl base);
TS_CAPI TSControl TS_CCALL tsControlArea_baseControlPtr(TSControlArea self);
TS_CAPI void TS_CCALL tsControlArea_setAbsolute(TSControlArea self, bool_t absolute);
TS_CAPI bool_t TS_CCALL tsControlArea_isAbsolute(TSControlArea self);
TS_CAPI void TS_CCALL tsControlArea_setScalable(TSControlArea self, bool_t scalable);
TS_CAPI bool_t TS_CCALL tsControlArea_isScalable(TSControlArea self);
TS_CAPI void TS_CCALL tsControlArea_setScrollable(TSControlArea self, bool_t scrollable);
TS_CAPI bool_t TS_CCALL tsControlArea_isScrollable(TSControlArea self);
TS_CAPI void TS_CCALL tsControlArea_setScale(TSControlArea self, float32_t scale);
TS_CAPI float32_t TS_CCALL tsControlArea_getScale(TSControlArea self);
TS_CAPI void TS_CCALL tsControlArea_setScaleRange(TSControlArea self, float32_t min, float32_t max);
TS_CAPI float32_t TS_CCALL tsControlArea_getMinScale(TSControlArea self);
TS_CAPI float32_t TS_CCALL tsControlArea_getMaxScale(TSControlArea self);
TS_CAPI void TS_CCALL tsControlArea_setHorizontalStep(TSControlArea self, float64_t step);
TS_CAPI void TS_CCALL tsControlArea_setVerticalStep(TSControlArea self, float64_t step);
TS_CAPI void TS_CCALL tsControlArea_setStep(TSControlArea self, float64_t horizontal, float64_t vertical);
TS_CAPI float64_t TS_CCALL tsControlArea_getHorizontalStep(TSControlArea self);
TS_CAPI float64_t TS_CCALL tsControlArea_getVerticalStep(TSControlArea self);
TS_CAPI void TS_CCALL tsControlArea_setHorizontalValue(TSControlArea self, float64_t value);
TS_CAPI void TS_CCALL tsControlArea_setVerticalValue(TSControlArea self, float64_t value);
TS_CAPI void TS_CCALL tsControlArea_setValue(TSControlArea self, float64_t horizontal, float64_t vertical);
TS_CAPI float64_t TS_CCALL tsControlArea_getHorizontalValue(TSControlArea self);
TS_CAPI float64_t TS_CCALL tsControlArea_getVerticalValue(TSControlArea self);
TS_CAPI void TS_CCALL tsControlArea_setFrameAlign(TSControlArea self, TS_ControlAlign align);
TS_CAPI TS_ControlAlign TS_CCALL tsControlArea_getFrameAlign(TSControlArea self);
TS_CAPI float64_t TS_CCALL tsControlArea_getHorizontalFrame(TSControlArea self);
TS_CAPI float64_t TS_CCALL tsControlArea_getVerticalFrame(TSControlArea self);
TS_CAPI float64_t TS_CCALL tsControlArea_getHorizontalRange(TSControlArea self);
TS_CAPI float64_t TS_CCALL tsControlArea_getVerticalRange(TSControlArea self);
TS_CAPI void TS_CCALL tsControlArea_setHorizontalEnabled(TSControlArea self, bool_t enabled, bool_t dynamic);
TS_CAPI bool_t TS_CCALL tsControlArea_isHorizontalEnabled(TSControlArea self);
TS_CAPI bool_t TS_CCALL tsControlArea_isHorizontalDynamic(TSControlArea self);
TS_CAPI bool_t TS_CCALL tsControlArea_isHorizontalHidden(TSControlArea self);
TS_CAPI TSControlScroll TS_CCALL tsControlArea_getHorizontalScroll_c(TSControlArea self);
TS_CAPI TSControlScroll TS_CCALL tsControlArea_getHorizontalScroll(TSControlArea self);
TS_CAPI void TS_CCALL tsControlArea_setVerticalEnabled(TSControlArea self, bool_t enabled, bool_t dynamic);
TS_CAPI bool_t TS_CCALL tsControlArea_isVerticalEnabled(TSControlArea self);
TS_CAPI bool_t TS_CCALL tsControlArea_isVerticalDynamic(TSControlArea self);
TS_CAPI bool_t TS_CCALL tsControlArea_isVerticalHidden(TSControlArea self);
TS_CAPI TSControlScroll TS_CCALL tsControlArea_getVerticalScroll_c(TSControlArea self);
TS_CAPI TSControlScroll TS_CCALL tsControlArea_getVerticalScroll(TSControlArea self);
TS_CAPI bool_t TS_CCALL tsControlArea_setFontSize(TSControlArea self, uint32_t size);
TS_CAPI uint32_t TS_CCALL tsControlArea_getFontSize(TSControlArea self);
TS_CAPI bool_t TS_CCALL tsControlArea_setFontStyle(TSControlArea self, const TSFontStyle *style);
TS_CAPI TSFontStyle TS_CCALL tsControlArea_getFontStyleConst(TSControlArea self);
TS_CAPI TSFontStyle TS_CCALL tsControlArea_getFontStyle_c(TSControlArea self);
TS_CAPI TSFontStyle TS_CCALL tsControlArea_getFontStyle(TSControlArea self);
TS_CAPI void TS_CCALL tsControlArea_setColumns(TSControlArea self, uint32_t columns);
TS_CAPI uint32_t TS_CCALL tsControlArea_getColumns(TSControlArea self);
TS_CAPI void TS_CCALL tsControlArea_setSpacing_cV2(TSControlArea self, const TSVector2f *spacing);
TS_CAPI void TS_CCALL tsControlArea_setSpacing_ff(TSControlArea self, float32_t x, float32_t y);
TS_CAPI TSVector2f TS_CCALL tsControlArea_getSpacing(TSControlArea self);
TS_CAPI void TS_CCALL tsControlArea_setColumnRatio(TSControlArea self, uint32_t index, float32_t ratio);
TS_CAPI float32_t TS_CCALL tsControlArea_getColumnRatio(TSControlArea self, uint32_t index);
TS_CAPI TSVector2f TS_CCALL tsControlArea_getControlsSize(TSControlArea self);
TS_CAPI TSVector2f TS_CCALL tsControlArea_getControlsOffset(TSControlArea self);
TS_CAPI TSRect TS_CCALL tsControlArea_getViewRect(TSControlArea self);

/// Tellusim::ControlTree
typedef void (*TSControlTreeChangedCallback)(TSControlTree a0, uint32_t item, void *data_);
typedef bool_t (*TSControlTreeDraggedCallback)(TSControlTree a0, uint32_t item, void *data_);
typedef void (*TSControlTreeDroppedCallback)(TSControlTree a0, uint32_t item, void *data_);
typedef void (*TSControlTreeClickedCallback)(TSControlTree a0, uint32_t item, void *data_);
typedef void (*TSControlTreeExpandedCallback)(TSControlTree a0, uint32_t item, void *data_);
typedef void (*TSControlTreeSelectedCallback)(TSControlTree a0, void *data_);
TS_CAPI TSControlTree TS_CCALL tsControlTree_new(void);
TS_CAPI TSControlTree TS_CCALL tsControlTree_new_C(TSControl *parent);
TS_CAPI void TS_CCALL tsControlTree_delete(TSControlTree self);
TS_CAPI bool_t TS_CCALL tsControlTree_equalPtr(const TSControlTree self, const TSControlTree ptr);
TS_CAPI TSControlTree TS_CCALL tsControlTree_copyPtr(const TSControlTree self);
TS_CAPI TSControlTree TS_CCALL tsControlTree_clonePtr(const TSControlTree self);
TS_CAPI void TS_CCALL tsControlTree_clearPtr(TSControlTree self);
TS_CAPI void TS_CCALL tsControlTree_destroyPtr(TSControlTree self);
TS_CAPI void TS_CCALL tsControlTree_acquirePtr(TSControlTree self);
TS_CAPI void TS_CCALL tsControlTree_unacquirePtr(TSControlTree self);
TS_CAPI bool_t TS_CCALL tsControlTree_isValidPtr(const TSControlTree self);
TS_CAPI bool_t TS_CCALL tsControlTree_isOwnerPtr(const TSControlTree self);
TS_CAPI bool_t TS_CCALL tsControlTree_isConstPtr(const TSControlTree self);
TS_CAPI uint32_t TS_CCALL tsControlTree_getCountPtr(const TSControlTree self);
TS_CAPI const void* TS_CCALL tsControlTree_getInternalPtr(const TSControlTree self);
TS_CAPI bool_t TS_CCALL tsControlTree_equalControlTextPtr(const TSControlTree self, const TSControlText base);
TS_CAPI TSControlTree TS_CCALL tsControlTree_castControlTextPtr(TSControlText base);
TS_CAPI TSControlText TS_CCALL tsControlTree_baseControlTextPtr(TSControlTree self);
TS_CAPI bool_t TS_CCALL tsControlTree_equalControlPtr(const TSControlTree self, const TSControl base);
TS_CAPI TSControlTree TS_CCALL tsControlTree_castControlPtr(TSControl base);
TS_CAPI TSControl TS_CCALL tsControlTree_baseControlPtr(TSControlTree self);
TS_CAPI void TS_CCALL tsControlTree_setSelectable(TSControlTree self, bool_t selectable);
TS_CAPI bool_t TS_CCALL tsControlTree_isSelectable(TSControlTree self);
TS_CAPI void TS_CCALL tsControlTree_setMultiSelection(TSControlTree self, bool_t multi_selection);
TS_CAPI bool_t TS_CCALL tsControlTree_isMultiSelection(TSControlTree self);
TS_CAPI void TS_CCALL tsControlTree_setFoldedText_s(TSControlTree self, const char *text);
TS_CAPI void TS_CCALL tsControlTree_setFoldedText_cS(TSControlTree self, const TSString text);
TS_CAPI TSString TS_CCALL tsControlTree_getFoldedText(TSControlTree self);
TS_CAPI void TS_CCALL tsControlTree_setExpandedText_s(TSControlTree self, const char *text);
TS_CAPI void TS_CCALL tsControlTree_setExpandedText_cS(TSControlTree self, const TSString text);
TS_CAPI TSString TS_CCALL tsControlTree_getExpandedText(TSControlTree self);
TS_CAPI void TS_CCALL tsControlTree_setTexture(TSControlTree self, TSTexture texture, uint32_t rows, uint32_t columns);
TS_CAPI TSTexture TS_CCALL tsControlTree_getTexture(TSControlTree self);
TS_CAPI void TS_CCALL tsControlTree_setTextureName_suu(TSControlTree self, const char *name, uint32_t rows, uint32_t columns);
TS_CAPI void TS_CCALL tsControlTree_setTextureName_cSuu(TSControlTree self, const TSString name, uint32_t rows, uint32_t columns);
TS_CAPI TSString TS_CCALL tsControlTree_getTextureName(TSControlTree self);
TS_CAPI void TS_CCALL tsControlTree_setTextureGrid(TSControlTree self, uint32_t rows, uint32_t columns);
TS_CAPI uint32_t TS_CCALL tsControlTree_getTextureRows(TSControlTree self);
TS_CAPI uint32_t TS_CCALL tsControlTree_getTextureColumns(TSControlTree self);
TS_CAPI void TS_CCALL tsControlTree_clearItems(TSControlTree self);
TS_CAPI uint32_t TS_CCALL tsControlTree_addItem_sub(TSControlTree self, const char *text, uint32_t parent, bool_t expanded);
TS_CAPI uint32_t TS_CCALL tsControlTree_addItem_cSub(TSControlTree self, const TSString text, uint32_t parent, bool_t expanded);
TS_CAPI void TS_CCALL tsControlTree_removeItem(TSControlTree self, uint32_t item, bool_t children);
TS_CAPI void TS_CCALL tsControlTree_viewItem(TSControlTree self, uint32_t item);
TS_CAPI uint32_t TS_CCALL tsControlTree_getNumItems(TSControlTree self);
TS_CAPI uint32_t TS_CCALL tsControlTree_getItem(TSControlTree self, uint32_t index);
TS_CAPI bool_t TS_CCALL tsControlTree_switchItemHidden(TSControlTree self, uint32_t item, bool_t children);
TS_CAPI void TS_CCALL tsControlTree_setItemHidden(TSControlTree self, uint32_t item, bool_t hidden, bool_t children);
TS_CAPI bool_t TS_CCALL tsControlTree_isItemHidden(TSControlTree self, uint32_t item);
TS_CAPI bool_t TS_CCALL tsControlTree_switchItemExpanded(TSControlTree self, uint32_t item, bool_t children);
TS_CAPI void TS_CCALL tsControlTree_setItemExpanded(TSControlTree self, uint32_t item, bool_t expanded, bool_t children);
TS_CAPI bool_t TS_CCALL tsControlTree_isItemExpanded(TSControlTree self, uint32_t item);
TS_CAPI bool_t TS_CCALL tsControlTree_switchItemSelected(TSControlTree self, uint32_t item, bool_t children);
TS_CAPI void TS_CCALL tsControlTree_setItemSelected(TSControlTree self, uint32_t item, bool_t selected, bool_t children);
TS_CAPI bool_t TS_CCALL tsControlTree_isItemSelected(TSControlTree self, uint32_t item);
TS_CAPI void TS_CCALL tsControlTree_setItemParent(TSControlTree self, uint32_t item, uint32_t parent);
TS_CAPI uint32_t TS_CCALL tsControlTree_getItemParent(TSControlTree self, uint32_t item);
TS_CAPI bool_t TS_CCALL tsControlTree_isItemParent(TSControlTree self, uint32_t item, uint32_t parent, bool_t hierarchy);
TS_CAPI void TS_CCALL tsControlTree_addItemChild(TSControlTree self, uint32_t item, uint32_t child);
TS_CAPI void TS_CCALL tsControlTree_removeItemChild(TSControlTree self, uint32_t item, uint32_t child);
TS_CAPI void TS_CCALL tsControlTree_addItemChildren(TSControlTree self, uint32_t item, const uint32_t *children, uint32_t children_size);
TS_CAPI void TS_CCALL tsControlTree_removeItemChildren(TSControlTree self, uint32_t item, const uint32_t *children, uint32_t children_size);
TS_CAPI uint32_t TS_CCALL tsControlTree_findItemChild(TSControlTree self, uint32_t item, uint32_t child);
TS_CAPI bool_t TS_CCALL tsControlTree_isItemChild(TSControlTree self, uint32_t item, uint32_t child);
TS_CAPI uint32_t TS_CCALL tsControlTree_getNumItemChildren(TSControlTree self, uint32_t item);
TS_CAPI uint32_t TS_CCALL tsControlTree_getItemChild(TSControlTree self, uint32_t item, uint32_t index);
TS_CAPI void TS_CCALL tsControlTree_setItemText_us(TSControlTree self, uint32_t item, const char *text);
TS_CAPI void TS_CCALL tsControlTree_setItemText_ucS(TSControlTree self, uint32_t item, const TSString text);
TS_CAPI TSString TS_CCALL tsControlTree_getItemText(TSControlTree self, uint32_t item);
TS_CAPI uint32_t TS_CCALL tsControlTree_findItemText_cs(TSControlTree self, const char *text);
TS_CAPI uint32_t TS_CCALL tsControlTree_findItemText_ccS(TSControlTree self, const TSString text);
TS_CAPI void TS_CCALL tsControlTree_setItemColor(TSControlTree self, uint32_t item, const TSColor *color);
TS_CAPI TSColor TS_CCALL tsControlTree_getItemColor(TSControlTree self, uint32_t item);
TS_CAPI void TS_CCALL tsControlTree_setItemTexture(TSControlTree self, uint32_t item, uint32_t row, uint32_t column);
TS_CAPI uint32_t TS_CCALL tsControlTree_getItemTextureRow(TSControlTree self, uint32_t item);
TS_CAPI uint32_t TS_CCALL tsControlTree_getItemTextureColumn(TSControlTree self, uint32_t item);
TS_CAPI void TS_CCALL tsControlTree_setItemData(TSControlTree self, uint32_t item, void *data);
TS_CAPI void* TS_CCALL tsControlTree_getItemData(TSControlTree self, uint32_t item);
TS_CAPI uint32_t TS_CCALL tsControlTree_getFocusedItem(TSControlTree self);
TS_CAPI void TS_CCALL tsControlTree_setCurrentItem(TSControlTree self, uint32_t item, bool_t select, bool_t view, bool_t callback);
TS_CAPI uint32_t TS_CCALL tsControlTree_getCurrentItem(TSControlTree self);
TS_CAPI TSString TS_CCALL tsControlTree_getCurrentText(TSControlTree self);
TS_CAPI void TS_CCALL tsControlTree_setSelection(TSControlTree self);
TS_CAPI void TS_CCALL tsControlTree_clearSelection(TSControlTree self);
TS_CAPI void TS_CCALL tsControlTree_inverseSelection(TSControlTree self);
TS_CAPI uint32_t TS_CCALL tsControlTree_getNumSelectedItems(TSControlTree self);
TS_CAPI uint32_t TS_CCALL tsControlTree_getSelectedItem(TSControlTree self, uint32_t index);
TS_CAPI void TS_CCALL tsControlTree_setChangedCallback(TSControlTree self, const TSControlTreeChangedCallback func, void *data_);
TS_CAPI void TS_CCALL tsControlTree_setDraggedCallback(TSControlTree self, const TSControlTreeDraggedCallback func, void *data_);
TS_CAPI void TS_CCALL tsControlTree_setDroppedCallback(TSControlTree self, const TSControlTreeDroppedCallback func, void *data_);
TS_CAPI void TS_CCALL tsControlTree_setClickedCallback(TSControlTree self, const TSControlTreeClickedCallback func, void *data_);
TS_CAPI void TS_CCALL tsControlTree_setClicked2Callback(TSControlTree self, const TSControlTreeClickedCallback func, void *data_);
TS_CAPI void TS_CCALL tsControlTree_setClickedRightCallback(TSControlTree self, const TSControlTreeClickedCallback func, void *data_);
TS_CAPI void TS_CCALL tsControlTree_setExpandedCallback(TSControlTree self, const TSControlTreeExpandedCallback func, void *data_);
TS_CAPI void TS_CCALL tsControlTree_setSelectedCallback(TSControlTree self, const TSControlTreeSelectedCallback func, void *data_);

/// Tellusim::ControlEdit
typedef void (*TSControlEditClickedCallback)(TSControlEdit a0, void *data_);
typedef void (*TSControlEditChangedCallback)(TSControlEdit a0, void *data_);
typedef void (*TSControlEditReturnedCallback)(TSControlEdit a0, void *data_);
TS_CAPI TSControlEdit TS_CCALL tsControlEdit_new(void);
TS_CAPI TSControlEdit TS_CCALL tsControlEdit_new_C(TSControl *parent);
TS_CAPI TSControlEdit TS_CCALL tsControlEdit_new_Cs(TSControl *parent, const char *text);
TS_CAPI TSControlEdit TS_CCALL tsControlEdit_new_CcS(TSControl *parent, const TSString text);
TS_CAPI void TS_CCALL tsControlEdit_delete(TSControlEdit self);
TS_CAPI bool_t TS_CCALL tsControlEdit_equalPtr(const TSControlEdit self, const TSControlEdit ptr);
TS_CAPI TSControlEdit TS_CCALL tsControlEdit_copyPtr(const TSControlEdit self);
TS_CAPI TSControlEdit TS_CCALL tsControlEdit_clonePtr(const TSControlEdit self);
TS_CAPI void TS_CCALL tsControlEdit_clearPtr(TSControlEdit self);
TS_CAPI void TS_CCALL tsControlEdit_destroyPtr(TSControlEdit self);
TS_CAPI void TS_CCALL tsControlEdit_acquirePtr(TSControlEdit self);
TS_CAPI void TS_CCALL tsControlEdit_unacquirePtr(TSControlEdit self);
TS_CAPI bool_t TS_CCALL tsControlEdit_isValidPtr(const TSControlEdit self);
TS_CAPI bool_t TS_CCALL tsControlEdit_isOwnerPtr(const TSControlEdit self);
TS_CAPI bool_t TS_CCALL tsControlEdit_isConstPtr(const TSControlEdit self);
TS_CAPI uint32_t TS_CCALL tsControlEdit_getCountPtr(const TSControlEdit self);
TS_CAPI const void* TS_CCALL tsControlEdit_getInternalPtr(const TSControlEdit self);
TS_CAPI bool_t TS_CCALL tsControlEdit_equalControlTextPtr(const TSControlEdit self, const TSControlText base);
TS_CAPI TSControlEdit TS_CCALL tsControlEdit_castControlTextPtr(TSControlText base);
TS_CAPI TSControlText TS_CCALL tsControlEdit_baseControlTextPtr(TSControlEdit self);
TS_CAPI bool_t TS_CCALL tsControlEdit_equalControlPtr(const TSControlEdit self, const TSControl base);
TS_CAPI TSControlEdit TS_CCALL tsControlEdit_castControlPtr(TSControl base);
TS_CAPI TSControl TS_CCALL tsControlEdit_baseControlPtr(TSControlEdit self);
TS_CAPI void TS_CCALL tsControlEdit_setFrame(TSControlEdit self, bool_t frame);
TS_CAPI bool_t TS_CCALL tsControlEdit_getFrame(TSControlEdit self);
TS_CAPI void TS_CCALL tsControlEdit_setBackground(TSControlEdit self, bool_t background);
TS_CAPI bool_t TS_CCALL tsControlEdit_getBackground(TSControlEdit self);
TS_CAPI void TS_CCALL tsControlEdit_setEditColor(TSControlEdit self, const TSColor *color);
TS_CAPI TSColor TS_CCALL tsControlEdit_getEditColor(TSControlEdit self);
TS_CAPI void TS_CCALL tsControlEdit_setEditMode(TSControlEdit self, TS_ControlEditEditMode mode);
TS_CAPI TS_ControlEditEditMode TS_CCALL tsControlEdit_getEditMode(TSControlEdit self);
TS_CAPI void TS_CCALL tsControlEdit_setPasswordCode(TSControlEdit self, uint32_t code);
TS_CAPI uint32_t TS_CCALL tsControlEdit_getPasswordCode(TSControlEdit self);
TS_CAPI uint32_t TS_CCALL tsControlEdit_getNumCodes(TSControlEdit self);
TS_CAPI const uint32_t* TS_CCALL tsControlEdit_getCodes(TSControlEdit self);
TS_CAPI void TS_CCALL tsControlEdit_setCurrentIndex(TSControlEdit self, uint32_t index, uint32_t selection_index);
TS_CAPI uint32_t TS_CCALL tsControlEdit_getCurrentIndex(TSControlEdit self);
TS_CAPI uint32_t TS_CCALL tsControlEdit_getSelectionIndex(TSControlEdit self);
TS_CAPI void TS_CCALL tsControlEdit_setSelection(TSControlEdit self, bool_t current, bool_t changed);
TS_CAPI void TS_CCALL tsControlEdit_clearSelection(TSControlEdit self);
TS_CAPI TSString TS_CCALL tsControlEdit_getSelectedText(TSControlEdit self);
TS_CAPI bool_t TS_CCALL tsControlEdit_updateKeyboard(TSControlEdit self, TSControlRoot root, uint32_t key, uint32_t code);
TS_CAPI void TS_CCALL tsControlEdit_setClickedCallback(TSControlEdit self, const TSControlEditClickedCallback func, void *data_);
TS_CAPI bool_t TS_CCALL tsControlEdit_isClicked(TSControlEdit self);
TS_CAPI void TS_CCALL tsControlEdit_setChangedCallback(TSControlEdit self, const TSControlEditChangedCallback func, void *data_);
TS_CAPI bool_t TS_CCALL tsControlEdit_isChanged(TSControlEdit self);
TS_CAPI void TS_CCALL tsControlEdit_setReturnedCallback(TSControlEdit self, const TSControlEditReturnedCallback func, void *data_);
TS_CAPI bool_t TS_CCALL tsControlEdit_isReturned(TSControlEdit self);
TS_CAPI TSCanvasMesh TS_CCALL tsControlEdit_getCanvasMesh(TSControlEdit self);

/// Tellusim::DialogMessage
typedef bool_t (*TSDialogMessageUpdateCallback)(void *data_);
TS_CAPI TSDialogMessage TS_CCALL tsDialogMessage_new_ss(const char *title, const char *message);
TS_CAPI TSDialogMessage TS_CCALL tsDialogMessage_new_cSs(const TSString title, const char *message);
TS_CAPI TSDialogMessage TS_CCALL tsDialogMessage_new_scS(const char *title, const TSString message);
TS_CAPI TSDialogMessage TS_CCALL tsDialogMessage_new_cScS(const TSString title, const TSString message);
TS_CAPI void TS_CCALL tsDialogMessage_delete(TSDialogMessage self);
TS_CAPI bool_t TS_CCALL tsDialogMessage_equalPtr(const TSDialogMessage self, const TSDialogMessage ptr);
TS_CAPI TSDialogMessage TS_CCALL tsDialogMessage_copyPtr(const TSDialogMessage self);
TS_CAPI TSDialogMessage TS_CCALL tsDialogMessage_clonePtr(const TSDialogMessage self);
TS_CAPI void TS_CCALL tsDialogMessage_clearPtr(TSDialogMessage self);
TS_CAPI void TS_CCALL tsDialogMessage_destroyPtr(TSDialogMessage self);
TS_CAPI void TS_CCALL tsDialogMessage_acquirePtr(TSDialogMessage self);
TS_CAPI void TS_CCALL tsDialogMessage_unacquirePtr(TSDialogMessage self);
TS_CAPI bool_t TS_CCALL tsDialogMessage_isValidPtr(const TSDialogMessage self);
TS_CAPI bool_t TS_CCALL tsDialogMessage_isOwnerPtr(const TSDialogMessage self);
TS_CAPI bool_t TS_CCALL tsDialogMessage_isConstPtr(const TSDialogMessage self);
TS_CAPI uint32_t TS_CCALL tsDialogMessage_getCountPtr(const TSDialogMessage self);
TS_CAPI const void* TS_CCALL tsDialogMessage_getInternalPtr(const TSDialogMessage self);
TS_CAPI void TS_CCALL tsDialogMessage_setPosition(TSDialogMessage self, int32_t x, int32_t y);
TS_CAPI int32_t TS_CCALL tsDialogMessage_getPositionX(TSDialogMessage self);
TS_CAPI int32_t TS_CCALL tsDialogMessage_getPositionY(TSDialogMessage self);
TS_CAPI void TS_CCALL tsDialogMessage_setTitle_s(TSDialogMessage self, const char *title);
TS_CAPI void TS_CCALL tsDialogMessage_setTitle_cS(TSDialogMessage self, const TSString title);
TS_CAPI TSString TS_CCALL tsDialogMessage_getTitle(TSDialogMessage self);
TS_CAPI void TS_CCALL tsDialogMessage_setMessage_s(TSDialogMessage self, const char *message);
TS_CAPI void TS_CCALL tsDialogMessage_setMessage_cS(TSDialogMessage self, const TSString message);
TS_CAPI TSString TS_CCALL tsDialogMessage_getMessage(TSDialogMessage self);
TS_CAPI void TS_CCALL tsDialogMessage_setUpdateCallback(TSDialogMessage self, const TSDialogMessageUpdateCallback func, void *data_);
TS_CAPI TS_DialogMessageResult TS_CCALL tsDialogMessage_run(TSDialogMessage self, TS_DialogMessageFlags flags);

/// Tellusim::DialogFileOpen
typedef bool_t (*TSDialogFileOpenUpdateCallback)(void *data_);
TS_CAPI TSDialogFileOpen TS_CCALL tsDialogFileOpen_new_ss(const char *title, const char *name);
TS_CAPI TSDialogFileOpen TS_CCALL tsDialogFileOpen_new_cSs(const TSString title, const char *name);
TS_CAPI TSDialogFileOpen TS_CCALL tsDialogFileOpen_new_scS(const char *title, const TSString name);
TS_CAPI TSDialogFileOpen TS_CCALL tsDialogFileOpen_new_cScS(const TSString title, const TSString name);
TS_CAPI void TS_CCALL tsDialogFileOpen_delete(TSDialogFileOpen self);
TS_CAPI bool_t TS_CCALL tsDialogFileOpen_equalPtr(const TSDialogFileOpen self, const TSDialogFileOpen ptr);
TS_CAPI TSDialogFileOpen TS_CCALL tsDialogFileOpen_copyPtr(const TSDialogFileOpen self);
TS_CAPI TSDialogFileOpen TS_CCALL tsDialogFileOpen_clonePtr(const TSDialogFileOpen self);
TS_CAPI void TS_CCALL tsDialogFileOpen_clearPtr(TSDialogFileOpen self);
TS_CAPI void TS_CCALL tsDialogFileOpen_destroyPtr(TSDialogFileOpen self);
TS_CAPI void TS_CCALL tsDialogFileOpen_acquirePtr(TSDialogFileOpen self);
TS_CAPI void TS_CCALL tsDialogFileOpen_unacquirePtr(TSDialogFileOpen self);
TS_CAPI bool_t TS_CCALL tsDialogFileOpen_isValidPtr(const TSDialogFileOpen self);
TS_CAPI bool_t TS_CCALL tsDialogFileOpen_isOwnerPtr(const TSDialogFileOpen self);
TS_CAPI bool_t TS_CCALL tsDialogFileOpen_isConstPtr(const TSDialogFileOpen self);
TS_CAPI uint32_t TS_CCALL tsDialogFileOpen_getCountPtr(const TSDialogFileOpen self);
TS_CAPI const void* TS_CCALL tsDialogFileOpen_getInternalPtr(const TSDialogFileOpen self);
TS_CAPI void TS_CCALL tsDialogFileOpen_setPosition(TSDialogFileOpen self, int32_t x, int32_t y);
TS_CAPI int32_t TS_CCALL tsDialogFileOpen_getPositionX(TSDialogFileOpen self);
TS_CAPI int32_t TS_CCALL tsDialogFileOpen_getPositionY(TSDialogFileOpen self);
TS_CAPI void TS_CCALL tsDialogFileOpen_setTitle_s(TSDialogFileOpen self, const char *title);
TS_CAPI void TS_CCALL tsDialogFileOpen_setTitle_cS(TSDialogFileOpen self, const TSString title);
TS_CAPI TSString TS_CCALL tsDialogFileOpen_getTitle(TSDialogFileOpen self);
TS_CAPI void TS_CCALL tsDialogFileOpen_setFilter_s(TSDialogFileOpen self, const char *filter);
TS_CAPI void TS_CCALL tsDialogFileOpen_setFilter_cS(TSDialogFileOpen self, const TSString filter);
TS_CAPI TSString TS_CCALL tsDialogFileOpen_getFilter(TSDialogFileOpen self);
TS_CAPI void TS_CCALL tsDialogFileOpen_setFile_s(TSDialogFileOpen self, const char *name);
TS_CAPI void TS_CCALL tsDialogFileOpen_setFile_cS(TSDialogFileOpen self, const TSString name);
TS_CAPI TSString TS_CCALL tsDialogFileOpen_getFile(TSDialogFileOpen self);
TS_CAPI void TS_CCALL tsDialogFileOpen_setUpdateCallback(TSDialogFileOpen self, const TSDialogFileOpenUpdateCallback func, void *data_);
TS_CAPI TS_DialogFileOpenResult TS_CCALL tsDialogFileOpen_run(TSDialogFileOpen self, TS_DialogFileOpenFlags flags);

/// Tellusim::DialogFileSave
typedef bool_t (*TSDialogFileSaveUpdateCallback)(void *data_);
TS_CAPI TSDialogFileSave TS_CCALL tsDialogFileSave_new_ss(const char *title, const char *name);
TS_CAPI TSDialogFileSave TS_CCALL tsDialogFileSave_new_cSs(const TSString title, const char *name);
TS_CAPI TSDialogFileSave TS_CCALL tsDialogFileSave_new_scS(const char *title, const TSString name);
TS_CAPI TSDialogFileSave TS_CCALL tsDialogFileSave_new_cScS(const TSString title, const TSString name);
TS_CAPI void TS_CCALL tsDialogFileSave_delete(TSDialogFileSave self);
TS_CAPI bool_t TS_CCALL tsDialogFileSave_equalPtr(const TSDialogFileSave self, const TSDialogFileSave ptr);
TS_CAPI TSDialogFileSave TS_CCALL tsDialogFileSave_copyPtr(const TSDialogFileSave self);
TS_CAPI TSDialogFileSave TS_CCALL tsDialogFileSave_clonePtr(const TSDialogFileSave self);
TS_CAPI void TS_CCALL tsDialogFileSave_clearPtr(TSDialogFileSave self);
TS_CAPI void TS_CCALL tsDialogFileSave_destroyPtr(TSDialogFileSave self);
TS_CAPI void TS_CCALL tsDialogFileSave_acquirePtr(TSDialogFileSave self);
TS_CAPI void TS_CCALL tsDialogFileSave_unacquirePtr(TSDialogFileSave self);
TS_CAPI bool_t TS_CCALL tsDialogFileSave_isValidPtr(const TSDialogFileSave self);
TS_CAPI bool_t TS_CCALL tsDialogFileSave_isOwnerPtr(const TSDialogFileSave self);
TS_CAPI bool_t TS_CCALL tsDialogFileSave_isConstPtr(const TSDialogFileSave self);
TS_CAPI uint32_t TS_CCALL tsDialogFileSave_getCountPtr(const TSDialogFileSave self);
TS_CAPI const void* TS_CCALL tsDialogFileSave_getInternalPtr(const TSDialogFileSave self);
TS_CAPI void TS_CCALL tsDialogFileSave_setPosition(TSDialogFileSave self, int32_t x, int32_t y);
TS_CAPI int32_t TS_CCALL tsDialogFileSave_getPositionX(TSDialogFileSave self);
TS_CAPI int32_t TS_CCALL tsDialogFileSave_getPositionY(TSDialogFileSave self);
TS_CAPI void TS_CCALL tsDialogFileSave_setTitle_s(TSDialogFileSave self, const char *title);
TS_CAPI void TS_CCALL tsDialogFileSave_setTitle_cS(TSDialogFileSave self, const TSString title);
TS_CAPI TSString TS_CCALL tsDialogFileSave_getTitle(TSDialogFileSave self);
TS_CAPI void TS_CCALL tsDialogFileSave_setFilter_s(TSDialogFileSave self, const char *filter);
TS_CAPI void TS_CCALL tsDialogFileSave_setFilter_cS(TSDialogFileSave self, const TSString filter);
TS_CAPI TSString TS_CCALL tsDialogFileSave_getFilter(TSDialogFileSave self);
TS_CAPI void TS_CCALL tsDialogFileSave_setFile_s(TSDialogFileSave self, const char *name);
TS_CAPI void TS_CCALL tsDialogFileSave_setFile_cS(TSDialogFileSave self, const TSString name);
TS_CAPI TSString TS_CCALL tsDialogFileSave_getFile(TSDialogFileSave self);
TS_CAPI void TS_CCALL tsDialogFileSave_setUpdateCallback(TSDialogFileSave self, const TSDialogFileSaveUpdateCallback func, void *data_);
TS_CAPI TS_DialogFileSaveResult TS_CCALL tsDialogFileSave_run(TSDialogFileSave self, TS_DialogFileSaveFlags flags);

/// Tellusim::DialogDirectory
typedef bool_t (*TSDialogDirectoryUpdateCallback)(void *data_);
TS_CAPI TSDialogDirectory TS_CCALL tsDialogDirectory_new_ss(const char *title, const char *name);
TS_CAPI TSDialogDirectory TS_CCALL tsDialogDirectory_new_cSs(const TSString title, const char *name);
TS_CAPI TSDialogDirectory TS_CCALL tsDialogDirectory_new_scS(const char *title, const TSString name);
TS_CAPI TSDialogDirectory TS_CCALL tsDialogDirectory_new_cScS(const TSString title, const TSString name);
TS_CAPI void TS_CCALL tsDialogDirectory_delete(TSDialogDirectory self);
TS_CAPI bool_t TS_CCALL tsDialogDirectory_equalPtr(const TSDialogDirectory self, const TSDialogDirectory ptr);
TS_CAPI TSDialogDirectory TS_CCALL tsDialogDirectory_copyPtr(const TSDialogDirectory self);
TS_CAPI TSDialogDirectory TS_CCALL tsDialogDirectory_clonePtr(const TSDialogDirectory self);
TS_CAPI void TS_CCALL tsDialogDirectory_clearPtr(TSDialogDirectory self);
TS_CAPI void TS_CCALL tsDialogDirectory_destroyPtr(TSDialogDirectory self);
TS_CAPI void TS_CCALL tsDialogDirectory_acquirePtr(TSDialogDirectory self);
TS_CAPI void TS_CCALL tsDialogDirectory_unacquirePtr(TSDialogDirectory self);
TS_CAPI bool_t TS_CCALL tsDialogDirectory_isValidPtr(const TSDialogDirectory self);
TS_CAPI bool_t TS_CCALL tsDialogDirectory_isOwnerPtr(const TSDialogDirectory self);
TS_CAPI bool_t TS_CCALL tsDialogDirectory_isConstPtr(const TSDialogDirectory self);
TS_CAPI uint32_t TS_CCALL tsDialogDirectory_getCountPtr(const TSDialogDirectory self);
TS_CAPI const void* TS_CCALL tsDialogDirectory_getInternalPtr(const TSDialogDirectory self);
TS_CAPI void TS_CCALL tsDialogDirectory_setPosition(TSDialogDirectory self, int32_t x, int32_t y);
TS_CAPI int32_t TS_CCALL tsDialogDirectory_getPositionX(TSDialogDirectory self);
TS_CAPI int32_t TS_CCALL tsDialogDirectory_getPositionY(TSDialogDirectory self);
TS_CAPI void TS_CCALL tsDialogDirectory_setTitle_s(TSDialogDirectory self, const char *title);
TS_CAPI void TS_CCALL tsDialogDirectory_setTitle_cS(TSDialogDirectory self, const TSString title);
TS_CAPI TSString TS_CCALL tsDialogDirectory_getTitle(TSDialogDirectory self);
TS_CAPI void TS_CCALL tsDialogDirectory_setDirectory_s(TSDialogDirectory self, const char *name);
TS_CAPI void TS_CCALL tsDialogDirectory_setDirectory_cS(TSDialogDirectory self, const TSString name);
TS_CAPI TSString TS_CCALL tsDialogDirectory_getDirectory(TSDialogDirectory self);
TS_CAPI void TS_CCALL tsDialogDirectory_setUpdateCallback(TSDialogDirectory self, const TSDialogDirectoryUpdateCallback func, void *data_);
TS_CAPI TS_DialogDirectoryResult TS_CCALL tsDialogDirectory_run(TSDialogDirectory self, TS_DialogDirectoryFlags flags);

/// Tellusim::DialogProgress
TS_CAPI TSDialogProgress TS_CCALL tsDialogProgress_new_ss(const char *title, const char *message);
TS_CAPI TSDialogProgress TS_CCALL tsDialogProgress_new_cSs(const TSString title, const char *message);
TS_CAPI TSDialogProgress TS_CCALL tsDialogProgress_new_scS(const char *title, const TSString message);
TS_CAPI TSDialogProgress TS_CCALL tsDialogProgress_new_cScS(const TSString title, const TSString message);
TS_CAPI void TS_CCALL tsDialogProgress_delete(TSDialogProgress self);
TS_CAPI bool_t TS_CCALL tsDialogProgress_equalPtr(const TSDialogProgress self, const TSDialogProgress ptr);
TS_CAPI TSDialogProgress TS_CCALL tsDialogProgress_copyPtr(const TSDialogProgress self);
TS_CAPI TSDialogProgress TS_CCALL tsDialogProgress_clonePtr(const TSDialogProgress self);
TS_CAPI void TS_CCALL tsDialogProgress_clearPtr(TSDialogProgress self);
TS_CAPI void TS_CCALL tsDialogProgress_destroyPtr(TSDialogProgress self);
TS_CAPI void TS_CCALL tsDialogProgress_acquirePtr(TSDialogProgress self);
TS_CAPI void TS_CCALL tsDialogProgress_unacquirePtr(TSDialogProgress self);
TS_CAPI bool_t TS_CCALL tsDialogProgress_isValidPtr(const TSDialogProgress self);
TS_CAPI bool_t TS_CCALL tsDialogProgress_isOwnerPtr(const TSDialogProgress self);
TS_CAPI bool_t TS_CCALL tsDialogProgress_isConstPtr(const TSDialogProgress self);
TS_CAPI uint32_t TS_CCALL tsDialogProgress_getCountPtr(const TSDialogProgress self);
TS_CAPI const void* TS_CCALL tsDialogProgress_getInternalPtr(const TSDialogProgress self);
TS_CAPI void TS_CCALL tsDialogProgress_setPosition(TSDialogProgress self, int32_t x, int32_t y);
TS_CAPI int32_t TS_CCALL tsDialogProgress_getPositionX(TSDialogProgress self);
TS_CAPI int32_t TS_CCALL tsDialogProgress_getPositionY(TSDialogProgress self);
TS_CAPI void TS_CCALL tsDialogProgress_setTitle_s(TSDialogProgress self, const char *title);
TS_CAPI void TS_CCALL tsDialogProgress_setTitle_cS(TSDialogProgress self, const TSString title);
TS_CAPI TSString TS_CCALL tsDialogProgress_getTitle(TSDialogProgress self);
TS_CAPI void TS_CCALL tsDialogProgress_setMessage_s(TSDialogProgress self, const char *message);
TS_CAPI void TS_CCALL tsDialogProgress_setMessage_cS(TSDialogProgress self, const TSString message);
TS_CAPI TSString TS_CCALL tsDialogProgress_getMessage(TSDialogProgress self);
TS_CAPI void TS_CCALL tsDialogProgress_setProgress(TSDialogProgress self, uint32_t progress);
TS_CAPI uint32_t TS_CCALL tsDialogProgress_getProgress(TSDialogProgress self);
TS_CAPI TS_DialogProgressResult TS_CCALL tsDialogProgress_run(TSDialogProgress self, TS_DialogProgressFlags flags);
TS_CAPI void TS_CCALL tsDialogProgress_close(TSDialogProgress self);

/// Tellusim::DialogColor
typedef void (*TSDialogColorChangedCallback)(TSColor a0, void *data_);
typedef bool_t (*TSDialogColorUpdateCallback)(void *data_);
TS_CAPI TSDialogColor TS_CCALL tsDialogColor_new_scC(const char *title, const TSColor *color);
TS_CAPI TSDialogColor TS_CCALL tsDialogColor_new_cScC(const TSString title, const TSColor *color);
TS_CAPI void TS_CCALL tsDialogColor_delete(TSDialogColor self);
TS_CAPI bool_t TS_CCALL tsDialogColor_equalPtr(const TSDialogColor self, const TSDialogColor ptr);
TS_CAPI TSDialogColor TS_CCALL tsDialogColor_copyPtr(const TSDialogColor self);
TS_CAPI TSDialogColor TS_CCALL tsDialogColor_clonePtr(const TSDialogColor self);
TS_CAPI void TS_CCALL tsDialogColor_clearPtr(TSDialogColor self);
TS_CAPI void TS_CCALL tsDialogColor_destroyPtr(TSDialogColor self);
TS_CAPI void TS_CCALL tsDialogColor_acquirePtr(TSDialogColor self);
TS_CAPI void TS_CCALL tsDialogColor_unacquirePtr(TSDialogColor self);
TS_CAPI bool_t TS_CCALL tsDialogColor_isValidPtr(const TSDialogColor self);
TS_CAPI bool_t TS_CCALL tsDialogColor_isOwnerPtr(const TSDialogColor self);
TS_CAPI bool_t TS_CCALL tsDialogColor_isConstPtr(const TSDialogColor self);
TS_CAPI uint32_t TS_CCALL tsDialogColor_getCountPtr(const TSDialogColor self);
TS_CAPI const void* TS_CCALL tsDialogColor_getInternalPtr(const TSDialogColor self);
TS_CAPI void TS_CCALL tsDialogColor_setPosition(TSDialogColor self, int32_t x, int32_t y);
TS_CAPI int32_t TS_CCALL tsDialogColor_getPositionX(TSDialogColor self);
TS_CAPI int32_t TS_CCALL tsDialogColor_getPositionY(TSDialogColor self);
TS_CAPI void TS_CCALL tsDialogColor_setTitle_s(TSDialogColor self, const char *title);
TS_CAPI void TS_CCALL tsDialogColor_setTitle_cS(TSDialogColor self, const TSString title);
TS_CAPI TSString TS_CCALL tsDialogColor_getTitle(TSDialogColor self);
TS_CAPI void TS_CCALL tsDialogColor_setColor(TSDialogColor self, const TSColor *color, bool_t callback);
TS_CAPI TSColor TS_CCALL tsDialogColor_getColor(TSDialogColor self);
TS_CAPI void TS_CCALL tsDialogColor_setChangedCallback(TSDialogColor self, const TSDialogColorChangedCallback func, void *data_);
TS_CAPI void TS_CCALL tsDialogColor_setUpdateCallback(TSDialogColor self, const TSDialogColorUpdateCallback func, void *data_);
TS_CAPI TS_DialogColorResult TS_CCALL tsDialogColor_run(TSDialogColor self, TS_DialogColorFlags flags);

/// Tellusim::DialogMenu
typedef void (*TSDialogMenuClickedCallback)(void *data_);
typedef void (*TSDialogMenuChangedCallback)(bool_t a0, void *data_);
typedef bool_t (*TSDialogMenuUpdateCallback)(void *data_);
TS_CAPI TSDialogMenu TS_CCALL tsDialogMenu_new(void);
TS_CAPI void TS_CCALL tsDialogMenu_delete(TSDialogMenu self);
TS_CAPI bool_t TS_CCALL tsDialogMenu_equalPtr(const TSDialogMenu self, const TSDialogMenu ptr);
TS_CAPI TSDialogMenu TS_CCALL tsDialogMenu_copyPtr(const TSDialogMenu self);
TS_CAPI TSDialogMenu TS_CCALL tsDialogMenu_clonePtr(const TSDialogMenu self);
TS_CAPI void TS_CCALL tsDialogMenu_clearPtr(TSDialogMenu self);
TS_CAPI void TS_CCALL tsDialogMenu_destroyPtr(TSDialogMenu self);
TS_CAPI void TS_CCALL tsDialogMenu_acquirePtr(TSDialogMenu self);
TS_CAPI void TS_CCALL tsDialogMenu_unacquirePtr(TSDialogMenu self);
TS_CAPI bool_t TS_CCALL tsDialogMenu_isValidPtr(const TSDialogMenu self);
TS_CAPI bool_t TS_CCALL tsDialogMenu_isOwnerPtr(const TSDialogMenu self);
TS_CAPI bool_t TS_CCALL tsDialogMenu_isConstPtr(const TSDialogMenu self);
TS_CAPI uint32_t TS_CCALL tsDialogMenu_getCountPtr(const TSDialogMenu self);
TS_CAPI const void* TS_CCALL tsDialogMenu_getInternalPtr(const TSDialogMenu self);
TS_CAPI void TS_CCALL tsDialogMenu_setPosition(TSDialogMenu self, int32_t x, int32_t y);
TS_CAPI int32_t TS_CCALL tsDialogMenu_getPositionX(TSDialogMenu self);
TS_CAPI int32_t TS_CCALL tsDialogMenu_getPositionY(TSDialogMenu self);
TS_CAPI uint32_t TS_CCALL tsDialogMenu_getNumItems(TSDialogMenu self);
TS_CAPI void TS_CCALL tsDialogMenu_setItemText_us(TSDialogMenu self, uint32_t index, const char *text);
TS_CAPI void TS_CCALL tsDialogMenu_setItemText_ucS(TSDialogMenu self, uint32_t index, const TSString text);
TS_CAPI TSString TS_CCALL tsDialogMenu_getItemText(TSDialogMenu self, uint32_t index);
TS_CAPI void TS_CCALL tsDialogMenu_setItemKey(TSDialogMenu self, uint32_t index, const char *key);
TS_CAPI TSString TS_CCALL tsDialogMenu_getItemKey(TSDialogMenu self, uint32_t index);
TS_CAPI void TS_CCALL tsDialogMenu_setItemImage(TSDialogMenu self, uint32_t index, const TSImage image);
TS_CAPI TSImage TS_CCALL tsDialogMenu_getItemImage(TSDialogMenu self, uint32_t index);
TS_CAPI void TS_CCALL tsDialogMenu_setItemChecked(TSDialogMenu self, uint32_t index, bool_t checked, bool_t callback);
TS_CAPI bool_t TS_CCALL tsDialogMenu_isItemChecked(TSDialogMenu self, uint32_t index);
TS_CAPI void TS_CCALL tsDialogMenu_setItemEnabled(TSDialogMenu self, uint32_t index, bool_t enabled);
TS_CAPI bool_t TS_CCALL tsDialogMenu_isItemEnabled(TSDialogMenu self, uint32_t index);
TS_CAPI void TS_CCALL tsDialogMenu_setItemHidden(TSDialogMenu self, uint32_t index, bool_t hidden);
TS_CAPI bool_t TS_CCALL tsDialogMenu_isItemHidden(TSDialogMenu self, uint32_t index);
TS_CAPI void TS_CCALL tsDialogMenu_setItemsGroup(TSDialogMenu self, uint32_t index, uint32_t size);
TS_CAPI uint32_t TS_CCALL tsDialogMenu_getItemGroupIndex(TSDialogMenu self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsDialogMenu_getItemGroupSize(TSDialogMenu self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsDialogMenu_addItem_ss(TSDialogMenu self, const char *text, const char *key);
TS_CAPI uint32_t TS_CCALL tsDialogMenu_addItem_cSs(TSDialogMenu self, const TSString text, const char *key);
TS_CAPI uint32_t TS_CCALL tsDialogMenu_addItem_scIs(TSDialogMenu self, const char *text, const TSImage image, const char *key);
TS_CAPI uint32_t TS_CCALL tsDialogMenu_addItem_cScIs(TSDialogMenu self, const TSString text, const TSImage image, const char *key);
TS_CAPI uint32_t TS_CCALL tsDialogMenu_addItem_scDMCCs(TSDialogMenu self, const char *text, const TSDialogMenuClickedCallback func, const char *key, void *data_);
TS_CAPI uint32_t TS_CCALL tsDialogMenu_addItem_cScDMCCs(TSDialogMenu self, const TSString text, const TSDialogMenuClickedCallback func, const char *key, void *data_);
TS_CAPI uint32_t TS_CCALL tsDialogMenu_addItem_scIcDMCCs(TSDialogMenu self, const char *text, const TSImage image, const TSDialogMenuClickedCallback func, const char *key, void *data_);
TS_CAPI uint32_t TS_CCALL tsDialogMenu_addItem_cScIcDMCCs(TSDialogMenu self, const TSString text, const TSImage image, const TSDialogMenuClickedCallback func, const char *key, void *data_);
TS_CAPI uint32_t TS_CCALL tsDialogMenu_addItem_sbcDMCCs(TSDialogMenu self, const char *text, bool_t checked, const TSDialogMenuChangedCallback func, const char *key, void *data_);
TS_CAPI uint32_t TS_CCALL tsDialogMenu_addItem_cSbcDMCCs(TSDialogMenu self, const TSString text, bool_t checked, const TSDialogMenuChangedCallback func, const char *key, void *data_);
TS_CAPI uint32_t TS_CCALL tsDialogMenu_addItem_scIbcDMCCs(TSDialogMenu self, const char *text, const TSImage image, bool_t checked, const TSDialogMenuChangedCallback func, const char *key, void *data_);
TS_CAPI uint32_t TS_CCALL tsDialogMenu_addItem_cScIbcDMCCs(TSDialogMenu self, const TSString text, const TSImage image, bool_t checked, const TSDialogMenuChangedCallback func, const char *key, void *data_);
TS_CAPI void TS_CCALL tsDialogMenu_setUpdateCallback(TSDialogMenu self, const TSDialogMenuUpdateCallback func, void *data_);
TS_CAPI TS_DialogMenuResult TS_CCALL tsDialogMenu_run(TSDialogMenu self, TS_DialogMenuFlags flags);

/// Tellusim::CubeFilter
TS_CAPI TSCubeFilter TS_CCALL tsCubeFilter_new(void);
TS_CAPI void TS_CCALL tsCubeFilter_delete(TSCubeFilter self);
TS_CAPI bool_t TS_CCALL tsCubeFilter_equalPtr(const TSCubeFilter self, const TSCubeFilter ptr);
TS_CAPI TSCubeFilter TS_CCALL tsCubeFilter_copyPtr(const TSCubeFilter self);
TS_CAPI TSCubeFilter TS_CCALL tsCubeFilter_clonePtr(const TSCubeFilter self);
TS_CAPI void TS_CCALL tsCubeFilter_clearPtr(TSCubeFilter self);
TS_CAPI void TS_CCALL tsCubeFilter_destroyPtr(TSCubeFilter self);
TS_CAPI void TS_CCALL tsCubeFilter_acquirePtr(TSCubeFilter self);
TS_CAPI void TS_CCALL tsCubeFilter_unacquirePtr(TSCubeFilter self);
TS_CAPI bool_t TS_CCALL tsCubeFilter_isValidPtr(const TSCubeFilter self);
TS_CAPI bool_t TS_CCALL tsCubeFilter_isOwnerPtr(const TSCubeFilter self);
TS_CAPI bool_t TS_CCALL tsCubeFilter_isConstPtr(const TSCubeFilter self);
TS_CAPI uint32_t TS_CCALL tsCubeFilter_getCountPtr(const TSCubeFilter self);
TS_CAPI const void* TS_CCALL tsCubeFilter_getInternalPtr(const TSCubeFilter self);
TS_CAPI void TS_CCALL tsCubeFilter_clear(TSCubeFilter self);
TS_CAPI bool_t TS_CCALL tsCubeFilter_isCreated(TSCubeFilter self, TS_CubeFilterMode mode);
TS_CAPI uint32_t TS_CCALL tsCubeFilter_getGroupSize(TSCubeFilter self);
TS_CAPI uint32_t TS_CCALL tsCubeFilter_getMaxOrder(TSCubeFilter self);
TS_CAPI uint32_t TS_CCALL tsCubeFilter_getMaxSize(TSCubeFilter self);
TS_CAPI uint32_t TS_CCALL tsCubeFilter_getHarmonics(TSCubeFilter self);
TS_CAPI bool_t TS_CCALL tsCubeFilter_create_cDCFMuuu(TSCubeFilter self, const TSDevice device, TS_CubeFilterMode mode, uint32_t order, uint32_t size, uint32_t groups);
TS_CAPI bool_t TS_CCALL tsCubeFilter_create_cDCFFuuu(TSCubeFilter self, const TSDevice device, TS_CubeFilterFlags flags, uint32_t order, uint32_t size, uint32_t groups);
TS_CAPI bool_t TS_CCALL tsCubeFilter_dispatch_cCBuTcS(TSCubeFilter self, TSCompute compute, TSBuffer buffer, uint32_t offset, TSTexture texture, const TSSlice *slice);
TS_CAPI bool_t TS_CCALL tsCubeFilter_dispatch_cCBuT(TSCubeFilter self, TSCompute compute, TSBuffer buffer, uint32_t offset, TSTexture texture);
TS_CAPI bool_t TS_CCALL tsCubeFilter_dispatch_cCTcSBu(TSCubeFilter self, TSCompute compute, TSTexture texture, const TSSlice *slice, TSBuffer buffer, uint32_t offset);
TS_CAPI bool_t TS_CCALL tsCubeFilter_dispatch_cCTBu(TSCubeFilter self, TSCompute compute, TSTexture texture, TSBuffer buffer, uint32_t offset);

/// Tellusim::DecoderJPEG
TS_CAPI TSDecoderJPEG TS_CCALL tsDecoderJPEG_new(void);
TS_CAPI void TS_CCALL tsDecoderJPEG_delete(TSDecoderJPEG self);
TS_CAPI bool_t TS_CCALL tsDecoderJPEG_equalPtr(const TSDecoderJPEG self, const TSDecoderJPEG ptr);
TS_CAPI TSDecoderJPEG TS_CCALL tsDecoderJPEG_copyPtr(const TSDecoderJPEG self);
TS_CAPI TSDecoderJPEG TS_CCALL tsDecoderJPEG_clonePtr(const TSDecoderJPEG self);
TS_CAPI void TS_CCALL tsDecoderJPEG_clearPtr(TSDecoderJPEG self);
TS_CAPI void TS_CCALL tsDecoderJPEG_destroyPtr(TSDecoderJPEG self);
TS_CAPI void TS_CCALL tsDecoderJPEG_acquirePtr(TSDecoderJPEG self);
TS_CAPI void TS_CCALL tsDecoderJPEG_unacquirePtr(TSDecoderJPEG self);
TS_CAPI bool_t TS_CCALL tsDecoderJPEG_isValidPtr(const TSDecoderJPEG self);
TS_CAPI bool_t TS_CCALL tsDecoderJPEG_isOwnerPtr(const TSDecoderJPEG self);
TS_CAPI bool_t TS_CCALL tsDecoderJPEG_isConstPtr(const TSDecoderJPEG self);
TS_CAPI uint32_t TS_CCALL tsDecoderJPEG_getCountPtr(const TSDecoderJPEG self);
TS_CAPI const void* TS_CCALL tsDecoderJPEG_getInternalPtr(const TSDecoderJPEG self);
TS_CAPI void TS_CCALL tsDecoderJPEG_clear(TSDecoderJPEG self);
TS_CAPI bool_t TS_CCALL tsDecoderJPEG_isCreated(TSDecoderJPEG self, TS_DecoderJPEGMode mode);
TS_CAPI bool_t TS_CCALL tsDecoderJPEG_isYUV(TS_DecoderJPEGMode mode);
TS_CAPI bool_t TS_CCALL tsDecoderJPEG_create_cDDJM(TSDecoderJPEG self, const TSDevice device, TS_DecoderJPEGMode mode);
TS_CAPI bool_t TS_CCALL tsDecoderJPEG_create_cDDJF(TSDecoderJPEG self, const TSDevice device, TS_DecoderJPEGFlags flags);
TS_CAPI bool_t TS_CCALL tsDecoderJPEG_load_sIDJMS(const char *name, TSImage image, TS_DecoderJPEGMode *mode, TSSize *size);
TS_CAPI bool_t TS_CCALL tsDecoderJPEG_load_StIDJMS(TSStream stream, TSImage image, TS_DecoderJPEGMode *mode, TSSize *size);
TS_CAPI TSTexture TS_CCALL tsDecoderJPEG_loadTexture_ccDsTF(TSDecoderJPEG self, const TSDevice device, const char *name, TS_TextureFlags flags);
TS_CAPI TSTexture TS_CCALL tsDecoderJPEG_loadTexture_ccDStTF(TSDecoderJPEG self, const TSDevice device, TSStream stream, TS_TextureFlags flags);
TS_CAPI bool_t TS_CCALL tsDecoderJPEG_dispatch_cCDJMTTcScS(TSDecoderJPEG self, TSCompute compute, TS_DecoderJPEGMode mode, TSTexture dest, TSTexture src, const TSSlice *dest_slice, const TSSlice *src_slice);
TS_CAPI bool_t TS_CCALL tsDecoderJPEG_dispatch_cCDJMTTcS(TSDecoderJPEG self, TSCompute compute, TS_DecoderJPEGMode mode, TSTexture dest, TSTexture src, const TSSlice *src_slice);
TS_CAPI bool_t TS_CCALL tsDecoderJPEG_dispatch_cCDJMTT(TSDecoderJPEG self, TSCompute compute, TS_DecoderJPEGMode mode, TSTexture dest, TSTexture src);
TS_CAPI bool_t TS_CCALL tsDecoderJPEG_dispatchYUV_cCDJMTTcScS(TSDecoderJPEG self, TSCompute compute, TS_DecoderJPEGMode mode, TSTexture dest, TSTexture src, const TSSlice *dest_slice, const TSSlice *src_slice);
TS_CAPI bool_t TS_CCALL tsDecoderJPEG_dispatchYUV_cCDJMTTcS(TSDecoderJPEG self, TSCompute compute, TS_DecoderJPEGMode mode, TSTexture dest, TSTexture src, const TSSlice *src_slice);
TS_CAPI bool_t TS_CCALL tsDecoderJPEG_dispatchYUV_cCDJMTT(TSDecoderJPEG self, TSCompute compute, TS_DecoderJPEGMode mode, TSTexture dest, TSTexture src);

/// Tellusim::EncoderBC15
TS_CAPI TSEncoderBC15 TS_CCALL tsEncoderBC15_new(void);
TS_CAPI void TS_CCALL tsEncoderBC15_delete(TSEncoderBC15 self);
TS_CAPI bool_t TS_CCALL tsEncoderBC15_equalPtr(const TSEncoderBC15 self, const TSEncoderBC15 ptr);
TS_CAPI TSEncoderBC15 TS_CCALL tsEncoderBC15_copyPtr(const TSEncoderBC15 self);
TS_CAPI TSEncoderBC15 TS_CCALL tsEncoderBC15_clonePtr(const TSEncoderBC15 self);
TS_CAPI void TS_CCALL tsEncoderBC15_clearPtr(TSEncoderBC15 self);
TS_CAPI void TS_CCALL tsEncoderBC15_destroyPtr(TSEncoderBC15 self);
TS_CAPI void TS_CCALL tsEncoderBC15_acquirePtr(TSEncoderBC15 self);
TS_CAPI void TS_CCALL tsEncoderBC15_unacquirePtr(TSEncoderBC15 self);
TS_CAPI bool_t TS_CCALL tsEncoderBC15_isValidPtr(const TSEncoderBC15 self);
TS_CAPI bool_t TS_CCALL tsEncoderBC15_isOwnerPtr(const TSEncoderBC15 self);
TS_CAPI bool_t TS_CCALL tsEncoderBC15_isConstPtr(const TSEncoderBC15 self);
TS_CAPI uint32_t TS_CCALL tsEncoderBC15_getCountPtr(const TSEncoderBC15 self);
TS_CAPI const void* TS_CCALL tsEncoderBC15_getInternalPtr(const TSEncoderBC15 self);
TS_CAPI void TS_CCALL tsEncoderBC15_clear(TSEncoderBC15 self);
TS_CAPI bool_t TS_CCALL tsEncoderBC15_isCreated(TSEncoderBC15 self, TS_EncoderBC15Mode mode);
TS_CAPI bool_t TS_CCALL tsEncoderBC15_create_cDEB15M(TSEncoderBC15 self, const TSDevice device, TS_EncoderBC15Mode mode);
TS_CAPI bool_t TS_CCALL tsEncoderBC15_create_cDEB15F(TSEncoderBC15 self, const TSDevice device, TS_EncoderBC15Flags flags);
TS_CAPI bool_t TS_CCALL tsEncoderBC15_dispatch_cCEB15MTTcScS(TSEncoderBC15 self, TSCompute compute, TS_EncoderBC15Mode mode, TSTexture dest, TSTexture src, const TSSlice *dest_slice, const TSSlice *src_slice);
TS_CAPI bool_t TS_CCALL tsEncoderBC15_dispatch_cCEB15MTTcS(TSEncoderBC15 self, TSCompute compute, TS_EncoderBC15Mode mode, TSTexture dest, TSTexture src, const TSSlice *src_slice);
TS_CAPI bool_t TS_CCALL tsEncoderBC15_dispatch_cCEB15MTT(TSEncoderBC15 self, TSCompute compute, TS_EncoderBC15Mode mode, TSTexture dest, TSTexture src);

/// Tellusim::EncoderBC67
TS_CAPI TSEncoderBC67 TS_CCALL tsEncoderBC67_new(void);
TS_CAPI void TS_CCALL tsEncoderBC67_delete(TSEncoderBC67 self);
TS_CAPI bool_t TS_CCALL tsEncoderBC67_equalPtr(const TSEncoderBC67 self, const TSEncoderBC67 ptr);
TS_CAPI TSEncoderBC67 TS_CCALL tsEncoderBC67_copyPtr(const TSEncoderBC67 self);
TS_CAPI TSEncoderBC67 TS_CCALL tsEncoderBC67_clonePtr(const TSEncoderBC67 self);
TS_CAPI void TS_CCALL tsEncoderBC67_clearPtr(TSEncoderBC67 self);
TS_CAPI void TS_CCALL tsEncoderBC67_destroyPtr(TSEncoderBC67 self);
TS_CAPI void TS_CCALL tsEncoderBC67_acquirePtr(TSEncoderBC67 self);
TS_CAPI void TS_CCALL tsEncoderBC67_unacquirePtr(TSEncoderBC67 self);
TS_CAPI bool_t TS_CCALL tsEncoderBC67_isValidPtr(const TSEncoderBC67 self);
TS_CAPI bool_t TS_CCALL tsEncoderBC67_isOwnerPtr(const TSEncoderBC67 self);
TS_CAPI bool_t TS_CCALL tsEncoderBC67_isConstPtr(const TSEncoderBC67 self);
TS_CAPI uint32_t TS_CCALL tsEncoderBC67_getCountPtr(const TSEncoderBC67 self);
TS_CAPI const void* TS_CCALL tsEncoderBC67_getInternalPtr(const TSEncoderBC67 self);
TS_CAPI void TS_CCALL tsEncoderBC67_clear(TSEncoderBC67 self);
TS_CAPI bool_t TS_CCALL tsEncoderBC67_isCreated(TSEncoderBC67 self, TS_EncoderBC67Mode mode);
TS_CAPI bool_t TS_CCALL tsEncoderBC67_create_cDEB67M(TSEncoderBC67 self, const TSDevice device, TS_EncoderBC67Mode mode);
TS_CAPI bool_t TS_CCALL tsEncoderBC67_create_cDEB67F(TSEncoderBC67 self, const TSDevice device, TS_EncoderBC67Flags flags);
TS_CAPI bool_t TS_CCALL tsEncoderBC67_dispatch_cCEB67MTTcScSu(TSEncoderBC67 self, TSCompute compute, TS_EncoderBC67Mode mode, TSTexture dest, TSTexture src, const TSSlice *dest_slice, const TSSlice *src_slice, uint32_t components);
TS_CAPI bool_t TS_CCALL tsEncoderBC67_dispatch_cCEB67MTTcSu(TSEncoderBC67 self, TSCompute compute, TS_EncoderBC67Mode mode, TSTexture dest, TSTexture src, const TSSlice *src_slice, uint32_t components);
TS_CAPI bool_t TS_CCALL tsEncoderBC67_dispatch_cCEB67MTTu(TSEncoderBC67 self, TSCompute compute, TS_EncoderBC67Mode mode, TSTexture dest, TSTexture src, uint32_t components);

/// Tellusim::EncoderASTC
TS_CAPI TSEncoderASTC TS_CCALL tsEncoderASTC_new(void);
TS_CAPI void TS_CCALL tsEncoderASTC_delete(TSEncoderASTC self);
TS_CAPI bool_t TS_CCALL tsEncoderASTC_equalPtr(const TSEncoderASTC self, const TSEncoderASTC ptr);
TS_CAPI TSEncoderASTC TS_CCALL tsEncoderASTC_copyPtr(const TSEncoderASTC self);
TS_CAPI TSEncoderASTC TS_CCALL tsEncoderASTC_clonePtr(const TSEncoderASTC self);
TS_CAPI void TS_CCALL tsEncoderASTC_clearPtr(TSEncoderASTC self);
TS_CAPI void TS_CCALL tsEncoderASTC_destroyPtr(TSEncoderASTC self);
TS_CAPI void TS_CCALL tsEncoderASTC_acquirePtr(TSEncoderASTC self);
TS_CAPI void TS_CCALL tsEncoderASTC_unacquirePtr(TSEncoderASTC self);
TS_CAPI bool_t TS_CCALL tsEncoderASTC_isValidPtr(const TSEncoderASTC self);
TS_CAPI bool_t TS_CCALL tsEncoderASTC_isOwnerPtr(const TSEncoderASTC self);
TS_CAPI bool_t TS_CCALL tsEncoderASTC_isConstPtr(const TSEncoderASTC self);
TS_CAPI uint32_t TS_CCALL tsEncoderASTC_getCountPtr(const TSEncoderASTC self);
TS_CAPI const void* TS_CCALL tsEncoderASTC_getInternalPtr(const TSEncoderASTC self);
TS_CAPI void TS_CCALL tsEncoderASTC_clear(TSEncoderASTC self);
TS_CAPI bool_t TS_CCALL tsEncoderASTC_isCreated(TSEncoderASTC self, TS_EncoderASTCMode mode);
TS_CAPI bool_t TS_CCALL tsEncoderASTC_create_cDEAM(TSEncoderASTC self, const TSDevice device, TS_EncoderASTCMode mode);
TS_CAPI bool_t TS_CCALL tsEncoderASTC_create_cDEAF(TSEncoderASTC self, const TSDevice device, TS_EncoderASTCFlags flags);
TS_CAPI bool_t TS_CCALL tsEncoderASTC_dispatch_cCEAMTTcScSu(TSEncoderASTC self, TSCompute compute, TS_EncoderASTCMode mode, TSTexture dest, TSTexture src, const TSSlice *dest_slice, const TSSlice *src_slice, uint32_t components);
TS_CAPI bool_t TS_CCALL tsEncoderASTC_dispatch_cCEAMTTcSu(TSEncoderASTC self, TSCompute compute, TS_EncoderASTCMode mode, TSTexture dest, TSTexture src, const TSSlice *src_slice, uint32_t components);
TS_CAPI bool_t TS_CCALL tsEncoderASTC_dispatch_cCEAMTTu(TSEncoderASTC self, TSCompute compute, TS_EncoderASTCMode mode, TSTexture dest, TSTexture src, uint32_t components);

/// Tellusim::MeshModel
typedef bool_t (*TSMeshModelCreateCallback)(const void *src, size_t size, bool_t owner, void *data_);
TS_CAPI TSMeshModel TS_CCALL tsMeshModel_new(void);
TS_CAPI void TS_CCALL tsMeshModel_delete(TSMeshModel self);
TS_CAPI void TS_CCALL tsMeshModel_clear(TSMeshModel self);
TS_CAPI bool_t TS_CCALL tsMeshModel_isCreated(TSMeshModel self);
TS_CAPI TS_MeshModelFlags TS_CCALL tsMeshModel_getFlags(TSMeshModel self);
TS_CAPI bool_t TS_CCALL tsMeshModel_hasFlag(TSMeshModel self, TS_MeshModelFlags flags);
TS_CAPI bool_t TS_CCALL tsMeshModel_hasFlags(TSMeshModel self, TS_MeshModelFlags flags);
TS_CAPI bool_t TS_CCALL tsMeshModel_load_cDcPsMMFA(TSMeshModel self, const TSDevice device, const TSPipeline pipeline, const char *name, TS_MeshModelFlags flags, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMeshModel_load_cDcPStMMFA(TSMeshModel self, const TSDevice device, const TSPipeline pipeline, TSStream stream, TS_MeshModelFlags flags, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsMeshModel_create_cDcPsMMF(TSMeshModel self, const TSDevice device, const TSPipeline pipeline, const char *name, TS_MeshModelFlags flags);
TS_CAPI bool_t TS_CCALL tsMeshModel_create_cDcPcMMMF(TSMeshModel self, const TSDevice device, const TSPipeline pipeline, const TSMesh mesh, TS_MeshModelFlags flags);
TS_CAPI bool_t TS_CCALL tsMeshModel_create_cDcPcMGMMF(TSMeshModel self, const TSDevice device, const TSPipeline pipeline, const TSMeshGeometry geometry, TS_MeshModelFlags flags);
TS_CAPI bool_t TS_CCALL tsMeshModel_create_cDcPcAMGMMF(TSMeshModel self, const TSDevice device, const TSPipeline pipeline, const TSMeshGeometry *geometries, uint32_t geometries_size, TS_MeshModelFlags flags);
TS_CAPI void TS_CCALL tsMeshModel_setVertexBufferCallback(TSMeshModel self, const TSMeshModelCreateCallback func, void *data_);
TS_CAPI void TS_CCALL tsMeshModel_setIndexBufferCallback(TSMeshModel self, const TSMeshModelCreateCallback func, void *data_);
TS_CAPI void TS_CCALL tsMeshModel_setMeshBufferCallback(TSMeshModel self, const TSMeshModelCreateCallback func, void *data_);
TS_CAPI void TS_CCALL tsMeshModel_setBuffers(TSMeshModel self, TSCommand command, uint32_t index, const TSPipeline *pipeline);
TS_CAPI void TS_CCALL tsMeshModel_draw_cC(TSMeshModel self, TSCommand command);
TS_CAPI void TS_CCALL tsMeshModel_draw_cCu(TSMeshModel self, TSCommand command, uint32_t geometry);
TS_CAPI void TS_CCALL tsMeshModel_draw_cCuu(TSMeshModel self, TSCommand command, uint32_t geometry, uint32_t material);
TS_CAPI void TS_CCALL tsMeshModel_drawInstanced_cCuuu(TSMeshModel self, TSCommand command, uint32_t geometry, uint32_t num_instances, uint32_t base_instance);
TS_CAPI void TS_CCALL tsMeshModel_drawInstanced_cCuuuu(TSMeshModel self, TSCommand command, uint32_t geometry, uint32_t material, uint32_t num_instances, uint32_t base_instance);
TS_CAPI uint32_t TS_CCALL tsMeshModel_getNumVertices(TSMeshModel self);
TS_CAPI uint32_t TS_CCALL tsMeshModel_getNumVertexBuffers(TSMeshModel self);
TS_CAPI uint32_t TS_CCALL tsMeshModel_getVertexBufferStride(TSMeshModel self, uint32_t index);
TS_CAPI size_t TS_CCALL tsMeshModel_getVertexBufferOffset(TSMeshModel self, uint32_t index);
TS_CAPI TSBuffer TS_CCALL tsMeshModel_getVertexBuffer(TSMeshModel self);
TS_CAPI uint32_t TS_CCALL tsMeshModel_getNumIndices(TSMeshModel self);
TS_CAPI TS_Format TS_CCALL tsMeshModel_getIndexFormat(TSMeshModel self);
TS_CAPI TSBuffer TS_CCALL tsMeshModel_getIndexBuffer(TSMeshModel self);
TS_CAPI uint32_t TS_CCALL tsMeshModel_getNumMeshlets(TSMeshModel self);
TS_CAPI TSBuffer TS_CCALL tsMeshModel_getMeshletBuffer(TSMeshModel self);
TS_CAPI uint32_t TS_CCALL tsMeshModel_getNumGeometries(TSMeshModel self);
TS_CAPI uint32_t TS_CCALL tsMeshModel_getNumGeometryIndices(TSMeshModel self, uint32_t geometry);
TS_CAPI uint32_t TS_CCALL tsMeshModel_getNumGeometryVertices(TSMeshModel self, uint32_t geometry);
TS_CAPI uint32_t TS_CCALL tsMeshModel_getNumGeometryMeshlets(TSMeshModel self, uint32_t geometry);
TS_CAPI uint32_t TS_CCALL tsMeshModel_getGeometryBaseIndex(TSMeshModel self, uint32_t geometry);
TS_CAPI uint32_t TS_CCALL tsMeshModel_getGeometryBaseVertex(TSMeshModel self, uint32_t geometry);
TS_CAPI uint32_t TS_CCALL tsMeshModel_getGeometryBaseMeshlet(TSMeshModel self, uint32_t geometry);
TS_CAPI uint32_t TS_CCALL tsMeshModel_getNumMaterials(TSMeshModel self, uint32_t geometry);
TS_CAPI uint32_t TS_CCALL tsMeshModel_getNumMaterialIndices(TSMeshModel self, uint32_t geometry, uint32_t material);
TS_CAPI uint32_t TS_CCALL tsMeshModel_getNumMaterialVertices(TSMeshModel self, uint32_t geometry, uint32_t material);
TS_CAPI uint32_t TS_CCALL tsMeshModel_getNumMaterialMeshlets(TSMeshModel self, uint32_t geometry, uint32_t material);
TS_CAPI uint32_t TS_CCALL tsMeshModel_getMaterialBaseIndex(TSMeshModel self, uint32_t geometry, uint32_t material);
TS_CAPI uint32_t TS_CCALL tsMeshModel_getMaterialBaseVertex(TSMeshModel self, uint32_t geometry, uint32_t material);
TS_CAPI uint32_t TS_CCALL tsMeshModel_getMaterialBaseMeshlet(TSMeshModel self, uint32_t geometry, uint32_t material);
TS_CAPI size_t TS_CCALL tsMeshModel_getMemory(TSMeshModel self);

/// Tellusim::SeparableFilter
TS_CAPI TSSeparableFilter TS_CCALL tsSeparableFilter_new(void);
TS_CAPI void TS_CCALL tsSeparableFilter_delete(TSSeparableFilter self);
TS_CAPI bool_t TS_CCALL tsSeparableFilter_equalPtr(const TSSeparableFilter self, const TSSeparableFilter ptr);
TS_CAPI TSSeparableFilter TS_CCALL tsSeparableFilter_copyPtr(const TSSeparableFilter self);
TS_CAPI TSSeparableFilter TS_CCALL tsSeparableFilter_clonePtr(const TSSeparableFilter self);
TS_CAPI void TS_CCALL tsSeparableFilter_clearPtr(TSSeparableFilter self);
TS_CAPI void TS_CCALL tsSeparableFilter_destroyPtr(TSSeparableFilter self);
TS_CAPI void TS_CCALL tsSeparableFilter_acquirePtr(TSSeparableFilter self);
TS_CAPI void TS_CCALL tsSeparableFilter_unacquirePtr(TSSeparableFilter self);
TS_CAPI bool_t TS_CCALL tsSeparableFilter_isValidPtr(const TSSeparableFilter self);
TS_CAPI bool_t TS_CCALL tsSeparableFilter_isOwnerPtr(const TSSeparableFilter self);
TS_CAPI bool_t TS_CCALL tsSeparableFilter_isConstPtr(const TSSeparableFilter self);
TS_CAPI uint32_t TS_CCALL tsSeparableFilter_getCountPtr(const TSSeparableFilter self);
TS_CAPI const void* TS_CCALL tsSeparableFilter_getInternalPtr(const TSSeparableFilter self);
TS_CAPI void TS_CCALL tsSeparableFilter_clear(TSSeparableFilter self);
TS_CAPI bool_t TS_CCALL tsSeparableFilter_isCreated(TSSeparableFilter self, TS_Format format, uint32_t size);
TS_CAPI void TS_CCALL tsSeparableFilter_setInputSource(TSSeparableFilter self, TS_SeparableFilterMode mode, const char *src);
TS_CAPI TSString TS_CCALL tsSeparableFilter_getInputSource(TSSeparableFilter self, TS_SeparableFilterMode mode);
TS_CAPI void TS_CCALL tsSeparableFilter_setKernelSource(TSSeparableFilter self, TS_SeparableFilterMode mode, const char *src);
TS_CAPI TSString TS_CCALL tsSeparableFilter_getKernelSource(TSSeparableFilter self, TS_SeparableFilterMode mode);
TS_CAPI void TS_CCALL tsSeparableFilter_setOutputSource(TSSeparableFilter self, TS_SeparableFilterMode mode, const char *src);
TS_CAPI TSString TS_CCALL tsSeparableFilter_getOutputSource(TSSeparableFilter self, TS_SeparableFilterMode mode);
TS_CAPI bool_t TS_CCALL tsSeparableFilter_create(TSSeparableFilter self, const TSDevice device, TS_Format format, uint32_t size, TS_SeparableFilterFlags flags);
TS_CAPI void TS_CCALL tsSeparableFilter_setWeights_SFMcAV4b(TSSeparableFilter self, TS_SeparableFilterMode mode, const TSVector4f *weights, uint32_t weights_size, bool_t normalize);
TS_CAPI void TS_CCALL tsSeparableFilter_setWeights_SFMcA32b(TSSeparableFilter self, TS_SeparableFilterMode mode, const float32_t *weights, uint32_t weights_size, bool_t normalize);
TS_CAPI void TS_CCALL tsSeparableFilter_setGaussianWeights_ucV4(TSSeparableFilter self, uint32_t size, const TSVector4f *sigma);
TS_CAPI void TS_CCALL tsSeparableFilter_setGaussianWeights_uf(TSSeparableFilter self, uint32_t size, float32_t sigma);
TS_CAPI void TS_CCALL tsSeparableFilter_setSobelXWeights(TSSeparableFilter self, uint32_t size);
TS_CAPI void TS_CCALL tsSeparableFilter_setSobelYWeights(TSSeparableFilter self, uint32_t size);
TS_CAPI void TS_CCALL tsSeparableFilter_setBoxWeights(TSSeparableFilter self, uint32_t size);
TS_CAPI bool_t TS_CCALL tsSeparableFilter_dispatch_cCSFMuTTcScScV4(TSSeparableFilter self, TSCompute compute, TS_SeparableFilterMode mode, uint32_t size, TSTexture dest, TSTexture src, const TSSlice *dest_slice, const TSSlice *src_slice, const TSVector4f *parameters);
TS_CAPI bool_t TS_CCALL tsSeparableFilter_dispatch_cCSFMuTTcScV4(TSSeparableFilter self, TSCompute compute, TS_SeparableFilterMode mode, uint32_t size, TSTexture dest, TSTexture src, const TSSlice *src_slice, const TSVector4f *parameters);
TS_CAPI bool_t TS_CCALL tsSeparableFilter_dispatch_cCSFMuTTcV4(TSSeparableFilter self, TSCompute compute, TS_SeparableFilterMode mode, uint32_t size, TSTexture dest, TSTexture src, const TSVector4f *parameters);

/// Tellusim::PrefixScan
TS_CAPI TSPrefixScan TS_CCALL tsPrefixScan_new(void);
TS_CAPI void TS_CCALL tsPrefixScan_delete(TSPrefixScan self);
TS_CAPI bool_t TS_CCALL tsPrefixScan_equalPtr(const TSPrefixScan self, const TSPrefixScan ptr);
TS_CAPI TSPrefixScan TS_CCALL tsPrefixScan_copyPtr(const TSPrefixScan self);
TS_CAPI TSPrefixScan TS_CCALL tsPrefixScan_clonePtr(const TSPrefixScan self);
TS_CAPI void TS_CCALL tsPrefixScan_clearPtr(TSPrefixScan self);
TS_CAPI void TS_CCALL tsPrefixScan_destroyPtr(TSPrefixScan self);
TS_CAPI void TS_CCALL tsPrefixScan_acquirePtr(TSPrefixScan self);
TS_CAPI void TS_CCALL tsPrefixScan_unacquirePtr(TSPrefixScan self);
TS_CAPI bool_t TS_CCALL tsPrefixScan_isValidPtr(const TSPrefixScan self);
TS_CAPI bool_t TS_CCALL tsPrefixScan_isOwnerPtr(const TSPrefixScan self);
TS_CAPI bool_t TS_CCALL tsPrefixScan_isConstPtr(const TSPrefixScan self);
TS_CAPI uint32_t TS_CCALL tsPrefixScan_getCountPtr(const TSPrefixScan self);
TS_CAPI const void* TS_CCALL tsPrefixScan_getInternalPtr(const TSPrefixScan self);
TS_CAPI void TS_CCALL tsPrefixScan_clear(TSPrefixScan self);
TS_CAPI bool_t TS_CCALL tsPrefixScan_isCreated(TSPrefixScan self, TS_PrefixScanFlags flags);
TS_CAPI uint32_t TS_CCALL tsPrefixScan_getGroupSize(TSPrefixScan self);
TS_CAPI uint32_t TS_CCALL tsPrefixScan_getScanElements(TSPrefixScan self);
TS_CAPI uint32_t TS_CCALL tsPrefixScan_getMaxElements(TSPrefixScan self);
TS_CAPI uint32_t TS_CCALL tsPrefixScan_getMaxRegions(TSPrefixScan self);
TS_CAPI bool_t TS_CCALL tsPrefixScan_create_cDPSMuuA(TSPrefixScan self, const TSDevice device, TS_PrefixScanMode mode, uint32_t groups, uint32_t regions, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsPrefixScan_create_cDPSFuuA(TSPrefixScan self, const TSDevice device, TS_PrefixScanFlags flags, uint32_t groups, uint32_t regions, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsPrefixScan_dispatch_CBuu(TSPrefixScan self, TSCompute compute, TSBuffer data, uint32_t offset, uint32_t size);
TS_CAPI bool_t TS_CCALL tsPrefixScan_dispatch_CBuupupPSF(TSPrefixScan self, TSCompute compute, TSBuffer data, uint32_t count, const uint32_t *offsets, const uint32_t *sizes, TS_PrefixScanFlags flags);
TS_CAPI bool_t TS_CCALL tsPrefixScan_dispatchIndirect_CBBuPSFu(TSPrefixScan self, TSCompute compute, TSBuffer data, TSBuffer dispatch, uint32_t offset, TS_PrefixScanFlags flags, uint32_t max_size);
TS_CAPI bool_t TS_CCALL tsPrefixScan_dispatchIndirect_CBuBuPSFu(TSPrefixScan self, TSCompute compute, TSBuffer data, uint32_t count, TSBuffer dispatch, uint32_t offset, TS_PrefixScanFlags flags, uint32_t max_size);
TS_CAPI bool_t TS_CCALL tsPrefixScan_dispatchIndirect_CBBBuuPSFu(TSPrefixScan self, TSCompute compute, TSBuffer data, TSBuffer count, TSBuffer dispatch, uint32_t count_offset, uint32_t dispatch_offset, TS_PrefixScanFlags flags, uint32_t max_size);

/// Tellusim::RadixSort
TS_CAPI TSRadixSort TS_CCALL tsRadixSort_new(void);
TS_CAPI void TS_CCALL tsRadixSort_delete(TSRadixSort self);
TS_CAPI bool_t TS_CCALL tsRadixSort_equalPtr(const TSRadixSort self, const TSRadixSort ptr);
TS_CAPI TSRadixSort TS_CCALL tsRadixSort_copyPtr(const TSRadixSort self);
TS_CAPI TSRadixSort TS_CCALL tsRadixSort_clonePtr(const TSRadixSort self);
TS_CAPI void TS_CCALL tsRadixSort_clearPtr(TSRadixSort self);
TS_CAPI void TS_CCALL tsRadixSort_destroyPtr(TSRadixSort self);
TS_CAPI void TS_CCALL tsRadixSort_acquirePtr(TSRadixSort self);
TS_CAPI void TS_CCALL tsRadixSort_unacquirePtr(TSRadixSort self);
TS_CAPI bool_t TS_CCALL tsRadixSort_isValidPtr(const TSRadixSort self);
TS_CAPI bool_t TS_CCALL tsRadixSort_isOwnerPtr(const TSRadixSort self);
TS_CAPI bool_t TS_CCALL tsRadixSort_isConstPtr(const TSRadixSort self);
TS_CAPI uint32_t TS_CCALL tsRadixSort_getCountPtr(const TSRadixSort self);
TS_CAPI const void* TS_CCALL tsRadixSort_getInternalPtr(const TSRadixSort self);
TS_CAPI void TS_CCALL tsRadixSort_clear(TSRadixSort self);
TS_CAPI bool_t TS_CCALL tsRadixSort_isCreated(TSRadixSort self, TS_RadixSortFlags flags);
TS_CAPI uint32_t TS_CCALL tsRadixSort_getDataSize(TSRadixSort self);
TS_CAPI uint32_t TS_CCALL tsRadixSort_getGroupSize(TSRadixSort self);
TS_CAPI uint32_t TS_CCALL tsRadixSort_getSortElements(TSRadixSort self);
TS_CAPI uint32_t TS_CCALL tsRadixSort_getUpdateElements(TSRadixSort self);
TS_CAPI uint32_t TS_CCALL tsRadixSort_getMaxElements(TSRadixSort self);
TS_CAPI uint32_t TS_CCALL tsRadixSort_getMaxRegions(TSRadixSort self);
TS_CAPI TSPrefixScan TS_CCALL tsRadixSort_getPrefixScan(TSRadixSort self);
TS_CAPI TSBuffer TS_CCALL tsRadixSort_getDataBuffer(TSRadixSort self);
TS_CAPI bool_t TS_CCALL tsRadixSort_create_cDRSMPSuuuA(TSRadixSort self, const TSDevice device, TS_RadixSortMode mode, TSPrefixScan scan, uint32_t size, uint32_t groups, uint32_t regions, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsRadixSort_create_cDRSFPSuuuA(TSRadixSort self, const TSDevice device, TS_RadixSortFlags flags, TSPrefixScan scan, uint32_t size, uint32_t groups, uint32_t regions, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsRadixSort_dispatch_CBuuuRSFu(TSRadixSort self, TSCompute compute, TSBuffer data, uint32_t keys_offset, uint32_t data_offset, uint32_t size, TS_RadixSortFlags flags, uint32_t bits);
TS_CAPI bool_t TS_CCALL tsRadixSort_dispatch_CBuupupupRSFu(TSRadixSort self, TSCompute compute, TSBuffer data, uint32_t count, const uint32_t *keys_offsets, const uint32_t *data_offsets, const uint32_t *sizes, TS_RadixSortFlags flags, uint32_t bits);
TS_CAPI bool_t TS_CCALL tsRadixSort_dispatchIndirect_CBBuRSFuu(TSRadixSort self, TSCompute compute, TSBuffer data, TSBuffer dispatch, uint32_t offset, TS_RadixSortFlags flags, uint32_t bits, uint32_t max_size);
TS_CAPI bool_t TS_CCALL tsRadixSort_dispatchIndirect_CBuBuRSFuu(TSRadixSort self, TSCompute compute, TSBuffer data, uint32_t count, TSBuffer dispatch, uint32_t offset, TS_RadixSortFlags flags, uint32_t bits, uint32_t max_size);
TS_CAPI bool_t TS_CCALL tsRadixSort_dispatchIndirect_CBBBuuRSFuu(TSRadixSort self, TSCompute compute, TSBuffer data, TSBuffer count, TSBuffer dispatch, uint32_t count_offset, uint32_t dispatch_offset, TS_RadixSortFlags flags, uint32_t bits, uint32_t max_size);

/// Tellusim::BitonicSort
TS_CAPI TSBitonicSort TS_CCALL tsBitonicSort_new(void);
TS_CAPI void TS_CCALL tsBitonicSort_delete(TSBitonicSort self);
TS_CAPI bool_t TS_CCALL tsBitonicSort_equalPtr(const TSBitonicSort self, const TSBitonicSort ptr);
TS_CAPI TSBitonicSort TS_CCALL tsBitonicSort_copyPtr(const TSBitonicSort self);
TS_CAPI TSBitonicSort TS_CCALL tsBitonicSort_clonePtr(const TSBitonicSort self);
TS_CAPI void TS_CCALL tsBitonicSort_clearPtr(TSBitonicSort self);
TS_CAPI void TS_CCALL tsBitonicSort_destroyPtr(TSBitonicSort self);
TS_CAPI void TS_CCALL tsBitonicSort_acquirePtr(TSBitonicSort self);
TS_CAPI void TS_CCALL tsBitonicSort_unacquirePtr(TSBitonicSort self);
TS_CAPI bool_t TS_CCALL tsBitonicSort_isValidPtr(const TSBitonicSort self);
TS_CAPI bool_t TS_CCALL tsBitonicSort_isOwnerPtr(const TSBitonicSort self);
TS_CAPI bool_t TS_CCALL tsBitonicSort_isConstPtr(const TSBitonicSort self);
TS_CAPI uint32_t TS_CCALL tsBitonicSort_getCountPtr(const TSBitonicSort self);
TS_CAPI const void* TS_CCALL tsBitonicSort_getInternalPtr(const TSBitonicSort self);
TS_CAPI void TS_CCALL tsBitonicSort_clear(TSBitonicSort self);
TS_CAPI bool_t TS_CCALL tsBitonicSort_isCreated(TSBitonicSort self, TS_BitonicSortFlags flags);
TS_CAPI uint32_t TS_CCALL tsBitonicSort_getDataSize(TSBitonicSort self);
TS_CAPI uint32_t TS_CCALL tsBitonicSort_getGroupSize(TSBitonicSort self);
TS_CAPI uint32_t TS_CCALL tsBitonicSort_getSortElements(TSBitonicSort self);
TS_CAPI uint32_t TS_CCALL tsBitonicSort_getMaxRegions(TSBitonicSort self);
TS_CAPI bool_t TS_CCALL tsBitonicSort_create_cDBSMuuuA(TSBitonicSort self, const TSDevice device, TS_BitonicSortMode mode, uint32_t size, uint32_t groups, uint32_t regions, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsBitonicSort_create_cDBSFuuuA(TSBitonicSort self, const TSDevice device, TS_BitonicSortFlags flags, uint32_t size, uint32_t groups, uint32_t regions, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsBitonicSort_dispatch_CBuuuBSF(TSBitonicSort self, TSCompute compute, TSBuffer data, uint32_t keys_offset, uint32_t data_offset, uint32_t size, TS_BitonicSortFlags flags);
TS_CAPI bool_t TS_CCALL tsBitonicSort_dispatch_CBuupupupBSF(TSBitonicSort self, TSCompute compute, TSBuffer data, uint32_t count, const uint32_t *keys_offsets, const uint32_t *data_offsets, const uint32_t *sizes, TS_BitonicSortFlags flags);
TS_CAPI bool_t TS_CCALL tsBitonicSort_dispatchIndirect_CBBuBSF(TSBitonicSort self, TSCompute compute, TSBuffer data, TSBuffer dispatch, uint32_t offset, TS_BitonicSortFlags flags);
TS_CAPI bool_t TS_CCALL tsBitonicSort_dispatchIndirect_CBuBuBSF(TSBitonicSort self, TSCompute compute, TSBuffer data, uint32_t count, TSBuffer dispatch, uint32_t offset, TS_BitonicSortFlags flags);
TS_CAPI bool_t TS_CCALL tsBitonicSort_dispatchIndirect_CBBBuuBSF(TSBitonicSort self, TSCompute compute, TSBuffer data, TSBuffer count, TSBuffer dispatch, uint32_t count_offset, uint32_t dispatch_offset, TS_BitonicSortFlags flags);

/// Tellusim::SpatialGrid
TS_CAPI TSSpatialGrid TS_CCALL tsSpatialGrid_new(void);
TS_CAPI void TS_CCALL tsSpatialGrid_delete(TSSpatialGrid self);
TS_CAPI bool_t TS_CCALL tsSpatialGrid_equalPtr(const TSSpatialGrid self, const TSSpatialGrid ptr);
TS_CAPI TSSpatialGrid TS_CCALL tsSpatialGrid_copyPtr(const TSSpatialGrid self);
TS_CAPI TSSpatialGrid TS_CCALL tsSpatialGrid_clonePtr(const TSSpatialGrid self);
TS_CAPI void TS_CCALL tsSpatialGrid_clearPtr(TSSpatialGrid self);
TS_CAPI void TS_CCALL tsSpatialGrid_destroyPtr(TSSpatialGrid self);
TS_CAPI void TS_CCALL tsSpatialGrid_acquirePtr(TSSpatialGrid self);
TS_CAPI void TS_CCALL tsSpatialGrid_unacquirePtr(TSSpatialGrid self);
TS_CAPI bool_t TS_CCALL tsSpatialGrid_isValidPtr(const TSSpatialGrid self);
TS_CAPI bool_t TS_CCALL tsSpatialGrid_isOwnerPtr(const TSSpatialGrid self);
TS_CAPI bool_t TS_CCALL tsSpatialGrid_isConstPtr(const TSSpatialGrid self);
TS_CAPI uint32_t TS_CCALL tsSpatialGrid_getCountPtr(const TSSpatialGrid self);
TS_CAPI const void* TS_CCALL tsSpatialGrid_getInternalPtr(const TSSpatialGrid self);
TS_CAPI void TS_CCALL tsSpatialGrid_clear(TSSpatialGrid self);
TS_CAPI bool_t TS_CCALL tsSpatialGrid_isCreated(TSSpatialGrid self);
TS_CAPI uint32_t TS_CCALL tsSpatialGrid_getGroupSize(TSSpatialGrid self);
TS_CAPI TSRadixSort TS_CCALL tsSpatialGrid_getRadixSort(TSSpatialGrid self);
TS_CAPI bool_t TS_CCALL tsSpatialGrid_create(TSSpatialGrid self, const TSDevice device, TSRadixSort sort, uint32_t groups);
TS_CAPI bool_t TS_CCALL tsSpatialGrid_dispatch(TSSpatialGrid self, TSCompute compute, TSBuffer data, uint32_t offset, uint32_t size, uint32_t bits);
TS_CAPI bool_t TS_CCALL tsSpatialGrid_dispatchIndirect(TSSpatialGrid self, TSCompute compute, TSBuffer data, TSBuffer dispatch, uint32_t offset, uint32_t max_size);

/// Tellusim::SpatialTree
TS_CAPI TSSpatialTree TS_CCALL tsSpatialTree_new(void);
TS_CAPI void TS_CCALL tsSpatialTree_delete(TSSpatialTree self);
TS_CAPI bool_t TS_CCALL tsSpatialTree_equalPtr(const TSSpatialTree self, const TSSpatialTree ptr);
TS_CAPI TSSpatialTree TS_CCALL tsSpatialTree_copyPtr(const TSSpatialTree self);
TS_CAPI TSSpatialTree TS_CCALL tsSpatialTree_clonePtr(const TSSpatialTree self);
TS_CAPI void TS_CCALL tsSpatialTree_clearPtr(TSSpatialTree self);
TS_CAPI void TS_CCALL tsSpatialTree_destroyPtr(TSSpatialTree self);
TS_CAPI void TS_CCALL tsSpatialTree_acquirePtr(TSSpatialTree self);
TS_CAPI void TS_CCALL tsSpatialTree_unacquirePtr(TSSpatialTree self);
TS_CAPI bool_t TS_CCALL tsSpatialTree_isValidPtr(const TSSpatialTree self);
TS_CAPI bool_t TS_CCALL tsSpatialTree_isOwnerPtr(const TSSpatialTree self);
TS_CAPI bool_t TS_CCALL tsSpatialTree_isConstPtr(const TSSpatialTree self);
TS_CAPI uint32_t TS_CCALL tsSpatialTree_getCountPtr(const TSSpatialTree self);
TS_CAPI const void* TS_CCALL tsSpatialTree_getInternalPtr(const TSSpatialTree self);
TS_CAPI void TS_CCALL tsSpatialTree_clear(TSSpatialTree self);
TS_CAPI bool_t TS_CCALL tsSpatialTree_isCreated(TSSpatialTree self, TS_SpatialTreeFlags flags);
TS_CAPI uint32_t TS_CCALL tsSpatialTree_getGroupSize(TSSpatialTree self);
TS_CAPI uint32_t TS_CCALL tsSpatialTree_getBoundsNodes(TSSpatialTree self);
TS_CAPI uint32_t TS_CCALL tsSpatialTree_getMaxNodes(TSSpatialTree self);
TS_CAPI uint32_t TS_CCALL tsSpatialTree_getMaxRegions(TSSpatialTree self);
TS_CAPI TSRadixSort TS_CCALL tsSpatialTree_getRadixSort(TSSpatialTree self);
TS_CAPI TSBuffer TS_CCALL tsSpatialTree_getHashBuffer(TSSpatialTree self);
TS_CAPI TSBuffer TS_CCALL tsSpatialTree_getParentsBuffer(TSSpatialTree self);
TS_CAPI TSBuffer TS_CCALL tsSpatialTree_getCounterBuffer(TSSpatialTree self);
TS_CAPI bool_t TS_CCALL tsSpatialTree_create_cDSTMRSuuuA(TSSpatialTree self, const TSDevice device, TS_SpatialTreeMode mode, TSRadixSort sort, uint32_t size, uint32_t groups, uint32_t regions, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsSpatialTree_create_cDSTFRSuuuA(TSSpatialTree self, const TSDevice device, TS_SpatialTreeFlags flags, TSRadixSort sort, uint32_t size, uint32_t groups, uint32_t regions, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsSpatialTree_dispatch_CSTHBuuSTF(TSSpatialTree self, TSCompute compute, TS_SpatialTreeHash hash, TSBuffer nodes, uint32_t offset, uint32_t size, TS_SpatialTreeFlags flags);
TS_CAPI bool_t TS_CCALL tsSpatialTree_dispatch_CSTHBuupupSTF(TSSpatialTree self, TSCompute compute, TS_SpatialTreeHash hash, TSBuffer nodes, uint32_t count, const uint32_t *offsets, const uint32_t *sizes, TS_SpatialTreeFlags flags);
TS_CAPI bool_t TS_CCALL tsSpatialTree_dispatchIndirect_CSTHBBuuSTF(TSSpatialTree self, TSCompute compute, TS_SpatialTreeHash hash, TSBuffer nodes, TSBuffer dispatch, uint32_t offset, uint32_t max_size, TS_SpatialTreeFlags flags);
TS_CAPI bool_t TS_CCALL tsSpatialTree_dispatchIndirect_CSTHBuBuuSTF(TSSpatialTree self, TSCompute compute, TS_SpatialTreeHash hash, TSBuffer nodes, uint32_t count, TSBuffer dispatch, uint32_t offset, uint32_t max_size, TS_SpatialTreeFlags flags);

/// Tellusim::FourierTransform
TS_CAPI TSFourierTransform TS_CCALL tsFourierTransform_new(void);
TS_CAPI void TS_CCALL tsFourierTransform_delete(TSFourierTransform self);
TS_CAPI bool_t TS_CCALL tsFourierTransform_equalPtr(const TSFourierTransform self, const TSFourierTransform ptr);
TS_CAPI TSFourierTransform TS_CCALL tsFourierTransform_copyPtr(const TSFourierTransform self);
TS_CAPI TSFourierTransform TS_CCALL tsFourierTransform_clonePtr(const TSFourierTransform self);
TS_CAPI void TS_CCALL tsFourierTransform_clearPtr(TSFourierTransform self);
TS_CAPI void TS_CCALL tsFourierTransform_destroyPtr(TSFourierTransform self);
TS_CAPI void TS_CCALL tsFourierTransform_acquirePtr(TSFourierTransform self);
TS_CAPI void TS_CCALL tsFourierTransform_unacquirePtr(TSFourierTransform self);
TS_CAPI bool_t TS_CCALL tsFourierTransform_isValidPtr(const TSFourierTransform self);
TS_CAPI bool_t TS_CCALL tsFourierTransform_isOwnerPtr(const TSFourierTransform self);
TS_CAPI bool_t TS_CCALL tsFourierTransform_isConstPtr(const TSFourierTransform self);
TS_CAPI uint32_t TS_CCALL tsFourierTransform_getCountPtr(const TSFourierTransform self);
TS_CAPI const void* TS_CCALL tsFourierTransform_getInternalPtr(const TSFourierTransform self);
TS_CAPI void TS_CCALL tsFourierTransform_clear(TSFourierTransform self);
TS_CAPI bool_t TS_CCALL tsFourierTransform_isCreated_cFTM(TSFourierTransform self, TS_FourierTransformMode mode);
TS_CAPI bool_t TS_CCALL tsFourierTransform_isCreated_cFTF(TSFourierTransform self, TS_FourierTransformFlags flags);
TS_CAPI uint32_t TS_CCALL tsFourierTransform_getMaxWidth(TSFourierTransform self);
TS_CAPI uint32_t TS_CCALL tsFourierTransform_getMaxHeight(TSFourierTransform self);
TS_CAPI uint32_t TS_CCALL tsFourierTransform_getAlignedSize(TSFourierTransform self, uint32_t size);
TS_CAPI bool_t TS_CCALL tsFourierTransform_create_cDFTMuuA(TSFourierTransform self, const TSDevice device, TS_FourierTransformMode mode, uint32_t width, uint32_t height, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsFourierTransform_create_cDFTFuuA(TSFourierTransform self, const TSDevice device, TS_FourierTransformFlags flags, uint32_t width, uint32_t height, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsFourierTransform_dispatch_cCFTMFTOTTcScS(TSFourierTransform self, TSCompute compute, TS_FourierTransformMode mode, TS_FourierTransformOperation op, TSTexture dest, TSTexture src, const TSSlice *dest_slice, const TSSlice *src_slice);
TS_CAPI bool_t TS_CCALL tsFourierTransform_dispatch_cCFTMFTOTTcS(TSFourierTransform self, TSCompute compute, TS_FourierTransformMode mode, TS_FourierTransformOperation op, TSTexture dest, TSTexture src, const TSSlice *src_slice);
TS_CAPI bool_t TS_CCALL tsFourierTransform_dispatch_cCFTMFTOTT(TSFourierTransform self, TSCompute compute, TS_FourierTransformMode mode, TS_FourierTransformOperation op, TSTexture dest, TSTexture src);

/// Tellusim::TensorGraph
TS_CAPI TSTensorGraph TS_CCALL tsTensorGraph_new(void);
TS_CAPI void TS_CCALL tsTensorGraph_delete(TSTensorGraph self);
TS_CAPI bool_t TS_CCALL tsTensorGraph_equalPtr(const TSTensorGraph self, const TSTensorGraph ptr);
TS_CAPI TSTensorGraph TS_CCALL tsTensorGraph_copyPtr(const TSTensorGraph self);
TS_CAPI TSTensorGraph TS_CCALL tsTensorGraph_clonePtr(const TSTensorGraph self);
TS_CAPI void TS_CCALL tsTensorGraph_clearPtr(TSTensorGraph self);
TS_CAPI void TS_CCALL tsTensorGraph_destroyPtr(TSTensorGraph self);
TS_CAPI void TS_CCALL tsTensorGraph_acquirePtr(TSTensorGraph self);
TS_CAPI void TS_CCALL tsTensorGraph_unacquirePtr(TSTensorGraph self);
TS_CAPI bool_t TS_CCALL tsTensorGraph_isValidPtr(const TSTensorGraph self);
TS_CAPI bool_t TS_CCALL tsTensorGraph_isOwnerPtr(const TSTensorGraph self);
TS_CAPI bool_t TS_CCALL tsTensorGraph_isConstPtr(const TSTensorGraph self);
TS_CAPI uint32_t TS_CCALL tsTensorGraph_getCountPtr(const TSTensorGraph self);
TS_CAPI const void* TS_CCALL tsTensorGraph_getInternalPtr(const TSTensorGraph self);
TS_CAPI void TS_CCALL tsTensorGraph_clear(TSTensorGraph self);
TS_CAPI bool_t TS_CCALL tsTensorGraph_isCreated(TSTensorGraph self);
TS_CAPI bool_t TS_CCALL tsTensorGraph_create(TSTensorGraph self, const TSDevice device, TS_TensorGraphFlags flags, TS_TensorGraphMasks masks, TSAsync *async);
TS_CAPI bool_t TS_CCALL tsTensorGraph_dispatch_cCTGOcTTGF(TSTensorGraph self, TSCompute compute, TS_TensorGraphOperation op, const TSTensor *dest, TS_TensorGraphFlags flags);
TS_CAPI bool_t TS_CCALL tsTensorGraph_dispatch_cCTGOTcTTGF(TSTensorGraph self, TSCompute compute, TS_TensorGraphOperation op, TSTensor *dest, const TSTensor *src_0, TS_TensorGraphFlags flags);
TS_CAPI bool_t TS_CCALL tsTensorGraph_dispatch_cCTGOTcTcTTGF(TSTensorGraph self, TSCompute compute, TS_TensorGraphOperation op, TSTensor *dest, const TSTensor *src_0, const TSTensor *src_1, TS_TensorGraphFlags flags);
TS_CAPI bool_t TS_CCALL tsTensorGraph_dispatch_cCTGOTcTcTcTTGF(TSTensorGraph self, TSCompute compute, TS_TensorGraphOperation op, TSTensor *dest, const TSTensor *src_0, const TSTensor *src_1, const TSTensor *src_2, TS_TensorGraphFlags flags);
TS_CAPI bool_t TS_CCALL tsTensorGraph_dispatch_cCcTTcRcS(TSTensorGraph self, TSCompute compute, const TSTensor *dest, TSTexture src, const TSRegion *region, const TSSlice *slice);
TS_CAPI bool_t TS_CCALL tsTensorGraph_dispatch_cCcTTcS(TSTensorGraph self, TSCompute compute, const TSTensor *dest, TSTexture src, const TSSlice *slice);
TS_CAPI bool_t TS_CCALL tsTensorGraph_dispatch_cCTcTcRcS(TSTensorGraph self, TSCompute compute, TSTexture dest, const TSTensor *src, const TSRegion *region, const TSSlice *slice);
TS_CAPI bool_t TS_CCALL tsTensorGraph_dispatch_cCTcTcS(TSTensorGraph self, TSCompute compute, TSTexture dest, const TSTensor *src, const TSSlice *slice);

/// Tellusim::Controller
typedef void (*TSControllerButtonPressedCallback)(TSController controller, TS_ControllerButton button, void *data_);
typedef void (*TSControllerButtonReleasedCallback)(TSController controller, TS_ControllerButton button, void *data_);
typedef void (*TSControllerConnectedCallback)(TSController controller, void *data_);
typedef void (*TSControllerDisconnectedCallback)(TSController controller, void *data_);
TS_CAPI TSController TS_CCALL tsController_new(void);
TS_CAPI TSController TS_CCALL tsController_new_u(uint32_t index);
TS_CAPI TSController TS_CCALL tsController_new_CTu(TS_ControllerType type, uint32_t index);
TS_CAPI void TS_CCALL tsController_delete(TSController self);
TS_CAPI bool_t TS_CCALL tsController_equalPtr(const TSController self, const TSController ptr);
TS_CAPI TSController TS_CCALL tsController_copyPtr(const TSController self);
TS_CAPI TSController TS_CCALL tsController_clonePtr(const TSController self);
TS_CAPI void TS_CCALL tsController_clearPtr(TSController self);
TS_CAPI void TS_CCALL tsController_destroyPtr(TSController self);
TS_CAPI void TS_CCALL tsController_acquirePtr(TSController self);
TS_CAPI void TS_CCALL tsController_unacquirePtr(TSController self);
TS_CAPI bool_t TS_CCALL tsController_isValidPtr(const TSController self);
TS_CAPI bool_t TS_CCALL tsController_isOwnerPtr(const TSController self);
TS_CAPI bool_t TS_CCALL tsController_isConstPtr(const TSController self);
TS_CAPI uint32_t TS_CCALL tsController_getCountPtr(const TSController self);
TS_CAPI const void* TS_CCALL tsController_getInternalPtr(const TSController self);
TS_CAPI uint32_t TS_CCALL tsController_getNumControllers(void);
TS_CAPI uint32_t TS_CCALL tsController_findController(const char *name);
TS_CAPI TSController TS_CCALL tsController_getController(uint32_t index);
TS_CAPI void TS_CCALL tsController_update(void);
TS_CAPI void TS_CCALL tsController_setType(TSController self, TS_ControllerType type);
TS_CAPI TS_ControllerType TS_CCALL tsController_getType(TSController self);
TS_CAPI const char* TS_CCALL tsController_getTypeName_CT(TS_ControllerType type);
TS_CAPI const char* TS_CCALL tsController_getTypeName_c(TSController self);
TS_CAPI bool_t TS_CCALL tsController_isUnknown(TSController self);
TS_CAPI bool_t TS_CCALL tsController_isJoystick(TSController self);
TS_CAPI bool_t TS_CCALL tsController_isGamePad(TSController self);
TS_CAPI bool_t TS_CCALL tsController_isWheel(TSController self);
TS_CAPI void TS_CCALL tsController_setIndex(TSController self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsController_getIndex(TSController self);
TS_CAPI void TS_CCALL tsController_setName(TSController self, const char *name);
TS_CAPI TSString TS_CCALL tsController_getName(TSController self);
TS_CAPI void TS_CCALL tsController_setModel(TSController self, const char *model);
TS_CAPI TSString TS_CCALL tsController_getModel(TSController self);
TS_CAPI bool_t TS_CCALL tsController_isConnected(TSController self);
TS_CAPI bool_t TS_CCALL tsController_wasConnected(TSController self);
TS_CAPI bool_t TS_CCALL tsController_connect(TSController self, const char *name);
TS_CAPI void TS_CCALL tsController_release(TSController self);
TS_CAPI void TS_CCALL tsController_setStickName(TSController self, TS_ControllerStick stick, const char *name);
TS_CAPI TSString TS_CCALL tsController_getStickName(TSController self, TS_ControllerStick stick);
TS_CAPI TS_ControllerStick TS_CCALL tsController_findStick(TSController self, const char *name);
TS_CAPI void TS_CCALL tsController_setStick(TSController self, TS_ControllerStick stick, float32_t x, float32_t y);
TS_CAPI float32_t TS_CCALL tsController_getStickX(TSController self, TS_ControllerStick stick);
TS_CAPI float32_t TS_CCALL tsController_getStickY(TSController self, TS_ControllerStick stick);
TS_CAPI void TS_CCALL tsController_setAxisName(TSController self, TS_ControllerAxis axis, const char *name);
TS_CAPI TSString TS_CCALL tsController_getAxisName(TSController self, TS_ControllerAxis axis);
TS_CAPI TS_ControllerAxis TS_CCALL tsController_findAxis(TSController self, const char *name);
TS_CAPI void TS_CCALL tsController_setAxis(TSController self, TS_ControllerAxis axis, float32_t value);
TS_CAPI float32_t TS_CCALL tsController_getAxis(TSController self, TS_ControllerAxis axis);
TS_CAPI void TS_CCALL tsController_setButtonName(TSController self, TS_ControllerButton button, const char *name);
TS_CAPI TSString TS_CCALL tsController_getButtonName(TSController self, TS_ControllerButton button);
TS_CAPI TS_ControllerButton TS_CCALL tsController_findButton(TSController self, const char *name);
TS_CAPI void TS_CCALL tsController_setButton(TSController self, TS_ControllerButton button, bool_t value);
TS_CAPI bool_t TS_CCALL tsController_getButton(TSController self, TS_ControllerButton button, bool_t clear);
TS_CAPI bool_t TS_CCALL tsController_wasButtonPressed(TSController self, TS_ControllerButton button);
TS_CAPI bool_t TS_CCALL tsController_wasButtonReleased(TSController self, TS_ControllerButton button);
TS_CAPI void TS_CCALL tsController_setButtonValue(TSController self, TS_ControllerButton button, float32_t value);
TS_CAPI float32_t TS_CCALL tsController_getButtonValue(TSController self, TS_ControllerButton button);
TS_CAPI void TS_CCALL tsController_setMotorName(TSController self, TS_ControllerMotor motor, const char *name);
TS_CAPI TSString TS_CCALL tsController_getMotorName(TSController self, TS_ControllerMotor motor);
TS_CAPI TS_ControllerMotor TS_CCALL tsController_findMotor(TSController self, const char *name);
TS_CAPI void TS_CCALL tsController_setMotor(TSController self, TS_ControllerMotor motor, float32_t value);
TS_CAPI float32_t TS_CCALL tsController_getMotor(TSController self, TS_ControllerMotor motor);
TS_CAPI void TS_CCALL tsController_setButtonPressedCallback(TSController self, const TSControllerButtonPressedCallback func, void *data_);
TS_CAPI void TS_CCALL tsController_setButtonReleasedCallback(TSController self, const TSControllerButtonReleasedCallback func, void *data_);
TS_CAPI void TS_CCALL tsController_setConnectedCallback(TSController self, const TSControllerConnectedCallback func, void *data_);
TS_CAPI void TS_CCALL tsController_setDisconnectedCallback(TSController self, const TSControllerDisconnectedCallback func, void *data_);
TS_CAPI extern const char* tsControllerNameXbox;
TS_CAPI extern const char* tsControllerNamePlayStation;
TS_CAPI extern const char* tsControllerNameNintendo;

/// Tellusim::Desktop
TS_CAPI TSDesktop TS_CCALL tsDesktop_new(void);
TS_CAPI void TS_CCALL tsDesktop_delete(TSDesktop self);
TS_CAPI bool_t TS_CCALL tsDesktop_equalPtr(const TSDesktop self, const TSDesktop ptr);
TS_CAPI TSDesktop TS_CCALL tsDesktop_copyPtr(const TSDesktop self);
TS_CAPI TSDesktop TS_CCALL tsDesktop_clonePtr(const TSDesktop self);
TS_CAPI void TS_CCALL tsDesktop_clearPtr(TSDesktop self);
TS_CAPI void TS_CCALL tsDesktop_destroyPtr(TSDesktop self);
TS_CAPI void TS_CCALL tsDesktop_acquirePtr(TSDesktop self);
TS_CAPI void TS_CCALL tsDesktop_unacquirePtr(TSDesktop self);
TS_CAPI bool_t TS_CCALL tsDesktop_isValidPtr(const TSDesktop self);
TS_CAPI bool_t TS_CCALL tsDesktop_isOwnerPtr(const TSDesktop self);
TS_CAPI bool_t TS_CCALL tsDesktop_isConstPtr(const TSDesktop self);
TS_CAPI uint32_t TS_CCALL tsDesktop_getCountPtr(const TSDesktop self);
TS_CAPI const void* TS_CCALL tsDesktop_getInternalPtr(const TSDesktop self);
TS_CAPI bool_t TS_CCALL tsDesktop_update(TSDesktop self);
TS_CAPI uint32_t TS_CCALL tsDesktop_getWidth_c(TSDesktop self);
TS_CAPI uint32_t TS_CCALL tsDesktop_getHeight_c(TSDesktop self);
TS_CAPI int32_t TS_CCALL tsDesktop_getPositionX_c(TSDesktop self);
TS_CAPI int32_t TS_CCALL tsDesktop_getPositionY_c(TSDesktop self);
TS_CAPI float32_t TS_CCALL tsDesktop_getScale(TSDesktop self);
TS_CAPI uint32_t TS_CCALL tsDesktop_getNumScreens(TSDesktop self);
TS_CAPI TSString TS_CCALL tsDesktop_getScreenName(TSDesktop self, uint32_t index);
TS_CAPI TSString TS_CCALL tsDesktop_getScreenDevice(TSDesktop self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsDesktop_getScreenWidth(TSDesktop self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsDesktop_getScreenHeight(TSDesktop self, uint32_t index);
TS_CAPI int32_t TS_CCALL tsDesktop_getScreenPositionX(TSDesktop self, uint32_t index);
TS_CAPI int32_t TS_CCALL tsDesktop_getScreenPositionY(TSDesktop self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsDesktop_getScreenFrequency(TSDesktop self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsDesktop_getNumModes(TSDesktop self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsDesktop_getModeWidth(TSDesktop self, uint32_t index, uint32_t mode);
TS_CAPI uint32_t TS_CCALL tsDesktop_getModeHeight(TSDesktop self, uint32_t index, uint32_t mode);
TS_CAPI uint32_t TS_CCALL tsDesktop_getModeIndex(TSDesktop self, uint32_t index, uint32_t width, uint32_t height);
TS_CAPI bool_t TS_CCALL tsDesktop_setMode(TSDesktop self, uint32_t index, uint32_t width, uint32_t height);
TS_CAPI bool_t TS_CCALL tsDesktop_restoreMode(TSDesktop self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsDesktop_getWidth_cu(TSDesktop self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsDesktop_getHeight_cu(TSDesktop self, uint32_t index);
TS_CAPI int32_t TS_CCALL tsDesktop_getPositionX_cu(TSDesktop self, uint32_t index);
TS_CAPI int32_t TS_CCALL tsDesktop_getPositionY_cu(TSDesktop self, uint32_t index);
TS_CAPI uint32_t TS_CCALL tsDesktop_getScreenIndex(TSDesktop self, int32_t x, int32_t y);
TS_CAPI bool_t TS_CCALL tsDesktop_setMouse(TSDesktop self, int32_t x, int32_t y);
TS_CAPI bool_t TS_CCALL tsDesktop_getMouse(TSDesktop self, int32_t *x, int32_t *y);

/// Tellusim
TS_CAPI const char* TS_CCALL ts_getPlatformName(TS_Platform platform);
TS_CAPI TS_Platform TS_CCALL ts_findPlatformName(const char *name);
TS_CAPI bool_t TS_CCALL ts_isPlatformAvailable(TS_Platform platform);
TS_CAPI const char* TS_CCALL ts_getFormatName(TS_Format format);
TS_CAPI TS_Format TS_CCALL ts_findFormatName(const char *name);
TS_CAPI const char* TS_CCALL ts_getGLSLFormatName(TS_Format format);
TS_CAPI TS_Format TS_CCALL ts_findGLSLFormatName(const char *name);
TS_CAPI bool_t TS_CCALL ts_isColorFormat(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isDepthFormat(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isPixelFormat(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isPlainFormat(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isMixedFormat(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isBlockFormat(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isStencilFormat(TS_Format format);
TS_CAPI TS_Format TS_CCALL ts_toPixelFormat(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isNormFormat(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isSRGBFormat(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isSignedFormat(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isUnsignedFormat(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isIntegerFormat(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isFloatFormat(TS_Format format);
TS_CAPI TS_Format TS_CCALL ts_toNormFormat(TS_Format format);
TS_CAPI TS_Format TS_CCALL ts_toSRGBFormat(TS_Format format);
TS_CAPI TS_Format TS_CCALL ts_toSignedFormat(TS_Format format);
TS_CAPI TS_Format TS_CCALL ts_toUnsignedFormat(TS_Format format);
TS_CAPI TS_Format TS_CCALL ts_toFloatFormat(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isi8Format(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isu8Format(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_is8BitFormat(TS_Format format);
TS_CAPI TS_Format TS_CCALL ts_to8BitFormat(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isi16Format(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isu16Format(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isf16Format(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_is16BitFormat(TS_Format format);
TS_CAPI TS_Format TS_CCALL ts_to16BitFormat(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isi32Format(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isu32Format(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isf32Format(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_is32BitFormat(TS_Format format);
TS_CAPI TS_Format TS_CCALL ts_to32BitFormat(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isi64Format(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isu64Format(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isf64Format(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_is64BitFormat(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isBC15Format(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isBC67Format(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isETC2Format(TS_Format format);
TS_CAPI bool_t TS_CCALL ts_isASTCFormat(TS_Format format);
TS_CAPI uint32_t TS_CCALL ts_getFormatComponents(TS_Format format);
TS_CAPI TS_Format TS_CCALL ts_toFormatComponents(TS_Format format, uint32_t components);
TS_CAPI uint32_t TS_CCALL ts_getFormatPixelSize(TS_Format format);
TS_CAPI uint32_t TS_CCALL ts_getFormatBlockSize(TS_Format format);
TS_CAPI uint32_t TS_CCALL ts_getFormatBlockWidth(TS_Format format);
TS_CAPI uint32_t TS_CCALL ts_getFormatBlockHeight(TS_Format format);
TS_CAPI uint32_t TS_CCALL ts_getPixelFormatValue(TS_Format format, float32_t value[4], const void *src, uint32_t stride);
TS_CAPI uint32_t TS_CCALL ts_setPixelFormatValue(TS_Format format, void *dest, const float32_t value[4], uint32_t stride);

/// Tellusim::Allocator
TS_CAPI void* TS_CCALL tsAllocator_allocate_z(size_t size);
TS_CAPI void* TS_CCALL tsAllocator_reallocate(void *ptr, size_t old_size, size_t new_size);
TS_CAPI void TS_CCALL tsAllocator_free(const void *ptr, size_t size);
TS_CAPI size_t TS_CCALL tsAllocator_getMemory(void);
TS_CAPI size_t TS_CCALL tsAllocator_getAllocations(void);

/// Tellusim::Log
TS_CAPI void TS_CCALL tsLog_setLevel(TS_LogLevel level);
TS_CAPI TS_LogLevel TS_CCALL tsLog_getLevel(void);
TS_CAPI void TS_CCALL tsLog_setCallback(TSLogCallback callback, void *data);
TS_CAPI void* TS_CCALL tsLog_getCallbackData(void);
TS_CAPI void TS_CCALL tsLog_unlockCallback(void);
TS_CAPI void TS_CCALL tsLog_lockCallback(void);
TS_CAPI void TS_CCALL tsLog_print_s(const char *str);
TS_CAPI void TS_CCALL tsLog_vprintf_sva(const char *str, va_list args);
TS_CAPI void TS_CCALL tsLog_print_LLs(TS_LogLevel level, const char *str);
TS_CAPI void TS_CCALL tsLog_printe(TS_LogLevel level, const char *str);
TS_CAPI void TS_CCALL tsLog_vprintf_LLsva(TS_LogLevel level, const char *str, va_list args);
TS_CAPI void TS_CCALL tsLog_vprintef(TS_LogLevel level, const char *str, va_list args);

/// Tellusim::Time
TS_CAPI uint64_t TS_CCALL tsTime_current(void);
TS_CAPI float64_t TS_CCALL tsTime_seconds(void);
TS_CAPI void TS_CCALL tsTime_sleep(uint32_t usec);

/// Tellusim::System
TS_CAPI uint32_t TS_CCALL tsSystem_getThreadID(void);
TS_CAPI bool_t TS_CCALL tsSystem_setEnvironment_ss(const char *name, const char *value);
TS_CAPI bool_t TS_CCALL tsSystem_setEnvironment_cSs(const TSString name, const char *value);
TS_CAPI TSString TS_CCALL tsSystem_getEnvironment_s(const char *name);
TS_CAPI TSString TS_CCALL tsSystem_getEnvironment_cS(const TSString name);
TS_CAPI void* TS_CCALL tsSystem_loadLibrary_s(const char *name);
TS_CAPI void* TS_CCALL tsSystem_loadLibrary_cS(const TSString name);
TS_CAPI void* TS_CCALL tsSystem_getFunction_prs(void *handle, const char *name);
TS_CAPI void* TS_CCALL tsSystem_getFunction_prcS(void *handle, const TSString name);
TS_CAPI void TS_CCALL tsSystem_closeLibrary(void *handle);
TS_CAPI bool_t TS_CCALL tsSystem_exec_sbb(const char *command, bool_t wait, bool_t console);
TS_CAPI bool_t TS_CCALL tsSystem_exec_cSbb(const TSString command, bool_t wait, bool_t console);
TS_CAPI bool_t TS_CCALL tsSystem_open_s(const char *command);
TS_CAPI bool_t TS_CCALL tsSystem_open_cS(const TSString command);

/// Tellusim::MeshGraph
typedef bool_t (*TSMeshGraphProgressCallback)(uint32_t progress, void *data_);
TS_CAPI bool_t TS_CCALL tsMeshGraph_create_MMuucMGPCA(TSMesh dest, TSMesh src, uint32_t max_attributes, uint32_t max_primitives, const TSMeshGraphProgressCallback func, TSAsync *async, void *data_);

/// Tellusim::MeshReduce
typedef bool_t (*TSMeshReduceProgressCallback)(uint32_t progress, void *data_);
TS_CAPI bool_t TS_CCALL tsMeshReduce_collapse_McMffcMRPC(TSMesh dest, const TSMesh src, float32_t ratio, float32_t threshold, const TSMeshReduceProgressCallback func, void *data_);
TS_CAPI bool_t TS_CCALL tsMeshReduce_collapse_MGcMGffcMRPCu(TSMeshGeometry dest, const TSMeshGeometry src, float32_t ratio, float32_t threshold, const TSMeshReduceProgressCallback func, uint32_t position, void *data_);

/// Tellusim::MeshRefine
TS_CAPI bool_t TS_CCALL tsMeshRefine_subdiv_McMuf(TSMesh dest, const TSMesh src, uint32_t steps, float32_t weight);
TS_CAPI bool_t TS_CCALL tsMeshRefine_subdiv_MGcMGufu(TSMeshGeometry dest, const TSMeshGeometry src, uint32_t steps, float32_t weight, uint32_t position);

/// Tellusim::MeshSolid
typedef bool_t (*TSMeshSolidProgressCallback)(uint32_t progress, void *data_);
TS_CAPI bool_t TS_CCALL tsMeshSolid_create_McMffcMSPC(TSMesh dest, const TSMesh src, float32_t ratio, float32_t threshold, const TSMeshSolidProgressCallback func, void *data_);
TS_CAPI bool_t TS_CCALL tsMeshSolid_create_MGcMGffcMSPCu(TSMeshGeometry dest, const TSMeshGeometry src, float32_t ratio, float32_t threshold, const TSMeshSolidProgressCallback func, uint32_t position, void *data_);

#ifdef __cplusplus
}
#endif

#endif /* __TELLUSIM_C_API_H__ */

// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_OBJC_BASE_H__
#define __TELLUSIM_OBJC_BASE_H__

#include <Foundation/Foundation.h>

/*
 */
#if _WIN32
	#define TS_CAPI		__declspec(dllexport)
	#define TS_CCALL	__stdcall
#else
	#define TS_CAPI		__attribute__ ((visibility("default")))
	#define TS_CCALL
#endif

/*
 */
#if _WIN32
	#define TS_CALIGNAS16(TYPE)	__declspec(align(16)) TYPE
#else
	#define TS_CALIGNAS16(TYPE)	TYPE __attribute__ ((aligned(16)))
#endif

/*
 */
#ifndef TS_CFLOAT32
	#define TS_CFLOAT32 float
	typedef TS_CFLOAT32 float32_t;
#endif
#ifndef TS_CFLOAT64
	#define TS_CFLOAT64 double
	typedef TS_CFLOAT64 float64_t;
#endif

/*
 */
#include "TellusimObjCMath.h"

/*
 */
#ifdef __cplusplus
extern "C" {
#endif

/*
 */
NS_SWIFT_NAME(TSSource.OpenCallback)
@protocol TSSourceOpenCallback <NSObject>
	-(BOOL)run: (const char*)name data: (const void*)data;
@end

NS_SWIFT_NAME(TSSource.IsCallback)
@protocol TSSourceIsCallback <NSObject>
	-(BOOL)run: (const char*)name data: (const void*)data;
@end

/*****************************************************************************\
 *
 * Log
 *
\*****************************************************************************/

/*
 */
NS_SWIFT_NAME(TSLog.Callback)
@protocol TSLogCallback<NSObject>
	-(BOOL)run: (uint32_t)level time: (uint64_t)time str: (const char*)str data: (const void*)data;
@end

/*****************************************************************************\
 *
 * Color
 *
\*****************************************************************************/

/*
 */
typedef struct TSColor {
	union {
		struct {
			float32_t r, g, b, a;
		};
		float32_t c[4];
	};
} TSColor;

/*
 */
typedef TSColor Color;

/*
 */
TS_CAPI TSColor* TS_CCALL tsColor_gammaToLinear(TSColor *ret, const TSColor *c);
TS_CAPI TSColor* TS_CCALL tsColor_linearToGamma(TSColor *ret, const TSColor *c);

TS_CAPI TSColor* TS_CCALL tsColor_sRGBtoLinear(TSColor *ret, const TSColor *c);
TS_CAPI TSColor* TS_CCALL tsColor_linearToSRGB(TSColor *ret, const TSColor *c);

TS_CAPI void TS_CCALL tsColor_setRGBAu8(TSColor *c, uint32_t color);
TS_CAPI uint32_t TS_CCALL tsColor_getRGBAu8(const TSColor *c);

TS_CAPI void TS_CCALL tsColor_setBGRAu8(TSColor *c, uint32_t color);
TS_CAPI uint32_t TS_CCALL tsColor_getBGRAu8(const TSColor *c);

TS_CAPI void TS_CCALL tsColor_setABGRu8(TSColor *c, uint32_t color);
TS_CAPI uint32_t TS_CCALL tsColor_getABGRu8(const TSColor *c);

TS_CAPI TSColor* TS_CCALL tsColor_html(TSColor *ret, const char *src);
TS_CAPI TSColor* TS_CCALL tsColor_hsv(TSColor *ret, float32_t h, float32_t s, float32_t v);
TS_CAPI TSColor* TS_CCALL tsColor_temperature(TSColor *ret, float32_t t);

/*****************************************************************************\
 *
 * ImageColor
 *
\*****************************************************************************/

/*
 */
typedef struct TSImageColor {
	union {
		struct { int32_t r, g, b, a; } i;
		struct { uint32_t r, g, b, a; } u;
		struct { uint16_t r, g, b, a; } h;
		struct { float32_t r, g, b, a; } f;
		int32_t iv[4];
		uint32_t uv[4];
		uint16_t hv[4];
		float32_t fv[4];
	};
} TSImageColor;

/*
 */
typedef TSImageColor ImageColor;

/*
 */
TS_CAPI void TS_CCALL tsImageColor_set(TSImageColor *c, const TSColor *src, uint32_t format);
TS_CAPI void TS_CCALL tsImageColor_get(const TSImageColor *c, TSColor *dest, uint32_t format);

/*****************************************************************************\
 *
 * Bounds
 *
\*****************************************************************************/

/*
 */
typedef struct TSBoundRectf {
	TSVector2f min;
	TSVector2f max;
} TSBoundRectf;

typedef struct TSBoundRectd {
	TSVector2d min;
	TSVector2d max;
} TSBoundRectd;

/*
 */
typedef TSBoundRectf BoundRectf;
typedef TSBoundRectd BoundRectd;

/*
 */
typedef struct TSBoundCirclef {
	TSVector2f center;
	float32_t radius;
} TSBoundCirclef;

typedef struct TSBoundCircled {
	TSVector2d center;
	float64_t radius;
} TSBoundCircled;

/*
 */
typedef TSBoundCirclef BoundCirclef;
typedef TSBoundCircled BoundCircled;

/*
 */
typedef struct TSBoundBoxf {
	TSVector3f min;
	TSVector3f max;
} TSBoundBoxf;

typedef struct TSBoundBoxd {
	TSVector3d min;
	TSVector3d max;
} TSBoundBoxd;

/*
 */
typedef TSBoundBoxf BoundBoxf;
typedef TSBoundBoxd BoundBoxd;

/*
 */
typedef struct TSBoundSpheref {
	TSVector3f center;
	float32_t radius;
} TSBoundSpheref;

typedef struct TSBoundSphered {
	TSVector3d center;
	float64_t radius;
} TSBoundSphered;

/*
 */
typedef TSBoundSpheref BoundSpheref;
typedef TSBoundSphered BoundSphered;

/*
 */
typedef struct TSBoundFrustumf {
	TSMatrix4x4f projection;
	TSMatrix4x4f modelview;
	TSVector3f camera;
	TSVector4f plane_l;
	TSVector4f plane_r;
	TSVector4f plane_b;
	TSVector4f plane_t;
	TSVector4f plane_n;
	TSVector4f plane_f;
	uint8_t signs[6][4];
} TSBoundFrustumf;

typedef struct TSBoundFrustumd {
	TSMatrix4x4d projection;
	TSMatrix4x4d modelview;
	TSVector3d camera;
	TSVector4d plane_l;
	TSVector4d plane_r;
	TSVector4d plane_b;
	TSVector4d plane_t;
	TSVector4d plane_n;
	TSVector4d plane_f;
	uint8_t signs[6][4];
} TSBoundFrustumd;

/*
 */
typedef TSBoundFrustumf BoundFrustumf;
typedef TSBoundFrustumd BoundFrustumd;

/*
 */
TS_CAPI void TS_CCALL tsBoundRectf_set_brd(TSBoundRectf *br, const TSBoundRectd *r);
TS_CAPI void TS_CCALL tsBoundRectd_set_brf(TSBoundRectd *br, const TSBoundRectf *r);

TS_CAPI void TS_CCALL tsBoundRectf_set_bc(TSBoundRectf *br, const TSBoundCirclef *c);
TS_CAPI void TS_CCALL tsBoundRectd_set_bc(TSBoundRectd *br, const TSBoundCircled *c);

TS_CAPI void TS_CCALL tsBoundRectf_expand1(TSBoundRectf *br, const TSVector2f *p);
TS_CAPI void TS_CCALL tsBoundRectd_expand1(TSBoundRectd *br, const TSVector2d *p);

TS_CAPI void TS_CCALL tsBoundRectf_expand(TSBoundRectf *br, const TSBoundRectf *r);
TS_CAPI void TS_CCALL tsBoundRectd_expand(TSBoundRectd *br, const TSBoundRectd *r);

TS_CAPI BOOL TS_CCALL tsBoundRectf_inside1(const TSBoundRectf *br, const TSVector2f *p);
TS_CAPI BOOL TS_CCALL tsBoundRectd_inside1(const TSBoundRectd *br, const TSVector2d *p);

TS_CAPI BOOL TS_CCALL tsBoundRectf_inside(const TSBoundRectf *br, const TSBoundRectf *r);
TS_CAPI BOOL TS_CCALL tsBoundRectd_inside(const TSBoundRectd *br, const TSBoundRectd *r);

TS_CAPI float32_t TS_CCALL tsBoundRectf_distance(const TSBoundRectf *br, const TSVector2f *p);
TS_CAPI float64_t TS_CCALL tsBoundRectd_distance(const TSBoundRectd *br, const TSVector2d *p);

TS_CAPI void TS_CCALL tsMatrix4x3f_mul_br(TSBoundRectf *br, const TSMatrix4x3f *m, const TSBoundRectf *r);
TS_CAPI void TS_CCALL tsMatrix4x3d_mul_br(TSBoundRectd *br, const TSMatrix4x3d *m, const TSBoundRectd *r);

TS_CAPI void TS_CCALL tsMatrix4x4f_mul_br(TSBoundRectf *br, const TSMatrix4x4f *m, const TSBoundRectf *r);
TS_CAPI void TS_CCALL tsMatrix4x4d_mul_br(TSBoundRectd *br, const TSMatrix4x4d *m, const TSBoundRectd *r);

/*
 */
TS_CAPI void TS_CCALL tsBoundCirclef_set_bcd(TSBoundCirclef *bc, const TSBoundCircled *c);
TS_CAPI void TS_CCALL tsBoundCircled_set_bcf(TSBoundCircled *bc, const TSBoundCirclef *c);

TS_CAPI void TS_CCALL tsBoundCirclef_set_br(TSBoundCirclef *bc, const TSBoundRectf *r);
TS_CAPI void TS_CCALL tsBoundCircled_set_br(TSBoundCircled *bc, const TSBoundRectd *r);

TS_CAPI void TS_CCALL tsBoundCirclef_expand1(TSBoundCirclef *bc, const TSVector2f *p);
TS_CAPI void TS_CCALL tsBoundCircled_expand1(TSBoundCircled *bc, const TSVector2d *p);

TS_CAPI void TS_CCALL tsBoundCirclef_expand(TSBoundCirclef *bc, const TSBoundCirclef *c);
TS_CAPI void TS_CCALL tsBoundCircled_expand(TSBoundCircled *bc, const TSBoundCircled *c);

TS_CAPI void TS_CCALL tsBoundCirclef_expandRadius1(TSBoundCirclef *bc, const TSVector2f *p);
TS_CAPI void TS_CCALL tsBoundCircled_expandRadius1(TSBoundCircled *bc, const TSVector2d *p);

TS_CAPI void TS_CCALL tsBoundCirclef_expandRadius(TSBoundCirclef *bc, const TSBoundCirclef *c);
TS_CAPI void TS_CCALL tsBoundCircled_expandRadius(TSBoundCircled *bc, const TSBoundCircled *c);

TS_CAPI BOOL TS_CCALL tsBoundCirclef_inside1(const TSBoundCirclef *bc, const TSVector2f *p);
TS_CAPI BOOL TS_CCALL tsBoundCircled_inside1(const TSBoundCircled *bc, const TSVector2d *p);

TS_CAPI BOOL TS_CCALL tsBoundCirclef_inside(const TSBoundCirclef *bc, const TSBoundCirclef *c);
TS_CAPI BOOL TS_CCALL tsBoundCircled_inside(const TSBoundCircled *bc, const TSBoundCircled *c);

TS_CAPI float32_t TS_CCALL tsBoundCirclef_distance(const TSBoundCirclef *bc, const TSVector2f *p);
TS_CAPI float64_t TS_CCALL tsBoundCircled_distance(const TSBoundCircled *bc, const TSVector2d *p);

TS_CAPI void TS_CCALL tsMatrix4x3f_mul_bc(TSBoundCirclef *bc, const TSMatrix4x3f *m, const TSBoundCirclef *c);
TS_CAPI void TS_CCALL tsMatrix4x3d_mul_bc(TSBoundCircled *bc, const TSMatrix4x3d *m, const TSBoundCircled *c);

TS_CAPI void TS_CCALL tsMatrix4x4f_mul_bc(TSBoundCirclef *bc, const TSMatrix4x4f *m, const TSBoundCirclef *c);
TS_CAPI void TS_CCALL tsMatrix4x4d_mul_bc(TSBoundCircled *bc, const TSMatrix4x4d *m, const TSBoundCircled *c);

/*
 */
TS_CAPI void TS_CCALL tsBoundBoxf_set_bbd(TSBoundBoxf *bb, const TSBoundBoxd *b);
TS_CAPI void TS_CCALL tsBoundBoxd_set_bbf(TSBoundBoxd *bb, const TSBoundBoxf *b);

TS_CAPI void TS_CCALL tsBoundBoxf_set_bs(TSBoundBoxf *bb, const TSBoundSpheref *s);
TS_CAPI void TS_CCALL tsBoundBoxd_set_bs(TSBoundBoxd *bb, const TSBoundSphered *s);

TS_CAPI void TS_CCALL tsBoundBoxf_expand1(TSBoundBoxf *bb, const TSVector3f *p);
TS_CAPI void TS_CCALL tsBoundBoxd_expand1(TSBoundBoxd *bb, const TSVector3d *p);

TS_CAPI void TS_CCALL tsBoundBoxf_expand(TSBoundBoxf *bb, const TSBoundBoxf *b);
TS_CAPI void TS_CCALL tsBoundBoxd_expand(TSBoundBoxd *bb, const TSBoundBoxd *b);

TS_CAPI BOOL TS_CCALL tsBoundBoxf_inside1(const TSBoundBoxf *bb, const TSVector3f *p);
TS_CAPI BOOL TS_CCALL tsBoundBoxd_inside1(const TSBoundBoxd *bb, const TSVector3d *p);

TS_CAPI BOOL TS_CCALL tsBoundBoxf_inside(const TSBoundBoxf *bb, const TSBoundBoxf *b);
TS_CAPI BOOL TS_CCALL tsBoundBoxd_inside(const TSBoundBoxd *bb, const TSBoundBoxd *b);

TS_CAPI float32_t TS_CCALL tsBoundBoxf_distance(const TSBoundBoxf *bb, const TSVector3f *p);
TS_CAPI float64_t TS_CCALL tsBoundBoxd_distance(const TSBoundBoxd *bb, const TSVector3d *p);

TS_CAPI void TS_CCALL tsMatrix4x3f_mul_bb(TSBoundBoxf *bb, const TSMatrix4x3f *m, const TSBoundBoxf *b);
TS_CAPI void TS_CCALL tsMatrix4x3d_mul_bb(TSBoundBoxd *bb, const TSMatrix4x3d *m, const TSBoundBoxd *b);

TS_CAPI void TS_CCALL tsMatrix4x4f_mul_bb(TSBoundBoxf *bb, const TSMatrix4x4f *m, const TSBoundBoxf *b);
TS_CAPI void TS_CCALL tsMatrix4x4d_mul_bb(TSBoundBoxd *bb, const TSMatrix4x4d *m, const TSBoundBoxd *b);

/*
 */
TS_CAPI void TS_CCALL tsBoundSpheref_set_bsd(TSBoundSpheref *bs, const TSBoundSphered *s);
TS_CAPI void TS_CCALL tsBoundSphered_set_bsf(TSBoundSphered *bs, const TSBoundSpheref *s);

TS_CAPI void TS_CCALL tsBoundSpheref_set_bb(TSBoundSpheref *bs, const TSBoundBoxf *b);
TS_CAPI void TS_CCALL tsBoundSphered_set_bb(TSBoundSphered *bs, const TSBoundBoxd *b);

TS_CAPI void TS_CCALL tsBoundSpheref_expand1(TSBoundSpheref *bs, const TSVector3f *p);
TS_CAPI void TS_CCALL tsBoundSphered_expand1(TSBoundSphered *bs, const TSVector3d *p);

TS_CAPI void TS_CCALL tsBoundSpheref_expand(TSBoundSpheref *bs, const TSBoundSpheref *s);
TS_CAPI void TS_CCALL tsBoundSphered_expand(TSBoundSphered *bs, const TSBoundSphered *s);

TS_CAPI void TS_CCALL tsBoundSpheref_expandRadius1(TSBoundSpheref *bs, const TSVector3f *p);
TS_CAPI void TS_CCALL tsBoundSphered_expandRadius1(TSBoundSphered *bs, const TSVector3d *p);

TS_CAPI void TS_CCALL tsBoundSpheref_expandRadius(TSBoundSpheref *bs, const TSBoundSpheref *s);
TS_CAPI void TS_CCALL tsBoundSphered_expandRadius(TSBoundSphered *bs, const TSBoundSphered *s);

TS_CAPI BOOL TS_CCALL tsBoundSpheref_inside1(const TSBoundSpheref *bs, const TSVector3f *p);
TS_CAPI BOOL TS_CCALL tsBoundSphered_inside1(const TSBoundSphered *bs, const TSVector3d *p);

TS_CAPI BOOL TS_CCALL tsBoundSpheref_inside(const TSBoundSpheref *bs, const TSBoundSpheref *s);
TS_CAPI BOOL TS_CCALL tsBoundSphered_inside(const TSBoundSphered *bs, const TSBoundSphered *s);

TS_CAPI float32_t TS_CCALL tsBoundSpheref_distance(const TSBoundSpheref *bs, const TSVector3f *p);
TS_CAPI float64_t TS_CCALL tsBoundSphered_distance(const TSBoundSphered *bs, const TSVector3d *p);

TS_CAPI void TS_CCALL tsMatrix4x3f_mul_bs(TSBoundSpheref *bs, const TSMatrix4x3f *m, const TSBoundSpheref *s);
TS_CAPI void TS_CCALL tsMatrix4x3d_mul_bs(TSBoundSphered *bs, const TSMatrix4x3d *m, const TSBoundSphered *s);

TS_CAPI void TS_CCALL tsMatrix4x4f_mul_bs(TSBoundSpheref *bs, const TSMatrix4x4f *m, const TSBoundSpheref *s);
TS_CAPI void TS_CCALL tsMatrix4x4d_mul_bs(TSBoundSphered *bs, const TSMatrix4x4d *m, const TSBoundSphered *s);

/*
 */
TS_CAPI void TS_CCALL tsBoundFrustumf_set_bfd(TSBoundFrustumf *bf, const TSBoundFrustumd *f);
TS_CAPI void TS_CCALL tsBoundFrustumd_set_bff(TSBoundFrustumd *bf, const TSBoundFrustumf *f);

TS_CAPI void TS_CCALL tsBoundFrustumf_set(TSBoundFrustumf *bf, const TSMatrix4x4f *projection, const TSMatrix4x4f *modelview, float32_t aspect);
TS_CAPI void TS_CCALL tsBoundFrustumd_set(TSBoundFrustumd *bf, const TSMatrix4x4d *projection, const TSMatrix4x4d *modelview, float64_t aspect);

TS_CAPI BOOL TS_CCALL tsBoundFrustumf_inside_bb(const TSBoundFrustumf *bf, const TSBoundBoxf *b);
TS_CAPI BOOL TS_CCALL tsBoundFrustumd_inside_bb(const TSBoundFrustumd *bf, const TSBoundBoxd *b);

TS_CAPI BOOL TS_CCALL tsBoundFrustumf_inside_bs(const TSBoundFrustumf *bf, const TSBoundSpheref *s);
TS_CAPI BOOL TS_CCALL tsBoundFrustumd_inside_bs(const TSBoundFrustumd *bf, const TSBoundSphered *s);

/*****************************************************************************\
 *
 * Platform
 *
\*****************************************************************************/

/*
 */
typedef struct TSOrigin {
	uint32_t x;
	uint32_t y;
	uint32_t z;
} TSOrigin;

typedef struct TSSize {
	uint32_t width;
	uint32_t height;
	uint32_t depth;
} TSSize;

typedef struct TSRegion {
	uint32_t x;
	uint32_t y;
	uint32_t z;
	uint32_t width;
	uint32_t height;
	uint32_t depth;
} TSRegion;

typedef struct TSSlice {
	uint32_t face;
	uint32_t faces;
	uint32_t layer;
	uint32_t layers;
	uint32_t mipmap;
	uint32_t mipmaps;
} TSSlice;

/*
 */
typedef TSOrigin Origin;
typedef TSRegion Region;
typedef TSSlice Slice;

/*
 */
typedef struct TSViewport {
	float32_t x;
	float32_t y;
	float32_t width;
	float32_t height;
	float32_t znear;
	float32_t zfar;
} TSViewport;

typedef struct TSScissor {
	int32_t x;
	int32_t y;
	int32_t width;
	int32_t height;
} TSScissor;

/*
 */
typedef TSViewport Viewport;
typedef TSScissor Scissor;

/*
 */
typedef struct IDXGISwapChain IDXGISwapChain;

/*
 */
typedef struct ID3D10Blob *LPD3D10BLOB;
typedef struct ID3D10Blob ID3DBlob;

/*
 */
typedef struct IDXGIFactory4 IDXGIFactory4;
typedef struct ID3D12Device ID3D12Device;
typedef struct ID3D12CommandQueue ID3D12CommandQueue;
typedef struct ID3D12GraphicsCommandList ID3D12GraphicsCommandList;
typedef struct ID3D12RootSignature ID3D12RootSignature;
typedef struct ID3D12Resource ID3D12Resource;

/*
 */
typedef struct IDXGIFactory IDXGIFactory;
typedef struct ID3D11Device ID3D11Device;
typedef struct ID3D11DeviceContext ID3D11DeviceContext;
typedef struct ID3D11Buffer ID3D11Buffer;
typedef struct ID3D11Texture2D ID3D11Texture2D;
typedef struct ID3D11RenderTargetView ID3D11RenderTargetView;
typedef struct ID3D11DepthStencilView ID3D11DepthStencilView;
typedef struct ID3D11ShaderResourceView ID3D11ShaderResourceView;
typedef struct ID3D11UnorderedAccessView ID3D11UnorderedAccessView;

/*
 */
typedef struct VkInstance_T *VkInstance;
typedef struct VkPhysicalDevice_T *VkPhysicalDevice;
typedef struct VkDevice_T *VkDevice;
typedef struct VkQueue_T *VkQueue;
typedef struct VkCommandBuffer_T *VkCommandBuffer;
typedef struct VkSwapchainKHR_T *VkSwapchainKHR;
typedef struct VkShaderModule_T *VkShaderModule;
typedef struct VkDescriptorSet_T *VkDescriptorSet;
typedef struct VkRenderPass_T *VkRenderPass;
typedef struct VkFramebuffer_T *VkFramebuffer;
typedef struct VkFence_T *VkFence;
typedef struct VkSemaphore_T *VkSemaphore;
typedef struct VkImage_T *VkImage;
typedef struct VkImageView_T *VkImageView;
typedef struct VkBuffer_T *VkBuffer;
typedef struct VkBufferView_T *VkBufferView;
typedef struct VkAccelerationStructureKHR_T *VkAccelerationStructureKHR;

#if _WIN32
	#define TS_VKAPI __stdcall
#else
	#define TS_VKAPI
#endif
typedef void (TS_VKAPI *PFN_vkVoidFunction)(void);
typedef PFN_vkVoidFunction (TS_VKAPI *PFN_vkGetInstanceProcAddr)(VkInstance instance, const char *name);
typedef PFN_vkVoidFunction (TS_VKAPI *PFN_vkGetDeviceProcAddr)(VkDevice device, const char *name);

/*
 */
typedef struct WGPUInstanceImpl *WGPUInstance;
typedef struct WGPUAdapterImpl *WGPUAdapter;
typedef struct WGPUDeviceImpl *WGPUDevice;

/*
 */
typedef struct CUctx_st *CUcontext;
typedef struct CUmod_st *CUmodule;
typedef struct CUfunc_st *CUfunction;
typedef struct CUevent_st *CUevent;
typedef struct CUstream_st *CUstream;
typedef struct CUarray_st *CUarray;
typedef struct CUmipmappedArray_st *CUmipmappedArray;
typedef struct CUextMemory_st *CUexternalMemory;

/*****************************************************************************\
 *
 * Interface
 *
\*****************************************************************************/

/*
 */
typedef struct TSRect {
	float32_t left;
	float32_t right;
	float32_t bottom;
	float32_t top;
} TSRect;

/*
 */
typedef struct TSFontStyle {
	uint32_t size;
	uint32_t scale;
	uint8_t fixed;
	uint8_t kerning;
	TSVector2f spacing;
	TSColor color;
	TSVector3f offset;
	TSColor shadow;
} TSFontStyle;

typedef struct TSFontBatch {
	TSVector3f position;
	TSColor color;
	TSFontStyle *style;
	const char *str;
} TSFontBatch;

typedef struct TSFontBatch32 {
	TSVector3f position;
	TSColor color;
	TSFontStyle *style;
	const uint32_t *str;
} TSFontBatch32;

typedef struct TSStrokeStyle {
	float32_t width;
	float32_t offset;
	TSColor color;
} TSStrokeStyle;

typedef struct TSGradientStyle {
	float32_t radius;
	float32_t length;
	TSVector2f center;
	TSVector2f axis;
	TSColor color_0;
	TSColor color_1;
} TSGradientStyle;

/*
 */
typedef TSFontStyle FontStyle;
typedef TSFontBatch FontBatch;
typedef TSFontBatch32 FontBatch32;
typedef TSStrokeStyle StrokeStyle;
typedef TSGradientStyle GradientStyle;

/*
 */
typedef struct TSCanvasVertex {
	TSVector3f position;
	TSVector2f texcoord;
	uint32_t color;
} TSCanvasVertex;

typedef struct TSCanvasShapeVertex {
	TSVector4f position;
	TSVector4f parameters;
	TSVector2f texcoord;
	TSVector2u padding;
} TSCanvasShapeVertex;

typedef struct TSCanvasStripVertex {
	TSVector4f position;
	TSVector4f parameters;
	TSVector4f adjacencies;
} TSCanvasStripVertex;

/*
 */
typedef TSCanvasVertex CanvasVertex;
typedef TSCanvasShapeVertex CanvasShapeVertex;
typedef TSCanvasStripVertex CanvasStripVertex;

/*****************************************************************************\
 *
 * Parallel
 *
\*****************************************************************************/

/*
 */
typedef struct TSTensor {
	size_t buffer;
	uint32_t format;
	size_t offset;
	uint32_t axis;
	uint32_t kernel;
	uint32_t stride;
	uint32_t padding;
	uint32_t dilation;
	float32_t scale;
	float32_t bias;
	union {
		struct {
			uint32_t width;
			uint32_t height;
			uint32_t depth;
			uint32_t layers;
		};
		uint32_t size[4];
	};
} TSTensor;

/*
 */
typedef TSTensor Tensor;

#ifdef __cplusplus
}
#endif

#endif /* __TELLUSIM_OBJC_BASE_H__ */

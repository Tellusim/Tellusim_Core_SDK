// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PY_API_H__
#define __TELLUSIM_PY_API_H__

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

#include "TellusimPyBase.h"

/*
 */
namespace Tellusim {
	
	/// Tellusim::String
	struct PYString {
		PyObject_HEAD
		String ptr;
	};
	TS_PYAPI extern PyTypeObject PYString_Type;
	TS_PYAPI extern PyNumberMethods PYString_number;
	TS_PYAPI extern PyBufferProcs PYString_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYString_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYString_getsets;
	TS_PYAPI bool isPYString(PyObject *object);
	TS_PYAPI String &pyString_get(PyObject *object);
	TS_PYAPI PyObject *pyString_new(const String &ptr);
	TS_PYAPI PyObject *pyString_new(String &&ptr);
	
	/// Tellusim::App
	struct PYApp {
		PyObject_HEAD
		App ptr;
	};
	TS_PYAPI extern PyTypeObject PYApp_Type;
	TS_PYAPI extern PyNumberMethods PYApp_number;
	TS_PYAPI extern PyBufferProcs PYApp_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYApp_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYApp_getsets;
	TS_PYAPI bool isPYApp(PyObject *object);
	TS_PYAPI App &pyApp_get(PyObject *object);
	
	/// Tellusim::Async
	struct PYAsync {
		PyObject_HEAD
		Async ptr;
	};
	TS_PYAPI extern PyTypeObject PYAsync_Type;
	TS_PYAPI extern PyNumberMethods PYAsync_number;
	TS_PYAPI extern PyBufferProcs PYAsync_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYAsync_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYAsync_getsets;
	TS_PYAPI bool isPYAsync(PyObject *object);
	TS_PYAPI Async &pyAsync_get(PyObject *object);
	TS_PYAPI PyObject *pyAsync_new(const Async &ptr);
	TS_PYAPI PyObject *pyAsync_new(Async &&ptr);
	
	/// Tellusim::Stream
	struct PYStream {
		PyObject_HEAD
		Stream ptr;
	};
	TS_PYAPI extern PyTypeObject PYStream_Type;
	TS_PYAPI extern PyNumberMethods PYStream_number;
	TS_PYAPI extern PyBufferProcs PYStream_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYStream_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYStream_getsets;
	TS_PYAPI bool isPYStream(PyObject *object);
	TS_PYAPI Stream &pyStream_get(PyObject *object);
	TS_PYAPI PyObject *pyStream_new(const Stream &ptr);
	TS_PYAPI PyObject *pyStream_new(Stream &&ptr);
	
	/// Tellusim::Blob
	struct PYBlob {
		PYStream base;
		Blob ptr;
	};
	TS_PYAPI extern PyTypeObject PYBlob_Type;
	TS_PYAPI extern PyNumberMethods PYBlob_number;
	TS_PYAPI extern PyBufferProcs PYBlob_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYBlob_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYBlob_getsets;
	TS_PYAPI bool isPYBlob(PyObject *object);
	TS_PYAPI Blob &pyBlob_get(PyObject *object);
	TS_PYAPI PyObject *pyBlob_new(const Blob &ptr);
	TS_PYAPI PyObject *pyBlob_new(Blob &&ptr);
	
	/// Tellusim::File
	struct PYFile {
		PYStream base;
		File ptr;
	};
	TS_PYAPI extern PyTypeObject PYFile_Type;
	TS_PYAPI extern PyNumberMethods PYFile_number;
	TS_PYAPI extern PyBufferProcs PYFile_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYFile_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYFile_getsets;
	TS_PYAPI bool isPYFile(PyObject *object);
	TS_PYAPI File &pyFile_get(PyObject *object);
	TS_PYAPI PyObject *pyFile_new(const File &ptr);
	TS_PYAPI PyObject *pyFile_new(File &&ptr);
	
	/// Tellusim::Socket
	struct PYSocket {
		PYStream base;
		Socket ptr;
	};
	TS_PYAPI extern PyTypeObject PYSocket_Type;
	TS_PYAPI extern PyNumberMethods PYSocket_number;
	TS_PYAPI extern PyBufferProcs PYSocket_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYSocket_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYSocket_getsets;
	TS_PYAPI bool isPYSocket(PyObject *object);
	TS_PYAPI Socket &pySocket_get(PyObject *object);
	TS_PYAPI PyObject *pySocket_new(const Socket &ptr);
	TS_PYAPI PyObject *pySocket_new(Socket &&ptr);
	
	/// Tellusim::SocketSSL
	struct PYSocketSSL {
		PYSocket base;
		SocketSSL ptr;
	};
	TS_PYAPI extern PyTypeObject PYSocketSSL_Type;
	TS_PYAPI extern PyNumberMethods PYSocketSSL_number;
	TS_PYAPI extern PyBufferProcs PYSocketSSL_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYSocketSSL_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYSocketSSL_getsets;
	TS_PYAPI bool isPYSocketSSL(PyObject *object);
	TS_PYAPI SocketSSL &pySocketSSL_get(PyObject *object);
	TS_PYAPI PyObject *pySocketSSL_new(const SocketSSL &ptr);
	TS_PYAPI PyObject *pySocketSSL_new(SocketSSL &&ptr);
	
	/// Tellusim::Source
	struct PYSource {
		PYStream base;
		Source ptr;
	};
	TS_PYAPI extern PyTypeObject PYSource_Type;
	TS_PYAPI extern PyNumberMethods PYSource_number;
	TS_PYAPI extern PyBufferProcs PYSource_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYSource_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYSource_getsets;
	TS_PYAPI bool isPYSource(PyObject *object);
	TS_PYAPI Source &pySource_get(PyObject *object);
	TS_PYAPI PyObject *pySource_new(const Source &ptr);
	TS_PYAPI PyObject *pySource_new(Source &&ptr);
	
	/// Tellusim::Date
	struct PYDate {
		PyObject_HEAD
		Date ptr;
	};
	TS_PYAPI extern PyTypeObject PYDate_Type;
	TS_PYAPI extern PyNumberMethods PYDate_number;
	TS_PYAPI extern PyBufferProcs PYDate_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYDate_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYDate_getsets;
	TS_PYAPI bool isPYDate(PyObject *object);
	TS_PYAPI Date &pyDate_get(PyObject *object);
	TS_PYAPI PyObject *pyDate_new(const Date &ptr);
	TS_PYAPI PyObject *pyDate_new(Date &&ptr);
	
	/// Tellusim::Info
	struct PYInfo {
		PyObject_HEAD
		Info ptr;
	};
	TS_PYAPI extern PyTypeObject PYInfo_Type;
	TS_PYAPI extern PyNumberMethods PYInfo_number;
	TS_PYAPI extern PyBufferProcs PYInfo_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYInfo_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYInfo_getsets;
	TS_PYAPI bool isPYInfo(PyObject *object);
	TS_PYAPI Info &pyInfo_get(PyObject *object);
	TS_PYAPI PyObject *pyInfo_new(const Info &ptr);
	TS_PYAPI PyObject *pyInfo_new(Info &&ptr);
	
	/// Tellusim::Directory
	struct PYDirectory {
		PyObject_HEAD
		Directory ptr;
	};
	TS_PYAPI extern PyTypeObject PYDirectory_Type;
	TS_PYAPI extern PyNumberMethods PYDirectory_number;
	TS_PYAPI extern PyBufferProcs PYDirectory_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYDirectory_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYDirectory_getsets;
	TS_PYAPI bool isPYDirectory(PyObject *object);
	TS_PYAPI Directory &pyDirectory_get(PyObject *object);
	TS_PYAPI PyObject *pyDirectory_new(const Directory &ptr);
	TS_PYAPI PyObject *pyDirectory_new(Directory &&ptr);
	
	/// Tellusim::Archive
	struct PYArchive {
		PyObject_HEAD
		Archive ptr;
	};
	TS_PYAPI extern PyTypeObject PYArchive_Type;
	TS_PYAPI extern PyNumberMethods PYArchive_number;
	TS_PYAPI extern PyBufferProcs PYArchive_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYArchive_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYArchive_getsets;
	TS_PYAPI bool isPYArchive(PyObject *object);
	TS_PYAPI Archive &pyArchive_get(PyObject *object);
	
	/// Tellusim::Image
	struct PYImage {
		PyObject_HEAD
		Image ptr;
		Py_ssize_t shape[8];
		Py_ssize_t strides[8];
	};
	TS_PYAPI extern PyTypeObject PYImage_Type;
	TS_PYAPI extern PyNumberMethods PYImage_number;
	TS_PYAPI extern PyBufferProcs PYImage_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYImage_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYImage_getsets;
	TS_PYAPI bool isPYImage(PyObject *object);
	TS_PYAPI Image &pyImage_get(PyObject *object);
	TS_PYAPI PyObject *pyImage_new(const Image &ptr);
	TS_PYAPI PyObject *pyImage_new(Image &&ptr);
	
	/// Tellusim::ImageSampler
	struct PYImageSampler {
		PyObject_HEAD
		ImageSampler ptr;
		Py_ssize_t shape[8];
		Py_ssize_t strides[8];
	};
	TS_PYAPI extern PyTypeObject PYImageSampler_Type;
	TS_PYAPI extern PyNumberMethods PYImageSampler_number;
	TS_PYAPI extern PyBufferProcs PYImageSampler_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYImageSampler_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYImageSampler_getsets;
	TS_PYAPI bool isPYImageSampler(PyObject *object);
	TS_PYAPI ImageSampler &pyImageSampler_get(PyObject *object);
	TS_PYAPI PyObject *pyImageSampler_new(const ImageSampler &ptr);
	TS_PYAPI PyObject *pyImageSampler_new(ImageSampler &&ptr);
	
	/// Tellusim::MeshNode
	struct PYMeshNode {
		PyObject_HEAD
		MeshNode ptr;
	};
	TS_PYAPI extern PyTypeObject PYMeshNode_Type;
	TS_PYAPI extern PyNumberMethods PYMeshNode_number;
	TS_PYAPI extern PyBufferProcs PYMeshNode_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMeshNode_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMeshNode_getsets;
	TS_PYAPI bool isPYMeshNode(PyObject *object);
	TS_PYAPI MeshNode &pyMeshNode_get(PyObject *object);
	TS_PYAPI PyObject *pyMeshNode_new(const MeshNode &ptr);
	TS_PYAPI PyObject *pyMeshNode_new(MeshNode &&ptr);
	
	/// Tellusim::MeshIndices
	struct PYMeshIndices {
		PyObject_HEAD
		MeshIndices ptr;
		Py_ssize_t shape[8];
		Py_ssize_t strides[8];
	};
	TS_PYAPI extern PyTypeObject PYMeshIndices_Type;
	TS_PYAPI extern PyNumberMethods PYMeshIndices_number;
	TS_PYAPI extern PyBufferProcs PYMeshIndices_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMeshIndices_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMeshIndices_getsets;
	TS_PYAPI bool isPYMeshIndices(PyObject *object);
	TS_PYAPI MeshIndices &pyMeshIndices_get(PyObject *object);
	TS_PYAPI PyObject *pyMeshIndices_new(const MeshIndices &ptr);
	TS_PYAPI PyObject *pyMeshIndices_new(MeshIndices &&ptr);
	
	/// Tellusim::MeshAttribute
	struct PYMeshAttribute {
		PyObject_HEAD
		MeshAttribute ptr;
		Py_ssize_t shape[8];
		Py_ssize_t strides[8];
	};
	TS_PYAPI extern PyTypeObject PYMeshAttribute_Type;
	TS_PYAPI extern PyNumberMethods PYMeshAttribute_number;
	TS_PYAPI extern PyBufferProcs PYMeshAttribute_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMeshAttribute_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMeshAttribute_getsets;
	TS_PYAPI bool isPYMeshAttribute(PyObject *object);
	TS_PYAPI MeshAttribute &pyMeshAttribute_get(PyObject *object);
	TS_PYAPI PyObject *pyMeshAttribute_new(const MeshAttribute &ptr);
	TS_PYAPI PyObject *pyMeshAttribute_new(MeshAttribute &&ptr);
	
	/// Tellusim::MeshJoint
	struct PYMeshJoint {
		PyObject_HEAD
		MeshJoint ptr;
	};
	TS_PYAPI extern PyTypeObject PYMeshJoint_Type;
	TS_PYAPI extern PyNumberMethods PYMeshJoint_number;
	TS_PYAPI extern PyBufferProcs PYMeshJoint_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMeshJoint_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMeshJoint_getsets;
	TS_PYAPI bool isPYMeshJoint(PyObject *object);
	TS_PYAPI MeshJoint &pyMeshJoint_get(PyObject *object);
	TS_PYAPI PyObject *pyMeshJoint_new(const MeshJoint &ptr);
	TS_PYAPI PyObject *pyMeshJoint_new(MeshJoint &&ptr);
	
	/// Tellusim::MeshMaterial
	struct PYMeshMaterial {
		PyObject_HEAD
		MeshMaterial ptr;
	};
	TS_PYAPI extern PyTypeObject PYMeshMaterial_Type;
	TS_PYAPI extern PyNumberMethods PYMeshMaterial_number;
	TS_PYAPI extern PyBufferProcs PYMeshMaterial_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMeshMaterial_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMeshMaterial_getsets;
	TS_PYAPI bool isPYMeshMaterial(PyObject *object);
	TS_PYAPI MeshMaterial &pyMeshMaterial_get(PyObject *object);
	TS_PYAPI PyObject *pyMeshMaterial_new(const MeshMaterial &ptr);
	TS_PYAPI PyObject *pyMeshMaterial_new(MeshMaterial &&ptr);
	
	/// Tellusim::MeshGeometry
	struct PYMeshGeometry {
		PyObject_HEAD
		MeshGeometry ptr;
	};
	TS_PYAPI extern PyTypeObject PYMeshGeometry_Type;
	TS_PYAPI extern PyNumberMethods PYMeshGeometry_number;
	TS_PYAPI extern PyBufferProcs PYMeshGeometry_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMeshGeometry_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMeshGeometry_getsets;
	TS_PYAPI bool isPYMeshGeometry(PyObject *object);
	TS_PYAPI MeshGeometry &pyMeshGeometry_get(PyObject *object);
	TS_PYAPI PyObject *pyMeshGeometry_new(const MeshGeometry &ptr);
	TS_PYAPI PyObject *pyMeshGeometry_new(MeshGeometry &&ptr);
	
	/// Tellusim::MeshTransform
	struct PYMeshTransform {
		PyObject_HEAD
		MeshTransform ptr;
	};
	TS_PYAPI extern PyTypeObject PYMeshTransform_Type;
	TS_PYAPI extern PyNumberMethods PYMeshTransform_number;
	TS_PYAPI extern PyBufferProcs PYMeshTransform_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMeshTransform_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMeshTransform_getsets;
	TS_PYAPI bool isPYMeshTransform(PyObject *object);
	TS_PYAPI MeshTransform &pyMeshTransform_get(PyObject *object);
	TS_PYAPI PyObject *pyMeshTransform_new(const MeshTransform &ptr);
	TS_PYAPI PyObject *pyMeshTransform_new(MeshTransform &&ptr);
	
	/// Tellusim::MeshAnimation
	struct PYMeshAnimation {
		PyObject_HEAD
		MeshAnimation ptr;
	};
	TS_PYAPI extern PyTypeObject PYMeshAnimation_Type;
	TS_PYAPI extern PyNumberMethods PYMeshAnimation_number;
	TS_PYAPI extern PyBufferProcs PYMeshAnimation_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMeshAnimation_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMeshAnimation_getsets;
	TS_PYAPI bool isPYMeshAnimation(PyObject *object);
	TS_PYAPI MeshAnimation &pyMeshAnimation_get(PyObject *object);
	TS_PYAPI PyObject *pyMeshAnimation_new(const MeshAnimation &ptr);
	TS_PYAPI PyObject *pyMeshAnimation_new(MeshAnimation &&ptr);
	
	/// Tellusim::MeshAttachment
	struct PYMeshAttachment {
		PyObject_HEAD
		MeshAttachment ptr;
	};
	TS_PYAPI extern PyTypeObject PYMeshAttachment_Type;
	TS_PYAPI extern PyNumberMethods PYMeshAttachment_number;
	TS_PYAPI extern PyBufferProcs PYMeshAttachment_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMeshAttachment_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMeshAttachment_getsets;
	TS_PYAPI bool isPYMeshAttachment(PyObject *object);
	TS_PYAPI MeshAttachment &pyMeshAttachment_get(PyObject *object);
	TS_PYAPI PyObject *pyMeshAttachment_new(const MeshAttachment &ptr);
	TS_PYAPI PyObject *pyMeshAttachment_new(MeshAttachment &&ptr);
	
	/// Tellusim::Mesh
	struct PYMesh {
		PyObject_HEAD
		Mesh ptr;
	};
	TS_PYAPI extern PyTypeObject PYMesh_Type;
	TS_PYAPI extern PyNumberMethods PYMesh_number;
	TS_PYAPI extern PyBufferProcs PYMesh_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMesh_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMesh_getsets;
	TS_PYAPI bool isPYMesh(PyObject *object);
	TS_PYAPI Mesh &pyMesh_get(PyObject *object);
	TS_PYAPI PyObject *pyMesh_new(const Mesh &ptr);
	TS_PYAPI PyObject *pyMesh_new(Mesh &&ptr);
	
	/// Tellusim::Json
	struct PYJson {
		PyObject_HEAD
		Json ptr;
	};
	TS_PYAPI extern PyTypeObject PYJson_Type;
	TS_PYAPI extern PyNumberMethods PYJson_number;
	TS_PYAPI extern PyBufferProcs PYJson_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYJson_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYJson_getsets;
	TS_PYAPI bool isPYJson(PyObject *object);
	TS_PYAPI Json &pyJson_get(PyObject *object);
	TS_PYAPI PyObject *pyJson_new(const Json &ptr);
	TS_PYAPI PyObject *pyJson_new(Json &&ptr);
	
	/// Tellusim::Xml
	struct PYXml {
		PyObject_HEAD
		Xml ptr;
	};
	TS_PYAPI extern PyTypeObject PYXml_Type;
	TS_PYAPI extern PyNumberMethods PYXml_number;
	TS_PYAPI extern PyBufferProcs PYXml_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYXml_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYXml_getsets;
	TS_PYAPI bool isPYXml(PyObject *object);
	TS_PYAPI Xml &pyXml_get(PyObject *object);
	TS_PYAPI PyObject *pyXml_new(const Xml &ptr);
	TS_PYAPI PyObject *pyXml_new(Xml &&ptr);
	
	/// Tellusim::Buffer
	struct PYBuffer {
		PyObject_HEAD
		Buffer ptr;
	};
	TS_PYAPI extern PyTypeObject PYBuffer_Type;
	TS_PYAPI extern PyNumberMethods PYBuffer_number;
	TS_PYAPI extern PyBufferProcs PYBuffer_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYBuffer_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYBuffer_getsets;
	TS_PYAPI bool isPYBuffer(PyObject *object);
	TS_PYAPI Buffer &pyBuffer_get(PyObject *object);
	TS_PYAPI PyObject *pyBuffer_new(const Buffer &ptr);
	TS_PYAPI PyObject *pyBuffer_new(Buffer &&ptr);
	
	/// Tellusim::BufferTable
	struct PYBufferTable {
		PyObject_HEAD
		BufferTable ptr;
	};
	TS_PYAPI extern PyTypeObject PYBufferTable_Type;
	TS_PYAPI extern PyNumberMethods PYBufferTable_number;
	TS_PYAPI extern PyBufferProcs PYBufferTable_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYBufferTable_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYBufferTable_getsets;
	TS_PYAPI bool isPYBufferTable(PyObject *object);
	TS_PYAPI BufferTable &pyBufferTable_get(PyObject *object);
	TS_PYAPI PyObject *pyBufferTable_new(const BufferTable &ptr);
	TS_PYAPI PyObject *pyBufferTable_new(BufferTable &&ptr);
	
	/// Tellusim::D3D12Buffer
	struct PYD3D12Buffer {
		PYBuffer base;
		D3D12Buffer ptr;
	};
	TS_PYAPI extern PyTypeObject PYD3D12Buffer_Type;
	TS_PYAPI extern PyNumberMethods PYD3D12Buffer_number;
	TS_PYAPI extern PyBufferProcs PYD3D12Buffer_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYD3D12Buffer_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYD3D12Buffer_getsets;
	TS_PYAPI bool isPYD3D12Buffer(PyObject *object);
	TS_PYAPI D3D12Buffer &pyD3D12Buffer_get(PyObject *object);
	TS_PYAPI PyObject *pyD3D12Buffer_new(const D3D12Buffer &ptr);
	TS_PYAPI PyObject *pyD3D12Buffer_new(D3D12Buffer &&ptr);
	
	/// Tellusim::D3D11Buffer
	struct PYD3D11Buffer {
		PYBuffer base;
		D3D11Buffer ptr;
	};
	TS_PYAPI extern PyTypeObject PYD3D11Buffer_Type;
	TS_PYAPI extern PyNumberMethods PYD3D11Buffer_number;
	TS_PYAPI extern PyBufferProcs PYD3D11Buffer_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYD3D11Buffer_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYD3D11Buffer_getsets;
	TS_PYAPI bool isPYD3D11Buffer(PyObject *object);
	TS_PYAPI D3D11Buffer &pyD3D11Buffer_get(PyObject *object);
	TS_PYAPI PyObject *pyD3D11Buffer_new(const D3D11Buffer &ptr);
	TS_PYAPI PyObject *pyD3D11Buffer_new(D3D11Buffer &&ptr);
	
	/// Tellusim::MTLBuffer
	struct PYMTLBuffer {
		PYBuffer base;
		MTLBuffer ptr;
	};
	TS_PYAPI extern PyTypeObject PYMTLBuffer_Type;
	TS_PYAPI extern PyNumberMethods PYMTLBuffer_number;
	TS_PYAPI extern PyBufferProcs PYMTLBuffer_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMTLBuffer_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMTLBuffer_getsets;
	TS_PYAPI bool isPYMTLBuffer(PyObject *object);
	TS_PYAPI MTLBuffer &pyMTLBuffer_get(PyObject *object);
	TS_PYAPI PyObject *pyMTLBuffer_new(const MTLBuffer &ptr);
	TS_PYAPI PyObject *pyMTLBuffer_new(MTLBuffer &&ptr);
	
	/// Tellusim::VKBuffer
	struct PYVKBuffer {
		PYBuffer base;
		VKBuffer ptr;
	};
	TS_PYAPI extern PyTypeObject PYVKBuffer_Type;
	TS_PYAPI extern PyNumberMethods PYVKBuffer_number;
	TS_PYAPI extern PyBufferProcs PYVKBuffer_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYVKBuffer_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYVKBuffer_getsets;
	TS_PYAPI bool isPYVKBuffer(PyObject *object);
	TS_PYAPI VKBuffer &pyVKBuffer_get(PyObject *object);
	TS_PYAPI PyObject *pyVKBuffer_new(const VKBuffer &ptr);
	TS_PYAPI PyObject *pyVKBuffer_new(VKBuffer &&ptr);
	
	/// Tellusim::GLBuffer
	struct PYGLBuffer {
		PYBuffer base;
		GLBuffer ptr;
	};
	TS_PYAPI extern PyTypeObject PYGLBuffer_Type;
	TS_PYAPI extern PyNumberMethods PYGLBuffer_number;
	TS_PYAPI extern PyBufferProcs PYGLBuffer_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYGLBuffer_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYGLBuffer_getsets;
	TS_PYAPI bool isPYGLBuffer(PyObject *object);
	TS_PYAPI GLBuffer &pyGLBuffer_get(PyObject *object);
	TS_PYAPI PyObject *pyGLBuffer_new(const GLBuffer &ptr);
	TS_PYAPI PyObject *pyGLBuffer_new(GLBuffer &&ptr);
	
	/// Tellusim::GLESBuffer
	struct PYGLESBuffer {
		PYBuffer base;
		GLESBuffer ptr;
	};
	TS_PYAPI extern PyTypeObject PYGLESBuffer_Type;
	TS_PYAPI extern PyNumberMethods PYGLESBuffer_number;
	TS_PYAPI extern PyBufferProcs PYGLESBuffer_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYGLESBuffer_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYGLESBuffer_getsets;
	TS_PYAPI bool isPYGLESBuffer(PyObject *object);
	TS_PYAPI GLESBuffer &pyGLESBuffer_get(PyObject *object);
	TS_PYAPI PyObject *pyGLESBuffer_new(const GLESBuffer &ptr);
	TS_PYAPI PyObject *pyGLESBuffer_new(GLESBuffer &&ptr);
	
	/// Tellusim::CUBuffer
	struct PYCUBuffer {
		PYBuffer base;
		CUBuffer ptr;
	};
	TS_PYAPI extern PyTypeObject PYCUBuffer_Type;
	TS_PYAPI extern PyNumberMethods PYCUBuffer_number;
	TS_PYAPI extern PyBufferProcs PYCUBuffer_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYCUBuffer_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYCUBuffer_getsets;
	TS_PYAPI bool isPYCUBuffer(PyObject *object);
	TS_PYAPI CUBuffer &pyCUBuffer_get(PyObject *object);
	TS_PYAPI PyObject *pyCUBuffer_new(const CUBuffer &ptr);
	TS_PYAPI PyObject *pyCUBuffer_new(CUBuffer &&ptr);
	
	/// Tellusim::HIPBuffer
	struct PYHIPBuffer {
		PYBuffer base;
		HIPBuffer ptr;
	};
	TS_PYAPI extern PyTypeObject PYHIPBuffer_Type;
	TS_PYAPI extern PyNumberMethods PYHIPBuffer_number;
	TS_PYAPI extern PyBufferProcs PYHIPBuffer_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYHIPBuffer_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYHIPBuffer_getsets;
	TS_PYAPI bool isPYHIPBuffer(PyObject *object);
	TS_PYAPI HIPBuffer &pyHIPBuffer_get(PyObject *object);
	TS_PYAPI PyObject *pyHIPBuffer_new(const HIPBuffer &ptr);
	TS_PYAPI PyObject *pyHIPBuffer_new(HIPBuffer &&ptr);
	
	/// Tellusim::FUBuffer
	struct PYFUBuffer {
		PYBuffer base;
		FUBuffer ptr;
	};
	TS_PYAPI extern PyTypeObject PYFUBuffer_Type;
	TS_PYAPI extern PyNumberMethods PYFUBuffer_number;
	TS_PYAPI extern PyBufferProcs PYFUBuffer_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYFUBuffer_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYFUBuffer_getsets;
	TS_PYAPI bool isPYFUBuffer(PyObject *object);
	TS_PYAPI FUBuffer &pyFUBuffer_get(PyObject *object);
	TS_PYAPI PyObject *pyFUBuffer_new(const FUBuffer &ptr);
	TS_PYAPI PyObject *pyFUBuffer_new(FUBuffer &&ptr);
	
	/// Tellusim::Command
	struct PYCommand {
		PyObject_HEAD
		Command ptr;
	};
	TS_PYAPI extern PyTypeObject PYCommand_Type;
	TS_PYAPI extern PyNumberMethods PYCommand_number;
	TS_PYAPI extern PyBufferProcs PYCommand_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYCommand_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYCommand_getsets;
	TS_PYAPI bool isPYCommand(PyObject *object);
	TS_PYAPI Command &pyCommand_get(PyObject *object);
	TS_PYAPI PyObject *pyCommand_new(const Command &ptr);
	TS_PYAPI PyObject *pyCommand_new(Command &&ptr);
	
	/// Tellusim::Command::DrawArraysIndirect
	struct PYCommandDrawArraysIndirect {
		PyObject_HEAD
		Command::DrawArraysIndirect ptr;
	};
	TS_PYAPI extern PyNumberMethods PYCommandDrawArraysIndirect_number;
	TS_PYAPI extern PyBufferProcs PYCommandDrawArraysIndirect_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYCommandDrawArraysIndirect_methods;
	TS_PYAPI extern Array<PyMemberDef> PYCommandDrawArraysIndirect_members;
	TS_PYAPI extern Array<PyGetSetDef> PYCommandDrawArraysIndirect_getsets;
	TS_PYAPI extern PyTypeObject PYCommandDrawArraysIndirect_Type;
	TS_PYAPI bool isPYCommandDrawArraysIndirect(PyObject *object);
	TS_PYAPI Command::DrawArraysIndirect &pyCommandDrawArraysIndirect_get(PyObject *object);
	TS_PYAPI PyObject *pyCommandDrawArraysIndirect_new(const Command::DrawArraysIndirect &ptr);
	
	/// Tellusim::Command::DrawElementsIndirect
	struct PYCommandDrawElementsIndirect {
		PyObject_HEAD
		Command::DrawElementsIndirect ptr;
	};
	TS_PYAPI extern PyNumberMethods PYCommandDrawElementsIndirect_number;
	TS_PYAPI extern PyBufferProcs PYCommandDrawElementsIndirect_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYCommandDrawElementsIndirect_methods;
	TS_PYAPI extern Array<PyMemberDef> PYCommandDrawElementsIndirect_members;
	TS_PYAPI extern Array<PyGetSetDef> PYCommandDrawElementsIndirect_getsets;
	TS_PYAPI extern PyTypeObject PYCommandDrawElementsIndirect_Type;
	TS_PYAPI bool isPYCommandDrawElementsIndirect(PyObject *object);
	TS_PYAPI Command::DrawElementsIndirect &pyCommandDrawElementsIndirect_get(PyObject *object);
	TS_PYAPI PyObject *pyCommandDrawElementsIndirect_new(const Command::DrawElementsIndirect &ptr);
	
	/// Tellusim::Command::DrawMeshIndirect
	struct PYCommandDrawMeshIndirect {
		PyObject_HEAD
		Command::DrawMeshIndirect ptr;
	};
	TS_PYAPI extern PyNumberMethods PYCommandDrawMeshIndirect_number;
	TS_PYAPI extern PyBufferProcs PYCommandDrawMeshIndirect_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYCommandDrawMeshIndirect_methods;
	TS_PYAPI extern Array<PyMemberDef> PYCommandDrawMeshIndirect_members;
	TS_PYAPI extern Array<PyGetSetDef> PYCommandDrawMeshIndirect_getsets;
	TS_PYAPI extern PyTypeObject PYCommandDrawMeshIndirect_Type;
	TS_PYAPI bool isPYCommandDrawMeshIndirect(PyObject *object);
	TS_PYAPI Command::DrawMeshIndirect &pyCommandDrawMeshIndirect_get(PyObject *object);
	TS_PYAPI PyObject *pyCommandDrawMeshIndirect_new(const Command::DrawMeshIndirect &ptr);
	
	/// Tellusim::D3D12Command
	struct PYD3D12Command {
		PYCommand base;
		D3D12Command ptr;
	};
	TS_PYAPI extern PyTypeObject PYD3D12Command_Type;
	TS_PYAPI extern PyNumberMethods PYD3D12Command_number;
	TS_PYAPI extern PyBufferProcs PYD3D12Command_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYD3D12Command_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYD3D12Command_getsets;
	TS_PYAPI bool isPYD3D12Command(PyObject *object);
	TS_PYAPI D3D12Command &pyD3D12Command_get(PyObject *object);
	TS_PYAPI PyObject *pyD3D12Command_new(const D3D12Command &ptr);
	TS_PYAPI PyObject *pyD3D12Command_new(D3D12Command &&ptr);
	
	/// Tellusim::MTLCommand
	struct PYMTLCommand {
		PYCommand base;
		MTLCommand ptr;
	};
	TS_PYAPI extern PyTypeObject PYMTLCommand_Type;
	TS_PYAPI extern PyNumberMethods PYMTLCommand_number;
	TS_PYAPI extern PyBufferProcs PYMTLCommand_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMTLCommand_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMTLCommand_getsets;
	TS_PYAPI bool isPYMTLCommand(PyObject *object);
	TS_PYAPI MTLCommand &pyMTLCommand_get(PyObject *object);
	TS_PYAPI PyObject *pyMTLCommand_new(const MTLCommand &ptr);
	TS_PYAPI PyObject *pyMTLCommand_new(MTLCommand &&ptr);
	
	/// Tellusim::VKCommand
	struct PYVKCommand {
		PYCommand base;
		VKCommand ptr;
	};
	TS_PYAPI extern PyTypeObject PYVKCommand_Type;
	TS_PYAPI extern PyNumberMethods PYVKCommand_number;
	TS_PYAPI extern PyBufferProcs PYVKCommand_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYVKCommand_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYVKCommand_getsets;
	TS_PYAPI bool isPYVKCommand(PyObject *object);
	TS_PYAPI VKCommand &pyVKCommand_get(PyObject *object);
	TS_PYAPI PyObject *pyVKCommand_new(const VKCommand &ptr);
	TS_PYAPI PyObject *pyVKCommand_new(VKCommand &&ptr);
	
	/// Tellusim::FUCommand
	struct PYFUCommand {
		PYCommand base;
		FUCommand ptr;
	};
	TS_PYAPI extern PyTypeObject PYFUCommand_Type;
	TS_PYAPI extern PyNumberMethods PYFUCommand_number;
	TS_PYAPI extern PyBufferProcs PYFUCommand_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYFUCommand_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYFUCommand_getsets;
	TS_PYAPI bool isPYFUCommand(PyObject *object);
	TS_PYAPI FUCommand &pyFUCommand_get(PyObject *object);
	TS_PYAPI PyObject *pyFUCommand_new(const FUCommand &ptr);
	TS_PYAPI PyObject *pyFUCommand_new(FUCommand &&ptr);
	
	/// Tellusim::Compute
	struct PYCompute {
		PyObject_HEAD
		Compute ptr;
	};
	TS_PYAPI extern PyTypeObject PYCompute_Type;
	TS_PYAPI extern PyNumberMethods PYCompute_number;
	TS_PYAPI extern PyBufferProcs PYCompute_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYCompute_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYCompute_getsets;
	TS_PYAPI bool isPYCompute(PyObject *object);
	TS_PYAPI Compute &pyCompute_get(PyObject *object);
	TS_PYAPI PyObject *pyCompute_new(const Compute &ptr);
	TS_PYAPI PyObject *pyCompute_new(Compute &&ptr);
	
	/// Tellusim::Compute::DispatchIndirect
	struct PYComputeDispatchIndirect {
		PyObject_HEAD
		Compute::DispatchIndirect ptr;
	};
	TS_PYAPI extern PyNumberMethods PYComputeDispatchIndirect_number;
	TS_PYAPI extern PyBufferProcs PYComputeDispatchIndirect_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYComputeDispatchIndirect_methods;
	TS_PYAPI extern Array<PyMemberDef> PYComputeDispatchIndirect_members;
	TS_PYAPI extern Array<PyGetSetDef> PYComputeDispatchIndirect_getsets;
	TS_PYAPI extern PyTypeObject PYComputeDispatchIndirect_Type;
	TS_PYAPI bool isPYComputeDispatchIndirect(PyObject *object);
	TS_PYAPI Compute::DispatchIndirect &pyComputeDispatchIndirect_get(PyObject *object);
	TS_PYAPI PyObject *pyComputeDispatchIndirect_new(const Compute::DispatchIndirect &ptr);
	
	/// Tellusim::D3D12Compute
	struct PYD3D12Compute {
		PYCompute base;
		D3D12Compute ptr;
	};
	TS_PYAPI extern PyTypeObject PYD3D12Compute_Type;
	TS_PYAPI extern PyNumberMethods PYD3D12Compute_number;
	TS_PYAPI extern PyBufferProcs PYD3D12Compute_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYD3D12Compute_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYD3D12Compute_getsets;
	TS_PYAPI bool isPYD3D12Compute(PyObject *object);
	TS_PYAPI D3D12Compute &pyD3D12Compute_get(PyObject *object);
	TS_PYAPI PyObject *pyD3D12Compute_new(const D3D12Compute &ptr);
	TS_PYAPI PyObject *pyD3D12Compute_new(D3D12Compute &&ptr);
	
	/// Tellusim::MTLCompute
	struct PYMTLCompute {
		PYCompute base;
		MTLCompute ptr;
	};
	TS_PYAPI extern PyTypeObject PYMTLCompute_Type;
	TS_PYAPI extern PyNumberMethods PYMTLCompute_number;
	TS_PYAPI extern PyBufferProcs PYMTLCompute_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMTLCompute_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMTLCompute_getsets;
	TS_PYAPI bool isPYMTLCompute(PyObject *object);
	TS_PYAPI MTLCompute &pyMTLCompute_get(PyObject *object);
	TS_PYAPI PyObject *pyMTLCompute_new(const MTLCompute &ptr);
	TS_PYAPI PyObject *pyMTLCompute_new(MTLCompute &&ptr);
	
	/// Tellusim::VKCompute
	struct PYVKCompute {
		PYCompute base;
		VKCompute ptr;
	};
	TS_PYAPI extern PyTypeObject PYVKCompute_Type;
	TS_PYAPI extern PyNumberMethods PYVKCompute_number;
	TS_PYAPI extern PyBufferProcs PYVKCompute_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYVKCompute_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYVKCompute_getsets;
	TS_PYAPI bool isPYVKCompute(PyObject *object);
	TS_PYAPI VKCompute &pyVKCompute_get(PyObject *object);
	TS_PYAPI PyObject *pyVKCompute_new(const VKCompute &ptr);
	TS_PYAPI PyObject *pyVKCompute_new(VKCompute &&ptr);
	
	/// Tellusim::FUCompute
	struct PYFUCompute {
		PYCompute base;
		FUCompute ptr;
	};
	TS_PYAPI extern PyTypeObject PYFUCompute_Type;
	TS_PYAPI extern PyNumberMethods PYFUCompute_number;
	TS_PYAPI extern PyBufferProcs PYFUCompute_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYFUCompute_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYFUCompute_getsets;
	TS_PYAPI bool isPYFUCompute(PyObject *object);
	TS_PYAPI FUCompute &pyFUCompute_get(PyObject *object);
	TS_PYAPI PyObject *pyFUCompute_new(const FUCompute &ptr);
	TS_PYAPI PyObject *pyFUCompute_new(FUCompute &&ptr);
	
	/// Tellusim::Context
	struct PYContext {
		PyObject_HEAD
		Context ptr;
	};
	TS_PYAPI extern PyTypeObject PYContext_Type;
	TS_PYAPI extern PyNumberMethods PYContext_number;
	TS_PYAPI extern PyBufferProcs PYContext_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYContext_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYContext_getsets;
	TS_PYAPI bool isPYContext(PyObject *object);
	TS_PYAPI Context &pyContext_get(PyObject *object);
	TS_PYAPI PyObject *pyContext_new(const Context &ptr);
	TS_PYAPI PyObject *pyContext_new(Context &&ptr);
	
	/// Tellusim::D3D12Context
	struct PYD3D12Context {
		PYContext base;
		D3D12Context ptr;
	};
	TS_PYAPI extern PyTypeObject PYD3D12Context_Type;
	TS_PYAPI extern PyNumberMethods PYD3D12Context_number;
	TS_PYAPI extern PyBufferProcs PYD3D12Context_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYD3D12Context_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYD3D12Context_getsets;
	TS_PYAPI bool isPYD3D12Context(PyObject *object);
	TS_PYAPI D3D12Context &pyD3D12Context_get(PyObject *object);
	TS_PYAPI PyObject *pyD3D12Context_new(const D3D12Context &ptr);
	TS_PYAPI PyObject *pyD3D12Context_new(D3D12Context &&ptr);
	
	/// Tellusim::D3D11Context
	struct PYD3D11Context {
		PYContext base;
		D3D11Context ptr;
	};
	TS_PYAPI extern PyTypeObject PYD3D11Context_Type;
	TS_PYAPI extern PyNumberMethods PYD3D11Context_number;
	TS_PYAPI extern PyBufferProcs PYD3D11Context_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYD3D11Context_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYD3D11Context_getsets;
	TS_PYAPI bool isPYD3D11Context(PyObject *object);
	TS_PYAPI D3D11Context &pyD3D11Context_get(PyObject *object);
	TS_PYAPI PyObject *pyD3D11Context_new(const D3D11Context &ptr);
	TS_PYAPI PyObject *pyD3D11Context_new(D3D11Context &&ptr);
	
	/// Tellusim::MTLContext
	struct PYMTLContext {
		PYContext base;
		MTLContext ptr;
	};
	TS_PYAPI extern PyTypeObject PYMTLContext_Type;
	TS_PYAPI extern PyNumberMethods PYMTLContext_number;
	TS_PYAPI extern PyBufferProcs PYMTLContext_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMTLContext_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMTLContext_getsets;
	TS_PYAPI bool isPYMTLContext(PyObject *object);
	TS_PYAPI MTLContext &pyMTLContext_get(PyObject *object);
	TS_PYAPI PyObject *pyMTLContext_new(const MTLContext &ptr);
	TS_PYAPI PyObject *pyMTLContext_new(MTLContext &&ptr);
	
	/// Tellusim::VKContext
	struct PYVKContext {
		PYContext base;
		VKContext ptr;
	};
	TS_PYAPI extern PyTypeObject PYVKContext_Type;
	TS_PYAPI extern PyNumberMethods PYVKContext_number;
	TS_PYAPI extern PyBufferProcs PYVKContext_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYVKContext_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYVKContext_getsets;
	TS_PYAPI bool isPYVKContext(PyObject *object);
	TS_PYAPI VKContext &pyVKContext_get(PyObject *object);
	TS_PYAPI PyObject *pyVKContext_new(const VKContext &ptr);
	TS_PYAPI PyObject *pyVKContext_new(VKContext &&ptr);
	
	/// Tellusim::GLContext
	struct PYGLContext {
		PYContext base;
		GLContext ptr;
	};
	TS_PYAPI extern PyTypeObject PYGLContext_Type;
	TS_PYAPI extern PyNumberMethods PYGLContext_number;
	TS_PYAPI extern PyBufferProcs PYGLContext_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYGLContext_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYGLContext_getsets;
	TS_PYAPI bool isPYGLContext(PyObject *object);
	TS_PYAPI GLContext &pyGLContext_get(PyObject *object);
	TS_PYAPI PyObject *pyGLContext_new(const GLContext &ptr);
	TS_PYAPI PyObject *pyGLContext_new(GLContext &&ptr);
	
	/// Tellusim::GLESContext
	struct PYGLESContext {
		PYContext base;
		GLESContext ptr;
	};
	TS_PYAPI extern PyTypeObject PYGLESContext_Type;
	TS_PYAPI extern PyNumberMethods PYGLESContext_number;
	TS_PYAPI extern PyBufferProcs PYGLESContext_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYGLESContext_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYGLESContext_getsets;
	TS_PYAPI bool isPYGLESContext(PyObject *object);
	TS_PYAPI GLESContext &pyGLESContext_get(PyObject *object);
	TS_PYAPI PyObject *pyGLESContext_new(const GLESContext &ptr);
	TS_PYAPI PyObject *pyGLESContext_new(GLESContext &&ptr);
	
	/// Tellusim::WGContext
	struct PYWGContext {
		PYContext base;
		WGContext ptr;
	};
	TS_PYAPI extern PyTypeObject PYWGContext_Type;
	TS_PYAPI extern PyNumberMethods PYWGContext_number;
	TS_PYAPI extern PyBufferProcs PYWGContext_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYWGContext_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYWGContext_getsets;
	TS_PYAPI bool isPYWGContext(PyObject *object);
	TS_PYAPI WGContext &pyWGContext_get(PyObject *object);
	TS_PYAPI PyObject *pyWGContext_new(const WGContext &ptr);
	TS_PYAPI PyObject *pyWGContext_new(WGContext &&ptr);
	
	/// Tellusim::CUContext
	struct PYCUContext {
		PYContext base;
		CUContext ptr;
	};
	TS_PYAPI extern PyTypeObject PYCUContext_Type;
	TS_PYAPI extern PyNumberMethods PYCUContext_number;
	TS_PYAPI extern PyBufferProcs PYCUContext_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYCUContext_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYCUContext_getsets;
	TS_PYAPI bool isPYCUContext(PyObject *object);
	TS_PYAPI CUContext &pyCUContext_get(PyObject *object);
	TS_PYAPI PyObject *pyCUContext_new(const CUContext &ptr);
	TS_PYAPI PyObject *pyCUContext_new(CUContext &&ptr);
	
	/// Tellusim::HIPContext
	struct PYHIPContext {
		PYContext base;
		HIPContext ptr;
	};
	TS_PYAPI extern PyTypeObject PYHIPContext_Type;
	TS_PYAPI extern PyNumberMethods PYHIPContext_number;
	TS_PYAPI extern PyBufferProcs PYHIPContext_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYHIPContext_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYHIPContext_getsets;
	TS_PYAPI bool isPYHIPContext(PyObject *object);
	TS_PYAPI HIPContext &pyHIPContext_get(PyObject *object);
	TS_PYAPI PyObject *pyHIPContext_new(const HIPContext &ptr);
	TS_PYAPI PyObject *pyHIPContext_new(HIPContext &&ptr);
	
	/// Tellusim::Query
	struct PYQuery {
		PyObject_HEAD
		Query ptr;
	};
	TS_PYAPI extern PyTypeObject PYQuery_Type;
	TS_PYAPI extern PyNumberMethods PYQuery_number;
	TS_PYAPI extern PyBufferProcs PYQuery_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYQuery_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYQuery_getsets;
	TS_PYAPI bool isPYQuery(PyObject *object);
	TS_PYAPI Query &pyQuery_get(PyObject *object);
	TS_PYAPI PyObject *pyQuery_new(const Query &ptr);
	TS_PYAPI PyObject *pyQuery_new(Query &&ptr);
	
	/// Tellusim::Query::Statistics
	struct PYQueryStatistics {
		PyObject_HEAD
		Query::Statistics ptr;
	};
	TS_PYAPI extern PyNumberMethods PYQueryStatistics_number;
	TS_PYAPI extern PyBufferProcs PYQueryStatistics_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYQueryStatistics_methods;
	TS_PYAPI extern Array<PyMemberDef> PYQueryStatistics_members;
	TS_PYAPI extern Array<PyGetSetDef> PYQueryStatistics_getsets;
	TS_PYAPI extern PyTypeObject PYQueryStatistics_Type;
	TS_PYAPI bool isPYQueryStatistics(PyObject *object);
	TS_PYAPI Query::Statistics &pyQueryStatistics_get(PyObject *object);
	TS_PYAPI PyObject *pyQueryStatistics_new(const Query::Statistics &ptr);
	
	/// Tellusim::FUQuery
	struct PYFUQuery {
		PYQuery base;
		FUQuery ptr;
	};
	TS_PYAPI extern PyTypeObject PYFUQuery_Type;
	TS_PYAPI extern PyNumberMethods PYFUQuery_number;
	TS_PYAPI extern PyBufferProcs PYFUQuery_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYFUQuery_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYFUQuery_getsets;
	TS_PYAPI bool isPYFUQuery(PyObject *object);
	TS_PYAPI FUQuery &pyFUQuery_get(PyObject *object);
	TS_PYAPI PyObject *pyFUQuery_new(const FUQuery &ptr);
	TS_PYAPI PyObject *pyFUQuery_new(FUQuery &&ptr);
	
	/// Tellusim::Fence
	struct PYFence {
		PyObject_HEAD
		Fence ptr;
	};
	TS_PYAPI extern PyTypeObject PYFence_Type;
	TS_PYAPI extern PyNumberMethods PYFence_number;
	TS_PYAPI extern PyBufferProcs PYFence_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYFence_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYFence_getsets;
	TS_PYAPI bool isPYFence(PyObject *object);
	TS_PYAPI Fence &pyFence_get(PyObject *object);
	TS_PYAPI PyObject *pyFence_new(const Fence &ptr);
	TS_PYAPI PyObject *pyFence_new(Fence &&ptr);
	
	/// Tellusim::VKFence
	struct PYVKFence {
		PYFence base;
		VKFence ptr;
	};
	TS_PYAPI extern PyTypeObject PYVKFence_Type;
	TS_PYAPI extern PyNumberMethods PYVKFence_number;
	TS_PYAPI extern PyBufferProcs PYVKFence_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYVKFence_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYVKFence_getsets;
	TS_PYAPI bool isPYVKFence(PyObject *object);
	TS_PYAPI VKFence &pyVKFence_get(PyObject *object);
	TS_PYAPI PyObject *pyVKFence_new(const VKFence &ptr);
	TS_PYAPI PyObject *pyVKFence_new(VKFence &&ptr);
	
	/// Tellusim::FUFence
	struct PYFUFence {
		PYFence base;
		FUFence ptr;
	};
	TS_PYAPI extern PyTypeObject PYFUFence_Type;
	TS_PYAPI extern PyNumberMethods PYFUFence_number;
	TS_PYAPI extern PyBufferProcs PYFUFence_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYFUFence_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYFUFence_getsets;
	TS_PYAPI bool isPYFUFence(PyObject *object);
	TS_PYAPI FUFence &pyFUFence_get(PyObject *object);
	TS_PYAPI PyObject *pyFUFence_new(const FUFence &ptr);
	TS_PYAPI PyObject *pyFUFence_new(FUFence &&ptr);
	
	/// Tellusim::Shader
	struct PYShader {
		PyObject_HEAD
		Shader ptr;
	};
	TS_PYAPI extern PyTypeObject PYShader_Type;
	TS_PYAPI extern PyNumberMethods PYShader_number;
	TS_PYAPI extern PyBufferProcs PYShader_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYShader_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYShader_getsets;
	TS_PYAPI bool isPYShader(PyObject *object);
	TS_PYAPI Shader &pyShader_get(PyObject *object);
	TS_PYAPI PyObject *pyShader_new(const Shader &ptr);
	TS_PYAPI PyObject *pyShader_new(Shader &&ptr);
	
	/// Tellusim::ShaderCompiler
	struct PYShaderCompiler {
		PYShader base;
		ShaderCompiler ptr;
	};
	TS_PYAPI extern PyTypeObject PYShaderCompiler_Type;
	TS_PYAPI extern PyNumberMethods PYShaderCompiler_number;
	TS_PYAPI extern PyBufferProcs PYShaderCompiler_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYShaderCompiler_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYShaderCompiler_getsets;
	TS_PYAPI bool isPYShaderCompiler(PyObject *object);
	TS_PYAPI ShaderCompiler &pyShaderCompiler_get(PyObject *object);
	TS_PYAPI PyObject *pyShaderCompiler_new(const ShaderCompiler &ptr);
	TS_PYAPI PyObject *pyShaderCompiler_new(ShaderCompiler &&ptr);
	
	/// Tellusim::D3D12Shader
	struct PYD3D12Shader {
		PYShader base;
		D3D12Shader ptr;
	};
	TS_PYAPI extern PyTypeObject PYD3D12Shader_Type;
	TS_PYAPI extern PyNumberMethods PYD3D12Shader_number;
	TS_PYAPI extern PyBufferProcs PYD3D12Shader_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYD3D12Shader_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYD3D12Shader_getsets;
	TS_PYAPI bool isPYD3D12Shader(PyObject *object);
	TS_PYAPI D3D12Shader &pyD3D12Shader_get(PyObject *object);
	TS_PYAPI PyObject *pyD3D12Shader_new(const D3D12Shader &ptr);
	TS_PYAPI PyObject *pyD3D12Shader_new(D3D12Shader &&ptr);
	
	/// Tellusim::D3D11Shader
	struct PYD3D11Shader {
		PYShader base;
		D3D11Shader ptr;
	};
	TS_PYAPI extern PyTypeObject PYD3D11Shader_Type;
	TS_PYAPI extern PyNumberMethods PYD3D11Shader_number;
	TS_PYAPI extern PyBufferProcs PYD3D11Shader_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYD3D11Shader_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYD3D11Shader_getsets;
	TS_PYAPI bool isPYD3D11Shader(PyObject *object);
	TS_PYAPI D3D11Shader &pyD3D11Shader_get(PyObject *object);
	TS_PYAPI PyObject *pyD3D11Shader_new(const D3D11Shader &ptr);
	TS_PYAPI PyObject *pyD3D11Shader_new(D3D11Shader &&ptr);
	
	/// Tellusim::MTLShader
	struct PYMTLShader {
		PYShader base;
		MTLShader ptr;
	};
	TS_PYAPI extern PyTypeObject PYMTLShader_Type;
	TS_PYAPI extern PyNumberMethods PYMTLShader_number;
	TS_PYAPI extern PyBufferProcs PYMTLShader_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMTLShader_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMTLShader_getsets;
	TS_PYAPI bool isPYMTLShader(PyObject *object);
	TS_PYAPI MTLShader &pyMTLShader_get(PyObject *object);
	TS_PYAPI PyObject *pyMTLShader_new(const MTLShader &ptr);
	TS_PYAPI PyObject *pyMTLShader_new(MTLShader &&ptr);
	
	/// Tellusim::VKShader
	struct PYVKShader {
		PYShader base;
		VKShader ptr;
	};
	TS_PYAPI extern PyTypeObject PYVKShader_Type;
	TS_PYAPI extern PyNumberMethods PYVKShader_number;
	TS_PYAPI extern PyBufferProcs PYVKShader_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYVKShader_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYVKShader_getsets;
	TS_PYAPI bool isPYVKShader(PyObject *object);
	TS_PYAPI VKShader &pyVKShader_get(PyObject *object);
	TS_PYAPI PyObject *pyVKShader_new(const VKShader &ptr);
	TS_PYAPI PyObject *pyVKShader_new(VKShader &&ptr);
	
	/// Tellusim::GLShader
	struct PYGLShader {
		PYShader base;
		GLShader ptr;
	};
	TS_PYAPI extern PyTypeObject PYGLShader_Type;
	TS_PYAPI extern PyNumberMethods PYGLShader_number;
	TS_PYAPI extern PyBufferProcs PYGLShader_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYGLShader_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYGLShader_getsets;
	TS_PYAPI bool isPYGLShader(PyObject *object);
	TS_PYAPI GLShader &pyGLShader_get(PyObject *object);
	TS_PYAPI PyObject *pyGLShader_new(const GLShader &ptr);
	TS_PYAPI PyObject *pyGLShader_new(GLShader &&ptr);
	
	/// Tellusim::GLESShader
	struct PYGLESShader {
		PYShader base;
		GLESShader ptr;
	};
	TS_PYAPI extern PyTypeObject PYGLESShader_Type;
	TS_PYAPI extern PyNumberMethods PYGLESShader_number;
	TS_PYAPI extern PyBufferProcs PYGLESShader_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYGLESShader_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYGLESShader_getsets;
	TS_PYAPI bool isPYGLESShader(PyObject *object);
	TS_PYAPI GLESShader &pyGLESShader_get(PyObject *object);
	TS_PYAPI PyObject *pyGLESShader_new(const GLESShader &ptr);
	TS_PYAPI PyObject *pyGLESShader_new(GLESShader &&ptr);
	
	/// Tellusim::CUShader
	struct PYCUShader {
		PYShader base;
		CUShader ptr;
	};
	TS_PYAPI extern PyTypeObject PYCUShader_Type;
	TS_PYAPI extern PyNumberMethods PYCUShader_number;
	TS_PYAPI extern PyBufferProcs PYCUShader_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYCUShader_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYCUShader_getsets;
	TS_PYAPI bool isPYCUShader(PyObject *object);
	TS_PYAPI CUShader &pyCUShader_get(PyObject *object);
	TS_PYAPI PyObject *pyCUShader_new(const CUShader &ptr);
	TS_PYAPI PyObject *pyCUShader_new(CUShader &&ptr);
	
	/// Tellusim::HIPShader
	struct PYHIPShader {
		PYShader base;
		HIPShader ptr;
	};
	TS_PYAPI extern PyTypeObject PYHIPShader_Type;
	TS_PYAPI extern PyNumberMethods PYHIPShader_number;
	TS_PYAPI extern PyBufferProcs PYHIPShader_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYHIPShader_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYHIPShader_getsets;
	TS_PYAPI bool isPYHIPShader(PyObject *object);
	TS_PYAPI HIPShader &pyHIPShader_get(PyObject *object);
	TS_PYAPI PyObject *pyHIPShader_new(const HIPShader &ptr);
	TS_PYAPI PyObject *pyHIPShader_new(HIPShader &&ptr);
	
	/// Tellusim::FUShader
	struct PYFUShader {
		PYShader base;
		FUShader ptr;
	};
	TS_PYAPI extern PyTypeObject PYFUShader_Type;
	TS_PYAPI extern PyNumberMethods PYFUShader_number;
	TS_PYAPI extern PyBufferProcs PYFUShader_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYFUShader_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYFUShader_getsets;
	TS_PYAPI bool isPYFUShader(PyObject *object);
	TS_PYAPI FUShader &pyFUShader_get(PyObject *object);
	TS_PYAPI PyObject *pyFUShader_new(const FUShader &ptr);
	TS_PYAPI PyObject *pyFUShader_new(FUShader &&ptr);
	
	/// Tellusim::Sampler
	struct PYSampler {
		PyObject_HEAD
		Sampler ptr;
	};
	TS_PYAPI extern PyTypeObject PYSampler_Type;
	TS_PYAPI extern PyNumberMethods PYSampler_number;
	TS_PYAPI extern PyBufferProcs PYSampler_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYSampler_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYSampler_getsets;
	TS_PYAPI bool isPYSampler(PyObject *object);
	TS_PYAPI Sampler &pySampler_get(PyObject *object);
	TS_PYAPI PyObject *pySampler_new(const Sampler &ptr);
	TS_PYAPI PyObject *pySampler_new(Sampler &&ptr);
	
	/// Tellusim::MTLSampler
	struct PYMTLSampler {
		PYSampler base;
		MTLSampler ptr;
	};
	TS_PYAPI extern PyTypeObject PYMTLSampler_Type;
	TS_PYAPI extern PyNumberMethods PYMTLSampler_number;
	TS_PYAPI extern PyBufferProcs PYMTLSampler_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMTLSampler_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMTLSampler_getsets;
	TS_PYAPI bool isPYMTLSampler(PyObject *object);
	TS_PYAPI MTLSampler &pyMTLSampler_get(PyObject *object);
	TS_PYAPI PyObject *pyMTLSampler_new(const MTLSampler &ptr);
	TS_PYAPI PyObject *pyMTLSampler_new(MTLSampler &&ptr);
	
	/// Tellusim::FUSampler
	struct PYFUSampler {
		PYSampler base;
		FUSampler ptr;
	};
	TS_PYAPI extern PyTypeObject PYFUSampler_Type;
	TS_PYAPI extern PyNumberMethods PYFUSampler_number;
	TS_PYAPI extern PyBufferProcs PYFUSampler_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYFUSampler_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYFUSampler_getsets;
	TS_PYAPI bool isPYFUSampler(PyObject *object);
	TS_PYAPI FUSampler &pyFUSampler_get(PyObject *object);
	TS_PYAPI PyObject *pyFUSampler_new(const FUSampler &ptr);
	TS_PYAPI PyObject *pyFUSampler_new(FUSampler &&ptr);
	
	/// Tellusim::Texture
	struct PYTexture {
		PyObject_HEAD
		Texture ptr;
	};
	TS_PYAPI extern PyTypeObject PYTexture_Type;
	TS_PYAPI extern PyNumberMethods PYTexture_number;
	TS_PYAPI extern PyBufferProcs PYTexture_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYTexture_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYTexture_getsets;
	TS_PYAPI bool isPYTexture(PyObject *object);
	TS_PYAPI Texture &pyTexture_get(PyObject *object);
	TS_PYAPI PyObject *pyTexture_new(const Texture &ptr);
	TS_PYAPI PyObject *pyTexture_new(Texture &&ptr);
	
	/// Tellusim::TextureTable
	struct PYTextureTable {
		PyObject_HEAD
		TextureTable ptr;
	};
	TS_PYAPI extern PyTypeObject PYTextureTable_Type;
	TS_PYAPI extern PyNumberMethods PYTextureTable_number;
	TS_PYAPI extern PyBufferProcs PYTextureTable_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYTextureTable_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYTextureTable_getsets;
	TS_PYAPI bool isPYTextureTable(PyObject *object);
	TS_PYAPI TextureTable &pyTextureTable_get(PyObject *object);
	TS_PYAPI PyObject *pyTextureTable_new(const TextureTable &ptr);
	TS_PYAPI PyObject *pyTextureTable_new(TextureTable &&ptr);
	
	/// Tellusim::D3D12Texture
	struct PYD3D12Texture {
		PYTexture base;
		D3D12Texture ptr;
	};
	TS_PYAPI extern PyTypeObject PYD3D12Texture_Type;
	TS_PYAPI extern PyNumberMethods PYD3D12Texture_number;
	TS_PYAPI extern PyBufferProcs PYD3D12Texture_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYD3D12Texture_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYD3D12Texture_getsets;
	TS_PYAPI bool isPYD3D12Texture(PyObject *object);
	TS_PYAPI D3D12Texture &pyD3D12Texture_get(PyObject *object);
	TS_PYAPI PyObject *pyD3D12Texture_new(const D3D12Texture &ptr);
	TS_PYAPI PyObject *pyD3D12Texture_new(D3D12Texture &&ptr);
	
	/// Tellusim::D3D11Texture
	struct PYD3D11Texture {
		PYTexture base;
		D3D11Texture ptr;
	};
	TS_PYAPI extern PyTypeObject PYD3D11Texture_Type;
	TS_PYAPI extern PyNumberMethods PYD3D11Texture_number;
	TS_PYAPI extern PyBufferProcs PYD3D11Texture_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYD3D11Texture_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYD3D11Texture_getsets;
	TS_PYAPI bool isPYD3D11Texture(PyObject *object);
	TS_PYAPI D3D11Texture &pyD3D11Texture_get(PyObject *object);
	TS_PYAPI PyObject *pyD3D11Texture_new(const D3D11Texture &ptr);
	TS_PYAPI PyObject *pyD3D11Texture_new(D3D11Texture &&ptr);
	
	/// Tellusim::MTLTexture
	struct PYMTLTexture {
		PYTexture base;
		MTLTexture ptr;
	};
	TS_PYAPI extern PyTypeObject PYMTLTexture_Type;
	TS_PYAPI extern PyNumberMethods PYMTLTexture_number;
	TS_PYAPI extern PyBufferProcs PYMTLTexture_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMTLTexture_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMTLTexture_getsets;
	TS_PYAPI bool isPYMTLTexture(PyObject *object);
	TS_PYAPI MTLTexture &pyMTLTexture_get(PyObject *object);
	TS_PYAPI PyObject *pyMTLTexture_new(const MTLTexture &ptr);
	TS_PYAPI PyObject *pyMTLTexture_new(MTLTexture &&ptr);
	
	/// Tellusim::VKTexture
	struct PYVKTexture {
		PYTexture base;
		VKTexture ptr;
	};
	TS_PYAPI extern PyTypeObject PYVKTexture_Type;
	TS_PYAPI extern PyNumberMethods PYVKTexture_number;
	TS_PYAPI extern PyBufferProcs PYVKTexture_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYVKTexture_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYVKTexture_getsets;
	TS_PYAPI bool isPYVKTexture(PyObject *object);
	TS_PYAPI VKTexture &pyVKTexture_get(PyObject *object);
	TS_PYAPI PyObject *pyVKTexture_new(const VKTexture &ptr);
	TS_PYAPI PyObject *pyVKTexture_new(VKTexture &&ptr);
	
	/// Tellusim::GLTexture
	struct PYGLTexture {
		PYTexture base;
		GLTexture ptr;
	};
	TS_PYAPI extern PyTypeObject PYGLTexture_Type;
	TS_PYAPI extern PyNumberMethods PYGLTexture_number;
	TS_PYAPI extern PyBufferProcs PYGLTexture_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYGLTexture_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYGLTexture_getsets;
	TS_PYAPI bool isPYGLTexture(PyObject *object);
	TS_PYAPI GLTexture &pyGLTexture_get(PyObject *object);
	TS_PYAPI PyObject *pyGLTexture_new(const GLTexture &ptr);
	TS_PYAPI PyObject *pyGLTexture_new(GLTexture &&ptr);
	
	/// Tellusim::GLESTexture
	struct PYGLESTexture {
		PYTexture base;
		GLESTexture ptr;
	};
	TS_PYAPI extern PyTypeObject PYGLESTexture_Type;
	TS_PYAPI extern PyNumberMethods PYGLESTexture_number;
	TS_PYAPI extern PyBufferProcs PYGLESTexture_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYGLESTexture_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYGLESTexture_getsets;
	TS_PYAPI bool isPYGLESTexture(PyObject *object);
	TS_PYAPI GLESTexture &pyGLESTexture_get(PyObject *object);
	TS_PYAPI PyObject *pyGLESTexture_new(const GLESTexture &ptr);
	TS_PYAPI PyObject *pyGLESTexture_new(GLESTexture &&ptr);
	
	/// Tellusim::CUTexture
	struct PYCUTexture {
		PYTexture base;
		CUTexture ptr;
	};
	TS_PYAPI extern PyTypeObject PYCUTexture_Type;
	TS_PYAPI extern PyNumberMethods PYCUTexture_number;
	TS_PYAPI extern PyBufferProcs PYCUTexture_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYCUTexture_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYCUTexture_getsets;
	TS_PYAPI bool isPYCUTexture(PyObject *object);
	TS_PYAPI CUTexture &pyCUTexture_get(PyObject *object);
	TS_PYAPI PyObject *pyCUTexture_new(const CUTexture &ptr);
	TS_PYAPI PyObject *pyCUTexture_new(CUTexture &&ptr);
	
	/// Tellusim::HIPTexture
	struct PYHIPTexture {
		PYTexture base;
		HIPTexture ptr;
	};
	TS_PYAPI extern PyTypeObject PYHIPTexture_Type;
	TS_PYAPI extern PyNumberMethods PYHIPTexture_number;
	TS_PYAPI extern PyBufferProcs PYHIPTexture_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYHIPTexture_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYHIPTexture_getsets;
	TS_PYAPI bool isPYHIPTexture(PyObject *object);
	TS_PYAPI HIPTexture &pyHIPTexture_get(PyObject *object);
	TS_PYAPI PyObject *pyHIPTexture_new(const HIPTexture &ptr);
	TS_PYAPI PyObject *pyHIPTexture_new(HIPTexture &&ptr);
	
	/// Tellusim::FUTexture
	struct PYFUTexture {
		PYTexture base;
		FUTexture ptr;
	};
	TS_PYAPI extern PyTypeObject PYFUTexture_Type;
	TS_PYAPI extern PyNumberMethods PYFUTexture_number;
	TS_PYAPI extern PyBufferProcs PYFUTexture_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYFUTexture_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYFUTexture_getsets;
	TS_PYAPI bool isPYFUTexture(PyObject *object);
	TS_PYAPI FUTexture &pyFUTexture_get(PyObject *object);
	TS_PYAPI PyObject *pyFUTexture_new(const FUTexture &ptr);
	TS_PYAPI PyObject *pyFUTexture_new(FUTexture &&ptr);
	
	/// Tellusim::Tracing
	struct PYTracing {
		PyObject_HEAD
		Tracing ptr;
	};
	TS_PYAPI extern PyTypeObject PYTracing_Type;
	TS_PYAPI extern PyNumberMethods PYTracing_number;
	TS_PYAPI extern PyBufferProcs PYTracing_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYTracing_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYTracing_getsets;
	TS_PYAPI bool isPYTracing(PyObject *object);
	TS_PYAPI Tracing &pyTracing_get(PyObject *object);
	TS_PYAPI PyObject *pyTracing_new(const Tracing &ptr);
	TS_PYAPI PyObject *pyTracing_new(Tracing &&ptr);
	
	/// Tellusim::Tracing::Instance
	struct PYTracingInstance {
		PyObject_HEAD
		Tracing::Instance ptr;
	};
	TS_PYAPI extern PyNumberMethods PYTracingInstance_number;
	TS_PYAPI extern PyBufferProcs PYTracingInstance_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYTracingInstance_methods;
	TS_PYAPI extern Array<PyMemberDef> PYTracingInstance_members;
	TS_PYAPI extern Array<PyGetSetDef> PYTracingInstance_getsets;
	TS_PYAPI extern PyTypeObject PYTracingInstance_Type;
	TS_PYAPI bool isPYTracingInstance(PyObject *object);
	TS_PYAPI Tracing::Instance &pyTracingInstance_get(PyObject *object);
	TS_PYAPI PyObject *pyTracingInstance_new(const Tracing::Instance &ptr);
	
	/// Tellusim::Tracing::BuildIndirect
	struct PYTracingBuildIndirect {
		PyObject_HEAD
		Tracing::BuildIndirect ptr;
	};
	TS_PYAPI extern PyNumberMethods PYTracingBuildIndirect_number;
	TS_PYAPI extern PyBufferProcs PYTracingBuildIndirect_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYTracingBuildIndirect_methods;
	TS_PYAPI extern Array<PyMemberDef> PYTracingBuildIndirect_members;
	TS_PYAPI extern Array<PyGetSetDef> PYTracingBuildIndirect_getsets;
	TS_PYAPI extern PyTypeObject PYTracingBuildIndirect_Type;
	TS_PYAPI bool isPYTracingBuildIndirect(PyObject *object);
	TS_PYAPI Tracing::BuildIndirect &pyTracingBuildIndirect_get(PyObject *object);
	TS_PYAPI PyObject *pyTracingBuildIndirect_new(const Tracing::BuildIndirect &ptr);
	
	/// Tellusim::D3D12Tracing
	struct PYD3D12Tracing {
		PYTracing base;
		D3D12Tracing ptr;
	};
	TS_PYAPI extern PyTypeObject PYD3D12Tracing_Type;
	TS_PYAPI extern PyNumberMethods PYD3D12Tracing_number;
	TS_PYAPI extern PyBufferProcs PYD3D12Tracing_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYD3D12Tracing_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYD3D12Tracing_getsets;
	TS_PYAPI bool isPYD3D12Tracing(PyObject *object);
	TS_PYAPI D3D12Tracing &pyD3D12Tracing_get(PyObject *object);
	TS_PYAPI PyObject *pyD3D12Tracing_new(const D3D12Tracing &ptr);
	TS_PYAPI PyObject *pyD3D12Tracing_new(D3D12Tracing &&ptr);
	
	/// Tellusim::MTLTracing
	struct PYMTLTracing {
		PYTracing base;
		MTLTracing ptr;
	};
	TS_PYAPI extern PyTypeObject PYMTLTracing_Type;
	TS_PYAPI extern PyNumberMethods PYMTLTracing_number;
	TS_PYAPI extern PyBufferProcs PYMTLTracing_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMTLTracing_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMTLTracing_getsets;
	TS_PYAPI bool isPYMTLTracing(PyObject *object);
	TS_PYAPI MTLTracing &pyMTLTracing_get(PyObject *object);
	TS_PYAPI PyObject *pyMTLTracing_new(const MTLTracing &ptr);
	TS_PYAPI PyObject *pyMTLTracing_new(MTLTracing &&ptr);
	
	/// Tellusim::VKTracing
	struct PYVKTracing {
		PYTracing base;
		VKTracing ptr;
	};
	TS_PYAPI extern PyTypeObject PYVKTracing_Type;
	TS_PYAPI extern PyNumberMethods PYVKTracing_number;
	TS_PYAPI extern PyBufferProcs PYVKTracing_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYVKTracing_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYVKTracing_getsets;
	TS_PYAPI bool isPYVKTracing(PyObject *object);
	TS_PYAPI VKTracing &pyVKTracing_get(PyObject *object);
	TS_PYAPI PyObject *pyVKTracing_new(const VKTracing &ptr);
	TS_PYAPI PyObject *pyVKTracing_new(VKTracing &&ptr);
	
	/// Tellusim::FUTracing
	struct PYFUTracing {
		PYTracing base;
		FUTracing ptr;
	};
	TS_PYAPI extern PyTypeObject PYFUTracing_Type;
	TS_PYAPI extern PyNumberMethods PYFUTracing_number;
	TS_PYAPI extern PyBufferProcs PYFUTracing_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYFUTracing_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYFUTracing_getsets;
	TS_PYAPI bool isPYFUTracing(PyObject *object);
	TS_PYAPI FUTracing &pyFUTracing_get(PyObject *object);
	TS_PYAPI PyObject *pyFUTracing_new(const FUTracing &ptr);
	TS_PYAPI PyObject *pyFUTracing_new(FUTracing &&ptr);
	
	/// Tellusim::Target
	struct PYTarget {
		PyObject_HEAD
		Target ptr;
	};
	TS_PYAPI extern PyTypeObject PYTarget_Type;
	TS_PYAPI extern PyNumberMethods PYTarget_number;
	TS_PYAPI extern PyBufferProcs PYTarget_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYTarget_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYTarget_getsets;
	TS_PYAPI bool isPYTarget(PyObject *object);
	TS_PYAPI Target &pyTarget_get(PyObject *object);
	TS_PYAPI PyObject *pyTarget_new(const Target &ptr);
	TS_PYAPI PyObject *pyTarget_new(Target &&ptr);
	
	/// Tellusim::D3D12Target
	struct PYD3D12Target {
		PYTarget base;
		D3D12Target ptr;
	};
	TS_PYAPI extern PyTypeObject PYD3D12Target_Type;
	TS_PYAPI extern PyNumberMethods PYD3D12Target_number;
	TS_PYAPI extern PyBufferProcs PYD3D12Target_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYD3D12Target_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYD3D12Target_getsets;
	TS_PYAPI bool isPYD3D12Target(PyObject *object);
	TS_PYAPI D3D12Target &pyD3D12Target_get(PyObject *object);
	TS_PYAPI PyObject *pyD3D12Target_new(const D3D12Target &ptr);
	TS_PYAPI PyObject *pyD3D12Target_new(D3D12Target &&ptr);
	
	/// Tellusim::D3D11Target
	struct PYD3D11Target {
		PYTarget base;
		D3D11Target ptr;
	};
	TS_PYAPI extern PyTypeObject PYD3D11Target_Type;
	TS_PYAPI extern PyNumberMethods PYD3D11Target_number;
	TS_PYAPI extern PyBufferProcs PYD3D11Target_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYD3D11Target_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYD3D11Target_getsets;
	TS_PYAPI bool isPYD3D11Target(PyObject *object);
	TS_PYAPI D3D11Target &pyD3D11Target_get(PyObject *object);
	TS_PYAPI PyObject *pyD3D11Target_new(const D3D11Target &ptr);
	TS_PYAPI PyObject *pyD3D11Target_new(D3D11Target &&ptr);
	
	/// Tellusim::MTLTarget
	struct PYMTLTarget {
		PYTarget base;
		MTLTarget ptr;
	};
	TS_PYAPI extern PyTypeObject PYMTLTarget_Type;
	TS_PYAPI extern PyNumberMethods PYMTLTarget_number;
	TS_PYAPI extern PyBufferProcs PYMTLTarget_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMTLTarget_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMTLTarget_getsets;
	TS_PYAPI bool isPYMTLTarget(PyObject *object);
	TS_PYAPI MTLTarget &pyMTLTarget_get(PyObject *object);
	TS_PYAPI PyObject *pyMTLTarget_new(const MTLTarget &ptr);
	TS_PYAPI PyObject *pyMTLTarget_new(MTLTarget &&ptr);
	
	/// Tellusim::VKTarget
	struct PYVKTarget {
		PYTarget base;
		VKTarget ptr;
	};
	TS_PYAPI extern PyTypeObject PYVKTarget_Type;
	TS_PYAPI extern PyNumberMethods PYVKTarget_number;
	TS_PYAPI extern PyBufferProcs PYVKTarget_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYVKTarget_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYVKTarget_getsets;
	TS_PYAPI bool isPYVKTarget(PyObject *object);
	TS_PYAPI VKTarget &pyVKTarget_get(PyObject *object);
	TS_PYAPI PyObject *pyVKTarget_new(const VKTarget &ptr);
	TS_PYAPI PyObject *pyVKTarget_new(VKTarget &&ptr);
	
	/// Tellusim::GLTarget
	struct PYGLTarget {
		PYTarget base;
		GLTarget ptr;
	};
	TS_PYAPI extern PyTypeObject PYGLTarget_Type;
	TS_PYAPI extern PyNumberMethods PYGLTarget_number;
	TS_PYAPI extern PyBufferProcs PYGLTarget_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYGLTarget_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYGLTarget_getsets;
	TS_PYAPI bool isPYGLTarget(PyObject *object);
	TS_PYAPI GLTarget &pyGLTarget_get(PyObject *object);
	TS_PYAPI PyObject *pyGLTarget_new(const GLTarget &ptr);
	TS_PYAPI PyObject *pyGLTarget_new(GLTarget &&ptr);
	
	/// Tellusim::GLESTarget
	struct PYGLESTarget {
		PYTarget base;
		GLESTarget ptr;
	};
	TS_PYAPI extern PyTypeObject PYGLESTarget_Type;
	TS_PYAPI extern PyNumberMethods PYGLESTarget_number;
	TS_PYAPI extern PyBufferProcs PYGLESTarget_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYGLESTarget_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYGLESTarget_getsets;
	TS_PYAPI bool isPYGLESTarget(PyObject *object);
	TS_PYAPI GLESTarget &pyGLESTarget_get(PyObject *object);
	TS_PYAPI PyObject *pyGLESTarget_new(const GLESTarget &ptr);
	TS_PYAPI PyObject *pyGLESTarget_new(GLESTarget &&ptr);
	
	/// Tellusim::FUTarget
	struct PYFUTarget {
		PYTarget base;
		FUTarget ptr;
	};
	TS_PYAPI extern PyTypeObject PYFUTarget_Type;
	TS_PYAPI extern PyNumberMethods PYFUTarget_number;
	TS_PYAPI extern PyBufferProcs PYFUTarget_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYFUTarget_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYFUTarget_getsets;
	TS_PYAPI bool isPYFUTarget(PyObject *object);
	TS_PYAPI FUTarget &pyFUTarget_get(PyObject *object);
	TS_PYAPI PyObject *pyFUTarget_new(const FUTarget &ptr);
	TS_PYAPI PyObject *pyFUTarget_new(FUTarget &&ptr);
	
	/// Tellusim::Device
	struct PYDevice {
		PyObject_HEAD
		Device ptr;
	};
	TS_PYAPI extern PyTypeObject PYDevice_Type;
	TS_PYAPI extern PyNumberMethods PYDevice_number;
	TS_PYAPI extern PyBufferProcs PYDevice_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYDevice_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYDevice_getsets;
	TS_PYAPI bool isPYDevice(PyObject *object);
	TS_PYAPI Device &pyDevice_get(PyObject *object);
	TS_PYAPI PyObject *pyDevice_new(const Device &ptr);
	TS_PYAPI PyObject *pyDevice_new(Device &&ptr);
	
	/// Tellusim::Device::Features
	struct PYDeviceFeatures {
		PyObject_HEAD
		Device::Features ptr;
	};
	TS_PYAPI extern PyNumberMethods PYDeviceFeatures_number;
	TS_PYAPI extern PyBufferProcs PYDeviceFeatures_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYDeviceFeatures_methods;
	TS_PYAPI extern Array<PyMemberDef> PYDeviceFeatures_members;
	TS_PYAPI extern Array<PyGetSetDef> PYDeviceFeatures_getsets;
	TS_PYAPI extern PyTypeObject PYDeviceFeatures_Type;
	TS_PYAPI bool isPYDeviceFeatures(PyObject *object);
	TS_PYAPI Device::Features &pyDeviceFeatures_get(PyObject *object);
	TS_PYAPI PyObject *pyDeviceFeatures_new(const Device::Features &ptr);
	
	/// Tellusim::D3D12Device
	struct PYD3D12Device {
		PYDevice base;
		D3D12Device ptr;
	};
	TS_PYAPI extern PyTypeObject PYD3D12Device_Type;
	TS_PYAPI extern PyNumberMethods PYD3D12Device_number;
	TS_PYAPI extern PyBufferProcs PYD3D12Device_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYD3D12Device_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYD3D12Device_getsets;
	TS_PYAPI bool isPYD3D12Device(PyObject *object);
	TS_PYAPI D3D12Device &pyD3D12Device_get(PyObject *object);
	TS_PYAPI PyObject *pyD3D12Device_new(const D3D12Device &ptr);
	TS_PYAPI PyObject *pyD3D12Device_new(D3D12Device &&ptr);
	
	/// Tellusim::D3D11Device
	struct PYD3D11Device {
		PYDevice base;
		D3D11Device ptr;
	};
	TS_PYAPI extern PyTypeObject PYD3D11Device_Type;
	TS_PYAPI extern PyNumberMethods PYD3D11Device_number;
	TS_PYAPI extern PyBufferProcs PYD3D11Device_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYD3D11Device_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYD3D11Device_getsets;
	TS_PYAPI bool isPYD3D11Device(PyObject *object);
	TS_PYAPI D3D11Device &pyD3D11Device_get(PyObject *object);
	TS_PYAPI PyObject *pyD3D11Device_new(const D3D11Device &ptr);
	TS_PYAPI PyObject *pyD3D11Device_new(D3D11Device &&ptr);
	
	/// Tellusim::MTLDevice
	struct PYMTLDevice {
		PYDevice base;
		MTLDevice ptr;
	};
	TS_PYAPI extern PyTypeObject PYMTLDevice_Type;
	TS_PYAPI extern PyNumberMethods PYMTLDevice_number;
	TS_PYAPI extern PyBufferProcs PYMTLDevice_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMTLDevice_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMTLDevice_getsets;
	TS_PYAPI bool isPYMTLDevice(PyObject *object);
	TS_PYAPI MTLDevice &pyMTLDevice_get(PyObject *object);
	TS_PYAPI PyObject *pyMTLDevice_new(const MTLDevice &ptr);
	TS_PYAPI PyObject *pyMTLDevice_new(MTLDevice &&ptr);
	
	/// Tellusim::VKDevice
	struct PYVKDevice {
		PYDevice base;
		VKDevice ptr;
	};
	TS_PYAPI extern PyTypeObject PYVKDevice_Type;
	TS_PYAPI extern PyNumberMethods PYVKDevice_number;
	TS_PYAPI extern PyBufferProcs PYVKDevice_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYVKDevice_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYVKDevice_getsets;
	TS_PYAPI bool isPYVKDevice(PyObject *object);
	TS_PYAPI VKDevice &pyVKDevice_get(PyObject *object);
	TS_PYAPI PyObject *pyVKDevice_new(const VKDevice &ptr);
	TS_PYAPI PyObject *pyVKDevice_new(VKDevice &&ptr);
	
	/// Tellusim::FUDevice
	struct PYFUDevice {
		PYDevice base;
		FUDevice ptr;
	};
	TS_PYAPI extern PyTypeObject PYFUDevice_Type;
	TS_PYAPI extern PyNumberMethods PYFUDevice_number;
	TS_PYAPI extern PyBufferProcs PYFUDevice_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYFUDevice_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYFUDevice_getsets;
	TS_PYAPI bool isPYFUDevice(PyObject *object);
	TS_PYAPI FUDevice &pyFUDevice_get(PyObject *object);
	TS_PYAPI PyObject *pyFUDevice_new(const FUDevice &ptr);
	TS_PYAPI PyObject *pyFUDevice_new(FUDevice &&ptr);
	
	/// Tellusim::Kernel
	struct PYKernel {
		PyObject_HEAD
		Kernel ptr;
	};
	TS_PYAPI extern PyTypeObject PYKernel_Type;
	TS_PYAPI extern PyNumberMethods PYKernel_number;
	TS_PYAPI extern PyBufferProcs PYKernel_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYKernel_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYKernel_getsets;
	TS_PYAPI bool isPYKernel(PyObject *object);
	TS_PYAPI Kernel &pyKernel_get(PyObject *object);
	TS_PYAPI PyObject *pyKernel_new(const Kernel &ptr);
	TS_PYAPI PyObject *pyKernel_new(Kernel &&ptr);
	
	/// Tellusim::D3D12Kernel
	struct PYD3D12Kernel {
		PYKernel base;
		D3D12Kernel ptr;
	};
	TS_PYAPI extern PyTypeObject PYD3D12Kernel_Type;
	TS_PYAPI extern PyNumberMethods PYD3D12Kernel_number;
	TS_PYAPI extern PyBufferProcs PYD3D12Kernel_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYD3D12Kernel_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYD3D12Kernel_getsets;
	TS_PYAPI bool isPYD3D12Kernel(PyObject *object);
	TS_PYAPI D3D12Kernel &pyD3D12Kernel_get(PyObject *object);
	TS_PYAPI PyObject *pyD3D12Kernel_new(const D3D12Kernel &ptr);
	TS_PYAPI PyObject *pyD3D12Kernel_new(D3D12Kernel &&ptr);
	
	/// Tellusim::MTLKernel
	struct PYMTLKernel {
		PYKernel base;
		MTLKernel ptr;
	};
	TS_PYAPI extern PyTypeObject PYMTLKernel_Type;
	TS_PYAPI extern PyNumberMethods PYMTLKernel_number;
	TS_PYAPI extern PyBufferProcs PYMTLKernel_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMTLKernel_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMTLKernel_getsets;
	TS_PYAPI bool isPYMTLKernel(PyObject *object);
	TS_PYAPI MTLKernel &pyMTLKernel_get(PyObject *object);
	TS_PYAPI PyObject *pyMTLKernel_new(const MTLKernel &ptr);
	TS_PYAPI PyObject *pyMTLKernel_new(MTLKernel &&ptr);
	
	/// Tellusim::FUKernel
	struct PYFUKernel {
		PYKernel base;
		FUKernel ptr;
	};
	TS_PYAPI extern PyTypeObject PYFUKernel_Type;
	TS_PYAPI extern PyNumberMethods PYFUKernel_number;
	TS_PYAPI extern PyBufferProcs PYFUKernel_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYFUKernel_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYFUKernel_getsets;
	TS_PYAPI bool isPYFUKernel(PyObject *object);
	TS_PYAPI FUKernel &pyFUKernel_get(PyObject *object);
	TS_PYAPI PyObject *pyFUKernel_new(const FUKernel &ptr);
	TS_PYAPI PyObject *pyFUKernel_new(FUKernel &&ptr);
	
	/// Tellusim::Pipeline
	struct PYPipeline {
		PyObject_HEAD
		Pipeline ptr;
	};
	TS_PYAPI extern PyTypeObject PYPipeline_Type;
	TS_PYAPI extern PyNumberMethods PYPipeline_number;
	TS_PYAPI extern PyBufferProcs PYPipeline_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYPipeline_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYPipeline_getsets;
	TS_PYAPI bool isPYPipeline(PyObject *object);
	TS_PYAPI Pipeline &pyPipeline_get(PyObject *object);
	TS_PYAPI PyObject *pyPipeline_new(const Pipeline &ptr);
	TS_PYAPI PyObject *pyPipeline_new(Pipeline &&ptr);
	
	/// Tellusim::D3D12Pipeline
	struct PYD3D12Pipeline {
		PYPipeline base;
		D3D12Pipeline ptr;
	};
	TS_PYAPI extern PyTypeObject PYD3D12Pipeline_Type;
	TS_PYAPI extern PyNumberMethods PYD3D12Pipeline_number;
	TS_PYAPI extern PyBufferProcs PYD3D12Pipeline_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYD3D12Pipeline_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYD3D12Pipeline_getsets;
	TS_PYAPI bool isPYD3D12Pipeline(PyObject *object);
	TS_PYAPI D3D12Pipeline &pyD3D12Pipeline_get(PyObject *object);
	TS_PYAPI PyObject *pyD3D12Pipeline_new(const D3D12Pipeline &ptr);
	TS_PYAPI PyObject *pyD3D12Pipeline_new(D3D12Pipeline &&ptr);
	
	/// Tellusim::MTLPipeline
	struct PYMTLPipeline {
		PYPipeline base;
		MTLPipeline ptr;
	};
	TS_PYAPI extern PyTypeObject PYMTLPipeline_Type;
	TS_PYAPI extern PyNumberMethods PYMTLPipeline_number;
	TS_PYAPI extern PyBufferProcs PYMTLPipeline_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMTLPipeline_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMTLPipeline_getsets;
	TS_PYAPI bool isPYMTLPipeline(PyObject *object);
	TS_PYAPI MTLPipeline &pyMTLPipeline_get(PyObject *object);
	TS_PYAPI PyObject *pyMTLPipeline_new(const MTLPipeline &ptr);
	TS_PYAPI PyObject *pyMTLPipeline_new(MTLPipeline &&ptr);
	
	/// Tellusim::FUPipeline
	struct PYFUPipeline {
		PYPipeline base;
		FUPipeline ptr;
	};
	TS_PYAPI extern PyTypeObject PYFUPipeline_Type;
	TS_PYAPI extern PyNumberMethods PYFUPipeline_number;
	TS_PYAPI extern PyBufferProcs PYFUPipeline_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYFUPipeline_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYFUPipeline_getsets;
	TS_PYAPI bool isPYFUPipeline(PyObject *object);
	TS_PYAPI FUPipeline &pyFUPipeline_get(PyObject *object);
	TS_PYAPI PyObject *pyFUPipeline_new(const FUPipeline &ptr);
	TS_PYAPI PyObject *pyFUPipeline_new(FUPipeline &&ptr);
	
	/// Tellusim::Traversal
	struct PYTraversal {
		PyObject_HEAD
		Traversal ptr;
	};
	TS_PYAPI extern PyTypeObject PYTraversal_Type;
	TS_PYAPI extern PyNumberMethods PYTraversal_number;
	TS_PYAPI extern PyBufferProcs PYTraversal_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYTraversal_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYTraversal_getsets;
	TS_PYAPI bool isPYTraversal(PyObject *object);
	TS_PYAPI Traversal &pyTraversal_get(PyObject *object);
	TS_PYAPI PyObject *pyTraversal_new(const Traversal &ptr);
	TS_PYAPI PyObject *pyTraversal_new(Traversal &&ptr);
	
	/// Tellusim::D3D12Traversal
	struct PYD3D12Traversal {
		PYTraversal base;
		D3D12Traversal ptr;
	};
	TS_PYAPI extern PyTypeObject PYD3D12Traversal_Type;
	TS_PYAPI extern PyNumberMethods PYD3D12Traversal_number;
	TS_PYAPI extern PyBufferProcs PYD3D12Traversal_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYD3D12Traversal_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYD3D12Traversal_getsets;
	TS_PYAPI bool isPYD3D12Traversal(PyObject *object);
	TS_PYAPI D3D12Traversal &pyD3D12Traversal_get(PyObject *object);
	TS_PYAPI PyObject *pyD3D12Traversal_new(const D3D12Traversal &ptr);
	TS_PYAPI PyObject *pyD3D12Traversal_new(D3D12Traversal &&ptr);
	
	/// Tellusim::FUTraversal
	struct PYFUTraversal {
		PYTraversal base;
		FUTraversal ptr;
	};
	TS_PYAPI extern PyTypeObject PYFUTraversal_Type;
	TS_PYAPI extern PyNumberMethods PYFUTraversal_number;
	TS_PYAPI extern PyBufferProcs PYFUTraversal_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYFUTraversal_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYFUTraversal_getsets;
	TS_PYAPI bool isPYFUTraversal(PyObject *object);
	TS_PYAPI FUTraversal &pyFUTraversal_get(PyObject *object);
	TS_PYAPI PyObject *pyFUTraversal_new(const FUTraversal &ptr);
	TS_PYAPI PyObject *pyFUTraversal_new(FUTraversal &&ptr);
	
	/// Tellusim::Surface
	struct PYSurface {
		PyObject_HEAD
		Surface ptr;
	};
	TS_PYAPI extern PyTypeObject PYSurface_Type;
	TS_PYAPI extern PyNumberMethods PYSurface_number;
	TS_PYAPI extern PyBufferProcs PYSurface_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYSurface_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYSurface_getsets;
	TS_PYAPI bool isPYSurface(PyObject *object);
	TS_PYAPI Surface &pySurface_get(PyObject *object);
	TS_PYAPI PyObject *pySurface_new(const Surface &ptr);
	TS_PYAPI PyObject *pySurface_new(Surface &&ptr);
	
	/// Tellusim::D3D12Surface
	struct PYD3D12Surface {
		PYSurface base;
		D3D12Surface ptr;
	};
	TS_PYAPI extern PyTypeObject PYD3D12Surface_Type;
	TS_PYAPI extern PyNumberMethods PYD3D12Surface_number;
	TS_PYAPI extern PyBufferProcs PYD3D12Surface_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYD3D12Surface_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYD3D12Surface_getsets;
	TS_PYAPI bool isPYD3D12Surface(PyObject *object);
	TS_PYAPI D3D12Surface &pyD3D12Surface_get(PyObject *object);
	TS_PYAPI PyObject *pyD3D12Surface_new(const D3D12Surface &ptr);
	TS_PYAPI PyObject *pyD3D12Surface_new(D3D12Surface &&ptr);
	
	/// Tellusim::D3D11Surface
	struct PYD3D11Surface {
		PYSurface base;
		D3D11Surface ptr;
	};
	TS_PYAPI extern PyTypeObject PYD3D11Surface_Type;
	TS_PYAPI extern PyNumberMethods PYD3D11Surface_number;
	TS_PYAPI extern PyBufferProcs PYD3D11Surface_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYD3D11Surface_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYD3D11Surface_getsets;
	TS_PYAPI bool isPYD3D11Surface(PyObject *object);
	TS_PYAPI D3D11Surface &pyD3D11Surface_get(PyObject *object);
	TS_PYAPI PyObject *pyD3D11Surface_new(const D3D11Surface &ptr);
	TS_PYAPI PyObject *pyD3D11Surface_new(D3D11Surface &&ptr);
	
	/// Tellusim::MTLSurface
	struct PYMTLSurface {
		PYSurface base;
		MTLSurface ptr;
	};
	TS_PYAPI extern PyTypeObject PYMTLSurface_Type;
	TS_PYAPI extern PyNumberMethods PYMTLSurface_number;
	TS_PYAPI extern PyBufferProcs PYMTLSurface_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMTLSurface_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMTLSurface_getsets;
	TS_PYAPI bool isPYMTLSurface(PyObject *object);
	TS_PYAPI MTLSurface &pyMTLSurface_get(PyObject *object);
	TS_PYAPI PyObject *pyMTLSurface_new(const MTLSurface &ptr);
	TS_PYAPI PyObject *pyMTLSurface_new(MTLSurface &&ptr);
	
	/// Tellusim::VKSurface
	struct PYVKSurface {
		PYSurface base;
		VKSurface ptr;
	};
	TS_PYAPI extern PyTypeObject PYVKSurface_Type;
	TS_PYAPI extern PyNumberMethods PYVKSurface_number;
	TS_PYAPI extern PyBufferProcs PYVKSurface_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYVKSurface_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYVKSurface_getsets;
	TS_PYAPI bool isPYVKSurface(PyObject *object);
	TS_PYAPI VKSurface &pyVKSurface_get(PyObject *object);
	TS_PYAPI PyObject *pyVKSurface_new(const VKSurface &ptr);
	TS_PYAPI PyObject *pyVKSurface_new(VKSurface &&ptr);
	
	/// Tellusim::GLSurface
	struct PYGLSurface {
		PYSurface base;
		GLSurface ptr;
	};
	TS_PYAPI extern PyTypeObject PYGLSurface_Type;
	TS_PYAPI extern PyNumberMethods PYGLSurface_number;
	TS_PYAPI extern PyBufferProcs PYGLSurface_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYGLSurface_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYGLSurface_getsets;
	TS_PYAPI bool isPYGLSurface(PyObject *object);
	TS_PYAPI GLSurface &pyGLSurface_get(PyObject *object);
	TS_PYAPI PyObject *pyGLSurface_new(const GLSurface &ptr);
	TS_PYAPI PyObject *pyGLSurface_new(GLSurface &&ptr);
	
	/// Tellusim::GLESSurface
	struct PYGLESSurface {
		PYSurface base;
		GLESSurface ptr;
	};
	TS_PYAPI extern PyTypeObject PYGLESSurface_Type;
	TS_PYAPI extern PyNumberMethods PYGLESSurface_number;
	TS_PYAPI extern PyBufferProcs PYGLESSurface_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYGLESSurface_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYGLESSurface_getsets;
	TS_PYAPI bool isPYGLESSurface(PyObject *object);
	TS_PYAPI GLESSurface &pyGLESSurface_get(PyObject *object);
	TS_PYAPI PyObject *pyGLESSurface_new(const GLESSurface &ptr);
	TS_PYAPI PyObject *pyGLESSurface_new(GLESSurface &&ptr);
	
	/// Tellusim::Window
	struct PYWindow {
		PyObject_HEAD
		Window ptr;
	};
	TS_PYAPI extern PyTypeObject PYWindow_Type;
	TS_PYAPI extern PyNumberMethods PYWindow_number;
	TS_PYAPI extern PyBufferProcs PYWindow_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYWindow_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYWindow_getsets;
	TS_PYAPI bool isPYWindow(PyObject *object);
	TS_PYAPI Window &pyWindow_get(PyObject *object);
	TS_PYAPI PyObject *pyWindow_new(const Window &ptr);
	TS_PYAPI PyObject *pyWindow_new(Window &&ptr);
	
	/// Tellusim::Font
	struct PYFont {
		PyObject_HEAD
		Font ptr;
	};
	TS_PYAPI extern PyTypeObject PYFont_Type;
	TS_PYAPI extern PyNumberMethods PYFont_number;
	TS_PYAPI extern PyBufferProcs PYFont_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYFont_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYFont_getsets;
	TS_PYAPI bool isPYFont(PyObject *object);
	TS_PYAPI Font &pyFont_get(PyObject *object);
	TS_PYAPI PyObject *pyFont_new(const Font &ptr);
	TS_PYAPI PyObject *pyFont_new(Font &&ptr);
	
	/// Tellusim::CanvasElement
	struct PYCanvasElement {
		PyObject_HEAD
		CanvasElement ptr;
	};
	TS_PYAPI extern PyTypeObject PYCanvasElement_Type;
	TS_PYAPI extern PyNumberMethods PYCanvasElement_number;
	TS_PYAPI extern PyBufferProcs PYCanvasElement_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYCanvasElement_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYCanvasElement_getsets;
	TS_PYAPI bool isPYCanvasElement(PyObject *object);
	TS_PYAPI CanvasElement &pyCanvasElement_get(PyObject *object);
	TS_PYAPI PyObject *pyCanvasElement_new(const CanvasElement &ptr);
	TS_PYAPI PyObject *pyCanvasElement_new(CanvasElement &&ptr);
	
	/// Tellusim::CanvasText
	struct PYCanvasText {
		PYCanvasElement base;
		CanvasText ptr;
	};
	TS_PYAPI extern PyTypeObject PYCanvasText_Type;
	TS_PYAPI extern PyNumberMethods PYCanvasText_number;
	TS_PYAPI extern PyBufferProcs PYCanvasText_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYCanvasText_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYCanvasText_getsets;
	TS_PYAPI bool isPYCanvasText(PyObject *object);
	TS_PYAPI CanvasText &pyCanvasText_get(PyObject *object);
	TS_PYAPI PyObject *pyCanvasText_new(const CanvasText &ptr);
	TS_PYAPI PyObject *pyCanvasText_new(CanvasText &&ptr);
	
	/// Tellusim::CanvasMesh
	struct PYCanvasMesh {
		PYCanvasElement base;
		CanvasMesh ptr;
	};
	TS_PYAPI extern PyTypeObject PYCanvasMesh_Type;
	TS_PYAPI extern PyNumberMethods PYCanvasMesh_number;
	TS_PYAPI extern PyBufferProcs PYCanvasMesh_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYCanvasMesh_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYCanvasMesh_getsets;
	TS_PYAPI bool isPYCanvasMesh(PyObject *object);
	TS_PYAPI CanvasMesh &pyCanvasMesh_get(PyObject *object);
	TS_PYAPI PyObject *pyCanvasMesh_new(const CanvasMesh &ptr);
	TS_PYAPI PyObject *pyCanvasMesh_new(CanvasMesh &&ptr);
	
	/// Tellusim::CanvasRect
	struct PYCanvasRect {
		PYCanvasElement base;
		CanvasRect ptr;
	};
	TS_PYAPI extern PyTypeObject PYCanvasRect_Type;
	TS_PYAPI extern PyNumberMethods PYCanvasRect_number;
	TS_PYAPI extern PyBufferProcs PYCanvasRect_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYCanvasRect_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYCanvasRect_getsets;
	TS_PYAPI bool isPYCanvasRect(PyObject *object);
	TS_PYAPI CanvasRect &pyCanvasRect_get(PyObject *object);
	TS_PYAPI PyObject *pyCanvasRect_new(const CanvasRect &ptr);
	TS_PYAPI PyObject *pyCanvasRect_new(CanvasRect &&ptr);
	
	/// Tellusim::CanvasTriangle
	struct PYCanvasTriangle {
		PYCanvasElement base;
		CanvasTriangle ptr;
	};
	TS_PYAPI extern PyTypeObject PYCanvasTriangle_Type;
	TS_PYAPI extern PyNumberMethods PYCanvasTriangle_number;
	TS_PYAPI extern PyBufferProcs PYCanvasTriangle_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYCanvasTriangle_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYCanvasTriangle_getsets;
	TS_PYAPI bool isPYCanvasTriangle(PyObject *object);
	TS_PYAPI CanvasTriangle &pyCanvasTriangle_get(PyObject *object);
	TS_PYAPI PyObject *pyCanvasTriangle_new(const CanvasTriangle &ptr);
	TS_PYAPI PyObject *pyCanvasTriangle_new(CanvasTriangle &&ptr);
	
	/// Tellusim::CanvasEllipse
	struct PYCanvasEllipse {
		PYCanvasElement base;
		CanvasEllipse ptr;
	};
	TS_PYAPI extern PyTypeObject PYCanvasEllipse_Type;
	TS_PYAPI extern PyNumberMethods PYCanvasEllipse_number;
	TS_PYAPI extern PyBufferProcs PYCanvasEllipse_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYCanvasEllipse_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYCanvasEllipse_getsets;
	TS_PYAPI bool isPYCanvasEllipse(PyObject *object);
	TS_PYAPI CanvasEllipse &pyCanvasEllipse_get(PyObject *object);
	TS_PYAPI PyObject *pyCanvasEllipse_new(const CanvasEllipse &ptr);
	TS_PYAPI PyObject *pyCanvasEllipse_new(CanvasEllipse &&ptr);
	
	/// Tellusim::CanvasShape
	struct PYCanvasShape {
		PYCanvasElement base;
		CanvasShape ptr;
	};
	TS_PYAPI extern PyTypeObject PYCanvasShape_Type;
	TS_PYAPI extern PyNumberMethods PYCanvasShape_number;
	TS_PYAPI extern PyBufferProcs PYCanvasShape_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYCanvasShape_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYCanvasShape_getsets;
	TS_PYAPI bool isPYCanvasShape(PyObject *object);
	TS_PYAPI CanvasShape &pyCanvasShape_get(PyObject *object);
	TS_PYAPI PyObject *pyCanvasShape_new(const CanvasShape &ptr);
	TS_PYAPI PyObject *pyCanvasShape_new(CanvasShape &&ptr);
	
	/// Tellusim::CanvasStrip
	struct PYCanvasStrip {
		PYCanvasElement base;
		CanvasStrip ptr;
	};
	TS_PYAPI extern PyTypeObject PYCanvasStrip_Type;
	TS_PYAPI extern PyNumberMethods PYCanvasStrip_number;
	TS_PYAPI extern PyBufferProcs PYCanvasStrip_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYCanvasStrip_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYCanvasStrip_getsets;
	TS_PYAPI bool isPYCanvasStrip(PyObject *object);
	TS_PYAPI CanvasStrip &pyCanvasStrip_get(PyObject *object);
	TS_PYAPI PyObject *pyCanvasStrip_new(const CanvasStrip &ptr);
	TS_PYAPI PyObject *pyCanvasStrip_new(CanvasStrip &&ptr);
	
	/// Tellusim::Canvas
	struct PYCanvas {
		PyObject_HEAD
		Canvas ptr;
	};
	TS_PYAPI extern PyTypeObject PYCanvas_Type;
	TS_PYAPI extern PyNumberMethods PYCanvas_number;
	TS_PYAPI extern PyBufferProcs PYCanvas_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYCanvas_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYCanvas_getsets;
	TS_PYAPI bool isPYCanvas(PyObject *object);
	TS_PYAPI Canvas &pyCanvas_get(PyObject *object);
	TS_PYAPI PyObject *pyCanvas_new(const Canvas &ptr);
	TS_PYAPI PyObject *pyCanvas_new(Canvas &&ptr);
	
	/// Tellusim::Control
	struct PYControl {
		PyObject_HEAD
		Control ptr;
	};
	TS_PYAPI extern PyTypeObject PYControl_Type;
	TS_PYAPI extern PyNumberMethods PYControl_number;
	TS_PYAPI extern PyBufferProcs PYControl_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYControl_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYControl_getsets;
	TS_PYAPI bool isPYControl(PyObject *object);
	TS_PYAPI Control &pyControl_get(PyObject *object);
	TS_PYAPI PyObject *pyControl_new(const Control &ptr);
	TS_PYAPI PyObject *pyControl_new(Control &&ptr);
	
	/// Tellusim::ControlRoot
	struct PYControlRoot {
		PYControl base;
		ControlRoot ptr;
	};
	TS_PYAPI extern PyTypeObject PYControlRoot_Type;
	TS_PYAPI extern PyNumberMethods PYControlRoot_number;
	TS_PYAPI extern PyBufferProcs PYControlRoot_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYControlRoot_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYControlRoot_getsets;
	TS_PYAPI bool isPYControlRoot(PyObject *object);
	TS_PYAPI ControlRoot &pyControlRoot_get(PyObject *object);
	TS_PYAPI PyObject *pyControlRoot_new(const ControlRoot &ptr);
	TS_PYAPI PyObject *pyControlRoot_new(ControlRoot &&ptr);
	
	/// Tellusim::ControlText
	struct PYControlText {
		PYControl base;
		ControlText ptr;
	};
	TS_PYAPI extern PyTypeObject PYControlText_Type;
	TS_PYAPI extern PyNumberMethods PYControlText_number;
	TS_PYAPI extern PyBufferProcs PYControlText_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYControlText_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYControlText_getsets;
	TS_PYAPI bool isPYControlText(PyObject *object);
	TS_PYAPI ControlText &pyControlText_get(PyObject *object);
	TS_PYAPI PyObject *pyControlText_new(const ControlText &ptr);
	TS_PYAPI PyObject *pyControlText_new(ControlText &&ptr);
	
	/// Tellusim::ControlRect
	struct PYControlRect {
		PYControl base;
		ControlRect ptr;
	};
	TS_PYAPI extern PyTypeObject PYControlRect_Type;
	TS_PYAPI extern PyNumberMethods PYControlRect_number;
	TS_PYAPI extern PyBufferProcs PYControlRect_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYControlRect_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYControlRect_getsets;
	TS_PYAPI bool isPYControlRect(PyObject *object);
	TS_PYAPI ControlRect &pyControlRect_get(PyObject *object);
	TS_PYAPI PyObject *pyControlRect_new(const ControlRect &ptr);
	TS_PYAPI PyObject *pyControlRect_new(ControlRect &&ptr);
	
	/// Tellusim::ControlGrid
	struct PYControlGrid {
		PYControl base;
		ControlGrid ptr;
	};
	TS_PYAPI extern PyTypeObject PYControlGrid_Type;
	TS_PYAPI extern PyNumberMethods PYControlGrid_number;
	TS_PYAPI extern PyBufferProcs PYControlGrid_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYControlGrid_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYControlGrid_getsets;
	TS_PYAPI bool isPYControlGrid(PyObject *object);
	TS_PYAPI ControlGrid &pyControlGrid_get(PyObject *object);
	TS_PYAPI PyObject *pyControlGrid_new(const ControlGrid &ptr);
	TS_PYAPI PyObject *pyControlGrid_new(ControlGrid &&ptr);
	
	/// Tellusim::ControlGroup
	struct PYControlGroup {
		PYControlText base;
		ControlGroup ptr;
	};
	TS_PYAPI extern PyTypeObject PYControlGroup_Type;
	TS_PYAPI extern PyNumberMethods PYControlGroup_number;
	TS_PYAPI extern PyBufferProcs PYControlGroup_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYControlGroup_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYControlGroup_getsets;
	TS_PYAPI bool isPYControlGroup(PyObject *object);
	TS_PYAPI ControlGroup &pyControlGroup_get(PyObject *object);
	TS_PYAPI PyObject *pyControlGroup_new(const ControlGroup &ptr);
	TS_PYAPI PyObject *pyControlGroup_new(ControlGroup &&ptr);
	
	/// Tellusim::ControlPanel
	struct PYControlPanel {
		PYControlRect base;
		ControlPanel ptr;
	};
	TS_PYAPI extern PyTypeObject PYControlPanel_Type;
	TS_PYAPI extern PyNumberMethods PYControlPanel_number;
	TS_PYAPI extern PyBufferProcs PYControlPanel_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYControlPanel_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYControlPanel_getsets;
	TS_PYAPI bool isPYControlPanel(PyObject *object);
	TS_PYAPI ControlPanel &pyControlPanel_get(PyObject *object);
	TS_PYAPI PyObject *pyControlPanel_new(const ControlPanel &ptr);
	TS_PYAPI PyObject *pyControlPanel_new(ControlPanel &&ptr);
	
	/// Tellusim::ControlDialog
	struct PYControlDialog {
		PYControlPanel base;
		ControlDialog ptr;
	};
	TS_PYAPI extern PyTypeObject PYControlDialog_Type;
	TS_PYAPI extern PyNumberMethods PYControlDialog_number;
	TS_PYAPI extern PyBufferProcs PYControlDialog_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYControlDialog_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYControlDialog_getsets;
	TS_PYAPI bool isPYControlDialog(PyObject *object);
	TS_PYAPI ControlDialog &pyControlDialog_get(PyObject *object);
	TS_PYAPI PyObject *pyControlDialog_new(const ControlDialog &ptr);
	TS_PYAPI PyObject *pyControlDialog_new(ControlDialog &&ptr);
	
	/// Tellusim::ControlWindow
	struct PYControlWindow {
		PYControlDialog base;
		ControlWindow ptr;
	};
	TS_PYAPI extern PyTypeObject PYControlWindow_Type;
	TS_PYAPI extern PyNumberMethods PYControlWindow_number;
	TS_PYAPI extern PyBufferProcs PYControlWindow_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYControlWindow_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYControlWindow_getsets;
	TS_PYAPI bool isPYControlWindow(PyObject *object);
	TS_PYAPI ControlWindow &pyControlWindow_get(PyObject *object);
	TS_PYAPI PyObject *pyControlWindow_new(const ControlWindow &ptr);
	TS_PYAPI PyObject *pyControlWindow_new(ControlWindow &&ptr);
	
	/// Tellusim::ControlCheck
	struct PYControlCheck {
		PYControlText base;
		ControlCheck ptr;
	};
	TS_PYAPI extern PyTypeObject PYControlCheck_Type;
	TS_PYAPI extern PyNumberMethods PYControlCheck_number;
	TS_PYAPI extern PyBufferProcs PYControlCheck_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYControlCheck_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYControlCheck_getsets;
	TS_PYAPI bool isPYControlCheck(PyObject *object);
	TS_PYAPI ControlCheck &pyControlCheck_get(PyObject *object);
	TS_PYAPI PyObject *pyControlCheck_new(const ControlCheck &ptr);
	TS_PYAPI PyObject *pyControlCheck_new(ControlCheck &&ptr);
	
	/// Tellusim::ControlCombo
	struct PYControlCombo {
		PYControlText base;
		ControlCombo ptr;
	};
	TS_PYAPI extern PyTypeObject PYControlCombo_Type;
	TS_PYAPI extern PyNumberMethods PYControlCombo_number;
	TS_PYAPI extern PyBufferProcs PYControlCombo_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYControlCombo_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYControlCombo_getsets;
	TS_PYAPI bool isPYControlCombo(PyObject *object);
	TS_PYAPI ControlCombo &pyControlCombo_get(PyObject *object);
	TS_PYAPI PyObject *pyControlCombo_new(const ControlCombo &ptr);
	TS_PYAPI PyObject *pyControlCombo_new(ControlCombo &&ptr);
	
	/// Tellusim::ControlButton
	struct PYControlButton {
		PYControlText base;
		ControlButton ptr;
	};
	TS_PYAPI extern PyTypeObject PYControlButton_Type;
	TS_PYAPI extern PyNumberMethods PYControlButton_number;
	TS_PYAPI extern PyBufferProcs PYControlButton_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYControlButton_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYControlButton_getsets;
	TS_PYAPI bool isPYControlButton(PyObject *object);
	TS_PYAPI ControlButton &pyControlButton_get(PyObject *object);
	TS_PYAPI PyObject *pyControlButton_new(const ControlButton &ptr);
	TS_PYAPI PyObject *pyControlButton_new(ControlButton &&ptr);
	
	/// Tellusim::ControlSlider
	struct PYControlSlider {
		PYControlText base;
		ControlSlider ptr;
	};
	TS_PYAPI extern PyTypeObject PYControlSlider_Type;
	TS_PYAPI extern PyNumberMethods PYControlSlider_number;
	TS_PYAPI extern PyBufferProcs PYControlSlider_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYControlSlider_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYControlSlider_getsets;
	TS_PYAPI bool isPYControlSlider(PyObject *object);
	TS_PYAPI ControlSlider &pyControlSlider_get(PyObject *object);
	TS_PYAPI PyObject *pyControlSlider_new(const ControlSlider &ptr);
	TS_PYAPI PyObject *pyControlSlider_new(ControlSlider &&ptr);
	
	/// Tellusim::ControlScroll
	struct PYControlScroll {
		PYControlText base;
		ControlScroll ptr;
	};
	TS_PYAPI extern PyTypeObject PYControlScroll_Type;
	TS_PYAPI extern PyNumberMethods PYControlScroll_number;
	TS_PYAPI extern PyBufferProcs PYControlScroll_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYControlScroll_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYControlScroll_getsets;
	TS_PYAPI bool isPYControlScroll(PyObject *object);
	TS_PYAPI ControlScroll &pyControlScroll_get(PyObject *object);
	TS_PYAPI PyObject *pyControlScroll_new(const ControlScroll &ptr);
	TS_PYAPI PyObject *pyControlScroll_new(ControlScroll &&ptr);
	
	/// Tellusim::ControlSplit
	struct PYControlSplit {
		PYControl base;
		ControlSplit ptr;
	};
	TS_PYAPI extern PyTypeObject PYControlSplit_Type;
	TS_PYAPI extern PyNumberMethods PYControlSplit_number;
	TS_PYAPI extern PyBufferProcs PYControlSplit_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYControlSplit_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYControlSplit_getsets;
	TS_PYAPI bool isPYControlSplit(PyObject *object);
	TS_PYAPI ControlSplit &pyControlSplit_get(PyObject *object);
	TS_PYAPI PyObject *pyControlSplit_new(const ControlSplit &ptr);
	TS_PYAPI PyObject *pyControlSplit_new(ControlSplit &&ptr);
	
	/// Tellusim::ControlArea
	struct PYControlArea {
		PYControl base;
		ControlArea ptr;
	};
	TS_PYAPI extern PyTypeObject PYControlArea_Type;
	TS_PYAPI extern PyNumberMethods PYControlArea_number;
	TS_PYAPI extern PyBufferProcs PYControlArea_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYControlArea_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYControlArea_getsets;
	TS_PYAPI bool isPYControlArea(PyObject *object);
	TS_PYAPI ControlArea &pyControlArea_get(PyObject *object);
	TS_PYAPI PyObject *pyControlArea_new(const ControlArea &ptr);
	TS_PYAPI PyObject *pyControlArea_new(ControlArea &&ptr);
	
	/// Tellusim::ControlTree
	struct PYControlTree {
		PYControlText base;
		ControlTree ptr;
	};
	TS_PYAPI extern PyTypeObject PYControlTree_Type;
	TS_PYAPI extern PyNumberMethods PYControlTree_number;
	TS_PYAPI extern PyBufferProcs PYControlTree_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYControlTree_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYControlTree_getsets;
	TS_PYAPI bool isPYControlTree(PyObject *object);
	TS_PYAPI ControlTree &pyControlTree_get(PyObject *object);
	TS_PYAPI PyObject *pyControlTree_new(const ControlTree &ptr);
	TS_PYAPI PyObject *pyControlTree_new(ControlTree &&ptr);
	
	/// Tellusim::ControlEdit
	struct PYControlEdit {
		PYControlText base;
		ControlEdit ptr;
	};
	TS_PYAPI extern PyTypeObject PYControlEdit_Type;
	TS_PYAPI extern PyNumberMethods PYControlEdit_number;
	TS_PYAPI extern PyBufferProcs PYControlEdit_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYControlEdit_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYControlEdit_getsets;
	TS_PYAPI bool isPYControlEdit(PyObject *object);
	TS_PYAPI ControlEdit &pyControlEdit_get(PyObject *object);
	TS_PYAPI PyObject *pyControlEdit_new(const ControlEdit &ptr);
	TS_PYAPI PyObject *pyControlEdit_new(ControlEdit &&ptr);
	
	/// Tellusim::DialogMessage
	struct PYDialogMessage {
		PyObject_HEAD
		DialogMessage ptr;
	};
	TS_PYAPI extern PyTypeObject PYDialogMessage_Type;
	TS_PYAPI extern PyNumberMethods PYDialogMessage_number;
	TS_PYAPI extern PyBufferProcs PYDialogMessage_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYDialogMessage_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYDialogMessage_getsets;
	TS_PYAPI bool isPYDialogMessage(PyObject *object);
	TS_PYAPI DialogMessage &pyDialogMessage_get(PyObject *object);
	TS_PYAPI PyObject *pyDialogMessage_new(const DialogMessage &ptr);
	TS_PYAPI PyObject *pyDialogMessage_new(DialogMessage &&ptr);
	
	/// Tellusim::DialogFileOpen
	struct PYDialogFileOpen {
		PyObject_HEAD
		DialogFileOpen ptr;
	};
	TS_PYAPI extern PyTypeObject PYDialogFileOpen_Type;
	TS_PYAPI extern PyNumberMethods PYDialogFileOpen_number;
	TS_PYAPI extern PyBufferProcs PYDialogFileOpen_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYDialogFileOpen_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYDialogFileOpen_getsets;
	TS_PYAPI bool isPYDialogFileOpen(PyObject *object);
	TS_PYAPI DialogFileOpen &pyDialogFileOpen_get(PyObject *object);
	TS_PYAPI PyObject *pyDialogFileOpen_new(const DialogFileOpen &ptr);
	TS_PYAPI PyObject *pyDialogFileOpen_new(DialogFileOpen &&ptr);
	
	/// Tellusim::DialogFileSave
	struct PYDialogFileSave {
		PyObject_HEAD
		DialogFileSave ptr;
	};
	TS_PYAPI extern PyTypeObject PYDialogFileSave_Type;
	TS_PYAPI extern PyNumberMethods PYDialogFileSave_number;
	TS_PYAPI extern PyBufferProcs PYDialogFileSave_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYDialogFileSave_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYDialogFileSave_getsets;
	TS_PYAPI bool isPYDialogFileSave(PyObject *object);
	TS_PYAPI DialogFileSave &pyDialogFileSave_get(PyObject *object);
	TS_PYAPI PyObject *pyDialogFileSave_new(const DialogFileSave &ptr);
	TS_PYAPI PyObject *pyDialogFileSave_new(DialogFileSave &&ptr);
	
	/// Tellusim::DialogDirectory
	struct PYDialogDirectory {
		PyObject_HEAD
		DialogDirectory ptr;
	};
	TS_PYAPI extern PyTypeObject PYDialogDirectory_Type;
	TS_PYAPI extern PyNumberMethods PYDialogDirectory_number;
	TS_PYAPI extern PyBufferProcs PYDialogDirectory_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYDialogDirectory_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYDialogDirectory_getsets;
	TS_PYAPI bool isPYDialogDirectory(PyObject *object);
	TS_PYAPI DialogDirectory &pyDialogDirectory_get(PyObject *object);
	TS_PYAPI PyObject *pyDialogDirectory_new(const DialogDirectory &ptr);
	TS_PYAPI PyObject *pyDialogDirectory_new(DialogDirectory &&ptr);
	
	/// Tellusim::DialogProgress
	struct PYDialogProgress {
		PyObject_HEAD
		DialogProgress ptr;
	};
	TS_PYAPI extern PyTypeObject PYDialogProgress_Type;
	TS_PYAPI extern PyNumberMethods PYDialogProgress_number;
	TS_PYAPI extern PyBufferProcs PYDialogProgress_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYDialogProgress_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYDialogProgress_getsets;
	TS_PYAPI bool isPYDialogProgress(PyObject *object);
	TS_PYAPI DialogProgress &pyDialogProgress_get(PyObject *object);
	TS_PYAPI PyObject *pyDialogProgress_new(const DialogProgress &ptr);
	TS_PYAPI PyObject *pyDialogProgress_new(DialogProgress &&ptr);
	
	/// Tellusim::DialogColor
	struct PYDialogColor {
		PyObject_HEAD
		DialogColor ptr;
	};
	TS_PYAPI extern PyTypeObject PYDialogColor_Type;
	TS_PYAPI extern PyNumberMethods PYDialogColor_number;
	TS_PYAPI extern PyBufferProcs PYDialogColor_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYDialogColor_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYDialogColor_getsets;
	TS_PYAPI bool isPYDialogColor(PyObject *object);
	TS_PYAPI DialogColor &pyDialogColor_get(PyObject *object);
	TS_PYAPI PyObject *pyDialogColor_new(const DialogColor &ptr);
	TS_PYAPI PyObject *pyDialogColor_new(DialogColor &&ptr);
	
	/// Tellusim::DialogMenu
	struct PYDialogMenu {
		PyObject_HEAD
		DialogMenu ptr;
	};
	TS_PYAPI extern PyTypeObject PYDialogMenu_Type;
	TS_PYAPI extern PyNumberMethods PYDialogMenu_number;
	TS_PYAPI extern PyBufferProcs PYDialogMenu_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYDialogMenu_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYDialogMenu_getsets;
	TS_PYAPI bool isPYDialogMenu(PyObject *object);
	TS_PYAPI DialogMenu &pyDialogMenu_get(PyObject *object);
	TS_PYAPI PyObject *pyDialogMenu_new(const DialogMenu &ptr);
	TS_PYAPI PyObject *pyDialogMenu_new(DialogMenu &&ptr);
	
	/// Tellusim::CubeFilter
	struct PYCubeFilter {
		PyObject_HEAD
		CubeFilter ptr;
	};
	TS_PYAPI extern PyTypeObject PYCubeFilter_Type;
	TS_PYAPI extern PyNumberMethods PYCubeFilter_number;
	TS_PYAPI extern PyBufferProcs PYCubeFilter_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYCubeFilter_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYCubeFilter_getsets;
	TS_PYAPI bool isPYCubeFilter(PyObject *object);
	TS_PYAPI CubeFilter &pyCubeFilter_get(PyObject *object);
	TS_PYAPI PyObject *pyCubeFilter_new(const CubeFilter &ptr);
	TS_PYAPI PyObject *pyCubeFilter_new(CubeFilter &&ptr);
	
	/// Tellusim::DecoderJPEG
	struct PYDecoderJPEG {
		PyObject_HEAD
		DecoderJPEG ptr;
	};
	TS_PYAPI extern PyTypeObject PYDecoderJPEG_Type;
	TS_PYAPI extern PyNumberMethods PYDecoderJPEG_number;
	TS_PYAPI extern PyBufferProcs PYDecoderJPEG_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYDecoderJPEG_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYDecoderJPEG_getsets;
	TS_PYAPI bool isPYDecoderJPEG(PyObject *object);
	TS_PYAPI DecoderJPEG &pyDecoderJPEG_get(PyObject *object);
	TS_PYAPI PyObject *pyDecoderJPEG_new(const DecoderJPEG &ptr);
	TS_PYAPI PyObject *pyDecoderJPEG_new(DecoderJPEG &&ptr);
	
	/// Tellusim::EncoderBC15
	struct PYEncoderBC15 {
		PyObject_HEAD
		EncoderBC15 ptr;
	};
	TS_PYAPI extern PyTypeObject PYEncoderBC15_Type;
	TS_PYAPI extern PyNumberMethods PYEncoderBC15_number;
	TS_PYAPI extern PyBufferProcs PYEncoderBC15_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYEncoderBC15_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYEncoderBC15_getsets;
	TS_PYAPI bool isPYEncoderBC15(PyObject *object);
	TS_PYAPI EncoderBC15 &pyEncoderBC15_get(PyObject *object);
	TS_PYAPI PyObject *pyEncoderBC15_new(const EncoderBC15 &ptr);
	TS_PYAPI PyObject *pyEncoderBC15_new(EncoderBC15 &&ptr);
	
	/// Tellusim::EncoderBC67
	struct PYEncoderBC67 {
		PyObject_HEAD
		EncoderBC67 ptr;
	};
	TS_PYAPI extern PyTypeObject PYEncoderBC67_Type;
	TS_PYAPI extern PyNumberMethods PYEncoderBC67_number;
	TS_PYAPI extern PyBufferProcs PYEncoderBC67_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYEncoderBC67_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYEncoderBC67_getsets;
	TS_PYAPI bool isPYEncoderBC67(PyObject *object);
	TS_PYAPI EncoderBC67 &pyEncoderBC67_get(PyObject *object);
	TS_PYAPI PyObject *pyEncoderBC67_new(const EncoderBC67 &ptr);
	TS_PYAPI PyObject *pyEncoderBC67_new(EncoderBC67 &&ptr);
	
	/// Tellusim::EncoderASTC
	struct PYEncoderASTC {
		PyObject_HEAD
		EncoderASTC ptr;
	};
	TS_PYAPI extern PyTypeObject PYEncoderASTC_Type;
	TS_PYAPI extern PyNumberMethods PYEncoderASTC_number;
	TS_PYAPI extern PyBufferProcs PYEncoderASTC_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYEncoderASTC_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYEncoderASTC_getsets;
	TS_PYAPI bool isPYEncoderASTC(PyObject *object);
	TS_PYAPI EncoderASTC &pyEncoderASTC_get(PyObject *object);
	TS_PYAPI PyObject *pyEncoderASTC_new(const EncoderASTC &ptr);
	TS_PYAPI PyObject *pyEncoderASTC_new(EncoderASTC &&ptr);
	
	/// Tellusim::MeshModel
	struct PYMeshModel {
		PyObject_HEAD
		MeshModel ptr;
	};
	TS_PYAPI extern PyTypeObject PYMeshModel_Type;
	TS_PYAPI extern PyNumberMethods PYMeshModel_number;
	TS_PYAPI extern PyBufferProcs PYMeshModel_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMeshModel_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYMeshModel_getsets;
	TS_PYAPI bool isPYMeshModel(PyObject *object);
	TS_PYAPI MeshModel &pyMeshModel_get(PyObject *object);
	
	/// Tellusim::MeshModel::Meshlet
	struct PYMeshModelMeshlet {
		PyObject_HEAD
		MeshModel::Meshlet ptr;
	};
	TS_PYAPI extern PyNumberMethods PYMeshModelMeshlet_number;
	TS_PYAPI extern PyBufferProcs PYMeshModelMeshlet_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYMeshModelMeshlet_methods;
	TS_PYAPI extern Array<PyMemberDef> PYMeshModelMeshlet_members;
	TS_PYAPI extern Array<PyGetSetDef> PYMeshModelMeshlet_getsets;
	TS_PYAPI extern PyTypeObject PYMeshModelMeshlet_Type;
	TS_PYAPI bool isPYMeshModelMeshlet(PyObject *object);
	TS_PYAPI MeshModel::Meshlet &pyMeshModelMeshlet_get(PyObject *object);
	TS_PYAPI PyObject *pyMeshModelMeshlet_new(const MeshModel::Meshlet &ptr);
	
	/// Tellusim::SeparableFilter
	struct PYSeparableFilter {
		PyObject_HEAD
		SeparableFilter ptr;
	};
	TS_PYAPI extern PyTypeObject PYSeparableFilter_Type;
	TS_PYAPI extern PyNumberMethods PYSeparableFilter_number;
	TS_PYAPI extern PyBufferProcs PYSeparableFilter_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYSeparableFilter_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYSeparableFilter_getsets;
	TS_PYAPI bool isPYSeparableFilter(PyObject *object);
	TS_PYAPI SeparableFilter &pySeparableFilter_get(PyObject *object);
	TS_PYAPI PyObject *pySeparableFilter_new(const SeparableFilter &ptr);
	TS_PYAPI PyObject *pySeparableFilter_new(SeparableFilter &&ptr);
	
	/// Tellusim::PrefixScan
	struct PYPrefixScan {
		PyObject_HEAD
		PrefixScan ptr;
	};
	TS_PYAPI extern PyTypeObject PYPrefixScan_Type;
	TS_PYAPI extern PyNumberMethods PYPrefixScan_number;
	TS_PYAPI extern PyBufferProcs PYPrefixScan_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYPrefixScan_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYPrefixScan_getsets;
	TS_PYAPI bool isPYPrefixScan(PyObject *object);
	TS_PYAPI PrefixScan &pyPrefixScan_get(PyObject *object);
	TS_PYAPI PyObject *pyPrefixScan_new(const PrefixScan &ptr);
	TS_PYAPI PyObject *pyPrefixScan_new(PrefixScan &&ptr);
	
	/// Tellusim::PrefixScan::DispatchParameters
	struct PYPrefixScanDispatchParameters {
		PyObject_HEAD
		PrefixScan::DispatchParameters ptr;
	};
	TS_PYAPI extern PyNumberMethods PYPrefixScanDispatchParameters_number;
	TS_PYAPI extern PyBufferProcs PYPrefixScanDispatchParameters_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYPrefixScanDispatchParameters_methods;
	TS_PYAPI extern Array<PyMemberDef> PYPrefixScanDispatchParameters_members;
	TS_PYAPI extern Array<PyGetSetDef> PYPrefixScanDispatchParameters_getsets;
	TS_PYAPI extern PyTypeObject PYPrefixScanDispatchParameters_Type;
	TS_PYAPI bool isPYPrefixScanDispatchParameters(PyObject *object);
	TS_PYAPI PrefixScan::DispatchParameters &pyPrefixScanDispatchParameters_get(PyObject *object);
	TS_PYAPI PyObject *pyPrefixScanDispatchParameters_new(const PrefixScan::DispatchParameters &ptr);
	
	/// Tellusim::RadixSort
	struct PYRadixSort {
		PyObject_HEAD
		RadixSort ptr;
	};
	TS_PYAPI extern PyTypeObject PYRadixSort_Type;
	TS_PYAPI extern PyNumberMethods PYRadixSort_number;
	TS_PYAPI extern PyBufferProcs PYRadixSort_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYRadixSort_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYRadixSort_getsets;
	TS_PYAPI bool isPYRadixSort(PyObject *object);
	TS_PYAPI RadixSort &pyRadixSort_get(PyObject *object);
	TS_PYAPI PyObject *pyRadixSort_new(const RadixSort &ptr);
	TS_PYAPI PyObject *pyRadixSort_new(RadixSort &&ptr);
	
	/// Tellusim::RadixSort::DispatchParameters
	struct PYRadixSortDispatchParameters {
		PyObject_HEAD
		RadixSort::DispatchParameters ptr;
	};
	TS_PYAPI extern PyNumberMethods PYRadixSortDispatchParameters_number;
	TS_PYAPI extern PyBufferProcs PYRadixSortDispatchParameters_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYRadixSortDispatchParameters_methods;
	TS_PYAPI extern Array<PyMemberDef> PYRadixSortDispatchParameters_members;
	TS_PYAPI extern Array<PyGetSetDef> PYRadixSortDispatchParameters_getsets;
	TS_PYAPI extern PyTypeObject PYRadixSortDispatchParameters_Type;
	TS_PYAPI bool isPYRadixSortDispatchParameters(PyObject *object);
	TS_PYAPI RadixSort::DispatchParameters &pyRadixSortDispatchParameters_get(PyObject *object);
	TS_PYAPI PyObject *pyRadixSortDispatchParameters_new(const RadixSort::DispatchParameters &ptr);
	
	/// Tellusim::BitonicSort
	struct PYBitonicSort {
		PyObject_HEAD
		BitonicSort ptr;
	};
	TS_PYAPI extern PyTypeObject PYBitonicSort_Type;
	TS_PYAPI extern PyNumberMethods PYBitonicSort_number;
	TS_PYAPI extern PyBufferProcs PYBitonicSort_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYBitonicSort_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYBitonicSort_getsets;
	TS_PYAPI bool isPYBitonicSort(PyObject *object);
	TS_PYAPI BitonicSort &pyBitonicSort_get(PyObject *object);
	TS_PYAPI PyObject *pyBitonicSort_new(const BitonicSort &ptr);
	TS_PYAPI PyObject *pyBitonicSort_new(BitonicSort &&ptr);
	
	/// Tellusim::BitonicSort::DispatchParameters
	struct PYBitonicSortDispatchParameters {
		PyObject_HEAD
		BitonicSort::DispatchParameters ptr;
	};
	TS_PYAPI extern PyNumberMethods PYBitonicSortDispatchParameters_number;
	TS_PYAPI extern PyBufferProcs PYBitonicSortDispatchParameters_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYBitonicSortDispatchParameters_methods;
	TS_PYAPI extern Array<PyMemberDef> PYBitonicSortDispatchParameters_members;
	TS_PYAPI extern Array<PyGetSetDef> PYBitonicSortDispatchParameters_getsets;
	TS_PYAPI extern PyTypeObject PYBitonicSortDispatchParameters_Type;
	TS_PYAPI bool isPYBitonicSortDispatchParameters(PyObject *object);
	TS_PYAPI BitonicSort::DispatchParameters &pyBitonicSortDispatchParameters_get(PyObject *object);
	TS_PYAPI PyObject *pyBitonicSortDispatchParameters_new(const BitonicSort::DispatchParameters &ptr);
	
	/// Tellusim::SpatialGrid
	struct PYSpatialGrid {
		PyObject_HEAD
		SpatialGrid ptr;
	};
	TS_PYAPI extern PyTypeObject PYSpatialGrid_Type;
	TS_PYAPI extern PyNumberMethods PYSpatialGrid_number;
	TS_PYAPI extern PyBufferProcs PYSpatialGrid_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYSpatialGrid_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYSpatialGrid_getsets;
	TS_PYAPI bool isPYSpatialGrid(PyObject *object);
	TS_PYAPI SpatialGrid &pySpatialGrid_get(PyObject *object);
	TS_PYAPI PyObject *pySpatialGrid_new(const SpatialGrid &ptr);
	TS_PYAPI PyObject *pySpatialGrid_new(SpatialGrid &&ptr);
	
	/// Tellusim::SpatialGrid::DispatchParameters
	struct PYSpatialGridDispatchParameters {
		PyObject_HEAD
		SpatialGrid::DispatchParameters ptr;
	};
	TS_PYAPI extern PyNumberMethods PYSpatialGridDispatchParameters_number;
	TS_PYAPI extern PyBufferProcs PYSpatialGridDispatchParameters_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYSpatialGridDispatchParameters_methods;
	TS_PYAPI extern Array<PyMemberDef> PYSpatialGridDispatchParameters_members;
	TS_PYAPI extern Array<PyGetSetDef> PYSpatialGridDispatchParameters_getsets;
	TS_PYAPI extern PyTypeObject PYSpatialGridDispatchParameters_Type;
	TS_PYAPI bool isPYSpatialGridDispatchParameters(PyObject *object);
	TS_PYAPI SpatialGrid::DispatchParameters &pySpatialGridDispatchParameters_get(PyObject *object);
	TS_PYAPI PyObject *pySpatialGridDispatchParameters_new(const SpatialGrid::DispatchParameters &ptr);
	
	/// Tellusim::SpatialTree
	struct PYSpatialTree {
		PyObject_HEAD
		SpatialTree ptr;
	};
	TS_PYAPI extern PyTypeObject PYSpatialTree_Type;
	TS_PYAPI extern PyNumberMethods PYSpatialTree_number;
	TS_PYAPI extern PyBufferProcs PYSpatialTree_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYSpatialTree_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYSpatialTree_getsets;
	TS_PYAPI bool isPYSpatialTree(PyObject *object);
	TS_PYAPI SpatialTree &pySpatialTree_get(PyObject *object);
	TS_PYAPI PyObject *pySpatialTree_new(const SpatialTree &ptr);
	TS_PYAPI PyObject *pySpatialTree_new(SpatialTree &&ptr);
	
	/// Tellusim::SpatialTree::Node
	struct PYSpatialTreeNode {
		PyObject_HEAD
		SpatialTree::Node ptr;
	};
	TS_PYAPI extern PyNumberMethods PYSpatialTreeNode_number;
	TS_PYAPI extern PyBufferProcs PYSpatialTreeNode_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYSpatialTreeNode_methods;
	TS_PYAPI extern Array<PyMemberDef> PYSpatialTreeNode_members;
	TS_PYAPI extern Array<PyGetSetDef> PYSpatialTreeNode_getsets;
	TS_PYAPI extern PyTypeObject PYSpatialTreeNode_Type;
	TS_PYAPI bool isPYSpatialTreeNode(PyObject *object);
	TS_PYAPI SpatialTree::Node &pySpatialTreeNode_get(PyObject *object);
	TS_PYAPI PyObject *pySpatialTreeNode_new(const SpatialTree::Node &ptr);
	
	/// Tellusim::SpatialTree::DispatchParameters
	struct PYSpatialTreeDispatchParameters {
		PyObject_HEAD
		SpatialTree::DispatchParameters ptr;
	};
	TS_PYAPI extern PyNumberMethods PYSpatialTreeDispatchParameters_number;
	TS_PYAPI extern PyBufferProcs PYSpatialTreeDispatchParameters_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYSpatialTreeDispatchParameters_methods;
	TS_PYAPI extern Array<PyMemberDef> PYSpatialTreeDispatchParameters_members;
	TS_PYAPI extern Array<PyGetSetDef> PYSpatialTreeDispatchParameters_getsets;
	TS_PYAPI extern PyTypeObject PYSpatialTreeDispatchParameters_Type;
	TS_PYAPI bool isPYSpatialTreeDispatchParameters(PyObject *object);
	TS_PYAPI SpatialTree::DispatchParameters &pySpatialTreeDispatchParameters_get(PyObject *object);
	TS_PYAPI PyObject *pySpatialTreeDispatchParameters_new(const SpatialTree::DispatchParameters &ptr);
	
	/// Tellusim::FourierTransform
	struct PYFourierTransform {
		PyObject_HEAD
		FourierTransform ptr;
	};
	TS_PYAPI extern PyTypeObject PYFourierTransform_Type;
	TS_PYAPI extern PyNumberMethods PYFourierTransform_number;
	TS_PYAPI extern PyBufferProcs PYFourierTransform_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYFourierTransform_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYFourierTransform_getsets;
	TS_PYAPI bool isPYFourierTransform(PyObject *object);
	TS_PYAPI FourierTransform &pyFourierTransform_get(PyObject *object);
	TS_PYAPI PyObject *pyFourierTransform_new(const FourierTransform &ptr);
	TS_PYAPI PyObject *pyFourierTransform_new(FourierTransform &&ptr);
	
	/// Tellusim::TensorGraph
	struct PYTensorGraph {
		PyObject_HEAD
		TensorGraph ptr;
	};
	TS_PYAPI extern PyTypeObject PYTensorGraph_Type;
	TS_PYAPI extern PyNumberMethods PYTensorGraph_number;
	TS_PYAPI extern PyBufferProcs PYTensorGraph_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYTensorGraph_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYTensorGraph_getsets;
	TS_PYAPI bool isPYTensorGraph(PyObject *object);
	TS_PYAPI TensorGraph &pyTensorGraph_get(PyObject *object);
	TS_PYAPI PyObject *pyTensorGraph_new(const TensorGraph &ptr);
	TS_PYAPI PyObject *pyTensorGraph_new(TensorGraph &&ptr);
	
	/// Tellusim::Controller
	struct PYController {
		PyObject_HEAD
		Controller ptr;
	};
	TS_PYAPI extern PyTypeObject PYController_Type;
	TS_PYAPI extern PyNumberMethods PYController_number;
	TS_PYAPI extern PyBufferProcs PYController_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYController_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYController_getsets;
	TS_PYAPI bool isPYController(PyObject *object);
	TS_PYAPI Controller &pyController_get(PyObject *object);
	TS_PYAPI PyObject *pyController_new(const Controller &ptr);
	TS_PYAPI PyObject *pyController_new(Controller &&ptr);
	
	/// Tellusim::Desktop
	struct PYDesktop {
		PyObject_HEAD
		Desktop ptr;
	};
	TS_PYAPI extern PyTypeObject PYDesktop_Type;
	TS_PYAPI extern PyNumberMethods PYDesktop_number;
	TS_PYAPI extern PyBufferProcs PYDesktop_buffer;
	TS_PYAPI extern Array<PyMethodDef> PYDesktop_methods;
	TS_PYAPI extern Array<PyGetSetDef> PYDesktop_getsets;
	TS_PYAPI bool isPYDesktop(PyObject *object);
	TS_PYAPI Desktop &pyDesktop_get(PyObject *object);
	TS_PYAPI PyObject *pyDesktop_new(const Desktop &ptr);
	TS_PYAPI PyObject *pyDesktop_new(Desktop &&ptr);
	
	/// Tellusim::Allocator
	struct PYAllocator {
		PyObject_HEAD
	};
	TS_PYAPI extern PyTypeObject PYAllocator_Type;
	TS_PYAPI extern Array<PyMethodDef> PYAllocator_methods;
	
	/// Tellusim::Log
	struct PYLog {
		PyObject_HEAD
	};
	TS_PYAPI extern PyTypeObject PYLog_Type;
	TS_PYAPI extern Array<PyMethodDef> PYLog_methods;
	
	/// Tellusim::Time
	struct PYTime {
		PyObject_HEAD
	};
	TS_PYAPI extern PyTypeObject PYTime_Type;
	TS_PYAPI extern Array<PyMethodDef> PYTime_methods;
	
	/// Tellusim::System
	struct PYSystem {
		PyObject_HEAD
	};
	TS_PYAPI extern PyTypeObject PYSystem_Type;
	TS_PYAPI extern Array<PyMethodDef> PYSystem_methods;
	
	/// Tellusim::MeshGraph
	struct PYMeshGraph {
		PyObject_HEAD
	};
	TS_PYAPI extern PyTypeObject PYMeshGraph_Type;
	TS_PYAPI extern Array<PyMethodDef> PYMeshGraph_methods;
	
	/// Tellusim::MeshReduce
	struct PYMeshReduce {
		PyObject_HEAD
	};
	TS_PYAPI extern PyTypeObject PYMeshReduce_Type;
	TS_PYAPI extern Array<PyMethodDef> PYMeshReduce_methods;
	
	/// Tellusim::MeshRefine
	struct PYMeshRefine {
		PyObject_HEAD
	};
	TS_PYAPI extern PyTypeObject PYMeshRefine_Type;
	TS_PYAPI extern Array<PyMethodDef> PYMeshRefine_methods;
	
	/// Tellusim::MeshSolid
	struct PYMeshSolid {
		PyObject_HEAD
	};
	TS_PYAPI extern PyTypeObject PYMeshSolid_Type;
	TS_PYAPI extern Array<PyMethodDef> PYMeshSolid_methods;
	
	/// Tellusim API
	bool pyInitAPI(Tellusim::Array<PyMethodDef> &methods);
	bool pyCreateAPI(PyObject *module);
}

#endif /* __TELLUSIM_PY_API_H__ */

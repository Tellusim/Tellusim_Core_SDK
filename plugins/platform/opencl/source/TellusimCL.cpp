// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <TellusimBase.h>

#if _LINUX
	#include <dlfcn.h>
#endif

#include <core/TellusimLog.h>
#include <core/TellusimArray.h>
#include <core/TellusimSystem.h>
#include <core/TellusimAtomic.h>
#include <core/TellusimString.h>

#include "../include/TellusimCL.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	namespace CL {
		
		Atomici32 counter = 0;				// reference counter
		
		void *handle = nullptr;				// library handle
		
		cl_platform_id platform = nullptr;	// current platform
		
		String platform_name;				// platform name
		String platform_vendor;				// platform vendor
		String platform_version;			// platform version
		String platform_extensions;			// platform extensions
		
		Array<CLDevice*> devices;			// platform devices
		
		/*
		 */
		bool retain() {
			counter++;
			return !isOpened();
		}
		
		bool release() {
			TS_ASSERT(counter > 0 && "CL::release(): reference counter is zero");
			return (--counter == 0);
		}
		
		/*
		 */
		bool isOpened() {
			return (handle != nullptr);
		}
		
		/*
		 */
		bool open() {
			
			TS_ASSERT(!isOpened() && "CL::open(): is already opened");
			
			// load library
			const char *library_name = nullptr;
			#if _WIN32
				library_name = "opencl.dll";
			#elif _LINUX || _ANDROID
				library_name = "libOpenCL.so";
			#elif _MACOS
				library_name = "/System/Library/Frameworks/OpenCL.framework/OpenCL";
			#else
				TS_LOG(Error, "CL::open(): unknown platform\n");
				close();
				return false;
			#endif
			handle = System::loadLibrary(library_name);
			if(handle == nullptr) {
				TS_LOGEF(Error, "CL::open(): can't load %s library\n", library_name);
				close();
				return false;
			}
			
			#define GET_ADDRESS(NAME) { \
				void *address = System::getFunction(handle, #NAME); \
				if(address == nullptr) TS_LOGF(Error, "CL::open(): can't find \"%s\" function\n", #NAME); \
				if(address == nullptr) { close(); return false; } \
				NAME = (PFN_ ## NAME)address; \
			}
			
			// OpenCL functions
			GET_ADDRESS(clGetPlatformIDs)
			GET_ADDRESS(clGetPlatformInfo)
			GET_ADDRESS(clGetDeviceIDs)
			GET_ADDRESS(clGetDeviceInfo)
			GET_ADDRESS(clCreateSubDevices)
			GET_ADDRESS(clRetainDevice)
			GET_ADDRESS(clReleaseDevice)
			GET_ADDRESS(clSetDefaultDeviceCommandQueue)
			GET_ADDRESS(clGetDeviceAndHostTimer)
			GET_ADDRESS(clGetHostTimer)
			GET_ADDRESS(clCreateContext)
			GET_ADDRESS(clCreateContextFromType)
			GET_ADDRESS(clRetainContext)
			GET_ADDRESS(clReleaseContext)
			GET_ADDRESS(clGetContextInfo)
			GET_ADDRESS(clSetContextDestructorCallback)
			GET_ADDRESS(clCreateCommandQueueWithProperties)
			GET_ADDRESS(clRetainCommandQueue)
			GET_ADDRESS(clReleaseCommandQueue)
			GET_ADDRESS(clGetCommandQueueInfo)
			GET_ADDRESS(clCreateBuffer)
			GET_ADDRESS(clCreateSubBuffer)
			GET_ADDRESS(clCreateImage)
			GET_ADDRESS(clCreatePipe)
			GET_ADDRESS(clCreateBufferWithProperties)
			GET_ADDRESS(clCreateImageWithProperties)
			GET_ADDRESS(clRetainMemObject)
			GET_ADDRESS(clReleaseMemObject)
			GET_ADDRESS(clGetSupportedImageFormats)
			GET_ADDRESS(clGetMemObjectInfo)
			GET_ADDRESS(clGetImageInfo)
			GET_ADDRESS(clGetPipeInfo)
			GET_ADDRESS(clSetMemObjectDestructorCallback)
			GET_ADDRESS(clSVMAlloc)
			GET_ADDRESS(clSVMFree)
			GET_ADDRESS(clCreateSamplerWithProperties)
			GET_ADDRESS(clRetainSampler)
			GET_ADDRESS(clReleaseSampler)
			GET_ADDRESS(clGetSamplerInfo)
			GET_ADDRESS(clCreateProgramWithSource)
			GET_ADDRESS(clCreateProgramWithBinary)
			GET_ADDRESS(clCreateProgramWithBuiltInKernels)
			GET_ADDRESS(clCreateProgramWithIL)
			GET_ADDRESS(clRetainProgram)
			GET_ADDRESS(clReleaseProgram)
			GET_ADDRESS(clBuildProgram)
			GET_ADDRESS(clCompileProgram)
			GET_ADDRESS(clLinkProgram)
			GET_ADDRESS(clSetProgramReleaseCallback)
			GET_ADDRESS(clSetProgramSpecializationConstant)
			GET_ADDRESS(clUnloadPlatformCompiler)
			GET_ADDRESS(clGetProgramInfo)
			GET_ADDRESS(clGetProgramBuildInfo)
			GET_ADDRESS(clCreateKernel)
			GET_ADDRESS(clCreateKernelsInProgram)
			GET_ADDRESS(clCloneKernel)
			GET_ADDRESS(clRetainKernel)
			GET_ADDRESS(clReleaseKernel)
			GET_ADDRESS(clSetKernelArg)
			GET_ADDRESS(clSetKernelArgSVMPointer)
			GET_ADDRESS(clSetKernelExecInfo)
			GET_ADDRESS(clGetKernelInfo)
			GET_ADDRESS(clGetKernelArgInfo)
			GET_ADDRESS(clGetKernelWorkGroupInfo)
			GET_ADDRESS(clGetKernelSubGroupInfo)
			GET_ADDRESS(clWaitForEvents)
			GET_ADDRESS(clGetEventInfo)
			GET_ADDRESS(clCreateUserEvent)
			GET_ADDRESS(clRetainEvent)
			GET_ADDRESS(clReleaseEvent)
			GET_ADDRESS(clSetUserEventStatus)
			GET_ADDRESS(clSetEventCallback)
			GET_ADDRESS(clGetEventProfilingInfo)
			GET_ADDRESS(clFlush)
			GET_ADDRESS(clFinish)
			GET_ADDRESS(clEnqueueReadBuffer)
			GET_ADDRESS(clEnqueueReadBufferRect)
			GET_ADDRESS(clEnqueueWriteBuffer)
			GET_ADDRESS(clEnqueueWriteBufferRect)
			GET_ADDRESS(clEnqueueFillBuffer)
			GET_ADDRESS(clEnqueueCopyBuffer)
			GET_ADDRESS(clEnqueueCopyBufferRect)
			GET_ADDRESS(clEnqueueReadImage)
			GET_ADDRESS(clEnqueueWriteImage)
			GET_ADDRESS(clEnqueueFillImage)
			GET_ADDRESS(clEnqueueCopyImage)
			GET_ADDRESS(clEnqueueCopyImageToBuffer)
			GET_ADDRESS(clEnqueueCopyBufferToImage)
			GET_ADDRESS(clEnqueueMapBuffer)
			GET_ADDRESS(clEnqueueMapImage)
			GET_ADDRESS(clEnqueueUnmapMemObject)
			GET_ADDRESS(clEnqueueMigrateMemObjects)
			GET_ADDRESS(clEnqueueNDRangeKernel)
			GET_ADDRESS(clEnqueueNativeKernel)
			GET_ADDRESS(clEnqueueMarkerWithWaitList)
			GET_ADDRESS(clEnqueueBarrierWithWaitList)
			GET_ADDRESS(clEnqueueSVMMemcpy)
			GET_ADDRESS(clEnqueueSVMMemFill)
			GET_ADDRESS(clEnqueueSVMMap)
			GET_ADDRESS(clEnqueueSVMUnmap)
			GET_ADDRESS(clEnqueueSVMMigrateMem)
			GET_ADDRESS(clGetExtensionFunctionAddressForPlatform)
			GET_ADDRESS(clCreateImage2D)
			GET_ADDRESS(clCreateImage3D)
			GET_ADDRESS(clEnqueueMarker)
			GET_ADDRESS(clEnqueueWaitForEvents)
			GET_ADDRESS(clEnqueueBarrier)
			GET_ADDRESS(clUnloadCompiler)
			GET_ADDRESS(clGetExtensionFunctionAddress)
			GET_ADDRESS(clCreateCommandQueue)
			GET_ADDRESS(clCreateSampler)
			GET_ADDRESS(clEnqueueTask)
			
			#undef GET_ADDRESS
			
			// get devices
			cl_uint num_platforms = 0;
			cl_platform_id platforms[64] = {};
			if(clGetPlatformIDs(TS_COUNTOF(platforms), platforms, &num_platforms) == CL_SUCCESS && num_platforms) {
				for(uint32_t i = 0; i < num_platforms; i++) {
					cl_uint num_platform_devices = 0;
					cl_device_id platform_devices[64] = {};
					if(clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_GPU, TS_COUNTOF(platform_devices), platform_devices, &num_platform_devices) == CL_SUCCESS && num_platform_devices) {
						for(uint32_t j = 0; j < num_platform_devices; j++) {
							devices.append(new CLDevice(platforms[i], platform_devices[j]));
						}
						platform = platforms[i];
						break;
					}
				}
			}
			
			// check devices
			if(!devices) {
				close();
				return false;
			}
			
			// platform info
			size_t size = 0;
			if(clGetPlatformInfo(platform, CL_PLATFORM_NAME, 0, nullptr, &size) == CL_SUCCESS) {
				platform_name.resize((uint32_t)size);
				clGetPlatformInfo(platform, CL_PLATFORM_NAME, platform_name.size(), platform_name.get(), nullptr);
			}
			if(clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, 0, nullptr, &size) == CL_SUCCESS) {
				platform_vendor.resize((uint32_t)size);
				clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, platform_vendor.size(), platform_vendor.get(), nullptr);
			}
			if(clGetPlatformInfo(platform, CL_PLATFORM_VERSION, 0, nullptr, &size) == CL_SUCCESS) {
				platform_version.resize((uint32_t)size);
				clGetPlatformInfo(platform, CL_PLATFORM_VERSION, platform_version.size(), platform_version.get(), nullptr);
			}
			if(clGetPlatformInfo(platform, CL_PLATFORM_EXTENSIONS, 0, nullptr, &size) == CL_SUCCESS) {
				platform_extensions.resize((uint32_t)size);
				clGetPlatformInfo(platform, CL_PLATFORM_EXTENSIONS, platform_extensions.size(), platform_extensions.get(), nullptr);
				platform_extensions = platform_extensions.replace("cl_", "");
			}
			
			// extension functions
			#define GET_ADDRESS(NAME) { \
				void *address = clGetExtensionFunctionAddressForPlatform(platform, #NAME); \
				NAME = (PFN_ ## NAME)address; \
			}
			
			// OpenCL extension functions
			GET_ADDRESS(clGetGLContextInfoKHR)
			GET_ADDRESS(clCreateFromGLBuffer)
			GET_ADDRESS(clCreateFromGLTexture)
			GET_ADDRESS(clCreateFromGLRenderbuffer)
			GET_ADDRESS(clGetGLObjectInfo)
			GET_ADDRESS(clGetGLTextureInfo)
			GET_ADDRESS(clEnqueueAcquireGLObjects)
			GET_ADDRESS(clEnqueueReleaseGLObjects)
			GET_ADDRESS(clCreateFromGLTexture2D)
			GET_ADDRESS(clCreateFromGLTexture3D)
			GET_ADDRESS(clCreateEventFromGLsyncKHR)
			GET_ADDRESS(clGetSupportedGLTextureFormatsINTEL)
			GET_ADDRESS(clSetMemObjectDestructorAPPLE)
			GET_ADDRESS(clLogMessagesToSystemLogAPPLE)
			GET_ADDRESS(clLogMessagesToStdoutAPPLE)
			GET_ADDRESS(clLogMessagesToStderrAPPLE)
			GET_ADDRESS(clIcdGetPlatformIDsKHR)
			GET_ADDRESS(clIcdGetFunctionAddressForPlatformKHR)
			GET_ADDRESS(clIcdSetPlatformDispatchDataKHR)
			GET_ADDRESS(clCreateProgramWithILKHR)
			GET_ADDRESS(clTerminateContextKHR)
			GET_ADDRESS(clCreateCommandQueueWithPropertiesKHR)
			GET_ADDRESS(clReleaseDeviceEXT)
			GET_ADDRESS(clRetainDeviceEXT)
			GET_ADDRESS(clCreateSubDevicesEXT)
			GET_ADDRESS(clEnqueueMigrateMemObjectEXT)
			GET_ADDRESS(clGetDeviceImageInfoQCOM)
			GET_ADDRESS(clEnqueueAcquireGrallocObjectsIMG)
			GET_ADDRESS(clEnqueueReleaseGrallocObjectsIMG)
			GET_ADDRESS(clEnqueueGenerateMipmapIMG)
			GET_ADDRESS(clGetKernelSubGroupInfoKHR)
			GET_ADDRESS(clGetKernelSuggestedLocalWorkSizeKHR)
			GET_ADDRESS(clEnqueueAcquireExternalMemObjectsKHR)
			GET_ADDRESS(clEnqueueReleaseExternalMemObjectsKHR)
			GET_ADDRESS(clGetSemaphoreHandleForTypeKHR)
			GET_ADDRESS(clReImportSemaphoreSyncFdKHR)
			GET_ADDRESS(clCreateSemaphoreWithPropertiesKHR)
			GET_ADDRESS(clEnqueueWaitSemaphoresKHR)
			GET_ADDRESS(clEnqueueSignalSemaphoresKHR)
			GET_ADDRESS(clGetSemaphoreInfoKHR)
			GET_ADDRESS(clReleaseSemaphoreKHR)
			GET_ADDRESS(clRetainSemaphoreKHR)
			GET_ADDRESS(clImportMemoryARM)
			GET_ADDRESS(clSVMAllocARM)
			GET_ADDRESS(clSVMFreeARM)
			GET_ADDRESS(clEnqueueSVMMemcpyARM)
			GET_ADDRESS(clEnqueueSVMMemFillARM)
			GET_ADDRESS(clEnqueueSVMMapARM)
			GET_ADDRESS(clEnqueueSVMUnmapARM)
			GET_ADDRESS(clSetKernelArgSVMPointerARM)
			GET_ADDRESS(clSetKernelExecInfoARM)
			GET_ADDRESS(clCreateAcceleratorINTEL)
			GET_ADDRESS(clGetAcceleratorInfoINTEL)
			GET_ADDRESS(clRetainAcceleratorINTEL)
			GET_ADDRESS(clReleaseAcceleratorINTEL)
			GET_ADDRESS(clHostMemAllocINTEL)
			GET_ADDRESS(clDeviceMemAllocINTEL)
			GET_ADDRESS(clSharedMemAllocINTEL)
			GET_ADDRESS(clMemFreeINTEL)
			GET_ADDRESS(clMemBlockingFreeINTEL)
			GET_ADDRESS(clGetMemAllocInfoINTEL)
			GET_ADDRESS(clSetKernelArgMemPointerINTEL)
			GET_ADDRESS(clEnqueueMemFillINTEL)
			GET_ADDRESS(clEnqueueMemcpyINTEL)
			GET_ADDRESS(clEnqueueMemAdviseINTEL)
			GET_ADDRESS(clEnqueueMigrateMemINTEL)
			GET_ADDRESS(clEnqueueMemsetINTEL)
			GET_ADDRESS(clCreateBufferWithPropertiesINTEL)
			GET_ADDRESS(clEnqueueReadHostPipeINTEL)
			GET_ADDRESS(clEnqueueWriteHostPipeINTEL)
			GET_ADDRESS(clGetImageRequirementsInfoEXT)
			GET_ADDRESS(clGetICDLoaderInfoOCLICD)
			GET_ADDRESS(clSetContentSizeBufferPoCL)
			GET_ADDRESS(clSetKernelArgDevicePointerEXT)
			GET_ADDRESS(clCancelCommandsIMG)
			GET_ADDRESS(clSetPerfHintQCOM)
			
			#undef GET_ADDRESS
			
			return true;
		}
		
		/*
		 */
		void close() {
			
			// release devices
			for(uint32_t i = 0; i < devices.size(); i++) {
				delete devices[i];
			}
			devices.clear();
			
			// close library
			if(handle != nullptr) {
				System::closeLibrary(handle);
				handle = nullptr;
			}
		}
		
		/*
		 */
		cl_platform_id getPlatform() {
			return platform;
		}
		
		const String &getName() {
			return platform_name;
		}
		
		const String &getVendor() {
			return platform_vendor;
		}
		
		const String &getVersion() {
			return platform_version;
		}
		
		const String &getExtensions() {
			return platform_extensions;
		}
		
		/*
		 */
		bool checkExtension(const char *name) {
			if(!strncmp(name, "cl_", 3)) name += 3;
			return platform_extensions.contains(name);
		}
		
		/*
		 */
		uint32_t getNumDevices() {
			return devices.size();
		}
		
		CLDevice *getDevice(uint32_t index) {
			return devices[index];
		}
		
		/*
		 */
		bool error(cl_int error) {
			const char *error_str = nullptr;
			switch(error) {
				case CL_SUCCESS: return false;
				case CL_DEVICE_NOT_FOUND: error_str = "device not found"; break;
				case CL_DEVICE_NOT_AVAILABLE: error_str = "device not available"; break;
				case CL_COMPILER_NOT_AVAILABLE: error_str = "compiler not available"; break;
				case CL_MEM_OBJECT_ALLOCATION_FAILURE: error_str = "mem object allocation failure"; break;
				case CL_OUT_OF_RESOURCES: error_str = "out of resources"; break;
				case CL_OUT_OF_HOST_MEMORY: error_str = "out of host memory"; break;
				case CL_PROFILING_INFO_NOT_AVAILABLE: error_str = "profiling info not available"; break;
				case CL_MEM_COPY_OVERLAP: error_str = "mem copy overlap"; break;
				case CL_IMAGE_FORMAT_MISMATCH: error_str = "image format mismatch"; break;
				case CL_IMAGE_FORMAT_NOT_SUPPORTED: error_str = "image format not supported"; break;
				case CL_BUILD_PROGRAM_FAILURE: error_str = "build program failure"; break;
				case CL_MAP_FAILURE: error_str = "map failure"; break;
				case CL_MISALIGNED_SUB_BUFFER_OFFSET: error_str = "misaligned sub buffer offset"; break;
				case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST: error_str = "exec status error for events in wait list"; break;
				case CL_COMPILE_PROGRAM_FAILURE: error_str = "compile program failure"; break;
				case CL_LINKER_NOT_AVAILABLE: error_str = "linker not available"; break;
				case CL_LINK_PROGRAM_FAILURE: error_str = "link program failure"; break;
				case CL_DEVICE_PARTITION_FAILED: error_str = "device partition failed"; break;
				case CL_KERNEL_ARG_INFO_NOT_AVAILABLE: error_str = "kernel arg info not available"; break;
				case CL_INVALID_VALUE: error_str = "invalid value"; break;
				case CL_INVALID_DEVICE_TYPE: error_str = "invalid device type"; break;
				case CL_INVALID_PLATFORM: error_str = "invalid platform"; break;
				case CL_INVALID_DEVICE: error_str = "invalid device"; break;
				case CL_INVALID_CONTEXT: error_str = "invalid context"; break;
				case CL_INVALID_QUEUE_PROPERTIES: error_str = "invalid queue properties"; break;
				case CL_INVALID_COMMAND_QUEUE: error_str = "invalid command queue"; break;
				case CL_INVALID_HOST_PTR: error_str = "invalid host ptr"; break;
				case CL_INVALID_MEM_OBJECT: error_str = "invalid mem object"; break;
				case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR: error_str = "invalid image format descriptor"; break;
				case CL_INVALID_IMAGE_SIZE: error_str = "invalid image size"; break;
				case CL_INVALID_SAMPLER: error_str = "invalid sampler"; break;
				case CL_INVALID_BINARY: error_str = "invalid binary"; break;
				case CL_INVALID_BUILD_OPTIONS: error_str = "invalid build options"; break;
				case CL_INVALID_PROGRAM: error_str = "invalid program"; break;
				case CL_INVALID_PROGRAM_EXECUTABLE: error_str = "invalid program executable"; break;
				case CL_INVALID_KERNEL_NAME: error_str = "invalid kernel name"; break;
				case CL_INVALID_KERNEL_DEFINITION: error_str = "invalid kernel definition"; break;
				case CL_INVALID_KERNEL: error_str = "invalid kernel"; break;
				case CL_INVALID_ARG_INDEX: error_str = "invalid arg index"; break;
				case CL_INVALID_ARG_VALUE: error_str = "invalid arg value"; break;
				case CL_INVALID_ARG_SIZE: error_str = "invalid arg size"; break;
				case CL_INVALID_KERNEL_ARGS: error_str = "invalid kernel args"; break;
				case CL_INVALID_WORK_DIMENSION: error_str = "invalid work dimension"; break;
				case CL_INVALID_WORK_GROUP_SIZE: error_str = "invalid work group size"; break;
				case CL_INVALID_WORK_ITEM_SIZE: error_str = "invalid work item size"; break;
				case CL_INVALID_GLOBAL_OFFSET: error_str = "invalid global offset"; break;
				case CL_INVALID_EVENT_WAIT_LIST: error_str = "invalid event wait list"; break;
				case CL_INVALID_EVENT: error_str = "invalid event"; break;
				case CL_INVALID_OPERATION: error_str = "invalid operation"; break;
				case CL_INVALID_GL_OBJECT: error_str = "invalid gl object"; break;
				case CL_INVALID_BUFFER_SIZE: error_str = "invalid buffer size"; break;
				case CL_INVALID_MIP_LEVEL: error_str = "invalid mip level"; break;
				case CL_INVALID_GLOBAL_WORK_SIZE: error_str = "invalid global work size"; break;
				case CL_INVALID_PROPERTY: error_str = "invalid property"; break;
				case CL_INVALID_IMAGE_DESCRIPTOR: error_str = "invalid image descriptor"; break;
				case CL_INVALID_COMPILER_OPTIONS: error_str = "invalid compiler options"; break;
				case CL_INVALID_LINKER_OPTIONS: error_str = "invalid linker options"; break;
				case CL_INVALID_DEVICE_PARTITION_COUNT: error_str = "invalid device partition count"; break;
				case CL_INVALID_PIPE_SIZE: error_str = "invalid pipe size"; break;
				case CL_INVALID_DEVICE_QUEUE: error_str = "invalid device queue"; break;
				case CL_INVALID_SPEC_ID: error_str = "invalid spec id"; break;
				case CL_MAX_SIZE_RESTRICTION_EXCEEDED: error_str = "max size restriction exceeded"; break;
			}
			if(error_str) TS_LOGF(Error, "CL::error(): %s\n", error_str);
			else TS_LOGF(Error, "CL::error(): 0x%04x\n", error);
			return true;
		}
	}
	
	/*****************************************************************************\
	 *
	 * OpenCL Device
	 *
	\*****************************************************************************/
	
	/*
	 */
	CLDevice::CLDevice(cl_platform_id p, cl_device_id d) {
		
		// current device
		platform = p;
		device = d;
		
		// device info
		size_t size = 0;
		if(clGetDeviceInfo(device, CL_DEVICE_NAME, 0, nullptr, &size) == CL_SUCCESS) {
			device_name.resize((uint32_t)size);
			clGetDeviceInfo(device, CL_DEVICE_NAME, device_name.size(), device_name.get(), nullptr);
		}
		if(clGetDeviceInfo(device, CL_DEVICE_VENDOR, 0, nullptr, &size) == CL_SUCCESS) {
			device_vendor.resize((uint32_t)size);
			clGetDeviceInfo(device, CL_DEVICE_VENDOR, device_vendor.size(), device_vendor.get(), nullptr);
		}
		if(clGetDeviceInfo(device, CL_DEVICE_VERSION, 0, nullptr, &size) == CL_SUCCESS) {
			device_version.resize((uint32_t)size);
			clGetDeviceInfo(device, CL_DEVICE_VERSION, device_version.size(), device_version.get(), nullptr);
		}
		if(clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, 0, nullptr, &size) == CL_SUCCESS) {
			device_extensions.resize((uint32_t)size);
			clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, device_extensions.size(), device_extensions.get(), nullptr);
			device_extensions = device_extensions.replace("cl_", "");
		}
	}
	
	CLDevice::~CLDevice() {
		
	}
	
	/*
	 */
	bool CLDevice::checkExtension(const char *name) {
		if(!strncmp(name, "cl_", 3)) name += 3;
		return device_extensions.contains(name);
	}
	
	/*****************************************************************************\
	 *
	 * OpenCL functions
	 *
	\*****************************************************************************/
	
	// OpenCL functions
	PFN_clGetPlatformIDs clGetPlatformIDs = nullptr;
	PFN_clGetPlatformInfo clGetPlatformInfo = nullptr;
	PFN_clGetDeviceIDs clGetDeviceIDs = nullptr;
	PFN_clGetDeviceInfo clGetDeviceInfo = nullptr;
	PFN_clCreateSubDevices clCreateSubDevices = nullptr;
	PFN_clRetainDevice clRetainDevice = nullptr;
	PFN_clReleaseDevice clReleaseDevice = nullptr;
	PFN_clSetDefaultDeviceCommandQueue clSetDefaultDeviceCommandQueue = nullptr;
	PFN_clGetDeviceAndHostTimer clGetDeviceAndHostTimer = nullptr;
	PFN_clGetHostTimer clGetHostTimer = nullptr;
	PFN_clCreateContext clCreateContext = nullptr;
	PFN_clCreateContextFromType clCreateContextFromType = nullptr;
	PFN_clRetainContext clRetainContext = nullptr;
	PFN_clReleaseContext clReleaseContext = nullptr;
	PFN_clGetContextInfo clGetContextInfo = nullptr;
	PFN_clSetContextDestructorCallback clSetContextDestructorCallback = nullptr;
	PFN_clCreateCommandQueueWithProperties clCreateCommandQueueWithProperties = nullptr;
	PFN_clRetainCommandQueue clRetainCommandQueue = nullptr;
	PFN_clReleaseCommandQueue clReleaseCommandQueue = nullptr;
	PFN_clGetCommandQueueInfo clGetCommandQueueInfo = nullptr;
	PFN_clCreateBuffer clCreateBuffer = nullptr;
	PFN_clCreateSubBuffer clCreateSubBuffer = nullptr;
	PFN_clCreateImage clCreateImage = nullptr;
	PFN_clCreatePipe clCreatePipe = nullptr;
	PFN_clCreateBufferWithProperties clCreateBufferWithProperties = nullptr;
	PFN_clCreateImageWithProperties clCreateImageWithProperties = nullptr;
	PFN_clRetainMemObject clRetainMemObject = nullptr;
	PFN_clReleaseMemObject clReleaseMemObject = nullptr;
	PFN_clGetSupportedImageFormats clGetSupportedImageFormats = nullptr;
	PFN_clGetMemObjectInfo clGetMemObjectInfo = nullptr;
	PFN_clGetImageInfo clGetImageInfo = nullptr;
	PFN_clGetPipeInfo clGetPipeInfo = nullptr;
	PFN_clSetMemObjectDestructorCallback clSetMemObjectDestructorCallback = nullptr;
	PFN_clSVMAlloc clSVMAlloc = nullptr;
	PFN_clSVMFree clSVMFree = nullptr;
	PFN_clCreateSamplerWithProperties clCreateSamplerWithProperties = nullptr;
	PFN_clRetainSampler clRetainSampler = nullptr;
	PFN_clReleaseSampler clReleaseSampler = nullptr;
	PFN_clGetSamplerInfo clGetSamplerInfo = nullptr;
	PFN_clCreateProgramWithSource clCreateProgramWithSource = nullptr;
	PFN_clCreateProgramWithBinary clCreateProgramWithBinary = nullptr;
	PFN_clCreateProgramWithBuiltInKernels clCreateProgramWithBuiltInKernels = nullptr;
	PFN_clCreateProgramWithIL clCreateProgramWithIL = nullptr;
	PFN_clRetainProgram clRetainProgram = nullptr;
	PFN_clReleaseProgram clReleaseProgram = nullptr;
	PFN_clBuildProgram clBuildProgram = nullptr;
	PFN_clCompileProgram clCompileProgram = nullptr;
	PFN_clLinkProgram clLinkProgram = nullptr;
	PFN_clSetProgramReleaseCallback clSetProgramReleaseCallback = nullptr;
	PFN_clSetProgramSpecializationConstant clSetProgramSpecializationConstant = nullptr;
	PFN_clUnloadPlatformCompiler clUnloadPlatformCompiler = nullptr;
	PFN_clGetProgramInfo clGetProgramInfo = nullptr;
	PFN_clGetProgramBuildInfo clGetProgramBuildInfo = nullptr;
	PFN_clCreateKernel clCreateKernel = nullptr;
	PFN_clCreateKernelsInProgram clCreateKernelsInProgram = nullptr;
	PFN_clCloneKernel clCloneKernel = nullptr;
	PFN_clRetainKernel clRetainKernel = nullptr;
	PFN_clReleaseKernel clReleaseKernel = nullptr;
	PFN_clSetKernelArg clSetKernelArg = nullptr;
	PFN_clSetKernelArgSVMPointer clSetKernelArgSVMPointer = nullptr;
	PFN_clSetKernelExecInfo clSetKernelExecInfo = nullptr;
	PFN_clGetKernelInfo clGetKernelInfo = nullptr;
	PFN_clGetKernelArgInfo clGetKernelArgInfo = nullptr;
	PFN_clGetKernelWorkGroupInfo clGetKernelWorkGroupInfo = nullptr;
	PFN_clGetKernelSubGroupInfo clGetKernelSubGroupInfo = nullptr;
	PFN_clWaitForEvents clWaitForEvents = nullptr;
	PFN_clGetEventInfo clGetEventInfo = nullptr;
	PFN_clCreateUserEvent clCreateUserEvent = nullptr;
	PFN_clRetainEvent clRetainEvent = nullptr;
	PFN_clReleaseEvent clReleaseEvent = nullptr;
	PFN_clSetUserEventStatus clSetUserEventStatus = nullptr;
	PFN_clSetEventCallback clSetEventCallback = nullptr;
	PFN_clGetEventProfilingInfo clGetEventProfilingInfo = nullptr;
	PFN_clFlush clFlush = nullptr;
	PFN_clFinish clFinish = nullptr;
	PFN_clEnqueueReadBuffer clEnqueueReadBuffer = nullptr;
	PFN_clEnqueueReadBufferRect clEnqueueReadBufferRect = nullptr;
	PFN_clEnqueueWriteBuffer clEnqueueWriteBuffer = nullptr;
	PFN_clEnqueueWriteBufferRect clEnqueueWriteBufferRect = nullptr;
	PFN_clEnqueueFillBuffer clEnqueueFillBuffer = nullptr;
	PFN_clEnqueueCopyBuffer clEnqueueCopyBuffer = nullptr;
	PFN_clEnqueueCopyBufferRect clEnqueueCopyBufferRect = nullptr;
	PFN_clEnqueueReadImage clEnqueueReadImage = nullptr;
	PFN_clEnqueueWriteImage clEnqueueWriteImage = nullptr;
	PFN_clEnqueueFillImage clEnqueueFillImage = nullptr;
	PFN_clEnqueueCopyImage clEnqueueCopyImage = nullptr;
	PFN_clEnqueueCopyImageToBuffer clEnqueueCopyImageToBuffer = nullptr;
	PFN_clEnqueueCopyBufferToImage clEnqueueCopyBufferToImage = nullptr;
	PFN_clEnqueueMapBuffer clEnqueueMapBuffer = nullptr;
	PFN_clEnqueueMapImage clEnqueueMapImage = nullptr;
	PFN_clEnqueueUnmapMemObject clEnqueueUnmapMemObject = nullptr;
	PFN_clEnqueueMigrateMemObjects clEnqueueMigrateMemObjects = nullptr;
	PFN_clEnqueueNDRangeKernel clEnqueueNDRangeKernel = nullptr;
	PFN_clEnqueueNativeKernel clEnqueueNativeKernel = nullptr;
	PFN_clEnqueueMarkerWithWaitList clEnqueueMarkerWithWaitList = nullptr;
	PFN_clEnqueueBarrierWithWaitList clEnqueueBarrierWithWaitList = nullptr;
	PFN_clEnqueueSVMMemcpy clEnqueueSVMMemcpy = nullptr;
	PFN_clEnqueueSVMMemFill clEnqueueSVMMemFill = nullptr;
	PFN_clEnqueueSVMMap clEnqueueSVMMap = nullptr;
	PFN_clEnqueueSVMUnmap clEnqueueSVMUnmap = nullptr;
	PFN_clEnqueueSVMMigrateMem clEnqueueSVMMigrateMem = nullptr;
	PFN_clGetExtensionFunctionAddressForPlatform clGetExtensionFunctionAddressForPlatform = nullptr;
	PFN_clCreateImage2D clCreateImage2D = nullptr;
	PFN_clCreateImage3D clCreateImage3D = nullptr;
	PFN_clEnqueueMarker clEnqueueMarker = nullptr;
	PFN_clEnqueueWaitForEvents clEnqueueWaitForEvents = nullptr;
	PFN_clEnqueueBarrier clEnqueueBarrier = nullptr;
	PFN_clUnloadCompiler clUnloadCompiler = nullptr;
	PFN_clGetExtensionFunctionAddress clGetExtensionFunctionAddress = nullptr;
	PFN_clCreateCommandQueue clCreateCommandQueue = nullptr;
	PFN_clCreateSampler clCreateSampler = nullptr;
	PFN_clEnqueueTask clEnqueueTask = nullptr;
	
	// OpenCL extension functions
	PFN_clGetGLContextInfoKHR clGetGLContextInfoKHR = nullptr;
	PFN_clCreateFromGLBuffer clCreateFromGLBuffer = nullptr;
	PFN_clCreateFromGLTexture clCreateFromGLTexture = nullptr;
	PFN_clCreateFromGLRenderbuffer clCreateFromGLRenderbuffer = nullptr;
	PFN_clGetGLObjectInfo clGetGLObjectInfo = nullptr;
	PFN_clGetGLTextureInfo clGetGLTextureInfo = nullptr;
	PFN_clEnqueueAcquireGLObjects clEnqueueAcquireGLObjects = nullptr;
	PFN_clEnqueueReleaseGLObjects clEnqueueReleaseGLObjects = nullptr;
	PFN_clCreateFromGLTexture2D clCreateFromGLTexture2D = nullptr;
	PFN_clCreateFromGLTexture3D clCreateFromGLTexture3D = nullptr;
	PFN_clCreateEventFromGLsyncKHR clCreateEventFromGLsyncKHR = nullptr;
	PFN_clGetSupportedGLTextureFormatsINTEL clGetSupportedGLTextureFormatsINTEL = nullptr;
	PFN_clSetMemObjectDestructorAPPLE clSetMemObjectDestructorAPPLE = nullptr;
	PFN_clLogMessagesToSystemLogAPPLE clLogMessagesToSystemLogAPPLE = nullptr;
	PFN_clLogMessagesToStdoutAPPLE clLogMessagesToStdoutAPPLE = nullptr;
	PFN_clLogMessagesToStderrAPPLE clLogMessagesToStderrAPPLE = nullptr;
	PFN_clIcdGetPlatformIDsKHR clIcdGetPlatformIDsKHR = nullptr;
	PFN_clIcdGetFunctionAddressForPlatformKHR clIcdGetFunctionAddressForPlatformKHR = nullptr;
	PFN_clIcdSetPlatformDispatchDataKHR clIcdSetPlatformDispatchDataKHR = nullptr;
	PFN_clCreateProgramWithILKHR clCreateProgramWithILKHR = nullptr;
	PFN_clTerminateContextKHR clTerminateContextKHR = nullptr;
	PFN_clCreateCommandQueueWithPropertiesKHR clCreateCommandQueueWithPropertiesKHR = nullptr;
	PFN_clReleaseDeviceEXT clReleaseDeviceEXT = nullptr;
	PFN_clRetainDeviceEXT clRetainDeviceEXT = nullptr;
	PFN_clCreateSubDevicesEXT clCreateSubDevicesEXT = nullptr;
	PFN_clEnqueueMigrateMemObjectEXT clEnqueueMigrateMemObjectEXT = nullptr;
	PFN_clGetDeviceImageInfoQCOM clGetDeviceImageInfoQCOM = nullptr;
	PFN_clEnqueueAcquireGrallocObjectsIMG clEnqueueAcquireGrallocObjectsIMG = nullptr;
	PFN_clEnqueueReleaseGrallocObjectsIMG clEnqueueReleaseGrallocObjectsIMG = nullptr;
	PFN_clEnqueueGenerateMipmapIMG clEnqueueGenerateMipmapIMG = nullptr;
	PFN_clGetKernelSubGroupInfoKHR clGetKernelSubGroupInfoKHR = nullptr;
	PFN_clGetKernelSuggestedLocalWorkSizeKHR clGetKernelSuggestedLocalWorkSizeKHR = nullptr;
	PFN_clEnqueueAcquireExternalMemObjectsKHR clEnqueueAcquireExternalMemObjectsKHR = nullptr;
	PFN_clEnqueueReleaseExternalMemObjectsKHR clEnqueueReleaseExternalMemObjectsKHR = nullptr;
	PFN_clGetSemaphoreHandleForTypeKHR clGetSemaphoreHandleForTypeKHR = nullptr;
	PFN_clReImportSemaphoreSyncFdKHR clReImportSemaphoreSyncFdKHR = nullptr;
	PFN_clCreateSemaphoreWithPropertiesKHR clCreateSemaphoreWithPropertiesKHR = nullptr;
	PFN_clEnqueueWaitSemaphoresKHR clEnqueueWaitSemaphoresKHR = nullptr;
	PFN_clEnqueueSignalSemaphoresKHR clEnqueueSignalSemaphoresKHR = nullptr;
	PFN_clGetSemaphoreInfoKHR clGetSemaphoreInfoKHR = nullptr;
	PFN_clReleaseSemaphoreKHR clReleaseSemaphoreKHR = nullptr;
	PFN_clRetainSemaphoreKHR clRetainSemaphoreKHR = nullptr;
	PFN_clImportMemoryARM clImportMemoryARM = nullptr;
	PFN_clSVMAllocARM clSVMAllocARM = nullptr;
	PFN_clSVMFreeARM clSVMFreeARM = nullptr;
	PFN_clEnqueueSVMMemcpyARM clEnqueueSVMMemcpyARM = nullptr;
	PFN_clEnqueueSVMMemFillARM clEnqueueSVMMemFillARM = nullptr;
	PFN_clEnqueueSVMMapARM clEnqueueSVMMapARM = nullptr;
	PFN_clEnqueueSVMUnmapARM clEnqueueSVMUnmapARM = nullptr;
	PFN_clSetKernelArgSVMPointerARM clSetKernelArgSVMPointerARM = nullptr;
	PFN_clSetKernelExecInfoARM clSetKernelExecInfoARM = nullptr;
	PFN_clCreateAcceleratorINTEL clCreateAcceleratorINTEL = nullptr;
	PFN_clGetAcceleratorInfoINTEL clGetAcceleratorInfoINTEL = nullptr;
	PFN_clRetainAcceleratorINTEL clRetainAcceleratorINTEL = nullptr;
	PFN_clReleaseAcceleratorINTEL clReleaseAcceleratorINTEL = nullptr;
	PFN_clHostMemAllocINTEL clHostMemAllocINTEL = nullptr;
	PFN_clDeviceMemAllocINTEL clDeviceMemAllocINTEL = nullptr;
	PFN_clSharedMemAllocINTEL clSharedMemAllocINTEL = nullptr;
	PFN_clMemFreeINTEL clMemFreeINTEL = nullptr;
	PFN_clMemBlockingFreeINTEL clMemBlockingFreeINTEL = nullptr;
	PFN_clGetMemAllocInfoINTEL clGetMemAllocInfoINTEL = nullptr;
	PFN_clSetKernelArgMemPointerINTEL clSetKernelArgMemPointerINTEL = nullptr;
	PFN_clEnqueueMemFillINTEL clEnqueueMemFillINTEL = nullptr;
	PFN_clEnqueueMemcpyINTEL clEnqueueMemcpyINTEL = nullptr;
	PFN_clEnqueueMemAdviseINTEL clEnqueueMemAdviseINTEL = nullptr;
	PFN_clEnqueueMigrateMemINTEL clEnqueueMigrateMemINTEL = nullptr;
	PFN_clEnqueueMemsetINTEL clEnqueueMemsetINTEL = nullptr;
	PFN_clCreateBufferWithPropertiesINTEL clCreateBufferWithPropertiesINTEL = nullptr;
	PFN_clEnqueueReadHostPipeINTEL clEnqueueReadHostPipeINTEL = nullptr;
	PFN_clEnqueueWriteHostPipeINTEL clEnqueueWriteHostPipeINTEL = nullptr;
	PFN_clGetImageRequirementsInfoEXT clGetImageRequirementsInfoEXT = nullptr;
	PFN_clGetICDLoaderInfoOCLICD clGetICDLoaderInfoOCLICD = nullptr;
	PFN_clSetContentSizeBufferPoCL clSetContentSizeBufferPoCL = nullptr;
	PFN_clSetKernelArgDevicePointerEXT clSetKernelArgDevicePointerEXT = nullptr;
	PFN_clCancelCommandsIMG clCancelCommandsIMG = nullptr;
	PFN_clSetPerfHintQCOM clSetPerfHintQCOM = nullptr;
}

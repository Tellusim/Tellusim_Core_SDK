// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_PLUGINS_PLATFORM_CL_H__
#define __TELLUSIM_PLUGINS_PLATFORM_CL_H__

#define CL_TARGET_OPENCL_VERSION 300
#include <CL/opencl.h>

#include <core/TellusimString.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class CLDevice;
	
	/**
	 * OpenCL
	 */
	namespace CL {
		
		/// retain/release
		bool retain();
		bool release();
		
		/// check status
		bool isOpened();
		
		/// open/close
		bool open();
		void close();
		
		/// OpenCL platform
		cl_platform_id getPlatform();
		
		/// OpenCL platform info
		const String &getName();
		const String &getVendor();
		const String &getVersion();
		const String &getExtensions();
		
		/// check OpenCL platform info
		bool checkExtension(const char *name);
		
		/// OpenCL devices
		uint32_t getNumDevices();
		CLDevice *getDevice(uint32_t index);
		
		/// check OpenCL errors
		bool error(cl_int error);
	}
	
	/**
	 * OpenCL Device
	 */
	class CLDevice {
			
		public:
			
			CLDevice(cl_platform_id platform, cl_device_id device);
			~CLDevice();
			
			/// OpenCL device
			cl_platform_id getPlatform() const { return platform; }
			cl_device_id getDevice() const { return device; }
			
			/// OpenCL device info
			const String &getName() const { return device_name; }
			const String &getVendor() const { return device_vendor; }
			const String &getVersion() const { return device_version; }
			const String &getExtensions() const { return device_extensions; }
			
			/// check OpenCL device info
			bool checkExtension(const char *name);
			
		private:
			
			cl_platform_id platform = nullptr;
			cl_device_id device = nullptr;
			
			String device_name;
			String device_vendor;
			String device_version;
			String device_extensions;
	};
	
	/// OpenCL types
	typedef cl_int (CL_API_CALL *PFN_clGetPlatformIDs)(cl_uint num_entries, cl_platform_id* platforms, cl_uint* num_platforms);
	typedef cl_int (CL_API_CALL *PFN_clGetPlatformInfo)(cl_platform_id platform, cl_platform_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_int (CL_API_CALL *PFN_clGetDeviceIDs)(cl_platform_id platform, cl_device_type device_type, cl_uint num_entries, cl_device_id* devices, cl_uint* num_devices);
	typedef cl_int (CL_API_CALL *PFN_clGetDeviceInfo)(cl_device_id device, cl_device_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_int (CL_API_CALL *PFN_clCreateSubDevices)(cl_device_id in_device, const cl_device_partition_property* properties, cl_uint num_devices, cl_device_id* out_devices, cl_uint* num_devices_ret);
	typedef cl_int (CL_API_CALL *PFN_clRetainDevice)(cl_device_id device);
	typedef cl_int (CL_API_CALL *PFN_clReleaseDevice)(cl_device_id device);
	typedef cl_int (CL_API_CALL *PFN_clSetDefaultDeviceCommandQueue)(cl_context context, cl_device_id device, cl_command_queue command_queue);
	typedef cl_int (CL_API_CALL *PFN_clGetDeviceAndHostTimer)(cl_device_id device, cl_ulong* device_timestamp, cl_ulong* host_timestamp);
	typedef cl_int (CL_API_CALL *PFN_clGetHostTimer)(cl_device_id device, cl_ulong* host_timestamp);
	typedef cl_context (CL_API_CALL *PFN_clCreateContext)(const cl_context_properties* properties, cl_uint num_devices, const cl_device_id* devices, void (* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), void* user_data, cl_int* errcode_ret);
	typedef cl_context (CL_API_CALL *PFN_clCreateContextFromType)(const cl_context_properties* properties, cl_device_type device_type, void (* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), void* user_data, cl_int* errcode_ret);
	typedef cl_int (CL_API_CALL *PFN_clRetainContext)(cl_context context);
	typedef cl_int (CL_API_CALL *PFN_clReleaseContext)(cl_context context);
	typedef cl_int (CL_API_CALL *PFN_clGetContextInfo)(cl_context context, cl_context_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_int (CL_API_CALL *PFN_clSetContextDestructorCallback)(cl_context context, void (* pfn_notify)(cl_context context, void* user_data), void* user_data);
	typedef cl_command_queue (CL_API_CALL *PFN_clCreateCommandQueueWithProperties)(cl_context context, cl_device_id device, const cl_queue_properties* properties, cl_int* errcode_ret);
	typedef cl_int (CL_API_CALL *PFN_clRetainCommandQueue)(cl_command_queue command_queue);
	typedef cl_int (CL_API_CALL *PFN_clReleaseCommandQueue)(cl_command_queue command_queue);
	typedef cl_int (CL_API_CALL *PFN_clGetCommandQueueInfo)(cl_command_queue command_queue, cl_command_queue_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_mem (CL_API_CALL *PFN_clCreateBuffer)(cl_context context, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret);
	typedef cl_mem (CL_API_CALL *PFN_clCreateSubBuffer)(cl_mem buffer, cl_mem_flags flags, cl_buffer_create_type buffer_create_type, const void* buffer_create_info, cl_int* errcode_ret);
	typedef cl_mem (CL_API_CALL *PFN_clCreateImage)(cl_context context, cl_mem_flags flags, const cl_image_format* image_format, const cl_image_desc* image_desc, void* host_ptr, cl_int* errcode_ret);
	typedef cl_mem (CL_API_CALL *PFN_clCreatePipe)(cl_context context, cl_mem_flags flags, cl_uint pipe_packet_size, cl_uint pipe_max_packets, const cl_pipe_properties* properties, cl_int* errcode_ret);
	typedef cl_mem (CL_API_CALL *PFN_clCreateBufferWithProperties)(cl_context context, const cl_mem_properties* properties, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret);
	typedef cl_mem (CL_API_CALL *PFN_clCreateImageWithProperties)(cl_context context, const cl_mem_properties* properties, cl_mem_flags flags, const cl_image_format* image_format, const cl_image_desc* image_desc, void* host_ptr, cl_int* errcode_ret);
	typedef cl_int (CL_API_CALL *PFN_clRetainMemObject)(cl_mem memobj);
	typedef cl_int (CL_API_CALL *PFN_clReleaseMemObject)(cl_mem memobj);
	typedef cl_int (CL_API_CALL *PFN_clGetSupportedImageFormats)(cl_context context, cl_mem_flags flags, cl_mem_object_type image_type, cl_uint num_entries, cl_image_format* image_formats, cl_uint* num_image_formats);
	typedef cl_int (CL_API_CALL *PFN_clGetMemObjectInfo)(cl_mem memobj, cl_mem_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_int (CL_API_CALL *PFN_clGetImageInfo)(cl_mem image, cl_image_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_int (CL_API_CALL *PFN_clGetPipeInfo)(cl_mem pipe, cl_pipe_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_int (CL_API_CALL *PFN_clSetMemObjectDestructorCallback)(cl_mem memobj, void (* pfn_notify)(cl_mem memobj, void* user_data), void* user_data);
	typedef void * (CL_API_CALL *PFN_clSVMAlloc)(cl_context context, cl_svm_mem_flags flags, size_t size, cl_uint alignment);
	typedef void (CL_API_CALL *PFN_clSVMFree)(cl_context context, void* svm_pointer);
	typedef cl_sampler (CL_API_CALL *PFN_clCreateSamplerWithProperties)(cl_context context, const cl_sampler_properties* sampler_properties, cl_int* errcode_ret);
	typedef cl_int (CL_API_CALL *PFN_clRetainSampler)(cl_sampler sampler);
	typedef cl_int (CL_API_CALL *PFN_clReleaseSampler)(cl_sampler sampler);
	typedef cl_int (CL_API_CALL *PFN_clGetSamplerInfo)(cl_sampler sampler, cl_sampler_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_program (CL_API_CALL *PFN_clCreateProgramWithSource)(cl_context context, cl_uint count, const char ** strings, const size_t* lengths, cl_int* errcode_ret);
	typedef cl_program (CL_API_CALL *PFN_clCreateProgramWithBinary)(cl_context context, cl_uint num_devices, const cl_device_id* device_list, const size_t* lengths, const uint8_t ** binaries, cl_int* binary_status, cl_int* errcode_ret);
	typedef cl_program (CL_API_CALL *PFN_clCreateProgramWithBuiltInKernels)(cl_context context, cl_uint num_devices, const cl_device_id* device_list, const char* kernel_names, cl_int* errcode_ret);
	typedef cl_program (CL_API_CALL *PFN_clCreateProgramWithIL)(cl_context context, const void* il, size_t length, cl_int* errcode_ret);
	typedef cl_int (CL_API_CALL *PFN_clRetainProgram)(cl_program program);
	typedef cl_int (CL_API_CALL *PFN_clReleaseProgram)(cl_program program);
	typedef cl_int (CL_API_CALL *PFN_clBuildProgram)(cl_program program, cl_uint num_devices, const cl_device_id* device_list, const char* options, void (* pfn_notify)(cl_program program, void* user_data), void* user_data);
	typedef cl_int (CL_API_CALL *PFN_clCompileProgram)(cl_program program, cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_headers, const cl_program* input_headers, const char ** header_include_names, void (* pfn_notify)(cl_program program, void* user_data), void* user_data);
	typedef cl_program (CL_API_CALL *PFN_clLinkProgram)(cl_context context, cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_programs, const cl_program* input_programs, void (* pfn_notify)(cl_program program, void* user_data), void* user_data, cl_int* errcode_ret);
	typedef cl_int (CL_API_CALL *PFN_clSetProgramReleaseCallback)(cl_program program, void (* pfn_notify)(cl_program program, void* user_data), void* user_data);
	typedef cl_int (CL_API_CALL *PFN_clSetProgramSpecializationConstant)(cl_program program, cl_uint spec_id, size_t spec_size, const void* spec_value);
	typedef cl_int (CL_API_CALL *PFN_clUnloadPlatformCompiler)(cl_platform_id platform);
	typedef cl_int (CL_API_CALL *PFN_clGetProgramInfo)(cl_program program, cl_program_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_int (CL_API_CALL *PFN_clGetProgramBuildInfo)(cl_program program, cl_device_id device, cl_program_build_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_kernel (CL_API_CALL *PFN_clCreateKernel)(cl_program program, const char* kernel_name, cl_int* errcode_ret);
	typedef cl_int (CL_API_CALL *PFN_clCreateKernelsInProgram)(cl_program program, cl_uint num_kernels, cl_kernel* kernels, cl_uint* num_kernels_ret);
	typedef cl_kernel (CL_API_CALL *PFN_clCloneKernel)(cl_kernel source_kernel, cl_int* errcode_ret);
	typedef cl_int (CL_API_CALL *PFN_clRetainKernel)(cl_kernel kernel);
	typedef cl_int (CL_API_CALL *PFN_clReleaseKernel)(cl_kernel kernel);
	typedef cl_int (CL_API_CALL *PFN_clSetKernelArg)(cl_kernel kernel, cl_uint arg_index, size_t arg_size, const void* arg_value);
	typedef cl_int (CL_API_CALL *PFN_clSetKernelArgSVMPointer)(cl_kernel kernel, cl_uint arg_index, const void* arg_value);
	typedef cl_int (CL_API_CALL *PFN_clSetKernelExecInfo)(cl_kernel kernel, cl_kernel_exec_info param_name, size_t param_value_size, const void* param_value);
	typedef cl_int (CL_API_CALL *PFN_clGetKernelInfo)(cl_kernel kernel, cl_kernel_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_int (CL_API_CALL *PFN_clGetKernelArgInfo)(cl_kernel kernel, cl_uint arg_indx, cl_kernel_arg_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_int (CL_API_CALL *PFN_clGetKernelWorkGroupInfo)(cl_kernel kernel, cl_device_id device, cl_kernel_work_group_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_int (CL_API_CALL *PFN_clGetKernelSubGroupInfo)(cl_kernel kernel, cl_device_id device, cl_kernel_sub_group_info param_name, size_t input_value_size, const void* input_value, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_int (CL_API_CALL *PFN_clWaitForEvents)(cl_uint num_events, const cl_event* event_list);
	typedef cl_int (CL_API_CALL *PFN_clGetEventInfo)(cl_event event, cl_event_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_event (CL_API_CALL *PFN_clCreateUserEvent)(cl_context context, cl_int* errcode_ret);
	typedef cl_int (CL_API_CALL *PFN_clRetainEvent)(cl_event event);
	typedef cl_int (CL_API_CALL *PFN_clReleaseEvent)(cl_event event);
	typedef cl_int (CL_API_CALL *PFN_clSetUserEventStatus)(cl_event event, cl_int execution_status);
	typedef cl_int (CL_API_CALL *PFN_clSetEventCallback)(cl_event event, cl_int command_exec_callback_type, void (* pfn_notify)(cl_event event, cl_int event_command_status, void* user_data), void* user_data);
	typedef cl_int (CL_API_CALL *PFN_clGetEventProfilingInfo)(cl_event event, cl_profiling_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_int (CL_API_CALL *PFN_clFlush)(cl_command_queue command_queue);
	typedef cl_int (CL_API_CALL *PFN_clFinish)(cl_command_queue command_queue);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueReadBuffer)(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueReadBufferRect)(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_origin, const size_t* host_origin, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueWriteBuffer)(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueWriteBufferRect)(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_origin, const size_t* host_origin, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueFillBuffer)(cl_command_queue command_queue, cl_mem buffer, const void* pattern, size_t pattern_size, size_t offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueCopyBuffer)(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, size_t src_offset, size_t dst_offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueCopyBufferRect)(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, const size_t* src_origin, const size_t* dst_origin, const size_t* region, size_t src_row_pitch, size_t src_slice_pitch, size_t dst_row_pitch, size_t dst_slice_pitch, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueReadImage)(cl_command_queue command_queue, cl_mem image, cl_bool blocking_read, const size_t* origin, const size_t* region, size_t row_pitch, size_t slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueWriteImage)(cl_command_queue command_queue, cl_mem image, cl_bool blocking_write, const size_t* origin, const size_t* region, size_t input_row_pitch, size_t input_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueFillImage)(cl_command_queue command_queue, cl_mem image, const void* fill_color, const size_t* origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueCopyImage)(cl_command_queue command_queue, cl_mem src_image, cl_mem dst_image, const size_t* src_origin, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueCopyImageToBuffer)(cl_command_queue command_queue, cl_mem src_image, cl_mem dst_buffer, const size_t* src_origin, const size_t* region, size_t dst_offset, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueCopyBufferToImage)(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_image, size_t src_offset, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef void * (CL_API_CALL *PFN_clEnqueueMapBuffer)(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_map, cl_map_flags map_flags, size_t offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event, cl_int* errcode_ret);
	typedef void * (CL_API_CALL *PFN_clEnqueueMapImage)(cl_command_queue command_queue, cl_mem image, cl_bool blocking_map, cl_map_flags map_flags, const size_t* origin, const size_t* region, size_t* image_row_pitch, size_t* image_slice_pitch, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event, cl_int* errcode_ret);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueUnmapMemObject)(cl_command_queue command_queue, cl_mem memobj, void* mapped_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueMigrateMemObjects)(cl_command_queue command_queue, cl_uint num_mem_objects, const cl_mem* mem_objects, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueNDRangeKernel)(cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t* global_work_offset, const size_t* global_work_size, const size_t* local_work_size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueNativeKernel)(cl_command_queue command_queue, void (* user_func)(void *), void* args, size_t cb_args, cl_uint num_mem_objects, const cl_mem* mem_list, const void ** args_mem_loc, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueMarkerWithWaitList)(cl_command_queue command_queue, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueBarrierWithWaitList)(cl_command_queue command_queue, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueSVMMemcpy)(cl_command_queue command_queue, cl_bool blocking_copy, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueSVMMemFill)(cl_command_queue command_queue, void* svm_ptr, const void* pattern, size_t pattern_size, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueSVMMap)(cl_command_queue command_queue, cl_bool blocking_map, cl_map_flags flags, void* svm_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueSVMUnmap)(cl_command_queue command_queue, void* svm_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueSVMMigrateMem)(cl_command_queue command_queue, cl_uint num_svm_pointers, const void ** svm_pointers, const size_t* sizes, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef void * (CL_API_CALL *PFN_clGetExtensionFunctionAddressForPlatform)(cl_platform_id platform, const char* func_name);
	typedef cl_mem (CL_API_CALL *PFN_clCreateImage2D)(cl_context context, cl_mem_flags flags, const cl_image_format* image_format, size_t image_width, size_t image_height, size_t image_row_pitch, void* host_ptr, cl_int* errcode_ret);
	typedef cl_mem (CL_API_CALL *PFN_clCreateImage3D)(cl_context context, cl_mem_flags flags, const cl_image_format* image_format, size_t image_width, size_t image_height, size_t image_depth, size_t image_row_pitch, size_t image_slice_pitch, void* host_ptr, cl_int* errcode_ret);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueMarker)(cl_command_queue command_queue, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueWaitForEvents)(cl_command_queue command_queue, cl_uint num_events, const cl_event* event_list);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueBarrier)(cl_command_queue command_queue);
	typedef cl_int (CL_API_CALL *PFN_clUnloadCompiler)(void);
	typedef void * (CL_API_CALL *PFN_clGetExtensionFunctionAddress)(const char* func_name);
	typedef cl_command_queue (CL_API_CALL *PFN_clCreateCommandQueue)(cl_context context, cl_device_id device, cl_command_queue_properties properties, cl_int* errcode_ret);
	typedef cl_sampler (CL_API_CALL *PFN_clCreateSampler)(cl_context context, cl_bool normalized_coords, cl_addressing_mode addressing_mode, cl_filter_mode filter_mode, cl_int* errcode_ret);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueTask)(cl_command_queue command_queue, cl_kernel kernel, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	
	/// OpenCL extension types
	typedef cl_int (CL_API_CALL *PFN_clGetGLContextInfoKHR)(const cl_context_properties* properties, cl_gl_context_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_mem (CL_API_CALL *PFN_clCreateFromGLBuffer)(cl_context context, cl_mem_flags flags, cl_GLuint bufobj, cl_int* errcode_ret);
	typedef cl_mem (CL_API_CALL *PFN_clCreateFromGLTexture)(cl_context context, cl_mem_flags flags, cl_GLenum target, cl_GLint miplevel, cl_GLuint texture, cl_int* errcode_ret);
	typedef cl_mem (CL_API_CALL *PFN_clCreateFromGLRenderbuffer)(cl_context context, cl_mem_flags flags, cl_GLuint renderbuffer, cl_int* errcode_ret);
	typedef cl_int (CL_API_CALL *PFN_clGetGLObjectInfo)(cl_mem memobj, cl_gl_object_type* gl_object_type, cl_GLuint* gl_object_name);
	typedef cl_int (CL_API_CALL *PFN_clGetGLTextureInfo)(cl_mem memobj, cl_gl_texture_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueAcquireGLObjects)(cl_command_queue command_queue, cl_uint num_objects, const cl_mem* mem_objects, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueReleaseGLObjects)(cl_command_queue command_queue, cl_uint num_objects, const cl_mem* mem_objects, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_mem (CL_API_CALL *PFN_clCreateFromGLTexture2D)(cl_context context, cl_mem_flags flags, cl_GLenum target, cl_GLint miplevel, cl_GLuint texture, cl_int* errcode_ret);
	typedef cl_mem (CL_API_CALL *PFN_clCreateFromGLTexture3D)(cl_context context, cl_mem_flags flags, cl_GLenum target, cl_GLint miplevel, cl_GLuint texture, cl_int* errcode_ret);
	typedef cl_event (CL_API_CALL *PFN_clCreateEventFromGLsyncKHR)(cl_context context, cl_GLsync sync, cl_int* errcode_ret);
	typedef cl_int (CL_API_CALL *PFN_clGetSupportedGLTextureFormatsINTEL)(cl_context context, cl_mem_flags flags, cl_mem_object_type image_type, cl_uint num_entries, cl_GLenum* gl_formats, cl_uint* num_texture_formats);
	typedef cl_int (CL_API_CALL *PFN_clSetMemObjectDestructorAPPLE)(cl_mem memobj, void (* pfn_notify)(cl_mem memobj, void* user_data), void* user_data);
	typedef void (CL_API_CALL *PFN_clLogMessagesToSystemLogAPPLE)(const char* errstr, const void* private_info, size_t cb, void* user_data);
	typedef void (CL_API_CALL *PFN_clLogMessagesToStdoutAPPLE)(const char* errstr, const void* private_info, size_t cb, void* user_data);
	typedef void (CL_API_CALL *PFN_clLogMessagesToStderrAPPLE)(const char* errstr, const void* private_info, size_t cb, void* user_data);
	typedef cl_int (CL_API_CALL *PFN_clIcdGetPlatformIDsKHR)(cl_uint num_entries, cl_platform_id* platforms, cl_uint* num_platforms);
	typedef void* (CL_API_CALL *PFN_clIcdGetFunctionAddressForPlatformKHR)(cl_platform_id platform, const char* func_name);
	typedef cl_int (CL_API_CALL *PFN_clIcdSetPlatformDispatchDataKHR)(cl_platform_id platform, void* dispatch_data);
	typedef cl_program (CL_API_CALL *PFN_clCreateProgramWithILKHR)(cl_context context, const void* il, size_t length, cl_int* errcode_ret);
	typedef cl_int (CL_API_CALL *PFN_clTerminateContextKHR)(cl_context context);
	typedef cl_command_queue (CL_API_CALL *PFN_clCreateCommandQueueWithPropertiesKHR)(cl_context context, cl_device_id device, const cl_queue_properties_khr* properties, cl_int* errcode_ret);
	typedef cl_int (CL_API_CALL *PFN_clReleaseDeviceEXT)(cl_device_id device);
	typedef cl_int (CL_API_CALL *PFN_clRetainDeviceEXT)(cl_device_id device);
	typedef cl_int (CL_API_CALL *PFN_clCreateSubDevicesEXT)(cl_device_id in_device, const cl_device_partition_property_ext* properties, cl_uint num_entries, cl_device_id* out_devices, cl_uint* num_devices);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueMigrateMemObjectEXT)(cl_command_queue command_queue, cl_uint num_mem_objects, const cl_mem* mem_objects, cl_mem_migration_flags_ext flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clGetDeviceImageInfoQCOM)(cl_device_id device, size_t image_width, size_t image_height, const cl_image_format* image_format, cl_image_pitch_info_qcom param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueAcquireGrallocObjectsIMG)(cl_command_queue command_queue, cl_uint num_objects, const cl_mem* mem_objects, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueReleaseGrallocObjectsIMG)(cl_command_queue command_queue, cl_uint num_objects, const cl_mem* mem_objects, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueGenerateMipmapIMG)(cl_command_queue command_queue, cl_mem src_image, cl_mem dst_image, cl_mipmap_filter_mode_img mipmap_filter_mode, const size_t* array_region, const size_t* mip_region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clGetKernelSubGroupInfoKHR)(cl_kernel in_kernel, cl_device_id in_device, cl_kernel_sub_group_info param_name, size_t input_value_size, const void* input_value, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_int (CL_API_CALL *PFN_clGetKernelSuggestedLocalWorkSizeKHR)(cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t* global_work_offset, const size_t* global_work_size, size_t* suggested_local_work_size);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueAcquireExternalMemObjectsKHR)(cl_command_queue command_queue, cl_uint num_mem_objects, const cl_mem* mem_objects, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueReleaseExternalMemObjectsKHR)(cl_command_queue command_queue, cl_uint num_mem_objects, const cl_mem* mem_objects, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clGetSemaphoreHandleForTypeKHR)(cl_semaphore_khr sema_object, cl_device_id device, cl_external_semaphore_handle_type_khr handle_type, size_t handle_size, void* handle_ptr, size_t* handle_size_ret);
	typedef cl_int (CL_API_CALL *PFN_clReImportSemaphoreSyncFdKHR)(cl_semaphore_khr sema_object, cl_semaphore_reimport_properties_khr* reimport_props, int32_t fd);
	typedef cl_semaphore_khr (CL_API_CALL *PFN_clCreateSemaphoreWithPropertiesKHR)(cl_context context, const cl_semaphore_properties_khr* sema_props, cl_int* errcode_ret);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueWaitSemaphoresKHR)(cl_command_queue command_queue, cl_uint num_sema_objects, const cl_semaphore_khr* sema_objects, const cl_semaphore_payload_khr* sema_payload_list, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueSignalSemaphoresKHR)(cl_command_queue command_queue, cl_uint num_sema_objects, const cl_semaphore_khr* sema_objects, const cl_semaphore_payload_khr* sema_payload_list, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clGetSemaphoreInfoKHR)(cl_semaphore_khr sema_object, cl_semaphore_info_khr param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_int (CL_API_CALL *PFN_clReleaseSemaphoreKHR)(cl_semaphore_khr sema_object);
	typedef cl_int (CL_API_CALL *PFN_clRetainSemaphoreKHR)(cl_semaphore_khr sema_object);
	typedef cl_mem (CL_API_CALL *PFN_clImportMemoryARM)(cl_context context, cl_mem_flags flags, const cl_import_properties_arm* properties, void* memory, size_t size, cl_int* errcode_ret);
	typedef void* (CL_API_CALL *PFN_clSVMAllocARM)(cl_context context, cl_svm_mem_flags_arm flags, size_t size, cl_uint alignment);
	typedef void (CL_API_CALL *PFN_clSVMFreeARM)(cl_context context, void* svm_pointer);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueSVMMemcpyARM)(cl_command_queue command_queue, cl_bool blocking_copy, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueSVMMemFillARM)(cl_command_queue command_queue, void* svm_ptr, const void* pattern, size_t pattern_size, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueSVMMapARM)(cl_command_queue command_queue, cl_bool blocking_map, cl_map_flags flags, void* svm_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueSVMUnmapARM)(cl_command_queue command_queue, void* svm_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clSetKernelArgSVMPointerARM)(cl_kernel kernel, cl_uint arg_index, const void* arg_value);
	typedef cl_int (CL_API_CALL *PFN_clSetKernelExecInfoARM)(cl_kernel kernel, cl_kernel_exec_info_arm param_name, size_t param_value_size, const void* param_value);
	typedef cl_accelerator_intel (CL_API_CALL *PFN_clCreateAcceleratorINTEL)(cl_context context, cl_accelerator_type_intel accelerator_type, size_t descriptor_size, const void* descriptor, cl_int* errcode_ret);
	typedef cl_int (CL_API_CALL *PFN_clGetAcceleratorInfoINTEL)(cl_accelerator_intel accelerator, cl_accelerator_info_intel param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_int (CL_API_CALL *PFN_clRetainAcceleratorINTEL)(cl_accelerator_intel accelerator);
	typedef cl_int (CL_API_CALL *PFN_clReleaseAcceleratorINTEL)(cl_accelerator_intel accelerator);
	typedef void* (CL_API_CALL *PFN_clHostMemAllocINTEL)(cl_context context, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret);
	typedef void* (CL_API_CALL *PFN_clDeviceMemAllocINTEL)(cl_context context, cl_device_id device, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret);
	typedef void* (CL_API_CALL *PFN_clSharedMemAllocINTEL)(cl_context context, cl_device_id device, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret);
	typedef cl_int (CL_API_CALL *PFN_clMemFreeINTEL)(cl_context context, void* ptr);
	typedef cl_int (CL_API_CALL *PFN_clMemBlockingFreeINTEL)(cl_context context, void* ptr);
	typedef cl_int (CL_API_CALL *PFN_clGetMemAllocInfoINTEL)(cl_context context, const void* ptr, cl_mem_info_intel param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_int (CL_API_CALL *PFN_clSetKernelArgMemPointerINTEL)(cl_kernel kernel, cl_uint arg_index, const void* arg_value);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueMemFillINTEL)(cl_command_queue command_queue, void* dst_ptr, const void* pattern, size_t pattern_size, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueMemcpyINTEL)(cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueMemAdviseINTEL)(cl_command_queue command_queue, const void* ptr, size_t size, cl_mem_advice_intel advice, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueMigrateMemINTEL)(cl_command_queue command_queue, const void* ptr, size_t size, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueMemsetINTEL)(cl_command_queue command_queue, void* dst_ptr, cl_int value, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_mem (CL_API_CALL *PFN_clCreateBufferWithPropertiesINTEL)(cl_context context, const cl_mem_properties_intel* properties, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueReadHostPipeINTEL)(cl_command_queue command_queue, cl_program program, const char* pipe_symbol, cl_bool blocking_read, void* ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clEnqueueWriteHostPipeINTEL)(cl_command_queue command_queue, cl_program program, const char* pipe_symbol, cl_bool blocking_write, const void* ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	typedef cl_int (CL_API_CALL *PFN_clGetImageRequirementsInfoEXT)(cl_context context, const cl_mem_properties* properties, cl_mem_flags flags, const cl_image_format* image_format, const cl_image_desc* image_desc, cl_image_requirements_info_ext param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_int (CL_API_CALL *PFN_clGetICDLoaderInfoOCLICD)(cl_icdl_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	typedef cl_int (CL_API_CALL *PFN_clSetContentSizeBufferPoCL)(cl_mem buffer, cl_mem content_size_buffer);
	typedef cl_int (CL_API_CALL *PFN_clSetKernelArgDevicePointerEXT)(cl_kernel kernel, cl_uint arg_index, cl_mem_device_address_ext arg_value);
	typedef cl_int (CL_API_CALL *PFN_clCancelCommandsIMG)(const cl_event* event_list, size_t num_events_in_list);
	typedef cl_int (CL_API_CALL *PFN_clSetPerfHintQCOM)(cl_context context, cl_perf_hint_qcom perf_hint);
	
	/// OpenCL functions
	extern PFN_clGetPlatformIDs clGetPlatformIDs;
	extern PFN_clGetPlatformInfo clGetPlatformInfo;
	extern PFN_clGetDeviceIDs clGetDeviceIDs;
	extern PFN_clGetDeviceInfo clGetDeviceInfo;
	extern PFN_clCreateSubDevices clCreateSubDevices;
	extern PFN_clRetainDevice clRetainDevice;
	extern PFN_clReleaseDevice clReleaseDevice;
	extern PFN_clSetDefaultDeviceCommandQueue clSetDefaultDeviceCommandQueue;
	extern PFN_clGetDeviceAndHostTimer clGetDeviceAndHostTimer;
	extern PFN_clGetHostTimer clGetHostTimer;
	extern PFN_clCreateContext clCreateContext;
	extern PFN_clCreateContextFromType clCreateContextFromType;
	extern PFN_clRetainContext clRetainContext;
	extern PFN_clReleaseContext clReleaseContext;
	extern PFN_clGetContextInfo clGetContextInfo;
	extern PFN_clSetContextDestructorCallback clSetContextDestructorCallback;
	extern PFN_clCreateCommandQueueWithProperties clCreateCommandQueueWithProperties;
	extern PFN_clRetainCommandQueue clRetainCommandQueue;
	extern PFN_clReleaseCommandQueue clReleaseCommandQueue;
	extern PFN_clGetCommandQueueInfo clGetCommandQueueInfo;
	extern PFN_clCreateBuffer clCreateBuffer;
	extern PFN_clCreateSubBuffer clCreateSubBuffer;
	extern PFN_clCreateImage clCreateImage;
	extern PFN_clCreatePipe clCreatePipe;
	extern PFN_clCreateBufferWithProperties clCreateBufferWithProperties;
	extern PFN_clCreateImageWithProperties clCreateImageWithProperties;
	extern PFN_clRetainMemObject clRetainMemObject;
	extern PFN_clReleaseMemObject clReleaseMemObject;
	extern PFN_clGetSupportedImageFormats clGetSupportedImageFormats;
	extern PFN_clGetMemObjectInfo clGetMemObjectInfo;
	extern PFN_clGetImageInfo clGetImageInfo;
	extern PFN_clGetPipeInfo clGetPipeInfo;
	extern PFN_clSetMemObjectDestructorCallback clSetMemObjectDestructorCallback;
	extern PFN_clSVMAlloc clSVMAlloc;
	extern PFN_clSVMFree clSVMFree;
	extern PFN_clCreateSamplerWithProperties clCreateSamplerWithProperties;
	extern PFN_clRetainSampler clRetainSampler;
	extern PFN_clReleaseSampler clReleaseSampler;
	extern PFN_clGetSamplerInfo clGetSamplerInfo;
	extern PFN_clCreateProgramWithSource clCreateProgramWithSource;
	extern PFN_clCreateProgramWithBinary clCreateProgramWithBinary;
	extern PFN_clCreateProgramWithBuiltInKernels clCreateProgramWithBuiltInKernels;
	extern PFN_clCreateProgramWithIL clCreateProgramWithIL;
	extern PFN_clRetainProgram clRetainProgram;
	extern PFN_clReleaseProgram clReleaseProgram;
	extern PFN_clBuildProgram clBuildProgram;
	extern PFN_clCompileProgram clCompileProgram;
	extern PFN_clLinkProgram clLinkProgram;
	extern PFN_clSetProgramReleaseCallback clSetProgramReleaseCallback;
	extern PFN_clSetProgramSpecializationConstant clSetProgramSpecializationConstant;
	extern PFN_clUnloadPlatformCompiler clUnloadPlatformCompiler;
	extern PFN_clGetProgramInfo clGetProgramInfo;
	extern PFN_clGetProgramBuildInfo clGetProgramBuildInfo;
	extern PFN_clCreateKernel clCreateKernel;
	extern PFN_clCreateKernelsInProgram clCreateKernelsInProgram;
	extern PFN_clCloneKernel clCloneKernel;
	extern PFN_clRetainKernel clRetainKernel;
	extern PFN_clReleaseKernel clReleaseKernel;
	extern PFN_clSetKernelArg clSetKernelArg;
	extern PFN_clSetKernelArgSVMPointer clSetKernelArgSVMPointer;
	extern PFN_clSetKernelExecInfo clSetKernelExecInfo;
	extern PFN_clGetKernelInfo clGetKernelInfo;
	extern PFN_clGetKernelArgInfo clGetKernelArgInfo;
	extern PFN_clGetKernelWorkGroupInfo clGetKernelWorkGroupInfo;
	extern PFN_clGetKernelSubGroupInfo clGetKernelSubGroupInfo;
	extern PFN_clWaitForEvents clWaitForEvents;
	extern PFN_clGetEventInfo clGetEventInfo;
	extern PFN_clCreateUserEvent clCreateUserEvent;
	extern PFN_clRetainEvent clRetainEvent;
	extern PFN_clReleaseEvent clReleaseEvent;
	extern PFN_clSetUserEventStatus clSetUserEventStatus;
	extern PFN_clSetEventCallback clSetEventCallback;
	extern PFN_clGetEventProfilingInfo clGetEventProfilingInfo;
	extern PFN_clFlush clFlush;
	extern PFN_clFinish clFinish;
	extern PFN_clEnqueueReadBuffer clEnqueueReadBuffer;
	extern PFN_clEnqueueReadBufferRect clEnqueueReadBufferRect;
	extern PFN_clEnqueueWriteBuffer clEnqueueWriteBuffer;
	extern PFN_clEnqueueWriteBufferRect clEnqueueWriteBufferRect;
	extern PFN_clEnqueueFillBuffer clEnqueueFillBuffer;
	extern PFN_clEnqueueCopyBuffer clEnqueueCopyBuffer;
	extern PFN_clEnqueueCopyBufferRect clEnqueueCopyBufferRect;
	extern PFN_clEnqueueReadImage clEnqueueReadImage;
	extern PFN_clEnqueueWriteImage clEnqueueWriteImage;
	extern PFN_clEnqueueFillImage clEnqueueFillImage;
	extern PFN_clEnqueueCopyImage clEnqueueCopyImage;
	extern PFN_clEnqueueCopyImageToBuffer clEnqueueCopyImageToBuffer;
	extern PFN_clEnqueueCopyBufferToImage clEnqueueCopyBufferToImage;
	extern PFN_clEnqueueMapBuffer clEnqueueMapBuffer;
	extern PFN_clEnqueueMapImage clEnqueueMapImage;
	extern PFN_clEnqueueUnmapMemObject clEnqueueUnmapMemObject;
	extern PFN_clEnqueueMigrateMemObjects clEnqueueMigrateMemObjects;
	extern PFN_clEnqueueNDRangeKernel clEnqueueNDRangeKernel;
	extern PFN_clEnqueueNativeKernel clEnqueueNativeKernel;
	extern PFN_clEnqueueMarkerWithWaitList clEnqueueMarkerWithWaitList;
	extern PFN_clEnqueueBarrierWithWaitList clEnqueueBarrierWithWaitList;
	extern PFN_clEnqueueSVMMemcpy clEnqueueSVMMemcpy;
	extern PFN_clEnqueueSVMMemFill clEnqueueSVMMemFill;
	extern PFN_clEnqueueSVMMap clEnqueueSVMMap;
	extern PFN_clEnqueueSVMUnmap clEnqueueSVMUnmap;
	extern PFN_clEnqueueSVMMigrateMem clEnqueueSVMMigrateMem;
	extern PFN_clGetExtensionFunctionAddressForPlatform clGetExtensionFunctionAddressForPlatform;
	extern PFN_clCreateImage2D clCreateImage2D;
	extern PFN_clCreateImage3D clCreateImage3D;
	extern PFN_clEnqueueMarker clEnqueueMarker;
	extern PFN_clEnqueueWaitForEvents clEnqueueWaitForEvents;
	extern PFN_clEnqueueBarrier clEnqueueBarrier;
	extern PFN_clUnloadCompiler clUnloadCompiler;
	extern PFN_clGetExtensionFunctionAddress clGetExtensionFunctionAddress;
	extern PFN_clCreateCommandQueue clCreateCommandQueue;
	extern PFN_clCreateSampler clCreateSampler;
	extern PFN_clEnqueueTask clEnqueueTask;
	
	/// OpenCL extension functions
	extern PFN_clGetGLContextInfoKHR clGetGLContextInfoKHR;
	extern PFN_clCreateFromGLBuffer clCreateFromGLBuffer;
	extern PFN_clCreateFromGLTexture clCreateFromGLTexture;
	extern PFN_clCreateFromGLRenderbuffer clCreateFromGLRenderbuffer;
	extern PFN_clGetGLObjectInfo clGetGLObjectInfo;
	extern PFN_clGetGLTextureInfo clGetGLTextureInfo;
	extern PFN_clEnqueueAcquireGLObjects clEnqueueAcquireGLObjects;
	extern PFN_clEnqueueReleaseGLObjects clEnqueueReleaseGLObjects;
	extern PFN_clCreateFromGLTexture2D clCreateFromGLTexture2D;
	extern PFN_clCreateFromGLTexture3D clCreateFromGLTexture3D;
	extern PFN_clCreateEventFromGLsyncKHR clCreateEventFromGLsyncKHR;
	extern PFN_clGetSupportedGLTextureFormatsINTEL clGetSupportedGLTextureFormatsINTEL;
	extern PFN_clSetMemObjectDestructorAPPLE clSetMemObjectDestructorAPPLE;
	extern PFN_clLogMessagesToSystemLogAPPLE clLogMessagesToSystemLogAPPLE;
	extern PFN_clLogMessagesToStdoutAPPLE clLogMessagesToStdoutAPPLE;
	extern PFN_clLogMessagesToStderrAPPLE clLogMessagesToStderrAPPLE;
	extern PFN_clIcdGetPlatformIDsKHR clIcdGetPlatformIDsKHR;
	extern PFN_clIcdGetFunctionAddressForPlatformKHR clIcdGetFunctionAddressForPlatformKHR;
	extern PFN_clIcdSetPlatformDispatchDataKHR clIcdSetPlatformDispatchDataKHR;
	extern PFN_clCreateProgramWithILKHR clCreateProgramWithILKHR;
	extern PFN_clTerminateContextKHR clTerminateContextKHR;
	extern PFN_clCreateCommandQueueWithPropertiesKHR clCreateCommandQueueWithPropertiesKHR;
	extern PFN_clReleaseDeviceEXT clReleaseDeviceEXT;
	extern PFN_clRetainDeviceEXT clRetainDeviceEXT;
	extern PFN_clCreateSubDevicesEXT clCreateSubDevicesEXT;
	extern PFN_clEnqueueMigrateMemObjectEXT clEnqueueMigrateMemObjectEXT;
	extern PFN_clGetDeviceImageInfoQCOM clGetDeviceImageInfoQCOM;
	extern PFN_clEnqueueAcquireGrallocObjectsIMG clEnqueueAcquireGrallocObjectsIMG;
	extern PFN_clEnqueueReleaseGrallocObjectsIMG clEnqueueReleaseGrallocObjectsIMG;
	extern PFN_clEnqueueGenerateMipmapIMG clEnqueueGenerateMipmapIMG;
	extern PFN_clGetKernelSubGroupInfoKHR clGetKernelSubGroupInfoKHR;
	extern PFN_clGetKernelSuggestedLocalWorkSizeKHR clGetKernelSuggestedLocalWorkSizeKHR;
	extern PFN_clEnqueueAcquireExternalMemObjectsKHR clEnqueueAcquireExternalMemObjectsKHR;
	extern PFN_clEnqueueReleaseExternalMemObjectsKHR clEnqueueReleaseExternalMemObjectsKHR;
	extern PFN_clGetSemaphoreHandleForTypeKHR clGetSemaphoreHandleForTypeKHR;
	extern PFN_clReImportSemaphoreSyncFdKHR clReImportSemaphoreSyncFdKHR;
	extern PFN_clCreateSemaphoreWithPropertiesKHR clCreateSemaphoreWithPropertiesKHR;
	extern PFN_clEnqueueWaitSemaphoresKHR clEnqueueWaitSemaphoresKHR;
	extern PFN_clEnqueueSignalSemaphoresKHR clEnqueueSignalSemaphoresKHR;
	extern PFN_clGetSemaphoreInfoKHR clGetSemaphoreInfoKHR;
	extern PFN_clReleaseSemaphoreKHR clReleaseSemaphoreKHR;
	extern PFN_clRetainSemaphoreKHR clRetainSemaphoreKHR;
	extern PFN_clImportMemoryARM clImportMemoryARM;
	extern PFN_clSVMAllocARM clSVMAllocARM;
	extern PFN_clSVMFreeARM clSVMFreeARM;
	extern PFN_clEnqueueSVMMemcpyARM clEnqueueSVMMemcpyARM;
	extern PFN_clEnqueueSVMMemFillARM clEnqueueSVMMemFillARM;
	extern PFN_clEnqueueSVMMapARM clEnqueueSVMMapARM;
	extern PFN_clEnqueueSVMUnmapARM clEnqueueSVMUnmapARM;
	extern PFN_clSetKernelArgSVMPointerARM clSetKernelArgSVMPointerARM;
	extern PFN_clSetKernelExecInfoARM clSetKernelExecInfoARM;
	extern PFN_clCreateAcceleratorINTEL clCreateAcceleratorINTEL;
	extern PFN_clGetAcceleratorInfoINTEL clGetAcceleratorInfoINTEL;
	extern PFN_clRetainAcceleratorINTEL clRetainAcceleratorINTEL;
	extern PFN_clReleaseAcceleratorINTEL clReleaseAcceleratorINTEL;
	extern PFN_clHostMemAllocINTEL clHostMemAllocINTEL;
	extern PFN_clDeviceMemAllocINTEL clDeviceMemAllocINTEL;
	extern PFN_clSharedMemAllocINTEL clSharedMemAllocINTEL;
	extern PFN_clMemFreeINTEL clMemFreeINTEL;
	extern PFN_clMemBlockingFreeINTEL clMemBlockingFreeINTEL;
	extern PFN_clGetMemAllocInfoINTEL clGetMemAllocInfoINTEL;
	extern PFN_clSetKernelArgMemPointerINTEL clSetKernelArgMemPointerINTEL;
	extern PFN_clEnqueueMemFillINTEL clEnqueueMemFillINTEL;
	extern PFN_clEnqueueMemcpyINTEL clEnqueueMemcpyINTEL;
	extern PFN_clEnqueueMemAdviseINTEL clEnqueueMemAdviseINTEL;
	extern PFN_clEnqueueMigrateMemINTEL clEnqueueMigrateMemINTEL;
	extern PFN_clEnqueueMemsetINTEL clEnqueueMemsetINTEL;
	extern PFN_clCreateBufferWithPropertiesINTEL clCreateBufferWithPropertiesINTEL;
	extern PFN_clEnqueueReadHostPipeINTEL clEnqueueReadHostPipeINTEL;
	extern PFN_clEnqueueWriteHostPipeINTEL clEnqueueWriteHostPipeINTEL;
	extern PFN_clGetImageRequirementsInfoEXT clGetImageRequirementsInfoEXT;
	extern PFN_clGetICDLoaderInfoOCLICD clGetICDLoaderInfoOCLICD;
	extern PFN_clSetContentSizeBufferPoCL clSetContentSizeBufferPoCL;
	extern PFN_clSetKernelArgDevicePointerEXT clSetKernelArgDevicePointerEXT;
	extern PFN_clCancelCommandsIMG clCancelCommandsIMG;
	extern PFN_clSetPerfHintQCOM clSetPerfHintQCOM;
}

#endif /* __TELLUSIM_PLUGINS_PLATFORM_CL_H__ */

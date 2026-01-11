// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimMath.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimCompute.h>
#include <platform/TellusimContext.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// create app
	App app(argc, argv);
	if(!app.create()) return 1;
	
	// create context
	Context context(app.getPlatform(), app.getDevice());
	if(!context || !context.create()) return 1;
	
	// create device
	Device device(context);
	if(!device) return 1;
	
	// check compute shader support
	if(!device.hasShader(Shader::TypeCompute)) {
		TS_LOG(Error, "compute shader is not supported\n");
		return 0;
	}
	
	// check subgroup math support
	const Device::Features &features = device.getFeatures();
	if(features.subgroupSize == 0 || !features.subgroupMath) {
		TS_LOG(Error, "subgroup math is not supported\n");
		return 0;
	}
	
	// print device info
	TS_LOGF(Message, "%s (%s)\n", device.getName().get(), device.getPlatformName());
	TS_LOGF(Message, "subgroupSize: %u (%u %u)\n", features.subgroupSize, features.minSubgroupSize, features.maxSubgroupSize);
	
	// create kernel
	constexpr uint32_t size = 128;
	Kernel kernel = device.createKernel().setStorages(1);
	if(!kernel.loadShaderGLSL("main.shader", "COMPUTE_SHADER=1; GROUP_SIZE=%uu; SIZE=%uu", features.subgroupSize, size)) return 1;
	if(!kernel.create()) return 1;
	
	// create buffer
	Buffer storage_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagSource, sizeof(Vector4u) * size * 4);
	if(!storage_buffer) return 1;
	
	{
		// create command list
		Compute compute = device.createCompute();
		
		// run kernel
		compute.setKernel(kernel);
		compute.setStorageBuffer(0, storage_buffer);
		compute.dispatch(size);
		
		// buffer barrier
		compute.barrier(storage_buffer);
	}
	
	// flush context
	context.flush();
	
	// get buffer
	Array<Vector4u> data(size * 4);
	if(!device.getBuffer(storage_buffer, data.get())) return 1;
	
	// print buffer
	auto print = [&](const char *name, uint32_t offset, uint32_t index) {
		
		// subgroup parameters
		bool mode_add = (strstr(name, "Add") != nullptr);
		bool mode_mul = (strstr(name, "Mul") != nullptr);
		bool mode_min = (strstr(name, "Min") != nullptr);
		bool mode_max = (strstr(name, "Max") != nullptr);
		bool mode_inc = (strstr(name, "Inclusive") != nullptr);
		bool mode_exc = (strstr(name, "Exclusive") != nullptr);
		
		Log::printf("\n%s():\n", name);
		for(uint32_t i = 0; i < size; i++) {
			
			// subgroup operation
			uint32_t value = 0u;
			if(mode_mul) value = 1u;
			if(mode_min) value = ~0u;
			uint32_t begin = i & ~(features.subgroupSize - 1);
			for(uint32_t j = begin; j < begin + features.subgroupSize; j++) {
				uint32_t v = j;
				if(mode_mul) v = (j & 3) + 1;
				if(mode_min) v = size - 1 - j;
				if(mode_exc && j >= i) break;
				if(mode_add) value = value + v;
				if(mode_mul) value = value * v;
				if(mode_min) value = Tellusim::min(value, v);
				if(mode_max) value = Tellusim::max(value, v);
				if(mode_inc && j >= i) break;
			}
			
			// check result
			uint32_t v = data[i * 4 + offset][index];
			if(value != v) TS_LOGF(Fatal, "%u: %u %u\n", i, value, v);
			if(mode_mul) Log::printf("%u ", v);
			else Log::printf("%4d ", v);
			if(((i + 1) & 31) == 0) Log::print("\n");
		}
	};
	
	print("subgroupAdd", 0, 0);
	print("subgroupInclusiveAdd", 0, 1);
	print("subgroupExclusiveAdd", 0, 2);
	
	print("subgroupMul", 1, 0);
	print("subgroupInclusiveMul", 1, 1);
	print("subgroupExclusiveMul", 1, 2);
	
	print("subgroupMin", 2, 0);
	print("subgroupInclusiveMin", 2, 1);
	print("subgroupExclusiveMin", 2, 2);
	
	print("subgroupMax", 3, 0);
	print("subgroupInclusiveMax", 3, 1);
	print("subgroupExclusiveMax", 3, 2);
	
	Log::printf("\ngl_SubgroupInvocationID:\n");
	for(uint32_t i = 0; i < size; i++) {
		Log::printf("%2d ", data[i * 4 + 0][3]);
		if(((i + 1) & 31) == 0) Log::print("\n");
	}
	
	Log::printf("\ngl_SubgroupSize:\n");
	for(uint32_t i = 0; i < size; i++) {
		Log::printf("%2d ", data[i * 4 + 1][3]);
		if(((i + 1) & 31) == 0) Log::print("\n");
	}
	
	// finish context
	context.finish();
	
	return 0;
}

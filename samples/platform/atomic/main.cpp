// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
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
	
	// buffer size
	constexpr uint32_t num_buffers = 5;
	constexpr uint32_t buffer_size = 256;
	
	// create device
	Device device(context);
	if(!device) return 1;
	
	// check compute shader support
	if(!device.hasShader(Shader::TypeCompute)) {
		TS_LOG(Error, "compute shader is not supported\n");
		return 0;
	}
	
	// print device info
	TS_LOGF(Message, "%s (%s)\n", device.getName().get(), device.getPlatformName());
	
	// create kernel
	Kernel kernel = device.createKernel().setUniforms(1).setStorages(num_buffers, BindFlagFixed);
	if(!kernel.loadShaderGLSL("main.shader", "COMPUTE_SHADER=1")) return 1;
	if(!kernel.create()) return 1;
	
	// create buffers
	Array<Buffer> buffers;
	Array<uint32_t> buffer_data(buffer_size, 0u);
	for(uint32_t i = 0; i < num_buffers; i++) {
		buffers.append(device.createBuffer(Buffer::FlagStorage | Buffer::FlagSource, buffer_data.get(), buffer_data.bytes()));
		if(!buffers.back()) return 1;
	}
	
	{
		// create command list
		Compute compute = device.createCompute();
		
		// dispatch kernel
		compute.setKernel(kernel);
		compute.setUniform(0, buffer_size);
		compute.setStorageBuffers(0, buffers);
		compute.dispatch(buffer_data.size());
	}
	
	// flush context
	context.flush();
	
	// check buffer data
	uint32_t data = 0;
	for(uint32_t i = 0; i < buffers.size(); i++) {
		if(!device.getBuffer(buffers[i], buffer_data.get(), buffer_data.bytes())) return 1;
		for(uint32_t j = 0; j < buffer_data.size(); j++) {
			if(buffer_data[j] != j) TS_LOGF(Fatal, "%u: %u %u\n", i, buffer_data[j], j);
			data += buffer_data[j];
		}
	}
	TS_LOGF(Message, "%u\n", data);
	
	// finish context
	context.finish();
	
	return 0;
}

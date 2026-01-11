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
	
	// buffer size
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
	Kernel kernel = device.createKernel().setUniforms(1).setStorages(2);
	if(!kernel.loadShaderGLSL("main.shader", "COMPUTE_SHADER=1")) return 1;
	if(!kernel.create()) return 1;
	
	// create buffers
	Array<float16_t> buffer_data(buffer_size);
	for(uint32_t i = 0; i < buffer_size; i++) {
		buffer_data[i] = (float32_t)i;
	}
	Buffer input_buffer = device.createBuffer(Buffer::FlagStorage, buffer_data.get(), buffer_data.bytes());
	Buffer output_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagSource, buffer_data.bytes());
	if(!input_buffer || !output_buffer) return 1;
	
	{
		// create command list
		Compute compute = device.createCompute();
		
		// dispatch kernel
		compute.setKernel(kernel);
		compute.setUniform(0, buffer_size);
		compute.setStorageBuffers(0, { input_buffer, output_buffer });
		compute.dispatch(buffer_size);
	}
	
	// flush context
	context.flush();
	
	// check buffer data
	float32_t data = 0.0f;
	if(!device.getBuffer(output_buffer, buffer_data.get(), buffer_data.bytes())) return 1;
	for(uint32_t i = 0; i < buffer_size; i++) {
		if((float32_t)buffer_data[i] != i * 2.0f + 1.0f) TS_LOGF(Fatal, "%u: %f\n", i, (float32_t)buffer_data[i]);
		data += (float32_t)buffer_data[i];
	}
	TS_LOGF(Message, "%f\n", data);
	
	// finish context
	context.finish();
	
	return 0;
}

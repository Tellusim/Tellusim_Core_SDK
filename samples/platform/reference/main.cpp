// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimMath.h>
#include <math/TellusimString.h>
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
	
	// reference structure
	struct Data {
		uint32_t size;
		uint32_t u;
		float32_t f;
		uint32_t pad;
		Vector3f v3;
		Vector4f v4;
		Matrix4x4f m4;
	};
	
	// buffer size
	constexpr uint32_t num_buffers = 5;
	constexpr uint32_t buffer_size = sizeof(Data) * 256;
	
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
	Kernel kernel = device.createKernel().setStorages(num_buffers, BindFlagFixed);
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
		compute.setStorageBuffers(0, buffers);
		compute.dispatch(1);
	}
	
	// flush context
	context.flush();
	
	// check buffer data
	for(uint32_t i = 0; i < buffers.size(); i++) {
		if(!device.getBuffer(buffers[i], buffer_data.get(), buffer_data.bytes())) return 1;
		for(uint32_t j = 0; j < 32; j++) {
			Data *data = (Data*)buffer_data.get() + j;
			if(data->u != j) TS_LOGF(Fatal, "%u %u: i: %u %u\n", i, j, data->u, j);
			if(data->f != (float32_t)j) TS_LOGF(Fatal, "%u %u: f: %f %f\n", i, j, data->f, (float32_t)j);
			if(data->size != sizeof(Data)) TS_LOGF(Fatal, "%u %u: size: %u %u\n", i, j, data->size, (uint32_t)sizeof(Data));
			if(data->v3 != Vector3f(1.0f, 2.0f, 3.0f)) TS_LOGF(Fatal, "%u %u: v3: %s\n", i, j, toString(data->v3).get());
			if(data->v4 != Vector4f(4.0f, 5.0f, 6.0f, 7.0f)) TS_LOGF(Fatal, "%u %u: v4: %s\n", i, j, toString(data->v4).get());
			if(data->m4 != Matrix4x4f(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f)) TS_LOGF(Fatal, "%u %u: m4: %s\n", i, j, toString(data->m4).get());
			if(j == i) TS_LOGF(Message, "%u: %u | %u | %f | %s | %s\n", i, data->size, data->u, data->f, toString(data->v3).get(), toString(data->v4).get());
		}
	}
	
	// finish context
	context.finish();
	
	return 0;
}

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimBuffer.h>
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
	
	// print device info
	TS_LOGF(Message, "%s (%s)\n", device.getName().get(), device.getPlatformName());
	
	// create kernel
	Kernel kernel = device.createKernel().setStorages(1);
	if(!kernel.loadShaderGLSL("main.shader", "COMPUTE_SHADER=1")) return 1;
	if(!kernel.create()) return 1;
	
	// create buffer
	Array<uint32_t> data(1024 * 1024, 0u);
	Buffer storage_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagSource, data.get(), data.bytes());
	if(!storage_buffer) return 1;
	
	{
		// create command list
		Compute compute = device.createCompute();
		
		// run kernel
		compute.setKernel(kernel);
		compute.setStorageBuffer(0, storage_buffer);
		compute.dispatch(1);
		
		// buffer barrier
		compute.barrier(storage_buffer);
	}
	
	// get buffer data
	if(!device.getBuffer(storage_buffer, data.get())) return 1;
	
	// print buffer
	String str, format;
	for(uint32_t i = 1; i < data[0]; i++) {
		uint32_t num = data[i] >> 16;
		uint32_t size = data[i] & 0xffff;
		if(i + size > data[0] || size < num) break;
		const char *f = (const char*)&data[i + 1];
		const uint32_t *args = &data[i + 1 + size - num];
		str.clear();
		while(*f) {
			if(*f == '%') {
				format.clear();
				format += *f++;
				while(*f) {
					char c = *f++;
					format += c;
					if(!strchr("0123456789+-.", c)) {
						if(format == "%d") String::fromi32(str, *args++, 10);
						else if(format == "%i") String::fromi32(str, *args++, 10);
						else if(format == "%u") String::fromu32(str, *args++, 10);
						else if(format == "%x") String::fromu32(str, *args++, 16);
						else if(format == "%f") String::fromf64(str, f32u32(*args++).f, 6, false, false);
						else if(format == "%g") String::fromf64(str, f32u32(*args++).f, 6, false, true);
						else if(format == "%s") str += (const char*)args++;
						else if(format == "%%") str += '%';
						else if(strchr("fegEG", c)) str += String::format(format.get(), f32u32(*args++).f);
						else str += String::format(format.get(), *args++);
						break;
					}
				}
			} else {
				str += *f++;
			}
		}
		if(str) Log::print(Log::Message, str.get());
		i += size;
	}
	
	// check errors
	device.check();
	
	// finish context
	context.finish();
	
	return 0;
}

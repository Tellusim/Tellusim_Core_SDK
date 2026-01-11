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
static void printm4x4(const char *str, const Matrix4x4f &m) {
	TS_LOGF(Message, "%s%f %f %f %f | %f %f %f %f | %f %f %f %f | %f %f %f %f\n", str,
		m.m00, m.m01, m.m02, m.m03, m.m10, m.m11, m.m12, m.m13, m.m20, m.m21, m.m22, m.m23, m.m30, m.m31, m.m32, m.m33);
}

static void printv4(const char *str, const Matrix4x4f &m) {
	TS_LOGF(Message, "%s%f %f %f %f\n", str, m.m00, m.m01, m.m02, m.m03);
}

static void printv4(const char *str, const Vector4f &v) {
	TS_LOGF(Message, "%s%f %f %f %f\n", str, v.x, v.y, v.z, v.w);
}

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
	Kernel kernel = device.createKernel().setUniforms(3).setStorages(2);
	if(!kernel.loadShaderGLSL("main.shader", "COMPUTE_SHADER=1")) return 1;
	if(!kernel.create()) return 1;
	
	// create buffers
	Array<Matrix4x4f> read_buffer_data(1024, Matrix4x4f::zero);
	Array<Matrix4x4f> write_buffer_data(1024, Matrix4x4f::zero);
	read_buffer_data[0] = Matrix4x4f::rotateX(30.0f) * Matrix4x4f::scale(2.0f, 2.0f, 2.0f) * Matrix4x4f::translate(1.0f, 2.0f, 3.0f) * Matrix4x4f::rotateZ(20.0f);
	read_buffer_data[1] = inverse(Matrix4x4f::rotateY(30.0f) * Matrix4x4f::scale(3.0f, 3.0f, 3.0f) * Matrix4x4f::translate(3.0f, 2.0f, 1.0f) * Matrix4x4f::rotateY(20.0f));
	Buffer read_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagSource, read_buffer_data.get(), read_buffer_data.bytes());
	Buffer write_buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagSource, write_buffer_data.get(), write_buffer_data.bytes());
	if(!read_buffer || !write_buffer) return 1;
	
	{
		// create command list
		Compute compute = device.createCompute();
		
		struct Parameters {
			Matrix4x4f mat4[2];
		};
		Parameters parameters_r;
		Parameters parameters_c;
		parameters_r.mat4[0] = read_buffer_data[0];
		parameters_r.mat4[1] = read_buffer_data[1];
		parameters_c.mat4[0] = transpose(read_buffer_data[0]);
		parameters_c.mat4[1] = transpose(read_buffer_data[1]);
		
		// dispatch kernel
		compute.setKernel(kernel);
		compute.setUniform(0, parameters_r);
		compute.setUniform(1, parameters_r);
		compute.setUniform(2, parameters_c);
		compute.setStorageBuffer(0, read_buffer);
		compute.setStorageBuffer(1, write_buffer);
		compute.dispatch(64);
	}
	
	// flush context
	context.flush();
	
	// get write buffer
	if(!device.getBuffer(write_buffer, write_buffer_data.get(), write_buffer_data.bytes())) return 1;
	const Matrix4x4f *data = write_buffer_data.get();
	
	// reference vector
	Vector4f vec4 = Vector4f(-1.0f, 2.0f, 3.0f, 1.0f);
	
	// mat4 * mat4
	Log::print("\n");
	TS_LOG(Message, "mat4 * mat4\n");
	printm4x4("ref: ", read_buffer_data[0] * read_buffer_data[1]);
	printm4x4("  f: ", data[0]);
	printm4x4("  i: ", data[1]);
	printm4x4("  r: ", data[2]);
	printm4x4("  c: ", data[3]);
	printm4x4("  u: ", data[4]);
	data += 5;
	
	// mat4 * mat4 * vec4
	Log::print("\n");
	TS_LOG(Message, "mat4 * mat4 * vec4\n");
	printv4("ref: ", (read_buffer_data[0] * read_buffer_data[1]) * vec4);
	printv4("  f: ", data[0]);
	printv4("  i: ", data[1]);
	printv4("  r: ", data[2]);
	printv4("  c: ", data[3]);
	printv4("  u: ", data[4]);
	data += 5;
	
	// mat4 * vec4
	Log::print("\n");
	TS_LOG(Message, "mat4 * vec4\n");
	printv4("ref: ", read_buffer_data[0] * vec4);
	printv4("  f: ", data[0]);
	printv4("  i: ", data[1]);
	printv4("  r: ", data[2]);
	printv4("  c: ", data[3]);
	printv4("  u: ", data[4]);
	data += 5;
	
	// vec4 * mat4
	Log::print("\n");
	TS_LOG(Message, "vec4 * mat4\n");
	printv4("ref: ", vec4 * read_buffer_data[0]);
	printv4("  f: ", data[0]);
	printv4("  i: ", data[1]);
	printv4("  r: ", data[2]);
	printv4("  c: ", data[3]);
	printv4("  u: ", data[4]);
	data += 5;
	
	// mat4x3 * vec4
	Log::print("\n");
	TS_LOG(Message, "mat4x3 * vec4\n");
	printv4("ref: ", read_buffer_data[0] * vec4);
	printv4("  f: ", data[0]);
	printv4("  i: ", data[1]);
	data += 2;
	
	// vec3 * mat4x3
	Log::print("\n");
	TS_LOG(Message, "vec4 * mat4x3\n");
	printv4("ref: ", vec4 * read_buffer_data[0]);
	printv4("  f: ", data[0]);
	printv4("  i: ", data[1]);
	data += 2;
	
	// finish context
	context.finish();
	
	return 0;
}

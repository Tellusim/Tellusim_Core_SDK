// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <common/common.h>
#include <math/TellusimNumerical.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimKernel.h>
#include <platform/TellusimCompute.h>
#include <platform/TellusimContext.h>

/*
 */
using namespace Tellusim;

/*
 */
template <class Matrix> static void printm(const char *name, const Matrix &m) {
	Log::printf("%s:\n", name);
	for(uint32_t i = 0; i < m.Rows; i++) {
		String row;
		for(uint32_t j = 0; j < m.Columns; j++) {
			if(row) row += " ";
			row += String::format("%7.4f", m[i][j]);
		}
		row += "\n";
		Log::print(row.get());
	}
	Log::print("\n");
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
	
	// check cooperative matrix support
	if(!device.getFeatures().matrix16f16 && !device.getFeatures().matrix8x16x16f16) {
		TS_LOG(Error, "cooperative matrix is not supported\n");
		return 0;
	}
	
	// print device info
	TS_LOGF(Message, "%s (%s)\n", device.getName().get(), device.getPlatformName());
	
	// matrix size
	constexpr uint32_t M = 16;		// number of rows in a, c, d
	constexpr uint32_t N = 16;		// number of columns in b, c, d
	constexpr uint32_t K = 16;		// number of columns in a and rows in b
	constexpr uint32_t S = 16;		// maximum dimension
	
	// create kernel
	Kernel kernel = device.createKernel().setStorages(1);
	if(!kernel.loadShaderGLSL("main.shader", "COMPUTE_SHADER=1; M=%u; N=%u; K=%u; S=%u", M, N, K, S)) return 1;
	if(!kernel.create()) return 1;
	
	// create matrices
	Array<float16_t> data;
	for(uint32_t i = 0; i < S * S; i++) {
		uint32_t j = i % S;
		uint32_t k = i / S;
		float32_t value = (float32_t)(S + S - j - k) / (S + S);
		if(j < k) value = -value;
		data.append(float16_t(value));
	}
	for(uint32_t i = 0; i < S * S * 3; i++) {
		data.append(float16_t::zero);
	}
	
	// inverse matrix (columns, rows)
	MatrixNxM<float64_t, K, M> a(MatrixNxM<float16_t, K, M>(data.get() + S * S * 0));
	MatrixNxM<float64_t, N, K> b = LU::inverse(MatrixNxM<float64_t, S, S>(MatrixNxM<float16_t, S, S>(data.get() + S * S * 0)));
	MatrixNxM<float64_t, N, M> c = -(a * b);
	MatrixNxM<float64_t, N, M> d(1.0);
	
	MatrixNxM<float16_t, K, M>(a).get(data.get() + S * S * 0);
	MatrixNxM<float16_t, N, K>(b).get(data.get() + S * S * 1);
	MatrixNxM<float16_t, N, M>(c).get(data.get() + S * S * 2);
	MatrixNxM<float16_t, N, M>(d).get(data.get() + S * S * 3);
	
	// create buffer
	Buffer buffer = device.createBuffer(Buffer::FlagStorage | Buffer::FlagSource, data.get(), data.bytes());
	if(!buffer) return 1;
	
	{
		// create command list
		Compute compute = device.createCompute();
		
		// run kernel
		compute.setKernel(kernel);
		compute.setStorageBuffer(0, buffer);
		compute.dispatch(1);
	}
	
	// flush context
	context.flush();
	
	// get buffer
	if(!device.getBuffer(buffer, data.get())) return 1;
	
	// print result
	a = MatrixNxM<float64_t, K, M>(MatrixNxM<float16_t, K, M>(data.get() + S * S * 0));
	b = MatrixNxM<float64_t, N, K>(MatrixNxM<float16_t, N, K>(data.get() + S * S * 1));
	c = MatrixNxM<float64_t, N, M>(MatrixNxM<float16_t, N, M>(data.get() + S * S * 2));
	d = MatrixNxM<float64_t, N, M>(MatrixNxM<float16_t, N, M>(data.get() + S * S * 3));
	printm("a", a);
	printm("b", b);
	printm("c", c);
	printm("d", d);
	
	// reference result
	printm("ref", a * b + c);
	
	// check errors
	device.check();
	
	// finish context
	context.finish();
	
	return 0;
}

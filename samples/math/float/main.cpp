// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <math/TellusimFloat.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	using Tellusim::pow;
	using Tellusim::abs;
	using Tellusim::sin;
	using Tellusim::cos;
	using Tellusim::asin;
	using Tellusim::acos;
	using Tellusim::atan;
	using Tellusim::rsqrt;
	
	{
		for(int32_t i = -9; i <= 16; i++) {
			for(int32_t j = 2; j <= 3; j++) {
				float32_t f = pow(2.0f, (float32_t)i) * ((float32_t)j / 2.0f);
				TS_LOGF(Message, "%f %f %f %f\n", f, float16_t(f).get(), float21_t(f).get(), float24_t(f).get());
			}
		}
	}
	
	if(1) {
		
		TS_LOG(Message, "\n");
		
		float32_t rsqrt_error = 0.0f;
		float32_t rcbrt_error = 0.0f;
		for(float64_t X = 0.0; X <= 32.0; X += 1e-7) {
			float32_t x = (float32_t)X;
			rsqrt_error = max(rsqrt_error, abs(rsqrt(x) - rsqrtFast(x)));
			rcbrt_error = max(rcbrt_error, abs(1.0f / pow(x, 1.0f / 3.0f) - rcbrtFast(x)));
		}
		TS_LOGF(Message, "rsqrt: %e\n", rsqrt_error);
		TS_LOGF(Message, "rcbrt: %e\n", rsqrt_error);
	}
	
	if(1) {
		
		TS_LOG(Message, "\n");
		
		float32_t sin_error = 0.0f;
		float32_t cos_error = 0.0f;
		for(float64_t X = -Pi2d * 4.0; X <= Pi2d * 4.0; X += Pi2d * 1e-7) {
			float32_t x = (float32_t)X;
			sin_error = max(sin_error, abs(sin(x) - sinFast(x)));
			cos_error = max(cos_error, abs(cos(x) - cosFast(x)));
		}
		TS_LOGF(Message, "sin: %e\n", sin_error);
		TS_LOGF(Message, "cos: %e\n", cos_error);
	}
	
	if(1) {
		
		TS_LOG(Message, "\n");
		
		float32_t asin_error = 0.0f;
		float32_t acos_error = 0.0f;
		for(float64_t X = -1.0; X <= 1.0; X += 1e-6) {
			float32_t x = (float32_t)X;
			asin_error = max(asin_error, abs(asin(x) - asinFast(x)));
			acos_error = max(acos_error, abs(acos(x) - acosFast(x)));
		}
		TS_LOGF(Message, "asin: %e\n", asin_error);
		TS_LOGF(Message, "acos: %e\n", acos_error);
	}
	
	if(1) {
		
		TS_LOG(Message, "\n");
		
		float32_t atan_error = 0.0f;
		for(float64_t X = -64.0; X <= 64.0; X += 1e-6) {
			float32_t x = (float32_t)X;
			atan_error = max(atan_error, abs(atan(x) - atanFast(x)));
		}
		TS_LOGF(Message, "atan: %e\n", atan_error);
	}
	
	return 0;
}

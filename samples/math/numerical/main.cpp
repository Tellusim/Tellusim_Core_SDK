// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <math/TellusimMatrix.h>
#include <math/TellusimNumerical.h>

/*
 */
using namespace Tellusim;

/*
 */
template <class Type> void print4(const char *str, const Type &v) {
	TS_LOGF(Message, "%s%f %f %f %f\n", str, v.x, v.y, v.z, v.w);
}

template <class Type> void print4x4(const char *str, const Matrix4x4<Type> &m) {
	TS_LOGF(Message, "%s%f %f %f %f\n", str, m.m00, m.m01, m.m02, m.m03);
	TS_LOGF(Message, "%s%f %f %f %f\n", str, m.m10, m.m11, m.m12, m.m13);
	TS_LOGF(Message, "%s%f %f %f %f\n", str, m.m20, m.m21, m.m22, m.m23);
	TS_LOGF(Message, "%s%f %f %f %f\n", str, m.m30, m.m31, m.m32, m.m33);
}

template <class Type, uint32_t N> void printN(const char *str, const VectorN<Type, N> &v) {
	TS_LOGF(Message, "%s", str);
	for(uint32_t i = 0; i < N; i++) {
		if(i != N - 1) Log::printf("%f ", v[i]);
		else Log::printf("%f\n", v[i]);
	}
}

template <class Type, uint32_t N, uint32_t M> void printNxM(const char *str, const MatrixNxM<Type, N, M> &m) {
	for(uint32_t y = 0; y < M; y++) {
		TS_LOGF(Message, "%s", str);
		for(uint32_t x = 0; x < N; x++) {
			if(x != N - 1) Log::printf("%f ", m[y][x]);
			else Log::printf("%f\n", m[y][x]);
		}
	}
}

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	using Tellusim::abs;
	
	{
		using Vector4 = Tellusim::VectorN<float32_t, 4>;
		
		Vector4 a = Vector4(2.0f);
		Vector4 b = Vector4({ 0.0f, 1.0f, 2.0f, 3.0f });
		printN("v4: ", a + b * Vector4(2.0f));
	}
	
	{
		TS_LOG(Message, "\n");
		
		using Vector4 = Tellusim::Vector4<float32_t>;
		using Matrix4x4 = Tellusim::Matrix4x4<float32_t>;
		
		Matrix4x4 m0, m1;
		Vector4 v = Vector4(1.0f, 2.0f, 3.0f, 4.0f);
		for(uint32_t i = 0; i < 16; i++) {
			m0.m[i] = 16.0f - (float32_t)i;
			m1.m[i] = (float32_t)i;
		}
		
		print4x4("mul m4x4 m4x4: ", m0 * m1);
		print4x4("mul m4x4 m4x4: ", m1 * m0);
		print4("mul m4x4 v4:   ", m0 * v);
		print4("mul v4 m4x4:   ", v * m0);
	}
	
	{
		TS_LOG(Message, "\n");
		
		using Vector4 = Tellusim::VectorN<float32_t, 4>;
		using Matrix4x4 = Tellusim::MatrixNxM<float32_t, 4, 4>;
		
		Matrix4x4 m0, m1;
		Vector4 v = Vector4({ 1.0f, 2.0f, 3.0f, 4.0f });
		for(uint32_t j = 0, k = 0; j < 4; j++) {
			for(uint32_t i = 0; i < 4; i++, k++) {
				m0.rows[j].v[i] = 16.0f - (float32_t)k;
				m1.rows[j].v[i] = (float32_t)k;
			}
		}
		
		auto aa = m0 * m1;
		TS_LOGF(Error, "%u %u\n", aa.Columns, aa.Rows);
		
		printNxM("mul m4x4 m4x4: ", m0 * m1);
		printNxM("mul m4x4 m4x4: ", m1 * m0);
		printN("mul m4x4 v4:   ", m0 * v);
		printN("mul v4 m4x4:   ", v * m0);
	}
	
	{
		TS_LOG(Message, "\n");
		
		using Vector3 = Tellusim::VectorN<float32_t, 3>;
		using Vector4 = Tellusim::VectorN<float32_t, 4>;
		using Matrix4x3 = Tellusim::MatrixNxM<float32_t, 4, 3>;
		
		Matrix4x3 m;
		Vector3 v3 = Vector3({ 1.0f, 2.0f, 3.0f });
		Vector4 v4 = Vector4({ 1.0f, 2.0f, 3.0f, 4.0f });
		for(uint32_t j = 0, k = 0; j < 3; j++) {
			for(uint32_t i = 0; i < 4; i++, k++) {
				m.rows[j].v[i] = (float32_t)k;
			}
		}
		
		printN("mul m4x3 v4: ", m * v4);
		printN("mul v3 m4x3: ", v3 * m);
	}
	
	{
		TS_LOG(Message, "\n");
		
		using Matrix4x2 = Tellusim::MatrixNxM<float32_t, 4, 2>;
		using Matrix2x3 = Tellusim::MatrixNxM<float32_t, 2, 3>;
		using Matrix3x2 = Tellusim::MatrixNxM<float32_t, 3, 2>;
		using Matrix2x4 = Tellusim::MatrixNxM<float32_t, 2, 4>;
		using Matrix3x4 = Tellusim::MatrixNxM<float32_t, 3, 4>;
		
		printNxM("mul m2x3 m4x2: ", Matrix2x3({ 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f }) * Matrix4x2({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f }));
		printNxM("mul m2x4 m3x2: ", Matrix2x4({ 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f }) * Matrix3x2({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f }));
		printNxM("mul m4x2 m3x4: ", Matrix4x2({ 3.0f, 2.0f, 1.0f, 5.0f, 9.0f, 1.0f, 3.0f, 0.0f }) * Matrix3x4({ 2.0f, 9.0f, 0.0f, 1.0f, 3.0f, 5.0f, 2.0f, 4.0f, 7.0f, 8.0f, 1.0f, 5.0f }));
	}
	
	{
		
		TS_LOG(Message, "\n");
		TS_LOG(Message, "Jacobi:\n");
		
		using VectorN = Tellusim::VectorN<float64_t, 3>;
		using MatrixNxN = Tellusim::MatrixNxM<float64_t, 3, 3>;
		
		MatrixNxN m0({
			VectorN({ -1.0f,  2.0f,  3.0f }),
			VectorN({  2.0f,  4.0f, -5.0f }),
			VectorN({  3.0f, -5.0f,  6.0f }) });
		
		MatrixNxN m2;
		MatrixNxN m1 = jacobi(m0, m2);
		
		printNxM("m1: ", m1);
		printNxM("m2: ", m2);
		printNxM("m0: ", m2 * m1 * transpose(m2));
	}
	
	if(1) {
		
		using VectorN = Tellusim::VectorN<float64_t, 7>;
		using MatrixNxN = Tellusim::MatrixNxM<float64_t, 7, 7>;
		
		MatrixNxN m0({
			VectorN({  1.0f, 3.0f, 0.0f,  0.0f, 7.0f,  7.0f, -9.0f }),
			VectorN({  2.0f, 1.0f, 3.0f,  0.0f, 0.0f,  7.0f,  7.0f }),
			VectorN({  0.0f, 2.0f, 1.0f, -3.0f, 6.0f,  0.0f,  7.0f }),
			VectorN({  0.0f, 0.0f, 2.0f, -1.0f, 3.0f,  0.0f,  0.0f }),
			VectorN({  0.0f, 0.0f, 6.0f, -2.0f, 1.0f, -3.0f,  0.0f }),
			VectorN({  7.0f, 7.0f, 0.0f,  0.0f, 2.0f, -1.0f,  3.0f }),
			VectorN({ -9.0f, 7.0f, 7.0f,  0.0f, 0.0f,  2.0f,  1.0f }) });
		
		VectorN b({ -3.0f, -2.0f, -1.0f, 0.0f, 1.0f, 2.0f, 3.0f });
		
		if(1) {
			
			MatrixNxN lu;
			Tellusim::VectorN<uint32_t, 7> indices;
			if(LU::decompose(m0, lu, indices)) {
				
				TS_LOG(Message, "\n");
				TS_LOG(Message, "LU:\n");
				
				MatrixNxN m1 = LU::inverse(lu, indices);
				printNxM("inv: ", m0 * m1);
				
				VectorN x = LU::solve(lu, indices, b);
				printN("Ax: ", m0 * x);
				printN("b:  ", b);
			}
			
			MatrixNxN l, u;
			if(LU::decompose(m0, l, u)) {
				MatrixNxN m1 = m0 - l * u;
				for(uint32_t j = 0; j < m0.Rows; j++) {
					for(uint32_t i = 0; i < m0.Columns; i++) {
						if(abs(m1[j][i]) > 1e-6f) return 1;
					}
				}
			}
		}
		
		if(1) {
			
			VectorN c, d;
			MatrixNxN qr;
			if(QR::decompose(m0, qr, c, d)) {
				
				TS_LOG(Message, "\n");
				TS_LOG(Message, "QR:\n");
				
				MatrixNxN m1 = QR::inverse(qr, c, d);
				printNxM("inv: ", m0 * m1);
				
				VectorN x = QR::solve(qr, c, d, b);
				printN("Ax: ", m0 * x);
				printN("b:  ", b);
			}
			
			MatrixNxN q, r;
			if(QR::decompose(m0, q, r)) {
				MatrixNxN m1 = m0 - q * r;
				for(uint32_t j = 0; j < m0.Rows; j++) {
					for(uint32_t i = 0; i < m0.Columns; i++) {
						if(abs(m1[j][i]) > 1e-6f) return 1;
					}
				}
			}
		}
		
		if(1) {
			
			VectorN w;
			MatrixNxN u, v;
			if(SVD::decompose(m0, u, w, v)) {
				
				TS_LOG(Message, "\n");
				TS_LOG(Message, "SVD:\n");
				
				MatrixNxN m1 = SVD::inverse(u, w, v);
				printNxM("inv: ", m0 * m1);
				
				VectorN x = SVD::solve(u, w, v, b);
				printN("Ax: ", m0 * x);
				printN("b:  ", b);
			}
			
			if(SVD::decompose(m0, u, w, v)) {
				MatrixNxN m1 = m0 - (u * diagonal(w) * transpose(v));
				for(uint32_t j = 0; j < m0.Rows; j++) {
					for(uint32_t i = 0; i < m0.Columns; i++) {
						if(abs(m1[j][i]) > 1e-6f) return 1;
					}
				}
			}
		}
	}
	
	if(1) {
		
		constexpr uint32_t size = 8;
		
		using Vector3 = Tellusim::Vector3<float64_t>;
		using VectorN = Tellusim::VectorN<float64_t, 3>;
		using MatrixNxN = Tellusim::MatrixNxM<float64_t, 3, 3>;
		using Matrix4x4 = Tellusim::Matrix4x4<float64_t>;
		
		Matrix4x4 transform = Matrix4x4::translate(1.0, 20.0f, 300.0) * Matrix4x4::rotateZ(-70.0);
		transform *= Matrix4x4::rotateX(12.0) * Matrix4x4::scale(3.0) * Matrix4x4::rotateY(17.0);
		transform *= Matrix4x4::rotateZ(33.0) * Matrix4x4::translate(-4.0, -8.0, 16.0) * Matrix4x4::rotateX(-13.0);
		
		VectorN points_0[size] = {
			VectorN({  1.0,  0.0,  0.0 }),
			VectorN({  0.0,  2.0,  0.0 }),
			VectorN({  0.0,  0.0,  3.0 }),
			VectorN({  4.0,  5.0,  6.0 }),
			VectorN({  0.0, -1.0,  0.0 }),
			VectorN({  0.0,  0.0, -2.0 }),
			VectorN({ -3.0,  0.0,  0.0 }),
			VectorN({  7.0,  8.0,  9.0 }),
		};
		
		VectorN points_1[TS_COUNTOF(points_0)];
		for(uint32_t i = 0; i < TS_COUNTOF(points_0); i++) {
			points_1[i] = VectorN((transform * Vector3(points_0[i].v)).v);
		}
		
		if(1) {
			
			TS_LOG(Message, "\n");
			TS_LOG(Message, "Inverse:\n");
			
			float64_t scale_0 = 0.0;
			float64_t scale_1 = 0.0;
			for(uint32_t i = 1; i < size; i++) {
				scale_0 += length(points_0[i] - points_0[0]);
				scale_1 += length(points_1[i] - points_1[0]);
			}
			float64_t scale = scale_1 / scale_0;
			
			MatrixNxN m0, m1;
			for(uint32_t i = 0; i < 3; i++) {
				m0[i] = points_0[i + 1] - points_0[0];
				m1[i] = (points_1[i + 1] - points_1[0]) / scale;
			}
			
			MatrixNxN r = LU::inverse(m0) * m1;
			printNxM(" R: ", r);
			
			for(uint32_t i = 0; i < size; i++) {
				printN(" v: ", r * ((points_1[i] - points_1[0]) / scale) + points_0[0]);
			}
		}
		
		if(1) {
			
			using Matrix3x4 = Tellusim::MatrixNxM<float64_t, 3, size>;
			
			float64_t scale_0 = 0.0;
			float64_t scale_1 = 0.0;
			for(uint32_t i = 1; i < size; i++) {
				scale_0 += length(points_0[i] - points_0[0]);
				scale_1 += length(points_1[i] - points_1[0]);
			}
			float64_t scale = scale_1 / scale_0;
			
			VectorN center_0 = VectorN(0.0);
			VectorN center_1 = VectorN(0.0);
			for(uint32_t i = 0; i < size; i++) {
				center_0 += points_0[i] / (float64_t)size;
				center_1 += points_1[i] / (float64_t)size;
			}
			
			Matrix3x4 m0, m1;
			for(uint32_t i = 0; i < size; i++) {
				m0[i] = points_0[i] - center_0;
				m1[i] = (points_1[i] - center_1) / scale;
			}
			MatrixNxN a = transpose(m0) * m1;
			
			VectorN w;
			MatrixNxN u, v;
			if(SVD::decompose(a, u, w, v)) {
				
				TS_LOG(Message, "\n");
				TS_LOG(Message, "Kabsch:\n");
				
				MatrixNxN r = u * transpose(v);
				printNxM(" R: ", r);
				
				for(uint32_t i = 0; i < size; i++) {
					printN(" v: ", r * ((points_1[i] - center_1) / scale) + center_0);
				}
			}
		}
	}
	
	return 0;
}

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_MATH_NUMERICAL_H__
#define __TELLUSIM_MATH_NUMERICAL_H__

#include <math/TellusimScalar.h>

/*
 */
namespace Tellusim {
	
	/*****************************************************************************\
	 *
	 * VectorN
	 *
	\*****************************************************************************/
	
	/**
	 * VectorN class
	 */
	template <class Type, uint32_t N> struct VectorN final {
		
		VectorN() { }
		VectorN(const VectorN &vector) { set(vector); }
		explicit VectorN(uint32_t size) : Size(size) { TS_ASSERT(size <= N); }
		explicit VectorN(const Type &value, uint32_t size = N) { set(value, size); }
		explicit VectorN(const Type *vector, uint32_t size = N) { set(vector, size); }
		explicit VectorN(const InitializerList<Type> &list) { set(list); }
		template <class CType> explicit VectorN(const VectorN<CType, N> &vector) {
			Size = vector.Size;
			for(uint32_t i = 0; i < Size; i++) v[i] = (Type)vector.v[i];
		}
		
		/// update vector data
		void set(const Type &value, uint32_t size = N) {
			TS_ASSERT(size <= N);
			Size = size;
			for(uint32_t i = 0; i < Size; i++) v[i] = value;
		}
		void set(const Type *TS_RESTRICT vector, uint32_t size = N) {
			TS_ASSERT(size <= N);
			Size = size;
			for(uint32_t i = 0; i < Size; i++) v[i] = vector[i];
		}
		void set(const VectorN &vector) {
			Size = vector.Size;
			for(uint32_t i = 0; i < Size; i++) v[i] = vector.v[i];
		}
		void set(const InitializerList<Type> &list) {
			TS_ASSERT(list.size() <= N);
			auto it = list.begin();
			Size = (uint32_t)list.size();
			for(uint32_t i = 0; i < Size; i++) v[i] = *it++;
		}
		void get(Type *TS_RESTRICT vector, uint32_t size = N) {
			TS_ASSERT(size <= Size);
			for(uint32_t i = 0; i < size; i++) vector[i] = v[i];
		}
		
		/// vector to scalar operators
		TS_INLINE VectorN &operator*=(const Type &value) {
			for(uint32_t i = 0; i < Size; i++) v[i] *= value;
			return *this;
		}
		TS_INLINE VectorN &operator/=(const Type &value) {
			for(uint32_t i = 0; i < Size; i++) v[i] /= value;
			return *this;
		}
		TS_INLINE VectorN &operator+=(const Type &value) {
			for(uint32_t i = 0; i < Size; i++) v[i] += value;
			return *this;
		}
		TS_INLINE VectorN &operator-=(const Type &value) {
			for(uint32_t i = 0; i < Size; i++) v[i] -= value;
			return *this;
		}
		
		/// vector to vector operators
		TS_INLINE VectorN &operator=(const VectorN &vector) {
			Size = vector.Size;
			for(uint32_t i = 0; i < Size; i++) v[i] = vector.v[i];
			return *this;
		}
		TS_INLINE VectorN &operator*=(const VectorN &vector) {
			TS_ASSERT(Size == vector.Size);
			for(uint32_t i = 0; i < Size; i++) v[i] *= vector.v[i];
			return *this;
		}
		TS_INLINE VectorN &operator/=(const VectorN &vector) {
			TS_ASSERT(Size == vector.Size);
			for(uint32_t i = 0; i < Size; i++) v[i] /= vector.v[i];
			return *this;
		}
		TS_INLINE VectorN &operator+=(const VectorN &vector) {
			TS_ASSERT(Size == vector.Size);
			for(uint32_t i = 0; i < Size; i++) v[i] += vector.v[i];
			return *this;
		}
		TS_INLINE VectorN &operator-=(const VectorN &vector) {
			TS_ASSERT(Size == vector.Size);
			for(uint32_t i = 0; i < Size; i++) v[i] -= vector.v[i];
			return *this;
		}
		
		/// vector data
		TS_INLINE const Type &operator[](uint32_t index) const {
			TS_ASSERT(index < Size);
			return v[index];
		}
		TS_INLINE Type &operator[](uint32_t index) {
			TS_ASSERT(index < Size);
			return v[index];
		}
		
		Type v[N];
		
		uint32_t Size = N;
	};
	
	/// unary operators
	template <class Type, uint32_t N> TS_INLINE VectorN<Type, N> operator-(const VectorN<Type, N> &v) {
		VectorN<Type, N> ret(v.Size);
		for(uint32_t i = 0; i < v.Size; i++) ret.v[i] = -v.v[i];
		return ret;
	}
	
	/// scalar to vector operators
	template <class Type, uint32_t N> TS_INLINE VectorN<Type, N> operator*(const Type &v0, const VectorN<Type, N> &v1) {
		VectorN<Type, N> ret(v1.size);
		for(uint32_t i = 0; i < v1.size; i++) ret.v[i] = v0 * v1.v[i];
		return ret;
	}
	template <class Type, uint32_t N> TS_INLINE VectorN<Type, N> operator/(const Type &v0, const VectorN<Type, N> &v1) {
		VectorN<Type, N> ret(v1.size);
		for(uint32_t i = 0; i < v1.size; i++) ret.v[i] = v0 / v1.v[i];
		return ret;
	}
	template <class Type, uint32_t N> TS_INLINE VectorN<Type, N> operator+(const Type &v0, const VectorN<Type, N> &v1) {
		VectorN<Type, N> ret(v1.size);
		for(uint32_t i = 0; i < v1.size; i++) ret.v[i] = v0 + v1.v[i];
		return ret;
	}
	template <class Type, uint32_t N> TS_INLINE VectorN<Type, N> operator-(const Type &v0, const VectorN<Type, N> &v1) {
		VectorN<Type, N> ret(v1.size);
		for(uint32_t i = 0; i < v1.size; i++) ret.v[i] = v0 - v1.v[i];
		return ret;
	}
	
	/// vector to scalar operators
	template <class Type, uint32_t N> TS_INLINE VectorN<Type, N> operator*(const VectorN<Type, N> &v0, const Type &v1) {
		VectorN<Type, N> ret(v0.Size);
		for(uint32_t i = 0; i < v0.Size; i++) ret.v[i] = v0.v[i] * v1;
		return ret;
	}
	template <class Type, uint32_t N> TS_INLINE VectorN<Type, N> operator/(const VectorN<Type, N> &v0, const Type &v1) {
		VectorN<Type, N> ret(v0.Size);
		for(uint32_t i = 0; i < v0.Size; i++) ret.v[i] = v0.v[i] / v1;
		return ret;
	}
	template <class Type, uint32_t N> TS_INLINE VectorN<Type, N> operator+(const VectorN<Type, N> &v0, const Type &v1) {
		VectorN<Type, N> ret(v0.Size);
		for(uint32_t i = 0; i < v0.Size; i++) ret.v[i] = v0.v[i] + v1;
		return ret;
	}
	template <class Type, uint32_t N> TS_INLINE VectorN<Type, N> operator-(const VectorN<Type, N> &v0, const Type &v1) {
		VectorN<Type, N> ret(v0.Size);
		for(uint32_t i = 0; i < v0.Size; i++) ret.v[i] = v0.v[i] - v1;
		return ret;
	}
	
	/// vector to vector operators
	template <class Type, uint32_t N> TS_INLINE VectorN<Type, N> operator*(const VectorN<Type, N> &v0, const VectorN<Type, N> &v1) {
		TS_ASSERT(v0.Size == v1.Size);
		VectorN<Type, N> ret(v0.Size);
		for(uint32_t i = 0; i < v0.Size; i++) ret.v[i] = v0.v[i] * v1.v[i];
		return ret;
	}
	template <class Type, uint32_t N> TS_INLINE VectorN<Type, N> operator/(const VectorN<Type, N> &v0, const VectorN<Type, N> &v1) {
		TS_ASSERT(v0.Size == v1.Size);
		VectorN<Type, N> ret(v0.Size);
		for(uint32_t i = 0; i < v0.Size; i++) ret.v[i] = v0.v[i] / v1.v[i];
		return ret;
	}
	template <class Type, uint32_t N> TS_INLINE VectorN<Type, N> operator+(const VectorN<Type, N> &v0, const VectorN<Type, N> &v1) {
		TS_ASSERT(v0.Size == v1.Size);
		VectorN<Type, N> ret(v0.Size);
		for(uint32_t i = 0; i < v0.Size; i++) ret.v[i] = v0.v[i] + v1.v[i];
		return ret;
	}
	template <class Type, uint32_t N> TS_INLINE VectorN<Type, N> operator-(const VectorN<Type, N> &v0, const VectorN<Type, N> &v1) {
		TS_ASSERT(v0.Size == v1.Size);
		VectorN<Type, N> ret(v0.Size);
		for(uint32_t i = 0; i < v0.Size; i++) ret.v[i] = v0.v[i] - v1.v[i];
		return ret;
	}
	
	/// comparison operators
	template <class Type, uint32_t N> TS_INLINE bool operator==(const VectorN<Type, N> &v0, const VectorN<Type, N> &v1) {
		TS_ASSERT(v0.Size == v1.Size);
		for(uint32_t i = 0; i < v0.Size; i++) if(v0.v[i] != v1.v[i]) return false;
		return true;
	}
	template <class Type, uint32_t N> TS_INLINE bool operator!=(const VectorN<Type, N> &v0, const VectorN<Type, N> &v1) {
		TS_ASSERT(v0.Size == v1.Size);
		for(uint32_t i = 0; i < v0.Size; i++) if(v0.v[i] != v1.v[i]) return true;
		return false;
	}
	template <class Type, uint32_t N> TS_INLINE bool compare(const VectorN<Type, N> &v0, const VectorN<Type, N> &v1, const Type &a) {
		TS_ASSERT(v0.Size == v1.Size);
		for(uint32_t i = 0; i < v0.Size; i++) if(!compare(v0.v[i], v1.v[i], a)) return false;
		return true;
	}
	template <class Type, uint32_t N> TS_INLINE bool compare(const VectorN<Type, N> &v0, const VectorN<Type, N> &v1, const Type &a, const Type &r) {
		TS_ASSERT(v0.Size == v1.Size);
		for(uint32_t i = 0; i < v0.Size; i++) if(!compare(v0.v[i], v1.v[i], a, r)) return false;
		return true;
	}
	
	/// min/max functions
	template <class Type, uint32_t N> TS_INLINE VectorN<Type, N> min(const VectorN<Type, N> &v0, const VectorN<Type, N> &v1) {
		TS_ASSERT(v0.Size == v1.Size);
		VectorN<Type, N> ret(v0.Size);
		for(uint32_t i = 0; i < v0.Size; i++) ret.v[i] = min(v0.v[i], v1.v[i]);
		return ret;
	}
	template <class Type, uint32_t N> TS_INLINE VectorN<Type, N> max(const VectorN<Type, N> &v0, const VectorN<Type, N> &v1) {
		TS_ASSERT(v0.Size == v1.Size);
		VectorN<Type, N> ret(v0.Size);
		for(uint32_t i = 0; i < v0.Size; i++) ret.v[i] = max(v0.v[i], v1.v[i]);
		return ret;
	}
	
	/// range functions
	template <class Type, uint32_t N> TS_INLINE VectorN<Type, N> clamp(const VectorN<Type, N> &v, const Type &v0, const Type &v1) {
		VectorN<Type, N> ret(v.Size);
		for(uint32_t i = 0; i < v.Size; i++) ret.v[i] = clamp(v.v[i], v0, v1);
		return ret;
	}
	template <class Type, uint32_t N> TS_INLINE VectorN<Type, N> clamp(const VectorN<Type, N> &v, const VectorN<Type, N> &v0, const VectorN<Type, N> &v1) {
		TS_ASSERT(v.Size == v0.Size && v0.Size == v1.Size);
		VectorN<Type, N> ret(v0.Size);
		for(uint32_t i = 0; i < v0.Size; i++) ret.v[i] = clamp(v.v[i], v0.v[i], v1.v[i]);
		return ret;
	}
	
	/// math functions
	template <class Type, uint32_t N> TS_INLINE VectorN<Type, N> rcp(const VectorN<Type, N> &v) {
		VectorN<Type, N> ret(v.Size);
		for(uint32_t i = 0; i < v.Size; i++) ret.v[i] = rcp(v.v[i]);
		return ret;
	}
	template <class Type, uint32_t N> TS_INLINE VectorN<Type, N> sqrt(const VectorN<Type, N> &v) {
		VectorN<Type, N> ret(v.Size);
		for(uint32_t i = 0; i < v.Size; i++) ret.v[i] = sqrt(v.v[i]);
		return ret;
	}
	template <class Type, uint32_t N> TS_INLINE VectorN<Type, N> rsqrt(const VectorN<Type, N> &v) {
		VectorN<Type, N> ret(v.Size);
		for(uint32_t i = 0; i < v.Size; i++) ret.v[i] = rsqrt(v.v[i]);
		return ret;
	}
	
	/// vector functions
	template <class Type, uint32_t N> TS_INLINE Type dot(const VectorN<Type, N> &v0, const VectorN<Type, N> &v1) {
		TS_ASSERT(v0.Size == v1.Size);
		Type ret = v0.v[0] * v1.v[0];
		for(uint32_t i = 1; i < v0.Size; i++) ret += v0.v[i] * v1.v[i];
		return ret;
	}
	template <class Type> TS_INLINE Type cross(const VectorN<Type, 2> &v0, const VectorN<Type, 2> &v1) {
		TS_ASSERT(v0.Size == 2 && v0.Size == v1.Size);
		return v0.v[2] * v1.v[0] - v0.v[0] * v1.v[1];
	}
	template <class Type, uint32_t N> TS_INLINE VectorN<Type, N> cross(const VectorN<Type, N> &v0, const VectorN<Type, N> &v1) {
		TS_ASSERT(v0.Size == 3 && v0.Size == v1.Size);
		VectorN<Type, N> ret(v0.Size);
		ret.v[0] = v0.v[1] * v1.v[2] - v0.v[2] * v1.v[1];
		ret.v[1] = v0.v[2] * v1.v[0] - v0.v[0] * v1.v[2];
		ret.v[2] = v0.v[0] * v1.v[1] - v0.v[1] * v1.v[0];
		return ret;
	}
	template <class Type, uint32_t N> TS_INLINE Type length2(const VectorN<Type, N> &v) {
		Type ret = v.v[0] * v.v[0];
		for(uint32_t i = 1; i < v.Size; i++) ret += v.v[i] * v.v[i];
		return ret;
	}
	template <class Type, uint32_t N> TS_INLINE Type length(const VectorN<Type, N> &v) {
		return sqrt(length2(v));
	}
	template <class Type, uint32_t N> TS_INLINE VectorN<Type, N> normalize(const VectorN<Type, N> &v) {
		return v * rsqrt(length2(v));
	}
	template <class Type, uint32_t N> TS_INLINE VectorN<Type, N> lerp(const VectorN<Type, N> &v0, const VectorN<Type, N> &v1, const Type &k) {
		TS_ASSERT(v0.Size == v1.Size);
		VectorN<Type, N> ret(v0.Size);
		for(uint32_t i = 0; i < v0.Size; i++) ret.v[i] = v0.v[i] + (v1.v[i] - v0.v[i]) * k;
		return ret;
	}
	
	/*****************************************************************************\
	 *
	 * MatrixNxM
	 *
	\*****************************************************************************/
	
	/**
	 * MatrixNxM class
	 */
	template <class Type, uint32_t N, uint32_t M> struct MatrixNxM final {
		
		using VectorN = Tellusim::VectorN<Type, N>;
		using VectorM = Tellusim::VectorN<Type, M>;
		using VectorNxM = Tellusim::VectorN<Type, N * M>;
		
		MatrixNxM() { }
		MatrixNxM(const MatrixNxM &matrix) { set(matrix); }
		MatrixNxM(uint32_t columns, uint32_t rows) : Columns(columns), Rows(rows) { TS_ASSERT(columns <= N && rows <= M); }
		explicit MatrixNxM(const Type &value, uint32_t columns = N, uint32_t rows = M) { set(value, columns, rows); }
		explicit MatrixNxM(const Type *matrix, uint32_t columns = N, uint32_t rows = M) { set(matrix, columns, rows); }
		explicit MatrixNxM(const VectorNxM &vector, uint32_t columns = N, uint32_t rows = M) { set(vector, columns, rows); }
		explicit MatrixNxM(const InitializerList<Type> &list, uint32_t columns = N, uint32_t rows = M) { set(list, columns, rows); }
		explicit MatrixNxM(const InitializerList<VectorN> &list, uint32_t rows = M) { set(list, rows); }
		template <class CType> explicit MatrixNxM(const MatrixNxM<CType, N, M> &matrix) {
			Columns = matrix.Columns; Rows = matrix.Rows;
			for(uint32_t j = 0; j < Rows; j++) {
				for(uint32_t i = 0; i < Columns; i++) rows[j].v[i] = (Type)matrix.rows[j].v[i];
			}
		}
		
		/// update matrix data
		void set(const Type &value, uint32_t columns = N, uint32_t rows = M) {
			TS_ASSERT(columns <= N && rows <= M);
			Columns = columns; Rows = rows;
			for(uint32_t j = 0; j < Rows; j++) {
				for(uint32_t i = 0; i < Columns; i++) MatrixNxM::rows[j].v[i] = value;
			}
		}
		void set(const Type *TS_RESTRICT matrix, uint32_t columns = N, uint32_t rows = M) {
			TS_ASSERT(columns <= N && rows <= M);
			Columns = columns; Rows = rows;
			for(uint32_t j = 0, k = 0; j < Rows; j++) {
				for(uint32_t i = 0; i < Columns; i++, k++) MatrixNxM::rows[j].v[i] = matrix[k];
			}
		}
		void set(const MatrixNxM &matrix) {
			Columns = matrix.Columns; Rows = matrix.Rows;
			for(uint32_t j = 0; j < Rows; j++) {
				for(uint32_t i = 0; i < Columns; i++) rows[j].v[i] = matrix.rows[j].v[i];
			}
		}
		void set(const VectorNxM &vector, uint32_t columns = N, uint32_t rows = M) {
			TS_ASSERT(columns <= N && rows <= M && vector.Size == columns * rows);
			Columns = columns; Rows = rows;
			for(uint32_t j = 0, k = 0; j < Rows; j++) {
				for(uint32_t i = 0; i < Columns; i++, k++) MatrixNxM::rows[j].v[i] = vector.v[k];
			}
		}
		void set(const InitializerList<Type> &list, uint32_t columns = N, uint32_t rows = M) {
			TS_ASSERT(columns <= N && rows <= M && list.size() == columns * rows);
			Columns = columns; Rows = rows;
			auto it = list.begin();
			for(uint32_t j = 0; j < Rows; j++) {
				for(uint32_t i = 0; i < Columns; i++) MatrixNxM::rows[j].v[i] = *it++;
			}
		}
		void set(const InitializerList<VectorN> &list, uint32_t rows = M) {
			TS_ASSERT(rows <= M && list.size() == rows);
			Rows = rows;
			auto it = list.begin();
			for(uint32_t j = 0; j < Rows; j++) MatrixNxM::rows[j] = *it++;
			Columns = MatrixNxM::rows[0].Size;
		}
		void get(Type *TS_RESTRICT matrix, uint32_t columns = N, uint32_t rows = M) {
			TS_ASSERT(columns <= Columns && rows <= Rows);
			for(uint32_t j = 0, k = 0; j < Rows; j++) {
				for(uint32_t i = 0; i < Columns; i++, k++) matrix[k] = MatrixNxM::rows[j].v[i];
			}
		}
		
		/// zero matrix
		void setZero() {
			for(uint32_t j = 0; j < Rows; j++) {
				for(uint32_t i = 0; i < Columns; i++) rows[j].v[i] = (Type)0.0f;
			}
		}
		
		/// identity matrix
		void setIdentity() {
			TS_ASSERT(Columns == Rows);
			for(uint32_t j = 0; j < Rows; j++) {
				for(uint32_t i = 0; i < Columns; i++) rows[j].v[i] = (Type)0.0f;
				rows[j].v[j] = (Type)1.0f;
			}
		}
		
		/// matrix to scalar operators
		MatrixNxM &operator*=(const Type &value) {
			for(uint32_t j = 0; j < Rows; j++) {
				for(uint32_t i = 0; i < Columns; i++) rows[j].v[i] *= value;
			}
			return *this;
		}
		MatrixNxM &operator/=(const Type &value) {
			for(uint32_t j = 0; j < Rows; j++) {
				for(uint32_t i = 0; i < Columns; i++) rows[j].v[i] /= value;
			}
			return *this;
		}
		
		/// matrix to matrix operators
		TS_INLINE MatrixNxM &operator=(const MatrixNxM &matrix) {
			Columns = matrix.Columns; Rows = matrix.Rows;
			for(uint32_t j = 0; j < Rows; j++) {
				for(uint32_t i = 0; i < Columns; i++) rows[j].v[i] = matrix.rows[j].v[i];
			}
			return *this;
		}
		
		/// matrix rows
		void setRow(uint32_t index, const VectorN &r) {
			TS_ASSERT(index < Rows);
			rows[index] = r;
		}
		const VectorN &getRow(uint32_t index) const {
			TS_ASSERT(index < Rows);
			return rows[index];
		}
		VectorN &getRow(uint32_t index) {
			TS_ASSERT(index < Rows);
			return rows[index];
		}
		
		/// matrix columns
		void setColumn(uint32_t index, const VectorM &c) {
			TS_ASSERT(index < Columns);
			for(uint32_t j = 0; j < Rows; j++) rows[j].v[index] = c.v[j];
		}
		VectorM getColumn(uint32_t index) const {
			TS_ASSERT(index < Columns);
			VectorM ret(Rows);
			for(uint32_t j = 0; j < Rows; j++) ret.v[j] = rows[j].v[index];
			return ret;
		}
		
		/// matrix data
		TS_INLINE const VectorN &operator[](uint32_t index) const {
			TS_ASSERT(index < Rows);
			return rows[index];
		}
		TS_INLINE VectorN &operator[](uint32_t index) {
			TS_ASSERT(index < Rows);
			return rows[index];
		}
		
		VectorN rows[M];
		
		uint32_t Columns = N;
		uint32_t Rows = M;
	};
	
	/// unary operators
	template <class Type, uint32_t N, uint32_t M> TS_INLINE MatrixNxM<Type, N, M> operator-(const MatrixNxM<Type, N, M> &m) {
		MatrixNxM<Type, N, M> ret(m.Columns, m.Rows);
		for(uint32_t j = 0; j < m.Rows; j++) {
			for(uint32_t i = 0; i < m.Columns; i++) ret.rows[j].v[i] = -m.rows[j].v[i];
		}
		return ret;
	}
	
	/// matrix to scalar operators
	template <class Type, uint32_t N, uint32_t M> TS_INLINE MatrixNxM<Type, N, M> operator*(const MatrixNxM<Type, N, M> &m, const Type &v) {
		MatrixNxM<Type, N, M> ret(m.Columns, m.Rows);
		for(uint32_t j = 0; j < m.Rows; j++) {
			for(uint32_t i = 0; i < m.Columns; i++) ret.rows[j].v[i] = m.rows[j].v[i] * v;
		}
		return ret;
	}
	template <class Type, uint32_t N, uint32_t M> TS_INLINE MatrixNxM<Type, N, M> operator/(const MatrixNxM<Type, N, M> &m, const Type &v) {
		MatrixNxM<Type, N, M> ret(m.Columns, m.Rows);
		for(uint32_t j = 0; j < m.Rows; j++) {
			for(uint32_t i = 0; i < m.Columns; i++) ret.rows[j].v[i] = m.rows[j].v[i] / v;
		}
		return ret;
	}
	
	/// matrix to matrix operators
	template <class Type, uint32_t N, uint32_t M> TS_INLINE MatrixNxM<Type, N, M> operator+(const MatrixNxM<Type, N, M> &m0, const MatrixNxM<Type, N, M> &m1) {
		TS_ASSERT(m0.Columns == m1.Columns && m0.Rows == m1.Rows);
		MatrixNxM<Type, N, M> ret(m0.Columns, m0.Rows);
		for(uint32_t j = 0; j < m0.Rows; j++) {
			for(uint32_t i = 0; i < m0.Columns; i++) ret.rows[j].v[i] = m0.rows[j].v[i] + m1.rows[j].v[i];
		}
		return ret;
	}
	template <class Type, uint32_t N, uint32_t M> TS_INLINE MatrixNxM<Type, N, M> operator-(const MatrixNxM<Type, N, M> &m0, const MatrixNxM<Type, N, M> &m1) {
		TS_ASSERT(m0.Columns == m1.Columns && m0.Rows == m1.Rows);
		MatrixNxM<Type, N, M> ret(m0.Columns, m0.Rows);
		for(uint32_t j = 0; j < m0.Rows; j++) {
			for(uint32_t i = 0; i < m0.Columns; i++) ret.rows[j].v[i] = m0.rows[j].v[i] - m1.rows[j].v[i];
		}
		return ret;
	}
	
	/// matrix to vector multiplication
	template <class Type, uint32_t N, uint32_t M> TS_INLINE VectorN<Type, M> operator*(const MatrixNxM<Type, N, M> &m, const VectorN<Type, N> &v) {
		TS_ASSERT(m.Columns == v.Size);
		VectorN<Type, M> ret(m.Rows);
		for(uint32_t j = 0; j < m.Rows; j++) {
			Type value = m.rows[j].v[0] * v.v[0];
			for(uint32_t i = 1; i < m.Columns; i++) value += m.rows[j].v[i] * v.v[i];
			ret.v[j] = value;
		}
		return ret;
	}
	
	/// vector to matrix multiplication
	template <class Type, uint32_t N, uint32_t M> TS_INLINE VectorN<Type, N> operator*(const VectorN<Type, M> &v, const MatrixNxM<Type, N, M> &m) {
		TS_ASSERT(v.Size == m.Rows);
		VectorN<Type, N> ret(m.Columns);
		for(uint32_t i = 0; i < m.Columns; i++) {
			Type value = m.rows[0].v[i] * v.v[0];
			for(uint32_t j = 1; j < m.Rows; j++) value += m.rows[j].v[i] * v.v[j];
			ret.v[i] = value;
		}
		return ret;
	}
	
	/// matrix to matrix multiplications
	template <class Type, uint32_t N, uint32_t M, uint32_t K> TS_INLINE MatrixNxM<Type, N, M> operator*(const MatrixNxM<Type, K, M> &m0, const MatrixNxM<Type, N, K> &m1) {
		TS_ASSERT(m0.Columns == m1.Rows);
		MatrixNxM<Type, N, M> ret(m1.Columns, m0.Rows);
		for(uint32_t j = 0; j < m0.Rows; j++) {
			for(uint32_t i = 0; i < m1.Columns; i++) {
				Type value = m0.rows[j].v[0] * m1.rows[0].v[i];
				for(uint32_t k = 1; k < m1.Rows; k++) value += m0.rows[j].v[k] * m1.rows[k].v[i];
				ret.rows[j].v[i] = value;
			}
		}
		return ret;
	}
	
	/// comparison operators
	template <class Type, uint32_t N, uint32_t M> TS_INLINE bool operator==(const MatrixNxM<Type, N, M> &m0, const MatrixNxM<Type, N, M> &m1) {
		TS_ASSERT(m0.Columns == m1.Columns && m0.Rows == m1.Rows);
		for(uint32_t j = 0; j < m0.Rows; j++) {
			for(uint32_t i = 0; i < m0.Columns; i++) if(m0.rows[j].v[i] != m1.rows[j].v[i]) return false;
		}
		return true;
	}
	template <class Type, uint32_t N, uint32_t M> TS_INLINE bool operator!=(const MatrixNxM<Type, N, M> &m0, const MatrixNxM<Type, N, M> &m1) {
		TS_ASSERT(m0.Columns == m1.Columns && m0.Rows == m1.Rows);
		for(uint32_t j = 0; j < m0.Rows; j++) {
			for(uint32_t i = 0; i < m0.Columns; i++) if(m0.rows[j].v[i] != m1.rows[j].v[i]) return true;
		}
		return false;
	}
	template <class Type, uint32_t N, uint32_t M> TS_INLINE bool compare(const MatrixNxM<Type, N, M> &m0, const MatrixNxM<Type, N, M> &m1, const Type &a) {
		TS_ASSERT(m0.Columns == m1.Columns && m0.Rows == m1.Rows);
		for(uint32_t j = 0; j < m0.Rows; j++) {
			for(uint32_t i = 0; i < m0.Columns; i++) if(!compare(m0.rows[j].v[i], m1.rows[j].v[i], a)) return false;
		}
		return true;
	}
	template <class Type, uint32_t N, uint32_t M> TS_INLINE bool compare(const MatrixNxM<Type, N, M> &m0, const MatrixNxM<Type, N, M> &m1, const Type &a, const Type &r) {
		TS_ASSERT(m0.Columns == m1.Columns && m0.Rows == m1.Rows);
		for(uint32_t j = 0; j < m0.Rows; j++) {
			for(uint32_t i = 0; i < m0.Columns; i++) if(!compare(m0.rows[j].v[i], m1.rows[j].v[i], a, r)) return false;
		}
		return true;
	}
	
	/// matrix functions
	template <class Type, uint32_t N> TS_INLINE MatrixNxM<Type, N, N> diagonal(const VectorN<Type, N> &v) {
		MatrixNxM<Type, N, N> ret(0.0f, v.Size, v.Size);
		for(uint32_t i = 0; i < v.Size; i++) ret.rows[i].v[i] = v.v[i];
		return ret;
	}
	template <class Type, uint32_t N, uint32_t M> TS_INLINE MatrixNxM<Type, M, N> transpose(const MatrixNxM<Type, N, M> &m) {
		MatrixNxM<Type, M, N> ret(m.Rows, m.Columns);
		for(uint32_t j = 0; j < m.Rows; j++) {
			for(uint32_t i = 0; i < m.Columns; i++) ret.rows[i].v[j] = m.rows[j].v[i];
		}
		return ret;
	}
	template <class Type, uint32_t N, uint32_t M> TS_INLINE MatrixNxM<Type, N, M> flipX(const MatrixNxM<Type, N, M> &m) {
		MatrixNxM<Type, N, M> ret(m.Columns, m.Rows);
		for(uint32_t j = 0; j < m.Rows; j++) {
			for(uint32_t i = 0; i < m.Columns; i++) ret.rows[j].v[i] = m.rows[j].v[m.Columns - i - 1];
		}
		return ret;
	}
	template <class Type, uint32_t N, uint32_t M> TS_INLINE MatrixNxM<Type, N, M> flipY(const MatrixNxM<Type, N, M> &m) {
		MatrixNxM<Type, N, M> ret(m.Columns, m.Rows);
		for(uint32_t j = 0; j < m.Rows; j++) {
			for(uint32_t i = 0; i < m.Columns; i++) ret.rows[j].v[i] = m.rows[m.Rows - j - 1].v[i];
		}
		return ret;
	}
	
	/*****************************************************************************\
	 *
	 * Jacobi Decomposition
	 *
	\*****************************************************************************/
	
	/**
	 * Computes eigenvectors and eigenvalues of symmetric matrix
	 */
	template <class Type, uint32_t N, uint32_t Iterations = 32>
	MatrixNxM<Type, N, N> jacobi(const MatrixNxM<Type, N, N> &m, MatrixNxM<Type, N, N> &v, Type threshold = 1e-6f) {
		TS_ASSERT(m.Columns == m.Rows);
		const uint32_t Size = m.Columns;
		v.setIdentity();
		Type old_sum = Maxf32;
		MatrixNxM<Type, N, N> ret = m, m0, m1;
		for(uint32_t iteration = 0; iteration < Iterations; iteration++) {
			uint32_t p = 0, q = 0;
			Type max = 0.0f, sum = 0.0f;
			for(uint32_t i = 0; i < Size; i++) {
				for(uint32_t j = i + 1; j < Size; j++) {
					Type v = abs(ret.rows[i].v[j]);
					if(max < v) { max = v; p = i; q = j; }
					sum += v;
				}
			}
			if(max < threshold || old_sum < sum) break;
			old_sum = sum;
			Type r = (ret.rows[p].v[p] - ret.rows[q].v[q]) / (ret.rows[p].v[q] * (Type)2.0f);
			Type t = sign(r) * rcp(sqrt(1.0f + r * r) + abs(r));
			Type c = rsqrt(1.0f + t * t);
			Type s = t * c;
			m0.setIdentity();
			m1.setIdentity();
			m0.rows[p].v[p] = c;
			m0.rows[p].v[q] = s;
			m0.rows[q].v[p] = -s;
			m0.rows[q].v[q] = c;
			m1.rows[p].v[p] = c;
			m1.rows[p].v[q] = -s;
			m1.rows[q].v[p] = s;
			m1.rows[q].v[q] = c;
			ret = m0 * ret * m1;
			v = v * m1;
		}
		return ret;
	}
	
	/*****************************************************************************\
	 *
	 * Lower Upper Decomposition
	 *
	\*****************************************************************************/
	
	/**
	 * Lower Upper Decomposition
	 */
	namespace LU {
		
		/// Lower Upper Decomposition
		/// Computes A = l * u decomposition
		template <class Type, uint32_t N>
		static bool decompose(const MatrixNxM<Type, N, N> &a, MatrixNxM<Type, N, N> &lu, VectorN<uint32_t, N> &indices, Type threshold = 0.0f) {
			TS_ASSERT(a.Columns == a.Rows);
			const uint32_t Size = lu.Columns;
			lu.set(a);
			indices.Size = Size;
			for(uint32_t i = 0; i < Size; i++) indices.v[i] = i;
			for(uint32_t i = 0; i < Size; i++) {
				uint32_t index = i;
				Type max = abs(lu.rows[i].v[i]);
				for(uint32_t j = i + 1; j < Size; j++) {
					Type v = abs(lu.rows[j].v[i]);
					if(max < v) { max = v; index = j; }
				}
				if(max <= threshold) return false;
				if(index != i) {
					Type *row_0 = lu.rows[i].v;
					Type *row_1 = lu.rows[index].v;
					swap(indices.v[i], indices.v[index]);
					for(uint32_t j = 0; j < Size; j++) swap(row_0[j], row_1[j]);
				}
				Type d = 1.0f / lu.rows[i].v[i];
				for(uint32_t j = i + 1; j < Size; j++) lu.rows[j].v[i] *= d;
				for(uint32_t j = i + 1; j < Size; j++) {
					Type d = lu.rows[j].v[i];
					for(uint32_t k = i + 1; k < Size; k++) lu.rows[j].v[k] -= lu.rows[i].v[k] * d;
				}
			}
			return true;
		}
		
		/// Lower Upper Decomposition
		/// Computes A = l * u decomposition
		template <class Type, uint32_t N>
		static bool decompose(const MatrixNxM<Type, N, N> &a, MatrixNxM<Type, N, N> &l, MatrixNxM<Type, N, N> &u, Type threshold = 0.0f) {
			TS_ASSERT(a.Columns == a.Rows);
			const uint32_t Size = a.Columns;
			l.set(Type(0.0f), Size, Size);
			u.set(Type(0.0f), Size, Size);
			MatrixNxM<Type, N, N> lu = a;
			for(uint32_t i = 0; i < Size; i++) {
				if(abs(lu.rows[i].v[i]) <= threshold) return false;
				Type d = 1.0f / lu.rows[i].v[i];
				for(uint32_t j = i + 1; j < Size; j++) lu.rows[j].v[i] *= d;
				for(uint32_t j = i + 1; j < Size; j++) {
					Type d = lu.rows[j].v[i];
					for(uint32_t k = i + 1; k < Size; k++) lu.rows[j].v[k] -= lu.rows[i].v[k] * d;
				}
				l.rows[i].v[i] = 1.0f;
				for(uint32_t j = 0; j < i; j++) l.rows[i].v[j] = lu.rows[i].v[j];
				for(uint32_t j = i; j < Size; j++) u.rows[i].v[j] = lu.rows[i].v[j];
			}
			return true;
		}
		
		/// Solution of linear argebraic equations
		/// Computes x vector for Ax = b equation
		template <class Type, uint32_t N>
		static VectorN<Type, N> solve(const MatrixNxM<Type, N, N> &lu, const VectorN<uint32_t, N> &indices, const VectorN<Type, N> &b) {
			TS_ASSERT(lu.Columns == lu.Rows && lu.Columns == indices.Size && lu.Columns == b.Size);
			const uint32_t Size = lu.Columns;
			VectorN<Type, N> ret(Size, Size);
			for(uint32_t i = 0; i < Size; i++) {
				Type value = b.v[indices.v[i]];
				for(uint32_t j = 0; j < i; j++) value -= lu.rows[i].v[j] * ret.v[j];
				ret.v[i] = value;
			}
			for(int32_t i = Size - 1; i >= 0; i--) {
				Type value = ret.v[i];
				for(uint32_t j = i + 1; j < Size; j++) value -= lu.rows[i].v[j] * ret.v[j];
				ret.v[i] = value / lu.rows[i].v[i];
			}
			return ret;
		}
		
		/// Matrix inversion
		/// Computes inverse matrix
		template <class Type, uint32_t N>
		static MatrixNxM<Type, N, N> inverse(const MatrixNxM<Type, N, N> &lu, const VectorN<uint32_t, N> &indices) {
			TS_ASSERT(lu.Columns == lu.Rows && lu.Columns == indices.Size);
			const uint32_t Size = lu.Columns;
			MatrixNxM<Type, N, N> ret(Size, Size);
			VectorN<Type, N> b(0.0f);
			for(uint32_t i = 0; i < Size; i++) {
				b.v[i] = 1.0f;
				VectorN<Type, N> col = solve(lu, indices, b);
				for(uint32_t j = 0; j < Size; j++) ret.rows[j].v[i] = col.v[j];
				b.v[i] = 0.0f;
			}
			return ret;
		}
		
		/// Matrix inversion
		template <class Type, uint32_t N>
		static MatrixNxM<Type, N, N> inverse(const MatrixNxM<Type, N, N> &m) {
			TS_ASSERT(m.Columns == m.Rows);
			MatrixNxM<Type, N, N> lu;
			VectorN<uint32_t, N> indices;
			if(decompose(m, lu, indices)) return inverse(lu, indices);
			return MatrixNxM<Type, N, N>(0.0f, m.Columns, m.Rows);
		}
	}
	
	/*****************************************************************************\
	 *
	 * Orthogonal Decomposition
	 *
	\*****************************************************************************/
	
	/**
	 * Orthogonal Decomposition
	 */
	namespace QR {
		
		/// Orthogonal Decomposition
		/// Computes A = q * r decomposition
		template <class Type, uint32_t N>
		static bool decompose(const MatrixNxM<Type, N, N> &a, MatrixNxM<Type, N, N> &qr, VectorN<Type, N> &c, VectorN<Type, N> &d) {
			TS_ASSERT(a.Columns == a.Rows);
			const uint32_t Size = a.Columns;
			qr.set(a);
			c.Size = Size;
			d.Size = Size;
			bool singular = false;
			for(uint32_t k = 0; k < Size - 1; k++) {
				Type scale = 0.0f;
				for(uint32_t i = k; i < Size; i++) scale = max(scale, abs(qr.rows[i].v[k]));
				if(scale == 0.0f) {
					singular = true;
					c.v[k] = 0.0f;
					d.v[k] = 0.0f;
				} else {
					Type s = 0.0f;
					for(uint32_t i = k; i < Size; i++) qr.rows[i].v[k] /= scale;
					for(uint32_t i = k; i < Size; i++) s += qr.rows[i].v[k] * qr.rows[i].v[k];
					Type sigma = sqrt(s);
					if(qr.rows[k].v[k] < 0.0f) sigma = -sigma;
					qr.rows[k].v[k] += sigma;
					c.v[k] = qr.rows[k].v[k] * sigma;
					d.v[k] = -scale * sigma;
					for(uint32_t j = k + 1; j < Size; j++) {
						Type s = 0.0f;
						for(uint32_t i = k; i < Size; i++) s += qr.rows[i].v[k] * qr.rows[i].v[j];
						Type tau = s / c.v[k];
						for(uint32_t i = k; i < Size; i++) qr.rows[i].v[j] -= qr.rows[i].v[k] * tau;
					}
				}
			}
			d.v[Size - 1] = qr.rows[Size - 1].v[Size - 1];
			singular |= (d.v[Size - 1] == 0.0f);
			return !singular;
		}
		
		/// Orthogonal Decomposition
		/// Computes A = q * r decomposition
		template <class Type, uint32_t N>
		static bool decompose(const MatrixNxM<Type, N, N> &a, MatrixNxM<Type, N, N> &q, MatrixNxM<Type, N, N> &r) {
			TS_ASSERT(a.Columns == a.Rows);
			const uint32_t Size = a.Columns;
			q.set(Type(0.0f));
			r.set(Type(0.0f));
			VectorN<Type, N> c, d;
			MatrixNxM<Type, N, N> qr;
			bool ret = decompose(a, qr, c, d);
			for(uint32_t i = 0; i < Size; i++) q.rows[i].v[i] = 1.0f;
			for(uint32_t i = 0; i < Size - 1; i++) {
				if(c.v[i] != 0.0f) {
					for(uint32_t j = 0; j < Size; j++) {
						Type s = 0.0f;
						for(uint32_t k = i; k < Size; k++) s += qr.rows[k].v[i] * q.rows[j].v[k];
						Type tau = s / c.v[i];
						for(uint32_t k = i; k < Size; k++) q.rows[j].v[k] -= qr.rows[k].v[i] * tau;
					}
				}
			}
			for(uint32_t j = 0; j < Size; j++) {
				r.rows[j].v[j] = d.v[j];
				for(uint32_t i = j + 1; i < Size; i++) {
					r.rows[j].v[i] = qr.rows[j].v[i];
				}
			}
			return ret;
		}
		
		/// Solution of linear argebraic equations
		/// Computes x vector for Ax = b equation
		template <class Type, uint32_t N>
		static VectorN<Type, N> solve(const MatrixNxM<Type, N, N> &qr, const VectorN<Type, N> &c, const VectorN<Type, N> &d, const VectorN<Type, N> &b) {
			TS_ASSERT(qr.Columns == qr.Rows && qr.Columns == c.Size && qr.Columns == d.Size);
			const uint32_t Size = qr.Columns;
			VectorN<Type, N> ret = b;
			for(uint32_t i = 0; i < Size - 1; i++) {
				Type s = 0.0f;
				for(uint32_t j = i; j < Size; j++) s += qr.rows[j].v[i] * ret.v[j];
				Type tau = s / c.v[i];
				for(uint32_t j = i; j < Size; j++) ret.v[j] -= qr.rows[j].v[i] * tau;
			}
			for(int32_t i = Size - 1; i >= 0; i--) {
				Type s = 0.0f;
				for(uint32_t j = i + 1; j < Size; j++) s += qr.rows[i].v[j] * ret.v[j];
				ret.v[i] = (ret.v[i] - s) / d.v[i];
			}
			return ret;
		}
		
		/// Matrix inversion
		/// Computes inverse matrix
		template <class Type, uint32_t N>
		static MatrixNxM<Type, N, N> inverse(const MatrixNxM<Type, N, N> &qr, const VectorN<Type, N> &c, const VectorN<Type, N> &d) {
			TS_ASSERT(qr.Columns == qr.Rows && qr.Columns == c.Size && qr.Columns == d.Size);
			const uint32_t Size = qr.Columns;
			MatrixNxM<Type, N, N> ret(Size, Size);
			VectorN<Type, N> b(0.0f);
			for(uint32_t i = 0; i < Size; i++) {
				b.v[i] = 1.0f;
				VectorN<Type, N> col = solve(qr, c, d, b);
				for(uint32_t j = 0; j < Size; j++) ret.rows[j].v[i] = col.v[j];
				b.v[i] = 0.0f;
			}
			return ret;
		}
		
		/// Matrix inversion
		template <class Type, uint32_t N>
		static MatrixNxM<Type, N, N> inverse(const MatrixNxM<Type, N, N> &m) {
			TS_ASSERT(m.Columns == m.Rows);
			MatrixNxM<Type, N, N> qr;
			VectorN<Type, N> c, d;
			if(decompose(m, qr, c, d)) return inverse(qr, c, d);
			return MatrixNxM<Type, N, N>(0.0f, m.Columns, m.Rows);
		}
	}
	
	/*****************************************************************************\
	 *
	 * Singular Value Decomposition
	 *
	\*****************************************************************************/
	
	/**
	 * Singular Value Decomposition
	 */
	namespace SVD {
		
		/// Computes sqrt(a^2 + b^2) function
		template <class Type> TS_INLINE Type pythagorean(Type a, Type b) {
			a = abs(a); b = abs(b);
			if(a > b) return a * sqrt(1.0f + (b / a) * (b / a));
			if(b != 0.0f) return b * sqrt(1.0f + (a / b) * (a / b));
			return 0.0f;
		}
		
		/// Singular Value Decomposition
		/// Computes A = u * diagonal(w) * transpose(v) matrix decomposition
		template <class Type, uint32_t N, uint32_t M, uint32_t Iterations = 32>
		static bool decompose(const MatrixNxM<Type, N, M> &a, MatrixNxM<Type, N, M> &u, VectorN<Type, N> &w, MatrixNxM<Type, N, N> &v) {
			u.set(a);
			w.set(Type(0.0f), a.Columns);
			v.set(Type(0.0f), a.Columns, a.Rows);
			const int32_t Columns = (int32_t)a.Columns;
			const int32_t Rows = (int32_t)a.Rows;
			int32_t i, j, k, l, n = 0, m;
			Type c, f, g = 0.0f, h, s, x, y, z;
			Type norm = 0.0f, scale = 0.0f;
			VectorN<Type, N> r(Type(0.0f));
			for(i = 0; i < Columns; i++) {
				l = i + 1;
				r.v[i] = scale * g;
				g = s = scale = 0.0f;
				if(i < Rows) {
					for(k = i; k < Rows; k++) {
						scale += abs(u.rows[k].v[i]);
					}
					if(scale != 0.0f) {
						for(k = i; k < Rows; k++) {
							u.rows[k].v[i] /= scale;
							s += u.rows[k].v[i] * u.rows[k].v[i];
						}
						g = -sqrt(s);
						f = u.rows[i].v[i];
						if(f < 0.0f) g = -g;
						h = f * g - s;
						u.rows[i].v[i] = f - g;
						for(j = l; j < Columns; j++) {
							for(s = 0.0f, k = i; k < Rows; k++) s += u.rows[k].v[i] * u.rows[k].v[j];
							f = s / h;
							for(k = i; k < Rows; k++) u.rows[k].v[j] += u.rows[k].v[i] * f;
						}
						for(k = i; k < Rows; k++) u.rows[k].v[i] *= scale;
					}
				}
				w.v[i] = scale * g;
				g = s = scale = 0.0f;
				if(i < Rows && i != Columns - 1) {
					for(k = l; k < Columns; k++) {
						scale += abs(u.rows[i].v[k]);
					}
					if(scale != 0.0f) {
						for(k = l; k < Columns; k++) {
							u.rows[i].v[k] /= scale;
							s += u.rows[i].v[k] * u.rows[i].v[k];
						}
						g = -sqrt(s);
						f = u.rows[i].v[l];
						if(f < 0.0f) g = -g;
						h = f * g - s;
						u.rows[i].v[l] = f - g;
						for(k = l; k < Columns; k++) {
							r.v[k] = u.rows[i].v[k] / h;
						}
						for(j = l; j < Rows; j++) {
							for(s = 0.0f, k = l; k < Columns; k++) s += u.rows[j].v[k] * u.rows[i].v[k];
							for(k = l; k < Columns; k++) u.rows[j].v[k] += r.v[k] * s;
						}
						for(k = l; k < Columns; k++) u.rows[i].v[k] *= scale;
					}
				}
				norm = max(norm, abs(w.v[i]) + abs(r.v[i]));
			}
			for(i = Columns - 1; i >= 0; i--) {
				l = i + 1;
				if(i < Columns - 1) {
					if(g != 0.0f) {
						for(j = l; j < Columns; j++) {
							v.rows[j].v[i] = (u.rows[i].v[j] / u.rows[i].v[l]) / g;
						}
						for(j = l; j < Columns; j++) {
							for(s = 0.0f, k = l; k < Columns; k++) s += u.rows[i].v[k] * v.rows[k].v[j];
							for(k = l; k < Columns; k++) v.rows[k].v[j] += v.rows[k].v[i] * s;
						}
					}
					for(j = l; j < Columns; j++) {
						v.rows[i].v[j] = 0.0f;
						v.rows[j].v[i] = 0.0f;
					}
				}
				v.rows[i].v[i] = 1.0f;
				g = r.v[i];
				l = i;
			}
			for(i = min(Columns, Rows) - 1; i >= 0; i--) {
				l = i + 1;
				g = w.v[i];
				for(j = l; j < Columns; j++) {
					u.rows[i].v[j] = 0.0f;
				}
				if(g != 0.0f) {
					for(j = l; j < Columns; j++) {
						for(s = 0.0f, k = l; k < Rows; k++) s += u.rows[k].v[i] * u.rows[k].v[j];
						f = (s / u.rows[i].v[i]) / g;
						for(k = i; k < Rows; k++) u.rows[k].v[j] += u.rows[k].v[i] * f;
					}
					for(j = i; j < Rows; j++) u.rows[j].v[i] /= g;
				} else {
					for(j = i; j < Rows; j++) u.rows[j].v[i] = 0.0f;
				}
				u.rows[i].v[i] += 1.0f;
			}
			for(k = Columns - 1; k >= 0; k--) {
				for(uint32_t iteration = 0; iteration <= Iterations; iteration++) {
					bool flag = true;
					for(l = k; l >= 0; l--) {
						n = l - 1;
						if(abs(r.v[l]) + norm == norm) { flag = false; break; }
						if(abs(w.v[n]) + norm == norm) break;
					}
					if(flag) {
						c = 0.0f;
						s = 1.0f;
						for(i = l; i <= k; i++) {
							f = s * r.v[i];
							r.v[i] = r.v[i] * c;
							if(abs(f) + norm == norm) break;
							g = w.v[i];
							h = pythagorean(f, g);
							w.v[i] = h;
							c = g / h;
							s = -f / h;
							for(j = 0; j < Rows; j++) {
								y = u.rows[j].v[n];
								z = u.rows[j].v[i];
								u.rows[j].v[n] = y * c + z * s;
								u.rows[j].v[i] = z * c - y * s;
							}
						}
					}
					z = w.v[k];
					if(l == k) {
						if(z < 0.0f) {
							w.v[k] = -z;
							for(j = 0; j < Columns; j++) v.rows[j].v[k] = -v.rows[j].v[k];
						}
						break;
					}
					if(iteration == Iterations) return false;
					x = w.v[l];
					n = k - 1;
					y = w.v[n];
					g = r.v[n];
					h = r.v[k];
					f = ((y - z) * (y + z) + (g - h) * (g + h)) / (2.0f * h * y);
					g = pythagorean(f, Type(1.0f));
					if(f < 0.0f) g = -g;
					f = ((x - z) * (x + z) + h * ((y / (f + g)) - h)) / x;
					c = s = 1.0f;
					for(j = l; j <= n; j++) {
						i = j + 1;
						g = r.v[i];
						y = w.v[i];
						h = s * g;
						g = c * g;
						z = pythagorean(f, h);
						r.v[j] = z;
						c = f / z;
						s = h / z;
						f = x * c + g * s;
						g = g * c - x * s;
						h = y * s;
						y *= c;
						for(m = 0; m < Columns; m++) {
							x = v.rows[m].v[j];
							z = v.rows[m].v[i];
							v.rows[m].v[j] = x * c + z * s;
							v.rows[m].v[i] = z * c - x * s;
						}
						z = pythagorean(f, h);
						w.v[j] = z;
						if(z != 0.0f) {
							c = f / z;
							s = h / z;
						}
						f = c * g + s * y;
						x = c * y - s * g;
						for(m = 0; m < Rows; m++) {
							y = u.rows[m].v[j];
							z = u.rows[m].v[i];
							u.rows[m].v[j] = y * c + z * s;
							u.rows[m].v[i] = z * c - y * s;
						}
					}
					r.v[l] = 0.0f;
					r.v[k] = f;
					w.v[k] = x;
				}
			}
			return true;
		}
		
		/// Solution of linear argebraic equations
		/// Computes x vector for Ax = b equation
		template <class Type, uint32_t N, uint32_t M>
		static VectorN<Type, N> solve(const MatrixNxM<Type, N, M> &u, const VectorN<Type, N> &w, const MatrixNxM<Type, N, N> &v, const VectorN<Type, M> &b, Type threshold = 1e-6f) {
			TS_ASSERT(u.Columns == u.Rows && u.Columns == w.Size && u.Columns == v.Columns && u.Rows == v.Rows);
			VectorN<Type, N> ret(u.Columns);
			VectorN<Type, N> temp;
			for(uint32_t i = 0; i < u.Columns; i++) {
				Type value = 0.0f;
				if(w.v[i] >= threshold) {
					value = u.rows[0].v[i] * b.v[0];
					for(uint32_t j = 1; j < u.Rows; j++) {
						value += u.rows[j].v[i] * b.v[j];
					}
					value /= w.v[i];
				}
				temp.v[i] = value;
			}
			for(uint32_t j = 0; j < u.Columns; j++) {
				Type value = v.rows[j].v[0] * temp.v[0];
				for(uint32_t i = 1; i < u.Columns; i++) {
					value += v.rows[j].v[i] * temp.v[i];
				}
				ret.v[j] = value;
			}
			return ret;
		}
		
		/// Matrix inversion
		/// Computes v * diagonal(1/w) * transpose(u) matrix
		template <class Type, uint32_t N>
		static MatrixNxM<Type, N, N> inverse(const MatrixNxM<Type, N, N> &u, const VectorN<Type, N> &w, const MatrixNxM<Type, N, N> &v, Type threshold = 1e-6f) {
			TS_ASSERT(u.Columns == u.Rows && u.Columns == w.Size && u.Columns == v.Columns && u.Rows == v.Rows);
			const uint32_t Size = u.Columns;
			MatrixNxM<Type, N, N> ret(Size, Size);
			MatrixNxM<Type, N, N> temp = v;
			for(uint32_t i = 0; i < Size; i++) {
				Type value = (w.v[i] < threshold) ? 0.0f : 1.0f / w.v[i];
				for(uint32_t j = 0; j < Size; j++) temp.rows[j].v[i] *= value;
			}
			for(uint32_t i = 0; i < Size; i++) {
				for(uint32_t j = 0; j < Size; j++) {
					Type value = temp.rows[i].v[0] * u.rows[j].v[0];
					for(uint32_t k = 1; k < Size; k++) value += temp.rows[i].v[k] * u.rows[j].v[k];
					ret.rows[i].v[j] = value;
				}
			}
			return ret;
		}
		
		/// Matrix inversion
		template <class Type, uint32_t N>
		static MatrixNxM<Type, N, N> inverse(const MatrixNxM<Type, N, N> &m, Type threshold = 1e-6f) {
			TS_ASSERT(m.Columns == m.Rows);
			VectorN<Type, N> w;
			MatrixNxM<Type, N, N> u;
			MatrixNxM<Type, N, N> v;
			if(decompose(m, u, w, v)) return inverse(u, w, v, threshold);
			return MatrixNxM<Type, N, N>(0.0f, m.Columns, m.Rows);
		}
	}
}

#endif /* __TELLUSIM_MATH_NUMERICAL_H__ */

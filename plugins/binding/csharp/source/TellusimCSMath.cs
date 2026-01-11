// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

using System;
using System.Runtime.InteropServices;

/*
 */
namespace Tellusim {
	
	/*****************************************************************************\
	 *
	 * Scalars
	 *
	\*****************************************************************************/
	
	/*
	 */
	public static partial class Base {
		
		/// 32-bit signed integer numbers
		public static int min(int v0, int v1) { return (v0 < v1) ? v0 : v1; }
		public static int max(int v0, int v1) { return (v0 < v1) ? v1 : v0; }
		public static int min(int v0, int v1, int v2) { return (v0 < v1) ? min(v0, v2) : min(v1, v2); }
		public static int max(int v0, int v1, int v2) { return (v0 < v1) ? max(v1, v2) : max(v0, v2); }
		public static int min(int v0, int v1, int v2, int v3) { return (v0 < v1) ? min(v0, v2, v3) : min(v1, v2, v3); }
		public static int max(int v0, int v1, int v2, int v3) { return (v0 < v1) ? max(v1, v2, v3) : max(v0, v2, v3); }
		public static int mid(int v0, int v1, int v2) { return (v0 < v1) ? ((v1 < v2) ? v1 : max(v0, v2)) : ((v0 < v2) ? v0 : max(v1, v2)); }
		public static int clamp(int v, int v0, int v1) { return min(max(v, v0), v1); }
		
		/// 64-bit signed integer numbers
		public static long min(long v0, long v1) { return (v0 < v1) ? v0 : v1; }
		public static long max(long v0, long v1) { return (v0 < v1) ? v1 : v0; }
		public static long min(long v0, long v1, long v2) { return (v0 < v1) ? min(v0, v2) : min(v1, v2); }
		public static long max(long v0, long v1, long v2) { return (v0 < v1) ? max(v1, v2) : max(v0, v2); }
		public static long min(long v0, long v1, long v2, long v3) { return (v0 < v1) ? min(v0, v2, v3) : min(v1, v2, v3); }
		public static long max(long v0, long v1, long v2, long v3) { return (v0 < v1) ? max(v1, v2, v3) : max(v0, v2, v3); }
		public static long mid(long v0, long v1, long v2) { return (v0 < v1) ? ((v1 < v2) ? v1 : max(v0, v2)) : ((v0 < v2) ? v0 : max(v1, v2)); }
		public static long clamp(long v, long v0, long v1) { return min(max(v, v0), v1); }
		
		/// 32-bit unsigned integer numbers
		public static bool ispot(uint x) { return ((x & (x - 1)) == 0); }
		public static bool isaligned(uint a, uint b) { return ispot(b) ? ((a & (b - 1)) == 0) : ((a / b) * b == a); }
		public static uint npot(uint x) { uint ret = 1; while(ret < x) ret += ret; return ret; }
		public static uint log2(uint x) { uint ret = 0; while(x > 1) { x >>= 1; ret++; } return ret; }
		public static uint sqrt(uint x) { uint ret = 0, y = (1 << 30); while(y > x) y >>= 2; while(y != 0) { if(x >= ret + y) { x -= ret + y; ret += y << 1; } ret >>= 1; y >>= 2; } return ret; }
		public static uint pow(uint x, uint y) { uint ret = 1; while(y != 0) { if((y & 1) != 0) ret *= x; x *= x; y >>= 1; } return ret; }
		public static uint align(uint a, uint b) { return ispot(b) ? ((a + b - 1) & ~(b - 1)) : (((a + b - 1) / b) * b); }
		public static uint udiv(uint a, uint b) { return (a + b - 1) / b; }
		
		public static uint min(uint v0, uint v1) { return (v0 < v1) ? v0 : v1; }
		public static uint max(uint v0, uint v1) { return (v0 < v1) ? v1 : v0; }
		public static uint min(uint v0, uint v1, uint v2) { return (v0 < v1) ? min(v0, v2) : min(v1, v2); }
		public static uint max(uint v0, uint v1, uint v2) { return (v0 < v1) ? max(v1, v2) : max(v0, v2); }
		public static uint min(uint v0, uint v1, uint v2, uint v3) { return (v0 < v1) ? min(v0, v2, v3) : min(v1, v2, v3); }
		public static uint max(uint v0, uint v1, uint v2, uint v3) { return (v0 < v1) ? max(v1, v2, v3) : max(v0, v2, v3); }
		public static uint mid(uint v0, uint v1, uint v2) { return (v0 < v1) ? ((v1 < v2) ? v1 : max(v0, v2)) : ((v0 < v2) ? v0 : max(v1, v2)); }
		public static uint clamp(uint v, uint v0, uint v1) { return min(max(v, v0), v1); }
		
		/// 64-bit unsigned integer numbers
		public static bool ispot(ulong x) { return ((x & (x - 1)) == 0); }
		public static bool isaligned(ulong a, ulong b) { return ispot(b) ? ((a & (b - 1)) == 0) : ((a / b) * b == a); }
		public static ulong npot(ulong x) { ulong ret = 1; while(ret < x) ret += ret; return ret; }
		public static ulong log2(ulong x) { ulong ret = 0; while(x > 1) { x >>= 1; ret++; } return ret; }
		public static ulong sqrt(ulong x) { ulong ret = 0, y = (1 << 30); while(y > x) y >>= 2; while(y != 0) { if(x >= ret + y) { x -= ret + y; ret += y << 1; } ret >>= 1; y >>= 2; } return ret; }
		public static ulong pow(ulong x, ulong y) { ulong ret = 1; while(y != 0) { if((y & 1) != 0) ret *= x; x *= x; y >>= 1; } return ret; }
		public static ulong align(ulong a, ulong b) { return ispot(b) ? ((a + b - 1) & ~(b - 1)) : (((a + b - 1) / b) * b); }
		public static ulong udiv(ulong a, ulong b) { return (a + b - 1) / b; }
		
		public static ulong min(ulong v0, ulong v1) { return (v0 < v1) ? v0 : v1; }
		public static ulong max(ulong v0, ulong v1) { return (v0 < v1) ? v1 : v0; }
		public static ulong min(ulong v0, ulong v1, ulong v2) { return (v0 < v1) ? min(v0, v2) : min(v1, v2); }
		public static ulong max(ulong v0, ulong v1, ulong v2) { return (v0 < v1) ? max(v1, v2) : max(v0, v2); }
		public static ulong min(ulong v0, ulong v1, ulong v2, ulong v3) { return (v0 < v1) ? min(v0, v2, v3) : min(v1, v2, v3); }
		public static ulong max(ulong v0, ulong v1, ulong v2, ulong v3) { return (v0 < v1) ? max(v1, v2, v3) : max(v0, v2, v3); }
		public static ulong mid(ulong v0, ulong v1, ulong v2) { return (v0 < v1) ? ((v1 < v2) ? v1 : max(v0, v2)) : ((v0 < v2) ? v0 : max(v1, v2)); }
		public static ulong clamp(ulong v, ulong v0, ulong v1) { return min(max(v, v0), v1); }
		
		/// 32-bit floating point numbers
		public static float min(float v0, float v1) { return (v0 < v1) ? v0 : v1; }
		public static float max(float v0, float v1) { return (v0 < v1) ? v1 : v0; }
		public static float min(float v0, float v1, float v2) { return (v0 < v1) ? min(v0, v2) : min(v1, v2); }
		public static float max(float v0, float v1, float v2) { return (v0 < v1) ? max(v1, v2) : max(v0, v2); }
		public static float min(float v0, float v1, float v2, float v3) { return (v0 < v1) ? min(v0, v2, v3) : min(v1, v2, v3); }
		public static float max(float v0, float v1, float v2, float v3) { return (v0 < v1) ? max(v1, v2, v3) : max(v0, v2, v3); }
		public static float mid(float v0, float v1, float v2) { return (v0 < v1) ? ((v1 < v2) ? v1 : max(v0, v2)) : ((v0 < v2) ? v0 : max(v1, v2)); }
		public static float clamp(float v, float v0, float v1) { return min(max(v, v0), v1); }
		public static float saturate(float v) { return min(max(v, 0.0f), 1.0f); }
		
		public static float lerp(float v0, float v1, float k) { return v0 + (v1 - v0) * k; }
		
		/// 64-bit floating point numbers
		public static double min(double v0, double v1) { return (v0 < v1) ? v0 : v1; }
		public static double max(double v0, double v1) { return (v0 < v1) ? v1 : v0; }
		public static double min(double v0, double v1, double v2) { return (v0 < v1) ? min(v0, v2) : min(v1, v2); }
		public static double max(double v0, double v1, double v2) { return (v0 < v1) ? max(v1, v2) : max(v0, v2); }
		public static double min(double v0, double v1, double v2, double v3) { return (v0 < v1) ? min(v0, v2, v3) : min(v1, v2, v3); }
		public static double max(double v0, double v1, double v2, double v3) { return (v0 < v1) ? max(v1, v2, v3) : max(v0, v2, v3); }
		public static double mid(double v0, double v1, double v2) { return (v0 < v1) ? ((v1 < v2) ? v1 : max(v0, v2)) : ((v0 < v2) ? v0 : max(v1, v2)); }
		public static double clamp(double v, double v0, double v1) { return min(max(v, v0), v1); }
		public static double saturate(double v) { return min(max(v, 0.0), 1.0); }
		
		public static double lerp(double v0, double v1, double k) { return v0 + (v1 - v0) * k; }
		
		/// packed floating point numbers
		public static ushort f32tof16(float f) { return ts_f32tof16(f); }
		public static float f16tof32(ushort h) { return ts_f16tof32(h); }
		public static uint f32tof21(float f) { return ts_f32tof21(f); }
		public static float f21tof32(uint h) { return ts_f21tof32(h); }
		public static uint f32tof24(float f) { return ts_f32tof24(f); }
		public static float f24tof32(uint h) { return ts_f24tof32(h); }
		
		[DllImport(Import)] private static extern ushort ts_f32tof16(float f);
		[DllImport(Import)] private static extern float ts_f16tof32(ushort h);
		[DllImport(Import)] private static extern uint ts_f32tof21(float f);
		[DllImport(Import)] private static extern float ts_f21tof32(uint h);
		[DllImport(Import)] private static extern uint ts_f32tof24(float f);
		[DllImport(Import)] private static extern float ts_f24tof32(uint h);
	}
	
	/*****************************************************************************\
	 *
	 * Vector2
	 *
	\*****************************************************************************/
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct Vector2i {
		
		public Vector2i(int v) { x = v; y = v; }
		public Vector2i(int x, int y) { this.x = x; this.y = y; }
		public Vector2i(in Vector2i v) { x = v.x; y = v.y; }
		public Vector2i(in Vector3i v) { x = v.x; y = v.y; }
		public Vector2i(in Vector4i v) { x = v.x; y = v.y; }
		public Vector2i(in Vector2u v) { x = (int)v.x; y = (int)v.y; }
		public Vector2i(in Vector2f v) { x = (int)v.x; y = (int)v.y; }
		public Vector2i(in Vector2d v) { x = (int)v.x; y = (int)v.y; }
		public Vector2i(in int[] v) { x = v[0]; y = v[1]; }
		
		public static Vector2i operator-(in Vector2i v) { Vector2i ret = new Vector2i(); tsVector2i_neg(ref ret, in v); return ret; }
		
		public static Vector2i operator*(in Vector2i v0, int v1) { Vector2i ret = new Vector2i(); tsVector2i_mul1(ref ret, in v0, v1); return ret; }
		public static Vector2i operator/(in Vector2i v0, int v1) { Vector2i ret = new Vector2i(); tsVector2i_div1(ref ret, in v0, v1); return ret; }
		public static Vector2i operator+(in Vector2i v0, int v1) { Vector2i ret = new Vector2i(); tsVector2i_add1(ref ret, in v0, v1); return ret; }
		public static Vector2i operator-(in Vector2i v0, int v1) { Vector2i ret = new Vector2i(); tsVector2i_sub1(ref ret, in v0, v1); return ret; }
		public static Vector2i operator&(in Vector2i v0, int v1) { Vector2i ret = new Vector2i(); tsVector2i_and1(ref ret, in v0, v1); return ret; }
		public static Vector2i operator|(in Vector2i v0, int v1) { Vector2i ret = new Vector2i(); tsVector2i_or1(ref ret, in v0, v1); return ret; }
		public static Vector2i operator^(in Vector2i v0, int v1) { Vector2i ret = new Vector2i(); tsVector2i_xor1(ref ret, in v0, v1); return ret; }
		public static Vector2i operator<<(in Vector2i v0, int v1) { Vector2i ret = new Vector2i(); tsVector2i_shl1(ref ret, in v0, v1); return ret; }
		public static Vector2i operator>>(in Vector2i v0, int v1) { Vector2i ret = new Vector2i(); tsVector2i_shr1(ref ret, in v0, v1); return ret; }
		
		public static Vector2i operator*(in Vector2i v0, in Vector2i v1) { Vector2i ret = new Vector2i(); tsVector2i_mul(ref ret, in v0, in v1); return ret; }
		public static Vector2i operator/(in Vector2i v0, in Vector2i v1) { Vector2i ret = new Vector2i(); tsVector2i_div(ref ret, in v0, in v1); return ret; }
		public static Vector2i operator+(in Vector2i v0, in Vector2i v1) { Vector2i ret = new Vector2i(); tsVector2i_add(ref ret, in v0, in v1); return ret; }
		public static Vector2i operator-(in Vector2i v0, in Vector2i v1) { Vector2i ret = new Vector2i(); tsVector2i_sub(ref ret, in v0, in v1); return ret; }
		public static Vector2i operator&(in Vector2i v0, in Vector2i v1) { Vector2i ret = new Vector2i(); tsVector2i_and(ref ret, in v0, in v1); return ret; }
		public static Vector2i operator|(in Vector2i v0, in Vector2i v1) { Vector2i ret = new Vector2i(); tsVector2i_or(ref ret, in v0, in v1); return ret; }
		public static Vector2i operator^(in Vector2i v0, in Vector2i v1) { Vector2i ret = new Vector2i(); tsVector2i_xor(ref ret, in v0, in v1); return ret; }
		
		public Vector2i abs() { Vector2i ret = new Vector2i(); tsVector2i_abs(ref ret, in this); return ret; }
		
		public static Vector2i min(in Vector2i v0, in Vector2i v1) { Vector2i ret = new Vector2i(); tsVector2i_min(ref ret, in v0, in v1); return ret; }
		public static Vector2i max(in Vector2i v0, in Vector2i v1) { Vector2i ret = new Vector2i(); tsVector2i_max(ref ret, in v0, in v1); return ret; }
		
		public Vector2i clamp(in Vector2i v0, in Vector2i v1) { Vector2i ret = new Vector2i(); tsVector2i_clamp(ref ret, in this, in v0, in v1); return ret; }
		
		public override string ToString() { return System.String.Format("({0} {1})", x, y); }
		
		[DllImport(Base.Import)] private static extern IntPtr tsVector2i_abs(ref Vector2i ret, in Vector2i v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2i_neg(ref Vector2i ret, in Vector2i v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2i_mul1(ref Vector2i ret, in Vector2i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2i_div1(ref Vector2i ret, in Vector2i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2i_add1(ref Vector2i ret, in Vector2i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2i_sub1(ref Vector2i ret, in Vector2i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2i_and1(ref Vector2i ret, in Vector2i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2i_or1(ref Vector2i ret, in Vector2i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2i_xor1(ref Vector2i ret, in Vector2i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2i_shl1(ref Vector2i ret, in Vector2i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2i_shr1(ref Vector2i ret, in Vector2i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2i_mul(ref Vector2i ret, in Vector2i v0, in Vector2i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2i_div(ref Vector2i ret, in Vector2i v0, in Vector2i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2i_add(ref Vector2i ret, in Vector2i v0, in Vector2i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2i_sub(ref Vector2i ret, in Vector2i v0, in Vector2i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2i_and(ref Vector2i ret, in Vector2i v0, in Vector2i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2i_or(ref Vector2i ret, in Vector2i v0, in Vector2i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2i_xor(ref Vector2i ret, in Vector2i v0, in Vector2i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2i_min(ref Vector2i ret, in Vector2i v0, in Vector2i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2i_max(ref Vector2i ret, in Vector2i v0, in Vector2i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2i_clamp(ref Vector2i ret, in Vector2i v, in Vector2i v0, in Vector2i v1);
		
		public static readonly Vector2i zero = new Vector2i(0);
		public static readonly Vector2i oneX = new Vector2i(1, 0);
		public static readonly Vector2i oneY = new Vector2i(0, 1);
		public static readonly Vector2i one = new Vector2i(1);
		
		public int x, y;
	}
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct Vector2u {
		
		public Vector2u(uint v) { x = v; y = v; }
		public Vector2u(uint x, uint y) { this.x = x; this.y = y; }
		public Vector2u(in Vector2u v) { x = v.x; y = v.y; }
		public Vector2u(in Vector3u v) { x = v.x; y = v.y; }
		public Vector2u(in Vector4u v) { x = v.x; y = v.y; }
		public Vector2u(in Vector2i v) { x = (uint)v.x; y = (uint)v.y; }
		public Vector2u(in Vector2f v) { x = (uint)v.x; y = (uint)v.y; }
		public Vector2u(in Vector2d v) { x = (uint)v.x; y = (uint)v.y; }
		public Vector2u(in uint[] v) { x = v[0]; y = v[1]; }
		
		public static Vector2u operator*(in Vector2u v0, uint v1) { Vector2u ret = new Vector2u(); tsVector2u_mul1(ref ret, in v0, v1); return ret; }
		public static Vector2u operator/(in Vector2u v0, uint v1) { Vector2u ret = new Vector2u(); tsVector2u_div1(ref ret, in v0, v1); return ret; }
		public static Vector2u operator+(in Vector2u v0, uint v1) { Vector2u ret = new Vector2u(); tsVector2u_add1(ref ret, in v0, v1); return ret; }
		public static Vector2u operator-(in Vector2u v0, uint v1) { Vector2u ret = new Vector2u(); tsVector2u_sub1(ref ret, in v0, v1); return ret; }
		public static Vector2u operator&(in Vector2u v0, uint v1) { Vector2u ret = new Vector2u(); tsVector2u_and1(ref ret, in v0, v1); return ret; }
		public static Vector2u operator|(in Vector2u v0, uint v1) { Vector2u ret = new Vector2u(); tsVector2u_or1(ref ret, in v0, v1); return ret; }
		public static Vector2u operator^(in Vector2u v0, uint v1) { Vector2u ret = new Vector2u(); tsVector2u_xor1(ref ret, in v0, v1); return ret; }
		public static Vector2u operator<<(in Vector2u v0, int v1) { Vector2u ret = new Vector2u(); tsVector2u_shl1(ref ret, in v0, (uint)v1); return ret; }
		public static Vector2u operator>>(in Vector2u v0, int v1) { Vector2u ret = new Vector2u(); tsVector2u_shr1(ref ret, in v0, (uint)v1); return ret; }
		
		public static Vector2u operator*(in Vector2u v0, in Vector2u v1) { Vector2u ret = new Vector2u(); tsVector2u_mul(ref ret, in v0, in v1); return ret; }
		public static Vector2u operator/(in Vector2u v0, in Vector2u v1) { Vector2u ret = new Vector2u(); tsVector2u_div(ref ret, in v0, in v1); return ret; }
		public static Vector2u operator+(in Vector2u v0, in Vector2u v1) { Vector2u ret = new Vector2u(); tsVector2u_add(ref ret, in v0, in v1); return ret; }
		public static Vector2u operator-(in Vector2u v0, in Vector2u v1) { Vector2u ret = new Vector2u(); tsVector2u_sub(ref ret, in v0, in v1); return ret; }
		public static Vector2u operator&(in Vector2u v0, in Vector2u v1) { Vector2u ret = new Vector2u(); tsVector2u_and(ref ret, in v0, in v1); return ret; }
		public static Vector2u operator|(in Vector2u v0, in Vector2u v1) { Vector2u ret = new Vector2u(); tsVector2u_or(ref ret, in v0, in v1); return ret; }
		public static Vector2u operator^(in Vector2u v0, in Vector2u v1) { Vector2u ret = new Vector2u(); tsVector2u_xor(ref ret, in v0, in v1); return ret; }
		
		public static Vector2u min(in Vector2u v0, in Vector2u v1) { Vector2u ret = new Vector2u(); tsVector2u_min(ref ret, in v0, in v1); return ret; }
		public static Vector2u max(in Vector2u v0, in Vector2u v1) { Vector2u ret = new Vector2u(); tsVector2u_max(ref ret, in v0, in v1); return ret; }
		
		public Vector2u clamp(in Vector2u v0, in Vector2u v1) { Vector2u ret = new Vector2u(); tsVector2u_clamp(ref ret, in this, in v0, in v1); return ret; }
		
		public override string ToString() { return System.String.Format("({0} {1})", x, y); }
		
		[DllImport(Base.Import)] private static extern IntPtr tsVector2u_mul1(ref Vector2u ret, in Vector2u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2u_div1(ref Vector2u ret, in Vector2u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2u_add1(ref Vector2u ret, in Vector2u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2u_sub1(ref Vector2u ret, in Vector2u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2u_and1(ref Vector2u ret, in Vector2u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2u_or1(ref Vector2u ret, in Vector2u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2u_xor1(ref Vector2u ret, in Vector2u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2u_shl1(ref Vector2u ret, in Vector2u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2u_shr1(ref Vector2u ret, in Vector2u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2u_mul(ref Vector2u ret, in Vector2u v0, in Vector2u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2u_div(ref Vector2u ret, in Vector2u v0, in Vector2u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2u_add(ref Vector2u ret, in Vector2u v0, in Vector2u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2u_sub(ref Vector2u ret, in Vector2u v0, in Vector2u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2u_and(ref Vector2u ret, in Vector2u v0, in Vector2u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2u_or(ref Vector2u ret, in Vector2u v0, in Vector2u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2u_xor(ref Vector2u ret, in Vector2u v0, in Vector2u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2u_min(ref Vector2u ret, in Vector2u v0, in Vector2u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2u_max(ref Vector2u ret, in Vector2u v0, in Vector2u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2u_clamp(ref Vector2u ret, in Vector2u v, in Vector2u v0, in Vector2u v1);
		
		public static readonly Vector2u zero = new Vector2u(0);
		public static readonly Vector2u oneX = new Vector2u(1, 0);
		public static readonly Vector2u oneY = new Vector2u(0, 1);
		public static readonly Vector2u one = new Vector2u(1);
		
		public uint x, y;
	}
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct Vector2f {
		
		public Vector2f(float v) { x = v; y = v; }
		public Vector2f(float x, float y) { this.x = x; this.y = y; }
		public Vector2f(in Vector2f v) { x = v.x; y = v.y; }
		public Vector2f(in Vector3f v) { x = v.x; y = v.y; }
		public Vector2f(in Vector4f v) { x = v.x; y = v.y; }
		public Vector2f(in Vector2i v) { x = (float)v.x; y = (float)v.y; }
		public Vector2f(in Vector2u v) { x = (float)v.x; y = (float)v.y; }
		public Vector2f(in Vector2d v) { x = (float)v.x; y = (float)v.y; }
		public Vector2f(in float[] v) { x = v[0]; y = v[1]; }
		
		public static Vector2f operator-(in Vector2f v) { Vector2f ret = new Vector2f(); tsVector2f_neg(ref ret, in v); return ret; }
		
		public static Vector2f operator*(in Vector2f v0, float v1) { Vector2f ret = new Vector2f(); tsVector2f_mul1(ref ret, in v0, v1); return ret; }
		public static Vector2f operator/(in Vector2f v0, float v1) { Vector2f ret = new Vector2f(); tsVector2f_div1(ref ret, in v0, v1); return ret; }
		public static Vector2f operator+(in Vector2f v0, float v1) { Vector2f ret = new Vector2f(); tsVector2f_add1(ref ret, in v0, v1); return ret; }
		public static Vector2f operator-(in Vector2f v0, float v1) { Vector2f ret = new Vector2f(); tsVector2f_sub1(ref ret, in v0, v1); return ret; }
		
		public static Vector2f operator*(in Vector2f v0, in Vector2f v1) { Vector2f ret = new Vector2f(); tsVector2f_mul(ref ret, in v0, in v1); return ret; }
		public static Vector2f operator/(in Vector2f v0, in Vector2f v1) { Vector2f ret = new Vector2f(); tsVector2f_div(ref ret, in v0, in v1); return ret; }
		public static Vector2f operator+(in Vector2f v0, in Vector2f v1) { Vector2f ret = new Vector2f(); tsVector2f_add(ref ret, in v0, in v1); return ret; }
		public static Vector2f operator-(in Vector2f v0, in Vector2f v1) { Vector2f ret = new Vector2f(); tsVector2f_sub(ref ret, in v0, in v1); return ret; }
		
		public Vector2f abs() { Vector2f ret = new Vector2f(); tsVector2f_abs(ref ret, in this); return ret; }
		
		public static Vector2f min(in Vector2f v0, in Vector2f v1) { Vector2f ret = new Vector2f(); tsVector2f_min(ref ret, in v0, in v1); return ret; }
		public static Vector2f max(in Vector2f v0, in Vector2f v1) { Vector2f ret = new Vector2f(); tsVector2f_max(ref ret, in v0, in v1); return ret; }
		
		public Vector2f clamp(in Vector2f v0, in Vector2f v1) { Vector2f ret = new Vector2f(); tsVector2f_clamp(ref ret, in this, in v0, in v1); return ret; }
		public Vector2f saturate() { Vector2f ret = new Vector2f(); tsVector2f_saturate(ref ret, in this); return ret; }
		
		public static float dot(in Vector2f v0, in Vector2f v1) { return tsVector2f_dot(in v0, in v1); }
		public static float cross(in Vector2f v0, in Vector2f v1) { return tsVector2f_cross(in v0, in v1); }
		
		public float length() { return tsVector2f_length(in this); }
		public Vector2f normalize() { Vector2f ret = new Vector2f(); tsVector2f_normalize(ref ret, in this); return ret; }
		
		public static Vector2f lerp(in Vector2f v0, in Vector2f v1, float k) { Vector2f ret = new Vector2f(); tsVector2f_lerp(ref ret, in v0, in v1, k); return ret; }
		
		public override string ToString() { return System.String.Format("({0} {1})", x, y); }
		
		[DllImport(Base.Import)] private static extern IntPtr tsVector2f_abs(ref Vector2f ret, in Vector2f v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2f_neg(ref Vector2f ret, in Vector2f v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2f_mul1(ref Vector2f ret, in Vector2f v0, float v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2f_div1(ref Vector2f ret, in Vector2f v0, float v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2f_add1(ref Vector2f ret, in Vector2f v0, float v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2f_sub1(ref Vector2f ret, in Vector2f v0, float v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2f_mul(ref Vector2f ret, in Vector2f v0, in Vector2f v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2f_div(ref Vector2f ret, in Vector2f v0, in Vector2f v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2f_add(ref Vector2f ret, in Vector2f v0, in Vector2f v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2f_sub(ref Vector2f ret, in Vector2f v0, in Vector2f v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2f_min(ref Vector2f ret, in Vector2f v0, in Vector2f v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2f_max(ref Vector2f ret, in Vector2f v0, in Vector2f v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2f_clamp(ref Vector2f ret, in Vector2f v, in Vector2f v0, in Vector2f v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2f_saturate(ref Vector2f ret, in Vector2f v);
		[DllImport(Base.Import)] private static extern float tsVector2f_dot(in Vector2f v0, in Vector2f v1);
		[DllImport(Base.Import)] private static extern float tsVector2f_cross(in Vector2f v0, in Vector2f v1);
		[DllImport(Base.Import)] private static extern float tsVector2f_length(in Vector2f v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2f_normalize(ref Vector2f ret, in Vector2f v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2f_lerp(ref Vector2f ret, in Vector2f v0, in Vector2f v1, float k);
		
		public static readonly Vector2f zero = new Vector2f(0.0f);
		public static readonly Vector2f oneX = new Vector2f(1.0f, 0.0f);
		public static readonly Vector2f oneY = new Vector2f(0.0f, 1.0f);
		public static readonly Vector2f one = new Vector2f(1.0f);
		
		public float x, y;
	}
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct Vector2d {
		
		public Vector2d(double v) { x = v; y = v; }
		public Vector2d(double x, double y) { this.x = x; this.y = y; }
		public Vector2d(in Vector2d v) { x = v.x; y = v.y; }
		public Vector2d(in Vector3d v) { x = v.x; y = v.y; }
		public Vector2d(in Vector4d v) { x = v.x; y = v.y; }
		public Vector2d(in Vector2i v) { x = (double)v.x; y = (double)v.y; }
		public Vector2d(in Vector2u v) { x = (double)v.x; y = (double)v.y; }
		public Vector2d(in Vector2f v) { x = (double)v.x; y = (double)v.y; }
		public Vector2d(in double[] v) { x = v[0]; y = v[1]; }
		
		public static Vector2d operator-(in Vector2d v) { Vector2d ret = new Vector2d(); tsVector2d_neg(ref ret, in v); return ret; }
		
		public static Vector2d operator*(in Vector2d v0, double v1) { Vector2d ret = new Vector2d(); tsVector2d_mul1(ref ret, in v0, v1); return ret; }
		public static Vector2d operator/(in Vector2d v0, double v1) { Vector2d ret = new Vector2d(); tsVector2d_div1(ref ret, in v0, v1); return ret; }
		public static Vector2d operator+(in Vector2d v0, double v1) { Vector2d ret = new Vector2d(); tsVector2d_add1(ref ret, in v0, v1); return ret; }
		public static Vector2d operator-(in Vector2d v0, double v1) { Vector2d ret = new Vector2d(); tsVector2d_sub1(ref ret, in v0, v1); return ret; }
		
		public static Vector2d operator*(in Vector2d v0, in Vector2d v1) { Vector2d ret = new Vector2d(); tsVector2d_mul(ref ret, in v0, in v1); return ret; }
		public static Vector2d operator/(in Vector2d v0, in Vector2d v1) { Vector2d ret = new Vector2d(); tsVector2d_div(ref ret, in v0, in v1); return ret; }
		public static Vector2d operator+(in Vector2d v0, in Vector2d v1) { Vector2d ret = new Vector2d(); tsVector2d_add(ref ret, in v0, in v1); return ret; }
		public static Vector2d operator-(in Vector2d v0, in Vector2d v1) { Vector2d ret = new Vector2d(); tsVector2d_sub(ref ret, in v0, in v1); return ret; }
		
		public Vector2d abs() { Vector2d ret = new Vector2d(); tsVector2d_abs(ref ret, in this); return ret; }
		
		public static Vector2d min(in Vector2d v0, in Vector2d v1) { Vector2d ret = new Vector2d(); tsVector2d_min(ref ret, in v0, in v1); return ret; }
		public static Vector2d max(in Vector2d v0, in Vector2d v1) { Vector2d ret = new Vector2d(); tsVector2d_max(ref ret, in v0, in v1); return ret; }
		
		public Vector2d clamp(in Vector2d v0, in Vector2d v1) { Vector2d ret = new Vector2d(); tsVector2d_clamp(ref ret, in this, in v0, in v1); return ret; }
		public Vector2d saturate() { Vector2d ret = new Vector2d(); tsVector2d_saturate(ref ret, in this); return ret; }
		
		public static double dot(in Vector2d v0, in Vector2d v1) { return tsVector2d_dot(in v0, in v1); }
		public static double cross(in Vector2d v0, in Vector2d v1) { return tsVector2d_cross(in v0, in v1); }
		
		public double length() { return tsVector2d_length(in this); }
		public Vector2d normalize() { Vector2d ret = new Vector2d(); tsVector2d_normalize(ref ret, in this); return ret; }
		
		public static Vector2d lerp(in Vector2d v0, in Vector2d v1, double k) { Vector2d ret = new Vector2d(); tsVector2d_lerp(ref ret, in v0, in v1, k); return ret; }
		
		public override string ToString() { return System.String.Format("({0} {1})", x, y); }
		
		[DllImport(Base.Import)] private static extern IntPtr tsVector2d_abs(ref Vector2d ret, in Vector2d v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2d_neg(ref Vector2d ret, in Vector2d v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2d_mul1(ref Vector2d ret, in Vector2d v0, double v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2d_div1(ref Vector2d ret, in Vector2d v0, double v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2d_add1(ref Vector2d ret, in Vector2d v0, double v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2d_sub1(ref Vector2d ret, in Vector2d v0, double v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2d_mul(ref Vector2d ret, in Vector2d v0, in Vector2d v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2d_div(ref Vector2d ret, in Vector2d v0, in Vector2d v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2d_add(ref Vector2d ret, in Vector2d v0, in Vector2d v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2d_sub(ref Vector2d ret, in Vector2d v0, in Vector2d v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2d_min(ref Vector2d ret, in Vector2d v0, in Vector2d v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2d_max(ref Vector2d ret, in Vector2d v0, in Vector2d v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2d_clamp(ref Vector2d ret, in Vector2d v, in Vector2d v0, in Vector2d v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2d_saturate(ref Vector2d ret, in Vector2d v);
		[DllImport(Base.Import)] private static extern double tsVector2d_dot(in Vector2d v0, in Vector2d v1);
		[DllImport(Base.Import)] private static extern double tsVector2d_cross(in Vector2d v0, in Vector2d v1);
		[DllImport(Base.Import)] private static extern double tsVector2d_length(in Vector2d v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2d_normalize(ref Vector2d ret, in Vector2d v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector2d_lerp(ref Vector2d ret, in Vector2d v0, in Vector2d v1, double k);
		
		public static readonly Vector2d zero = new Vector2d(0.0);
		public static readonly Vector2d oneX = new Vector2d(1.0, 0.0);
		public static readonly Vector2d oneY = new Vector2d(0.0, 1.0);
		public static readonly Vector2d one = new Vector2d(1.0);
		
		public double x, y;
	}
	
	/*****************************************************************************\
	 *
	 * Vector3
	 *
	\*****************************************************************************/
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct Vector3i {
		
		public Vector3i(int v) { x = v; y = v; z = v; }
		public Vector3i(int x, int y, int z) { this.x = x; this.y = y; this.z = z; }
		public Vector3i(in Vector2i v, int z) { x = v.x; y = v.y; this.z = z; }
		public Vector3i(in Vector3i v) { x = v.x; y = v.y; z = v.z; }
		public Vector3i(in Vector4i v) { x = v.x; y = v.y; z = v.z; }
		public Vector3i(in Vector3u v) { x = (int)v.x; y = (int)v.y; z = (int)v.z; }
		public Vector3i(in Vector3f v) { x = (int)v.x; y = (int)v.y; z = (int)v.z; }
		public Vector3i(in Vector3d v) { x = (int)v.x; y = (int)v.y; z = (int)v.z; }
		public Vector3i(in int[] v) { x = v[0]; y = v[1]; z = v[2]; }
		
		public static Vector3i operator-(in Vector3i v) { Vector3i ret = new Vector3i(); tsVector3i_neg(ref ret, in v); return ret; }
		
		public static Vector3i operator*(in Vector3i v0, int v1) { Vector3i ret = new Vector3i(); tsVector3i_mul1(ref ret, in v0, v1); return ret; }
		public static Vector3i operator/(in Vector3i v0, int v1) { Vector3i ret = new Vector3i(); tsVector3i_div1(ref ret, in v0, v1); return ret; }
		public static Vector3i operator+(in Vector3i v0, int v1) { Vector3i ret = new Vector3i(); tsVector3i_add1(ref ret, in v0, v1); return ret; }
		public static Vector3i operator-(in Vector3i v0, int v1) { Vector3i ret = new Vector3i(); tsVector3i_sub1(ref ret, in v0, v1); return ret; }
		public static Vector3i operator&(in Vector3i v0, int v1) { Vector3i ret = new Vector3i(); tsVector3i_and1(ref ret, in v0, v1); return ret; }
		public static Vector3i operator|(in Vector3i v0, int v1) { Vector3i ret = new Vector3i(); tsVector3i_or1(ref ret, in v0, v1); return ret; }
		public static Vector3i operator^(in Vector3i v0, int v1) { Vector3i ret = new Vector3i(); tsVector3i_xor1(ref ret, in v0, v1); return ret; }
		public static Vector3i operator<<(in Vector3i v0, int v1) { Vector3i ret = new Vector3i(); tsVector3i_shl1(ref ret, in v0, v1); return ret; }
		public static Vector3i operator>>(in Vector3i v0, int v1) { Vector3i ret = new Vector3i(); tsVector3i_shr1(ref ret, in v0, v1); return ret; }
		
		public static Vector3i operator*(in Vector3i v0, in Vector3i v1) { Vector3i ret = new Vector3i(); tsVector3i_mul(ref ret, in v0, in v1); return ret; }
		public static Vector3i operator/(in Vector3i v0, in Vector3i v1) { Vector3i ret = new Vector3i(); tsVector3i_div(ref ret, in v0, in v1); return ret; }
		public static Vector3i operator+(in Vector3i v0, in Vector3i v1) { Vector3i ret = new Vector3i(); tsVector3i_add(ref ret, in v0, in v1); return ret; }
		public static Vector3i operator-(in Vector3i v0, in Vector3i v1) { Vector3i ret = new Vector3i(); tsVector3i_sub(ref ret, in v0, in v1); return ret; }
		public static Vector3i operator&(in Vector3i v0, in Vector3i v1) { Vector3i ret = new Vector3i(); tsVector3i_and(ref ret, in v0, in v1); return ret; }
		public static Vector3i operator|(in Vector3i v0, in Vector3i v1) { Vector3i ret = new Vector3i(); tsVector3i_or(ref ret, in v0, in v1); return ret; }
		public static Vector3i operator^(in Vector3i v0, in Vector3i v1) { Vector3i ret = new Vector3i(); tsVector3i_xor(ref ret, in v0, in v1); return ret; }
		
		public Vector3i abs() { Vector3i ret = new Vector3i(); tsVector3i_abs(ref ret, in this); return ret; }
		
		public static Vector3i min(in Vector3i v0, in Vector3i v1) { Vector3i ret = new Vector3i(); tsVector3i_min(ref ret, in v0, in v1); return ret; }
		public static Vector3i max(in Vector3i v0, in Vector3i v1) { Vector3i ret = new Vector3i(); tsVector3i_max(ref ret, in v0, in v1); return ret; }
		
		public Vector3i clamp(in Vector3i v0, in Vector3i v1) { Vector3i ret = new Vector3i(); tsVector3i_clamp(ref ret, in this, in v0, in v1); return ret; }
		
		public override string ToString() { return System.String.Format("({0} {1} {2})", x, y, z); }
		
		[DllImport(Base.Import)] private static extern IntPtr tsVector3i_abs(ref Vector3i ret, in Vector3i v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3i_neg(ref Vector3i ret, in Vector3i v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3i_mul1(ref Vector3i ret, in Vector3i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3i_div1(ref Vector3i ret, in Vector3i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3i_add1(ref Vector3i ret, in Vector3i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3i_sub1(ref Vector3i ret, in Vector3i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3i_and1(ref Vector3i ret, in Vector3i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3i_or1(ref Vector3i ret, in Vector3i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3i_xor1(ref Vector3i ret, in Vector3i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3i_shl1(ref Vector3i ret, in Vector3i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3i_shr1(ref Vector3i ret, in Vector3i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3i_mul(ref Vector3i ret, in Vector3i v0, in Vector3i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3i_div(ref Vector3i ret, in Vector3i v0, in Vector3i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3i_add(ref Vector3i ret, in Vector3i v0, in Vector3i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3i_sub(ref Vector3i ret, in Vector3i v0, in Vector3i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3i_and(ref Vector3i ret, in Vector3i v0, in Vector3i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3i_or(ref Vector3i ret, in Vector3i v0, in Vector3i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3i_xor(ref Vector3i ret, in Vector3i v0, in Vector3i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3i_min(ref Vector3i ret, in Vector3i v0, in Vector3i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3i_max(ref Vector3i ret, in Vector3i v0, in Vector3i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3i_clamp(ref Vector3i ret, in Vector3i v, in Vector3i v0, in Vector3i v1);
		
		public static readonly Vector3i zero = new Vector3i(0);
		public static readonly Vector3i oneX = new Vector3i(1, 0, 0);
		public static readonly Vector3i oneY = new Vector3i(0, 1, 0);
		public static readonly Vector3i oneZ = new Vector3i(0, 0, 1);
		public static readonly Vector3i one = new Vector3i(1);
		
		public int x, y, z;
	}
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct Vector3u {
		
		public Vector3u(uint v) { x = v; y = v; z = v; }
		public Vector3u(uint x, uint y, uint z) { this.x = x; this.y = y; this.z = z; }
		public Vector3u(in Vector2u v, uint z) { x = v.x; y = v.y; this.z = z; }
		public Vector3u(in Vector3u v) { x = v.x; y = v.y; z = v.z; }
		public Vector3u(in Vector4u v) { x = v.x; y = v.y; z = v.z; }
		public Vector3u(in Vector3i v) { x = (uint)v.x; y = (uint)v.y; z = (uint)v.z; }
		public Vector3u(in Vector3f v) { x = (uint)v.x; y = (uint)v.y; z = (uint)v.z; }
		public Vector3u(in Vector3d v) { x = (uint)v.x; y = (uint)v.y; z = (uint)v.z; }
		public Vector3u(in uint[] v) { x = v[0]; y = v[1]; z = v[2]; }
		
		public static Vector3u operator*(in Vector3u v0, uint v1) { Vector3u ret = new Vector3u(); tsVector3u_mul1(ref ret, in v0, v1); return ret; }
		public static Vector3u operator/(in Vector3u v0, uint v1) { Vector3u ret = new Vector3u(); tsVector3u_div1(ref ret, in v0, v1); return ret; }
		public static Vector3u operator+(in Vector3u v0, uint v1) { Vector3u ret = new Vector3u(); tsVector3u_add1(ref ret, in v0, v1); return ret; }
		public static Vector3u operator-(in Vector3u v0, uint v1) { Vector3u ret = new Vector3u(); tsVector3u_sub1(ref ret, in v0, v1); return ret; }
		public static Vector3u operator&(in Vector3u v0, uint v1) { Vector3u ret = new Vector3u(); tsVector3u_and1(ref ret, in v0, v1); return ret; }
		public static Vector3u operator|(in Vector3u v0, uint v1) { Vector3u ret = new Vector3u(); tsVector3u_or1(ref ret, in v0, v1); return ret; }
		public static Vector3u operator^(in Vector3u v0, uint v1) { Vector3u ret = new Vector3u(); tsVector3u_xor1(ref ret, in v0, v1); return ret; }
		public static Vector3u operator<<(in Vector3u v0, int v1) { Vector3u ret = new Vector3u(); tsVector3u_shl1(ref ret, in v0, (uint)v1); return ret; }
		public static Vector3u operator>>(in Vector3u v0, int v1) { Vector3u ret = new Vector3u(); tsVector3u_shr1(ref ret, in v0, (uint)v1); return ret; }
		
		public static Vector3u operator*(in Vector3u v0, in Vector3u v1) { Vector3u ret = new Vector3u(); tsVector3u_mul(ref ret, in v0, in v1); return ret; }
		public static Vector3u operator/(in Vector3u v0, in Vector3u v1) { Vector3u ret = new Vector3u(); tsVector3u_div(ref ret, in v0, in v1); return ret; }
		public static Vector3u operator+(in Vector3u v0, in Vector3u v1) { Vector3u ret = new Vector3u(); tsVector3u_add(ref ret, in v0, in v1); return ret; }
		public static Vector3u operator-(in Vector3u v0, in Vector3u v1) { Vector3u ret = new Vector3u(); tsVector3u_sub(ref ret, in v0, in v1); return ret; }
		public static Vector3u operator&(in Vector3u v0, in Vector3u v1) { Vector3u ret = new Vector3u(); tsVector3u_and(ref ret, in v0, in v1); return ret; }
		public static Vector3u operator|(in Vector3u v0, in Vector3u v1) { Vector3u ret = new Vector3u(); tsVector3u_or(ref ret, in v0, in v1); return ret; }
		public static Vector3u operator^(in Vector3u v0, in Vector3u v1) { Vector3u ret = new Vector3u(); tsVector3u_xor(ref ret, in v0, in v1); return ret; }
		
		public static Vector3u min(in Vector3u v0, in Vector3u v1) { Vector3u ret = new Vector3u(); tsVector3u_min(ref ret, in v0, in v1); return ret; }
		public static Vector3u max(in Vector3u v0, in Vector3u v1) { Vector3u ret = new Vector3u(); tsVector3u_max(ref ret, in v0, in v1); return ret; }
		
		public Vector3u clamp(in Vector3u v0, in Vector3u v1) { Vector3u ret = new Vector3u(); tsVector3u_clamp(ref ret, in this, in v0, in v1); return ret; }
		
		public override string ToString() { return System.String.Format("({0} {1} {2})", x, y, z); }
		
		[DllImport(Base.Import)] private static extern IntPtr tsVector3u_mul1(ref Vector3u ret, in Vector3u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3u_div1(ref Vector3u ret, in Vector3u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3u_add1(ref Vector3u ret, in Vector3u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3u_sub1(ref Vector3u ret, in Vector3u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3u_and1(ref Vector3u ret, in Vector3u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3u_or1(ref Vector3u ret, in Vector3u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3u_xor1(ref Vector3u ret, in Vector3u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3u_shl1(ref Vector3u ret, in Vector3u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3u_shr1(ref Vector3u ret, in Vector3u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3u_mul(ref Vector3u ret, in Vector3u v0, in Vector3u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3u_div(ref Vector3u ret, in Vector3u v0, in Vector3u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3u_add(ref Vector3u ret, in Vector3u v0, in Vector3u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3u_sub(ref Vector3u ret, in Vector3u v0, in Vector3u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3u_and(ref Vector3u ret, in Vector3u v0, in Vector3u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3u_or(ref Vector3u ret, in Vector3u v0, in Vector3u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3u_xor(ref Vector3u ret, in Vector3u v0, in Vector3u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3u_min(ref Vector3u ret, in Vector3u v0, in Vector3u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3u_max(ref Vector3u ret, in Vector3u v0, in Vector3u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3u_clamp(ref Vector3u ret, in Vector3u v, in Vector3u v0, in Vector3u v1);
		
		public static readonly Vector3u zero = new Vector3u(0);
		public static readonly Vector3u oneX = new Vector3u(1, 0, 0);
		public static readonly Vector3u oneY = new Vector3u(0, 1, 0);
		public static readonly Vector3u oneZ = new Vector3u(0, 0, 1);
		public static readonly Vector3u one = new Vector3u(1);
		
		public uint x, y, z;
	}
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct Vector3f {
		
		public Vector3f(float v) { x = v; y = v; z = v; }
		public Vector3f(float x, float y, float z) { this.x = x; this.y = y; this.z = z; }
		public Vector3f(in Vector2f v, float z) { x = v.x; y = v.y; this.z = z; }
		public Vector3f(in Vector3f v) { x = v.x; y = v.y; z = v.z; }
		public Vector3f(in Vector4f v) { x = v.x; y = v.y; z = v.z; }
		public Vector3f(in Vector3i v) { x = (float)v.x; y = (float)v.y; z = (float)v.z; }
		public Vector3f(in Vector3u v) { x = (float)v.x; y = (float)v.y; z = (float)v.z; }
		public Vector3f(in Vector3d v) { x = (float)v.x; y = (float)v.y; z = (float)v.z; }
		public Vector3f(in float[] v) { x = v[0]; y = v[1]; z = v[2]; }
		
		public static Vector3f operator-(in Vector3f v) { Vector3f ret = new Vector3f(); tsVector3f_neg(ref ret, in v); return ret; }
		
		public static Vector3f operator*(in Vector3f v0, float v1) { Vector3f ret = new Vector3f(); tsVector3f_mul1(ref ret, in v0, v1); return ret; }
		public static Vector3f operator/(in Vector3f v0, float v1) { Vector3f ret = new Vector3f(); tsVector3f_div1(ref ret, in v0, v1); return ret; }
		public static Vector3f operator+(in Vector3f v0, float v1) { Vector3f ret = new Vector3f(); tsVector3f_add1(ref ret, in v0, v1); return ret; }
		public static Vector3f operator-(in Vector3f v0, float v1) { Vector3f ret = new Vector3f(); tsVector3f_sub1(ref ret, in v0, v1); return ret; }
		
		public static Vector3f operator*(in Vector3f v0, in Vector3f v1) { Vector3f ret = new Vector3f(); tsVector3f_mul(ref ret, in v0, in v1); return ret; }
		public static Vector3f operator/(in Vector3f v0, in Vector3f v1) { Vector3f ret = new Vector3f(); tsVector3f_div(ref ret, in v0, in v1); return ret; }
		public static Vector3f operator+(in Vector3f v0, in Vector3f v1) { Vector3f ret = new Vector3f(); tsVector3f_add(ref ret, in v0, in v1); return ret; }
		public static Vector3f operator-(in Vector3f v0, in Vector3f v1) { Vector3f ret = new Vector3f(); tsVector3f_sub(ref ret, in v0, in v1); return ret; }
		
		public Vector3f abs() { Vector3f ret = new Vector3f(); tsVector3f_abs(ref ret, in this); return ret; }
		
		public static Vector3f min(in Vector3f v0, in Vector3f v1) { Vector3f ret = new Vector3f(); tsVector3f_min(ref ret, in v0, in v1); return ret; }
		public static Vector3f max(in Vector3f v0, in Vector3f v1) { Vector3f ret = new Vector3f(); tsVector3f_max(ref ret, in v0, in v1); return ret; }
		
		public Vector3f clamp(in Vector3f v0, in Vector3f v1) { Vector3f ret = new Vector3f(); tsVector3f_clamp(ref ret, in this, in v0, in v1); return ret; }
		public Vector3f saturate() { Vector3f ret = new Vector3f(); tsVector3f_saturate(ref ret, in this); return ret; }
		
		public static float dot(in Vector3f v0, in Vector3f v1) { return tsVector3f_dot(in v0, in v1); }
		public static Vector3f cross(in Vector3f v0, in Vector3f v1) { Vector3f ret = new Vector3f(); tsVector3f_cross(ref ret, in v0, in v1); return ret; }
		
		public float length() { return tsVector3f_length(in this); }
		public Vector3f normalize() { Vector3f ret = new Vector3f(); tsVector3f_normalize(ref ret, in this); return ret; }
		
		public static Vector3f lerp(in Vector3f v0, in Vector3f v1, float k) { Vector3f ret = new Vector3f(); tsVector3f_lerp(ref ret, in v0, in v1, k); return ret; }
		
		public override string ToString() { return System.String.Format("({0} {1} {2})", x, y, z); }
		
		[DllImport(Base.Import)] private static extern IntPtr tsVector3f_abs(ref Vector3f ret, in Vector3f v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3f_neg(ref Vector3f ret, in Vector3f v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3f_mul1(ref Vector3f ret, in Vector3f v0, float v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3f_div1(ref Vector3f ret, in Vector3f v0, float v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3f_add1(ref Vector3f ret, in Vector3f v0, float v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3f_sub1(ref Vector3f ret, in Vector3f v0, float v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3f_mul(ref Vector3f ret, in Vector3f v0, in Vector3f v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3f_div(ref Vector3f ret, in Vector3f v0, in Vector3f v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3f_add(ref Vector3f ret, in Vector3f v0, in Vector3f v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3f_sub(ref Vector3f ret, in Vector3f v0, in Vector3f v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3f_min(ref Vector3f ret, in Vector3f v0, in Vector3f v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3f_max(ref Vector3f ret, in Vector3f v0, in Vector3f v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3f_clamp(ref Vector3f ret, in Vector3f v, in Vector3f v0, in Vector3f v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3f_saturate(ref Vector3f ret, in Vector3f v);
		[DllImport(Base.Import)] private static extern float tsVector3f_dot(in Vector3f v0, in Vector3f v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3f_cross(ref Vector3f ret, in Vector3f v0, in Vector3f v1);
		[DllImport(Base.Import)] private static extern float tsVector3f_length(in Vector3f v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3f_normalize(ref Vector3f ret, in Vector3f v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3f_lerp(ref Vector3f ret, in Vector3f v0, in Vector3f v1, float k);
		
		public static readonly Vector3f zero = new Vector3f(0.0f);
		public static readonly Vector3f oneX = new Vector3f(1.0f, 0.0f, 0.0f);
		public static readonly Vector3f oneY = new Vector3f(0.0f, 1.0f, 0.0f);
		public static readonly Vector3f oneZ = new Vector3f(0.0f, 0.0f, 1.0f);
		public static readonly Vector3f one = new Vector3f(1.0f);
		
		public float x, y, z;
	}
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct Vector3d {
		
		public Vector3d(double v) { x = v; y = v; z = v; }
		public Vector3d(double x, double y, double z) { this.x = x; this.y = y; this.z = z; }
		public Vector3d(in Vector2d v, double z) { x = v.x; y = v.y; this.z = z; }
		public Vector3d(in Vector3d v) { x = v.x; y = v.y; z = v.z; }
		public Vector3d(in Vector4d v) { x = v.x; y = v.y; z = v.z; }
		public Vector3d(in Vector3i v) { x = (double)v.x; y = (double)v.y; z = (double)v.z; }
		public Vector3d(in Vector3u v) { x = (double)v.x; y = (double)v.y; z = (double)v.z; }
		public Vector3d(in Vector3f v) { x = (double)v.x; y = (double)v.y; z = (double)v.z; }
		public Vector3d(in double[] v) { x = v[0]; y = v[1]; z = v[2]; }
		
		public static Vector3d operator-(in Vector3d v) { Vector3d ret = new Vector3d(); tsVector3d_neg(ref ret, in v); return ret; }
		
		public static Vector3d operator*(in Vector3d v0, double v1) { Vector3d ret = new Vector3d(); tsVector3d_mul1(ref ret, in v0, v1); return ret; }
		public static Vector3d operator/(in Vector3d v0, double v1) { Vector3d ret = new Vector3d(); tsVector3d_div1(ref ret, in v0, v1); return ret; }
		public static Vector3d operator+(in Vector3d v0, double v1) { Vector3d ret = new Vector3d(); tsVector3d_add1(ref ret, in v0, v1); return ret; }
		public static Vector3d operator-(in Vector3d v0, double v1) { Vector3d ret = new Vector3d(); tsVector3d_sub1(ref ret, in v0, v1); return ret; }
		
		public static Vector3d operator*(in Vector3d v0, in Vector3d v1) { Vector3d ret = new Vector3d(); tsVector3d_mul(ref ret, in v0, in v1); return ret; }
		public static Vector3d operator/(in Vector3d v0, in Vector3d v1) { Vector3d ret = new Vector3d(); tsVector3d_div(ref ret, in v0, in v1); return ret; }
		public static Vector3d operator+(in Vector3d v0, in Vector3d v1) { Vector3d ret = new Vector3d(); tsVector3d_add(ref ret, in v0, in v1); return ret; }
		public static Vector3d operator-(in Vector3d v0, in Vector3d v1) { Vector3d ret = new Vector3d(); tsVector3d_sub(ref ret, in v0, in v1); return ret; }
		
		public Vector3d abs() { Vector3d ret = new Vector3d(); tsVector3d_abs(ref ret, in this); return ret; }
		
		public static Vector3d min(in Vector3d v0, in Vector3d v1) { Vector3d ret = new Vector3d(); tsVector3d_min(ref ret, in v0, in v1); return ret; }
		public static Vector3d max(in Vector3d v0, in Vector3d v1) { Vector3d ret = new Vector3d(); tsVector3d_max(ref ret, in v0, in v1); return ret; }
		
		public Vector3d clamp(in Vector3d v0, in Vector3d v1) { Vector3d ret = new Vector3d(); tsVector3d_clamp(ref ret, in this, in v0, in v1); return ret; }
		public Vector3d saturate() { Vector3d ret = new Vector3d(); tsVector3d_saturate(ref ret, in this); return ret; }
		
		public static double dot(in Vector3d v0, in Vector3d v1) { return tsVector3d_dot(in v0, in v1); }
		public static Vector3d cross(in Vector3d v0, in Vector3d v1) { Vector3d ret = new Vector3d(); tsVector3d_cross(ref ret, in v0, in v1); return ret; }
		
		public double length() { return tsVector3d_length(in this); }
		public Vector3d normalize(Vector3d v) { Vector3d ret = new Vector3d(); tsVector3d_normalize(ref ret, in this); return ret; }
		
		public static Vector3d lerp(in Vector3d v0, in Vector3d v1, double k) { Vector3d ret = new Vector3d(); tsVector3d_lerp(ref ret, in v0, in v1, k); return ret; }
		
		public override string ToString() { return System.String.Format("({0} {1} {2})", x, y, z); }
		
		[DllImport(Base.Import)] private static extern IntPtr tsVector3d_abs(ref Vector3d ret, in Vector3d v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3d_neg(ref Vector3d ret, in Vector3d v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3d_mul1(ref Vector3d ret, in Vector3d v0, double v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3d_div1(ref Vector3d ret, in Vector3d v0, double v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3d_add1(ref Vector3d ret, in Vector3d v0, double v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3d_sub1(ref Vector3d ret, in Vector3d v0, double v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3d_mul(ref Vector3d ret, in Vector3d v0, in Vector3d v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3d_div(ref Vector3d ret, in Vector3d v0, in Vector3d v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3d_add(ref Vector3d ret, in Vector3d v0, in Vector3d v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3d_sub(ref Vector3d ret, in Vector3d v0, in Vector3d v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3d_min(ref Vector3d ret, in Vector3d v0, in Vector3d v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3d_max(ref Vector3d ret, in Vector3d v0, in Vector3d v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3d_clamp(ref Vector3d ret, in Vector3d v, in Vector3d v0, in Vector3d v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3d_saturate(ref Vector3d ret, in Vector3d v);
		[DllImport(Base.Import)] private static extern double tsVector3d_dot(in Vector3d v0, in Vector3d v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3d_cross(ref Vector3d ret, in Vector3d v0, in Vector3d v1);
		[DllImport(Base.Import)] private static extern double tsVector3d_length(in Vector3d v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3d_normalize(ref Vector3d ret, in Vector3d v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector3d_lerp(ref Vector3d ret, in Vector3d v0, in Vector3d v1, double k);
		
		public static readonly Vector3d zero = new Vector3d(0.0);
		public static readonly Vector3d oneX = new Vector3d(1.0, 0.0, 0.0);
		public static readonly Vector3d oneY = new Vector3d(0.0, 1.0, 0.0);
		public static readonly Vector3d oneZ = new Vector3d(0.0, 0.0, 1.0);
		public static readonly Vector3d one = new Vector3d(1.0);
		
		public double x, y, z;
	}
	
	/*****************************************************************************\
	 *
	 * Vector4
	 *
	\*****************************************************************************/
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential, Pack=16)]
	public struct Vector4i {
		
		public Vector4i(int v) { x = v; y = v; z = v; w = v; }
		public Vector4i(int x, int y, int z, int w) { this.x = x; this.y = y; this.z = z; this.w = w; }
		public Vector4i(in Vector2i v, int z, int w) { x = v.x; y = v.y; this.z = z; this.w = w; }
		public Vector4i(in Vector3i v, int w) { x = v.x; y = v.y; z = v.z; this.w = w; }
		public Vector4i(in Vector4i v) { x = v.x; y = v.y; z = v.z; w = v.w; }
		public Vector4i(in Vector4u v) { x = (int)v.x; y = (int)v.y; z = (int)v.z; w = (int)v.w; }
		public Vector4i(in Vector4f v) { x = (int)v.x; y = (int)v.y; z = (int)v.z; w = (int)v.w; }
		public Vector4i(in Vector4d v) { x = (int)v.x; y = (int)v.y; z = (int)v.z; w = (int)v.w; }
		public Vector4i(in int[] v) { x = v[0]; y = v[1]; z = v[2]; w = v[3]; }
		
		public static Vector4i operator-(in Vector4i v) { Vector4i ret = new Vector4i(); tsVector4i_neg(ref ret, in v); return ret; }
		
		public static Vector4i operator*(in Vector4i v0, int v1) { Vector4i ret = new Vector4i(); tsVector4i_mul1(ref ret, in v0, v1); return ret; }
		public static Vector4i operator/(in Vector4i v0, int v1) { Vector4i ret = new Vector4i(); tsVector4i_div1(ref ret, in v0, v1); return ret; }
		public static Vector4i operator+(in Vector4i v0, int v1) { Vector4i ret = new Vector4i(); tsVector4i_add1(ref ret, in v0, v1); return ret; }
		public static Vector4i operator-(in Vector4i v0, int v1) { Vector4i ret = new Vector4i(); tsVector4i_sub1(ref ret, in v0, v1); return ret; }
		public static Vector4i operator&(in Vector4i v0, int v1) { Vector4i ret = new Vector4i(); tsVector4i_and1(ref ret, in v0, v1); return ret; }
		public static Vector4i operator|(in Vector4i v0, int v1) { Vector4i ret = new Vector4i(); tsVector4i_or1(ref ret, in v0, v1); return ret; }
		public static Vector4i operator^(in Vector4i v0, int v1) { Vector4i ret = new Vector4i(); tsVector4i_xor1(ref ret, in v0, v1); return ret; }
		public static Vector4i operator<<(in Vector4i v0, int v1) { Vector4i ret = new Vector4i(); tsVector4i_shl1(ref ret, in v0, v1); return ret; }
		public static Vector4i operator>>(in Vector4i v0, int v1) { Vector4i ret = new Vector4i(); tsVector4i_shr1(ref ret, in v0, v1); return ret; }
		
		public static Vector4i operator*(in Vector4i v0, in Vector4i v1) { Vector4i ret = new Vector4i(); tsVector4i_mul(ref ret, in v0, in v1); return ret; }
		public static Vector4i operator/(in Vector4i v0, in Vector4i v1) { Vector4i ret = new Vector4i(); tsVector4i_div(ref ret, in v0, in v1); return ret; }
		public static Vector4i operator+(in Vector4i v0, in Vector4i v1) { Vector4i ret = new Vector4i(); tsVector4i_add(ref ret, in v0, in v1); return ret; }
		public static Vector4i operator-(in Vector4i v0, in Vector4i v1) { Vector4i ret = new Vector4i(); tsVector4i_sub(ref ret, in v0, in v1); return ret; }
		public static Vector4i operator&(in Vector4i v0, in Vector4i v1) { Vector4i ret = new Vector4i(); tsVector4i_and(ref ret, in v0, in v1); return ret; }
		public static Vector4i operator|(in Vector4i v0, in Vector4i v1) { Vector4i ret = new Vector4i(); tsVector4i_or(ref ret, in v0, in v1); return ret; }
		public static Vector4i operator^(in Vector4i v0, in Vector4i v1) { Vector4i ret = new Vector4i(); tsVector4i_xor(ref ret, in v0, in v1); return ret; }
		
		public Vector4i abs() { Vector4i ret = new Vector4i(); tsVector4i_abs(ref ret, in this); return ret; }
		
		public static Vector4i min(in Vector4i v0, in Vector4i v1) { Vector4i ret = new Vector4i(); tsVector4i_min(ref ret, in v0, in v1); return ret; }
		public static Vector4i max(in Vector4i v0, in Vector4i v1) { Vector4i ret = new Vector4i(); tsVector4i_max(ref ret, in v0, in v1); return ret; }
		
		public Vector4i clamp(in Vector4i v0, in Vector4i v1) { Vector4i ret = new Vector4i(); tsVector4i_clamp(ref ret, in this, in v0, in v1); return ret; }
		
		public override string ToString() { return System.String.Format("({0} {1} {2} {3})", x, y, z, w); }
		
		[DllImport(Base.Import)] private static extern IntPtr tsVector4i_abs(ref Vector4i ret, in Vector4i v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4i_neg(ref Vector4i ret, in Vector4i v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4i_mul1(ref Vector4i ret, in Vector4i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4i_div1(ref Vector4i ret, in Vector4i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4i_add1(ref Vector4i ret, in Vector4i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4i_sub1(ref Vector4i ret, in Vector4i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4i_and1(ref Vector4i ret, in Vector4i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4i_or1(ref Vector4i ret, in Vector4i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4i_xor1(ref Vector4i ret, in Vector4i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4i_shl1(ref Vector4i ret, in Vector4i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4i_shr1(ref Vector4i ret, in Vector4i v0, int v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4i_mul(ref Vector4i ret, in Vector4i v0, in Vector4i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4i_div(ref Vector4i ret, in Vector4i v0, in Vector4i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4i_add(ref Vector4i ret, in Vector4i v0, in Vector4i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4i_sub(ref Vector4i ret, in Vector4i v0, in Vector4i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4i_and(ref Vector4i ret, in Vector4i v0, in Vector4i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4i_or(ref Vector4i ret, in Vector4i v0, in Vector4i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4i_xor(ref Vector4i ret, in Vector4i v0, in Vector4i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4i_min(ref Vector4i ret, in Vector4i v0, in Vector4i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4i_max(ref Vector4i ret, in Vector4i v0, in Vector4i v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4i_clamp(ref Vector4i ret, in Vector4i v, in Vector4i v0, in Vector4i v1);
		
		public static readonly Vector4i zero = new Vector4i(0);
		public static readonly Vector4i oneX = new Vector4i(1, 0, 0, 0);
		public static readonly Vector4i oneY = new Vector4i(0, 1, 0, 0);
		public static readonly Vector4i oneZ = new Vector4i(0, 0, 1, 0);
		public static readonly Vector4i oneW = new Vector4i(0, 0, 0, 1);
		public static readonly Vector4i one = new Vector4i(1);
		
		public int x, y, z, w;
	}
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential, Pack=16)]
	public struct Vector4u {
		
		public Vector4u(uint v) { x = v; y = v; z = v; w = v; }
		public Vector4u(uint x, uint y, uint z, uint w) { this.x = x; this.y = y; this.z = z; this.w = w; }
		public Vector4u(in Vector2u v, uint z, uint w) { x = v.x; y = v.y; this.z = z; this.w = w; }
		public Vector4u(in Vector3u v, uint w) { x = v.x; y = v.y; z = v.z; this.w = w; }
		public Vector4u(in Vector4u v) { x = v.x; y = v.y; z = v.z; w = v.w; }
		public Vector4u(in Vector4i v) { x = (uint)v.x; y = (uint)v.y; z = (uint)v.z; w = (uint)v.w; }
		public Vector4u(in Vector4f v) { x = (uint)v.x; y = (uint)v.y; z = (uint)v.z; w = (uint)v.w; }
		public Vector4u(in Vector4d v) { x = (uint)v.x; y = (uint)v.y; z = (uint)v.z; w = (uint)v.w; }
		public Vector4u(in uint[] v) { x = v[0]; y = v[1]; z = v[2]; w = v[3]; }
		
		public static Vector4u operator*(in Vector4u v0, uint v1) { Vector4u ret = new Vector4u(); tsVector4u_mul1(ref ret, in v0, v1); return ret; }
		public static Vector4u operator/(in Vector4u v0, uint v1) { Vector4u ret = new Vector4u(); tsVector4u_div1(ref ret, in v0, v1); return ret; }
		public static Vector4u operator+(in Vector4u v0, uint v1) { Vector4u ret = new Vector4u(); tsVector4u_add1(ref ret, in v0, v1); return ret; }
		public static Vector4u operator-(in Vector4u v0, uint v1) { Vector4u ret = new Vector4u(); tsVector4u_sub1(ref ret, in v0, v1); return ret; }
		public static Vector4u operator&(in Vector4u v0, uint v1) { Vector4u ret = new Vector4u(); tsVector4u_and1(ref ret, in v0, v1); return ret; }
		public static Vector4u operator|(in Vector4u v0, uint v1) { Vector4u ret = new Vector4u(); tsVector4u_or1(ref ret, in v0, v1); return ret; }
		public static Vector4u operator^(in Vector4u v0, uint v1) { Vector4u ret = new Vector4u(); tsVector4u_xor1(ref ret, in v0, v1); return ret; }
		public static Vector4u operator<<(in Vector4u v0, int v1) { Vector4u ret = new Vector4u(); tsVector4u_shl1(ref ret, in v0, (uint)v1); return ret; }
		public static Vector4u operator>>(in Vector4u v0, int v1) { Vector4u ret = new Vector4u(); tsVector4u_shr1(ref ret, in v0, (uint)v1); return ret; }
		
		public static Vector4u operator*(in Vector4u v0, in Vector4u v1) { Vector4u ret = new Vector4u(); tsVector4u_mul(ref ret, in v0, in v1); return ret; }
		public static Vector4u operator/(in Vector4u v0, in Vector4u v1) { Vector4u ret = new Vector4u(); tsVector4u_div(ref ret, in v0, in v1); return ret; }
		public static Vector4u operator+(in Vector4u v0, in Vector4u v1) { Vector4u ret = new Vector4u(); tsVector4u_add(ref ret, in v0, in v1); return ret; }
		public static Vector4u operator-(in Vector4u v0, in Vector4u v1) { Vector4u ret = new Vector4u(); tsVector4u_sub(ref ret, in v0, in v1); return ret; }
		public static Vector4u operator&(in Vector4u v0, in Vector4u v1) { Vector4u ret = new Vector4u(); tsVector4u_and(ref ret, in v0, in v1); return ret; }
		public static Vector4u operator|(in Vector4u v0, in Vector4u v1) { Vector4u ret = new Vector4u(); tsVector4u_or(ref ret, in v0, in v1); return ret; }
		public static Vector4u operator^(in Vector4u v0, in Vector4u v1) { Vector4u ret = new Vector4u(); tsVector4u_xor(ref ret, in v0, in v1); return ret; }
		
		public static Vector4u min(in Vector4u v0, in Vector4u v1) { Vector4u ret = new Vector4u(); tsVector4u_min(ref ret, in v0, in v1); return ret; }
		public static Vector4u max(in Vector4u v0, in Vector4u v1) { Vector4u ret = new Vector4u(); tsVector4u_max(ref ret, in v0, in v1); return ret; }
		
		public Vector4u clamp(in Vector4u v0, in Vector4u v1) { Vector4u ret = new Vector4u(); tsVector4u_clamp(ref ret, in this, in v0, in v1); return ret; }
		
		public override string ToString() { return System.String.Format("({0} {1} {2} {3})", x, y, z, w); }
		
		[DllImport(Base.Import)] private static extern IntPtr tsVector4u_mul1(ref Vector4u ret, in Vector4u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4u_div1(ref Vector4u ret, in Vector4u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4u_add1(ref Vector4u ret, in Vector4u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4u_sub1(ref Vector4u ret, in Vector4u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4u_and1(ref Vector4u ret, in Vector4u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4u_or1(ref Vector4u ret, in Vector4u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4u_xor1(ref Vector4u ret, in Vector4u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4u_shl1(ref Vector4u ret, in Vector4u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4u_shr1(ref Vector4u ret, in Vector4u v0, uint v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4u_mul(ref Vector4u ret, in Vector4u v0, in Vector4u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4u_div(ref Vector4u ret, in Vector4u v0, in Vector4u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4u_add(ref Vector4u ret, in Vector4u v0, in Vector4u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4u_sub(ref Vector4u ret, in Vector4u v0, in Vector4u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4u_and(ref Vector4u ret, in Vector4u v0, in Vector4u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4u_or(ref Vector4u ret, in Vector4u v0, in Vector4u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4u_xor(ref Vector4u ret, in Vector4u v0, in Vector4u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4u_min(ref Vector4u ret, in Vector4u v0, in Vector4u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4u_max(ref Vector4u ret, in Vector4u v0, in Vector4u v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4u_clamp(ref Vector4u ret, in Vector4u v, in Vector4u v0, in Vector4u v1);
		
		public static readonly Vector4u zero = new Vector4u(0);
		public static readonly Vector4u oneX = new Vector4u(1, 0, 0, 0);
		public static readonly Vector4u oneY = new Vector4u(0, 1, 0, 0);
		public static readonly Vector4u oneZ = new Vector4u(0, 0, 1, 0);
		public static readonly Vector4u oneW = new Vector4u(0, 0, 0, 1);
		public static readonly Vector4u one = new Vector4u(1);
		
		public uint x, y, z, w;
	}
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential, Pack=16)]
	public struct Vector4f {
		
		public Vector4f(float v) { x = v; y = v; z = v; w = v; }
		public Vector4f(float x, float y, float z, float w) { this.x = x; this.y = y; this.z = z; this.w = w; }
		public Vector4f(in Vector2f v, float z, float w) { x = v.x; y = v.y; this.z = z; this.w = w; }
		public Vector4f(in Vector3f v, float w) { x = v.x; y = v.y; z = v.z; this.w = w; }
		public Vector4f(in Vector4f v) { x = v.x; y = v.y; z = v.z; w = v.w; }
		public Vector4f(in Vector4i v) { x = (float)v.x; y = (float)v.y; z = (float)v.z; w = (float)v.w; }
		public Vector4f(in Vector4u v) { x = (float)v.x; y = (float)v.y; z = (float)v.z; w = (float)v.w; }
		public Vector4f(in Vector4d v) { x = (float)v.x; y = (float)v.y; z = (float)v.z; w = (float)v.w; }
		public Vector4f(in float[] v) { x = v[0]; y = v[1]; z = v[2]; w = v[3]; }
		
		public static Vector4f operator-(in Vector4f v) { Vector4f ret = new Vector4f(); tsVector4f_neg(ref ret, in v); return ret; }
		
		public static Vector4f operator*(in Vector4f v0, float v1) { Vector4f ret = new Vector4f(); tsVector4f_mul1(ref ret, in v0, v1); return ret; }
		public static Vector4f operator/(in Vector4f v0, float v1) { Vector4f ret = new Vector4f(); tsVector4f_div1(ref ret, in v0, v1); return ret; }
		public static Vector4f operator+(in Vector4f v0, float v1) { Vector4f ret = new Vector4f(); tsVector4f_add1(ref ret, in v0, v1); return ret; }
		public static Vector4f operator-(in Vector4f v0, float v1) { Vector4f ret = new Vector4f(); tsVector4f_sub1(ref ret, in v0, v1); return ret; }
		
		public static Vector4f operator*(in Vector4f v0, in Vector4f v1) { Vector4f ret = new Vector4f(); tsVector4f_mul(ref ret, in v0, in v1); return ret; }
		public static Vector4f operator/(in Vector4f v0, in Vector4f v1) { Vector4f ret = new Vector4f(); tsVector4f_div(ref ret, in v0, in v1); return ret; }
		public static Vector4f operator+(in Vector4f v0, in Vector4f v1) { Vector4f ret = new Vector4f(); tsVector4f_add(ref ret, in v0, in v1); return ret; }
		public static Vector4f operator-(in Vector4f v0, in Vector4f v1) { Vector4f ret = new Vector4f(); tsVector4f_sub(ref ret, in v0, in v1); return ret; }
		
		public Vector4f abs() { Vector4f ret = new Vector4f(); tsVector4f_abs(ref ret, in this); return ret; }
		
		public static Vector4f min(in Vector4f v0, in Vector4f v1) { Vector4f ret = new Vector4f(); tsVector4f_min(ref ret, in v0, in v1); return ret; }
		public static Vector4f max(in Vector4f v0, in Vector4f v1) { Vector4f ret = new Vector4f(); tsVector4f_max(ref ret, in v0, in v1); return ret; }
		
		public Vector4f clamp(in Vector4f v0, in Vector4f v1) { Vector4f ret = new Vector4f(); tsVector4f_clamp(ref ret, in this, in v0, in v1); return ret; }
		public Vector4f saturate() { Vector4f ret = new Vector4f(); tsVector4f_saturate(ref ret, in this); return ret; }
		
		public static float dot(in Vector4f v0, in Vector4f v1) { return tsVector4f_dot(in v0, in v1); }
		public static float dot33(in Vector4f v0, in Vector4f v1) { return tsVector4f_dot33(in v0, in v1); }
		public static float dot43(in Vector4f v0, in Vector4f v1) { return tsVector4f_dot43(in v0, in v1); }
		public static float dot34(in Vector4f v0, in Vector4f v1) { return tsVector4f_dot34(in v0, in v1); }
		public static Vector4f cross(in Vector4f v0, in Vector4f v1) { Vector4f ret = new Vector4f(); tsVector4f_cross(ref ret, in v0, in v1); return ret; }
		
		public float length() { return tsVector4f_length(in this); }
		public float length3() { return tsVector4f_length3(in this); }
		public Vector4f normalize() { Vector4f ret = new Vector4f(); tsVector4f_normalize(ref ret, in this); return ret; }
		public Vector4f normalize3() { Vector4f ret = new Vector4f(); tsVector4f_normalize3(ref ret, in this); return ret; }
		
		public static Vector4f lerp(in Vector4f v0, in Vector4f v1, float k) { Vector4f ret = new Vector4f(); tsVector4f_lerp(ref ret, in v0, in v1, k); return ret; }
		
		public override string ToString() { return System.String.Format("({0} {1} {2} {3})", x, y, z, w); }
		
		[DllImport(Base.Import)] private static extern IntPtr tsVector4f_abs(ref Vector4f ret, in Vector4f v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4f_neg(ref Vector4f ret, in Vector4f v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4f_mul1(ref Vector4f ret, in Vector4f v0, float v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4f_div1(ref Vector4f ret, in Vector4f v0, float v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4f_add1(ref Vector4f ret, in Vector4f v0, float v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4f_sub1(ref Vector4f ret, in Vector4f v0, float v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4f_mul(ref Vector4f ret, in Vector4f v0, in Vector4f v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4f_div(ref Vector4f ret, in Vector4f v0, in Vector4f v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4f_add(ref Vector4f ret, in Vector4f v0, in Vector4f v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4f_sub(ref Vector4f ret, in Vector4f v0, in Vector4f v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4f_min(ref Vector4f ret, in Vector4f v0, in Vector4f v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4f_max(ref Vector4f ret, in Vector4f v0, in Vector4f v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4f_clamp(ref Vector4f ret, in Vector4f v, in Vector4f v0, in Vector4f v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4f_saturate(ref Vector4f ret, in Vector4f v);
		[DllImport(Base.Import)] private static extern float tsVector4f_dot(in Vector4f v0, in Vector4f v1);
		[DllImport(Base.Import)] private static extern float tsVector4f_dot33(in Vector4f v0, in Vector4f v1);
		[DllImport(Base.Import)] private static extern float tsVector4f_dot43(in Vector4f v0, in Vector4f v1);
		[DllImport(Base.Import)] private static extern float tsVector4f_dot34(in Vector4f v0, in Vector4f v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4f_cross(ref Vector4f ret, in Vector4f v0, in Vector4f v1);
		[DllImport(Base.Import)] private static extern float tsVector4f_length(in Vector4f v);
		[DllImport(Base.Import)] private static extern float tsVector4f_length3(in Vector4f v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4f_normalize(ref Vector4f ret, in Vector4f v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4f_normalize3(ref Vector4f ret, in Vector4f v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4f_lerp(ref Vector4f ret, in Vector4f v0, in Vector4f v1, float k);
		
		public static readonly Vector4f zero = new Vector4f(0.0f);
		public static readonly Vector4f oneX = new Vector4f(1.0f, 0.0f, 0.0f, 0.0f);
		public static readonly Vector4f oneY = new Vector4f(0.0f, 1.0f, 0.0f, 0.0f);
		public static readonly Vector4f oneZ = new Vector4f(0.0f, 0.0f, 1.0f, 0.0f);
		public static readonly Vector4f oneW = new Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
		public static readonly Vector4f one = new Vector4f(1.0f);
		
		public float x, y, z, w;
	}
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential, Pack=16)]
	public struct Vector4d {
		
		public Vector4d(double v) { x = v; y = v; z = v; w = v; }
		public Vector4d(double x, double y, double z, double w) { this.x = x; this.y = y; this.z = z; this.w = w; }
		public Vector4d(in Vector2d v, double z, double w) { x = v.x; y = v.y; this.z = z; this.w = w; }
		public Vector4d(in Vector3d v, double w) { x = v.x; y = v.y; z = v.z; this.w = w; }
		public Vector4d(in Vector4d v) { x = v.x; y = v.y; z = v.z; w = v.w; }
		public Vector4d(in Vector4i v) { x = (double)v.x; y = (double)v.y; z = (double)v.z; w = (double)v.w; }
		public Vector4d(in Vector4u v) { x = (double)v.x; y = (double)v.y; z = (double)v.z; w = (double)v.w; }
		public Vector4d(in Vector4f v) { x = (double)v.x; y = (double)v.y; z = (double)v.z; w = (double)v.w; }
		public Vector4d(in double[] v) { x = v[0]; y = v[1]; z = v[2]; w = v[3]; }
		
		public static Vector4d operator-(in Vector4d v) { Vector4d ret = new Vector4d(); tsVector4d_neg(ref ret, in v); return ret; }
		
		public static Vector4d operator*(in Vector4d v0, double v1) { Vector4d ret = new Vector4d(); tsVector4d_mul1(ref ret, in v0, v1); return ret; }
		public static Vector4d operator/(in Vector4d v0, double v1) { Vector4d ret = new Vector4d(); tsVector4d_div1(ref ret, in v0, v1); return ret; }
		public static Vector4d operator+(in Vector4d v0, double v1) { Vector4d ret = new Vector4d(); tsVector4d_add1(ref ret, in v0, v1); return ret; }
		public static Vector4d operator-(in Vector4d v0, double v1) { Vector4d ret = new Vector4d(); tsVector4d_sub1(ref ret, in v0, v1); return ret; }
		
		public static Vector4d operator*(in Vector4d v0, in Vector4d v1) { Vector4d ret = new Vector4d(); tsVector4d_mul(ref ret, in v0, in v1); return ret; }
		public static Vector4d operator/(in Vector4d v0, in Vector4d v1) { Vector4d ret = new Vector4d(); tsVector4d_div(ref ret, in v0, in v1); return ret; }
		public static Vector4d operator+(in Vector4d v0, in Vector4d v1) { Vector4d ret = new Vector4d(); tsVector4d_add(ref ret, in v0, in v1); return ret; }
		public static Vector4d operator-(in Vector4d v0, in Vector4d v1) { Vector4d ret = new Vector4d(); tsVector4d_sub(ref ret, in v0, in v1); return ret; }
		
		public Vector4d abs() { Vector4d ret = new Vector4d(); tsVector4d_abs(ref ret, in this); return ret; }
		
		public static Vector4d min(in Vector4d v0, in Vector4d v1) { Vector4d ret = new Vector4d(); tsVector4d_min(ref ret, in v0, in v1); return ret; }
		public static Vector4d max(in Vector4d v0, in Vector4d v1) { Vector4d ret = new Vector4d(); tsVector4d_max(ref ret, in v0, in v1); return ret; }
		
		public Vector4d clamp(in Vector4d v0, in Vector4d v1) { Vector4d ret = new Vector4d(); tsVector4d_clamp(ref ret, in this, in v0, in v1); return ret; }
		public Vector4d saturate() { Vector4d ret = new Vector4d(); tsVector4d_saturate(ref ret, in this); return ret; }
		
		public static double dot(in Vector4d v0, in Vector4d v1) { return tsVector4d_dot(in v0, in v1); }
		public static double dot33(in Vector4d v0, in Vector4d v1) { return tsVector4d_dot33(in v0, in v1); }
		public static double dot43(in Vector4d v0, in Vector4d v1) { return tsVector4d_dot43(in v0, in v1); }
		public static double dot34(in Vector4d v0, in Vector4d v1) { return tsVector4d_dot34(in v0, in v1); }
		public static Vector4d cross(in Vector4d v0, in Vector4d v1) { Vector4d ret = new Vector4d(); tsVector4d_cross(ref ret, in v0, in v1); return ret; }
		
		public double length() { return tsVector4d_length(in this); }
		public double length3() { return tsVector4d_length3(in this); }
		public Vector4d normalize() { Vector4d ret = new Vector4d(); tsVector4d_normalize(ref ret, in this); return ret; }
		public Vector4d normalize3() { Vector4d ret = new Vector4d(); tsVector4d_normalize3(ref ret, in this); return ret; }
		
		public static Vector4d lerp(in Vector4d v0, in Vector4d v1, double k) { Vector4d ret = new Vector4d(); tsVector4d_lerp(ref ret, in v0, in v1, k); return ret; }
		
		public override string ToString() { return System.String.Format("({0} {1} {2} {3})", x, y, z, w); }
		
		[DllImport(Base.Import)] private static extern IntPtr tsVector4d_abs(ref Vector4d ret, in Vector4d v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4d_neg(ref Vector4d ret, in Vector4d v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4d_mul1(ref Vector4d ret, in Vector4d v0, double v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4d_div1(ref Vector4d ret, in Vector4d v0, double v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4d_add1(ref Vector4d ret, in Vector4d v0, double v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4d_sub1(ref Vector4d ret, in Vector4d v0, double v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4d_mul(ref Vector4d ret, in Vector4d v0, in Vector4d v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4d_div(ref Vector4d ret, in Vector4d v0, in Vector4d v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4d_add(ref Vector4d ret, in Vector4d v0, in Vector4d v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4d_sub(ref Vector4d ret, in Vector4d v0, in Vector4d v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4d_min(ref Vector4d ret, in Vector4d v0, in Vector4d v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4d_max(ref Vector4d ret, in Vector4d v0, in Vector4d v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4d_clamp(ref Vector4d ret, in Vector4d v, in Vector4d v0, in Vector4d v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4d_saturate(ref Vector4d ret, in Vector4d v);
		[DllImport(Base.Import)] private static extern double tsVector4d_dot(in Vector4d v0, in Vector4d v1);
		[DllImport(Base.Import)] private static extern double tsVector4d_dot33(in Vector4d v0, in Vector4d v1);
		[DllImport(Base.Import)] private static extern double tsVector4d_dot43(in Vector4d v0, in Vector4d v1);
		[DllImport(Base.Import)] private static extern double tsVector4d_dot34(in Vector4d v0, in Vector4d v1);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4d_cross(ref Vector4d ret, in Vector4d v0, in Vector4d v1);
		[DllImport(Base.Import)] private static extern double tsVector4d_length(in Vector4d v);
		[DllImport(Base.Import)] private static extern double tsVector4d_length3(in Vector4d v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4d_normalize(ref Vector4d ret, in Vector4d v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4d_normalize3(ref Vector4d ret, in Vector4d v);
		[DllImport(Base.Import)] private static extern IntPtr tsVector4d_lerp(ref Vector4d ret, in Vector4d v0, in Vector4d v1, double k);
		
		public static readonly Vector4d zero = new Vector4d(0.0);
		public static readonly Vector4d oneX = new Vector4d(1.0, 0.0, 0.0, 0.0);
		public static readonly Vector4d oneY = new Vector4d(0.0, 1.0, 0.0, 0.0);
		public static readonly Vector4d oneZ = new Vector4d(0.0, 0.0, 1.0, 0.0);
		public static readonly Vector4d oneW = new Vector4d(0.0, 0.0, 0.0, 1.0);
		public static readonly Vector4d one = new Vector4d(1.0);
		
		public double x, y, z, w;
	}
	
	/*****************************************************************************\
	 *
	 * Matrix3x2
	 *
	\*****************************************************************************/
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct Matrix3x2f {
		
		public Matrix3x2f(in Matrix3x2f m) { row_0 = m.row_0; row_1 = m.row_1; }
		public Matrix3x2f(in Matrix3x2d m) { row_0 = new Vector3f(m.row_0); row_1 = new Vector3f(m.row_1); }
		public Matrix3x2f(in Vector3f row_0, in Vector3f row_1) { this.row_0 = row_0; this.row_1 = row_1; }
		public Matrix3x2f(in float[] src, bool row_major = true) { Matrix3x2f ret = new Matrix3x2f(); ret.set(src, row_major); row_0 = ret.row_0; row_1 = ret.row_1; }
		
		public void set(in float[] src, bool row_major = true) { tsMatrix3x2f_set(ref this, in src, (uint)src.Length, row_major); }
		public void get(ref float[] dest, bool row_major = true) { tsMatrix3x2f_get(in this, ref dest, (uint)dest.Length, row_major); }
		
		public static Matrix3x2f scale(float s) { Matrix3x2f ret = new Matrix3x2f(); tsMatrix3x2f_scale(ref ret, s, s); return ret; }
		public static Matrix3x2f scale(float x, float y) { Matrix3x2f ret = new Matrix3x2f(); tsMatrix3x2f_scale(ref ret, x, y); return ret; }
		public static Matrix3x2f scale(in Vector2f s) { Matrix3x2f ret = new Matrix3x2f(); tsMatrix3x2f_scale(ref ret, s.x, s.y); return ret; }
		public static Matrix3x2f translate(float x, float y) { Matrix3x2f ret = new Matrix3x2f(); tsMatrix3x2f_translate(ref ret, x, y); return ret; }
		public static Matrix3x2f translate(in Vector2f t) { Matrix3x2f ret = new Matrix3x2f(); tsMatrix3x2f_translate(ref ret, t.x, t.y); return ret; }
		public static Matrix3x2f rotate(float angle) { Matrix3x2f ret = new Matrix3x2f(); tsMatrix3x2f_rotate(ref ret, angle); return ret; }
		
		public static Vector2f operator*(in Matrix3x2f m, in Vector2f v) { Vector2f ret = new Vector2f(); tsMatrix3x2f_mul2(ref ret, in m, in v); return ret; }
		public static Vector2f operator*(in Vector2f v, in Matrix3x2f m) { Vector2f ret = new Vector2f(); tsMatrix3x2f_mul2t(ref ret, in v, in m); return ret; }
		public static Matrix3x2f operator*(in Matrix3x2f m0, in Matrix3x2f m1) { Matrix3x2f ret = new Matrix3x2f(); tsMatrix3x2f_mul(ref ret, in m0, in m1); return ret; }
		
		public Matrix3x2f transpose() { Matrix3x2f ret = new Matrix3x2f(); tsMatrix3x2f_transpose(ref ret, in this); return ret; }
		public Matrix3x2f inverse() { Matrix3x2f ret = new Matrix3x2f(); tsMatrix3x2f_inverse(ref ret, in this); return ret; }
		
		public override string ToString() { return System.String.Format("{0} : {1}", row_0, row_1); }
		
		[DllImport(Base.Import)] private static extern void tsMatrix3x2f_set(ref Matrix3x2f m, in float[] src, uint size, bool row_major);
		[DllImport(Base.Import)] private static extern void tsMatrix3x2f_get(in Matrix3x2f m, ref float[] dest, uint size, bool row_major);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix3x2f_scale(ref Matrix3x2f ret, float x, float y);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix3x2f_translate(ref Matrix3x2f ret, float x, float y);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix3x2f_rotate(ref Matrix3x2f ret, float angle);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix3x2f_mul2(ref Vector2f ret, in Matrix3x2f m, in Vector2f v);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix3x2f_mul2t(ref Vector2f ret, in Vector2f v, in Matrix3x2f m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix3x2f_mul(ref Matrix3x2f ret, in Matrix3x2f m0, in Matrix3x2f m1);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix3x2f_transpose(ref Matrix3x2f ret, in Matrix3x2f m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix3x2f_inverse(ref Matrix3x2f ret, in Matrix3x2f m);
		
		public static readonly Matrix3x2f zero = new Matrix3x2f(Vector3f.zero, Vector3f.zero);
		public static readonly Matrix3x2f identity = new Matrix3x2f(new Vector3f(1.0f, 0.0f, 0.0f), new Vector3f(0.0f, 1.0f, 0.0f));
		
		public Vector3f row_0;
		public Vector3f row_1;
	}
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct Matrix3x2d {
		
		public Matrix3x2d(in Matrix3x2d m) { row_0 = m.row_0; row_1 = m.row_1; }
		public Matrix3x2d(in Matrix3x2f m) { row_0 = new Vector3d(m.row_0); row_1 = new Vector3d(m.row_1); }
		public Matrix3x2d(in Vector3d row_0, in Vector3d row_1) { this.row_0 = row_0; this.row_1 = row_1; }
		public Matrix3x2d(in double[] src, bool row_major = true) { Matrix3x2d ret = new Matrix3x2d(); ret.set(src, row_major); row_0 = ret.row_0; row_1 = ret.row_1; }
		
		public void set(in double[] src, bool row_major = true) { tsMatrix3x2d_set(ref this, in src, (uint)src.Length, row_major); }
		public void get(ref double[] dest, bool row_major = true) { tsMatrix3x2d_get(in this, ref dest, (uint)dest.Length, row_major); }
		
		public static Matrix3x2d scale(double s) { Matrix3x2d ret = new Matrix3x2d(); tsMatrix3x2d_scale(ref ret, s, s); return ret; }
		public static Matrix3x2d scale(double x, double y) { Matrix3x2d ret = new Matrix3x2d(); tsMatrix3x2d_scale(ref ret, x, y); return ret; }
		public static Matrix3x2d scale(in Vector2d s) { Matrix3x2d ret = new Matrix3x2d(); tsMatrix3x2d_scale(ref ret, s.x, s.y); return ret; }
		public static Matrix3x2d translate(double x, double y) { Matrix3x2d ret = new Matrix3x2d(); tsMatrix3x2d_translate(ref ret, x, y); return ret; }
		public static Matrix3x2d translate(in Vector2d t) { Matrix3x2d ret = new Matrix3x2d(); tsMatrix3x2d_translate(ref ret, t.x, t.y); return ret; }
		public static Matrix3x2d rotate(double angle) { Matrix3x2d ret = new Matrix3x2d(); tsMatrix3x2d_rotate(ref ret, angle); return ret; }
		
		public static Vector2d operator*(in Matrix3x2d m, in Vector2d v) { Vector2d ret = new Vector2d(); tsMatrix3x2d_mul2(ref ret, in m, in v); return ret; }
		public static Vector2d operator*(in Vector2d v, in Matrix3x2d m) { Vector2d ret = new Vector2d(); tsMatrix3x2d_mul2t(ref ret, in v, in m); return ret; }
		public static Matrix3x2d operator*(in Matrix3x2d m0, in Matrix3x2d m1) { Matrix3x2d ret = new Matrix3x2d(); tsMatrix3x2d_mul(ref ret, in m0, in m1); return ret; }
		
		public Matrix3x2d transpose() { Matrix3x2d ret = new Matrix3x2d(); tsMatrix3x2d_transpose(ref ret, in this); return ret; }
		public Matrix3x2d inverse() { Matrix3x2d ret = new Matrix3x2d(); tsMatrix3x2d_inverse(ref ret, in this); return ret; }
		
		public override string ToString() { return System.String.Format("{0} : {1}", row_0, row_1); }
		
		[DllImport(Base.Import)] private static extern void tsMatrix3x2d_set(ref Matrix3x2d m, in double[] src, uint size, bool row_major);
		[DllImport(Base.Import)] private static extern void tsMatrix3x2d_get(in Matrix3x2d m, ref double[] dest, uint size, bool row_major);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix3x2d_scale(ref Matrix3x2d ret, double x, double y);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix3x2d_translate(ref Matrix3x2d ret, double x, double y);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix3x2d_rotate(ref Matrix3x2d ret, double angle);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix3x2d_mul2(ref Vector2d ret, in Matrix3x2d m, in Vector2d v);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix3x2d_mul2t(ref Vector2d ret, in Vector2d v, in Matrix3x2d m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix3x2d_mul(ref Matrix3x2d ret, in Matrix3x2d m0, in Matrix3x2d m1);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix3x2d_transpose(ref Matrix3x2d ret, in Matrix3x2d m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix3x2d_inverse(ref Matrix3x2d ret, in Matrix3x2d m);
		
		public static readonly Matrix3x2d zero = new Matrix3x2d(Vector3d.zero, Vector3d.zero);
		public static readonly Matrix3x2d identity = new Matrix3x2d(new Vector3d(1.0, 0.0, 0.0), new Vector3d(0.0, 1.0, 0.0));
		
		public Vector3d row_0;
		public Vector3d row_1;
	}
	
	/*****************************************************************************\
	 *
	 * Matrix4x3
	 *
	\*****************************************************************************/
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential, Pack=16)]
	public struct Matrix4x3f {
		
		public Matrix4x3f(in Matrix4x3f m) { row_0 = m.row_0; row_1 = m.row_1; row_2 = m.row_2; }
		public Matrix4x3f(in Matrix4x4f m) { row_0 = m.row_0; row_1 = m.row_1; row_2 = m.row_2; }
		public Matrix4x3f(in Matrix4x3d m) { row_0 = new Vector4f(m.row_0); row_1 = new Vector4f(m.row_1); row_2 = new Vector4f(m.row_2); }
		public Matrix4x3f(in Vector4f row_0, in Vector4f row_1, in Vector4f row_2) { this.row_0 = row_0; this.row_1 = row_1; this.row_2 = row_2; }
		public Matrix4x3f(in Quaternionf q) { Matrix4x3f ret = new Matrix4x3f(); ret.set(q); row_0 = ret.row_0; row_1 = ret.row_1; row_2 = ret.row_2; }
		public Matrix4x3f(in float[] src, bool row_major = true) { Matrix4x3f ret = new Matrix4x3f(); ret.set(src, row_major); row_0 = ret.row_0; row_1 = ret.row_1; row_2 = ret.row_2; }
		
		public void set(in float[] src, bool row_major = true) { tsMatrix4x3f_set(ref this, in src, (uint)src.Length, row_major); }
		public void get(ref float[] dest, bool row_major = true) { tsMatrix4x3f_get(in this, ref dest, (uint)dest.Length, row_major); }
		public void set(in Quaternionf q) { tsQuaternionf_get(in q, ref row_0, ref row_1, ref row_2); }
		public void get(ref Quaternionf q) { tsQuaternionf_set(ref q, in row_0, in row_1, in row_2); }
		
		public static Matrix4x3f scale(float s) { Matrix4x3f ret = new Matrix4x3f(); tsMatrix4x3f_scale(ref ret, s, s, s); return ret; }
		public static Matrix4x3f scale(float x, float y, float z) { Matrix4x3f ret = new Matrix4x3f(); tsMatrix4x3f_scale(ref ret, x, y, z); return ret; }
		public static Matrix4x3f scale(in Vector3f s) { Matrix4x3f ret = new Matrix4x3f(); tsMatrix4x3f_scale(ref ret, s.x, s.y, s.z); return ret; }
		public static Matrix4x3f translate(float x, float y, float z) { Matrix4x3f ret = new Matrix4x3f(); tsMatrix4x3f_translate(ref ret, x, y, z); return ret; }
		public static Matrix4x3f translate(in Vector3f t) { Matrix4x3f ret = new Matrix4x3f(); tsMatrix4x3f_translate(ref ret, t.x, t.y, t.z); return ret; }
		public static Matrix4x3f rotateX(float angle) { Matrix4x3f ret = new Matrix4x3f(); tsMatrix4x3f_rotateX(ref ret, angle); return ret; }
		public static Matrix4x3f rotateY(float angle) { Matrix4x3f ret = new Matrix4x3f(); tsMatrix4x3f_rotateY(ref ret, angle); return ret; }
		public static Matrix4x3f rotateZ(float angle) { Matrix4x3f ret = new Matrix4x3f(); tsMatrix4x3f_rotateZ(ref ret, angle); return ret; }
		public static Matrix4x3f rotate(in Vector3f axis, float angle) { Matrix4x3f ret = new Matrix4x3f(); tsMatrix4x3f_rotate(ref ret, in axis, angle); return ret; }
		
		public static Matrix4x3f lookAt(in Vector3f from, in Vector3f to, in Vector3f up) { Matrix4x3f ret = new Matrix4x3f(); tsMatrix4x3f_lookAt(ref ret, in from, in to, in up); return ret; }
		public static Matrix4x3f placeTo(in Vector3f to, in Vector3f from, in Vector3f up) { Matrix4x3f ret = new Matrix4x3f(); tsMatrix4x3f_placeTo(ref ret, in to, in from, in up); return ret; }
		public static Matrix4x3f compose(in Vector3f t, in Quaternionf r, in Vector3f s) { Matrix4x3f ret = new Matrix4x3f(); tsMatrix4x3f_compose(ref ret, in t, in r, in s); return ret; }
		public static Matrix4x3f basis(in Vector3f normal, in Vector3f t) { Matrix4x3f ret = new Matrix4x3f(); tsMatrix4x3f_basis(ref ret, in normal, in t); return ret; }
		
		public static Vector2f operator*(in Matrix4x3f m, in Vector2f v) { Vector2f ret = new Vector2f(); tsMatrix4x3f_mul2(ref ret, in m, in v); return ret; }
		public static Vector3f operator*(in Matrix4x3f m, in Vector3f v) { Vector3f ret = new Vector3f(); tsMatrix4x3f_mul3(ref ret, in m, in v); return ret; }
		public static Vector4f operator*(in Matrix4x3f m, in Vector4f v) { Vector4f ret = new Vector4f(); tsMatrix4x3f_mul4(ref ret, in m, in v); return ret; }
		public static Vector2f operator*(in Vector2f v, in Matrix4x3f m) { Vector2f ret = new Vector2f(); tsMatrix4x3f_mul2t(ref ret, in v, in m); return ret; }
		public static Vector3f operator*(in Vector3f v, in Matrix4x3f m) { Vector3f ret = new Vector3f(); tsMatrix4x3f_mul3t(ref ret, in v, in m); return ret; }
		public static Vector4f operator*(in Vector4f v, in Matrix4x3f m) { Vector4f ret = new Vector4f(); tsMatrix4x3f_mul4t(ref ret, in v, in m); return ret; }
		public static Matrix4x3f operator*(in Matrix4x3f m0, in Matrix4x3f m1) { Matrix4x3f ret = new Matrix4x3f(); tsMatrix4x3f_mul(ref ret, in m0, in m1); return ret; }
		
		public Matrix4x3f normalize() { Matrix4x3f ret = new Matrix4x3f(); tsMatrix4x3f_normalize(ref ret, in this); return ret; }
		public Matrix4x3f transpose() { Matrix4x3f ret = new Matrix4x3f(); tsMatrix4x3f_transpose(ref ret, in this); return ret; }
		public Matrix4x3f inverse() { Matrix4x3f ret = new Matrix4x3f(); tsMatrix4x3f_inverse(ref ret, in this); return ret; }
		public Matrix4x3f inverse33() { Matrix4x3f ret = new Matrix4x3f(); tsMatrix4x3f_inverse33(ref ret, in this); return ret; }
		
		public static Matrix4x3f lerp(in Matrix4x3f m0, in Matrix4x3f m1, float k) { Matrix4x3f ret = new Matrix4x3f(); tsMatrix4x3f_lerp(ref ret, in m0, in m1, k); return ret; }
		
		public override string ToString() { return System.String.Format("{0} : {1} : {2}", row_0, row_1, row_2); }
		
		[DllImport(Base.Import)] private static extern void tsMatrix4x3f_set(ref Matrix4x3f m, in float[] src, uint size, bool row_major);
		[DllImport(Base.Import)] private static extern void tsMatrix4x3f_get(in Matrix4x3f m, ref float[] dest, uint size, bool row_major);
		[DllImport(Base.Import)] private static extern void tsQuaternionf_set(ref Quaternionf q, in Vector4f row_0, in Vector4f row_1, in Vector4f row_2);
		[DllImport(Base.Import)] private static extern void tsQuaternionf_get(in Quaternionf q, ref Vector4f row_0, ref Vector4f row_1, ref Vector4f row_2);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_scale(ref Matrix4x3f ret, float x, float y, float z);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_translate(ref Matrix4x3f ret, float x, float y, float z);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_rotateX(ref Matrix4x3f ret, float angle);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_rotateY(ref Matrix4x3f ret, float angle);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_rotateZ(ref Matrix4x3f ret, float angle);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_rotate(ref Matrix4x3f ret, in Vector3f axis, float angle);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_lookAt(ref Matrix4x3f ret, in Vector3f from, in Vector3f to, in Vector3f up);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_placeTo(ref Matrix4x3f ret, in Vector3f to, in Vector3f from, in Vector3f up);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_compose(ref Matrix4x3f ret, in Vector3f t, in Quaternionf r, in Vector3f s);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_basis(ref Matrix4x3f ret, in Vector3f normal, in Vector3f t);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_mul2(ref Vector2f ret, in Matrix4x3f m, in Vector2f v);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_mul3(ref Vector3f ret, in Matrix4x3f m, in Vector3f v);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_mul4(ref Vector4f ret, in Matrix4x3f m, in Vector4f v);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_mul2t(ref Vector2f ret, in Vector2f v, in Matrix4x3f m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_mul3t(ref Vector3f ret, in Vector3f v, in Matrix4x3f m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_mul4t(ref Vector4f ret, in Vector4f v, in Matrix4x3f m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_mul(ref Matrix4x3f ret, in Matrix4x3f m0, in Matrix4x3f m1);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_normalize(ref Matrix4x3f ret, in Matrix4x3f m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_transpose(ref Matrix4x3f ret, in Matrix4x3f m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_inverse(ref Matrix4x3f ret, in Matrix4x3f m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_inverse33(ref Matrix4x3f ret, in Matrix4x3f m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_lerp(ref Matrix4x3f ret, in Matrix4x3f m0, in Matrix4x3f m1, float k);
		
		public static readonly Matrix4x3f zero = new Matrix4x3f(Vector4f.zero, Vector4f.zero, Vector4f.zero);
		public static readonly Matrix4x3f identity = new Matrix4x3f(new Vector4f(1.0f, 0.0f, 0.0f, 0.0f), new Vector4f(0.0f, 1.0f, 0.0f, 0.0f), new Vector4f(0.0f, 0.0f, 1.0f, 0.0f));
		
		public Vector4f row_0;
		public Vector4f row_1;
		public Vector4f row_2;
	}
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential, Pack=16)]
	public struct Matrix4x3d {
		
		public Matrix4x3d(in Matrix4x3d m) { row_0 = m.row_0; row_1 = m.row_1; row_2 = m.row_2; }
		public Matrix4x3d(in Matrix4x4d m) { row_0 = m.row_0; row_1 = m.row_1; row_2 = m.row_2; }
		public Matrix4x3d(in Matrix4x3f m) { row_0 = new Vector4d(m.row_0); row_1 = new Vector4d(m.row_1); row_2 = new Vector4d(m.row_2); }
		public Matrix4x3d(in Vector4d row_0, in Vector4d row_1, in Vector4d row_2) { this.row_0 = row_0; this.row_1 = row_1; this.row_2 = row_2; }
		public Matrix4x3d(in Quaterniond q) { Matrix4x3d ret = new Matrix4x3d(); ret.set(q); row_0 = ret.row_0; row_1 = ret.row_1; row_2 = ret.row_2; }
		public Matrix4x3d(in double[] src, bool row_major = true) { Matrix4x3d ret = new Matrix4x3d(); ret.set(src, row_major); row_0 = ret.row_0; row_1 = ret.row_1; row_2 = ret.row_2; }
		
		public void set(in double[] src, bool row_major = true) { tsMatrix4x3d_set(ref this, in src, (uint)src.Length, row_major); }
		public void get(ref double[] dest, bool row_major = true) { tsMatrix4x3d_get(in this, ref dest, (uint)dest.Length, row_major); }
		public void set(in Quaterniond q) { tsQuaterniond_get(in q, ref row_0, ref row_1, ref row_2); }
		public void get(ref Quaterniond q) { tsQuaterniond_set(ref q, in row_0, in row_1, in row_2); }
		
		public static Matrix4x3d scale(double s) { Matrix4x3d ret = new Matrix4x3d(); tsMatrix4x3d_scale(ref ret, s, s, s); return ret; }
		public static Matrix4x3d scale(double x, double y, double z) { Matrix4x3d ret = new Matrix4x3d(); tsMatrix4x3d_scale(ref ret, x, y, z); return ret; }
		public static Matrix4x3d scale(in Vector3d s) { Matrix4x3d ret = new Matrix4x3d(); tsMatrix4x3d_scale(ref ret, s.x, s.y, s.z); return ret; }
		public static Matrix4x3d translate(double x, double y, double z) { Matrix4x3d ret = new Matrix4x3d(); tsMatrix4x3d_translate(ref ret, x, y, z); return ret; }
		public static Matrix4x3d translate(in Vector3d t) { Matrix4x3d ret = new Matrix4x3d(); tsMatrix4x3d_translate(ref ret, t.x, t.y, t.z); return ret; }
		public static Matrix4x3d rotateX(double angle) { Matrix4x3d ret = new Matrix4x3d(); tsMatrix4x3d_rotateX(ref ret, angle); return ret; }
		public static Matrix4x3d rotateY(double angle) { Matrix4x3d ret = new Matrix4x3d(); tsMatrix4x3d_rotateY(ref ret, angle); return ret; }
		public static Matrix4x3d rotateZ(double angle) { Matrix4x3d ret = new Matrix4x3d(); tsMatrix4x3d_rotateZ(ref ret, angle); return ret; }
		public static Matrix4x3d rotate(in Vector3d axis, double angle) { Matrix4x3d ret = new Matrix4x3d(); tsMatrix4x3d_rotate(ref ret, in axis, angle); return ret; }
		
		public static Matrix4x3d lookAt(in Vector3d from, in Vector3d to, in Vector3d up) { Matrix4x3d ret = new Matrix4x3d(); tsMatrix4x3d_lookAt(ref ret, in from, in to, in up); return ret; }
		public static Matrix4x3d placeTo(in Vector3d to, in Vector3d from, in Vector3d up) { Matrix4x3d ret = new Matrix4x3d(); tsMatrix4x3d_placeTo(ref ret, in to, in from, in up); return ret; }
		public static Matrix4x3d compose(in Vector3d t, in Quaterniond r, in Vector3d s) { Matrix4x3d ret = new Matrix4x3d(); tsMatrix4x3d_compose(ref ret, in t, in r, in s); return ret; }
		public static Matrix4x3d basis(in Vector3d normal, in Vector3d t) { Matrix4x3d ret = new Matrix4x3d(); tsMatrix4x3d_basis(ref ret, in normal, in t); return ret; }
		
		public static Vector2d operator*(in Matrix4x3d m, in Vector2d v) { Vector2d ret = new Vector2d(); tsMatrix4x3d_mul2(ref ret, in m, in v); return ret; }
		public static Vector3d operator*(in Matrix4x3d m, in Vector3d v) { Vector3d ret = new Vector3d(); tsMatrix4x3d_mul3(ref ret, in m, in v); return ret; }
		public static Vector4d operator*(in Matrix4x3d m, in Vector4d v) { Vector4d ret = new Vector4d(); tsMatrix4x3d_mul4(ref ret, in m, in v); return ret; }
		public static Vector2d operator*(in Vector2d v, in Matrix4x3d m) { Vector2d ret = new Vector2d(); tsMatrix4x3d_mul2t(ref ret, in v, in m); return ret; }
		public static Vector3d operator*(in Vector3d v, in Matrix4x3d m) { Vector3d ret = new Vector3d(); tsMatrix4x3d_mul3t(ref ret, in v, in m); return ret; }
		public static Vector4d operator*(in Vector4d v, in Matrix4x3d m) { Vector4d ret = new Vector4d(); tsMatrix4x3d_mul4t(ref ret, in v, in m); return ret; }
		public static Matrix4x3d operator*(in Matrix4x3d m0, in Matrix4x3d m1) { Matrix4x3d ret = new Matrix4x3d(); tsMatrix4x3d_mul(ref ret, in m0, in m1); return ret; }
		
		public Matrix4x3d normalize() { Matrix4x3d ret = new Matrix4x3d(); tsMatrix4x3d_normalize(ref ret, in this); return ret; }
		public Matrix4x3d transpose() { Matrix4x3d ret = new Matrix4x3d(); tsMatrix4x3d_transpose(ref ret, in this); return ret; }
		public Matrix4x3d inverse() { Matrix4x3d ret = new Matrix4x3d(); tsMatrix4x3d_inverse(ref ret, in this); return ret; }
		public Matrix4x3d inverse33() { Matrix4x3d ret = new Matrix4x3d(); tsMatrix4x3d_inverse33(ref ret, in this); return ret; }
		
		public static Matrix4x3d lerp(in Matrix4x3d m0, in Matrix4x3d m1, double k) { Matrix4x3d ret = new Matrix4x3d(); tsMatrix4x3d_lerp(ref ret, in m0, in m1, k); return ret; }
		
		public override string ToString() { return System.String.Format("{0} : {1} : {2}", row_0, row_1, row_2); }
		
		[DllImport(Base.Import)] private static extern void tsMatrix4x3d_set(ref Matrix4x3d m, in double[] src, uint size, bool row_major);
		[DllImport(Base.Import)] private static extern void tsMatrix4x3d_get(in Matrix4x3d m, ref double[] dest, uint size, bool row_major);
		[DllImport(Base.Import)] private static extern void tsQuaterniond_set(ref Quaterniond q, in Vector4d row_0, in Vector4d row_1, in Vector4d row_2);
		[DllImport(Base.Import)] private static extern void tsQuaterniond_get(in Quaterniond q, ref Vector4d row_0, ref Vector4d row_1, ref Vector4d row_2);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_scale(ref Matrix4x3d ret, double x, double y, double z);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_translate(ref Matrix4x3d ret, double x, double y, double z);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_rotateX(ref Matrix4x3d ret, double angle);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_rotateY(ref Matrix4x3d ret, double angle);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_rotateZ(ref Matrix4x3d ret, double angle);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_rotate(ref Matrix4x3d ret, in Vector3d axis, double angle);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_lookAt(ref Matrix4x3d ret, in Vector3d from, in Vector3d to, in Vector3d up);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_placeTo(ref Matrix4x3d ret, in Vector3d to, in Vector3d from, in Vector3d up);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_compose(ref Matrix4x3d ret, in Vector3d t, in Quaterniond r, in Vector3d s);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_basis(ref Matrix4x3d ret, in Vector3d normal, in Vector3d t);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_mul2(ref Vector2d ret, in Matrix4x3d m, in Vector2d v);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_mul3(ref Vector3d ret, in Matrix4x3d m, in Vector3d v);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_mul4(ref Vector4d ret, in Matrix4x3d m, in Vector4d v);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_mul2t(ref Vector2d ret, in Vector2d v, in Matrix4x3d m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_mul3t(ref Vector3d ret, in Vector3d v, in Matrix4x3d m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_mul4t(ref Vector4d ret, in Vector4d v, in Matrix4x3d m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_mul(ref Matrix4x3d ret, in Matrix4x3d m0, in Matrix4x3d m1);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_normalize(ref Matrix4x3d ret, in Matrix4x3d m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_transpose(ref Matrix4x3d ret, in Matrix4x3d m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_inverse(ref Matrix4x3d ret, in Matrix4x3d m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_inverse33(ref Matrix4x3d ret, in Matrix4x3d m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_lerp(ref Matrix4x3d ret, in Matrix4x3d m0, in Matrix4x3d m1, double k);
		
		public static readonly Matrix4x3d zero = new Matrix4x3d(Vector4d.zero, Vector4d.zero, Vector4d.zero);
		public static readonly Matrix4x3d identity = new Matrix4x3d(new Vector4d(1.0, 0.0, 0.0, 0.0), new Vector4d(0.0, 1.0, 0.0, 0.0), new Vector4d(0.0, 0.0, 1.0, 0.0));
		
		public Vector4d row_0;
		public Vector4d row_1;
		public Vector4d row_2;
	}
	
	/*****************************************************************************\
	 *
	 * Matrix4x4
	 *
	\*****************************************************************************/
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential, Pack=16)]
	public struct Matrix4x4f {
		
		public Matrix4x4f(in Matrix4x3f m) { row_0 = m.row_0; row_1 = m.row_1; row_2 = m.row_2; row_3 = new Vector4f(0.0f, 0.0f, 0.0f, 1.0f); }
		public Matrix4x4f(in Matrix4x4f m) { row_0 = m.row_0; row_1 = m.row_1; row_2 = m.row_2; row_3 = m.row_3; }
		public Matrix4x4f(in Matrix4x4d m) { row_0 = new Vector4f(m.row_0); row_1 = new Vector4f(m.row_1); row_2 = new Vector4f(m.row_2); row_3 = new Vector4f(m.row_3); }
		public Matrix4x4f(in Vector4f row_0, in Vector4f row_1, in Vector4f row_2, in Vector4f row_3) { this.row_0 = row_0; this.row_1 = row_1; this.row_2 = row_2; this.row_3 = row_3; }
		public Matrix4x4f(in Quaternionf q) { Matrix4x3f ret = new Matrix4x3f(); ret.set(q); row_0 = ret.row_0; row_1 = ret.row_1; row_2 = ret.row_2; row_3 = new Vector4f(0.0f, 0.0f, 0.0f, 1.0f); }
		public Matrix4x4f(in float[] src, bool row_major = true) { Matrix4x4f ret = new Matrix4x4f(); ret.set(src, row_major); row_0 = ret.row_0; row_1 = ret.row_1; row_2 = ret.row_2; row_3 = ret.row_3; }
		
		public void set(in float[] src, bool row_major = true) { tsMatrix4x4f_set(ref this, in src, (uint)src.Length, row_major); }
		public void get(ref float[] dest, bool row_major = true) { tsMatrix4x4f_get(in this, ref dest, (uint)dest.Length, row_major); }
		public void set(in Quaternionf q) { tsQuaternionf_get(in q, ref row_0, ref row_1, ref row_2); row_3 = new Vector4f(0.0f, 0.0f, 0.0f, 1.0f); }
		public void get(ref Quaternionf q) { tsQuaternionf_set(ref q, in row_0, in row_1, in row_2); }
		
		public static Matrix4x4f scale(float s) { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_scale(ref ret, s, s, s); return ret; }
		public static Matrix4x4f scale(float x, float y, float z) { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_scale(ref ret, x, y, z); return ret; }
		public static Matrix4x4f scale(in Vector3f s) { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_scale(ref ret, s.x, s.y, s.z); return ret; }
		public static Matrix4x4f translate(float x, float y, float z) { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_translate(ref ret, x, y, z); return ret; }
		public static Matrix4x4f translate(in Vector3f t) { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_translate(ref ret, t.x, t.y, t.z); return ret; }
		public static Matrix4x4f rotateX(float angle) { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_rotateX(ref ret, angle); return ret; }
		public static Matrix4x4f rotateY(float angle) { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_rotateY(ref ret, angle); return ret; }
		public static Matrix4x4f rotateZ(float angle) { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_rotateZ(ref ret, angle); return ret; }
		public static Matrix4x4f rotate(in Vector3f axis, float angle) { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_rotate(ref ret, in axis, angle); return ret; }
		
		public static Matrix4x4f lookAt(in Vector3f from, in Vector3f to, in Vector3f up) { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_lookAt(ref ret, in from, in to, in up); return ret; }
		public static Matrix4x4f placeTo(in Vector3f to, in Vector3f from, in Vector3f up) { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_placeTo(ref ret, in to, in from, in up); return ret; }
		public static Matrix4x4f compose(in Vector3f t, in Quaternionf r, in Vector3f s) { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_compose(ref ret, in t, in r, in s); return ret; }
		public static Matrix4x4f basis(in Vector3f normal, in Vector3f t) { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_basis(ref ret, in normal, in t); return ret; }
		
		public static Matrix4x4f ortho(float left, float right, float bottom, float top, float znear, float zfar) { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_ortho(ref ret, left, right, bottom, top, znear, zfar); return ret; }
		public static Matrix4x4f frustum(float left, float right, float bottom, float top, float znear, float zfar, bool reverse = false) { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_frustum(ref ret, left, right, bottom, top, znear, zfar, reverse); return ret; }
		public static Matrix4x4f frustum(float left, float right, float bottom, float top, float znear, bool reverse = false) { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_frustumi(ref ret, left, right, bottom, top, znear, reverse); return ret; }
		public static Matrix4x4f perspective(float fov, float aspect, float znear, float zfar, bool reverse = false) { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_perspective(ref ret, fov, aspect, znear, zfar, reverse); return ret; }
		public static Matrix4x4f perspective(float fov, float aspect, float znear, bool reverse = false) { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_perspectivei(ref ret, fov, aspect, znear, reverse); return ret; }
		
		public static Vector2f operator*(in Matrix4x4f m, in Vector2f v) { Vector2f ret = new Vector2f(); tsMatrix4x4f_mul2(ref ret, in m, in v); return ret; }
		public static Vector3f operator*(in Matrix4x4f m, in Vector3f v) { Vector3f ret = new Vector3f(); tsMatrix4x4f_mul3(ref ret, in m, in v); return ret; }
		public static Vector4f operator*(in Matrix4x4f m, in Vector4f v) { Vector4f ret = new Vector4f(); tsMatrix4x4f_mul4(ref ret, in m, in v); return ret; }
		public static Vector2f operator*(in Vector2f v, in Matrix4x4f m) { Vector2f ret = new Vector2f(); tsMatrix4x4f_mul2t(ref ret, in v, in m); return ret; }
		public static Vector3f operator*(in Vector3f v, in Matrix4x4f m) { Vector3f ret = new Vector3f(); tsMatrix4x4f_mul3t(ref ret, in v, in m); return ret; }
		public static Vector4f operator*(in Vector4f v, in Matrix4x4f m) { Vector4f ret = new Vector4f(); tsMatrix4x4f_mul4t(ref ret, in v, in m); return ret; }
		public static Matrix4x4f operator*(in Matrix4x4f m0, in Matrix4x4f m1) { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_mul(ref ret, in m0, in m1); return ret; }
		
		public Matrix4x4f normalize() { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_normalize(ref ret, in this); return ret; }
		public Matrix4x4f transpose() { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_transpose(ref ret, in this); return ret; }
		public Matrix4x4f inverse() { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_inverse(ref ret, in this); return ret; }
		public Matrix4x4f inverse43() { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_inverse43(ref ret, in this); return ret; }
		
		public static Matrix4x4f lerp(in Matrix4x4f m0, in Matrix4x4f m1, float k) { Matrix4x4f ret = new Matrix4x4f(); tsMatrix4x4f_lerp(ref ret, in m0, in m1, k); return ret; }
		
		public override string ToString() { return System.String.Format("{0} : {1} : {2} : {3}", row_0, row_1, row_2, row_3); }
		
		[DllImport(Base.Import)] private static extern void tsMatrix4x4f_set(ref Matrix4x4f m, in float[] src, uint size, bool row_major);
		[DllImport(Base.Import)] private static extern void tsMatrix4x4f_get(in Matrix4x4f m, ref float[] dest, uint size, bool row_major);
		[DllImport(Base.Import)] private static extern void tsQuaternionf_set(ref Quaternionf q, in Vector4f row_0, in Vector4f row_1, in Vector4f row_2);
		[DllImport(Base.Import)] private static extern void tsQuaternionf_get(in Quaternionf q, ref Vector4f row_0, ref Vector4f row_1, ref Vector4f row_2);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_scale(ref Matrix4x4f ret, float x, float y, float z);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_translate(ref Matrix4x4f ret, float x, float y, float z);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_rotateX(ref Matrix4x4f ret, float angle);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_rotateY(ref Matrix4x4f ret, float angle);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_rotateZ(ref Matrix4x4f ret, float angle);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_rotate(ref Matrix4x4f ret, in Vector3f axis, float angle);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_lookAt(ref Matrix4x4f ret, in Vector3f from, in Vector3f to, in Vector3f up);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_placeTo(ref Matrix4x4f ret, in Vector3f to, in Vector3f from, in Vector3f up);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_compose(ref Matrix4x4f ret, in Vector3f t, in Quaternionf r, in Vector3f s);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_basis(ref Matrix4x4f ret, in Vector3f normal, in Vector3f t);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_ortho(ref Matrix4x4f ret, float left, float right, float bottom, float top, float znear, float zfar);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_frustum(ref Matrix4x4f ret, float left, float right, float bottom, float top, float znear, float zfar, bool reverse);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_frustumi(ref Matrix4x4f ret, float left, float right, float bottom, float top, float znear, bool reverse);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_perspective(ref Matrix4x4f ret, float fov, float aspect, float znear, float zfar, bool reverse);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_perspectivei(ref Matrix4x4f ret, float fov, float aspect, float znear, bool reverse);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_mul2(ref Vector2f ret, in Matrix4x4f m, in Vector2f v);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_mul3(ref Vector3f ret, in Matrix4x4f m, in Vector3f v);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_mul4(ref Vector4f ret, in Matrix4x4f m, in Vector4f v);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_mul2t(ref Vector2f ret, in Vector2f v, in Matrix4x4f m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_mul3t(ref Vector3f ret, in Vector3f v, in Matrix4x4f m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_mul4t(ref Vector4f ret, in Vector4f v, in Matrix4x4f m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_mul(ref Matrix4x4f ret, in Matrix4x4f m0, in Matrix4x4f m1);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_normalize(ref Matrix4x4f ret, in Matrix4x4f m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_transpose(ref Matrix4x4f ret, in Matrix4x4f m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_inverse(ref Matrix4x4f ret, in Matrix4x4f m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_inverse43(ref Matrix4x4f ret, in Matrix4x4f m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_lerp(ref Matrix4x4f ret, in Matrix4x4f m0, in Matrix4x4f m1, float k);
		
		public static readonly Matrix4x4f zero = new Matrix4x4f(Vector4f.zero, Vector4f.zero, Vector4f.zero, Vector4f.zero);
		public static readonly Matrix4x4f identity = new Matrix4x4f(new Vector4f(1.0f, 0.0f, 0.0f, 0.0f), new Vector4f(0.0f, 1.0f, 0.0f, 0.0f), new Vector4f(0.0f, 0.0f, 1.0f, 0.0f), new Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
		
		public Vector4f row_0;
		public Vector4f row_1;
		public Vector4f row_2;
		public Vector4f row_3;
	}
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential, Pack=16)]
	public struct Matrix4x4d {
		
		public Matrix4x4d(in Matrix4x3d m) { row_0 = m.row_0; row_1 = m.row_1; row_2 = m.row_2; row_3 = new Vector4d(0.0, 0.0, 0.0, 1.0); }
		public Matrix4x4d(in Matrix4x4d m) { row_0 = m.row_0; row_1 = m.row_1; row_2 = m.row_2; row_3 = m.row_3; }
		public Matrix4x4d(in Matrix4x4f m) { row_0 = new Vector4d(m.row_0); row_1 = new Vector4d(m.row_1); row_2 = new Vector4d(m.row_2); row_3 = new Vector4d(m.row_3); }
		public Matrix4x4d(in Vector4d row_0, in Vector4d row_1, in Vector4d row_2, in Vector4d row_3) { this.row_0 = row_0; this.row_1 = row_1; this.row_2 = row_2; this.row_3 = row_3; }
		public Matrix4x4d(in Quaterniond q) { Matrix4x3d ret = new Matrix4x3d(); ret.set(q); row_0 = ret.row_0; row_1 = ret.row_1; row_2 = ret.row_2; row_3 = new Vector4d(0.0, 0.0, 0.0, 1.0); }
		public Matrix4x4d(in double[] src, bool row_major = true) { Matrix4x4d ret = new Matrix4x4d(); ret.set(src, row_major); row_0 = ret.row_0; row_1 = ret.row_1; row_2 = ret.row_2; row_3 = ret.row_3; }
		
		public void set(in double[] src, bool row_major = true) { tsMatrix4x4d_set(ref this, in src, (uint)src.Length, row_major); }
		public void get(ref double[] dest, bool row_major = true) { tsMatrix4x4d_get(in this, ref dest, (uint)dest.Length, row_major); }
		public void set(in Quaterniond q) { tsQuaterniond_get(in q, ref row_0, ref row_1, ref row_2); row_3 = new Vector4d(0.0, 0.0, 0.0, 1.0); }
		public void get(ref Quaterniond q) { tsQuaterniond_set(ref q, in row_0, in row_1, in row_2); }
		
		public static Matrix4x4d scale(double s) { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_scale(ref ret, s, s, s); return ret; }
		public static Matrix4x4d scale(double x, double y, double z) { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_scale(ref ret, x, y, z); return ret; }
		public static Matrix4x4d scale(in Vector3d s) { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_scale(ref ret, s.x, s.y, s.z); return ret; }
		public static Matrix4x4d translate(double x, double y, double z) { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_translate(ref ret, x, y, z); return ret; }
		public static Matrix4x4d translate(in Vector3d t) { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_translate(ref ret, t.x, t.y, t.z); return ret; }
		public static Matrix4x4d rotateX(double angle) { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_rotateX(ref ret, angle); return ret; }
		public static Matrix4x4d rotateY(double angle) { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_rotateY(ref ret, angle); return ret; }
		public static Matrix4x4d rotateZ(double angle) { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_rotateZ(ref ret, angle); return ret; }
		public static Matrix4x4d rotate(in Vector3d axis, double angle) { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_rotate(ref ret, in axis, angle); return ret; }
		
		public static Matrix4x4d lookAt(in Vector3d from, in Vector3d to, in Vector3d up) { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_lookAt(ref ret, in from, in to, in up); return ret; }
		public static Matrix4x4d placeTo(in Vector3d to, in Vector3d from, in Vector3d up) { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_placeTo(ref ret, in to, in from, in up); return ret; }
		public static Matrix4x4d compose(in Vector3d t, in Quaterniond r, in Vector3d s) { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_compose(ref ret, in t, in r, in s); return ret; }
		public static Matrix4x4d basis(in Vector3d normal, in Vector3d t) { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_basis(ref ret, in normal, in t); return ret; }
		
		public static Matrix4x4d ortho(double left, double right, double bottom, double top, double znear, double zfar) { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_ortho(ref ret, left, right, bottom, top, znear, zfar); return ret; }
		public static Matrix4x4d frustum(double left, double right, double bottom, double top, double znear, double zfar, bool reverse = false) { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_frustum(ref ret, left, right, bottom, top, znear, zfar, reverse); return ret; }
		public static Matrix4x4d frustum(double left, double right, double bottom, double top, double znear, bool reverse = false) { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_frustumi(ref ret, left, right, bottom, top, znear, reverse); return ret; }
		public static Matrix4x4d perspective(double fov, double aspect, double znear, double zfar, bool reverse = false) { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_perspective(ref ret, fov, aspect, znear, zfar, reverse); return ret; }
		public static Matrix4x4d perspective(double fov, double aspect, double znear, bool reverse = false) { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_perspectivei(ref ret, fov, aspect, znear, reverse); return ret; }
		
		public static Vector2d operator*(in Matrix4x4d m, in Vector2d v) { Vector2d ret = new Vector2d(); tsMatrix4x4d_mul2(ref ret, in m, in v); return ret; }
		public static Vector3d operator*(in Matrix4x4d m, in Vector3d v) { Vector3d ret = new Vector3d(); tsMatrix4x4d_mul3(ref ret, in m, in v); return ret; }
		public static Vector4d operator*(in Matrix4x4d m, in Vector4d v) { Vector4d ret = new Vector4d(); tsMatrix4x4d_mul4(ref ret, in m, in v); return ret; }
		public static Vector2d operator*(in Vector2d v, in Matrix4x4d m) { Vector2d ret = new Vector2d(); tsMatrix4x4d_mul2t(ref ret, in v, in m); return ret; }
		public static Vector3d operator*(in Vector3d v, in Matrix4x4d m) { Vector3d ret = new Vector3d(); tsMatrix4x4d_mul3t(ref ret, in v, in m); return ret; }
		public static Vector4d operator*(in Vector4d v, in Matrix4x4d m) { Vector4d ret = new Vector4d(); tsMatrix4x4d_mul4t(ref ret, in v, in m); return ret; }
		public static Matrix4x4d operator*(in Matrix4x4d m0, in Matrix4x4d m1) { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_mul(ref ret, in m0, in m1); return ret; }
		
		public Matrix4x4d normalize() { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_normalize(ref ret, in this); return ret; }
		public Matrix4x4d transpose() { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_transpose(ref ret, in this); return ret; }
		public Matrix4x4d inverse() { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_inverse(ref ret, in this); return ret; }
		public Matrix4x4d inverse43() { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_inverse43(ref ret, in this); return ret; }
		
		public static Matrix4x4d lerp(in Matrix4x4d m0, in Matrix4x4d m1, double k) { Matrix4x4d ret = new Matrix4x4d(); tsMatrix4x4d_lerp(ref ret, in m0, in m1, k); return ret; }
		
		public override string ToString() { return System.String.Format("{0} : {1} : {2} : {3}", row_0, row_1, row_2, row_3); }
		
		[DllImport(Base.Import)] private static extern void tsMatrix4x4d_set(ref Matrix4x4d m, in double[] src, uint size, bool row_major);
		[DllImport(Base.Import)] private static extern void tsMatrix4x4d_get(in Matrix4x4d m, ref double[] dest, uint size, bool row_major);
		[DllImport(Base.Import)] private static extern void tsQuaterniond_set(ref Quaterniond q, in Vector4d row_0, in Vector4d row_1, in Vector4d row_2);
		[DllImport(Base.Import)] private static extern void tsQuaterniond_get(in Quaterniond q, ref Vector4d row_0, ref Vector4d row_1, ref Vector4d row_2);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_scale(ref Matrix4x4d ret, double x, double y, double z);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_translate(ref Matrix4x4d ret, double x, double y, double z);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_rotateX(ref Matrix4x4d ret, double angle);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_rotateY(ref Matrix4x4d ret, double angle);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_rotateZ(ref Matrix4x4d ret, double angle);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_rotate(ref Matrix4x4d ret, in Vector3d axis, double angle);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_lookAt(ref Matrix4x4d ret, in Vector3d from, in Vector3d to, in Vector3d up);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_placeTo(ref Matrix4x4d ret, in Vector3d to, in Vector3d from, in Vector3d up);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_compose(ref Matrix4x4d ret, in Vector3d t, in Quaterniond r, in Vector3d s);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_basis(ref Matrix4x4d ret, in Vector3d normal, in Vector3d t);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_ortho(ref Matrix4x4d ret, double left, double right, double bottom, double top, double znear, double zfar);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_frustum(ref Matrix4x4d ret, double left, double right, double bottom, double top, double znear, double zfar, bool reverse);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_frustumi(ref Matrix4x4d ret, double left, double right, double bottom, double top, double znear, bool reverse);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_perspective(ref Matrix4x4d ret, double fov, double aspect, double znear, double zfar, bool reverse);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_perspectivei(ref Matrix4x4d ret, double fov, double aspect, double znear, bool reverse);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_mul2(ref Vector2d ret, in Matrix4x4d m, in Vector2d v);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_mul3(ref Vector3d ret, in Matrix4x4d m, in Vector3d v);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_mul4(ref Vector4d ret, in Matrix4x4d m, in Vector4d v);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_mul2t(ref Vector2d ret, in Vector2d v, in Matrix4x4d m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_mul3t(ref Vector3d ret, in Vector3d v, in Matrix4x4d m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_mul4t(ref Vector4d ret, in Vector4d v, in Matrix4x4d m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_mul(ref Matrix4x4d ret, in Matrix4x4d m0, in Matrix4x4d m1);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_normalize(ref Matrix4x4d ret, in Matrix4x4d m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_transpose(ref Matrix4x4d ret, in Matrix4x4d m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_inverse(ref Matrix4x4d ret, in Matrix4x4d m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_inverse43(ref Matrix4x4d ret, in Matrix4x4d m);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_lerp(ref Matrix4x4d ret, in Matrix4x4d m0, in Matrix4x4d m1, double k);
		
		public static readonly Matrix4x4d zero = new Matrix4x4d(Vector4d.zero, Vector4d.zero, Vector4d.zero, Vector4d.zero);
		public static readonly Matrix4x4d identity = new Matrix4x4d(new Vector4d(1.0, 0.0, 0.0, 0.0), new Vector4d(0.0, 1.0, 0.0, 0.0), new Vector4d(0.0, 0.0, 1.0, 0.0), new Vector4d(0.0, 0.0, 0.0, 1.0));
		
		public Vector4d row_0;
		public Vector4d row_1;
		public Vector4d row_2;
		public Vector4d row_3;
	}
	
	/*****************************************************************************\
	 *
	 * Quaternion
	 *
	\*****************************************************************************/
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential, Pack=16)]
	public struct Quaternionf {
		
		public Quaternionf(float x, float y, float z, float w) { this.x = x; this.y = y; this.z = z; this.w = w; }
		public Quaternionf(in Quaternionf q) { x = q.x; y = q.y; z = q.z; w = q.w; }
		public Quaternionf(in Quaterniond q) { x = (float)q.x; y = (float)q.y; z = (float)q.z; w = (float)q.w; }
		public Quaternionf(in Matrix4x3f m) { Quaternionf ret = new Quaternionf(); ret.set(m); x = ret.x; y = ret.y; z = ret.z; w = ret.w; }
		public Quaternionf(in Matrix4x4f m) { Quaternionf ret = new Quaternionf(); ret.set(m); x = ret.x; y = ret.y; z = ret.z; w = ret.w; }
		public Quaternionf(in float[] q) { x = q[0]; y = q[1]; z = q[2]; w = q[3]; }
		
		public void set(in Matrix4x3f m) { tsQuaternionf_set(ref this, in m.row_0, in m.row_1, in m.row_2); }
		public void set(in Matrix4x4f m) { tsQuaternionf_set(ref this, in m.row_0, in m.row_1, in m.row_2); }
		public void get(ref Matrix4x3f m) { tsQuaternionf_get(in this, ref m.row_0, ref m.row_1, ref m.row_2); }
		public void get(ref Matrix4x4f m) { tsQuaternionf_get(in this, ref m.row_0, ref m.row_1, ref m.row_2); }
		
		public static Quaternionf rotateX(float angle) { Quaternionf ret = new Quaternionf(); tsQuaternionf_rotateX(ref ret, angle); return ret; }
		public static Quaternionf rotateY(float angle) { Quaternionf ret = new Quaternionf(); tsQuaternionf_rotateY(ref ret, angle); return ret; }
		public static Quaternionf rotateZ(float angle) { Quaternionf ret = new Quaternionf(); tsQuaternionf_rotateZ(ref ret, angle); return ret; }
		public static Quaternionf rotateXYZ(in Vector3f angles) { Quaternionf ret = new Quaternionf(); tsQuaternionf_rotateXYZ(ref ret, in angles); return ret; }
		public static Quaternionf rotateZYX(in Vector3f angles) { Quaternionf ret = new Quaternionf(); tsQuaternionf_rotateZYX(ref ret, in angles); return ret; }
		public static Quaternionf rotate(in Vector3f axis, float angle) { Quaternionf ret = new Quaternionf(); tsQuaternionf_rotate(ref ret, in axis, angle); return ret; }
		
		public static Vector2f operator*(in Quaternionf q, in Vector2f v) { Vector2f ret = new Vector2f(); tsQuaternionf_mul2(ref ret, in q, in v); return ret; }
		public static Vector3f operator*(in Quaternionf q, in Vector3f v) { Vector3f ret = new Vector3f(); tsQuaternionf_mul3(ref ret, in q, in v); return ret; }
		public static Vector4f operator*(in Quaternionf q, in Vector4f v) { Vector4f ret = new Vector4f(); tsQuaternionf_mul4(ref ret, in q, in v); return ret; }
		public static Vector2f operator*(in Vector2f v, in Quaternionf q) { Vector2f ret = new Vector2f(); tsQuaternionf_mul2t(ref ret, in v, in q); return ret; }
		public static Vector3f operator*(in Vector3f v, in Quaternionf q) { Vector3f ret = new Vector3f(); tsQuaternionf_mul3t(ref ret, in v, in q); return ret; }
		public static Vector4f operator*(in Vector4f v, in Quaternionf q) { Vector4f ret = new Vector4f(); tsQuaternionf_mul4t(ref ret, in v, in q); return ret; }
		public static Quaternionf operator*(in Quaternionf q, float v) { Quaternionf ret = new Quaternionf(); tsQuaternionf_mul1(ref ret, in q, v); return ret; }
		public static Quaternionf operator*(in Quaternionf q0, in Quaternionf q1) { Quaternionf ret = new Quaternionf(); tsQuaternionf_mul(ref ret, in q0, in q1); return ret; }
		
		public Quaternionf normalize() { Quaternionf ret = new Quaternionf(); tsQuaternionf_normalize(ref ret, in this); return ret; }
		public Quaternionf inverse() { Quaternionf ret = new Quaternionf(); tsQuaternionf_inverse(ref ret, in this); return ret; }
		
		public static Quaternionf lerp(in Quaternionf q0, in Quaternionf q1, float k) { Quaternionf ret = new Quaternionf(); tsQuaternionf_lerp(ref ret, in q0, in q1, k); return ret; }
		public static Quaternionf slerp(in Quaternionf q0, in Quaternionf q1, float k) { Quaternionf ret = new Quaternionf(); tsQuaternionf_slerp(ref ret, in q0, in q1, k); return ret; }
		
		public override string ToString() { return System.String.Format("({0} {1} {2} {3})", x, y, z, w); }
		
		[DllImport(Base.Import)] private static extern void tsQuaternionf_set(ref Quaternionf q, in Vector4f row_0, in Vector4f row_1, in Vector4f row_2);
		[DllImport(Base.Import)] private static extern void tsQuaternionf_get(in Quaternionf q, ref Vector4f row_0, ref Vector4f row_1, ref Vector4f row_2);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaternionf_rotateX(ref Quaternionf ret, float angle);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaternionf_rotateY(ref Quaternionf ret, float angle);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaternionf_rotateZ(ref Quaternionf ret, float angle);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaternionf_rotateXYZ(ref Quaternionf ret, in Vector3f angles);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaternionf_rotateZYX(ref Quaternionf ret, in Vector3f angles);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaternionf_rotate(ref Quaternionf ret, in Vector3f axis, float angle);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaternionf_mul2(ref Vector2f ret, in Quaternionf q, in Vector2f v);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaternionf_mul3(ref Vector3f ret, in Quaternionf q, in Vector3f v);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaternionf_mul4(ref Vector4f ret, in Quaternionf q, in Vector4f v);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaternionf_mul2t(ref Vector2f ret, in Vector2f v, in Quaternionf q);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaternionf_mul3t(ref Vector3f ret, in Vector3f v, in Quaternionf q);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaternionf_mul4t(ref Vector4f ret, in Vector4f v, in Quaternionf q);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaternionf_mul1(ref Quaternionf ret, in Quaternionf q, float v);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaternionf_mul(ref Quaternionf ret, in Quaternionf q0, in Quaternionf q1);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaternionf_normalize(ref Quaternionf ret, in Quaternionf q);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaternionf_inverse(ref Quaternionf ret, in Quaternionf q);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaternionf_lerp(ref Quaternionf ret, in Quaternionf q0, in Quaternionf q1, float k);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaternionf_slerp(ref Quaternionf ret, in Quaternionf q0, in Quaternionf q1, float k);
		
		public static readonly Quaternionf zero = new Quaternionf(0.0f, 0.0f, 0.0f, 0.0f);
		public static readonly Quaternionf identity = new Quaternionf(0.0f, 0.0f, 0.0f, 1.0f);
		
		public float x, y, z, w;
	}
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential, Pack=16)]
	public struct Quaterniond {
		
		public Quaterniond(double x, double y, double z, double w) { this.x = x; this.y = y; this.z = z; this.w = w; }
		public Quaterniond(in Quaterniond q) { x = q.x; y = q.y; z = q.z; w = q.w; }
		public Quaterniond(in Quaternionf q) { x = (double)q.x; y = (double)q.y; z = (double)q.z; w = (double)q.w; }
		public Quaterniond(in Matrix4x3d m) { Quaterniond ret = new Quaterniond(); ret.set(m); x = ret.x; y = ret.y; z = ret.z; w = ret.w; }
		public Quaterniond(in Matrix4x4d m) { Quaterniond ret = new Quaterniond(); ret.set(m); x = ret.x; y = ret.y; z = ret.z; w = ret.w; }
		public Quaterniond(in double[] q) { x = q[0]; y = q[1]; z = q[2]; w = q[3]; }
		
		public void set(in Matrix4x3d m) { tsQuaterniond_set(ref this, in m.row_0, in m.row_1, in m.row_2); }
		public void set(in Matrix4x4d m) { tsQuaterniond_set(ref this, in m.row_0, in m.row_1, in m.row_2); }
		public void get(ref Matrix4x3d m) { tsQuaterniond_get(in this, ref m.row_0, ref m.row_1, ref m.row_2); }
		public void get(ref Matrix4x4d m) { tsQuaterniond_get(in this, ref m.row_0, ref m.row_1, ref m.row_2); }
		
		public static Quaterniond rotateX(double angle) { Quaterniond ret = new Quaterniond(); tsQuaterniond_rotateX(ref ret, angle); return ret; }
		public static Quaterniond rotateY(double angle) { Quaterniond ret = new Quaterniond(); tsQuaterniond_rotateY(ref ret, angle); return ret; }
		public static Quaterniond rotateZ(double angle) { Quaterniond ret = new Quaterniond(); tsQuaterniond_rotateZ(ref ret, angle); return ret; }
		public static Quaterniond rotateXYZ(in Vector3d angles) { Quaterniond ret = new Quaterniond(); tsQuaterniond_rotateXYZ(ref ret, in angles); return ret; }
		public static Quaterniond rotateZYX(in Vector3d angles) { Quaterniond ret = new Quaterniond(); tsQuaterniond_rotateZYX(ref ret, in angles); return ret; }
		public static Quaterniond rotate(in Vector3d axis, double angle) { Quaterniond ret = new Quaterniond(); tsQuaterniond_rotate(ref ret, in axis, angle); return ret; }
		
		public static Vector2d operator*(in Quaterniond q, in Vector2d v) { Vector2d ret = new Vector2d(); tsQuaterniond_mul2(ref ret, in q, in v); return ret; }
		public static Vector3d operator*(in Quaterniond q, in Vector3d v) { Vector3d ret = new Vector3d(); tsQuaterniond_mul3(ref ret, in q, in v); return ret; }
		public static Vector4d operator*(in Quaterniond q, in Vector4d v) { Vector4d ret = new Vector4d(); tsQuaterniond_mul4(ref ret, in q, in v); return ret; }
		public static Vector2d operator*(in Vector2d v, in Quaterniond q) { Vector2d ret = new Vector2d(); tsQuaterniond_mul2t(ref ret, in v, in q); return ret; }
		public static Vector3d operator*(in Vector3d v, in Quaterniond q) { Vector3d ret = new Vector3d(); tsQuaterniond_mul3t(ref ret, in v, in q); return ret; }
		public static Vector4d operator*(in Vector4d v, in Quaterniond q) { Vector4d ret = new Vector4d(); tsQuaterniond_mul4t(ref ret, in v, in q); return ret; }
		public static Quaterniond operator*(in Quaterniond q, double v) { Quaterniond ret = new Quaterniond(); tsQuaterniond_mul1(ref ret, in q, v); return ret; }
		public static Quaterniond operator*(in Quaterniond q0, in Quaterniond q1) { Quaterniond ret = new Quaterniond(); tsQuaterniond_mul(ref ret, in q0, in q1); return ret; }
		
		public Quaterniond normalize() { Quaterniond ret = new Quaterniond(); tsQuaterniond_normalize(ref ret, in this); return ret; }
		public Quaterniond inverse() { Quaterniond ret = new Quaterniond(); tsQuaterniond_inverse(ref ret, in this); return ret; }
		
		public static Quaterniond lerp(in Quaterniond q0, in Quaterniond q1, double k) { Quaterniond ret = new Quaterniond(); tsQuaterniond_lerp(ref ret, in q0, in q1, k); return ret; }
		public static Quaterniond slerp(in Quaterniond q0, in Quaterniond q1, double k) { Quaterniond ret = new Quaterniond(); tsQuaterniond_slerp(ref ret, in q0, in q1, k); return ret; }
		
		public override string ToString() { return System.String.Format("({0} {1} {2} {3})", x, y, z, w); }
		
		[DllImport(Base.Import)] private static extern void tsQuaterniond_set(ref Quaterniond q, in Vector4d row_0, in Vector4d row_1, in Vector4d row_2);
		[DllImport(Base.Import)] private static extern void tsQuaterniond_get(in Quaterniond q, ref Vector4d row_0, ref Vector4d row_1, ref Vector4d row_2);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaterniond_rotateX(ref Quaterniond ret, double angle);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaterniond_rotateY(ref Quaterniond ret, double angle);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaterniond_rotateZ(ref Quaterniond ret, double angle);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaterniond_rotateXYZ(ref Quaterniond ret, in Vector3d angles);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaterniond_rotateZYX(ref Quaterniond ret, in Vector3d angles);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaterniond_rotate(ref Quaterniond ret, in Vector3d axis, double angle);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaterniond_mul2(ref Vector2d ret, in Quaterniond q, in Vector2d v);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaterniond_mul3(ref Vector3d ret, in Quaterniond q, in Vector3d v);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaterniond_mul4(ref Vector4d ret, in Quaterniond q, in Vector4d v);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaterniond_mul2t(ref Vector2d ret, in Vector2d v, in Quaterniond q);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaterniond_mul3t(ref Vector3d ret, in Vector3d v, in Quaterniond q);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaterniond_mul4t(ref Vector4d ret, in Vector4d v, in Quaterniond q);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaterniond_mul1(ref Quaterniond ret, in Quaterniond q, double v);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaterniond_mul(ref Quaterniond ret, in Quaterniond q0, in Quaterniond q1);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaterniond_normalize(ref Quaterniond ret, in Quaterniond q);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaterniond_inverse(ref Quaterniond ret, in Quaterniond q);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaterniond_lerp(ref Quaterniond ret, in Quaterniond q0, in Quaterniond q1, double k);
		[DllImport(Base.Import)] private static extern IntPtr tsQuaterniond_slerp(ref Quaterniond ret, in Quaterniond q0, in Quaterniond q1, double k);
		
		public static readonly Quaterniond zero = new Quaterniond(0.0, 0.0, 0.0, 0.0);
		public static readonly Quaterniond identity = new Quaterniond(0.0, 0.0, 0.0, 1.0);
		
		public double x, y, z, w;
	}
	
} /* namespace Tellusim */

// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

using System;
using System.Runtime.InteropServices;

/*
 */
namespace Tellusim {
	
	/*****************************************************************************\
	 *
	 * Base
	 *
	\*****************************************************************************/
	
	/*
	 */
	public static partial class Base {
		
		/// 8-bit integer constants
		public const sbyte Mini8 = -127 - 1;
		public const sbyte Maxi8 =  127;
		public const byte Maxu8 = 255;
		
		/// 16-bit integer constants
		public const short Mini16 = -32767 - 1;
		public const short Maxi16 =  32767;
		public const ushort Maxu16 = 65535;
		
		/// 32-bit integer constants
		public const int Mini32 = -2147483647 - 1;
		public const int Maxi32 =  2147483647;
		public const uint Maxu32 = 4294967295u;
		
		/// 64-bit integer constants
		public const long Mini64 = -9223372036854775807L - 1;
		public const long Maxi64 =  9223372036854775807L;
		public const ulong Maxu64 = 18446744073709551615uL;
		
		/// 16-bit floating point constants
		public const float Minf16 = 5.96046448e-08f;
		public const float Maxf16 = 65504.0f;
		
		/// 32-bit floating point constants
		public const float Minf32 = 1.17549435e-38f;
		public const float Maxf32 = 3.40282346e+38f;
		public const float Pi = 3.141592653589793f;
		public const float Pi2 = 6.283185307179586f;
		public const float Pi05 = 1.570796326794897f;
		public const float Sqrt2 = 1.4142135623730951f;
		public const float Deg2Rad = 0.017453292519943f;
		public const float Rad2Deg = 57.295779513082325f;
		
		/// 64-bit floating point constants
		public const double Minf64 = 2.22507385850720138e-308;
		public const double Maxf64 = 1.79769313486231571e+308;
		public const double Pid = 3.141592653589793115997963468544;
		public const double Pi2d = 6.283185307179586231995926937088;
		public const double Pi05d = 1.570796326794896557998981734272;
		public const double Sqrt2d = 1.414213562373095145474621858739;
		public const double Deg2Radd = 0.017453292519943295474371680598;
		public const double Rad2Degd = 57.295779513082322864647721871734;
		
		/// null handle
		public static HandleRef Null = new HandleRef(null, IntPtr.Zero);
		
		/// string utils
		internal static string[] getArgs(string[] args) {
			string[] ret = new string[args.Length + 1];
			for(uint i = 0; i < args.Length; i++) ret[i + 1] = args[i];
			ret[0] = "main";
			return ret;
		}
		
		internal static string getCString(IntPtr ptr) {
			if(ptr != IntPtr.Zero) {
				#if _WIN32
					return Marshal.PtrToStringAnsi(ptr);
				#else
					return Marshal.PtrToStringUTF8(ptr);
				#endif
			}
			return string.Empty;
		}
		
		internal static string getString(IntPtr self) {
			if(self != IntPtr.Zero) {
				#if _WIN32
					string ret = Marshal.PtrToStringAnsi(tsString_get_c(self), (int)tsString_size(self));
				#else
					string ret = Marshal.PtrToStringUTF8(tsString_get_c(self), (int)tsString_size(self));
				#endif
				tsString_delete(self);
				return ret;
			}
			return string.Empty;
		}
		
		/// array data
		internal static void setData<Type>(ref Type[] data, IntPtr ptr, int stride) {
			long address = ptr.ToInt64();
			for(int i = 0; i < data.Length; i++) {
				data[i] = Marshal.PtrToStructure<Type>(new IntPtr(address));
				address += stride;
			}
		}
		internal static void getData<Type>(Type[] data, IntPtr ptr, int stride) {
			long address = ptr.ToInt64();
			for(int i = 0; i < data.Length; i++) {
				Marshal.StructureToPtr(data[i], new IntPtr(address), false);
				address += stride;
			}
		}
		
		/// callback pointer
		internal static IntPtr getFunc(Delegate func) {
			if(func != null) return Marshal.GetFunctionPointerForDelegate(func);
			return IntPtr.Zero;
		}
		
		/// library name
		#if _WIN32
			#if TS_ARM64
				#if TS_DEBUG
					internal const string Import = "TellusimC_arm64d.dll";
				#else
					internal const string Import = "TellusimC_arm64.dll";
				#endif
			#else
				#if TS_DEBUG
					internal const string Import = "TellusimC_x64d.dll";
				#else
					internal const string Import = "TellusimC_x64.dll";
				#endif
			#endif
		#elif _LINUX
			#if TS_ARM64
				#if TS_DEBUG
					internal const string Import = "libTellusimC_arm64d.so";
				#else
					internal const string Import = "libTellusimC_arm64.so";
				#endif
			#else
				#if TS_DEBUG
					internal const string Import = "libTellusimC_x64d.so";
				#else
					internal const string Import = "libTellusimC_x64.so";
				#endif
			#endif
		#elif _MACOS
			#if TS_ARM64
				#if TS_DEBUG
					internal const string Import = "libTellusimC_arm64d.dylib";
				#else
					internal const string Import = "libTellusimC_arm64.dylib";
				#endif
			#else
				#if TS_DEBUG
					internal const string Import = "libTellusimC_x64d.dylib";
				#else
					internal const string Import = "libTellusimC_x64.dylib";
				#endif
			#endif
		#endif
		
		[DllImport(Import)] private static extern uint tsString_size(IntPtr self);
		[DllImport(Import)] private static extern IntPtr tsString_get_c(IntPtr self);
		[DllImport(Import)] private static extern void tsString_delete(IntPtr self);
	}
	
	/*****************************************************************************\
	 *
	 * Color
	 *
	\*****************************************************************************/
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct Color {
		
		public Color(float c) { r = c; g = c; b = c; a = c; }
		public Color(float l, float a) { r = l; g = l; b = l; this.a = a; }
		public Color(float r, float g, float b, float a = 1.0f) { this.r = r; this.g = g; this.b = b; this.a = a; }
		public Color(in Color c) { r = c.r; g = c.g; b = c.b; a = c.a; }
		public Color(in float[] c) { r = c[0]; g = c[1]; b = c[2]; a = c[3]; }
		
		public static Color operator*(in Color c0, float c1) { Color ret = new Color(); tsColor_mul1(ref ret, in c0, c1); return ret; }
		public static Color operator/(in Color c0, float c1) { Color ret = new Color(); tsColor_div1(ref ret, in c0, c1); return ret; }
		public static Color operator+(in Color c0, float c1) { Color ret = new Color(); tsColor_add1(ref ret, in c0, c1); return ret; }
		public static Color operator-(in Color c0, float c1) { Color ret = new Color(); tsColor_sub1(ref ret, in c0, c1); return ret; }
		
		public static Color operator*(in Color c0, in Color c1) { Color ret = new Color(); tsColor_mul(ref ret, in c0, in c1); return ret; }
		public static Color operator/(in Color c0, in Color c1) { Color ret = new Color(); tsColor_div(ref ret, in c0, in c1); return ret; }
		public static Color operator+(in Color c0, in Color c1) { Color ret = new Color(); tsColor_add(ref ret, in c0, in c1); return ret; }
		public static Color operator-(in Color c0, in Color c1) { Color ret = new Color(); tsColor_sub(ref ret, in c0, in c1); return ret; }
		
		public Color gammaToLinear() { Color ret = new Color(); tsColor_gammaToLinear(ref ret, in this); return ret; }
		public Color linearToGamma() { Color ret = new Color(); tsColor_linearToGamma(ref ret, in this); return ret; }
		
		public Color sRGBtoLinear() { Color ret = new Color(); tsColor_sRGBtoLinear(ref ret, in this); return ret; }
		public Color linearToSRGB() { Color ret = new Color(); tsColor_linearToSRGB(ref ret, in this); return ret; }
		
		public void setRGBAu8(uint color) { tsColor_setRGBAu8(ref this, color); }
		public uint getRGBAu8() { return tsColor_getRGBAu8(in this); }
		
		public void setBGRAu8(uint color) { tsColor_setBGRAu8(ref this, color); }
		public uint getBGRAu8() { return tsColor_getBGRAu8(in this); }
		
		public void setABGRu8(uint color) { tsColor_setABGRu8(ref this, color); }
		public uint getABGRu8() { return tsColor_getABGRu8(in this); }
		
		public static Color html(string src) { Color ret = new Color(); tsColor_html(ref ret, src); return ret; }
		public static Color hsv(float h, float s, float v) { Color ret = new Color(); tsColor_hsv(ref ret, h, s, v); return ret; }
		public static Color temperature(float t) { Color ret = new Color(); tsColor_temperature(ref ret, t); return ret; }
		
		public static Color min(in Color c0, in Color c1) { Color ret = new Color(); tsColor_min(ref ret, in c0, in c1); return ret; }
		public static Color max(in Color c0, in Color c1) { Color ret = new Color(); tsColor_max(ref ret, in c0, in c1); return ret; }
		
		public Color clamp(in Color c0, in Color c1) { Color ret = new Color(); tsColor_clamp(ref ret, in this, in c0, in c1); return ret; }
		public Color saturate() { Color ret = new Color(); tsColor_saturate(ref ret, in this); return ret; }
		
		public static Color lerp(in Color c0, in Color c1, float k) { Color ret = new Color(); tsColor_lerp(ref ret, in c0, in c1, k); return ret; }
		
		public override string ToString() { return System.String.Format("({0} {1} {2} {3})", r, g, b, a); }
		
		[DllImport(Base.Import)] private static extern IntPtr tsColor_gammaToLinear(ref Color ret, in Color c);
		[DllImport(Base.Import)] private static extern IntPtr tsColor_linearToGamma(ref Color ret, in Color c);
		[DllImport(Base.Import)] private static extern IntPtr tsColor_sRGBtoLinear(ref Color ret, in Color c);
		[DllImport(Base.Import)] private static extern IntPtr tsColor_linearToSRGB(ref Color ret, in Color c);
		[DllImport(Base.Import)] private static extern void tsColor_setRGBAu8(ref Color c, uint color);
		[DllImport(Base.Import)] private static extern uint tsColor_getRGBAu8(in Color c);
		[DllImport(Base.Import)] private static extern void tsColor_setBGRAu8(ref Color c, uint color);
		[DllImport(Base.Import)] private static extern uint tsColor_getBGRAu8(in Color c);
		[DllImport(Base.Import)] private static extern void tsColor_setABGRu8(ref Color c, uint color);
		[DllImport(Base.Import)] private static extern uint tsColor_getABGRu8(in Color c);
		[DllImport(Base.Import)] private static extern IntPtr tsColor_html(ref Color ret, string src);
		[DllImport(Base.Import)] private static extern IntPtr tsColor_hsv(ref Color ret, float h, float s, float v);
		[DllImport(Base.Import)] private static extern IntPtr tsColor_temperature(ref Color ret, float t);
		[DllImport(Base.Import)] private static extern IntPtr tsColor_mul1(ref Color ret, in Color c0, float c1);
		[DllImport(Base.Import)] private static extern IntPtr tsColor_div1(ref Color ret, in Color c0, float c1);
		[DllImport(Base.Import)] private static extern IntPtr tsColor_add1(ref Color ret, in Color c0, float c1);
		[DllImport(Base.Import)] private static extern IntPtr tsColor_sub1(ref Color ret, in Color c0, float c1);
		[DllImport(Base.Import)] private static extern IntPtr tsColor_mul(ref Color ret, in Color c0, in Color c1);
		[DllImport(Base.Import)] private static extern IntPtr tsColor_div(ref Color ret, in Color c0, in Color c1);
		[DllImport(Base.Import)] private static extern IntPtr tsColor_add(ref Color ret, in Color c0, in Color c1);
		[DllImport(Base.Import)] private static extern IntPtr tsColor_sub(ref Color ret, in Color c0, in Color c1);
		[DllImport(Base.Import)] private static extern IntPtr tsColor_min(ref Color ret, in Color c0, in Color c1);
		[DllImport(Base.Import)] private static extern IntPtr tsColor_max(ref Color ret, in Color c0, in Color c1);
		[DllImport(Base.Import)] private static extern IntPtr tsColor_clamp(ref Color ret, in Color c, in Color c0, in Color c1);
		[DllImport(Base.Import)] private static extern IntPtr tsColor_saturate(ref Color ret, in Color c);
		[DllImport(Base.Import)] private static extern IntPtr tsColor_lerp(ref Color ret, in Color c0, in Color c1, float k);
		
		public static readonly Color zero = new Color(0.0f, 0.0f, 0.0f, 0.0f);
		public static readonly Color black = new Color(0.0f, 0.0f, 0.0f, 1.0f);
		public static readonly Color white = new Color(1.0f, 1.0f, 1.0f, 1.0f);
		public static readonly Color gray = new Color(0.5f, 0.5f, 0.5f, 1.0f);
		
		public static readonly Color red = new Color(1.0f, 0.0f, 0.0f, 1.0f);
		public static readonly Color yellow = new Color(1.0f, 1.0f, 0.0f, 1.0f);
		public static readonly Color green = new Color(0.0f, 1.0f, 0.0f, 1.0f);
		public static readonly Color cyan = new Color(0.0f, 1.0f, 1.0f, 1.0f);
		public static readonly Color blue = new Color(0.0f, 0.0f, 1.0f, 1.0f);
		public static readonly Color magenta = new Color(1.0f, 0.0f, 1.0f, 1.0f);
		
		public float r, g, b, a;
	}
	
	/*****************************************************************************\
	 *
	 * ImageColor
	 *
	\*****************************************************************************/
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct ImageColor {
		
		public ImageColor(uint u) { r = u; g = u; b = u; a = u; }
		public ImageColor(uint l, uint a) { r = l; g = l; b = l; this.a = a; }
		public ImageColor(uint r, uint g, uint b, uint a) { this.r = r; this.g = g; this.b = b; this.a = a; }
		public ImageColor(in Vector4i v) { r = (uint)v.x; g = (uint)v.y; b = (uint)v.z; a = (uint)v.w; }
		public ImageColor(in Vector4u v) { r = v.x; g = v.y; b = v.z; a = v.w; }
		public ImageColor(in Vector4f v) { ImageColor ret = new ImageColor(); tsImageColor_set_f(ref ret, in v); r = ret.r; g = ret.g; b = ret.b; a = ret.a; }
		public ImageColor(in Color c) { ImageColor ret = new ImageColor(); tsImageColor_set_f(ref ret, in c); r = ret.r; g = ret.g; b = ret.b; a = ret.a; }
		public ImageColor(in Color c, Format format) { ImageColor ret = new ImageColor(); tsImageColor_set_c(ref ret, in c, format); r = ret.r; g = ret.g; b = ret.b; a = ret.a; }
		public ImageColor(in ImageColor c) { r = c.r; g = c.g; b = c.b; a = c.a; }
		public ImageColor(in uint[] c) { r = c[0]; g = c[1]; b = c[2]; a = c[3]; }
		
		public void set(in Vector4i v) { tsImageColor_set_i(ref this, in v); }
		public void get(ref Vector4i v) { tsImageColor_get_i(in this, ref v); }
		public void set(in Vector4u v) { tsImageColor_set_u(ref this, in v); }
		public void get(ref Vector4u v) { tsImageColor_get_u(in this, ref v); }
		public void set(in Vector4f v) { tsImageColor_set_f(ref this, in v); }
		public void get(ref Vector4f v) { tsImageColor_get_f(in this, ref v); }
		public void set(in Color c, Format format) { tsImageColor_set_c(ref this, in c, format); }
		public void get(ref Color c, Format format) { tsImageColor_get_c(in this, ref c, format); }
		
		public override string ToString() { return System.String.Format("({0} {1} {2} {3})", r, g, b, a); }
		
		[DllImport(Base.Import)] private static extern void tsImageColor_set_i(ref ImageColor c, in Vector4i src);
		[DllImport(Base.Import)] private static extern void tsImageColor_get_i(in ImageColor c, ref Vector4i dest);
		[DllImport(Base.Import)] private static extern void tsImageColor_set_u(ref ImageColor c, in Vector4u src);
		[DllImport(Base.Import)] private static extern void tsImageColor_get_u(in ImageColor c, ref Vector4u dest);
		[DllImport(Base.Import)] private static extern void tsImageColor_set_f(ref ImageColor c, in Vector4f src);
		[DllImport(Base.Import)] private static extern void tsImageColor_get_f(in ImageColor c, ref Vector4f dest);
		[DllImport(Base.Import)] private static extern void tsImageColor_set_f(ref ImageColor c, in Color src);
		[DllImport(Base.Import)] private static extern void tsImageColor_get_f(in ImageColor c, ref Color dest);
		[DllImport(Base.Import)] private static extern void tsImageColor_set_c(ref ImageColor c, in Color src, Format format);
		[DllImport(Base.Import)] private static extern void tsImageColor_get_c(in ImageColor c, ref Color dest, Format format);
		
		public uint r, g, b, a;
	}
	
	/*****************************************************************************\
	 *
	 * Bounds
	 *
	\*****************************************************************************/
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct BoundRectf {
		
		public BoundRectf(in Vector2f min, in Vector2f max) { this.min = min; this.max = max; }
		public BoundRectf(in BoundRectf r) { min = r.min; max = r.max; }
		public BoundRectf(in BoundRectd r) { BoundRectf ret = new BoundRectf(); tsBoundRectf_set_brd(ref ret, in r); min = ret.min; max = ret.max; }
		public BoundRectf(in BoundCirclef c) { BoundRectf ret = new BoundRectf(); tsBoundRectf_set_bc(ref ret, in c); min = ret.min; max = ret.max; }
		
		public void expand(in Vector2f v) { tsBoundRectf_expand1(ref this, in v); }
		public void expand(in BoundRectf r) { tsBoundRectf_expand(ref this, in r); }
		
		public bool inside(in Vector2f v) { return tsBoundRectf_inside1(in this, in v); }
		public bool inside(in BoundRectf r) { return tsBoundRectf_inside(in this, in r); }
		
		public float distance(in Vector2f v) { return tsBoundRectf_distance(in this, in v); }
		
		public static BoundRectf operator*(in Matrix4x3f m, in BoundRectf r) { BoundRectf ret = new BoundRectf(); tsMatrix4x3f_mul_br(ref ret, in m, in r); return ret; }
		public static BoundRectf operator*(in Matrix4x4f m, in BoundRectf r) { BoundRectf ret = new BoundRectf(); tsMatrix4x4f_mul_br(ref ret, in m, in r); return ret; }
		
		public override string ToString() { return System.String.Format("{0} : {1}", min, max); }
		
		[DllImport(Base.Import)] private static extern IntPtr tsBoundRectf_set_brd(ref BoundRectf ret, in BoundRectd r);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundRectf_set_bc(ref BoundRectf ret, in BoundCirclef c);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundRectf_expand1(ref BoundRectf ret, in Vector2f v);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundRectf_expand(ref BoundRectf ret, in BoundRectf r);
		[DllImport(Base.Import)] private static extern bool tsBoundRectf_inside1(in BoundRectf br, in Vector2f v);
		[DllImport(Base.Import)] private static extern bool tsBoundRectf_inside(in BoundRectf br, in BoundRectf r);
		[DllImport(Base.Import)] private static extern float tsBoundRectf_distance(in BoundRectf br, in Vector2f v);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_mul_br(ref BoundRectf ret, in Matrix4x3f m, in BoundRectf r);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_mul_br(ref BoundRectf ret, in Matrix4x4f m, in BoundRectf r);
		
		public Vector2f min;
		public Vector2f max;
	}
	
	[StructLayout(LayoutKind.Sequential)]
	public struct BoundRectd {
		
		public BoundRectd(in Vector2d min, in Vector2d max) { this.min = min; this.max = max; }
		public BoundRectd(in BoundRectd r) { min = r.min; max = r.max; }
		public BoundRectd(in BoundRectf r) { BoundRectd ret = new BoundRectd(); tsBoundRectd_set_brf(ref ret, in r); min = ret.min; max = ret.max; }
		public BoundRectd(in BoundCircled c) { BoundRectd ret = new BoundRectd(); tsBoundRectd_set_bc(ref ret, in c); min = ret.min; max = ret.max; }
		
		public void expand(in Vector2d v) { tsBoundRectd_expand1(ref this, in v); }
		public void expand(in BoundRectd r) { tsBoundRectd_expand(ref this, in r); }
		
		public bool inside(in Vector2d v) { return tsBoundRectd_inside1(in this, in v); }
		public bool inside(in BoundRectd r) { return tsBoundRectd_inside(in this, in r); }
		
		public double distance(in Vector2d v) { return tsBoundRectd_distance(in this, in v); }
		
		public static BoundRectd operator*(in Matrix4x3d m, in BoundRectd r) { BoundRectd ret = new BoundRectd(); tsMatrix4x3d_mul_br(ref ret, in m, in r); return ret; }
		public static BoundRectd operator*(in Matrix4x4d m, in BoundRectd r) { BoundRectd ret = new BoundRectd(); tsMatrix4x4d_mul_br(ref ret, in m, in r); return ret; }
		
		public override string ToString() { return System.String.Format("{0} : {1}", min, max); }
		
		[DllImport(Base.Import)] private static extern IntPtr tsBoundRectd_set_brf(ref BoundRectd ret, in BoundRectf r);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundRectd_set_bc(ref BoundRectd ret, in BoundCircled c);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundRectd_expand1(ref BoundRectd ret, in Vector2d v);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundRectd_expand(ref BoundRectd ret, in BoundRectd r);
		[DllImport(Base.Import)] private static extern bool tsBoundRectd_inside1(in BoundRectd br, in Vector2d v);
		[DllImport(Base.Import)] private static extern bool tsBoundRectd_inside(in BoundRectd br, in BoundRectd r);
		[DllImport(Base.Import)] private static extern float tsBoundRectd_distance(in BoundRectd br, in Vector2d v);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_mul_br(ref BoundRectd ret, in Matrix4x3d m, in BoundRectd r);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_mul_br(ref BoundRectd ret, in Matrix4x4d m, in BoundRectd r);
		
		public Vector2d min;
		public Vector2d max;
	}
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct BoundCirclef {
		
		public BoundCirclef(in Vector2f center, float radius) { this.center = center; this.radius = radius; }
		public BoundCirclef(in BoundCirclef c) { center = c.center; radius = c.radius; }
		public BoundCirclef(in BoundCircled c) { BoundCirclef ret = new BoundCirclef(); tsBoundCirclef_set_bcd(ref ret, in c); center = ret.center; radius = ret.radius; }
		public BoundCirclef(in BoundRectf r) { BoundCirclef ret = new BoundCirclef(); tsBoundCirclef_set_br(ref ret, in r); center = ret.center; radius = ret.radius; }
		
		public void expand(in Vector2f v) { tsBoundCirclef_expand1(ref this, in v); }
		public void expand(in BoundCirclef c) { tsBoundCirclef_expand(ref this, in c); }
		
		public void expandRadius(in Vector2f v) { tsBoundCirclef_expandRadius1(ref this, in v); }
		public void expandRadius(in BoundCirclef c) { tsBoundCirclef_expandRadius(ref this, in c); }
		
		public bool inside(in Vector2f v) { return tsBoundCirclef_inside1(in this, in v); }
		public bool inside(in BoundCirclef c) { return tsBoundCirclef_inside(in this, in c); }
		
		public float distance(in Vector2f v) { return tsBoundCirclef_distance(in this, in v); }
		
		public static BoundCirclef operator*(in Matrix4x3f m, in BoundCirclef r) { BoundCirclef ret = new BoundCirclef(); tsMatrix4x3f_mul_bc(ref ret, in m, in r); return ret; }
		public static BoundCirclef operator*(in Matrix4x4f m, in BoundCirclef r) { BoundCirclef ret = new BoundCirclef(); tsMatrix4x4f_mul_bc(ref ret, in m, in r); return ret; }
		
		public override string ToString() { return System.String.Format("{0} : {1}", center, radius); }
		
		[DllImport(Base.Import)] private static extern IntPtr tsBoundCirclef_set_bcd(ref BoundCirclef ret, in BoundCircled c);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundCirclef_set_br(ref BoundCirclef ret, in BoundRectf r);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundCirclef_expand1(ref BoundCirclef ret, in Vector2f v);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundCirclef_expand(ref BoundCirclef ret, in BoundCirclef c);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundCirclef_expandRadius1(ref BoundCirclef ret, in Vector2f v);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundCirclef_expandRadius(ref BoundCirclef ret, in BoundCirclef c);
		[DllImport(Base.Import)] private static extern bool tsBoundCirclef_inside1(in BoundCirclef bc, in Vector2f v);
		[DllImport(Base.Import)] private static extern bool tsBoundCirclef_inside(in BoundCirclef bc, in BoundCirclef c);
		[DllImport(Base.Import)] private static extern float tsBoundCirclef_distance(in BoundCirclef bc, in Vector2f v);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_mul_bc(ref BoundCirclef ret, in Matrix4x3f m, in BoundCirclef c);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_mul_bc(ref BoundCirclef ret, in Matrix4x4f m, in BoundCirclef c);
		
		public Vector2f center;
		public float radius;
	}
	
	[StructLayout(LayoutKind.Sequential)]
	public struct BoundCircled {
		
		public BoundCircled(in Vector2d center, double radius) { this.center = center; this.radius = radius; }
		public BoundCircled(in BoundCircled c) { center = c.center; radius = c.radius; }
		public BoundCircled(in BoundCirclef c) { BoundCircled ret = new BoundCircled(); tsBoundCircled_set_bcf(ref ret, in c); center = ret.center; radius = ret.radius; }
		public BoundCircled(in BoundRectd r) { BoundCircled ret = new BoundCircled(); tsBoundCircled_set_br(ref ret, in r); center = ret.center; radius = ret.radius; }
		
		public void expand(in Vector2d v) { tsBoundCircled_expand1(ref this, in v); }
		public void expand(in BoundCircled c) { tsBoundCircled_expand(ref this, in c); }
		
		public void expandRadius(in Vector2d v) { tsBoundCircled_expandRadius1(ref this, in v); }
		public void expandRadius(in BoundCircled c) { tsBoundCircled_expandRadius(ref this, in c); }
		
		public bool inside(in Vector2d v) { return tsBoundCircled_inside1(in this, in v); }
		public bool inside(in BoundCircled c) { return tsBoundCircled_inside(in this, in c); }
		
		public double distance(in Vector2d v) { return tsBoundCircled_distance(in this, in v); }
		
		public static BoundCircled operator*(in Matrix4x3d m, in BoundCircled r) { BoundCircled ret = new BoundCircled(); tsMatrix4x3d_mul_bc(ref ret, in m, in r); return ret; }
		public static BoundCircled operator*(in Matrix4x4d m, in BoundCircled r) { BoundCircled ret = new BoundCircled(); tsMatrix4x4d_mul_bc(ref ret, in m, in r); return ret; }
		
		public override string ToString() { return System.String.Format("{0} : {1}", center, radius); }
		
		[DllImport(Base.Import)] private static extern IntPtr tsBoundCircled_set_bcf(ref BoundCircled ret, in BoundCirclef c);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundCircled_set_br(ref BoundCircled ret, in BoundRectd r);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundCircled_expand1(ref BoundCircled ret, in Vector2d v);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundCircled_expand(ref BoundCircled ret, in BoundCircled c);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundCircled_expandRadius1(ref BoundCircled ret, in Vector2d v);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundCircled_expandRadius(ref BoundCircled ret, in BoundCircled c);
		[DllImport(Base.Import)] private static extern bool tsBoundCircled_inside1(in BoundCircled bc, in Vector2d v);
		[DllImport(Base.Import)] private static extern bool tsBoundCircled_inside(in BoundCircled bc, in BoundCircled c);
		[DllImport(Base.Import)] private static extern float tsBoundCircled_distance(in BoundCircled bc, in Vector2d v);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_mul_bc(ref BoundCircled ret, in Matrix4x3d m, in BoundCircled c);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_mul_bc(ref BoundCircled ret, in Matrix4x4d m, in BoundCircled c);
		
		public Vector2d center;
		public double radius;
	}
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct BoundBoxf {
		
		public BoundBoxf(in Vector3f min, in Vector3f max) { this.min = min; this.max = max; }
		public BoundBoxf(in BoundBoxf b) { min = b.min; max = b.max; }
		public BoundBoxf(in BoundBoxd b) { BoundBoxf ret = new BoundBoxf(); tsBoundBoxf_set_bbd(ref ret, in b); min = ret.min; max = ret.max; }
		public BoundBoxf(in BoundSpheref s) { BoundBoxf ret = new BoundBoxf(); tsBoundBoxf_set_bs(ref ret, in s); min = ret.min; max = ret.max; }
		
		public void expand(in Vector3f v) { tsBoundBoxf_expand1(ref this, in v); }
		public void expand(in BoundBoxf b) { tsBoundBoxf_expand(ref this, in b); }
		
		public bool inside(in Vector3f v) { return tsBoundBoxf_inside1(in this, in v); }
		public bool inside(in BoundBoxf b) { return tsBoundBoxf_inside(in this, in b); }
		
		public double distance(in Vector3f v) { return tsBoundBoxf_distance(in this, in v); }
		
		public static BoundBoxf operator*(in Matrix4x3f m, in BoundBoxf r) { BoundBoxf ret = new BoundBoxf(); tsMatrix4x3f_mul_bb(ref ret, in m, in r); return ret; }
		public static BoundBoxf operator*(in Matrix4x4f m, in BoundBoxf r) { BoundBoxf ret = new BoundBoxf(); tsMatrix4x4f_mul_bb(ref ret, in m, in r); return ret; }
		
		public override string ToString() { return System.String.Format("{0} : {1}", min, max); }
		
		[DllImport(Base.Import)] private static extern IntPtr tsBoundBoxf_set_bbd(ref BoundBoxf ret, in BoundBoxd b);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundBoxf_set_bs(ref BoundBoxf ret, in BoundSpheref s);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundBoxf_expand1(ref BoundBoxf ret, in Vector3f v);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundBoxf_expand(ref BoundBoxf ret, in BoundBoxf b);
		[DllImport(Base.Import)] private static extern bool tsBoundBoxf_inside1(in BoundBoxf br, in Vector3f v);
		[DllImport(Base.Import)] private static extern bool tsBoundBoxf_inside(in BoundBoxf br, in BoundBoxf b);
		[DllImport(Base.Import)] private static extern float tsBoundBoxf_distance(in BoundBoxf br, in Vector3f v);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_mul_bb(ref BoundBoxf ret, in Matrix4x3f m, in BoundBoxf b);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_mul_bb(ref BoundBoxf ret, in Matrix4x4f m, in BoundBoxf b);
		
		public Vector3f min;
		public Vector3f max;
	}
	
	[StructLayout(LayoutKind.Sequential)]
	public struct BoundBoxd {
		
		public BoundBoxd(in Vector3d min, in Vector3d max) { this.min = min; this.max = max; }
		public BoundBoxd(in BoundBoxd b) { min = b.min; max = b.max; }
		public BoundBoxd(in BoundBoxf b) { BoundBoxd ret = new BoundBoxd(); tsBoundBoxd_set_bbf(ref ret, in b); min = ret.min; max = ret.max; }
		public BoundBoxd(in BoundSphered s) { BoundBoxd ret = new BoundBoxd(); tsBoundBoxd_set_bs(ref ret, in s); min = ret.min; max = ret.max; }
		
		public void expand(in Vector3d v) { tsBoundBoxd_expand1(ref this, in v); }
		public void expand(in BoundBoxd b) { tsBoundBoxd_expand(ref this, in b); }
		
		public bool inside(in Vector3d v) { return tsBoundBoxd_inside1(in this, in v); }
		public bool inside(in BoundBoxd b) { return tsBoundBoxd_inside(in this, in b); }
		
		public double distance(in Vector3d v) { return tsBoundBoxd_distance(in this, in v); }
		
		public static BoundBoxd operator*(in Matrix4x3d m, in BoundBoxd r) { BoundBoxd ret = new BoundBoxd(); tsMatrix4x3d_mul_bb(ref ret, in m, in r); return ret; }
		public static BoundBoxd operator*(in Matrix4x4d m, in BoundBoxd r) { BoundBoxd ret = new BoundBoxd(); tsMatrix4x4d_mul_bb(ref ret, in m, in r); return ret; }
		
		public override string ToString() { return System.String.Format("{0} : {1}", min, max); }
		
		[DllImport(Base.Import)] private static extern IntPtr tsBoundBoxd_set_bbf(ref BoundBoxd ret, in BoundBoxf b);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundBoxd_set_bs(ref BoundBoxd ret, in BoundSphered s);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundBoxd_expand1(ref BoundBoxd ret, in Vector3d v);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundBoxd_expand(ref BoundBoxd ret, in BoundBoxd b);
		[DllImport(Base.Import)] private static extern bool tsBoundBoxd_inside1(in BoundBoxd br, in Vector3d v);
		[DllImport(Base.Import)] private static extern bool tsBoundBoxd_inside(in BoundBoxd br, in BoundBoxd b);
		[DllImport(Base.Import)] private static extern float tsBoundBoxd_distance(in BoundBoxd br, in Vector3d v);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_mul_bb(ref BoundBoxd ret, in Matrix4x3d m, in BoundBoxd b);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_mul_bb(ref BoundBoxd ret, in Matrix4x4d m, in BoundBoxd b);
		
		public Vector3d min;
		public Vector3d max;
	}
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct BoundSpheref {
		
		public BoundSpheref(in Vector3f center, float radius) { this.center = center; this.radius = radius; }
		public BoundSpheref(in BoundSpheref s) { center = s.center; radius = s.radius; }
		public BoundSpheref(in BoundSphered s) { BoundSpheref ret = new BoundSpheref(); tsBoundSpheref_set_bsd(ref ret, in s); center = ret.center; radius = ret.radius; }
		public BoundSpheref(in BoundBoxf b) { BoundSpheref ret = new BoundSpheref(); tsBoundSpheref_set_bb(ref ret, in b); center = ret.center; radius = ret.radius; }
		
		public void expand(in Vector2d v) { tsBoundSpheref_expand1(ref this, in v); }
		public void expand(in BoundSpheref s) { tsBoundSpheref_expand(ref this, in s); }
		
		public void expandRadius(in Vector2d v) { tsBoundSpheref_expandRadius1(ref this, in v); }
		public void expandRadius(in BoundSpheref s) { tsBoundSpheref_expandRadius(ref this, in s); }
		
		public bool inside(in Vector2d v) { return tsBoundSpheref_inside1(in this, in v); }
		public bool inside(in BoundSpheref s) { return tsBoundSpheref_inside(in this, in s); }
		
		public float distance(in Vector2d v) { return tsBoundSpheref_distance(in this, in v); }
		
		public static BoundSpheref operator*(in Matrix4x3f m, in BoundSpheref r) { BoundSpheref ret = new BoundSpheref(); tsMatrix4x3f_mul_bs(ref ret, in m, in r); return ret; }
		public static BoundSpheref operator*(in Matrix4x4f m, in BoundSpheref r) { BoundSpheref ret = new BoundSpheref(); tsMatrix4x4f_mul_bs(ref ret, in m, in r); return ret; }
		
		public override string ToString() { return System.String.Format("{0} : {1}", center, radius); }
		
		[DllImport(Base.Import)] private static extern IntPtr tsBoundSpheref_set_bsd(ref BoundSpheref ret, in BoundSphered s);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundSpheref_set_bb(ref BoundSpheref ret, in BoundBoxf b);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundSpheref_expand1(ref BoundSpheref ret, in Vector2d v);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundSpheref_expand(ref BoundSpheref ret, in BoundSpheref s);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundSpheref_expandRadius1(ref BoundSpheref ret, in Vector2d v);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundSpheref_expandRadius(ref BoundSpheref ret, in BoundSpheref s);
		[DllImport(Base.Import)] private static extern bool tsBoundSpheref_inside1(in BoundSpheref bs, in Vector2d v);
		[DllImport(Base.Import)] private static extern bool tsBoundSpheref_inside(in BoundSpheref bs, in BoundSpheref s);
		[DllImport(Base.Import)] private static extern float tsBoundSpheref_distance(in BoundSpheref bs, in Vector2d v);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3f_mul_bs(ref BoundSpheref ret, in Matrix4x3f m, in BoundSpheref s);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4f_mul_bs(ref BoundSpheref ret, in Matrix4x4f m, in BoundSpheref s);
		
		public Vector3f center;
		public float radius;
	}
	
	[StructLayout(LayoutKind.Sequential)]
	public struct BoundSphered {
		
		public BoundSphered(in Vector3d center, double radius) { this.center = center; this.radius = radius; }
		public BoundSphered(in BoundSphered s) { center = s.center; radius = s.radius; }
		public BoundSphered(in BoundSpheref s) { BoundSphered ret = new BoundSphered(); tsBoundSphered_set_bsf(ref ret, in s); center = ret.center; radius = ret.radius; }
		public BoundSphered(in BoundBoxd b) { BoundSphered ret = new BoundSphered(); tsBoundSphered_set_bb(ref ret, in b); center = ret.center; radius = ret.radius; }
		
		public void expand(in Vector3d v) { tsBoundSphered_expand1(ref this, in v); }
		public void expand(in BoundSphered s) { tsBoundSphered_expand(ref this, in s); }
		
		public void expandRadius(in Vector3d v) { tsBoundSphered_expandRadius1(ref this, in v); }
		public void expandRadius(in BoundSphered s) { tsBoundSphered_expandRadius(ref this, in s); }
		
		public bool inside(in Vector3d v) { return tsBoundSphered_inside1(in this, in v); }
		public bool inside(in BoundSphered s) { return tsBoundSphered_inside(in this, in s); }
		
		public float distance(in Vector3d v) { return tsBoundSphered_distance(in this, in v); }
		
		public static BoundSphered operator*(in Matrix4x3d m, in BoundSphered r) { BoundSphered ret = new BoundSphered(); tsMatrix4x3d_mul_bs(ref ret, in m, in r); return ret; }
		public static BoundSphered operator*(in Matrix4x4d m, in BoundSphered r) { BoundSphered ret = new BoundSphered(); tsMatrix4x4d_mul_bs(ref ret, in m, in r); return ret; }
		
		public override string ToString() { return System.String.Format("{0} : {1}", center, radius); }
		
		[DllImport(Base.Import)] private static extern IntPtr tsBoundSphered_set_bsf(ref BoundSphered ret, in BoundSpheref s);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundSphered_set_bb(ref BoundSphered ret, in BoundBoxd b);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundSphered_expand1(ref BoundSphered ret, in Vector3d v);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundSphered_expand(ref BoundSphered ret, in BoundSphered s);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundSphered_expandRadius1(ref BoundSphered ret, in Vector3d v);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundSphered_expandRadius(ref BoundSphered ret, in BoundSphered s);
		[DllImport(Base.Import)] private static extern bool tsBoundSphered_inside1(in BoundSphered bs, in Vector3d v);
		[DllImport(Base.Import)] private static extern bool tsBoundSphered_inside(in BoundSphered bs, in BoundSphered s);
		[DllImport(Base.Import)] private static extern float tsBoundSphered_distance(in BoundSphered bs, in Vector3d v);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x3d_mul_bs(ref BoundSphered ret, in Matrix4x3d m, in BoundSphered s);
		[DllImport(Base.Import)] private static extern IntPtr tsMatrix4x4d_mul_bs(ref BoundSphered ret, in Matrix4x4d m, in BoundSphered s);
		
		public Vector3d center;
		public double radius;
	}
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct BoundFrustumf {
		
		public BoundFrustumf(in Matrix4x4f p, in Matrix4x4f m, in Vector3f c, in Vector4f l, in Vector4f r, in Vector4f b, in Vector4f t, in Vector4f n, in Vector4f f) { this.projection = p; this.modelview = m; this.camera = c; this.plane_l = l; this.plane_r = r; this.plane_b = b; this.plane_t = t; this.plane_n = n; this.plane_f = f; this.sign_l = 0; this.sign_r = 0; this.sign_b = 0; this.sign_t = 0; this.sign_n = 0; this.sign_f = 0; }
		public BoundFrustumf(in BoundFrustumf f) { projection = f.projection; modelview = f.modelview; camera = f.camera; plane_l = f.plane_l; plane_r = f.plane_r; plane_b = f.plane_b; plane_t = f.plane_t; plane_n = f.plane_n; plane_f = f.plane_f; sign_l = f.sign_l; sign_r = f.sign_r; sign_b = f.sign_b; sign_t = f.sign_t; sign_n = f.sign_n; sign_f = f.sign_f; }
		public BoundFrustumf(in BoundFrustumd f) { BoundFrustumf ret = new BoundFrustumf(); tsBoundFrustumf_set_bfd(ref ret, in f); projection = ret.projection; modelview = ret.modelview; camera = ret.camera; plane_l = ret.plane_l; plane_r = ret.plane_r; plane_b = ret.plane_b; plane_t = ret.plane_t; plane_n = ret.plane_n; plane_f = ret.plane_f; sign_l = ret.sign_l; sign_r = ret.sign_r; sign_b = ret.sign_b; sign_t = ret.sign_t; sign_n = ret.sign_n; sign_f = ret.sign_f; }
		public BoundFrustumf(in Matrix4x4f p, in Matrix4x4f m, float aspect = 1.0f) { BoundFrustumf ret = new BoundFrustumf(); tsBoundFrustumf_set(ref ret, in p, in m, aspect); projection = ret.projection; modelview = ret.modelview; camera = ret.camera; plane_l = ret.plane_l; plane_r = ret.plane_r; plane_b = ret.plane_b; plane_t = ret.plane_t; plane_n = ret.plane_n; plane_f = ret.plane_f; sign_l = ret.sign_l; sign_r = ret.sign_r; sign_b = ret.sign_b; sign_t = ret.sign_t; sign_n = ret.sign_n; sign_f = ret.sign_f; }
		
		public bool inside(in BoundBoxf bb) { return tsBoundFrustumf_inside_bb(in this, in bb); }
		public bool inside(in BoundSpheref bs) { return tsBoundFrustumf_inside_bs(in this, in bs); }
		
		public override string ToString() { return System.String.Format("{0} : {1} : {2} : {3} : {4} : {5}", plane_l, plane_r, plane_b, plane_t, plane_n, plane_f); }
		
		[DllImport(Base.Import)] private static extern IntPtr tsBoundFrustumf_set_bfd(ref BoundFrustumf ret, in BoundFrustumd bf);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundFrustumf_set(ref BoundFrustumf ret, in Matrix4x4f projection, in Matrix4x4f modelview, float aspect);
		[DllImport(Base.Import)] private static extern bool tsBoundFrustumf_inside_bb(in BoundFrustumf bf, in BoundBoxf bb);
		[DllImport(Base.Import)] private static extern bool tsBoundFrustumf_inside_bs(in BoundFrustumf bf, in BoundSpheref bs);
		
		public Matrix4x4f projection;
		public Matrix4x4f modelview;
		public Vector3f camera;
		
		public Vector4f plane_l;
		public Vector4f plane_r;
		public Vector4f plane_b;
		public Vector4f plane_t;
		public Vector4f plane_n;
		public Vector4f plane_f;
		
		public uint sign_l;
		public uint sign_r;
		public uint sign_b;
		public uint sign_t;
		public uint sign_n;
		public uint sign_f;
	}
	
	[StructLayout(LayoutKind.Sequential)]
	public struct BoundFrustumd {
		
		public BoundFrustumd(in Matrix4x4d p, in Matrix4x4d m, in Vector3d c, in Vector4d l, in Vector4d r, in Vector4d b, in Vector4d t, in Vector4d n, in Vector4d f) { this.projection = p; this.modelview = m; this.camera = c; this.plane_l = l; this.plane_r = r; this.plane_b = b; this.plane_t = t; this.plane_n = n; this.plane_f = f; this.sign_l = 0; this.sign_r = 0; this.sign_b = 0; this.sign_t = 0; this.sign_n = 0; this.sign_f = 0; }
		public BoundFrustumd(in BoundFrustumd f) { projection = f.projection; modelview = f.modelview; camera = f.camera; plane_l = f.plane_l; plane_r = f.plane_r; plane_b = f.plane_b; plane_t = f.plane_t; plane_n = f.plane_n; plane_f = f.plane_f; sign_l = f.sign_l; sign_r = f.sign_r; sign_b = f.sign_b; sign_t = f.sign_t; sign_n = f.sign_n; sign_f = f.sign_f; }
		public BoundFrustumd(in BoundFrustumf f) { BoundFrustumd ret = new BoundFrustumd(); tsBoundFrustumd_set_bff(ref ret, in f); projection = ret.projection; modelview = ret.modelview; camera = ret.camera; plane_l = ret.plane_l; plane_r = ret.plane_r; plane_b = ret.plane_b; plane_t = ret.plane_t; plane_n = ret.plane_n; plane_f = ret.plane_f; sign_l = ret.sign_l; sign_r = ret.sign_r; sign_b = ret.sign_b; sign_t = ret.sign_t; sign_n = ret.sign_n; sign_f = ret.sign_f; }
		public BoundFrustumd(in Matrix4x4d p, in Matrix4x4d m, double aspect = 1.0) { BoundFrustumd ret = new BoundFrustumd(); tsBoundFrustumd_set(ref ret, in p, in m, aspect); projection = ret.projection; modelview = ret.modelview; camera = ret.camera; plane_l = ret.plane_l; plane_r = ret.plane_r; plane_b = ret.plane_b; plane_t = ret.plane_t; plane_n = ret.plane_n; plane_f = ret.plane_f; sign_l = ret.sign_l; sign_r = ret.sign_r; sign_b = ret.sign_b; sign_t = ret.sign_t; sign_n = ret.sign_n; sign_f = ret.sign_f; }
		
		public bool inside(in BoundBoxd bb) { return tsBoundFrustumd_inside_bb(in this, in bb); }
		public bool inside(in BoundSphered bs) { return tsBoundFrustumd_inside_bs(in this, in bs); }
		
		public override string ToString() { return System.String.Format("{0} : {1} : {2} : {3} : {4} : {5}", plane_l, plane_r, plane_b, plane_t, plane_n, plane_f); }
		
		[DllImport(Base.Import)] private static extern IntPtr tsBoundFrustumd_set_bff(ref BoundFrustumd ret, in BoundFrustumf bf);
		[DllImport(Base.Import)] private static extern IntPtr tsBoundFrustumd_set(ref BoundFrustumd ret, in Matrix4x4d projection, in Matrix4x4d modelview, double aspect);
		[DllImport(Base.Import)] private static extern bool tsBoundFrustumd_inside_bb(in BoundFrustumd bf, in BoundBoxd bb);
		[DllImport(Base.Import)] private static extern bool tsBoundFrustumd_inside_bs(in BoundFrustumd bf, in BoundSphered bs);
		
		public Matrix4x4d projection;
		public Matrix4x4d modelview;
		public Vector3d camera;
		
		public Vector4d plane_l;
		public Vector4d plane_r;
		public Vector4d plane_b;
		public Vector4d plane_t;
		public Vector4d plane_n;
		public Vector4d plane_f;
		
		public uint sign_l;
		public uint sign_r;
		public uint sign_b;
		public uint sign_t;
		public uint sign_n;
		public uint sign_f;
	}
	
	/*****************************************************************************\
	 *
	 * Interface
	 *
	\*****************************************************************************/
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct Rect {
		
		public Rect(float value) { this.left = value; this.right = value; this.bottom = value; this.top = value; }
		public Rect(float horizontal, float vertical) { this.left = horizontal; this.right = horizontal; this.bottom = vertical; this.top = vertical; }
		public Rect(float left, float right, float bottom, float top) { this.left = left; this.right = right; this.bottom = bottom; this.top = top; }
		
		public float left;
		public float right;
		public float bottom;
		public float top;
	}
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct FontStyle {
		
		public FontStyle(uint size) { this.size = size; this.scale = 100; this.mono = false; this.kerning = true; this.spacing = Vector2f.zero; this.color = Color.white; this.offset = Vector3f.zero; this.shadow = Color.black; }
		public FontStyle(in Color color) { this.size = 16; this.scale = 100; this.mono = false; this.kerning = true; this.spacing = Vector2f.zero; this.color = color; this.offset = Vector3f.zero; this.shadow = Color.black; }
		public FontStyle(uint size, in Color color) { this.size = size; this.scale = 100; this.mono = false; this.kerning = true; this.spacing = Vector2f.zero; this.color = color; this.offset = Vector3f.zero; this.shadow = Color.black; }
		
		public uint size;
		public uint scale;
		[MarshalAs(UnmanagedType.U1)] public bool mono;
		[MarshalAs(UnmanagedType.U1)] public bool kerning;
		public Vector2f spacing;
		public Color color;
		public Vector3f offset;
		public Color shadow;
	}
	
	[StructLayout(LayoutKind.Sequential)]
	public struct StrokeStyle {
		
		public StrokeStyle(float width) { this.width = width; this.offset = 0.0f; this.color = Color.white; }
		public StrokeStyle(in Color color) { this.width = 0.0f; this.offset = 0.0f; this.color = color; }
		public StrokeStyle(float width, float offset) { this.width = width; this.offset = offset; this.color = Color.white; }
		public StrokeStyle(float width, in Color color) { this.width = width; this.offset = 0.0f; this.color = color; }
		public StrokeStyle(float width, float offset, in Color color) { this.width = width; this.offset = offset; this.color = color; }
		
		public float width;
		public float offset;
		public Color color;
	}
	
	[StructLayout(LayoutKind.Sequential)]
	public struct GradientStyle {
		
		public GradientStyle(in Color c0, in Color c1) { this.radius = 0.0f; this.length = 0.0f; this.center = Vector2f.zero; this.axis = Vector2f.zero; this.color_0 = c0; this.color_1 = c1; }
		public GradientStyle(float radius, in Vector2f center) { this.radius = radius; this.length = 0.0f; this.center = center; this.axis = Vector2f.zero; this.color_0 = Color.white; this.color_1 = Color.white; }
		public GradientStyle(float length, in Vector2f center, in Vector2f axis) { this.radius = 0.0f; this.length = length; this.center = center; this.axis = axis; this.color_0 = Color.white; this.color_1 = Color.white; }
		public GradientStyle(float radius, in Vector2f center, in Color c0, in Color c1) { this.radius = radius; this.length = 0.0f; this.center = center; this.axis = Vector2f.zero; this.color_0 = c0; this.color_1 = c1; }
		public GradientStyle(float length, in Vector2f center, in Vector2f axis, in Color c0, in Color c1) { this.radius = 0.0f; this.length = length; this.center = center; this.axis = axis; this.color_0 = c0; this.color_1 = c1; }
		
		public float radius;
		public float length;
		public Vector2f center;
		public Vector2f axis;
		public Color color_0;
		public Color color_1;
	}
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct CanvasVertex {
		public Vector3f position;
		public Vector2f texcoord;
		public uint color;
	}
	
	[StructLayout(LayoutKind.Sequential)]
	public struct CanvasShapeVertex {
		public Vector4f position;
		public Vector4f parameters;
		public Vector2f texcoord;
		public Vector2u padding;
	}
	
	[StructLayout(LayoutKind.Sequential)]
	public struct CanvasStripVertex {
		public Vector4f position;
		public Vector4f parameters;
		public Vector4f adjacencies;
	}
	
	/*****************************************************************************\
	 *
	 * Platform
	 *
	\*****************************************************************************/
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct Origin {
		
		public Origin(uint x, uint y, uint z = 0) { this.x = x; this.y = y; this.z = z; }
		
		public override string ToString() { return System.String.Format("({0} {1} {2})", x, y, z); }
		
		public uint x;
		public uint y;
		public uint z;
	}
	
	[StructLayout(LayoutKind.Sequential)]
	public struct Size {
		
		public Size(uint width, uint height, uint depth = 1) { this.width = width; this.height = height; this.depth = depth; }
		
		public override string ToString() { return System.String.Format("({0} {1} {2})", width, height, depth); }
		
		public uint width;
		public uint height;
		public uint depth;
	}
	
	[StructLayout(LayoutKind.Sequential)]
	public struct Region {
		
		public Region(uint x, uint y, uint width, uint height) { this.x = x; this.y = y; z = 0; this.width = width; this.height = height; depth = 1; }
		public Region(uint x, uint y, uint z, uint width, uint height, uint depth) { this.x = x; this.y = y; this.z = z; this.width = width; this.height = height; this.depth = depth; }
		
		public override string ToString() { return System.String.Format("({0} {1} {2}) - ({3} {4} {5})", x, y, z, width, height, depth); }
		
		public uint x;
		public uint y;
		public uint z;
		public uint width;
		public uint height;
		public uint depth;
	}
	
	/*
	 */
	public struct Face {
		
		public Face(uint index, uint size = 1) { this.index = index; this.size = size; }
		
		public override string ToString() { return System.String.Format("({0} {1})", index, size); }
		
		public static readonly Face zero = new Face(0);
		
		public uint index;
		public uint size;
	}
	
	public struct Layer {
		
		public Layer(uint index, uint size = 1) { this.index = index; this.size = size; }
		
		public override string ToString() { return System.String.Format("({0} {1})", index, size); }
		
		public static readonly Layer zero = new Layer(0);
		
		public uint index;
		public uint size;
	}
	
	public struct Mipmap {
		
		public Mipmap(uint index, uint size = 1) { this.index = index; this.size = size; }
		
		public override string ToString() { return System.String.Format("({0} {1})", index, size); }
		
		public static readonly Mipmap zero = new Mipmap(0);
		
		public uint index;
		public uint size;
	}
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct Slice {
		
		public Slice(in Face f) { face = f.index; faces = f.size; layer = 0; layers = 1; mipmap = 0; mipmaps = 1; }
		public Slice(in Layer l) { face = 0; faces = 1; layer = l.index; layers = l.size; mipmap = 0; mipmaps = 1; }
		public Slice(in Mipmap m) { face = 0; faces = 1; layer = 0; layers = 1; mipmap = m.index; mipmaps = m.size; }
		public Slice(in Layer l, in Face f) { face = f.index; faces = f.size; layer = l.index; layers = l.size; mipmap = 0; mipmaps = 1; }
		public Slice(in Face f, in Mipmap m) { face = f.index; faces = f.size; layer = 0; layers = 1; mipmap = m.index; mipmaps = m.size; }
		public Slice(in Layer l, in Mipmap m) { face = 0; faces = 1; layer = l.index; layers = l.size; mipmap = m.index; mipmaps = m.size; }
		public Slice(in Layer l, in Face f, in Mipmap m) { face = f.index; faces = f.size; layer = l.index; layers = l.size; mipmap = m.index; mipmaps = m.size; }
		public Slice(uint face, uint layer = 0, uint mipmap = 0) { this.face = face; faces = 1; this.layer = layer; layers = 1; this.mipmap = mipmap; mipmaps = 1; }
		
		public static implicit operator Slice(in Face f) { return new Slice(f); }
		public static implicit operator Slice(in Layer l) { return new Slice(l); }
		public static implicit operator Slice(in Mipmap m) { return new Slice(m); }
		
		public override string ToString() { return System.String.Format("({0} {1}) : ({2} {3}) : ({4} {5})", face, faces, layer, layers, mipmap, mipmaps); }
		
		public static readonly Slice zero = new Slice(0, 0, 0);
		
		public uint face;
		public uint faces;
		public uint layer;
		public uint layers;
		public uint mipmap;
		public uint mipmaps;
	}
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct Viewport {
		
		Viewport(float width, float height) { x = 0.0f; y = 0.0f; this.width = width; this.height = height; znear = 0.0f; zfar = 1.0f; }
		Viewport(float x, float y, float width, float height) { this.x = x; this.y = y; this.width = width; this.height = height; znear = 0.0f; zfar = 1.0f; }
		Viewport(float x, float y, float width, float height, float znear, float zfar) { this.x = x; this.y = y; this.width = width; this.height = height; this.znear = znear; this.zfar = zfar; }
		
		public float getLeft() { return x; }
		public float getBottom() { return y; }
		public float getRight() { return x + width; }
		public float getTop() { return y + height; }
		
		public override string ToString() { return System.String.Format("({0} {1}) : ({2} {3}) : ({4} {5})", x, y, width, height, znear, zfar); }
		
		public float x;
		public float y;
		public float width;
		public float height;
		public float znear;
		public float zfar;
	}
	
	[StructLayout(LayoutKind.Sequential)]
	public struct Scissor {
		
		Scissor(int width, int height) { x = 0; y = 0; this.width = width; this.height = height; }
		Scissor(int x, int y, int width, int height) { this.x = x; this.y = y; this.width = width; this.height = height; }
		
		public override string ToString() { return System.String.Format("({0} {1}) : ({2} {3})", x, y, width, height); }
		
		public int x;
		public int y;
		public int width;
		public int height;
	}
	
	/*
	 */
	public partial class Command {
		public void setUniform<Type>(uint index, Type data) {
			int size = Marshal.SizeOf(data);
			IntPtr ptr = tsCommand_getUniformData(self, index, (ulong)size);
			if(ptr == IntPtr.Zero) {
				ptr = Marshal.AllocHGlobal(size);
				Marshal.StructureToPtr(data, ptr, false);
				tsCommand_setUniformData(self, index, ptr, (ulong)size); Marshal.FreeHGlobal(ptr);
			} else {
				Marshal.StructureToPtr(data, ptr, false);
			}
		}
		public void setUniform<Type>(uint index, Type[] data) {
			int stride = Marshal.SizeOf(data[0]), size = stride * data.Length;
			IntPtr ptr = tsCommand_getUniformData(self, index, (ulong)size);
			if(ptr == IntPtr.Zero) {
				ptr = Marshal.AllocHGlobal(size);
				Base.getData(data, ptr, stride);
				tsCommand_setUniformData(self, index, ptr, (ulong)size);
				Marshal.FreeHGlobal(ptr);
			} else {
				Base.getData(data, ptr, stride);
			}
		}
		public void setStorage<Type>(uint index, Type data) {
			int size = Marshal.SizeOf(data);
			IntPtr ptr = tsCommand_getStorageData(self, index, (ulong)size);
			if(ptr == IntPtr.Zero) {
				ptr = Marshal.AllocHGlobal(size);
				Marshal.StructureToPtr(data, ptr, false);
				tsCommand_setStorageData(self, index, ptr, (ulong)size);
				Marshal.FreeHGlobal(ptr);
			} else {
				Marshal.StructureToPtr(data, ptr, false);
			}
		}
		public void setStorage<Type>(uint index, Type[] data) {
			int stride = Marshal.SizeOf(data[0]), size = stride * data.Length;
			IntPtr ptr = tsCommand_getStorageData(self, index, (ulong)size);
			if(ptr == IntPtr.Zero) {
				ptr = Marshal.AllocHGlobal(size);
				Base.getData(data, ptr, stride);
				tsCommand_setStorageData(self, index, ptr, (ulong)size);
				Marshal.FreeHGlobal(ptr);
			} else {
				Base.getData(data, ptr, stride);
			}
		}
		public void setVertices<Type>(uint index, Type[] data) {
			int stride = Marshal.SizeOf(data[0]), size = stride * data.Length;
			IntPtr ptr = tsCommand_getVertexData(self, index, (ulong)size);
			if(ptr == IntPtr.Zero) {
				ptr = Marshal.AllocHGlobal(size);
				Base.getData(data, ptr, stride);
				tsCommand_setVertexData(self, index, ptr, (ulong)size);
				Marshal.FreeHGlobal(ptr);
			} else {
				Base.getData(data, ptr, stride);
			}
		}
		public void setIndices(short[] data) {
			int size = 2 * data.Length;
			IntPtr ptr = tsCommand_getIndexData(self, Format.Ru16, (ulong)size);
			if(ptr == IntPtr.Zero) {
				ptr = Marshal.AllocHGlobal(size);
				Marshal.Copy(data, 0, ptr, data.Length);
				tsCommand_setIndexData(self, Format.Ru16, ptr, (ulong)size);
				Marshal.FreeHGlobal(ptr);
			} else {
				Marshal.Copy(data, 0, ptr, data.Length);
			}
		}
		public void setIndices(int[] data) {
			int size = 4 * data.Length;
			IntPtr ptr = tsCommand_getIndexData(self, Format.Ru32, (ulong)size);
			if(ptr == IntPtr.Zero) {
				ptr = Marshal.AllocHGlobal(size);
				Marshal.Copy(data, 0, ptr, data.Length);
				tsCommand_setIndexData(self, Format.Ru32, ptr, (ulong)size);
				Marshal.FreeHGlobal(ptr);
			} else {
				Marshal.Copy(data, 0, ptr, data.Length);
			}
		}
		public void setIndirect<Type>(Type data) {
			int size = Marshal.SizeOf(data);
			IntPtr ptr = tsCommand_getIndirectData(self, (ulong)size);
			if(ptr == IntPtr.Zero) {
				ptr = Marshal.AllocHGlobal(size);
				Marshal.StructureToPtr(data, ptr, false);
				tsCommand_setIndirectData(self, ptr, (ulong)size);
				Marshal.FreeHGlobal(ptr);
			} else {
				Marshal.StructureToPtr(data, ptr, false);
			}
		}
		public void setIndirect<Type>(Type[] data) {
			int stride = Marshal.SizeOf(data[0]), size = stride * data.Length;
			IntPtr ptr = tsCommand_getIndirectData(self, (ulong)size);
			if(ptr == IntPtr.Zero) {
				ptr = Marshal.AllocHGlobal(size);
				Base.getData(data, ptr, stride);
				tsCommand_setIndirectData(self, ptr, (ulong)size);
				Marshal.FreeHGlobal(ptr);
			} else {
				Base.getData(data, ptr, stride);
			}
		}
	}
	
	/*
	 */
	public partial class Compute {
		public void setUniform<Type>(uint index, Type data) {
			int size = Marshal.SizeOf(data);
			IntPtr ptr = tsCompute_getUniformData(self, index, (ulong)size);
			if(ptr == IntPtr.Zero) {
				ptr = Marshal.AllocHGlobal(size);
				Marshal.StructureToPtr(data, ptr, false);
				tsCompute_setUniformData(self, index, ptr, (ulong)size); Marshal.FreeHGlobal(ptr);
			} else {
				Marshal.StructureToPtr(data, ptr, false);
			}
		}
		public void setUniform<Type>(uint index, Type[] data) {
			int stride = Marshal.SizeOf(data[0]), size = stride * data.Length;
			IntPtr ptr = tsCompute_getUniformData(self, index, (ulong)size);
			if(ptr == IntPtr.Zero) {
				ptr = Marshal.AllocHGlobal(size);
				Base.getData(data, ptr, stride);
				tsCompute_setUniformData(self, index, ptr, (ulong)size);
				Marshal.FreeHGlobal(ptr);
			} else {
				Base.getData(data, ptr, stride);
			}
		}
		public void setStorage<Type>(uint index, Type data) {
			int size = Marshal.SizeOf(data);
			IntPtr ptr = tsCompute_getStorageData(self, index, (ulong)size);
			if(ptr == IntPtr.Zero) {
				ptr = Marshal.AllocHGlobal(size);
				Marshal.StructureToPtr(data, ptr, false);
				tsCompute_setStorageData(self, index, ptr, (ulong)size);
				Marshal.FreeHGlobal(ptr);
			} else {
				Marshal.StructureToPtr(data, ptr, false);
			}
		}
		public void setStorage<Type>(uint index, Type[] data) {
			int stride = Marshal.SizeOf(data[0]), size = stride * data.Length;
			IntPtr ptr = tsCompute_getStorageData(self, index, (ulong)size);
			if(ptr == IntPtr.Zero) {
				ptr = Marshal.AllocHGlobal(size);
				Base.getData(data, ptr, stride);
				tsCompute_setStorageData(self, index, ptr, (ulong)size);
				Marshal.FreeHGlobal(ptr);
			} else {
				Base.getData(data, ptr, stride);
			}
		}
		public void setIndirect<Type>(Type data) {
			int size = Marshal.SizeOf(data);
			IntPtr ptr = tsCompute_getIndirectData(self, (ulong)size);
			if(ptr == IntPtr.Zero) {
				ptr = Marshal.AllocHGlobal(size);
				Marshal.StructureToPtr(data, ptr, false);
				tsCompute_setIndirectData(self, ptr, (ulong)size);
				Marshal.FreeHGlobal(ptr);
			} else {
				Marshal.StructureToPtr(data, ptr, false);
			}
		}
		public void setIndirect<Type>(Type[] data) {
			int stride = Marshal.SizeOf(data[0]), size = stride * data.Length;
			IntPtr ptr = tsCompute_getIndirectData(self, (ulong)size);
			if(ptr == IntPtr.Zero) {
				ptr = Marshal.AllocHGlobal(size);
				Base.getData(data, ptr, stride);
				tsCompute_setIndirectData(self, ptr, (ulong)size);
				Marshal.FreeHGlobal(ptr);
			} else {
				Base.getData(data, ptr, stride);
			}
		}
	}
	
	/*****************************************************************************\
	 *
	 * Parallel
	 *
	\*****************************************************************************/
	
	/*
	 */
	[StructLayout(LayoutKind.Sequential)]
	public struct Tensor {
		
		public Tensor(uint width) { buffer = new IntPtr(); format = Format.Unknown; offset = 0; axis = 0; kernel = 2; stride = 1; padding = 0; dilation = 1; scale = 1.0f; bias = 0.0f; this.width = width; height = 1; depth = 1; layers = 1; }
		public Tensor(Buffer buffer, ulong offset = 0) { this.buffer = buffer.getSelfPtr(); format = Format.Unknown; this.offset = offset; axis = 0; kernel = 2; stride = 1; padding = 0; dilation = 1; scale = 1.0f; bias = 0.0f; width = 0; height = 1; depth = 1; layers = 1; }
		public Tensor(Buffer buffer, Format format, uint width, uint height = 1, uint depth = 1, uint layers = 1) { this.buffer = buffer.getSelfPtr(); this.format = format; offset = 0; axis = 0; kernel = 2; stride = 1; padding = 0; dilation = 1; scale = 1.0f; bias = 0.0f; this.width = width; this.height = height; this.depth = depth; this.layers = layers; }
		public Tensor(in Tensor tensor, uint width, uint height = 1, uint depth = 1, uint layers = 1) { buffer = tensor.buffer; format = tensor.format; offset = tensor.offset; axis = 0; kernel = 2; stride = 1; padding = 0; dilation = 1; scale = 1.0f; bias = 0.0f; this.width = width; this.height = height; this.depth = depth; this.layers = layers; }
		public Tensor(in Tensor tensor) { buffer = tensor.buffer; format = tensor.format; offset = tensor.offset; axis = tensor.axis; kernel = tensor.kernel; stride = tensor.stride; padding = tensor.padding; dilation = tensor.dilation; scale = tensor.scale; bias = tensor.bias; width = tensor.width; height = tensor.height; depth = tensor.depth; layers = tensor.layers; }
		
		public Tensor setAxis(uint axis) { Tensor ret = new Tensor(this); ret.axis = axis; return ret; }
		public Tensor setKernel(uint kernel) { Tensor ret = new Tensor(this); ret.kernel = kernel; return ret; }
		public Tensor setStride(uint stride) { Tensor ret = new Tensor(this); ret.stride = stride; return ret; }
		public Tensor setPadding(uint padding) { Tensor ret = new Tensor(this); ret.padding = padding; return ret; }
		public Tensor setDilation(uint dilation) { Tensor ret = new Tensor(this); ret.dilation = dilation; return ret; }
		
		public Tensor setScaleBias(float scale, float bias) { Tensor ret = new Tensor(this); ret.scale = scale; ret.bias = bias; return ret; }
		public Tensor setScale(float scale) { Tensor ret = new Tensor(this); ret.scale = scale; return ret; }
		public Tensor setBias(float bias) { Tensor ret = new Tensor(this); ret.bias = bias; return ret; }
		
		public override string ToString() { return System.String.Format("[{0}x{1}x{2}x{3}]", width, height, depth, layers); }
		
		public IntPtr buffer;
		public Format format;
		public ulong offset;
		public uint axis;
		public uint kernel;
		public uint stride;
		public uint padding;
		public uint dilation;
		public float scale;
		public float bias;
		public uint width;
		public uint height;
		public uint depth;
		public uint layers;
	}
	
} /* namespace Tellusim */

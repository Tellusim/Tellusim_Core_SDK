// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;

/*
 */
public class BaseGlobal {
	
	/// 8-bit integer constants
	public static final byte Mini8 = -127 - 1;
	public static final byte Maxi8 =  127;
	public static final byte Maxu8 = -1;
	
	/// 16-bit integer constants
	public static final short Mini16 = -32767 - 1;
	public static final short Maxi16 =  32767;
	public static final short Maxu16 = -1;
	
	/// 32-bit integer constants
	public static final int Mini32 = -2147483647 - 1;
	public static final int Maxi32 =  2147483647;
	public static final int Maxu32 = -1;
	
	/// 64-bit integer constants
	public static final long Mini64 = -9223372036854775807l - 1;
	public static final long Maxi64 =  9223372036854775807l;
	public static final long Maxu64 = -1;
	
	/// 16-bit floating point constants
	public static final float Minf16 = 5.96046448e-08f;
	public static final float Maxf16 = 65504.0f;
	
	/// 32-bit floating point constants
	public static final float Minf32 = 1.17549435e-38f;
	public static final float Maxf32 = 3.40282346e+38f;
	public static final float Pi = 3.141592653589793f;
	public static final float Pi2 = 6.283185307179586f;
	public static final float Pi05 = 1.570796326794897f;
	public static final float Sqrt2 = 1.4142135623730951f;
	public static final float Deg2Rad = 0.017453292519943f;
	public static final float Rad2Deg = 57.295779513082325f;
	
	/// 64-bit floating point constants
	public static final double Minf64 = 2.22507385850720138e-308;
	public static final double Maxf64 = 1.79769313486231571e+308;
	public static final double Pid = 3.141592653589793115997963468544;
	public static final double Pi2d = 6.283185307179586231995926937088;
	public static final double Pi05d = 1.570796326794896557998981734272;
	public static final double Sqrt2d = 1.414213562373095145474621858739;
	public static final double Deg2Radd = 0.017453292519943295474371680598;
	public static final double Rad2Degd = 57.295779513082322864647721871734;
	
	/// command line
	protected static String[] getArgs(String[] args) {
		String[] ret = new String[args.length + 1];
		for(int i = 0; i < args.length; i++) ret[i + 1] = args[i];
		ret[0] = "main";
		return ret;
	}
	
	/// load library
	public static void loadDebug() {
		loadLibrary("d");
	}
	public static void loadRelease() {
		loadLibrary("");
	}
	public static void loadLibrary(String postfix) {
		String arch = System.getProperty("os.arch");
		if(arch.equals("amd64")) System.loadLibrary("TellusimJNI_x64" + postfix);
		else if(arch.equals("aarch64")) System.loadLibrary("TellusimJNI_arm64" + postfix);
		else System.out.printf("Base::loadLibrary(): unknown arch \"%s\"\n", arch);
	}
	
	/// main class
	private static Class main_class;
	public static void setMain(Class clazz) {
		main_class = clazz;
	}
	public static Class getMain() {
		return main_class;
	}
}

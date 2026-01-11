// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.main;

import com.tellusim.*;

import android.os.Bundle;
import android.app.NativeActivity;

/*
 */
public class activity extends NativeActivity {
	
	/*
	 */
	static {
		
		// load JNI library
		Base.loadDebug();
		
		// Java entry point
		Base.setMain(main.class);
		
		// Kotlin entry point
		//Base.setMain(MainKt.class);
	}
	
	/*
	 */
	protected void onCreate(Bundle state) {
		super.onCreate(state);
	}
}

fn main() {
	
	println!("cargo:rustc-link-search=native=.");
	
	#[cfg(not(debug_assertions))]
	println!("cargo:rustc-link-lib=dylib=TellusimC_@ARCH@");
	
	#[cfg(debug_assertions)]
	println!("cargo:rustc-link-lib=dylib=TellusimC_@ARCH@d");
	
	#[cfg(target_os = "macos")]
	println!("cargo:rustc-link-arg=-Wl,-rpath,@loader_path/../../");
}

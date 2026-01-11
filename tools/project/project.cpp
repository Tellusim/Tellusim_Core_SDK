// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <TellusimApp.h>
#include <core/TellusimCore.h>
#include <core/TellusimSystem.h>
#include <core/TellusimDirectory.h>
#include <format/TellusimParser.h>
#include <platform/TellusimDevice.h>
#include <platform/TellusimWindow.h>
#include <interface/TellusimControls.h>

#include "Controls.h"

/*
 */
using namespace Tellusim;

/*
 */
using Arguments = Map<String, String>;
using Variables = Map<const char*, String>;

/*****************************************************************************\
 *
 * Utils
 *
\*****************************************************************************/

/*
 */
static void create_args(int32_t argc, char **argv, uint32_t index, Arguments &args) {
	
	// target platform
	String platform;
	const char *language = "cpp";
	for(int32_t i = index; i < argc; i++) {
		const char *s = argv[i];
		if(s[0] == '-') {
			while(*s == '-') s++;
			String command = String(s);
			if(command == "clear") break;
			else if(command == "csproj") language = "csharp";
			else if(command == "java") language = "java";
			else if(command == "cargo") language = "rust";
			else if(command == "swift") language = "swift";
			else if(command == "python" || command == "py") language = "python";
			else if(command == "javascript" || command == "js") language = "javascript";
			else if(command == "ipa") args.append(command);
			else if(command == "apk") args.append(command);
			else if(command == "platform" && i + 1 < argc) platform = String(argv[++i]);
		}
	}
	args.append(String("language"), String(language));
	if(platform == "ios" || platform == "tvos") args.append(String("ipa"));
	else if(platform == "and") args.append(String("apk"));
	
	// cpp version
	args.append(String("std"), String("11"));
	
	// target binary name
	args.append(String("target"), String("main"));
	
	// target architecture
	#if TS_X64
		args.append(String("arch"), String("x64"));
	#elif TS_ARM64
		args.append(String("arch"), String("arm64"));
	#endif
	
	// Visual Studio toolset version
	args.append(String("toolset"), String("v143"));
	
	// Visual Studio version
	String version = System::getEnvironment("VSVERSION");
	if(!version) version = "170";
	args.append(String("version"), "vs" + version);
	
	// Android SDK version
	args.append(String("minsdk"), String("33"));
}

/*
 */
static void print_args(const Arguments &args) {
	for(const auto &it : args) {
		const auto &arguments = it.data.split(" \n");
		if(arguments.size() > 1) {
			TS_LOGF(Message, "%s = \n", it.key.get());
			for(const auto &value : arguments) {
				TS_LOGF(Message, " %s\n", value.get());
			}
		} else {
			TS_LOGF(Message, "%s = %s\n", it.key.get(), it.data.get());
		}
	}
}

/*
 */
static String get_path(const char *path) {
	String ret = String(path) + "/";
	#if _WIN32
		ret = ret.replace("\\", "/");
	#endif
	return ret;
}

/*
 */
static String get_dirname(const String &name) {
	String ret = name.dirname();
	if(!ret) ret = "./";
	return ret;
}

/*
 */
static String get_target(const Arguments &args) {
	auto target_it = args.find("target");
	auto postfix_it = args.find("postfix");
	if(!target_it) return String::null;
	String postfix;
	if(postfix_it) postfix = postfix_it->data;
	String target = target_it->data.extension(nullptr);
	return target.replace("$(POSTFIX)", postfix.get());
}

/*
 */
static String get_root_path(const String &path) {
	String ret;
	while(path && ret.size() < 256) {
		String bin_path = (path + ret).pathname();
		if(bin_path.size() == 1 && bin_path[0] == '/') break;
		if(bin_path.size() == 3 && bin_path[1] == ':' && bin_path[2] == '/') break;
		bin_path += "bin/";
		if(File::isFile(bin_path + "ts_root.sh")) return ret;
		if(File::isFile(bin_path + "ts_root.bat")) return ret;
		ret += "../";
	}
	return String::null;
}

static String get_relative_path(const String &path, const String &name) {
	if(name) {
		if(name && name[0] == '/') return String::relname(name, path);
		if(name.size() > 1 && name[1] == ':') return String::relname(name, path);
		return String::relname(Directory::getCurrentDirectory() + "/" + name.dirname(), path);
	}
	return path;
}

static String get_root(const Arguments &args, const String &name = String::null, bool force = false) {
	auto root_it = args.find("root");
	if(root_it && !force) return root_it->data;
	
	// internal path
	String path = name;
	#if _WIN32
		if(path.size() > 1 && path[1] != ':') {
	#else
		if(path.size() > 0 && path[0] != '/' && path[0] != '~') {
	#endif
		path = (Directory::getCurrentDirectory() + "/" + path).pathname();
	}
	path = get_root_path(path.dirname());
	if(path) return path;
	
	// environment path
	String ret = System::getEnvironment("TSROOT");
	#if _WIN32
		ret = ret.replace('\\', '/');
	#endif
	if(ret && Directory::isDirectory(ret)) {
		path = ret + "/";
		return get_relative_path(path, name);
	}
	
	// binary path
	path = Directory::getBinaryDirectory() + "/";
	ret = get_root_path(path);
	if(ret) {
		path = (path + ret).pathname();
		return get_relative_path(path, name);
	}
	TS_LOG(Error, "get_root(): can't find Tellusim root directory\n");
	return String::null;
}

/*
 */
static String get_assets(const Arguments &args, const String &name) {
	auto assets_it = args.find("assets");
	if(!assets_it) return String::null;
	String ret;
	String path = get_dirname(name);
	for(const String &asset : assets_it->data.split(" \n")) {
		if(asset.contains("*")) {
			Directory directory;
			String prefix = asset.dirname();
			if(directory.open(path + prefix)) {
				for(const String &name : directory.getFiles()) {
					if(name.match(asset.get())) {
						ret += prefix + name;
						ret += " ";
					}
				}
			}
		} else {
			ret += asset;
			ret += " ";
		}
	}
	return ret;
}

/*
 */
static String get_hash(const Arguments &args) {
	Blob blob;
	for(const auto &it : args) {
		blob.puts(it.key);
		blob.puts(it.data);
	}
	blob.seek(0);
	return blob.getSHA1();
}

static String get_guid(const String &hash) {
	String guid;
	guid.append(hash.get(), 8); guid += '-';
	guid.append(hash.get() + 8, 4); guid += '-';
	guid.append(hash.get() + 12, 4); guid += '-';
	guid.append(hash.get() + 16, 4); guid += '-';
	guid.append(hash.get() + 20, 12);
	return guid;
}

static String get_uuid(const String &hash, uint32_t index) {
	String uuid = hash.substring(0, 18).upper();
	return String::format("6%s%04XA", uuid.get(), index);
}

/*
 */
static bool check_args(const Arguments &args, const InitializerList<const char*> &names) {
	for(const auto &name : names) {
		if(!args.find(name)) {
			TS_LOGF(Error, "check_args(): \"%s\" is not defined\n", name);
			return false;
		}
	}
	return true;
}

/*
 */
static bool save_file(const String &name, const uint8_t (*blob)[256]) {
	File file;
	TS_LOGF(Verbose, "Saving \"%s\" file\n", name.get());
	if(!file.open(name, "wb")) {
		TS_LOGF(Error, "save_file(): can't create \"%s\" file\n", name.get());
		return false;
	}
	Blob file_blob(blob);
	file.writeStream(file_blob);
	return true;
}

/*
 */
static bool save_template(const String &name, const uint8_t (*blob)[256], const Variables &vars) {
	String dest;
	Blob template_blob(blob);
	String src = template_blob.gets();
	TS_LOGF(Verbose, "Saving \"%s\" template\n", name.get());
	try {
		String token;
		const char *s = src.get();
		while(*s) {
			if(*s == '@' && Parser::isUpper(s[1])) {
				s += Parser::readRegion(s + 1, token, 0, '@') + 1;
				auto it = vars.find(token);
				if(it) dest += it->data;
				else {
					dest += String::tformat("@{0}@", token);
					TS_LOGF(Error, "save_template(): unknown variable \"%s\"\n", token.get());
				}
				if(*s == '@') s++;
				continue;
			}
			dest += *s++;
		}
	}
	catch(const String &error) {
		TS_LOGF(Error, "save_template(): %s\n", error.get());
		return false;
	}
	File file;
	if(!file.open(name, "wb")) {
		TS_LOGF(Error, "save_template(): can't create \"%s\" file\n", name.get());
		return false;
	}
	file.puts(dest);
	return true;
}

/*
 */
bool copy_files(const String &dest_prefix, const String &src_prefix, const char **dest_names, const char **src_names = nullptr) {
	uint32_t num_files = 0;
	if(!src_names) src_names = dest_names;
	for(uint32_t i = 0; dest_names[i]; i++) {
		String name = src_prefix + src_names[i];
		if(!File::isFile(name)) continue;
		TS_LOGF(Verbose, "Copying \"%s\" file\n", name.get());
		if(!Directory::copyFile(name, dest_prefix + dest_names[i], true)) {
			TS_LOGF(Error, "copy_files(): can't copy \"%s\" file\n", src_names[i]);
			return false;
		}
		num_files++;
	}
	if(num_files == 0) {
		TS_LOGF(Error, "copy_files(): can't copy \"%s\" files\n", src_prefix.get());
		return false;
	}
	return true;
}

/*****************************************************************************\
 *
 * Applications
 *
\*****************************************************************************/

/*
 */
static bool create_app(Arguments &args, Variables &vars, String &root, const String &path) {
	
	// root directory
	bool is_external = false;
	root = get_root(args, path);
	for(uint32_t i = 0; i < root.size(); i++) {
		if(root[i] == '/' || root[i] == '.') continue;
		is_external = true;
		break;
	}
	if(is_external) {
		root = get_root(args);
	}
	if(!root) {
		TS_LOG(Error, "create_app(): can't get root directory\n");
		return false;
	}
	
	// check application path
	if(!path || path.back() != '/') {
		TS_LOGF(Error, "create_app(): invalid app path \"%s\"\n", path.get());
		return false;
	}
	
	// application name
	String name;
	auto name_it = args.find("name");
	if(name_it) {
		name = name_it->data;
	} else {
		name = path.substring(0, path.size() - 1);
		name = name.basename();
		args.append(String("name"), name);
	}
	if(!name) {
		TS_LOGF(Error, "create_app(): can't create \"%s\" application\n", path.get());
		return false;
	}
	
	// check directory
	if(Directory::isDirectory(path) && !args.find("force")) {
		TS_LOGF(Error, "create_app(): \"%s\" path is already exists\n", path.get());
		return false;
	}
	
	// create application
	if(!Directory::createDirectory(path, true)) {
		TS_LOGF(Error, "create_app(): can't create \"%s\" directory\n", path.get());
		return false;
	}
	
	// get language
	String language = args["language"];
	
	// create dependencies
	if(language == "cpp") {
		
		// copy libraries
		if(is_external) {
			
			// create application
			if(!Directory::createDirectory(path + "bin", true)) {
				TS_LOGF(Error, "create_app(): can't create \"%s\" directory\n", path.get());
				return false;
			}
			
			// copy bin libraries
			const char *library_names[] = {
				"Tellusim_x64.dll", "Tellusim_x64d.dll",
				"Tellusim_arm64.dll", "Tellusim_arm64d.dll",
				"libTellusim_x64.so", "libTellusim_x64d.so",
				"libTellusim_arm64.so", "libTellusim_arm64d.so",
				"libTellusim_x64.dylib", "libTellusim_x64d.dylib",
				"libTellusim_arm64.dylib", "libTellusim_arm64d.dylib",
				nullptr,
			};
			if(!copy_files(path + "bin/", root + "bin/", library_names)) {
				TS_LOG(Error, "create_app(): can't copy libraries\n");
				return false;
			}
			
			// copy includes
			if(!Directory::copyDirectory(root + "include", path + "include", true)) {
				TS_LOG(Error, "create_app(): can't copy include directory\n");
				return false;
			}
			
			// copy libraries
			const char *library = "lib";
			auto platform_it = args.find("platform");
			if(args.find("ipa") && !platform_it) library = "lib/ios";
			if(args.find("ipa") && platform_it && platform_it->data == "ios") library = "lib/ios";
			if(args.find("ipa") && platform_it && platform_it->data == "tvos") library = "lib/tvos";
			if(args.find("apk")) library = "lib/android";
			if(platform_it && platform_it->data == "ems") library = "lib/emscripten";
			if(!Directory::copyDirectory(root + library, path + library, true)) {
				TS_LOG(Error, "create_app(): can't copy library directory\n");
				return false;
			}
			
			// root directory
			args.append(String("root"), String("./"));
			args.append(String("external"));
		}
		else {
			
			// root directory
			args.append(String("root"), root);
		}
	}
	else if(language == "csharp") {
		
		// local root
		root = get_root(args);
		
		// create application
		if(!Directory::createDirectory(path + "lib", true)) {
			TS_LOGF(Error, "create_app(): can't create \"%s\" directory\n", path.get());
			return false;
		}
		
		// copy engine libraries
		const char *library_names[] = {
			"Tellusim_x64.dll", "Tellusim_x64d.dll",
			"Tellusim_arm64.dll", "Tellusim_arm64d.dll",
			"libTellusim_x64.so", "libTellusim_x64d.so",
			"libTellusim_arm64.so", "libTellusim_arm64d.so",
			"libTellusim_x64.dylib", "libTellusim_x64d.dylib",
			"libTellusim_arm64.dylib", "libTellusim_arm64d.dylib",
			nullptr,
		};
		if(!copy_files(path + "lib/", root + "bin/", library_names)) {
			TS_LOG(Error, "create_app(): can't copy libraries\n");
			return false;
		}
		
		// copy c libraries
		const char *c_library_names[] = {
			"TellusimC_x64.dll", "TellusimC_x64d.dll",
			"TellusimC_arm64.dll", "TellusimC_arm64d.dll",
			"libTellusimC_x64.so", "libTellusimC_x64d.so",
			"libTellusimC_arm64.so", "libTellusimC_arm64d.so",
			"libTellusimC_x64.dylib", "libTellusimC_x64d.dylib",
			"libTellusimC_arm64.dylib", "libTellusimC_arm64d.dylib",
			nullptr,
		};
		if(!copy_files(path + "lib/", root + "plugins/binding/capi/", c_library_names)) {
			TS_LOG(Error, "create_app(): can't copy c libraries\n");
			return false;
		}
		
		// copy csharp libraries
		const char *csharp_library_names[] = {
			"TellusimCS.dll", "TellusimCSd.dll",
			"libTellusimCS.dll", "libTellusimCSd.dll",
			nullptr,
		};
		if(!copy_files(path + "lib/", root + "plugins/binding/csharp/", csharp_library_names)) {
			TS_LOG(Error, "create_app(): can't copy c# libraries\n");
			return false;
		}
	}
	else if(language == "java") {
		
		// local root
		root = get_root(args);
		
		// create application
		if(!Directory::createDirectory(path + "lib", true) ||
			!Directory::createDirectory(path + "src/main/java/com/main", true)) {
			TS_LOGF(Error, "create_app(): can't create \"%s\" directory\n", path.get());
			return false;
		}
		
		// android platform
		if(args.find("apk")) {
			
			// copy engine libraries
			const char *library_names[] = {
				"libTellusim_arm64.so", "libTellusim_arm64d.so",
				nullptr,
			};
			if(!copy_files(path + "lib/", root + "lib/android/arm64/", library_names)) {
				TS_LOG(Error, "create_app(): can't copy libraries\n");
				return false;
			}
			
			// copy jni libraries
			const char *jni_library_names[] = {
				"libTellusimJNI_arm64.so", "libTellusimJNI_arm64d.so",
				"tellusim.jar",
				nullptr,
			};
			if(!copy_files(path + "lib/", root + "plugins/binding/java/", jni_library_names)) {
				TS_LOG(Error, "create_app(): can't copy jni libraries\n");
				return false;
			}
		}
		// desktop platform
		else {
			
			// copy engine libraries
			const char *library_names[] = {
				"Tellusim_x64.dll", "Tellusim_x64d.dll",
				"Tellusim_arm64.dll", "Tellusim_arm64d.dll",
				"libTellusim_x64.so", "libTellusim_x64d.so",
				"libTellusim_arm64.so", "libTellusim_arm64d.so",
				"libTellusim_x64.dylib", "libTellusim_x64d.dylib",
				"libTellusim_arm64.dylib", "libTellusim_arm64d.dylib",
				nullptr,
			};
			if(!copy_files(path + "lib/", root + "bin/", library_names)) {
				TS_LOG(Error, "create_app(): can't copy libraries\n");
				return false;
			}
			
			// copy jni libraries
			const char *jni_library_names[] = {
				"TellusimJNI_x64.dll", "TellusimJNI_x64d.dll",
				"TellusimJNI_arm64.dll", "TellusimJNI_arm64d.dll",
				"libTellusimJNI_x64.so", "libTellusimJNI_x64d.so",
				"libTellusimJNI_arm64.so", "libTellusimJNI_arm64d.so",
				"libTellusimJNI_x64.dylib", "libTellusimJNI_x64d.dylib",
				"libTellusimJNI_arm64.dylib", "libTellusimJNI_arm64d.dylib",
				"tellusim.jar",
				nullptr,
			};
			if(!copy_files(path + "lib/", root + "plugins/binding/java/", jni_library_names)) {
				TS_LOG(Error, "create_app(): can't copy jni libraries\n");
				return false;
			}
		}
	}
	else if(language == "rust") {
		
		// local root
		root = get_root(args);
		
		// create application
		if(!Directory::createDirectory(path + "src", true) ||
			!Directory::createDirectory(path + "tellusim/src", true)) {
			TS_LOGF(Error, "create_app(): can't create \"%s\" directory\n", path.get());
			return false;
		}
		
		// copy engine libraries
		const char *library_names[] = {
			"Tellusim_x64.dll", "Tellusim_x64d.dll",
			"Tellusim_arm64.dll", "Tellusim_arm64d.dll",
			"libTellusim_x64.so", "libTellusim_x64d.so",
			"libTellusim_arm64.so", "libTellusim_arm64d.so",
			"libTellusim_x64.dylib", "libTellusim_x64d.dylib",
			"libTellusim_arm64.dylib", "libTellusim_arm64d.dylib",
			nullptr,
		};
		if(!copy_files(path, root + "bin/", library_names)) {
			TS_LOG(Error, "create_app(): can't copy libraries\n");
			return false;
		}
		
		// copy c libraries
		const char *c_library_names[] = {
			"TellusimC_x64.lib", "TellusimC_x64d.lib",
			"TellusimC_arm64.lib", "TellusimC_arm64d.lib",
			"TellusimC_x64.dll", "TellusimC_x64d.dll",
			"TellusimC_arm64.dll", "TellusimC_arm64d.dll",
			"libTellusimC_x64.so", "libTellusimC_x64d.so",
			"libTellusimC_arm64.so", "libTellusimC_arm64d.so",
			"libTellusimC_x64.dylib", "libTellusimC_x64d.dylib",
			"libTellusimC_arm64.dylib", "libTellusimC_arm64d.dylib",
			nullptr,
		};
		if(!copy_files(path, root + "plugins/binding/capi/", c_library_names)) {
			TS_LOG(Error, "create_app(): can't copy c libraries\n");
			return false;
		}
		
		// copy rust sources
		const char *source_names[] = {
			"TellusimRS.rs", "TellusimRSAPI.rs",
			"TellusimRSBase.rs", "TellusimRSMath.rs",
			nullptr,
		};
		const char *target_source_names[] = {
			"lib.rs", "TellusimRSAPI.rs",
			"TellusimRSBase.rs", "TellusimRSMath.rs",
			nullptr,
		};
		TS_STATIC_ASSERT(TS_COUNTOF(source_names) == TS_COUNTOF(target_source_names));
		if(!copy_files(path + "tellusim/src/", root + "plugins/binding/rust/source/", target_source_names, source_names)) {
			TS_LOG(Error, "create_app(): can't copy sources\n");
			return false;
		}
	}
	else if(language == "swift") {
		
		// platform name
		String platform;
		if(args.find("ipa")) platform = "ios";
		else platform = "macos";
		
		// get arguments
		String arch = args["arch"];
		arch = arch.replace("x64", "x86_64");
		
		// set variables
		vars.append("PLATFORM", platform);
		vars.append("ARCH", arch);
		
		// local root
		root = get_root(args);
		
		// framework path
		String framework_path = path + String::tformat("Tellusim.xcframework/{0}-{1}/", platform, arch);
		
		// create application
		if(!Directory::createDirectory(path + "Sources", true) ||
			!Directory::createDirectory(framework_path + "Tellusim.swiftmodule", true) ||
			!Directory::createDirectory(framework_path + "Headers/Tellusim.swiftmodule", true)) {
			TS_LOGF(Error, "create_app(): can't create \"%s\" directory\n", path.get());
			return false;
		}
		
		// ios platform
		if(args.find("ipa")) {
			
			// copy frameworks
			if(!Directory::copyDirectory(root + "plugins/binding/swift/TellusimObjC.framework", path + "TellusimObjC.framework", true) ||
				!Directory::copyDirectory(root + "plugins/binding/swift/TellusimObjCd.framework", path + "TellusimObjCd.framework", true)) {
				TS_LOG(Error, "create_app(): can't copy framework\n");
				return false;
			}
		}
		// desktop platform
		else {
			
			// copy engine libraries
			const char *library_names[] = {
				"libTellusim_x64.dylib", "libTellusim_x64d.dylib",
				"libTellusim_arm64.dylib", "libTellusim_arm64d.dylib",
				nullptr,
			};
			if(!copy_files(path, root + "bin/", library_names)) {
				TS_LOG(Error, "create_app(): can't copy libraries\n");
				return false;
			}
			
			// copy objc libraries
			const char *objc_library_names[] = {
				"libTellusimObjC_x64.dylib", "libTellusimObjC_x64d.dylib",
				"libTellusimObjC_arm64.dylib", "libTellusimObjC_arm64d.dylib",
				nullptr,
			};
			if(!copy_files(path, root + "plugins/binding/swift/", objc_library_names)) {
				TS_LOG(Error, "create_app(): can't copy objc libraries\n");
				return false;
			}
		}
		
		// copy objc headers
		const char *header_names[] = {
			"TellusimObjCAPI.h",
			"TellusimObjCBase.h",
			"TellusimObjCMath.h",
			nullptr,
		};
		if(!copy_files(framework_path + "Headers/", root + "plugins/binding/swift/include/", header_names)) {
			TS_LOG(Error, "create_app(): can't copy headers\n");
			return false;
		}
		
		// copy swift libraries
		String module_name = "Tellusim.swiftmodule/" + arch + ".swiftmodule";
		String interface_name = "Headers/Tellusim.swiftmodule/" + arch + ".swiftinterface";
		const char *swift_library_names[] = {
			"libTellusim.a",
			"Tellusim.swiftmodule",
			"Tellusim.swiftinterface",
			nullptr,
		};
		const char *target_library_names[] = {
			"libTellusim.a",
			module_name.get(),
			interface_name.get(),
			nullptr,
		};
		TS_STATIC_ASSERT(TS_COUNTOF(swift_library_names) == TS_COUNTOF(target_library_names));
		if(!copy_files(framework_path, root + "plugins/binding/swift/", target_library_names, swift_library_names)) {
			TS_LOG(Error, "create_app(): can't copy sources\n");
			return false;
		}
		
		// create info
		#include "templates/swift/info.blob"
		if(!save_template(path + "Tellusim.xcframework/Info.plist", info_blob_src, vars)) {
			TS_LOG(Error, "create_app(): can't save info template\n");
			return false;
		}
		
		// create module map
		#include "templates/swift/module.blob"
		if(!save_file(framework_path + "Headers/module.modulemap", module_blob_src)) {
			TS_LOG(Error, "create_app(): can't save module template\n");
			return false;
		}
	}
	else if(language == "python") {
		
		// local root
		root = get_root(args);
		
		// create application
		if(!Directory::createDirectory(path, true)) {
			TS_LOGF(Error, "create_app(): can't create \"%s\" directory\n", path.get());
			return false;
		}
		
		// copy engine libraries
		const char *library_names[] = {
			"Tellusim_x64.dll", "Tellusim_x64d.dll",
			"Tellusim_arm64.dll", "Tellusim_arm64d.dll",
			"libTellusim_x64.so", "libTellusim_x64d.so",
			"libTellusim_arm64.so", "libTellusim_arm64d.so",
			"libTellusim_x64.dylib", "libTellusim_x64d.dylib",
			"libTellusim_arm64.dylib", "libTellusim_arm64d.dylib",
			nullptr,
		};
		if(!copy_files(path, root + "bin/", library_names)) {
			TS_LOG(Error, "create_app(): can't copy libraries\n");
			return false;
		}
		
		// copy python libraries
		const char *python_library_names[] = {
			"TellusimPy_x64.dll", "TellusimPy_x64d.dll",
			"TellusimPy_arm64.dll", "TellusimPy_arm64d.dll",
			"libTellusimPy_x64.so", "libTellusimPy_x64d.so",
			"libTellusimPy_arm64.so", "libTellusimPy_arm64d.so",
			"libTellusimPy_x64.dylib", "libTellusimPy_x64d.dylib",
			"libTellusimPy_arm64.dylib", "libTellusimPy_arm64d.dylib",
			nullptr,
		};
		const char *target_library_names[] = {
			"tellusim.pyd", "tellusimd.pyd",
			"tellusim.pyd", "tellusimd.pyd",
			"tellusim.so", "tellusimd.so",
			"tellusim.so", "tellusimd.so",
			"tellusim.so", "tellusimd.so",
			"tellusim.so", "tellusimd.so",
			nullptr,
		};
		TS_STATIC_ASSERT(TS_COUNTOF(python_library_names) == TS_COUNTOF(target_library_names));
		if(!copy_files(path, root + "plugins/binding/python/", target_library_names, python_library_names)) {
			TS_LOG(Error, "create_app(): can't copy python libraries\n");
			return false;
		}
	}
	else if(language == "javascript") {
		
		// local root
		root = get_root(args);
		
		// create application
		if(!Directory::createDirectory(path, true)) {
			TS_LOGF(Error, "create_app(): can't create \"%s\" directory\n", path.get());
			return false;
		}
		
		// copy javascript libraries
		const char *library_names[] = {
			"tellusim.js", "tellusimd.js",
			"tellusim.wasm", "tellusimd.wasm",
			nullptr,
		};
		TS_STATIC_ASSERT(TS_COUNTOF(library_names) == TS_COUNTOF(library_names));
		if(!copy_files(path, root + "plugins/binding/javascript/", library_names)) {
			TS_LOG(Error, "create_app(): can't copy javascript libraries\n");
			return false;
		}
		
		// create server
		#if _WIN32
			#include "templates/javascript/main_bat.blob"
			String main_name = path + "main.bat";
			if(!save_file(main_name, main_bat_blob_src)) {
				TS_LOG(Error, "create_app(): can't save main template\n");
				return false;
			}
		#else
			#include "templates/javascript/main_sh.blob"
			String main_name = path + "main.sh";
			if(!save_file(main_name, main_sh_blob_src)) {
				TS_LOG(Error, "create_app(): can't save main template\n");
				return false;
			}
			Directory::setFileAttributes(main_name.get(), Directory::AttributeRead | Directory::AttributeWrite | Directory::AttributeExecute);
		#endif
	}
	else {
		TS_LOGF(Error, "create_app(): unknown language \"%s\"\n", language.get());
		return false;
	}
	
	// application variables
	vars.append("NAME", name);
	
	return true;
}

/*
 */
static bool create_core(Arguments &args, const String &app_path) {
	
	// create app
	String root;
	Variables vars;
	if(!create_app(args, vars, root, app_path)) {
		TS_LOG(Error, "create_core(): can't create app\n");
		return false;
	}
	
	// get language
	String language = args["language"];
	
	// create sources
	if(language == "cpp") {
		
		// create app template
		#include "templates/cpp/app_core.blob"
		String app_name = app_path + "main.cpp";
		if(!save_template(app_name, app_core_blob_src, vars)) {
			TS_LOG(Error, "create_core(): can't save app template\n");
			return false;
		}
		
		// application sources
		args.append(String("srcs"), String("main.cpp"));
	}
	else if(language == "csharp") {
		
		// create app template
		#include "templates/csharp/app_core.blob"
		String app_name = app_path + "main.cs";
		if(!save_template(app_name, app_core_blob_src, vars)) {
			TS_LOG(Error, "create_core(): can't save app template\n");
			return false;
		}
		
		// application sources
		args.append(String("srcs"), String("main.cs"));
	}
	else if(language == "java") {
		
		// create app template
		#include "templates/java/app_core.blob"
		String app_name = app_path + "src/main/java/com/main/Application.java";
		if(!save_template(app_name, app_core_blob_src, vars)) {
			TS_LOG(Error, "create_core(): can't save app template\n");
			return false;
		}
		
		// create main template
		#include "templates/java/app_main.blob"
		String main_name = app_path + "src/main/java/com/main/main.java";
		if(!save_template(main_name, app_main_blob_src, vars)) {
			TS_LOG(Error, "create_core(): can't save main template\n");
			return false;
		}
	}
	else if(language == "rust") {
		
		// create app template
		#include "templates/rust/app_core.blob"
		String app_name = app_path + "src/main.rs";
		if(!save_template(app_name, app_core_blob_src, vars)) {
			TS_LOG(Error, "create_core(): can't save app template\n");
			return false;
		}
	}
	else if(language == "swift") {
		
		// create app template
		#include "templates/swift/app_core.blob"
		String app_name = app_path + "Sources/main.swift";
		if(!save_template(app_name, app_core_blob_src, vars)) {
			TS_LOG(Error, "create_core(): can't save app template\n");
			return false;
		}
		
		// application sources
		args.append(String("srcs"), String("main.swift"));
	}
	else if(language == "python") {
		
		// create app template
		#include "templates/python/app_core.blob"
		String app_name = app_path + "main.py";
		if(!save_template(app_name, app_core_blob_src, vars)) {
			TS_LOG(Error, "create_core(): can't save app template\n");
			return false;
		}
		Directory::setFileAttributes(app_name.get(), Directory::AttributeRead | Directory::AttributeWrite | Directory::AttributeExecute);
	}
	else if(language == "javascript") {
		
		// create app template
		#include "templates/javascript/app_core.blob"
		String app_name = app_path + "main.js";
		if(!save_template(app_name, app_core_blob_src, vars)) {
			TS_LOG(Error, "create_core(): can't save app template\n");
			return false;
		}
		
		// create index template
		#include "templates/javascript/app_index.blob"
		String index_name = app_path + "index.html";
		if(!save_template(index_name, app_index_blob_src, vars)) {
			TS_LOG(Error, "create_core(): can't save index template\n");
			return false;
		}
		
		// create indexd template
		#include "templates/javascript/app_indexd.blob"
		String indexd_name = app_path + "indexd.html";
		if(!save_template(indexd_name, app_indexd_blob_src, vars)) {
			TS_LOG(Error, "create_core(): can't save indexd template\n");
			return false;
		}
	}
	else {
		TS_LOGF(Error, "create_core(): unknown language \"%s\"\n", language.get());
		return false;
	}
	
	return true;
}

/*
 */
static bool create_engine(Arguments &args, const String &app_path) {
	
	// create app
	String root;
	Variables vars;
	if(!create_app(args, vars, root, app_path)) {
		TS_LOG(Error, "create_engine(): can't create app\n");
		return false;
	}
	
	// get language
	String language = args["language"];
	
	// copy plugins
	if(language == "cpp" && args.find("external")) {
		
		// create plugins
		if(!Directory::createDirectory(app_path + "plugins/render/system/source", true) ||
			!Directory::createDirectory(app_path + "plugins/render/system/include", true)) {
			TS_LOGF(Error, "create_engine(): can't create \"%splugins/render/system\" directory\n", app_path.get());
			return false;
		}
		
		// copy plugins
		const char *plugin_names[] = {
			"source/TellusimRenderSystem.cpp",
			"include/TellusimRenderSystem.h",
			nullptr,
		};
		if(!copy_files(app_path + "plugins/render/system/", root + "plugins/render/system/", plugin_names)) {
			TS_LOG(Error, "create_engine(): can't copy plugins\n");
			return false;
		}
	}
	
	// create sources
	if(language == "cpp") {
		
		// create app template
		#include "templates/cpp/app_engine.blob"
		String app_name = app_path + "main.cpp";
		if(!save_template(app_name, app_engine_blob_src, vars)) {
			TS_LOG(Error, "create_engine(): can't save app template\n");
			return false;
		}
		
		// create application template
		#include "templates/cpp/app_engine_application.blob"
		String application_name = app_path + "Application.h";
		if(!save_template(application_name, app_engine_application_blob_src, vars)) {
			TS_LOG(Error, "create_engine(): can't save application template\n");
			return false;
		}
		
		// create plugins source template
		#include "templates/cpp/app_engine_plugins_cpp.blob"
		String plugins_source_name = app_path + "Plugins.cpp";
		if(!save_file(plugins_source_name, app_engine_plugins_cpp_blob_src)) {
			TS_LOG(Error, "create_engine(): can't save plugins source template\n");
			return false;
		}
		
		// create plugins header template
		#include "templates/cpp/app_engine_plugins_h.blob"
		String plugins_header_name = app_path + "Plugins.h";
		if(!save_file(plugins_header_name, app_engine_plugins_h_blob_src)) {
			TS_LOG(Error, "create_engine(): can't save plugins header template\n");
			return false;
		}
		
		// application sources
		args.append(String("srcs"), String("main.cpp Plugins.cpp"));
	}
	else if(language == "csharp") {
		
		// create app template
		#include "templates/csharp/app_engine.blob"
		String app_name = app_path + "main.cs";
		if(!save_template(app_name, app_engine_blob_src, vars)) {
			TS_LOG(Error, "create_engine(): can't save app template\n");
			return false;
		}
		
		// application sources
		args.append(String("srcs"), String("main.cs"));
	}
	else if(language == "java") {
		
		// create app template
		#include "templates/java/app_engine.blob"
		String app_name = app_path + "src/main/java/com/main/Application.java";
		if(!save_template(app_name, app_engine_blob_src, vars)) {
			TS_LOG(Error, "create_engine(): can't save app template\n");
			return false;
		}
		
		// create main template
		#include "templates/java/app_main.blob"
		String main_name = app_path + "src/main/java/com/main/main.java";
		if(!save_template(main_name, app_main_blob_src, vars)) {
			TS_LOG(Error, "create_engine(): can't save main template\n");
			return false;
		}
	}
	else if(language == "rust") {
		
		// create app template
		#include "templates/rust/app_engine.blob"
		String app_name = app_path + "src/main.rs";
		if(!save_template(app_name, app_engine_blob_src, vars)) {
			TS_LOG(Error, "create_engine(): can't save app template\n");
			return false;
		}
	}
	else if(language == "swift") {
		
		// create app template
		#include "templates/swift/app_engine.blob"
		String app_name = app_path + "Sources/main.swift";
		if(!save_template(app_name, app_engine_blob_src, vars)) {
			TS_LOG(Error, "create_engine(): can't save app template\n");
			return false;
		}
		
		// application sources
		args.append(String("srcs"), String("main.swift"));
	}
	else if(language == "python") {
		
		// create app template
		#include "templates/python/app_engine.blob"
		String app_name = app_path + "main.py";
		if(!save_template(app_name, app_engine_blob_src, vars)) {
			TS_LOG(Error, "create_engine(): can't save app template\n");
			return false;
		}
		Directory::setFileAttributes(app_name.get(), Directory::AttributeRead | Directory::AttributeWrite | Directory::AttributeExecute);
	}
	else {
		TS_LOGF(Error, "create_engine(): unknown language \"%s\"\n", language.get());
		return false;
	}
	
	// create scene file
	#include "templates/resources/app_engine_scene.blob"
	String scene_name = app_path + "scene.graphx";
	if(!save_file(scene_name, app_engine_scene_blob_src)) {
		TS_LOG(Error, "create_engine(): can't save scene template\n");
		return false;
	}
	
	// application assets
	args.append(String("assets"), String("scene.graphx"));
	
	return true;
}

/*
 */
static bool create_core_canvas(Arguments &args, const String &app_path) {
	
	// create app
	String root;
	Variables vars;
	if(!create_app(args, vars, root, app_path)) {
		TS_LOG(Error, "create_core_canvas(): can't create app\n");
		return false;
	}
	
	// get language
	String language = args["language"];
	
	// create sources
	if(language == "cpp") {
		
		// create app template
		#include "templates/cpp/app_core_canvas.blob"
		String app_name = app_path + "main.cpp";
		if(!save_template(app_name, app_core_canvas_blob_src, vars)) {
			TS_LOG(Error, "create_core_canvas(): can't save app template\n");
			return false;
		}
		
		// application sources
		args.append(String("srcs"), String("main.cpp"));
	}
	else if(language == "csharp") {
		
		// create app template
		#include "templates/csharp/app_core_canvas.blob"
		String app_name = app_path + "main.cs";
		if(!save_template(app_name, app_core_canvas_blob_src, vars)) {
			TS_LOG(Error, "create_core_canvas(): can't save app template\n");
			return false;
		}
		
		// application sources
		args.append(String("srcs"), String("main.cs"));
	}
	else if(language == "java") {
		
		// create app template
		#include "templates/java/app_core_canvas.blob"
		String app_name = app_path + "src/main/java/com/main/Application.java";
		if(!save_template(app_name, app_core_canvas_blob_src, vars)) {
			TS_LOG(Error, "create_core_canvas(): can't save app template\n");
			return false;
		}
		
		// create main template
		#include "templates/java/app_main.blob"
		String main_name = app_path + "src/main/java/com/main/main.java";
		if(!save_template(main_name, app_main_blob_src, vars)) {
			TS_LOG(Error, "create_core_canvas(): can't save main template\n");
			return false;
		}
	}
	else if(language == "rust") {
		
		// create app template
		#include "templates/rust/app_core_canvas.blob"
		String app_name = app_path + "src/main.rs";
		if(!save_template(app_name, app_core_canvas_blob_src, vars)) {
			TS_LOG(Error, "create_core_canvas(): can't save app template\n");
			return false;
		}
	}
	else if(language == "swift") {
		
		// create app template
		#include "templates/swift/app_core_canvas.blob"
		String app_name = app_path + "Sources/main.swift";
		if(!save_template(app_name, app_core_canvas_blob_src, vars)) {
			TS_LOG(Error, "create_core_canvas(): can't save app template\n");
			return false;
		}
		
		// application sources
		args.append(String("srcs"), String("main.swift"));
	}
	else if(language == "python") {
		
		// create app template
		#include "templates/python/app_core_canvas.blob"
		String app_name = app_path + "main.py";
		if(!save_template(app_name, app_core_canvas_blob_src, vars)) {
			TS_LOG(Error, "create_core_canvas(): can't save app template\n");
			return false;
		}
		Directory::setFileAttributes(app_name.get(), Directory::AttributeRead | Directory::AttributeWrite | Directory::AttributeExecute);
	}
	else if(language == "javascript") {
		
		// create app template
		#include "templates/javascript/app_core_canvas.blob"
		String app_name = app_path + "main.js";
		if(!save_template(app_name, app_core_canvas_blob_src, vars)) {
			TS_LOG(Error, "create_core_canvas(): can't save app template\n");
			return false;
		}
		
		// create index template
		#include "templates/javascript/app_index.blob"
		String index_name = app_path + "index.html";
		if(!save_template(index_name, app_index_blob_src, vars)) {
			TS_LOG(Error, "create_core_canvas(): can't save index template\n");
			return false;
		}
		
		// create indexd template
		#include "templates/javascript/app_indexd.blob"
		String indexd_name = app_path + "indexd.html";
		if(!save_template(indexd_name, app_indexd_blob_src, vars)) {
			TS_LOG(Error, "create_core_canvas(): can't save indexd template\n");
			return false;
		}
	}
	else {
		TS_LOGF(Error, "create_core_canvas(): unknown language \"%s\"\n", language.get());
		return false;
	}
	
	return true;
}

/*
 */
static bool create_core_compute(Arguments &args, const String &app_path) {
	
	// create app
	String root;
	Variables vars;
	if(!create_app(args, vars, root, app_path)) {
		TS_LOG(Error, "create_core_compute(): can't create app\n");
		return false;
	}
	
	// get language
	String language = args["language"];
	
	// create sources
	if(language == "cpp") {
		
		// create app template
		#include "templates/cpp/app_core_compute.blob"
		String app_name = app_path + "main.cpp";
		if(!save_template(app_name, app_core_compute_blob_src, vars)) {
			TS_LOG(Error, "create_core_compute(): can't save app template\n");
			return false;
		}
		
		// application sources
		args.append(String("srcs"), String("main.cpp"));
	}
	else if(language == "csharp") {
		
		// create app template
		#include "templates/csharp/app_core_compute.blob"
		String app_name = app_path + "main.cs";
		if(!save_template(app_name, app_core_compute_blob_src, vars)) {
			TS_LOG(Error, "create_core_compute(): can't save app template\n");
			return false;
		}
		
		// application sources
		args.append(String("srcs"), String("main.cs"));
	}
	else if(language == "java") {
		
		// create app template
		#include "templates/java/app_core_compute.blob"
		String app_name = app_path + "src/main/java/com/main/Application.java";
		if(!save_template(app_name, app_core_compute_blob_src, vars)) {
			TS_LOG(Error, "create_core_compute(): can't save app template\n");
			return false;
		}
		
		// create main template
		#include "templates/java/app_main.blob"
		String main_name = app_path + "src/main/java/com/main/main.java";
		if(!save_template(main_name, app_main_blob_src, vars)) {
			TS_LOG(Error, "create_core_compute(): can't save main template\n");
			return false;
		}
	}
	else if(language == "rust") {
		
		// create app template
		#include "templates/rust/app_core_compute.blob"
		String app_name = app_path + "src/main.rs";
		if(!save_template(app_name, app_core_compute_blob_src, vars)) {
			TS_LOG(Error, "create_core_compute(): can't save app template\n");
			return false;
		}
	}
	else if(language == "swift") {
		
		// create app template
		#include "templates/swift/app_core_compute.blob"
		String app_name = app_path + "Sources/main.swift";
		if(!save_template(app_name, app_core_compute_blob_src, vars)) {
			TS_LOG(Error, "create_core_compute(): can't save app template\n");
			return false;
		}
		
		// application sources
		args.append(String("srcs"), String("main.swift"));
	}
	else if(language == "python") {
		
		// create app template
		#include "templates/python/app_core_compute.blob"
		String app_name = app_path + "main.py";
		if(!save_template(app_name, app_core_compute_blob_src, vars)) {
			TS_LOG(Error, "create_core_compute(): can't save app template\n");
			return false;
		}
		Directory::setFileAttributes(app_name.get(), Directory::AttributeRead | Directory::AttributeWrite | Directory::AttributeExecute);
	}
	else if(language == "javascript") {
		
		// create app template
		#include "templates/javascript/app_core_compute.blob"
		String app_name = app_path + "main.js";
		if(!save_template(app_name, app_core_compute_blob_src, vars)) {
			TS_LOG(Error, "create_core_compute(): can't save app template\n");
			return false;
		}
		
		// create index template
		#include "templates/javascript/app_index.blob"
		String index_name = app_path + "index.html";
		if(!save_template(index_name, app_index_blob_src, vars)) {
			TS_LOG(Error, "create_core_compute(): can't save index template\n");
			return false;
		}
		
		// create indexd template
		#include "templates/javascript/app_indexd.blob"
		String indexd_name = app_path + "indexd.html";
		if(!save_template(indexd_name, app_indexd_blob_src, vars)) {
			TS_LOG(Error, "create_core_compute(): can't save indexd template\n");
			return false;
		}
	}
	else {
		TS_LOGF(Error, "create_core_compute(): unknown language \"%s\"\n", language.get());
		return false;
	}
	
	// create shader file
	#include "templates/resources/app_core_compute.blob"
	String scene_name = app_path + "main.shader";
	if(!save_file(scene_name, app_core_compute_blob_src)) {
		TS_LOG(Error, "create_core_compute(): can't save shader file\n");
		return false;
	}
	
	// application assets
	args.append(String("assets"), String("main.shader"));
	
	return true;
}

/*
 */
static bool create_core_fragment(Arguments &args, const String &app_path) {
	
	// create app
	String root;
	Variables vars;
	if(!create_app(args, vars, root, app_path)) {
		TS_LOG(Error, "create_core_fragment(): can't create app\n");
		return false;
	}
	
	// get language
	String language = args["language"];
	
	// create sources
	if(language == "cpp") {
		
		// create app template
		#include "templates/cpp/app_core_fragment.blob"
		String app_name = app_path + "main.cpp";
		if(!save_template(app_name, app_core_fragment_blob_src, vars)) {
			TS_LOG(Error, "create_core_fragment(): can't save app template\n");
			return false;
		}
		
		// application sources
		args.append(String("srcs"), String("main.cpp"));
	}
	else if(language == "csharp") {
		
		// create app template
		#include "templates/csharp/app_core_fragment.blob"
		String app_name = app_path + "main.cs";
		if(!save_template(app_name, app_core_fragment_blob_src, vars)) {
			TS_LOG(Error, "create_core_fragment(): can't save app template\n");
			return false;
		}
		
		// application sources
		args.append(String("srcs"), String("main.cs"));
	}
	else if(language == "java") {
		
		// create app template
		#include "templates/java/app_core_fragment.blob"
		String app_name = app_path + "src/main/java/com/main/Application.java";
		if(!save_template(app_name, app_core_fragment_blob_src, vars)) {
			TS_LOG(Error, "create_core_fragment(): can't save app template\n");
			return false;
		}
		
		// create main template
		#include "templates/java/app_main.blob"
		String main_name = app_path + "src/main/java/com/main/main.java";
		if(!save_template(main_name, app_main_blob_src, vars)) {
			TS_LOG(Error, "create_core_fragment(): can't save main template\n");
			return false;
		}
	}
	else if(language == "rust") {
		
		// create app template
		#include "templates/rust/app_core_fragment.blob"
		String app_name = app_path + "src/main.rs";
		if(!save_template(app_name, app_core_fragment_blob_src, vars)) {
			TS_LOG(Error, "create_core_fragment(): can't save app template\n");
			return false;
		}
	}
	else if(language == "swift") {
		
		// create app template
		#include "templates/swift/app_core_fragment.blob"
		String app_name = app_path + "Sources/main.swift";
		if(!save_template(app_name, app_core_fragment_blob_src, vars)) {
			TS_LOG(Error, "create_core_fragment(): can't save app template\n");
			return false;
		}
		
		// application sources
		args.append(String("srcs"), String("main.swift"));
	}
	else if(language == "python") {
		
		// create app template
		#include "templates/python/app_core_fragment.blob"
		String app_name = app_path + "main.py";
		if(!save_template(app_name, app_core_fragment_blob_src, vars)) {
			TS_LOG(Error, "create_core_fragment(): can't save app template\n");
			return false;
		}
		Directory::setFileAttributes(app_name.get(), Directory::AttributeRead | Directory::AttributeWrite | Directory::AttributeExecute);
	}
	else if(language == "javascript") {
		
		// create app template
		#include "templates/javascript/app_core_fragment.blob"
		String app_name = app_path + "main.js";
		if(!save_template(app_name, app_core_fragment_blob_src, vars)) {
			TS_LOG(Error, "create_core_fragment(): can't save app template\n");
			return false;
		}
		
		// create index template
		#include "templates/javascript/app_index.blob"
		String index_name = app_path + "index.html";
		if(!save_template(index_name, app_index_blob_src, vars)) {
			TS_LOG(Error, "create_core_fragment(): can't save index template\n");
			return false;
		}
		
		// create indexd template
		#include "templates/javascript/app_indexd.blob"
		String indexd_name = app_path + "indexd.html";
		if(!save_template(indexd_name, app_indexd_blob_src, vars)) {
			TS_LOG(Error, "create_core_fragment(): can't save indexd template\n");
			return false;
		}
	}
	else {
		TS_LOGF(Error, "create_core_fragment(): unknown language \"%s\"\n", language.get());
		return false;
	}
	
	// create shader file
	#include "templates/resources/app_core_fragment.blob"
	String scene_name = app_path + "main.shader";
	if(!save_file(scene_name, app_core_fragment_blob_src)) {
		TS_LOG(Error, "create_core_fragment(): can't save shader file\n");
		return false;
	}
	
	// application assets
	args.append(String("assets"), String("main.shader"));
	
	return true;
}

/*****************************************************************************\
 *
 * Makefile
 *
\*****************************************************************************/

/*
 */
static const char *parse_argument(const String &argument, const Arguments &args) {
	if(argument.begins("$(shell grep")) {
		return "";
	}
	#if _LINUX
		if(argument == "$(shell uname -s)") {
			return "Linux";
		}
		if(argument == "$(shell uname -m)") {
			#if TS_X64
				return "x86_64";
			#elif TS_ARM64
				return "aarch64";
			#endif
		}
	#elif _MACOS
		if(argument == "$(shell uname -s)") {
			return "Darwin";
		}
		if(argument == "$(shell uname -m)") {
			#if TS_ARM64
				return "arm64";
			#endif
		}
	#elif _WIN32
		if(argument == "$(ARCH)") {
			#if TS_ARM64
				return "arm64";
			#endif
		}
	#endif
	return argument.get();
}

/*
 */
static bool parse_expression(const String &name, const char *s, const Arguments &args) {
	String token;
	String argument_0;
	String argument_1;
	if(name == "ifeq" || name == "ifneq") {
		s += Parser::readString(s, argument_0);
		s += Parser::readString(s, argument_1);
		argument_0 = parse_argument(argument_0, args);
		argument_1 = parse_argument(argument_1, args);
		if(name == "ifeq") return (argument_0 == argument_1);
		if(name == "ifneq") return (argument_0 != argument_1);
	}
	else if(name == "!if" || name == "!elseif") {
		if(*s == '"') {
			s += Parser::readString(s, argument_0);
			s += Parser::readToken(s, token);
			s += Parser::readString(s, argument_1);
			argument_0 = parse_argument(argument_0, args);
			argument_1 = parse_argument(argument_1, args);
			if(token == "==") return (argument_0 == argument_1);
			if(token == "!=") return (argument_0 != argument_1);
		}
	}
	else if(name == "ifdef" || name == "!ifdef") {
		s += Parser::readToken(s, token);
		return (bool)args.find(token.lower());
	}
	else if(name == "ifndef" || name == "!ifndef") {
		s += Parser::readToken(s, token);
		return !args.find(token.lower());
	}
	return false;
}

/*
 */
static bool load_makefile(Arguments &args, const String &name) {
	
	// load file
	Source source;
	if(!source.open(name)) {
		TS_LOGF(Error, "load_makefile(): can't open \"%s\" file\n", name.get());
		return false;
	}
	String src = source.gets();
	source.close();
	
	// parse file
	try {
		
		String name;
		String value;
		String token;
		
		Array<bool> stack;
		Array<uint32_t> counter;
		bool is_else = false;
		
		const char *s = src.get();
		
		while(*s) {
			s += Parser::readToken(s, name, "=:?+");
			if(name.begins("#")) {
				s -= name.size();
				s += Parser::skipLine(s);
			}
			else if(name.begins("if") || name.begins("!if") || name.begins("!elseif")) {
				if(name.begins("!elseif")) {
					if(is_else || !stack) Parser::error("else without if\n");
					stack.back() = !stack.back();
					is_else = true;
				}
				s += Parser::readLine(s, value);
				stack.append(parse_expression(name, value.get(), args));
				if(is_else) counter.back()++;
				else counter.append(1);
				is_else = false;
			}
			else if(name.begins("endif") || name.begins("!endif")) {
				if(!stack) Parser::error("stack underflow\n");
				while(counter.back()--) stack.removeBack();
				counter.removeBack();
				is_else = false;
			}
			else if(name.begins("else") || name.begins("!else")) {
				if(!stack) Parser::error("else without if\n");
				stack.back() = !stack.back();
				is_else = true;
			}
			else if(stack.find(false)) {
				s += Parser::skipLine(s, true);
			}
			else if(name == "include" || name == "-include" || name == "!include") {
				auto it = args.find(name);
				s += Parser::readToken(s, value);
				if(it) it->data += " " + value;
				else args.append(name, value);
			}
			else if(name && name.back() == ':') {
				name.removeBack();
				auto it = args.append(name);
				s += Parser::readLine(s, value);
				if(value) it->data += value;
				while(*s == '\n' && (s[1] == ' ' || s[1] == '\t')) {
					s += Parser::readLine(s, value);
					if(value) it->data += "\n" + value;
				}
			}
			else if(name) {
				s += Parser::skipSpaces(s);
				if(*s == ':') {
					s += 1;
					name = name.lower();
					s += Parser::readLine(s, value);
					auto it = args.append(name, value);
					while(*s == '\n' || *s == '\r') s++;
					while(*s == ' ' || *s == '\t') {
						s += Parser::readLine(s, value);
						while(*s == '\n' || *s == '\r') s++;
						it->data += "\n" + value;
					}
				} else if(*s == '=' || (s[1] == '=' && (*s == ':' || *s == '?'))) {
					s += (*s == '=') ? 1 : 2;
					name = name.lower();
					auto it = args.find(name);
					s += Parser::readLine(s, value, true);
					value = value.replace('\n', ' ').replace('\t', ' ');
					value = value.replace(String::tformat("$({0})", name.upper()), (it) ? it->data : String::null);
					args.append(name, value);
				} else if(*s == '+' && s[1] == '=') {
					s += 2;
					name = name.lower();
					auto it = args.find(name);
					s += Parser::readLine(s, value, true);
					value = value.replace('\n', ' ').replace('\t', ' ');
					if(it) it->data += " " + value;
					else args.append(name, value);
				} else if(name[0] == '$' || name[0] == '!') {
					s += Parser::skipLine(s);
				} else {
					Parser::error("unknown token \"%s\"\n", name.get());
				}
			}
		}
		
		// check stack
		if(stack || counter || is_else) Parser::error("invalid branch\n");
	}
	catch(const String &error) {
		TS_LOGF(Error, "load_makefile(): %s: %s", name.get(), error.get());
		return false;
	}
	
	return true;
}

/*****************************************************************************\
 *
 * CMake
 *
\*****************************************************************************/

/*
 */
static void create_cmake_vars(Variables &vars, const Arguments &args, const String &root, const String &name) {
	
	// get arguments
	String arch = args["arch"];
	String version = args["version"];
	
	// set variables
	vars.append("ARCH", arch);
	
	// local path
	String include_path = String::tformat("\n\t{0}include\n\t{0}plugins\n\t{0}samples", root);
	String library_path_windows = String::tformat("\n\t\t{0}lib/windows/{2}{1}", root, arch, version);
	String library_path_linux = String::tformat("\n\t\t{0}lib/linux/{1}", root, arch);
	String library_path_macos = String::tformat("\n\t\t{0}lib/macos/{1}", root, arch);
	
	// extern path
	String path = get_dirname(name);
	if(Directory::isDirectory(path + "extern")) {
		include_path += "\n\textern";
		if(Directory::isDirectory(path + "extern/include")) include_path += "\n\textern/include";
		if(Directory::isDirectory(path + "extern/lib/windows/" + arch)) library_path_windows += "\n\t\textern/lib/windows/" + arch;
		if(Directory::isDirectory(path + "extern/lib/linux/" + arch)) library_path_linux += "\n\t\textern/lib/linux/" + arch;
		if(Directory::isDirectory(path + "extern/lib/macos/" + arch)) library_path_macos += "\n\t\textern/lib/macos/" + arch;
	}
	
	// compilation flags
	String options_windows;
	String options_linux;
	String options_macos;
	auto flags_it = args.find("flags");
	if(flags_it) {
		for(const String &flag : flags_it->data.replace("\\\"", "").replace("\\", "/").split(" ")) {
			if(flag.begins("/I") || flag.begins("-I")) {
				include_path += String::tformat("\n\t{0}", flag.get() + 2).replace("$(TSROOT)/", root.get());
			}
			if(flag.begins("/D")) {
				if(options_windows) options_windows += " ";
				options_windows += flag;
			}
			if(flag.begins("-D")) {
				if(options_linux) options_linux += " ";
				if(options_macos) options_macos += " ";
				options_linux += flag;
				options_macos += flag;
			}
			if(flag == "-ObjC++" || flag == "-fobjc-arc") {
				if(options_macos) options_macos += " ";
				options_macos += flag;
			}
		}
	}
	if(options_windows) options_windows = String::tformat("\n\tadd_compile_options({0})", options_windows);
	if(options_linux) options_linux = String::tformat("\n\tadd_compile_options({0})", options_linux);
	if(options_macos) options_macos = String::tformat("\n\tadd_compile_options({0})", options_macos);
	
	// libraries path
	auto lib_it = args.find("lib");
	if(lib_it) {
		for(const String &lib : lib_it->data.replace("\\", "/").split(";")) {
			library_path_windows += String::tformat("\n\t\t{0}", lib).replace("$(TSROOT)/", root.get()).replace("$(ARCH)", arch.get());
		}
	}
	
	// linker flags
	String link_library_windows;
	String link_library_linux;
	String link_library_macos;
	auto libs_it = args.find("libs");
	if(libs_it) {
		bool is_framework = false;
		for(const String &lib : libs_it->data.split(" ")) {
			if(lib.begins("-l")) {
				link_library_linux += String::tformat(" {0}", lib.get() + 2).replace("$(ARCH)", arch.get());
				link_library_macos += String::tformat(" {0}", lib.get() + 2).replace("$(ARCH)", arch.get());
			}
			if(lib.begins("-L")) {
				library_path_linux += String::tformat("\n\t\t{0}", lib.get() + 2).replace("$(TSROOT)/", root.get()).replace("$(ARCH)", arch.get());
				library_path_macos += String::tformat("\n\t\t{0}", lib.get() + 2).replace("$(TSROOT)/", root.get()).replace("$(ARCH)", arch.get());
			}
			if(lib.begins("-framework")) {
				is_framework = true;
			} else if(is_framework) {
				link_library_macos += String::tformat(" \"-framework {0}\"", lib);
				is_framework = false;
			}
		}
	}
	auto ldflags_it = args.find("ldflags");
	if(ldflags_it) {
		for(const String &flag : ldflags_it->data.split(" ")) {
			if(flag.extension() == "lib") link_library_windows += String::tformat(" {0}", flag.extension(nullptr));
		}
	}
	
	// language standard
	String std = args["std"];
	auto cflags_it = args.find("cflags");
	if(cflags_it) {
		for(const String &flag : cflags_it->data.split(" ")) {
			if(flag.contains("c++14")) std = "14";
			if(flag.contains("c++17")) std = "17";
			if(flag.contains("c++20")) std = "20";
		}
	}
	
	vars.append("OPTIONS_WINDOWS", options_windows);
	vars.append("OPTIONS_LINUX", options_linux);
	vars.append("OPTIONS_MACOS", options_macos);
	vars.append("INCLUDE_PATH", include_path);
	vars.append("LIBRARY_PATH_WINDOWS", library_path_windows);
	vars.append("LIBRARY_PATH_LINUX", library_path_linux);
	vars.append("LIBRARY_PATH_MACOS", library_path_macos);
	vars.append("LINK_LIBRARY_WINDOWS", link_library_windows);
	vars.append("LINK_LIBRARY_LINUX", link_library_linux);
	vars.append("LINK_LIBRARY_MACOS", link_library_macos);
	vars.append("STD", std);
}

/*
 */
static bool create_cmake(const Arguments &args, const String &cmake_name) {
	
	// check arguments
	if(!check_args(args, { "language", "std", "name", "target", "arch", "version", "srcs" })) return false;
	
	// root directory
	String root = get_root(args, cmake_name);
	if(!root) {
		TS_LOG(Error, "create_cmake(): can't get root directory\n");
		return false;
	}
	
	// get arguments
	String name = args["name"];
	String srcs = args["srcs"];
	String target = get_target(args);
	
	// cmake variables
	Variables vars;
	vars.append("NAME", name);
	vars.append("TARGET", target);
	create_cmake_vars(vars, args, root, cmake_name);
	
	// sources
	String sources;
	for(const String &src : srcs.split(" \n")) {
		sources += "\n\t" + src;
	}
	vars.append("SOURCES", sources);
	
	// project template
	#include "templates/cmake.blob"
	if(!save_template(cmake_name, cmake_blob_src, vars)) {
		TS_LOG(Error, "create_cmake(): can't save project template\n");
		return false;
	}
	
	return true;
}

/*****************************************************************************\
 *
 * Makefile
 *
\*****************************************************************************/

/*
 */
static bool create_makefile(const Arguments &args, const String &makefile_name) {
	
	// check arguments
	if(!check_args(args, { "language", "std", "target", "arch", "version", "srcs" })) return false;
	
	// root directory
	String root = get_root(args, makefile_name);
	if(!root) {
		TS_LOG(Error, "create_makefile(): can't get root directory\n");
		return false;
	}
	
	// get arguments
	String std = args["std"];
	String arch = args["arch"];
	String srcs = args["srcs"];
	String version = args["version"];
	String target = get_target(args);
	
	// makefile variables
	Variables vars;
	vars.append("STD", std);
	vars.append("ARCH", arch);
	vars.append("ROOT", root);
	vars.append("TARGET", target);
	vars.append("VERSION", version);
	
	// sources
	String sources;
	for(const String &src : srcs.split(" \n")) {
		if(sources) sources += " ";
		sources += src;
	}
	vars.append("SOURCES", sources);
	
	// compilation flags
	String cflags;
	String path = get_dirname(makefile_name);
	if(Directory::isDirectory(path + "extern")) {
		cflags += " -Iextern";
		if(Directory::isDirectory(path + "extern/include")) cflags += " -Iextern/include";
	}
	vars.append("CFLAGS", cflags);
	
	// linker flags
	String ldflags;
	auto libs_it = args.find("libs");
	if(libs_it) ldflags = libs_it->data;
	vars.append("LDFLAGS", ldflags);
	
	// platform type
	String platform = makefile_name.extension();
	
	// assets
	if(platform == "and" || platform == "ios" || platform == "tvos" || platform == "ems") {
		String assets;
		for(const String &asset : get_assets(args, makefile_name).split(" \n")) {
			if(assets) assets += " ";
			assets += asset;
		}
		#if _WIN32
			assets = assets.replace("/", "\\");
		#endif
		vars.append("ASSETS", assets);
	}
	
	// android platform
	if(platform == "and") {
		
		// check arguments
		if(!check_args(args, { "apk", "minsdk" })) return false;
		
		// get arguments
		String apk = args["apk"];
		String minsdk = args["minsdk"];
		
		// makefile variables
		vars.append("APK", apk);
		vars.append("MINSDK", minsdk);
		
		// project template
		#include "templates/makefile_and.blob"
		if(!save_template(makefile_name, makefile_and_blob_src, vars)) {
			TS_LOG(Error, "create_makefile(): can't save project template\n");
			return false;
		}
		
		// copy binaries
		if(args.find("external")) {
			const char *binary_names[] = {
				"ts_apk.sh",
				"ts_echo.sh",
				"ts_apk.keystore",
				nullptr,
			};
			String root = get_root(args, String::null, true);
			if(!copy_files(path + "bin/", root + "bin/", binary_names)) {
				TS_LOG(Error, "create_makefile(): can't copy binaries\n");
				return false;
			}
		}
	}
	// ios/tvos platform
	else if(platform == "ios" || platform == "tvos") {
		
		// check arguments
		if(!check_args(args, { "ipa" })) return false;
		
		// get arguments
		String ipa = args["ipa"];
		
		// makefile variables
		vars.append("IPA", ipa);
		
		// project template
		if(platform == "ios") {
			#include "templates/makefile_ios.blob"
			if(!save_template(makefile_name, makefile_ios_blob_src, vars)) {
				TS_LOG(Error, "create_makefile(): can't save project template\n");
				return false;
			}
		} else if(platform == "tvos") {
			#include "templates/makefile_tvos.blob"
			if(!save_template(makefile_name, makefile_tvos_blob_src, vars)) {
				TS_LOG(Error, "create_makefile(): can't save project template\n");
				return false;
			}
		}
		
		// copy binaries
		if(args.find("external")) {
			const char *binary_names[] = {
				"ts_ipa.sh",
				"ts_echo.sh",
				"ts_imaged",
				nullptr,
			};
			String root = get_root(args, String::null, true);
			if(!copy_files(path + "bin/", root + "bin/", binary_names)) {
				TS_LOG(Error, "create_makefile(): can't copy binaries\n");
				return false;
			}
		}
	}
	// emscripten platform
	else if(platform == "ems") {
		
		// project template
		#include "templates/makefile_ems.blob"
		if(!save_template(makefile_name, makefile_ems_blob_src, vars)) {
			TS_LOG(Error, "create_makefile(): can't save project template\n");
			return false;
		}
		
		// application page
		#include "templates/resources/app_page.blob"
		String page_name = path + "tellusim.html";
		if(!save_file(page_name, app_page_blob_src)) {
			TS_LOG(Error, "create_makefile(): can't save page file\n");
			return false;
		}
	}
	// windows platform
	else if(platform == "win") {
		
		// root directory
		root = root.replace("/", "\\");
		if(root && root.back() == '\\') root.removeBack();
		vars.append("ROOT", root);
		
		// project template
		#include "templates/makefile_win.blob"
		if(!save_template(makefile_name, makefile_win_blob_src, vars)) {
			TS_LOG(Error, "create_makefile(): can't save project template\n");
			return false;
		}
		
		// application resource
		#include "templates/resources/app_resource.blob"
		String resource_name = path + "tellusim.rc";
		if(!save_file(resource_name, app_resource_blob_src)) {
			TS_LOG(Error, "create_makefile(): can't save resource file\n");
			return false;
		}
		
		// application icon
		#include "templates/resources/app_icon.blob"
		String icon_name = path + "tellusim.ico";
		if(!save_file(icon_name, app_icon_blob_src)) {
			TS_LOG(Error, "create_makefile(): can't save icon file\n");
			return false;
		}
		
		// copy binaries
		if(args.find("external")) {
			const char *binary_names[] = {
				"ts_dep.bat",
				nullptr,
			};
			String root = get_root(args, String::null, true);
			if(!copy_files(path + "bin/", root + "bin/", binary_names)) {
				TS_LOG(Error, "create_makefile(): can't copy binaries\n");
				return false;
			}
		}
	}
	// unix platform
	else if(!platform) {
		
		// project template
		#include "templates/makefile.blob"
		if(!save_template(makefile_name, makefile_blob_src, vars)) {
			TS_LOG(Error, "create_makefile(): can't save project template\n");
			return false;
		}
	}
	// unknown platform
	else {
		TS_LOGF(Error, "create_makefile(): unknown platform \"%s\"\n", platform.get());
		return false;
	}
	
	// application icon
	if(platform == "and" || platform == "ios" || platform == "tvos") {
		
		// application icon
		#include "templates/resources/app_image.blob"
		String image_name = path + "tellusim.png";
		if(!save_file(image_name, app_image_blob_src)) {
			TS_LOG(Error, "create_makefile(): can't save image file\n");
			return false;
		}
	}
	
	return true;
}

/*****************************************************************************\
 *
 * VCXProj
 *
\*****************************************************************************/

/*
 */
static void create_vcxproj_vars(Variables &vars, const Arguments &args, const String &root, const char *prefix, const String &name) {
	
	// get arguments
	String arch = args["arch"];
	String version = args["version"];
	
	// set variables
	vars.append("ARCH", arch);
	vars.append("VERSION", version);
	
	// local path
	String include_path = String::tformat("{0}include;{0}plugins;{0}samples;", root);
	String library_path = String::tformat("{0}lib/{1}/{3}{2};", root, prefix, arch, version);
	
	// extern path
	String path = get_dirname(name);
	if(Directory::isDirectory(path + "extern")) {
		include_path += "extern;";
		String extern_include = String("extern/include");
		String extern_library = String::tformat("extern/lib/windows/{0}", arch);
		if(Directory::isDirectory(path + extern_include)) include_path += extern_include + ";";
		if(Directory::isDirectory(path + extern_library)) library_path += extern_library + ";";
	}
	
	// compilation flags
	String preprocessor;
	auto flags_it = args.find("flags");
	if(flags_it) {
		for(const String &flag : flags_it->data.replace("\\\"", "").replace("\\", "/").split(" ")) {
			if(flag.begins("/I")) include_path += String(flag.get() + 2).replace("$(TSROOT)/", root.get()) + ";";
			if(flag.begins("/D")) preprocessor += String(flag.get() + 2) + ";";
		}
	}
	
	// libraries path
	auto lib_it = args.find("lib");
	if(lib_it) {
		for(const String &lib : lib_it->data.replace("\\", "/").split(";")) {
			library_path += lib.replace("$(TSROOT)/", root.get()).replace("$(ARCH)", arch.get()) + ";";
		}
	}
	
	// linker flags
	String libraries;
	auto ldflags_it = args.find("ldflags");
	if(ldflags_it) {
		for(const String &flag : ldflags_it->data.split(" ")) {
			if(flag.extension() == "lib") libraries += flag + ";";
		}
	}
	
	// language standard
	String standard = String("Default");
	auto cflags_it = args.find("cflags");
	if(cflags_it) {
		for(const String &flag : cflags_it->data.split(" ")) {
			if(flag == "/std:c++14") standard = "stdcpp14";
			if(flag == "/std:c++17") standard = "stdcpp17";
			if(flag == "/std:c++20") standard = "stdcpp20";
		}
	}
	
	vars.append("INCLUDE_PATH", include_path.replace("/", "\\"));
	vars.append("LIBRARY_PATH", library_path.replace("/", "\\"));
	vars.append("LIBRARY_PATH_X64", library_path.replace(arch.get(), "x64").replace("/", "\\"));
	vars.append("LIBRARY_PATH_ARM64", library_path.replace(arch.get(), "arm64").replace("/", "\\"));
	vars.append("PREPROCESSOR", preprocessor);
	vars.append("LIBRARIES", libraries);
	vars.append("STANDARD", standard);
}

/*
 */
static bool create_vcxproj(const Arguments &args, const String &vcxproj_name) {
	
	// check arguments
	if(!check_args(args, { "language", "name", "target", "arch", "toolset", "version", "srcs" })) return false;
	
	// root directory
	String root = get_root(args, vcxproj_name);
	if(!root) {
		TS_LOG(Error, "create_vcxproj(): can't get root directory\n");
		return false;
	}
	
	// get arguments
	String name = args["name"];
	String srcs = args["srcs"];
	String hash = get_hash(args);
	String target = get_target(args);
	String toolset = args["toolset"];
	
	// vcxproj variables
	Variables vars;
	vars.append("NAME", name);
	vars.append("GUID", get_guid(hash));
	vars.append("TARGET", target);
	vars.append("TOOLSET", toolset);
	create_vcxproj_vars(vars, args, root, "windows", vcxproj_name);
	
	vars.append("DEBUGGER_PATH", String::tformat("{0}bin;", root).replace("/", "\\"));
	
	// sources
	String sources;
	for(const String &src : srcs.split(" \n")) {
		sources += String::tformat("\n\t\t<ClCompile Include=\"{0}\"/>", src.replace("/", "\\"));
	}
	vars.append("SOURCES", sources);
	
	// resources
	String resources;
	auto resources_it = args.find("resources");
	if(resources_it && resources_it->data) {
		for(const String &resource : resources_it->data.split(" \n")) {
			resources += String::tformat("\n\t\t<ResourceCompile Include=\"{0}\"/>", resource.replace("/", "\\"));
		}
	}
	vars.append("RESOURCES", resources);
	
	// project template
	#include "templates/vcxproj.blob"
	if(!save_template(vcxproj_name, vcxproj_blob_src, vars)) {
		TS_LOG(Error, "create_vcxproj(): can't save project template\n");
		return false;
	}
	
	return true;
}

/*****************************************************************************\
 *
 * Xcodeproj
 *
\*****************************************************************************/

/*
 */
static void create_xcodeproj_vars(Variables &vars, const Arguments &args, const String &root, const char *prefix, const String &arch, const String &name) {
	
	// container name
	vars.append("CONTAINER", name.basename());
	
	// local path
	String include_path = String::tformat(R"(
					"$(PROJECT_DIR)/{0}include",
					"$(PROJECT_DIR)/{0}plugins",
					"$(PROJECT_DIR)/{0}samples",)", root);
	
	String library_path = String::tformat(R"(
					"$(PROJECT_DIR)/{0}lib/{1}/{2}",)", root, prefix, arch);
	
	// extern path
	String path = get_dirname(name);
	if(Directory::isDirectory(path + "extern")) {
		include_path += R"(
					"$(PROJECT_DIR)/extern",)";
		if(Directory::isDirectory(path + "extern/include")) {
			include_path += R"(
					"$(PROJECT_DIR)/extern/include",)";
		}
		if(Directory::isDirectory(String::tformat("{0}extern/lib/{1}/{2}", path, prefix, arch))) {
			library_path += String::tformat(R"(
					"$(PROJECT_DIR)/extern/lib/{0}/{1}",)", prefix, arch);
		}
	}
	
	// compilation flags
	String preprocessor;
	String filetype = String("automatic");
	auto flags_it = args.find("flags");
	if(flags_it) {
		for(const String &flag : flags_it->data.replace("\\\"", "").replace("\\", "/").split(" ")) {
			if(flag.begins("-I")) {
				include_path += String::tformat(R"(
					"$(PROJECT_DIR)/{0}",)", flag.get() + 2).replace("$(TSROOT)/", root.get());
			}
			if(flag.begins("-D")) {
				preprocessor += String::tformat(R"(
					"{0}",)", flag.replace("\"", "\\\\\\\"").get() + 2);
			}
			if(flag == "-ObjC++" || flag == "-fobjc-arc") {
				filetype = "sourcecode.cpp.objcpp";
			}
		}
	}
	
	// linker flags
	String ldflags;
	auto libs_it = args.find("libs");
	if(libs_it) {
		bool is_framework = false;
		for(const String &lib : libs_it->data.split(" ")) {
			if(lib.begins("-l")) {
				ldflags += String::tformat(R"(
					"{0}",)", lib);
			}
			if(lib.begins("-L")) {
				library_path += String::tformat(R"(
					"$(PROJECT_DIR)/{0}",)", lib.get() + 2).replace("$(TSROOT)/", root.get()).replace("$(ARCH)", arch.get());
			}
			if(lib.begins("-framework")) {
				is_framework = true;
			} else if(is_framework) {
				ldflags += String::tformat(R"(
					"-framework", "{0}",)", lib);
				is_framework = false;
			}
		}
	}
	
	// language standard
	String std = args["std"];
	auto cflags_it = args.find("cflags");
	if(cflags_it) {
		for(const String &flag : cflags_it->data.split(" ")) {
			if(flag.contains("c++14")) std = "14";
			if(flag.contains("c++17")) std = "17";
			if(flag.contains("c++20")) std = "20";
		}
	}
	
	vars.append("INCLUDE_PATH", include_path);
	vars.append("LIBRARY_PATH", library_path);
	vars.append("PREPROCESSOR", preprocessor);
	vars.append("FILETYPE", filetype);
	vars.append("LDFLAGS", ldflags);
	vars.append("STD", std);
}

/*
 */
static bool create_xcodeproj_project(const String &name) {
	
	// create directory
	if(Directory::isDirectory(name) && !Directory::removeDirectory(name, true)) {
		TS_LOGF(Error, "create_xcodeproj_project(): can't remove \"%s\" directory\n", name.get());
		return false;
	}
	if(!Directory::createDirectory(name + "/xcshareddata/xcschemes", true)) {
		TS_LOGF(Error, "create_xcodeproj_project(): can't create \"%s\" directory\n", name.get());
		return false;
	}
	
	return true;
}

/*
 */
static bool create_xcodeproj(const Arguments &args, const String &xcodeproj_name) {
	
	// check arguments
	if(!check_args(args, { "language", "std", "target", "arch", "srcs" })) return false;
	
	// root directory
	String root = get_root(args, xcodeproj_name);
	if(!root) {
		TS_LOG(Error, "create_xcodeproj(): can't get root directory\n");
		return false;
	}
	
	// get arguments
	String arch = args["arch"];
	String srcs = args["srcs"];
	String hash = get_hash(args);
	String target = get_target(args);
	
	// variables
	Variables vars;
	vars.append("TARGET", target);
	vars.append("ARCH", arch);
	create_xcodeproj_vars(vars, args, root, "macos", arch, xcodeproj_name);
	
	vars.append("RUN_PATH", String::tformat(R"(
					"$(PROJECT_DIR)/{0}lib/macos/{1}",)", root, arch));
	
	// sources
	String files;
	String groups;
	String sources;
	uint32_t uuid = 0;
	for(const String &src : srcs.split(" \n")) {
		String uuid_0 = get_uuid(hash, uuid++);
		String uuid_1 = get_uuid(hash, uuid++);
		files += String::tformat(R"(
		{0} = { isa = PBXBuildFile; fileRef = {1}; };
		{1} = { isa = PBXFileReference; path = {2}; sourceTree = "<group>"; };)", uuid_0, uuid_1, src);
		groups += String::tformat(R"(
				{0},)", uuid_1);
		sources += String::tformat(R"(
				{0},)", uuid_0);
	}
	
	vars.append("FILES", files);
	vars.append("GROUPS", groups);
	vars.append("SOURCES", sources);
	
	// create uuid
	Array<String> uuids(32);
	for(uint32_t i = 0; i < uuids.size(); i++) {
		uuids[i] = String::format("ID%02u", i);
		vars.append(uuids[i].get(), get_uuid(hash, uuid++));
	}
	
	// create project
	if(!create_xcodeproj_project(xcodeproj_name)) {
		TS_LOG(Error, "create_xcodeproj(): can't create project\n");
		return false;
	}
	
	// project template
	#include "templates/pbxproj.blob"
	String project_name = xcodeproj_name + "/project.pbxproj";
	if(!save_template(project_name, pbxproj_blob_src, vars)) {
		TS_LOG(Error, "create_xcodeproj(): can't save project template\n");
		return false;
	}
	
	// scheme template
	#include "templates/pbxscheme.blob"
	String scheme_name = String::tformat("{0}/xcshareddata/xcschemes/{1}.{2}.xcscheme", xcodeproj_name, target, arch);
	if(!save_template(scheme_name, pbxscheme_blob_src, vars)) {
		TS_LOG(Error, "create_xcodeproj(): can't save scheme template\n");
		return false;
	}
	
	return true;
}

/*
 */
static bool create_xcodeproj_ios(const Arguments &args, const String &xcodeproj_name) {
	
	// check arguments
	if(!check_args(args, { "language", "std", "ipa", "target", "srcs" })) return false;
	
	// root directory
	String root = get_root(args, xcodeproj_name);
	if(!root) {
		TS_LOG(Error, "create_xcodeproj_ios(): can't get root directory\n");
		return false;
	}
	
	// get arguments
	String ipa = args["ipa"];
	String srcs = args["srcs"];
	String arch = String("arm64");
	String hash = get_hash(args);
	String target = get_target(args);
	
	// variables
	Variables vars;
	vars.append("IPA", ipa);
	vars.append("TARGET", target);
	create_xcodeproj_vars(vars, args, root, "ios", arch, xcodeproj_name);
	
	// code sign
	auto team_it = args.find("team");
	if(team_it) {
		vars.append("TEAM", team_it->data);
		vars.append("SIGN", String("Automatic"));
	} else {
		vars.append("TEAM", String::null);
		vars.append("SIGN", String("Manual"));
	}
	
	// sources
	String files;
	String groups;
	String sources;
	uint32_t uuid = 0;
	for(const String &src : srcs.split(" \n")) {
		String uuid_0 = get_uuid(hash, uuid++);
		String uuid_1 = get_uuid(hash, uuid++);
		files += String::tformat(R"(
		{0} = { isa = PBXBuildFile; fileRef = {1}; };
		{1} = { isa = PBXFileReference; path = {2}; sourceTree = "<group>"; };)", uuid_0, uuid_1, src);
		groups += String::tformat(R"(
				{0},)", uuid_1);
		sources += String::tformat(R"(
				{0},)", uuid_0);
	}
	
	// assets
	String assets;
	for(const String &asset : get_assets(args, xcodeproj_name).split(" \n")) {
		String uuid_0 = get_uuid(hash, uuid++);
		String uuid_1 = get_uuid(hash, uuid++);
		files += String::tformat(R"(
		{0} = { isa = PBXBuildFile; fileRef = {1}; settings = { ATTRIBUTES = ("--decompress"); }; };
		{1} = { isa = PBXFileReference; path = {2}; sourceTree = "<group>"; };)", uuid_0, uuid_1, asset);
		groups += String::tformat(R"(
				{0},)", uuid_1);
		assets += String::tformat(R"(
				{0},)", uuid_0);
	}
	
	vars.append("FILES", files);
	vars.append("GROUPS", groups);
	vars.append("SOURCES", sources);
	vars.append("ASSETS", assets);
	
	// create uuid
	Array<String> uuids(32);
	for(uint32_t i = 0; i < uuids.size(); i++) {
		uuids[i] = String::format("ID%02u", i);
		vars.append(uuids[i].get(), get_uuid(hash, uuid++));
	}
	
	// create project
	if(!create_xcodeproj_project(xcodeproj_name)) {
		TS_LOG(Error, "create_xcodeproj_ios(): can't create project\n");
		return false;
	}
	
	// project template
	#include "templates/pbxproj_ios.blob"
	String project_name = xcodeproj_name + "/project.pbxproj";
	if(!save_template(project_name, pbxproj_ios_blob_src, vars)) {
		TS_LOG(Error, "create_xcodeproj_ios(): can't save project template\n");
		return false;
	}
	
	// scheme template
	#include "templates/pbxscheme_ios.blob"
	String scheme_name = String::tformat("{0}/xcshareddata/xcschemes/{1}.{2}.xcscheme", xcodeproj_name, target, arch);
	if(!save_template(scheme_name, pbxscheme_ios_blob_src, vars)) {
		TS_LOG(Error, "create_xcodeproj_ios(): can't save scheme template\n");
		return false;
	}
	
	return true;
}

/*
 */
static bool create_xcodeproj_tvos(const Arguments &args, const String &xcodeproj_name) {
	
	// check arguments
	if(!check_args(args, { "language", "std", "ipa", "target", "srcs" })) return false;
	
	// root directory
	String root = get_root(args, xcodeproj_name);
	if(!root) {
		TS_LOG(Error, "create_xcodeproj_tvos(): can't get root directory\n");
		return false;
	}
	
	// get arguments
	String ipa = args["ipa"];
	String srcs = args["srcs"];
	String arch = String("arm64");
	String hash = get_hash(args);
	String target = get_target(args);
	
	// variables
	Variables vars;
	vars.append("IPA", ipa);
	vars.append("TARGET", target);
	create_xcodeproj_vars(vars, args, root, "tvos", arch, xcodeproj_name);
	
	// code sign
	auto team_it = args.find("team");
	if(team_it) {
		vars.append("TEAM", team_it->data);
		vars.append("SIGN", String("Automatic"));
	} else {
		vars.append("TEAM", String::null);
		vars.append("SIGN", String("Manual"));
	}
	
	// sources
	String files;
	String groups;
	String sources;
	uint32_t uuid = 0;
	for(const String &src : srcs.split(" \n")) {
		String uuid_0 = get_uuid(hash, uuid++);
		String uuid_1 = get_uuid(hash, uuid++);
		files += String::tformat(R"(
		{0} = { isa = PBXBuildFile; fileRef = {1}; };
		{1} = { isa = PBXFileReference; path = {2}; sourceTree = "<group>"; };)", uuid_0, uuid_1, src);
		groups += String::tformat(R"(
				{0},)", uuid_1);
		sources += String::tformat(R"(
				{0},)", uuid_0);
	}
	
	// assets
	String assets;
	for(const String &asset : get_assets(args, xcodeproj_name).split(" \n")) {
		String uuid_0 = get_uuid(hash, uuid++);
		String uuid_1 = get_uuid(hash, uuid++);
		files += String::tformat(R"(
		{0} = { isa = PBXBuildFile; fileRef = {1}; settings = { ATTRIBUTES = ("--decompress"); }; };
		{1} = { isa = PBXFileReference; path = {2}; sourceTree = "<group>"; };)", uuid_0, uuid_1, asset);
		groups += String::tformat(R"(
				{0},)", uuid_1);
		assets += String::tformat(R"(
				{0},)", uuid_0);
	}
	
	vars.append("FILES", files);
	vars.append("GROUPS", groups);
	vars.append("SOURCES", sources);
	vars.append("ASSETS", assets);
	
	// create uuid
	Array<String> uuids(32);
	for(uint32_t i = 0; i < uuids.size(); i++) {
		uuids[i] = String::format("ID%02u", i);
		vars.append(uuids[i].get(), get_uuid(hash, uuid++));
	}
	
	// create project
	if(!create_xcodeproj_project(xcodeproj_name)) {
		TS_LOG(Error, "create_xcodeproj_ios(): can't create project\n");
		return false;
	}
	
	// project template
	#include "templates/pbxproj_tvos.blob"
	String project_name = xcodeproj_name + "/project.pbxproj";
	if(!save_template(project_name, pbxproj_tvos_blob_src, vars)) {
		TS_LOG(Error, "create_xcodeproj_tvos(): can't save project template\n");
		return false;
	}
	
	// scheme template
	#include "templates/pbxscheme_tvos.blob"
	String scheme_name = String::tformat("{0}/xcshareddata/xcschemes/{1}.{2}.xcscheme", xcodeproj_name, target, arch);
	if(!save_template(scheme_name, pbxscheme_tvos_blob_src, vars)) {
		TS_LOG(Error, "create_xcodeproj_tvos(): can't save scheme template\n");
		return false;
	}
	
	return true;
}

/*
 */
static bool create_xcodeproj_swift_ios(const Arguments &args, const String &xcodeproj_name) {
	
	// check arguments
	if(!check_args(args, { "language", "std", "ipa", "target", "srcs" })) return false;
	
	// root directory
	String root = get_root(args, xcodeproj_name);
	if(!root) {
		TS_LOG(Error, "create_xcodeproj_swift_ios(): can't get root directory\n");
		return false;
	}
	
	// get arguments
	String std = args["std"];
	String ipa = args["ipa"];
	String srcs = args["srcs"];
	String arch = String("arm64");
	String hash = get_hash(args);
	String target = get_target(args);
	
	// variables
	Variables vars;
	vars.append("STD", std);
	vars.append("IPA", ipa);
	vars.append("TARGET", target);
	vars.append("CONTAINER", xcodeproj_name.basename());
	
	// code sign
	auto team_it = args.find("team");
	if(team_it) {
		vars.append("TEAM", team_it->data);
		vars.append("SIGN", String("Automatic"));
	} else {
		vars.append("TEAM", String::null);
		vars.append("SIGN", String("Manual"));
	}
	
	// delegate source
	srcs += " delegate.swift";
	
	// sources
	String files;
	String groups;
	String sources;
	uint32_t uuid = 0;
	for(const String &src : srcs.split(" \n")) {
		String uuid_0 = get_uuid(hash, uuid++);
		String uuid_1 = get_uuid(hash, uuid++);
		files += String::tformat(R"(
		{0} = { isa = PBXBuildFile; fileRef = {1}; };
		{1} = { isa = PBXFileReference; path = {2}; sourceTree = "<group>"; };)", uuid_0, uuid_1, src);
		groups += String::tformat(R"(
				{0},)", uuid_1);
		sources += String::tformat(R"(
				{0},)", uuid_0);
	}
	
	// assets
	String assets;
	String resources;
	for(const String &asset : get_assets(args, xcodeproj_name).split(" \n")) {
		String uuid_0 = get_uuid(hash, uuid++);
		String uuid_1 = get_uuid(hash, uuid++);
		files += String::tformat(R"(
		{0} = { isa = PBXBuildFile; fileRef = {1}; settings = { ATTRIBUTES = ("--decompress"); }; };
		{1} = { isa = PBXFileReference; path = {2}; sourceTree = "<group>"; };)", uuid_0, uuid_1, asset);
		resources += String::tformat(R"(
				{0},)", uuid_1);
		assets += String::tformat(R"(
				{0},)", uuid_0);
	}
	
	vars.append("FILES", files);
	vars.append("GROUPS", groups);
	vars.append("SOURCES", sources);
	vars.append("RESOURCES", resources);
	vars.append("ASSETS", assets);
	
	// create uuid
	Array<String> uuids(32);
	for(uint32_t i = 0; i < uuids.size(); i++) {
		uuids[i] = String::format("ID%02u", i);
		vars.append(uuids[i].get(), get_uuid(hash, uuid++));
	}
	
	// create project
	if(!create_xcodeproj_project(xcodeproj_name)) {
		TS_LOG(Error, "create_xcodeproj_swift_ios(): can't create project\n");
		return false;
	}
	
	// create delegate template
	#include "templates/swift/app_delegate.blob"
	String delegate_name = xcodeproj_name.dirname() + "Sources/delegate.swift";
	if(!save_template(delegate_name, app_delegate_blob_src, vars)) {
		TS_LOG(Error, "create_xcodeproj_swift_ios(): can't save delegate template\n");
		return false;
	}
	
	// project template
	#include "templates/swift/pbxproj_ios.blob"
	String project_name = xcodeproj_name + "/project.pbxproj";
	if(!save_template(project_name, pbxproj_ios_blob_src, vars)) {
		TS_LOG(Error, "create_xcodeproj_swift_ios(): can't save project template\n");
		return false;
	}
	
	// scheme template
	#include "templates/pbxscheme_ios.blob"
	String scheme_name = String::tformat("{0}/xcshareddata/xcschemes/{1}.{2}.xcscheme", xcodeproj_name, target, arch);
	if(!save_template(scheme_name, pbxscheme_ios_blob_src, vars)) {
		TS_LOG(Error, "create_xcodeproj_swift_ios(): can't save scheme template\n");
		return false;
	}
	
	return true;
}

/*****************************************************************************\
 *
 * Gradle
 *
\*****************************************************************************/

/*
 */
static bool create_gradlew(const String &gradle_name) {
	
	// gradle path
	String gradle_path = gradle_name;
	if(gradle_path && gradle_path.back() != '/') gradle_path += "/";
	
	// create gradlew
	String wrapper_path = gradle_path + "gradle/wrapper/";
	if(!Directory::createDirectory(wrapper_path, true)) {
		TS_LOGF(Error, "create_gradlew(): can't create \"%s\" directory\n", wrapper_path.get());
		return false;
	}
	
	// create unix wrapper
	#include "templates/gradle/gradlew_sh.blob"
	String gradlew_name = gradle_path + "gradlew";
	if(!save_file(gradlew_name, gradlew_sh_blob_src)) {
		TS_LOG(Error, "create_gradlew(): can't save gradlew file\n");
		return false;
	}
	Directory::setFileAttributes(gradlew_name.get(), Directory::AttributeRead | Directory::AttributeWrite | Directory::AttributeExecute);
	
	// create windows wrapper
	#include "templates/gradle/gradlew_bat.blob"
	String gradlew_bat_name = gradle_path + "gradlew.bat";
	if(!save_file(gradlew_bat_name, gradlew_bat_blob_src)) {
		TS_LOG(Error, "create_gradlew(): can't save gradlew.bat file\n");
		return false;
	}
	Directory::setFileAttributes(gradlew_bat_name.get(), Directory::AttributeRead | Directory::AttributeWrite | Directory::AttributeExecute);
	
	// create wrapper
	#include "templates/gradle/wrapper.blob"
	String jar_name = wrapper_path + "gradle-wrapper.jar";
	if(!save_file(jar_name, wrapper_blob_src)) {
		TS_LOG(Error, "create_gradlew(): can't save jar file\n");
		return false;
	}
	
	// create properties
	#include "templates/gradle/properties.blob"
	String properties_name = wrapper_path + "gradle-wrapper.properties";
	if(!save_file(properties_name, properties_blob_src)) {
		TS_LOG(Error, "create_gradlew(): can't save properties file\n");
		return false;
	}
	
	return true;
}

/*
 */
static void create_gradle_and_vars(Variables &vars, const Arguments &args, const String &root, const String &name) {
	
	// get arguments
	String std = args["std"];
	
	// set variables
	vars.append("STD", std);
	
	// local path
	String include_path = String::tformat("\n\t{0}include\n\t{0}plugins\n\t{0}samples", root);
	String library_path = String::tformat("\n\t{0}lib/android/arm64", root);
	
	// extern path
	String path = get_dirname(name);
	if(Directory::isDirectory(path + "extern")) {
		include_path += "\n\t../extern";
		if(Directory::isDirectory(path + "extern/include")) include_path += "\n\t../extern/include";
		if(Directory::isDirectory(path + "extern/lib/android/arm64")) library_path += "\n\t../extern/lib/android/arm64";
	}
	
	vars.append("INCLUDE_PATH", include_path);
	vars.append("LIBRARY_PATH", library_path);
	
	// linker flags
	String link_library;
	auto libs_it = args.find("libs");
	if(libs_it) {
		for(const String &lib : libs_it->data.split(" ")) {
			if(lib.begins("-l")) {
				link_library += String::tformat(" {0}", lib.get() + 2);
			}
		}
	}
	vars.append("LINK_LIBRARY", link_library);
}

/*
 */
static bool create_gradle_and(const Arguments &args, const String &gradle_name) {
	
	// check arguments
	if(!check_args(args, { "language", "std", "apk", "target", "minsdk", "srcs" })) return false;
	
	// root directory
	String root = get_root(args, gradle_name);
	if(!root) {
		TS_LOG(Error, "create_gradle_and(): can't get root directory\n");
		return false;
	}
	root = ("../" + root).pathname();
	
	// get arguments
	String apk = args["apk"];
	String srcs = args["srcs"];
	String minsdk = args["minsdk"];
	String target = get_target(args);
	
	// gradle variables
	Variables vars;
	vars.append("APK", apk);
	vars.append("ROOT", root);
	vars.append("TARGET", target);
	vars.append("MINSDK", minsdk);
	create_gradle_and_vars(vars, args, root, gradle_name);
	
	// sources
	String sources;
	for(const String &src : srcs.split(" \n")) {
		sources += "\n\t../" + src;
	}
	vars.append("SOURCES", sources);
	
	// assets
	String assets;
	for(const String &asset : get_assets(args, gradle_name).split(" \n")) {
		if(assets) assets += ", ";
		assets += String::tformat("\"../{0}\"", asset);
	}
	vars.append("ASSETS", assets);
	
	// create directory
	if(Directory::isDirectory(gradle_name) && !Directory::removeDirectory(gradle_name, true)) {
		TS_LOGF(Error, "create_gradle_and(): can't remove \"%s\" directory\n", gradle_name.get());
		return false;
	}
	if(!Directory::createDirectory(gradle_name + "/src/main/res/drawable", true)) {
		TS_LOGF(Error, "create_gradle_and(): can't create \"%s\" directory\n", gradle_name.get());
		return false;
	}
	
	// application icon
	#include "templates/resources/app_image.blob"
	String drawable_name = gradle_name + "/src/main/res/drawable/tellusim.png";
	if(!save_file(drawable_name, app_image_blob_src)) {
		TS_LOG(Error, "create_gradle_and(): can't save drawable file\n");
		return false;
	}
	
	// build template
	#include "templates/gradle_and_build.blob"
	String build_name = gradle_name + "/build.gradle";
	if(!save_template(build_name, gradle_and_build_blob_src, vars)) {
		TS_LOG(Error, "create_gradle_and(): can't save build template\n");
		return false;
	}
	
	// project template
	#include "templates/gradle_and_cmake.blob"
	String project_name = gradle_name + "/CMakeLists.txt";
	if(!save_template(project_name, gradle_and_cmake_blob_src, vars)) {
		TS_LOG(Error, "create_gradle_and(): can't save project template\n");
		return false;
	}
	
	// settings template
	#include "templates/gradle_and_settings.blob"
	String settings_name = gradle_name + "/settings.gradle";
	if(!save_template(settings_name, gradle_and_settings_blob_src, vars)) {
		TS_LOG(Error, "create_gradle_and(): can't save settings template\n");
		return false;
	}
	
	// manifest template
	#include "templates/gradle_and_apk.blob"
	String manifest_name = gradle_name + "/src/main/AndroidManifest.xml";
	if(!save_template(manifest_name, gradle_and_apk_blob_src, vars)) {
		TS_LOG(Error, "create_gradle_and(): can't save manifest template\n");
		return false;
	}
	
	// create gradle
	if(!create_gradlew(gradle_name)) return false;
	
	return true;
}

/*
 */
static bool create_gradle_java(const Arguments &args, const String &project_path) {
	
	// check arguments
	if(!check_args(args, { "language", "name" })) return false;
	
	// root directory
	String root = get_root(args, project_path);
	if(!root) {
		TS_LOG(Error, "create_gradle_java(): can't get root directory\n");
		return false;
	}
	
	// get arguments
	String name = args["name"];
	
	// gradle variables
	Variables vars;
	vars.append("NAME", name);
	
	// build template
	#include "templates/java/gradle_build.blob"
	String build_name = project_path + "build.gradle";
	if(!save_template(build_name, gradle_build_blob_src, vars)) {
		TS_LOG(Error, "create_gradle_java(): can't save build template\n");
		return false;
	}
	
	// settings template
	#include "templates/java/gradle_settings.blob"
	String settings_name = project_path + "settings.gradle";
	if(!save_template(settings_name, gradle_settings_blob_src, vars)) {
		TS_LOG(Error, "create_gradle_java(): can't save settings template\n");
		return false;
	}
	
	// create gradle
	if(!create_gradlew(project_path)) return false;
	
	return true;
}

/*
 */
static bool create_gradle_java_and(const Arguments &args, const String &project_path) {
	
	// check arguments
	if(!check_args(args, { "language", "apk", "minsdk" })) return false;
	
	// root directory
	String root = get_root(args, project_path);
	if(!root) {
		TS_LOG(Error, "create_gradle_java_and(): can't get root directory\n");
		return false;
	}
	
	// get arguments
	String apk = args["apk"];
	String minsdk = args["minsdk"];
	
	// gradle variables
	Variables vars;
	vars.append("APK", apk);
	vars.append("MINSDK", minsdk);
	
	// assets
	String assets;
	for(const String &asset : get_assets(args, project_path).split(" \n")) {
		if(assets) assets += ", ";
		assets += String::tformat("\"{0}\"", asset);
	}
	vars.append("ASSETS", assets);
	
	// create directory
	if(!Directory::createDirectory(project_path + "src/main/res/drawable", true)) {
		TS_LOGF(Error, "create_gradle_java_and(): can't create \"%s\" directory\n", project_path.get());
		return false;
	}
	
	// create activity template
	#include "templates/java/app_activity.blob"
	String activity_name = project_path + "src/main/java/com/main/activity.java";
	if(!save_template(activity_name, app_activity_blob_src, vars)) {
		TS_LOG(Error, "create_gradle_java_and(): can't save activity template\n");
		return false;
	}
	
	// application icon
	#include "templates/resources/app_image.blob"
	String drawable_name = project_path + "src/main/res/drawable/tellusim.png";
	if(!save_file(drawable_name, app_image_blob_src)) {
		TS_LOG(Error, "create_gradle_java_and(): can't save drawable file\n");
		return false;
	}
	
	// build template
	#include "templates/java/gradle_and_build.blob"
	String build_name = project_path + "build.gradle";
	if(!save_template(build_name, gradle_and_build_blob_src, vars)) {
		TS_LOG(Error, "create_gradle_java_and(): can't save build template\n");
		return false;
	}
	
	// settings template
	#include "templates/java/gradle_and_settings.blob"
	String settings_name = project_path + "settings.gradle";
	if(!save_template(settings_name, gradle_and_settings_blob_src, vars)) {
		TS_LOG(Error, "create_gradle_java_and(): can't save settings template\n");
		return false;
	}
	
	// manifest template
	#include "templates/java/gradle_and_apk.blob"
	String manifest_name = project_path + "src/main/AndroidManifest.xml";
	if(!save_template(manifest_name, gradle_and_apk_blob_src, vars)) {
		TS_LOG(Error, "create_gradle_java_and(): can't save manifest template\n");
		return false;
	}
	
	// create gradle
	if(!create_gradlew(project_path)) return false;
	
	return true;
}

/*****************************************************************************\
 *
 * CSProj
 *
\*****************************************************************************/

/*
 */
static bool create_csproj(const Arguments &args, const String &csproj_name) {
	
	// check arguments
	if(!check_args(args, { "language", "name", "target", "arch", "srcs" })) return false;
	
	// root directory
	String root = get_root(args, csproj_name);
	if(!root) {
		TS_LOG(Error, "create_csproj(): can't get root directory\n");
		return false;
	}
	
	// get arguments
	String arch = args["arch"];
	String name = args["name"];
	String srcs = args["srcs"];
	String target = get_target(args);
	
	// csproj variables
	Variables vars;
	vars.append("ARCH", arch);
	vars.append("NAME", name);
	vars.append("TARGET", target);
	
	// sources
	String sources;
	for(const String &src : srcs.split(" \n")) {
		if(sources) sources += " ";
		sources += src;
	}
	vars.append("SOURCES", sources);
	
	// project template
	#include "templates/csharp/csproj.blob"
	if(!save_template(csproj_name, csproj_blob_src, vars)) {
		TS_LOG(Error, "create_csproj(): can't save project template\n");
		return false;
	}
	
	// makefile template
	#if !_WIN32
		#include "templates/csharp/makefile.blob"
		String makefile_name = csproj_name.dirname() + "Makefile";
		if(!save_template(makefile_name, makefile_blob_src, vars)) {
			TS_LOG(Error, "create_csproj(): can't save project template\n");
			return false;
		}
	#endif
	
	return true;
}

/*****************************************************************************\
 *
 * Cargo
 *
\*****************************************************************************/

/*
 */
static bool create_cargo(const Arguments &args, const String &project_path) {
	
	// check arguments
	if(!check_args(args, { "language", "name", "target", "arch" })) return false;
	
	// root directory
	String root = get_root(args, project_path);
	if(!root) {
		TS_LOG(Error, "create_cargo(): can't get root directory\n");
		return false;
	}
	
	// get arguments
	String arch = args["arch"];
	String name = args["name"];
	String target = get_target(args);
	
	// cargo variables
	Variables vars;
	vars.append("ARCH", arch);
	vars.append("NAME", name);
	vars.append("TARGET", target);
	
	// build template
	#include "templates/rust/build.blob"
	if(!save_template(project_path + "build.rs", build_blob_src, vars)) {
		TS_LOG(Error, "create_cargo(): can't save build template\n");
		return false;
	}
	
	// cargo template
	#include "templates/rust/cargo.blob"
	if(!save_template(project_path + "Cargo.toml", cargo_blob_src, vars)) {
		TS_LOG(Error, "create_cargo(): can't save cargo template\n");
		return false;
	}
	
	// build template
	#include "templates/rust/tellusim.blob"
	if(!save_template(project_path + "tellusim/Cargo.toml", tellusim_blob_src, vars)) {
		TS_LOG(Error, "create_cargo(): can't save tellusim template\n");
		return false;
	}
	
	return true;
}

/*****************************************************************************\
 *
 * SwiftPM
 *
\*****************************************************************************/

/*
 */
static bool create_swift(const Arguments &args, const String &project_path) {
	
	// check arguments
	if(!check_args(args, { "language", "name", "target", "arch" })) return false;
	
	// root directory
	String root = get_root(args, project_path);
	if(!root) {
		TS_LOG(Error, "create_swift(): can't get root directory\n");
		return false;
	}
	
	// get arguments
	String arch = args["arch"];
	String name = args["name"];
	String target = get_target(args);
	
	// swift variables
	Variables vars;
	vars.append("ARCH", arch);
	vars.append("NAME", name);
	vars.append("TARGET", target);
	
	// package template
	#include "templates/swift/package.blob"
	if(!save_template(project_path + "Package.swift", package_blob_src, vars)) {
		TS_LOG(Error, "create_swift(): can't save package template\n");
		return false;
	}
	
	return true;
}

/*****************************************************************************\
 *
 * main
 *
\*****************************************************************************/

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	// message log level
	Log::setLevel(Log::Message);
	
	// create controls
	if(argc == 1) {
		Controls controls(argc, argv);
		if(!controls.create()) {
			TS_LOGF(Error, "%s: can't create controls\n", argv[0]);
			return 1;
		}
		return controls.run();
	}
	
	// print help
	App app(argc, argv);
	if(app.isArgument("h") || app.isArgument("help")) {
		Log::printf("Tellusim Project Generation Tool (build " __DATE__ " https://tellusim.com/)\n");
		Log::printf("Usage: %s -fragment my_project -vcxproj -xcodeproj -root ../Tellusim_SDK\n", argv[0]);
		Log::printf("Usage: %s -engine my_project -makefile Makefile -root ../Tellusim_SDK\n", argv[0]);
		Log::printf("Usage: %s Makefile -cmake -makefile\n", argv[0]);
		Log::print("  -verbose          Verbose output\n");
		Log::print("  -force            Force creation\n");
		Log::print("  -clear            Clear arguments\n");
		Log::print("  -info             Print arguments\n");
		Log::print("  -run              Run Application\n");
		Log::print("  -core <name>      Create Core App\n");
		Log::print("  -engine <name>    Create Engine App\n");
		Log::print("  -canvas <name>    Create Canvas App\n");
		Log::print("  -compute <name>   Create Compute App\n");
		Log::print("  -fragment <name>  Create Fragment App\n");
		Log::print("  -name <name>      Set project name\n");
		Log::print("  -root <path>      Path to Tellusim SDK root\n");
		Log::print("  -target <name>    Binary name (main)\n");
		Log::print("  -postfix <name>   Target postfix\n");
		Log::print("  -platform <name>  Target platform (ios, tvos, and)\n");
		Log::print("  -arch <name>      Project architecture\n");
		Log::print("  -ipa <name>       iOS/tvOS IPA name\n");
		Log::print("  -apk <name>       Android APK name\n");
		Log::print("  -team <name>      Xcode development team\n");
		Log::print("  -srcs <name>      Source files\n");
		Log::print("  -libs <name>      Library names\n");
		Log::print("  -assets <name>    Resource names\n");
		Log::print("  -std <version>    C++ STD version (11)\n");
		Log::print("  -toolset <ver>    Visual Studio toolset (v143)\n");
		Log::print("  -version <ver>    Visual Studio version (vs170)\n");
		Log::print("  -minsdk <ver>     Android SDK version (33)\n");
		Log::print("  -check <argument> Exit if the argument is not defined\n");
		Log::print("  -cmake (name)     Create CMake C++ project\n");
		Log::print("  -makefile (name)  Create Makefile C++ project (win, and, ios, tvos, ems)\n");
		Log::print("  -vcxproj (name)   Create Visual Studio C++ project\n");
		Log::print("  -xcodeproj (name) Create Xcode C++ project\n");
		Log::print("  -gradle (name)    Create Gradle C++ project\n");
		Log::print("  -csproj (name)    Create C# project\n");
		Log::print("  -java (name)      Create Java project\n");
		Log::print("  -cargo            Create Rust project\n");
		Log::print("  -swift            Create Swift project\n");
		Log::print("  -python           Create Python project\n");
		Log::print("  -javascript       Create JavaScript project\n");
		return 0;
	}
	
	// arguments
	Set<const char*> names = {
		"name", "root", "target", "postfix", "platform", "arch", "ipa", "apk", "team",
		"srcs", "libs", "assets", "std", "toolset", "version", "minsdk",
	};
	Map<const char*, const char*> renames = {
		{ "src", "srcs" },
		{ "lib", "libs" },
		{ "asset", "assets" },
	};
	
	// makefile name
	String makefile_name;
	
	// project path
	String project_name;
	String project_path;
	
	// project arguments
	Arguments arguments;
	create_args(argc, argv, 1, arguments);
	
	// command line arguments
	for(int32_t i = 1; i < argc; i++) {
		const char *s = argv[i];
		
		// commands
		if(s[0] == '-') {
			while(*s == '-') s++;
			String command = String(s);
			
			// application mode
			if(command == "run") {
				Controls controls(argc, argv);
				if(!controls.create()) {
					TS_LOGF(Error, "%s: can't create controls\n", argv[0]);
					return 1;
				}
				return controls.run();
			}
			
			// verbose output
			else if(command == "verbose" || command == "v") {
				Log::setLevel(Log::Verbose);
			}
			
			// force creation
			else if(command == "force" || command == "f") {
				arguments.append(String("force"));
			}
			
			// clear arguments
			else if(command == "clear") {
				arguments.clear();
				create_args(argc, argv, i + 1, arguments);
				makefile_name.clear();
				project_name.clear();
				project_path.clear();
			}
			
			// print current arguments
			else if(command == "info") {
				print_args(arguments);
			}
			
			// create application
			else if(command == "core" && i + 1 < argc) {
				project_path = get_path(argv[++i]);
				TS_LOGF(Verbose, "Creating \"%s\" Core App\n", project_path.get());
				if(!create_core(arguments, project_path)) {
					TS_LOGF(Error, "%s: can't create \"%s\" core app\n", argv[0], project_path.get());
					return 1;
				}
				project_name = arguments["name"];
			}
			else if(command == "engine" && i + 1 < argc) {
				project_path = get_path(argv[++i]);
				TS_LOGF(Verbose, "Creating \"%s\" Engine App\n", project_path.get());
				if(!create_engine(arguments, project_path)) {
					TS_LOGF(Error, "%s: can't create \"%s\" engine app\n", argv[0], project_path.get());
					return 1;
				}
				project_name = arguments["name"];
			}
			else if(command == "canvas" && i + 1 < argc) {
				project_path = get_path(argv[++i]);
				TS_LOGF(Verbose, "Creating \"%s\" Canvas App\n", project_path.get());
				if(!create_core_canvas(arguments, project_path)) {
					TS_LOGF(Error, "%s: can't create \"%s\" canvas app\n", argv[0], project_path.get());
					return 1;
				}
				project_name = arguments["name"];
			}
			else if(command == "compute" && i + 1 < argc) {
				project_path = get_path(argv[++i]);
				TS_LOGF(Verbose, "Creating \"%s\" Compute App\n", project_path.get());
				if(!create_core_compute(arguments, project_path)) {
					TS_LOGF(Error, "%s: can't create \"%s\" compute app\n", argv[0], project_path.get());
					return 1;
				}
				project_name = arguments["name"];
			}
			else if(command == "fragment" && i + 1 < argc) {
				project_path = get_path(argv[++i]);
				TS_LOGF(Verbose, "Creating \"%s\" Fragment App\n", project_path.get());
				if(!create_core_fragment(arguments, project_path)) {
					TS_LOGF(Error, "%s: can't create \"%s\" fragment app\n", argv[0], project_path.get());
					return 1;
				}
				project_name = arguments["name"];
			}
			
			// command line parameters
			else if(names.find(command) && i + 1 < argc) {
				arguments.append(command, String(argv[++i]));
			}
			else if(renames.find(command) && i + 1 < argc) {
				auto rename_it = renames.find(command);
				auto argument_it = arguments.find(rename_it->data);
				String argument = String(argv[++i]);
				if(argument_it) argument_it->data += " " + argument;
				else arguments.append(String(rename_it->data), argument);
			}
			
			// check argument
			else if(command == "check" && i + 1 < argc) {
				if(!arguments.find(argv[++i])) return 0;
			}
			
			// targets
			else if(command == "cmake") {
				String name = project_path;
				if(i + 1 < argc && argv[i + 1][0] != '-') name += argv[++i];
				else name += "CMakeLists.txt";
				TS_LOGF(Verbose, "Creating \"%s\"\n", name.get());
				if(!create_cmake(arguments, name)) {
					if(makefile_name) TS_LOGF(Error, "%s: can't create \"%s\" from \"%s\"\n", argv[0], name.get(), makefile_name.get());
					else TS_LOGF(Error, "%s: can't create \"%s\"\n", argv[0], name.get());
					print_args(arguments);
					return 1;
				}
			}
			else if(command == "makefile") {
				String name = project_path;
				auto apk_it = arguments.find("apk");
				auto ipa_it = arguments.find("ipa");
				auto platform_it = arguments.find("platform");
				if(i + 1 < argc && argv[i + 1][0] != '-') name += argv[++i];
				else if(platform_it) name += "Makefile." + platform_it->data;
				else if(ipa_it) name += "Makefile.ios";
				else if(apk_it) name += "Makefile.and";
				#if _WIN32
					else name += "Makefile.win";
				#else
					else name += "Makefile";
				#endif
				TS_LOGF(Verbose, "Creating \"%s\"\n", name.get());
				if(!create_makefile(arguments, name)) {
					if(makefile_name) TS_LOGF(Error, "%s: can't create \"%s\" from \"%s\"\n", argv[0], name.get(), makefile_name.get());
					else TS_LOGF(Error, "%s: can't create \"%s\"\n", argv[0], name.get());
					print_args(arguments);
					return 1;
				}
			}
			else if(command == "vcxproj") {
				bool ret = false;
				String name = project_path;
				if(i + 1 < argc && argv[i + 1][0] != '-') name += argv[++i];
				else if(project_name) name += project_name + ".vcxproj";
				else name.clear();
				if(name) {
					TS_LOGF(Verbose, "Creating \"%s\"\n", name.get());
					ret = create_vcxproj(arguments, name);
				} else {
					TS_LOGF(Error, "%s: unknown project name\n", argv[0]);
				}
				if(!ret) {
					if(makefile_name) TS_LOGF(Error, "%s: can't create vcxproj from \"%s\"\n", argv[0], makefile_name.get());
					else TS_LOGF(Error, "%s: can't create vcxproj\n", argv[0]);
					print_args(arguments);
					return 1;
				}
			}
			else if(command == "xcodeproj") {
				bool ret = false;
				String name = project_path;
				auto ipa_it = arguments.find("ipa");
				auto platform_it = arguments.find("platform");
				if(i + 1 < argc && argv[i + 1][0] != '-') name += argv[++i];
				else if(project_name && platform_it) name += project_name + String::tformat("_{0}.xcodeproj", platform_it->data);
				else if(ipa_it) name += project_name + "_ios.xcodeproj";
				else if(project_name) name += project_name + ".xcodeproj";
				else name.clear();
				if(name) {
					TS_LOGF(Verbose, "Creating \"%s\"\n", name.get());
					if(platform_it) {
						if(platform_it->data == "ios") {
							if((!ipa_it || !ipa_it->data) && project_name) arguments.append(String("ipa"), project_name);
							ret = create_xcodeproj_ios(arguments, name);
						} else if(platform_it->data == "tvos") {
							if((!ipa_it || !ipa_it->data) && project_name) arguments.append(String("ipa"), project_name);
							ret = create_xcodeproj_tvos(arguments, name);
						} else {
							TS_LOGF(Error, "%s: unknown platform \"%s\"\n", argv[0], platform_it->data.get());
						}
					} else if(ipa_it) {
						if(!ipa_it->data && project_name) arguments.append(String("ipa"), project_name);
						ret = create_xcodeproj_ios(arguments, name);
					} else {
						ret = create_xcodeproj(arguments, name);
					}
				} else {
					TS_LOGF(Error, "%s: unknown project name\n", argv[0]);
				}
				if(!ret) {
					if(makefile_name) TS_LOGF(Error, "%s: can't create xcodeproj from \"%s\"\n", argv[0], makefile_name.get());
					else TS_LOGF(Error, "%s: can't create xcodeproj\n", argv[0]);
					print_args(arguments);
					return 1;
				}
			}
			else if(command == "gradle") {
				bool ret = false;
				String name = project_path;
				if(i + 1 < argc && argv[i + 1][0] != '-') name += argv[++i];
				else if(project_name) name += project_name + ".gradle";
				else name.clear();
				if(name) {
					TS_LOGF(Verbose, "Creating \"%s\"\n", name.get());
					if(!arguments.find("apk") && project_name) arguments.append(String("apk"), project_name);
					ret = create_gradle_and(arguments, name);
				} else {
					TS_LOGF(Error, "%s: unknown project name\n", argv[0]);
				}
				if(!ret) {
					if(makefile_name) TS_LOGF(Error, "%s: can't create gradle from \"%s\"\n", argv[0], makefile_name.get());
					else TS_LOGF(Error, "%s: can't create gradle\n", argv[0]);
					print_args(arguments);
					return 1;
				}
			}
			else if(command == "csproj") {
				bool ret = false;
				String name = project_path;
				if(i + 1 < argc && argv[i + 1][0] != '-') name += argv[++i];
				else if(project_name) name += project_name + ".csproj";
				else name.clear();
				if(name) {
					TS_LOGF(Verbose, "Creating \"%s\"\n", name.get());
					ret = create_csproj(arguments, name);
				} else {
					TS_LOGF(Error, "%s: unknown project name\n", argv[0]);
				}
				if(!ret) {
					TS_LOGF(Error, "%s: can't create csproj\n", argv[0]);
					print_args(arguments);
					return 1;
				}
			}
			else if(command == "java") {
				bool ret = false;
				auto apk_it = arguments.find("apk");
				auto platform_it = arguments.find("platform");
				TS_LOGF(Verbose, "Creating \"%s\"\n", project_path.get());
				if(platform_it) {
					if(platform_it->data == "and") {
						if((!apk_it || !apk_it->data) && project_name) arguments.append(String("apk"), project_name);
						ret = create_gradle_java_and(arguments, project_path);
					} else {
						TS_LOGF(Error, "%s: unknown platform \"%s\"\n", argv[0], platform_it->data.get());
					}
				} else if(apk_it) {
					if(!apk_it->data && project_name) arguments.append(String("apk"), project_name);
					ret = create_gradle_java_and(arguments, project_path);
				} else {
					ret = create_gradle_java(arguments, project_path);
				}
				if(!ret) {
					TS_LOGF(Error, "%s: can't create gradle\n", argv[0]);
					print_args(arguments);
					return 1;
				}
			}
			else if(command == "cargo") {
				TS_LOGF(Verbose, "Creating \"%s\"\n", project_path.get());
				if(!create_cargo(arguments, project_path)) {
					TS_LOGF(Error, "%s: can't create cargo\n", argv[0]);
					print_args(arguments);
					return 1;
				}
			}
			else if(command == "swift") {
				bool ret = false;
				auto ipa_it = arguments.find("ipa");
				auto platform_it = arguments.find("platform");
				if(ipa_it || platform_it) {
					String name = project_path;
					if(project_name && platform_it) name += project_name + String::tformat("_{0}.xcodeproj", platform_it->data);
					else if(ipa_it) name += project_name + "_ios.xcodeproj";
					else if(project_name) name += project_name + ".xcodeproj";
					else name.clear();
					TS_LOGF(Verbose, "Creating \"%s\"\n", name.get());
					if(name) {
						if(platform_it) {
							if(platform_it->data == "ios") {
								if((!ipa_it || !ipa_it->data) && project_name) arguments.append(String("ipa"), project_name);
								ret = create_xcodeproj_swift_ios(arguments, name);
							} else {
								TS_LOGF(Error, "%s: unknown platform \"%s\"\n", argv[0], platform_it->data.get());
							}
						} else if(ipa_it) {
							if(!ipa_it->data && project_name) arguments.append(String("ipa"), project_name);
							ret = create_xcodeproj_swift_ios(arguments, name);
						}
					}
				} else {
					TS_LOGF(Verbose, "Creating \"%s\"\n", project_path.get());
					ret = create_swift(arguments, project_path);
				}
				if(!ret) {
					TS_LOGF(Error, "%s: can't create swift\n", argv[0]);
					print_args(arguments);
					return 1;
				}
			}
			else if(command == "python" || command == "py") {
				
			}
			else if(command == "javascript" || command == "js") {
				
			}
			else {
				TS_LOGF(Error, "%s: unknown argument \"%s\"\n", argv[0], command.get());
				return 1;
			}
		}
		
		// load makefile
		else {
			makefile_name = String(argv[i]);
			#if _WIN32
				if(makefile_name.size() > 5 && makefile_name.begins("/mnt/")) {
					makefile_name = makefile_name.replace("/mnt", "");
					makefile_name[0] = makefile_name[1];
					makefile_name[1] = ':';
				}
			#endif
			if(!load_makefile(arguments, makefile_name)) {
				TS_LOGF(Error, "%s: can't load \"%s\" Makefile\n", argv[0], makefile_name.get());
				return 1;
			}
			project_path = makefile_name.dirname();
			if(!project_path || project_path == "./") {
				project_path = Directory::getCurrentDirectory() + "/";
			}
			if(project_path && project_path.back() == '/') {
				project_name = project_path.substring(0, project_path.size() - 1);
				project_name = project_name.basename();
				if(project_name && !arguments.find("name")) {
					arguments.append(String("name"), project_name);
				}
			}
		}
	}
	
	return 0;
}

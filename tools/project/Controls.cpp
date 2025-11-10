// Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimBlob.h>
#include <core/TellusimSystem.h>
#include <interface/TellusimDialogs.h>

#if _WIN32
	#include <system/TellusimWindows.h>
#endif

#include "Controls.h"

/*
 */
int32_t main(int32_t argc, char **argv);

/*
 */
namespace Tellusim {
	
	/*
	 */
	Controls::Controls(int32_t argc, char **argv) : ControlApp(argc, argv) {
		
		// hide console window
		#if _WIN32
			Windows::setConsoleHidden(true);
		#endif
	}
	
	/*
	 */
	bool Controls::create() {
		
		// set console log
		log_func = Log::getCallback();
		log_data = Log::getCallbackData();
		Log::setCallback([](Log::Level level, uint64_t time, const char *str, void *data) {
			Controls *controls = (Controls*)data;
			if(level != Log::Level::Verbose) controls->console_log += str;
			if(controls->log_func) controls->log_func(level, time, str, controls->log_data);
			return false;
		}, this);
		
		// create app
		return ControlApp::create("Tellusim Project Tool " TS_APP_VERSION);
	}
	
	/*
	 */
	int32_t Controls::run() {
		
		// window icon
		Image tellusim_image;
		#include "interface/tellusim.blob"
		Blob tellusim_blob = Blob(tellusim_blob_src);
		if(tellusim_image.load(tellusim_blob)) {
			window.setIcon(tellusim_image);
		}
		
		// create fonts
		#include "interface/sansb.blob"
		canvas.addFont("sansb.ttf", sansb_blob_src);
		
		// create tooltip
		ControlTooltip tooltip(&root);
		
		// create title
		ControlText title_text(&dialog, window.getTitle());
		title_text.setAlign(Control::AlignCenterX | Control::AlignTop);
		title_text.setColor(Color("#f71e46"));
		title_text.setFontName("sansb.ttf");
		title_text.setMargin(16.0f, 0.0f);
		title_text.setFontSize(24);
		
		// create grid
		ControlGrid grid(&dialog, 2, 8.0f, 8.0f);
		grid.setAlign(Control::AlignExpandX | Control::AlignTop);
		grid.setMargin(0.0f, 0.0f, 16.0f, 16.0f);
		
		// template project
		ControlText template_text(&grid, "Template");
		template_text.setAlign(Control::AlignRight | Control::AlignCenterY);
		
		#if TS_CORE
			ControlCombo template_combo(&grid, { "Core", "Canvas", "Compute", "Fragment" });
		#else
			ControlCombo template_combo(&grid, { "Core", "Engine", "Canvas", "Compute", "Fragment" });
		#endif
		template_combo.setAlign(Control::AlignExpandX | Control::AlignCenterY);
		
		// language selector
		ControlText language_text(&grid, "Language");
		language_text.setAlign(Control::AlignRight | Control::AlignCenterY);
		
		#if _MACOS
			ControlCombo language_combo(&grid, { "C++", "C#", "Java", "Rust", "Swift", "Python", "JavaScript" });
		#else
			ControlCombo language_combo(&grid, { "C++", "C#", "Java", "Rust", "Python", "JavaScript" });
		#endif
		language_combo.setAlign(Control::AlignExpandX | Control::AlignCenterY);
		
		// platform selector
		ControlText platform_text(&grid, "Platform");
		platform_text.setAlign(Control::AlignRight | Control::AlignCenterY);
		
		#if _MACOS
			ControlCombo platform_cpp_combo(&grid, { "Desktop", "Android", "iOS", "tvOS", "Web" });
		#else
			ControlCombo platform_cpp_combo(&grid, { "Desktop", "Android", "Web" });
		#endif
		platform_cpp_combo.setAlign(Control::AlignExpandX | Control::AlignCenterY);
		
		ControlCombo platform_java_combo(&grid, { "Desktop", "Android" });
		platform_java_combo.setAlign(Control::AlignExpandX | Control::AlignCenterY);
		
		ControlCombo platform_swift_combo(&grid, { "Desktop", "iOS" });
		platform_swift_combo.setAlign(Control::AlignExpandX | Control::AlignCenterY);
		
		// project name
		ControlText project_text(&grid, "Project Name");
		project_text.setAlign(Control::AlignRight | Control::AlignCenterY);
		
		ControlEdit project_edit(&grid, "TSProject");
		project_edit.setAlign(Control::AlignExpandX | Control::AlignCenterY);
		
		// package name
		ControlText package_text(&grid, "Package Name");
		package_text.setAlign(Control::AlignRight | Control::AlignCenterY);
		
		ControlEdit package_edit(&grid, "TSApplication");
		package_edit.setAlign(Control::AlignExpandX | Control::AlignCenterY);
		
		// binary name
		ControlText target_text(&grid, "Binary Name");
		target_text.setAlign(Control::AlignRight | Control::AlignCenterY);
		
		ControlEdit target_edit(&grid, "main");
		target_edit.setAlign(Control::AlignExpandX | Control::AlignCenterY);
		
		// project selector
		Control projects_spacer(&grid);
		ControlGrid projects_grid(&grid, 1, 8.0f, 8.0f);
		projects_grid.setAlign(Control::AlignLeft | Control::AlignTop);
		
		ControlCheck cmake_check(&projects_grid, "CMake");
		ControlCheck makefile_check(&projects_grid, "Makefile");
		ControlCheck vcxproj_check(&projects_grid, "VCXProj");
		#if _MACOS
			ControlCheck xcodeproj_check(&projects_grid, "Xcodeproj");
			ControlCheck swift_check(&projects_grid, "SwiftPM");
		#endif
		ControlCheck gradle_check(&projects_grid, "Gradle");
		ControlCheck csproj_check(&projects_grid, "CSProj");
		ControlCheck cargo_check(&projects_grid, "Cargo");
		
		// create tooltips
		tooltip.addTooltip(template_combo, "Select template type");
		tooltip.addTooltip(language_combo, "Select programming language");
		tooltip.addTooltip(platform_cpp_combo, "Select target platform");
		tooltip.addTooltip(platform_java_combo, "Select target platform");
		tooltip.addTooltip(platform_swift_combo, "Select target platform");
		tooltip.addTooltip(project_edit, "Enter the project name");
		tooltip.addTooltip(package_edit, "Enter the package name");
		tooltip.addTooltip(target_edit, "Enter the binary name");
		tooltip.addTooltip(cmake_check, "Create CMake project");
		tooltip.addTooltip(makefile_check, "Create Makefile project");
		tooltip.addTooltip(vcxproj_check, "Create Visual Studio project");
		#if _MACOS
			tooltip.addTooltip(xcodeproj_check, "Create Xcode project");
			tooltip.addTooltip(swift_check, "Create Swift project");
		#endif
		tooltip.addTooltip(gradle_check, "Create Gradle project");
		tooltip.addTooltip(csproj_check, "Create C# project");
		tooltip.addTooltip(cargo_check, "Create Rust (Cargo) project");
		
		// create button
		ControlButton create_button(&dialog, "Create Project");
		create_button.setAlign(Control::AlignExpandX | Control::AlignBottom);
		create_button.setFontName("sansb.ttf");
		create_button.setSize(0.0f, 28.0f);
		
		// close button
		ControlButton close_button(&dialog, "&#215;");
		close_button.setAlign(Control::AlignOverlap | Control::AlignRightTop);
		close_button.setPosition(6.0f, 14.0f);
		close_button.setFontName("sansb.ttf");
		close_button.setFontSize(24);
		close_button.setBackground(false);
		close_button.setClickedCallback([&](ControlButton button) {
			window.stop();
		});
		
		// check callbacks
		ControlCheck::ClickedCallback check_clicked = [&](ControlCheck check) {
			const String &language = language_combo.getText();
			bool show_create = (language == "Python" || language == "JavaScript");
			show_create |= (cmake_check.isEnabled() && cmake_check.isChecked());
			show_create |= (makefile_check.isEnabled() && makefile_check.isChecked());
			show_create |= (vcxproj_check.isEnabled() && vcxproj_check.isChecked());
			#if _MACOS
				show_create |= (xcodeproj_check.isEnabled() && xcodeproj_check.isChecked());
				show_create |= (swift_check.isEnabled() && swift_check.isChecked());
			#endif
			show_create |= (gradle_check.isEnabled() && gradle_check.isChecked());
			show_create |= (csproj_check.isEnabled() && csproj_check.isChecked());
			show_create |= (cargo_check.isEnabled() && cargo_check.isChecked());
			if(project_edit.isEnabled()) show_create &= (bool)project_edit.getText();
			if(package_edit.isEnabled()) show_create &= (bool)package_edit.getText();
			if(target_edit.isEnabled()) show_create &= (bool)target_edit.getText();
			create_button.setDisabled(!show_create);
			frame_counter = 2;
		};
		cmake_check.setClickedCallback(check_clicked);
		makefile_check.setClickedCallback(check_clicked);
		vcxproj_check.setClickedCallback(check_clicked);
		#if _MACOS
			xcodeproj_check.setClickedCallback(check_clicked);
			swift_check.setClickedCallback(check_clicked);
		#endif
		gradle_check.setClickedCallback(check_clicked);
		csproj_check.setClickedCallback(check_clicked);
		cargo_check.setClickedCallback(check_clicked);
		
		// combo callbacks
		ControlCombo::ChangedCallback combo_changed = [&](ControlCombo combo) {
			
			// current language
			const String &language = language_combo.getText();
			bool show_platform_cpp = (language == "C++");
			bool show_platform_java = (language == "Java");
			bool show_platform_swift = (language == "Swift");
			
			// select platform
			platform_cpp_combo.setEnabled(show_platform_cpp);
			platform_java_combo.setEnabled(show_platform_java);
			platform_swift_combo.setEnabled(show_platform_swift);
			platform_text.setEnabled(show_platform_cpp || show_platform_java || show_platform_swift);
			
			// current platform
			String platform = platform_cpp_combo.getText();
			if(platform_java_combo.isEnabled()) platform = platform_java_combo.getText();
			if(platform_swift_combo.isEnabled()) platform = platform_swift_combo.getText();
			
			// update controls
			bool show_package = (platform != "Desktop" && platform != "Web");
			bool show_target = (language != "Java" && language != "Python" && language != "JavaScript" && !(language == "Swift" && platform == "iOS"));
			package_text.setEnabled(show_package);
			package_edit.setEnabled(show_package);
			target_text.setEnabled(show_target);
			target_edit.setEnabled(show_target);
			
			// update projects
			bool show_cmake = false;
			bool show_makefile = false;
			bool show_vcxproj = false;
			bool show_xcodeproj = false;
			bool show_swift = false;
			bool show_gradle = false;
			bool show_csproj = false;
			bool show_cargo = false;
			if(language == "C++") {
				show_makefile = true;
				if(platform == "Desktop") {
					show_cmake = true;
					show_vcxproj = true;
					show_xcodeproj = true;
				} else if(platform == "Android") {
					show_gradle = true;
				} else if(platform == "iOS" || platform == "tvOS") {
					show_xcodeproj = true;
				}
			}
			else if(language == "C#") {
				show_csproj = true;
			}
			else if(language == "Java") {
				show_gradle = true;
			}
			else if(language == "Rust") {
				show_cargo = true;
			}
			else if(language == "Swift") {
				if(platform == "iOS") {
					show_xcodeproj = true;
				} else {
					show_swift = true;
				}
			}
			cmake_check.setEnabled(show_cmake);
			makefile_check.setEnabled(show_makefile);
			vcxproj_check.setEnabled(show_vcxproj);
			#if _MACOS
				xcodeproj_check.setEnabled(show_xcodeproj);
				swift_check.setEnabled(show_swift);
			#endif
			gradle_check.setEnabled(show_gradle);
			csproj_check.setEnabled(show_csproj);
			cargo_check.setEnabled(show_cargo);
			TS_UNUSED(show_vcxproj);
			TS_UNUSED(show_xcodeproj);
			TS_UNUSED(show_swift);
			
			// update button
			check_clicked(ControlCheck::null);
		};
		language_combo.setChangedCallback(combo_changed);
		platform_cpp_combo.setChangedCallback(combo_changed);
		platform_java_combo.setChangedCallback(combo_changed);
		platform_swift_combo.setChangedCallback(combo_changed);
		
		// button callback
		create_button.setClickedCallback([&](ControlButton) {
			String directory = config.gets("directory");
			DialogDirectory dialog("Select Target Directory", directory);
			if(dialog.run(DialogDirectory::FlagMouse) == DialogDirectory::ResultOk) {
				
				Array<String> args;
				args.append(String("project"));
				args.append(String("-v"));
				
				// force creation
				if(app.isArgument("force") || app.isArgument("f")) args.append(String("-f"));
				
				// project name
				String project = dialog.getDirectory() + "/" + project_edit.getText();
				
				// template
				const String &type = template_combo.getText();
				if(type == "Core") args.append(String("-core"));
				else if(type == "Engine") args.append(String("-engine"));
				else if(type == "Canvas") args.append(String("-canvas"));
				else if(type == "Compute") args.append(String("-compute"));
				else if(type == "Fragment") args.append(String("-fragment"));
				args.append(project);
				
				// platform
				String platform = platform_cpp_combo.getText();
				if(platform_java_combo.isEnabled()) platform = platform_java_combo.getText();
				if(platform_swift_combo.isEnabled()) platform = platform_swift_combo.getText();
				if(platform != "Desktop" && platform != "Web") {
					
					// package
					if(platform == "Android") args.append(String("-apk"));
					else if(platform == "iOS") args.append(String("-ipa"));
					else if(platform == "tvOS") args.append(String("-ipa"));
					args.append(package_edit.getText());
					
					// platform
					if(platform == "iOS" || platform == "tvOS") {
						args.append(String("-platform"));
						if(platform == "iOS") args.append(String("ios"));
						else if(platform == "tvOS") args.append(String("tvos"));
					}
				}
				else if(platform == "Web") {
					args.append(String("-platform"));
					args.append(String("ems"));
				}
				
				// target
				args.append(String("-target"));
				args.append(target_edit.getText());
				
				// language
				const String &language = language_combo.getText();
				if(language == "Java") args.append(String("-java"));
				if(language == "Python") args.append(String("-python"));
				if(language == "JavaScript") args.append(String("-javascript"));
				
				// project
				#define TS_DECLARE_CHECK(NAME) if(NAME ## _check.isEnabled() && NAME ## _check.isChecked()) args.append(String("-" #NAME));
				TS_DECLARE_CHECK(cmake)
				TS_DECLARE_CHECK(makefile)
				if(args && args.back() == "-makefile") {
					#if _WIN32
						if(platform == "Desktop") args.append(String("Makefile.win"));
					#endif
					if(platform == "Web") args.append(String("Makefile.ems"));
				}
				TS_DECLARE_CHECK(vcxproj)
				#if _MACOS
					TS_DECLARE_CHECK(xcodeproj)
					TS_DECLARE_CHECK(swift)
					if(language == "Swift" && args.back() == "-xcodeproj") args.back() = "-swift";
				#endif
				if(language != "Java") {
					TS_DECLARE_CHECK(gradle)
				}
				TS_DECLARE_CHECK(csproj)
				TS_DECLARE_CHECK(cargo)
				#undef TS_DECLARE_CHECK
				
				// create arguments
				Array<char*> argv(args.size());
				for(uint32_t i = 0; i < args.size(); i++) {
					argv[i] = args[i].get();
				}
				
				// run project
				console_log.clear();
				if(main(argv.size(), argv.get())) {
					DialogMessage dialog("Can't create project", console_log);
					dialog.run(DialogMessage::FlagError | DialogMessage::FlagClose | DialogMessage::FlagMouse);
				} else {
					config.set("directory", dialog.getDirectory());
					#if _WIN32
						System::open(project.replace("/", "\\"));
					#else
						System::open(project);
					#endif
				}
			}
		});
		
		// update controls
		combo_changed(ControlCombo::null);
		
		// run the app
		bool is_resized = false;
		return ControlApp::run([&]() {
			if(!is_resized) {
				is_resized = true;
				dialog.setSize(dialog.getControlsSize());
			}
			if(tooltip.isTooltip()) {
				frame_counter = 30;
			}
			return true;
		});
	}
}

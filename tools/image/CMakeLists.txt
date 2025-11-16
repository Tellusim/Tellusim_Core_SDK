cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

find_program(HAS_CCACHE "ccache")
if(HAS_CCACHE)
	set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif()

if(WIN32)
	add_compile_options(/bigobj /D_CRT_SECURE_NO_WARNINGS /fp:fast)
	add_compile_options(/MD /W4 /Os /EHsc /D_WIN32_WINNT=0x0603)
elseif(UNIX AND NOT APPLE)
	add_compile_options(-Wall -Os)
	add_compile_options(-Wno-undefined-var-template -Wno-class-memaccess)
	add_compile_options(-Wno-maybe-uninitialized -Wno-enum-compare)
elseif(UNIX AND APPLE)
	add_compile_options(-Wall -Wno-undefined-var-template -Os)
endif()

include_directories(
	../../include
	../../plugins
	../../samples
	../../plugins/formats/webp/extern
)

if(WIN32)
	add_definitions(-D_WIN64=1)
	link_directories(
		../../lib/windows/vs170arm64
	)
elseif(UNIX AND NOT APPLE)
	add_definitions(-D_LINUX=1)
	link_directories(
		../../lib/linux/arm64
		../../plugins/formats/webp/extern/lib/linux/arm64
	)
elseif(UNIX AND APPLE)
	add_definitions(-D_MACOS=1)
	link_directories(
		../../lib/macos/arm64
		../../plugins/formats/webp/extern/lib/linux/arm64
	)
endif()

set(SRCS
	image.cpp
	Plugins.cpp
)

project(image)
add_executable(image ${SRCS})
set_target_properties(image PROPERTIES DEBUG_POSTFIX "_arm64d")
set_target_properties(image PROPERTIES RELEASE_POSTFIX "_arm64")
set_target_properties(image PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
target_link_libraries(image debug Tellusim_arm64d optimized Tellusim_arm64)

if(WIN32)
	target_link_libraries(image)
elseif(UNIX AND NOT APPLE)
	target_link_libraries(image webp)
elseif(UNIX AND APPLE)
	target_link_libraries(image webp)
endif()

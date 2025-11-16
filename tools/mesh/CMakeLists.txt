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
	../../plugins/formats/draco/extern
	../../plugins/formats/webp/extern
)

if(WIN32)
	add_definitions(-D_WIN64=1)
	link_directories(
		../../lib/windows/vs170arm64
		../../plugins/formats/draco/extern/lib/windows/arm64
		../../plugins/formats/webp/extern/lib/windows/arm64
	)
elseif(UNIX AND NOT APPLE)
	add_definitions(-D_LINUX=1)
	link_directories(
		../../lib/linux/arm64
	)
elseif(UNIX AND APPLE)
	add_definitions(-D_MACOS=1)
	link_directories(
		../../lib/macos/arm64
	)
endif()

set(SRCS
	mesh.cpp
	Plugins.cpp
)

project(mesh)
add_executable(mesh ${SRCS})
set_target_properties(mesh PROPERTIES DEBUG_POSTFIX "_arm64d")
set_target_properties(mesh PROPERTIES RELEASE_POSTFIX "_arm64")
set_target_properties(mesh PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
target_link_libraries(mesh debug Tellusim_arm64d optimized Tellusim_arm64)

if(WIN32)
	target_link_libraries(mesh)
elseif(UNIX AND NOT APPLE)
	target_link_libraries(mesh)
elseif(UNIX AND APPLE)
	target_link_libraries(mesh)
endif()

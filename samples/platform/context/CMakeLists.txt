cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)

find_program(HAS_CCACHE "ccache")
if(HAS_CCACHE)
	set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif()

if(WIN32)
	add_compile_options(/D_CRT_SECURE_NO_WARNINGS /fp:fast)
	add_compile_options(/MD /MP /W4 /Os /EHsc /D_WIN32_WINNT=0x0603)
elseif(UNIX)
	add_compile_options(-Wall -Wno-undefined-var-template -Os)
endif()

include_directories(
	../../../include
	../../../plugins
	../../../samples
)

if(WIN32)
	add_definitions(-D_WIN64=1)
	link_directories(
		../../../lib/windows/vs170x64
	)
elseif(UNIX AND NOT APPLE)
	add_definitions(-D_LINUX=1)
	link_directories(
		../../../lib/linux/x64
	)
elseif(UNIX AND APPLE)
	add_definitions(-D_MACOS=1)
	link_directories(
		../../../lib/macos/x64
	)
endif()

set(SRCS
	main.cpp
)

project(context)
add_executable(main ${SRCS})
set_target_properties(main PROPERTIES DEBUG_POSTFIX "_x64d")
set_target_properties(main PROPERTIES RELEASE_POSTFIX "_x64")
set_target_properties(main PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
target_link_libraries(main debug Tellusim_x64d optimized Tellusim_x64)

if(NOT WIN32)
	target_link_libraries(main)
endif()

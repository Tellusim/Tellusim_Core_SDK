cmake_minimum_required(VERSION 3.5.0)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-D_ANDROID=1)
add_compile_options(-Wall -Wno-null-dereference -Wno-undefined-var-template -Os)

include_directories(
	../../../../include
	../../../../plugins
	../../../../samples
	../extern
)

link_directories(
	../../../../lib/android/arm64
	../extern/lib/android/arm64
)

set(SRCS
	../main.cpp
	../source/TellusimRmlUi.cpp
)

project(tsInterfaceRmlUi)
add_library(main SHARED ${SRCS})
target_link_libraries(main android log)
target_link_libraries(main debug Tellusim_arm64d optimized Tellusim_arm64)
target_link_libraries(main rmlui freetype)

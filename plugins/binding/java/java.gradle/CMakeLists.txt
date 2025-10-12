cmake_minimum_required(VERSION 3.5.0)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-D_ANDROID=1)
add_compile_options(-Wall -Wno-null-dereference -Wno-undefined-var-template -Os)

include_directories(
	../../../../include
	../../../../plugins
	../../../../samples
)

link_directories(
	../../../../lib/android/arm64
)

set(SRCS
	../source/TellusimJNIBase.cpp
	../source/TellusimJNIMath.cpp
	../source/TellusimJNIAPI.cpp
)

project(@$(ECHO) y "Making $(APK).apk"
@$(BUILD) $(APK) $(ICON) $(APKARCH) $(SDK) $(TARGET) $(ASSETS))
add_library(TellusimJNI_$(ARCH) SHARED ${SRCS})
target_link_libraries(TellusimJNI_$(ARCH) android log)
target_link_libraries(TellusimJNI_$(ARCH) debug Tellusim_arm64d optimized Tellusim_arm64)
target_link_libraries(TellusimJNI_$(ARCH))

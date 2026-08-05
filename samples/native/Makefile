ifeq "$(shell uname -s)" "Linux"
	TESTS = \
		gl_device \
		gl_glfw_window \
		gl_gtk3_window \
		gl_runtime \
		gl_sdl_window \
		gles_device \
		gles_runtime \
		vk_device \
		vk_glfw_window \
		vk_gtk3_window \
		vk_pipeline \
		vk_runtime \
		vk_sdl_window \
		vk_spirv \
		vk_swap_chain
else ifeq "$(shell uname -s)" "Darwin"
	TESTS = \
		mtl_pipeline \
		mtl_runtime \
		mtl_window
else
 	$(error Unknown platform $(shell uname -s))
endif

include ../Makefile

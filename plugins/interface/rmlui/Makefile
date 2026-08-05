#FLAGS = -DRMLUI_PATH="./"

SRCS = main.cpp \
	source/TellusimRmlUi.cpp

ifeq "$(shell uname -s)" "Linux"
	LIBS += -Lextern/lib/linux/$(ARCH)
else ifeq "$(shell uname -s)" "Darwin"
	LIBS += -Lextern/lib/macos/$(ARCH)
endif

LIBS += -lrmlui -lfreetype

include ../../Makefile.unx.mk

CFLAGS += -std=c++17

blob:
	@ts_blob -src source/TellusimRmlUi.shader

TARGET = librmlui.a

PREFIX = RmlUi.git

SRC = $(PREFIX)/Source/Core

SRCS = $(shell find $(SRC) -name \*.cpp -print0 | sort -z | xargs -r0)

CFLAGS += -std=c++17 -I$(PREFIX)/Include -DRMLUI_STATIC_LIB=1 -DRMLUI_NO_THIRDPARTY_CONTAINERS=1 -DRMLUI_MATRIX_ROW_MAJOR=1 -DRMLUI_FONT_ENGINE_FREETYPE=1

CFLAGS += -I$(CLAYROOT)/extern/include

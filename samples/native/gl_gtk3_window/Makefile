SRCS = main.cpp

FLAGS += -I$(TSROOT)/plugins/platform/opengl/extern

FLAGS += `pkg-config --cflags gtk+-3.0`
LIBS += `pkg-config --libs gtk+-3.0`

include ../../Makefile.unx.mk

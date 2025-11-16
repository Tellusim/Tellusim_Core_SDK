SRCS = main.cpp

FLAGS += -I$(TSROOT)/plugins/platform/vulkan/extern

FLAGS += `pkg-config --cflags gtk+-3.0`
LIBS += `pkg-config --libs gtk+-3.0`

include ../../Makefile.unx.mk

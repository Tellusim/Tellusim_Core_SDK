SRCS = main.cpp \
	source/TellusimONNX.cpp

ifeq "$(shell uname -s)" "Linux"
	LIBS += -Lextern/lib/linux/$(ARCH) -lonnxpb
else ifeq "$(shell uname -s)" "Darwin"
	LIBS += -Lextern/lib/macos/$(ARCH) -lonnxpb
endif

include ../../Makefile.unx.mk

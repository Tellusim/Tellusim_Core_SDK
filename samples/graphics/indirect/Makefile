SRCS = main.cpp

ifeq "$(shell uname -s)" "Darwin"
	FLAGS = -ObjC++ -fobjc-arc
	LIBS += -framework Cocoa -framework Metal
endif

include ../../Makefile.unx.mk

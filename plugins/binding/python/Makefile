# Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/

TSROOT = $(CURDIR)/../../..

#
# Platform configuration
#
ifeq "$(shell uname -s)" "Linux"
	TARGET = libTellusimPy_$(ARCH)$(POSTFIX).so
	CFLAGS = $(shell python3-config --includes)
	LDFLAGS = $(shell python3-config --libs --embed)
	LDFLAGS += -Wl,-rpath,./,-rpath,../../../source,-rpath,../../../lib/linux/$(ARCH)
else ifeq "$(shell uname -s)" "Darwin"
	TARGET = libTellusimPy_$(ARCH)$(POSTFIX).dylib
	CFLAGS = $(shell python3-config --includes)
	LDFLAGS = -L$(shell python3-config --prefix)/lib
	LDFLAGS += $(shell python3-config --libs --embed)
	LDFLAGS += -Wl,-w,-rpath,@loader_path/,-rpath,@loader_path/../../../source/,-rpath,@loader_path/../../../lib/macos/$(ARCH)/
else
 	$(error Unknown platform $(shell uname -s))
endif

#
# Default configuration
#
LDFLAGS += -shared

#
# Sources
#
SRCS = source/TellusimPyBase.cpp \
	source/TellusimPyMath.cpp \
	source/TellusimPyAPI.cpp

#
# Build
#
include $(TSROOT)/build/Makefile.unx.mk

#
# Install
#
install:
	@$(ECHO) b "Install $(TARGET)"
	@ln -f -s ../plugins/binding/python/$(TARGET) $(TSROOT)/bin/tellusim$(POSTFIX).so

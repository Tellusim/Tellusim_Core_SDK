# Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/

TSROOT = $(CURDIR)/../../..

#
# Platform configuration
#
ifeq "$(shell uname -s)" "Linux"
	TARGET = libTellusimC_$(ARCH)$(POSTFIX).so
	CLDFLAGS = -Wl,-rpath,./,-rpath,../../../source,-rpath,../../../lib/linux/$(ARCH)
else ifeq "$(shell uname -s)" "Darwin"
	TARGET = libTellusimC_$(ARCH)$(POSTFIX).dylib
	CLDFLAGS = -Wl,-rpath,@loader_path/,-rpath,@loader_path/../../../source/,-rpath,@loader_path/../../../lib/macos/$(ARCH)/
else
 	$(error Unknown platform $(shell uname -s))
endif

#
# Default configuration
#
LDFLAGS = -shared $(CLDFLAGS)

#
# Sources
#
SRCS = source/TellusimCBase.cpp \
	source/TellusimCMath.cpp \
	source/TellusimCAPI.cpp

#
# Main target
#
MAIN_TARGET = main$(POSTFIX)
MAIN_OBJS = main.o

#
# Clear targets
#
CLEAN = $(MAIN_TARGET) $(MAIN_OBJS)

#
# Build
#
include $(TSROOT)/build/Makefile.unx.mk

#
# Main
#
all: $(MAIN_TARGET)

.c.o:
	@echo `basename $<`
	@$(CC) $(ARCHFLAGS) -Wall -Wextra -Os -c -o $@ $^

$(MAIN_TARGET): $(MAIN_OBJS) $(TARGET)
	@$(CC) $(ARCHFLAGS) $(CLDFLAGS) -o $@ $^ -lm
	@$(ECHO) g "Done `basename $@`"

#
# Install
#
install:
	@$(ECHO) b "Install $(TARGET)"
	@ln -f -s ../plugins/binding/capi/$(TARGET) $(TSROOT)/bin/

# Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/

TSROOT = $(CURDIR)/../../..

SWC = swiftc

#
# Platform configuration
#
ifeq "$(shell uname -s)" "Linux"
	TARGET = libTellusimObjC_$(ARCH)$(POSTFIX).so
	LDFLAGS = -Wl,-rpath,./,-rpath,../../../source,-rpath,../../../lib/linux/$(ARCH)
else ifeq "$(shell uname -s)" "Darwin"
	TARGET = libTellusimObjC_$(ARCH)$(POSTFIX).dylib
	LDFLAGS = -Wl,-rpath,@loader_path/,-rpath,@loader_path/../../../source/,-rpath,@loader_path/../../../lib/macos/$(ARCH)/
else
 	$(error Unknown platform $(shell uname -s))
endif

#
# Default configuration
#
CFLAGS = -ObjC++ -fobjc-arc
LDFLAGS += -shared -framework Foundation

#
# Swift configuration
#
SWFLAGS = -Osize -I. -L.

#
# Sources
#
SRCS = source/TellusimObjCBase.cpp \
	source/TellusimObjCMath.cpp \
	source/TellusimObjCAPI.cpp

#
# Module target
#
MODULE_TARGET = libTellusim.a
MODULE_SRCS = source/TellusimSwBase.swift \
	source/TellusimSwMath.swift \
	source/TellusimSwAPI.swift

#
# Main target
#
MAIN_TARGET = main$(POSTFIX)
MAIN_SRCS = main.swift

#
# Clean targets
#
CLEAN = $(MODULE_TARGET) $(MAIN_TARGET) Tellusim.*

#
# Build
#
include $(TSROOT)/build/Makefile.unx.mk

#
# Module
#
$(MODULE_TARGET): $(MODULE_SRCS)
	@$(SWC) $(SWFLAGS) -enable-library-evolution -import-underlying-module -emit-module-interface -emit-module -emit-library -static -module-name Tellusim $(MODULE_SRCS)
	@$(ECHO) g "Done `basename $@`"

#
# Main
#
all: $(MAIN_TARGET)

$(MAIN_TARGET): $(MAIN_SRCS) $(MODULE_TARGET) $(TARGET)
	@$(SWC) $(SWFLAGS) -lTellusimObjC_$(ARCH)$(POSTFIX) $(MODULE_TARGET) -o $@ $(MAIN_SRCS)
	@$(ECHO) g "Done `basename $@`"

#
# Install
#
install:
	@$(ECHO) b "Install $(TARGET)"
	@ln -f -s ../plugins/binding/swift/$(TARGET) $(TSROOT)/bin/

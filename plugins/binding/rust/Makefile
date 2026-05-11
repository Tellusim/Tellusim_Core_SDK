# Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/

RSC = rustc

ARCH = $(shell uname -m)

#
# Debug configuration
#
ifneq "$(debug)" "0"
	POSTFIX := $(POSTFIX)d
	RSFLAGS += -C debuginfo=2
else
	RSFLAGS += -C opt-level=s
	RSFLAGS += -C strip=symbols
endif

#
# Cross architecture
#
ifdef arch
	ARCH = $(arch)
endif
ifeq "$(ARCH)" "x86_64"
	ARCH = x64
else ifeq "$(ARCH)" "armv7l"
	ARCH = armv7
else ifeq "$(ARCH)" "aarch64"
	ARCH = arm64
else ifeq "$(ARCH)" "arm64"
	ARCH = arm64
else
 	$(error Unknown arch $(ARCH))
endif

#
# Library target
#
LIBRARY = libTellusimRS_$(ARCH)$(POSTFIX).rlib

LIBS = -lTellusimC_$(ARCH)$(POSTFIX)

SRCS = source/TellusimRS.rs \
	source/TellusimRSBase.rs \
	source/TellusimRSMath.rs \
	source/TellusimRSAPI.rs

#
# Main target
#
TARGET = main$(POSTFIX)

MAIN = main.rs

LDFLAGS = -L../../../bin -L../capi --extern tellusim=$(LIBRARY)

ifeq "$(shell uname -s)" "Darwin"
	LDFLAGS += -C link-args="-Wl,-rpath,@loader_path/,-rpath,@loader_path/../../../bin/,-rpath,@loader_path/../capi/"
endif

#
# Build rules
#
all: $(TARGET)

$(LIBRARY): $(SRCS)
	@+$(RSC) $(RSFLAGS) -o $@ $(LIBS) $<
	@echo "Done `basename $@`"

$(TARGET): $(MAIN) $(LIBRARY)
	@+$(RSC) $(RSFLAGS) $(LDFLAGS) -o $@ $<
	@echo "Done `basename $@`"

clean:
	@echo "Cleaning `basename $(CURDIR)`"
	@rm -f $(LIBRARY) $(TARGET)

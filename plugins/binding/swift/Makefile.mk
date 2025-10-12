# Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/

SWC = swiftc

ARCH = $(shell uname -m)

#
# Debug configuration
#
ifneq "$(debug)" "0"
	POSTFIX := $(POSTFIX)d
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
# Target
#
TARGET = main$(POSTFIX)

FLAGS = -Osize
FLAGS += -I$(TSROOT)/plugins/binding/swift -L$(TSROOT)/plugins/binding/swift
FLAGS += -lTellusimObjC_$(ARCH)$(POSTFIX) -lTellusim

$(TARGET): $(SRC)
	@$(SWC) $(FLAGS) -o $@ $<
	@echo "Done `basename $@`"

clean:
	@echo "Cleaning `basename $(CURDIR)`"
	@rm -f $(TARGET)

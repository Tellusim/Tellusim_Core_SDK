# Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/

CSC = csc

#
# Platform configuration
#
ifeq "$(shell uname -s)" "Linux"
	CSFLAGS = /langversion:8.0 /define:_LINUX
else ifeq "$(shell uname -s)" "Darwin"
	CSFLAGS = /langversion:8.0 /define:_MACOS
endif

#
# Arch configuration
#
ifeq "$(shell uname -m)" "aarch64"
	CSFLAGS += /define:TS_ARM64
else ifeq "$(shell uname -m)" "arm64"
	CSFLAGS += /define:TS_ARM64
endif

#
# Debug configuration
#
ifneq "$(debug)" "0"
	CSFLAGS += /debug:full /define:TS_DEBUG
	POSTFIX := $(POSTFIX)d
else
	CSFLAGS += /o
endif

#
# Library target
#
LIBRARY = libTellusimCS$(POSTFIX).dll

SRCS = source/TellusimCSBase.cs \
	source/TellusimCSMath.cs \
	source/TellusimCSAPI.cs

#
# Main target
#
TARGET = main$(POSTFIX).exe

MAIN = main.cs

#
# Build rules
#
all: $(TARGET)

$(LIBRARY): $(SRCS)
	@$(CSC) /nologo /target:library $(CSFLAGS) /out:$@ $(SRCS)
	@echo "Done `basename $@`"

$(TARGET): $(MAIN) $(LIBRARY)
	@$(CSC) /nologo /target:exe $(CSFLAGS) /out:$@ /reference:$(LIBRARY) $(MAIN)
	@echo "Done `basename $@`"

run:
	@echo "Running $(TARGET)"
	@mono $(TARGET)

clean:
	@echo "Cleaning `basename $(CURDIR)`"
	@rm -f $(LIBRARY) $(TARGET) *.pdb

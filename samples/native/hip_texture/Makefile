# Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/

HIPCC = hipcc

TSROOT = $(CURDIR)/../../..

DEPENDS = tellusim
ARCH = $(shell uname -m)
ECHO = $(TSROOT)/bin/ts_echo.sh

#
# Cross architecture
#
ifdef arch
	ARCH = $(arch)
endif
ifeq "$(ARCH)" "x86_64"
	ARCH = x64
else
 	$(error Unknown arch $(ARCH))
endif

#
# Debug configuration
#
ifneq "$(debug)" "0"
	CFLAGS += -g
	POSTFIX += d
endif

#
# Default configuration
#
CFLAGS += -I$(TSROOT)/include
CFLAGS += -I$(TSROOT)/samples
LDFLAGS += -L$(TSROOT)/source
LDFLAGS += -L$(TSROOT)/lib/linux/$(ARCH)
LDFLAGS += -lTellusim_$(ARCH)$(POSTFIX)
CFLAGS += -Wno-undefined-var-template -Wno-unused-result

#
# Main target
#
TARGET = main$(POSTFIX)

OBJS = main.o

#
# Build target
#
all: $(TARGET)

main.o: main.cpp
	@$(ECHO) b `basename $<`
	@$(HIPCC) $(CFLAGS) -c -o $@ $^

$(TARGET): $(OBJS)
	@$(HIPCC) $(LDFLAGS) -o $@ $(OBJS)
	@$(ECHO) g "Done `basename $@`"

clean:
	@$(ECHO) r "Cleaning `basename $(CURDIR)`"
	@rm -f $(TARGET) $(OBJS)

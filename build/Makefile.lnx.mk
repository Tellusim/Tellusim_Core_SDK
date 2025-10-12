# Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/
#
# Required environment variables:
#
#  * TARGET - Binary target name
#  * TSROOT - Path to the Tellusim root
#
# Optional command line arguments:
#
#  * debug  - 0, 1
#  * depend - 0, 1

CXX = ccache clang++

DEPEND = .depend
ARCH = $(shell uname -m)
ECHO = $(TSROOT)/bin/ts_echo.sh

#
# Check environment
#
ifndef TARGET
 	$(error TARGET is not defined)
endif
ifndef TSROOT
 	$(error TSROOT is not defined)
endif

#
# Default configuration
#
CFLAGS += -std=c++11 -Wall -Wfloat-conversion -Os -fPIC -ffast-math -fvisibility=hidden
CFLAGS += -D_LINUX=1 -DTS_CORE=1 -I$(TSROOT)/include -I$(TSROOT)/plugins
CFLAGS += -Wno-null-dereference -Wno-undefined-var-template
ifeq "$(ARCH)" "x86_64"
	ARCH=x64
else ifeq "$(ARCH)" "armv7l"
	ARCH=armv7
else ifeq "$(ARCH)" "aarch64"
	ARCH=arm64
else
 	$(error Unknown arch $(ARCH))
endif
LDFLAGS += -L$(TSROOT)/lib/linux/$(ARCH)
LIBS += -lstdc++ -lm -lpthread -ldl

#
# Debugging
#
ifneq "$(debug)" "0"
	POSTFIX := $(POSTFIX)d
	CFLAGS += -g -DTS_DEBUG=1
	LIBS += -lTellusim_$(ARCH)d
else
	CFLAGS += -DNDEBUG=1
	LIBS += -lTellusim_$(ARCH)
endif

#
# Dependencies
#
ifneq "$(depend)" "0"
	DEPS = $(SRCS)
	ifeq "$(depend)" "1"
		CLEAN += $(DEPEND)
	endif
else
	DEPS =
endif

#
# Targets
#
OBJS = $(SRCS:.cpp=.o)

#
# Build target
#
all: $(TARGET)

.cpp.o:
	@echo `basename $<`
	@$(CXX) $(CFLAGS) $(FLAGS) -c -o $@ $<

$(DEPEND):
	@rm -f $@
	@$(ECHO) b "Depend `basename $(CURDIR)`"
	@$(foreach SRC, $(DEPS), $(CXX) $(CFLAGS) $(FLAGS) -MM -MT $(SRC:.cpp=.o) $(SRC) >> $@;)

$(TARGET): $(DEPEND) $(OBJS)
	@$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)
	@$(ECHO) g "Done `basename $(CURDIR)`"

clean:
	@$(ECHO) r "Cleaning `basename $(CURDIR)`"
	@rm -f $(TARGET) $(OBJS) $(CLEAN)

#
# Dependencies
#
ifneq "$(MAKECMDGOALS)" "clean"
 	-include $(DEPEND)
endif

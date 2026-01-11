# Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/
#
# Required environment variables:
#
#  * TARGET - Binary target name
#  * TSROOT - Path to the Tellusim root
#
# Optional command line arguments:
#
#  * arch   - Cross architecture name
#  * debug  - 0, 1
#  * depend - 0, 1

CXX = ccache clang++

DEPEND = .depend
ARCH = $(shell uname -m)
ECHO = $(TSROOT)/bin/ts_echo.sh
SIGN = codesign --force --deep --sign "Mac Developer"

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
# Codesign
#
ifdef sign
	SIGN = $(sign)
endif

#
# Cross architecture
#
ifdef arch
	ARCH = $(arch)
endif

#
# Default configuration
#
CFLAGS += -std=c++11 -Wall -Wfloat-conversion -Os -ffast-math -fvisibility=hidden
CFLAGS += -Wno-null-dereference -Wno-return-std-move -Wno-undefined-var-template
CFLAGS += -D_MACOS=1 -DTS_CORE=1 -I$(TSROOT)/include -I$(TSROOT)/plugins
ifeq "$(ARCH)" "arm64"
	ARCHFLAGS = -target arm64-apple-macos13
	LDFLAGS += $(ARCHFLAGS)
	CFLAGS += $(ARCHFLAGS)
	ARCH=arm64
else ifeq "$(ARCH)" "x86_64"
	ARCHFLAGS = -target x86_64-apple-macos13
	LDFLAGS += $(ARCHFLAGS)
	CFLAGS += $(ARCHFLAGS)
	ARCH=x64
else
 	$(error Unknown arch $(ARCH))
endif
LDFLAGS += -L$(TSROOT)/lib/macos/$(ARCH)
LIBS += -lm

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
	@$(SIGN) $@ 2>&1

run_:
	@$(ECHO) g "Running `basename $(CURDIR)`"
	@./$(TARGET) $(RUN_ARGS)

clean_:
	@$(ECHO) r "Cleaning `basename $(CURDIR)`"
	@rm -f $(TARGET) $(OBJS) $(CLEAN)

%: %_
	@true

#
# Dependencies
#
ifneq "$(MAKECMDGOALS)" "run"
ifneq "$(MAKECMDGOALS)" "clean"
 	-include $(DEPEND)
endif
endif

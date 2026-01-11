# Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/
#
# Required environment variables:
#
#  * TARGET - Binary target name
#  * TSROOT - Path to the Tellusim root
#  * IPA    - iOS package name
#  * ICON   - iOS package icon
#
# Optional environment variables:
#
#  * HTTPS      - 0, 1
#
# Optional command line arguments:
#
#  * debug  - 0, 1
#  * depend - 0, 1

ARCH = arm64
DEPEND = .depend
CXX = ccache clang++
ECHO = $(TSROOT)/bin/ts_echo.sh
BUILD = $(TSROOT)/bin/ts_ipa.sh

#
# Check environment
#
ifndef TARGET
 	$(error TARGET is not defined)
endif
ifndef IPA
 	$(error IPA is not defined)
endif
ifndef ICON
 	$(error ICON is not defined)
endif
ifndef TSROOT
 	$(error TSROOT is not defined)
endif

#
# Default configuration
#
CFLAGS += -std=c++11 -Wall -Wfloat-conversion -Os -ffast-math -fsigned-char -fvisibility=hidden
CFLAGS += -D_TVOS=1 -DTS_CORE=1 -ObjC++ -fobjc-arc -I$(TSROOT)/include -I$(TSROOT)/plugins
CFLAGS += -Wno-return-std-move -Wno-undefined-var-template
LDFLAGS += -L$(TSROOT)/lib/tvos/$(ARCH)
LIBS += -framework Foundation
LIBS += -framework QuartzCore
LIBS += -framework GameController
LIBS += -framework UIKit
LIBS += -framework Metal

#
# Debugging
#
ifneq "$(debug)" "0"
	POSTFIX := $(POSTFIX)d
	CFLAGS += -g -DTS_DEBUG=1
else
	CFLAGS += -DNDEBUG=1
endif

LDFLAGS += -Wl,-all_load $(TSROOT)/lib/tvos/$(ARCH)/libTellusim_arm64$(POSTFIX).a

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
# Platform configuration
#
CFLAGS += -arch arm64
LDFLAGS += -arch arm64
CFLAGS += -mappletvos-version-min=16.0
LDFLAGS += -mappletvos-version-min=16.0

#
# Entry point
#
ifeq "$(findstring dylib, $(TARGET))" ""
	LDFLAGS += -Wl,-e,_clay_main
endif

#
# Controller
#
ifeq "$(CONTROLLER)" "1"
	LIBS += -framework Foundation -framework GameController
	INFO += CONTROLLER
endif

#
# Https
#
ifeq "$(HTTPS)" "1"
	BUILD += -https
endif

#
# System root
#
SYSROOT = $(shell xcrun --sdk appletvos --show-sdk-path)
CFLAGS += -isysroot$(SYSROOT)
LDFLAGS += -isysroot$(SYSROOT)

#
# Targets
#
OBJS = $(SRCS:.cpp=.o)
IPA := $(IPA)$(POSTFIX)

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
	@$(CXX) -o $@ $(LDFLAGS) $(OBJS) $(LIBS)
	@$(ECHO) g "Done `basename $(CURDIR)`"

ipa_:
	@$(ECHO) y "Making $(IPA).ipa"
	@$(BUILD) "$(IPA)" $(ICON) $(ARCH) $(TARGET) $(ASSETS)

install_:
	@$(ECHO) y "Installing $(IPA)"
	@$(BUILD) -install "$(IPA)" $(ICON) $(ARCH) $(TARGET) $(ASSETS)

run_:
	@$(ECHO) y "Running $(IPA)"
	@$(BUILD) -run "$(IPA)" $(ICON) $(ARCH) $(TARGET) $(ASSETS)

debug_:
	@$(ECHO) y "Debugging $(IPA)"
	@$(BUILD) -debug "$(IPA)" $(ICON) $(ARCH) $(TARGET) $(ASSETS)

remove_:
	@$(ECHO) r "Removing $(IPA)"
	@-$(BUILD) -remove "$(IPA)"

clean_:
	@$(ECHO) r "Cleaning `basename $(CURDIR)`"
	@rm -f $(TARGET) $(OBJS) $(CLEAN) "$(IPA).ipa" *.tmp
	@rm -rf "$(IPA).app"

%: %_
	@true

#
# Dependencies
#
ifneq "$(MAKECMDGOALS)" "run"
ifneq "$(MAKECMDGOALS)" "debug"
ifneq "$(MAKECMDGOALS)" "clean"
ifneq "$(MAKECMDGOALS)" "remove"
 	-include $(DEPEND)
endif
endif
endif
endif

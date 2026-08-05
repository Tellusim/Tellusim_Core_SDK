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
#  * debug  - 0, 1
#  * depend - 0, 1

DEPEND = .depend
CXX = ccache em++
ECHO = $(TSROOT)/bin/ts_echo.sh
RUN = emrun --serve_after_close --no_browser

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
CFLAGS += -std=c++11 -Wall -Wfloat-conversion -Os -ffast-math -fvisibility=hidden
CFLAGS += -D_EMSCRIPTEN=1 -DTS_CORE=1 -I$(TSROOT)/include -I$(TSROOT)/plugins
CFLAGS += -Wno-undefined-var-template -Wno-nontrivial-memcall -Wno-unused-template
CFLAGS += --use-port=emdawnwebgpu
LDFLAGS += -s EXPORTED_RUNTIME_METHODS="['ccall','requestFullscreen']"
LDFLAGS += -s STACK_SIZE=32MB -s TOTAL_MEMORY=256MB -s ALLOW_MEMORY_GROWTH=1
LDFLAGS += -s FULL_ES3=1 -s GL_ENABLE_GET_PROC_ADDRESS=1
LDFLAGS += --use-port=emdawnwebgpu -s ASYNCIFY=1
LDFLAGS += -L$(TSROOT)/lib/emscripten/bc
LDFLAGS += -Os --emrun
LIBS += -lpthread

#
# Debugging
#
ifneq "$(debug)" "0"
	POSTFIX := $(POSTFIX)d
	CFLAGS += -g -DTS_DEBUG=1
	LDFLAGS += -s ASSERTIONS=2
	LIBS += -lTellusim_bcd
else
	CFLAGS += -DNDEBUG=1
	LIBS += -lTellusim_bc
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
# Assets
#
ifdef ASSETS
	LDFLAGS += $(addprefix --embed-file , $(wildcard $(ASSETS)))
endif

#
# Page
#
ifdef PAGE
	ifneq "$(PAGE)" "0"
		LDFLAGS += --shell-file $(PAGE)
	endif
else
	LDFLAGS += --shell-file shell_minimal.html
endif

#
# Targets
#
OBJS = $(SRCS:.cpp=.o)
ifneq "$(PAGE)" "0"
	TARGET := $(TARGET).html
endif

#
# Build target
#
all: $(TARGET)

.cpp.o:
	@echo `basename $<`
	@$(CXX) $(FLAGS) $(CFLAGS) -c -o $@ $<

$(DEPEND):
	@rm -f $@
	@$(ECHO) b "Depend `basename $(CURDIR)`"
	@$(foreach SRC, $(DEPS), $(CXX) $(FLAGS) $(CFLAGS) -MM -MT $(SRC:.cpp=.o) $(SRC) >> $@;)

$(TARGET): $(DEPEND) $(OBJS)
	@$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)
	@$(ECHO) g "Done `basename $(CURDIR)`"

install_:
	@$(ECHO) g "Installing `basename $(CURDIR)`"
	@$(eval INSTALL:=~/webgpu-`date +%Y%m%d`/`basename \`dirname $(CURDIR)\``_`basename $(CURDIR)`/)
	@mkdir -p $(INSTALL) && cp main$(POSTFIX).js main$(POSTFIX).html main$(POSTFIX).wasm $(INSTALL) && gzip -k -9 $(INSTALL)/main$(POSTFIX).wasm

run_:
	@$(ECHO) g "Running `basename $(CURDIR)`"
	@$(RUN) $(TARGET) $(RUN_ARGS)

clean_:
	@$(ECHO) r "Cleaning `basename $(CURDIR)`"
	@rm -f $(TARGET) $(OBJS) $(CONFIG) $(CLEAN) *.js *.wasm

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

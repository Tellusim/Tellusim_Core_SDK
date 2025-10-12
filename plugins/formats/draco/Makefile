SRCS = main.cpp \
	source/TellusimFormatDRC.cpp

FLAGS += -I$(TSROOT)/plugins/formats/draco/extern

ifeq "$(shell uname -s)" "Linux"
	LIBS += -Lextern/lib/linux/$(ARCH) -ldraco
else ifeq "$(shell uname -s)" "Darwin"
	LIBS += -Lextern/lib/macos/$(ARCH) -ldraco
endif

CLEAN = test_save*

include ../../Makefile.unx.mk

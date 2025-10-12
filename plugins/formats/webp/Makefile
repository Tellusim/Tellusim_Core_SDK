SRCS = main.cpp \
	source/TellusimFormatWEBP.cpp

CFLAGS += -Iextern

ifeq "$(shell uname -s)" "Linux"
	LIBS += -Lextern/lib/linux/$(ARCH)
else ifeq "$(shell uname -s)" "Darwin"
	LIBS += -Lextern/lib/macos/$(ARCH)
endif

LIBS += -lwebp

CLEAN = test_save*

include ../../Makefile.unx.mk

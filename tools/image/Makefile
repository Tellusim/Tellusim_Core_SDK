TARGET = image$(POSTFIX)

SRCS = image.cpp \
	Plugins.cpp

FLAGS += -I$(TSROOT)/plugins/formats/webp/extern

ifeq "$(shell uname -s)" "Linux"
	LIBS += -L$(TSROOT)/plugins/formats/webp/extern/lib/linux/$(ARCH) -lwebp
else ifeq "$(shell uname -s)" "Darwin"
	LIBS += -L$(TSROOT)/plugins/formats/webp/extern/lib/macos/$(ARCH) -lwebp
endif

include ../Makefile.unx.mk

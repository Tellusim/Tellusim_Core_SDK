TSROOT = $(CURDIR)/../../..

TARGET = main$(POSTFIX)

CFLAGS += -I$(TSROOT)/samples

#
# Arch configuration
#
ARCH = $(shell uname -m)
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
# Platform configuration
#
ifeq "$(shell uname -s)" "Linux"
	LDFLAGS = -Wl,-rpath,./,-rpath,../../../source,-rpath,../../../lib/linux/$(ARCH)
else ifeq "$(shell uname -s)" "Darwin"
	LDFLAGS = -Wl,-rpath,@loader_path/,-rpath,@loader_path/../../../source/,-rpath,@loader_path/../../../lib/macos/$(ARCH)/
else
 	$(error Unknown platform $(shell uname -s))
endif

#
# Build
#
include $(TSROOT)/build/Makefile.unx.mk

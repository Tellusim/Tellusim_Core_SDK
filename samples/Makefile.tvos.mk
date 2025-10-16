TSROOT = $(CURDIR)/../../..

TARGET = main$(POSTFIX)

ICON = $(TSROOT)/samples/common/tellusim.png

CFLAGS += -I$(TSROOT)/samples

#
# Build
#
include $(TSROOT)/build/Makefile.tvos.mk

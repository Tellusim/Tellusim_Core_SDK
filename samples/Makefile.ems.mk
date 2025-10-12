TSROOT = $(CURDIR)/../../..

TARGET = main$(POSTFIX)

CFLAGS += -I$(TSROOT)/samples

PAGE = ../../../samples/common/tellusim.html

#
# Build
#
include $(TSROOT)/build/Makefile.ems.mk

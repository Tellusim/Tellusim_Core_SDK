TSROOT = $(MAKEDIR)\..\..\..

TARGET = main$(POSTFIX).exe

CFLAGS = $(CFLAGS) /I$(TSROOT)\samples

RESOURCES = $(TSROOT)\samples\common\tellusim.rc

#
# Build
#
!include $(TSROOT)\build\Makefile.win.mk

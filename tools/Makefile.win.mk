TSROOT = $(MAKEDIR)\..\..

#
# Default prefix
#
!ifndef PREFIX
PREFIX = $(TSROOT)
!endif
INSTALL = $(PREFIX)/bin
INSTALL = $(INSTALL:/=\\)

#
# Build
#
!include $(TSROOT)\build\Makefile.win.mk

#
# Install
#
install:
	@$(ECHO) y "Installing $(TARGET)"
	@-if not exist $(INSTALL) mkdir $(INSTALL) > nul
	@copy $(TARGET) $(INSTALL)\ts_$(TARGET)

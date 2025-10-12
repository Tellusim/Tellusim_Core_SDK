# Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/
#
# Required environment variables:
#
#  * TARGET - Binary target name
#  * TSROOT - Path to the Tellusim root

#
# Check environment
#
ifndef TSROOT
 	$(error TSROOT is not defined)
endif

#
# Platform
#
ifeq "$(shell uname -s)" "Linux"
	include $(TSROOT)/build/Makefile.lnx.mk
else ifeq "$(shell uname -s)" "Darwin"
	include $(TSROOT)/build/Makefile.mac.mk
else
 	$(error Unknown platform $(shell uname -s))
endif

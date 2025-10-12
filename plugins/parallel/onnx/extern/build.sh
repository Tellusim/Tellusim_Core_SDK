#!/bin/bash

# Nanopb - Protocol Buffers for Embedded Systems
# Uses Windows Subsystem for Linux on Windows
#
# Usage: build.sh

# Windows and Unix
make clean && make && make install

# Android and iOS
if [ "`uname -s`" == "Darwin" ]; then
	
	# Android
	make -f Makefile.and clean && make -f Makefile.and && make -f Makefile.and install
	
	# iOS
	make -f Makefile.ios clean && make -f Makefile.ios && make -f Makefile.ios install
	
	# tvOS
	make -f Makefile.tvos clean && make -f Makefile.tvos && make -f Makefile.tvos install
	
fi

make clean

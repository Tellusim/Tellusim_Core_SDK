# Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/

TSROOT = $(CURDIR)/../../..

LN = ln
JAR = jar
JAVA = java
JAVAC = javac
KOTLINC = kotlinc

#
# Platform configuration
#
ifeq "$(shell uname -s)" "Linux"
	TARGET = libTellusimJNI_$(ARCH)$(POSTFIX).so
	CFLAGS = -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux
	LDFLAGS = -Wl,-rpath,./,-rpath,../../../source,-rpath,../../../lib/linux/$(ARCH)
else ifeq "$(shell uname -s)" "Darwin"
	TARGET = libTellusimJNI_$(ARCH)$(POSTFIX).dylib
	CFLAGS = -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/darwin
	LDFLAGS = -Wl,-rpath,@loader_path/,-rpath,@loader_path/../../../source/,-rpath,@loader_path/../../../lib/macos/$(ARCH)/
	JAVA := $(JAVA) -XstartOnFirstThread
else
 	$(error Unknown platform $(shell uname -s))
endif

#
# Default configuration
#
LDFLAGS += -shared

#
# Sources
#
SRCS = source/TellusimJNIBase.cpp \
	source/TellusimJNIMath.cpp \
	source/TellusimJNIAPI.cpp

#
# Package target
#
PACKAGE_TARGET = tellusim.jar
PACKAGE_SRCS = source/base/*.java \
	source/math/*.java \
	source/api/*.java

#
# Main target
#
JAVA_TARGET = main$(POSTFIX).jar
JAVA_SRCS = main.java

KOTLIN_TARGET = main_kt$(POSTFIX).jar
KOTLIN_SRCS = main.kt

ifeq "$(kotlin)" "1"
	MAIN_TARGET = $(KOTLIN_TARGET)
else
	MAIN_TARGET = $(JAVA_TARGET)
endif

#
# Clean targets
#
CLEAN = $(PACKAGE_TARGET) $(MAIN_TARGET) ./com/tellusim/* ./com/main/*

#
# Build
#
include $(TSROOT)/build/Makefile.unx.mk

#
# Package
#
$(PACKAGE_TARGET): $(PACKAGE_SRCS)
	@$(JAVAC) -d . source/base/*.java source/math/*.java source/api/*.java
	@$(JAR) -c -f $@ com/tellusim/*.class
	@$(ECHO) g "Done `basename $@`"

#
# Main
#
all: $(MAIN_TARGET)

$(JAVA_TARGET): $(JAVA_SRCS) $(PACKAGE_TARGET) $(TARGET)
	@$(JAVAC) -d . -classpath $(PACKAGE_TARGET) $(JAVA_SRCS)
	@$(JAR) -c -f $@ -m main.mf com/main/*.class
	@$(ECHO) g "Done `basename $@`"

$(KOTLIN_TARGET): $(KOTLIN_SRCS) $(PACKAGE_TARGET) $(TARGET)
	@$(KOTLINC) -d $@ -include-runtime -classpath $(PACKAGE_TARGET) $(KOTLIN_SRCS)
	@$(JAR) -u -f $@ -m main.mf
	@$(JAR) -u -f $@ -e com.main.MainKt
	@$(LN) -f -s $@ $(JAVA_TARGET)
	@$(ECHO) g "Done `basename $@`"

#
# Install
#
install:
	@$(ECHO) b "Install $(TARGET)"
	@$(LN) -f -s ../plugins/binding/java/$(TARGET) $(TSROOT)/bin/

#
# Run target
#
run:
	@echo "Running $(MAIN_TARGET)"
	@$(JAVA) -jar $(MAIN_TARGET)

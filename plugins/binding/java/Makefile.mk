# Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/

LN = ln
JAR = jar
JAVA = java
JAVAC = javac
KOTLINC = kotlinc

#
# Debug configuration
#
ifneq "$(debug)" "0"
	POSTFIX := $(POSTFIX)d
endif

#
# Platform configuration
#
ifeq "$(shell uname -s)" "Darwin"
	JAVA := $(JAVA) -XstartOnFirstThread
endif

#
# Default configuration
#
LIBRARY = $(TSROOT)/plugins/binding/java/tellusim.jar
MANIFEST = $(TSROOT)/plugins/binding/java/main.mf

#
# Target
#
JAVA_TARGET = main$(POSTFIX).jar
KOTLIN_TARGET = main_kt$(POSTFIX).jar

ifeq "$(KOTLIN)" "1"
	TARGET = $(KOTLIN_TARGET)
else
	TARGET = $(JAVA_TARGET)
endif

all: $(TARGET)

$(JAVA_TARGET): $(SRCS)
	@$(LN) -f -s $(LIBRARY)
	@$(JAVAC) -d . -classpath $(LIBRARY) $^
	@$(JAR) -c -f $@ -m $(MANIFEST) com/main/*.class
	@echo "Done `basename $@`"

$(KOTLIN_TARGET): $(SRCS)
	@$(LN) -f -s $(LIBRARY)
	@$(KOTLINC) -d $@ -include-runtime -classpath $(LIBRARY) $^
	@$(JAR) -u -f $@ -m $(MANIFEST)
	@$(JAR) -u -f $@ -e com.main.MainKt
	@echo "Done `basename $@`"

run:
	@echo "Running `basename $(CURDIR)`"
	@$(JAVA) -jar $(TARGET)

clean:
	@echo "Cleaning `basename $(CURDIR)`"
	@rm -rf *.jar ./com

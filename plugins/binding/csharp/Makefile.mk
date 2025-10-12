# Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/

CSC = csc
MONO = mono

#
# Debug configuration
#
ifneq "$(debug)" "0"
	POSTFIX := $(POSTFIX)d
endif

#
# Target
#
TARGET = main$(POSTFIX).exe

CFLAGS = /langversion:8.0

LIBRARY = libTellusimCS$(POSTFIX).dll

$(TARGET): $(SRCS)
	@$(CSC) /nologo /target:exe $(CFLAGS) /out:$@ /reference:$(TSROOT)/plugins/binding/csharp/$(LIBRARY) $(SRCS)
	@echo "<configuration><runtime><assemblyBinding><probing privatePath=\"$(TSROOT)/plugins/binding/csharp\"/></assemblyBinding></runtime></configuration>" > $(TARGET).config
	@echo "Done `basename $@`"

run:
	@echo "Running `basename $(CURDIR)`"
	@$(MONO) $(TARGET)

clean:
	@echo "Cleaning `basename $(CURDIR)`"
	@rm -f $(TARGET) $(TARGET).config

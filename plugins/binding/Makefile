PLUGINS = \
	capi

ifneq "$(shell command -v csc 2> /dev/null)" ""
	PLUGINS += csharp
endif
ifneq "$(shell command -v python3-config 2> /dev/null)" ""
	PLUGINS += python
endif
ifneq "$(shell command -v rustc 2> /dev/null)" ""
	PLUGINS += rust
endif
ifeq "$(shell uname -s)" "Darwin"
	PLUGINS += swift
endif
ifneq "$(shell command -v javac 2> /dev/null)" ""
	PLUGINS += java
endif

include ../Makefile

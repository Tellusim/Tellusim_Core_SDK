# Copyright (C) 2018-2025, Tellusim Technologies Inc. All rights reserved
# https://tellusim.com/
#
# Required environment variables:
#
#  * TARGET - Binary target name
#  * TSROOT - Path to the Tellusim root
#
# Optional environment variables:
#
#  * CLEAN  - Additional clean targets
#
# Optional command line arguments:
#
#  * DEBUG  - 0, 1
#  * CCACHE - 0, 1
#  * DEPEND - 0, 1

RC = rc.exe
CXX = cl.exe
LINK = link.exe

DEPFILE = .depend
ECHO = $(TSROOT)\bin\ts_echo.bat
DEP = $(TSROOT)\bin\ts_dep.bat

#
# Check environment
#
!ifndef TARGET
!error TARGET is not defined
!endif
!ifndef TSROOT
!error TSROOT is not defined
!endif

#
# Compiler cache
#
!if "$(CCACHE)" != "0" && [where /q ccache.exe] == 0
CXX = ccache.exe depend_mode=true $(CXX)
!endif

#
# Default configuration
#
CFLAGS = $(CFLAGS) /nologo /bigobj /fp:fast /D_CRT_SECURE_NO_WARNINGS
CFLAGS = $(CFLAGS) /MD /W4 /O2 /EHsc /FC /D_WIN32_WINNT=0x0603
CFLAGS = $(CFLAGS) /DTS_CORE=1 /I$(TSROOT)\include /I$(TSROOT)\plugins

LDFLAGS = $(LDFLAGS) /nologo /incremental /debug:fastlink

DEPFLAGS = $(DEPFLAGS) /I$(MAKEDIR)

#
# Debugging
#
!if "$(DEBUG)" != "0"
POSTFIX = $(POSTFIX)d
CFLAGS = $(CFLAGS) /Z7 /DTS_DEBUG=1
LDFLAGS = $(LDFLAGS) $(TSROOT)\lib\windows\vs170x64\Tellusim_x64d.lib
!else
CFLAGS = $(CFLAGS) /DNDEBUG
LDFLAGS = $(LDFLAGS) $(TSROOT)\lib\windows\vs170x64\Tellusim_x64.lib
!endif

#
# Dependencies
#
!if "$(DEPEND)" != "0"
DEPS = $(SRCS)
!if "$(DEPEND)" == "1"
CLEAN = $(CLEAN) $(DEPFILE)
!endif
!else
DEPS =
!endif
DEPEND = $(DEPFILE)

#
# Targets
#
SRCS = $(SRCS:/=\\)
SRCS = $(SRCS:\\=\)
OBJS = $(SRCS:.cpp=.obj)
OBJS = $(OBJS) $(RESOURCES:.rc=.res)

#
# Build target
#
all: $(TARGET) done

.rc.res:
	@$(RC) /nologo /fo$*.res $<

.cpp.obj:
	@$(CXX) $(CFLAGS) $(FLAGS) /c /Fo$*.obj $<

$(DEPEND): $(MAKEDIR)
	@del /f $@ 2>nul
	@$(ECHO) g "Depend %|fF"
	@$(DEP) $(DEPFLAGS) /Fo$@ $(DEPS)

$(TARGET): $(DEPEND) $(OBJS)
	@$(LINK) $(LDFLAGS) /out:$@ $(OBJS)

done: $(MAKEDIR)
	@$(ECHO) g "Done %|fF"

clean: $(MAKEDIR)
	@$(ECHO) r "Cleaning %|fF"
	@del /f $(TARGET) $(OBJS) $(CLEAN) 2>nul
	@del /f $(TARGET:.exe=.lib) $(TARGET:.dll=.lib) 2>nul
	@del /f $(TARGET:.exe=.pdb) $(TARGET:.dll=.pdb) 2>nul
	@del /f *.exp *.ilk *.res 2>nul

#
# Dependencies
#
!if exist($(DEPEND))
!include $(DEPEND)
!endif

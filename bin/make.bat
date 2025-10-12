@echo off

if not defined VSCOMNTOOLS (
	call "%~dp0\vcvars_any.bat"
)

cmd /c nmake.exe /nologo -f Makefile.win %*

@echo off

if not defined VSCOMNTOOLS (
	call "%~dp0\vcvars_x64.bat"
)

cmd /c nmake.exe /nologo -f Makefile.win %*

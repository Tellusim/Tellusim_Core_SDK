@echo off

if "%1" == "-f" (
	echo Clear Environment
	set TSROOT=
)

if defined TSROOT goto ts_ok

set TSROOT=%~dp0..
set PATH=%~dp0;%PATH%
call ts_echo.bat y "Set TSROOT to '%TSROOT%'"
if %ERRORLEVEL% NEQ 0 (
	echo Cannot set TSROOT
	exit 1
)

:ts_ok

call ts_dep.bat
call ts_exec.bat

set ECHO="%~dp0\ts_echo.bat"

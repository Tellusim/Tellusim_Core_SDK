@echo off

set TSROOT=%~dp0

set PATH=%TSROOT%\bin;%PATH%
set PYTHONPATH=%TSROOT%\bin;%PYTHONPATH%

cmd.exe /c "%~dp0\bin\vcvars_any.bat && %~dp0\bin\ts_browser.exe -port 62848 -root utils/browser/"
if %ERRORLEVEL% EQU 0 exit 0

call "%~dp0\bin\ts_browser.exe" -port 62848 -root utils/browser/

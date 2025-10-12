@echo off

call %~dp0..\bin\ts_root.bat

cmd /c "make_x64 %* clean && make_x64 %*"

call %ECHO% g "All Done"

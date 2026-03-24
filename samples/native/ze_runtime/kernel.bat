@echo off

rem set PATH=%PATH%;D:\Intel\oneAPI\ocloc\latest\bin

ocloc.exe -file kernel.cl -spv_only -output kernel

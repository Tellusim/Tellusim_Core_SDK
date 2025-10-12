@echo off

if not defined VSCOMNTOOLS (
	if "%PROCESSOR_ARCHITECTURE%" == "AMD64" (
		call "%~dp0\vcvars_x64.bat"
	) else if "%PROCESSOR_ARCHITECTURE%" == "ARM64" (
		call "%~dp0\vcvars_arm64.bat"
	) else (
		echo Unknown architecture %PROCESSOR_ARCHITECTURE%
	)
)

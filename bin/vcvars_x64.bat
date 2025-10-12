@echo off

:vcvars_init

set VCVARS=%VS170COMNTOOLS%\..\..\VC\Auxiliary\Build\vcvars64.bat
if exist "%VCVARS%" (
	set VSCOMNTOOLS=%VS170COMNTOOLS%
	set VSVERSION=170
	set VSYEAR=2022
	goto vcvars_ok
)

set VCVARS=%VS160COMNTOOLS%\..\..\VC\Auxiliary\Build\vcvars64.bat
if exist "%VCVARS%" (
	set VSCOMNTOOLS=%VS160COMNTOOLS%
	set VSVERSION=160
	set VSYEAR=2019
	goto vcvars_ok
)

set VSPATH=C:\Program Files\Microsoft Visual Studio
for %%i in (Community Enterprice Professional) do (
	if exist "%VSPATH%\2022\%%i\VC\Auxiliary\Build\vcvars64.bat" (
		set VS170COMNTOOLS=%VSPATH%\2022\%%i\Common7\Tools
		goto vcvars_init
	)
	if exist "%VSPATH%\2019\%%i\VC\Auxiliary\Build\vcvars64.bat" (
		set VS160COMNTOOLS=%VSPATH%\2019\%%i\Common7\Tools
		goto vcvars_init
	)
)

echo Cannot find Visual Studio default installation directory
echo Make sure that VSXXXCOMNTOOLS variable is available
exit 1

:vcvars_ok

pushd "%~dp0"
call "%VCVARS%"
popd

set ARCH=x64

call "%~dp0\ts_dep.bat"
call "%~dp0\ts_exec.bat"
call "%~dp0\ts_echo.bat" y "Compiling with Visual Studio %VSYEAR% %ARCH%"

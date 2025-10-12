@echo off

set ECHO=%TEMP%\ts_echo
set ECHO_SRC="%ECHO%.cpp"

if not exist "%ECHO%.exe" (
	if not defined VSCOMNTOOLS (
		call "%~dp0\vcvars_any.bat"
	)
	more +19 "%~dp0\ts_echo.bat" > "%ECHO_SRC%"
	cl.exe /nologo /MD /Os /c "%ECHO_SRC%" /Fo"%ECHO%.obj"
	link.exe /nologo /out:"%ECHO%.exe" "%ECHO%.obj"
	del "%ECHO_SRC%" "%ECHO%.obj"
)

call "%ECHO%.exe" %*

goto :eof

#include <stdio.h>
#include <windows.h>
int main(int argc, char **argv) {
	if(argc < 2) return 1;
	CONSOLE_SCREEN_BUFFER_INFO info = {};
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	if(!output || !GetConsoleScreenBufferInfo(output, &info)) {
		for(int i = 2; i < argc; i++) {
			fwrite(argv[i], 1, strlen(argv[i]), stdout);
			fwrite(" ", 1, 1, stdout);
		}
		fwrite("\n", 1, 1, stdout); return 0;
	}
	WORD attributes = info.wAttributes & 0xf0;
	switch(argv[1][0]) {
		case 'r': attributes |= 12; break;
		case 'g': attributes |= 10; break;
		case 'y': attributes |= 14; break;
		case 'b': attributes |=  9; break;
		case 'm': attributes |= 13; break;
		case 'c': attributes |= 11; break;
		case 'w': attributes |= 15; break;
		default: return 1;
	}
	SetConsoleTextAttribute(output, attributes);
	for(int i = 2; i < argc; i++) {
		WriteConsoleA(output, argv[i], (DWORD)strlen(argv[i]), NULL, NULL);
		WriteConsoleA(output, " ", 1, NULL, NULL);
	}
	WriteConsoleA(output, "\n", 1, NULL, NULL);
	SetConsoleTextAttribute(output, info.wAttributes);
	return 0;
}

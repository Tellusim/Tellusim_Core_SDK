@echo off

set TEE=%TEMP%\ts_tee
set TEE_SRC="%TEE%.cpp"

if not exist "%TEE%.exe" (
	if not defined VSCOMNTOOLS (
		call "%~dp0\vcvars_any.bat"
	)
	more +19 "%~dp0\ts_tee.bat" > "%TEE_SRC%"
	cl.exe /nologo /MD /Os /c "%TEE_SRC%" /Fo"%TEE%.obj"
	link.exe /nologo /out:"%TEE%.exe" "%TEE%.obj" user32.lib
	del "%TEE_SRC%" "%TEE%.obj"
)

call "%TEE%.exe" %*

goto :eof

#include <conio.h>
#include <windows.h>
int main(int argc, char **argv) {
	DWORD read = 0;
	char buffer[1024];
	HANDLE handles[1024];
	HANDLE input = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	if(!input || !output) return 1;
	for(int i = 1; i < argc; i++) {
		handles[i] = CreateFileA(argv[i], GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if(!handles[i]) return 1;
	}
	HWND window = GetConsoleWindow();
	if(window) ShowWindow(window, SW_SHOWNORMAL);
	while(true) {
		if(!ReadFile(input, buffer, sizeof(buffer), &read, NULL)) break;
		for(int i = 0; i < read; i++) { if(buffer[i] == '/') buffer[i] = '\\'; }
		for(int i = 1; i < argc; i++) WriteFile(handles[i], buffer, read, NULL, NULL);
		WriteConsoleA(output, buffer, read, NULL, NULL);
	}
	for(int i = 1; i < argc; i++) CloseHandle(handles[i]);
	strcpy(buffer, "Hit any key to close this window...\n");
	WriteConsoleA(output, buffer, strlen(buffer), NULL, NULL);
	_getch();
	return 0;
}

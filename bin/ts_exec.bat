@echo off

set EXEC=%TEMP%\ts_exec
set EXEC_SRC="%EXEC%.cpp"

if not exist "%EXEC%.exe" (
	if not defined VSCOMNTOOLS (
		call "%~dp0\vcvars_any.bat"
	)
	more +19 "%~dp0\ts_exec.bat" > "%EXEC_SRC%"
	cl.exe /nologo /MD /Os /c "%EXEC_SRC%" /Fo"%EXEC%.obj"
	link.exe /nologo /out:"%EXEC%.exe" "%EXEC%.obj"
	del "%EXEC_SRC%" "%EXEC%.obj"
)

call "%EXEC%.exe" %*

goto :eof

#include <stdio.h>
#include <windows.h>
int main(int argc, char **argv) {
	if(argc < 2) return 1;
	SYSTEM_INFO info = {};
	GetSystemInfo(&info);
	STARTUPINFOA startups[1024] = {};
	PROCESS_INFORMATION processes[1024] = {};
	if(info.dwNumberOfProcessors > 1024) info.dwNumberOfProcessors = 1024;
	int cmd = 1, count = 1;
	for(; argv[cmd][0] == '-'; cmd++) {
		if(argv[cmd][1] == 's') info.dwNumberOfProcessors = 1;
		if(argv[cmd][1] == 'p') count = info.dwNumberOfProcessors;
	}
	for(int j = cmd + 1; j < argc; j += count, count = info.dwNumberOfProcessors) {
		if(j + count > argc) count = argc - j;
		for(int i = 0; i < count; i++) {
			char buffer[4096]; char *d = buffer;
			for(const char *s = argv[cmd]; *s; s++) {
				if(*s == '@') for(const char *s = argv[j + i]; *s; s++) *d++ = *s;
				else if(*s == '\'') *d++ = '"';
				else *d++ = *s;
			}
			*d++ = '\0';
			startups[i].cb = sizeof(startups[i]);
			startups[i].dwFlags = STARTF_USESTDHANDLES;
			startups[i].hStdError = GetStdHandle(STD_ERROR_HANDLE);
			startups[i].hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
			if(!CreateProcessA(NULL, buffer, NULL, NULL, TRUE, 0, NULL, NULL, &startups[i], &processes[i])) return 1;
		}
		int ret = 0;
		for(int i = 0; i < count; i++) {
			if(WaitForSingleObject(processes[i].hProcess, INFINITE) == WAIT_FAILED) return 1;
			DWORD code = 0; if(!GetExitCodeProcess(processes[i].hProcess, &code)) return 1;
			if(code != 0) ret = code;
			CloseHandle(processes[i].hProcess); CloseHandle(processes[i].hThread);
		}
		if(ret != 0) return ret;
	}
	return 0;
}

@echo off

set CHWORD=%TEMP%\ts_chword
set CHWORD_SRC="%CHWORD%.cpp"

if not exist "%CHWORD%.exe" (
	if not defined VSCOMNTOOLS (
		call "%~dp0\vcvars_any.bat"
	)
	more +19 "%~dp0\ts_chword.bat" > "%CHWORD_SRC%"
	cl.exe /nologo /MD /Os /c "%CHWORD_SRC%" /Fo"%CHWORD%.obj"
	link.exe /nologo /out:"%CHWORD%.exe" "%CHWORD%.obj"
	del "%CHWORD_SRC%" "%CHWORD%.obj"
)

call "%CHWORD%.exe" %*

goto :eof

#include <stdio.h>
#include <string.h>
int main(int argc, char **argv) {
	if(argc < 4) return 1;
	FILE *from = fopen(argv[1], "rb");
	FILE *to = fopen(argv[2], "rb");
	if(from) {
		fseek(from, 0, SEEK_END); size_t size = ftell(from);
		fseek(from, 0, SEEK_SET); argv[1] = new char[size + 1];
		fread(argv[1], size, 1, from); argv[1][size] = '\0'; fclose(from);
	}
	if(to) {
		fseek(to, 0, SEEK_END); size_t size = ftell(to);
		fseek(to, 0, SEEK_SET); argv[2] = new char[size + 1];
		fread(argv[2], size, 1, to); argv[2][size] = '\0'; fclose(to);
	}
	for(int i = 3; i < argc; i++) {
		FILE *file = fopen(argv[i], "rb");
		if(!file) continue;
		fseek(file, 0, SEEK_END); size_t size = ftell(file);
		fseek(file, 0, SEEK_SET); char *src = new char[size + 1];
		fread(src, size, 1, file); src[size] = '\0'; fclose(file);
		file = fopen(argv[i], "wb");
		if(!file) { delete [] src; continue; }
		const char *s = src, *d = NULL;
		size = strlen(argv[1]);
		int counter = 0;
		while(*s) {
			if(!strncmp(s, argv[1], size)) {
				if(d) fwrite(d, s - d, 1, file);
				d = NULL; s += size; fputs(argv[2], file);
				counter++;
			}
			else if(!d) d = s++;
			else s++;
		}
		if(d) fwrite(d, s - d, 1, file);
		delete [] src; fclose(file);
		if(counter) printf("%s: %u change%s\n", argv[i], counter, (counter > 1) ? "s" : "");
	}
	return 0;
}

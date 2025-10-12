#!/bin/bash

EXEC=/tmp/ts_exec
EXEC_SRC=$EXEC$$.cpp
ARGUMENT=$1
COMMAND=$2
shift 2

if [ ! -f "$EXEC" ]; then
	echo "Building $EXEC"
	tail -n +25 "${BASH_SOURCE[0]}" > $EXEC_SRC
	clang++ -Wall -Os $EXEC_SRC -o $EXEC$$
	if [ $? -ne 0 ]; then
		echo "Please install clang++"
		exit 1
	fi
	mv $EXEC$$ $EXEC
	rm -f $EXEC_SRC
fi

$EXEC "$ARGUMENT" "$COMMAND" $*

exit

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char **argv) {
	if(argc < 2) return 1;
	pid_t pids[1024] = {};
	int step = sysconf(_SC_NPROCESSORS_ONLN);
	if(step > 1024) step = 1024;
	int cmd = 1, count = 1;
	for(; argv[cmd][0] == '-'; cmd++) {
		if(argv[cmd][1] == 's') step = 1;
		if(argv[cmd][1] == 'p') count = step;
	}
	for(int j = cmd + 1; j < argc; j += count, count = step) {
		if(j + count > argc) count = argc - j;
		for(int i = 0; i < count; i++) {
			char buffer[4096]; char *d = buffer;
			for(const char *s = argv[cmd]; *s; s++) {
				if(*s == '@') { for(const char *s = argv[j + i]; *s; s++) *d++ = *s; }
				else if(*s == '\'') *d++ = '\"';
				else *d++ = *s;
			}
			*d++ = '\0';
			if((pids[i] = fork()) < 0) return 1;
			if(pids[i] == 0) { int status = system(buffer); exit(WEXITSTATUS(status)); }
		}
		int ret = 0;
		for(int i = 0; i < count; i++) {
			int status = 0; if(waitpid(pids[i], &status, 0) < 0) return 1;
			if(WEXITSTATUS(status) != 0) ret = WEXITSTATUS(status);
		}
		if(ret != 0) return ret;
	}
	return 0;
}

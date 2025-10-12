#!/bin/bash

ECHO=/tmp/ts_echo
ECHO_SRC=$ECHO$$.cpp

if [ ! -f "$ECHO" ]; then
	echo "Building $EXEC"
	tail -n +22 "${BASH_SOURCE[0]}" > $ECHO_SRC
	clang++ -Wall -Os $ECHO_SRC -o $ECHO$$
	if [ $? -ne 0 ]; then
		echo "Please install clang++"
		exit 1
	fi
	mv $ECHO$$ $ECHO
	rm -f $ECHO_SRC
fi

$ECHO $*

exit

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char **argv) {
	if(argc < 2) return 1;
	const char *term = getenv("TERM");
	if(term && !strcmp(term, "dumb")) term = 0;
	if(term) switch(argv[1][0]) {
		case 'r': fputs("\033[01;31m", stdout); break;
		case 'g': fputs("\033[01;32m", stdout); break;
		case 'y': fputs("\033[01;33m", stdout); break;
		case 'b': fputs("\033[01;34m", stdout); break;
		case 'm': fputs("\033[01;35m", stdout); break;
		case 'c': fputs("\033[01;36m", stdout); break;
		case 'w': fputs("\033[01;37m", stdout); break;
		default: return 1;
	}
	for(int i = 2; i < argc; i++) {
		fputs(argv[i], stdout);
		fputs(" ", stdout);
	}
	fputs("\n", stdout);
	if(term) fputs("\033[m", stdout);
	return 0;
}

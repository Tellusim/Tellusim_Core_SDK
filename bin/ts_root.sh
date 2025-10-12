#!/bin/bash

if [ "$1" == "-f" ]; then
	echo "Clear Environment"
	unset TSROOT
fi

if [ -z "$TSROOT" ]; then
	
	cd `dirname "${BASH_SOURCE[0]}"`/..
	export TSROOT="$PWD"
	cd - > /dev/null
	
	export PATH="$TSROOT/bin":$PATH
	export LD_LIBRARY_PATH="$TSROOT/bin":$LD_LIBRARY_PATH
	ts_echo.sh y "Set TSROOT to '$TSROOT'"
	if [ $? -ne 0 ]; then
		echo "Cannot set TSROOT"
		exit 1
	fi
fi

ts_exec.sh

export ECHO="$TSROOT/bin/ts_echo.sh"

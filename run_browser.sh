#!/bin/bash

cd `dirname "${BASH_SOURCE[0]}"`
export TSROOT="$PWD"

export PATH="$TSROOT/bin":$PATH
export PYTHONPATH="$TSROOT/bin":$PYTHONPATH
export LD_LIBRARY_PATH="$TSROOT/bin":$LD_LIBRARY_PATH

killall -q -9 ./bin/ts_browser && sleep 1

./bin/ts_browser -port 62848 -root ./utils/browser/ &

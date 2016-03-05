#!/bin/sh
#
# Author: Peter Rogers (peter.rogers@gmail.com)
# License: Public Domain
#
# Attaches to another process, intercepts its stdout stream and prints
# to this process stdout. This is useful to grab the output stream from
# another shell process running on the system and have it be interpreted
# by the shell calling this script. (effectively spying on another shell)
#

if [ "$1" = "" ]; then
    echo "usage: $0 <pid>"
    exit;
fi

# Change into the scripts directory so we can run helper scripts
cd `dirname $0`

# Call strace on the given PID, piping output through out decoding script
# (takes output from strace and extracts strings for printing)
# "-e trace=write" == trace write system calls
# "-e write=1,2"   == trace writes into stdout and stderr (FD 1, 2)
# "-f"             == follow child processes
# "-s10000"        == how long of a string to include in strace output (max)
# "-p NN"          == trace given PID
strace -e trace=write -e write=1,2 -f -s10000 -p $1 2>&1 | ./decodestrace.py

#!/bin/bash
#
# Author: Peter Rogers (peter.rogers@gmail.com)
# License: Public Domain
#
# Attaches to a process with strace and shows all calls to exec. (usually
# spawning a new process via fork/exec)
#

if [ "$1" = "" ]; then
    echo "usage: $0 <pid>"
    exit;
fi

strace -f -p $1 -e trace=execve 2>&1 | perl -ne '/\[pid *(\d+)\] execve\(.*?, (\[.*\]),/ && print "$1 $2\n"'

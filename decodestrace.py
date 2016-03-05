#!/usr/bin/env python3
#
# Author: Peter Rogers (peter.rogers@gmail.com)
# License: Public Domain
#
# A script to decode the escaped output from strace and turn it back into
# non-escaped text, printing to stdout. (eg turn literal "\n" into newline)
#

import re
import sys

# Output from strace looks like:
#    select(7, [3 4], NULL, NULL, NULL)      = 1 (in [3])
#    ...
#    write(3, "SSH-2.0-OpenSSH_5.3\r\n", 21) = 21
pat = re.compile(".*write\([12], \"(.*)\", \d+\).*")
while 1:
    # Read strace input from stdin, extract the string (that the attached
    # process would write to the user stdin/stderr) and output it to
    # our terminal. We could differentiate between stdout and stderr 
    # (FD 1 and 2) but whatever.
    line = sys.stdin.readline()
    m = pat.match(line)
    if (m):
        # Strace outputs strings encoded with backslash (eg newline
        # is printed as literal '\n' instead of byte value 10). So 
        # we do some trickery here to decode the string and dump
        # it to stdout.
        txt = m.groups()[0]
        sys.stdout.write(bytes(txt, "UTF-8").decode("unicode_escape"))
        sys.stdout.flush()

#!/usr/bin/env python3

import time
import sys

try:
    src = sys.argv[1]
except:
    print("usage: %s logfile" % sys.argv[0])
    sys.exit()

fd = open(src)
while 1:
    ch = fd.read(1)
    if (not ch):
        break
    sys.stdout.write(ch)
    sys.stdout.flush()
    time.sleep(0.01)

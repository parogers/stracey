#!/bin/bash

grep NR_ | perl -pe 's/\#define __NR_(\w+) (\d+)/\[\2\] = "\1",/'

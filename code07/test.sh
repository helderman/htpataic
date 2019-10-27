#!/bin/sh
awk -f test.awk testscript.txt | expect -f - > transcript.txt
cmp baseline.txt transcript.txt

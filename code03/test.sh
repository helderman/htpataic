#!/bin/sh
rm -f test.old
mv test.out test.old
awk -f test.awk < test.in | expect -f - > test.out
cmp test.old test.out

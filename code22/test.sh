#!/bin/bash
./lilcave.testable <<<'' 1>&2 &
MYPID=$!
sleep 1
nc -Cw0 localhost 18811 < "$1"
kill $MYPID

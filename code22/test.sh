#!/bin/bash
./lilcave.testable <<<'' > /dev/null &
MYPID=$!
tr '\n' '\r' < "$1" | pv -qL 20 | nc -N localhost 18811
kill $MYPID
sleep 1

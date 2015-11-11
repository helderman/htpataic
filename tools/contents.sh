#!/bin/bash

DIR="${0%/*}"

awk -v current="$1" -f "$DIR/contents.awk" htpataic??.txt

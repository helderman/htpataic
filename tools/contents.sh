#!/bin/bash

DIR="${0%/*}"

awk -v current="htpataic$1.txt" -f "$DIR/contents.awk" htpataic??.txt

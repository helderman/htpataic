#!/bin/bash

TOOLS="${0%/*}"

awk -v current="$2/htpataic$1.txt" -f "$TOOLS/contents.awk" "$2"/htpataic??.txt

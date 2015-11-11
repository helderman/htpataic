#!/bin/bash

DIR="${0%/*}"

if [ -z "$(diff --old-line-format=%L --new-line-format= --unchanged-line-format= "$@")" ]; then
	"$DIR/ldiff.sh" "$@"
else
	"$DIR/wdiff.sh" "$@"
fi

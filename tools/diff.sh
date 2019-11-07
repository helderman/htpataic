#!/bin/bash

TOOLS="${0%/*}"

if [ -z "$(diff --old-line-format=%L --new-line-format= --unchanged-line-format= "$@")" ]; then
	"$TOOLS/ldiff.sh" "$@"
else
	"$TOOLS/wdiff.sh" "$@"
fi

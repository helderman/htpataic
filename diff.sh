#!/bin/bash

if [ -z "$(diff --old-line-format=%L --new-line-format= --unchanged-line-format= $*)" ]; then
	./ldiff.sh $*
else
	./wdiff.sh $*
fi

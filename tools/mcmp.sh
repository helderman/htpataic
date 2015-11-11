#!/bin/bash

# mcmp.sh - multi-compare
# Usage: mcmp.sh file1 file2 [file3 ...]
# Example: mcmp.sh code??/makefile
# Rationale: helps me propagate changes in sample code through all chapters

version=1
while echo -e "\033[1;3$((version&7))mv$version $1\033[0m"; [ $# -gt 1 ]; do
	if ! cmp -s "$1" "$2" ; then
		((++version))
	fi
	shift
done

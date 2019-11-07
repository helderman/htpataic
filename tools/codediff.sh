#!/bin/bash

TOOLS="${0%/*}"

new="code$(printf "%02d" $1)/$3"
old="code$(printf "%02d" $(($1 - 1)))/$3"
if [[ ! -a "$old" ]] ; then old="$TOOLS/empty" ; fi
"$TOOLS/$2.sh" "$old" "$new" | awk -f "$TOOLS/codediff.awk"

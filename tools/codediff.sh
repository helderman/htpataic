#!/bin/bash

DIR="${0%/*}"

new="code$(printf "%02d" $1)/$3"
old="code$(printf "%02d" $(($1 - 1)))/$3"
if [[ ! -a "$old" ]] ; then old="$DIR/empty" ; fi
"$DIR/$2.sh" "$old" "$new" | awk -f "$DIR/codediff.awk"

#!/bin/bash

DIR="${0%/*}"

new="code$(printf "%02d" $2)/$3"
old="code$(printf "%02d" $(($2 - 1)))/$3"
if [[ ! -a "$old" ]] ; then old="$DIR/empty" ; fi
"$DIR/$1.sh" "$old" "$new" | awk -f "$DIR/codediff.awk"

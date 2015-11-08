#!/bin/bash
new=code$(printf "%02d" $2)/$3
old=code$(printf "%02d" $(($2 - 1)))/$3
if [[ ! -a $old ]] ; then old=empty ; fi
./$1.sh $old $new | awk -f codediff.awk

#!/bin/bash

DIR="${0%/*}"

while IFS= read -r line
do
	case "$line" in

	(\#contents)
		"$DIR/contents.sh" "$1"
		;;
	(\#new\ *|\#diff\ *|\#[lw]diff\ *)
		"$DIR/codediff.sh" ${line#\#}
		;;
	(\#test\ *)
		"$DIR/html.sh" "$(printf "code%02d/baseline.txt" ${line#\#test })"
		;;
	(*)
		echo "$line"
		;;
	esac
done < "$1"

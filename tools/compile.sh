#!/bin/bash

DIR="${0%/*}"

DEPS="htpataic$1.html: htpataic$1.txt"

while IFS= read -r line
do
	case "$line" in

	(\#contents)
		"$DIR/contents.sh" "$1"
		;;
	(\#new\ *|\#diff\ *|\#[lw]diff\ *)
		"$DIR/codediff.sh" "${1#0}" ${line#\#}
		DEPS+=" code$1/${line#* }"
		;;
	(\#test)
		"$DIR/html.sh" "code$1/baseline.txt"
		DEPS+=" code$1/baseline.txt"
		;;
	(\#map)
		echo '<img class="genmap" src="code'$1'/map.png" />'
		;;
	(\#zip)
		echo '<a href="code'$1'/src.zip">Download source code</a>'
		;;
	(*)
		echo "$line"
		;;
	esac
done < "htpataic$1.txt" > "htpataic$1.html"
echo "$DEPS" > "htpataic$1.d"

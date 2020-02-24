#!/bin/bash

# Directories
TOOLS="${0%/*}"
CODE="code$1"

# To build up a list of dependencies
DEPS="\$(HTML)/htpataic$1.html: \$(SRC)/htpataic$1.txt"

while IFS= read -r line
do
	case "$line" in

	(\#contents)
		"$TOOLS/contents.sh" "$1" "$3"
		;;
	(\#new\ *|\#diff\ *|\#[lw]diff\ *)
		"$TOOLS/codediff.sh" "${1#0}" ${line#\#}
		DEPS+=" $CODE/${line#* }"
		;;
	(\#test)
		"$TOOLS/html.sh" "$CODE/baseline.txt"
		DEPS+=" $CODE/baseline.txt"
		;;
	(\#map)
		echo "<img class=\"genmap\" src=\"$CODE/map.png\" />"
		;;
	(\#zip)
		echo "<a class=\"button\" href=\"$CODE/src.zip\">&#x2B73; &nbsp; Download source code</a>"
		echo "<a class=\"button\" href=\"https://repl.it/github/helderman/htpataic\">&#x1F300; &nbsp; Run on Repl.it</a>"
		;;
	(*)
		echo "$line"
		;;
	esac
done < "$3/htpataic$1.txt" > "$4/htpataic$1.html"

# Create (or overwrite) the dependencies file.
# This file should be included into our main makefile;
# just like you would with auto-dependencies created by gcc -M.
echo "$DEPS" > "$2"

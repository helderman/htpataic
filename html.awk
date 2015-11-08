#!/usr/bin/awk -f

{
	gsub(/&/, "\\&amp;");
	gsub(/</, "\\&lt;");
	gsub(/>/, "\\&gt;");
	print $0 "<br />";
}

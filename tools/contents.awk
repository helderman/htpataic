#!/usr/bin/awk -f

BEGIN	{ print "<h4>Contents</h4>"; }

/^<h2>/ {
	bold = FILENAME == current;
	url = FILENAME;
	sub(/^.*\//, "", url);
	sub(/\.txt$/, ".html", url);
	sub(/h2>/, bold ? "b>" : "a href=\"" url "\">");
	sub(/h2>/, bold ? "b>" : "a>");
	print "<div>" $0 "</div>";
}

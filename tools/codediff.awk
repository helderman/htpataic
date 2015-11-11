#!/usr/bin/awk -f

BEGIN	{ print "<ol>"; }
END	{ print "</ol>"; }

{
	gsub(/&/, "\\&amp;");
	gsub(/</, "\\&lt;");
	gsub(/>/, "\\&gt;");
	liClass = "old";
	if (/\[new\]/) {
		liClass = "new";
		$0 = "[old]" $0 "[new]";
		gsub(/\[old\]\[new\]/, "");
		gsub(/\[old\]/, "<span class=\"old\">");
		gsub(/\[new\]/, "</span>");
	}
	print "<li class=\"" liClass "\">" $0 "</li>";
}

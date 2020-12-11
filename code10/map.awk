BEGIN     { print "digraph map {"; }
/^- /     { outputEdges(); delete a; }
/^[ \t]/  { a[$1] = $2; }
END       { outputEdges(); print "}"; }

function outputEdges()
{
   outputEdge(a["location"], a["destination"], "");
   outputEdge(a["location"], a["prospect"], " [style=dashed]");
}

function outputEdge(from, to, style)
{
   if (from && to) print "\t" from " -> " to style;
}

BEGIN     { print "digraph map {"; }
/^- /     { outputEdges(); delete a; }
/^[ \t]/  { a[$1] = $2; }
END       { outputEdges(); print "}"; }

function outputEdges()
{
   outputEdge(a["location"], a["destination"]);
}

function outputEdge(from, to)
{
   if (from && to) print "\t" from " -> " to;
}

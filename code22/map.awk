BEGIN     { print "digraph map {\n\tnode [style=filled]"; }
/^- /     { outputEdges(); obj = $2; delete a; }
/^[ \t]/  { a[$1] = $2; }
END       { outputEdges(); outputNodes(); print "}"; }

function outputEdges()
{
   color[obj] = a["light"] ? "white" : "grey";
   outputEdge(a["location"], a["destination"], "");
   outputEdge(a["location"], a["prospect"], " [style=dashed]");
}

function outputEdge(from, to, style)
{
   if (to)
   {
      nodes[to] = 1;
      if (from)
      {
         nodes[from] = 1;
         print "\t" from " -> " to style;
      }
   }
}

function outputNodes()
{
   for (n in nodes) print "\t" n " [fillcolor=" color[n] "]";
}

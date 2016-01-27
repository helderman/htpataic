BEGIN               { print "digraph map {\n\tnode [style=filled, fillcolor=grey]"; }
/^- field$/         { print "\t" $2 " [fillcolor=white]"; }
/^- /               { outputEdge(); location = destination = prospect = ""; }
$1 == "location"    { location = $2; }
$1 == "destination" { destination = $2; }
$1 == "prospect"    { prospect = $2; }
END                 { outputEdge(); print "}"; }

function outputEdge()
{
   if (location && destination) print "\t" location " -> " destination;
   if (location && prospect) print "\t" location " -> " prospect " [style=dashed]";
}

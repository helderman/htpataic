BEGIN               { print "digraph map {\n\tnode [style=filled, fillcolor=grey]"; }
/^- /               { obj = $2; outputEdge(); location = destination = prospect = ""; }
$1 == "location"    { if ((location = $2) == "daylight") print "\t" obj " [fillcolor=white]"; }
$1 == "destination" { destination = $2; }
$1 == "prospect"    { prospect = $2; }
END                 { outputEdge(); print "}"; }

function outputEdge()
{
   if (location && destination) print "\t" location " -> " destination;
   if (location && prospect) print "\t" location " -> " prospect " [style=dashed]";
}

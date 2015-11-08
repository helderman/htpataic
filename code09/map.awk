BEGIN               { print "digraph map {"; }
/^- /               { outputEdge(); location = destination = ""; }
$1 == "location"    { location = $2; }
$1 == "destination" { destination = $2; }
END                 { outputEdge(); print "}"; }

function outputEdge()
{
   if (location && destination) print "\t" location " -> " destination;
}

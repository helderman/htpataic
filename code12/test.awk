#!/usr/bin/awk -f

BEGIN {
	print "spawn -noecho ./lilcave";
}

{
	print "expect \"\\n--> \" { send \"" $0 "\\r\" }";
}

END {
	print "expect eof";
}

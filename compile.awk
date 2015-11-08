#!/usr/bin/awk -f

{
	if (/^#contents$/)
	{
		system("./contents.sh " FILENAME);

	}
	else if (/^#(new|[lw]?diff) [0-9]+ /)
	{
		system("./codediff.sh " substr($1, 2) " " $2 " " $3);

	}
	else if (/^#test [0-9]+$/)
	{
		system(sprintf("awk -f html.awk code%02d/test.out", $2));
	}
	else
	{
		print;
	}
}

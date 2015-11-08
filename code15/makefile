all: test.out map.png

C = object.c misc.c match.c toggle.c location.c move.c execute.c parsexec.c main.c
H = object.h misc.h match.h toggle.h location.h move.h execute.h parsexec.h

test.out: test.in lilcave
	./test.sh

lilcave: $(C) $(H)
	gcc -Wall -Wextra $(C) -o $@

object.h: object.awk object.txt
	awk -v pass=h -f object.awk object.txt > $@

object.c: object.awk object.txt
	awk -v pass=c1 -f object.awk object.txt > $@
	awk -v pass=c2 -f object.awk object.txt >> $@

map.png: map.gv
	dot -Tpng -o $@ $<

map.gv: map.awk object.txt
	awk -f map.awk object.txt > $@

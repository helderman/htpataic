all: success.txt src.zip map.png

C = object.c misc.c match.c noun.c toggle.c location.c move.c reach.c inventory.c inventory2.c openclose.c parsexec.c main.c
H = object.h misc.h match.h noun.h toggle.h location.h move.h reach.h inventory.h inventory2.h openclose.h parsexec.h

success.txt: lilcave testscript.txt baseline.txt
	./test.sh
	mv -f transcript.txt $@

lilcave: $(C) $(H)
	gcc -Wall -Wextra -Wpedantic -Werror $(C) -o $@

object.h: object.awk object.txt
	awk -v pass=h -f object.awk object.txt > $@

object.c: object.awk object.txt
	awk -v pass=c1 -f object.awk object.txt > $@
	awk -v pass=c2 -f object.awk object.txt >> $@

map.png: map.gv
	dot -Tpng -o $@ $<

map.gv: map.awk object.txt
	awk -f map.awk object.txt > $@

src.zip: $(C) $(H) object.txt makefile testscript.txt baseline.txt
	zip -rq $@ $^

clean:
	$(RM) object.c object.h lilcave map.gv map.png transcript.txt success.txt src.zip

all: lilcave success.txt src.zip map.png

C = object.c misc.c match.c noun.c toggle.c location.c move.c reach.c inventory.c inventory2.c openclose.c onoff.c talk.c damage.c attack.c turn.c expand.c parsexec.c main.c
H = object.h misc.h match.h noun.h toggle.h location.h move.h reach.h inventory.h inventory2.h openclose.h onoff.h talk.h damage.h attack.h turn.h expand.h parsexec.h

success.txt: lilcave.testable testscript.txt baseline.txt
	./lilcave.testable testscript.txt > transcript.txt
	gcov *.gcda | tee codecoverage.txt | tail -n1
	cmp baseline.txt transcript.txt
	mv -f transcript.txt $@

lilcave.testable: $(C) $(H)
	gcc --coverage $(C) -o $@

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
	$(RM) object.c object.h lilcave map.gv map.png lilcave.testable *.gcda *.gcno *.gcov codecoverage.txt transcript.txt success.txt src.zip

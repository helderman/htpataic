all: success.txt src.zip

C = object.c misc.c noun.c location.c parsexec.c main.c
H = object.h misc.h noun.h location.h parsexec.h

success.txt: lilcave testscript.txt baseline.txt
	./test.sh
	mv -f transcript.txt $@

lilcave: $(C) $(H)
	gcc -Wall -Wextra -Wpedantic -Werror $(C) -o $@

src.zip: $(C) $(H) makefile testscript.txt baseline.txt
	zip -rq $@ $^

clean:
	$(RM) lilcave transcript.txt success.txt src.zip

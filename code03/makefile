C = location.c parsexec.c main.c
H = location.h parsexec.h

success.txt: lilcave testscript.txt baseline.txt
	./test.sh
	mv -f transcript.txt $@

lilcave: $(C) $(H)
	gcc -Wall -Wextra -Wpedantic -Werror $(C) -o $@

clean:
	$(RM) lilcave transcript.txt success.txt

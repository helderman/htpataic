C = parsexec.c main.c
H = parsexec.h

success.txt: lilcave testscript.txt baseline.txt
	./test.sh
	mv -f transcript.txt $@

lilcave: $(C) $(H)
	gcc -Wall -Wextra -Wpedantic $(C) -o $@

clean:
	$(RM) lilcave transcript.txt success.txt

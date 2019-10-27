success.txt: lilcave testscript.txt baseline.txt
	./test.sh
	mv -f transcript.txt $@

lilcave: main.c
	gcc -Wall -Wextra -Wpedantic -Werror main.c -o $@

clean:
	$(RM) lilcave transcript.txt success.txt

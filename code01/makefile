all: success.txt src.zip

success.txt: lilcave testscript.txt baseline.txt
	./test.sh
	mv -f transcript.txt $@

lilcave: main.c
	gcc -Wall -Wextra -Wpedantic -Werror main.c -o $@

src.zip: main.c makefile testscript.txt baseline.txt
	zip -rq $@ $^

clean:
	$(RM) lilcave transcript.txt success.txt src.zip

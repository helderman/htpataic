C = object.c misc.c noun.c location.c parsexec.c main.c
H = object.h misc.h noun.h location.h parsexec.h

test.out: test.in lilcave
	./test.sh

lilcave: $(C) $(H)
	gcc -Wall -Wextra -Wpedantic -Werror $(C) -o $@

clean:
	$(RM) lilcave

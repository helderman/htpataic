C = object.c misc.c noun.c location.c move.c inventory.c parsexec.c main.c
H = object.h misc.h noun.h location.h move.h inventory.h parsexec.h

test.out: test.in lilcave
	./test.sh

lilcave: $(C) $(H)
	gcc -Wall -Wextra $(C) -o $@

clean:
	$(RM) lilcave

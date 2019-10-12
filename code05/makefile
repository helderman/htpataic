C = object.c misc.c noun.c location.c move.c exec_move.c parsexec.c main.c
H = object.h misc.h noun.h location.h move.h exec_move.h parsexec.h

test.out: test.in lilcave
	./test.sh

lilcave: $(C) $(H)
	gcc -Wall -Wextra $(C) -o $@

clean:
	$(RM) lilcave

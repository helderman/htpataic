C = object.c misc.c match.c location.c move.c execute.c parsexec.c main.c
H = object.h misc.h match.h location.h move.h execute.h parsexec.h

test.out: test.in lilcave
	./test.sh

lilcave: $(C) $(H)
	gcc -Wall -Wextra $(C) -o $@

C = location.c parsexec.c main.c
H = location.h parsexec.h

test.out: test.in lilcave
	./test.sh

lilcave: $(C) $(H)
	gcc -Wall -Wextra -Wpedantic -Werror $(C) -o $@

clean:
	$(RM) lilcave

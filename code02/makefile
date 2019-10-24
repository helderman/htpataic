C = parsexec.c main.c
H = parsexec.h

test.out: test.in lilcave
	./test.sh

lilcave: $(C) $(H)
	gcc -Wall -Wextra -Wpedantic $(C) -o $@

clean:
	$(RM) lilcave

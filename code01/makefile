test.out: test.in lilcave
	./test.sh

lilcave: main.c
	gcc -Wall -Wextra -Wpedantic -Werror main.c -o $@

clean:
	$(RM) lilcave

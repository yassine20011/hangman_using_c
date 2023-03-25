main: game.c functions.c
	gcc -o game game.c functions.c -Wall -Wextra -Werror -lcurses

test: test.c
	gcc -o test test.c -Wall -Wextra -Werror -lcurses

clean: rm -f game


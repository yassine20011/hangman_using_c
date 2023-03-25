main: game.c functions.c
	gcc -o game game.c functions.c -Wall -Wextra -Werror 

clean: rm -f game
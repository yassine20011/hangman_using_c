main: src/main.c src/util.c
	gcc -o bin/pendu src/main.c src/util.c src/hint.c -Wall -Wextra -Werror -lcurses

test: test.c
	gcc -o bin/test test.c src/hint.c -Wall -Wextra -Werror -lcurses

clean: rm -f bin/game

run: bin/pendu
	./bin/pendu

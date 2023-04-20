main: src/main.c src/util.c
	gcc -o bin/pendu src/main.c src/util.c -Wall -Wextra -Werror -lcurses

test: test.c
	gcc -o test test.c -Wall -Wextra -Werror -lcurses -lcurl

clean: rm -f bin/game

run: bin/pendu
	./bin/pendu

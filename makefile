main: src/main.c src/util.c
	gcc -o bin/pendu src/main.c src/util.c src/hint.c -Wall -Wextra -Werror -lcurses

test: test.c
	gcc -o bin/test test.c src/hint.c -Wall -Wextra -Werror -lcurses

clean: rm -f bin/game

container: docker build -t hello-world .
	docker run -t -i -e "PULSE_SERVER=/mnt/wslg/PulseServer" -v \\wsl$\Ubuntu\mnt\wslg:/mnt/wslg/ hello-world

run: bin/pendu
	./bin/pendu

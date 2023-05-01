# Jeu du PENDU

## Description
Ce jeu est un jeu de pendu. Le but est de trouver le mot caché en entrant des lettres. Si le mot est trouvé, le joueur gagne. Sinon, le joueur perd.

## What we use to achieve this project?
* C language (gcc compiler)
* Makefile {to compile the project}
* Git {to version the project}
## Project structure
* src/ : contains all the source files
* include/ : contains all the header files
* bin/ : contains the executable file

## How to compile the project?
* Open a terminal
* Go to the project directory
* Type `make` to compile the project
* Type `make clean` to delete the object files

you can also use the `make run` command to compile and run the project

This game build with C language and makefile in Subsystem Linux (WSL) in Windows 11
it may not work on other Operating Systems.

## How to play?
* Open a terminal
* Go to the project directory
* Type `./bin/pendu` to run the game
* Type `./bin/pendu -h` to see the help


## librairies used

* unistd.h
* ctype.h
* time.h
* string.h
* ncurses.h(for positioning the cursor)

I converted the mp3 to wav using the following command:
`ffmpeg -i input.mp3 -acodec pcm_s16le -ac 1 -ar 16000 output.wav`


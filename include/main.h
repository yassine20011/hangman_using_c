#pragma once

#include <stdio.h>
#include <ncurses.h>
#include "util.h"
#include "hint.h"
#include <unistd.h> 
#include <termios.h> // for tcgetattr(), tcsetattr()

struct main
{
    char words[256][256]; // words array
};

struct main data;
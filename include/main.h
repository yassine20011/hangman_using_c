#pragma once

#include <stdio.h>
#include <ncurses.h>
#include "util.h"
#include "hint.h"
#include <unistd.h> 
#include <termios.h> // for tcgetattr(), tcsetattr()
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include <time.h>


struct main
{
    char words[256][256]; // words array
};

extern struct main data;
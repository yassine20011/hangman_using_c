#include "../include/main.h"

struct playerData player;
struct main data;

/**
 * The function displays an introduction to the Hangman game and waits for a keypress to start playing
 * while disabling input buffering and echoing in the terminal.
 */
void intro(void)
{
    char text[] = {"Hello! Welcome to Hangman. This is a classic word-guessing game where you have to guess a hidden word by suggesting letters one at a time.\n\nFor each incorrect guess, a part of a 'hangman' is drawn on the screen. You have to guess the word before the hangman is complete, or you lose the game.\n\nTo get started, you will need to input a letter to guess the hidden word.If the letter you guessed is in the word, it will be revealed on the screen.\nIf not, a part of the hangman will be drawn on the screen.You win the game if you successfully guess the word before the hangman is complete.\n\nPress any key to start playing and see how many words you can guess correctly.Good luck !"};

    system("nohup aplay intro.wav > /dev/null 2>&1 &");

    for (int i = 0; text[i] != '\0'; i++)
    {
        printf("%c", text[i]);
        fflush(stdout); // flushes the output buffer of a stream
        usleep(56750);
    }

    // wait for a keypress to continue
    printf("\n\n\n");
    printf("Press any key to start playing...");
    fflush(stdout);

    /* This code block is disabling input buffering and echoing in the terminal. */
    struct termios old_term, new_term;
    tcgetattr(STDIN_FILENO, &old_term);
    new_term = old_term;
    new_term.c_lflag &= ~(ICANON | ECHO); // ~ = bitwise NOT operator (inverts each bit)
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);

    // read a single character
    getchar();

    // restore the old terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
}

/**
 * The main function calls three other functions.
 *
 * @return an integer value of 0.
 */
int main()
{
    intro();
    Welcome();
    Game();
    return 0;
}
#include "../include/main.h"

/**
 * The main function reads user input and calls different functions based on the user's choice.
 *
 * @return The function `main()` is returning an integer value of 0.
 */
int main()
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

    // disable input buffering and echoing
    struct termios old_term, new_term;
    tcgetattr(STDIN_FILENO, &old_term);
    new_term = old_term;
    new_term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);

    // read a single character
    char ch = getchar();

    // restore the old terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);

    // continue with the game
    printf("\n");
    printf("You pressed the '%c' key. Let's play!\n", ch);
    // your code continues here...

    Welcome();
    Game();

    return 0;
}
#include <ncurses.h>
#include <stdio.h>


int main()
{
    int counter = 0;

    // Initialize ncurses
    initscr();

    // Print the initial value of the counter
    printw("entre un nombre: ");
    refresh();

    // Wait for user input
    while (1)
    {
        int c = getch();
        if (c == 'q')
            break;
        else if (c == 'a')
            counter++;
        else if (c == 'z')
            counter--;
        else
            continue;

        // Clear the screen
        clear();

        // Print the new value of the counter
        printw("entre un nombre: %d", counter);
        refresh();
    }

    // Exit ncurses
    endwin();

    return 0;
}

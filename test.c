#include <ncurses.h>
#include <unistd.h>
#include <time.h>

int main()
{
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_WHITE);

    attron(COLOR_PAIR(1));
    mvprintw(0, 0, "Hello World!");
    attroff(COLOR_PAIR(1));
    refresh();

    getch();
    endwin();

    return 0;
}

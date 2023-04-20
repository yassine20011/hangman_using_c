#include "../include/main.h"

int main()
{

        Welcome();
        if (player.choice == 1)
            Game();
        else if (player.choice == 2)
        {
            gameMenu(0);
            difficultyMenu(50);
        }
        else if (player.choice == 3)
        {
            mvprintw(10, 50, "Merci d'avoir joué!");
            exit(0);
        }
        else
        {
            mvprintw(10, 50, "Erreur de choix!");
            exit(0);
        }

    return 0;
}
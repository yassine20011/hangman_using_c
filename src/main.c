#include "../include/main.h"

int main()
{
    Welcome();
    if (player.choice == 1)
        Game();
    else if (player.choice == 2)
    {
        printf("Options\n");
    }
    else if (player.choice == 3)
    {
        printf("Au revoir!\n");
        exit(0);
    }
    else
    {
        printf("Choix invalide!\n");
        exit(0);
    }

    return 0;
}
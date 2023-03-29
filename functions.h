#include <stdlib.h>
#define random(min, max) (rand() % (max - min + 1) + min)
#define arrayLen(array) (sizeof(array) / sizeof(array[0]))

// char *F_GREEN = "\033[0;32m";
// char *F_YELLOW = "\033[0;33m";
// char *F_BLUE = "\033[0;34m";

// char *B_RED = "\033[0;41m";
// char *B_GREEN = "\033[0;42m";
// char *B_YELLOW = "\033[0;43m";
// char *B_BLUE = "\033[0;44m";

// char *UL_N = "\033[4;0m";         /*Underline with no colour*/
// char *UL_F_RED = "\033[4;31m";    /*Underline in red*/
// char *UL_F_GREEN = "\033[4;32m";  /*Underline in green*/
// char *UL_F_YELLOW = "\033[4;33m"; /*Underline in yellow*/
// char *UL_F_BLUE = "\033[4;34m";   /*Underline in yellow*/


void Welcome(void);
void Game(void);
void findLetterIndex(char *word, char letter);

int str_len(char *str);

struct playerData
{
    char name[20]; // Player name
    char letter; // la lettre entrée par le joueur
    char replay; // Rejouer ou non
    char word[20]; // Le mot à trouver
    char alreadyFound[40]; // Les lettres déjà trouvées
    int indexs[20]; // Les indexs des lettres trouvées
    int chance; // Le nombre de chance du joueur
    int choice; // Le choix du joueur
    int difficulty; // La difficulté du jeu
};

struct playerData player;

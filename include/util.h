#ifndef UTIL_H
#define UTIL_H


#include <stdlib.h>



// A macro that returns the length of an array.
#define arrayLen(array) (sizeof(array) / sizeof(array[0])) // for example: arrayLen(words) will return the length of the words array.

void Welcome(void);
void Game(void);
void findLetterIndex(char *word, char letter);
int isExist(char *word, char letter);
void rePlay(void);
void keyboard(int X, int Y);
void gameMenu(int position);
void difficultyMenu(int position);

struct playerData
{
    char name[20]; // Player name
    char letter; // la lettre entrée par le joueur
    char replay; // Rejouer ou non
    char word[20]; // le mot a trouver par le joueur
    char alreadyFound[40]; // Les lettres déjà trouvées
    int indexs[20]; // Les indexs des lettres trouvées
    int chance; // Le nombre de chance du joueur
    int theme; // Le thème du jeu
    int difficulty; // La difficulté du jeu
};

struct playerData player;




#endif



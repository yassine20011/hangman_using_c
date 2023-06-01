#pragma once

#include <stdlib.h>


// A macro that returns the length of an array.
#define arrayLen(array) (sizeof(array) / sizeof(array[0])) // for example: arrayLen(words) will return the length of the words array.

void Welcome(void);
void Game(void);
void findLetterIndex(char *word, char letter);
int isExist(char *word, char letter);
void rePlay(void);
void keyboard(int X, int Y);
void difficultyMenu(int position);
int _random(int min, int max);
void theme(int position);

struct playerData
{
    char name[50]; // Player name
    char letter; // la lettre entrée par le joueur
    char replay; // Rejouer ou non
    char word[20]; // le mot a trouver par le joueur
    char alreadyFound[40]; // Les lettres déjà trouvées
    int indexs[20]; // Les indexs des lettres trouvées
    int chance; // Le nombre de chance du joueur
    int theme; // Le thème du jeu
    int difficulty; // La difficulté du jeu
};

extern struct playerData player;


typedef struct {
    char guessed_words[20][50]; // guessed words
    int num_words; // number of words
    int score; // score
} PlayerStats;

extern PlayerStats person;
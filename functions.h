#include <stdlib.h>

#define random(min, max) (rand() % (max - min + 1) + min)
#define arrayLen(array) (sizeof(array) / sizeof(array[0]))

void Welcome(void);
void Game(void);
void findLetterIndex(char *word, char letter);

int str_len(char *str);

struct playerData
{
    char name[20];
    char username[20];
    char letter;
    char word[20];
    int indexs[20];
    int chance;
    int choice;
    int difficulty;
    int level;
};

struct playerData player;

#include <stdio.h>
#include <unistd.h>
#include "functions.h"
#include <ctype.h>
#include <time.h>
#include <time.h>

int difficulty[] = {10, 5, 3};

int str_len(char *str)
{
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}

char penduSurface[11][10] = {
    "_________",
    "|       |",
    "|       |",
    "|       O",
    "|      /|\\",
    "|      / \\",
    "|",
    "|",
    "|",
    "|",
    "_________",
};

void Welcome(void)
{
    int c;
    printf("|---------------------------------------|\n");
    printf("| Bienvenue dans le jeu du pendu!       |\n");
    printf("|---------------------------------------|\n");
    printf("  Saisissez votre nom: ");
    scanf("%s", player.name);
    printf("|---------------------------------------|\n");
    printf("  Saisissez votre username: ");
    scanf("%s", player.username);
    printf("|---------------------------------------|\n");

    printf("Bonjour %s, votre username est %s\n", player.name, player.username);

    // loading animation
    printf("\nVeuillez patienter");
    int i = 0;
    while (i < 3)
    {
        printf(".");
        fflush(stdout);
        sleep(1);
        i++;
    }
    printf("\n");

    // difficulty menu
    printf("Choisissez votre niveau de difficulte:\n\n");
    printf("\t1. Facile\n");
    printf("\t2. Moyen\n");
    printf("\t3. Difficile\n\n");

    printf("Saisissez votre choix: ");
    scanf("%d", &player.difficulty);
    while ((c = getchar()) != '\n' && c != EOF)
    {
    } // clear buffer

    // game menu
    printf("Menu du jeu :\n\n");
    printf("\t1. Jouer\n");
    printf("\t2. Options\n");
    printf("\t3. Quitter\n\n");

    printf("Saisissez votre choix: ");
    scanf("%d", &player.choice);
    while ((c = getchar()) != '\n' && c != EOF)
    {
    } // clear buffer
}

void findLetterIndex(char *word, char letter)
{
    int i = 0;
    while (word[i] != '\0')
    {
        player.indexs[i] = 0;
        if (word[i] == letter)
        {
            player.indexs[i] = i + 1;
        }
        i++;
    }
}

int isExist(char *word, char letter)
{
    int i = 0;
    while (word[i] != '\0')
    {
        if (word[i] == letter)
            return 1;
        i++;
    }
    return 0;
}

void Game(void)
{
    srand(time(NULL)); // pour avoir des nombres aleatoires sans repetition
    int c, index = 0;
    char *words[] = {"jeu", "pendu", "programmation", "c", "python", "javascript", "java", "c++", "c#", "php", "ruby", "swift", "go", "rust", "kotlin", "dart", "scala", "haskell", "erlang", "elixir", "prolog", "clojure", "lisp", "fortran", "cobol", "pascal", "ada", "perl", "lua", "bash", "zsh"};
    int wordsLen = arrayLen(words);
    char *randomWord = words[random(0, wordsLen - 1)];
    int wordLen = str_len(randomWord);

    printf("Le mot a trouver contient %d lettres\n", wordLen);
    printf("\nPendu sur les langages de programmation\n\n");
    printf("Vous avez %d chances pour trouver le mot\n\n", difficulty[player.difficulty - 1]);

    printf("%s\n", randomWord);
    do
    {
        printf("\rSaisissez une lettre: ");
        fflush(stdout);
        player.letter = getchar();
        while ((c = getchar()) != '\n' && player.letter != EOF)
        {
        }

        if (isalpha(player.letter) || player.letter == 32 || player.letter == 39)
        {
            findLetterIndex(randomWord, player.letter);
            for (unsigned int i = 0; i < arrayLen(player.indexs); i++)
            {
                if (player.indexs[i] != 0)
                {
                    player.word[player.indexs[i] - 1] = player.letter;
                }

                if (isExist(player.word, player.letter) == 0)
                    player.chance++;
                else
                {
                    for (int j = 0; j < wordLen; j++)
                    {
                        if (player.word[j] == '\0')
                        {
                            printf("_ ");
                        }
                        else
                        {
                            printf("%c ", player.word[j]);
                        }
                    }
                    printf("\n");
                }
            }
        }
        else
        {
            printf("Saisie invalide!\n");
        }

    } while (player.chance < difficulty[player.difficulty - 1]);
}
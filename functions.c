#include <stdio.h>
#include <unistd.h>
#include "functions.h"
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>
#define COLOR_RED 1
#define COLOR_GREEN 2
#define COLOR_YELLOW 3
#define COLOR_BLUE 4

int difficulty[] = {10, 5, 3};

char *F_RED = "\033[0;31m";
char *RMF = "\033[0;00m";

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

void keyboard(int X, int Y)
{
    int x = X, y = Y;
    int alpha = 65;
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK); 
    init_pair(2, COLOR_GREEN, COLOR_BLACK);

    mvprintw(30, y, "+===+===+===+===+===+===+\n");
    attron(COLOR_PAIR(2));
    mvprintw(31, y, "|  ALLOWED CHARACTERS:  |\n");
    attroff(COLOR_PAIR(2));
    mvprintw(32, y, "+===+===+===+===+===+===+\n");
    refresh();
    for (size_t i = 0; i < 26; i++)
    {
        if (isExist(player.alreadyFound, alpha) == 0)
        {
            mvprintw(x + 1, y, "| %c |", alpha);
            refresh();
        }
       
        else
        {
            mvprintw(x + 1, y, "|");
            addch(' ');
            attron(COLOR_PAIR(1));
            addch(alpha);
            attroff(COLOR_PAIR(1));
            addch(' ');
            addch('|');
            refresh();
        }
        y += 4;
        if (y == Y + 24)
        {
            mvprintw(x + 1, y, "|\n");
            mvprintw(x + 2, Y, "+===+===+===+===+===+===+\n");
            refresh();
            y = Y;
            x += 2;
        }
        alpha++;
    }
    mvprintw(x + 1, y, "| SPACE | ' | - |\n");
    mvprintw(x + 2, Y, "+===+===+===+===+===+===+\n");
    refresh();

    usleep(1000000);
}

int str_len(char *str)
{
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}

char penduSurface[11][11] = {
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
    initscr();     /* Start curses mode 		  */
    start_color(); /* enable color */

    mvprintw(0, 0, "Bienvenue dans le jeu du pendu!");
    mvprintw(2, 0, "Saisissez votre nom: ");
    refresh();
    getstr(player.name);

    mvprintw(4, 0, "Bienvenue %s !", player.name);
    refresh();
    sleep(1);

    // difficulty menu
    mvprintw(0, 50, "Menu de difficulte :\n\n");
    refresh();
    mvprintw(2, 50, "\t1. Facile\n");
    mvprintw(3, 50, "\t2. Moyen\n");
    mvprintw(4, 50, "\t3. Difficile\n\n");
    mvprintw(6, 50, "Choisissez le niveau de difficulte: ");
    refresh();
    scanw("%d", &player.difficulty);

    // game menu
    mvprintw(0, 100, "Menu du jeu :\n\n");
    refresh();
    mvprintw(2, 100, "\t1. Nouvelle partie\n");
    mvprintw(3, 100, "\t2. Charger difficulte du jeu\n");
    mvprintw(4, 100, "\t3. Quitter\n\n");
    mvprintw(6, 100, "Saisissez votre choix: ");
    refresh();
    scanw("%d", &player.choice);

    int i = 0;
    while (i < 11)
    {
        mvprintw(10 + i, 0, penduSurface[i]);
        refresh();
        i++;
    }

    // loading animation
    mvprintw(15, 60, "Chargement");
    refresh();
    i = 0;
    while (i < 3)
    {
        mvprintw(15, 70 + i, ".");
        refresh();
        sleep(1);
        i++;
        printf("\r");
    }
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

void rePlay(void)
{
    mvprintw(0, 0, "Voulez-vous rejouer? (y/n): ");
    refresh();
    player.replay = getchar();
    if (player.replay == 'y')
        Game();
    else if (player.replay == 'n')
    {
        mvprintw(0, 0, "Au revoir!\n");
        clear();
    }
    else
    {
        mvprintw(0, 0, "Choix invalide!\n");
        clear();
    }
}

void Game(void)
{
    srand(time(NULL)); // pour avoir des nombres aleatoires sans repetition
    char *words[] = {
        "jeu", "pendu", "programmation", "c", "python",
        "javascript", "java", "c++", "c#", "php", "ruby",
        "swift", "go", "rust", "kotlin", "dart", "scala",
        "haskell", "erlang", "elixir", "prolog", "clojure",
        "lisp", "fortran", "cobol", "pascal", "ada", "perl",
        "lua", "bash", "zsh"};

    int wordsLen = arrayLen(words);
    char *randomWord = words[random(0, wordsLen - 1)];
    int wordLen = str_len(randomWord);
    int k = 0;

    mvprintw(25, 50, "Le mot a trouver contient %d lettres\n\n", wordLen);
    mvprintw(26, 50, "Pendu sur les langages de programmation\n\n");
    refresh();

    do
    {

        if (strcmp(randomWord, player.word) == 0)
        {
            mvprintw(50, 0, "Vous avez gagne!\n");
            clear();
            rePlay();
        }
        else if (player.chance >= difficulty[player.difficulty - 1])
        {
            mvprintw(50, 0, "Vous avez perdu!\n");
            clear();
            rePlay();
        }

        mvprintw(25, 0, "Chances restantes: %02d", (difficulty[player.difficulty - 1] - player.chance));
        mvprintw(26, 0, "Word: %s", randomWord);
        refresh();

        keyboard(32, 50);
        mvprintw(28, 50, "Saisissez une lettre: ");
        refresh();
        player.letter = getchar();

        if (isExist(randomWord, player.letter))
        {
            mvprintw(15, 60, "La lettre %c existe dans le mot\n", player.letter);
            refresh();
        }
        else
        {
            mvprintw(15, 60, "La lettre %c n'existe pas dans le mot\n", player.letter);
            refresh();
            player.chance++;
            int i = difficulty[player.difficulty - 1] + 1;
            int j = difficulty[player.difficulty - 1] - player.chance;
            while (i >= j)
            {
                mvprintw(15 + i, 100, penduSurface[i]);
                refresh();
                usleep(500000); // 500000 microsecondes = 0.5 seconde
                i--;
            }
        }

        if (isalpha(player.letter) || player.letter == ' ' || player.letter == '-' || player.letter == '\'')
        {
            findLetterIndex(randomWord, player.letter);
            if (player.letter >= 'a' && player.letter <= 'z')
            {
                player.alreadyFound[k] = toupper(player.letter);
                k++;
            }

            int i = 0;
            while (i < wordLen)
            {
                if (player.indexs[i] != 0)
                {
                    player.word[i] = player.letter;
                    for (int j = 0; j < wordLen; j++)
                    {
                        if (player.word[j] == '\0')
                        {
                            mvprintw(27, 2 * j, "_ "); // 2 * j pour l'espacement entre les lettres du mot
                            refresh();
                        }
                        else if (player.word[j] == ' ')
                        {
                            mvprintw(27, 2 * j, "_ ");
                            refresh();
                        }
                        else
                        {
                            mvprintw(27, 2 * j, "%c ", player.word[j]);
                            refresh();
                        }
                    }
                }
                i++;
            }
        }
        else
        {
            mvprintw(20, 50, "La lettre %c n'est pas valide\n", player.letter);
            refresh();
        }

    } while (1);

    endwin(); /* End curses mode		  */
}

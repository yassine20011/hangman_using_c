#include <unistd.h>
#include "functions.h"
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>

// global variables
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
int difficulty[] = {10, 5, 3}; // the number of tries for each difficulty

/**
 * It takes a word and a letter and finds the index of the letter in the word.
 *
 * @param word The word that the player is trying to guess.
 * @param letter The letter that the player guessed
 */
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

/**
 * It returns 1 if the letter is in the word, otherwise it returns 0
 *
 * @param word the word that the user is trying to guess
 * @param letter the letter that the user has guessed
 *
 * @return The function isExist() returns 1 if the letter is found in the word, and 0 if it is not.
 */
int isExist(char *word, char letter)
{
    int i = 0;
    while (word[i] != '\0')
    {
        if (word[i] == letter)
            return 1; // vrai
        i++;
    }
    return 0; // faux
}

/**
 * It asks the user if he wants to replay the game, and if he does, it clears the screen and calls the
 * Game() function again
 *
 */
void rePlay(void)
{
    mvprintw(0, 0, "Voulez-vous rejouer? (y/n): ");
    refresh();
    player.replay = getchar();
    if (player.replay == 'y')
    {
        clear();
        for (size_t i = 0; player.alreadyFound[i]; i++)
            player.alreadyFound[i] = '\0';
        for (size_t i = 0; player.word[i] != '\0'; i++)
            player.word[i] = '\0';

        Game();
    }
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

/**
 * It prints a table of allowed characters in the game.
 *
 * @param X The x coordinate of the cursor.
 * @param Y The y-coordinate of the top-left corner of the box.
 */
void keyboard(int X, int Y)
{
    int x = X, y = Y;
    int alpha = 65;

    start_color();                          // start color mode
    init_pair(1, COLOR_RED, COLOR_BLACK);   // Red
    init_pair(2, COLOR_GREEN, COLOR_WHITE); // Green

    mvprintw(X, y, "+===+===+===+===+===+===+\n");
    mvprintw(X - 1, y, "|");
    addch(' ');
    attron(COLOR_PAIR(2));
    addstr(" ALLOWED CHARACTERS: ");
    attroff(COLOR_PAIR(2));
    addch(' ');
    addch('|');
    mvprintw(X - 2, y, "+===+===+===+===+===+===+\n");
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

/* It's the function that is called in the main function, it's the function that prints the welcome
message, the difficulty menu, the game menu, and the loading animation. */
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

    // loading animation
    int i = 0, j = 0;
    mvprintw(15, 60, "Chargement du jeu");
    refresh();
    while (i < 3)
    {
        while (j < 3)
        {
            mvprintw(15, 78 + j, ".");
            refresh();
            usleep(500000);
            j++;
        }
        while (j > 0)
        {
            mvprintw(15, 81 - j, " ");
            refresh();
            j--;
        }
        j = 0;
        i++;
    }
    clear();
}

/**
 * The function Game() is the main function of the game, it contains the main loop of the game, it's
 * the function that will be called in the main function
 */
void Game(void)
{
    srand(time(NULL)); // pour avoir des nombres aleatoires sans repetition

    char *words[] = {
        "jeu", "pendu", "programmation", "python",
        "javascript", "java", "php", "ruby",
        "swift", "go", "rust", "kotlin", "dart", "scala",
        "haskell", "erlang", "elixir", "prolog", "clojure",
        "lisp", "fortran", "cobol", "pascal", "ada", "perl",
        "lua", "bash", "zsh"};

    int wordsLen = arrayLen(words);
    char *randomWord = words[random(0, wordsLen - 1)];
    int wordLen = strlen(randomWord);
    int k = 0;

    mvprintw(2, 100, "Le mot a trouver contient %d lettres\n\n", wordLen);
    mvprintw(3, 100, "Pendu sur les langages de programmation\n\n");
    refresh();

    do
    {

        /* Checking if the player has won the game. */
        if (strcmp(randomWord, player.word) == 0)
        {
            attron(COLOR_PAIR(1));
            mvprintw(2, 100, "Vous avez gagne!\n");
            attroff(COLOR_PAIR(1));
            int i = 0;
            while (i < 6)
            {

                mvprintw(1, 0, "game restart in %d", 5 - i);
                refresh();
                sleep(1);
                i++;
                printf("\r");
            }
            clear();
            rePlay();
        }
        else if (player.chance >= difficulty[player.difficulty - 1])
        {
            clear();
            mvprintw(21,60,"  _____                                                            \n");
            mvprintw(22,60," / ____|                                                           \n");
            mvprintw(23,60,"| |  __    __ _   _ __ ___     ___      ___   __   __   ___   _ __ \n");
            mvprintw(24,60,"| | |_ |  / _` | | '_ ` _ \\   / _ \\    / _ \\  \\ \\ / /  / _ \\ | '__|\n");
            mvprintw(25,60,"| |__| | | (_| | | | | | | | |  __/   | (_) |  \\ V /  |  __/ | |   \n");
            mvprintw(26,60," \\_____|  \\__,_| |_| |_| |_|  \\___|    \\___/    \\_/    \\___| |_|   \n");
            rePlay();
        }

        /* It's printing the number of chances left and the word to guess. */
        mvprintw(2, 0, "Chances restantes: %02d", (difficulty[player.difficulty - 1] - player.chance));
        mvprintw(3, 0, "Word: %s", randomWord);
        refresh();

        /* It's printing the keyboard on the screen. */
        mvprintw(2, 50, "Saisissez une lettre: ");
        keyboard(8, 50);
        refresh();
        player.letter = getchar(); // get the letter from the player

        /* It's checking if the letter that the player has guessed is in the word, if it is, it prints a
        message to the player, otherwise it prints another message. */
        if (isExist(randomWord, player.letter))
        {
            mvprintw(5, 0, "La lettre %c existe dans le mot\n", player.letter);
            refresh();
        }
        else
        {
            mvprintw(5, 0, "La lettre %c n'existe pas dans le mot\n", player.letter);
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

        /* It's checking if the letter allowed to the player to guess the word. */
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
                    player.word[i] = player.letter; // ajouter la lettre dans le mot a trouver par le joueur
                    for (int j = 0; j < wordLen; j++)
                    {
                        if (player.word[j] == '\0')
                        {
                            mvprintw(10, 2 * j, "_ "); // 2 * j pour l'espacement entre les lettres du mot
                            refresh();
                        }
                        else if (player.word[j] == ' ')
                        {
                            mvprintw(10, 2 * j, "_ ");
                            refresh();
                        }
                        else
                        {
                            mvprintw(10, 2 * j, "%c ", player.word[j]);
                            refresh();
                        }
                    }
                }
                i++;
            }
        }
        else
        {

            attron(COLOR_PAIR(1));
            mvprintw(5, 0, "Message: ");
            attroff(COLOR_PAIR(1));
            mvprintw(5, 9, "La lettre %c n'est pas valide\n", player.letter);
        }

    } while (1);

    
    endwin(); /* End curses mode		  */
}

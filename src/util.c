#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>
#include "../include/util.h"
#include "../include/hint.h"



char penduSurface[11][11] = {
    "_________",   // 0
    "|       |",   // 1
    "|       |",   // 2
    "|       O",   // 3
    "|      /|\\", // 4
    "|      / \\", // 5
    "|",           // 6
    "|",           // 7
    "|",           // 8
    "|",           // 9
    "_________",   // 10
};

char *winAcsiiArt[6] = {
    "__     __   ____    _    _    __          __  _____   _   _   _ ",
    "\\ \\   / /  / __ \\  | |  | |   \\ \\        / / |_   _| | \\ | | | |",
    " \\ \\_/ /  | |  | | | |  | |    \\ \\  /\\  / /    | |   |  \\| | | |",
    "  \\   /   | |  | | | |  | |     \\ \\/  \\/ /     | |   | . ` | | |",
    "   | |    | |__| | | |__| |      \\  /\\  /     _| |_  | |\\  | |_|",
    "   |_|     \\____/   \\____/        \\/  \\/     |_____| |_| \\_| (_)",
};

char *loseAcsiiArt[6] = {
    "  _____              __  __   ______      ____   __      __  ______   _____  ",
    " / ____|     /\\     |  \\/  | |  ____|    / __ \\  \\ \\    / / |  ____| |  __ \\ ",
    "| |  __     /  \\    | \\  / | | |__      | |  | |  \\ \\  / /  | |__    | |__) |",
    "| | |_ |   / /\\ \\   | |\\/| | |  __|     | |  | |   \\ \\/ /   |  __|   |  _  / ",
    "| |__| |  / ____ \\  | |  | | | |____    | |__| |    \\  /    | |____  | | \\ \\ ",
    " \\_____| /_/    \\_\\ |_|  |_| |______|    \\____/      \\/     |______| |_|  \\_\\ ",
};

int difficulty[] = {10, 5, 3}; // the number of tries for each difficulty

int _random(int min, int max)
{
    static int init = 0;
    srand(time(NULL));
    init = (rand() % (max - min + 1) + min);
    return init;
}

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
    do
    {
        mvprintw(0, 0, "Voulez-vous rejouer? (o/n): ");
        refresh();

        player.replay = getchar();
        if (player.replay == 'o' || player.replay == 'O')
        {
            clear();
            hint(-1, 1);
            memset(player.indexs, 0, sizeof(player.indexs));
            memset(player.alreadyFound, 0, sizeof(player.alreadyFound));
            memset(player.word, 0, sizeof(player.word));
            Game();
        }
        else if (player.replay == 'n' || player.replay == 'N')
        {
            clear();
            mvprintw(0, 0, "Au revoir!\n");
            refresh();
            endwin();
            exit(0);
        }
    } while (player.replay != 'O' && player.replay != 'o' && player.replay != 'n' && player.replay != 'N');
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
    init_pair(2, COLOR_GREEN, COLOR_BLACK); // Green

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
            if (isExist(player.alreadyFound, alpha) == 1)
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
}

/**
 * The function displays a menu for selecting the difficulty level and prompts the user to choose a
 * level until a valid input is entered.
 *
 * @param position The position parameter is the column position where the difficulty menu will be
 * displayed on the screen.
 */
void difficultyMenu(int position)
{
    do
    {
        mvprintw(0, position, "Menu de difficulte :\n\n");
        mvprintw(2, position, "\t1. Facile\n");
        mvprintw(3, position, "\t2. Moyen\n");
        mvprintw(4, position, "\t3. Difficile\n\n");
        mvprintw(6, position, "Choisissez le niveau de difficulte: ");
        refresh();
        scanw("%d", &player.difficulty);
    } while (player.difficulty < 1 || player.difficulty > 3);
}

/**
 * The function displays a game menu and prompts the player to make a choice.
 *
 * @param position The position parameter is the column position where the game menu will be displayed
 * on the screen.
 */
void theme(int position)
{
    do
    {
        mvprintw(0, position, "Theme du jeu :\n\n");
        mvprintw(2, position, "\t1. Animaux      | 4. Musique\n");
        mvprintw(3, position, "\t2. Informatique | 5. Education\n");
        mvprintw(4, position, "\t3. Football     | 6. Aleatoire\n\n");
        mvprintw(6, position, "Saisissez votre choix: ");
        refresh();
        scanw("%d", &player.theme);
    } while (player.theme < 1 || player.theme > 6);
}

/* It's the function that is called in the main function, it's the function that prints the welcome
message, the difficulty menu, the game menu, and the loading animation. */
void Welcome(void)
{
    initscr(); /* Start curses mode 		  */

    mvprintw(0, 0, "Bienvenue dans le jeu du pendu!");
    mvprintw(2, 0, "Saisissez votre nom: ");
    refresh();
    getstr(player.name);

    mvprintw(4, 0, "Bienvenue %s !", player.name);
    refresh();
    sleep(1);
    difficultyMenu(50);
    theme(100);
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

    int randomWordIndex = _random(0, 41);
    read_words();
    char *randomWord = data.words[randomWordIndex];
    // remove the \n from the word
    randomWord[strlen(randomWord) - 1] = '\0';
    int wordLen = strlen(randomWord);
    int k = 0;

    start_color();                          /* enable color */
    init_pair(3, COLOR_BLACK, COLOR_WHITE); // White

    mvprintw(2, 100, "Le mot a trouver contient %d lettres\n\n", wordLen);
    mvprintw(3, 100, "Vous avez %2d chances\n\n", difficulty[player.difficulty - 1]);
    attron(COLOR_PAIR(3));
    mvprintw(29, 0, "+================================================+\n");
    mvprintw(30, 0, "| Appuyez sur la touche '0' pour quitter le jeu  |\n");
    mvprintw(31, 0, "+================================================+\n");
    mvprintw(32, 0, "| Appuyez sur la touche '1' pour une indication  |\n");
    mvprintw(33, 0, "+================================================+\n");
    attroff(COLOR_PAIR(3));
    refresh();

    do
    {

        /* Checking if the player has won the game. */
        if (strcmp(randomWord, player.word) == 0)
        {
            clear();
            attron(COLOR_PAIR(2));
            for (size_t i = 0; winAcsiiArt[i]; i++)
            {
                mvprintw(20 + i, 60, "%s" ,winAcsiiArt[i]);
            }
            attroff(COLOR_PAIR(2));
            system("nohup aplay winSOund.wav > /dev/null 2>&1 &");
            int i = 0;
            while (i < 10)
            {

                mvprintw(1, 0, "game restart in %02d", 9 - i);
                refresh();
                sleep(1);
                i++;
            }
            clear();
            rePlay();
        }
        /* Checking if the player has lost the game. */
        else if (player.chance >= difficulty[player.difficulty - 1])
        {
            usleep(1500000);
            clear();
            attron(COLOR_PAIR(1));
            for (size_t i = 0; loseAcsiiArt[i]; i++)
            {
                mvprintw(20 + i, 60, "%s",loseAcsiiArt[i]);
            }
            system("nohup aplay loseSound.wav > /dev/null 2>&1 &");
            attroff(COLOR_PAIR(1));
            player.chance = 0;
            rePlay();
        }

        /* It's printing the number of chances left and the word to guess. */
        mvprintw(2, 0, "Chances restantes: %02d", (difficulty[player.difficulty - 1] - player.chance));
        // mvprintw(3, 0, "Word: %s", randomWord);
        refresh();

        /* It's printing the keyboard on the screen. */
        keyboard(8, 50);
        mvprintw(2, 50, "Saisissez une lettre: ");
        player.letter = getch(); // It's getting the letter that the player has guessed.
        refresh();

        if (player.letter == '0')
        {
            clear();
            endwin();
            exit(0);
        }
        else if (player.letter == '1')
        {
            attron(COLOR_PAIR(2));
            mvprintw(4, 100, "Indication: ");
            attroff(COLOR_PAIR(2));
            mvprintw(4, 112, "%s", hint(randomWordIndex, 0));
            refresh();
        }

        /* It's checking if the letter that the player has guessed is in the word, if it is, it prints a
        message to the player, otherwise it prints another message. */
        if (isExist(randomWord, player.letter))
        {
            mvprintw(5, 0, "Message: La lettre %c existe dans le mot\n", player.letter);
            refresh();
        }
        else if (player.letter != '1')
        {
            mvprintw(5, 0, "La lettre %c n'existe pas dans le mot\n", player.letter);
            refresh();
            player.chance++;
            int i = 10;
            int j = difficulty[player.difficulty - 1] - player.chance;
            while (i >= j)
            {
                mvprintw(22 + i, 100, "%s",penduSurface[i]);
                refresh();
                i--;
                mvprintw(2, 0, "Chances restantes: %02d", (difficulty[player.difficulty - 1] - player.chance));
            }
        }

        /* It's checking if the letter allowed to the player to guess the word. */
        if (isalpha(player.letter) || player.letter == ' ' || player.letter == '-' || player.letter == '\'')
        {
            findLetterIndex(randomWord, player.letter);
            player.alreadyFound[k] = toupper(player.letter);
            k++;

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
            mvprintw(5, 0, "Message: La lettre %c n'est pas autorisee\n", player.letter);
            refresh();
        }

    } while (1);

    endwin(); /* End curses mode		  */
}

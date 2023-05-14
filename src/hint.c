#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hint.h"
#include "../include/main.h"
#include <ncurses.h>

static char paths[6][MAX_LENGTH] = {
    "./resource/animals",
    "./resource/Informatique",
    "./resource/foot"
    "./resource/music",
    "./resource/edu",
    "./resource/",
};

/**
 * The function returns a hint from a file based on an index input, with a limit of three hints.
 *
 * @param index The index parameter is an integer that represents the line number of the hint to be
 * retrieved from the file.
 *
 * @return a pointer to a character array (string) containing a hint for a given index. If all hints
 * have been used, it returns an error message.
 */
char *hint(int index, int boolean)
{

    static int hint_count = 0;

    if (boolean)
        hint_count = 0;

    static char hints[3][MAX_LENGTH] = {"/hint1.txt", "/hint2.txt", "/hint3.txt"};
    static char hint[MAX_LENGTH];
    static char errorString[] = "Plus aucun indice n'est disponible";
    char path[MAX_LENGTH];

    strcpy(path, paths[player.theme - 1]);
    strcat(path, hints[hint_count]);

    FILE *fp = fopen(path, "r");
    if (hint_count >= 3)
    {
        return errorString;
    }
    else if (index != -1)
    {
        if (fp == NULL)
            return strcat("Impossible d'ouvrir le fichier ", hints[hint_count]);

        // reading line by line, max 256 bytes(255 characters + 1 null terminator)
        char buffer[MAX_LENGTH];

        int line_count = 0;
        while (fgets(buffer, MAX_LENGTH, fp))
        {
            // remove the newline character
            buffer[strcspn(buffer, "\n")] = 0; // strcspn() returns the number of characters in the initial segment of str1 which are not in the string str2.
            if (line_count == index)
            {
                strcpy(hint, buffer);
                break;
            }
            line_count++;
        }
        // close the file
        fclose(fp);

        hint_count++;
    }

    return hint;
}

/**
 * This function reads words from a file and stores them in an array.
 *
 * @return an integer value, which is 0 if the file was successfully read and 1 if there was an error
 * opening the file.
 */
int read_words()
{
    char path[MAX_LENGTH];
    strcpy(path, paths[player.theme - 1]);
    strcat(path, "/words.txt");
    // the * in *fp means that fp is a pointer to a FILE object (not a FILE object itself) and that it is uninitialized (it doesn't point to anything yet) and that it will be initialized by the fopen function.
    FILE *fp = fopen(path, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", path);
        return 1;
    }

    // reading line by line, max 256 bytes(255 characters + 1 null terminator)
    char buffer[MAX_LENGTH];

    int i = 0;
    while (fgets(buffer, MAX_LENGTH, fp))
    {
        // remove the newline character
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(data.words[i], buffer);
        i++;
    }

    // close the file
    fclose(fp);

    return 0;
}

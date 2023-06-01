#include "../include/main.h"

struct playerData player;
struct main data;
PlayerStats person;


/**
 * The function "intro" displays an introduction message for the Hangman game and waits for a keypress
 * to start playing.
 */
void intro(void)
{
    char text[] = {"Hello! Welcome to Hangman. This is a classic word-guessing game where you have to guess a hidden word by suggesting letters one at a time.\n\nFor each incorrect guess, a part of a 'hangman' is drawn on the screen. You have to guess the word before the hangman is complete, or you lose the game.\n\nTo get started, you will need to input a letter to guess the hidden word.If the letter you guessed is in the word, it will be revealed on the screen.\nIf not, a part of the hangman will be drawn on the screen.You win the game if you successfully guess the word before the hangman is complete.\n\nPress any key to start playing and see how many words you can guess correctly.Good luck !"};

    system("nohup aplay intro.wav > /dev/null 2>&1 &");

    for (int i = 0; text[i] != '\0'; i++)
    {
        printf("%c", text[i]);
        fflush(stdout); // flushes the output buffer of a stream
        usleep(56750);
    }

    // wait for a keypress to continue
    printf("\n\n\n");
    printf("Press any key to start playing...");
    fflush(stdout);

    /* This code block is disabling input buffering and echoing in the terminal. */
    struct termios old_term, new_term;
    tcgetattr(STDIN_FILENO, &old_term);
    new_term = old_term;
    new_term.c_lflag &= ~(ICANON | ECHO); // ~ = bitwise NOT operator (inverts each bit)
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);

    // read a single character
    getchar();

    // restore the old terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
}

int main()
{
    intro();
    Welcome();
    Game();

    // Get the current time
    time_t currentTime = time(NULL);

    // Convert the time to a local time structure
    struct tm *localTime = localtime(&currentTime);

    // Format the date and time string
    char dateTimeString[100];
    strftime(dateTimeString, sizeof(dateTimeString), "%Y-%m-%d %H:%M:%S", localTime);

    json_object *person_json = json_object_new_object();
    json_object_object_add(person_json, "time", json_object_new_string(dateTimeString));
    json_object_object_add(person_json, "name", json_object_new_string(player.name));

    json_object *string_array = json_object_new_array();

    for (int i = 0; i < person.num_words; i++)
    {
        json_object_array_add(string_array, json_object_new_string(person.guessed_words[i]));
    }

    json_object_object_add(person_json, "guessed_words", string_array);
    json_object_object_add(person_json, "score", json_object_new_int(person.score));

    const char *json_string = json_object_to_json_string_ext(person_json, JSON_C_TO_STRING_PRETTY);
    FILE *file = fopen("./html/leaderboard.json", "r+");

    // Check if the file is empty
    fseek(file, 0, SEEK_END);
    long size = ftell(file);

    if (size == 0)
    {
        fprintf(file, "[%s]", json_string);
    }
    else
    {
        fseek(file, -1, SEEK_END); // Move the file pointer to the position before the closing bracket
        char last_char = fgetc(file);
        if (last_char == ']')
        {
            fseek(file, -1, SEEK_END); // Move the file pointer to the position before the closing bracket
            fprintf(file, ",%s]", json_string);
        }
        else
        {
            fseek(file, 0, SEEK_END);
            fprintf(file, ",%s]", json_string);
        }
    }

    fclose(file);
    json_object_put(person_json);

    initscr();

    // Clear the screen
    clear();
    mvprintw(0, 0, "Thank you for playing Hangman!\n");
    system("python3 -m http.server > /dev/null 2>&1 &");
    mvprintw(1, 0, "You can view the leaderboard at http://localhost:8000/html\n");
    mvprintw(2, 0, "Press q to quit\n");
    refresh();

    while (getch() != 'q');
    endwin();

    return 0;
}
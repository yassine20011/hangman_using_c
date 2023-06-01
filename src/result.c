#include <stdio.h>
#include "../include/util.h"
#include <stdlib.h>
#include <string.h>

int main() {



    strcpy(player.username, "test");

    FILE *htmlFile = fopen(strcat(player.username, ".html"), "w");

    // Write the HTML header
    fprintf(htmlFile, "<html>\n");
    fprintf(htmlFile, "<head>\n");
    fprintf(htmlFile, "<title>Generated HTML</title>\n");
    fprintf(htmlFile, "</head>\n");
    fprintf(htmlFile, "<body>\n");

    fprintf(htmlFile, "<table border=\"1\">\n");
    fprintf(htmlFile, "<tr>\n");
    fprintf(htmlFile, "<th>Player name</th>\n");
    fprintf(htmlFile, "<th>Word</th>\n");
    fprintf(htmlFile, "<th>Already found</th>\n");
    fprintf(htmlFile, "<th>Indexs</th>\n");
    fprintf(htmlFile, "<th>Chance</th>\n");
    fprintf(htmlFile, "<th>Theme</th>\n");
    fprintf(htmlFile, "<th>Difficulty</th>\n");
    fprintf(htmlFile, "</tr>\n");
    fprintf(htmlFile, "<tr>\n");
    fprintf(htmlFile, "<td>%s</td>\n", player.name);
    fprintf(htmlFile, "<td>%s</td>\n", player.word);
    fprintf(htmlFile, "<td>%s</td>\n", player.alreadyFound);
    fprintf(htmlFile, "<td>%d</td>\n", player.theme);
    fprintf(htmlFile, "<td>%d</td>\n", player.difficulty);
    fprintf(htmlFile, "</tr>\n");
    fprintf(htmlFile, "</table>\n");
    
    // Write the HTML footer
    fprintf(htmlFile, "</body>\n");
    fprintf(htmlFile, "</html>\n");

    fclose(htmlFile);  // Close the HTML file

    printf("HTML file generated successfully!\n");

    return 0;
}

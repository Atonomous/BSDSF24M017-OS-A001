#include "../include/myfilefunctions.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int wordCount(FILE* file, int* lines, int* words, int* chars) {
    if (!file || !lines || !words || !chars) return -1;
    *lines = 0; *words = 0; *chars = 0;
    int ch, in_word = 0;

    rewind(file);
    while ((ch = fgetc(file)) != EOF) {
        (*chars)++;
        if (ch == '\n') (*lines)++;
        if (isspace(ch)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            (*words)++;
        }
    }
    return 0;
}

int mygrep(FILE* fp, const char* search_str, char*** matches) {
    if (!fp || !search_str || !matches) return -1;
    rewind(fp);
    char buffer[1024];
    int count = 0;
    *matches = NULL;

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strstr(buffer, search_str) != NULL) {
            char** temp = realloc(*matches, (count + 1) * sizeof(char*));
            if (!temp) return -1;
            *matches = temp;
            (*matches)[count] = strdup(buffer);
            count++;
        }
    }
    return count;
}

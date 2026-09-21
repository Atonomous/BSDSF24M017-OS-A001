#include <stdio.h>
#include <stdlib.h>
#include "../include/mystrfunctions.h"
#include "../include/myfilefunctions.h"

int main() {
    printf("--- Testing String Functions ---\n");
    char buf[100];
    mystrcpy(buf, "Hello");
    printf("mystrlen: %d\n", mystrlen(buf));
    mystrcat(buf, " World!");
    printf("mystrcat: %s\n", buf);

    printf("\n--- Testing File Functions ---\n");
    FILE* f = fopen("test.txt", "w+");
    if (f) {
        fputs("Line 1: Hello World\nLine 2: Operating Systems\nLine 3: Hello Linux\n", f);
        int l, w, c;
        wordCount(f, &l, &w, &c);
        printf("Lines: %d, Words: %d, Chars: %d\n", l, w, c);

        char** matches = NULL;
        int count = mygrep(f, "Hello", &matches);
        printf("Matches found for 'Hello': %d\n", count);
        for (int i = 0; i < count; i++) {
            printf("  [%d]: %s", i + 1, matches[i]);
            free(matches[i]);
        }
        free(matches);
        fclose(f);
        remove("test.txt");
    }
    return 0;
}
